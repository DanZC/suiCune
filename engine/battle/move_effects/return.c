#include "../../../constants.h"
#include "return.h"
#include "../effect_commands.h"

void BattleCommand_HappinessPower(void){
//  happinesspower
    // PUSH_BC;
    // LD_HL(wBattleMonHappiness);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wEnemyMonHappiness);
    uint8_t happiness = (hram.hBattleTurn == TURN_PLAYER)? wram->wBattleMon.happiness: wram->wEnemyMon.happiness;

// ok:
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_hl;
    // LDH_addr_A(hMultiplicand + 2);
    // LD_A(10);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    uint32_t n = happiness * 10;
    // LD_A(25);
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);
    n /= 25;
    // LDH_A_addr(hQuotient + 3);
    // LD_D_A;
    gBattleCmdState.d = (uint8_t)n;
    // POP_BC;
    // RET;

}
