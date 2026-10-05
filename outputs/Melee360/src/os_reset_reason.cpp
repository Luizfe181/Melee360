#include <xtl.h>
#include <string.h>
extern "C" {
#include <dolphin/types.h>
}
/* Reset reasons are transported explicitly in our native relaunch data;
 * arbitrary dashboard launch data must not be interpreted as a reset code. */
struct NativeResetData {DWORD magic,version,code,checksum;};
static u32 parseResetReason(const void* buffer,DWORD bytes){NativeResetData reason;if(!buffer||bytes!=sizeof(reason))return 0x80000000u;memcpy(&reason,buffer,sizeof(reason));return reason.magic==0x4d335253&&reason.version==1&&reason.checksum==(reason.magic^reason.version^reason.code)?reason.code:0x80000000u;}
extern "C" u32 OSGetResetCode(void){DWORD bytes=0;if(XGetLaunchDataSize(&bytes)!=ERROR_SUCCESS||bytes!=sizeof(NativeResetData))return 0x80000000u;NativeResetData reason;if(XGetLaunchData(&reason,sizeof(reason))!=ERROR_SUCCESS)return 0x80000000u;return parseResetReason(&reason,sizeof(reason));}
extern "C" int Melee360ResetReasonProbe(void){NativeResetData data={0x4d335253,1,37,0x4d335253^1^37};if(parseResetReason(0,0)!=0x80000000u||parseResetReason(&data,sizeof(data))!=37)return 0;data.checksum^=1;if(parseResetReason(&data,sizeof(data))!=0x80000000u)return 0;/* Exercise actual launch-data APIs without initiating a relaunch. */OSGetResetCode();return 1;}
