#include "../../../constants.h"
#include "../hidden_power.h"
#include "../effect_commands.h"

void BattleCommand_HiddenPower(void){
//  hiddenpower

    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wAttackMissed)
        return;
    // FARCALL(aHiddenPowerDamage);
    gBattleCmdState.d = HiddenPowerDamage();
    // RET;
    return;
}
