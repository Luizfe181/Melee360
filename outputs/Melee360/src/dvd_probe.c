#include <dolphin/dvd.h>
#include <string.h>
extern void OSReport(const char*,...);
void Melee360DVDPump(void);
static int completed;static s32 completion;
static void finish(s32 result,DVDFileInfo* info){completion=result;++completed;if(info->cb.state!=DVD_STATE_END)completion=-2;}
int Melee360DVDProbe(void){DVDFileInfo f;unsigned char storage[63];unsigned char* bytes=(unsigned char*)(((u32)storage+31)&~31u);s32 entry;u32 archiveSize;
 DVDInit();if(memcmp(DVDGetCurrentDiskID()->gameName,"GALE",4)||memcmp(DVDGetCurrentDiskID()->company,"01",2)||!DVDCheckDisk()) {OSReport("DVD probe failure step 1\n");return 0;}
 entry=DVDConvertPathToEntrynum("/PlMr.dat");if(entry<0||entry!=DVDConvertPathToEntrynum("PlMr.dat")||DVDConvertPathToEntrynum("nonexistent.dat")!=-1) {OSReport("DVD probe failure step 2\n");return 0;}
 if(!DVDFastOpen(entry,&f)||f.length<32) {OSReport("DVD probe failure step 3\n");return 0;}completed=0;completion=-3;
 if(!DVDReadAsyncPrio(&f,bytes,32,0,finish,2)||completed||f.cb.state!=DVD_STATE_WAITING||DVDClose(&f)) {OSReport("DVD probe failure step 4\n");return 0;}
 Melee360DVDPump();if(completed!=1||completion!=32||DVDGetTransferredSize(&f)!=32) {OSReport("DVD probe failure step 5\n");return 0;}
 archiveSize=((u32)bytes[0]<<24)|((u32)bytes[1]<<16)|((u32)bytes[2]<<8)|bytes[3];
 if(archiveSize!=f.length||!DVDClose(&f)) {OSReport("DVD probe failure step 6\n");return 0;}
 completed=0;completion=-3;
 if(!DVDFastOpen(DVDConvertPathToEntrynum("/audio/1padv.ssm"),&f)||!DVDReadAsyncPrio(&f,bytes,32,0,finish,2)||completed){OSReport("DVD nested path queue FAILED\n");return 0;}
 Melee360DVDPump();if(completed!=1||completion!=32||!DVDClose(&f)){OSReport("DVD nested path read FAILED\n");return 0;}
 return 1;
}
