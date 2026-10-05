#include <xtl.h>
#include "platform_log.h"
namespace {
CRITICAL_SECTION logMutex;
volatile LONG logMutexState;
void lockLog(){
    if(InterlockedCompareExchange(&logMutexState,1,0)==0){InitializeCriticalSection(&logMutex);InterlockedExchange(&logMutexState,2);}
    else while(InterlockedCompareExchange(&logMutexState,2,2)!=2)Sleep(0);
    EnterCriticalSection(&logMutex);
}
}
void Melee360Log(const char* message)
{
    if(!message)return;
    lockLog();
#ifdef _DEBUG
    OutputDebugStringA(message);
#endif
    HANDLE file = CreateFileA("game:\\melee360.log", GENERIC_WRITE,
        FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) {LeaveCriticalSection(&logMutex);return;}
    SetFilePointer(file, 0, NULL, FILE_END);
    DWORD written;
    WriteFile(file, message, (DWORD)strlen(message), &written, NULL);
    CloseHandle(file);
    LeaveCriticalSection(&logMutex);
}
