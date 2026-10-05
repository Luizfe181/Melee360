#include <sysdolphin/baselib/aobj.h>
#include <math.h>
#include <stdarg.h>
#include <string.h>
#include <sysdolphin/baselib/cobj.h> // IWYU pragma: keep
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/fog.h>
#include <sysdolphin/baselib/id.h>
#include <sysdolphin/baselib/jobj.h>
#include <sysdolphin/baselib/list.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/robj.h>
#include <sysdolphin/baselib/tobj.h>
#include <sysdolphin/baselib/wobj.h>

HSD_ObjAllocData aobj_alloc_data;
HSD_SList* endcallback_list;
void HSD_AObjInitAllocData(void)
{
    HSD_ObjAllocInit(&aobj_alloc_data, sizeof(HSD_AObj), 4);
}
HSD_ObjAllocData* HSD_AObjGetAllocData(void)
{
    return &aobj_alloc_data;
}
void _HSD_AObjForgetMemory(void* low, void* high)
{
    endcallback_list = NULL;
}
