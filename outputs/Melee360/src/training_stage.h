#ifndef MELEE360_TRAINING_STAGE_H
#define MELEE360_TRAINING_STAGE_H
#ifdef __cplusplus
extern "C" {
#endif
void Melee360StageInit(void);
void Melee360StageSetPosition(int,float,float);
void Melee360StageMove(int,int);
int Melee360StageTestPlaceAt(int);
void Melee360StageCursor(float*,float*,int*);
int Melee360StageKind(int);
int Melee360StageFrame(int);
struct StartMeleeData;
const struct StartMeleeData* Melee360TrainingStartData(void);
int Melee360TrainingPrepare(int);
int Melee360TrainingProbe(void);
int Melee360FightPrepare(void);
int Melee360FightSetupProbe(void);
const struct StartMeleeData* Melee360FightStartData(void);
#ifdef __cplusplus
}
#endif
#endif
