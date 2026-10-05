#include <xtl.h>
#include "platform_log.h"
extern "C" {
#include <dolphin/os/OSReset.h>
void __assert(const char*,unsigned int,const char*);
void Melee360AudioClose(void);void Melee360HIOClose(void);void MCCExit(void);
void Melee360CardPump(void);void Melee360ARAMPump(void);unsigned Melee360CardPending(void);unsigned Melee360ARAMPending(void);
}
namespace {
OSResetFunctionQueue resetQueue;bool resetting;
void resetRequire(bool value){if(!value)__assert(__FILE__,__LINE__,"native OS reset contract");}
bool resetCallbacks(bool final){bool ready=true;for(OSResetFunctionInfo* p=resetQueue.head;p;p=p->next)ready=(p->func(final?TRUE:FALSE)!=0)&&ready;return ready;}
void drainIO(){DWORD start=GetTickCount();while(Melee360CardPending()||Melee360ARAMPending()){Melee360CardPump();Melee360ARAMPump();resetRequire(GetTickCount()-start<5000);}}
}
extern "C" void OSRegisterResetFunction(OSResetFunctionInfo* info){resetRequire(info&&info->func&&!resetting);for(OSResetFunctionInfo* p=resetQueue.head;p;p=p->next)resetRequire(p!=info);OSResetFunctionInfo* next=resetQueue.head;while(next&&next->priority<=info->priority)next=next->next;info->next=next;info->prev=next?next->prev:resetQueue.tail;if(info->prev)info->prev->next=info;else resetQueue.head=info;if(next)next->prev=info;else resetQueue.tail=info;}
extern "C" void OSUnregisterResetFunction(OSResetFunctionInfo* info){resetRequire(info&&!resetting);bool found=false;for(OSResetFunctionInfo* p=resetQueue.head;p;p=p->next)if(p==info)found=true;resetRequire(found);if(info->prev)info->prev->next=info->next;else resetQueue.head=info->next;if(info->next)info->next->prev=info->prev;else resetQueue.tail=info->prev;info->next=info->prev=0;}
extern "C" void OSResetSystem(int kind,u32 code,BOOL forceMenu){resetRequire(!resetting&&kind>=OS_RESET_RESTART&&kind<=OS_RESET_SHUTDOWN);resetting=true;DWORD start=GetTickCount();while(!resetCallbacks(false)){drainIO();Sleep(1);resetRequire(GetTickCount()-start<5000);}drainIO();resetRequire(resetCallbacks(true));drainIO();Melee360AudioClose();MCCExit();Melee360HIOClose();DWORD launchData[4]={0x4d335253,1,code,0x4d335253^1^code};resetRequire(XSetLaunchData(launchData,sizeof(launchData))==ERROR_SUCCESS);Melee360Log("OS reset: callbacks and I/O drained; native image launch requested\n");XLaunchNewImage(forceMenu||kind==OS_RESET_SHUTDOWN?XLAUNCH_KEYWORD_DASH:"game:\\default.xex",0);}
namespace {int resetTrace[16],resetCount,resetDeferred;BOOL resetFirst(BOOL final){resetTrace[resetCount++]=final?11:1;return final||resetDeferred++>0;}BOOL resetSecond(BOOL final){resetTrace[resetCount++]=final?12:2;return TRUE;}BOOL resetThird(BOOL final){resetTrace[resetCount++]=final?13:3;return TRUE;}}
extern "C" int Melee360ResetCallbacksProbe(void){if(resetQueue.head)return 0;OSResetFunctionInfo first={resetFirst,1,0,0},second={resetSecond,5,0,0},third={resetThird,5,0,0};resetCount=resetDeferred=0;OSRegisterResetFunction(&second);OSRegisterResetFunction(&first);OSRegisterResetFunction(&third);bool ok=!resetCallbacks(false)&&resetCallbacks(false)&&resetCallbacks(true);const int expected[9]={1,2,3,1,2,3,11,12,13};ok=ok&&resetCount==9&&!memcmp(resetTrace,expected,sizeof(expected));OSUnregisterResetFunction(&second);ok=ok&&first.next==&third&&third.prev==&first;OSUnregisterResetFunction(&first);OSUnregisterResetFunction(&third);ok=ok&&!resetQueue.head&&!resetQueue.tail;drainIO();if(ok)Melee360Log("OS reset: stable priority, readiness retries, final callbacks and I/O drain passed; image relaunch untested\n");return ok;}
