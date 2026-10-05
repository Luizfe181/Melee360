import argparse, hashlib, json, re
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--base',required=True);p.add_argument('--project',required=True);a=p.parse_args()
base,project=Path(a.base),Path(a.project)
out=['/* Original GX CPU functions and fog register translation. No GPU command stubs. */',
 '#include <dolphin/gx.h>', '#include <sysdolphin/baselib/debug.h>', '#include <math.h>', '#include <string.h>',
 '#undef cosf', 'extern float cosf(float);',
 '#define ASSERTMSGLINE(line,condition,message) HSD_ASSERTREPORT(line,condition,message)',
 '#define ASSERTMSGLINEV(line,condition,...) HSD_ASSERTREPORT(line,condition,"GX argument validation")',
 'GXBool __GXinBegin = GX_FALSE;', 'extern void Melee360GXRegisterTextureImage(GXTexObj*, const void*);', 'extern void Melee360GXRegisterPaletteImage(GXTlutObj*,const void*,u32,u32);',
 '#define CHECK_GXBEGIN(line,name) ASSERTMSGLINE(line,!__GXinBegin,"GX object operation during primitive")',
 '#define GET_REG_FIELD(reg,size,shift) ((int)((reg)>>(shift)) & ((1<<(size))-1))',
 '#define SET_REG_FIELD(line,reg,size,shift,value) ((reg)=((reg)&~(((1u<<(size))-1u)<<(shift)))|(((unsigned int)(value)&((1u<<(size))-1u))<<(shift)))',
 'static unsigned int Melee360LeadingZeros(unsigned int x){unsigned int n=0;if(!x)return 32;while(!(x&0x80000000U)){++n;x<<=1;}return n;}',
 '#define __cntlzw Melee360LeadingZeros', 'extern void Melee360GXWriteFogRegister(u32);', '#define GX_WRITE_RAS_REG(value) Melee360GXWriteFogRegister(value)']
manifest=[]
groups={'GXLight.c':['GXInitLightAttn','GXInitLightAttnA','GXGetLightAttnA','GXInitLightAttnK','GXGetLightAttnK','GXInitLightSpot','GXInitLightDistAttn','GXInitLightPos','GXGetLightPos','GXInitLightDir','GXGetLightDir','GXInitSpecularDir','GXInitSpecularDirHA','GXInitLightColor','GXGetLightColor'],
 'GXTexture.c':['__GXGetTexTileShift','GXGetTexBufferSize','__GetImageTileCount','GXGetTexObjWidth','GXGetTexObjHeight','GXGetTexObjFmt','GXInitTexObj','GXInitTexObjCI','GXInitTexObjData','GXInitTexObjLOD','GXInitTlutObj'], 'GXPixel.c':['GXInitFogAdjTable','GXSetFog','GXSetFogRangeAdj'], 'GXMisc.c':['GXCompressZ16','GXDecompressZ16']}
for filename,names in groups.items():
 file=base/'libs/dolphin/src/dolphin/gx'/filename;text=file.read_text(encoding='utf-8')
 clean=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"',lambda m:' '*len(m[0]),text,flags=re.S)
 pattern=r'(?m)^struct __GXLightObjInt_struct \{.*?\};' if filename=='GXLight.c' else r'(?ms)^typedef struct __GXTexObjInt_struct \{.*?\} __GXTexObjInt;'
 if filename in ('GXLight.c','GXTexture.c'):
  struct=re.search(pattern,text,re.S).group(0);out.append(struct)
  if filename=='GXTexture.c':
   out.append(re.search(r'(?ms)^typedef struct __GXTlutObjInt_struct \{.*?\} __GXTlutObjInt;',text).group(0))
   out.append(re.search(r'(?m)^static u8 GX2HWFiltConv\[6\].*?;',text).group(0))
 for name in names:
  m=re.search(r'(?m)^(?:static\s+)?(?:void|u16|u32|GXTexFmt)\s+'+name+r'\s*\([^;{}]*\)\s*\{',clean)
  if not m:raise RuntimeError('Missing '+name)
  start=m.start();depth=1;end=m.end()
  while depth:
   if clean[end]=='{':depth+=1
   elif clean[end]=='}':depth-=1
   end+=1
  body=text[start:end]
  original_body=body
  if name in ('GXSetFog','GXSetFogRangeAdj'): body=body.replace('    gx->bpSent = 0;', '    /* Register writes update the native shader state, not a GX FIFO. */')
  if name in ('GXInitTexObj','GXInitTexObjData'): body=body[:-1]+'    Melee360GXRegisterTextureImage(obj, image_ptr);\n}'
  if name=='GXInitTlutObj': body=body[:-1]+'    Melee360GXRegisterPaletteImage(tlut_obj,lut,fmt,n_entries);\n}'
  out.append(body)
  manifest.append({'function':name,'source':str(file),'line':text[:start].count('\n')+1,'fileSha256':hashlib.sha256(file.read_bytes()).hexdigest(),'bodySha256':hashlib.sha256(original_body.encode()).hexdigest(),'adaptations':['native fog register sink replaces FIFO and bpSent cache'] if name in ('GXSetFog','GXSetFogRangeAdj') else ['capture original image pointer for Xenon address preservation'] if name in ('GXInitTexObj','GXInitTexObjData','GXInitTlutObj') else []})
file=base/'libs/dolphin/src/dolphin/gx/GXFrameBuf.c';text=file.read_text(encoding='utf-8')
for name in ('GXNtsc480Int','GXNtsc480IntDf','GXNtsc480Prog','GXNtsc480ProgAa','GXNtsc480IntAa'):
 m=re.search(r'(?ms)^GXRenderModeObj '+name+r' = \{.*?\};',text)
 body=m.group(0);out.append(body);manifest.append({'object':name,'source':str(file),'line':text[:m.start()].count('\n')+1,'fileSha256':hashlib.sha256(file.read_bytes()).hexdigest(),'bodySha256':hashlib.sha256(body.encode()).hexdigest()})
out.append('typedef char Melee360GXLightLayout[(sizeof(struct __GXLightObjInt_struct)==sizeof(GXLightObj))?1:-1];\ntypedef char Melee360GXTextureLayout[(sizeof(__GXTexObjInt)==sizeof(GXTexObj))?1:-1];')
(project/'compat/generated/portable_gx.c').write_text('\n\n'.join(out)+'\n',encoding='utf-8')
(project/'logs/portable-gx-provenance.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
print('Extracted',sum('function' in m for m in manifest),'original GX CPU/register functions and',sum('object' in m for m in manifest),'original mode objects.')

