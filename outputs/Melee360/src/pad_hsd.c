#include <sysdolphin/baselib/controller.h>
#include <sysdolphin/baselib/rumble.h>
static HSD_PadData queue[4];
static HSD_PadRumbleListData rumble[16];
int Melee360PadAbi(void)
{
    HSD_Rumble command;
    command.def = 0x2001;
    return sizeof(HSD_Rumble) == 2 && command.command.op == 1 && command.command.frame == 1;
}
void Melee360PadInit(void) { HSD_PadInit(4, queue, 16, rumble); }
unsigned int Melee360PadFrame(void)
{
    HSD_PadRenewStatus();
    return HSD_PadGameStatus[0].button;
}
void Melee360PadStick(int* x,int* y){*x=HSD_PadCopyStatus[0].stickX;*y=HSD_PadCopyStatus[0].stickY;}
void Melee360PadStop(void)
{
    int i;
    HSD_PadReset();
    for (i = 0; i < 4; ++i) PADControlMotor(i, PAD_MOTOR_STOP_HARD);
}
