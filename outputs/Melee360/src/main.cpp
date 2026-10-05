extern "C" int Melee360AXContinuousProbe(void);extern "C" int Melee360AXDepopProbe(void);extern "C" int Melee360AXMixerProbe(void);extern "C" int Melee360AXUpdateProbe(void);
extern "C" int Melee360AXPCMOutputProbe(void);
extern "C" int Melee360ResetCallbacksProbe(void);
extern "C" int Melee360NativeThreadsProbe(void);
extern "C" int Melee360AIDMAProbe(void);
extern "C" int Melee360ResetReasonProbe(void);
extern "C" int Melee360THPPixelProbe(void);
extern "C" int Melee360GXTexgenProbe(void);
extern "C" int Melee360MCCProbe(void);
extern "C" int Melee360GXLightingProbe(void);
#include "audio_effects.h"
#include <xtl.h>
#include "platform_log.h"
#include "asset_archive.h"
#include "intro_stream.h"
#include "intro_video.h"
#include "title_scene.h"
#include "menu_ui.h"
#include "original_character_select.h"
bool Melee360MenuSchedulerInit();
bool Melee360MenuScheduledFrame(bool,unsigned int,unsigned int);
void Melee360MenuSchedulerClose();
#ifdef MELEE360_DECOMP
bool Melee360RendererProbe();
void Melee360FpsDetail(const char*);bool Melee360FpsInit(IDirect3DDevice9*);bool Melee360FpsDraw(IDirect3DDevice9*);void Melee360FpsPresented();void Melee360FpsClose();
extern "C" {
void Melee360GXProfileEnable(int);void Melee360GXProfileFrame(LONGLONG,LONGLONG,LONGLONG);
int Melee360HsdProbe(void);
int Melee360HsdMainHeapBoot(void);int Melee360OriginalHeapBoot(void);int Melee360OriginalArchiveBoot(void);int Melee360OriginalRuntimeBoot(void);int Melee360OriginalMatchFrame(void);int Melee360OriginalMatchRender(void);int Melee360GXCaptureMatch(unsigned);int Melee360MatchSurfaceInit(void);int Melee360MatchSurfaceBegin(void);int Melee360MatchSurfacePresent(void);int Melee360HsdRenderConfigure(unsigned,unsigned);const char* Melee360OriginalMatchStatus(void);
int Melee360AXFXProbe(void);
int Melee360ReverbStdProbe(void);
int Melee360ReverbHiProbe(void);
int Melee360ChorusProbe(void);
int Melee360FIOProbe(void);
int Melee360MemorySizeProbe(void);
int Melee360VideoSettingsProbe(void);
int Melee360HsdArenaOwnershipProbe(void);
int Melee360ObjDumpProbe(void);
int Melee360ObjLifecycleProbe(void);
int Melee360TrainingProbe(void);
int Melee360OriginalLogicProbe(void);
int Melee360NativeLogicProbe(void);
int Melee360FightSetupProbe(void);
int Melee360RuntimeAssetsProbe(void);
int Melee360CacheProbe(void);
int Melee360HsdHeapProbe(void);
const char* Melee360RuntimeAssetsStatus(void);
int Melee360GameRulesProbe(void);
int Melee360GObjProbe(void);
int Melee360MathProbe(void);
int Melee360GXCpuProbe(void);
int Melee360AXControlProbe(void);
int Melee360THPHeaderProbe(void);
int Melee360AIStreamVolumeProbe(void);
int Melee360DVDProbe(void);
int Melee360CalendarProbe(void);
int Melee360ReportProbe(void);
void Melee360DVDPump(void);
void Melee360AlarmPump(void);
void Melee360CardPump(void);
void Melee360ARAMPump(void);
int Melee360PlatformServicesProbe(void);
int Melee360ArenaProbe(void);
int Melee360VIProbe(void);
void Melee360VIBeginFrame(void);
void Melee360VIEndFrame(int);
int Melee360AudioInit(void);
void Melee360AudioPump(int menuActive);
void Melee360AudioClose(void);
void Melee360GXBindDevice(IDirect3DDevice9*);
int Melee360GXStateProbe(void);
int Melee360GXPixelFormatProbe(void);
int Melee360HsdRenderBoot(void);
void Melee360HsdStartScreen(void);
int Melee360GXTextureCopyProbe(void);int Melee360GXFogProbe(void);int Melee360GXRasterProbe(void);int Melee360GXZ16Probe(void);void Melee360XfbBeginRender(void);
int Melee360XfbInit(IDirect3DDevice9*);int Melee360XfbPresent(void);void Melee360XfbClose(void);
void Melee360GXPump(void);
int Melee360GXDirectBind(IDirect3DDevice9*);
int Melee360GXDirectProbe(void);
int Melee360GXTextureBindingProbe(void);
int Melee360GXTextureExpansionProbe(void);
int Melee360GXTevProbe(void);
extern "C" int Melee360GXAlphaProbe(void);
int Melee360TimeProbe(void);
void Melee360PadInit(void);
int Melee360PadAbi(void);
int Melee360PadSamplingProbe(void);
unsigned int Melee360PadFrame(void);
void Melee360PadStop(void);
}
#endif

static bool diagnosticFlag(const char* path) {
    HANDLE file=CreateFileA(path,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if(file==INVALID_HANDLE_VALUE)return false;CloseHandle(file);return true;
}
VOID __cdecl main()
{
    Melee360Log("Melee360: CRT entry reached\n");
    Melee360Log("Melee360 build: original-fighter-assets-1\n");
    bool probeOk = true;
    int assetState = -1;

    IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);
    if (!d3d) { Melee360Log("Direct3DCreate9 failed\n"); return; }
    D3DPRESENT_PARAMETERS pp;
    ZeroMemory(&pp, sizeof(pp));
    pp.BackBufferWidth = 1280;
    pp.BackBufferHeight = 720;
    pp.BackBufferFormat = (D3DFORMAT)MAKESRGBFMT(D3DFMT_A8R8G8B8);
    pp.FrontBufferFormat = (D3DFORMAT)MAKESRGBFMT(D3DFMT_LE_X8R8G8B8);
    pp.BackBufferCount = 1;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
    pp.EnableAutoDepthStencil = TRUE;
    pp.AutoDepthStencilFormat = D3DFMT_D24S8;
    IDirect3DDevice9* device = NULL;
    HRESULT hr = d3d->CreateDevice(0, D3DDEVTYPE_HAL, NULL,
        D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &device);
    if (FAILED(hr)) { Melee360Log("CreateDevice failed\n"); d3d->Release(); return; }
    // Present before tests and file I/O so hardware startup is independently visible.
    HRESULT firstClear = device->Clear(0, NULL, D3DCLEAR_TARGET,
        D3DCOLOR_XRGB(10, 24, 48), 1.0f, 0);
    D3DRECT bootMarker = {40, 40, 280, 64};
    if (SUCCEEDED(firstClear)) firstClear = device->Clear(1, &bootMarker,
        D3DCLEAR_TARGET, D3DCOLOR_XRGB(220, 160, 20), 1.0f, 0);
    HRESULT firstPresent = FAILED(firstClear) ? firstClear :
        device->Present(NULL, NULL, NULL, NULL);
    if (FAILED(firstPresent)) {
        Melee360Log("Melee360: first diagnostic frame FAILED\n");
        device->Release();
        d3d->Release();
        return;
    }
    Melee360Log("Melee360: first diagnostic frame presented\n");
#ifdef MELEE360_DECOMP
    Melee360GXBindDevice(device);
    if(!Melee360HsdMainHeapBoot()){Melee360Log("HSD main heap boot FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("HSD main heap: original reset, native ownership, allocation and live-reset protection passed\n");
    if(!Melee360OriginalHeapBoot()){Melee360Log("Original heap bootstrap FAILED\n");device->Release();d3d->Release();return;}
    if(!Melee360OriginalArchiveBoot()){Melee360Log("Original archive bootstrap FAILED\n");device->Release();d3d->Release();return;}
    if(!Melee360HsdRenderBoot()){Melee360Log("HSD render boot FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("HSD render: original pass lifecycle, native progressive dimensions, RGB/Z24 and full coverage passed\n");
    if(diagnosticFlag("game:\\original-match.flag")){
        if(!Melee360GXDirectBind(device)||!Melee360MatchSurfaceInit()||!Melee360HsdRenderConfigure(640,480)||!Melee360OriginalRuntimeBoot()||!Melee360FpsInit(device)){Melee360Log("Original match initialization FAILED\n");return;}
        const bool profile=diagnosticFlag("game:\\gx-profile.flag");Melee360GXProfileEnable(profile?1:0);
        unsigned rendered=0;const bool capture=diagnosticFlag("game:\\original-render-capture.flag");
        for(;;){
            LARGE_INTEGER p0,p1,p2,p3;if(profile)QueryPerformanceCounter(&p0);
            if(!Melee360OriginalMatchFrame()){Melee360Log("Original match simulation FAILED\n");break;}
            if(profile)QueryPerformanceCounter(&p1);
            Melee360FpsDetail(Melee360OriginalMatchStatus());
            if(!Melee360MatchSurfaceBegin()||!Melee360OriginalMatchRender()||(capture&&(rendered==0||rendered==59||rendered==299||rendered==599)&&!Melee360GXCaptureMatch(rendered+1))){Melee360Log("Original match presentation FAILED\n");break;}
            if(profile)QueryPerformanceCounter(&p2);
            if(!Melee360MatchSurfacePresent()||!Melee360FpsDraw(device)||FAILED(device->Present(0,0,0,0))){Melee360Log("Original match presentation FAILED\n");break;}
            if(profile){QueryPerformanceCounter(&p3);Melee360GXProfileFrame(p1.QuadPart-p0.QuadPart,p2.QuadPart-p1.QuadPart,p3.QuadPart-p2.QuadPart);}
            ++rendered;if(profile&&rendered==180)Melee360Log("GX profile: 180 frames presented\n");Melee360FpsPresented();if(rendered==900)Melee360Log("Original match render: 900 frames presented\n");
        }
        Melee360FpsClose();return;
    }
    if(diagnosticFlag("game:\\fighter-bootstrap.flag")){if(!Melee360OriginalRuntimeBoot())Melee360Log("Original Fighter bootstrap FAILED\n");return;}
    if(!Melee360VIProbe()){Melee360Log("VI callback dispatch FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("VI presentation callbacks/order/count probe passed\n");
    if(!Melee360ArenaProbe()){Melee360Log("OS arena probe FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("OS arena: aligned dual-ended allocations and bounds probe passed\n");
    if(!Melee360FIOProbe()||!Melee360MemorySizeProbe()){Melee360Log("FIO / OS memory queries FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("FIO / OS memory: native file export, exclusive creation, read-only protection, stale handles and arena capacity probes passed\n");
    if(!Melee360VideoSettingsProbe()){Melee360Log("Video settings FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("Video settings: native format/progressive queries, persistent preference and original bit masking passed\n");
    if(!Melee360GXPixelFormatProbe()){Melee360Log("GX pixel format FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("GX pixel format: RGB8/Z24 native targets, depth-only mask and alpha exclusion passed\n");
    const bool gxStateOk=Melee360GXStateProbe()!=0;
    Melee360Log(gxStateOk?"GX Xbox: native blend/depth/color/scissor and GPU fence probes passed\n":"GX Xbox state probes FAILED\n");
    if(!gxStateOk){device->Release();d3d->Release();return;}
    if(!Melee360GXDirectBind(device)){Melee360Log("GX direct resource initialization FAILED\n");device->Release();d3d->Release();return;}
    if(!Melee360GXDirectProbe()||(diagnosticFlag("game:\\verification.flag")&&!Melee360GXAlphaProbe())){Melee360Log("GX direct primitive completion FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("GX direct: matrix-transformed colored triangle submitted to Xbox GPU\n");
    if(diagnosticFlag("game:\\verification.flag")){
        if(!Melee360GXTextureBindingProbe()){Melee360Log("GX texture binding FAILED\n");device->Release();d3d->Release();return;}
        if(!Melee360GXTextureExpansionProbe()){Melee360Log("GX texture expansion FAILED\n");device->Release();d3d->Release();return;}
        Melee360Log("GX texture expansion: 45 GPU probes, 8 units, CI palettes, mip levels, TLUT reload and texture invalidation passed\n");

        if(!Melee360GXTevProbe()){Melee360Log("TEV validation FAILED\n");device->Release();d3d->Release();return;}
        Melee360Log("GX TEV: direct, indirect, vertex routing, original helpers, LOD and Z texture GPU validation passed\n");
        Melee360Log("GX texture binding: original descriptors, Xenon pointers, tiled RGBA8 and 6 GPU alpha/wrap probes passed\n");
    }
    if(!Melee360HsdHeapProbe()){Melee360Log("HSD heap transition FAILED\n");device->Release();d3d->Release();return;}
    if(!Melee360HsdArenaOwnershipProbe()){Melee360Log("HSD arena ownership FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("HSD arena ownership: primary bounds, per-heap live counts and reclaim eligibility passed\n");
    Melee360Log("HSD heap: owner-aware free, live data preservation and current heap transition passed\n");
    probeOk = Melee360HsdProbe() != 0;
    Melee360Log(probeOk ? "HSD memory/allocator/list/random/ID/class probes passed\n" : "HSD probes FAILED\n");
    if(!Melee360AXFXProbe()){Melee360Log("Original AXFX delay FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("Original AXFX delay: impulse/feedback/wrap/ownership/failure probes passed\n");
    if(!Melee360ChorusProbe()){Melee360Log("AXFX chorus FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("AXFX chorus: impulse, ring wrap, fractional modulation and allocation ownership probes passed\n");
    if(!Melee360ReverbHiProbe()){Melee360Log("AXFX high reverb FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("AXFX high reverb: impulse, channels, predelay, crosstalk and allocation ownership probes passed\n");
    if(!Melee360ReverbStdProbe()){Melee360Log("AXFX standard reverb FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("AXFX standard reverb: impulse, independent channels, predelay wrap, ownership and allocation-failure probes passed\n");
    if(!Melee360TrainingProbe()){Melee360Log("Training rules probe FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("Training: original defaults/human/CPU/training rules probe passed\n");
    if(!Melee360CacheProbe()){Melee360Log("Xenon cache probe FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("Xenon cache: native store/flush/invalidate byte preservation probe passed\n");
    const bool runtimeAssetsOk=Melee360RuntimeAssetsProbe()!=0;
    Melee360Log(Melee360RuntimeAssetsStatus());
    if(!runtimeAssetsOk){device->Release();d3d->Release();return;}
    if(!Melee360OriginalLogicProbe()){Melee360Log("Original standalone logic probe FAILED\n");device->Release();d3d->Release();return;}
    if(!Melee360NativeLogicProbe()){Melee360Log("Native Mario/Link logic probe FAILED\n");device->Release();d3d->Release();return;}
    if(!Melee360FightSetupProbe()){Melee360Log("Mario/Link setup probe FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("Original logic subset: directed intersections, Mario/Link native gravity and Battlefield point sweeps passed; no Fighter created\n");
    Melee360Log("Fight setup: Mario human P1, Link CPU level 9 P2, Battlefield, 3 stocks prepared; match runtime NOT started\n");
    const bool gameRulesOk = Melee360GameRulesProbe() != 0;
    Melee360Log(gameRulesOk ? "Game rules layout/bitfield ABI passed\n" : "Game rules layout/bitfield ABI FAILED\n");
    probeOk = probeOk && gameRulesOk;
    const bool schedulerOk=Melee360GObjProbe()!=0&&Melee360MenuSchedulerInit();
    Melee360Log(schedulerOk?"Original GObj scheduler priority/pause/self-delete probes passed\n":"Original GObj scheduler FAILED\n");
    if(!Melee360ObjLifecycleProbe()){Melee360Log("HSD pool lifecycle FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("HSD pool lifecycle: original free/forget retains backing memory; isolated cleanup and registry restoration passed\n");
    if(!Melee360ObjDumpProbe()){Melee360Log("HSD object pool statistics FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("HSD object pool statistics: live registry report and allocation preservation passed\n");
    if(!schedulerOk){device->Release();d3d->Release();return;}
    const bool mathOk=Melee360MathProbe()!=0&&Melee360TimeProbe()!=0;
    Melee360Log(mathOk?"Original portable matrix/vector and Xbox tick clock probes passed\n":"Portable math/clock FAILED\n");
    if(!mathOk){Melee360MenuSchedulerClose();device->Release();d3d->Release();return;}
    const bool gxCpuOk=Melee360GXCpuProbe()!=0;
    Melee360Log(gxCpuOk?"Original GX CPU: light attenuation/color and texture tile/mipmap probes passed\n":"Original GX CPU FAILED\n");
    if(!gxCpuOk){Melee360MenuSchedulerClose();device->Release();d3d->Release();return;}
    const bool reportOk=Melee360ReportProbe()!=0;
    Melee360Log(reportOk?"HSD report callback: text/length/reentrancy/reset probes passed\n":"HSD report callback FAILED\n");
    if(!reportOk){Melee360MenuSchedulerClose();device->Release();d3d->Release();return;}
    const bool calendarOk=Melee360CalendarProbe()!=0;
    Melee360Log(calendarOk?"Original calendar: epoch/leap/negative/subsecond probes passed\n":"Original calendar FAILED\n");
    if(!calendarOk){Melee360MenuSchedulerClose();device->Release();d3d->Release();return;}
    const bool dvdOk=Melee360DVDProbe()!=0;
    Melee360Log(dvdOk?"DVD filesystem: original FST/ID and deferred Mario read probes passed\n":"DVD filesystem FAILED\n");
    if(!dvdOk){Melee360MenuSchedulerClose();device->Release();d3d->Release();return;}
    const int servicesResult=Melee360PlatformServicesProbe();
    const bool servicesOk=servicesResult!=0;
    if(servicesResult==2)Melee360Log("CARD: game directory is read-only; persistence probe skipped, boot continues\n");
    Melee360Log(servicesResult==2?"OS alarms/ARAM probes passed; CARD persistence unavailable\n":servicesOk?"OS alarms/CARD/ARAM: deferred callbacks and persisted byte-exact save probes passed\n":"OS/CARD/ARAM services FAILED\n");
    if(!servicesOk){Melee360MenuSchedulerClose();device->Release();d3d->Release();return;}
    if(!Melee360EffectsBridgeProbe()){Melee360Log("Audio effects bridge FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("Audio effects bridge: identical PCM across HPS partitions, partial final block and exact frame count passed\n");
    if(diagnosticFlag("game:\\mcc-host.cfg")&&diagnosticFlag("game:\\verification.flag")){if(!Melee360MCCProbe()){Melee360Log("MCC native transport FAILED\n");return;}Melee360Log("MCC original: host handshake, channel allocation, sync/deferred transfers, notifications and errors passed\n");}
    const bool audioOk=Melee360AudioInit()!=0;
    Melee360Log(audioOk?"Audio: XAudio2 engine/master voice initialized\n":"Audio: XAudio2 initialization unavailable\n");
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360ResetCallbacksProbe()){Melee360Log("OS reset callbacks FAILED\n");return;}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360NativeThreadsProbe()){Melee360Log("OS native threads FAILED\n");return;}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360AIDMAProbe()){Melee360Log("AI DMA validation FAILED\n");return;}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360AXPCMOutputProbe()){Melee360Log("AX PCM consumer FAILED\n");return;}
    if(diagnosticFlag("game:\\verification.flag")){int ax=Melee360AXControlProbe();char axMessage[192];sprintf_s(axMessage,sizeof(axMessage),"AX original CPU control: result=%d (voices, priority stealing, parameters, auxiliary rings)\n",ax);Melee360Log(axMessage);if(ax!=1){Melee360Log("AX CPU control FAILED\n");device->Release();d3d->Release();return;}}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360AXDepopProbe()){Melee360Log("AX depop FAILED\n");return;}if(diagnosticFlag("game:\\verification.flag")&&!Melee360AXMixerProbe()){Melee360Log("AX mixer FAILED\n");return;}if(diagnosticFlag("game:\\verification.flag")&&!Melee360AXUpdateProbe()){Melee360Log("AX updates FAILED\n");return;}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360AXContinuousProbe()){Melee360Log("AX continuous FAILED\n");return;}
    if(diagnosticFlag("game:\\verification.flag")){int thp=Melee360THPHeaderProbe();char msg[128];sprintf_s(msg,sizeof(msg),"THP original headers: result=%d (real frame, work size, Huffman/quantization tables and errors)\n",thp);Melee360Log(msg);if(thp!=1){Melee360Log("THP headers FAILED\n");device->Release();d3d->Release();return;}}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360ResetReasonProbe()){Melee360Log("OS launch reset reason FAILED\n");return;}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360THPPixelProbe()){Melee360Log("THP pixel validation FAILED\n");return;}
    if(diagnosticFlag("game:\\verification.flag")){if(!Melee360AIStreamVolumeProbe()){Melee360Log("AI stream gain FAILED\n");device->Release();d3d->Release();return;}Melee360Log("AI stream gains: 4 boundary pairs, getters and actual XAudio2 output matrix readback passed\n");}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360GXZ16Probe()){Melee360Log("GX Z16 FAILED\n");device->Release();d3d->Release();return;}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360GXRasterProbe()){Melee360Log("GX raster validation FAILED\n");device->Release();d3d->Release();return;}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360GXFogProbe()){Melee360Log("GX fog validation FAILED\n");device->Release();d3d->Release();return;}
    const bool cssOk=Melee360CSSProbe()!=0;
    Melee360Log(cssOk?"Original CSS core: 25 icon/CKind commits and cursor/token probes passed\n":"Original CSS core FAILED\n");
    if(!cssOk){Melee360MenuSchedulerClose();device->Release();d3d->Release();return;}
    if (probeOk) assetState = Melee360LoadMario();
    Melee360RendererProbe();
    Melee360PadInit();
    Melee360Log(Melee360PadAbi() ? "HSD rumble bitfield ABI passed\n" : "HSD rumble bitfield ABI FAILED\n");
    if(!Melee360PadSamplingProbe()||!Melee360MenuSoundModeProbe()){Melee360Log("PAD sampling / OS sound settings FAILED\n");device->Release();d3d->Release();return;}
    Melee360Log("PAD sampling / OS sound settings: cached cadence, input conversion, Mono/Stereo and invalid-value preservation passed\n");
    if (Melee360PrepareIntro() == 1 && (Melee360AudioPump(3), !Melee360IntroVideoInit(device)))
        Melee360Log("Intro: video initialization FAILED\n");
#endif
    Melee360Log("Melee360: present loop started; BACK exits\n");
#ifdef MELEE360_DECOMP
    if(!Melee360FpsInit(device)){Melee360Log("FPS overlay initialization FAILED\n");device->Release();d3d->Release();return;}
#endif
    #ifdef MELEE360_DECOMP
    if(!Melee360XfbInit(device)){Melee360Log("VI/XFB init FAILED\n");device->Release();d3d->Release();return;}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360GXTexgenProbe()){Melee360Log("GX texgen validation FAILED\n");return;}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360GXLightingProbe()){Melee360Log("GX lighting FAILED\n");return;}
    if(diagnosticFlag("game:\\verification.flag")&&!Melee360GXTextureCopyProbe()){Melee360Log("GX texture copy validation FAILED\n");device->Release();d3d->Release();return;}
    #endif
    DWORD frame = 0;
    bool titleActive = false, titleAttempted = false;
    bool forceTitle = diagnosticFlag("game:\\title-preview.flag");
    bool automatedTest = diagnosticFlag("game:\\verification.flag");
    bool forceMenu = diagnosticFlag("game:\\menu-preview.flag");
    bool menuTest=automatedTest&&forceMenu;
    bool menuActive = false;unsigned int previousButtons=0;
    for (;;) {
        unsigned int hsdButtons = 0;
#ifdef MELEE360_DECOMP
        Melee360XfbBeginRender();Melee360HsdStartScreen();
        Melee360DVDPump();
        Melee360AlarmPump();
        Melee360CardPump();
        Melee360ARAMPump();
        Melee360GXPump();
        hsdButtons = Melee360PadFrame();
#endif
        XINPUT_STATE input;
        bool exitRequested = false;
        bool skipIntro = false;
        unsigned int buttons=0;
        for (DWORD user = 0; user < 4; ++user) {
            ZeroMemory(&input, sizeof(input));
            if (XInputGetState(user, &input) == ERROR_SUCCESS) {
                buttons |= input.Gamepad.wButtons;
                if(!Melee360MenuUsesOriginalCursor()){
                    if(input.Gamepad.sThumbLY>16000)buttons|=XINPUT_GAMEPAD_DPAD_UP;
                    if(input.Gamepad.sThumbLY<-16000)buttons|=XINPUT_GAMEPAD_DPAD_DOWN;
                    if(input.Gamepad.sThumbLX>16000)buttons|=XINPUT_GAMEPAD_DPAD_RIGHT;
                    if(input.Gamepad.sThumbLX<-16000)buttons|=XINPUT_GAMEPAD_DPAD_LEFT;
                }
                if(input.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) exitRequested = true;
                if(input.Gamepad.wButtons & XINPUT_GAMEPAD_START) skipIntro = true;
            }
        }
        if(automatedTest) {exitRequested=false;skipIntro=false;buttons=0;}
        if(menuTest&&menuActive)buttons=Melee360MenuTestButtons(frame);
        unsigned int pressed=buttons&~previousButtons;previousButtons=buttons;
        if (exitRequested) {Melee360Log("Melee360: BACK requested exit\n");break;}
        device->Clear(0, NULL, D3DCLEAR_TARGET,
            probeOk ? D3DCOLOR_XRGB(10, 24, 48) : D3DCOLOR_XRGB(96, 0, 0), 1.0f, 0);
        D3DRECT pulse = {40, 40, 80 + (LONG)(frame % 240), 64};
        device->Clear(1, &pulse, D3DCLEAR_TARGET, D3DCOLOR_XRGB(40, 210, 140), 1.0f, 0);
        D3DRECT assetMarker = {40, 80, 280, 104};
        device->Clear(1, &assetMarker, D3DCLEAR_TARGET,
            assetState == 1 ? D3DCOLOR_XRGB(40, 210, 140) :
            assetState == -1 ? D3DCOLOR_XRGB(220, 160, 20) : D3DCOLOR_XRGB(210, 30, 30), 1.0f, 0);
        D3DRECT padMarker = {40, 120, 280, 144};
        device->Clear(1, &padMarker, D3DCLEAR_TARGET,
            (hsdButtons & 0x100) ? D3DCOLOR_XRGB(40, 210, 140) : D3DCOLOR_XRGB(80, 80, 80), 1.0f, 0);
#ifdef MELEE360_DECOMP
        // Actual movie texture replaces diagnostic bars while video is active.
        bool wasTitleActive=titleActive;
        if(!titleAttempted && (forceTitle || forceMenu || skipIntro || Melee360IntroVideoFinished())) {
            Melee360Log(forceTitle||forceMenu ? "Title transition: diagnostic flag\n" : skipIntro ? "Title transition: START\n" : "Title transition: movie completed\n");
            titleAttempted = true;
            titleActive = Melee360TitleInit(device);
            if(!titleActive) Melee360Log("Title: static scene initialization FAILED\n");
        }
        if(!menuActive && ((wasTitleActive && (pressed&(XINPUT_GAMEPAD_START|XINPUT_GAMEPAD_A)))||forceMenu)) {
            forceMenu=false;
            menuActive=Melee360MenuInit(device,automatedTest,buttons);
            if(!menuActive){Melee360Log("Menu: initialization FAILED\n");titleActive=Melee360TitleInit(device);}
            else{Melee360Log("Menu transition: title to main menu\n");Melee360IntroVideoClose();Melee360CloseIntro();}
        }
        const bool menuLeave=Melee360MenuScheduledFrame(menuActive,buttons,GetTickCount());
        if(menuActive) {
            // Require releasing the confirm button used to enter the menu.
            if(menuLeave) {
                Melee360MenuClose();menuActive=false;titleActive=Melee360TitleInit(device);
                Melee360Log("Menu transition: main menu to title\n");
                if(!titleActive||!Melee360TitleDraw(device)){Melee360Log("Title return: draw FAILED\n");break;}
            } else if(!Melee360MenuDraw(device)){Melee360Log("Menu: draw FAILED\n");break;}
        } else if(titleActive) {
            if(!Melee360TitleDraw(device)) {Melee360Log("Title: static mesh draw FAILED\n");break;}
        } else Melee360IntroVideoDraw(device);
#endif
#ifdef MELEE360_DECOMP
        if(!Melee360FpsDraw(device)){Melee360Log("FPS overlay draw FAILED\n");break;}

#endif
#ifdef MELEE360_DECOMP
        HRESULT presentResult=Melee360XfbPresent()?S_OK:E_FAIL;
#else
        HRESULT presentResult=device->Present(NULL,NULL,NULL,NULL);
#endif
        if (FAILED(presentResult)) {
            Melee360Log("Present failed\n"); break;
        }
        ++frame;
#ifdef MELEE360_DECOMP
        Melee360FpsPresented();
#endif
#ifdef MELEE360_DECOMP
        Melee360AudioPump(menuActive?Melee360MenuAudioTrack():(!titleActive&&!Melee360IntroVideoFinished()?3:0));
#endif
        if (frame == 120) Melee360Log("Melee360: 120 successful frame presentations\n");
    }
#ifdef MELEE360_DECOMP
    Melee360XfbClose();
    Melee360FpsClose();
    Melee360IntroVideoClose();
    Melee360AudioClose();
    Melee360GXBindDevice(NULL);
    Melee360GXDirectBind(NULL);
    Melee360TitleClose();
    Melee360MenuClose();
    Melee360MenuSchedulerClose();
    Melee360PadStop();
    Melee360CloseIntro();
#endif
    device->Release();
    d3d->Release();
}



