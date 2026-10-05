/* Generated XDK C constant-expression adapter. Source SHA256: 8FF8FA7CEFFBF23F5D28B8C034EA5B9331001E7A7FA1E10877A54BF8E8D4E92E */
#ifndef MELEE_FT_CHARA_FTFOX_FORWARD_H
#define MELEE_FT_CHARA_FTFOX_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

typedef struct ftFox_DatAttrs ftFox_DatAttrs;

#define ftFx_MF_Appeal ((MotionFlags) (Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_SkipAnimVel | Ft_MF_Unk06))

#define ftFx_MF_Special ((MotionFlags) (Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState))

#define ftFx_MF_SpecialN ((MotionFlags) (ftFx_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException))

#define ftFx_MF_SpecialS ((MotionFlags) (ftFx_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx))

#define ftFx_MF_SpecialHi ((MotionFlags) (ftFx_MF_SpecialS | Ft_MF_KeepFastFall))

#define ftFx_MF_SpecialAirN ((MotionFlags) (ftFx_MF_SpecialN | Ft_MF_SkipParasol))

#define ftFx_MF_SpecialAirS ((MotionFlags) (ftFx_MF_SpecialS | Ft_MF_SkipParasol))

#define ftFx_MF_SpecialAirHiHold ((MotionFlags) (ftFx_MF_SpecialHi | Ft_MF_SkipParasol))

#define ftFx_MF_SpecialLw ((MotionFlags) (ftFx_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipColAnim))

#define ftFx_MF_SpecialAirLw ((MotionFlags) (ftFx_MF_SpecialLw | Ft_MF_SkipParasol))

#define ftFx_MF_SpecialNLoop ((MotionFlags) (ftFx_MF_SpecialN | Ft_MF_Unk19))

#define ftFx_MF_SpecialAirNLoop ((MotionFlags) (ftFx_MF_SpecialNLoop | Ft_MF_SkipParasol))

#define ftFx_MF_SpecialLwLoop ((MotionFlags) (ftFx_MF_SpecialLw | Ft_MF_Unk19))

#define ftFx_MF_SpecialAirLwLoop ((MotionFlags) (ftFx_MF_SpecialLwLoop | Ft_MF_SkipParasol))

typedef enum ftFox_MotionState {
    ftFx_MS_SpecialNStart = ftCo_MS_Count,
    ftFx_MS_SpecialNLoop,
    ftFx_MS_SpecialNEnd,
    ftFx_MS_SpecialAirNStart,
    ftFx_MS_SpecialAirNLoop,
    ftFx_MS_SpecialAirNEnd,
    ftFx_MS_SpecialSStart,
    ftFx_MS_SpecialS,
    ftFx_MS_SpecialSEnd,
    ftFx_MS_SpecialAirSStart,
    ftFx_MS_SpecialAirS,
    ftFx_MS_SpecialAirSEnd,
    ftFx_MS_SpecialHiHold,
    ftFx_MS_SpecialHiHoldAir,
    ftFx_MS_SpecialHi,
    ftFx_MS_SpecialAirHi,
    ftFx_MS_SpecialHiLanding,
    ftFx_MS_SpecialHiFall,
    ftFx_MS_SpecialHiBound,
    ftFx_MS_SpecialLwStart,
    ftFx_MS_SpecialLwLoop,
    ftFx_MS_SpecialLwHit,
    ftFx_MS_SpecialLwEnd,
    ftFx_MS_SpecialLwTurn,
    ftFx_MS_SpecialAirLwStart,
    ftFx_MS_SpecialAirLwLoop,
    ftFx_MS_SpecialAirLwHit,
    ftFx_MS_SpecialAirLwEnd,
    ftFx_MS_SpecialAirLwTurn,
    ftFx_MS_AppealSStartR,
    ftFx_MS_AppealSStartL,
    ftFx_MS_AppealSR,
    ftFx_MS_AppealSL,
    ftFx_MS_AppealSEndR,
    ftFx_MS_AppealSEndL,
    ftFx_MS_Count,
    ftFx_MS_SelfCount = ftFx_MS_Count - ftCo_MS_Count,
} ftFox_MotionState;

typedef enum ftFx_Submotion {
    ftFx_SM_SpecialNStart = ftCo_SM_Count,
    ftFx_SM_SpecialNLoop,
    ftFx_SM_SpecialNEnd,
    ftFx_SM_SpecialAirNStart,
    ftFx_SM_SpecialAirNLoop,
    ftFx_SM_SpecialAirNEnd,
    ftFx_SM_SpecialSStart,
    ftFx_SM_SpecialS,
    ftFx_SM_SpecialSEnd,
    ftFx_SM_SpecialAirSStart,
    ftFx_SM_SpecialAirS,
    ftFx_SM_SpecialAirSEnd,
    ftFx_SM_SpecialHiHold,
    ftFx_SM_SpecialHiHoldAir,
    ftFx_SM_SpecialHi,
    ftFx_SM_SpecialHiLanding,
    ftFx_SM_SpecialHiFall,
    ftFx_SM_SpecialHiBound,
    ftFx_SM_SpecialLwStart,
    ftFx_SM_SpecialLwLoop,
    ftFx_SM_SpecialLwHit,
    ftFx_SM_SpecialLwEnd,
    ftFx_SM_SpecialAirLwStart,
    ftFx_SM_SpecialAirLwLoop,
    ftFx_SM_SpecialAirLwHit,
    ftFx_SM_SpecialAirLwEnd,
    ftFx_SM_AppealSStartR,
    ftFx_SM_AppealSStartL,
    ftFx_SM_AppealSR,
    ftFx_SM_AppealSL,
    ftFx_SM_AppealSEndR,
    ftFx_SM_AppealSEndL,
    ftFx_SM_Count,
    ftFx_SM_SelfCount = ftFx_SM_Count - ftCo_SM_Count,
} ftFx_Submotion;

typedef enum ftFx_SpecialNIndex {
    // msid = currASID - ftFx_MS_SpecialNStart;
    ftFx_SpecialNIndex_Start,
    ftFx_SpecialNIndex_Loop,
    ftFx_SpecialNIndex_End,
    ftFx_SpecialNIndex_AirStart,
    ftFx_SpecialNIndex_AirLoop,
    ftFx_SpecialNIndex_AirEnd,
    // msid = currASID - ftCo_MS_CatchDash;
    ftFx_SpecialNIndex_ThrowB,
    ftFx_SpecialNIndex_ThrowHi,
    ftFx_SpecialNIndex_ThrowLw,
    // ftFx_SpecialNIndex_None,
} ftFx_SpecialNIndex;

#endif
