#include "card_image.h"
#include <string.h>
namespace {
unsigned int word(const unsigned char* p) {return (p[0]<<8)|p[1];}
void put(unsigned char* p,unsigned int v) {p[0]=(unsigned char)(v>>8);p[1]=(unsigned char)v;}
unsigned int checksum(const unsigned char* p,unsigned int bytes,bool inverse) {
    unsigned int result=0;
    for(unsigned int i=0;i<bytes;i+=2) result+=(inverse?~word(p+i):word(p+i))&65535;
    result&=65535;return result==65535?0:result;
}
void store(unsigned char* at,const unsigned char* data,unsigned int bytes) {
    put(at,checksum(data,bytes,false));put(at+2,checksum(data,bytes,true));
}
bool check(const unsigned char* at,const unsigned char* data,unsigned int bytes) {
    return word(at)==checksum(data,bytes,false)&&word(at+2)==checksum(data,bytes,true);
}
}
int Melee360FormatCardImage(unsigned char* image,unsigned int bytes,const unsigned char serial[32]) {
    if(!image||bytes!=MELEE360_CARD_BYTES||!serial) return 0;
    memset(image,255,bytes);memcpy(image,serial,32);
    put(image+32,0);put(image+34,16);put(image+36,0);store(image+508,image,508);
    for(unsigned int copy=0;copy<2;++copy) {
        unsigned char* dir=image+(1+copy)*MELEE360_CARD_BLOCK;
        put(dir+8186,copy);store(dir+8188,dir,8188);
        unsigned char* fat=image+(3+copy)*MELEE360_CARD_BLOCK;
        memset(fat,0,MELEE360_CARD_BLOCK);put(fat+4,copy);put(fat+6,251);put(fat+8,4);store(fat,fat+4,8188);
    }
    return 1;
}
int Melee360CheckCardSystem(const unsigned char* image,unsigned int bytes) {
    if(!image||bytes!=MELEE360_CARD_BYTES||word(image+32)||word(image+34)!=16||word(image+36)!=0||!check(image+508,image,508)) return 0;
    bool dirValid=false,fatValid=false;
    for(unsigned int copy=0;copy<2;++copy) {
        const unsigned char* dir=image+(1+copy)*MELEE360_CARD_BLOCK;
        const unsigned char* fat=image+(3+copy)*MELEE360_CARD_BLOCK;
        dirValid|=check(dir+8188,dir,8188);
        fatValid|=check(fat,fat+4,8188)&&word(fat+6)<=251&&word(fat+8)>=4&&word(fat+8)<256;
    }
    return dirValid&&fatValid;
}
