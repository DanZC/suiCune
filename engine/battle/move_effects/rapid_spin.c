#include "../../../constants.h"
#include "rapid_spin.h"
#include "../effect_commands.h"
#include "../../../home/battle_vars.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_ClearHazards(void){
//  clearhazards

    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVarAddr);
    uint8_t* ss4 = GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS4);
    // BIT_hl(SUBSTATUS_LEECH_SEED);
    // IF_Z goto not_leeched;
    if(bit_test(*ss4, SUBSTATUS_LEECH_SEED)) {
        // RES_hl(SUBSTATUS_LEECH_SEED);
        bit_reset(*ss4, SUBSTATUS_LEECH_SEED);
        // LD_HL(mShedLeechSeedText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox_Conv2(ShedLeechSeedText);
    }

// not_leeched:

    // LD_HL(wPlayerScreens);
    // LD_DE(wPlayerWrapCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_screens_wrap;
    // LD_HL(wEnemyScreens);
    // LD_DE(wEnemyWrapCount);
    uint8_t* screens = (hram->hBattleTurn == 0)? &wram->wPlayerScreens: &wram->wEnemyScreens;
    uint8_t* wrap    = (hram->hBattleTurn == 0)? &wram->wPlayerWrapCount: &wram->wEnemyWrapCount;

// got_screens_wrap:
    // BIT_hl(SCREENS_SPIKES);
    // IF_Z goto no_spikes;
    if(bit_test(*screens, SCREENS_SPIKES)) {
        // RES_hl(SCREENS_SPIKES);
        bit_reset(*screens, SCREENS_SPIKES);
        // LD_HL(mBlewSpikesText);
        // PUSH_DE;
        // CALL(aStdBattleTextbox);
        StdBattleTextbox_Conv2(BlewSpikesText);
        // POP_DE;
    }

// no_spikes:

    // LD_A_de;
    // AND_A_A;
    // RET_Z ;
    if(*wrap == 0)
        return;

    // XOR_A_A;
    // LD_de_A;
    *wrap = 0;
    // LD_HL(mReleasedByText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(ReleasedByText);

}
