#include <sysdolphin/baselib/initialize.h>
#include <sysdolphin/baselib/video.h>
#include <dolphin/gx.h>
#include <dolphin/vi.h>
#include <string.h>

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
void HSD_Init_803755A8(void)
{
    // Does nothing, but need to force a comparison to make this match
    if (current_render_pass == HSD_RP_OFFSCREEN) {
        current_render_pass == 0;
    }
}

/* Establish a native progressive target without claiming GC XFB ownership. */
int Melee360HsdRenderConfigure(u32 width,u32 height){
    GXRenderModeObj* mode=HSD_VIGetRenderMode();
    if(!width||!height||width>16384||height>16384)return 0;
    memset(&HSD_VIData,0,sizeof(HSD_VIData));
    mode->viTVmode=VI_TVMODE_NTSC_PROG;mode->fbWidth=(u16)width;
    mode->efbHeight=(u16)height;mode->xfbHeight=(u16)height;
    mode->viWidth=(u16)width;mode->viHeight=(u16)height;mode->xFBmode=VI_XFBMODE_SF;
    mode->field_rendering=GX_FALSE;mode->aa=GX_FALSE;
    {
        static const u8 filter[7]={0,0,21,22,21,0,0};
        int i;memcpy(mode->vfilter,filter,sizeof(filter));
        for(i=0;i<12;++i){mode->sample_pattern[i][0]=6;mode->sample_pattern[i][1]=6;}
    }
    current_pix_fmt=GX_PF_RGB8_Z24;current_z_fmt=GX_ZC_MID;
    current_render_pass=HSD_RP_SCREEN;return 1;
}
