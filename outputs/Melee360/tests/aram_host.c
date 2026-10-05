#include <dolphin/ar.h>
#include <dolphin/os.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Melee360ARAMPump(void);
int OSDisableInterrupts(void){return 1;}int OSRestoreInterrupts(int token){return token;}
void __assert(const char* file,unsigned int line,const char* msg){fprintf(stderr,"%s:%u %s\n",file,line,msg);exit(99);}
static __declspec(align(32)) unsigned char data[64],output[64];
static u32 stack[8];static int count,order[4];
static void done(ARQRequest* r){order[count++]=(int)r->owner;}
int main(void){u32 a,b,size;ARQRequest low,high,read;
    if(ARInit(stack,8)!=0x4000||!ARCheckInit()||ARGetSize()!=16*1024*1024)return 1;
    a=ARAlloc(64);b=ARAlloc(32);if(a!=0x4000||b!=a+64||ARFree(&size)!=b||size!=32)return 2;
    memset(data,0x5a,64);ARQInit();ARQPostRequest(&low,1,0,0,(u32)data,a,64,done);ARQPostRequest(&high,2,0,1,(u32)data,a,64,done);if(count)return 3;Melee360ARAMPump();Melee360ARAMPump();if(count!=2||order[0]!=2||order[1]!=1)return 4;
    ARQPostRequest(&read,3,1,1,a,(u32)output,64,done);Melee360ARAMPump();if(count!=3||memcmp(data,output,64))return 5;
    if(ARFree(&size)!=a||size!=64)return 6;
    puts("ARAM: LIFO allocation, deferred priority queue and byte-exact RAM transfers passed");return 0;
}
