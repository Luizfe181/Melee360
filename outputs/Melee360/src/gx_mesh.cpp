#include "gx_mesh.h"
#include <stdlib.h>
#include <string.h>
#include <vector>
namespace {
unsigned int be16(const unsigned char* p) {return (p[0]<<8)|p[1];}
unsigned int be32(const unsigned char* p) {return ((unsigned int)p[0]<<24)|((unsigned int)p[1]<<16)|((unsigned int)p[2]<<8)|p[3];}
struct Attribute {unsigned int id,type,components,format,fraction,stride,array;};
unsigned int length(const Attribute& a) {
    if(a.id<=8) return 1;
    if(a.id==11||a.id==12) {const unsigned int sizes[]={2,3,4,2,3,4};return a.format<6?sizes[a.format]:0;}
    if(a.id==25)return a.components==1&&a.format<=4?9*(a.format<=1?1:a.format<=3?2:4):0;
    unsigned int n=a.id==9?(a.components?3:2):a.id==10?3:a.id>=13&&a.id<=20?(a.components?2:1):0;
    if(a.id==10&&a.components!=0) return 0;
    return a.format<=4?n*(a.format<=1?1:a.format<=3?2:4):0;
}
float number(const unsigned char* p,unsigned int type,unsigned int fraction) {
    if(type==4) {unsigned int bits=be32(p);float f;memcpy(&f,&bits,4);return f;}
    int v=type==0?p[0]:type==1?(signed char)p[0]:type==2?(int)be16(p):(short)be16(p);
    return (float)v/(float)(1u<<fraction);
}
unsigned int expand(unsigned int v,int n) {return n==4?(v<<4)|v:n==5?(v<<3)|(v>>2):n==6?(v<<2)|(v>>4):v;}
unsigned int color(const unsigned char* p,unsigned int type) {
    unsigned int r,g,b,a=255,v;
    switch(type) {
    case 0:v=be16(p);r=expand(v>>11,5);g=expand((v>>5)&63,6);b=expand(v&31,5);break;
    case 1:case 2:r=p[0];g=p[1];b=p[2];break;
    case 3:v=be16(p);r=expand(v>>12,4);g=expand((v>>8)&15,4);b=expand((v>>4)&15,4);a=expand(v&15,4);break;
    case 4:v=(p[0]<<16)|(p[1]<<8)|p[2];r=expand(v>>18,6);g=expand((v>>12)&63,6);b=expand((v>>6)&63,6);a=expand(v&63,6);break;
    default:r=p[0];g=p[1];b=p[2];a=p[3];break;
    }
    return (a<<24)|(r<<16)|(g<<8)|b;
}
void triangle(std::vector<Melee360MeshVertex>& out,const std::vector<Melee360MeshVertex>& in,unsigned int a,unsigned int b,unsigned int c) {
    out.push_back(in[a]);out.push_back(in[b]);out.push_back(in[c]);
}
}
int Melee360DecodeGxMesh(const unsigned char* data,unsigned int bytes,unsigned int pobj,
    Melee360MeshVertex** vertices,unsigned int* count,unsigned int* unsupported) {
    if(!vertices||!count||!unsupported) return 0;
    *vertices=0;*count=0;*unsupported=0;
    if(!data||pobj>bytes||bytes-pobj<24) return 0;
    unsigned int desc=be32(data+pobj+8),dl=be32(data+pobj+16),size=be16(data+pobj+14)*32;
    if(dl>bytes||size>bytes-dl) return 0;
    std::vector<Attribute> attrs;
    for(unsigned int i=0;i<32;++i) {
        if(desc>bytes||bytes-desc<24) return 0;
        Attribute a;a.id=be32(data+desc);if(a.id==255) break;
        a.type=be32(data+desc+4);a.components=be32(data+desc+8);a.format=be32(data+desc+12);
        a.fraction=data[desc+16];a.stride=be16(data+desc+18);a.array=be32(data+desc+20);
        if(a.type>3||a.fraction>31) return 0;
        if(a.type&&!length(a)) {*unsupported=0x100|a.id;return -1;}
        attrs.push_back(a);desc+=24;
        if(i==31) return 0;
    }
    unsigned int cursor=dl,end=dl+size;
    unsigned int matrixIndices[10];for(unsigned int i=0;i<10;++i)matrixIndices[i]=i;
    std::vector<Melee360MeshVertex> out;
    while(cursor<end) {
        unsigned int opcode=data[cursor++];if(!opcode) continue;
        if(opcode==0x20||opcode==0x28||opcode==0x30||opcode==0x38) {
            if(end-cursor<4) return 0;
            if(opcode==0x20){unsigned int index=be16(data+cursor),address=be16(data+cursor+2)&4095;if(address%12||address/12>=10)return 0;matrixIndices[address/12]=index;}
            cursor+=4;continue;
        }
        unsigned int primitive=opcode&0xF8;
        if(primitive!=0x80&&primitive!=0x90&&primitive!=0x98&&primitive!=0xA0) {*unsupported=opcode;return -1;}
        if(end-cursor<2) return 0;
        unsigned int n=be16(data+cursor);cursor+=2;
        std::vector<Melee360MeshVertex> in;
        for(unsigned int v=0;v<n;++v) {
            Melee360MeshVertex vertex;memset(&vertex,0,sizeof(vertex));vertex.color=0xFFFFFFFF;
            for(unsigned int k=0;k<attrs.size();++k) {
                const Attribute& a=attrs[k];if(!a.type) continue;
                unsigned int len=length(a),offset=cursor;
                if(a.type>=2) {
                    unsigned int ixbytes=a.type==2?1:2;if(end-cursor<ixbytes) return 0;
                    unsigned int index=ixbytes==1?data[cursor]:be16(data+cursor);cursor+=ixbytes;
                    if(!a.stride||a.array>bytes||index>(bytes-a.array)/a.stride) return 0;
                    offset=a.array+index*a.stride;
                    if(offset>bytes||len>bytes-offset) return 0;
                } else {if(len>end-cursor) return 0;cursor+=len;}
                const unsigned char* p=data+offset;
                if(a.id==0) vertex.matrix=p[0];
                else if(a.id==11) vertex.color=color(p,a.format);
                else if(a.id==9||a.id==10||a.id==25||a.id==13) {
                    float* target=a.id==9?vertex.position:a.id==10||a.id==25?vertex.normal:vertex.uv;
                    unsigned int width=a.format<=1?1:a.format<=3?2:4;
                    unsigned int fraction=a.id==10||a.id==25?(a.format==1?6:a.format==3?14:0):a.fraction;
                    unsigned int components=a.id==25?3:len/width;
                    for(unsigned int c=0;c<components;++c) target[c]=number(p+c*width,a.format,fraction);
                }
            }
            if(vertex.matrix%3||vertex.matrix/3>=10)return 0;vertex.envelope=matrixIndices[vertex.matrix/3];
            in.push_back(vertex);
        }
        if(primitive==0x80) {if(n%4) return 0;for(unsigned int i=0;i<n;i+=4) {triangle(out,in,i,i+1,i+2);triangle(out,in,i,i+2,i+3);}}
        else if(primitive==0x90) {if(n%3) return 0;for(unsigned int i=0;i<n;i+=3) triangle(out,in,i,i+1,i+2);}
        else if(primitive==0x98) {for(unsigned int i=2;i<n;++i) triangle(out,in,i%2?i-1:i-2,i%2?i-2:i-1,i);}
        else {for(unsigned int i=2;i<n;++i) triangle(out,in,0,i-1,i);}
        if(out.size()>1000000) return 0;
    }
    if(out.empty()) return 1;
    *vertices=(Melee360MeshVertex*)malloc(out.size()*sizeof(Melee360MeshVertex));
    if(!*vertices) return 0;
    memcpy(*vertices,&out[0],out.size()*sizeof(Melee360MeshVertex));*count=(unsigned int)out.size();return 1;
}
