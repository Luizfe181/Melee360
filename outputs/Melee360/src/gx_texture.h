#ifndef MELEE360_GX_TEXTURE_H
#define MELEE360_GX_TEXTURE_H
unsigned int Melee360GxTextureBytes(unsigned int width,unsigned int height,unsigned int format);
int Melee360DecodeGxTexture(const unsigned char* data,unsigned int bytes,
    unsigned int width,unsigned int height,unsigned int format,
    const unsigned char* palette,unsigned int paletteEntries,unsigned int paletteFormat,
    unsigned int* argb,unsigned int outputPixels);
#endif
