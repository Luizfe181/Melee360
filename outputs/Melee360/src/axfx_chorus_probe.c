#include <dolphin/axfx.h>
#include <string.h>
static void* (*savedAlloc)(unsigned long);static void (*savedFree)(void*);static int allocated,freed,fail;
static void* allocate(unsigned long n){++allocated;return fail?0:savedAlloc(n);}static void release(void* p){++freed;savedFree(p);}
int Melee360ChorusProbe(void){struct AXFX_CHORUS c;struct AXFX_BUFFERUPDATE b;long l[160],r[160],s[160];int i,block,heard=0,ok=1,slow=0,fast=0,fractional=0;long* old;u32 phase;
    if(sizeof(c)!=0x9c||sizeof(long)!=4)return 0;memset(&c,0,sizeof(c));c.baseDelay=10;c.period=10;c.variation=0;b.left=l;b.right=r;b.surround=s;
    savedAlloc=__AXFXAlloc;savedFree=__AXFXFree;allocated=freed=fail=0;AXFXSetHooks(allocate,release);if(!AXFXChorusInit(&c)){AXFXSetHooks(savedAlloc,savedFree);return 0;}
    for(block=0;block<6;++block){memset(l,0,sizeof(l));memset(r,0,sizeof(r));memset(s,0,sizeof(s));if(!block)l[0]=1000000;AXFXChorusCallback(&b,&c);for(i=0;i<160;++i){int sample=block*160+i;if(sample<160&&l[i])ok=0;if(sample==160&&(l[i]<-977||l[i]>-975))ok=0;if(l[i])heard=1;if(r[i]||s[i])ok=0;}if(c.work.currentPosHi>=480)ok=0;}if(!heard)ok=0;
    old=c.work.lastLeft[0];fail=1;if(AXFXChorusInit(&c)||old!=c.work.lastLeft[0]||freed)ok=0;fail=0;c.period=0;phase=c.work.currentPosHi;if(AXFXChorusSettings(&c)||phase!=c.work.currentPosHi)ok=0;c.period=10;c.variation=1;if(!AXFXChorusSettings(&c))ok=0;
    for(block=0;block<40;++block){for(i=0;i<160;++i){l[i]=10000;r[i]=-20000;s[i]=30000;}AXFXChorusCallback(&b,&c);if(c.work.currentPosHi>=480||c.work.src.pitchHi>1)ok=0;if(c.work.src.pitchHi==0)slow=1;else fast=1;if(c.work.currentPosLo)fractional=1;}if(!slow||!fast||!fractional)ok=0;if(c.work.pitchOffsetPeriodCount>c.work.pitchOffsetPeriod)ok=0;
    AXFXSetHooks(savedAlloc,savedFree);AXFXChorusShutdown(&c);if(freed!=1||c.work.lastLeft[0])ok=0;AXFXChorusShutdown(&c);if(freed!=1)ok=0;return ok;
}
