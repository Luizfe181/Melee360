# AX updates PB por milissegundo — 2026-10-04

## Caminho implementado

As filas criadas por AXSetVoiceUpdateWrite e AXSetVoiceUpdateIncrement agora são aplicadas nos cinco intervalos de 32 amostras do frame de 5 ms/32 kHz. Uma voz inicialmente parada pode ser ligada por uma alteração posterior; mudanças em volume, mixer, estado e demais palavras válidas do PB são aplicadas antes de consumir o intervalo correspondente.

O consumidor de frame confere a soma das contagens, o tamanho da fila e todos os offsets antes de alterar o PB. Usa uma cópia local dos dados/contagens para que uma palavra de metadata modificada não faça a leitura sair da fila. Pares repetidos preservam sua ordem. Após sucesso, limpa contagens e contador, reinicia updateMS e aponta updateWrite para o início do buffer, evitando replay e permitindo novas filas no callback seguinte.

O caminho sem alterações mantém o consumo anterior de 160 amostras. O helper de consumo estéreo isolado recusa filas pendentes, pois não é proprietário do relógio dos cinco intervalos.

## Adaptação do setter

O corpo original de AXSetVoiceUpdateWrite disponível no decomp armazena os pares no buffer e incrementa updateCounter, mas não registra a quantidade por updateMS. A cópia nativa registra essa contagem em pb.update.updNum e valida índice de milissegundo/offset. É uma adaptação explícita da ponte CPU/runtime, não uma implementação do protocolo de mailbox DSP.

O original permanece intacto. A mudança está no gerador `diagnostics/generate_portable_ax.py`, com hash do corpo original, hash adaptado e motivo em `logs/portable-ax-provenance.json`.

Fontes: `work/melee-base/libs/dolphin/src/dolphin/ax/AXVPB.c`, setters e reset em __AXSyncPBs; [Dolphin AX.cpp, ProcessPBList](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/Core/HW/DSPHLE/UCodes/AX.cpp) e [AXVoice, ApplyUpdatesForMs](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/Core/HW/DSPHLE/UCodes/AXVoice.h).

## Verificação

O probe usa voz, ARAM e setters originais, não reproduz apenas a estrutura da fila:

- Intervalo 0 em silêncio; início no intervalo 1, alteração do envelope no 2, ganho esquerdo no 3 e parada no 4. Compara as 160 amostras estéreo.
- Dois writes do mesmo volume no mesmo intervalo e uma alteração no último intervalo, conferindo ordem e fronteira de 4 ms.
- Fila completa de 64 pares/128 palavras, conferindo resultado e reutilização após reset.
- Offset inválido rejeitado antes de alterar o volume ou escrever áudio.
- Callback AX real cria cinco intervalos de ganho a cada frame; o consumer e o driver AI/XAudio2 conferem a saída {64,32,0,-128,64}, reset e playback contínuo.

Training passou com os marcadores obrigatórios novos e anteriores. Evidência: `logs/ax-pb-updates-training-runtime.log` e `logs/ax-pb-updates-training-verification.txt`.

## Limites

O suporte cobre filas internas produzidas pelos setters nativos. Não importa arbitrariamente dados de update.dataHi/Lo de outro PB/DSP externo. Contagens são fixadas no início do frame; alterar a própria metadata durante a fila não cria uma agenda dinâmica. Um update que ativa SRC/FIR/ITD/modo ainda não suportado continua falhando explicitamente quando consumido.

FIR, ITD, DPL2, revisão do SRC linear e bookkeeping do fim de voz ainda precisam de trabalho. Não há prova de equivalência temporal bit a bit nem validação física desta revisão. Os probes e a regressão não demonstram suporte de todos os casos do AX.

## Build publicada

Release/Compat compilou. A XEX final passou em Training com os dois novos marcadores obrigatórios, teste da fila e scheduling em callback/AI reais. A regressão original Mario/Link em Battlefield apresentou 180 frames com movimento e dano 9/11, sem bloqueio de voz ou parada de DMA, e com consumo XAudio2 crescente. Nesta revisão foram testados 180 frames de partida, não os 900 da build anterior.

Evidência de regressão: `logs/ax-pb-updates-match-verification.txt`. Hashes, backup, contadores e flags: `logs/ax-pb-updates-package-verification.json`. Base original limpa e pacote publicado após os testes.
