#include <stdio.h>
#include <stdarg.h>
#include <string.h>
void Melee360NotifyReport(const char*,size_t);int Melee360ReportProbe(void);
void OSReport(const char* fmt,...){char text[512];va_list a;va_start(a,fmt);_vsnprintf(text,sizeof(text)-1,fmt,a);va_end(a);text[511]=0;Melee360NotifyReport(text,strlen(text));}
int main(void){if(!Melee360ReportProbe())return 1;puts("HSD report callback text/length, nested report guard and unregister checks passed");return 0;}
