#define LINT 1
#include "../compat/gameplay_boundary.h"
#include "runtime_archive.h"
#include <melee/ft/fighter.h>
#include <melee/ft/types.h>
#include <melee/mp/types.h>
#include <sysdolphin/baselib/jobj.h>
#include <float.h>
#include <stdio.h>
static char report[256];
const char* Melee360RuntimeAssetsStatus(void){return report;}
static int inside(HSD_Archive* a,const void* p,unsigned int bytes){unsigned int address=(unsigned int)p,base=(unsigned int)a->data;return p&&address>=base&&address-base<=a->header.data_size&&bytes<=a->header.data_size-(address-base);}
int Melee360RuntimeAssetsProbe(void){HSD_Archive *common,*mario,*costume,*stage;struct ftLoadCommonData* co;struct ftData* mr;HSD_Joint* model;MapCollData* collision;int i;unsigned int endian=0x01020304;
 sprintf_s(report,sizeof(report),"Native original archives: initialization FAILED\n");if(((unsigned char*)&endian)[0]!=1)return 0;
 if(!Melee360RuntimeArchiveLoad("PlCo.dat",&common)||!Melee360RuntimeArchiveLoad("PlMr.dat",&mario)||!Melee360RuntimeArchiveLoad("PlMrNr.dat",&costume)||!Melee360RuntimeArchiveLoad("GrNBa.dat",&stage))return 0;
 co=HSD_ArchiveGetPublicAddress(common,"ftLoadCommonData");mr=HSD_ArchiveGetPublicAddress(mario,"ftDataMario");model=HSD_ArchiveGetPublicAddress(costume,"PlyMario5K_Share_joint");collision=HSD_ArchiveGetPublicAddress(stage,"coll_data");
 if(!inside(common,co,sizeof(*co))||!inside(common,co->common,sizeof(*co->common))||!inside(mario,mr,sizeof(*mr))||!inside(mario,mr->x0,sizeof(*mr->x0))||!inside(costume,model,sizeof(*model))||!inside(costume,model->child,sizeof(*model))||!inside(stage,collision,sizeof(*collision)))return 0;
 if(!_finite(mr->x0->gravity)||mr->x0->gravity<=0||!_finite(mr->x0->walk_max_vel)||mr->x0->walk_max_vel<=0||collision->vert_count<=0||collision->vert_count>4096||collision->line_count<=0||collision->line_count>4096||!inside(stage,collision->verts,collision->vert_count*sizeof(*collision->verts))||!inside(stage,collision->lines,collision->line_count*sizeof(*collision->lines)))return 0;
 for(i=0;i<collision->vert_count;++i)if(!_finite(collision->verts[i].x)||!_finite(collision->verts[i].y))return 0;for(i=0;i<collision->line_count;++i)if(collision->lines[i].v0_idx>=collision->vert_count||collision->lines[i].v1_idx>=collision->vert_count)return 0;
 sprintf_s(report,sizeof(report),"Native original archives: PlCo/Mario/costume/Battlefield relocated; gravity=%.6f walk=%.6f vertices=%d lines=%d; no Fighter created\n",mr->x0->gravity,mr->x0->walk_max_vel,collision->vert_count,collision->line_count);return 1;
}
