#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>
extern "C" {
void* OSInitAlloc(void*,void*,int);
int OSCreateHeap(void*,void*);
void OSDestroyHeap(int);
int Melee360OSHeapAllocationState(int);
void* OSAllocFromHeap(int,unsigned long);
void OSFreeToHeap(int,void*);
long OSCheckHeap(int);
unsigned long OSReferentSize(void*);
void __assert(const char* file,unsigned int line,const char* message){fprintf(stderr,"%s:%u %s\n",file,line,message);exit(99);}
void OSReport(const char* fmt,...){va_list a;va_start(a,fmt);vprintf(fmt,a);va_end(a);}
}
int main(){
    unsigned char* arena=(unsigned char*)_aligned_malloc(65536,32);
    if(!arena)return 1;
    void* start=OSInitAlloc(arena,arena+65536,2);
    int heap=OSCreateHeap(start,arena+32768);
    int second=OSCreateHeap(arena+32768,arena+65536);
    if(Melee360OSHeapAllocationState(heap)!=0||Melee360OSHeapAllocationState(-1)!=-1)return 9;
    long initial=OSCheckHeap(heap),other=OSCheckHeap(second);
    void* a=OSAllocFromHeap(heap,1);void* b=OSAllocFromHeap(heap,511);void* c=OSAllocFromHeap(heap,4096);
    if(Melee360OSHeapAllocationState(heap)!=1||Melee360OSHeapAllocationState(second)!=0)return 10;
    if(!a||!b||!c||((unsigned long)a&31)||((unsigned long)b&31)||OSReferentSize(b)<511)return 2;
    memset(b,0x5a,511);OSFreeToHeap(heap,a);OSFreeToHeap(heap,c);
    if(((unsigned char*)b)[510]!=0x5a||OSCheckHeap(heap)<0||OSCheckHeap(second)!=other)return 3;
    OSFreeToHeap(heap,b);if(OSCheckHeap(heap)!=initial)return 4;
    void* blocks[1024];int n=0;
    while(n<1024&&(blocks[n]=OSAllocFromHeap(heap,257))!=0)++n;
    if(n==0||n==1024||OSCheckHeap(heap)<0)return 5;
    for(int i=1;i<n;i+=2)OSFreeToHeap(heap,blocks[i]);
    for(int i=0;i<n;i+=2)OSFreeToHeap(heap,blocks[i]);
    if(OSCheckHeap(heap)!=initial)return 6;
    if(Melee360OSHeapAllocationState(heap)!=0)return 11;
    OSDestroyHeap(heap);if(Melee360OSHeapAllocationState(heap)!=-1)return 12;if(OSCheckHeap(heap)!=-1)return 7;
    if(OSCreateHeap(start,arena+32768)!=heap)return 8;
    OSDestroyHeap(heap);OSDestroyHeap(second);_aligned_free(arena);
    puts("Original allocator: alignment, split/coalesce, exhaustion, isolation and heap reuse passed");return 0;
}
