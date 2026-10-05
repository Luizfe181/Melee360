/* Original 640x480 EFB coordinates, resolved into a 4:3 native presentation. */
#include "scene_PS.h"
namespace {
IDirect3DSurface9 *matchColor,*matchDepth,*matchBack,*matchBackDepth;
IDirect3DTexture9* matchImage;IDirect3DVertexShader9* matchVS;IDirect3DPixelShader9* matchPS;IDirect3DVertexDeclaration9* matchDecl;
struct MatchQuad {float p[4],uv[2],color[4];};
}
extern "C" int Melee360MatchSurfaceInit(void){
 require(device);device->GetRenderTarget(0,&matchBack);device->GetDepthStencilSurface(&matchBackDepth);
 D3DSURFACE_PARAMETERS color={0},depth={0};depth.Base=240;
 const D3DVERTEXELEMENT9 elements[]={{0,0,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},{0,16,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},{0,24,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},D3DDECL_END()};
 return SUCCEEDED(device->CreateRenderTarget(640,480,D3DFMT_A8R8G8B8,D3DMULTISAMPLE_NONE,0,FALSE,&matchColor,&color))&&SUCCEEDED(device->CreateDepthStencilSurface(640,480,D3DFMT_D24S8,D3DMULTISAMPLE_NONE,0,FALSE,&matchDepth,&depth))&&SUCCEEDED(device->CreateTexture(640,480,1,0,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&matchImage,0))&&SUCCEEDED(device->CreateVertexShader((DWORD*)Melee360SceneVS,&matchVS))&&SUCCEEDED(device->CreatePixelShader((DWORD*)Melee360ScenePS,&matchPS))&&SUCCEEDED(device->CreateVertexDeclaration(elements,&matchDecl));
}
extern "C" int Melee360MatchSurfaceBegin(void){
 require(matchColor&&matchDepth);return SUCCEEDED(device->SetRenderTarget(0,matchColor))&&SUCCEEDED(device->SetDepthStencilSurface(matchDepth))&&SUCCEEDED(device->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER|D3DCLEAR_STENCIL,0xff000000,1,0));
}
extern "C" int Melee360MatchSurfacePresent(void){
 require(SUCCEEDED(device->Resolve(D3DRESOLVE_RENDERTARGET0,0,matchImage,0,0,0,0,1.f,0,0)));
 IDirect3DStateBlock9* state=0;require(SUCCEEDED(device->CreateStateBlock(D3DSBT_ALL,&state))&&SUCCEEDED(state->Capture()));
 require(SUCCEEDED(device->SetRenderTarget(0,matchBack))&&SUCCEEDED(device->SetDepthStencilSurface(matchBackDepth)));
 D3DSURFACE_DESC desc;matchBack->GetDesc(&desc);D3DVIEWPORT9 viewport={0,0,desc.Width,desc.Height,0,1};device->SetViewport(&viewport);
 device->SetRenderState(D3DRS_SCISSORTESTENABLE,FALSE);device->SetRenderState(D3DRS_COLORWRITEENABLE,15);device->SetRenderState(D3DRS_ZENABLE,FALSE);device->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);device->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);device->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);device->SetRenderState(D3DRS_STENCILENABLE,FALSE);
 require(SUCCEEDED(device->Clear(0,0,D3DCLEAR_TARGET,0xff000000,1,0)));device->SetVertexDeclaration(matchDecl);device->SetVertexShader(matchVS);device->SetPixelShader(matchPS);device->SetTexture(0,matchImage);
 device->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);device->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);device->SetSamplerState(0,D3DSAMP_MIPFILTER,D3DTEXF_NONE);
 const float c[4]={1,0,0,0};device->SetVertexShaderConstantF(0,c,1);float x=(4.f/3.f)*desc.Height/desc.Width,y=1;if(x>1){y=1/x;x=1;}
 const MatchQuad quad[6]={{{-x,y,0,1},{0,0},{1,1,1,1}},{{x,y,0,1},{1,0},{1,1,1,1}},{{x,-y,0,1},{1,1},{1,1,1,1}},{{-x,y,0,1},{0,0},{1,1,1,1}},{{x,-y,0,1},{1,1},{1,1,1,1}},{{-x,-y,0,1},{0,1},{1,1,1,1}}};
 HRESULT hr=device->DrawPrimitiveUP(D3DPT_TRIANGLELIST,2,quad,sizeof(MatchQuad));require(SUCCEEDED(state->Apply()));state->Release();
 IDirect3DSurface9* active=0;require(SUCCEEDED(device->GetRenderTarget(0,&active))&&active==matchBack);active->Release();
 static unsigned frame;static bool capture=GetFileAttributesA("game:\\original-render-capture.flag")!=((DWORD)-1);
 ++frame;if(capture&&(frame==1||frame==300||frame==600))require(Melee360GXCaptureMatch(10000+frame)!=0);
 return SUCCEEDED(hr);
}
