#include "../../../constants.h"
#include "check_pokerus.h"

bool v_CheckPokerus(void){
//  Return carry if a monster in your party has Pokerus

//  Get number of monsters to iterate over
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // IF_Z goto NoPokerus;
    if(gPokemon.partyCount != 0) {
        // LD_B_A;
        uint8_t b = gPokemon.partyCount;
    //  Check each monster in the party for Pokerus
        // LD_HL(wPartyMon1PokerusStatus);
        struct PartyMon* hl = gPokemon.partyMon;
        // LD_DE(PARTYMON_STRUCT_LENGTH);

        do {
        // Check:
            // LD_A_hl;
            // AND_A(0x0f);  // only the bottom nybble is used
            // IF_NZ goto HasPokerus;
            if(hl->status & 0x0f) {
            // HasPokerus:
                // SCF;
                // RET;
                return true;
            }
        //  Next PartyMon
            // ADD_HL_DE;
            // DEC_B;
            // IF_NZ goto Check;
        } while(hl++, --b != 0);
    }

// NoPokerus:
    // AND_A_A;
    // RET;
    return false;
}
