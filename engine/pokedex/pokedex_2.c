#include "../../constants.h"
#include "pokedex_2.h"
#include "../../home/text.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/names.h"
#include "../../home/pokemon.h"
#include "../../home/print_text.h"
#include "../../home/pokedex_flags.h"
#include "../../data/pokemon/dex_entries.h"
#include "../../charmap.h"

void AnimateDexSearchSlowpoke(void){
    static const uint8_t FrameIDs[] = {
    // frame ID, duration
        0, 7,
        1, 7,
        2, 7,
        3, 7,
        4, 7,
        (uint8_t)-2,
    };
    // LD_HL(mAnimateDexSearchSlowpoke_FrameIDs);
    const uint8_t* hl = FrameIDs;
    // LD_B(25);
    uint8_t b = 25;

    do {
    // loop:
        // LD_A_hli;
        uint8_t a = *(hl++);

    // Wrap around
        // CP_A(0xfe);
        // IF_NZ goto ok;
        if(a == (uint8_t)-2){
            // LD_HL(mAnimateDexSearchSlowpoke_FrameIDs);
            hl = FrameIDs;
            // LD_A_hli;
            a = *(hl++);
        }
    // ok:
        // LD_addr_A(wDexSearchSlowpokeFrame);
        wram->wDexSearchSlowpokeFrame = a;
        // LD_A_hli;
        // LD_C_A;
        uint8_t c = *(hl++);
        // PUSH_BC;
        // PUSH_HL;
        // CALL(aDoDexSearchSlowpokeFrame);
        DoDexSearchSlowpokeFrame();
        // POP_HL;
        // POP_BC;
        // CALL(aDelayFrames);
        DelayFrames(c);
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // XOR_A_A;
    // LD_addr_A(wDexSearchSlowpokeFrame);
    wram->wDexSearchSlowpokeFrame = 0;
    // CALL(aDoDexSearchSlowpokeFrame);
    DoDexSearchSlowpokeFrame();
    // LD_C(32);
    // CALL(aDelayFrames);
    DelayFrames(32);
    // RET;
}

void DoDexSearchSlowpokeFrame(void){
    static const uint8_t SlowpokeSpriteData[] = {
        dbsprite( 9, 11, 0, 0, 0x00, 0),
        dbsprite(10, 11, 0, 0, 0x01, 0),
        dbsprite(11, 11, 0, 0, 0x02, 0),
        dbsprite( 9, 12, 0, 0, 0x10, 0),
        dbsprite(10, 12, 0, 0, 0x11, 0),
        dbsprite(11, 12, 0, 0, 0x12, 0),
        dbsprite( 9, 13, 0, 0, 0x20, 0),
        dbsprite(10, 13, 0, 0, 0x21, 0),
        dbsprite(11, 13, 0, 0, 0x22, 0),
        (uint8_t)-1,
    };
    // LD_A_addr(wDexSearchSlowpokeFrame);
    // LD_HL(mDoDexSearchSlowpokeFrame_SlowpokeSpriteData);
    const uint8_t* hl = SlowpokeSpriteData;
    // LD_DE(wVirtualOAMSprite00);
    struct SpriteOAM* de = wram->wVirtualOAMSprite;

    while(*hl != (uint8_t)-1){
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // RET_Z ;
        // LD_de_A;  // y
        // INC_DE;
        de->yCoord = *(hl++);
        // LD_A_hli;
        // LD_de_A;  // x
        // INC_DE;
        de->xCoord = *(hl++);
        // LD_A_addr(wDexSearchSlowpokeFrame);
        // LD_B_A;
        // ADD_A_A;
        // ADD_A_B;
        // ADD_A_hl;
        // INC_HL;
        // LD_de_A;  // tile id
        // INC_DE;
        de->tileID = (wram->wDexSearchSlowpokeFrame * 3) + *(hl++);
        // LD_A_hli;
        // LD_de_A;  // attributes
        // INC_DE;
        de->attributes = *(hl++);
        // goto loop;
        de++;
    }
}

void DisplayDexEntry(species_t a){
    // CALL(aGetPokemonName);
    // hlcoord(9, 3, wTilemap);
    // CALL(aPlaceString);  // mon species
    PlaceStringSimple(GetPokemonName(a), coord(9, 3, wram->wTilemap));
    // LD_A_addr(wTempSpecies);
    // LD_B_A;
    // CALL(aGetDexEntryPointer);
    const struct DexEntry* entry = GetDexEntryPointer(a);
    // LD_A_B;
    // PUSH_AF;
    // hlcoord(9, 5, wTilemap);
    struct TextPrintState st = {.de = U82C(entry->category), .hl = coord(9, 5, wram->wTilemap)};
    // CALL(aPlaceFarString);  // dex species
    PlaceString(&st, st.hl);
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
    PrintNum(coord(4, 8, wram->wTilemap), &wram->wTempSpecies, PRINTNUM_LEADINGZEROS | 1, 3);
//  Check to see if we caught it.  Get out of here if we haven't.
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // CALL(aCheckCaughtMon);
    // POP_HL;
    // POP_BC;
    // RET_Z ;
    if(!CheckCaughtMon(wram->wTempSpecies - 1))
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
    uint16_t height = NativeToBigEndian16(entry->height);
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
        PrintNum(coord(12, 7, wram->wTilemap), &height, 2, (2 << 4) | 4);
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
    uint16_t weight = NativeToBigEndian16(entry->weight);
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
        PrintNum(coord(11, 9, wram->wTilemap), &weight, 2, (4 << 4) | 5);
        // POP_DE;
    }

// skip_weight:
//  Page 1
    // LD_BC((5 << 8) | SCREEN_WIDTH - 2);
    // hlcoord(2, 11, wTilemap);
    // CALL(aClearBox);
    ClearBox(coord(2, 11, wram->wTilemap), SCREEN_WIDTH - 2, 5);
    // hlcoord(1, 10, wTilemap);
    // LD_BC(SCREEN_WIDTH - 1);
    // LD_A(0x61);  // horizontal divider
    // CALL(aByteFill);
    ByteFill(coord(1, 10, wram->wTilemap), SCREEN_WIDTH - 1, 0x61);
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
    PlaceString(&st, st.hl);
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
    ClearBox(coord(2, 11, wram->wTilemap), SCREEN_WIDTH - 2, 5);
    // hlcoord(1, 10, wTilemap);
    // LD_BC(SCREEN_WIDTH - 1);
    // LD_A(0x61);
    // CALL(aByteFill);
    ByteFill(coord(1, 10, wram->wTilemap), SCREEN_WIDTH - 1, 0x61);
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
    PlaceString(&st, st.hl);
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

uint8_t* GetDexEntryPagePointer(species_t b, uint8_t c){
    // CALL(aGetDexEntryPointer);
    const struct DexEntry* entry = GetDexEntryPointer(b);
    // PUSH_HL;
    // LD_H_D;
    // LD_L_E;
//  skip species name

// loop1:
    // LD_A_B;
    // CALL(aGetFarByte);
    // INC_HL;
    // CP_A(0x50);
    // IF_NZ goto loop1;
//  skip height and weight
    // for(int rept = 0; rept < 4; rept++){
    // INC_HL;
    // }
    uint8_t* de = U82C(entry->description);
//  if c != 1: skip entry
    // DEC_C;
    // IF_Z goto done;
    if(c != 1) {
    //  skip entry
    // loop2:
        // LD_A_B;
        // CALL(aGetFarByte);
        // INC_HL;
        // CP_A(0x50);
        // IF_NZ goto loop2;
        while(*de != CHAR_PAGE) 
            de++;
        de++;
    }


// done:
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // RET;
    return de;
// INCLUDE "data/pokemon/dex_entry_pointers.asm"

}
