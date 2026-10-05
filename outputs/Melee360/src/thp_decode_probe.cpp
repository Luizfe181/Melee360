#include <xtl.h>
#include <stdio.h>
#include <vector>
#include <malloc.h>
#include "mth_decode.h"
#include "platform_log.h"
extern "C" {
#include <dolphin/thp/thp.h>
}
static u32 decodeBe32(const u8* p){return (u32)p[0]<<24|(u32)p[1]<<16|(u32)p[2]<<8|p[3];}
static u8 sampleTile(const u8* p,unsigned width,unsigned x,unsigned y){return p[(y/4)*(width/8)*32+(x/8)*32+(y%4)*8+x%8];}
static int clampChannel(int value){return value<0?0:value>255?255:value;}
extern "C" int Melee360THPPixelProbe(void){FILE* f=fopen("game:\\data\\MvOpen.mth","rb");if(!f)return 0;u8 header[64];if(fread(header,1,64,f)!=64){fclose(f);return 0;}unsigned length=decodeBe32(header+40),offset=decodeBe32(header+32);bool ok=true;unsigned tested=0,pixels=0,maxError=0;const unsigned targets[]={0,90,300};std::vector<u8> frame;for(unsigned index=0;index<=300&&ok;++index){if(length<8||length>2*1024*1024){ok=false;break;}frame.resize(length);if(fseek(f,offset,SEEK_SET)||fread(&frame[0],1,length,f)!=length){ok=false;break;}offset+=length;unsigned next=decodeBe32(&frame[0]);if(index==targets[tested]){THPDec_8032FD40_Data desc;ok=THPDec_8032F8D4(&frame[4],&desc)!=0;if(!ok)break;u16 dimensions[2]={desc.val1,desc._pad};unsigned w=dimensions[0],h=dimensions[1],yBytes=w*h,chroma=yBytes/4,workBytes=THPDec_8032FD40(&desc,(u16)h);u8* work=(u8*)_aligned_malloc(workBytes,32);u8* planes=(u8*)_aligned_malloc(yBytes+2*chroma+32,32);std::vector<u32> reference(yBytes);if(!work||!planes){ok=false;if(work)_aligned_free(work);if(planes)_aligned_free(planes);break;}
 for(unsigned entry=0;entry<2&&ok;++entry){u8 status;THPFileInfo* info=THPVideoDecode(dimensions,&status,(THPFileInfo*)work,&frame[4],&desc);ok=info&&status==0;if(!ok)break;memset(planes,0xcd,yBytes+2*chroma+32);if(entry==0)THPDec_80331340(info,planes,planes+yBytes,planes+yBytes+chroma);else THPDec_803313D0(info,planes,planes+yBytes,planes+yBytes+chroma,w);ok=info->x8EE==h&&info->tileY==planes+yBytes;for(unsigned i=0;i<32;++i)ok=ok&&planes[yBytes+2*chroma+i]==0xcd;
 if(!Melee360DecodeMth(&frame[4],(u32)frame.size()-4,&reference[0],w,h))ok=false;for(unsigned y=0;y<h&&ok;++y)for(unsigned x=0;x<w;++x){int yy=sampleTile(planes,w,x,y),u=sampleTile(planes+yBytes,w/2,x/2,y/2)-128,v=sampleTile(planes+yBytes+chroma,w/2,x/2,y/2)-128;int base=yy*65536+32768;int result[3]={clampChannel((base+91881*v)>>16),clampChannel((base-22554*u-46802*v)>>16),clampChannel((base+116130*u)>>16)};u32 expected=reference[y*w+x];for(int c=0;c<3;++c){unsigned error=(unsigned)abs(result[c]-(int)((expected>>(16-c*8))&255));if(error>maxError)maxError=error;if(error>4)ok=false;}++pixels;}}
 _aligned_free(work);_aligned_free(planes);++tested;}
 length=next;}
 fclose(f);char msg[180];sprintf_s(msg,sizeof(msg),"THP native pixels: %s frames=%u entries=2 checked=%u max_RGB_error=%u (tiled YUV vs portable intro decoder)\n",ok&&tested==3?"passed":"FAILED",tested,pixels,maxError);Melee360Log(msg);return ok&&tested==3;}
