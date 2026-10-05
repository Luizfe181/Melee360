#include <xtl.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "platform_log.h"
extern "C" void Melee360NotifyReport(const char*,size_t);
extern "C" void OSReport(const char* format, ...)
{
    char message[512];
    va_list args;
    va_start(args, format);
    _vsnprintf(message, sizeof(message) - 1, format, args);
    va_end(args);
    message[sizeof(message) - 1] = 0;
    Melee360Log(message);
    Melee360NotifyReport(message,strlen(message));
}
extern "C" __declspec(noreturn) void __assert(const char* file, unsigned int line, const char* condition)
{
    OSReport("HSD ASSERT %s:%u: %s\n", file, line, condition);
    // Fail visibly in debugger and terminate instead of continuing corrupt state.
#ifdef _DEBUG
    DebugBreak();
#endif
    exit(1);
}
extern "C" __declspec(noreturn) void HSD_Panic(const char* file,unsigned int line,const char* message)
{
    __assert(file,line,message);
}
extern "C" __declspec(noreturn) void OSPanic(const char* file,int line,const char* format,...)
{
    char message[512];va_list args;va_start(args,format);
    _vsnprintf(message,sizeof(message)-1,format,args);va_end(args);
    message[sizeof(message)-1]=0;__assert(file,(unsigned int)line,message);
}
