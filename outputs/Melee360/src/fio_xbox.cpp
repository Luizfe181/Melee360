#include <xtl.h>
#include <stdio.h>
#include <string.h>
extern "C" {
#include <dolphin/types.h>
#include <dolphin/mcc.h>
int OSDisableInterrupts(void);int OSRestoreInterrupts(int);
}
namespace {
struct Slot{HANDLE file;unsigned int generation;bool writable;} slots[32];bool initialized;u8 lastError;
struct Guard{int previous;Guard():previous(OSDisableInterrupts()){}~Guard(){OSRestoreInterrupts(previous);}};
const char* directory="game:\\fio";
bool path(const char* name,char* destination){if(!name||!*name||strlen(name)>180)return false;/* Local debug exports, never arbitrary host paths. */for(const char* p=name;*p;++p)if(*p==':'||*p=='/'||*p=='\\'||*p<32)return false;if(!strcmp(name,".")||!strcmp(name,".."))return false;sprintf_s(destination,256,"%s\\%s",directory,name);return true;}
int index(int descriptor){if(descriptor<=0)return -1;unsigned int value=(unsigned int)descriptor-1,s=value%32;return slots[s].file&&slots[s].generation==value/32?(int)s:-1;}
}
extern "C" int FIOInit(MCC_EXI exi,MCC_CHANNEL channel,u8 blockSize){Guard guard;if(exi<MCC_EXI_0||exi>MCC_EXI_2||channel<MCC_CHANNEL_1||channel>MCC_CHANNEL_15||!blockSize){lastError=0xB0;return 0;}if(!CreateDirectoryA(directory,0)&&GetLastError()!=ERROR_ALREADY_EXISTS){lastError=0x87;return 0;}DWORD attributes=GetFileAttributesA(directory);if(attributes==0xffffffffu||!(attributes&FILE_ATTRIBUTE_DIRECTORY)){lastError=0x87;return 0;}initialized=true;lastError=0;return 1;}
extern "C" void FIOExit(void){Guard guard;for(int i=0;i<32;++i)if(slots[i].file){CloseHandle(slots[i].file);slots[i].file=0;}initialized=false;lastError=0;}
extern "C" int FIOQuery(void){Guard guard;DWORD attributes=GetFileAttributesA(directory);bool ok=initialized&&attributes!=0xffffffffu&&(attributes&FILE_ATTRIBUTE_DIRECTORY);lastError=ok?0:0x87;return ok?1:0;}
extern "C" u8 FIOGetLastError(void){Guard guard;return lastError;}
extern "C" int FIOFopen(const char* name,u32 mode){Guard guard;char full[256];int i;if(!initialized){lastError=0x87;return -1;}if(!path(name,full)||(mode&~0xe03u)||(mode&3)==3||((mode&0x800)&&!(mode&0x200))||((mode&0x400)&&(mode&3)==0)){lastError=0xB0;return -1;}for(i=0;i<32&&slots[i].file;++i){}if(i==32){lastError=0xA1;return -1;}
    DWORD access=(mode&3)==0?GENERIC_READ:(mode&3)==1?GENERIC_WRITE:GENERIC_READ|GENERIC_WRITE;DWORD creation=mode&0x800?CREATE_NEW:mode&0x400?(mode&0x200?CREATE_ALWAYS:TRUNCATE_EXISTING):mode&0x200?OPEN_ALWAYS:OPEN_EXISTING;
    HANDLE h=CreateFileA(full,access,FILE_SHARE_READ,0,creation,FILE_ATTRIBUTE_NORMAL,0);if(h==INVALID_HANDLE_VALUE){lastError=0x87;return -1;}slots[i].file=h;slots[i].writable=(mode&3)!=0;slots[i].generation=(slots[i].generation+1)&0x01ffffffu;lastError=0;return (int)(slots[i].generation*32+i+1);}
extern "C" int FIOFclose(int descriptor){Guard guard;int i=index(descriptor);if(i<0){lastError=0xB0;return 0;}BOOL ok=CloseHandle(slots[i].file);if(ok)slots[i].file=0;lastError=ok?0:0x87;return ok?1:0;}
extern "C" u32 FIOFwrite(int descriptor,void* data,u32 bytes){Guard guard;int i=index(descriptor);DWORD written=0;if(i<0||!slots[i].writable||(!data&&bytes)){lastError=0xB0;return 0;}if(!bytes){lastError=0;return 0;}if(!WriteFile(slots[i].file,data,bytes,&written,0)){lastError=0x87;return written;}lastError=0;return written;}
extern "C" int Melee360FIOProbe(void){char name[64],full[256];const char payload[]="Melee360 original FIO export\n";char readback[sizeof(payload)]={0};DWORD bytes;int descriptor,stale;bool ok;
    FIOExit();if(FIOQuery())return 0;sprintf_s(name,sizeof(name),"probe-%08x.bin",GetTickCount());if(!path(name,full)||!FIOInit(MCC_EXI_0,MCC_CHANNEL_1,10)||!FIOQuery())return 0;
    descriptor=FIOFopen(name,0xa02);if(descriptor<0){FIOExit();return 0;}ok=FIOFwrite(descriptor,(void*)payload,sizeof(payload))==sizeof(payload);stale=descriptor;ok=FIOFclose(descriptor)&&ok;ok=!FIOFclose(stale)&&!FIOFwrite(stale,(void*)payload,1)&&ok;
    HANDLE file=CreateFileA(full,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);if(file==INVALID_HANDLE_VALUE)ok=false;else{ok=ReadFile(file,readback,sizeof(readback),&bytes,0)&&bytes==sizeof(payload)&&!memcmp(payload,readback,sizeof(payload))&&ok;CloseHandle(file);}
    descriptor=FIOFopen(name,0xa02);if(descriptor>=0){FIOFclose(descriptor);ok=false;}descriptor=FIOFopen(name,0);if(descriptor<0)ok=false;else{ok=!FIOFclose(stale)&&!FIOFwrite(descriptor,(void*)payload,1)&&ok;FIOExit();ok=!FIOFclose(descriptor)&&ok;}ok=FIOInit(MCC_EXI_0,MCC_CHANNEL_1,10)&&ok;ok=FIOFopen("../escape.bin",0xa02)<0&&FIOGetLastError()==0xB0&&ok;FIOExit();if(!DeleteFileA(full))ok=false;return ok?1:0;
}
