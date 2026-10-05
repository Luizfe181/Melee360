#include <dolphin/axfx.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <limits.h>
/* Scalar Xenon translation of reverb_hi.c HandleReverb. Original comb/AP
 * lengths, coefficients, sample rate and dry/wet gains. Not bit-identical to
 * Gekko fused arithmetic. Each API channel is addressed independently. */
struct ReverbOwner{struct AXFX_REVERBHI* effect;void (*release)(void*);};
static struct ReverbOwner owners[16];
static int owner(struct AXFX_REVERBHI* effect,int create){int i,empty=-1;for(i=0;i<16;++i){if(owners[i].effect==effect)return i;if(!owners[i].effect&&empty<0)empty=i;}return create?empty:-1;}
static int params(const struct AXFX_REVERBHI* e){return e&&_finite(e->coloration)&&_finite(e->mix)&&_finite(e->time)&&_finite(e->damping)&&_finite(e->preDelay)&&e->coloration>=0&&e->coloration<=1&&e->mix>=0&&e->mix<=1&&e->time>=.01f&&e->time<=10&&e->damping>=0&&e->damping<=1&&e->preDelay>=0&&e->preDelay<=.1f&&_finite(e->crosstalk)&&e->crosstalk>=0&&e->crosstalk<=1;}
static void releaseWork(struct AXFX_REVHI_WORK* w,void (*release)(void*)){int i;for(i=0;i<9;++i){if(w->C[i].inputs)release(w->C[i].inputs);if(w->AP[i].inputs)release(w->AP[i].inputs);}for(i=0;i<3;++i)if(w->preDelayLine[i])release(w->preDelayLine[i]);memset(w,0,sizeof(*w));}
static int delay(struct AXFX_REVHI_DELAYLINE* d,int lag,void* (*allocate)(unsigned long)){d->length=(lag+2)*4;d->inPoint=0;d->outPoint=8;d->lastOutput=0;d->inputs=allocate(d->length);if(!d->inputs)return 0;memset(d->inputs,0,d->length);return 1;}
int AXFXReverbHiSettings(struct AXFX_REVERBHI* e){struct AXFX_REVHI_WORK w;int i,k,n;void* (*allocate)(unsigned long)=__AXFXAlloc;void (*release)(void*)=__AXFXFree;static const int lengths[8]={1789,1999,2333,433,149,47,73,67};
    if(!params(e)||!allocate||!release||(n=owner(e,1))<0)return 0;memset(&w,0,sizeof(w));
    for(k=0;k<3;++k){for(i=0;i<3;++i){if(!delay(&w.C[k*3+i],lengths[i],allocate)){releaseWork(&w,release);return 0;}w.combCoef[k*3+i]=powf(10.f,(lengths[i]*-3)/(32000.f*e->time));}
        for(i=0;i<3;++i)if(!delay(&w.AP[k*3+i],lengths[i<2?i+3:k+5],allocate)){releaseWork(&w,release);return 0;}}
    w.crosstalk=e->crosstalk;w.allPassCoeff=e->coloration;w.level=e->mix;w.damping=1.f-(.05f+.8f*(e->damping<.05f?.05f:e->damping));w.preDelayTime=(long)(32000.f*e->preDelay);
    if(w.preDelayTime)for(k=0;k<3;++k){w.preDelayLine[k]=allocate(w.preDelayTime*4);if(!w.preDelayLine[k]){releaseWork(&w,release);return 0;}memset(w.preDelayLine[k],0,w.preDelayTime*4);w.preDelayPtr[k]=w.preDelayLine[k];}
    if(owners[n].effect)releaseWork(&e->rv,owners[n].release);e->rv=w;e->tempDisableFX=0;owners[n].effect=e;owners[n].release=release;return 1;
}
int AXFXReverbHiInit(struct AXFX_REVERBHI* e){return AXFXReverbHiSettings(e);}
int AXFXReverbHiShutdown(struct AXFX_REVERBHI* e){int n;if(!e)return 0;n=owner(e,0);if(n>=0){releaseWork(&e->rv,owners[n].release);owners[n].effect=0;owners[n].release=0;}e->tempDisableFX=1;return 1;}
static void advance(struct AXFX_REVHI_DELAYLINE* d){d->inPoint+=4;d->outPoint+=4;if(d->inPoint==d->length)d->inPoint=0;if(d->outPoint==d->length)d->outPoint=0;}
static float comb(struct AXFX_REVHI_DELAYLINE* d,float input,float coefficient){float output;d->inputs[d->inPoint/4]=input+coefficient*d->lastOutput;output=d->inputs[d->outPoint/4];d->lastOutput=output;advance(d);return output;}
static float allpass(struct AXFX_REVHI_DELAYLINE* d,float input,float coefficient){float stored=input+coefficient*d->lastOutput,output=d->lastOutput-coefficient*stored;d->inputs[d->inPoint/4]=stored;d->lastOutput=d->inputs[d->outPoint/4];advance(d);return output;}
static long nearest(float v){double base,fraction;if(!_finite(v)||v>=2147483648.0||v<-2147483648.0)return LONG_MIN;base=floor((double)v);fraction=(double)v-base;if(fraction>.5||(fraction==.5&&fmod(base,2.0)!=0))base+=1;return base>=2147483648.0?LONG_MIN:(long)base;}
static long convert(float v){if(!_finite(v)||v>=2147483648.0||v<-2147483648.0)return LONG_MIN;return (long)v;}
void AXFXReverbHiCallback(struct AXFX_BUFFERUPDATE* b,struct AXFX_REVERBHI* e){int k,i;long* channels[3];float wet,dry;if(!b||!e||owner(e,0)<0||e->tempDisableFX||!b->left||!b->right||!b->surround)return;channels[0]=b->left;channels[1]=b->right;channels[2]=b->surround;/* DoCrossTalk uses fctiw (nearest/even) and scales the right sum by .6.
       Preserve that asymmetric original gain rather than inventing a stereo matrix. */
    if(e->rv.crosstalk!=0){float cross=.5f*e->rv.crosstalk,inv=1.f-cross;for(i=0;i<160;++i){float l=(float)channels[0][i],r=(float)channels[1][i];channels[0][i]=nearest(inv*l+cross*r);channels[1][i]=nearest(.6f*(cross*l+inv*r));}}
    wet=.6f*e->rv.level;dry=.6f-wet;
    for(k=0;k<3;++k)for(i=0;i<160;++i){struct AXFX_REVHI_WORK* w=&e->rv;float input=(float)channels[k][i],signal=input,filtered;
        if(w->preDelayTime){signal=*w->preDelayPtr[k];*w->preDelayPtr[k]++=input;if(w->preDelayPtr[k]==w->preDelayLine[k]+w->preDelayTime)w->preDelayPtr[k]=w->preDelayLine[k];}
        filtered=comb(&w->C[k*3],signal,w->combCoef[k*3])+comb(&w->C[k*3+1],signal,w->combCoef[k*3+1])+comb(&w->C[k*3+2],signal,w->combCoef[k*3+2]);
        filtered=allpass(&w->AP[k*3],filtered,w->allPassCoeff);filtered=allpass(&w->AP[k*3+1],filtered,w->allPassCoeff);
        filtered=.3f*filtered+w->damping*w->lpLastout[k];w->lpLastout[k]=filtered;filtered=allpass(&w->AP[k*3+2],filtered,w->allPassCoeff);channels[k][i]=convert(wet*filtered+dry*input);
    }
}
