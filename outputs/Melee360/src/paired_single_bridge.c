/* Xenon has no Gekko paired-single instructions. Dispatch to the original C
 * implementation; arithmetic behavior is tested, bit identity is not claimed. */
#include <dolphin/mtx.h>
void PSMTXIdentity(Mtx m){C_MTXIdentity(m);}
void PSMTXCopy(Mtx a,Mtx b){C_MTXCopy(a,b);}
void PSMTXConcat(Mtx a,Mtx b,Mtx out){C_MTXConcat(a,b,out);}
void PSMTXTranspose(Mtx a,Mtx b){C_MTXTranspose(a,b);}
u32 PSMTXInverse(Mtx a,Mtx b){return C_MTXInverse(a,b);}
void PSMTXScale(Mtx m,f32 x,f32 y,f32 z){C_MTXScale(m,x,y,z);}
void PSMTXQuat(Mtx m,Quaternion* q){C_MTXQuat(m,q);}
void PSMTXRotAxisRad(Mtx m,Vec* axis,f32 angle){C_MTXRotAxisRad(m,axis,angle);}
void PSMTXTrans(Mtx m,f32 x,f32 y,f32 z){C_MTXIdentity(m);m[0][3]=x;m[1][3]=y;m[2][3]=z;}
#undef MTXTrans
void MTXTrans(Mtx m,f32 x,f32 y,f32 z){PSMTXTrans(m,x,y,z);}
void PSMTXMultVec(Mtx m,Vec* a,Vec* b){C_MTXMultVec(m,a,b);}
void PSMTXMultVecSR(Mtx m,Vec* a,Vec* b){C_MTXMultVecSR(m,a,b);}
void PSVECAdd(Vec* a,Vec* b,Vec* c){C_VECAdd(a,b,c);}
void PSVECSubtract(Vec* a,Vec* b,Vec* c){C_VECSubtract(a,b,c);}
void PSVECScale(Vec* a,Vec* b,f32 k){C_VECScale(a,b,k);}
void PSVECNormalize(Vec* a,Vec* b){C_VECNormalize(a,b);}
void PSVECCrossProduct(Vec* a,Vec* b,Vec* c){C_VECCrossProduct(a,b,c);}
f32 PSVECMag(Vec* a){return C_VECMag(a);}
f32 PSVECDotProduct(Vec* a,Vec* b){return C_VECDotProduct(a,b);}
