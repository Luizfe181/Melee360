# Catálogo: src/melee/mn

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/melee/mn/forward.h`

221 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/mn/inlines.h`

97 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `melee/lb/lbaudio_ax.h`, `melee/lb/lbspdisplay.h`, `melee/mn/mnmain.h`, `melee/mn/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `Menu_DecrementAnimTimer`, `Menu_GetAllInputs`, `Menu_GetInputsForPort`, `sfxBack`, `sfxForward`, `sfxMove`, `Menu_InitCenterText`, `inline_test_3`, `inline_test_4`

## `src/melee/mn/mn_22EC.c`

337 linhas; 16 definições aparentes; 0 marcadores asm.

Includes: `mncharsel.h`, `mnmain.h`, `types.h`, `dolphin/pad.h`, `melee/gm/gm_unsplit.h`, `melee/gm/gmmain_lib.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `mn_8022EC18`, `mn_8022ED6C`, `mn_8022EE84`, `mn_8022EFD8`, `mn_8022F0F0`, `mn_8022F138`, `mn_8022F1A8_inline`, `mn_8022F1A8`, `mn_8022F218`, `mn_8022F268`, `mn_8022F298`, `mn_8022F360`, `mn_8022F3D8`, `mn_8022F410`, `mn_8022F470`, `mn_8022F4CC`

## `src/melee/mn/mncharsel.c`

5490 linhas; 54 definições aparentes; 0 marcadores asm.

Includes: `mncharsel.h`, `melee/ft/forward.h`, `sysdolphin/baselib/forward.h`, `math.h`, `inlines.h`, `mnmain.h`, `mnmainrule.h`, `mnname.h`, `mnnamenew.h`, `types.h`, `melee/gm/gm_1601.h`, `melee/gm/gm_unsplit.h`, `melee/gm/gmmain_lib.h`, `melee/gm/types.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_013B.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lbdvd.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/lb/types.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/sislib_font.h`

Definições aparentes: `mnCharSel_8025BC20`, `mnCharSel_8025BD30`, `loadStickValue`, `getStickDelta`, `drawTimeText`, `getClassicHighscore`, `getAdventureHighscore`, `getAllStarHighscore`, `toMeters`, `toFeet`, `inline3`, `mnCharSel_8025C020`, `mnCharSel_8025D1C4`, `sethidden`, `animateJoint`, `animateJointPadded`, `animateJointLeadingPad`, `mnCharSel_8025D5AC`, `isDuplicateCostumeWith`, `loadCSSValue`, `equalU8`, `isDuplicateCostumeCached`, `isDuplicateCostumeExact`, `isDuplicateCostume`, `mnCharSel_8025DAA0`, `pickUniqueCostume`, `getHandicapValue`, `mnCharSel_8025DB34`, `mnCharSel_8025EE8C`, `updateStockIcons`, `fn_8025F0E0`, `fn_8025FAC0`, `fn_8025FB2C`, `getIconOffset`, `getPlayerForDoor`, `mnCharSel_8025FB50`, `mnCharSel_8025FDEC`, `mnCharSel_CostumeChange`, `updateCursorDisplay`, `updateGrabbedSlider`, `cycleTeam`, `mnCharSel_CursorThink`, `getDoorCount`, `animateCharModel`, `fn_80262648`, `fn_80262F44`, `fn_80263354`, `fn_802633B0`, `mnCharSel_80264070`, `fn_8026407C`, `mnCharSel_802640A0`, `mnCharSel_Scene_OnEnter`, `mnCharSel_Scene_OnFrame`, `mnCharSel_Scene_OnExit`

## `src/melee/mn/mncharsel.h`

54 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `melee/sc/types.h`

## `src/melee/mn/mncount.c`

841 linhas; 35 definições aparentes; 0 marcadores asm.

Includes: `mncount.h`, `placeholder.h`, `inlines.h`, `mndiagram.h`, `mnmain.h`, `mnname.h`, `types.h`, `melee/gm/gm_1601.h`, `melee/gm/gmmain_lib.h`, `melee/gm/types.h`, `melee/lb/lbarchive.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `melee/ty/toy.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `inline_is_row_time`, `inline_is_row_char`, `inline_update_entries`, `mnCount_8025035C_inline`, `mnCount_GetMatchTime`, `mnCount_GetKOKingpin`, `mnCount_GetNoDefenseNelly`, `mnCount_GetDisasterMaster`, `mnCount_8025035C`, `mnCount_GetSmashChamp`, `mnCount_GetSmashSap`, `mnCount_GetSlugMeister`, `mnCount_GetPunchingBag`, `mnCount_8025072C`, `mnCount_8025092C_inline`, `mnCount_8025092C`, `mnCount_CountUnlockedChars`, `mnCount_CountUnlockedMaps`, `mnCount_GetRowValue_Character`, `mnCount_GetCombinedVSPlayTimeValue`, `mnCount_GetRowValue_Number`, `mnCount_CreateRow`, `mnCount_HandleUserInput`, `mnCount_UpdateArrowIndicators`, `mnCount_UpdateArrowIndicators_noinline`, `fn_802514B8`, `fn_802514D8_inline`, `fn_802514D8`, `fn_80251640_FreeText`, `fn_80251640_InitModel`, `fn_80251640`, `mnCount_InitUserData`, `mnCount_InitUserData_noinline`, `mnCount_AllocUserData`, `mnCount_Create`

## `src/melee/mn/mncount.h`

87 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/mn/forward.h`, `sysdolphin/baselib/forward.h`, `melee/mn/types.h`

## `src/melee/mn/mndatadel.c`

959 linhas; 23 definições aparentes; 0 marcadores asm.

Includes: `mndatadel.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `forward.h`, `inlines.h`, `mnmain.h`, `mnmainrule.h`, `types.h`, `melee/gm/gm_1601.h`, `melee/gm/gm_16F1.h`, `melee/gm/gm_1A36.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `melee/ty/toy.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`

Definições aparentes: `sdata2_order`, `mnDataDel_8024E940_inline`, `mnDataDel_8024E940`, `mnDataDel_8024EA6C_inline`, `mnDataDel_8024EA6C`, `mnDataDel_8024EBC8`, `mnDataDel_GetWarnData`, `mnDataDel_AnimateWarning`, `fn_8024ECCC`, `mnDataDel_8024EEC0`, `fn_8024F1D4`, `mnDataDel_GetMenuJObj`, `fn_8024F318`, `fn_8024F840_inline`, `mnDataDel_UpdateDescription`, `fn_8024F840`, `fn_8024FBA4`, `fn_8024FC48_inline`, `fn_8024FC48`, `mnDataDel_GetAnimSettings`, `fn_8024FD40`, `mnDataDel_8024FE4C`, `mnDataDel_80250170`

## `src/melee/mn/mndatadel.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/mn/mndeflicker.c`

193 linhas; 7 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `inlines.h`, `mnmain.h`, `types.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lbarchive.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnDeflicker_8024A168`, `mnDeflicker_8024A2E8`, `mnDeflicker_8024A344`, `mnDeflicker_8024A3E8`, `mnDeflicker_8024A4BC_inline`, `mnDeflicker_8024A4BC`, `mnDeflicker_8024A6C4`

## `src/melee/mn/mndeflicker.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/mn/mndiagram.c`

2544 linhas; 83 definições aparentes; 0 marcadores asm.

Includes: `mndiagram.h`, `melee/gm/forward.h`, `inlines.h`, `mndiagram2.h`, `mndiagram3.h`, `mnmain.h`, `mnname.h`, `types.h`, `dolphin/types.h`, `melee/gm/gm_1601.h`, `melee/gm/gmmain_lib.h`, `melee/gm/types.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00CE.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`

Definições aparentes: `mnDiagram_GetFighterByIndex`, `mnDiagram_GetNameByIndex`, `mnDiagram_IsDistanceOverflow`, `mnDiagram_ConvertDistanceForDisplay`, `mnDiagram_GetHitPercentage`, `mnDiagram_GetPlayPercentage`, `mnDiagram_GetAveragePlayerCount`, `getNamePairKOs`, `mnDiagram_GetNameTotalKOs`, `sumNameKOs`, `mnDiagram_GetNameTotalFalls`, `mnDiagram_GetFighterTotalKOs`, `mnDiagram_SumFighterFalls`, `mnDiagram_GetFighterTotalFalls`, `mnDiagram_FormatDecimalNumber`, `writeIntegerDigits`, `mnDiagram_FormatTime`, `mnDiagram_IntToStr`, `mnDiagram_GetPrevNameIndex`, `mnDiagram_GetNextNameIndex`, `mnDiagram_GetPrevFighterIndex`, `mnDiagram_GetNextFighterIndex`, `mnDiagram_GetNamePlayTimeByFighter`, `allPlayTimesZero`, `mnDiagram_GetRankedFighterForName`, `mnDiagram_GetLeastPlayedFighter`, `mnDiagram_SortFightersByKOs`, `mnDiagram_SortNamesByKOs`, `mnDiagram_CountUnlockedFighters`, `mnDiagram_PopupInputProc`, `mnDiagram_GetVisibleNameFrom`, `mnDiagram_FindPrevFighter`, `mnDiagram_FindNextFighter`, `mnDiagram_FindPrevName`, `mnDiagram_FindPrevNameWrap`, `mnDiagram_FindPrevFighterWrap`, `mnDiagram_FindNextName`, `mnDiagram_GetVisibleNameCursorFrom`, `mnDiagram_GetVisibleFighterCursorFrom`, `mnDiagram_GetVisibleFighterColumnForInput`, `mnDiagram_GetVisibleFighterRowForInput`, `mnDiagram_GetVisibleFighterFromPointer`, `mnDiagram_GetVisibleFighterCursorFrom2`, `mnDiagram_GetCurrentDiagramData`, `saveCursorPositions`, `getHoveredRow`, `getHoveredColumn`, `mnDiagram_InputProc`, `removeText`, `mnDiagram_PopupCleanup`, `mnDiagram_PopupAnimProc_Inline`, `mnDiagram_TextSetPos`, `mnDiagram_PopupAnimProc`, `mnDiagram_FormatPopupNumber`, `setPopupTextPosition`, `mnDiagram_CreatePopupTexts`, `mnDiagram_CreatePopup`, `mnDiagram_ClearGrid`, `refreshGrid`, `mnDiagram_RefreshGrid`, `setArrowVisible`, `mnDiagram_UpdateScrollArrows`, `mnDiagram_ExitAnimProc`, `updateScrollArrowVisibility`, `mnDiagram_UpdateScrollArrowVisibility`, `getEntryCount`, `getFighterCount`, `mnDiagram_OnFrame`, `requestIntegerAnimFrame`, `mnDiagram_DrawCellValue`, `mnDiagram_GetFighterPairKOs`, `mnDiagram_DrawGridValues`, `getColumnReferenceX`, `getRowReferenceY`, `mnDiagram_DrawNameHeaders`, `mnDiagram_CreateFighterIcon`, `mnDiagram_LoadHeaderIcon`, `getVisibleFighter`, `mnDiagram_DrawFighterHeaders`, `mnDiagram_CursorProc`, `mnDiagram_CreateCursor`, `mnDiagram_CreateScreen`, `mnDiagram_Init`

## `src/melee/mn/mndiagram.h`

127 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `melee/mn/types.h`, `melee/sc/types.h`

## `src/melee/mn/mndiagram2.c`

1312 linhas; 25 definições aparentes; 0 marcadores asm.

Includes: `mndiagram2.h`, `sysdolphin/baselib/forward.h`, `stdbool.h`, `inlines.h`, `mndiagram.h`, `mndiagram3.h`, `mnmain.h`, `types.h`, `melee/gm/gm_1601.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbspdisplay.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnDiagram2_IsTimeStat`, `mnDiagram2_IsDistanceStat`, `mnDiagram2_IsPercentageStat`, `mnDiagram2_IsIconOnlyStat`, `mnDiagram2_ClearStatRows`, `mnDiagram2_UpdateHeader`, `getCurrentDiagramData`, `mnDiagram2_RefreshStatRows`, `saveDiagramSelection`, `updateDiagramMode`, `mnDiagram2_HandleInput`, `mnDiagram2_GetStatValue`, `mnDiagram2_CreateStatRow`, `mnDiagram2_PopulateStatRows`, `mnDiagram2_OnAnimComplete`, `mnDiagram2_UpdateScrollArrows`, `mnDiagram2_Think`, `mnDiagram2_FreeUserData`, `mnDiagram2_InitUserData`, `mnDiagram2_Create`, `mnDiagram2_Init`, `mnDiagram2_GetRankedFighter`, `mnDiagram2_GetRankedName`, `mnDiagram2_GetAggregatedFighterRank`, `mnDiagram2_ClearDetailView`

## `src/melee/mn/mndiagram2.h`

56 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/mn/types.h`, `sysdolphin/baselib/gobj.h`

## `src/melee/mn/mndiagram3.c`

780 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `mndiagram3.h`, `inlines.h`, `mndiagram.h`, `mndiagram2.h`, `mnmain.h`, `mnname.h`, `types.h`, `dolphin/gx/GXStruct.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbspdisplay.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `sdata2_order`, `mnDiagram3_PopulateRankings`, `mnDiagram3_GetRowSpacing`, `mnDiagram3_ClearRowLabels`, `mnDiagram3_GetRowStat`, `mnDiagram3_RebuildRowLabels`, `mnDiagram3_RefreshRankings`, `mnDiagram3_PositionPopup`, `mnDiagram3_HandleInput`, `mnDiagram3_UpdateScrollArrows`, `mnDiagram3_OnAnimComplete`, `mnDiagram3_Think`, `mnDiagram3_FreeUserData`, `mnDiagram3_InitUserData`, `mnDiagram3_LoadJoint`, `mnDiagram3_Create`, `mnDiagram3_SetupRows`, `mnDiagram3_GetPopupSpacing`, `mnDiagram3_GetPopupY`, `mnDiagram3_CreatePopup`, `mnDiagram3_Init`

## `src/melee/mn/mndiagram3.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `melee/mn/types.h`, `sysdolphin/baselib/gobj.h`

## `src/melee/mn/mnevent.c`

733 linhas; 23 definições aparentes; 0 marcadores asm.

Includes: `mnevent.h`, `melee/ft/forward.h`, `placeholder.h`, `inlines.h`, `mnmain.h`, `types.h`, `melee/db/db.h`, `melee/gm/gm_1601.h`, `melee/gm/gmevent.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lbarchive.h`, `melee/lb/lbspdisplay.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnEvent_CountUnlocked`, `mnEvent_8024D014`, `mnEvent_8024D0CC`, `mnEvent_GetData`, `getMainConEv`, `getMainMarkEv`, `mnEvent_CreateIconForSlot`, `mnEvent_8024D15C`, `mnEvent_8024D4E0`, `mnEvent_8024D5B0`, `mnEvent_8024D7E0`, `mnEvent_RefreshRows`, `mnEvent_ShowSelected`, `mnEvent_SetPageCursorY`, `mnEvent_8024D864`, `GET_EVENTDATA`, `mnEvent_8024E1B4`, `mnEvent_8024E2A0`, `mnEvent_8024E34C`, `mnEvent_SetPageY`, `mnEvent_8024E420`, `mnEvent_8024E524`, `mnEvent_8024E838`

## `src/melee/mn/mnevent.h`

34 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `dolphin/mtx.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

## `src/melee/mn/mngallery.c`

509 linhas; 16 definições aparentes; 0 marcadores asm.

Includes: `mngallery.h`, `inlines.h`, `melee/gm/gmhowto.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lbarchive.h`, `melee/lb/lbmthp.h`, `melee/sc/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sobjlib.h`

Definições aparentes: `float_order_helper`, `mnGallery_80258940`, `mnGallery_8025896C`, `mnGallery_80258A08`, `mnGallery_80258BC4`, `mnGallery_80258D50`, `mnGallery_80258DBC`, `fn_80258ED0_helper`, `fn_80258ED0`, `fn_802590C4_inline`, `fn_802590C4`, `mnGallery_802591BC`, `mnGallery_80259604`, `initUserData`, `mnGallery_8025963C`, `mnGallery_80259868`

## `src/melee/mn/mngallery.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/gobj.h`

## `src/melee/mn/mnhyaku.c`

229 linhas; 8 definições aparentes; 0 marcadores asm.

Includes: `mnhyaku.h`, `melee/gm/forward.h`, `melee/it/forward.h`, `melee/sc/forward.h`, `inlines.h`, `mnmain.h`, `types.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/sc/types.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/memory.h`

Definições aparentes: `mnHyaku_8024C68C_inline`, `mnHyaku_8024C68C_inline_2`, `mnHyaku_8024C68C`, `mnHyaku_8024C9F0`, `mnHyaku_8024CA50`, `mnHyaku_8024CAC8`, `mnHyaku_8024CB94`, `mnHyaku_8024CD64`

## `src/melee/mn/mnhyaku.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjproc.h`

## `src/melee/mn/mninfo.c`

571 linhas; 23 definições aparentes; 0 marcadores asm.

Includes: `mninfo.h`, `placeholder.h`, `inlines.h`, `mnmain.h`, `melee/gm/gm_1601.h`, `melee/gm/gmmain_lib.h`, `melee/gm/types.h`, `melee/if/ifprize.h`, `melee/lb/lbarchive.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnInfo_80251A08`, `isUnlockVisible`, `mnInfo_80251AA4`, `mnInfo_80251AFC_inline`, `mnInfo_80251AFC_inline_2`, `mnInfo_80251AFC_inline_3`, `mnInfo_80251AFC`, `mnInfo_80251D58`, `mnInfo_80251F04`, `mnInfo_CountUnlocked`, `mnInfo_CreateEntry`, `mnInfo_CreateEntries`, `mnInfo_FreeEntries`, `fn_80251FE4`, `mnInfo_802522B8`, `fn_802523B8`, `fn_802523D8_inline`, `fn_802523D8`, `fn_80252548_inline`, `fn_80252548`, `mnInfo_80252720`, `initUserData`, `mnInfo_80252758`

## `src/melee/mn/mninfo.h`

23 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/mn/forward.h`, `melee/sc/forward.h`, `sysdolphin/baselib/forward.h`

## `src/melee/mn/mninfobonus.c`

359 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `mninfobonus.h`, `melee/sc/forward.h`, `sysdolphin/baselib/forward.h`, `inlines.h`, `mnmain.h`, `melee/db/db.h`, `melee/gm/gm_16F1.h`, `melee/gm/gmvs.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/sc/types.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnInfoBonus_802528F8_inline`, `textSize`, `textSetup`, `mnInfoBonus_802528F8`, `mnInfoBonus_802528F8_wrapper`, `mnInfoBonus_802529B4_inline0`, `mnInfoBonus_802529B4_inline1`, `mnInfoBonus_802529B4`, `mnInfoBonus_80252ADC_inline`, `mnInfoBonus_80252ADC`, `fn_80252C50`, `fn_80252E4C`, `mnInfoBonus_inline_SetGObjFlag`, `mnInfoBonus_80252F8C_inline0`, `mnInfoBonus_80252F8C`

## `src/melee/mn/mninfobonus.h`

13 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/mn/mnitemsw.c`

909 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `mnitemsw.h`, `Runtime/platform.h`, `inlines.h`, `mnmain.h`, `mnmainrule.h`, `melee/gm/gm_1601.h`, `melee/gm/gm_1A3F.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lbcardgame.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnItemSw_GetTable`, `mnItemSw_80233A98`, `mnItemSw_80233B68`, `mnItemSw_CommitItems`, `fn_80233E10`, `mnItemSw_8023405C`, `mnItemSw_GetItemAnim`, `mnItemSw_SetCursorPosition`, `mnItemSw_80234104`, `mnItemSw_ReqFreqAnim`, `mnItemSw_UpdateConfirmed`, `mnItemSw_8023453C`, `mnItemSw_SaveSettings`, `fn_80234C24`, `mnItemSw_80235020`, `setInitialCursorPosition`, `initUserData`, `mnItemSw_802351A0`, `mnItemSw_802358C0`

## `src/melee/mn/mnitemsw.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

## `src/melee/mn/mnlanguage.c`

220 linhas; 7 definições aparentes; 0 marcadores asm.

Includes: `mnlanguage.h`, `melee/gm/forward.h`, `melee/it/forward.h`, `melee/sc/forward.h`, `inlines.h`, `mnmain.h`, `melee/lb/lbarchive.h`, `melee/lb/lbcardgame.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/object.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnLanguage_8024BFE0`, `fn_8024C210`, `fn_8024C270`, `fn_8024C2E8`, `order_sdata2`, `mnLanguage_8024C3C4`, `mnLanguage_8024C5C0`

## `src/melee/mn/mnlanguage.h`

13 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/mn/mnmain.c`

3047 linhas; 66 definições aparentes; 0 marcadores asm.

Includes: `mnmain.h`, `melee/gm/forward.h`, `math.h`, `forward.h`, `inlines.h`, `mncount.h`, `mndatadel.h`, `mndeflicker.h`, `mndiagram.h`, `mnevent.h`, `mngallery.h`, `mnhyaku.h`, `mninfo.h`, `mninfobonus.h`, `mnlanguage.h`, `mnmainrule.h`, `mnname.h`, `mnsnap.h`, `mnsound.h`, `mnsoundtest.h`, `mnvibration.h`, `types.h`, `dolphin/pad.h`, `melee/gm/gm_unsplit.h`, `melee/gm/gmevent.h`, `melee/gm/gmmain_lib.h`, `melee/gm/types.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00CE.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lblanguage.h`, `melee/lb/lbmthp.h`, `melee/sc/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/mobj.h`

Definições aparentes: `sdata2_order`, `mn_802295AC`, `mn_80229624`, `mn_80229860`, `mn_80229894`, `mn_80229938`, `mn_80229A04`, `mn_80229A04_dontinline`, `mn_80229A7C`, `mn_80229A7C_dontinline`, `mn_80229B2C`, `fn_80229BF4`, `mn_80229DC0`, `mn_80229F60`, `mn_8022A440`, `mn_8022A5D0`, `GetAnimStartFrame`, `GetAnimEndFrame`, `mn_8022ADD8`, `fn_8022AF10`, `fn_8022AFEC`, `GetSelectionFrameOffset`, `CountUnlockedSelections`, `mn_8022B3A0`, `mn_8022BA1C`, `fn_8022BCD4`, `mn_8022BCF8`, `mn_8022BD6C`, `mn_8022BD8C`, `fn_8022BDB4`, `mn_8022BE34`, `mn_8022BE34_OnEnter`, `mn_8022BEDC`, `mn_8022BFBC`, `mn_8022C010`, `LerpLightColor`, `mn_8022C068`, `fn_8022C128`, `mn_8022C304`, `x2_dec`, `x2_inc`, `decrement_selection`, `increment_selection`, `mn_8022C4F4`, `mn_8022C7CC_inline`, `mn_8022C7CC`, `mn_8022CA54`, `mn_8022CC28`, `mn_8022CE6C`, `mn_8022D104`, `mn_8022D34C`, `mn_8022D594`, `mn_8022D7F4`, `mn_8022DB10`, `mnMain_Scene_OnFrame`, `mn_8022DDA8_inline`, `mnMain_Scene_OnEnter`, `mn_IsFighterUnlocked`, `mn_8022E978`, `mn_8022EA08`, `mn_8022EA78`, `mn_8022EAE0`, `mn_8022EB04`, `mn_GetDigitAt`, `mn_GetDigitCount`, `mn_8022EBDC`

## `src/melee/mn/mnmain.h`

139 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/mn/forward.h`, `dolphin/gx.h`, `melee/mn/types.h`, `melee/sc/types.h`, `sysdolphin/baselib/object.h`

## `src/melee/mn/mnmainrule.c`

1504 linhas; 24 definições aparentes; 0 marcadores asm.

Includes: `mnmainrule.h`, `inlines.h`, `mnmain.h`, `melee/gm/gm_1A36.h`, `melee/gm/gm_1A3F.h`, `melee/gm/gmmain_lib.h`, `melee/gm/gmtoulib.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mn_8022F538_GetHoveredSelection`, `fn_8022F538`, `mn_8022FB88`, `mn_8022FD18`, `mn_8022FEC8_AnimDigit`, `mn_8022FEC8_AnimDamageDigits`, `mn_8022FEC8_GetSettings`, `mn_8022FEC8_AnimStockDigits`, `mn_8022FEC8`, `mn_80230198`, `mn_80230274_InitOptionRoots`, `mn_80230274`, `mn_802307F8`, `mn_802308F0`, `fn_802309F0`, `mn_80230D18`, `mn_80230E38_CountVisible`, `mn_80230E38`, `mn_80231634`, `mn_8023164C`, `mn_80231714`, `mn_802317E4`, `mn_80231804`, `mn_80231F80`

## `src/melee/mn/mnmainrule.h`

53 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/mn/mnname.c`

1800 linhas; 59 definições aparentes; 0 marcadores asm.

Includes: `mnname.h`, `placeholder.h`, `forward.h`, `inlines.h`, `mnmain.h`, `mnmainrule.h`, `mnnamenew.h`, `types.h`, `dolphin/gx/GXStruct.h`, `dolphin/mtx.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`

Definições aparentes: `order_sdata`, `mnName_8023749C`, `GetNameText`, `GetNameCount_noinline`, `GetNameCount`, `GetNumNameList`, `IsNameListFull`, `readNameTerminator`, `signedCharactersEqual`, `checkStringRest`, `unsignedCharacter`, `CompareNameStrings`, `IsNameUnique`, `DeleteName`, `IsNameValid`, `CreateNameAtIndex`, `mnName_SortNames`, `mnName_80237D94`, `mnName_ConfirmNameDeleteInput`, `mnName_GetHoveredName`, `mnName_CountValid`, `mnName_MainInput`, `fn_80238540`, `mnName_802385A0`, `mnName_GetPageCount`, `mnName_GetColumnCount`, `mnName_80238754_noinline`, `mnName_80238754`, `mnName_802388D4_noinline`, `mnName_802388D4`, `mnName_80238964_noinline`, `mnName_80238964`, `mnName_80238A04`, `mnName_80238AE0`, `mnName_FindAnimLoop`, `mnName_80238C34_inline`, `mnName_UpdateSelection`, `mnName_80238C34`, `fn_80239574`, `mnName_80239878`, `mnName_TextWidth`, `mnName_GetDisplayIndex`, `mnName_80239A24`, `mnName_80239EBC`, `mnName_80239F5C`, `mnName_80239FFC`, `mnName_8023A058`, `fn_8023A0BC`, `mnName_SetupDeleteCursor`, `mnName_8023A290`, `mnName_SetupScrollbarAndText`, `mnName_8023A59C`, `mnName_8023A9B4_GetUserData`, `mnName_8023A9B4_ResetDisplayOrder`, `mnName_8023A9B4_GetGObj`, `mnName_8023A9B4`, `mnName_InitNameDisplayOrder`, `mnName_8023AC40`, `IsNameNotAllowed`

## `src/melee/mn/mnname.h`

55 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `stdbool.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

## `src/melee/mn/mnnamenew.c`

1986 linhas; 40 definições aparentes; 0 marcadores asm.

Includes: `mnnamenew.h`, `inlines.h`, `mncharsel.h`, `mnmain.h`, `mnname.h`, `types.h`, `dolphin/gx/GXStruct.h`, `melee/gm/gm_1A3F.h`, `melee/gm/gmmain_lib.h`, `melee/gm/gmtoulib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `order_sdata`, `mnNameNew_8023B0F8`, `mnNameNew_8023B224`, `mnNameNew_8023B314`, `mnNameNew_SetKeyColor`, `mnNameNew_KeySetup`, `mnNameNew_8023BAA8`, `GetAutoNameCharacter`, `PickAutoNameInline`, `PickAutoName`, `NameContainsOnlySpaces`, `WriteCharactersForNameAtIndex`, `AddCharacterToName_getGlyphs`, `AddCharacterToName`, `mnNameNew_GlyphVariantInput`, `copyName`, `mnNameNew_CountVariants`, `IsNameEmpty`, `CanConfirmName`, `SubmitName`, `mnNameNew_MainInput`, `mnNameNew_GetEntryData`, `mnNameNew_8023CE4C`, `fn_8023CFC8`, `fn_8023D0F8`, `mnNameNew_8023D130`, `GlyphVariantCount`, `AnimateGlyphVariant`, `CreateGlyphVariant`, `mnNameNew_GlyphVariantSetup`, `mnNameNew_8023DA08`, `fn_8023DAEC`, `fn_8023DBE8`, `mnNameNew_8023E0D8`, `InitNameEntryUIState`, `mnNameNew_InitKeyJobjs`, `mnNameNew_8023E32C`, `mnNameNew_EnterFromMnName`, `mnNameNew_EnterFromMnCharSel`, `mnNameNew_8023EA08`

## `src/melee/mn/mnnamenew.h`

40 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `placeholder.h`, `melee/mn/types.h`

## `src/melee/mn/mnruleplus.c`

1054 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `mnruleplus.h`, `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `forward.h`, `inlines.h`, `mnmain.h`, `mnmainrule.h`, `mnstagesw.h`, `types.h`, `melee/gm/gm_1A3F.h`, `melee/gm/gmmain_lib.h`, `melee/gm/types.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `SisLib_ClearText`, `mnRulePlus_GetDescIdx`, `mnRulePlus_SaveRules`, `mnRulePlus_IsOptionVisible`, `fn_8023201C`, `mn_80232458`, `mnRulePlus_AnimTimeDigits`, `mnRulePlus_AnimZeros`, `mn_802324E4`, `mn_80232660`, `mn_802327A4_InitOptionRoots`, `mn_802327A4_UpdateOption`, `mn_802327A4`, `mn_80232D4C`, `fn_80232F44`, `mnRulePlus_CountAllVisible`, `mnRulePlus_CountVisibleBefore`, `mn_80233218`, `mn_802339FC`

## `src/melee/mn/mnruleplus.h`

62 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/mn/forward.h`, `sysdolphin/baselib/forward.h`, `melee/mn/types.h`

## `src/melee/mn/mnsnap.c`

2587 linhas; 47 definições aparentes; 0 marcadores asm.

Includes: `mnsnap.h`, `placeholder.h`, `inlines.h`, `mnmain.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbcardnew.h`, `melee/lb/lblanguage.h`, `melee/lb/lbsnap.h`, `sysdolphin/baselib/aobj.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnSnap_80253184`, `mnSnap_GetLoadIdx`, `mnSnap_GetThumbImage`, `mnSnap_GetDObj`, `mnSnap_GetThumbJObj`, `mnSnap_GetImageDesc`, `mnSnap_GetLoadPhotoIdx`, `mnSnap_8025329C`, `mnSnap_GetBlankImg`, `mnSnap_80253640`, `mnSnap_80253964`, `mnSnap_80253AE4`, `mnSnap_80253BE0`, `fn_80253DB4`, `fn_80253DE8`, `fn_80253E1C`, `fn_80253E5C`, `mnSnap_80253E90`, `mnSnap_80253F60`, `mnSnap_80254014`, `mnSnap_sdata2_order`, `mnSnap_8025409C`, `mnSnap_RefreshSlotSelection`, `mnSnap_ShowSubmenu`, `mnSnap_HideSubmenu`, `resetToSlotSelect`, `mnSnap_80254298`, `UNINITIALIZED_RETURN`, `mnSnap_InitDialogText`, `mnSnap_GetCursorIdx`, `mnSnap_GetMoveJObj`, `mnSnap_GetActivePhotoCount`, `mnSnap_GetCurrentThumbImage`, `mnSnap_AnimateCardSlots`, `mnSnap_UpdateSlotStatus`, `mnSnap_CheckCopy`, `mnSnap_UpdateSelectionCursor`, `mnSnap_ReadCardStatus`, `fn_802545C4`, `fn_80257D7C`, `mnSnap_LoadPageIndicator`, `mnSnap_GetCardStatus`, `mnSnap_InitPageText`, `mnSnap_GetMainJoint`, `mnSnap_GetMainShapeAnim`, `mnSnap_CreateThumbnails`, `mnSnap_80257F24`

## `src/melee/mn/mnsnap.h`

27 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/melee/mn/mnsound.c`

384 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `mnsound.h`, `melee/it/forward.h`, `inlines.h`, `mnmain.h`, `types.h`, `melee/gm/gm_1601.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lbarchive.h`, `melee/lb/lbcardgame.h`, `melee/sc/types.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `getVolumePosition`, `updateVolumeAnim`, `updateChannelAnim`, `updateCenterText`, `mnSound_802492CC`, `animateSelectedChannel`, `chooseVolumeAnim`, `fn_80249A1C`, `initUserData`, `mnSound_80249C08`, `mnSound_8024A09C`

## `src/melee/mn/mnsound.h`

11 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`

## `src/melee/mn/mnsoundtest.c`

867 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `mnsoundtest.h`, `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `forward.h`, `inlines.h`, `types.h`, `dolphin/os.h`, `melee/gm/gm_unsplit.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lbarchive.h`, `melee/lb/lbspdisplay.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnSoundTest_8024A790`, `mnSoundTest_8024A958`, `mnSoundTest_8024AA70`, `mnSoundTest_8024ABF8`, `mnSoundTest_8024AD58`, `fn_8024AED0_inline`, `fn_8024AED0_GetUserData`, `fn_8024AED0`, `mnSoundTest_GetInputs`, `mnSoundTest_GetAudioVolume`, `mnSoundTest_ToggleView`, `mnSoundTest_PlaySampleAnim`, `mnSoundTest_UpdateCategoryAnim`, `fn_8024B2B0`, `fn_8024B7E4`, `fn_8024B8B4`, `fn_8024BAF0`, `mnSoundTest_8024BCA0`, `mnSoundTest_8024BEE0`

## `src/melee/mn/mnsoundtest.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/mn/forward.h`, `sysdolphin/baselib/forward.h`

## `src/melee/mn/mnstagesel.c`

923 linhas; 22 definições aparentes; 0 marcadores asm.

Includes: `mnstagesel.h`, `placeholder.h`, `forward.h`, `inlines.h`, `mnmain.h`, `melee/gm/gm_unsplit.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_013B.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbdvd.h`, `melee/lb/lblanguage.h`, `melee/lb/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `order_sdata2`, `mnStageSel_802599EC`, `mnStageSel_80259C28`, `fn_80259D84`, `do_anim`, `mnStageSel_80259ED8`, `fn_8025A090`, `fn_8025A310`, `fn_8025A560`, `fn_8025A91C`, `fn_8025A974`, `make_stage_icon`, `attach_menu_model`, `make_bg_model`, `make_icon_root`, `get_jobj`, `mnStageSel_Scene_OnEnter`, `get_pad`, `mnStageSel_Scene_OnFrame`, `mnStageSel_Scene_OnExit`, `mnSelStageRandom`, `mnStageSel_8025BC08`

## `src/melee/mn/mnstagesel.h`

48 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `placeholder.h`, `melee/sc/types.h`

## `src/melee/mn/mnstagesw.c`

788 linhas; 20 definições aparentes; 0 marcadores asm.

Includes: `mnstagesw.h`, `inlines.h`, `mnmain.h`, `mnruleplus.h`, `melee/gm/gm_1601.h`, `melee/gm/gm_1A3F.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lbspdisplay.h`, `melee/sc/types.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnStageSw_8023593C`, `mnStageSw_802359C8`, `mnStageSw_80235C58`, `mnStageSw_80235DC8`, `mnStageSw_CountEnabled`, `saveSettings`, `fn_80235F80`, `mnStageSw_80236178`, `mnStageSw_802364A0_noinline`, `mnStageSw_802364A0`, `mnStageSw_80236548`, `mnStageSw_FinishEnter`, `mnStageSw_FreeTexts`, `fn_80236998`, `mnStageSw_SetCursorPosition`, `mnStageSw_InitUserData`, `mnStageSw_SetCursorAnim`, `mnStageSw_CreateCursor`, `mnStageSw_80236CBC`, `mnStageSw_80237410`

## `src/melee/mn/mnstagesw.h`

6 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/mn/mnvibration.c`

1126 linhas; 34 definições aparentes; 0 marcadores asm.

Includes: `mnvibration.h`, `dolphin/pad.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/jobj.h`, `inlines.h`, `mnmain.h`, `types.h`, `dolphin/os.h`, `melee/gm/gm_1A36.h`, `melee/gm/gmmain_lib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbspdisplay.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/sislib.h`

Definições aparentes: `mnVibration_JObjGetTranslationX`, `mnVibration_JObjGetTranslationY`, `mnVibration_JObjGetTranslationZ`, `mnVibration_JObjSetTranslateX`, `mnVibration_JObjSetTranslateY`, `mnVibration_JObjSetTranslateZ`, `mnVibration_GetNameSlot`, `mnVibration_GetNameSlotRaw`, `mnVibration_GetNameRumble`, `mnVibration_GetCursorRow`, `mnVibration_GetPreviousCursorRow`, `mnVibration_GetNextCursorRow`, `mnVibration_GetPortRumble`, `mnVibration_FreeNameTexts`, `mnVibration_GetNameRowJObj`, `mnVibration_GetCursorYSpacing`, `mnVibration_AnimatePortPanel`, `mnVibration_AnimateNameRow`, `setCursorTranslateX`, `setCursorTranslateY`, `setCursorTranslateZ`, `mnVibration_HandleInput`, `mnVibration_CursorThink`, `mnVibration_UpdatePortPanel`, `mnVibration_CreatePortPanels`, `mnVibration_CreateNameRow`, `mnVibration_RefreshNameRows`, `mnVibration_OnAnimComplete`, `mnVibration_GetPortChildAt`, `mnVibration_GetPadIndex`, `mnVibration_Think`, `mnVibration_IntroProc`, `mnVibration_CreateScreen`, `mnVibration_Init`

## `src/melee/mn/mnvibration.h`

34 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/melee/mn/types.h`

737 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/gm/forward.h`, `melee/mn/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`

