#include <xtl.h>
extern "C" {
#include <dolphin/pad.h>
void __assert(const char*,unsigned int,const char*);
}
static DWORD (WINAPI* readInput)(DWORD,XINPUT_STATE*)=XInputGetState;
static BOOL (WINAPI* readClock)(LARGE_INTEGER*)=QueryPerformanceCounter;
static LARGE_INTEGER sampleFrequency,sampleTime;
static unsigned long sampleMillis;static bool cached;
static PADStatus sampleStatus[4];static u32 sampleMotors;
static CRITICAL_SECTION padLock;
static LONG lockState;
static void ensureLock()
{
    if (InterlockedCompareExchange(&lockState, 1, 0) == 0) {
        InitializeCriticalSection(&padLock);
        if(!QueryPerformanceFrequency(&sampleFrequency)||sampleFrequency.QuadPart<=0)__assert(__FILE__,__LINE__,"PAD sampling clock unavailable");
        InterlockedExchange(&lockState, 2);
    } else {
        while (InterlockedCompareExchange(&lockState, 2, 2) != 2) Sleep(0);
    }
}
extern "C" int OSDisableInterrupts(void) { ensureLock(); EnterCriticalSection(&padLock); return 1; }
extern "C" int OSRestoreInterrupts(int previous) { LeaveCriticalSection(&padLock); return previous; }
extern "C" int OSGetResetSwitchState(void) { return 0; } // No console reset switch is mapped.
extern "C" BOOL PADInit(void) { ensureLock(); return TRUE; }
extern "C" int PADReset(unsigned long mask) { (void)mask; return TRUE; }
extern "C" BOOL PADRecalibrate(u32 mask) { (void)mask; return TRUE; } // XInput calibration handled by system.
static s8 axis(SHORT value)
{
    int scaled = value / 256;
    return (s8)(scaled < -127 ? -127 : scaled);
}
extern "C" u32 PADRead(PADStatus* status)
{
    LARGE_INTEGER now;u32 result;if(!status)return 0;ensureLock();EnterCriticalSection(&padLock);
    if(!readClock(&now))__assert(__FILE__,__LINE__,"PAD sampling counter unavailable");
    if(sampleMillis&&cached&&now.QuadPart>=sampleTime.QuadPart&&now.QuadPart-sampleTime.QuadPart<(sampleFrequency.QuadPart*sampleMillis)/1000){memcpy(status,sampleStatus,sizeof(sampleStatus));result=sampleMotors;LeaveCriticalSection(&padLock);return result;}
    u32 connected = 0;
    for (DWORD user = 0; user < 4; ++user) {
        XINPUT_STATE input;
        ZeroMemory(status + user, sizeof(PADStatus));
        if (readInput(user, &input) != ERROR_SUCCESS) {
            status[user].err = PAD_ERR_NO_CONTROLLER; continue;
        }
        connected |= PAD_CHAN0_BIT >> user;
        WORD b = input.Gamepad.wButtons;
        u16 buttons = 0;
        if (b & XINPUT_GAMEPAD_A) buttons |= PAD_BUTTON_A;
        if (b & XINPUT_GAMEPAD_B) buttons |= PAD_BUTTON_B;
        if (b & XINPUT_GAMEPAD_X) buttons |= PAD_BUTTON_X;
        if (b & XINPUT_GAMEPAD_Y) buttons |= PAD_BUTTON_Y;
        if (b & XINPUT_GAMEPAD_START) buttons |= PAD_BUTTON_START;
        if (b & XINPUT_GAMEPAD_DPAD_LEFT) buttons |= PAD_BUTTON_LEFT;
        if (b & XINPUT_GAMEPAD_DPAD_RIGHT) buttons |= PAD_BUTTON_RIGHT;
        if (b & XINPUT_GAMEPAD_DPAD_UP) buttons |= PAD_BUTTON_UP;
        if (b & XINPUT_GAMEPAD_DPAD_DOWN) buttons |= PAD_BUTTON_DOWN;
        if (b & (XINPUT_GAMEPAD_LEFT_SHOULDER | XINPUT_GAMEPAD_RIGHT_SHOULDER)) buttons |= PAD_TRIGGER_Z;
        if (input.Gamepad.bLeftTrigger >= 240) buttons |= PAD_TRIGGER_L;
        if (input.Gamepad.bRightTrigger >= 240) buttons |= PAD_TRIGGER_R;
        status[user].button = buttons;
        status[user].stickX = axis(input.Gamepad.sThumbLX);
        status[user].stickY = axis(input.Gamepad.sThumbLY);
        status[user].substickX = axis(input.Gamepad.sThumbRX);
        status[user].substickY = axis(input.Gamepad.sThumbRY);
        status[user].triggerLeft = input.Gamepad.bLeftTrigger;
        status[user].triggerRight = input.Gamepad.bRightTrigger;
        status[user].analogA = (b & XINPUT_GAMEPAD_A) ? 255 : 0;
        status[user].analogB = (b & XINPUT_GAMEPAD_B) ? 255 : 0;
    }
    // PADRead returns the motor-supported channels, not a count.
    sampleTime=now;sampleMotors=connected;memcpy(sampleStatus,status,sizeof(sampleStatus));cached=true;LeaveCriticalSection(&padLock);return connected;
}
extern "C" void PADSetSamplingRate(unsigned long msec){ensureLock();EnterCriticalSection(&padLock);sampleMillis=msec>11?11:msec;cached=false;LeaveCriticalSection(&padLock);}
// Adapter: 0 refreshes every PADRead, 1..11 limit reads to that millisecond
// period. This does not emulate GameCube scanline-driven SI interrupts.
static int testCalls,testPhase;static LONGLONG testTime;
static DWORD WINAPI testInput(DWORD user,XINPUT_STATE* s){++testCalls;if(user)return ERROR_DEVICE_NOT_CONNECTED;ZeroMemory(s,sizeof(*s));s->Gamepad.wButtons=testPhase?XINPUT_GAMEPAD_B:XINPUT_GAMEPAD_A;s->Gamepad.sThumbLX=-32768;return ERROR_SUCCESS;}
static BOOL WINAPI testClock(LARGE_INTEGER* value){value->QuadPart=testTime;return TRUE;}
extern "C" int Melee360PadSamplingProbe(void){PADStatus states[4],saved[4];DWORD (WINAPI* oldInput)(DWORD,XINPUT_STATE*)=readInput;BOOL (WINAPI* oldClock)(LARGE_INTEGER*)=readClock;LARGE_INTEGER oldFrequency,oldTime;unsigned long oldPeriod;bool oldCached;u32 oldMotors;int ok;
    ensureLock();EnterCriticalSection(&padLock);oldFrequency=sampleFrequency;oldTime=sampleTime;oldPeriod=sampleMillis;oldCached=cached;oldMotors=sampleMotors;memcpy(saved,sampleStatus,sizeof(saved));readInput=testInput;readClock=testClock;sampleFrequency.QuadPart=1000;testTime=10;testCalls=testPhase=0;
    PADSetSamplingRate(3);ok=PADRead(states)==PAD_CHAN0_BIT&&testCalls==4&&states[0].button==PAD_BUTTON_A&&states[0].stickX==-127&&states[1].err==PAD_ERR_NO_CONTROLLER;
    testPhase=1;testTime=12;PADRead(states);ok=ok&&testCalls==4&&states[0].button==PAD_BUTTON_A;testTime=13;PADRead(states);ok=ok&&testCalls==8&&states[0].button==PAD_BUTTON_B;
    PADSetSamplingRate(0);PADRead(states);PADRead(states);ok=ok&&testCalls==16;PADSetSamplingRate(99);ok=ok&&sampleMillis==11;
    readInput=oldInput;readClock=oldClock;sampleFrequency=oldFrequency;sampleTime=oldTime;sampleMillis=oldPeriod;cached=oldCached;sampleMotors=oldMotors;memcpy(sampleStatus,saved,sizeof(saved));LeaveCriticalSection(&padLock);return ok;
}
extern "C" void PADControlMotor(s32 chan, u32 command)
{
    if (chan < 0 || chan >= 4) return;
    XINPUT_VIBRATION v = {0, 0};
    if (command == PAD_MOTOR_RUMBLE) v.wLeftMotorSpeed = v.wRightMotorSpeed = 32768;
    XInputSetState(chan, &v);
}
