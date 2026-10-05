#ifndef MELEE360_RUNTIME_ARCHIVE_H
#define MELEE360_RUNTIME_ARCHIVE_H
#include <sysdolphin/baselib/archive.h>
int Melee360ValidateNativeArchive(const unsigned char*,unsigned int);
int Melee360RuntimeArchiveLoad(const char*,HSD_Archive**);
int Melee360RuntimeAssetsProbe(void);
#endif
