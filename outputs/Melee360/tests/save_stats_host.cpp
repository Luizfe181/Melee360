#include "../src/save_stats.h"
#include <vector>
#include <stdio.h>
#include <string.h>
extern "C" {
#include <sysdolphin/baselib/crypt.h>
}
static void word(unsigned char* p,unsigned int v){p[0]=(unsigned char)(v>>24);p[1]=(unsigned char)(v>>16);p[2]=(unsigned char)(v>>8);p[3]=(unsigned char)v;}
int main(int argc,char** argv){if(argc!=2)return 1;FILE* f=fopen(argv[1],"rb");if(!f)return 2;fseek(f,0,SEEK_END);long bytes=ftell(f);rewind(f);std::vector<unsigned char> raw(bytes);if(fread(&raw[0],1,bytes,f)!=(unsigned int)bytes)return 3;fclose(f);Melee360SaveStats stats;
    if(!Melee360ReadSaveStats(&raw[0],raw.size(),stats))return 4;printf("Original GCI: time=%u stock=%u coin=%u bonus=%u stamina=%u resets=%u KOs=%u trophies=%u\n",stats.matches[0],stats.matches[1],stats.matches[2],stats.matches[3],stats.matches[4],stats.matches[5],stats.kos,stats.trophies);
    Melee360SaveStats unchanged=stats;if(Melee360ReadSaveStats(&raw[0],raw.size()-1,stats)||memcmp(&unchanged,&stats,sizeof(stats)))return 5;raw[0]^=1;if(Melee360ReadSaveStats(&raw[0],raw.size(),stats))return 6;raw[0]^=1;
    for(unsigned int at=64;at+8192<=raw.size();at+=8192)raw[at+60]^=1;if(Melee360ReadSaveStats(&raw[0],raw.size(),stats))return 7;
    std::vector<unsigned char> fixture(64+8192*2,0);memcpy(&fixture[0],"GALE01",6);fixture[0x39]=2;unsigned char* block=&fixture[64+8192];block[17]=1;block[19]=1;block[21]=0x17;block[22]=0x90;word(block+32+0x1b0,17);word(block+32+0x1f4,53);block[32+0x469]=12;unsigned char* mario=block+32+0x6c4+8*0xac;mario[2*24]=0x12;mario[2*24+1]=0x34;word(mario+0x34+12,0xfffffff9);word(mario+0x34+4,123456);mario[0x34+27]=9;mario[0x34+29]=5;mario[0x34+31]=4;unsigned char* ganon=block+32+0x6c4+24*0xac;ganon[0]=0xab;ganon[1]=0xcd;word(ganon+0x34+32,987654);if(HSD_Encrypt(block,8192)||!Melee360ReadSaveStats(&fixture[0],fixture.size(),stats)||stats.matches[0]!=17||stats.kos!=53||stats.trophies!=12||stats.fighters[8].opponentKOs[24]!=0x1234||stats.fighters[8].damageDealt!=-7||stats.fighters[8].attacksHit!=123456||stats.fighters[8].matches!=9||stats.fighters[8].wins!=5||stats.fighters[8].losses!=4||stats.fighters[24].opponentKOs[0]!=0xabcd||stats.fighters[24].playTime!=987654||stats.fighters[7].matches!=0)return 8;
    puts("Original crypto / BE counters / truncated / checksum / identity / output preservation tests passed");return 0;}
