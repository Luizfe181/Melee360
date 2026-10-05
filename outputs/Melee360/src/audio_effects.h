#ifndef MELEE360_AUDIO_EFFECTS_H
#define MELEE360_AUDIO_EFFECTS_H
#include <vector>
bool Melee360EffectsInit();
void Melee360EffectsClose();
bool Melee360EffectsProcess(std::vector<short>& pcm,unsigned int channels,bool finalBlock);
int Melee360EffectsBridgeProbe();
#endif
