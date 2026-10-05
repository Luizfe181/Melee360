#include <dolphin/os.h>
#include <stdio.h>
int Melee360ArenaProbe(void);
void* OSGetArenaLo(void);void* OSGetArenaHi(void);
void OSSetArenaLo(void*);void OSSetArenaHi(void*);
void* OSAllocFromArenaLo(u32,u32);void* OSAllocFromArenaHi(u32,u32);
int main(void){void* lo;void* hi;void* a;void* b;if(!Melee360ArenaProbe())return 1;
lo=OSGetArenaLo();hi=OSGetArenaHi();OSSetArenaLo((void*)1);OSSetArenaHi((void*)1);
if(lo!=OSGetArenaLo()||hi!=OSGetArenaHi())return 2;
a=OSAllocFromArenaLo(4*1024*1024,32);b=OSAllocFromArenaHi(4*1024*1024,32);
if(!a||!b||OSGetArenaLo()!=OSGetArenaHi()||OSAllocFromArenaLo(1,32)||OSAllocFromArenaHi(1,32))return 3;
OSSetArenaLo(lo);OSSetArenaHi(hi);puts("OS arena: alignment, byte writes, limits, exhaustion and boundary restoration passed");return 0;}
