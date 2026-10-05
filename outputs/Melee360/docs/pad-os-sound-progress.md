# PAD e modo de som OS — 2026-10-02

Implementados PADSetSamplingRate, OSGetSoundMode e OSSetSoundMode sem stubs. Auditoria do caminho Fighter_FirstInitialize -> Fighter_Create(Mario) -> Fighter_Create(Link): 136 para 133 símbolos ausentes, zero duplicatas. A auditoria ainda não liga uma partida e não executa Fighter_Create.

PADRead usa XInput com cache protegido pela seção crítica existente. Neste adaptador, taxa 0 consulta a cada leitura; taxas 1..11 impõem o intervalo mínimo em milissegundos; valores superiores são limitados a 11. Uma mudança de taxa invalida o cache. Isso adapta a API à plataforma; não reproduz as tabelas SI por linhas de vídeo do GameCube. Probe determinístico com relógio e entrada injetados verifica cache antes do prazo, atualização no prazo, taxa zero, limite, máscara de canais, desconexão e eixo negativo. Restaura todos os providers e estados; não equivale a teste de controle físico.

OSGet/SetSoundMode usam os valores originais Mono=0 e Stereo=1. A configuração é compartilhada com menu, persistência e matriz XAudio já existente. Valores inválidos preservam o estado; configuração anterior à abertura do menu é aplicada na inicialização. Alterações no menu passam pela API original. Surround permanece fallback Stereo. O header de compatibilidade inclui OSRtc.h original para disponibilizar declarações e constantes, sem implementar os outros serviços RTC.

Build Release/Compat passou: logs/pad-os-sound-build.txt. OptionsPreview passou no Xenia: logs/pad-os-sound-xenia-final.txt, incluindo probes, telas originais Vibração/Som, sincronização OS/menu, matrizes Mono/Stereo e retorno ao título. Auditoria: logs/pad-os-sound-audit-final.txt.

Próximos bloqueios reais: GX/TEV e classes HSD necessárias à construção dos Fighters; serviços AX/DSP, VI e demais dependências do link. Ainda não há Fighter criado, IA Link executando, colisão ECB completa ou combate. Os probes de gravidade e interseções existentes continuam diagnósticos isolados. Itens originais foram autorizados como escopo adicional, mas não foram integrados; a configuração diagnóstica continua item_freq=-1. O runtime de partida precisa existir antes de validar spawn, física, colisão e efeitos de itens. Nenhuma alteração na base original.

TrainingPreview tambem passou (logs/pad-os-sound-training.txt): navegacao Training/CSS/SSS, preparacao Battlefield ainda bloqueada para partida e retorno ao menu. XEX validada copiada para package/RGH/Melee360/default.xex; SHA256 atualizado em logs/RGH-image-sha256.json. Testes somente no Xenia.
