#include <dolphin/card.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../compat/generated/card_icons.inc"
typedef char card_info_layout[sizeof(CARDFileInfo)==20?1:-1];
typedef char card_stat_layout[sizeof(CARDStat)==108?1:-1];
/* Private port container; not a raw GameCube memory-card image or GCI file.
 * Same-target byte order is checked explicitly. All filenames stay metadata:
 * game-provided names never become host filesystem paths. */
#define CAPACITY (2u*1024u*1024u-5u*8192u)
#define MAX_HANDLES 32
typedef struct Entry {CARDStat stat;unsigned char* data;} Entry;
typedef struct Request {int kind,index;CARDCallback callback;CARDFileInfo* info;void* buffer;s32 length,offset;u32 size;char name[33],newName[33];CARDStat stat;} Request;
typedef struct Card {int mounted,formatted,result,xferred;Entry entries[CARD_MAX_FILE];Request request;} Card;
typedef struct Handle {CARDFileInfo* info;int channel,index;} Handle;
static Card cards[2];static Handle handles[MAX_HANDLES];
static char prefix[384]="game:\\card-slot";
static u32 stamp(void){return (u32)OSTicksToSeconds(OSGetTime());}
enum {MOUNT=1,CHECK,FORMAT,CREATE,DELETE_FILE,RENAME_FILE,STATUS,READ_FILE,WRITE_FILE};
static int validChannel(int ch){return ch>=0&&ch<2;}
static int validName(const char* name){size_t n;if(!name)return 0;n=strlen(name);return n>0&&n<=32;}
static int findEntry(Card* c,const char* name){int i;for(i=0;i<CARD_MAX_FILE;++i)if(c->entries[i].data&&!strncmp(c->entries[i].stat.fileName,name,32))return i;return -1;}
static u32 used(Card* c){int i;u32 bytes=0;for(i=0;i<CARD_MAX_FILE;++i)if(c->entries[i].data)bytes+=c->entries[i].stat.length;return bytes;}
static void clear(Card* c){int i;for(i=0;i<CARD_MAX_FILE;++i){free(c->entries[i].data);memset(&c->entries[i],0,sizeof(Entry));}c->formatted=0;}
static void paths(int channel,char* mainPath,char* temporary,char* backup){sprintf(mainPath,"%s-%c.m360card",prefix,'a'+channel);sprintf(temporary,"%s.tmp",mainPath);sprintf(backup,"%s.bak",mainPath);}
static u32 hash(u32 h,const void* data,u32 bytes){const u8* p=(const u8*)data;while(bytes--)h=(h^*p++)*16777619u;return h;}
static int readImage(Card* c,const char* path){
    FILE* file=fopen(path,"rb");char magic[8];u32 endian,count,i,index,sum=2166136261u,stored;int result=CARD_RESULT_BROKEN;
    if(!file)return CARD_RESULT_BROKEN;
    clear(c);
    if(fread(magic,1,8,file)!=8||memcmp(magic,"M360CARD",8)||fread(&endian,4,1,file)!=1||endian!=0x01020304||fread(&count,4,1,file)!=1||count>CARD_MAX_FILE)goto end;
    sum=hash(sum,&count,4);
    for(i=0;i<count;++i){Entry* e;int j;
        if(fread(&index,4,1,file)!=1||index>=CARD_MAX_FILE||c->entries[index].data)goto end;
        e=&c->entries[index];if(fread(&e->stat,sizeof(e->stat),1,file)!=1||!e->stat.length||e->stat.length%8192||e->stat.length>CAPACITY-used(c)||!e->stat.fileName[0])goto end;
        for(j=0;j<CARD_MAX_FILE;++j)if(c->entries[j].data&&!memcmp(c->entries[j].stat.fileName,e->stat.fileName,32))goto end;
        e->data=(unsigned char*)malloc(e->stat.length);if(!e->data){result=CARD_RESULT_IOERROR;goto end;}
        if(fread(e->data,1,e->stat.length,file)!=e->stat.length)goto end;
        sum=hash(hash(hash(sum,&index,4),&e->stat,sizeof(e->stat)),e->data,e->stat.length);
    }
    if(fread(&stored,4,1,file)!=1||stored!=sum||fgetc(file)!=EOF)goto end;
    result=CARD_RESULT_READY;c->formatted=1;
end: fclose(file);if(result!=CARD_RESULT_READY)clear(c);return result;
}
static int load(Card* c,int channel){char path[420],tmp[424],bak[424];int result;paths(channel,path,tmp,bak);result=readImage(c,path);if(result==CARD_RESULT_BROKEN)result=readImage(c,bak);return result;}
static int persist(Card* c,int channel){
    char path[420],tmp[424],bak[424];FILE* file;u32 endian=0x01020304,count=0,index,sum=2166136261u;int ok,existed;
    paths(channel,path,tmp,bak);file=fopen(tmp,"wb");if(!file)return CARD_RESULT_IOERROR;
    for(index=0;index<CARD_MAX_FILE;++index)if(c->entries[index].data)++count;
    ok=fwrite("M360CARD",1,8,file)==8&&fwrite(&endian,4,1,file)==1&&fwrite(&count,4,1,file)==1;sum=hash(sum,&count,4);
    for(index=0;ok&&index<CARD_MAX_FILE;++index){Entry* e=&c->entries[index];if(!e->data)continue;
        ok=fwrite(&index,4,1,file)==1&&fwrite(&e->stat,sizeof(e->stat),1,file)==1&&fwrite(e->data,1,e->stat.length,file)==e->stat.length;
        sum=hash(hash(hash(sum,&index,4),&e->stat,sizeof(e->stat)),e->data,e->stat.length);
    }
    ok=ok&&fwrite(&sum,4,1,file)==1;if(fflush(file))ok=0;if(fclose(file))ok=0;
    if(!ok){remove(tmp);return CARD_RESULT_IOERROR;}
    file=fopen(path,"rb");existed=file!=0;if(file)fclose(file);
    if(existed){remove(bak);if(rename(path,bak)){remove(tmp);return CARD_RESULT_IOERROR;}}
    if(rename(tmp,path)){if(existed)rename(bak,path);remove(tmp);return CARD_RESULT_IOERROR;}
    return CARD_RESULT_READY;
}
static Handle* getHandle(CARDFileInfo* info){int i;for(i=0;i<MAX_HANDLES;++i)if(handles[i].info==info)return &handles[i];return 0;}
static int openEntry(int ch,int index,CARDFileInfo* info){int i;Card* c=&cards[ch];
    if(!info)return CARD_RESULT_FATAL_ERROR;
    if(index<0||index>=CARD_MAX_FILE||!c->entries[index].data)return CARD_RESULT_NOFILE;
    if(getHandle(info))return CARD_RESULT_BUSY;
    for(i=0;i<MAX_HANDLES;++i)if(!handles[i].info){handles[i].info=info;handles[i].channel=ch;handles[i].index=index;memset(info,0,sizeof(*info));info->chan=ch;info->fileNo=index;info->length=c->entries[index].stat.length;return 0;}
    return CARD_RESULT_LIMIT;
}
static int hasOpen(int ch,int index){int i;for(i=0;i<MAX_HANDLES;++i)if(handles[i].info&&handles[i].channel==ch&&(index<0||handles[i].index==index))return 1;return 0;}
static int ready(int ch){if(!validChannel(ch))return CARD_RESULT_FATAL_ERROR;if(cards[ch].request.kind)return CARD_RESULT_BUSY;if(!cards[ch].mounted)return CARD_RESULT_NOCARD;if(!cards[ch].formatted)return CARD_RESULT_BROKEN;return 0;}
static int execute(int ch,Request* r){Card* c=&cards[ch];Entry* e;int index,result=0,i;
    c->xferred=0;
    switch(r->kind){
    case MOUNT:c->mounted=1;return load(c,ch);
    case CHECK:return load(c,ch);
    case FORMAT:if(hasOpen(ch,-1))return CARD_RESULT_BUSY;clear(c);c->formatted=1;break;
    case CREATE:
        if(findEntry(c,r->name)>=0)return CARD_RESULT_EXIST;
        if(r->size>CAPACITY-used(c))return CARD_RESULT_INSSPACE;
        for(index=0;index<CARD_MAX_FILE&&c->entries[index].data;++index);if(index==CARD_MAX_FILE)return CARD_RESULT_NOENT;
        /* Reserve the handle before persisting, so a successful create always
         * returns a usable fileInfo. Roll back allocation on handle exhaustion. */
        e=&c->entries[index];memset(&e->stat,0,sizeof(e->stat));e->stat.length=r->size;memcpy(e->stat.fileName,r->name,strlen(r->name));memcpy(e->stat.gameName,"GALE",4);memcpy(e->stat.company,"01",2);e->stat.iconAddr=e->stat.commentAddr=0xffffffffu;
        e->data=(unsigned char*)calloc(1,r->size);if(!e->data)return CARD_RESULT_IOERROR;
        e->stat.time=stamp();
        result=openEntry(ch,index,r->info);if(result){free(e->data);memset(e,0,sizeof(*e));return result;}break;
    case DELETE_FILE:index=findEntry(c,r->name);if(index<0)return CARD_RESULT_NOFILE;if(hasOpen(ch,index))return CARD_RESULT_BUSY;free(c->entries[index].data);memset(&c->entries[index],0,sizeof(Entry));break;
    case RENAME_FILE:index=findEntry(c,r->name);if(index<0)return CARD_RESULT_NOFILE;if(findEntry(c,r->newName)>=0)return CARD_RESULT_EXIST;memset(c->entries[index].stat.fileName,0,32);memcpy(c->entries[index].stat.fileName,r->newName,strlen(r->newName));break;
    case STATUS:e=&c->entries[r->index];e->stat.bannerFormat=r->stat.bannerFormat;e->stat.iconAddr=r->stat.iconAddr;e->stat.iconFormat=r->stat.iconFormat;e->stat.iconSpeed=r->stat.iconSpeed;e->stat.commentAddr=r->stat.commentAddr;e->stat.time=stamp();break;
    case READ_FILE:e=&c->entries[r->index];memcpy(r->buffer,e->data+r->offset,r->length);c->xferred=r->length;r->info->offset=r->offset+r->length;return 0;
    case WRITE_FILE:e=&c->entries[r->index];memcpy(e->data+r->offset,r->buffer,r->length);e->stat.time=stamp();c->xferred=r->length;r->info->offset=r->offset+r->length;break;
    default:return CARD_RESULT_FATAL_ERROR;
    }
    result=persist(c,ch);
    if(result==0&&r->kind==FORMAT){char path[420],tmp[424],backup[424];paths(ch,path,tmp,backup);remove(backup);}
    if(result){/* Failed writes do not leave a seemingly valid dirty card. */
        for(i=0;i<MAX_HANDLES;++i)if(handles[i].info&&handles[i].channel==ch){handles[i].info->fileNo=-1;handles[i].info=0;}
        load(c,ch);c->xferred=0;
    }return result;
}
static int queue(int ch,Request* r){int result;
    if(!validChannel(ch))return CARD_RESULT_FATAL_ERROR;
    if(cards[ch].request.kind)return CARD_RESULT_BUSY;
    if(r->kind!=MOUNT&&r->kind!=FORMAT){result=ready(ch);if(result)return result;}
    if(r->kind==FORMAT&&!cards[ch].mounted)return CARD_RESULT_NOCARD;
    cards[ch].request=*r;cards[ch].result=CARD_RESULT_BUSY;return 0;
}
void Melee360CardPump(void){int ch;for(ch=0;ch<2;++ch)if(cards[ch].request.kind){Request r=cards[ch].request;int result=execute(ch,&r);memset(&cards[ch].request,0,sizeof(Request));cards[ch].result=result;if(r.callback)r.callback(ch,result);}}
int Melee360CardSetRoot(const char* root){if(!root||strlen(root)>380||cards[0].mounted||cards[1].mounted||cards[0].request.kind||cards[1].request.kind)return 0;strcpy(prefix,root);return 1;}
void CARDInit(void){/* Static initialization is intentionally idempotent. */}
BOOL CARDProbe(long ch){return validChannel(ch);}
s32 CARDProbeEx(s32 ch,s32* memSize,s32* sectorSize){if(!validChannel(ch))return CARD_RESULT_NOCARD;if(memSize)*memSize=16;if(sectorSize)*sectorSize=8192;return 0;}
s32 CARDGetResultCode(s32 ch){return validChannel(ch)?cards[ch].result:CARD_RESULT_FATAL_ERROR;}
long CARDGetXferredBytes(long ch){return validChannel(ch)?cards[ch].xferred:CARD_RESULT_FATAL_ERROR;}
s32 CARDMountAsync(s32 ch,void* area,CARDCallback detach,CARDCallback callback){Request r;int result;(void)detach;if(!area||((u32)area&31))return CARD_RESULT_FATAL_ERROR;if(validChannel(ch)&&cards[ch].mounted)return CARD_RESULT_BUSY;memset(&r,0,sizeof(r));r.kind=MOUNT;r.callback=callback;result=queue(ch,&r);return result;}
s32 CARDUnmount(s32 ch){if(!validChannel(ch))return CARD_RESULT_FATAL_ERROR;if(cards[ch].request.kind||hasOpen(ch,-1))return CARD_RESULT_BUSY;clear(&cards[ch]);cards[ch].mounted=0;return 0;}
s32 CARDCheckAsync(s32 ch,CARDCallback cb){Request r;if(validChannel(ch)&&hasOpen(ch,-1))return CARD_RESULT_BUSY;memset(&r,0,sizeof(r));r.kind=CHECK;r.callback=cb;return queue(ch,&r);}
s32 CARDFormatAsync(s32 ch,CARDCallback cb){Request r;if(validChannel(ch)&&hasOpen(ch,-1))return CARD_RESULT_BUSY;memset(&r,0,sizeof(r));r.kind=FORMAT;r.callback=cb;return queue(ch,&r);}
s32 CARDFreeBlocks(s32 ch,s32* bytes,s32* files){int result=ready(ch),i,count=0;if(result)return result;for(i=0;i<CARD_MAX_FILE;++i)if(cards[ch].entries[i].data)++count;if(bytes)*bytes=CAPACITY-used(&cards[ch]);if(files)*files=CARD_MAX_FILE-count;return 0;}
s32 CARDFastOpen(s32 ch,s32 index,CARDFileInfo* info){int result=ready(ch);return result?result:openEntry(ch,index,info);}
s32 CARDOpen(s32 ch,const char* name,CARDFileInfo* info){int result=ready(ch);if(result)return result;if(!validName(name))return CARD_RESULT_NAMETOOLONG;return openEntry(ch,findEntry(&cards[ch],name),info);}
s32 CARDClose(CARDFileInfo* info){Handle* h=getHandle(info);if(!h)return CARD_RESULT_NOFILE;if(cards[h->channel].request.kind)return CARD_RESULT_BUSY;h->info=0;info->fileNo=-1;return 0;}
s32 CARDCreateAsync(s32 ch,const char* name,u32 size,CARDFileInfo* info,CARDCallback cb){Request r;if(!validName(name))return CARD_RESULT_NAMETOOLONG;if(!info||getHandle(info)||!size||size%8192||size>CAPACITY)return CARD_RESULT_FATAL_ERROR;memset(&r,0,sizeof(r));r.kind=CREATE;r.size=size;r.info=info;r.callback=cb;strcpy(r.name,name);return queue(ch,&r);}
s32 CARDDeleteAsync(s32 ch,char* name,CARDCallback cb){Request r;if(!validName(name))return CARD_RESULT_NAMETOOLONG;memset(&r,0,sizeof(r));r.kind=DELETE_FILE;r.callback=cb;strcpy(r.name,name);return queue(ch,&r);}
s32 CARDRenameAsync(s32 ch,const char* name,const char* newName,CARDCallback cb){Request r;if(!validName(name)||!validName(newName))return CARD_RESULT_NAMETOOLONG;memset(&r,0,sizeof(r));r.kind=RENAME_FILE;r.callback=cb;strcpy(r.name,name);strcpy(r.newName,newName);return queue(ch,&r);}
s32 CARDGetStatus(s32 ch,s32 index,CARDStat* stat){CARDDir dir;int result=ready(ch);if(result)return result;if(!stat||index<0||index>=CARD_MAX_FILE||!cards[ch].entries[index].data)return CARD_RESULT_NOFILE;*stat=cards[ch].entries[index].stat;memset(&dir,0,sizeof(dir));dir.iconAddr=stat->iconAddr;dir.bannerFormat=stat->bannerFormat;dir.iconFormat=stat->iconFormat;dir.iconSpeed=stat->iconSpeed;UpdateIconOffsets(&dir,stat);return 0;}
s32 CARDSetStatusAsync(s32 ch,s32 index,CARDStat* stat,CARDCallback cb){
    Request r;int result=ready(ch);if(result)return result;
    if(!stat||index<0||index>=CARD_MAX_FILE||!cards[ch].entries[index].data)return CARD_RESULT_NOFILE;
    if((stat->iconAddr!=0xffffffffu&&stat->iconAddr>=CARD_READ_SIZE)||
       (stat->commentAddr!=0xffffffffu&&(stat->commentAddr>cards[ch].entries[index].stat.length-64||stat->commentAddr%8192>8192-64)))return CARD_RESULT_FATAL_ERROR;
    memset(&r,0,sizeof(r));r.kind=STATUS;r.index=index;r.stat=*stat;r.callback=cb;return queue(ch,&r);
}
static int io(CARDFileInfo* info,void* buffer,s32 length,s32 offset,CARDCallback cb,int kind,int async){Handle* h=getHandle(info);Request r;int result,alignment=kind==WRITE_FILE?8192:512;
    if(!h)return CARD_RESULT_NOFILE;result=ready(h->channel);if(result)return result;
    if(!buffer||((u32)buffer&31)||length<=0||length%alignment||offset<0||offset%alignment||(u32)offset>cards[h->channel].entries[h->index].stat.length||(u32)length>cards[h->channel].entries[h->index].stat.length-(u32)offset)return CARD_RESULT_FATAL_ERROR;
    memset(&r,0,sizeof(r));r.kind=kind;r.index=h->index;r.info=info;r.buffer=buffer;r.length=length;r.offset=offset;r.callback=cb;
    if(async)return queue(h->channel,&r);result=execute(h->channel,&r);cards[h->channel].result=result;return result;
}
s32 CARDReadAsync(CARDFileInfo* i,void* b,s32 n,s32 o,CARDCallback cb){return io(i,b,n,o,cb,READ_FILE,1);}
long CARDRead(CARDFileInfo* i,void* b,long n,long o){return io(i,b,n,o,0,READ_FILE,0);}
s32 CARDWriteAsync(CARDFileInfo* i,void* b,s32 n,s32 o,CARDCallback cb){return io(i,b,n,o,cb,WRITE_FILE,1);}
s32 CARDWrite(CARDFileInfo* i,void* b,s32 n,s32 o){return io(i,b,n,o,0,WRITE_FILE,0);}
unsigned Melee360CardPending(void){return (cards[0].request.kind?1u:0u)+(cards[1].request.kind?1u:0u);}
