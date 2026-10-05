#include "hsd_animation.h"
#include <string.h>
#include <math.h>
extern "C" {
#include <sysdolphin/baselib/fobj.h>
}
namespace {
unsigned int u(const unsigned char* p) {return ((unsigned int)p[0]<<24)|(p[1]<<16)|(p[2]<<8)|p[3];}
bool finite(float v) {unsigned int bits;memcpy(&bits,&v,4);return (bits&0x7F800000)!=0x7F800000;}
bool range(unsigned int at,unsigned int n,unsigned int bytes) {return at<=bytes&&n<=bytes-at;}
bool varint(const unsigned char* d,unsigned int n,unsigned int& at,unsigned int& v,unsigned int shift=0) {
    for(int i=0;i<5;++i){if(at>=n||shift>28)return false;unsigned int b=d[at++];if(shift==28&&(b&127)>15)return false;v|=(b&127)<<shift;if(!(b&128))return true;shift+=7;}return false;
}
unsigned int valueSize(unsigned int frac) {return frac==0?4:(frac>>5)==1||(frac>>5)==2?2:(frac>>5)==3||(frac>>5)==4?1:0;}
bool stream(const unsigned char* d,unsigned int n,unsigned int fv,unsigned int fs) {
    unsigned int at=0,values=valueSize(fv),slopes=valueSize(fs);if(!n||!values||!slopes)return false;
    while(at<n){unsigned int b=d[at++],op=b&15,count=((b>>4)&7)+1;
        if(b&128){unsigned int high=0;if(!varint(d,n,at,high,3)||high>65535-count)return false;count+=high;}
        if(op<1||op>6)return false;
        for(unsigned int i=0;i<count;++i){unsigned int size=op==5?slopes:values+(op==4?slopes:0);
            if(!range(at,size,n))return false;at+=size;
            // Slope packets have no wait and leave the parser in LOAD_DATA.
            if(op!=5&&at<n){unsigned int wait=0;if(!varint(d,n,at,wait)||wait>65535)return false;}
            else if(op!=5&&i+1<count)return false;
        }
    }return true;
}
struct Callback {Melee360AnimValue update;void* object;bool ok;};
void callback(void* obj,enum_t type,HSD_ObjData* value) {
    Callback* c=(Callback*)obj;if(!finite(value->fv)){c->ok=false;return;}c->update(c->object,type,value->fv);
}
}
bool Melee360SampleAObj(const unsigned char* data,unsigned int bytes,unsigned int aobj,float frame,
    Melee360AnimValue update,void* object,unsigned int* tracks) {
    if(!aobj)return true;if(!data||!update||!finite(frame)||frame<0||!range(aobj,16,bytes))return false;
    unsigned int desc=u(data+aobj+8),visited[256],count=0;
    while(desc){if(count>=256||!range(desc,20,bytes))return false;for(unsigned int i=0;i<count;++i)if(visited[i]==desc)return false;visited[count++]=desc;
        unsigned int length=u(data+desc+4),ad=u(data+desc+16),bits=u(data+desc+8);float start;memcpy(&start,&bits,4);
        if(!finite(start)||start<-32768||start>32767||!range(ad,length,bytes)||!stream(data+ad,length,data[desc+13],data[desc+14]))return false;
        HSD_FObj f;memset(&f,0,sizeof(f));f.ad_head=(u8*)data+ad;f.length=length;f.startframe=(s16)start;
        f.obj_type=data[desc+12];f.frac_value=data[desc+13];f.frac_slope=data[desc+14];
        Callback c={update,object,true};HSD_FObjReqAnimAll(&f,frame);HSD_FObjInterpretAnim(&f,&c,callback,0);
        if(!c.ok)return false;if(tracks)++*tracks;desc=u(data+desc);
    }return true;
}
bool Melee360SampleFigaTracks(const unsigned char* data,unsigned int bytes,unsigned int at,unsigned int count,
    float frame,Melee360AnimValue update,void* object,unsigned int* tracks){
    if(!data||!update||count>127||!finite(frame)||frame<0||!range(at,count*12,bytes))return false;
    for(unsigned int i=0;i<count;++i,at+=12){unsigned int length=(data[at]<<8)|data[at+1],ad=u(data+at+8);
        if(!range(ad,length,bytes)||!stream(data+ad,length,data[at+5],data[at+6]))return false;
        HSD_FObj f;memset(&f,0,sizeof(f));f.ad_head=(u8*)data+ad;f.length=length;
        f.startframe=(s16)((data[at+2]<<8)|data[at+3]);f.obj_type=data[at+4];f.frac_value=data[at+5];f.frac_slope=data[at+6];
        Callback c={update,object,true};HSD_FObjReqAnimAll(&f,frame);HSD_FObjInterpretAnim(&f,&c,callback,0);
        if(!c.ok)return false;if(tracks)++*tracks;
    }return true;
}
