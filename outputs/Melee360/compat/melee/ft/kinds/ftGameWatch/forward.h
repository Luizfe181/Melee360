/* Generated XDK C constant-expression adapter. Source SHA256: BC50B872B491124807F5EFD6CCA02223D1D1AE7C0404FF67B79FB79F8CE62683 */
#ifndef MELEE_FT_CHARA_FTGAMEWATCH_FORWARD_H
#define MELEE_FT_CHARA_FTGAMEWATCH_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

#define ftGw_MF_Base ((MotionFlags) (Ft_MF_SkipItemVis | Ft_MF_FreezeState))

#define ftGw_MF_Landing ((MotionFlags) (Ft_MF_KeepColAnimHitStatus | Ft_MF_SkipHit | Ft_MF_KeepSfx | Ft_MF_SkipParasol))

#define ftGw_MF_LandingAirB ((MotionFlags) (ftGw_MF_Landing | Ft_MF_KeepGfx))

#define ftGw_MF_LandingAirHi ((MotionFlags) (ftGw_MF_LandingAirB | Ft_MF_KeepFastFall))

#define ftGw_MF_Attack ((MotionFlags) (ftGw_MF_Base | Ft_MF_KeepSfx))

#define ftGw_MF_AttackLw3 ((MotionFlags) (ftGw_MF_Attack | Ft_MF_SkipHit))

#define ftGw_MF_AttackAirN ((MotionFlags) (ftGw_MF_Attack | ftGw_MF_Landing))

#define ftGw_MF_AttackAirB ((MotionFlags) (ftGw_MF_AttackAirN | Ft_MF_KeepGfx))

#define ftGw_MF_AttackAirHi ((MotionFlags) (ftGw_MF_AttackAirB | Ft_MF_KeepFastFall))

#define ftGw_MF_AttackS4 ((MotionFlags) (ftGw_MF_AttackLw3 | Ft_MF_KeepFastFall | Ft_MF_SkipRumble))

#define ftGw_MF_Attack11 ((MotionFlags) (ftGw_MF_Attack | Ft_MF_KeepFastFall | Ft_MF_Unk19))

#define ftGw_MF_Attack100 ((MotionFlags) (ftGw_MF_Attack | Ft_MF_KeepColAnimHitStatus | Ft_MF_Unk19))

#define ftGw_MF_Special ((MotionFlags) (ftGw_MF_Base | Ft_MF_SkipModel | Ft_MF_UnkUpdatePhys))

#define ftGw_MF_SpecialS ((MotionFlags) (ftGw_MF_Special | Ft_MF_KeepGfx))

#define ftGw_MF_SpecialHi ((MotionFlags) (ftGw_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx))

#define ftGw_MF_SpecialLwCatch ((MotionFlags) (ftGw_MF_Special | Ft_MF_KeepColAnimHitStatus))

#define ftGw_MF_SpecialN ((MotionFlags) (ftGw_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException))

#define ftGw_MF_SpecialAirS ((MotionFlags) (ftGw_MF_SpecialS | Ft_MF_SkipParasol))

#define ftGw_MF_SpecialAirHi ((MotionFlags) (ftGw_MF_SpecialHi | Ft_MF_SkipParasol))

#define ftGw_MF_SpecialAirLwCatch ((MotionFlags) (ftGw_MF_SpecialLwCatch | Ft_MF_SkipParasol))

#define ftGw_MF_SpecialAirN ((MotionFlags) (ftGw_MF_SpecialN | Ft_MF_SkipParasol))

#define ftGw_MF_SpecialLw ((MotionFlags) (ftGw_MF_SpecialLwCatch | Ft_MF_Unk19))

#define ftGw_MF_SpecialAirLw ((MotionFlags) (ftGw_MF_SpecialLw | Ft_MF_SkipParasol))

/// Mr. Game & Watch Motion State IDs
typedef enum ftGameWatch_MotionState {
    ftGw_MS_Attack11 = ftCo_MS_Count,
    ftGw_MS_Attack100Start,
    ftGw_MS_Attack100Loop,
    ftGw_MS_Attack100End,
    ftGw_MS_AttackLw3,
    ftGw_MS_AttackS4,
    ftGw_MS_AttackAirN,
    ftGw_MS_AttackAirB,
    ftGw_MS_AttackAirHi,
    ftGw_MS_LandingAirN,
    ftGw_MS_LandingAirB,
    ftGw_MS_LandingAirHi,
    ftGw_MS_SpecialN,
    ftGw_MS_SpecialAirN,
    ftGw_MS_SpecialS1,
    ftGw_MS_SpecialS2,
    ftGw_MS_SpecialS3,
    ftGw_MS_SpecialS4,
    ftGw_MS_SpecialS5,
    ftGw_MS_SpecialS6,
    ftGw_MS_SpecialS7,
    ftGw_MS_SpecialS8,
    ftGw_MS_SpecialS9,
    ftGw_MS_SpecialAirS1,
    ftGw_MS_SpecialAirS2,
    ftGw_MS_SpecialAirS3,
    ftGw_MS_SpecialAirS4,
    ftGw_MS_SpecialAirS5,
    ftGw_MS_SpecialAirS6,
    ftGw_MS_SpecialAirS7,
    ftGw_MS_SpecialAirS8,
    ftGw_MS_SpecialAirS9,
    ftGw_MS_SpecialHi,
    ftGw_MS_SpecialAirHi,
    ftGw_MS_SpecialLw,
    ftGw_MS_SpecialLwCatch,
    ftGw_MS_SpecialLwShoot,
    ftGw_MS_SpecialAirLw,
    ftGw_MS_SpecialAirLwCatch,
    ftGw_MS_SpecialAirLwShoot,
    ftGw_MS_Count,
    ftGw_MS_SelfCount = ftGw_MS_Count - ftCo_MS_Count,
} ftGameWatch_MotionState;

typedef enum ftGw_Submotion {
    ftGw_SM_SpecialN = ftCo_SM_Count,
    ftGw_SM_SpecialAirN,
    ftGw_SM_SpecialS1,
    ftGw_SM_SpecialS2,
    ftGw_SM_SpecialS3,
    ftGw_SM_SpecialS4,
    ftGw_SM_SpecialS5,
    ftGw_SM_SpecialS6,
    ftGw_SM_SpecialS7,
    ftGw_SM_SpecialS8,
    ftGw_SM_SpecialS9,
    ftGw_SM_SpecialAirS1,
    ftGw_SM_SpecialAirS2,
    ftGw_SM_SpecialAirS3,
    ftGw_SM_SpecialAirS4,
    ftGw_SM_SpecialAirS5,
    ftGw_SM_SpecialAirS6,
    ftGw_SM_SpecialAirS7,
    ftGw_SM_SpecialAirS8,
    ftGw_SM_SpecialAirS9,
    ftGw_SM_SpecialHi,
    ftGw_SM_SpecialAirHi,
    ftGw_SM_SpecialLw,
    ftGw_SM_SpecialLwCatch,
    ftGw_SM_SpecialLwShoot,
    ftGw_SM_SpecialAirLw,
    ftGw_SM_SpecialAirLwCatch,
    ftGw_SM_SpecialAirLwShoot,
    ftGw_SM_Count,
    ftGw_SM_SelfCount = ftGw_SM_Count - ftCo_SM_Count,
} ftGw_Submotion;

typedef enum ftGameWatch_PanicLevel {
    ftGw_Panic_Empty,
    ftGw_Panic_Low,
    ftGw_Panic_Mid,
    ftGw_Panic_Full,
} ftGameWatch_PanicLevel;

#endif
