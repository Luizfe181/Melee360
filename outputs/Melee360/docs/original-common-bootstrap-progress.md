# Registro da etapa anterior — bloqueios de Mario resolvidos na revisão CPU

Veja original-cpu-match-progress.md para o estado atual: Fighter_Create retorna e o combate de lógica original executa com CPUs. O restante deste arquivo preserva as evidências da revisão anterior.

# Bootstrap original comum e pools de Fighter — 2026-10-03

## Executado e integrado

O boot normal agora usa lbFile_8001668C, lbArchive_LoadSymbols, Player_80036DD8 e Fighter_LoadCommonData. PdPm.dat e PlCo.dat passam pelo DevCom original, relocacao original e ligam os globais de Player/Fighter. O carregamento conserva os corpos originais de archive/common. Na fronteira nativa, a espera processa DVD/ARAM e a classificacao de enderecos usa ARGetSize. A expansao de nomes usa manifesto US-first (.usd/.dat); ainda nao reproduz as preferencias de idioma do save.

HSD_GObjInit original substitui as tabelas minimas manuais, com prioridade maxima 0x18 usada pelo Melee. O teste isolado executa Player_InitAllPlayers, lbDvd_80018F68 e Player_80036DA4/Fighter_FirstInitialize. Passou no Xenia; logs/common-pools-verification.txt e fighter-pools-runtime.log.

A biblioteca original e reconstruida antes do link Compat por prepare-original-runtime-library.ps1. Auditoria: zero simbolos ausentes e zero duplicacoes no caminho Mario/Link. Isto nao significa que uma partida funciona.

## Tentativa real de Fighter_Create

verify-original-bootstrap.ps1 -CreateMario chama Fighter_Create original com Mario e configuracao Player original. Carregou PlMr.dat, EfMrData.dat, PlMrNr.dat e PlMrAJ.dat (1.259.328 bytes). O banco de animacoes foi transferido para ARAM pelo DevCom original; a espera original restante tambem bombeia callbacks reais. Os buffers de relay de DevCom receberam alinhamento explicito de 32 bytes numa copia gerada, sem modificar a base.

Os marcadores confirmam retorno de ftData_80085B10, ftParts_80074E58, ftParts_SetupParts, ftAnim_80070308, ftCo_800C884C, Fighter_80068E64, ftParts_800749CC, ftAnim_8007077C, ftCo_8009CF84, ftAnim_8006FE48, Fighter_UnkUpdateVecFromBones_8006876C e ftCo_8009F578. Nao atingiu retorno valido de Fighter_Create em 45 segundos. Evidencia: logs/fighter-create-runtime.log. Nao foi produzido primeiro frame de gameplay.

O proximo trecho e ftData_OnLoad[Mario]. ftMr_Init_OnLoad registra Fire/Cape em it_804D6D38 via it_8026B3F8; esse bootstrap ainda nao instala o runtime comum de itens. Isso e uma dependencia identificada pela leitura do codigo, ainda requer instrumentacao/validacao propria. Depois seguem camera, shadow, spawn e inicializacao do estado de movimento. Nao foram substituidos por stubs nem pulados.

O diagnostico e isolado: fighter-bootstrap.flag e fighter-create.flag apenas na copia temporaria de teste. O boot normal nao chama Fighter_Create. O verificador remove suas flags e encerra apenas o processo que criou.

## Limites preservados

ARAM: o allocator ARAlloc e os heaps logicos originais ainda reservam a mesma regiao independentemente. O teste de criacao roda isolado e nao mistura bancos residentes com as vozes dos probes. A integracao conjunta exige reservas coordenadas antes de ativar uma partida.

Ainda faltam transicoes/reclaim de heaps, bootstrap completo de itens/camera/stage e dispatch original continuo. AX conserva depop L/R e PCM/ADPCM continuo ja implementados; aux/surround e demais modos DSP continuam incompletos. GX conserva as restricoes documentadas de RGBA6/AA/blend. Esta revisao nao completa toda a renderizacao/audio nem valida hardware real.

A base work/melee-base permanece intacta. As adaptacoes estao em diagnostics/generate_original_load.py, generate_bootstrap_memory.py, generate_hsd_runtime_pools.py e seus arquivos gerados. Proveniencia em logs/original-load-provenance.json e bootstrap-memory-provenance.json.

## Regressao e pacote

Training, Sound e Battlefield AA (quatro variantes, 120 updates cada) passaram no Xenia. Evidencias: logs/common-bootstrap-training.txt, common-bootstrap-sound.txt e common-bootstrap-aa-stage.txt. Os probes de depop AX e 28 pixels RGBA6 continuam passando. Callbacks de eventos Battlefield ainda nao suportados: 4/4/4/2.

Pacote atualizado apos os testes, sem flags diagnosticas: package/RGH/Melee360/default.xex. SHA256: F607170E03B17BFC638A62C2DA30F651414BE7E9B1D75A4786D54E13A4A932A7. Backup: C:\Users\luizf\Documents\Codex\2026-10-01\referenced-chatgpt-conversation-this-is-an-2\work\default-before-common-bootstrap-20261003-170422.xex. Manifesto: logs/common-bootstrap-package-verification.json. A criacao de Fighter continua bloqueada; nao ha partida.

