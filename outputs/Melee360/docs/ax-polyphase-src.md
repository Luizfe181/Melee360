# AX SRC de quatro taps — 2026-10-04

O consumidor nativo agora processa `srcSelect=0` e `coefSelect=0/1/2`, selecionados pelas funções originais AX_SRC_TYPE_4TAP_8K/12K/16K. Não há fallback para linear.

## Implementação

Antes de produzir uma amostra de saída, acumula a razão 16.16, consome as amostras inteiras necessárias via PCM/ADPCM em ARAM e desloca o histórico de quatro amostras. A fração seleciona uma das 128 fases do banco; quatro produtos signed são acumulados em 64 bits, deslocados por 15 e saturados para s16. Fase e histórico ficam no PB para a próxima chamada. O caminho mantém as rampas estéreo, envelope e callbacks existentes.

Os coeficientes são a tabela livre do Dolphin, commit `eb236466c4f0ec8bef619add0972353d3996fe6c`, SHA256 `d7741279c2e8ec5c5fb318f8fbdd6de6bf583520d288e836a5383233a4238179`. São aproximações da ROM DSP, **não equivalência bit a bit com Nintendo**. Binário, atribuição e licença estão em `third_party/dolphin`; a tabela convertida está em `src/ax_src_coefficients.inc`.

Referências: [Dolphin AXVoice.h](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/Core/HW/DSPHLE/UCodes/AXVoice.h), [leitura dos coeficientes AX.cpp](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/Core/HW/DSPHLE/UCodes/AX.cpp), [descrição da ROM livre](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/docs/DSP/free_dsp_rom/dsp_rom_readme.txt).

## Verificação

`diagnostics/generate_ax_src.py` verifica o hash do binário, lê palavras big-endian e gera a tabela e 15 vetores fixos. Seu modelo usa uma fila de amostras, separada da implementação C. Os testes nativos usam AXAcquireVoice, AXSetVoiceAddr, AXSetVoiceSrc, AXSetVoiceSrcType e ARAM reais.

Cada banco é testado com razões 0, 0,5, 1, 1,5 e 4, fases iniciais variadas, sinal alternado/extremo, saturação e bloco dividido 13+19 amostras. Compara saída estéreo, endereço final, fase e todas as quatro amostras do histórico. Modelo de referência e dados congelados não são uma execução de DSP LLE independente; validação bit-exata com hardware permanece pendente.

O teste contínuo alterna linear e quatro taps com ADPCM em loop, confere a saída de quatro taps (127 nos dois canais neste vetor) e consumo AI/XAudio2. Um código SRC inválido, 3, continua parando DMA explicitamente. O verificador requer os novos marcadores; a falha esperada não é mais um modo válido de quatro taps.

## Limites

Este incremento completa o cálculo do filtro com a tabela livre nos casos testados. Não completa todo o AX: Aux/Surround, updates de PB por milissegundo, FIR, ITD, streaming/contexto de loop e semântica do envelope continuam pendentes. O SRC linear anterior ainda precisa de revisão de alinhamento/histórico. Razões superiores a 4 e seletores desconhecidos continuam recusados. Não há validação física nesta revisão.

## Resultados na XEX publicada

Release/Compat compilou. Training passou com os novos marcadores obrigatórios: vetores, rampas, PCM/ADPCM, SRC linear/quatro taps, callbacks, shutdown e consumo real AI. Logs preservados em `logs/ax-polyphase-training-runtime.log` e `logs/ax-polyphase-training-verification.txt`.

Mario/Link em Battlefield apresentou 180 frames. O diagnóstico AX deixou de parar pela ausência de SRC=0; posteriormente parou na voz 62 com ADPCM, SRC=0 e endereço corrente `0xc23d42` maior que o fim `0xc13d3f`. ITD, FIR, updates, type e mixer estavam zerados. Esse estado impede leitura no consumidor; origem precisa ser rastreada nos setters, loop e callbacks do PB. Não foi corrigido com clamp, silêncio ou descarte da voz. O teste de render/CPU passar não significa áudio completo da partida.

Evidência: `logs/ax-polyphase-match-verification.txt`. Hash, backup e ausência de flags no pacote: `logs/ax-polyphase-package-verification.json`. Base original permaneceu limpa.

**Correção da interpretação em revisão posterior:** current > end é válido durante a troca de buffers de streaming HSD. Era uma checagem incorreta do consumidor nativo, não evidência de corrupção de endereço. [Correção e validação](ax-streaming-runtime.md).
