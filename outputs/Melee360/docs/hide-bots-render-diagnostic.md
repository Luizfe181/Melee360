# Battlefield com bots invisiveis

Modo solicitado para separar o custo de desenho dos Fighters do custo da partida. A build inicia Mario CPU vs Link CPU em Battlefield. O mapa, cameras, audio, scheduler, animacoes logicas, IA, fisica e colisoes continuam ativos. O overlay mostra frame, posicao, estado, dano e stocks dos dois personagens.

Durante cada passe de renderizacao, somente os callbacks dos Fighters cujo tipo e CPU sao temporariamente suprimidos. Os ponteiros originais sao restaurados antes do proximo frame de simulacao. E uma chave explicita de diagnostico; nao substitui uma dependencia ausente. Objetos separados, como efeitos e itens, continuam desenhados. O codigo base nao foi modificado.

## Comparacao no Xenia

Mesma XEX, 180 frames, duas execucoes do mesmo caminho original:

| Medida por frame | Bots visiveis | Bots ocultos |
|---|---:|---:|
| Logica | 3.235 ms | 3.078 ms |
| Renderizacao | 345.445 ms | 189.933 ms |
| Apresentacao | 0.343 ms | 0.344 ms |
| Draws acumulados | 203241 | 81546 |

Reducao do tempo de renderizacao: 45.0%. Os registros CPU amostrados coincidem, incluindo estado, posicao, dano e stocks. No frame 180 os danos eram 9 e 11. Nenhum bloqueio AX ou parada DMA nos testes. Uma terceira execucao verificou visualmente o mapa com captura no frame 60.

Os valores sao tempos CPU medidos no caminho de diagnostico do Xenia, nao uma promessa de FPS no console nem equivalencia com o preview isolado de Battlefield. O render ainda tem custo alto mesmo sem Fighters. A comparacao inclui o trabalho feito pelos callbacks de desenho dos personagens; nao separa skinning, preparacao de vertices, materiais e GPU entre si. Nao prova equivalencia completa da simulacao alem dos frames e estados observados.

Evidencias: logs/hide-bots-profile.txt, logs/show-bots-profile.txt, logs/hide-bots-comparison.json, logs/hide-bots-capture-verification.txt e logs/hide-bots-frame60.png.

## Usar e reverter

O pacote RGH/Melee360 esta configurado com original-match.flag e hide-bot-render.flag. Abra default.xex para entrar diretamente na partida original com os bots invisiveis.

Para mostrar os personagens na mesma partida, remova apenas hide-bot-render.flag e reinicie. Para voltar aos menus, remova tambem original-match.flag. O script set-bot-render-test.ps1 oferece os modos Hidden, Visible e Menu e altera apenas essas duas flags. Reinicie a XEX apos trocar o modo.
