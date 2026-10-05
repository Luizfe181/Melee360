#ifndef MELEE360_GAMEPLAY_BOUNDARY_H
#define MELEE360_GAMEPLAY_BOUNDARY_H
#include <Runtime/platform.h>
#include <math.h>
#undef FLT_EPSILON
#include <float.h>
/* Preserve the original project's tolerance rather than the CRT definition. */
#undef FLT_EPSILON
#define FLT_EPSILON 1.00000001335e-10F
#ifndef F32_MAX
#define F32_MAX FLT_MAX
#endif
#ifndef M_PI_2
#define M_PI_2 1.57079632679489661923
#endif
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#ifndef M_TAU
#define M_TAU 6.28318530717958647692
#endif
#ifndef M_PI_4
#define M_PI_4 0.78539816339744830962
#endif
#define M_PI_F 3.14159265358979323846F
#define M_PI_2_F 1.57079632679489661923F
#define M_PI_3 1.04719755119659774615
#define M_TAU_F 6.28318530717958647692F
/* CRT float macros expand through double functions and collide with original
 * function definitions and local variables named sin/cos. Keep float APIs. */
#undef sinf
#undef cosf
#undef expf
#undef acosf
#undef asinf
#undef atanf
#undef atan2f
#undef powf
/* Keep the game's approximation and every original caller separate from the
 * XDK/D3D math implementation. Do not replace either provider with the other. */
#define powf Melee360OriginalPowf
#define expf Melee360OriginalExpf
#define atan2f Melee360OriginalAtan2f
extern float sinf(float);
extern float cosf(float);
extern float expf(float);
extern float acosf(float);
extern float asinf(float);
extern float atanf(float);
extern float atan2f(float,float);
extern float powf(float,float);
#ifndef U64_MAX
#define U64_MAX (~(u64)0)
#endif
/* A real platform clock provider is required before these objects can link. */
extern u32 Melee360OSBusClock;
#ifndef OS_TIMER_CLOCK
#define OS_TIMER_CLOCK (Melee360OSBusClock / 4)
#endif
#ifndef FP_NAN
#define FP_NAN 0
#define FP_INFINITE 1
#define FP_ZERO 2
#define FP_SUBNORMAL 3
#define FP_NORMAL 4
static __inline int Melee360Classify(double value, double minimum) {
    double magnitude;
    if (_isnan(value)) return FP_NAN;
    if (!_finite(value)) return FP_INFINITE;
    if (value == 0.0) return FP_ZERO;
    magnitude = value < 0.0 ? -value : value;
    return magnitude < minimum ? FP_SUBNORMAL : FP_NORMAL;
}
#define fpclassify(value) Melee360Classify((value), sizeof(value)==sizeof(float)?FLT_MIN:DBL_MIN)
#endif
/* Preload adapted headers before quoted includes can select upstream siblings. */
#include <generated/gameplay_headers.h>
#endif
