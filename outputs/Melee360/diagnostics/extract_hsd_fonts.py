import argparse, hashlib, json, struct
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--dol',required=True);p.add_argument('--project',required=True);a=p.parse_args()
dol=Path(a.dol);project=Path(a.project);data=dol.read_bytes()
if hashlib.sha1(data).hexdigest()!='08e0bf20134dfcb260699671004527b2d6bb1a45':raise RuntimeError('Requires verified GALE01 1.02 main.dol')
u32=lambda off:struct.unpack_from('>I',data,off)[0]
out=project/'compat/sysdolphin/baselib';out.mkdir(parents=True,exist_ok=True);manifest=[]
for name,address,size,stride in [('sislib_font',0x8040CD40,287*512,512),('debug_font',0x804088B8,0x1C00,56)]:
    offset=None
    for i in range(18):
        start,count,fileoff=u32(0x48+4*i),u32(0x90+4*i),u32(4*i)
        if count and address>=start and address+size<=start+count:offset=fileoff+address-start;break
    if offset is None or offset+size>len(data):raise RuntimeError('Font range outside DOL: '+name)
    atlas=data[offset:offset+size];lines=['/* Locally extracted original font; GALE01 1.02 DOL verified. */']
    for i in range(0,size,stride):
        lines.append('{{')
        for j in range(i,i+stride,16):lines.append(','.join('0x%02X'%b for b in atlas[j:min(j+16,i+stride)])+',')
        lines.append('}},')
    (out/(name+'.inc')).write_text('\n'.join(lines)+'\n',encoding='ascii')
    manifest.append({'name':name,'address':hex(address),'bytes':size,'glyphs':size//stride,'sha256':hashlib.sha256(atlas).hexdigest()})
(project/'logs/hsd-font-provenance.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
print('Extracted original HSD font includes:',[(m['name'],m['bytes']) for m in manifest])
