#ifndef MELEE360_INTRO_VIDEO_H
#define MELEE360_INTRO_VIDEO_H
struct IDirect3DDevice9;
bool Melee360IntroVideoInit(IDirect3DDevice9* device);
bool Melee360IntroVideoDraw(IDirect3DDevice9* device);
void Melee360IntroVideoClose();
bool Melee360IntroVideoFinished();
#endif
