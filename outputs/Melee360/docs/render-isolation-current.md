# Diagnostico atual da renderizacao

Mesma XEX `95074C0C2CFC7226F2ABE2E88CBB4975411A1A6FD35054DA0FAE079CCE210738`, dez execucoes de 180 frames de Mario/Link CPU em Battlefield no Xenia. Referencias antes e depois; pacote do usuario preservado.

| Teste | Logica ms | Render ms | Total ms | Reducao render contra referencias |
|---|---:|---:|---:|---:|
| baseline-before | 3.275 | 345.548 | 349.157 | -1.0% a 0.0% |
| detail-visible | 3.481 | 341.067 | 344.875 | 0.4% a 1.3% |
| vertex-phase0 | 3.197 | 342.151 | 345.675 | 0.0% a 1.0% |
| vertex-phase31 | 3.274 | 341.957 | 345.568 | 0.1% a 1.0% |
| detail-hidden | 3.135 | 203.818 | 207.287 | 40.5% a 41.0% |
| no-draw | 3.194 | 230.003 | 233.567 | 32.8% a 33.4% |
| simple-shader | 3.305 | 348.680 | 352.317 | -1.9% a -0.9% |
| white-textures | 3.122 | 266.188 | 269.642 | 22.2% a 23.0% |
| no-copy | 3.103 | 234.006 | 237.439 | 31.6% a 32.3% |
| baseline-after | 3.310 | 342.295 | 345.937 | 0.0% a 0.9% |

Variacao entre referencias: -0.9% no render. Estados CPU amostrados coincidiram em todas as execucoes.

## Detalhamento com desenho normal

- frames: 180.0
- packet_ms: 125.556
- submit_ms: 49.706
- draw_api_ms: 31.56
- idle_ms: 14.548
- filter_ms: 10.263
- vertices: 4586837.0
- idle_calls: 345.0

## Estimativas por vertice

- position: 17.763 a 18.397 ms/frame (duas fases de amostragem).
- lighting: 28.147 a 28.555 ms/frame (duas fases de amostragem).
- texgen: 17.449 a 17.801 ms/frame (duas fases de amostragem).
- normal: 8.897 a 8.992 ms/frame (duas fases de amostragem).

## Interpretacao e limites

CPU wall time in Xenia including waits, not GPU timestamps. Nested timers cannot be added indiscriminately. Vertex sampling uses 1/64 calls with two offsets and includes timing overhead. Counterfactual modes alter output, and their effects are not additive. CPU log equality checks sampled states, not full deterministic equivalence.

packet inclui montagem GX original, atributos e transformacoes. submit inclui pipeline e chamadas de desenho; draw_api e parte de submit. upload inclui cache/decodificacao/alocacao/sampler. copy inclui readback e filtro; idle e filtro sao subconjuntos. simple-shader conserva preparacao TEV e troca o pixel shader; no-draw remove DrawPrimitiveUP, conservando montagem; white-textures ignora cache/decodificacao e altera pixels/cache; no-copy substitui a imagem copiada por cor neutra. Nenhum e uma otimizacao publicavel como esta.

O custo de esconder Fighters inclui todos os trabalhos de seus callbacks graficos. A logica e amostrada separadamente. Nao foram medidos tempos internos GPU ou hardware Xbox 360.
