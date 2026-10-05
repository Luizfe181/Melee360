extern "C" int Melee360OpeningAudioTime(unsigned int*);
#include <xtl.h>
#include "intro_VS.h"
#include "intro_PS.h"
#include <stdlib.h>
#include <stdio.h>
#include "intro_video.h"
#include "intro_stream.h"
#include "mth_decode.h"
#include "platform_log.h"
static IDirect3DTexture9* texture;
static IDirect3DVertexShader9* vs;
static IDirect3DPixelShader9* ps;
static IDirect3DVertexDeclaration9* declaration;
static unsigned int* pixels;
static DWORD startTime;static bool audioClockReported;
static bool running,finished,reportedDraw,reportedAdvance;
static DWORD decodeCount,decodeTime,uploadTime,lastReport;
static unsigned int width,height;
bool Melee360IntroVideoFinished() {return finished;}
void Melee360IntroVideoClose()
{
    if(texture) texture->Release(); texture=NULL;
    if(vs) vs->Release(); vs=NULL;
    if(ps) ps->Release(); ps=NULL;
    if(declaration) declaration->Release(); declaration=NULL;
    free(pixels); pixels=NULL;
    running=finished=reportedDraw=reportedAdvance=false;
    decodeCount=decodeTime=uploadTime=lastReport=0;
}
static bool upload()
{
    unsigned int bytes;
    const unsigned char* frame=Melee360IntroFirstFrame(&bytes);
    DWORD decodeStart=GetTickCount();
    if(!Melee360DecodeMth(frame,bytes,pixels,width,height)) {
        Melee360Log("Intro: portable frame decode FAILED\n");return false;
    }
    DWORD uploadStart=GetTickCount();
    decodeTime+=uploadStart-decodeStart;
    D3DLOCKED_RECT lock;
    if(FAILED(texture->LockRect(0,&lock,NULL,0))) return false;
    for(unsigned int y=0;y<height;++y) memcpy((char*)lock.pBits+y*lock.Pitch,pixels+y*width,width*4);
    bool result=SUCCEEDED(texture->UnlockRect(0));
    uploadTime+=GetTickCount()-uploadStart;
    ++decodeCount;
    return result;
}
bool Melee360IntroVideoInit(IDirect3DDevice9* device)
{
    Melee360IntroVideoClose();
    HRESULT hr=device->CreateVertexShader(Melee360IntroVS,&vs);
    if(FAILED(hr)) {Melee360IntroVideoClose();return false;}
    hr=device->CreatePixelShader(Melee360IntroPS,&ps);
    const D3DVERTEXELEMENT9 elements[]={
        {0,0,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
        {0,8,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},D3DDECL_END()};
    if(FAILED(hr) || FAILED(device->CreateVertexDeclaration(elements,&declaration)) ||
       FAILED(device->CreateTexture(Melee360MovieWidth(),Melee360MovieHeight(),1,0,(D3DFORMAT)MAKESRGBFMT(D3DFMT_LIN_A8R8G8B8),D3DPOOL_DEFAULT,&texture,NULL))) {
        Melee360IntroVideoClose();return false;
    }
    width=Melee360MovieWidth();height=Melee360MovieHeight();pixels=(unsigned int*)malloc(width*height*4);
    if(!pixels || !upload()) {Melee360IntroVideoClose();return false;}
    startTime=GetTickCount();running=true;audioClockReported=false;
    lastReport=startTime;
    Melee360Log("Intro: portable decoder ready; first frame uploaded to Xbox texture\n");
    return true;
}
bool Melee360IntroVideoDraw(IDirect3DDevice9* device)
{
    if(!running) return false;
    if(GetTickCount()-lastReport>=5000 && decodeCount) {
        char message[160];
        sprintf_s(message,sizeof(message),"Intro perf: frames=%lu decode_avg_ms=%.2f upload_avg_ms=%.2f movie_frame=%u\n",
            decodeCount,(double)decodeTime/decodeCount,(double)uploadTime/decodeCount,Melee360IntroFrameIndex());
        Melee360Log(message);
        decodeCount=decodeTime=uploadTime=0;lastReport=GetTickCount();
    }
    unsigned int elapsed=GetTickCount()-startTime;if(Melee360OpeningAudioTime(&elapsed)&&!audioClockReported){Melee360Log("Movie audio: video timing follows consumed HPS samples\n");audioClockReported=true;}const DWORD desired=(DWORD)(((ULONGLONG)elapsed*30)/1000);
    if(!finished && desired>Melee360IntroFrameIndex()) {
        int result=1;
        // Skip stale compressed frames when decode falls behind the movie clock.
        while(Melee360IntroFrameIndex()<desired && result>0) result=Melee360IntroAdvance();
        if(result<0) {Melee360Log("Intro: movie frame read FAILED\n");running=false;return false;}
        if(!upload()) {running=false;return false;}
        if(result==0) {finished=true;Melee360Log("Intro: movie video stream completed\n");}
        if(Melee360IntroFrameIndex()>=30 && !reportedAdvance) {
            Melee360Log("Intro: video advanced beyond frame 30\n");reportedAdvance=true;
        }
    }
    struct Vertex{float x,y,u,v;};
    device->Clear(0,NULL,D3DCLEAR_TARGET,D3DCOLOR_XRGB(0,0,0),1.f,0);
    const Vertex vertices[]={{-.75f,1,0,0},{.75f,1,1,0},{-.75f,-1,0,1},{.75f,-1,1,1}};
    device->SetVertexDeclaration(declaration);device->SetVertexShader(vs);device->SetPixelShader(ps);
    device->SetTexture(0,texture);
    device->SetRenderState(D3DRS_ZENABLE,FALSE);device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
    device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
    device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
    device->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);
    device->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);
    HRESULT hr=device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,vertices,sizeof(Vertex));
    if(FAILED(hr)) {Melee360Log("Intro: textured draw FAILED\n");running=false;return false;}
    if(!reportedDraw) {Melee360Log("Intro: first textured draw submitted\n");reportedDraw=true;}
    return true;
}
