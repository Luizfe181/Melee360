#include "menu_ui.h"
#include "platform_log.h"
extern "C" {
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/gobjproc.h>
#include <sysdolphin/baselib/gobjplink.h>
int Melee360GObjRuntimeInit(void);
}
namespace {
HSD_GObj* menuObject;
unsigned int latchedButtons,latchedTicks;
bool enabled,leaveTitle;
unsigned int dispatched;
void menuTick(HSD_GObj*) { if(enabled){leaveTitle=Melee360MenuUpdate(latchedButtons,latchedTicks);if(++dispatched==120)Melee360Log("Menu scheduler: original GObj_RunProcs dispatched 120 active updates\n");} }
}
bool Melee360MenuSchedulerInit() {
    if(menuObject)return true;
    if(!Melee360GObjRuntimeInit())return false;
    menuObject=GObj_Create(0x360,1,0);
    if(!menuObject)return false;
    dispatched=0;
    HSD_GObj_SetupProc(menuObject,menuTick,0);
    return true;
}
bool Melee360MenuScheduledFrame(bool active,unsigned int buttons,unsigned int ticks) {
    enabled=active;latchedButtons=buttons;latchedTicks=ticks;leaveTitle=false;
    HSD_GObj_RunProcs();return leaveTitle;
}
void Melee360MenuSchedulerClose() {
    if(menuObject){HSD_GObjFree(menuObject);menuObject=0;}enabled=false;
}
