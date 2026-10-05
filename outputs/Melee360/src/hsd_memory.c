#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/initialize.h>
#include <sysdolphin/baselib/debug.h>
#include <dolphin/os/OSAlloc.h>
#include <stdlib.h>
#define HSD_MEMORY_BUDGET (64u * 1024u * 1024u)
static void* arenaBacking;
static OSHeapHandle heapHandle=-1;
static void* primaryLo;
static void* primaryHi;
static void* secondaryLo;
static void* secondaryHi;
typedef struct {OSHeapHandle handle;u32 live;int registered;} HeapOwnership;
static HeapOwnership ownership[4];
extern int Melee360OSHeapAllocationState(OSHeapHandle handle);
static int ownerIndex(OSHeapHandle handle,int create){int i,empty=-1;for(i=0;i<4;++i){if(ownership[i].registered&&ownership[i].handle==handle)return i;if(!ownership[i].registered&&empty<0)empty=i;}if(create&&empty>=0){ownership[empty].handle=handle;ownership[empty].live=0;ownership[empty].registered=1;return empty;}return -1;}
int Melee360HsdHeapCanReclaim(OSHeapHandle handle){int token=OSDisableInterrupts(),index=ownerIndex(handle,0);int result=index>=0&&ownership[index].live==0&&handle!=heapHandle&&Melee360OSHeapAllocationState(handle)==0;OSRestoreInterrupts(token);return result;}
u32 Melee360HsdHeapLiveAllocations(OSHeapHandle handle){int token=OSDisableInterrupts(),index=ownerIndex(handle,0);u32 result=index>=0?ownership[index].live:0;OSRestoreInterrupts(token);return result;}
typedef struct {OSHeapHandle owner;u32 magic;u32 reserved[6];} AllocationHeader;
#define ALLOCATION_MAGIC 0x48333630u
/* Runtime owns this arena. Do not reinitialize OSInitAlloc while live. */
static int initializeHeap(void){
    uintptr_t aligned;void* start;
    if(heapHandle>=0)return 1;
    arenaBacking=malloc(HSD_MEMORY_BUDGET+31);
    if(!arenaBacking)return 0;
    aligned=((uintptr_t)arenaBacking+31)&~31u;
    start=OSInitAlloc((void*)aligned,(void*)(aligned+HSD_MEMORY_BUDGET),4);
    secondaryLo=(void*)(aligned+HSD_MEMORY_BUDGET-512*1024);
    secondaryHi=(void*)(aligned+HSD_MEMORY_BUDGET);
    primaryLo=start;primaryHi=secondaryLo;heapHandle=OSCreateHeap(primaryLo,primaryHi);
    HSD_ASSERT(0,heapHandle>=0);
    HSD_ASSERT(0,ownerIndex(heapHandle,1)>=0);OSSetCurrentHeap(heapHandle);
    return 1;
}
void* HSD_MemAlloc(ssize_t size){
    AllocationHeader* pointer;int token;
    if(size<=0||(u32)size>HSD_MEMORY_BUDGET-64)return NULL;
    token=OSDisableInterrupts();
    pointer=initializeHeap()?OSAllocFromHeap(heapHandle,(u32)size+sizeof(*pointer)):NULL;
    if(pointer){int index=ownerIndex(heapHandle,1);HSD_ASSERT(0,index>=0&&ownership[index].live!=0xffffffffu);ownership[index].live++;pointer->owner=heapHandle;pointer->magic=ALLOCATION_MAGIC;}
    OSRestoreInterrupts(token);return pointer?(void*)(pointer+1):NULL;
}
void HSD_Free(void* pointer){
    AllocationHeader* header;int token;if(!pointer)return;
    token=OSDisableInterrupts();header=((AllocationHeader*)pointer)-1;
    HSD_ASSERT(0,header->magic==ALLOCATION_MAGIC);{int index=ownerIndex(header->owner,0);HSD_ASSERT(0,index>=0&&ownership[index].live>0);ownership[index].live--;}header->magic=0;
    OSFreeToHeap(header->owner,header);OSRestoreInterrupts(token);
}
void HSD_SetHeap(OSHeapHandle handle){int token=OSDisableInterrupts();
    HSD_ASSERT(0,initializeHeap()&&handle>=0&&OSCheckHeap(handle)>=0);
    HSD_ASSERT(0,ownerIndex(handle,1)>=0);heapHandle=handle;OSSetCurrentHeap(handle);OSRestoreInterrupts(token);
}
int Melee360HsdHeapProbe(void){OSHeapHandle original=HSD_GetHeap(),temporary;
    unsigned char *old,*current;long before;u32 originalLive=Melee360HsdHeapLiveAllocations(original);int ok;
    temporary=OSCreateHeap(secondaryLo,secondaryHi);
    if(temporary<0)return 0;before=OSCheckHeap(original);
    old=HSD_MemAlloc(256);if(!old){OSDestroyHeap(temporary);return 0;}old[0]=0x31;old[255]=0x79;ok=Melee360HsdHeapLiveAllocations(original)==originalLive+1&&!Melee360HsdHeapCanReclaim(original);
    HSD_SetHeap(temporary);current=HSD_MemAlloc(64);
    ok=ok&&current&&Melee360HsdHeapLiveAllocations(temporary)==1&&!Melee360HsdHeapCanReclaim(original)&&!Melee360HsdHeapCanReclaim(temporary)&&old[0]==0x31&&old[255]==0x79&&HSD_GetHeap()==temporary&&__OSCurrHeap==temporary;
    HSD_Free(old);HSD_Free(current);ok=ok&&OSCheckHeap(original)==before;
    HSD_SetHeap(original);ok=ok&&Melee360HsdHeapCanReclaim(temporary)&&Melee360HsdHeapLiveAllocations(original)==originalLive;OSDestroyHeap(temporary);ok=ok&&!Melee360HsdHeapCanReclaim(temporary);
    return ok&&HSD_GetHeap()==original&&__OSCurrHeap==original;
}
OSHeapHandle HSD_GetHeap(void){
    int token=OSDisableInterrupts();initializeHeap();OSRestoreInterrupts(token);
    return heapHandle;
}

/* The port's primary HSD arena, not the 512 KiB secondary probe region. */
void HSD_GetNextArena(void** lo,void** hi){int token=OSDisableInterrupts();HSD_ASSERT(0,lo&&hi&&initializeHeap());*lo=primaryLo;*hi=primaryHi;OSRestoreInterrupts(token);}
int Melee360HsdArenaOwnershipProbe(void){void* lo;void* hi;OSHeapHandle handle=HSD_GetHeap();u32 before=Melee360HsdHeapLiveAllocations(handle);unsigned char* data;HSD_GetNextArena(&lo,&hi);if(!lo||!hi||(uintptr_t)hi<=(uintptr_t)lo)return 0;data=HSD_MemAlloc(33);if(!data)return 0;data[0]=0x63;data[32]=0xa7;{int ok=(uintptr_t)data>=(uintptr_t)lo&&(uintptr_t)data+33<=(uintptr_t)hi&&Melee360HsdHeapLiveAllocations(handle)==before+1&&!Melee360HsdHeapCanReclaim(handle)&&data[0]==0x63&&data[32]==0xa7;HSD_Free(data);return ok&&Melee360HsdHeapLiveAllocations(handle)==before;}}

/* Reset is authorized only with no live native or original allocations.
 * This protects port-owned asset pointers that original forget callbacks
 * cannot discover. Replacement bounds must remain inside the owned arena. */
int Melee360HsdMainHeapReady(void* lo,void* hi){
    uintptr_t low=(uintptr_t)(lo?lo:primaryLo),high=(uintptr_t)(hi?hi:primaryHi);
    int index=ownerIndex(heapHandle,0);
    return heapHandle>=0&&index>=0&&ownership[index].live==0&&Melee360OSHeapAllocationState(heapHandle)==0&&
        low>=(uintptr_t)primaryLo&&high<=(uintptr_t)primaryHi&&high>low&&high-low>=4096&&!(low&31)&&!(high&31);
}
#include "hsd_main_heap_original.inc"
int Melee360HsdMainHeapBoot(void){
    OSHeapHandle first=HSD_GetHeap(),second;void* lo;void* hi;unsigned char* bytes;int ok;
    HSD_GetNextArena(&lo,&hi);if(!Melee360HsdMainHeapReady(lo,hi))return 0;
    second=HSD_CreateMainHeap(lo,hi);if(second<0||HSD_GetHeap()!=second||__OSCurrHeap!=second)return 0;
    bytes=HSD_MemAlloc(96);if(!bytes)return 0;bytes[0]=0x42;bytes[95]=0x19;
    ok=!Melee360HsdMainHeapReady(lo,hi)&&bytes[0]==0x42&&bytes[95]==0x19;HSD_Free(bytes);
    ok=ok&&Melee360HsdMainHeapReady(lo,hi)&&!Melee360HsdMainHeapReady((void*)((uintptr_t)lo+1),hi)&&!Melee360HsdMainHeapReady(hi,lo);
    (void)first;return ok;
}
