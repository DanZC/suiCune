#include "../constants.h"
#include "pokemon.h"
#include "array.h"
#include "print_text.h"
#include "audio.h"
#include "copy.h"
#include "../engine/gfx/place_graphic.h"
#include "../engine/gfx/load_pics.h"
#include "../engine/pokemon/correct_nick_errors.h"
#include "../charmap.h"
#include "../data/pokemon/base_stats.h"
#include "../data/pokemon/pic_pointers.h"
#include "../data/pokemon/unown_pic_pointers.h"
#include "../data/pokemon/cries.h"

bool IsAPokemon(species_t species) {
    // Pokemon index 0 is not a pokemon
    if(species == 0) return false;

    // Eggs are pokemon
    if(species == EGG) return true;

    // Pokemon indicies in range are pokemon
    if(species <= NUM_POKEMON) return true;

    // Everything else is not a pokemon
    return false;
}

//  Draw an HP bar d tiles long at hl
//  Fill it up to e pixels
void DrawBattleHPBar(uint8_t* hl, uint8_t d, uint8_t e, uint8_t b, uint8_t c){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;

//  Place 'HP:'
    // LD_A(0x60);
    // LD_hli_A;
    *(hl++) = 0x60;
    // LD_A(0x61);
    // LD_hli_A;
    *(hl++) = 0x61;

//  Draw a template
    // PUSH_HL;
    uint8_t* hl2 = hl;
    // LD_A(0x62);  // empty bar

    do {
    // template:
        // LD_hli_A;
        *(hl2++) = 0x62;
        // DEC_D;
        // IF_NZ goto template;
    } while(--d != 0);
    // LD_A(0x6b);  // bar end
    // ADD_A_B;
    // LD_hl_A;
    *(hl2) = 0x6b + b;
    // POP_HL;

//  Safety check # pixels
    // LD_A_E;
    // AND_A_A;
    // IF_NZ goto fill;
    if(e == 0) {
        // LD_A_C;
        // AND_A_A;
        // IF_Z goto done;
        if(c == 0)
            return;
        // LD_E(1);
        e = 1;
    }

    do {
    // fill:
        //  Keep drawing tiles until pixel length is reached
        // LD_A_E;
        // SUB_A(TILE_WIDTH);
        // IF_C goto lastbar;
        if(e < TILE_WIDTH) {
        // lastbar:
            // LD_A(0x62);  // empty bar
            // ADD_A_E;  // + e
            // LD_hl_A;
            *hl = 0x62 + e;
            break;
        }

        // LD_E_A;
        e -= TILE_WIDTH;
        // LD_A(0x6a);  // full bar
        // LD_hli_A;
        *(hl++) = 0x6a;
        // LD_A_E;
        // AND_A_A;
        // IF_Z goto done;
        // goto fill;
    } while(e != 0);

// done:
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void PrepMonFrontpic(tile_t* hl){
    // LD_A(0x1);
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0x1;
    return v_PrepMonFrontpic(hl);
}

void v_PrepMonFrontpic(tile_t* hl){
    // LD_A_addr(wCurPartySpecies);
    // CALL(aIsAPokemon);
    // IF_C goto not_pokemon;
    if(IsAPokemon(wram->wCurPartySpecies)) {
        // PUSH_HL;
        // LD_DE(vTiles2);
        // PREDEF(pGetMonFrontpic);
        GetMonFrontpic(vram->vTiles2);
        // POP_HL;
        // XOR_A_A;
        // LDH_addr_A(hGraphicStartTile);
        hram.hGraphicStartTile = 0;
        // LD_BC((7 << 8) | 7);
        // PREDEF(pPlaceGraphic);
        PlaceGraphicYStagger(hl, 7, 7);
        // XOR_A_A;
        // LD_addr_A(wBoxAlignment);
        wram->wBoxAlignment = 0;
        // RET;
        return;
    }

// not_pokemon:
    // XOR_A_A;
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0;
    // INC_A;
    // LD_addr_A(wCurPartySpecies);
    // RET;
    wram->wCurPartySpecies = 1;
}

void PlayStereoCry(species_t species){
    // PUSH_AF;
    // LD_A(1);
    // LD_addr_A(wStereoPanningMask);
    wram->wStereoPanningMask = 1;
    // POP_AF;
    // CALL(av_PlayMonCry);
    v_PlayMonCry(species);
    // CALL(aWaitSFX);
    WaitSFX();
    // RET;
}

//  Don't wait for the cry to end.
//  Used during pic animations.
void PlayStereoCry2(species_t species){
    // PUSH_AF;
    // LD_A(1);
    // LD_addr_A(wStereoPanningMask);
    wram->wStereoPanningMask = 1;
    // POP_AF;
    // JP(mv_PlayMonCry);
    return v_PlayMonCry(species);
}

void PlayMonCry(species_t species){
    // CALL(aPlayMonCry2);
    PlayMonCry2(species);
    // CALL(aWaitSFX);
    WaitSFX();
    // RET;
}

//  Don't wait for the cry to end.
void PlayMonCry2(species_t species){
    // PUSH_AF;
    // XOR_A_A;
    // LD_addr_A(wStereoPanningMask);
    wram->wStereoPanningMask = 0;
    // LD_addr_A(wCryTracks);
    wram->wCryTracks = 0;
    // POP_AF;
    // CALL(av_PlayMonCry);
    v_PlayMonCry(species);
    // RET;
}

void v_PlayMonCry(species_t species){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;

    // CALL(aGetCryIndex);
    // IF_C goto done;

    int16_t idx = GetCryIndex(species);
    if(idx == -1)
        return;

    // LD_E_C;
    // LD_D_B;
    // CALL(aPlayCry);

    // PUSH_DE;
    // REG_DE = (uint16_t)idx;
    PlayCry((uint16_t)idx);
    // POP_DE;


// done:
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

//  Load cry bc.
const struct PokemonCry* LoadCry(species_t a){
    int16_t index = GetCryIndex(a);
    if(index < 0) 
        return NULL;
    uint16_t i = (uint16_t)index;

    const struct PokemonCry* hl = PokemonCries + i;

    wram->wCryPitch = hl->pitch;
    wram->wCryLength = hl->length;

    return hl;
}

int16_t GetCryIndex(species_t index){
    if(index == 0 || index >= (NUM_POKEMON + 1))
        return -1;
    return index;
}

//  Print wTempMonLevel at hl
void PrintLevel(tile_t* hl, uint8_t lvl){
    // LD_A_addr(wTempMonLevel);
    // LD_hl(0x6e);
    // INC_HL;
    uint8_t a = lvl;
    *(hl++) = CHAR_LV;

//  How many digits?
    if(a < 100) {
        // LD_C(2);
        // CP_A(100);  // This is distinct from MAX_LEVEL.
        // JR_C (mPrint8BitNumLeftAlign);
        return Print8BitNumLeftAlign(hl, a, 2);
    }

//  3-digit numbers overwrite the :L.
    // DEC_HL;
    // INC_C;
    // JR(mPrint8BitNumLeftAlign);
    return Print8BitNumLeftAlign(hl - 1, a, 3);
}

void PrintLevel_Force3Digits(tile_t* hl, uint8_t a){
    //  Print :L and all 3 digits
    // LD_hl(0x6e);
    *hl = 0x6e;
    // INC_HL;
    // LD_C(3);

    return Print8BitNumLeftAlign(hl + 1, a, 3);
}

void Print8BitNumLeftAlign(tile_t* hl, uint8_t a, uint8_t c){
    // LD_addr_A(wTextDecimalByte);
    wram->wTextDecimalByte = a;
    // LD_DE(wTextDecimalByte);
    // LD_B(PRINTNUM_LEFTALIGN | 1);
    // JP(mPrintNum);
    PrintNum(hl, &wram->wTextDecimalByte, PRINTNUM_LEFTALIGN | 1, c);
    return;
}

//  //  unreferenced
void GetNthMove(void){
    // LD_HL(wListMoves_MoveIndicesBuffer);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // RET;
}

void GetBaseData(species_t species){
    // printf("%s:: %d\n", __func__, species);
//  Egg doesn't have BaseData
    if(species == EGG)
    {
        //LD_DE(mUnusedEggPic);

    //  Sprite dimensions
        wram->wBasePicSize = 0x55;  // 5x5

    //  Beta front and back sprites
    //  (see pokegold-spaceworld's data/pokemon/base_stats/*)
        // gb_write16(wBaseUnusedFrontpic,     mUnusedEggPic);
        // gb_write16(wBaseUnusedFrontpic + 2, mUnusedEggPic);
    }
    else 
    {

    //  Get BaseData
        //DEC_A;
        const struct BaseData* hl = BasePokemonData + (species - 1);
        //LD_BC(BASE_DATA_SIZE);
        //LD_HL(mBaseData);
        //CALL(aAddNTimes);
        //LD_DE(wCurBaseData);
        //LD_BC(BASE_DATA_SIZE);
        //CALL(aCopyBytes);
        CopyBytes(&wram->wBaseDexNo, hl, sizeof(struct BaseData));
        // If our pic size is 0, we haven't initialized it yet.
        if(hl->picSize == 0) {
            // We dynamically get the base pic size by loading the frontpic and counting how many tiles
            // horizontally the pic takes up and then cache the result in BasePokemonData.

            // If our species is unown, we use the Unown pic table.
            const char* (*const hl)[2] = ((species == UNOWN)? UnownPicPointers: PokemonPicPointers);
            // unown_letter_t c = wram->wUnownLetter;

            // We either get the species or an unown letter, which will be the index into the table.
            uint16_t a = (species == UNOWN)? 1: species;
            const char *path = hl[a - 1][0];
            int w, h;
            LoadDimensionsFromPNG(path, &w, &h);

            // We assume pics have a square proportion (if a pic has a non-square proportion, we must
            // do something more involved since a frontpic image has multiple frames, stacked vertically)
            uint8_t size = (uint8_t)((((w / TILE_WIDTH) & 0xf) << 4) | ((w / TILE_WIDTH) & 0xf));
            wram->wBasePicSize = size;

            // We cache it back into the table.
            BasePokemonData[species - 1].picSize = size;
        }
    }

    //  Replace Pokedex # with species
    wram->wBaseDexNo = species;
}

//  Get nickname a from list hl.
void GetNickname(const uint8_t* hl, uint8_t a){
    // PUSH_HL;
    // PUSH_BC;

    // CALL(aSkipNames);
    hl = SkipNames(hl, a);

    // LD_DE(wStringBuffer1);

    CopyBytes(wram->wStringBuffer1, hl, MON_NAME_LENGTH);

    //PUSH_DE;
    //LD_BC(MON_NAME_LENGTH);
    //CALL(aCopyBytes);
    //POP_DE;

    // CALLFAR(aCorrectNickErrors);
    CorrectNickErrors(wram->wStringBuffer1);

    // POP_BC;
    // POP_HL;
    // RET;
}

uint8_t* GetCurNickname(void){
    CopyBytes(wram->wStringBuffer1, gPokemon.partyMonNickname[wram->wCurPartyMon], MON_NAME_LENGTH);
    CorrectNickErrors(wram->wStringBuffer1);
    return wram->wStringBuffer1;
}