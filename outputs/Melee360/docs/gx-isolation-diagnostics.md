# Diagnósticos de isolamento GX — 2026-10-04

Seis testes de 180 frames, 1080 frames totais, mesma XEX de diagnóstico, Xenia headless, Mario CPU/Link CPU em Battlefield. Referência antes e depois; quatro alterações isoladas. Compilação Release/Compat e compilação XDK do shader de cor simples passaram.

Os modos são experimentos que deliberadamente alteram a imagem. Não são implementações substitutas de funções ausentes nem otimizações adotadas. Só atuam com profiling habilitado e suas flags específicas. Não foram publicados. Todos apresentaram amostras CPU originais idênticas e 4586837 vértices montados. Contador de pacotes GX continuou 203241; no modo sem desenho esse contador NÃO significa desenhos enviados à GPU.

| Modo | Render ms/frame | Total ms/frame | Uploads | Cópias |
|---|---:|---:|---:|---:|
| Referência | 346,859 | 350,044 | 1367 | 345 |
| Shader simples | 340,727 | 343,792 | 1367 | 345 |
| Sem DrawPrimitiveUP | 237,386 | 240,499 | 161 | 345 |
| Texturas brancas | 273,361 | 276,422 | 0 | 345 |
| Cópias neutras | 238,002 | 241,216 | 161 | 345 |
| Referência repetida | 353,010 | 356,122 | 1367 | 345 |

Cópias é contador de pedidos. No modo cópias neutras, esses pedidos não fazem readback/filter, mas retornam pixels cinza para o encoder GX; a lógica original continua recebendo uma imagem de tamanho válido. Não usar como saída visual final. Texturas brancas mantém descritores, estados de sampler e cópias auxiliares, substituindo as imagens GPU por uma textura 1x1, sem decodificação/alocação/upload normal. Sem desenho ainda executa pipeline e montagem, mas omite DrawPrimitiveUP. Shader simples mantém shader de vértices e geometria, substituindo o fragmento TEV/texturas/fog/alpha-test/packing por cor do vértice; a cobertura/efeitos ficam diferentes.

## O que a comparação indica

Shader simples melhorou o total em 1,79% contra a primeira referência e 3,46% contra a repetição. A diferença é pequena comparada aos outros modos: não há evidência aqui de que o TEV seja sozinho a causa dominante. Não extrapolar para console nem afirmar tempo interno GPU; os temporizadores medem CPU wall time, incluindo bloqueios.

Texturas brancas reduziu total em aproximadamente 21–22%. Tempo do caminho upload caiu de 73,878 para 1,078 ms/frame. Esse experimento remove também trabalho de busca/decodificação/alocação e reduz o custo de amostragem GPU, portanto não é medição isolada de transferência GPU.

Cópias neutras reduziu total em aproximadamente 31–32%. Tempo de cópia caiu de 37,685 para 0,601 ms/frame, e upload de 73,878 para 7,954. Como o conteúdo retornado é constante, o cache fica mais eficaz. É forte evidência sobre o caminho combinado de cópia e atualização de texturas, não sobre apenas BlockUntilIdle.

Sem desenho também reduziu uploads para 161, porque o conteúdo do framebuffer muda. Seu tempo de cópia e espera, inclusive, subiu. A melhora de aproximadamente 31–32% não pode ser atribuída inteiramente a rasterização ou shader. Esses acoplamentos impedem somar os ganhos dos modos.

## Caminho prioritário

O código atual faz Resolve da GPU, BlockUntilIdle, LockRect, untile, filtro CPU, encode para formato GX em RAM e posterior decode/upload na carga de textura. Esse percurso GPU→CPU→GPU custa processamento e invalida reutilização quando a imagem muda. Prioridade: registrar formatos, dimensões e consumidores reais das cópias; estudar manter o resultado em textura GPU nativa e sincronizar a representação RAM somente quando exigida pelos consumidores. Preservar filtro, canais, quantização, mutações em RAM, clear e vida dos recursos. Isso requer implementação e validação própria; os dados neutros destes diagnósticos não servem como solução.

Montagem CPU ainda ficou perto de 125–128 ms/frame mesmo nesses modos. Logo, cópias/texturas são um problema importante, mas sua correção isolada não demonstra que chegaríamos a 60 FPS. Ainda existe trabalho no caminho de montagem/emissão/transformação de vértices.

## Evidências e reprodução

Dados completos: logs/gx-isolation-analysis.json, gerado por diagnostics/analyze_gx_isolation.py. Logs gx-isolation-{baseline,simple-shader,no-draw,white-textures,no-copy,baseline-repeat}.txt. Build e shader: gx-isolation-build.txt e gx-isolation-shader-build.txt. Imagem de diagnóstico: work/gx-isolation-tested.xex, hash em logs/gx-isolation-image-verification.json.

Ativar um único modo colocando a flag correspondente ao lado da XEX de diagnóstico: gx-diag-simple-shader.flag, gx-diag-no-draw.flag, gx-diag-white-textures.flag ou gx-diag-no-copy.flag. Executar verify-original-bootstrap.ps1 -Match -Performance -Detailed -TimeoutSeconds 300. Remover a flag depois. Esses modos só entram com o profiler habilitado; sem flags usam o caminho normal. Não combinar modos para reproduzir as medições acima.

Sem comparação visual de fidelidade ou regressão de 900 frames dos modos, pois as imagens são intencionalmente alteradas e a finalidade é diagnóstico. Não houve medição no hardware físico. O erro AX/ARAM conhecido continua. Todas as flags temporárias foram removidas, scratch restaurado com a imagem publicada e base decomp original preservada.
