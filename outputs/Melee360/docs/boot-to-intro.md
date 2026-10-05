# Boot original até a abertura

O objetivo atual é integrar o boot e depois mostrar a intro, seguindo o fluxo original. O vídeo original agora tem um caminho portátil de reprodução, ainda sem áudio ou integração completa da máquina de cenas.

## Fluxo identificado no código original

1. `gm/gmmain.c:main`: inicializa OS, VI, DVD, PAD, CARD e alarmes; configura HSD, buffers de vídeo/FIFO, áudio, memória, leitura de arquivos e serviços. Entra em `gm_801A4510`.
2. `gm/gm_1A3F.c:gm_801A4510`: inicializa os modos e seleciona modo progressivo ou `GM_BOOT`.
3. `gm/gmboot.c:bootOnLoad`: a primeira cena é `GS_MEMCARD`. Seleciona `GM_TITLE` quando skip_intro está ativo, ou `GM_OPENING_MV` no fluxo normal. A saída ainda trata save/card e desbloqueios.
4. `gm/gmopeningmode.c:gm_Mode_Opening_States`: a primeira cena do modo de abertura é `GS_MOVIE_OPENING`.
5. `gm/gmopening.c:gm_Scene_Opening_OnEnter`: configura áudio, câmeras e objetos e inicia `MvOpen.mth` com a tabela original de tempos `gm_803DBFB4`.
6. `gm/gmopening.c:gm_Scene_Opening_OnFrame`: atualiza o vídeo, dispara áudio e sobreposições e controla a passagem para as próximas cenas.

## O que funciona na build experimental

`src/intro_stream.cpp` abre o arquivo original no filesystem do Xbox, confere o header MTHP big endian, dimensões, versão, tamanhos e limites e lê blocos comprimidos sequencialmente em memória física alinhada. O decoder portátil gera os pixels para a textura Direct3D. O teste no Xenia leu 640×480, 30 fps, 3036 quadros e primeiro bloco de 7680 bytes.

Essa chamada ainda ocorre dentro do programa de diagnóstico; não é execução de gmboot ou gmopening. A build apresenta o vídeo usando o decoder próprio e a textura Direct3D, após os testes de diagnóstico. A leitura de Mario permanece um teste histórico separado, não é parte do boot original da abertura.

## Bloqueios concretos

- A inicialização original depende de arenas, tempo, alarmes, DVD assíncrono, CARD, VI, áudio e HSD ainda incompletos.
- A primeira cena original precisa da integração de memory card/save e da máquina de cenas; não deve ser tratada como implementada por um stub vazio.
- `libs/dolphin/src/dolphin/thp/THPDec.c` possui IDCT/saída com assembly de paired singles e GQR do Gekko. Compilar sem MWERKS exclui essas partes; isso não produz um decoder funcional no Xenon. Essa dependência foi substituída no caminho experimental por src/mth_decode.cpp, validado com MTH real; o decoder original permanece apenas no probe.
- A saída portátil já vira textura na GPU do Xbox. Falta usar a tabela original de tempos da abertura; atualmente a reprodução usa o relógio nominal do arquivo. Áudio e elementos sobrepostos são etapas adicionais.

## Diagnóstico de compilação

`BootIntroProbe=true` inclui gmboot.c, gmopening.c, lbmthp.c e THPDec.c somente para compilação isolada. Não vincular esse conjunto no executável até resolver os símbolos, declarações e suporte de plataforma. Resultado e erros atuais ficam em `logs/boot-intro-probe.log`.

O repositório original permanece preservado. Todo o trabalho de adaptação fica em Melee360.

Avanço de compilação: gmboot.c e gmopening.c produziram objetos no XDK. O probe conjunto permanece com erros no THPDec.c: atributos de alinhamento são posicionados após declaradores no código original, uma sintaxe que o XDK não aceita. Mesmo resolvendo a sintaxe, as rotinas paired singles/GQR precisam de substituição funcional antes de executar o decoder. Os objetos de diagnóstico não são vinculados no pacote.

Validação completa do decoder portátil: os 3036 quadros de MvOpen.mth foram decodificados com sucesso no host. Quatro quadros (0, 900, 1800, 3035) passaram em comparação independente e testes de assinatura inválida/truncamento. A XEX executou o decoder no Xenon emulado, carregou textura, submeteu desenho, avançou além do quadro 30 e completou 120 Present. Não houve inspeção de captura do framebuffer do emulador nem teste físico; os PNG em logs são imagens geradas pelo decoder de host para validação, não screenshots do Xbox.
