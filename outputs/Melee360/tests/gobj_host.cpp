#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
extern "C" int Melee360GObjProbe(void);
extern "C" int OSDisableInterrupts(void){return 1;}
extern "C" int OSRestoreInterrupts(int token){return token;}
extern "C" void OSReport(const char* f,...){va_list a;va_start(a,f);vprintf(f,a);va_end(a);}
extern "C" __declspec(noreturn) void __assert(const char* f,unsigned l,const char* c){fprintf(stderr,"%s:%u %s\n",f,l,c);exit(2);}
int main(){int ok=Melee360GObjProbe();printf("Original GObj priority/pause/disable/self-delete/userdata cleanup: %s\n",ok?"PASS":"FAIL");return ok?0:1;}
