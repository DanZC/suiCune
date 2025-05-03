#include "../../../constants.h"
#include "lock_on.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_LockOn(void){
//  lockon

    // CALL(aCheckSubstituteOpp);
    // IF_NZ goto fail;

    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto fail;
    if(CheckSubstituteOpp() || wram->wAttackMissed) {
    // fail:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintDidntAffect);
        return PrintDidntAffect();
    }

    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_LOCK_ON);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5_OPP), SUBSTATUS_LOCK_ON);
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();

    // LD_HL(mTookAimText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(TookAimText);

}
