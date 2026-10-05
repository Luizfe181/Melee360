#include "../compat/gameplay_boundary.h"
#include <melee/pl/player.h>
#include <melee/ft/fighter.h>
#include <melee/ft/types.h>
#include <melee/lb/lbaudio_ax.h>
#include <sysdolphin/baselib/debug.h>
#include <melee/lb/lbdvd.h>
#include <melee/lb/lbarq.h>
#include <melee/gm/types.h>
#include <melee/gm/gmvs.h>
#include <sysdolphin/baselib/gobj.h>
#include <sysdolphin/baselib/sislib.h>
#include <sysdolphin/baselib/initialize.h>
#include "training_stage.h"
#include <melee/it/iteffect.h>
#include <melee/cm/camera.h>
#include <stdio.h>
#include <string.h>
static int hideBotRender,hideBotShadows;
int Melee360GObjRuntimeInit(void);void Melee360LoadWaitPump(void);
int Melee360OriginalRuntimeBoot(void){
 if(!Melee360GObjRuntimeInit())return 0;
 {FILE* match=fopen("game:\\original-match.flag","rb");if(match){StartMeleeData data;int frame;fclose(match);lbDvd_80018F68();lbArq_80014D2C();Melee360FightPrepare();data=*Melee360FightStartData();data.players[0].slot_type=Gm_PKind_Cpu;data.players[0].cpu_level=9;HSD_SisLib_803A6048(0xC000);OSReport("Original match: entering gm_Scene_Vs_OnEnter Mario CPU vs Link CPU Battlefield\n");{FILE* hide=fopen("game:\\hide-bot-render.flag","rb");hideBotRender=hide!=0;if(hide)fclose(hide);if(hideBotRender)OSReport("Render diagnostic: CPU fighter drawing disabled; stage and original simulation active\n");}{FILE* hide=fopen("game:\\hide-bot-shadows.flag","rb");hideBotShadows=hide!=0;if(hide)fclose(hide);if(hideBotShadows)OSReport("Render diagnostic: CPU fighter shadow objects suppressed during render only\n");}gm_Scene_Vs_OnEnter(&data);OSReport("Original match: scene entered\n");return 1;}}
 OSReport("Bootstrap Fighter: entering original Player_InitAllPlayers\n");Player_InitAllPlayers();
 OSReport("Bootstrap Fighter: entering original Player_80036DA4/Fighter_FirstInitialize\n");lbDvd_80018F68();Player_80036DA4();
 OSReport("Bootstrap Fighter: original players and Fighter pools initialized; no Fighter created\n");{FILE* f=fopen("game:\\fighter-create.flag","rb");if(f){struct plAllocInfo input;Fighter_GObj* mario;fclose(f);memset(&input,0,sizeof(input));input.internal_id=Ft_Kind_Mario;input.slot=0;
Player_SetPlayerCharacter(0,CKind_Mario);Player_SetSlottype(0,Gm_PKind_Human);Player_SetCostumeId(0,0);Player_SetPadPort(0,0);Player_SetStocks(0,3);Player_SetModelScale(0,1);Player_SetAttackRatio(0,1);Player_SetDefenseRatio(0,1);Player_SetFacingDirection(0,1);
OSReport("Bootstrap match: entering original item common and Camera_Init\n");it_8027870C(0);Camera_Init(8);lbArq_80014D2C();OSReport("Bootstrap match: item common and camera subjects initialized\n");
OSReport("Bootstrap Fighter: entering original Mario Fighter_Create\n");mario=Fighter_Create(&input);if(!mario||!mario->user_data)return 0;OSReport("Bootstrap Fighter: original Mario Fighter_Create returned a valid GObj\n");}}return 1;
}

/* Original scheduler and VS controller; no substitute fighter/CPU/collision logic. */
static unsigned matchFrame;
static void diagnosticHiddenBot(HSD_GObj* obj,intptr_t pass){(void)obj;(void)pass;}
int Melee360OriginalMatchFrame(void){
 HSD_GObj* obj;int fighters=0;
 Melee360LoadWaitPump();lbAudioAx_80027DF8();HSD_GObj_RunProcs();gm_Scene_Vs_OnFrame();
 for(obj=HSD_GObjPLinkHead[8];obj;obj=obj->next){Fighter* fp=(Fighter*)obj->user_data;
  if(!fp||!_finite(fp->cur_pos.x)||!_finite(fp->cur_pos.y)||!_finite(fp->dmg.x1830_percent))return 0;
  ++fighters;
  if(!(matchFrame%60))OSReport("Original CPU: frame=%u slot=%d kind=%d ms=%d pos=(%.3f,%.3f) air=%d input=%x enabled=%d damage=%.2f stocks=%d\n",matchFrame,fp->player_idx,fp->kind,fp->motion_id,fp->cur_pos.x,fp->cur_pos.y,fp->ground_or_air,fp->input.held_buttons[0],!fp->input_disabled,fp->dmg.x1830_percent,Player_GetStocks(fp->player_idx));
 }
 if(fighters!=2)return 0;
 if(++matchFrame==900)OSReport("Original match: 900 scheduler frames completed\n");return 1;
}
const char* Melee360OriginalMatchStatus(void){
 static char status[256];unsigned used;HSD_GObj* obj;
 used=(unsigned)sprintf(status,"Battlefield: Mario CPU vs Link CPU\nFrame %u - HSD/render originais",matchFrame);
 for(obj=HSD_GObjPLinkHead[8];obj&&used<160;obj=obj->next){Fighter* fp=(Fighter*)obj->user_data;used+=(unsigned)sprintf(status+used,"\nP%d: %.1f%% stocks=%d X=%.1f Y=%.1f state=%d",fp->player_idx+1,fp->dmg.x1830_percent,Player_GetStocks(fp->player_idx),fp->cur_pos.x,fp->cur_pos.y,fp->motion_id);}
 return status;
}


int Melee360OriginalMatchRender(void){
 static unsigned frames;HSD_GObj* hidden[6];GObj_RenderFunc callbacks[6];int shadowSuppression[6];HSD_GObj* obj;int count=0,i;
 /* x221E_b5 excludes the fighter from the original shadow object list.
  * Keep this diagnostic bit scoped to graphics, restoring it before logic. */
 if(hideBotRender||hideBotShadows)for(obj=HSD_GObjPLinkHead[8];obj;obj=obj->next){Fighter* fp=(Fighter*)obj->user_data;if(fp&&Player_GetPlayerSlotType(fp->player_idx)==Gm_PKind_Cpu){if(count>=6){for(i=0;i<count;++i){hidden[i]->render_cb=callbacks[i];((Fighter*)hidden[i]->user_data)->x221E_b5=shadowSuppression[i];}return 0;}hidden[count]=obj;callbacks[count]=obj->render_cb;shadowSuppression[count++]=fp->x221E_b5;if(hideBotRender)obj->render_cb=diagnosticHiddenBot;if(hideBotShadows)fp->x221E_b5=1;}}
 if(!frames)OSReport("Original match render: entering HSD screen/GObj camera passes\n");
 HSD_StartRender(HSD_RP_SCREEN);HSD_GObj_80390FC0();HSD_Init_803755A8();
 for(i=0;i<count;++i){hidden[i]->render_cb=callbacks[i];((Fighter*)hidden[i]->user_data)->x221E_b5=shadowSuppression[i];}
 if(hideBotRender&&frames==0)OSReport("Render diagnostic: skipped %d CPU fighter callbacks; originals restored after camera passes\n",count);
 if(hideBotShadows&&frames==0)OSReport("Render diagnostic: restored %d CPU shadow exclusion bits after camera passes\n",count);
 if(++frames==1)OSReport("Original match render: first original camera passes returned\n");return 1;
}
