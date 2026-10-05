# Training e seleção original de cenários — 2026-10-02

Revisão: original-training-sss-1. Implementação parcial: NÃO há treino jogável.

## O que executa

1 jogador -> Training abre a seleção existente de personagens. Confirmar com
A e depois START abre a seleção de cenários. O analógico/direcional move o
cursor com o cálculo e os limites originais de fn_8025A310 (mnstagesel.c).
O hit-test usa posições dos descriptors de layout MnSlMap.usd.

Malhas, texturas, câmera, layout, cursor, nomes e previews vêm de
MnSelectStageDataTable no arquivo original. O port monta esses descriptors;
não executa a íntegra de mnStageSel_Scene_OnEnter/OnFrame. Os ícones foram
escurecidos por uma alteração do port para indicar indisponibilidade.
Somente Battlefield pode ser confirmado. Outros cenários e Random são
rejeitados. O índice original de Battlefield é 24; seu StKind externo é
0x1F/31. Não confundir com GrKind interno 0x24/36.

A confirmação no Training executa os trechos originais:
- gm_SetupPlayerDefaults, gm_SetupAllPlayerDefaults, gm_SetupRulesDefaults;
- gm_801B05F4, gm_SetupHumanPlayer, gm_SetupCpuPlayer;
- gm_80189CDC (configuração de regras e snapshot TrainingModeState).

Os três flags de gm_801B1F70 são aplicados pela ponte do port. Os trechos
originais são gerados, com hash de origem, sem alterar a base, em
compat/generated/original_training_rules.inc e original_stage_select.inc.
O registro StartMeleeData fica acessível por Melee360TrainingStartData para
a futura entrada do motor. Não foi conectado ao motor de partida.

## Limites deliberadamente visíveis

No Training, confirmar Battlefield mostra “Dados prontos. Runtime de partida
 ainda pendente.” A tela não diz que a partida começou e não simula Mario.
Não há andar, pular, cair, colisão, ataques ou reset de treino nesta revisão.
P1 pode usar o roster da seleção existente; CPU Mario está apenas no registro
preparado, sem personagem criado. O seletor completo de CPU ainda falta.
No VS, confirmar Battlefield abre o diagnóstico de cenário já existente,
explicitamente “Sem partida”.

O movimento/hit-test original usa uma fronteira com nós planos privados,
não objetos HSD vivos; posições são fornecidas pelos descriptors. Fog, luz,
materiais e transições são parciais. O teste host registra duas limitações
de material (skipped=2), ainda pendentes. A captura stage-select-cpu.png é
uma renderização CPU de diagnóstico, NÃO uma captura de Xbox/Xenia.

## Verificação

verify-training-stage.ps1: regras e jogadores originais, slot/team, itens
inativos, cursor, limites, hit-test e mapeamento Battlefield.
verify-stage-select-scene.ps1: 29 previews e geometria finita; resultado em
logs/stage-select-scene-test.txt. Regressão dos três modelos de troféus passou.
Build Release/Compat XDK em logs/training-xdk-build.txt.
verify-xenia.ps1 -TrainingPreview: navega do menu original, confirma Mario,
abre SSS, rejeita outro cenário, prepara Battlefield e retorna aos menus.
A colocação direta do cursor nesse teste só ocorre com flag de verificação.
Resultados em logs/training-xenia.txt e logs/xenia-training-test.log.
Não testado fisicamente no console nesta revisão.

## Bloqueio da partida real

Audit com todos os objetos originais/runtime ainda falha: 175 símbolos,
364 referências e zero duplicações (logs/training-link-audit.txt).
Há chamadas GX de display lists, arrays, texturas e TEV não implementadas,
vozes/mixer AX e callbacks AUX ausentes, serviços OS/threads/contextos e
inicialização HSD pendentes. Arquivo completo:
logs/gameplay-compile/link-missing-symbols.txt.

Próximo marco necessário: carregar os dados originais do fighter, criar seu
GObj/Fighter pelo caminho original, inicializar cenário e colisões MP, ligar
os callbacks de estados/controle/anim/physics/coll e só então renderizar o
primeiro frame da partida. Esta revisão não substitui esses passos por
uma rotina de movimento independente.
