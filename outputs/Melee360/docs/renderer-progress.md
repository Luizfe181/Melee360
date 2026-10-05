# Renderer e sequência de boot — estado verificado

Este documento preserva os resultados da etapa static-title-1. O estado atual original-menu-1, com dez páginas de gráficos originais, está em [original-menu-progress.md](original-menu-progress.md). Os blockers e o SHA256 abaixo são históricos.

Build: `static-title-1`. Alvo: Xbox 360 RGH/JTAG. Base doldecomp preservada.

## O que esta build executa

Apresenta o primeiro frame diagnóstico, verifica o núcleo HSD, carrega o archive do Mario, lê a geometria original de `GmTitle.usd` e reproduz o vídeo original `MvOpen.mth`. Ao terminar a intro, desenha o título original na pose estática dos arquivos. START pula o vídeo para o título; BACK encerra. START no título ainda não abre o menu.

A tela de formatação e o menu principal **ainda não estão disponíveis**. O título usa materiais simplificados e não tem animações. Este pacote não deve ser apresentado como jogo completo ou renderer completo.

## Integração do título estático

`hsd_scene.cpp/h` lê SceneDesc, câmera, joints, DObjs/PObjs, materiais e texturas sem relocar ou modificar o arquivo original. Aplica SRT/hierarquia e compensação de escala por eixo, câmera look-at com roll e projeção perspectiva/ortográfica. Os vértices passam para clip space; Z é convertido para o intervalo Direct3D 0..1. Não cobre joints com quaternion, restrições RObj ou matrizes externas; envelopes/morphs são ignorados explicitamente nessa ponte estática.

`title_scene.cpp/h` carrega `GmTitle.usd`, envia 13 texturas ao Direct3D e desenha 13 batches, com depth/alpha test e blend simples. `scene.hlsl` passa posição, UV e cor, multiplica a primeira textura pela cor do material e mantém o enquadramento 4:3. Não reproduz TEV, luzes, múltiplas texturas, textura/mat animação ou configuração PE individual. Por isso logotipo e fundo ainda diferem da aparência original.

`verify-static-title.ps1` confirmou 13 batches, 13 texturas, 4.926 vértices e zero malhas puladas no título. `tests/render_static_title.py` gera `logs/title-static-cpu.png`, uma prévia CPU da mesma geometria/câmera; **não é captura do Xbox/Xenia**. A imagem foi inspecionada: mostra logotipo, Press Start e créditos, com os efeitos/material ainda incorretos.

`verify-xenia.ps1 -TitlePreview` passou: upload dos recursos, primeiro DrawPrimitiveUP das malhas e 120 apresentações. O teste não inspeciona os pixels da GPU. O arquivo temporário de diagnóstico é removido ao terminar; o pacote normal inicia pela intro. A sequência completa pode ser verificada com `-MovieToTitle`.

O primeiro teste do vídeo inteiro encontrou um erro anterior no leitor: o quadro 2650 ocupa 61.184 bytes, acima dos 61.152 indicados no cabeçalho. O buffer passou a reservar também prefixo/alinhamento (61.184 bytes nesta imagem). `tests/check_mth_packing.py` verificou limites, SOI, encadeamento e posição final dos 3.036 quadros; apenas esse quadro excede o valor do cabeçalho. Resultado: `logs/mth-packing-regression.json`. Nenhum arquivo do jogo foi alterado.

Após a correção, `verify-xenia.ps1 -MovieToTitle` passou com o executável final: vídeo atravessou o quadro 2650, concluiu o stream, registrou `Title transition: movie completed`, carregou 13 batches/texturas e submeteu o desenho do título. Evidência: `logs/xenia-movie-to-title-test.log`. A execução acompanha o relógio e pode descartar quadros atrasados; a decodificação individual de todos os frames foi verificada anteriormente no host, não nesta reprodução. Os testes automatizados usam `verification.flag` para ignorar entrada do controle e o removem ao terminar. No pacote normal esse arquivo não existe; os controles funcionam normalmente. O atalho START precisa de teste manual no console.

SHA256 do pacote final `default.xex`: `E02C1ED02F4F2759F307BE5C7BCB6A0756B32D1885E801A8FD3D0C5E81B216C6`.

## Código acrescentado

- `gx_texture.cpp/h`: conversão das texturas tiled GX I4, I8, IA4, IA8, RGB565, RGB5A3, RGBA8, C4, C8, C14X2 e CMPR para ARGB. Suporta paletas IA8, RGB565 e RGB5A3. Valida dimensões, capacidade dos buffers e índices da paleta. Apenas o nível base é decodificado; mipmaps e gerenciamento GPU das texturas HSD ainda faltam.
- `gx_mesh.cpp/h`: leitura das descrições HSD de atributos e das listas GX; atributos diretos ou indexados de 8/16 bits; posições, normais XYZ, primeira cor e primeira coordenada UV. Converte quads, triângulos, strips e fans em listas de triângulos. Preserva o índice de matriz por vértice. Consome comandos de carregamento indexado de matriz, mas **não resolve essas matrizes**. Não aplica envelopes, morphs, animações ou transformações dos joints. Atributos NBT e primitivas não suportadas retornam um resultado explícito.
- `renderer_probe.cpp`: carrega o arquivo original do título no Xbox, encontra `ScTitle_scene_data`, percorre seus joints/DObjs/PObjs e verifica a decodificação da geometria. O resultado aparece no log.
- `card_image.cpp/h`: constrói, em memória, os cinco blocos de sistema de um cartão virtual de 2 MiB, incluindo diretórios/FAT redundantes e checksums big-endian. O teste verifica corrupção de metadados e recuperação quando uma cópia permanece válida. **Ainda não grava um cartão, não armazena saves e não chama a cena de formatação.** O serial é próprio do port: compatibilidade com validação de flash ID do GameCube/Dolphin não foi implementada. A verificação é dos metadados de sistema; não verifica cadeias FAT de saves existentes.
- Adaptadores de headers isolados: `stdbool.h`, limites inteiros, `OSCalendarTime` e declarações do cartão. A base original permanece sem alterações.

## Evidência

1. `verify-gx-textures.ps1`: testes de formatos, canais RGBA8 e limites passaram. O inspetor encontrou e decodificou **375 descritores de imagem** em `GmTitle.usd`, `MnMaAll.usd` e `NtMemAc.usd`. PNGs e offsets: `logs/menu-textures/manifest.json`. São texturas isoladas, não capturas do console e não telas reconstruídas. A busca é por descritores referenciados na tabela de relocação; não cobre imagens só acessíveis por tabelas de animação.
2. `verify-gx-meshes.ps1`: testes de indexação, limites e comandos desconhecidos passaram. Todas as listas inventariadas nesses arquivos foram decodificadas:

| Archive | Joints | Malhas | Vértices na lista de triângulos |
|---|---:|---:|---:|
| GmTitle.usd | 16 | 13 | 4.926 |
| MnMaAll.usd | 637 | 426 | 17.013 |
| NtMemAc.usd | 2 | 4 | 93 |

41 malhas do menu têm flags de envelope. A leitura dos vértices passou, mas a deformação desses envelopes **não foi implementada**. O número de malhas do menu inclui recursos de submenus presentes no mesmo archive; não significa que todos devem ser desenhados juntos.

3. `verify-card-image.ps1`: construção/checksums/redundância/corrupção passaram. Não modifica arquivos de save do usuário.
4. Release/Compat compilou com o XDK e gerou o pacote `package/RGH/Melee360/default.xex`. Permanecem warnings do código original e dos adaptadores; a build terminou sem erros.
5. `verify-xenia.ps1` passou com o novo teste obrigatório: `Renderer probe: title joints=16 meshes=13 triangle_vertices=4926 passed`, além dos testes anteriores, primeiro desenho da intro, avanço além do frame 30 e 120 apresentações. Isso não substitui validação dessa versão no console físico.
6. `MenuProbe=true` compilou como objetos seis unidades originais: gmscmemcard, gmtitle, gmtitlemode, mnmain, lbcardnew e lbcardgame. São probes de compilação; essas cenas ainda **não estão ligadas ao executável**.

## Próximos blockers concretos

1. Transformações SRT, hierarquia dos joints, câmeras, matrizes de posição/normais e envelopes. O formato dos vértices está legível; falta colocá-los na posição correta.
2. Materiais HSD/GX: upload/cache das texturas, UVs, geração de coordenadas, múltiplas texturas, TEV, blend/alpha/depth e lights. A conversão de pixels não reproduz o pipeline GX.
3. Animações HSD: AObj/FObj, joints, materiais e shapes. O menu original depende delas para posicionar painéis, botões e seleção.
4. Serviço CARD virtual persistente e compatibilidade das chamadas originais, com mensagens/decisões ligadas à cena de boot. Criar/formartar somente o cartão virtual do port, após a escolha na interface; não o armazenamento do console.
5. Integração do gerenciador de cenas e callbacks originais, texto/SIS, input e áudio. A sequência pretendida é: verificação do cartão e prompts necessários → intro → título → Start → menu. O prompt de formatar depende do estado do cartão; não deve reaparecer obrigatoriamente em todos os boots.

Não há benchmark de renderer: ainda não há desenho das malhas. Os testes de listas acima medem correção da leitura, não desempenho gráfico ou fidelidade visual.
