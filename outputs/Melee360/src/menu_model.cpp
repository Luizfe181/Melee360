#include "menu_model.h"
#include "original_menu_root.h"
#include <stdio.h>
#include <string.h>
namespace {
struct Entry {const char* label;int target;};
const Entry mainEntries[]={{"1 jogador",1},{"Versus",2},{"Trofeus",3},{"Opcoes",4},{"Dados",5}};
const Entry one[]={{"Partida regular",6},{"Eventos",107},{"Estadio",9},{"Treinamento",108}};
const Entry vs[]={{"Melee",109},{"Torneio",110},{"Versus especial",12},{"Regras",13},{"Nomes",18}};
const Entry trophies[]={{"Galeria",111},{"Loteria",112},{"Colecao",113}};
const Entry settings[]={{"Vibracao",19},{"Som",20},{"Tela",21},{"Idioma",23},{"Apagar dados",24}};
const Entry data[]={{"Fotos",125},{"Arquivos",26},{"Teste de som",127},{"Recordes",28},{"Dados especiais",129}};
const Entry archives[]={{"Special Movie",201},{"Como jogar",202}};
const Entry regular[]={{"Classic",130},{"Adventure",131},{"All-Star",132}};
const Entry stadium[]={{"Target Test",133},{"Home-Run Contest",134},{"Multi-Man Melee",33}};
const Entry special[]={{"Camera Melee",140},{"Stamina Melee",141},{"Sudden Death",142},{"Giant Melee",143},{"Tiny Melee",144},{"Invisible Melee",145},{"Fixed Camera",146},{"Single-Button",147},{"Lightning Melee",148},{"Slo-Mo Melee",149}};
const Entry records[]={{"Versus",150},{"Bonus",151},{"Diversos",152}};
const Entry multi[]={{"10-Man Melee",160},{"100-Man Melee",161},{"3-Minute Melee",162},{"15-Minute Melee",163},{"Endless Melee",164},{"Cruel Melee",165}};
const char* itemNames[]={"Capsula","Caixa","Barril","Ovo","Party Ball","Barrel Cannon","Pokebola","Comida","Maxim Tomato","Heart Container","Warp Star","Ray Gun","Super Scope","Fire Flower","Lip's Stick","Star Rod","Beam Sword","Home-Run Bat","Fan","Hammer","Green Shell","Red Shell","Flipper","Freezie","Mr. Saturn","Bob-omb","Motion-Sensor Bomb","Super Mushroom","Poison Mushroom","Starman","Parasol","Screw Attack","Bunny Hood","Metal Box","Cloaking Device"};
const char* stageNames[]={"Princess Peach's Castle","Rainbow Cruise","Kongo Jungle","Jungle Japes","Great Bay","Temple","Brinstar","Brinstar Depths","Yoshi's Story","Yoshi's Island","Fountain of Dreams","Green Greens","Corneria","Venom","Pokemon Stadium","Poke Floats","Mute City","Big Blue","Onett","Fourside","Icicle Mountain","Mushroom Kingdom","Mushroom Kingdom II","Flat Zone","Dream Land N64","Yoshi's Island N64","Kongo Jungle N64","Battlefield","Final Destination"};
const char* titles[]={"Menu principal","1 jogador","Versus","Trofeus","Opcoes","Dados","Partida regular"};
const char* valueNames[]={"Modo","Tempo (minutos)","Vidas","Handicap","Dano (%)","Frequencia de itens","Vibracao","Saida de som","Musica","Efeitos","Modo de tela","Idioma","Limite de tempo","Fogo amigo","Pausa","Exibir placar","Selecao de cenario","Autodestruicao"};
const unsigned char minimum[]={0,0,1,0,50,0,0,0,0,0,0,0,0,0,0,0,0,0};
const unsigned char maximum[]={3,99,99,2,200,5,1,2,10,10,1,1,99,1,1,1,2,2};
const Entry* entries(int page,int& count) {
    count=0;
    switch(page){case 0:count=5;return mainEntries;case 1:count=4;return one;case 2:count=5;return vs;case 3:count=3;return trophies;case 4:count=5;return settings;case 5:count=5;return data;case 6:count=3;return regular;case 9:count=3;return stadium;case 12:count=10;return special;case 26:count=2;return archives;case 28:count=3;return records;case 33:count=6;return multi;default:return 0;}
}
int field(int page,int row) {
    if(page==13&&row<6)return row;
    if(page==15&&row<6)return row+12;
    if(page==19)return -1;if(page==20)return 7+row;if(page==21)return 10;if(page==23)return 11;return -1;
}
const char* value(const Melee360MenuConfig& c,int f,char* buffer) {
    int v=c.values[f];
    const char* modes[]={"Tempo","Vidas","Moedas","Bonus"};const char* handicap[]={"Desligado","Ligado","Automatico"};
    const char* sound[]={"Mono","Stereo","Surround"};const char* frequency[]={"Nenhuma","Muito baixa","Baixa","Media","Alta","Muito alta"};
    if(f==0)return modes[v];if(f==3)return handicap[v];if(f==5)return frequency[v];if(f==7)return sound[v];
    if(f==10)return v?"Ampla (16:9)":"Original (4:3)";if(f==11)return v?"English":"Portugues";
    if(f==6||f==13||f==14||f==15)return v?"Ligado":"Desligado";
    if(f==16){const char* stages[]={"Jogadores","Aleatorio","Em ordem"};return stages[v];}
    if(f==1||f==12){if(!v)return "Sem limite";}
    sprintf_s(buffer,24,"%u",v);return buffer;
}
void enter(Melee360MenuModel& m,int page) {
    if(m.depth>=16)return;m.historyPage[m.depth]=m.page;m.historySelection[m.depth++]=m.selection;m.page=page;m.selection=0;
}
unsigned int hash(const unsigned char* p,unsigned int bytes) {unsigned int v=2166136261u;for(unsigned int i=0;i<bytes;++i)v=(v^p[i])*16777619u;return v;}
bool valid(const Melee360MenuConfig& c) {
    for(int i=0;i<24;++i)if(i<18?(c.values[i]<minimum[i]||c.values[i]>maximum[i]):i<22?c.values[i]>1:c.values[i]!=0)return false;
    for(int i=0;i<35;++i)if(c.items[i]>1)return false;for(int i=0;i<29;++i)if(c.stages[i]>1)return false;
    for(int i=0;i<8;++i){if(c.names[i][8])return false;for(int j=0;j<8;++j)if(c.names[i][j]&&((unsigned char)c.names[i][j]<32||(unsigned char)c.names[i][j]>126))return false;}return true;
}
}
void Melee360MenuDefaults(Melee360MenuConfig& c) {memset(&c,0,sizeof(c));c.values[1]=2;c.values[2]=3;c.values[4]=100;c.values[5]=3;c.values[6]=1;c.values[7]=1;c.values[8]=8;c.values[9]=8;c.values[14]=1;memset(c.items,1,sizeof(c.items));memset(c.stages,1,sizeof(c.stages));for(int i=0;i<8;++i)sprintf_s(c.names[i],9,"PLAYER%d",i+1);}
void Melee360MenuReset(Melee360MenuModel& m) {memset(&m,0,sizeof(m));m.leaf=-1;Melee360MenuDefaults(m.config);}
int Melee360MenuCount(const Melee360MenuModel& m) {if(m.leaf>=0)return 1;int n;entries(m.page,n);if(n)return n;switch(m.page){case 13:return 9;case 15:return 6;case 16:return 35;case 17:return 29;case 18:return 8;case 19:return 4;case 21:case 23:return 1;case 20:return 3;case 24:return 2;default:return 1;}}
static const char* titleText(const Melee360MenuModel& m) {
    if(m.leaf>=0){int n;const Entry* e=entries(m.page,n);return e&&m.selection<n?e[m.selection].label:"Indisponivel";}
    if(m.page<=6)return titles[m.page];switch(m.page){case 9:return "Estadio";case 12:return "Versus especial";case 13:return "Regras";case 15:return "Regras extras";case 16:return "Itens";case 17:return "Cenarios aleatorios";case 18:return "Nomes";case 19:return "Vibracao";case 20:return "Som";case 21:return "Tela";case 23:return "Idioma do menu";case 24:return "Apagar configuracoes";case 26:return "Arquivos";case 28:return "Recordes";case 33:return "Multi-Man Melee";default:return "Menu";}
}
const char* Melee360MenuTranslate(const Melee360MenuModel& m,const char* text) {
    static const char* modeNames[][2]={{"Classic","Classico"},{"Adventure","Aventura"},{"All-Star","Todas as estrelas"},{"Target Test","Quebre os alvos"},{"Home-Run Contest","Concurso de rebatida"},{"Multi-Man Melee","Melee contra varios"},{"Camera Melee","Melee com camera"},{"Stamina Melee","Melee de energia"},{"Sudden Death","Morte subita"},{"Giant Melee","Melee gigante"},{"Tiny Melee","Melee miniatura"},{"Invisible Melee","Melee invisivel"},{"Fixed Camera","Camera fixa"},{"Single-Button","Um botao"},{"Lightning Melee","Melee rapido"},{"Slo-Mo Melee","Melee lento"},{"10-Man Melee","Contra 10 lutadores"},{"100-Man Melee","Contra 100 lutadores"},{"3-Minute Melee","Melee de 3 minutos"},{"15-Minute Melee","Melee de 15 minutos"},{"Endless Melee","Melee sem fim"},{"Cruel Melee","Melee cruel"},{"Special Movie","Video especial"},{"Party Ball","Bola de festa"},{"Barrel Cannon","Barril canhao"},{"Maxim Tomato","Tomate Maxim"},{"Heart Container","Recipiente de coracao"},{"Warp Star","Estrela de viagem"},{"Ray Gun","Pistola laser"},{"Fire Flower","Flor de fogo"},{"Lip's Stick","Vara de Lip"},{"Star Rod","Bastao estelar"},{"Beam Sword","Espada laser"},{"Home-Run Bat","Taco de beisebol"},{"Fan","Leque"},{"Hammer","Martelo"},{"Green Shell","Casco verde"},{"Red Shell","Casco vermelho"},{"Motion-Sensor Bomb","Mina de proximidade"},{"Super Mushroom","Super cogumelo"},{"Poison Mushroom","Cogumelo venenoso"},{"Starman","Estrela de invencibilidade"},{"Parasol","Guarda-sol"},{"Screw Attack","Ataque giratorio"},{"Bunny Hood","Orelhas de coelho"},{"Metal Box","Caixa de metal"},{"Cloaking Device","Dispositivo de invisibilidade"}};
    for(unsigned int i=0;i<sizeof(modeNames)/sizeof(modeNames[0]);++i){if(!strcmp(text,modeNames[i][0]))return m.config.values[11]?modeNames[i][0]:modeNames[i][1];if(!strcmp(text,modeNames[i][1]))return m.config.values[11]?modeNames[i][0]:modeNames[i][1];}
    if(!m.config.values[11])return text;
    static const char* translations[][2]={
        {"Menu principal","Main menu"},{"1 jogador","1 player"},{"Trofeus","Trophies"},{"Opcoes","Options"},{"Dados","Data"},
        {"Partida regular","Regular match"},{"Eventos","Events"},{"Estadio","Stadium"},{"Treinamento","Training"},{"Torneio","Tournament"},{"Versus especial","Special versus"},{"Regras","Rules"},{"Nomes","Names"},
        {"Galeria","Gallery"},{"Loteria","Lottery"},{"Colecao","Collection"},{"Vibracao","Rumble"},{"Som","Sound"},{"Tela","Display"},{"Idioma","Language"},{"Apagar dados","Erase data"},{"Fotos","Snapshots"},{"Arquivos","Archives"},{"Teste de som","Sound test"},{"Recordes","Records"},{"Dados especiais","Special messages"},{"Como jogar","How to play"},{"Diversos","Miscellaneous"},
        {"Regras extras","Extra rules"},{"Itens","Items"},{"Cenarios aleatorios","Random stages"},{"Idioma do menu","Menu language"},{"Apagar configuracoes","Reset settings"},{"Cancelar","Cancel"},{"Restaurar configuracoes do port","Restore port settings"},{"Voltar","Back"},
        {"Modo","Mode"},{"Tempo (minutos)","Time (minutes)"},{"Vidas","Stock"},{"Dano (%)","Damage (%)"},{"Frequencia de itens","Item frequency"},{"Saida de som","Sound output"},{"Musica","Music"},{"Efeitos","Effects"},{"Modo de tela","Display mode"},{"Limite de tempo","Time limit"},{"Fogo amigo","Friendly fire"},{"Pausa","Pause"},{"Exibir placar","Score display"},{"Selecao de cenario","Stage selection"},{"Autodestruicao","Self-destruct penalty"},
        {"Tempo","Time"},{"Moedas","Coin"},{"Desligado","Off"},{"Ligado","On"},{"Automatico","Automatic"},{"Nenhuma","None"},{"Muito baixa","Very low"},{"Baixa","Low"},{"Media","Medium"},{"Alta","High"},{"Muito alta","Very high"},{"Sem limite","No limit"},{"Jogadores","Players"},{"Aleatorio","Random"},{"Em ordem","In order"},{"Ampla (16:9)","Wide (16:9)"},{"Original (4:3)","Original (4:3)"},
        {"Capsula","Capsule"},{"Caixa","Crate"},{"Barril","Barrel"},{"Ovo","Egg"},{"Pokebola","Poke Ball"},{"Comida","Food"},
        {"Ainda indisponivel nesta build. Nenhuma partida foi iniciada.","Unavailable in this build. No match has been started."},
        {"A confirma; B cancela. Apaga apenas as configuracoes do port.","A confirms; B cancels. Only port settings are reset."},
        {"Cima/baixo: letra. Esquerda/direita: cursor. A: salvar. B: cancelar.","Up/down: letter. Left/right: cursor. A: save. B: cancel."},
        {"Regras salvas para integracao futura; partidas ainda indisponiveis.","Rules are saved; matches are still unavailable."},
        {"Volume da musica aplicado. Efeitos e modos de saida pendentes.","Music volume applied. Effects and output modes pending."},
        {"Idioma desta interface. Texturas e textos originais nao sao traduzidos.","Interface language. Original images and text are unchanged."},
        {"A: selecionar   B: voltar   Esquerda/direita: ajustar","A: select   B: back   Left/right: adjust"},
        {"Ainda indisponivel nesta build.","Unavailable in this build."},{"O gameplay e esta tela ainda nao foram integrados.","This screen is not available yet."},{"Editar nome","Edit name"},{"Restaurar configuracoes do port?","Restore port settings?"},{"A: confirmar    B: cancelar","A: confirm    B: cancel"},
        {"Configuracoes salvas.","Settings saved."},{"Arquivo de configuracoes invalido: preservado.","Invalid settings file: preserved."},{"Nao foi possivel criar o arquivo de configuracoes.","Could not create the settings file."},{"Falha ao salvar. A configuracao anterior foi preservada.","Save failed. Previous settings have been preserved."}
        ,{"Videos e musicas originais. A reproduz; B volta.","Original videos and music. A plays; B returns."},{"O video nao pode ser aberto.","The video could not be opened."}
    };
    for(unsigned int i=0;i<sizeof(translations)/sizeof(translations[0]);++i)if(!strcmp(text,translations[i][0]))return translations[i][1];return text;
}
const char* Melee360MenuTitle(const Melee360MenuModel& m) {return Melee360MenuTranslate(m,titleText(m));}
void Melee360MenuLabel(const Melee360MenuModel& m,int row,char* out,unsigned int bytes) {
    if(!bytes)return;const char* name="Voltar";int n;const Entry* e=entries(m.page,n);char buffer[24];
    if(m.leaf>=0){strcpy_s(out,bytes,Melee360MenuTranslate(m,"Voltar"));return;}
    if(e&&row>=0&&row<n)name=e[row].label;
    if(m.page==19){sprintf_s(out,bytes,"Controle %d: %s",row+1,Melee360MenuTranslate(m,m.config.values[6]&&!m.config.values[18+row]?"Ligado":"Desligado"));return;}
    int f=field(m.page,row);if(f>=0){sprintf_s(out,bytes,"%s: %s",Melee360MenuTranslate(m,valueNames[f]),Melee360MenuTranslate(m,value(m.config,f,buffer)));return;}
    if(m.page==13&&row>=6){const char* sub[]={"Regras extras","Itens","Cenarios aleatorios"};name=sub[row-6];}
    if(m.page==16){sprintf_s(out,bytes,"%s: %s",Melee360MenuTranslate(m,itemNames[row]),Melee360MenuTranslate(m,m.config.items[row]?"Ligado":"Desligado"));return;}
    if(m.page==17){sprintf_s(out,bytes,"%s: %s",stageNames[row],Melee360MenuTranslate(m,m.config.stages[row]?"Ligado":"Desligado"));return;}
    if(m.page==18){sprintf_s(out,bytes,"%d. %s",row+1,m.config.names[row]);return;}
    if(m.page==24)name=row?"Restaurar configuracoes do port":"Cancelar";
    strcpy_s(out,bytes,Melee360MenuTranslate(m,name));
}
static const char* descriptionText(const Melee360MenuModel& m) {
    if(m.leaf>=0)return "Ainda indisponivel nesta build. Nenhuma partida foi iniciada.";
    if(m.confirmReset)return "A confirma; B cancela. Apaga apenas as configuracoes do port.";
    if(m.editing)return "Cima/baixo: letra. Esquerda/direita: cursor. A: salvar. B: cancelar.";
    if(m.page==13||m.page==15||m.page==16||m.page==17)return "Regras salvas para integracao futura; partidas ainda indisponiveis.";
    if(m.page==20)return "Volume da musica aplicado. Efeitos e modos de saida pendentes.";
    if(m.page==26)return "Videos e musicas originais. A reproduz; B volta.";
    if(m.page==23)return "Idioma desta interface. Texturas e textos originais nao sao traduzidos.";
    return "A: selecionar   B: voltar   Esquerda/direita: ajustar";
}
const char* Melee360MenuDescription(const Melee360MenuModel& m) {return Melee360MenuTranslate(m,descriptionText(m));}
bool Melee360MenuInput(Melee360MenuModel& m,Melee360MenuAction a) {
    if(m.confirmReset){if(a==MenuBack)m.confirmReset=false;else if(a==MenuAccept){Melee360MenuDefaults(m.config);m.dirty=true;m.confirmReset=false;}return false;}
    if(m.editing){if(a==MenuBack)m.editing=false;else if(a==MenuAccept){memcpy(m.config.names[m.selection],m.editedName,9);m.dirty=true;m.editing=false;}else if(a==MenuLeft||a==MenuRight)m.editPosition=(m.editPosition+(a==MenuLeft?7:1))%8;else{char& c=m.editedName[m.editPosition];if(c<32)c=' ';c=(char)(32+((c-32)+(a==MenuUp?1:94))%95);}return false;}
    if(m.leaf>=0){if(a==MenuAccept||a==MenuBack)m.leaf=-1;return false;}
    if(m.page==0){int old=m.selection,selection=old,destination=0;unsigned int bits=a==MenuUp?1:a==MenuDown?2:a==MenuAccept?16:a==MenuBack?32:0;
        if(Melee360OriginalRootInput(bits,&selection,&destination))return true;
        if(destination){m.selection=old;enter(m,destination);}else m.selection=selection;return false;}
    if(a==MenuBack){if(!m.depth)return true;--m.depth;m.page=m.historyPage[m.depth];m.selection=m.historySelection[m.depth];return false;}
    int count=Melee360MenuCount(m);
    if(a==MenuUp||a==MenuDown){m.selection=(m.selection+(a==MenuUp?count-1:1))%count;return false;}
    if(m.page==19&&(a==MenuAccept||a==MenuLeft||a==MenuRight)){if(!m.config.values[6]){m.config.values[6]=1;for(int i=18;i<22;++i)m.config.values[i]=1;}m.config.values[18+m.selection]^=1;m.dirty=true;return false;}
    int f=field(m.page,m.selection);int dir=a==MenuLeft?-1:1;
    if(f>=0&&(a==MenuAccept||a==MenuLeft||a==MenuRight)){int range=maximum[f]-minimum[f]+1;int v=m.config.values[f]-minimum[f];m.config.values[f]=(unsigned char)(minimum[f]+(v+dir+range)%range);m.dirty=true;return false;}
    if((m.page==16||m.page==17)&&(a==MenuAccept||a==MenuLeft||a==MenuRight)){unsigned char* values=m.page==16?m.config.items:m.config.stages;values[m.selection]^=1;m.dirty=true;return false;}
    if(a!=MenuAccept)return false;
    if(m.page==18){memcpy(m.editedName,m.config.names[m.selection],9);for(int i=0;i<8;++i)if(!m.editedName[i])m.editedName[i]=' ';m.editedName[8]=0;m.editPosition=0;m.editing=true;return false;}
    if(m.page==24){if(m.selection)m.confirmReset=true;else return Melee360MenuInput(m,MenuBack);return false;}
    if(m.page==13&&m.selection>=6){enter(m,15+m.selection-6);return false;}
    int n;const Entry* e=entries(m.page,n);if(e&&m.selection<n){if(e[m.selection].target>=100)m.leaf=e[m.selection].target;else enter(m,e[m.selection].target);}return false;
}
bool Melee360ConfigEncode(const Melee360MenuConfig& c,unsigned char* p,unsigned int bytes) {
    if(!p||bytes!=Melee360ConfigBytes||!valid(c))return false;memset(p,0,bytes);memcpy(p,"M36C",4);p[4]=1;
    memcpy(p+8,c.values,24);memcpy(p+32,c.items,35);memcpy(p+67,c.stages,29);memcpy(p+96,c.names,72);
    unsigned int h=hash(p,172);for(int i=0;i<4;++i)p[172+i]=(unsigned char)(h>>(i*8));return true;
}
bool Melee360ConfigDecode(Melee360MenuConfig& c,const unsigned char* p,unsigned int bytes) {
    if(!p||bytes!=Melee360ConfigBytes||memcmp(p,"M36C",4)||p[4]!=1)return false;unsigned int h=0;for(int i=0;i<4;++i)h|=(unsigned int)p[172+i]<<(i*8);if(h!=hash(p,172))return false;
    Melee360MenuConfig candidate;memcpy(candidate.values,p+8,24);memcpy(candidate.items,p+32,35);memcpy(candidate.stages,p+67,29);memcpy(candidate.names,p+96,72);if(!valid(candidate))return false;c=candidate;return true;
}
