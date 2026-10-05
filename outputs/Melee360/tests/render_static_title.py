"""CPU preview of the static scene bridge; not a console screenshot."""
import pathlib,struct,sys
import numpy as np
from PIL import Image
raw=pathlib.Path(sys.argv[1]).read_bytes();at=0
def integer():
    global at
    v=struct.unpack_from('<I',raw,at)[0];at+=4;return v
textures=[]
for _ in range(integer()):
    w,h=integer(),integer();p=np.frombuffer(raw,dtype='<u4',count=w*h,offset=at).reshape(h,w);at+=w*h*4
    textures.append(np.stack([(p>>16)&255,(p>>8)&255,p&255,p>>24],axis=-1)/255.)
width,height=640,480
canvas=np.zeros((height,width,4));canvas[:,:,3]=1
depth=np.ones((height,width));drawn=0
for _ in range(integer()):
    texture=integer();mode=integer();wrap_s=integer();wrap_t=integer();n=integer();verts=np.frombuffer(raw,dtype='<f4',count=n*10,offset=at).reshape(n,10);at+=n*40
    for tri in verts.reshape(-1,3,10):
        if np.any(tri[:,3]<=0):continue
        ndc=tri[:,:3]/tri[:,3,None]
        if np.any(ndc[:,2]<0) or np.all(ndc[:,2]>1):continue
        p=np.stack([(ndc[:,0]+1)*width/2,(1-ndc[:,1])*height/2],axis=-1)
        x0=max(0,int(np.floor(p[:,0].min())));x1=min(width,int(np.ceil(p[:,0].max())))
        y0=max(0,int(np.floor(p[:,1].min())));y1=min(height,int(np.ceil(p[:,1].max())))
        if x1<=x0 or y1<=y0:continue
        denom=(p[1,1]-p[2,1])*(p[0,0]-p[2,0])+(p[2,0]-p[1,0])*(p[0,1]-p[2,1])
        if abs(denom)<1e-6:continue
        yy,xx=np.mgrid[y0:y1,x0:x1];xx=xx+.5;yy=yy+.5
        a=((p[1,1]-p[2,1])*(xx-p[2,0])+(p[2,0]-p[1,0])*(yy-p[2,1]))/denom
        b=((p[2,1]-p[0,1])*(xx-p[2,0])+(p[0,0]-p[2,0])*(yy-p[2,1]))/denom
        bary=np.stack([a,b,1-a-b],axis=-1);z=bary@ndc[:,2]
        mask=(bary.min(axis=-1)>=-1e-6)&((z<=depth[y0:y1,x0:x1]) if not mode&(1<<27) else True)
        weights=bary/tri[:,3];weights/=weights.sum(axis=-1,keepdims=True)
        color=weights@tri[:,6:10]
        if texture!=0xffffffff:
            uv=weights@tri[:,4:6];tex=textures[texture];h,w=tex.shape[:2]
            def address(value,wrap,size):
                if wrap==1:value=value%1
                if wrap==2:value=1-np.abs(value%2-1)
                return np.clip(np.floor(value*size).astype(int),0,size-1)
            u=address(uv[:,:,0],wrap_s,w);v=address(uv[:,:,1],wrap_t,h)
            color*=tex[v,u]
        color=np.clip(color,0,1);mask&=color[:,:,3]>.01
        dst=canvas[y0:y1,x0:x1];alpha=color[:,:,3:4]
        blended=color*alpha+dst*(1-alpha)
        dst[mask]=blended[mask]
        if not mode&(1<<29):depth[y0:y1,x0:x1][mask]=z[mask]
        drawn+=int(mask.any())
Image.fromarray((np.clip(canvas[:,:,:3],0,1)*255).astype('uint8')).save(sys.argv[2])
print('CPU preview triangles with visible pixels:',drawn)
