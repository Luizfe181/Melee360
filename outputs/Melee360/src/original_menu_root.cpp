#include "original_menu_root.h"
extern "C" {
#include <Runtime/platform.h>
#include <melee/mn/forward.h>
#include <melee/gm/forward.h>
#include <placeholder.h>
}
// Port event bridge for the isolated original root handler. Visual construction
// and the next page are serviced by menu_ui; the full GObj scheduler is pending.
struct HSD_GObj {};
struct HSD_GObjProc {unsigned int flags_3;};
struct RootFlow {u8 cur_menu,prev_menu;u16 hovered_selection;u8 confirmed_selection,pad_5[3];u64 buttons;u8 x10,entering_menu,light_lerp_frames,pad_13;void* light_color;};
typedef RootFlow MenuFlow;
struct MenuExitData {s8 pending_mode;u8 pad[3];};
struct RootKind {u8 selection_count;void (*think)(HSD_GObj*);};
struct RootInputState {u16 cooldown,x2;s32 x4;};
namespace {
RootFlow mn_804A04F0;RootInputState mn_804D6BC8;RootKind mn_803EB6B0[34];
unsigned int input;bool returnTitle;MenuExitData exitData;HSD_GObj portObject;HSD_GObjProc portProc;
HSD_GObj* HSD_GObj_CurrentInvokedProcGObj=&portObject;unsigned int HSD_GObj_804D783C;
enum {MenuInput_Up=1,MenuInput_Down=2,MenuInput_Confirm=16,MenuInput_Back=32};
u32 mn_80229624(int) {return input;}
bool mn_80229938(int,int) {return true;} // Root's five entries are always unlocked.
void sfxForward() {} void sfxBack() {} void sfxMove() {} // Audio backend is pending.
HSD_GObj* mn_8022B3A0(u8) {return &portObject;} // Requests are reflected through RootFlow.
void HSD_GObj_80390CD4(HSD_GObj*) {} void HSD_GObjFree(HSD_GObj*) {}
HSD_GObj* GObj_Create(int,int,int) {return &portObject;}
HSD_GObjProc* HSD_GObj_SetupProc(HSD_GObj*,void (*)(HSD_GObj*),int) {return &portProc;}
MenuExitData* gm_GetCurrentSceneExitData() {return &exitData;}
void gm_801A4B60() {returnTitle=exitData.pending_mode==GM_TITLE;}
#include "../compat/generated/mnmain_root.inc"
}
bool Melee360OriginalRootInput(unsigned int buttons,int* selection,int* destination){
    if(!selection||!destination||*selection<0||*selection>=5)return false;
    input=buttons;returnTitle=false;exitData.pending_mode=-1;
    mn_804A04F0.cur_menu=MENU_KIND_MAIN;mn_804A04F0.hovered_selection=(u16)*selection;mn_803EB6B0[0].selection_count=5;
    mn_8022DB10(&portObject);*selection=mn_804A04F0.hovered_selection;*destination=mn_804A04F0.cur_menu;return returnTitle;
}
