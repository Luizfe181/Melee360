#ifndef MELEE360_SAVE_STATS_H
#define MELEE360_SAVE_STATS_H
struct Melee360FighterStats {unsigned short opponentKOs[25],selfDestructs,matches,wins,losses,peakDamage;unsigned int attacksHit,attacksTotal,playTime;int damageDealt,damageTaken;};
struct Melee360SaveStats {unsigned int matches[6],kos,damage,selfDestructs;unsigned short characters,stages,trophies;Melee360FighterStats fighters[25];};
bool Melee360ReadSaveStats(const unsigned char*,unsigned int,Melee360SaveStats&);
#endif
