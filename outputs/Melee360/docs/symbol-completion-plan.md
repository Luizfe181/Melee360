# Conclusão funcional dos símbolos — 2026-10-04

O foco passa de otimização para comportamento completo e verificável. Uma definição no linker prova presença, não equivalência com GameCube. Não adicionar funções vazias para diminuir contagens.

## Escopo e evidência

- Inventário original GALE01: 35.289 entradas, incluindo funções, objetos e labels. Gameplay tem 17.273 funções; menus 431; HSD 1.078; SDK 837; runtime 208. Essa classificação não mede cobertura do port.
- A auditoria selecionada de criação de Mario/Link com heap HSD liga com zero pendências. Isso não cobre todos os caminhos do jogo.
- Inventário dos headers públicos GX reexecutado nesta revisão: 250 APIs, 116 definições encontradas nos objetos Release/Compat, 2 inline originais, 132 sem definição nesses objetos. Lista individual: [inventário GX](gx-api-inventory.md); dados: `logs/gx-api-inventory.json`. Essas APIs podem não ser requisitadas pelo caminho hoje ligado.
- Não há auditoria semântica individual de todas as funções originais. Não atribuir porcentagem de conclusão a essas contagens.

## Fila inicial de conclusão

| Grupo / símbolos | Situação conhecida | Critério para avançar |
| --- | --- | --- |
| AXSetVoiceMix / Melee360AXConsumePCM | Setter original; consumidor agora aceita bit 3 e aplica rampas L/R por amostra, com acumuladores de 16 bits | Vetores de saída, deltas de ambos os sinais, continuidade e wrap no Xenia |
| Melee360AXConsumePCM: SRC | PCM8/16 e ADPCM, NONE/linear; quatro taps agora implementado com a tabela livre Dolphin | Três bancos e 15 vetores passaram; ainda revisar alinhamento/histórico linear e equivalência com ROM física |
| Envelope AX | Signed/wrap e saturação por voz corrigidos; seis vetores e continuidade passaram | Ampliar fim de voz/subframes e validar temporalmente no DSP físico |
| Melee360AXNativeFrame / __AXProcessAux | Nove buses, callbacks, rotação e retorno integrados; B isolado corrigido | Teste integrado passou; DPL2 e equivalência temporal completa continuam pendentes |
| AX PB updates | Filas dos setters agora aplicadas em cinco blocos de 32 amostras; testes de ordem, capacidade, reset e callback/AI passaram | Importação de PB externo e equivalência temporal DSP completa continuam fora do suporte |
| AX FIR / ITD | Ainda recusados | Coeficientes e delay/histórico |
| AX streaming type=1 | Agora conserva yn1/yn2 no loop; setter e vetor de fronteira passaram | Ampliar cenas e confirmar demais variantes DSP sem alterar padding do PB antigo |
| GX público | 132 APIs sem definição no inventário | Agrupar por dependências; implementar estado e efeitos observáveis, sem entradas vazias |
| GX já presente / TEV / VI | Modos e probes existentes não demonstram equivalência de todos os casos | Matriz explícita de modos, referências e teste com HSD original |
| HSD / OS / CARD / cenas | Caminhos específicos existentes; cobertura geral ainda não auditada | Expandir inventário por subsistema e seguir chamadas de cenas originais |

Para cada incremento: identificar o chamador original, documentar entrada/saída e estado persistente, implementar a dependência real, executar vetores e o caminho integrado, registrar limites. Não silenciar modos não suportados.

## Primeiro incremento

`src/ax_pcm_consumer.c`: aceitar somente bits de mixer implementados (0 ou 8 para estéreo); incrementar vL/vR depois de cada amostra quando bit 3 estiver ativo; preservar gains entre chamadas. Rejeitar explicitamente parâmetros Aux que antes podiam passar se o PB fosse construído diretamente com mixerCtrl zero.

O teste usa AXAcquireVoice, ARAM e AXSetVoiceMix originais. Confere os quatro valores L/R de uma rampa dividida em duas chamadas e overflow/underflow. Os demais probes PCM, ADPCM, SRC linear, depop e DMA continuam necessários. O primeiro frame AX que falhar agora registra índice e parâmetros PB para distinguir modo não suportado de endereço inválido.

Fontes de semântica: `work/melee-base/libs/dolphin/src/dolphin/ax/AXVPB.c` (AXSetVoiceMix) e [Dolphin AXVoice.h, MixAdd](https://github.com/dolphin-emu/dolphin/blob/eb236466c4f0ec8bef619add0972353d3996fe6c/Source/Core/Core/HW/DSPHLE/UCodes/AXVoice.h). A mudança não é uma conclusão do mixer AX inteiro e não corrige sozinha todo o áudio de combate.

## Resultado desta revisão

- Release/Compat compilou com os avisos existentes; XEX retail gerada e publicada após os testes.
- Training no Xenia passou, incluindo o novo marcador obrigatório de rampas e os probes PCM/ADPCM/SRC linear, depop, AX contínuo e consumo AI real. Evidência preservada: `logs/ax-stereo-completion-training-runtime.log`.
- Partida Mario/Link original apresentou 180 frames, com movimento e dano (9/11 aos 180 frames). Esse teste não valida todas as cenas ou o console físico. Evidência: `logs/ax-stereo-completion-match-verification.txt`.
- Bloqueio AX real da partida: voz 62, format=0 (ADPCM), src=0 (4-tap), mixer=0, type=0, ITD/FIR/updates=0; endereço 0xc43d42, fim 0xc53d3f. O consumidor recusa esse SRC antes de ler ARAM, portanto esse registro não demonstra corrupção do endereço. O DMA para explicitamente. Próxima prioridade: SRC 4-tap com coeficientes e histórico corretos, sem substituição silenciosa por linear.
- Base original permanece limpa. Hashes e backup: `logs/ax-stereo-completion-package-verification.json`.

Revisão seguinte: o bloqueio SRC=0 foi removido pelo filtro de quatro taps, com testes de saída e playback contínuo. O diagnóstico de partida avançou até outro PB com endereço corrente maior que o fim. A parada explícita permanece; não mascarar endereços nem atribuir automaticamente a corrupção de disco. [Implementação e próximos limites](ax-polyphase-src.md).

Correção posterior: current > end não significa necessariamente endereço inválido. No anel de streaming HSD, o callback atualiza end após a troca de buffer. O falso bloqueio foi removido por correção da condição de término, mantendo validação física de ARAM. Também foi integrado o contexto ADPCM de type=1. [Causa, testes e limites](ax-streaming-runtime.md).

Incremento seguinte: envelope signed/wrap, saturação por voz, nove buses e retorno Aux/Surround com callbacks originais. Corrigidos Aux B isolado e limpeza de todos os buffers em reinicialização. [Implementação e cobertura](ax-envelope-aux-runtime.md). Próxima prioridade: updates por milissegundo, com ponte explícita entre updateCounter/updateData e o PB consumido; FIR/ITD/DPL2 continuam fora da cobertura.

Updates integrados: agenda dos setters em cinco intervalos de 1 ms, com início/volume/parada, ordem, capacidade, reset e callback real. [Verificação e limites](ax-pb-updates-runtime.md). FIR, ITD e DPL2 permanecem pendentes.

SRC linear revisado: avan�o de fase antes da sa�da, hist�rico PB persistente e seis vetores de refer�ncia divididos entre blocos. [Cobertura e limites](ax-linear-runtime.md).

Encerramento AX revisado: intervalo ativo de 32 amostras completo, envelope/ganhos/depop e historico SRC; seis casos PCM16 passaram. Fins fracionarios ADPCM e reinicio via updates continuam pendentes. [Cobertura](ax-voice-end-runtime.md).
