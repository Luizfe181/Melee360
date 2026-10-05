/* Layout and on-target bit order checks; no game startup is executed. */
#define DEBUG 1
#define LINT 1
#include <melee/gm/types.h>
#include <string.h>
ASSERT_SIZE(struct StartMeleeRules, 0x60);
ASSERT_SIZE(struct StartMeleeData, 0x138);
ASSERT_SIZE(struct VsModeData, 0x140);
ASSERT_OFFSET(struct StartMeleeRules, x6, 6);
ASSERT_OFFSET(struct StartMeleeRules, x20, 0x20);
ASSERT_OFFSET(struct StartMeleeRules, on_match_start, 0x44);
int Melee360GameRulesProbe(void)
{
    struct StartMeleeRules rules;
    const u8* bytes = (const u8*)&rules;
    memset(&rules, 0, sizeof(rules));
    rules.match_kind = 5;
    rules.timer_enabled = 1;
    rules.friendly_fire = 1;
    rules.is_stock = 1;
    rules.x3_7 = 1;
    rules.is_vs = 1;
    rules.x5_7 = 1;
    rules.x6 = 0xA5;
    /* Xenon, like GameCube, is big endian; fields must start at the MSB. */
    return bytes[0] == 0xA2 && bytes[1] == 0x01 &&
           bytes[2] == 0x80 && bytes[3] == 0x01 &&
           bytes[4] == 0x40 && bytes[5] == 0x01 && bytes[6] == 0xA5;
}
