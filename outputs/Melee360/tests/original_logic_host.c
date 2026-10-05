#include "../src/original_logic_core.h"
#include "../src/training_stage.h"
#include <stdio.h>
int main(void){if(!Melee360OriginalLogicProbe())return 1;if(!Melee360FightSetupProbe())return 2;if(!Melee360TrainingProbe())return 3;puts("Original directed intersections, nearest swept contact, physics limits, Mario human / Link CPU setup and Training isolation passed");return 0;}
