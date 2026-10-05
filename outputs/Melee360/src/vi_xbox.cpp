#include <xtl.h>
#include "platform_log.h"
extern "C" {
#include <dolphin/vi.h>
#include <dolphin/os.h>
void __assert(const char*,unsigned int,const char*);
}
namespace {
u32 count;bool initialized,inFrame;VIRetraceCallback pre,post;
u32 probePre,probePost;
void before(u32 value){probePre=value;}
void after(u32 value){probePost=value;}
}
/* Presentation-boundary adapter, not a physical vblank interrupt emulator.
 * Callbacks run on the render thread and only surround successful frames. */
extern "C" void VIInit(void){if(!initialized){count=0;pre=post=0;inFrame=false;initialized=true;}}
extern "C" u32 VIGetRetraceCount(void){VIInit();return count;}
extern "C" VIRetraceCallback VISetPreRetraceCallback(VIRetraceCallback value){VIInit();VIRetraceCallback old=pre;pre=value;return old;}
extern "C" VIRetraceCallback VISetPostRetraceCallback(VIRetraceCallback value){VIInit();VIRetraceCallback old=post;post=value;return old;}
extern "C" void Melee360VIBeginFrame(void){VIInit();if(inFrame)__assert(__FILE__,__LINE__,"nested VI presentation");inFrame=true;if(pre)pre(count+1);}
extern "C" void Melee360VIEndFrame(int success){if(!inFrame)__assert(__FILE__,__LINE__,"VI presentation not begun");inFrame=false;if(success){++count;if(post)post(count);}}
extern "C" int Melee360VIProbe(void){
    u32 saved=count;VIRetraceCallback oldPre=VISetPreRetraceCallback(before),oldPost=VISetPostRetraceCallback(after);
    // Probe callback dispatch only; restore the count so no synthetic frame persists.
    probePre=probePost=0;Melee360VIBeginFrame();Melee360VIEndFrame(1);
    bool ok=probePre==saved+1&&probePost==saved+1&&count==saved+1;
    Melee360VIBeginFrame();Melee360VIEndFrame(0);ok=ok&&count==saved+1;
    VISetPreRetraceCallback(oldPre);VISetPostRetraceCallback(oldPost);count=saved;return ok;
}

namespace {
GXRenderModeObj stagedMode,activeMode;void* stagedBuffer;void* activeBuffer;
int stagedBlack,activeBlack;bool modeDirty,bufferDirty,blackDirty;int (*presenter)(void);
}
extern "C" int Melee360XfbValid(void*);
extern "C" int Melee360XfbModeSupported(const GXRenderModeObj*);
extern "C" void GXWaitDrawDone(void);
extern "C" void VIConfigure(GXRenderModeObj* mode){
    if(!Melee360XfbModeSupported(mode))__assert(__FILE__,__LINE__,"unsupported native VI mode");stagedMode=*mode;modeDirty=true;
}
extern "C" void VISetNextFrameBuffer(void* buffer){if(!Melee360XfbValid(buffer))__assert(__FILE__,__LINE__,"unregistered native XFB");stagedBuffer=buffer;bufferDirty=true;}
extern "C" void VISetBlack(BOOL black){stagedBlack=black?1:0;blackDirty=true;}
extern "C" void VIFlush(void){
    int token=OSDisableInterrupts();if(modeDirty)activeMode=stagedMode;if(bufferDirty)activeBuffer=stagedBuffer;if(blackDirty)activeBlack=stagedBlack;
    modeDirty=bufferDirty=blackDirty=false;OSRestoreInterrupts(token);
}
extern "C" u32 VIGetNextField(void){return (activeMode.viTVmode&3)==VI_INTERLACE?((count+1)&1):0;}
extern "C" void* Melee360VIActiveBuffer(void){return activeBuffer;}
extern "C" int Melee360VIBlack(void){return activeBlack;}
extern "C" void Melee360VISetPresenter(int (*value)(void)){presenter=value;}
extern "C" void VIWaitForRetrace(void){
    if(!presenter||inFrame)__assert(__FILE__,__LINE__,"VI wait outside initialized presentation path");
    GXWaitDrawDone();Melee360VIBeginFrame();int ok=presenter();Melee360VIEndFrame(ok);
    if(!ok)__assert(__FILE__,__LINE__,"native VI presentation failed");
}
