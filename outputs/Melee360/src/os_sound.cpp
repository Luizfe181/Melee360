#include "menu_ui.h"
extern "C" {
#include <dolphin/os.h>
#include <dolphin/os/OSRtc.h>
// The same setting feeds the XAudio output matrix and menu persistence.
// Original OS supports Mono/Stereo; the port's pending Surround option uses
// Stereo until a decoder exists. Invalid values do not alter the setting.
u32 OSGetSoundMode(void){return Melee360MenuSoundOutput()==0?OS_SOUND_MODE_MONO:OS_SOUND_MODE_STEREO;}
void OSSetSoundMode(u32 mode){Melee360MenuSetSoundOutput(mode);}
}
