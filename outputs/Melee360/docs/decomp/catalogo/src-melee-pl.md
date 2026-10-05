# Catálogo: src/melee/pl

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/melee/pl/forward.h`

189 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/pl/inlines.h`

31 linhas; 2 definições aparentes; 0 marcadores asm.

Includes: `melee/gm/gmvs.h`, `melee/pl/player.h`

Definições aparentes: `pl_CheckIfSameTeam`, `pl_Verify_gm_8016AEDC`

## `src/melee/pl/pl_040D.c`

346 linhas; 22 definições aparentes; 0 marcadores asm.

Includes: `pl_040D.h`, `player.h`, `plbonus.h`, `plbonusinline.h`, `melee/gm/gm_unsplit.h`

Definições aparentes: `pl_80040DDC`, `pl_80040ED4`, `pl_80040FBC`, `pl_800410F4`, `pl_800411C4`, `pl_80041280`, `pl_800412D0`, `pl_80041300`, `pl_8004134C`, `fn_8004138C`, `pl_800414C0`, `pl_80041524`, `fn_800415B0`, `pl_80041720`, `pl_80041744`, `fn_80041770`, `pl_8004182C`, `pl_800418F4`, `pl_800419AC`, `pl_80041B08`, `fn_80041BC8`, `pl_80041BFC`

## `src/melee/pl/pl_040D.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `placeholder.h`

## `src/melee/pl/plattack.c`

73 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `plattack.h`, `player.h`, `types.h`

Definições aparentes: `plAttack_80037590`, `clearAttackStats`, `plAttack_8003759C`, `plAttack_80037B08`

## `src/melee/pl/plattack.h`

10 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`

## `src/melee/pl/player.c`

2106 linhas; 164 definições aparentes; 0 marcadores asm.

Includes: `player.h`, `melee/ft/forward.h`, `forward.h`, `plattack.h`, `plbonus.h`, `plstale.h`, `types.h`, `dolphin/mtx.h`, `melee/ft/fighter.h`, `melee/ft/ft_0877.h`, `melee/ft/ft_0D4D.h`, `melee/ft/ftdata.h`, `melee/ft/ftdemo.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftKirby/ftkirby.h`, `melee/ft/types.h`, `melee/gm/gm_unsplit.h`, `melee/if/ifstatus.h`, `melee/lb/lbarchive.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/objalloc.h`

Definições aparentes: `hasExtraFighterId`, `Player_CheckSlot`, `Player_GetPtrForSlot`, `Player_80031790`, `Player_80031848`, `func_8008688C_wrapper`, `Player_80031900`, `Player_800319C4`, `Player_80031AD0`, `Player_80031CB0`, `Player_80031D2C`, `Player_80031DA8`, `Player_80031DC8`, `Player_80031EBC`, `Player_80031FB0`, `Player_80032070`, `Player_8003219C`, `Player_8003221C`, `Player_GetPlayerState`, `Player_GetPlayerCharacter`, `Player_SetPlayerCharacter`, `Player_GetPlayerSlotType`, `Player_8003248C`, `Player_SetSlottype`, `Player_800325C8`, `Player_80032610`, `Player_LoadPlayerCoords`, `Player_80032768`, `Player_80032828`, `Player_800328D4`, `Player_80032A04`, `Player_SetPlayerAndEntityFacingDirection`, `Player_80032BB0`, `Player_SetScale`, `Player_GetSpawnPlatformPos`, `Player_SetSpawnPlatformPos`, `Player_GetSomePos`, `Player_SetSomePos`, `Player_80032F30`, `Player_80032FA4`, `Player_GetFacingDirection`, `Player_SetFacingDirection`, `Player_SetFacingDirectionConditional`, `Player_GetCostumeId`, `Player_SetCostumeId`, `Player_GetSubColor`, `Player_SetSubColor`, `Player_GetTeam`, `Player_SetTeam`, `Player_GetPadPort`, `Player_SetPadPort`, `Player_GetCpuLevel`, `Player_SetPlayerAndEntityCpuLevel`, `Player_GetCpuType`, `Player_SetPlayerAndEntityCpuType`, `Player_GetHandicap`, `Player_SetHandicap`, `Player_GetUnk50`, `Player_GetAttackRatio`, `Player_SetAttackRatio`, `Player_GetDefenseRatio`, `Player_SetDefenseRatio`, `Player_GetModelScale`, `Player_SetModelScale`, `Player_80033BB8`, `Player_GetStocks`, `Player_GetP1Stock`, `Player_SetStocks`, `Player_LoseStock`, `Player_GetCoins`, `Player_SetCoins`, `Player_GetTotalCoins`, `Player_SetTotalCoins`, `Player_GetUnk98`, `Player_SetUnk98`, `Player_GetUnk9C`, `Player_SetUnk9C`, `Player_GetEntity`, `Player_GetEntityAtIndex`, `Player_SwapTransformedStates`, `Player_GetDamage`, `Player_SetHUDDamage`, `Player_SetHPByIndex`, `Player_GetOtherStamina`, `Player_SetOtherStamina`, `Player_GetRemainingHP`, `Player_GetMoreFlagsBit2`, `Player_SetMoreFlagsBit2`, `Player_GetMoreFlagsBit3`, `Player_SetMoreFlagsBit3`, `Player_SetMoreFlagsBit4`, `Player_GetMoreFlagsBit4`, `Player_GetMoreFlagsBit5`, `Player_SetMoreFlagsBit5`, `Player_GetMoreFlagsBit6`, `Player_SetMoreFlagsBit6`, `Player_GetFlagsAEBit0`, `Player_SetFlagsAEBit0`, `Player_GetRemainingHPByIndex`, `Player_GetFalls`, `Player_GetFallsByIndex`, `Player_SetFalls`, `Player_SetFallsByIndex`, `Player_GetKOsByPlayerIndex`, `Player_UpdateKOsBySlot`, `Player_GetMatchFrameCount`, `Player_UpdateMatchFrameCount`, `Player_GetSelfDestructs`, `Player_SetSelfDestructs`, `Player_IncSelfDestructs`, `Player_800353BC`, `Player_8003544C`, `Player_SetFlagsBit0`, `Player_GetNametagSlotID`, `Player_SetNametagSlotID`, `Player_GetFlagsBit1`, `Player_SetFlagsBit1`, `Player_UnsetFlagsBit1`, `Player_GetFlagsBit3`, `Player_SetFlagsBit3`, `Player_GetFlagsBit4`, `Player_GetFlagsBit5`, `Player_SetFlagsBit5`, `Player_GetFlagsBit6`, `Player_SetFlagsBit6`, `Player_GetFlagsBit7`, `Player_SetFlagsBit7`, `Player_GetMoreFlagsBit0`, `Player_GetMoreFlagsBit1`, `Player_SetMoreFlagsBit1`, `Player_GetUnk4D`, `Player_SetUnk4D`, `Player_GetFlagsAEBit1`, `Player_SetFlagsAEBit1`, `Player_GetUnk4C`, `Player_SetUnk4C`, `Player_80036058`, `Player_800360D8`, `Player_SetStructFunc`, `Player_GetActionStats`, `Player_GetStaleMoveTableIndexPtr`, `Player_GetUnk6A8Ptr`, `Player_GetStaleMoveTableIndexPtr2`, `Player_80036394`, `Player_80036428`, `Player_SetUnk45`, `Player_GetUnk45`, `Player_UpdateJoystickCountByIndex`, `Player_GetJoystickCountByIndex`, `Player_800366DC`, `Player_80036790`, `Player_80036844`, `Player_800368F8`, `Player_80036978`, `Player_InitOrResetPlayer`, `Player_80036CF0`, `Player_80036D24`, `Player_InitAllPlayers`, `Player_80036DA4`, `Player_80036DD8`, `Player_80036E20`, `Player_80036EA0`, `Player_80036F34`, `Player_80037054`

## `src/melee/pl/player.h`

321 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/gm/forward.h`, `melee/pl/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `dolphin/pad.h`, `melee/pl/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

## `src/melee/pl/plbonus.c`

1254 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `plbonus.h`, `inlines.h`, `pl_040D.h`, `plattack.h`, `player.h`, `plbonusinline.h`, `plbonuslib.h`, `plstale.h`, `pltrick.h`, `types.h`, `melee/cm/camera.h`, `melee/ft/ft_0877.h`, `melee/ft/ft_0892.h`, `melee/ft/ftlib.h`, `melee/gm/gm_unsplit.h`, `melee/it/it_26B1.h`, `sysdolphin/baselib/debug.h`

Definições aparentes: `setFlag`, `setPointValue`, `pl_80038788`, `pl_80038824`, `pl_80038898`, `pl_80038914`, `pl_8003891C`, `pl_80038F10`, `fn_80038FB8`, `pl_8003906C`, `pl_80039238`, `pl_80039418`, `resetBonuses`, `pl_80039450`, `fn_80039618`, `fn_8003B044`, `fn_8003B9A4`, `fn_8003BD60`, `fn_8003C340`, `fn_8003CC84`, `fn_8003D2EC`

## `src/melee/pl/plbonus.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/pl/forward.h`, `stdbool.h`

## `src/melee/pl/plbonusinline.h`

12 linhas; 1 definições aparentes; 0 marcadores asm.

Includes: `sysdolphin/baselib/debug.h`

Definições aparentes: `pl_CalculateAverage`

## `src/melee/pl/plbonuslib.c`

1667 linhas; 96 definições aparentes; 0 marcadores asm.

Includes: `plbonuslib.h`, `Runtime/platform.h`, `math.h`, `placeholder.h`, `inlines.h`, `pl_040D.h`, `player.h`, `plbonus.h`, `plbonusinline.h`, `pltrick.h`, `melee/ft/ft_0877.h`, `melee/ft/ft_0892.h`, `melee/ft/ftlib.h`, `melee/gm/gm_16F1.h`, `melee/gr/stage.h`, `melee/if/ifmagnify.h`, `melee/it/it_26B1.h`

Definições aparentes: `my_sqrtf`, `match_item_kind`, `unk_cond`, `pokemon_item_kind_check`, `plBonusLib_8003D514`, `pl_8003D60C`, `pl_8003D644`, `pl_8003DF44`, `pl_8003DFF4`, `pl_8003E058`, `pl_8003E0E8`, `pl_8003E114`, `pl_8003E150`, `pl_8003E2CC`, `pl_8003E334`, `pl_8003E39C`, `pl_8003E420`, `pl_8003E4A4`, `pl_8003E70C`, `pl_8003E7D4`, `pl_8003E854`, `pl_8003E978`, `fn_8003E998`, `pl_8003EA08`, `pl_8003EA40`, `pl_8003EA74`, `pl_8003EAAC`, `pl_8003EB30`, `pl_8003EC30`, `pl_8003EC9C`, `pl_8003ED0C`, `fn_8003EE2C`, `plBonusLib_8003F294_inline`, `fn_8003F294`, `fn_8003F53C`, `fn_8003F654`, `pl_8003FAA8`, `pl_8003FBFC`, `pl_8003FC20`, `pl_8003FC44`, `pl_8003FC88`, `pl_8003FDA0`, `pl_8003FDC8`, `pl_8003FDF4`, `pl_8003FE1C`, `pl_8003FE40`, `pl_8003FE64`, `pl_8003FED0`, `pl_8003FF44`, `pl_8003FFDC`, `pl_80040048`, `pl_80040120`, `pl_800401F0`, `pl_80040270`, `pl_800402D0`, `pl_80040330`, `pl_80040374`, `pl_800403C0`, `pl_800403FC`, `pl_80040460`, `pl_8004049C`, `pl_80040614`, `pl_8004065C`, `pl_80040688`, `pl_800407C8`, `pl_80040870`, `pl_80040894`, `pl_800408B8`, `pl_800408DC`, `pl_80040900`, `pl_80040924`, `pl_80040948`, `pl_80040A04`, `pl_80040A30`, `pl_80040A54`, `pl_80040A78`, `pl_80040A9C`, `pl_80040AF0`, `pl_80040B18`, `pl_80040B3C`, `pl_80040B64`, `pl_80040B8C`, `pl_80040BD8`, `pl_80040BFC`, `pl_80040C24`, `pl_80040C48`, `pl_80040C6C`, `pl_80040C90`, `pl_80040CB4`, `pl_80040CD8`, `pl_80040CFC`, `pl_80040D20`, `pl_80040D44`, `pl_80040D68`, `pl_80040D8C`, `pl_80040DB8`

## `src/melee/pl/plbonuslib.h`

102 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/pl/forward.h`

## `src/melee/pl/plstale.c`

98 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `plstale.h`, `player.h`, `types.h`, `melee/ft/ftlib.h`, `melee/ft/inlines.h`, `melee/ft/types.h`, `melee/it/inlines.h`, `melee/it/types.h`

Definições aparentes: `plStale_InitAttackInstance`, `plStale_ResetStaleMoveTableForPlayer`, `plStale_IncrementAttackInstance`, `plStale_UpdateStaleMovesFromFighter`, `plStale_UpdateStaleMovesFromItem`

## `src/melee/pl/plstale.h`

14 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/gobj.h`

## `src/melee/pl/pltrick.c`

470 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `pltrick.h`, `pl_040D.h`, `player.h`, `plbonus.h`, `plbonuslib.h`, `types.h`, `melee/ft/ft_0892.h`, `melee/ft/ftdata.h`, `melee/ft/inlines.h`, `melee/gm/gmvs.h`, `melee/if/ifmagnify.h`, `sysdolphin/baselib/debug.h`

Definições aparentes: `pl_80037B2C`, `pl_80037BC0`, `pl_80037BC0_inline`, `pl_80037C60`, `pl_80037DF4`, `pl_80037ECC`, `fn_80037F00`, `pl_80038144`, `pl_800384DC`, `pl_80038628`, `pl_800386D8`, `pl_800386E8`, `fn_80038700`

## `src/melee/pl/pltrick.h`

27 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/pl/forward.h`, `melee/ft/types.h`

## `src/melee/pl/types.h`

376 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/pl/forward.h`, `melee/ft/types.h`

