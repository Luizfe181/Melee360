#include "gx_copy_codec.h"
extern "C" void Melee360GXCopySettings(u32*,u32*,u32*,u32*,int*);
extern "C" float Melee360GXClearDepth(u32);
extern "C" int Melee360GXCopyFilterEnabled(void);
extern "C" void DCStoreRange(void*,u32);
namespace {
struct TextureCopy {u16 x,y,w,h,dw,dh;GXTexFmt format;bool configured;};TextureCopy texCopy;
IDirect3DTexture9* copyReadback;unsigned copyReadbackWidth,copyReadbackHeight;D3DFORMAT copyReadbackFormat;std::vector<u8> copyReadbackRaw;
void closeCopyReadback(){if(copyReadback)copyReadback->Release();copyReadback=0;copyReadbackWidth=copyReadbackHeight=0;std::vector<u8>().swap(copyReadbackRaw);}
void textureCopyPixels(std::vector<u32>& out){
 GXProfileTimer timer(&gxProfile.copyTicks);if(gxProfile.enabled)++gxProfile.copies;
 // Explicit diagnostic only: omit readback/filter and substitute neutral pixels.
 if(gxProfile.noCopy){out.assign(texCopy.w*texCopy.h,0xff808080);return;}
 IDirect3DSurface9* target=0;D3DSURFACE_DESC desc;require(SUCCEEDED(device->GetRenderTarget(0,&target))&&target);HRESULT hr=target->GetDesc(&desc);target->Release();require(SUCCEEDED(hr));
 require(texCopy.x+texCopy.w<=desc.Width&&texCopy.y+texCopy.h<=desc.Height);
 require(desc.Format==D3DFMT_A8R8G8B8||desc.Format==(D3DFORMAT)MAKESRGBFMT(D3DFMT_A8R8G8B8)||desc.Format==D3DFMT_R5G6B5);
 static const bool pooled=GetFileAttributesA("game:\\gx-copy-pool.flag")!=((DWORD)-1);
 static const bool regionOnly=GetFileAttributesA("game:\\gx-copy-full-untile.flag")==((DWORD)-1);
 bool rgba6=Melee360GXRGBA6()!=0;D3DFORMAT readback=rgba6?D3DFMT_LE_A8R8G8B8:D3DFMT_LE_X8R8G8B8;IDirect3DTexture9* image=0;
 if(pooled){if(copyReadback&&(copyReadbackWidth!=desc.Width||copyReadbackHeight!=desc.Height||copyReadbackFormat!=readback))closeCopyReadback();
  if(!copyReadback){require(SUCCEEDED(device->CreateTexture(desc.Width,desc.Height,1,0,readback,D3DPOOL_DEFAULT,&copyReadback,0)));copyReadbackWidth=desc.Width;copyReadbackHeight=desc.Height;copyReadbackFormat=readback;}image=copyReadback;
 }else require(SUCCEEDED(device->CreateTexture(desc.Width,desc.Height,1,0,readback,D3DPOOL_DEFAULT,&image,0)));
 require(SUCCEEDED(device->Resolve(D3DRESOLVE_RENDERTARGET0|(desc.MultiSampleType!=D3DMULTISAMPLE_NONE?D3DRESOLVE_FRAGMENTS0123:0),0,image,0,0,0,0,1.f,0,0)));profileIdle();
 unsigned rawX=regionOnly?texCopy.x:0,rawY=regionOnly?(texCopy.y?texCopy.y-1:0):0;
 unsigned rawW=regionOnly?texCopy.w:desc.Width,rawBottom=regionOnly?texCopy.y+texCopy.h+1:desc.Height;if(rawBottom>desc.Height)rawBottom=desc.Height;
 unsigned rawH=rawBottom-rawY;
 D3DLOCKED_RECT lock;require(SUCCEEDED(image->LockRect(0,&lock,0,D3DLOCK_READONLY)));std::vector<u8> localRaw;std::vector<u8>& raw=pooled?copyReadbackRaw:localRaw;raw.resize(rawW*rawH*4);
 RECT region={(LONG)rawX,(LONG)rawY,(LONG)(rawX+rawW),(LONG)rawBottom};POINT origin={0,0};
 XGUntileTextureLevel(desc.Width,desc.Height,0,XGGetGpuFormat(readback),0,&raw[0],rawW*4,regionOnly?&origin:0,lock.pBits,regionOnly?&region:0);image->UnlockRect(0);if(!pooled)image->Release();
 if(gxProfile.enabled&&gxProfile.copies<=8){char trace[240];sprintf_s(trace,sizeof(trace),"GX copy layout: source=%ux%u rect=%u,%u/%ux%u format=%u raw_bytes=%u pooled=%u region=%u\n",desc.Width,desc.Height,texCopy.x,texCopy.y,texCopy.w,texCopy.h,(unsigned)texCopy.format,rawW*rawH*4,pooled?1:0,regionOnly?1:0);Melee360Log(trace);}
 GXDetailTimer filterTimer(&gxProfile.filterTicks);
 u32 weights[3],clamp,color,z;int aa;Melee360GXCopySettings(weights,&clamp,&color,&z,&aa);
 const int top=clamp&GX_CLAMP_TOP?texCopy.y:0,bottom=clamp&GX_CLAMP_BOTTOM?texCopy.y+texCopy.h-1:desc.Height-1;
 out.resize(texCopy.w*texCopy.h);
 for(u32 y=0;y<texCopy.h;++y)for(u32 x=0;x<texCopy.w;++x){u32 rgb[3]={0,0,0};
  for(int sample=0;sample<3;++sample){int row=(int)texCopy.y+y+sample-1;if(row<top)row=top;if(row>bottom)row=bottom;const u8* p=&raw[((row-rawY)*rawW+texCopy.x-rawX+x)*4];for(int c=0;c<3;++c){u32 channel=p[2-c];if(desc.Format==D3DFMT_R5G6B5)channel=c==1?(channel&252)|(channel>>6):(channel&248)|(channel>>5);rgb[c]+=channel*weights[sample];}}
  for(int c=0;c<3;++c){rgb[c]=(rgb[c]/64)&511;if(rgb[c]>255)rgb[c]=255;}
  // RGBA6 retains the six-bit-expanded alpha at the source row.
  u32 alpha=rgba6?raw[((texCopy.y+y-rawY)*rawW+texCopy.x-rawX+x)*4+3]:255;out[y*texCopy.w+x]=(alpha<<24)|(rgb[0]<<16)|(rgb[1]<<8)|rgb[2];
 }
}
}
extern "C" void GXSetTexCopySrc(u16 x,u16 y,u16 w,u16 h){require(device&&!__GXinBegin&&w&&h&&w<=1024&&h<=1024&&x<=1023&&y<=1023);texCopy.x=x;texCopy.y=y;texCopy.w=w;texCopy.h=h;}
extern "C" void GXSetTexCopyDst(u16 w,u16 h,GXTexFmt fmt,GXBool half){if(half||!Melee360GXCopyBytes(w,h,fmt)){char msg[120];sprintf_s(msg,sizeof(msg),"GX copy dst: w=%u h=%u fmt=%u half=%u\n",w,h,fmt,half);Melee360Log(msg);}require(device&&!__GXinBegin&&half==GX_FALSE&&Melee360GXCopyBytes(w,h,fmt));texCopy.dw=w;texCopy.dh=h;texCopy.format=fmt;texCopy.configured=true;}
extern "C" void GXCopyTex(void* destination,GXBool clear){
 require(device&&!__GXinBegin&&destination&&((u32)destination&31)==0&&texCopy.configured&&texCopy.w==texCopy.dw&&texCopy.h==texCopy.dh&&(clear==GX_FALSE||clear==GX_TRUE));
 std::vector<u32> pixels;textureCopyPixels(pixels);u32 bytes=Melee360GXCopyBytes(texCopy.dw,texCopy.dh,texCopy.format);
 require(Melee360EncodeGXCopy(&pixels[0],texCopy.dw,texCopy.dh,texCopy.format,(u8*)destination,bytes)!=0);DCStoreRange(destination,bytes);
 if(clear){u32 coefficients[3],clamp,color,z;int aa;Melee360GXCopySettings(coefficients,&clamp,&color,&z,&aa);DWORD mask=0,zWrite=0,flags=0;device->GetRenderState(D3DRS_COLORWRITEENABLE,&mask);device->GetRenderState(D3DRS_ZWRITEENABLE,&zWrite);require(Melee360GXRGBA6()?(mask==0||mask==15):(mask==0||mask==7||mask==15));color=Melee360GXPackEfbColor(color);if(mask)flags|=D3DCLEAR_TARGET;if(zWrite)flags|=D3DCLEAR_ZBUFFER;
  D3DRECT region={texCopy.x,texCopy.y,texCopy.x+texCopy.w,texCopy.y+texCopy.h};if(flags)require(SUCCEEDED(device->Clear(1,&region,flags,color,Melee360GXClearDepth(z),0)));
 }
}
extern "C" int Melee360GXTextureCopyProbe(void){
 require(device&&!__GXinBegin);IDirect3DStateBlock9* saved=0;IDirect3DSurface9 *oldTarget=0,*oldDepth=0;D3DVIEWPORT9 viewport;TextureCopy oldCopy=texCopy;
 require(SUCCEEDED(device->CreateStateBlock(D3DSBT_ALL,&saved))&&SUCCEEDED(saved->Capture()));device->GetRenderTarget(0,&oldTarget);device->GetDepthStencilSurface(&oldDepth);device->GetViewport(&viewport);
 u32 oldWeights[3],oldClamp,oldColor,oldZ;int aa;int oldFilterEnabled=Melee360GXCopyFilterEnabled();Melee360GXCopySettings(oldWeights,&oldClamp,&oldColor,&oldZ,&aa);
 const u8 identity[7]={0,0,0,64,0,0,0},filter[7]={16,0,32,0,0,16,0};GXSetCopyFilter(aa?GX_TRUE:GX_FALSE,GXNtsc480ProgAa.sample_pattern,GX_FALSE,identity);GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP|GX_CLAMP_BOTTOM));
 device->SetDepthStencilSurface(0);device->SetRenderState(D3DRS_ZENABLE,FALSE);device->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);device->SetRenderState(D3DRS_COLORWRITEENABLE,15);device->SetRenderState(D3DRS_SCISSORTESTENABLE,FALSE);
 bool ok=true;unsigned cases=0,pixelsChecked=0;u8* encoded=(u8*)_aligned_malloc(2048,32);require(encoded!=0);std::vector<u32> decoded(32*32);
 for(int targetKind=0;targetKind<2&&ok;++targetKind){D3DSURFACE_PARAMETERS params={0};params.Base=1800;IDirect3DSurface9* target=0;require(SUCCEEDED(device->CreateRenderTarget(64,64,targetKind?D3DFMT_R5G6B5:D3DFMT_A8R8G8B8,targetKind?D3DMULTISAMPLE_4_SAMPLES:D3DMULTISAMPLE_NONE,0,FALSE,&target,&params)));device->SetRenderTarget(0,target);
  device->Clear(0,0,D3DCLEAR_TARGET,0xff183c78,1,0);D3DRECT red={8,8,24,24},green={24,8,40,24},blue={8,24,24,40};device->Clear(1,&red,D3DCLEAR_TARGET,0xfff80000,1,0);device->Clear(1,&green,D3DCLEAR_TARGET,0xff00fc00,1,0);device->Clear(1,&blue,D3DCLEAR_TARGET,0xff0000f8,1,0);
  const u16 widths[]={4,7,17},heights[]={4,5,9};
  for(int shape=0;shape<3&&ok;++shape)for(u32 fmt=4;fmt<=6&&ok;++fmt){u32 w=widths[shape],h=heights[shape],bytes=Melee360GXCopyBytes(w,h,fmt);memset(encoded,0xCD,2048);GXSetTexCopySrc(7,7,(u16)w,(u16)h);GXSetTexCopyDst((u16)w,(u16)h,(GXTexFmt)fmt,GX_FALSE);GXCopyTex(encoded,GX_FALSE);ok=encoded[bytes]==0xCD&&Melee360DecodeGxTexture(encoded,bytes,w,h,fmt,0,0,0,&decoded[0],(u32)decoded.size());
   for(u32 y=0;y<h&&ok;++y)for(u32 x=0;x<w&&ok;++x){u32 atX=x+7,atY=y+7,want=atX>=8&&atX<24&&atY>=8&&atY<24?0xfff80000:atX>=24&&atX<40&&atY>=8&&atY<24?0xff00fc00:0xff183c78;
    u32 r=(want>>16)&255,g=(want>>8)&255,b=want&255;if(targetKind||fmt==4){r=(r&248)|(r>>5);g=(g&252)|(g>>6);b=(b&248)|(b>>5);}if(fmt==5){r=(r&248)|(r>>5);g=(g&248)|(g>>5);b=(b&248)|(b>>5);}want=0xff000000|(r<<16)|(g<<8)|b;
    if(decoded[y*w+x]!=want){char msg[180];sprintf_s(msg,sizeof(msg),"GX texture copy FAILED target=%d format=%u shape=%d xy=%u,%u actual=%08x wanted=%08x\n",targetKind,fmt,shape,x,y,decoded[y*w+x],want);Melee360Log(msg);ok=false;}++pixelsChecked;
   }++cases;
  }
  if(ok){
   device->Clear(0,0,D3DCLEAR_TARGET,0,1,0);const u32 levels[3]={40,80,200};
   for(int row=0;row<3;++row){D3DRECT rect={0,row,64,row+1};u32 shade=levels[row];device->Clear(1,&rect,D3DCLEAR_TARGET,0xff000000|shade*0x010101,1,0);}
   GXSetCopyFilter(aa?GX_TRUE:GX_FALSE,GXNtsc480ProgAa.sample_pattern,GX_TRUE,filter);GXSetTexCopySrc(0,1,4,1);GXSetTexCopyDst(4,1,GX_TF_RGBA8,GX_FALSE);
   for(int clampCase=0;clampCase<4&&ok;++clampCase){GXSetCopyClamp((GXFBClamp)clampCase);GXCopyTex(encoded,GX_FALSE);ok=Melee360DecodeGxTexture(encoded,64,4,1,6,0,0,0,&decoded[0],32*32);u32 expected[3]={0,0,0};
    for(int c=0;c<3;++c){u32 sums=0;for(int row=0;row<3;++row){u32 shade=levels[row];if(row==0&&(clampCase&GX_CLAMP_TOP))shade=levels[1];if(row==2&&(clampCase&GX_CLAMP_BOTTOM))shade=levels[1];if(targetKind)shade=c==1?(shade&252)|(shade>>6):(shade&248)|(shade>>5);sums+=shade*(row==1?2:1);}expected[c]=sums/4;}
    u32 want=0xff000000|(expected[0]<<16)|(expected[1]<<8)|expected[2];for(int k=0;k<4;++k){if(decoded[k]!=want){char msg[160];sprintf_s(msg,sizeof(msg),"GX texture copy filter FAILED target=%d clamp=%d actual=%08x wanted=%08x\n",targetKind,clampCase,decoded[k],want);Melee360Log(msg);ok=false;}++pixelsChecked;}++cases;
   }
   GXSetCopyFilter(aa?GX_TRUE:GX_FALSE,GXNtsc480ProgAa.sample_pattern,GX_FALSE,identity);GXSetCopyClamp((GXFBClamp)(GX_CLAMP_TOP|GX_CLAMP_BOTTOM));
  }
  if(ok){
   device->Clear(0,0,D3DCLEAR_TARGET,0xff183c78,1,0);GXColor copyClear={17,34,51,255};GXSetCopyClear(copyClear,0xffffff);GXSetTexCopySrc(0,0,4,4);GXSetTexCopyDst(4,4,GX_TF_RGBA8,GX_FALSE);
   GXCopyTex(encoded,GX_TRUE);ok=Melee360DecodeGxTexture(encoded,64,4,4,6,0,0,0,&decoded[0],32*32);for(int k=0;k<16;++k){ok=ok&&decoded[k]==(targetKind?0xff183c7b:0xff183c78);++pixelsChecked;}++cases;
   GXCopyTex(encoded,GX_FALSE);ok=ok&&Melee360DecodeGxTexture(encoded,64,4,4,6,0,0,0,&decoded[0],32*32);for(int k=0;k<16;++k){ok=ok&&decoded[k]==(targetKind?0xff102031:0xff112233);++pixelsChecked;}++cases;
   GXSetTexCopySrc(4,4,4,4);GXCopyTex(encoded,GX_FALSE);ok=ok&&Melee360DecodeGxTexture(encoded,64,4,4,6,0,0,0,&decoded[0],32*32);for(int k=0;k<16;++k){ok=ok&&decoded[k]==(targetKind?0xff183c7b:0xff183c78);++pixelsChecked;}++cases;
  }
  device->SetRenderTarget(0,oldTarget);target->Release();
 }
 _aligned_free(encoded);device->SetRenderTarget(0,oldTarget);device->SetDepthStencilSurface(oldDepth);saved->Apply();device->SetViewport(&viewport);saved->Release();oldTarget->Release();if(oldDepth)oldDepth->Release();texCopy=oldCopy;
 u8 restored[7];u32 a=oldWeights[0],b=oldWeights[1],c=oldWeights[2];restored[0]=(u8)(a>63?63:a);restored[1]=(u8)(a-restored[0]);restored[2]=(u8)(b>63?63:b);b-=restored[2];restored[3]=(u8)(b>63?63:b);restored[4]=(u8)(b-restored[3]);restored[5]=(u8)(c>63?63:c);restored[6]=(u8)(c-restored[5]);GXSetCopyFilter(aa?GX_TRUE:GX_FALSE,GXNtsc480ProgAa.sample_pattern,oldFilterEnabled?GX_TRUE:GX_FALSE,restored);GXSetCopyClamp((GXFBClamp)oldClamp);GXColor restoreColor={(u8)(oldColor>>16),(u8)(oldColor>>8),(u8)oldColor,(u8)(oldColor>>24)};GXSetCopyClear(restoreColor,oldZ);
 if(ok){char msg[160];sprintf_s(msg,sizeof(msg),"GX texture copy: %u GPU copies, %u decoded pixels, RGB565/RGB5A3/RGBA8, cropped padded tiles and AA resolve passed\n",cases,pixelsChecked);Melee360Log(msg);}return ok;
}

/* Called only with the dedicated linear, single-sample RGBA6 probe target. */
static bool rgba6CopyProbe(){
 TextureCopy oldCopy=texCopy;u32 weights[3],clamp,color,z;int aa;int filtered=Melee360GXCopyFilterEnabled();Melee360GXCopySettings(weights,&clamp,&color,&z,&aa);
 const u8 identity[7]={0,0,0,64,0,0,0},filter[7]={8,8,16,16,0,8,8};
 const u32 colors[3]={0x2e284060,0x895080a0,0xc9c8e0f0};u32 packed[3];for(int i=0;i<3;++i){packed[i]=Melee360GXPackEfbColor(colors[i]);D3DRECT rect={0,i,64,i+1};require(SUCCEEDED(device->Clear(1,&rect,D3DCLEAR_TARGET,packed[i],1,0)));}
 u8* encoded=(u8*)_aligned_malloc(64,32);require(encoded!=0);u32 decoded[4];bool ok=true;unsigned checks=0;
 GXSetColorUpdate(GX_TRUE);GXSetAlphaUpdate(GX_TRUE);GXSetTexCopySrc(0,1,4,1);GXSetTexCopyDst(4,1,GX_TF_RGBA8,GX_FALSE);GXSetCopyFilter(aa?GX_TRUE:GX_FALSE,GXNtsc480ProgAa.sample_pattern,GX_TRUE,filter);
 for(int c=0;c<4;++c){GXSetCopyClamp((GXFBClamp)c);GXCopyTex(encoded,GX_FALSE);ok=ok&&Melee360DecodeGxTexture(encoded,64,4,1,6,0,0,0,decoded,4);u32 expected=packed[1]&0xff000000;for(unsigned shift=0;shift<=16;shift+=8){u32 top=c&GX_CLAMP_TOP?packed[1]:packed[0],bottom=c&GX_CLAMP_BOTTOM?packed[1]:packed[2];u32 value=(((top>>shift)&255)+2*((packed[1]>>shift)&255)+((bottom>>shift)&255))/4;expected|=value<<shift;}for(int k=0;k<4;++k){ok=ok&&decoded[k]==expected;++checks;}}
 GXSetCopyFilter(aa?GX_TRUE:GX_FALSE,GXNtsc480ProgAa.sample_pattern,GX_FALSE,identity);GXSetCopyClamp((GXFBClamp)3);GXColor clear={17,34,51,137};GXSetCopyClear(clear,0xffffff);GXCopyTex(encoded,GX_TRUE);ok=ok&&Melee360DecodeGxTexture(encoded,64,4,1,6,0,0,0,decoded,4);for(int k=0;k<4;++k){ok=ok&&decoded[k]==packed[1];++checks;}
 GXCopyTex(encoded,GX_FALSE);ok=ok&&Melee360DecodeGxTexture(encoded,64,4,1,6,0,0,0,decoded,4);for(int k=0;k<4;++k){ok=ok&&decoded[k]==Melee360GXPackEfbColor(0x89112233);++checks;}
 GXSetTexCopySrc(0,0,4,1);GXCopyTex(encoded,GX_FALSE);ok=ok&&Melee360DecodeGxTexture(encoded,64,4,1,6,0,0,0,decoded,4);for(int k=0;k<4;++k){ok=ok&&decoded[k]==packed[0];++checks;}
 _aligned_free(encoded);texCopy=oldCopy;u8 restored[7];u32 a=weights[0],b=weights[1],c=weights[2];restored[0]=(u8)(a>63?63:a);restored[1]=(u8)(a-restored[0]);restored[2]=(u8)(b>63?63:b);b-=restored[2];restored[3]=(u8)(b>63?63:b);restored[4]=(u8)(b-restored[3]);restored[5]=(u8)(c>63?63:c);restored[6]=(u8)(c-restored[5]);GXSetCopyFilter(aa?GX_TRUE:GX_FALSE,GXNtsc480ProgAa.sample_pattern,filtered?GX_TRUE:GX_FALSE,restored);GXSetCopyClamp((GXFBClamp)clamp);GXColor restore={(u8)(color>>16),(u8)(color>>8),(u8)color,(u8)(color>>24)};GXSetCopyClear(restore,z);
 if(ok&&checks==28)Melee360Log("GX RGBA6 copy: 28 decoded pixels, RGB filtering with untouched alpha, four clamp modes and quantized regional clear passed\n");else Melee360Log("GX RGBA6 copy FAILED\n");return ok;
}



