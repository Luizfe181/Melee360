#include "hsd_scene.h"
#include "training_stage.h"
#include "gx_mesh.h"
#include "gx_texture.h"
#include "hsd_animation.h"
#include "../compat/generated/menu_metadata.h"
#include "../compat/generated/animation_metadata.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
namespace {
// Isolated original loop helper; these hooks expose frame state only, not GObj.
typedef float f32;typedef Melee360OriginalLoop AnimLoopSettings;
struct HSD_JObj {float frame;bool requested;};
float mn_8022F298(HSD_JObj* j){return j->frame;}
void HSD_JObjReqAnimAll(HSD_JObj* j,float f){j->frame=f;j->requested=true;}
void HSD_JObjAnimAll(HSD_JObj* j){if(j->requested)j->requested=false;else j->frame+=1;}
#include "../compat/generated/original_loop.inc"
float originalFrame(const Melee360OriginalLoop& input,float elapsed){
    if(!_finite(elapsed)||elapsed<0)return input.start_frame;AnimLoopSettings loop=input;float steps=floorf(elapsed);
    unsigned int initial=(unsigned int)(input.end_frame-input.start_frame+2);
    if(input.loop_frame>=0&&input.end_frame>input.loop_frame&&steps>initial)steps=initial+fmodf(steps-initial,ceilf(input.end_frame-input.loop_frame));
    if(input.loop_frame<0&&steps>initial)steps=(float)initial;unsigned int n=(unsigned int)steps;HSD_JObj j={input.start_frame,false};for(unsigned int i=0;i<n;++i)mn_8022ED6C(&j,&loop);return j.frame;
}
struct Reader {
    const unsigned char* d;unsigned int size;bool ok;
    bool range(unsigned int p,unsigned int n) {if(p>size||n>size-p) {ok=false;return false;}return true;}
    unsigned int u(unsigned int p) {if(!range(p,4)) return 0;return ((unsigned int)d[p]<<24)|((unsigned int)d[p+1]<<16)|(d[p+2]<<8)|d[p+3];}
    unsigned int h(unsigned int p) {return range(p,2)?(d[p]<<8)|d[p+1]:0;}
    float f(unsigned int p) {unsigned int bits=u(p);float v;memcpy(&v,&bits,4);if(!_finite(v)) ok=false;return v;}
};
struct Matrix {float m[4][4];};
Matrix identity() {Matrix m;memset(&m,0,sizeof(m));for(int i=0;i<4;++i)m.m[i][i]=1;return m;}
Matrix mul(const Matrix& a,const Matrix& b) {Matrix o;memset(&o,0,sizeof(o));for(int i=0;i<4;++i)for(int j=0;j<4;++j)for(int k=0;k<4;++k)o.m[i][j]+=a.m[i][k]*b.m[k][j];return o;}
float dot(const float* a,const float* b) {return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];}
bool normalize(float* v) {float len=sqrtf(dot(v,v));if(len<1e-8f)return false;for(int i=0;i<3;++i)v[i]/=len;return true;}
void cross(const float* a,const float* b,float* o) {o[0]=a[1]*b[2]-a[2]*b[1];o[1]=a[2]*b[0]-a[0]*b[2];o[2]=a[0]*b[1]-a[1]*b[0];}
struct MeshCache {unsigned int pobj;std::vector<Melee360MeshVertex> vertices;};
struct TextureCache {std::vector<unsigned char> key;Melee360SceneTexture texture;bool supported;};
struct ArchiveCache {const void* source;std::vector<MeshCache> meshes;std::vector<TextureCache> textures;unsigned int pixels,stamp;ArchiveCache():source(0),pixels(0),stamp(0){}};
ArchiveCache archiveCaches[3];unsigned int cacheStamp;
ArchiveCache& cacheFor(const void* source){
    if(!source)return archiveCaches[2];
    for(int i=0;i<2;++i)if(archiveCaches[i].source==source){archiveCaches[i].stamp=++cacheStamp;return archiveCaches[i];}
    int i=archiveCaches[0].stamp<=archiveCaches[1].stamp?0:1;ArchiveCache& c=archiveCaches[i];c.meshes.clear();c.textures.clear();c.pixels=0;c.source=source;c.stamp=++cacheStamp;return c;
}
struct Loader {
    Reader r;Melee360Scene& scene;Matrix camera;const void* source;std::vector<unsigned int> seen,textureOffsets;
    std::vector<std::vector<unsigned char> > textureKeys;
    struct Pose {unsigned int joint;Matrix world;float scale[3];};std::vector<Pose> poses;bool collect;
    ArchiveCache& cache;std::vector<MeshCache>& meshCache;std::vector<TextureCache>& textureCache;unsigned int& cachedPixelBytes;
    struct Light {float position[3],color[3],k[3];};std::vector<Light> lights;
    void setupMenuLights(unsigned int table,int colorIndex){
        static const unsigned char colors[5][3]={{90,115,255},{255,90,65},{14,210,65},{240,200,90},{155,65,255}};
        for(unsigned int i=0;i<16&&r.ok;++i){unsigned int pair=r.u(table+i*4);if(!pair)break;unsigned int desc=r.u(pair),flags=r.h(desc+8);
            if((flags&3)!=2||(flags&32)||!(flags&4))continue;unsigned int pos=r.u(desc+16),atten=r.u(desc+24);Light l;
            for(int c=0;c<3;++c){l.position[c]=r.f(pos+4+c*4);l.color[c]=(lights.empty()?colors[colorIndex][c]:r.d[desc+12+c])/255.f;}
            l.k[0]=1;l.k[1]=l.k[2]=0;
            if(r.h(desc+10)&1){for(int c=0;c<3;++c)l.k[c]=r.f(atten+12+c*4);}
            else{float bright=r.f(atten),distance=r.f(atten+4);unsigned int mode=r.u(atten+8);
                if(distance>0&&bright>0&&bright<1){float a=(1-bright)/bright;if(mode==1)l.k[1]=a/distance;else if(mode==2){l.k[1]=a/(2*distance);l.k[2]=a/(2*distance*distance);}else if(mode==3)l.k[2]=a/(distance*distance);}}
            lights.push_back(l);
        }
    }
    void lighting(const Matrix& world,const Melee360MeshVertex& v,float* color){
        float pos[3],n[3];for(int row=0;row<3;++row){pos[row]=world.m[row][3];n[row]=0;for(int col=0;col<3;++col){pos[row]+=world.m[row][col]*v.position[col];n[row]+=world.m[row][col]*v.normal[col];}}
        // Inverse transpose, including nonuniform animated joint scaling.
        float a[3]={world.m[0][0],world.m[1][0],world.m[2][0]},b[3]={world.m[0][1],world.m[1][1],world.m[2][1]},c[3]={world.m[0][2],world.m[1][2],world.m[2][2]},x[3],y[3],z[3];cross(b,c,x);cross(c,a,y);cross(a,b,z);float determinant=dot(a,x);
        if(fabsf(determinant)>1e-10f)for(int row=0;row<3;++row)n[row]=(x[row]*v.normal[0]+y[row]*v.normal[1]+z[row]*v.normal[2])/determinant;
        if(!normalize(n))return;float illumination[3]={0,0,0};
        for(unsigned int i=0;i<lights.size();++i){Light& l=lights[i];float delta[3];for(int c=0;c<3;++c)delta[c]=l.position[c]-pos[c];float distance=sqrtf(dot(delta,delta));if(!normalize(delta))continue;
            float facing=dot(delta,n);if(facing<0)facing=0;float denominator=l.k[0]+l.k[1]*distance+l.k[2]*distance*distance;if(denominator<=0)continue;
            for(int c=0;c<3;++c)illumination[c]+=l.color[c]*facing/denominator;}
        for(int c=0;c<3;++c)color[c]*=illumination[c]>1?1:illumination[c];
    }
    Loader(const unsigned char* d,unsigned int size,Melee360Scene& s,const void* archive=0):scene(s),source(archive),collect(false),cache(cacheFor(archive)),meshCache(cache.meshes),textureCache(cache.textures),cachedPixelBytes(cache.pixels) {r.d=d;r.size=size;r.ok=true;camera=identity();}
    bool world(unsigned int offset,Matrix& out){for(unsigned int i=0;i<poses.size();++i)if(poses[i].joint==offset){out=poses[i].world;return true;}return false;}
    bool envelope(unsigned int pobj,unsigned int index,unsigned int owner,Matrix& out){
        if(!(r.u(owner+4)&4))return false;unsigned int table=r.u(pobj+20);if(index>=256||!r.range(table,(index+1)*4))return false;
        unsigned int list=r.u(table+index*4);if(!list||!r.range(list,8))return false;float total=0;out=identity();for(int row=0;row<3;++row)for(int col=0;col<4;++col)out.m[row][col]=0;
        for(unsigned int i=0;i<64;++i){if(!r.range(list+i*8,8))return false;unsigned int target=r.u(list+i*8);if(!target)return total>.99f&&total<1.01f;
            float weight=r.f(list+i*8+4);if(weight<0||weight>1)return false;Matrix transform;if(!world(target,transform))return false;
            if(weight<.999999f){unsigned int bind=r.u(target+56);if(!bind||!r.range(bind,48))return false;Matrix inv=identity();for(int row=0;row<3;++row)for(int col=0;col<4;++col)inv.m[row][col]=r.f(bind+row*16+col*4);transform=mul(transform,inv);}
            for(int row=0;row<3;++row)for(int col=0;col<4;++col)out.m[row][col]+=transform.m[row][col]*weight;total+=weight;
        }return false;
    }
    void draw(unsigned int root){float one[3]={1,1,1};draw(root,identity(),one);}
    void draw(unsigned int root,const Matrix& parent,const float* scale){poses.clear();seen.clear();collect=true;joint(root,parent,scale,0,false);seen.clear();collect=false;joint(root,parent,scale,0,false);}
    bool setupCamera(unsigned int desc) {
        if(!r.range(desc,56))return false;
        float eye[3],interest[3],up[3]={0,1,0},back[3],right[3];unsigned int ep=r.u(desc+24),ip=r.u(desc+28);
        for(int i=0;i<3;++i){eye[i]=r.f(ep+4+i*4);interest[i]=r.f(ip+4+i*4);back[i]=eye[i]-interest[i];}
        if(!normalize(back))return false;
        unsigned int upp=r.u(desc+36);if(upp)for(int i=0;i<3;++i)up[i]=r.f(upp+i*4);
        cross(up,back,right);if(!normalize(right))return false;cross(back,right,up);
        float roll=r.f(desc+32),c=cosf(roll),s=sinf(roll),oldRight[3];memcpy(oldRight,right,sizeof(right));
        for(int i=0;i<3;++i){right[i]=oldRight[i]*c+up[i]*s;up[i]=up[i]*c-oldRight[i]*s;}
        Matrix view=identity();for(int i=0;i<3;++i){view.m[0][i]=right[i];view.m[1][i]=up[i];view.m[2][i]=back[i];}
        view.m[0][3]=-dot(right,eye);view.m[1][3]=-dot(up,eye);view.m[2][3]=-dot(back,eye);
        float nearPlane=r.f(desc+40),farPlane=r.f(desc+44);if(nearPlane<=0||farPlane<=nearPlane)return false;
        Matrix projection;memset(&projection,0,sizeof(projection));unsigned int type=r.h(desc+6);
        if(type==1) {
            float fov=r.f(desc+48),aspect=r.f(desc+52);if(fov<=0||fov>=179||aspect<=0)return false;
            float scale=1/tanf(fov*0.00872664626f);projection.m[0][0]=scale/aspect;projection.m[1][1]=scale;
            projection.m[2][2]=farPlane/(nearPlane-farPlane);projection.m[2][3]=nearPlane*farPlane/(nearPlane-farPlane);projection.m[3][2]=-1;
        } else if(type==3) {
            float t=r.f(desc+48),b=r.f(desc+52),l=r.f(desc+56),rr=r.f(desc+60);if(t==b||rr==l)return false;
            projection=identity();projection.m[0][0]=2/(rr-l);projection.m[0][3]=-(rr+l)/(rr-l);
            projection.m[1][1]=2/(t-b);projection.m[1][3]=-(t+b)/(t-b);projection.m[2][2]=1/(nearPlane-farPlane);projection.m[2][3]=nearPlane/(nearPlane-farPlane);
        } else return false;
        camera=mul(projection,view);return r.ok;
    }
    float tevInput(unsigned int code,int channel,const float* tex,unsigned int tev,bool alpha,bool& ok) {
        if(alpha){if(code==4)return tex[3];if(code==7)return 0;if(code>=64&&code<=67)return r.d[tev+16+code-64]/255.f;
            if(code==68||code==69)return r.d[tev+(code==68?23:27)]/255.f;}
        else {if(code==8)return tex[channel];if(code==9)return tex[3];if(code==12)return 1;if(code==13)return .5f;if(code==15)return 0;
            if(code==128)return r.d[tev+16+channel]/255.f;if(code>=129&&code<=132)return r.d[tev+16+code-129]/255.f;
            if(code==133)return r.d[tev+20+channel]/255.f;if(code==134)return r.d[tev+23]/255.f;
            if(code==135)return r.d[tev+24+channel]/255.f;if(code==136)return r.d[tev+27]/255.f;}
        ok=false;return 0;
    }
    float tevChannel(unsigned int tev,int channel,const float* tex,bool& ok) {
        bool alpha=channel==3;unsigned int input=tev+(alpha?12:8);
        float a=tevInput(r.d[input],channel,tex,tev,alpha,ok),b=tevInput(r.d[input+1],channel,tex,tev,alpha,ok),c=tevInput(r.d[input+2],channel,tex,tev,alpha,ok),d=tevInput(r.d[input+3],channel,tex,tev,alpha,ok);
        unsigned int op=r.d[tev+(alpha?1:0)],bias=r.d[tev+(alpha?3:2)],scale=r.d[tev+(alpha?5:4)];
        if(op>1||bias>2||scale>3){ok=false;return tex[channel];}float v=d+(op==1?-1.f:1.f)*((1-c)*a+c*b);v+=(bias==1?.5f:bias==2?-.5f:0);v*=scale==1?2.f:scale==2?4.f:scale==3?.5f:1.f;
        return v<0?0:v>1?1:v;
    }
    int texture(unsigned int tobj,unsigned int material) {
        if(!tobj)return -1;unsigned int image=r.u(tobj+76);
        unsigned int tev=r.u(tobj+88),tlut=r.u(tobj+80);std::vector<unsigned char> key;
        if(!r.range(tobj,92)||!r.range(image,24)||(material&&!r.range(material,20))||(tev&&!r.range(tev,32)))return -2;
        key.insert(key.end(),r.d+image,r.d+image+24);key.insert(key.end(),r.d+tobj+64,r.d+tobj+72);
        if(tlut){if(!r.range(tlut,14))return -2;key.insert(key.end(),r.d+tlut,r.d+tlut+14);}
        if(material)key.insert(key.end(),r.d+material,r.d+material+20);if(tev)key.insert(key.end(),r.d+tev,r.d+tev+32);
        for(unsigned int i=0;i<textureKeys.size();++i)if(textureKeys[i]==key)return (int)i;
        if(source)for(unsigned int i=0;i<textureCache.size();++i)if(textureCache[i].key==key){textureOffsets.push_back(image);textureKeys.push_back(key);scene.textures.push_back(textureCache[i].texture);if(!textureCache[i].supported)++scene.skipped;return (int)scene.textures.size()-1;}
        unsigned int ptr=r.u(image),w=r.h(image+4),h=r.h(image+6),fmt=r.u(image+8),bytes=Melee360GxTextureBytes(w,h,fmt);
        if(!bytes||!r.range(ptr,bytes))return -2;
        unsigned int entries=0,pf=0,palptr=0;
        if(fmt==8||fmt==9||fmt==10){unsigned int tlut=r.u(tobj+80);palptr=r.u(tlut);pf=r.u(tlut+4);entries=r.h(tlut+12);if(!r.range(palptr,entries*2))return -2;}
        Melee360SceneTexture t;t.width=w;t.height=h;t.pixels.resize(w*h);
        if(!Melee360DecodeGxTexture(r.d+ptr,bytes,w,h,fmt,entries?r.d+palptr:0,entries,pf,&t.pixels[0],w*h))return -2;
        float mat[4]={1,1,1,1};if(material){for(int c=0;c<3;++c)mat[c]=r.d[material+4+c]/255.f;mat[3]=r.f(material+12);}
        unsigned int flags=r.u(tobj+64),colormap=(flags>>16)&15,alphamap=(flags>>20)&15,active=tev?r.u(tev+28):0;
        float blend=r.f(tobj+68);bool supported=true;
        for(unsigned int p=0;p<t.pixels.size();++p){unsigned int packed=t.pixels[p];float tex[4],src[4];for(int c=0;c<4;++c)src[c]=tex[c]=((packed>>(c==0?16:c==1?8:c==2?0:24))&255)/255.f;
            for(int c=0;c<4;++c)if(active&(c==3?0x80000000u:0x40000000u))src[c]=tevChannel(tev,c,tex,supported);
            unsigned int out=0;for(int c=0;c<4;++c){unsigned int mode=c==3?alphamap:colormap;float v=mat[c];
                if(c<3){if(mode==1)v=mat[c]*(1-src[3])+src[c]*src[3];else if(mode==2)v=mat[c]*(1-src[c])+src[c]*src[c];else if(mode==3)v=mat[c]*(1-blend)+src[c]*blend;
                    else if(mode==4)v=mat[c]*src[c];else if(mode==5)v=src[c];else if(mode==7)v=mat[c]+src[c];else if(mode==8)v=mat[c]-src[c];}
                else {if(mode==1)v=mat[c]*(1-src[c])+src[c]*src[c];else if(mode==2)v=mat[c]*(1-blend)+src[c]*blend;else if(mode==3)v=mat[c]*src[c];else if(mode==4)v=src[c];else if(mode==6)v=mat[c]+src[c];else if(mode==7)v=mat[c]-src[c];}
                v=v<0?0:v>1?1:v;out|=(unsigned int)(v*255+.5f)<<(c==0?16:c==1?8:c==2?0:24);}t.pixels[p]=out;}
        t.contentHash=2166136261u;for(unsigned int p=0;p<t.pixels.size();++p){t.contentHash^=t.pixels[p];t.contentHash*=16777619u;}
        if(source){unsigned int bytes=(unsigned int)t.pixels.size()*4;if(cachedPixelBytes+bytes>16*1024*1024||textureCache.size()>=256){textureCache.clear();cachedPixelBytes=0;}if(bytes<=16*1024*1024){TextureCache cached;cached.key=key;cached.texture=t;cached.supported=supported;textureCache.push_back(cached);cachedPixelBytes+=bytes;}}
        if(!supported)++scene.skipped;textureOffsets.push_back(image);textureKeys.push_back(key);scene.textures.push_back(t);return (int)scene.textures.size()-1;
    }
    void joint(unsigned int at,const Matrix& parent,const float* parentScale,unsigned int depth,bool parentHidden) {
        if(!at||!r.ok)return;if(depth>128||seen.size()>4096){r.ok=false;return;}
        for(unsigned int i=0;i<seen.size();++i)if(seen[i]==at){r.ok=false;return;}seen.push_back(at);
        if(!r.range(at,64))return;unsigned int flags=r.u(at+4);
        float rot[3],scale[3],translate[3],accScale[3];for(int i=0;i<3;++i){rot[i]=r.f(at+20+i*4);scale[i]=r.f(at+32+i*4);translate[i]=r.f(at+44+i*4);accScale[i]=parentScale[i]*((flags&8)?1:scale[i]);}
        float sx=sinf(rot[0]),cx=cosf(rot[0]),sy=sinf(rot[1]),cy=cosf(rot[1]),sz=sinf(rot[2]),cz=cosf(rot[2]);
        Matrix local=identity();
        local.m[0][0]=cz*cy;local.m[0][1]=cz*sx*sy-cx*sz;local.m[0][2]=cz*cx*sy+sx*sz;
        local.m[1][0]=sz*cy;local.m[1][1]=sz*sx*sy+cx*cz;local.m[1][2]=sz*cx*sy-sx*cz;
        local.m[2][0]=-sy;local.m[2][1]=cy*sx;local.m[2][2]=cy*cx;
        for(int row=0;row<3;++row){local.m[row][3]=translate[row];for(int col=0;col<3;++col){if(fabsf(parentScale[row])<1e-8f){r.ok=false;return;}local.m[row][col]*=scale[col]*parentScale[col]/parentScale[row];}}
        Matrix world=mul(parent,local),clip=mul(camera,world);
        if(collect){Pose pose;pose.joint=at;pose.world=world;memcpy(pose.scale,accScale,sizeof(accScale));poses.push_back(pose);joint(r.u(at+8),world,accScale,depth+1,false);joint(r.u(at+12),parent,parentScale,depth,false);return;}
        bool hidden=parentHidden||(flags&16)!=0;
        if(flags&0x20000){++scene.skipped;hidden=true;} // quaternion pose not handled yet
        unsigned int dobj=r.u(at+16);
        if(!hidden&&!(flags&((1<<5)|(1<<14))))for(unsigned int d=0;dobj&&r.ok;++d){
            if(d>4096||!r.range(dobj,16)){r.ok=false;return;}
            unsigned int mobj=r.u(dobj+8),pobj=r.u(dobj+12),mat=mobj?r.u(mobj+12):0,tobj=mobj?r.u(mobj+8):0;
            float diffuse[4]={1,1,1,1};if(mat&&r.range(mat,20)){for(int i=0;i<3;++i)diffuse[i]=r.d[mat+4+i]/255.f;diffuse[3]=r.f(mat+12);}
            int tex=texture(tobj,mat);if(tex>=0)for(int c=0;c<4;++c)diffuse[c]=1;
            for(unsigned int p=0;pobj&&r.ok;++p){
                if(p>4096||!r.range(pobj,24)){r.ok=false;return;}
                unsigned int kind=r.h(pobj+12)&0x3000;if(kind==0x1000||kind==0x3000){++scene.skipped;pobj=r.u(pobj+4);continue;}
                Melee360MeshVertex* vertices=0;unsigned int count=0,unsupported=0;
                int result=0;bool owned=true;
                if(source)for(unsigned int ci=0;ci<meshCache.size();++ci)if(meshCache[ci].pobj==pobj){vertices=&meshCache[ci].vertices[0];count=(unsigned int)meshCache[ci].vertices.size();result=1;owned=false;break;}
                if(owned){result=Melee360DecodeGxMesh(r.d,r.size,pobj,&vertices,&count,&unsupported);if(result==1&&source){MeshCache c;c.pobj=pobj;c.vertices.assign(vertices,vertices+count);meshCache.push_back(c);free(vertices);vertices=&meshCache.back().vertices[0];owned=false;}}
                if(result!=1||tex==-2){
#ifndef _XBOX
                    printf("HSD skipped pobj=%u decode=%d texture=%d attrs=%u\n",pobj,result,tex,unsupported);
#endif
                    ++scene.skipped;if(owned)free(vertices);pobj=r.u(pobj+4);continue;}
                Melee360SceneBatch batch;batch.texture=tex;batch.joint=at;batch.mode=mobj?r.u(mobj+4):0;batch.wrapS=tobj?r.u(tobj+52):0;batch.wrapT=tobj?r.u(tobj+56):0;batch.vertices.resize(count);
                Matrix envelopes[10];bool valid[10]={false};unsigned int envelopeIds[10]={0};bool meshOk=true;
                for(unsigned int v=0;v<count;++v){Melee360SceneVertex& o=batch.vertices[v];
                    Matrix vertexClip=clip;
                    if(kind==0x2000){unsigned int slot=vertices[v].matrix/3;if(!valid[slot]||envelopeIds[slot]!=vertices[v].envelope){envelopeIds[slot]=vertices[v].envelope;meshOk=envelope(pobj,vertices[v].envelope,at,envelopes[slot]);if(!meshOk)break;valid[slot]=true;}vertexClip=mul(camera,envelopes[slot]);}
                    else if(r.u(pobj+20)){Matrix target;if(!this->world(r.u(pobj+20),target)){meshOk=false;break;}vertexClip=mul(camera,target);}
                    for(int row=0;row<4;++row){o.clip[row]=vertexClip.m[row][3];for(int col=0;col<3;++col)o.clip[row]+=vertexClip.m[row][col]*vertices[v].position[col];}
                    for(int i=0;i<4;++i)o.color[i]=diffuse[i]*((vertices[v].color>>(i==0?16:i==1?8:i==2?0:24))&255)/255.f;
                    if(!lights.empty()&&(flags&0x80)&&(batch.mode&4))lighting(world,vertices[v],o.color);
                    o.uv[0]=vertices[v].uv[0];o.uv[1]=vertices[v].uv[1];
                    if(tobj){float u=o.uv[0]-r.f(tobj+40),vv=o.uv[1]-r.f(tobj+44),rot=r.f(tobj+24),cs=cosf(rot),sn=sinf(rot),su=r.f(tobj+28),sv=r.f(tobj+32);
                        o.uv[0]=fabsf(su)<1e-8f?0:(u*cs+vv*sn)*r.d[tobj+60]/su;o.uv[1]=fabsf(sv)<1e-8f?0:(vv*cs-u*sn)*r.d[tobj+61]/sv;}
                }
                if(owned)free(vertices);if(meshOk)scene.batches.push_back(batch);else ++scene.skipped;pobj=r.u(pobj+4);
            }
            dobj=r.u(dobj+4);
        }
        // HSD_JObjDispAll does not inherit JOBJ_HIDDEN: BRANCH animation
        // explicitly sets the flag on descendants, NODE only affects itself.
        joint(r.u(at+8),world,accScale,depth+1,parentHidden||(flags&0x20000)!=0);joint(r.u(at+12),parent,parentScale,depth,parentHidden);
    }
};
}

namespace {
struct MenuPose {
    std::vector<unsigned char> data;Reader r;std::vector<unsigned int> joints,anims,mats;unsigned int tracks,unsupportedEvents;bool ok,descriptorLoops,stageForcedLoop;
    MenuPose(const unsigned char* d,unsigned int bytes):data(d,d+bytes),tracks(0),unsupportedEvents(0),ok(true),descriptorLoops(false),stageForcedLoop(false){r.d=&data[0];r.size=bytes;r.ok=true;}
    void put(unsigned int at,unsigned int v){if(!r.range(at,4)){ok=false;return;}data[at]=(unsigned char)(v>>24);data[at+1]=(unsigned char)(v>>16);data[at+2]=(unsigned char)(v>>8);data[at+3]=(unsigned char)v;}
    void number(unsigned int at,float v){unsigned int bits;memcpy(&bits,&v,4);put(at,bits);}
    void gather(unsigned int j,unsigned int a,unsigned int m,unsigned int depth=0){
        if(!j||!ok)return;if(depth>128||joints.size()>4096||!r.range(j,64)||(a&&!r.range(a,20))||(m&&!r.range(m,12))){ok=false;return;}
        for(unsigned int i=0;i<joints.size();++i)if(joints[i]==j){ok=false;return;}
        joints.push_back(j);anims.push_back(a?r.u(a+8):0);mats.push_back(m?r.u(m+8):0);
        gather(r.u(j+8),a?r.u(a):0,m?r.u(m):0,depth+1);
        gather(r.u(j+12),a?r.u(a+4):0,m?r.u(m+4):0,depth);
    }
    void hide(unsigned int j,bool hidden,bool recursive){
        if(!j||!r.range(j,64)){ok=false;return;}put(j+4,hidden?r.u(j+4)|16:r.u(j+4)&~16u);
        if(recursive){unsigned int child=r.u(j+8);for(unsigned int guard=0;child&&guard<4096;++guard){hide(child,hidden,true);child=r.u(child+12);}}
    }
    struct Target {MenuPose* pose;unsigned int offset,kind,texanim;bool preserveColor;};
    static void update(void* object,unsigned int type,float value){
        Target* t=(Target*)object;MenuPose& p=*t->pose;unsigned int at=t->offset;
        if(t->kind==0){
            if(type>=1&&type<=3)p.number(at+20+(type-1)*4,value);
            else if(type>=5&&type<=7)p.number(at+44+(type-5)*4,value);
            else if(type>=8&&type<=10)p.number(at+32+(type-8)*4,fabsf(value)<.001f?.001f:value);
            else if(type==11||type==12)p.hide(at,value<=.5f,type==12);
            else if(p.descriptorLoops&&type>=40&&type<=42){++p.unsupportedEvents;}
            else p.ok=false;
        }else if(t->kind==1){
            if(type>=1&&type<=9){unsigned int base=type<=3?0:type<=6?4:8,component=(type-1)%3;if(!p.r.range(at+base+component,1)){p.ok=false;return;}p.data[at+base+component]=(unsigned char)((value<0?0:value>1?1:value)*255);}
            else if(type==10)p.number(at+12,1.f-value);
            // Pixel-engine references are not yet applied by this renderer.
        }else{
            unsigned int ta=t->texanim;
            if(type==1||type==10){unsigned int count=p.r.h(ta+(type==1?20:22)),index=value>=0?(unsigned int)value:count;
                unsigned int table=p.r.u(ta+(type==1?12:16));if(index>=count||!table){p.ok=false;return;}unsigned int desc=p.r.u(table+index*4);if(desc)p.put(at+(type==1?76:80),desc);
            }else if(type==2||type==3)p.number(at+40+(type-2)*4,value);
            else if(type==4||type==5)p.number(at+28+(type-4)*4,value);
            else if(type>=6&&type<=8)p.number(at+16+(type-6)*4,value);
            else if(type==9)p.number(at+68,value);
            else if(type>=12&&type<=23&&!t->preserveColor){unsigned int tev=p.r.u(at+88);if(tev&&p.r.range(tev,32))p.data[tev+16+type-12]=(unsigned char)((value<0?0:value>1?1:value)*255);}
        }
    }
    void sample(unsigned int a,Target& target,float frame){
        if(descriptorLoops&&a){float end=r.f(a+4);if(end<0){ok=false;return;}
            if(end>0&&frame>end)frame=(stageForcedLoop||(r.u(a)&(1u<<29)))?fmodf(frame,end):end;}
        if(ok&&!Melee360SampleAObj(r.d,r.size,a,frame,update,&target,&tracks))ok=false;
    }
    void one(unsigned int index,float frame,bool joint=true,bool material=true,bool preserveColor=false,unsigned int channels=3){
        if(index>=joints.size()){ok=false;return;}Target t={this,joints[index],0,0,preserveColor};if(joint)sample(anims[index],t,frame);
        if(!material)return;unsigned int d=r.u(joints[index]+16),m=mats[index];
        for(unsigned int guard=0;d&&m&&ok;++guard){if(guard>4096||!r.range(d,16)||!r.range(m,16)){ok=false;break;}
            unsigned int mo=r.u(d+8),mat=mo?r.u(mo+12):0;if(mat&&(channels&1)){t.offset=mat;t.kind=1;sample(r.u(m+4),t,frame);}
            unsigned int tobj=mo&&(channels&2)?r.u(mo+8):0;
            for(unsigned int ti=0;tobj&&ok;++ti){if(ti>32||!r.range(tobj,84)){ok=false;break;}unsigned int ta=r.u(m+8);
                for(unsigned int ai=0;ta&&ok;++ai){if(ai>32||!r.range(ta,24)){ok=false;break;}
                    if(r.u(ta+4)==r.u(tobj+8)){t.offset=tobj;t.kind=2;t.texanim=ta;sample(r.u(ta+8),t,frame);break;}ta=r.u(ta);}
                tobj=r.u(tobj+4);}
            d=r.u(d+4);m=r.u(m);
        }
    }
    void branch(unsigned int index,float frame,bool joint=true,bool material=true){
        if(index>=joints.size()){ok=false;return;}unsigned int root=joints[index];std::vector<unsigned int> pending;pending.push_back(root);
        for(unsigned int at=0;at<pending.size()&&ok;++at){unsigned int j=pending[at];for(unsigned int i=0;i<joints.size();++i)if(joints[i]==j){one(i,frame,joint,material);break;}
            unsigned int c=r.u(j+8);for(unsigned int n=0;c&&n<4096;++n){pending.push_back(c);c=r.u(c+12);}if(pending.size()>4096)ok=false;}
    }
};
unsigned int rootOffset(const unsigned char* archive,unsigned int bytes,const char* name,bool* found=0){if(found)*found=false;
    Reader h={archive,bytes,true};unsigned int ds=h.u(4),nr=h.u(8),np=h.u(12),ne=h.u(16);unsigned __int64 table=32ULL+ds+4ULL*nr,names=table+8ULL*(np+ne);
    if(bytes<32||h.u(0)!=bytes||names>bytes)return 0;
    for(unsigned int i=0;i<np;++i){unsigned int s=h.u((unsigned int)table+i*8+4);unsigned __int64 at=names+s;if(at>=bytes||!memchr(archive+(unsigned int)at,0,bytes-(unsigned int)at))return 0;
        if(!strcmp((const char*)archive+(unsigned int)at,name)){if(found)*found=true;return h.u((unsigned int)table+i*8);}}
    return 0;
}
bool gatherMenu(MenuPose& p,const unsigned char* archive,unsigned int bytes,const char* base){
    char name[96];sprintf_s(name,sizeof(name),"%s_joint",base);unsigned int j=rootOffset(archive,bytes,name);sprintf_s(name,sizeof(name),"%s_animjoint",base);unsigned int a=rootOffset(archive,bytes,name);
    sprintf_s(name,sizeof(name),"%s_matanim_joint",base);unsigned int m=rootOffset(archive,bytes,name);if(!j)return false;p.gather(j,a,m);return p.ok&&p.r.ok;
}
}
bool Melee360OriginalMenuSupported(int menu){return menu>=0&&menu<34&&(menu<=6||menu==9||menu==12||menu==28);}
static unsigned int captionMetric(unsigned int glyph,unsigned int side,const unsigned char* font,Reader& sis){
    if(glyph<287)return font[glyph*2+side];unsigned int at=sis.u(4)+(glyph-287)*2+side;if(!sis.range(at,1))return 32;return sis.d[at];
}
bool Melee360AppendOriginalMenuCaption(const unsigned char* menuArchive,unsigned int menuBytes,
    const unsigned char* sisArchive,unsigned int sisBytes,const unsigned char* font,unsigned int fontBytes,int menu,int selection,Melee360Scene& scene){
    if(!menuArchive||!sisArchive||sisBytes<32||!font||fontBytes!=288*2+287*512||!Melee360OriginalMenuSupported(menu)||selection<0||selection>=10)return false;
    int originalSelection=selection+((menu==1||menu==3)&&selection>=2?1:menu==4&&selection>=3?1:0);
    if(originalSelection>=10)return false;unsigned int id=Melee360OriginalMenuKinds[menu].descriptions[originalSelection];if(!id)return false;
    Reader header={sisArchive,sisBytes,true};unsigned int size=header.u(4);if(size>sisBytes-32||header.u(0)!=sisBytes)return false;
    Reader sis={sisArchive+32,size,true};unsigned int at=sis.u(id*4);if(!at)return false;
    struct Line {std::vector<unsigned int> glyphs;float scaleX,scaleY,x,y,color[4];};
    std::vector<Line> lines;float scaleX=1,scaleY=1,color[4]={1,1,1,1},offsetX=0,offsetY=0,savedX=0,savedY=0,flowY=0;bool terminated=false;
    for(unsigned int guard=0;guard<2048&&sis.ok;++guard){if(!sis.range(at,1))return false;unsigned int op=sis.d[at++];if(!op){terminated=true;break;}
        if(op==0x20||op==0x21){if(lines.empty()||!sis.range(at,1))return false;unsigned int glyph=sis.d[at++];if(op==0x21)glyph+=287;lines.back().glyphs.push_back(glyph);}
        else if(op==0x1a){if(lines.empty())return false;lines.back().glyphs.push_back(0xFFFFFFFF);}
        else if(op==0x0c){if(!sis.range(at,3))return false;for(int c=0;c<3;++c)color[c]=sis.d[at++]/255.f;}
        else if(op==0x0e){scaleX=sis.h(at)/256.f;scaleY=sis.h(at+2)/256.f;at+=4;}
        else if(op==6||op==7){float x=(short)sis.h(at),y=(short)sis.h(at+2);at+=4;if(op==6){offsetX=x;offsetY=y;}else{offsetX+=x;flowY+=y;}}
        else if(op==0x18){Line line;line.scaleX=scaleX;line.scaleY=scaleY;line.x=offsetX;line.y=offsetY+flowY;memcpy(line.color,color,sizeof(color));lines.push_back(line);}
        else if(op==0x16){savedX=offsetX;savedY=offsetY;}
        else if(op==0x19){offsetX=savedX;offsetY=savedY;}
        else if(op==3){flowY+=32*scaleY;}
        else if(op!=0x10&&op!=0x12&&op!=0x0f&&op!=0x0d)return false;
    }
    if(!terminated||lines.empty()||!sis.ok)return false;
    unsigned int camera=rootOffset(menuArchive,menuBytes,"ScMenMain_cam_int1_camera");Reader mh={menuArchive,menuBytes,true};unsigned int menuData=mh.u(4);if(menuData>menuBytes-32)return false;
    Loader loader(menuArchive+32,menuData,scene);if(!loader.setupCamera(camera))return false;
    std::vector<unsigned int> cachedGlyphs;std::vector<int> cachedTextures;
    for(unsigned int lineIndex=0;lineIndex<lines.size();++lineIndex){Line& line=lines[lineIndex];std::vector<unsigned int>& glyphs=line.glyphs;
    float width=0;for(unsigned int i=0;i<glyphs.size();++i){unsigned int g=glyphs[i];if(g!=0xFFFFFFFF&&captionMetric(g,0,font,sis)+captionMetric(g,1,font,sis)>32)return false;width+=g==0xFFFFFFFF?16:32-captionMetric(g,0,font,sis)-captionMetric(g,1,font,sis);}
    // Original mn_80229A7C world position/font scale; SIS centers each run.
    float advance=-width*.5f,unitX=.0521f*line.scaleX,unitY=.0521f*line.scaleY;
    if(width*line.scaleX>364.68332f)unitX=.0521f*364.68332f/width;
    for(unsigned int i=0;i<glyphs.size();++i){unsigned int g=glyphs[i];if(g==0xFFFFFFFF){advance+=16;continue;}int texture=-1;
        for(unsigned int c=0;c<cachedGlyphs.size();++c)if(cachedGlyphs[c]==g)texture=cachedTextures[c];
        if(texture<0){unsigned int custom=g>=287?sis.u(0)+(g-287)*512:0;if(g>=287&&!sis.range(custom,512))return false;const unsigned char* pixels=g<287?font+576+g*512:sis.d+custom;
            Melee360SceneTexture t;t.width=t.height=32;t.pixels.resize(1024);if(!Melee360DecodeGxTexture(pixels,512,32,32,0,0,0,0,&t.pixels[0],1024))return false;
            for(unsigned int p=0;p<1024;++p)t.pixels[p]=(t.pixels[p]&0xFF000000)|0xFFFFFF;texture=(int)scene.textures.size();scene.textures.push_back(t);cachedGlyphs.push_back(g);cachedTextures.push_back(texture);}
        float left=(advance-captionMetric(g,0,font,sis)+line.x)*unitX,right=left+32*unitX,top=-9.1f-line.y*.0521f,bottom=top-32*unitY;
        float coordinates[6][4]={{left,top,0,0},{right,top,1,0},{left,bottom,0,1},{left,bottom,0,1},{right,top,1,0},{right,bottom,1,1}};
        Melee360SceneBatch batch;batch.texture=texture;batch.joint=0;batch.mode=(1u<<27)|(1u<<29)|(1u<<30);batch.wrapS=batch.wrapT=0;
        for(int v=0;v<6;++v){Melee360SceneVertex vert;float pos[3]={coordinates[v][0],coordinates[v][1],17};for(int row=0;row<4;++row){vert.clip[row]=loader.camera.m[row][3];for(int col=0;col<3;++col)vert.clip[row]+=loader.camera.m[row][col]*pos[col];}
            vert.uv[0]=coordinates[v][2];vert.uv[1]=coordinates[v][3];memcpy(vert.color,line.color,sizeof(color));batch.vertices.push_back(vert);}
        scene.batches.push_back(batch);advance+=32-captionMetric(g,0,font,sis)-captionMetric(g,1,font,sis);
    }}return true;
}
bool Melee360LoadOriginalMenu(const unsigned char* archive,unsigned int bytes,int menu,int selection,float frame,Melee360Scene& scene,unsigned int* tracks,bool animate,float hoverFrame,bool backwards){
    scene.batches.clear();scene.textures.clear();scene.skipped=0;if(tracks)*tracks=0;
    if(!archive||bytes<32||!_finite(frame)||frame<0||!_finite(hoverFrame)||hoverFrame<0||!Melee360OriginalMenuSupported(menu)||selection<0)return false;
    int count=Melee360OriginalMenuKinds[menu].count-(menu==1||menu==3||menu==4?1:0);if(selection>=count)return false;
    int originalSelection=selection+((menu==1||menu==3)&&selection>=2?1:menu==4&&selection>=3?1:0);
    unsigned int ds=rootOffset(archive,bytes,"ScMenMain_cam_int1_camera");Reader h={archive,bytes,true};unsigned int size=h.u(4);if(!ds||size>bytes-32)return false;
    MenuPose p(archive+32,size);Loader loader(&p.data[0],size,scene,animate?archive:0);if(!loader.setupCamera(ds))return false;
    const Melee360OriginalLoop backgroundLoop={0,799,0};
    int light=menu==0?selection:menu==1||menu==6||menu==9?0:menu==2||menu==12?1:menu==3?2:menu==4?3:4;
    loader.setupMenuLights(rootOffset(archive,bytes,"ScMenMain_scene_lights"),light);
    if(!gatherMenu(p,archive,bytes,"MenMainBack_Top"))return false;p.branch(0,animate?originalFrame(backgroundLoop,frame):frame);loader.draw(p.joints[0]);
    p.joints.clear();p.anims.clear();p.mats.clear();if(!gatherMenu(p,archive,bytes,"MenMainPanel_Top"))return false;
    p.branch(0,0);p.branch(4,animate?originalFrame(backgroundLoop,frame):frame);float panelFrame=Melee360OriginalMenuKinds[menu].idle;
    if(animate){const Melee360OriginalLoop& enter=Melee360PanelLoops[menu][0];float length=enter.end_frame-enter.start_frame;if(frame<=length)panelFrame=originalFrame(enter,frame);else panelFrame=originalFrame(Melee360PanelLoops[menu][2],frame-length);}p.branch(41,panelFrame);loader.draw(p.joints[0]);
    p.joints.clear();p.anims.clear();p.mats.clear();if(!gatherMenu(p,archive,bytes,"MenMainConTop_Top"))return false;
    p.branch(0,0);const Melee360OriginalLoop entry={backwards?360.f:320.f,backwards?379.f:339.f,-.1f};if(animate)p.one(3,originalFrame(entry,frame),true,false);p.branch(14,animate?originalFrame(Melee360HoverLoops[menu][originalSelection],hoverFrame):Melee360OriginalMenuKinds[menu].hover[originalSelection]);
    // Cursor children are attached to the original slot joints below.
    unsigned int slotOffsets[10];
    for(int i=0;i<count;++i){p.one(4+i,(float)count,true,false);slotOffsets[i]=p.joints[4+i];}
    loader.draw(p.joints[0]);
    // Temporarily parent the single archive cursor to each slot. The hierarchy
    // clone is built from original descriptors; no synthetic button rectangles.
    Matrix slotWorld[10];float slotScale[10][3];for(int i=0;i<count;++i){bool found=false;for(unsigned int j=0;j<loader.poses.size();++j)if(loader.poses[j].joint==slotOffsets[i]){slotWorld[i]=loader.poses[j].world;memcpy(slotScale[i],loader.poses[j].scale,sizeof(slotScale[i]));found=true;break;}if(!found)return false;}
    std::vector<unsigned char> base=p.data;
    for(int i=0;i<count;++i){p.data=base;p.r.d=&p.data[0];loader.r.d=&p.data[0];p.joints.clear();p.anims.clear();p.mats.clear();
        if(!gatherMenu(p,archive,bytes,"MenMainCursor_Top"))return false;p.branch(0,0);
        int originalIndex=i+((menu==1||menu==3)&&i>=2?1:menu==4&&i>=3?1:0);
        const Melee360OriginalLoop buttonLoops[2]={{0,49,0},{50,99,50}},ringLoops[2]={{0,49,-.1f},{50,250,50}};
        p.one(2,animate?originalFrame(buttonLoops[i==selection],hoverFrame):i==selection?70.f:20.f);p.branch(3,i==selection?1.f:0.f);p.one(3,(float)(Melee360OriginalMenuKinds[menu].labelFrame+originalIndex*2),true,true,true);
        p.branch(4,i==selection?(animate?originalFrame(ringLoops[1],hoverFrame):70.f):49.f);
        const Melee360OriginalLoop effectLoop={0,10,-.1f};if(animate&&i==selection&&hoverFrame<10){p.one(9,originalFrame(effectLoop,hoverFrame));p.hide(p.joints[9],false,true);}else p.hide(p.joints[9],true,true);p.hide(p.joints[11],true,true);
        // Label color tracks 12..19 are intentionally sampled with the hover
        // pose, while the label image selection uses menu*20+selection*2.
        loader.draw(p.joints[0],slotWorld[i],slotScale[i]);
    }
    if(tracks)*tracks=p.tracks;return p.ok&&p.r.ok&&loader.r.ok&&!scene.batches.empty();
}
void Melee360ResetSceneCache(){for(int i=0;i<3;++i){ArchiveCache& c=archiveCaches[i];c.source=0;c.meshes.clear();c.textures.clear();c.pixels=c.stamp=0;}cacheStamp=0;}
bool Melee360LoadTrophyModel(const unsigned char* archive,unsigned int bytes,const char* name,Melee360Scene& scene){
    scene=Melee360Scene();if(!archive||bytes<32||!name)return false;Reader header={archive,bytes,true};unsigned int ds=header.u(4);bool found=false;unsigned int root=rootOffset(archive,bytes,name,&found);if(!found||ds>bytes-32)return false;
    Loader loader(archive+32,ds,scene,archive);loader.camera=identity();loader.draw(root);if(!loader.r.ok||scene.batches.empty()){
#ifndef _XBOX
        printf("Trophy loader %s: reader=%u batches=%u skipped=%u\n",name,(unsigned int)loader.r.ok,(unsigned int)scene.batches.size(),scene.skipped);
#endif
        return false;}
    float lo[3]={1e30f,1e30f,1e30f},hi[3]={-1e30f,-1e30f,-1e30f};
    for(unsigned int b=0;b<scene.batches.size();++b)for(unsigned int v=0;v<scene.batches[b].vertices.size();++v)for(int c=0;c<3;++c){float x=scene.batches[b].vertices[v].clip[c];if(x<lo[c])lo[c]=x;if(x>hi[c])hi[c]=x;}
    float extent=0;for(int c=0;c<3;++c)if(hi[c]-lo[c]>extent)extent=hi[c]-lo[c];if(extent<1e-6f)return false;
    for(unsigned int b=0;b<scene.batches.size();++b)for(unsigned int v=0;v<scene.batches[b].vertices.size();++v){Melee360SceneVertex& o=scene.batches[b].vertices[v];for(int c=0;c<3;++c)o.clip[c]=(o.clip[c]-(lo[c]+hi[c])*.5f)*2/extent;o.clip[3]=1;}
    return true;
}
bool Melee360LoadStaticScene(const unsigned char* archive,unsigned int bytes,const char* root,Melee360Scene& scene) {
    scene.batches.clear();scene.textures.clear();scene.skipped=0;
    if(!archive||bytes<32||!root)return false;
    Reader header={archive,bytes,true};unsigned int ds=header.u(4),nr=header.u(8),np=header.u(12),ne=header.u(16);
    unsigned __int64 table=32ULL+ds+4ULL*nr,names=table+8ULL*(np+ne);if(header.u(0)!=bytes||names>bytes)return false;
    unsigned int sceneOffset=0,menuCamera=0;bool found=false;
    for(unsigned int i=0;i<np;++i){unsigned int offset=header.u((unsigned int)table+i*8),symbol=header.u((unsigned int)table+i*8+4);unsigned __int64 at=names+symbol;
        if(at>=bytes||!memchr(archive+(unsigned int)at,0,bytes-(unsigned int)at))return false;
        if(!strcmp((const char*)archive+(unsigned int)at,root)){found=true;sceneOffset=offset;}
        if(!strcmp((const char*)archive+(unsigned int)at,"ScMenMain_cam_int1_camera"))menuCamera=offset;}
    if(!found)return false;Loader loader(archive+32,ds,scene);
    bool menu=!strcmp(root,"MenMainBack_Top_joint");
    unsigned int cameras=menu?0:loader.r.u(sceneOffset+4),camera=menu?menuCamera:loader.r.u(cameras);
    if(!loader.setupCamera(camera))return false;
    float one[3]={1,1,1};
    if(menu){loader.draw(sceneOffset);return loader.r.ok&&!scene.batches.empty();}
    unsigned int models=loader.r.u(sceneOffset);
    for(unsigned int i=0;i<256&&loader.r.ok;++i){unsigned int model=loader.r.u(models+i*4);if(!model)break;
        loader.draw(loader.r.u(model));if(i==255)loader.r.ok=false;}
    return loader.r.ok&&!scene.batches.empty();
}
bool Melee360LoadCharacterSelect(const unsigned char* archive,unsigned int bytes,int selected,Melee360Scene& scene,float frame,bool animate,const Melee360CSSState* cursor){
    scene.batches.clear();scene.textures.clear();scene.skipped=0;
    if(!archive||bytes<32||!_finite(frame)||frame<0||selected< -1||selected>=25)return false;
    bool found=false;unsigned int root=rootOffset(archive,bytes,"MnSelectChrDataTable",&found);if(!found||root!=0)return false;
    Reader h={archive,bytes,true};unsigned int size=h.u(4);if(h.u(0)!=bytes||size>bytes-32||size<160)return false;
    MenuPose p(archive+32,size);Loader l(&p.data[0],size,scene,animate?archive:0);if(!l.setupCamera(p.r.u(0)))return false;
    unsigned int pieces[2]={0x10,0x40};std::vector<unsigned int> highlightJoints;
    static const unsigned int icons[25]={4,16,17,18,19,20,21,22,6,8,23,24,25,26,27,28,29,10,12,30,31,32,33,34,14};
    for(int part=0;part<2;++part){unsigned int at=pieces[part];p.joints.clear();p.anims.clear();p.mats.clear();p.gather(p.r.u(at),p.r.u(at+4),p.r.u(at+8));if(p.joints.empty())return false;const Melee360OriginalLoop cssBackground={0,200,0};p.branch(0,part==0&&animate?originalFrame(cssBackground,frame):0);
        if(part==1){for(int i=0;i<25;++i){unsigned int id=icons[i];if(id>=p.joints.size())return false;p.hide(p.joints[id],false,true);}
            // Expose unlockable portraits in this diagnostic; no save flags are loaded.
            unsigned int special[6]={4,6,8,10,12,14};for(int i=0;i<6;++i){unsigned int id=special[i];if(id)p.branch(id-1,20);p.hide(p.joints[id],false,true);}
            p.number(p.joints[17]+48,20.2f);p.number(p.joints[30]+48,5.8f);
            if(cursor){
                // mnCharSel_803F0DFC joint IDs and mnCharSel_804D50CC/D8 frames.
                // Single human P1, closed P2-P4, neutral-costume HUD portraits.
                static const unsigned int doors[4][6]={{0x2e,0x33,0x38,0x85,0x29,0xa6},{0x2f,0x34,0x39,0x8d,0x2a,0xa8},{0x30,0x35,0x3a,0x95,0x2b,0xaa},{0x31,0x36,0x3b,0x9d,0x2c,0xac}};
                if(p.joints.size()<=0xac)return false;
                for(int port=0;port<4;++port){
                    p.branch(doors[port][3],port==0?40.f:0.f);
                    p.one(doors[port][5],port==0?1.f:2.f);
                    p.one(doors[port][4],port==0?2.f:7.f,false,true,false,2);
                    p.one(doors[port][0],port==0?2.f:7.f,false,true,false,1);
                    p.hide(p.joints[doors[port][2]],true,true);
                    static const unsigned int sliders[4][3]={{0x3d,0x41,0x40},{0x43,0x47,0x46},{0x49,0x4d,0x4c},{0x4f,0x53,0x52}};
                    for(int field=0;field<3;++field)p.hide(p.joints[sliders[port][field]],true,true);
                    int portrait=port==0?Melee360CSSPortraitFrame(selected):-1;
                    for(int field=0;field<2;++field){unsigned int id=doors[port][field];p.hide(p.joints[id],portrait<0,true);if(portrait>=0)p.one(id,(float)portrait,false,true,false,2);}
                }
            }
            if(selected>=0){if(cursor&&cursor->confirmed)p.one(icons[selected],10,false,true);highlightJoints.push_back(p.joints[icons[selected]]);for(unsigned int n=0;n<highlightJoints.size();++n){unsigned int child=p.r.u(highlightJoints[n]+8);for(unsigned int g=0;child&&g<4096;++g){highlightJoints.push_back(child);child=p.r.u(child+12);}if(highlightJoints.size()>4096)return false;}}
        }l.draw(p.joints[0]);if(!p.ok||!p.r.ok||!l.r.ok)return false;
    }
    if(cursor){
        if(!_finite(cursor->handX)||!_finite(cursor->handY)||!_finite(cursor->tokenX)||!_finite(cursor->tokenY))return false;
        // The original hand/token descriptors; color and state frames correspond
        // to the single P1 boundary. No synthetic cursor rectangle is appended.
        const unsigned int descriptors[2]={0x30,0x20};
        for(int part=0;part<2;++part){unsigned int at=descriptors[part];p.joints.clear();p.anims.clear();p.mats.clear();p.gather(p.r.u(at),p.r.u(at+4),p.r.u(at+8));if(p.joints.empty())return false;p.branch(0,0);
            if(part==1&&p.joints.size()>3){p.one(2,(float)cursor->handState,false,true);p.one(3,0,false,true);}
            p.number(p.joints[0]+44,part==0?cursor->tokenX:cursor->handX);p.number(p.joints[0]+48,part==0?cursor->tokenY:cursor->handY);p.number(p.joints[0]+52,0);
            l.draw(p.joints[0]);if(!p.ok||!p.r.ok||!l.r.ok)return false;
        }
        return !scene.batches.empty();
    }
    if(selected<0)return !scene.batches.empty();
    // Diagnostic highlight follows the projected original portrait geometry.
    float left=1e30f,right=-1e30f,top=-1e30f,bottom=1e30f;
    for(unsigned int i=0;i<scene.batches.size();++i){Melee360SceneBatch& batch=scene.batches[i];bool match=false;for(unsigned int j=0;j<highlightJoints.size();++j)if(batch.joint==highlightJoints[j])match=true;if(!match)continue;
        for(unsigned int v=0;v<batch.vertices.size();++v){Melee360SceneVertex& o=batch.vertices[v];if(o.clip[3]<=0)return false;float x=o.clip[0]/o.clip[3],y=o.clip[1]/o.clip[3];if(x<left)left=x;if(x>right)right=x;if(y>top)top=y;if(y<bottom)bottom=y;}}
    if(left>right)return false;    Melee360SceneBatch b;b.texture=-1;b.joint=0;b.mode=(1u<<27)|(1u<<29);b.wrapS=b.wrapT=0;
    for(int edge=0;edge<4;++edge){float x0=left,x1=right,y0=top,y1=bottom;
        if(edge==0)y1=top-.012f;else if(edge==1)y0=bottom+.012f;else if(edge==2)x1=left+.012f;else x0=right-.012f;
        float xy[6][2]={{x0,y0},{x1,y0},{x0,y1},{x0,y1},{x1,y0},{x1,y1}};
        for(int v=0;v<6;++v){Melee360SceneVertex o;o.clip[0]=xy[v][0];o.clip[1]=xy[v][1];o.clip[2]=0;o.clip[3]=1;o.uv[0]=o.uv[1]=0;o.color[0]=1;o.color[1]=.85f;o.color[2]=.1f;o.color[3]=1;b.vertices.push_back(o);}
    }scene.batches.push_back(b);return !scene.batches.empty();
}
static bool loadFighterPreview(const unsigned char* archive,unsigned int bytes,const unsigned char* motion,unsigned int motionBytes,float frame,Melee360Scene& scene,unsigned int* tracks){
    if(tracks)*tracks=0;
    scene.batches.clear();scene.textures.clear();scene.skipped=0;if(!archive||bytes<32)return false;
    Reader h={archive,bytes,true};unsigned int size=h.u(4),nr=h.u(8),np=h.u(12),ne=h.u(16);unsigned __int64 table=32ULL+size+nr*4ULL,names=table+(np+ne)*8ULL;
    if(h.u(0)!=bytes||names>bytes)return false;unsigned int root=0;
    for(unsigned int i=0;i<np;++i){unsigned int s=h.u((unsigned int)table+i*8+4);if(names+s>=bytes||!memchr(archive+names+s,0,bytes-(unsigned int)(names+s)))return false;
        const char* name=(const char*)archive+names+s;size_t n=strlen(name);if(n>6&&!strcmp(name+n-6,"_joint")){root=h.u((unsigned int)table+i*8);break;}}
    if(!root)return false;MenuPose pose(archive+32,size);
    if(motion){
        if(motionBytes<32||!_finite(frame)||frame<0)return false;Reader outer={motion,motionBytes,true};
        unsigned int os=outer.u(4),nr=outer.u(8),np=outer.u(12);unsigned __int64 table=32ULL+os+nr*4ULL;
        if(outer.u(0)!=motionBytes||!np||table+8>motionBytes)return false;
        unsigned int start=32+outer.u((unsigned int)table);if(!outer.range(start,32))return false;unsigned int chunk=outer.u(start);
        if(chunk<32||!outer.range(start,chunk))return false;Reader nested={motion+start,chunk,true};
        unsigned int ns=nested.u(4),nn=nested.u(8),npublic=nested.u(12);unsigned __int64 nt=32ULL+ns+nn*4ULL;
        if(ns>chunk-32||npublic!=1||nt+8>chunk)return false;
        unsigned int tree=nested.u((unsigned int)nt);Reader anim={nested.d+32,ns,true};if(!anim.range(tree,20))return false;
        float end=anim.f(tree+8);unsigned int nodes=anim.u(tree+12),track=anim.u(tree+16),kind=anim.u(tree);
        if(!anim.ok||end<=0||kind>1)return false;float sample=fmodf(frame,end);
        pose.gather(root,0,0);if(!pose.ok||pose.joints.empty())return false;
        for(unsigned int joint=0;joint<pose.joints.size();++joint){
            if(!anim.range(nodes+joint,1))return false;unsigned int count=anim.d[nodes+joint];if(count>127)return false;
            if(count){unsigned int j=pose.joints[joint];pose.put(j+4,kind&1?pose.r.u(j+4)|8:pose.r.u(j+4)&~8u);
                MenuPose::Target target={&pose,j,0,0,false};
                if(!Melee360SampleFigaTracks(anim.d,anim.size,track,count,sample,MenuPose::update,&target,tracks)||!pose.ok)return false;}
            track+=count*12;
        }
        if(!anim.range(nodes+(unsigned int)pose.joints.size(),1)||anim.d[nodes+pose.joints.size()]!=255)return false;
    }
    Loader l(pose.r.d,size,scene,motion?archive:0);l.draw(root);if(!l.r.ok||scene.batches.empty())return false;
    float min[3]={1e30f,1e30f,1e30f},max[3]={-1e30f,-1e30f,-1e30f};float angle=-.45f,c=cosf(angle),s=sinf(angle);
    for(unsigned int i=0;i<scene.batches.size();++i)for(unsigned int v=0;v<scene.batches[i].vertices.size();++v){Melee360SceneVertex& o=scene.batches[i].vertices[v];float x=o.clip[0],z=o.clip[2];o.clip[0]=x*c+z*s;o.clip[2]=-x*s+z*c;
        for(int k=0;k<3;++k){if(!_finite(o.clip[k]))return false;if(o.clip[k]<min[k])min[k]=o.clip[k];if(o.clip[k]>max[k])max[k]=o.clip[k];}}
    float height=max[1]-min[1],width=max[0]-min[0];if(height<.001f||width<.001f)return false;float scale=1.7f/height;if(width*scale>1.7f)scale=1.7f/width;
    for(unsigned int i=0;i<scene.batches.size();++i)for(unsigned int v=0;v<scene.batches[i].vertices.size();++v){Melee360SceneVertex& o=scene.batches[i].vertices[v];o.clip[0]=(o.clip[0]-(min[0]+max[0])*.5f)*scale;o.clip[1]=(o.clip[1]-(min[1]+max[1])*.5f)*scale;o.clip[2]=.1f+.8f*(max[2]-o.clip[2])/(max[2]-min[2]+.001f);o.clip[3]=1;}
    return true;
}

bool Melee360LoadFighterPreview(const unsigned char* archive,unsigned int bytes,Melee360Scene& scene){return loadFighterPreview(archive,bytes,0,0,0,scene,0);}
bool Melee360LoadAnimatedFighterPreview(const unsigned char* model,unsigned int modelBytes,const unsigned char* motion,unsigned int motionBytes,float frame,Melee360Scene& scene,unsigned int* tracks){
    if(!motion)return false;return loadFighterPreview(model,modelBytes,motion,motionBytes,frame,scene,tracks);
}
bool Melee360LoadAnimatedTitle(const unsigned char* archive,unsigned int bytes,float frame,Melee360Scene& scene,unsigned int* tracks){
    scene.batches.clear();scene.textures.clear();scene.skipped=0;if(tracks)*tracks=0;
    if(!archive||bytes<32||!_finite(frame)||frame<0)return false;
    bool found=false;unsigned int cam=rootOffset(archive,bytes,"ScTitle_cam_int1_camera",&found);Reader h={archive,bytes,true};unsigned int size=h.u(4);if(!found||size>bytes-32)return false;
    MenuPose p(archive+32,size);Loader l(&p.data[0],size,scene,archive);if(!l.setupCamera(cam))return false;
    const Melee360OriginalLoop title={400,1600,400},background={130,1330,130};
    const char* parts[2]={"TtlBg_Top","TtlMoji_Top"};
    for(int i=0;i<2;++i){p.joints.clear();p.anims.clear();p.mats.clear();if(!gatherMenu(p,archive,bytes,parts[i]))return false;p.branch(0,originalFrame(i==0?background:title,frame));l.draw(p.joints[0]);if(!p.ok||!p.r.ok||!l.r.ok)return false;}
    if(tracks)*tracks=p.tracks;return !scene.batches.empty();
}
bool Melee360LoadBattlefield(const unsigned char* archive,unsigned int bytes,float frame,int background,Melee360Scene& scene,unsigned int* tracks,unsigned int* groups){
    scene.batches.clear();scene.textures.clear();scene.skipped=scene.unsupportedEvents=0;if(tracks)*tracks=0;if(groups)*groups=0;
    if(!archive||bytes<32||!_finite(frame)||frame<0||background<0||background>3)return false;
    bool found=false;unsigned int root=rootOffset(archive,bytes,"map_head",&found);Reader h={archive,bytes,true};unsigned int size=h.u(4);
    if(!found||size>bytes-32)return false;MenuPose p(archive+32,size);p.descriptorLoops=true;
    if(!p.r.range(root,48))return false;unsigned int models=p.r.u(root+8),count=p.r.u(root+12);
    if(count!=7||!p.r.range(models,count*52))return false;
    Loader l(&p.data[0],size,scene,archive);unsigned int camera=p.r.u(models+6*52+16);if(!l.setupCamera(camera))return false;
    static const unsigned int backgrounds[4]={1,2,4,5};
    // Match the playable platform and select one of the original background
    // variants. Model 3 is the transition overlay, drawn by its own descriptors.
    const unsigned int selected[4]={0,backgrounds[background],3,6};
    for(unsigned int i=0;i<4;++i){unsigned int at=models+selected[i]*52,j=p.r.u(at),aj=p.r.u(at+4),mj=p.r.u(at+8);
        if(p.r.u(at+12))return false; // Morph animation is not implemented.
        if(aj&&(!p.r.range(aj,8)||p.r.u(aj+4)))return false;
        if(mj&&(!p.r.range(mj,8)||p.r.u(mj+4)))return false;
        // grAnime_801C8138 sets AOBJ_LOOP for the full hierarchy from the
        // per-animation byte table at map model +0x28, not just AObjDesc flags.
        unsigned int loopFlags=p.r.u(at+40);p.stageForcedLoop=loopFlags&&p.r.range(loopFlags,1)&&p.data[loopFlags]!=0;
        p.joints.clear();p.anims.clear();p.mats.clear();p.gather(j,aj?p.r.u(aj):0,mj?p.r.u(mj):0);
        if(p.joints.empty())return false;for(unsigned int n=0;n<p.joints.size();++n)p.one(n,frame);
        if(!p.ok||!p.r.ok){printf("Stage animation failed model=%u p=%d r=%d\n",selected[i],p.ok,p.r.ok);return false;}l.draw(j);if(!l.r.ok){printf("Stage geometry failed model=%u\n",selected[i]);return false;}if(groups)++*groups;
    }
    scene.unsupportedEvents=p.unsupportedEvents;if(tracks)*tracks=p.tracks;return !scene.batches.empty()&&p.ok&&p.r.ok&&l.r.ok;
}

bool Melee360LoadStageSelect(const unsigned char* archive,unsigned int bytes,float frame,float cursorX,float cursorY,int hover,Melee360Scene& scene){
    scene=Melee360Scene();if(!archive||bytes<32||!_finite(frame)||!_finite(cursorX)||!_finite(cursorY)||hover< -1||hover>29)return false;
    bool found=false;unsigned int table=rootOffset(archive,bytes,"MnSelectStageDataTable",&found);Reader h={archive,bytes,true};unsigned int size=h.u(4);if(!found||table!=0||size>bytes-32||size<208)return false;
    MenuPose p(archive+32,size);Loader l(&p.data[0],size,scene,archive);if(!l.setupCamera(p.r.u(0)))return false;
    float positions[19][3];unsigned int layout=p.r.u(0xa0);p.gather(layout,p.r.u(0xa4),p.r.u(0xa8));if(p.joints.empty())return false;p.branch(0,60);unsigned int node=p.r.u(layout+8);
    for(int i=0;i<19;++i){if(!node||!p.r.range(node,64))return false;for(int k=0;k<3;++k)positions[i][k]=p.r.f(node+44+k*4);node=p.r.u(node+12);}
    for(int piece=0;piece<21;++piece){unsigned int descriptor;int layoutIndex=-1;float pose=0;bool disabled=false;
        if(piece==0){descriptor=0xb0;pose=frame;}
        else if(piece==1){descriptor=0x60;pose=60;}
        else if(piece>=2&&piece<13){descriptor=0x50;layoutIndex=piece-2;pose=0;disabled=true;}
        else if(piece>=13&&piece<18){descriptor=0x30;layoutIndex=piece-2;pose=(float)(piece-11);disabled=piece!=13;}
        else if(piece==18){descriptor=0x10;layoutIndex=17;pose=2;disabled=true;}
        else if(piece==19){descriptor=0x10;layoutIndex=18;pose=3;disabled=true;}
        else{descriptor=0x20;layoutIndex=16;pose=2;disabled=true;}
        p.joints.clear();p.anims.clear();p.mats.clear();p.gather(p.r.u(descriptor),p.r.u(descriptor+4),p.r.u(descriptor+8));if(p.joints.empty())return false;p.branch(0,pose);
        if(piece>=13&&piece<=20){p.branch(0,0,true,false);p.branch(0,pose,false,true);}
        if(piece>=2&&piece<13){unsigned int child=p.r.u(p.joints[0]+8);for(unsigned int j=0;j<p.joints.size();++j)if(p.joints[j]==child||p.joints[j]==p.r.u(child+12))p.one(j,(float)(Melee360StageFrame((piece-2)*2)/2+2),false,true);}
        if(layoutIndex>=0){for(int k=0;k<3;++k)p.number(p.joints[0]+44+k*4,positions[layoutIndex][k]);}
        unsigned int first=(unsigned int)scene.batches.size();l.draw(p.joints[0]);
        for(unsigned int b=first;b<scene.batches.size();++b)if(disabled)for(unsigned int v=0;v<scene.batches[b].vertices.size();++v)for(int c=0;c<3;++c)scene.batches[b].vertices[v].color[c]*=.35f;
        if(piece>=2&&piece<13){unsigned int child=p.r.u(p.joints[0]+8),other=p.r.u(child+12);Melee360StageSetPosition((piece-2)*2,positions[layoutIndex][0]+p.r.f(other+44),positions[layoutIndex][1]+p.r.f(other+48));Melee360StageSetPosition((piece-2)*2+1,positions[layoutIndex][0]+p.r.f(child+44),positions[layoutIndex][1]+p.r.f(child+48));}
        else if(piece>=13&&piece<18)Melee360StageSetPosition(piece+11,positions[layoutIndex][0],positions[layoutIndex][1]);
        else if(piece==18||piece==19)Melee360StageSetPosition(piece+4,positions[layoutIndex][0],positions[layoutIndex][1]);
        else if(piece==20)Melee360StageSetPosition(29,positions[layoutIndex][0],positions[layoutIndex][1]);
    }
    const unsigned int descriptors[3]={0x40,0x70,0x90};for(int piece=0;piece<3;++piece){unsigned int descriptor=descriptors[piece];if(piece<2&&(hover<0||hover>=29))continue;p.joints.clear();p.anims.clear();p.mats.clear();p.gather(p.r.u(descriptor),p.r.u(descriptor+4),p.r.u(descriptor+8));if(p.joints.empty())return false;if(piece==0){p.branch(0,9,true,false);p.branch(0,20.f*Melee360StageFrame(hover),false,true);}else p.branch(0,piece==1?50.f*Melee360StageFrame(hover)+49:0);if(piece==1)p.number(p.joints[0]+44,0);if(piece==2){p.number(p.joints[0]+44,cursorX);p.number(p.joints[0]+48,cursorY);}l.draw(p.joints[0]);}
    return p.ok&&p.r.ok&&l.r.ok&&!scene.batches.empty();
}

// Descriptor bridge for mnsoundtest.c's music view. Original FObj sampling;
// SSM category view and original SIS dynamic music labels remain pending.
bool Melee360LoadSoundTest(const unsigned char* archive,unsigned int bytes,float frame,bool playing,Melee360Scene& scene,unsigned int* tracks){
    scene=Melee360Scene();if(tracks)*tracks=0;if(!archive||bytes<32||!_finite(frame)||frame<0)return false;
    Reader header={archive,bytes,true};unsigned int size=header.u(4),camera=rootOffset(archive,bytes,"ScMenMain_cam_int1_camera");if(size>bytes-32||!camera)return false;
    MenuPose p(archive+32,size);Loader loader(&p.data[0],size,scene,archive);if(!loader.setupCamera(camera))return false;loader.setupMenuLights(rootOffset(archive,bytes,"ScMenMain_scene_lights"),4);
    if(!gatherMenu(p,archive,bytes,"MenMainBack_Top"))return false;p.branch(0,fmodf(frame,800.f));loader.draw(p.joints[0]);
    p.joints.clear();p.anims.clear();p.mats.clear();if(!gatherMenu(p,archive,bytes,"MenMainConTs_Top")||p.joints.size()<22)return false;
    p.branch(0,0);float entry=frame<19?frame:19;
    p.one(1,entry,true,false);p.one(2,entry,true,false);p.one(11,entry,true,false);
    p.branch(2,1,false,true);p.one(5,fmodf(frame,21.f),false,true);p.one(4,playing?fmodf(frame,201.f):0,false,true);
    p.branch(11,0,false,true);p.one(13,10,false,true);p.one(14,0,false,true);p.one(20,0,false,true);p.hide(p.joints[19],true,true);
    loader.draw(p.joints[0]);if(tracks)*tracks=p.tracks;return p.ok&&p.r.ok&&loader.r.ok&&!scene.batches.empty();
}

// Settings descriptors and joint indices follow mnsound.c / mnvibration.c.
bool Melee360LoadOptions(const unsigned char* archive,unsigned int bytes,int page,int selection,int output,int music,unsigned int rumble,unsigned int connected,float frame,Melee360Scene& scene,unsigned int* tracks){
    scene=Melee360Scene();if(tracks)*tracks=0;if(!archive||bytes<32||(page!=19&&page!=20&&page!=152)||selection<0||selection>3||music<0||music>10||output<0||output>2||!_finite(frame)||frame<0)return false;
    Reader h={archive,bytes,true};unsigned int size=h.u(4),camera=rootOffset(archive,bytes,"ScMenMain_cam_int1_camera");if(size>bytes-32||!camera)return false;
    MenuPose p(archive+32,size);Loader l(&p.data[0],size,scene,archive);if(!l.setupCamera(camera))return false;l.setupMenuLights(rootOffset(archive,bytes,"ScMenMain_scene_lights"),page==152?4:3);
    if(!gatherMenu(p,archive,bytes,"MenMainBack_Top"))return false;p.branch(0,fmodf(frame,800.f));l.draw(p.joints[0]);p.joints.clear();p.anims.clear();p.mats.clear();
    if(!gatherMenu(p,archive,bytes,page==152?"MenMainConCo_Top":page==20?"MenMainConSo_Top":"MenMainConVi_Top"))return false;p.branch(0,0);
    if(page==152){if(p.joints.size()<3)return false;p.branch(0,fmodf(frame,200.f));p.hide(p.joints[1],true,true);p.hide(p.joints[2],true,true);l.draw(p.joints[0]);}
    else if(page==20){if(p.joints.size()<15)return false;p.branch(8,output==0?1:0);p.one(9,selection==0?fmodf(frame,200.f):0,false,true);p.one(10,selection==0?fmodf(frame,200.f):0,false,true);
        p.one(11,(output==0?0.f:10.f)+fmodf(frame,6.f),false,true);p.one(14,(selection==0?0.f:30.f)+fmodf(frame,30.f),false,true);
        float left=p.r.f(p.joints[3]+44),right=p.r.f(p.joints[4]+44);p.number(p.joints[6]+44,left+(right-left)*music/10.f);l.draw(p.joints[0]);
    }else{if(p.joints.size()<25)return false;for(int i=19;i<=22;++i)p.hide(p.joints[i],true,true);l.draw(p.joints[0]);
        Matrix parent=identity();float scale[3]={1,1,1};bool found=false;for(unsigned int i=0;i<l.poses.size();++i)if(l.poses[i].joint==p.joints[23]){parent=l.poses[i].world;memcpy(scale,l.poses[i].scale,sizeof(scale));found=true;break;}if(!found)return false;
        float spacing=p.r.f(p.joints[24]+44)-p.r.f(p.joints[23]+44);std::vector<unsigned char> base=p.data;
        for(int port=0;port<4;++port){p.data=base;p.r.d=&p.data[0];l.r.d=&p.data[0];p.joints.clear();p.anims.clear();p.mats.clear();if(!gatherMenu(p,archive,bytes,"MenMainCtlVi_Top")||p.joints.size()<4)return false;p.branch(0,0);p.number(p.joints[0]+44,spacing*port);
            bool present=(connected&(1u<<port))!=0;p.branch(1,present?(float)port:20,true,false);p.branch(1,(rumble&(1u<<port))?1.f:0.f,false,true);p.branch(2,present?((rumble&(1u<<port))?1.f:0.f):20.f);p.branch(3,present?(float)(port+1):20.f);l.draw(p.joints[0],parent,scale);
        }
    }
    if(tracks)*tracks=p.tracks;return p.ok&&p.r.ok&&l.r.ok&&!scene.batches.empty();
}
