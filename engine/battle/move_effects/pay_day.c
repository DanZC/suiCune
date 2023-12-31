#include "../../../constants.h"
#include "pay_day.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_PayDay(void){
//  payday

    // XOR_A_A;
    // LD_HL(wStringBuffer1);
    // LD_hli_A;
    wram->wStringBuffer1[0] = 0;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A_addr(wBattleMonLevel);
    // IF_Z goto ok;
    // LD_A_addr(wEnemyMonLevel);
    uint8_t level = (hram->hBattleTurn == 0)? wram->wBattleMon.level: wram->wEnemyMon.level;

// ok:

    // ADD_A_A;
    level <<= 1;
    // LD_HL(wPayDayMoney + 2);
    // ADD_A_hl;
    uint32_t temp = wram->wPayDayMoney[2] + level;
    // LD_hld_A;
    wram->wPayDayMoney[2] = (uint8_t)temp;
    // IF_NC goto done;
    if(temp > 255) {
        // INC_hl;
        // DEC_HL;
        // IF_NZ goto done;
        if(++wram->wPayDayMoney[1] == 0) {
            // INC_hl;
            wram->wPayDayMoney[0]++;
        }
    }
// done:
    // LD_HL(mCoinsScatteredText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(CoinsScatteredText);

}
