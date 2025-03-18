#include "../../../constants.h"
#include "snore.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"

void BattleCommand_Snore(void){
//  snore
    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVar);
    // AND_A(SLP);
    // RET_NZ ;
    if((GetBattleVar(BATTLE_VARS_STATUS) & SLP) == 0) {
        // CALL(aResetDamage);
        ResetDamage();
        // LD_A(0x1);
        // LD_addr_A(wAttackMissed);
        wram->wAttackMissed = TRUE;
        // CALL(aFailMove);
        FailMove();
        // JP(mEndMoveEffect);
        return EndMoveEffect();
    }
}
