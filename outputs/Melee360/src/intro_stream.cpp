#include <xtl.h>
#include <stdio.h>
#include "intro_stream.h"
#include "platform_log.h"
static HANDLE movie = INVALID_HANDLE_VALUE;
static unsigned char* packedFrame = NULL;
static DWORD packedBytes = 0;
static DWORD capacity = 0, frameIndex = 0, frameCount = 0;
static ULONGLONG nextOffset = 0, movieBytes = 0;
static unsigned int movieWidth,movieHeight;
unsigned int Melee360MovieWidth() {return movieWidth;}
unsigned int Melee360MovieHeight() {return movieHeight;}
static DWORD be32(const unsigned char* p)
{
    return (DWORD(p[0]) << 24) | (DWORD(p[1]) << 16) | (DWORD(p[2]) << 8) | p[3];
}
void Melee360CloseIntro()
{
    if (packedFrame) XPhysicalFree(packedFrame);
    packedFrame = NULL;
    packedBytes = 0;
    capacity = frameIndex = frameCount = 0;
    movieWidth=movieHeight=0;
    if (movie != INVALID_HANDLE_VALUE) CloseHandle(movie);
    movie = INVALID_HANDLE_VALUE;
}
int Melee360PrepareIntro() {return Melee360PrepareMovie("MvOpen.mth");}
int Melee360PrepareMovie(const char* filename)
{
    Melee360CloseIntro();
    if(!filename||strlen(filename)>64||strchr(filename,'/')||strchr(filename,'\\'))return 0;
    char path[96];sprintf_s(path,sizeof(path),"game:\\data\\%s",filename);
    movie = CreateFile(path, GENERIC_READ,
        FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (movie == INVALID_HANDLE_VALUE) {
        Melee360Log("Boot: opening movie file unavailable\n");
        return -1;
    }
    unsigned char header[64];
    DWORD read = 0;
    LARGE_INTEGER fileSize;
    if (!GetFileSizeEx(movie, &fileSize) || !ReadFile(movie, header, 64, &read, NULL) || read != 64) {
        Melee360Log("Boot: opening movie header read FAILED\n");
        Melee360CloseIntro();
        return 0;
    }
    const DWORD width = be32(header+16), height = be32(header+20);
    const DWORD fps = be32(header+24), frames = be32(header+28);
    const DWORD firstOffset = be32(header+32), firstSize = be32(header+40);
    const DWORD maxSize = be32(header+12);
    const DWORD packedCapacity = (maxSize + 4 + 31) & ~31u;
    if (memcmp(header, "MTHP", 4) || be32(header+8) != 2 ||
        !width || !height || width>640 || height>480 || width%16 || height%16 || fps != 30 || !frames ||
        firstOffset < 64 || firstSize < 8 || firstSize > packedCapacity || maxSize > 2*1024*1024 ||
        (ULONGLONG)firstOffset + firstSize > (ULONGLONG)fileSize.QuadPart) {
        Melee360Log("Boot: opening movie header validation FAILED\n");
        Melee360CloseIntro();
        return 0;
    }
    // Header maxSize excludes the packed prefix/alignment. Frame 2650 occupies
    // 61184 bytes although this movie advertises 61152; reserve one aligned prefix.
    packedFrame = (unsigned char*)XPhysicalAlloc(packedCapacity, MAXULONG_PTR, 32, PAGE_READWRITE);
    LARGE_INTEGER offset;
    offset.QuadPart = firstOffset;
    if (!packedFrame || !SetFilePointerEx(movie, offset, NULL, FILE_BEGIN) ||
        !ReadFile(movie, packedFrame, firstSize, &read, NULL) || read != firstSize ||
        packedFrame[4] != 0xFF || packedFrame[5] != 0xD8) {
        Melee360Log("Boot: opening compressed frame read FAILED\n");
        Melee360CloseIntro();
        return 0;
    }
    packedBytes = firstSize;
    capacity = packedCapacity;
    frameCount = frames;
    movieWidth=width;movieHeight=height;
    movieBytes = fileSize.QuadPart;
    nextOffset = (ULONGLONG)firstOffset + firstSize;
    char message[160];
    sprintf_s(message, sizeof(message), "Boot: %s prepared %lux%lu %lu fps %lu frames; first compressed frame %lu bytes\n",
        filename,width, height, fps, frames, firstSize);
    Melee360Log(message);
    return 1;
}
const unsigned char* Melee360IntroFirstFrame(unsigned int* bytes)
{
    if (bytes) *bytes = packedBytes > 4 ? packedBytes-4 : 0;
    return packedFrame ? packedFrame+4 : NULL;
}
unsigned int Melee360IntroFrameIndex() { return frameIndex; }
int Melee360IntroAdvance()
{
    if (!packedFrame) return -1;
    if (frameIndex+1 >= frameCount) return 0;
    DWORD nextSize = be32(packedFrame), read = 0;
    if (nextSize < 8 || nextSize > capacity || nextOffset+nextSize > movieBytes) return -1;
    LARGE_INTEGER offset;
    offset.QuadPart = nextOffset;
    if (!SetFilePointerEx(movie, offset, NULL, FILE_BEGIN) ||
        !ReadFile(movie, packedFrame, nextSize, &read, NULL) || read != nextSize ||
        packedFrame[4] != 0xFF || packedFrame[5] != 0xD8) return -1;
    nextOffset += nextSize;
    packedBytes = nextSize;
    ++frameIndex;
    return 1;
}
