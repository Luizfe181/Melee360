# Amostragem de custo dos vértices — 2026-10-04

Quatro execuções na mesma XEX: referência, amostragem com deslocamento 0, amostragem com deslocamento 31 e referência repetida. Cada execução apresentou 180 frames de Mario CPU/Link CPU em Battlefield no Xenia headless. Compilação Release/Compat passou. Nenhuma mudança de lógica, geometria, shader ou sincronização GPU foi feita. A base original permanece preservada.

Amostragem determinística: uma chamada em cada 64 de cada rotina, incluindo chamadas que retornam cedo. Cada categoria conta todas as chamadas; tempo estimado é o tempo acumulado nas amostras multiplicado pela razão chamadas/amostras e dividido pelos frames. Os deslocamentos diferentes reduzem o risco de escolher sempre o mesmo subconjunto, mas não equivalem a amostragem aleatória nem fornecem intervalo estatístico.

| Categoria | Estimativa fase 0 (ms/frame) | Fase 31 | Escopo |
|---|---:|---:|---|
| Posição | 18,508 | 17,948 | Transformações para clip e espaço de câmera |
| Iluminação | 29,156 | 27,702 | applyLighting completo, inclusive retornos sem trabalho |
| Coordenadas de textura | 20,004 | 18,282 | generateTexcoords completo |
| Normal | 8,796 | 9,045 | Primeira normal, cópia, decisão de transformar e normalização |

Em cada execução: 4586837 chamadas de posição, iluminação e texgen; 2971348 de normal. Cada fase mediu aproximadamente 71670 chamadas por categoria de posição/iluminação/texgen e 46428 de normal. Essas estimativas incluem overhead do temporizador; não houve subtração/calibração. Valores arredondados servem para orientar investigação, não para atribuir milissegundos exatos.

O tempo de montagem completo foi 129,580 ms/frame na fase 0 e 126,451 na fase 31. Nem todo esse intervalo está coberto pelas quatro categorias: há emissão/decodificação de atributos, validações, inicialização de vértices, cópias e chamadas originais. Não atribuir o saldo inteiro a um único sistema.

## Conclusão de investigação

Iluminação é a maior categoria medida dentro desse grupo nas duas fases. O código repete direção, distância e fatores de luz nos componentes RGB que usam o mesmo controle. A posição em espaço de câmera também aparece em mais de um caminho. São candidatos a reutilização local de resultados, sem descartar luzes, vértices ou materiais. Ainda precisam de implementação, benchmark repetido e validação visual antes de adoção.

Upload de textura permanece relevante, perto de 75 ms/frame nesses testes. Não foi demonstrada dependência ausente que explique o desempenho. O erro AX/ARAM conhecido continua separado. Estas medições CPU não fornecem tempo interno de execução GPU ou custo isolado do shader TEV.

## Verificação e reprodução

Amostras CPU e contagens de desenho foram idênticas nos quatro testes. Não houve regressão de 900 frames nem comparação visual desta instrumentação; nenhuma nova XEX foi publicada. Referências e tempos completos: logs/gx-vertex-samples-analysis.json. O script diagnostics/analyze_gx_vertex_samples.py reproduz a análise. Logs: gx-vertex-baseline.txt, gx-vertex-phase0.txt, gx-vertex-phase31.txt, gx-vertex-baseline-repeat.txt. Build: gx-vertex-samples-build.txt.

Na XEX de diagnóstico, gx-profile-vertex.flag ativa amostragem; gx-profile-vertex-alt.flag seleciona deslocamento 31. Sem a segunda flag, usa 0. As flags devem estar ao lado da XEX antes de iniciar `verify-original-bootstrap.ps1 -Match -Performance -Detailed -TimeoutSeconds 300`; remover ambas ao terminar. Elas não são necessárias para jogar. A rotina de medição só coleta tempos com profiling habilitado.

A imagem instrumentada testada está em work/gx-vertex-samples-tested.xex, identificada por logs/gx-vertex-samples-image-verification.json. Depois dos testes, flags temporárias foram removidas e scratch restaurado com a imagem publicada cache64; essa build publicada continua inalterada.
