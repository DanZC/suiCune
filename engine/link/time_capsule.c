#include "../../constants.h"
#include "time_capsule.h"
#include "../../home/text.h"
#include "../../home/names.h"
#include "../../home/pokemon.h"

//  These functions seem to be related to backwards compatibility

void ValidateOTTrademon(void){
    LD_A_addr(wCurOTTradePartyMon);
    LD_HL(wOTPartyMon1Species);
    CALL(aGetPartyLocation);
    PUSH_HL;
    LD_A_addr(wCurOTTradePartyMon);
    INC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartyCount);
    ADD_HL_BC;
    LD_A_hl;
    POP_HL;
    CP_A(EGG);
    IF_Z goto matching_or_egg;
    CP_A_hl;
    IF_NZ goto abnormal;


matching_or_egg:
    LD_B_H;
    LD_C_L;
    LD_HL(MON_LEVEL);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(MAX_LEVEL + 1);
    IF_NC goto abnormal;
    LD_A_addr(wLinkMode);
    CP_A(LINK_TIMECAPSULE);
    IF_NZ goto normal;
    LD_HL(wOTPartySpecies);
    LD_A_addr(wCurOTTradePartyMon);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;

// Magnemite and Magneton's types changed
// from Electric to Electric/Steel.
    CP_A(MAGNEMITE);
    IF_Z goto normal;
    CP_A(MAGNETON);
    IF_Z goto normal;

    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_HL(wLinkOTPartyMonTypes);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_addr(wBaseType1);
    CP_A_hl;
    IF_NZ goto abnormal;
    INC_HL;
    LD_A_addr(wBaseType2);
    CP_A_hl;
    IF_NZ goto abnormal;


normal:
    AND_A_A;
    RET;


abnormal:
    SCF;
    RET;

}

// Returns true (nc) if the trade mon is valid.
// Returns false (c) if the trade mon is abnormal.
bool ValidateOTTrademon_Conv(uint8_t mon){
    // LD_A_addr(wCurOTTradePartyMon);
    // LD_HL(wOTPartyMon1Species);
    // CALL(aGetPartyLocation);
    struct PartyMon* pmon = wram->wOTPartyMon + mon;
    // PUSH_HL;
    // LD_A_addr(wCurOTTradePartyMon);
    // INC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wOTPartyCount);
    // ADD_HL_BC;
    // LD_A_hl;
    species_t a = wram->wOTPartySpecies[mon];
    // POP_HL;
    // CP_A(EGG);
    // IF_Z goto matching_or_egg;
    // CP_A_hl;
    // IF_NZ goto abnormal;
    if(a != EGG && a != pmon->mon.species)
        return false;

// matching_or_egg:
    // LD_B_H;
    // LD_C_L;
    // LD_HL(MON_LEVEL);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(MAX_LEVEL + 1);
    // IF_NC goto abnormal;
    if(pmon->mon.level >= MAX_LEVEL + 1)
        return false;
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_TIMECAPSULE);
    // IF_NZ goto normal;
// If we're in the time capsule we require additional checks.
    if(wram->wLinkMode == LINK_TIMECAPSULE)
        return true;
    // LD_HL(wOTPartySpecies);
    // LD_A_addr(wCurOTTradePartyMon);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;

// Magnemite and Magneton's types changed
// from Electric to Electric/Steel.
    // CP_A(MAGNEMITE);
    // IF_Z goto normal;
    // CP_A(MAGNETON);
    // IF_Z goto normal;
    if(a == MAGNEMITE || a == MAGNETON)
        return true;

    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = a;
    // CALL(aGetBaseData);
    GetBaseData_Conv();
    // LD_HL(wLinkOTPartyMonTypes);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_addr(wBaseType1);
    // CP_A_hl;
    // IF_NZ goto abnormal;
    if(wram->wBaseType1 != LOW(wram->wLinkOTPartyMonType[mon]))
        return false;
    // INC_HL;
    // LD_A_addr(wBaseType2);
    // CP_A_hl;
    // IF_NZ goto abnormal;
    if(wram->wBaseType2 != HIGH(wram->wLinkOTPartyMonType[mon]))
        return false;


// normal:
    // AND_A_A;
    // RET;
    return true;

// abnormal:
    // SCF;
    // RET;
}

void CheckAnyOtherAliveMonsForTrade(void){
    LD_A_addr(wCurTradePartyMon);
    LD_D_A;
    LD_A_addr(wPartyCount);
    LD_B_A;
    LD_C(0);

loop:
    LD_A_C;
    CP_A_D;
    IF_Z goto next;
    PUSH_BC;
    LD_A_C;
    LD_HL(wPartyMon1HP);
    CALL(aGetPartyLocation);
    POP_BC;
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto done;


next:
    INC_C;
    DEC_B;
    IF_NZ goto loop;
    LD_A_addr(wCurOTTradePartyMon);
    LD_HL(wOTPartyMon1HP);
    CALL(aGetPartyLocation);
    LD_A_hli;
    OR_A_hl;
    IF_NZ goto done;
    SCF;
    RET;


done:
    AND_A_A;
    RET;

}

// Returns true (nc) if any other alive mons are available
// for trade.
// Returns false (c) otherwise.
bool CheckAnyOtherAliveMonsForTrade_Conv(uint8_t mon){
    // LD_A_addr(wCurTradePartyMon);
    // LD_D_A;
    // LD_A_addr(wPartyCount);
    // LD_B_A;
    // LD_C(0);

    for(uint32_t c = 0; c < wram->wPartyCount; ++c) {
    // loop:
        // LD_A_C;
        // CP_A_D;
        // IF_Z goto next;
        if(c == mon)
            continue;
        // PUSH_BC;
        // LD_A_C;
        // LD_HL(wPartyMon1HP);
        // CALL(aGetPartyLocation);
        struct PartyMon* hl = wram->wPartyMon + c;
        // POP_BC;
        // LD_A_hli;
        // OR_A_hl;
        // IF_NZ goto done;
        if(hl->HP != 0)
            return true;

    // next:
        // INC_C;
        // DEC_B;
        // IF_NZ goto loop;
    }
    // LD_A_addr(wCurOTTradePartyMon);
    // LD_HL(wOTPartyMon1HP);
    // CALL(aGetPartyLocation);
    struct PartyMon* hl = wram->wOTPartyMon + mon;
    // LD_A_hli;
    // OR_A_hl;
    // IF_NZ goto done;
    if(hl->HP != 0)
        return true;
    // SCF;
    // RET;
    return false;

// done:
    // AND_A_A;
    // RET;
}

static void PlaceTradePartnerNamesAndParty_PlaceSpeciesNames(tile_t* hl, species_t* de) {
    // LD_C(0);
    uint8_t c = 0;

    while(de[c] != 0xff) {
    // loop:
        // LD_A_de;
        // CP_A(-1);
        // RET_Z ;
        // LD_addr_A(wNamedObjectIndex);
        // PUSH_BC;
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_HL;
        // LD_A_C;
        // LDH_addr_A(hProduct);
        // CALL(aGetPokemonName);
        // POP_HL;
        // CALL(aPlaceString);
        PlaceStringSimple(GetPokemonName_Conv2(de[c]), hl);
        // POP_DE;
        // INC_DE;
        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // INC_C;
        c++;
        // goto loop;
    }
}

void PlaceTradePartnerNamesAndParty(void){
    // hlcoord(4, 0, wTilemap);
    // LD_DE(wPlayerName);
    // CALL(aPlaceString);
    struct TextPrintState st = {.de = wram->wPlayerName, .hl = coord(4, 0, wram->wTilemap)};
    PlaceString_Conv(&st, st.hl);
    // LD_A(0x14);
    // LD_bc_A;
    *st.bc = 0x14;
    // hlcoord(4, 8, wTilemap);
    st.hl = coord(4, 8, wram->wTilemap);
    // LD_DE(wOTPlayerName);
    st.de = wram->wOTPlayerName;
    // CALL(aPlaceString);
    PlaceString_Conv(&st, st.hl);
    // LD_A(0x14);
    // LD_bc_A;
    *st.bc = 0x14;
    // hlcoord(7, 1, wTilemap);
    // LD_DE(wPartySpecies);
    // CALL(aPlaceTradePartnerNamesAndParty_PlaceSpeciesNames);
    PlaceTradePartnerNamesAndParty_PlaceSpeciesNames(coord(7, 1, wram->wTilemap), wram->wPartySpecies);
    // hlcoord(7, 9, wTilemap);
    // LD_DE(wOTPartySpecies);
    PlaceTradePartnerNamesAndParty_PlaceSpeciesNames(coord(7, 9, wram->wTilemap), wram->wOTPartySpecies);

// INCLUDE "data/pokemon/gen1_base_special.asm"

}
