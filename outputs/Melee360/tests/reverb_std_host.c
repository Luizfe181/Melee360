#include <math.h>
#include <stdio.h>
float Melee360OriginalPowf(float a,float b){return (float)pow((double)a,(double)b);}
int Melee360ReverbStdProbe(void);
int main(void){if(!Melee360ReverbStdProbe())return 1;puts("AXFX standard reverb impulse/channel/predelay/ownership/failure tests passed");return 0;}
