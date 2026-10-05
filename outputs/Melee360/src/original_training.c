#ifndef LINT
#define LINT 1
#endif
#include "../compat/gameplay_boundary.h"
#include <melee/gm/types.h>
#include <melee/ft/forward.h>
#include <string.h>
#include "training_stage.h"
#define memzero(p,n) memset(p,0,n)
#define gm_SetupPlayerDefaults M360SetupPlayerDefaults
#define gm_SetupAllPlayerDefaults M360SetupAllPlayerDefaults
#define gm_SetupRulesDefaults M360SetupRulesDefaults
#define gm_801B05F4 M360SetupPlayerSlot
#define gm_SetupHumanPlayer M360SetupHumanPlayer
#define gm_SetupCpuPlayer M360SetupCpuPlayer
#define gm_80189CDC M360TrainingConfigure
static TrainingModeState lbl_80473700;
static CssSubStruct gm_80473814;
static StartMeleeData trainingData;
#include <generated/original_training_rules.inc>
int Melee360TrainingPrepare(int ckind){int i;if(ckind<0||ckind>=26)return 0;memset(&trainingData,0,sizeof(trainingData));M360SetupRulesDefaults(&trainingData.rules);M360SetupAllPlayerDefaults(trainingData.players);trainingData.rules.stkind=31;
    M360SetupHumanPlayer(&trainingData.players[0],(u8)ckind,0,1,0);M360SetupCpuPlayer(&trainingData.players[1],CKind_Mario,0,1,0);
    /* These three flags are the original gm_801B1F70 Training entry settings. */
    trainingData.rules.x3_6=true;trainingData.rules.x2_5=false;trainingData.rules.x2_1=true;
    for(i=0;i<4;++i){trainingData.players[i].xC_b1=false;trainingData.players[i].xD_b2=true;}
    M360TrainingConfigure(&trainingData);return trainingData.rules.stkind==31&&trainingData.players[0].slot_type==Gm_PKind_Human&&trainingData.players[1].slot_type==Gm_PKind_Cpu&&trainingData.players[2].slot_type==Gm_PKind_NA&&lbl_80473700.count==1;
}
int Melee360TrainingProbe(void){if(!Melee360TrainingPrepare(CKind_Mario))return 0;return trainingData.rules.match_kind==0&&trainingData.rules.is_teams==1&&trainingData.rules.item_freq==-1&&trainingData.rules.x20==0xffffffffffffffffULL&&trainingData.players[0].slot==1&&trainingData.players[1].team==4&&trainingData.players[0].attack_ratio==1&&trainingData.players[0].defense_ratio==1&&!Melee360TrainingPrepare(-1);}


const StartMeleeData* Melee360TrainingStartData(void){return &trainingData;}
static StartMeleeData fightData;
int Melee360FightPrepare(void){
    memset(&fightData,0,sizeof(fightData));M360SetupRulesDefaults(&fightData.rules);M360SetupAllPlayerDefaults(fightData.players);
    fightData.rules.stkind=31;fightData.rules.match_kind=MatchKind_Stock;fightData.rules.timer_enabled=false;fightData.rules.is_teams=false;fightData.rules.item_freq=-1;
    M360SetupHumanPlayer(&fightData.players[0],CKind_Mario,0,3,0);M360SetupCpuPlayer(&fightData.players[1],CKind_Link,0,3,1);fightData.players[1].cpu_level=9;
    return 1;
}
const StartMeleeData* Melee360FightStartData(void){return &fightData;}
int Melee360FightSetupProbe(void){if(!Melee360FightPrepare())return 0;return fightData.rules.stkind==31&&fightData.rules.match_kind==MatchKind_Stock&&!fightData.rules.is_teams&&!fightData.rules.timer_enabled&&fightData.rules.item_freq==-1&&fightData.players[0].ckind==CKind_Mario&&fightData.players[1].ckind==CKind_Link&&fightData.players[0].slot_type==Gm_PKind_Human&&fightData.players[1].slot_type==Gm_PKind_Cpu&&fightData.players[0].slot==1&&fightData.players[1].slot==2&&fightData.players[1].cpu_level==9&&fightData.players[0].stocks==3&&fightData.players[1].stocks==3&&fightData.players[2].slot_type==Gm_PKind_NA&&fightData.players[3].slot_type==Gm_PKind_NA;}
