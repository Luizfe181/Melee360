#include <xtl.h>
#include <xgraphics.h>
#include <math.h>
#include <stdio.h>
#include "platform_log.h"
#include "xfb_VS.h"
#include "xfb_PS.h"
#include "xfb_PSWhite.h"
extern "C" {
#include <dolphin/gx.h>
#include <dolphin/vi.h>
#include <sysdolphin/baselib/video.h>
void __assert(const char*,unsigned int,const char*);
u32 Melee360GXPackEfbColor(u32);int Melee360GXRGBA6(void);void Melee360VIBeginFrame(void);void Melee360VIEndFrame(int);
void Melee360HsdCopyInvalidateState(void);
void Melee360VISetPresenter(int (*)(void));
void* Melee360VIActiveBuffer(void);int Melee360VIBlack(void);
int Melee360VIConfigureSupported(const GXRenderModeObj*);
float Melee360GXClearDepth(u32);
}
namespace {
IDirect3DDevice9* device;IDirect3DTexture9* buffers[3];IDirect3DTexture9* blackTexture;
u32 width,height,xfbWidth,xfbHeight,outputWidth,outputHeight;bool aaMode;
IDirect3DSurface9 *aaColor,*aaDepth,*originalColor,*originalDepth;u16 srcX,srcY,srcW,srcH,dstW,dstH;float scale=1;GXColor clearColor;u32 clearDepth=0xffffff;
unsigned int copies,presents;bool running,experimental;
IDirect3DTexture9* history[2];
int index(void*);
IDirect3DTexture9* snapshot;IDirect3DSurface9* stripe;
IDirect3DVertexShader9* filterVS;IDirect3DPixelShader9* filterPS;IDirect3DVertexDeclaration9* filterDecl;
float weights[4]={0,64,0,1};GXFBClamp copyClamp=(GXFBClamp)(GX_CLAMP_TOP|GX_CLAMP_BOTTOM);
bool verticalFilter,fieldCopy;
void check(bool ok){if(!ok)__assert(__FILE__,__LINE__,"unsupported/invalid native XFB operation");}
void filteredCopy(IDirect3DTexture9* destination){
    check(SUCCEEDED(device->Resolve(D3DRESOLVE_RENDERTARGET0|(aaMode?D3DRESOLVE_FRAGMENTS0123:0),0,snapshot,0,0,0,0,1.f,0,0)));
    IDirect3DStateBlock9* saved=0;IDirect3DSurface9* target=0;IDirect3DSurface9* depth=0;D3DVIEWPORT9 viewport;
    check(SUCCEEDED(device->CreateStateBlock(D3DSBT_ALL,&saved))&&SUCCEEDED(saved->Capture()));
    check(SUCCEEDED(device->GetRenderTarget(0,&target))&&SUCCEEDED(device->GetDepthStencilSurface(&depth))&&SUCCEEDED(device->GetViewport(&viewport)));
    check(SUCCEEDED(device->SetDepthStencilSurface(0))&&SUCCEEDED(device->SetRenderTarget(0,stripe)));
    D3DVIEWPORT9 tile={0,0,dstW,32,0,1};device->SetViewport(&tile);
    device->SetVertexShader(filterVS);device->SetPixelShader(filterPS);device->SetVertexDeclaration(filterDecl);float raster[4]={(float)dstW,32,0,0};device->SetVertexShaderConstantF(0,raster,1);
    device->SetRenderState(D3DRS_ZENABLE,FALSE);device->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);device->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
    device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);device->SetRenderState(D3DRS_SCISSORTESTENABLE,FALSE);
    device->SetRenderState(D3DRS_COLORWRITEENABLE,15);device->SetTexture(0,snapshot);device->SetTexture(1,fieldCopy&&index(Melee360VIActiveBuffer())>=0?history[index(Melee360VIActiveBuffer())]:snapshot);
    for(int i=0;i<2;++i){device->SetSamplerState(i,D3DSAMP_MINFILTER,D3DTEXF_POINT);device->SetSamplerState(i,D3DSAMP_MAGFILTER,D3DTEXF_POINT);device->SetSamplerState(i,D3DSAMP_MIPFILTER,D3DTEXF_NONE);device->SetSamplerState(i,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);device->SetSamplerState(i,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);}
    float rect[4]={(float)srcX,(float)srcY,(float)width,(float)height};
    float limits[4]={copyClamp&GX_CLAMP_TOP?(float)srcY:0,copyClamp&GX_CLAMP_BOTTOM?(float)(srcY+srcH-1):(float)(height-1),(float)width,0};
    float field[4]={fieldCopy?1.f:0.f,(float)VIGetNextField(),(float)srcW,(float)xfbHeight};device->SetPixelShaderConstantF(0,rect,1);device->SetPixelShaderConstantF(2,weights,1);device->SetPixelShaderConstantF(3,limits,1);device->SetPixelShaderConstantF(4,field,1);
    const float quad[6][4]={{-1,1,0,0},{1,1,1,0},{-1,-1,0,1},{-1,-1,0,1},{1,1,1,0},{1,-1,1,1}};
    for(u32 y=0;y<dstH;y+=32){float dest[4]={(float)dstW,(float)dstH,(float)y,1.f/scale};device->SetPixelShaderConstantF(1,dest,1);
        check(SUCCEEDED(device->DrawPrimitiveUP(D3DPT_TRIANGLELIST,2,quad,sizeof(quad[0]))));
        D3DRECT region={0,0,dstW,(LONG)((dstH-y)<32?dstH-y:32)};D3DPOINT at={0,(LONG)y};
        check(SUCCEEDED(device->Resolve(D3DRESOLVE_RENDERTARGET0,&region,destination,&at,0,0,0,1.f,0,0)));
        check(SUCCEEDED(device->Resolve(D3DRESOLVE_RENDERTARGET0,&region,history[index(destination)],&at,0,0,0,1.f,0,0)));
    }
    device->SetRenderTarget(0,target);device->SetDepthStencilSurface(depth);saved->Apply();device->SetViewport(&viewport);
    if(depth)depth->Release();target->Release();saved->Release();
}

u32 readPixel(IDirect3DTexture9* image,u32 row,u32 x=0){
    device->BlockUntilIdle();D3DLOCKED_RECT lock;check(SUCCEEDED(image->LockRect(0,&lock,0,D3DLOCK_READONLY)));
    XGTEXTURE_DESC desc;XGGetTextureDesc(image,0,&desc);u8 pixel[4]={0};RECT region={(LONG)x,(LONG)row,(LONG)x+1,(LONG)row+1};
    XGUntileTextureLevel(desc.Width,desc.Height,0,XGGetGpuFormat(desc.Format),0,pixel,4,0,lock.pBits,&region);image->UnlockRect(0);
    if(desc.Format==D3DFMT_A8R8G8B8)return D3DCOLOR_ARGB(pixel[0],pixel[1],pixel[2],pixel[3]);
    check(desc.Format==(D3DFORMAT)MAKESRGBFMT(D3DFMT_LE_X8R8G8B8)||desc.Format==D3DFMT_LE_X8R8G8B8);return D3DCOLOR_ARGB(pixel[3],pixel[2],pixel[1],pixel[0]);
}
bool rawProbe(IDirect3DTexture9* image,u32 row,u32 expected,const char* label){
    u32 actual=readPixel(image,row);char trace[192];sprintf_s(trace,sizeof(trace),"XFB raw probe %s: row=%u actual=%08x expected=%08x\n",label,row,actual,expected);Melee360Log(trace);
    return (actual&0xffffff)==(expected&0xffffff);
}
bool nativeAaProbe(){
    IDirect3DStateBlock9* saved=0;IDirect3DSurface9* oldTarget=0;IDirect3DSurface9* oldDepth=0;D3DVIEWPORT9 viewport;
    check(SUCCEEDED(device->CreateStateBlock(D3DSBT_ALL,&saved))&&SUCCEEDED(saved->Capture()));device->GetRenderTarget(0,&oldTarget);device->GetDepthStencilSurface(&oldDepth);device->GetViewport(&viewport);
    D3DSURFACE_PARAMETERS params={0};params.Base=2000;
    check(params.Base+XGSurfaceSize(64,64,D3DFMT_R5G6B5,D3DMULTISAMPLE_4_SAMPLES)<=2048);
    IDirect3DSurface9* color=0;IDirect3DTexture9* image=0;IDirect3DPixelShader9* white=0;
    HRESULT allocation=device->CreateRenderTarget(64,64,D3DFMT_R5G6B5,D3DMULTISAMPLE_4_SAMPLES,0,FALSE,&color,&params);
    if(FAILED(allocation)){char trace[128];sprintf_s(trace,sizeof(trace),"AA native RGB565 allocation rejected: %08x\n",allocation);Melee360Log(trace);saved->Release();oldTarget->Release();if(oldDepth)oldDepth->Release();return false;}
    check(SUCCEEDED(device->CreateTexture(64,64,1,0,D3DFMT_LE_X8R8G8B8,D3DPOOL_DEFAULT,&image,0))&&SUCCEEDED(device->CreatePixelShader((DWORD*)Melee360XfbPSWhite,&white)));
    device->SetDepthStencilSurface(0);device->SetRenderTarget(0,color);D3DVIEWPORT9 tile={0,0,64,64,0,1};device->SetViewport(&tile);
    device->SetVertexShader(filterVS);device->SetPixelShader(white);device->SetVertexDeclaration(filterDecl);float raster[4]={64,64,0,0};device->SetVertexShaderConstantF(0,raster,1);
    device->SetRenderState(D3DRS_ZENABLE,FALSE);device->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);device->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);device->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);device->SetRenderState(D3DRS_SCISSORTESTENABLE,FALSE);device->SetRenderState(D3DRS_COLORWRITEENABLE,15);device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);device->SetRenderState(D3DRS_MULTISAMPLEMASK,0xffff);
    device->Clear(0,0,D3DCLEAR_TARGET,0,1,0);const float triangle[3][4]={{-1,1,0,0},{1,1,1,0},{-1,-1,0,1}};check(SUCCEEDED(device->DrawPrimitiveUP(D3DPT_TRIANGLELIST,1,triangle,sizeof(triangle[0]))));
    device->Resolve(D3DRESOLVE_RENDERTARGET0|D3DRESOLVE_FRAGMENTS0123,0,image,0,0,0,0,1.f,0,0);
    bool ok=(readPixel(image,1,1)&0xffffff)==0xffffff&&(readPixel(image,63,63)&0xffffff)==0;unsigned partial=0;
    for(u32 i=1;i<63;++i){u32 pixel=readPixel(image,63-i,i)&0xffffff;if(pixel&&pixel!=0xffffff)++partial;}ok=ok&&partial>0;
    device->SetRenderTarget(0,oldTarget);device->SetDepthStencilSurface(oldDepth);saved->Apply();device->SetViewport(&viewport);device->BlockUntilIdle();
    saved->Release();oldTarget->Release();if(oldDepth)oldDepth->Release();color->Release();image->Release();white->Release();
    char trace[160];sprintf_s(trace,sizeof(trace),"AA native RGB565/4x MSAA: interior/background and %u partially covered edge pixels; passed=%d\n",partial,ok);Melee360Log(trace);return ok;
}
bool copyProbes(){
    srcX=srcY=0;srcW=dstW=(u16)width;srcH=dstH=(u16)height;scale=1;
    device->Clear(0,0,D3DCLEAR_TARGET,D3DCOLOR_XRGB(80,0,0),1,0);
    D3DRECT first={0,0,(LONG)width,1},third={0,2,(LONG)width,3};
    device->Clear(1,&first,D3DCLEAR_TARGET,D3DCOLOR_XRGB(40,0,0),1,0);device->Clear(1,&third,D3DCLEAR_TARGET,D3DCOLOR_XRGB(120,0,0),1,0);
    weights[0]=0;weights[1]=40;weights[2]=24;weights[3]=1;filteredCopy(buffers[1]);
    u32 middle=(readPixel(snapshot,1)>>16)&255,lower=(readPixel(snapshot,2)>>16)&255;
    u32 red=(middle*40+lower*24)/64;
    if(!rawProbe(buffers[1],1,red<<16,"vertical coefficients"))return false;
    weights[0]=weights[2]=0;weights[1]=64;
    const int levels[]={0,1,15,32,63,64,95,127,128,159,191,192,200,223,254,255};
    for(int gamma=0;gamma<3;++gamma){GXSetDispCopyGamma((GXGamma)gamma);
        for(int test=0;test<16;++test){int v=levels[test];device->Clear(0,0,D3DCLEAR_TARGET,D3DCOLOR_XRGB(v,v,v),1,0);
            device->Resolve(D3DRESOLVE_RENDERTARGET0,0,buffers[0],0,0,0,0,1.f,0,0);filteredCopy(buffers[1]);
            u32 base=readPixel(snapshot,1)&255;u32 expected=gamma?(u32)floor(pow(base/255.f,weights[3])*255+.5f):base;
            if(!rawProbe(buffers[1],1,expected*0x010101,"identity/gamma full range"))return false;
            if(!gamma&&(readPixel(buffers[0],1)&0xffffff)!=(readPixel(buffers[1],1)&0xffffff))return false;
        }
    }
    GXSetDispCopyGamma(GX_GM_1_0);
    weights[0]=126;weights[1]=189;weights[2]=126;device->Clear(0,0,D3DCLEAR_TARGET,D3DCOLOR_XRGB(255,255,255),1,0);filteredCopy(buffers[1]);if(!rawProbe(buffers[1],1,0xdddddd,"nine-bit wrap"))return false;weights[0]=weights[2]=0;weights[1]=64;
    GXSetDispCopySrc(0,0,(u16)width,242);u32 rows=GXSetDispCopyYScale(480.f/242.f);if(rows!=480)return false;GXSetDispCopyDst((u16)width,(u16)rows);
    const u32 selectedRows[]={0,1,121,241};const int shades[]={40,80,200,120};device->Clear(0,0,D3DCLEAR_TARGET,0,1,0);
    for(int i=0;i<4;++i){D3DRECT row={0,(LONG)selectedRows[i],(LONG)width,(LONG)selectedRows[i]+1};device->Clear(1,&row,D3DCLEAR_TARGET,D3DCOLOR_XRGB(shades[i],shades[i],shades[i]),1,0);}
    GXCopyDisp(buffers[1],GX_FALSE);const u32 outputRows[]={0,1,2,239,240,479};
    for(int i=0;i<6;++i){u32 row=(u32)floor((outputRows[i]+.5f)/scale);if(!rawProbe(buffers[1],outputRows[i],readPixel(snapshot,row),"242 to 480 quantized Y scale"))return false;}
    u32 preserved=readPixel(snapshot,121);device->Resolve(D3DRESOLVE_RENDERTARGET0|(aaMode?D3DRESOLVE_FRAGMENTS0123:0),0,snapshot,0,0,0,0,1.f,0,0);if(!rawProbe(snapshot,121,preserved,"clear=false EFB preservation"))return false;
    GXSetDispCopySrc(0,0,(u16)width,(u16)height);GXSetDispCopyYScale(1);GXSetDispCopyDst((u16)width,(u16)height);
    device->Clear(0,0,D3DCLEAR_TARGET,D3DCOLOR_XRGB(40,0,0),1,0);filteredCopy(buffers[0]);u32 old=readPixel(buffers[0],0);
    VISetNextFrameBuffer(buffers[0]);VIFlush();device->Clear(0,0,D3DCLEAR_TARGET,D3DCOLOR_XRGB(200,0,0),1,0);
    for(int parityTest=0;parityTest<2;++parityTest){fieldCopy=true;filteredCopy(buffers[1]);fieldCopy=false;
        u32 parity=VIGetNextField();const u32 boundaries[]={0,1,31,32,63,64,239,240,479,480,719};
        for(int i=0;i<11;++i){u32 row=boundaries[i];u32 expected=(row&1)==parity?readPixel(snapshot,row):old;if(!rawProbe(buffers[1],row,expected,"field/stripe boundary"))return false;}
        VIWaitForRetrace();
    }
    device->Clear(0,0,D3DCLEAR_TARGET,0,1,0);
    Melee360Log("VI/XFB: byte readback vertical coefficients, 48 full-range gamma cases and both field parities passed\n");return true;
}

int index(void* pointer){if(!pointer)return -1;for(int i=0;i<3;++i)if(pointer==buffers[i])return i;return -1;}
int swapFrame(){
    check(device&&running);IDirect3DTexture9* image=(IDirect3DTexture9*)Melee360VIActiveBuffer();
    check(index(image)>=0);if(Melee360VIBlack())image=blackTexture;
    device->SynchronizeToPresentationInterval();if(aaMode){D3DVIDEO_SCALER_PARAMETERS scaler={0};scaler.ScalerSourceRect.x2=xfbWidth;scaler.ScalerSourceRect.y2=xfbHeight;scaler.ScaledOutputWidth=outputWidth;scaler.ScaledOutputHeight=outputHeight;device->Swap(image,&scaler);}else device->Swap(image,0);++presents;return 1;
}
}
/* XFB addresses are registered native texture handles. The original HSD state
 * machine treats them as opaque buffers; CPU YUYV access is not exposed. */
extern "C" void Melee360XfbSetField(int value){fieldCopy=value!=0;}
extern "C" int Melee360XfbValid(void* pointer){return index(pointer)>=0;}
extern "C" int Melee360XfbModeSupported(const GXRenderModeObj* mode){
    return device&&mode&&(mode->aa!=GX_FALSE)==aaMode&&mode->fbWidth==width&&mode->efbHeight==height&&mode->xfbHeight==xfbHeight&&mode->viHeight==xfbHeight&&mode->viWidth==xfbWidth&&
        ((!mode->field_rendering&&mode->xFBmode==VI_XFBMODE_SF&&(mode->viTVmode&3)==VI_PROGRESSIVE)||(mode->xFBmode==VI_XFBMODE_DF&&(mode->viTVmode&3)==VI_INTERLACE));
}
extern "C" void GXSetDispCopySrc(u16 x,u16 y,u16 w,u16 h){check(device&&w&&h&&x+w<=width&&y+h<=height);srcX=x;srcY=y;srcW=w;srcH=h;}
extern "C" void GXSetDispCopyDst(u16 w,u16 h){check(device&&w&&h&&w<=xfbWidth&&h<=xfbHeight);dstW=w;dstH=h;}
extern "C" u32 GXSetDispCopyYScale(f32 value){check(device&&_finite(value)&&value>=1.f&&value<=256.f&&srcH);u32 inverse=(u32)(256.f/value)&0x1ff;check(inverse!=0);scale=256.f/inverse;return (u32)(srcH*scale);}
extern "C" void GXSetCopyClear(GXColor color,u32 z){check(z<=0xffffff);clearColor=color;clearDepth=z;}
extern "C" void GXSetCopyClamp(GXFBClamp clamp){check((clamp&~(GX_CLAMP_TOP|GX_CLAMP_BOTTOM))==0);copyClamp=clamp;}
extern "C" void GXSetCopyFilter(GXBool aa,const u8 samples[12][2],GXBool vertical,const u8 filter[7]){
    check(device&&samples&&filter&&(aa!=GX_FALSE)==aaMode);
    if(aa){check(aaColor!=0);for(int i=0;i<12;++i)for(int axis=0;axis<2;++axis)check(samples[i][axis]==GXNtsc480ProgAa.sample_pattern[i][axis]);}verticalFilter=vertical!=GX_FALSE;
    weights[0]=weights[2]=0;weights[1]=64;
    if(verticalFilter){for(int i=0;i<7;++i)check(filter[i]<=63);weights[0]=filter[0]+filter[1];weights[1]=filter[2]+filter[3]+filter[4];weights[2]=filter[5]+filter[6];}
}
extern "C" void GXSetDispCopyGamma(GXGamma gamma){check(gamma>=GX_GM_1_0&&gamma<=GX_GM_2_2);weights[3]=gamma==GX_GM_1_0?1.f:gamma==GX_GM_1_7?1.f/1.7f:1.f/2.2f;}
extern "C" void GXCopyDisp(void* pointer,GXBool clear){
    int slot=index(pointer);check(device&&slot>=0&&srcW&&srcH&&dstW&&dstH);
    if(verticalFilter||weights[3]!=1.f||fieldCopy||srcX||srcY||srcW!=width||srcH!=height||dstW!=width||dstH!=height||scale!=1.f)filteredCopy(buffers[slot]);else {check(SUCCEEDED(device->Resolve(D3DRESOLVE_RENDERTARGET0,0,buffers[slot],0,0,0,0,1.f,0,0)));check(SUCCEEDED(device->Resolve(D3DRESOLVE_RENDERTARGET0,0,history[slot],0,0,0,0,1.f,0,0)));}++copies;
    if(clear){DWORD mask=0,zWrite=0,flags=0;
        check(SUCCEEDED(device->GetRenderState(D3DRS_COLORWRITEENABLE,&mask))&&SUCCEEDED(device->GetRenderState(D3DRS_ZWRITEENABLE,&zWrite)));
        check(mask==0||mask==7||mask==15);if(Melee360GXRGBA6())check(mask==0||mask==15);if(mask)flags|=D3DCLEAR_TARGET;if(zWrite)flags|=D3DCLEAR_ZBUFFER;
        if(flags)check(SUCCEEDED(device->Clear(0,0,flags,Melee360GXPackEfbColor(D3DCOLOR_ARGB(clearColor.a,clearColor.r,clearColor.g,clearColor.b)),Melee360GXClearDepth(clearDepth),0)));
    }
}
extern "C" int Melee360XfbInit(IDirect3DDevice9* value){
    check(value&&!device);device=value;IDirect3DSurface9* target=0;D3DSURFACE_DESC desc;
    check(SUCCEEDED(device->GetRenderTarget(0,&target))&&target);HRESULT result=target->GetDesc(&desc);target->Release();check(SUCCEEDED(result));width=desc.Width;height=desc.Height;outputWidth=width;outputHeight=height;xfbWidth=width;xfbHeight=height;
    FILE* aaFlag=fopen("game:\\hsd-aa.flag","rb");aaMode=aaFlag!=0;if(aaFlag)fclose(aaFlag);
    if(aaMode){
        check(SUCCEEDED(device->GetRenderTarget(0,&originalColor))&&SUCCEEDED(device->GetDepthStencilSurface(&originalDepth)));
        width=GXNtsc480ProgAa.fbWidth;height=GXNtsc480ProgAa.efbHeight;xfbWidth=GXNtsc480ProgAa.fbWidth;xfbHeight=GXNtsc480ProgAa.xfbHeight;
        D3DSURFACE_PARAMETERS aaParams={0};
        check(SUCCEEDED(device->CreateRenderTarget(width,height,D3DFMT_R5G6B5,D3DMULTISAMPLE_4_SAMPLES,0,FALSE,&aaColor,&aaParams)));
        aaParams.Base=XGSurfaceSize(width,height,D3DFMT_R5G6B5,D3DMULTISAMPLE_4_SAMPLES);check(aaParams.Base+XGSurfaceSize(width,height,D3DFMT_D24S8,D3DMULTISAMPLE_4_SAMPLES)<1800);
        check(SUCCEEDED(device->CreateDepthStencilSurface(width,height,D3DFMT_D24S8,D3DMULTISAMPLE_4_SAMPLES,0,FALSE,&aaDepth,&aaParams)));
        device->SetDepthStencilSurface(0);device->SetRenderTarget(0,aaColor);device->SetDepthStencilSurface(aaDepth);GXSetViewport(0,0,(float)width,(float)height,0,1);GXSetPixelFmt(GX_PF_RGB565_Z16,GX_ZC_MID);device->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS,TRUE);device->SetRenderState(D3DRS_MULTISAMPLEMASK,0xffff);
        Melee360Log("HSD AA: original GXNtsc480ProgAa, native EFB 640x242 RGB565/4x, quantized MID Z16, XFB 640x480; GX sample pattern maps to fixed Xenon 4x\n");
    }
    FILE* flag=fopen("game:\\xfb-filter-probe.flag","rb");experimental=flag!=0;if(flag)fclose(flag);
    check(SUCCEEDED(device->CreateTexture(width,height,1,0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&snapshot,0)));
    D3DSURFACE_PARAMETERS params={0};params.Base=2000;
    check(SUCCEEDED(device->CreateRenderTarget(width,32,D3DFMT_A8R8G8B8,D3DMULTISAMPLE_NONE,0,FALSE,&stripe,&params)));
    D3DVERTEXELEMENT9 elements[]={{0,0,D3DDECLTYPE_FLOAT2,0,D3DDECLUSAGE_POSITION,0},{0,8,D3DDECLTYPE_FLOAT2,0,D3DDECLUSAGE_TEXCOORD,0},D3DDECL_END()};
    check(SUCCEEDED(device->CreateVertexShader((DWORD*)Melee360XfbVS,&filterVS))&&SUCCEEDED(device->CreatePixelShader((DWORD*)Melee360XfbPS,&filterPS))&&SUCCEEDED(device->CreateVertexDeclaration(elements,&filterDecl)));
    for(int i=0;i<2;++i)check(SUCCEEDED(device->CreateTexture(xfbWidth,xfbHeight,1,0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&history[i],0)));
    for(int i=0;i<2;++i)check(SUCCEEDED(device->CreateTexture(xfbWidth,xfbHeight,1,0,(D3DFORMAT)MAKESRGBFMT(D3DFMT_LE_X8R8G8B8),D3DPOOL_DEFAULT,&buffers[i],0)));
    check(SUCCEEDED(device->CreateTexture(xfbWidth,xfbHeight,1,0,(D3DFORMAT)MAKESRGBFMT(D3DFMT_LE_X8R8G8B8),D3DPOOL_DEFAULT,&blackTexture,0)));
    check(SUCCEEDED(device->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,0,1.f,0)));
    if(aaMode){srcX=srcY=0;srcW=(u16)width;srcH=(u16)height;dstW=(u16)xfbWidth;dstH=(u16)xfbHeight;GXSetDispCopyYScale((float)xfbHeight/height);
        filteredCopy(buffers[0]);device->BlockUntilIdle();D3DLOCKED_RECT source,destination;check(SUCCEEDED(buffers[0]->LockRect(0,&source,0,D3DLOCK_READONLY))&&SUCCEEDED(blackTexture->LockRect(0,&destination,0,0)));XGTEXTURE_DESC blackDesc;XGGetTextureDesc(blackTexture,0,&blackDesc);memcpy(destination.pBits,source.pBits,blackDesc.SlicePitch);blackTexture->UnlockRect(0);buffers[0]->UnlockRect(0);
    }else check(SUCCEEDED(device->Resolve(D3DRESOLVE_RENDERTARGET0,0,blackTexture,0,0,0,0,1.f,0,0)));
    HSD_VIStatus status=HSD_VIData.current.vi;status.gamma=GX_GM_1_0;status.vf=0;status.black=0;status.clear_clr.r=status.clear_clr.g=status.clear_clr.b=0;status.clear_clr.a=255;status.clear_z=0xffffff;status.update_clr=1;status.update_alpha=0;status.update_z=1;if(aaMode){status.rmode=GXNtsc480ProgAa;status.vf=1;}
    Melee360HsdCopyInvalidateState();HSD_VIInit(&status,buffers[0],buffers[1],0);
    HSD_VISetUserGXDrawDoneCallback(HSD_VIDrawDoneXFB);running=true;Melee360VISetPresenter(swapFrame);
    // Pending VI changes must not become visible until VIFlush.
    VISetNextFrameBuffer(buffers[0]);VIFlush();
    VISetNextFrameBuffer(buffers[1]);if(Melee360VIActiveBuffer()!=buffers[0])return 0;
    VIFlush();if(Melee360VIActiveBuffer()!=buffers[1])return 0;
    VISetBlack(TRUE);if(Melee360VIBlack())return 0;VIFlush();if(!Melee360VIBlack())return 0;
    VISetBlack(FALSE);if(!Melee360VIBlack())return 0;VIFlush();if(Melee360VIBlack())return 0;
    if(VIGetNextField()!=0)return 0;
    VISetNextFrameBuffer(buffers[0]);VIFlush();
    u32 before=VIGetRetraceCount();VIWaitForRetrace();if(VIGetRetraceCount()!=before+1)return 0;
    Melee360Log("VI/XFB: VIWaitForRetrace repeated a real synchronized native swap\n");
    Melee360Log("VI/XFB: staged buffer/black changes, atomic flush and progressive field probes passed\n");
    if(experimental&&!aaMode){
    GXRenderModeObj interlaced=status.rmode;interlaced.viTVmode=VI_TVMODE_NTSC_INT;interlaced.xFBmode=VI_XFBMODE_DF;
    VIConfigure(&interlaced);VIFlush();u32 fieldBefore=VIGetNextField();VIWaitForRetrace();if(VIGetNextField()==fieldBefore)return 0;
    if(!copyProbes()||!nativeAaProbe())return 0;
    VIConfigure(&status.rmode);VIFlush();
    Melee360Log("VI/XFB: interlaced VI field alternation through synchronized swaps passed\n");
    }
    if(HSD_VIData.nb_xfb!=2||copies!=((experimental&&!aaMode)?2u:1u))return 0;
    Melee360Log("VI/XFB: original HSD init, two GPU-backed buffers and original callbacks installed\n");return 1;
}
extern "C" void Melee360XfbBeginRender(void){if(aaMode){device->SetDepthStencilSurface(0);device->SetRenderTarget(0,aaColor);device->SetDepthStencilSurface(aaDepth);GXSetViewport(0,0,(float)width,(float)height,0,1);}}
extern "C" int Melee360XfbPresent(void){
    check(running);Melee360HsdCopyInvalidateState();HSD_VICopyXFBAsync(HSD_RP_SCREEN);GXWaitDrawDone();
    Melee360VIBeginFrame();int ok=swapFrame();Melee360VIEndFrame(ok);
    int displayed=HSD_VIGetXFBLastDrawDone();
    if(displayed<0||HSD_VIData.xfb[displayed].status!=HSD_VI_XFB_DISPLAY||HSD_VIData.drawdone.waiting)return 0;
    if(Melee360VIActiveBuffer()!=HSD_VIData.xfb[displayed].buffer)return 0;
    int freeBuffers=0;for(int i=0;i<2;++i)if(HSD_VIData.xfb[i].status==HSD_VI_XFB_FREE)++freeBuffers;
    if(freeBuffers!=1)return 0;
    if(aaMode&&copies==120)Melee360Log("HSD AA: 120 original screen copies; 242 to 480 filter/scale, original queues and synchronized scaler swaps passed\n");
    if(presents==120){char trace[160];sprintf_s(trace,sizeof(trace),"VI/XFB: 120 native swaps, copies=%u; original WAITDONE/NEXT/DISPLAY transitions passed\n",copies);Melee360Log(trace);}return ok;
}
extern "C" void Melee360XfbClose(void){
    if(!device)return;Melee360VISetPresenter(0);VISetPreRetraceCallback(0);VISetPostRetraceCallback(0);GXSetDrawDoneCallback(0);device->BlockUntilIdle();
    if(aaMode){device->SetDepthStencilSurface(0);device->SetRenderTarget(0,originalColor);device->SetDepthStencilSurface(originalDepth);GXSetPixelFmt(GX_PF_RGB8_Z24,GX_ZC_LINEAR);aaColor->Release();aaDepth->Release();originalColor->Release();originalDepth->Release();aaColor=aaDepth=originalColor=originalDepth=0;aaMode=false;}
    for(int i=0;i<2;++i){if(history[i])history[i]->Release();history[i]=0;}
    if(snapshot)snapshot->Release();snapshot=0;if(stripe)stripe->Release();stripe=0;if(filterVS)filterVS->Release();filterVS=0;if(filterPS)filterPS->Release();filterPS=0;if(filterDecl)filterDecl->Release();filterDecl=0;
    for(int i=0;i<3;++i){if(buffers[i])buffers[i]->Release();buffers[i]=0;}if(blackTexture)blackTexture->Release();blackTexture=0;device=0;running=false;
}
// Shared copy-engine settings, also consumed by texture copies.
extern "C" void Melee360GXCopySettings(u32* coefficients,u32* clamp,u32* color,u32* depth,int* aa){for(int i=0;i<3;++i)coefficients[i]=(u32)weights[i];*clamp=(u32)copyClamp;*color=D3DCOLOR_ARGB(clearColor.a,clearColor.r,clearColor.g,clearColor.b);*depth=clearDepth;*aa=aaMode?1:0;}
extern "C" int Melee360GXCopyFilterEnabled(void){return verticalFilter?1:0;}
