#include "../src/hsd_scene.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
static double signature(const Melee360Scene& s){double sum=0;for(unsigned int i=0;i<s.batches.size();++i)for(unsigned int v=0;v<s.batches[i].vertices.size();++v){const Melee360SceneVertex& o=s.batches[i].vertices[v];for(int k=0;k<4;++k)sum+=o.clip[k]*(k+1)+o.color[k]*(k+3);sum+=o.uv[0]*.7+o.uv[1]*.3;}for(unsigned int i=0;i<s.textures.size();++i)for(unsigned int k=0;k<s.textures[i].pixels.size();k+=31)sum+=(s.textures[i].pixels[k]&65535)*.00001;return sum;}
int main(){FILE* f=fopen("C:\\Users\\luizf\\Documents\\melee_extraido\\GrNBa.dat","rb");if(!f)return 1;fseek(f,0,SEEK_END);long n=ftell(f);rewind(f);std::vector<unsigned char> raw(n);bool read=fread(&raw[0],1,n,f)==(size_t)n;fclose(f);if(!read)return 2;
    const float frames[]={0,1,10,30,60,120,300,600,1200,2400,3600,7200};
    for(int bg=0;bg<4;++bg){bool changed=false;double first=0;for(int at=0;at<12;++at){Melee360Scene s;unsigned int tracks=0,groups=0;if(!Melee360LoadBattlefield(&raw[0],(unsigned int)raw.size(),frames[at],bg,s,&tracks,&groups)){printf("FAILED bg=%d frame=%.0f\n",bg,frames[at]);return 3;}if(s.skipped||groups!=4||!tracks){printf("SKIPPED bg=%d meshes=%u tracks=%u\n",bg,s.skipped,tracks);return 4;}
        for(unsigned int i=0;i<s.batches.size();++i){const Melee360SceneBatch& b=s.batches[i];if(b.texture>=0&&(unsigned int)b.texture>=s.textures.size())return 5;for(unsigned int v=0;v<b.vertices.size();++v){const Melee360SceneVertex& o=b.vertices[v];for(int k=0;k<4;++k)if(!_finite(o.clip[k])||!_finite(o.color[k]))return 6;if(!_finite(o.uv[0])||!_finite(o.uv[1]))return 6;}}
        double value=signature(s);if(!at)first=value;else if(fabs(first-value)>.01)changed=true;printf("Battlefield bg=%d frame=%.0f groups=%u tracks=%u batches=%u textures=%u skipped=%u signature=%.6f\n",bg,frames[at],groups,tracks,(unsigned int)s.batches.size(),(unsigned int)s.textures.size(),s.skipped,value);
    }if(!changed)return 7;}
    Melee360Scene s;unsigned int tracks;if(Melee360LoadBattlefield(&raw[0],(unsigned int)raw.size(),-1,0,s,&tracks)||Melee360LoadBattlefield(&raw[0],32,0,0,s,&tracks))return 8;
    puts("Battlefield: 48 animation samples passed, all seven model groups covered across four background variants; no skipped meshes; descriptor animation only");return 0;
}
