#ifndef MELEE360_CARD_IMAGE_H
#define MELEE360_CARD_IMAGE_H
enum { MELEE360_CARD_BYTES=2*1024*1024, MELEE360_CARD_BLOCK=8192 };
// Native virtual card metadata. Serial belongs to this port, not a GameCube flash ID.
int Melee360FormatCardImage(unsigned char* image,unsigned int bytes,const unsigned char serial[32]);
int Melee360CheckCardSystem(const unsigned char* image,unsigned int bytes);
#endif
