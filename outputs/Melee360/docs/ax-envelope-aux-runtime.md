# Envelope AX e buses Aux/Surround — 2026-10-04

## Envelope e saturação

O volume do envelope GameCube é interpretado como s16, multiplicado pela amostra, deslocado por 15 e saturado. O delta atualiza o acumulador de 16 bits com wrap, sem clamp. O mixer aplica ganhos u16 por canal, satura cada contribuição para s16 antes de somar as vozes e registra o mesmo valor no depop. Isso corrige o antigo comportamento unsigned/clamp e a divergência entre a contribuição somada e o depop.

Os probes antigos usavam 0x8000 como ganho positivo unitário. Agora conferem sua interpretação negativa real. Os vetores de SRC continuam validando os mesmos resultados do filtro, com a transformação correta do envelope e da saída estéreo. Seis vetores específicos cobrem ganho positivo/negativo, cruzamento 0x7fff/0x8000, underflow em zero, deltas extremos, split 3+5 e saturação positiva/negativa por voz.

Fonte: [Dolphin AXVoice, ProcessVoice e MixAdd](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/Core/HW/DSPHLE/UCodes/AXVoice.h). Não implica equivalência de toda a execução DSP.

## Buses e callbacks

O consumidor interno aceita nove buffers s32: Main L/R/S, Aux A L/R/S e Aux B L/R/S. A máscara do AX antigo controla Aux A (1), Aux B (2), Surround (4) e rampas (8). Apenas canais ativos são processados; ganhos e depop persistem no PB. O wrapper de probes estéreo continua recusando uma solicitação de outros buses sem buffers; a partida usa o consumidor completo.

O frame nativo inclui o depop dos nove canais. Processa o anel CPU original antes de obter os buffers da próxima operação DSP, publica os buses Aux nos buffers de entrada e soma os retornos processados em Main L/R/S. Conserva a rotação original de três buffers e a latência de dois frames até o retorno da contribuição de uma voz.

O buffer S anterior é reaplicado de acordo com a sequência AXCL original: mode=0 soma em L/R; mode=1 soma em R e subtrai de L; mode=2/3 não faz esse fold. A saída AI continua estéreo, não um dispositivo 5.1. Mode=4/DPL2 continua explicitamente sem suporte completo.

Fontes originais: `AXCL.c` (__AXNextFrame), `AXOut.c` (__AXOutNewFrame), `AXAux.c`, `AXSPB.c` e `AXVPB.c` (AXSetVoiceMix). Referência adicional: [Dolphin AX.cpp, MixAUXSamples e SetMainLR/SetOppositeLR](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/Core/HW/DSPHLE/UCodes/AX.cpp).

## Adaptações registradas

O gerador `diagnostics/generate_portable_ax.py` corrige duas condições na cópia nativa, preservando o repositório base:

- __AXGetAuxBInput consulta o registro de callback B, permitindo B isolado. A versão copiada anteriormente consultava A.
- __AXAuxInit zera os três slots completos, evitando conteúdo antigo ao reinicializar o runtime.

As mudanças e o hash do original estão em `logs/portable-ax-provenance.json`. Não editar somente o arquivo gerado.

## Verificação e limites

O probe integrado usa voz, ARAM e setters/registros de callback originais. Confere B isolado, nove lanes, valores exatos antes/depois dos callbacks, latência de dois frames, feedback surround nos modos 0/1/2/3, unregister e reinicialização. Os callbacks de teste fazem transformações conhecidas para tornar o retorno observável; não substituem callbacks do jogo na partida.

Training passou com os novos marcadores obrigatórios, junto com PCM/ADPCM, SRC, rampas, contexto de streaming, depop, callbacks AX e consumo real AI. Evidência: `logs/ax-envelope-aux-training-runtime.log`.

Ainda faltam updates PB por milissegundo e sua sincronização com updateCounter/updateData dos setters, FIR, ITD, DPL2, revisão do SRC linear e do bookkeeping no fim de voz em subframes de 32 amostras. A ordem global CPU/DSP foi adaptada ao runtime nativo; não foi demonstrada equivalência temporal bit a bit com o hardware. Também faltam validação auditiva de todas as cenas e validação física desta build.

## Resultado da partida e pacote

A XEX final apresentou os 900 frames originais de Mario/Link em Battlefield. Os bots alternaram chão/ar, tiveram movimento, estados e inputs CPU diversos e chegaram a 56,03/47,64 de dano. A lógica e a execução HSD/GX passaram; não foram feitas capturas comparativas nesta revisão.

O AX permaneceu ativo, com 36.000 blocos observados e 5.759.840 amostras consumidas por canal no XAudio2. O verificador confirmou consumo crescente e o clock de 160 amostras por callback, sem parada de DMA. Isso não prova que todas as cenas ou os efeitos sonoros estejam auditivamente corretos.

Evidências: `logs/ax-envelope-aux-match-verification.txt`, `logs/ax-envelope-aux-audio-verification.json` e `logs/ax-envelope-aux-logic-verification.json`. Base original limpa; pacote atualizado somente após os testes, com backup e hashes em `logs/ax-envelope-aux-package-verification.json`.
