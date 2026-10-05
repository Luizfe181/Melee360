/* Measurement only. Never linked; runnable sources retain layout assertions. */
#include <Runtime/platform.h>
#undef ASSERT_SIZE
#undef ASSERT_OFFSET
#define ASSERT_SIZE(type, size)
#define ASSERT_OFFSET(type, member, offset)
#include <melee/ft/types.h>
const unsigned int Melee360FighterLayout[] = {
    sizeof(struct Fighter), 0x23EC,
    offsetof(struct Fighter, gobj), 0,
    offsetof(struct Fighter, cur_pos), 0xB0,
    offsetof(struct Fighter, input), 0x620,
    offsetof(struct Fighter, mv), 0x2340
};
