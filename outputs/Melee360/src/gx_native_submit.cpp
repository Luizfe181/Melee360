#include "gx_native_submit.h"
#include "platform_log.h"
#include <stdio.h>
#include <string.h>
namespace {
IDirect3DDevice9* nativeDevice;bool enabled;
unsigned draws;unsigned __int64 uploadedBytes;
unsigned vertexCount(D3DPRIMITIVETYPE type,unsigned count){
 switch(type){case D3DPT_TRIANGLELIST:return count<=0xffffffffu/3?count*3:0;
 case D3DPT_TRIANGLESTRIP:case D3DPT_TRIANGLEFAN:return count<=0xfffffffdu?count+2:0;
 case D3DPT_LINELIST:return count<=0xffffffffu/2?count*2:0;
 case D3DPT_LINESTRIP:return count<0xffffffffu?count+1:0;
 case D3DPT_POINTLIST:return count;default:return 0;}
}
}
int Melee360GXNativeOpen(IDirect3DDevice9* device){
 if(nativeDevice||!device)return 0;nativeDevice=device;draws=0;uploadedBytes=0;
 enabled=GetFileAttributesA("game:\\gx-native-submit.flag")!=((DWORD)-1);
 if(enabled)Melee360Log("GX native submit: enabled, XDK managed BeginVertices/EndVertices; legacy UP retained\n");return 1;
}
void Melee360GXNativeClose(){nativeDevice=0;enabled=false;}
HRESULT Melee360GXNativeDraw(D3DPRIMITIVETYPE type,unsigned count,const void* data,unsigned stride){
 if(!nativeDevice||!data||!stride||!count)return E_INVALIDARG;
 if(!enabled)return nativeDevice->DrawPrimitiveUP(type,count,data,stride);
 unsigned vertices=vertexCount(type,count);if(!vertices||vertices>0xffffffffu/stride)return E_INVALIDARG;
 unsigned bytes=vertices*stride;void* destination=0;
 // XDK owns command-buffer allocation, GPU lifetime and cache coherency.
 // Complete the write before EndVertices; never retain its returned pointer.
 HRESULT result=nativeDevice->BeginVertices(type,vertices,stride,&destination);
 if(FAILED(result))return result;
 memcpy(destination,data,bytes);result=nativeDevice->EndVertices();
 if(SUCCEEDED(result)){++draws;uploadedBytes+=bytes;}return result;
}
void Melee360GXNativeReport(unsigned frames){
 if(!enabled||!frames)return;char message[256];sprintf_s(message,sizeof(message),"GX native submit: frames=%u draws=%u bytes=%I64u mode=xdk-managed\n",frames,draws,uploadedBytes);Melee360Log(message);
}