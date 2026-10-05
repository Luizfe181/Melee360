#include <math.h>
#include <float.h>
#include <stdio.h>
extern "C" float Melee360OriginalPowf(float,float);
int main(){const float cases[][2]={{0,2},{1,8},{2,3},{2,-2},{.5f,3},{3,.5f}};for(int i=0;i<6;++i){float original=Melee360OriginalPowf(cases[i][0],cases[i][1]);double expected=pow((double)cases[i][0],(double)cases[i][1]);if(!_finite(original)||fabs(original-expected)>0.0001*(1+fabs(expected)))return 1;}puts("Original powf approximation: six positive-domain/zero cases passed; namespaced provider retained");return 0;}
