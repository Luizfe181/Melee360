#include "gx_native_submit.h"
#include "platform_log.h"
#include <stdio.h>
#include <string.h>

namespace {
const unsigned PageCount=8,PageBytes=1024*1024;
struct Page {IDirect3DVertexBuffer9* buffer;unsigned used;DWORD fence;bool protectedByFence;};
struct Stats {unsigned draws,rotations,waits,fallbacks;unsigned __int64 bytes;LONGLONG waitTicks;};
Page pages[PageCount];Stats stats;unsigned currentPage;IDirect3DDevice9* nativeDevice;
bool enabled;LARGE_INTEGER frequency;
unsigned vertexCount(D3DPRIMITIVETYPE type,unsigned count){
 switch(type){case D3DPT_TRIANGLELIST:return count<=0xffffffffu/3?count*3:0;
 case D3DPT_TRIANGLESTRIP:case D3DPT_TRIANGLEFAN:return count<=0xfffffffdu?count+2:0;
 case D3DPT_LINELIST:return count<=0xffffffffu/2?count*2:0;
 case D3DPT_LINESTRIP:return count<0xffffffffu?count+1:0;
 case D3DPT_POINTLIST:return count;default:return 0;}
}
}

int Melee360GXNativeOpen(IDirect3DDevice9* device){
 if(nativeDevice||!device)return 0;
 nativeDevice=device;currentPage=0;memset(pages,0,sizeof(pages));memset(&stats,0,sizeof(stats));QueryPerformanceFrequency(&frequency);
 enabled=GetFileAttributesA("game:\\gx-native-submit.flag")!=((DWORD)-1);
 if(!enabled)return 1;
 for(unsigned i=0;i<PageCount;++i){
  if(FAILED(device->CreateVertexBuffer(PageBytes,D3DUSAGE_WRITEONLY|D3DUSAGE_CPU_CACHED_MEMORY,0,D3DPOOL_DEFAULT,&pages[i].buffer,0))){
   Melee360Log("GX native submit: vertex buffer allocation FAILED\n");Melee360GXNativeClose();return 0;
  }
 }
 Melee360Log("GX native submit: enabled, eight 1 MiB fenced pages; legacy UP retained\n");return 1;
}

void Melee360GXNativeClose(){
 if(!nativeDevice)return;
 if(enabled){nativeDevice->BlockUntilIdle();nativeDevice->SetStreamSource(0,0,0,0);}
 for(unsigned i=0;i<PageCount;++i){if(pages[i].buffer)pages[i].buffer->Release();pages[i].buffer=0;}
 nativeDevice=0;enabled=false;
}

HRESULT Melee360GXNativeDraw(D3DPRIMITIVETYPE type,unsigned count,const void* data,unsigned stride){
 if(!nativeDevice||!data||!stride||!count)return E_INVALIDARG;
 if(!enabled)return nativeDevice->DrawPrimitiveUP(type,count,data,stride);
 unsigned vertices=vertexCount(type,count);
 if(!vertices||vertices>0xffffffffu/stride)return E_INVALIDARG;
 unsigned bytes=vertices*stride;
 // Oversized packets keep the known UP path; never split primitives or reorder.
 if(bytes>PageBytes){++stats.fallbacks;return nativeDevice->DrawPrimitiveUP(type,count,data,stride);}
 Page* page=&pages[currentPage];unsigned offset=((page->used+stride-1)/stride)*stride;
 if(offset>PageBytes||bytes>PageBytes-offset){
  // Fence covers every draw that referenced the retiring page, including
  // destination-alpha and early-Z passes. Do not overwrite GPU-live storage.
  page->fence=nativeDevice->InsertFence();page->protectedByFence=true;
  currentPage=(currentPage+1)%PageCount;page=&pages[currentPage];++stats.rotations;
  if(page->protectedByFence){
   if(nativeDevice->IsFencePending(page->fence)){LARGE_INTEGER begin,end;QueryPerformanceCounter(&begin);nativeDevice->BlockOnFence(page->fence);QueryPerformanceCounter(&end);stats.waitTicks+=end.QuadPart-begin.QuadPart;++stats.waits;}
   page->protectedByFence=false;
  }
  page->used=0;offset=0;
 }
 void* mapped=0;
 // DISCARD is unsupported on Xbox 360. NOOVERWRITE is backed by append-only
 // ranges and explicit fences at page reuse. Normal Unlock keeps cache flushes.
 page->buffer->Lock(offset,bytes,&mapped,0);
 if(!mapped)return E_FAIL;
 memcpy(mapped,data,bytes);page->buffer->Unlock();page->used=offset+bytes;
 nativeDevice->SetStreamSource(0,page->buffer,0,stride);
 HRESULT result=nativeDevice->DrawPrimitive(type,offset/stride,count);
 // Keep stream ownership local; UI/intro/probes use their own submission.
 nativeDevice->SetStreamSource(0,0,0,0);
 ++stats.draws;stats.bytes+=bytes;return result;
}

void Melee360GXNativeReport(unsigned frames){
 if(!enabled||!frames)return;
 char message[384];sprintf_s(message,sizeof(message),"GX native submit: frames=%u draws=%u bytes=%I64u rotations=%u waits=%u wait_ms=%.3f fallbacks=%u\n",frames,stats.draws,stats.bytes,stats.rotations,stats.waits,1000.0*stats.waitTicks/frequency.QuadPart/frames,stats.fallbacks);Melee360Log(message);
}