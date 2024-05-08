#include "../../constants.h"
#include "pokeball_wobble.h"
#include "../../home/random.h"
#include "../../data/battle/wobble_probabilities.h"

//  Returns whether a Poke Ball will wobble in the catch animation.
//  Whether a Pokemon is caught is determined beforehand.
uint8_t GetPokeBallWobble(void){
    // PUSH_DE;

    // LDH_A_addr(rSVBK);
    // LD_D_A;
    // PUSH_DE;

    // LD_A(BANK(wThrownBallWobbleCount));  // aka BANK(wFinalCatchRate)
    // LDH_addr_A(rSVBK);

    // LD_A_addr(wThrownBallWobbleCount);
    // INC_A;
    // LD_addr_A(wThrownBallWobbleCount);
    uint8_t a = ++wram->wThrownBallWobbleCount;
    uint8_t c;

//  Wobble up to 3 times.
    // CP_A(3 + 1);
    // IF_Z goto finished;
    if(a == 3 + 1) {
    // finished:
        // LD_A_addr(wWildMon);
        // AND_A_A;
        // LD_C(1);  // caught
        // IF_NZ goto done;
        // LD_C(2);  // escaped
        c = (wram->wWildMon == 0)? 2: 1;
    }

    // LD_A_addr(wWildMon);
    // AND_A_A;
    // LD_C(0);  // next
    // IF_NZ goto done;
    else if(wram->wWildMon != 0) {
        c = 0;
    }

    else {
        // LD_HL(mWobbleProbabilities);
        const uint8_t (*hl)[2] = WobbleProbabilities;
        // LD_A_addr(wFinalCatchRate);
        // LD_B_A;
        uint8_t b = wram->wFinalCatchRate;

        while(1) {
        // loop:
            // LD_A_hli;
            // CP_A_B;
            // IF_NC goto checkwobble;
            if(hl[0][0] >= b)
                break;
            // INC_HL;
            hl++;
            // goto loop;
        }

    // checkwobble:
        // LD_B_hl;
        // CALL(aRandom);
        // CP_A_B;
        // LD_C(0);  // next
        // IF_C goto done;
        // LD_C(2);  // escaped
        c = (Random_Conv() < hl[0][1])? 0: 2;
        // goto done;
    }

// done:
    // POP_DE;
    // LD_E_A;
    // LD_A_D;
    // LDH_addr_A(rSVBK);
    // LD_A_E;
    // POP_DE;
    // RET;
    return c;
// INCLUDE "data/battle/wobble_probabilities.asm"

}
