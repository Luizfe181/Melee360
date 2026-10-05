#include <xtl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "gx_mesh.h"
#include "platform_log.h"
namespace {
unsigned int be32(const unsigned char* p) {return ((unsigned int)p[0]<<24)|((unsigned int)p[1]<<16)|((unsigned int)p[2]<<8)|p[3];}
bool word(const unsigned char* data,unsigned int size,unsigned int off,unsigned int& value) {
    if(off>size||size-off<4) return false;value=be32(data+off);return true;
}
}
bool Melee360RendererProbe() {
    HANDLE file=CreateFileA("game:\\data\\GmTitle.usd",GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
    if(file==INVALID_HANDLE_VALUE) {Melee360Log("Renderer: original title archive unavailable\n");return false;}
    DWORD high=0,size=GetFileSize(file,&high),read=0;
    if(size<=32||size>=8*1024*1024||high) {CloseHandle(file);return false;}
    unsigned char* raw=(unsigned char*)malloc(size);
    bool ok=raw&&ReadFile(file,raw,size,&read,0)&&read==size;CloseHandle(file);
    if(!ok) {free(raw);return false;}
    const unsigned int ds=be32(raw+4),nr=be32(raw+8),np=be32(raw+12),ne=be32(raw+16);
    ULONGLONG table=32ULL+ds+4ULL*nr,names=table+8ULL*(np+ne);
    ok=be32(raw)==size&&names<=size;
    unsigned int scene=0;bool found=false;
    if(ok) for(unsigned int i=0;i<np;++i) {
        unsigned int offset=be32(raw+(unsigned int)table+i*8),symbol=be32(raw+(unsigned int)table+i*8+4);
        ULONGLONG at=names+symbol;
        if(at>=size||!memchr(raw+(unsigned int)at,0,size-(unsigned int)at)) {ok=false;break;}
        if(!strcmp((char*)raw+(unsigned int)at,"ScTitle_scene_data")) {scene=offset;found=true;}
    }
    const unsigned char* data=raw+32;unsigned int models=0;
    ok=ok&&found&&word(data,ds,scene,models);
    std::vector<unsigned int> stack,seen;
    if(ok) for(unsigned int i=0;i<256;++i) {
        unsigned int model,joint;
        if(!word(data,ds,models+i*4,model)) {ok=false;break;}
        if(!model) break;
        if(!word(data,ds,model,joint)) {ok=false;break;}
        stack.push_back(joint);if(i==255) ok=false;
    }
    unsigned int meshCount=0,vertexCount=0;
    while(ok&&!stack.empty()) {
        unsigned int joint=stack.back();stack.pop_back();if(!joint) continue;
        bool visited=false;for(unsigned int s=0;s<seen.size();++s) if(seen[s]==joint) visited=true;
        if(visited) continue;seen.push_back(joint);if(seen.size()>4096) {ok=false;break;}
        unsigned int flags,child,next,dobj;
        if(!word(data,ds,joint+4,flags)||!word(data,ds,joint+8,child)||!word(data,ds,joint+12,next)||!word(data,ds,joint+16,dobj)) {ok=false;break;}
        stack.push_back(child);stack.push_back(next);if(flags&((1<<5)|(1<<14))) continue;
        for(unsigned int d=0;dobj&&ok&&d<4096;++d) {
            unsigned int pobj;if(!word(data,ds,dobj+12,pobj)) {ok=false;break;}
            for(unsigned int p=0;pobj&&ok&&p<4096;++p) {
                Melee360MeshVertex* vertices=0;unsigned int count=0,unsupported=0;
                int result=Melee360DecodeGxMesh(data,ds,pobj,&vertices,&count,&unsupported);
                free(vertices);
                if(result!=1) {ok=false;break;}++meshCount;vertexCount+=count;
                if(!word(data,ds,pobj+4,pobj)) {ok=false;break;}
                if(p==4095&&pobj) ok=false;
            }
            if(!word(data,ds,dobj+4,dobj)) {ok=false;break;}
            if(d==4095&&dobj) ok=false;
        }
    }
    char message[160];sprintf_s(message,sizeof(message),"Renderer probe: title joints=%u meshes=%u triangle_vertices=%u %s\n",(unsigned int)seen.size(),meshCount,vertexCount,ok?"passed":"FAILED");Melee360Log(message);
    free(raw);return ok&&meshCount>0;
}
