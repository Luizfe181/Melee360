# Bootstrap original, depop AX e copia RGBA6

## Implementado em execucao

O main Xbox agora instala lbMemory_8001564C, lbHeap_80015F3C e lbHeap_80015900 antes dos objetos HSD. Seq (2 KiB) e Stay (tamanho original) ficam fora do HSD ativo. Uma particao de 1 MiB e reservada para o heap de audio antes da separacao dos heaps; HSD_AudioMalloc/HSD_AudioFree usam os corpos originais de synth.c e o OSHeap real. lbHeap/lbMemory executam alocacao/liberacao RAM e ARAM. A arena nativa total continua sendo 64 MiB; isto nao reproduz a capacidade fisica do GameCube.

Foi corrigida a identificacao RAM/ARAM de lbmemory.c: o limite 0x80000000 do GameCube classifica incorretamente ponteiros Xbox. A copia de compatibilidade usa ARGetSize para identificar enderecos ARAM. O original permanece intacto. Gerador e proveniencia: diagnostics/generate_bootstrap_memory.py, logs/bootstrap-memory-provenance.json e bootstrap-original-bodies.json.

PdPm.dat e PlCo.dat agora sao lidos pelo HSD_DevComRequest original com callbacks reais de DVD; uma espera cooperativa no mesmo thread bombeia DVD/ARAM. Depois lbArchive_InitializeDAT original aplica relocacoes e valida plLoadCommonData/ftLoadCommonData. Os dados ficam residentes. Esta ponte usa o DevCom e o initializer originais, mas ainda nao usa toda a cadeia lbFile/lbArchive_LoadSymbols nem liga os globais Player/Fighter. Nao e uma chamada de Fighter_Create ou uma partida.

AX: o consumidor atualiza os samples finais de depop do PB; as somas e fades sao calculados por __AXDepopVoice/__AXPrintStudio originais. O mixer nativo aplica volume inicial e delta L/R por sample antes da soma das vozes e saturacao para PCM16. Os vetores cobrem sinais opostos, corte abaixo de 160, varios frames e saturacao. O teste de vozes continuas e HPS permanece passando. Nao ha comparacao de captura bit a bit com o DSP nem validacao no console desta revisao.

GX: RGBA6 agora permite filtro RGB na copia mantendo o alpha da linha central. GXCopyTex quantiza o clear regional e recusa mascaras parciais RGBA6. Foram verificados 28 pixels decodificados: quatro clamps, alpha central, copia antes do clear, clear quantizado e preservacao fora da regiao. Mantem as restricoes de target linear, sem multisampling, blending ou downsample neste caminho.

## Testes

Build XDK sem /FORCE ou stubs. Training: bootstrap-copy-training.txt. Audio/depop: bootstrap-depop-sound.txt. A build final e suas regressoes estao em bootstrap-final-build.txt, bootstrap-final-aa-stage.txt e bootstrap-final-sound.txt. O verificador exige os marcadores novos de heaps, arquivos, depop e copy RGBA6.

Auditorias Mario/Link normal e HSD main heap: zero simbolos ausentes e zero duplicacoes. Restos de synth/lbarchive compartilham os corpos ja compilados no runtime; os modulos integrais lbheap/devcom e lbmemory adaptado nao sao ligados duas vezes. Fighter nao foi executado. Inventario publico GX: 116 simbolos compilados, 2 inline e 132 ausentes; este inventario tem escopo diferente do caminho Mario/Link.

Falhas diagnosticadas: limite RAM/ARAM do GameCube (bootstrap-training.txt), e nome errado de root no novo probe (bootstrap-training-recheck.txt). O root correto PlCo e ftLoadCommonData, nao ftCommonData. Logs foram preservados.

## Proximos bloqueios concretos

1. Conectar lbFile e lbArchive_LoadSymbols originais a espera cooperativa; o lbFile original espera callbacks dentro de lb_800195D0. A ponte atual carrega as duas archives diretamente via DevCom, portanto nao substitui o scheduler de carregamento completo.
2. Executar Player_InitAllPlayers, Player_80036DD8 e Player_80036DA4 com dados/globais originais, inicializar lbDvd/preloads e caches de fighter/costume. O link ja fecha, mas nao valida essa ordem ou os dados em runtime.
3. Coordenar o allocator logico ARAM original com as reservas feitas pelo ARAlloc nativo. Os probes atuais nao deixam blocos ARAM residentes; futuras banks/caches nao podem reservar a mesma faixa por allocators independentes.
4. Criar Mario/Link, registrar e executar seus GObj procs e instalar o estado original de Battlefield; colisoes/animacoes/eventos do mapa nao estao completos. O preview ainda tem callbacks de eventos ausentes.
5. RGBA6 blending/AA/sRGB, downsample/formatos de copy adicionais e fidelidade de lighting GPU. Esses modos nao foram declarados prontos.
6. AX SRC quatro taps com coeficientes DSP, updates por milissegundo, FIR/ITD/rampas, aux send/return e surround. Depop L/R foi integrado, mas aux/surround depop e equivalencia do fim natural de voz ainda precisam validacao.

Referencias primarias de comportamento, sem copiar corpos do Dolphin: https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/VideoCommon/TextureConversionShader.cpp (filtro RGB preserva alpha) e https://github.com/dolphin-emu/dolphin/blob/master/Source/Core/Core/HW/DSPHLE/UCodes/AX.h (rampa inicial dos buffers). Os corpos Melee/Dolphin SDK usados aqui vieram da base decomp local.

A primeira regressao AA desta revisao encontrou GXSetCopyFilter(false) no novo probe enquanto o modo XFB era AA. O probe agora preserva o modo AA do ambiente ao testar o target temporario single-sample; isso nao adiciona suporte RGBA6 com AA. Falha preservada em bootstrap-final-aa-stage.txt, rechecagem em bootstrap-final-aa-stage-recheck.txt.

Tambem falta validar as transicoes de scene/heaps: a reserva inicial Seq/Stay foi testada, mas reclaim/expansao posteriores precisam ser coordenados com os limites e a protecao de allocations vivas do HSD nativo. Os corpos extraidos de lbArchive_InitializeDAT e HSD_AudioMalloc/Free foram comparados literalmente com a base em bootstrap-body-verification.json.

Regressoes finais AA e Sound passaram no Xenia, exigindo os novos marcadores. Pacote atualizado: package/RGH/Melee360/default.xex; SHA256 059B36C3067FE40FD8C60D57535F3CC2EC633AEF8B1618A6C132CB0426768D51. Backup: work/default-before-bootstrap-runtime.xex. Manifesto: logs/bootstrap-package-verification.json. Nenhuma partida/Fighter foi executado; nenhuma validacao desta revisao no console real.
