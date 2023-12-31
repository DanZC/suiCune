#include "../../../constants.h"
#include "destiny_bond.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_DestinyBond(void){
//  destinybond

    // LD_A(BATTLE_VARS_SUBSTATUS5);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_DESTINY_BOND);
    bit_set(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS5), SUBSTATUS_DESTINY_BOND);
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mDestinyBondEffectText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(DestinyBondEffectText);

}
