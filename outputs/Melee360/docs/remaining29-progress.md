# Redução das 29 pendências — 2026-10-03

Este lote preserva work/melee-base e não utiliza /FORCE ou stubs. As auditorias incluem os objetos reais do runtime e a biblioteca original de gameplay. Compilar um símbolo não certifica todos os formatos ou modos de um subsistema.

## Implementações

### MCC: 12 símbolos

O módulo original mcc.c é gerado em compat/generated/portable_mcc.c, com proveniência em logs/portable-mcc-provenance.json. Preserva canais, mapa de blocos, flags, callbacks, notificações, estados e códigos de erro. Adaptações: alinhamento XDK, dispatch cooperativo em lugar de interrupção EXI, correção de leitura um byte além do mapa, contador de tentativas inicializado e validação de transferências negativas/overflow.

src/hio_xbox.cpp implementa transporte TCP para memória de adaptador de 128 KiB, mailbox e status. **Sem host configurado/conectado, a inicialização falha de verdade.** Não é memory card nem stub de dispositivo conectado. As transferências async concluem o RPC de forma bloqueante e entregam callback de conclusão depois, pelo pump; não há I/O assíncrono de rede em background. Código MCC original de stream foi compilado, mas o teste só cobre StreamOpen/Close, não o handshake de streaming de payload inteiro. A API MCC não foi certificada para chamadas simultâneas de vários threads.

O host de desenvolvimento diagnostics/mcc_host.py implementa o peer do protocolo nativo (memória, canais, ping e eco explícito de notificações). Não emula USB2EXI fisicamente e não implementa FIO host. Default escuta somente 127.0.0.1:36729. Uso: execute Python diagnostics/mcc_host.py; crie mcc-host.cfg junto da XEX contendo `IPv4 porta`, por exemplo `127.0.0.1 36729` no Xenia. O arquivo de configuração de teste não é publicado no pacote RGH. Para console, um host LAN explicitamente configurado é necessário; não foi testado neste lote.

Teste Xenia com peer real: MCCInit/EnumDevices, 15 blocos livres, abrir dois canais, recuperar estado, leitura/escrita byte-exata, callback deferred, notificação pelo host, erros e liberar os blocos. Relatório de operações TCP em logs/remaining29-mcc-host-live.json.

### GX: coordenadas e alpha de destino

GXSetNumTexGens e GXSetTexCoordGen2 são consumidos pelo caminho de vértices. Matrizes 2x4/3x4, fonte posição/normal/UV/cor SRTG, normalização e matrizes post (64–121). Todas as oito coordenadas carregam STQ; a divisão por Q acontece por fragmento no shader, após interpolação. A declaração nativa e a expansão de linhas/pontos foram ajustadas. **Bump texgen, binormal/tangente e matrizes dinâmicas por vértice de textura ainda não são suportados**; formatos não suportados falham explicitamente.

GXInvalidateVtxCache drena os draws anteriores. Este backend faz fetch CPU novo de atributos indexados a cada vértice, sem cache de índices persistente; não adiciona um cache fictício. Não houve teste específico novo de invalidação, além das regressões existentes de atributos indexados.

GXSetDstAlpha usa dois passes: primeiro RGB com alpha original para o blend, depois alpha de destino constante, repetindo o mesmo teste de alpha e usando EQUAL se o primeiro passe escreveu depth. Quatro readbacks GPU cobrem alpha constante, blend SRCALPHA, fragmento rejeitado e depth LESS com escrita. Implementação no pipeline direto GX; previews que desenham por outro renderer não ganham automaticamente esse comportamento. Custo extra de draw, sem otimização neste lote.

### THP: duas funções de decode

THPDec_80331340 e THPDec_803313D0 consomem o THPFileInfo do parser original, tabelas originais e preditores DC. Entropia Huffman/AC/DC, IDCT AA&N nativo e saída Y/U/V no layout I8 8x4 substituem Gekko/GQR/locked cache. O butterfly já licenciado IJG/libjpeg-turbo em mth_decode.cpp é compartilhado. 31340 usa largura 640; 313D0 aceita stride múltiplo de 16, até 672. Suporte testado: 4:2:0, altura múltipla de 16. Estado interno de bits é nativo, não ABI de instruções Gekko. A assinatura original não tem tamanho do bitstream; não é um decoder seguro de entradas arbitrárias. Restart por intervalo preserva alinhamento e reset de preditores como o original, mas não foi testado com um asset de restart.

Teste com frames 0, 90 e 300 de MvOpen.mth nas duas entradas: **1.843.200 pixels**, maior erro RGB 3 contra o decoder portátil da intro, sentinelas intactas. Não certifica identidade bit a bit com Dolphin; a intro existente continua no decoder portátil por desempenho.

### AI: inicialização e clock DSP

AIInit e AISetDSPSampleRate inicializam uma voice PCM estéreo real no XAudio2 e configuram 32/48 kHz independentemente do HPS. Também implementados DMA start/stop/endereço/tamanho/bytes restantes e registro de callback. Samples BE do GameCube são convertidos para PCM LE. Um thread nativo atende eventos OnBufferEnd, chama o callback DMA e submete o próximo buffer real. O buffer de stack Gekko opcional não é usado para trocar o stack Xenon; callbacks usam o stack do thread nativo. Inicialização idempotente; fechamento integrado antes de destruir o engine compartilhado.

Teste: consumo SamplesPlayed real e três callbacks em cada rate, leitura do sample rate da voice e estado parado. Este DMA é a saída para um futuro mixer AX; ainda não gera samples das vozes AX. Serviços completos de interrupção/contador/trigger do stream AI não foram acrescentados por este lote.

### Runtime OS e diagnóstico de stack

OSGetResetCode lê XGetLaunchData real e valida registro versionado/checksum; cold boot para dados ausentes/externos. OSResetSystem executa callbacks por prioridade, readiness com timeout, callbacks finais, drena CARD/ARAM, fecha áudio/MCC e prepara XSetLaunchData/XLaunchNewImage. O teste cobre ordem, retries e drenagem. **Relaunch/dashboard ainda não foram executados**, e shutdown é mapeado para dashboard, não desligamento físico.

OSCheckActiveThreads valida handles, liveness e páginas de stack dos threads registrados no runtime nativo. O teste cria e termina um worker real. Não valida filas de scheduler GameCube nem contabiliza threads de bibliotecas que não foram registrados. db_PrintThreadInfo foi adaptado em cópia isolada para consultar os stacks Xenon; as dependências dos rótulos-array _stack_addr/_stack_end foram removidas do consumidor, sem criar rótulos fictícios. High-water mark não é anunciado: só limites e uso atual consultados.

### GXSetZCompLoc

Depth antecipado é executado por triângulo em passe sem cor/alpha, seguido de passe de cor com depth EQUAL. Três readbacks GPU confirmam que um fragmento próximo rejeitado pelo alpha bloqueia o desenho distante apenas no modo antecipado; depth igual com LESS também não escreve cor. O stencil D24S8 interno marca os fragmentos aprovados no primeiro passe. Outros formatos de depth e stencil de usuário ativo não são suportados neste caminho. Z-texture simultâneo com early depth é rejeitado explicitamente. O custo de passes adicionais não foi otimizado.

## Pendências reais

As duas auditorias integrais confirmam **29 → 3 pendências, zero duplicados** (fighter-create-mario-link-summary.json e fighter-create-mario-link-hsd-main-heap-summary.json). A recompilação geral produziu **985/987** módulos: debug.c e initialize.c ainda falham como unidades diretas; o caminho auditado usa suas adaptações de runtime existentes. O inventário GX geral registra **115/250 símbolos compilados, 2 inline e 133 ausentes**; isso é outro escopo, não a lista de três dependências do caminho Fighter. Permanecem como bloqueios técnicos:

- AXInit/AXRegisterCallback: o original AXInit chama inicialização de command lists/studio/output DSP. AXOutNewFrame envia listas por mailbox ao DSP e sincroniza PBs, auxiliares e callback por frame. A saída AI PCM está testada, mas ainda não há executor/mixer dessas listas e AXVPBs. Registrar callback sem esse produtor de frames deixaria o caminho incompleto.
- GXSetDither: falta o caminho RGBA6_Z24 com precisão de cor/alpha e blend correspondente. Revendo a implementação de referência Dolphin, o Bayer 2x2 atua no resultado TEV antes de fog/blend e só no modo RGBA6; a afirmação anterior de que o dither em si ocorre após o blend estava incorreta. RGB8 não usa esse dither. Referência primária: https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/PixelShaderGen.cpp (GetPixelShaderUid e etapa Dithering). Nenhum código GPL deste arquivo foi copiado para o port.

O inventário foi recompilado por inteiro após detectar que uma compilação parcial DB substituía a lista geral. compile-gameplay.ps1 agora preserva entradas de outras áreas ao atualizar uma área, evitando contagens com escopo truncado.

Os Fighters originais ainda não linkam nem foram executados por este lote. As prévias Training/Battlefield não são partidas. Compilar os símbolos acima não conclui todos os modos GX, todos os serviços OS ou gameplay.
## Verificação deste lote

- Release/Compat gerada pelo XDK sem /FORCE; imagem retail criada por XexTool para o pacote de desenvolvimento.
- remaining29-final-training.txt: menu/CSS/Training preview e probes GX, THP, AI e OS; MCC com peer TCP real (718 operações, relatório remaining29-final-mcc-host.json).
- remaining29-final-sound.txt: Sound Test, duas faixas HPS, efeitos originais Std/Hi/Chorus, fade e retorno ao menu. Uma execução anterior expirou; a repetição é registrada separadamente.
- remaining29-final-aa-stage.txt: quatro variantes Battlefield com 120 updates por variante, VI/XFB e AA; callbacks de eventos de cenário ainda não suportados (4/4/4/2). Teste anterior à última alteração exclusiva de validação MCC; o código GX desta imagem é o mesmo.
- Base original verificada sem alterações. Nenhum teste novo deste lote foi executado no console real.
Pacote atualizado: package/RGH/Melee360/default.xex. SHA256: BF20D3045C391E5B1DF34F5550019F40B9D3D6D37FCD4181610C213E2E0D5743. Backup: work/default-before-remaining29.xex. Manifesto: logs/remaining29-package-verification.json.

### Continuação: consumidor de amostras AX

Melee360ARAMReadPCM oferece leitura síncrona e validada de PCM16 BE (formato AX 10, endereço em samples de 16 bits) e PCM8 assinado (formato 25, endereço em bytes). Usa a memória ARAM real alimentada por ARQ, sem converter seus offsets em ponteiros Xenon. O teste de serviços envia bytes reais por ARQ, verifica as duas interpretações e rejeita endereço fora de limite/formato não suportado. Isso é infraestrutura do futuro mixer, não AXInit completo: ADPCM, SRC, mix, envelope, update lists e callbacks por frame ainda precisam ser integrados. Release compilada em logs/ax-consumer-build.txt; teste Xenia em logs/ax-consumer-training.txt. Pacote público anterior preservado enquanto o mixer não estiver integrado.

### Dependências AX: studio original integrado

O gerador portable_ax inclui agora AXSPB.c original (hash de proveniência no manifesto), sem mudanças nas funções. __AXSPBInit, __AXGetStudio, __AXDepopVoice, __AXDepopFade e __AXPrintStudio estão compilados com o layout PPC32 real. O probe AX verifica os limites de fade ±20, zona inferior a 160, somas de canais L/R e atualização/subsequente esvaziamento do studio. Não implementa por si só o consumidor DSP que deve aplicar esses valores aos samples; não equivale a AXInit completo. Logs: ax-studio-build.txt, ax-studio-training.txt e ax-studio-*-audit.txt. O pacote público permanece na imagem previamente testada.

### Consumidor PCM de voz original → AI real

src/ax_pcm_consumer.c implementa o consumo nativo restrito de AXVPB: PCM16/PCM8 via ARAM, srcSelect=NONE, endereço final inclusivo, loop, volume com delta/saturação e ganhos L/R em acumuladores s32. Para impedir overflow dos ganhos, intermediários de mix usam s64. Não implementa o DSP completo nem __AXSyncPBs: usa os parâmetros CPU da voz; não aceita ADPCM, SRC, ITD, FIR, updates, auxiliares, surround, tipos especiais ou rampas de mix. Modos não aceitos retornam falha explícita. Não foi comparado bit a bit com o DSP GameCube.

O probe usa allocator/setters originais para preparar a voz, copia PCM por ARQ real, verifica quatro samples seguidos de parada/silêncio, loop de quatro samples por 160 frames, ganhos L/R e endereço final. O buffer gerado é consumido por voice AI/XAudio2 com três eventos reais de fim de buffer e SamplesPlayed>0. Isso testa uma saída sintetizada a partir de AXVPB; não cria ainda o scheduler/mixer de todas as vozes nem callback AX por frame. A repetição de playback do probe usa o mesmo buffer já produzido, não remixa ao vivo. Logs ax-pcm-build.txt e ax-pcm-training.txt. Os três símbolos continuam pendentes.

## AX contínuo, ADPCM e SRC linear

AXInit inicializa allocator/VPBs/studio/auxiliares originais e o driver de saída nativo a 32 kHz. O driver gera blocos de 160 samples (5 ms de áudio), percorre as listas de prioridade do allocator e mistura as vozes ativas. O callback de fim do buffer AI/XAudio2 pede o próximo bloco; AXRegisterCallback instala um callback de frame real, executado antes da mistura sob o lock de OS nativo. AXQuit para DMA, espera o worker e libera o estado; AudioClose também fecha AX. Shutdown deve ocorrer fora do callback/worker AI, verificado explicitamente para impedir auto-join. A frequência de callbacks acompanha a entrega de buffers XAudio2; jitter/underruns no console não foram medidos.

ADPCM formato 0 lê endereços em nibbles, cabeçalhos de 14 samples, coeficientes assinados, preditor/escala, arredondamento, saturação e histórico. Avanço pula os nibbles de cabeçalho. Loop carrega o contexto ADPCMLOOP. PCM formatos 10/25 continuam disponíveis. SRC NONE avança um sample por saída; SRC linear usa ratio 16.16 e fração persistente, incluindo múltiplos avanços e lookahead. Não há certificação bit a bit com o DSP: é tradução funcional nativa que consome PBs CPU diretamente, sem executar o microcode ou emular mailbox/command list.

Testes: vetores ADPCM de sinais positivos/negativos, feedback com coeficiente e reset de histórico em loop; PCM SRC 0,5; duas vozes simultâneas com mix exato; consumo SamplesPlayed real; troca/remoção de callback e continuidade após remoção; ADPCM loop + SRC 0,5 com saída AI real; modo 4-tap interrompe DMA explicitamente. ax-live-build.txt, ax-live-training.txt, ax-live-fighter-audit.txt e ax-live-hsd-audit.txt.

### Próximos bloqueios reais

- Link Fighter Mario/Link: resta GXSetDither; RGBA6 continua ausente. AXInit/AXRegisterCallback agora têm execução real restrita, não foram preenchidos por stubs.
- AX SRC de quatro taps e suas tabelas/coeficientes ainda não suportados.
- AX updates por milissegundo, sincronização separada dos PBs CPU/DSP, FIR, ITD, tipos especiais e rampas de mix ainda não suportados; uma voz ativa nesses modos falha e para o DMA.
- Auxiliares/surround: callbacks/rings originais executam, mas o mixer ainda não preenche os buses nem aplica seus retornos; vozes que exigem esses buses são rejeitadas.
- Depop: o studio original recebe e atualiza somas; aplicar esses valores à saída ainda falta. Não é certificada a supressão de estalos na saída nativa.
- DSP command lists/microcode, comparação com áudio Dolphin e playback de bancos SSM originais ainda não foram integrados/testados. Todos os testes novos são vetores de controle, não uma partida.
- GXSetDither/RGBA6 e os modos de rendering já documentados continuam necessários; o Fighter não foi executado neste lote.

Correções da verificação: um caso de SRC com fração 65535 e extremos -32768/+32767 detecta overflow de produtos s32; o interpolador usa s64 e o teste exige resultado 32766. A gravação de log foi serializada com um lock nativo: worker AX e thread principal escreviam simultaneamente e truncavam mensagens do probe, causando uma expiração de 180 segundos. O log anterior foi preservado em ax-live-before-log-lock-training.txt; repetir após a correção é necessário. Nenhuma expiração foi tratada como teste aprovado.
