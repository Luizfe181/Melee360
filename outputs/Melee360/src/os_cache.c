#include <dolphin/os/OSCache.h>
/* Xenon SDK XM_CACHE_LINE_SIZE=128. Byte ranges must cover entire native lines. */
int Melee360CacheRange(u32 address,u32 size,u32* first,u32* last){if(!first||!last||!address||!size||size-1>0xffffffffu-address)return 0;*first=address&~127u;*last=(address+size-1)&~127u;return 1;}
#ifdef _XBOX
#include <ppcintrinsics.h>
#include <malloc.h>
#include <string.h>
static void cacheRange(void* pointer,u32 size,int store,int synchronize){u32 first,last,at;if(!Melee360CacheRange((u32)pointer,size,&first,&last))return;at=first;for(;;){if(store)__dcbst(0,(const void*)at);else __dcbf(0,(const void*)at);if(at==last)break;at+=128;}if(synchronize)__sync();}
void DCFlushRange(void* pointer,u32 size){cacheRange(pointer,size,0,1);}
void DCFlushRangeNoSync(void* pointer,u32 size){cacheRange(pointer,size,0,0);}
void DCStoreRange(void* pointer,u32 size){cacheRange(pointer,size,1,1);}
/* XDK exposes dcbf, not privileged dcbi. Flush+invalidate preserves unrelated
 * dirty bytes sharing a Xenon line. This is stronger than discard-only GC. */
void DCInvalidateRange(void* pointer,u32 size){cacheRange(pointer,size,0,1);}
int Melee360CacheProbe(void){unsigned char* p=(unsigned char*)_aligned_malloc(384,128);int ok;if(!p)return 0;memset(p,0x39,384);p[129]=0x82;p[257]=0x76;DCStoreRange(p+129,129);DCFlushRange(p+1,256);DCInvalidateRange(p+127,130);ok=p[0]==0x39&&p[129]==0x82&&p[257]==0x76&&p[383]==0x39;_aligned_free(p);return ok;}
#endif
