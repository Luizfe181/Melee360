# Consultas de vídeo e preferência progressiva — 2026-10-02

Quatro ausências implementadas: VIGetTvFormat, VIGetDTVStatus, OSGetProgressiveMode e OSSetProgressiveMode. Auditoria Mario/Link: 117 -> 113 únicos, zero duplicatas. Sem stubs ou /FORCE. Log video-settings-audit.txt. Fighter_Create continua não executado e a partida não liga.

VIGetTvFormat consulta XGetVideoMode: PAL_I -> VI_PAL; NTSC_M/J -> VI_NTSC. Outros standards são tratados como NTSC neste adaptador; não há identificação MPAL. VIGetDTVStatus retorna se a saída ativa é progressiva (!fIsInterlaced). É uma substituição de plataforma explícita; não lê GPIO de cabo componente do GameCube e não equivale a detectar capacidade de todos os cabos conectados.

OSGetProgressiveMode carrega preferência local com fallback para o modo físico atual. OSSetProgressiveMode aplica mode & 1, igual ao bit usado pelo código original OSRtc.c. Persistência usa registro de quatro bytes (magic/version/valor/check), escrita temporária e MoveFileEx com replace/write-through. Erro de persistência é registrado e preserva a preferência anterior. Arquivo: game:\melee360-video.bin. Não muda a resolução/output Xbox, VIConfigure ainda está ausente. Não usa SRAM do GameCube.

Probe usa um arquivo privado separado e preserva a preferência/cache/caminho reais: alterna valor, invalida cache e confirma leitura persistida, verifica masking de entradas 2/3, testa mapeamento PAL/interlaced e NTSC/progressive, compara getters com XGetVideoMode e valida dimensões positivas. Arquivo de teste removido. Serialização pela seção crítica OS/PAD existente. Não altera o arquivo de preferências do usuário.

Build Release/Compat passou (video-settings-build.txt). Xenia passou nos probes de vídeo e regressão anterior. Base work/melee-base preservada. Nenhuma mudança em renderer, mixer, IA, ECB completo ou spawn de itens nesta etapa. Ainda falta implementar configuração/presentação VI e inicialização HSD, além de GX/TEV e vozes AX/DSP, para executar o primeiro frame do Mario original.

TrainingPreview passou: novos probes obrigatorios, render/audio existentes e percurso Training/CSS/SSS/retorno ao menu. Log video-settings-xenia.txt. XEX validada atualizada no pacote; SHA256 renovado. Testado somente no Xenia.
