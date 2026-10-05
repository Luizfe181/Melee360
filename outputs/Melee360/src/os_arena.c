#include <dolphin/os.h>
#include <malloc.h>
#include <string.h>
/* Separate from the existing 64 MiB HSD heap. This is an adapter budget,
 * not a report of GameCube physical RAM or Xbox system memory. */
#define ARENA_BYTES (8u*1024u*1024u)
static unsigned char* storage;
static u32 low,high;
static int initialize(void){
    if(storage)return 1;
    storage=(unsigned char*)_aligned_malloc(ARENA_BYTES,32);
    if(!storage)return 0;
    low=(u32)storage;high=low+ARENA_BYTES;return 1;
}
static int alignment(u32 value){return value&&!(value&(value-1));}
void* OSGetArenaLo(void){return initialize()?(void*)low:0;}
void* OSGetArenaHi(void){return initialize()?(void*)high:0;}
void OSSetArenaLo(void* value){u32 address=(u32)value;if(initialize()&&address>=(u32)storage&&address<=high)low=address;}
void OSSetArenaHi(void* value){u32 address=(u32)value;if(initialize()&&address>=low&&address<=(u32)storage+ARENA_BYTES)high=address;}
void* OSAllocFromArenaLo(u32 size,u32 align){
    u32 start,end,mask;if(!alignment(align)||!initialize())return 0;mask=align-1;
    if(low>0xffffffffu-mask)return 0;start=(low+mask)&~mask;
    if(start>high||size>high-start)return 0;end=start+size;
    if(end>0xffffffffu-mask)return 0;end=(end+mask)&~mask;
    if(end>high)return 0;low=end;return (void*)start;
}
void* OSAllocFromArenaHi(u32 size,u32 align){
    u32 end,start;if(!alignment(align)||!initialize())return 0;
    end=high&~(align-1);if(end<low||size>end-low)return 0;
    start=(end-size)&~(align-1);if(start<low)return 0;high=start;return (void*)start;
}
int Melee360ArenaProbe(void){
    void* lo=OSGetArenaLo();void* hi=OSGetArenaHi();void* a;void* b;int ok;
    if(!lo||!hi)return 0;a=OSAllocFromArenaLo(65,64);b=OSAllocFromArenaHi(97,128);
    ok=a&&b&&!((u32)a&63)&&!((u32)b&127)&&(u32)a+65<=(u32)b;
    if(ok){memset(a,0x35,65);memset(b,0x79,97);ok=((unsigned char*)a)[64]==0x35&&((unsigned char*)b)[96]==0x79;}
    ok=ok&&!OSAllocFromArenaLo(0xffffffffu,32)&&!OSAllocFromArenaHi(0xffffffffu,32)&&!OSAllocFromArenaLo(1,3);
    OSSetArenaLo(lo);OSSetArenaHi(hi);return ok&&OSGetArenaLo()==lo&&OSGetArenaHi()==hi;
}

u32 OSGetConsoleSimulatedMemSize(void){return initialize()?ARENA_BYTES:0;}
