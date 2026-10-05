#ifndef MELEE360_MTH_DECODE_H
#define MELEE360_MTH_DECODE_H
/* Portable replacement for Gekko Huffman/IDCT: baseline 4:2:0 MTH frames.
 * The entropy bytes in MTH are raw, without JPEG FF/00 byte stuffing. */
int Melee360DecodeMth(const unsigned char* input, unsigned int size,
                     unsigned int* argb, unsigned int width, unsigned int height);
#endif
