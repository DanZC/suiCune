#include "../../constants.h"
#include "search.h"
#include "../../home/sram.h"
#include "../../util/serialize.h"

//  Check if the player owns all three legendary beasts.
//  They must exist in either party or PC, and have the player's OT and ID.
//  Return the result in wScriptVar.
void BeastsCheck(void){
    // LD_A(RAIKOU);
    // LD_addr_A(wScriptVar);
    // CALL(aCheckOwnMonAnywhere);
    // IF_NC goto notexist;

    // LD_A(ENTEI);
    // LD_addr_A(wScriptVar);
    // CALL(aCheckOwnMonAnywhere);
    // IF_NC goto notexist;

    // LD_A(SUICUNE);
    // LD_addr_A(wScriptVar);
    // CALL(aCheckOwnMonAnywhere);
    // IF_NC goto notexist;

    if(CheckOwnMonAnywhere(RAIKOU) && CheckOwnMonAnywhere(ENTEI) && CheckOwnMonAnywhere(SUICUNE)) {
    // they exist
        // LD_A(1);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 1;
        // RET;
        return;
    }

// notexist:
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // RET;
}

//  Check if the player owns any Pokémon of the species in wScriptVar.
//  Return the result in wScriptVar.
void MonCheck(void){
    // CALL(aCheckOwnMonAnywhere);
    // IF_C goto exists;
    if(CheckOwnMonAnywhere((species_t)wram->wScriptVar)) {
    // exists:
        // LD_A(1);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 1;
        // RET;
        return;
    }

// doesn't exist
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // RET;
}

//  Check if the player owns any monsters of the species in wScriptVar.
//  It must exist in either party or PC, and have the player's OT and ID.
bool CheckOwnMonAnywhere(species_t species){
// If there are no monsters in the party,
// the player must not own any yet.
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // RET_Z ;
    if(gPokemon.partyCount == 0)
        return false;

    // LD_D_A;
    uint8_t d = gPokemon.partyCount;
    // LD_E(0);
    // LD_HL(wPartyMon1Species);
    const struct PartyMon* hl = gPokemon.partyMon;
    // LD_BC(wPartyMonOTs);
    const uint8_t (*ots)[NAME_LENGTH] = gPokemon.partyMonOT;

// Run CheckOwnMon on each Pokémon in the party.

    do {
    // partymon:
        // CALL(aCheckOwnMon);
        // RET_C ;  // found!
        if(CheckOwnMon(&hl->mon, *ots, species))
            return true;

        // PUSH_BC;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_BC;
        hl++;
        // POP_BC;
        // CALL(aUpdateOTPointer);
        ots++;
        // DEC_D;
        // IF_NZ goto partymon;
    } while(--d != 0);

// Run CheckOwnMon on each Pokémon in the PC.
    // LD_A(BANK(sBoxCount));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxCount));
    struct Box box;
    Deserialize_Box(&box, GBToRAMAddr(sBox));
    // LD_A_addr(sBoxCount);
    // AND_A_A;
    // IF_Z goto boxes;

    d = box.count;
    if(d != 0) {
        // LD_D_A;
        // LD_HL(sBoxMon1Species);
        struct BoxMon* bmon = box.mons;
        // LD_BC(sBoxMonOTs);
        uint8_t (*ots)[NAME_LENGTH] = box.monOT;

        do {
        // openboxmon:
            // CALL(aCheckOwnMon);
            // IF_NC goto loop;

            if(CheckOwnMon(bmon, *ots, species)) {
            // found!
                // CALL(aCloseSRAM);
                CloseSRAM();
                // RET;
                return true;
            }

        // loop:
            // PUSH_BC;
            // LD_BC(BOXMON_STRUCT_LENGTH);
            // ADD_HL_BC;
            bmon++;
            // POP_BC;
            // CALL(aUpdateOTPointer);
            ots++;
            // DEC_D;
            // IF_NZ goto openboxmon;
        } while(--d != 0);
    }
// Run CheckOwnMon on each monster in the other 13 PC boxes.

// boxes:
    // CALL(aCloseSRAM);
    CloseSRAM();

    // LD_C(0);
    uint8_t c = 0;

    do {
    // box:
    // Don't search the current box again.
        // LD_A_addr(wCurBox);
        // AND_A(0xf);
        // CP_A_C;
        // IF_Z goto loopbox;
        if((gPlayer.curBox & 0xf) == c)
            continue;

    // Load the box.
        // LD_HL(mSearchBoxAddressTable);
        // LD_B(0);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // ADD_HL_BC;
        uint32_t boxAddr = SearchBoxAddressTable[c];
        // LD_A_hli;
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(boxAddr));

        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        uint8_t* boxPtr = GBToRAMAddr(boxAddr & 0xffff);
        Deserialize_Box(&box, boxPtr);

    // Number of monsters in the box
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto loopbox;
        if(box.count == 0)
            continue;

        // PUSH_BC;

        // PUSH_HL;
        // LD_DE(sBoxMons - sBoxCount);
        // ADD_HL_DE;
        // LD_D_H;
        // LD_E_L;
        const struct BoxMon* bmon = box.mons;
        // POP_HL;
        // PUSH_DE;
        // LD_DE(sBoxMonOTs - sBoxCount);
        const uint8_t* ots = box.monOT[0];
        // ADD_HL_DE;
        // LD_B_H;
        // LD_C_L;
        // POP_HL;

        // LD_D_A;
        d = c;

        do {
        // boxmon:
            // CALL(aCheckOwnMon);
            // IF_NC goto loopboxmon;

            if(CheckOwnMon(bmon, ots, species)) {
            // found!
                // POP_BC;
                // CALL(aCloseSRAM);
                CloseSRAM();
                // RET;
                return true;
            }

        // loopboxmon:
            // PUSH_BC;
            // LD_BC(BOXMON_STRUCT_LENGTH);
            // ADD_HL_BC;
            hl++;
            // POP_BC;
            // CALL(aUpdateOTPointer);
            ots += NAME_LENGTH;
            // DEC_D;
            // IF_NZ goto boxmon;
        } while(--d != 0);
        // POP_BC;

    // loopbox:
        // INC_C;
        // LD_A_C;
        // CP_A(NUM_BOXES);
        // IF_C goto box;
    } while(++c < NUM_BOXES);

// not found
    // CALL(aCloseSRAM);
    CloseSRAM();
    // AND_A_A;
    // RET;
    return false;
}

//  Check if a Pokémon belongs to the player and is of a specific species.
//
//  inputs:
//  hl, pointer to PartyMonNSpecies
//  bc, pointer to PartyMonNOT
//  wScriptVar should contain the species we're looking for
//
//  outputs:
//  sets carry if monster matches species, ID, and OT name.
bool CheckOwnMon(const struct BoxMon* hl, const uint8_t* ot, species_t species){
    // PUSH_BC;
    // PUSH_HL;
    // PUSH_DE;
    // LD_D_B;
    // LD_E_C;

//  check species
    // LD_A_addr(wScriptVar);  // species we're looking for
    // LD_B_hl;  // species we have
    // CP_A_B;
    // IF_NZ goto notfound;  // species doesn't match
    if(hl->species != species)
        return false;

//  check ID number
    // LD_BC(MON_ID);
    // ADD_HL_BC;  // now hl points to ID number
    // LD_A_addr(wPlayerID);
    // CP_A_hl;
    // IF_NZ goto notfound;  // ID doesn't match
    // INC_HL;
    // LD_A_addr(wPlayerID + 1);
    // CP_A_hl;
    // IF_NZ goto notfound;  // ID doesn't match
    if(hl->id != gPlayer.playerID)
        return false;

//  check OT
//  This only checks five characters, which is fine for the Japanese version,
//  but in the English version the player name is 7 characters, so this is wrong.

    // LD_HL(wPlayerName);
    const uint8_t* plyr = gPlayer.playerName;

#if BUGFIX_OWN_MON_OT_CHECK_NAME_LENGTH
    for(int rept = 0; rept < PLAYER_NAME_LENGTH - 1; rept++)
#else
    for(int rept = 0; rept < NAME_LENGTH_JAPANESE - 1; rept++)  //  should be PLAYER_NAME_LENGTH - 1
#endif
    {
        // LD_A_de;
        // CP_A_hl;
        // IF_NZ goto notfound;
        if(plyr[rept] != ot[rept])
            return false;
        // CP_A(0x50);
        // IF_Z goto found;  // reached end of string
        if(plyr[rept] == 0x50)
            return true;
        // INC_HL;
        // INC_DE;
    }

    // LD_A_de;
    // CP_A_hl;
    // IF_Z goto found;

// notfound:
    // POP_DE;
    // POP_HL;
    // POP_BC;
    // AND_A_A;
    // RET;
    return false;

// found:
    // POP_DE;
    // POP_HL;
    // POP_BC;
    // SCF;
    // RET;
}

const uint32_t SearchBoxAddressTable[] = {
    //table_width ['3', 'SearchBoxAddressTable']
    asBox1,
    asBox2,
    asBox3,
    asBox4,
    asBox5,
    asBox6,
    asBox7,
    asBox8,
    asBox9,
    asBox10,
    asBox11,
    asBox12,
    asBox13,
    asBox14,
};
static_assert(lengthof(SearchBoxAddressTable) == NUM_BOXES, "");

void UpdateOTPointer(void){
    // PUSH_HL;
    // LD_HL(NAME_LENGTH);
    // ADD_HL_BC;
    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // RET;
}
