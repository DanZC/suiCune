#include "../../../constants.h"
#include "safeguard.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_Safeguard(void){
//  safeguard

    // LD_HL(wPlayerScreens);
    // LD_DE(wPlayerSafeguardCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wEnemyScreens);
    // LD_DE(wEnemySafeguardCount);
    uint8_t* screens = (hram->hBattleTurn == 0)? &wram->wPlayerScreens: &wram->wEnemyScreens;
    uint8_t* safeguard_cnt = (hram->hBattleTurn == 0)? &wram->wPlayerSafeguardCount: &wram->wEnemySafeguardCount;

// ok:
    // BIT_hl(SCREENS_SAFEGUARD);
    // IF_NZ goto failed;
    if(bit_test(*screens, SCREENS_SAFEGUARD)) {
    // failed:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintButItFailed);
        return PrintButItFailed();
    }

    // SET_hl(SCREENS_SAFEGUARD);
    bit_set(*screens, SCREENS_SAFEGUARD);
    // LD_A(5);
    // LD_de_A;
    *safeguard_cnt = 5;
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mCoveredByVeilText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(CoveredByVeilText);

}
