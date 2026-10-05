#include "hps_decode.h"
#include <string.h>
static unsigned int be32(const unsigned char* p){return ((unsigned int)p[0]<<24)|((unsigned int)p[1]<<16)|(p[2]<<8)|p[3];}
static short be16(const unsigned char* p){return (short)((p[0]<<8)|p[1]);}
bool Melee360DecodeHPSBlock(const unsigned char* raw,unsigned int bytes,unsigned int block,std::vector<short>& pcm,unsigned int& rate,unsigned int& channels,unsigned int& next){
    pcm.clear();if(!raw||bytes<0xa0||memcmp(raw," HALPST\0",8))return false;
    rate=be32(raw+8);channels=be32(raw+12);
    if(rate<8000||rate>48000||(channels!=1&&channels!=2)||block<0x80||block>bytes-32)return false;
    unsigned int total=be32(raw+block),last=be32(raw+block+4);next=be32(raw+block+8);
    if(!total||total%channels||total>1024*1024||total>bytes-block-32||last==0xffffffff)return false;
    unsigned int stride=total/channels,nibbles=last+1;
    if(nibbles>stride*2)return false;
    if(next!=0xffffffff&&(next<0x80||next>bytes-32))return false;
    unsigned int samples=(nibbles/16)*14+(nibbles%16>2?nibbles%16-2:0);
    if(!samples)return false;pcm.resize(samples*channels);
    for(unsigned int channel=0;channel<channels;++channel){
        short coefficients[16];for(int i=0;i<16;++i)coefficients[i]=be16(raw+0x20+channel*0x38+i*2);
        int h1=be16(raw+block+0x0e+channel*8),h2=be16(raw+block+0x10+channel*8);
        const unsigned char* data=raw+block+32+channel*stride;
        for(unsigned int i=0;i<samples;++i){unsigned int frame=i/14,sample=i%14,header=data[frame*8],predictor=header>>4,scale=1u<<(header&15);
            if(predictor>=8){pcm.clear();return false;}
            unsigned int packed=data[frame*8+1+sample/2];int nibble=(sample&1)?packed&15:packed>>4;if(nibble>=8)nibble-=16;
            __int64 accumulator=(__int64)nibble*scale*2048+1024+(__int64)coefficients[predictor*2]*h1+(__int64)coefficients[predictor*2+1]*h2;
            __int64 value=accumulator>>11;if(value>32767)value=32767;if(value< -32768)value=-32768;
            h2=h1;h1=(int)value;pcm[i*channels+channel]=(short)value;
        }
    }return true;
}
