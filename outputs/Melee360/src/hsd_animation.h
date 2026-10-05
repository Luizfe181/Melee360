#ifndef MELEE360_HSD_ANIMATION_H
#define MELEE360_HSD_ANIMATION_H
// Samples unchanged upstream fobj.c/spline.c, with bounds checked packed data.
typedef void (*Melee360AnimValue)(void*,unsigned int,float);
bool Melee360SampleAObj(const unsigned char* data,unsigned int bytes,unsigned int aobj,
    float frame,Melee360AnimValue update,void* object,unsigned int* tracks);
// Packed original FigaTrack array (12-byte entries), sampled by upstream FObj.
bool Melee360SampleFigaTracks(const unsigned char* data,unsigned int bytes,unsigned int at,unsigned int count,
    float frame,Melee360AnimValue update,void* object,unsigned int* tracks);
#endif
