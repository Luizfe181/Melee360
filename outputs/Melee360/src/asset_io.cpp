#include <xtl.h>
#include "asset_archive.h"
#include "platform_log.h"
extern "C" int Melee360ParseMario(unsigned char*, unsigned int);
static void* marioBytes;
extern "C" int Melee360LoadMario(void)
{
    HANDLE file = CreateFileA("game:\\data\\PlMr.dat", GENERIC_READ,
        FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (file == INVALID_HANDLE_VALUE) {
        Melee360Log("Asset missing: game:\\data\\PlMr.dat\n"); return -1;
    }
    DWORD high = 0, size = GetFileSize(file, &high), read = 0;
    if (high || size < 32 || size > 32 * 1024 * 1024) {
        CloseHandle(file); Melee360Log("Invalid Mario asset size\n"); return 0;
    }
    if (marioBytes) { CloseHandle(file); return 0; }
    marioBytes = XPhysicalAlloc(size, MAXULONG_PTR, 32, PAGE_READWRITE);
    bool ok = marioBytes && ReadFile(file, marioBytes, size, &read, NULL) && read == size;
    CloseHandle(file);
    if (ok) ok = Melee360ParseMario((unsigned char*)marioBytes, size) != 0;
    if (!ok) {
        if (marioBytes) XPhysicalFree(marioBytes);
        marioBytes = NULL;
        Melee360Log("Mario HSD archive failed validation/parse/root lookup\n"); return 0;
    }
    Melee360Log("Mario HSD archive loaded: ftDataMario found\n");
    return 1;
}
