#include <sysdolphin/baselib/debug.h>
#include <string.h>
static ReportCallback reportCallback;
static int notifying;
/* Original debug.c setter; the Metrowerks stdout hook is replaced by the
 * notification from the XDK formatter in hsd_support.cpp. */
void HSD_SetReportCallback(ReportCallback cb)
{
    reportCallback = cb;
}
void Melee360NotifyReport(const char* message,size_t bytes){
    if(reportCallback&&!notifying){notifying=1;reportCallback((const unsigned char*)message,bytes);notifying=0;}
}
static int calls,valid;
static void collect(const unsigned char* bytes,size_t n){
    static const char expected[]="Melee360 report probe: 17\n";
    ++calls;valid=n==sizeof(expected)-1&&!memcmp(bytes,expected,n);
    OSReport("Melee360 nested report probe\n");
}
int Melee360ReportProbe(void){
    calls=valid=0;HSD_SetReportCallback(collect);OSReport("Melee360 report probe: %d\n",17);
    HSD_SetReportCallback(NULL);OSReport("Melee360 report callback reset\n");return calls==1&&valid;
}
