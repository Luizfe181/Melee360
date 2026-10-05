import argparse, hashlib, json, re
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--base',required=True);p.add_argument('--project',required=True);a=p.parse_args()
base,project=Path(a.base),Path(a.project)
groups={'mtx.c':['C_MTXIdentity','C_MTXCopy','C_MTXConcat','C_MTXTranspose','C_MTXInverse','C_MTXInvXpose','C_MTXRotTrig','C_MTXRotAxisRad','C_MTXScale','C_MTXQuat','C_MTXLookAt','MTXTransApply','MTXScaleApply'],
        'vec.c':['C_VECAdd','C_VECSubtract','C_VECScale','C_VECNormalize','C_VECSquareMag','C_VECMag','C_VECDotProduct','C_VECCrossProduct','C_VECSquareDistance'],
        'mtxvec.c':['C_MTXMultVec','C_MTXMultVecSR','C_MTXMultVecArray'],
        'mtx44.c':['MTXFrustum','MTXPerspective','MTXOrtho'],
        '../gx/GXTransform.c':['GXProject']}
groups['mtx.c'] += ['MTXRotRad','MTXLightFrustum','MTXLightPerspective','MTXLightOrtho']
out=['/* Generated unchanged C implementations; paired-single assembly excluded. */','#define DEBUG 1','#include <dolphin/mtx.h>','#include <sysdolphin/baselib/debug.h>','#include <math.h>','#undef sinf','#undef cosf','extern float sinf(float);','extern float cosf(float);','#define MTXRotTrig C_MTXRotTrig','#define ASSERTMSGLINE(line,condition,message) HSD_ASSERTREPORT(line,condition,message)']
manifest=[]
for filename,names in groups.items():
    file=base/'libs/dolphin/src/dolphin/mtx'/filename;text=file.read_text(encoding='utf-8')
    clean=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"',lambda m:' '*len(m[0]),text,flags=re.S)
    for name in names:
        m=re.search(r'(?m)^(?:void|u32|f32)\s+'+name+r'\s*\([^;{}]*\)\s*\{',clean)
        if not m:raise RuntimeError('Missing '+name)
        start=m.start();brace=m.end()-1;depth=1;end=brace+1
        while depth:
            if clean[end]=='{':depth+=1
            elif clean[end]=='}':depth-=1
            end+=1
        body=text[start:end];out.append(body)
        manifest.append({'function':name,'source':str(file),'fileSha256':hashlib.sha256(file.read_bytes()).hexdigest(),'bodySha256':hashlib.sha256(body.encode()).hexdigest()})
dest=project/'compat/generated/portable_mtx.c';dest.parent.mkdir(parents=True,exist_ok=True);dest.write_text('\n\n'.join(out)+'\n',encoding='utf-8')
(project/'logs/portable-mtx-provenance.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
print('Extracted',len(manifest),'original C matrix/vector functions.')
