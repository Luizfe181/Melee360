# Troféus — referência em vídeo, 2026-10-02

Referência: Dolphin Emulator 2026.10.02 - 09.52.21.02.mp4 (42,8 s).
O vídeo mostra Galeria, lista, Loteria e Coleção. Esta revisão implementa
um subconjunto desse fluxo no port; não reproduz integralmente as cenas originais.

## Implementado

- Entrada pelas opções do submenu original Troféus.
- Galeria: geometria e texturas originais de TyDaisy.dat e TyKusuda.dat,
  pedestal original TyStand.dat, rotação pelo analógico, seleção e lista por Y.
- Coleção: Daisy e Party Ball lado a lado quando obtidos.
- Loteria de demonstração: 105 moedas iniciais, gasto ajustável de 1 a 20,
  recompensa fixa Party Ball e contador de cópias. Não é o algoritmo original.
- Progresso separado em game:\melee360-trophies-demo.bin: 5 inteiros nativos
  (magic 0x4d335459, versão 1, moedas, cópias Daisy, cópias Party Ball).
  Escrita temporária e renomeação; não importa nem modifica saves GCI/GameCube.
  O teste automatizado mantém esse progresso apenas em RAM e não grava esse arquivo.
- Recursos de modelo/textura persistem durante a rotação; atualização geométrica
  limitada a aproximadamente 30 Hz. Troca de página/modelo recria a cena.
- Decoder GX lê normais NBT intercaladas do pedestal. Tangentes/binormais não
  alimentam iluminação; NBT3 com índices separados permanece pendente.

## Validação

Build Release/Compat pelo XDK e conversão retail encrypted uncompressed.
Teste host: Daisy 85863 vértices/19 texturas, Party Ball 1203/3,
pedestal 1365/1; nenhuma malha ignorada. Geometria finita e rejeição de
arquivo truncado verificadas. Logs em logs/trophies-model-test.txt.
Teste Xenia automatizado em verify-xenia.ps1 -TrophiesPreview:
Galeria, abrir/fechar lista, recompensa, Coleção, retorno e seleção Party Ball.
Resultado em logs/trophies-video-xenia.txt e logs/xenia-trophies-test.log.
Regressão GX em logs/trophies-gx-mesh-regression.txt.
O teste físico desta revisão no Xbox 360 ainda depende de validação do usuário.

## Pendências e limites

Somente dois troféus. Interface, textos resumidos em português, câmera e
navegação destas três páginas são próprios do port. Não há o gerenciador
original das cenas de troféus, texto SIS completo, máquina e animação de sorteio,
regras originais de chance, disposição/câmera da mesa da Coleção, catálogo
completo, classificação, iluminação/reflexos completos ou integração com save
original. A implementação usa assets originais, mas não deve ser apresentada
como todas as telas originais traduzidas. Não adiciona gameplay de partidas.

Arquivos principais: src/menu_ui.cpp, src/title_scene.cpp, src/hsd_scene.cpp,
src/gx_mesh.cpp, tests/trophy_models_host.cpp, verify-trophy-models.ps1.
