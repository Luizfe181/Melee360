#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
extern "C" void OSReport(const char* f,...){va_list a;va_start(a,f);vprintf(f,a);va_end(a);}
extern "C" int Melee360MathProbe(void);
extern "C" __declspec(noreturn) void __assert(const char* f,unsigned l,const char* c){fprintf(stderr,"%s:%u %s\n",f,l,c);exit(2);}
int main(){int ok=Melee360MathProbe();printf("Original C math / paired-single bridge: concat alias, inverse, look-at, quaternion, axis rotation, normalization: %s\n",ok?"PASS":"FAIL");return ok?0:1;}
