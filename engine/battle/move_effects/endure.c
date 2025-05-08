#include "../../../constants.h"
#include "endure.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_Endure(void){
//  endure

//  Endure shares code with Protect. See protect.asm.

    // CALL(aProtectChance);
    // RET_C ;
    if(!ProtectChance())
        return;

    // LD_A(BATTLE_VARS_SUBSTATUS1);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_ENDURE);
    bit_set(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS1), SUBSTATUS_ENDURE);

    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();

    // LD_HL(mBracedItselfText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(BracedItselfText);

}
