#include <sysdolphin/baselib/synth.h>
#include <math.h> // IWYU pragma: keep
#include <placeholder.h>
#include <string.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/devcom.h>
#include <dolphin/ai.h>
#include <dolphin/ar.h>
#include <dolphin/ax.h>
#include <dolphin/os.h>

OSHeapHandle HSD_Synth_804D6018 = -1;
void* HSD_AudioMalloc(size_t size)
{
    void* p = OSAllocFromHeap(HSD_Synth_804D6018, size);
    HSD_ASSERTREPORT(0x29U, p, "audio heap overflow.\n");
    return p;
}
void HSD_AudioFree(void* ptr)
{
    OSFreeToHeap(HSD_Synth_804D6018, ptr);
}
