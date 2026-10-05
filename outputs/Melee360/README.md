Diagnostico atual: Battlefield original com bots invisiveis e logica ativa. Pacote configurado para iniciar a partida diretamente. [Resultados e como reverter](docs/hide-bots-render-diagnostic.md).

Incremento atual: encerramento AX conclui o intervalo ativo de 32 amostras e preserva vozes paradas nos seguintes. Seis casos NONE/linear/4-tap verificados. Veja [cobertura e limites](docs/ax-voice-end-runtime.md).

Incremento atual: SRC linear AX com historico persistente corrigido; seis vetores fixos e reproducao AI continua verificados. Veja [cobertura e limites](docs/ax-linear-runtime.md).

# Melee360 — estado atual

Último incremento: updates PB AX por milissegundo, ligando as filas dos setters aos cinco intervalos de 32 amostras. Passou em scheduling via callback/AI, Training e regressão de 180 frames Mario/Link sem parada de áudio. FIR/ITD/DPL2 continuam pendentes. [Implementação, testes e limites](docs/ax-pb-updates-runtime.md).

Último incremento: envelope AX signed/wrap e mixer de nove canais, com retornos Aux A/B, depop, rampas e feedback Surround. Corrigidos Aux B isolado e limpeza dos buffers ao reinicializar. Training, seis vetores de envelope, teste dos buses e 900 frames Mario/Link passaram no Xenia sem parada de áudio. Updates PB/FIR/ITD/DPL2 ainda pendentes. [Implementação e limites](docs/ax-envelope-aux-runtime.md).

Última correção: streaming AX entre buffers de ARAM e preservação do histórico ADPCM para type=1. Training e 900 frames Mario/Link em Battlefield passaram no Xenia, com consumo AI/XAudio2 contínuo e sem parada de DMA AX. Mixagem completa e validação auditiva/física continuam pendentes. [Causa, testes e próximos passos](docs/ax-streaming-runtime.md).

Último incremento funcional: SRC AX de quatro taps para os três bancos, fase/histórico persistentes e saturação. Passou em 15 vetores fixos e ADPCM com playback AI contínuo no Xenia. Usa coeficientes livres do Dolphin, sem equivalência bit-exata com a ROM original. [Implementação e limites](docs/ax-polyphase-src.md).

Foco atual: conclusão funcional dos símbolos, antes de novas otimizações. Primeiro incremento: rampas estéreo AX por amostra usando o setter original, com deltas positivos/negativos, continuidade entre blocos e wrap de 16 bits. A presença no linker continua separada da cobertura funcional. [Fila, auditoria e limites](docs/symbol-completion-plan.md).

Última mudança: untile das cópias GX limitado à região solicitada e às linhas do filtro. Nas sombras de Battlefield, processa 78,6% menos bytes nesse estágio. Passou em 900 frames, sete capturas idênticas, Training e menus. Ganho total de FPS ainda inconclusivo. [Implementação e limites](docs/gx-copy-region-optimization.md).

Última revisão de cache: 1,72–2,09% menos tempo por frame e 29,46% menos uploads no teste repetido de 180 frames. Orçamento contabilizado de 64 MiB; passou em 900 frames, sete capturas idênticas, Training e menus. [Medições e limites](docs/gx-cache64-performance.md).

Otimização anterior: cache de texturas GX com 26,67% menos tempo por frame e 94,82% menos uploads na comparação de 180 frames originais no Xenia. A XEX final passou em 900 frames de combate, Training e navegação de menus. O desempenho continua insuficiente; não há ganho medido nos menus ou no console. [Medição, implementação e limites](docs/gx-texture-cache-performance.md).

Última revisão: Mario CPU vs Link CPU em Battlefield com desenho original HSD/GX, movimento e dano. Renderer experimental: materiais, desempenho e áudio AX ainda precisam de trabalho. [Resultado, execução e limites](docs/original-match-render-progress.md).


Port nativo experimental para Xbox 360 RGH/JTAG. Build atual: `original-fighter-assets-1`. Inclui vídeo da intro, título e menus animados com assets originais, seletor com retratos 2D e diagnóstico animado de Battlefield. A música original do menu toca via XAudio2. O combate CPU original possui um modo de diagnóstico com renderização HSD/GX original. Execute start-original-match-xenia.ps1 para testá-lo; materiais e desempenho ainda são experimentais.

Esta revisão adiciona estados GX de blend/depth/cor/scissor e fences GPU, alarmes OS, 16 MiB de ARAM com transferências adiadas e API CARD com persistência em arquivos próprios. Faltam o pipeline GX completo, mixer AX/SFX, threads/contextos OS e a conexão da interface original de save/formatar. [Implementação, verificações e limites](docs/gx-audio-card-services-progress.md).

O inventário de compilação registra **985 de 987 módulos**; partes de debug/initialize possuem adaptações nativas. As duas auditorias do caminho Mario/Link ligam com **zero símbolos pendentes e zero duplicações**, na auditoria de link. A execução CPU original é validada separadamente no modo de diagnóstico. O inventário público GX é separado: 116 símbolos compilados, 2 inline e 132 APIs ausentes. Essas contagens não indicam uma porcentagem confiável de conclusão.

Último incremento: arena OS própria de 8 MiB, com alocação pelas duas extremidades e validação de limites. [Verificações e limites](docs/os-arena-progress.md). A melhoria de cache do seletor foi mantida.

Incremento GX/áudio: viewport e cull nativos; música HPS no diagnóstico Battlefield, com retorno à faixa do menu. [Limites e verificação](docs/gx-viewport-audio-progress.md).

## Pacote e execução

O projeto Visual Studio 2010/XDK gera `package/RGH/Melee360/default.xex`, imagem Release retail para RGH/JTAG. Copie a pasta Melee360 inteira, incluindo `data` e `melee360-font.bin`, para o console. A revisão atual foi verificada no Xenia; ainda requer validação física.

O seletor usa partes do código original de cursor/ficha e commit de personagem. Por padrão mostra retratos 2D; `debug-css-models.flag` habilita modelos 3D de diagnóstico. START após confirmar abre Battlefield, com quatro variantes animadas; não inicia combate. As telas profundas de menu continuam provisórias. Configurações desse menu usam seu próprio arquivo, não o save original do Melee.

Os cards adaptados usam `card-slot-a.m360card` e `card-slot-b.m360card` ao lado da XEX. O formato privado não é RAW/GCI e não importa saves Dolphin. Testes internos usam arquivos `card-selftest` isolados; não formatam os containers do jogador.

## Verificação e reprodução

Build Release/Compat, empacotamento RGH e auditoria de link foram executados. Testes host verificaram alarmes, persistência/corrupção CARD, transferências ARAM, 98 músicas HPS e 200 poses de 25 modelos. O PCM dos primeiros quatro segundos de menu01 foi comparado byte a byte com um decoder independente. O Xenia verificou estados/fence GPU, callbacks OS/CARD/ARAM, consumo de áudio e navegação do seletor.

No PowerShell, nesta pasta:

```powershell
.\build.ps1 -DecompMode Compat -Configuration Release
.\package-rgh.ps1 -SkipAssetCopy
.\verify-platform-services.ps1 -Service alarm
.\verify-platform-services.ps1 -Service card
.\verify-platform-services.ps1 -Service aram
.\verify-hps.ps1
.\verify-xenia.ps1 -CharacterPreview
.\verify-xenia.ps1 -StagePreview
```

SkipAssetCopy pressupõe que os assets já estejam no pacote. Para reproduzir a auditoria: compile-gameplay.ps1, collect-gameplay-dependencies.ps1 e audit-gameplay-link.ps1.

## Base preservada

Base: doldecomp/melee, commit `17697c2d7e46f023f8c7320b75d8cf254ed8e5a4`, em work/melee-base na raiz do workspace. As adaptações ficam separadas neste projeto. A extração contém 1209 arquivos; nomes/tamanhos correspondem ao FST e a cópia foi comparada por SHA256. Isso verifica a cópia, não autentica todos os assets contra um disco conhecido. O main.dol corresponde ao SHA1 esperado para GALE01 1.02.

Relatórios históricos ficam em docs; estados antigos não substituem o relatório desta revisão. Backup anterior: logs/default-before-gx-audio-card-services-1.xex. O decoder JPEG da intro contém trabalho do Independent JPEG Group; termos em third_party/ijg/README.ijg.

Troféus (revisão do vídeo 2026-10-02): Galeria com Daisy/Party Ball e
pedestal originais, lista (Y), rotação (analógico) e Coleção com dois modelos.
Loteria identificada como demonstração: recompensa fixa, regras originais
pendentes. Progresso próprio em melee360-trophies-demo.bin; não importa GCI.
Veja docs/trophies-video-progress.md para implementação e limitações.

Áudio original AXFX (original-axfx-delay-1): callback de delay e hooks originais
integrados; init/settings/shutdown adaptados com validação e tratamento de
falha. Testes host/XDK e probe de boot. Ainda não conectado ao mixer de
partida ou à música XAudio. Audit: 175 símbolos ausentes, zero duplicados.
Detalhes: docs/original-axfx-delay-progress.md.

Training / SSS (original-training-sss-1): 1 jogador -> Training -> personagens
-> START abre seleção com assets originais de MnSlMap.usd, cursor/hit-test e
mapeamento originais. Apenas Battlefield aceita confirmação. Regras/jogadores
originais são preparados; o motor de partida ainda NÃO inicia. Não há treino
jogável. No VS, Battlefield continua sendo diagnóstico de cenário sem partida.
Detalhes e bloqueios: docs/training-stage-progress.md.

Incremento HSD: troca de heap com liberação pelo proprietário e preservação de dados vivos; [verificação e limites](docs/hsd-heap-transition-progress.md). Auditoria Fighter: 150 símbolos pendentes; nenhum frame de gameplay.

GXPosition2u8 direto implementado; auditoria Fighter: 149 símbolos. [Testes e limites](docs/gx-u8-progress.md).

GX: quads, triangle strips e fans convertidos com ordem dos vértices verificada no Xenia. [Detalhes](docs/gx-topology-progress.md). O escopo atual é compatibilidade completa de renderização e áudio; otimização depois.

Cores indexadas CLR0 implementadas para RGB8/RGBA8/RGB565; GXSetArray ainda parcial. Auditoria Fighter: 143 símbolos pendentes. [Testes](docs/gx-color-index-progress.md).

UVs indexadas TEX0 U8/F32 implementadas; auditoria Fighter: 141 símbolos. [Testes e limites](docs/gx-uv-index-progress.md).

Executor parcial GXCallDisplayList para primitivas/cores/UV implementado e testado no Xenia. Auditoria Fighter: 140 símbolos. [Limites importantes](docs/gx-display-list-progress.md).

Overlay FPS/ms sempre ativo em intro/título/menus/previews; apresentação medida em janelas de um segundo. Cópias redundantes de TRIANGLES removidas do backend direto. [Verificação e limites](docs/fps-overlay-progress.md).

Posições indexadas em display lists e faixa original da abertura com relógio de amostras implementadas. [Testes e limites](docs/gx-pos-opening-progress.md).

Atualização 2026-10-02: posições inteiras nas display lists GX e regressões de intro/Training verificadas. Consulte docs/gx-integer-progress.md para escopo e limitações.

Atualização 2026-10-02: Teste de som com tela original e 80 músicas na ordem original, fade-out, áudio dos vídeos de Arquivos e traduções da interface. Escopo e fila em docs/menu-priority-progress.md.

Atualização 2026-10-02: telas originais de Vibração/Som, ajustes por controle, Mono/Stereo real e Dados/Diversos com snapshot GCI validado pela rotina original. Consulte docs/options-data-progress.md.

Gameplay sem desenho: veja docs/headless-gameplay-progress.md. Novo subconjunto de logica original e probes Mario/Link/Battlefield; ainda sem partida executavel.

Dependencias Mario/Link: reverb padrao AXFX e HSD_ObjDumpStat implementados; auditoria com 136 simbolos restantes, sem stubs. Veja docs/mario-link-dependencies-progress.md.

Dependencias Mario/Link: PADSetSamplingRate e OSGet/SetSoundMode implementados, com auditoria atual de 133 simbolos restantes. Veja docs/pad-os-sound-progress.md.

GX PNMTXIDX: indice de matriz de posicao por vertice implementado em chamadas diretas e display lists. Auditoria Mario/Link: 132 simbolos restantes. Veja docs/gx-matrix-index-progress.md.

GXSetAlphaCompare implementado em shader dedicado ao backend direto; auditoria Mario/Link: 131 simbolos restantes. Veja docs/gx-alpha-progress.md.

AXFX Reverb Hi traduzido e testado com processamento de tres canais; auditoria Mario/Link: 128 simbolos restantes. Veja docs/reverb-hi-progress.md.

AXFX Chorus traduzido com tabela original e resampler fracionario; auditoria Mario/Link: 125 simbolos restantes. Veja docs/chorus-progress.md.

Integracao diagnostica PCM HPS -> Std/Hi/Chorus -> XAudio2, com carry de 160 frames e preservacao de duracao. Veja docs/effects-bridge-progress.md.

Oito dependencias FIO/OS memoria implementadas; auditoria Mario/Link: 125 -> 117 ausencias, zero duplicatas. Veja docs/fio-memory-progress.md.

Consultas de video e preferencia progressiva persistente implementadas; auditoria Mario/Link: 113 simbolos. Veja docs/video-settings-progress.md.

Documentacao geral e analise do decomp: [Mapa geral](docs/decomp/README.md), arquitetura, boot/partida, contratos, bloqueios, plano e catalogo de todos os arquivos de codigo.

Arena HSD: limites primarios e contagem de alocacoes por proprietario implementados; auditoria atual Mario/Link: 112 simbolos. Veja [evidencias e bloqueios](docs/hsd-arena-ownership-progress.md).

Ciclo original de pools HSD validado isoladamente e TrainingPreview aprovado no Xenia. XEX atualizada no pacote. [Resultado e bloqueios](docs/hsd-pool-lifecycle-progress.md). Auditoria permanece em 112 simbolos.

Inicializacao HSD original compilada numa auditoria isolada: 111 ausencias nesse caminho, com GXSetPixelFmt/GXSetFieldMode agora expostos. Runtime permanece em 112. [Evidencias e limites](docs/hsd-original-initialization-audit.md).

GXSetPixelFmt: RGB8/Z24 e depth-only implementados com targets nativos e mascaras de escrita. Auditoria HSD ampliada: 110; normal: 112. [Limites e validacao](docs/gx-pixel-format-progress.md).

GXLoadTexObj TEXMAP0: upload de texturas GX nao indexadas e sampler inicial implementados; CPU e seis queries GPU passaram. Auditoria normal 111, HSD ampliada 109. [Escopo e evidencias](docs/gx-texture-binding-progress.md).

Mipmaps, C4/C8/C14X2 e oito slots GX implementados no caminho direto; roteamento do estagio TEV inicial. 29 testes GPU passaram. Auditoria normal: 109; ampliada HSD: 107. [Evidencias e limites](docs/gx-mipmaps-palettes-units-progress.md).

Atualizacao GX: GXInitTexObjData original agora preserva o ponteiro Xbox ao trocar imagens. Teste CPU, 31 queries GPU e TrainingPreview passaram; veja docs/gx-mipmaps-palettes-units-progress.md.

GXSetTevOp: cinco modos predefinidos do primeiro estagio traduzidos. 41 queries GPU e TrainingPreview passaram no Xenia; auditoria Mario/Link em 108 pendencias. Combiner TEV geral segue pendente.

TEV direto/indireto: 28 APIs de GXTev/GXBump expostas, 16 estágios, oito UVs, duas cores e Z-texture. 694 casos GPU, TrainingPreview e quatro variantes de Battlefield passaram no Xenia. Auditoria Mario/Link: 88 ausências; HSD ampliada: 86. GXSetTevClampMode preserva a assertion original de API indisponível. [Implementação, evidências e limites](docs/gx-tev-completion-progress.md).

GXInvalidateTexAll: atualiza as cópias GPU das imagens originais sem alterar os bindings. 45 casos de textura, 694 TEV e TrainingPreview passaram no Xenia. Auditoria Mario/Link: 87 pendências; HSD ampliada: 85. [Evidências e limites](docs/gx-texture-invalidation-progress.md).

HSD/runtime: HSD_CreateMainHeap original agora executa no boot, com pools originais e proteção contra reset de memória viva. Build e TrainingPreview passaram; auditoria normal 86, ampliada 85, sem duplicados. [Escopo e bloqueios](docs/hsd-runtime-main-heap-progress.md).

HSD render: três corpos originais de ciclo de renderização integrados; StartRender chamado antes de cada frame no backend progressivo RGB8/Z24. Auditorias Mario/Link normal/ampliada: 83 ausências, zero duplicados. [Validação e limitações](docs/hsd-render-start-progress.md).

VI/XFB: máquina de estados original de video.c integrada a dois buffers GPU, Resolve/fence/Swap nativos, flush e espera real de apresentação. Auditorias Mario/Link: 69 pendências, zero duplicados. AA/entrelaçamento e filtros avançados continuam bloqueados explicitamente. [Escopo e testes](docs/vi-xfb-pipeline-progress.md).


