#ifndef MELEE360_HSD_BOUNDARY_H
#define MELEE360_HSD_BOUNDARY_H
/* Forced into objalloc.c only. initialize.h drags in GX/video initialization.
 * Provide its sole required declaration without pretending to implement GX. */
#define _initialize_h_
#include <dolphin/os/OSAlloc.h>
#ifdef __cplusplus
extern "C" OSHeapHandle HSD_GetHeap(void);
#else
OSHeapHandle HSD_GetHeap(void);
#endif
#endif
