"""Read unmodified DAT relocation tables and decode referenced HSD image descriptors."""
import json, pathlib, struct, subprocess, sys
from PIL import Image

assets, exe, output = map(pathlib.Path, sys.argv[1:4])
output.mkdir(parents=True, exist_ok=True)
manifest = []
tiles = {0:(8,8,32),1:(8,4,32),2:(8,4,32),3:(4,4,32),4:(4,4,32),5:(4,4,32),6:(4,4,64),8:(8,8,32),9:(8,4,32),10:(4,4,32),14:(8,8,32)}
for name in ['NtMemAc.usd','GmTitle.usd','MnMaAll.usd']:
    raw=(assets/name).read_bytes()
    size,ds,nr,np,ne=struct.unpack_from('>5I',raw)
    if size!=len(raw) or 32+ds+nr*4+(np+ne)*8>size: raise ValueError(name)
    data=raw[32:32+ds]
    rel=set(struct.unpack_from('>'+str(nr)+'I',raw,32+ds))
    u32=lambda off: struct.unpack_from('>I',data,off)[0]
    seen=set()
    # Image descriptor is reached through the relocated TObj image field (+76).
    for field in sorted(rel):
        tobj=field-76
        if tobj<0 or tobj+92>ds: continue
        if u32(tobj+8)>7 or u32(tobj+12)>20 or u32(tobj+52)>2 or u32(tobj+56)>2 or u32(tobj+72)>1: continue
        desc=u32(field)
        if desc in seen or desc+24>ds or desc not in rel: continue
        image,w,h,fmt,mip=struct.unpack_from('>IHHII',data,desc)
        if fmt not in tiles or not 1<=w<=1024 or not 1<=h<=1024 or mip not in (0,1): continue
        bw,bh,b=tiles[fmt]; count=((w+bw-1)//bw)*((h+bh-1)//bh)*b
        if image+count>ds: continue
        palette=b'';entries=pf=0
        if fmt in (8,9,10):
            if tobj+80 not in rel: continue
            tlut=u32(tobj+80)
            if tlut+16>ds or tlut not in rel: continue
            paloff,pf,_=struct.unpack_from('>3I',data,tlut)
            entries=struct.unpack_from('>H',data,tlut+12)[0]
            if not 1<=entries<=16384 or pf>2 or paloff+entries*2>ds: continue
            palette=data[paloff:paloff+entries*2]
        seen.add(desc)
        stem=f'{pathlib.Path(name).stem}-{desc:08x}'
        tex=output/(stem+'.gx');pal=output/(stem+'.tlut');rgba=output/(stem+'.rgba')
        tex.write_bytes(data[image:image+count]);pal.write_bytes(palette)
        subprocess.run([str(exe),str(tex),str(w),str(h),str(fmt),str(pal),str(entries),str(pf),str(rgba)],check=True)
        im=Image.frombytes('RGBA',(w,h),rgba.read_bytes());im.save(output/(stem+'.png'))
        tex.unlink();pal.unlink();rgba.unlink()
        manifest.append(dict(archive=name,descriptor=desc,width=w,height=h,format=fmt,png=stem+'.png'))
(output/'manifest.json').write_text(json.dumps(manifest,indent=2))
if not manifest: raise RuntimeError('No image descriptors found')
print(f'Decoded {len(manifest)} original menu/title textures')
