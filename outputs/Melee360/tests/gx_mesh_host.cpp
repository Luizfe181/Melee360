#include "../src/gx_mesh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
static void put32(unsigned char* p,unsigned int v) {p[0]=(unsigned char)(v>>24);p[1]=(unsigned char)(v>>16);p[2]=(unsigned char)(v>>8);p[3]=(unsigned char)v;}
int main(int argc,char** argv) {
    Melee360MeshVertex* v=0;unsigned int n=0,unsupported=0;
    if(argc==1) {
        unsigned char data[256];memset(data,0,sizeof(data));
        put32(data+8,32);put32(data+16,96);data[15]=2;
        put32(data+32,9);put32(data+36,2);put32(data+40,1);put32(data+44,4);data[51]=12;put32(data+52,160);put32(data+56,255);
        data[96]=0x90;data[98]=3;data[99]=0;data[100]=1;data[101]=2;
        put32(data+160,0x3F800000);put32(data+176,0x40000000);put32(data+192,0x40400000);
        if(Melee360DecodeGxMesh(data,sizeof(data),0,&v,&n,&unsupported)!=1||n!=3) return 1;
        if(v[0].position[0]!=1||v[1].position[1]!=2||v[2].position[2]!=3) return 2;free(v);
        data[101]=255;if(Melee360DecodeGxMesh(data,sizeof(data),0,&v,&n,&unsupported)!=0) return 3;
        data[101]=2;data[96]=0xFF;if(Melee360DecodeGxMesh(data,sizeof(data),0,&v,&n,&unsupported)!=-1||unsupported!=255) return 4;
        puts("GX mesh indexed triangle/bounds/unsupported tests passed");return 0;
    }
    if(argc!=3) return 5;
    FILE* fp=fopen(argv[1],"rb");if(!fp) return 6;fseek(fp,0,SEEK_END);unsigned int bytes=ftell(fp);rewind(fp);
    unsigned char* data=(unsigned char*)malloc(bytes);if(!data||fread(data,1,bytes,fp)!=bytes) return 7;fclose(fp);
    int result=Melee360DecodeGxMesh(data+32,bytes-32,(unsigned int)strtoul(argv[2],0,10),&v,&n,&unsupported);
    printf("%d %u %u\n",result,n,unsupported);free(v);free(data);return result==0?8:0;
}
