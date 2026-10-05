# menu-animation-1

Esta revisão anima o título/Press Start, as dez páginas de menus já integradas e o fundo da seleção de personagens. Usa streams originais por FObj; não são vídeos desses menus nem curvas visuais inventadas. É uma integração parcial e não representa todas as animações/cenas do Melee.

## Implementado

- O título passou de GmTitle.usd estático para GmTtAll.usd, conforme gmtitle.c. Carrega TtlBg_Top e TtlMoji_Top, câmera original e animações de joints/materiais/texturas. Usa os loops originais 130–1330→130 e 400–1600→400. São 175 tracks FObj, com 33 batches e 28 texturas nas amostras verificadas. O Press Start e o fundo mudam com a animação. O modo de entrada usado aqui corresponde ao título ativo, começando nas poses 130/400; não reproduz ainda toda a transição da cena de abertura.
- Dez menus: fundo, painel de entrada/idle, entrada dos botões em avanço/retorno, painel de descrição lateral, destaque, anel selecionado e efeito breve. generate-original-menu.ps1 agora extrai todos os start/end/loop frames de mnmain.c, além dos dados anteriores. As posições dos componentes usam os índices originais mn_803EAE7C; anel é joint 4 e efeito breve é joint 9. Isso corrige a associação anterior que duplicava os ícones não selecionados.
- mn_8022ED6C foi extraído de mn_22EC.c com corpo inalterado e SHA256 registrado. Uma ponte isolada fornece o estado de frame e chamadas de avanço/requisição para esse helper. O FObj/spline também continua original. Isso não integra o scheduler GObj/JObj completo.
- A atualização tenta acompanhar o relógio do jogo em 60 frames por segundo, amostrando o tempo decorrido. A taxa efetiva de desenho depende do custo do renderer; não há garantia de 60 fps. Frames visuais podem ser saltados quando a atualização demora.
- Corrigida a semântica original de HSD_A_M_ALPHA: alpha é 1 − valor da track, conforme mobj.c. Isso recuperou elementos do título que estavam desaparecendo.
- O fundo da seleção repete a cada 200 frames, conforme fn_80263354. Modelos dos fighters, cursor, cartões de jogadores e confirmação continuam no teste parcial anterior; os fighters não ganharam animações nesta revisão.

## Recursos e desempenho

Archives do título/menu/CSS permanecem em memória. As listas de vértices decodificadas e texturas processadas são reutilizadas durante a animação. O cache de pixels é limitado a 16 MiB/256 entradas e é invalidado quando muda o archive ativo. O cache pressupõe archives imutáveis, como os buffers privados do runtime. Os cursores são desenhados diretamente sob as transformações originais dos slots, evitando desenhar/descartar repetidamente seus ancestrais.

Shaders e declarações GPU permanecem carregados durante o avanço. Texturas com pixels/dimensões iguais são mantidas; pixels alterados são atualizados com LockRect. Mudanças de dimensão e entradas novas ainda podem exigir alocação. Trocar uma página ou modelo pode recriar recursos; não há um cache GPU completo de todas as cenas.

Uma medição intermediária no Xenia registrou build/upload médio de 36,29 ms no menu principal e 21,53 ms no título, em 120 updates. Esses números não são FPS, tempo total de apresentação nem benchmark do Xbox físico; a revisão final corrige componentes e também anima CSS. logs/xenia-animation-test.log contém a medição atualizada da XEX final.

## Validação

verify-animated-scenes.ps1 verificou 14 tempos do título, 644 amostras das 46 seleções das dez páginas, entrada reversa nas dez páginas e 14 tempos do fundo CSS. Verifica mudanças da geometria/UV/cores/pixels, índices de texturas, valores finitos e ausência de skips. Inclui amostras antes/depois dos limites de repetição. Evidência: logs/animated-scenes-host.txt. As imagens CPU do título e do menu foram inspecionadas; não são screenshots do console/Xenia.

Os testes estáticos de menus e seleção passaram também. Release/Compat gerou o pacote retail sem xbdm. Hash final em logs/RGH-image-sha256.json. Na XEX final, verify-xenia.ps1 -AnimationPreview passou com 120 updates no principal, VS e título; -CharacterPreview passou com seis modelos, confirmação, cancelamento e retorno. Evidência em logs/xenia-animation-test.log e logs/xenia-character-test.log. Os testes Xenia registram execução, atualizações e submissão GPU, sem verificar visualmente os pixels; falta validar animações/desempenho no console físico.

## Ainda necessário para atender todas as animações

1. Integrar o scheduler, callbacks e estados completos de mnmain/gmtitle/mncharsel. A navegação dos submenus ainda é uma ponte própria.
2. Coordenar saída das árvores antigas com entrada das novas, efeitos procedurais de ligação do cursor e continuidade exata das tracks ao trocar seleção. As tabelas de saída foram extraídas, mas a sequência completa ainda não é executada.
3. Portar as cenas especializadas que permanecem provisórias (regras, som, rumble, idioma, nomes, itens, etc.), com recursos e callbacks próprios.
4. Completar shapes/morphs, materiais TEV com múltiplas texturas, fog, luzes e demais componentes animáveis. A leitura de 175 tracks no título não significa reprodução integral do pipeline GX.
5. Integrar mão/token, estados de confirmação, multiplayer, costumes e animações dos fighters no CSS.

Textos e imagens originais permanecem em inglês. Aqui “traduzir o código” significa adaptar a execução ao XDK/Direct3D, não traduzir os textos para português. O checkout upstream e assets do usuário foram preservados.
