#include <math.h>
#undef atanf
#undef atan2f
float atanf(float x){return (float)atan(x);}
float Melee360CSSAtan2f(float x,float y){return (float)atan2(x,y);}
