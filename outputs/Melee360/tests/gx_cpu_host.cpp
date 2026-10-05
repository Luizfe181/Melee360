#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
extern "C" void OSReport(const char* f,...){va_list a;va_start(a,f);vprintf(f,a);va_end(a);}
extern "C" int Melee360GXCpuProbe(void);
extern "C" __declspec(noreturn) void __assert(const char* f,unsigned l,const char* c){fprintf(stderr,"%s:%u %s\n",f,l,c);exit(2);}
extern "C" __declspec(noreturn) void OSPanic(const char* file,int line,const char* format,...){va_list args;va_start(args,format);fprintf(stderr,"%s:%d ",file,line);vfprintf(stderr,format,args);va_end(args);exit(2);}
static void* capturedObject;static const void* capturedImage;static unsigned captures;
extern "C" void Melee360GXRegisterTextureImage(void* object,const void* image){capturedObject=object;capturedImage=image;++captures;}
static unsigned paletteCaptures;
static unsigned fogRegisters[11],fogWrites;
extern "C" void Melee360GXWriteFogRegister(unsigned value){unsigned reg=value>>24;if(reg<0xe8||reg>0xf2)exit(3);fogRegisters[reg-0xe8]=value&0xffffff;++fogWrites;}
struct FogColor{unsigned char r,g,b,a;};struct FogTable{unsigned short r[10];};
extern "C" void GXSetFog(int,float,float,float,float,FogColor);
extern "C" void GXSetFogRangeAdj(unsigned char,unsigned short,FogTable*);
extern "C" void Melee360GXRegisterPaletteImage(void* object,const void* image,unsigned format,unsigned entries){if(object&&image==(const void*)0x2000&&format==1&&entries==256)++paletteCaptures;}
int main(){int ok=Melee360GXCpuProbe()&&paletteCaptures==1&&captures==3&&capturedObject&&capturedImage==(const void*)0x3000;
FogColor color={12,34,56,78};GXSetFog(2,2,16,1,64,color);ok=ok&&fogWrites==5&&fogRegisters[10]==0x0c2238&&((fogRegisters[9]>>21)&7)==2;
FogTable table;for(int i=0;i<10;++i)table.r[i]=256;GXSetFogRangeAdj(1,320,&table);ok=ok&&fogWrites==11&&fogRegisters[0]==(662|1024);
for(int i=1;i<=5;++i)ok=ok&&fogRegisters[i]==0x100100;GXSetFogRangeAdj(0,0,0);ok=ok&&fogWrites==12&&fogRegisters[0]==342;
printf("Original GX CPU light/mipmap/fog-register semantics: %s\n",ok?"PASS":"FAIL");return ok?0:1;}

