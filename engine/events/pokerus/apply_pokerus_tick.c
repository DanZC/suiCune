#include "../../../constants.h"
#include "apply_pokerus_tick.h"

//  decreases all pokemon's pokerus counter by b. if the lower nybble reaches zero, the pokerus is cured.
void ApplyPokerusTick(uint8_t b){
    // LD_HL(wPartyMon1PokerusStatus);  // wPartyMon1 + MON_PKRS
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;  // make sure it's not wasting time on an empty party
    if(wram->wPartyCount == 0)
        return;
    // LD_C_A;
    uint8_t c = wram->wPartyCount;
    struct PartyMon* hl = wram->wPartyMon;

    do {
    // loop:
        uint8_t status = hl->status & 0xf;
        // LD_A_hl;
        // AND_A(0xf);  // lower nybble is the number of days remaining
        // IF_Z goto next;  // if already 0, skip
        if(status == 0)
            continue;
        // SUB_A_B;  // subtract the number of days
        // IF_NC goto ok;  // max(result, 0)
        // XOR_A_A;
        if(status < b)
            status = 0;
        else
            status -= b;

    // ok:
        // LD_D_A;  // back up this value because we need to preserve the strain (upper nybble)
        // LD_A_hl;
        // AND_A(0xf0);
        // ADD_A_D;
        // LD_hl_A;  // this prevents a cured pokemon from recontracting pokerus
        hl->status = (hl->status & 0xf0) | status;

    // next:
        // LD_DE(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_DE;
        // DEC_C;
        // IF_NZ goto loop;
    } while(hl++, --c != 0);
    // RET;

}
