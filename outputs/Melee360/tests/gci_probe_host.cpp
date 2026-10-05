#include <stdio.h>
#include <vector>
extern "C" {
#include <sysdolphin/baselib/crypt.h>
}
int main(int argc,char** argv){if(argc!=2)return 1;FILE* f=fopen(argv[1],"rb");if(!f)return 2;fseek(f,0,SEEK_END);long size=ftell(f);rewind(f);std::vector<unsigned char> raw(size);fread(&raw[0],1,size,f);fclose(f);for(unsigned int at=64;at+8192<=raw.size();at+=8192){std::vector<unsigned char> block(raw.begin()+at,raw.begin()+at+8192);if(!HSD_Decrypt(&block[0],8192)){printf("block=%u id=%u seq=%u table=",(at-64)/8192,(block[16]<<8)|block[17],block[18]);for(int i=19;i<31;++i)printf("%02x",block[i]);puts("");}}return 0;}
