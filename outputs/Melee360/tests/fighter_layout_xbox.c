/* Actual XDK ABI checks; compilation fails on any mismatch. */
#include <melee/ft/types.h>
ASSERT_SIZE(struct Fighter, 0x23EC);
ASSERT_SIZE(union Fighter_x594, 4);
ASSERT_OFFSET(struct Fighter, x594, 0x594);
ASSERT_OFFSET(struct Fighter, x598, 0x598);
ASSERT_OFFSET(struct Fighter, cur_pos, 0xB0);
ASSERT_OFFSET(struct Fighter, input, 0x620);
ASSERT_OFFSET(struct Fighter, coll_data, 0x6F0);
ASSERT_OFFSET(struct Fighter, cur_anim_frame, 0x894);
ASSERT_OFFSET(struct Fighter, mv, 0x2340);
