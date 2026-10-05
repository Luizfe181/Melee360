#include <xtl.h>
#include <stdio.h>
#include <string.h>
#include "platform_log.h"
extern "C" {
#include <dolphin/os.h>
#include <dolphin/vi.h>
}
namespace {
bool loaded;u32 progressive;const char* settingPath="game:\\melee360-video.bin";
struct Guard{int old;Guard():old(OSDisableInterrupts()){}~Guard(){OSRestoreInterrupts(old);}};
u32 format(const XVIDEO_MODE& mode){return mode.VideoStandard==XC_VIDEO_STANDARD_PAL_I?VI_PAL:VI_NTSC;}
u32 digital(const XVIDEO_MODE& mode){return !mode.fIsInterlaced?1u:0u;}
void load(){if(loaded)return;XVIDEO_MODE mode={0};XGetVideoMode(&mode);progressive=digital(mode);unsigned char record[4];FILE* file=fopen(settingPath,"rb");if(file){if(fread(record,1,4,file)==4&&fgetc(file)==EOF&&record[0]=='V'&&record[1]==1&&record[2]<=1&&record[3]==(unsigned char)(record[2]^0xa5))progressive=record[2];fclose(file);}loaded=true;}
bool store(u32 value){char temp[256];sprintf_s(temp,sizeof(temp),"%s.tmp",settingPath);unsigned char record[4]={'V',1,(unsigned char)value,(unsigned char)(value^0xa5)};FILE* file=fopen(temp,"wb");if(!file)return false;bool ok=fwrite(record,1,4,file)==4;if(fclose(file))ok=false;if(ok)ok=MoveFileExA(temp,settingPath,MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH)!=0;if(!ok)DeleteFileA(temp);return ok;}
}
extern "C" u32 VIGetTvFormat(void){XVIDEO_MODE mode={0};XGetVideoMode(&mode);return format(mode);}
/* Reports active progressive output, not GameCube component-cable GPIO. */
extern "C" u32 VIGetDTVStatus(void){XVIDEO_MODE mode={0};XGetVideoMode(&mode);return digital(mode);}
extern "C" u32 OSGetProgressiveMode(void){Guard guard;load();return progressive;}
extern "C" void OSSetProgressiveMode(u32 mode){Guard guard;load();mode&=1;if(mode==progressive)return;if(store(mode))progressive=mode;else Melee360Log("OS progressive preference: persistence unavailable\n");}
extern "C" int Melee360VideoSettingsProbe(void){Guard guard;bool savedLoaded=loaded;u32 savedProgressive=progressive;const char* savedPath=settingPath;char path[160];sprintf_s(path,sizeof(path),"game:\\video-probe-%08x.bin",GetTickCount());if(GetFileAttributesA(path)!=0xffffffffu)return 0;settingPath=path;loaded=false;u32 initial=OSGetProgressiveMode();OSSetProgressiveMode(initial^1);bool ok=OSGetProgressiveMode()==(initial^1);loaded=false;ok=OSGetProgressiveMode()==(initial^1)&&ok;OSSetProgressiveMode(2);ok=OSGetProgressiveMode()==0&&ok;OSSetProgressiveMode(3);loaded=false;ok=OSGetProgressiveMode()==1&&ok;
    XVIDEO_MODE mode={0},actual={0};mode.VideoStandard=XC_VIDEO_STANDARD_PAL_I;mode.fIsInterlaced=true;ok=format(mode)==VI_PAL&&digital(mode)==0&&ok;mode.VideoStandard=XC_VIDEO_STANDARD_NTSC_J;mode.fIsInterlaced=false;ok=format(mode)==VI_NTSC&&digital(mode)==1&&ok;XGetVideoMode(&actual);ok=actual.dwDisplayWidth>0&&actual.dwDisplayHeight>0&&VIGetTvFormat()==format(actual)&&VIGetDTVStatus()==digital(actual)&&ok;
    if(!DeleteFileA(path))ok=false;settingPath=savedPath;loaded=savedLoaded;progressive=savedProgressive;return ok?1:0;
}
