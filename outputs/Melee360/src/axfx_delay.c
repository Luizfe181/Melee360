#include <dolphin/axfx.h>
#include <stdlib.h>
#include <string.h>
#ifdef _XBOX
#include <sysdolphin/baselib/memory.h>
#endif
/* Defaults are port-owned; hooks and processing are original generated C. */
void* AXFXAllocFunction(unsigned long size){
#ifdef _XBOX
    return HSD_MemAlloc(size);
#else
    return malloc(size);
#endif
}
void AXFXFreeFunction(void* pointer){
#ifdef _XBOX
    HSD_Free(pointer);
#else
    free(pointer);
#endif
}
void* (*__AXFXAlloc)(unsigned long)=AXFXAllocFunction;
void (*__AXFXFree)(void*)=AXFXFreeFunction;
#define AXFXDelayCallback Melee360OriginalDelayCallback
#include <generated/axfx_original.inc>
#undef AXFXDelayCallback
/* Ownership is recorded so shutdown and settings retain the allocator that
 * allocated the buffers, even if the global hooks change in the meantime.
 * Calls must be serialized by the future audio mixer. */
#define MAX_DELAYS 16
struct DelayOwner{struct AXFX_DELAY* effect;void (*release)(void*);};
static struct DelayOwner owners[MAX_DELAYS];
static int slot(struct AXFX_DELAY* effect,int create){int i,empty=-1;for(i=0;i<MAX_DELAYS;++i){if(owners[i].effect==effect)return i;if(!owners[i].effect&&empty<0)empty=i;}return create?empty:-1;}
static int valid(const struct AXFX_DELAY* effect){int i;if(!effect)return 0;for(i=0;i<3;++i)if(effect->delay[i]<6||effect->delay[i]>5000||effect->feedback[i]>100||effect->output[i]>100)return 0;return 1;}
int AXFXDelayShutdown(struct AXFX_DELAY* effect){int n;if(!effect)return 0;n=slot(effect,0);if(n>=0){if(effect->left)owners[n].release(effect->left);if(effect->right)owners[n].release(effect->right);if(effect->sur)owners[n].release(effect->sur);owners[n].effect=0;owners[n].release=0;}effect->left=effect->right=effect->sur=0;memset(effect->currentSize,0,sizeof(effect->currentSize));memset(effect->currentPos,0,sizeof(effect->currentPos));return 1;}
int AXFXDelaySettings(struct AXFX_DELAY* effect){long* buffers[3]={0,0,0};u32 sizes[3];int i,n;void* (*allocate)(unsigned long)=__AXFXAlloc;void (*release)(void*)=__AXFXFree;
    if(!valid(effect)||!allocate||!release)return 0;n=slot(effect,1);if(n<0)return 0;
    /* Original block length, delay, feedback and gain formulas. Allocate all
     * replacement channels first: failure leaves the previous effect intact. */
    for(i=0;i<3;++i){sizes[i]=(((effect->delay[i]-5)<<5)+0x9f)/160U;buffers[i]=(long*)allocate(sizes[i]*160*sizeof(long));if(!buffers[i]){while(i>0)release(buffers[--i]);return 0;}memset(buffers[i],0,sizes[i]*160*sizeof(long));}
    AXFXDelayShutdown(effect);owners[n].effect=effect;owners[n].release=release;effect->left=buffers[0];effect->right=buffers[1];effect->sur=buffers[2];
    for(i=0;i<3;++i){effect->currentSize[i]=sizes[i];effect->currentPos[i]=0;effect->currentFeedback[i]=(effect->feedback[i]<<7)/100U;effect->currentOutput[i]=(effect->output[i]<<7)/100U;}return 1;
}
int AXFXDelayInit(struct AXFX_DELAY* effect){if(!valid(effect))return 0;if(slot(effect,0)<0)effect->left=effect->right=effect->sur=0;return AXFXDelaySettings(effect);}
void AXFXDelayCallback(struct AXFX_BUFFERUPDATE* update,struct AXFX_DELAY* effect){int i;if(!update||!effect||slot(effect,0)<0||!update->left||!update->right||!update->surround||!effect->left||!effect->right||!effect->sur)return;for(i=0;i<3;++i)if(!effect->currentSize[i]||effect->currentPos[i]>=effect->currentSize[i])return;Melee360OriginalDelayCallback(update,effect);}
