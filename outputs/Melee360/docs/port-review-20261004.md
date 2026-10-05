# Revisao incremental do Melee360 - 2026-10-04

Arquitetura preservada: codigo original/HSD -> GX -> traducao Melee360 -> Direct3D/Xenos. Esta rodada nao muda gameplay, fisica, AI, RNG, estados ou scheduler. Base `work/melee-base` preservada. Compilar todos os simbolos nao comprova comportamento completo.

## Decisoes por sistema

| Parte | Decisao | Implementacao atual, evidencia e proxima acao minima |
|---|---|---|
| GX -> Direct3D/Xenos | MANTER A TRADUCAO / OTIMIZAR A TRADUCAO | `gx_direct.cpp`, `gx_xbox_state.cpp`, transform/lighting/texgen: API GX original, atributos/transformacoes CPU e pipeline D3D. Sem renderer novo. Medicao anterior packet ~126 ms/frame; amostras position ~18, lighting ~28, texgen ~18, normal ~9 ms, aninhadas e aproximadas. Priorizar reuso seguro de dados/recursos; nao suprimir vertices/callbacks. |
| DrawPrimitiveUP | ADAPTAR | `profileDraw` usa UP por draw e nas passagens de early-Z/destination-alpha. Medicao draw_api ~32 ms/frame, incluindo esperas. XDK confirma UP -> DrawVerticesUP. Nao assumir que BeginVertices elimina custo: tambem exigiria copiar dados. Estudar VB nativo apos instrumentar lifetime/sincronizacao; conservar UP como referencia. |
| Vertex/index buffers | ADAPTAR | Caminho GX original acumula `Vertex` em vetores CPU. Triangulos evitam copia extra; quads/strips/fans expandem triangulos em `triangleVertices`. Nao ha VB/IB persistente neste caminho. Revisar topologia/index buffers sem alterar winding, ordem ou early-Z. A geometria deformada continua dinamica. |
| Display lists | MANTER A TRADUCAO / OTIMIZAR A TRADUCAO | `gx_display_list.inc` valida stream inteiro e executa segunda passagem, buscando arrays e transformando atributos novamente. Suporta listas de primitivas; opcodes de estado continuam rejeitados. Cache futuro deve considerar VAT/VCD, bytes da lista, arrays mutaveis e matrizes. Endereco sozinho seria incorreto. |
| Texture conversion/cache | ADAPTAR | `gx_texture_cache.inc`: cache por forma/conteudo real, busca prioriza mesma origem, 64 MiB/1024 entradas, sem eviction porque recursos emprestados sao retidos pelos bindings/probes. Na saturacao novos uploads seguem caminho anterior. `uploadTexture` ainda decodifica/aloca/upload em misses, copia snapshot por unidade e reaplica samplers. Primeira experiencia desta rodada: reuso da imagem ainda bound com comparacao integral dos pixels; paletizadas permanecem no caminho atual. |
| TEV/shaders | MANTER A TRADUCAO / OTIMIZAR A TRADUCAO | `gx_tev_state.inc`, `gx_tev.hlsl` e variantes implementam estado TEV, indiretos, fog, depth, alpha. Upload amplo de constantes e binds D3D por primitiva; early-Z pode desenhar por triangulo. Cache de constantes anterior piorou pipeline e esta rejeitado/preservado em diagnostics/experiments. Shader simplificado nao melhorou teste anterior. Manter fidelidade e medir dirty ranges/variantes antes de alterar. |
| EFB/XFB copies | MANTER A TRADUCAO / OTIMIZAR A TRADUCAO | `gx_copy_texture.inc` faz Resolve -> espera GPU -> untile regional -> filtro -> encode GX RAM -> posterior decode/upload. Recorte regional validado deve ficar. `xfb_xbox.cpp` conserva filtros/modos nativos. Pool experimental segue desligado. Readback e RAM original nao podem ser simplesmente removidos: jogo pode ler/mutar essa RAM. Proxima adaptacao exige acompanhar coerencia GPU/RAM e lifetime. |
| HSD render original | MANTER | `hsd_render_original.c`, geradores compat e originais ligados: manter ordem/callbacks, passes, animation e regras de estado. `hsd_scene.cpp` tambem tem preview custom com caches de meshes/archives e transformacao CPU; nao confundir preview com gameplay HSD original. Fidelidade integral nao certificada; sem gargalo isolado justificando reescrever HSD. Otimizar fronteira GX primeiro. |
| AX/DSP -> XAudio2 | MANTER A TRADUCAO / OTIMIZAR A TRADUCAO | `ax_pcm_consumer.c`, `ai_dma.inc`, efeitos AXFX e `audio_xbox.cpp`: PB/PCM/ADPCM/SRC/mixer CPU, buffers XAudio2/callbacks. Ha restricoes explicitas ITD/FIR, combinacoes mixer/SRC/enderecos e historico de DMA interrompido. Nao declarar audio completo. Prioridade aqui e compatibilidade e ruido/underflow; manter decoder e vetores de referencia. Nenhum gargalo de fps AX comprovado nesta rodada. |
| VI | MANTER A TRADUCAO | `vi_xbox.cpp`, `hsd_video_original.c`, `xfb_xbox.cpp`: retrace ligado a apresentacao, callbacks no render thread, staged configure/buffer/black, filtros AA/fields. Nao e interrupcao fisica VI emulada. Manter compatibilidade implementada e probes; nao alterar cadencia para aumentar FPS. |
| PAD | MANTER | `pad_xbox.cpp`, `pad_hsd.c`: XInput -> PADStatus, quatro slots, eixos, triggers/motors, amostragem/lock e HSD original. Nenhum gargalo isolado medido. Preservar inputs/timing e probes; cache de amostra nao deve ser ampliado por FPS. |
| CARD | MANTER | `card_filesystem.c`: container proprio com metadados, validacao/hash, temporario/backup e fila callbacks; nao e imagem raw GC/GCI. Manter formato persistente e probes. Persistencia escreve container: se houver stall de save, medir essa operacao separadamente. Nao ha evidencia de gargalo do render. |
| DVD/filesystem | MANTER | `dvd_filesystem.c`, manifest e loaders: arquivos extraidos, handles persistentes, reads/alinhamento/limites, fila prioridade/callbacks. Assincronia processada pelo pump nativo, diferente do hardware GC. Manter contrato e probes. Medir stalls de troca de asset antes de introduzir prefetch/thread. |
| Runtime/OS/memoria/ARAM | MANTER A TRADUCAO | Adaptadores arena/heap/pools, alarms/threads/cache, ARAM e bootstrap; preservar invariantes e tamanhos. Locks/async/timing precisam validacao especifica; nao otimizar mudando contrato OS. |
| Menus/CSS/SSS/Training, intro/THP | ADAPTAR | Existem UI/preview nativos e subconjuntos originais gerados/ligados; nem todas as telas sao codigo original completo. Preservar caminhos funcionais, videos/decoders, caches e probes. Original CSS/SSS/Training nao deve ser substituido por mocks. Sem reescrever nesta rodada. |
| Gameplay/fisica/AI/state machines | MANTER | Teste anterior logic ~3 ms/render ~342 ms, estados CPU amostrados iguais nos modos de isolamento. Evidencia nao sustenta alterar logica por FPS. Igualdade amostrada nao prova determinismo integral com GC. |

## Experiencia selecionada: reuso da textura bound

1. Atual: cada GXLoadTexObj procura cache global por conteudo, e misses podem converter/criar/upload mesmo se a unidade ja tem imagem igual nao retida no cache cheio.
2. Decisao: ADAPTAR a implementacao existente, sem eviction nem novo cache global.
3. Gargalo: upload/cache medido ~75 ms/frame; saturacao de 64 MiB documentada. Magnitude do caso de reuso bound ainda precisa ser medida.
4. Mudanca minima: flag `gx-texture-binding-reuse.flag` permite reutilizar loadedTextures[map] para imagem nao paletizada, descriptor de mesma forma/mip layout e snapshot identico. Sampler/LOD continuam atualizados. Comparacao byte a byte conserva mutacoes RAM. Nunca dar Release na mesma textura reutilizada. Caminho antigo permanece padrao ate validacao.
5. Validar: build Release/Compat, probes texture/mipmap/palette/invalidation/copy, match 180 antes/reuso/depois sem build concorrente, mesmos samples CPU e draws; capturas e match 900 se experiencia apresentar beneficio e corretude. Modo white-textures nao participa do reuso.

Tempos historicos sao CPU wall time no Xenia, com esperas; nao sao GPU timestamps nem ganho no Xbox real. Probes/caminhos de isolamento ficam preservados. Produto publicado nao sera atualizado apenas por compilacao.

## Observacoes de lifetime e estado

Nao aplicar cache D3D global sem considerar `CreateStateBlock`/`Apply` e codigo de UI/intro/probes que muda o device diretamente. `bindDirectPipeline` reestabelece estado por essa razao. Um dirty cache local pode mentir sobre o estado real apos esses caminhos.

Nao fazer eviction do cache atual sem contabilizar `loadedTextures[8]`, texturas mip com memoria fisica propria, referencias salvas por probes e comando GPU ainda em voo. A adaptacao de reuso selecionada nao altera ownership nem escreve em recurso GPU existente.

UP tambem aparece em UI/font/FPS, titulo/preview, intro e scaler XFB. Um quad por video/copy nao tem o mesmo peso de milhares de chamadas GX. Migrar todas as ocorrencias indiscriminadamente para VB nao e prioridade demonstrada.

`GXInvalidateVtxCache` chama `BlockUntilIdle`; os arrays GX sao lidos pela CPU. Ha uma possivel sincronizacao dispensavel, mas os usos e o lifetime dos uploads precisam ser confirmados antes de remover o barrier. Nao confundir invalidacao de atributos com coerencia das copias EFB.

Modo padrao do produto inclui atualmente `original-match.flag` e `hide-bot-render.flag`. As comparacoes desta rodada usam scratch sem esconder fighters, com tres execucoes da mesma XEX candidata; nao comparar diretamente esses numeros com o FPS mostrado pelo pacote em outro modo.

## Resultado desta rodada

Build Release/Compat compilou com MSBuild/XDK. Mudancas do runtime limitadas a `src/gx_texture_cache.inc`, `src/gx_direct.cpp` e `src/gx_profile.inc`. Novo caminho opt-in via `gx-texture-binding-reuse.flag`; padrao antigo e probes preservados. A XEX publicada nao foi substituida.

| Medida / 180 frames | Antigo antes | Reuso | Antigo depois |
|---|---:|---:|---:|
| Render ms/frame | 327.156 | 300.392 | 334.548 |
| Upload/cache ms/frame (aninhado no render) | 76.489 | 49.999 | 75.476 |
| Uploads efetivos | 1367 | 1056 | 1367 |
| Reusos da unidade bound | 0 | 3908 | 0 |
| Draws | 203241 | 203241 | 203241 |
| Copias | 345 | 345 | 345 |

Reducao render 8.18% a 10.21% contra duas referencias; drift entre referencias 2.26%. Reducao de uploads 22.75%. Total de pedidos de imagem (`uploads + cache_hits + binding_reuses`) continua 37415 em cada execucao. Samples CPU identicos. Uma execucao por configuracao, sem intervalos estatisticos; nao extrapolar para console, menus ou todos os stages.

Training/probes GPU existentes passaram: 45 casos de textura/8 unidades/paletas/mips/TLUT/invalidation, 32 copias GPU e demais verificacoes exigidas pelo script. Comparacao de capturas salva separadamente em logs/port-review-binding/regression.json. Limite da rodada: match de 180 frames e capturas internas nos frames 1/60; nao e validacao de combate de 900 frames.

O primeiro launch da regressao falhou antes do jogo por configuracao externa do Xenia cheia de NUL (60481 bytes). `verify-xenia.ps1` agora valida fonte antes de gravar config/rodar probes, aceita `-ConfigSource` e mantem testes silenciosos. A repeticao usa test-source.toml preservado de configuracao local valida. O arquivo externo do usuario nao foi modificado. Esse erro nao foi uma regressao do renderer.

Mantidos: logica original, HSD/callbacks, PAD/CARD/DVD, shaders/TEV, copies/VI e todos os probes/caminhos antigos. Adaptado: reuso seguro da textura bound e verificador de configuracao. Traducao mantida: GX/TEV/EFB/XFB/AX/OS, com limites expostos. Nenhum renderer generico novo, eviction insegura ou modo que esconda bots usado na comparacao.

Proximo gargalo prioritario: preparacao CPU dos vertices/display lists (~126 ms/frame no teste), seguida dos misses de texturas/copies dinamicas e lifetime do cache cheio. VB/IB pode reduzir submissao/copia/topologia, mas nao eliminara sozinho transformacoes, lighting e texgen CPU. Sem evidencias para otimizar AI/fisica por mudanca de logica. Antes de promover o caminho de reuso para pacote padrao, ampliar combate/capturas e testar console/memoria.

Reproduzir: compilar MSBuild /t:Build /p:Configuration=Release /p:Platform="Xbox 360" /p:DecompMode=Compat; executar diagnostics/run_binding_reuse.ps1, analyze_binding_reuse.py, run_binding_regression.ps1 e analyze_binding_regression.py. Scripts usam scratch, restauram sua XEX e nao publicam automaticamente. Preparar test-source.toml valido no diretorio de logs para regressao.

Resultado final da comparacao visual: zero pixels alterados nos frames 1 e 60 (640x480), samples CPU das duas execucoes com captura identicos. Sem regressao encontrada nos probes/testes executados; isso nao certifica todos os jogos, frames ou modos GX. Produto SHA256 95074C0C2CFC7226F2ABE2E88CBB4975411A1A6FD35054DA0FAE079CCE210738 preservado, scratch restaurado e nenhuma flag temporaria restante. Candidata testada SHA256 83FE1C890DBC8407ACEB0DE91E85A41FDB3E4BF7B87A8198B9664B841CFF9147.

Arquivos alterados nesta rodada: src/gx_direct.cpp, src/gx_texture_cache.inc, src/gx_profile.inc, verify-xenia.ps1. Arquivos criados: este documento e diagnostics/run_binding_reuse.ps1, diagnostics/analyze_binding_reuse.py, diagnostics/run_binding_regression.ps1, diagnostics/analyze_binding_regression.py. Resultados/logs/capturas/manifestos ficam em logs/port-review-binding; build intermediaria em build/Release/Compat/default.xex. Nao alterar pacote do usuario para testar a candidata: os scripts montam flags apenas no scratch. Ganho observado exige ligar a flag de reuso; build sem ela permanece no caminho antigo.
