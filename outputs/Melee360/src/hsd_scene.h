#ifndef MELEE360_HSD_SCENE_H
#define MELEE360_HSD_SCENE_H
#include <vector>
#include "original_character_select.h"
struct Melee360SceneVertex {float clip[4],uv[2],color[4];};
struct Melee360SceneTexture {unsigned int width,height,contentHash;std::vector<unsigned int> pixels;Melee360SceneTexture():width(0),height(0),contentHash(0){}};
struct Melee360SceneBatch {std::vector<Melee360SceneVertex> vertices;int texture;unsigned int joint,mode,wrapS,wrapT;};
struct Melee360Scene {std::vector<Melee360SceneBatch> batches;std::vector<Melee360SceneTexture> textures;unsigned int skipped,unsupportedEvents;Melee360Scene():skipped(0),unsupportedEvents(0){}};
// Clear before replacing archives whose backing allocation can be reused.
void Melee360ResetSceneCache();
bool Melee360LoadTrophyModel(const unsigned char*,unsigned int,const char*,Melee360Scene&);
// Static descriptor diagnostic with partial materials; scene callbacks pending.
bool Melee360LoadStaticScene(const unsigned char* archive,unsigned int bytes,const char* root,Melee360Scene& scene);
// Original main-menu archive objects posed by upstream FObj. Navigation remains
// the platform bridge until the original scene scheduler and game state link.
bool Melee360LoadOriginalMenu(const unsigned char* archive,unsigned int bytes,int menu,int selection,float frame,
    Melee360Scene& scene,unsigned int* tracks,bool animate=false,float hoverFrame=0,bool backwards=false);
bool Melee360OriginalMenuSupported(int menu);
bool Melee360LoadAnimatedTitle(const unsigned char* archive,unsigned int bytes,float frame,Melee360Scene& scene,unsigned int* tracks);
bool Melee360LoadCharacterSelect(const unsigned char* archive,unsigned int bytes,int selected,Melee360Scene& scene,float frame=0,bool animate=false,const Melee360CSSState* cursor=0);
bool Melee360LoadFighterPreview(const unsigned char* archive,unsigned int bytes,Melee360Scene& scene);
bool Melee360LoadStageSelect(const unsigned char*,unsigned int,float,float,float,int,Melee360Scene&);
// Original CSS DViWait FigaTree/FObj motion; descriptor bridge, no fighter logic.
bool Melee360LoadAnimatedFighterPreview(const unsigned char* model,unsigned int modelBytes,
    const unsigned char* motion,unsigned int motionBytes,float frame,Melee360Scene& scene,unsigned int* tracks);
// One-stage descriptor diagnostic. Background variants are chosen explicitly;
// original stage callbacks, particles and collisions are not executed here.
bool Melee360LoadBattlefield(const unsigned char* archive,unsigned int bytes,float frame,
    int background,Melee360Scene& scene,unsigned int* tracks,unsigned int* groups=0);
bool Melee360AppendOriginalMenuCaption(const unsigned char* menuArchive,unsigned int menuBytes,
    const unsigned char* sisArchive,unsigned int sisBytes,const unsigned char* font,unsigned int fontBytes,
    int menu,int selection,Melee360Scene& scene);
bool Melee360LoadSoundTest(const unsigned char*,unsigned int,float,bool,Melee360Scene&,unsigned int*);
bool Melee360LoadOptions(const unsigned char*,unsigned int,int,int,int,int,unsigned int,unsigned int,float,Melee360Scene&,unsigned int*);
#endif
