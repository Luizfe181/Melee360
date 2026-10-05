#include <sysdolphin/baselib/displayfunc.h>
#include <string.h>
#include <sysdolphin/baselib/cobj.h>
#include <sysdolphin/baselib/dobj.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/mobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/objalloc.h>
#include <sysdolphin/baselib/pobj.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/util.h>
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

typedef struct _HSD_ZList {
    Mtx pmtx;
    MtxPtr vmtx;
    HSD_JObj* jobj;
    u32 rendermode;

    struct _HSD_ZList_sort {
        struct _HSD_ZList* texedge;
        struct _HSD_ZList* xlu;
    } sort;

    struct _HSD_ZList* next;
} HSD_ZList;

HSD_ObjAllocData zlist_alloc_data;
HSD_ZList* zlist_top = NULL;
HSD_ZList** zlist_bottom = &zlist_top;
HSD_ZList* zlist_texedge_top = NULL;
HSD_ZList** zlist_texedge_bottom = &zlist_texedge_top;
int zlist_texedge_nb = 0;
HSD_ZList* zlist_xlu_top = NULL;
HSD_ZList** zlist_xlu_bottom = &zlist_xlu_top;
int zlist_xlu_nb = 0;
void HSD_ZListInitAllocData(void)
{
    HSD_ObjAllocInit(&zlist_alloc_data, sizeof(HSD_ZList), 4);
}
void _HSD_DispForgetMemory(void* lo, void* hi)
{
    zlist_top = NULL;
    zlist_bottom = &zlist_top;

    zlist_texedge_top = NULL;
    zlist_texedge_bottom = &zlist_texedge_top;
    zlist_texedge_nb = 0;

    zlist_xlu_top = NULL;
    zlist_xlu_bottom = &zlist_xlu_top;
    zlist_xlu_nb = 0;
}
