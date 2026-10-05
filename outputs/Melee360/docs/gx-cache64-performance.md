# Cache GX: segunda medição — 2026-10-04

Esta revisão prioriza entradas da mesma origem na busca do cache e aumenta seu orçamento contabilizado de 32 para 64 MiB, com limite de 1024 entradas. A origem apenas determina a ordem da busca: os bytes da imagem e da paleta continuam sendo comparados. Existe busca alternativa por conteúdo; mudanças nas texturas continuam visíveis. Recursos ficam retidos até o fechamento GX, preservando referências emprestadas. Quando o cache enche, o caminho de upload anterior continua funcionando.

O orçamento conta imagens GPU estimadas/alocadas, cópias dos pixels e paletas. Não conta overhead de objetos/vetores ou padding de texturas lineares. O aumento de memória precisa de validação no console real.

## Medição

Mesma XEX, Xenia headless, Mario CPU contra Link CPU em Battlefield, 180 frames, sem capturas. Ordem: configuração anterior, nova configuração, configuração anterior novamente. As opções de diagnóstico `gx-content-only-cache.flag`, `gx-cache-small-limit.flag` e `gx-cache-32mb.flag` reproduzem a configuração anterior; a configuração nova não precisa dessas flags.

| Medida | Anterior | Nova | Anterior repetida |
|---|---:|---:|---:|
| Tempo por frame (ms) | 342,889 | 335,714 | 341,580 |
| Uploads | 1938 | 1367 | 1938 |
| Entradas retidas | 237 | 352 | 237 |
| Bytes contabilizados | 33553782 | 67108758 | 33553782 |

Redução de tempo: 2,09% contra a primeira execução e 1,72% contra a repetição. Uploads caíram 29,46%. O tempo de upload medido aumentou de 70,809 para 74,116 ms/frame; menos chamadas não garantem menor tempo. O ganho total é pequeno, sem análise estatística além dessa repetição. Amostras CPU e 203241 chamadas de desenho foram idênticas. FPS estimado permanece perto de 3 nesse teste: não representa desempenho suficiente nem uma medição de menus ou console.

Os contadores demonstraram que o cache anterior já esgotava os 32 MiB antes do limite de entradas. Aumentar apenas o número de entradas não resolveu esse limite.

## Experimento rejeitado

Um cache de constantes de shader reduziu escritas, mas elevou o custo CPU do pipeline de aproximadamente 8 para 24 ms/frame, sem ganho total. Foi removido do caminho ativo. A implementação experimental está em `diagnostics/experiments/gx_constant_cache-rejected.inc`. O helper ativo apenas encaminha as chamadas originais e conta escritas quando o profiling está habilitado.

## Limites

Nenhuma substituição de gameplay, geometria ou função ausente por stub foi feita. A base original permanece preservada. Materiais completos, desempenho e áudio AX da partida continuam incompletos; o runtime ainda registra interrupção DMA por modo de voz/ARAM não suportado. Os números anteriores de 26,67% e 94,82% pertencem à primeira revisão de cache, documentada separadamente; não são o ganho deste incremento.

Resultados de regressão e identificação do pacote: `logs/gx-cache64-package-verification.json`. Medições reproduzíveis: `diagnostics/compare_gx_cache64.py` e `logs/gx-cache64-comparison.json`.

Regressões finais: 900 frames apresentados, amostras CPU preservadas, sete capturas pixel a pixel idênticas à revisão anterior; Training e menus passaram. SHA256 da XEX publicada: 1E0458D94556D1F4B2FAE880929BEBAE29039A775F44B89670641466D4E238A6.
