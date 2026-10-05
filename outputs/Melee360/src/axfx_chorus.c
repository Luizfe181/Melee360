#include <dolphin/axfx.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <limits.h>
#include "axfx_chorus_table.inc"
/* Scalar translation of do_src1/do_src2 with original phase table. */
struct Owner {struct AXFX_CHORUS* effect;void (*release)(void*);};static struct Owner owners[16];
static int owner(struct AXFX_CHORUS* c,int create){int i,empty=-1;for(i=0;i<16;++i){if(owners[i].effect==c)return i;if(!owners[i].effect&&empty<0)empty=i;}return create?empty:-1;}
static int parameters(const struct AXFX_CHORUS* c,u32* period,long* offset){unsigned __int64 numerator,denominator;if(!c||c->baseDelay<5||c->baseDelay>15||c->period<5)return 0;*period=((c->period/5)+1)&~1u;denominator=(unsigned __int64)*period*5;numerator=(unsigned __int64)c->variation<<16;if(numerator/denominator>65535)return 0;*offset=(long)(numerator/denominator);return 1;}
int AXFXChorusSettings(struct AXFX_CHORUS* c){u32 period;long offset;if(owner(c,0)<0||!parameters(c,&period,&offset))return 0;c->work.currentPosHi=(u32)((320-(int)(c->baseDelay-5)*32+((int)c->work.currentLast-1)*160+480)%480);c->work.currentPosLo=0;c->work.pitchOffsetPeriod=period;c->work.pitchOffsetPeriodCount=period/2;c->work.pitchOffset=offset;return 1;}
int AXFXChorusInit(struct AXFX_CHORUS* c){struct AXFX_CHORUS_WORK w;u32 period;long offset;int n,i;void* (*allocate)(unsigned long)=__AXFXAlloc;void (*release)(void*)=__AXFXFree;if(!parameters(c,&period,&offset)||!allocate||!release||(n=owner(c,1))<0)return 0;memset(&w,0,sizeof(w));w.lastLeft[0]=allocate(0x1680);if(!w.lastLeft[0])return 0;memset(w.lastLeft[0],0,0x1680);w.lastRight[0]=w.lastLeft[0]+480;w.lastSur[0]=w.lastRight[0]+480;for(i=1;i<3;++i){w.lastLeft[i]=w.lastLeft[0]+i*160;w.lastRight[i]=w.lastRight[0]+i*160;w.lastSur[i]=w.lastSur[0]+i*160;}w.currentLast=1;w.src.trigger=480;w.currentPosHi=320-(c->baseDelay-5)*32;w.pitchOffsetPeriod=period;w.pitchOffsetPeriodCount=period/2;w.pitchOffset=offset;if(owners[n].effect)owners[n].release(c->work.lastLeft[0]);c->work=w;owners[n].effect=c;owners[n].release=release;return 1;}
int AXFXChorusShutdown(struct AXFX_CHORUS* c){int n;if(!c)return 0;n=owner(c,0);if(n>=0){owners[n].release(c->work.lastLeft[0]);memset(&c->work,0,sizeof(c->work));owners[n].effect=0;owners[n].release=0;}return 1;}
static long convert(float value){if(!_finite(value)||value>=2147483648.0||value<-2147483648.0)return LONG_MIN;return (long)value;}
static void resample(struct AXFX_CHORUS_SRCINFO* s){int i,j;float history[4];u32 hi=s->posHi,lo=s->posLo;for(j=0;j<3;++j)history[j]=(float)s->old[j];history[3]=(float)s->smpBase[hi];
    for(i=0;i<160;++i){const float* coef=rsmpTab12khz+((lo>>25)*4);float output=history[0]*coef[0];u32 next=lo+s->pitchLo,steps=s->pitchHi+(next<lo);output+=history[1]*coef[1];output+=history[2]*coef[2];output+=history[3]*coef[3];s->dest[i]=convert(output);lo=next;
        while(steps--){history[0]=history[1];history[1]=history[2];history[2]=history[3];if(++hi==s->trigger)hi=s->target;/* Assembly skips the final lookahead when no next output exists. */if(i<159||steps)history[3]=(float)s->smpBase[hi];}}
    for(j=0;j<3;++j)s->old[j]=convert(history[j]);s->posHi=hi;s->posLo=lo;
}
void AXFXChorusCallback(struct AXFX_BUFFERUPDATE* bufferUpdate,
                        struct AXFX_CHORUS* chorus)
{
    long* leftD;
    long* rightD;
    long* surD;
    long* leftS;
    long* rightS;
    long* surS;
    u32 i;
    u8 nextCurrentLast;

    if(!bufferUpdate||!chorus||owner(chorus,0)<0||!bufferUpdate->left||!bufferUpdate->right||!bufferUpdate->surround)return;
    nextCurrentLast = (chorus->work.currentLast + 1) % 3;
    leftD = chorus->work.lastLeft[nextCurrentLast];
    rightD = chorus->work.lastRight[nextCurrentLast];
    surD = chorus->work.lastSur[nextCurrentLast];
    leftS = bufferUpdate->left;
    rightS = bufferUpdate->right;
    surS = bufferUpdate->surround;
    for (i = 0; i < 0xA0; i++) {
        *leftD++ = *leftS++;
        *rightD++ = *rightS++;
        *surD++ = *surS++;
    }
    chorus->work.src.pitchHi = (chorus->work.pitchOffset < 0 ? 0 : 1);
    chorus->work.src.pitchLo = (chorus->work.pitchOffset & 0xFFFF) << 0x10;
    if (--chorus->work.pitchOffsetPeriodCount == 0) {
        chorus->work.pitchOffsetPeriodCount = chorus->work.pitchOffsetPeriod;
        chorus->work.pitchOffset = -chorus->work.pitchOffset;
    }
    for (i = 0; i < 3; i++) {
        chorus->work.src.posHi = chorus->work.currentPosHi;
        chorus->work.src.posLo = chorus->work.currentPosLo;
        switch (i) {
        case 0:
            chorus->work.src.smpBase = chorus->work.lastLeft[0];
            chorus->work.src.dest = bufferUpdate->left;
            chorus->work.src.old = &chorus->work.oldLeft[0];
            break;
        case 1:
            chorus->work.src.smpBase = chorus->work.lastRight[0];
            chorus->work.src.dest = bufferUpdate->right;
            chorus->work.src.old = &chorus->work.oldRight[0];
            break;
        case 2:
            chorus->work.src.smpBase = chorus->work.lastSur[0];
            chorus->work.src.dest = bufferUpdate->surround;
            chorus->work.src.old = &chorus->work.oldSur[0];
            break;
        }
        switch (chorus->work.src.pitchHi) {
        case 0:
            resample(&chorus->work.src);
            break;
        case 1:
            resample(&chorus->work.src);
            break;
        }
    }
    chorus->work.currentPosHi = (chorus->work.src.posHi % 480);
    chorus->work.currentPosLo = chorus->work.src.posLo;
    chorus->work.currentLast = nextCurrentLast;
}
