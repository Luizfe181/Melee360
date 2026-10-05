extern "C" void AXQuit(void);
extern "C" void Melee360AIDMAClose(void);
#include <xtl.h>
#include <xaudio2.h>
#include <stdio.h>
#include "platform_log.h"
#include "hps_decode.h"
#include "audio_effects.h"
#include "menu_ui.h"
#include "music_catalog.h"
namespace {
IXAudio2* engine;IXAudio2MasteringVoice* master;IXAudio2SourceVoice* voice;
struct Buffer {std::vector<short> pcm;volatile LONG busy;} buffers[3];
std::vector<unsigned char> archive;unsigned int nextBlock;bool active,reported,errorReported;int currentTrack;unsigned int voiceRate,voiceChannels;int appliedOutput=-1;unsigned char aiLeft=255,aiRight=255;bool useEffects;unsigned __int64 effectFramesIn,effectFramesOut;bool effectsSubmitted;
struct Callbacks:IXAudio2VoiceCallback {
    volatile LONG error;
    void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32){} void STDMETHODCALLTYPE OnVoiceProcessingPassEnd(){}
    void STDMETHODCALLTYPE OnStreamEnd(){} void STDMETHODCALLTYPE OnBufferStart(void*){}
    void STDMETHODCALLTYPE OnBufferEnd(void* context){InterlockedExchange(&((Buffer*)context)->busy,0);}
    void STDMETHODCALLTYPE OnLoopEnd(void*){} void STDMETHODCALLTYPE OnVoiceError(void*,HRESULT code){InterlockedExchange(&error,(LONG)code);}
} callbacks;
void stop(){if(voice){voice->Stop();voice->DestroyVoice();voice=0;}for(int i=0;i<3;++i){buffers[i].pcm.clear();buffers[i].busy=0;}archive.clear();active=false;Melee360EffectsClose();useEffects=false;}
bool start(int track){if(track!=1&&track!=2&&track!=3&&(track<Melee360MusicTrackBase||track>=Melee360MusicTrackBase+Melee360MusicCount))return false;const char* name=track>=Melee360MusicTrackBase?Melee360MusicFiles[track-Melee360MusicTrackBase]:track==3?"opening.hps":track==2?"vl_battle.hps":"menu01.hps";char path[128];sprintf_s(path,sizeof(path),"game:\\data\\audio\\%s",name);FILE* file=fopen(path,"rb");if(!file)return false;fseek(file,0,SEEK_END);long length=ftell(file);rewind(file);
    if(length<160||length>32*1024*1024){fclose(file);return false;}archive.resize(length);bool ok=fread(&archive[0],1,length,file)==(unsigned int)length;fclose(file);if(!ok)return false;
    unsigned int rate,channels,next;if(!Melee360DecodeHPSBlock(&archive[0],archive.size(),0x80,buffers[0].pcm,rate,channels,next))return false;
    WAVEFORMATEX format={0};format.wFormatTag=WAVE_FORMAT_PCM;format.nChannels=(WORD)channels;format.nSamplesPerSec=rate;format.wBitsPerSample=16;format.nBlockAlign=(WORD)(channels*2);format.nAvgBytesPerSec=rate*format.nBlockAlign;
    callbacks.error=0;if(FAILED(engine->CreateSourceVoice(&voice,&format,0,2.f,&callbacks))||FAILED(voice->SetVolume(.6f))||FAILED(voice->Start()))return false;
    voiceChannels=channels;voiceRate=rate;useEffects=GetFileAttributesA("game:\\audio-effects-preview.flag")!=0xffffffffu;
    if(useEffects){if(rate!=32000){Melee360Log("Audio effects: diagnostic chain requires 32000 Hz; stream unchanged\n");useEffects=false;}else if(!Melee360EffectsInit())return false;else Melee360Log("Audio effects: PCM -> original Std/Hi/Chorus -> XAudio2 chain enabled\n");}effectFramesIn=effectFramesOut=0;effectsSubmitted=false;appliedOutput=-1;nextBlock=0x80;active=true;reported=false;char message[128];sprintf_s(message,sizeof(message),"Audio: original %s streaming through XAudio2 PCM\n",name);Melee360Log(message);return true;
}
}
extern "C" int Melee360AudioInit(void){if(engine)return 1;Melee360Log("Audio init: creating engine\n");if(FAILED(XAudio2Create(&engine,0,XAUDIO2_DEFAULT_PROCESSOR)))return 0;Melee360Log("Audio init: creating master voice\n");if(FAILED(engine->CreateMasteringVoice(&master))){engine->Release();engine=0;return 0;}return 1;}
extern "C" void Melee360AudioClose(void){AXQuit();Melee360AIDMAClose();stop();if(master){master->DestroyVoice();master=0;}if(engine){engine->Release();engine=0;}}
extern "C" void Melee360AudioPump(int track){
    if(!engine)return;
    if(track!=currentTrack){stop();currentTrack=track;errorReported=false;}
    if(!track){if(active)stop();errorReported=false;return;}
    if(!active){if(errorReported)return;if(!start(track)){stop();errorReported=true;Melee360Log("Audio: music stream unavailable\n");return;}}
    if(callbacks.error){Melee360Log("Audio: XAudio2 voice error\n");stop();errorReported=true;return;}
    XAUDIO2_VOICE_STATE state;voice->GetState(&state);
    int output=currentTrack==3?1:Melee360MenuSoundOutput();if(output!=appliedOutput){XAUDIO2_VOICE_DETAILS details;master->GetVoiceDetails(&details);float matrix[16]={0};unsigned int destinations=details.InputChannels;
        if(destinations>=1&&destinations<=8&&voiceChannels<=2){for(unsigned int src=0;src<voiceChannels;++src){if(destinations==1)matrix[src]=1.f/voiceChannels;else if(output==0){matrix[src]=matrix[src+voiceChannels]=1.f/voiceChannels;}else if(voiceChannels==1)matrix[0]=matrix[1]=1;else matrix[src+voiceChannels*src]=1;}
            for(unsigned int dst=0;dst<destinations;++dst)for(unsigned int src=0;src<voiceChannels;++src){float gain=destinations==1?(voiceChannels==2?(src?aiRight:aiLeft)/255.f:(aiLeft+aiRight)/510.f):dst==0?aiLeft/255.f:dst==1?aiRight/255.f:1.f;matrix[src+voiceChannels*dst]*=gain;}
            if(SUCCEEDED(voice->SetOutputMatrix(master,voiceChannels,destinations,matrix))){float readback[16]={0};voice->GetOutputMatrix(master,voiceChannels,destinations,readback);if(memcmp(matrix,readback,voiceChannels*destinations*sizeof(float))){Melee360Log("Audio: output matrix readback FAILED\n");stop();errorReported=true;return;}appliedOutput=output;Melee360Log(output==0?"Audio: mono output matrix applied\n":"Audio: stereo output matrix applied (surround decoding pending)\n");}}
    }
    voice->SetVolume(.6f*(currentTrack==3?1.f:Melee360MenuMusicVolume()));
    if(!reported&&state.SamplesPlayed>0){Melee360Log("Audio: original HPS samples consumed by XAudio2\n");reported=true;}
    for(int i=0;i<3&&nextBlock!=0xffffffff;++i){Buffer& buffer=buffers[i];if(InterlockedCompareExchange(&buffer.busy,0,0))continue;
        unsigned int rate,channels,next;if(!Melee360DecodeHPSBlock(&archive[0],archive.size(),nextBlock,buffer.pcm,rate,channels,next)||rate!=voiceRate||channels!=voiceChannels||buffer.pcm.empty()){Melee360Log("Audio: malformed HPS block rejected\n");stop();errorReported=true;return;}
        if(useEffects){effectFramesIn+=buffer.pcm.size()/channels;if(!Melee360EffectsProcess(buffer.pcm,channels,next==0xffffffff)){Melee360Log("Audio effects: PCM processing FAILED\n");stop();errorReported=true;return;}effectFramesOut+=buffer.pcm.size()/channels;if(effectFramesOut>effectFramesIn||effectFramesIn-effectFramesOut>=160||(next==0xffffffff&&effectFramesOut!=effectFramesIn)){Melee360Log("Audio effects: frame accounting FAILED\n");stop();errorReported=true;return;}if(buffer.pcm.empty()){nextBlock=next;continue;}}
        XAUDIO2_BUFFER descriptor={0};descriptor.AudioBytes=(UINT32)buffer.pcm.size()*2;descriptor.pAudioData=(BYTE*)&buffer.pcm[0];descriptor.pContext=&buffer;descriptor.Flags=next==0xffffffff?XAUDIO2_END_OF_STREAM:0;
        InterlockedExchange(&buffer.busy,1);if(FAILED(voice->SubmitSourceBuffer(&descriptor))){Melee360Log("Audio: source buffer submission failed\n");stop();errorReported=true;return;}nextBlock=next;if(useEffects&&!effectsSubmitted){Melee360Log("Audio effects: processed PCM submitted; frame accounting and block carry passed\n");effectsSubmitted=true;}
    }
}

extern "C" int Melee360OpeningAudioTime(unsigned int* ms){if(!ms||!active||(currentTrack!=3&&currentTrack!=Melee360MusicTrackBase+0x24&&currentTrack!=Melee360MusicTrackBase+0x52)||!voice||!voiceRate)return 0;XAUDIO2_VOICE_STATE state;voice->GetState(&state);if(!state.SamplesPlayed||!state.BuffersQueued)return 0;*ms=(unsigned int)((state.SamplesPlayed*1000)/voiceRate);return 1;}

extern "C" int Melee360AudioTrackStatus(int track){if(track!=currentTrack)return 0;if(errorReported)return -1;if(!active||!voice)return 0;XAUDIO2_VOICE_STATE state;voice->GetState(&state);return state.BuffersQueued?1:nextBlock==0xffffffff?2:0;}

// AI stream gains act on the existing real HPS/XAudio2 output, not DSP voice SRC.
extern "C" void AISetStreamVolLeft(unsigned char value){aiLeft=value;appliedOutput=-1;}
extern "C" void AISetStreamVolRight(unsigned char value){aiRight=value;appliedOutput=-1;}
extern "C" unsigned char AIGetStreamVolLeft(void){return aiLeft;}
extern "C" unsigned char AIGetStreamVolRight(void){return aiRight;}
extern "C" int Melee360AIStreamVolumeProbe(void){
 if(!engine||active)return 0;unsigned char previousL=aiLeft,previousR=aiRight;int oldTrack=currentTrack;const unsigned char values[]={0,1,127,255};bool ok=true;
 for(int i=0;i<4&&ok;++i){AISetStreamVolLeft(values[i]);AISetStreamVolRight(values[3-i]);Melee360AudioPump(1);if(!voice||errorReported){ok=false;break;}XAUDIO2_VOICE_DETAILS details;master->GetVoiceDetails(&details);float matrix[16]={0};voice->GetOutputMatrix(master,voiceChannels,details.InputChannels,matrix);int output=Melee360MenuSoundOutput();
  for(unsigned int dst=0;dst<details.InputChannels&&ok;++dst)for(unsigned int src=0;src<voiceChannels&&ok;++src){float base=details.InputChannels==1?1.f/voiceChannels:dst>=2?0.f:output==0?1.f/voiceChannels:voiceChannels==1?1.f:src==dst?1.f:0.f;float gain=details.InputChannels==1?(voiceChannels==2?(src?aiRight:aiLeft)/255.f:(aiLeft+aiRight)/510.f):dst==0?aiLeft/255.f:dst==1?aiRight/255.f:1.f;float error=matrix[src+voiceChannels*dst]-base*gain;if(error>0.000001f||error<-0.000001f)ok=false;}
  ok=ok&&AIGetStreamVolLeft()==values[i]&&AIGetStreamVolRight()==values[3-i];
 }
 stop();currentTrack=oldTrack;errorReported=false;AISetStreamVolLeft(previousL);AISetStreamVolRight(previousR);return ok?1:0;
}

#include "ai_dma.inc"
