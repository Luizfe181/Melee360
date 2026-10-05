# Catálogo: src/melee/it

Lista completa de arquivos presentes; definições e includes extraídos por heurística, não análise semântica. Caminhos relativos ao checkout work/melee-base.

## `src/melee/it/forward.h`

505 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `sysdolphin/baselib/forward.h`

## `src/melee/it/inlines.h`

107 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `melee/ef/eflib.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itmaplib.h`, `melee/it/types.h`, `melee/mp/mplib.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `GetItemData`, `itResetVelocity`, `Item_ClearCmdVars`, `Item_SetEffectHitlagCallbacks`, `Item_EnterStateWithEffectHitlag`, `Item_ApplyFallingPhysics`, `Item_TickLifetime`, `itGrappleCheckCollision`, `itGetJObjGrandchild`

## `src/melee/it/it_266F.h`

3 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/it/it_26B1.c`

1177 linhas; 79 definições aparentes; 0 marcadores asm.

Includes: `it_26B1.h`, `sysdolphin/baselib/forward.h`, `math.h`, `forward.h`, `inlines.h`, `it_2725.h`, `it_3F14.h`, `itanimlist.h`, `itCommonItems.h`, `item.h`, `ithitbox.h`, `itspawn.h`, `kinds/itbat.h`, `kinds/itbombhei.h`, `kinds/itbox.h`, `kinds/itfflower.h`, `kinds/itflipper.h`, `kinds/itheart.h`, `kinds/itkusudama.h`, `kinds/itlinkbomb.h`, `kinds/itmarumine.h`, `kinds/itmsbomb.h`, `kinds/itrabbitc.h`, `kinds/itsscope.h`, `kinds/itsword.h`, `kinds/ittomato.h`, `types.h`, `melee/ft/ftlib.h`, `melee/ft/types.h`, `melee/gm/gm_unsplit.h`, `melee/lb/lb_00B0.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `my_sqrtf`, `it_8026B1D4`, `it_8026B294`, `itIsHeavy`, `it_8026B2D8`, `itGetKind`, `it_8026B30C`, `itGetHoldKind`, `itGetDamageMultiplier`, `it_8026B344`, `itGetGrabRangeX`, `itGetGrabRangeY`, `it_8026B390`, `it_8026B3A8`, `it_8026B3C0`, `it_8026B3F8`, `it_8026B40C`, `it_8026B424`, `it_8026B47C`, `it_8026B4F0`, `it_8026B54C`, `it_8026B560`, `it_8026B574`, `it_8026B588`, `it_8026B594`, `it_8026B5E4`, `it_8026B634`, `it_8026B684`, `it_8026B6A8`, `it_8026B6C8`, `it_8026B718`, `it_8026B724`, `it_8026B73C`, `it_8026B774`, `itGetMotionId`, `itGetTeamId`, `it_8026B7BC`, `it_8026B7CC`, `it_8026B7D8`, `it_8026B7E0`, `it_8026B7E8`, `RunCallbackUnk`, `it_8026B7F8`, `it_8026B894`, `it_8026B924`, `it_8026B960`, `it_8026B9A8`, `it_8026BAE8`, `it_8026BB20`, `it_8026BB44`, `it_8026BB68`, `it_8026BB88`, `it_8026BBCC`, `it_8026BC14`, `it_8026BC68`, `itGetAttackId`, `it_8026BC90`, `it_8026BCF4`, `it_8026BD0C`, `it_8026BD24`, `it_8026BD3C`, `it_8026BD54`, `it_8026BD6C`, `it_8026BD84`, `it_8026BD9C`, `it_8026BDCC`, `it_8026BE28`, `it_8026BE84`, `it_8026C100`, `it_8026C16C`, `it_8026C1B4`, `it_8026C1D4`, `it_8026C1E8`, `it_8026C220`, `it_8026C258`, `it_8026C334`, `it_8026C368`, `it_8026C3FC`, `it_8026C42C`

## `src/melee/it/it_26B1.h`

251 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/ft/types.h`

## `src/melee/it/it_2725.c`

1488 linhas; 101 definições aparentes; 0 marcadores asm.

Includes: `it_2725.h`, `inlines.h`, `it_26B1.h`, `it_279C.h`, `it_3F14.h`, `itanimlist.h`, `itcoll.h`, `iteffect.h`, `item.h`, `ithitbox.h`, `itmaplib.h`, `melee/db/db.h`, `melee/ef/efsync.h`, `melee/ft/ftlib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcollision.h`, `melee/lb/lbvector.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_8027129C_by_4`, `it_80272560`, `it_802725D4`, `it_80272674`, `it_80272784_inline`, `it_80272784`, `it_80272818`, `it_80272828`, `it_80272860`, `it_802728C8`, `it_80272940`, `it_80272980`, `it_80272A18`, `it_80272A3C`, `it_80272A60`, `it_80272AC4`, `it_80272B40`, `it_80272BA4`, `it_80272C08`, `it_80272C6C`, `it_80272C90`, `it_80272CC0`, `it_80272D1C`, `it_80272D40`, `itColl_BounceOffVictim`, `it_80272DE4`, `it_80272F7C`, `it_80273030`, `itColl_BounceOffShield`, `it_80273130`, `it_80273168`, `it_802731A4`, `it_802731E0`, `it_8027321C`, `it_8027327C`, `it_802732E4`, `it_80273318`, `it_80273408`, `it_80273454`, `it_8027346C`, `it_80273484`, `it_8027349C`, `it_802734B4`, `it_80273500`, `it_80273598`, `it_80273600`, `it_80273648`, `it_80273670`, `it_80273748`, `getOwnerJointPosition`, `it_80273B50`, `it_80273F34`, `it_80274198`, `it_802741F4`, `it_80274250`, `it_8027429C`, `it_802742F4`, `it_80274484`, `it_80274574`, `HSD_JObjSetScale_2`, `it_80274594`, `it_80274658`, `it_802746F8`, `it_80274740`, `it_80274990`, `it_80274A64`, `it_80274C60`, `it_80274C78`, `it_80274C88`, `it_80274CAC`, `it_80274D04`, `it_80274D6C`, `it_80274DAC`, `it_80274DFC`, `it_80274E44`, `it_80274ECC`, `it_80274ED8`, `it_80274EE8`, `it_80274EF8`, `it_80274F10`, `it_80274F28`, `get_bone_by_id`, `it_80274F48`, `it_80274FDC`, `it_80275070`, `it_802750E8`, `it_802750F8`, `it_80275158`, `it_80275174`, `it_8027518C`, `it_802751D8`, `it_80275210`, `it_80275228`, `it_80275240`, `it_80275258`, `it_80275270`, `it_80275288`, `it_802752D8`, `it_80275328`, `it_80275390`, `it_802753BC`

## `src/melee/it/it_2725.h`

123 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/itCharItems.h`, `melee/it/types.h`

## `src/melee/it/it_279C.c`

1630 linhas; 33 definições aparentes; 0 marcadores asm.

Includes: `it_279C.h`, `inlines.h`, `it_2725.h`, `itdraw.h`, `itgroundcoll.h`, `ithitbox.h`, `itzako.h`, `kinds/itcerebi.h`, `kinds/itchicorita.h`, `kinds/itentei.h`, `kinds/itfire.h`, `kinds/itfreezer.h`, `kinds/itfushigibana.h`, `kinds/ithassam.h`, `kinds/ithinoarashi.h`, `kinds/ithitodeman.h`, `kinds/ithouou.h`, `kinds/itkabigon.h`, `kinds/itkamex.h`, `kinds/itkireihana.h`, `kinds/itlizardon.h`, `kinds/itlucky.h`, `kinds/itlugia.h`, `kinds/itmaril.h`, `kinds/itmarumine.h`, `kinds/itmatadogas.h`, `kinds/itmetamon.h`, `kinds/itmew.h`, `kinds/itoldkuri.h`, `kinds/itpippi.h`, `kinds/itporygon2.h`, `kinds/itraikou.h`, `kinds/itsonans.h`, `kinds/itsuikun.h`, `kinds/itthunder.h`, `kinds/ittogepy.h`, `kinds/ittosakinto.h`, `kinds/itunknown.h`, `melee/db/db.h`, `melee/ef/efsync.h`, `melee/ft/fighter.h`, `melee/ft/ft_0892.h`, `melee/ft/ftlib.h`, `melee/gm/gm_unsplit.h`, `melee/lb/lbvector.h`, `melee/pl/plattack.h`, `melee/pl/plbonuslib.h`, `melee/pl/plstale.h`, `melee/pl/pltrick.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_80279C48`, `it_80279CDC`, `it_80279D38`, `it_80279D5C`, `it_80279E24_inline`, `it_80279E24`, `it_80279FF8`, `it_8027A09C`, `it_8027A118`, `it_8027A13C`, `it_8027A160`, `it_8027A344`, `it_8027A364`, `it_8027A4D4`, `it_8027A780`, `it_8027A9B8`, `it_8027AAA0`, `selectPokemonForOpening`, `selectPokemonFromList`, `it_8027AB64`, `it_8027ADEC`, `it_8027AE34`, `it_8027AF50`, `it_8027B070`, `it_8027B0C4`, `it_8027B1F4`, `it_8027B288`, `it_8027B330`, `it_8027B378`, `it_8027B408`, `it_8027B4A4`, `it_8027B508`, `it_8027B564`

## `src/melee/it/it_279C.h`

46 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/it_3F14.c`

863 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `it_3F14.h`, `itdraw.h`, `kinds/itbat.h`, `kinds/itbombhei.h`, `kinds/itbox.h`, `kinds/itcapsule.h`, `kinds/itdkinoko.h`, `kinds/itdosei.h`, `kinds/itegg.h`, `kinds/itevyoshiegg.h`, `kinds/itfflower.h`, `kinds/itfflowerflame.h`, `kinds/itflipper.h`, `kinds/itfoods.h`, `kinds/itfreeze.h`, `kinds/itgshell.h`, `kinds/ithammer.h`, `kinds/ithammerhead.h`, `kinds/itharisen.h`, `kinds/itheart.h`, `kinds/itkinoko.h`, `kinds/itkusudama.h`, `kinds/itlgun.h`, `kinds/itlgunbeam.h`, `kinds/itlgunray.h`, `kinds/itlipstick.h`, `kinds/itlipstickspore.h`, `kinds/itmball.h`, `kinds/itmetalb.h`, `kinds/itmsbomb.h`, `kinds/itparasol.h`, `kinds/itrabbitc.h`, `kinds/itrshell.h`, `kinds/itscball.h`, `kinds/itspycloak.h`, `kinds/itsscope.h`, `kinds/itsscopebeam.h`, `kinds/itstar.h`, `kinds/itstarrod.h`, `kinds/itstarrodstar.h`, `kinds/itsword.h`, `kinds/ittaru.h`, `kinds/ittarucann.h`, `kinds/ittomato.h`, `kinds/itwstar.h`

## `src/melee/it/it_3F14.h`

76 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `dat_macros.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/it_3F2F.c`

2783 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `it_3F2F.h`, `itdraw.h`, `itzako.h`, `kinds/forward.h`, `kinds/it_2ADA.h`, `kinds/it_2E5A.h`, `kinds/it_2F28.h`, `kinds/itarwinglaser.h`, `kinds/itclimbersblizzard.h`, `kinds/itclimbersice.h`, `kinds/itclimbersstring.h`, `kinds/itclinkmilk.h`, `kinds/itcoin.h`, `kinds/itcrazyhandbomb.h`, `kinds/itdrmariopill.h`, `kinds/itfoxblaster.h`, `kinds/itfoxillusion.h`, `kinds/itfoxlaser.h`, `kinds/itgamewatchbreath.h`, `kinds/itgamewatchchef.h`, `kinds/itgamewatchfire.h`, `kinds/itgamewatchgreenhouse.h`, `kinds/itgamewatchjudge.h`, `kinds/itgamewatchmanhole.h`, `kinds/itgamewatchpanic.h`, `kinds/itgamewatchparachute.h`, `kinds/itgamewatchrescue.h`, `kinds/itgamewatchturtle.h`, `kinds/itgreatfoxlaser.h`, `kinds/itheiho.h`, `kinds/itkirbycutterbeam.h`, `kinds/itkirbygamewatchchefpan.h`, `kinds/itkirbyhammer.h`, `kinds/itklap.h`, `kinds/itkoopaflame.h`, `kinds/itkyasarin.h`, `kinds/itkyasarinegg.h`, `kinds/itleadead.h`, `kinds/itlikelike.h`, `kinds/itlinkarrow.h`, `kinds/itlinkbomb.h`, `kinds/itlinkboomerang.h`, `kinds/itlinkbow.h`, `kinds/itlinkhookshot.h`, `kinds/itluigifireball.h`, `kinds/itmariocape.h`, `kinds/itmariofireball.h`, `kinds/itmasterhandbullet.h`, `kinds/itmasterhandlaser.h`, `kinds/itmato.h`, `kinds/itmewtwodisable.h`, `kinds/itmewtwoshadowball.h`, `kinds/itnessbat.h`, `kinds/itnesspkfire.h`, `kinds/itnesspkfirepillar.h`, `kinds/itnesspkflash.h`, `kinds/itnesspkflashexplode.h`, `kinds/itnesspkthunderball.h`, `kinds/itnesspkthundertrail.h`, `kinds/itnessyoyo.h`, `kinds/itnokonoko.h`, `kinds/itoctarock.h`, `kinds/itoctarockstone.h`, `kinds/itoldkuri.h`, `kinds/itoldottosea.h`, `kinds/itpatapata.h`, `kinds/itpeachexplode.h`, `kinds/itpeachparasol.h`, `kinds/itpeachtoad.h`, `kinds/itpeachtoadspore.h`, `kinds/itpeachturnip.h`, `kinds/itpikachuthunder.h`, `kinds/itpikachutjoltair.h`, `kinds/itpikachutjoltground.h`, `kinds/itsamusbomb.h`, `kinds/itsamuschargeshot.h`, `kinds/itsamusgrapple.h`, `kinds/itsamusmissile.h`, `kinds/itseakchain.h`, `kinds/itseakneedleheld.h`, `kinds/itseakneedlethrown.h`, `kinds/itseakvanish.h`, `kinds/ittincle.h`, `kinds/ittools.h`, `kinds/itwhispyapple.h`, `kinds/itwhitebea.h`, `kinds/ityaku.h`, `kinds/ityoshiegglay.h`, `kinds/ityoshieggthrow.h`, `kinds/ityoshistar.h`, `kinds/itzeldadinfire.h`, `kinds/itzeldadinfireexplode.h`, `kinds/itzgshell.h`, `kinds/itzrshell.h`, `kinds/types.h`

## `src/melee/it/it_3F2F.h`

12 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/itanimlist.c`

379 linhas; 25 definições aparentes; 0 marcadores asm.

Includes: `itanimlist.h`, `forward.h`, `inlines.h`, `it_2725.h`, `it_3F14.h`, `itcoll.h`, `iteffect.h`, `item.h`, `ithitbox.h`, `melee/lb/inlines.h`, `melee/lb/lb_013B.h`, `melee/lb/lbcommand.h`, `sysdolphin/baselib/gobjproc.h`

Definições aparentes: `sdata2_order`, `it_80278F2C`, `it_802790C0`, `it_80279544`, `it_802795EC`, `it_80279680`, `it_802796C4`, `it_802796FC`, `it_80279720`, `it_80279744`, `it_80279768`, `it_8027978C`, `it_80279888`, `it_802798D4`, `it_8027990C`, `it_80279958`, `it_802799A8`, `it_802799E4`, `it_80279AF0`, `it_80279B10`, `fn_80279B30`, `it_80279B64`, `it_80279B88`, `it_80279BBC`, `it_80279BE0`

## `src/melee/it/itanimlist.h`

38 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/lb/forward.h`

## `src/melee/it/itCharItems.h`

916 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/ft/types.h`, `melee/gm/types.h`, `melee/lb/types.h`, `sysdolphin/baselib/jobj.h`

## `src/melee/it/itcoll.c`

1433 linhas; 39 definições aparentes; 0 marcadores asm.

Includes: `itcoll.h`, `Runtime/platform.h`, `melee/ef/forward.h`, `placeholder.h`, `inlines.h`, `it_26B1.h`, `it_2725.h`, `it_279C.h`, `it_3F14.h`, `item.h`, `types.h`, `melee/ef/efsync.h`, `melee/ft/fighter.h`, `melee/ft/ft_0881.h`, `melee/ft/ftchangeparam.h`, `melee/ft/ftcoll.h`, `melee/ft/ftcommon.h`, `melee/ft/ftlib.h`, `melee/ft/inlines.h`, `melee/ft/kinds/ftCommon/ftCo_DownAttack.h`, `melee/gm/gm_unsplit.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbcollision.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itColl_chkECBOverlap`, `it_8026F9A0`, `it_8026F9AC`, `it_8026FA2C`, `it_8026FAC4`, `it_8026FC00_inline`, `it_8026FC00`, `it_8026FCF8`, `order_sdata2_0`, `it_8026FE68`, `it_8026FAC4_noinline`, `it_802701BC`, `it_8026F9AC_noinline`, `it_802703E8`, `it_802706D0_sub3`, `it_802706D0`, `it_80270CD8`, `it_80270E30`, `it_8027129C`, `it_8027137C`, `it_8027146C`, `it_802714C0`, `it_80271508`, `it_80271534`, `it_80271590`, `it_8027163C`, `it_80271830`, `it_80271A58`, `it_80271B60`, `it_80271D2C`, `it_80271F78`, `it_802721B8`, `it_80272280`, `it_80272298`, `it_802722B0`, `it_80272304`, `it_8027236C`, `it_802723FC`, `it_80272460`

## `src/melee/it/itcoll.h`

40 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/lb/types.h`

## `src/melee/it/itCommonItems.h`

1908 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/gr/forward.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `placeholder.h`, `dolphin/mtx.h`, `dolphin/types.h`, `melee/gm/types.h`, `melee/lb/types.h`

## `src/melee/it/itdraw.c`

239 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `itdraw.h`, `inlines.h`, `it_2725.h`, `melee/cm/camera.h`, `melee/ft/ftlib.h`, `melee/lb/lb_0146.h`, `melee/lb/lbcollision.h`, `melee/lb/lbgx.h`, `sysdolphin/baselib/tev.h`

Definições aparentes: `it_8026EB18`, `it_8026EBC8`, `it_8026EC54`, `it_8026ECE0`, `it_8026EECC_inline_1`, `it_8026EECC_inline_2`, `it_8026EECC_inline_3`, `it_8026EECC_inline_0`, `it_8026EECC_inline_sw`, `it_8026EECC`

## `src/melee/it/itdraw.h`

16 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `melee/it/types.h`

## `src/melee/it/itdrop.c`

213 linhas; 8 definições aparentes; 0 marcadores asm.

Includes: `itdrop.h`, `inlines.h`, `it_26B1.h`, `it_2725.h`, `it_3F14.h`, `item.h`, `itspawn.h`, `kinds/it_2E5A.h`, `melee/ft/ftlib.h`, `melee/gm/gm_unsplit.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_8026F3AC`, `it_8026F3D4_check_kind`, `it_8026F3D4`, `it_8026F53C`, `it_8026F5C8`, `it_8026F6BC`, `it_8026F7C8`, `it_8026F8B4`

## `src/melee/it/itdrop.h`

17 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/types.h`

## `src/melee/it/iteffect.c`

397 linhas; 4 definições aparentes; 0 marcadores asm.

Includes: `iteffect.h`, `forward.h`, `it_2725.h`, `it_3F14.h`, `types.h`, `melee/ef/efasync.h`, `melee/ef/efsync.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbarchive.h`, `melee/lb/lblanguage.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_8027870C`, `it_802787B4`, `it_80278800_rand_vec`, `it_80278800`

## `src/melee/it/iteffect.h`

16 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`

## `src/melee/it/item.c`

2232 linhas; 83 definições aparentes; 0 marcadores asm.

Includes: `item.h`, `melee/lb/forward.h`, `inlines.h`, `it_26B1.h`, `it_2725.h`, `it_279C.h`, `it_3F14.h`, `it_3F2F.h`, `itanimlist.h`, `itcoll.h`, `iteffect.h`, `itgroundcoll.h`, `ithitbox.h`, `itmaplib.h`, `itmaterial.h`, `types.h`, `dolphin/mtx.h`, `melee/cm/camera.h`, `melee/db/db.h`, `melee/ef/efasync.h`, `melee/ef/eflib.h`, `melee/ft/ftlib.h`, `melee/gm/gm_unsplit.h`, `melee/gr/grlib.h`, `melee/gr/stage.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00F9.h`, `melee/lb/lbaudio_ax.h`, `melee/mp/mpcoll.h`, `melee/mp/mplib.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/debug.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `Item_80266F3C`, `Item_80266F70`, `Item_80266FA8`, `Item_80266FCC`, `ItUnkHoldKind`, `HSD_JObjSetScaleItem`, `HSD_JObjSetFacingDirItem`, `Item_80267130`, `Item_80267454`, `Item_802674AC`, `Item_802675A8`, `Item_802676F4`, `Item_8026784C`, `Item_80267978`, `Item_80267AA8`, `Item_802680CC`, `Item_8026814C`, `Item_802682F0`, `Item_8026849C`, `Item_80268560`, `foobar`, `foobar2`, `foobar3`, `Item_8026862C`, `Item_80268B18`, `Item_80268B5C`, `Item_80268B9C`, `Item_80268BE0`, `Item_80268D34`, `Item_80268DD4`, `Item_80268E40`, `Item_80268E5C`, `Item_802693E4`, `Item_802694CC`, `Item_80269528`, `Item_802696CC`, `Item_802697D4`, `Item_80269978`, `Item_80269A9C`, `Item_80269B60`, `Item_80269BE4`, `Item_80269C5C`, `Item_80269CA0`, `Item_80269CC4`, `Item_80269DC8`, `Item_80269F14`, `Item_8026A0A0`, `Item_8026A0FC`, `func_8026A158_helper`, `Item_8026A158`, `func_8026A1E8_inline`, `Item_8026A1E8`, `processCallback`, `OnTakeDamageThink`, `OnClankThink`, `OnGiveDamageThink`, `EnterHitlagThink`, `checkHitLag`, `Item_8026A294`, `Item_8026A788`, `Item_8026A810`, `Item_8026A848`, `DestroyItemInline`, `ItemSwitch`, `RunGObjCallback`, `func_8026A8EC_inline1`, `func_8026A8EC_inline2`, `func_8026A8EC_inline3`, `Item_8026A8EC`, `Item_8026AB54`, `Item_8026ABD8`, `Item_8026AC74`, `Item_8026AD20`, `Item_8026ADC0`, `Item_OnUserDataRemove`, `Item_8026AE60`, `Item_8026AE84`, `Item_8026AF0C`, `Item_8026AFA0`, `Item_8026B034`, `Item_8026B074`, `Item_8026B0B4`, `Item_IsGrabbable`

## `src/melee/it/item.h`

131 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/ft/types.h`, `sysdolphin/baselib/objalloc.h`

## `src/melee/it/itgroundcoll.c`

802 linhas; 41 definições aparentes; 0 marcadores asm.

Includes: `itgroundcoll.h`, `inlines.h`, `it_2725.h`, `it_3F14.h`, `item.h`, `itmaplib.h`, `melee/mp/mpcoll.h`, `melee/mp/mplib.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_8026D564`, `it_8026D5CC`, `it_8026D604`, `it_8026D62C`, `it_8026D6F4`, `it_8026D78C`, `it_8026D82C`, `it_8026D8A4`, `it_8026D938`, `it_8026D9A0`, `it_8026DA08`, `it_8026DA70`, `it_8026DAA8`, `it_8026DB40`, `it_8026DBC8`, `it_8026DC24`, `it_8026DD5C`, `it_8026DDFC`, `it_8026DE98`, `it_8026DF34`, `it_8026DFB0`, `it_8026E058`, `it_8026E0F4`, `it_8026E_inline`, `it_8026E15C_inline1`, `it_8026E15C_inline2`, `it_8026E15C`, `land`, `it_8026E248`, `it_8026E32C_inline`, `it_8026E32C`, `it_8026E414`, `it_8026E4D0`, `it_8026E5A0`, `it_8026E664`, `it_8026E71C`, `it_8026E7E0`, `it_8026E8C4`, `it_8026E9A4`, `it_8026EA20`, `it_8026EA9C`

## `src/melee/it/itgroundcoll.h`

50 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/types.h`

## `src/melee/it/ithitbox.c`

261 linhas; 22 definições aparentes; 0 marcadores asm.

Includes: `ithitbox.h`, `inlines.h`, `it_2725.h`, `itcoll.h`

Definições aparentes: `it_802753DC`, `it_80275414`, `it_8027542C`, `it_80275444`, `it_80275474`, `it_802754A4`, `it_802754BC`, `it_802754D4`, `it_80275504`, `it_80275534`, `it_80275594`, `it_802755C0`, `it_80275640`, `it_802756D0`, `it_802756E0`, `it_8027570C`, `it_8027572C`, `it_8027574C`, `it_80275788`, `it_80275820`, `it_80275870`, `it_802758D4`

## `src/melee/it/ithitbox.h`

40 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/types.h`

## `src/melee/it/itmaplib.c`

1045 linhas; 38 definições aparentes; 0 marcadores asm.

Includes: `itmaplib.h`, `inlines.h`, `it_26B1.h`, `it_2725.h`, `it_3F14.h`, `iteffect.h`, `ithitbox.h`, `melee/lb/lbvector.h`, `melee/mp/mpcoll.h`, `melee/mp/mplib.h`

Definições aparentes: `sdata2_order`, `it_802759DC`, `it_80275BC8`, `it_80275D5C`, `it_80275DFC`, `it_80275E98`, `it_80276100`, `it_80276174`, `it_80276214`, `it_80276278`, `it_802762B0`, `it_802762BC`, `it_802762D8`, `it_80276308`, `it_80276348`, `it_802763B8`, `it_802763E0`, `it_80276408`, `it_8027649C`, `it_802765BC`, `it_80276934`, `it_80276CB8`, `it_80276CEC`, `it_80276D9C`, `it_80276FC4`, `checkNormalAngle`, `it_80277040`, `sqrtf_accurate_store`, `it_8027737C`, `it_80277544`, `sqrtf_accurate_sp18`, `it_802775F0`, `it_8027770C`, `product_xy`, `sqrtf_accurate_local`, `return_sqrt_value`, `it_8027781C`, `it_80277C40`

## `src/melee/it/itmaplib.h`

45 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/lb/types.h`

## `src/melee/it/itmaterial.c`

431 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `itmaterial.h`, `forward.h`, `inlines.h`, `melee/ft/ftdevice.h`, `melee/lb/lb_00B0.h`, `sysdolphin/baselib/class.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/tev.h`

Definições aparentes: `it_80277D08`, `fn_80277D8C`, `it_80277F90`, `it_80278108`, `it_80278574`

## `src/melee/it/itmaterial.h`

22 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/gx.h`

## `src/melee/it/itPKFlash.h`

46 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/melee/it/itPKThunder.h`

32 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`

## `src/melee/it/itspawn.c`

496 linhas; 20 definições aparentes; 0 marcadores asm.

Includes: `itspawn.h`, `Runtime/platform.h`, `placeholder.h`, `it_26B1.h`, `it_2725.h`, `it_3F14.h`, `item.h`, `melee/db/db.h`, `melee/ef/efsync.h`, `melee/gm/gm_unsplit.h`, `melee/gr/ground.h`, `melee/gr/stage.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/memory.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `sdata2_order`, `it_8026C47C`, `bisectValue`, `it_8026C65C`, `it_8026C704`, `it_8026C75C`, `it_8026C88C_inline`, `fn_8026C88C`, `it_8026CA4C`, `it_8026CB3C`, `it_8026CB9C`, `it_8026CD50`, `it_8026CF04`, `it_8026D018_inline`, `it_8026D018_inline2`, `it_8026D018_inline3`, `it_8026D018`, `it_8026D258`, `it_8026D324`, `it_8026D3CC`

## `src/melee/it/itspawn.h`

23 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `dolphin/mtx.h`, `melee/it/types.h`

## `src/melee/it/itYoyo.h`

35 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`

## `src/melee/it/itzako.c`

708 linhas; 31 definições aparentes; 0 marcadores asm.

Includes: `itzako.h`, `inlines.h`, `it_2725.h`, `it_3F14.h`, `itgroundcoll.h`, `ithitbox.h`, `itmaplib.h`, `itmaterial.h`, `kinds/itcoin.h`, `melee/cm/camera.h`, `melee/ft/fighter.h`, `melee/ft/ftlib.h`, `melee/gm/gm_unsplit.h`, `melee/gr/grlib.h`, `melee/gr/ground.h`, `melee/gr/grzakogenerator.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `melee/pl/plbonuslib.h`, `melee/ty/tydisplay.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `sdata2_order`, `it_8027B5B0`, `it_8027B730`, `it_8027B798_CalcAngle`, `it_8027B798`, `it_8027B964`, `it_8027BA54`, `it_8027BB1C`, `it_8027BBF4`, `it_8027C0A8`, `it_8027C0CC`, `it_8027C0F0`, `it_8027C56C`, `it_8027C794`, `it_8027C79C`, `it_8027C824`, `it_2725_Logic9_Destroyed`, `product_xyz`, `itzako_sqrtf`, `return_sqrt_value3`, `it_8027C8D0`, `it_8027C9D8`, `it_8027CA7C`, `it_8027CAD8`, `it_8027CB3C`, `it_8027CBA4`, `it_8027CBFC`, `it_8027CC88`, `it_8027CE18`, `it_8027CE44`, `it_8027CE64`

## `src/melee/it/itzako.h`

38 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`

## `src/melee/it/kinds/forward.h`

7 linhas; 0 definições aparentes; 0 marcadores asm.

## `src/melee/it/kinds/inlines.h`

319 linhas; 24 definições aparentes; 0 marcadores asm.

Includes: `math.h`, `dolphin/mtx.h`, `melee/cm/camera.h`, `melee/db/db.h`, `melee/ef/eflib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/it/kinds/itlinkhookshot.h`, `melee/it/types.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `Item_RetractChain`, `Item_AttachToParent`, `Item_AttachGameWatchArticle`, `Item_StopAndEnterState`, `Item_EnterAirStateWithHitlag`, `Item_EnterAirStateWithHitlagAndStateDesc`, `Item_UpdateRollingShellRotation`, `Item_ClampAngle`, `Item_ClampAngleReverse`, `Item_UpdateRayAnimation`, `Item_BounceRayOffShield`, `Item_ResetRayAfterReflection`, `Item_InitSpawnPosition`, `Item_InitSpawnCommonFields`, `Item_InitSpawnPositionFromParent`, `itUpdateVelocityFromBone`, `itReflectItemAndUpdateRotation`, `Item_CopyJObjScale`, `Item_NormalizeAngle`, `Item_ClearFlagsAndEnterState`, `Item_UpdateZakoVelocity`, `Item_ZakoDefeat`, `Item_InitLinkMtx`, `Item_InitZakoCollision`

## `src/melee/it/kinds/it_2ADA.c`

85 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `it_2ADA.h`, `Runtime/platform.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `it_802ADA1C`, `it_802ADAF0`, `it_2ADA_UnkMotion0_Anim`, `it_2ADA_UnkMotion0_Phys`, `it_2ADA_UnkMotion0_Coll`, `it_802ADBE4`

## `src/melee/it/kinds/it_2ADA.h`

13 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/it_2E5A.c`

550 linhas; 27 definições aparentes; 1 marcadores asm.

Includes: `it_2E5A.h`, `melee/it/forward.h`, `math.h`, `types.h`, `melee/db/db.h`, `melee/gm/gm_unsplit.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbvector.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjproc.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `sqrtf_store`, `sqrtf_accurate_store`, `it_802E5AC4`, `it_802E5EF4`, `it_802E5F00`, `it_802E5F8C`, `it_802E609C`, `it_802E614C`, `it_802E61C4`, `it_802E628C`, `it_802E6380_inline`, `it_802E6380_tier`, `it_802E6380`, `it_802E657C`, `it_802E6658`, `it_2E5A_ApplyStateDesc`, `it_802E66A0`, `it_2E5A_UnkMotion1_Anim`, `it_2E5A_UnkMotion1_Phys`, `it_2E5A_UnkMotion0_Coll`, `it_802E6888`, `it_2E5A_UnkMotion2_Anim`, `it_2E5A_UnkMotion2_Phys`, `it_2E5A_UnkMotion2_Coll`, `it_2E5A_Logic115_DmgDealt`, `it_802E6A74`, `it_2E5A_Logic115_EvtUnk`

## `src/melee/it/kinds/it_2E5A.h`

35 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/itCommonItems.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/it_2F28.c`

129 linhas; 7 definições aparentes; 0 marcadores asm.

Includes: `it_2F28.h`, `melee/it/forward.h`, `math.h`, `inlines.h`, `types.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itzako.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `it_802F28C8`, `it_802F295C`, `it_802F2A58`, `it_2F28_UnkMotion0_Anim`, `it_2F28_UnkMotion0_Phys`, `it_2F28_UnkMotion0_Coll`, `it_802F2BDC`

## `src/melee/it/kinds/it_2F28.h`

13 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itarwinglaser.c`

630 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `itarwinglaser.h`, `Runtime/platform.h`, `math.h`, `melee/ef/efsync.h`, `melee/ft/ftlib.h`, `melee/gr/grcorneria.h`, `melee/gr/ground.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `melee/mp/mplib.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itArwinglaser_GetCollArg`, `it_802E70BC`, `it_802E72E0`, `it_802E7654`, `it_802E79C8`, `it_802E7A4C`, `itArwinglaser_UnkMotion2_Anim`, `itArwinglaser_UnkMotion3_Anim`, `itArwinglaser_UnkMotion2_Phys`, `itArwinglaser_UnkMotion3_Phys`, `itArwinglaser_UnkMotion2_Coll`, `itArwinglaser_UnkMotion3_Coll`, `itArwinglaser_UnkMotion5_Coll`, `it_802E838C`, `it_802E8418`, `it_802E8420`, `it_802E85F4`, `it_802E8784`

## `src/melee/it/kinds/itarwinglaser.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itbat.c`

209 linhas; 26 definições aparentes; 0 marcadores asm.

Includes: `itbat.h`, `inlines.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_80284854`, `itBat_Logic11_Spawned`, `it_80284974`, `itBat_UnkMotion0_Anim`, `itBat_UnkMotion0_Phys`, `itBat_UnkMotion0_Coll`, `it_802849F0`, `itBat_UnkMotion3_Anim`, `itBat_UnkMotion3_Phys`, `itBat_UnkMotion3_Coll`, `itBat_Logic11_PickedUp`, `itBat_UnkMotion2_Anim`, `itBat_UnkMotion2_Phys`, `itBat_UnkMotion2_Coll`, `itBat_Logic11_Dropped`, `itBat_Logic11_Thrown`, `itBat_Logic11_EnteredAir`, `itBat_UnkMotion4_Anim`, `itBat_UnkMotion4_Phys`, `itBat_UnkMotion4_Coll`, `itBat_Logic11_DmgDealt`, `itBat_Logic11_Reflected`, `itBat_Logic11_Clanked`, `itBat_Logic11_HitShield`, `itBat_Logic11_ShieldBounced`, `itBat_Logic11_EvtUnk`

## `src/melee/it/kinds/itbat.h`

38 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itbombhei.c`

820 linhas; 67 definições aparentes; 0 marcadores asm.

Includes: `itbombhei.h`, `melee/it/forward.h`, `inlines.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/lb/lb_00F9.h`

Definições aparentes: `itBombhei_UpdateStatePreserveBone`, `itBombhei_UpdateStatePreserveBoneFake`, `inline1_UnkMotion0_Anim`, `inline2_UnkMotion0_Anim`, `inline_UnkMotion8_Anim`, `itBombhei_UpdateStatePreserveBoneMotion10`, `fn_80280974_inline`, `itBombhei_UnkMotion1_Setup`, `it_8027D670`, `it_8027D730`, `itBombhei_Logic6_Spawned`, `it_8027D820`, `fn_8027DAC8`, `itBombhei_UnkMotion0_Anim`, `itBombhei_UnkMotion0_Phys`, `itBombhei_UnkMotion0_Coll`, `it_8027DE18`, `itBombhei_UnkMotion1_Anim`, `itBombhei_UnkMotion1_Phys`, `itBombhei_UnkMotion1_Coll`, `itBombhei_Logic6_PickedUp`, `itBombhei_UnkMotion8_Anim`, `itBombhei_UnkMotion8_Phys`, `it_3F14_Logic6_Dropped`, `it_8027E978`, `itBombhei_UnkMotion3_Anim`, `itBombhei_UnkMotion3_Phys`, `itBombhei_UnkMotion3_Coll`, `it_8027EE04`, `itBombhei_UnkMotion2_Anim`, `itBombhei_UnkMotion2_Phys`, `itBombhei_UnkMotion2_Coll`, `it_8027F42C`, `itBombhei_UnkMotion4_Anim`, `itBombhei_UnkMotion4_Phys`, `itBombhei_UnkMotion4_Coll`, `it_8027F8E0`, `itBombhei_UnkMotion5_Anim`, `itBombhei_UnkMotion5_Phys`, `itBombhei_UnkMotion5_Coll`, `fn_8027FCA8`, `itBombhei_UnkMotion6_Anim`, `itBombhei_UnkMotion6_Phys`, `fn_8028007C_inline`, `fn_8028007C`, `itBombhei_UnkMotion6_Coll`, `it_3F14_Logic6_Thrown`, `itBombhei_UnkMotion10_Anim`, `itBombhei_UnkMotion10_Phys`, `fn_80280974`, `itBombhei_UnkMotion10_Coll`, `it_80280B60`, `it_80280DC0`, `it_3F14_Logic6_DmgDealt`, `it_3F14_Logic6_DmgReceived`, `itBombhei_UnkMotion11_Anim`, `itBombhei_UnkMotion11_Phys`, `itBombhei_UnkMotion11_Coll`, `it_3F14_Logic6_EnteredAir`, `itBombhei_UnkMotion12_Anim`, `itBombhei_UnkMotion12_Phys`, `itBombhei_UnkMotion12_Coll`, `itBombhei_Logic6_Clanked`, `itBombhei_Logic6_Reflected`, `it_3F14_Logic6_HitShield`, `it_3F14_Logic6_ShieldBounced`, `itBombhei_Logic6_EvtUnk`

## `src/melee/it/kinds/itbombhei.h`

69 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itbox.c`

647 linhas; 46 definições aparentes; 0 marcadores asm.

Includes: `itbox.h`, `Runtime/platform.h`, `placeholder.h`, `inlines.h`, `melee/cm/camera.h`, `melee/ef/efsync.h`, `melee/gr/grkongo.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/itdrop.h`, `melee/it/iteffect.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00F9.h`, `melee/lb/lbvector.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_80286088`, `itBox_Logic1_Spawned`, `itBox_Logic1_Destroyed`, `it_80286248`, `it_80286340`, `it_802863BC`, `fn_80286480`, `itBox_UnkMotion0_Anim`, `itBox_UnkMotion0_Phys`, `itBox_UnkMotion0_Coll`, `it_8028655C`, `itBox_UnkMotion4_Anim`, `itBox_UnkMotion1_Phys`, `itBox_UnkMotion1_Coll`, `itBox_Logic1_PickedUp`, `itBox_UnkMotion2_Anim`, `itBox_UnkMotion2_Phys`, `itBox_Logic1_Thrown`, `itBox_UnkMotion4_Phys`, `itBox_TryOpen_inline`, `itBox_UnkMotion3_Coll`, `itBox_Logic1_Dropped`, `itBox_UnkMotion4_Coll`, `it_80286AA4`, `itBox_UnkMotion6_Anim`, `itBox_UnkMotion6_Phys`, `itBox_UnkMotion6_Coll`, `it_80286BA0`, `itBox_UnkMotion7_Anim`, `itBox_UnkMotion7_Phys`, `itBox_UnkMotion7_Coll`, `itBox_Logic1_DmgDealt`, `itBox_Logic1_Clanked`, `itBox_Logic1_HitShield`, `itBox_Logic1_Reflected`, `itBox_Logic1_DmgReceived`, `itBox_Logic1_EnteredAir`, `itBox_UnkMotion5_Anim`, `itBox_UnkMotion5_Phys`, `itBox_UnkMotion5_Coll`, `itBox_Logic1_EvtUnk`, `it_802870A4`, `itBox_UnkMotion8_Anim`, `itBox_UnkMotion8_Phys`, `itBox_UnkMotion8_Coll`, `it_8028733C`

## `src/melee/it/kinds/itbox.h`

55 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itcapsule.c`

293 linhas; 34 definições aparentes; 0 marcadores asm.

Includes: `itcapsule.h`, `Runtime/platform.h`, `dolphin/mtx.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itCommonItems.h`, `melee/it/itdrop.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/types.h`, `melee/lb/lb_00F9.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itCapsule_Logic0_Spawned`, `it_8027CF30`, `it_8027CFE8`, `it_8027D0B8`, `itCapsule_UnkMotion0_Anim`, `itCapsule_UnkMotion0_Phys`, `itCapsule_UnkMotion0_Coll`, `it_8027D148`, `itCapsule_UnkMotion4_Anim`, `itCapsule_UnkMotion4_Phys`, `itCapsule_UnkMotion4_Coll`, `itCapsule_Logic0_PickedUp`, `itCapsule_UnkMotion2_Anim`, `itCapsule_UnkMotion2_Phys`, `itCapsule_Logic0_Dropped`, `itCapsule_Logic0_Thrown`, `itCapsule_UnkMotion3_Phys`, `itCapsule_UnkMotion3_Coll`, `it_8027D2DC`, `itCapsule_UnkMotion5_Anim`, `itCapsule_UnkMotion5_Phys`, `itCapsule_UnkMotion5_Coll`, `itCapsule_Logic0_DmgDealt`, `itCapsule_Logic0_DmgDealt_autoinlined`, `itCapsule_Logic0_DmgReceived`, `itCapsule_Logic0_EnteredAir`, `itCapsule_UnkMotion6_Anim`, `itCapsule_UnkMotion6_Phys`, `itCapsule_UnkMotion6_Coll`, `itCapsule_Logic0_Clanked`, `itCapsule_Logic0_Reflected`, `itCapsule_Logic0_HitShield`, `itCapsule_Logic0_ShieldBounced`, `itCapsule_Logic0_EvtUnk`

## `src/melee/it/kinds/itcapsule.h`

46 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itcerebi.c`

152 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `itcerebi.h`, `inlines.h`, `melee/ef/efsync.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itCerebi_Logic23_Spawned`, `it_802D3F4C`, `it_802D3F6C`, `it_802D3FA0`, `itCerebi_UnkMotion1_Anim`, `itCerebi_UnkMotion1_Phys`, `itCerebi_UnkMotion1_Coll`, `it_802D4070`, `itCerebi_UnkMotion2_Anim`, `itCerebi_UnkMotion2_Phys`, `itCerebi_UnkMotion2_Coll`, `it_802D4168`, `itCerebi_UnkMotion0_Anim`, `itCerebi_UnkMotion0_Phys`, `itCerebi_UnkMotion0_Coll`

## `src/melee/it/kinds/itcerebi.h`

12 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itchicorita.c`

306 linhas; 27 definições aparentes; 0 marcadores asm.

Includes: `itchicorita.h`, `melee/it/forward.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`

Definições aparentes: `it_802C9588`, `it_802C9618`, `itChicorita_Logic1_EvtUnk`, `it_802C963C`, `it_802C9670`, `itChicorita_UnkMotion0_Anim`, `itChicorita_Phys`, `itChicorita_UnkMotion0_Phys`, `itChicorita_UnkMotion0_Coll`, `it_802C989C`, `it_802C98E4`, `itChicorita_UnkMotion1_Anim`, `itChicorita_UnkMotion1_Phys`, `itChicorita_UnkMotion1_Coll`, `it_802C9A74`, `itChicorita_UnkMotion2_Anim`, `itChicorita_UnkMotion2_Phys`, `itChicorita_UnkMotion2_Coll`, `it_802C9B20`, `itChicoritaLeaf_Logic30_Spawned`, `itChicoritaLeaf_Logic30_HitShield`, `itChicoritaLeaf_Logic30_EvtUnk`, `itChicoritaLeaf_Logic30_Reflected`, `it_802C9CC0`, `itChicoritaleaf_UnkMotion0_Anim`, `itChicoritaleaf_UnkMotion0_Phys`, `itChicoritaleaf_UnkMotion0_Coll`

## `src/melee/it/kinds/itchicorita.h`

39 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itclimbersblizzard.c`

166 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `itclimbersblizzard.h`, `Runtime/platform.h`, `melee/it/forward.h`, `math.h`, `forward.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `spawn_item_0z`, `itClimbersBlizzard_Spawn`, `itClimbersBlizzard_802C2248`, `itClimbersBlizzard_802C2358`, `itClimbersBlizzard_UnkMotion0_Anim`, `itClimbersBlizzard_UnkMotion0_Phys`, `itClimbersBlizzard_UnkMotion0_Coll`, `itClimbersBlizzard_DmgDealt`, `itClimbersBlizzard_Reflected`, `itClimbersBlizzard_Clanked`, `itClimbersBlizzard_HitShield`, `itClimbersBlizzard_Absorbed`, `itClimbersBlizzard_ShieldBounced`, `itClimbersBlizzard_EvtUnk`

## `src/melee/it/kinds/itclimbersblizzard.h`

22 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itclimbersice.c`

382 linhas; 34 definições aparentes; 0 marcadores asm.

Includes: `itclimbersice.h`, `placeholder.h`, `inlines.h`, `melee/db/db.h`, `melee/ef/efasync.h`, `melee/ef/eflib.h`, `melee/ft/kinds/ftKirby/ftkirbyspecialiceclimber.h`, `melee/ft/kinds/ftPopo/ftpopo.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `order_sdata2`, `itClimbersIce_sub_x4`, `itClimbersice_Spawn`, `itClimbersice_Spawn2`, `it_802C1590`, `it_802C16F8`, `it_802C17DC`, `it_2725_Logic90_Destroyed`, `it_802C1854`, `it_802C1950`, `itClimbersice_UnkMotion0_Anim`, `itClimbersice_UnkMotion0_Phys`, `itClimbersice_UnkMotion0_Coll`, `it_802C1A58`, `itClimbersice_UnkMotion1_Anim`, `itClimbersice_UnkMotion1_Phys`, `itClimbersice_UnkMotion1_Coll`, `it_802C1AE4`, `itClimbersice_UnkMotion2_Anim`, `itClimbersice_Phys_inline`, `itClimbersice_UnkMotion2_Phys`, `itClimbersice_Coll`, `itClimbersice_UnkMotion2_Coll`, `fn_802C1D44`, `itClimbersice_UnkMotion3_Anim`, `itClimbersice_UnkMotion3_Phys`, `itClimbersice_UnkMotion3_Coll`, `itClimbersIce_Logic90_DmgDealt`, `itClimbersIce_Logic90_Reflected`, `itClimbersIce_Logic90_Clanked`, `it_2725_Logic90_HitShield`, `itClimbersIce_Logic90_Absorbed`, `itClimbersIce_Logic90_ShieldBounced`, `itClimbersIce_Logic90_EvtUnk`

## `src/melee/it/kinds/itclimbersice.h`

42 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itclimbersstring.c`

616 linhas; 25 definições aparentes; 0 marcadores asm.

Includes: `itclimbersstring.h`, `inlines.h`, `itlinkhookshot.h`, `melee/ft/ftlib.h`, `melee/ft/inlines.h`, `melee/ft/kinds/ftPopo/ftpopospecials.h`, `melee/it/inlines.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjuserdata.h`

Definições aparentes: `it_802C248C_setupGObj`, `it_802C248C_joint24`, `it_802C248C_joint28`, `it_802C248C`, `it_802C2750`, `it_802C27D4`, `fn_802C28B8`, `fn_802C28DC`, `fn_802C29E8`, `fn_802C2AF4`, `itClimbersstring_Cleanup`, `itClimbersstring_UnkMotion3_Anim`, `it_802C2CA8`, `it_802C2DB0`, `it_802C2EC4`, `it_802C2CA8_outline`, `it_802C30E8`, `it_802C32D4`, `it_802C33B8`, `it_802C3520`, `it_2725_Logic70_PickedUp`, `it_802C3810`, `it_802C3864`, `it_802C3950`, `it_2725_Logic70_EvtUnk`

## `src/melee/it/kinds/itclimbersstring.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/itCharItems.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itclinkmilk.c`

140 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `itclinkmilk.h`, `inlines.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftCLink/ftclink.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`

Definições aparentes: `it_802C8B28`, `it_802C8C34`, `it_2725_Logic80_PickedUp`, `itCLinkMilk_NotifyParent`, `itCLinkMilk_Destroy`, `itClinkmilk_UnkMotion1_Anim`, `itClinkmilk_UnkMotion1_Phys`, `itClinkmilk_UnkMotion1_Coll`, `itCLinkMilk_Logic80_EvtUnk`

## `src/melee/it/kinds/itclinkmilk.h`

18 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itcoin.c`

439 linhas; 32 definições aparentes; 0 marcadores asm.

Includes: `itcoin.h`, `melee/it/forward.h`, `inlines.h`, `melee/cm/camera.h`, `melee/gm/gm_unsplit.h`, `melee/gr/grfigureget.h`, `melee/gr/ground.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itcoll.h`, `melee/it/itCommonItems.h`, `melee/it/itdraw.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbvector.h`, `melee/mp/mpcoll.h`, `melee/ty/tydisplay.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802F13B4`, `itCoin_Logic116_Spawned`, `itCoin_Logic116_Destroyed`, `it_802F1588`, `itCoin_UnkMotion0_Anim`, `itCoin_UnkMotion0_Phys`, `itCoin_UnkMotion0_Coll`, `itCoin_ResetRotation`, `it_802F1630`, `itCoin_UnkMotion1_Anim`, `itCoin_UnkMotion1_Phys`, `itCoin_UnkMotion1_Coll`, `itCoin_Logic116_PickedUp`, `itCoin_UnkMotion2_Anim`, `itCoin_UnkMotion2_Phys`, `itCoin_Logic116_EvtUnk`, `itCoin_Logic116_DmgReceived`, `itCoin_UnkMotion3_Anim`, `itCoin_UnkMotion3_Phys`, `itCoin_UnkMotion3_Coll`, `itCoin_Logic116_Thrown`, `itCoin_UnkMotion4_Anim`, `itCoin_UnkMotion4_Phys`, `itCoin_UnkMotion4_Coll`, `itCoin_Logic116_EnteredAir`, `itCoin_UnkMotion5_Anim`, `itCoin_UnkMotion5_Phys`, `itCoin_UnkMotion5_Coll`, `it_802F2014`, `it_802F2020`, `it_802F202C`, `it_802F2094`

## `src/melee/it/kinds/itcoin.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/kinds/itcrazyhandbomb.c`

139 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `itcrazyhandbomb.h`, `inlines.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802F0F6C`, `it_802F1030`, `itCrazyHandBomb_Logic86_EvtUnk`, `itCrazyHandBomb_Logic86_DmgDealt`, `itCrazyHandBomb_Logic86_Reflected`, `it_802F10F8`, `itCrazyhandbomb_UnkMotion0_Anim`, `itCrazyhandbomb_UnkMotion0_Phys`, `itCrazyhandbomb_UnkMotion0_Coll`, `it_802F1340`, `it_802F1344`, `itCrazyhandbomb_UnkMotion1_Anim`, `itCrazyhandbomb_UnkMotion1_Phys`, `itCrazyhandbomb_UnkMotion1_Coll`, `it_802F13B0`

## `src/melee/it/kinds/itcrazyhandbomb.h`

28 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itdkinoko.c`

152 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `itdkinoko.h`, `itkinoko.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`

Definições aparentes: `itDKinoko_Logic27_Spawned`, `it_80293A70`, `itDkinoko_UnkMotion0_Anim`, `itDkinoko_UnkMotion0_Phys`, `itDkinoko_UnkMotion0_Coll`, `it_80293BE8`, `it_80293C10`, `itDkinoko_UnkMotion1_Anim`, `itDkinoko_UnkMotion1_Phys`, `itDkinoko_UnkMotion1_Coll`, `itDKinoko_Logic27_DmgDealt`, `itDKinoko_Logic27_EvtUnk`

## `src/melee/it/kinds/itdkinoko.h`

24 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itdosei.c`

733 linhas; 64 definições aparentes; 0 marcadores asm.

Includes: `itdosei.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/lb/lb_00B0.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `sdata2_order`, `itDosei_SetSpeed`, `HSD_JObjSetRotationZero`, `HSD_JObjSetRotationZeroWithMtxDirty`, `itDosei_FacingAngle`, `itDosei_Logic7_Spawned`, `itDosei_80281390`, `itDosei_UnkMotion0_Anim`, `itDosei_UnkMotion0_Phys`, `itDosei_UnkMotion0_Coll`, `itDosei_80281734`, `itDosei_802817A0`, `itDosei_UnkMotion1_Anim`, `itDosei_UnkMotion1_Phys`, `itDosei_UnkMotion1_Coll`, `itDosei_80281C6C`, `itDosei_UnkMotion2_Anim`, `itDosei_UnkMotion2_Phys`, `itDosei_SetupWalk_FC`, `itDosei_UnkMotion2_Coll`, `itDosei_80282074`, `itDosei_UnkMotion3_Anim`, `itDosei_UnkMotion3_Phys`, `itDosei_UnkMotion5_Coll`, `itDosei_Logic7_PickedUp`, `itDosei_UnkMotion4_Anim_inline`, `itDosei_UnkMotion4_GetAnimSpeed`, `itDosei_UnkMotion4_GetAttrs`, `itDosei_UnkMotion4_Anim`, `itDosei_UnkMotion4_Phys`, `itDosei_GetJObj`, `itDosei_Logic7_Dropped`, `itDosei_Logic7_Thrown`, `itDosei_UnkMotion5_Anim`, `itDosei_UnkMotion5_Phys`, `itDosei_Logic7_EnteredAir`, `itDosei_UnkMotion6_Anim`, `itDosei_UnkMotion6_Phys`, `itDosei_UnkMotion6_Coll`, `itDosei_80282BFC`, `itDosei_UnkMotion8_Anim`, `itDosei_UnkMotion8_Phys`, `itDosei_UnkMotion8_Coll`, `itDosei_80282CD4`, `itDosei_UnkMotion7_Anim`, `itDosei_UnkMotion7_Phys`, `itDosei_UnkMotion7_Coll`, `itDosei_80282DE4`, `itDosei_UnkMotion9_Anim`, `itDosei_UnkMotion9_Phys`, `itDosei_UnkMotion9_Coll`, `itDosei_UnkMotion10_Anim`, `itDosei_UnkMotion10_Phys`, `itDosei_UnkMotion10_Coll`, `itDosei_Logic7_DmgReceived`, `itDosei_UnkMotion11_Anim`, `itDosei_UnkMotion11_Phys`, `itDosei_UnkMotion11_Coll`, `itDosei_Logic7_DmgDealt`, `itDosei_Logic7_Reflected`, `itDosei_Logic7_Clanked`, `itDosei_Logic7_HitShield`, `itDosei_Logic7_ShieldBounced`, `itDosei_Logic7_EvtUnk`

## `src/melee/it/kinds/itdosei.h`

76 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itdrmariopill.c`

460 linhas; 28 definições aparentes; 0 marcadores asm.

Includes: `itdrmariopill.h`, `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `math.h`, `placeholder.h`, `inlines.h`, `dolphin/mtx.h`, `dolphin/types.h`, `melee/db/db.h`, `melee/ft/ft_0BF0.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftDrMario/ftdrmario.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mtx.h`

Definições aparentes: `my_sqrtf`, `itDrMarioPill_Spawn`, `itDrMarioPill_802C061C`, `itDrMarioPill_Appeal_Spawn`, `itDrMarioPill_802C09C4`, `itDrMarioPill_802C0B5C`, `itDrMarioPill_UnkMotion0_Anim`, `itDrMarioPill_UnkMotion0_Phys`, `itDrmariopill_UnkMotion0_Coll`, `itDrMarioPill_802C0DBC`, `itDrMarioPill_802C0DF8`, `itDrMarioPill_Motion2_Anim_sub`, `itDrMarioPill_Motion2_Anim_flags`, `itDrMarioPill_Motion2_Anim`, `itDrMarioPill_Motion2_Phys`, `itDrMariopill_Motion2_Coll`, `itDrMarioPill_802C1180`, `itDrMarioPill_PickedUp`, `itDrMarioPill_Motion6_Anim`, `itDrMarioPill_Motion6_Phys`, `itDrMarioPill_Motion6_Coll`, `itDrMarioPill_DmgDealt`, `itDrMarioPill_Reflected`, `itDrMarioPill_Clanked`, `itDrMarioPill_HitShield`, `itDrMarioPill_Absorbed`, `itDrMarioPill_ShieldBounced`, `itDrMarioPill_EvtUnk`

## `src/melee/it/kinds/itdrmariopill.h`

32 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itegg.c`

324 linhas; 37 definições aparentes; 0 marcadores asm.

Includes: `itegg.h`, `sysdolphin/baselib/forward.h`, `inlines.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itanimlist.h`, `melee/it/itdrop.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_80288C88`, `itEgg_Logic3_Spawned`, `attrRand`, `it_80288DC4`, `it_80288E6C`, `itEgg_UnkMotion0_Anim`, `itEgg_UnkMotion0_Phys`, `itEgg_UnkMotion0_Coll`, `it_80288EFC`, `itEgg_UnkMotion3_Anim`, `itEgg_UnkMotion1_Phys`, `itEgg_UnkMotion1_Coll`, `itEgg_Logic3_PickedUp`, `itEgg_UnkMotion2_Anim`, `itEgg_UnkMotion2_Phys`, `itEgg_Logic3_Dropped`, `itEgg_Logic3_Thrown`, `itEgg_UnkMotion3_Phys`, `itEgg_UnkMotion3_Coll`, `it_80289094`, `itEgg_UnkMotion5_Anim`, `itEgg_UnkMotion5_Phys`, `itEgg_UnkMotion5_Coll`, `it_80289158`, `itEgg_UnkMotion6_Anim`, `itEgg_UnkMotion6_Phys`, `itEgg_UnkMotion6_Coll`, `itEgg_Logic3_DmgDealt`, `itEgg_Logic3_Clanked`, `itEgg_Logic3_HitShield`, `itEgg_Logic3_Reflected`, `itEgg_Logic3_DmgReceived`, `itEgg_Logic3_EnteredAir`, `itEgg_UnkMotion4_Anim`, `itEgg_UnkMotion4_Phys`, `itEgg_UnkMotion4_Coll`, `itEgg_Logic3_EvtUnk`

## `src/melee/it/kinds/itegg.h`

24 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itentei.c`

163 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `itentei.h`, `inlines.h`, `melee/cm/camera.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802CF3E0`, `it_802CF44C`, `it_802CF450`, `it_802CF470`, `it_802CF4D4`, `itEntei_UnkMotion0_Anim`, `itEntei_UnkMotion0_Phys`, `itEntei_UnkMotion0_Coll`, `it_802CF6C8`, `it_802CF744`, `itEntei_UnkMotion1_Anim`, `itEntei_UnkMotion1_Phys`, `itEntei_UnkMotion1_Coll`

## `src/melee/it/kinds/itentei.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itevyoshiegg.c`

256 linhas; 33 definições aparentes; 0 marcadores asm.

Includes: `itevyoshiegg.h`, `Runtime/platform.h`, `melee/it/forward.h`, `placeholder.h`, `forward.h`, `inlines.h`, `melee/ef/efsync.h`, `melee/gm/gmevent.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itEvYoshiEgg_Spawn`, `itEvYoshiEgg_Logic42_Destroyed`, `itEvYoshiEgg_Logic42_Spawned`, `it_8029B1D8`, `itEvyoshiegg_UnkMotion0_Anim`, `itEvyoshiegg_UnkMotion0_Phys`, `itEvyoshiegg_UnkMotion0_Coll`, `it_8029B268`, `itEvyoshiegg_UnkMotion3_Anim`, `itEvyoshiegg_UnkMotion1_Phys`, `itEvyoshiegg_UnkMotion1_Coll`, `itEvYoshiEgg_Logic42_PickedUp`, `itEvyoshiegg_UnkMotion2_Anim`, `itEvyoshiegg_UnkMotion2_Phys`, `itEvYoshiEgg_Logic42_Dropped`, `itEvYoshiEgg_Logic42_Thrown`, `itEvyoshiegg_UnkMotion3_Phys`, `itEvyoshiegg_UnkMotion3_Coll`, `itEvyoshiegg_UnkMotion5_Anim`, `itEvyoshiegg_UnkMotion5_Phys`, `itEvyoshiegg_UnkMotion5_Coll`, `itEvyoshiegg_BounceOff`, `it_3F14_Logic42_DmgDealt`, `it_3F14_Logic42_Clanked`, `it_3F14_Logic42_HitShield`, `it_3F14_Logic42_Reflected`, `dmgReceived`, `itEvYoshiEgg_Logic42_DmgReceived`, `itEvYoshiEgg_Logic42_EnteredAir`, `itEvyoshiegg_UnkMotion4_Anim`, `itEvyoshiegg_UnkMotion4_Phys`, `itEvyoshiegg_UnkMotion4_Coll`, `itEvYoshiEgg_Logic42_EvtUnk`

## `src/melee/it/kinds/itevyoshiegg.h`

43 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itfflower.c`

347 linhas; 32 definições aparentes; 0 marcadores asm.

Includes: `itfflower.h`, `inlines.h`, `itlgunbeam.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `msid_check`, `it_80292D48`, `itFFlower_Logic25_Spawned`, `it_80292E64`, `it_80292EAC`, `it_80292EF8`, `it_80292F14`, `it_80292FF0`, `itFflower_UnkMotion0_Anim`, `itFflower_UnkMotion0_Phys`, `itFflower_UnkMotion0_Coll`, `it_8029313C`, `itFflower_UnkMotion6_Anim`, `itFflower_UnkMotion1_Phys`, `itFflower_UnkMotion1_Coll`, `itFFlower_Logic25_PickedUp`, `itFflower_UnkMotion5_Anim`, `itFflower_UnkMotion5_Phys`, `itFFlower_Logic25_Dropped`, `itFFlower_Logic25_Thrown`, `itFflower_UnkMotion6_Phys`, `itFflower_UnkMotion6_Coll`, `itFFlower_Logic25_DmgDealt`, `itFFlower_Logic25_Clanked`, `itFFlower_Logic25_HitShield`, `itFFlower_Logic25_Reflected`, `itFFlower_Logic25_ShieldBounced`, `itFFlower_Logic25_EnteredAir`, `itFflower_UnkMotion7_Anim`, `itFflower_UnkMotion7_Phys`, `itFflower_UnkMotion7_Coll`, `itFFlower_Logic25_EvtUnk`

## `src/melee/it/kinds/itfflower.h`

29 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/kinds/itfflowerflame.c`

233 linhas; 23 definições aparentes; 0 marcadores asm.

Includes: `itfflowerflame.h`, `placeholder.h`, `inlines.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `it_8029A748`, `it_8029A89C`, `it_8029A8F4`, `itFFlowerFlame_Logic41_Spawned`, `it_8029AA1C`, `itFflowerflame_UnkMotion0_Anim`, `itFflowerflame_UnkMotion0_Phys`, `itFflowerflame_UnkMotion0_Coll`, `it_8029AB90`, `itFflowerflame_UnkMotion1_Anim`, `itFflowerflame_UnkMotion1_Phys`, `itFflowerflame_UnkMotion1_Coll`, `itFFlowerFlame_Logic41_PickedUp`, `itFflowerflame_UnkMotion2_Anim`, `itFFlowerFlame_Logic41_Dropped`, `itFflowerflame_UnkMotion3_Anim`, `itFflowerflame_UnkMotion3_Phys`, `itFflowerflame_UnkMotion3_Coll`, `itFFlowerFlame_Logic41_EnteredAir`, `itFflowerflame_UnkMotion4_Anim`, `itFflowerflame_UnkMotion4_Phys`, `itFflowerflame_UnkMotion4_Coll`, `itFFlowerFlame_Logic41_EvtUnk`

## `src/melee/it/kinds/itfflowerflame.h`

22 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/kinds/itfire.c`

142 linhas; 17 definições aparentes; 0 marcadores asm.

Includes: `itfire.h`, `Runtime/platform.h`, `placeholder.h`, `inlines.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `itFire_Logic6_Spawned`, `it_802CC740`, `itFire_Logic6_EvtUnk`, `itFire_UnkMotion1_Anim`, `itFire_UnkMotion1_Phys`, `itFire_UnkMotion1_Coll`, `it_802CC7D4`, `it_802CC7D8`, `itFire_UnkMotion2_Anim_inline`, `itFire_UnkMotion2_Anim`, `itFire_UnkMotion2_Phys`, `itFire_UnkMotion2_Coll`, `it_802CC944`, `itFire_UnkMotion0_Anim`, `itFire_UnkMotion0_Phys_inline`, `itFire_UnkMotion0_Phys`, `itFire_UnkMotion0_Coll`

## `src/melee/it/kinds/itfire.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itflipper.c`

608 linhas; 48 definições aparentes; 0 marcadores asm.

Includes: `itflipper.h`, `math.h`, `inlines.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbcollision.h`, `melee/lb/lbvector.h`

Definições aparentes: `itFlipper_Spawn`, `itFlipper_Spawned`, `itFlipper_UpdateSpin`, `itFlipper_AddSpinImpulse`, `spinSpeed`, `spinSpeedDirect`, `itFlipper_SpinFromFighter`, `spinFromVictim`, `itFlipper_Repel`, `itFlipper_EnterResting`, `itFlipper_Resting_Anim`, `itFlipper_Resting_Phys`, `itFlipper_Resting_Coll`, `itFlipper_EnterFalling`, `itFlipper_Falling_Anim`, `itFlipper_Falling_Phys`, `itFlipper_Falling_Coll`, `itFlipper_PickedUp`, `itFlipper_Held_Anim`, `itFlipper_Held_Phys`, `itFlipper_Dropped`, `itFlipper_Thrown`, `itFlipper_Inflight_Anim`, `itFlipper_Inflight_Phys`, `itFlipper_Inflight_Coll`, `itFlipper_Settle`, `itFlipper_EnterActive`, `itFlipper_RefreshHitboxes`, `itFlipper_UpdateActive`, `itFlipper_Active_Anim`, `itFlipper_Spinning_Anim`, `itFlipper_Spinning_Phys`, `itFlipper_Spinning_Coll`, `bounce`, `spin`, `itFlipper_DmgDealt`, `bounceOrSpin`, `itFlipper_Clanked`, `itFlipper_HitShield`, `itFlipper_Reflected`, `itFlipper_ShieldBounced`, `spinFromAttacker`, `itFlipper_DmgReceived`, `itFlipper_EnteredAir`, `itFlipper_Airborne_Anim`, `itFlipper_Airborne_Phys`, `itFlipper_Airborne_Coll`, `itFlipper_EvtUnk`

## `src/melee/it/kinds/itflipper.h`

325 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itfoods.c`

185 linhas; 20 definições aparentes; 0 marcadores asm.

Includes: `itfoods.h`, `types.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itspawn.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_8028F9D8`, `it_8028FAF4`, `getRandMax`, `itFoods_Logic18_Spawned`, `it_8028FC5C`, `itFoods_UnkMotion0_Anim`, `itFoods_UnkMotion0_Phys`, `itFoods_UnkMotion0_Coll`, `it_8028FCE8`, `itFoods_UnkMotion1_Anim`, `itFoods_UnkMotion1_Phys`, `itFoods_UnkMotion1_Coll`, `itFoods_Logic18_PickedUp`, `itFoods_UnkMotion2_Anim`, `itFoods_UnkMotion2_Phys`, `itFoods_Logic18_Dropped`, `itFoods_UnkMotion3_Anim`, `itFoods_UnkMotion3_Phys`, `itFoods_UnkMotion3_Coll`, `itFoods_Logic18_EvtUnk`

## `src/melee/it/kinds/itfoods.h`

17 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itfoxblaster.c`

869 linhas; 30 definições aparentes; 0 marcadores asm.

Includes: `itfoxblaster.h`, `stdbool.h`, `inlines.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/ft/ft_0BF0.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftFox/ftfoxspecialn.h`, `melee/ft/kinds/ftKirby/ftkirby.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itFoxBlaster_PlaySFX`, `it_802ADDD0`, `it_802ADEF0`, `itFoxBlaster_SetShotOffset`, `itFoxBlaster_SetShotAngle`, `it_802ADF10`, `it_802AE1D0`, `it_802AE200`, `it_802AE538`, `it_802AE608`, `it_802AE63C`, `itFoxBlaster_SetCommandVars`, `itFoxBlaster_ClearShot`, `it_802AE7B8`, `it_802AE8A8`, `it_802AE994`, `it_802AEAB4`, `itFoxBlaster_Logic96_PickedUp`, `clear_blaster_references`, `clear_blaster`, `itFoxblaster_UnkMotion8_Anim`, `itFoxblaster_UnkMotion8_Phys`, `itFoxblaster_UnkMotion8_Coll`, `itFoxblaster_UnkMotion9_Anim`, `itFoxblaster_UnkMotion9_Phys`, `itFoxblaster_UnkMotion9_Coll`, `itFoxblaster_UnkMotion10_Anim`, `itFoxblaster_UnkMotion10_Phys`, `itFoxblaster_UnkMotion10_Coll`, `itFoxBlaster_Logic96_EvtUnk`

## `src/melee/it/kinds/itfoxblaster.h`

24 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itfoxillusion.c`

244 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `itfoxillusion.h`, `inlines.h`, `melee/db/db.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftFox/ftfoxspecials.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCharItems.h`, `melee/it/itdraw.h`, `melee/it/item.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_8029CD18`, `it_8029CD78`, `it_8029CEB4`, `itFoxIllusion_Logic14_DmgDealt`, `itFoxIllusion_Logic14_Destroyed`, `it_8029CFF0`, `itFoxillusion_UnkMotion0_Anim`, `itFoxillusion_Phys`, `itFoxillusion_UnkMotion0_Phys`, `itFoxillusion_UnkMotion0_Coll`, `itFoxillusion_UnkMotion1_Anim`, `itFoxillusion_UnkMotion1_Phys`, `itFoxillusion_UnkMotion1_Coll`, `it_8029D798`, `itFoxillusion_UnkMotion2_Anim`, `itFoxillusion_UnkMotion2_Phys`, `itFoxillusion_UnkMotion2_Coll`, `it_8029D948`

## `src/melee/it/kinds/itfoxillusion.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itfoxlaser.c`

136 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `itfoxlaser.h`, `melee/lb/forward.h`, `placeholder.h`, `inlines.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_8029C4D4`, `it_8029C504`, `it_8029C6A4`, `it_8029C6CC`, `itFoxlaser_UnkMotion1_Anim`, `itFoxlaser_UnkMotion1_Phys`, `itFoxlaser_UnkMotion1_Coll`, `itFoxLaser_Logic94_Clanked`, `itFoxLaser_Logic94_Reflected`, `itFoxLaser_Logic94_Absorbed`, `itFoxLaser_Logic94_ShieldBounced`, `itFoxLaser_Logic94_HitShield`, `itFoxLaser_Logic94_EvtUnk`

## `src/melee/it/kinds/itfoxlaser.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/lb/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itfreeze.c`

508 linhas; 42 definições aparentes; 0 marcadores asm.

Includes: `itfreeze.h`, `placeholder.h`, `forward.h`, `inlines.h`, `itwhitebea.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_8028EB88`, `it_8028EC98`, `it_8028ECE0`, `it_8028ECF0`, `itFreeze_Logic17_Destroyed`, `it_3F14_Logic17_Spawned`, `it_8028EDBC`, `it_8028EF34`, `itFreeze_UnkMotion0_Anim`, `itFreeze_UnkMotion0_Phys`, `itFreeze_UnkMotion0_Coll`, `it_8028F1D8`, `itFreeze_UnkMotion3_Anim`, `itFreeze_UnkMotion1_Phys`, `itFreeze_UnkMotion1_Coll`, `itFreeze_Logic17_PickedUp`, `itFreeze_UnkMotion2_Anim`, `itFreeze_Logic17_Dropped`, `itFreeze_Logic17_Thrown`, `itFreeze_UnkMotion3_Phys`, `itFreeze_UnkMotion3_Coll`, `itFreeze_Logic17_DmgDealt`, `itFreeze_Logic17_Clanked`, `itFreeze_Logic17_HitShield`, `itFreeze_Logic17_Absorbed`, `itFreeze_Logic17_Reflected`, `itFreeze_Logic17_ShieldBounced`, `itFreeze_Logic17_DmgReceived`, `it_8028F434`, `itFreeze_UnkMotion4_Anim`, `itFreeze_UnkMotion4_Phys`, `itFreeze_ClearLinkedItem`, `itFreeze_ResetToMotion0`, `itFreeze_UnkMotion4_Coll`, `it_8028F7C8`, `itFreeze_UnkMotion5_Anim`, `itFreeze_UnkMotion5_Phys`, `itFreeze_UnkMotion5_Coll`, `itFreeze_Logic17_EvtUnk`, `it_8028F8E4`, `it_8028F968`, `it_8028F9B8`

## `src/melee/it/kinds/itfreeze.h`

52 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itfreezer.c`

180 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `itfreezer.h`, `Runtime/platform.h`, `inlines.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `itFreezer_802CCF9C`, `itFreezer_802CCFFC`, `itFreezer_802CD000`, `itFreezer_UnkMotion1_Anim`, `itFreezer_UnkMotion1_Phys`, `itFreezer_UnkMotion1_Coll`, `itFreezer_802CD090`, `itFreezer_802CD12C`, `itFreezer_UnkMotion2_Anim_Inline`, `itFreezer_UnkMotion2_Anim`, `itFreezer_UnkMotion2_Phys`, `itFreezer_UnkMotion2_Coll`, `itFreezer_802CD290`, `itFreezer_802CD2EC`, `itFreezer_UnkMotion0_Anim`, `itFreezer_UnkMotion0_Phys_inline2`, `itFreezer_UnkMotion0_Phys_inline1`, `itFreezer_UnkMotion0_Phys`, `itFreezer_UnkMotion0_Coll`

## `src/melee/it/kinds/itfreezer.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itfushigibana.c`

146 linhas; 16 definições aparentes; 0 marcadores asm.

Includes: `itfushigibana.h`, `Runtime/platform.h`, `placeholder.h`, `melee/ef/eflib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`

Definições aparentes: `itFushigibana_UnkMotion1_Anim_inline1`, `itFushigibana_UnkMotion1_Anim_inline2`, `itFushigibana_Logic29_Spawned`, `it_802D705C`, `it_802D70A4`, `itFushigibana_UnkMotion0_Anim`, `itFushigibana_UnkMotion0_Phys`, `itFushigibana_UnkMotion0_Coll`, `it_802D718C`, `itFushigibana_UnkMotion1_Anim`, `itFushigibana_UnkMotion1_Phys`, `itFushigibana_UnkMotion1_Coll`, `it_802D7328`, `itFushigibana_UnkMotion2_Anim`, `itFushigibana_UnkMotion2_Phys`, `itFushigibana_UnkMotion2_Coll`

## `src/melee/it/kinds/itfushigibana.h`

24 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itgamewatchbreath.c`

110 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `itgamewatchbreath.h`, `melee/it/forward.h`, `inlines.h`, `melee/ft/kinds/ftGameWatch/ftgamewatchattackair.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`, `melee/it/types.h`

Definições aparentes: `it_802C720C`, `itGameWatchBreath_Logic76_Destroyed`, `it_802C7340`, `it_802C738C`, `it_802C73AC`, `itGameWatchBreath_Logic76_PickedUp`, `it_802C7424`, `itGamewatchbreath_UnkMotion1_Anim`, `itGameWatchBreath_Logic76_EvtUnk`

## `src/melee/it/kinds/itgamewatchbreath.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itgamewatchchef.c`

207 linhas; 16 definições aparentes; 0 marcadores asm.

Includes: `itgamewatchchef.h`, `placeholder.h`, `inlines.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itzako.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802C837C`, `itGameWatchChef_Logic112_DmgDealt`, `it_802C84A0`, `itGamewatchchef_UnkMotion0_Anim`, `itGamewatchchef_UnkMotion0_Phys`, `itGamewatchchef_UnkMotion0_Coll`, `it_802C875C`, `itGamewatchchef_UnkMotion1_Anim`, `itGamewatchchef_UnkMotion1_Phys`, `itGamewatchchef_UnkMotion1_Coll`, `it_2725_Logic112_Clanked`, `it_2725_Logic112_HitShield`, `it_2725_Logic112_Absorbed`, `itGameWatchChef_Logic112_ShieldBounced`, `itGameWatchChef_Logic112_Reflected`, `itGameWatchChef_Logic112_EvtUnk`

## `src/melee/it/kinds/itgamewatchchef.h`

29 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itgamewatchfire.c`

117 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `itgamewatchfire.h`, `inlines.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftGameWatch/ftgamewatchattacks4.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`, `melee/it/types.h`, `melee/lb/lb_00B0.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itGamewatchFire_Spawn`, `itGamewatchFire_Destroyed`, `itGamewatchFire_802C6A2C`, `itGamewatchFire_802C6A78`, `itGamewatchFire_802C6A98`, `itGamewatchFire_PickedUp`, `torchRemoveCheck`, `itGamewatchFire_Motion0_Anim`, `itGamewatchFire_EvtUnk`

## `src/melee/it/kinds/itgamewatchfire.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itgamewatchgreenhouse.c`

145 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `itgamewatchgreenhouse.h`, `melee/it/forward.h`, `forward.h`, `inlines.h`, `melee/ft/kinds/ftGameWatch/ftgamewatchattack11.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/types.h`

Definições aparentes: `itGamewatchGreenhouse_Spawn`, `itGamewatchGreenhouse_Destroyed`, `itGamewatchGreenhouse_802C6328`, `itGamewatchGreenhouse_802C6374`, `itGamewatchGreenhouse_802C6394`, `itGamewatchGreenhouse_PickedUp`, `itGamewatchGreenhouse_802C6430`, `itGamewatchGreenhouse_802C6458`, `itGamewatchGreenhouse_802C6480`, `itGamewatchGreenhouse_802C64A8`, `greenhouse_Check`, `itGamewatchGreenhouse_Motion3_Anim`, `itGamewatchGreenhouse_Motion2_Anim`, `itGamewatchGreenhouse_EvtUnk`

## `src/melee/it/kinds/itgamewatchgreenhouse.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itgamewatchjudge.c`

123 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `itgamewatchjudge.h`, `melee/it/forward.h`, `placeholder.h`, `inlines.h`, `melee/db/db.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftGameWatch/ftgamewatchspecials.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itzako.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802C7774`, `it_802C78B8`, `itGameWatchJudge_Logic77_Destroyed`, `it_802C7A84`, `it_802C7AD0`, `it_802C7AF0`, `it_2725_Logic77_PickedUp`, `itGamewatchjudge_UnkMotion0_Anim`, `itGameWatchJudge_Logic77_EvtUnk`

## `src/melee/it/kinds/itgamewatchjudge.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itgamewatchmanhole.c`

112 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `itgamewatchmanhole.h`, `melee/it/forward.h`, `inlines.h`, `melee/ft/kinds/ftGameWatch/ftgamewatchattacklw3.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00F9.h`

Definições aparentes: `it_802C65E4`, `itGameWatchManhole_Logic72_Destroyed`, `it_802C6718`, `it_802C6764`, `it_802C6784`, `itGameWatchManhole_Logic72_PickedUp`, `itGamewatchmanhole_UnkMotion0_Anim_inline`, `itGamewatchmanhole_UnkMotion0_Anim`, `itGameWatchManhole_Logic72_EvtUnk`

## `src/melee/it/kinds/itgamewatchmanhole.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/kinds/itgamewatchpanic.c`

97 linhas; 8 definições aparentes; 0 marcadores asm.

Includes: `itgamewatchpanic.h`, `inlines.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftGameWatch/ftgamewatchspeciallw.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`

Definições aparentes: `it_802C7D60`, `itGameWatchPanic_Logic78_Destroyed`, `it_802C7E94`, `it_802C7EE0`, `it_802C7F00`, `itGameWatchPanic_Logic78_PickedUp`, `itGamewatchpanic_UnkMotion1_Anim`, `itGameWatchPanic_Logic78_EvtUnk`

## `src/melee/it/kinds/itgamewatchpanic.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/ft/types.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/kinds/itgamewatchparachute.c`

127 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `itgamewatchparachute.h`, `melee/it/forward.h`, `inlines.h`, `melee/ft/kinds/ftGameWatch/ftgamewatchattackair.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`

Definições aparentes: `it_802C6C38`, `itGameWatchParachute_Logic74_Destroyed`, `it_802C6D6C`, `it_802C6DB8`, `it_802C6DD8`, `itGameWatchParachute_Logic74_PickedUp`, `it_802C6E50`, `itGamewatchparachute_UnkMotion1_Anim`, `itGameWatchParachute_Logic74_EvtUnk`

## `src/melee/it/kinds/itgamewatchparachute.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itgamewatchrescue.c`

158 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `itgamewatchrescue.h`, `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `inlines.h`, `melee/ft/kinds/ftGameWatch/ftgamewatchspecialhi.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`, `melee/it/itzako.h`

Definições aparentes: `it_802C8038`, `it_802C8158`, `it_802C81C8`, `it_802C81E8`, `it_802C8208`, `itGamewatchrescue_UnkMotion1_Anim`, `itGamewatchrescue_UnkMotion1_Phys`, `itGamewatchrescue_UnkMotion1_Coll`, `itGameWatchRescue_Logic81_EvtUnk`

## `src/melee/it/kinds/itgamewatchrescue.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itgamewatchturtle.c`

108 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `itgamewatchturtle.h`, `inlines.h`, `types.h`, `melee/ft/kinds/ftGameWatch/ftgamewatchattackair.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `it_802C6F40`, `itGameWatchTurtle_Logic75_Destroyed`, `it_802C7074`, `it_802C70C0`, `it_802C70E0`, `itGameWatchTurtle_Logic75_PickedUp`, `it_802C7158`, `itGamewatchturtle_UnkMotion1_Anim`, `itGameWatchTurtle_Logic75_EvtUnk`

## `src/melee/it/kinds/itgamewatchturtle.h`

23 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/ft/types.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/kinds/itgreatfoxlaser.c`

167 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `itgreatfoxlaser.h`, `melee/ft/ftlib.h`, `melee/gr/ground.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/ithitbox.h`, `melee/it/itzako.h`, `melee/lb/lb_00B0.h`

Definições aparentes: `it_802EAF34`, `it_802EB1EC`, `it_802EB268`, `itGreatfoxlaser_UnkMotion1_Anim`, `itGreatfoxlaser_UnkMotion1_Phys`, `itGreatFoxLaser_Logic27_DmgDealt`, `itGreatFoxLaser_Logic27_Clanked`, `itGreatFoxLaser_Logic27_Absorbed`, `it_2725_Logic27_Reflected`, `it_802EB5A8`

## `src/melee/it/kinds/itgreatfoxlaser.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itgshell.c`

623 linhas; 46 definições aparentes; 0 marcadores asm.

Includes: `itgshell.h`, `Runtime/platform.h`, `melee/it/forward.h`, `placeholder.h`, `inlines.h`, `melee/ef/efasync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_8028B8D8`, `it_8028B988`, `it_8028BA2C`, `it_8028BAD8`, `it_8028BC2C`, `itGShell_Logic14_Spawned`, `it_8028BE54`, `itGshell_UnkMotion0_Anim`, `itGshell_UnkMotion0_Phys`, `itGshell_UnkMotion0_Coll`, `it_8028C018`, `itGshell_UnkMotion1_Anim`, `itGshell_UnkMotion1_Phys`, `itGshell_UnkMotion1_Coll`, `itGShell_Logic14_PickedUp`, `itGshell_UnkMotion2_Anim`, `itGshell_UnkMotion2_Phys`, `itGShell_Logic14_Thrown`, `itGshell_UnkMotion3_Anim`, `itGshell_UnkMotion3_Phys`, `itGshell_UnkMotion3_Coll`, `itGShell_Logic14_Dropped`, `itGshell_UnkMotion4_Anim`, `itGshell_UnkMotion4_Phys`, `itGshell_UnkMotion4_Coll`, `it_8028C3A8`, `itGshell_UnkMotion6_Anim`, `itGshell_UnkMotion6_Phys`, `itGshell_UnkMotion6_Coll`, `it_8028C898`, `itGshell_UnkMotion8_Anim`, `itGshell_UnkMotion8_Phys`, `itGshell_UnkMotion8_Coll`, `itGShell_Logic14_EnteredAir`, `itGshell_UnkMotion9_Anim`, `itGshell_UnkMotion9_Phys`, `itGshell_UnkMotion9_Coll`, `itGShell_Logic14_DmgDealt`, `itGShell_Logic14_DmgReceived`, `itGShell_Logic14_Reflected`, `shellHit`, `itGShell_Logic14_Clanked`, `itGShell_Logic14_HitShield`, `itGShell_Logic14_ShieldBounced`, `it_8028CF68`, `itGShell_Logic14_EvtUnk`

## `src/melee/it/kinds/itgshell.h`

57 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ithammer.c`

237 linhas; 24 definições aparentes; 0 marcadores asm.

Includes: `ithammer.h`, `Runtime/platform.h`, `ithammerhead.h`, `dolphin/mtx.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `thing`, `it_80293D94`, `it_80293DCC`, `it_80293E34`, `itHammer_Logic28_Spawned`, `it_80293F84`, `itHammer_UnkMotion0_Anim`, `itHammer_UnkMotion0_Phys`, `itHammer_UnkMotion0_Coll`, `it_8029402C`, `itHammer_UnkMotion4_Anim`, `itHammer_UnkMotion1_Phys`, `itHammer_UnkMotion1_Coll`, `itHammer_Logic28_PickedUp`, `itHammer_UnkMotion3_Anim`, `it_802941A4`, `itHammer_Logic28_Dropped`, `itHammer_UnkMotion4_Phys`, `itHammer_UnkMotion4_Coll`, `itHammer_Logic28_EnteredAir`, `itHammer_UnkMotion5_Anim`, `itHammer_UnkMotion5_Phys`, `itHammer_UnkMotion5_Coll`, `itHammer_Logic28_EvtUnk`

## `src/melee/it/kinds/ithammer.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ithammerhead.c`

216 linhas; 23 definições aparentes; 0 marcadores asm.

Includes: `ithammerhead.h`, `Runtime/platform.h`, `melee/it/forward.h`, `forward.h`, `inlines.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`

Definições aparentes: `it_80299C48`, `itHammerHead_Logic40_Spawned`, `it_80299D7C`, `itHammerHead_Logic40_PickedUp`, `itHammerhead_UnkMotion1_Anim`, `itHammerhead_UnkMotion1_Phys`, `itHammerHead_Logic40_Dropped`, `itHammerHead_Logic40_Thrown`, `itHammerhead_UnkMotion2_Anim`, `itHammerhead_UnkMotion2_Phys`, `itHammerhead_UnkMotion2_Coll`, `it_80299F94`, `it_80299FB4_get`, `it_80299FB4`, `itHammerhead_UnkMotion3_Anim`, `itHammerhead_UnkMotion3_Phys`, `itHammerhead_UnkMotion3_Coll`, `itHammerHead_Logic40_DmgDealt`, `itHammerHead_Logic40_Clanked`, `itHammerHead_Logic40_HitShield`, `itHammerHead_Logic40_Reflected`, `itHammerHead_Logic40_DmgReceived`, `itHammerHead_Logic40_EvtUnk`

## `src/melee/it/kinds/ithammerhead.h`

36 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itharisen.c`

235 linhas; 33 definições aparentes; 0 marcadores asm.

Includes: `itharisen.h`, `Runtime/platform.h`, `placeholder.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `it_802927E8`, `it_8029282C`, `itHarisen_Logic24_Spawned`, `it_8029287C`, `itHarisen_UnkMotion0_Anim`, `itHarisen_UnkMotion0_Phys`, `itHarisen_UnkMotion0_Coll`, `it_8029290C`, `itHarisen_UnkMotion8_Anim`, `itHarisen_UnkMotion1_Phys`, `itHarisen_UnkMotion1_Coll`, `it_80292998`, `it_802929C8`, `it_802929F8`, `it_80292A28`, `itHarisen_Logic24_PickedUp`, `itHarisen_UnkMotion6_Anim`, `itHarisen_UnkMotion6_Phys`, `itHarisen_Logic24_Dropped`, `itHarisen_UnkMotion8_Coll`, `itHarisen_Logic24_Thrown`, `itHarisen_UnkMotion8_Phys`, `itHarisen_UnkMotion7_Coll`, `itHarisen_Logic24_DmgDealt`, `itHarisen_Logic24_EnteredAir`, `itHarisen_UnkMotion9_Anim`, `itHarisen_UnkMotion9_Phys`, `itHarisen_UnkMotion9_Coll`, `itHarisen_Logic24_Clanked`, `itHarisen_Logic24_Reflected`, `itHarisen_Logic24_HitShield`, `itHarisen_Logic24_ShieldBounced`, `itHarisen_Logic24_EvtUnk`

## `src/melee/it/kinds/itharisen.h`

45 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ithassam.c`

376 linhas; 23 definições aparentes; 0 marcadores asm.

Includes: `ithassam.h`, `melee/it/forward.h`, `math.h`, `inlines.h`, `melee/cm/camera.h`, `melee/ef/eflib.h`, `melee/ft/ftlib.h`, `melee/ft/inlines.h`, `melee/gm/gm_unsplit.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/it/types.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itHassam_802CDBE0`, `itHassam_802CDC5C`, `itHassam_802CDC60`, `itHassam_802CDC80`, `itHassam_802CDCB4`, `itHassam_UnkMotion0_Anim`, `itHassam_UnkMotion0_Phys`, `itHassam_UnkMotion0_Coll`, `itHassam_802CDE1C`, `itHassam_802CDF28`, `itHassam_802CE008`, `itHassam_UnkMotion1_Anim`, `itHassam_UnkMotion1_Phys`, `itHassam_UnkMotion1_Coll`, `itHassam_802CE400_sub`, `itHassam_802CE400`, `itHassam_UnkMotion2_Anim`, `itHassam_UnkMotion2_Phys`, `itHassam_UnkMotion2_Coll`, `it_802CE640`, `itHassam_UnkMotion3_Anim`, `itHassam_UnkMotion3_Phys`, `itHassam_UnkMotion3_Coll`

## `src/melee/it/kinds/ithassam.h`

12 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itheart.c`

194 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `itheart.h`, `inlines.h`, `melee/gm/gm_18A1.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_80283AE4`, `it_80283BD4`, `itHeart_Logic8_Spawned`, `itHeart_Logic8_Destroyed`, `it_80283C7C`, `itHeart_UnkMotion0_Anim`, `itHeart_UnkMotion0_Phys`, `itHeart_UnkMotion0_Coll`, `it_80283DD4`, `itHeart_UnkMotion3_Anim`, `itHeart_UnkMotion3_Phys`, `itHeart_UnkMotion3_Coll`, `itHeart_Logic8_PickedUp`, `itHeart_UnkMotion2_Anim`, `itHeart_UnkMotion2_Phys`, `itHeart_Logic8_Dropped`, `itHeart_Logic8_EnteredAir`, `itHeart_UnkMotion4_Anim`, `itHeart_UnkMotion4_Phys`, `itHeart_UnkMotion4_Coll`, `itHeart_Logic8_EvtUnk`

## `src/melee/it/kinds/itheart.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/kinds/itheiho.c`

426 linhas; 29 definições aparentes; 0 marcadores asm.

Includes: `itheiho.h`, `inlines.h`, `itfoods.h`, `itfreeze.h`, `types.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `sysdolphin/baselib/dobj.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802D8618`, `it_802D8688`, `it_802D8894`, `itHeiho_UnkMotion0_Anim`, `itHeiho_UnkMotion0_Phys`, `itHeiho_UnkMotion0_Coll`, `it_802D8918`, `itHeiho_UnkMotion1_Anim_inline`, `itHeiho_UnkMotion1_Anim`, `itHeiho_UnkMotion1_Phys`, `itHeiho_UnkMotion1_Coll`, `itHeiho_UnkMotion2_Anim`, `it_802D8EC8_inline`, `itHeiho_UnkMotion2_Phys`, `itHeiho_UnkMotion2_Coll`, `itHeiho_UnkMotion3_Anim`, `itHeiho_UnkMotion3_Phys`, `itHeiho_UnkMotion3_Coll`, `it_802D8EC8`, `it_802D9168`, `itHeiho_UnkMotion4_Anim`, `itHeiho_UnkMotion4_Phys`, `itHeiho_UnkMotion4_Coll`, `it_802D96B0`, `it_802D9714_inline`, `it_802D9714`, `it_802D98AC`, `it_802D98C4`, `it_802D9A0C`

## `src/melee/it/kinds/itheiho.h`

14 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ithinoarashi.c`

326 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `ithinoarashi.h`, `math.h`, `inlines.h`, `itmaril.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802D5CF8`, `it_802D5D7C`, `it_802D5E4C`, `it_802D5EC8`, `it_802D5EEC`, `it_802D5F0C`, `it_802D5F34`, `itHinoarashi_UnkMotion1_Anim`, `itHinoarashi_UnkMotion1_Phys`, `itHinoarashi_UnkMotion1_Coll`, `itHinoarashi_UnkMotion2_Anim`, `itHinoarashi_UnkMotion2_Phys`, `it_2725_Logic27_DmgReceived`, `it_802D61A8`, `it_802D61C8`, `it_802D6310`, `it_802D64B8`, `it_802D6674`

## `src/melee/it/kinds/ithinoarashi.h`

30 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ithitodeman.c`

465 linhas; 34 definições aparentes; 0 marcadores asm.

Includes: `ithitodeman.h`, `math.h`, `inlines.h`, `melee/ef/efsync.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `order_data`, `it_2725_Logic24_Spawned`, `it_802D43AC`, `it_802D43B0`, `it_802D43EC`, `it_802D4494`, `it_802D4510`, `it_802D4564_anim_done`, `it_802D4564`, `it_802D472C_inline`, `it_802D472C`, `it_802D48A8`, `it_802D48B0`, `it_802D4990`, `itHitodeman_UnkMotion1_Anim`, `itHitodeman_UnkMotion1_Phys`, `itHitodeman_UnkMotion1_Coll`, `it_802D4B50`, `it_802D4B54`, `itHitodeman_UnkMotion2_Anim`, `itHitodeman_UnkMotion2_Phys`, `itHitodeman_UnkMotion2_Coll`, `it_802D4C74`, `it_2725_Logic43_Spawned`, `it_802D4EF4`, `it_802D4F08`, `it_802D4F28`, `itHitodeman_Logic43_Absorbed`, `it_802D4F50`, `it_802D4F58`, `it_802D4F78`, `it_802D4FFC`, `it_802D5044`, `it_802D5048`

## `src/melee/it/kinds/ithitodeman.h`

45 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ithouou.c`

410 linhas; 34 definições aparentes; 0 marcadores asm.

Includes: `ithouou.h`, `Runtime/platform.h`, `placeholder.h`, `inlines.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/mp/mplib.h`

Definições aparentes: `it_2725_Logic18_Spawned`, `it_802D25B8`, `it_802D25BC`, `itHouou_UnkMotion1_Anim`, `itHouou_UnkMotion1_Phys`, `itHouou_UnkMotion1_Coll`, `it_802D2668`, `itHouou_UnkMotion2_Anim`, `itHouou_UnkMotion2_Phys`, `itHouou_UnkMotion2_Coll`, `it_802D27B0`, `itHouou_UnkMotion3_Anim`, `itHouou_UnkMotion3_Phys`, `itHouou_UnkMotion3_Coll`, `it_802D290C`, `itHouou_UnkMotion4_Anim`, `itHouou_UnkMotion4_Phys`, `itHouou_UnkMotion4_Coll`, `it_802D2A58`, `itHouou_UnkMotion5_Anim`, `itHouou_UnkMotion5_Phys`, `itHouou_UnkMotion5_Coll`, `it_802D2B4C`, `it_802D2BE0`, `it_802D2C54`, `it_802D2C78`, `it_802D2D04`, `it_802D2D2C`, `it_2725_Logic42_Spawned`, `it_802D2ED0`, `it_802D2EF0`, `it_802D2F3C`, `it_802D2F70`, `it_802D2FE8`

## `src/melee/it/kinds/ithouou.h`

45 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkabigon.c`

225 linhas; 20 definições aparentes; 0 marcadores asm.

Includes: `itkabigon.h`, `inlines.h`, `melee/cm/camera.h`, `melee/ef/efsync.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802C9D40`, `it_802C9DFC`, `itKabigon_Logic2_Destroyed`, `it_802C9E24`, `it_802C9E44`, `it_802C9E8C`, `itKabigon_UnkMotion0_Anim`, `itKabigon_UnkMotion0_Phys`, `itKabigon_UnkMotion0_Coll`, `it_802CA014`, `it_802CA074`, `itKabigon_UnkMotion1_Anim_inline`, `itKabigon_UnkMotion1_Anim`, `itKabigon_UnkMotion1_Phys`, `itKabigon_UnkMotion1_Coll`, `it_802CA324`, `itKabigon_UnkMotion2_Anim`, `itKabigon_UnkMotion2_Phys`, `itKabigon_UnkMotion2_Coll`, `it_802CA3F4`

## `src/melee/it/kinds/itkabigon.h`

29 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkamex.c`

325 linhas; 30 definições aparentes; 0 marcadores asm.

Includes: `itkamex.h`, `inlines.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lbaudio_ax.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802CA49C`, `it_802CA534`, `it_802CA538`, `it_802CA558`, `it_802CA58C`, `it_802CA5D8`, `it_802CA618`, `it_802CA654`, `it_802CA6A0`, `itKamex_UnkMotion1_Anim`, `itKamex_UnkMotion1_Phys`, `itKamex_UnkMotion1_Coll`, `it_802CA8DC`, `it_802CA938`, `itKamex_UnkMotion2_Anim`, `itKamex_UnkMotion2_Phys`, `itKamex_UnkMotion2_Coll`, `it_802CAA40`, `itKamex_UnkMotion3_Anim`, `itKamex_UnkMotion3_Phys`, `itKamex_UnkMotion3_Coll`, `it_802CAB10`, `it_2725_Logic31_Spawned`, `itKamex_Logic31_HitShield`, `itKamex_Logic31_DmgDealt`, `itKamex_Logic31_EvtUnk`, `it_802CADF0`, `it_802CAE60`, `it_802CAE94`, `it_802CAFB4`

## `src/melee/it/kinds/itkamex.h`

43 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkinoko.c`

157 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `itkinoko.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`

Definições aparentes: `it_80293660`, `itKinoko_Logic26_Spawned`, `it_802936E4`, `itKinoko_UnkMotion0_Anim`, `itKinoko_UnkMotion0_Phys`, `itKinoko_UnkMotion0_Coll`, `it_8029385C`, `it_80293884`, `itKinoko_UnkMotion1_Anim`, `itKinoko_UnkMotion1_Phys`, `itKinoko_UnkMotion1_Coll`, `itKinoko_Logic26_DmgDealt`, `itKinoko_Logic26_EvtUnk`

## `src/melee/it/kinds/itkinoko.h`

36 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkirby_2F23.c`

161 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `itkirby_2F23.h`, `melee/ft/kinds/ftKirby/ftkirby.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/lb/lbvector.h`

Definições aparentes: `it_802F23AC`, `it_802F23EC_inline`, `it_802F23EC`, `itKirby_2F23_UnkMotion0_Anim`, `itKirby_2F23_UnkMotion0_Phys`, `itKirby_2F23_UnkMotion0_Coll`, `it_802F258C_scale`, `it_802F258C_update`, `it_802F258C`, `it_802F2810`, `itKirby_2F23_UnkMotion1_Anim`, `itKirby_2F23_UnkMotion1_Phys`, `itKirby_2F23_UnkMotion1_Coll`, `it_802F289C`

## `src/melee/it/kinds/itkirby_2F23.h`

27 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkirbycutterbeam.c`

245 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `itkirbycutterbeam.h`, `math.h`, `inlines.h`, `melee/db/db.h`, `melee/ft/kinds/ftKirby/ftkirbyattackdash.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/lb/lbvector.h`

Definições aparentes: `it_8029BAB8`, `it_8029BB90`, `itKirbycutterbeam_UnkMotion0_Anim`, `itKirbycutterbeam_UnkMotion0_Phys`, `itKirbycutterbeam_UnkMotion0_Coll`, `itKirbyCutterBeam_Logic7_DmgDealt`, `itKirbyCutterBeam_Logic7_Clanked`, `itKirbyCutterBeam_Logic7_Absorbed`, `it_2725_Logic7_Reflected`, `it_2725_Logic7_ShieldBounced`, `itKirbyCutterBeam_Logic7_HitShield`, `it_8029C4B4`

## `src/melee/it/kinds/itkirbycutterbeam.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkirbygamewatchchefpan.c`

93 linhas; 9 definições aparentes; 0 marcadores asm.

Includes: `itkirbygamewatchchefpan.h`, `inlines.h`, `melee/ft/kinds/ftKirby/ftkirbyspecialgamewatch.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`, `melee/it/types.h`

Definições aparentes: `it_802C74D8`, `itKirbyGameWatchChefPan_Logic113_Destroyed`, `it_802C760C`, `it_802C7658`, `it_802C7678`, `itKirbyGameWatchChefPan_Logic113_PickedUp`, `itKirbygamewatchchefpan_UnkMotion0_Anim_inline`, `itKirbygamewatchchefpan_UnkMotion0_Anim`, `itKirbyGameWatchChefPan_Logic113_EvtUnk`

## `src/melee/it/kinds/itkirbygamewatchchefpan.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkirbyhammer.c`

78 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `itkirbyhammer.h`, `inlines.h`, `melee/db/db.h`, `melee/ef/efasync.h`, `melee/ft/kinds/ftKirby/ftkirby.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`

Definições aparentes: `itKirbyHammer_Logic8_Destroyed`, `it_802ADC34`, `setupHammerParticles`, `it_802ADC54`, `itKirbyHammer_Logic8_PickedUp`, `it_802ADDB0`

## `src/melee/it/kinds/itkirbyhammer.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/ft/types.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkirbyyoshispecialn.c`

76 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `itkirbyyoshispecialn.h`, `Runtime/platform.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/lb/lb_00B0.h`

Definições aparentes: `it_802F2D98`, `itKirbyyoshispecialn_UnkMotion0_Anim`, `itKirbyyoshispecialn_UnkMotion0_Phys`, `itKirbyyoshispecialn_UnkMotion0_Coll`, `it_802F2E7C`

## `src/melee/it/kinds/itkirbyyoshispecialn.h`

14 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkireihana.c`

290 linhas; 27 definições aparentes; 0 marcadores asm.

Includes: `itkireihana.h`, `Runtime/platform.h`, `placeholder.h`, `inlines.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itKireihana_Logic15_Spawned`, `itKireihana_Logic15_EvtUnk`, `it_802D0138`, `it_802D01A0`, `itKireihana_UnkMotion1_Anim_inline`, `itKireihana_UnkMotion1_Anim`, `itKireihana_UnkMotion1_Phys`, `itKireihana_UnkMotion1_Coll`, `it_802D03F8`, `itKireihana_UnkMotion2_Anim_inline`, `itKireihana_UnkMotion2_Anim`, `itKireihana_UnkMotion2_Phys`, `itKireihana_UnkMotion2_Coll`, `it_802D05D8`, `it_802D062C`, `itKireihana_UnkMotion3_Anim`, `itKireihana_UnkMotion3_Phys`, `itKireihana_UnkMotion3_Coll`, `it_802D0774`, `it_802D07C0`, `itKireihana_UnkMotion4_Anim`, `itKireihana_UnkMotion4_Phys`, `itKireihana_UnkMotion4_Coll`, `it_802D08F0`, `itKireihana_UnkMotion0_Anim`, `itKireihana_UnkMotion0_Phys`, `itKireihana_UnkMotion0_Coll`

## `src/melee/it/kinds/itkireihana.h`

35 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itklap.c`

341 linhas; 26 definições aparentes; 0 marcadores asm.

Includes: `itklap.h`, `math.h`, `melee/gr/grkongo.h`, `melee/gr/ground.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbcollision.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802E1820`, `itKlap_Logic10_Destroyed`, `it_802E18B4_inline`, `it_802E18B4`, `it_802E1930`, `itKlap_UnkMotion1_Anim`, `itKlap_UnkMotion1_Phys`, `itKlap_UnkMotion1_Coll`, `it_802E1C4C`, `it_802E1C84`, `itKlap_UnkMotion2_Anim`, `itKlap_UnkMotion2_Phys`, `itKlap_UnkMotion2_Coll`, `it_2725_Logic10_DmgReceived`, `it_802E1E94`, `itKlap_UnkMotion4_Anim`, `itKlap_UnkMotion4_Phys`, `itKlap_UnkMotion4_Coll`, `it_802E20D8`, `itKlap_UnkMotion3_Anim`, `itKlap_UnkMotion3_Phys`, `itKlap_UnkMotion3_Coll`, `it_802E215C`, `it_802E2330_inline`, `it_802E2330`, `it_802E2450`

## `src/melee/it/kinds/itklap.h`

34 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkoopaflame.c`

329 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `itkoopaflame.h`, `Runtime/platform.h`, `melee/it/forward.h`, `melee/lb/forward.h`, `math.h`, `placeholder.h`, `inlines.h`, `melee/db/db.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/ft/kinds/ftKirby/ftkirby.h`, `melee/ft/kinds/ftKoopa/ftkoopaspecialn.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itKoopaFlame_Update_Direction`, `itKoopaFlame_Update_Angle`, `itKoopaFlame_Spawn`, `itKoopaFlame_Setup`, `itKoopaFlame_UnkMotion0_Anim`, `itKoopaFlame_UnkMotion0_Phys`, `itKoopaFlame_UnkMotion0_Coll`, `itKoopaFlame_Logic111_DmgDealt`, `itKoopaFlame_Logic111_Reflected`, `itKoopaFlame_Logic111_Clanked`, `itKoopaFlame_Logic111_Absorbed`, `itKoopaFlame_Logic111_ShieldBounced`, `itKoopaFlame_Logic111_HitShield`, `itKoopaFlame_Logic111_EvtUnk`

## `src/melee/it/kinds/itkoopaflame.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkusudama.c`

712 linhas; 59 definições aparentes; 0 marcadores asm.

Includes: `itkusudama.h`, `Runtime/platform.h`, `melee/it/forward.h`, `placeholder.h`, `inlines.h`, `dolphin/mtx.h`, `melee/ef/efsync.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/itdrop.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itspawn.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802896CC`, `itKusudama_Logic4_Spawned`, `it_802897C8`, `it_80289910`, `it_8028A544_inline`, `it_80289A00`, `it_80289B50`, `it_80289BE8_inline`, `it_80289BE8_spawn_random`, `it_80289BE8_spawn`, `sdata2_order`, `it_80289BE8`, `it_8028A114`, `it_8028A190_inline`, `it_8028A190`, `itKusudama_UnkMotion0_Anim`, `itKusudama_UnkMotion0_Phys`, `itKusudama_UnkMotion0_Coll`, `itKusudama_UnkMotion1_Anim`, `itKusudama_UnkMotion1_Phys`, `itKusudama_UnkMotion1_Coll`, `it_8028A3CC`, `itKusudama_UnkMotion2_Anim`, `itKusudama_UnkMotion2_Phys`, `itKusudama_UnkMotion2_Coll`, `it_8028A544`, `itKusudama_UnkMotion3_inline`, `itKusudama_UnkMotion3_Anim`, `itKusudama_UnkMotion3_Phys`, `itKusudama_UnkMotion3_Coll`, `itKusudama_Logic4_PickedUp`, `itKusudama_UnkMotion4_Anim`, `itKusudama_UnkMotion4_Phys`, `itKusudama_Logic4_Thrown`, `itKusudama_UnkMotion6_Anim`, `itKusudama_UnkMotion6_Phys`, `itKusudama_UnkMotion5_Coll_inline`, `itKusudama_UnkMotion5_Coll`, `itKusudama_Logic4_Dropped`, `itKusudama_UnkMotion6_Coll_inline2`, `itKusudama_UnkMotion6_Coll_inline`, `itKusudama_UnkMotion6_Coll`, `it_8028AC74`, `itKusudama_UnkMotion7_Anim`, `itKusudama_UnkMotion7_Phys`, `itKusudama_UnkMotion7_Coll`, `it_8028AD44`, `itKusudama_UnkMotion8_Anim_inline`, `itKusudama_UnkMotion8_Anim`, `itKusudama_UnkMotion8_Phys`, `itKusudama_UnkMotion8_Coll`, `itKusudama_Logic4_DmgDealt_inline`, `itKusudama_Logic4_DmgDealt`, `itKusudama_Logic4_Clanked_inline`, `itKusudama_Logic4_Clanked`, `itKusudama_Logic4_HitShield`, `itKusudama_Logic4_Reflected`, `itKusudama_Logic4_DmgReceived`, `itKusudama_Logic4_EvtUnk`

## `src/melee/it/kinds/itkusudama.h`

58 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkyasarin.c`

560 linhas; 39 definições aparentes; 0 marcadores asm.

Includes: `itkyasarin.h`, `placeholder.h`, `forward.h`, `itkyasarinegg.h`, `melee/gr/grinishie2.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itKyasarin_Logic25_Destroyed`, `it_802ECD1C`, `it_802ECD3C`, `it_802ECE90`, `it_802ECEB0`, `itKyasarin_UnkMotion0_Anim`, `itKyasarin_UnkMotion0_Coll`, `it_802ECFE0`, `itKyasarin_UnkMotion1_Anim`, `itKyasarin_UnkMotion3_Anim`, `it_802ED0D0`, `itKyasarin_UnkMotion2_Anim`, `itKyasarin_UnkMotion2_Coll`, `it_802ED25C`, `itKyasarin_UnkMotion4_Anim`, `itKyasarin_Randi`, `itKyasarin_UnkMotion4_Coll`, `it_802ED4F8`, `itKyasarin_TurnAround`, `itKyasarin_UnkMotion6_Anim`, `it_802ED774`, `itKyasarin_UnkMotion7_Anim`, `it_802ED8BC`, `itKyasarin_UnkMotion5_Anim`, `itKyasarin_UnkMotion8_case3`, `itKyasarin_UnkMotion8_case8`, `itKyasarin_UnkMotion8_Anim`, `itKyasarin_UnkMotion9_Anim`, `itKyasarin_UnkMotion9_Phys`, `itKyasarin_UnkMotion9_Coll`, `itKyasarin_UnkMotion10_Anim`, `itKyasarin_UnkMotion10_Phys`, `itKyasarin_UnkMotion10_Coll`, `itKyasarin_SetFallCollPos`, `itKyasarin_GetCollData`, `itKyasarin_FlipAndFall`, `itKyasarin_SaveStateAndStop`, `it_802EDDC0`, `it_802EE1E0`

## `src/melee/it/kinds/itkyasarin.h`

41 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itkyasarinegg.c`

208 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `itkyasarinegg.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itanimlist.h`, `melee/it/itdrop.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itzako.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802EFA44`, `it_802EFB0C`, `itKyasarinegg_UnkMotion0_Coll`, `itKyasarinEgg_Logic28_PickedUp`, `itKyasarinEgg_Logic28_Dropped`, `itKyasarinEgg_Logic28_Thrown`, `itKyasarinegg_UnkMotion3_Phys`, `itKyasarinegg_UnkMotion3_Coll`, `it_802EFCC0`, `itKyasarinegg_UnkMotion1_Phys`, `itKyasarinegg_UnkMotion1_Coll`, `it_802EFD84`, `itKyasarinegg_UnkMotion4_Anim`, `it_damage_inline`, `it_2725_Logic28_DmgDealt`, `it_2725_Logic28_Clanked`, `it_2725_Logic28_HitShield`, `it_2725_Logic28_Reflected`, `itKyasarinEgg_Logic28_ShieldBounced`, `it_802F022C`, `it_802F0320`

## `src/melee/it/kinds/itkyasarinegg.h`

30 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itleadead.c`

1145 linhas; 85 definições aparentes; 0 marcadores asm.

Includes: `itleadead.h`, `Runtime/platform.h`, `math.h`, `placeholder.h`, `inlines.h`, `melee/cm/camera.h`, `melee/ft/ftCo_800C7590.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/lb/lb_00B0.h`, `melee/mp/mpcoll.h`, `melee/mp/mplib.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802E8BCC`, `it_802E8CD8`, `it_802E8F24_inline`, `it_802E8F24`, `itLeadead_UnkMotion1_Anim`, `itLeadead_UnkMotion1_Phys`, `itLeadead_UnkMotion1_Coll`, `it_802E9038`, `itLeadead_UnkMotion2_Anim_inline`, `itLeadead_UnkMotion2_Anim`, `itLeadead_UnkMotion2_Phys`, `itLeadead_UnkMotion2_Coll`, `it_802E9308_inline`, `it_802E9308`, `itLeadead_UnkMotion10_Anim`, `itLeadead_UnkMotion10_Phys`, `itLeadead_UnkMotion10_Coll`, `it_802E93C8`, `it_802E9494`, `itLeadead_UnkMotion11_Anim`, `itLeadead_UnkMotion12_Anim`, `itLeadead_UnkMotion12_Phys`, `itLeadead_UnkMotion12_Coll`, `it_802E9738`, `itLeadead_UnkMotion7_Anim`, `itLeadead_UnkMotion7_Phys`, `itLeadead_UnkMotion7_Coll`, `it_802E98E0`, `itLeadead_UnkMotion8_Anim`, `itLeadead_UnkMotion8_Phys`, `itLeadead_UnkMotion8_Coll`, `it_802E9A00`, `itLeadead_UnkMotion9_Anim`, `itLeadead_UnkMotion9_Phys`, `itLeadead_UnkMotion9_Coll`, `it_802E9BA0`, `itLeadead_UnkMotion3_Anim_inline`, `itLeadead_UnkMotion3_Anim`, `itLeadead_UnkMotion3_Phys`, `itLeadead_UnkMotion3_Coll`, `it_802E9D50`, `itLeadead_UnkMotion4_Anim`, `itLeadead_UnkMotion4_Phys`, `itLeadead_UnkMotion4_Coll_inline`, `itLeadead_UnkMotion4_Coll`, `itLeadead_UnkMotion5_Anim`, `itLeadead_UnkMotion5_Phys`, `itLeadead_UnkMotion5_Coll`, `itLeadead_UnkMotion6_Anim`, `itLeadead_UnkMotion6_Phys`, `itLeadead_UnkMotion6_Coll`, `itLeadead_Logic1_PickedUp`, `itLeadead_UnkMotion13_Anim`, `itLeadead_UnkMotion13_Phys`, `itLeadead_Logic1_Dropped`, `itLeadead_Logic1_Thrown`, `itLeadead_UnkMotion14_Anim`, `itLeadead_UnkMotion14_Phys`, `itLeadead_UnkMotion14_Coll`, `it_802EA2A0`, `itLeadead_UnkMotion15_Anim`, `itLeadead_UnkMotion15_Phys`, `itLeadead_UnkMotion15_Coll`, `it_802EA334`, `itLeadead_UnkMotion16_Anim`, `itLeadead_UnkMotion16_Phys`, `itLeadead_UnkMotion16_Coll`, `itLeadead_UnkMotion17_Anim`, `itLeadead_UnkMotion17_Phys`, `itLeadead_UnkMotion17_Coll`, `itLeadead_Logic1_Destroyed`, `it_802EA478`, `it_802EA674`, `it_802EA6F4`, `neg_dot`, `it_802EA804`, `it_802EA988`, `it_802EA9FC`, `it_802EAAEC_inline`, `it_802EAAEC`, `it_802EAC8C`, `it_802EADD8`, `it_802EAE80_inline`, `it_802EAE80`, `it_802EAF28`

## `src/melee/it/kinds/itleadead.h`

90 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlgun.c`

211 linhas; 30 definições aparentes; 0 marcadores asm.

Includes: `itlgun.h`, `stdbool.h`, `inlines.h`, `itlgunray.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `itLGun_Logic16_Spawned`, `it_8028E774`, `it_8028E79C`, `it_8028E7D8`, `itLgun_UnkMotion0_Anim`, `itLgun_UnkMotion0_Phys`, `itLgun_UnkMotion0_Coll`, `it_8028E860`, `itLgun_UnkMotion4_Anim`, `itLgun_UnkMotion1_Phys`, `itLgun_UnkMotion4_Coll`, `itLGun_Logic16_PickedUp`, `itLgun_UnkMotion2_Anim`, `itLgun_UnkMotion2_Phys`, `it_8028E938`, `itLgun_UnkMotion3_Anim`, `itLgun_UnkMotion3_Phys`, `itLGun_Logic16_Dropped`, `itLGun_Logic16_Thrown`, `itLgun_UnkMotion4_Phys`, `itLGun_Logic16_DmgDealt`, `itLGun_Logic16_Clanked`, `itLGun_Logic16_HitShield`, `itLGun_Logic16_Reflected`, `itLGun_Logic16_ShieldBounced`, `itLGun_Logic16_EnteredAir`, `itLgun_UnkMotion5_Anim`, `itLgun_UnkMotion5_Phys`, `itLgun_UnkMotion5_Coll`, `itLGun_Logic16_EvtUnk`

## `src/melee/it/kinds/itlgun.h`

28 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlgunbeam.c`

291 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `itlgunbeam.h`, `melee/it/forward.h`, `math.h`, `placeholder.h`, `inlines.h`, `melee/db/db.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802993E0`, `it_80299528`, `it_802996D0`, `it_802998A0`, `itLgunbeam_UnkMotion0_Anim`, `itLgunbeam_UnkMotion0_Phys`, `itLgunbeam_UnkMotion0_Coll`, `itLGunBeam_Logic39_DmgDealt`, `itLGunBeam_Logic39_Reflected`, `itLGunBeam_Logic39_Clanked`, `itLGunBeam_Logic39_Absorbed`, `itLGunBeam_Logic39_ShieldBounced`, `itLGunBeam_Logic39_HitShield`, `itLGunBeam_Logic39_EvtUnk`

## `src/melee/it/kinds/itlgunbeam.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlgunray.c`

126 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `itlgunray.h`, `placeholder.h`, `stdbool.h`, `inlines.h`, `itfoxlaser.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `it_80298168`, `it_802982AC`, `itLgunray_UnkMotion0_Anim`, `itLgunray_UnkMotion0_Phys`, `itLgunray_UnkMotion0_Coll`, `itLGunRay_Logic35_DmgDealt`, `itLGunRay_Logic35_Clanked`, `itLGunRay_Logic35_HitShield`, `itLGunRay_Logic35_Absorbed`, `itLGunRay_Logic35_Reflected`, `itLGunRay_Logic35_ShieldBounced`, `itLGunRay_Logic35_EvtUnk`

## `src/melee/it/kinds/itlgunray.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlikelike.c`

1383 linhas; 94 definições aparentes; 0 marcadores asm.

Includes: `itlikelike.h`, `Runtime/platform.h`, `melee/it/forward.h`, `placeholder.h`, `inlines.h`, `melee/ft/ftCo_800C78B0.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itcoll.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/lb/lb_00B0.h`, `melee/lb/types.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itSwapVelocity`, `swapVelocity`, `it_802D9A2C`, `it_802D9B78`, `it_802D9BA8`, `it_2725_Logic5_DmgReceived`, `it_802D9DDC`, `itLikelike_UnkMotion0_Anim`, `itLikelike_UnkMotion0_Phys`, `itLikelike_UnkMotion0_Coll`, `itLikelike_UnkMotion7_Anim`, `itLikelike_UnkMotion7_Phys`, `itLikelike_UnkMotion7_Coll`, `it_802DA104`, `itLikelike_UnkMotion1_Anim`, `itLikelike_UnkMotion1_Phys`, `likelikeVelocity`, `itLikelike_UnkMotion1_Coll`, `it_802DA4C0`, `itLikelike_UnkMotion2_Anim`, `itLikelike_UnkMotion2_Phys`, `itLikelike_UnkMotion2_Coll`, `it_802DA8D8`, `it_802DA960`, `it_802DC4BC_ptr`, `it_802DAA10`, `itLikelike_UnkMotion5_Anim`, `itLikelike_UnkMotion5_Phys`, `itLikelike_UnkMotion4_Coll`, `itLikelike_UnkMotion5_Coll`, `it_802DABC0`, `itLikelike_UnkMotion17_Anim`, `itLikelike_UnkMotion17_Phys`, `itLikelike_UnkMotion17_Coll`, `it_802DAD18`, `itLikelike_UnkMotion3_Anim`, `itLikelike_UnkMotion3_Phys`, `itLikelike_UnkMotion3_Coll`, `it_802DAE6C`, `itLikelike_UnkMotion16_Anim`, `itLikelike_UnkMotion16_Phys`, `itLikelike_UnkMotion16_Coll`, `it_802DB074`, `itLikelike_UnkMotion8_Anim`, `itLikelike_UnkMotion8_Phys`, `itLikelike_UnkMotion8_Coll`, `it_802DB358`, `it_802DB398`, `itLikelike_UnkMotion12_Anim`, `itLikelike_UnkMotion12_Phys`, `itLikelike_UnkMotion12_Coll`, `it_802DB5F0`, `itLikelike_UnkMotion9_Anim`, `itLikelike_UnkMotion9_Phys`, `itLikelike_UnkMotion9_Coll`, `it_802DB74C`, `itLikelike_UnkMotion10_Anim`, `itLikelike_UnkMotion10_Phys`, `itLikelike_UnkMotion10_Coll`, `it_802DB8A8`, `itLikelike_UnkMotion13_Anim`, `itLikelike_UnkMotion13_Phys`, `itLikelike_UnkMotion13_Coll`, `it_802DB9F4`, `it_802DBA68`, `it_802DBAF0`, `itLikelike_UnkMotion14_Anim`, `itLikelike_UnkMotion14_Phys`, `itLikelike_UnkMotion14_Coll`, `itLikelike_UnkMotion15_Anim`, `itLikelike_UnkMotion15_Phys`, `itLikelike_UnkMotion15_Coll`, `itLikeLike_Logic5_PickedUp`, `itLikelike_UnkMotion18_Anim`, `itLikelike_UnkMotion18_Phys`, `it_2725_Logic5_Dropped`, `itLikeLike_Logic5_Thrown`, `itLikelike_UnkMotion19_Anim`, `itLikelike_UnkMotion19_Phys`, `itLikelike_UnkMotion19_Coll`, `it_802DC0AC`, `itLikelike_UnkMotion6_Anim`, `itLikelike_UnkMotion6_Phys`, `itLikelike_UnkMotion6_Coll`, `it_802DC310`, `itLikelike_UnkMotion20_Anim`, `itLikelike_UnkMotion20_Phys`, `itLikelike_UnkMotion20_Coll`, `it_802DC3DC`, `itLikelike_UnkMotion21_Anim`, `itLikelike_UnkMotion21_Phys`, `itLikelike_UnkMotion21_Coll`, `itLikeLike_Logic5_Destroyed`, `it_802DC4BC`

## `src/melee/it/kinds/itlikelike.h`

99 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlinkarrow.c`

863 linhas; 43 definições aparentes; 0 marcadores asm.

Includes: `itlinkarrow.h`, `math.h`, `inlines.h`, `melee/db/db.h`, `melee/ef/efsync.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftCommon/ftCo_Guard.h`, `melee/ft/kinds/ftKirby/ftkirby.h`, `melee/ft/kinds/ftLink/ftlinkspecialn.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itcoll.h`, `melee/it/itdraw.h`, `melee/it/iteffect.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/mp/mpcoll.h`, `melee/mp/mplib.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/mtx.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `sdata2_order`, `it_802A7D8C`, `it_802A7E40`, `itLinkArrow_802A81C4`, `it_802A8330`, `it_802A8398`, `it_802A83E0`, `itLinkArrow_802A850C_inline`, `itLinkArrow_802A850C_inline_2`, `itLinkArrow_802A850C`, `itLinkArrow_Logic98_Destroyed`, `it_802A8A7C`, `itLinkArrow_Logic98_PickedUp`, `itLinkarrow_UnkMotion1_Anim_inline_s_2`, `itLinkarrow_UnkMotion0_Anim`, `itLinkarrow_UnkMotion0_Phys`, `itLinkarrow_UnkMotion0_Coll`, `it_802A8C7C`, `it_802A8330_inline`, `itLinkarrow_UnkMotion1_Anim_inline`, `itLinkarrow_UnkMotion1_Anim_inline2`, `itLinkarrow_UnkMotion1_Anim`, `itLinkarrow_UnkMotion1_Phys`, `itLinkarrow_UnkMotion1_Coll_inline`, `itLinkarrow_UnkMotion1_Coll`, `itLinkarrow_UnkMotion2_Anim`, `itLinkarrow_UnkMotion2_Phys`, `itLinkarrow_UnkMotion2_Coll`, `itLinkarrow_UnkMotion3_Anim`, `itLinkarrow_UnkMotion3_Phys`, `itLinkarrow_UnkMotion3_Coll`, `it_802A9458`, `itlinkarrow_inline_bool`, `itLinkarrow_UnkMotion4_Anim`, `itLinkarrow_UnkMotion4_Phys`, `itLinkarrow_UnkMotion4_Coll_inline`, `itLinkarrow_UnkMotion4_Coll`, `itLinkArrow_Logic98_DmgDealt`, `itLinkArrow_Logic98_HitShield_inline`, `itLinkArrow_Logic98_HitShield`, `itLinkArrow_Logic98_Clanked`, `itLinkArrow_Logic98_Reflected`, `itLinkArrow_Logic98_EvtUnk`

## `src/melee/it/kinds/itlinkarrow.h`

47 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlinkbomb.c`

697 linhas; 48 definições aparentes; 0 marcadores asm.

Includes: `itlinkbomb.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `melee/ft/kinds/ftLink/ftlinkattackair.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/lb/lb_00F9.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `order_sdata2`, `it_8029D968`, `it_8029D9A4`, `it_8029DB5C_Inline_AnimAddWithMtxDirty`, `it_8029DB5C_Inline_Matching`, `it_8029DB5C_Inline_AnimAdd_Part`, `it_8029DB5C_Inline_TimerCheck_Part`, `it_8029DB5C`, `it_8029DD58_inline`, `it_8029DD58`, `it_8029DEB0`, `itLinkbomb_UnkMotion0_Anim`, `itLinkbomb_UnkMotion0_Phys`, `fn_8029E21C`, `itLinkbomb_UnkMotion1_Anim`, `itLinkbomb_UnkMotion1_Phys`, `itLinkbomb_UnkMotion1_Coll`, `it_8029E5D0`, `itLinkbomb_UnkMotion2_Anim`, `itLinkbomb_UnkMotion2_Phys`, `it_LinkBomb_Inline_VelocityCompare`, `itLinkbomb_UnkMotion2_Coll`, `it_8029EC34`, `itLinkbomb_UnkMotion3_Anim_inline1`, `itLinkbomb_UnkMotion3_Anim_inline2`, `itLinkbomb_UnkMotion3_Anim`, `itLinkbomb_UnkMotion3_Phys`, `itLinkbomb_UnkMotion3_Coll`, `fsign_inline`, `float_sign_int_inline`, `it_8029F18C`, `itLinkbomb_UnkMotion4_Anim`, `itLinkbomb_UnkMotion4_Phys`, `itLinkbomb_UnkMotion4_Coll`, `it_8029F69C`, `itLinkbomb_UnkMotion5_Anim`, `itLinkbomb_UnkMotion5_Phys`, `itLinkbomb_UnkMotion5_Coll`, `it_8029F960`, `itLinkBomb_Logic16_DmgReceived`, `itLinkBomb_Logic16_EnteredAir`, `itLinkbomb_UnkMotion6_Anim`, `itLinkbomb_UnkMotion6_Phys`, `itLinkbomb_UnkMotion6_Coll`, `itLinkBomb_Logic16_Reflected`, `itLinkBomb_Logic16_HitShield`, `itLinkBomb_Logic16_ShieldBounced`, `it_8029FD84`

## `src/melee/it/kinds/itlinkbomb.h`

51 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlinkboomerang.c`

925 linhas; 54 definições aparentes; 0 marcadores asm.

Includes: `itlinkboomerang.h`, `placeholder.h`, `inlines.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftLink/ftlinkspecialhi.h`, `melee/ft/kinds/ftLink/ftlinkspecials.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCharItems.h`, `melee/it/itdraw.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/mtx.h`

Definições aparentes: `norm_xF74`, `norm_xF74_from_angle`, `remove_boomerang`, `it_8029FDBC`, `it_8029FDDC`, `it_8029FE64`, `it_802A013C_inline`, `it_802A013C_LoadAnim`, `it_802A013C`, `loop_lb_8000BA0C_gobj`, `loop_lb_8000BA0C_gobj_1`, `it_802A0534`, `it_802A07B4`, `it_802A0810`, `itLinkBoomerang_Logic18_Destroyed`, `it_802A0930`, `it_8029FE64_no_inline`, `it_802A0C34_sub_1`, `it_802A0C34_sub_2`, `it_802A0C34`, `it_802A0E70`, `itLinkboomerang_UnkMotion0_Anim`, `it_802A0F84`, `it_802A0F88`, `itLinkboomerang_UnkMotion1_Anim`, `itLinkboomerang_get_x18`, `itLinkboomerang_UnkMotion1_Phys`, `itLinkboomerang_UnkMotion1_Coll`, `it_802A10E4`, `itLinkboomerang_UnkMotion2_Anim`, `itLinkboomerang_UnkMotion2_Phys`, `clamp_tau`, `clamp_pi_tau`, `it_802A13EC_inline`, `it_802A13EC`, `it_802A15EC`, `it_802A15EC_no_inline`, `itLinkboomerang_UnkMotion2_Coll`, `it_802A19E0_no_inline`, `clamp_angle_pi`, `it_802A1948`, `it_802A19E0`, `itLinkboomerang_UnkMotion3_Anim`, `itLinkboomerang_UnkMotion3_Phys_sub`, `itLinkboomerang_UnkMotion3_Phys_add_clamp`, `itLinkboomerang_UnkMotion3_Phys`, `it_802A1F08`, `it_802A1FA8`, `itLinkBoomerang_Logic18_Absorbed`, `it_802A20E8_inline`, `it_802A20E8`, `it_802A2288`, `it_802A2320`, `it_802A23CC`

## `src/melee/it/kinds/itlinkboomerang.h`

48 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlinkbow.c`

270 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `itlinkbow.h`, `inlines.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftKirby/ftkirby.h`, `melee/ft/kinds/ftLink/ftlinkspecialn.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `it_802AF1A4`, `itLinkBow_Logic100_Destroyed`, `it_802AF304`, `it_802AF32C`, `itLinkBow_Logic100_PickedUp`, `itLinkbow_UnkMotion5_Anim`, `itLinkbow_UnkMotion5_Phys`, `itLinkbow_UnkMotion5_Coll`, `itLinkbow_UnkMotion6_Anim`, `itLinkbow_UnkMotion6_Phys`, `itLinkbow_UnkMotion6_Coll`, `itLinkBow_Logic100_EvtUnk`

## `src/melee/it/kinds/itlinkbow.h`

17 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlinkhookshot.c`

2273 linhas; 93 definições aparentes; 0 marcadores asm.

Includes: `itlinkhookshot.h`, `math.h`, `placeholder.h`, `inlines.h`, `dolphin/mtx.h`, `dolphin/types.h`, `melee/ef/efsync.h`, `melee/ft/ft_081B.h`, `melee/ft/ftcliffcommon.h`, `melee/ft/ftcoll.h`, `melee/ft/ftcommon.h`, `melee/ft/ftparts.h`, `melee/ft/inlines.h`, `melee/ft/kinds/ftCommon/ftCo_AirCatch.h`, `melee/ft/kinds/ftCommon/ftCo_CliffJump.h`, `melee/ft/kinds/ftCommon/ftCo_DamageFall.h`, `melee/it/inlines.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbvector.h`, `melee/mp/mpcoll.h`, `melee/mp/mpisland.h`, `melee/mp/mplib.h`, `melee/mp/types.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `sdata2_order`, `it_802A2418`, `it_802A2428`, `it_802A2474`, `it_802A24A0`, `it_802A24D0`, `link_fighter_compare`, `it_802A2568_inline`, `it_link_get_joint`, `it_link_get_joint_c`, `it_link_lerp`, `it_link_attr_math`, `it_802A2568`, `it_802A2B10`, `it_802A2BA4`, `itLinkhookshot_UnkMotion8_Anim`, `fn_802A2E4C`, `itLinkhookshot_UnkMotion0_Phys`, `it_802A2EE4_inline`, `it_802A2EE4_inline_alt`, `it_802A2EE4_inline_alt_mtx_first`, `it_802A2EE4_inline_alt_pad`, `it_802A2EE4`, `itLinkhookshot_UnkMotion1_Phys`, `mtx_reset`, `vec3_eq_mtx`, `fn_802A3110_inline`, `fn_802A3110`, `itLinkhookshot_UnkMotion2_Phys`, `it_802A3254`, `itLinkhookshot_UnkMotion3_Phys`, `fn_802A33A0_GetFighter`, `fn_802A33A0`, `itLinkhookshot_UnkMotion4_Phys`, `it_802A3500`, `itLinkhookshot_UnkMotion5_Phys`, `it_802A3630`, `itLinkhookshot_UnkMotion6_Phys`, `it_802A3828`, `itLinkhookshot_UnkMotion7_Phys`, `it_802A39FC`, `itLinkhookshot_UnkMotion8_Phys`, `it_802A3C98`, `it_802A3D90`, `it_802A3E50`, `it_802A40D0`, `it_802A42F4`, `it_802A43B8`, `it_802A43EC`, `it_802A4420`, `it_802A4454`, `it_802A44CC`, `test_comp`, `it_802A4758_permuterslop`, `it_802A4758`, `it_802A49B0`, `it_802A6A78_normalize_diff`, `it_802A4BFC_sqrtf_offset`, `it_802A4BFC_normalize_diff`, `it_802A4BFC`, `it_802A5320`, `it_802A5770_inline`, `it_802A5770`, `it_802A5AE0`, `it_802A5E28`, `it_802A5FE0`, `it_802A4758_no_inline`, `it_802A6474`, `it_802A678C`, `it_802A6944`, `it_802A6A78_get_next`, `it_802A6A78_get_pos`, `it_802A6A78_normalize_diff_rev`, `it_802A6A78`, `it_802A6DC8`, `it_802A6F80`, `it_802A7168`, `it_802A7384`, `itLinkHookshot_Logic20_PickedUp_inline`, `itLinkHookshot_Logic20_PickedUp`, `it_802A76EC`, `it_802A7764`, `it_802A77DC`, `it_802A7840`, `it_802A78B8`, `it_802A793C`, `it_802A79A0`, `it_802A7A04`, `it_802A7AAC`, `it_802A7AF0`, `it_802A7B34_6944_inline`, `it_802A7B34`, `it_802A7D40`

## `src/melee/it/kinds/itlinkhookshot.h`

107 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/itCharItems.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/kinds/itlipstick.c`

214 linhas; 29 definições aparentes; 0 marcadores asm.

Includes: `itlipstick.h`, `forward.h`, `itlipstickspore.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`

Definições aparentes: `itLipstick_Logic23_Spawned`, `it_80295748`, `it_80295770`, `it_802957AC`, `itLipstick_UnkMotion0_Anim`, `itLipstick_UnkMotion0_Phys`, `itLipstick_UnkMotion0_Coll`, `it_8029583C`, `itLipstick_UnkMotion4_Anim`, `itLipstick_UnkMotion1_Phys`, `itLipstick_UnkMotion1_Coll`, `itLipstick_Logic23_PickedUp`, `itLipstick_UnkMotion2_Anim`, `itLipstick_UnkMotion2_Phys`, `itLipstick_Logic23_Dropped`, `itLipstick_UnkMotion4_Coll`, `itLipstick_Logic23_Thrown`, `itLipstick_UnkMotion4_Phys`, `itLipstick_UnkMotion3_Coll`, `itLipstick_Logic23_DmgDealt`, `itLipstick_Logic23_EnteredAir`, `itLipstick_UnkMotion5_Anim`, `itLipstick_UnkMotion5_Phys`, `itLipstick_UnkMotion5_Coll`, `itLipstick_Logic23_Clanked`, `itLipstick_Logic23_Reflected`, `itLipstick_Logic23_HitShield`, `itLipstick_Logic23_ShieldBounced`, `itLipstick_Logic23_EvtUnk`

## `src/melee/it/kinds/itlipstick.h`

42 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlipstickspore.c`

236 linhas; 17 definições aparentes; 0 marcadores asm.

Includes: `itlipstickspore.h`, `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `math.h`, `placeholder.h`, `inlines.h`, `melee/db/db.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `it_8029A114`, `it_8029A218`, `it_8029A31C`, `it_8029A498`, `itLipstickspore_UnkMotion0_Anim`, `itLipstickspore_UnkMotion0_Phys`, `itLipstickspore_UnkMotion0_Coll`, `itLipstickspore_UnkMotion1_Anim`, `itLipstickspore_UnkMotion1_Phys`, `itLipstickspore_UnkMotion1_Coll`, `itLipstickSpore_Logic37_DmgDealt`, `itLipstickSpore_Logic37_Clanked`, `itLipstickSpore_Logic37_HitShield`, `itLipstickSpore_Logic37_Absorbed`, `itLipstickSpore_Logic37_Reflected`, `itLipstickSpore_Logic37_ShieldBounced`, `itLipstickSpore_Logic37_EvtUnk`

## `src/melee/it/kinds/itlipstickspore.h`

39 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlizardon.c`

464 linhas; 36 definições aparentes; 0 marcadores asm.

Includes: `itlizardon.h`, `Runtime/platform.h`, `melee/it/forward.h`, `math.h`, `placeholder.h`, `inlines.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lb_00B0.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802CB8AC`, `it_802CB93C`, `it_802CB940`, `it_802CB960`, `it_802CB994`, `itLizardon_UnkMotion1_Anim`, `itLizardon_UnkMotion1_Phys`, `itLizardon_UnkMotion1_Coll`, `it_802CBAA8_inline`, `it_802CBAA8`, `itLizardon_UnkMotion2_Anim`, `itLizardon_UnkMotion2_Phys`, `itLizardon_UnkMotion2_Coll`, `it_802CBD24_inline`, `it_802CBD24`, `it_802CBFE4`, `itLizardon_UnkMotion3_Anim`, `itLizardon_UnkMotion3_Phys`, `itLizardon_UnkMotion3_Coll`, `it_802CC0EC`, `it_802CC160`, `it_802CC184`, `it_802CC1A4`, `it_802CC1CC`, `itLizardon_Logic34_Spawned`, `itLizardon_Logic35_Spawned`, `itLizardon_Logic36_Spawned`, `itLizardon_Logic37_Spawned`, `itLizardon_Logic37_EvtUnk`, `itLizardon_Logic37_Reflected`, `itLizardon_Logic37_HitShield`, `itLizardon_Logic37_Absorbed`, `it_802CC5D4`, `it_802CC650`, `it_802CC684`, `it_802CC6C4`

## `src/melee/it/kinds/itlizardon.h`

47 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlucky.c`

448 linhas; 45 definições aparentes; 0 marcadores asm.

Includes: `itlucky.h`, `Runtime/platform.h`, `melee/it/forward.h`, `placeholder.h`, `itegg.h`, `melee/ef/eflib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itspawn.h`, `melee/lb/lb_00B0.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802D5050`, `it_802D50F0`, `it_802D5124`, `it_802D51C8`, `it_802D52E4`, `it_802D533C_inline`, `it_802D533C`, `it_802D53AC`, `it_802D53F0`, `it_802D53F4`, `it_802D5420`, `it_802D546C_inline`, `it_802D546C`, `itLucky_UnkMotion5_Anim`, `itLucky_UnkMotion5_Phys`, `itLucky_UnkMotion5_Coll`, `itLucky_UnkMotion6_Anim`, `itLucky_UnkMotion6_Phys`, `it_802D5560`, `it_802D55DC`, `it_802D5600`, `it_802D5620`, `it_802D5648_inline`, `it_802D5648`, `it_802D56F0`, `it_802D5710_inline`, `it_802D5710`, `itLucky_Logic44_Spawned`, `it_802D582C`, `it_802D5884`, `it_802D58BC`, `it_802D58C0`, `it_802D58EC`, `itLucky_UnkMotion3_Anim`, `itLucky_UnkMotion3_Phys`, `itLucky_UnkMotion3_Coll`, `itLucky_Logic44_PickedUp`, `itLucky_UnkMotion2_Anim`, `itLucky_UnkMotion2_Phys`, `itLucky_Logic44_Dropped`, `itLucky_Logic44_EnteredAir`, `it_802D5A2C`, `it_802D5A64`, `it_802D5A68`, `itLucky_Logic44_EvtUnk`

## `src/melee/it/kinds/itlucky.h`

55 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itlugia.c`

555 linhas; 41 definições aparentes; 0 marcadores asm.

Includes: `itlugia.h`, `math.h`, `placeholder.h`, `inlines.h`, `melee/ef/eflib.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `my_sqrtf`, `my_sqrtf_accurate`, `it_2725_Logic17_Spawned`, `it_802D14D0`, `itLugia_Logic17_EvtUnk`, `itLugia_UnkMotion1_Anim`, `itLugia_UnkMotion1_Phys`, `itLugia_UnkMotion1_Coll`, `it_802D1580`, `itLugia_UnkMotion2_Anim`, `itLugia_UnkMotion2_Phys`, `itLugia_UnkMotion2_Coll`, `it_802D16D4`, `itLugia_UnkMotion3_Anim`, `itLugia_UnkMotion3_Phys`, `itLugia_UnkMotion3_Coll`, `it_802D1830`, `itLugia_UnkMotion4_Anim`, `itLugia_UnkMotion4_Phys`, `itLugia_UnkMotion4_Coll`, `it_802D1A44`, `itLugia_UnkMotion5_Anim`, `itLugia_UnkMotion5_Phys`, `itLugia_UnkMotion5_Coll`, `it_802D1BBC`, `it_802D1D40`, `it_802D1DB4`, `it_802D1DD8`, `it_802D1E64`, `it_802D1E8C`, `it_802D208C_inline`, `it_802D1F64`, `it_802D208C`, `itLugia_Logic39_Spawned`, `itLugia_Logic40_Spawned`, `itLugia_Logic41_Spawned`, `it_802D23D4`, `it_802D23F4`, `it_802D246C`, `it_802D24A0`, `it_802D24FC`

## `src/melee/it/kinds/itlugia.h`

49 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itluigifireball.c`

127 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `itluigifireball.h`, `Runtime/platform.h`, `inlines.h`, `dolphin/mtx.h`, `melee/db/db.h`, `melee/ef/efasync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/mtx.h`

Definições aparentes: `it_802C01AC`, `it_802C027C`, `itLuigifireball_UnkMotion0_Anim`, `itLuigifireball_UnkMotion0_Phys`, `calc_dist_2d_accurate`, `itLuigifireball_UnkMotion0_Coll`, `itLuigiFireball_Logic89_DmgDealt`, `itLuigiFireball_Logic89_Reflected`, `itLuigiFireball_Logic89_Clanked`, `itLuigiFireball_Logic89_HitShield`, `itLuigiFireball_Logic89_Absorbed`, `itLuigiFireball_Logic89_ShieldBounced`, `itLuigiFireball_Logic89_EvtUnk`

## `src/melee/it/kinds/itluigifireball.h`

23 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmaril.c`

293 linhas; 31 definições aparentes; 0 marcadores asm.

Includes: `itmaril.h`, `ithinoarashi.h`, `melee/ef/eflib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/lb/lbvector.h`

Definições aparentes: `itMaril_UnkMotion2_Anim_inline`, `it_802D66F8`, `it_802D6740`, `it_802D6798`, `it_802D6808`, `it_802D6810`, `it_802D6830`, `it_802D6838`, `it_802D6840`, `it_802D6848`, `it_802D6850`, `itMaril_Logic28_Spawned`, `it_802D68FC`, `itMaril_UnkMotion1_Coll_inline`, `itMaril_UnkMotion0_Anim`, `itMaril_UnkMotion0_Phys`, `itMaril_UnkMotion0_Coll`, `it_802D69E4`, `it_802D6A54`, `itMaril_UnkMotion1_Anim`, `itMaril_UnkMotion1_Phys`, `itMaril_UnkMotion1_Coll`, `it_802D6DDC`, `itMaril_UnkMotion2_Anim`, `itMaril_UnkMotion2_Phys`, `itMaril_UnkMotion2_Coll`, `itMaril_UnkMotion3_Anim`, `itMaril_UnkMotion3_Phys`, `it_802D6F00_inline`, `it_802D6F00`, `it_802D6FB0`

## `src/melee/it/kinds/itmaril.h`

40 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmariocape.c`

129 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `itmariocape.h`, `inlines.h`, `melee/ef/efasync.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftMario/ftmariospecials.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`

Definições aparentes: `it_802B2560`, `itMarioCape_Logic41_Destroyed`, `it_802B2674`, `it_802B26C0`, `it_802B26E0`, `it_2725_Logic41_PickedUp`, `inlineA0`, `reset`, `itMariocape_UnkMotion1_Anim`, `it_802B2870`

## `src/melee/it/kinds/itmariocape.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmariofireball.c`

125 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `itmariofireball.h`, `math.h`, `inlines.h`, `dolphin/mtx.h`, `melee/db/db.h`, `melee/ef/efasync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/mtx.h`

Definições aparentes: `it_8029B6F8`, `it_8029B7C0`, `itMariofireball_UnkMotion0_Anim`, `itMariofireball_UnkMotion0_Phys`, `calc_dist_2d_accurate`, `itMariofireball_UnkMotion0_Coll`, `itMarioFireball_Logic87_DmgDealt`, `itMarioFireball_Logic87_Reflected`, `itMarioFireball_Logic87_Clanked`, `itMarioFireball_Logic87_HitShield`, `itMarioFireball_Logic87_Absorbed`, `itMarioFireball_Logic87_ShieldBounced`, `itMarioFireball_Logic87_EvtUnk`

## `src/melee/it/kinds/itmariofireball.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmarumine.c`

394 linhas; 37 definições aparentes; 0 marcadores asm.

Includes: `itmarumine.h`, `inlines.h`, `dolphin/mtx.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/types.h`, `melee/lb/lb_00B0.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `it_802D09D0`, `itMarumine_Logic16_Spawned`, `it_802D0AAC`, `it_802D0AB0`, `it_802D0AD0`, `it_802D0B04`, `itMarumine_UnkMotion1_Anim`, `itMarumine_UnkMotion1_Phys`, `itMarumine_UnkMotion1_Coll`, `it_802D0C44`, `itMarumine_UnkMotion2_Anim`, `itMarumine_UnkMotion2_Phys`, `itMarumine_UnkMotion2_Coll`, `it_802D0D18`, `itMarumine_UnkMotion3_Anim`, `itMarumine_UnkMotion3_Phys`, `itMarumine_UnkMotion3_Coll`, `it_802D0DBC`, `it_802D0E30`, `it_802D0E90`, `itMarumine_UnkMotion4_Anim`, `itMarumine_UnkMotion4_Phys`, `itMarumine_UnkMotion4_Coll`, `fn_802D0F98`, `it_802D100C`, `itMarumine_UnkMotion5_Anim`, `itMarumine_UnkMotion5_Phys`, `itMarumine_UnkMotion5_Coll`, `it_802D1140`, `it_802D1204`, `itMarumine_UnkMotion6_Anim`, `itMarumine_UnkMotion6_Phys`, `itMarumine_UnkMotion6_Coll`, `it_802D1320`, `itMarumine_UnkMotion0_Anim`, `itMarumine_UnkMotion0_Phys`, `itMarumine_UnkMotion0_Coll`

## `src/melee/it/kinds/itmarumine.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmasterhandbullet.c`

152 linhas; 16 definições aparentes; 0 marcadores asm.

Includes: `itmasterhandbullet.h`, `Runtime/platform.h`, `dolphin/mtx.h`, `melee/db/db.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802F0AE0_sub`, `it_802F0AE0`, `itMasterHandBullet_Logic85_EvtUnk`, `it_802F0BE8`, `it_802F0D2C`, `itMasterhandbullet_UnkMotion1_Anim`, `itMasterhandbullet_UnkMotion1_Phys`, `itMasterhandbullet_UnkMotion1_Coll`, `it_802F0F04`, `it_802F0F08`, `itMasterHandBullet_Logic83_DmgDealt`, `itMasterHandBullet_Logic83_Reflected`, `itMasterHandBullet_Logic83_Clanked`, `itMasterHandBullet_Logic83_Absorbed`, `itMasterHandBullet_Logic83_ShieldBounced`, `itMasterHandBullet_Logic83_HitShield`

## `src/melee/it/kinds/itmasterhandbullet.h`

28 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmasterhandlaser.c`

200 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `itmasterhandlaser.h`, `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `inlines.h`, `melee/db/db.h`, `melee/ef/efsync.h`, `melee/ft/inlines.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/ithitbox.h`, `melee/it/types.h`, `melee/lb/lb_00B0.h`, `melee/mp/mplib.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `sqrtf_store`, `it_802F0340`, `itMasterHandLaser_Logic84_EvtUnk`, `it_802F046C`, `it_802F0484`, `itMasterhandlaser_UnkMotion0_Anim`, `itMasterhandlaser_UnkMotion0_Phys`, `itMasterhandlaser_UnkMotion0_Coll`, `it_802F05A8`, `it_802F063C`

## `src/melee/it/kinds/itmasterhandlaser.h`

22 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmatadogas.c`

265 linhas; 22 definições aparentes; 0 marcadores asm.

Includes: `itmatadogas.h`, `math.h`, `inlines.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802CAFD4`, `it_802CB0F4`, `it_802CB0F8`, `it_802CB118`, `it_802CB14C`, `it_802CB150`, `itMatadogas_UnkMotion1_Anim`, `itMatadogas_UnkMotion1_Phys`, `itMatadogas_UnkMotion1_Coll`, `it_802CB2B0`, `it_802CB350`, `itMatadogas_UnkMotion2_Anim`, `itMatadogas_UnkMotion2_Phys`, `itMatadogas_UnkMotion2_Coll`, `it_802CB4F0`, `it_2725_Logic32_Spawned`, `it_2725_Logic33_Spawned`, `itMatadogas_Logic33_EvtUnk`, `it_802CB798`, `it_802CB810`, `it_802CB844`, `it_802CB8A4`

## `src/melee/it/kinds/itmatadogas.h`

33 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmato.c`

64 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `itmato.h`, `Runtime/platform.h`, `dolphin/mtx.h`, `melee/gr/ground.h`, `melee/it/inlines.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itzako.h`, `melee/it/types.h`, `melee/lb/lb_00B0.h`

Definições aparentes: `it_802D84F8`, `it_802D8554`, `itMato_UnkMotion0_Anim`, `itMato_UnkMotion0_Phys`, `itMato_UnkMotion0_Coll`, `it_802D85F4`

## `src/melee/it/kinds/itmato.h`

18 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmball.c`

304 linhas; 36 definições aparentes; 0 marcadores asm.

Includes: `itmball.h`, `Runtime/platform.h`, `forward.h`, `dolphin/mtx.h`, `melee/ef/efasync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/it/types.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itMball_Destroyed`, `itMball_Spawned`, `itMball_80297944`, `itMball_Motion0_Anim`, `itMball_Motion0_Phys`, `itMball_Motion0_Coll`, `itMball_802979D4`, `itMball_Motion3_Anim`, `itMball_Motion1_Phys`, `itMball_Motion1_Coll`, `itMball_PickedUp`, `itMball_Motion2_Anim`, `itMball_Motion2_Phys`, `itMball_Dropped`, `itMball_Thrown`, `itMball_Motion3_Phys`, `itMball_Motion3_Coll`, `itMball_DmgDealt`, `itMball_EnteredAir`, `itMball_Motion4_Anim`, `itMball_Motion4_Phys`, `itMball_Motion4_Coll`, `itMball_80297CC4`, `itMball_OnAccessory`, `itMball_Motion5_Anim`, `itMball_Motion5_Phys`, `itMball_Motion5_Coll`, `itMball_80297E8C`, `itMball_Motion6_Anim`, `itMball_Motion6_Phys`, `itMball_Motion6_Coll`, `itMball_Clanked`, `itMball_Reflected`, `itMball_HitShield`, `itMball_ShieldBounced`, `itMball_EvtUnk`

## `src/melee/it/kinds/itmball.h`

48 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmetalb.c`

158 linhas; 20 definições aparentes; 0 marcadores asm.

Includes: `itmetalb.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/pl/plbonuslib.h`

Definições aparentes: `itMetalB_Logic32_Spawned`, `it_802953FC`, `itMetalb_UnkMotion0_Anim`, `itMetalb_UnkMotion0_Phys`, `itMetalb_UnkMotion0_Coll`, `it_80295498`, `itMetalb_UnkMotion3_Anim`, `itMetalb_UnkMotion1_Phys`, `itMetalb_UnkMotion1_Coll`, `itMetalB_Logic32_PickedUp`, `itMetalb_UnkMotion2_Anim`, `itMetalB_Logic32_Dropped`, `itMetalb_UnkMotion3_Phys`, `itMetalb_UnkMotion3_Coll`, `itMetalB_Logic32_DmgReceived`, `itMetalB_Logic32_EnteredAir`, `itMetalb_UnkMotion4_Anim`, `itMetalb_UnkMotion4_Phys`, `itMetalb_UnkMotion4_Coll`, `itMetalB_Logic32_EvtUnk`

## `src/melee/it/kinds/itmetalb.h`

32 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmetamon.c`

121 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `itmetamon.h`, `Runtime/platform.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`

Definições aparentes: `it_802D3008`, `it_802D306C`, `itMetamon_Logic19_EvtUnk`, `it_802D3090`, `it_802D30C4`, `itMetamon_UnkMotion0_Anim`, `itMetamon_UnkMotion0_Phys`, `itMetamon_UnkMotion0_Coll`, `itMetamon_UnkMotion1_Anim`, `itMetamon_UnkMotion1_Phys`, `itMetamon_UnkMotion1_Coll`, `it_802D31B4`, `itMetamon_UnkMotion2_Anim`, `itMetamon_UnkMotion2_Phys`, `itMetamon_UnkMotion2_Coll`

## `src/melee/it/kinds/itmetamon.h`

27 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmew.c`

149 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `itmew.h`, `inlines.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itMew_Logic22_Spawned`, `it_802D3B6C`, `it_802D3B8C`, `it_802D3BE0`, `itMew_UnkMotion1_Anim`, `itMew_UnkMotion1_Phys`, `itMew_UnkMotion1_Coll`, `it_802D3C9C`, `itMew_UnkMotion2_Anim`, `itMew_UnkMotion2_Phys`, `itMew_UnkMotion2_Coll`, `it_802D3D94`, `itMew_UnkMotion0_Anim`, `itMew_UnkMotion0_Phys`, `itMew_UnkMotion0_Coll`

## `src/melee/it/kinds/itmew.h`

12 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmewtwodisable.c`

158 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `itmewtwodisable.h`, `Runtime/platform.h`, `melee/it/forward.h`, `melee/db/db.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftMewtwo/ftmewtwospeciallw.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`

Definições aparentes: `itMewtwoDisable_Logic67_Destroy`, `itMewtwoDisable_Logic67_Destroyed`, `itMewtwoDisable_Logic67_SpawnMewtwoDisable`, `it_802C4B38`, `it_802C4BB8`, `itMewtwodisable_UnkMotion0_Anim`, `itMewtwodisable_UnkMotion0_Phys`, `itMewtwodisable_UnkMotion0_Coll`, `itMewtwoDisable_Logic67_DmgDealt`, `itMewtwoDisable_Logic67_Reflected`, `itMewtwoDisable_Logic67_Clanked`, `itMewtwoDisable_Logic67_HitShield`, `itMewtwoDisable_Logic67_Absorbed`, `itMewtwoDisable_Logic67_ShieldBounced`, `itMewtwoDisable_Logic67_EvtUnk`

## `src/melee/it/kinds/itmewtwodisable.h`

29 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmewtwoshadowball.c`

660 linhas; 30 definições aparentes; 0 marcadores asm.

Includes: `itmewtwoshadowball.h`, `inlines.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftKirby/ftkirbyspecialmewtwo.h`, `melee/ft/kinds/ftMewtwo/ftmewtwospecialn.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/mtx.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802C4D10`, `it_802C4F50`, `it_802C5000`, `it_802C519C`, `it_802C53F0`, `it_2725_Logic101_Destroyed`, `it_802C573C`, `it_2725_Logic101_PickedUp`, `itMewtwoshadowball_UnkMotion0_Anim`, `itMewtwoshadowball_UnkMotion0_Phys`, `itMewtwoshadowball_UnkMotion0_Coll`, `it_802C5B18`, `itMewtwoshadowball_UnkMotion8_Anim`, `itMewtwoshadowball_UnkMotion8_Phys`, `itMewtwoshadowball_UnkMotion8_Coll`, `itMewtwoshadowball_UnkMotion9_Anim`, `itMewtwoshadowball_UnkMotion9_Phys`, `itMewtwoshadowball_UnkMotion9_Coll`, `fn_802C5E18`, `it_802C5E5C`, `itMewtwoshadowball_UnkMotion17_Anim`, `itMewtwoshadowball_UnkMotion17_Phys`, `itMewtwoshadowball_UnkMotion17_Coll`, `itMewtwoShadowball_Logic101_DmgDealt`, `itMewtwoShadowball_Logic101_Clanked`, `itMewtwoShadowball_Logic101_Absorbed`, `it_2725_Logic101_Reflected`, `itMewtwoShadowball_Logic101_HitShield`, `it_2725_Logic101_ShieldBounced`, `itMewtwoShadowball_Logic101_EvtUnk`

## `src/melee/it/kinds/itmewtwoshadowball.h`

43 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itmsbomb.c`

330 linhas; 34 definições aparentes; 0 marcadores asm.

Includes: `itmsbomb.h`, `melee/it/forward.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/lb/lb_00F9.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_8028FE90`, `itMSBomb_Logic19_Spawned`, `it_8028FF1C`, `itMsbomb_UnkMotion0_Coll`, `it_8028FF8C`, `itMsbomb_UnkMotion1_Phys`, `itMsbomb_UnkMotion1_Coll`, `itMSBomb_Logic19_PickedUp`, `itMSBomb_Logic19_Dropped`, `itMSBomb_Logic19_Thrown`, `itMsbomb_UnkMotion3_Phys`, `itMsbomb_UnkMotion3_Coll`, `it_80290238`, `it_80290314_inline`, `it_80290314`, `itMsbomb_UnkMotion4_Coll`, `it_8029047C`, `itMsbomb_UnkMotion5_Phys`, `itMsbomb_UnkMotion5_Coll`, `it_802905D8`, `it_80290614`, `itMsbomb_UnkMotion6_Anim`, `itMSBomb_Logic19_DmgDealt`, `itMSBomb_Logic19_DmgReceived_inline`, `itMSBomb_Logic19_DmgReceived`, `itMSBomb_Logic19_EnteredAir`, `itMsbomb_UnkMotion7_Coll`, `itMSBomb_Logic19_Clanked`, `itMSBomb_Logic19_Reflected`, `itMSBomb_Logic19_HitShield`, `itMSBomb_Logic19_ShieldBounced`, `it_802908D8_inline`, `it_802908D8`, `itMSBomb_Logic19_EvtUnk`

## `src/melee/it/kinds/itmsbomb.h`

43 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itnessbat.c`

195 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `itnessbat.h`, `Runtime/platform.h`, `placeholder.h`, `inlines.h`, `melee/ft/ft_0BF0.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftNess/ftnessattacks4.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itNessbat_ClearOwnerRef`, `itNessbat_RemoveItem`, `it_802AD478`, `it_802AD590`, `it_802AD6B8`, `it_2725_Logic58_PickedUp`, `itNessbat_UnkMotion0_Anim`, `itNessbat_UnkMotion0_Phys`, `itNessbat_UnkMotion0_Coll`, `itNessbat_UnkMotion1_Anim`, `itNessbat_UnkMotion1_Phys`, `itNessbat_UnkMotion1_Coll`, `itNessBat_Logic58_EvtUnk`

## `src/melee/it/kinds/itnessbat.h`

22 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itnesspkfire.c`

124 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `itnesspkfire.h`, `Runtime/platform.h`, `melee/it/forward.h`, `placeholder.h`, `inlines.h`, `itnesspkfirepillar.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802AA054`, `it_802AA1D8`, `itNesspkfire_UnkMotion0_Anim`, `itNesspkfire_UnkMotion0_Coll`, `it_2725_Logic23_DmgDealt`, `it_2725_Logic23_Clanked`, `itNessPKFire_Logic23_Absorbed`, `itNessPKFire_Logic23_HitShield`, `itNessPKFire_Logic23_Reflected`, `it_2725_Logic23_ShieldBounced`, `it_802AA474`

## `src/melee/it/kinds/itnesspkfire.h`

24 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itnesspkfirepillar.c`

146 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `itnesspkfirepillar.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `get_min_life`, `itNesspkfirepillar_INLINE_SpawnItem_Init`, `itNesspkfirepillar_802AA494`, `itNesspkfirepillar_802AA55C`, `itNesspkfirepillar_INLINE_Anim_SetScale`, `itNesspkfirepillar_UnkMotion0_Anim`, `itNesspkfirepillar_UnkMotion0_Phys`, `itNesspkfirepillar_UnkMotion0_Coll`, `itNesspkfirepillar_Logic24_DmgReceived`, `itNesspkfirepillar_Logic24_EvtUnk`

## `src/melee/it/kinds/itnesspkfirepillar.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itnesspkflash.c`

382 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `itnesspkflash.h`, `Runtime/platform.h`, `melee/it/forward.h`, `math.h`, `placeholder.h`, `inlines.h`, `itnesspkflashexplode.h`, `melee/db/db.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftKirby/ftkirby.h`, `melee/ft/kinds/ftNess/ftnessspecialn.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itNesspkflash_SetScale`, `it_802AA7E4`, `it_802AA7F0`, `it_802AA810`, `it_802AA8C0`, `it_2725_Logic102_Destroyed`, `it_802AAA50`, `it_802AAA80`, `itNesspkflash_UnkMotion0_Anim`, `itNesspkflash_UnkMotion1_Anim`, `itNesspkflash_UnkMotion2_Anim`, `itNesspkflash_UnkMotion0_Phys`, `itNesspkflash_UnkMotion1_Phys`, `itNesspkflash_UnkMotion2_Phys`, `itNesspkflash_UnkMotion0_Coll`, `itNesspkflash_UnkMotion1_Coll`, `itNesspkflash_UnkMotion2_Coll`, `itNesspkflash_Logic102_Reflected`, `itNesspkflash_Logic102_Clanked`, `itNesspkflash_Logic102_Absorbed`, `itNesspkflash_Logic102_EvtUnk`

## `src/melee/it/kinds/itnesspkflash.h`

32 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itnesspkflashexplode.c`

163 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `itnesspkflashexplode.h`, `Runtime/platform.h`, `melee/it/forward.h`, `placeholder.h`, `inlines.h`, `melee/cm/camera.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802AF940`, `it_2725_Logic103_Destroyed`, `it_802AFA70`, `itNessPKFlashExplode_UnkMotion0_Anim`, `itNessPKFlashExplode_UnkMotion0_Phys`, `itNessPKFlashExplode_UnkMotion0_Coll`, `itNessPKFlashExplode_Logic103_Clanked`, `itNessPKFlashExplode_Logic103_Absorbed`, `itNessPKFlashExplode_Logic103_ShieldBounced`, `itNessPKFlashExplode_Logic103_HitShield`, `itNessPKFlashExplode_Logic103_EvtUnk`

## `src/melee/it/kinds/itnesspkflashexplode.h`

23 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itnesspkthunderball.c`

444 linhas; 20 definições aparentes; 0 marcadores asm.

Includes: `itnesspkthunderball.h`, `math.h`, `placeholder.h`, `inlines.h`, `itnesspkthundertrail.h`, `melee/db/db.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftNess/ftnessspecialhi.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lbvector.h`

Definições aparentes: `it_802AB3F0`, `it_802AB468`, `it_802AB4B8`, `it_802AB568`, `it_802AB58C`, `it_802AB90C`, `it_802AB9C0`, `it_802ABA4C`, `itNesspkthunderball_UnkMotion0_Anim`, `itNesspkthunderball_ShiftAngles`, `itNesspkthunderball_ShiftPositions`, `itNesspkthunderball_UnkMotion0_Phys`, `itNesspkthunderball_UnkMotion0_Coll`, `itNessPKThunderball_Logic26_DmgDealt`, `it_802AC074`, `it_802AC098`, `it_802AC338`, `it_802AC35C`, `it_802AC3F8`, `it_802AC41C`

## `src/melee/it/kinds/itnesspkthunderball.h`

31 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itnesspkthundertrail.c`

152 linhas; 7 definições aparentes; 0 marcadores asm.

Includes: `itnesspkthundertrail.h`, `Runtime/platform.h`, `melee/it/forward.h`, `math.h`, `placeholder.h`, `inlines.h`, `itnesspkthunderball.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802AC43C`, `it_802AC58C`, `it_802AC5D8`, `it_802AC604`, `itNesspkthundertrail_UnkMotion0_Anim`, `itNesspkthundertrail_UnkMotion0_Phys`, `itNesspkthundertrail_UnkMotion0_Coll`

## `src/melee/it/kinds/itnesspkthundertrail.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itnessyoyo.c`

803 linhas; 29 definições aparentes; 0 marcadores asm.

Includes: `itnessyoyo.h`, `inlines.h`, `itlinkhookshot.h`, `melee/ft/ftlib.h`, `melee/ft/inlines.h`, `melee/ft/kinds/ftNess/ftnessattackhi4.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itYoyo.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjuserdata.h`

Definições aparentes: `it_802BE598`, `it_802BE5B8`, `it_802BE5D8`, `it_802BE65C_LoadString`, `it_802BE65C`, `it_802BE958_inline`, `it_802BE958`, `it_802BE9D8`, `itNessyoyo_UnkMotion0_Phys`, `itNessyoyo_UnkMotion1_Phys`, `itNessyoyo_UnkMotion2_Phys`, `itNessyoyo_UnkMotion3_Phys`, `itNessyoyo_UnkMotion3_Anim_inline`, `itNessyoyo_UnkMotion3_Anim_UpdateRotation`, `itNessyoyo_UnkMotion3_Anim`, `it_802BF030`, `it_802BF180`, `it_802BF28C`, `it_802BF4A0_adjust_tail`, `it_802BF4A0`, `it_802BF800`, `it_802BF900`, `it_802BFAFC`, `itNessYoyo_Logic59_PickedUp`, `it_802BFE5C`, `my_sqrtf`, `it_802BFEC4`, `it_802C0010`, `it_2725_Logic59_EvtUnk`

## `src/melee/it/kinds/itnessyoyo.h`

36 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/itCharItems.h`, `melee/it/itYoyo.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itnokonoko.c`

559 linhas; 51 definições aparentes; 0 marcadores asm.

Includes: `itnokonoko.h`, `itzgshell.h`, `itzrshell.h`, `melee/cm/camera.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/mp/mpcoll.h`

Definições aparentes: `coll_inline`, `it_802DC69C`, `order_sdata2`, `itNokonoko_Logic3_DmgReceived`, `it_802DC83C`, `fn_802DC8B8`, `itNokonoko_UnkMotion1_Anim`, `itNokonoko_UnkMotion1_Phys`, `itNokonoko_UnkMotion1_Coll`, `it_802DC990`, `itNokonoko_UnkMotion2_Anim`, `itNokonoko_UnkMotion2_Phys`, `itNokonoko_UnkMotion2_Coll`, `it_802DCB9C`, `itNokonoko_UnkMotion4_Anim`, `itNokonoko_UnkMotion4_Phys`, `itNokonoko_UnkMotion6_Coll`, `it_802DCCCC`, `itNokonoko_UnkMotion8_Anim`, `itNokonoko_UnkMotion7_Phys`, `itNokonoko_UnkMotion8_Coll`, `it_802DCE00`, `itNokonoko_UnkMotion8_Phys`, `it_802DCEC4`, `it_802DCFBC`, `lt_zero`, `itNokonoko_UnkMotion5_Anim`, `itNokonoko_UnkMotion5_Phys`, `itNokonoko_UnkMotion5_Coll`, `itNokonoko_UnkMotion6_Anim`, `itNokonoko_UnkMotion6_Phys`, `it_802DD290_inline`, `it_802DD290`, `it_802DD2DC`, `itNokonoko_UnkMotion3_Anim`, `itNokonoko_UnkMotion3_Phys`, `itNokonoko_UnkMotion3_Coll`, `it_802DD4A8`, `it_802DD4F4`, `itNokonoko_UnkMotion9_Anim`, `itNokonoko_UnkMotion9_Phys`, `it_802DD59C_inline`, `it_802DD59C`, `it_802DD67C`, `itNokonoko_UnkMotion10_Anim`, `itNokonoko_UnkMotion10_Phys`, `itNokonoko_UnkMotion10_Coll`, `it_802DD78C`, `it_802DD7D0`, `it_802DD7F0`, `it_802DDA84`

## `src/melee/it/kinds/itnokonoko.h`

59 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itoctarock.c`

489 linhas; 43 definições aparentes; 0 marcadores asm.

Includes: `itoctarock.h`, `placeholder.h`, `inlines.h`, `itoctarockstone.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/lb/lb_00B0.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itOctarock_SetFacingDir`, `it_802E4A44`, `it_802E4B00`, `it_802E4C08`, `itOctarock_UnkMotion0_Anim`, `itOctarock_UnkMotion0_Phys`, `itOctarock_UnkMotion0_Coll`, `it_802E4DB4`, `itOctarock_UnkMotion2_Anim`, `itOctarock_UnkMotion2_Phys`, `itOctarock_UnkMotion2_Coll`, `it_802E4E6C`, `itOctarock_UnkMotion3_Anim`, `itOctarock_UnkMotion3_Phys`, `itOctarock_UnkMotion3_Coll`, `it_802E503C`, `itOctarock_UnkMotion4_Anim`, `itOctarock_UnkMotion4_Phys`, `itOctarock_UnkMotion4_Coll`, `it_802E52E0`, `it_802E53C8`, `itOctarock_UnkMotion1_Anim`, `itOctarock_UnkMotion1_Phys`, `itOctarock_UnkMotion1_Coll`, `itOctarock_Logic2_PickedUp`, `itOctarock_UnkMotion5_Anim`, `itOctarock_UnkMotion5_Phys`, `itOctarock_Logic2_Dropped`, `itOctarock_Logic2_Thrown`, `itOctarock_UnkMotion6_Anim`, `itOctarock_UnkMotion6_Phys`, `itOctarock_UnkMotion6_Coll`, `it_802E57D4`, `itOctarock_UnkMotion7_Anim`, `itOctarock_UnkMotion7_Phys`, `itOctarock_UnkMotion7_Coll`, `it_802E58A0`, `itOctarock_UnkMotion8_Anim`, `itOctarock_UnkMotion8_Phys`, `itOctarock_UnkMotion8_Coll`, `it_802E5944`, `it_802E595C`, `it_802E5AA4`

## `src/melee/it/kinds/itoctarock.h`

54 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itoctarockstone.c`

192 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `itoctarockstone.h`, `melee/it/forward.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itOctarockstone_802E878C`, `itOctarockstone_Logic4_DmgDealt`, `itOctarockstone_Logic4_Clanked`, `itOctarockstone_Logic4_HitShield`, `itOctarockstone_Logic4_Absorbed`, `itOctarockstone_Logic4_Reflected`, `itOctarockstone_Logic4_ShieldBounced`, `itOctarockstone_802E883C`, `itOctarockstone_UnkMotion0_Anim`, `itOctarockstone_UnkMotion0_Phys`, `itOctarockstone_UnkMotion0_Coll`, `itOctarockstone_802E890C`, `itOctarockstone_UnkMotion1_Anim`, `itOctarockstone_UnkMotion1_Phys`, `itOctarockstone_UnkMotion1_Coll`, `itOctarockstone_802E89B0`, `getX`, `it_802E89D0`, `it_802E8ADC`

## `src/melee/it/kinds/itoctarockstone.h`

30 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itoldkuri.c`

563 linhas; 53 definições aparentes; 0 marcadores asm.

Includes: `itoldkuri.h`, `Runtime/platform.h`, `placeholder.h`, `inlines.h`, `melee/cm/camera.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itOldKuri_Logic29_EvtUnk`, `it_802D73F0`, `it_802D747C`, `itOldkuri_UnkMotion0_Anim`, `itOldkuri_UnkMotion0_Phys`, `itOldkuri_UnkMotion0_Coll`, `it_802D758C`, `itOldkuri_UnkMotion1_Anim`, `itOldkuri_UnkMotion1_Phys`, `itOldkuri_UnkMotion1_Coll`, `it_802D775C`, `itOldkuri_UnkMotion2_Anim`, `itOldkuri_UnkMotion2_Phys`, `itOldkuri_UnkMotion2_Coll`, `itOldkuri_UnkMotion3_Anim`, `itOldkuri_UnkMotion3_Phys`, `itOldkuri_UnkMotion3_Coll`, `it_802D7AF0`, `itOldkuri_UnkMotion4_Anim`, `itOldkuri_UnkMotion4_Phys`, `itOldkuri_UnkMotion4_Coll`, `itOldKuri_Logic0_PickedUp`, `itOldkuri_UnkMotion5_Anim`, `itOldkuri_UnkMotion5_Phys`, `it_2725_Logic0_Dropped`, `it_2725_Logic0_Thrown`, `itOldkuri_UnkMotion6_Anim`, `itOldkuri_UnkMotion6_Phys`, `itOldkuri_UnkMotion6_Coll`, `itOldkuri_UnkMotion9_Anim`, `itOldkuri_UnkMotion9_Phys`, `itOldkuri_UnkMotion9_Coll`, `it_2725_Logic0_DmgReceived_inline`, `it_2725_Logic0_DmgReceived`, `it_802D8098`, `it_802D813C`, `itOldkuri_UnkMotion7_Anim`, `itOldkuri_UnkMotion7_Phys`, `itOldkuri_UnkMotion7_Coll`, `it_802D81FC`, `itOldkuri_UnkMotion8_Anim`, `itOldkuri_UnkMotion8_Phys`, `itOldkuri_UnkMotion8_Coll`, `it_802D82C4`, `itOldkuri_UnkMotion10_Anim`, `itOldkuri_UnkMotion10_Phys`, `itOldkuri_UnkMotion10_Coll`, `it_802D839C`, `itOldkuri_UnkMotion11_Anim`, `itOldkuri_UnkMotion11_Phys`, `itOldkuri_UnkMotion11_Coll`, `it_802D848C`, `it_802D84D8`

## `src/melee/it/kinds/itoldkuri.h`

64 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itoldottosea.c`

479 linhas; 27 definições aparentes; 0 marcadores asm.

Includes: `itoldottosea.h`, `inlines.h`, `itfreeze.h`, `itwhitebea.h`, `melee/gm/gmvs.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itspawn.h`, `melee/it/itzako.h`, `melee/lb/lblanguage.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802E2470`, `it_2725_Logic8_DmgReceived`, `it_802E269C`, `itOldottosea_UnkMotion0_Anim`, `itOldottosea_UnkMotion0_Phys`, `itOldottosea_UnkMotion0_Coll`, `it_802E27B4`, `itOldottosea_UnkMotion2_Anim`, `itOldottosea_UnkMotion2_Phys`, `itOldottosea_UnkMotion2_Coll`, `it_802E2BC0`, `itOldottosea_UnkMotion4_Anim`, `itOldottosea_UnkMotion4_Phys`, `itOldottosea_UnkMotion4_Coll`, `it_802E2C80`, `itOldottosea_UnkMotion5_Anim`, `itOldottosea_UnkMotion5_Phys`, `itOldottosea_UnkMotion5_Coll`, `it_802E2DF4`, `it_802E2E30`, `itOldottosea_UnkMotion7_Anim`, `itOldottosea_UnkMotion7_Phys`, `itOldottosea_UnkMotion7_Coll`, `it_802E3098`, `itOldottosea_UnkMotion3_Anim`, `itOldottosea_UnkMotion3_Phys`, `itOldottosea_UnkMotion3_Coll`

## `src/melee/it/kinds/itoldottosea.h`

37 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itparasol.c`

256 linhas; 36 definições aparentes; 0 marcadores asm.

Includes: `itparasol.h`, `dolphin/mtx.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_8028B08C`, `itParasol_Logic13_Spawned`, `it_8028B0EC`, `itParasol_UnkMotion0_Anim`, `itParasol_UnkMotion0_Phys`, `itParasol_UnkMotion0_Coll`, `it_8028B17C`, `jobj_child`, `itParasol_UnkMotion2_Anim`, `decelerateItemX`, `itParasol_UnkMotion1_Phys`, `itParasol_UnkMotion2_Coll`, `itParasol_Logic13_Dropped`, `itParasol_Logic13_Thrown`, `itParasol_UnkMotion2_Phys`, `itParasol_Logic13_DmgDealt`, `itParasol_Logic13_Clanked`, `itParasol_Logic13_HitShield`, `itParasol_Logic13_Reflected`, `itParasol_Logic13_ShieldBounced`, `itParasol_Logic13_EnteredAir`, `itParasol_UnkMotion3_Anim`, `itParasol_UnkMotion3_Phys`, `itParasol_UnkMotion3_Coll`, `itParasol_Logic13_PickedUp`, `itParasol_UnkMotion10_Anim`, `itParasol_UnkMotion10_Phys`, `animSpeed`, `it_8028B618`, `it_8028B648`, `it_8028B6B0`, `it_8028B718`, `it_8028B780`, `it_8028B7E8`, `it_8028B850`, `itParasol_Logic13_EvtUnk`

## `src/melee/it/kinds/itparasol.h`

46 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itpatapata.c`

575 linhas; 33 definições aparentes; 0 marcadores asm.

Includes: `itpatapata.h`, `Runtime/platform.h`, `melee/it/forward.h`, `placeholder.h`, `inlines.h`, `itnokonoko.h`, `melee/cm/camera.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/lb/lb_00B0.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802E05A0`, `it_802E0678`, `itPatapata_UnkMotion1_Anim`, `itPatapata_UnkMotion1_Phys`, `itPatapata_UnkMotion1_Coll`, `it_802E0734`, `itPatapata_UnkMotion2_Anim`, `itPatapata_UnkMotion3_Phys`, `itPatapata_UnkMotion3_Coll`, `it_802E0D9C`, `itPatapata_UnkMotion3_Anim`, `it_2725_Logic4_DmgReceived`, `it_802E0F1C`, `itPatapata_Logic4_PickedUp`, `itPatapata_UnkMotion5_Anim`, `itPatapata_UnkMotion5_Phys`, `it_2725_Logic4_Dropped`, `itPatapata_UnkMotion7_Anim`, `itPatapata_UnkMotion7_Phys`, `itPatapata_UnkMotion7_Coll`, `it_2725_Logic4_Thrown`, `itPatapata_UnkMotion6_Anim`, `itPatapata_UnkMotion6_Phys`, `itPatapata_UnkMotion6_Coll`, `it_802E11E0`, `itPatapata_UnkMotion4_Anim`, `itPatapata_UnkMotion4_Phys`, `itPatapata_UnkMotion4_Coll`, `it_802E15B0`, `it_802E1648`, `it_802E1694`, `it_802E16D8`, `it_802E16F8`

## `src/melee/it/kinds/itpatapata.h`

43 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itpeachexplode.c`

75 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `itpeachexplode.h`, `inlines.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/types.h`

Definições aparentes: `it_802BD158`, `itPeachExplode_Logic55_DmgDealt`, `it_802BD248`, `itPeachexplode_UnkMotion1_Anim`, `itPeachExplode_Logic55_EvtUnk`

## `src/melee/it/kinds/itpeachexplode.h`

17 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itpeachparasol.c`

138 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `itpeachparasol.h`, `inlines.h`, `melee/ft/kinds/ftPeach/ftpeachspecialhi.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`

Definições aparentes: `it_802BDA40`, `it_802BDA64`, `itPeachParasol_Logic60_Destroyed`, `it_802BDB94`, `it_802BDBF8`, `it_802BDC18`, `it_802BDC38`, `itPeachParasol_Logic60_PickedUp`, `itPeachparasol_UnkMotion2_Anim`, `it_802BDD3C`, `it_802BDD40`, `it_802BDDB4`, `itPeachParasol_Logic60_EvtUnk`

## `src/melee/it/kinds/itpeachparasol.h`

29 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/ft/types.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itpeachtoad.c`

162 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `itpeachtoad.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `inlines.h`, `melee/ft/kinds/ftKirby/ftkirbyspecialpeach.h`, `melee/ft/kinds/ftPeach/ftpeachspecialn.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/lb/lb_00B0.h`

Definições aparentes: `itpeachtoad_inline_1`, `itpeachtoad_inline_2`, `it_802BDE18`, `itPeachToad_Logic91_Destroyed`, `it_802BDF40`, `it_802BDFA0`, `it_802BDFC0`, `itPeachToad_Logic91_PickedUp`, `itPeachtoad_UnkMotion0_Anim`, `it_802BE100`, `itPeachtoad_UnkMotion1_Anim`, `itPeachToad_Logic91_EvtUnk`

## `src/melee/it/kinds/itpeachtoad.h`

23 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itpeachtoadspore.c`

154 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `itpeachtoadspore.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `math.h`, `inlines.h`, `melee/db/db.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802BE214`, `it_802BE2E8`, `itPeachtoadspore_UnkMotion0_Anim`, `itPeachtoadspore_UnkMotion0_Phys`, `itPeachToadSpore_Logic92_DmgDealt`, `itPeachToadSpore_Logic68_Clanked`, `itPeachToadSpore_Logic68_HitShield`, `itPeachToadSpore_Logic68_Absorbed`, `itPeachToadSpore_Logic68_ShieldBounced`, `itPeachToadSpore_Logic68_Reflected`, `itPeachToadSpore_Logic92_EvtUnk`

## `src/melee/it/kinds/itpeachtoadspore.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itpeachturnip.c`

289 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `itpeachturnip.h`, `inlines.h`, `melee/ft/kinds/ftPeach/ftpeachspeciallw.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `decrease_lifetimer`, `it_802BD32C`, `it_802BD45C`, `itPeachTurnip_Logic56_Destroyed`, `it_802BD4AC`, `itPeachTurnip_Logic56_PickedUp`, `itPeachturnip_UnkMotion4_Anim`, `itPeachturnip_UnkMotion4_Phys`, `itPeachturnip_UnkMotion1_Anim`, `itPeachturnip_UnkMotion1_Phys`, `itPeachTurnip_Logic56_Thrown`, `itPeachturnip_UnkMotion3_Anim`, `itPeachturnip_UnkMotion3_Phys`, `itPeachturnip_UnkMotion3_Coll`, `itPeachTurnip_Logic56_Dropped`, `itPeachTurnip_Logic56_DmgDealt`, `itPeachTurnip_Logic56_Clanked`, `itPeachTurnip_Logic56_Reflected`, `itPeachTurnip_Logic56_HitShield`, `itPeachTurnip_Logic56_ShieldBounced`, `itPeachTurnip_Logic56_EvtUnk`

## `src/melee/it/kinds/itpeachturnip.h`

34 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itpikachuthunder.c`

308 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `itpikachuthunder.h`, `placeholder.h`, `forward.h`, `inlines.h`, `melee/db/db.h`, `melee/ft/kinds/ftPikachu/ftpikachuspeciallw.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802B1DEC`, `it_802B1DF8`, `it_802B1FC8`, `it_802B1FE8`, `it_2725_Logic39_Destroyed`, `it_802B2080`, `itPikachuthunder_UnkMotion0_Anim`, `it_802B211C`, `itPikachuthunder_UnkMotion1_Anim`, `itPikachuthunder_UnkMotion1_Coll`, `it_802B22B8_inline`, `it_802B22B8`, `pika_scale`, `itPikachuthunder_UnkMotion2_ScaleCall`, `itPikachuthunder_UnkMotion2_UpdateScale`, `itPikachuthunder_UnkMotion2_Anim`, `itPikachuThunder_Logic39_DmgDealt`, `itPikachuThunder_Logic39_HitShield`, `itPikachuThunder_Logic39_Clanked`, `itPikachuThunder_Logic39_Absorbed`, `itPikachuThunder_Logic39_EvtUnk`

## `src/melee/it/kinds/itpikachuthunder.h`

30 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itpikachutjoltair.c`

288 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `itpikachutjoltair.h`, `Runtime/platform.h`, `math.h`, `placeholder.h`, `forward.h`, `inlines.h`, `itpikachutjoltground.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/lb/lb_00B0.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802B3EFC`, `it_802B3F20`, `it_802B3F88`, `it_802B4224`, `it_802B43B0`, `it_802B43D0`, `itPikachuTJoltAir_Anim_Destroy`, `itPikachutjoltair_UnkMotion0_Anim_inline`, `itPikachutjoltair_UnkMotion0_Anim`, `itPikachutjoltair_UnkMotion0_Phys`, `itPikachutjoltair_UnkMotion0_Coll`, `it_2725_Logic107_DmgDealt`, `it_2725_Logic107_Clanked`, `it_2725_Logic107_Absorbed`, `it_2725_Logic107_Reflected`, `it_2725_Logic107_HitShield`, `it_2725_Logic107_ShieldBounced`, `itPikachuTJoltAir_Logic107_EvtUnk`

## `src/melee/it/kinds/itpikachutjoltair.h`

30 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/lb/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itpikachutjoltground.c`

404 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `itpikachutjoltground.h`, `melee/it/forward.h`, `math.h`, `inlines.h`, `itpikachutjoltair.h`, `melee/db/db.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `order_sdata2`, `it_802B3368`, `itPikachuThunderJolt_Spawn`, `it_2725_Logic106_Destroyed`, `it_802B3544`, `it_802B3554`, `itPikachutjoltground_UnkMotion0_Anim`, `itPikachutjoltground_UnkMotion1_Anim`, `itPikachutjoltground_UnkMotion0_Phys`, `itPikachutjoltground_UnkMotion1_Phys`, `itPikachutjoltground_UnkMotion0_Coll`, `itPikachutjoltground_UnkMotion1_Coll`, `it_2725_Logic106_DmgDealt`, `it_2725_Logic106_Reflected`, `it_2725_Logic106_Clanked`, `it_2725_Logic106_Absorbed`, `it_2725_Logic106_HitShield`, `it_2725_Logic106_ShieldBounced`, `itPikachuTJoltGround_Logic106_EvtUnk`

## `src/melee/it/kinds/itpikachutjoltground.h`

32 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itpippi.c`

182 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `itpippi.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itPippi_Logic20_Spawned`, `it_802D32D8`, `it_802D32DC`, `itPippi_UnkMotion1_Anim`, `itPippi_UnkMotion1_Phys`, `itPippi_UnkMotion1_Coll`, `it_802D33F8`, `itPippi_UnkMotion5_Anim`, `itPippi_UnkMotion5_Phys`, `itPippi_UnkMotion5_Coll`, `it_802D3590`, `itPippi_UnkMotion0_Anim`, `itPippi_UnkMotion0_Phys`, `itPippi_UnkMotion0_Coll`

## `src/melee/it/kinds/itpippi.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itporygon2.c`

92 linhas; 10 definições aparentes; 0 marcadores asm.

Includes: `itporygon2.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `itPorygon2_Logic26_Spawned`, `it_802D5B14`, `itPorygon2_UnkMotion0_Anim`, `itPorygon2_UnkMotion0_Phys`, `itPorygon2_UnkMotion0_Coll`, `it_802D5C00`, `itPorygon2_UnkMotion1_Anim`, `itPorygon2_UnkMotion1_Phys`, `itPorygon2_UnkMotion1_Coll`, `it_802D5CD8`

## `src/melee/it/kinds/itporygon2.h`

23 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itrabbitc.c`

214 linhas; 24 definições aparentes; 0 marcadores asm.

Includes: `itrabbitc.h`, `melee/it/forward.h`, `inlines.h`, `types.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itRabbitC_Logic30_ShieldBounced`, `it_80294DC0`, `it_80294E78`, `it_80294EB0`, `it_802950D4`, `itRabbitC_Logic31_Spawned`, `it_80295138`, `itRabbitc_UnkMotion0_Anim`, `itRabbitc_UnkMotion0_Phys`, `itRabbitc_UnkMotion0_Coll`, `it_802951C0`, `itRabbitc_UnkMotion3_Anim`, `itRabbitc_UnkMotion1_Phys`, `itRabbitc_UnkMotion1_Coll`, `itRabbitC_Logic31_PickedUp`, `itRabbitc_UnkMotion2_Anim`, `itRabbitC_Logic31_Dropped`, `itRabbitc_UnkMotion3_Phys`, `itRabbitc_UnkMotion3_Coll`, `itRabbitC_Logic31_EnteredAir`, `itRabbitc_UnkMotion4_Anim`, `itRabbitc_UnkMotion4_Phys`, `itRabbitc_UnkMotion4_Coll`, `itRabbitC_Logic31_EvtUnk`

## `src/melee/it/kinds/itrabbitc.h`

23 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itraikou.c`

163 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `itraikou.h`, `inlines.h`, `melee/cm/camera.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802CF814`, `it_802CF880`, `it_802CF884`, `it_802CF8A4`, `it_802CF908`, `itRaikou_UnkMotion0_Anim`, `itRaikou_UnkMotion0_Phys`, `itRaikou_UnkMotion0_Coll`, `it_802CFAFC`, `it_802CFB78`, `itRaikou_UnkMotion1_Anim`, `itRaikou_UnkMotion1_Phys`, `itRaikou_UnkMotion1_Coll`

## `src/melee/it/kinds/itraikou.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itrshell.c`

756 linhas; 56 definições aparentes; 0 marcadores asm.

Includes: `itrshell.h`, `Runtime/platform.h`, `placeholder.h`, `inlines.h`, `melee/ef/efasync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_8028CFE0`, `it_8028D090`, `it_8028D100`, `it_8028D26C`, `it_8028D390`, `it_8028D3B8`, `fn_8028D4A8`, `it_8028D4E4`, `itRshell_ClampVel`, `it_8028D56C`, `it_3F14_Logic15_Spawned`, `it_8028D62C`, `itRshell_UnkMotion0_Anim`, `itRshell_UnkMotion0_Phys`, `itRshell_UnkMotion0_Coll`, `it_8028D7F0`, `itRshell_UnkMotion1_Anim`, `itRshell_UnkMotion1_Phys`, `itRshell_UnkMotion1_Coll`, `itRShell_Logic15_PickedUp`, `itRshell_UnkMotion2_Anim`, `itRshell_UnkMotion2_Phys`, `it_3F14_Logic15_Thrown`, `itRshell_UnkMotion3_Anim`, `itRshell_UnkMotion3_Phys`, `itRshell_UnkMotion3_Coll`, `it_3F14_Logic15_Dropped`, `itRshell_UnkMotion4_Anim`, `itRshell_UnkMotion4_Phys`, `itRshell_UnkMotion4_Coll`, `itRshell_StopInit`, `it_8028DAE4`, `itRshell_UnkMotion5_Anim`, `itRshell_UM5_Accel`, `itRshell_UM5_AddVelAndCheck`, `itRshell_UM5_MaybeBrake`, `itRshell_UnkMotion5_Phys`, `itRshell_UM5C_Reverse`, `itRshell_UM5C_GroundSpin`, `itRshell_UnkMotion5_Coll`, `it_8028E170`, `itRshell_UnkMotion6_Anim`, `itRshell_UnkMotion6_Phys`, `itRshell_UnkMotion6_Coll`, `it_3F14_Logic15_EnteredAir`, `itRshell_UnkMotion7_Anim`, `itRshell_UnkMotion7_Phys`, `itRshell_UnkMotion7_Coll`, `it_3F14_Logic15_DmgDealt`, `it_3F14_Logic15_DmgReceived`, `itRShell_Logic15_Reflected`, `itRShell_Logic15_Clanked`, `it_3F14_Logic15_HitShield`, `itRShell_Logic15_ShieldBounced`, `it_8028E6C0`, `itRShell_Logic15_EvtUnk`

## `src/melee/it/kinds/itrshell.h`

61 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itsamusbomb.c`

280 linhas; 26 definições aparentes; 0 marcadores asm.

Includes: `itsamusbomb.h`, `Runtime/platform.h`, `melee/it/forward.h`, `inlines.h`, `melee/db/db.h`, `melee/ft/kinds/ftSamus/ftsamus.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/mtx.h`

Definições aparentes: `it_802B4AC8`, `it_802B4BA0`, `it_802B4C10`, `itSamusBomb_UnkMotion_Process`, `itSamusBomb_UnkMotion_PreProcess`, `itSamusbomb_UnkMotion0_Anim`, `itSamusbomb_UnkMotion0_Phys`, `itSamusbomb_UnkMotion0_Coll`, `it_802B4CF4`, `itSamusbomb_UnkMotion1_Anim`, `itSamusbomb_UnkMotion1_Phys`, `itSamusbomb_UnkMotion1_Coll`, `itSamusBomb_Logic50_EnteredAir`, `itSamusbomb_UnkMotion2_Anim`, `my_sqrtf`, `itSamusbomb_UnkMotion2_Phys`, `itSamusbomb_UnkMotion2_Coll`, `itSamusBomb_Logic50_DmgDealt`, `itSamusBomb_Logic50_Clanked`, `itSamusBomb_Logic50_HitShield`, `itSamusBomb_Logic50_ShieldBounced`, `it_2725_Logic50_Reflected`, `it_802B53CC`, `itSamusbomb_UnkMotion3_Anim`, `it_802B5478`, `itSamusBomb_Logic50_EvtUnk`

## `src/melee/it/kinds/itsamusbomb.h`

37 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itsamuschargeshot.c`

431 linhas; 21 definições aparentes; 0 marcadores asm.

Includes: `itsamuschargeshot.h`, `inlines.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftKirby/ftkirby.h`, `melee/ft/kinds/ftSamus/ftsamusspeciallw0.h`, `melee/ft/kinds/ftSamus/ftsamusspecialn.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/mtx.h`

Definições aparentes: `it_802B5518`, `it_802B55C8`, `it_802B56E4`, `it_2725_Logic108_Destroyed`, `it_802B5974`, `it_2725_Logic108_PickedUp`, `itSamuschargeshot_UnkMotion0_Anim`, `itSamuschargeshot_UnkMotion0_Phys`, `itSamuschargeshot_UnkMotion0_Coll`, `it_802B5CBC`, `itSamuschargeshot_UnkMotion8_Anim`, `itSamuschargeshot_UnkMotion8_Phys`, `itSamuschargeshot_UnkMotion8_Coll`, `it_802B5EDC`, `itSamusChargeshot_Logic108_DmgDealt`, `itSamusChargeshot_Logic108_Clanked`, `itSamusChargeshot_Logic108_Absorbed`, `it_2725_Logic108_Reflected`, `itSamusChargeshot_Logic108_HitShield`, `it_2725_Logic108_ShieldBounced`, `itSamusChargeshot_Logic108_EvtUnk`

## `src/melee/it/kinds/itsamuschargeshot.h`

36 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itsamusgrapple.c`

1747 linhas; 59 definições aparentes; 0 marcadores asm.

Includes: `itsamusgrapple.h`, `melee/ft/forward.h`, `sysdolphin/baselib/forward.h`, `placeholder.h`, `inlines.h`, `itlinkhookshot.h`, `dolphin/types.h`, `melee/ef/efsync.h`, `melee/ft/fighter.h`, `melee/ft/ft_081B.h`, `melee/ft/ftcliffcommon.h`, `melee/ft/ftcoll.h`, `melee/ft/ftcommon.h`, `melee/ft/ftlib.h`, `melee/ft/ftparts.h`, `melee/ft/inlines.h`, `melee/ft/kinds/ftCommon/ftCo_0A01.h`, `melee/ft/kinds/ftCommon/ftCo_AirCatch.h`, `melee/ft/kinds/ftCommon/ftCo_CliffJump.h`, `melee/ft/kinds/ftCommon/ftCo_DamageFall.h`, `melee/ft/kinds/ftSamus/types.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/lb/lbvector.h`, `melee/lb/types.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `samus_grapple_fighter_compare`, `samus_grapple_init_link`, `samus_grapple_calc_grav`, `samus_grapple_setup_pos`, `samus_grapple_anim`, `samus_grapple_state_sync`, `itSamusGrapple_Logic53_Spawned`, `it_802B7160`, `it_802B743C`, `samus_grapple_setup_tail`, `it_802B75FC`, `it_802B7B84`, `it_802B7C18`, `fn_802B7E34_inline`, `fn_802B7E34_anim_inline`, `fn_802B7E34`, `itSamusgrapple_UnkMotion0_Phys`, `fn_802B805C`, `itSamusgrapple_UnkMotion1_Phys`, `fn_802B8384`, `itSamusgrapple_UnkMotion2_Phys`, `fn_802B8524`, `itSamusgrapple_UnkMotion3_Phys`, `fn_802B8684`, `itSamusgrapple_UnkMotion4_Phys`, `fn_802B8814`, `itSamusgrapple_UnkMotion5_Phys`, `fn_802B895C`, `itSamusgrapple_UnkMotion6_Phys`, `fn_802B8B54`, `itSamusgrapple_UnkMotion7_Phys`, `fn_802B8D38`, `itSamusgrapple_UnkMotion8_Phys`, `it_802B900C`, `it_802B91C4`, `it_802B9328_attach`, `it_802B9328_grav`, `it_802B9328`, `it_802B99A0`, `it_802B9CE8`, `it_802B9FD4`, `it_802BA194`, `it_802BA2D8`, `it_802BA3BC`, `it_802BA5DC`, `it_802BA760`, `itSamusGrapple_Logic53_PickedUp`, `it_802BA9B8`, `it_802BAA08`, `it_802BAA58`, `it_802BAA94`, `it_802BAAE4`, `it_802BAB40`, `it_802BAB7C`, `it_802BABB8`, `it_802BAC3C`, `it_802BAC80`, `it_802BACC4`, `itSamusGrapple_Logic53_EvtUnk`

## `src/melee/it/kinds/itsamusgrapple.h`

100 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/forward.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/itCharItems.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itsamusmissile.c`

438 linhas; 24 definições aparentes; 0 marcadores asm.

Includes: `itsamusmissile.h`, `inlines.h`, `melee/db/db.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/ft/kinds/ftSamus/ftsamusspecialn.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/mtx.h`

Definições aparentes: `it_802B62D0`, `it_802B63F8`, `itSamusMissile_ClampTurn`, `it_802B64FC`, `it_802B66A8`, `isSamusmissile_MotionAnim`, `itSamusmissile_UnkMotion0_Anim`, `inlineA0`, `itSamusmissile_SetRotationX`, `itSamusmissile_UnkMotion0_Phys`, `itSamusmissile_UnkMotion0_Coll`, `it_802B6A60`, `itSamusmissile_UnkMotion1_Anim`, `itSamusmissile_UnkMotion1_Phys`, `itSamusmissile_UnkMotion1_Coll`, `it_2725_Logic52_DmgDealt`, `it_2725_Logic52_Clanked`, `it_2725_Logic52_HitShield`, `it_2725_Logic52_ShieldBounced`, `it_2725_Logic52_Reflected`, `it_802B701C`, `itSamusmissile_UnkMotion3_Anim`, `it_802B70A0`, `it_2725_Logic52_EvtUnk`

## `src/melee/it/kinds/itsamusmissile.h`

48 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itscball.c`

163 linhas; 24 definições aparentes; 0 marcadores asm.

Includes: `itscball.h`, `sysdolphin/baselib/forward.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `itScball_Logic30_Spawned`, `it_80294AD0`, `itScball_UnkMotion0_Anim`, `itScball_UnkMotion0_Phys`, `itScball_UnkMotion0_Coll`, `it_80294B58`, `itScball_UnkMotion1_Anim`, `itScball_UnkMotion1_Phys`, `itScball_UnkMotion1_Coll`, `itScball_Logic30_PickedUp`, `itScball_UnkMotion2_Anim`, `itScball_Logic30_Dropped`, `itScball_Logic30_Thrown`, `itScball_UnkMotion3_Anim`, `itScball_UnkMotion3_Phys`, `itScball_UnkMotion3_Coll`, `itScball_Logic30_EnteredAir`, `itScball_UnkMotion4_Anim`, `itScball_UnkMotion4_Phys`, `itScball_UnkMotion4_Coll`, `itScball_Logic30_DmgDealt`, `itScball_Logic30_Clanked`, `itScball_Logic30_Reflected`, `itScball_Logic30_HitShield`

## `src/melee/it/kinds/itscball.h`

21 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itseakchain.c`

1008 linhas; 35 definições aparentes; 0 marcadores asm.

Includes: `itseakchain.h`, `Runtime/platform.h`, `melee/ft/kinds/ftSeak/forward.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `inlines.h`, `itlinkhookshot.h`, `dolphin/mtx.h`, `melee/ft/ftcoll.h`, `melee/ft/ftlib.h`, `melee/ft/inlines.h`, `melee/ft/kinds/ftSeak/ftseakspecials.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCharItems.h`, `melee/it/item.h`, `melee/it/types.h`, `melee/lb/lbaudio_ax.h`, `melee/lb/lbvector.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/gobjgxlink.h`, `sysdolphin/baselib/gobjobject.h`, `sysdolphin/baselib/gobjplink.h`, `sysdolphin/baselib/gobjuserdata.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `order_sdata2`, `it_802BAEEC`, `it_802BAF0C`, `it_802BAF2C_Load_x64`, `it_802BAF2C_Load_x68`, `it_802BAF2C`, `inlineA0`, `it_802BB20C`, `itSeakChain_Spawn`, `fn_802BB428`, `fn_802BB44C`, `fn_802BB574`, `fn_802BB694`, `fn_802BB784`, `notInSpecialS`, `itSeakchain_UnkMotion4_Anim`, `it_802BB938`, `it_802BBAEC`, `it_802BBB0C`, `it_802BBC38`, `it_802BBD64`, `it_802BBED0`, `itSeakChain_clamp_x10`, `itSeakChain_clamp_x14`, `it_802BC080`, `it_802BC94C`, `it_802BCA30`, `it_802BCB88_prev`, `it_802BCB88`, `it_2725_Logic54_PickedUp`, `it_802BCED4`, `it_802BCF2C`, `it_802BCF84`, `it_802BCFC4`, `itSeakChain_Logic54_EvtUnk`

## `src/melee/it/kinds/itseakchain.h`

38 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/itCharItems.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itseakneedleheld.c`

145 linhas; 7 definições aparentes; 0 marcadores asm.

Includes: `itseakneedleheld.h`, `melee/ft/forward.h`, `inlines.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftKirby/ftkirbyspecialdonkey.h`, `melee/ft/kinds/ftSeak/ftseakspecials.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/item.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802B18B0`, `it_802B19AC`, `itSeakNeedleHeld_Logic110_PickedUp`, `itSeakneedleheld_UnkMotion0_Anim`, `itSeakneedleheld_UnkMotion0_Phys`, `itSeakneedleheld_UnkMotion0_Coll`, `itSeakNeedleHeld_Logic110_EvtUnk`

## `src/melee/it/kinds/itseakneedleheld.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itseakneedlethrown.c`

572 linhas; 35 definições aparentes; 0 marcadores asm.

Includes: `itseakneedlethrown.h`, `melee/it/forward.h`, `math.h`, `placeholder.h`, `inlines.h`, `melee/db/db.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/lb/lbvector.h`, `melee/mp/mpcoll.h`, `melee/mp/mplib.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `sdata2_order`, `it_802AFD8C`, `it_802AFEA8`, `itSeakNeedleThrown_Logic109_Destroyed`, `it_802AFF08`, `itSeakNeedleThrown_SetupBounce`, `itSeakNeedleThrown_SetupDrop`, `it_802B00F4`, `itSeakneedlethrown_UnkMotion0_Anim`, `itSeakneedlethrown_UnkMotion1_Anim`, `itSeakneedlethrown_UnkMotion2_Anim`, `itSeakneedlethrown_UnkMotion3_Anim`, `itSeakneedlethrown_UnkMotion4_Anim`, `itSeakneedlethrown_UnkMotion0_Phys`, `itSeakneedlethrown_UnkMotion1_Phys`, `itSeakneedlethrown_UnkMotion2_Phys`, `itSeakneedlethrown_UnkMotion3_Phys`, `itSeakneedlethrown_UnkMotion4_Phys`, `itSeakNeedleThrown_CheckGroundHit`, `itSeakNeedleThrown_CheckGroundHit4`, `itSeakneedlethrown_UnkMotion0_Coll`, `itSeakneedlethrown_UnkMotion1_Coll`, `itSeakNeedleThrown_Coll2_Inline`, `itSeakNeedleThrown_Coll2_Rotate`, `itSeakneedlethrown_UnkMotion2_Coll`, `itSeakneedlethrown_UnkMotion3_Coll`, `itSeakneedlethrown_UnkMotion4_Coll`, `it_2725_Logic109_DmgDealt`, `it_2725_Logic109_Clanked`, `it_2725_Logic109_DmgReceived`, `it_2725_Logic109_Reflected`, `it_2725_Logic109_ShieldBounced`, `it_2725_Logic109_HitShield_inline`, `it_2725_Logic109_HitShield`, `itSeakNeedleThrown_Logic109_EvtUnk`

## `src/melee/it/kinds/itseakneedlethrown.h`

48 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/kinds/itseakvanish.c`

62 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `itseakvanish.h`, `inlines.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`

Definições aparentes: `it_802B1C60`, `itSeakVanish_Logic42_DmgDealt`, `it_802B1D40`, `itSeakvanish_UnkMotion0_Anim`, `it_802B1DCC`

## `src/melee/it/kinds/itseakvanish.h`

19 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`, `melee/it/types.h`

## `src/melee/it/kinds/itsonans.c`

228 linhas; 17 definições aparentes; 0 marcadores asm.

Includes: `itsonans.h`, `inlines.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itcoll.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`

Definições aparentes: `it_802CD44C`, `it_802CD4D8`, `it_802CD4DC`, `it_802CD4FC`, `itSonans_Logic9_DmgDealt`, `it_802CD7D4`, `itSonans_UnkMotion0_Anim`, `itSonans_UnkMotion0_Phys`, `itSonans_UnkMotion0_Coll`, `it_802CD9C0`, `itSonans_UnkMotion1_Anim`, `itSonans_UnkMotion1_Phys`, `itSonans_UnkMotion1_Coll`, `it_802CDAA8`, `itSonans_UnkMotion2_Anim`, `itSonans_UnkMotion2_Phys`, `itSonans_UnkMotion2_Coll`

## `src/melee/it/kinds/itsonans.h`

29 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itspycloak.c`

145 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `itspycloak.h`, `Runtime/platform.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`

Definições aparentes: `itSpyCloak_Logic33_Spawned`, `it_80295C68`, `itSpycloak_UnkMotion0_Anim`, `itSpycloak_UnkMotion0_Phys`, `itSpycloak_UnkMotion0_Coll`, `it_80295D04`, `itSpycloak_UnkMotion3_Anim`, `itSpycloak_UnkMotion1_Phys`, `itSpycloak_UnkMotion1_Coll`, `itSpyCloak_Logic33_PickedUp`, `itSpycloak_UnkMotion2_Anim`, `itSpyCloak_Logic33_Dropped`, `itSpycloak_UnkMotion3_Phys`, `itSpycloak_UnkMotion3_Coll`, `itSpyCloak_Logic33_EnteredAir`, `itSpycloak_UnkMotion4_Anim`, `itSpycloak_UnkMotion4_Phys`, `itSpycloak_UnkMotion4_Coll`, `itSpyCloak_Logic33_EvtUnk`

## `src/melee/it/kinds/itspycloak.h`

15 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itsscope.c`

277 linhas; 33 definições aparentes; 0 marcadores asm.

Includes: `itsscope.h`, `Runtime/platform.h`, `melee/it/forward.h`, `placeholder.h`, `inlines.h`, `itsscopebeam.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `it_80291BE0`, `itSScope_Logic21_Spawned`, `it_80291CCC`, `it_80291CF4`, `it_80291D38`, `it_80291DAC_level`, `it_80291DAC`, `it_80291F14`, `it_80291FA8`, `it_80292030`, `itSscope_UnkMotion0_Anim`, `itSscope_UnkMotion0_Phys`, `itSscope_UnkMotion0_Coll`, `it_802920B8`, `itSscope_UnkMotion3_Anim`, `itSscope_UnkMotion1_Phys`, `itSscope_UnkMotion3_Coll`, `itSScope_Logic21_PickedUp`, `itSscope_UnkMotion2_Anim`, `itSscope_UnkMotion2_Phys`, `itSScope_Logic21_Dropped`, `itSScope_Logic21_Thrown`, `itSscope_UnkMotion3_Phys`, `itSScope_Logic21_DmgDealt`, `itSScope_Logic21_Clanked`, `itSScope_Logic21_HitShield`, `itSScope_Logic21_Reflected`, `itSScope_Logic21_ShieldBounced`, `itSScope_Logic21_EnteredAir`, `itSscope_UnkMotion4_Anim`, `itSscope_UnkMotion4_Phys`, `itSscope_UnkMotion4_Coll`, `itSScope_Logic21_EvtUnk`

## `src/melee/it/kinds/itsscope.h`

45 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itsscopebeam.c`

214 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `itsscopebeam.h`, `math.h`, `inlines.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_80298DEC`, `it_80298ED0`, `itSscopebeam_UnkMotion9_Anim`, `itSscopebeam_UnkMotion9_Phys`, `itSscopebeam_UnkMotion9_Coll`, `itSScopeBeam_Logic38_DmgDealt`, `itSScopeBeam_Logic38_Clanked`, `itSScopeBeam_Logic38_HitShield`, `itSScopeBeam_Logic38_Absorbed`, `itSScopeBeam_Logic38_ShieldBounced`, `itSScopeBeam_Logic38_Reflected`, `itSScopeBeam_Logic38_EvtUnk`

## `src/melee/it/kinds/itsscopebeam.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itstar.c`

90 linhas; 7 definições aparentes; 0 marcadores asm.

Includes: `itstar.h`, `dolphin/mtx.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/it/types.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itStar_Logic10_Spawned`, `it_802846D4`, `itStar_UnkMotion0_Anim`, `itStar_UnkMotion0_Phys`, `itStar_UnkMotion0_Coll`, `itStar_Logic10_DmgDealt`, `itStar_Logic10_EvtUnk`

## `src/melee/it/kinds/itstar.h`

20 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itstarrod.c`

214 linhas; 29 definições aparentes; 0 marcadores asm.

Includes: `itstarrod.h`, `Runtime/platform.h`, `melee/it/forward.h`, `itstarrodstar.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `itStarRod_Logic22_Spawned`, `it_80292394`, `it_802923BC`, `it_802923F8`, `itStarrod_UnkMotion0_Anim`, `itStarrod_UnkMotion0_Phys`, `itStarrod_UnkMotion0_Coll`, `it_80292488`, `itStarrod_UnkMotion4_Anim`, `itStarrod_UnkMotion1_Phys`, `itStarrod_UnkMotion1_Coll`, `itStarRod_Logic22_PickedUp`, `itStarrod_UnkMotion2_Anim`, `itStarrod_UnkMotion2_Phys`, `itStarRod_Logic22_Dropped`, `itStarrod_UnkMotion4_Coll`, `itStarRod_Logic22_Thrown`, `itStarrod_UnkMotion4_Phys`, `itStarrod_UnkMotion3_Coll`, `itStarRod_Logic22_DmgDealt`, `itStarRod_Logic22_EnteredAir`, `itStarrod_UnkMotion5_Anim`, `itStarrod_UnkMotion5_Phys`, `itStarrod_UnkMotion5_Coll`, `itStarRod_Logic22_Clanked`, `itStarRod_Logic22_Reflected`, `itStarRod_Logic22_HitShield`, `itStarRod_Logic22_ShieldBounced`, `itStarRod_Logic22_EvtUnk`

## `src/melee/it/kinds/itstarrod.h`

41 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itstarrodstar.c`

144 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `itstarrodstar.h`, `Runtime/platform.h`, `melee/it/forward.h`, `melee/lb/forward.h`, `math.h`, `placeholder.h`, `inlines.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802988E4`, `it_802989C8`, `itStarrodstar_UnkMotion0_Anim`, `itStarrodstar_UnkMotion0_Phys`, `itStarrodstar_UnkMotion0_Coll`, `itStarRodStar_Logic36_DmgDealt`, `itStarRodStar_Logic36_Clanked`, `itStarRodStar_Logic36_HitShield`, `itStarRodStar_Logic36_Absorbed`, `itStarRodStar_Logic36_Reflected`, `itStarRodStar_Logic36_ShieldBounced`, `itStarRodStar_Logic36_EvtUnk`

## `src/melee/it/kinds/itstarrodstar.h`

24 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itsuikun.c`

162 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `itsuikun.h`, `inlines.h`, `melee/cm/camera.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itSuikun_Logic14_Spawned`, `it_802CFCB4`, `it_802CFCB8`, `it_802CFCD8`, `it_802CFD3C`, `itSuikun_UnkMotion0_Anim`, `itSuikun_UnkMotion0_Phys`, `itSuikun_UnkMotion0_Coll`, `it_802CFF30`, `it_802CFFAC`, `itSuikun_UnkMotion1_Anim`, `itSuikun_UnkMotion1_Phys`, `itSuikun_UnkMotion1_Coll`

## `src/melee/it/kinds/itsuikun.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itsword.c`

531 linhas; 44 definições aparentes; 0 marcadores asm.

Includes: `itsword.h`, `Runtime/platform.h`, `placeholder.h`, `forward.h`, `inlines.h`, `types.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itdraw.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itSword_Spawn`, `it_80284E10`, `it_80284E30`, `it_80284FC4`, `it_80285024`, `it_80285084`, `it_80285140`, `it_802851FC`, `it_802852B8`, `it_80285300`, `it_80285314`, `itSword_Logic12_Spawned`, `inlineA0`, `inlineB0`, `inlineA1`, `inlineA2`, `inlineC1`, `inlineA3`, `inlineD1`, `inlineA4`, `it_80285424`, `itSword_UnkMotion0_Anim`, `itSword_UnkMotion0_Phys`, `itSword_UnkMotion0_Coll`, `it_802855F8`, `itSword_UnkMotion3_Anim`, `itSword_UnkMotion3_Phys`, `itSword_UnkMotion3_Coll`, `itSword_Logic12_PickedUp`, `itSword_UnkMotion2_Anim`, `itSword_UnkMotion2_Phys`, `itSword_UnkMotion2_Coll`, `itSword_Logic12_Dropped`, `itSword_Logic12_Thrown`, `itSword_Logic12_EnteredAir`, `itSword_UnkMotion4_Anim`, `itSword_UnkMotion4_Phys`, `itSword_UnkMotion4_Coll`, `itSword_Logic12_DmgDealt`, `itSword_Logic12_Reflected`, `itSword_Logic12_Clanked`, `itSword_Logic12_HitShield`, `itSword_Logic12_ShieldBounced`, `itSword_Logic12_EvtUnk`

## `src/melee/it/kinds/itsword.h`

34 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/itCommonItems.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ittaru.c`

704 linhas; 48 definições aparentes; 0 marcadores asm.

Includes: `ittaru.h`, `placeholder.h`, `inlines.h`, `melee/cm/camera.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itcoll.h`, `melee/it/itdrop.h`, `melee/it/iteffect.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lb_00F9.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_3F14_Logic2_Spawned`, `inline_fabsf`, `order_sdata2`, `it_802874F0`, `it_80287690`, `itTaru_UnkMotion0_Anim`, `itTaru_UnkMotion0_Phys`, `itTaru_UnkMotion0_Coll`, `it_80287D0C`, `itTaru_UnkMotion1_Anim`, `itTaru_UnkMotion1_Phys`, `itTaru_UnkMotion1_Coll`, `itTaru_Logic2_PickedUp`, `itTaru_UnkMotion2_Anim`, `itTaru_UnkMotion2_Phys`, `itTaru_Logic2_Dropped`, `itTaru_Logic2_Thrown`, `it_80287F20`, `itTaru_UnkMotion3_Anim`, `itTaru_UnkMotion3_Phys`, `itTaru_UnkMotion3_Coll`, `it_80288194`, `it_802881B4`, `it_802881FC`, `itTaru_UnkMotion5_Anim`, `itTaru_UnkMotion5_Phys`, `itTaru_UnkMotion5_Coll`, `itTaru_UnkMotion4_Anim`, `itTaru_UnkMotion4_Phys_inline`, `itTaru_UnkMotion4_Phys`, `itTaru_UnkMotion4_Coll`, `it_802885C8`, `itTaru_UnkMotion6_Anim`, `itTaru_UnkMotion6_Phys`, `itTaru_UnkMotion6_Coll`, `it_802886C4_inline`, `it_802886C4`, `itTaru_UnkMotion7_Anim`, `itTaru_UnkMotion7_Phys`, `itTaru_UnkMotion7_Coll`, `itTaru_RandCheck`, `it_3F14_Logic2_inline`, `it_3F14_Logic2_DmgDealt`, `it_3F14_Logic2_Clanked`, `it_3F14_Logic2_HitShield`, `it_3F14_Logic2_Reflected`, `it_3F14_Logic2_DmgReceived`, `itTaru_Logic2_EvtUnk`

## `src/melee/it/kinds/ittaru.h`

52 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ittarucann.c`

717 linhas; 47 definições aparentes; 0 marcadores asm.

Includes: `ittarucann.h`, `sysdolphin/baselib/forward.h`, `math.h`, `inlines.h`, `types.h`, `melee/cm/camera.h`, `melee/ef/efsync.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftCommon/ftCo_Barrel.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/iteffect.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/lb/lb_00B0.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `inline_itTarucann_SetRotationZ`, `it_80295ED4`, `it_80295F38`, `it_802960B8`, `it_802960CC`, `it_3F14_Logic5_Destroyed`, `order_sdata2`, `it_3F14_Logic5_Spawned`, `it_802961E8`, `it_802962E0`, `itTarucann_UnkMotion0_Anim`, `itTarucann_UnkMotion0_Phys`, `itTarucann_UnkMotion0_Coll`, `it_80296694`, `itTarucann_UnkMotion1_Anim`, `itTarucann_UnkMotion1_Phys`, `itTarucann_UnkMotion1_Coll`, `itTaruCann_Logic5_PickedUp`, `itTarucann_UnkMotion2_Anim`, `itTarucann_UnkMotion2_Phys`, `it_3F14_Logic5_Dropped`, `it_3F14_Logic5_Thrown`, `it_802969D8`, `itTarucann_UnkMotion6_Anim`, `itTarucann_UnkMotion6_Phys`, `itTarucann_UnkMotion6_Coll`, `it_80296E88`, `it_80296EA8`, `it_80296EF0`, `itTarucann_UnkMotion8_Anim`, `itTarucann_UnkMotion8_Phys`, `itTarucann_UnkMotion8_Coll`, `itTarucann_UnkMotion7_Anim`, `inline_itTarucann_UnkMotion7_Phys`, `itTarucann_UnkMotion7_Phys`, `itTarucann_UnkMotion7_Coll`, `it_802975F4`, `itTarucann_UnkMotion9_Anim_inline`, `itTarucann_UnkMotion9_Anim`, `itTarucann_UnkMotion9_Phys`, `itTarucann_UnkMotion9_Coll`, `it_80297790`, `itTaruCann_Logic5_DmgDealt`, `itTaruCann_Logic5_Clanked`, `itTaruCann_Logic5_HitShield`, `itTaruCann_Logic5_Reflected`, `itTaruCann_Logic5_EvtUnk`

## `src/melee/it/kinds/ittarucann.h`

53 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itthunder.c`

190 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `itthunder.h`, `Runtime/platform.h`, `inlines.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `itThunder_Logic7_Spawned`, `it_802CCB10`, `it_802CCB14`, `itThunder_UnkMotion1_Anim`, `itThunder_UnkMotion1_Phys`, `itThunder_UnkMotion1_Coll`, `it_802CCBF8`, `it_802CCC68`, `itThunder_UnkMotion2_Anim_inline2`, `itThunder_UnkMotion2_Anim`, `itThunder_UnkMotion2_Phys`, `itThunder_UnkMotion2_Coll`, `it_802CCE28`, `itThunder_UnkMotion0_Anim`, `itThunder_UnkMotion0_Phys_inline2`, `itThunder_UnkMotion0_Phys_inline`, `itThunder_UnkMotion0_Phys`, `itThunder_UnkMotion0_Coll`

## `src/melee/it/kinds/itthunder.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ittincle.c`

835 linhas; 61 definições aparentes; 0 marcadores asm.

Includes: `ittincle.h`, `melee/gr/ground.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/lb/lb_00B0.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `order_sdata2`, `it_802EB5C8`, `itTincle_Logic13_DmgReceived`, `itTincle_Logic13_DmgDealt`, `it_802EB6DC`, `itTincle_UnkMotion0_Anim`, `itTincle_UnkMotion0_Phys`, `itTincle_UnkMotion0_Coll`, `it_802EB870`, `itTincle_UnkMotion1_Anim`, `itTincle_UnkMotion1_Phys`, `itTincle_UnkMotion1_Coll`, `it_802EBA00`, `itTincle_UnkMotion2_Anim`, `itTincle_UnkMotion2_Phys`, `itTincle_UnkMotion2_Coll`, `it_802EBD14`, `itTincle_UnkMotion3_Anim`, `itTincle_UnkMotion3_Phys`, `itTincle_UnkMotion3_Coll`, `it_802EBE5C`, `itTincle_UnkMotion4_Anim`, `itTincle_UnkMotion4_Phys`, `itTincle_UnkMotion4_Coll`, `it_802EBFAC`, `itTincle_UnkMotion5_Anim`, `itTincle_UnkMotion5_Phys`, `itTincle_UnkMotion5_Coll`, `it_802EC18C`, `it_802EC1F4`, `itTincle_UnkMotion7_Anim`, `itTincle_UnkMotion7_Phys`, `itTincle_UnkMotion7_Coll`, `it_802EC35C`, `itTincle_UnkMotion8_Anim`, `itTincle_UnkMotion8_Phys`, `itTincle_UnkMotion8_Coll`, `it_802EC3F4`, `itTincle_UnkMotion9_Anim`, `itTincle_UnkMotion9_Phys`, `itTincle_UnkMotion9_Coll`, `it_802EC4D0`, `itTincle_UnkMotion10_Anim`, `itTincle_UnkMotion10_Phys`, `itTincle_UnkMotion10_Coll`, `it_802EC604`, `itTincle_UnkMotion11_Anim`, `itTincle_UnkMotion11_Phys`, `itTincle_UnkMotion11_Coll`, `it_802EC69C`, `itTincle_UnkMotion12_Anim`, `itTincle_UnkMotion12_Phys`, `itTincle_UnkMotion12_Coll`, `it_802EC830`, `it_802EC850`, `it_802EC870`, `it_802EC9E8`, `it_802ECA70`, `it_802ECC8C`, `it_802ECC98`, `it_802ECCA4`

## `src/melee/it/kinds/ittincle.h`

69 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ittogepy.c`

189 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `ittogepy.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itTogepy_Logic21_Spawned`, `it_802D3728`, `itTogepy_Logic21_EvtUnk`, `itTogepy_UnkMotion1_Anim`, `itTogepy_UnkMotion1_Phys`, `itTogepy_UnkMotion1_Coll`, `it_802D3848`, `itTogepy_UnkMotion6_Anim`, `itTogepy_UnkMotion6_Phys`, `itTogepy_UnkMotion6_Coll`, `it_802D39F8`, `itTogepy_UnkMotion0_Anim`, `itTogepy_UnkMotion0_Phys`, `itTogepy_UnkMotion0_Coll`

## `src/melee/it/kinds/ittogepy.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ittomato.c`

212 linhas; 25 definições aparentes; 0 marcadores asm.

Includes: `ittomato.h`, `inlines.h`, `melee/gm/gm_18A1.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802841B4`, `it_8028428C`, `itTomato_Logic9_Spawned`, `itTomato_Logic9_Destroyed`, `it_80284358`, `itTomato_UnkMotion0_Anim`, `itTomato_UnkMotion0_Phys`, `itTomato_UnkMotion0_Coll`, `it_802843E4`, `itTomato_UnkMotion1_Anim`, `itTomato_UnkMotion1_Phys`, `itTomato_UnkMotion1_Coll`, `it_80284458`, `itTomato_UnkMotion4_Anim`, `itTomato_UnkMotion4_Phys`, `itTomato_UnkMotion4_Coll`, `itTomato_Logic9_PickedUp`, `itTomato_UnkMotion3_Anim`, `itTomato_UnkMotion3_Phys`, `itTomato_Logic9_Dropped`, `itTomato_Logic9_EnteredAir`, `itTomato_UnkMotion5_Anim`, `itTomato_UnkMotion5_Phys`, `itTomato_UnkMotion5_Coll`, `itTomato_Logic9_EvtUnk`

## `src/melee/it/kinds/ittomato.h`

18 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ittools.c`

327 linhas; 19 definições aparentes; 0 marcadores asm.

Includes: `ittools.h`, `placeholder.h`, `inlines.h`, `melee/ft/ftlib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802EEFA8`, `itTools_Logic22_DmgDealt`, `it_802EF098`, `itTools_UnkMotion4_Anim`, `itTools_UnkMotion4_Phys`, `itTools_UnkMotion4_Coll`, `it_802EF320`, `itTools_UnkMotion9_Anim`, `itTools_UnkMotion9_Phys`, `itTools_UnkMotion9_Coll_inline`, `itTools_UnkMotion9_Coll`, `it_802EF548`, `itTools_Logic22_DmgReceived`, `it_2725_Logic22_Clanked`, `it_2725_Logic22_HitShield`, `it_2725_Logic22_Absorbed`, `itTools_Logic22_ShieldBounced`, `itTools_Logic22_Reflected`, `it_802EFA24`

## `src/melee/it/kinds/ittools.h`

28 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ittosakinto.c`

179 linhas; 15 definições aparentes; 0 marcadores asm.

Includes: `ittosakinto.h`, `Runtime/platform.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/itmaplib.h`, `melee/lb/lbaudio_ax.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802C8F4C`, `it_802C8FC4`, `it_802C8FE4`, `it_802C90E8`, `itTosakinto_UnkMotion2_Anim`, `itTosakinto_UnkMotion2_Phys`, `itTosakinto_UnkMotion2_Coll`, `it_802C93BC`, `itTosakinto_UnkMotion4_Anim`, `itTosakinto_UnkMotion4_Phys`, `itTosakinto_UnkMotion4_Coll`, `it_802C9468`, `itTosakinto_UnkMotion3_Phys`, `itTosakinto_UnkMotion3_Coll`, `itTosakinto_Logic0_Destroyed`

## `src/melee/it/kinds/ittosakinto.h`

25 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itunknown.c`

322 linhas; 23 definições aparentes; 0 marcadores asm.

Includes: `itunknown.h`, `math.h`, `inlines.h`, `melee/cm/camera.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/lb/lbvector.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `randi_perm`, `randi_perm_int`, `it_802CE710`, `it_802CE7CC`, `it_802CE7D0`, `itUnknown_UnkMotion0_Anim`, `itUnknown_UnkMotion0_Phys`, `itUnknown_UnkMotion0_Coll`, `it_802CE8D0`, `itUnknown_UnkMotion1_Anim`, `itUnknown_UnkMotion1_Phys`, `itUnknown_UnkMotion1_Coll`, `it_802CEC24`, `itUnknown_UnkMotion2_Anim`, `itUnknown_UnkMotion2_Phys`, `itUnknown_UnkMotion2_Coll`, `it_802CED54`, `it_2725_Logic38_Spawned`, `itUnknown_Logic38_EvtUnk`, `it_802CF0D4`, `it_802CF120`, `it_802CF154`, `it_802CF3D8`

## `src/melee/it/kinds/itunknown.h`

33 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itwhispyapple.c`

400 linhas; 34 definições aparentes; 0 marcadores asm.

Includes: `itwhispyapple.h`, `melee/it/forward.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itspawn.h`, `melee/lb/lb_00F9.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `itWhispyapple_UnkMotion0_Anim_inline`, `it_802EE200`, `it_802EE374`, `itWhispyapple_UnkMotion0_Anim`, `itWhispyapple_UnkMotion0_Phys`, `itWhispyapple_UnkMotion0_Coll_inline`, `itWhispyapple_UnkMotion0_Coll`, `it_802EE6A0`, `itWhispyapple_UnkMotion1_Anim`, `itWhispyapple_UnkMotion1_Phys`, `itWhispyapple_UnkMotion1_Coll`, `fn_802EE7FC`, `itWhispyapple_UnkMotion5_Anim`, `itWhispyapple_UnkMotion5_Phys`, `itWhispyapple_UnkMotion5_Coll`, `it_802EEA08`, `itWhispyapple_UnkMotion3_Anim`, `itWhispyapple_UnkMotion3_Phys`, `it_802EEA70`, `it_802EEB28`, `itWhispyApple_Logic18_EnteredAir`, `itWhispyapple_UnkMotion6_Anim`, `itWhispyapple_UnkMotion6_Phys`, `itWhispyapple_UnkMotion6_Coll`, `it_802EED00`, `itWhispyapple_UnkMotion7_Anim`, `itWhispyapple_UnkMotion7_Phys`, `itWhispyapple_UnkMotion7_Coll`, `it_802EEED0`, `it_802EEED8`, `it_802EEF10`, `it_802EEF30`, `it_802EEF68`, `it_802EEF88`

## `src/melee/it/kinds/itwhispyapple.h`

43 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itwhitebea.c`

857 linhas; 72 definições aparentes; 0 marcadores asm.

Includes: `itwhitebea.h`, `math.h`, `placeholder.h`, `inlines.h`, `itfreeze.h`, `melee/gr/gricemt.h`, `melee/gr/stage.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/mp/mpcoll.h`, `melee/mp/mplib.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802E31F8`, `itOldottosea_UnkMotion8_Anim`, `itOldottosea_UnkMotion8_Phys`, `it_802E32B4`, `it_802E3314`, `itOldottosea_UnkMotion9_Anim`, `itOldottosea_UnkMotion9_Phys`, `itOldottosea_UnkMotion9_Coll`, `it_802E3400`, `itOldottosea_UnkMotion10_Anim`, `itOldottosea_UnkMotion10_Phys`, `itOldottosea_UnkMotion10_Coll`, `it_2725_Logic3_Destroyed`, `it_802E3528`, `itOldottosea_UnkMotion11_Anim`, `itOldottosea_UnkMotion11_Phys`, `itOldottosea_UnkMotion11_Coll`, `it_802E35CC`, `it_802E3784`, `it_802E37A4`, `it_802E37BC`, `it_802E3884`, `fn_802E398C`, `itWhitebea_UnkMotion0_Anim`, `itWhitebea_UnkMotion0_Phys`, `itWhitebea_UnkMotion0_Coll`, `it_802E3AC8`, `itWhitebea_UnkMotion1_Anim`, `itWhitebea_UnkMotion1_Phys`, `itWhitebea_UnkMotion1_Coll`, `it_802E3DA0`, `itWhitebea_UnkMotion3_Anim`, `itWhitebea_UnkMotion3_Phys`, `itWhitebea_UnkMotion3_Coll`, `it_802E3ED0`, `itWhitebea_UnkMotion4_Anim`, `itWhitebea_UnkMotion4_Phys`, `itWhitebea_UnkMotion4_Coll`, `it_802E40A4`, `it_802E4190`, `itWhitebea_UnkMotion2_Anim`, `itWhitebea_UnkMotion2_Phys`, `itWhitebea_UnkMotion2_Coll`, `it_802E436C`, `itWhitebea_UnkMotion5_Anim`, `itWhitebea_UnkMotion5_Phys`, `itWhitebea_UnkMotion5_Coll`, `it_802E4464`, `itWhitebea_UnkMotion6_Anim`, `itWhitebea_UnkMotion6_Phys`, `itWhitebea_UnkMotion6_Coll`, `it_802E4558`, `itWhitebea_UnkMotion7_Anim`, `itWhitebea_UnkMotion7_Phys`, `itWhitebea_UnkMotion7_Coll`, `itWhiteBea_Logic9_PickedUp`, `itWhitebea_UnkMotion8_Anim`, `itWhitebea_UnkMotion8_Phys`, `it_2725_Logic9_Dropped`, `it_2725_Logic9_Thrown`, `itWhitebea_UnkMotion9_Anim`, `itWhitebea_UnkMotion9_Phys`, `itWhitebea_UnkMotion9_Coll`, `it_802E48B4`, `itWhitebea_UnkMotion10_Anim`, `itWhitebea_UnkMotion10_Phys`, `itWhitebea_UnkMotion10_Coll`, `it_802E4980`, `itWhitebea_UnkMotion11_Anim`, `itWhitebea_UnkMotion11_Phys`, `itWhitebea_UnkMotion11_Coll`, `it_802E4A24`

## `src/melee/it/kinds/itwhitebea.h`

82 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itwstar.c`

250 linhas; 25 definições aparentes; 0 marcadores asm.

Includes: `itwstar.h`, `placeholder.h`, `inlines.h`, `melee/ef/efasync.h`, `melee/ef/eflib.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/it_3F14.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/lb/lb_00F9.h`, `sysdolphin/baselib/jobj.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_80294364`, `it_80294430`, `it_802944AC`, `itWStar_Logic29_Spawned`, `it_8029455C`, `itWstar_UnkMotion0_Anim`, `itWstar_UnkMotion0_Phys`, `itWstar_UnkMotion0_Coll`, `it_80294624`, `itWstar_UnkMotion1_Anim`, `itWstar_UnkMotion1_Phys`, `itWstar_UnkMotion1_Coll`, `it_802946B0`, `it_3F14_Logic29_PickedUp`, `itWstar_UnkMotion3_Anim`, `itWStar_Logic29_Dropped`, `it_802947CC`, `itWstar_UnkMotion5_Anim`, `itWstar_UnkMotion5_Phys`, `itWstar_UnkMotion5_Coll`, `itWStar_Logic29_EnteredAir`, `itWstar_UnkMotion4_Anim`, `itWstar_UnkMotion4_Phys`, `itWstar_UnkMotion4_Coll`, `itWStar_Logic30_EvtUnk`

## `src/melee/it/kinds/itwstar.h`

38 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `melee/ft/kinds/ftCommon/forward.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ityaku.c`

220 linhas; 6 definições aparentes; 0 marcadores asm.

Includes: `ityaku.h`, `melee/it/forward.h`, `types.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_3F14.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/ithitbox.h`, `melee/it/itzako.h`, `melee/it/types.h`, `melee/lb/lb_00B0.h`

Definições aparentes: `it_802E6AEC`, `it_2E6A_UnkMotion19_Phys`, `it_2E6A_Logic117_DmgDealt`, `it_2E6A_Logic117_DmgReceived`, `it_802E7054`, `it_2E6A_Logic117_EvtUnk`

## `src/melee/it/kinds/ityaku.h`

22 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/gr/forward.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ityoshiegglay.c`

180 linhas; 13 definições aparentes; 0 marcadores asm.

Includes: `ityoshiegglay.h`, `melee/it/forward.h`, `inlines.h`, `types.h`, `melee/ef/efasync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCommonItems.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802F2F34`, `it_802F3020`, `it_27CF_UnkMotion1_Anim`, `it_27CF_UnkMotion1_Phys`, `it_27CF_UnkMotion1_Coll`, `it_802F317C`, `it_27CF_UnkMotion0_Anim`, `it_27CF_UnkMotion0_Phys`, `it_27CF_UnkMotion0_Coll`, `it_802F3290`, `it_27CF_UnkMotion2_Anim`, `it_27CF_Logic114_DmgReceived`, `it_27CF_Logic114_EvtUnk`

## `src/melee/it/kinds/ityoshiegglay.h`

27 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `melee/it/itCommonItems.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ityoshieggthrow.c`

201 linhas; 18 definições aparentes; 0 marcadores asm.

Includes: `ityoshieggthrow.h`, `melee/ef/efasync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`

Definições aparentes: `it_802B2890`, `it_802B28C8`, `it_802B2A10`, `itYoshiEggThrow_Logic43_PickedUp`, `it_802B2B08`, `itYoshieggthrow_UnkMotion1_Anim`, `itYoshieggthrow_UnkMotion1_Phys`, `itYoshieggthrow_UnkMotion1_Coll`, `it_802B2C04`, `spawn1`, `spawn2`, `it_802B2C38`, `itYoshieggthrow_UnkMotion2_Anim`, `it_2725_Logic43_Clanked`, `it_802B2E5C`, `it_802B2E7C`, `it_802B2F88`, `it_802B2FA8`

## `src/melee/it/kinds/ityoshieggthrow.h`

29 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ityoshistar.c`

113 linhas; 12 definições aparentes; 0 marcadores asm.

Includes: `ityoshistar.h`, `inlines.h`, `melee/db/db.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `it_802B2FC8`, `it_802B309C`, `it_802B30C0`, `it_802B30E4`, `it_802B3108`, `it_802B312C`, `it_802B314C`, `it_802B322C`, `itYoshistar_UnkMotion0_Anim`, `itYoshistar_UnkMotion0_Phys`, `itYoshistar_UnkMotion0_Coll`, `it_802B3348`

## `src/melee/it/kinds/ityoshistar.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/ityoshitongue.c`

75 linhas; 5 definições aparentes; 0 marcadores asm.

Includes: `ityoshitongue.h`, `Runtime/platform.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftYoshi/ftyoshispecialn.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_279C.h`, `melee/it/item.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/lb/lb_00B0.h`

Definições aparentes: `it_802F2BFC`, `it_2F2B_UnkMotion0_Anim`, `it_2F2B_UnkMotion0_Phys`, `it_2F2B_UnkMotion0_Coll`, `it_802F2CE0`

## `src/melee/it/kinds/ityoshitongue.h`

14 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itzeldadinfire.c`

320 linhas; 17 definições aparentes; 0 marcadores asm.

Includes: `itzeldadinfire.h`, `melee/it/forward.h`, `sysdolphin/baselib/forward.h`, `math.h`, `inlines.h`, `itzeldadinfireexplode.h`, `melee/db/db.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/ft/ftlib.h`, `melee/ft/kinds/ftZelda/ftzeldaspeciallw.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `itZeldaDinFire_GetOwner`, `it_802C3AFC`, `it_802C3BAC`, `itZeldaDinFire_Logic65_Destroyed`, `it_802C3D44`, `it_802C3D74`, `itZeldadinfire_UnkMotion0_Anim_inline`, `itZeldadinfire_UnkMotion0_Anim`, `itZeldadinfire_UnkMotion1_Anim`, `itZeldadinfire_UnkMotion0_Phys`, `itZeldadinfire_UnkMotion1_Phys`, `itZeldadinfire_UnkMotion0_Coll`, `itZeldadinfire_UnkMotion1_Coll`, `itZeldaDinFire_Logic65_Reflected`, `itZeldaDinFire_Logic65_Clanked`, `itZeldaDinFire_Logic65_Absorbed`, `itZeldaDinFire_Logic65_EvtUnk`

## `src/melee/it/kinds/itzeldadinfire.h`

30 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/ft/forward.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itzeldadinfireexplode.c`

162 linhas; 11 definições aparentes; 0 marcadores asm.

Includes: `itzeldadinfireexplode.h`, `placeholder.h`, `inlines.h`, `melee/cm/camera.h`, `melee/db/db.h`, `melee/ef/eflib.h`, `melee/ef/efsync.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/itCharItems.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `sysdolphin/baselib/gobj.h`, `sysdolphin/baselib/jobj.h`

Definições aparentes: `it_802C4580`, `itZeldaDinFireExplode_Logic66_Destroyed`, `it_802C46C4`, `itZeldadinfireexplode_UnkMotion0_Anim`, `itZeldadinfireexplode_UnkMotion0_Phys`, `itZeldadinfireexplode_UnkMotion0_Coll`, `itZeldaDinFireExplode_Logic66_Clanked`, `itZeldaDinFireExplode_Logic66_Absorbed`, `itZeldaDinFireExplode_Logic66_ShieldBounced`, `itZeldaDinFireExplode_Logic66_HitShield`, `itZeldaDinFireExplode_Logic66_EvtUnk`

## `src/melee/it/kinds/itzeldadinfireexplode.h`

23 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itzgshell.c`

966 linhas; 61 definições aparentes; 0 marcadores asm.

Includes: `itzgshell.h`, `inlines.h`, `itnokonoko.h`, `melee/cm/camera.h`, `melee/ef/efasync.h`, `melee/gr/grzakogenerator.h`, `melee/it/inlines.h`, `melee/it/it_26B1.h`, `melee/it/it_2725.h`, `melee/it/it_3F14.h`, `melee/it/itcoll.h`, `melee/it/item.h`, `melee/it/itgroundcoll.h`, `melee/it/ithitbox.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/lb/lb_00B0.h`, `melee/mp/mpcoll.h`, `sysdolphin/baselib/random.h`

Definições aparentes: `it_802DDB38`, `it_802DDBE8`, `fn_802DDC8C`, `it_802DDD38`, `get_attrs`, `it_802DDEB4`, `it_802DE040`, `it_802DE0F0`, `itZrshell_UnkMotion0_Anim`, `itZrshell_UnkMotion0_Phys`, `itZrshell_UnkMotion0_Coll`, `it_802DE320`, `itZrshell_UnkMotion1_Anim`, `itZrshell_UnkMotion1_Phys`, `itZrshell_UnkMotion1_Coll`, `it_2725_Logic11_PickedUp`, `itZrshell_UnkMotion2_Anim`, `itZrshell_UnkMotion2_Phys`, `itZGShell_Logic11_Thrown`, `itZrshell_UnkMotion3_Anim`, `itZrshell_UnkMotion3_Phys`, `itZrshell_UnkMotion3_Coll`, `itZGShell_Logic11_Dropped`, `itZrshell_UnkMotion4_Anim`, `itZrshell_UnkMotion4_Phys`, `itZrshell_UnkMotion4_Coll`, `it_802DE6F0`, `itZrshell_UnkMotion6_Anim`, `itZrshell_UnkMotion6_Phys`, `itZrshell_UnkMotion6_Coll`, `it_802DEC80`, `itZrshell_UnkMotion8_Anim`, `itZrshell_UnkMotion8_Phys`, `itZrshell_UnkMotion8_Coll`, `it_2725_Logic11_EnteredAir`, `itZrshell_UnkMotion9_Anim`, `itZGShell_StopAndIdle`, `itZrshell_UnkMotion9_Phys`, `itZrshell_UnkMotion9_Coll`, `it_802DF230`, `itZrshell_UnkMotion11_Anim`, `itZrshell_UnkMotion11_Phys`, `itZrshell_UnkMotion11_Coll`, `it_802DF9F8`, `itZrshell_UnkMotion10_Anim`, `itZrshell_UnkMotion10_Phys`, `itZrshell_UnkMotion10_Coll`, `itZGShell_Logic11_DmgDealt`, `itZGShell_Logic11_DmgReceived`, `itZGShell_Logic11_Reflected`, `it_2725_Logic11_Clanked`, `it_2725_Logic11_HitShield`, `itZGShell_Logic11_ShieldBounced`, `fn_802DFE7C`, `it_802DFED4`, `itZGShell_Logic11_Destroyed`, `it_802DFF14`, `it_802DFFA0`, `it_802DFFB8`, `it_802E0100`, `keep_data`

## `src/melee/it/kinds/itzgshell.h`

70 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `dolphin/mtx.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/itzrshell.c`

133 linhas; 14 definições aparentes; 0 marcadores asm.

Includes: `itzrshell.h`, `itnokonoko.h`, `itzgshell.h`, `melee/gr/grzakogenerator.h`, `melee/it/it_26B1.h`, `melee/it/item.h`, `melee/it/itmaplib.h`, `melee/it/itzako.h`, `melee/it/types.h`, `sysdolphin/baselib/gobj.h`

Definições aparentes: `it_802E02E8`, `itZRShell_Logic12_PickedUp`, `itZRShell_Logic12_Thrown`, `itZRShell_Logic12_Dropped`, `itZRShell_Logic12_EnteredAir`, `itZRShell_Logic12_Destroyed`, `itZRShell_Logic12_DmgDealt`, `itZRShell_Logic12_DmgReceived`, `itZRShell_Logic12_Reflected`, `itZRShell_Logic12_Clanked`, `itZRShell_Logic12_HitShield`, `itZRShell_Logic12_ShieldBounced`, `it_802E0468`, `it_802E0488`

## `src/melee/it/kinds/itzrshell.h`

26 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/forward.h`, `melee/it/kinds/types.h`

## `src/melee/it/kinds/types.h`

52 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/it/kinds/forward.h`, `sysdolphin/baselib/forward.h`

## `src/melee/it/types.h`

876 linhas; 0 definições aparentes; 0 marcadores asm.

Includes: `Runtime/platform.h`, `melee/cm/forward.h`, `melee/ef/forward.h`, `melee/it/forward.h`, `melee/it/kinds/forward.h`, `sysdolphin/baselib/forward.h`, `dat_macros.h`, `placeholder.h`, `dolphin/gx.h`, `dolphin/mtx.h`, `melee/ft/types.h`, `melee/it/itCharItems.h`, `melee/it/itCommonItems.h`, `melee/it/itPKFlash.h`, `melee/it/itPKThunder.h`, `melee/lb/types.h`

