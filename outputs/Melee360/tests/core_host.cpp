#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
extern "C" {
#include <sysdolphin/baselib/archive.h>
int Melee360ValidateArchive(const unsigned char*, unsigned int);
}
extern "C" int Melee360HsdProbe(void);
extern "C" int OSDisableInterrupts(void) { return 1; }
extern "C" int OSRestoreInterrupts(int prior) { return prior; }
extern "C" void OSReport(const char* fmt, ...) { va_list a; va_start(a, fmt); vprintf(fmt, a); va_end(a); }
extern "C" __declspec(noreturn) void __assert(const char* f, unsigned l, const char* c) {
    fprintf(stderr, "%s:%u %s\n", f, l, c); exit(2);
}
int main(int argc, char** argv) {
    int result = Melee360HsdProbe();
    printf("HSD 32-bit host probes: %s\n", result ? "PASS" : "FAIL");
    __declspec(align(32)) unsigned char fixture[65] = {0};
    unsigned* words = (unsigned*)fixture;
    HSD_Archive archive;
    words[0] = sizeof(fixture); words[1] = 16; words[2] = 1; words[3] = 1;
    words[8] = 4; words[12] = 0; words[13] = 4; words[14] = 0;
    memcpy(fixture + 60, "root", 5);
    int archiveOk = HSD_ArchiveParse(&archive, fixture, sizeof(fixture)) == 0 &&
        HSD_ArchiveGetPublicAddress(&archive, "root") == fixture + 36 &&
        *(unsigned*)(fixture + 32) == (unsigned)(fixture + 36) &&
        HSD_ArchiveGetPublicAddress(&archive, "absent") == NULL &&
        HSD_ArchiveGetExtern(&archive, -1) == NULL;
    printf("Original HSD archive relocation/root probe: %s\n", archiveOk ? "PASS" : "FAIL");
    result = result && archiveOk;
    if (argc > 1) {
        FILE* f = fopen(argv[1], "rb");
        if (!f) return 3;
        fseek(f, 0, SEEK_END); unsigned size = ftell(f); rewind(f);
        unsigned char* bytes = (unsigned char*)malloc(size);
        if (!bytes || fread(bytes, 1, size, f) != size) return 3;
        fclose(f);
        int valid = Melee360ValidateArchive(bytes, size);
        int rejectsShort = !Melee360ValidateArchive(bytes, 31);
        bytes[8] = bytes[9] = bytes[10] = bytes[11] = 255;
        int rejectsOverflow = !Melee360ValidateArchive(bytes, size);
        printf("Actual Mario big-endian validation: %s; truncated/overflow rejection: %s\n",
            valid ? "PASS" : "FAIL", rejectsShort && rejectsOverflow ? "PASS" : "FAIL");
        result = result && valid && rejectsShort && rejectsOverflow;
        free(bytes);
    }
    return result ? 0 : 1;
}
