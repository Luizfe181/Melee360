# Catálogo: src/melee/gm

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/melee/gm/forward.h`

226 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/gm/gm_1601.c`

4383 linhas; 197 definições aparentes; 1 marcadores asm.

Includes: `gm_1601.h`, `Runtime/platform.h`, `melee/ft/forward.h`, `melee/pl/forward.h`, `placeholder.h`, `stddef.h`, `forward.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmscene.h`, `gmstamina.h`, `types.h`, `dolphin/mtx.h`, `dolphin/pad.h`, `melee/cm/camera.h`, `melee/gr/ground.h`, `melee/gr/stage.h`, `melee/if/ifstatus.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_013B.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/lb/lbtime.h`, `melee/mn/mnstagesel.h`, `melee/mn/types.h`, `melee/pl/player.h`, `melee/pl/plbonus.h`, `melee/pl/plbonuslib.h`, `melee/sc/types.h`, `melee/ty/toy.h`, `melee/ty/types.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/hsd_3924.h`, `sysdolphin/baselib/hsd_3982.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/video.h`

Definições aparentes: `gm_801601C4`, `gm_80160244`, `gm_801601C4_inner`, `gm_801601C4_noinline`, `gm_80160244_inner`, `gm_80160244_noinline`, `gm_801602C0`, `gm_801603B0`, `fn_80160400`, `gm_80160438`, `gm_80160474`, `gm_801604DC`, `gm_80160564`, `gm_SelKindToUnlockIndex`, `gm_CKindToUnlockIndex`, `get_unlockable_selkind_by_bit_index`, `gm_GetCKindByUnlockIndex`, `fn_80160710`, `gm_GetChallengerStKind`, `fn_801607A8`, `fn_801607F4`, `fn_80160840`, `gm_80160854`, `gm_80160968`, `gm_80160980`, `fn_801609E0`, `gm_80160A60`, `gm_80160B40_init_text`, `gm_80160B40`, `gm_80160C90`, `fn_80160DE8`, `fn_80160F58`, `fn_80161004`, `fn_80161154`, `fn_80161C90_count_players`, `fn_80161C90`, `fn_80162068`, `fn_80162170`, `gm_801623A4`, `gm_801623D8`, `gm_801623FC`, `gm_8016247C`, `gm_80162574`, `gm_SetupHumanResultsScreen`, `gm_GetVsPlayMatchTotal`, `gm_80162800`, `gm_SetupResultsScreenPlayTime`, `gm_80162968`, `gm_801629B4`, `gm_GetPlayTime`, `gm_80162A4C`, `gm_80162A98`, `gm_RecordSelfDestructs`, `gm_IncrementPowerCount`, `gm_80162BD8`, `fn_80162BFC`, `gm_80162C48`, `fn_80162CCC`, `gm_80162D1C`, `gm_80162D6C`, `gm_80162DD4`, `fn_80162DF8`, `gm_80162E44`, `gm_80162EC8`, `gm_80162F18`, `gm_80162F68`, `gm_80162FD0`, `fn_80162FF4`, `gm_80163040`, `fn_801630C4`, `gm_80163114`, `gm_80163164`, `gm_801631CC`, `gm_801631F0`, `gm_80163274`, `gm_80163298`, `gm_8016332C`, `gm_80163374`, `gm_801634D4`, `gm_8016365C`, `gm_80163690`, `gm_801636D8`, `gm_80163838`, `gm_801639C0`, `gm_801639F4`, `gm_80163A3C`, `gm_80163B9C`, `fn_80163D24`, `fn_80163D74`, `gm_Get3MinMultimanHighscore`, `gm_Get3MinMultimanTotalHighscore`, `gm_Get15MinMultimanHighscore`, `gm_Get15MinMultimanTotalHighscore`, `gm_GetEndlessHighscore`, `gm_GetEndlessTotalHighscore`, `gm_GetCruelHighscore`, `gm_GetCruelTotalHighscore`, `fn_80163FA4`, `gm_SelKindToCKind`, `gm_CKindToSelKind`, `gm_8016403C`, `fn_801640B0`, `fn_8016419C`, `fn_801641B4`, `gm_801641CC`, `gm_801641E4`, `gm_IsStageUnlocked`, `fn_801642A0`, `gm_80164330`, `getStageUnlockIndex`, `getStageUnlockNotifyId`, `gm_80164430`, `gm_80164504`, `gm_80164600`, `gm_8016468C`, `gm_801647D0`, `gm_801647F8`, `gm_IsCKindUnlocked`, `gm_UnlockCKind`, `gm_80164A0C`, `gm_80164ABC`, `is_character_unlocked`, `fn_80164B48`, `gm_8016505C`, `gm_80165084`, `fn_801650E8`, `gm_EnablePlayerPauseCamera`, `fn_80165190`, `fn_801651FC`, `gm_80165268`, `gm_80165290`, `fn_801652B0`, `fn_801652D8`, `gm_80165388`, `gm_801653C8`, `fn_801653E8`, `fn_80165418`, `fn_801654A0`, `fn_80165548`, `fn_801656A8`, `fn_8016588C_clamp`, `fn_8016588C`, `fn_80165AC0`, `fn_80165D60`, `fn_80165E7C`, `fn_80165FA4`, `fn_801661E0`, `gm_80166378`, `fn_80166A8C`, `gm_80166A98`, `fn_80166CBC`, `gm_80166CCC`, `gm_MatchHasMultipleWinners`, `fn_80167194`, `fn_8016719C`, `gm_80167320`, `gm_80167470`, `gm_801674C4`, `fn_8016758C`, `get_idx`, `fn_80167638`, `gm_801677C0`, `gm_801677E8`, `gm_801677F0`, `gm_RumbleEnabledForPlayer`, `gm_80167858`, `gm_801678F8`, `gm_SetupPlayerDefaults`, `gm_SetupAllPlayerDefaults`, `gm_SetupRulesDefaults`, `gm_InitVsMode`, `gm_80167BC8`, `pad_inline`, `get_flag_unk`, `gm_80167FC4`, `gm_801685D4`, `gm_80168638`, `gm_80168710`, `gm_801688AC`, `gm_80168940`, `gm_8016895C`, `fn_801689E4`, `fn_80168A6C`, `gm_80168B34`, `gm_80168BF8`, `gm_80168C5C`, `fn_80168E54`, `fn_80168F2C`, `fn_80168F7C`, `gm_80168F88`, `gm_LoadAnnouncer`, `fn_80169000`, `gm_GetNumCostumesForCKind`, `gm_80169264`, `gm_80169290`, `gm_801692BC`, `gm_801692E8`

## `src/melee/gm/gm_1601.h`

266 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/gm/forward.h`, `melee/mn/forward.h`, `melee/sc/forward.h`, `dolphin/gx.h`, `melee/mn/types.h`

## `src/melee/gm/gm_16A2.c`

982 linhas; 52 definições aparentes; 0 marcadores asm.

Includes: `gm_16A2.h`, `stddef.h`, `gm_unsplit.h`, `melee/gr/ground.h`, `melee/gr/stage.h`, `melee/if/ifnametag.h`, `melee/if/ifstatus.h`, `melee/lb/lb_00B0.h`, `melee/pl/player.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `gm_1601_GetUnkData`, `gm_80169370`, `gm_80169384`, `gm_80169394`, `fn_801693A8`, `gm_801693BC`, `fn_80169434`, `fn_80169444`, `gm_801694A0`, `gm_80169520`, `gm_80169530`, `gm_80169540`, `fn_80169550`, `fn_80169574`, `fn_801695BC_rand_color`, `fn_801695BC`, `fn_801697FC`, `fn_8016989C`, `fn_80169900`, `fn_80169A84`, `fn_80169C54_inline`, `fn_80169C54`, `fn_80169F50_inline`, `fn_80169F50`, `fn_8016A09C`, `gm_8016A164`, `fn_8016A1E4`, `gm_8016A1F8`, `gm_8016A21C`, `gm_8016A404_event_player_init_cb`, `gm_8016A22C_header`, `setCostumes`, `gm_8016A22C`, `gm_8016A404`, `gm_8016A414`, `gm_8016A424`, `gm_8016A434`, `fn_8016A450`, `fn_8016A46C`, `fn_8016A488`, `getSpawnPointIndex`, `fn_8016A4C8_attack_ratio`, `roll_cpu_type`, `hasDuplicateCostume`, `fn_8016A4C8`, `gm_8016A92C`, `gm_8016A944`, `gm_8016A97C`, `gm_8016A98C`, `gm_8016A998`, `gm_8016A9E8`, `gm_8016AC44`

## `src/melee/gm/gm_16A2.h`

52 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/mn/forward.h`, `sysdolphin/baselib/forward.h`

## `src/melee/gm/gm_16F1.c`

2445 linhas; 91 definições aparentes; 0 marcadores asm.

Includes: `gm_16F1.h`, `Runtime/platform.h`, `melee/pl/forward.h`, `gm_1601.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmvs.h`, `melee/if/textlib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lblanguage.h`, `melee/lb/lbtime.h`, `melee/mn/types.h`, `melee/pl/player.h`, `melee/pl/plbonus.h`, `melee/pl/plbonuslib.h`, `melee/ty/toy.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `fn_8016F180`, `gmDecisionGetType`, `fn_8016F1F0`, `gm_8016F208`, `fn_8016F280`, `gm_8016F2F8`, `fn_8016F344`, `fn_8016F39C_GetSisTextId`, `fn_8016F39C`, `fn_8016F548`, `fn_8016F740`, `fn_8016F870`, `fn_8016F9A8`, `fn_8016FAD4`, `fn_8016FFD4`, `fn_80170110`, `gm_801701A0`, `fn_801701AC`, `fn_801701B8`, `fn_801701C0`, `fn_80171A88`, `fn_80171AD4`, `fn_80171B00`, `fn_80171B2C`, `fn_80171B64`, `fn_80171BA4`, `fn_80171DC4`, `gm_801720B4`, `gm_801720F8`, `gm_80172140`, `gm_80172174`, `gm_8017219C`, `gm_801721EC_1`, `gm_801721EC_2`, `gm_801721EC_3`, `gm_801721EC_4`, `gm_801721EC`, `fn_801722BC`, `fn_801722F4`, `fn_8017232C`, `fn_80172380`, `fn_801723D4`, `fn_80172428`, `fn_80172478`, `fn_801724C8`, `fn_801724D0`, `fn_80172504`, `fn_80172538`, `fn_8017256C`, `fn_801725A8`, `fn_801725E4`, `fn_80172624`, `fn_80172664`, `fn_80172698`, `fn_801726CC`, `fn_80172700`, `fn_80172734`, `fn_80172768`, `fn_8017279C`, `fn_8017280C`, `tryUnlock`, `gm_80172898`, `gm_8017297C`, `inline3`, `gm_801729EC`, `gm_80172BC4`, `gm_80172C04`, `gm_80172C44`, `fn_80172C78`, `inline2`, `gm_DecideChallengerCpuLevel`, `gm_80172D78`, `inline1`, `gm_80172DD4`, `gm_80172E74`, `gm_80172F00`, `fn_80172FAC`, `fn_80173098_CountUnlocked`, `fn_80173098`, `gm_80173224`, `gm_801732D8`, `gm_8017335C`, `gm_801733D8`, `gm_8017341C`, `gm_80173460`, `gm_80173498`, `gm_801734D0`, `fn_80173510`, `fn_801735F0`, `fn_80173644`, `fn_8017367C`

## `src/melee/gm/gm_16F1.h`

115 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `sysdolphin/baselib/forward.h`

## `src/melee/gm/gm_1736.c`

435 linhas; 22 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `gm_1601.h`, `gm_16F1.h`, `gm_1A3F.h`, `gmevent.h`, `gmmain_lib.h`, `gmregclear.h`, `types.h`, `melee/if/textlib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lblanguage.h`, `melee/lb/lbtime.h`, `melee/ty/toy.h`

Definições aparentes: `gm_GetChallengerData`, `gm_InitChallengerData`, `gm_80173754`, `gm_801737D8`, `gm_Mode_ChallengerApproach_OnLoad`, `fn_80173834`, `unlockAdventureTrophies`, `unlockClassicTrophies`, `unlockAllStarTrophies`, `gm_8017390C`, `gm_80173AA4`, `gm_80173B30`, `gm_80173BC4`, `gm_80173C70`, `inline0`, `gm_80173D3C`, `gm_80173DE4`, `gm_80173EEC_inline`, `gm_80173EEC`, `gm_80174180`, `gm_801741FC`, `gm_80174238`

## `src/melee/gm/gm_1798.c`

642 linhas; 25 definições aparentes; 0 marcadores asm.

Includes: `gm_1798.h`, `placeholder.h`, `forward.h`, `gm_1601.h`, `gm_unsplit.h`, `gmresult.h`, `gmresultplayer.h`, `types.h`, `melee/cm/camera.h`, `melee/ef/efasync.h`, `melee/ef/eflib.h`, `melee/ft/ftdemo.h`, `melee/gr/ground.h`, `melee/gr/stage.h`, `melee/it/item.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00F9.h`, `melee/lb/lbarchive.h`, `melee/lb/lbbgflash.h`, `melee/lb/lbspdisplay.h`, `melee/mp/mpcoll.h`, `melee/pl/player.h`, `melee/sc/types.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `sdata2_order`, `fn_80179854`, `get_big_loser`, `fn_80179990_img_at`, `fn_80179990_set_erase_color`, `fn_80179990_copy_efb`, `fn_80179990_copy_efb_at`, `fn_80179990`, `fn_80179D3C`, `fn_80179D60`, `fn_80179D84`, `fn_80179DA8`, `fn_80179DCC`, `fn_80179E34`, `fn_80179E9C`, `fn_80179F04`, `fn_80179F6C`, `fn_80179F84`, `fn_8017A004`, `fn_8017A078`, `fn_8017A318`, `fn_8017A67C`, `inline1`, `fn_8017A9B4`, `fn_8017AA78`

## `src/melee/gm/gm_1798.h`

30 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `sysdolphin/baselib/forward.h`, `melee/gm/gmresultplayer.h`

## `src/melee/gm/gm_17AD.c`

347 linhas; 36 definições aparentes; 0 marcadores asm.

Includes: `gm_17AD.h`, `melee/pl/forward.h`, `gmresult.h`, `inlines.h`, `types.h`, `melee/lb/lblanguage.h`

Definições aparentes: `fn_8017AD04`, `clampKOs`, `getKOs`, `fn_8017AD28`, `fn_8017AD48`, `fn_8017AD78`, `fn_8017ADA8`, `fn_8017AE0C`, `fn_8017AE70`, `fn_8017AED8`, `fn_8017AF40`, `fn_8017AFA8`, `fn_8017B010`, `fn_8017B07C`, `fn_8017B0E4`, `fn_8017B14C`, `fn_8017B1B4`, `fn_8017B21C`, `fn_8017B280`, `fn_8017B2E4`, `fn_8017B348`, `fn_8017B3AC`, `fn_8017B410`, `fn_8017B4D0`, `fn_8017B534`, `fn_8017B598`, `fn_8017B5FC`, `fn_8017B660`, `fn_8017B6C4`, `fn_8017B728`, `fn_8017B78C`, `fn_8017B7F0`, `fn_8017B854`, `fn_8017B8B8`, `fn_8017B91C`, `fn_8017B9F4`

## `src/melee/gm/gm_17AD.h`

41 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/gm/gm_17BA.c`

88 linhas; 7 definições aparentes; 0 marcadores asm.

Includes: `gm_17BA.h`, `gm_17AD.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmresult.h`, `inlines.h`, `types.h`, `melee/lb/lblanguage.h`

Definições aparentes: `fn_8017BACC`, `fn_8017BB30`, `fn_8017BB94_inline`, `fn_8017BB94`, `fn_8017BC50`, `fn_8017BD0C`, `fn_8017BDC8`

## `src/melee/gm/gm_17BA.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gm_17C0.c`

965 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `forward.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmregclear.h`, `gmregcommon.h`, `types.h`, `melee/cm/camera.h`, `melee/db/db.h`, `melee/ft/ft_0877.h`, `melee/ft/ftbosslib.h`, `melee/ft/ftlib.h`, `melee/gr/ground.h`, `melee/gr/grpushon.h`, `melee/gr/stage.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbbgflash.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lbtime.h`, `melee/pl/player.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `fn_8017C0C8`, `fn_8017C1A4`, `fn_8017C71C`, `fn_8017C7A0`, `fn_8017C7EC`, `gm_8017C838`, `gm_8017C984`, `gm_8017C9A8`, `gm_8017CA38`, `gm_8017CBAC`, `gm_8017CD94`, `gm_8017CE34_CountEnemies`, `gm_8017CE34_SetupColors`, `gm_8017CE34_GetCpuLevel`, `gm_8017CE34`, `gm_8017D7AC`, `pick_random_ckind`, `fn_8017D9C0`

## `src/melee/gm/gm_17DB.c`

306 linhas; 17 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `forward.h`, `gm_18A1.h`, `gm_unsplit.h`, `gmregclear.h`, `types.h`, `melee/ty/toy.h`

Definições aparentes: `gm_8017DB58`, `gm_8017DB6C`, `gm_8017DB78`, `gm_8017DB88`, `fn_8017DD7C`, `fn_8017DE54`, `fn_8017DEC8`, `fn_8017DF28`, `fn_8017DF90`, `gm_8017DFF4`, `gm_8017E068`, `fn_8017E0E4`, `fn_8017E160`, `fn_8017E21C`, `gm_8017E280`, `fn_8017E318`, `fn_8017E3C8`

## `src/melee/gm/gm_17E4.c`

400 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `forward.h`, `gm_unsplit.h`, `gmadventure.h`, `gmmain_lib.h`, `gmregclear.h`, `types.h`, `melee/if/ifstatus.h`, `melee/pl/player.h`

Definições aparentes: `gm_GetAdventureData`, `gm_8017E430`, `gm_8017E440`, `gm_8017E48C`, `gm_8017E4C4`, `gm_8017E500`, `gm_8017E528`, `gm_8017E578`, `gm_8017E5C8`, `gm_8017E5FC`, `gm_8017E630`, `gm_8017E664`, `gm_8017E6B4`, `gm_8017E704`, `gm_8017E738`, `gm_8017E76C`, `gm_8017E7A0`, `gm_8017E7E0`, `gm_8017E7FC`, `getCurrentStage`, `fn_8017E8A4`

## `src/melee/gm/gm_17EB.c`

222 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `forward.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmregclear.h`, `types.h`, `melee/pl/player.h`

Definições aparentes: `gm_GetAllStarData`, `gm_8017EB3C`, `gm_8017EB64`, `gm_8017EB98`, `gm_8017EBCC`, `gm_8017EC00`, `gm_8017EC50`, `gm_8017ECA0`, `gm_8017ECD4`, `gm_8017ED08`, `gm_8017ED3C`, `gm_8017ED8C`, `fn_8017EDDC`, `fn_8017EE40`

## `src/melee/gm/gm_180A.c`

366 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmregclear.h`, `melee/gr/ground.h`, `melee/if/iftime.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/pl/player.h`, `melee/sc/types.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `gm_80180AE4`, `gm_80180AF4`, `gm_80180B18`, `gm_80180BA0`, `fn_80180C14`, `fn_80180C60`, `fn_80181598`, `fn_80181708`, `gm_80181998`, `gm_80181A00`

## `src/melee/gm/gm_181A.c`

1072 linhas; 27 definições aparentes; 0 marcadores asm.

Includes: `gm_181A.h`, `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `forward.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmregclear.h`, `types.h`, `dolphin/pad.h`, `melee/cm/camera.h`, `melee/if/ifnametag.h`, `melee/if/ifstock.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/mn/inlines.h`, `melee/pl/player.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `gm_80181A14`, `gm_80181A24`, `gm_80181A34`, `gm_80181A44`, `gm_80181AC8`, `gm_80181B64`, `fn_80181BFC`, `fn_80181C80_CountPlayers`, `fn_80181C80`, `countActiveOpponents`, `fn_80181E18`, `gm_80182174`, `gm_IsMultimanSmashMode`, `gm_80182554`, `gm_80182578_GetTimeFromData`, `gm_80182578_GetRecordTime`, `gm_80182578_GetRecordScore`, `gm_80182578_GetIndexFromPointer`, `gm_80182578_SetTime`, `gm_80182578`, `fn_80182B5C_GetRecordBlocks`, `fn_80182B5C_GetScore`, `fn_80182B5C_GetTime`, `fn_80182B5C`, `gm_80182DF0`, `fn_80182F40`, `gm_80183218`

## `src/melee/gm/gm_181A.h`

16 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/gm/gm_1832.c`

1164 linhas; 36 definições aparentes; 0 marcadores asm.

Includes: `gm_1832.h`, `gm_1601.h`, `gm_unsplit.h`, `gmscene.h`, `melee/cm/camera.h`, `melee/ef/efasync.h`, `melee/ef/eflib.h`, `melee/ft/ftdemo.h`, `melee/gr/ground.h`, `melee/gr/stage.h`, `melee/it/item.h`, `melee/lb/lb_00F9.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/mn/mnname.h`, `melee/mp/mpcoll.h`, `melee/pl/player.h`, `melee/sc/types.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/sobjlib.h`, `sysdolphin/baselib/state.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/util.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `fn_8018325C`, `fn_80184138`, `fn_801849E0`, `fn_80184A04`, `fn_80184A28`, `fn_80184A4C`, `fn_80184A70`, `fn_80184A94`, `fn_80184AB8`, `fn_8018504C`, `fn_801851C0`, `fn_801852FC`, `gm_1832_sdata2_order`, `fn_80185408`, `fn_801855BC`, `fn_8018564C`, `fn_8018569C`, `fn_8018575C`, `fn_801857C4`, `fn_801859C8`, `fn_80185A0C_Tail`, `fn_80185A0C`, `fn_80185D64`, `fn_80185E34`, `fn_80185F5C`, `fn_80186080`, `fn_801861B8`, `fn_80186400`, `gm_80186634_LoadLightList`, `gm_80186634_SetupLight`, `gm_80186634_SetupCamera`, `gm_80186634_SetupModel`, `gm_80186634_SetupFog`, `fn_80186634`, `gm_Scene_IntroEasy_OnFrame`, `gm_Scene_IntroEasy_OnEnter`

## `src/melee/gm/gm_1832.h`

80 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`

## `src/melee/gm/gm_186E.c`

253 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `gm_186E.h`, `gm_1601.h`, `gm_unsplit.h`, `gmscene.h`, `melee/cm/camera.h`, `melee/ef/efasync.h`, `melee/ef/eflib.h`, `melee/ft/ftdemo.h`, `melee/gr/ground.h`, `melee/gr/stage.h`, `melee/it/item.h`, `melee/lb/lb_00F9.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbspdisplay.h`, `melee/mp/mpcoll.h`, `melee/pl/player.h`, `melee/sc/types.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `fn_80186EFC`, `fn_80186F6C`, `fn_801873F0`, `fn_80187494`, `fn_801874FC`, `fn_80187714`, `gm_Scene_IntroAllstar_OnFrame`, `setupScene`, `gm_Scene_IntroAllstar_OnEnter`

## `src/melee/gm/gm_186E.h`

17 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `placeholder.h`

## `src/melee/gm/gm_1879.c`

441 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `gm_1879.h`, `gm_1A36.h`, `gm_1A3F.h`, `gm_unsplit.h`, `gmscene.h`, `types.h`, `dolphin/pad.h`, `melee/cm/camera.h`, `melee/ef/efasync.h`, `melee/ef/eflib.h`, `melee/gr/ground.h`, `melee/gr/stage.h`, `melee/it/item.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00F9.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbbgflash.h`, `melee/lb/lbspdisplay.h`, `melee/mn/inlines.h`, `melee/mp/mpcoll.h`, `melee/pl/player.h`, `melee/sc/types.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/state.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `fn_80187AB4_LoadAnim`, `fn_80187910`, `fn_80187AB4`, `fn_80187C9C`, `fn_80187CF4`, `getStKind`, `gm_80187F48_GetAudioConfig`, `gm_80187F48_OnEnter_inline`, `gm_Scene_IntroNormal_OnEnter`, `gm_Scene_IntroNormal_OnLeave`, `gm_Scene_IntroNormal_OnFrame`, `gm_801883C0`, `gm_8018841C`

## `src/melee/gm/gm_1879.h`

18 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `placeholder.h`

## `src/melee/gm/gm_1884.c`

933 linhas; 23 definições aparentes; 0 marcadores asm.

Includes: `gm_1884.h`, `melee/it/forward.h`, `gm_1601.h`, `gm_1A36.h`, `gm_unsplit.h`, `gmscene.h`, `types.h`, `dolphin/pad.h`, `melee/gr/stage.h`, `melee/if/ifall.h`, `melee/if/ifstatus.h`, `melee/it/itspawn.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_0195.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/mn/inlines.h`, `melee/mn/types.h`, `melee/pl/pl_040D.h`, `melee/pl/player.h`, `melee/sc/types.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `gm_1884_sdata2_order`, `TrainingItemTable_Get`, `gm_80188454`, `fn_8018846C`, `fn_801884F8`, `fn_80188550`, `fn_80188644`, `fn_80188738`, `fn_8018846C_noInline`, `fn_80188910`, `fn_801884F8_noinline`, `fn_801884F8_noinline_2`, `fn_80188B3C`, `fn_80188D3C`, `fn_80188EE8`, `gm_801891F4_GetTickRate`, `gm_801891F4_GetMenuValues`, `gm_801891F4_SetCpuType`, `fn_801891F4`, `fn_80189B88`, `gm_80189CDC`, `resetText`, `fn_8018A000`

## `src/melee/gm/gm_1884.h`

24 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `melee/gm/types.h`

## `src/melee/gm/gm_18A1.c`

204 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `gm_18A1.h`, `gmmain_lib.h`, `gmregclear.h`, `gmvs.h`, `types.h`, `melee/pl/player.h`

Definições aparentes: `gm_8018A160`, `gm_8018A188`, `gm_8018A1D8`, `gm_8018A228`, `gm_8018A25C`, `gm_8018A290`, `gm_8018A2C4`, `gm_8018A314`, `fn_8018A364`

## `src/melee/gm/gm_18A1.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `dolphin/types.h`

## `src/melee/gm/gm_19EF.c`

761 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `gm_19EF.h`, `gm_1601.h`, `gm_1A36.h`, `gm_1A3F.h`, `gm_unsplit.h`, `gmscene.h`, `dolphin/pad.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbspdisplay.h`, `melee/mn/inlines.h`, `melee/sc/types.h`, `melee/ty/toy.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `fn_8019EFC4`, `fn_8019F1D0`, `fn_8019F2D4_inline1`, `fn_8019F2D4_inline2`, `fn_8019F2D4`, `fn_8019F6EC`, `fn_8019F810`, `fn_8019F9C4_GetCharIdx`, `fn_8019F9C4_LoadSymbols`, `fn_8019F9C4_inline1`, `fn_8019F9C4_inline2`, `fn_8019F9C4_inline3`, `fn_8019F9C4`, `gm_Scene_GOver_OnEnter`, `gm_Scene_GOver_OnExit`, `fn_801A0B60`, `gm_Scene_ComingSoon_OnEnter`, `gm_Scene_ComingSoon_OnExit`

## `src/melee/gm/gm_19EF.h`

13 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/gm/gm_1A33.c`

112 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `gm_1A33.h`, `gm_1A36.h`, `gmcamera.h`, `gmscene.h`, `types.h`, `dolphin/pad.h`, `melee/lb/lbsnap.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `gmCamera_801A33BC`, `gm_Scene_CameraVs_OnFrame`, `gm_Scene_CameraVs_OnEnter`, `gm_Scene_CameraVs_OnExit`

## `src/melee/gm/gm_1A33.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `placeholder.h`

## `src/melee/gm/gm_1A36.c`

205 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `gm_1A36.h`, `Runtime/platform.h`, `gmscdata.h`, `types.h`, `dolphin/pad.h`, `sysdolphin/baselib/controller.h`

Definições aparentes: `gm_GetButtonsPressed`, `gm_GetButtonsTriggered`, `gm_801A36C0`, `gm_801A36E0`, `gm_801A3714`, `gm_801A3820`, `fn_801A396C`, `mapButtons`, `copyStatus`, `updatePad`, `gm_EvaluateAllControllerInputs`, `gm_801A3E88`, `gm_801A3EF4`

## `src/melee/gm/gm_1A36.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/gm/gm_1A3F.c`

398 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `gm_1A3F.h`, `gm_1A36.h`, `gmmain_lib.h`, `gmscdata.h`, `gmscene.h`, `types.h`, `dolphin/vi.h`, `melee/db/db.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lbdvd.h`, `melee/lb/lbheap.h`, `melee/lb/lbmthp.h`, `melee/lb/lbsnap.h`, `melee/lb/types.h`, `melee/ty/toy.h`, `melee/ty/tydisplay.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/devcom.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/video.h`

Definições aparentes: `preloadState`, `firstState`, `nextState`, `findState`, `gm_801A4014`, `gm_GetGameModeStateEnterData`, `gm_GetGameModeStateExitData`, `gm_SetGameModeStateId`, `gm_SetNextGameModeStateId`, `gm_GetPreviousSceneIndex`, `gm_GetCurrentSceneIndex`, `gm_SetNewGameModePending`, `gm_SetPendingGameMode`, `gm_ChangeGameModeAfterCurrentScene`, `gm_GetCurrentGameMode`, `gm_GetPreviousGameMode`, `gm_SetGameModeOverride`, `gm_Is1PMode`, `findMode`, `runGameMode`, `gm_801A4510`

## `src/melee/gm/gm_1A3F.h`

100 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`

## `src/melee/gm/gm_1A7A.c`

154 linhas; 8 definições aparentes; 0 marcadores asm.

Includes: `gm_1A7A.h`, `gm_unsplit.h`, `gmevent.h`, `gmregtyfall.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbspdisplay.h`, `melee/mn/mnmain.h`, `melee/sc/types.h`, `melee/ty/toy.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`

Definições aparentes: `fn_801A7A44`, `fn_801A7A68`, `fn_801A7A8C`, `setupLight`, `setupCamera`, `setupMain`, `setupCharacter`, `gm_801A7B00`

## `src/melee/gm/gm_1A7A.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `placeholder.h`

## `src/melee/gm/gm_1A9B.c`

166 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `forward.h`, `gm_1A36.h`, `gm_1A3F.h`, `gm_1A7A.h`, `gmevent.h`, `gmregclear.h`, `gmregtyfall.h`, `dolphin/pad.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbbgflash.h`, `melee/lb/lbmthp.h`, `melee/mn/inlines.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/sobjlib.h`

Definições aparentes: `gm_Scene_Congrats_OnEnter`, `gm_Scene_Congrats_OnFrame`

## `src/melee/gm/gm_1ADD.c`

394 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `gm_1ADD.h`, `gm_unsplit.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lblanguage.h`, `melee/sc/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `gm_801ADDD8`, `gm_801ADE1C`, `gm_801AE050`, `gm_801AE44C`, `gm_801AE544`, `gm_801AE640`, `gm_801AE74C`, `gm_801AE848`, `fn_801AE948`, `gm_801AEBB0`, `gm_801AECC4`, `get_master_status`, `get_copy_status`, `gm_801AEDC8`

## `src/melee/gm/gm_1ADD.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/gm/gm_1B03.c`

218 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `gm_1B03.h`, `melee/mn/forward.h`, `melee/pl/forward.h`, `gm_unsplit.h`, `types.h`, `dolphin/types.h`, `melee/mn/types.h`

Definições aparentes: `gm_SetupSubColors`, `player_standings_inline`, `gm_801B0474_inline`, `gm_SetupSuddenDeath`, `gm_801B05F4`, `gm_SetupHumanPlayer`, `gm_SetupCpuPlayer`, `gm_801B06B0`, `gm_801B0730`, `gm_801B07B4`, `gm_801B07E8`

## `src/melee/gm/gm_1B03.h`

22 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/mn/forward.h`, `melee/gm/types.h`

## `src/melee/gm/gm_1BFA.c`

247 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `gm_1BFA.h`, `melee/lb/forward.h`, `forward.h`, `gm_unsplit.h`, `gmapproach.h`, `gmmain_lib.h`, `gmvsmelee.h`, `types.h`, `melee/if/if_2FD9.h`, `melee/lb/inlines.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbtime.h`, `melee/ty/toy.h`, `sysdolphin/baselib/memory.h`

Definições aparentes: `gm_ModeState_Approach_OnEnter`, `gm_ModeState_ApproachVs_OnEnter`, `onExitVs`, `gm_801BFC60`, `gm_ModeState_Prize_OnEnter`, `onExitPrize`

## `src/melee/gm/gm_1BFA.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`

## `src/melee/gm/gm_unsplit.h`

36 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/gm_1601.h`, `melee/gm/gm_16A2.h`, `melee/gm/gm_16F1.h`, `melee/gm/gm_17AD.h`, `melee/gm/gm_17BA.h`, `melee/gm/gm_1832.h`, `melee/gm/gm_186E.h`, `melee/gm/gm_1879.h`, `melee/gm/gm_19EF.h`, `melee/gm/gm_1A36.h`, `melee/gm/gm_1A3F.h`, `melee/gm/gm_1A7A.h`, `melee/gm/gm_1ADD.h`, `melee/gm/gm_1B03.h`, `melee/gm/gm_1BFA.h`, `melee/gm/gmevent.h`, `melee/gm/gmregclear.h`, `melee/gm/gmscene.h`, `melee/gm/gmscmemcard.h`, `melee/gm/gmtoulib.h`, `melee/gm/gmvs.h`

## `src/melee/gm/gmadventure.c`

1772 linhas; 36 definições aparentes; 0 marcadores asm.

Includes: `gmadventure.h`, `forward.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmregcommon.h`, `melee/gr/ground.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `getIndex`, `setValUnk`, `gm_801B3F40`, `gm_801B4064`, `gm_801B4170`, `gm_801B4254`, `gm_801B4294`, `gm_801B42E8`, `gm_801B4350`, `gm_801B4408`, `gm_801B4430`, `gm_801B44A0`, `gm_801B45A4`, `gm_801B461C`, `gm_801B4684`, `gm_801B4768`, `gm_801B47FC`, `gm_801B4860_inline0`, `gm_801B4860_inline1`, `gm_801B4860`, `gm_8016A22C_inline`, `gm_801B4974`, `inline0`, `gm_801B4B28`, `gm_801B4C5C`, `gm_801B4D34`, `gm_801B4DAC`, `gm_801B4E58`, `gm_801B4EB8`, `gm_801B4F44`, `gm_801B4FCC`, `gm_801B5078`, `gm_801B50C4`, `gm_801B518C`, `gm_Mode_Adventure_OnInit`, `gm_Mode_Adventure_OnLoad`

## `src/melee/gm/gmadventure.h`

39 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmallstar.c`

824 linhas; 16 definições aparentes; 0 marcadores asm.

Includes: `gmallstar.h`, `gm_18A1.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmregcommon.h`, `dolphin/types.h`, `melee/gr/ground.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbbgflash.h`, `melee/lb/lbdvd.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `gm_801B5324_inline`, `gm_801B5324`, `gm_801B5624_inline`, `gm_801B5624`, `gm_801B59AC`, `fn_801B5AA8`, `gm_801B5ACC_inline1`, `gm_801B5ACC`, `gm_801B5E7C`, `gm_801B5EB4`, `gm_801B5EE4`, `gm_801B5F50`, `gm_801B5FB4`, `gm_801B607C`, `gm_Mode_AllStar_OnLoad`, `gm_Mode_AllStar_OnInit`

## `src/melee/gm/gmallstar.h`

22 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmapproach.c`

159 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `gmapproach.h`, `gm_unsplit.h`, `gmscene.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `fn_801AD920`, `gm_801ADB04`, `gm_Scene_Approach_OnFrame`, `gm_Scene_Approach_OnEnter`, `gm_Scene_Approach_OnExit`

## `src/melee/gm/gmapproach.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmboot.c`

105 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `gm_unsplit.h`, `gmmain_lib.h`, `types.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lblanguage.h`, `melee/ty/toy.h`

Definições aparentes: `bootOnLoad`, `bootOnLeave`, `memcardOnLoad`

## `src/melee/gm/gmboot.h`

4 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gmcamera.c`

600 linhas; 27 definições aparentes; 0 marcadores asm.

Includes: `gmcamera.h`, `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `gm_1601.h`, `gmpause.h`, `gmscene.h`, `gmvs.h`, `types.h`, `dolphin/pad.h`, `melee/cm/cmsnap.h`, `melee/if/ifall.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardnew.h`, `melee/lb/lbsnap.h`, `melee/lb/lbspdisplay.h`, `melee/mn/inlines.h`, `melee/sc/types.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/sislib_font.h`

Definições aparentes: `gmCamera_801A2224`, `gmCamera_801A2334`, `gmCamera_801A253C`, `gmCamera_801A25C8`, `gmCamera_801A2640`, `gmCamera_801A2650`, `freeTexts`, `gmCamera_801A26C0`, `gmCamera_801A2798`, `gmCamera_801A2800`, `gmCamera_801A28AC`, `gmCamera_801A292C`, `gmCamera_801A2AAC`, `gmCamera_801A2BB0`, `gmCamera_801A2BF0_get_translate_x`, `gmCamera_801A2BF0_get_jobj`, `gmCamera_801A2BF0`, `gmCamera_801A2D44_update_selection`, `gmCamera_801A2D44`, `gmCamera_801A2FBC`, `gmCamera_801A2FFC`, `gmCamera_801A3048`, `gmCamera_801A3098`, `gmCamera_801A30E4`, `fn_801A31D8`, `gmCamera_801A31FC_inline`, `gmCamera_801A31FC`

## `src/melee/gm/gmcamera.h`

63 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `dolphin/types.h`

## `src/melee/gm/gmcameramode.c`

249 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `gmcameramode.h`, `melee/lb/forward.h`, `gm_1A3F.h`, `gm_1B03.h`, `gm_unsplit.h`, `gmcamera.h`, `gmmain_lib.h`, `gmvsmelee.h`, `types.h`, `dolphin/os.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardnew.h`, `melee/lb/lbdvd.h`, `melee/lb/lbsnap.h`, `melee/lb/types.h`, `melee/mn/types.h`

Definições aparentes: `gm_801B23F0`, `gm_801B24B4`, `gm_801B2510`, `gm_801B254C`, `gm_801B25D4`, `gm_801B26AC`, `gm_801B2704`, `gm_PrepCameraModeVSScene`, `gm_801B2AF8`, `gm_Mode_Camera_OnInit`

## `src/melee/gm/gmcameramode.h`

18 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmclassic.c`

1091 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `gmclassic.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmregcommon.h`, `melee/gr/ground.h`, `melee/gr/stage.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbdvd.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `gmClassic_InitMatchupOrder`, `gmClassic_GetMatchupCount`, `gmClassic_801B2BA4`, `gmClassic_801B2D54`, `gm_Mode_Classic_OnLoad`, `gm_Mode_Classic_OnInit`, `gmClassic_GetStKind`, `gmClassic_801B3500`, `gmClassic_801B3A34`, `gmClassic_801B3B40`, `gmClassic_801B3D44`, `gmClassic_801B3D84`, `gmClassic_801B3DD8`, `gmClassic_801B3E44`, `gmClassic_801B3F18`

## `src/melee/gm/gmclassic.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/gm/types.h`

## `src/melee/gm/gmdebugmode.c`

475 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `melee/mn/forward.h`, `gm_1A3F.h`, `gm_unsplit.h`, `gmresultplayer.h`, `types.h`, `dolphin/types.h`, `melee/if/if_2FFC.h`, `melee/if/if_3004.h`, `melee/lb/lbaudio_ax.h`, `melee/mn/inlines.h`, `melee/mn/types.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `onExitIntro`, `onEnterMenu0`, `fn_801B09F8`, `onEnterMenu1`, `fn_801B0A8C`, `onEnterMenu2`, `onEnterPrize`, `onExitPrize`, `onEnterVs`, `onEnterResults0`, `onExitResults0`, `onEnterIntroEasy`, `onEnterIntroAllstar`, `onEnterGameOver`, `onEnterApproach`, `onEnterResults1`, `onExitResults1`, `onEnterMemCard`, `onExitMemCard`

## `src/melee/gm/gmdebugmode.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmevent.c`

2368 linhas; 60 definições aparentes; 0 marcadores asm.

Includes: `gmevent.h`, `melee/ft/forward.h`, `melee/pl/forward.h`, `gm_1601.h`, `gm_16F1.h`, `gm_unsplit.h`, `gmmain_lib.h`, `types.h`, `melee/cm/camera.h`, `melee/ft/ftbosslib.h`, `melee/ft/ftlib.h`, `melee/gr/ground.h`, `melee/if/ifstock.h`, `melee/it/kinds/itevyoshiegg.h`, `melee/lb/lb_0219.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbbgflash.h`, `melee/lb/lbdvd.h`, `melee/lb/types.h`, `melee/mn/types.h`, `melee/pl/player.h`, `melee/pl/plbonuslib.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/random.h`, `MetroTRK/intrinsics.h`

Definições aparentes: `gm_801BA8FC`, `gm_801BA938`, `onEnterCss`, `onExitCss`, `gm_801BAB40`, `gm_801BAC9C`, `gm_GetEventData`, `gm_GetNextColor`, `onEnterVs`, `onExitVs`, `gm_Mode_Event_OnInit`, `gm_801BBB64_inline`, `gm_801BBB64`, `gm_Mode_Event_OnLoad`, `gm_Mode_Event_OnUnload`, `fn_801BBFE8`, `gm_801BC00C_inline`, `gm_801BC00C_GetCharacter`, `gm_801BC00C_GetCharacterKind`, `gm_801BC00C`, `gm_801BC488`, `gm_801BC4F4`, `gm_801BC670`, `failEvent`, `gm_801BC754`, `gm_801BC9E8`, `gm_801BCAF0`, `gm_801BCC9C`, `gm_801BCF20`, `gm_801BCF40`, `gm_801BD028`, `gm_801BD164`, `gm_801BD30C`, `gm_801BD44C`, `gm_801BD46C`, `gm_801BD658`, `gm_801BD7FC`, `gm_801BD93C`, `gm_801BDAD4`, `gm_801BDAF4`, `gm_801BDC08`, `gm_801BDD44`, `gm_801BDE94`, `gm_801BE37C`, `gm_801BE39C`, `gm_801BE618`, `gm_801BE638`, `gm_801BEA10`, `gm_801BEA4C`, `gm_801BEA88`, `gm_801BEAF0`, `gm_801BEB2C`, `gm_801BEB68`, `gm_801BEB74`, `gm_801BEB80`, `gm_801BEB8C`, `gm_801BEBA8`, `gm_801BEBC0`, `gm_801BEBF8`, `gm_801BEC54`

## `src/melee/gm/gmevent.h`

38 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/gm/types.h`

## `src/melee/gm/gmfixedcamera.c`

182 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `gmfixedcamera.h`, `gm_unsplit.h`, `gmapproach.h`, `gmmain_lib.h`, `gmmovieend.h`, `gmvsmelee.h`, `types.h`, `melee/if/if_2FD9.h`, `melee/mn/types.h`

Definições aparentes: `gm_801B9F10`, `gm_801B9F3C`, `gm_801B9F64`, `gm_801B9F8C`, `fn_801B9FB8`, `gm_801B9FC8`, `gm_801B9FFC`, `gm_801BA024`, `gm_801BA058`, `gm_801BA078`, `gm_801BA098`, `gm_Mode_CameraVs_OnInit`, `gm_Mode_CameraVs_OnLoad`

## `src/melee/gm/gmfixedcamera.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/mn/forward.h`

## `src/melee/gm/gmgiant.c`

183 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `gmgiant.h`, `gm_unsplit.h`, `gmapproach.h`, `gmmain_lib.h`, `gmmovieend.h`, `gmvsmelee.h`, `types.h`, `melee/if/if_2FD9.h`

Definições aparentes: `gm_801B8FB8`, `gm_801B8FE4`, `gm_801B900C`, `gm_801B9034`, `fn_801B9060`, `gm_801B9084`, `gm_801B90B8`, `gm_801B90E0`, `gm_801B9114`, `gm_801B9134`, `gm_801B9154`, `gm_Mode_GiantVs_OnInit`, `gm_Mode_GiantVs_OnLoad`

## `src/melee/gm/gmgiant.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/mn/forward.h`

## `src/melee/gm/gmgover.c`

185 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `gm_1601.h`, `gm_16F1.h`, `gm_unsplit.h`, `gmevent.h`, `types.h`, `melee/lb/lbmthp.h`

Definições aparentes: `gm_801BEE9C`, `gm_801BEF84`, `gm_801BEFA4`, `gm_801BEFB0`, `gm_801BEFC0`, `gm_801BEFD0`, `gm_801BEFE0`, `gm_801BEFF0`, `gm_801BF000`, `gm_801BF010`, `gm_801BF020`, `gm_801BF030`, `gm_801BF040`, `gm_801BF050`

## `src/melee/gm/gmgover.h`

4 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gmhanyucss.c`

54 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `gm_1601.h`, `gm_unsplit.h`, `gmvsmelee.h`, `types.h`, `melee/mn/types.h`

Definições aparentes: `gm_801BED3C`, `gm_801BEDA8`

## `src/melee/gm/gmhanyucss.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmhanyusss.c`

30 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `gm_unsplit.h`, `gmmain_lib.h`, `types.h`, `melee/lb/types.h`, `melee/mn/types.h`

Definições aparentes: `gm_801BEE58`

## `src/melee/gm/gmhanyusss.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmhomerun.c`

184 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `gmhomerun.h`, `melee/pl/forward.h`, `forward.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmvsmelee.h`, `types.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lbdvd.h`, `melee/lb/lbtime.h`, `melee/lb/types.h`, `melee/mn/types.h`

Definições aparentes: `gm_801B98E8`, `gm_801B999C`, `gm_801B9A3C`, `gm_801B9DD8`, `gm_Mode_Homerun_OnInit`, `gm_Mode_Homerun_OnLoad`

## `src/melee/gm/gmhomerun.h`

16 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/mn/types.h`

## `src/melee/gm/gmhowto.c`

83 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `gmhowto.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmopening.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbmthp.h`, `melee/mn/inlines.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/sobjlib.h`

Definições aparentes: `gm_801ACC94`, `gm_Scene_HowTo_OnEnter`, `gm_Scene_HowTo_OnFrame`

## `src/melee/gm/gmhowto.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `placeholder.h`

## `src/melee/gm/gminvisible.c`

198 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `gminvisible.h`, `gm_unsplit.h`, `gmapproach.h`, `gmmain_lib.h`, `gmmovieend.h`, `gmvsmelee.h`, `gmvsmode.h`, `types.h`, `melee/if/if_2FD9.h`, `melee/mn/types.h`

Definições aparentes: `onEnterCss`, `onExitCss`, `onEnterSss`, `onExitSss`, `initVsPlayer`, `onEnterVs`, `onExitVs`, `onEnterSuddenDeath`, `onExitSuddenDeath`, `onEnterResults`, `onExitResults`, `gm_Mode_InvisibleVs_OnInit`, `gm_Mode_InvisibleVs_OnLoad`

## `src/melee/gm/gminvisible.h`

7 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gmlightning.c`

184 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `gmlightning.h`, `gm_unsplit.h`, `gmapproach.h`, `gmmain_lib.h`, `gmmovieend.h`, `gmvsmelee.h`, `gmvsmode.h`, `types.h`, `melee/if/if_2FD9.h`

Definições aparentes: `gm_801BA704`, `gm_801BA730`, `gm_801BA758`, `gm_801BA780`, `fn_801BA7AC`, `gm_801BA7B8`, `gm_801BA7EC`, `gm_801BA814`, `gm_801BA848`, `gm_801BA868`, `gm_801BA888`, `gm_Mode_LightningVs_OnInit`, `gm_Mode_LightningVs_OnLoad`

## `src/melee/gm/gmlightning.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`

## `src/melee/gm/gmmain.c`

220 linhas; 6 definições aparentes; 3 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `gm_unsplit.h`, `gmmain_lib.h`, `types.h`, `dolphin/card.h`, `dolphin/dvd.h`, `dolphin/gx.h`, `dolphin/os.h`, `dolphin/pad.h`, `dolphin/vi.h`, `melee/db/db.h`, `melee/lb/lb_0195.h`, `melee/lb/lbarq.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lbdvd.h`, `melee/lb/lbheap.h`, `melee/lb/lblanguage.h`, `melee/lb/lbmemory.h`, `melee/lb/lbmthp.h`, `melee/lb/lbsnap.h`, `melee/lb/lbtime.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/hsd_392C.h`, `sysdolphin/baselib/hsd_3933.h`, `sysdolphin/baselib/initialize.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/video.h`

Definições aparentes: `gmMain_8015FD24`, `gmMain_8015FDA0`, `gmMain_8015FDA4`, `init_spr_unk`, `__eabi`, `main`

## `src/melee/gm/gmmain.h`

4 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gmmain_lib.c`

1333 linhas; 175 definições aparentes; 0 marcadores asm.

Includes: `gmmain_lib.h`, `Runtime/platform.h`, `placeholder.h`, `forward.h`, `gm_unsplit.h`, `gmhomerun.h`, `types.h`, `dolphin/os/OSReset.h`, `dolphin/pad.h`, `melee/db/db.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardnew.h`, `melee/lb/lblanguage.h`, `melee/lb/lbtime.h`, `melee/mn/mnname.h`, `melee/ty/toy.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/video.h`

Definições aparentes: `order_bss`, `bitset_mask`, `bitset_set`, `bitset_clear`, `bitset_test`, `bitset_test_word`, `bitset64_mask`, `selkind_mask`, `selkind_bit`, `GetNameTagSlot`, `gmMainLib_GetGameRules`, `gmMainLib_GetCardData`, `gmMainLib_GetNameTagDataBanks`, `gmMainLib_GetGamePrefs`, `GetPersistentFighterDataBase`, `GetPersistentFighterData`, `gmMainLib_GetTrophyFlags`, `gmMainLib_GetTrophyCategoryFlags`, `gmMainLib_GetTrophyCount`, `GetPersistentNameData`, `gmMainLib_8015CCE4`, `gmMainLib_8015CCF0`, `gmMainLib_8015CCFC`, `gmMainLib_GetVsPlayContestants`, `gmMainLib_GetVsPlayTime`, `gmMainLib_GetCombinedVSPlayTime`, `gmMainLib_GetTimeMatchTotal`, `gmMainLib_GetStockMatchTotal`, `gmMainLib_GetCoinMatchTotal`, `gmMainLib_GetBonusMatchTotal`, `gmMainLib_GetStaminaMatchTotal`, `gmMainLib_GetMatchResetCounter`, `gmMainLib_GetSingleplayerTime`, `gmMainLib_8015CD80`, `gmMainLib_GetPowerCount`, `gm_GetPowerTime`, `gmMainLib_GetTotalDamage`, `gmMainLib_GetKOTotal`, `gmMainLib_GetSelfDestructTotal`, `gmMainLib_8015CDC8`, `gmMainLib_8015CDD4`, `gmMainLib_8015CDE0`, `gmMainLib_8015CDEC`, `gmMainLib_8015CE44`, `gmMainLib_8015CEB4`, `gmMainLib_8015CEFC`, `gmMainLib_8015CF5C`, `gmMainLib_8015CF70`, `gmMainLib_8015CF84`, `gmMainLib_8015CF94`, `gmMainLib_8015CFB4`, `gmMainLib_8015CFCC`, `gmMainLib_8015D00C`, `gmMainLib_8015D06C`, `gmMainLib_8015D084`, `gmMainLib_8015D0C0`, `gmMainLib_8015D0D8`, `gmMainLib_8015D0F4`, `gmMainLib_8015D134`, `gmMainLib_8015D194`, `gmMainLib_8015D1AC`, `gmMainLib_8015D1C8`, `gmMainLib_8015D1E8`, `gmMainLib_8015D200`, `gmMainLib_8015D21C`, `gmMainLib_8015D25C`, `gmMainLib_8015D2BC`, `gmMainLib_8015D2D4`, `gmMainLib_8015D2F0`, `gmMainLib_8015D310`, `gmMainLib_8015D328`, `gmMainLib_8015D344`, `gmMainLib_8015D384`, `gmMainLib_8015D3E4`, `gmMainLib_8015D3FC`, `gmMainLib_8015D418`, `gmMainLib_8015D438`, `gmMainLib_8015D450`, `gmMainLib_8015D48C`, `gmMainLib_8015D4A8`, `gmMainLib_8015D4E8`, `gmMainLib_8015D508`, `gmMainLib_8015D5DC`, `gmMainLib_8015D640`, `gmMainLib_8015D6A4`, `gmMainLib_8015D6BC`, `gmMainLib_8015D6D8`, `gmMainLib_8015D6F8`, `gmMainLib_8015D710`, `gmMainLib_8015D72C`, `gmMainLib_8015D74C`, `gmMainLib_8015D764`, `gmMainLib_8015D780`, `gmMainLib_8015D7A4`, `gmMainLib_8015D7BC`, `gmMainLib_8015D7D4`, `gmMainLib_8015D7EC`, `gmMainLib_8015D804`, `gmMainLib_8015D818`, `gmMainLib_8015D888`, `gmMainLib_8015D8B0`, `gmMainLib_8015D8D8`, `gmMainLib_8015D8FC`, `gmMainLib_8015D924`, `gmMainLib_8015D94C`, `gmMainLib_8015D970`, `gmMainLib_8015D984`, `gmMainLib_8015D9F4`, `gmMainLib_8015DA1C`, `gmMainLib_8015DA40`, `gmMainLib_8015DA68`, `gmMainLib_8015DA90`, `gmMainLib_8015DAB4`, `gmMainLib_8015DADC`, `gmMainLib_8015DB00`, `gmMainLib_8015DB0C`, `gmMainLib_8015DB18`, `gmMainLib_8015DB2C`, `gmMainLib_8015DB6C`, `gmMainLib_8015DB80`, `gmMainLib_AdjustNameTags`, `gmMainLib_AdjustNameTag`, `gmMainLib_ClearNameTag`, `gmMainLib_8015DBF4`, `SetDefaultHandicaps`, `gmMainLib_8015EA80`, `gmMainLib_8015ECB0`, `gmMainLib_8015ECBC`, `gmMainLib_8015ED30`, `GetRumbleSettingOfPort`, `gmMainLib_SetRumbleEnabled`, `gmMainLib_8015ED5C`, `gmMainLib_8015ED68`, `gmMainLib_8015ED74`, `gmMainLib_8015ED80`, `gmMainLib_GetUnlockedCharactersBitmaskPtr`, `gmMainLib_8015ED98`, `gmMainLib_8015EDA4`, `gmMainLib_8015EDB0`, `gmMainLib_8015EDBC`, `gmMainLib_8015EDC8`, `gmMainLib_8015EDD4`, `gmMainLib_8015EDE4`, `gmMainLib_8015EDF8`, `gmMainLib_8015EE0C`, `gmMainLib_8015EE1C`, `gmMainLib_8015EE30`, `gmMainLib_8015EE44`, `gmMainLib_8015EE54`, `gmMainLib_8015EE68`, `gmMainLib_8015EE90`, `gmMainLib_8015EEA0`, `gmMainLib_8015EEB4`, `gmMainLib_8015EEC8`, `gmMainLib_8015EF30`, `InitializePersistentNameData`, `ResetAllPersistentFighterData`, `ResetPersistentFighterData`, `gmMainLib_8015F150`, `gmMainLib_8015F260`, `gmMainLib_8015F464`, `gmMainLib_8015F490`, `gmMainLib_8015F4BC`, `gmMainLib_8015F4E8`, `gmMainLib_8015F4F4`, `gmMainLib_8015F500`, `gmMainLib_8015F588`, `gmMainLib_8015F600`, `setupAudioVideo`, `resetSaveData`, `gmMainLib_8015FA34`, `gmMainLib_8015FB68`, `gmMainLib_8015FBA4`, `gmMainLib_8015FC74`, `gmMainLib_8015FCC0`

## `src/melee/gm/gmmain_lib.h`

169 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/gm/forward.h`, `melee/gm/types.h`

## `src/melee/gm/gmmenu.c`

67 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `gmmenu.h`, `gm_18A1.h`, `gm_unsplit.h`, `gmevent.h`, `types.h`, `dolphin/types.h`

Definições aparentes: `gm_Mode_ClassicGOver_OnLoad`, `gm_Mode_AdventureGOver_OnLoad`, `gm_Mode_AllstarGOver_OnLoad`, `gm_Mode_Opening_OnLoad`

## `src/melee/gm/gmmenu.h`

9 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gmmenumode.c`

249 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `melee/lb/forward.h`, `gm_1A3F.h`, `gm_unsplit.h`, `gmmain_lib.h`, `types.h`, `melee/if/soundtest.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lbdvd.h`, `melee/lb/lbsnap.h`, `melee/mn/mngallery.h`, `melee/mn/mnsnap.h`, `melee/mn/types.h`, `sysdolphin/baselib/memory.h`

Definições aparentes: `onEnterDebug`, `onEnter`, `onExit`

## `src/melee/gm/gmmenumode.h`

9 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmmovieend.c`

166 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `gmmovieend.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmopening.h`, `types.h`, `dolphin/pad.h`, `melee/if/ifcoget.h`, `melee/if/textlib.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbmthp.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/sobjlib.h`

Definições aparentes: `gm_ModeState_ApproachVs_OnExit`, `gm_ModeState_Prize_OnExit`, `gm_Scene_DebugMenu_OnEnter`, `gm_Scene_MovieEnd_OnEnter`, `gm_Scene_MovieEnd_OnFrame`

## `src/melee/gm/gmmovieend.h`

12 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`

## `src/melee/gm/gmmultiman.c`

1087 linhas; 47 definições aparentes; 0 marcadores asm.

Includes: `gmmultiman.h`, `gm_unsplit.h`, `gmmain_lib.h`, `types.h`, `melee/gr/ground.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lbdvd.h`, `melee/lb/lbtime.h`, `melee/lb/types.h`

Definições aparentes: `gm_801B6320`, `gm_801B632C`, `gm_801B63C4`, `gm_801B6428`, `gm_801B65D4`, `gm_Mode_TargetTest_OnInit`, `gm_Mode_TargetTest_OnLoad`, `gm_Mode_10ManVs_OnInit`, `gm_Mode_10ManVs_OnLoad`, `gm_801B688C`, `gm_801B6AD8_inline`, `gm_801B69C0`, `gm_801B6AD8`, `gmMultiman_LeaveFinish`, `gmMultiman_InitPlayers`, `gmMultiman_InitTimedRules`, `gmMultiman_InitScoreRules`, `gm_801B6B70`, `gm_801B6BE8`, `gmMultiman_RecordMatchResult`, `gmMultiman_SaveCompletionRecord`, `gm_801B6F44`, `gm_801B7044`, `gm_801B70DC`, `gm_801B7154`, `gm_801B74F0`, `gm_801B75F0`, `gm_801B7688`, `getMultimanData`, `gmMultiman_InitRecord`, `gmMultiman_InitScoreRecord`, `gmMultiman_SaveTimedRecord`, `gmMultiman_SaveScoreRecord`, `gm_801B7700`, `gm_801B7AA0`, `gm_801B7B74`, `gm_801B7C0C`, `gm_801B7C84`, `gm_801B8024`, `gm_801B8110`, `gm_801B81A8`, `gm_801B8220`, `gm_801B8580`, `gm_801B863C`, `gm_801B86D4`, `gm_801B874C`, `gm_801B8AF8`

## `src/melee/gm/gmmultiman.h`

45 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/mn/forward.h`, `placeholder.h`

## `src/melee/gm/gmomake15.c`

72 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `gmomake15.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmopening.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbmthp.h`, `melee/mn/inlines.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/sobjlib.h`

Definições aparentes: `gm_Scene_Omake15_OnEnter`, `gm_Scene_Omake15_OnFrame`

## `src/melee/gm/gmomake15.h`

7 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gmopening.c`

292 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `gmopening.h`, `stdio.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmtitle.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/lb/lbmthp.h`, `melee/mn/inlines.h`, `melee/mn/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/hsd_3924.h`, `sysdolphin/baselib/sobjlib.h`

Definições aparentes: `sdata2_order`, `gm_801A9DD0`, `fn_801A9FCC`, `fn_801AA0E8`, `gm_Scene_Opening_OnEnter`, `gm_Scene_Opening_OnFrame`

## `src/melee/gm/gmopening.h`

16 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/sobjlib.h`

## `src/melee/gm/gmopeningmode.c`

666 linhas; 36 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/pl/forward.h`, `gm_1601.h`, `gm_16F1.h`, `gm_unsplit.h`, `gmevent.h`, `gmmain_lib.h`, `gmtitlemode.h`, `types.h`, `melee/db/db.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbdvd.h`, `melee/lb/lbmthp.h`, `melee/lb/types.h`, `melee/mn/types.h`, `melee/vi/vi0102.h`, `melee/vi/vi0401.h`, `melee/vi/vi0501.h`, `melee/vi/vi0502.h`, `melee/vi/vi1101.h`, `melee/vi/vi1201v1.h`, `melee/vi/vi1201v2.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `onExitTitle`, `gm_GetRandomHistory`, `gm_GetCharacterUsage`, `gm_GetCharacterUsageDirect`, `gm_GetStageUsage`, `gm_SetupTitleDemo`, `gm_PreloadTitleDemo`, `onEnterVs`, `gm_801BF634`, `gm_801BF648`, `gm_801BF65C`, `gm_801BF670`, `gm_801BF684`, `gm_801BF694`, `gm_801BF6A8`, `gm_801BF6B8`, `gm_801BF6C8`, `gm_801BF6D8`, `gm_801BF6E8`, `gm_801BF6F8`, `gm_801BF708`, `gm_801BF718`, `gm_801BEFA4_inner3`, `gm_801BEFA4_inner2`, `gm_801BEFA4_inner`, `gm_801BEFA4_noinline`, `gm_801BEFC0_inner3`, `gm_801BEFC0_inner2`, `gm_801BEFC0_inner`, `gm_801BEFC0_noinline`, `onEnterCutsceneLuigi`, `onExitRegendCongrats`, `onEnterMovie`, `onExitMovie`, `onExitHowto`, `onExitOmake15`

## `src/melee/gm/gmpause.c`

101 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `gmpause.h`, `gm_unsplit.h`, `melee/lb/lbarchive.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `fn_801A0E34`, `gm_801A0FEC`, `gm_801A10FC`, `fn_801A1134`

## `src/melee/gm/gmpause.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/gm/gmprogressive.c`

199 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `gmprogressive.h`, `gm_1A36.h`, `gm_unsplit.h`, `gmmain_lib.h`, `types.h`, `dolphin/pad.h`, `melee/lb/lbarchive.h`, `melee/lb/lblanguage.h`, `melee/mn/inlines.h`, `melee/sc/types.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `gm_801AD088`, `gm_801AD254`, `gm_Scene_ProgScan_OnFrame`, `gm_Scene_ProgScan_OnEnter`, `gm_Scene_ProgScan_OnExit`

## `src/melee/gm/gmprogressive.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gmprogressivemode.c`

36 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `gmprogressivemode.h`, `gm_1A3F.h`

Definições aparentes: `gm_801BF8F8`, `gm_801BF920`

## `src/melee/gm/gmprogressivemode.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmregclear.c`

1073 linhas; 24 definições aparentes; 0 marcadores asm.

Includes: `gmregclear.h`, `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `forward.h`, `gm_unsplit.h`, `types.h`, `dolphin/pad.h`, `melee/cm/camera.h`, `melee/gr/ground.h`, `melee/gr/grpushon.h`, `melee/if/ifcoget.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/mn/inlines.h`, `melee/pl/player.h`, `melee/sc/types.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `order_data`, `fn_8017F008`, `fn_8017F09C`, `fn_8017F14C`, `fn_8017F1B8`, `fn_8017F294`, `fn_8017F2A4`, `fn_8017F47C`, `fn_8017F608`, `fn_8017FA1C`, `fn_8017FBA4`, `fn_8017FE54`, `fn_8017FF1C`, `fn_801803FC`, `setScoreBonuses`, `fn_80180630_CreateCameraGObj`, `fn_80180630_LoadLightList`, `fn_80180630_LoadCameraDesc`, `fn_80180630_GetModelDesc`, `fn_80180630_SetupSisLib`, `fn_80180630_CreateLightAndCamera`, `fn_80180630_GetX118`, `fn_80180630`, `fn_80180AC0`

## `src/melee/gm/gmregclear.h`

133 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/gm/forward.h`, `melee/gr/forward.h`, `melee/mn/forward.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `melee/gm/types.h`

## `src/melee/gm/gmregcommon.c`

79 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `gmregcommon.h`, `melee/ft/forward.h`, `gm_unsplit.h`, `sysdolphin/baselib/debug.h`

Definições aparentes: `gm_8017BE84`, `gm_8017BE8C`, `gmRegSetupEnemyColorTable`

## `src/melee/gm/gmregcommon.h`

13 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/gm/gmregenddisp.c`

518 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `math.h`, `gm_1A7A.h`, `gm_unsplit.h`, `gmevent.h`, `gmregtyfall.h`, `inlines.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `melee/ty/toy.h`, `melee/ty/tydisplay.h`, `melee/ty/types.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `fn_801A7FB4`, `order_sdata2`, `fn_801A80CC`, `fn_801A80F0`, `gm_801A8114`, `order_data_0`, `fn_801A851C`, `gm_801A85E4`, `gm_801A8D54`, `gm_801A9094_get_entry`, `gm_801A9094_get_bg`, `gm_801A9094_create_gobj`, `gm_801A9094`, `fn_801A9498`, `fn_801A94BC`, `gm_801A8114_inline`, `gm_801A9630_init`, `gm_801A9630_fog`, `gm_801A9630_light`, `gm_801A9630_camera`, `gm_801A9630`

## `src/melee/gm/gmregtyfall.c`

569 linhas; 22 definições aparentes; 0 marcadores asm.

Includes: `gmregtyfall.h`, `forward.h`, `gm_unsplit.h`, `dolphin/pad.h`, `melee/cm/camera.h`, `melee/ef/efasync.h`, `melee/ef/eflib.h`, `melee/ft/ftdemo.h`, `melee/gr/inlines.h`, `melee/gr/stage.h`, `melee/it/item.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbspdisplay.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `melee/pl/player.h`, `melee/sc/types.h`, `melee/ty/toy.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sobjlib.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `order_sdata2`, `gm_801A659C`, `gm_801A6630`, `fn_801A6664`, `fn_801A6844`, `fn_801A6868`, `gm_801A68D8`, `fn_801A6A48`, `order_data`, `fn_801A6ACC`, `fn_801A6B6C`, `fn_801A6C30`, `gm_801A6C54`, `fn_801A6D78`, `gm_801A6DC0`, `gm_801A6EE4`, `initImages`, `gm_801A7070_SetupMain`, `getCurrentTrophy`, `gm_801A7070_SetupTrophy`, `gm_Scene_ToyFall_OnEnter`, `gm_Scene_ToyFall_OnFrame`

## `src/melee/gm/gmregtyfall.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/sc/forward.h`, `sysdolphin/baselib/forward.h`

## `src/melee/gm/gmresult.c`

1827 linhas; 47 definições aparentes; 0 marcadores asm.

Includes: `gmresult.h`, `types.h`, `melee/lb/lb_013B.h`, `gm_1601.h`, `gm_1798.h`, `gm_unsplit.h`, `gmresultplayer.h`, `dolphin/gx/GXStruct.h`, `dolphin/types.h`, `melee/if/ifcoget.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/lb/lbvector.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `melee/pl/player.h`, `melee/sc/types.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `order_sdata`, `gmresult_sdata2_order`, `fn_80174274`, `fn_80174284_noinline`, `fn_80174284`, `fn_80174338`, `fn_8017435C`, `fn_80174380`, `gm_WasMatchCanceled`, `fn_801743C4`, `gmResultFindNth`, `gmResultFormatLabel`, `fn_80174468`, `fn_801748EC`, `fn_80174920`, `fn_801749B8`, `fn_80174A60`, `order_data`, `fn_80174B4C_blk14829`, `fn_80174B4C`, `fn_80174FD0`, `fn_80175038`, `fn_8017507C`, `fn_80175240`, `fn_8017556C`, `matchWasSkipped`, `fn_801756E0`, `fn_80175880`, `fn_80175A94_get_match_end`, `fn_80175A94`, `fn_80175C5C`, `fn_80175D34`, `fn_80175DC8`, `fn_80176A6C`, `fn_80176BCC`, `fn_80176BF0_inline`, `fn_80176BF0`, `fn_80176D18`, `fn_80176D3C`, `fn_80176F60`, `fn_801771C0`, `gmResultLoadArchive`, `gmResultReportLightGObj`, `gmResultReportLightLObj`, `gmResultReportModelGObj`, `gm_Scene_Results_OnEnter`, `gm_Scene_Results_OnExit`

## `src/melee/gm/gmresult.h`

50 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx/GXStruct.h`, `dolphin/mtx.h`

## `src/melee/gm/gmresultplayer.c`

1361 linhas; 20 definições aparentes; 0 marcadores asm.

Includes: `gmresultplayer.h`, `placeholder.h`, `forward.h`, `gm_1601.h`, `gm_1798.h`, `gm_unsplit.h`, `gmresult.h`, `gmscene.h`, `types.h`, `melee/if/ifcoget.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbspdisplay.h`, `melee/mn/mnmain.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `gm_80177724`, `inline0`, `fn_80177748`, `fn_80177920`, `pagePrev`, `pageNext`, `scrollDown`, `scrollUp`, `fn_80177B7C`, `fn_80177DD0`, `fn_80178050`, `fn_801785B0`, `fn_80178BB4_init_players`, `fn_80178BB4`, `fn_801791E4`, `fn_80179350_inline`, `fn_80179350_update`, `fn_80179350`, `fn_801795D4`, `fn_801796F0`

## `src/melee/gm/gmresultplayer.h`

138 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `melee/gm/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/tobj.h`

## `src/melee/gm/gmscdata.c`

762 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `gmscdata.h`, `gm_1A33.h`, `gm_unsplit.h`, `gmadventure.h`, `gmallstar.h`, `gmapproach.h`, `gmcameramode.h`, `gmclassic.h`, `gmdebugmode.h`, `gmfixedcamera.h`, `gmgiant.h`, `gmhanyucss.h`, `gmhanyusss.h`, `gmhomerun.h`, `gmhowto.h`, `gminvisible.h`, `gmlightning.h`, `gmmenu.h`, `gmmenumode.h`, `gmmovieend.h`, `gmmultiman.h`, `gmomake15.h`, `gmopening.h`, `gmprogressive.h`, `gmprogressivemode.h`, `gmregtyfall.h`, `gmresult.h`, `gmsinglebutton.h`, `gmslomo.h`, `gmstaffroll.h`, `gmstamina.h`, `gmsupersudden.h`, `gmtiny.h`, `gmtitle.h`, `gmtitlemode.h`, `gmtoulib.h`, `gmtoumode.h`, `gmtoycollection.h`, `gmtoygallery.h`, `gmtoylottery.h`, `gmtrainingmode.h`, `gmvsmelee.h`, `gmvsmode.h`, `types.h`, `melee/if/ifprize.h`, `melee/mn/mncharsel.h`, `melee/mn/mnmain.h`, `melee/mn/mnstagesel.h`, `melee/ty/toy.h`, `melee/ty/tydisplay.h`, `melee/ty/tyfigupon.h`, `melee/vi/vi0102.h`, `melee/vi/vi0401.h`, `melee/vi/vi0402.h`, `melee/vi/vi0501.h`, `melee/vi/vi0502.h`, `melee/vi/vi0601.h`, `melee/vi/vi0801.h`, `melee/vi/vi1101.h`, `melee/vi/vi1201v1.h`, `melee/vi/vi1201v2.h`, `melee/vi/vi1202.h`

Definições aparentes: `gm_GetAllGameScenes`, `gm_GetAllGameModes`

## `src/melee/gm/gmscdata.h`

35 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmscene.c`

385 linhas; 26 definições aparentes; 0 marcadores asm.

Includes: `gmscene.h`, `gm_1A36.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmscdata.h`, `dolphin/os/OSThread.h`, `melee/db/db.h`, `melee/if/ifcoget.h`, `melee/lb/lb_013B.h`, `melee/lb/lb_0195.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbheap.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/hsd_3924.h`, `sysdolphin/baselib/hsd_392C.h`, `sysdolphin/baselib/initialize.h`, `sysdolphin/baselib/leak.h`, `sysdolphin/baselib/perf.h`, `sysdolphin/baselib/sobjlib.h`

Definições aparentes: `gm_GetDbPauseFlag`, `gm_801A4624`, `gm_SetDbPauseFlag`, `gm_ClearDbPauseFlag`, `gm_801A46B8`, `fn_801A46F4`, `fn_801A47E4`, `gm_801A48A4`, `gm_801A4970`, `gm_SetDbPauseInputHandlers`, `gm_801A4B1C`, `gm_SetPreGObjProcCallback`, `gm_801A4B50`, `gm_801A4B60`, `gm_801A4B74`, `gm_801A4B88`, `gm_GetCurrentSceneEnterData`, `gm_GetCurrentSceneExitData`, `gm_801A4BA8`, `gm_801A4BB8`, `gm_801A4BC8`, `fn_801A4BD0`, `gm_801A4BD4`, `gm_FindGameSceneHandler`, `maybe_gm_801A48A4`, `gm_801A4D34`

## `src/melee/gm/gmscene.h`

56 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `melee/gm/types.h`, `sysdolphin/baselib/gobj.h`

## `src/melee/gm/gmscmemcard.c`

497 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `gmscmemcard.h`, `gm_unsplit.h`, `gmmain_lib.h`, `melee/db/db.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lblanguage.h`, `melee/mn/inlines.h`, `sysdolphin/baselib/controller.h`

Definições aparentes: `gm_801AEE6C`, `gm_801AF0D4_inline`, `gm_801AF0D4`, `set_gm_804D6870_inline`, `gm_801AEDC8_flag_check`, `get_lang_val`, `unk_inline`, `gm_801AF250`, `gm_Scene_MemCard_OnFrame`, `checkUnk0`, `gm_Scene_MemCard_OnEnter`, `gm_Scene_MemCard_OnExit`

## `src/melee/gm/gmscmemcard.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gmsinglebutton.c`

186 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `gmsinglebutton.h`, `gm_unsplit.h`, `gmapproach.h`, `gmmain_lib.h`, `gmvsmelee.h`, `types.h`, `melee/if/if_2FD9.h`, `melee/mn/types.h`

Definições aparentes: `gm_801BA10C`, `gm_801BA138`, `gm_801BA160`, `gm_801BA188`, `fn_801BA1B4`, `gm_801BA1C8`, `gm_801BA1FC`, `gm_801BA224`, `gm_801BA258`, `gm_801BA278`, `gm_801BA298`, `gm_Mode_SingleButtonVs_OnInit`, `gm_Mode_SingleButtonVs_OnLoad`

## `src/melee/gm/gmsinglebutton.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/mn/forward.h`

## `src/melee/gm/gmslomo.c`

181 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `gmslomo.h`, `gm_unsplit.h`, `gmapproach.h`, `gmmain_lib.h`, `gmmovieend.h`, `gmvsmelee.h`, `types.h`, `melee/if/if_2FD9.h`

Definições aparentes: `gm_801BA50C`, `gm_801BA538`, `gm_801BA560`, `gm_801BA588`, `fn_801BA5B4`, `gm_801BA5C0`, `gm_801BA5F4`, `gm_801BA61C`, `gm_801BA650`, `gm_801BA670`, `gm_801BA690`, `gm_Mode_SlowMo_OnInit`, `gm_Mode_SlowMo_OnLoad`

## `src/melee/gm/gmslomo.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/mn/forward.h`

## `src/melee/gm/gmstaffroll.c`

1338 linhas; 22 definições aparentes; 0 marcadores asm.

Includes: `gmstaffroll.h`, `melee/ft/forward.h`, `math.h`, `gm_unsplit.h`, `gmmain_lib.h`, `melee/ef/efasync.h`, `melee/ef/eflib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbbgflash.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `melee/ty/toy.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/generator.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/psappsrt.h`, `sysdolphin/baselib/psstructs.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `gm_801AA644`, `gm_801AA664`, `gm_801AA688`, `gm_801AA6D8`, `gm_801AA6FC`, `gm_801AA774`, `gm_Scene_StaffRoll_OnFrame`, `fn_801AA7F8`, `fn_801AA854`, `fn_801AAA28`, `fn_801AAABC`, `fn_801AAB18`, `fn_801AAB74`, `gm_801AB200_GetXPos`, `gm_801AB200_GetTrigger`, `gm_801AB200_HasCheck`, `gm_801AB200_SetAppSRT`, `gm_801AB200_ptcl`, `fn_801AB200`, `fn_801AC67C`, `gm_Scene_StaffRoll_OnEnter`, `gm_Scene_StaffRoll_OnExit`

## `src/melee/gm/gmstaffroll.h`

24 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/gm/gmstamina.c`

237 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `gmstamina.h`, `placeholder.h`, `gm_1A3F.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmvsmelee.h`, `types.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbdvd.h`, `melee/mn/types.h`, `melee/pl/player.h`, `sysdolphin/baselib/gobjproc.h`

Definições aparentes: `gm_801B91C8`, `gm_801B922C`, `gm_801B9254`, `gm_801B927C`, `gm_801B931C`, `gm_801B9560`, `gm_Mode_StaminaVs_OnInit`, `gm_Mode_StaminaVs_OnLoad`, `gm_801B9600`, `fn_801B96E8`, `gm_801B97C4`, `fn_801B9850`

## `src/melee/gm/gmstamina.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/gm/forward.h`

## `src/melee/gm/gmsupersudden.c`

184 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `gmsupersudden.h`, `gm_unsplit.h`, `gmapproach.h`, `gmmain_lib.h`, `gmmovieend.h`, `gmvsmelee.h`, `types.h`, `melee/if/if_2FD9.h`, `melee/mn/types.h`

Definições aparentes: `gm_801B8BB4`, `gm_801B8BE0`, `gm_801B8C08`, `gm_801B8C30`, `fn_801B8C5C`, `gm_801B8C68`, `gm_801B8C9C`, `gm_801B8CC4`, `gm_801B8CF4`, `gm_801B8D14`, `gm_801B8D34`, `gm_Mode_SuperSuddenDeath_OnInit`, `gm_Mode_SuperSuddenDeath_OnLoad`

## `src/melee/gm/gmsupersudden.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/mn/forward.h`

## `src/melee/gm/gmtiny.c`

182 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `gmtiny.h`, `gm_unsplit.h`, `gmapproach.h`, `gmmain_lib.h`, `gmmovieend.h`, `gmvsmelee.h`, `types.h`, `melee/if/if_2FD9.h`

Definições aparentes: `gm_801B8DA8`, `gm_801B8DD4`, `gm_801B8DFC`, `gm_801B8E24`, `fn_801B8E50`, `gm_801B8E74`, `gm_801B8EA8`, `gm_801B8ED0`, `gm_801B8F04`, `gm_801B8F24`, `gm_801B8F44`, `gm_Mode_TinyVs_OnInit`, `gm_Mode_TinyVs_OnLoad`

## `src/melee/gm/gmtiny.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/mn/forward.h`

## `src/melee/gm/gmtitle.c`

369 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `gmtitle.h`, `melee/cm/forward.h`, `melee/if/forward.h`, `gm_unsplit.h`, `gmevent.h`, `gmmain_lib.h`, `gmopening.h`, `types.h`, `melee/db/db.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/lb/lbmthp.h`, `melee/lb/lbspdisplay.h`, `melee/lb/lbtime.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `melee/sc/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `gmTitle_801A12C4`, `gmTitle_801A146C`, `isActiveTitle`, `fn_801A1498_inline`, `fn_801A1498`, `gmTitle_801A1630`, `isEmblemUnlocked`, `gmTitle_801A165C`, `gmTitle_801A1814`, `gmTitle_801A185C`, `gmTitle_801A18D4`, `gmTitle_801A1944`, `gmTitle_801A19AC`, `gmTitle_801A1A18`, `gmTitle_801A1A3C`, `gmTitle_801A1AC0`, `gm_Scene_Title_OnFrame`, `gmTitle_801A1D38`, `gm_Scene_Title_OnEnter`

## `src/melee/gm/gmtitle.h`

16 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/gm/gmtitlemode.c`

70 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `gmtitlemode.h`, `gm_1A3F.h`, `gm_unsplit.h`, `types.h`, `melee/db/db.h`, `melee/lb/lbdvd.h`, `sysdolphin/baselib/controller.h`

Definições aparentes: `gmTitleMode_OnEnter`, `onExit`

## `src/melee/gm/gmtitlemode.h`

9 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmtou_0.c`

2915 linhas; 58 definições aparentes; 0 marcadores asm.

Includes: `gmtou_0.h`, `placeholder.h`, `forward.h`, `gm_1601.h`, `gm_1A3F.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmscene.h`, `gmtoulib.h`, `types.h`, `dolphin/pad.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `melee/mn/mnmainrule.h`, `melee/mn/mnname.h`, `melee/mn/mnnamenew.h`, `melee/sc/types.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `sbss_order`, `sdata2_order0`, `order_sdata2_1`, `fn_80190ABC`, `gm_80190EA4`, `gm_80190FE4`, `fn_801910E0`, `fn_80191154`, `fn_80191240_dec_flash_timer`, `fn_80191240_save_root_jobj`, `fn_80191240_get_menu_state`, `fn_80191240_show_children`, `fn_80191240`, `fn_801913BC`, `fn_80191678`, `fn_8019175C`, `fn_801918F0`, `fn_80191A54`, `fn_80191B5C`, `fn_80191CA4`, `fn_80191D38`, `fn_80191E9C`, `fn_80191FD4_is_selected`, `fn_80191FD4`, `fn_8019237C`, `fn_8019249C_get_jobj`, `fn_8019249C`, `fn_80192690`, `fn_80192758_get_jobj`, `fn_80192758`, `fn_80192938`, `fn_80192BB0`, `fn_80192E6C`, `fn_80193230`, `fn_80193308`, `fn_801935B8`, `tmSettings_StepDown`, `tmSettings_StepUp`, `tmSettings_Refresh`, `fn_801937C4`, `fn_80193B58`, `fn_80193FCC`, `fn_80194658_get_value`, `fn_80194658`, `fn_801949B4`, `fn_80194BC4`, `fn_80194D84`, `fn_80194F30`, `fn_801953C8_GetPreviousPosition`, `fn_801953C8_GetPlayerIndex`, `fn_801953C8`, `fn_80195AF0`, `fn_80195CCC_IsUniqueEntry`, `fn_80195CCC`, `fn_8019610C`, `gm_Scene_TouSetup_OnFrame`, `gm_Scene_TouSetup_OnEnter`, `gm_Scene_TouSetup_OnExit`

## `src/melee/gm/gmtou_0.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/gm/gmtou_1.c`

2384 linhas; 48 definições aparentes; 0 marcadores asm.

Includes: `placeholder.h`, `forward.h`, `gm_1601.h`, `gm_1A3F.h`, `gm_unsplit.h`, `gmscene.h`, `gmtou_0.h`, `gmtoulib.h`, `inlines.h`, `types.h`, `dolphin/pad.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbdvd.h`, `melee/lb/types.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `melee/sc/types.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `sdata2_order`, `fn_80196510`, `fn_8019655C`, `fn_80196564`, `fn_80196594`, `fn_801965C4`, `fn_80196684`, `fn_801967E0`, `fn_80196CF8`, `fn_80196DBC`, `fn_80196E30`, `fn_80196EEC`, `gmTournament_IsPlayerSetupOption`, `fn_80196FFC`, `fn_801973F8`, `fn_801975C8`, `fn_801976D4`, `fn_801977AC`, `fn_80197AF0`, `fn_80197D4C`, `fn_80197E18`, `fn_80197FD8`, `fn_801981A0`, `fn_801983E4`, `fn_80198584`, `fn_801985D4`, `fn_80198824`, `fn_80198BA0`, `fn_80198C60`, `fn_80198D18`, `fn_80198EBC`, `fn_80199AF0`, `fn_8019A158_GetBracketEntry`, `fn_8019A158`, `fn_8019A71C`, `gm_8019A828`, `get_pad_error`, `fn_8019A86C`, `fn_8019AF50`, `gm_Scene_TouBracket_OnFrame`, `fn_8019B458_UpdateRank`, `setupScene`, `fn_8019B458`, `fn_8019B81C`, `fn_8019B860`, `gm_Scene_TouBracket_OnEnter`, `gm_Scene_TouBracket_OnExit`, `fn_8019BA04`

## `src/melee/gm/gmtou_1.h`

4 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gmtou_2.c`

1215 linhas; 29 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/pl/forward.h`, `placeholder.h`, `gm_1601.h`, `gm_1A3F.h`, `gmmain_lib.h`, `gmscene.h`, `gmtoulib.h`, `inlines.h`, `types.h`, `dolphin/os.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbdvd.h`, `melee/lb/types.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `melee/sc/types.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `sdata2_order`, `fn_8019BA08`, `fn_8019BF18`, `fn_8019BF8C`, `fn_8019C048`, `fn_8019C3EC`, `GetTmData`, `fn_8019C570`, `fn_8019C6AC`, `fn_8019C744`, `fn_8019CA38`, `fn_8019CBFC`, `fn_8019CC74`, `fn_8019CDBC`, `fn_8019CFA4`, `fn_8019D074`, `gmTournament_GetJObj`, `fn_8019D1BC`, `fn_8019DD60`, `get_match_player_index`, `get_match_player_index_xF`, `gm_Scene_TouAlt_OnFrame`, `gm_8019ECAC_OnEnter_inline`, `gm_8019E634`, `gm_Scene_TouAlt_OnEnter`, `gm_Scene_TouAlt_OnExit`, `fn_8019EE80`, `fn_8019EF08`, `order_data_1`

## `src/melee/gm/gmtou_2.h`

4 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/gm/gmtoulib.c`

2666 linhas; 66 definições aparentes; 0 marcadores asm.

Includes: `gmtoulib.h`, `melee/ft/forward.h`, `melee/pl/forward.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `stdio.h`, `string.h`, `forward.h`, `gm_1601.h`, `gm_unsplit.h`, `gmmain_lib.h`, `types.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/mn/mnmain.h`, `melee/mn/mnname.h`, `melee/mn/mnstagesel.h`, `melee/pl/player.h`, `melee/sc/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/hsd_3915.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `gmTournament_SetBracketByes`, `fn_8018A514`, `fn_8018A970`, `gmTournament_SetTripleRightCoords`, `gmTournament_SetRegularCoords`, `fn_8018AA74`, `gmTournament_GetBracketSlideYForward`, `gmTournament_GetBracketSlideYReverse`, `fn_8018B090_inline0`, `fn_8018B090_inline2`, `fn_8018B090_inline3`, `fn_8018B090_inline4`, `fn_8018B090_inline5`, `fn_8018B090_inline6`, `fn_8018B090_inline7`, `fn_8018B090_inline8`, `fn_8018B090`, `fn_8018C8D4`, `fn_8018D50C`, `fn_8018DC18`, `fn_8018DF68`, `fn_8018E46C`, `gmTournament_InitBracket`, `fn_8018E618`, `fn_8018E85C`, `fn_8018EC48`, `fn_8018EC7C`, `fn_8018ECA8`, `fn_8018F00C`, `gm_8018F1B0`, `fn_8018F310`, `fn_8018F3BC`, `fn_8018F3D0`, `fn_8018F410`, `fn_8018F4A0`, `fn_8018F508`, `fn_8018F5F0`, `fn_8018F62C`, `gm_GetTournamentData`, `fn_8018F640`, `fn_8018F674`, `fn_8018F6A8`, `fn_8018F6DC`, `fn_8018F6FC`, `fn_8018F71C`, `fn_8018F74C`, `fn_8018F808`, `fn_8018F888_inline0`, `fn_8018F888`, `fn_8018FA24_inline0`, `fn_8018FA24`, `fn_8018FBD8`, `fn_8018FBE0`, `fn_8018FDC4`, `fn_8018FF9C`, `fn_80190174`, `fn_801901F8`, `fn_8019027C`, `fn_801902F0`, `fn_8019035C`, `fn_8019044C`, `fn_80190480`, `fn_801904D0`, `fn_80190520`, `gm_801905F0_inline0`, `gm_801905F0`

## `src/melee/gm/gmtoulib.h`

182 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/gm/forward.h`, `melee/mn/forward.h`, `melee/sc/forward.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `melee/gm/types.h`

## `src/melee/gm/gmtoumode.c`

229 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `gmtoumode.h`, `melee/lb/forward.h`, `gm_1A3F.h`, `gm_1B03.h`, `gm_unsplit.h`, `gmtoulib.h`, `gmvsmelee.h`, `types.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/types.h`, `melee/mn/types.h`

Definições aparentes: `gm_801B1724`, `gm_801B174C`, `gm_801B1788`, `gm_801B1810`, `gm_801B1834`, `gm_801B18D4`, `gm_801B1A2C`, `gm_801B1A84`, `gm_801B1AD4`

## `src/melee/gm/gmtoumode.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmtoycollection.c`

28 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `gm_unsplit.h`, `types.h`, `melee/lb/types.h`

Definições aparentes: `gm_801BED14`

## `src/melee/gm/gmtoycollection.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmtoygallery.c`

31 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `gmtoygallery.h`, `gm_unsplit.h`, `types.h`

Definições aparentes: `onExit`

## `src/melee/gm/gmtoygallery.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmtoylottery.c`

41 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `gm_16F1.h`, `gm_unsplit.h`, `types.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/types.h`

Definições aparentes: `onEnter`, `onExit`

## `src/melee/gm/gmtoylottery.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmtrainingmode.c`

282 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `gmtrainingmode.h`, `melee/lb/forward.h`, `gm_1884.h`, `gm_1A3F.h`, `gm_1B03.h`, `gm_unsplit.h`, `gmmain_lib.h`, `types.h`, `dolphin/pad.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lbdvd.h`, `melee/lb/lbtime.h`, `melee/lb/types.h`, `melee/mn/inlines.h`, `melee/mn/types.h`

Definições aparentes: `gm_801B1B74`, `gm_801B07E8_layer`, `gm_801B1C24`, `gm_801B1EB8`, `gm_801B1EEC`, `fn_801B1F6C`, `gm_801B1F70`, `gm_801B2204`, `gm_Mode_Training_OnInit`, `gm_Mode_Training_OnLoad`

## `src/melee/gm/gmtrainingmode.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/gmvs.c`

2300 linhas; 118 definições aparentes; 0 marcadores asm.

Includes: `gmvs.h`, `Runtime/platform.h`, `string.h`, `forward.h`, `gm_1884.h`, `gm_18A1.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmmultiman.h`, `gmpause.h`, `types.h`, `dolphin/pad.h`, `melee/cm/camera.h`, `melee/db/db.h`, `melee/ef/efasync.h`, `melee/ef/eflib.h`, `melee/ft/ftdevice.h`, `melee/ft/ftlib.h`, `melee/gr/ground.h`, `melee/gr/grpstadium.h`, `melee/gr/stage.h`, `melee/if/if_2F6E.h`, `melee/if/ifall.h`, `melee/if/ifhazard.h`, `melee/if/ifnametag.h`, `melee/if/ifstatus.h`, `melee/if/ifstock.h`, `melee/if/iftime.h`, `melee/it/item.h`, `melee/it/itspawn.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00F9.h`, `melee/lb/lb_0195.h`, `melee/lb/lb_0219.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbrefract.h`, `melee/lb/lbtime.h`, `melee/mn/types.h`, `melee/mp/mpcoll.h`, `melee/pl/player.h`, `melee/pl/plbonus.h`, `melee/pl/plbonuslib.h`, `melee/sfx/crowdsfx.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobjproc.h`

Definições aparentes: `gmVs_GetSceneController`, `gmVs_GetSceneState`, `gm_GetStartMeleeRules`, `fn_8016AE60`, `gm_8016AE80`, `gm_8016AE94`, `gm_8016AEA4`, `gm_8016AEB8`, `gm_8016AEC8`, `gm_GetFrameCount`, `gm_8016AEEC`, `gm_8016AEFC`, `gm_8016AF0C`, `GetMatchTimer`, `gm_GetStKind`, `gm_8016B014`, `gm_8016B094`, `gm_8016B0B4`, `gm_8016B0D4`, `gm_8016B0E8`, `gm_8016B0FC`, `gm_8016B110`, `gm_8016B124`, `fn_8016B138`, `gm_8016B14C`, `gm_8016B168`, `gm_8016B184`, `gm_8016B1A8`, `gm_8016B1C4`, `gm_8016B1D8`, `gm_8016B1EC`, `gm_8016B204`, `gm_8016B238`, `gm_8016B248`, `gm_8016B258`, `gm_SetGameSpeed`, `gm_ResetGameSpeed`, `gm_8016B328`, `gm_8016B33C`, `gm_8016B350`, `gm_8016B364`, `gm_8016B378`, `fn_8016B388`, `gm_8016B3A0`, `gm_8016B3D8`, `gm_IsCurrently1PMode_inline`, `get_unk_float`, `gm_IsCurrently1PMode`, `fn_8016B4BC`, `fn_8016B510`, `gm_8016B558`, `fn_8016B5B0`, `gm_8016B6E8`, `fn_8016B728`, `fn_8016B738`, `gm_8016B774`, `fn_8016B784`, `fn_8016B7B4`, `fn_8016B7F8`, `fn_8016B88C`, `gm_8016B8D4`, `fn_8016B918_inline`, `fn_8016B918`, `gm_AnyControllerPressedStart`, `gm_AnyControllerPressedZ`, `gm_DefaultVSGetPauser`, `gm_CameraModeVSGetPauser`, `gm_GetFFAOutcome`, `gm_GetTeamBattleOutcome`, `gm_GetMatchOutcome`, `fn_8016C46C`, `fn_8016C46C_dontinline`, `fn_8016C4F4`, `gm_8016C5C0`, `gm_GetMatchEndPlayerScore`, `gm_8016C6C0`, `gm_8016C75C`, `fn_8016C7D0`, `fn_8016C7F0`, `gm_GetSlotByPlayerId`, `gm_DoPauseChecksAndRoutine`, `gm_GetPlayerPressingUnpause`, `gm_DoUnpauseChecksAndRoutine`, `fn_8016CD98`, `fn_8016CF4C`, `fn_8016CF4C_dontinline`, `fn_8016CFE0_inline`, `fn_8016CFE0`, `fn_8016CBE8_inline`, `gm_Scene_Training_OnFrame`, `fn_8016D538`, `fn_8016D634`, `gm_Scene_Vs_OnFrame`, `fn_8016D8AC`, `fn_8016DCC0`, `direction`, `getSpawnPoint`, `setPlayerUnk45`, `fn_8016DEEC`, `fn_8016E124`, `fn_8016E2BC`, `fn_8016E5C0`, `fn_8016E730`, `gm_Scene_Vs_OnEnter`, `gm_8016E9C8_inline`, `gm_Scene_Vs_OnExit`, `gm_Scene_SuddenDeath_OnEnter`, `gm_Scene_Training_OnEnter`, `gm_8016ECE8`, `gm_8016EDDC`, `fn_8016EF98`, `gm_8016F00C`, `fn_8016F030`, `getPort`, `gm_LoadRumbleEnabled`, `gm_8016F120`, `fn_8016F140`, `fn_8016F160`

## `src/melee/gm/gmvs.h`

144 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/forward.h`, `melee/it/forward.h`, `melee/mn/forward.h`

## `src/melee/gm/gmvsmelee.c`

344 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `gmvsmelee.h`, `Runtime/platform.h`, `melee/pl/forward.h`, `forward.h`, `gm_1A3F.h`, `gm_unsplit.h`, `gmmain_lib.h`, `gmresult.h`, `gmresultplayer.h`, `gmvsmode.h`, `types.h`, `melee/lb/inlines.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbdvd.h`, `melee/lb/lbtime.h`, `melee/mn/types.h`

Definições aparentes: `gmVsMelee_GetVsData`, `gmVsMelee_GetKOCounts`, `gmVsMelee_UpdateKOCounts`, `gmVsMelee_WasAnyPlayerHuman`, `findSmallestLoser`, `gmVsMelee_Mode_OnInit`, `gmVsMelee_ResetKOCounts`, `gmVsMelee_Mode_OnLoad`, `gm_Mode_Vs_OnUnload`, `gmVsMelee_EnterCss`, `gmVsMelee_ExitCss`, `gmVsMelee_EnterSss`, `gmVsMelee_ExitSss`, `gmVsMelee_EnterVs`, `gmVsMelee_ExitVs`, `gmVsMelee_EnterSuddenDeath`, `gmVsMelee_ExitSuddenDeath`, `gmVsMelee_EnterResults`, `gmVsMelee_ExitResults`

## `src/melee/gm/gmvsmelee.h`

51 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/gm/forward.h`, `melee/mn/forward.h`, `melee/mn/types.h`

## `src/melee/gm/gmvsmode.c`

261 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `gmvsmode.h`, `melee/lb/forward.h`, `forward.h`, `gm_1A3F.h`, `gm_unsplit.h`, `gmapproach.h`, `gmmovieend.h`, `gmresult.h`, `gmvsmelee.h`, `types.h`, `melee/if/if_2FD9.h`, `melee/lb/types.h`, `melee/mn/types.h`

Definições aparentes: `onEnterDebugVs`, `onEnterCss`, `onExitCss`, `onEnterSss`, `onExitSss`, `onEnterVs`, `onExitVs`, `onEnterSuddenDeath`, `onExitSuddenDeath`, `onEnterResults`, `onExitResults`

## `src/melee/gm/gmvsmode.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/types.h`

## `src/melee/gm/inlines.h`

66 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/gmregtyfall.h`, `melee/ty/toy.h`

Definições aparentes: `gmClampResultStat`, `fn_801A7FB4_inline`, `fn_801A7FB4_inline2`, `gmTournament_GetPlayerX`, `gmTournament_SetPlayerX`

## `src/melee/gm/types.h`

1310 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/gm/forward.h`, `melee/gr/forward.h`, `melee/pl/forward.h`, `melee/sc/forward.h`, `melee/ty/forward.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `dolphin/gx.h`, `dolphin/pad.h`, `dolphin/types.h`, `melee/mn/types.h`

