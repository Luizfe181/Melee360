#include <dolphin/axfx.h>
#include <string.h>
static void* (*savedAlloc)(unsigned long);static void (*savedFree)(void*);static int allocated,freed,failAt;
static void* allocate(unsigned long bytes){++allocated;return allocated==failAt?0:savedAlloc(bytes);}
static void release(void* p){++freed;savedFree(p);}
int Melee360ReverbHiProbe(void){struct AXFX_REVERBHI e;struct AXFX_BUFFERUPDATE b;long left[160],right[160],sur[160];int block,i,ok=1;float* old;
    if(sizeof(long)!=4||sizeof(e)!=0x1E0)return 0;memset(&e,0,sizeof(e));e.coloration=.5f;e.mix=1;e.time=1;e.damping=.5f;
    savedAlloc=__AXFXAlloc;savedFree=__AXFXFree;allocated=freed=failAt=0;AXFXSetHooks(allocate,release);
    if(!AXFXReverbHiInit(&e)){AXFXSetHooks(savedAlloc,savedFree);return 0;}b.left=left;b.right=right;b.surround=sur;
    for(block=0;block<30;++block){memset(left,0,sizeof(left));memset(right,0,sizeof(right));memset(sur,0,sizeof(sur));if(!block)left[0]=1000000;AXFXReverbHiCallback(&b,&e);
        for(i=0;i<160;++i){int sample=block*160+i;if(sample<1789&&left[i])ok=0;if(sample==1789&&(left[i]<-22502||left[i]>-22498))ok=0;if(right[i]||sur[i])ok=0;}
    }
    old=e.rv.C[0].inputs;allocated=freed=0;failAt=3;if(AXFXReverbHiSettings(&e)||old!=e.rv.C[0].inputs||freed!=2)ok=0;
    failAt=0;e.preDelay=1.f/32000.f;allocated=freed=0;if(!AXFXReverbHiSettings(&e)||freed!=18||e.rv.preDelayTime!=1)ok=0;
    for(block=0;block<15;++block){memset(left,0,sizeof(left));memset(right,0,sizeof(right));memset(sur,0,sizeof(sur));if(!block)right[0]=1000000;AXFXReverbHiCallback(&b,&e);for(i=0;i<160;++i){int sample=block*160+i;if(sample<1790&&right[i])ok=0;if(sample==1790&&(right[i]<-22502||right[i]>-22498))ok=0;if(left[i]||sur[i])ok=0;}if(e.rv.preDelayPtr[1]!=e.rv.preDelayLine[1])ok=0;}
    e.mix=0;if(!AXFXReverbHiSettings(&e))ok=0;memset(left,0,sizeof(left));memset(right,0,sizeof(right));memset(sur,0,sizeof(sur));left[0]=10000;AXFXReverbHiCallback(&b,&e);if(left[0]!=6000)ok=0;
    e.tempDisableFX=1;left[0]=999;AXFXReverbHiCallback(&b,&e);if(left[0]!=999)ok=0;e.tempDisableFX=0;
    e.time=0;old=e.rv.C[0].inputs;if(AXFXReverbHiSettings(&e)||e.rv.C[0].inputs!=old)ok=0;
    e.time=1;e.preDelay=0;e.crosstalk=1;e.mix=0;if(!AXFXReverbHiSettings(&e))ok=0;
    memset(left,0,sizeof(left));memset(right,0,sizeof(right));memset(sur,0,sizeof(sur));left[0]=1000000;sur[0]=10000;AXFXReverbHiCallback(&b,&e);if(left[0]!=300000||right[0]!=180000||sur[0]!=6000)ok=0;
    e.preDelay=1.f/32000.f;if(!AXFXReverbHiSettings(&e))ok=0;
    AXFXSetHooks(savedAlloc,savedFree);freed=0;AXFXReverbHiShutdown(&e);if(freed!=21||e.rv.C[0].inputs)ok=0;AXFXReverbHiShutdown(&e);if(freed!=21)ok=0;
    return ok;
}
