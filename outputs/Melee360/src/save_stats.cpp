#include "save_stats.h"
#include <vector>
#include <string.h>
extern "C" {
#include <sysdolphin/baselib/crypt.h>
}
static unsigned int be32(const unsigned char* p){return ((unsigned int)p[0]<<24)|((unsigned int)p[1]<<16)|(p[2]<<8)|p[3];}
static unsigned short be16(const unsigned char* p){return (unsigned short)((p[0]<<8)|p[1]);}
// Strict read-only GALE GCI subset: original logical file 1, GmSaveData 0x1790.
// Reject divergent spare copies instead of guessing which transaction is newer.
bool Melee360ReadSaveStats(const unsigned char* raw,unsigned int bytes,Melee360SaveStats& out){
    if(!raw||bytes<64+8192||bytes>64+32*8192||memcmp(raw,"GALE01",6)||bytes!=64u+be16(raw+0x38)*8192u)return false;
    std::vector<unsigned char> selected;unsigned int candidates=0;
    for(unsigned int at=64;at+8192<=bytes;at+=8192){std::vector<unsigned char> block(raw+at,raw+at+8192);if(HSD_Decrypt(&block[0],8192)||be16(&block[16])!=1)continue;
        bool manifest=false;for(int i=0;i<3;++i){unsigned char* row=&block[19+i*4];if(row[0]==1&&row[1]==0&&be16(row+2)==0x1790)manifest=true;}
        if(!manifest)continue;if(!selected.empty()&&memcmp(&selected[0],&block[32],0x1790))return false;selected.assign(block.begin()+32,block.begin()+32+0x1790);++candidates;
    }
    if(!candidates)return false;Melee360SaveStats result={0};const unsigned char* data=&selected[0];result.characters=be16(data);result.stages=be16(data+2);result.trophies=be16(data+0x468);
    if(result.trophies>293)return false;for(int i=0;i<6;++i)result.matches[i]=be32(data+0x1b0+i*4);result.damage=be32(data+0x1f0);result.kos=be32(data+0x1f4);result.selfDestructs=be32(data+0x1f8);
    // gm/types.h: GmSaveData.x1F2C, FighterData stride 0xAC, GmStats at +0x34.
    // Indices are SelectableCharacterKind, not CSS portrait order.
    for(int i=0;i<25;++i){const unsigned char* fighter=data+0x6c4+i*0xac;const unsigned char* s=fighter+0x34;Melee360FighterStats& f=result.fighters[i];
        for(int j=0;j<25;++j)f.opponentKOs[j]=be16(fighter+j*2);f.selfDestructs=be16(s);f.attacksHit=be32(s+4);f.attacksTotal=be32(s+8);f.damageDealt=(int)be32(s+12);f.damageTaken=(int)be32(s+16);f.peakDamage=be16(s+24);f.matches=be16(s+26);f.wins=be16(s+28);f.losses=be16(s+30);f.playTime=be32(s+32);
    }out=result;return true;
}
