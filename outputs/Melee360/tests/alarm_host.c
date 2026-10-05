#include <dolphin/os.h>
#include <stdio.h>
#include <stdlib.h>
static OSTime clockNow=100;static int count;static int order[16];static OSAlarm a,b,c;
OSTime OSGetTime(void){return clockNow;}
int OSDisableInterrupts(void){return 1;}int OSRestoreInterrupts(int token){return token;}
void __assert(const char* file,unsigned int line,const char* msg){fprintf(stderr,"%s:%u %s",file,line,msg);exit(99);}
void Melee360AlarmPump(void);
static void cb(OSAlarm* alarm,OSContext* context){if(context)exit(9);order[count++]=(int)alarm->tag;if(alarm==&c)OSCancelAlarm(alarm);}
static void requeue(OSAlarm* alarm,OSContext* context){cb(alarm,context);if(count==1)OSSetAlarm(alarm,0,cb);}
int main(void){OSInitAlarm();OSCreateAlarm(&a);OSCreateAlarm(&b);OSCreateAlarm(&c);a.tag=1;b.tag=2;c.tag=3;
    OSSetAlarm(&a,20,cb);OSSetAlarm(&b,10,cb);OSSetPeriodicAlarm(&c,0,15,cb);
    if(count||!OSCheckAlarmQueue())return 1;clockNow=110;Melee360AlarmPump();if(count!=2||order[0]!=3||order[1]!=2)return 2;
    OSCancelAlarm(&a);clockNow=999;Melee360AlarmPump();if(count!=2)return 3;
    count=0;OSSetAlarm(&a,0,requeue);Melee360AlarmPump();if(count!=2||!OSCheckAlarmQueue())return 4;
    count=0;OSSetPeriodicAlarm(&b,1000,10,cb);clockNow=1000;Melee360AlarmPump();clockNow=1055;Melee360AlarmPump();if(count!=2||b.fire!=1060)return 5;
    OSInitAlarm();if(!b.handler)return 6;OSCancelAlarm(&b);if(!OSCheckAlarmQueue())return 7;
    puts("OS alarms: deferred ordering, cancellation, callback requeue and periodic catch-up passed");return 0;
}
