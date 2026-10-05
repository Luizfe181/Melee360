#include "asset_archive.h"
#include <sysdolphin/baselib/archive.h>
#include <string.h>
static HSD_Archive mario;

static unsigned int be32(const unsigned char* p)
{
    return ((unsigned int)p[0] << 24) | ((unsigned int)p[1] << 16) |
        ((unsigned int)p[2] << 8) | p[3];
}

int Melee360ValidateArchive(const unsigned char* p, unsigned int size)
{
    unsigned int data, reloc, pub, ext, table, names, i, j, count, offset;
    if (!p || size < 32 || be32(p) != size) return 0;
    data = be32(p + 4); reloc = be32(p + 8);
    pub = be32(p + 12); ext = be32(p + 16);
    if (data > size - 32 || (data & 3)) return 0;
    table = 32 + data;
    if (reloc > (size - table) / 4) return 0;
    table += reloc * 4;
    if (pub > (size - table) / 8) return 0;
    table += pub * 8;
    if (ext > (size - table) / 8) return 0;
    names = table + ext * 8;
    for (i = 0; i < reloc; ++i) {
        offset = be32(p + 32 + data + i * 4);
        if (data < 4 || offset > data - 4 || (offset & 3)) return 0;
        if (be32(p + 32 + offset) > data) return 0;
    }
    table = 32 + data + reloc * 4;
    count = pub + ext;
    for (i = 0; i < count; ++i) {
        offset = be32(p + table + i * 8);
        if (i < pub ? offset >= data : (offset != 0xFFFFFFFFu && (data < 4 || offset > data - 4))) return 0;
        j = be32(p + table + i * 8 + 4);
        if (j >= size - names || !memchr(p + names + j, 0, size - names - j)) return 0;
    }
    return 1;
}

// Only call on Xbox's big-endian 32-bit target. The buffer remains owned by IO.
int Melee360ParseMario(unsigned char* bytes, unsigned int size)
{
    unsigned int endian = 1;
    if (*(unsigned char*)&endian == 1) return 0;
    if (!Melee360ValidateArchive(bytes, size)) return 0;
    if (HSD_ArchiveParse(&mario, bytes, size) != 0) return 0;
    return HSD_ArchiveGetPublicAddress(&mario, "ftDataMario") != NULL;
}
