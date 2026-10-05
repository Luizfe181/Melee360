#ifndef MELEE360_INTRO_STREAM_H
#define MELEE360_INTRO_STREAM_H
int Melee360PrepareIntro();
int Melee360PrepareMovie(const char* filename);
unsigned int Melee360MovieWidth();
unsigned int Melee360MovieHeight();
const unsigned char* Melee360IntroFirstFrame(unsigned int* bytes);
int Melee360IntroAdvance();
unsigned int Melee360IntroFrameIndex();
void Melee360CloseIntro();
#endif
