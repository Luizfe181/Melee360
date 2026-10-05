# SRC linear persistente no AX

O consumer nativo passa a usar o histórico de quatro amostras do PB também no SRC linear. Antes fazia leitura antecipada da amostra atual e seguinte, ignorando o histórico inicial e produzindo outra latência. Agora avança a fase antes da saída, consome as amostras inteiras e interpola as duas primeiras posições do histórico ordenado. O histórico e a fase persistem entre chamadas. Nenhum stub foi acrescentado e a base original permanece preservada.

Referência de comportamento: Dolphin `AXVoice.h`, função `ResampleAudio`, cópia local em `work/dolphin-reference/AXVoice.h`, revisão de referência eb236466c4f0ec8bef619add0972353d3996fe6c. A implementação nativa usa o histórico ordenado; os vetores são gerados por um modelo separado em Python. Isso não comprova equivalência bit a bit com todas as revisões do DSP original.

## Verificação

Seis vetores fixos cobrem razão zero com fase zero/fracionária, 0,5, 1, 1,5 e 4; histórico inicial não nulo; sinal alternado/extremos; fase final; endereço final; e execução dividida em 13 + 19 amostras. Também foram atualizadas as expectativas do probe antigo de interpolação, explicitando seu histórico inicial. O teste contínuo ADPCM/SRC manteve reprodução real via AI/XAudio2.

Release/Compat compilou e Training passou, incluindo os probes anteriores. Evidências: `logs/ax-linear-build.txt`, `logs/ax-linear-reference-vectors.json`, `logs/ax-linear-training-runtime.log` e `logs/ax-linear-training-verification.txt`.

## Limites

FIR, ITD, DPL2, importação de filas PB externas e bookkeeping de fim de voz continuam pendentes. O encerramento de uma voz dentro de um intervalo ainda exige uma revisão separada do processamento de zeros e acumuladores até sua fronteira. Esta mudança corrige o caminho linear; não promete ganho de FPS nem validação auditiva completa ou teste no console.

## Build publicada

A regressao original Mario/Link em Battlefield apresentou 180 frames sem bloqueio AX ou parada de DMA. A XEX testada foi publicada, com backup da anterior. Base original limpa. Evidencias: logs/ax-linear-match-verification.txt e logs/ax-linear-package-verification.json.
