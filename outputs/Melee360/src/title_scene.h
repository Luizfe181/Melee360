#ifndef MELEE360_TITLE_SCENE_H
#define MELEE360_TITLE_SCENE_H
struct IDirect3DDevice9;
bool Melee360TitleInit(IDirect3DDevice9* device);
bool Melee360TrophyPage(IDirect3DDevice9*,int,bool,float);
bool Melee360MenuBackgroundInit(IDirect3DDevice9* device);
bool Melee360OriginalMenuPage(IDirect3DDevice9* device,int page,int selection,bool backwards=false);
void Melee360SceneSetWide(bool wide);
bool Melee360TitleDraw(IDirect3DDevice9* device);
void Melee360TitleClose();
bool Melee360SoundTestPage(IDirect3DDevice9*,bool);
bool Melee360OptionsPage(IDirect3DDevice9*,int,int,int,int,unsigned int,unsigned int);
#endif
bool Melee360CharacterSelectPage(IDirect3DDevice9* device,int selected);
bool Melee360BattlefieldPage(IDirect3DDevice9* device,int background);

bool Melee360StageSelectPage(IDirect3DDevice9*,float,float,int);
