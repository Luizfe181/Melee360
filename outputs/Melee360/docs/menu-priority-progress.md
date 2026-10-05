# Menus: fila de compatibilidade e Teste de som — 2026-10-02

## Implementado nesta etapa

- Tela Teste de som: geometria, texturas e animações originais MenMainConTs_Top de MnMaAll.usd, câmera/luzes e fundo originais. Entrada e indicadores de música usam o sampler FObj existente e os índices de joints documentados em mnsoundtest.c. Não executa o handler GObj completo original.
- Lista de 80 músicas na ordem original text_ids/data_2 de mnsoundtest.c, ligada à tabela hps_files de lbaudio_ax.c. A toca/para a mesma seleção; direcional troca; START reduz volume até parar (~833 ms); X também para; B volta. O estado exibido consulta a voz real XAudio2. Os nomes dos arquivos e instruções ainda usam a faixa auxiliar do port. A área SOUND fica visualmente presente, mas não oferece efeitos SSM nesta build.
- Vídeos Arquivos: Como jogar usa howto.hps (ID 0x24); vídeo especial usa swm_15min.hps (ID 0x52), conforme gmhowto.c/gmomake15.c. O relógio dos vídeos acompanha amostras consumidas quando a voz está disponível. Fallback de relógio de parede permanece; não garante sincronia perfeita em todos os casos.
- Traduzidos nomes de modos especiais, desafios e vários itens na interface textual do port, com alternância PT/EN. Texturas/textos originais de menus continuam em inglês.
- Limite de leitura HPS elevado de 16 para 32 MiB para o arquivo original swm_15min.hps (30.918.144 bytes). Ainda mantém o arquivo inteiro em RAM; streaming incremental será necessário para reduzir o pico de memória. A tabela geral tem 99 entradas; testnz.hps não existe nos assets extraídos. As 80 músicas do Teste de som usam a ordem do jogo, não esse arquivo de teste.

## Fila prioritária

| Prioridade | Caminho | Estado e trabalho necessário |
| --- | --- | --- |
| 1 | Teste de som / SIS | Tela original integrada; implementar os nomes e números dinâmicos SIS nas posições originais, seleção de categorias e efeitos. |
| 2 | Som / AX-DSP | Música HPS real; falta SSM, vozes/mixer AX, efeitos e aplicação dos modos mono/stereo/surround. Volume de música funciona. Volume de efeitos não tem mixer funcional ainda. |
| 3 | Opções originais | Vibração, configurações locais, nomes, idioma da interface e reset existem. Migrar as telas de Som, Vibração, Display e exclusão para os descritores/fluxos originais. Display original é deflicker; a opção 4:3/16:9 atual é do port e não equivale a ele. |
| 4 | Regras / itens / cenários | Navegação e persistência locais existentes; ligar à estrutura real da partida. Configurar não significa que a regra já funciona em gameplay. |
| 5 | Dados / recordes / fotos | Menus de entrada existentes; integrar registros reais e arquivos de save. Não inventar recordes ou capturas. |
| 6 | Troféus | Galeria/coleção de dois modelos e loteria diagnóstica; faltam a coleção completa e lógica original. |
| 7 | Training / VS | CSS e seleção de cenário parciais, Battlefield apenas; Fighter_Create, runtime de partida e colisões ainda bloqueiam gameplay. |
| 8 | Eventos / estádio / torneio / modos especiais | Entradas presentes; handlers e gameplay específicos ainda não integrados. |

## Validação

Release/Compat compilado com XDK. Base work/melee-base permaneceu limpa. Host: navegação das 22 páginas / 36 destinos e 149 ativações; edição/serialização/corrupção e tradução PT/EN. Decoder HPS: 98 arquivos, 3.457 blocos, 390.943.044 amostras PCM. Cenas originais de som nos frames 0, 19, 60 e 200: 109 batches, 63 texturas, 273 tracks, zero malhas ignoradas. Prévia CPU inspecionada em logs/sound-original-preview.png; não é screenshot do console.

Xenia: teste SoundPreview com tela original, opening.hps/castle.hps, fade-out, parada e retorno passou. Algumas execuções anteriores encerraram antes de concluir; as causas desses encerramentos não foram estabelecidas. Testes passaram a usar pacote isolado em work/xenia-test/package para não compartilhar arquivos de log/flags com execução manual. ArchivePreview passou para ambos os vídeos com suas músicas originais e retorno ao menu (menu-archive-xenia.txt). A regressão geral MenuPreview não concluiu em 90 segundos; o último marcador foi a entrada em Opções, página 4. A causa do bloqueio não foi estabelecida. Não se declara que todas as opções passaram no Xenia nesta etapa. Console físico ainda precisa ser validado nesta build.

Logs principais: menu-sound-build.txt, menu-sound-xenia.txt, menu-options-host.txt, menu-catalog-hps.txt, sound-scene-host.txt menu-options-xenia.txt e menu-archive-xenia.txt. Artefato: package/RGH/Melee360/default.xex.

O catálogo é regenerável com generate-music-catalog.ps1, usando somente as tabelas do decomp original.
