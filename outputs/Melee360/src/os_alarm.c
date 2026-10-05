#include <dolphin/os.h>
#include <string.h>
typedef char alarm_layout[sizeof(OSAlarm)==40?1:-1];
/* Cooperative alarm service. Callbacks execute on the runtime thread at the
 * frame boundary, not in a PowerPC decrementer exception. */
static OSAlarm* first;
static void unlinkAlarm(OSAlarm* alarm){
    OSAlarm* p=first;
    while(p&&p!=alarm)p=p->next;
    if(!p)return;
    if(p->prev)p->prev->next=p->next;else first=p->next;
    if(p->next)p->next->prev=p->prev;
    p->next=p->prev=0;p->handler=0;
}
static void insertAlarm(OSAlarm* alarm){
    OSAlarm* p=first;OSAlarm* previous=0;
    while(p&&p->fire<=alarm->fire){previous=p;p=p->next;}
    alarm->prev=previous;alarm->next=p;
    if(previous)previous->next=alarm;else first=alarm;
    if(p)p->prev=alarm;
}
void OSInitAlarm(void){/* Idempotent; initialization must not erase live alarms. */}
void OSCreateAlarm(OSAlarm* alarm){int token=OSDisableInterrupts();unlinkAlarm(alarm);memset(alarm,0,sizeof(*alarm));OSRestoreInterrupts(token);}
void OSCancelAlarm(OSAlarm* alarm){int token=OSDisableInterrupts();unlinkAlarm(alarm);alarm->period=0;OSRestoreInterrupts(token);}
void OSSetAbsAlarm(OSAlarm* alarm,OSTime time,OSAlarmHandler handler){
    int token=OSDisableInterrupts();unlinkAlarm(alarm);
    if(handler){alarm->handler=handler;alarm->fire=time;alarm->period=0;insertAlarm(alarm);}
    OSRestoreInterrupts(token);
}
void OSSetAlarm(OSAlarm* alarm,OSTime ticks,OSAlarmHandler handler){
    OSTime now=OSGetTime();
    if(ticks<0||now>0x7fffffffffffffffLL-ticks)__assert(__FILE__,__LINE__,"invalid relative alarm interval");
    OSSetAbsAlarm(alarm,now+ticks,handler);
}
void OSSetPeriodicAlarm(OSAlarm* alarm,OSTime start,OSTime period,OSAlarmHandler handler){
    int token;OSTime now=OSGetTime(),fire=start;
    if(start<0||period<=0)__assert(__FILE__,__LINE__,"invalid periodic alarm interval");
    if(fire<now){OSTime advance=(now-start)/period+1;if(advance>(0x7fffffffffffffffLL-start)/period)__assert(__FILE__,__LINE__,"alarm overflow");fire=start+advance*period;}
    token=OSDisableInterrupts();unlinkAlarm(alarm);
    if(handler){alarm->handler=handler;alarm->start=start;alarm->period=period;alarm->fire=fire;insertAlarm(alarm);}
    OSRestoreInterrupts(token);
}
BOOL OSCheckAlarmQueue(void){OSAlarm* p=first;OSAlarm* previous=0;unsigned int count=0;
    while(p){if(++count>4096||p->prev!=previous||!p->handler||(previous&&p->fire<previous->fire))return 0;previous=p;p=p->next;}return 1;
}
void Melee360AlarmPump(void){
    int budget=32;
    /* A missing saved CPU context is explicit: callbacks receive NULL. Code
     * requiring exception-register state needs the future context adapter. */
    while(budget--){OSAlarm* alarm;OSAlarmHandler handler;OSTime period,start;int token=OSDisableInterrupts();OSTime now=OSGetTime();
        alarm=first;if(!alarm||alarm->fire>now){OSRestoreInterrupts(token);break;}
        handler=alarm->handler;period=alarm->period;start=alarm->start;unlinkAlarm(alarm);
        if(period){OSTime advance=(now-start)/period+1;if(advance>(0x7fffffffffffffffLL-start)/period)__assert(__FILE__,__LINE__,"alarm overflow");alarm->handler=handler;alarm->fire=start+advance*period;alarm->start=start;alarm->period=period;insertAlarm(alarm);}
        OSRestoreInterrupts(token);handler(alarm,0);
    }
}
