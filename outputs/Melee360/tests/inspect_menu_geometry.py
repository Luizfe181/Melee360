"""Inventory original HSD mesh descriptors without changing game archives."""
import collections,json,pathlib,struct,sys
assets,out=map(pathlib.Path,sys.argv[1:3])
result=[]
for name in ['GmTitle.usd','MnMaAll.usd','NtMemAc.usd']:
    raw=(assets/name).read_bytes();size,ds,nr,np,ne=struct.unpack_from('>5I',raw)
    data=raw[32:32+ds];table=32+ds+nr*4;names=table+(np+ne)*8
    def u(p):
        if p<0 or p+4>ds: raise ValueError(f'{name}: pointer {p:x}')
        return struct.unpack_from('>I',data,p)[0]
    roots={raw[names+s:raw.index(0,names+s)].decode():o for o,s in [struct.unpack_from('>2I',raw,table+i*8) for i in range(np)]}
    start=[]
    for symbol,ptr in roots.items():
        if symbol.endswith('_joint') and 'anim_joint' not in symbol: start.append(ptr)
        elif symbol.endswith('_scene_data'):
            models=u(ptr)
            for i in range(256):
                model=u(models+i*4)
                if not model: break
                start.append(u(model))
    seen=set();pseen=set();meshes=[];joints=[];stack=list(start)
    while stack:
        joint=stack.pop()
        if not joint or joint in seen: continue
        seen.add(joint);flags=u(joint+4)
        joints.append(dict(offset=joint,flags=flags,rotation=struct.unpack_from('>3f',data,joint+20),scale=struct.unpack_from('>3f',data,joint+32),translation=struct.unpack_from('>3f',data,joint+44)))
        stack.extend([u(joint+8),u(joint+12)])
        # Spline and particle joints do not contain DObjs.
        if flags & ((1<<14)|(1<<5)): continue
        dobj=u(joint+16);dseen=set()
        while dobj and dobj not in dseen:
            dseen.add(dobj);pobj=u(dobj+12)
            while pobj and pobj not in pseen:
                pseen.add(pobj);vdesc=u(pobj+8);attrs=[]
                for i in range(32):
                    off=vdesc+i*24;attr=u(off)
                    if attr==255: break
                    attrs.append(dict(attr=attr,type=u(off+4),components=u(off+8),format=u(off+12),fraction=data[off+16],stride=struct.unpack_from('>H',data,off+18)[0],array=u(off+20)))
                pflags,blocks=struct.unpack_from('>2H',data,pobj+12);dl=u(pobj+16)
                if dl+blocks*32>ds: raise ValueError('Display list exceeds archive')
                meshes.append(dict(joint=joint,offset=pobj,flags=pflags,display_offset=dl,display_bytes=blocks*32,attributes=attrs,first_opcode=data[dl] if blocks else None))
                pobj=u(pobj+4)
            dobj=u(dobj+4)
    report=dict(archive=name,roots=roots,joint_count=len(joints),mesh_count=len(meshes),joints=joints,meshes=meshes)
    result.append(report)
    print(name,len(joints),'joints',len(meshes),'meshes',dict(collections.Counter(m['flags']&0x3000 for m in meshes)))
out.write_text(json.dumps(result,indent=2))
