#include <dolphin/card.h>
#include <dolphin/ar.h>
#include <stdio.h>
#include <string.h>
void Melee360CardPump(void);void Melee360AlarmPump(void);int Melee360CardSetRoot(const char*);
void Melee360ARAMPump(void); int Melee360ARAMReadPCM(u32,u16,s16*);
static __declspec(align(32)) unsigned char workArea[40960],data[8192],readBack[8192];
static int completion,result,alarms;
static u32 arStack[16];static int arCompleted;
static void arDone(ARQRequest* request){if(request->owner==17)++arCompleted;}
static void cardDone(s32 channel,s32 code){result=channel==0?code:-999;++completion;}
static int pumpCard(int expected){int before=completion;Melee360CardPump();return completion==before+1&&result==expected;}
static void alarmDone(OSAlarm* alarm,OSContext* context){if(!context)++alarms;OSCancelAlarm(alarm);}
static void removeTest(void){remove("game:\\card-selftest-a.m360card");remove("game:\\card-selftest-a.m360card.tmp");remove("game:\\card-selftest-a.m360card.bak");}
int Melee360PlatformServicesProbe(void){
    OSAlarm alarm;CARDFileInfo file;CARDStat stat;int ok=0;
    OSCreateAlarm(&alarm);OSSetAlarm(&alarm,0,alarmDone);if(alarms||!OSCheckAlarmQueue())return 0;Melee360AlarmPump();if(alarms!=1||alarm.handler)return 0;
    {
        u32 address,freed;ARQRequest request;s16 sample=0;
        if(ARInit(arStack,16)!=0x4000)return 0;ARQInit();address=ARAlloc(64);memset(data,0x37,64);
        ARQPostRequest(&request,17,ARQ_TYPE_MRAM_TO_ARAM,1,(u32)data,address,64,arDone);if(arCompleted)return 0;Melee360ARAMPump();
        ARQPostRequest(&request,17,ARQ_TYPE_ARAM_TO_MRAM,1,address,(u32)readBack,64,arDone);Melee360ARAMPump();
        if(!Melee360ARAMReadPCM(address/2,10,&sample)||sample!=0x3737||!Melee360ARAMReadPCM(address,25,&sample)||sample!=0x3700||Melee360ARAMReadPCM(0xffffffff,10,&sample)||Melee360ARAMReadPCM(address,0,&sample))return 0; if(arCompleted!=2||memcmp(data,readBack,64)||ARFree(&freed)!=address||freed!=64)return 0;
    }
    /* A read-only package must still boot. The value 2 means CARD was not tested. */
    {
        FILE* writable=fopen("game:\\card-selftest-write.tmp","wb");
        if(!writable)return 2;
        fclose(writable);remove("game:\\card-selftest-write.tmp");
    }
    /* Self-test files are isolated from the actual card-slot containers. */
    if(!Melee360CardSetRoot("game:\\card-selftest"))return 0;removeTest();
    if(CARDMountAsync(0,workArea,0,cardDone)||!pumpCard(CARD_RESULT_BROKEN))goto cleanup;
    if(CARDFormatAsync(0,cardDone)||!pumpCard(0))goto cleanup;
    if(CARDCreateAsync(0,"Melee360 self-test",8192,&file,cardDone)||!pumpCard(0))goto cleanup;
    memset(data,0x5a,8192);
    if(CARDWriteAsync(&file,data,8192,0,cardDone)||!pumpCard(0)||CARDClose(&file))goto cleanup;
    if(CARDUnmount(0)||CARDMountAsync(0,workArea,0,cardDone)||!pumpCard(0)||CARDOpen(0,"Melee360 self-test",&file))goto cleanup;
    if(CARDRead(&file,readBack,8192,0)||memcmp(data,readBack,8192)||CARDGetStatus(0,file.fileNo,&stat)||stat.length!=8192)goto cleanup;
    ok=1;
cleanup:CARDClose(&file);CARDUnmount(0);removeTest();if(!Melee360CardSetRoot("game:\\card-slot"))ok=0;return ok;
}
