#include <dolphin/card.h>
#include <stdio.h>
#include <string.h>
void Melee360CardPump(void);int Melee360CardSetRoot(const char*);
u32 Melee360OSBusClock=162000000;
OSTime OSGetTime(void){return 40500000LL*123;}
static __declspec(align(32)) unsigned char area[40960],source[8192],target[8192];
static int count,result;
static void callback(s32 ch,s32 value){if(ch!=0)result=-999;else result=value;++count;}
static int finish(int expected){int old=count;Melee360CardPump();return count==old+1&&result==expected;}
static void cleanup(void){remove("card-test-a.m360card");remove("card-test-a.m360card.tmp");remove("card-test-a.m360card.bak");}
int main(void){CARDFileInfo info;CARDStat stat;s32 bytes,files;FILE* file;
    cleanup();CARDInit();if(!Melee360CardSetRoot("card-test"))return 1;
    if(CARDMountAsync(0,area,0,callback)||count||!finish(CARD_RESULT_BROKEN))return 2;
    if(CARDFormatAsync(0,callback)||CARDGetResultCode(0)!=CARD_RESULT_BUSY||!finish(0))return 3;
    if(CARDFreeBlocks(0,&bytes,&files)||files!=127||bytes<=8192)return 4;
    if(CARDCreateAsync(0,"Melee Save",8192,&info,callback)||!finish(0))return 5;
    memset(source,0x5a,sizeof(source));if(CARDWriteAsync(&info,source,8192,0,callback)||CARDClose(&info)!=CARD_RESULT_BUSY||!finish(0)||CARDGetXferredBytes(0)!=8192)return 6;
    if(CARDRead(&info,target,8192,0)||memcmp(source,target,8192))return 7;
    if(CARDRead(&info,target+1,512,0)!=CARD_RESULT_FATAL_ERROR||CARDRead(&info,target,512,8192)!=CARD_RESULT_FATAL_ERROR||CARDWrite(&info,source,512,0)!=CARD_RESULT_FATAL_ERROR)return 8;
    if(CARDGetStatus(0,info.fileNo,&stat)||stat.length!=8192||stat.time!=123)return 9;
    stat.commentAddr=64;stat.iconAddr=0;stat.bannerFormat=2;if(CARDSetStatusAsync(0,info.fileNo,&stat,callback)||!finish(0))return 10;
    if(CARDClose(&info)||CARDUnmount(0)||CARDMountAsync(0,area,0,callback)||!finish(0)||CARDOpen(0,"Melee Save",&info)||CARDRead(&info,target,8192,0)||memcmp(source,target,8192))return 11;
    if(CARDGetStatus(0,info.fileNo,&stat)||stat.commentAddr!=64||stat.bannerFormat!=2)return 12;
    if(CARDClose(&info)||CARDRenameAsync(0,"Melee Save","Renamed",callback)||!finish(0)||CARDOpen(0,"Renamed",&info))return 13;
    if(CARDDeleteAsync(0,"Renamed",callback)||!finish(CARD_RESULT_BUSY))return 14;
    if(CARDClose(&info)||CARDDeleteAsync(0,"Renamed",callback)||!finish(0)||CARDFreeBlocks(0,&bytes,&files)||files!=127)return 15;
    if(CARDUnmount(0))return 16;
    remove("card-test-a.m360card.bak");file=fopen("card-test-a.m360card","r+b");if(!file)return 17;fseek(file,16,SEEK_SET);fputc(0x77,file);fclose(file);
    if(CARDMountAsync(0,area,0,callback)||!finish(CARD_RESULT_BROKEN)||CARDOpen(0,"Renamed",&info)!=CARD_RESULT_BROKEN||CARDUnmount(0))return 18;
    cleanup();puts("CARD: deferred mount/format/create/write, byte-exact persistence, metadata, rename/delete and corruption detection passed");return 0;
}
