# Catálogo: src/melee/db

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/melee/db/db.h`

85 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/it/forward.h`, `sysdolphin/baselib/controller.h`

## `src/melee/db/dballoc.c`

62 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `db.h`, `melee/ef/efdata.h`, `melee/gm/types.h`, `sysdolphin/baselib/generator.h`, `sysdolphin/baselib/psappsrt.h`

Definições aparentes: `fn_SetupObjAllocLimiter`, `fn_UpdateObjAllocLimiter`

## `src/melee/db/dbanim.c`

222 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `db.h`, `melee/ft/ftlib.h`, `melee/ft/inlines.h`, `melee/ft/kinds/ftCommon/ftCo_KinokoGiantEnd.h`, `melee/ft/kinds/ftCommon/ftCo_KinokoGiantStart.h`, `melee/ft/kinds/ftCommon/ftCo_KinokoSmallEnd.h`, `melee/ft/kinds/ftCommon/ftCo_KinokoSmallStart.h`, `melee/if/textdraw.h`, `melee/if/textlib.h`, `melee/pl/player.h`

Definições aparentes: `fn_SetupAnimationInfo`, `fn_ToggleMiscFighterVisuals`, `fn_8022697C`, `fn_UpdateAnimationInfo`, `fn_CheckAnimationInfo`

## `src/melee/db/dbbonus.c`

155 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `db.h`, `melee/gm/gm_unsplit.h`, `melee/if/textdraw.h`, `melee/if/textlib.h`, `melee/pl/player.h`, `melee/pl/plbonus.h`, `sysdolphin/baselib/memory.h`

Definições aparentes: `fn_SetupBonusInfo`, `fn_80228D18`, `fn_80228D38`, `fn_80228E54`, `fn_8022900C`, `fn_CheckBonusInfo`

## `src/melee/db/dbcamera.c`

630 linhas; 20 definições aparentes; 0 marcadores asm.

Includes: `math.h`, `db.h`, `melee/cm/camera.h`, `melee/ft/inlines.h`, `melee/gm/gm_unsplit.h`, `melee/gr/ground.h`, `melee/if/textdraw.h`, `melee/if/textlib.h`, `melee/lb/lbshadow.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/controller.h`

Definições aparentes: `fn_SetupMiscStageVisuals`, `fn_CheckMiscStageEffects`, `fn_802270C4`, `fn_8022713C`, `fn_SetupCameraInfo`, `fn_CheckCameraInfo_helper`, `fn_80227188`, `fn_CheckCameraInfo`, `cstick_threshold`, `fn_802277E8`, `fn_80227904`, `fn_802279E8`, `fn_80227B64`, `fn_80227BA8`, `fn_80227CAC`, `fn_80227D38`, `fn_80227EB0`, `fn_80227FE0`, `fn_80227EB0_dummy_inline`, `fn_80228124`

## `src/melee/db/dbcpu.c`

66 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `db.h`, `melee/if/textdraw.h`, `melee/if/textlib.h`, `melee/pl/player.h`

Definições aparentes: `fn_SetupCpuHandicapInfo`, `fn_UpdateCpuHandicapInfo`, `fn_CheckCpuHandicapInfo`

## `src/melee/db/dbeffect.c`

21 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `db.h`, `melee/if/ifall.h`

Definições aparentes: `fn_CheckMiscVisualEffects`

## `src/melee/db/dberror.c`

81 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `stdarg.h`, `db.h`, `dolphin/base/PPCArch.h`, `dolphin/db.h`, `dolphin/os.h`, `melee/lb/lb_0195.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/debugconsole_main.h`, `sysdolphin/baselib/hsd_393C.h`, `sysdolphin/baselib/video.h`

Definições aparentes: `db_ClearFPUExceptions`, `fn_HSDPanicHandler`, `fn_OSErrorHandler`, `db_SetupCrashHandler`

## `src/melee/db/dbinit.c`

253 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `dbinit.h`, `db.h`, `dbsound.h`, `dolphin/card.h`, `dolphin/vi.h`, `melee/ft/ftlib.h`, `melee/lb/lbarchive.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `db_GetGameLaunchButtonState`, `db_Setup`, `db_ButtonsDown`, `db_ButtonsPressed`, `db_ButtonsRepeat`, `db_PrintEntityCounts`, `db_PrintThreadInfo`, `db_get_pad_button`, `db_get_pad_repeat`, `db_RunEveryFrame`

## `src/melee/db/dbinit.h`

12 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `dat_macros.h`

## `src/melee/db/dbitem.c`

562 linhas; 25 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `db.h`, `melee/ef/efsync.h`, `melee/ft/ftlib.h`, `melee/gm/gm_unsplit.h`, `melee/if/textdraw.h`, `melee/if/textlib.h`, `melee/if/types.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itspawn.h`, `melee/it/types.h`, `melee/pl/player.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `fn_SetupItemAndPokemonMenu`, `fn_80225A54`, `db_ShowEnemyStompRange`, `db_ShowItemPickupRange`, `db_ShowCoinPickupRange`, `fn_EnableShowCoinPickupRange`, `fn_DisableShowCoinPickupRange`, `fn_EnableShowEnemyStompRange`, `fn_DisableShowEnemyStompRange`, `fn_EnableShowItemPickupRange`, `fn_DisableShowItemPickupRange`, `db_GetCurrentlySelectedPokemon`, `db_DisableItemSpawns`, `db_EnableItemSpawns`, `db_AreItemSpawnsEnabled`, `db_80225D64`, `fn_ToggleItemCollisionBubbles`, `db_80225DD8`, `fn_80225E6C`, `db_HandleItemPokemonMenuInput`, `fn_ShowOrCreateItemAndPokemonMenu`, `fn_UpdateItemAndPokemonMenu`, `db_CheckAndSpawnItem`, `checkToggleCollisionBubbles`, `fn_CheckItemAndPokemonMenu`

## `src/melee/db/dbscreenshot.c`

98 linhas; 8 definições aparentes; 0 marcadores asm.

Includes: `string.h`, `db.h`, `melee/gm/gm_unsplit.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/hsd_3933.h`, `sysdolphin/baselib/video.h`

Definições aparentes: `fn_Setup5xSpeed`, `fn_Check5xSpeed`, `fn_Toggle5xSpeed`, `db_InitScreenshot`, `get_pad`, `db_CheckScreenshot`, `db_TakeScreenshotIfPending`, `fn_802289F8`

## `src/melee/db/dbsound.c`

138 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `db.h`, `dolphin/gx/GXStruct.h`, `melee/if/textdraw.h`, `melee/if/textlib.h`, `melee/lb/lbaudio_ax.h`

Definições aparentes: `fn_SetupSoundInfo`, `fn_UpdateSoundInfo`, `fn_CheckSoundInfo`

## `src/melee/db/dbsound.h`

9 linhas; 0 definições aparentes; 0 marcadores asm.

