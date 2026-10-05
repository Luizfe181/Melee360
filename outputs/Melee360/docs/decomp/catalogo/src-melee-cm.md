# Catálogo: src/melee/cm

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/melee/cm/camera.c`

4588 linhas; 163 definições aparentes; 0 marcadores asm.

Includes: `camera.h`, `Runtime/platform.h`, `melee/ft/forward.h`, `sysdolphin/baselib/forward.h`, `math.h`, `placeholder.h`, `forward.h`, `types.h`, `dolphin/mtx.h`, `dolphin/pad.h`, `dolphin/types.h`, `melee/ft/ftlib.h`, `melee/gm/gm_unsplit.h`, `melee/gr/grcastle.h`, `melee/gr/grcorneria.h`, `melee/gr/grgarden.h`, `melee/gr/grhomerun.h`, `melee/gr/grkinokoroute.h`, `melee/gr/grlib.h`, `melee/gr/ground.h`, `melee/gr/grzebes.h`, `melee/gr/stage.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbrefract.h`, `melee/lb/lbshadow.h`, `melee/lb/lbspdisplay.h`, `melee/lb/lbvector.h`, `melee/mp/mplib.h`, `melee/pl/player.h`, `sysdolphin/baselib/cobj.h`, `sysdolphin/baselib/controller.h`, `sysdolphin/baselib/displayfunc.h`, `sysdolphin/baselib/fog.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/lobj.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/random.h`, `sysdolphin/baselib/wobj.h`

Definições aparentes: `camera_sdata2_order`, `vec_len`, `Camera_Init`, `Camera_80028F5C`, `Camera_80029020`, `Camera_80029044`, `Camera_800290D4`, `Camera_80029124`, `cam_bound`, `Camera_8002928C`, `Camera_800293E0`, `Camera_8002958C`, `get_follow_speed`, `get_delta`, `Camera_80029AAC`, `Camera_80029BC4`, `Camera_80029C88`, `get_y_bias`, `Camera_80029CF8`, `Camera_ApplyQuake`, `Camera_SetQuakeOffset`, `Camera_UpdateQuakes`, `get_stage_floor_height`, `Camera_8002A4AC`, `Camera_8002A768`, `Camera_8002AF68`, `Camera_8002B0E0`, `Camera_8002B1F8`, `fighter_z_out_of_range`, `update_zoom_distance`, `update_transform`, `update_avg_bounds_width`, `update_bounds`, `Camera_8002B3D4`, `get_slot_pad`, `get_stick_x`, `get_stick_y`, `get_substick_x`, `get_substick_y`, `Camera_8002B694`, `Camera_8002BA00`, `Camera_8002BAA8`, `OrthonormalizeBasis`, `Camera_8002BC78`, `Camera_8002BD88`, `Camera_8002C010`, `Camera_8002C1A8_inline`, `getPauseScale`, `Camera_8002C1A8`, `eye_offset_len`, `Camera_8002C5B4`, `get_subject_pos`, `get_target_interest`, `track_subject`, `Camera_8002C908`, `absf`, `Camera_8002CB0C`, `Camera_8002CDDC`, `compute_orbit_distance`, `get_subject_x1C`, `Camera_8002D318`, `Camera_8002D85C`, `set_bounds_z`, `smooth_fixed_camera_interest`, `Camera_8002DDC4`, `Camera_8002DFE4`, `Camera_8002E158`, `Camera_8002E234`, `getX378`, `Camera_8002E490`, `Camera_8002E6FC`, `Camera_8002E818`, `Camera_8002E948`, `Camera_8002EA64`, `Camera_8002EB5C`, `Camera_8002EC7C`, `Camera_8002ED9C`, `Camera_8002EEC8`, `Camera_8002EF14`, `Camera_8002F0E4`, `Camera_8002F260`, `Camera_8002F274`, `fn_8002F360`, `getCameraGObj`, `Camera_8002F3AC`, `Camera_SetModeToStandard`, `Camera_SetBounds`, `Camera_SetUpPauseCamera`, `Camera_SetUpPauseCameraWithDefaultZoom`, `Camera_8002F760`, `Camera_8002F784`, `Camera_8002F7AC`, `Camera_SetModeToFixed`, `fn_8002F908`, `Camera_8002F9E4`, `fn_8002FBA0`, `Camera_8002FC7C`, `Camera_8002FE38`, `Camera_8002FEEC`, `Camera_8003006C`, `Camera_800300F0`, `Camera_8003010C`, `Camera_80030130`, `Camera_80030154`, `Camera_80030178`, `Camera_8003019C`, `gxlink_prio8`, `gxlink_prio1`, `gxlink_prio80`, `render_gxlink_pass`, `fn_800301D0`, `Camera_800304E0`, `Camera_Create`, `Camera_80030730`, `Camera_SetBackgroundColor`, `Camera_GetBackgroundColor`, `Camera_GetTransformPosition`, `Camera_GetTransformInterest`, `project_ground_x`, `same_side`, `Camera_800307D0`, `Camera_80030A50`, `Camera_80030A60`, `Camera_80030A78`, `Camera_80030A8C`, `Camera_SetStageVisible`, `Camera_80030AC4`, `Camera_80030AE0`, `Camera_80030AF8`, `Camera_80030B0C`, `Camera_80030B24`, `Camera_80030B38`, `Camera_80030B50`, `Camera_80030B64`, `Camera_80030B7C`, `Camera_80030B90`, `Camera_80030BA8`, `Camera_80030BBC`, `Camera_80030CD8`, `Camera_80030CFC`, `Camera_80030DE4`, `Camera_80030DF8`, `Camera_80030E10`, `Camera_SetQuakeScale`, `Camera_RequestQuake`, `Camera_StopQuake`, `Camera_80031060`, `Camera_80031074`, `Camera_8003108C`, `Camera_800310A0`, `Camera_800310B8`, `Camera_800310E8`, `Camera_80031144`, `Camera_80031154`, `Camera_8003118C`, `Camera_800311CC`, `Camera_800311DC`, `inline_cam_gx_b0`, `inline_cam_gx_b1`, `inline_cam_gx_b4`, `Camera_800311EC`, `Camera_80031328`, `Camera_800313E0`

## `src/melee/cm/camera.h`

168 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/cm/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx/GXStruct.h`, `dolphin/mtx.h`, `sysdolphin/baselib/cobj.h`

## `src/melee/cm/cmsnap.c`

58 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `cmsnap.h`, `forward.h`, `melee/lb/lbspdisplay.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/tobj.h`

Definições aparentes: `cmSnap_800315C8`, `cmSnap_80031618`, `cmSnap_80031640`, `cmSnap_800316B4`

## `src/melee/cm/cmsnap.h`

14 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/forward.h`, `sysdolphin/baselib/gobj.h`

## `src/melee/cm/forward.h`

68 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/cm/types.h`

312 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/cm/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx/GXStruct.h`, `dolphin/mtx.h`

