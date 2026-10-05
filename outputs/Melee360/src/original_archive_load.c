#include "../compat/gameplay_boundary.h"
#include <melee/lb/lbarchive.h>
#include <melee/lb/lbfile.h>
#include <melee/lb/lbheap.h>
#include <sysdolphin/baselib/archive.h>
#include <sysdolphin/baselib/debug.h>
#include <stdarg.h>
static inline void readArchive(const char* filename, void* data,
                               HSD_Archive* archive)
{
    size_t length;

    lbFile_8001668C(filename, data, &length);
    lbArchive_InitializeDAT(archive, data, length);
}
static inline HSD_Archive* loadArchive(const char* filename)
{
    HSD_Archive* archive;
    void* data;

    data = lbHeap_80015BD0(0, OSRoundUp32B(lbFileGetSize(filename)));
    archive = lbHeap_80015BD0(0, sizeof(HSD_Archive));
    readArchive(filename, data, archive);
    return archive;
}
HSD_Archive* lbArchive_LoadArchive(const char* filename)
{
    return loadArchive(filename);
}
static inline void vLoadSectionsFatal(HSD_Archive* archive, void** symbol,
                                      va_list symbols)
{
    const char* symbol_name;

    for (; symbol != NULL; symbol = va_arg(symbols, void**)) {
        symbol_name = va_arg(symbols, const char*);
        *symbol = NULL;
        *symbol = HSD_ArchiveGetPublicAddress(archive, symbol_name);
        if (*symbol == NULL) {
            OSReport("Cannot find symbol %s.\n", symbol_name);
            HSD_ASSERT(112, 0);
        }
    }
}
HSD_Archive*(lbArchive_LoadSymbols) (const char* filename, void* symbols, ...)
{
    va_list sections;
    HSD_Archive* archive;

    va_start(sections, symbols);

    archive = loadArchive(filename);
    vLoadSectionsFatal(archive, symbols, sections);

    va_end(sections);
    return archive;
}
