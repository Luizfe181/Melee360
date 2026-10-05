#include "audio_effects.h"
#include <string.h>
extern "C" {
#include <dolphin/axfx.h>
}
namespace {
AXFX_REVERBSTD standard;AXFX_REVERBHI high;AXFX_CHORUS chorus;bool ready;unsigned int pendingFrames;long left[160],right[160],surround[160];
short pcm16(long v){long scaled=v/256;if(scaled>32767)scaled=32767;if(scaled<-32768)scaled=-32768;return (short)scaled;}
void render(std::vector<short>& result,unsigned int channels,unsigned int frames){AXFX_BUFFERUPDATE b={left,right,surround};AXFXReverbStdCallback(&b,&standard);AXFXReverbHiCallback(&b,&high);AXFXChorusCallback(&b,&chorus);for(unsigned int i=0;i<frames;++i){result.push_back(pcm16(left[i]));if(channels==2)result.push_back(pcm16(right[i]));}}
}
void Melee360EffectsClose(){AXFXChorusShutdown(&chorus);AXFXReverbHiShutdown(&high);AXFXReverbStdShutdown(&standard);ready=false;pendingFrames=0;}
bool Melee360EffectsInit(){Melee360EffectsClose();memset(&standard,0,sizeof(standard));memset(&high,0,sizeof(high));memset(&chorus,0,sizeof(chorus));standard.coloration=.5f;standard.mix=.25f;standard.time=1;standard.damping=.5f;high.coloration=.5f;high.mix=.25f;high.time=1;high.damping=.5f;chorus.baseDelay=10;chorus.period=500;chorus.variation=1;if(!AXFXReverbStdInit(&standard)||!AXFXReverbHiInit(&high)||!AXFXChorusInit(&chorus)){Melee360EffectsClose();return false;}ready=true;return true;}
bool Melee360EffectsProcess(std::vector<short>& pcm,unsigned int channels,bool finalBlock){if(!ready||(channels!=1&&channels!=2)||pcm.size()%channels)return false;std::vector<short> result;result.reserve(pcm.size()+320);unsigned int frames=(unsigned int)pcm.size()/channels;
    for(unsigned int i=0;i<frames;++i){left[pendingFrames]=(long)pcm[i*channels]*256;right[pendingFrames]=(long)pcm[i*channels+(channels==2?1:0)]*256;surround[pendingFrames]=0;if(++pendingFrames==160){render(result,channels,160);pendingFrames=0;}}
    if(finalBlock&&pendingFrames){unsigned int valid=pendingFrames;for(unsigned int i=valid;i<160;++i)left[i]=right[i]=surround[i]=0;render(result,channels,valid);pendingFrames=0;}pcm.swap(result);return true;
}
int Melee360EffectsBridgeProbe(){std::vector<short> input,whole,partitioned,chunk;unsigned int i,at=0;const unsigned int sizes[]={159,1,321,79,800,640};bool ok=true;for(i=0;i<2000;++i){input.push_back((short)((int)(i%97)*300-14000));input.push_back((short)((int)(i%53)*400-10000));}if(!Melee360EffectsInit())return 0;whole=input;ok=Melee360EffectsProcess(whole,2,true)&&whole.size()==input.size()&&whole!=input;Melee360EffectsClose();if(!Melee360EffectsInit())return 0;for(i=0;i<6;++i){unsigned int frames=sizes[i];chunk.assign(input.begin()+at*2,input.begin()+(at+frames)*2);at+=frames;if(!Melee360EffectsProcess(chunk,2,at==2000))ok=false;partitioned.insert(partitioned.end(),chunk.begin(),chunk.end());}ok=ok&&partitioned==whole&&at==2000;Melee360EffectsClose();return ok?1:0;}
