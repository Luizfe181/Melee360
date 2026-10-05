#include <dolphin/ax.h>
#include <dolphin/os.h>
#include <stddef.h>
#include "ax_src_coefficients.inc"
int Melee360ARAMReadPCM(u32,u16,s16*);int Melee360ARAMReadByte(u32,u8*);
static u32 addressOf(u16 hi,u16 lo){return ((u32)hi<<16)|lo;}
static s16 clipSample(s64 value){return (s16)(value>32767?32767:value< -32768?-32768:value);}
static int nativeSample(AXPB* p,s16* sample){
 u32 current=addressOf(p->addr.currentAddressHi,p->addr.currentAddressLo),end=addressOf(p->addr.endAddressHi,p->addr.endAddressLo),next;u8 byte;int nibble,predictor; s64 value;
 if(!p->state){*sample=0;return 1;}
 /* DSP end is a trigger on equality, not a read-range upper bound.
  * HSD streaming can jump into the next ring buffer before its clock
  * callback changes end. Physical bounds remain enforced by ARAM reads. */
 if(p->addr.format==0){
  if((current&15)<2||!Melee360ARAMReadByte(current/2,&byte))return 0;
  if((current&15)==2){u8 header;if(!Melee360ARAMReadByte((current/16)*8,&header))return 0;p->adpcm.pred_scale=header;}
  predictor=p->adpcm.pred_scale>>4;if(predictor>=8)return 0;
  nibble=(current&1)?byte&15:byte>>4;if(nibble>=8)nibble-=16;
  value=(s64)nibble*(1<<(p->adpcm.pred_scale&15))*2048+1024+(s64)(s16)p->adpcm.a[predictor][0]*(s16)p->adpcm.yn1+(s64)(s16)p->adpcm.a[predictor][1]*(s16)p->adpcm.yn2;
  value>>=11;if(value>32767)value=32767;if(value< -32768)value=-32768;*sample=(s16)value;p->adpcm.yn2=p->adpcm.yn1;p->adpcm.yn1=(u16)*sample;
 }else if(!Melee360ARAMReadPCM(current,p->addr.format,sample))return 0;
 if(current==end){if(p->addr.loopFlag){next=addressOf(p->addr.loopAddressHi,p->addr.loopAddressLo);if(p->addr.format==0){p->adpcm.pred_scale=p->adpcmLoop.loop_pred_scale;if(p->type!=1){p->adpcm.yn1=p->adpcmLoop.loop_yn1;p->adpcm.yn2=p->adpcmLoop.loop_yn2;}}}else{next=current;p->state=0;}}
 else{next=current+1;if(p->addr.format==0&&(next&15)==0)next+=2;}
 p->addr.currentAddressHi=(u16)(next>>16);p->addr.currentAddressLo=(u16)next;return 1;
}
/* Native PCM/ADPCM with NONE/linear and four-tap polyphase SRC.
 * CPU PB state is consumed directly, rather than emulating DSP mailboxes. */
static int consumeVoice(AXVPB* voice,s32* buses[9],u32 count){
 AXPB* p;u32 i,ratio,phase,channel;int token;u16* gains[9];s16* depop[9];int active[9];
 if(!voice||!buses[0]||!buses[1]||count>160)return 0;p=&voice->pb;
 if(p->state!=0&&p->state!=1)return 0;if(!p->state)return 1;
 if((p->addr.format!=0&&p->addr.format!=10&&p->addr.format!=25)||p->srcSelect>2||(p->srcSelect==0&&p->coefSelect>2)||p->itd.flag||p->fir.numCoefs||(p->mixerCtrl&~15)||p->type>1||p->addr.loopFlag>1)return 0;
 gains[0]=&p->mix.vL;gains[1]=&p->mix.vR;gains[2]=&p->mix.vS;gains[3]=&p->mix.vAuxAL;gains[4]=&p->mix.vAuxAR;gains[5]=&p->mix.vAuxAS;gains[6]=&p->mix.vAuxBL;gains[7]=&p->mix.vAuxBR;gains[8]=&p->mix.vAuxBS;
 depop[0]=&p->dpop.aL;depop[1]=&p->dpop.aR;depop[2]=&p->dpop.aS;depop[3]=&p->dpop.aAuxAL;depop[4]=&p->dpop.aAuxAR;depop[5]=&p->dpop.aAuxAS;depop[6]=&p->dpop.aAuxBL;depop[7]=&p->dpop.aAuxBR;depop[8]=&p->dpop.aAuxBS;
 active[0]=active[1]=1;active[2]=(p->mixerCtrl&4)!=0;active[3]=active[4]=(p->mixerCtrl&1)!=0;active[5]=active[2]&&active[3];active[6]=active[7]=(p->mixerCtrl&2)!=0;active[8]=active[2]&&active[6];
 for(channel=0;channel<9;++channel)if(active[channel]&&!buses[channel])return 0;
 ratio=p->srcSelect==2?65536:addressOf(p->src.ratioHi,p->src.ratioLo);if(ratio>262144)return 0;
 token=OSDisableInterrupts();phase=p->src.currentAddressFrac;
 /* A voice active on entry completes this processing interval even if
  * its address reaches end. Zero input still advances envelope/mix state. */
 for(i=0;i<count;++i){
  s16 a;AXPB peek=*p;s32 enveloped;int volume;
  if(p->srcSelect!=2){
   const s16* coefficients;s64 filtered;u32 tap;
   phase+=ratio;
   while(phase>=65536){s16 consumed;if(!nativeSample(p,&consumed)){OSRestoreInterrupts(token);return 0;}p->src.last_samples[0]=p->src.last_samples[1];p->src.last_samples[1]=p->src.last_samples[2];p->src.last_samples[2]=p->src.last_samples[3];p->src.last_samples[3]=(u16)consumed;phase-=65536;}
   if(p->srcSelect==1){a=(s16)(phase?((s64)(s16)p->src.last_samples[0]*(65536-phase)+(s64)(s16)p->src.last_samples[1]*phase)>>16:(s16)p->src.last_samples[0]);}
   else{
   coefficients=axPolyphaseCoefficients+p->coefSelect*512+(phase>>9)*4;
   filtered=0;for(tap=0;tap<4;++tap)filtered+=(s64)(s16)p->src.last_samples[tap]*coefficients[tap];filtered>>=15;
   a=(s16)(filtered>32767?32767:filtered< -32768?-32768:filtered);
   }
  }else{
   if(!nativeSample(&peek,&a)){OSRestoreInterrupts(token);return 0;}
  }
  enveloped=clipSample(((s32)a*(s16)p->ve.currentVolume)>>15);
  for(channel=0;channel<9;++channel)if(active[channel]){s16 sample=clipSample(((s64)enveloped*gains[channel][0])>>15);buses[channel][i]+=sample;*depop[channel]=sample;if(p->mixerCtrl&8)gains[channel][0]=(u16)(gains[channel][0]+gains[channel][1]);}
  /* DSP volume accumulators are 16-bit: negative deltas and overflow
   * wrap, rather than clamping at zero or full scale. */
  volume=(int)p->ve.currentVolume+p->ve.currentDelta;p->ve.currentVolume=(u16)volume;
  if(p->srcSelect==2){phase+=ratio;while(phase>=65536){s16 consumed;if(!nativeSample(p,&consumed)){OSRestoreInterrupts(token);return 0;}p->src.last_samples[0]=p->src.last_samples[1];p->src.last_samples[1]=p->src.last_samples[2];p->src.last_samples[2]=p->src.last_samples[3];p->src.last_samples[3]=(u16)consumed;phase-=65536;}}
 }
 p->src.currentAddressFrac=(u16)(phase&65535);OSRestoreInterrupts(token);return 1;
}
int Melee360AXConsumePCM(AXVPB* voice,s32* left,s32* right,u32 count){s32* buses[9]={left,right,0,0,0,0,0,0,0};u32 ms;if(voice){if(voice->updateCounter)return 0;for(ms=0;ms<5;++ms)if(voice->pb.update.updNum[ms])return 0;}return consumeVoice(voice,buses,count);}
/* The frame owns the timeline. Snapshot/validate the whole queue before
 * changing any PB word; stopped voices may be started by a later update. */
static int consumeFrameVoice(AXVPB* voice,s32* buses[9]){
 u16 counts[5],updates[128];u32 ms,total=0,word,channel;
 for(ms=0;ms<5;++ms){counts[ms]=voice->pb.update.updNum[ms];total+=counts[ms];}
 if(total>64||voice->updateCounter!=total*2||voice->updateMS>4)return 0;
 if(!total){for(ms=0;ms<5;++ms){s32* slice[9];for(channel=0;channel<9;++channel)slice[channel]=buses[channel]?buses[channel]+ms*32:0;if(!consumeVoice(voice,slice,32))return 0;}voice->updateMS=0;voice->updateWrite=voice->updateData;return 1;}
 for(word=0;word<total*2;++word)updates[word]=voice->updateData[word];
 for(word=0;word<total*2;word+=2)if(updates[word]>=sizeof(AXPB)/2)return 0;
 word=0;
 for(ms=0;ms<5;++ms){s32* slice[9];u32 update;for(update=0;update<counts[ms];++update){((u16*)&voice->pb)[updates[word]]=updates[word+1];word+=2;}for(channel=0;channel<9;++channel)slice[channel]=buses[channel]?buses[channel]+ms*32:0;if(!consumeVoice(voice,slice,32))return 0;}
 for(ms=0;ms<5;++ms)voice->pb.update.updNum[ms]=0;
 voice->updateMS=voice->updateCounter=0;voice->updateWrite=voice->updateData;return 1;
}
#include <dolphin/ar.h>
#include <string.h>
#include "ax_src_vectors.inc"
void __AXAllocInit(void);void __AXVPBInit(void);void __AXAllocQuit(void);void Melee360ARAMPump(void);
int Melee360AXPCMProbe(s16* output,u32 frames){
 __declspec(align(32)) static u8 data[64];AXVPB* v;AXPBADDR addr;AXPBMIX mix;AXPBVE ve;ARQRequest request;s32 left[160],right[160];u32 base,freed,i;int ok=1;
 if(!output||frames!=160)return 0;
 __AXAllocInit();__AXVPBInit();v=AXAcquireVoice(1,0,0);if(!v)return 0;base=ARAlloc(64);
 for(i=0;i<32;++i){s16 value=(i&1)?-1024:1024;data[i*2]=(u8)((u16)value>>8);data[i*2+1]=(u8)value;}
 ARQPostRequest(&request,0,ARQ_TYPE_MRAM_TO_ARAM,1,(u32)data,base,64,0);Melee360ARAMPump();
 memset(&addr,0,sizeof(addr));addr.format=10;addr.currentAddressHi=addr.loopAddressHi=(u16)((base/2)>>16);addr.currentAddressLo=addr.loopAddressLo=(u16)(base/2);addr.endAddressHi=(u16)((base/2+3)>>16);addr.endAddressLo=(u16)(base/2+3);
 memset(&mix,0,sizeof(mix));mix.vL=0x8000;mix.vR=0x4000;ve.currentVolume=0x8000;ve.currentDelta=0;
 AXSetVoiceAddr(v,&addr);AXSetVoiceMix(v,&mix);AXSetVoiceVe(v,&ve);AXSetVoiceSrcType(v,AX_SRC_TYPE_NONE);AXSetVoiceState(v,1);
 memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=Melee360AXConsumePCM(v,left,right,8)&&!v->pb.state;
 for(i=0;i<8;++i)ok=ok&&left[i]==(i<4?((i&1)?1024:-1024):0)&&right[i]==left[i]/2;
 addr.loopFlag=1;AXSetVoiceAddr(v,&addr);AXSetVoiceState(v,1);memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,160)&&v->pb.state==1;
 for(i=0;i<160;++i){ok=ok&&left[i]==((i&1)?1024:-1024)&&right[i]==left[i]/2;output[i*2]=(s16)left[i];output[i*2+1]=(s16)right[i];}
 ok=ok&&((((u32)v->pb.addr.currentAddressHi<<16)|v->pb.addr.currentAddressLo)==base/2);
 /* Original setter must enable ramps. Splitting a block must preserve
  * gains and addresses; exercise positive/negative deltas and wrap. */
 {static const s32 expectedL[4]={-1024,1028,-1032,1036};static const s32 expectedR[4]={-512,508,-504,500};
 mix.vL=0x8000;mix.vR=0x4000;mix.vDeltaL=128;mix.vDeltaR=(u16)-128;AXSetVoiceMix(v,&mix);AXSetVoiceCurrentAddr(v,base/2);
 memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&v->pb.mixerCtrl==8&&Melee360AXConsumePCM(v,left,right,2)&&Melee360AXConsumePCM(v,left+2,right+2,2);
 for(i=0;i<4;++i)ok=ok&&left[i]==expectedL[i]&&right[i]==expectedR[i];ok=ok&&v->pb.mix.vL==0x8200&&v->pb.mix.vR==0x3e00;
 mix.vL=65535;mix.vR=0;mix.vDeltaL=1;mix.vDeltaR=(u16)-1;AXSetVoiceMix(v,&mix);AXSetVoiceCurrentAddr(v,base/2);
 memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,2)&&left[0]==-2048&&left[1]==0&&right[0]==0&&right[1]==2047&&v->pb.mix.vL==1&&v->pb.mix.vR==65534;
 mix.vL=0x8000;mix.vR=0x4000;mix.vDeltaL=mix.vDeltaR=0;AXSetVoiceMix(v,&mix);AXSetVoiceCurrentAddr(v,base/2);
 if(ok)OSReport("AX stereo ramps: original setter, signed deltas, split blocks and 16-bit wrap passed\n");}
 /* HSD PStream jumps to a disjoint buffer. The old end remains valid
  * until the following master-clock callback replaces it. */
 AXSetVoiceAddr(v,&addr);AXSetVoiceLoopAddr(v,base/2+16);AXSetVoiceSrcType(v,AX_SRC_TYPE_NONE);AXSetVoiceState(v,1);
 memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,8)&&addressOf(v->pb.addr.currentAddressHi,v->pb.addr.currentAddressLo)==base/2+20;
 for(i=0;i<8;++i)ok=ok&&left[i]==((i&1)?1024:-1024);
 AXSetVoiceEndAddr(v,base/2+23);AXSetVoiceLoop(v,0);memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,8)&&!v->pb.state;
 for(i=0;i<8;++i)ok=ok&&left[i]==(i<4?((i&1)?1024:-1024):0);
 AXSetVoiceCurrentAddr(v,0xffffffffu);AXSetVoiceState(v,1);ok=ok&&!Melee360AXConsumePCM(v,left,right,1);
 AXSetVoiceAddr(v,&addr);AXSetVoiceState(v,1);
 if(ok)OSReport("AX streaming end: disjoint ring jump, deferred end setter, stop equality and physical ARAM bounds passed\n");
 AXSetVoiceSrcType(v,AX_SRC_TYPE_LINEAR);AXSetVoiceSrcRatio(v,.5f);AXSetVoiceCurrentAddr(v,base/2);v->pb.src.currentAddressFrac=0;memset(v->pb.src.last_samples,0,sizeof(v->pb.src.last_samples));memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,8);{static const s16 expected[8]={0,0,0,0,0,0,-512,-1024};for(i=0;i<8;++i)ok=ok&&left[i]==expected[i];}
 {u32 current=addressOf(v->pb.addr.currentAddressHi,v->pb.addr.currentAddressLo);ok=ok&&current==base/2&&v->pb.src.currentAddressFrac==0;}
 /* Extreme interpolation must not overflow signed 32-bit products. */
 data[0]=0x80;data[1]=0;data[2]=0x7f;data[3]=0xff;ARQPostRequest(&request,0,ARQ_TYPE_MRAM_TO_ARAM,1,(u32)data,base,64,0);Melee360ARAMPump();addr.loopFlag=0;AXSetVoiceAddr(v,&addr);AXSetVoiceSrcType(v,AX_SRC_TYPE_LINEAR);AXSetVoiceSrcRatio(v,0);v->pb.src.currentAddressFrac=65535;v->pb.src.last_samples[0]=0x8000;v->pb.src.last_samples[1]=0x7fff;AXSetVoiceState(v,1);memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,1)&&left[0]==-32766&&right[0]==-16383&&v->pb.src.currentAddressFrac==65535;
 {AXPBADPCM adpcm;AXPBADPCMLOOP loopState;static const s16 expected[14]={1,2,3,4,5,6,7,-8,-7,-6,-5,-4,-3,-2};
 memset(data,0,sizeof(data));for(i=0;i<7;++i)data[i+1]=(u8)(((i*2+1)&15)<<4|((i*2+2)&15));
 ARQPostRequest(&request,0,ARQ_TYPE_MRAM_TO_ARAM,1,(u32)data,base,64,0);Melee360ARAMPump();
 memset(&addr,0,sizeof(addr));addr.format=0;addr.currentAddressHi=addr.loopAddressHi=(u16)((base*2+2)>>16);addr.currentAddressLo=addr.loopAddressLo=(u16)(base*2+2);addr.endAddressHi=(u16)((base*2+15)>>16);addr.endAddressLo=(u16)(base*2+15);
 memset(&adpcm,0,sizeof(adpcm));AXSetVoiceAddr(v,&addr);AXSetVoiceAdpcm(v,&adpcm);AXSetVoiceSrcType(v,AX_SRC_TYPE_NONE);AXSetVoiceState(v,1);memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,14)&&!v->pb.state;
 for(i=0;i<14;++i)ok=ok&&left[i]==-expected[i];ok=ok&&(s16)v->pb.adpcm.yn1==-2&&(s16)v->pb.adpcm.yn2==-3;
 adpcm.a[0][0]=1024;adpcm.yn1=100;memset(&loopState,0,sizeof(loopState));loopState.loop_yn1=100;addr.loopFlag=1;AXSetVoiceAddr(v,&addr);AXSetVoiceAdpcm(v,&adpcm);AXSetVoiceAdpcmLoop(v,&loopState);AXSetVoiceState(v,1);memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,15)&&left[0]==-51&&left[14]==-51;
 /* Stream type retains predictor history instead of restarting it from
  * the loop metadata. A second loop must continue the previous samples. */
 {static const s16 streamExpected[15]={51,28,17,13,12,12,13,-1,-7,-9,-9,-8,-7,-5,-1};
 AXSetVoiceAddr(v,&addr);AXSetVoiceAdpcm(v,&adpcm);AXSetVoiceType(v,1);AXSetVoiceState(v,1);memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,14)&&v->pb.adpcm.yn1==(u16)-5&&v->pb.adpcm.yn2==(u16)-7&&Melee360AXConsumePCM(v,left+14,right+14,1);
 for(i=0;i<15;++i)ok=ok&&left[i]==-streamExpected[i];AXSetVoiceType(v,2);ok=ok&&!Melee360AXConsumePCM(v,left,right,1);AXSetVoiceType(v,0);
 if(ok)OSReport("AX stream context: original type setter, ADPCM history across loop, split boundary and invalid type rejection passed\n");}
 }
 /* Freeze reference outputs independently from the native consumer.
  * All banks, fractional phase, zero/half/full/1.5/4 ratios, clipping
  * and block splits must agree, including persistent history/address. */
 for(i=0;i<8;++i){data[i*2]=(u8)((u16)axSrcInput[i]>>8);data[i*2+1]=(u8)axSrcInput[i];}
 ARQPostRequest(&request,0,ARQ_TYPE_MRAM_TO_ARAM,1,(u32)data,base,64,0);Melee360ARAMPump();
 memset(&addr,0,sizeof(addr));addr.format=10;addr.loopFlag=1;addr.currentAddressHi=addr.loopAddressHi=(u16)((base/2)>>16);addr.currentAddressLo=addr.loopAddressLo=(u16)(base/2);addr.endAddressHi=(u16)((base/2+7)>>16);addr.endAddressLo=(u16)(base/2+7);
 for(i=0;i<15;++i){const AXSrcVector* vector=&axSrcVectors[i];u32 sample,tap;AXPBSRC source;
  memset(&source,0,sizeof(source));source.ratioHi=(u16)(vector->ratio>>16);source.ratioLo=(u16)vector->ratio;source.currentAddressFrac=vector->initial;for(tap=0;tap<4;++tap)source.last_samples[tap]=(u16)(tap==0?300:tap==1?-400:tap==2?500:-600);
  AXSetVoiceAddr(v,&addr);AXSetVoiceSrc(v,&source);AXSetVoiceSrcType(v,(u32)(AX_SRC_TYPE_4TAP_8K+vector->bank));AXSetVoiceState(v,1);
  memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,13)&&Melee360AXConsumePCM(v,left+13,right+13,19);
  for(sample=0;sample<32;++sample){s32 expected=vector->output[sample]==-32768?32767:-vector->output[sample];ok=ok&&left[sample]==expected&&right[sample]==(expected>>1);}
  for(tap=0;tap<4;++tap)ok=ok&&(s16)v->pb.src.last_samples[tap]==vector->history[tap];
  ok=ok&&v->pb.src.currentAddressFrac==vector->phase&&addressOf(v->pb.addr.currentAddressHi,v->pb.addr.currentAddressLo)==base/2+vector->position;
 }
 if(ok)OSReport("AX polyphase SRC: 3 banks, 15 fixed vectors, phase/history, split blocks and saturation passed\n");
 for(i=0;i<6;++i){const AXSrcVector* vector=&axLinearVectors[i];u32 sample,tap;AXPBSRC source;
 memset(&source,0,sizeof(source));source.ratioHi=(u16)(vector->ratio>>16);source.ratioLo=(u16)vector->ratio;source.currentAddressFrac=vector->initial;for(tap=0;tap<4;++tap)source.last_samples[tap]=(u16)(tap==0?300:tap==1?-400:tap==2?500:-600);
 AXSetVoiceAddr(v,&addr);AXSetVoiceSrc(v,&source);AXSetVoiceSrcType(v,AX_SRC_TYPE_LINEAR);AXSetVoiceState(v,1);memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,13)&&Melee360AXConsumePCM(v,left+13,right+13,19);
 for(sample=0;sample<32;++sample){s32 expected=vector->output[sample]==-32768?32767:-vector->output[sample];ok=ok&&left[sample]==expected&&right[sample]==(expected>>1);}for(tap=0;tap<4;++tap)ok=ok&&(s16)v->pb.src.last_samples[tap]==vector->history[tap];ok=ok&&v->pb.src.currentAddressFrac==vector->phase&&addressOf(v->pb.addr.currentAddressHi,v->pb.addr.currentAddressLo)==base/2+vector->position;
 }
 if(ok)OSReport("AX linear SRC: 6 fixed vectors, persistent history, fractional phase and split blocks passed\n");

 {typedef struct {u16 volume;s16 delta,input;u16 gain,finalVolume;s16 expected[8];} EnvelopeVector;
 static const EnvelopeVector vectors[6]={
 {32767,1,32767,32768,32775,{32766,-32767,-32767,-32766,-32765,-32764,-32763,-32762}},
 {0,-1,32767,32768,65528,{0,-1,-2,-3,-4,-5,-6,-7}},
 {32768,-32768,-32768,32768,32768,{32767,0,32767,0,32767,0,32767,0}},
 {16384,-20000,32767,32768,52992,{16383,-3616,-23616,21919,1919,-18080,27455,7455}},
 {32768,0,-32768,65535,32768,{32767,32767,32767,32767,32767,32767,32767,32767}},
 {32767,0,-32768,65535,32767,{-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768}}};
 u32 vector,sample;
 for(vector=0;vector<6;++vector){const EnvelopeVector* test=&vectors[vector];for(sample=0;sample<32;++sample){data[sample*2]=(u8)((u16)test->input>>8);data[sample*2+1]=(u8)test->input;}
 ARQPostRequest(&request,0,ARQ_TYPE_MRAM_TO_ARAM,1,(u32)data,base,64,0);Melee360ARAMPump();AXSetVoiceAddr(v,&addr);AXSetVoiceSrcType(v,AX_SRC_TYPE_NONE);AXSetVoiceState(v,1);ve.currentVolume=test->volume;ve.currentDelta=test->delta;AXSetVoiceVe(v,&ve);memset(&mix,0,sizeof(mix));mix.vL=mix.vR=test->gain;AXSetVoiceMix(v,&mix);
 memset(left,0,sizeof(left));memset(right,0,sizeof(right));ok=ok&&Melee360AXConsumePCM(v,left,right,3)&&Melee360AXConsumePCM(v,left+3,right+3,5);for(sample=0;sample<8;++sample)ok=ok&&left[sample]==test->expected[sample]&&right[sample]==test->expected[sample];ok=ok&&v->pb.ve.currentVolume==test->finalVolume&&v->pb.dpop.aL==test->expected[7];
 }
 if(ok)OSReport("AX envelope: 6 signed vectors, wrap, split blocks and per-voice saturation passed\n");}
 v->pb.srcSelect=3;ok=ok&&!Melee360AXConsumePCM(v,left,right,1);AXFreeVoice(v);__AXAllocQuit();ok=ok&&ARFree(&freed)==base&&freed==64;return ok;
}
AXVPB* __AXGetStackHead(u32);void __AXAuxInit(void);void __AXAuxQuit(void);void __AXSPBInit(void);void __AXSPBQuit(void);void __AXProcessAux(void);void __AXPrintStudio(void);void __AXDepopVoice(AXPB*);void __AXServiceCallbackStack(void);
u32 __AXGetStudio(void);
void __AXGetAuxAInput(u32*);void __AXGetAuxAOutput(u32*);void __AXGetAuxBInput(u32*);void __AXGetAuxBOutput(u32*);
static s32 previousSurround[160];
void Melee360AXNativeInitState(void){__AXAllocInit();__AXVPBInit();__AXSPBInit();__AXAuxInit();AXSetMode(0);memset(previousSurround,0,sizeof(previousSurround));}
void Melee360AXNativeQuitState(void){__AXAuxQuit();__AXSPBQuit();__AXAllocQuit();}
int Melee360AXNativeFrame(s16* output){
 s32 storage[9][160];s32* buses[9];u32 priority,i,channel,mode=AXGetMode(),input[2],returned[2];AXVPB* v;int token=OSDisableInterrupts(),ok=1;
 if(mode>3){OSReport("AX native mode blocked: %u (DPL2/headphone processing pending)\n",mode);OSRestoreInterrupts(token);return 0;}
 for(channel=0;channel<9;++channel)buses[channel]=storage[channel];
 for(priority=1;priority<32;++priority)for(v=__AXGetStackHead(priority);v;v=v->next)if(v->depop){__AXDepopVoice(&v->pb);v->depop=0;}
 __AXPrintStudio();{u16* studio=(u16*)__AXGetStudio();for(channel=0;channel<9;++channel){s32 start=(s32)addressOf(studio[channel*3],studio[channel*3+1]);s16 delta=(s16)studio[channel*3+2];for(i=0;i<160;++i)buses[channel][i]=start+(s32)i*delta;}}
 for(i=0;i<160;++i){if(mode==0){buses[0][i]+=previousSurround[i];buses[1][i]+=previousSurround[i];}else if(mode==1){buses[0][i]-=previousSurround[i];buses[1][i]+=previousSurround[i];}}
 /* Original AXOut processes the CPU ring before constructing the next
  * DSP command list. Preserve its three-buffer rotation and latency. */
 __AXProcessAux();__AXGetAuxAInput(&input[0]);__AXGetAuxAOutput(&returned[0]);__AXGetAuxBInput(&input[1]);__AXGetAuxBOutput(&returned[1]);
 for(priority=1;priority<32&&ok;++priority)for(v=__AXGetStackHead(priority);v&&ok;v=v->next){
  ok=consumeFrameVoice(v,buses);
  if(!ok)OSReport("AX voice blocked: index=%u state=%u format=%u src=%u mixer=0x%x type=%u itd=%u fir=%u updates=%u address=0x%x end=0x%x\n",v->index,v->pb.state,v->pb.addr.format,v->pb.srcSelect,v->pb.mixerCtrl,v->pb.type,v->pb.itd.flag,v->pb.fir.numCoefs,v->updateTotal,addressOf(v->pb.addr.currentAddressHi,v->pb.addr.currentAddressLo),addressOf(v->pb.addr.endAddressHi,v->pb.addr.endAddressLo));
 }
 for(channel=0;channel<2;++channel)if(input[channel]){s32* write=(s32*)input[channel];s32* read=(s32*)returned[channel];u32 lane;for(lane=0;lane<3;++lane)for(i=0;i<160;++i){write[lane*160+i]=buses[3+channel*3+lane][i];buses[lane][i]=(s32)((u32)buses[lane][i]+(u32)read[lane*160+i]);}}
 __AXServiceCallbackStack();
 for(i=0;i<160;++i){previousSurround[i]=buses[2][i];output[i*2]=clipSample(buses[0][i]);output[i*2+1]=clipSample(buses[1][i]);}
 OSRestoreInterrupts(token);return ok;
}

int Melee360AXDepopProbe(void){
 s16 output[320];AXPB p;u32 i,frame;int ok=1;
 Melee360AXNativeInitState();memset(&p,0,sizeof(p));p.dpop.aL=3200;p.dpop.aR=-1600;__AXDepopVoice(&p);
 ok=Melee360AXNativeFrame(output);for(i=0;i<160;++i)ok=ok&&output[i*2]==3200-(s32)i*20&&output[i*2+1]==-1600+(s32)i*10;
 ok=ok&&Melee360AXNativeFrame(output);for(i=0;i<320;++i)ok=ok&&output[i]==0;
 p.dpop.aL=159;p.dpop.aR=-159;__AXDepopVoice(&p);ok=ok&&Melee360AXNativeFrame(output);for(i=0;i<320;++i)ok=ok&&output[i]==0;
 p.dpop.aL=32760;p.dpop.aR=-32760;__AXDepopVoice(&p);__AXDepopVoice(&p);
 for(frame=0;frame<21;++frame){s32 start=65520-(s32)frame*3200;int delta=start/160;if(delta>20)delta=20;if(!delta)start=0;ok=ok&&Melee360AXNativeFrame(output);for(i=0;i<160;++i){s32 raw=start-(s32)i*delta,expected=raw>32767?32767:raw;ok=ok&&output[i*2]==expected&&output[i*2+1]==(raw>32768?-32768:-raw);}}
 ok=ok&&Melee360AXNativeFrame(output);for(i=0;i<320;++i)ok=ok&&output[i]==0;
 Melee360AXNativeQuitState();if(ok)OSReport("AX depop: original studio fades, signed tails, low-level cutoff and saturated stereo output passed\n");return ok;
}

typedef struct {u32 calls;int bad;int bOnly;int bank;} AuxProbeContext;
static void mixerProbeCallback(void* data,void* user){
 struct AX_AUX_DATA* channels=(struct AX_AUX_DATA*)data;AuxProbeContext* context=(AuxProbeContext*)user;u32 i,lane;long* lanes[3];s32 expected[3];
 lanes[0]=channels->l;lanes[1]=channels->r;lanes[2]=channels->s;
 expected[0]=context->bank?(context->bOnly?500:250):500;expected[1]=context->bank?(context->bOnly?250:125):250;expected[2]=context->bOnly?0:context->bank?62:125;
 for(lane=0;lane<3;++lane)for(i=0;i<160;++i){if(lanes[lane][i]!=(context->calls<2?0:expected[lane]))context->bad=1;lanes[lane][i]*=context->bank?-1:2;}
 ++context->calls;
}
int Melee360AXMixerProbe(void){
 __declspec(align(32)) static u8 data[64];ARQRequest request;u32 base=ARAlloc(64),freed,i,stage,frame;int ok=1;s16 output[320];
 for(i=0;i<32;++i){data[i*2]=3;data[i*2+1]=0xe8;}ARQPostRequest(&request,0,ARQ_TYPE_MRAM_TO_ARAM,1,(u32)data,base,64,0);Melee360ARAMPump();
 for(stage=0;stage<2;++stage){AXVPB* voice;AXPBADDR addr;AXPBMIX mix;AXPBVE envelope;AuxProbeContext a={0,0,0,0},b={0,0,0,1};
  Melee360AXNativeInitState();voice=AXAcquireVoice(1,0,0);if(!voice){ok=0;Melee360AXNativeQuitState();break;}
  memset(&addr,0,sizeof(addr));addr.format=10;addr.loopFlag=1;addr.currentAddressHi=addr.loopAddressHi=(u16)((base/2)>>16);addr.currentAddressLo=addr.loopAddressLo=(u16)(base/2);addr.endAddressHi=(u16)((base/2+31)>>16);addr.endAddressLo=(u16)(base/2+31);AXSetVoiceAddr(voice,&addr);AXSetVoiceSrcType(voice,AX_SRC_TYPE_NONE);envelope.currentVolume=16384;envelope.currentDelta=0;AXSetVoiceVe(voice,&envelope);memset(&mix,0,sizeof(mix));
  if(stage==0){b.bOnly=1;mix.vAuxBL=0x8000;mix.vAuxBR=0x4000;}else{mix.vAuxAL=0x8000;mix.vAuxAR=0x4000;mix.vAuxAS=0x2000;mix.vAuxBL=0x4000;mix.vAuxBR=0x2000;mix.vAuxBS=0x1000;AXRegisterAuxACallback(mixerProbeCallback,&a);}
  AXRegisterAuxBCallback(mixerProbeCallback,&b);AXSetVoiceMix(voice,&mix);AXSetVoiceState(voice,1);
  for(frame=0;frame<4;++frame){s32 l=frame<2?0:stage==0?-500:frame==2?750:938,r=frame<2?0:stage==0?-250:frame==2?375:563;ok=ok&&Melee360AXNativeFrame(output);for(i=0;i<160;++i)ok=ok&&output[i*2]==l&&output[i*2+1]==r;}
  if(stage==1){AXSetMode(1);ok=ok&&Melee360AXNativeFrame(output);for(i=0;i<160;++i)ok=ok&&output[i*2]==562&&output[i*2+1]==563;AXSetMode(2);ok=ok&&Melee360AXNativeFrame(output);for(i=0;i<160;++i)ok=ok&&output[i*2]==750&&output[i*2+1]==375;AXSetMode(3);ok=ok&&Melee360AXNativeFrame(output);for(i=0;i<160;++i)ok=ok&&output[i*2]==750&&output[i*2+1]==375;AXSetMode(0);}
  ok=ok&&!a.bad&&!b.bad&&b.calls==(stage==0?4:7)&&a.calls==(stage==0?0:7);AXRegisterAuxACallback(0,0);AXRegisterAuxBCallback(0,0);AXSetVoiceState(voice,0);voice->depop=0;ok=ok&&Melee360AXNativeFrame(output)&&Melee360AXNativeFrame(output);for(i=0;i<320;++i)ok=ok&&output[i]==0;AXFreeVoice(voice);Melee360AXNativeQuitState();
 }
 ok=ok&&ARFree(&freed)==base&&freed==64;if(ok)OSReport("AX mixer buses: independent AuxB, 9 lanes, original ring callbacks, 2-frame latency, surround feedback and reinitialization passed\n");return ok;
}

int Melee360AXUpdateProbe(void){
 __declspec(align(32)) static u8 data[64];ARQRequest request;u32 base=ARAlloc(64),freed,i;int ok=1;AXVPB* voice;AXPBADDR addr;AXPBMIX mix;AXPBVE envelope;s16 output[320];s32 storage[9][160];s32* buses[9];
 const u16 stateOffset=(u16)(offsetof(AXPB,state)/2),volumeOffset=(u16)(offsetof(AXPB,ve)/2),leftOffset=(u16)(offsetof(AXPB,mix)/2);
 for(i=0;i<32;++i){data[i*2]=3;data[i*2+1]=0xe8;}ARQPostRequest(&request,0,ARQ_TYPE_MRAM_TO_ARAM,1,(u32)data,base,64,0);Melee360ARAMPump();Melee360AXNativeInitState();voice=AXAcquireVoice(1,0,0);if(!voice){Melee360AXNativeQuitState();ARFree(&freed);return 0;}
 memset(&addr,0,sizeof(addr));addr.format=10;addr.loopFlag=1;addr.currentAddressHi=addr.loopAddressHi=(u16)((base/2)>>16);addr.currentAddressLo=addr.loopAddressLo=(u16)(base/2);addr.endAddressHi=(u16)((base/2+31)>>16);addr.endAddressLo=(u16)(base/2+31);AXSetVoiceAddr(voice,&addr);AXSetVoiceSrcType(voice,AX_SRC_TYPE_NONE);envelope.currentVolume=16384;envelope.currentDelta=0;AXSetVoiceVe(voice,&envelope);memset(&mix,0,sizeof(mix));mix.vL=mix.vR=0x8000;AXSetVoiceMix(voice,&mix);
 AXSetVoiceUpdateIncrement(voice);AXSetVoiceUpdateWrite(voice,stateOffset,1);AXSetVoiceUpdateIncrement(voice);AXSetVoiceUpdateWrite(voice,volumeOffset,8192);AXSetVoiceUpdateIncrement(voice);AXSetVoiceUpdateWrite(voice,leftOffset,0x4000);AXSetVoiceUpdateIncrement(voice);AXSetVoiceUpdateWrite(voice,stateOffset,0);
 ok=voice->updateCounter==8&&voice->updateMS==4&&Melee360AXNativeFrame(output);
 for(i=0;i<160;++i){s16 l=i<32||i>=128?0:i<64?500:i<96?250:125,r=i<32||i>=128?0:i<64?500:250;ok=ok&&output[i*2]==l&&output[i*2+1]==r;}
 ok=ok&&!voice->pb.state&&!voice->updateCounter&&!voice->updateMS&&voice->updateWrite==voice->updateData;
 ok=ok&&Melee360AXNativeFrame(output);for(i=0;i<320;++i)ok=ok&&output[i]==0;
 /* Duplicate offsets preserve queue order, including the final 4ms slot. */
 AXSetVoiceMix(voice,&mix);AXSetVoiceUpdateWrite(voice,stateOffset,1);AXSetVoiceUpdateWrite(voice,volumeOffset,16384);AXSetVoiceUpdateWrite(voice,volumeOffset,8192);for(i=0;i<4;++i)AXSetVoiceUpdateIncrement(voice);AXSetVoiceUpdateWrite(voice,volumeOffset,16384);
 ok=ok&&Melee360AXNativeFrame(output);for(i=0;i<160;++i)ok=ok&&output[i*2]==(i<128?250:500)&&output[i*2+1]==(i<128?250:500);
 /* Full queue capacity and re-use after a frame reset. */
 for(i=0;i<64;++i)AXSetVoiceUpdateWrite(voice,volumeOffset,(u16)(16384+i));ok=ok&&voice->updateCounter==128&&Melee360AXNativeFrame(output);for(i=0;i<320;++i)ok=ok&&output[i]==501;
 /* End-of-source must finish the current 32-sample interval, but not
  * advance a voice already stopped at the next interval boundary. */
 {u32 mode,ending;for(mode=0;mode<3;++mode)for(ending=2;ending<=6;ending+=4){AXPBSRC source;
 memset(&source,0,sizeof(source));source.ratioHi=1;for(i=0;i<4;++i)source.last_samples[i]=1000;
 addr.loopFlag=0;addr.endAddressHi=(u16)((base/2+ending)>>16);addr.endAddressLo=(u16)(base/2+ending);AXSetVoiceAddr(voice,&addr);AXSetVoiceSrc(voice,&source);AXSetVoiceSrcType(voice,mode==0?AX_SRC_TYPE_NONE:mode==1?AX_SRC_TYPE_LINEAR:AX_SRC_TYPE_4TAP_8K);envelope.currentVolume=16384;envelope.currentDelta=1;AXSetVoiceVe(voice,&envelope);memset(&mix,0,sizeof(mix));mix.vL=mix.vR=0x8000;mix.vDeltaL=mix.vDeltaR=128;AXSetVoiceMix(voice,&mix);AXSetVoiceState(voice,1);
 ok=ok&&Melee360AXNativeFrame(output)&&!voice->pb.state&&voice->pb.ve.currentVolume==16416&&voice->pb.mix.vL==36864&&voice->pb.mix.vR==36864&&voice->pb.dpop.aL==0&&voice->pb.dpop.aR==0&&voice->pb.src.currentAddressFrac==0&&addressOf(voice->pb.addr.currentAddressHi,voice->pb.addr.currentAddressLo)==base/2+ending;
 for(i=24;i<320;++i)ok=ok&&output[i]==0;for(i=0;i<4;++i)ok=ok&&voice->pb.src.last_samples[i]==0;
 ok=ok&&Melee360AXNativeFrame(output)&&voice->pb.ve.currentVolume==16416&&voice->pb.mix.vL==36864;for(i=0;i<320;++i)ok=ok&&output[i]==0;
 }if(ok)OSReport("AX voice end: NONE/linear/4-tap, 6 boundaries, 32-sample accumulator completion, cleared history and stopped-frame stability passed\n");}
 /* Restore state for queue preflight probe. */
 envelope.currentVolume=16447;envelope.currentDelta=0;AXSetVoiceVe(voice,&envelope);
 /* Invalid PB offset is rejected before any word or output is modified. */
 AXSetVoiceUpdateWrite(voice,volumeOffset,100);voice->updateData[0]=(u16)(sizeof(AXPB)/2);memset(storage,0,sizeof(storage));for(i=0;i<9;++i)buses[i]=storage[i];ok=ok&&!consumeFrameVoice(voice,buses)&&voice->pb.ve.currentVolume==16447&&voice->updateCounter==2;for(i=0;i<160;++i)ok=ok&&storage[0][i]==0;
 voice->updateCounter=0;voice->pb.update.updNum[0]=0;voice->updateWrite=voice->updateData;AXSetVoiceState(voice,0);voice->depop=0;AXFreeVoice(voice);Melee360AXNativeQuitState();ok=ok&&ARFree(&freed)==base&&freed==64;
 if(ok)OSReport("AX PB updates: original setters, 5 millisecond slots, start/gain/stop, ordering, 64 pairs, reset and invalid offset rejection passed\n");return ok;
}
