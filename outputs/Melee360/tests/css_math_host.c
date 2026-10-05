#include <math.h>
#undef sinf
#undef cosf
#undef atanf
#undef atan2f
float sinf(float x){return (float)sin(x);}
float cosf(float x){return (float)cos(x);}
float atanf(float x){return (float)atan(x);}
float Melee360CSSAtan2f(float x,float y){return (float)atan2(x,y);}
