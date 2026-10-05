# character-select-1 — seleção e modelos estáticos

Entre em VS Mode → Melee. O direcional move entre 25 retratos; A/START confirma e bloqueia a troca. B cancela a confirmação; outro B volta a VS. A confirmação é somente do teste: não inicia partida, não grava fighter no estado original e não executa o fluxo completo de mncharsel.c.

A tela usa o archive original MnSlChr.usd: câmera e modelos background/menu de MnSelectChrDataTable. O interpretador FObj original aplica a pose inicial e poses para mostrar os retratos desbloqueáveis. Todos estão disponíveis para diagnóstico, sem depender de save. A moldura da seleção, controles e caixa de confirmação são próprios do port. Os quatro cartões inferiores ainda estão na pose estática dos recursos; seus indicadores CPU não representam quatro jogadores funcionais. Não há hand/token, multiplayer, seleção analógica, costumes, Sheik ou transições originais.

Ao mudar de personagem, o port carrega seu Pl*Nr.dat e desenha as malhas e texturas reais na área inferior esquerda. Não é vídeo nem imagem do modelo. A hierarquia e os envelopes passam pelo leitor HSD; uma câmera ortográfica de diagnóstico enquadra o modelo em bind pose, sem animação. O enquadramento e confirmação são adaptações do port, e os materiais/TEV continuam parciais. Ice Climbers mostra apenas Popo. Samus tem duas listas não decodificadas, com atributo GX_VA_NBT (código de diagnóstico 281). Os demais 24 arquivos do catálogo passaram com zero skips. Isso valida carregamento, não fidelidade visual de todos os modelos.

## Código e evidência

- `src/character_select.h`: catálogo com a ordem original de 25 retratos, arquivos e navegação pelas três linhas.
- `src/hsd_scene.cpp`: Melee360LoadCharacterSelect monta recursos originais e calcula a moldura a partir da geometria do retrato; Melee360LoadFighterPreview lê o primeiro joint público, transforma/enquadra a geometria e valida valores finitos.
- `src/title_scene.cpp`: compartilha upload/desenho GPU, carrega CSS/modelo e recria os recursos somente quando muda a seleção. Não há cache GPU completo de fighters nem benchmark no console.
- `src/menu_ui.cpp`: entrada VS/Melee, troca, confirmação/cancelamento e retorno, com indicação explícita de teste sem gameplay.
- `verify-character-select.ps1`: passou em todas as 25 seleções e arquivos, preservando os checks de arquivos inválidos do teste de cenas. Relatório: logs/character-select-host.txt. Título continua com 13 batches/texturas e 4.926 vértices, zero skips.
- Release/Compat compilou com XDK, sem erros; warnings permanecem. O pacote retail sem xbdm está em package/RGH/Melee360/default.xex. Hash em logs/RGH-image-sha256.json.
- `verify-xenia.ps1 -CharacterPreview`: passou na XEX final, carregando Mario, Luigi, Ness, Pikachu, Pichu e Fox, confirmando Fox, cancelando, voltando a VS e ao título, com 120 Present bem-sucedidos. Evidência: logs/xenia-character-test.log. Confirma execução/submissão de desenhos, sem inspecionar pixels da GPU. Falta validar esta revisão no console físico.
- As prévias logs/css-cpu.png e logs/mario-preview-cpu.png foram renderizadas e inspecionadas no host. São imagens CPU dos recursos, não screenshots do Xbox/Xenia. O Mario aparece texturizado em bind pose. A composição final com a interface do port deve ser conferida no console.

O checkout doldecomp e os arquivos de assets do usuário continuam preservados. Os próximos passos são integrar o cursor/token e estados originais da seleção, Nana/Sheik/costumes, animações e materiais/atributos NBT. Gameplay permanece fora desta etapa.
