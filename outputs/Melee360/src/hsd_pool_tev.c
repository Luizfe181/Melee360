#include <sysdolphin/baselib/tev.h>
#include <string.h>
#include <sysdolphin/baselib/debug.h>
#include <dolphin/gx.h>

HSD_ObjAllocData render_alloc_data;
HSD_ObjAllocData tevreg_alloc_data;
HSD_ObjAllocData chan_alloc_data;
void HSD_RenderInitAllocData(void)
{
    HSD_ObjAllocInit(&render_alloc_data, 28, 4);
    HSD_ObjAllocInit(&tevreg_alloc_data, 20, 4);
    HSD_ObjAllocInit(&chan_alloc_data, 48, 4);
}
HSD_ObjAllocData* HSD_RenderGetAllocData(void)
{
    return &render_alloc_data;
}
HSD_ObjAllocData* HSD_TevRegGetAllocData(void)
{
    return &tevreg_alloc_data;
}
HSD_ObjAllocData* HSD_ChanGetAllocData(void)
{
    return &chan_alloc_data;
}
