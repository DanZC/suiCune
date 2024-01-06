#include "../../../constants.h"
#include "nightmare.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_Nightmare(void){
//  nightmare

//  Can't hit an absent opponent.

    // CALL(aCheckHiddenOpponent);
    // IF_NZ goto failed;

//  Can't hit a substitute.

    // CALL(aCheckSubstituteOpp);
    // IF_NZ goto failed;

//  Only works on a sleeping opponent.

    // LD_A(BATTLE_VARS_STATUS_OPP);
    // CALL(aGetBattleVarAddr);
    // AND_A(SLP);
    // IF_Z goto failed;
    if(CheckHiddenOpponent_Conv() || CheckSubstituteOpp_Conv() || (GetBattleVar_Conv(BATTLE_VARS_STATUS_OPP) & SLP) == 0)
        goto failed;

//  Bail if the opponent is already having a nightmare.

    // LD_A(BATTLE_VARS_SUBSTATUS1_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* ss1_opp = GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS1_OPP);
    // BIT_hl(SUBSTATUS_NIGHTMARE);
    // IF_NZ goto failed;
    if(bit_test(*ss1_opp, SUBSTATUS_NIGHTMARE))
        goto failed;

//  Otherwise give the opponent a nightmare.

    // SET_hl(SUBSTATUS_NIGHTMARE);
    bit_set(*ss1_opp, SUBSTATUS_NIGHTMARE);
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mStartedNightmareText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(StartedNightmareText);

failed:
    // CALL(aAnimateFailedMove);
    AnimateFailedMove();
    // JP(mPrintButItFailed);
    return PrintButItFailed();

}
