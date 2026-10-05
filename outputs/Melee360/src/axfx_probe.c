#include <dolphin/axfx.h>
#include <string.h>
#include <stddef.h>
static long samples[3][160];
static int allocationCount,freeCount,failAt;
static void* (*savedAlloc)(unsigned long);
static void (*savedFree)(void*);
static void* testAlloc(unsigned long size){++allocationCount;return allocationCount==failAt?0:savedAlloc(size);}
static void testFree(void* value){++freeCount;savedFree(value);}
int Melee360AXFXProbe(void){struct AXFX_DELAY delay;struct AXFX_BUFFERUPDATE update;int block,c,i,ok=1;long* oldLeft;
    if(sizeof(long)!=4||sizeof(struct AXFX_DELAY)!=0x60)return 0;
    memset(&delay,0,sizeof(delay));for(c=0;c<3;++c){delay.delay[c]=10+c*10;delay.feedback[c]=50;delay.output[c]=100;}
    savedAlloc=__AXFXAlloc;savedFree=__AXFXFree;allocationCount=freeCount=0;failAt=0;AXFXSetHooks(testAlloc,testFree);
    if(!AXFXDelayInit(&delay)){AXFXSetHooks(savedAlloc,savedFree);return 0;}
    update.left=samples[0];update.right=samples[1];update.surround=samples[2];
    for(block=0;block<=10;++block){memset(samples,0,sizeof(samples));if(block==0)for(c=0;c<3;++c)samples[c][0]=12800*(c+1);AXFXDelayCallback(&update,&delay);for(c=0;c<3;++c){long expected=0;int size=(int)delay.currentSize[c];if(block>0&&block%size==0)expected=(12800*(c+1))>>(block/size-1);if(samples[c][0]!=expected)ok=0;for(i=1;i<160;++i)if(samples[c][i])ok=0;}}
    oldLeft=delay.left;allocationCount=freeCount=0;failAt=3;if(AXFXDelaySettings(&delay)||delay.left!=oldLeft||freeCount!=2)ok=0;
    failAt=0;allocationCount=freeCount=0;if(!AXFXDelaySettings(&delay)||freeCount!=3||delay.currentPos[0]!=0)ok=0;
    delay.delay[0]=5;if(AXFXDelaySettings(&delay))ok=0;delay.delay[0]=10;delay.feedback[1]=101;if(AXFXDelaySettings(&delay))ok=0;delay.feedback[1]=50;
    /* A later hook change must not change the owner used to release buffers. */
    AXFXSetHooks(savedAlloc,savedFree);freeCount=0;AXFXDelayShutdown(&delay);if(freeCount!=3||delay.left||delay.right||delay.sur)ok=0;
    AXFXDelayShutdown(&delay);if(freeCount!=3)ok=0;memset(samples,0,sizeof(samples));samples[0][0]=71;AXFXDelayCallback(&update,&delay);if(samples[0][0]!=71)ok=0;
    return ok;
}
