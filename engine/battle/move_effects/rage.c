#include "../../../constants.h"
#include "rage.h"
#include "../../../home/battle_vars.h"

void BattleCommand_Rage(void){
//  rage
    // LD_A(BATTLE_VARS_SUBSTATUS4);
    // CALL(aGetBattleVarAddr);
    // SET_hl(SUBSTATUS_RAGE);
    bit_set(*GetBattleVarAddr_Conv(BATTLE_VARS_SUBSTATUS4), SUBSTATUS_RAGE);
    // RET;
}
