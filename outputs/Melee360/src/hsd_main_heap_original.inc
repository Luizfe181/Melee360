#include <sysdolphin/baselib/tev.h>
/* Original initialize.c bodies; heap state shared with native allocator. */
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/fobj.h>
#include <sysdolphin/baselib/id.h>
#include <sysdolphin/baselib/list.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/objalloc.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/robj.h>
#include <sysdolphin/baselib/shadow.h>
#include <sysdolphin/baselib/state.h>
static void HSD_ObjInit(void);
void HSD_ObjInit(void)
{
    HSD_ListInitAllocData();
    HSD_AObjInitAllocData();
    HSD_FObjInitAllocData();
    HSD_IDInitAllocData();
    HSD_VecInitAllocData();
    HSD_MtxInitAllocData();
    HSD_RObjInitAllocData();
    HSD_RenderInitAllocData();
    HSD_ShadowInitAllocData();
    HSD_ZListInitAllocData();
}
OSHeapHandle HSD_CreateMainHeap(void* lo, void* hi)
{
    int i;
    void (*cb_table[])(void* lo, void* hi) = {
        _HSD_AObjForgetMemory,
        _HSD_DispForgetMemory,
        _HSD_IDForgetMemory,
        _HSD_ObjAllocForgetMemory,
        _HSD_RandForgetMemory,
        _HSD_RObjForgetMemory,
        NULL,
    };
    HSD_ASSERT(0, initializeHeap() && Melee360HsdMainHeapReady(lo,hi));
    hsdForgetClassLibrary("sysdolphin_base_library");
    HSD_ObjInit();
    for (i = 0; cb_table[i] != NULL; i++) {
        cb_table[i](primaryLo, primaryHi);
    }
    if (lo != NULL) {
        primaryLo = lo;
    }
    if (hi != NULL) {
        primaryHi = hi;
    }
    OSDestroyHeap(heapHandle);
    heapHandle =
        OSCreateHeap(primaryLo, primaryHi);
    HSD_ASSERT(0,heapHandle>=0);
    OSSetCurrentHeap(heapHandle);
    HSD_ObjSetHeap((uintptr_t) primaryHi -
                       (uintptr_t) primaryLo,
                   NULL);
    return heapHandle;
}
