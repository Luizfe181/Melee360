#include <xtl.h>
#include <stdio.h>
#include <math.h>
#include "platform_log.h"
extern "C" {
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXManage.h>
#include <dolphin/gx/GXTransform.h>
#include <dolphin/gx/GXCpu2Efb.h>
void __assert(const char*,unsigned int,const char*);
extern GXBool __GXinBegin;
}
extern "C" void Melee360GXFinishCompletedPacket(void);
namespace {
IDirect3DDevice9* device;DWORD colorMask=15,pixelWriteMask=15,fence;bool pending;int depthCompression=-1;GXPixelFmt currentPixelFormat=GX_PF_RGB8_Z24;bool ditherEnabled;GXDrawDoneCallback doneCallback;
void require(bool condition){if(!condition)__assert(__FILE__,__LINE__,"unsupported/invalid Xbox GX state");}
void bound(){Melee360GXFinishCompletedPacket();require(device!=0);}
DWORD blend(GXBlendFactor value,bool source){require(value>=0&&value<=7);static const DWORD factors[8]={D3DBLEND_ZERO,D3DBLEND_ONE,D3DBLEND_SRCCOLOR,D3DBLEND_INVSRCCOLOR,D3DBLEND_SRCALPHA,D3DBLEND_INVSRCALPHA,D3DBLEND_DESTALPHA,D3DBLEND_INVDESTALPHA};if(value==2)return source?D3DBLEND_DESTCOLOR:D3DBLEND_SRCCOLOR;if(value==3)return source?D3DBLEND_INVDESTCOLOR:D3DBLEND_INVSRCCOLOR;return factors[value];}
int completions;void completed(){++completions;}
float viewport[6]={0,0,1280,720,0,1};GXCullMode cullMode=GX_CULL_NONE;
}
extern "C" int Melee360GXCullMode(void){return (int)cullMode;}
extern "C" void GXSetCullMode(GXCullMode mode){bound();require(!__GXinBegin&&mode>=GX_CULL_NONE&&mode<=GX_CULL_ALL);cullMode=mode;device->SetRenderState(D3DRS_CULLMODE,mode==GX_CULL_FRONT?D3DCULL_CCW:mode==GX_CULL_BACK?D3DCULL_CW:D3DCULL_NONE);}
extern "C" void GXSetViewportJitter(f32 left,f32 top,f32 width,f32 height,f32 nearz,f32 farz,u32 field){
    bound();require(field<=1&&_finite(left)&&_finite(top)&&_finite(width)&&_finite(height)&&_finite(nearz)&&_finite(farz));
    if(field==0)top-=.5f;
    // The current backend accepts physical, integer target coordinates only.
    // Fractional interlaced origins need an offset in the vertex shader.
    require(left>=0&&top>=0&&width>0&&height>0&&left==floorf(left)&&top==floorf(top)&&width==floorf(width)&&height==floorf(height)&&left+width<=16384&&top+height<=16384&&nearz>=0&&farz<=1&&nearz<=farz);
    D3DVIEWPORT9 value={(DWORD)left,(DWORD)top,(DWORD)width,(DWORD)height,nearz,farz};require(SUCCEEDED(device->SetViewport(&value)));
    viewport[0]=left;viewport[1]=top;viewport[2]=width;viewport[3]=height;viewport[4]=nearz;viewport[5]=farz;
}
extern "C" void GXSetViewport(f32 left,f32 top,f32 width,f32 height,f32 nearz,f32 farz){GXSetViewportJitter(left,top,width,height,nearz,farz,1);}
extern "C" void GXGetViewportv(f32* value){require(value!=0);memcpy(value,viewport,sizeof(viewport));}
extern "C" void Melee360GXBindDevice(IDirect3DDevice9* value){require(!pending);device=value;colorMask=pixelWriteMask=15;currentPixelFormat=GX_PF_RGB8_Z24;ditherEnabled=false;}
extern "C" void GXSetBlendMode(GXBlendMode mode,GXBlendFactor source,GXBlendFactor destination,GXLogicOp op){bound();require(mode>=GX_BM_NONE&&mode<=GX_BM_SUBTRACT);require(mode!=GX_BM_LOGIC||op==GX_LO_COPY);bool enabled=mode==GX_BM_BLEND||mode==GX_BM_SUBTRACT;device->SetRenderState(D3DRS_ALPHABLENDENABLE,enabled);if(enabled){device->SetRenderState(D3DRS_SRCBLEND,mode==GX_BM_SUBTRACT?D3DBLEND_ONE:blend(source,true));device->SetRenderState(D3DRS_DESTBLEND,mode==GX_BM_SUBTRACT?D3DBLEND_ONE:blend(destination,false));device->SetRenderState(D3DRS_BLENDOP,mode==GX_BM_SUBTRACT?D3DBLENDOP_REVSUBTRACT:D3DBLENDOP_ADD);}}
/* Native RGB8/Z24 and RGB565/Z16 targets; compressed Z16 is represented
 * by original quantization buckets in the native D24 depth surface. */
extern "C" float Melee360GXClearDepth(u32 z){require(z<=0xffffff);if(depthCompression>=0)z=GXDecompressZ16(GXCompressZ16(z,(GXZFmt16)depthCompression),(GXZFmt16)depthCompression);return z/16777215.f;}
extern "C" int Melee360GXDepthCompression(void){return depthCompression;}
extern "C" u32 Melee360GXColorUpdates(void){return colorMask;}
extern "C" int Melee360GXRGBA6(void){return currentPixelFormat==GX_PF_RGBA6_Z24;}
extern "C" u32 Melee360GXPackEfbColor(u32 color){if(currentPixelFormat!=GX_PF_RGBA6_Z24)return color;u32 result=0;for(u32 shift=0;shift<32;shift+=8){u32 six=((color>>shift)&255)>>2;result|=(six*4+(six>>4))<<shift;}return result;}
extern "C" int Melee360GXDither(void){return ditherEnabled;}
extern "C" int Melee360GXPixelFormat(void){return (int)currentPixelFormat;}
extern "C" void GXSetDither(GXBool value){bound();require(!__GXinBegin&&(value==GX_FALSE||value==GX_TRUE));ditherEnabled=value!=GX_FALSE;}
extern "C" void GXSetPixelFmt(GXPixelFmt format,GXZFmt16 depth){
    bound();require(!__GXinBegin);
    require(((format==GX_PF_RGB8_Z24||format==GX_PF_RGBA6_Z24||format==GX_PF_Z24)&&depth==GX_ZC_LINEAR)||(format==GX_PF_RGB565_Z16&&depth>=GX_ZC_LINEAR&&depth<=GX_ZC_FAR));
    IDirect3DSurface9 *color=0,*z=0;D3DSURFACE_DESC colorDesc,zDesc;
    require(SUCCEEDED(device->GetRenderTarget(0,&color))&&color);
    require(SUCCEEDED(device->GetDepthStencilSurface(&z))&&z);
    HRESULT a=color->GetDesc(&colorDesc),b=z->GetDesc(&zDesc);color->Release();z->Release();
    require(SUCCEEDED(a)&&SUCCEEDED(b)&&colorDesc.Width==zDesc.Width&&colorDesc.Height==zDesc.Height);
    require(zDesc.Format==D3DFMT_D24S8);
    if(format==GX_PF_RGB565_Z16)require(colorDesc.Format==D3DFMT_R5G6B5&&colorDesc.MultiSampleType==zDesc.MultiSampleType);
    else require(colorDesc.Format==D3DFMT_A8R8G8B8||colorDesc.Format==(D3DFORMAT)MAKESRGBFMT(D3DFMT_A8R8G8B8));
    if(format==GX_PF_RGBA6_Z24)require(colorDesc.Format==D3DFMT_A8R8G8B8&&colorDesc.MultiSampleType==D3DMULTISAMPLE_NONE);currentPixelFormat=format;depthCompression=format==GX_PF_RGB565_Z16?(int)depth:-1;pixelWriteMask=format==GX_PF_Z24?0:format==GX_PF_RGBA6_Z24?15:7;
    require(SUCCEEDED(device->SetRenderState(D3DRS_COLORWRITEENABLE,colorMask&pixelWriteMask)));
}
extern "C" int Melee360GXPixelFormatProbe(void){
    bound();DWORD savedMask=colorMask,savedPixel=pixelWriteMask,savedNative=0,value=0;
    require(SUCCEEDED(device->GetRenderState(D3DRS_COLORWRITEENABLE,&savedNative)));
    GXSetColorUpdate(1);GXSetAlphaUpdate(1);GXSetPixelFmt(GX_PF_RGB8_Z24,GX_ZC_LINEAR);
    require(SUCCEEDED(device->GetRenderState(D3DRS_COLORWRITEENABLE,&value)));bool ok=value==7;
    GXSetAlphaUpdate(0);GXSetAlphaUpdate(1);device->GetRenderState(D3DRS_COLORWRITEENABLE,&value);ok=ok&&value==7;
    GXSetColorUpdate(0);device->GetRenderState(D3DRS_COLORWRITEENABLE,&value);ok=ok&&value==0;
    GXSetColorUpdate(1);GXSetPixelFmt(GX_PF_Z24,GX_ZC_LINEAR);device->GetRenderState(D3DRS_COLORWRITEENABLE,&value);ok=ok&&value==0;
    GXSetAlphaUpdate(0);GXSetAlphaUpdate(1);device->GetRenderState(D3DRS_COLORWRITEENABLE,&value);ok=ok&&value==0;
    GXSetPixelFmt(GX_PF_RGB8_Z24,GX_ZC_LINEAR);device->GetRenderState(D3DRS_COLORWRITEENABLE,&value);ok=ok&&value==7;
    colorMask=savedMask;pixelWriteMask=savedPixel;require(SUCCEEDED(device->SetRenderState(D3DRS_COLORWRITEENABLE,savedNative)));
    return ok;
}
extern "C" void GXSetColorUpdate(GXBool enabled){bound();colorMask=(colorMask&8)|(enabled?7:0);device->SetRenderState(D3DRS_COLORWRITEENABLE,colorMask&pixelWriteMask);}
extern "C" void GXSetAlphaUpdate(GXBool enabled){bound();colorMask=(colorMask&7)|(enabled?8:0);device->SetRenderState(D3DRS_COLORWRITEENABLE,colorMask&pixelWriteMask);}
extern "C" void GXSetZMode(GXBool compare,GXCompare function,GXBool write){bound();require(function>=GX_NEVER&&function<=GX_ALWAYS);static const DWORD comparisons[8]={D3DCMP_NEVER,D3DCMP_LESS,D3DCMP_EQUAL,D3DCMP_LESSEQUAL,D3DCMP_GREATER,D3DCMP_NOTEQUAL,D3DCMP_GREATEREQUAL,D3DCMP_ALWAYS};device->SetRenderState(D3DRS_ZENABLE,compare||write?D3DZB_TRUE:D3DZB_FALSE);device->SetRenderState(D3DRS_ZFUNC,compare?comparisons[function]:D3DCMP_ALWAYS);device->SetRenderState(D3DRS_ZWRITEENABLE,write!=0);}
extern "C" void GXSetScissor(u32 x,u32 y,u32 width,u32 height){bound();require(width&&height&&x<16384&&y<16384&&width<=16384-x&&height<=16384-y);RECT rectangle={(LONG)x,(LONG)y,(LONG)(x+width),(LONG)(y+height)};device->SetScissorRect(&rectangle);device->SetRenderState(D3DRS_SCISSORTESTENABLE,TRUE);}
extern "C" void GXPixModeSync(void){bound();device->BlockUntilIdle();}
extern "C" GXDrawDoneCallback GXSetDrawDoneCallback(GXDrawDoneCallback callback){GXDrawDoneCallback previous=doneCallback;doneCallback=callback;return previous;}
extern "C" void GXSetDrawDone(void){bound();fence=device->InsertFence();pending=true;}
extern "C" void Melee360GXPump(void){if(pending&&!device->IsFencePending(fence)){pending=false;if(doneCallback)doneCallback();}}
extern "C" void GXWaitDrawDone(void){bound();if(pending){device->BlockOnFence(fence);Melee360GXPump();}}
extern "C" int Melee360GXStateProbe(void){
    bound();static const D3DRENDERSTATETYPE states[]={D3DRS_ALPHABLENDENABLE,D3DRS_SRCBLEND,D3DRS_DESTBLEND,D3DRS_BLENDOP,D3DRS_ZENABLE,D3DRS_ZFUNC,D3DRS_ZWRITEENABLE,D3DRS_COLORWRITEENABLE,D3DRS_SCISSORTESTENABLE};DWORD saved[9],value;RECT oldRectangle,rectangle;for(int i=0;i<9;++i)device->GetRenderState(states[i],&saved[i]);device->GetScissorRect(&oldRectangle);
    GXSetBlendMode(GX_BM_BLEND,GX_BL_SRCALPHA,GX_BL_INVSRCALPHA,GX_LO_COPY);GXSetZMode(1,GX_LEQUAL,1);GXSetColorUpdate(1);GXSetAlphaUpdate(0);GXSetScissor(0,0,1280,720);
    bool ok=true;char message[128];device->GetRenderState(D3DRS_SRCBLEND,&value);sprintf_s(message,sizeof(message),"GX state probe: srcBlend=%u expected=%u\n",value,(DWORD)D3DBLEND_SRCALPHA);Melee360Log(message);ok=ok&&value==D3DBLEND_SRCALPHA;device->GetRenderState(D3DRS_ZFUNC,&value);sprintf_s(message,sizeof(message),"GX state probe: zFunc=%u expected=%u\n",value,(DWORD)D3DCMP_LESSEQUAL);Melee360Log(message);ok=ok&&value==D3DCMP_LESSEQUAL;device->GetRenderState(D3DRS_COLORWRITEENABLE,&value);sprintf_s(message,sizeof(message),"GX state probe: colorMask=%u expected=7\n",value);Melee360Log(message);ok=ok&&value==7;device->GetScissorRect(&rectangle);sprintf_s(message,sizeof(message),"GX state probe: scissor=%ld,%ld,%ld,%ld\n",rectangle.left,rectangle.top,rectangle.right,rectangle.bottom);Melee360Log(message);ok=ok&&rectangle.right==1280&&rectangle.bottom==720;
    completions=0;GXDrawDoneCallback previous=GXSetDrawDoneCallback(completed);GXSetDrawDone();GXWaitDrawDone();sprintf_s(message,sizeof(message),"GX state probe: fence callbacks=%d pending=%d\n",completions,pending?1:0);Melee360Log(message);ok=ok&&completions==1;GXSetDrawDoneCallback(previous);
    for(int i=0;i<9;++i)device->SetRenderState(states[i],saved[i]);device->SetScissorRect(&oldRectangle);colorMask=saved[7];return ok;
}

extern "C" {
#include <sysdolphin/baselib/initialize.h>
int Melee360HsdRenderConfigure(u32,u32);
}
/* Field selection is composed during XFB copy, preserving the previous field.
 * Half-height line/point footprints still require a separate raster path. */
extern "C" void Melee360XfbSetField(int);
extern "C" void GXSetFieldMode(GXBool field,GXBool halfAspect){
    bound();require(!__GXinBegin&&(field==GX_FALSE||field==GX_TRUE)&&halfAspect==GX_FALSE);
    require(SUCCEEDED(device->SetRenderState(D3DRS_MULTISAMPLEMASK,0xffffu)));
    Melee360XfbSetField(field);
}
extern "C" int Melee360HsdRenderBoot(void){
    bound();IDirect3DSurface9* target=0;D3DSURFACE_DESC desc;
    require(SUCCEEDED(device->GetRenderTarget(0,&target))&&target);
    HRESULT result=target->GetDesc(&desc);target->Release();require(SUCCEEDED(result));
    if(!Melee360HsdRenderConfigure(desc.Width,desc.Height))return 0;
    GXRenderModeObj* mode=HSD_VIGetRenderMode();
    if(mode->fbWidth!=desc.Width||mode->efbHeight!=desc.Height||mode->aa||mode->field_rendering)return 0;
    DWORD mask;
    for(int pass=HSD_RP_SCREEN;pass<HSD_RP_NUM;++pass){
        GXSetColorUpdate(GX_TRUE);GXSetPixelFmt(GX_PF_Z24,GX_ZC_LINEAR);
        require(SUCCEEDED(device->SetRenderState(D3DRS_MULTISAMPLEMASK,0)));
        HSD_StartRender((HSD_RenderPass)pass);
        require(SUCCEEDED(device->GetRenderState(D3DRS_COLORWRITEENABLE,&mask)));if(mask!=7){char trace[96];sprintf_s(trace,sizeof(trace),"HSD render RGB mask readback: %08x\n",mask);Melee360Log(trace);return 0;}
        require(SUCCEEDED(device->GetRenderState(D3DRS_MULTISAMPLEMASK,&mask)));if(mask!=0xffffu){char trace[96];sprintf_s(trace,sizeof(trace),"HSD render sample mask readback: %08x\n",mask);Melee360Log(trace);return 0;}
        if(HSD_GetCurrentRenderPass()!=pass)return 0;
        HSD_Init_803755A8();if(HSD_GetCurrentRenderPass()!=pass)return 0;
    }
    HSD_StartRender(HSD_RP_SCREEN);return HSD_GetCurrentRenderPass()==HSD_RP_SCREEN;
}
extern "C" void Melee360HsdStartScreen(void){HSD_StartRender(HSD_RP_SCREEN);}
