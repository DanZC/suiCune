#include "../../../constants.h"
#include "frustration.h"
#include "../effect_commands.h"

void BattleCommand_FrustrationPower(void){
//  frustrationpower
    // PUSH_BC;
    // LD_HL(wBattleMonHappiness);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wEnemyMonHappiness);
    uint8_t happiness = (hram->hBattleTurn == TURN_PLAYER)? wram->wBattleMon.happiness: wram->wEnemyMon.happiness;

// ok:
    // LD_A(0xff);
    // SUB_A_hl;
    // LDH_addr_A(hMultiplicand + 2);
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A(10);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    uint32_t n = (0xff - happiness) * 10;
    // LD_A(25);
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);
    n /= 4;
    // LDH_A_addr(hQuotient + 3);
    // LD_D_A;
    gBattleCmdState.d = (uint8_t)n;
    // POP_BC;
    // RET;
}
