#include "../src/menu_model.h"
#include <stdio.h>
#include <string.h>
#include <set>
#include <vector>
int main() {
    Melee360MenuModel root;Melee360MenuReset(root);
    std::vector<Melee360MenuModel> queue;queue.push_back(root);std::set<int> pages,leaves;int actions=0;
    for(unsigned int q=0;q<queue.size();++q){Melee360MenuModel base=queue[q];if(!pages.insert(base.page).second)continue;
        int count=Melee360MenuCount(base);if(count<=0||count>40)return 1;
        Melee360MenuModel wrapping=base;Melee360MenuInput(wrapping,MenuUp);if(wrapping.selection!=count-1)return 2;Melee360MenuInput(wrapping,MenuDown);if(wrapping.selection!=0)return 3;
        for(int row=0;row<count;++row){Melee360MenuModel selected=base;for(int i=0;i<row;++i)Melee360MenuInput(selected,MenuDown);
            char label[128];Melee360MenuLabel(selected,row,label,sizeof(label));if(!label[0])return 4;
            Melee360MenuInput(selected,MenuAccept);++actions;
            if(selected.leaf>=0){leaves.insert(selected.leaf);Melee360MenuInput(selected,MenuBack);if(selected.leaf>=0||selected.page!=base.page||selected.selection!=row)return 5;}
            else if(selected.page!=base.page){if(selected.depth>base.depth){queue.push_back(selected);Melee360MenuInput(selected,MenuBack);if(selected.page!=base.page||selected.selection!=row)return 6;}else if(base.page!=24||row!=0)return 19;}
            else if(selected.editing){Melee360MenuInput(selected,MenuRight);Melee360MenuInput(selected,MenuUp);Melee360MenuInput(selected,MenuAccept);if(selected.editing||!selected.dirty)return 7;}
            else if(selected.confirmReset){Melee360MenuInput(selected,MenuBack);if(selected.confirmReset)return 8;}
            unsigned char encoded[Melee360ConfigBytes];if(!Melee360ConfigEncode(selected.config,encoded,sizeof(encoded)))return 9;
        }
    }
    Melee360MenuModel m=root;m.page=13;m.selection=2;for(int i=0;i<400;++i)Melee360MenuInput(m,MenuRight);if(m.config.values[2]<1||m.config.values[2]>99)return 10;
    m.page=16;m.selection=34;unsigned char before=m.config.items[34];Melee360MenuInput(m,MenuAccept);if(m.config.items[34]==before)return 11;
    m.page=17;m.selection=28;before=m.config.stages[28];Melee360MenuInput(m,MenuLeft);if(m.config.stages[28]==before)return 12;
    unsigned char bytes[Melee360ConfigBytes];Melee360MenuConfig decoded;
    if(!Melee360ConfigEncode(m.config,bytes,sizeof(bytes))||!Melee360ConfigDecode(decoded,bytes,sizeof(bytes))||memcmp(&decoded,&m.config,sizeof(decoded)))return 13;
    bytes[40]^=1;if(Melee360ConfigDecode(decoded,bytes,sizeof(bytes)))return 14;
    if(Melee360ConfigDecode(decoded,bytes,sizeof(bytes)-1))return 15;
    m.config.values[0]=255;if(Melee360ConfigEncode(m.config,bytes,sizeof(bytes)))return 16;
    if(pages.size()!=22||leaves.size()!=36)return 17;
    if(!Melee360MenuInput(root,MenuBack))return 18;
    root.config.values[11]=1;if(strcmp(Melee360MenuTitle(root),"Main menu"))return 20;
    char label[128];Melee360MenuLabel(root,3,label,sizeof(label));if(strcmp(label,"Options"))return 21;
    m=root;m.config.values[11]=0;m.page=12;m.selection=0;Melee360MenuLabel(m,0,label,sizeof(label));if(strcmp(label,"Melee com camera"))return 22;
    m.config.values[11]=1;Melee360MenuLabel(m,0,label,sizeof(label));if(strcmp(label,"Camera Melee"))return 23;
    m=root;m.config.values[11]=0;m.page=19;m.selection=0;Melee360MenuInput(m,MenuAccept);if(m.config.values[18]!=1||m.config.values[19]!=0)return 24;
    m.selection=1;Melee360MenuInput(m,MenuRight);if(m.config.values[18]!=1||m.config.values[19]!=1)return 25;
    if(!Melee360ConfigEncode(m.config,bytes,sizeof(bytes))||!Melee360ConfigDecode(decoded,bytes,sizeof(bytes))||memcmp(&decoded,&m.config,sizeof(decoded)))return 26;
    printf("Menu traversal passed: %u pages, %u destinations (routing model; backend availability tested separately), %d option activations\n",(unsigned int)pages.size(),(unsigned int)leaves.size(),actions);
    puts("Configuration bounds/name editing/serialization/corruption tests passed");return 0;
}
