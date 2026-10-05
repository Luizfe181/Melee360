#include "../compat/gameplay_boundary.h"
#include <melee/lb/lbheap.h>
#include <melee/lb/lbmemory.h>
#include <melee/lb/lbarchive.h>
#include <dolphin/ar.h>
#include <dolphin/dvd.h>
#include <sysdolphin/baselib/devcom.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/debug.h>
#include <string.h>
#include <stdio.h>
#include <melee/lb/lbaudio_ax.h>
#include <sysdolphin/baselib/initialize.h>
#include <dolphin/os/OSAlloc.h>
extern OSHeapHandle HSD_Synth_804D6018;
static u32 arStack[64];
void Melee360DVDPump(void);void Melee360ARAMPump(void);
int Melee360OriginalHeapBoot(void){
 unsigned char *p;u32 address,freeSize;int i;void *lo,*hi,*audioLo;
 HSD_GetNextArena(&lo,&hi);audioLo=(void*)((uintptr_t)hi-1024*1024);HSD_CreateMainHeap(lo,audioLo);HSD_Synth_804D6018=OSCreateHeap(audioLo,hi);if(HSD_Synth_804D6018<0)return 0;
 if(!ARCheckInit()){ARInit(arStack,64);ARQInit();}
 {FILE* match=fopen("game:\\original-match.flag","rb");if(match){fclose(match);OSReport("Original match: entering original audio initialization before logical ARAM heaps\n");lbAudioAx_8002838C();OSReport("Original match: original audio initialized; ARAM reserved\n");}}
 lbMemory_8001564C();lbHeap_80015F3C();
 /* Keep the original sequence/stay partitions outside the active HSD heap. */
 lbHeap_800158D0(LbHeapKind_Seq,0);lbHeap_800158D0(LbHeapKind_Stay,0);lbHeap_80015900();
 if(lbHeap_80015BB8(LbHeapKind_Hsd)!=LbHeapStatus_Create||lbHeap_80015BB8(LbHeapKind_ARAM)!=LbHeapStatus_Create||lbHeap_80015BB8(LbHeapKind_Seq)!=LbHeapStatus_Create||lbHeap_80015BB8(LbHeapKind_Stay)!=LbHeapStatus_Create)return 0;
 p=lbHeap_80015BD0(LbHeapKind_Hsd,96);if(!p)return 0;for(i=0;i<96;++i)p[i]=(u8)(i^0x63);for(i=0;i<96;++i)if(p[i]!=(u8)(i^0x63))return 0;lbHeap_80015CA8(LbHeapKind_Hsd,p);
 address=(u32)lbHeap_80015BD0(LbHeapKind_ARAM,64);if(address<ARGetBaseAddress()||address+64>ARGetSize())return 0;lbHeap_80015CA8(LbHeapKind_ARAM,(void*)address);
 /* Native AR stack and the original logical allocator are independent. */
 address=ARAlloc(32);if(ARFree(&freeSize)!=address||freeSize!=32)return 0;
 OSReport("Bootstrap heaps: original lbMemory/lbHeap sequence, Stay/HSD/ARAM partitions and allocation/free passed\n");return 1;
}
int Melee360OriginalCommonBoot(void);
int Melee360OriginalArchiveBoot(void){DVDInit();if(!Melee360OriginalCommonBoot())return 0;OSReport("Bootstrap common: original lbFile/lbArchive_LoadSymbols and Player/Fighter common globals bound; no Fighter created\n");return 1;}
