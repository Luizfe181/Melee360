/* Link-only original heap lifecycle; never compiled into the runnable XEX. */
#include <sysdolphin/baselib/initialize.h>

#include <stdarg.h>

#include <sysdolphin/baselib/aobj.h>
#include <sysdolphin/baselib/class.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/displayfunc.h>
#include <sysdolphin/baselib/fobj.h>
#include <sysdolphin/baselib/id.h>
#include <sysdolphin/baselib/list.h>
#include <sysdolphin/baselib/lobj.h>
#include <sysdolphin/baselib/mtx.h>
#include <sysdolphin/baselib/objalloc.h>
#include <sysdolphin/baselib/random.h>
#include <sysdolphin/baselib/robj.h>
#include <sysdolphin/baselib/shadow.h>
#include <sysdolphin/baselib/state.h>
#include <sysdolphin/baselib/synth.h>
#include <sysdolphin/baselib/tev.h>
#include <sysdolphin/baselib/video.h>
#include <dolphin/gx.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>


static void* hsd_heap_next_arena_lo;
static void* hsd_heap_next_arena_hi;
static volatile OSHeapHandle current_heap=-1;
static void HSD_ObjInit(void);
static HSD_RenderPass current_render_pass;
static int current_pix_fmt;
static int current_z_fmt=GX_ZC_MID;
HSD_RenderPass HSD_GetCurrentRenderPass(void)
{
    return current_render_pass;
}
void HSD_StartRender(HSD_RenderPass pass)
{
    GXRenderModeObj* rmode = HSD_VIGetRenderMode();
    current_render_pass = pass;
    if (rmode->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, current_z_fmt);
    } else {
        GXSetPixelFmt(current_pix_fmt, GX_ZC_LINEAR);
    }
    GXSetFieldMode(rmode->field_rendering, rmode->xfbHeight < rmode->viHeight);
}
