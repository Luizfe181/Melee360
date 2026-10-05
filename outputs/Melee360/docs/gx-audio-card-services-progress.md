# gx-audio-card-services-1

Esta revisão acrescenta blocos funcionais de GX, áudio, OS e CARD. Não conclui esses subsistemas nem inicia uma partida. A auditoria integral caiu de **250 para 209 símbolos não resolvidos**, com zero duplicatas depois de separar as funções matemáticas originais das bibliotecas XDK. O pacote continua usando a camada de cenas parcial; a biblioteca de gameplay inteira não linka e não foi incorporada como jogo executável.

## GX e renderização

src/gx_xbox_state.cpp liga GXSetBlendMode, GXSetZMode, GXSetColorUpdate, GXSetAlphaUpdate e GXSetScissor ao dispositivo D3D9/Xenos. GXSetDrawDone/GXWaitDrawDone/GXSetDrawDoneCallback usam fences reais; GXPixModeSync espera a GPU. Callbacks de conclusão são despachados pelo runtime, sem uma interrupção Gekko. O dispositivo é emprestado, não criado pelo SDK Dolphin.

Título, menus, CSS e Battlefield agora usam o adaptador para blend, comparação/escrita de profundidade e escrita de cor/alpha. O probe lê estados de volta do dispositivo e verifica a conclusão da fence. Encontrou e corrigiu uma diferença de enums do XDK: comparações D3D no Xbox não seguem a numeração da versão PC. Escrever profundidade sem comparar mantém o teste em ALWAYS, em vez de desligar também a escrita.

Limites: scissor recebe coordenadas físicas do render target; a transformação completa VI/GX ainda falta. Blend lógico admite COPY; outros operadores lógicos são rejeitados explicitamente. Não há tradução geral de GXBegin/FIFO, display lists por chamadas GX, TEV, canais/luzes, matrizes e gerência de texturas. A leitura direta de display lists pelos viewers anteriores permanece. Os nove símbolos resolvidos não equivalem a um renderer GX completo.

## Áudio

src/hps_decode.cpp decodifica blocos HALPST/HPS em DSP ADPCM para PCM16 intercalado, com coeficientes, históricos por bloco, saturação, blocos parciais e offsets de repetição. Aceita mono/stereo, 8–48 kHz e limites explícitos de tamanho. Arquivos inválidos e predictors fora da faixa são rejeitados.

src/audio_xbox.cpp cria engine/master/source voices XAudio2. A música original audio/menu01.hps toca nos menus/CSS com três buffers, liberados pelos callbacks de término. A opção Música em Opções/Som controla o volume da voz. Filmes, título e diagnóstico Battlefield seguem sem trilha integrada. O dispatch de músicas original, efeitos SSM, vozes AX, resampling do mixer, DSP e efeitos auxiliares ainda faltam. Essa música usa um caminho nativo próprio, não o HSD_Synth/AX original completo.

verify-hps.ps1 passou vetores DSP conhecidos, rejeição de dados inválidos e **98 faixas / 3457 blocos / 390943044 amostras PCM**. Os primeiros quatro segundos de menu01.hps (256000 amostras intercaladas) coincidiram byte a byte com vgmstream CLI r2117-298-g7dc938fa. Esse teste não afirma comparação independente de todas as faixas. Referências primárias de formato: [HALPST](https://github.com/vgmstream/vgmstream/blob/master/src/meta/halpst.c) e [blocos HALPST](https://github.com/vgmstream/vgmstream/blob/master/src/layout/blocked_halpst.c). O decoder do port é próprio; o CLI ficou em work/vgmstream-reference, apenas como ferramenta de verificação. O PCM nativo usa a ordem de bytes esperada pelo Xbox, conforme o exemplo AtgAudio.cpp do XDK instalado.

As dependências xaudio2.lib e xmcore.lib foram adicionadas. O atanf global do adaptador anterior conflitava com o provider do XDK e foi removido. expf e atan2f originais passaram a Melee360OriginalExpf/Melee360OriginalAtan2f pela fronteira de compilação, como powf já fazia. Os corpos originais foram preservados e todos os callers do decomp recompilados. A função atan2 da ponte CSS continua isolada. Isso não verifica determinismo de gameplay.

## OS e ARAM

src/os_alarm.c fornece criação/cancelamento, alarmes absolutos/relativos/periódicos e verificação da fila. O runtime despacha até 32 callbacks vencidos por frame, com ordem estável; períodos atrasados saltam para o próximo prazo sem acumular uma chamada para cada intervalo perdido. Callbacks recebem contexto NULL: não há contexto de uma exceção decrementer do GameCube. Os serviços não substituem threads, caches, contextos/FPU, MSR, resets e configuração OS completos.

src/aram_memory.c fornece 16 MiB de RAM própria, base 0x4000, alocação LIFO ARAlloc/ARFree e transferências ARQ reais por memcpy. A fila tem 64 solicitações, prioridade alta antes da baixa e callbacks adiados; uma transferência é completada por pump. As estruturas e buffers da solicitação devem permanecer válidos até o callback. Não reproduz timing/chunks de DMA nem implementa o DSP/AX. O probe usa a mesma capacidade de stack de 16 entradas que o inicializador original do Melee.

## Memory card

src/card_filesystem.c implementa os 21 símbolos CARD pendentes: probe/mount/check/format, espaço livre, open/close, create/delete/rename, status, transferências sync/async e contagem de bytes. Há dois canais, cada um com capacidade de um card de 16 Mbit, 127 entradas e setores de 8192 bytes. Nomes do jogo são metadados; não viram caminhos no filesystem. Buffers e fileInfo de operações assíncronas devem viver até a conclusão.

Os containers são game:\\card-slot-a.m360card e game:\\card-slot-b.m360card. Persistência usa snapshot temporário, backup e rename, validação de limites e checksum FNV de metadados/payload. Pode recuperar um backup válido quando o snapshot principal está quebrado. Isso não garante durabilidade contra toda interrupção de energia; os saves não usam containers XContent. Formatar remove as entradas e o backup anterior desse card próprio. Não modifica a extração do jogo ou cards externos.

Formato privado, com byte order explicitamente verificada: não é RAW/GCI e não importa saves Dolphin. Metadados incluem timestamps do relógio original. UpdateIconOffsets de CARDStat.c foi extraído sem mudanças; proveniência em logs/card-icons-provenance.json. Layouts CARDFileInfo 20 bytes, CARDStat 108, ARQRequest 32 e OSAlarm 40 são verificados na compilação.

O fluxo original de save/formatar na interface ainda não foi conectado. As configurações provisórias anteriores do menu continuam em seu arquivo próprio. O probe grava/lê/reabre um card-selftest isolado, apaga somente seus arquivos temporários e restaura o prefixo normal; não formata os containers reais do jogador. Leitura/gravação e snapshot são síncronos dentro do pump e podem causar pausas; otimização posterior precisa medir isso no console.

## Verificações e pendências

Build Release/Compat e pacote RGH retail foram gerados. Host: alarmes, ARAM e CARD passaram ordem/cancelamento/reagendamento, LIFO/transferências byte-exatas, persistência, metadados, limites, rename/delete e corrupção. O Xenia verificou estados/fence GX, alarmes/CARD/ARAM, engine XAudio2, consumo das amostras HPS e navegação CSS. A revisão ainda requer teste físico no Xbox.

Recompilação: **985/987** módulos originais. Falham debug.c (FILE privado Metrowerks) e initialize.c (heap/MMIO original), como antes. Auditoria sem descartar referências: **209 pendências / 548 referências / zero duplicatas**.

| Grupo pendente | Símbolos |
| --- | ---: |
| GX | 89 |
| Áudio/DSP/AX | 39 |
| OS/CPU/cache/debug | 30 |
| FIO/MCC | 18 |
| Inicialização/render HSD | 13 |
| VI | 12 |
| THP | 6 |
| Configuração PAD | 2 |

Prioridades seguintes: pipeline GX de vértices/display lists/TEV, mixer AX e bancos SSM sobre a RAM adaptada, threads/contextos/arena OS, inicializador HSD sem MMIO e fluxo original de CARD na interface. Não há fighters executando combate, colisões ou partida.

O backup anterior está em logs/default-before-gx-audio-card-services-1.xex. Base doldecomp/melee e assets originais preservados. Relatórios e logs desta revisão têm prefixo gx-audio-card.
