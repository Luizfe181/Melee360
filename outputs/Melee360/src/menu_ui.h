#ifndef MELEE360_MENU_UI_H
#define MELEE360_MENU_UI_H
struct IDirect3DDevice9;
bool Melee360MenuInit(IDirect3DDevice9* device,bool automated,unsigned int initialButtons=0);
// Input uses XInput button masks, with repeat and stick directions mapped by caller.
bool Melee360MenuUpdate(unsigned int buttons,unsigned int ticks);
bool Melee360MenuDraw(IDirect3DDevice9* device);
void Melee360MenuClose();
unsigned int Melee360MenuTestButtons(unsigned int frame);
bool Melee360MenuUsesOriginalCursor();
bool Melee360MenuAudioActive();
int Melee360MenuAudioTrack();
float Melee360MenuMusicVolume();
int Melee360MenuSoundOutput();
void Melee360MenuSetSoundOutput(unsigned int);
int Melee360MenuSoundModeProbe();
#endif
