#include <stdio.h>
typedef unsigned int u32;int Melee360CacheRange(u32,u32,u32*,u32*);
int main(void){u32 first,last;if(!Melee360CacheRange(0x1001,128,&first,&last)||first!=0x1000||last!=0x1080)return 1;if(!Melee360CacheRange(0x1080,128,&first,&last)||first!=last)return 2;if(Melee360CacheRange(0xffffff80,129,&first,&last)||Melee360CacheRange(0,1,&first,&last)||Melee360CacheRange(0x1000,0,&first,&last))return 3;if(!Melee360CacheRange(0xffffff80,128,&first,&last)||last!=0xffffff80)return 4;puts("Xenon 128-byte cache range alignment/coverage/overflow checks passed");return 0;}
