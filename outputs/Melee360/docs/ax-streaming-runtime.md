# AX streaming e contexto ADPCM — 2026-10-04

## Causa da parada anterior

O diagnóstico anterior mostrou current > end e foi descrito como endereço inválido. Essa interpretação estava errada para o streaming HSD. `HSD_SynthPStreamMasterClockCallback` atualiza o fim quando detecta a entrada em outro buffer do anel; o loop pode saltar para esse buffer antes da atualização. End é um gatilho de término, não o limite físico de leitura.

No consumidor nativo, `if (current > end) return 0` interrompia uma transição válida. A correção remove essa comparação e mantém a condição de término por igualdade e as checagens reais de leitura dentro da ARAM em `Melee360ARAMReadPCM/Byte`. Não há clamp, descarte da voz nem substituição por silêncio para ocultar a falha.

Referências: `work/melee-base/src/sysdolphin/baselib/synth.c`, callbacks PStream; [Dolphin DSPAccelerator](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/Core/DSP/DSPAccelerator.cpp), condições de término e observações de end/current.

## Segundo incremento

`AXSetVoiceType(voice, 1)` agora permite o consumo de uma voz streaming. Na fronteira do loop ADPCM, aplica o pred_scale do próximo bloco e conserva yn1/yn2; para type=0 restaura o histórico do loop como antes. Tipos superiores a 1 continuam recusados. Não altera o layout AXPB do SDK antigo nem escreve contadores do layout DSP de versões posteriores em campos reservados.

Referência: [Dolphin AXVoice, OnSampleReadEndException](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/Core/HW/DSPHLE/UCodes/AXVoice.h).

## Testes específicos

- Loop PCM para outra região de ARAM acima do fim antigo; leitura de oito amostras atravessa a fronteira, endereço final conferido. Setter original muda o fim, e desligar o loop termina exatamente no novo limite.
- Endereço fora da ARAM continua falhando; current > end dentro da ARAM deixa de ser falso positivo.
- ADPCM com coeficiente 1024 e yn1 inicial 100: o loop reiniciado retorna 51; o loop streaming continua o histórico e retorna -1 após a fronteira. Confere o vetor completo de 15 amostras, yn1/yn2 e bloco dividido 14+1.
- Tipo inválido continua falhando, sem fallback.
- Os testes anteriores de quatro taps, rampas, PCM, ADPCM, callbacks, depop e DMA permanecem exigidos.

O driver agora registra periodicamente frames AX e SamplesPlayed do XAudio2. Isso permite distinguir playback contínuo de uma inicialização que apenas não registrou erro. Contadores não são validação auditiva de toda a mixagem.

## Próximas dependências conhecidas

Aux/Surround e seus retornos ao mixer, updates PB por milissegundo, FIR, ITD, envelope signed/wrap e revisão do alinhamento do SRC linear ainda estão pendentes. Uma função compilada não demonstra suporte completo. Os casos especiais de endereço final ADPCM alinhado ao header também precisam de vetores dedicados.

O streaming original observado usa type=0 e gerencia seu contexto via setters/callbacks HSD. A nova semântica type=1 foi validada por probe, não apresentada como requisito daquele bloqueio específico.

## Resultado final

Release/Compat compilou. Training passou, incluindo os novos marcadores obrigatórios de streaming e contexto, além dos probes anteriores. Logs: `logs/ax-stream-context-training-runtime.log` e `logs/ax-stream-context-training-verification.txt`.

A XEX final apresentou 900 frames Mario/Link em Battlefield com desenho HSD/GX original. Ambos os bots tiveram 15 posições distintas e 12 estados observados, alternaram chão/ar e chegaram a dano 56,03/47,64. Não foram capturadas imagens comparativas neste teste; ele valida execução, não equivalência visual completa.

O áudio permaneceu ativo sem `AX voice blocked` ou parada de DMA. `diagnostics/verify_ax_streaming.py` confirmou consumo crescente e coerência do clock de 160 amostras por callback. Evidências: `logs/ax-stream-context-match-verification.txt`, `logs/ax-stream-context-audio-verification.json` e `logs/ax-stream-context-logic-verification.json`.

Nenhum novo bloqueio de execução foi observado nesses 900 frames. As dependências pendentes acima são limites conhecidos de cobertura, não falhas inventadas desse teste. Próxima prioridade funcional: envelope signed/wrap e mixagem Aux/Surround com callbacks e retorno real. Base original limpa, XEX publicada com backup: `logs/ax-stream-context-package-verification.json`.
