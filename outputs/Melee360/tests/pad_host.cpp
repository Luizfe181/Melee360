#include <stdio.h>
#include <string.h>
extern "C" {
#include <sysdolphin/baselib/controller.h>
void Melee360PadInit(void);
unsigned int Melee360PadFrame(void);
void Melee360PadStop(void);
}
static PADStatus injected[4];
static unsigned lastMotor[4];
extern "C" int OSDisableInterrupts(void) { return 1; }
extern "C" int OSRestoreInterrupts(int value) { return value; }
extern "C" int OSGetResetSwitchState(void) { return 0; }
extern "C" BOOL PADInit(void) { return 1; }
extern "C" int PADReset(unsigned long) { return 1; }
extern "C" BOOL PADRecalibrate(u32) { return 1; }
extern "C" u32 PADRead(PADStatus* p) { memcpy(p, injected, sizeof(injected)); return 0x80000000; }
extern "C" void PADControlMotor(s32 n, u32 cmd) { if (n >= 0 && n < 4) lastMotor[n] = cmd; }
int main() {
    for (int i = 0; i < 4; ++i) injected[i].err = PAD_ERR_NO_CONTROLLER;
    Melee360PadInit();
    injected[0].err = 0;
    injected[0].button = PAD_BUTTON_A;
    int press = (Melee360PadFrame() & PAD_BUTTON_A) && (HSD_PadGameStatus[0].trigger & PAD_BUTTON_A);
    Melee360PadFrame();
    int held = !(HSD_PadGameStatus[0].trigger & PAD_BUTTON_A);
    injected[0].button = 0;
    Melee360PadFrame();
    int released = HSD_PadGameStatus[0].release & PAD_BUTTON_A;
    injected[0].err = PAD_ERR_NO_CONTROLLER;
    Melee360PadFrame();
    int disconnect = HSD_PadGameStatus[0].err == PAD_ERR_NO_CONTROLLER;
    Melee360PadStop();
    int stopped = lastMotor[0] == PAD_MOTOR_STOP_HARD;
    int ok = press && held && released && disconnect && stopped;
    printf("Original HSD input press/hold/release/disconnect/motor-stop: %s\n", ok ? "PASS" : "FAIL");
    return ok ? 0 : 1;
}
