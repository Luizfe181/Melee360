#include <dolphin/gx.h>
#include <string.h>
#include <math.h>
static int near_value(float a,float b){return fabs(a-b)<0.0001;}
int Melee360GXCpuProbe(void){
 GXLightObj obj; GXColor in={17,33,65,129},out; float x,y,z,a,b,c; unsigned int i;
 memset(&obj,0,sizeof(obj));
 GXInitLightColor(&obj,in);GXGetLightColor(&obj,&out);if(memcmp(&in,&out,4))return 0;
 GXInitLightPos(&obj,2,-3,4);GXGetLightPos(&obj,&x,&y,&z);if(x!=2||y!=-3||z!=4)return 0;
 GXInitLightDir(&obj,0.25f,-0.5f,1);GXGetLightDir(&obj,&x,&y,&z);if(x!=0.25f||y!=-0.5f||z!=1)return 0;
 GXInitLightAttn(&obj,1,2,3,4,5,6);GXGetLightAttnA(&obj,&a,&b,&c);if(a!=1||b!=2||c!=3)return 0;
 GXGetLightAttnK(&obj,&a,&b,&c);if(a!=4||b!=5||c!=6)return 0;
 GXInitLightSpot(&obj,60,GX_SP_COS);GXGetLightAttnA(&obj,&a,&b,&c);if(!near_value(a,-1)||!near_value(b,2)||c!=0)return 0;
 GXInitLightSpot(&obj,0,GX_SP_COS);GXGetLightAttnA(&obj,&a,&b,&c);if(a!=1||b!=0||c!=0)return 0;
 GXInitLightDistAttn(&obj,10,0.5f,GX_DA_MEDIUM);GXGetLightAttnK(&obj,&a,&b,&c);if(a!=1||!near_value(b,0.05f)||!near_value(c,0.005f))return 0;
 for(i=0;i<3;++i){GXInitLightDistAttn(&obj,8,0.25f,(GXDistAttnFn)(i+1));GXGetLightAttnK(&obj,&a,&b,&c);if(!near_value(a+b*8+c*64,4))return 0;}
 if(GXGetTexBufferSize(8,8,GX_TF_I4,0,0)!=32||GXGetTexBufferSize(9,9,GX_TF_I4,0,0)!=128)return 0;
 if(GXGetTexBufferSize(8,8,GX_TF_RGBA8,0,0)!=256||GXGetTexBufferSize(8,8,GX_TF_RGBA8,1,4)!=448)return 0;
 if(GXGetTexBufferSize(1,1,GX_TF_CMPR,1,8)!=32)return 0;
 {GXTexObj t;memset(&t,0,sizeof(t));t.dummy[2]=63|(31<<10);t.dummy[5]=GX_TF_RGB5A3;
 if(GXGetTexObjWidth(&t)!=64||GXGetTexObjHeight(&t)!=32||GXGetTexObjFmt(&t)!=GX_TF_RGB5A3)return 0;}
 {GXFogAdjTable t;float m[4][4]={{1,0,0,0},{0,1,0,0},{0,0,-1.002f,-2.002f},{0,0,-1,0}};
 GXInitFogAdjTable(&t,640,m);if(t.r[0]!=257||t.r[9]!=362)return 0;for(i=1;i<10;++i)if(t.r[i]<=t.r[i-1])return 0;}
 if(GXNtsc480Prog.fbWidth!=640||GXNtsc480Prog.efbHeight!=480||GXNtsc480IntDf.vfilter[3]!=12||GXNtsc480Int.vfilter[3]!=22)return 0;
 {GXTexObj t;GXTlutObj lut;u32* words=t.dummy;
 GXInitTexObj(&t,(void*)0x1000,64,32,GX_TF_RGB565,GX_REPEAT,GX_CLAMP,1);
 if(GXGetTexObjWidth(&t)!=64||GXGetTexObjHeight(&t)!=32||GXGetTexObjFmt(&t)!=GX_TF_RGB565||words[3]!=128)return 0;
 GXInitTexObjLOD(&t,GX_LIN_MIP_LIN,GX_LINEAR,-1,20,10,1,1,GX_ANISO_2);
 if((words[1]&65535)!=40960||((words[0]>>9)&255)!=127)return 0;
 GXInitTexObjCI(&t,(void*)0x1000,32,32,GX_TF_C8,GX_CLAMP,GX_CLAMP,0,7);
 if(words[6]!=7||GXGetTexObjFmt(&t)!=GX_TF_C8)return 0;
 GXInitTexObjData(&t,(void*)0x3000);if((words[3]&0x1fffff)!=384||words[6]!=7||GXGetTexObjWidth(&t)!=32)return 0;
 memset(&lut,0,sizeof(lut));GXInitTlutObj(&lut,(void*)0x2000,GX_TL_RGB565,256);
 if(lut.dummy[0]!=1024||lut.dummy[1]!=(0x64000000u|256))return 0;}
 return 1;
}

