# Posições indexadas e áudio da abertura — 2026-10-02

GXSetArray/GXSetVtxDesc e GXCallDisplayList agora suportam posições com índices
8/16 bits, para XY U8 fracionário e XY/XYZ F32. Leitura por stride do array,
transformação GX e submissão pelo backend existente. Probes: XYZ F32 nos índices
256–258/stride 16 e XY U8/stride 4, junto a cor/UV indexadas. Verifica coordenadas
transformadas e envio GPU. S16/U16, normais, matrizes e comandos de estado ainda
faltam; não se declara GXCallDisplayList completo.

Áudio: gmopening.c usa lbAudioAx_80023F28(0x3E); a tabela hps_files de
lbaudio_ax.c identifica opening.hps. A faixa original agora é decodificada de
DSP/HPS e reproduzida pelo XAudio existente durante MvOpen.mth. Volume inicial
independente da configuração de menu ainda não inicializada. Ao pular/terminar
o vídeo, o player é parado; nos menus troca para a faixa anterior menu01.hps.

Enquanto há áudio da abertura em reprodução, o vídeo usa SamplesPlayed/rate
como relógio; sem áudio disponível usa o relógio anterior. Isso não implementa
o scheduler original AX nem todos os SFX da intro. Os blocos HPS precisam manter
sample rate/canais da voz; mudanças inconsistentes são rejeitadas.

Build/logs: gx-pos-opening-build.txt, gx-pos-opening-intro-final.txt e
gx-pos-opening-training.txt. Não há Fighter executando ou frame de gameplay.
Não foram substituídas funções ausentes por stubs. Base original preservada.
Teste visual/auditivo e desempenho em console físico ainda necessários.

Intro e Training/CSS/Battlefield passaram no Xenia com exit 0. Logs confirmam uso do relógio de amostras, consumo de opening.hps e troca para menu01.hps. Auditoria Fighter continua com 140 símbolos ausentes/zero duplicatas: foram ampliados serviços existentes, não encerrada a tradução completa.
