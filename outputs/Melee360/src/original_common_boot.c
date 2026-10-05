#include "../compat/gameplay_boundary.h"
#include <melee/pl/player.h>
#include <melee/pl/types.h>
#include <melee/ft/fighter.h>
#include <melee/ft/types.h>
#include <melee/lb/lbarchive.h>
#include <sysdolphin/baselib/archive.h>
#include <math.h>
#include <sysdolphin/baselib/debug.h>
char str_PdPmdat_start_of_data[] = "PdPm.dat";
char str_plLoadCommonData[] = "plLoadCommonData";
pl_804D6470_t* pl_804D6470;
struct Fighter_804D64FC_t* Fighter_804D64FC = NULL;
CrowdConfig* gCrowdConfig = NULL;
HSD_Joint* Fighter_804D6504 = NULL;
u8* Fighter_804D6508 = NULL;
u8* Fighter_804D650C = NULL;
UNK_T Fighter_804D6510 = NULL;
HSD_Joint* Fighter_804D6514 = NULL;
struct Fighter_804D6518_t* Fighter_804D6518 = NULL;
struct Fighter_804D651C_t* Fighter_804D651C = NULL;
struct Fighter_804D6520_t* Fighter_804D6520 = NULL;
struct Fighter_804D6524_t* Fighter_804D6524 = NULL;
struct Fighter_ShakeTable_t* Fighter_SmashChargeShakeTable = NULL;
struct Fighter_ShakeTable_t* Fighter_GrabMashShake = NULL;
Vec2** Fighter_804D6530 = NULL;
UNK_T Fighter_804D6534 = NULL;
struct Fighter_804D653C_t* Fighter_804D6538 = NULL;
struct Fighter_804D653C_t* Fighter_804D653C = NULL;
struct Fighter_804D6540_t** Fighter_804D6540 = NULL;
FighterPartsTable** ftPartsTable = NULL;
float* Fighter_804D6548 = NULL;
float (*Fighter_804D654C)[5] = NULL;
ftCo_ItemThrowAttrs* Fighter_804D6550 = NULL;
ftCommonData* p_ftCommonData;

void Player_80036DD8(void)
{
    struct plLoadCommonData* data;

    lbArchive_LoadSymbols(str_PdPmdat_start_of_data, &data,
                          str_plLoadCommonData, 0);
    pl_804D6470 = data->x0;
}
void Fighter_LoadCommonData(void)
{
    struct ftLoadCommonData* data;
    lbArchive_LoadSymbols("PlCo.dat", &data, "ftLoadCommonData", 0);

    // copy 23 4-byte chunks from pData to p_ftCommonData in reverse order,
    // equivalent to this: for(i=0; i<23; i++)
    //   (&Fighter_804D64FC)[23-1-i] = pData[i];
    // loop unrolling doesn't work (only up to 8 elements)
    p_ftCommonData = data->common; // p_ftCommonData
    Fighter_804D6550 = data->item_throw;
    Fighter_804D654C = data->x8;
    Fighter_804D6548 = data->xC;
    ftPartsTable = data->parts_table;
    Fighter_804D6540 = data->x14;
    Fighter_804D653C = data->x18;
    Fighter_804D6538 = data->x1C;
    Fighter_804D6534 = data->x20;
    Fighter_804D6530 = data->x24;
    Fighter_GrabMashShake = data->grab_mash_shake;
    Fighter_SmashChargeShakeTable = data->smash_charge_shake;
    Fighter_804D6524 = data->x30;
    Fighter_804D6520 = data->x34;
    Fighter_804D651C = data->x38;
    Fighter_804D6518 = data->x3C;
    Fighter_804D6514 = data->x40;
    Fighter_804D6510 = data->x44;
    Fighter_804D650C = data->x48;
    Fighter_804D6508 = data->x4C;
    Fighter_804D6504 = data->x50;
    gCrowdConfig = data->crowd_config;
    Fighter_804D64FC = data->x58;
}
int Melee360OriginalCommonBoot(void){Player_80036DD8();Fighter_LoadCommonData();return pl_804D6470&&p_ftCommonData&&ftPartsTable&&_finite(p_ftCommonData->x260_startShieldHealth)&&p_ftCommonData->x260_startShieldHealth>0;}
