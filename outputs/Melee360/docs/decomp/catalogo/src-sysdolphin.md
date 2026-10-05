# Catálogo: src/sysdolphin

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/sysdolphin/baselib/aobj.c`

542 linhas; 33 definições aparentes; 0 marcadores asm.

Includes: `aobj.h`, `math.h`, `stdarg.h`, `string.h`, `cobj.h`, `debug.h`, `dobj.h`, `fog.h`, `id.h`, `jobj.h`, `list.h`, `lobj.h`, `mobj.h`, `pobj.h`, `robj.h`, `tobj.h`, `wobj.h`

Definições aparentes: `HSD_AObjInitAllocData`, `HSD_AObjGetAllocData`, `HSD_AObjGetFlags`, `HSD_AObjSetFlags`, `HSD_AObjClearFlags`, `HSD_AObjSetFObj`, `HSD_AObjInitEndCallBack`, `HSD_AObjInvokeCallBacks`, `HSD_AObjReqAnim`, `HSD_AObjStopAnim`, `getLoopedFrame`, `HSD_AObjInterpretAnim`, `HSD_AObjLoadDesc`, `HSD_AObjRemove`, `HSD_AObjAlloc`, `HSD_AObjFree`, `callbackForeachFunc`, `FogForeachAnim`, `TObjForeachAnim`, `RObjForeachAnim`, `WObjForeachAnim`, `CObjForeachAnim`, `LObjForeachAnim`, `PObjForeachAnim`, `MObjForeachAnim`, `DObjForeachAnim`, `JObjForeachAnim`, `HSD_ForeachAnim`, `HSD_AObjSetRate`, `HSD_AObjSetRewindFrame`, `HSD_AObjSetEndFrame`, `HSD_AObjSetCurrentFrame`, `_HSD_AObjForgetMemory`

## `src/sysdolphin/baselib/aobj.h`

105 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/fobj.h`, `sysdolphin/baselib/objalloc.h`, `sysdolphin/baselib/object.h`

Definições aparentes: `HSD_AObjGetCurrFrame`, `HSD_AObjGetEndFrame`

## `src/sysdolphin/baselib/archive.c`

119 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `archive.h`, `string.h`, `dolphin/os.h`

Definições aparentes: `Locate`, `HSD_ArchiveParse`, `HSD_ArchiveGetPublicAddress`, `HSD_ArchiveGetExtern`, `HSD_ArchiveLocateExtern`

## `src/sysdolphin/baselib/archive.h`

70 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`

## `src/sysdolphin/baselib/axdriver.c`

1363 linhas; 42 definições aparentes; 0 marcadores asm.

Includes: `axdriver.h`, `math.h`, `string.h`, `debug.h`, `synth.h`, `dolphin/ax.h`, `dolphin/axfx.h`, `dolphin/dvd.h`, `dolphin/os.h`

Definições aparentes: `AXDriverAlloc`, `AXDriverFree`, `AXDriverUnlink`, `AXDriverLink`, `AXDriverKeyOff`, `HSD_AudioSFXKeyOff`, `HSD_AudioSFXKeyOffAll`, `HSD_AudioSFXKeyOffTrack`, `sqrtf_store`, `AXDriverExec`, `parseWait`, `AXDriverInterp`, `AXDriverCallback`, `AXDriverKillCallback`, `AXDriverPauseCallback`, `AXDriverAssignVVoice`, `HSD_AudioSFXStartParam`, `HSD_AudioSFXSetPan`, `HSD_AudioSFXSetVolumeEx`, `HSD_AudioSFXSetPitchFid`, `HSD_AudioSFXSetMix`, `HSD_AudioSFXSetMixGroup`, `HSD_AudioSFXCheck`, `fn_8038DA5C`, `AXDriver_8038DA70`, `AXDriver_8038DCFC`, `AXDriverSetupAux`, `HSD_AudioGetAuxHeapSize`, `HSD_AudioSFXSetupAux`, `HSD_AudioSFXGetDefaultAuxParam`, `HSD_AudioInitMultiPStream`, `AXDriver_8038E5D4`, `AXDriver_8038E5DC`, `PStreamPauseCh`, `HSD_AudioPStreamPauseCh`, `PStreamResumeCh`, `HSD_AudioPStreamResumeCh`, `HSD_AudioPStreamStartChParam`, `AXDriverStop`, `AXDriverPause`, `AXDriverResume`, `AXDriverCheck`

## `src/sysdolphin/baselib/axdriver.h`

87 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/sysdolphin/baselib/bytecode.c`

534 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `bytecode.h`, `Runtime/platform.h`, `math.h`, `debug.h`, `list.h`, `random.h`, `util.h`, `dolphin/os.h`

Definições aparentes: `HSD_ByteCodeEval`

## `src/sysdolphin/baselib/bytecode.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/sysdolphin/baselib/card.c`

5554 linhas; 110 definições aparentes; 0 marcadores asm.

Includes: `card.h`, `placeholder.h`, `string.h`, `crypt.h`, `dolphin/card.h`, `dolphin/os.h`

Definições aparentes: `checkOpen`, `hsd_803A949C`, `fn_803AA790`, `retryCardOpen`, `retryCardFastOpen`, `retryCardReadAsync`, `retryCardWriteAsync`, `retryCardClose`, `retryCardCreateAsync`, `retryCardGetStatus`, `retryCardSetStatusAsync`, `setupCardIcons`, `unpackCardStat`, `rollbackCardCommands`, `initHeaderBlockCommand`, `queueHeaderBlock`, `queueHeaderBlocks`, `hsd_803AAA48`, `fn_803AC168`, `fn_803AC258`, `fn_803AC2A4`, `fn_803AC2D4`, `fn_803AC2E0`, `fn_803AC334`, `hsd_803AC340`, `hsd_803AC3E0`, `fn_803AC3F8`, `hsd_803AC558`, `fn_803AC634`, `fn_803AC6B8_first_block_count`, `fn_803AC6B8`, `fn_803AC6B8_blocks_before`, `fn_803AC7DC_block_count`, `fn_803AC7DC`, `fn_803ACB74`, `fn_803ACBE8`, `fn_803ACC0C`, `fn_803ACD58`, `fn_803ACF30`, `fn_803ACFC0_header`, `fn_803ACFC0_checksum_start`, `fn_803ACFC0`, `fn_803AD16C_total_blocks`, `fn_803AD16C_logical_index`, `fn_803AD16C_file_size`, `fn_803AD16C_nonnegative`, `fn_803AD16C_own`, `fn_803AD16C_queue_clear`, `fn_803AD16C_queue_read`, `fn_803AD16C_queue_write`, `fn_803AD16C_queue_write_last`, `fn_803AD16C`, `fn_803ADE4C`, `queueCardReadCommand`, `calculateDataBlockSize`, `calculateFileBlockCount`, `retryCardRead`, `cancelQueuedCardCommands`, `queueCardClearCommand`, `queueClearDataBlock`, `cardDataBlockOffset`, `queueReadDataBlock`, `readCardDataBlockFirst`, `readCardDataBlockFinal`, `fn_803ADF90`, `fn_803AE7F8_rewind`, `fn_803AE7F8_close`, `fn_803AE7F8`, `fn_803AF3F0_chunk_size`, `fn_803AF3F0_queue_verify_first`, `fn_803AF3F0_queue_verify_final`, `fn_803AF3F0_queue_write_first`, `fn_803AF3F0_queue_write_final`, `fn_803AF3F0_rewind`, `fn_803AF3F0_close`, `fn_803AF3F0_open`, `fn_803AF3F0_check_seq`, `fn_803AF3F0_calc_file_blocks`, `fn_803AF3F0`, `fn_803B0120_first_chunk`, `fn_803B0120_rewind`, `fn_803B0120_close`, `fn_803B0120_close_result`, `fn_803B0120_block_offset`, `fn_803B0120_queue_verify`, `fn_803B0120_queue_write`, `fn_803B0120`, `queueVerifyCardHeader`, `fn_803B0E9C_write_block`, `fn_803B0E9C_write_block_final`, `fn_803B0E9C_read_first`, `fn_803B0E9C`, `fn_803B1338_queue_write`, `fn_803B1338_data_at`, `fn_803B1338_data_size`, `fn_803B1338_queue_write_data`, `fn_803B1338`, `fn_803B1F78`, `fn_803B21E8`, `hsd_803B2374`, `hsd_803B24E4`, `hsd_803B2550`, `hsd_803B2674`, `fn_803B26CC`, `hsd_803B27F4`, `hsd_803B286C`, `hsd_803B2928`, `hsd_803B29D8`, `hsd_803B2A4C`, `hsd_SetCardIconInfo`

## `src/sysdolphin/baselib/card.h`

331 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/card.h`

## `src/sysdolphin/baselib/class.c`

513 linhas; 26 definições aparentes; 0 marcadores asm.

Includes: `class.h`, `string.h`, `debug.h`, `hash.h`, `memory.h`, `object.h`, `dolphin/os.h`

Definições aparentes: `ClassInfoInit`, `hsdInitClassInfo`, `OSReport_PrintSpaces`, `GetMemoryEntry`, `hsdAllocMemPiece`, `hsdFreeMemPiece`, `_hsdClassAlloc`, `_hsdClassInit`, `_hsdClassRelease`, `_hsdClassDestroy`, `_hsdClassAmnesia`, `_hsdClassInfoInit`, `hsdNew`, `HSD_GetClassInfo`, `HSD_PushClassInfo`, `hsdChangeClass_inline`, `hsdChangeClass`, `hsdIsDescendantOf`, `hsdObjIsDescendantOf`, `class_set_flags`, `ForgetClassLibraryReal`, `ForgetClassLibraryChild`, `hsdForgetClassLibrary`, `hsdSearchClassInfo`, `DumpClassStat`, `hsdDumpClassStat`

## `src/sysdolphin/baselib/class.h`

95 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

Definições aparentes: `hsdDelete`

## `src/sysdolphin/baselib/cobj.c`

1386 linhas; 86 definições aparentes; 0 marcadores asm.

Includes: `cobj.h`, `math.h`, `placeholder.h`, `aobj.h`, `class.h`, `debug.h`, `displayfunc.h`, `initialize.h`, `mtx.h`, `util.h`, `video.h`, `wobj.h`, `dolphin/gx.h`, `dolphin/gx/GXTransform.h`, `dolphin/mtx.h`, `dolphin/vi.h`

Definições aparentes: `HSD_CObjEraseScreen`, `HSD_CObjRemoveAnimByFlags`, `HSD_CObjRemoveAnim`, `HSD_CObjAddAnim`, `CObjUpdateFunc`, `HSD_CObjAnim`, `HSD_CObjReqAnim`, `makeProjectionMtx`, `setupOffscreenCamera`, `setupNormalCamera`, `setupTopHalfCamera`, `setupBottomHalfCamera`, `HSD_CObjSetupViewingMtx`, `HSD_CObjSetCurrent`, `HSD_CObjEndCurrent`, `HSD_CObjGetInterestWObj`, `HSD_CObjSetInterestWObj`, `HSD_CObjGetEyePositionWObj`, `HSD_CObjSetEyePositionWObj`, `HSD_CObjGetInterest`, `HSD_CObjSetInterest`, `HSD_CObjGetEyePosition`, `HSD_CObjSetEyePosition`, `HSD_CObjGetEyeVector`, `HSD_CObjGetEyeDistance`, `upvec2roll`, `vec_get_x`, `vec_get_abs_y`, `roll2upvec`, `cobj_get_up_x`, `HSD_CObjGetUpVector`, `HSD_CObjSetUpVector`, `HSD_CObjGetLeftVector`, `HSD_CObjSetMtxDirty`, `HSD_CObjMtxIsDirty`, `get_up_vector_for_viewing_mtx_inner`, `get_up_vector_for_viewing_mtx`, `HSD_CObjGetViewingMtx`, `HSD_CObjGetInvViewingMtxPtrDirect`, `HSD_CObjGetViewingMtxPtr`, `HSD_CObjGetInvViewingMtxPtr`, `HSD_CObjSetRoll`, `HSD_CObjGetFov`, `HSD_CObjSetFov`, `HSD_CObjGetAspect`, `HSD_CObjSetAspect`, `HSD_CObjGetTop`, `HSD_CObjSetTop`, `HSD_CObjGetBottom`, `HSD_CObjSetBottom`, `HSD_CObjGetLeft`, `HSD_CObjSetLeft`, `HSD_CObjGetRight`, `HSD_CObjSetRight`, `HSD_CObjGetNear`, `HSD_CObjSetNear`, `HSD_CObjGetFar`, `HSD_CObjSetFar`, `HSD_CObjGetScissor`, `HSD_CObjSetScissor`, `HSD_CObjSetScissorx4`, `HSD_CObjGetViewportf`, `HSD_CObjSetViewport`, `HSD_CObjSetViewportf`, `HSD_CObjSetViewportfx4`, `HSD_CObjGetProjectionType`, `HSD_CObjSetProjectionType`, `HSD_CObjSetPerspective`, `HSD_CObjSetFrustum`, `HSD_CObjSetOrtho`, `HSD_CObjGetPerspective`, `HSD_CObjGetOrtho`, `HSD_CObjGetFlags`, `HSD_CObjSetFlags`, `HSD_CObjClearFlags`, `HSD_CObjGetCurrent`, `HSD_CObjSetDefaultClass`, `HSD_CObjAlloc`, `CObjResetFlags`, `CObjLoad`, `HSD_CObjInit`, `HSD_CObjLoadDesc`, `CObjInit`, `CObjRelease`, `CObjAmnesia`, `CObjInfoInit`

## `src/sysdolphin/baselib/cobj.h`

229 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `dolphin/gx/GXEnum.h`, `dolphin/mtx.h`, `sysdolphin/baselib/object.h`

Definições aparentes: `HSD_CObjGetViewingMtxPtrDirect`

## `src/sysdolphin/baselib/controller.c`

590 linhas; 24 definições aparentes; 0 marcadores asm.

Includes: `controller.h`, `math.h`, `rumble.h`, `dolphin/os.h`, `dolphin/pad.h`

Definições aparentes: `HSD_PadGetRawQueueCount`, `HSD_PadGetResetSwitch`, `HSD_PadRawQueueShift`, `HSD_PadRawMerge`, `HSD_PadRenewRawStatus`, `HSD_PadFlushQueue`, `HSD_PadClampCheck1`, `HSD_PadClampCheck3`, `HSD_PadClamp`, `sq`, `vec2DSqDist`, `vec2Dlen`, `HSD_PadADConvertCheck1`, `HSD_PadADConvert`, `HSD_PadScale`, `HSD_PadCrossDir`, `HSD_PadRenewMasterStatus`, `HSD_PadCopyStatusFields`, `HSD_PadClearStatusFields`, `HSD_PadRenewCopyStatus`, `HSD_PadRenewGameStatus`, `HSD_PadRenewStatus`, `HSD_PadReset`, `HSD_PadInit`

## `src/sysdolphin/baselib/controller.h`

133 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/pad.h`, `sysdolphin/baselib/rumble.h`

Definições aparentes: `HSD_PadGetNmlStickY`, `HSD_PadGetNmlSubStickY`

## `src/sysdolphin/baselib/crypt.c`

206 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `crypt.h`, `string.h`

Definições aparentes: `HSD_Checksum`, `encryptByte`, `encryptAt`, `HSD_Encrypt`, `decryptByte`, `HSD_Decrypt`

## `src/sysdolphin/baselib/crypt.h`

15 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/sysdolphin/baselib/debug.c`

63 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `debug.h`, `stdio.h`, `dolphin/os.h`

Definições aparentes: `report_func`, `HSD_LogInit`, `__assert`, `HSD_Panic`, `HSD_SetReportCallback`, `HSD_SetPanicCallback`

## `src/sysdolphin/baselib/debug.h`

38 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/os.h`

## `src/sysdolphin/baselib/debugconsole_main.c`

2806 linhas; 66 definições aparentes; 0 marcadores asm.

Includes: `debugconsole_main.h`, `placeholder.h`, `string.h`, `hsd_3915.h`, `hsd_393C.h`, `hsd_397E.h`, `video.h`, `dolphin/os.h`, `dolphin/pad.h`, `dolphin/vi.h`, `MetroTRK/ppc_reg.h`

Definições aparentes: `gprmsg`, `hsd_80394314`, `hsd_80394434`, `hsd_80394544`, `hsd_80394668`, `hsd_80394950`, `unused`, `Exception_ReportStackTrace`, `Exception_ReportCodeline`, `fn_80394DF4`, `ps_push_node`, `ps_set_initial_node`, `hsd_80394E8C`, `hsd_80394F48_putc`, `hsd_80394F48_rule`, `hsd_80394F48`, `hsd_80395550`, `hsd_80395644`, `hsd_803957C0_inline`, `hsd_803956D8`, `hsd_803957C0_get_x50`, `hsd_803957C0`, `hsd_80395970`, `hsd_80395A78`, `ps_remove_node`, `ps_clear_nodes`, `hsd_80395D88_dump_gpr`, `hsd_80395D88_dump_misc`, `hsd_80395D88`, `hsd_80396130`, `hsd_80396188_draw_rows`, `hsd_80396188_get_x50`, `hsd_80396188`, `hsd_803962A8`, `hsd_803966A0`, `hsd_80396868`, `hsd_80396884_draw_char`, `hsd_80396884_get_x50`, `hsd_80396884`, `hsd_80396A20`, `hsd_80396C78`, `hsd_80396E40_get_x50`, `hsd_80396E40`, `fn_803970D8`, `fn_803970DC`, `fn_803970E0`, `fn_803970E4`, `fn_803970E8`, `fn_803970EC`, `fn_803970F0`, `fn_803970F4`, `fn_803970F8`, `fn_803970FC`, `fn_80397100`, `fn_80397104`, `fn_80397108`, `fn_8039710C`, `hsd_80397110`, `fn_80397374`, `hsd_80397520`, `hsd_803975D4`, `ps_node_child`, `fn_80397814`, `hsd_80397DA4`, `Exception_StoreDebugLevel`, `hsd_80397DFC`

## `src/sysdolphin/baselib/debugconsole_main.h`

51 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `stdbool.h`, `dolphin/os/OSContext.h`

## `src/sysdolphin/baselib/devcom.c`

524 linhas; 17 definições aparentes; 0 marcadores asm.

Includes: `devcom.h`, `debug.h`, `forward.h`, `synth.h`, `dolphin/ar.h`, `dolphin/dvd.h`

Definições aparentes: `HSD_DevComIsBusy`, `HSD_DevComUnlink`, `HSD_DevComStdCallback`, `HSD_DevComARAMCallback_inline`, `HSD_DevComARAMCallback`, `getRelayBufIdx`, `HSD_DevComARAMWakeUp`, `HSD_DevComDVDStdCallback`, `HSD_DevComDVDARAMEndCallback`, `HSD_DevComDVDMemCallback`, `HSD_DevComDVDCallback`, `HSD_DevComDVDWakeUp`, `HSD_DevComGetDestType`, `DevComLinkNext`, `HSD_DevComRequest`, `HSD_DevComCancelEx_inline`, `HSD_DevComCancelEx`

## `src/sysdolphin/baselib/devcom.h`

17 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/archive.h`

## `src/sysdolphin/baselib/displayfunc.c`

611 linhas; 22 definições aparentes; 0 marcadores asm.

Includes: `displayfunc.h`, `string.h`, `cobj.h`, `dobj.h`, `lobj.h`, `mobj.h`, `mtx.h`, `objalloc.h`, `pobj.h`, `state.h`, `tev.h`, `util.h`, `dolphin/gx.h`, `dolphin/mtx.h`

Definições aparentes: `HSD_ZListInitAllocData`, `HSD_ZListAlloc`, `HSD_ZListFree`, `HSD_StateInitDirect`, `mkVBillBoardMtx`, `mkHBillBoardMtx`, `mkBillBoardMtx`, `mkRBillBoardMtx`, `HSD_JObjMakePositionMtx`, `HSD_JObjFindSkeleton`, `_HSD_mkEnvelopeModelNodeMtx`, `HSD_JObjDispSub`, `HSD_JObjDispDObj`, `zlist_sort`, `_HSD_ZListSort`, `_HSD_ZListDisp`, `_HSD_ZListClear`, `HSD_JObjDisp`, `HSD_JObjSetSPtclCallback`, `HSD_SetEraseColor`, `HSD_EraseRect`, `_HSD_DispForgetMemory`

## `src/sysdolphin/baselib/displayfunc.h`

45 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `sysdolphin/baselib/jobj.h`

## `src/sysdolphin/baselib/dobj.c`

341 linhas; 26 definições aparentes; 0 marcadores asm.

Includes: `dobj.h`, `aobj.h`, `class.h`, `debug.h`, `mobj.h`, `pobj.h`, `dolphin/os.h`

Definições aparentes: `HSD_DObjSetCurrent`, `HSD_DObjGetFlags`, `HSD_DObjSetFlags`, `HSD_DObjClearFlags`, `HSD_DObjModifyFlags`, `HSD_DObjRemoveAnimByFlags`, `HSD_DObjRemoveAnimAllByFlags`, `HSD_DObjAddAnim`, `HSD_DObjAddAnimAll`, `HSD_DObjReqAnimByFlags`, `HSD_DObjReqAnimAllByFlags`, `HSD_DObjReqAnimAll`, `HSD_DObjAnim`, `HSD_DObjAnimAll`, `DObjLoad`, `HSD_DObjLoadDesc`, `HSD_DObjRemove`, `HSD_DObjRemoveAll`, `HSD_DObjSetDefaultClass`, `HSD_DObjAlloc`, `HSD_DObjResolveRefs`, `HSD_DObjResolveRefsAll`, `HSD_DObjDisp`, `DObjRelease`, `DObjAmnesia`, `DObjInfoInit`

## `src/sysdolphin/baselib/dobj.h`

73 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/mobj.h`

## `src/sysdolphin/baselib/fobj.c`

498 linhas; 30 definições aparentes; 0 marcadores asm.

Includes: `fobj.h`, `string.h`, `debug.h`, `spline.h`

Definições aparentes: `HSD_FObjGetAllocData`, `HSD_FObjInitAllocData`, `HSD_FObjRemove`, `HSD_FObjRemoveAll`, `HSD_FObjSetState`, `HSD_FObjGetState`, `HSD_FObjReqAnim`, `HSD_FObjReqAnimAll`, `FObj_FlushKeyData`, `HSD_FObjStopAnim`, `HSD_FObjStopAnimAll`, `parseFloat`, `parseOpCode`, `parsePackInfo`, `FObjLaunchKeyData`, `parseWait`, `FObjLoadWait`, `FObjAnimCON`, `FObjAnimLinear`, `FObjAnimSPL0`, `FObjAnimSPL`, `FObjAnimSLP`, `FObjAnimKey`, `FObjLoadData`, `FObjUpdateAnim`, `HSD_FObjInterpretAnim`, `HSD_FObjInterpretAnimAll`, `HSD_FObjLoadDesc`, `HSD_FObjAlloc`, `HSD_FObjFree`

## `src/sysdolphin/baselib/fobj.h`

96 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `dolphin/mtx.h`, `sysdolphin/baselib/objalloc.h`

## `src/sysdolphin/baselib/fog.c`

255 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `fog.h`, `aobj.h`, `class.h`, `cobj.h`, `debug.h`, `object.h`, `dolphin/gx/GXPixel.h`, `dolphin/mtx.h`

Definições aparentes: `HSD_FogSet`, `HSD_FogAlloc`, `HSD_FogLoadDesc`, `HSD_FogInit`, `HSD_FogAdjAlloc`, `HSD_FogAdjLoadDesc`, `HSD_FogAdjInit`, `HSD_Fog_8037DE7C`, `HSD_FogReqAnim`, `HSD_FogReqAnimByFlags`, `HSD_FogInterpretAnim`, `FogUpdateFunc`, `FogRelease`, `FogInfoInit`, `FogAdjInfoInit`

## `src/sysdolphin/baselib/fog.h`

66 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `sysdolphin/baselib/object.h`

## `src/sysdolphin/baselib/forward.h`

186 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/sysdolphin/baselib/generator.c`

1237 linhas; 17 definições aparentes; 0 marcadores asm.

Includes: `generator.h`, `math.h`, `string.h`, `cobj.h`, `mtx.h`, `particle.h`, `psappsrt.h`, `psstructs.h`, `random.h`, `wobj.h`

Definições aparentes: `hsd_8039D1E4`, `hsd_8039D1EC`, `hsd_8039D214`, `hsd_8039D354`, `hsd_8039D3AC`, `hsd_8039D4DC`, `hsd_8039D580`, `hsd_8039D5DC`, `hsd_8039D688`, `hsd_8039D71C`, `hsd_8039D9C8`, `hsd_8039DAD4_home`, `hsd_8039DAD4`, `hsd_8039EE24`, `hsd_8039EFAC`, `hsd_8039F05C`, `hsd_8039F6CC`

## `src/sysdolphin/baselib/generator.h`

40 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `placeholder.h`, `sysdolphin/baselib/objalloc.h`

## `src/sysdolphin/baselib/gobj.c`

187 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `gobj.h`, `fog.h`, `gobjplink.h`, `gobjproc.h`, `lobj.h`

Definições aparentes: `GObj_SetFlag1_inline`, `GObj_SetFlag2_inline`, `HSD_GObj_80390C5C`, `HSD_GObj_80390C84`, `HSD_GObj_80390CAC`, `HSD_GObj_80390CD4`, `HSD_GObj_RunProcs`, `HSD_GObj_80390EB8`, `render_gobj`, `HSD_GObj_80390ED0`, `HSD_GObj_80390FC0`

## `src/sysdolphin/baselib/gobj.h`

137 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/objalloc.h`

Definições aparentes: `HSD_GObjGetUserData`, `HSD_GObjGetHSDObj`, `HSD_GObjGetClassifier`, `HSD_GObjGetNext`

## `src/sysdolphin/baselib/gobjgxlink.c`

141 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `gobjgxlink.h`, `debug.h`, `gobj.h`

Definições aparentes: `GObj_GXReorder`, `GObj_GXInsertFromTail`, `GObj_GXInsertFromHead`, `GObj_GXInsert`, `GObj_SetupGXLink`, `GObj_SetupGXLinkMax`, `GObj_SetupGXLinkMaxSorted`, `HSD_GObjGXLink_8039084C`, `HSD_GObjGXLink_80390908`, `HSD_GObjGXLink_803909D8`

## `src/sysdolphin/baselib/gobjgxlink.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/gobj.h`

## `src/sysdolphin/baselib/gobjinit.c`

90 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `gobj.h`, `gobjproc.h`, `memory.h`, `objalloc.h`

Definições aparentes: `HSD_GObjSetInitDefaults`, `HSD_GObjInit`

## `src/sysdolphin/baselib/gobjobject.c`

44 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `gobjobject.h`, `debug.h`, `gobj.h`

Definições aparentes: `HSD_GObjObject_80390A3C`, `HSD_GObjObject_80390A70`, `HSD_GObjObject_80390ADC`, `HSD_GObjObject_80390B0C`

## `src/sysdolphin/baselib/gobjobject.h`

15 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`

## `src/sysdolphin/baselib/gobjplink.c`

198 linhas; 8 definições aparentes; 0 marcadores asm.

Includes: `gobjplink.h`, `debug.h`, `gobj.h`, `gobjgxlink.h`, `gobjobject.h`, `gobjproc.h`, `gobjuserdata.h`, `objalloc.h`

Definições aparentes: `GObj_PReorder`, `gobj_allocate`, `gobj_first_lower_prio`, `gobj_first_higher_prio`, `CreateGObj`, `GObj_Create`, `HSD_GObjFree`, `HSD_GObjPLink_ChangeGObjPri_Unk`

## `src/sysdolphin/baselib/gobjplink.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/gobj.h`

## `src/sysdolphin/baselib/gobjproc.c`

188 linhas; 7 definições aparentes; 0 marcadores asm.

Includes: `gobjproc.h`, `debug.h`, `gobj.h`, `objalloc.h`

Definições aparentes: `HSD_GObjProc_QueueProc`, `HSD_GObjProc_UnqueueProc`, `HSD_GObjProc_UnlinkProcFromGObj`, `assertProc`, `HSD_GObj_SetupProc`, `HSD_GObjProc_RemoveProc`, `HSD_GObjProc_RemoveAllProcs`

## `src/sysdolphin/baselib/gobjproc.h`

28 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/sysdolphin/baselib/gobjuserdata.c`

25 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `gobjuserdata.h`, `debug.h`, `gobj.h`

Definições aparentes: `GObj_InitUserData`, `GObj_RemoveUserData`

## `src/sysdolphin/baselib/gobjuserdata.h`

14 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/sysdolphin/baselib/hash.c`

50 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `hash.h`, `debug.h`

Definições aparentes: `HashSearchEntry`, `HSD_HashSearch`

## `src/sysdolphin/baselib/hash.h`

37 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/class.h`

## `src/sysdolphin/baselib/hsd_3910.c`

85 linhas; 8 definições aparentes; 0 marcadores asm.

Includes: `class.h`, `cobj.h`, `fog.h`, `gobj.h`, `jobj.h`, `lobj.h`, `object.h`

Definições aparentes: `HSD_GObj_LObjCallback`, `HSD_GObj_JObjCallback`, `HSD_GObj_FogCallback`, `HSD_GObj_803910D8`, `HSD_GObj_80391120`, `HSD_GObj_803911C0`, `HSD_GObj_80391260`, `HSD_GObj_803912A8`

## `src/sysdolphin/baselib/hsd_3915.c`

551 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `hsd_3915.h`, `math.h`, `placeholder.h`, `cobj.h`, `pobj.h`, `state.h`, `dolphin/gx.h`, `dolphin/gx/GXGeometry.h`, `sysdolphin/baselib/debug_font.inc`

Definições aparentes: `DrawRectangle`, `DrawASCII`, `hsd_80391A04`, `hexval`, `hsd_80391AC8`, `hsd_80391E18`, `hsd_80391F28_len`, `hsd_80391F28`, `hsd_80392194`, `hsd_803921B8`, `hsd_803922FC`

## `src/sysdolphin/baselib/hsd_3915.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `dolphin/gx/GXStruct.h`

## `src/sysdolphin/baselib/hsd_3924.c`

248 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `hsd_3924.h`, `placeholder.h`, `string.h`, `hsd_3915.h`, `list.h`, `memory.h`, `dolphin/gx.h`

Definições aparentes: `hsd_80392474`, `fn_80392480`, `hsd_80392528`, `count_bar_units`, `count_text_chars`, `hsd_8039254C`

## `src/sysdolphin/baselib/hsd_3924.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/list.h`

## `src/sysdolphin/baselib/hsd_392A.c`

196 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `hsd_392A.h`, `stdio.h`, `perf.h`, `psstructs.h`

Definições aparentes: `fn_80392934`, `fn_80392A08`, `get_perf_disp_item`, `fn_80392A3C`

## `src/sysdolphin/baselib/hsd_392A.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/sysdolphin/baselib/hsd_392C.c`

306 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `hsd_392C.h`, `placeholder.h`, `hsd_3933.h`, `dolphin/mcc.h`, `dolphin/os.h`

Definições aparentes: `fn_80392CCC`, `fn_80392CD8`, `fn_80392E2C`, `usb_exit_init`, `hsd_80392E80`, `hsd_803931A4`

## `src/sysdolphin/baselib/hsd_392C.h`

12 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/sysdolphin/baselib/hsd_3933.c`

362 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `hsd_3933.h`, `string.h`, `hsd_392C.h`, `random.h`, `dolphin/mcc.h`, `dolphin/os.h`

Definições aparentes: `fn_803932D0`, `hsd_80393328`, `hsd_80393440`, `hsd_80393840`, `hsd_80393844`, `hsd_80393A04`, `hsd_80393A54`, `kbps_scale`, `hsd_80393A5C`

## `src/sysdolphin/baselib/hsd_3933.h`

45 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/sysdolphin/baselib/hsd_393C.c`

334 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `hsd_393C.h`, `placeholder.h`, `string.h`, `debug.h`, `video.h`

Definições aparentes: `fn_80393C14`, `hsd_80393D2C`, `hsd_80393DA0`, `hsd_80393E34`, `hsd_80393E68`, `hsd_80393EF4`, `hsd_80394068`, `hsd_80394128`, `hsd_803941E8`

## `src/sysdolphin/baselib/hsd_393C.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/sysdolphin/baselib/hsd_397E.c`

228 linhas; 1 definições aparentes; 69 marcadores asm.

Includes: `hsd_397E.h`, `dolphin/os.h`, `MetroTRK/ppc_reg.h`

Definições aparentes: `baselib_mfspr`

## `src/sysdolphin/baselib/hsd_397E.h`

8 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/sysdolphin/baselib/hsd_3982.c`

55 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `hsd_3982.h`, `cobj.h`, `gobj.h`, `gobjgxlink.h`, `gobjobject.h`, `hsd_3924.h`, `hsd_392A.h`, `wobj.h`

Definições aparentes: `fn_803982E4`, `hsd_80398310`

## `src/sysdolphin/baselib/hsd_3982.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/sysdolphin/baselib/hsd_3A64.c`

493 linhas; 16 definições aparentes; 0 marcadores asm.

Includes: `stdarg.h`, `stdio.h`, `gobjobject.h`, `sislib.h`, `sislib_font.h`, `wobj.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `dolphin/types.h`

Definições aparentes: `sisBufferLength`, `HSD_SisLib_803A6478`, `HSD_SisLib_803A6530`, `HSD_SisLib_803A660C`, `HSD_SisLib_803A6754`, `sisBeginLine`, `sisEndKerning`, `HSD_SisLib_803A67EC`, `HSD_SisLib_803A6B98`, `fn_803A6FEC`, `HSD_SisLib_803A70A0`, `HSD_SisLib_803A746C`, `HSD_SisLib_803A74F0`, `HSD_SisLib_803A7548`, `HSD_SisLib_803A75E0`, `HSD_SisLib_803A7664`

## `src/sysdolphin/baselib/hsd_3A76.c`

1225 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `string.h`, `cobj.h`, `gobj.h`, `gobjobject.h`, `sislib.h`, `sislib_font.h`, `state.h`, `tev.h`, `wobj.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `dolphin/types.h`, `melee/lb/lbarchive.h`

Definições aparentes: `sisGetSavedCursor`, `sisGetJumpTarget`, `HSD_SisLib_803A7684`, `HSD_SisLib_803A7F0C`, `HSD_SisLib_803A8134`, `sisFitLineToBox`, `HSD_SisLib_803A84BC`, `HSD_SisLib_803A945C`, `HSD_SisLib_803A947C`

## `src/sysdolphin/baselib/hsd_3B33.c`

35 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `hsd_3B33.h`, `setjmp.h`, `string.h`, `hsd_3B34.h`

Definições aparentes: `hsd_803B3344`, `hsd_803B3398`

## `src/sysdolphin/baselib/hsd_3B33.h`

9 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/sysdolphin/baselib/hsd_3B34.c`

1123 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `hsd_3B34.h`, `placeholder.h`, `setjmp.h`, `stdlib.h`, `string.h`, `hsd_3B33.h`

Definições aparentes: `jpegLumaAddress`, `hsd_803B3408`, `fn_803B376C`, `bitLength`, `writeByte`, `writeBits`, `hsd_803B3CD8`, `hsd_803B46D4`, `hsd_803B4A2C`, `hsd_803B4D64`, `hsd_803B51C8_inline`, `hsd_803B51C8`, `hsd_803B5C2C`

## `src/sysdolphin/baselib/hsd_3B34.h`

39 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `setjmp.h`

## `src/sysdolphin/baselib/hsd_3B5C.c`

893 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `placeholder.h`, `setjmp.h`, `hsd_3B34.h`

Definições aparentes: `hsd_803B5C4C`, `hsd_803B5D70`, `hsd_803B5EA0`, `fn_803B61B4`, `jpeg_clamp`, `jpeg_store_rgb565`, `fn_803B6820`, `hsd_803B6BE4_inline`, `hsd_803B6BE4`

## `src/sysdolphin/baselib/id.c`

127 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `id.h`, `string.h`, `debug.h`

Definições aparentes: `HSD_IDGetAllocData`, `HSD_IDInitAllocData`, `HSD_IDSetup`, `hash`, `IDEntryAlloc`, `HSD_IDInsertToTable`, `IDEntryFree`, `HSD_IDRemoveByIDFromTable`, `HSD_IDGetDataFromTable`, `_HSD_IDForgetMemory`

## `src/sysdolphin/baselib/id.h`

33 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/objalloc.h`

Definições aparentes: `HSD_IDGetData`

## `src/sysdolphin/baselib/initialize.c`

369 linhas; 17 definições aparentes; 0 marcadores asm.

Includes: `initialize.h`, `stdarg.h`, `aobj.h`, `class.h`, `debug.h`, `displayfunc.h`, `fobj.h`, `id.h`, `list.h`, `lobj.h`, `mtx.h`, `objalloc.h`, `random.h`, `robj.h`, `shadow.h`, `state.h`, `synth.h`, `tev.h`, `video.h`, `dolphin/gx.h`, `dolphin/os.h`, `dolphin/vi.h`

Definições aparentes: `HSD_InitComponent`, `HSD_GXSetFifoObj`, `HSD_DVDInit`, `HSD_AllocateXFB`, `HSD_AllocateFifo`, `HSD_GXInit`, `HSD_OSInit`, `HSD_GetHeap`, `HSD_SetHeap`, `HSD_GetNextArena`, `HSD_CreateMainHeap`, `HSD_GetCurrentRenderPass`, `HSD_StartRender`, `HSD_Init_803755A8`, `HSD_ObjInit`, `HSD_ObjDumpStat`, `HSD_SetInitParameter`

## `src/sysdolphin/baselib/initialize.h`

45 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/gx.h`, `dolphin/os/OSAlloc.h`, `sysdolphin/baselib/video.h`

## `src/sysdolphin/baselib/jobj.c`

1578 linhas; 65 definições aparentes; 0 marcadores asm.

Includes: `jobj.h`, `math.h`, `string.h`, `aobj.h`, `class.h`, `cobj.h`, `displayfunc.h`, `dobj.h`, `fobj.h`, `id.h`, `mobj.h`, `mtx.h`, `pobj.h`, `robj.h`, `spline.h`, `dolphin/mtx.h`

Definições aparentes: `HSD_JObjCheckDepend`, `JObjResetRST`, `HSD_JObjResetRST`, `HSD_JObjWalkTree0`, `HSD_JObjWalkTree`, `has_scl`, `HSD_JObjMakeMatrix`, `HSD_JObjRemoveAnimByFlags`, `HSD_JObjRemoveAnimAllByFlags`, `HSD_JObjRemoveAnim`, `HSD_JObjRemoveAnimAll`, `HSD_JObjReqAnimByFlags`, `HSD_JObjReqAnimAllByFlags`, `HSD_JObjReqAnimAll`, `HSD_JObjReqAnim`, `JObjSortAnim`, `HSD_JObjAddAnim`, `HSD_JObjAddAnimAll`, `JObjUpdateFunc`, `HSD_JObjAnim`, `JObjAnimAll`, `HSD_JObjAnimAll`, `HSD_JObjDispAll`, `HSD_JObjSetDefaultClass`, `JObjLoadJointSub`, `JObjLoad`, `HSD_JObjLoadJoint`, `HSD_JObjResolveRefs`, `HSD_JObjResolveRefsAll`, `HSD_JObjUnref`, `HSD_JObjUnrefThis`, `HSD_JObjRemove`, `HSD_JObjRemoveAll`, `RecalcParentTrspBits`, `UpdateParentTrspBits`, `HSD_JObjAddChild`, `HSD_JObjReparent`, `HSD_JObjAddNext`, `HSD_JObjGetPrev`, `HSD_JObjGetDObj`, `HSD_JObjAddDObj`, `robj_set_next`, `HSD_JObjPrependRObj`, `HSD_JObjDeleteRObj`, `HSD_JObjGetFlags`, `HSD_JObjSetFlags`, `HSD_JObjSetFlagsAll`, `HSD_JObjClearFlags`, `HSD_JObjClearFlagsAll`, `HSD_JObjAlloc`, `HSD_JObjSetCurrent`, `HSD_JObjGetCurrent`, `jobj_get_joint2`, `jobj_get_effector`, `jobj_get_effector_checked`, `resolveIKJoint1`, `resolveIKJoint2`, `HSD_JObjSetupMatrixSub`, `HSD_JObjSetMtxDirtySub`, `HSD_JObjSetDPtclCallback`, `JObjInit`, `JObjReleaseChild`, `JObjRelease`, `JObjAmnesia`, `JObjInfoInit`

## `src/sysdolphin/baselib/jobj.h`

758 linhas; 61 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `dolphin/mtx.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/list.h`, `sysdolphin/baselib/object.h`, `sysdolphin/baselib/pobj.h`, `sysdolphin/baselib/spline.h`

Definições aparentes: `HSD_JObjGetChild`, `HSD_JObjGetNext`, `HSD_JObjGetParent`, `HSD_JObjGetRObj`, `HSD_JObjMtxIsDirty`, `HSD_JObjSetMtxDirtyOutOfLineLeaf`, `HSD_JObjSetMtxDirtyOutOfLine`, `HSD_JObjSetMtxDirtyInline`, `HSD_JObjSetRotation`, `HSD_JObjSetRotationWithMtxDirty`, `HSD_JObjSetRotationX`, `HSD_JObjSetRotationXWithMtxDirty`, `HSD_JObjSetRotationY`, `HSD_JObjSetRotationYWithMtxDirty`, `HSD_JObjSetRotationZ`, `HSD_JObjSetRotationZWithMtxDirty`, `HSD_JObjGetRotation`, `HSD_JObjGetRotationX`, `HSD_JObjGetRotationY`, `HSD_JObjGetRotationZ`, `HSD_JObjSetScale`, `HSD_JObjSetScaleWithMtxDirty`, `HSD_JObjSetScaleX`, `HSD_JObjSetScaleXWithMtxDirty`, `HSD_JObjSetScaleY`, `HSD_JObjSetScaleYWithMtxDirty`, `HSD_JObjSetScaleZ`, `HSD_JObjSetScaleZWithMtxDirty`, `HSD_JObjGetScale`, `HSD_JObjGetScaleX`, `HSD_JObjGetScaleY`, `HSD_JObjGetScaleZ`, `HSD_JObjSetTranslate`, `HSD_JObjSetTranslateWithMtxDirty`, `HSD_JObjSetTranslateWithMtxDirtyOutOfLine`, `HSD_JObjSetTranslateX`, `HSD_JObjSetTranslateXWithMtxDirty`, `HSD_JObjSetTranslateY`, `HSD_JObjSetTranslateYWithMtxDirty`, `HSD_JObjSetTranslateZ`, `HSD_JObjSetTranslateZWithMtxDirty`, `HSD_JObjGetTranslation`, `HSD_JObjGetTranslation2`, `HSD_JObjGetTranslationX`, `HSD_JObjGetTranslationY`, `HSD_JObjGetTranslationZ`, `HSD_JObjAddRotationX`, `HSD_JObjAddRotationXWithMtxDirty`, `HSD_JObjAddRotationY`, `HSD_JObjAddRotationZ`, `HSD_JObjAddScaleX`, `HSD_JObjAddScaleY`, `HSD_JObjAddScaleZ`, `HSD_JObjAddTranslationX`, `HSD_JObjAddTranslationY`, `HSD_JObjAddTranslationYWithMtxDirty`, `HSD_JObjAddTranslationZ`, `HSD_JObjGetMtxPtr`, `HSD_JObjCopyMtx`, `HSD_JObjRef`, `HSD_JObjRefThis`

## `src/sysdolphin/baselib/leak.c`

169 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `leak.h`, `dolphin/os.h`

Definições aparentes: `order_data`, `HSD_LeakGetCapacityPtr`, `HSD_LeakReportSpaces`, `HSD_Leak_80387DF8`

## `src/sysdolphin/baselib/leak.h`

6 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/sysdolphin/baselib/list.c`

91 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `list.h`, `Runtime/platform.h`, `string.h`, `debug.h`

Definições aparentes: `HSD_ListInitAllocData`, `HSD_SListGetAllocData`, `HSD_DListGetAllocData`, `HSD_SListAlloc`, `HSD_SListAllocAndAppend`, `HSD_SListAllocAndPrepend`, `HSD_SListAppendList`, `HSD_SListPrependList`, `HSD_SListRemove`

## `src/sysdolphin/baselib/list.h`

27 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/objalloc.h`

## `src/sysdolphin/baselib/lobj.c`

1082 linhas; 64 definições aparentes; 0 marcadores asm.

Includes: `lobj.h`, `placeholder.h`, `aobj.h`, `class.h`, `cobj.h`, `forward.h`, `list.h`, `object.h`, `wobj.h`, `dolphin/gx/GXEnum.h`, `dolphin/mtx.h`, `dolphin/os.h`

Definições aparentes: `HSD_LObjGetFlags`, `HSD_LObjSetFlags`, `HSD_LObjClearFlags`, `HSD_LObjGetLightMaskDiffuse`, `HSD_LObjGetLightMaskAttnFunc`, `HSD_LObjGetLightMaskAlpha`, `HSD_LObjGetLightMaskSpecular`, `HSD_LObjGetType`, `HSD_LObjSetActive`, `HSD_LObjGetNbActive`, `HSD_LObjGetActiveByID`, `HSD_LObjGetActiveByIndex`, `HSD_LObjClearActive`, `LObjUpdateFunc`, `HSD_LObjAnim`, `HSD_LObjAnimAll`, `HSD_LObjReqAnim`, `HSD_LObjReqAnimAll`, `HSD_LObjGetLightVector`, `HSD_LObjSetup`, `HSD_LObjSetupSpecularInit`, `setup_diffuse_lightobj`, `setup_spec_lightobj`, `setup_infinite_lightobj`, `setup_point_lightobj`, `setup_spot_lightobj`, `HSD_LObjSetupInit`, `HSD_LObjAddCurrent`, `HSD_LObjUnrefThis`, `HSD_LObjDeleteCurrent`, `LObjRemoveAll`, `HSD_LObjDeleteCurrentAll`, `HSD_LObjSetCurrentAll`, `LObjReplaceAll`, `HSD_LObj_803668EC`, `HSD_LObjGetCurrentByType`, `HSD_LightID2Index`, `HSD_Index2LightID`, `HSD_LObjRemoveAll`, `HSD_LObjSetColor`, `HSD_LObjGetColor`, `HSD_LObjSetSpot`, `HSD_LObjSetDistAttn`, `HSD_LObjSetAttnA`, `HSD_LObjSetAttnK`, `HSD_LObjSetAttn`, `HSD_LObjSetPosition`, `HSD_LObjGetPosition`, `HSD_LObjSetInterest`, `HSD_LObjGetInterest`, `HSD_LObjSetDefaultClass`, `HSD_LObjGetDefaultClass`, `HSD_LObjAlloc`, `HSD_LObjGetPositionWObj`, `HSD_LObjGetInterestWObj`, `HSD_LObjSetPositionWObj`, `HSD_LObjSetInterestWObj`, `LObjLoad`, `HSD_LObjLoadDesc`, `HSD_LObjAddAnim`, `HSD_LObjAddAnimAll`, `LObjRelease`, `LObjAmnesia`, `LObjInfoInit`

## `src/sysdolphin/baselib/lobj.h`

206 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `dolphin/gx.h`, `dolphin/gx/GXEnum.h`, `dolphin/mtx.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/object.h`

Definições aparentes: `HSD_LObjGetPriority`, `HSD_LObjGetNext`, `HSD_LObjSetNext`

## `src/sysdolphin/baselib/memory.c`

26 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `memory.h`, `Runtime/platform.h`, `debug.h`, `initialize.h`, `dolphin/os/OSAlloc.h`

Definições aparentes: `HSD_Free`, `HSD_MemAlloc`

## `src/sysdolphin/baselib/memory.h`

9 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/sysdolphin/baselib/mobj.c`

591 linhas; 28 definições aparentes; 0 marcadores asm.

Includes: `mobj.h`, `string.h`, `aobj.h`, `class.h`, `debug.h`, `state.h`, `tev.h`, `texp.h`, `dolphin/gx/GXEnum.h`

Definições aparentes: `HSD_MObjSetCurrent`, `HSD_MObjSetFlags`, `HSD_MObjClearFlags`, `HSD_MObjRemoveAnimByFlags`, `HSD_MObjAddAnim`, `HSD_MObjReqAnimByFlags`, `HSD_MObjReqAnim`, `MObjUpdateFunc`, `HSD_MObjAnim`, `MObjLoad`, `HSD_MObjLoadDesc`, `MObjMakeTExp`, `HSD_MObjCompileTev`, `MObjSetupTev`, `HSD_MObjSetup`, `HSD_MObjUnset`, `HSD_MObjSetToonTextureImage`, `HSD_MObjSetDiffuseColor`, `HSD_MObjSetAlpha`, `HSD_MObjGetTObj`, `HSD_MObjRemove`, `HSD_MObjAlloc`, `HSD_MaterialAlloc`, `HSD_MObjAddShadowTexture`, `HSD_MObjDeleteShadowTexture`, `MObjRelease`, `MObjAmnesia`, `MObjInfoInit`

## `src/sysdolphin/baselib/mobj.h`

186 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/texp.h`, `sysdolphin/baselib/tobj.h`

## `src/sysdolphin/baselib/mtx.c`

508 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `mtx.h`, `math.h`, `debug.h`

Definições aparentes: `HSD_CalcDeterminantMatrix3x4`, `HSD_MtxInverse`, `HSD_MtxInverseConcat`, `HSD_MtxInverseTranspose`, `calcVal`, `HSD_MtxGetRotation`, `HSD_MtxGetTranslate`, `HSD_MtxGetScale`, `HSD_MkRotationMtx`, `HSD_MtxQuat`, `HSD_MtxSRT`, `HSD_MtxSRTQuat`, `HSD_MtxScaledAdd`, `HSD_VecAlloc`, `HSD_VecFree`, `HSD_MtxAlloc`, `HSD_MtxFree`, `HSD_VecGetAllocData`, `HSD_VecInitAllocData`, `HSD_MtxGetAllocData`, `HSD_MtxInitAllocData`

## `src/sysdolphin/baselib/mtx.h`

64 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `math.h`, `dolphin/mtx.h`, `sysdolphin/baselib/objalloc.h`

Definições aparentes: `fabsf_bitwise`, `HSD_MtxColVec`, `HSD_MtxSetColVec`, `HSD_MtxColMag`

## `src/sysdolphin/baselib/objalloc.c`

161 linhas; 7 definições aparentes; 0 marcadores asm.

Includes: `objalloc.h`, `string.h`, `initialize.h`, `memory.h`, `dolphin/os/OSAlloc.h`

Definições aparentes: `HSD_ObjSetHeap`, `HSD_ObjAllocAddFree`, `HSD_ObjAlloc`, `HSD_ObjFree`, `removeAll`, `HSD_ObjAllocInit`, `_HSD_ObjAllocForgetMemory`

## `src/sysdolphin/baselib/objalloc.h`

80 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/debug.h`

Definições aparentes: `HSD_ObjAllocGetUsing`, `HSD_ObjAllocGetFreed`, `HSD_ObjAllocGetPeak`, `HSD_ObjAllocSetNumLimit`, `HSD_ObjAllocEnableNumLimit`, `HSD_ObjAllocDisableNumLimit`

## `src/sysdolphin/baselib/object.c`

9 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `object.h`

Definições aparentes: `ObjInfoInit`

## `src/sysdolphin/baselib/object.h`

121 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/debug.h`

Definições aparentes: `ref_DEC`, `ref_INC`, `ref_CNT`, `iref_CNT`, `iref_DEC`, `iref_INC`

## `src/sysdolphin/baselib/particle.c`

3085 linhas; 17 definições aparentes; 0 marcadores asm.

Includes: `particle.h`, `generator.h`, `Runtime/platform.h`, `math.h`, `string.h`, `gobjobject.h`, `mtx.h`, `psappsrt.h`, `psstructs.h`, `random.h`, `dolphin/gx.h`, `dolphin/os.h`

Definições aparentes: `hsd_803983A4`, `psInitDataBankLoad`, `psInitDataBankLocate`, `psInitDataBank`, `hsd_80398A08`, `psGenerateParticle0`, `hsd_80398F0C`, `hsd_80398F8C`, `hsd_803991D8`, `psEnableTexture`, `psReadFloat`, `psSpawnChild`, `hsd_8039930C`, `hsd_8039CEAC`, `hsd_8039CF4C`, `hsd_8039D048`, `hsd_8039D0A0`

## `src/sysdolphin/baselib/particle.h`

48 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/psstructs.h`

## `src/sysdolphin/baselib/perf.c`

46 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `perf.h`, `string.h`, `debug.h`, `dolphin/os.h`

Definições aparentes: `HSD_PerfInitStat`, `HSD_PerfSetStartTime`, `HSD_PerfSetCPUTime`, `HSD_PerfSetDrawTime`, `HSD_PerfSetTotalTime`, `HSD_PerfCountEnvelopeBlending`

## `src/sysdolphin/baselib/perf.h`

29 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

Definições aparentes: `HSD_PerfCountMtxLoad`

## `src/sysdolphin/baselib/pobj.c`

1305 linhas; 57 definições aparentes; 0 marcadores asm.

Includes: `pobj.h`, `math.h`, `string.h`, `aobj.h`, `class.h`, `debug.h`, `displayfunc.h`, `forward.h`, `id.h`, `jobj.h`, `memory.h`, `mtx.h`, `perf.h`, `state.h`, `tobj.h`, `util.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `dolphin/os.h`

Definições aparentes: `HSD_PObjGetFlags`, `HSD_PObjRemoveAnimByFlags`, `HSD_PObjRemoveAnimAllByFlags`, `HSD_PObjAddAnim`, `HSD_PObjAddAnimAll`, `HSD_PObjReqAnimByFlags`, `HSD_PObjReqAnimAllByFlags`, `ShapeSetSetAnimResult`, `PObjUpdateFunc`, `HSD_PObjAnim`, `HSD_PObjAnimAll`, `HSD_EnvelopeAlloc`, `HSD_EnvelopeFree`, `HSD_EnvelopeListFree`, `loadEnvelopeDesc`, `HSD_ShapeSetFree`, `HSD_ShapeSetRemove`, `loadShapeSetDesc`, `PObjLoad`, `HSD_PObjLoadDesc`, `HSD_PObjRemove`, `HSD_PObjRemoveAll`, `HSD_PObjGetDefaultClass`, `HSD_PObjSetDefaultClass`, `HSD_PObjAlloc`, `HSD_PObjFree`, `resolveEnvelope`, `HSD_PObjResolveRefs`, `HSD_PObjResolveRefsAll`, `HSD_ClearVtxDesc`, `setupArrayDesc`, `setupVtxDesc`, `setupShapeAnimArrayDesc`, `setupShapeAnimVtxDesc`, `decode_u8_xyz`, `decode_s8_xyz`, `decode_u16_xyz`, `decode_s16_xyz`, `get_shape_vertex_xyz`, `get_shape_normal_xyz`, `get_shape_nbt_xyz`, `interpretShapeAnimDisplayList`, `drawShapeAnim`, `HSD_PObjClearMtxMark`, `HSD_PObjSetMtxMark`, `HSD_PObjGetMtxMark`, `GetSetupFlags`, `SetupRigidModelMtx`, `SetupSharedVtxModelMtx`, `SetupEnvelopeModelMtx`, `PObjSetupMtx`, `PObjDispSimplePrimitive`, `PObjDispShapeAnim`, `HSD_PObjDisp`, `PObjRelease`, `PObjAmnesia`, `PObjInfoInit`

## `src/sysdolphin/baselib/pobj.h`

157 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `dolphin/gx/GXEnum.h`, `dolphin/mtx.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/list.h`

## `src/sysdolphin/baselib/psappsrt.c`

132 linhas; 8 definições aparentes; 0 marcadores asm.

Includes: `psappsrt.h`, `string.h`, `objalloc.h`, `particle.h`, `psstructs.h`

Definições aparentes: `psInitAppSRT`, `psAddGeneratorAppSRT`, `psAddParticleAppSRT_begin`, `psAddGeneratorAppSRT_begin`, `psAttachParticleAppSRT`, `psAttachGeneratorAppSRT`, `psRemoveParticleAppSRT`, `psRemoveGeneratorSRT`

## `src/sysdolphin/baselib/psappsrt.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/objalloc.h`

## `src/sysdolphin/baselib/psdisp.c`

2206 linhas; 29 definições aparentes; 0 marcadores asm.

Includes: `psdisp.h`, `string.h`, `cobj.h`, `fog.h`, `forward.h`, `lobj.h`, `mtx.h`, `particle.h`, `psdisptev.h`, `psstructs.h`, `state.h`, `util.h`, `dolphin/gx.h`

Definições aparentes: `setVtxDesc`, `calcTornadoLastPos`, `getColorPrimEnv`, `getColorMatAmb`, `getClrTrail`, `psSetColor`, `psSetupVtxFormat`, `setupChanCtrl`, `setupChanReg`, `setupTevReg`, `particleSort`, `psDispSubPoint`, `psDispSubPointTrail`, `setBlendMode`, `psSetCurrentMtx`, `psDispSubMakePolygon`, `psMaskAbsF32`, `psMaskAbsLtF32`, `psMaskAbsGtF32`, `psAbsLtF32`, `psAbsGtF32`, `psDispSubAbsLtF32`, `psDispSubAbsGtF32`, `psDispSub`, `psScaleAppSRTAxes`, `psDispSubAPPSRTPoint`, `psDispSubAppSRT`, `psUpdateBillboardAxes`, `psDispParticles`

## `src/sysdolphin/baselib/psdisp.h`

12 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/sysdolphin/baselib/psdisptev.c`

204 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `psdisptev.h`, `psstructs.h`, `dolphin/gx.h`

Definições aparentes: `psSetupTevCommon`, `psSetupTevInvalidState`, `psSetupTev`

## `src/sysdolphin/baselib/psdisptev.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/sysdolphin/baselib/psstructs.h`

360 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx.h`, `dolphin/gx/GXEnum.h`, `dolphin/mtx.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/jobj.h`

## `src/sysdolphin/baselib/quatlib.c`

199 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `quatlib.h`, `math.h`, `placeholder.h`

Definições aparentes: `MatToQuat`, `HSD_QuatLib_8037EB28`, `HSD_QuatLib_8037EC4C`, `HSD_QuatLib_8037ECE0`, `EulerToQuat`, `HSD_QuatLib_8037EF28`

## `src/sysdolphin/baselib/quatlib.h`

15 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/mtx.h`

## `src/sysdolphin/baselib/random.c`

28 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `random.h`

Definições aparentes: `HSD_Rand`, `HSD_Randf`, `HSD_Randi`, `_HSD_RandForgetMemory`

## `src/sysdolphin/baselib/random.h`

21 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

Definições aparentes: `randi`

## `src/sysdolphin/baselib/robj.c`

941 linhas; 44 definições aparentes; 0 marcadores asm.

Includes: `robj.h`, `math.h`, `string.h`, `aobj.h`, `bytecode.h`, `class.h`, `debug.h`, `fobj.h`, `id.h`, `jobj.h`, `list.h`, `memory.h`, `mtx.h`, `object.h`, `util.h`, `dolphin/mtx.h`, `dolphin/os.h`

Definições aparentes: `HSD_RObjInitAllocData`, `HSD_RObjGetAllocData`, `HSD_RvalueObjGetAllocData`, `HSD_RObjSetFlags`, `HSD_RObjGetByType`, `RObjUpdateFunc`, `HSD_RObjAnim`, `HSD_RObjAnimAll`, `HSD_RObjRemoveAnimByFlags`, `HSD_RObjRemoveAnimAllByFlags`, `HSD_RObjRemoveAnimAll`, `HSD_RObjReqAnimByFlags`, `HSD_RObjReqAnimAllByFlags`, `HSD_RObjReqAnimAll`, `HSD_RObjAddAnim`, `HSD_RObjAddAnimAll`, `HSD_RObjGetConstraintType`, `HSD_RObjGetGlobalPosition`, `set_dirup_matrix`, `resolveCnsDirUp`, `jobj_parent`, `inlined_HSD_RObjGetByType`, `resolveCnsOrientation`, `resolveLimits`, `HSD_RObjUpdateAll`, `HSD_RObjResolveRefs`, `HSD_RObjResolveRefsAll`, `HSD_RObjLoadDesc`, `HSD_RObjRemove`, `HSD_RObjRemoveAll`, `HSD_RObjAlloc`, `HSD_RObjFree`, `expEvaluate`, `dummy_func`, `HSD_RvalueAlloc`, `HSD_RvalueRemove`, `HSD_RvalueRemoveAll`, `loadRvalue`, `expLoadDesc`, `bcexpLoadDesc`, `HSD_RvalueResolveRefs`, `HSD_RvalueResolveRefsAll`, `HSD_RObjSetConstraintObj`, `_HSD_RObjForgetMemory`

## `src/sysdolphin/baselib/robj.h`

153 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `dolphin/mtx.h`, `sysdolphin/baselib/objalloc.h`

Definições aparentes: `RObjHasFlags`, `RObjHasFlags2`, `RObjHasLimitReftype`

## `src/sysdolphin/baselib/rumble.c`

275 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `rumble.h`, `Runtime/platform.h`, `controller.h`, `dolphin/os.h`, `dolphin/pad.h`

Definições aparentes: `HSD_PadRumbleOn`, `HSD_PadRumbleOffN`, `HSD_PadRumbleFree`, `HSD_PadRumbleRemove`, `HSD_PadRumbleRemoveAll`, `HSD_PadRumbleRemoveId`, `HSD_PadRumblePause`, `HSD_PadRumblePauseAll`, `HSD_PadRumbleUnpauseAll`, `func_80378430_inline`, `HSD_PadRumbleAdd`, `HSD_Rumble_80378524`, `HSD_PadRumbleInterpret1`, `HSD_PadRumbleInterpret`, `HSD_PadRumbleInit`

## `src/sysdolphin/baselib/rumble.h`

65 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/sysdolphin/baselib/shadow.c`

505 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `shadow.h`, `math.h`, `string.h`, `class.h`, `cobj.h`, `debug.h`, `jobj.h`, `list.h`, `memory.h`, `mobj.h`, `mtx.h`, `object.h`, `perf.h`, `pobj.h`, `state.h`, `tev.h`, `tobj.h`, `util.h`, `dolphin/gx.h`, `dolphin/mtx.h`

Definições aparentes: `HSD_ShadowGetAllocData`, `HSD_ShadowInitAllocData`, `makeShadowTObj`, `HSD_ShadowAlloc`, `HSD_ShadowRemove`, `HSD_ShadowInit`, `HSD_ShadowSetSize`, `drawBackgroundRect`, `HSD_ShadowStartRender`, `HSD_ShadowEndRender`, `HSD_ShadowSetActive`, `HSD_ShadowAddObject`, `HSD_ShadowDeleteObject`, `makeMatrix`, `HSD_ShadowSetViewingRect`, `HSD_ViewingRectInit`, `HSD_ViewingRectCheck`, `HSD_ViewingRectAddRect`

## `src/sysdolphin/baselib/shadow.h`

63 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `sysdolphin/baselib/list.h`, `sysdolphin/baselib/objalloc.h`, `sysdolphin/baselib/tobj.h`

## `src/sysdolphin/baselib/sislib.c`

603 linhas; 16 definições aparentes; 0 marcadores asm.

Includes: `sislib.h`, `stdio.h`, `cobj.h`, `gobj.h`, `gobjgxlink.h`, `gobjobject.h`, `gobjplink.h`, `gobjuserdata.h`, `memory.h`, `wobj.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `dolphin/os.h`, `dolphin/types.h`

Definições aparentes: `HSD_SisLib_Alloc`, `HSD_SisLib_Free`, `HSD_SisLib_803A5A2C`, `HSD_SisLib_803A5ACC`, `HSD_SisLib_803A5CC4`, `HSD_SisLib_803A5D30`, `HSD_SisLib_803A5DA0_inline0`, `HSD_SisLib_803A5DA0`, `HSD_SisLib_803A5E70`, `HSD_SisLib_803A5F50`, `HSD_SisLib_803A5FBC`, `HSD_SisLib_803A6048`, `fn_803A60EC`, `HSD_SisLib_803A611C`, `HSD_SisLib_803A62A0`, `HSD_SisLib_803A6368`

## `src/sysdolphin/baselib/sislib.h`

139 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `dolphin/gx/GXStruct.h`, `dolphin/mtx.h`, `sysdolphin/baselib/archive.h`

## `src/sysdolphin/baselib/sislib_font.c`

5 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sislib_font.h`, `sysdolphin/baselib/sislib_font.inc`

## `src/sysdolphin/baselib/sislib_font.h`

33 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/sysdolphin/baselib/sobjlib.c`

605 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `sobjlib.h`, `math.h`, `cobj.h`, `gobj.h`, `gobjgxlink.h`, `gobjobject.h`, `objalloc.h`, `pobj.h`, `state.h`, `tev.h`, `tobj.h`, `dolphin/gx.h`, `dolphin/os.h`

Definições aparentes: `HSD_SObjLib_803A44A4`, `HSD_SObjLib_803A44D4`, `HSD_SObjLib_803A466C`, `HSD_SObjLib_803A4740`, `order_data`, `HSD_SObjLib_803A477C`, `HSD_SObjLib_803A49E0`, `discard_color`, `HSD_SObjLib_803A4A68`, `HSD_SObjLib_803A54EC`, `HSD_SObjLib_803A55DC`

## `src/sysdolphin/baselib/sobjlib.h`

84 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx/GXStruct.h`, `sysdolphin/baselib/gobj.h`

## `src/sysdolphin/baselib/spline.c`

238 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `spline.h`, `math.h`, `placeholder.h`

Definições aparentes: `splGetHelmite`, `splGetCardinalPoint`, `splGetBSplinePoint`, `splGetBezierPoint`, `splGetSplinePoint`, `splArcLengthPolynomial`, `spl_GetCoeffs`, `spl_IterateSimpsonsMiddle`, `spl_GetArcLengthDx`, `splArcLengthGetParameter`, `splArcLengthPoint`

## `src/sysdolphin/baselib/spline.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `dolphin/mtx.h`

## `src/sysdolphin/baselib/state.c`

442 linhas; 22 definições aparentes; 0 marcadores asm.

Includes: `state.h`, `lobj.h`, `mobj.h`, `pobj.h`, `tev.h`, `texp.h`, `util.h`, `dolphin/gx/GXEnum.h`, `dolphin/gx/GXGeometry.h`, `dolphin/gx/GXPixel.h`, `dolphin/gx/GXTev.h`

Definições aparentes: `HSD_SetupChannelMode`, `HSD_SetupPEMode`, `setupTevMode_last`, `HSD_SetupRenderModeWithCustomPE`, `HSD_SetupRenderMode`, `HSD_SetMaterialColor`, `HSD_SetMaterialShininess`, `HSD_StateSetLineWidth`, `HSD_StateSetCullMode`, `HSD_StateSetBlendMode`, `HSD_StateSetZMode`, `HSD_StateSetPointSize`, `HSD_StateSetAlphaCompare`, `HSD_StateSetColorUpdate`, `HSD_StateSetAlphaUpdate`, `HSD_StateSetDstAlpha`, `HSD_StateSetZCompLoc`, `HSD_StateSetDither`, `_HSD_StateInvalidatePrimitive`, `_HSD_StateInvalidateVtxAttr`, `_HSD_StateInvalidateRenderMode`, `HSD_StateInvalidate`

## `src/sysdolphin/baselib/state.h`

58 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx.h`

## `src/sysdolphin/baselib/synth.c`

1634 linhas; 64 definições aparentes; 0 marcadores asm.

Includes: `synth.h`, `math.h`, `placeholder.h`, `string.h`, `debug.h`, `devcom.h`, `dolphin/ai.h`, `dolphin/ar.h`, `dolphin/ax.h`, `dolphin/os.h`

Definições aparentes: `HSD_AudioMalloc`, `HSD_AudioFree`, `SfxLoadStreamDataSize`, `HSD_SynthSFXSampleLoadCallback`, `HSD_SynthSFXHeaderLoadCallback`, `HSD_SynthSFXLoadNewProc`, `HSD_SynthSFXLoad`, `HSD_SynthSFXWaitForLoadCompletion`, `HSD_SynthSFXGetPendingLoadCount`, `HSD_SynthSFXCancelLoad`, `HSD_SynthSFXAllocateBank`, `order_data_0`, `HSD_SynthSFXGroupDataUnlink`, `HSD_SynthSFXUnloadBank`, `HSD_SynthSFXDataUnlink`, `HSD_SynthSFXGroupDataRemove`, `HSD_SynthSFXGroupDataReaddressCallback`, `order_data_1`, `HSD_SynthSFXGroupDataReaddress`, `HSD_SynthSFXBankDeflag`, `HSD_SynthSFXBankDeflagSync`, `HSD_SynthGetSoundMode`, `HSD_SynthSetSoundMode`, `HSD_SynthSFXStopNode`, `dropcallback`, `HSD_Synth_80389334`, `getNode`, `HSD_SynthSFXPlayWithGroup`, `freeVoices`, `HSD_SynthSFXKeyOff`, `stopRange`, `HSD_SynthSFXStopRange`, `HSD_SynthSFXPause`, `HSD_SynthSFXResume`, `HSD_SynthSFXCheck`, `HSD_SynthSFXSetVolumeFade`, `HSD_SynthSFXSetPan`, `HSD_SynthSFXSetMix`, `HSD_SynthSFXUpdatePitch`, `HSD_SynthSFXSetPitchRatio`, `HSD_SynthSFXSetPriority`, `user_vol_dst_offset`, `user_vol_src_offset`, `HSD_SynthSFXVolumeEnvelope`, `HSD_SynthSFXUpdateVolume`, `my_memzero`, `HSD_SynthSFXUpdateMix`, `updateAllVolume`, `HSD_SynthSFXUpdateAllVolume`, `HSD_SynthSFXSetDriverInactivatedCallback`, `HSD_SynthSFXSetDriverMasterClockCallback`, `HSD_SynthSFXSetDriverPauseCallback`, `HSD_SynthCallback`, `HSD_SynthResetStreamCounters`, `HSD_SynthPStreamHakoHeaderCallback`, `HSD_SynthPStreamMasterClockCallback_inline`, `HSD_SynthPStreamMasterClockCallback`, `HSD_SynthPStreamFirstHakoDataCallback`, `HSD_SynthPStreamFirstHakoHeaderCallback`, `HSD_SynthPStreamHeaderCallback`, `HSD_SynthPStreamStart_inline`, `HSD_SynthPStreamStart`, `HSD_SynthStreamSetVolume`, `HSD_SynthInit`

## `src/sysdolphin/baselib/synth.h`

66 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `placeholder.h`, `dolphin/os/OSAlloc.h`

## `src/sysdolphin/baselib/tev.c`

544 linhas; 30 definições aparentes; 0 marcadores asm.

Includes: `tev.h`, `string.h`, `debug.h`, `dolphin/gx.h`

Definições aparentes: `HSD_RenderInitAllocData`, `HSD_RenderGetAllocData`, `HSD_TevRegGetAllocData`, `HSD_ChanGetAllocData`, `CompareRGB`, `CompareRGBA`, `CopyRGB`, `HSD_SetupChannel`, `HSD_StateSetNumChans`, `HSD_SetupChannelAll`, `HSD_StateRegisterTexGen`, `HSD_StateSetNumTexGens`, `HSD_StateInitTev`, `HSD_StateGetNumTevStages`, `HSD_StateAssignTev`, `HSD_StateSetNumTevStages`, `HSD_SetupTevStage`, `setupTevStages`, `HSD_SetupTevStageAll`, `HSD_Channel2Num`, `HSD_Index2TevStage`, `HSD_TevStage2Index`, `HSD_TevStage2Num`, `HSD_SetTevRegAll`, `HSD_TexCoordID2Num`, `ChanUpdateFunc`, `_HSD_StateInvalidateColorChannel`, `_HSD_StateInvalidateTevStage`, `_HSD_StateInvalidateTevRegister`, `_HSD_StateInvalidateTexCoordGen`

## `src/sysdolphin/baselib/tev.h`

36 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/objalloc.h`, `sysdolphin/baselib/state.h`, `sysdolphin/baselib/texp.h`

## `src/sysdolphin/baselib/texp.c`

1235 linhas; 26 definições aparentes; 0 marcadores asm.

Includes: `texp.h`, `string.h`, `class.h`, `debug.h`, `tev.h`, `texpdag.h`, `tobj.h`

Definições aparentes: `HSD_TExpGetType`, `TevAlloc`, `CnstAlloc`, `HSD_TExpFree`, `HSD_TExpRef`, `HSD_TExpUnref`, `HSD_TExpFreeList`, `HSD_TExpTev`, `HSD_TExpCnst`, `HSD_TExpColorOp`, `HSD_TExpAlphaOp`, `HSD_TExpColorInSub`, `HSD_TExpColorIn`, `HSD_TExpAlphaInSub`, `HSD_TExpAlphaIn`, `HSD_TExpOrder`, `AssignColorReg`, `AssignAlphaReg`, `AssignColorKonst`, `AssignAlphaKonst`, `TExpAssignReg`, `TExp2TevDesc`, `HSD_TExpSetReg`, `HSD_TExpSetupTev`, `HSD_TExpCompile`, `HSD_TExpFreeTevDesc`

## `src/sysdolphin/baselib/texp.h`

212 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx/GXEnum.h`

Definições aparentes: `IsThroughColor`, `IsThroughAlpha`

## `src/sysdolphin/baselib/texpdag.c`

1317 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `texpdag.h`, `placeholder.h`, `string.h`, `debug.h`, `texp.h`, `tobj.h`

Definições aparentes: `assign_reg`, `order_dag`, `CalcDistance`, `HSD_TExpMakeDag`, `make_dependancy_mtx`, `make_full_dependancy_mtx`, `HSD_TExpSchedule`, `SimplifySrc`, `SimplifyThis`, `SimplifyByMerge`, `HSD_TExpSimplify`, `HSD_TExpSimplify2`

## `src/sysdolphin/baselib/texpdag.h`

38 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/texp.h`

## `src/sysdolphin/baselib/tobj.c`

1626 linhas; 59 definições aparentes; 0 marcadores asm.

Includes: `tobj.h`, `placeholder.h`, `string.h`, `aobj.h`, `cobj.h`, `debug.h`, `lobj.h`, `memory.h`, `mtx.h`, `tev.h`, `dolphin/gx.h`, `dolphin/mtx.h`

Definições aparentes: `HSD_TObjRemoveAnim`, `HSD_TObjRemoveAnimAll`, `lookupTextureAnim`, `HSD_TObjAddAnim`, `HSD_TObjAddAnimAll`, `HSD_TObjReqAnimByFlags`, `HSD_TObjReqAnimAllByFlags`, `HSD_TObjReqAnim`, `HSD_TObjReqAnimAll`, `TObjUpdateFunc`, `HSD_TObjAnim`, `HSD_TObjAnimAll`, `TObjLoad`, `HSD_TObjLoadDesc`, `HSD_TlutLoadDesc`, `HSD_TObjTevLoadDesc`, `_HSD_TObjGetCurrentByType`, `HSD_TexMapID2PTTexMtx`, `MakeTextureMtx`, `TObjSetupMtx`, `setupTextureCoordGen`, `setupTextureCoordGenBump`, `setupTextureCoordGenToon`, `HSD_TObjSetupTextureCoordGen`, `TObjSetupTevModulateShadow`, `SetupEmbossBumpTev`, `HSD_TObjSetupVolatileTev`, `MakeColorGenTExp`, `TObjMakeTExp`, `HSD_TObjAssignResources`, `DifferentTluts`, `HSD_TObjSetup`, `HSD_TGTex2Index`, `HSD_TexCoordID2TexGenSrc`, `HSD_TexCoord2Index`, `HSD_Index2TexCoord`, `HSD_TexMtx2Index`, `HSD_Index2TexMtx`, `HSD_Index2TexMap`, `HSD_TexMap2Index`, `HSD_TObjRemove`, `HSD_TObjRemoveAll`, `HSD_TObjGetNext`, `HSD_TObjSetDefaultClass`, `HSD_TObjGetDefaultClass`, `HSD_TObjAlloc`, `HSD_TObjFree`, `HSD_TlutAlloc`, `HSD_TlutFree`, `HSD_TlutRemove`, `HSD_TObjTevAlloc`, `HSD_TObjTevFree`, `HSD_TObjTevRemove`, `HSD_ImageDescAlloc`, `HSD_ImageDescFree`, `HSD_ImageDescCopyFromEFB`, `TObjRelease`, `TObjAmnesia`, `TObjInfoInit`

## `src/sysdolphin/baselib/tobj.h`

322 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `dolphin/gx.h`, `dolphin/gx/GXEnum.h`, `dolphin/mtx.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/object.h`

## `src/sysdolphin/baselib/util.c`

58 linhas; 3 definições aparentes; 0 marcadores asm.

Includes: `util.h`, `debug.h`, `dolphin/gx.h`

Definições aparentes: `HSD_MulColor`, `HSD_GetNbBits`, `HSD_Index2PosNrmMtx`

## `src/sysdolphin/baselib/util.h`

48 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `stdlib.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `sysdolphin/baselib/mtx.h`

Definições aparentes: `vec_normalize_check`, `atan2f_check`

## `src/sysdolphin/baselib/video.c`

442 linhas; 23 definições aparentes; 0 marcadores asm.

Includes: `video.h`, `debug.h`, `state.h`, `dolphin/gx.h`, `dolphin/vi.h`

Definições aparentes: `HSD_VISearchXFBByStatus`, `HSD_VISetUserPreRetraceCallback`, `HSD_VISetUserPostRetraceCallback`, `HSD_VISetUserGXDrawDoneCallback`, `HSD_VIPreRetraceCB`, `HSD_VIPostRetraceCB`, `HSD_VIGXDrawDoneCB`, `HSD_VIGetDrawDoneWaitingFlag`, `HSD_VIGetXFBDrawEnable`, `HSD_VIWaitXFBDrawEnable`, `HSD_VICopyEFB2XFBHiResoAA`, `HSD_VICopyEFB2XFBPtr`, `HSD_VIGXSetDrawDone`, `HSD_VISetXFBWaitDone`, `HSD_VICopyXFBAsync`, `HSD_VIDrawDoneXFB`, `HSD_VIWaitXFBFlush_sub`, `HSD_VIWaitXFBFlush`, `HSD_VIWaitXFBFlushNoYield`, `HSD_VIGetXFBLastDrawDone`, `HSD_VISetConfigure`, `HSD_VISetBlack`, `HSD_VIInit`

## `src/sysdolphin/baselib/video.h`

144 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/gx.h`, `dolphin/gx/GXEnum.h`

Definições aparentes: `HSD_VIGetNbXFB`, `HSD_VIGetXFBPtr`, `HSD_VIGetVIStatus`, `HSD_VIGetRenderMode`

## `src/sysdolphin/baselib/wobj.c`

265 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `wobj.h`, `aobj.h`, `class.h`, `debug.h`, `jobj.h`, `object.h`, `robj.h`, `spline.h`, `dolphin/mtx.h`

Definições aparentes: `HSD_WObjRemoveAnim`, `HSD_WObjReqAnim`, `HSD_WObjAddAnim`, `WObjUpdateFunc`, `HSD_WObjInterpretAnim`, `WObjLoad`, `HSD_WObjInit`, `HSD_WObjSetDefaultClass`, `HSD_WObjLoadDesc`, `HSD_WObjSetPosition`, `HSD_WObjSetPositionX`, `HSD_WObjSetPositionY`, `HSD_WObjSetPositionZ`, `HSD_WObjGetPosition`, `HSD_WObjAlloc`, `WObjRelease`, `WObjAmnesia`, `WObjInfoInit`

## `src/sysdolphin/baselib/wobj.h`

75 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/object.h`

Definições aparentes: `HSD_WObjUnref`, `HSD_WObjClearFlags`

