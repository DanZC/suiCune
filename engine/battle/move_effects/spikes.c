#include "../../../constants.h"
#include "spikes.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_Spikes(void){
//  spikes

    // LD_HL(wEnemyScreens);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_screens;
    // LD_HL(wPlayerScreens);
    uint8_t* hl = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemyScreens: &wram->wPlayerScreens;

// got_screens:

//  Fails if spikes are already down!

    // BIT_hl(SCREENS_SPIKES);
    // IF_NZ goto failed;
    if(bit_test(*hl, SCREENS_SPIKES)) {
    // failed:
        // JP(mFailMove);
        return FailMove();
    }

//  Nothing else stops it from working.

    // SET_hl(SCREENS_SPIKES);
    bit_set(*hl, SCREENS_SPIKES);

    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();

    // LD_HL(mSpikesText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(SpikesText);

}
