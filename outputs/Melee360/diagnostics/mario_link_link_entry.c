/* Link-only dependency proof. Not packaged, not a runnable match. */
#include <melee/ft/fighter.h>
#include <melee/pl/types.h>
#include "../src/training_stage.h"
void Melee360FighterCreateLinkEntry(void){
    struct plAllocInfo mario={0},link={0};
    Melee360FightPrepare();
    mario.internal_id=Ft_Kind_Mario;mario.slot=0;
    link.internal_id=Ft_Kind_Link;link.slot=1;
    Fighter_FirstInitialize_80067A84();Fighter_Create(&mario);Fighter_Create(&link);
}
