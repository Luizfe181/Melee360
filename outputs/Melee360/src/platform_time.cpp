#include <xtl.h>
extern "C" {
#include <dolphin/os.h>
// Keep the GameCube tick rate for original code. No MMIO reads on Xbox.
u32 Melee360OSBusClock=162000000;
static LONG clockState;
static LARGE_INTEGER clockFrequency,clockOrigin;
static OSTime calendarOrigin;
static OSTime convertCounter(LONGLONG value){
    return (value/clockFrequency.QuadPart)*40500000+
        ((value%clockFrequency.QuadPart)*40500000)/clockFrequency.QuadPart;
}
static void initClock(){
    if(InterlockedCompareExchange(&clockState,1,0)==0){
        FILETIME time;ULARGE_INTEGER file;
        if(!QueryPerformanceFrequency(&clockFrequency)||clockFrequency.QuadPart<=0||!QueryPerformanceCounter(&clockOrigin))
            __assert(__FILE__,__LINE__,"Xbox performance clock unavailable");
        GetSystemTimeAsFileTime(&time);file.LowPart=time.dwLowDateTime;file.HighPart=time.dwHighDateTime;
        // FILETIME epoch 1601 -> original calendar epoch 2000. Thereafter use
        // QPC so changes to the console clock do not jump animation timers.
        LONGLONG units=(LONGLONG)file.QuadPart-125911584000000000LL;
        calendarOrigin=(units/10000000)*40500000+((units%10000000)*40500000)/10000000;
        InterlockedExchange(&clockState,2);
    }else while(InterlockedCompareExchange(&clockState,2,2)!=2)Sleep(0);
}
OSTime OSGetTime(void) {
    LARGE_INTEGER counter;initClock();
    if(!QueryPerformanceCounter(&counter))
        __assert(__FILE__,__LINE__,"Xbox performance clock unavailable");
    return calendarOrigin+convertCounter(counter.QuadPart-clockOrigin.QuadPart);
}
OSTick OSGetTick(void){return (OSTick)OSGetTime();}
int Melee360TimeProbe(void){
    OSTime before=OSGetTime(),after;OSCalendarTime now;OSTicksToCalendarTime(before,&now);
    Sleep(2);after=OSGetTime();
    return now.year>=2000&&now.year<=2200&&after>=before&&OSTicksToMilliseconds(OSMillisecondsToTicks(123LL))==123LL&&
        OSTicksToSeconds(OSSecondsToTicks(3LL))==3LL;
}
}
