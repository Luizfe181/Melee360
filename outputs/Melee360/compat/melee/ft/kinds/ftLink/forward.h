/* Generated XDK C constant-expression adapter. Source SHA256: 53FC4FC375D7F296DFEA709846AEEFAC25E48E45AFBCD49F3D6F4C389CEE4D06 */
#ifndef MELEE_FT_CHARA_FTLINK_FORWARD_H
#define MELEE_FT_CHARA_FTLINK_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

typedef struct ftLk_DatAttrs ftLk_DatAttrs;
typedef struct ftLk_FighterVars ftLk_FighterVars;
typedef union ftLk_MotionVars ftLk_MotionVars;

#define ftLk_MF_Base0 ((MotionFlags) (Ft_MF_SkipModel | Ft_MF_SkipThrowException))

#define ftLk_MF_Base1 ((MotionFlags) (Ft_MF_SkipItemVis | Ft_MF_FreezeState))

#define ftLk_MF_Base2 ((MotionFlags) (ftLk_MF_Base1 | Ft_MF_KeepFastFall))

#define ftLk_MF_Base3 ((MotionFlags) (ftLk_MF_Base0 | Ft_MF_UnkUpdatePhys))

#define ftLk_MF_AttackS42 ((MotionFlags) (ftLk_MF_Base2 | Ft_MF_SkipHit))

#define ftLk_MF_SpecialN ((MotionFlags) (ftLk_MF_Base2 | ftLk_MF_Base3))

#define ftLk_MF_SpecialNFullyCharged ((MotionFlags) (ftLk_MF_SpecialN | Ft_MF_Unk19))

#define ftLk_MF_SpecialAirNCharge ((MotionFlags) (ftLk_MF_SpecialN | Ft_MF_SkipParasol))

#define ftLk_MF_SpecialAirNFullyCharged ((MotionFlags) (ftLk_MF_SpecialNFullyCharged | Ft_MF_SkipParasol))

#define ftLk_MF_SpecialAirNFire ((MotionFlags) (ftLk_MF_SpecialAirNCharge | Ft_MF_UnkUpdatePhys))

#define ftLk_MF_SpecialSThrow ((MotionFlags) (ftLk_MF_Base3 | ftLk_MF_Base1 | Ft_MF_KeepGfx))

#define ftLk_MF_SpecialSCatch ((MotionFlags) (ftLk_MF_SpecialSThrow | Ft_MF_UnkUpdatePhys))

#define ftLk_MF_SpecialAirSThrow ((MotionFlags) (ftLk_MF_SpecialSThrow | ftLk_MF_Base3 | Ft_MF_SkipParasol))

#define ftLk_MF_SpecialAirSThrowEmpty ((MotionFlags) (ftLk_MF_SpecialSCatch | ftLk_MF_Base1 | Ft_MF_SkipParasol))

#define ftLk_MF_SpecialHi ((MotionFlags) (Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_SkipModel | Ft_MF_KeepSfx | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState))

#define ftLk_MF_SpecialLw ((MotionFlags) (Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState))

#define ftLk_MF_SpecialAirLw ((MotionFlags) (ftLk_MF_SpecialLw | Ft_MF_SkipParasol))

#define ftLk_MF_ZairCatch ((MotionFlags) (Ft_MF_SkipModelPartVis | Ft_MF_SkipMetalB))

typedef enum ftLink_MotionState {
    ftLk_MS_AttackS42 = ftCo_MS_Count,
    ftLk_MS_AppealSR,
    ftLk_MS_AppealSL,
    ftLk_MS_SpecialNStart,
    ftLk_MS_SpecialNLoop,
    ftLk_MS_SpecialNEnd,
    ftLk_MS_SpecialAirNStart,
    ftLk_MS_SpecialAirNLoop,
    ftLk_MS_SpecialAirNEnd,
    ftLk_MS_SpecialS1,
    ftLk_MS_SpecialS2,
    ftLk_MS_SpecialS1Empty,
    ftLk_MS_SpecialAirS1,
    ftLk_MS_SpecialAirS2,
    ftLk_MS_SpecialAirS1Empty,
    ftLk_MS_SpecialHi,
    ftLk_MS_SpecialAirHi,
    ftLk_MS_SpecialLw,
    ftLk_MS_SpecialAirLw,
    ftLk_MS_AirCatch,
    ftLk_MS_AirCatchHit,
    ftLk_MS_Count,
    ftLk_MS_SelfCount = ftLk_MS_Count - ftCo_MS_Count,
} ftLink_MotionState;

typedef enum ftLk_SpecialNIndex {
    ftLk_SpecialNIndex_Start,
    ftLk_SpecialNIndex_Loop,
    ftLk_SpecialNIndex_End,
    ftLk_SpecialNIndex_AirStart,
    ftLk_SpecialNIndex_AirLoop,
    ftLk_SpecialNIndex_AirEnd,
    ftLk_SpecialNIndex_None,
} ftLk_SpecialNIndex;

typedef enum ftLk_Submotion {
    ftLk_SM_AttackS42 = ftCo_SM_Count,
    ftLk_SM_SpecialNStart,
    ftLk_SM_SpecialNLoop,
    ftLk_SM_SpecialNEnd,
    ftLk_SM_SpecialAirNStart,
    ftLk_SM_SpecialAirNLoop,
    ftLk_SM_SpecialAirNEnd,
    ftLk_SM_SpecialS1,
    ftLk_SM_SpecialS2,
    ftLk_SM_SpecialS1Empty,
    ftLk_SM_SpecialAirS1,
    ftLk_SM_SpecialAirS2,
    ftLk_SM_SpecialAirS1Empty,
    ftLk_SM_SpecialHi,
    ftLk_SM_SpecialAirHi,
    ftLk_SM_SpecialLw,
    ftLk_SM_SpecialAirLw,
    ftLk_SM_AirCatch,
    ftLk_SM_AirCatchHit,
    ftLk_SM_Count,
    ftLk_SM_SelfCount = ftLk_SM_Count - ftCo_SM_Count,
} ftLk_Submotion;

#endif
