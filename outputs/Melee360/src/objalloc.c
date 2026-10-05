/* Compile the unchanged original allocator, then expose diagnostics over its
 * actual registry. The port reports registered pools, not uninitialized GX
 * classes. No object/render implementations are synthesized for reporting. */
#include <sysdolphin/baselib/objalloc.c>
#include <dolphin/os.h>
#include <sysdolphin/baselib/memory.h>
void HSD_ObjDumpStat(void){HSD_ObjAllocData* pool;unsigned count=0;for(pool=alloc_datas;pool;pool=pool->next){
    OSReport("objalloc: pool=%p size=%u using=%u freed=%u peak=%u\n",pool,pool->size,HSD_ObjAllocGetUsing(pool),HSD_ObjAllocGetFreed(pool),HSD_ObjAllocGetPeak(pool));++count;
}OSReport("objalloc: registered pools=%u\n",count);}
static unsigned dumpRows;
static void capture(const unsigned char* bytes,size_t length){if(length>=9&&!memcmp(bytes,"objalloc:",9))++dumpRows;}
int Melee360ObjDumpProbe(void){static HSD_ObjAllocData test;void *a,*b;unsigned before;HSD_ObjAllocInit(&test,16,16);a=HSD_ObjAlloc(&test);b=HSD_ObjAlloc(&test);if(!a||!b)return 0;before=test.used;dumpRows=0;HSD_SetReportCallback(capture);HSD_ObjDumpStat();HSD_SetReportCallback(NULL);
    if(!dumpRows||test.used!=before||test.peak!=2)return 0;HSD_ObjFree(&test,a);HSD_ObjFree(&test,b);return test.used==0&&test.peak==2;
}

/* Exercise the original pool discard callback with isolated registries.
 * Free objects remain backed by HSD allocations; forgetting the registry
 * alone does not release those allocations. Never discard runtime pools. */
extern u32 Melee360HsdHeapLiveAllocations(OSHeapHandle handle);
int Melee360ObjLifecycleProbe(void){
    HSD_ObjAllocData* savedRegistry=alloc_datas;
    objheap savedHeap=obj_heap;
    HSD_ObjAllocData isolated;
    OSHeapHandle heap=HSD_GetHeap();
    u32 before=Melee360HsdHeapLiveAllocations(heap);
    void* object;int ok;
    alloc_datas=NULL;HSD_ObjSetHeap(4096,NULL);
    HSD_ObjAllocInit(&isolated,32,32);
    object=HSD_ObjAlloc(&isolated);
    if(!object){alloc_datas=savedRegistry;obj_heap=savedHeap;return 0;}
    ok=isolated.used==1&&Melee360HsdHeapLiveAllocations(heap)==before+1;
    HSD_ObjFree(&isolated,object);
    ok=ok&&isolated.used==0&&isolated.free==1&&Melee360HsdHeapLiveAllocations(heap)==before+1;
    _HSD_ObjAllocForgetMemory(NULL,NULL);
    ok=ok&&alloc_datas==NULL&&Melee360HsdHeapLiveAllocations(heap)==before+1;
    /* This isolated test owns exactly one page allocated for one object. */
    HSD_Free(object);alloc_datas=savedRegistry;obj_heap=savedHeap;
    return ok&&Melee360HsdHeapLiveAllocations(heap)==before&&alloc_datas==savedRegistry;
}
