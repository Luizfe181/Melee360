/* Single-owner DVD boundary. Callbacks run on the next pump, never inline.
 * File reads are blocking in the pump; optical hardware timing is not emulated. */
#include <dolphin/dvd.h>
#include <dolphin/os.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../compat/generated/dvd_manifest.h"
#define DVD_SLOTS 32
typedef struct OpenDVD {DVDFileInfo* info;FILE* file;int entry;int pending;int priority;unsigned int serial;} OpenDVD;
static OpenDVD slots[DVD_SLOTS];
static unsigned int serial;
static DVDDiskID diskID;
#ifdef _XBOX
static char assetRoot[512]="game:\\data";
#else
static char assetRoot[512]="C:\\Users\\luizf\\Documents\\melee_extraido";
#endif
static OpenDVD* slotFor(DVDFileInfo* info){int i;for(i=0;i<DVD_SLOTS;++i)if(info&&slots[i].info==info)return &slots[i];return NULL;}
void DVDInit(void){memcpy(&diskID,dvdDiskID,sizeof(diskID));}
DVDDiskID* DVDGetCurrentDiskID(void){return &diskID;}
s32 DVDConvertPathToEntrynum(const char* path){unsigned int i;if(!path)return -1;while(*path=='/')++path;
 for(i=0;i<sizeof(dvdEntries)/sizeof(dvdEntries[0]);++i)if(!strcmp(path,dvdEntries[i].path))return (s32)i;return -1;}
BOOL DVDFastOpen(s32 entry,DVDFileInfo* info){int i;char path[1024];char* normalized;FILE* file;long size;OpenDVD* existing=slotFor(info);
 if(!info||(existing&&existing->pending)||entry<0||entry>=(s32)(sizeof(dvdEntries)/sizeof(dvdEntries[0]))||dvdEntries[entry].directory)return 0;
 if(existing)i=(int)(existing-slots);else{for(i=0;i<DVD_SLOTS&&slots[i].info;++i){}if(i==DVD_SLOTS)return 0;}
 if(strlen(assetRoot)+strlen(dvdEntries[entry].file)+2>sizeof(path))return 0;
 sprintf(path,"%s\\%s",assetRoot,dvdEntries[entry].file);for(normalized=path;*normalized;++normalized)if(*normalized=='/')*normalized='\\';file=fopen(path,"rb");if(!file)return 0;
 if(fseek(file,0,SEEK_END)||(size=ftell(file))<0||(unsigned long)size!=dvdEntries[entry].length){fclose(file);return 0;}
 rewind(file);if(existing){fclose(existing->file);memset(existing,0,sizeof(*existing));}memset(info,0,sizeof(*info));info->startAddr=dvdEntries[entry].offset;info->length=dvdEntries[entry].length;info->cb.state=DVD_STATE_END;
 slots[i].info=info;slots[i].file=file;slots[i].entry=entry;slots[i].pending=0;return 1;}
BOOL DVDOpen(char* path,DVDFileInfo* info){return DVDFastOpen(DVDConvertPathToEntrynum(path),info);}
BOOL DVDClose(DVDFileInfo* info){OpenDVD* s=slotFor(info);if(!s||s->pending)return 0;fclose(s->file);memset(s,0,sizeof(*s));return 1;}
BOOL DVDCheckDisk(void){char path[1024];FILE* f;sprintf(path,"%s\\PlMr.dat",assetRoot);f=fopen(path,"rb");if(!f)return 0;fclose(f);return 1;}
long DVDGetDriveStatus(void){int i;for(i=0;i<DVD_SLOTS;++i)if(slots[i].pending)return DVD_STATE_BUSY;return DVDCheckDisk()?DVD_STATE_END:DVD_STATE_NO_DISK;}
long DVDGetCommandBlockStatus(DVDCommandBlock* block){return block?block->state:DVD_STATE_FATAL_ERROR;}
long DVDGetFileInfoStatus(DVDFileInfo* info){return info?info->cb.state:DVD_STATE_FATAL_ERROR;}
static long readSlot(OpenDVD* s,void* addr,long length,long offset){unsigned long available,want;size_t got;
 if(!s||!addr||length<0||offset<0||(unsigned long)offset>s->info->length||(unsigned long)length>s->info->length-(unsigned long)offset+31)return -1;
 available=s->info->length-(unsigned long)offset;want=(unsigned long)length<available?(unsigned long)length:available;
 if(fseek(s->file,offset,SEEK_SET))return -1;got=fread(addr,1,want,s->file);if(got!=want)return -1;
 if((unsigned long)length>want)memset((unsigned char*)addr+want,0,(unsigned long)length-want);return length;}
BOOL DVDReadAsyncPrio(DVDFileInfo* info,void* addr,s32 length,s32 offset,DVDCallback cb,s32 priority){OpenDVD* s=slotFor(info);
 if(!s||s->pending||!addr||((u32)addr&31)||length<0||offset<0||((u32)offset&3)||((u32)length&31)||priority<0||priority>3||(u32)offset>info->length||(u32)length>info->length-(u32)offset+31){OSReport("DVD async rejected: slot=%p pending=%d addr=%p length=%d offset=%d priority=%d filelen=%u\n",s,s?s->pending:0,addr,length,offset,priority,info?info->length:0);return 0;}
 info->cb.command=1;info->cb.state=DVD_STATE_WAITING;info->cb.addr=addr;info->cb.length=length;info->cb.offset=offset;info->cb.transferredSize=info->cb.currTransferSize=0;info->callback=cb;
 s->pending=1;s->priority=priority;s->serial=serial++;return 1;}
/* At most one completion per frame: callbacks may safely enqueue another read. */
void Melee360DVDPump(void){int i;OpenDVD* best=NULL;DVDFileInfo* info;DVDCallback cb;long result;
 for(i=0;i<DVD_SLOTS;++i)if(slots[i].pending&&(!best||slots[i].priority<best->priority||(slots[i].priority==best->priority&&slots[i].serial<best->serial)))best=&slots[i];
 if(!best)return;info=best->info;info->cb.state=DVD_STATE_BUSY;result=readSlot(best,info->cb.addr,info->cb.length,info->cb.offset);
 best->pending=0;info->cb.state=result<0?DVD_STATE_FATAL_ERROR:DVD_STATE_END;info->cb.transferredSize=info->cb.currTransferSize=result<0?0:result;cb=info->callback;if(cb)cb(result,info);}
long DVDReadPrio(DVDFileInfo* info,void* addr,long length,long offset,long priority){OpenDVD* s=slotFor(info);long result;(void)priority;if(!s||s->pending)return -1;
 info->cb.state=DVD_STATE_BUSY;result=readSlot(s,addr,length,offset);info->cb.state=result<0?DVD_STATE_FATAL_ERROR:DVD_STATE_END;info->cb.transferredSize=info->cb.currTransferSize=result<0?0:result;return result;}
s32 DVDGetTransferredSize(DVDFileInfo* info){return info?(s32)info->cb.transferredSize:0;}
int Melee360DVDSetRoot(const char* root){int i;if(!root||strlen(root)>=sizeof(assetRoot))return 0;for(i=0;i<DVD_SLOTS;++i)if(slots[i].info)return 0;strcpy(assetRoot,root);return 1;}
