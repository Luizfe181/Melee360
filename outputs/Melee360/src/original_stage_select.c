#include "training_stage.h"
#include <string.h>
/* Flat SSS nodes bridge the original hit test to archive layout positions.
 * They are not live HSD objects and never enter the full HSD renderer. */
typedef int s32;typedef unsigned int u32;typedef unsigned char u8;typedef float f32;
#include <dolphin/mtx.h>
#define HSD_JObj PortStageNode
#define HSD_GObj PortStageObject
#define HSD_JObjSetFlags PortStageSetFlags
#define HSD_JObjGetTranslation PortStageGetTranslation
#define HSD_JObjSetTranslate PortStageSetTranslation
#define lb_8000B1CC PortStageWorldPosition
typedef struct StageNode{Vec3 position;unsigned int flags;}HSD_JObj;
typedef struct StageObject{HSD_JObj* hsd_obj;}HSD_GObj;
#define JOBJ_HIDDEN 1
static void HSD_JObjSetFlags(HSD_JObj* j,int flags){j->flags|=flags;}
static void HSD_JObjGetTranslation(HSD_JObj* j,Vec3* p){*p=j->position;}
static void HSD_JObjSetTranslate(HSD_JObj* j,const Vec3* p){j->position=*p;}
static void lb_8000B1CC(HSD_JObj* j,void* unused,Vec3* p){(void)unused;*p=j->position;}
static unsigned char mnStageSel_804D6CAF,mnStageSel_804D6CAE;
static signed char mnStageSel_804D6CAC,mnStageSel_804D6CAD;
#define mnStageSel_8025BC08 Melee360OriginalStageKind
#define fn_8025A310 Melee360OriginalStageCursor
#include <generated/original_stage_select.inc>
static HSD_JObj nodes[30],cursor;static HSD_GObj cursorObject;
void Melee360StageInit(void){int i;memset(nodes,0,sizeof(nodes));for(i=0;i<30;++i){mnStageSel_803F06D0[i].x0=&nodes[i];mnStageSel_803F06D0[i].x8=0;}cursor.position.x=cursor.position.y=cursor.position.z=0;cursorObject.hsd_obj=&cursor;mnStageSel_804D6CAF=0;mnStageSel_804D6CAE=30;}
void Melee360StageSetPosition(int i,float x,float y){if(i<0||i>=30)return;nodes[i].position.x=x;nodes[i].position.y=y;mnStageSel_803F06D0[i].x8=2;}
void Melee360StageMove(int x,int y){if(x>100)x=100;if(x< -100)x=-100;if(y>100)y=100;if(y< -100)y=-100;mnStageSel_804D6CAC=(signed char)x;mnStageSel_804D6CAD=(signed char)y;mnStageSel_804D6CAE=30;Melee360OriginalStageCursor(&cursorObject);}
void Melee360StageCursor(float* x,float* y,int* hover){if(x)*x=cursor.position.x;if(y)*y=cursor.position.y;if(hover)*hover=mnStageSel_804D6CAE<30?mnStageSel_804D6CAE:-1;}
int Melee360StageKind(int index){return index>=0&&index<29?Melee360OriginalStageKind(index):-1;}

int Melee360StageTestPlaceAt(int index){if(index<0||index>=30||!mnStageSel_803F06D0[index].x8)return 0;cursor.position=nodes[index].position;Melee360StageMove(0,0);return mnStageSel_804D6CAE==index;}

int Melee360StageFrame(int index){return index>=0&&index<30?mnStageSel_803F06D0[index].x9:-1;}
