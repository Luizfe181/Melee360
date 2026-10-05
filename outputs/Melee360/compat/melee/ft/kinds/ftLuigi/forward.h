/* Generated XDK C constant-expression adapter. Source SHA256: ACC7EED1759F10276024EA7D0337A1A83D12F5C3CEEE6F6E56DAFDC54FEA1C1D */
#ifndef MELEE_FT_CHARA_FTLUIGI_FORWARD_H
#define MELEE_FT_CHARA_FTLUIGI_FORWARD_H

#include <melee/ft/forward.h>
#include <melee/ft/kinds/ftCommon/forward.h>

#define ftLg_MF_Special ((MotionFlags) (Ft_MF_SkipModel | Ft_MF_SkipItemVis | Ft_MF_UnkUpdatePhys | Ft_MF_FreezeState))

#define ftLg_MF_SpecialN ((MotionFlags) (ftLg_MF_Special | Ft_MF_KeepFastFall | Ft_MF_SkipThrowException))

#define ftLg_MF_SpecialS ((MotionFlags) (ftLg_MF_Special | Ft_MF_KeepGfx | Ft_MF_KeepSfx))

#define ftLg_MF_SpecialHi ((MotionFlags) (ftLg_MF_Special | Ft_MF_KeepFastFall | Ft_MF_KeepGfx | Ft_MF_KeepSfx))

#define ftLg_MF_SpecialLw ((MotionFlags) (ftLg_MF_Special | Ft_MF_KeepColAnimHitStatus | Ft_MF_KeepSfx))

#define ftLg_MF_SpecialAirN ((MotionFlags) (ftLg_MF_SpecialN | Ft_MF_SkipParasol))

#define ftLg_MF_SpecialAirS ((MotionFlags) (ftLg_MF_SpecialS | Ft_MF_SkipParasol))

#define ftLg_MF_SpecialAirHi ((MotionFlags) (ftLg_MF_SpecialHi | Ft_MF_SkipParasol))

#define ftLg_MF_SpecialAirLw ((MotionFlags) (ftLg_MF_SpecialLw | Ft_MF_SkipParasol))

#define ftLg_MF_SpecialN_Coll ((MotionFlags) (Ft_MF_SkipColAnim | Ft_MF_UpdateCmd))

typedef enum ftLuigi_MotionState {
    ftLg_MS_SpecialN = ftCo_MS_Count,
    ftLg_MS_SpecialAirN,
    ftLg_MS_SpecialSStart,
    ftLg_MS_SpecialSHold,
    ftLg_MS_SpecialS2,
    ftLg_MS_SpecialSEnd,
    ftLg_MS_SpecialS,
    ftLg_MS_SpecialSMisfire,
    ftLg_MS_SpecialAirSStart,
    ftLg_MS_SpecialAirSHold,
    ftLg_MS_SpecialAirS2,
    ftLg_MS_SpecialAirSEnd,
    ftLg_MS_SpecialAirS,
    ftLg_MS_SpecialAirSMisfire,
    ftLg_MS_SpecialHi,
    ftLg_MS_SpecialAirHi,
    ftLg_MS_SpecialLw,
    ftLg_MS_SpecialAirLw,
    ftLg_MS_Count,
    ftLg_MS_SelfCount = ftLg_MS_Count - ftCo_MS_Count,
} ftLuigi_MotionState;

typedef enum ftLg_Submotion {
    ftLg_SM_SpecialN = ftCo_SM_Count,
    ftLg_SM_SpecialAirN,
    ftLg_SM_SpecialSStart,
    ftLg_SM_SpecialSHold,
    ftLg_SM_SpecialS,
    ftLg_SM_SpecialSMisfire,
    ftLg_SM_SpecialS2,
    ftLg_SM_SpecialSEnd,
    ftLg_SM_SpecialAirSStart,
    ftLg_SM_SpecialAirSHold,
    ftLg_SM_SpecialAirS,
    ftLg_SM_SpecialAirSMisfire,
    ftLg_SM_SpecialAirSEnd,
    ftLg_SM_SpecialHi,
    ftLg_SM_SpecialAirHi,
    ftLg_SM_SpecialLw,
    ftLg_SM_SpecialAirLw,
    ftLg_SM_Count,
    ftLg_SM_SelfCount = ftLg_SM_Count - ftCo_SM_Count,
} ftLg_Submotion;

#endif
