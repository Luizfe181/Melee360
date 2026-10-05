#include <sysdolphin/baselib/state.h>
#include <dolphin/gx/GXPixel.h>
u8 state_z_enable;
int state_z_func;
u8 state_z_update;
u8 state_color_update;
u8 state_alpha_update;
void HSD_StateSetZMode(int arg0, int arg1, int arg2)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    arg2 = arg2 ? GX_TRUE : GX_FALSE;

    if (state_z_enable != arg0 || state_z_func != arg1 ||
        state_z_update != arg2)
    {
        GXSetZMode(arg0, arg1, arg2);
        state_z_enable = arg0;
        state_z_func = arg1;
        state_z_update = arg2;
    }
}
void HSD_StateSetColorUpdate(int arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_color_update != arg0) {
        GXSetColorUpdate(arg0);
        state_color_update = arg0;
    }
}
void HSD_StateSetAlphaUpdate(int arg0)
{
    arg0 = arg0 ? GX_TRUE : GX_FALSE;
    if (state_alpha_update != arg0) {
        GXSetAlphaUpdate(arg0);
        state_alpha_update = arg0;
    }
}
void Melee360HsdCopyInvalidateState(void){state_z_enable=state_z_update=state_color_update=state_alpha_update=255;state_z_func=-1;}
