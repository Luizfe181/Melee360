#include "../src/runtime_archive.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
void OSReport(const char* format,...){va_list args;va_start(args,format);vfprintf(stderr,format,args);va_end(args);}
static void put(unsigned char* p,unsigned int n){p[0]=(unsigned char)(n>>24);p[1]=(unsigned char)(n>>16);p[2]=(unsigned char)(n>>8);p[3]=(unsigned char)n;}
int main(void){const char* names[5]={"PlCo.dat","PlMr.dat","PlMrNr.dat","GrNBa.dat","PlLk.dat"};int i;unsigned char fixture[82]={0};HSD_Archive a;unsigned int value;
 for(i=0;i<5;++i){char path[256];FILE* f;long bytes;unsigned char* raw;sprintf_s(path,sizeof(path),"C:\\Users\\luizf\\Documents\\melee_extraido\\%s",names[i]);f=fopen(path,"rb");if(!f)return 1;fseek(f,0,SEEK_END);bytes=ftell(f);rewind(f);raw=malloc(bytes);if(!raw||fread(raw,1,bytes,f)!=(size_t)bytes)return 2;fclose(f);if(!Melee360ValidateNativeArchive(raw,bytes)||Melee360ValidateNativeArchive(raw,bytes-1))return 3;put(raw+32+((unsigned int)raw[4]<<24|(unsigned int)raw[5]<<16|(unsigned int)raw[6]<<8|raw[7]),0xfffffffc);if(Melee360ValidateNativeArchive(raw,bytes))return 4;free(raw);}
 /* Fixture in host-native byte order tests the actual original parser's pointer
  * relocation and public/extern APIs. Real assets are validated as big endian. */
 value=82;memcpy(fixture,&value,4);value=32;memcpy(fixture+4,&value,4);value=1;memcpy(fixture+8,&value,4);memcpy(fixture+12,&value,4);value=8;memcpy(fixture+32,&value,4);value=0;memcpy(fixture+64,&value,4);memcpy(fixture+68,&value,4);memcpy(fixture+72,&value,4);memcpy(fixture+76,"root",5);
 if(HSD_ArchiveParse(&a,fixture,sizeof(fixture))||*(unsigned int*)(fixture+32)!=(unsigned int)(fixture+40)||HSD_ArchiveGetPublicAddress(&a,"root")!=fixture+32||HSD_ArchiveGetPublicAddress(&a,"missing")||HSD_ArchiveGetExtern(&a,0))return 5;
 {unsigned char external[80]={0};unsigned int n=80;memcpy(external,&n,4);n=16;memcpy(external+4,&n,4);n=1;memcpy(external+12,&n,4);memcpy(external+16,&n,4);n=4;memcpy(external+32,&n,4);n=0xffffffffu;memcpy(external+36,&n,4);n=8;memcpy(external+48,&n,4);n=5;memcpy(external+60,&n,4);memcpy(external+64,"root",5);memcpy(external+69,"external",9);
 if(HSD_ArchiveParse(&a,external,80)||!HSD_ArchiveGetExtern(&a,0)||strcmp(HSD_ArchiveGetExtern(&a,0),"external")||HSD_ArchiveGetExtern(&a,1))return 7;
 HSD_ArchiveLocateExtern(&a,"external",NULL);if(*(unsigned int*)(external+32)||*(unsigned int*)(external+36))return 8;
 }
 {HSD_Archive* result=&a;if(Melee360RuntimeArchiveLoad("PlMr.dat",&result)||result)return 6;}
 puts("Original HSD archive relocation/public APIs, five real asset / original NULL extern-chain corruption checks and incompatible-host rejection passed");return 0;
}
