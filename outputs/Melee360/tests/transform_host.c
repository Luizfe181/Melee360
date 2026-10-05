#include <dolphin/gx/GXTransform.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void __assert(const char* f,unsigned int l,const char* c){fprintf(stderr,"%s:%u %s",f,l,c);exit(2);}
int Melee360GXTransformPosition(const float*,float*);
int Melee360GXTransformNormal(u32,const float*,float*);
int Melee360GXTransformTexcoord(u32,const float*,float*);
void GXGetProjectionv(float*);
GXBool __GXinBegin=GX_FALSE;
int Melee360GXTransformPositionSlot(u32,const float*,float*);
int Melee360GXTransformEyePosition(u32,const float*,float*);
int Melee360GXTransformPositionAndEye(u32,const float*,float*,float*);
static int sharedEyeCases(void){unsigned slot,type,test,r,c;unsigned cases=0;
 for(type=0;type<2;++type)for(slot=0;slot<10;++slot){
  float m[3][4],p[4][4]={{1.25f,0,.125f,-.25f},{0,.75f,-.25f,.5f},{0,0,-.125f,-1.125f},{0,0,-1,0}};
  for(r=0;r<3;++r)for(c=0;c<4;++c)m[r][c]=((int)(slot+1)*(int)(r+2)-(int)c*3)/8.f;
  GXLoadPosMtxImm(m,slot*3);GXSetProjection(p,(GXProjectionType)type);
  for(test=0;test<64;++test){float in[3]={((int)test-31)/7.f,((int)(test%9)-4)/3.f,-((int)test+1)/11.f},oldClip[4],oldEye[3],newClip[4],newEye[3];
   if(!Melee360GXTransformPositionSlot(slot,in,oldClip)||!Melee360GXTransformEyePosition(slot,in,oldEye)||!Melee360GXTransformPositionAndEye(slot,in,newClip,newEye)||memcmp(oldClip,newClip,sizeof(oldClip))||memcmp(oldEye,newEye,sizeof(oldEye)))return 0;
   ++cases;
  }
 }
 {float in[3]={0},clip[4],eye[3];if(Melee360GXTransformPositionAndEye(10,in,clip,eye)||Melee360GXTransformPositionAndEye(0,0,clip,eye)||Melee360GXTransformPositionAndEye(0,in,0,eye)||Melee360GXTransformPositionAndEye(0,in,clip,0))return 0;}
 printf("GX shared eye: %u exact clip/eye comparisons, ten slots and two projections passed\n",cases);return 1;
}
int main(void){float m[3][4]={{2,0,0,1},{0,3,0,2},{0,0,1,-5}},p[4][4]={{1,0,0,0},{0,1,0,0},{0,0,-.125f,-1.125f},{0,0,-1,0}},in[3]={1,1,0},out[4],saved[7];
GXLoadPosMtxImm(m,27);GXSetCurrentMtx(27);GXSetProjection(p,GX_PERSPECTIVE);GXGetProjectionv(saved);
if(saved[0]!=0||saved[5]!=-.125f||saved[6]!=-1.125f||!Melee360GXTransformPosition(in,out)||out[0]!=3||out[1]!=5||out[2]!=4.5f||out[3]!=5)return 1;
GXLoadNrmMtxImm(m,27);if(!Melee360GXTransformNormal(27,in,out)||out[0]!=2||out[1]!=3||out[2]!=0)return 2;
GXLoadTexMtxImm(m,57,GX_MTX2x4);if(!Melee360GXTransformTexcoord(57,in,out)||out[0]!=3||out[1]!=5||out[2]!=1)return 3;
GXSetProjection(p,GX_ORTHOGRAPHIC);if(!Melee360GXTransformPosition(in,out)||out[3]!=1)return 4;
/* Original MTXFrustum coefficients: near 1, far 9. Xbox z must map to 0..w. */
{float identity[3][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0}};float eye[3]={0,0,-1};
GXLoadPosMtxImm(identity,0);GXSetCurrentMtx(0);GXSetProjection(p,GX_PERSPECTIVE);
if(!Melee360GXTransformPosition(eye,out)||out[2]!=0||out[3]!=1)return 5;
eye[2]=-9;if(!Melee360GXTransformPosition(eye,out)||out[2]!=9||out[3]!=9)return 6;
p[2][2]=-.125f;p[2][3]=-1.125f;GXSetProjection(p,GX_ORTHOGRAPHIC);
eye[2]=-1;if(!Melee360GXTransformPosition(eye,out)||out[2]!=0||out[3]!=1)return 7;
eye[2]=-9;if(!Melee360GXTransformPosition(eye,out)||out[2]!=1||out[3]!=1)return 8;}
if(!sharedEyeCases())return 9;
puts("GX transform: position/normal/texture banks, projection packing and clip-depth conversion passed");return 0;}
