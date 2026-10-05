#include <sysdolphin/baselib/mtx.h>
#include <math.h>
#include <sysdolphin/baselib/debug.h>

HSD_ObjAllocData HSD_Mtx_804C2310;
HSD_ObjAllocData HSD_Mtx_804C233C;
void HSD_VecInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_VecGetAllocData(), sizeof(Vec), 4);
}
HSD_ObjAllocData* HSD_VecGetAllocData(void)
{
    return &HSD_Mtx_804C2310;
}
void HSD_MtxInitAllocData(void)
{
    HSD_ObjAllocInit(HSD_MtxGetAllocData(), sizeof(Mtx), 4);
}
HSD_ObjAllocData* HSD_MtxGetAllocData(void)
{
    return &HSD_Mtx_804C233C;
}
