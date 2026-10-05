#include "gx_copy_codec.h"
#include <string.h>
unsigned int Melee360GXCopyBytes(unsigned int w,unsigned int h,unsigned int f){if(!w||!h||w>1024||h>1024||(f!=4&&f!=5&&f!=6&&f!=32))return 0;if(f==32)return ((w+7)/8)*((h+7)/8)*32;return ((w+3)/4)*((h+3)/4)*(f==6?64:32);}
int Melee360EncodeGXCopy(const unsigned int* pixels,unsigned int w,unsigned int h,unsigned int f,unsigned char* dst,unsigned int capacity){
 unsigned int bytes=Melee360GXCopyBytes(w,h,f);if(!pixels||!dst||!bytes||capacity<bytes)return 0;memset(dst,0,bytes);
 for(unsigned int y=0;y<h;++y)for(unsigned int x=0;x<w;++x){unsigned int v=pixels[y*w+x],a=v>>24,r=(v>>16)&255,g=(v>>8)&255,b=v&255;
 if(f==32){unsigned at=(y%8)*8+x%8;unsigned char* tile=dst+((y/8)*((w+7)/8)+x/8)*32;tile[at/2]|=(unsigned char)((r>>4)<<((at&1)?0:4));continue;}
 unsigned char* tile=dst+((y/4)*((w+3)/4)+x/4)*(f==6?64:32);unsigned int at=((y%4)*4+x%4)*2;
 if(f==6){tile[at]=(unsigned char)a;tile[at+1]=(unsigned char)r;tile[at+32]=(unsigned char)g;tile[at+33]=(unsigned char)b;}
 else{unsigned int packed=f==4?((r>>3)<<11)|((g>>2)<<5)|(b>>3):a>=224?0x8000|((r>>3)<<10)|((g>>3)<<5)|(b>>3):((a>>5)<<12)|((r>>4)<<8)|((g>>4)<<4)|(b>>4);tile[at]=(unsigned char)(packed>>8);tile[at+1]=(unsigned char)packed;}
 }return 1;
}
