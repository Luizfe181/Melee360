#include <xtl.h>
extern "C" {
#include <dolphin/gx/GXEnum.h>
#include <dolphin/gx/GXStruct.h>
#include <dolphin/gx/GXPixel.h>
#include <dolphin/gx/GXCull.h>
#include <dolphin/gx/GXTransform.h>
}
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "title_scene.h"
#include "hsd_scene.h"
#include "character_select.h"
#include "platform_log.h"
#include "scene_VS.h"
#include "scene_PS.h"
#include "scene_quantized_PS.h"
extern "C" int Melee360GXDepthCompression(void);
extern "C" float Melee360GXClearDepth(unsigned int);
namespace {
Melee360Scene scene;
std::vector<IDirect3DTexture9*> textures;
IDirect3DTexture9* white;
IDirect3DVertexShader9* vs;IDirect3DPixelShader9* ps;IDirect3DPixelShader9* psQuant;IDirect3DVertexDeclaration9* declaration;
int optionsPage,optionsSelection,optionsOutput,optionsMusic;unsigned int optionsRumble,optionsConnected;
bool ready,reported,isMenu,currentBackward,soundPlaying;
std::vector<unsigned char> menuArchive,titleArchive,cssArchive,stageArchive;int currentPage=-99,currentSelection=-99;
std::vector<unsigned char> fighterArchive,fighterMotion;DWORD fighterStart,lastFighter;unsigned int fighterTracks,fighterUpdates;bool fighterAnimated;double fighterBuildMs;
bool cssModelDiagnostic=false;
std::vector<unsigned char> mapArchive;float mapCursorX,mapCursorY;int mapHover;
std::vector<unsigned char> trophyArchives[2],trophyStandArchive;Melee360Scene trophyBase;float trophyAngle;
std::vector<unsigned char> menuSis,menuFont;Melee360Scene captionScene,fighterScene;
std::vector<unsigned int> textureHashes,textureWidths,textureHeights;DWORD animationStart,hoverStart,lastAnimation;unsigned int animationSamples;double animationBuildMs;
bool readResource(const char* path,std::vector<unsigned char>& data){
    if(!data.empty())return true;HANDLE f=CreateFileA(path,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);if(f==INVALID_HANDLE_VALUE)return false;
    DWORD high=0,bytes=GetFileSize(f,&high),read=0;if(high||bytes<32||bytes>8*1024*1024){CloseHandle(f);return false;}data.resize(bytes);
    bool ok=ReadFile(f,&data[0],bytes,&read,0)&&read==bytes;CloseHandle(f);if(!ok)data.clear();return ok;
}
float widthScale=.75f;
bool upload(IDirect3DDevice9* device,unsigned int w,unsigned int h,const unsigned int* pixels,IDirect3DTexture9** texture) {
    if(FAILED(device->CreateTexture(w,h,1,0,(D3DFORMAT)MAKESRGBFMT(D3DFMT_LIN_A8R8G8B8),D3DPOOL_DEFAULT,texture,0)))return false;
    D3DLOCKED_RECT lock;if(FAILED((*texture)->LockRect(0,&lock,0,0)))return false;
    for(unsigned int y=0;y<h;++y)memcpy((char*)lock.pBits+y*lock.Pitch,pixels+y*w,w*4);
    return SUCCEEDED((*texture)->UnlockRect(0));
}
}
void Melee360TitleClose() {
    Melee360ResetSceneCache();
    for(unsigned int i=0;i<textures.size();++i)if(textures[i])textures[i]->Release();textures.clear();
    if(white)white->Release();white=0;if(vs)vs->Release();vs=0;if(ps)ps->Release();ps=0;if(psQuant)psQuant->Release();psQuant=0;if(declaration)declaration->Release();declaration=0;
    scene.batches.clear();scene.textures.clear();textureHashes.clear();textureWidths.clear();textureHeights.clear();captionScene.batches.clear();captionScene.textures.clear();fighterScene.batches.clear();fighterScene.textures.clear();fighterArchive.clear();fighterMotion.clear();fighterAnimated=false;fighterTracks=fighterUpdates=0;ready=reported=false;
}
static unsigned int pixelHash(const Melee360SceneTexture& t){if(t.contentHash)return t.contentHash;unsigned int h=2166136261u;for(unsigned int i=0;i<t.pixels.size();++i){h^=t.pixels[i];h*=16777619u;}return h;}
static void appendScene(Melee360Scene& dst,const Melee360Scene& src){dst.skipped+=src.skipped;int offset=(int)dst.textures.size();dst.textures.insert(dst.textures.end(),src.textures.begin(),src.textures.end());for(unsigned int i=0;i<src.batches.size();++i){Melee360SceneBatch b=src.batches[i];if(b.texture>=0)b.texture+=offset;dst.batches.push_back(b);}}
static bool syncAnimation(IDirect3DDevice9* device,Melee360Scene& next){
    for(unsigned int i=0;i<next.textures.size();++i){Melee360SceneTexture& t=next.textures[i];unsigned int hash=pixelHash(t);
        if(i>=textures.size()){IDirect3DTexture9* texture=0;if(!upload(device,t.width,t.height,&t.pixels[0],&texture))return false;textures.push_back(texture);textureHashes.push_back(hash);textureWidths.push_back(t.width);textureHeights.push_back(t.height);}
        else if(textureWidths[i]!=t.width||textureHeights[i]!=t.height){IDirect3DTexture9* texture=0;if(!upload(device,t.width,t.height,&t.pixels[0],&texture))return false;textures[i]->Release();textures[i]=texture;textureHashes[i]=hash;textureWidths[i]=t.width;textureHeights[i]=t.height;}
        else if(textureHashes[i]!=hash){D3DLOCKED_RECT lock;if(FAILED(textures[i]->LockRect(0,&lock,0,0)))return false;for(unsigned int y=0;y<t.height;++y)memcpy((char*)lock.pBits+y*lock.Pitch,&t.pixels[y*t.width],t.width*4);if(FAILED(textures[i]->UnlockRect(0)))return false;textureHashes[i]=hash;}
    }scene.batches.swap(next.batches);scene.skipped=next.skipped;scene.unsupportedEvents=next.unsupportedEvents;return true;
}
static bool updateAnimation(IDirect3DDevice9* device){
    if(isMenu&&currentPage<0)return true;DWORD now=GetTickCount();if(lastAnimation&&now-lastAnimation<(currentPage==1002?33u:16u))return true;
    Melee360Scene next;unsigned int tracks=0;float frame=(now-animationStart)*.06f,hover=(now-hoverStart)*.06f;bool ok;
    if(isMenu&&currentPage==1002){next=trophyBase;float cs=cosf(trophyAngle),sn=sinf(trophyAngle);bool collection=currentSelection>=10;float scale=collection?.40f:.65f;for(unsigned int b=0;b<next.batches.size();++b)for(unsigned int v=0;v<next.batches[b].vertices.size();++v){Melee360SceneVertex& o=next.batches[b].vertices[v];float x=o.clip[0],z=o.clip[2];o.clip[0]=(x*cs+z*sn)*scale+(collection?(next.batches[b].joint?-.45f:.45f):-.40f);o.clip[1]=o.clip[1]*scale-.05f;o.clip[2]=.5f+(z*cs-x*sn)*.1f;}ok=true;}
    else if(isMenu&&currentPage==1001)ok=Melee360LoadBattlefield(&stageArchive[0],(unsigned int)stageArchive.size(),frame,currentSelection,next,&tracks);
    else if(isMenu&&currentPage==1000){Melee360CSSState cursor;Melee360CSSGetState(&cursor);ok=Melee360LoadCharacterSelect(&cssArchive[0],(unsigned int)cssArchive.size(),cursor.confirmed?cursor.selected:cursor.hover,next,frame,true,&cursor);if(ok&&cssModelDiagnostic&&(cursor.confirmed||cursor.hover>=0)){
            DWORD tick=GetTickCount();
            if(fighterAnimated&&tick-lastFighter>=50){DWORD poseStarted=GetTickCount();Melee360Scene posed;unsigned int count=0;
                if(!Melee360LoadAnimatedFighterPreview(&fighterArchive[0],(unsigned int)fighterArchive.size(),&fighterMotion[0],(unsigned int)fighterMotion.size(),(tick-fighterStart)*.06f,posed,&count)){Melee360Log("CSS fighter animation FAILED\n");return false;}
                for(unsigned int b=0;b<posed.batches.size();++b)for(unsigned int v=0;v<posed.batches[b].vertices.size();++v){Melee360SceneVertex& o=posed.batches[b].vertices[v];o.clip[0]=o.clip[0]*.22f-.70f;o.clip[1]=o.clip[1]*.36f-.48f;}
                fighterScene=posed;fighterTracks=count;lastFighter=tick;++fighterUpdates;fighterBuildMs+=GetTickCount()-poseStarted;
                if(fighterUpdates==20){char msg[180];sprintf_s(msg,sizeof(msg),"CSS fighter: 20 animated updates; original FObj_tracks=%u skipped_meshes=%u build_avg_ms=%.2f\n",count,posed.skipped,fighterBuildMs/fighterUpdates);Melee360Log(msg);}
            }
            appendScene(next,fighterScene);
        }}
    else if(isMenu&&currentPage==1005)ok=Melee360LoadOptions(&menuArchive[0],(unsigned int)menuArchive.size(),optionsPage,optionsSelection,optionsOutput,optionsMusic,optionsRumble,optionsConnected,frame,next,&tracks);
    else if(isMenu&&currentPage==1004)ok=Melee360LoadSoundTest(&menuArchive[0],(unsigned int)menuArchive.size(),frame,soundPlaying,next,&tracks);
    else if(isMenu&&currentPage==1003){ok=Melee360LoadStageSelect(&mapArchive[0],(unsigned int)mapArchive.size(),60,mapCursorX,mapCursorY,mapHover,next);}
    else if(isMenu){ok=Melee360LoadOriginalMenu(&menuArchive[0],(unsigned int)menuArchive.size(),currentPage,currentSelection,frame,next,&tracks,true,hover,currentBackward);if(ok)appendScene(next,captionScene);}
    else ok=Melee360LoadAnimatedTitle(&titleArchive[0],(unsigned int)titleArchive.size(),frame,next,&tracks);
    if(!ok){Melee360Log("Animation: sampling FAILED\n");return false;}if(!syncAnimation(device,next))return false;
    lastAnimation=now;animationBuildMs+=GetTickCount()-now;++animationSamples;
    if(animationSamples==120){char info[256];sprintf_s(info,sizeof(info),"Animation: %s 120 updates; frame=%.1f FObj_tracks=%u build_upload_avg_ms=%.2f; persistent GPU resources\n",currentPage==1001&&isMenu?"Battlefield":isMenu?"menu":"title",frame,tracks,animationBuildMs/animationSamples);Melee360Log(info);
        if(currentPage==1001&&isMenu){sprintf_s(info,sizeof(info),"Battlefield: variant=%d 120 animation updates; skipped_meshes=%u unsupported_event_callbacks=%u\n",currentSelection,scene.skipped,scene.unsupportedEvents);Melee360Log(info);}}
    return true;
}
static bool uploadScene(IDirect3DDevice9* device){
    D3DVERTEXELEMENT9 elements[]={{0,0,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_POSITION,0},
        {0,16,D3DDECLTYPE_FLOAT2,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_TEXCOORD,0},
        {0,24,D3DDECLTYPE_FLOAT4,D3DDECLMETHOD_DEFAULT,D3DDECLUSAGE_COLOR,0},D3DDECL_END()};
    bool ok=SUCCEEDED(device->CreateVertexShader((DWORD*)Melee360SceneVS,&vs))&&SUCCEEDED(device->CreatePixelShader((DWORD*)Melee360ScenePS,&ps))&&SUCCEEDED(device->CreatePixelShader((DWORD*)Melee360SceneQuantizedPS,&psQuant))&&SUCCEEDED(device->CreateVertexDeclaration(elements,&declaration));
    unsigned int pixel=0xFFFFFFFF;if(ok)ok=upload(device,1,1,&pixel,&white);
    for(unsigned int i=0;ok&&i<scene.textures.size();++i){Melee360SceneTexture& t=scene.textures[i];IDirect3DTexture9* texture=0;ok=upload(device,t.width,t.height,&t.pixels[0],&texture);textures.push_back(texture);}
    if(!ok){Melee360TitleClose();return false;}
    textureHashes.resize(textures.size());textureWidths.resize(textures.size());textureHeights.resize(textures.size());
    for(unsigned int i=0;i<scene.textures.size();++i){textureHashes[i]=pixelHash(scene.textures[i]);textureWidths[i]=scene.textures[i].width;textureHeights[i]=scene.textures[i].height;}
    scene.textures.clear();ready=true;
    return true;
}
static bool sceneInit(IDirect3DDevice9* device,bool menu,int page=-1,int selection=0) {
    widthScale=.75f;
    Melee360TitleClose();isMenu=menu;std::vector<unsigned char>& archive=menu?menuArchive:titleArchive;animationStart=hoverStart=GetTickCount();lastAnimation=0;animationSamples=0;animationBuildMs=0;
    bool ok=true;if(archive.empty()){
        HANDLE file=CreateFileA(menu?"game:\\data\\MnMaAll.usd":"game:\\data\\GmTtAll.usd",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
        if(file==INVALID_HANDLE_VALUE)return false;DWORD high=0,bytes=GetFileSize(file,&high),read=0;
        if(high||bytes<32||bytes>8*1024*1024){CloseHandle(file);return false;}archive.resize(bytes);
        ok=ReadFile(file,&archive[0],bytes,&read,0)&&read==bytes;CloseHandle(file);if(!ok)archive.clear();}
    unsigned int tracks=0;
    if(ok)ok=menu&&page>=0?Melee360LoadOriginalMenu(&archive[0],(unsigned int)archive.size(),page,selection,0,scene,&tracks,true,0):menu?Melee360LoadStaticScene(&archive[0],(unsigned int)archive.size(),"MenMainBack_Top_joint",scene):Melee360LoadAnimatedTitle(&archive[0],(unsigned int)archive.size(),0,scene,&tracks);
    if(ok&&menu&&page>=0){bool caption=readResource("game:\\data\\SdMenu.usd",menuSis)&&readResource("game:\\melee360-font.bin",menuFont)&&Melee360AppendOriginalMenuCaption(&archive[0],(unsigned int)archive.size(),&menuSis[0],(unsigned int)menuSis.size(),&menuFont[0],(unsigned int)menuFont.size(),page,selection,captionScene);
        if(caption)appendScene(scene,captionScene);
        Melee360Log(caption?"Original menu: original SIS caption/glyphs loaded\n":"Original menu: SIS caption unavailable\n");}
    if(!ok){Melee360TitleClose();return false;}
    if(!uploadScene(device))return false;
    currentPage=page;currentSelection=selection;
    if(menu&&page>=0){char info[192];sprintf_s(info,sizeof(info),"Original menu: page=%d selection=%d batches=%u textures=%u FObj_tracks=%u skipped=%u\n",page,selection,(unsigned int)scene.batches.size(),(unsigned int)textures.size(),tracks,scene.skipped);Melee360Log(info);}
    char message[128];sprintf_s(message,sizeof(message),"%s: animated original scene ready; batches=%u textures=%u skipped=%u\n",menu?"Menu background":"Title",(unsigned int)scene.batches.size(),(unsigned int)textures.size(),scene.skipped);Melee360Log(message);return true;
}
bool Melee360TitleInit(IDirect3DDevice9* device) {currentBackward=false;return sceneInit(device,false);}
void Melee360SceneSetWide(bool wide) {widthScale=wide?1.f:.75f;}
bool Melee360MenuBackgroundInit(IDirect3DDevice9* device) {currentBackward=false;return sceneInit(device,true,0,0);}
bool Melee360OriginalMenuPage(IDirect3DDevice9* device,int page,int selection,bool backwards){currentBackward=backwards;
    if(!Melee360OriginalMenuSupported(page))return false;
    if(ready&&isMenu&&currentPage==page){if(currentSelection!=selection){currentSelection=selection;hoverStart=GetTickCount();lastAnimation=0;captionScene.batches.clear();captionScene.textures.clear();
            if(!menuSis.empty()&&!menuFont.empty())Melee360AppendOriginalMenuCaption(&menuArchive[0],(unsigned int)menuArchive.size(),&menuSis[0],(unsigned int)menuSis.size(),&menuFont[0],(unsigned int)menuFont.size(),page,selection,captionScene);}return true;}return sceneInit(device,true,page,selection);
}
bool Melee360TitleDraw(IDirect3DDevice9* device) {
    if(!ready)return false;if(!updateAnimation(device))return false;
    device->Clear(0,0,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0,0,0),Melee360GXClearDepth(0xffffff),0);
    device->SetVertexDeclaration(declaration);device->SetVertexShader(vs);int compression=Melee360GXDepthCompression();device->SetPixelShader(compression>=0?psQuant:ps);
    if(compression>=0){float depth[4]={1,(float)compression,0,0},normalization[4]={1.f/16777215.f,0,0,0};device->SetPixelShaderConstantF(187,depth,1);device->SetPixelShaderConstantF(186,normalization,1);}
    const float viewport[4]={widthScale,0,0,0};device->SetVertexShaderConstantF(0,viewport,1);
    IDirect3DSurface9* target=0;D3DSURFACE_DESC desc;if(FAILED(device->GetRenderTarget(0,&target))||!target)return false;HRESULT description=target->GetDesc(&desc);target->Release();if(FAILED(description))return false;GXSetViewport(0,0,(float)desc.Width,(float)desc.Height,0,1);GXSetCullMode(GX_CULL_NONE);device->SetRenderState(D3DRS_ZENABLE,TRUE);
    GXSetZMode(1,GX_LEQUAL,1);GXSetColorUpdate(1);GXSetAlphaUpdate(1);
    GXSetBlendMode(GX_BM_BLEND,GX_BL_SRCALPHA,GX_BL_INVSRCALPHA,GX_LO_COPY);
    device->SetRenderState(D3DRS_ALPHATESTENABLE,TRUE);device->SetRenderState(D3DRS_ALPHAFUNC,D3DCMP_GREATER);device->SetRenderState(D3DRS_ALPHAREF,2);
    device->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);device->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
    device->SetSamplerState(0,D3DSAMP_ADDRESSU,D3DTADDRESS_CLAMP);device->SetSamplerState(0,D3DSAMP_ADDRESSV,D3DTADDRESS_CLAMP);
    for(unsigned int i=0;i<scene.batches.size();++i){Melee360SceneBatch& b=scene.batches[i];if(b.vertices.empty())continue;
        device->SetTexture(0,b.texture>=0?textures[b.texture]:white);
        device->SetSamplerState(0,D3DSAMP_ADDRESSU,b.wrapS==1?D3DTADDRESS_WRAP:b.wrapS==2?D3DTADDRESS_MIRROR:D3DTADDRESS_CLAMP);
        device->SetSamplerState(0,D3DSAMP_ADDRESSV,b.wrapT==1?D3DTADDRESS_WRAP:b.wrapT==2?D3DTADDRESS_MIRROR:D3DTADDRESS_CLAMP);
        GXSetZMode(1,(b.mode&(1u<<27))?GX_ALWAYS:GX_LEQUAL,(b.mode&(1u<<29))?0:1);
        if(FAILED(device->DrawPrimitiveUP(D3DPT_TRIANGLELIST,(unsigned int)b.vertices.size()/3,&b.vertices[0],sizeof(Melee360SceneVertex))))return false;
    }
    if(!reported){Melee360Log(isMenu?"Menu background: first original mesh draw submitted\n":"Title: first original mesh draw submitted (original FObj animation)\n");reported=true;}return true;
}

bool Melee360CharacterSelectPage(IDirect3DDevice9* device,int selected){
    if(selected<0||selected>=25)return false;
    if(ready&&isMenu&&currentPage==1000&&currentSelection==selected)return true;
    if(ready&&isMenu&&currentPage==1000&&!cssModelDiagnostic){
        // Keep shaders, GPU textures and decoded archive caches across hover changes.
        currentSelection=selected;lastAnimation=0;
        char msg[160];sprintf_s(msg,sizeof(msg),"Character select: slot=%d name=%s portrait=original2D; P1=HMN P2-P4=NA\n",selected,Melee360CharacterNames[selected]);Melee360Log(msg);
        return true;
    }
    bool sameCss=ready&&isMenu&&currentPage==1000;DWORD oldStart=animationStart;Melee360TitleClose();isMenu=true;animationStart=sameCss?oldStart:GetTickCount();hoverStart=GetTickCount();lastAnimation=0;animationSamples=0;animationBuildMs=0;std::vector<unsigned char>& css=cssArchive;std::vector<unsigned char> raw;
    Melee360CSSState cursor;Melee360CSSGetState(&cursor);
    if(!readResource("game:\\data\\MnSlChr.usd",css)||!Melee360LoadCharacterSelect(&css[0],(unsigned int)css.size(),cursor.confirmed?cursor.selected:cursor.hover,scene,0,false,&cursor))return false;
    // Explicit diagnostic opt-in; normal CSS uses the original 2D HUD portraits.
    cssModelDiagnostic=GetFileAttributes("game:\\debug-css-models.flag")!=(DWORD)-1;
    if(!cssModelDiagnostic){
        if(!uploadScene(device))return false;currentPage=1000;currentSelection=selected;widthScale=.75f;
        char msg[160];sprintf_s(msg,sizeof(msg),"Character select: slot=%d name=%s portrait=original2D; P1=HMN P2-P4=NA\n",selected,Melee360CharacterNames[selected]);Melee360Log(msg);return true;
    }
    char path[96];sprintf_s(path,sizeof(path),"game:\\data\\%s",Melee360CharacterFiles[selected]);Melee360Scene fighter;
    bool loaded=readResource(path,fighterArchive)&&Melee360LoadFighterPreview(&fighterArchive[0],(unsigned int)fighterArchive.size(),fighter);
    sprintf_s(path,sizeof(path),"game:\\data\\%.4sDViWaitAJ.dat",Melee360CharacterFiles[selected]);
    fighterAnimated=loaded&&readResource(path,fighterMotion)&&Melee360LoadAnimatedFighterPreview(&fighterArchive[0],(unsigned int)fighterArchive.size(),&fighterMotion[0],(unsigned int)fighterMotion.size(),0,fighter,&fighterTracks);
    if(loaded&&!fighterAnimated){Melee360Log("CSS fighter: original motion unavailable; bind pose fallback\n");loaded=Melee360LoadFighterPreview(&fighterArchive[0],(unsigned int)fighterArchive.size(),fighter);}
    fighterStart=lastFighter=GetTickCount();fighterUpdates=0;fighterBuildMs=0;
    unsigned int modelBatches=(unsigned int)fighter.batches.size(),modelSkipped=fighter.skipped;
    if(loaded){fighterScene=fighter;for(unsigned int i=0;i<fighterScene.batches.size();++i)for(unsigned int v=0;v<fighterScene.batches[i].vertices.size();++v){Melee360SceneVertex& o=fighterScene.batches[i].vertices[v];o.clip[0]=o.clip[0]*.22f-.70f;o.clip[1]=o.clip[1]*.36f-.48f;}int offset=(int)scene.textures.size();scene.textures.insert(scene.textures.end(),fighter.textures.begin(),fighter.textures.end());
        for(unsigned int i=0;i<fighter.batches.size();++i){Melee360SceneBatch b=fighter.batches[i];if(b.texture>=0)b.texture+=offset;
            for(unsigned int v=0;v<b.vertices.size();++v){Melee360SceneVertex& o=b.vertices[v];o.clip[0]=o.clip[0]*.22f-.70f;o.clip[1]=o.clip[1]*.36f-.48f;}
            scene.batches.push_back(b);}scene.skipped+=fighter.skipped;}
    if(!uploadScene(device))return false;currentPage=1000;currentSelection=selected;widthScale=.75f;
    char info[256];sprintf_s(info,sizeof(info),"Character select: slot=%d name=%s model=%s batches=%u skipped=%u; original CSS cursor; motion=%s FObj_tracks=%u\n",selected,Melee360CharacterNames[selected],loaded?"loaded":"unavailable",modelBatches,modelSkipped,fighterAnimated?"original DViWait":"bind pose fallback",fighterTracks);Melee360Log(info);
    return true;
}
bool Melee360BattlefieldPage(IDirect3DDevice9* device,int background){
    if(background<0||background>3)return false;if(ready&&isMenu&&currentPage==1001&&currentSelection==background)return true;
    Melee360TitleClose();isMenu=true;animationStart=hoverStart=GetTickCount();lastAnimation=animationSamples=0;animationBuildMs=0;
    unsigned int tracks=0,groups=0;if(!readResource("game:\\data\\GrNBa.dat",stageArchive)||!Melee360LoadBattlefield(&stageArchive[0],(unsigned int)stageArchive.size(),0,background,scene,&tracks,&groups))return false;
    unsigned int events=scene.unsupportedEvents;if(!uploadScene(device))return false;currentPage=1001;currentSelection=background;widthScale=.75f;
    char info[256];sprintf_s(info,sizeof(info),"Battlefield: variant=%d original stage ready; groups=%u tracks=%u batches=%u textures=%u skipped=%u unsupported_event_callbacks=%u; no gameplay\n",background,groups,tracks,(unsigned int)scene.batches.size(),(unsigned int)textures.size(),scene.skipped,events);Melee360Log(info);return true;
}
bool Melee360TrophyPage(IDirect3DDevice9* device,int selected,bool collection,float angle){
    int key=collection?10+selected:selected;trophyAngle=angle+3.14159265359f;
    if(ready&&isMenu&&currentPage==1002&&currentSelection==key)return true;
    Melee360TitleClose();isMenu=true;animationStart=hoverStart=GetTickCount();lastAnimation=animationSamples=0;animationBuildMs=0;
    const char* files[2]={"game:\\data\\TyDaisy.dat","game:\\data\\TyKusuda.dat"};const char* roots[2]={"ToyDaisyModel_TopN_joint","ToyKusudamaModel_TopN_joint"};trophyBase=Melee360Scene();
    for(int id=0;id<2;++id){if(!collection&&id!=selected)continue;if(collection&&id>selected)continue;Melee360Scene model;
        if(!readResource(files[id],trophyArchives[id])||!Melee360LoadTrophyModel(&trophyArchives[id][0],(unsigned int)trophyArchives[id].size(),roots[id],model))return false;
        Melee360Scene stand;if(!readResource("game:\\data\\TyStand.dat",trophyStandArchive)||!Melee360LoadTrophyModel(&trophyStandArchive[0],(unsigned int)trophyStandArchive.size(),"ToyStandModel_TopN_joint",stand))return false;
        for(unsigned int b=0;b<stand.batches.size();++b)for(unsigned int v=0;v<stand.batches[b].vertices.size();++v){Melee360SceneVertex& o=stand.batches[b].vertices[v];o.clip[0]*=.7f;o.clip[1]=o.clip[1]*.25f-1.05f;o.clip[2]*=.7f;}appendScene(model,stand);
        for(unsigned int b=0;b<model.batches.size();++b)model.batches[b].joint=id;appendScene(trophyBase,model);}
    scene=trophyBase;if(!uploadScene(device))return false;trophyBase.textures.clear();currentPage=1002;currentSelection=key;widthScale=.75f;
    Melee360Log(collection?"Trophies: collection original models loaded\n":"Trophies: gallery original model loaded\n");if(!collection)Melee360Log(selected?"Trophies: gallery selected Party Ball\n":"Trophies: gallery selected Daisy\n");return true;
}

bool Melee360StageSelectPage(IDirect3DDevice9* device,float x,float y,int hover){mapCursorX=x;mapCursorY=y;mapHover=hover;if(ready&&isMenu&&currentPage==1003)return true;Melee360TitleClose();isMenu=true;animationStart=hoverStart=GetTickCount();lastAnimation=animationSamples=0;animationBuildMs=0;if(!readResource("game:\\data\\MnSlMap.usd",mapArchive)||!Melee360LoadStageSelect(&mapArchive[0],(unsigned int)mapArchive.size(),60,x,y,hover,scene)||!uploadScene(device))return false;currentPage=1003;currentSelection=0;widthScale=.75f;Melee360Log("Stage select: original MnSlMap models/camera/frames loaded; only Battlefield enabled\n");return true;}

bool Melee360SoundTestPage(IDirect3DDevice9* device,bool playing){soundPlaying=playing;if(ready&&isMenu&&currentPage==1004)return true;Melee360TitleClose();isMenu=true;animationStart=hoverStart=GetTickCount();lastAnimation=animationSamples=0;animationBuildMs=0;unsigned int tracks=0;
    if(!readResource("game:\\data\\MnMaAll.usd",menuArchive)||!Melee360LoadSoundTest(&menuArchive[0],(unsigned int)menuArchive.size(),0,playing,scene,&tracks)||!uploadScene(device))return false;
    currentPage=1004;currentSelection=0;widthScale=.75f;char report[160];sprintf_s(report,sizeof(report),"Sound test: original MenMainConTs scene loaded; batches=%u textures=%u skipped=%u\n",(unsigned int)scene.batches.size(),(unsigned int)textures.size(),scene.skipped);Melee360Log(report);return true;
}

bool Melee360OptionsPage(IDirect3DDevice9* device,int page,int selection,int output,int music,unsigned int rumble,unsigned int connected){bool same=optionsPage==page;optionsPage=page;optionsSelection=selection;optionsOutput=output;optionsMusic=music;optionsRumble=rumble;optionsConnected=connected;if(ready&&isMenu&&currentPage==1005&&same)return true;
    Melee360TitleClose();isMenu=true;animationStart=hoverStart=GetTickCount();lastAnimation=animationSamples=0;animationBuildMs=0;unsigned int tracks=0;
    if(!readResource("game:\\data\\MnMaAll.usd",menuArchive)||!Melee360LoadOptions(&menuArchive[0],(unsigned int)menuArchive.size(),page,selection,output,music,rumble,connected,0,scene,&tracks)||!uploadScene(device))return false;
    currentPage=1005;currentSelection=0;widthScale=.75f;char report[180];sprintf_s(report,sizeof(report),"Options: original page=%d loaded; batches=%u textures=%u tracks=%u skipped=%u\n",page,(unsigned int)scene.batches.size(),(unsigned int)textures.size(),tracks,scene.skipped);Melee360Log(report);return true;
}
