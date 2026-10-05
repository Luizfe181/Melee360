#include <dolphin/thp/thp.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
int Melee360THPWorkLayoutProbe(void);
static u32 be32(const u8* p){return ((u32)p[0]<<24)|((u32)p[1]<<16)|((u32)p[2]<<8)|p[3];}
int Melee360THPHeaderProbe(void){FILE* f=fopen("game:\\data\\MvOpen.mth","rb");u8 header[64],status;u8* frame=0;u8* work=0;int result=0;THPDec_8032FD40_Data desc;u16 size[2];u32 first,length;THPFileInfo* info;
 if(!f)return -1;if(!Melee360THPWorkLayoutProbe()){result=-14;goto done;}if(fread(header,1,64,f)!=64){result=-2;goto done;}first=be32(header+32);length=be32(header+40);if(length<8||length>2*1024*1024){result=-3;goto done;}frame=(u8*)malloc(length);if(!frame){result=-4;goto done;}if(fseek(f,first,SEEK_SET)||fread(frame,1,length,f)!=length){result=-5;goto done;}
 if(!THPDec_8032F8D4(frame+4,&desc)||desc.val1!=be32(header+16)||desc._pad!=be32(header+20)||desc.val2!=4){result=-6;goto done;}
 size[0]=desc.val1;size[1]=desc._pad;length=THPDec_8032FD40(&desc,size[1]);if(length!=0x4028+(u32)size[0]*size[1]*3/2){result=-7;goto done;}work=(u8*)_aligned_malloc(length+32,32);if(!work){result=-8;goto done;}memset(work,0xCD,length+32);info=THPVideoDecode(size,&status,(THPFileInfo*)work,frame+4,&desc);
 if(info!=(THPFileInfo*)work||status!=0||info->xPixelSize!=size[0]||info->yPixelSize!=size[1]||info->nComponents!=3||!info->validHuffmanTabs||!info->validQuantTabs||info->MCUsPerRow!=size[0]/16||info->scratch>work+length||((u32)info->mcuBuffer[0]&31)){result=-9;goto done;}
 {unsigned i;for(i=0;i<32;++i)if(work[length+i]!=0xCD){result=-10;goto done;}}
 // Parser errors with valid allocation, avoiding deliberately truncated unsafe original inputs.
 {u8 bad[4]={0,0,0,0};if(THPDec_8032F8D4(bad,&desc)!=0){result=-11;goto done;}if(THPVideoDecode(size,&status,(THPFileInfo*)work,bad,&desc)!=0||status!=3){result=-12;goto done;}}
 desc.val2=2;if(THPDec_8032FD40(&desc,16)!=0){result=-13;goto done;}result=1;
done:if(work)_aligned_free(work);free(frame);fclose(f);return result;
}
