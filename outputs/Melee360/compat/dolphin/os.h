#ifndef MELEE360_OS_H
#define MELEE360_OS_H
#include <dolphin/types.h>
/* Only the declarations required by original debug.h. */
typedef struct OSContext OSContext;
typedef signed __int64 OSTime;
typedef unsigned int OSTick;
typedef struct OSCalendarTime {
    int sec,min,hour,mday,mon,year,wday,yday,msec,usec;
} OSCalendarTime;
#include <dolphin/os/OSContext.h>
#include <dolphin/os/OSAlarm.h>
#include <dolphin/os/OSThread.h>
#include <dolphin/os/OSException.h>
#include <dolphin/os/OSRtc.h>
#define OSRoundUp32B(value) (((value) + 31u) & ~31u)
#define OSRoundDown32B(value) ((value) & ~31u)
#ifdef __cplusplus
extern "C" {
#endif
u32 OSGetPhysicalMemSize(void);
u32 OSGetConsoleSimulatedMemSize(void);
void* OSGetArenaLo(void);
void* OSGetArenaHi(void);
void OSReport(const char* format, ...);
int OSDisableInterrupts(void);
int OSRestoreInterrupts(int previous);
int OSGetResetSwitchState(void);
ATTRIBUTE_NORETURN void __assert(const char*,unsigned int,const char*);
ATTRIBUTE_NORETURN void OSPanic(const char*,int,const char*,...);
extern u32 Melee360OSBusClock;
OSTime OSGetTime(void);
OSTick OSGetTick(void);
void OSTicksToCalendarTime(OSTime,OSCalendarTime*);
OSTime OSCalendarTimeToTicks(OSCalendarTime*);
#define OS_BUS_CLOCK Melee360OSBusClock
#ifndef OS_TIMER_CLOCK
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#endif
#define OSTicksToSeconds(ticks) ((ticks) / OS_TIMER_CLOCK)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))
#define OSSecondsToTicks(sec) ((sec) * OS_TIMER_CLOCK)
#define OSMillisecondsToTicks(msec) ((msec) * (OS_TIMER_CLOCK / 1000))
#ifdef __cplusplus
}
#endif
#endif
