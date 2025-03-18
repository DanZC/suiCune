#include "../../../constants.h"
#include "focus_energy.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_FocusEnergy(void){
//  focusenergy

    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVarAddr);
    uint8_t* hl = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS4);
    // BIT_hl(SUBSTATUS_FOCUS_ENERGY);
    // IF_NZ goto already_pumped;
    if(bit_test(*hl, SUBSTATUS_FOCUS_ENERGY)) {
    // already_pumped:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintButItFailed);
        return PrintButItFailed();
    }

    // SET_hl(SUBSTATUS_FOCUS_ENERGY);
    bit_set(*hl, SUBSTATUS_FOCUS_ENERGY);
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mGettingPumpedText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(GettingPumpedText);

}
