/* Generated XDK C constant-expression adapter. Source SHA256: 2D13064AD31C1D2C9F080A7A07A74798D611F60AF4F60841B4B88B5DA7A602AC */
#ifndef MELEE_FT_CHARA_FTPEACH_FORWARD_H
#define MELEE_FT_CHARA_FTPEACH_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

#define ftPe_MF_Base ((MotionFlags) (Ft_MF_SkipItemVis | Ft_MF_FreezeState))

#define ftPe_MF_FloatAttack ((MotionFlags) (ftPe_MF_Base | Ft_MF_SkipParasol))

#define ftPe_MF_FloatAttackAirN ((MotionFlags) (ftPe_MF_FloatAttack | Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit))

#define ftPe_MF_Move_14 ((MotionFlags) (ftPe_MF_FloatAttackAirN | Ft_MF_KeepFastFall))

#define ftPe_MF_FloatAttackAirB ((MotionFlags) (ftPe_MF_FloatAttackAirN | Ft_MF_KeepGfx))

#define ftPe_MF_FloatAttackAirHi ((MotionFlags) (ftPe_MF_FloatAttackAirN | Ft_MF_KeepFastFall | Ft_MF_KeepGfx))

#define ftPe_MF_Move_17 ((MotionFlags) (ftPe_MF_FloatAttack | Ft_MF_SkipModel))

#define ftPe_MF_AttackS4 ((MotionFlags) (ftPe_MF_Base | Ft_MF_KeepFastFall | Ft_MF_SkipHit | Ft_MF_KeepSfx | Ft_MF_SkipRumble))

#define ftPe_MF_Special ((MotionFlags) (ftPe_MF_Base | Ft_MF_SkipModel | Ft_MF_UnkUpdatePhys))

#define ftPe_MF_SpecialN ((MotionFlags) (ftPe_MF_Special | Ft_MF_KeepFastFall))

#define ftPe_MF_SpecialHi ((MotionFlags) (ftPe_MF_SpecialN | Ft_MF_KeepGfx))

#define ftPe_MF_SpecialLw ((MotionFlags) (ftPe_MF_Special | Ft_MF_KeepColAnimHitStatus))

#define ftPe_MF_SpecialS ((MotionFlags) (ftPe_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx))

#define ftPe_MF_SpecialAirN ((MotionFlags) (ftPe_MF_SpecialN | Ft_MF_SkipParasol))

#define ftPe_MF_SpecialAirHi ((MotionFlags) (ftPe_MF_SpecialHi | Ft_MF_SkipParasol))

#define ftPe_MF_SpecialAirS ((MotionFlags) (ftPe_MF_SpecialS | Ft_MF_SkipParasol))

#define ftPe_MF_ParasolOpen ((MotionFlags) (Ft_MF_SkipHit | Ft_MF_SkipModel | Ft_MF_Unk06 | Ft_MF_SkipItemVis | Ft_MF_SkipModelPartVis))

#define ftPe_MF_ParasolFallSpecial ((MotionFlags) (ftPe_MF_ParasolOpen | Ft_MF_Unk19))

typedef enum ftPeach_MotionState {
    ftPe_MS_Float = ftCo_MS_Count,
    ftPe_MS_FloatFallF,
    ftPe_MS_FloatFallB,
    ftPe_MS_FloatAttackAirN,
    ftPe_MS_FloatAttackAirF,
    ftPe_MS_FloatAttackAirB,
    ftPe_MS_FloatAttackAirHi,
    ftPe_MS_FloatAttackAirLw,
    ftPe_MS_AttackS4Club,
    ftPe_MS_AttackS4Pan,
    ftPe_MS_AttackS4Racket,
    ftPe_MS_SpecialLw,
    ftPe_MS_SpecialAirLw,
    ftPe_MS_SpecialSStart,
    ftPe_MS_SpecialSEnd,
    ftPe_MS_SpecialSJump,
    ftPe_MS_SpecialAirSStart,
    ftPe_MS_SpecialAirSEnd_0,
    ftPe_MS_SpecialAirSEnd_1,
    ftPe_MS_SpecialAirSJump,
    ftPe_MS_SpecialHiStart,
    ftPe_MS_SpecialHiEnd,
    ftPe_MS_SpecialAirHiStart,
    ftPe_MS_SpecialAirHiEnd,
    ftPe_MS_SpecialN,
    ftPe_MS_SpecialNHit,
    ftPe_MS_SpecialAirN,
    ftPe_MS_SpecialAirNHit,
    ftPe_MS_ItemParasolOpen,
    ftPe_MS_ItemParasolFall,
    ftPe_MS_Count,
    ftPe_MS_SelfCount = ftPe_MS_Count - ftCo_MS_Count,
} ftPeach_MotionState;

typedef enum ftPe_Submotion {
    ftPe_SM_Float = ftCo_SM_Count,
    ftPe_SM_FloatFallF,
    ftPe_SM_FloatFallB,
    ftPe_SM_AttackS4_0,
    ftPe_SM_AttackS4_1,
    ftPe_SM_AttackS4_2,
    ftPe_SM_SpecialLw,
    ftPe_SM_SpecialSStart,
    ftPe_SM_SpecialSEnd,
    ftPe_SM_SpecialSJump,
    ftPe_SM_SpecialAirSStart,
    ftPe_SM_SpecialAirSEnd_0,
    ftPe_SM_SpecialAirSEnd_1,
    ftPe_SM_SpecialHiStart,
    ftPe_SM_SpecialHiEnd,
    ftPe_SM_SpecialAirHiStart,
    ftPe_SM_SpecialAirHiEnd,
    ftPe_SM_SpecialN,
    ftPe_SM_SpecialNHit,
    ftPe_SM_SpecialAirN,
    ftPe_SM_SpecialAirNHit,
    ftPe_SM_ItemParasolOpen,
    ftPe_SM_ItemParasolFall,
    ftPe_SM_Count,
    ftPe_SM_SelfCount = ftPe_SM_Count - ftCo_SM_Count,
} ftPe_Submotion;

#endif
