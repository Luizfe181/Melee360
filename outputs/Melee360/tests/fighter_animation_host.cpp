#include "../src/hsd_scene.h"
#include "../src/character_select.h"
#include <stdio.h>
#include <math.h>
#include <string.h>
static bool read(const char* name,std::vector<unsigned char>& d){char path[512];sprintf(path,"C:\\Users\\luizf\\Documents\\melee_extraido\\%s",name);FILE* f=fopen(path,"rb");if(!f)return false;fseek(f,0,SEEK_END);long n=ftell(f);rewind(f);d.resize(n);bool ok=fread(&d[0],1,n,f)==(size_t)n;fclose(f);return ok;}
static unsigned int hash(Melee360Scene& s){unsigned int h=2166136261U;for(unsigned int b=0;b<s.batches.size();++b)for(unsigned int v=0;v<s.batches[b].vertices.size();++v){const unsigned char* p=(unsigned char*)&s.batches[b].vertices[v];for(unsigned int i=0;i<16;++i)h=(h^p[i])*16777619;}return h;}
static void dump(Melee360Scene& scene,const char* path){FILE* fp=fopen(path,"wb");if(!fp)return;unsigned int n=(unsigned int)scene.textures.size();fwrite(&n,4,1,fp);for(unsigned int i=0;i<n;++i){Melee360SceneTexture& t=scene.textures[i];fwrite(&t.width,4,1,fp);fwrite(&t.height,4,1,fp);fwrite(&t.pixels[0],4,t.width*t.height,fp);}n=(unsigned int)scene.batches.size();fwrite(&n,4,1,fp);for(unsigned int i=0;i<n;++i){Melee360SceneBatch& b=scene.batches[i];unsigned int count=(unsigned int)b.vertices.size();fwrite(&b.texture,4,1,fp);fwrite(&b.mode,4,1,fp);fwrite(&b.wrapS,4,1,fp);fwrite(&b.wrapT,4,1,fp);fwrite(&count,4,1,fp);fwrite(&b.vertices[0],sizeof(Melee360SceneVertex),count,fp);}fclose(fp);}
int main(){unsigned int samples=0;std::vector<unsigned char> css;if(!read("MnSlChr.usd",css))return 18;
 for(int icon=0;icon<25;++icon){Melee360ResetSceneCache();std::vector<unsigned char> model,motion;char name[64];sprintf(name,"%.4sDViWaitAJ.dat",Melee360CharacterFiles[icon]);if(!read(Melee360CharacterFiles[icon],model)||!read(name,motion))return 1;
  Melee360Scene bind,posed;unsigned int tracks=0,first=0;bool moved=false;if(!Melee360LoadFighterPreview(&model[0],(unsigned int)model.size(),bind))return 2;
  for(int f=0;f<8;++f){Melee360Scene background;if(!Melee360LoadCharacterSelect(&css[0],(unsigned int)css.size(),icon,background,f*7.0f,true))return 19;
   if(!Melee360LoadAnimatedFighterPreview(&model[0],(unsigned int)model.size(),&motion[0],(unsigned int)motion.size(),f*7.0f,posed,&tracks)){printf("FAILED slot=%d %s frame=%d\n",icon,name,f*7);return 3;}
   if(!tracks||posed.skipped>bind.skipped)return 4;for(unsigned int b=0;b<posed.batches.size();++b)for(unsigned int v=0;v<posed.batches[b].vertices.size();++v)for(int k=0;k<4;++k)if(!_finite(posed.batches[b].vertices[v].clip[k]))return 5;
   if(icon==1&&(f==0||f==3))dump(posed,f?"mario-css-frame21.bin":"mario-css-frame0.bin");
   unsigned int current=hash(posed);
   if(f==3){Melee360ResetSceneCache();Melee360Scene cold;unsigned int coldTracks=0;if(!Melee360LoadAnimatedFighterPreview(&model[0],(unsigned int)model.size(),&motion[0],(unsigned int)motion.size(),21,cold,&coldTracks)||hash(cold)!=current||coldTracks!=tracks)return 20;}if(!f)first=current;else if(first!=current)moved=true;++samples;}
  if(!moved)return 6;
  unsigned int successfulTracks=tracks;
  if(Melee360LoadAnimatedFighterPreview(&model[0],(unsigned int)model.size(),&motion[0],(unsigned int)motion.size()-1,0,posed,&tracks))return 7;
  printf("slot=%d %s original FObj tracks=%u skipped=%u: animated\n",icon,name,successfulTracks,bind.skipped);
 }
 printf("Original CSS fighter FigaTree/FObj: %u poses, 25 models, finite geometry, actual motion and truncated archive rejection passed\n",samples);return 0;}
