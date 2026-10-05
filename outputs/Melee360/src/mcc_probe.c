#include <dolphin/types.h>
#include <dolphin/mcc.h>
#include <string.h>
void Melee360HIOPump(void);void Melee360HIOClose(void);
static int devices,events;static u32 notification;
static int enumerate(long channel){if(channel==0)++devices;return 1;}
static void event(enum MCC_CHANNEL channel,u32 type,u32 value){if(channel==MCC_CHANNEL_1){++events;if(type==0x100)notification=value;}}
int Melee360MCCProbe(void){
 __declspec(align(32)) u8 written[64],readback[64];int i,ok=1;enum MCC_CONNECT connection;MCC_Info info;
 MCCExit();ok=ok&&!MCCInit((enum MCC_EXI)-1,1,0)&&MCCGetLastError()==4;
 devices=events=0;notification=0;ok=ok&&MCCEnumDevices(enumerate)&&devices==1;ok=ok&&MCCInit(MCC_EXI_0,2,0);if(!ok){Melee360HIOClose();return 0;}
 ok=ok&&MCCGetFreeBlocks(MCC_MODE_ALL)==15;ok=ok&&MCCOpen(MCC_CHANNEL_1,2,event);Melee360HIOPump();ok=ok&&MCCGetConnectionStatus(MCC_CHANNEL_1,&connection)&&connection==MCC_CONNECT_CONNECTED;ok=ok&&MCCGetChannelInfo(MCC_CHANNEL_1,&info)&&info.blockLength==2;ok=ok&&MCCGetFreeBlocks(MCC_MODE_ALL)==13;
 for(i=0;i<64;++i)written[i]=(u8)(i*37+19);memset(readback,0,64);ok=ok&&MCCWrite(MCC_CHANNEL_1,4,written,64,MCC_SYNC)&&MCCRead(MCC_CHANNEL_1,4,readback,64,MCC_SYNC)&&!memcmp(written,readback,64);
 ok=ok&&!MCCRead(MCC_CHANNEL_1,0,readback,-32,MCC_SYNC)&&MCCGetLastError()==13;
 ok=ok&&!MCCWrite(MCC_CHANNEL_1,16384,written,32,MCC_SYNC)&&MCCGetLastError()==15;
 ok=ok&&MCCNotify(MCC_CHANNEL_1,0x123456);Melee360HIOPump();ok=ok&&notification==0x123456;
 ok=ok&&MCCWrite(MCC_CHANNEL_1,128,written,64,MCC_ASYNC);for(i=0;i<100&&!MCCCheckAsyncDone();++i)Melee360HIOPump();ok=ok&&i<100;memset(readback,0,64);ok=ok&&MCCRead(MCC_CHANNEL_1,128,readback,64,MCC_ASYNC);for(i=0;i<100&&!MCCCheckAsyncDone();++i)Melee360HIOPump();ok=ok&&i<100&&!memcmp(written,readback,64);
 ok=ok&&MCCStreamOpen(MCC_CHANNEL_2,1)&&MCCGetFreeBlocks(MCC_MODE_ALL)==12;ok=ok&&MCCClose(MCC_CHANNEL_2)&&MCCClose(MCC_CHANNEL_1)&&MCCGetFreeBlocks(MCC_MODE_ALL)==15&&events>0;
 MCCExit();ok=ok&&!MCCGetFreeBlocks(MCC_MODE_ALL)&&MCCGetLastError()==1;Melee360HIOClose();return ok;
}
