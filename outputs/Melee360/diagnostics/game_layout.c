/* Compile-only layout measurement: never included in a runnable build.
 * Assertions are disabled HERE solely to measure the mismatching sizes.
 * Normal sources retain their assertions and are never patched. */
#include <Runtime/platform.h>
#undef ASSERT_SIZE
#undef ASSERT_OFFSET
#define ASSERT_SIZE(type, size)
#define ASSERT_OFFSET(type, member, offset)
#include <melee/gm/types.h>
const unsigned int Melee360GameLayout[] = {
    sizeof(struct gmm_x0_vsmodes), 0x1850 - 0x588,
    sizeof(struct gmm_x0), 0x10A30,
    sizeof(struct TmData), 0x574,
    sizeof(struct VsSceneController), 0x2528,
    sizeof(struct StartMeleeRules), 0x60,
    sizeof(struct PlayerInitData), 0x24,
    sizeof(struct StartMeleeData), 0x138,
    sizeof(struct VsModeData), 0x140,
    offsetof(struct VsSceneState, x24C), 0x24C,
    sizeof(struct VsSceneState), 0x24C8,
    offsetof(struct VsSceneController, start), 0x24C8
};
