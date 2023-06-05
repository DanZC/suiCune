#include "../constants.h"
#include "pokemon.h"
#include "array.h"

void IsAPokemon(void){
    //  Return carry if species a is not a Pokemon.
    AND_A_A;
    IF_Z goto NotAPokemon;
    CP_A(EGG);
    IF_Z goto Pokemon;
    CP_A(NUM_POKEMON + 1);
    IF_C goto Pokemon;


NotAPokemon:
        SCF;
    RET;


Pokemon:
        AND_A_A;
    RET;

}

bool IsAPokemon_Conv(uint8_t species) {
    // Pokemon index 0 is not a pokemon
    if(species == 0) return false;

    // Eggs are pokemon
    if(species == EGG) return true;

    // Pokemon indicies in range are pokemon
    if(species <= NUM_POKEMON) return true;

    // Everything else is not a pokemon
    return false;
}

void DrawBattleHPBar(void){
    //  Draw an HP bar d tiles long at hl
//  Fill it up to e pixels

    PUSH_HL;
    PUSH_DE;
    PUSH_BC;

//  Place 'HP:'
    LD_A(0x60);
    LD_hli_A;
    LD_A(0x61);
    LD_hli_A;

//  Draw a template
    PUSH_HL;
    LD_A(0x62);  // empty bar

template:
        LD_hli_A;
    DEC_D;
    IF_NZ goto template;
    LD_A(0x6b);  // bar end
    ADD_A_B;
    LD_hl_A;
    POP_HL;

//  Safety check # pixels
    LD_A_E;
    AND_A_A;
    IF_NZ goto fill;
    LD_A_C;
    AND_A_A;
    IF_Z goto done;
    LD_E(1);


fill:
    //  Keep drawing tiles until pixel length is reached
    LD_A_E;
    SUB_A(TILE_WIDTH);
    IF_C goto lastbar;

    LD_E_A;
    LD_A(0x6a);  // full bar
    LD_hli_A;
    LD_A_E;
    AND_A_A;
    IF_Z goto done;
    goto fill;


lastbar:
        LD_A(0x62);  // empty bar
    ADD_A_E;  // + e
    LD_hl_A;


done:
        POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void PrepMonFrontpic(void){
        LD_A(0x1);
    LD_addr_A(wBoxAlignment);

    return v_PrepMonFrontpic();
}

void v_PrepMonFrontpic(void){
        LD_A_addr(wCurPartySpecies);
    CALL(aIsAPokemon);
    IF_C goto not_pokemon;

    PUSH_HL;
    LD_DE(vTiles2);
    PREDEF(pGetMonFrontpic);
    POP_HL;
    XOR_A_A;
    LDH_addr_A(hGraphicStartTile);
    LD_BC((7 << 8) | 7);
    PREDEF(pPlaceGraphic);
    XOR_A_A;
    LD_addr_A(wBoxAlignment);
    RET;


not_pokemon:
        XOR_A_A;
    LD_addr_A(wBoxAlignment);
    INC_A;
    LD_addr_A(wCurPartySpecies);
    RET;

}

void PlayStereoCry(void){
        PUSH_AF;
    LD_A(1);
    LD_addr_A(wStereoPanningMask);
    POP_AF;
    CALL(av_PlayMonCry);
    CALL(aWaitSFX);
    RET;

}

void PlayStereoCry2(void){
    //  Don't wait for the cry to end.
//  Used during pic animations.
    PUSH_AF;
    LD_A(1);
    LD_addr_A(wStereoPanningMask);
    POP_AF;
    JP(mv_PlayMonCry);

}

void PlayMonCry(void){
        CALL(aPlayMonCry2);
    CALL(aWaitSFX);
    RET;

}

void PlayMonCry2(void){
    //  Don't wait for the cry to end.
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wStereoPanningMask);
    LD_addr_A(wCryTracks);
    POP_AF;
    CALL(av_PlayMonCry);
    RET;

}

void v_PlayMonCry(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;

    CALL(aGetCryIndex);
    IF_C goto done;

    LD_E_C;
    LD_D_B;
    CALL(aPlayCry);


done:
        POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void LoadCry(void){
    //  Load cry bc.

    CALL(aGetCryIndex);
    RET_C ;

    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(aPokemonCries));
    RST(aBankswitch);

    LD_HL(mPokemonCries);
    for(int rept = 0; rept < MON_CRY_LENGTH; rept++){
    ADD_HL_BC;
    }

    LD_E_hl;
    INC_HL;
    LD_D_hl;
    INC_HL;

    LD_A_hli;
    LD_addr_A(wCryPitch);
    LD_A_hli;
    LD_addr_A(wCryPitch + 1);
    LD_A_hli;
    LD_addr_A(wCryLength);
    LD_A_hl;
    LD_addr_A(wCryLength + 1);

    POP_AF;
    RST(aBankswitch);
    AND_A_A;
    RET;

}

uint16_t LoadCry_Conv(uint8_t a){
    //  Load cry bc.
    int16_t index = GetCryIndex_Conv(a);
    if(index < 0) return 0;
    uint16_t i = (uint16_t)index;

    uint8_t oldBank = gb_read(hROMBank);
    Bankswitch_Conv(BANK(aPokemonCries));

    uint16_t hl = mPokemonCries + (MON_CRY_LENGTH * i);

    uint16_t de = gb_read16(hl);
    hl += 2;

    gb_write(wCryPitch, gb_read(hl++));
    gb_write(wCryPitch + 1, gb_read(hl++));
    gb_write(wCryLength, gb_read(hl++));
    gb_write(wCryLength + 1, gb_read(hl));

    Bankswitch_Conv(oldBank);

    return de;
}

void GetCryIndex(void){
        AND_A_A;
    IF_Z goto no;
    CP_A(NUM_POKEMON + 1);
    IF_NC goto no;

    DEC_A;
    LD_C_A;
    LD_B(0);
    AND_A_A;
    RET;


no:
        SCF;
    RET;

}

int16_t GetCryIndex_Conv(uint8_t index){
    if(index == 0 || index >= (NUM_POKEMON + 1))
        return -1;
    return (index - 1);
}

void PrintLevel(void){
    //  Print wTempMonLevel at hl

    LD_A_addr(wTempMonLevel);
    LD_hl(0x6e);
    INC_HL;

//  How many digits?
    LD_C(2);
    CP_A(100);  // This is distinct from MAX_LEVEL.
    JR_C (mPrint8BitNumLeftAlign);

//  3-digit numbers overwrite the :L.
    DEC_HL;
    INC_C;
    JR(mPrint8BitNumLeftAlign);

}

void PrintLevel_Force3Digits(void){
    //  Print :L and all 3 digits
    LD_hl(0x6e);
    INC_HL;
    LD_C(3);

    return Print8BitNumLeftAlign();
}

void Print8BitNumLeftAlign(void){
        LD_addr_A(wTextDecimalByte);
    LD_DE(wTextDecimalByte);
    LD_B(PRINTNUM_LEFTALIGN | 1);
    JP(mPrintNum);

}

void GetNthMove(void){
    //  //  unreferenced
    LD_HL(wListMoves_MoveIndicesBuffer);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    RET;

}

void GetBaseData(void){
        PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(aBaseData));
    RST(aBankswitch);

//  Egg doesn't have BaseData
    LD_A_addr(wCurSpecies);
    CP_A(EGG);
    IF_Z goto egg;

//  Get BaseData
    DEC_A;
    LD_BC(BASE_DATA_SIZE);
    LD_HL(mBaseData);
    CALL(aAddNTimes);
    LD_DE(wCurBaseData);
    LD_BC(BASE_DATA_SIZE);
    CALL(aCopyBytes);
    goto end;


egg:
        LD_DE(mUnusedEggPic);

//  Sprite dimensions
    LD_B(0x55);  // 5x5
    LD_HL(wBasePicSize);
    LD_hl_B;

//  Beta front and back sprites
//  (see pokegold-spaceworld's data/pokemon/base_stats/*)
    LD_HL(wBaseUnusedFrontpic);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    INC_HL;
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    goto end;  // useless


end:
    //  Replace Pokedex # with species
    LD_A_addr(wCurSpecies);
    LD_addr_A(wBaseDexNo);

    POP_AF;
    RST(aBankswitch);
    POP_HL;
    POP_DE;
    POP_BC;
    RET;

}

void CopyBytes_Conv(uint16_t de, uint16_t hl, uint16_t bc);

void GetBaseData_Conv(void){
    uint8_t oldBank = gb_read(hROMBank);
    Bankswitch_Conv(BANK(aBaseData));

//  Egg doesn't have BaseData
    uint8_t species = gb_read(wCurSpecies);
    if(species == EGG)
    {
        //LD_DE(mUnusedEggPic);

    //  Sprite dimensions
        gb_write(wBasePicSize, 0x55);  // 5x5

    //  Beta front and back sprites
    //  (see pokegold-spaceworld's data/pokemon/base_stats/*)
        gb_write16(wBaseUnusedFrontpic,     mUnusedEggPic);
        gb_write16(wBaseUnusedFrontpic + 2, mUnusedEggPic);
    }
    else 
    {

    //  Get BaseData
        species--;
        //DEC_A;
        uint16_t hl = mBaseData + (BASE_DATA_SIZE * species);
        uint16_t de = wCurBaseData;
        CopyBytes_Conv(de, hl, BASE_DATA_SIZE);
        //LD_BC(BASE_DATA_SIZE);
        //LD_HL(mBaseData);
        //CALL(aAddNTimes);
        //LD_DE(wCurBaseData);
        //LD_BC(BASE_DATA_SIZE);
        //CALL(aCopyBytes);
    }

    //  Replace Pokedex # with species
    gb_write(wBaseDexNo, gb_read(wCurSpecies));

    Bankswitch_Conv(oldBank);
}

void GetCurNickname(void){
        LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonNicknames);

    return GetNickname();
}

void GetNickname(void){
    //  Get nickname a from list hl.

    PUSH_HL;
    PUSH_BC;

    CALL(aSkipNames);
    LD_DE(wStringBuffer1);

    PUSH_DE;
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    POP_DE;

    CALLFAR(aCorrectNickErrors);

    POP_BC;
    POP_HL;
    RET;

}

//  Get nickname a from list hl.
void GetNickname_Conv(uint16_t hl, uint8_t a){
    // PUSH_HL;
    // PUSH_BC;

    // CALL(aSkipNames);
    hl = SkipNames_Conv(hl, a);

    // LD_DE(wStringBuffer1);

    CopyBytes_Conv(wStringBuffer1, hl, MON_NAME_LENGTH);

    //PUSH_DE;
    //LD_BC(MON_NAME_LENGTH);
    //CALL(aCopyBytes);
    //POP_DE;

    CALLFAR(aCorrectNickErrors);

    // POP_BC;
    // POP_HL;
    // RET;

}

void GetCurNickname_Conv(void){
    return GetNickname_Conv(wPartyMonNicknames, gb_read(wCurPartyMon));
}