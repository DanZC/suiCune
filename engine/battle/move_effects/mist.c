#include "../../../constants.h"
#include "mist.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_Mist(void){
//  mist

    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVarAddr);
    uint8_t* ss4 = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS4);
    // BIT_hl(SUBSTATUS_MIST);
    // IF_NZ goto already_mist;
    if(bit_test(*ss4, SUBSTATUS_MIST)) {
    // already_mist:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintButItFailed);
        return PrintButItFailed();
    }

    // SET_hl(SUBSTATUS_MIST);
    bit_set(*ss4, SUBSTATUS_MIST);
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mMistText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(MistText);

}
