import re,hashlib,json
from pathlib import Path
project=Path('outputs/Melee360');file=Path('work/melee-base/libs/dolphin/src/dolphin/thp/THPDec.c');source=file.read_text()
clean=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"',lambda m:' '*len(m[0]),source,flags=re.S)
out=['/* Original THP header/parser CPU path; Gekko IDCT is not compiled. */','#include <dolphin/thp/thp.h>','#include <string.h>','#define THPROUNDUP(a,b) ((((s32)(a))+((s32)(b)-1L))/((s32)(b)))']
manifest=[]
for pattern in [r'static char __THP420Error\[\].*?;',r'static const u8 __THPJpegNaturalOrder\[80\] = \{.*?\};',r'static const f64 __THPAANScaleFactor\[8\] = \{.*?\};',r'typedef struct THPVideoDecodeHeader \{.*?\} THPVideoDecodeHeader;']:
 out.append(re.search(pattern,source,re.S).group(0))
names=['THPDec_8032F8D4','THPDec_8032FD40','THPVideoDecode','THPDec_803300E0','THPDec_80330158','THPDec_803302EC','__THPReadFrameHeader','__THPReadQuantizationTable','__THPReadHuffmanTableSpecification','__THPReadScaneHeader','__THPHuffGenerateSizeTable','__THPHuffGenerateCodeTable','__THPHuffGenerateDecoderTables','THPDec_803310CC','__THPRestartDefinition']
out.append('u8 THPDec_803310CC(THPFileInfo*);')
for name in names:
 m=re.search(r'(?m)^(?:static\s+)?(?:void|u8|s32|int|THPFileInfo\*)\s+'+name+r'\s*\([^;{}]*\)\s*\{',clean)
 if not m:raise Exception(name)
 end=m.end();depth=1
 while depth:
  depth+=(clean[end]=='{')-(clean[end]=='}');end+=1
 body=source[m.start():end];adapt=[]
 if name=='THPVideoDecode':body=body.replace('DCZeroRange(info, 0x920);','memset(info, 0, 0x920);');adapt=['zero aligned native work with memset rather than Gekko cache-line zero']
 if name=='THPDec_803300E0':body=body.replace('OSRoundUp32B(info->scratch)','OSRoundUp32B((u32)info->scratch)');adapt=['explicit 32-bit address cast for OSRoundUp32B macro on XDK']
 out.append(body);manifest.append({'function':name,'source':str(file),'line':source[:m.start()].count('\n')+1,'bodySha256':hashlib.sha256(source[m.start():end].encode()).hexdigest(),'adaptations':adapt})
# Translate the original locked-cache layout to an actual native RAM workspace.
for pattern in [r'struct THPLCWork \{.*?\};',r'struct THPLCSizeEntry \{.*?\};',r'struct THPInitWork \{.*?\};',r'static struct THPLCSizeEntry __THPLCSizeTableA\[5\] = \{.*?\};',r'static struct THPLCSizeEntry __THPLCSizeTableB\[9\] = \{.*?\};']:
 out.append(re.search(pattern,source,re.S).group(0))
out.append('static __declspec(align(32)) u8 Melee360THPCache[0x4000];\nstatic struct THPInitWork Melee360THPWork;')
m=re.search(r'(?m)^void THPInit\(void\)\s*\{',clean);end=m.end();depth=1
while depth:
 depth+=(clean[end]=='{')-(clean[end]=='}');end+=1
original=source[m.start():end];body=original.replace('(struct THPInitWork*) &__THPLC','&Melee360THPWork')
body=re.sub(r'    if \(\(PPCMfhid2\(\) & 0x10000000\) == 0\) \{.*?\n    \}', '    /* Xenon CPU decoder workspace uses native RAM, not the Gekko LC address. */',body,flags=re.S)
body=body.replace('(u8*) 0xE0000000','Melee360THPCache').replace('    OSInitFastCast();','    /* No paired-single/GQR instructions in this native CPU header path. */')
out.append(body);manifest.append({'function':'THPInit','source':str(file),'line':source[:m.start()].count('\n')+1,'bodySha256':hashlib.sha256(original.encode()).hexdigest(),'adaptations':['native aligned 16 KiB RAM workspace replaces locked-cache absolute address; one explicit aggregate replaces linker-adjacent objects; GQR setup is specific to pending Gekko decoder, not used by native header path']})
out.append("""
int Melee360THPWorkLayoutProbe(void){u8* p=Melee360THPCache;int j,i;THPInit();
 for(j=0;j<2;++j){for(i=0;i<5;++i){if(Melee360THPWork.cache.offsets512[j][i]!=p)return 0;p+=i?0x400:0x1000;}}
 if(p!=Melee360THPCache+0x4000)return 0;p=Melee360THPCache;
 for(j=0;j<2;++j){for(i=0;i<9;++i){if(Melee360THPWork.cache.offsets672[j][i]!=p)return 0;p+=i?0x200:0x1000;}}
 if(p!=Melee360THPCache+0x4000||Melee360THPWork.cache.work512[1]!=Melee360THPCache+0x2000||Melee360THPWork.cache.work512[2]!=Melee360THPCache+0x2800||Melee360THPWork.work672[1]!=Melee360THPCache+0x2800||Melee360THPWork.work672[2]!=Melee360THPCache+0x3200)return 0;
 Melee360THPWork.work672[2][0x9ff]=0x57;THPInit();return Melee360THPCache[0x3bff]==0x57;
}
""")
out.append('typedef char Melee360THPInfoLayout[(sizeof(THPFileInfo)==0x908)?1:-1];')
(project/'compat/generated/portable_thp_headers.c').write_text('\n\n'.join(out)+'\n')
(project/'logs/portable-thp-provenance.json').write_text(json.dumps(manifest,indent=2))
print('Extracted 15 original THP header/parser functions')
