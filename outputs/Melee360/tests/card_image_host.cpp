#include "../src/card_image.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
int main() {
    unsigned char serial[32];memset(serial,42,32);
    unsigned char* image=(unsigned char*)malloc(MELEE360_CARD_BYTES);if(!image) return 1;
    if(!Melee360FormatCardImage(image,MELEE360_CARD_BYTES,serial)||!Melee360CheckCardSystem(image,MELEE360_CARD_BYTES)) return 2;
    image[8192]^=1;if(!Melee360CheckCardSystem(image,MELEE360_CARD_BYTES)) return 3;
    image[16384]^=1;if(Melee360CheckCardSystem(image,MELEE360_CARD_BYTES)) return 4;
    Melee360FormatCardImage(image,MELEE360_CARD_BYTES,serial);
    image[24580]^=1;if(!Melee360CheckCardSystem(image,MELEE360_CARD_BYTES)) return 5;
    image[32772]^=1;if(Melee360CheckCardSystem(image,MELEE360_CARD_BYTES)) return 6;
    Melee360FormatCardImage(image,MELEE360_CARD_BYTES,serial);
    image[100]^=1;if(Melee360CheckCardSystem(image,MELEE360_CARD_BYTES)) return 7;
    if(Melee360FormatCardImage(image,MELEE360_CARD_BYTES-1,serial)) return 8;
    free(image);puts("Virtual card system checksum/redundancy/corruption tests passed");return 0;
}
