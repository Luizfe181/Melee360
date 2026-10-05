# Revisão original-menu-1

O painel azul provisório foi substituído por geometria, texturas e poses dos recursos originais em dez páginas: Main Menu, 1-P Mode, VS Mode, Trophies, Options, Data, Regular Match, Stadium, Special Melee e Records. As 46 seleções dessas páginas carregaram no teste host sem malhas puladas. As telas especializadas mais profundas continuam com a interface própria do port, identificada como provisória. Não há partidas.

## O que foi integrado

- `hsd_animation.cpp`: leitura validada de descritores big-endian e amostragem pelo `fobj.c` e `spline.c` originais, compilados sem alterações. Testes cobrem interpolação e rejeição de streams truncados/inválidos e ciclos. Não substitui o gerenciador AObj/GObj completo.
- `generate-original-menu.ps1`: extrai as tabelas originais de poses/labels/descrições e os corpos inalterados de `mn_8022DB10`, `increment_selection` e `decrement_selection`. Registra o SHA256 de mnmain.c.
- `original_menu_root.cpp`: executa o handler original do menu principal por uma ponte limitada de eventos. Os hooks GObj/audio não implementam o scheduler nem áudio. As cinco entradas principais estão disponíveis; os estados reais de desbloqueio/save ainda não são aplicados. Os outros handlers de input continuam próprios do port.
- `hsd_scene.cpp`: monta os elementos originais Back/Panel/ConTop/Cursor, aplica poses de joints, materiais e texturas com FObj, posiciona os cursores na hierarquia original e resolve envelopes de raiz usados pelos menus. Acrescenta UVs, wrap/mirror, iluminação difusa parcial e tradução parcial de uma textura/TEV. Não é o pipeline GX completo.
- As descrições inferiores usam strings SIS de SdMenu.usd e os glifos I4 originais. `extract-menu-font.ps1` extrai 287 glifos e métricas do main.dol conhecido de GALE01 1.02, sem alterar o arquivo. O pacote inclui `melee360-font.bin`, 147.520 bytes. A leitura SIS implementa os comandos usados nessas descrições, incluindo duas linhas; não é o renderer completo de texto.
- `title_scene.cpp` mantém archives/fontes em cache e recria os recursos GPU quando a seleção/página muda. As poses são amostradas estaticamente; não há avanço contínuo das animações. `menu_ui.cpp` desenha as dez páginas sem o painel azul.
- Data/Archives abre MvOmake15.mth e MvHowto.mth pelo player do port, com retorno ao menu. Ambos continuam sem áudio.

Os arquivos em work/melee-base e os assets do usuário foram preservados. A fonte original conhecida tem SHA1 08E0BF20134DFCB260699671004527B2D6BB1A45. Não são patches no main.dol nem execução do binário GameCube.

## Verificação

Release/Compat compilou com Visual Studio 2010/XDK e gerou default.xex retail para RGH/JTAG sem import de xbdm. Permanecem warnings do decomp e adaptadores; o resultado e os avisos estão em logs/Release-Compat.log. O SHA256 atualizado do pacote está em logs/RGH-image-sha256.json.

`verify-original-menu.ps1` passou para as 46 seleções das dez páginas, descrições/glifos e validação de arquivos inválidos: logs/original-menu-host-test.txt. `verify-menu.ps1` passou para a navegação, o handler principal original e serialização da configuração própria. `verify-gx-meshes.ps1` passou nas 13 malhas do título, 426 do menu e quatro de NtMemAc. `verify-static-title.ps1` confirmou 13 batches/texturas, 4.926 vértices e zero skips.

`verify-xenia.ps1 -MenuPreview` percorreu páginas originais, telas provisórias de regras/som, abriu os dois vídeos, voltou a Data e retornou ao título. O teste exige desenho original submetido, persistência/ABI da configuração e 120 Present bem-sucedidos. `-TitlePreview` passou também. Evidência: logs/xenia-menu-test.log e logs/xenia-title-test.log. Os testes confirmam execução e submissão de desenhos; não inspecionam os pixels da GPU nem substituem teste físico.

As imagens logs/original-menu-cpu-0.png e logs/original-menu-vs-cpu.png são prévias CPU das mesmas malhas e foram inspecionadas; não são screenshots do console/Xenia. Materiais/ícones ainda têm diferenças visuais.

## Próximos blockers

1. Integrar scheduler e callbacks GObj/JObj/AObj, entrada de cada submenu e cenas especializadas, com animação contínua e transições reais. Evitar reconstruir todos os recursos durante a animação.
2. Completar GX/TEV com múltiplas texturas, fog, especular, texgen, materiais e deformações gerais. Os envelopes suportados aqui cobrem o menu; isso não valida fighters.
3. Implementar CARD/save e os flags reais de desbloqueio. O teste de cartão e a configuração própria não equivalem ao save original nem à cena de formatação.
4. Portar áudio, seleção de personagens/cenários e gameplay. Menus navegáveis não tornam esses modos executáveis.
5. Traduzir os textos e texturas originais para português em recursos separados; nesta revisão eles permanecem em inglês.
