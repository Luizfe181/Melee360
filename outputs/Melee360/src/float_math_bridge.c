#include <math.h>
#undef sinf
#undef cosf
float sinf(float angle){return (float)sin((double)angle);}
float cosf(float angle){return (float)cos((double)angle);}
