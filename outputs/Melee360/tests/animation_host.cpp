#include "../src/hsd_animation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
extern "C" {
#include <sysdolphin/baselib/objalloc.h>
void* HSD_ObjAlloc(HSD_ObjAllocData*) {return calloc(1,128);}
void HSD_ObjFree(HSD_ObjAllocData*,void* p) {free(p);}
void HSD_ObjAllocInit(HSD_ObjAllocData*,size_t,u32) {}
__declspec(noreturn) void __assert(const char* f,u32 l,const char* c) {fprintf(stderr,"%s:%u %s\n",f,l,c);exit(90);}
}
static float result;
static void value(void*,unsigned int,float v) {result=v;}
static void put(unsigned char* d,unsigned int v) {d[0]=(unsigned char)(v>>24);d[1]=(unsigned char)(v>>16);d[2]=(unsigned char)(v>>8);d[3]=(unsigned char)v;}
int main() {
    unsigned char d[128]={0};put(d+8,32);put(d+32+8,64);put(d+64+4,11);put(d+64+16,96);d[64+12]=5;
    // Original packed little-endian floats, a linear packet containing two keys.
    d[96]=0x12;float a=2,b=12;memcpy(d+97,&a,4);d[101]=10;memcpy(d+102,&b,4);d[106]=10;
    unsigned int tracks=0;if(!Melee360SampleAObj(d,128,32,5,value,0,&tracks)||result!=7||tracks!=1)return 1;
    if(!Melee360SampleAObj(d,128,32,0,value,0,0)||result!=2)return 2;
    if(!Melee360SampleAObj(d,128,32,10,value,0,0)||result!=12)return 3;
    d[96]=15;if(Melee360SampleAObj(d,128,32,5,value,0,0))return 4;d[96]=0x12;
    put(d+68,40);if(Melee360SampleAObj(d,128,32,5,value,0,0))return 5;put(d+68,11);
    put(d+64,64);if(Melee360SampleAObj(d,128,32,5,value,0,0))return 6;
    puts("Unchanged upstream FObj linear/start/end; malformed opcode/truncated stream/cyclic descriptor checks passed");return 0;
}
