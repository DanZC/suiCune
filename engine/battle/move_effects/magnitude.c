#include "../../../constants.h"
#include "magnitude.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../core.h"
#include "../../../data/text/battle.h"
#include "../../../data/moves/magnitude_power.h"

void BattleCommand_GetMagnitude(void){
//  getmagnitude

    // PUSH_BC;
    // CALL(aBattleRandom);
    // LD_B_A;
    uint8_t b = v_BattleRandom();
    // LD_HL(mMagnitudePower);
    const uint8_t (*hl)[3] = MagnitudePower;

    do {
    // loop:
        // LD_A_hli;
        // CP_A_B;
        // IF_NC goto ok;
        // INC_HL;
        // INC_HL;
        // goto loop;
    } while((hl++)[0][0] < b);


// ok:
    // LD_D_hl;
    gBattleCmdState.d = hl[0][1];
    // PUSH_DE;
    // INC_HL;
    // LD_A_hl;
    // LD_addr_A(wTextDecimalByte);
    wram->wTextDecimalByte = hl[0][2];
    // CALL(aBattleCommand_MoveDelay);
    BattleCommand_MoveDelay();
    // LD_HL(mMagnitudeText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(MagnitudeText);
    // POP_DE;
    // POP_BC;
    // RET;

// INCLUDE "data/moves/magnitude_power.asm"

}
