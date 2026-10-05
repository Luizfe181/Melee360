#include <stddef.h>
#include <xtl.h>
#include <xgraphics.h>
#include <vector>
#include <stdio.h>
#include <math.h>
extern "C" void* _ReturnAddress(void);
#pragma intrinsic(_ReturnAddress)
#include "platform_log.h"
#include "gx_texture.h"
#include "scene_VS.h"
#include "gx_direct_PS.h"
#include "gx_direct_VS.h"
#include "gx_direct_depth_PS.h"
#include "gx_direct_quantized_PS.h"
#include "gx_early_depth_PS.h"

#undef DEBUG
#define DEBUG 1
extern "C" {
#include <dolphin/gx/GXGeometry.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXLighting.h>
#include <dolphin/gx/GXFrameBuffer.h>
#include <dolphin/gx/GXTexture.h>
#include <dolphin/gx/GXGet.h>
#include <dolphin/gx/GXTev.h>
#include <dolphin/gx/GXBump.h>
#include <dolphin/gx/GXCpu2Efb.h>
#include <dolphin/gx/GXCull.h>
void __assert(const char*,unsigned int,const char*);
int Melee360GXTransformPosition(const float*,float*);
int Melee360GXTransformEyePosition(u32,const float*,float*);int Melee360GXTransformNormal(u32,const float*,float*);u32 Melee360GXCurrentMatrix(void);int Melee360GXTransformTexcoord(u32,const float*,float*);int Melee360GXTransformPostTexcoord(u32,const float*,float*);
int Melee360GXTransformPositionSlot(u32,const float*,float*);
void GXTexCoord1u8(u8);
extern GXBool __GXinBegin;
int Melee360GXDepthCompression(void);
int Melee360GXCullMode(void);int Melee360GXRGBA6(void);int Melee360GXDither(void);int Melee360GXPixelFormat(void);u32 Melee360GXColorUpdates(void);u32 Melee360GXPackEfbColor(u32);
}
extern "C" void Melee360GXFinishCompletedPacket(void);
namespace {void requireImpl(bool,unsigned int,const char*);}
#define require(condition) (Melee360GXFinishCompletedPacket(),requireImpl((condition),__LINE__,__FILE__))

#include "gx_profile.inc"
namespace {
struct Vertex {float clip[4],uv[3],color[4],extraUV[7][3],color1[4];};
IDirect3DDevice9* device;IDirect3DVertexShader9* vs;IDirect3DPixelShader9* ps;IDirect3DPixelShader9* psDepth;IDirect3DPixelShader9* psQuant;IDirect3DPixelShader9* psEarly;bool earlyDepth;IDirect3DVertexDeclaration9* decl;IDirect3DTexture9* white;
struct TextureImage {GXTexObj* object;const void* image;};
std::vector<TextureImage> textureImages;IDirect3DTexture9* loadedTextures[8];
struct PaletteImage {GXTlutObj* object;const u8* image;u32 format,entries;};
std::vector<PaletteImage> paletteImages;
struct Palette {std::vector<u8> data;u32 format,entries;};Palette palettes[20];
bool textureExpansionTesting;unsigned int selectedTexture;float textureLod[8][4],textureBias[8];
GXTexObj boundDescriptors[8];std::vector<u8> boundImages[8];bool boundValid[8];const u8* boundSources[8];
void uploadTexture(GXTexObj*,const u8*,GXTexMapID);
void uploadTev();void initializeTev();void uploadFog();
float alphaFirst[4]={7,0,0,0},alphaSecond[4]={7,0,0,0};
bool particleFifo;void* beginCaller;bool matrixEnabled,matrixReady;u8 vertexMatrix;
bool positionEnabled,colorEnabled,texEnabled,waitingTex,waitingColor,primitiveActive;unsigned int expected;std::vector<Vertex> vertices;GXAttrType posDescriptor=GX_NONE;const u8* posArray;u8 posStride;GXAttrType texDescriptor=GX_NONE;const u8* texArray;u8 texStride;GXAttrType colorDescriptor=GX_NONE;const u8* colorArray;u8 colorStride;Vertex pending;GXPrimitive activePrimitive;std::vector<Vertex> triangleVertices;unsigned __int64 avoidedCopyBytes;
struct Format {GXCompCnt count;GXCompType type;u8 frac;bool set;} posFormats[8],colorFormats[8],texFormats[8];
struct ExtraInput {GXAttrType descriptor;const u8* data;u8 stride;Format formats[8];};ExtraInput extraTex[7],extraColor;unsigned int currentTex,currentColor;static unsigned int activeFormat;void finishVertex();
#include "gx_lighting_state.inc"
static unsigned colorEncodedBytes(GXCompType type){return type==GX_RGB565||type==GX_RGBA4?2:type==GX_RGB8||type==GX_RGBA6?3:4;}
static unsigned int positionScalarSize(GXCompType);static float decodePositionScalar(const u8*,GXCompType,u8);
#include "gx_vertex_inputs.inc"
#include "gx_texgen_state.inc"
struct OwnedMipTexture {IDirect3DTexture9* texture;void* allocation;};std::vector<OwnedMipTexture> ownedMipTextures;
bool textureCached(IDirect3DTexture9*);
void releaseTexture(IDirect3DTexture9* texture){
    if(!texture||textureCached(texture))return;
    for(unsigned int i=0;i<ownedMipTextures.size();++i)if(ownedMipTextures[i].texture==texture){
        for(int unit=0;unit<8;++unit){IDirect3DBaseTexture9* bound=0;if(SUCCEEDED(device->GetTexture(unit,&bound))&&bound){if(bound==texture)device->SetTexture(unit,0);bound->Release();}}
        device->BlockUntilIdle();XPhysicalFree(ownedMipTextures[i].allocation);_aligned_free(texture);ownedMipTextures.erase(ownedMipTextures.begin()+i);return;
    }
    texture->Release();
}

#include "gx_texture_cache.inc"
void requireImpl(bool value,unsigned int line,const char* file){if(!value)__assert(file,line,"unsupported/invalid direct GX primitive");}
void triangle(unsigned int a,unsigned int b,unsigned int c){triangleVertices.push_back(vertices[a]);triangleVertices.push_back(vertices[b]);triangleVertices.push_back(vertices[c]);}
bool destinationAlphaEnabled;u8 destinationAlpha;
#include "gx_constant_cache.inc"
void bindDirectPipeline(){
    GXProfileTimer timer(&gxProfile.pipelineTicks);
    require(device&&vs&&ps&&decl&&white);device->SetVertexDeclaration(decl);device->SetVertexShader(vs);device->SetPixelShader(ps);
    const float viewport[4]={1,0,0,0};device->SetVertexShaderConstantF(0,viewport,1);for(unsigned int unit=0;unit<8;++unit)device->SetTexture(unit,loadedTextures[unit]?loadedTextures[unit]:white);
    require(SUCCEEDED(setGXPixelConstants(3,&textureLod[0][0],8))&&SUCCEEDED(setGXPixelConstants(11,textureBias,2)));
    const float framebufferControl[4]={(float)Melee360GXRGBA6(),(float)Melee360GXDither(),0,0};if(framebufferControl[0]){DWORD enabled=0;device->GetRenderState(D3DRS_ALPHABLENDENABLE,&enabled);require(!enabled);}require(SUCCEEDED(setGXPixelConstants(195,framebufferControl,1)));
    const float destinationControl[4]={0,destinationAlpha/255.f,0,0};require(SUCCEEDED(setGXPixelConstants(194,destinationControl,1)));uploadTev();const float routing[4]={(float)selectedTexture,0,0,0};require(SUCCEEDED(setGXPixelConstants(2,routing,1)));
    require(SUCCEEDED(setGXPixelConstants(0,alphaFirst,1))&&SUCCEEDED(setGXPixelConstants(1,alphaSecond,1)));
}
HRESULT drawLate(D3DPRIMITIVETYPE type,unsigned count,const void* data,unsigned stride){DWORD mask=0,zWrite=0,zFunction=0,zEnabled=0,blending=0;device->GetRenderState(D3DRS_COLORWRITEENABLE,&mask);if(!destinationAlphaEnabled||!(mask&8))return device->DrawPrimitiveUP(type,count,data,stride);device->GetRenderState(D3DRS_ZWRITEENABLE,&zWrite);device->GetRenderState(D3DRS_ZFUNC,&zFunction);device->GetRenderState(D3DRS_ZENABLE,&zEnabled);device->GetRenderState(D3DRS_ALPHABLENDENABLE,&blending);device->SetRenderState(D3DRS_COLORWRITEENABLE,mask&7);HRESULT result=device->DrawPrimitiveUP(type,count,data,stride);if(SUCCEEDED(result)){float alpha[4]={1,destinationAlpha/255.f,0,0};setGXPixelConstants(194,alpha,1);device->SetRenderState(D3DRS_COLORWRITEENABLE,8);device->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);device->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);if(zWrite&&zEnabled)device->SetRenderState(D3DRS_ZFUNC,D3DCMP_EQUAL);result=device->DrawPrimitiveUP(type,count,data,stride);alpha[0]=0;setGXPixelConstants(194,alpha,1);}device->SetRenderState(D3DRS_COLORWRITEENABLE,mask);device->SetRenderState(D3DRS_ALPHABLENDENABLE,blending);device->SetRenderState(D3DRS_ZWRITEENABLE,zWrite);device->SetRenderState(D3DRS_ZFUNC,zFunction);return result;}
bool depthTextureActive();
static bool compareAlpha(unsigned alpha,unsigned mode,unsigned reference){switch(mode){case GX_NEVER:return false;case GX_LESS:return alpha<reference;case GX_EQUAL:return alpha==reference;case GX_LEQUAL:return alpha<=reference;case GX_GREATER:return alpha>reference;case GX_NEQUAL:return alpha!=reference;case GX_GEQUAL:return alpha>=reference;default:return true;}}
static bool alphaCannotDiscard(){
 if(alphaFirst[3]<.5f)return true;
 for(unsigned a=0;a<256;++a){bool x=compareAlpha(a,(unsigned)alphaFirst[0],(unsigned)alphaFirst[1]),y=compareAlpha(a,(unsigned)alphaSecond[0],(unsigned)alphaSecond[1]);unsigned op=(unsigned)alphaFirst[2];if(!(op==GX_AOP_AND?(x&&y):op==GX_AOP_OR?(x||y):op==GX_AOP_XOR?(x!=y):(x==y)))return false;}return true;
}
HRESULT drawDirect(D3DPRIMITIVETYPE type,unsigned count,const void* data,unsigned stride){
 DWORD enabled=0,write=0;device->GetRenderState(D3DRS_ZENABLE,&enabled);device->GetRenderState(D3DRS_ZWRITEENABLE,&write);
 /* With no discard or fragment Z override, hardware late Z has the same
    observable result as early Z; avoid the per-triangle stencil emulation. */
 if(!earlyDepth||!enabled||!write||(!depthTextureActive()&&alphaCannotDiscard()))return drawLate(type,count,data,stride);
 require(type==D3DPT_TRIANGLELIST);
 IDirect3DSurface9* depth=0;D3DSURFACE_DESC description;require(SUCCEEDED(device->GetDepthStencilSurface(&depth))&&depth);depth->GetDesc(&description);depth->Release();require(description.Format==D3DFMT_D24S8);
 const D3DRENDERSTATETYPE states[]={D3DRS_STENCILENABLE,D3DRS_STENCILFUNC,D3DRS_STENCILREF,D3DRS_STENCILMASK,D3DRS_STENCILWRITEMASK,D3DRS_STENCILFAIL,D3DRS_STENCILZFAIL,D3DRS_STENCILPASS,D3DRS_TWOSIDEDSTENCILMODE};DWORD old[9];for(unsigned j=0;j<9;++j)device->GetRenderState(states[j],&old[j]);require(!old[0]);
 DWORD mask=0,function=0;device->GetRenderState(D3DRS_COLORWRITEENABLE,&mask);device->GetRenderState(D3DRS_ZFUNC,&function);IDirect3DPixelShader9* original=0;device->GetPixelShader(&original);require(original!=psDepth);
 device->SetRenderState(D3DRS_STENCILENABLE,TRUE);device->SetRenderState(D3DRS_STENCILREF,1);device->SetRenderState(D3DRS_STENCILMASK,255);device->SetRenderState(D3DRS_STENCILWRITEMASK,255);device->SetRenderState(D3DRS_STENCILFAIL,D3DSTENCILOP_KEEP);device->SetRenderState(D3DRS_STENCILZFAIL,D3DSTENCILOP_KEEP);device->SetRenderState(D3DRS_TWOSIDEDSTENCILMODE,FALSE);
 HRESULT result=S_OK;
 for(unsigned i=0;i<count&&SUCCEEDED(result);++i){
  if(gxProfile.enabled)++gxProfile.earlyTriangles;
  const u8* triangle=(const u8*)data+i*3*stride;
  require(SUCCEEDED(device->Clear(0,0,D3DCLEAR_STENCIL,0,1,0)));
  device->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_ALWAYS);device->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_REPLACE);
  device->SetPixelShader(psEarly);device->SetRenderState(D3DRS_COLORWRITEENABLE,0);device->SetRenderState(D3DRS_ZFUNC,function);device->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);result=device->DrawPrimitiveUP(type,1,triangle,stride);
  device->SetRenderState(D3DRS_STENCILFUNC,D3DCMP_EQUAL);device->SetRenderState(D3DRS_STENCILPASS,D3DSTENCILOP_KEEP);
  device->SetPixelShader(original);device->SetRenderState(D3DRS_COLORWRITEENABLE,mask);device->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);device->SetRenderState(D3DRS_ZFUNC,D3DCMP_EQUAL);if(SUCCEEDED(result))result=drawLate(type,1,triangle,stride);
 }
 for(unsigned j=0;j<9;++j)device->SetRenderState(states[j],old[j]);device->SetRenderState(D3DRS_ZFUNC,function);device->SetRenderState(D3DRS_ZWRITEENABLE,write);device->SetRenderState(D3DRS_COLORWRITEENABLE,mask);device->SetPixelShader(original);if(original)original->Release();return result;
}
void submitRaster();
void submit(){
    if(gxProfile.enabled)++gxProfile.draws;
    bindDirectPipeline();triangleVertices.clear();unsigned int i;
    if(activePrimitive==GX_LINES||activePrimitive==GX_LINESTRIP||activePrimitive==GX_POINTS){submitRaster();return;}
    if(Melee360GXCullMode()==GX_CULL_ALL){primitiveActive=false;return;}
    if(activePrimitive==GX_TRIANGLES){avoidedCopyBytes+=(unsigned __int64)expected*sizeof(Vertex);require(SUCCEEDED(drawDirect(D3DPT_TRIANGLELIST,expected/3,&vertices[0],sizeof(Vertex))));primitiveActive=false;return;}
    unsigned int converted=activePrimitive==GX_QUADS?(expected/4)*6:(expected-2)*3;triangleVertices.reserve(converted);
    if(activePrimitive==GX_QUADS){for(i=0;i<expected;i+=4){triangle(i,i+1,i+2);triangle(i,i+2,i+3);}}
    else if(activePrimitive==GX_TRIANGLESTRIP){for(i=2;i<expected;++i){if(i&1)triangle(i-1,i-2,i);else triangle(i-2,i-1,i);}}
    else if(activePrimitive==GX_TRIANGLEFAN){for(i=2;i<expected;++i)triangle(0,i-1,i);}else require(false);
    require(triangleVertices.size()==converted&&SUCCEEDED(drawDirect(D3DPT_TRIANGLELIST,(unsigned int)triangleVertices.size()/3,&triangleVertices[0],sizeof(Vertex))));primitiveActive=false;
}
void finishVertex(){require(!waitingNormal);applyLighting();generateTexcoords();vertices.push_back(pending);waitingColor=waitingTex=false;matrixReady=false;memset(texMatrixIndexReady,0,sizeof(texMatrixIndexReady));if(vertices.size()==expected){submit();if(particleFifo)__GXinBegin=GX_FALSE;}}
}
/* GX has no end opcode. Once all declared vertices were consumed, the
   next state command or primitive is legal even when GXEnd was omitted. */
extern "C" void Melee360GXFinishCompletedPacket(void){if(__GXinBegin&&!primitiveActive&&expected&&vertices.size()==expected)__GXinBegin=GX_FALSE;}
#include "gx_raster.inc"
#include "gx_fog.inc"
#include "gx_tev_state.inc"
extern "C" int Melee360GXDirectBind(IDirect3DDevice9* value){
    if(!value){require(!__GXinBegin);for(int unit=0;unit<8;++unit){releaseTexture(loadedTextures[unit]);loadedTextures[unit]=0;boundImages[unit].clear();boundValid[unit]=false;boundSources[unit]=0;}closeTextureCache();textureImages.clear();paletteImages.clear();for(int i=0;i<20;++i){palettes[i].data.clear();palettes[i].entries=0;}selectedTexture=0;if(vs)vs->Release();if(ps)ps->Release();if(psDepth)psDepth->Release();if(psQuant)psQuant->Release();if(psEarly)psEarly->Release();if(decl)decl->Release();if(white)white->Release();vs=0;ps=0;psDepth=0;psQuant=psEarly=0;decl=0;white=0;device=0;vertices.clear();return 1;}
    require(!device);device=value;initializeTev();
    D3DVERTEXELEMENT9 elements[]={{0,0,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},{0,(WORD)offsetof(Vertex,uv),D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},{0,(WORD)offsetof(Vertex,color),D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},{0,(WORD)offsetof(Vertex,extraUV)+0,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,1},{0,(WORD)offsetof(Vertex,extraUV)+12,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,2},{0,(WORD)offsetof(Vertex,extraUV)+24,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,3},{0,(WORD)offsetof(Vertex,extraUV)+36,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,4},{0,(WORD)offsetof(Vertex,extraUV)+48,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,5},{0,(WORD)offsetof(Vertex,extraUV)+60,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,6},{0,(WORD)offsetof(Vertex,extraUV)+72,D3DDECLTYPE_FLOAT3,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,7},{0,(WORD)offsetof(Vertex,color1),D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,1},D3DDECL_END()};
    if(FAILED(device->CreateVertexShader((DWORD*)Melee360GXDirectVS,&vs))||FAILED(device->CreatePixelShader((DWORD*)Melee360GXDirectPS,&ps))||FAILED(device->CreatePixelShader((DWORD*)Melee360GXDirectDepthPS,&psDepth))||FAILED(device->CreatePixelShader((DWORD*)Melee360GXDirectQuantizedPS,&psQuant))||FAILED(device->CreatePixelShader((DWORD*)Melee360GXEarlyDepthPS,&psEarly))||FAILED(device->CreateVertexDeclaration(elements,&decl))||FAILED(device->CreateTexture(1,1,1,0,(D3DFORMAT)MAKESRGBFMT(D3DFMT_LIN_A8R8G8B8),D3DPOOL_DEFAULT,&white,0)))return 0;
    D3DLOCKED_RECT lock;if(FAILED(white->LockRect(0,&lock,0,0)))return 0;*(DWORD*)lock.pBits=0xffffffff;return SUCCEEDED(white->UnlockRect(0));
}
/* The GC descriptor truncates addresses to its physical RAM space.
 * Keep the actual Xenon CPU pointer when the original initializer runs. */
extern "C" void Melee360GXRegisterTextureImage(GXTexObj* object,const void* image){
    for(unsigned int i=0;i<textureImages.size();++i)if(textureImages[i].object==object){textureImages[i].image=image;return;}
    TextureImage entry={object,image};textureImages.push_back(entry);
}
extern "C" void Melee360GXRegisterPaletteImage(GXTlutObj* object,const void* data,u32 format,u32 entries){
    for(unsigned int i=0;i<paletteImages.size();++i)if(paletteImages[i].object==object){paletteImages[i].image=(const u8*)data;paletteImages[i].format=format;paletteImages[i].entries=entries;return;}
    PaletteImage value={object,(const u8*)data,format,entries};paletteImages.push_back(value);
}
extern "C" void GXLoadTlut(GXTlutObj* object,u32 name){
    require(!__GXinBegin&&object&&name<20);PaletteImage* source=0;
    for(unsigned int i=0;i<paletteImages.size();++i)if(paletteImages[i].object==object)source=&paletteImages[i];
    require(source&&source->image&&source->format<=2&&source->entries>0&&source->entries<=16384);
    palettes[name].data.assign(source->image,source->image+source->entries*2);palettes[name].entries=source->entries;palettes[name].format=source->format;
    for(int unit=0;unit<8;++unit)if(boundValid[unit]&&boundDescriptors[unit].dummy[5]>=GX_TF_C4&&boundDescriptors[unit].dummy[5]<=GX_TF_C14X2&&boundDescriptors[unit].dummy[6]==name)uploadTexture(&boundDescriptors[unit],&boundImages[unit][0],(GXTexMapID)unit);
}

extern "C" void GXSetTevOrder(GXTevStageID stage,GXTexCoordID coord,GXTexMapID map,GXChannelID channel){
    TevStage& t=checkedStage(stage);require((coord>=GX_TEXCOORD0&&coord<=GX_TEXCOORD7)||coord==GX_TEXCOORD_NULL);
    require(channel==GX_COLOR0A0||channel==GX_COLOR0||channel==GX_ALPHA0||channel==GX_COLOR1A1||channel==GX_COLOR1||channel==GX_ALPHA1||channel==GX_COLOR_ZERO||channel==GX_COLOR_NULL||channel==GX_ALPHA_BUMP||channel==GX_ALPHA_BUMPN);
    unsigned int clean=(unsigned int)map&~0x100u;require(clean<8||map==GX_TEXMAP_NULL);
    t.order[3]=(float)(coord<8?coord:0);t.order[0]=(float)(clean<8?clean:0);t.order[1]=(float)channel;t.order[2]=(map!=GX_TEXMAP_NULL&&!(map&0x100))?1.0f:0.0f;
    if(stage==0)selectedTexture=clean<8?clean:0;
}
extern "C" void GXLoadTexObj(GXTexObj* object,GXTexMapID map){
    require(!__GXinBegin&&device&&object&&map>=GX_TEXMAP0&&map<=GX_TEXMAP7);
    const u8* data=0;for(unsigned int i=0;i<textureImages.size();++i)if(textureImages[i].object==object)data=(const u8*)textureImages[i].image;
    require(data!=0);uploadTexture(object,data,map);boundSources[map]=data;
}
extern "C" void GXInvalidateTexAll(void){
    require(device&&!__GXinBegin);
    // Native textures contain decoded copies of GC tiled RAM. Refresh every
    // bound copy from its original image, preserving the loaded descriptor.
    for(int unit=0;unit<8;++unit)if(boundValid[unit]){
        require(boundSources[unit]!=0);GXTexObj descriptor=boundDescriptors[unit];
        uploadTexture(&descriptor,boundSources[unit],(GXTexMapID)unit);
    }
}
namespace {void uploadTexture(GXTexObj* object,const u8* data,GXTexMapID map){
    GXProfileTimer timer(&gxProfile.uploadTicks);
    require(data!=0);unsigned int w=GXGetTexObjWidth(object),h=GXGetTexObjHeight(object),format=GXGetTexObjFmt(object);
    require(format<=GX_TF_RGBA8||(format>=GX_TF_C4&&format<=GX_TF_C14X2)||format==GX_TF_CMPR);
    const Palette* palette=0;if(format>=GX_TF_C4&&format<=GX_TF_C14X2){u32 name=object->dummy[6];require(name<20&&palettes[name].entries);palette=&palettes[name];}
    bool mip=(((const u8*)object)[31]&1)!=0;u32 mode=object->dummy[0],lod=object->dummy[1];
    unsigned int minLod=lod&255,maxLod=(lod>>8)&255;require(!mip||minLod<=maxLod);
    unsigned int levels=1,tw=w,th=h;while(mip&&(tw>1||th>1)&&levels<=(maxLod+15)/16){tw=tw>1?tw/2:1;th=th>1?th/2:1;++levels;}
    unsigned int wrapS=mode&3,wrapT=(mode>>2)&3,minFilter=(mode>>5)&7,aniso=(mode>>19)&3;
    require(wrapS<=2&&wrapT<=2&&(minFilter==0||minFilter==4||minFilter==1||minFilter==5||minFilter==2||minFilter==6)&&aniso<=2&&!(mode&(1u<<21)));
    unsigned sourceBytes=0,allocationBytes=0;tw=w;th=h;for(unsigned level=0;level<levels;++level){sourceBytes+=Melee360GxTextureBytes(tw,th,format);allocationBytes+=tw*th*4;tw=tw>1?tw/2:1;th=th>1?th/2:1;}require(sourceBytes!=0);
    IDirect3DTexture9* texture=findCachedTexture(w,h,format,levels,data,sourceBytes,palette);
    if(!texture){if(gxProfile.enabled)++gxProfile.uploads;
    if(mip){
        texture=(IDirect3DTexture9*)_aligned_malloc(sizeof(D3DTexture),16);require(texture!=0);UINT baseSize=0,mipSize=0;
        XGSetTextureHeaderEx(w,h,levels,0,D3DFMT_A8R8G8B8,0,XGHEADEREX_NONPACKED,0,0,0,texture,&baseSize,&mipSize);
        UINT baseAligned=(baseSize+4095)&~4095u;require(baseAligned>=baseSize&&mipSize<=0xffffffffu-baseAligned);
        allocationBytes=baseAligned+mipSize;
        void* allocation=XPhysicalAlloc(baseAligned+mipSize,MAXULONG_PTR,4096,PAGE_READWRITE);require(allocation!=0);memset(allocation,0,baseAligned+mipSize);
        XGOffsetBaseTextureAddress(texture,allocation,mipSize?(u8*)allocation+baseAligned:0);OwnedMipTexture owned={texture,allocation};ownedMipTextures.push_back(owned);
    }else require(SUCCEEDED(device->CreateTexture(w,h,levels,0,D3DFMT_LIN_A8R8G8B8,D3DPOOL_DEFAULT,&texture,0))&&texture);
    unsigned int offset=0;tw=w;th=h;
    for(unsigned int level=0;level<levels;++level){unsigned int bytes=Melee360GxTextureBytes(tw,th,format);std::vector<unsigned int> pixels(tw*th);
        require(bytes&&Melee360DecodeGxTexture(data+offset,bytes,tw,th,format,palette?&palette->data[0]:0,palette?palette->entries:0,palette?palette->format:0,&pixels[0],tw*th));
        D3DLOCKED_RECT lock;require(SUCCEEDED(texture->LockRect(level,&lock,0,0)));
        if(textureExpansionTesting&&mip){UINT baseData=0,mipData=0,baseSize=0,mipSize=0;XGGetTextureLayout(texture,&baseData,&baseSize,0,0,4096,&mipData,&mipSize,0,0,4096);char trace[256];sprintf_s(trace,sizeof(trace),"GX mip upload: level=%u decoded=%08x lock=%p pitch=%u base=%08x/%u mip=%08x/%u tail=%u\n",level,pixels[0],lock.pBits,lock.Pitch,baseData,baseSize,mipData,mipSize,XGGetMipTailLevelOffset(w,h,1,level,XGGetGpuFormat(D3DFMT_A8R8G8B8),TRUE,FALSE));Melee360Log(trace);}
        if(mip){UINT baseData=0,mipData=0,baseSize=0,mipSize=0;XGGetTextureLayout(texture,&baseData,&baseSize,0,0,4096,&mipData,&mipSize,0,0,4096);
            bool packed=XGIsPackedTexture(texture)!=0;UINT tailOffset=packed?XGGetMipTailLevelOffset(w,h,1,level,XGGetGpuFormat(D3DFMT_A8R8G8B8),TRUE,FALSE):0;
            require((UINT)lock.pBits>=tailOffset);u8* destination=(u8*)lock.pBits-tailOffset;
            require(((UINT)destination>=baseData&&(UINT)destination<baseData+baseSize)||(mipData&&(UINT)destination>=mipData&&(UINT)destination<mipData+mipSize));
            XGTileTextureLevel(w,h,level,XGGetGpuFormat(D3DFMT_A8R8G8B8),packed?0:XGTILE_NONPACKED,destination,0,&pixels[0],tw*4,0);}else for(unsigned int y=0;y<th;++y)memcpy((u8*)lock.pBits+y*lock.Pitch,&pixels[y*tw],tw*4);require(SUCCEEDED(texture->UnlockRect(level)));
        offset+=bytes;tw=tw>1?tw/2:1;th=th>1?th/2:1;
    }
    require(offset==sourceBytes);keepCachedTexture(texture,w,h,format,levels,data,sourceBytes,palette,allocationBytes);
    }
    releaseTexture(loadedTextures[map]);loadedTextures[map]=texture;
    static const DWORD address[]={D3DTADDRESS_CLAMP,D3DTADDRESS_WRAP,D3DTADDRESS_MIRROR};
    require(SUCCEEDED(device->SetSamplerState(map,D3DSAMP_ADDRESSU,address[wrapS]))&&SUCCEEDED(device->SetSamplerState(map,D3DSAMP_ADDRESSV,address[wrapT])));
    DWORD filter=(minFilter&4)?D3DTEXF_LINEAR:D3DTEXF_POINT,mipFilter=!mip||minFilter==0||minFilter==4?D3DTEXF_NONE:(minFilter&3)==1?D3DTEXF_POINT:D3DTEXF_LINEAR;
    float bias=(float)(s8)((mode>>9)&255)/32.f;DWORD biasBits;memcpy(&biasBits,&bias,4);
    require(SUCCEEDED(device->SetSamplerState(map,D3DSAMP_MINFILTER,aniso?D3DTEXF_ANISOTROPIC:filter))&&SUCCEEDED(device->SetSamplerState(map,D3DSAMP_MAGFILTER,(mode&16)?D3DTEXF_LINEAR:D3DTEXF_POINT))&&SUCCEEDED(device->SetSamplerState(map,D3DSAMP_MIPFILTER,mipFilter)));
    require(SUCCEEDED(device->SetSamplerState(map,D3DSAMP_MAXMIPLEVEL,0))&&SUCCEEDED(device->SetSamplerState(map,D3DSAMP_MINMIPLEVEL,levels-1))&&SUCCEEDED(device->SetSamplerState(map,D3DSAMP_MIPMAPLODBIAS,0))&&SUCCEEDED(device->SetSamplerState(map,D3DSAMP_MAXANISOTROPY,1u<<aniso)));
    textureLod[map][0]=(float)w;textureLod[map][1]=(float)h;textureLod[map][2]=mip?(float)minLod/16:0;textureLod[map][3]=mip?(float)maxLod/16:0;textureBias[map]=bias;
    static const bool paletteSnapshotsOnly=GetFileAttributesA("game:\\gx-palette-snapshots.flag")!=((DWORD)-1);
    if(!paletteSnapshotsOnly||palette){if(boundImages[map].empty()||data!=&boundImages[map][0])boundImages[map].assign(data,data+sourceBytes);}
    else boundImages[map].clear();
    boundDescriptors[map]=*object;boundValid[map]=true;
}}
extern "C" void GXSetAlphaCompare(GXCompare first,u8 reference0,GXAlphaOp operation,GXCompare second,u8 reference1){require(!__GXinBegin&&first>=GX_NEVER&&first<=GX_ALWAYS&&second>=GX_NEVER&&second<=GX_ALWAYS&&operation>=GX_AOP_AND&&operation<=GX_AOP_XNOR);alphaFirst[0]=(float)first;alphaFirst[1]=(float)reference0;alphaFirst[2]=(float)operation;alphaFirst[3]=1;alphaSecond[0]=(float)second;alphaSecond[1]=(float)reference1;}
extern "C" void GXClearVtxDesc(void){require(!__GXinBegin);waitingNormal=false;normalDescriptor=GX_NONE;memset(texMatrixIndexEnabled,0,sizeof(texMatrixIndexEnabled));matrixEnabled=matrixReady=false;positionEnabled=colorEnabled=texEnabled=false;posDescriptor=colorDescriptor=texDescriptor=GX_NONE;extraColor.descriptor=GX_NONE;for(int i=0;i<7;++i)extraTex[i].descriptor=GX_NONE;}
extern "C" void GXSetVtxDesc(GXAttr attr,GXAttrType type){if(attr>=GX_VA_TEX0MTXIDX&&attr<=GX_VA_TEX7MTXIDX){require(!__GXinBegin&&(type==GX_NONE||type==GX_DIRECT));texMatrixIndexEnabled[attr-GX_VA_TEX0MTXIDX]=type==GX_DIRECT;return;}if(attr==GX_VA_NRM||attr==GX_VA_NBT){require(!__GXinBegin&&type>=GX_NONE&&type<=GX_INDEX16);normalDescriptor=type;return;}if(extraDescriptor(attr,type))return;if(attr==GX_VA_PNMTXIDX){require(!__GXinBegin&&(type==GX_NONE||type==GX_DIRECT));matrixEnabled=type==GX_DIRECT;return;}require(!__GXinBegin&&(attr==GX_VA_POS||attr==GX_VA_CLR0||attr==GX_VA_TEX0)&&((type==GX_NONE||type==GX_DIRECT)||((attr==GX_VA_POS||attr==GX_VA_CLR0||attr==GX_VA_TEX0)&&(type==GX_INDEX8||type==GX_INDEX16))));if(attr==GX_VA_POS){posDescriptor=type;positionEnabled=type!=GX_NONE;}else if(attr==GX_VA_CLR0){colorDescriptor=type;colorEnabled=type!=GX_NONE;}else {texDescriptor=type;texEnabled=type!=GX_NONE;}}
extern "C" void GXSetArray(GXAttr attr,const void* base,u8 stride){if(!base||!stride||__GXinBegin){char msg[120];sprintf_s(msg,sizeof(msg),"GX array diagnostic: attr=%u stride=%u begin=%u base=%p\n",attr,stride,__GXinBegin,base);Melee360Log(msg);}if(attr==GX_VA_NRM||attr==GX_VA_NBT){require(!__GXinBegin&&base&&stride>=3);normalArray=(const u8*)base;normalStride=stride;return;}if(extraArray(attr,base,stride))return;require(!__GXinBegin&&(attr==GX_VA_POS||attr==GX_VA_CLR0||attr==GX_VA_TEX0)&&base&&stride);if(attr==GX_VA_POS){posArray=(const u8*)base;posStride=stride;}else if(attr==GX_VA_CLR0){colorArray=(const u8*)base;colorStride=stride;}else {texArray=(const u8*)base;texStride=stride;}}
extern "C" void GXSetVtxAttrFmt(GXVtxFmt format,GXAttr attr,GXCompCnt count,GXCompType type,u8 frac){require(!__GXinBegin&&format>=0&&format<=7);Format* dst=0;if(extraFormat(format,attr,count,type,frac))return;
    if(attr==GX_VA_NRM||attr==GX_VA_NBT){require((count==GX_NRM_XYZ||count==GX_NRM_NBT||count==GX_NRM_NBT3)&&(type==GX_F32||type==GX_S8||type==GX_S16));dst=&normalFormats[format];}
    else if(attr==GX_VA_POS){require((count==GX_POS_XY||count==GX_POS_XYZ)&&(type==GX_F32||type==GX_U8||type==GX_S8||type==GX_U16||type==GX_S16)&&frac<=31&&(type!=GX_F32||frac==0));dst=&posFormats[format];}
    else if(attr==GX_VA_CLR0){require((count==GX_CLR_RGB&&type>=GX_RGB565&&type<=GX_RGBX8)||(count==GX_CLR_RGBA&&type>=GX_RGBA4&&type<=GX_RGBA8));dst=&colorFormats[format];}
    else if(attr==GX_VA_TEX0){require(count==GX_TEX_ST&&(type==GX_F32||type==GX_U8||type==GX_S8||type==GX_U16||type==GX_S16)&&frac<=31&&(type!=GX_F32||frac==0));dst=&texFormats[format];}
    else require(false);dst->count=count;dst->type=type;dst->frac=frac;dst->set=true;
}
/* XDK may coalesce SDK GXEnd inline bodies compiled with different DEBUG flags. */
static void portEnd(){require(expected&&!primitiveActive&&vertices.size()==expected);__GXinBegin=GX_FALSE;}
#define GXEnd portEnd
extern "C" void GXBegin(GXPrimitive primitive,GXVtxFmt format,u16 count){particleFifo=false;beginCaller=_ReturnAddress();require(format>=0&&format<=7);require(normalDescriptor==GX_NONE||normalFormats[format].set);validateExtraInputs(format);require(!__GXinBegin&&device&&validPrimitive(primitive,count)&&format>=0&&format<=7&&positionEnabled&&posFormats[format].set&&(!colorEnabled||colorFormats[format].set)&&(!texEnabled||texFormats[format].set));activePrimitive=primitive;activeFormat=format;expected=count;vertices.clear();vertices.reserve(count);waitingNormal=waitingColor=waitingTex=false;matrixReady=false;memset(texMatrixIndexReady,0,sizeof(texMatrixIndexReady));primitiveActive=true;__GXinBegin=GX_TRUE;}
extern "C" void GXTexCoord1u8(u8 value){
 require(__GXinBegin&&primitiveActive&&!waitingNormal&&!waitingColor&&!waitingTex);
 if(matrixEnabled&&!matrixReady){require(value<=27&&value%3==0);vertexMatrix=value;matrixReady=true;return;}
 for(unsigned i=0;i<8;++i)if(texMatrixIndexEnabled[i]&&!texMatrixIndexReady[i]){require(value<=60&&value%3==0);texMatrixIndex[i]=value;texMatrixIndexReady[i]=true;return;}require(false);
}
static void emitPosition(float x,float y,float z){if(!__GXinBegin||!primitiveActive||waitingNormal||waitingColor||waitingTex){char msg[160];sprintf_s(msg,sizeof(msg),"GX position state: begin=%u active=%u normal=%u color=%u tex=%u count=%u/%u caller=%p texunit=%u tex1=%u\n",__GXinBegin,primitiveActive,waitingNormal,waitingColor,waitingTex,(unsigned)vertices.size(),expected,beginCaller,currentTex,extraTex[0].descriptor);Melee360Log(msg);}
require(__GXinBegin&&primitiveActive&&!waitingNormal&&!waitingColor&&!waitingTex);float p[3]={x,y,z};
require(!matrixEnabled||matrixReady);
for(unsigned i=0;i<8;++i)require(!texMatrixIndexEnabled[i]||texMatrixIndexReady[i]);
require((matrixEnabled?Melee360GXTransformPositionSlot(vertexMatrix/3,p,pending.clip):Melee360GXTransformPosition(p,pending.clip))!=0);
require(Melee360GXTransformEyePosition((matrixEnabled?vertexMatrix:Melee360GXCurrentMatrix())/3,p,eyePosition)!=0);eyeNormal[0]=eyeNormal[1]=0;eyeNormal[2]=1;waitingNormal=normalDescriptor!=GX_NONE;normalVectorIndex=0;memcpy(sourcePosition,p,12);sourceNormal[0]=sourceNormal[1]=0;sourceNormal[2]=1;pending.uv[0]=pending.uv[1]=0;pending.uv[2]=1;memset(pending.extraUV,0,sizeof(pending.extraUV));for(int q=0;q<7;++q)pending.extraUV[q][2]=1;for(int c=0;c<4;++c)pending.color[c]=pending.color1[c]=1;currentTex=nextTexture(0);currentColor=colorEnabled?0:1;waitingTex=currentTex<8;waitingColor=colorEnabled||extraColor.descriptor!=GX_NONE;if(!waitingNormal&&!waitingTex&&!waitingColor)finishVertex();}
extern "C" void GXPosition3f32(f32 x,f32 y,f32 z){require(posFormats[activeFormat].count==GX_POS_XYZ&&posFormats[activeFormat].type==GX_F32);emitPosition(x,y,z);}
/* GX writes are a FIFO scalar stream: the original shadow quad writes
   twelve XYZ floats through six GXPosition2f32 calls. */
static float positionScalars[3];static unsigned positionScalarCount;
extern "C" void GXPosition2f32(f32 x,f32 y){require(posFormats[activeFormat].type==GX_F32);if(posFormats[activeFormat].count==GX_POS_XY){emitPosition(x,y,0);return;}require(posFormats[activeFormat].count==GX_POS_XYZ);float input[2]={x,y};for(unsigned i=0;i<2;++i){positionScalars[positionScalarCount++]=input[i];if(positionScalarCount==3){positionScalarCount=0;emitPosition(positionScalars[0],positionScalars[1],positionScalars[2]);}}}
extern "C" void GXPosition2u8(u8 x,u8 y){require(posFormats[activeFormat].count==GX_POS_XY&&posFormats[activeFormat].type==GX_U8);float scale=1.f/(float)(1u<<posFormats[activeFormat].frac);emitPosition(x*scale,y*scale,0);}
extern "C" void GXColor4u8(u8 r,u8 g,u8 b,u8 a){require(__GXinBegin&&primitiveActive&&!waitingNormal&&waitingColor&&activeColorFormat().count==GX_CLR_RGBA);activeColorData()[0]=r/255.f;activeColorData()[1]=g/255.f;activeColorData()[2]=b/255.f;activeColorData()[3]=a/255.f;finishColorInput();}
extern "C" void GXColor3u8(u8 r,u8 g,u8 b){require(__GXinBegin&&primitiveActive&&!waitingNormal&&waitingColor&&activeColorFormat().count==GX_CLR_RGB);activeColorData()[0]=r/255.f;activeColorData()[1]=g/255.f;activeColorData()[2]=b/255.f;activeColorData()[3]=1;finishColorInput();}
extern "C" void GXColor1u16(u16 value){require(__GXinBegin&&primitiveActive&&!waitingNormal&&waitingColor&&activeColorFormat().count==GX_CLR_RGB&&activeColorFormat().type==GX_RGB565);unsigned int r=(value>>11)&31,g=(value>>5)&63,b=value&31;activeColorData()[0]=((r<<3)|(r>>2))/255.f;activeColorData()[1]=((g<<2)|(g>>4))/255.f;activeColorData()[2]=((b<<3)|(b>>2))/255.f;activeColorData()[3]=1;finishColorInput();}
static void packedColor(const u8* p){GXCompType type=activeColorFormat().type;
 if(type==GX_RGB565){GXColor1u16((u16)((p[0]<<8)|p[1]));return;}
 if(type==GX_RGB8||type==GX_RGBX8){GXColor3u8(p[0],p[1],p[2]);return;}
 if(type==GX_RGBA4){unsigned v=(p[0]<<8)|p[1];GXColor4u8(((v>>12)&15)*17,((v>>8)&15)*17,((v>>4)&15)*17,(v&15)*17);return;}
 if(type==GX_RGBA6){unsigned v=(p[0]<<16)|(p[1]<<8)|p[2],c[4];for(unsigned i=0;i<4;++i){unsigned n=(v>>(18-6*i))&63;c[i]=(n<<2)|(n>>4);}GXColor4u8((u8)c[0],(u8)c[1],(u8)c[2],(u8)c[3]);return;}
 require(type==GX_RGBA8);GXColor4u8(p[0],p[1],p[2],p[3]);
}
static void indexedColor(unsigned int index,GXAttrType descriptor){require(__GXinBegin&&primitiveActive&&!waitingNormal&&waitingColor&&activeColorDescriptor()==descriptor&&activeColorArray());unsigned width=colorEncodedBytes(activeColorFormat().type);require(activeColorStride()>=width&&(unsigned int)activeColorArray()<=0xffffffffu-index*activeColorStride()-width);packedColor(activeColorArray()+index*activeColorStride());}
extern "C" void GXColor1x8(u8 index){indexedColor(index,GX_INDEX8);}
extern "C" void GXColor1x16(u16 index){indexedColor(index,GX_INDEX16);}
static void emitTexcoord(float u,float v){require(__GXinBegin&&primitiveActive&&!waitingNormal&&!waitingColor&&waitingTex);activeTexData()[0]=u;activeTexData()[1]=v;finishTextureInput();}
extern "C" void GXTexCoord2f32(f32 u,f32 v){require(activeTexFormat().type==GX_F32);emitTexcoord(u,v);}
extern "C" void GXTexCoord2u8(u8 u,u8 v){require(__GXinBegin&&primitiveActive&&!waitingNormal&&!waitingColor&&waitingTex&&activeTexFormat().type==GX_U8);float scale=1.f/(float)(1u<<activeTexFormat().frac);activeTexData()[0]=u*scale;activeTexData()[1]=v*scale;finishTextureInput();}
static void indexedTex(unsigned int index,GXAttrType descriptor){require(__GXinBegin&&primitiveActive&&!waitingNormal&&!waitingColor&&waitingTex&&activeTexDescriptor()==descriptor&&activeTexArray());const Format f=activeTexFormat();unsigned scalar=positionScalarSize(f.type),width=scalar*2;require(activeTexStride()>=width&&(unsigned int)activeTexArray()<=0xffffffffu-index*activeTexStride()-width);const u8* p=activeTexArray()+index*activeTexStride();emitTexcoord(decodePositionScalar(p,f.type,f.frac),decodePositionScalar(p+scalar,f.type,f.frac));}
extern "C" void GXTexCoord1x8(u8 index){indexedTex(index,GX_INDEX8);}
extern "C" void GXTexCoord1x16(u16 index){indexedTex(index,GX_INDEX16);}
#include "gx_lighting_api.inc"
#include "gx_texgen_api.inc"
#include "gx_display_list.inc"
/* The original particle renderer writes the FIFO directly and omits GXEnd.
   End its packet after the declared vertex count, just as the GPU FIFO does. */
extern "C" void Melee360ParticleGXBegin(GXPrimitive primitive,GXVtxFmt format,u16 count){GXBegin(primitive,format,count);particleFifo=true;}
extern "C" void Melee360GXRawWriteU8(u8 value){
 require(__GXinBegin&&primitiveActive);
 if(waitingTex){require(activeTexDescriptor()==GX_INDEX8);GXTexCoord1x8(value);}else GXTexCoord1u8(value);
}
extern "C" void Melee360GXRawWriteF32(float value){
 static float scalars[3];static unsigned count;require(__GXinBegin&&primitiveActive&&!waitingColor);
 unsigned components=waitingNormal?3:waitingTex?2:posFormats[activeFormat].count==GX_POS_XYZ?3:2;
 scalars[count++]=value;if(count!=components)return;count=0;
 if(waitingNormal)GXNormal3f32(scalars[0],scalars[1],scalars[2]);else if(waitingTex)GXTexCoord2f32(scalars[0],scalars[1]);else emitPosition(scalars[0],scalars[1],components==3?scalars[2]:0);
}
extern "C" int Melee360GXDirectProbe(void){
    float m[3][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0}},p[4][4]={{1,0,0,0},{0,1,0,0},{0,0,-.1f,-.2f},{0,0,0,1}};
    GXLoadPosMtxImm(m,0);GXSetCurrentMtx(0);GXSetProjection(p,GX_ORTHOGRAPHIC);GXClearVtxDesc();GXSetVtxDesc(GX_VA_POS,GX_DIRECT);GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGBA,GX_RGBA8,0);
    device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);GXSetZMode(0,GX_ALWAYS,0);GXSetBlendMode(GX_BM_NONE,GX_BL_ONE,GX_BL_ZERO,GX_LO_COPY);
    GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);GXPosition3f32(-.2f,-.2f,-1);GXColor4u8(255,0,0,255);GXPosition3f32(.2f,-.2f,-1);GXColor4u8(0,255,0,255);GXPosition3f32(0,.2f,-1);GXColor4u8(0,0,255,255);GXEnd();
    GXSetLineWidth(12,GX_TO_ZERO);GXSetPointSize(12,GX_TO_ZERO);
    const GXPrimitive rasterTypes[]={GX_POINTS,GX_LINES,GX_LINESTRIP};
    for(int test=0;test<3;++test){unsigned count=test==2?3:2;u8 display[3+3*16]={0};display[0]=(u8)rasterTypes[test];display[2]=(u8)count;
        for(unsigned v=0;v<count;++v){float position[3]={-.2f+v*.2f,-.2f+v*.2f,-1};memcpy(display+3+v*16,position,12);memset(display+3+v*16+12,255,4);}
        GXCallDisplayList(display,3+count*16);require(vertices.size()==count&&triangleVertices.size()==(test==1?6:12));
    }
    GXSetLineWidth(6,GX_TO_ZERO);GXSetPointSize(6,GX_TO_ZERO);Melee360Log("GX raster display lists: original byte order, points/lines/strip decoded and submitted\n");
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XY,GX_U8,1);GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);GXPosition2u8(0,0);GXColor4u8(255,0,0,255);GXPosition2u8(1,0);GXColor4u8(0,255,0,255);GXPosition2u8(0,1);GXColor4u8(0,0,255,255);GXEnd();
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGB565,0);GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);GXPosition2u8(0,0);GXColor1u16(0xf800);GXPosition2u8(1,0);GXColor1u16(0x07e0);GXPosition2u8(0,1);GXColor1u16(0x001f);GXEnd();require(vertices[0].color[0]==1&&vertices[0].color[1]==0&&vertices[1].color[1]==1&&vertices[2].color[2]==1);Melee360Log("GX color: packed RGB565 red/green/blue GPU probe passed\n");GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGBA,GX_RGBA8,0);
    const u8 color8[18]={255,0,0,99,99,99,0,255,0,99,99,99,0,0,255,99,99,99};GXSetArray(GX_VA_CLR0,color8,6);GXSetVtxDesc(GX_VA_CLR0,GX_INDEX8);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGB8,0);GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);for(int i=0;i<3;++i){GXPosition2u8((u8)i,0);GXColor1x8((u8)i);}GXEnd();require(vertices[0].color[0]==1&&vertices[1].color[1]==1&&vertices[2].color[2]==1);
    u8 color16[1036]={0};color16[1024]=0xf8;color16[1028]=7;color16[1029]=0xe0;color16[1033]=0x1f;GXSetArray(GX_VA_CLR0,color16,4);GXSetVtxDesc(GX_VA_CLR0,GX_INDEX16);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGB565,0);GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);for(int i=0;i<3;++i){GXPosition2u8((u8)i,0);GXColor1x16((u16)(i+256));}GXEnd();require(vertices[0].color[0]==1&&vertices[1].color[1]==1&&vertices[2].color[2]==1);GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGBA,GX_RGBA8,0);Melee360Log("GX indexed color: INDEX8 RGB8 and INDEX16 RGB565 stride/byte order probes passed\n");
    const u8 rgba[12]={255,0,0,128,0,255,0,255,0,0,255,0};GXSetArray(GX_VA_CLR0,rgba,4);GXSetVtxDesc(GX_VA_CLR0,GX_INDEX8);GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);for(int i=0;i<3;++i){GXPosition2u8((u8)i,0);GXColor1x8((u8)i);}GXEnd();require(vertices[0].color[3]==128/255.f&&vertices[1].color[3]==1&&vertices[2].color[3]==0);GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);colorArray=0;colorStride=0;
    const GXPrimitive topologies[3]={GX_QUADS,GX_TRIANGLESTRIP,GX_TRIANGLEFAN};for(int t=0;t<3;++t){GXBegin(topologies[t],GX_VTXFMT0,4);for(int j=0;j<4;++j){GXPosition2u8((u8)j,(u8)(j&1));GXColor4u8(255,255,255,255);}GXEnd();require(triangleVertices.size()==6);if(t==0)require(triangleVertices[3].clip[0]==0&&triangleVertices[4].clip[0]==1&&triangleVertices[5].clip[0]==1.5f);if(t==1)require(triangleVertices[3].clip[0]==1&&triangleVertices[4].clip[0]==.5f&&triangleVertices[5].clip[0]==1.5f);if(t==2)require(triangleVertices[3].clip[0]==0&&triangleVertices[4].clip[0]==1&&triangleVertices[5].clip[0]==1.5f);}Melee360Log("GX topology: quads/strip/fan winding and Xbox draws passed\n");
    GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_TEX_ST,GX_U8,1);GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);GXPosition2u8(0,0);GXColor4u8(255,255,255,255);GXTexCoord2u8(0,0);GXPosition2u8(1,0);GXColor4u8(255,255,255,255);GXTexCoord2u8(2,0);GXPosition2u8(0,1);GXColor4u8(255,255,255,255);GXTexCoord2u8(0,2);GXEnd();
    require(vertices[1].uv[0]==1&&vertices[2].uv[1]==1);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_TEX_ST,GX_F32,0);GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);GXPosition2u8(0,0);GXColor4u8(255,255,255,255);GXTexCoord2f32(0,0);GXPosition2u8(1,0);GXColor4u8(255,255,255,255);GXTexCoord2f32(1,0);GXPosition2u8(0,1);GXColor4u8(255,255,255,255);GXTexCoord2f32(0,1);GXEnd();
    const u8 uv8[12]={0,0,99,99,2,0,99,99,0,2,99,99};GXSetArray(GX_VA_TEX0,uv8,4);GXSetVtxDesc(GX_VA_TEX0,GX_INDEX8);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_TEX_ST,GX_U8,1);GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);for(int i=0;i<3;++i){GXPosition2u8(i==1?1:0,i==2?1:0);GXColor4u8(255,255,255,255);GXTexCoord1x8((u8)i);}GXEnd();require(vertices[1].uv[0]==1&&vertices[2].uv[1]==1);
    float uv16[777]={0};uv16[257*3]=1;uv16[258*3+1]=1;GXSetArray(GX_VA_TEX0,uv16,12);GXSetVtxDesc(GX_VA_TEX0,GX_INDEX16);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_TEX_ST,GX_F32,0);GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);for(int i=0;i<3;++i){GXPosition2u8(i==1?1:0,i==2?1:0);GXColor4u8(255,255,255,255);GXTexCoord1x16((u16)(i+256));}GXEnd();texArray=0;texStride=0;GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);Melee360Log("GX indexed UV: INDEX8 U8 scale and INDEX16 F32 high-index/stride probes passed\n");
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_TEX_ST,GX_U8,1);u8 dl[32]={0x90,0,3,0,0,255,0,0,255,0,0,1,0,0,255,0,255,2,0,0,1,0,0,255,255,0,2};GXCallDisplayList(dl,sizeof(dl));require(vertices.size()==3&&vertices[0].color[0]==1&&vertices[1].color[1]==1&&vertices[2].color[2]==1);Melee360Log("GX display list: direct primitive decoding/NOP padding and GPU draw passed\n");
    GXSetArray(GX_VA_CLR0,color16,4);GXSetArray(GX_VA_TEX0,uv8,4);GXSetVtxDesc(GX_VA_CLR0,GX_INDEX16);GXSetVtxDesc(GX_VA_TEX0,GX_INDEX8);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGB565,0);u8 indexedDl[32]={0x90,0,3,0,0,1,0,0,1,0,1,1,1,0,1,1,2,2};GXCallDisplayList(indexedDl,sizeof(indexedDl));require(vertices[0].color[0]==1&&vertices[1].color[1]==1&&vertices[2].color[2]==1&&vertices[1].uv[0]==1&&vertices[2].uv[1]==1);colorArray=texArray=0;colorStride=texStride=0;GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGBA,GX_RGBA8,0);Melee360Log("GX display list: indexed color/UV high-index decoding passed\n");
    float positions[1036]={0};positions[256*4+2]=positions[257*4+2]=positions[258*4+2]=-1;positions[257*4]=.5f;positions[258*4+1]=.5f;GXSetArray(GX_VA_POS,positions,16);GXSetArray(GX_VA_CLR0,color16,4);GXSetArray(GX_VA_TEX0,uv8,4);GXSetVtxDesc(GX_VA_POS,GX_INDEX16);GXSetVtxDesc(GX_VA_CLR0,GX_INDEX16);GXSetVtxDesc(GX_VA_TEX0,GX_INDEX8);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGB,GX_RGB565,0);u8 positionDl[32]={0x90,0,3,1,0,1,0,0,1,1,1,1,1,1,2,1,2,2};GXCallDisplayList(positionDl,sizeof(positionDl));require(vertices[1].clip[0]==.5f&&vertices[2].clip[1]==.5f&&vertices[1].uv[0]==1&&vertices[2].uv[1]==1);
    const u8 position8[12]={0,0,99,99,1,0,99,99,0,1,99,99};GXSetArray(GX_VA_POS,position8,4);GXSetVtxDesc(GX_VA_POS,GX_INDEX8);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XY,GX_U8,1);u8 position8Dl[32]={0x90,0,3,0,1,0,0,1,1,1,1,2,1,2,2};GXCallDisplayList(position8Dl,sizeof(position8Dl));require(vertices[1].clip[0]==.5f&&vertices[2].clip[1]==.5f);posArray=colorArray=texArray=0;posStride=colorStride=texStride=0;GXSetVtxDesc(GX_VA_POS,GX_DIRECT);GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGBA,GX_RGBA8,0);Melee360Log("GX display list: INDEX16 F32 positions and INDEX8 U8 positions passed\n");
    // Big-endian signed positions: negative coordinates and fractional scale.
    GXSetVtxDesc(GX_VA_CLR0,GX_NONE);GXSetVtxDesc(GX_VA_TEX0,GX_NONE);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_S16,2);
    u8 signedDl[32]={0x90,0,3,0xff,0xfe,0,0,0xff,0xfc,0,2,0,0,0xff,0xfc,0,0,0,2,0xff,0xfc};
    GXCallDisplayList(signedDl,sizeof(signedDl));require(vertices[0].clip[0]==-.5f&&vertices[1].clip[0]==.5f&&vertices[2].clip[1]==.5f);
    u8 signedArray[2072]={0};memcpy(signedArray+256*8,signedDl+3,6);memcpy(signedArray+257*8,signedDl+9,6);memcpy(signedArray+258*8,signedDl+15,6);
    GXSetArray(GX_VA_POS,signedArray,8);GXSetVtxDesc(GX_VA_POS,GX_INDEX16);u8 signedIndexed[32]={0x90,0,3,1,0,1,1,1,2};
    GXCallDisplayList(signedIndexed,sizeof(signedIndexed));require(vertices[0].clip[0]==-.5f&&vertices[1].clip[0]==.5f&&vertices[2].clip[1]==.5f);
    GXSetVtxDesc(GX_VA_POS,GX_DIRECT);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XY,GX_S8,1);
    u8 signed8[32]={0x90,0,3,0xff,0,1,0,0,1};GXCallDisplayList(signed8,sizeof(signed8));require(vertices[0].clip[0]==-.5f&&vertices[1].clip[0]==.5f);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XY,GX_U16,9);u8 unsigned16[32]={0x90,0,3,0,0,0,0,1,0,0,0,0,0,1,0};GXCallDisplayList(unsigned16,sizeof(unsigned16));require(vertices[1].clip[0]==.5f&&vertices[2].clip[1]==.5f);
    Melee360Log("GX integer positions: S16 direct/indexed negative fractional, S8 and U16 probes passed\n");
    posArray=0;posStride=0;GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XY,GX_U8,1);GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);GXCallDisplayList(dl,sizeof(dl));
    GXSetVtxDesc(GX_VA_CLR0,GX_NONE);GXSetVtxDesc(GX_VA_TEX0,GX_NONE);GXSetVtxDesc(GX_VA_PNMTXIDX,GX_DIRECT);
    float translated[3][4]={{1,0,0,1},{0,1,0,0},{0,0,1,0}};GXLoadPosMtxImm(translated,27);
    GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);GXTexCoord1u8(0);GXPosition2u8(0,0);GXTexCoord1u8(27);GXPosition2u8(0,0);GXTexCoord1u8(0);GXPosition2u8(0,1);GXEnd();require(vertices[0].clip[0]==0&&vertices[1].clip[0]==1&&vertices[2].clip[0]==0);
    u8 matrixDl[32]={0x90,0,3,0,0,0,27,0,0,0,0,1};GXCallDisplayList(matrixDl,sizeof(matrixDl));require(vertices[0].clip[0]==0&&vertices[1].clip[0]==1&&vertices[2].clip[1]==.5f);
    GXSetVtxDesc(GX_VA_PNMTXIDX,GX_NONE);GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);GXPosition2u8(0,0);GXPosition2u8(1,0);GXPosition2u8(0,1);GXEnd();require(vertices[1].clip[0]==.5f);
    Melee360Log("GX matrix index: per-vertex slots 0/27, display list byte order and current-matrix preservation passed\n");
    GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);GXCallDisplayList(dl,sizeof(dl));
    char copyReport[128];sprintf_s(copyReport,sizeof(copyReport),"GX direct optimization: %I64u redundant vertex-copy bytes avoided in probes\n",avoidedCopyBytes);Melee360Log(copyReport);
    char message[128];sprintf_s(message,sizeof(message),"GX direct probe: inBegin=%u active=%u vertices=%u\n",(unsigned int)__GXinBegin,(unsigned int)primitiveActive,(unsigned int)vertices.size());Melee360Log(message);
    return !__GXinBegin&&!primitiveActive&&vertices.size()==3&&vertices[1].clip[0]==.5f&&vertices[2].clip[1]==.5f&&vertices[1].uv[0]==1&&vertices[2].uv[1]==1;
}

extern "C" int Melee360GXAlphaProbe(void){
    float savedFirst[4],savedSecond[4];memcpy(savedFirst,alphaFirst,16);memcpy(savedSecond,alphaSecond,16);
    float m[3][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0}},p[4][4]={{1,0,0,0},{0,1,0,0},{0,0,-.1f,-.2f},{0,0,0,1}};
    GXLoadPosMtxImm(m,0);GXSetCurrentMtx(0);GXSetProjection(p,GX_ORTHOGRAPHIC);GXClearVtxDesc();GXSetVtxDesc(GX_VA_POS,GX_DIRECT);GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGBA,GX_RGBA8,0);
    IDirect3DQuery9* query=0;require(SUCCEEDED(device->CreateQuery(D3DQUERYTYPE_OCCLUSION,&query))&&query);bool ok=true;
    for(int test=0;test<40;++test){int comparison=test<24?test/3:((test-24)/4&2)?GX_ALWAYS:GX_NEVER;int alpha=test<24?127+test%3:128;int operation=test<24?GX_AOP_AND:(test-24)%4;int second=test<24?GX_ALWAYS:((test-24)/4&1)?GX_ALWAYS:GX_NEVER;
        GXSetAlphaCompare((GXCompare)comparison,128,(GXAlphaOp)operation,(GXCompare)second,128);
        require(SUCCEEDED(query->Issue(D3DISSUE_BEGIN)));GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);GXPosition3f32(-.2f,-.2f,-1);GXColor4u8(255,255,255,(u8)alpha);GXPosition3f32(.2f,-.2f,-1);GXColor4u8(255,255,255,(u8)alpha);GXPosition3f32(0,.2f,-1);GXColor4u8(255,255,255,(u8)alpha);GXEnd();require(SUCCEEDED(query->Issue(D3DISSUE_END)));
        device->BlockUntilIdle();DWORD pixels=0;HRESULT result;unsigned int attempt=0;do{result=query->GetData(&pixels,sizeof(pixels),D3DGETDATA_FLUSH);if(result==S_FALSE)Sleep(1);}while(result==S_FALSE&&++attempt<10000);
        bool a=comparison==GX_NEVER?false:comparison==GX_LESS?alpha<128:comparison==GX_EQUAL?alpha==128:comparison==GX_LEQUAL?alpha<=128:comparison==GX_GREATER?alpha>128:comparison==GX_NEQUAL?alpha!=128:comparison==GX_GEQUAL?alpha>=128:true;
        bool b=second==GX_ALWAYS;bool expected=operation==GX_AOP_AND?(a&&b):operation==GX_AOP_OR?(a||b):operation==GX_AOP_XOR?(a!=b):(a==b);
        if(result!=S_OK||(pixels>0)!=expected){char message[180];sprintf_s(message,sizeof(message),"GX alpha probe FAILED: test=%d pixels=%u expected=%d HRESULT=%08x\n",test,pixels,expected?1:0,result);Melee360Log(message);ok=false;break;}
    }
    query->Release();memcpy(alphaFirst,savedFirst,16);memcpy(alphaSecond,savedSecond,16);if(ok)Melee360Log("GX alpha compare: 8 comparisons at reference boundaries and AND/OR/XOR/XNOR GPU occlusion probes passed\n");return ok;
}

extern "C" int Melee360GXTextureBindingProbe(void){
    float savedFirst[4],savedSecond[4];memcpy(savedFirst,alphaFirst,16);memcpy(savedSecond,alphaSecond,16);
    static const D3DSAMPLERSTATETYPE states[]={D3DSAMP_ADDRESSU,D3DSAMP_ADDRESSV,D3DSAMP_MINFILTER,D3DSAMP_MAGFILTER,D3DSAMP_MIPFILTER,D3DSAMP_MAXMIPLEVEL,D3DSAMP_MINMIPLEVEL,D3DSAMP_MIPMAPLODBIAS,D3DSAMP_MAXANISOTROPY};DWORD saved[9];
    for(int i=0;i<9;++i)device->GetSamplerState(0,states[i],&saved[i]);
    float savedLod[4],savedBias=textureBias[0];memcpy(savedLod,textureLod[0],16);GXTexObj oldDesc=boundDescriptors[0];std::vector<u8> oldImage=boundImages[0];bool oldValid=boundValid[0];const u8* oldSource=boundSources[0];
    IDirect3DTexture9* oldTexture=loadedTextures[0];loadedTextures[0]=0;GXTexObj object;
    __declspec(align(32)) static u8 tiled[64];IDirect3DQuery9* query=0;require(SUCCEEDED(device->CreateQuery(D3DQUERYTYPE_OCCLUSION,&query))&&query);
    float m[3][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0}},p[4][4]={{1,0,0,0},{0,1,0,0},{0,0,-.1f,-.2f},{0,0,0,1}};
    GXLoadPosMtxImm(m,0);GXSetCurrentMtx(0);GXSetProjection(p,GX_ORTHOGRAPHIC);GXClearVtxDesc();GXSetVtxDesc(GX_VA_POS,GX_DIRECT);GXSetVtxDesc(GX_VA_CLR0,GX_DIRECT);GXSetVtxDesc(GX_VA_TEX0,GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_POS,GX_POS_XYZ,GX_F32,0);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_CLR0,GX_CLR_RGBA,GX_RGBA8,0);GXSetVtxAttrFmt(GX_VTXFMT0,GX_VA_TEX0,GX_TEX_ST,GX_F32,0);
    GXSetAlphaCompare(GX_GEQUAL,128,GX_AOP_AND,GX_ALWAYS,0);GXSetZMode(0,GX_ALWAYS,0);bool ok=true;
    for(int wrap=0;wrap<3;++wrap)for(int opaque=0;opaque<2;++opaque){
        memset(tiled,255,64);for(int i=0;i<16;++i)tiled[i*2]=(u8)(opaque?255:0);
        GXInitTexObj(&object,tiled,4,4,GX_TF_RGBA8,(GXTexWrapMode)wrap,(GXTexWrapMode)wrap,0);GXLoadTexObj(&object,GX_TEXMAP0);
        DWORD actual;static const DWORD modes[]={D3DTADDRESS_CLAMP,D3DTADDRESS_WRAP,D3DTADDRESS_MIRROR};device->GetSamplerState(0,D3DSAMP_ADDRESSU,&actual);ok=ok&&actual==modes[wrap];device->GetSamplerState(0,D3DSAMP_ADDRESSV,&actual);ok=ok&&actual==modes[wrap];
        require(SUCCEEDED(query->Issue(D3DISSUE_BEGIN)));GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);
        GXPosition3f32(-.2f,-.2f,-1);GXColor4u8(255,255,255,255);GXTexCoord2f32(.5f,.5f);
        GXPosition3f32(.2f,-.2f,-1);GXColor4u8(255,255,255,255);GXTexCoord2f32(.5f,.5f);
        GXPosition3f32(0,.2f,-1);GXColor4u8(255,255,255,255);GXTexCoord2f32(.5f,.5f);GXEnd();require(SUCCEEDED(query->Issue(D3DISSUE_END)));
        device->BlockUntilIdle();DWORD pixels=0;HRESULT result;unsigned int attempt=0;do{result=query->GetData(&pixels,sizeof(pixels),D3DGETDATA_FLUSH);if(result==S_FALSE)Sleep(1);}while(result==S_FALSE&&++attempt<10000);
        ok=ok&&result==S_OK&&(pixels>0)==(opaque!=0);
    }
    query->Release();releaseTexture(loadedTextures[0]);loadedTextures[0]=oldTexture;memcpy(textureLod[0],savedLod,16);textureBias[0]=savedBias;boundDescriptors[0]=oldDesc;boundImages[0]=oldImage;boundValid[0]=oldValid;boundSources[0]=oldSource;
    for(unsigned int i=0;i<textureImages.size();++i)if(textureImages[i].object==&object){textureImages.erase(textureImages.begin()+i);break;}
    for(int i=0;i<9;++i)device->SetSamplerState(0,states[i],saved[i]);memcpy(alphaFirst,savedFirst,16);memcpy(alphaSecond,savedSecond,16);
    return ok;
}

extern "C" int Melee360GXTextureExpansionProbe(void){
    require(device&&!__GXinBegin);TevState savedTev=tev;initializeTev();GXSetTevOp(GX_TEVSTAGE0,GX_MODULATE);textureExpansionTesting=true;float first[4],second[4];memcpy(first,alphaFirst,16);memcpy(second,alphaSecond,16);unsigned int oldRoute=selectedTexture;float oldLod[8][4],oldBias[8];memcpy(oldLod,textureLod,sizeof(oldLod));memcpy(oldBias,textureBias,sizeof(oldBias));
    IDirect3DTexture9* oldTextures[8];GXTexObj oldDescriptors[8];std::vector<u8> oldImages[8];bool oldValid[8];const u8* oldSources[8];
    static const D3DSAMPLERSTATETYPE states[]={D3DSAMP_ADDRESSU,D3DSAMP_ADDRESSV,D3DSAMP_MINFILTER,D3DSAMP_MAGFILTER,D3DSAMP_MIPFILTER,D3DSAMP_MAXMIPLEVEL,D3DSAMP_MINMIPLEVEL,D3DSAMP_MIPMAPLODBIAS,D3DSAMP_MAXANISOTROPY};DWORD saved[8][9];
    for(int unit=0;unit<8;++unit){oldTextures[unit]=loadedTextures[unit];loadedTextures[unit]=0;oldDescriptors[unit]=boundDescriptors[unit];oldImages[unit]=boundImages[unit];oldValid[unit]=boundValid[unit];oldSources[unit]=boundSources[unit];boundValid[unit]=false;for(int i=0;i<9;++i)device->GetSamplerState(unit,states[i],&saved[unit][i]);}
    Palette oldPalette=palettes[19];GXTexObj object;GXTlutObj lut;
    __declspec(align(32)) static u8 data[512],palette[1024];IDirect3DQuery9* query=0;require(SUCCEEDED(device->CreateQuery(D3DQUERYTYPE_OCCLUSION,&query))&&query);
    GXSetAlphaCompare(GX_GEQUAL,128,GX_AOP_AND,GX_ALWAYS,0);bool ok=true;unsigned int draws=0;
    // Eight independent bindings, followed by routing without loading again.
    for(int unit=0;unit<8;++unit){memset(data,255,64);for(int i=0;i<16;++i)data[i*2]=(unit&1)?255:0;GXInitTexObj(&object,data,4,4,GX_TF_RGBA8,GX_CLAMP,GX_CLAMP,0);GXLoadTexObj(&object,(GXTexMapID)unit);}
    for(int test=0;test<45;++test){int expected=0;unsigned int slot=0;
        if(test<8){slot=test;expected=test&1;}
        else if(test<17){int kind=(test-8)/3,pf=(test-8)%3;memset(data,0,sizeof(data));unsigned int index=kind==2?257:1;
            if(kind==0)memset(data,0x11,32);else if(kind==1)memset(data,1,32);else for(int i=0;i<16;++i){data[i*2]=1;data[i*2+1]=1;}
            memset(palette,0,sizeof(palette));unsigned int value=pf==0?0xffff:pf==1?0xf800:0x0fff;palette[index*2]=(u8)(value>>8);palette[index*2+1]=(u8)value;
            GXInitTlutObj(&lut,palette,(GXTlutFmt)pf,(u16)(index+1));GXLoadTlut(&lut,GX_BIGTLUT3);
            GXInitTexObjCI(&object,data,kind==0?8:4,kind==0?8:4,(GXTexFmt)(GX_TF_C4+kind),GX_CLAMP,GX_CLAMP,0,GX_BIGTLUT3);GXLoadTexObj(&object,GX_TEXMAP0);expected=pf!=2;
        }else if(test<21){int level=test-17;unsigned int offset=0;
            for(int l=0;l<4;++l){unsigned int bytes=l==0?128:32;for(unsigned int i=0;i<bytes;i+=2){data[offset+i]=(l&1)?0xff:0x0f;data[offset+i+1]=0xff;}offset+=bytes;}
            GXInitTexObj(&object,data,8,8,GX_TF_RGB5A3,GX_CLAMP,GX_CLAMP,1);GXInitTexObjLOD(&object,GX_NEAR_MIP_NEAR,GX_NEAR,(float)level,(float)level,0,0,1,GX_ANISO_1);GXLoadTexObj(&object,GX_TEXMAP0);ok=ok&&loadedTextures[0]->GetLevelCount()==(unsigned int)level+1;expected=level&1;
        }else if(test<23){ // Reload TLUT changes the already-bound CI texture.
            memset(data,1,32);memset(palette,0,sizeof(palette));palette[2]=test==21?0xff:0;palette[3]=0xff;
            GXInitTlutObj(&lut,palette,GX_TL_IA8,2);GXLoadTlut(&lut,GX_BIGTLUT3);
            if(test==21){GXInitTexObjCI(&object,data,4,4,GX_TF_C8,GX_CLAMP,GX_CLAMP,0,GX_BIGTLUT3);GXLoadTexObj(&object,GX_TEXMAP0);}expected=test==21;
        }else if(test<25){ // Sampler conversions: trilinear/bias and anisotropy state.
            memset(data,255,sizeof(data));GXInitTexObj(&object,data,8,8,GX_TF_RGB5A3,GX_CLAMP,GX_CLAMP,1);
            GXInitTexObjLOD(&object,test==23?GX_LIN_MIP_LIN:GX_NEAR_MIP_LIN,GX_LINEAR,0,3,-.5f,0,1,test==23?GX_ANISO_1:GX_ANISO_4);GXLoadTexObj(&object,GX_TEXMAP0);
            DWORD actual;device->GetSamplerState(0,D3DSAMP_MIPFILTER,&actual);ok=ok&&actual==D3DTEXF_LINEAR;device->GetSamplerState(0,D3DSAMP_MIPMAPLODBIAS,&actual);float bias;memcpy(&bias,&actual,4);ok=ok&&bias==0&&textureBias[0]==-.5f;expected=1;
        }else if(test<27){
            memset(data,255,sizeof(data));for(int i=0;i<128;i+=2)data[i]=0x0f;
            GXInitTexObj(&object,data,8,8,GX_TF_RGB5A3,GX_CLAMP,GX_CLAMP,1);float lod=test==25?.5f:.25f;
            GXInitTexObjLOD(&object,GX_LIN_MIP_LIN,GX_LINEAR,lod,lod,0,0,1,GX_ANISO_1);GXLoadTexObj(&object,GX_TEXMAP0);expected=test==25;
        }else if(test<29){
            memset(data,0,32);memset(data+32,0x11,32);memset(palette,0,sizeof(palette));palette[2]=test==27?255:0;palette[3]=255;
            GXInitTlutObj(&lut,palette,GX_TL_IA8,2);GXLoadTlut(&lut,GX_BIGTLUT3);
            if(test==27){GXInitTexObjCI(&object,data,8,8,GX_TF_C4,GX_CLAMP,GX_CLAMP,1,GX_BIGTLUT3);GXInitTexObjLOD(&object,GX_NEAR_MIP_NEAR,GX_NEAR,1,1,0,0,1,GX_ANISO_1);GXLoadTexObj(&object,GX_TEXMAP0);}expected=test==27;
        }
        if(test>=29&&test<31){
            memset(data,255,sizeof(data));for(int i=0;i<32;i+=2)data[128+i]=0;
            GXInitTexObj(&object,data,4,4,GX_TF_RGB5A3,GX_CLAMP,GX_CLAMP,0);
            GXInitTexObjData(&object,test==29?data+128:data);GXLoadTexObj(&object,GX_TEXMAP0);expected=test==30;
        }
        u8 rasterAlpha=255;
        if(test>=31&&test<41){int mode=(test-31)/2;bool textureOpaque=(test&1)==0;rasterAlpha=textureOpaque?0:255;
            memset(data,255,sizeof(data));for(int i=0;i<32;i+=2)data[i]=textureOpaque?255:0;
            GXInitTexObj(&object,data,4,4,GX_TF_RGB5A3,GX_CLAMP,GX_CLAMP,0);GXLoadTexObj(&object,GX_TEXMAP0);GXSetTevOp(GX_TEVSTAGE0,(GXTevMode)mode);
            expected=(mode==GX_DECAL||mode==GX_PASSCLR)?!textureOpaque:mode==GX_REPLACE?textureOpaque:0;
        }
        if(test>=41){
            GXSetTevOp(GX_TEVSTAGE0,GX_REPLACE);
            if(test==41){
                memset(data,255,sizeof(data));
                GXInitTexObj(&object,data,4,4,GX_TF_RGB5A3,GX_CLAMP,GX_CLAMP,0);
                GXLoadTexObj(&object,GX_TEXMAP0);
                for(int i=0;i<32;i+=2)data[i]=0;
                expected=1; // CPU edits remain invisible before invalidation.
            }else if(test==42){GXInvalidateTexAll();expected=0;}
            else if(test==43){
                memset(data+128,255,32);GXInitTexObjData(&object,data+128);
                GXInvalidateTexAll();expected=0; // Changing an unloaded descriptor must not change the binding.
            }else{GXLoadTexObj(&object,GX_TEXMAP0);GXInvalidateTexAll();expected=1;}
        }
        GXSetTevOrder(GX_TEVSTAGE0,GX_TEXCOORD0,(GXTexMapID)slot,GX_COLOR0A0);
        require(SUCCEEDED(query->Issue(D3DISSUE_BEGIN)));GXBegin(GX_TRIANGLES,GX_VTXFMT0,3);
        GXPosition3f32(-.2f,-.2f,-1);GXColor4u8(255,255,255,rasterAlpha);GXTexCoord2f32(.5f,.5f);GXPosition3f32(.2f,-.2f,-1);GXColor4u8(255,255,255,rasterAlpha);GXTexCoord2f32(.5f,.5f);GXPosition3f32(0,.2f,-1);GXColor4u8(255,255,255,rasterAlpha);GXTexCoord2f32(.5f,.5f);GXEnd();require(SUCCEEDED(query->Issue(D3DISSUE_END)));
        device->BlockUntilIdle();DWORD pixels=0;HRESULT result;unsigned int attempt=0;do{result=query->GetData(&pixels,sizeof(pixels),D3DGETDATA_FLUSH);if(result==S_FALSE)Sleep(1);}while(result==S_FALSE&&++attempt<10000);
        if(result!=S_OK||(pixels>0)!=(expected!=0)){char report[160];sprintf_s(report,sizeof(report),"GX texture expansion FAILED: case=%d pixels=%u expected=%d HRESULT=%08x\n",test,pixels,expected,result);Melee360Log(report);ok=false;break;}++draws;
    }
    query->Release();palettes[19]=oldPalette;for(int unit=0;unit<8;++unit){releaseTexture(loadedTextures[unit]);loadedTextures[unit]=oldTextures[unit];boundDescriptors[unit]=oldDescriptors[unit];boundImages[unit]=oldImages[unit];boundValid[unit]=oldValid[unit];boundSources[unit]=oldSources[unit];for(int i=0;i<9;++i)device->SetSamplerState(unit,states[i],saved[unit][i]);}
    for(unsigned int i=0;i<textureImages.size();++i)if(textureImages[i].object==&object){textureImages.erase(textureImages.begin()+i);break;}
    for(unsigned int i=0;i<paletteImages.size();++i)if(paletteImages[i].object==&lut){paletteImages.erase(paletteImages.begin()+i);break;}
    selectedTexture=oldRoute;memcpy(textureLod,oldLod,sizeof(oldLod));memcpy(textureBias,oldBias,sizeof(oldBias));memcpy(alphaFirst,first,16);memcpy(alphaSecond,second,16);tev=savedTev;textureExpansionTesting=false;return ok&&draws==45;
}





#include "gx_tev_probe.inc"







extern "C" int Melee360GXZ16Probe(void){
    require(device&&!__GXinBegin);unsigned cpuCases=0;
    for(int mode=0;mode<4;++mode)for(u32 code=0;code<65536;++code){if(mode==GX_ZC_FAR&&code>=0xd000)continue;
        u32 decoded=GXDecompressZ16(code,(GXZFmt16)mode);if(GXCompressZ16(decoded,(GXZFmt16)mode)!=code)return 0;++cpuCases;}
    TevState savedTev=tev;float savedFirst[4],savedSecond[4];memcpy(savedFirst,alphaFirst,16);memcpy(savedSecond,alphaSecond,16);IDirect3DTexture9* oldImage=loadedTextures[0];loadedTextures[0]=0;
    IDirect3DStateBlock9* saved=0;IDirect3DSurface9 *oldTarget=0,*oldDepth=0,*target=0,*depth=0;D3DVIEWPORT9 viewport;
    require(SUCCEEDED(device->CreateStateBlock(D3DSBT_ALL,&saved))&&SUCCEEDED(saved->Capture()));device->GetRenderTarget(0,&oldTarget);device->GetDepthStencilSurface(&oldDepth);device->GetViewport(&viewport);int oldCompression=Melee360GXDepthCompression();
    D3DSURFACE_PARAMETERS params={0};params.Base=1800;
    require(SUCCEEDED(device->CreateRenderTarget(64,64,D3DFMT_R5G6B5,D3DMULTISAMPLE_4_SAMPLES,0,FALSE,&target,&params)));params.Base+=XGSurfaceSize(64,64,D3DFMT_R5G6B5,D3DMULTISAMPLE_4_SAMPLES);
    require(params.Base+XGSurfaceSize(64,64,D3DFMT_D24S8,D3DMULTISAMPLE_4_SAMPLES)<2000);
    require(SUCCEEDED(device->CreateDepthStencilSurface(64,64,D3DFMT_D24S8,D3DMULTISAMPLE_4_SAMPLES,0,FALSE,&depth,&params)));
    device->SetDepthStencilSurface(0);device->SetRenderTarget(0,target);device->SetDepthStencilSurface(depth);GXSetViewport(0,0,64,64,0,1);
    GXSetCullMode(GX_CULL_NONE);GXSetBlendMode(GX_BM_NONE,GX_BL_ONE,GX_BL_ZERO,GX_LO_COPY);GXSetScissor(0,0,64,64);device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);device->SetRenderState(D3DRS_MULTISAMPLEMASK,0xffff);
    initializeTev();GXSetTevOp(GX_TEVSTAGE0,GX_MODULATE);GXSetAlphaCompare(GX_ALWAYS,0,GX_AOP_AND,GX_ALWAYS,0);

    const u32 positions[]={0x004567,0x456789,0x8abcde,0xeabcde,0xff1234,0xfff123};IDirect3DQuery9* query=0;require(SUCCEEDED(device->CreateQuery(D3DQUERYTYPE_OCCLUSION,&query)));bool ok=true;unsigned gpuCases=0;
    for(int mode=0;mode<4&&ok;++mode){GXSetPixelFmt(GX_PF_RGB565_Z16,(GXZFmt16)mode);
        for(int path=0;path<2&&ok;++path)for(int sample=0;sample<6&&ok;++sample)for(int variation=0;variation<3&&ok;++variation){u32 a=positions[sample],b=variation==0?a:variation==1?a+16:a^0x1000;
            device->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,0,1,0);
            for(int pass=0;pass<2;++pass){u32 value=pass?b:a;float z=value/16777215.f;
                GXSetZTexture(path?GX_ZT_REPLACE:GX_ZT_DISABLE,GX_TF_Z24X8,(value-0xffffff)&0xffffff);GXSetZMode(GX_TRUE,pass?GX_EQUAL:GX_ALWAYS,pass?GX_FALSE:GX_TRUE);
                if(pass)query->Issue(D3DISSUE_BEGIN);Vertex triangle[3];memset(triangle,0,sizeof(triangle));
                for(int v=0;v<3;++v){for(unsigned unit=0;unit<8;++unit)vertexTex(triangle[v],unit)[2]=1;triangle[v].clip[0]=v==1?.5f:v==0?-.5f:0;triangle[v].clip[1]=v==2?.5f:-.5f;triangle[v].clip[2]=z;triangle[v].clip[3]=1;for(int c=0;c<4;++c)triangle[v].color[c]=triangle[v].color1[c]=1;}
                bindDirectPipeline();require(SUCCEEDED(device->DrawPrimitiveUP(D3DPT_TRIANGLELIST,1,triangle,sizeof(Vertex))));if(pass)query->Issue(D3DISSUE_END);
            }
            device->BlockUntilIdle();DWORD pixels=0;HRESULT result;unsigned attempt=0;do{result=query->GetData(&pixels,sizeof(pixels),D3DGETDATA_FLUSH);if(result==S_FALSE)Sleep(1);}while(result==S_FALSE&&++attempt<10000);
            bool expected=GXCompressZ16(a,(GXZFmt16)mode)==GXCompressZ16(b,(GXZFmt16)mode);ok=result==S_OK&&((pixels>0)==expected);++gpuCases;
            if(!ok){char trace[192];sprintf_s(trace,sizeof(trace),"GX Z16 probe mismatch: mode=%d path=%d a=%06x b=%06x pixels=%u expected=%d\n",mode,path,a,b,pixels,expected);Melee360Log(trace);}
        }
    }
    device->SetDepthStencilSurface(0);device->SetRenderTarget(0,oldTarget);device->SetDepthStencilSurface(oldDepth);GXSetPixelFmt(oldCompression>=0?GX_PF_RGB565_Z16:GX_PF_RGB8_Z24,oldCompression>=0?(GXZFmt16)oldCompression:GX_ZC_LINEAR);
    GXSetViewport(viewport.X,viewport.Y,viewport.Width,viewport.Height,viewport.MinZ,viewport.MaxZ);saved->Apply();device->BlockUntilIdle();query->Release();saved->Release();oldTarget->Release();oldDepth->Release();target->Release();depth->Release();tev=savedTev;memcpy(alphaFirst,savedFirst,16);memcpy(alphaSecond,savedSecond,16);loadedTextures[0]=oldImage;
    if(ok){char trace[192];sprintf_s(trace,sizeof(trace),"GX Z16: %u original CPU code roundtrips, %u GPU equality cases for regular/Z-texture and four compression modes passed\n",cpuCases,gpuCases);Melee360Log(trace);}return ok;
}
#include "gx_raster_probe.inc"
#include "gx_fog_probe.inc"

#include "gx_copy_texture.inc"
/* Explicit diagnostic capture before the FPS overlay. No draw state changed. */
extern "C" int Melee360GXCaptureMatch(unsigned frame){
 IDirect3DSurface9* target=0;D3DSURFACE_DESC desc;require(SUCCEEDED(device->GetRenderTarget(0,&target))&&target);target->GetDesc(&desc);target->Release();
 IDirect3DTexture9* image=0;const D3DFORMAT format=D3DFMT_LE_X8R8G8B8;
 require(SUCCEEDED(device->CreateTexture(desc.Width,desc.Height,1,0,format,D3DPOOL_DEFAULT,&image,0)));
 require(SUCCEEDED(device->Resolve(D3DRESOLVE_RENDERTARGET0,0,image,0,0,0,0,1.f,0,0)));device->BlockUntilIdle();
 D3DLOCKED_RECT lock;require(SUCCEEDED(image->LockRect(0,&lock,0,D3DLOCK_READONLY)));std::vector<u8> raw(desc.Width*desc.Height*4);
 XGUntileTextureLevel(desc.Width,desc.Height,0,XGGetGpuFormat(format),0,&raw[0],desc.Width*4,0,lock.pBits,0);image->UnlockRect(0);image->Release();
 unsigned colored=0;for(unsigned i=0;i<raw.size();i+=4){if(raw[i]||raw[i+1]||raw[i+2])++colored;raw[i+3]=255;}
 char path[100];sprintf_s(path,sizeof(path),"game:\\original-match-%04u.tga",frame);FILE* file=0;if(fopen_s(&file,path,"wb")||!file)return 0;
 u8 header[18]={0};header[2]=2;header[12]=(u8)desc.Width;header[13]=(u8)(desc.Width>>8);header[14]=(u8)desc.Height;header[15]=(u8)(desc.Height>>8);header[16]=32;header[17]=0x28;
 bool ok=fwrite(header,1,18,file)==18&&fwrite(&raw[0],1,raw.size(),file)==raw.size();fclose(file);
 char msg[160];sprintf_s(msg,sizeof(msg),"Original render capture: frame=%u size=%ux%u nonblack=%u saved=%u\n",frame,desc.Width,desc.Height,colored,ok?1:0);Melee360Log(msg);return ok?1:0;
}

#include "gx_lighting_probe.inc"
#include "gx_texgen_probe.inc"
extern "C" void GXInvalidateVtxCache(void){if(gxProfile.enabled)++gxProfile.invalidations;require(device&&!__GXinBegin);/* Indexed attributes are fetched afresh on the CPU for every submitted vertex.
 * Drain earlier uploads/draws before the caller reuses their backing storage. */device->BlockUntilIdle();}

extern "C" void GXSetDstAlpha(GXBool enabled,u8 alpha){require(!__GXinBegin&&(enabled==GX_FALSE||enabled==GX_TRUE));destinationAlphaEnabled=enabled!=GX_FALSE;destinationAlpha=alpha;}

extern "C" void GXSetZCompLoc(GXBool early){require(!__GXinBegin&&(early==GX_FALSE||early==GX_TRUE));earlyDepth=early!=GX_FALSE;}

#include "match_surface.inc"



