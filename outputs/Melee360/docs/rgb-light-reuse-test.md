# Reutilização RGB da iluminação — 2026-10-04

Candidato implementado em applyLighting: para cada vértice e canal, guardar o fator calculado para cada luz no componente R e reutilizá-lo em G/B. Esses componentes compartilham o mesmo NativeChannel, posição e normal. Mantidos material, ambiente, cor de cada luz, acumulação, floor, clamp e arredondamento por componente. Alfa calcula seus próprios fatores. Não há cache entre vértices ou frames, nem redução de luzes ou modelos.

Candidato opt-in: gx-reuse-rgb-light.flag ao lado da XEX de diagnóstico. Sem essa flag, continua o cálculo anterior. As flags foram removidas e scratch restaurado à XEX publicada depois do teste. Não foi publicada nova build nem ativado o candidato por padrão.

## Desempenho

Mesma XEX, Xenia headless, 180 frames originais Mario CPU/Link CPU em Battlefield, ordem referência/candidato/referência:

| Execução | ms/frame |
|---|---:|
| Referência inicial | 355,289 |
| Candidato | 334,667 |
| Referência repetida | 337,485 |

Ganho observado: 5,80% contra a primeira referência e 0,835% contra a repetição. As referências variaram aproximadamente 5%; o grupo não permite afirmar ganho robusto. Não reivindicar 5,8% como melhoria garantida. Amostras CPU, desenhos, uploads e cópias foram idênticos. Desempenho do console e menus não foi medido. Não houve amostragem isolada do novo applyLighting nesse teste; o benchmark mediu o frame completo com profiling detalhado por vértice desligado.

## Regressões

Compilação Release/Compat passou. Candidato apresentou 900 frames originais, com lógica dos bots idêntica à referência. Sete capturas — internas e apresentadas — ficaram pixel a pixel iguais às capturas da build cache64. Training passou, exercitando probes de iluminação e demais estados GX. O áudio AX continua com bloqueio conhecido; esta mudança não o resolve.

Evidências: logs/gx-rgb-light-comparison.json, gx-rgb-light-render-verification.json, gx-rgb-light-image-verification.json, gx-rgb-light-match900.txt, gx-rgb-light-logic.txt, gx-rgb-light-training.txt. Scripts: diagnostics/compare_gx_rgb_light.py e verify_gx_rgb_light_render.py. A XEX experimental testada está em work/gx-rgb-light-tested.xex, identificada pelo manifesto; é necessário preservar seus assets e habilitar a flag para reproduzir o candidato.

Próximo passo: avaliar um benchmark mais estável/mais longo antes de adotar a reutilização. Outras oportunidades continuam na duplicação da transformação para espaço de câmera e na geração de coordenadas de textura. A base decomp original permanece intacta.
## Confirmação adicional

Foram executados mais três pares de referência/candidato, cada execução com 180 frames: 1080 frames adicionais na mesma XEX, sem profiling por vértice. Melhoras pareadas: 0,562%, 4,350% e 1,183%; média 2,030%, mediana 1,183%, redução agregada de tempo 2,048%. Todas as amostras CPU e contagens de desenho coincidiram.

Os três pares melhoraram, reforçando o indício inicial. Ainda são apenas três pares com ordem fixa referência/candidato, sem intervalo de confiança ou controle de todas as variações do host. O menor ganho é pequeno; não tratar o resultado como ganho garantido, nem extrapolar para menus ou console. A imagem publicada permanece cache64 e o candidato continua opt-in na imagem experimental testada.

Logs gx-rgb-confirm-{1,2,3}-{base,rgb}.txt; análise reproduzível por diagnostics/analyze_gx_rgb_confirmation.py, resultado logs/gx-rgb-confirm-analysis.json. Flags temporárias removidas; scratch restaurado à imagem publicada.
