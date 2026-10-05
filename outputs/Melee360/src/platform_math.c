/* XAudio2 supplies the XDK atanf provider; defining another global atanf here
 * conflicts with its native math objects. Keep the CSS atan2 bridge scoped. */
#include <math.h>
#undef atanf
float Melee360CSSAtan2f(float x,float y){return (float)atan2((double)x,(double)y);}
