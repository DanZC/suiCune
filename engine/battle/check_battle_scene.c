#include "../../constants.h"
#include "check_battle_scene.h"
#include "../../home/copy.h"
#include "../../home/sram.h"

// Returns false (carry) if battle scene is turned off.
bool CheckBattleScene(void) {
    if(wram->wLinkMode == LINK_MOBILE) {
        if(gb_read(wcd2f) != 0) {
            return bit_test(wram->w5_dc00[0], 0);
        }
        OpenSRAM(MBANK(as4_a60c));  // MBC30 bank used by JP Crystal// inaccessible by MBC3
        uint8_t c = gb_read(s4_a60c);
        CloseSRAM();
        return bit_test(c, 0);
    }
    return !bit_test(gOptions.options, BATTLE_SCENE);
}
