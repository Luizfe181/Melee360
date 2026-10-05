/* Generated XDK C constant-expression adapter. Source SHA256: 446222A22507E4225DA69CF63C6E745689CB64E86BCB6C967499B4F938E22871 */
#ifndef MELEE_FT_CHARA_FTSAMUS_FORWARD_H
#define MELEE_FT_CHARA_FTSAMUS_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

typedef struct Fighter ftSs_Fighter;

#define ftSs_MF_Special ((MotionFlags) (Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState))

#define ftSs_MF_SpecialN ((MotionFlags) (ftSs_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException))

#define ftSs_MF_SpecialS ((MotionFlags) (ftSs_MF_Special | Ft_MF_KeepGfx | Ft_MF_SkipThrowException))

#define ftSs_MF_SpecialLw ((MotionFlags) (ftSs_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipThrowException))

#define ftSs_MF_SpecialHi ((MotionFlags) (ftSs_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_KeepSfx))

#define ftSs_MF_SpecialAirN ((MotionFlags) (ftSs_MF_SpecialN | Ft_MF_SkipParasol))

#define ftSs_MF_SpecialAirS ((MotionFlags) (ftSs_MF_SpecialS | Ft_MF_SkipParasol))

#define ftSs_MF_SpecialAirLw ((MotionFlags) (ftSs_MF_SpecialLw | Ft_MF_SkipParasol))

#define ftSs_MF_SpecialAirHi ((MotionFlags) (ftSs_MF_SpecialHi | Ft_MF_SkipParasol))

#define ftSs_MF_SpecialSSmash ((MotionFlags) (ftSs_MF_SpecialS | Ft_MF_SkipRumble))

#define ftSs_MF_SpecialAirSSmash ((MotionFlags) (ftSs_MF_SpecialSSmash | Ft_MF_SkipParasol))

#define ftSs_MF_ZairCatch ((MotionFlags) (Ft_MF_SkipModelPartVis | Ft_MF_SkipMetalB))

typedef enum ftSamus_MotionState {
    ftSs_MS_SpecialLw = ftCo_MS_Count,
    ftSs_MS_SpecialAirLw,
    ftSs_MS_SpecialNStart,
    ftSs_MS_SpecialNHold,
    ftSs_MS_SpecialNCancel,
    ftSs_MS_SpecialN,
    ftSs_MS_SpecialAirNStart,
    ftSs_MS_SpecialAirN,
    ftSs_MS_SpecialS,
    ftSs_MS_SpecialSSmash,
    ftSs_MS_SpecialAirS,
    ftSs_MS_SpecialAirSSmash,
    ftSs_MS_SpecialHi,
    ftSs_MS_SpecialAirHi,
    ftSs_MS_SpecialLwBomb,
    ftSs_MS_SpecialAirLwBomb,
    ftSs_MS_AirCatch,
    ftSs_MS_AirCatchHit,
    ftSs_MS_Count,
    ftSs_MS_SelfCount = ftSs_MS_Count - ftCo_MS_Count,
} ftSamus_MotionState;

typedef enum ftSs_Submotion {
    ftSs_SM_SpecialLw = ftCo_SM_Count,
    ftSs_SM_SpecialAirLw,
    ftSs_SM_SpecialNStart,
    ftSs_SM_SpecialNHold,
    ftSs_SM_SpecialNCancel,
    ftSs_SM_SpecialN,
    ftSs_SM_SpecialAirNStart,
    ftSs_SM_SpecialAirN,
    ftSs_SM_SpecialS,
    ftSs_SM_SpecialSSmash,
    ftSs_SM_SpecialAirS,
    ftSs_SM_SpecialAirSSmash,
    ftSs_SM_SpecialHi,
    ftSs_SM_SpecialAirHi,
    ftSs_SM_SpecialLwBomb,
    ftSs_SM_SpecialAirLwBomb,
    ftSs_SM_AirCatch,
    ftSs_SM_AirCatchHit,
    ftSs_SM_Count,
    ftSs_SM_SelfCount = ftSs_SM_Count - ftCo_SM_Count,
} ftSs_Submotion;

#endif
