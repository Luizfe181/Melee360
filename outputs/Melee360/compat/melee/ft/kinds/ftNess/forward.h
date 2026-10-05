/* Generated XDK C constant-expression adapter. Source SHA256: 53328B3777A91F1D09FB52334C8CB8C47716C82F227BD843D81CBE1D55F4CC76 */
#ifndef MELEE_FT_CHARA_FTNESS_FORWARD_H
#define MELEE_FT_CHARA_FTNESS_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

#define ftNs_MF_Attack4 ((MotionFlags) (Ft_MF_SkipHit | Ft_MF_SkipRumble | Ft_MF_SkipItemVis | Ft_MF_FreezeState))

#define ftNs_MF_AttackHi4 ((MotionFlags) (ftNs_MF_Attack4 | Ft_MF_KeepGfx))

#define ftNs_MF_AttackLw4 ((MotionFlags) (ftNs_MF_AttackHi4 | Ft_MF_KeepFastFall))

#define ftNs_MF_AttackHi4Start ((MotionFlags) (ftNs_MF_AttackHi4 | Ft_MF_KeepSfx))

#define ftNs_MF_AttackLw4Start ((MotionFlags) (ftNs_MF_AttackLw4 | Ft_MF_KeepSfx))

#define ftNs_MF_AttackS4 ((MotionFlags) (ftNs_MF_Attack4 | Ft_MF_KeepFastFall | Ft_MF_KeepSfx | Ft_MF_SkipColAnim))

#define ftNs_MF_Special ((MotionFlags) (Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState))

#define ftNs_MF_SpecialLw ((MotionFlags) (ftNs_MF_Special | Ft_MF_KeepColAnimHitStatus))

#define ftNs_MF_Special_SkipUpdateThrowException ((MotionFlags) (ftNs_MF_Special | Ft_MF_SkipThrowException))

#define ftNs_MF_SpecialN ((MotionFlags) (ftNs_MF_Special_SkipUpdateThrowException | Ft_MF_KeepFastFall))

#define ftNs_MF_SpecialS ((MotionFlags) (ftNs_MF_Special_SkipUpdateThrowException | Ft_MF_KeepGfx))

#define ftNs_MF_SpecialHi ((MotionFlags) (ftNs_MF_SpecialN | Ft_MF_KeepGfx))

#define ftNs_MF_SpecialAirLw ((MotionFlags) (ftNs_MF_SpecialLw | Ft_MF_SkipParasol))

#define ftNs_MF_SpecialAirN ((MotionFlags) (ftNs_MF_SpecialN | Ft_MF_SkipParasol))

#define ftNs_MF_SpecialAirS ((MotionFlags) (ftNs_MF_SpecialS | Ft_MF_SkipParasol))

#define ftNs_MF_SpecialAirHi ((MotionFlags) (ftNs_MF_SpecialHi | Ft_MF_SkipParasol))

#define ftNs_MF_SpecialLwLoop ((MotionFlags) (ftNs_MF_SpecialLw | Ft_MF_Unk19))

#define ftNs_MF_SpecialAirLwLoop ((MotionFlags) (ftNs_MF_SpecialLwLoop | Ft_MF_SkipParasol))

typedef enum ftNess_MotionState {
    ftNs_MS_AttackS4 = ftCo_MS_Count,
    ftNs_MS_AttackHi4,
    ftNs_MS_AttackHi4Charge,
    ftNs_MS_AttackHi4Release,
    ftNs_MS_AttackLw4,
    ftNs_MS_AttackLw4Charge,
    ftNs_MS_AttackLw4Release,
    /* 15C */ ftNs_MS_SpecialNStart,
    /* 15D */ ftNs_MS_SpecialNHold,
    /* 15E */ ftNs_MS_SpecialNRelease,
    /* 15F */ ftNs_MS_SpecialNEnd,
    ftNs_MS_SpecialAirNStart,
    ftNs_MS_SpecialAirNHold,
    ftNs_MS_SpecialAirNRelease,
    ftNs_MS_SpecialAirNEnd,
    ftNs_MS_SpecialS,
    ftNs_MS_SpecialAirS,
    /* 166 */ ftNs_MS_SpecialHiStart,
    /* 167 */ ftNs_MS_SpecialHiHold,
    /* 168 */ ftNs_MS_SpecialHiEnd,
    /* 169 */ ftNs_MS_SpecialHi,
    /* 16A */ ftNs_MS_SpecialAirHiStart,
    /* 16B */ ftNs_MS_SpecialAirHiHold,
    /* 16C */ ftNs_MS_SpecialAirHiEnd,
    /* 16D */ ftNs_MS_SpecialAirHi,
    /* 16E */ ftNs_MS_SpecialAirHiRebound,
    ftNs_MS_SpecialLwStart,
    ftNs_MS_SpecialLwHold,
    ftNs_MS_SpecialLwHit,
    ftNs_MS_SpecialLwEnd,
    ftNs_MS_SpecialLwTurn,
    ftNs_MS_SpecialAirLwStart,
    ftNs_MS_SpecialAirLwHold,
    ftNs_MS_SpecialAirLwHit,
    ftNs_MS_SpecialAirLwEnd,
    ftNs_MS_SpecialAirLwTurn,
    ftNs_MS_Count,
    ftNs_MS_SelfCount = ftNs_MS_Count - ftCo_MS_Count,
} ftNess_MotionState;

typedef enum ftNs_Submotion {
    ftNs_SM_AttackHi4Charge = ftCo_SM_Count,
    ftNs_SM_AttackHi4Release,
    ftNs_SM_AttackLw4Charge,
    ftNs_SM_AttackLw4Release,
    ftNs_SM_SpecialNStart,
    ftNs_SM_SpecialNHold0,
    ftNs_SM_SpecialNHold1,
    ftNs_SM_SpecialNEnd,
    ftNs_SM_SpecialAirNStart,
    ftNs_SM_SpecialAirNHold0,
    ftNs_SM_SpecialAirNHold1,
    ftNs_SM_SpecialAirNEnd,
    ftNs_SM_SpecialS,
    ftNs_SM_SpecialAirS,
    ftNs_SM_SpecialHiStart,
    ftNs_SM_SpecialHiHold,
    ftNs_SM_SpecialHiEnd,
    ftNs_SM_SpecialHi,
    ftNs_SM_SpecialAirHiStart,
    ftNs_SM_SpecialAirHiHold,
    ftNs_SM_SpecialAirHiEnd,
    ftNs_SM_SpecialAirHi,
    ftNs_SM_SpecialAirHiRebound,
    ftNs_SM_SpecialLwStart,
    ftNs_SM_SpecialLwHold,
    ftNs_SM_SpecialLwHit,
    ftNs_SM_SpecialLwEnd,
    ftNs_SM_SpecialAirLwStart,
    ftNs_SM_SpecialAirLwHold,
    ftNs_SM_SpecialAirLwHit,
    ftNs_SM_SpecialAirLwEnd,
    ftNs_SM_Count,
    ftNs_SM_SelfCount = ftNs_SM_Count - ftCo_SM_Count,
} ftNs_Submotion;

#endif
