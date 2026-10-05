#define LINT 1
#include "../compat/gameplay_boundary.h"
#include <melee/ft/types.h>
#include <melee/mp/types.h>
#include "runtime_archive.h"
#include "original_logic_core.h"
#include <string.h>
#include <float.h>
extern void M360_ftCommon_FallBasic(Fighter*);
extern void M360_ftCommon_ClampAirDrift(Fighter*);
static int inside(HSD_Archive* a,const void* p,unsigned int bytes){unsigned int address=(unsigned int)p,base=(unsigned int)a->data;return p&&address>=base&&address-base<=a->header.data_size&&bytes<=a->header.data_size-(address-base);}
int Melee360NativeLogicProbe(void){
    static Fighter isolated;HSD_Archive *archive,*stage;struct ftData* data;MapCollData* map;int k,i,hits=0;const char* files[2]={"PlMr.dat","PlLk.dat"};const char* roots[2]={"ftDataMario","ftDataLink"};
    // Isolated original physics routines on native attributes. This is not
    // Fighter_Create, AI, movement-state processing, or a match.
    for(k=0;k<2;++k){if(!Melee360RuntimeArchiveLoad(files[k],&archive))return 0;data=HSD_ArchiveGetPublicAddress(archive,roots[k]);if(!inside(archive,data,sizeof(*data))||!inside(archive,data->x0,sizeof(*data->x0)))return 0;
        for(i=0;i<(int)archive->header.nb_extern;++i){u32 at=archive->extern_info[i].offset;if(at!=0xffffffffu&&(at>archive->header.data_size-4||*(u32*)(archive->data+at)!=0))return 0;}
        memset(&isolated,0,sizeof(isolated));isolated.co_attrs=*data->x0;if(!_finite(isolated.co_attrs.gravity)||isolated.co_attrs.gravity<=0||!_finite(isolated.co_attrs.terminal_velocity)||isolated.co_attrs.terminal_velocity<=0||!_finite(isolated.co_attrs.air_drift_max)||isolated.co_attrs.air_drift_max<=0)return 0;
        for(i=0;i<600;++i)M360_ftCommon_FallBasic(&isolated);if(isolated.self_vel.y!=-isolated.co_attrs.terminal_velocity)return 0;isolated.self_vel.x=isolated.co_attrs.air_drift_max*2;M360_ftCommon_ClampAirDrift(&isolated);if(isolated.self_vel.x!=isolated.co_attrs.air_drift_max)return 0;
    }
    if(!Melee360RuntimeArchiveLoad("GrNBa.dat",&stage))return 0;map=HSD_ArchiveGetPublicAddress(stage,"coll_data");if(!inside(stage,map,sizeof(*map))||map->vert_count<=0||map->line_count<=0||!inside(stage,map->verts,map->vert_count*sizeof(*map->verts))||!inside(stage,map->lines,map->line_count*sizeof(*map->lines)))return 0;
    for(i=-60;i<=60;i+=10){float x,y;if(Melee360SweepMapPoint(map,MapLineGroup_Floor,(float)i,200,(float)i,-200,&x,&y)>=0){if(!_finite(x)||!_finite(y))return 0;++hits;}}
    if(!hits)return 0;
    // Exercise every static line group with crossings normal to each line.
    for(k=0;k<4;++k){int start=map->ranges[k].start,count=map->ranges[k].count;if(start<0||count<0||start>map->line_count||count>map->line_count-start)return 0;
        for(i=start;i<start+count;++i){MapLine* line=&map->lines[i];Vec2 a,b;float mx,my,nx,ny,x,y;if(line->v0_idx>=map->vert_count||line->v1_idx>=map->vert_count)return 0;a=map->verts[line->v0_idx];b=map->verts[line->v1_idx];mx=(a.x+b.x)*.5f;my=(a.y+b.y)*.5f;nx=(a.y-b.y)*.1f;ny=(b.x-a.x)*.1f;
            if(Melee360SweepMapPoint(map,k,mx+nx,my+ny,mx-nx,my-ny,&x,&y)<0||!_finite(x)||!_finite(y))return 0;
        }
    }return 1;
}
