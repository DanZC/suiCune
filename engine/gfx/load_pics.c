#include "../../constants.h"
#include "load_pics.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../../home/tilemap.h"
#include "../../data/pokemon/pic_pointers.h"
#include "../../data/pokemon/unown_pic_pointers.h"
#include "../../data/trainers/pic_pointers.h"

void GetUnownLetter(void){
//  Return Unown letter in wUnownLetter based on DVs at hl

//  Take the middle 2 bits of each DV and place them in order:
//     atk  def  spd  spc
//     .ww..xx.  .yy..zz.

// atk
    LD_A_hl;
    AND_A(0b01100000);
    SLA_A;
    LD_B_A;
// def
    LD_A_hli;
    AND_A(0b00000110);
    SWAP_A;
    SRL_A;
    OR_A_B;
    LD_B_A;

// spd
    LD_A_hl;
    AND_A(0b01100000);
    SWAP_A;
    SLA_A;
    OR_A_B;
    LD_B_A;
// spc
    LD_A_hl;
    AND_A(0b00000110);
    SRL_A;
    OR_A_B;

//  Divide by 10 to get 0-25
    LDH_addr_A(hDividend + 3);
    XOR_A_A;
    LDH_addr_A(hDividend);
    LDH_addr_A(hDividend + 1);
    LDH_addr_A(hDividend + 2);
    LD_A(0xff / NUM_UNOWN + 1);
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);

//  Increment to get 1-26
    LDH_A_addr(hQuotient + 3);
    INC_A;
    LD_addr_A(wUnownLetter);
    RET;

}

//  Return Unown letter in wUnownLetter based on DVs at hl
uint8_t GetUnownLetter_Conv(uint16_t dvs){
//  Take the middle 2 bits of each DV and place them in order:
//     atk  def  spd  spc
//     .ww..xx.  .yy..zz.
// atk
    // LD_A_hl;
    // AND_A(0b01100000);
    // SLA_A;
    // LD_B_A;
    uint8_t b = (LOW(dvs) & 0b01100000) << 1;
// def
    // LD_A_hli;
    // AND_A(0b00000110);
    // SWAP_A;
    // SRL_A;
    // OR_A_B;
    // LD_B_A;
    b |= (LOW(dvs) & 0b00000110) << 3;
// spd
    // LD_A_hl;
    // AND_A(0b01100000);
    // SWAP_A;
    // SLA_A;
    // OR_A_B;
    // LD_B_A;
    b |= (HIGH(dvs) & 0b01100000) >> 3;
// spc
    // LD_A_hl;
    // AND_A(0b00000110);
    // SRL_A;
    // OR_A_B;
    b |= (HIGH(dvs) & 0b00000110) >> 1;

//  Divide by 10 to get 0-25
    // LDH_addr_A(hDividend + 3);
    // XOR_A_A;
    // LDH_addr_A(hDividend);
    // LDH_addr_A(hDividend + 1);
    // LDH_addr_A(hDividend + 2);
    // LD_A(0xff / NUM_UNOWN + 1);
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);
    uint8_t quot = b / 10;

//  Increment to get 1-26
    // LDH_A_addr(hQuotient + 3);
    // INC_A;
    // LD_addr_A(wUnownLetter);
    wram->wUnownLetter = quot + 1;
    // RET;
    return quot + 1;
}

void GetMonFrontpic(void){
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    CALL(aIsAPokemon);
    RET_C ;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    CALL(av_GetFrontpic);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void GetMonFrontpic_Conv(uint8_t* de){
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies;
    // CALL(aIsAPokemon);
    // RET_C ;
    if(!IsAPokemon(wram->wCurSpecies))
        return;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // CALL(av_GetFrontpic);
    v_GetFrontpic_Conv(de, 0);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // RET;
}

void GetAnimatedFrontpic(void){
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    CALL(aIsAPokemon);
    RET_C ;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(av_GetFrontpic);
    CALL(aGetAnimatedEnemyFrontpic);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void GetAnimatedFrontpic_Conv(uint8_t* de, uint8_t frame){
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies;
    // CALL(aIsAPokemon);
    // RET_C ;
    if(!IsAPokemon(wram->wCurSpecies))
        return;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(av_GetFrontpic);
    v_GetFrontpic_Conv(de, frame);
    // CALL(aGetAnimatedEnemyFrontpic);
    GetAnimatedEnemyFrontpic_Conv(de);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // RET;
}

void v_GetFrontpic(void){
    PUSH_DE;
    CALL(aGetBaseData);
    LD_A_addr(wBasePicSize);
    AND_A(0xf);
    LD_B_A;
    PUSH_BC;
    CALL(aGetFrontpicPointer);
    LD_A(MBANK(awDecompressEnemyFrontpic));
    LDH_addr_A(rSVBK);
    LD_A_B;
    LD_DE(wDecompressEnemyFrontpic);
    CALL(aFarDecompress);
    POP_BC;
    LD_HL(wDecompressScratch);
    LD_DE(wDecompressEnemyFrontpic);
    CALL(aPadFrontpic);
    POP_HL;
    PUSH_HL;
    LD_DE(wDecompressScratch);
    LD_C(7 * 7);
    LDH_A_addr(hROMBank);
    LD_B_A;
    CALL(aGet2bpp);
    POP_HL;
    RET;

}

void v_GetFrontpic_Conv(uint8_t* de, uint8_t frame){
    // PUSH_DE;
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurSpecies);
    // LD_A_addr(wBasePicSize);
    // AND_A(0xf);
    // LD_B_A;
    uint8_t b = wram->wBasePicSize & 0xf;
    uint8_t c = (wram->wBasePicSize & 0xf0) >> 4;
    // PUSH_BC;
    // CALL(aGetFrontpicPointer);
    const char* de2 = GetFrontpicPointer_Conv();
    // LD_A(BANK(wDecompressEnemyFrontpic));
    // LDH_addr_A(rSVBK);
    // LD_A_B;
    // LD_DE(wDecompressEnemyFrontpic);
    // CALL(aFarDecompress);
    int size = c * b;
    // printf("Loading frame %d (tile %d, base %d,%d) of %s.\n", frame, size * frame, b, c, de2);
    LoadPNG2bppAssetSectionToVRAM(wram->wDecompressEnemyFrontpic, de2, size * frame, size);
    // POP_BC;
    // LD_HL(wDecompressScratch);
    // LD_DE(wDecompressEnemyFrontpic);
    // CALL(aPadFrontpic);
    PadFrontpic_Conv(wram->wDecompressScratch, wram->wDecompressEnemyFrontpic, b);
    // POP_HL;
    // PUSH_HL;
    // LD_DE(wDecompressScratch);
    // LD_C(7 * 7);
    // LDH_A_addr(hROMBank);
    // LD_B_A;
    // CALL(aGet2bpp);
    // POP_HL;
    // RET;
    CopyBytes(de, wram->wDecompressScratch, 7 * 7 * LEN_2BPP_TILE);
}

void GetFrontpicPointer(void){
    LD_A_addr(wCurPartySpecies);
    CP_A(UNOWN);
    IF_Z goto unown;
    LD_A_addr(wCurPartySpecies);
    LD_D(BANK(aPokemonPicPointers));
    goto ok;

unown:
    LD_A_addr(wUnownLetter);
    LD_D(BANK(aUnownPicPointers));

ok:
// These are assumed to be at the same address in their respective banks.
    //assert ['PokemonPicPointers == UnownPicPointers'];
    LD_HL(mPokemonPicPointers);
    DEC_A;
    LD_BC(6);
    CALL(aAddNTimes);
    LD_A_D;
    CALL(aGetFarByte);
    CALL(aFixPicBank);
    PUSH_AF;
    INC_HL;
    LD_A_D;
    CALL(aGetFarWord);
    POP_BC;
    RET;

}

const char* GetFrontpicPointer_Conv(void){
    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_Z goto unown;
    const char *(*hl)[2];

    uint8_t a = wram->wCurPartySpecies;
    if(a != UNOWN) {
        // LD_A_addr(wCurPartySpecies);
        // LD_D(BANK(aPokemonPicPointers));
        // goto ok;
        hl = PokemonPicPointers;
    }
    else {
    // unown:
        // LD_A_addr(wUnownLetter);
        // LD_D(BANK(aUnownPicPointers));
        a = wram->wUnownLetter;
        hl = UnownPicPointers;
    }

// ok:
// These are assumed to be at the same address in their respective banks.
    //assert ['PokemonPicPointers == UnownPicPointers'];
    // LD_HL(mPokemonPicPointers);
    // DEC_A;
    // LD_BC(6);
    // CALL(aAddNTimes);
    // LD_A_D;
    // CALL(aGetFarByte);
    // CALL(aFixPicBank);
    const char* p = hl[a - 1][0];
    // PUSH_AF;
    // INC_HL;
    // LD_A_D;
    // CALL(aGetFarWord);
    // POP_BC;
    // RET;
    return p;
}

void GetAnimatedEnemyFrontpic(void){
    LD_A(MBANK(avTiles3));
    LDH_addr_A(rVBK);
    PUSH_HL;
    LD_DE(wDecompressScratch);
    LD_C(7 * 7);
    LDH_A_addr(hROMBank);
    LD_B_A;
    CALL(aGet2bpp);
    POP_HL;
    LD_DE(7 * 7 * LEN_2BPP_TILE);
    ADD_HL_DE;
    PUSH_HL;
    LD_A(MBANK(awBasePicSize));
    LD_HL(wBasePicSize);
    CALL(aGetFarWRAMByte);
    POP_HL;
    AND_A(0xf);
    LD_DE(wDecompressEnemyFrontpic + 5 * 5 * LEN_2BPP_TILE);
    LD_C(5 * 5);
    CP_A(5);
    IF_Z goto got_dims;
    LD_DE(wDecompressEnemyFrontpic + 6 * 6 * LEN_2BPP_TILE);
    LD_C(6 * 6);
    CP_A(6);
    IF_Z goto got_dims;
    LD_DE(wDecompressEnemyFrontpic + 7 * 7 * LEN_2BPP_TILE);
    LD_C(7 * 7);

got_dims:
    PUSH_HL;
    PUSH_BC;
    CALL(aLoadFrontpicTiles);
    POP_BC;
    POP_HL;
    LD_DE(wDecompressScratch);
    LDH_A_addr(hROMBank);
    LD_B_A;
    CALL(aGet2bpp);
    XOR_A_A;
    LDH_addr_A(rVBK);
    RET;

}

void GetAnimatedEnemyFrontpic_Conv(uint8_t* hl){
    // LD_A(BANK(vTiles3));
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, MBANK(vTiles3));
    hl += VRAM_BANK_SIZE;
    // PUSH_HL;
    // LD_DE(wDecompressScratch);
    // LD_C(7 * 7);
    // LDH_A_addr(hROMBank);
    // LD_B_A;
    // CALL(aGet2bpp);
    // LoadPNG2bppAssetSectionToVRAM(wram->wDecompressScratch, GetFrontpicPointer_Conv(), 0, 7 * 7);
    CopyBytes(hl, wram->wDecompressScratch, 7 * 7 * LEN_2BPP_TILE);
    // POP_HL;
    // LD_DE(7 * 7 * LEN_2BPP_TILE);
    // ADD_HL_DE;
    // PUSH_HL;
    hl += 7 * 7 * LEN_2BPP_TILE;
    // LD_A(BANK(wBasePicSize));
    // LD_HL(wBasePicSize);
    // CALL(aGetFarWRAMByte);
    // POP_HL;
    // AND_A(0xf);
    uint8_t a = wram->wBasePicSize & 0xf;
    uint8_t* de;
    uint8_t c;
    // LD_DE(wDecompressEnemyFrontpic + 5 * 5 * LEN_2BPP_TILE);
    // LD_C(5 * 5);
    // CP_A(5);
    // IF_Z goto got_dims;
    if(a == 5) {
        de = wram->wDecompressEnemyFrontpic + 5 * 5 * LEN_2BPP_TILE;
        c = 5 * 5;
    }
    // LD_DE(wDecompressEnemyFrontpic + 6 * 6 * LEN_2BPP_TILE);
    // LD_C(6 * 6);
    // CP_A(6);
    // IF_Z goto got_dims;
    else if(a == 6) {
        de = wram->wDecompressEnemyFrontpic + 6 * 6 * LEN_2BPP_TILE;
        c = 6 * 6;
    }
    // LD_DE(wDecompressEnemyFrontpic + 7 * 7 * LEN_2BPP_TILE);
    // LD_C(7 * 7);
    else {
        de = wram->wDecompressEnemyFrontpic + 7 * 7 * LEN_2BPP_TILE;
        c = 7 * 7;
    }

// got_dims:
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aLoadFrontpicTiles);
    LoadFrontpicTiles_Conv(wram->wDecompressScratch, de, c);
    // POP_BC;
    // POP_HL;
    // LD_DE(wDecompressScratch);
    // LDH_A_addr(hROMBank);
    // LD_B_A;
    // CALL(aGet2bpp);
    CopyBytes(hl, wram->wDecompressScratch, 7 * 7 * LEN_2BPP_TILE);
    // XOR_A_A;
    // LDH_addr_A(rVBK);
    // gb_write(rVBK, 0);
    // RET;

}

void LoadFrontpicTiles(void){
    LD_HL(wDecompressScratch);
    SWAP_C;
    LD_A_C;
    AND_A(0xf);
    LD_B_A;
    LD_A_C;
    AND_A(0xf0);
    LD_C_A;
    PUSH_BC;
    CALL(aLoadOrientedFrontpic);
    POP_BC;

loop:
    PUSH_BC;
    LD_C(0);
    CALL(aLoadOrientedFrontpic);
    POP_BC;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void LoadFrontpicTiles_Conv(uint8_t* hl, uint8_t* de, uint8_t c){
    // LD_HL(wDecompressScratch);
    // SWAP_C;
    // LD_A_C;
    // AND_A(0xf);
    // LD_B_A;
    uint8_t b = (c & 0xf);
    // LD_A_C;
    // AND_A(0xf0);
    // LD_C_A;
    // PUSH_BC;
    // CALL(aLoadOrientedFrontpic);
    LoadOrientedFrontpic_Conv(&hl, &de, (c & 0xf0));
    // POP_BC;

    do {
    // loop:
        // PUSH_BC;
        // LD_C(0);
        // CALL(aLoadOrientedFrontpic);
        LoadOrientedFrontpic_Conv(&hl, &de, 0);
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

void GetMonBackpic(void){
    LD_A_addr(wCurPartySpecies);
    CALL(aIsAPokemon);
    RET_C ;

    LD_A_addr(wCurPartySpecies);
    LD_B_A;
    LD_A_addr(wUnownLetter);
    LD_C_A;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);
    PUSH_DE;

// These are assumed to be at the same address in their respective banks.
    //assert ['PokemonPicPointers == UnownPicPointers'];
    LD_HL(mPokemonPicPointers);
    LD_A_B;
    LD_D(BANK(aPokemonPicPointers));
    CP_A(UNOWN);
    IF_NZ goto ok;
    LD_A_C;
    LD_D(BANK(aUnownPicPointers));

ok:
    DEC_A;
    LD_BC(6);
    CALL(aAddNTimes);
    LD_BC(3);
    ADD_HL_BC;
    LD_A_D;
    CALL(aGetFarByte);
    CALL(aFixPicBank);
    PUSH_AF;
    INC_HL;
    LD_A_D;
    CALL(aGetFarWord);
    LD_DE(wDecompressScratch);
    POP_AF;
    CALL(aFarDecompress);
    LD_HL(wDecompressScratch);
    LD_C(6 * 6);
    CALL(aFixBackpicAlignment);
    POP_HL;
    LD_DE(wDecompressScratch);
    LDH_A_addr(hROMBank);
    LD_B_A;
    CALL(aGet2bpp);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void GetMonBackpic_Conv(uint8_t* de, species_t species){
    (void)de;
    // LD_A_addr(wCurPartySpecies);
    // CALL(aIsAPokemon);
    // RET_C ;
    if(!IsAPokemon(species))
        return;

    // LD_A_addr(wCurPartySpecies);
    // LD_B_A;
    species_t b = wram->wCurPartySpecies;
    // LD_A_addr(wUnownLetter);
    // LD_C_A;
    unown_letter_t c = wram->wUnownLetter;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awDecompressScratch));
    // LDH_addr_A(rSVBK);
    // PUSH_DE;

// These are assumed to be at the same address in their respective banks.
    //assert ['PokemonPicPointers == UnownPicPointers'];
    // LD_HL(mPokemonPicPointers);
    // LD_A_B;
    // LD_D(BANK(aPokemonPicPointers));
    // CP_A(UNOWN);
    // IF_NZ goto ok;
    // LD_A_C;
    // LD_D(BANK(aUnownPicPointers));
    const char* (*const hl)[2] = ((b == UNOWN)? UnownPicPointers: PokemonPicPointers);
    uint16_t a = (b == UNOWN)? c: b;

// ok:
    // DEC_A;
    const char *path = hl[a - 1][1];
    // LD_BC(6);
    // CALL(aAddNTimes);
    // LD_BC(3);
    // ADD_HL_BC;
    // LD_A_D;
    // CALL(aGetFarByte);
    // CALL(aFixPicBank);
    // PUSH_AF;
    // INC_HL;
    // LD_A_D;
    // CALL(aGetFarWord);
    // LD_DE(wDecompressScratch);
    // POP_AF;
    // CALL(aFarDecompress);
    LoadPNG2bppAssetToVRAM(wram->wDecompressScratch, path);
    // LD_HL(wDecompressScratch);
    // LD_C(6 * 6);
    // CALL(aFixBackpicAlignment);
    FixBackpicAlignment_Conv(wram->wDecompressScratch, 6 * 6);
    // POP_HL;
    // LD_DE(wDecompressScratch);
    // LDH_A_addr(hROMBank);
    // LD_B_A;
    // CALL(aGet2bpp);
    CopyBytes(de, wram->wDecompressScratch, 6 * 6 * LEN_2BPP_TILE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void FixPicBank(void){
//  This is a thing for some reason.

#define PICS_FIX (0x36)

    PUSH_HL;
    PUSH_BC;
    SUB_A(BANK(aHoOhFrontpic) - PICS_FIX);
    LD_C_A;
    LD_B(0);
    LD_HL(mFixPicBank_PicsBanks);
    ADD_HL_BC;
    LD_A_hl;
    POP_BC;
    POP_HL;
    RET;


PicsBanks:
    //db ['BANK("Pics 1")'];  // BANK("Pics 1") + 0
    //db ['BANK("Pics 2")'];  // BANK("Pics 1") + 1
    //db ['BANK("Pics 3")'];  // BANK("Pics 1") + 2
    //db ['BANK("Pics 4")'];  // BANK("Pics 1") + 3
    //db ['BANK("Pics 5")'];  // BANK("Pics 1") + 4
    //db ['BANK("Pics 6")'];  // BANK("Pics 1") + 5
    //db ['BANK("Pics 7")'];  // BANK("Pics 1") + 6
    //db ['BANK("Pics 8")'];  // BANK("Pics 1") + 7
    //db ['BANK("Pics 9")'];  // BANK("Pics 1") + 8
    //db ['BANK("Pics 10")'];  // BANK("Pics 1") + 9
    //db ['BANK("Pics 11")'];  // BANK("Pics 1") + 10
    //db ['BANK("Pics 12")'];  // BANK("Pics 1") + 11
    //db ['BANK("Pics 13")'];  // BANK("Pics 1") + 12
    //db ['BANK("Pics 14")'];  // BANK("Pics 1") + 13
    //db ['BANK("Pics 15")'];  // BANK("Pics 1") + 14
    //db ['BANK("Pics 16")'];  // BANK("Pics 1") + 15
    //db ['BANK("Pics 17")'];  // BANK("Pics 1") + 16
    //db ['BANK("Pics 18")'];  // BANK("Pics 1") + 17
    //db ['BANK("Pics 19")'];  // BANK("Pics 1") + 18
    //db ['BANK("Pics 20")'];  // BANK("Pics 1") + 19
    //db ['BANK("Pics 21")'];  // BANK("Pics 1") + 20
    //db ['BANK("Pics 22")'];  // BANK("Pics 1") + 21
    //db ['BANK("Pics 23")'];  // BANK("Pics 1") + 22
    //db ['BANK("Pics 24")'];  // BANK("Pics 1") + 23

    return GSIntro_GetMonFrontpic();
}

void GSIntro_GetMonFrontpic(void){
//  //  unreferenced
    LD_A_C;
    PUSH_DE;
    LD_HL(mPokemonPicPointers);
    DEC_A;
    LD_BC(6);
    CALL(aAddNTimes);
    LD_A(BANK(aPokemonPicPointers));
    CALL(aGetFarByte);
    CALL(aFixPicBank);
    PUSH_AF;
    INC_HL;
    LD_A(BANK(aPokemonPicPointers));
    CALL(aGetFarWord);
    POP_AF;
    POP_DE;
    CALL(aFarDecompress);
    RET;

}

void GetTrainerPic(void){
    LD_A_addr(wTrainerClass);
    AND_A_A;
    RET_Z ;
    CP_A(NUM_TRAINER_CLASSES + 1);
    RET_NC ;
    CALL(aWaitBGMap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_HL(mTrainerPicPointers);
    LD_A_addr(wTrainerClass);
    DEC_A;
    LD_BC(3);
    CALL(aAddNTimes);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);
    PUSH_DE;
    LD_A(BANK(aTrainerPicPointers));
    CALL(aGetFarByte);
    CALL(aFixPicBank);
    PUSH_AF;
    INC_HL;
    LD_A(BANK(aTrainerPicPointers));
    CALL(aGetFarWord);
    POP_AF;
    LD_DE(wDecompressScratch);
    CALL(aFarDecompress);
    POP_HL;
    LD_DE(wDecompressScratch);
    LD_C(7 * 7);
    LDH_A_addr(hROMBank);
    LD_B_A;
    CALL(aGet2bpp);
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aWaitBGMap);
    LD_A(1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void GetTrainerPic_Conv(uint8_t* de, uint8_t tclass){
    // LD_A_addr(wTrainerClass);
    // AND_A_A;
    // RET_Z ;
    // CP_A(NUM_TRAINER_CLASSES + 1);
    // RET_NC ;
    if(tclass == 0 || tclass >= NUM_TRAINER_CLASSES + 1)
        return;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_HL(mTrainerPicPointers);
    // LD_A_addr(wTrainerClass);
    // DEC_A;
    // LD_BC(3);
    // CALL(aAddNTimes);
    const char* hl = TrainerPicPointers[tclass - 1];
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(MBANK(awDecompressScratch));
    // LDH_addr_A(rSVBK);
    // PUSH_DE;
    // LD_A(BANK(aTrainerPicPointers));
    // CALL(aGetFarByte);
    // CALL(aFixPicBank);
    // PUSH_AF;
    // INC_HL;
    // LD_A(BANK(aTrainerPicPointers));
    // CALL(aGetFarWord);
    // POP_AF;
    // LD_DE(wDecompressScratch);
    // CALL(aFarDecompress);
    // POP_HL;
    // LD_DE(wDecompressScratch);
    // LD_C(7 * 7);
    // LDH_A_addr(hROMBank);
    // LD_B_A;
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(de, hl, 0, 7 * 7);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_A(1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

void DecompressGet2bpp(void){
//  Decompress lz data from b:hl to wDecompressScratch, then copy it to address de.

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(MBANK(awDecompressScratch));
    LDH_addr_A(rSVBK);

    PUSH_DE;
    PUSH_BC;
    LD_A_B;
    LD_DE(wDecompressScratch);
    CALL(aFarDecompress);
    POP_BC;
    LD_DE(wDecompressScratch);
    POP_HL;
    LDH_A_addr(hROMBank);
    LD_B_A;
    CALL(aGet2bpp);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void FixBackpicAlignment(void){
    PUSH_DE;
    PUSH_BC;
    LD_A_addr(wBoxAlignment);
    AND_A_A;
    IF_Z goto keep_dims;
    LD_A_C;
    CP_A(7 * 7);
    LD_DE(7 * 7 * LEN_2BPP_TILE);
    IF_Z goto got_dims;
    CP_A(6 * 6);
    LD_DE(6 * 6 * LEN_2BPP_TILE);
    IF_Z goto got_dims;
    LD_DE(5 * 5 * LEN_2BPP_TILE);


got_dims:
    LD_A_hl;
    LD_B(0);
    LD_C(8);

loop:
    RRA;
    RL_B;
    DEC_C;
    IF_NZ goto loop;
    LD_A_B;
    LD_hli_A;
    DEC_DE;
    LD_A_E;
    OR_A_D;
    IF_NZ goto got_dims;


keep_dims:
    POP_BC;
    POP_DE;
    RET;

}

void FixBackpicAlignment_Conv(uint8_t* hl, uint8_t c){
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_addr(wBoxAlignment);
    // AND_A_A;
    // IF_Z goto keep_dims;
    if(wram->wBoxAlignment == 0)
        return;
    
    uint16_t de;
    // LD_A_C;
    // CP_A(7 * 7);
    // LD_DE(7 * 7 * LEN_2BPP_TILE);
    // IF_Z goto got_dims;
    if(c == 7 * 7) {
        de = 7 * 7 * LEN_2BPP_TILE;
    }
    // CP_A(6 * 6);
    // LD_DE(6 * 6 * LEN_2BPP_TILE);
    // IF_Z goto got_dims;
    else if(c == 6 * 6) {
        de = 6 * 6 * LEN_2BPP_TILE;
    }
    // LD_DE(5 * 5 * LEN_2BPP_TILE);
    else {
        de = 5 * 5 * LEN_2BPP_TILE;
    }

    do {
    // got_dims:
        // LD_A_hl;
        uint8_t a = *hl;
        // LD_B(0);
        uint8_t b = 0;
        // LD_C(8);
        uint8_t c = 8;

        uint8_t carry = 0;
    
        do {
        // loop:
            // RRA;
            carry = a & 1;
            a = (a >> 1);
            b = (b << 1) | carry;
            // RL_B;
            // DEC_C;
            // IF_NZ goto loop;
        } while(--c != 0);
        // LD_A_B;
        // LD_hli_A;
        *hl = b;
        hl++;
        // DEC_DE;
        // LD_A_E;
        // OR_A_D;
        // IF_NZ goto got_dims;
    } while(--de != 0);

// keep_dims:
    // POP_BC;
    // POP_DE;
    // RET;
}

void PadFrontpic(void){
//  pads frontpic to fill 7x7 box
    LD_A_B;
    CP_A(6);
    IF_Z goto six;
    CP_A(5);
    IF_Z goto five;


seven_loop:
    LD_C(7 << 4);
    CALL(aLoadOrientedFrontpic);
    DEC_B;
    IF_NZ goto seven_loop;
    RET;


six:
    LD_C(7 << 4);
    XOR_A_A;
    CALL(aPadFrontpic_Fill);

six_loop:
    LD_C((7 - 6) << 4);
    XOR_A_A;
    CALL(aPadFrontpic_Fill);
    LD_C(6 << 4);
    CALL(aLoadOrientedFrontpic);
    DEC_B;
    IF_NZ goto six_loop;
    RET;


five:
    LD_C(7 << 4);
    XOR_A_A;
    CALL(aPadFrontpic_Fill);

five_loop:
    LD_C((7 - 5) << 4);
    XOR_A_A;
    CALL(aPadFrontpic_Fill);
    LD_C(5 << 4);
    CALL(aLoadOrientedFrontpic);
    DEC_B;
    IF_NZ goto five_loop;
    LD_C(7 << 4);
    XOR_A_A;
    CALL(aPadFrontpic_Fill);
    RET;


Fill:
    LD_hli_A;
    DEC_C;
    IF_NZ goto Fill;
    RET;

}

static uint8_t* PadFrontpic_Fill(uint8_t* hl, uint8_t c, uint8_t a) {
    do {
        // LD_hli_A;
        *(hl++) = a;
        // DEC_C;
        // IF_NZ goto Fill;
    } while(--c != 0);
    // RET;
    return hl;
}

//  pads frontpic to fill 7x7 box
void PadFrontpic_Conv(uint8_t* hl, uint8_t* de, uint8_t b){
    // LD_A_B;
    // CP_A(6);
    // IF_Z goto six;
    if(b == 6) {
    // six:
        // LD_C(7 << 4);
        // XOR_A_A;
        // CALL(aPadFrontpic_Fill);
        hl = PadFrontpic_Fill(hl, 7 << 4, 0);

        do {
        // six_loop:
            // LD_C((7 - 6) << 4);
            // XOR_A_A;
            // CALL(aPadFrontpic_Fill);
            hl = PadFrontpic_Fill(hl, (7 - 6) << 4, 0);
            // LD_C(6 << 4);
            // CALL(aLoadOrientedFrontpic);
            LoadOrientedFrontpic_Conv(&hl, &de, 6 << 4);
            // DEC_B;
            // IF_NZ goto six_loop;
        } while(--b != 0);
        // RET;
        return;
    }
    // CP_A(5);
    // IF_Z goto five;
    else if(b == 5) {
    // five:
        // LD_C(7 << 4);
        // XOR_A_A;
        // CALL(aPadFrontpic_Fill);
        hl = PadFrontpic_Fill(hl, 7 << 4, 0);
        hl = PadFrontpic_Fill(hl, 7 << 4, 0);

        do {
        // five_loop:
            // LD_C((7 - 5) << 4);
            // XOR_A_A;
            // CALL(aPadFrontpic_Fill);
            hl = PadFrontpic_Fill(hl, (7 - 6) << 4, 0);
            // LD_C(5 << 4);
            // CALL(aLoadOrientedFrontpic);
            LoadOrientedFrontpic_Conv(&hl, &de, 5 << 4);
            
            hl = PadFrontpic_Fill(hl, (7 - 6) << 4, 0);
            // DEC_B;
            // IF_NZ goto five_loop;
        } while(--b != 0);
        // LD_C(7 << 4);
        // XOR_A_A;
        // CALL(aPadFrontpic_Fill);
        // RET;
        return;
    }

    do {
    // seven_loop:
        // LD_C(7 << 4);
        // CALL(aLoadOrientedFrontpic);
        LoadOrientedFrontpic_Conv(&hl, &de, 7 << 4);
        // DEC_B;
        // IF_NZ goto seven_loop;
    } while(--b != 0);
    // RET;
    return;
}

void LoadOrientedFrontpic(void){
    LD_A_addr(wBoxAlignment);
    AND_A_A;
    IF_NZ goto x_flip;

left_loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_C;
    IF_NZ goto left_loop;
    RET;


x_flip:
    PUSH_BC;

right_loop:
    LD_A_de;
    INC_DE;
    LD_B_A;
    XOR_A_A;
    for(int rept = 0; rept < 8; rept++){
    RR_B;
    RLA;
    }
    LD_hli_A;
    DEC_C;
    IF_NZ goto right_loop;
    POP_BC;
    RET;

}

void LoadOrientedFrontpic_Conv(uint8_t** hl, uint8_t** de, uint8_t c){
    // LD_A_addr(wBoxAlignment);
    // AND_A_A;
    // IF_NZ goto x_flip;
    uint8_t* hl_ = *hl;
    uint8_t* de_ = *de;
    if(wram->wBoxAlignment == 0) {
        do {
        // left_loop:
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            *(hl_++) = *(de_++);
            // DEC_C;
            // IF_NZ goto left_loop;
        } while(--c != 0);
        // RET;
        *hl = hl_;
        *de = de_;
        return;
    }
    else {
    // x_flip:

        // PUSH_BC;

        do {
        // right_loop:
            // LD_A_de;
            // INC_DE;
            // LD_B_A;
            // XOR_A_A;
            uint8_t b = *(de_++);
            uint8_t a = 0;
            uint8_t cy = 0;
            uint8_t temp;
            for(int rept = 0; rept < 8; rept++){
                // RR_B;
                {
                    temp = b & 1;
                    b >>= 1;
                    b |= (cy << 7);
                    cy = temp;
                }
                // RLA;
                {
                    temp = a;
                    a = (a << 1) | cy;
                    cy = (temp >> 7) & 1;
                }
            }
            // LD_hli_A;
            *(hl_++) = a;
            // DEC_C;
            // IF_NZ goto right_loop;
        } while(--c != 0);
        // POP_BC;
        // RET;
        *hl = hl_;
        *de = de_;
        return;
    }

}

