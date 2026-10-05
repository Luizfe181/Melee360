#include <xtl.h>
#include <stdio.h>
#include <vector>
#include "menu_ui.h"
#include "menu_model.h"
#include "music_catalog.h"
#include "save_stats.h"
#include "training_stage.h"
#include "character_select.h"
#include "original_character_select.h"
extern "C" int Melee360AudioTrackStatus(int);
extern "C" void Melee360AudioPump(int);
extern "C" void Melee360PadStick(int*,int*);
extern "C" unsigned int OSGetSoundMode(void);
extern "C" void OSSetSoundMode(unsigned int);
#include "hsd_scene.h"
#include "title_scene.h"
#include "scene_VS.h"
#include "scene_PS.h"
#include "menu_font.h"
#include "platform_log.h"
#include "intro_stream.h"
#include "intro_video.h"
namespace {
Melee360MenuModel model;
IDirect3DTexture9* font;IDirect3DTexture9* white;
IDirect3DVertexShader9* vs;IDirect3DPixelShader9* ps;IDirect3DVertexDeclaration9* declaration;
unsigned int previous,nextRepeat,lastSave;bool testMode,ready,background,reported,saveAllowed;
unsigned int rumbleUntil[4];
static unsigned int rumbleMask(){unsigned int mask=0;for(int i=0;i<4;++i)if(model.config.values[6]&&!model.config.values[18+i])mask|=1u<<i;return mask;}
float soundFade=1;unsigned int soundFadeStart=0;int movieTrack=0;int soundSelection=0,soundPlaying=-1;bool soundTest=false,archiveTest=false,optionsTest=false,dataTest=false;
bool movieActive;IDirect3DDevice9* menuDevice;int character=1;bool characterConfirmed=false,characterTest=false,animationTest=false,transitionBackward=false;
bool mapActive=false,trainingMode=false,trainingBlocked=false,trainingTest=false;int mapHovered=-1;unsigned int mapTick,mapAccumulator;
bool stageActive=false,stageTest=false,trophyTest=false;int stageBackground=0;unsigned int cssTick,cssTestFrame,cssAccumulator;
int recordFighter=8,recordOpponent=0;
const char* const recordNames[25]={"Captain Falcon","Donkey Kong","Fox","Mr. Game & Watch","Kirby","Bowser","Link","Luigi","Mario","Marth","Mewtwo","Ness","Peach","Pikachu","Ice Climbers","Jigglypuff","Samus","Yoshi","Zelda / Sheik","Falco","Young Link","Dr. Mario","Roy","Pichu","Ganondorf"};
Melee360SaveStats importedStats;bool statsLoaded=false,statsValid=false;
const char* saveNotice="";
int pendingSound=-1,lastSound=1;
int trophySelected=0,trophyCoins=105,trophyCopies[2]={1,0},trophySpend=1;bool trophyList=false,trophyLoaded=false;unsigned int trophyAwardTime;float trophyRotation;unsigned int trophyTick;
void tickRumble(unsigned int ticks){if(testMode)return;unsigned int enabled=rumbleMask();for(DWORD i=0;i<4;++i){XINPUT_VIBRATION motors={0,0};if((enabled&(1u<<i))&&(int)(rumbleUntil[i]-ticks)>0)motors.wLeftMotorSpeed=motors.wRightMotorSpeed=12000;XInputSetState(i,&motors);}}
void loadStats(){if(statsLoaded)return;statsLoaded=true;statsValid=false;FILE* f=fopen("game:\\melee360-import.gci","rb");if(!f){Melee360Log("Data records: no imported original GCI\n");return;}fseek(f,0,SEEK_END);long size=ftell(f);rewind(f);if(size>=64+8192&&size<=64+32*8192){std::vector<unsigned char> raw(size);if(fread(&raw[0],1,size,f)==(unsigned int)size)statsValid=Melee360ReadSaveStats(&raw[0],(unsigned int)raw.size(),importedStats);}fclose(f);Melee360Log(statsValid?"Data records: original GCI checksum/manifest and statistics validated\n":"Data records: original GCI rejected; file preserved\n");}
void trophyPersist(bool load){const char* path="game:\\melee360-trophies-demo.bin";int record[5]={0x4d335459,1,trophyCoins,trophyCopies[0],trophyCopies[1]};
    if(testMode)return;const char* temp="game:\\melee360-trophies-demo.bin.tmp";
    FILE* f=fopen(load?path:temp,load?"rb":"wb");if(!f)return;if(load){if(fread(record,sizeof(record),1,f)==1&&fgetc(f)==EOF&&record[0]==0x4d335459&&record[1]==1&&record[2]>=0&&record[2]<=9999&&record[3]>=1&&record[3]<=9999&&record[4]>=0&&record[4]<=9999){trophyCoins=record[2];trophyCopies[0]=record[3];trophyCopies[1]=record[4];}fclose(f);}else{bool ok=fwrite(record,sizeof(record),1,f)==1;if(fclose(f)!=0)ok=false;if(ok)ok=MoveFileExA(temp,path,MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH)!=0;if(!ok)Melee360Log("Trophies: local demo progress could not be persisted\n");}}
bool upload(IDirect3DDevice9* d,unsigned int w,unsigned int h,const unsigned int* p,IDirect3DTexture9** t) {
    if(FAILED(d->CreateTexture(w,h,1,0,(D3DFORMAT)MAKESRGBFMT(D3DFMT_LIN_A8R8G8B8),D3DPOOL_DEFAULT,t,0)))return false;
    D3DLOCKED_RECT lock;if(FAILED((*t)->LockRect(0,&lock,0,0)))return false;
    for(unsigned int y=0;y<h;++y)memcpy((char*)lock.pBits+y*lock.Pitch,p+y*w,w*4);return SUCCEEDED((*t)->UnlockRect(0));
}
bool readConfig(const char* path,Melee360MenuConfig& c) {
    HANDLE file=CreateFileA(path,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);if(file==INVALID_HANDLE_VALUE)return false;
    unsigned char data[Melee360ConfigBytes];DWORD read=0,high=0,size=GetFileSize(file,&high);
    bool ok=!high&&size==sizeof(data)&&ReadFile(file,data,sizeof(data),&read,0)&&read==sizeof(data);CloseHandle(file);
    return ok&&Melee360ConfigDecode(c,data,sizeof(data));
}
bool writeConfig(const Melee360MenuConfig& config,const char* path,const char* temp) {
    unsigned char bytes[Melee360ConfigBytes];if(!Melee360ConfigEncode(config,bytes,sizeof(bytes)))return false;
    HANDLE file=CreateFileA(temp,GENERIC_WRITE,0,0,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,0);
    if(file==INVALID_HANDLE_VALUE)return false;
    DWORD written=0;bool ok=WriteFile(file,bytes,sizeof(bytes),&written,0)&&written==sizeof(bytes)&&FlushFileBuffers(file);CloseHandle(file);
    Melee360MenuConfig check;if(ok)ok=readConfig(temp,check)&&!memcmp(&check,&config,sizeof(check));
    if(ok)ok=MoveFileExA(temp,path,MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH)!=0;
    if(!ok)DeleteFileA(temp);
    return ok;
}
bool saveConfig() {
    if(testMode){model.dirty=false;return true;}
    if(!saveAllowed){saveNotice="Arquivo de configuracoes invalido: preservado.";return false;}
    bool ok=writeConfig(model.config,"game:\\melee360-menu.cfg","game:\\melee360-menu.tmp");
    if(ok){model.dirty=false;Melee360Log("Menu: configuration saved and readback verified\n");}
    saveNotice=ok?"Configuracoes salvas.":"Falha ao salvar. A configuracao anterior foi preservada.";return ok;
}
void quad(std::vector<Melee360SceneVertex>& v,float x,float y,float w,float h,float u0,float v0,float u1,float v1,unsigned int color) {
    const float pos[6][4]={{x,y,u0,v0},{x+w,y,u1,v0},{x,y+h,u0,v1},{x,y+h,u0,v1},{x+w,y,u1,v0},{x+w,y+h,u1,v1}};
    for(int i=0;i<6;++i){Melee360SceneVertex p;memset(&p,0,sizeof(p));p.clip[0]=pos[i][0]/320-1;p.clip[1]=1-pos[i][1]/240;p.clip[3]=1;
        p.uv[0]=pos[i][2];p.uv[1]=pos[i][3];for(int k=0;k<4;++k)p.color[k]=((color>>(k==0?16:k==1?8:k==2?0:24))&255)/255.f;v.push_back(p);}
}
void text(std::vector<Melee360SceneVertex>& out,const char* s,float x,float y,unsigned int color,float scale=1) {
    s=Melee360MenuTranslate(model,s);
    float start=x;for(unsigned int i=0;s[i];++i){unsigned char c=s[i];if(c=='\n'){x=start;y+=24*scale;continue;}if(c<32||c>127)c='?';unsigned int index=c-32;
        float u=(index%16)*16/256.f,v=(index/16)*24/144.f;quad(out,x,y,16*scale,24*scale,u,v,u+16/256.f,v+24/144.f,color);x+=11*scale;}
}
bool draw(IDirect3DDevice9* d,std::vector<Melee360SceneVertex>& vertices,IDirect3DTexture9* texture) {
    if(vertices.empty())return true;d->SetTexture(0,texture);return SUCCEEDED(d->DrawPrimitiveUP(D3DPT_TRIANGLELIST,(unsigned int)vertices.size()/3,&vertices[0],sizeof(Melee360SceneVertex)));
}
}
void Melee360MenuClose() {
    if(movieActive){Melee360IntroVideoClose();Melee360CloseIntro();movieActive=false;}
    if(ready)lastSound=model.config.values[7];
    if(ready&&model.dirty&&!testMode)saveConfig();
    if(ready){XINPUT_VIBRATION stop={0,0};for(DWORD i=0;i<4;++i)XInputSetState(i,&stop);}
    if(font)font->Release();font=0;if(white)white->Release();white=0;if(vs)vs->Release();vs=0;if(ps)ps->Release();ps=0;if(declaration)declaration->Release();declaration=0;ready=false;
}
bool Melee360MenuInit(IDirect3DDevice9* device,bool automated,unsigned int initialButtons) {
    menuDevice=device;
    Melee360MenuClose();testMode=automated;Melee360MenuReset(model);previous=initialButtons;nextRepeat=lastSave=0;memset(rumbleUntil,0,sizeof(rumbleUntil));reported=false;saveAllowed=true;saveNotice="";
    if(!testMode){HANDLE existing=CreateFileA("game:\\melee360-menu.cfg",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
        if(existing!=INVALID_HANDLE_VALUE){CloseHandle(existing);saveAllowed=readConfig("game:\\melee360-menu.cfg",model.config);if(!saveAllowed)saveNotice="Arquivo de configuracoes invalido: preservado.";}}
    if(pendingSound>=0){model.config.values[7]=(unsigned char)pendingSound;model.dirty=true;pendingSound=-1;}lastSound=model.config.values[7];
    unsigned char encoded[Melee360ConfigBytes];Melee360MenuConfig check;
    if(!Melee360ConfigEncode(model.config,encoded,sizeof(encoded))||!Melee360ConfigDecode(check,encoded,sizeof(encoded))||memcmp(&check,&model.config,sizeof(check))){Melee360Log("Menu: configuration ABI FAILED\n");return false;}
    Melee360Log("Menu: configuration ABI/serialization passed\n");
    if(testMode){char path[96],temp[96];sprintf_s(path,sizeof(path),"game:\\menu-verification-%lu.cfg",GetTickCount());sprintf_s(temp,sizeof(temp),"%s.tmp",path);
        HANDLE existing=CreateFileA(path,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
        if(existing!=INVALID_HANDLE_VALUE){CloseHandle(existing);Melee360Log("Menu: persistence test path already exists FAILED\n");return false;}
        bool stored=writeConfig(model.config,path,temp);if(stored)stored=readConfig(path,check)&&!memcmp(&check,&model.config,sizeof(check));
        if(stored){DeleteFileA(path);Melee360Log("Menu: file persistence write/rename/readback passed\n");}
        else{Melee360Log("Menu: file persistence FAILED\n");return false;}}
    statsLoaded=statsValid=false;recordFighter=8;recordOpponent=0;
    soundSelection=0;soundPlaying=-1;HANDLE soundFlag=CreateFileA("game:\\sound-preview.flag",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);soundTest=testMode&&soundFlag!=INVALID_HANDLE_VALUE;if(soundFlag!=INVALID_HANDLE_VALUE)CloseHandle(soundFlag);
    HANDLE archiveFlag=CreateFileA("game:\\archive-preview.flag",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);archiveTest=testMode&&archiveFlag!=INVALID_HANDLE_VALUE;if(archiveFlag!=INVALID_HANDLE_VALUE)CloseHandle(archiveFlag);
    HANDLE optionsFlag=CreateFileA("game:\\options-preview.flag",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);optionsTest=testMode&&optionsFlag!=INVALID_HANDLE_VALUE;if(optionsFlag!=INVALID_HANDLE_VALUE)CloseHandle(optionsFlag);
    HANDLE dataFlag=CreateFileA("game:\\data-preview.flag",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);dataTest=testMode&&dataFlag!=INVALID_HANDLE_VALUE;if(dataFlag!=INVALID_HANDLE_VALUE)CloseHandle(dataFlag);
    mapActive=false;trainingMode=trainingBlocked=false;character=1;characterConfirmed=false;stageActive=false;stageBackground=0;HANDLE flag=CreateFileA("game:\\character-preview.flag",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);characterTest=testMode&&flag!=INVALID_HANDLE_VALUE;if(flag!=INVALID_HANDLE_VALUE)CloseHandle(flag);
    flag=CreateFileA("game:\\training-preview.flag",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);trainingTest=testMode&&flag!=INVALID_HANDLE_VALUE;if(flag!=INVALID_HANDLE_VALUE)CloseHandle(flag);
    flag=CreateFileA("game:\\stage-preview.flag",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);stageTest=testMode&&flag!=INVALID_HANDLE_VALUE;if(flag!=INVALID_HANDLE_VALUE)CloseHandle(flag);
    flag=CreateFileA("game:\\trophy-preview.flag",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);trophyTest=testMode&&flag!=INVALID_HANDLE_VALUE;if(flag!=INVALID_HANDLE_VALUE)CloseHandle(flag);trophyLoaded=false;trophyList=false;trophyTick=0;trophyAwardTime=0;trophyRotation=0;if(testMode){trophyCoins=105;trophyCopies[0]=1;trophyCopies[1]=0;trophySelected=0;}
    flag=CreateFileA("game:\\animation-preview.flag",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);animationTest=testMode&&flag!=INVALID_HANDLE_VALUE;if(flag!=INVALID_HANDLE_VALUE)CloseHandle(flag);transitionBackward=false;
    background=Melee360MenuBackgroundInit(device);
    D3DVERTEXELEMENT9 e[]={{0,0,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},{0,16,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},{0,24,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},D3DDECL_END()};
    bool ok=SUCCEEDED(device->CreateVertexShader((DWORD*)Melee360SceneVS,&vs))&&SUCCEEDED(device->CreatePixelShader((DWORD*)Melee360ScenePS,&ps))&&SUCCEEDED(device->CreateVertexDeclaration(e,&declaration));
    std::vector<unsigned int> pixels(256*144);for(unsigned int i=0;i<pixels.size();++i)pixels[i]=((unsigned int)Melee360MenuFontAlpha[i]<<24)|0xFFFFFF;
    unsigned int pixel=0xFFFFFFFF;if(ok)ok=upload(device,256,144,&pixels[0],&font)&&upload(device,1,1,&pixel,&white);
    if(!ok){Melee360MenuClose();return false;}ready=true;Melee360Log(background?"Menu: native navigation ready with original HSD background\n":"Menu: native navigation ready; HSD background unavailable\n");return true;
}
bool Melee360MenuUpdate(unsigned int buttons,unsigned int ticks) {
    if(!ready)return false;unsigned int triggered=buttons&~previous;
    unsigned int arrows=buttons&(XINPUT_GAMEPAD_DPAD_UP|XINPUT_GAMEPAD_DPAD_DOWN|XINPUT_GAMEPAD_DPAD_LEFT|XINPUT_GAMEPAD_DPAD_RIGHT);
    if(arrows){if(arrows!=(previous&15))nextRepeat=ticks+350;else if((int)(ticks-nextRepeat)>=0){triggered|=arrows;nextRepeat=ticks+120;}}
    tickRumble(ticks);previous=buttons;bool returnTitle=false;unsigned int oldRumble=rumbleMask();int oldPage=model.page,oldLeaf=model.leaf,oldSound=model.config.values[7];
    if(model.leaf==150){
        if(triggered&XINPUT_GAMEPAD_B)Melee360MenuInput(model,MenuBack);
        else {if(triggered&XINPUT_GAMEPAD_DPAD_LEFT)recordFighter=(recordFighter+24)%25;if(triggered&XINPUT_GAMEPAD_DPAD_RIGHT)recordFighter=(recordFighter+1)%25;if(triggered&XINPUT_GAMEPAD_DPAD_UP)recordOpponent=(recordOpponent+24)%25;if(triggered&XINPUT_GAMEPAD_DPAD_DOWN)recordOpponent=(recordOpponent+1)%25;}
        return false;
    }
    if(model.leaf==127){
        if(soundFadeStart){unsigned int elapsed=ticks-soundFadeStart;soundFade=elapsed>=833?0:1.f-elapsed/833.f;if(elapsed>=833){soundPlaying=-1;soundFadeStart=0;Melee360Log("Sound test: fade-out completed\n");}}
        if((triggered&XINPUT_GAMEPAD_START)&&soundPlaying>=0){soundFadeStart=ticks;Melee360Log("Sound test: fade-out started\n");}
        if(triggered&XINPUT_GAMEPAD_B){soundPlaying=-1;model.leaf=-1;Melee360Log("Sound test: returned to Data menu\n");}
        else if(triggered&(XINPUT_GAMEPAD_DPAD_LEFT|XINPUT_GAMEPAD_DPAD_RIGHT|XINPUT_GAMEPAD_DPAD_UP|XINPUT_GAMEPAD_DPAD_DOWN)){int dir=(triggered&(XINPUT_GAMEPAD_DPAD_LEFT|XINPUT_GAMEPAD_DPAD_UP))?-1:1;soundSelection=(soundSelection+dir+Melee360SoundTrackCount)%Melee360SoundTrackCount;}
        else if(triggered&XINPUT_GAMEPAD_X){soundPlaying=-1;Melee360Log("Sound test: playback stopped\n");}
        else if(triggered&XINPUT_GAMEPAD_A){if(soundPlaying==soundSelection){soundPlaying=-1;Melee360Log("Sound test: playback stopped\n");return false;}soundFade=1;soundFadeStart=0;soundPlaying=soundSelection;char report[128];sprintf_s(report,sizeof(report),"Sound test: play original id=%d file=%s\n",soundPlaying,Melee360MusicFiles[Melee360SoundTrackIds[soundPlaying]]);Melee360Log(report);}
        return false;
    }
    if(model.leaf>=111&&model.leaf<=113){if(!trophyLoaded){trophyPersist(true);trophyLoaded=true;}unsigned int delta=trophyTick?ticks-trophyTick:0;trophyTick=ticks;if(delta>100)delta=100;int sx=0,sy=0;Melee360PadStick(&sx,&sy);trophyRotation+=sx*delta*.000008f;
        if(trophyTest)trophyRotation+=delta*.0005f;
        if(triggered&XINPUT_GAMEPAD_B){if(trophyList)trophyList=false;else{model.leaf=-1;trophyAwardTime=0;Melee360Log("Trophies: returned to original trophy menu\n");}return false;}
        if(model.leaf==111){if(triggered&XINPUT_GAMEPAD_Y){trophyList=!trophyList;Melee360Log(trophyList?"Trophies: list opened\n":"Trophies: list closed\n");}if((triggered&(XINPUT_GAMEPAD_DPAD_LEFT|XINPUT_GAMEPAD_DPAD_RIGHT|XINPUT_GAMEPAD_DPAD_UP|XINPUT_GAMEPAD_DPAD_DOWN))&&trophyCopies[1])trophySelected=1-trophySelected;}
        else if(model.leaf==112){if(triggered&XINPUT_GAMEPAD_DPAD_UP)trophySpend=trophySpend<20?trophySpend+1:20;if(triggered&XINPUT_GAMEPAD_DPAD_DOWN)trophySpend=trophySpend>1?trophySpend-1:1;
            if((triggered&XINPUT_GAMEPAD_A)&&!trophyAwardTime&&trophyCoins>=trophySpend&&trophyCopies[1]<9999){trophyCoins-=trophySpend;++trophyCopies[1];trophySelected=1;trophyAwardTime=ticks+2000;trophyPersist(false);Melee360Log("Trophies: diagnostic lottery acquired Party Ball; local demo reward applied\n");}
            if(trophyAwardTime&&(int)(ticks-trophyAwardTime)>=0)trophyAwardTime=0;}
        return false;}
    if(mapActive){unsigned int delta=ticks-mapTick;mapTick=ticks;if(delta>100)delta=100;mapAccumulator+=delta;int sx=0,sy=0;Melee360PadStick(&sx,&sy);if(buttons&XINPUT_GAMEPAD_DPAD_LEFT)sx=-80;if(buttons&XINPUT_GAMEPAD_DPAD_RIGHT)sx=80;if(buttons&XINPUT_GAMEPAD_DPAD_DOWN)sy=-80;if(buttons&XINPUT_GAMEPAD_DPAD_UP)sy=80;while(mapAccumulator>=16){mapAccumulator-=16;Melee360StageMove(sx,sy);}float x,y;Melee360StageCursor(&x,&y,&mapHovered);
        if(triggered&XINPUT_GAMEPAD_B){mapActive=false;trainingBlocked=false;Melee360Log("Stage select: returned to original CSS\n");return false;}
        if(triggered&(XINPUT_GAMEPAD_A|XINPUT_GAMEPAD_START)){if(mapHovered<0||Melee360StageKind(mapHovered)!=31){Melee360Log("Stage select: unavailable stage rejected\n");}else{Melee360CSSState cursor;Melee360CSSGetState(&cursor);if(trainingMode){if(!Melee360TrainingPrepare(cursor.ckind))return false;trainingBlocked=true;Melee360Log("Training: original rules/player data prepared for Battlefield; fighter runtime NOT started\n");}else{mapActive=false;stageActive=true;stageBackground=0;Melee360Log("Battlefield: entered stage animation diagnostic\n");}}}return false;}
    if(stageActive){if(triggered&XINPUT_GAMEPAD_B){stageActive=false;Melee360Log("Battlefield: returned to character select\n");}
        else if(triggered&XINPUT_GAMEPAD_RIGHT_SHOULDER)stageBackground=(stageBackground+1)%4;
        else if(triggered&XINPUT_GAMEPAD_LEFT_SHOULDER)stageBackground=(stageBackground+3)%4;return false;}
    if(movieActive){if((triggered&(XINPUT_GAMEPAD_B|XINPUT_GAMEPAD_A|XINPUT_GAMEPAD_START))||Melee360IntroVideoFinished()){
            Melee360IntroVideoClose();Melee360CloseIntro();movieActive=false;Melee360Log("Menu archive: video returned to archive menu\n");}return false;}
    if(model.leaf==109){
        unsigned int elapsed=ticks-cssTick;cssTick=ticks;if(elapsed>133)elapsed=133;cssAccumulator+=elapsed*60;int steps=(int)(cssAccumulator/1000);cssAccumulator%=1000;
        int sx=0,sy=0;Melee360PadStick(&sx,&sy);
        if(testMode){sx=sy=0;if(characterTest){int target=-1;switch(cssTestFrame){case 120:target=2;break;case 150:target=11;break;case 180:target=19;break;case 210:target=18;break;case 240:target=10;break;}if(target>=0)Melee360CSSPlaceAtIcon(target);}}
        else{if(buttons&XINPUT_GAMEPAD_DPAD_LEFT)sx=-80;else if(buttons&XINPUT_GAMEPAD_DPAD_RIGHT)sx=80;if(buttons&XINPUT_GAMEPAD_DPAD_DOWN)sy=-80;else if(buttons&XINPUT_GAMEPAD_DPAD_UP)sy=80;}
        for(int n=0;n<steps;++n)Melee360CSSAdvance(sx,sy);
        Melee360CSSState cursor;Melee360CSSGetState(&cursor);
        if(cursor.hover>=0&&cursor.hover!=character&&!cursor.confirmed){character=cursor.hover;char msg[96];sprintf_s(msg,sizeof(msg),"Character select: hover slot=%d; original hit bounds\n",character);Melee360Log(msg);}
        characterConfirmed=cursor.confirmed!=0;
        if(characterConfirmed&&(triggered&XINPUT_GAMEPAD_START)){if(stageTest){stageActive=true;stageBackground=0;Melee360Log("Battlefield: entered stage animation diagnostic\n");}else{mapActive=true;trainingBlocked=false;Melee360StageInit();mapTick=ticks;mapAccumulator=0;mapHovered=-1;Melee360Log("Stage select: entered original SSS boundary\n");}return false;}
        if(triggered&XINPUT_GAMEPAD_B){if(characterConfirmed){Melee360CSSRetrieve();characterConfirmed=false;Melee360Log("Character select: confirmation cancelled; original token retrieved\n");}else{model.leaf=-1;Melee360Log(trainingMode?"Character select: returned to Training menu\n":"Character select: returned to VS menu\n");}}
        else if(triggered&(XINPUT_GAMEPAD_A|XINPUT_GAMEPAD_START)){if(Melee360CSSConfirm()){Melee360CSSGetState(&cursor);character=cursor.selected;characterConfirmed=true;char msg[192];sprintf_s(msg,sizeof(msg),"Character select: confirmed slot=%d name=%s; original player CKind=%d; gameplay not started\n",character,Melee360CharacterNames[character],cursor.ckind);Melee360Log(msg);}}
        return false;
    }
    if(triggered&XINPUT_GAMEPAD_B)returnTitle=Melee360MenuInput(model,MenuBack);
    else if(triggered&(XINPUT_GAMEPAD_A|XINPUT_GAMEPAD_START))Melee360MenuInput(model,MenuAccept);
    else if(triggered&XINPUT_GAMEPAD_DPAD_UP)Melee360MenuInput(model,MenuUp);
    else if(triggered&XINPUT_GAMEPAD_DPAD_DOWN)Melee360MenuInput(model,MenuDown);
    else if(triggered&XINPUT_GAMEPAD_DPAD_LEFT)Melee360MenuInput(model,MenuLeft);
    else if(triggered&XINPUT_GAMEPAD_DPAD_RIGHT)Melee360MenuInput(model,MenuRight);
    if(oldPage!=model.page)transitionBackward=(triggered&XINPUT_GAMEPAD_B)!=0;
    if(oldPage!=model.page||oldLeaf!=model.leaf){char message[128];sprintf_s(message,sizeof(message),"Menu navigation: page=%d selection=%d destination=%d\n",model.page,model.selection,model.leaf);Melee360Log(message);}
    if(model.config.values[7]!=oldSound){if(model.config.values[7]<=1)OSSetSoundMode(model.config.values[7]);if(OSGetSoundMode()!=(model.config.values[7]==0?0u:1u))Melee360Log("OS sound mode synchronization FAILED\n");else Melee360Log("OS sound mode synchronized with menu setting\n");}
    if(model.leaf==150&&oldLeaf!=150){recordFighter=8;recordOpponent=0;loadStats();Melee360Log("Data records: per-fighter read-only viewer entered\n");}
    if(model.leaf==127&&oldLeaf!=127){soundSelection=0;soundPlaying=-1;soundFade=1;soundFadeStart=0;Melee360Log("Sound test: original HPS catalog ready\n");}
    if(model.leaf==108){trainingMode=true;model.leaf=109;Melee360Log("Training: original CSS entry; CPU selection pending\n");}else if(model.leaf==109&&oldLeaf!=109)trainingMode=false;
    if(model.leaf==109&&oldLeaf!=109){character=1;characterConfirmed=false;Melee360CSSInit();cssTick=ticks;cssAccumulator=0;Melee360Log("Character select: entered diagnostic original CSS; original cursor/token excerpts active\n");}
    if(model.leaf==201||model.leaf==202){const char* filename=model.leaf==201?"MvOmake15.mth":"MvHowto.mth";model.leaf=-1;
        movieTrack=filename[2]=='O'?Melee360MusicTrackBase+0x52:Melee360MusicTrackBase+0x24;
        bool prepared=Melee360PrepareMovie(filename)==1;if(prepared)Melee360AudioPump(movieTrack);
        movieActive=prepared&&Melee360IntroVideoInit(menuDevice);
        if(movieActive)Melee360Log("Menu archive: original movie playback started\n");
        else{Melee360IntroVideoClose();Melee360CloseIntro();saveNotice="O video nao pode ser aberto.";}}
    unsigned int newRumble=rumbleMask();if(oldRumble!=newRumble){for(int i=0;i<4;++i)if((oldRumble^newRumble)&(1u<<i))rumbleUntil[i]=(newRumble&(1u<<i))?ticks+180:0;Melee360Log("Options: per-port rumble setting changed\n");}
    if(!testMode){for(DWORD i=0;i<4;++i){XINPUT_VIBRATION motors={0,0};if((newRumble&(1u<<i))&&(int)(rumbleUntil[i]-ticks)>0)motors.wLeftMotorSpeed=motors.wRightMotorSpeed=12000;XInputSetState(i,&motors);}}
    if(model.dirty&&(int)(ticks-lastSave)>750){saveConfig();lastSave=ticks;}
    return returnTitle;
}
unsigned int Melee360MenuTestButtons(unsigned int frame) {
    if(dataTest){switch(frame){case 30:case 60:case 90:case 120:case 180:case 210:case 240:case 450:case 480:return XINPUT_GAMEPAD_DPAD_DOWN;case 150:case 270:case 300:case 510:return XINPUT_GAMEPAD_A;case 330:return XINPUT_GAMEPAD_DPAD_RIGHT;case 360:return XINPUT_GAMEPAD_DPAD_UP;case 390:case 570:case 600:case 630:case 660:return XINPUT_GAMEPAD_B;default:return 0;}}
    if(optionsTest){switch(frame){case 30:case 60:case 90:case 210:case 300:case 420:return XINPUT_GAMEPAD_DPAD_DOWN;case 120:case 150:case 330:return XINPUT_GAMEPAD_A;case 180:case 240:case 390:return XINPUT_GAMEPAD_DPAD_RIGHT;case 360:case 450:return XINPUT_GAMEPAD_DPAD_LEFT;case 270:case 480:case 510:case 540:return XINPUT_GAMEPAD_B;default:return 0;}}
    if(archiveTest){switch(frame){case 30:case 60:case 90:case 120:case 180:case 330:return XINPUT_GAMEPAD_DPAD_DOWN;case 150:case 210:case 240:case 360:return XINPUT_GAMEPAD_A;case 300:case 420:case 450:case 480:case 510:return XINPUT_GAMEPAD_B;default:return 0;}}
    if(soundTest){switch(frame){case 30:case 60:case 90:case 120:case 180:case 210:return XINPUT_GAMEPAD_DPAD_DOWN;case 150:case 240:case 270:case 360:return XINPUT_GAMEPAD_A;case 330:return XINPUT_GAMEPAD_DPAD_RIGHT;case 390:return XINPUT_GAMEPAD_START;case 480:return XINPUT_GAMEPAD_X;case 510:case 540:case 570:return XINPUT_GAMEPAD_B;default:return 0;}}
    if(trainingTest){if(frame==270)Melee360StageTestPlaceAt(0);if(frame==300)Melee360StageTestPlaceAt(24);switch(frame){case 60:case 180:case 210:case 270:case 330:return XINPUT_GAMEPAD_A;case 90:case 120:case 150:return XINPUT_GAMEPAD_DPAD_DOWN;case 240:return XINPUT_GAMEPAD_START;case 360:case 390:case 420:case 450:return XINPUT_GAMEPAD_B;default:return 0;}}

    if(trophyTest){switch(frame){case 60:case 90:case 270:case 480:return XINPUT_GAMEPAD_DPAD_DOWN;case 120:case 150:case 300:case 330:case 510:case 690:return XINPUT_GAMEPAD_A;case 180:case 210:return XINPUT_GAMEPAD_Y;case 240:case 450:case 600:case 810:case 840:return XINPUT_GAMEPAD_B;case 630:case 660:return XINPUT_GAMEPAD_DPAD_UP;case 720:return XINPUT_GAMEPAD_DPAD_RIGHT;default:return 0;}}
    cssTestFrame=frame;
    if(stageTest){switch(frame){case 30:return XINPUT_GAMEPAD_DPAD_DOWN;case 60:case 90:case 120:return XINPUT_GAMEPAD_A;case 150:return XINPUT_GAMEPAD_START;
        case 420:case 720:case 1020:return XINPUT_GAMEPAD_RIGHT_SHOULDER;case 1320:case 1350:case 1380:case 1410:return XINPUT_GAMEPAD_B;default:return 0;}}
    if(animationTest){switch(frame){case 420:return XINPUT_GAMEPAD_DPAD_DOWN;case 450:return XINPUT_GAMEPAD_A;case 840:case 900:return XINPUT_GAMEPAD_B;default:return 0;}}
    if(characterTest){switch(frame){case 30:return XINPUT_GAMEPAD_DPAD_DOWN;case 60:case 90:case 270:return XINPUT_GAMEPAD_A;
        case 120:return XINPUT_GAMEPAD_DPAD_RIGHT;case 150:case 180:return XINPUT_GAMEPAD_DPAD_DOWN;case 210:return XINPUT_GAMEPAD_DPAD_LEFT;case 240:return XINPUT_GAMEPAD_DPAD_UP;
        case 300:case 330:case 360:case 390:return XINPUT_GAMEPAD_B;default:return 0;}}
    switch(frame){case 30:case 60:case 90:case 240:case 360:case 600:case 630:case 750:return XINPUT_GAMEPAD_A;
        case 120:case 150:case 180:case 480:case 510:case 690:case 810:case 840:case 1110:case 1290:case 1320:case 1350:case 1380:return XINPUT_GAMEPAD_B;
        case 210:case 270:case 300:case 330:case 420:case 540:case 570:case 720:case 870:case 930:case 1140:return XINPUT_GAMEPAD_DPAD_DOWN;
        case 900:case 960:case 990:case 1170:return XINPUT_GAMEPAD_A;
        case 390:case 450:case 660:case 780:return XINPUT_GAMEPAD_DPAD_RIGHT;default:return 0;}
}
bool Melee360MenuDraw(IDirect3DDevice9* device) {
    if(!ready)return false;
    if(stageActive&&(!Melee360BattlefieldPage(device,stageBackground)||!Melee360TitleDraw(device)))return false;
    if(movieActive){if(Melee360IntroVideoDraw(device))return true;Melee360IntroVideoClose();Melee360CloseIntro();movieActive=false;saveNotice="O video nao pode ser aberto.";}
    if(!stageActive&&!mapActive&&model.leaf<0&&!model.editing&&!model.confirmReset&&Melee360OriginalMenuSupported(model.page)){
        if(!Melee360OriginalMenuPage(device,model.page,model.selection,transitionBackward))return false;
        Melee360SceneSetWide(false);if(!Melee360TitleDraw(device))return false;
        if(!reported){Melee360Log("Menu: first original selectable menu draw submitted; root input uses upstream mn_8022DB10\n");reported=true;}return true;
    }
    bool optionsScreen=model.leaf<0&&(model.page==19||model.page==20);unsigned int connected=0;if(optionsScreen){for(DWORD port=0;port<4;++port){XINPUT_STATE pad;if(XInputGetState(port,&pad)==ERROR_SUCCESS)connected|=1u<<port;}if(testMode)connected=15;if(!Melee360OptionsPage(device,model.page,model.selection,model.config.values[7],model.config.values[8],rumbleMask(),connected)||!Melee360TitleDraw(device))return false;}
    bool statsScreen=model.leaf==152;if(statsScreen&&(!Melee360OptionsPage(device,152,0,1,8,0,0)||!Melee360TitleDraw(device)))return false;
    bool soundScreen=model.leaf==127;
    if(soundScreen&&(!Melee360SoundTestPage(device,soundPlaying>=0&&Melee360AudioTrackStatus(Melee360MusicTrackBase+Melee360SoundTrackIds[soundPlaying])==1)||!Melee360TitleDraw(device)))return false;
    bool trophy=model.leaf>=111&&model.leaf<=113;
    if(trophy){if(!Melee360TrophyPage(device,model.leaf==113?(trophyCopies[1]?1:0):model.leaf==112?1:trophySelected,model.leaf==113,trophyRotation)||!Melee360TitleDraw(device))return false;}
    if(mapActive){float x,y;Melee360StageCursor(&x,&y,&mapHovered);if(!Melee360StageSelectPage(device,x,y,mapHovered)||!Melee360TitleDraw(device))return false;}
    bool css=model.leaf==109&&!stageActive&&!mapActive;
    if(css){if(!Melee360CharacterSelectPage(device,character)||!Melee360TitleDraw(device))return false;}
    Melee360SceneSetWide(css||stageActive||mapActive?false:model.config.values[10]!=0);
    if(!statsScreen&&!optionsScreen&&!soundScreen&&!css&&!stageActive&&!mapActive&&!trophy)device->Clear(0,0,D3DCLEAR_TARGET,D3DCOLOR_XRGB(14,22,42),1,0);
    device->SetVertexDeclaration(declaration);device->SetVertexShader(vs);device->SetPixelShader(ps);device->SetRenderState(D3DRS_ZENABLE,FALSE);device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);device->SetRenderState(D3DRS_ALPHATESTENABLE,FALSE);
    const float viewport[4]={!css&&model.config.values[10]?1.f:.75f,0,0,0};device->SetVertexShaderConstantF(0,viewport,1);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCALPHA);
    device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);device->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);device->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);
    std::vector<Melee360SceneVertex> boxes,letters;
    if(mapActive){quad(boxes,18,416,604,58,0,0,1,1,0xDD101628);text(letters,trainingMode?"Training / selecao original de cenario":"Selecao original de cenario",28,421,0xFFFFFFFF,.8f);text(letters,trainingBlocked?"Dados prontos. Runtime de partida ainda pendente.":mapHovered>=0&&Melee360StageKind(mapHovered)==31?"Battlefield: A confirma. B: personagens.":"Somente Battlefield habilitado. B: personagens.",28,446,trainingBlocked?0xFFFFCF70:0xFFFFFFFF,.75f);return draw(device,boxes,white)&&draw(device,letters,font);}
    if(trophy){quad(boxes,18,20,604,40,0,0,1,1,0xE51E4625);text(letters,model.leaf==111?"Trofeus / Galeria":model.leaf==112?"Trofeus / Loteria":"Trofeus / Colecao",28,26,0xFFFFFFFF,1.1f);
        char label[128];if(model.leaf==111){const char* name=trophySelected?"Party Ball":"Daisy";quad(boxes,350,80,270,330,0,0,1,1,0xDD0E2018);text(letters,name,365,88,0xFFFFCF30,1.4f);
            const char* daisy[]={"Princesa de Sarasaland.","Conheceu Mario quando ele", "a salvou de Tatanga em", "Super Mario Land.","Seu primeiro jogo:","Super Mario Land - 8/89"};const char* party[]={"Uma bola cheia de itens.","Quando se abre, derruba", "objetos sobre o cenario.","Primeiro jogo:","Super Smash Bros. Melee", "12/01"};for(int i=0;i<6;++i)text(letters,trophySelected?party[i]:daisy[i],360,145+i*28,0xFFFFFFFF,.75f);
            sprintf_s(label,sizeof(label),"Copias: %d",trophyCopies[trophySelected]);text(letters,label,360,355,0xFFBBDFBB,.85f);if(trophyList){quad(boxes,35,80,285,140,0,0,1,1,0xED193525);text(letters,"Lista de trofeus",45,90,0xFFFFFFFF,.9f);text(letters,"Daisy",50,130,0xFFFFFFFF,.9f);if(trophyCopies[1])text(letters,"Party Ball",50,165,0xFFFFFFFF,.9f);}}
        else if(model.leaf==112){sprintf_s(label,sizeof(label),"Moedas: %d  Usar: %d",trophyCoins,trophySpend);text(letters,label,35,76,0xFFFFD83F,1);text(letters,trophyAwardTime?"TROFEU OBTIDO: Party Ball":"A: obter Party Ball (loteria de teste)",30,360,0xFFFFFFFF,.9f);text(letters,"Cima/baixo: moedas. Regras originais pendentes.",25,390,0xFFC8D1DF,.7f);}
        else {sprintf_s(label,sizeof(label),"Daisy x%d    Party Ball x%d",trophyCopies[0],trophyCopies[1]);text(letters,label,100,400,0xFFFFFFFF,.9f);}
        text(letters,"Demo: 2 trofeus. Analogico: girar. B: voltar.",25,443,0xFFB8D4BB,.75f);if(model.leaf==111)text(letters,"Direcional: trocar. Y: lista.",25,416,0xFFFFFFFF,.8f);return draw(device,boxes,white)&&draw(device,letters,font);}
    if(stageActive){quad(boxes,18,420,604,48,0,0,1,1,0xDD101628);text(letters,"Battlefield: teste de animacoes. Sem partida.",28,425,0xFFFFCF70,.8f);text(letters,"LB/RB: fundo  B: voltar. Particulas pendentes.",28,448,0xFFFFFFFF,.8f);return draw(device,boxes,white)&&draw(device,letters,font);}
    if(css){text(letters,Melee360CharacterNames[character],58,394,0xFFFFFFFF,.7f);text(letters,"P1",55,417,0xFFFFFFFF,.8f);text(letters,characterConfirmed?"START: teste Battlefield (sem partida). B: pegar ficha":"A: soltar ficha. B: voltar. Sem partida nesta build.",28,462,0xFFC8D1DF,.65f);return draw(device,letters,font);}
    if(optionsScreen){char label[128];Melee360MenuLabel(model,model.selection,label,sizeof(label));quad(boxes,24,390,592,80,0,0,1,1,0xCC101628);text(letters,label,32,396,0xFFFFFFFF,.85f);text(letters,model.page==19?"Cima/baixo: controle  A/esquerda/direita: ligar/desligar":"Cima/baixo: ajuste  Esquerda/direita: valor",32,421,0xFFFFFFFF,.65f);text(letters,model.page==20?"Mono/stereo e musica aplicados. Efeitos/Surround pendentes.":"Configuracao por controle salva. B: voltar.",32,447,0xFFFFCF70,.65f);return draw(device,boxes,white)&&draw(device,letters,font);}
    quad(boxes,30,24,580,432,0,0,1,1,0xE5101628);quad(boxes,30,24,580,48,0,0,1,1,0xF0223355);
    text(letters,Melee360MenuTitle(model),48,35,0xFFFFFFFF,1.25f);
    text(letters,"Tela provisoria do port",380,57,0xFFFFCF70,.7f);
    int count=Melee360MenuCount(model),first=model.selection>=9?model.selection-8:0;
    if(soundScreen){boxes.clear();letters.clear();char label[128];sprintf_s(label,sizeof(label),"%02d / %d  %s",soundSelection+1,Melee360SoundTrackCount,Melee360MusicFiles[Melee360SoundTrackIds[soundSelection]]);quad(boxes,24,388,592,82,0,0,1,1,0xCC101628);text(letters,label,32,396,0xFFFFFFFF,.8f);int status=soundPlaying<0?0:Melee360AudioTrackStatus(Melee360MusicTrackBase+Melee360SoundTrackIds[soundPlaying]);text(letters,soundPlaying<0?"Parado":status<0?"Arquivo indisponivel":status==2?"Concluido":status==1?"Reproduzindo musica original":"Carregando",32,420,0xFFFFCF70,.75f);text(letters,"Direcional: musica  A: ouvir/parar  START: fade  B: voltar",32,447,0xFFFFFFFF,.7f);return draw(device,boxes,white)&&draw(device,letters,font);}
    if(model.leaf==150){char label[160];text(letters,"Recordes Versus / snapshot original",48,92,0xFFFFCF70,.9f);
        if(statsValid){const Melee360FighterStats& f=importedStats.fighters[recordFighter];sprintf_s(label,sizeof(label),"%02d / 25  %s",recordFighter+1,recordNames[recordFighter]);text(letters,label,48,126,0xFFFFFFFF);
            sprintf_s(label,sizeof(label),"Partidas: %u  Vitorias: %u  Derrotas: %u",f.matches,f.wins,f.losses);text(letters,label,48,164,0xFFFFFFFF,.8f);
            sprintf_s(label,sizeof(label),"Dano causado: %d  Recebido: %d",f.damageDealt,f.damageTaken);text(letters,label,48,194,0xFFFFFFFF,.8f);
            sprintf_s(label,sizeof(label),"Ataques acertados: %u / %u",f.attacksHit,f.attacksTotal);text(letters,label,48,224,0xFFFFFFFF,.8f);
            sprintf_s(label,sizeof(label),"Autodestruicoes: %u  Dano maximo: %u",f.selfDestructs,f.peakDamage);text(letters,label,48,254,0xFFFFFFFF,.8f);
            sprintf_s(label,sizeof(label),"KOs contra %s: %u",recordNames[recordOpponent],f.opponentKOs[recordOpponent]);text(letters,label,48,291,0xFFFFCF70,.8f);
        }else text(letters,"Nenhum save original valido importado.",48,140,0xFFFFFFFF,.8f);
        text(letters,"Esq/dir: lutador. Cima/baixo: adversario. B: voltar.",48,365,0xFFFFFFFF,.65f);text(letters,"Somente leitura; renderer original de recordes pendente.",48,395,0xFFC8D1DF,.65f);return draw(device,boxes,white)&&draw(device,letters,font);
    }
    if(model.leaf==152){boxes.clear();letters.clear();loadStats();text(letters,"Recordes / Diversos",48,90,0xFFFFCF70);if(statsValid){const char* modes[]={"Partidas por tempo","Partidas por vidas","Partidas por moedas","Partidas por bonus","Partidas de energia","Reinicios"};char label[128];for(int i=0;i<6;++i){sprintf_s(label,sizeof(label),"%s: %u",modes[i],importedStats.matches[i]);text(letters,label,48,124+i*27,0xFFFFFFFF,.8f);}sprintf_s(label,sizeof(label),"KOs: %u  Autodestruicoes: %u  Trofeus: %u",importedStats.kos,importedStats.selfDestructs,importedStats.trophies);text(letters,label,48,302,0xFFFFFFFF,.7f);text(letters,"Snapshot do save original importado. Somente leitura.",48,340,0xFFC8D1DF,.7f);}else{text(letters,"Nenhum save original valido importado.",48,130,0xFFFFFFFF,.8f);}text(letters,"B: voltar. Partidas do port ainda nao geram recordes.",48,393,0xFFFFCF70,.7f);return draw(device,boxes,white)&&draw(device,letters,font);}
    if(model.leaf>=0){text(letters,"Ainda indisponivel nesta build.",48,105,0xFFFFCF70);text(letters,"O gameplay e esta tela ainda nao foram integrados.",48,134,0xFFC8D1DF,.9f);first=0;}
    for(int row=first;row<count&&row<first+9;++row){float y=(model.leaf>=0?205.f:86.f)+(row-first)*29;
        bool selected=model.leaf>=0||row==model.selection;if(selected)quad(boxes,44,y,550,28,0,0,1,1,0xEA3F6688);
        char label[128];Melee360MenuLabel(model,row,label,sizeof(label));if(!model.editing&&!model.confirmReset)text(letters,label,54,y+1,selected?0xFFFFFFFF:0xFFD7DFEA);}
    if(count>9){char position[32];sprintf_s(position,sizeof(position),"%d / %d",model.selection+1,count);text(letters,position,506,357,0xFFAEBFD1,.8f);}
    if(model.editing){quad(boxes,48,160,544,118,0,0,1,1,0xFE12243A);text(letters,"Editar nome",66,176,0xFFFFFFFF);text(letters,model.editedName,70,214,0xFFFFD56A,1.4f);quad(boxes,72+model.editPosition*15.4f,245,13,2,0,0,1,1,0xFFFFD56A);}
    if(model.confirmReset){quad(boxes,48,150,544,140,0,0,1,1,0xFE12243A);text(letters,"Restaurar configuracoes do port?",65,174,0xFFFFD56A);text(letters,"A: confirmar    B: cancelar",65,217,0xFFFFFFFF);}
    const char* description=Melee360MenuDescription(model);
    // Footer wraps to fit within the 4:3 panel.
    char line[64];unsigned int len=(unsigned int)strlen(description),cut=len>60?60:len;memcpy(line,description,cut);line[cut]=0;text(letters,line,44,385,0xFFAFC1D5,.82f);
    if(len>cut)text(letters,description+cut,44,403,0xFFAFC1D5,.82f);
    text(letters,saveNotice,44,429,0xFFBBDAD0,.75f);
    bool ok=draw(device,boxes,white)&&draw(device,letters,font);if(ok&&!reported){Melee360Log("Menu: first selectable menu/text draw submitted\n");reported=true;}return ok;
}
bool Melee360MenuAudioActive(){return ready&&!movieActive&&!stageActive;}
int Melee360MenuAudioTrack(){return !ready?0:movieActive?movieTrack:model.leaf==127?(soundPlaying<0?0:Melee360MusicTrackBase+Melee360SoundTrackIds[soundPlaying]):stageActive?2:1;}
float Melee360MenuMusicVolume(){return model.config.values[8]/10.f*(model.leaf==127?soundFade:1.f);}

bool Melee360MenuUsesOriginalCursor(){return ready&&model.leaf==109&&!stageActive&&!mapActive;}

int Melee360MenuSoundOutput(){return ready?model.config.values[7]:pendingSound>=0?pendingSound:lastSound;}
void Melee360MenuSetSoundOutput(unsigned int mode){if(mode>1)return;lastSound=(int)mode;if(ready){if(model.config.values[7]!=mode){model.config.values[7]=(unsigned char)mode;model.dirty=true;}}else pendingSound=(int)mode;}
int Melee360MenuSoundModeProbe(){int savedPending=pendingSound,savedLast=lastSound;unsigned char saved=model.config.values[7];bool dirty=model.dirty;OSSetSoundMode(0);bool ok=OSGetSoundMode()==0;OSSetSoundMode(1);ok=ok&&OSGetSoundMode()==1;OSSetSoundMode(99);ok=ok&&OSGetSoundMode()==1;pendingSound=savedPending;lastSound=savedLast;model.config.values[7]=saved;model.dirty=dirty;return ok;}
