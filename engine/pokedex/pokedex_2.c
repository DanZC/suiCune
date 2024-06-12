#include "../../constants.h"
#include "pokedex_2.h"
#include "../../home/text.h"
#include "../../home/copy.h"
#include "../../home/names.h"
#include "../../home/pokemon.h"
#include "../../home/print_text.h"
#include "../../home/pokedex_flags.h"
#include "../../data/pokemon/dex_entries.h"

void AnimateDexSearchSlowpoke(void){
    LD_HL(mAnimateDexSearchSlowpoke_FrameIDs);
    LD_B(25);

loop:
    LD_A_hli;

// Wrap around
    CP_A(0xfe);
    IF_NZ goto ok;
    LD_HL(mAnimateDexSearchSlowpoke_FrameIDs);
    LD_A_hli;

ok:

    LD_addr_A(wDexSearchSlowpokeFrame);
    LD_A_hli;
    LD_C_A;
    PUSH_BC;
    PUSH_HL;
    CALL(aDoDexSearchSlowpokeFrame);
    POP_HL;
    POP_BC;
    CALL(aDelayFrames);
    DEC_B;
    IF_NZ goto loop;
    XOR_A_A;
    LD_addr_A(wDexSearchSlowpokeFrame);
    CALL(aDoDexSearchSlowpokeFrame);
    LD_C(32);
    CALL(aDelayFrames);
    RET;


FrameIDs:
// frame ID, duration
    //db ['0', '7'];
    //db ['1', '7'];
    //db ['2', '7'];
    //db ['3', '7'];
    //db ['4', '7'];
    //db ['-2'];

    return DoDexSearchSlowpokeFrame();
}

void DoDexSearchSlowpokeFrame(void){
    LD_A_addr(wDexSearchSlowpokeFrame);
    LD_HL(mDoDexSearchSlowpokeFrame_SlowpokeSpriteData);
    LD_DE(wVirtualOAMSprite00);

loop:
    LD_A_hli;
    CP_A(-1);
    RET_Z ;
    LD_de_A;  // y
    INC_DE;
    LD_A_hli;
    LD_de_A;  // x
    INC_DE;
    LD_A_addr(wDexSearchSlowpokeFrame);
    LD_B_A;
    ADD_A_A;
    ADD_A_B;
    ADD_A_hl;
    INC_HL;
    LD_de_A;  // tile id
    INC_DE;
    LD_A_hli;
    LD_de_A;  // attributes
    INC_DE;
    goto loop;


// SlowpokeSpriteData:
    //dbsprite ['9', '11', '0', '0', '0x00', '0']
    //dbsprite ['10', '11', '0', '0', '0x01', '0']
    //dbsprite ['11', '11', '0', '0', '0x02', '0']
    //dbsprite ['9', '12', '0', '0', '0x10', '0']
    //dbsprite ['10', '12', '0', '0', '0x11', '0']
    //dbsprite ['11', '12', '0', '0', '0x12', '0']
    //dbsprite ['9', '13', '0', '0', '0x20', '0']
    //dbsprite ['10', '13', '0', '0', '0x21', '0']
    //dbsprite ['11', '13', '0', '0', '0x22', '0']
    //db ['-1'];
}

void DisplayDexEntry(species_t a){
    // CALL(aGetPokemonName);
    // hlcoord(9, 3, wTilemap);
    // CALL(aPlaceString);  // mon species
    PlaceStringSimple(GetPokemonName_Conv2(a), coord(9, 3, wram->wTilemap));
    // LD_A_addr(wTempSpecies);
    // LD_B_A;
    // CALL(aGetDexEntryPointer);
    const struct DexEntry* entry = GetDexEntryPointer(a);
    // LD_A_B;
    // PUSH_AF;
    // hlcoord(9, 5, wTilemap);
    struct TextPrintState st = {.de = U82C(entry->category), .hl = coord(9, 5, wram->wTilemap)};
    // CALL(aPlaceFarString);  // dex species
    PlaceString_Conv(&st, st.hl);
    // LD_H_B;
    // LD_L_C;
    st.hl = st.bc;
    // PUSH_DE;
//  Print dex number
    // hlcoord(2, 8, wTilemap);
    // LD_A(0x5c);  // No
    // LD_hli_A;
    *coord(2, 8, wram->wTilemap) = 0x5c;
    // LD_A(0x5d);  // .
    // LD_hli_A;
    *coord(3, 8, wram->wTilemap) = 0x5d;
    // LD_DE(wTempSpecies);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(4, 8, wram->wTilemap), &wram->wTempSpecies, PRINTNUM_LEADINGZEROS | 1, 3);
//  Check to see if we caught it.  Get out of here if we haven't.
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // CALL(aCheckCaughtMon);
    // POP_HL;
    // POP_BC;
    // RET_Z ;
    if(!CheckCaughtMon_Conv(wram->wTempSpecies - 1))
        return;
//  Get the height of the Pokemon.
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    // INC_HL;
    // LD_A_B;
    // PUSH_AF;
    // PUSH_HL;
    // CALL(aGetFarWord);
    // LD_D_L;
    // LD_E_H;
    // POP_HL;
    // INC_HL;
    // INC_HL;
    // LD_A_D;
    // OR_A_E;
    uint16_t height = ReverseEndian16(entry->height);
    // IF_Z goto skip_height;
    if(height != 0) {
        // PUSH_HL;
        // PUSH_DE;
    //  Print the height, with two of the four digits in front of the decimal point
        // LD_HL_SP(0);
        // LD_D_H;
        // LD_E_L;
        // hlcoord(12, 7, wTilemap);
        // LD_BC((2 << 8) | (2 << 4) | 4);
        // CALL(aPrintNum);
        PrintNum_Conv2(coord(12, 7, wram->wTilemap), &height, 2, (2 << 4) | 4);
    //  Replace the decimal point with a ft symbol
        // hlcoord(14, 7, wTilemap);
        // LD_hl(0x5e);
        *coord(14, 7, wram->wTilemap) = 0x5e;
        // POP_AF;
        // POP_HL;
    }

// skip_height:
    // POP_AF;
    // PUSH_AF;
    // INC_HL;
    // PUSH_HL;
    // DEC_HL;
    // CALL(aGetFarWord);
    // LD_D_L;
    // LD_E_H;
    uint16_t weight = ReverseEndian16(entry->weight);
    // LD_A_E;
    // OR_A_D;
    // IF_Z goto skip_weight;
    if(weight != 0) {
        // PUSH_DE;
    //  Print the weight, with four of the five digits in front of the decimal point
        // LD_HL_SP(0);
        // LD_D_H;
        // LD_E_L;
        // hlcoord(11, 9, wTilemap);
        // LD_BC((2 << 8) | (4 << 4) | 5);
        // CALL(aPrintNum);
        PrintNum_Conv2(coord(11, 9, wram->wTilemap), &weight, 2, (4 << 4) | 5);
        // POP_DE;
    }

// skip_weight:
//  Page 1
    // LD_BC((5 << 8) | SCREEN_WIDTH - 2);
    // hlcoord(2, 11, wTilemap);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(2, 11, wram->wTilemap), SCREEN_WIDTH - 2, 5);
    // hlcoord(1, 10, wTilemap);
    // LD_BC(SCREEN_WIDTH - 1);
    // LD_A(0x61);  // horizontal divider
    // CALL(aByteFill);
    ByteFill_Conv2(coord(1, 10, wram->wTilemap), SCREEN_WIDTH - 1, 0x61);
// page number
    // hlcoord(1, 9, wTilemap);
    // LD_hl(0x55);
    *coord(1, 9, wram->wTilemap) = 0x55;
    // INC_HL;
    // LD_hl(0x55);
    *coord(2, 9, wram->wTilemap) = 0x55;
    // hlcoord(1, 10, wTilemap);
    // LD_hl(0x56);  // P.
    *coord(1, 10, wram->wTilemap) = 0x56;
    // INC_HL;
    // LD_hl(0x57);  // 1
    *coord(2, 10, wram->wTilemap) = 0x57;
    // POP_DE;
    // INC_DE;
    // POP_AF;
    // hlcoord(2, 11, wTilemap);
    // PUSH_AF;
    // CALL(aPlaceFarString);
    st.de = U82C(entry->description);
    st.hl = coord(2, 11, wram->wTilemap);
    PlaceString_Conv(&st, st.hl);
    // POP_BC;
    // LD_A_addr(wPokedexStatus);
    // OR_A_A;  // check for page 2
    // RET_Z ;
    if(wram->wPokedexStatus == 0)
        return;

//  Page 2
    // PUSH_BC;
    // PUSH_DE;
    // LD_BC((5 << 8) | SCREEN_WIDTH - 2);
    // hlcoord(2, 11, wTilemap);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(2, 11, wram->wTilemap), SCREEN_WIDTH - 2, 5);
    // hlcoord(1, 10, wTilemap);
    // LD_BC(SCREEN_WIDTH - 1);
    // LD_A(0x61);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(1, 10, wram->wTilemap), SCREEN_WIDTH - 1, 0x61);
// page number
    // hlcoord(1, 9, wTilemap);
    // LD_hl(0x55);
    *coord(1, 9, wram->wTilemap) = 0x55;
    // INC_HL;
    // LD_hl(0x55);
    *coord(2, 9, wram->wTilemap) = 0x55;
    // hlcoord(1, 10, wTilemap);
    // LD_hl(0x56);  // P.
    *coord(1, 10, wram->wTilemap) = 0x56;
    // INC_HL;
    // LD_hl(0x58);  // 2
    *coord(2, 10, wram->wTilemap) = 0x58;
    // POP_DE;
    // INC_DE;
    // POP_AF;
    st.de++;
    // hlcoord(2, 11, wTilemap);
    st.hl = coord(2, 11, wram->wTilemap);
    // CALL(aPlaceFarString);
    PlaceString_Conv(&st, st.hl);
    // RET;
}

void POKeString(void){
//  //  unreferenced
    //db ['"#@"'];
}

const struct DexEntry* GetDexEntryPointer(uint8_t b){
//  return dex entry pointer b:de
    // PUSH_HL;
    // LD_HL(mPokedexDataPointerTable);
    // LD_A_B;
    // DEC_A;
    // LD_D(0);
    // LD_E_A;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // PUSH_DE;
    // RLCA;
    // RLCA;
    // maskbits(NUM_DEX_ENTRY_BANKS, 0);
    // LD_HL(mGetDexEntryPointer_PokedexEntryBanks);
    // LD_D(0);
    // LD_E_A;
    // ADD_HL_DE;
    // LD_B_hl;
    // POP_DE;
    // POP_HL;
    // RET;


// PokedexEntryBanks:
    //db ['BANK("Pokedex Entries 001-064")'];
    //db ['BANK("Pokedex Entries 065-128")'];
    //db ['BANK("Pokedex Entries 129-192")'];
    //db ['BANK("Pokedex Entries 193-251")'];

    return PokedexDataPointerTable[b - 1];
}

void GetDexEntryPagePointer(void){
    CALL(aGetDexEntryPointer);
    PUSH_HL;
    LD_H_D;
    LD_L_E;
//  skip species name

loop1:
    LD_A_B;
    CALL(aGetFarByte);
    INC_HL;
    CP_A(0x50);
    IF_NZ goto loop1;
//  skip height and weight
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }
//  if c != 1: skip entry
    DEC_C;
    IF_Z goto done;
//  skip entry

loop2:
    LD_A_B;
    CALL(aGetFarByte);
    INC_HL;
    CP_A(0x50);
    IF_NZ goto loop2;


done:
    LD_D_H;
    LD_E_L;
    POP_HL;
    RET;

// INCLUDE "data/pokemon/dex_entry_pointers.asm"

}
