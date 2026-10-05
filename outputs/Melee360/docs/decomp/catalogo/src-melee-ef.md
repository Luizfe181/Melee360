# Catálogo: src/melee/ef

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/melee/ef/efalt.c`

539 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `efalt.h`, `placeholder.h`, `eflib.h`, `types.h`, `melee/ft/types.h`, `sysdolphin/baselib/generator.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `efAlt_Spawn`

## `src/melee/ef/efalt.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `stdarg.h`

## `src/melee/ef/efasync.c`

1471 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `efasync.h`, `stdarg.h`, `efdata.h`, `eflib.h`, `efsync.h`, `types.h`, `melee/cm/camera.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbdvd.h`, `sysdolphin/baselib/generator.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/particle.h`, `sysdolphin/baselib/psstructs.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `efAsync_GetEffectJObj`, `efAsync_SetEffectRotationZFromPtr`, `efAsync_SetEffectRandomRotationZ`, `efAsync_SetEffectScaleXYZ`, `efAsync_SetEffectScale`, `efAsync_SetEffectFacingDir`, `efAsync_Dispatch`, `efAsync_LoadAsync`, `efAsync_OnLoad`, `efAsync_LoadSync`, `efAsync_QueueProcessDeferred`, `efAsync_QueueFlush`, `efAsync_QueueClear`, `efAsync_Spawn`, `efAsync_QueueInit`

## `src/melee/ef/efasync.h`

23 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ef/forward.h`, `sysdolphin/baselib/forward.h`, `stdarg.h`

## `src/melee/ef/efdata.c`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `efdata.h`

## `src/melee/ef/efdata.h`

14 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `dolphin/types.h`, `sysdolphin/baselib/objalloc.h`

## `src/melee/ef/eflib.c`

1506 linhas; 57 definições aparentes; 0 marcadores asm.

Includes: `eflib.h`, `math.h`, `stdarg.h`, `efasync.h`, `efdata.h`, `inlines.h`, `types.h`, `dolphin/mtx.h`, `melee/ft/inlines.h`, `melee/ft/kinds/ftCommon/ftCo_Bury.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbspdisplay.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/generator.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/particle.h`, `sysdolphin/baselib/psappsrt.h`, `sysdolphin/baselib/psdisp.h`, `sysdolphin/baselib/psstructs.h`, `sysdolphin/baselib/state.h`

Definições aparentes: `eflib_create_generator_add_appsrt`, `eflib_create_effect_and_attach`, `eflib_generator_add_appsrt`, `efLib_Init`, `efLib_SetFlags`, `efLib_Destroy`, `efLib_DestroyAll`, `efLib_PauseAll`, `efLib_ResumeAll`, `efLib_remove_user_data`, `efLib_RemoveLast`, `efLib_Update`, `efLib_Create`, `efLib_Create_Attach`, `efLib_Create_AttachChild`, `efLib_Create_Attach_Scale`, `efLib_Create_AttachChild_Scale`, `efLib_Create_Attach_Scale_FacingDir`, `efLib_Create_Attach_Pos`, `efLib_render_callback`, `efLib_particles_proc_main`, `efLib_particles_proc_aux`, `efLib_CreateGenerator`, `efLib_CreateGenerator_AddAppSRT`, `efLib_CreateGenerator_Translate_FacingDir`, `efLib_CreateGenerator_Attach`, `efLib_CreateGenerator_Attach_AddAppSRT`, `efLib_CreateGenerator_Attach_Scale`, `efLib_CreateGenerator_AppSRT_SetScale`, `efLib_CreateGenerator_AppSRT_SetFacingDir`, `efLib_CreateGenerator_AppSRT_SetFacingDirScale`, `efLib_SpawnParticleEffect`, `efLib_Cb_SPtcl`, `efLib_Cb_DPtcl`, `efLib_Cb_ParticleRender`, `efLib_Cb_PtclAppSRTHook`, `efLib_Cb_SetOffsetY_FromParamY`, `efLib_Cb_SetScale_FromParamX`, `efLib_Cb_SetRotYAndTransition`, `efLib_Cb_SetJObjOffsetZ`, `efLib_Cb_SetRotY_FromFighterDir`, `efLib_Cb_SetRotYZ_FromFighter`, `efLib_Cb_Fall_FromParamY`, `efLib_Cb_SetOffset_FromParams`, `efLib_Cb_LifetimeEndSpawn`, `efLib_Cb_SetScaleRotY_FromFighter`, `efLib_Cb_SetRotYZ_FromParamZ_FighterDir`, `efLib_Cb_ftMr_SpecialLw`, `efLib_Cb_ftLg_SpecialLw`, `efLib_Cb_ftKp_SpecialHi`, `efLib_Cb_ftCo_Bury`, `efLib_SetTevKonstColor`, `efLib_SetParamAlpha`, `efLib_SetParamGfxId`, `efLib_Cb_ApplyStoredAlpha`, `efLib_Cb_AccumOffset_FromParams`, `efLib_CreateGenerator_AppSRT_SetPos`

## `src/melee/ef/eflib.h`

124 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ef/forward.h`, `sysdolphin/baselib/forward.h`, `stdarg.h`, `dolphin/mtx.h`

## `src/melee/ef/efsync.c`

662 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `efsync.h`, `math.h`, `efalt.h`, `efasync.h`, `efdata.h`, `eflib.h`, `types.h`, `melee/ft/inlines.h`, `sysdolphin/baselib/generator.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/psstructs.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `efSync_GetEffect`, `efSync_GetGenerator`, `efSync_Spawn`

## `src/melee/ef/efsync.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/ef/forward.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/ef/inlines.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/ef/types.h`

116 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ef/forward.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `dolphin/mtx.h`, `dolphin/types.h`, `melee/sc/types.h`

