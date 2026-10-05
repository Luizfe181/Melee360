# Opções originais e dados reais do save — 2026-10-02

## Mudanças

Vibração usa MenMainConVi_Top e quatro instâncias originais MenMainCtlVi_Top, ancoradas aos joints 23/24 conforme mnvibration_CreatePortPanels. Os estados dos controles conectados vêm de XInput; os testes forçam quatro conexões. Liga/desliga é independente para cada porta. O pulso de teste dura 180 ms e somente o controle ligado é acionado; o serviço de expiração roda também nas páginas modais. Valores reservados 18–21 da configuração M36C v1 agora guardam quatro flags de desativação. Arquivos antigos com esses bytes em zero mantêm o comportamento global anterior. Nomes associados à vibração e o cursor completo original ainda não estão integrados.

Som usa MenMainConSo_Top e os joints/frames de mnsound.c. A convenção original é 0=stereo/1=mono, invertida em relação à configuração do port; a ponte converte explicitamente. Volume de música move o indicador original e altera XAudio2. Mono faz média dos canais L/R e envia a mesma mistura para os dois canais frontais; Stereo preserva L/R. A matriz segue a ordem indicada no header XDK xaudio2.h: S + SourceChannels * D. GetOutputMatrix verifica a leitura de retorno. O modo Surround ainda usa Stereo, explicitamente identificado como pendente. Efeitos/AX e o mix único original sounds/music não foram implementados: continuam ajustes independentes do port, com aviso no rodapé.

Dados > Recordes > Diversos usa MenMainConCo_Top (mncount.c) e exibe os totais reais de um snapshot de save original. Nomes/valores dinâmicos usam a fonte auxiliar do port, não a implementação completa de SIS. O leitor aceita somente o subconjunto GALE01 GCI com GmSaveData de 0x1790 bytes no arquivo lógico 1. Valida tamanho, setores, manifesto e checksum pelo HSD_Decrypt original. Cópias de reserva divergentes são rejeitadas; não adivinha qual versão é mais recente. Campos vêm dos offsets documentados de GmSaveData em gm/types.h e dos getters em gmmain_lib.c.

O código original crypt.c é incluído sem edição por original_save_crypto.cpp, compilando como C++ para aceitar o array com tamanho const que o compilador C do XDK rejeita. Não há stubs de checksum/decriptação.

Foi copiado o GCI encontrado em AppData/Roaming/Dolphin Emulator/GC/USA/Card A para package/RGH/Melee360/melee360-import.gci. Os SHA256 de origem e cópia são iguais: F21B78A34FF1257198864114B90BB5420C87594CDB4BDCB91FB9A97C2360E99B. A origem foi apenas lida. A tela identifica os valores como snapshot importado, não progresso produzido pelo port. Esse snapshot possui 2 troféus e zero partidas/KOs registrados. Nenhum dado foi importado para o runtime do gameplay ou regravado no save original.

## Validação

- Release/Compat compilado com XDK. Base work/melee-base preservada.
- Modelo de menu: 22 páginas, 36 destinos, 152 ativações; edição, limites, tradução, persistência serializada e independência dos controles passaram.
- Cenas host: Som 104 batches / 60 texturas / 162 tracks; Vibração 115 batches / 51–54 texturas / 188 tracks; Diversos 86 batches / 43 texturas / 106 tracks. Zero malhas ignoradas. Estados de conexão e valores de volume distintos testados. Prévias CPU de Som/Vibração inspecionadas; não são screenshots do console.
- Leitor GCI: arquivo real, fixture cifrada pela rotina original com contadores conhecidos, big-endian, tamanho truncado, identidade incorreta, checksum corrompido e preservação da saída em erro passaram.
- Xenia OptionsPreview: navegação em Vibração/Som, alterações por porta, aplicação Mono/Stereo e retorno ao título. DataPreview: tela original Diversos, validação do snapshot e retorno ao título.

Logs: options-data-build.txt, options-model-host.txt, options-scene-host.txt, options-xenia.txt, save-stats-host.txt e data-records-xenia.txt. Scripts: verify-menu.ps1, verify-sound-scene.ps1, verify-save-stats.ps1, verify-xenia.ps1 -OptionsPreview/-DataPreview.

## Limites e fila

Screen Display ainda é o ajuste 4:3/16:9 do port; não equivale ao deflicker do GameCube. Tela e aplicação de deflicker, idioma original japonês/inglês, exclusão completa do save, fotos, recordes por lutador, bônus e mensagens de desbloqueio seguem pendentes. Não se declara que todas as opções estão implementadas. O port ainda não produz recordes de gameplay. Console físico precisa validar os motores e a saída de áudio desta build.

Para testar os recordes no Xbox, copiar também melee360-import.gci junto ao default.xex. Os arquivos data/ e fontes existentes continuam necessários.
