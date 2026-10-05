#include "../src/gx_texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc,char** argv) {
    unsigned char data[256],pal[32];unsigned int pixels[64];
    memset(data,255,sizeof(data));memset(pal,255,sizeof(pal));
    const unsigned int formats[]={0,1,2,3,4,5,6,8,9,10,14};
    for(unsigned int j=0;j<11;++j) {
        unsigned int f=formats[j],bytes=Melee360GxTextureBytes(8,8,f);
        if(f==8||f==9||f==10) memset(data,0,sizeof(data));else memset(data,255,sizeof(data));
        if(f==14) for(unsigned int block=0;block<4;++block) memset(data+block*8+4,0,4);
        if(!Melee360DecodeGxTexture(data,bytes,8,8,f,pal,16,1,pixels,64)) return 1;
        if(pixels[0]!=0xFFFFFFFF) return 2;
        if(Melee360DecodeGxTexture(data,bytes-1,8,8,f,pal,16,1,pixels,64)) return 3;
    }
    memset(data,0,sizeof(data));data[0]=255;data[1]=0;data[32]=0;data[33]=0;
    if(!Melee360DecodeGxTexture(data,64,4,4,6,0,0,0,pixels,64)||pixels[0]!=0xFF000000) return 4;
    // RGBA8 has separated AR and GB planes, including the last pixel.
    data[30]=128;data[31]=17;data[62]=34;data[63]=51;
    Melee360DecodeGxTexture(data,64,4,4,6,0,0,0,pixels,64);
    if(pixels[15]!=0x80112233) return 5;
    if(argc==1) {puts("GX texture format/bounds/channel tests passed");return 0;}
    if(argc!=9) return 6;
    unsigned int w=atoi(argv[2]),h=atoi(argv[3]),f=atoi(argv[4]);
    unsigned int n=atoi(argv[6]),pf=atoi(argv[7]);
    FILE* fp=fopen(argv[1],"rb");if(!fp) return 7;
    unsigned int bytes=Melee360GxTextureBytes(w,h,f);
    unsigned char* raw=(unsigned char*)malloc(bytes);
    unsigned char* palette=(unsigned char*)malloc(n*2+1);
    unsigned int* out=(unsigned int*)malloc(w*h*4);
    if(!raw||!palette||!out||fread(raw,1,bytes,fp)!=bytes) return 8;fclose(fp);
    if(n) {fp=fopen(argv[5],"rb");if(!fp||fread(palette,2,n,fp)!=n) return 9;fclose(fp);}
    if(!Melee360DecodeGxTexture(raw,bytes,w,h,f,palette,n,pf,out,w*h)) return 10;
    fp=fopen(argv[8],"wb");if(!fp) return 11;
    for(unsigned int i=0;i<w*h;++i) {unsigned char rgba[4]={(unsigned char)(out[i]>>16),(unsigned char)(out[i]>>8),(unsigned char)out[i],(unsigned char)(out[i]>>24)};fwrite(rgba,1,4,fp);}
    fclose(fp);free(raw);free(palette);free(out);return 0;
}
