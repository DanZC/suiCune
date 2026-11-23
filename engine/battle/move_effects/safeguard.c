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
    struct BattleStatus* status = UserBattleStatus();

// ok:
    // BIT_hl(SCREENS_SAFEGUARD);
    // IF_NZ goto failed;
    if(bit_test(status->screens, SCREENS_SAFEGUARD)) {
    // failed:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintButItFailed);
        return PrintButItFailed();
    }

    // SET_hl(SCREENS_SAFEGUARD);
    bit_set(status->screens, SCREENS_SAFEGUARD);
    // LD_A(5);
    // LD_de_A;
    status->safeguardCount = 5;
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mCoveredByVeilText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(CoveredByVeilText);

}
