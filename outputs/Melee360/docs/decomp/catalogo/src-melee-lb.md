# Catálogo: src/melee/lb

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/melee/lb/forward.h`

138 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/lb/inlines.h`

28 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`

Definições aparentes: `lbCardGame_SetupArchive`

## `src/melee/lb/lb_00B0.c`

759 linhas; 43 definições aparentes; 0 marcadores asm.

Includes: `lb_00B0.h`, `dolphin/mtx.h`, `melee/sc/types.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/pobj.h`, `sysdolphin/baselib/quatlib.h`, `sysdolphin/baselib/robj.h`

Definições aparentes: `lb_8000B074`, `lb_8000B09C`, `lb_8000B134`, `lb_8000B1CC`, `lb_8000B4FC`, `lb_8000B5DC`, `lb_8000B6A4`, `lb_8000B760`, `lb_8000B804`, `lb_8000B9D8`, `lb_8000BA0C`, `lbDObjSetRateAll`, `lbDObjReqAnimAll`, `lbFindJObjWithAObj`, `lbGetJObjFramerate`, `lbGetJObjCurrFrame`, `lbGetJObjEndFrame`, `lb_8000BECC`, `lb_8000BFF0`, `lb_8000C07C`, `lb_8000C0E8`, `memzero`, `lb_8000C1C0`, `lb_8000C228`, `lb_8000C290`, `lb_8000C2F8`, `robj_next`, `lb_8000C390`, `lb_8000C420`, `lb_8000C490`, `lbCopyJObjSRT`, `lb_8000C868`, `lbGetFreeColorRegImpl`, `lbGetFreeColorRegister`, `lb_8000CC8C`, `lb_8000CCA4`, `lbGetFreeAlphaRegImpl`, `lbGetFreeAlphaRegister`, `lb_8000CD90`, `lb_8000CDA8`, `lb_8000CDC0`, `lb_8000CE30`, `lb_8000CE40`

## `src/melee/lb/lb_00B0.h`

55 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/sc/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `sysdolphin/baselib/jobj.h`

## `src/melee/lb/lb_00CE.c`

217 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `lb_00CE.h`, `placeholder.h`, `Runtime/platform.h`, `math.h`

Definições aparentes: `sdata2_order`, `expf`, `powf`, `powi`, `lb_8000D008`, `lb_8000D148`

## `src/melee/lb/lb_00CE.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/lb/lb_00F9.c`

1098 linhas; 24 definições aparentes; 0 marcadores asm.

Includes: `lb_00F9.h`, `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `math.h`, `placeholder.h`, `stddef.h`, `forward.h`, `lbcollision.h`, `lbspdisplay.h`, `lbvector.h`, `types.h`, `dolphin/mtx.h`, `melee/mp/mplib.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/psstructs.h`, `sysdolphin/baselib/quatlib.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `order_data`, `checkJObjFlags`, `lb_8000F9F8`, `lb_8000FA94`, `lb_8000FCDC`, `lb_8000FD18`, `popDynamicsData`, `lb_8000FD48`, `inlineA0`, `inlineA1`, `lb_800100B0`, `lb_800101C8`, `lb_800103B8`, `lb_800103D8`, `approximatelyZeroVec3`, `absf`, `groundHeight`, `lb_8001044C`, `lb_800115F4`, `lb_80011710`, `lb_800117F4`, `lb_800119DC`, `lb_80011A50`, `lb_80011ABC`

## `src/melee/lb/lb_00F9.h`

37 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `dolphin/gx/GXStruct.h`, `dolphin/mtx.h`

## `src/melee/lb/lb_013B.c`

262 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `forward.h`, `lbarchive.h`, `lbcommand.h`, `types.h`, `dolphin/pad.h`, `sysdolphin/baselib/rumble.h`

Definições aparentes: `lb_80013BB0`, `lb_80013BB8`, `lb_80013BE4`, `lb_80013C18`, `lb_80013D68`, `lb_80013E3C`, `lb_80013F78`, `lb_80013FF0`, `lb_80014014`, `lb_800140F8`, `lb_80014234`, `lb_80014258`, `lb_80014498`, `lb_800144C8`, `lb_80014534`, `lb_80014574`, `lb_800145C0`, `lb_800145F4`

## `src/melee/lb/lb_013B.h`

17 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/lb/forward.h`

## `src/melee/lb/lb_0146.c`

154 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `types.h`, `dolphin/gx/GXCull.h`, `dolphin/gx/GXGeometry.h`, `dolphin/gx/GXLighting.h`, `dolphin/gx/GXPixel.h`, `dolphin/gx/GXTev.h`, `dolphin/gx/GXTransform.h`, `dolphin/gx/GXVert.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/psstructs.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `lb_80014638`, `lb_80014770`, `lb_800149E0`

## `src/melee/lb/lb_0146.h`

17 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `melee/lb/types.h`

## `src/melee/lb/lb_0192.c`

190 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `lb_0192.h`, `lbaudio_ax.h`, `lblanguage.h`, `dolphin/dvd.h`, `melee/gm/gmmain_lib.h`, `melee/gm/types.h`, `sysdolphin/baselib/initialize.h`, `sysdolphin/baselib/rumble.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/video.h`

Definições aparentes: `lb_80019230`, `lb_800192A8`

## `src/melee/lb/lb_0192.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/lb/lb_0195.c`

191 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `lb_0195.h`, `lb_0192.h`, `lbaudio_ax.h`, `lbcardgame.h`, `lbcardnew.h`, `lbsnap.h`, `dolphin/os.h`, `dolphin/vi.h`, `sysdolphin/baselib/controller.h`

Definições aparentes: `lb_8001955C`, `lb_800195D0`, `fn_800195FC`, `lb_80019628`, `lb_80019880`, `lb_80019894`, `lb_800198E0`, `lb_80019900`, `lb_80019A30`, `lb_80019A48`, `lb_80019AAC`

## `src/melee/lb/lb_0195.h`

18 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/lb/lb_01F8.c`

119 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `string.h`, `lbfile.h`, `lbmthp.h`, `dolphin/thp/thp.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sobjlib.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `lbMthp8001F890`, `lbMthp8001F928`, `lbMthp8001FAA0`

## `src/melee/lb/lb_020A.c`

415 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `lb_020A.h`, `math.h`, `placeholder.h`, `lbvector.h`, `dolphin/mtx.h`, `melee/ft/types.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mtx.h`, `sysdolphin/baselib/quatlib.h`

Definições aparentes: `fn_80020AEC`, `lbBgFlash_80020E38`, `fn_8002113C`, `calc_acos`, `sqrtf_store`, `lbBgFlash_80021410`

## `src/melee/lb/lb_020A.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`

## `src/melee/lb/lb_0219.c`

120 linhas; 8 definições aparentes; 0 marcadores asm.

Includes: `lb_0219.h`, `placeholder.h`, `lb_013B.h`, `lbarchive.h`, `lbbgflash.h`, `types.h`, `dolphin/gx/GXStruct.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/objalloc.h`

Definições aparentes: `lbBgFlash_Free`, `lbBgFlash_SetFlashScale`, `lbBgFlash_Init`, `lbBgFlash_Proc`, `fn_80021C18`, `fn_80021C1C`, `lbBgFlash_80021C48`, `fn_80021C80`

## `src/melee/lb/lb_0219.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/melee/lb/lbanim.c`

145 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `lbanim.h`, `placeholder.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/fobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `lbAnim_InitFrames`, `fn_8001E60C`, `lbAnim_JObjSortAnim`, `lbAnim_8001E6D8`, `lbAnim_8001E7E8`, `lbAnim_8001E8F8`

## `src/melee/lb/lbanim.h`

38 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `sysdolphin/baselib/fobj.h`

## `src/melee/lb/lbarchive.c`

264 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `lbarchive.h`, `stdarg.h`, `string.h`, `lbdvd.h`, `lbfile.h`, `lbheap.h`, `dolphin/os.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/debug.h`

Definições aparentes: `lbArchive_InitializeDAT`, `vLoadSections`, `readArchive`, `loadArchive`, `lbArchive_LoadArchive`, `vLoadSectionsFatal`, `lbArchive_80016EFC`, `lbArchive_80016F80`, `Locate`, `lbArchiveRelocate`

## `src/melee/lb/lbarchive.h`

52 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/archive.h`

## `src/melee/lb/lbarq.c`

173 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `lbarq.h`, `placeholder.h`, `dolphin/ar.h`, `dolphin/os.h`, `sysdolphin/baselib/debug.h`

Definições aparentes: `lbArq_80014ABC`, `lbArq_80014AC4`, `lbArq_80014BD0`, `lbArq_80014D2C`

## `src/melee/lb/lbarq.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `stddef.h`

## `src/melee/lb/lbaudio_ax.c`

2597 linhas; 104 definições aparentes; 0 marcadores asm.

Includes: `lbaudio_ax.h`, `Runtime/platform.h`, `melee/ft/forward.h`, `stdbool.h`, `stddef.h`, `string.h`, `lb_0195.h`, `lbarchive.h`, `lblanguage.h`, `dolphin/ai.h`, `dolphin/ar.h`, `dolphin/ax.h`, `dolphin/axfx.h`, `melee/cm/camera.h`, `melee/ft/ftlib.h`, `melee/gm/gm_1601.h`, `melee/gm/gm_16A2.h`, `melee/gm/gmvs.h`, `melee/gr/stage.h`, `melee/it/it_26B1.h`, `melee/pl/player.h`, `sysdolphin/baselib/axdriver.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/objalloc.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/synth.h`

Definições aparentes: `lbAudioAx_8002305C`, `lbAudioAx_80023090`, `lbAudioAx_800230C8`, `lbAudioAx_80023130`, `lbAudioAx_80023220`, `fn_80023254_shift`, `fn_80023254`, `lbAudioAx_800233EC`, `lbAudioAx_80023694`, `lbAudioAx_800236B8`, `lbAudioAx_800236DC`, `lbAudioAx_80023710`, `lbAudioAx_80023730`, `fn_80023750`, `lbAudioAx_800237A8`, `lbAudioAx_80023870`, `lbAudioAx_8002392C`, `getAudioLoadData`, `lbAudioAx_80023968`, `lbAudioAx_80023A44`, `fn_800269AC_delay`, `lbAudioAx_80023B24`, `fn_80023ED4`, `getHPSFile`, `lbAudioAx_80023F28_helper1`, `lbAudioAx_80023F28`, `lbAudioAx_80024030`, `lbAudioAx_800240B4`, `lbAudioAx_8002411C`, `lbAudioAx_80024184`, `lbAudioAx_80024304`, `lbAudioAx_8002438C`, `lbAudioAx_800243F4`, `fn_800244F4`, `lbAudioAx_800245D4`, `lbAudioAx_800245F4`, `lbAudioAx_80024614`, `lbAudioAx_80024634`, `fn_80024654`, `lbAudioAx_80024B1C`, `lbAudioAx_80024B58`, `lbAudioAx_80024B94`, `lbAudioAx_80024BD0`, `lbAudioAx_80024C08`, `lbAudioAx_80024C84`, `lbAudioAx_80024D50`, `lbAudioAx_80024D78`, `lbAudioAx_80024DC4`, `lbAudioAx_80024E50`, `lbAudioAx_80024E84`, `lbAudioAx_80024F08`, `lbAudioAx_80024F6C`, `lbAudioAx_80024FDC`, `lbAudioAx_80024FF4`, `lbAudioAx_8002500C`, `lbAudioAx_80025038`, `lbAudioAx_80025064`, `lbAudioAx_80025098`, `calcPan`, `soundGetPosition`, `fn_800251EC`, `fn_800253D8`, `fn_800256BC`, `fn_800259A0`, `fn_800259EC`, `fn_80025A98`, `fn_80025B44`, `fn_80025CBC`, `fn_80025E38`, `fn_80025FAC`, `fn_800262A0`, `lbAudioAx_ObjFree`, `lbAudioAx_800263E8`, `lbAudioAx_800264E4`, `lbAudioAx_80026510`, `lbAudioAx_800265C4`, `fn_80026650`, `fn_800267B0`, `fn_800268B4`, `fn_800269AC`, `fn_80026C04`, `fn_80026E58`, `lbAudioAx_80026E84`, `lbAudioAx_80026EBC`, `lbAudioAx_80026F2C`, `lbAudioAx_8002702C`, `lbAudioAx_80027168_inline`, `lbAudioAx_80027168_inline_2`, `lbAudioAx_80027168`, `fn_80027488`, `lbAudioAx_80027648`, `lbAudioAx_8002785C`, `setup_audio_lang`, `lbAudioAx_80027AB0`, `lbAudioAx_80027DBC`, `lbAudioAx_80027DF8_inline`, `lbAudioAx_80027DF8`, `lbAudioAx_8002835C`, `lbAudioAx_8002838C`, `lbAudioAx_80028690`, `lbAudioAx_80028B2C`, `lbAudioAx_80028B4C`, `lbAudioAx_80028B6C`, `lbAudioAx_80028B90`

## `src/melee/lb/lbaudio_ax.h`

98 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/gr/forward.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/gobj.h`

## `src/melee/lb/lbbgflash.c`

503 linhas; 12 definições aparentes; 1 marcadores asm.

Includes: `lbbgflash.h`, `placeholder.h`, `dolphin/gx/GXStruct.h`, `sysdolphin/baselib/wobj.h`, `dolphin/gx.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/hsd_3915.h`

Definições aparentes: `fn_8001FC08`, `sdata2_order`, `fn_8001FEC4`, `fn_800204C8`, `lbBgFlash_800205F0`, `lbBgFlash_8002063C`, `lbBgFlash_80020688`, `lbBgFlash_800206D4`, `lbBgFlash_InitState`, `fn_800208B0`, `lbBgFlash_800208EC`, `lbBgFlash_800209F4`

## `src/melee/lb/lbbgflash.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/gx/GXStruct.h`, `sysdolphin/baselib/gobj.h`

## `src/melee/lb/lbcardgame.c`

344 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `lbcardgame.h`, `lbarchive.h`, `lbcardnew.h`, `lblanguage.h`, `dolphin/card.h`, `dolphin/os.h`, `melee/gm/gm_unsplit.h`, `melee/gm/gmmain_lib.h`, `melee/gm/types.h`, `melee/if/textlib.h`, `melee/sc/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `lb_8001C600`, `lb_8001C658`, `getCurrentIcon`, `lb_8001C87C`, `lb_8001C8BC`, `updateCardStatus`, `lbCardGame_SetCardStatus`, `lb_8001CBBC`, `fn_8001CC30`, `lb_8001CC4C`, `dont_inline_helper`, `lb_8001CC84`, `lb_8001CDB4`, `lbCardGame_SaveChanges`, `lbCardGame_DecideGameMode`, `gobj1_Proc`, `gobj0_RenderFunc`, `lbCardGame_InitScene`, `lbCardGame_LoadArchive`, `lbCardGame_Reset`, `lbCardGame_Init`

## `src/melee/lb/lbcardgame.h`

32 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/lb/lbcardnew.h`

## `src/melee/lb/lbcardnew.c`

1226 linhas; 50 definições aparentes; 0 marcadores asm.

Includes: `lbcardnew.h`, `Runtime/platform.h`, `ctype.h`, `placeholder.h`, `stdlib.h`, `string.h`, `types.h`, `dolphin/card.h`, `sysdolphin/baselib/card.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/memory.h`

Definições aparentes: `convertSdkResult`, `lb_80019C38_noinline`, `getNewTask`, `resetTaskArray`, `executeNextTask`, `resetState`, `onCardComplete`, `convertHsdResult`, `fn_8001A0B0`, `taskMount`, `taskCheck`, `setTaskFilename`, `setupCardEntries`, `taskOpen`, `taskUnk3`, `taskFormat`, `taskDelete`, `taskRename`, `taskCreate`, `readCardFileSize`, `taskRead`, `taskWrite`, `taskSetStatus`, `taskReadHeader`, `taskListSnapshots`, `taskFindFile`, `lb_8001B6E0`, `lbCardNew_CompleteNextTask`, `lbCardNew_CompleteAllTasks`, `setupTask`, `addTaskEntries`, `addTask`, `lb_8001A4CC_dontinline`, `lb_8001B7E0`, `lb_8001B8C8`, `lbCardNew_DeleteSnap`, `lb_8001BA44`, `lb_8001BB48`, `lb_8001BC18`, `lb_8001BD34`, `lb_8001BE30`, `lb_8001BF04`, `lb_8001BFD8`, `lb_8001C0F4`, `lb_8001C2D8`, `lbCardNew_ProbeEx`, `lb_8001C4A8`, `lbCardNew_AllocWorkArea`, `lbCardNew_ForgetMemory`, `lbCardNew_Init`

## `src/melee/lb/lbcardnew.h`

70 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/lb/forward.h`, `placeholder.h`

## `src/melee/lb/lbcollision.c`

2677 linhas; 48 definições aparentes; 0 marcadores asm.

Includes: `lbcollision.h`, `Runtime/platform.h`, `math.h`, `placeholder.h`, `forward.h`, `lb_00B0.h`, `lbaudio_ax.h`, `lbvector.h`, `types.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `melee/ft/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mtx.h`, `sysdolphin/baselib/state.h`, `sysdolphin/baselib/tev.h`

Definições aparentes: `lbColl_80005BB0`, `lbColl_80005C44`, `lbColl_80005EBC`, `lbColl_80005FC0`, `end`, `lbColl_80006094`, `lbColl_GetY`, `lbColl_DifferenceY`, `lbColl_800067F8`, `lbColl_80006E58`, `sqrDistance`, `sqrtf_store`, `lbColl_800077A0`, `lbColl_80007AFC`, `lbColl_80007B78`, `lbColl_80007BCC`, `lbColl_80007DD8`, `lbColl_80007ECC`, `lbColl_8000805C`, `lbColl_80008248`, `lbColl_800083C4`, `lbColl_80008428`, `lbColl_80008434`, `lbColl_80008440`, `lbColl_CopyHitCapsule`, `lbColl_80008688`, `lbColl_80008820`, `lbColl_800089B8`, `lbColl_80008A5C`, `lbColl_80008D30`, `lbColl_80008DA4`, `isSmall`, `lbColl_80008FC8`, `lbColl_800096B4`, `lbColl_80009DD4`, `lbColl_80009F54`, `lbColl_DrawHitResult`, `lbColl_8000A044`, `lbColl_8000A10C`, `lbColl_8000A1A8`, `lbColl_8000A244`, `lbColl_8000A460`, `lbColl_8000A584`, `lbColl_DrawHit`, `lbColl_8000A78C`, `lbColl_8000A95C`, `lbColl_8000AB2C`, `lbColl_8000ACFC`

## `src/melee/lb/lbcollision.h`

123 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `dolphin/gx/GXStruct.h`, `dolphin/mtx.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `approximatelyZero`, `testPlusX`, `testPlus`, `testMinusX`

## `src/melee/lb/lbcommand.c`

98 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `lbcommand.h`, `inlines.h`, `lb_0219.h`, `types.h`

Definições aparentes: `Command_00`, `Command_01`, `Command_02`, `Command_03`, `Command_04`, `Command_05`, `Command_06`, `Command_07`, `Command_08`, `Command_09`, `Command_Execute`

## `src/melee/lb/lbcommand.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/lb/forward.h`

## `src/melee/lb/lbdvd.c`

841 linhas; 35 definições aparentes; 0 marcadores asm.

Includes: `lbdvd.h`, `melee/ft/forward.h`, `melee/gm/forward.h`, `string.h`, `lb_0195.h`, `lbarchive.h`, `lbfile.h`, `lbheap.h`, `lbmemory.h`, `types.h`, `dolphin/dvd.h`, `melee/db/db.h`, `melee/ef/efasync.h`, `melee/gm/gmcameramode.h`, `melee/gr/grdatfiles.h`, `melee/gr/stage.h`, `melee/pl/player.h`, `sysdolphin/baselib/debug.h`

Definições aparentes: `lbDvd_SetupVsPreloadCache`, `releaseEntry`, `lbDvd_800174E8`, `lbDvd_80017598`, `lbDvd_80017644`, `lbDvd_80017700`, `same`, `lbDvd_80017740`, `lbDvd_800178E8`, `lbDvd_80017960`, `lbDvd_80017A80`, `cleanupPreloadHeap`, `lbDvd_CachePreloadedFile`, `lbDvd_80017CC4`, `lbDvd_80017E64`, `lbDvd_GetPreloadedArchive`, `preloadFile`, `preloadRumbleFile`, `preloadCommonFiles`, `lbDvd_8001819C`, `lbDvd_GetPreloadCacheScene`, `lbDvd_8001823C`, `negateLoadScores`, `releaseNegativeEntries`, `lbDvd_80018254`, `lbDvd_800187F4`, `lbDvd_800189EC`, `lbDvd_80018A2C`, `lbDvd_80018C2C`, `lbDvd_80018C6C`, `releaseHeap`, `releaseListedHeaps`, `lbDvd_80018CF4`, `lbDvd_80018F58`, `lbDvd_80018F68`

## `src/melee/lb/lbdvd.h`

37 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`

## `src/melee/lb/lbfile.c`

176 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `lbfile.h`, `placeholder.h`, `string.h`, `lb_0195.h`, `lbdvd.h`, `lbheap.h`, `lblanguage.h`, `dolphin/dvd.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/devcom.h`

Definições aparentes: `lbFile_8001615C`, `discIsDone`, `waitForDisc`, `lbFile_800161C4`, `lbFileGetFullName`, `lbFile_8001634C`, `lbFileGetSize`, `lbFile_800164A4`, `lbFile_80016580`, `lbFile_8001668C`, `loadFile`, `lbFile_80016760`, `lbFile_800168A0`

## `src/melee/lb/lbfile.h`

51 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/melee/lb/lbgx.c`

85 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `lbgx.h`, `placeholder.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `sysdolphin/baselib/cobj.h`

Definições aparentes: `lbGx_8001E2F8`

## `src/melee/lb/lbgx.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/mtx.h`

## `src/melee/lb/lbheap.c`

331 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `lbheap.h`, `lbmemory.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/initialize.h`, `sysdolphin/baselib/memory.h`

Definições aparentes: `resetHeap`, `destroyHeap`, `createHeap`, `lbHeap_800158D0`, `lbHeap_800158E8`, `lbHeap_80015900`, `lbHeap_80015BB8`, `lbHeap_80015BD0`, `lbHeap_80015CA8`, `lbHeap_80015D6C`, `lbHeap_80015DF8`, `lbHeap_80015F3C`

## `src/melee/lb/lbheap.h`

36 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/lb/lblanguage.c`

50 linhas; 8 definições aparentes; 0 marcadores asm.

Includes: `lblanguage.h`, `melee/gm/gmmain_lib.h`, `melee/gm/types.h`

Definições aparentes: `lbLang_GetLanguageSetting`, `lbLang_SetLanguageSetting`, `lbLang_IsSettingJP`, `lbLang_IsSettingUS`, `lbLang_GetSavedLanguage`, `lbLang_SetSavedLanguage`, `lbLang_IsSavedLanguageJP`, `lbLang_IsSavedLanguageUS`

## `src/melee/lb/lblanguage.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/lb/lbmemory.c`

321 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `lbmemory.h`, `Runtime/platform.h`, `string.h`, `dolphin/ar.h`, `dolphin/os/OSAlarm.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/devcom.h`

Definições aparentes: `lbMemory_80014E24`, `lbMemory_80014EEC`, `lbMemory_80014F7C`, `lbMemory_80014FC8`, `lbMemFreeToHeap`, `fn_80015184`, `lbMemory_8001529C`, `start_ram_copy`, `lbMemory_80015320`, `lbMemory_800154BC`, `lbMemory_800154D4`, `lbMemory_800155A4`, `lbMemory_8001564C`

## `src/melee/lb/lbmemory.h`

33 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/lb/forward.h`

## `src/melee/lb/lbmthp.c`

660 linhas; 24 definições aparentes; 0 marcadores asm.

Includes: `lbmthp.h`, `placeholder.h`, `lbfile.h`, `dolphin/dvd.h`, `dolphin/gx/GXTexture.h`, `dolphin/os.h`, `dolphin/thp/thp.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/devcom.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sobjlib.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/video.h`

Definições aparentes: `fn_8001E910`, `fn_8001EB14`, `fn_8001EBF0`, `fn_8001ECF4`, `fn_8001EF5C`, `fn_8001F06C`, `fn_8001F13C`, `fn_8001F294`, `lbMthp_GetFrame`, `lbMthp_GetPlayer`, `lbMthp_GetDecoder`, `fn_8001F2A4`, `lbMthp_8001F410`, `lbMthp_8001F578`, `lbMthp_8001F5C4`, `lbMthp_8001F5D4`, `lbMthp_8001F5E4`, `lbMthp_8001F5F4`, `lbMthp_8001F604`, `lbMthp_8001F614`, `lbMthp_8001F624`, `lbMthp_8001F67C`, `lbMthp_8001F800`, `lbMthp_8001F87C`

## `src/melee/lb/lbmthp.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `stddef.h`

## `src/melee/lb/lbrefract.c`

679 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `lbrefract.h`, `math.h`, `placeholder.h`, `string.h`, `lbarchive.h`, `types.h`, `dolphin/gx/GXBump.h`, `dolphin/gx/GXEnum.h`, `dolphin/gx/GXGeometry.h`, `dolphin/gx/GXLighting.h`, `dolphin/gx/GXPixel.h`, `dolphin/gx/GXTev.h`, `dolphin/gx/GXTexture.h`, `dolphin/gx/GXTransform.h`, `dolphin/os/OSCache.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/pobj.h`, `sysdolphin/baselib/state.h`

Definições aparentes: `lbRefract_WriteTexCoord`, `my_fmodf`, `lbRefract_80021CE8`, `lbRefract_WriteTexCoordIA4`, `fn_80021F70`, `fn_80021FB4`, `fn_80021FF8`, `fn_8002206C`, `lbRefract_ReadTexCoordRGBA8`, `lbRefract_8002219C`, `lbRefract_800222A4`, `lbRefract_8002247C`, `lbRefract_80022560`, `lbRefract_800225D4`, `lbRefract_DObjDispReset`, `fn_80022650`, `lbRefract_PObjLoad`, `fn_80022940`, `lbRefract_80022998`, `lbRefract_80022BB8`, `lbRefSetUnuse`

## `src/melee/lb/lbrefract.h`

40 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/melee/lb/lbshadow.c`

570 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `lbshadow.h`, `lbvector.h`, `types.h`, `dolphin/gx/GXVert.h`, `melee/cm/types.h`, `melee/ft/ftdrawcommon.h`, `melee/ft/ftlib.h`, `melee/ft/types.h`, `melee/gr/ground.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/initialize.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/perf.h`, `sysdolphin/baselib/pobj.h`, `sysdolphin/baselib/shadow.h`, `sysdolphin/baselib/spline.h`, `sysdolphin/baselib/state.h`, `sysdolphin/baselib/tev.h`, `sysdolphin/baselib/util.h`, `sysdolphin/baselib/video.h`

Definições aparentes: `splGetCardinalTangent`, `splGetBSplineTangent`, `splGetBezierTangent`, `lbShadow_8000E9F0`, `lbShadow_8000ED54`, `lbShadow_8000EE8C`, `lbShadow_8000EEE0`, `lbShadow_8000EFEC`, `lbShadow_8000F214`, `my_sqrtf`, `lbShadow_8000F38C`

## `src/melee/lb/lbshadow.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `sysdolphin/baselib/spline.h`

## `src/melee/lb/lbsnap.c`

479 linhas; 27 definições aparentes; 0 marcadores asm.

Includes: `lbsnap.h`, `placeholder.h`, `stdio.h`, `lbarchive.h`, `lbcardnew.h`, `lblanguage.h`, `types.h`, `melee/it/types.h`, `MetroTRK/intrinsics.h`, `dolphin/card.h`, `dolphin/os.h`, `melee/ft/ft_0877.h`, `melee/gm/gm_unsplit.h`, `melee/it/itspawn.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/hsd_3B34.h`

Definições aparentes: `lbSnap_8001D2BC`, `lbSnap_8001D338`, `lbSnap_8001D350`, `lbSnap_8001D394`, `lbSnap_8001D3B0`, `lbSnap_8001D3CC`, `lbSnap_8001D3E8`, `lbSnap_8001D40C`, `lbSnap_8001D4A4`, `lbSnap_ClearText`, `lbSnap_FormatTime`, `lbSnap_8001D5FC`, `lbSnap_8001D7B0`, `RGB565_TO_RGB5A3`, `lbSnap_GetMemSnapIconData`, `lbSnap_8001DA5C`, `lbSnap_8001DC0C`, `lbSnap_8001DE8C`, `lbSnap_GetSaveDataOffset`, `lbSnap_8001DF20`, `lbSnap_8001DF6C`, `lbSnap_8001E058`, `lbSnap_8001E204`, `lbSnap_8001E210`, `lbSnap_8001E218`, `lbSnap_8001E27C`, `lbSnap_8001E290`

## `src/melee/lb/lbsnap.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/lb/forward.h`

## `src/melee/lb/lbspdisplay.c`

735 linhas; 20 definições aparentes; 0 marcadores asm.

Includes: `lbspdisplay.h`, `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `stdarg.h`, `stddef.h`, `lbdvd.h`, `types.h`, `dolphin/gx/GXCull.h`, `dolphin/gx/GXGeometry.h`, `dolphin/gx/GXPixel.h`, `dolphin/gx/GXTev.h`, `dolphin/gx/GXTexture.h`, `dolphin/gx/GXTransform.h`, `dolphin/gx/GXVert.h`, `melee/sc/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/psstructs.h`, `sysdolphin/baselib/state.h`, `sysdolphin/baselib/tev.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `lb_80011AC4`, `lb_80011B74`, `checkJObjFlags`, `lb_80011C18`, `lb_80011E24`, `lb_8001204C`, `setImageFromPreloadedArchive`, `lb_800121FC`, `lb_800122C8`, `lb_800122F0`, `lb_8001271C`, `lb_8001285C`, `setTevAlpha`, `lb_80012994`, `fn_80013614`, `fn_800138AC`, `lb_800138CC`, `lb_800138D8`, `lb_800138EC`, `lb_80013B14`

## `src/melee/lb/lbspdisplay.h`

35 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/sc/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx.h`

## `src/melee/lb/lbtime.c`

66 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `lbtime.h`

Definições aparentes: `lbTime_8000AEC8`, `lbTime_8000AEE4`, `lbTime_8000AF24`, `lbTime_8000AF74`, `lbTime_GetTimeInSeconds`, `lbTime_8000B028`

## `src/melee/lb/lbtime.h`

15 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/os.h`

## `src/melee/lb/lbtrigf.c`

243 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `lbtrigf.h`, `Runtime/platform.h`, `math.h`, `placeholder.h`

Definições aparentes: `atan2f`, `acosf`, `asinf`, `lb_sqrtf`, `atanf`

## `src/melee/lb/lbtrigf.h`

4 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/lb/lbvector.c`

524 linhas; 26 definições aparentes; 0 marcadores asm.

Includes: `lbvector.h`, `Runtime/platform.h`, `math.h`, `placeholder.h`, `dolphin/gx/GXTransform.h`, `dolphin/mtx.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/debug.h`

Definições aparentes: `lbVector_Len_xy_accurate`, `lbVector_Normalize`, `lbVector_NormalizeXY`, `lbVector_Add`, `lbVector_Add_xy`, `lbVector_Sub`, `lbVector_Diff`, `lbVector_CrossprodNormalized`, `lbVector_Angle`, `lbVector_AngleXY`, `lbvector_sin`, `lbvector_cos`, `lbVector_RotateAboutUnitAxis`, `lbVector_Rotate`, `order_sdata2`, `lbVector_Mirror`, `lbVector_CosAngle`, `lbVector_Lerp`, `lbVector_8000DE38`, `lbVector_EulerAnglesFromONB`, `lbVector_EulerAnglesFromPartialONB`, `lbVector_ApplyEulerRotation`, `lbVector_sqrtf_accurate`, `lbVector_WorldToScreen`, `lbVector_CreateEulerMatrix`, `lbVector_8000E838`

## `src/melee/lb/lbvector.h`

51 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `math.h`, `dolphin/mtx.h`

Definições aparentes: `lbVector_Len`, `lbVector_Len_xy`

## `src/melee/lb/types.h`

1050 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/gr/forward.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `placeholder.h`, `dolphin/gx.h`, `dolphin/mtx.h`

