#include "../src/gx_copy_codec.h"
#include "../src/gx_texture.h"
#include <stdio.h>
#include <string.h>
int main(){unsigned int input[17*9],out[17*9];unsigned char bytes[1024];
 for(unsigned int i=0;i<17*9;++i)input[i]=((i*13&255)<<24)|((i*37&255)<<16)|((i*53&255)<<8)|(i*71&255);
 for(unsigned int f=4;f<=6;++f){unsigned int n=Melee360GXCopyBytes(17,9,f);memset(bytes,0xCD,sizeof(bytes));if(!Melee360EncodeGXCopy(input,17,9,f,bytes,n))return 1;
 if(bytes[n]!=0xCD||!Melee360DecodeGxTexture(bytes,n,17,9,f,0,0,0,out,17*9))return 2;
 for(unsigned int i=0;i<17*9;++i){unsigned int v=input[i],a=v>>24,r=(v>>16)&255,g=(v>>8)&255,b=v&255;
 if(f==4){r=(r&248)|(r>>5);g=(g&252)|(g>>6);b=(b&248)|(b>>5);a=255;}
 if(f==5){if(a>=224){r=(r&248)|(r>>5);g=(g&248)|(g>>5);b=(b&248)|(b>>5);a=255;}else{r=(r&240)|(r>>4);g=(g&240)|(g>>4);b=(b&240)|(b>>4);a=(a&224)|((a>>3)&28)|(a>>6);}}
 if(out[i]!=((a<<24)|(r<<16)|(g<<8)|b))return 3;}
 if(Melee360EncodeGXCopy(input,17,9,f,bytes,n-1))return 4;
 }
 if(Melee360GXCopyBytes(0,9,6)||Melee360GXCopyBytes(1025,9,6)||Melee360GXCopyBytes(4,4,14))return 5;
 // Independently specified first texel and GB plane, not merely a round trip.
 input[0]=0x80112233;if(!Melee360EncodeGXCopy(input,4,4,6,bytes,64)||bytes[0]!=0x80||bytes[1]!=0x11||bytes[32]!=0x22||bytes[33]!=0x33)return 6;
 puts("GX EFB copy codec: 459 independent decoded pixels, big-endian planes, padded tiles and destination bounds passed");return 0;
}
