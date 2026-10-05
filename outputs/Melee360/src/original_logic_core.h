#ifndef M360_ORIGINAL_LOGIC_CORE_H
#define M360_ORIGINAL_LOGIC_CORE_H
#ifdef __cplusplus
extern "C" {
#endif
struct MapCollData;
int Melee360OriginalLogicProbe(void);
int Melee360NativeLogicProbe(void);
int Melee360SweepMapPoint(const struct MapCollData*,int,float,float,float,float,float*,float*);
#ifdef __cplusplus
}
#endif
#endif
