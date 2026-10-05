# css-motion-boundary-1

Esta revisão acrescenta animação original à prévia dos 25 personagens do seletor e implementa dependências GX, DVD e calendário. O seletor ainda é uma integração parcial, e a build continua sem partidas ou áudio.

## Modelos animados

Os arquivos originais `Pl??DViWaitAJ.dat` contêm um arquivo HSD interno com FigaTree e FigaTrack. A ponte valida os limites dos dois arquivos, associa a lista de nós à hierarquia do modelo e fornece as trilhas compactadas ao `HSD_FObjReqAnimAll`/`HSD_FObjInterpretAnim` original já integrado. Ela aplica rotação, posição e escala aos descritores, incluindo a flag de escala clássica usada pelo `lbAnim_8001E6D8`, antes de transformar a geometria e os envelopes.

Isso executa os dados de animação e o interpretador original; não executa o gerenciador completo de animação do Fighter ou `lbAnim_8001E6D8` inteiro. O loop e a apresentação permanecem na ponte do port. A prévia atualiza no máximo 20 vezes por segundo, usando o tempo decorrido para escolher o frame original a 60 frames/s. O enquadramento é ajustado à geometria de cada pose; não reproduz a câmera completa do seletor.

A navegação continua usando os trechos originais de cursor/ficha/CKind da revisão anterior. O cache passou a manter dois arquivos ativos (seletor e modelo), com limite de 16 MiB de texturas por arquivo. Foi acrescentada invalidação ao trocar arquivos: o endereço do buffer pode ser reutilizado para outro personagem. Se a animação não carregar, o log identifica explicitamente o fallback para a pose estática.

Samus conserva duas malhas ignoradas, e Ice Climbers mostra Popo, sem Nana. Materiais, TEV e iluminação continuam parciais. Não há ataques, física, colisão, escolha de roupas, CPUs ou quatro jogadores.

## Dependências implementadas

- **GX:** 22 funções originais que operam na CPU, incluindo cálculo de luz/atenuação, cor, tamanho de textura com mipmaps, getters e tabela de ajuste de fog. Três descritores NTSC originais também foram integrados. A proveniência está em `logs/portable-gx-provenance.json`. O renderer nativo passa a usar o cálculo original de tamanho de textura. Os cálculos de luz/fog e descritores ainda não constituem um backend completo de GPU.
- **DVD:** implementação própria da API para os arquivos extraídos, mantendo os 1212 índices do FST original e validando os tamanhos dos 1209 arquivos. ID do disco vem do `boot.bin`, sem alterar os arquivos de origem. A reabertura de um `DVDFileInfo` inativo é permitida, inclusive dentro do callback, como o HSD original exige. Caminhos de subpastas são normalizados para o XDK. Open/close, estados, leitura síncrona e fila assíncrona com prioridade executam operações reais. O callback ocorre no pump seguinte, nunca dentro de `DVDReadAsyncPrio`; pode enfileirar outra leitura. Há 32 slots, limite de uma conclusão por frame, validação de alinhamento/limites e preenchimento com zero de até 31 bytes finais de alinhamento. A diferença de separadores de caminho detectada no Xenia foi corrigida.
- **Relatórios HSD:** setter original de `HSD_SetReportCallback`, ligado às mensagens formatadas de `OSReport` no Xbox, com proteção contra callback recursivo e teste de registro/remoção. A proveniência está em `logs/report-callback-provenance.json`. Não integra o hook privado de stdout do Metrowerks nem captura de contexto de panic.
- **Calendário:** seis corpos originais de `OSTime.c`, incluindo conversão de datas e anos bissextos. O relógio Xbox é calibrado ao epoch 2000 pelo RTC e avança pelo contador monotônico, mantendo a frequência GameCube de 40,5 MHz. Alterações posteriores do RTC não mudam os timers da sessão. Isso fornece conversão de datas; saves completos ainda não estão integrados.

A fila DVD pertence ao thread principal. Não é um serviço de leitura concorrente, nem emulação de timing do leitor óptico. O pump usa leitura bloqueante, então arquivos grandes podem causar pausas. O probe nativo também lê `audio/1padv.ssm`, sem reproduzir áudio. O backend ainda não substitui todas as leituras diretas dos viewers existentes; suas APIs e probe já executam na XEX.

## Validação

- `verify-fighter-animation.ps1`: 200 poses nos 25 modelos, alternando com o seletor e comparando resultados com cache quente/frio, movimento efetivo da geometria, coordenadas finitas, nenhuma nova malha ignorada e rejeição de arquivos truncados. `logs/fighter-animation-host.txt` registra as trilhas de cada personagem.
- `verify-css-scene.ps1`: 50 estados de mão/ficha nos 25 retratos, sem malhas ignoradas do seletor.
- `verify-stage.ps1`: 48 amostras cobrindo sete grupos de modelo e quatro fundos de Battlefield.
- `verify-gx-cpu.ps1`: resultados de atenuação/cor, tiling/mipmaps, fog e descritores NTSC.
- `verify-dvd.ps1`: igualdade dos bytes com o arquivo de origem, estados/callbacks adiados, prioridade, callback que agenda outra leitura, limites, alinhamento, padding e mídia ausente.
- `verify-report.ps1`: conteúdo, comprimento, chamada aninhada e remoção do callback.
- `verify-calendar.ps1`: epoch 2000, tick negativo, precisão de subseguundos, fevereiro de 2000, 2100 e 2400.

`logs/mario-css-motion-cpu.png` mostra uma pose animada por rasterização aproximada na CPU. Não é uma captura do Xbox. Os logs `css-motion-xenia-character.txt` e `css-motion-xenia-stage.txt` registram a verificação da XEX no Xenia. O teste de seleção no Xenia passou dentro de 90 segundos após a correção dos caches. As amostras de montagem de pose registraram médias de aproximadamente 23–42 ms; isso não é uma medição de FPS nem de desempenho no console. Esta revisão ainda precisa de teste físico no Xbox 360.

## Continuação

A auditoria caiu de 279 para **254 símbolos pendentes**, com **zero definições duplicadas**: GX 98, áudio/DSP/ARAM 45, OS/CPU/cache/debug 39, CARD 21, FIO/MCC 18, HSD 13, VI 12, THP 6 e PAD 2.

Os bloqueios maiores continuam na emissão real de comandos GX e inicialização/render HSD, além de áudio, CARD, VI e OS. A recompilação integral confirmou 985 de 987 unidades. `debug.c` ainda depende do stdout privado do Metrowerks; `initialize.c` ainda depende do heap/arena original. A biblioteca parcial permanece um artefato de diagnóstico; não está toda ligada à XEX. A contagem de símbolos não mede a porcentagem funcional do jogo. Consulte `logs/gameplay-compile/link-audit-summary.json` para a auditoria mais recente. O hash da XEX e os resultados finais estão em `logs/css-motion-final-verification.json`.

Copie a pasta inteira `package/RGH/Melee360` para HDD/USB e abra `default.xex` no Aurora/XeXMenu. Analógico/direcional move a mão; A solta a ficha; B pega/volta. Após confirmar, START abre apenas o diagnóstico animado de Battlefield, com LB/RB para mudar o fundo.
