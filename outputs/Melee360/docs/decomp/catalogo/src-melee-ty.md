# Catálogo: src/melee/ty

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/melee/ty/forward.h`

61 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/ty/inlines.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/ty/toy.c`

6512 linhas; 116 definições aparentes; 0 marcadores asm.

Includes: `toy.h`, `Runtime/platform.h`, `melee/if/forward.h`, `math.h`, `placeholder.h`, `stddef.h`, `string.h`, `tylist.h`, `types.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `dolphin/os.h`, `melee/db/db.h`, `melee/gm/gm_1601.h`, `melee/gm/gm_16F1.h`, `melee/gm/gm_1A3F.h`, `melee/gm/gmmain_lib.h`, `melee/gm/gmscene.h`, `melee/gm/gmvs.h`, `melee/if/textdraw.h`, `melee/if/textlib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00CE.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/lb/lbvector.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `melee/sc/types.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/sobjlib.h`, `sysdolphin/baselib/state.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `un_80304470`, `un_80304510`, `un_803045A0`, `un_80304690`, `un_80304780`, `order_sdata2_0`, `order_sdata2_38`, `order_sdata2_148`, `order_sdata2_154`, `order_sdata_8`, `order_data_144`, `Toy_GetTrophyTotal`, `_Toy_GetTrophyTotal`, `getTrophyFlags`, `Toy_803048C0`, `Toy_80304924`, `Toy_80304988`, `Toy_803049F4`, `Toy_80304A58`, `Toy_80304B0C`, `Toy_80304B94`, `Toy_80304CC8`, `_Toy_80304CC8_noinline`, `_Toy_80304D30`, `Toy_80305058`, `_Toy_803053C4`, `Toy_SetUnlockState`, `Toy_80305918`, `Toy_80305B88`, `Toy_80305C44`, `Toy_80305D00`, `Toy_80305DB0`, `HSD_PadGetNmlSubStickX`, `Toy_80305EB4`, `Toy_80305FB8`, `Toy_803060BC`, `Toy_803062BC`, `_Toy_803062EC`, `getViewDatFilename`, `getDataiDatFilename`, `getInfoDatFilename`, `getBgDatFilename`, `Toy_803063D4`, `_Toy_803064B8`, `_Toy_8030663C`, `Toy_803067BC`, `Toy_803068E0`, `Toy_80306930`, `Toy_80306954`, `_Toy_80306A0C`, `Toy_80306A48`, `Toy_80306B18`, `Toy_80306BB8`, `_Toy_80306C5C`, `Toy_RemoveUserData`, `Toy_80306D14`, `Toy_80306D70`, `Toy_LoadLObjList`, `order_data_670`, `_Toy_80307018`, `order_data_6C4`, `_Toy_8030715C`, `Toy_AddPanelAnims`, `Toy_80307470`, `_Toy_803075E8`, `_Toy_80307828`, `_Toy_803078E4`, `_Toy_80307BA0`, `Toy_80307E84`, `_Toy_80307F64`, `Toy_8030813C`, `setupTrophyEntry`, `Toy_80308250`, `Toy_803082F8`, `Toy_80308328`, `Toy_80308354`, `Toy_803083D8`, `_Toy_803084A0`, `Toy_803087F4`, `order_data_6F4`, `_Toy_80308DC8`, `_Toy_80308F04`, `_Toy_80309338`, `_Toy_ReadTrigger`, `_Toy_80309404`, `_Toy_8030B530`, `_Toy_8030E110`, `_Toy_8030FA50`, `_Toy_8030FE48_init_sort_key`, `_Toy_8030FE48_link_entries`, `_Toy_8030FE48`, `_Toy_803102C4`, `order_data_9AC`, `Toy_803102D0`, `toy_toggle_flag`, `toy_make_gobj`, `toy_sobj_loop`, `Toy_80310324`, `Toy_80310660`, `_Toy_803109A0`, `_Toy_80310B48`, `showDevText`, `_Toy_803114E8`, `Toy_80311680`, `_Toy_80311788`, `Toy_80311960`, `Toy_Scene_OnEnter`, `_Toy_80311F5C`, `Toy_Scene_OnFrame`, `_Toy_80312050`, `Toy_Mode_OnInit`, `Toy_8031234C`, `loadTrophyMetadata`, `Toy_803124BC`, `Toy_8031263C`, `Toy_803127D4`

## `src/melee/ty/toy.h`

81 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/sc/forward.h`, `sysdolphin/baselib/forward.h`, `melee/ty/types.h`

## `src/melee/ty/tydisplay.c`

2527 linhas; 45 definições aparentes; 0 marcadores asm.

Includes: `tydisplay.h`, `Runtime/platform.h`, `math.h`, `placeholder.h`, `stddef.h`, `forward.h`, `toy.h`, `types.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `dolphin/os.h`, `melee/db/db.h`, `melee/gm/gmscene.h`, `melee/if/textdraw.h`, `melee/if/textlib.h`, `melee/if/types.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00CE.h`, `melee/lb/lbarchive.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/lb/lbvector.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `melee/sc/types.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `order_data_0`, `order_data_44`, `_tyDisplay_8031830C`, `order_sdata2_0`, `_tyDisplay_80318714`, `_tyDisplay_80318B1C`, `tyDisplay_GetGridSortElem`, `_tyDisplay_80319540_sort`, `_tyDisplay_80319994_sort`, `_tyDisplay_80318CB4_sort`, `_tyDisplay_80319994_sort_pos`, `_tyDisplay_80318CB4_sort_pos`, `_tyDisplay_80318CB4_calc_dist_sq`, `_tyDisplay_80318CB4_place_toys`, `_tyDisplay_80318CB4_sqrt_store`, `_tyDisplay_80318CB4`, `_tyDisplay_80319540`, `_tyDisplay_80319994`, `_tyDisplay_80319EF0`, `order_data_A8`, `_tyDisplay_8031A4EC`, `_tyDisplay_8031A94C`, `_tyDisplay_8031B1FC`, `order_data_110`, `_tyDisplay_8031B328`, `tyDisplay_SetGridSize`, `tyDisplay_Scene_OnEnter`, `_tyDisplay_8031B850`, `tyDisplay_Scene_OnFrame`, `tyDisplay_8031B9DC`, `_tyDisplay_8031BA78`, `tyDisplay_8031BB34`, `tyDisplay_8031BB94`, `_tyDisplay_8031BBF4`, `_tyDisplay_8031BC54`, `un_8031BF34_inline`, `_tyDisplay_8031BF34`, `_tyDisplay_8031C1D0`, `tyDisplay_8031C2CC`, `tyDisplay_8031C2EC`, `tyDisplay_8031C354`, `tyDisplay_8031C454`, `un_8031C5E4_inline`, `tyDisplay_8031C5E4`, `tyDisplay_8031C8B8`

## `src/melee/ty/tydisplay.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ty/forward.h`, `sysdolphin/baselib/forward.h`

## `src/melee/ty/tyfigupon.c`

1578 linhas; 36 definições aparentes; 0 marcadores asm.

Includes: `tyfigupon.h`, `Runtime/platform.h`, `placeholder.h`, `stddef.h`, `inlines.h`, `toy.h`, `types.h`, `dolphin/mtx.h`, `dolphin/os.h`, `melee/gm/gm_1601.h`, `melee/gm/gmscene.h`, `melee/if/types.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcardgame.h`, `melee/lb/lblanguage.h`, `melee/lb/lbspdisplay.h`, `melee/lb/lbvector.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `melee/sc/types.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `order_data_0`, `order_sdata2_0`, `_tyFigupon_80314AA8`, `_tyFigupon_80314B54`, `_tyFigupon_80314BE4`, `_tyFigupon_80314C5C`, `_tyFigupon_803152BC`, `_tyFigupon_803153EC`, `_tyFigupon_80315574`, `tyFigupon_CountRemaining`, `tyFigupon_UpdateRemainingCount`, `tyFigupon_GetTotalCount`, `setupPercentDisplay`, `setupBetAnim`, `_tyFigupon_803155C8`, `order_data_108`, `tyFigupon_GetCoinCount`, `tyFigupon_CreateCoin`, `tyFigupon_StoreDigits`, `tyFigupon_GetBetCount`, `tyFigupon_FinishCoinDrop`, `_tyFigupon_80315C44`, `_tyFigupon_80316170`, `_tyFigupon_8031638C`, `_tyFigupon_80316420`, `_tyFigupon_803168DC`, `_tyFigupon_80316BF8`, `_tyFigupon_80316C24`, `_tyFigupon_8031753C`, `order_data_4A8`, `_tyFigupon_80317A60`, `tyFigupon_GetED4`, `tyFigupon_InitScene`, `tyFigupon_Scene_OnEnter`, `_tyFigupon_803181BC`, `tyFigupon_Scene_OnFrame`

## `src/melee/ty/tyfigupon.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `placeholder.h`

## `src/melee/ty/tylist.c`

1080 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `tylist.h`, `Runtime/platform.h`, `placeholder.h`, `toy.h`, `types.h`, `dolphin/mtx.h`, `dolphin/os.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_0146.h`, `melee/lb/lbspdisplay.h`, `melee/mn/inlines.h`, `melee/mn/mnmain.h`, `sysdolphin/baselib/archive.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/mobj.h`, `sysdolphin/baselib/sislib.h`, `sysdolphin/baselib/sislib_font.h`, `sysdolphin/baselib/tobj.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `order_data_0`, `_tyList_80312834`, `_tyList_80312904`, `_tyList_80312BAC`, `_tyList_80312E88`, `_tyList_8031305C`, `_tyList_80313358`, `_tyList_80313464`, `_tyList_80313508`, `_tyList_80313774`, `get_repeat_count`, `tyList_80313BD8_inline`, `_tyList_80313BD8`, `_tyList_8031438C`, `_tyList_80314504`, `_tyList_8031457C`, `tyList_803147C4`, `_tyList_803148E4`

## `src/melee/ty/tylist.h`

6 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/ty/types.h`

603 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ty/forward.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `dolphin/gx/GXStruct.h`, `dolphin/mtx.h`

