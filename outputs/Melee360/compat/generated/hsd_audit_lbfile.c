void Melee360LoadWaitPump(void);
#include <melee/lb/lbfile.h>

#include <placeholder.h>
#include <string.h>

#include <melee/lb/lb_0195.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbheap.h>
#include <melee/lb/lblanguage.h>
#include <dolphin/dvd.h>
#include <sysdolphin/baselib/debug.h>
#include <sysdolphin/baselib/devcom.h>

static bool cancel;

static void lbFile_8001615C(int dcreq, uintptr_t args, void* buf,
                            bool cancelflag)
{
    HSD_ASSERT(71, !cancelflag);
    cancel = true;
}

/// @todo Non-inlined function forces loop in ::lbFile_800161C4 to yield to
///       interrupts. Pragma solution likely fake.
#ifdef __MWERKS__
#pragma push
#pragma dont_inline on
#endif
static bool discIsDone(void)
{
    Melee360LoadWaitPump();
    return cancel;
}
#ifdef __MWERKS__
#pragma pop
#endif

static void waitForDisc(void)
{
    do {
    } while (!discIsDone());
}

void lbFile_800161C4(int file, uintptr_t src, uintptr_t dst, size_t size,
                     int type, int pri)
{
    cancel = false;
    HSD_DevComRequest(file, src, dst, size, type, pri, lbFile_8001615C, 0);
    waitForDisc();
    OSReport("Original lbFile wait completed\n");
}

#define MAX_FILENAME_LENGTH 0x20
enum { FILE_EXTENSION_LENGTH = 4 }; // ".usd" or ".dat"
enum { MAX_BASENAME_LENGTH = MAX_FILENAME_LENGTH - FILE_EXTENSION_LENGTH };

/// append file extension (if needed)
char* lbFileGetFullName(const char* basename);

size_t lbFile_8001634C(int fileno);

size_t lbFileGetSize(const char* basename);

void lbFile_800164A4(int file, uintptr_t dst, size_t* size, int pri,
                     HSD_DevComCallback callback, uintptr_t args);

void lbFile_80016580(const char* basename, void* dst, size_t* size,
                     HSD_DevComCallback callback, uintptr_t args);

void lbFile_8001668C(const char* basename, void* dst, size_t* size);

static void loadFile(int heap_id, const char* basename, void** dst,
                     size_t* size)
{
    OSReport("Original loadFile: %s heap=%d\n", basename, heap_id);
    *size = lbFileGetSize(basename);
    *dst = lbHeap_80015BD0(heap_id, OSRoundUp32B(*size));
    OSReport("Original loadFile allocation: %p bytes=%u\n", *dst, (unsigned)*size);
    lbFile_80016580(basename, *dst, size, lbFile_8001615C, 0);
    waitForDisc();
    OSReport("Original lbFile wait completed\n");
}

void lbFile_80016760(const char* basename, void** dst, size_t* size)
{
    cancel = false;
    loadFile(0, basename, dst, size);
}

bool lbFile_800168A0(int heap_id, const char* basename, void** dst,
                     size_t* size)
{
    if ((*dst = lbDvd_8001819C(basename))) {
        *size = lbFileGetSize(basename);
        return true;
    } else {
        cancel = false;
        loadFile(heap_id, basename, dst, size);
        return false;
    }
}
