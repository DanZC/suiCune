#include "../../constants.h"
#include "poisonstep_pals.h"
#include "../../home/delay.h"
#include "../../home/palettes.h"
#include "../tilesets/timeofday_pals.h"

static void LoadPoisonBGPals_LoadPals(void) {
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_NZ goto cgb;
    if(hram.hCGB) {
    // cgb:
        // LDH_A_addr(rSVBK);
        // PUSH_AF;
        // LD_A(BANK(wBGPals2));
        // LDH_addr_A(rSVBK);
        // LD_HL(wBGPals2);
        uint16_t* hl = (uint16_t*)wram_ptr(wBGPals2);
        // LD_C(4 * PALETTE_SIZE);
        uint8_t c = 4 * NUM_PAL_COLORS;

        do {
        // loop:
            // LD_A(LOW((1 << 0) * 28 + (1 << 5) * 21 + (1 << 10) * 31));
            // LD_hli_A;
            // LD_A(HIGH((1 << 0) * 28 + (1 << 5) * 21 + (1 << 10) * 31));
            // LD_hli_A;
            *(hl++) = (1 << 0) * 28 + (1 << 5) * 21 + (1 << 10) * 31;
            // DEC_C;
            // IF_NZ goto loop;
        } while(--c != 0);
        // POP_AF;
        // LDH_addr_A(rSVBK);
        // LD_A(TRUE);
        // LDH_addr_A(hCGBPalUpdate);
        hram.hCGBPalUpdate = TRUE;
        // LD_C(4);
        // CALL(aDelayFrames);
        DelayFrames(4);
        // FARCALL(av_UpdateTimePals);
        v_UpdateTimePals();
        // RET;
        return;
    }
    // LD_A_addr(wTimeOfDayPal);
    // maskbits(NUM_DAYTIMES, 0);
    // CP_A(DARKNESS_F);
    // LD_A(0b00000000);
    // IF_Z goto convert_pals;
    // LD_A(0b10101010);
    uint8_t a = (gPlayer.timeOfDayPal & (NUM_DAYTIMES - 1))? 0b10101010: 0b00000000;

// convert_pals:
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(a);
    // LD_C(4);
    // CALL(aDelayFrames);
    DelayFrames(4);
    // FARCALL(av_UpdateTimePals);
    v_UpdateTimePals();
    // RET;
}

void LoadPoisonBGPals(void){
    // CALL(aLoadPoisonBGPals_LoadPals);
    LoadPoisonBGPals_LoadPals();
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_NZ ;
// code was probably dummied out here
    // RET;
}
