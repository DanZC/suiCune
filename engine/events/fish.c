#include "../../constants.h"
#include "fish.h"
#include "../../home/random.h"
#include "../../data/wild/fish.h"

void Fish(void){
    struct SpeciesLevel res = Fish_Conv(REG_E, REG_D);
    REG_E = res.level;
    REG_D = res.species;
    return;
//  Using a fishing rod.
//  Fish for monsters with rod e in encounter group d.
//  Return monster d at level e.

    PUSH_AF;
    PUSH_BC;
    PUSH_HL;

    LD_B_E;
    CALL(aGetFishGroupIndex);

    LD_HL(mFishGroups);
    for(int rept = 0; rept < FISHGROUP_DATA_LENGTH; rept++){
    ADD_HL_DE;
    }
    CALL(aFish_Fish);

    POP_HL;
    POP_BC;
    POP_AF;
    RET;


Fish:
//  Fish for monsters with rod b from encounter data in FishGroup at hl.
//  Return monster d at level e.

    CALL(aRandom);
    CP_A_hl;
    IF_NC goto no_bite;

// Get encounter data by rod:
// 0: Old
// 1: Good
// 2: Super
    INC_HL;
    LD_E_B;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

// Compare the encounter chance to select a Pokemon.
    CALL(aRandom);

loop:
    CP_A_hl;
    IF_Z goto ok;
    IF_C goto ok;
    INC_HL;
    INC_HL;
    INC_HL;
    goto loop;

ok:
    INC_HL;

// Species 0 reads from a time-based encounter table.
    LD_A_hli;
    LD_D_A;
    AND_A_A;
    CALL_Z (aFish_TimeEncounter);

    LD_E_hl;
    RET;


no_bite:
    LD_DE(0);
    RET;


TimeEncounter:
// The level byte is repurposed as the index for the new table.
    LD_E_hl;
    LD_D(0);
    LD_HL(mTimeFishGroups);
    for(int rept = 0; rept < 4; rept++){
    ADD_HL_DE;
    }

    LD_A_addr(wTimeOfDay);
    maskbits(NUM_DAYTIMES, 0);
    CP_A(NITE_F);
    IF_C goto time_species;
    INC_HL;
    INC_HL;


time_species:
    LD_D_hl;
    INC_HL;
    RET;

}

enum {
    ROD_OLD,
    ROD_GOOD,
    ROD_SUPER,
};

// The level byte is repurposed as the index for the new table.
static struct SpeciesLevel Fish_TimeEncounter(uint8_t index) {
    // LD_E_hl;
    // LD_D(0);
    // LD_HL(mTimeFishGroups);
    // for(int rept = 0; rept < 4; rept++){
    // ADD_HL_DE;
    // }
    const struct TimeFishGroup group = TimeFishGroups[index];

    // LD_A_addr(wTimeOfDay);
    // maskbits(NUM_DAYTIMES, 0);
    // CP_A(NITE_F);
    // IF_C goto time_species;
    if((wram->wTimeOfDay & 3) >= NITE_F) {
        // INC_HL;
        // INC_HL;
        return (struct SpeciesLevel){group.nite_mon, group.nite_lvl};
    }

// time_species:
    // LD_D_hl;
    // INC_HL;
    // RET;
    return (struct SpeciesLevel){group.day_mon, group.day_lvl};
}

//  Fish for monsters with rod b from encounter data in FishGroup at hl.
//  Return monster d at level e.
static struct SpeciesLevel Fish_Fish(const struct FishGroup* hl, uint8_t rod) {
    // CALL(aRandom);
    // CP_A_hl;
    // IF_NC goto no_bite;
    if(Random_Conv() >= hl->chance)
        return (struct SpeciesLevel){0, 0};

// Get encounter data by rod:
// 0: Old
// 1: Good
// 2: Super
    // INC_HL;
    // LD_E_B;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct FishEncounter* enc;
    switch(rod) {
        default:
        case ROD_OLD:   enc = hl->old_rod;   break;
        case ROD_GOOD:  enc = hl->good_rod;  break;
        case ROD_SUPER: enc = hl->super_rod; break;
    }

// Compare the encounter chance to select a Pokemon.
    // CALL(aRandom);
    uint8_t a = Random_Conv();

    while(a > enc->chance) {
    // loop:
        // CP_A_hl;
        // IF_Z goto ok;
        // IF_C goto ok;
        // INC_HL;
        // INC_HL;
        // INC_HL;
        enc++;
        // goto loop;
    }

// ok:
    // INC_HL;

// Species 0 reads from a time-based encounter table.
    struct SpeciesLevel res;
    // LD_A_hli;
    // LD_D_A;
    res.species = enc->species;
    // AND_A_A;
    // CALL_Z (aFish_TimeEncounter);
    if(res.species == 0) {
        return Fish_TimeEncounter(enc->lvl);
    }

    // LD_E_hl;
    res.level = enc->lvl;
    // RET;
    return res;

// no_bite:
    // LD_DE(0);
    // RET;
}

//  Using a fishing rod.
//  Fish for monsters with rod e in encounter group d.
//  Return monster d at level e.
struct SpeciesLevel Fish_Conv(uint8_t e, uint8_t d){
    // PUSH_AF;
    // PUSH_BC;
    // PUSH_HL;

    // LD_B_E;
    // CALL(aGetFishGroupIndex);
    uint16_t idx = GetFishGroupIndex(d);

    // LD_HL(mFishGroups);
    // for(int rept = 0; rept < FISHGROUP_DATA_LENGTH; rept++){
    // ADD_HL_DE;
    // }
    const struct FishGroup* hl = FishGroups + idx;
    // CALL(aFish_Fish);

    // POP_HL;
    // POP_BC;
    // POP_AF;
    // RET;
    return Fish_Fish(hl, e);
}

uint16_t GetFishGroupIndex(uint8_t d){
//  Return the index of fishgroup d in de.

    // PUSH_HL;
    // LD_HL(wDailyFlags1);
    // BIT_hl(DAILYFLAGS1_FISH_SWARM_F);
    // POP_HL;
    // IF_Z goto done;
    if(bit_test(wram->wDailyFlags1, DAILYFLAGS1_FISH_SWARM_F)) {
        // LD_A_D;
        // CP_A(FISHGROUP_QWILFISH);
        // IF_Z goto qwilfish;
        if(d == FISHGROUP_QWILFISH) {
        // qwilfish:
            // LD_A_addr(wFishingSwarmFlag);
            // CP_A(FISHSWARM_QWILFISH);
            // IF_NZ goto done;
            if(wram->wFishingSwarmFlag == FISHSWARM_QWILFISH) {
                // LD_D(FISHGROUP_QWILFISH_SWARM);
                d = FISHGROUP_QWILFISH_SWARM;
            }
            // goto done;
        }
        // CP_A(FISHGROUP_REMORAID);
        // IF_Z goto remoraid;
        else if(d == FISHGROUP_REMORAID) {
        // remoraid:
            // LD_A_addr(wFishingSwarmFlag);
            // CP_A(FISHSWARM_REMORAID);
            // IF_NZ goto done;
            if(wram->wFishingSwarmFlag == FISHSWARM_REMORAID) {
                // LD_D(FISHGROUP_REMORAID_SWARM);
                d = FISHGROUP_REMORAID_SWARM;
            }
            // goto done;
        }
    }

// done:
    // DEC_D;
    // LD_E_D;
    // LD_D(0);
    // RET;

// INCLUDE "data/wild/fish.asm"
    return d - 1;
}
