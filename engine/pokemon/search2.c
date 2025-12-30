#include "../../constants.h"
#include "search2.h"

uint8_t v_FindPartyMonAboveLevel(uint8_t level){
    // LD_HL(wPartyMon1Level);
    // CALL(aFindAboveLevel);
    // RET;
    return FindAboveLevel(gPokemon.partyMon, level);
}

uint8_t v_FindPartyMonAtLeastThatHappy(uint8_t happiness){
    // LD_HL(wPartyMon1Happiness);
    // CALL(aFindAtLeastThatHappy);
    // RET;
    return FindAtLeastThatHappy(gPokemon.partyMon, happiness);
}

u8_flag_s v_FindPartyMonThatSpecies(species_t b){
    // LD_HL(wPartyMon1Species);
    // JP(mFindThatSpecies);
    return FindThatSpecies(b);
}

bool v_FindPartyMonThatSpeciesYourTrainerID(species_t b){
    // LD_HL(wPartyMon1Species);
    // CALL(aFindThatSpecies);
    u8_flag_s res = FindThatSpecies(b);
    // RET_Z ;
    if(!res.flag)
        return false;
    // LD_A_C;
    // LD_HL(wPartyMon1ID);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    const struct PartyMon* hl = gPokemon.partyMon + res.a;
    // LD_A_addr(wPlayerID);
    // CP_A_hl;
    // IF_NZ goto nope;
    // INC_HL;
    // LD_A_addr(wPlayerID + 1);
    // CP_A_hl;
    // IF_NZ goto nope;
    if(hl->mon.id == gPlayer.playerID) {
        // LD_A(0x1);
        // AND_A_A;
        // RET;
        return true;
    }

// nope:
    // XOR_A_A;
    // RET;
    return false;
}

//  Sets the bits for the Pokemon that have a happiness greater than or equal to b.
//  The lowest bits are used.  Sets z if no Pokemon in your party is at least that happy.
uint8_t FindAtLeastThatHappy(struct PartyMon* bc, uint8_t happiness){
    // LD_C(0x0);
    uint8_t c = 0x0;
    // LD_A_addr(wPartyCount);
    // LD_D_A;

    for(uint32_t i = gPokemon.partyCount; i > 0; --i) {
    // loop:
        // LD_A_D;
        // DEC_A;
        // PUSH_HL;
        // PUSH_BC;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // POP_BC;
        // LD_A_B;
        // CP_A_hl;
        // POP_HL;
        // IF_Z goto greater_equal;
        // IF_NC goto lower;
        if(bc[i-1].mon.happiness >= happiness) {
        // greater_equal:
            // LD_A_C;
            // OR_A(0x1);
            // LD_C_A;
            c |= 0x1;
        }

    // lower:
        // SLA_C;
        c <<= 1;
        // DEC_D;
        // IF_NZ goto loop;
    }
    // CALL(aRetroactivelyIgnoreEggs);
    // LD_A_C;
    // AND_A_A;
    // RET;
    return RetroactivelyIgnoreEggs(c);
}

uint8_t FindAboveLevel(struct PartyMon* bc, uint8_t level){
    // LD_C(0x0);
    uint8_t c = 0x0;
    // LD_A_addr(wPartyCount);
    // LD_D_A;

    for(uint32_t i = gPokemon.partyCount; i > 0; --i) {
    // loop:
        // LD_A_D;
        // DEC_A;
        // PUSH_HL;
        // PUSH_BC;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // POP_BC;
        // LD_A_B;
        // CP_A_hl;
        // POP_HL;
        // IF_C goto greater;
        if(bc[i-1].mon.level >= level) {
            // LD_A_C;
            // OR_A(0x1);
            // LD_C_A;
            c |= 0x1;
        }

    // greater:
        // SLA_C;
        c <<= 1;
        // DEC_D;
        // IF_NZ goto loop;
    }
    // CALL(aRetroactivelyIgnoreEggs);
    c = RetroactivelyIgnoreEggs(c);
    // LD_A_C;
    // AND_A_A;
    // RET;
    return c;
}

//  Find species b in your party.
//  If you have no Pokemon, returns c = -1 and false (z).
//  If that species is in your party, returns its location in c, and true (nz).
//  Otherwise, returns false (z).
u8_flag_s FindThatSpecies(species_t b){
    // LD_C(-1);
    uint8_t c = (uint8_t)-1;
    // LD_HL(wPartySpecies);
    species_t* hl = gPokemon.partySpecies;
    species_t a;
    do {
    // loop:
        // LD_A_hli;
        a = *(hl++);
        // CP_A(-1);
        // RET_Z ;
        if(a == (uint8_t)-1)
            return u8_flag(c, false);
        // INC_C;
        c++;
        // CP_A_B;
        // IF_NZ goto loop;
    } while(a != b);
    // LD_A(0x1);
    // AND_A_A;
    return u8_flag(c, true);
    // RET;
}

uint8_t RetroactivelyIgnoreEggs(uint8_t c){
    // LD_E(0b11111110);
    uint8_t e = 0b11111110;
    // LD_HL(wPartySpecies);
    for(uint32_t i = 0; i < lengthof(gPokemon.partySpecies) && gPokemon.partySpecies[i] != 0xff; ++i) {
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // RET_Z ;
        // CP_A(EGG);
        // IF_NZ goto skip_notegg;
        if(gPokemon.partySpecies[i] == EGG) {
            // LD_A_C;
            // AND_A_E;
            // LD_C_A;
            c &= e;
        }

    // skip_notegg:
        // RLC_E;
        e = RotateLeftC8(e);
        // goto loop;
    }
    return c;
}
