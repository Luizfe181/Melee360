#include <dolphin/mtx.h>
#include <dolphin/pad.h>
#include <dolphin/gx.h>
#include <math.h>
#include <string.h>
static int near_value(float a,float b){return fabs((double)a-b)<0.00002;}
int Melee360MathProbe(void) {
    Mtx a,b,c,inv,id,view,rot;
    Mtx44 projection;Mtx light;
    PADStatus pads[4];float pm[7]={1,1,0,1,0,1,0},vp[6]={0,0,640,480,0,1},sx,sy,sz;
    Vec input={1,2,3},out,eye={0,0,10},up={0,1,0},target={0,0,0};
    Vec x={1,0,0},y={0,1,0},v={3,0,4};
    Quaternion q={0,0,0,1};
    int i,j,ok=1;
    PSMTXScale(a,2,3,4);PSMTXTrans(b,5,6,7);PSMTXConcat(a,b,c);
    PSMTXMultVec(c,&input,&out);
    ok=ok&&near_value(out.x,12)&&near_value(out.y,24)&&near_value(out.z,40);
    PSMTXConcat(a,b,a);
    for(i=0;i<3;i++)for(j=0;j<4;j++)ok=ok&&near_value(a[i][j],c[i][j]);
    ok=ok&&C_MTXInverse(c,inv)!=0;C_MTXConcat(c,inv,id);
    for(i=0;i<3;i++)for(j=0;j<4;j++)ok=ok&&near_value(id[i][j],i==j?1.0f:0.0f);
    C_MTXLookAt(view,&eye,&up,&target);PSMTXMultVec(view,&eye,&out);
    ok=ok&&near_value(out.x,0)&&near_value(out.y,0)&&near_value(out.z,0);
    PSVECCrossProduct(&x,&y,&out);ok=ok&&near_value(out.z,1);
    PSVECNormalize(&v,&v);ok=ok&&near_value(v.x,.6f)&&near_value(v.z,.8f);
    PSMTXRotAxisRad(rot,&y,1.5707963267948966f);PSMTXMultVec(rot,&x,&out);
    ok=ok&&near_value(out.x,0)&&near_value(out.z,-1);
    PSMTXQuat(rot,&q);
    for(i=0;i<3;i++)for(j=0;j<4;j++)ok=ok&&near_value(rot[i][j],i==j?1.0f:0.0f);
    MTXPerspective(projection,90,1,1,10);ok=ok&&near_value(projection[0][0],1)&&near_value(projection[1][1],1)&&near_value(projection[3][2],-1);
    MTXFrustum(projection,1,-1,-1,1,1,10);ok=ok&&near_value(projection[0][0],1)&&near_value(projection[3][2],-1);
    MTXOrtho(projection,1,-1,-1,1,1,10);ok=ok&&near_value(projection[0][0],1)&&near_value(projection[3][3],1);
    MTXLightPerspective(light,90,1,.5f,.5f,.5f,.5f);ok=ok&&near_value(light[0][0],.5f)&&near_value(light[0][2],-.5f)&&near_value(light[2][2],-1);
    MTXLightFrustum(light,1,-1,-1,1,1,.5f,.5f,.5f,.5f);ok=ok&&near_value(light[0][0],.5f)&&near_value(light[2][2],-1);
    MTXLightOrtho(light,1,-1,-1,1,.5f,.5f,.5f,.5f);ok=ok&&near_value(light[0][3],.5f)&&near_value(light[2][3],1);
    MTXRotRad(rot,'y',1.5707963267948966f);PSMTXMultVec(rot,&x,&out);ok=ok&&near_value(out.z,-1);
    ok=ok&&PSMTXInverse(c,inv)!=0;
    PSMTXIdentity(id);GXProject(0,0,0,id,pm,vp,&sx,&sy,&sz);ok=ok&&near_value(sx,320)&&near_value(sy,240);
    memset(pads,0,sizeof(pads));pads[0].stickX=127;pads[0].substickY=-127;pads[0].triggerLeft=255;pads[1].stickX=15;pads[2].err=PAD_ERR_NO_CONTROLLER;pads[2].stickX=100;
    PADClamp(pads);ok=ok&&pads[0].stickX==72&&pads[0].substickY==-59&&pads[0].triggerLeft==150&&pads[1].stickX==0&&pads[2].stickX==100;
    return ok;
}
