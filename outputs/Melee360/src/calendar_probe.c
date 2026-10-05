#include <dolphin/os.h>
OSTime OSCalendarTimeToTicks(OSCalendarTime*);
void OSTicksToCalendarTime(OSTime,OSCalendarTime*);
int Melee360CalendarProbe(void){OSCalendarTime t,u;OSTime ticks;
 OSTicksToCalendarTime(0,&t);if(t.year!=2000||t.mon||t.mday!=1||t.wday!=6||t.hour||t.min||t.sec||t.msec||t.usec)return 0;
 OSTicksToCalendarTime(-1,&t);if(t.year!=1999||t.mon!=11||t.mday!=31||t.hour!=23||t.min!=59||t.sec!=59||t.msec!=999||t.usec!=999)return 0;
 t.year=2000;t.mon=1;t.mday=29;t.hour=12;t.min=34;t.sec=56;t.msec=123;t.usec=456;ticks=OSCalendarTimeToTicks(&t);OSTicksToCalendarTime(ticks,&u);
 if(u.year!=2000||u.mon!=1||u.mday!=29||u.hour!=12||u.min!=34||u.sec!=56||u.msec!=123||u.usec<455||u.usec>456||u.yday!=59)return 0;
 t.year=2100;t.mon=1;t.mday=29;t.hour=t.min=t.sec=t.msec=t.usec=0;OSTicksToCalendarTime(OSCalendarTimeToTicks(&t),&u);if(u.year!=2100||u.mon!=2||u.mday!=1)return 0;
 t.year=2400;t.mon=1;t.mday=29;OSTicksToCalendarTime(OSCalendarTimeToTicks(&t),&u);if(u.year!=2400||u.mon!=1||u.mday!=29)return 0;
 return 1;}
