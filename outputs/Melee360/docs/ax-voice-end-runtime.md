# Encerramento de vozes AX

O consumer completa o intervalo que comecou com a voz ativa, mesmo quando o endereco da fonte chega ao fim. A entrada passa a zero, o historico SRC continua avancando, e envelope, ganhos e depop completam o intervalo. Nos intervalos seguintes, uma voz parada nao avanca os acumuladores. O frame sem updates tambem passou a usar cinco intervalos de 32 amostras, como o frame com updates.

Antes, NONE interrompia o loop na ultima amostra, conservando valores residuais de ganho/depop. Linear e quatro taps podiam processar o resto do frame de 160 amostras quando a fronteira correta era o intervalo de 32. Nenhum stub foi adicionado; a base original foi preservada.

A referencia de comportamento e a copia local do Dolphin AXVoice.h: ProcessVoice verifica running na entrada, gera e mistura um intervalo inteiro, e atualiza os acumuladores de todas as amostras. A referencia moderna nao comprova equivalencia completa com o DSP antigo do Melee. O tratamento nativo de entrada apos o fim continua usando zeros e nao pretende emular todos os acessos do acelerador DSP.

## Testes

Seis casos encerram fontes PCM16 depois de 3 ou 7 amostras usando NONE, linear e quatro taps. Conferem endereco terminal, estado parado, fase, historico zerado, ganhos e envelope depois de exatamente 32 amostras, depop zero, ausencia de cauda depois do historico e estabilidade no frame seguinte. O marcador e obrigatorio no verificador Xenia, junto dos probes anteriores.

## Limites

Este incremento nao implementa FIR, ITD ou DPL2. Fins fracionarios de ADPCM/SRC, reinicio de uma voz terminada por updates dentro do mesmo frame, filas PB externas e comparacao auditiva abrangente ainda exigem testes separados. Nao houve teste no console ou promessa de ganho de FPS.

## Ruido dos diagnosticos

O usuario identificou ruido durante os testes. Os probes usam ondas sinteticas, extremos e mudancas abruptas de ganho. A saida da source voice AI agora fica em volume zero durante AIDMAProbe, AXPCMOutputProbe e AXContinuousProbe, com escopo C++ que restaura a politica de volume ao sair. Isso preserva SubmitSourceBuffer, SamplesPlayed, callbacks e comparacoes PCM; nao silencia o audio normal do jogo. AIInit verifica o volume zero e registra um marcador obrigatorio durante o teste. Nao foi demonstrado que esses sinais explicam todo ruido possivel do jogo.

## Build publicada

Release/Compat compilou. Training passou com todos os marcadores obrigatorios, incluindo diagnosticos sinteticos em volume zero. A build final apresentou 180 frames da partida original Mario/Link em Battlefield, sem bloqueio AX ou parada DMA. A XEX testada foi publicada apos backup da anterior; base original limpa. Evidencias: logs/ax-voice-end-build.txt, logs/ax-voice-end-training-runtime.log, logs/ax-voice-end-training-verification.txt, logs/ax-voice-end-match-verification.txt e logs/ax-voice-end-package-verification.json.
