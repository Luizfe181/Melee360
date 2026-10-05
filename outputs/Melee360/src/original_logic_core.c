#define LINT 1
#include "../compat/gameplay_boundary.h"
#include <melee/ft/types.h>
#include <melee/mp/types.h>
#include <string.h>
#include <float.h>
#include "original_logic_core.h"
#include <generated/original_logic_core.inc>

// Diagnostic point sweep, NOT the Fighter ECB solver. Original directed
// intersection predicate selects the earliest crossed line in the given group.
int Melee360SweepMapPoint(const MapCollData* map,int group,float x0,float y0,float x1,float y1,float* outX,float* outY){
    int i,best=-1,start,count;float distance=FLT_MAX,dx=x1-x0,dy=y1-y0,bestX=0,bestY=0;
    if(!map||!outX||!outY||!map->verts||!map->lines||group<0||group>=MapLineGroup_Dynamic||map->vert_count<=0||map->line_count<=0||!_finite(x0)||!_finite(y0)||!_finite(x1)||!_finite(y1))return -1;
    start=map->ranges[group].start;count=map->ranges[group].count;if(start<0||count<0||start>map->line_count||count>map->line_count-start)return -1;
    for(i=start;i<start+count;++i){MapLine* line=&map->lines[i];Vec2 a,b;float x,y,d;
        if(line->v0_idx>=map->vert_count||line->v1_idx>=map->vert_count)return -1;a=map->verts[line->v0_idx];b=map->verts[line->v1_idx];if(!_finite(a.x)||!_finite(a.y)||!_finite(b.x)||!_finite(b.y))return -1;
        if(M360_mpLineIntersection(a.x,a.y,b.x,b.y,x0,y0,x1,y1,&x,&y)){d=(x-x0)*dx+(y-y0)*dy;if(d<distance){distance=d;best=i;bestX=x;bestY=y;}}
    }if(best>=0){*outX=bestX;*outY=bestY;}return best;
}

int Melee360OriginalLogicProbe(void){
    static Fighter fp;float x=99,y=99;int i;Vec2 verts[4]={{-10,0},{10,0},{-10,5},{10,5}};MapLine lines[2]={{0}};MapCollData map={0};
    if(!M360_mpLineIntersection(-10,0,10,0,0,2,0,-2,&x,&y)||x!=0||y!=0)return 0;
    x=y=99;if(M360_mpLineIntersection(-10,0,10,0,0,-2,0,2,&x,&y)||x!=99||y!=99)return 0;
    if(M360_mpLineIntersection(-10,0,10,0,-3,0,3,0,&x,&y))return 0;
    if(!M360_mpLineIntersectionH(&x,&y,-10,0,10,1,2,1,-2)||x!=1||y!=0)return 0;
    if(!M360_mpLineIntersectionV(&x,&y,0,-10,10,-2,1,2,1)||x!=0||y!=1)return 0;
    map.verts=verts;map.vert_count=4;map.lines=lines;map.line_count=2;map.ranges[0].start=0;map.ranges[0].count=2;lines[0].v0_idx=0;lines[0].v1_idx=1;lines[1].v0_idx=2;lines[1].v1_idx=3;
    if(Melee360SweepMapPoint(&map,0,0,10,0,-10,&x,&y)!=1||y!=5)return 0;
    if(Melee360SweepMapPoint(&map,0,20,10,20,-10,&x,&y)!=-1)return 0;
    memset(&fp,0,sizeof(fp));fp.co_attrs.gravity=.1f;fp.co_attrs.terminal_velocity=2;fp.co_attrs.fast_fall_velocity=3;fp.co_attrs.air_drift_max=1;fp.co_attrs.max_jumps=2;
    for(i=0;i<100;++i)M360_ftCommon_FallBasic(&fp);if(fp.self_vel.y!=-2)return 0;
    M360_ftCommon_FallFast(&fp);if(fp.self_vel.y!=-3)return 0;
    M360_ftCommon_Ascend(&fp,10,4);if(fp.self_vel.y!=4)return 0;
    fp.self_vel.x=2;M360_ftCommon_ClampAirDrift(&fp);if(fp.self_vel.x!=1)return 0;
    fp.self_vel.x=-.05f;M360_ftCommon_CalcSelfAccel_Deaccel(&fp,.1f);if(fp.x74_self_accel.x!=.05f)return 0;
    fp.co_attrs.air_max_horizontal_velocity=2;fp.co_attrs.air_drift_stick_mul=.1f;fp.co_attrs.aerial_drift_base=.05f;fp.co_attrs.aerial_friction=.05f;fp.input.lstick[0].x=1;fp.self_vel.x=0;
    M360_ftCommon_CalcSelfAccel_DriftFrom(&fp,0);if(fp.x74_self_accel.x<=0)return 0;
    fp.self_vel.x=1;M360_ftCommon_CalcSelfAccel_DriftSimple(&fp,.2f,.1f,1);if(fp.x74_self_accel.x!=0)return 0;
    fp.input.lstick[0].x=-1;fp.self_vel.x=0;M360_ftCommon_CalcSelfAccel_DriftSimple_NoFriction(&fp,.2f,.1f,1);if(fp.x74_self_accel.x!=-.1f)return 0;
    x=y=99;lines[1].v0_idx=99;if(Melee360SweepMapPoint(&map,0,0,10,0,-10,&x,&y)!=-1||x!=99||y!=99)return 0;
    M360_ftCommon_UseAllJumps(&fp);if(fp.x1968_jumpsUsed!=2)return 0;
    fp.ecb_lock=10;fp.coll_data.x130_flags=CollData_X130_Locked;M360_ftCommon_UnlockECB(&fp);if(fp.ecb_lock||fp.coll_data.x130_flags&CollData_X130_Locked)return 0;
    return 1;
}
