#include "../src/mth_decode.h"
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <time.h>
static unsigned int be(const unsigned char* p) {return (p[0]<<24)|(p[1]<<16)|(p[2]<<8)|p[3];}
int main(int argc,char** argv) {
    if(argc!=4) return 2;
    FILE* f=fopen(argv[1],"rb"); if(!f) return 3;
    unsigned char header[64]; if(fread(header,1,64,f)!=64) return 4;
    bool all=!strcmp(argv[2],"all");
    bool benchmark=!strcmp(argv[2],"bench");
    unsigned int offset=be(header+32),size=be(header+40),frame=all?be(header+28)-1:benchmark?900:atoi(argv[2]);
    if(frame>=be(header+28)) return 5;
    std::vector<unsigned char> packed;
    unsigned int width=be(header+16),height=be(header+20);if(!width||!height||width>640||height>480||width%16||height%16)return 12;
    std::vector<unsigned int> rgb(width*height);
    for(unsigned int i=0;i<=frame;++i) {
        if(size<8 || size>2*1024*1024) return 6;
        packed.resize(size); if(fseek(f,offset,SEEK_SET) || fread(&packed[0],1,size,f)!=size) return 7;
        if(all && !Melee360DecodeMth(&packed[4],size-4,&rgb[0],width,height)) {
            printf("Frame %u decode FAILED\n",i);return 8;
        }
        offset+=size; if(i!=frame) size=be(&packed[0]);
    }
    fclose(f);
    if(benchmark) {
        clock_t start=clock();
        for(int repeat=0;repeat<200;++repeat)
            if(!Melee360DecodeMth(&packed[4],size-4,&rgb[0],width,height)) return 8;
        printf("200 decodes of frame 900: %.3f ms/frame\n",1000.*(clock()-start)/CLOCKS_PER_SEC/200.);
        return 0;
    }
    if(!Melee360DecodeMth(&packed[4],size-4,&rgb[0],width,height)) { puts("Decode FAILED"); return 8; }
    FILE* out=fopen(argv[3],"wb"); if(!out) return 9;
    fprintf(out,"P6\n%u %u\n255\n",width,height);
    for(size_t i=0;i<rgb.size();++i) {unsigned char p[3]={(unsigned char)(rgb[i]>>16),(unsigned char)(rgb[i]>>8),(unsigned char)rgb[i]};fwrite(p,1,3,out);}
    fclose(out);
    // Reject truncation and invalid SOI without relying on a crash.
    if(Melee360DecodeMth(&packed[4],32,&rgb[0],width,height)) return 10;
    packed[4]=0;
    if(Melee360DecodeMth(&packed[4],size-4,&rgb[0],width,height)) return 11;
    printf("Frame %u portable decode and malformed-input checks passed\n",frame);
    if(all) printf("All %u movie frames decoded successfully\n",frame+1);
    return 0;
}
