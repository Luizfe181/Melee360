#ifndef MELEE360_OSALLOC_H
#define MELEE360_OSALLOC_H
typedef int OSHeapHandle;
#ifdef __cplusplus
extern "C" {
#endif
extern volatile OSHeapHandle __OSCurrHeap;
OSHeapHandle OSSetCurrentHeap(OSHeapHandle heap);
long OSCheckHeap(OSHeapHandle heap);
void* OSInitAlloc(void* start,void* end,int heaps);
OSHeapHandle OSCreateHeap(void* start,void* end);
void OSDestroyHeap(OSHeapHandle heap);
void* OSAllocFromHeap(OSHeapHandle heap,unsigned long size);
void OSFreeToHeap(OSHeapHandle heap,void* pointer);
#ifdef __cplusplus
}
#endif
#endif
