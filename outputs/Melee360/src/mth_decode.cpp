#include "mth_decode.h"
/* inverse8 is adapted from the IJG/libjpeg-turbo floating-point IDCT.
 * Copyright (C) 1994-1998 Thomas G. Lane; modified 2010 Guido Vollbeding;
 * libjpeg-turbo modifications (C) 2014, 2022, 2026 D. R. Commander.
 * Distribution terms: ../third_party/ijg/README.ijg.
 * Adaptation: standalone butterfly, scaled MTH quantization, explicit clamps. */
#include <math.h>
#include <string.h>
namespace {
const int zig[64] = {
 0,1,8,16,9,2,3,10,17,24,32,25,18,11,4,5,
 12,19,26,33,40,48,41,34,27,20,13,6,7,14,21,28,
 35,42,49,56,57,50,43,36,29,22,15,23,30,37,44,51,
 58,59,52,45,38,31,39,46,53,60,61,54,47,55,62,63};
struct Huff {
    int min[17], max[17], base[17];
    unsigned char symbols[256];
    bool valid;
};
struct Decoder {
    const unsigned char* p;
    const unsigned char* end;
    unsigned int bits;
    int bitCount;
    bool ok;
    Huff h[2][4];
    int quant[4][64];
    bool qvalid[4];
    int id[3], q[3], dc[3], ac[3], pred[3];
    float scaledQuant[4][64];
    int byte() { if(p == end) {ok=false;return 0;} return *p++; }
    int word() { int a=byte(); return (a<<8)|byte(); }
    int get(int count) {
        if(count < 0 || count > 16) {ok=false;return 0;}
        while(bitCount < count && ok) { bits=(bits<<8)|byte(); bitCount+=8; }
        if(!ok) return 0;
        bitCount-=count;
        return (bits>>bitCount)&((1u<<count)-1);
    }
    int symbol(Huff& table) {
        if(!table.valid) {ok=false;return 0;}
        int code=0;
        for(int n=1;n<=16 && ok;++n) {
            code=(code<<1)|get(1);
            if(table.max[n]>=0 && code>=table.min[n] && code<=table.max[n])
                return table.symbols[table.base[n]+code-table.min[n]];
        }
        ok=false;return 0;
    }
    int signedBits(int n) {
        if(n==0) return 0;
        int v=get(n);
        return v < (1<<(n-1)) ? v-((1<<n)-1) : v;
    }
    static int clamp(float x) {
        if(x<=0.f) return 0;
        if(x>=255.f) return 255;
        return (int)(x+0.5f);
    }
    // AA&N scaled inverse transform, as also used by the original THP decoder.
    // Floating-point butterfly formulation follows IJG/libjpeg-turbo jidctflt.
    static void inverse8(const float* in, float* out) {
        float e0=in[0]+in[4],e1=in[0]-in[4];
        float e3=in[2]+in[6],e2=(in[2]-in[6])*1.414213562f-e3;
        float a=e0+e3,b=e1+e2,c=e1-e2,d=e0-e3;
        float z13=in[5]+in[3],z10=in[5]-in[3];
        float z11=in[1]+in[7],z12=in[1]-in[7];
        float o7=z11+z13,o11=(z11-z13)*1.414213562f;
        float z5=(z10+z12)*1.847759065f;
        float o10=z5-z12*1.082392200f,o12=z5-z10*2.613125930f;
        float o6=o12-o7,o5=o11-o6,o4=o10-o5;
        out[0]=a+o7;out[7]=a-o7;out[1]=b+o6;out[6]=b-o6;
        out[2]=c+o5;out[5]=c-o5;out[3]=d+o4;out[4]=d-o4;
    }
    void block(int component, unsigned char* samples) {
        int coeff[64]; memset(coeff,0,sizeof(coeff));
        int n=symbol(h[0][dc[component]]);
        if(n>11) {ok=false;return;}
        pred[component]+=signedBits(n);
        if(pred[component]<-32768 || pred[component]>32767) {ok=false;return;}
        coeff[0]=pred[component];
        for(int k=1;k<64 && ok;) {
            int rs=symbol(h[1][ac[component]]), run=rs>>4, size=rs&15;
            if(!size) {
                if(!run) break;
                if(run!=15 || k+16>64) {ok=false;return;}
                k+=16; continue;
            }
            k+=run;
            if(k>=64 || size>10) {ok=false;return;}
            coeff[zig[k++]]=signedBits(size);
        }
        if(!ok) return;
        bool onlyDC=true;
        for(int k=1;k<64;++k) if(coeff[k]) {onlyDC=false;break;}
        if(onlyDC) {
            memset(samples,clamp(coeff[0]*quant[q[component]][0]/8.f+128.f),64);
            return;
        }
        float rows[64], in[8], out[8];
        for(int v=0;v<8;++v) {
            bool rowDC=true;
            for(int u=1;u<8;++u) if(coeff[v*8+u]) {rowDC=false;break;}
            if(rowDC) {
                float value=coeff[v*8]*scaledQuant[q[component]][v*8];
                for(int x=0;x<8;++x) rows[v*8+x]=value;
            } else {
                for(int u=0;u<8;++u) in[u]=coeff[v*8+u]*scaledQuant[q[component]][v*8+u];
                inverse8(in,rows+v*8);
            }
        }
        for(int x=0;x<8;++x) {
            for(int v=0;v<8;++v) in[v]=rows[v*8+x];
            inverse8(in,out);
            for(int y=0;y<8;++y) samples[y*8+x]=(unsigned char)clamp(out[y]+128.f);
        }
    }
};
}
int Melee360DecodeMth(const unsigned char* input, unsigned int size,
                     unsigned int* argb, unsigned int width, unsigned int height)
{
    if(!input || !argb || size<4 || !width || !height || width>640 || height>480 || width%16 || height%16) return 0;
    Decoder d; memset(&d,0,sizeof(d)); d.p=input; d.end=input+size; d.ok=true;
    if(d.word()!=0xFFD8) return 0;
    bool frame=false,scan=false;
    while(d.ok && !scan) {
        if(d.byte()!=0xFF) return 0;
        int marker; do {marker=d.byte();} while(marker==0xFF && d.ok);
        int length=d.word();
        if(length<2 || length-2>d.end-d.p) return 0;
        const unsigned char* segmentEnd=d.p+length-2;
        if(marker==0xDB) {
            while(d.p<segmentEnd && d.ok) {
                int table=d.byte(); if(table>3 || segmentEnd-d.p<64) return 0;
                for(int i=0;i<64;++i) { int value=d.byte(); if(!value) return 0; d.quant[table][zig[i]]=value; }
                d.qvalid[table]=true;
            }
        } else if(marker==0xC4) {
            while(d.p<segmentEnd && d.ok) {
                int selector=d.byte(),type=selector>>4,table=selector&15;
                if(type>1 || table>3 || segmentEnd-d.p<16) return 0;
                Huff& h=d.h[type][table]; int counts[17],total=0;
                for(int n=1;n<=16;++n) {counts[n]=d.byte();total+=counts[n];}
                if(total>256 || total>segmentEnd-d.p) return 0;
                int code=0,index=0;
                for(int n=1;n<=16;++n) {
                    if(code+counts[n]>(1<<n)) return 0;
                    h.min[n]=code; h.max[n]=counts[n]?code+counts[n]-1:-1; h.base[n]=index;
                    index+=counts[n]; code=(code+counts[n])<<1;
                }
                for(int i=0;i<total;++i) h.symbols[i]=(unsigned char)d.byte();
                h.valid=true;
            }
        } else if(marker==0xC0) {
            if(length!=17 || d.byte()!=8) return 0;
            int fh=d.word(),fw=d.word(); if(fw!=(int)width || fh!=(int)height || d.byte()!=3) return 0;
            for(int c=0;c<3;++c) {
                d.id[c]=d.byte(); int sampling=d.byte(); d.q[c]=d.byte();
                if(sampling!=(c?0x11:0x22) || d.q[c]>3) return 0;
                for(int k=0;k<c;++k) if(d.id[k]==d.id[c]) return 0;
            }
            frame=true;
        } else if(marker==0xDA) {
            if(!frame || length!=12 || d.byte()!=3) return 0;
            for(int c=0;c<3;++c) {
                if(d.byte()!=d.id[c]) return 0;
                int selector=d.byte(); d.dc[c]=selector>>4; d.ac[c]=selector&15;
                if(d.dc[c]>3 || d.ac[c]>3 || !d.qvalid[d.q[c]]) return 0;
            }
            if(d.byte()!=0 || d.byte()!=63 || d.byte()!=0) return 0;
            scan=true;
        } else if(marker>=0xE0 && marker<=0xEF) {
            d.p=segmentEnd;
        } else return 0; // No progressive, restart markers or unsupported components.
        if(d.p!=segmentEnd) return 0;
    }
    if(!d.ok || !scan) return 0;
    const float scale[8]={1.f,1.387039845f,1.306562965f,1.175875602f,
                         1.f,0.785694958f,0.541196100f,0.275899379f};
    for(int t=0;t<4;++t) if(d.qvalid[t]) for(int v=0;v<8;++v) for(int u=0;u<8;++u)
        d.scaledQuant[t][v*8+u]=d.quant[t][v*8+u]*scale[u]*scale[v]*0.125f;
    unsigned char y[4][64],cb[64],cr[64];
    for(unsigned int my=0;my<height;my+=16) for(unsigned int mx=0;mx<width;mx+=16) {
        for(int b=0;b<4 && d.ok;++b) d.block(0,y[b]);
        d.block(1,cb); d.block(2,cr); if(!d.ok) return 0;
        for(int iy=0;iy<16;++iy) for(int ix=0;ix<16;++ix) {
            int luma=y[(iy/8)*2+ix/8][(iy%8)*8+ix%8], ci=(iy/2)*8+ix/2;
            int u=cb[ci]-128,v=cr[ci]-128;
            int base=luma*65536+32768;
            int r=(base+91881*v)>>16,g=(base-22554*u-46802*v)>>16,b=(base+116130*u)>>16;
            r=r<0?0:r>255?255:r;g=g<0?0:g>255?255:g;b=b<0?0:b>255?255:b;
            argb[(my+iy)*width+mx+ix]=0xFF000000u|(r<<16)|(g<<8)|b;
        }
    }
    return 1;
}
/* Native replacement for the Gekko paired-single transform, using the existing
 * licensed IJG/libjpeg-turbo butterfly in mth_decode.cpp. */
extern "C" void Melee360THPInverseBlock(const short* coefficients,const float* scaledQuant,unsigned char* pixels){
 float rows[64],input[8],output[8];for(int y=0;y<8;++y){for(int x=0;x<8;++x)input[x]=coefficients[y*8+x]*scaledQuant[y*8+x]*.125f;Decoder::inverse8(input,rows+y*8);}for(int x=0;x<8;++x){for(int y=0;y<8;++y)input[y]=rows[y*8+x];Decoder::inverse8(input,output);for(int y=0;y<8;++y){float value=output[y]+128;pixels[y*8+x]=(unsigned char)(value<=0?0:value>=255?255:(int)value);}}
}
