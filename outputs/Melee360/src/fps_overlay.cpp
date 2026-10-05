#include <xtl.h>
#include <stdio.h>
#include "scene_VS.h"
#include "scene_PS.h"
#include "menu_font.h"
#include "platform_log.h"
namespace {
char detail[256];
struct V {float clip[4],uv[2],color[4];};
IDirect3DTexture9 *font,*white;IDirect3DVertexShader9* vs;IDirect3DPixelShader9* ps;IDirect3DVertexDeclaration9* decl;
LARGE_INTEGER frequency,origin;unsigned int frames;char label[48]="FPS: --";bool reported,sampled;
bool texture(IDirect3DDevice9* d,unsigned int w,unsigned int h,IDirect3DTexture9** t){
 if(FAILED(d->CreateTexture(w,h,1,0,(D3DFORMAT)MAKESRGBFMT(D3DFMT_LIN_A8R8G8B8),D3DPOOL_DEFAULT,t,0)))return false;
 D3DLOCKED_RECT l;if(FAILED((*t)->LockRect(0,&l,0,0)))return false;
 for(unsigned int y=0;y<h;++y)for(unsigned int x=0;x<w;++x)((DWORD*)((char*)l.pBits+y*l.Pitch))[x]=w==1?0xffffffff:((DWORD)Melee360MenuFontAlpha[y*w+x]<<24)|0xffffff;
 return SUCCEEDED((*t)->UnlockRect(0));
}
void quad(V* out,float x,float y,float w,float h,float u,float v,float uw,float vh,float color,float alpha){
 const float p[6][4]={{x,y,u,v},{x+w,y,u+uw,v},{x,y+h,u,v+vh},{x,y+h,u,v+vh},{x+w,y,u+uw,v},{x+w,y+h,u+uw,v+vh}};
 for(int i=0;i<6;++i){memset(out+i,0,sizeof(V));out[i].clip[0]=p[i][0]/640-1;out[i].clip[1]=1-p[i][1]/360;out[i].clip[3]=1;out[i].uv[0]=p[i][2];out[i].uv[1]=p[i][3];for(int j=0;j<3;++j)out[i].color[j]=color;out[i].color[3]=alpha;}
}
}
void Melee360FpsClose(){if(font)font->Release();if(white)white->Release();if(vs)vs->Release();if(ps)ps->Release();if(decl)decl->Release();font=white=0;vs=0;ps=0;decl=0;}
bool Melee360FpsInit(IDirect3DDevice9* d){
 Melee360FpsClose();frames=0;reported=sampled=false;strcpy_s(label,sizeof(label),"FPS: --");
 D3DVERTEXELEMENT9 e[]={{0,0,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},{0,16,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},{0,24,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},D3DDECL_END()};
 bool ok=QueryPerformanceFrequency(&frequency)&&frequency.QuadPart>0&&QueryPerformanceCounter(&origin)&&SUCCEEDED(d->CreateVertexShader((DWORD*)Melee360SceneVS,&vs))&&SUCCEEDED(d->CreatePixelShader((DWORD*)Melee360ScenePS,&ps))&&SUCCEEDED(d->CreateVertexDeclaration(e,&decl))&&texture(d,256,144,&font)&&texture(d,1,1,&white);
 if(!ok)Melee360FpsClose();return ok;
}
void Melee360FpsPresented(){LARGE_INTEGER now;++frames;if(!QueryPerformanceCounter(&now))return;LONGLONG elapsed=now.QuadPart-origin.QuadPart;if(elapsed>=frequency.QuadPart){double seconds=(double)elapsed/frequency.QuadPart;double fps=frames/seconds;sprintf_s(label,sizeof(label),"FPS: %.1f  %.1f ms",fps,seconds*1000/frames);if(!sampled){Melee360Log("FPS overlay: first one-second presentation sample computed\n");sampled=true;}origin=now;frames=0;}}
void Melee360FpsDetail(const char* text){strncpy_s(detail,sizeof(detail),text?text:"",_TRUNCATE);}
bool Melee360FpsDraw(IDirect3DDevice9* d){
 if(!font)return false;IDirect3DVertexShader9* oldVs=0;IDirect3DPixelShader9* oldPs=0;IDirect3DVertexDeclaration9* oldDecl=0;IDirect3DBaseTexture9* oldTexture=0;D3DVIEWPORT9 oldViewport;
 d->GetVertexShader(&oldVs);d->GetPixelShader(&oldPs);d->GetVertexDeclaration(&oldDecl);d->GetTexture(0,&oldTexture);d->GetViewport(&oldViewport);
 const D3DRENDERSTATETYPE states[]={D3DRS_ZENABLE,D3DRS_ZWRITEENABLE,D3DRS_CULLMODE,D3DRS_ALPHABLENDENABLE,D3DRS_SRCBLEND,D3DRS_DESTBLEND,D3DRS_BLENDOP,D3DRS_SCISSORTESTENABLE,D3DRS_ALPHATESTENABLE,D3DRS_COLORWRITEENABLE};
 const DWORD values[]={FALSE,FALSE,D3DCULL_NONE,TRUE,D3DBLEND_SRCALPHA,D3DBLEND_INVSRCALPHA,D3DBLENDOP_ADD,FALSE,FALSE,15};DWORD old[10];for(int i=0;i<10;++i){d->GetRenderState(states[i],old+i);d->SetRenderState(states[i],values[i]);}
 D3DVIEWPORT9 viewport=oldViewport;IDirect3DSurface9* target=0;D3DSURFACE_DESC desc;if(SUCCEEDED(d->GetRenderTarget(0,&target))&&target){target->GetDesc(&desc);viewport.Width=desc.Width;viewport.Height=desc.Height;target->Release();}viewport.X=viewport.Y=0;viewport.MinZ=0;viewport.MaxZ=1;d->SetViewport(&viewport);d->SetVertexShader(vs);d->SetPixelShader(ps);d->SetVertexDeclaration(decl);
 float constants[4];d->GetVertexShaderConstantF(0,constants,1);const float overlayConstants[4]={1,0,0,0};d->SetVertexShaderConstantF(0,overlayConstants,1);
 char text[320];sprintf_s(text,sizeof(text),"%s%s%s",label,detail[0]?"\n":"",detail);
 V box[6],letters[320*6];unsigned int count=(unsigned int)strlen(text),rows=1,width=0,col=0,glyphs=0,row=0;
 for(unsigned i=0;i<count;++i){if(text[i]=='\n'){if(col>width)width=col;col=0;++rows;}else ++col;}if(col>width)width=col;
 quad(box,12,12,width*11.f+16,rows*24.f+8,0,0,1,1,0,.75f);d->SetTexture(0,white);bool ok=SUCCEEDED(d->DrawPrimitiveUP(D3DPT_TRIANGLELIST,2,box,sizeof(V)));col=0;
 for(unsigned int i=0;i<count;++i){if(text[i]=='\n'){++row;col=0;continue;}unsigned int c=(unsigned char)text[i]-32;if(c>=96)c='?'-32;quad(letters+glyphs*6,20+col*11.f,16+row*24.f,16,24,(c%16)/16.f,(c/16)/6.f,1/16.f,1/6.f,1,1);++glyphs;++col;}
 d->SetTexture(0,font);ok=SUCCEEDED(d->DrawPrimitiveUP(D3DPT_TRIANGLELIST,glyphs*2,letters,sizeof(V)))&&ok;
 d->SetVertexShaderConstantF(0,constants,1);d->SetTexture(0,oldTexture);d->SetVertexShader(oldVs);d->SetPixelShader(oldPs);d->SetVertexDeclaration(oldDecl);d->SetViewport(&oldViewport);for(int i=0;i<10;++i)d->SetRenderState(states[i],old[i]);
 if(oldTexture)oldTexture->Release();if(oldVs)oldVs->Release();if(oldPs)oldPs->Release();if(oldDecl)oldDecl->Release();if(ok&&!reported){Melee360Log("FPS overlay: first draw submitted\n");reported=true;}return ok;
}
