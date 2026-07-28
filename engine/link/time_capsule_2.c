#if FEATURE_TIME_CAPSULE
#include "../../constants.h"
#include "time_capsule_2.h"
#include "../../data/pokemon/gen1_order.h"


//  Takes the Gen 2 Pokemon number stored in wTempSpecies,
//  finds it in the Pokered_MonIndices table,
//  and returns its index in wTempSpecies.
species_t ConvertMon_2to1(species_t a){
    // PUSH_BC;
    // PUSH_HL;
    // LD_A_addr(wTempSpecies);
    // LD_B_A;
    // LD_C(0);
    // LD_HL(mPokered_MonIndices);
    for(species_t i = 0; i < NUM_POKEMON; ++i) {
    // loop:
        // INC_C;
        // LD_A_hli;
        // CP_A_B;
        // IF_NZ goto loop;
        if(Pokered_MonIndices[i] == a) {
            // LD_A_C;
            // LD_addr_A(wTempSpecies);
            // POP_HL;
            // POP_BC;
            // RET;
            return i + 1;
        }
    }
    return 0;
}

//  Takes the Gen 1 Pokemon number stored in wTempSpecies
//  and returns the corresponding value from Pokered_MonIndices in wTempSpecies.
species_t ConvertMon_1to2(species_t a){
    // PUSH_BC;
    // PUSH_HL;
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // LD_HL(mPokered_MonIndices);
    // LD_B(0);
    // LD_C_A;
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wTempSpecies);
    // POP_HL;
    // POP_BC;
    // RET;
    return Pokered_MonIndices[a-1];
// INCLUDE "data/pokemon/gen1_order.asm"

}
#endif // FEATURE_TIME_CAPSULE
