#include <dolphin/ax.h>
#include <dolphin/os.h>
#include <string.h>
void __AXAllocInit(void);void __AXAllocQuit(void);void __AXVPBInit(void);
void __AXSPBInit(void);void __AXSPBQuit(void);void __AXDepopVoice(AXPB*);void __AXPrintStudio(void);u32 __AXGetStudio(void);void __AXDepopFade(long*,long*,s16*);void __AXAuxInit(void);void __AXAuxQuit(void);void __AXProcessAux(void);
static int stolen,auxA,auxB,auxBad;static void* rings[3];
static void steal(void* p){if(((AXVPB*)p)->userContext==0x12345678)++stolen;}
static void aux(void* data,void* ctx){long** channels=(long**)data;int* count=(int*)ctx;
 if(channels[1]-channels[0]!=160||channels[2]-channels[0]!=320)auxBad=1;
 if(count==&auxA && *count<3)rings[*count]=channels[0];
 channels[0][159]=123;channels[1][159]=-456;channels[2][159]=789;++*count;
}
#define CHECK(c) do{if(!(c)){result=__LINE__;goto cleanup;}}while(0)
int Melee360AXControlProbe(void){
 AXVPB *v[64],*p,*s;AXPBADDR addr;AXPBADPCM adpcm;AXPBADPCMLOOP loop;AXPBSRC src;AXPBVE ve;AXPBMIX mix;
 unsigned int i,j;int result=0;u32 prior=AXGetMode();u16* words;
 {long sum=7200,volume=0;s16 delta=0;AXPB pb;AXSPB* studio;
 __AXSPBInit();__AXDepopFade(&sum,&volume,&delta);CHECK(sum==4000&&volume==7200&&delta==-20);
 sum=-7200;__AXDepopFade(&sum,&volume,&delta);CHECK(sum==-4000&&volume==-7200&&delta==20);
 sum=159;__AXDepopFade(&sum,&volume,&delta);CHECK(!sum&&!volume&&!delta);
 memset(&pb,0,sizeof(pb));pb.dpop.aL=3200;pb.dpop.aR=-3200;__AXDepopVoice(&pb);__AXPrintStudio();studio=(AXSPB*)__AXGetStudio();
 CHECK((s32)(((u32)studio->dpopLHi<<16)|studio->dpopLLo)==3200&&studio->dpopLDelta==-20);
 CHECK((s32)(((u32)studio->dpopRHi<<16)|studio->dpopRLo)==-3200&&studio->dpopRDelta==20);
 __AXPrintStudio();CHECK(!studio->dpopLHi&&!studio->dpopLLo&&!studio->dpopLDelta);__AXSPBQuit();}
 __AXAllocInit();__AXVPBInit();__AXAuxInit();stolen=auxA=auxB=auxBad=0;
 for(i=0;i<64;++i){v[i]=AXAcquireVoice(1,steal,0x12345678);CHECK(v[i]!=0);CHECK(v[i]->priority==1&&v[i]->pb.state==0);for(j=0;j<i;++j)CHECK(v[j]!=v[i]);}
 CHECK(AXAcquireVoice(1,steal,0)==0);s=AXAcquireVoice(2,0,0);CHECK(s==v[0]&&stolen==1);v[0]=s;
 AXSetVoicePriority(v[1],3);CHECK(v[1]->priority==3);AXFreeVoice(v[2]);p=AXAcquireVoice(5,0,0);CHECK(p==v[2]);v[2]=p;
 AXSetVoiceState(p,1);CHECK(p->pb.state==1&&(p->sync&AX_SYNC_FLAG_COPYSTATE));AXSetVoiceState(p,0);CHECK(p->depop==1);
 ve.currentVolume=0x4321;ve.currentDelta=-123;AXSetVoiceVe(p,&ve);CHECK(p->pb.ve.currentVolume==0x4321&&p->pb.ve.currentDelta==-123);
 AXSetVoiceVeDelta(p,-32768);CHECK(p->pb.ve.currentDelta==-32768&&(p->sync&AX_SYNC_FLAG_SWAPVOL));
 AXSetVoiceItdTarget(p,17,31);AXSetVoiceItdOn(p);CHECK(p->pb.itd.flag==1&&p->pb.itd.targetShiftL==0&&!(p->sync&AX_SYNC_FLAG_COPYTSHIFT));AXSetVoiceItdTarget(p,3,7);CHECK(p->pb.itd.targetShiftL==3&&p->pb.itd.targetShiftR==7);
 memset(&addr,0,sizeof(addr));addr.loopAddressLo=2;addr.endAddressLo=15;addr.currentAddressLo=3;
 for(i=0;i<3;++i){addr.format=i==0?0:i==1?10:25;memset(&p->pb.adpcm,0xAA,sizeof(p->pb.adpcm));AXSetVoiceAddr(p,&addr);CHECK(!memcmp(&addr,&p->pb.addr,sizeof(addr)));if(i)CHECK(p->pb.adpcm.gain==(i==1?0x800:0x100));CHECK(!(p->sync&(AX_SYNC_FLAG_COPYCURADDR|AX_SYNC_FLAG_COPYLOOPADDR|AX_SYNC_FLAG_COPYENDADDR|AX_SYNC_FLAG_COPYLOOP)));}
 AXSetVoiceLoop(p,1);AXSetVoiceLoopAddr(p,0x12345678);AXSetVoiceEndAddr(p,0x87654321);AXSetVoiceCurrentAddr(p,0xDEADBEEF);
 CHECK(p->pb.addr.loopFlag==1&&p->pb.addr.loopAddressHi==0x1234&&p->pb.addr.loopAddressLo==0x5678&&p->pb.addr.endAddressHi==0x8765&&p->pb.addr.endAddressLo==0x4321&&p->pb.addr.currentAddressHi==0xDEAD&&p->pb.addr.currentAddressLo==0xBEEF);
 words=(u16*)&adpcm;for(i=0;i<sizeof(adpcm)/2;++i)words[i]=(u16)(i*37+11);AXSetVoiceAdpcm(p,&adpcm);CHECK(!memcmp(&adpcm,&p->pb.adpcm,sizeof(adpcm)));
 words=(u16*)&loop;for(i=0;i<sizeof(loop)/2;++i)words[i]=(u16)(i*29+5);AXSetVoiceAdpcmLoop(p,&loop);CHECK(!memcmp(&loop,&p->pb.adpcmLoop,sizeof(loop)));
 words=(u16*)&src;for(i=0;i<sizeof(src)/2;++i)words[i]=(u16)(i*43+19);AXSetVoiceSrc(p,&src);CHECK(!memcmp(&src,&p->pb.src,sizeof(src))&&!(p->sync&AX_SYNC_FLAG_COPYRATIO));
 for(i=0;i<=20;++i){u32 expected=i>16?0x40000:i*16384;AXSetVoiceSrcRatio(p,i*0.25f);CHECK((((u32)p->pb.src.ratioHi<<16)|p->pb.src.ratioLo)==expected);}
 for(i=0;i<5;++i){AXSetMode(i);CHECK(AXGetMode()==i);for(j=0;j<18;++j){u16 expected=0;memset(&mix,0,sizeof(mix));((u16*)&mix)[j]=1;AXSetVoiceMix(p,&mix);if(j==4||j==6)expected=1;if(j==8||j==10)expected=i==4?16:2;if((j==12||j==14||j==16)&&i!=4)expected=4;if((j&1)&&!(i==4&&(j==13||j==15)))expected=8;CHECK(p->pb.mixerCtrl==expected&& !memcmp(&mix,&p->pb.mix,sizeof(mix)));}}
 AXSetMode(0);AXRegisterAuxACallback(aux,&auxA);AXRegisterAuxBCallback(aux,&auxB);for(i=0;i<3;++i)__AXProcessAux();CHECK(auxA==3&&auxB==3&&!auxBad&&rings[0]!=rings[1]&&rings[1]!=rings[2]&&rings[0]!=rings[2]);
 AXSetMode(4);__AXProcessAux();CHECK(auxA==4&&auxB==3);AXRegisterAuxACallback(0,0);AXRegisterAuxBCallback(0,0);__AXProcessAux();CHECK(auxA==4&&auxB==3);
 for(i=0;i<64;++i)AXFreeVoice(v[i]);for(i=0;i<64;++i){v[i]=AXAcquireVoice(1,0,0);CHECK(v[i]!=0);}CHECK(AXAcquireVoice(1,0,0)==0);
cleanup:__AXAuxQuit();__AXAllocQuit();AXSetMode(prior);return result? -result:1;
}
