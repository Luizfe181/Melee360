#include "../compat/gameplay_boundary.h"
#include <melee/lb/lbfile.h>
#include <dolphin/ar.h>
#include <dolphin/dvd.h>
#include <sysdolphin/baselib/devcom.h>
#include <sysdolphin/baselib/debug.h>
#include <string.h>
#include <stdio.h>
void Melee360DVDPump(void);void Melee360ARAMPump(void);
static bool cancel;
void Melee360LoadWaitPump(void){Melee360DVDPump();Melee360ARAMPump();}
/* Native filesystem name boundary: exact filenames or manifest-backed .usd/.dat. */
char* lbFileGetFullName(const char* basename){static char name[32];size_t length;HSD_ASSERT(0,basename);length=strlen(basename);HSD_ASSERT(0,length<sizeof(name)-5);strcpy(name,basename);if(!strchr(name,'.')){strcat(name,".usd");if(DVDConvertPathToEntrynum(name)<0){strcpy(name,basename);strcat(name,".dat");}}return name;}
static void lbFile_8001615C(int dcreq, uintptr_t args, void* buf,
                            bool cancelflag)
{
    HSD_ASSERT(71, !cancelflag);
    cancel = true;
}
static bool discIsDone(void)
{
    Melee360LoadWaitPump();
    return cancel;
}
static void waitForDisc(void)
{
    do {
    } while (!discIsDone());
}
size_t lbFile_8001634C(int fileno)
{
    DVDFileInfo info;
    size_t length;
    bool intr = OSDisableInterrupts();

    if (!DVDFastOpen(fileno, &info)) {
        OSReport("Cannot open file no=%d.", fileno);
        HSD_ASSERT(0xD8, 0);
    }

    length = info.length;
    DVDClose(&info);
    OSRestoreInterrupts(intr);
    return length;
}
size_t lbFileGetSize(const char* basename)
{
    int entry_num;
    char* filename = lbFileGetFullName(basename);
    entry_num = DVDConvertPathToEntrynum(filename);
    HSD_ASSERTREPORT(0xEE, entry_num != -1, "file isn't exist %s = %d\n",
                     filename, entry_num);
    return lbFile_8001634C(entry_num);
}
void lbFile_800164A4(int file, uintptr_t dst, size_t* size, int pri,
                     HSD_DevComCallback callback, uintptr_t args)
{
    int type;
    *size = lbFile_8001634C(file);
    type = (dst >= ARGetSize()) ? 0x21 : 0x23;
    HSD_DevComRequest(file, 0, dst, OSRoundUp32B(*size), type, pri, callback,
                      args);
}
void lbFile_80016580(const char* basename, void* dst, size_t* size,
                     HSD_DevComCallback callback, uintptr_t args)
{
    char* filename = lbFileGetFullName(basename);
    int entry_num = DVDConvertPathToEntrynum(filename);
    PAD_STACK(4);

    HSD_ASSERTREPORT(0x11A, entry_num != -1, "file isn't exist %s = %d\n",
                     filename, entry_num);

    lbFile_800164A4(entry_num, (uintptr_t) dst, size, 1, callback, args);
}
void lbFile_8001668C(const char* basename, void* dst, size_t* size)
{
    OSReport("lbFile native wait: %s\n", basename);
    cancel = false;
    lbFile_80016580(basename, dst, size, lbFile_8001615C, 0);
    waitForDisc();
}
