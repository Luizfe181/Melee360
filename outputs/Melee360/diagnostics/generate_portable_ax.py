import re,hashlib,json
from pathlib import Path
project=Path('outputs/Melee360');base=Path('work/melee-base/libs/dolphin/src/dolphin/ax')
out=['/* Original AX CPU control. DSP execution is deliberately not emulated here. */','#include <dolphin/ax.h>','#include <dolphin/os.h>','#include <string.h>','#include <sysdolphin/baselib/debug.h>','#define ASSERTLINE(line,c) HSD_ASSERTREPORT(line,c,"AX argument validation")','#define ASSERTMSGLINE(line,c,msg) HSD_ASSERTREPORT(line,c,msg)']
manifest=[]
def add(file,names):
 text=(base/file).read_text();clean=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"',lambda m:' '*len(m[0]),text,flags=re.S)
 for name in names:
  m=re.search(r'(?m)^(?:void|u32|AXVPB\*)\s+'+name+r'\s*\([^;{}]*\)\s*\{',clean)
  if not m:raise Exception(name)
  end=m.end();depth=1
  while depth:
   depth+=(clean[end]=='{')-(clean[end]=='}');end+=1
  body=text[m.start():end];original_hash=hashlib.sha256(body.encode()).hexdigest();adaptations=[]
  if name=='AXSetVoiceUpdateWrite':
   body=body.replace('p->updateCounter += 2;', 'ASSERTMSGLINE(0x43F, p->updateMS <= 4 && param < sizeof(AXPB)/2, "Invalid native PB update\\n");\n    p->pb.update.updNum[p->updateMS]++;\n    p->updateCounter += 2;')
   adaptations=['native per-ms count recorded when queuing update pair; offset/MS bounds checked']
  out.append(body);manifest.append({'function':name,'source':str(base/file),'line':text[:m.start()].count('\n')+1,'bodySha256':original_hash,'adaptedBodySha256':hashlib.sha256(body.encode()).hexdigest(),'adaptations':adaptations})
out += ['static u16 __AXHRTFHistory[128];','u32 __AXClMode;']
add('AXCL.c',['AXSetMode','AXGetMode'])
alloc=(base/'AXAlloc.c').read_text();out.append(alloc[alloc.index('static AXVPB*'):]);manifest.append({'module':'AXAlloc.c','sha256':hashlib.sha256(alloc.encode()).hexdigest(),'adaptations':['includes consolidated into generated unit']})
# Forward declarations used by the original allocator and voice initialization.
out.insert(7,'void __AXRemoveFromStack(AXVPB*);\nvoid __AXPushFreeStack(AXVPB*);\nAXVPB* __AXPopCallbackStack(void);\nvoid __AXSetPBDefault(AXVPB*);')
out += ['static AXPB __AXPB[AX_MAX_VOICES] ATTRIBUTE_ALIGN(32);','static AXPBITDBUFFER __AXITD[AX_MAX_VOICES] ATTRIBUTE_ALIGN(32);','static AXPBU __AXUpdates[AX_MAX_VOICES] ATTRIBUTE_ALIGN(32);','static AXVPB __AXVPB[AX_MAX_VOICES];','static u32 __AXMaxDspCycles, __AXRecDspCycles;','typedef char Melee360AXPBLayout[(sizeof(AXPB)==0xC0)?1:-1];','typedef char Melee360AXVPBLayout[(sizeof(AXVPB)==0x1F8)?1:-1];']
add('AXVPB.c',['__AXSetPBDefault','__AXVPBInit','AXSetVoiceState','AXSetVoiceMix','AXSetVoiceItdOn','AXSetVoiceItdTarget','AXSetVoiceVe','AXSetVoiceVeDelta','AXSetVoiceAddr','AXSetVoiceLoop','AXSetVoiceLoopAddr','AXSetVoiceEndAddr','AXSetVoiceCurrentAddr','AXSetVoiceAdpcm','AXSetVoiceSrc','AXSetVoiceSrcRatio','AXSetVoiceAdpcmLoop','AXSetVoiceSrcType','AXSetVoiceType','AXSetVoiceFir','AXSetVoiceDpop','AXSetVoiceUpdateIncrement','AXSetVoiceUpdateWrite'])
aux=(base/'AXAux.c').read_text()
# Native AX may be initialized more than once. Clear every ring slot,
# and enable B's input from B's callback rather than A's registration.
aux=aux.replace('i < 0x1E0', 'i < 3 * 480')
aux=re.sub(r'void __AXGetAuxBInput\(u32\* p\).*?\n}',lambda m:m[0].replace('__AXCallbackAuxA','__AXCallbackAuxB'),aux,flags=re.S)
out.append(aux[aux.index('static long'):]);manifest.append({'compilerAdaptation':'ATTRIBUTE_ALIGN(32) suffix becomes prefix __declspec(align(32)); allocation layouts unchanged'})
manifest.append({'nativeAdaptations':['AXAuxInit clears all 3 ring slots on reinitialization','AXGetAuxBInput depends on AuxB callback registration, independently of AuxA'],'source':'AXAux.c','originalSha256':hashlib.sha256((base/'AXAux.c').read_bytes()).hexdigest()})
manifest.append({'module':'AXAux.c','sha256':hashlib.sha256((base/'AXAux.c').read_text().encode()).hexdigest(),'adaptedSha256':hashlib.sha256(aux.encode()).hexdigest(),'adaptations':['includes consolidated into generated unit','clear all ring slots on native reinitialization','AuxB input uses its own callback registration']})
spb=(base/'AXSPB.c').read_text()
out.append(spb[spb.index('// .bss'):])
manifest.append({'module':'AXSPB.c','sha256':hashlib.sha256(spb.encode()).hexdigest(),'adaptations':['includes consolidated; native PPC32 studio layout preserved']})
generated=re.sub(r'static ([^;\n]+) ATTRIBUTE_ALIGN\(32\);',r'static __declspec(align(32)) \1;','\n\n'.join(out)+'\n')
(project/'compat/generated/portable_ax.c').write_text(generated)
(project/'logs/portable-ax-provenance.json').write_text(json.dumps(manifest,indent=2))
print('Generated AX CPU control, original allocator and auxiliary rings')
