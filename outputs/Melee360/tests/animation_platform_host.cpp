#include <stdlib.h>
#include <stdio.h>
extern "C" {
#include <sysdolphin/baselib/objalloc.h>
void* HSD_ObjAlloc(HSD_ObjAllocData*) {return calloc(1,128);}
void HSD_ObjFree(HSD_ObjAllocData*,void* p) {free(p);}
void HSD_ObjAllocInit(HSD_ObjAllocData*,size_t,u32) {}
__declspec(noreturn) void __assert(const char* f,u32 l,const char* c) {fprintf(stderr,"%s:%u %s\n",f,l,c);exit(90);}
}
