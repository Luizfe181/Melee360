#include "../src/hps_decode.h"
#include <stdio.h>
#include <string.h>
#include <io.h>
#include <algorithm>
static void word(unsigned char* p,unsigned int n){p[0]=(unsigned char)(n>>24);p[1]=(unsigned char)(n>>16);p[2]=(unsigned char)(n>>8);p[3]=(unsigned char)n;}
int main(){unsigned char synthetic[168]={0};memcpy(synthetic," HALPST\0",8);word(synthetic+8,32000);word(synthetic+12,1);word(synthetic+128,8);word(synthetic+132,15);word(synthetic+136,0xffffffff);memset(synthetic+161,0x17,7);std::vector<short> pcm;unsigned int rate,channels,next;
    if(!Melee360DecodeHPSBlock(synthetic,sizeof(synthetic),128,pcm,rate,channels,next)||pcm.size()!=14)return 1;
    for(int i=0;i<14;++i)if(pcm[i]!=(i%2?7:1))return 2;
    synthetic[160]=1;if(!Melee360DecodeHPSBlock(synthetic,sizeof(synthetic),128,pcm,rate,channels,next)||pcm[0]!=2||pcm[1]!=14)return 3;
    synthetic[160]=0xf0;if(Melee360DecodeHPSBlock(synthetic,sizeof(synthetic),128,pcm,rate,channels,next)||Melee360DecodeHPSBlock(synthetic,160,128,pcm,rate,channels,next))return 4;
    const char* root="C:\\Users\\luizf\\Documents\\melee_extraido\\audio\\";char pattern[512];sprintf(pattern,"%s*.hps",root);_finddata_t item;intptr_t search=_findfirst(pattern,&item);if(search==-1)return 5;int tracks=0,blocks=0;long long samples=0;
    do{char path[512];sprintf(path,"%s%s",root,item.name);FILE* f=fopen(path,"rb");if(!f)return 6;fseek(f,0,SEEK_END);long bytes=ftell(f);rewind(f);std::vector<unsigned char> raw(bytes);if(fread(&raw[0],1,bytes,f)!=(unsigned int)bytes)return 7;fclose(f);std::vector<unsigned int> visited;unsigned int offset=128;int nonzero=0;std::vector<short> preview;
        while(offset!=0xffffffff&&std::find(visited.begin(),visited.end(),offset)==visited.end()){
            if(visited.size()>10000||!Melee360DecodeHPSBlock(&raw[0],raw.size(),offset,pcm,rate,channels,next)){fprintf(stderr,"HPS rejected %s block %x\n",item.name,offset);return 8;}
            visited.push_back(offset);++blocks;samples+=pcm.size();for(unsigned int i=0;i<pcm.size();++i)if(pcm[i])++nonzero;
            if(!strcmp(item.name,"menu01.hps")&&preview.size()<32000*2*4)preview.insert(preview.end(),pcm.begin(),pcm.end());offset=next;
        }
        if(!nonzero)return 9;++tracks;
        if(!preview.empty()){preview.resize(32000*2*4);unsigned int dataSize=preview.size()*2,riffSize=dataSize+36,formatSize=16,sampleRate=32000,byteRate=128000;unsigned short format=1,ch=2,align=4,bits=16;f=fopen("menu01-preview.wav","wb");if(!f)return 10;fwrite("RIFF",1,4,f);fwrite(&riffSize,4,1,f);fwrite("WAVEfmt ",1,8,f);fwrite(&formatSize,4,1,f);fwrite(&format,2,1,f);fwrite(&ch,2,1,f);fwrite(&sampleRate,4,1,f);fwrite(&byteRate,4,1,f);fwrite(&align,2,1,f);fwrite(&bits,2,1,f);fwrite("data",1,4,f);fwrite(&dataSize,4,1,f);fwrite(&preview[0],2,preview.size(),f);fclose(f);}
    }while(_findnext(search,&item)==0);_findclose(search);printf("HPS DSP: known-vector/malformed tests and %d tracks / %d blocks / %I64d PCM samples passed\n",tracks,blocks,samples);return 0;
}
