#ifndef MELEE360_MENU_MODEL_H
#define MELEE360_MENU_MODEL_H
enum Melee360MenuAction {MenuUp,MenuDown,MenuLeft,MenuRight,MenuAccept,MenuBack};
struct Melee360MenuConfig {unsigned char values[24],items[35],stages[29];char names[8][9];};
struct Melee360MenuModel {
    int page,selection,depth,historyPage[16],historySelection[16],leaf,editPosition;
    bool dirty,editing,confirmReset;char editedName[9];Melee360MenuConfig config;
};
void Melee360MenuDefaults(Melee360MenuConfig& config);
void Melee360MenuReset(Melee360MenuModel& model);
int Melee360MenuCount(const Melee360MenuModel& model);
const char* Melee360MenuTitle(const Melee360MenuModel& model);
void Melee360MenuLabel(const Melee360MenuModel& model,int row,char* out,unsigned int bytes);
const char* Melee360MenuDescription(const Melee360MenuModel& model);
const char* Melee360MenuTranslate(const Melee360MenuModel& model,const char* text);
// Returns true only when B at the root requests return to the title.
bool Melee360MenuInput(Melee360MenuModel& model,Melee360MenuAction action);
enum {Melee360ConfigBytes=176};
bool Melee360ConfigEncode(const Melee360MenuConfig& config,unsigned char* data,unsigned int bytes);
bool Melee360ConfigDecode(Melee360MenuConfig& config,const unsigned char* data,unsigned int bytes);
#endif
