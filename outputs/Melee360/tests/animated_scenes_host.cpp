#include "../src/hsd_scene.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
static bool read(const char* path,std::vector<unsigned char>& d){FILE* f=fopen(path,"rb");if(!f)return false;fseek(f,0,SEEK_END);unsigned int n=ftell(f);rewind(f);d.resize(n);bool ok=fread(&d[0],1,n,f)==n;fclose(f);return ok;}
static double signature(const Melee360Scene& s){double result=0;for(unsigned int i=0;i<s.batches.size();++i)for(unsigned int v=0;v<s.batches[i].vertices.size();++v){const Melee360SceneVertex& o=s.batches[i].vertices[v];for(int k=0;k<4;++k)result+=o.clip[k]*(k+1)+o.color[k]*(k+3);result+=o.uv[0]*.7+o.uv[1]*.3;}for(unsigned int i=0;i<s.textures.size();++i)for(unsigned int p=0;p<s.textures[i].pixels.size();p+=31)result+=(s.textures[i].pixels[p]&65535)*.00001;return result;}
static bool valid(const Melee360Scene& s){if(s.batches.empty()||s.skipped)return false;for(unsigned int i=0;i<s.batches.size();++i){const Melee360SceneBatch& b=s.batches[i];if(b.texture>=0&&(unsigned int)b.texture>=s.textures.size())return false;for(unsigned int v=0;v<b.vertices.size();++v){const Melee360SceneVertex& o=b.vertices[v];for(int k=0;k<4;++k)if(!_finite(o.clip[k])||!_finite(o.color[k]))return false;}}return true;}
int main(){std::vector<unsigned char> title,menu;if(!read("C:\\Users\\luizf\\Documents\\melee_extraido\\GmTtAll.usd",title)||!read("C:\\Users\\luizf\\Documents\\melee_extraido\\MnMaAll.usd",menu))return 1;
    Melee360Scene scene;unsigned int tracks=0;const int frames[]={0,1,10,20,49,50,60,120,250,799,800,1200,1201,2400};double first=0;bool changed=false;
    for(int i=0;i<14;++i){if(!Melee360LoadAnimatedTitle(&title[0],(unsigned int)title.size(),(float)frames[i],scene,&tracks)||!valid(scene))return 2;double sig=signature(scene);if(!i)first=sig;else if(fabs(sig-first)>.01)changed=true;printf("Title frame=%d tracks=%u batches=%u skipped=%u\n",frames[i],tracks,(unsigned int)scene.batches.size(),scene.skipped);}if(!changed)return 3;
    if(Melee360LoadAnimatedTitle(&title[0],(unsigned int)title.size(),-1,scene,&tracks))return 4;
    const int pages[10][2]={{0,5},{1,4},{2,5},{3,3},{4,5},{5,5},{6,3},{9,3},{12,10},{28,3}};clock_t start=clock();unsigned int samples=0;
    for(int page=0;page<10;++page)for(int slot=0;slot<pages[page][1];++slot){changed=false;for(int i=0;i<14;++i){if(!Melee360LoadOriginalMenu(&menu[0],(unsigned int)menu.size(),pages[page][0],slot,(float)frames[i],scene,&tracks,true,(float)frames[i])||!valid(scene)){printf("FAILED menu=%d slot=%d frame=%d skipped=%u\n",pages[page][0],slot,frames[i],scene.skipped);return 5;}double sig=signature(scene);if(!i)first=sig;else if(fabs(sig-first)>.01)changed=true;++samples;}if(!changed)return 6;printf("Menu page=%d slot=%d: entry/hover/loop changed; bounds/index/finite checks passed\n",pages[page][0],slot);}
    std::vector<unsigned char> css;if(!read("C:\\Users\\luizf\\Documents\\melee_extraido\\MnSlChr.usd",css))return 7;
    changed=false;for(int i=0;i<14;++i){if(!Melee360LoadCharacterSelect(&css[0],(unsigned int)css.size(),1,scene,(float)frames[i],true)||!valid(scene))return 8;double sig=signature(scene);if(!i)first=sig;else if(fabs(sig-first)>.01)changed=true;}if(!changed)return 9;puts("Character select: original 200-frame background cycle changed; valid geometry/texture indices");
    for(int page=0;page<10;++page)for(int i=0;i<4;++i)if(!Melee360LoadOriginalMenu(&menu[0],(unsigned int)menu.size(),pages[page][0],0,(float)frames[i],scene,&tracks,true,(float)frames[i],true)||!valid(scene))return 10;
    puts("Original backward-entry tracks passed for all ten menu pages");
    printf("Animated menus: %u samples, %.2f ms/sample host (includes signatures); title and menu loops passed\n",samples,1000.*(clock()-start)/CLOCKS_PER_SEC/samples);return 0;
}
