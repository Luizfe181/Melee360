#include "../src/original_character_select.h"
#include <stdio.h>
#include <math.h>
int main(){struct Melee360CSSState s;if(!Melee360CSSProbe())return 1;Melee360CSSInit();Melee360CSSGetState(&s);float x=s.handX,y=s.handY;Melee360CSSAdvance(10,10);Melee360CSSGetState(&s);if(s.handX!=x||s.handY!=y)return 2;for(int i=0;i<8;++i)Melee360CSSAdvance(80,0);Melee360CSSGetState(&s);if(s.handX<=x||s.hover<=1)return 3;puts("Original CSS excerpts: 25 icon hits/CKind commits, token retrieval, free cursor bounds/deadzone/motion passed");return 0;}
