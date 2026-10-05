# Catálogo: src/melee/mp

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/melee/mp/forward.h`

122 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/lb/forward.h`

## `src/melee/mp/mpcoll.c`

4552 linhas; 124 definições aparentes; 0 marcadores asm.

Includes: `mpcoll.h`, `Runtime/platform.h`, `melee/ft/kinds/ftCommon/forward.h`, `math.h`, `placeholder.h`, `stdbool.h`, `forward.h`, `mplib.h`, `melee/db/db.h`, `melee/ft/ftlib.h`, `melee/gr/grdynamicattr.h`, `melee/it/it_26B1.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `melee/lb/types.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `sdata2_order`, `mpColl_80041C78`, `mpCollPrev`, `clamp_above`, `clamp_below`, `mpCollCheckBounding`, `mpColl_80041EE4`, `mpColl_SetECBSource_JObj`, `mpColl_SetECBSource_Fixed`, `mpColl_SetLedgeSnap`, `mpColl_80042384`, `update_min_max`, `mpColl_LoadECB_JObj`, `update_min_max_2`, `clamp_above_2`, `clamp_below_2`, `mpColl_LoadECB_Fixed`, `mpColl_80042C58`, `mpColl_LoadECB_inline`, `mpColl_LoadECB`, `Vec2_Interpolate`, `mpCollInterpolateECB`, `mpColl_RightWall_inline`, `mpColl_LeftWall_inline`, `mpColl_LeftWall_inline3`, `mpColl_80043268`, `mpCollEnd_inline2`, `mpCollEnd_inline`, `mpCollEnd`, `mpColl_80043558`, `mpColl_80043670`, `mpColl_80043680`, `mpCollSetFacingDir`, `mpColl_800436E4`, `max_inline`, `mpColl_80043754`, `mpColl_800439FC`, `mpColl_80043ADC`, `mpColl_80043BBC`, `mpColl_80043C6C`, `mpColl_80043E90`, `mpColl_80043F40`, `mpColl_80044164`, `mpColl_800443C4`, `mpColl_80044628_Floor`, `mpColl_80044838_Floor`, `mpColl_80044948_Floor`, `mpColl_80044AD8_Ceiling`, `mpColl_80044C74_Ceiling`, `mpColl_RightWall_inline2`, `mpColl_80044E10_RightWall`, `mpColl_800454A4_RightWall`, `mpColl_LeftWall_inline2`, `mpColl_80045B74_LeftWall`, `mpColl_80046224_LeftWall`, `mpCollCeilingInline`, `floorWallHug`, `mpCollFloorInline`, `mpColl_80046904`, `mpColl_80046F78_inline`, `mpColl_80046F78`, `inline0`, `inline4`, `inline2`, `inline3`, `inline1`, `mpColl_800471F8`, `mpColl_8004730C`, `mpColl_800473CC`, `mpColl_800474E0`, `mpColl_800475F4`, `mpColl_800476B4`, `mpColl_800477E0`, `mpColl_800478F4`, `mpColl_80047A08`, `mpColl_80047AC8`, `mpColl_80047BF4`, `mpColl_80047D20`, `mpColl_80047E14`, `mpColl_80047F40`, `mpColl_8004806C`, `mpColl_80048160`, `mpColl_80048274`, `mpColl_80048388`, `mpColl_80048464`, `mpColl_80048578`, `mpColl_80048654`, `mpColl_80048768`, `mpColl_80048844`, `mpColl_800488F4`, `mpColl_80048AB0_RightWall`, `mpColl_800491C8_RightWall`, `mpColl_80049778_LeftWall`, `mpColl_80049EAC_LeftWall`, `mpColl_8004A45C_Floor`, `mpColl_8004A678_Floor`, `mpColl_8004A908_Floor`, `mpColl_8004AB80`, `mpColl_8004ACE4`, `mpColl_8004B108`, `mpColl_8004B21C`, `mpColl_8004B2DC`, `mpColl_8004B3F0`, `mpColl_8004B4B0`, `mpColl_8004B5C4`, `mpColl_8004B6D8`, `mpColl_8004B894_RightWall`, `mpColl_8004BDD4_LeftWall`, `mpColl_8004C328_Ceiling`, `mpColl_8004C534`, `mpColl_8004C750`, `mpCollSqueezeHorizontal`, `mpCollSqueezeVertical`, `mpColl_8004CA6C`, `mpCollGetSpeedCeiling`, `mpCollGetSpeedLeftWall`, `mpCollGetSpeedRightWall`, `mpCollGetSpeedFloor`, `mpColl_IsOnPlatform`, `mpUpdateFloorSkip`, `mpClearFloorSkip`, `mpCopyCollData`, `prepareColl`, `mpColl_8004D024`

## `src/melee/mp/mpcoll.h`

131 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/ft/kinds/ftCommon/forward.h`, `melee/mp/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`

## `src/melee/mp/mpisland.c`

629 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `mpisland.h`, `placeholder.h`, `mplib.h`, `types.h`, `melee/lb/lb_00B0.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/memory.h`

Definições aparentes: `mpIsland_8005A6F8`, `mpIsland_AssertSeg`, `mpIsland_8005A728`, `mpIsland_8005AB54`, `mpIsland_8005AC14`, `mpIsland_8005AC8C`, `mpIsland_8005ACE8`, `mpIsland_8005AE1C`, `mpIsland_8005B004`, `mpIsland_8005B334`

## `src/melee/mp/mpisland.h`

24 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/mp/forward.h`, `dolphin/mtx.h`, `melee/mp/types.h`

## `src/melee/mp/mplib.c`

7163 linhas; 141 definições aparentes; 0 marcadores asm.

Includes: `mplib.h`, `Runtime/platform.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `math.h`, `placeholder.h`, `stdbool.h`, `stddef.h`, `forward.h`, `mpcoll.h`, `mpisland.h`, `types.h`, `dolphin/gx/GXGeometry.h`, `dolphin/gx/GXStruct.h`, `dolphin/gx/GXVert.h`, `dolphin/mtx.h`, `dolphin/types.h`, `melee/cm/camera.h`, `melee/cm/types.h`, `melee/db/db.h`, `melee/ft/ftlib.h`, `melee/gr/grdynamicattr.h`, `melee/gr/ground.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/itCharItems.h`, `melee/lb/types.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/tev.h`, `sysdolphin/baselib/texp.h`

Definições aparentes: `mpLib_8004D164`, `mpGetGroundCollVtx`, `mpGetGroundCollLine`, `mpGetGroundCollJoint`, `mpPruneEmptyLines`, `mpLibLoad`, `mpLineGetNext`, `mpLineGetPrev`, `mpRemap2d`, `mpLib_8004DD90_Floor`, `mpLib_8004E090_Ceiling`, `mpLib_8004E398_LeftWall`, `mpLib_8004E684_RightWall`, `mpLineIntersection`, `mpLineIntersectionH`, `mpLineGetCollLine`, `mpLib_8004ED5C`, `mpCheckFloor`, `mpCheckFloorRemap`, `mpCheckCeiling`, `mpCheckCeilingRemap`, `mpLineIntersectionV`, `mpCheckLeftWall`, `mpCheckLeftWallRemap`, `mpCheckRightWall`, `mpCheckRightWallRemap`, `mpLib_800511A4_RightWall`, `mpLib_800515A0_LeftWall`, `mpLib_8005199C_Floor`, `mpLib_80051BA8_Floor`, `mpCheckMultiple`, `mpCheckAllRemap`, `mpCheckAll`, `mpLineGetNextCheckInline`, `mpLineGetPrevCheckInline`, `mpLineGetPrevCheckInlineVtx`, `mpLineGetNextCheckInlineVtx`, `mpLineIterNonResult`, `mpLineNextNonFloor`, `mpLinePrevNonFloor`, `mpLinePrevNonCeiling`, `mpLineNextNonCeiling`, `mpLineNextNonLeftWall`, `mpLinePrevNonLeftWall`, `mpLinePrevNonRightWall`, `mpLineNextNonRightWall`, `mpLineWalkNon`, `mpLib_80053394_Floor`, `mpLib_80053448_Floor`, `mpLineGetNextInline`, `mpLineGetNextCachedInline`, `mpLineGetNextCheckResultFirst`, `mpLib_800534FC_Floor`, `mpLineGetPrevInline`, `mpLineGetPrevCheckResultFirst`, `mpLib_800536CC_Floor`, `mpLib_8005389C_Ceiling`, `mpLib_80053950_Ceiling`, `mpLib_80053A04_Ceiling`, `mpLib_80053BD4_Ceiling`, `mpLib_80053DA4_Floor`, `mpLib_80053ECC_Floor`, `mpLineGetKindInline`, `mpFloorGetRight`, `mpFloorGetLeft`, `mpCeilingGetRight`, `mpCeilingGetLeft`, `mpLeftWallGetTop`, `mpLeftWallGetBottom`, `mpRightWallGetTop`, `mpRightWallGetBottom`, `mpLineGetV1Pos`, `mpLineGetV0Pos`, `mpLineGetKind`, `mpLineGetFlags`, `mpLib_80054D68`, `mpLineGetNormal`, `mpLib_80054ED8`, `mpLineGetNextFrom`, `mpLineGetPrevFrom`, `mpLinesConnected`, `mpLib_800552B0`, `mpJointHide`, `mpJointUnhide`, `mpJointUpdateDynamics`, `mpLib_80055E24`, `mpLib_80055E9C`, `mpJointUpdateBounding`, `mpLib_8005667C`, `mpVtxGetPos`, `mpVtxSetPos`, `mpLineSetPos`, `mpLib_80056758`, `mpGetSpeed`, `mpLib_800569EC`, `mpLib_80056A1C`, `mpLib_80056A54`, `mpLib_80056A8C`, `mpLib_80056AC4`, `mpLib_80056AFC`, `mpLib_80056B34`, `sqrtf_store`, `mpJointFromLine`, `mpLib_80056C54`, `mpLib_80057424`, `mpLib_80057528`, `mpLib_800575B0`, `mpJointListAdd`, `mpJointListUnlink`, `mpLib_80057BC0`, `mpLib_80057FDC`, `mpLib_80058044`, `mpJointSetB10`, `mpJointSetCb1`, `mpJointClearCb1`, `mpJointGetCb1`, `mpLib_8005811C`, `mpJointSetCb2`, `mpJointGetCb2`, `mpLib_GetJointVtxRange`, `mpLib_800581DC`, `mpLib_80058560`, `mpLib_80058614_Floor`, `mpLib_800587FC`, `mpLib_80058820`, `mpCheckedBounding`, `mpBoundingCheck`, `mpBoundingCheck2`, `mpBoundingCheck3`, `mpUncheckBounding`, `mpLib_SetupDraw`, `mpLib_DrawEcbs`, `mpLib_CopyColor`, `mpLib_DrawSnapping`, `UNINITIALIZED`, `mpLib_80059554`, `mpLib_80059E60`, `mpLib_DrawCrosses`, `mpLib_DrawSpecialPoints`, `mpLib_8005A2DC`, `mpLib_DrawZones`

## `src/melee/mp/mplib.h`

223 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx/GXStruct.h`, `dolphin/mtx.h`, `melee/mp/types.h`

## `src/melee/mp/types.h`

142 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/gr/forward.h`, `melee/mp/forward.h`, `dolphin/gx/GXStruct.h`, `dolphin/mtx.h`

