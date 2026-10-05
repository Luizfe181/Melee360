#ifndef MELEE360_ASSET_ARCHIVE_H
#define MELEE360_ASSET_ARCHIVE_H
#ifdef __cplusplus
extern "C" {
#endif
int Melee360ValidateArchive(const unsigned char* bytes, unsigned int size);
int Melee360LoadMario(void);
#ifdef __cplusplus
}
#endif
#endif
