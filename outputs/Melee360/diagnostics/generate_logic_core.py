from pathlib import Path
import hashlib
root=Path(__file__).resolve().parents[3]
base=root/'work/melee-base/src/melee'
out=root/'outputs/Melee360/compat/generated/original_logic_core.inc'
items=[('mp/mplib.c',['mpLineIntersection','mpLineIntersectionH','mpLineIntersectionV']),('ft/ftcommon.c',['ftCommon_CalcSelfAccel_Deaccel','ftCommon_CalcSelfAccel_AccelToVelClampedFrom','ftCommon_CalcSelfAccel_AccelToVelClamped','ftCommon_CalcSelfAccel_DriftFrom','ftCommon_CalcSelfAccel_AccelToVel','ftCommon_CalcSelfAccel_DriftSimple','ftCommon_CalcSelfAccel_DriftSimple_NoFriction','ftCommon_ClampSelfVelX','ftCommon_ClampAirDrift','ftCommon_Fall','ftCommon_FallBasic','ftCommon_FallFast','ftCommon_ClampFallSpeed','ftCommon_Ascend','ftCommon_UseAllJumps','ftCommon_UnlockECB'])]
def body(s,name):
 import re
 match=re.search(r'^(?:bool|void) '+name+r'\([^;{]*\)\s*\{',s,re.M)
 if not match:raise ValueError(name)
 a=match.start();b=s.index('{',a);d=1;e=b+1
 while d:
  d+=(s[e]=='{')-(s[e]=='}');e+=1
 return s[a:e]
text='/* Original standalone logic subset; bodies unchanged; names isolated from full-runtime linkage. */\n'
for path,names in items:
 source=base/path;s=source.read_text();text+='/* '+path+' SHA256 '+hashlib.sha256(source.read_bytes()).hexdigest()+' */\n'
 for name in names:text+='#define '+name+' M360_'+name+'\n'
 for name in names:text+=body(s,name)+'\n'
out.write_text(text)
