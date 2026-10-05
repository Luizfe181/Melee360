#include "gx_texture.h"
#ifdef _XBOX
extern "C" unsigned int GXGetTexBufferSize(unsigned short,unsigned short,unsigned int,unsigned char,unsigned char);
#endif
namespace {
unsigned int word(const unsigned char* p) {return (p[0]<<8)|p[1];}
unsigned int rgba(unsigned int r,unsigned int g,unsigned int b,unsigned int a) {
    return (a<<24)|(r<<16)|(g<<8)|b;
}
unsigned int expand(unsigned int v,int bits) {
    if(bits==3) return (v<<5)|(v<<2)|(v>>1);
    if(bits==4) return (v<<4)|v;
    if(bits==5) return (v<<3)|(v>>2);
    return (v<<2)|(v>>4);
}
unsigned int rgb565(unsigned int v) {
    return rgba(expand(v>>11,5),expand((v>>5)&63,6),expand(v&31,5),255);
}
unsigned int rgb5a3(unsigned int v) {
    if(v&0x8000) return rgba(expand((v>>10)&31,5),expand((v>>5)&31,5),expand(v&31,5),255);
    return rgba(expand((v>>8)&15,4),expand((v>>4)&15,4),expand(v&15,4),expand((v>>12)&7,3));
}
bool layout(unsigned int f,unsigned int& w,unsigned int& h,unsigned int& bytes) {
    bytes=32;
    switch(f) {
    case 0:case 8:case 14:w=h=8;return true;
    case 1:case 2:case 9:w=8;h=4;return true;
    case 3:case 4:case 5:case 10:w=h=4;return true;
    case 6:w=h=4;bytes=64;return true;
    default:return false;
    }
}
unsigned int blend(unsigned int a,unsigned int b,int wa,int wb,int divisor,int alpha) {
    return rgba((((a>>16)&255)*wa+((b>>16)&255)*wb)/divisor,
                (((a>>8)&255)*wa+((b>>8)&255)*wb)/divisor,
                ((a&255)*wa+(b&255)*wb)/divisor,alpha);
}
}
unsigned int Melee360GxTextureBytes(unsigned int w,unsigned int h,unsigned int f) {
    unsigned int bw,bh,size;
    if(!w || !h || w>1024 || h>1024 || !layout(f,bw,bh,size)) return 0;
    #ifdef _XBOX
    return GXGetTexBufferSize((unsigned short)w,(unsigned short)h,f,0,0);
#else
    return ((w+bw-1)/bw)*((h+bh-1)/bh)*size;
#endif
}
int Melee360DecodeGxTexture(const unsigned char* data,unsigned int bytes,
    unsigned int w,unsigned int h,unsigned int f,const unsigned char* palette,
    unsigned int entries,unsigned int pf,unsigned int* out,unsigned int outputPixels)
{
    unsigned int bw,bh,size,required=Melee360GxTextureBytes(w,h,f);
    if(!data || !out || !required || bytes<required || outputPixels<w*h || !layout(f,bw,bh,size)) return 0;
    if((f==8 || f==9 || f==10) && (!palette || !entries || entries>16384 || pf>2)) return 0;
    unsigned int tiles=(w+bw-1)/bw;
    for(unsigned int y=0;y<h;++y) for(unsigned int x=0;x<w;++x) {
        const unsigned char* tile=data+((y/bh)*tiles+x/bw)*size;
        unsigned int p=(y%bh)*bw+x%bw,color=0,index=0;
        switch(f) {
        case 0: {unsigned int i=expand((tile[p/2]>>(p%2?0:4))&15,4);color=rgba(i,i,i,i);break;}
        case 1: {unsigned int i=tile[p];color=rgba(i,i,i,i);break;}
        case 2: {unsigned int i=expand(tile[p]&15,4);color=rgba(i,i,i,expand(tile[p]>>4,4));break;}
        case 3: {unsigned int i=tile[p*2+1];color=rgba(i,i,i,tile[p*2]);break;}
        case 4:color=rgb565(word(tile+p*2));break;
        case 5:color=rgb5a3(word(tile+p*2));break;
        case 6:color=rgba(tile[p*2+1],tile[32+p*2],tile[33+p*2],tile[p*2]);break;
        case 8:index=(tile[p/2]>>(p%2?0:4))&15;break;
        case 9:index=tile[p];break;
        case 10:index=word(tile+p*2)&0x3FFF;break;
        case 14: {
            const unsigned char* block=tile+((y%8)/4*2+(x%8)/4)*8;
            unsigned int a=word(block),b=word(block+2),colors[4];
            colors[0]=rgb565(a);colors[1]=rgb565(b);
            if(a>b) {colors[2]=blend(colors[0],colors[1],5,3,8,255);colors[3]=blend(colors[0],colors[1],3,5,8,255);}
            else {colors[2]=blend(colors[0],colors[1],1,1,2,255);colors[3]=blend(colors[0],colors[1],1,1,2,0);}
            color=colors[(block[4+y%4]>>(6-2*(x%4)))&3];break;
        }
        }
        if(f==8 || f==9 || f==10) {
            if(index>=entries) return 0;
            unsigned int v=word(palette+index*2);
            if(pf==0) {unsigned int i=v&255;color=rgba(i,i,i,v>>8);}
            else color=pf==1?rgb565(v):rgb5a3(v);
        }
        out[y*w+x]=color;
    }
    return 1;
}
