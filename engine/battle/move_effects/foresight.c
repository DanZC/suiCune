#include "../../../constants.h"
#include "foresight.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_Foresight(void){
//  foresight

    uint8_t* ss1_opp;
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto failed;

    // CALL(aCheckHiddenOpponent);
    // IF_NZ goto failed;

    // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    // CALL(aGetBattleVarAddr);
    // BIT_hl(SUBSTATUS_IDENTIFIED);
    // IF_NZ goto failed;
    if(wram->wAttackMissed
    || CheckHiddenOpponent()
    || ((ss1_opp = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS1_OPP)), bit_test(*ss1_opp, SUBSTATUS_IDENTIFIED))) {
    // failed:
        // JP(mFailMove);
        return FailMove();
    }

    // SET_hl(SUBSTATUS_IDENTIFIED);
    bit_set(*ss1_opp, SUBSTATUS_IDENTIFIED);
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mIdentifiedText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(IdentifiedText);
}
