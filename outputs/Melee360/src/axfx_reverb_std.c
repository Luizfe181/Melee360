#include <dolphin/axfx.h>
#include <math.h>
#include <float.h>
#include <string.h>
#include <limits.h>
/* Scalar Xenon translation of reverb_std.c HandleReverb. Original comb/AP
 * lengths, coefficients, sample rate and dry/wet gains. Not bit-identical to
 * Gekko fused arithmetic. Each API channel is addressed independently. */
struct ReverbOwner{struct AXFX_REVERBSTD* effect;void (*release)(void*);};
static struct ReverbOwner owners[16];
static int owner(struct AXFX_REVERBSTD* effect,int create){int i,empty=-1;for(i=0;i<16;++i){if(owners[i].effect==effect)return i;if(!owners[i].effect&&empty<0)empty=i;}return create?empty:-1;}
static int params(const struct AXFX_REVERBSTD* e){return e&&_finite(e->coloration)&&_finite(e->mix)&&_finite(e->time)&&_finite(e->damping)&&_finite(e->preDelay)&&e->coloration>=0&&e->coloration<=1&&e->mix>=0&&e->mix<=1&&e->time>=.01f&&e->time<=10&&e->damping>=0&&e->damping<=1&&e->preDelay>=0&&e->preDelay<=.1f;}
static void releaseWork(struct AXFX_REVSTD_WORK* w,void (*release)(void*)){int i;for(i=0;i<6;++i){if(w->C[i].inputs)release(w->C[i].inputs);if(w->AP[i].inputs)release(w->AP[i].inputs);}for(i=0;i<3;++i)if(w->preDelayLine[i])release(w->preDelayLine[i]);memset(w,0,sizeof(*w));}
static int delay(struct AXFX_REVSTD_DELAYLINE* d,int lag,void* (*allocate)(unsigned long)){d->length=(lag+2)*4;d->inPoint=0;d->outPoint=8;d->lastOutput=0;d->inputs=allocate(d->length);if(!d->inputs)return 0;memset(d->inputs,0,d->length);return 1;}
int AXFXReverbStdSettings(struct AXFX_REVERBSTD* e){struct AXFX_REVSTD_WORK w;int i,k,n;void* (*allocate)(unsigned long)=__AXFXAlloc;void (*release)(void*)=__AXFXFree;static const int lengths[4]={1789,1999,433,149};
    if(!params(e)||!allocate||!release||(n=owner(e,1))<0)return 0;memset(&w,0,sizeof(w));
    for(k=0;k<3;++k)for(i=0;i<2;++i){if(!delay(&w.C[k*2+i],lengths[i],allocate)||!delay(&w.AP[k*2+i],lengths[i+2],allocate)){releaseWork(&w,release);return 0;}w.combCoef[k*2+i]=powf(10.f,(lengths[i]*-3)/(32000.f*e->time));}
    w.allPassCoeff=e->coloration;w.level=e->mix;w.damping=1.f-(.05f+.8f*(e->damping<.05f?.05f:e->damping));w.preDelayTime=(long)(32000.f*e->preDelay);
    if(w.preDelayTime)for(k=0;k<3;++k){w.preDelayLine[k]=allocate(w.preDelayTime*4);if(!w.preDelayLine[k]){releaseWork(&w,release);return 0;}memset(w.preDelayLine[k],0,w.preDelayTime*4);w.preDelayPtr[k]=w.preDelayLine[k];}
    if(owners[n].effect)releaseWork(&e->rv,owners[n].release);e->rv=w;e->tempDisableFX=0;owners[n].effect=e;owners[n].release=release;return 1;
}
int AXFXReverbStdInit(struct AXFX_REVERBSTD* e){return AXFXReverbStdSettings(e);}
int AXFXReverbStdShutdown(struct AXFX_REVERBSTD* e){int n;if(!e)return 0;n=owner(e,0);if(n>=0){releaseWork(&e->rv,owners[n].release);owners[n].effect=0;owners[n].release=0;}e->tempDisableFX=1;return 1;}
static void advance(struct AXFX_REVSTD_DELAYLINE* d){d->inPoint+=4;d->outPoint+=4;if(d->inPoint==d->length)d->inPoint=0;if(d->outPoint==d->length)d->outPoint=0;}
static float comb(struct AXFX_REVSTD_DELAYLINE* d,float input,float coefficient){float output;d->inputs[d->inPoint/4]=input+coefficient*d->lastOutput;output=d->inputs[d->outPoint/4];d->lastOutput=output;advance(d);return output;}
static float allpass(struct AXFX_REVSTD_DELAYLINE* d,float input,float coefficient){float stored=input+coefficient*d->lastOutput,output=d->lastOutput-coefficient*stored;d->inputs[d->inPoint/4]=stored;d->lastOutput=d->inputs[d->outPoint/4];advance(d);return output;}
static long convert(float v){if(!_finite(v)||v>=2147483648.0||v<-2147483648.0)return LONG_MIN;return (long)v;}
void AXFXReverbStdCallback(struct AXFX_BUFFERUPDATE* b,struct AXFX_REVERBSTD* e){int k,i;long* channels[3];float wet,dry;if(!b||!e||owner(e,0)<0||e->tempDisableFX||!b->left||!b->right||!b->surround)return;channels[0]=b->left;channels[1]=b->right;channels[2]=b->surround;wet=.6f*e->rv.level;dry=.6f-wet;
    for(k=0;k<3;++k)for(i=0;i<160;++i){struct AXFX_REVSTD_WORK* w=&e->rv;float input=(float)channels[k][i],signal=input,filtered;
        if(w->preDelayTime){signal=*w->preDelayPtr[k];*w->preDelayPtr[k]++=input;if(w->preDelayPtr[k]==w->preDelayLine[k]+w->preDelayTime)w->preDelayPtr[k]=w->preDelayLine[k];}
        filtered=comb(&w->C[k*2],signal,w->combCoef[k*2])+comb(&w->C[k*2+1],signal,w->combCoef[k*2+1]);filtered=allpass(&w->AP[k*2],filtered,w->allPassCoeff);filtered=.3f*filtered+w->damping*w->lpLastout[k];w->lpLastout[k]=filtered;filtered=allpass(&w->AP[k*2+1],filtered,w->allPassCoeff);channels[k][i]=convert(wet*filtered+dry*input);
    }
}
