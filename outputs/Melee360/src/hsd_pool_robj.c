#include <sysdolphin/baselib/robj.h>
#include <math.h>
#include <string.h>
#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/bytecode.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/fobj.h>
#include <sysdolphin/baselib/id.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/list.h>
#include <sysdolphin/baselib/memory.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/object.h>
#include <sysdolphin/baselib/util.h>
#include <dolphin/mtx.h>
#include <dolphin/os.h>

HSD_ObjAllocData robj_alloc_data;
HSD_ObjAllocData rvalue_alloc_data;
float* arg_buf;
u32 arg_buf_size;
void HSD_RObjInitAllocData(void)
{
    HSD_ObjAllocInit(&robj_alloc_data, sizeof(HSD_RObj), 4);
    HSD_ObjAllocInit(&rvalue_alloc_data, sizeof(HSD_Rvalue), 4);
}
HSD_ObjAllocData* HSD_RObjGetAllocData(void)
{
    return &robj_alloc_data;
}
HSD_ObjAllocData* HSD_RvalueObjGetAllocData(void)
{
    return &rvalue_alloc_data;
}
void _HSD_RObjForgetMemory(void* low, void* high)
{
    if (low <= (void*) arg_buf && (void*) arg_buf < high) {
        arg_buf = 0U;
        arg_buf_size = 0U;
    }
}
