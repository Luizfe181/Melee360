#include <dolphin/gx/GXTransform.h>
#include <math.h>
#include <string.h>
void __assert(const char*,unsigned int,const char*);
static float position[10][3][4],normal[10][3][3],texture[10][3][4],projection[7];
static unsigned char positionValid[10],normalValid[10],textureValid[10];
static u32 current;
static float postTexture[20][3][4];static unsigned char postValid[20];
static void require(int condition){if(!condition)__assert(__FILE__,__LINE__,"invalid GX transformation state");}
static u32 slot(u32 id){require(id<=27&&id%3==0);return id/3;}
static void finiteValues(const float* values,unsigned int count){unsigned int i;require(values!=0);for(i=0;i<count;++i)require(_finite(values[i]));}
void GXLoadPosMtxImm(f32 matrix[3][4],u32 id){u32 s=slot(id);finiteValues(&matrix[0][0],12);memcpy(position[s],matrix,48);positionValid[s]=1;}
void GXLoadNrmMtxImm(f32 matrix[3][4],u32 id){u32 s=slot(id),r;finiteValues(&matrix[0][0],12);for(r=0;r<3;++r)memcpy(normal[s][r],matrix[r],12);normalValid[s]=1;}
void GXLoadTexMtxImm(f32 matrix[][4],u32 id,GXTexMtxType type){u32 s;require(((id>=30&&id<=57&&(id-30)%3==0)||(id>=64&&id<=121&&(id-64)%3==0&&type==GX_MTX3x4))&&(type==GX_MTX2x4||type==GX_MTX3x4));if(id>=64&&id<=121&&(id-64)%3==0){s=(id-64)/3;finiteValues(&matrix[0][0],12);memcpy(postTexture[s],matrix,48);postValid[s]=1;return;}s=(id-30)/3;finiteValues(&matrix[0][0],type==GX_MTX2x4?8:12);memset(texture[s],0,48);memcpy(texture[s],matrix,type==GX_MTX2x4?32:48);if(type==GX_MTX2x4)texture[s][2][3]=1;textureValid[s]=1;}
void GXSetCurrentMtx(u32 id){current=slot(id);}
void GXSetProjection(f32 matrix[4][4],GXProjectionType type){finiteValues(&matrix[0][0],16);require(type==GX_PERSPECTIVE||type==GX_ORTHOGRAPHIC);projection[0]=(float)type;projection[1]=matrix[0][0];projection[2]=matrix[0][type==GX_PERSPECTIVE?2:3];projection[3]=matrix[1][1];projection[4]=matrix[1][type==GX_PERSPECTIVE?2:3];projection[5]=matrix[2][2];projection[6]=matrix[2][3];}
void GXGetProjectionv(f32* values){require(values!=0);memcpy(values,projection,sizeof(projection));}
void GXSetProjectionv(f32* values){extern GXBool __GXinBegin;require(!__GXinBegin);finiteValues(values,7);require(values[0]==GX_PERSPECTIVE||values[0]==GX_ORTHOGRAPHIC);memcpy(projection,values,sizeof(projection));}
/* Consumer for the forthcoming GX vertex submission path. GC clip depth is
 * negative; translate it to the Xbox shader's zero-to-one clip convention. */
int Melee360GXTransformPositionSlot(u32 selected,const float* input,float* output){float eye[3];u32 r,c;if(selected>=10||!input||!output||!positionValid[selected])return 0;
for(r=0;r<3;++r){eye[r]=position[selected][r][3];for(c=0;c<3;++c)eye[r]+=position[selected][r][c]*input[c];}
output[0]=eye[0]*projection[1]+(projection[0]==0?eye[2]:1)*projection[2];output[1]=eye[1]*projection[3]+(projection[0]==0?eye[2]:1)*projection[4];output[3]=projection[0]==0?-eye[2]:1;output[2]=output[3]+eye[2]*projection[5]+projection[6];return 1;}
/* Shared eye-space result for projection and lighting. Keep arithmetic order
 * identical to the two reference consumers; no cross-vertex/state cache. */
int Melee360GXTransformPositionAndEye(u32 selected,const float* input,float* output,float* eye){u32 r,c;if(selected>=10||!input||!output||!eye||!positionValid[selected])return 0;
for(r=0;r<3;++r){eye[r]=position[selected][r][3];for(c=0;c<3;++c)eye[r]+=position[selected][r][c]*input[c];}
output[0]=eye[0]*projection[1]+(projection[0]==0?eye[2]:1)*projection[2];output[1]=eye[1]*projection[3]+(projection[0]==0?eye[2]:1)*projection[4];output[3]=projection[0]==0?-eye[2]:1;output[2]=output[3]+eye[2]*projection[5]+projection[6];return 1;}
int Melee360GXTransformNormal(u32 id,const float* input,float* output){u32 r,c,s=slot(id);if(!input||!output||!normalValid[s])return 0;for(r=0;r<3;++r){output[r]=0;for(c=0;c<3;++c)output[r]+=normal[s][r][c]*input[c];}return 1;}
int Melee360GXTransformEyePosition(u32,const float*,float*);
int Melee360GXTransformTexcoord(u32 id,const float* input,float* output){u32 s,r,c;if(id<=27&&id%3==0)return Melee360GXTransformEyePosition(id/3,input,output);require(id>=30&&id<=57&&(id-30)%3==0);s=(id-30)/3;if(!input||!output||!textureValid[s])return 0;for(r=0;r<3;++r){output[r]=texture[s][r][3];for(c=0;c<3;++c)output[r]+=texture[s][r][c]*input[c];}return 1;}

int Melee360GXTransformPosition(const float* input,float* output){return Melee360GXTransformPositionSlot(current,input,output);}
int Melee360GXTransformEyePosition(u32 selected,const float* input,float* out){u32 r,c;if(selected>=10||!input||!out||!positionValid[selected])return 0;for(r=0;r<3;++r){out[r]=position[selected][r][3];for(c=0;c<3;++c)out[r]+=position[selected][r][c]*input[c];}return 1;}
u32 Melee360GXCurrentMatrix(void){return current*3;}

int Melee360GXTransformPostTexcoord(u32 id,const float* input,float* output){u32 s,r,c;if(id<64||id>121||(id-64)%3||!input||!output)return 0;s=(id-64)/3;if(!postValid[s])return 0;for(r=0;r<3;++r){output[r]=postTexture[s][r][3];for(c=0;c<3;++c)output[r]+=postTexture[s][r][c]*input[c];}return 1;}
