#include "../src/hsd_scene.h"
#include <stdio.h>
#include <stdlib.h>
static bool readFile(const char* path,std::vector<unsigned char>& data){FILE* f=fopen(path,"rb");if(!f)return false;fseek(f,0,SEEK_END);long n=ftell(f);rewind(f);if(n<=0){fclose(f);return false;}data.resize(n);bool ok=fread(&data[0],1,n,f)==n;fclose(f);return ok;}
int main(int argc,char** argv) {
    if(argc!=3&&argc!=4&&argc!=6)return 1;const char* root=argc>=4?argv[3]:"ScTitle_scene_data";FILE* fp=fopen(argv[1],"rb");if(!fp)return 2;
    fseek(fp,0,SEEK_END);unsigned int bytes=ftell(fp);rewind(fp);unsigned char* raw=(unsigned char*)malloc(bytes);
    if(!raw||fread(raw,1,bytes,fp)!=bytes)return 3;fclose(fp);
    Melee360Scene scene;unsigned int tracks=0;
    if(argc>=4&&root[0]=='#'){
        int page=0,selection=0;float frame=0;if(sscanf(root+1,"%d,%d,%f",&page,&selection,&frame)<2){selection=page;page=0;}
        if(!Melee360LoadOriginalMenu(raw,bytes,page,selection,frame,scene,&tracks))return 4;
        printf("Original menu page=%d selection=%d upstream FObj tracks=%u\n",page,selection,tracks);
        if(argc==6){std::vector<unsigned char> sis,font;if(!readFile(argv[4],sis)||!readFile(argv[5],font)||!Melee360AppendOriginalMenuCaption(raw,bytes,&sis[0],(unsigned int)sis.size(),&font[0],(unsigned int)font.size(),page,selection,scene))return 9;
            puts("Original SIS caption/glyph rendering loaded");}
    }else if(root[0]=='$'){if(!Melee360LoadAnimatedTitle(raw,bytes,(float)atof(root+1),scene,&tracks))return 4;printf("Animated title FObj tracks=%u\n",tracks);}else if(root[0]=='!'){if(!Melee360LoadFighterPreview(raw,bytes,scene))return 4;}
    else if(root[0]=='@'){if(!Melee360LoadCharacterSelect(raw,bytes,atoi(root+1),scene))return 4;}
    else if(root[0]=='^'){int page=20,selection=0,music=8,mask=15,connected=15;float frame=0;sscanf(root+1,"%d,%d,%d,%d,%d,%f",&page,&selection,&music,&mask,&connected,&frame);if(!Melee360LoadOptions(raw,bytes,page,selection,1,music,mask,connected,frame,scene,&tracks))return 4;printf("Options scene page=%d FObj tracks=%u\n",page,tracks);}
    else if(root[0]=='%'){if(!Melee360LoadSoundTest(raw,bytes,(float)atof(root+1),true,scene,&tracks))return 4;printf("Sound scene FObj tracks=%u\n",tracks);}
    else if(root[0]=='~'){const char* split=strchr(root+1,':');int variant=split?atoi(split+1):0;
        if(!Melee360LoadBattlefield(raw,bytes,(float)atof(root+1),variant,scene,&tracks))return 4;printf("Battlefield FObj tracks=%u unsupported event callbacks=%u\n",tracks,scene.unsupportedEvents);}
    else if(!Melee360LoadStaticScene(raw,bytes,root,scene))return 4;
    unsigned int count=0;for(unsigned int i=0;i<scene.batches.size();++i)count+=(unsigned int)scene.batches[i].vertices.size();
    printf("Static title: %u batches %u textures %u triangle vertices %u skipped\n",(unsigned int)scene.batches.size(),(unsigned int)scene.textures.size(),count,scene.skipped);
    fp=fopen(argv[2],"wb");if(!fp)return 5;
    unsigned int n=(unsigned int)scene.textures.size();fwrite(&n,4,1,fp);
    for(unsigned int i=0;i<n;++i){Melee360SceneTexture& t=scene.textures[i];fwrite(&t.width,4,1,fp);fwrite(&t.height,4,1,fp);fwrite(&t.pixels[0],4,t.width*t.height,fp);}
    n=(unsigned int)scene.batches.size();fwrite(&n,4,1,fp);
    for(unsigned int i=0;i<n;++i){Melee360SceneBatch& b=scene.batches[i];unsigned int count=(unsigned int)b.vertices.size();fwrite(&b.texture,4,1,fp);fwrite(&b.mode,4,1,fp);fwrite(&b.wrapS,4,1,fp);fwrite(&b.wrapT,4,1,fp);fwrite(&count,4,1,fp);fwrite(&b.vertices[0],sizeof(Melee360SceneVertex),count,fp);}
    fclose(fp);
    if(Melee360LoadStaticScene(raw,bytes-1,"ScTitle_scene_data",scene))return 6;
    if(Melee360LoadStaticScene(raw,bytes,"nonexistent_scene",scene))return 7;
    raw[0]^=1;if(Melee360LoadStaticScene(raw,bytes,"ScTitle_scene_data",scene))return 8;
    free(raw);puts("Static scene truncated archive/missing root/bad size checks passed");return 0;
}
