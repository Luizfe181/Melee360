> Registro histórico do bring-up de lógica. A revisão atual acrescenta desenho original HSD/GX: veja [progresso do renderer](original-match-render-progress.md).

# Primeiro combate original com CPUs — 2026-10-03

## Resultado validado no Xenia

A entrada gm_Scene_Vs_OnEnter original inicializa Battlefield, Mario CPU nivel 9 e Link CPU nivel 9, Stock com 3 vidas e itens aleatorios desativados. O codigo original cria os dois Fighters, estabelece spawn, partes, animacoes, artigos de ataques e colisao do cenario. HSD_GObj_RunProcs e gm_Scene_Vs_OnFrame executam continuamente; o processamento de DVD/ARAM e lbAudioAx_80027DF8 ocorre antes do scheduler.

900 frames com apresentacao no Xenia passaram, sem assert e sem substituir funcoes de gameplay por stubs. A amostragem confirmou 15 posicoes diferentes e 12 estados diferentes para cada bot, inputs CPU nao zerados, estados no chao e no ar e dano recebido: Mario 56,03%, Link 47,64%. Evidencia e validacao automatica: logs/original-match-runtime.log e logs/original-match-logic-verification.json; diagnostics/verify_original_match.py.

O teste confirma movimento, transicoes, interacao e dano. Nao valida ainda todos os golpes, perdas de stock/respawn, encerramento da partida ou todos os mapas/personagens. A ligacao do caminho Mario/Link continua sem simbolos pendentes e sem duplicacoes, sem /FORCE.

## O que aparece

Fundo preto, FPS e painel atualizado a partir dos Fighters reais: dano, stocks, posicao e estado. O desenho do combate nao esta implementado neste modo; nenhum modelo/combate visual substituto foi adicionado. Isto e um combate de logica original em execucao, ainda nao uma partida visual completa. Os menus existentes continuam disponiveis no boot normal.

Para abrir no Xenia, execute start-original-match-xenia.ps1. O launcher cria uma pasta propria em work/xenia-match-play-*, usa os assets via junction e ativa apenas nessa copia original-match.flag. Ao fechar Xenia, remove a flag. Nao altera saves/configuracao instalada do emulador nem os assets. Este teste ainda nao foi validado no hardware real.

## Bloqueios resolvidos

- it_8027870C instala o arquivo comum de itens, incluindo a tabela de artigos Fire/Cape usada por OnLoad de Mario.
- Camera_Init cria os subjects reais; lbArq_80014D2C inicializa a fila original. A espera sincronica lbArq agora bombeia ARAM, conservando a transferencia/callback original.
- lbAudioAx_8002838C executa antes de lbMemory/lbHeap no modo de combate, reservando os bancos de audio e streaming via ARAlloc antes dos heaps logicos de animacao. Evita a sobreposicao nesse boot isolado; transicoes posteriores de heaps ainda requerem validacao.
- Buffers de cabecalho SFX e pstHakoHeader de HPS receberam alinhamento explicito de 32 bytes. A espera de synth bombeia DVD/ARAM. As validacoes de alinhamento continuam ativas.
- HSD_SisLib_803A6048 inicializa o allocator SIS original. Isso permite completar name tags, HUD, pausa, timer e a entrada VS original.

Os arquivos gmvs/ifall gerados contem somente inclusoes qualificadas e marcadores de diagnostico, com os corpos originais conservados. lbarq/synth possuem as adaptacoes de espera/alinhamento acima. A base work/melee-base permanece intacta.

## Bloqueios ainda reais

Audio: o bootstrap/bancos originais funcionam, mas o consumidor AX nativo interrompe o DMA ao encontrar um modo de voz ainda nao suportado. O marcador foi preservado no log. A musica/SFX deste combate nao sao validados; srcSelect/FIR, mixer/aux e demais parametros precisam de traducao e testes. Nao foi removida a validacao nem silenciado o erro.

Render: a renderizacao original dos Fighters/HUD/cenario nao e despachada neste modo. O painel usa dados reais, mas nao substitui essa tarefa. Ainda falta integrar os passes GX/HSD e verificar as chamadas e formatos de vertex/texture/TEV desse caminho.

Fluxo: entrada pelo launcher/flag, ainda sem conectar ao seletor/menu VS normal. Ainda falta testar fim de partida, respawn, jogador humano, audio completo e integracao do desenho.

## Pacote publicado e regressoes

Build: logs/original-match-presented-build.txt. Regressao Mario: mario-create-final-verification.txt. Training, audio dos menus e Battlefield AA: match-final-training-regression.txt, match-final-sound-regression.txt e match-final-aa-stage-regression.txt, todos passaram.

Imagem atualizada: package/RGH/Melee360/default.xex. SHA256 FBF1919B03799ED13EB988AA585F4DC77BE3726E26E9661097B981106473EBEB. Backup C:\Users\luizf\Documents\Codex\2026-10-01\referenced-chatgpt-conversation-this-is-an-2\work\default-before-original-cpu-match-20261003-174730.xex. Manifesto logs/original-match-package-verification.json. Nenhuma flag de combate e enviada no pacote normal; use o launcher isolado para o teste CPU.

