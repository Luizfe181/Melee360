/* Link-only proof for the real creation path. Never packaged or executed. */
#include <melee/ft/fighter.h>
#include <melee/pl/types.h>
void Melee360FighterCreateLinkEntry(void){struct plAllocInfo info={0};info.internal_id=Ft_Kind_Mario;info.slot=0;Fighter_FirstInitialize_80067A84();Fighter_Create(&info);}
