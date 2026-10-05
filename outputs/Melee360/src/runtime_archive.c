#include "runtime_archive.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
static unsigned int be32(const unsigned char* p){return (unsigned int)p[0]<<24|(unsigned int)p[1]<<16|(unsigned int)p[2]<<8|p[3];}
int Melee360ValidateNativeArchive(const unsigned char* raw,unsigned int length){unsigned int ds,nr,np,ne,i,table,names;unsigned char* seen;unsigned __int64 end;if(!raw||length<32||be32(raw)!=length)return 0;ds=be32(raw+4);nr=be32(raw+8);np=be32(raw+12);ne=be32(raw+16);if(ds>length-32||nr>length/4||np>length/8||ne>length/8)return 0;end=32ULL+ds+4ULL*nr+8ULL*np+8ULL*ne;if(end>length||ds<4)return 0;table=32+ds+4*nr;names=(unsigned int)end;
 seen=(unsigned char*)calloc((ds+31u)/32u,1);if(!seen)return 0;for(i=0;i<nr;++i){unsigned int offset=be32(raw+32+ds+i*4),index=offset/4;if((offset&3)||offset>ds-4||be32(raw+32+offset)>=ds){free(seen);return 0;}if(seen[index/8]&(1u<<(index%8))){free(seen);return 0;}seen[index/8]|=(unsigned char)(1u<<(index%8));}free(seen);
 for(i=0;i<np+ne;++i){unsigned int at=table+8*i,offset=be32(raw+at),name=be32(raw+at+4);if(offset>=ds||name>=length-names||!memchr(raw+names+name,0,length-names-name))return 0;if(i>=np){unsigned int steps=0;while(offset!=0xffffffffu){if((offset&3)||offset>ds-4||++steps>ds/4)return 0;offset=be32(raw+32+offset);}}}return 1;}
struct ArchiveSlot{char filename[32];unsigned char* raw;HSD_Archive archive;};
static struct ArchiveSlot slots[8];
int Melee360RuntimeArchiveLoad(const char* name,HSD_Archive** result){unsigned int i;char path[128];FILE* file;long length;unsigned char* raw;unsigned int endian=0x01020304u;if(!result)return 0;*result=0;if(sizeof(void*)!=4||*(unsigned char*)&endian!=1)return 0;if(!name||!name[0]||strlen(name)>=32||strchr(name,'/')||strchr(name,'\\')||strchr(name,':')||strstr(name,".."))return 0;
 for(i=0;i<8;++i)if(slots[i].raw&&!strcmp(slots[i].filename,name)){*result=&slots[i].archive;return 1;}for(i=0;i<8;++i)if(!slots[i].raw)break;if(i==8)return 0;
 sprintf_s(path,sizeof(path),"game:\\data\\%s",name);file=fopen(path,"rb");if(!file)return 0;if(fseek(file,0,SEEK_END)!=0){fclose(file);return 0;}length=ftell(file);if(length<32||length>8*1024*1024||fseek(file,0,SEEK_SET)!=0){fclose(file);return 0;}raw=(unsigned char*)_aligned_malloc(length,32);if(!raw){fclose(file);return 0;}if(fread(raw,1,length,file)!=(size_t)length){fclose(file);_aligned_free(raw);return 0;}fclose(file);
 /* Original parser requires a 32-bit big-endian target. Extern initialization
  * follows lbArchive_InitializeDAT: original HSD APIs bind the chains to NULL.
  * This is the game's initial archive state, not a missing-function stub. */
 if(!Melee360ValidateNativeArchive(raw,length)||HSD_ArchiveParse(&slots[i].archive,raw,length)!=0){_aligned_free(raw);return 0;}
 {int ext=0;const char* symbol;while((symbol=HSD_ArchiveGetExtern(&slots[i].archive,ext++))!=NULL)HSD_ArchiveLocateExtern(&slots[i].archive,symbol,NULL);}
 slots[i].raw=raw;strcpy_s(slots[i].filename,32,name);*result=&slots[i].archive;return 1;
}
