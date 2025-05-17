#include "../constants.h"
#include "mobile_42.h"
#include "mobile_41.h"
#include "../home/delay.h"
#include "../home/copy.h"
#include "../home/gfx.h"
#include "../home/names.h"
#include "../home/tilemap.h"
#include "../home/clear_sprites.h"
#include "../home/text.h"
#include "../home/lcd.h"
#include "../home/palettes.h"
#include "../home/print_text.h"
#include "../home/pokemon.h"
#include "../home/video.h"
#include "../home/sprite_anims.h"
#include "../home/audio.h"
#include "../engine/gfx/place_graphic.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/sprites.h"
#include "../engine/gfx/pic_animation.h"
#include "../engine/gfx/load_pics.h"
#include "../engine/movie/trade_animation.h"
#include "../data/text/common.h"
#include "../charmap.h"

// add_mobiletradeanim: MACRO
// \1_MobileTradeCmd:
//     dw \1
// ENDM
#define add_mobiletradeanim(_x) [_x##_MobileTradeCmd] = _x

// mobiletradeanim: MACRO
//     db (\1_MobileTradeCmd - MobileTradeAnim_JumptableLoop.Jumptable) / 2
// ENDM
#define mobiletradeanim(_x) _x##_MobileTradeCmd

enum {
    mobiletradeanim(GetMobileTradeAnimByte),  // 00
    mobiletradeanim(MobileTradeAnim_ShowPlayerMonToBeSent),  // 01
    mobiletradeanim(MobileTradeAnim_02),  // 02
    mobiletradeanim(MobileTradeAnim_GiveTrademon1),  // 03
    mobiletradeanim(MobileTradeAnim_GiveTrademon2),  // 04
    mobiletradeanim(MobileTradeAnim_05),  // 05
    mobiletradeanim(MobileTradeAnim_06),  // 06
    mobiletradeanim(MobileTradeAnim_07),  // 07
    mobiletradeanim(MobileTradeAnim_GetTrademon1),  // 08
    mobiletradeanim(MobileTradeAnim_GetTrademon2),  // 09
    mobiletradeanim(MobileTradeAnim_GetTrademon3),  // 0a
    mobiletradeanim(MobileTradeAnim_ShowOTMonFromTrade),  // 0b
    mobiletradeanim(EndMobileTradeAnim),  // 0c
    mobiletradeanim(MobileTradeAnim_ShowPlayerMonForGTS),  // 0d
    mobiletradeanim(MobileTradeAnim_ShowOTMonFromGTS),  // 0e
    mobiletradeanim(MobileTradeAnim_0f),  // 0f
    mobiletradeanim(MobileTradeAnim_10),  // 10
    mobiletradeanim(MobileTradeAnim_11),  // 11
    mobiletradeanim(MobileTradeAnim_FadeToBlack),  // 12
    mobiletradeanim(MobileTradeAnim_GetOddEgg),  // 13 get odd egg
};

void MobileTradeAnimation_SendGivemonToGTS(void){
    static const uint8_t TradeAnimScript[] = {
        mobiletradeanim(MobileTradeAnim_ShowPlayerMonForGTS),
        mobiletradeanim(MobileTradeAnim_FadeToBlack),
        mobiletradeanim(MobileTradeAnim_10),
        mobiletradeanim(MobileTradeAnim_GiveTrademon1),
        mobiletradeanim(MobileTradeAnim_06),
        mobiletradeanim(MobileTradeAnim_0f),
        mobiletradeanim(EndMobileTradeAnim),
    };
    // LD_A(0x80);
    // LD_addr_A(wcf65);
    wram->wcf65 = 0x80;
    // LD_DE(mMobileTradeAnimation_SendGivemonToGTS_TradeAnimScript);
    // JP(mRunMobileTradeAnim_NoFrontpics);
    return RunMobileTradeAnim_NoFrontpics(TradeAnimScript);
}

void MobileTradeAnimation_RetrieveGivemonFromGTS(void){
    // LD_A(0x80);
    // JR(masm_108018);
    return asm_108018(0x80);
}

void MobileTradeAnimation_ReceiveGetmonFromGTS(void){
    // LD_A(0x0);
    return asm_108018(0x0);
}

void asm_108018(uint8_t a){
    static const uint8_t TradeAnimScript[] = {
        mobiletradeanim(MobileTradeAnim_11),
        mobiletradeanim(MobileTradeAnim_07),
        mobiletradeanim(MobileTradeAnim_GetTrademon1),
        mobiletradeanim(MobileTradeAnim_ShowOTMonFromGTS),
        mobiletradeanim(EndMobileTradeAnim),
    };
    // LD_addr_A(wcf65);
    wram->wcf65 = a;
    // LD_DE(masm_108018_TradeAnimScript);
    // JP(mRunMobileTradeAnim_NoFrontpics);
    return RunMobileTradeAnim_NoFrontpics(TradeAnimScript);
}

void Function108026(void){
    // LD_A(0x0);
    // JR(masm_10802c);
    return asm_10802c(0x0);
}

void Function10802a(void){
    // LD_A(0x1);

    return asm_10802c(0x1);
}

void asm_10802c(uint8_t a){
    static const uint8_t TradeAnimScript[] = {
    //   //  trade
        mobiletradeanim(MobileTradeAnim_ShowPlayerMonToBeSent),
        mobiletradeanim(MobileTradeAnim_FadeToBlack),
        mobiletradeanim(MobileTradeAnim_02),
        mobiletradeanim(MobileTradeAnim_GiveTrademon1),
        mobiletradeanim(MobileTradeAnim_05),
        mobiletradeanim(MobileTradeAnim_GetTrademon1),
        mobiletradeanim(MobileTradeAnim_ShowOTMonFromTrade),
        mobiletradeanim(EndMobileTradeAnim),
    };
    // LD_addr_A(wcf65);
    wram->wcf65 = a;
    // LD_DE(masm_10802c_TradeAnimScript);
    // JP(mRunMobileTradeAnim_Frontpics);
    RunMobileTradeAnim_Frontpics(TradeAnimScript);
}

void Function10803d(void){
    static const uint8_t TradeAnimScript[] = {
        mobiletradeanim(MobileTradeAnim_11),
        mobiletradeanim(MobileTradeAnim_07),
        mobiletradeanim(MobileTradeAnim_GetTrademon1),
        mobiletradeanim(MobileTradeAnim_GetOddEgg),
        mobiletradeanim(EndMobileTradeAnim),
    };
    // LD_A(0x0);
    // LD_addr_A(wcf65);
    wram->wcf65 = 0x0;
    // LD_DE(mFunction10803d_TradeAnimScript);
    // JP(mRunMobileTradeAnim_NoFrontpics);
    RunMobileTradeAnim_NoFrontpics(TradeAnimScript);
}

void Function10804d(void){
    static const uint8_t TradeAnimScript[] = {
        mobiletradeanim(MobileTradeAnim_11),
        mobiletradeanim(MobileTradeAnim_ShowOTMonFromGTS),
        mobiletradeanim(EndMobileTradeAnim),
    };
    // LD_A(0x0);
    // LD_addr_A(wcf65);
    wram->wcf65 = 0x0;
    // LD_DE(mFunction10804d_TradeAnimScript);
    // JP(mRunMobileTradeAnim_NoFrontpics);
    RunMobileTradeAnim_NoFrontpics(TradeAnimScript);
}

void RunMobileTradeAnim_Frontpics(const uint8_t* de){
    // LD_HL(wTradeAnimAddress);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gTradeAnimAddress = de;
    // LDH_A_addr(hMapAnims);
    // PUSH_AF;
    uint8_t mapAnims = hram.hMapAnims;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram.hMapAnims = FALSE;
    // LD_HL(wVramState);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // RES_hl(0);
    bit_reset(wram->wVramState, 0);
    // LD_HL(wOptions);
    // LD_A_hl;
    uint8_t options = wram->wOptions;
    // PUSH_AF;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aFunction1080b7);
    Function1080b7();

    bool done;
    do {
    // loop:
        // CALL(aMobileTradeAnim_JumptableLoop);
        done = MobileTradeAnim_JumptableLoop();
        // IF_NC goto loop;
    } while(!done);
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LDH_addr_A(hMapAnims);
    hram.hMapAnims = mapAnims;
    // RET;
}

void RunMobileTradeAnim_NoFrontpics(const uint8_t* de){
    // LD_HL(wTradeAnimAddress);
    // LD_hl_E;
    // INC_HL;
    // LD_hl_D;
    gTradeAnimAddress = de;
    // LDH_A_addr(hMapAnims);
    // PUSH_AF;
    uint8_t mapAnims = hram.hMapAnims;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram.hMapAnims = FALSE;
    // LD_HL(wVramState);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // RES_hl(0);
    bit_reset(wram->wVramState, 0);
    // LD_HL(wOptions);
    // LD_A_hl;
    uint8_t options = wram->wOptions;
    // PUSH_AF;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aFunction108157);
    Function108157();

    bool done;
    do {
    // loop:
        // CALL(aMobileTradeAnim_JumptableLoop);
        done = MobileTradeAnim_JumptableLoop();
        // IF_NC goto loop;
    } while(!done);
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LDH_addr_A(hMapAnims);
    hram.hMapAnims = mapAnims;
    // RET;
}

void Function1080b7(void){
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aMobileTradeAnim_ClearTiles);
    MobileTradeAnim_ClearTiles();
    // CALL(aMobileTradeAnim_ClearBGMap);
    MobileTradeAnim_ClearBGMap();
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra();

    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_HL(mMobileTradeGFX);
    // LD_DE(vTiles2);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles5, MobileTradeGFX);

    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // LD_HL(mMobileTradeSpritesGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x20);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x20, MobileTradeSpritesGFX);

    // CALL(aEnableLCD);
    EnableLCD();

    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();

    // CALL(aDelayFrame);
    DelayFrame();

    // LD_DE(mTradeBallGFX);
    // LD_HL(vTiles0);
    // LD_BC((BANK(aTradeBallGFX) << 8) | 6);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 0 * LEN_2BPP_TILE, TradeBallGFX, 0, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 1 * LEN_2BPP_TILE, TradeBallGFX, 2, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 2 * LEN_2BPP_TILE, TradeBallGFX, 4, 4);

    // LD_DE(mTradePoofGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x06);
    // LD_BC((BANK(aTradePoofGFX) << 8) | 12);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x06, TradePoofGFX, 0, 12);

    // XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT
    // LD_HL(wSpriteAnimDict);
    // LD_hli_A;
    wram->wSpriteAnimDict[0] = SPRITE_ANIM_DICT_DEFAULT;
    // LD_hl(0x00);
    wram->wSpriteAnimDict[1] = 0x00;

    // LD_A_addr(wPlayerTrademonSpecies);
    // LD_HL(wPlayerTrademonDVs);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x30);
    // CALL(aMobileTradeAnim_GetFrontpic);
    MobileTradeAnim_GetFrontpic(vram->vTiles0 + LEN_2BPP_TILE * 0x30, wram->wPlayerTrademon.species, wram->wPlayerTrademon.dvs);

    // LD_A_addr(wOTTrademonSpecies);
    // LD_HL(wOTTrademonDVs);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // CALL(aMobileTradeAnim_GetFrontpic);
    MobileTradeAnim_GetFrontpic(vram->vTiles2 + LEN_2BPP_TILE * 0x31, wram->wOTTrademon.species, wram->wOTTrademon.dvs);

    // LD_A_addr(wPlayerTrademonSpecies);
    // LD_DE(wPlayerTrademonSpeciesName);
    // CALL(aMobileTradeAnim_InitSpeciesName);
    MobileTradeAnim_InitSpeciesName(wram->wPlayerTrademon.speciesName, wram->wPlayerTrademon.species);

    // LD_A_addr(wOTTrademonSpecies);
    // LD_DE(wOTTrademonSpeciesName);
    // CALL(aMobileTradeAnim_InitSpeciesName);
    MobileTradeAnim_InitSpeciesName(wram->wOTTrademon.speciesName, wram->wOTTrademon.species);

    // XOR_A_A;
    // CALL(aFunction108b98);
    // CALL(aFunction108af4);
    Function108af4();
    // RET;
}

void Function108157(void){
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aMobileTradeAnim_ClearTiles);
    MobileTradeAnim_ClearTiles();
    // CALL(aMobileTradeAnim_ClearBGMap);
    MobileTradeAnim_ClearBGMap();
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra();
    // CALL(aEnableLCD);
    EnableLCD();
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims();
    // XOR_A_A;  // SPRITE_ANIM_DICT_DEFAULT
    // LD_HL(wSpriteAnimDict);
    // LD_hli_A;
    wram->wSpriteAnimDict[0] = SPRITE_ANIM_DICT_DEFAULT;
    // LD_hl(0x00);
    wram->wSpriteAnimDict[1] = 0x00;
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A_addr(wPlayerTrademonSpecies);
    // LD_DE(wPlayerTrademonSpeciesName);
    // CALL(aMobileTradeAnim_InitSpeciesName);
    MobileTradeAnim_InitSpeciesName(wram->wPlayerTrademon.speciesName, wram->wPlayerTrademon.species);
    // LD_A_addr(wOTTrademonSpecies);
    // LD_DE(wOTTrademonSpeciesName);
    // CALL(aMobileTradeAnim_InitSpeciesName);
    MobileTradeAnim_InitSpeciesName(wram->wOTTrademon.speciesName, wram->wOTTrademon.species);
    // XOR_A_A;
    // CALL(aFunction108b98);
    // CALL(aFunction108af4);
    Function108af4();
    // RET;
}

void MobileTradeAnim_ClearTiles(void){
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_HL(vTiles0);
    // LD_BC(3 * 0x80 * LEN_2BPP_TILE);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(vram->vTiles3, 3 * 0x80 * LEN_2BPP_TILE, 0);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // LD_HL(vTiles0);
    // LD_BC(3 * 0x80 * LEN_2BPP_TILE);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(vram->vTiles0, 3 * 0x80 * LEN_2BPP_TILE, 0);
    // RET;
}

void MobileTradeAnim_ClearBGMap(void){
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // hlbgcoord(0, 0, vBGMap0);
    // LD_BC(2 * BG_MAP_HEIGHT * BG_MAP_WIDTH);
    // LD_A(0x0);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 0, vram->vBGMap2), 2 * BG_MAP_HEIGHT * BG_MAP_WIDTH, 0x0);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // hlbgcoord(0, 0, vBGMap0);
    // LD_BC(2 * BG_MAP_HEIGHT * BG_MAP_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(bgcoord(0, 0, vram->vBGMap0), 2 * BG_MAP_HEIGHT * BG_MAP_WIDTH, 0x7f);
    // RET;
}

void MobileTradeAnim_GetFrontpic(uint8_t* de, species_t species, uint16_t dvs){
    // PUSH_DE;
    // PUSH_AF;
    // PREDEF(pGetUnownLetter);
    GetUnownLetter(dvs);
    // POP_AF;
    // LD_addr_A(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies = species;
    // CALL(aGetBaseData);
    GetBaseData(species);
    // POP_DE;
    // PREDEF(pGetMonFrontpic);
    GetMonFrontpic(de);
    // RET;
}

void Function108201(uint8_t* de, species_t species, uint16_t dvs){
    // PUSH_DE;
    // PUSH_AF;
    // PREDEF(pGetUnownLetter);
    GetUnownLetter(dvs);
    // POP_AF;
    // LD_addr_A(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies = species;
    // CALL(aGetBaseData);
    GetBaseData(species);
    // POP_DE;
    // PREDEF(pGetAnimatedFrontpic);
    GetAnimatedFrontpic(de, 0);
    // RET;
}

void Function108219(void){
//  //  unreferenced
    LD_addr_A(wCurPartySpecies);
    hlcoord(7, 2, wTilemap);
    LD_D(0x0);
    LD_E(ANIM_MON_TRADE);
    PREDEF(pAnimateFrontpic);
    RET;

}

void Function108229(species_t species){
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = species;
    // hlcoord(7, 2, wTilemap);
    // LD_D(0x0);
    // LD_E(ANIM_MON_TRADE);
    // PREDEF(pLoadMonAnimation);
    LoadMonAnimation(coord(7, 2, wram->wTilemap), 0x0, ANIM_MON_TRADE);
    // RET;
}

void MobileTradeAnim_InitSpeciesName(uint8_t* de, species_t species){
    // PUSH_DE;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // POP_DE;
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(de, GetPokemonName(species), MON_NAME_LENGTH);
    // RET;
}

static void (*const MobileTradeAnim_JumptableLoop_Jumptable[])(void) = {
    add_mobiletradeanim(GetMobileTradeAnimByte),  // 00
    add_mobiletradeanim(MobileTradeAnim_ShowPlayerMonToBeSent),  // 01
    add_mobiletradeanim(MobileTradeAnim_02),  // 02
    add_mobiletradeanim(MobileTradeAnim_GiveTrademon1),  // 03
    add_mobiletradeanim(MobileTradeAnim_GiveTrademon2),  // 04
    add_mobiletradeanim(MobileTradeAnim_05),  // 05
    add_mobiletradeanim(MobileTradeAnim_06),  // 06
    add_mobiletradeanim(MobileTradeAnim_07),  // 07
    add_mobiletradeanim(MobileTradeAnim_GetTrademon1),  // 08
    add_mobiletradeanim(MobileTradeAnim_GetTrademon2),  // 09
    add_mobiletradeanim(MobileTradeAnim_GetTrademon3),  // 0a
    add_mobiletradeanim(MobileTradeAnim_ShowOTMonFromTrade),  // 0b
    add_mobiletradeanim(EndMobileTradeAnim),  // 0c
    add_mobiletradeanim(MobileTradeAnim_ShowPlayerMonForGTS),  // 0d
    add_mobiletradeanim(MobileTradeAnim_ShowOTMonFromGTS),  // 0e
    add_mobiletradeanim(MobileTradeAnim_0f),  // 0f
    add_mobiletradeanim(MobileTradeAnim_10),  // 10
    add_mobiletradeanim(MobileTradeAnim_11),  // 11
    add_mobiletradeanim(MobileTradeAnim_FadeToBlack),  // 12
    add_mobiletradeanim(MobileTradeAnim_GetOddEgg),  // 13 get odd egg)
};

bool MobileTradeAnim_JumptableLoop(void){
    // LD_A_addr(wJumptableIndex);
    // BIT_A(7);
    // IF_NZ goto StopAnim;
    if(!bit_test(wram->wJumptableIndex, 7)) {
        // CALL(aMobileTradeAnim_JumptableLoop_ExecuteMobileTradeAnimCommand);
        // inlined
        // ExecuteMobileTradeAnimCommand:
        //jumptable ['.Jumptable', 'wJumptableIndex']
        MobileTradeAnim_JumptableLoop_Jumptable[wram->wJumptableIndex]();
        // CALL(aDelayFrame);
        DelayFrame();
        // AND_A_A;
        // RET;
        return false;
    }

// StopAnim:
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra();
    // FARCALL(aStubbed_Function106462);
    Stubbed_Function106462();
    // FARCALL(aFunction106464);
    Function106464();
    // SCF;
    // RET;
    return true;
}

void MobileTradeAnim_Next(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;
}

void GetMobileTradeAnimByte(void){
    // LD_HL(wTradeAnimAddress);
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    const uint8_t* de = gTradeAnimAddress;
    // LD_A_de;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = *de;
    // INC_DE;
    de++;
    // LD_hl_D;
    // DEC_HL;
    // LD_hl_E;
    gTradeAnimAddress = de;
    // RET;
}

void EndMobileTradeAnim(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    // RET;
    bit_set(wram->wJumptableIndex, 7);
}

void WaitMobileTradeSpriteAnims(uint8_t c){
    do {
    // loop:
        // PUSH_BC;
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations();
        // POP_BC;
        // CALL(aDelayFrame);
        DelayFrame();
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void Function1082db(void){
    bool done;
    do {
    // loop:
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations();
        // FARCALL(aSetUpPokeAnim);
        done = SetUpPokeAnim();
        // FARCALL(aHDMATransferTilemapToWRAMBank3);
        HDMATransferTilemapToWRAMBank3();
        // IF_NC goto loop;
    } while(!done);
    // RET;
}

void Function1082f0(uint16_t* hl, uint8_t c){
    do {
    // loop:
        // CALL(aFunction108b78);
        Function108b78(hl, c);
        // CALL(aDelayFrame);
        DelayFrame();
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void Function1082fa(uint16_t* hl, uint8_t c){
    do {
    // loop:
        // CALL(aFunction108b78);
        Function108b78(hl, c);
        // PUSH_HL;
        // PUSH_BC;
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations();
        // POP_BC;
        // POP_HL;
        // CALL(aDelayFrame);
        DelayFrame();
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void MobileTradeAnim_ShowPlayerMonToBeSent(void){
    // LD_DE(MUSIC_EVOLUTION);
    // CALL(aPlayMusic2);
    PlayMusic2(MUSIC_EVOLUTION);
    // LD_A(0x80);
    // LDH_addr_A(hSCX);
    hram.hSCX = 0x80;
    // XOR_A_A;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0;
    // LD_A(0x87);
    // LDH_addr_A(hWX);
    hram.hWX = 0x87;
    // LD_A(0x50);
    // LDH_addr_A(hWY);
    hram.hWY = 0x50;
    // CALL(aMobileTradeAnim_DisplayMonToBeSent);
    MobileTradeAnim_DisplayMonToBeSent();
    // LD_A_addr(wPlayerTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wPlayerTrademon.species;
    // CALL(aFunction10895e);
    Function10895e();
    // LD_A_addr(wPlayerTrademonDVs);
    // LD_addr_A(wTempMonDVs);
    // LD_A_addr(wPlayerTrademonDVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = wram->wPlayerTrademon.dvs;
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0b11100100);
    // CALL(aWaitBGMap);
    WaitBGMap();

    while(hram.hWX != 0x7) {
    // loop:
        // LDH_A_addr(hWX);
        // CP_A(0x7);
        // IF_Z goto okay;
        // SUB_A(0x4);
        // LDH_addr_A(hWX);
        hram.hWX -= 0x4;
        // LDH_A_addr(hSCX);
        // SUB_A(0x4);
        // LDH_addr_A(hSCX);
        hram.hSCX -= 0x4;
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// okay:
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0;
    // LD_A_addr(wPlayerTrademonSpecies);
    // CALL(aGetCryIndex);
    int16_t cryIndex = GetCryIndex(wram->wPlayerTrademon.species);
    // IF_C goto skip_cry;
    if(cryIndex >= 0) {
        // LD_E_C;
        // LD_D_B;
        // CALL(aPlayCry);
        PlayCry((uint16_t)cryIndex);
    }

// skip_cry:
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames(80);
    // CALL(aFunction108bec);
    Function108bec();
    // depixel4(10, 11, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_SENT_BALL);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_SENT_BALL, pixel4(10, 11, 4, 0));
    // LD_DE(SFX_BALL_POOF);
    // CALL(aPlaySFX);
    PlaySFX(SFX_BALL_POOF);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(12 * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), 12 * SCREEN_WIDTH, 0x7f);
    // LD_C(80);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(80);
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_ShowOTMonFromTrade(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aMobileTradeAnim_ClearBGMap);
    MobileTradeAnim_ClearBGMap();
    // LD_A_addr(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    // LD_HL(wOTTrademonDVs);
    // LD_DE(vTiles2);
    // CALL(aFunction108201);
    Function108201(vram->vTiles2, wram->wOTTrademon.species,  wram->wOTTrademon.dvs);
    // CALL(aEnableLCD);
    EnableLCD();
    // FARCALL(aDeinitializeAllSprites);
    DeinitializeAllSprites();
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0x0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // depixel4(10, 11, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_BALL);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_BALL, pixel4(10, 11, 4, 0));
    // CALL(aFunction108b45);
    Function108b45();
    // LD_A(0x1);
    // CALL(aFunction108b98);
    // CALL(aFunction108af4);
    Function108af4();
    // LD_C(48);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(48);
    // LD_DE(SFX_BALL_POOF);
    // CALL(aPlaySFX);
    PlaySFX(SFX_BALL_POOF);
    // CALL(aMobileTradeAnim_DisplayReceivedMon);
    MobileTradeAnim_DisplayReceivedMon();
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0x0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x50);
    // LDH_addr_A(hWY);
    hram.hWY = 0x50;
    // LD_A_addr(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wOTTrademon.species;
    // LD_A_addr(wOTTrademonDVs);
    // LD_addr_A(wTempMonDVs);
    // LD_A_addr(wOTTrademonDVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = wram->wOTTrademon.dvs;
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0b11100100);
    // CALL(aFunction108963);
    Function108963();
    // LD_A_addr(wOTTrademonSpecies);
    // CALL(aFunction108229);
    Function108229(wram->wOTTrademon.species);
    // CALL(aFunction1082db);
    Function1082db();
    // CALL(aFunction108c16);
    Function108c16();
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_ShowPlayerMonForGTS(void){
    // LD_DE(MUSIC_EVOLUTION);
    // CALL(aPlayMusic2);
    PlayMusic2(MUSIC_EVOLUTION);
    // LD_A(0x80);
    // LDH_addr_A(hSCX);
    hram.hSCX = 0x80;
    // XOR_A_A;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0x0;
    // LD_A(0x87);
    // LDH_addr_A(hWX);
    hram.hWX = 0x87;
    // LD_A(0x50);
    // LDH_addr_A(hWY);
    hram.hWY = 0x50;
    // CALL(aMobileTradeAnim_DisplayMonToBeSent);
    MobileTradeAnim_DisplayMonToBeSent();
    // LD_A_addr(wPlayerTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wPlayerTrademon.species;
    // LD_HL(wPlayerTrademonDVs);
    // CALL(aFunction10898a);
    Function10898a(wram->wPlayerTrademon.species, wram->wPlayerTrademon.dvs);
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_DE(mTradeBallGFX);
    // LD_HL(vTiles0);
    // LD_BC((BANK(aTradeBallGFX) << 8) | 6);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 0 * LEN_2BPP_TILE, TradeBallGFX, 0, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 1 * LEN_2BPP_TILE, TradeBallGFX, 2, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 2 * LEN_2BPP_TILE, TradeBallGFX, 4, 4);
    // LD_DE(mTradePoofGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x06);
    // LD_BC((BANK(aTradePoofGFX) << 8) | 12);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x06, TradePoofGFX, 0, 12);
    // LD_A_addr(wPlayerTrademonDVs);
    // LD_addr_A(wTempMonDVs);
    // LD_A_addr(wPlayerTrademonDVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = wram->wPlayerTrademon.dvs;
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0b11100100);
    // CALL(aWaitBGMap);
    WaitBGMap();

    while(hram.hWX != 0x7) {
    // loop:
        // LDH_A_addr(hWX);
        // CP_A(0x7);
        // IF_Z goto done;
        // SUB_A(0x4);
        // LDH_addr_A(hWX);
        hram.hWX -= 0x4;
        // LDH_A_addr(hSCX);
        // SUB_A(0x4);
        // LDH_addr_A(hSCX);
        hram.hSCX -= 0x4;
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// done:
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0;
    // LD_A_addr(wPlayerTrademonSpecies);
    // CALL(aGetCryIndex);
    int16_t cry = GetCryIndex(wram->wPlayerTrademon.species);
    // IF_C goto skip_cry;
    if(cry >= 0) {
        // LD_E_C;
        // LD_D_B;
        // CALL(aPlayCry);
        PlayCry((uint16_t)cry);
    }

// skip_cry:
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames(80);
    // CALL(aFunction108c2b);
    Function108c2b();
    // depixel4(10, 11, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_SENT_BALL);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_SENT_BALL, pixel4(10, 11, 4, 0));
    // LD_DE(SFX_BALL_POOF);
    // CALL(aPlaySFX);
    PlaySFX(SFX_BALL_POOF);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(12 * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), 12 * SCREEN_WIDTH, 0x7f);
    // LD_C(80);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(80);
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_ShowOTMonFromGTS(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aMobileTradeAnim_ClearBGMap);
    MobileTradeAnim_ClearBGMap();
    // LD_A_addr(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    // LD_HL(wOTTrademonDVs);
    // LD_DE(vTiles2);
    // CALL(aFunction108201);
    Function108201(vram->vTiles2, wram->wOTTrademon.species, wram->wOTTrademon.dvs);
    // CALL(aEnableLCD);
    EnableLCD();
    // FARCALL(aDeinitializeAllSprites);
    DeinitializeAllSprites();
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_DE(mTradeBallGFX);
    // LD_HL(vTiles0);
    // LD_BC((BANK(aTradeBallGFX) << 8) | 6);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 0 * LEN_2BPP_TILE, TradeBallGFX, 0, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 1 * LEN_2BPP_TILE, TradeBallGFX, 2, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 2 * LEN_2BPP_TILE, TradeBallGFX, 4, 4);
    // LD_DE(mTradePoofGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x06);
    // LD_BC((BANK(aTradePoofGFX) << 8) | 12);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x06, TradePoofGFX, 0, 12);
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0x0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // depixel4(10, 11, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_BALL);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_BALL, pixel4(10, 11, 4, 0));
    // CALL(aFunction108b45);
    Function108b45();
    // LD_A(0x1);
    // CALL(aFunction108b98);
    // CALL(aFunction108af4);
    Function108af4();
    // LD_C(48);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(48);
    // LD_DE(SFX_BALL_POOF);
    // CALL(aPlaySFX);
    PlaySFX(SFX_BALL_POOF);
    // CALL(aMobileTradeAnim_DisplayReceivedMon);
    MobileTradeAnim_DisplayReceivedMon();
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0x0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0x0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x50);
    // LDH_addr_A(hWY);
    hram.hWY = 0x50;
    // LD_A_addr(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wOTTrademon.species;
    // LD_A_addr(wOTTrademonDVs);
    // LD_addr_A(wTempMonDVs);
    // LD_A_addr(wOTTrademonDVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = wram->wOTTrademon.dvs;
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0b11100100);
    // LD_A_addr(wOTTrademonSpecies);
    // LD_HL(wOTTrademonDVs);
    // CALL(aFunction10898a);
    Function10898a(wram->wOTTrademon.species, wram->wOTTrademon.dvs);
    // LD_A_addr(wOTTrademonSpecies);
    // CALL(aFunction108229);
    Function108229(wram->wOTTrademon.species);
    // CALL(aFunction1082db);
    Function1082db();
    // CALL(aFunction108c40);
    Function108c40();
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_GetOddEgg(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aMobileTradeAnim_ClearBGMap);
    MobileTradeAnim_ClearBGMap();
    // LD_A_addr(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    // LD_HL(wOTTrademonDVs);
    // LD_DE(vTiles2);
    // CALL(aFunction108201);
    Function108201(vram->vTiles2, wram->wOTTrademon.species, wram->wOTTrademon.dvs);
    // CALL(aEnableLCD);
    EnableLCD();
    // FARCALL(aDeinitializeAllSprites);
    DeinitializeAllSprites();
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_DE(mTradeBallGFX);
    // LD_HL(vTiles0);
    // LD_BC((BANK(aTradeBallGFX) << 8) | 6);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 0 * LEN_2BPP_TILE, TradeBallGFX, 0, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 1 * LEN_2BPP_TILE, TradeBallGFX, 2, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + 2 * LEN_2BPP_TILE, TradeBallGFX, 4, 4);
    // LD_DE(mTradePoofGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x06);
    // LD_BC((BANK(aTradePoofGFX) << 8) | 12);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x06, TradePoofGFX, 0, 12);
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // depixel4(10, 11, 4, 0);
    // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_BALL);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_BALL, pixel4(10, 11, 4, 0));
    // CALL(aFunction108b45);
    Function108b45();
    // LD_A(0x1);
    // CALL(aFunction108b98);
    // CALL(aFunction108af4);
    Function108af4();
    // LD_C(48);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(48);
    // LD_DE(SFX_BALL_POOF);
    // CALL(aPlaySFX);
    PlaySFX(SFX_BALL_POOF);
    // CALL(aFunction108a33);
    Function108a33();
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram.hSCX = 0;
    // LDH_addr_A(hSCY);
    hram.hSCY = 0;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x50);
    // LDH_addr_A(hWY);
    hram.hWY = 0x50;
    // LD_A_addr(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wOTTrademon.species;
    // LD_A_addr(wOTTrademonDVs);
    // LD_addr_A(wTempMonDVs);
    // LD_A_addr(wOTTrademonDVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = wram->wOTTrademon.dvs;
    // LD_B(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_PLAYER_OR_MON_FRONTPIC_PALS);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0b11100100);
    // LD_A_addr(wOTTrademonSpecies);
    // LD_HL(wOTTrademonDVs);
    // CALL(aFunction10898a);
    Function10898a(wram->wOTTrademon.species, wram->wOTTrademon.dvs);
    // LD_A_addr(wOTTrademonSpecies);
    // CALL(aFunction108229);
    Function108229(wram->wOTTrademon.species);
    // CALL(aFunction1082db);
    Function1082db();
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_02(void){
    // FARCALL(aDeinitializeAllSprites);
    DeinitializeAllSprites();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aMobileTradeAnim_ClearBGMap);
    MobileTradeAnim_ClearBGMap();
    // CALL(aFunction108c80);
    Function108c80();
    // CALL(aFunction108c6d);
    Function108c6d();
    // CALL(aEnableLCD);
    EnableLCD();
    // LD_A(0xc);
    // LDH_addr_A(hSCX);
    hram.hSCX = 0xc;
    // LD_A(0x78);
    // LDH_addr_A(hSCY);
    hram.hSCY = 0x78;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mMobileTradeBGPalettes);
    // LD_DE(wBGPals1);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    LoadPaletteAssetColorsToBuffer(wram->wBGPals1, 8 * PALETTE_SIZE, MobileTradeBGPalettes, 0, 8 * NUM_PAL_COLORS);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aLoadMobileAdapterPalette);
    LoadMobileAdapterPalette();
    // CALL(aFunction108af4);
    Function108af4();
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_10(void){
    // FARCALL(aDeinitializeAllSprites);
    DeinitializeAllSprites();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aMobileTradeAnim_ClearBGMap);
    MobileTradeAnim_ClearBGMap();
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_HL(mMobileTradeGFX);
    // LD_DE(vTiles2);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles5, MobileTradeGFX);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // LD_HL(mMobileTradeSpritesGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x20);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x20, MobileTradeGFX);
    // CALL(aFunction108c80);
    Function108c80();
    // CALL(aFunction108c6d);
    Function108c6d();
    // CALL(aEnableLCD);
    EnableLCD();
    // LD_A(0xc);
    // LDH_addr_A(hSCX);
    hram.hSCX = 0xc;
    // LD_A(0x78);
    // LDH_addr_A(hSCY);
    hram.hSCY = 0x78;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mMobileTradeBGPalettes);
    // LD_DE(wBGPals1);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    LoadPaletteAssetColorsToBuffer(wram->wBGPals1, 8 * PALETTE_SIZE, MobileTradeBGPalettes, 0, 8 * NUM_PAL_COLORS);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aLoadMobileAdapterPalette);
    LoadMobileAdapterPalette();
    // CALL(aFunction108af4);
    Function108af4();
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_11(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_HL(mMobileTradeGFX);
    // LD_DE(vTiles2);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles5, MobileTradeGFX);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // LD_HL(mMobileTradeSpritesGFX);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x20);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x20, MobileTradeSpritesGFX);
    // CALL(aFunction108c80);
    Function108c80();
    // CALL(aFunction108c6d);
    Function108c6d();
    // CALL(aEnableLCD);
    EnableLCD();
    // LD_A(0x80);
    // LDH_addr_A(hSCX);
    hram.hSCX = 0x80;
    // LD_A(0x90);
    // LDH_addr_A(hSCY);
    hram.hSCY = 0x90;
    // LD_A(0x7);
    // LDH_addr_A(hWX);
    hram.hWX = 0x7;
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mMobileTradeBGPalettes);
    // LD_DE(wBGPals1);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    LoadPaletteAssetColorsToBuffer(wram->wBGPals1, 8 * PALETTE_SIZE, MobileTradeBGPalettes, 0, 8 * NUM_PAL_COLORS);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aLoadMobileAdapterPalette);
    LoadMobileAdapterPalette();
    // CALL(aFunction108af4);
    Function108af4();
    // CALL(aFunction108b5a);
    Function108b5a();
    // LD_A(0xe0);
    // LDH_addr_A(hSCX);
    hram.hSCX = 0xe0;
    // LD_DE(MUSIC_EVOLUTION);
    // CALL(aPlayMusic2);
    PlayMusic2(MUSIC_EVOLUTION);
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_GiveTrademon1(void){
    // LD_DE(SFX_GIVE_TRADEMON);
    // CALL(aPlaySFX);
    PlaySFX(SFX_GIVE_TRADEMON);
    // LD_C(40);
    // LD_HL(wBGPals2 + PALETTE_SIZE * 6);
    // CALL(aFunction1082f0);
    Function1082f0((uint16_t*)(wram->wBGPals2 + PALETTE_SIZE * 6), 40);
    // CALL(aFunction108af4);
    Function108af4();

    while(hram.hSCX != 0xe0) {
    // loop:
        // LDH_A_addr(hSCX);
        // CP_A(0xe0);
        // IF_Z goto loop2;
        // DEC_A;
        // DEC_A;
        // LDH_addr_A(hSCX);
        hram.hSCX -= 2;
        // CP_A(0xf8);
        // IF_NZ goto next;
        if(hram.hSCX == 0xf8) {
            // depixel4(10, 11, 4, 0);
            // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_CABLE_BULGE);
            // CALL(aInitSpriteAnimStruct);
            InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_CABLE_BULGE, pixel4(10, 11, 4, 0));
        }

    // next:
        // LD_C(1);
        // CALL(aWaitMobileTradeSpriteAnims);
        WaitMobileTradeSpriteAnims(1);
        // goto loop;
    }

    while(hram.hSCY != 0xf8) {
    // loop2:
        // LDH_A_addr(hSCY);
        // CP_A(0xf8);
        // IF_Z goto done;
        // DEC_A;
        // DEC_A;
        // LDH_addr_A(hSCY);
        hram.hSCY -= 2;
        // CP_A(0x40);
        // IF_Z goto init;
        if(hram.hSCY == 0x40) {
        // init:
            // depixel4(10, 11, 4, 0);
            // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_CABLE_BULGE);
            // CALL(aInitSpriteAnimStruct);
            InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_CABLE_BULGE, pixel4(10, 11, 4, 0));
            // XOR_A_A;
            // CALL(aFunction108ad4);
            Function108ad4(0);
            // goto next2;
        }
        // CP_A(0x30);
        // IF_Z goto delete;
        else if(hram.hSCY == 0x30) {
        // delete:
            // CALL(aMobileTradeAnim_DeleteSprites);
            MobileTradeAnim_DeleteSprites();
            // goto next2;
        }
        // CP_A(0x68);
        // IF_Z goto replace;
        else if(hram.hSCY == 0x68) {
        // replace:
            // CALL(aMobileTradeAnim_DeleteSprites);
            MobileTradeAnim_DeleteSprites();
            // LD_A(0x1);
            // CALL(aFunction108ad4);
            Function108ad4(0x1);
        }
        // goto next2;

    // next2:
        // LD_C(1);
        // CALL(aWaitMobileTradeSpriteAnims);
        WaitMobileTradeSpriteAnims(1);
        // goto loop2;
    }

// done:
    // CALL(aMobileTradeAnim_Next);
    MobileTradeAnim_Next();
    // RET;
}

void MobileTradeAnim_GiveTrademon2(void){
    // LD_C(40);
    // LD_HL(wBGPals2 + 1 * PALETTE_SIZE);
    // CALL(aFunction1082f0);
    Function1082f0((uint16_t*)(wram->wBGPals2 + PALETTE_SIZE * 1), 40);
    // CALL(aFunction108af4);
    Function108af4();
    // CALL(aFunction108b5a);
    Function108b5a();
    // depixel4(9, 10, 2, 0);
    // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_PING);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_PING, pixel4(9, 10, 2, 0));
    // LD_DE(SFX_FORESIGHT);
    // CALL(aPlaySFX);
    PlaySFX(SFX_FORESIGHT);
    // LD_C(10);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(10);
    // XOR_A_A;
    // LD_addr_A(wcf64);
    wram->wcf64 = 0;
    // depixel4(9, 10, 2, 0);
    // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_SENT_PULSE);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_SENT_PULSE, pixel4(9, 10, 2, 0));

    while(hram.hSCY != 0x90) {
    // loop:
        // LDH_A_addr(hSCY);
        // CP_A(0x90);
        // IF_Z goto done;
        // SUB_A(0x8);
        // LDH_addr_A(hSCY);
        hram.hSCY -= 0x8;
        // LD_C(1);
        // CALL(aWaitMobileTradeSpriteAnims);
        WaitMobileTradeSpriteAnims(1);
        // goto loop;
    }

// done:
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_05(void){
    // LD_C(40);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(40);
    // LD_A(0x1);
    // LD_addr_A(wcf64);
    wram->wcf64 = 0x1;
    // LD_DE(SFX_SHARPEN);
    // CALL(aPlaySFX);
    PlaySFX(SFX_SHARPEN);
    // LD_C(60);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(60);
    // depixel4(30, 10, 2, 0);
    // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_PULSE);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_PULSE, pixel4(30, 10, 2, 0));
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // LD_DE(SFX_THROW_BALL);
    // CALL(aPlaySFX);
    PlaySFX(SFX_THROW_BALL);
    // RET;
}

void MobileTradeAnim_06(void){
    // LD_C(40);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(40);
    // LD_A(0x1);
    // LD_addr_A(wcf64);
    wram->wcf64 = 0x1;
    // LD_DE(SFX_SHARPEN);
    // CALL(aPlaySFX);
    PlaySFX(SFX_SHARPEN);
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_07(void){
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames(80);
    // depixel4(30, 10, 2, 0);
    // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_PULSE);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_PULSE, pixel4(30, 10, 2, 0));
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // LD_DE(SFX_THROW_BALL);
    // CALL(aPlaySFX);
    PlaySFX(SFX_THROW_BALL);
    // RET;
}

void MobileTradeAnim_GetTrademon1(void){
    // LD_C(40);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(40);

    while(hram.hSCY != 0xf8) {
    // loop:
        // LDH_A_addr(hSCY);
        // CP_A(0xf8);
        // IF_Z goto done;
        // ADD_A(0x8);
        // LDH_addr_A(hSCY);
        hram.hSCY += 0x8;
        // LD_C(1);
        // CALL(aWaitMobileTradeSpriteAnims);
        WaitMobileTradeSpriteAnims(1);
        // goto loop;
    }

// done:
    // FARCALL(aDeinitializeAllSprites);
    DeinitializeAllSprites();
    // depixel4(9, 10, 2, 0);
    // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_PING);
    // CALL(aInitSpriteAnimStruct);
    InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_PING, pixel4(9, 10, 2, 0));
    // LD_DE(SFX_GLASS_TING_2);
    // CALL(aPlaySFX);
    PlaySFX(SFX_GLASS_TING_2);
    // CALL(aFunction108af4);
    Function108af4();
    // CALL(aMobileTradeAnim_Next);
    MobileTradeAnim_Next();
    // RET;
}

void MobileTradeAnim_GetTrademon2(void){
    // LD_C(20);
    // LD_HL(wBGPals2 + 1 * PALETTE_SIZE);
    // CALL(aFunction1082fa);
    Function1082fa((uint16_t*)(wram->wBGPals2 + 1 * PALETTE_SIZE), 20);
    // LD_DE(SFX_GIVE_TRADEMON);
    // CALL(aPlaySFX);
    PlaySFX(SFX_GIVE_TRADEMON);
    // LD_C(20);
    // LD_HL(wBGPals2 + 1 * PALETTE_SIZE);
    // CALL(aFunction1082fa);
    Function1082fa((uint16_t*)(wram->wBGPals2 + 1 * PALETTE_SIZE), 20);
    // CALL(aFunction108af4);
    Function108af4();

    while(hram.hSCY != 0x78) {
    // asm_1088ad:
        // LDH_A_addr(hSCY);
        // CP_A(0x78);
        // IF_Z goto asm_1088ee;
        // INC_A;
        // INC_A;
        // LDH_addr_A(hSCY);
        hram.hSCY += 2;
        // CP_A(0x30);
        // IF_Z goto asm_1088c5;
        if(hram.hSCY == 0x30) {
        // asm_1088c5:
            // depixel4(10, 11, 4, 0);
            // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_CABLE_BULGE);
            // CALL(aInitSpriteAnimStruct);
            InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_CABLE_BULGE, pixel4(10, 11, 4, 0));
            // goto asm_1088e7;
        }
        // CP_A(0x40);
        // IF_Z goto asm_1088dd;
        else if(hram.hSCY == 0x40) {
        // asm_1088dd:
            // CALL(aMobileTradeAnim_DeleteSprites);
            MobileTradeAnim_DeleteSprites();
            // LD_A(0x1);
            // CALL(aFunction108ad4);
            Function108ad4(0x1);
            // goto asm_1088e7;
        }
        // CP_A(0x68);
        // IF_Z goto asm_1088cf;
        else if(hram.hSCY == 0x68) {
        // asm_1088cf:
            // depixel4(10, 11, 4, 0);
            // LD_A(SPRITE_ANIM_INDEX_MOBILE_TRADE_CABLE_BULGE);
            // CALL(aInitSpriteAnimStruct);
            InitSpriteAnimStruct(SPRITE_ANIM_INDEX_MOBILE_TRADE_CABLE_BULGE, pixel4(10, 11, 4, 0));
            // XOR_A_A;
            // CALL(aFunction108ad4);
            Function108ad4(0);
            // goto asm_1088e7;
        }
        // goto asm_1088e7;

    asm_1088e7:
        // LD_C(1);
        // CALL(aWaitMobileTradeSpriteAnims);
        WaitMobileTradeSpriteAnims(1);
        // goto asm_1088ad;
    }

    while(hram.hSCX != 0xc) {
    // asm_1088ee:
        // LDH_A_addr(hSCX);
        // CP_A(0xc);
        // IF_Z goto asm_108906;
        // INC_A;
        // INC_A;
        // LDH_addr_A(hSCX);
        hram.hSCX += 2;
        // CP_A(-8);
        // IF_NZ goto asm_1088e7;
        if(hram.hSCX != (uint8_t)-8) 
            goto asm_1088e7;
        // CALL(aMobileTradeAnim_DeleteSprites);
        MobileTradeAnim_DeleteSprites();
        // LD_C(1);
        // CALL(aWaitMobileTradeSpriteAnims);
        WaitMobileTradeSpriteAnims(1);
        // goto asm_1088ee;
    }

// asm_108906:
    // CALL(aMobileTradeAnim_Next);
    MobileTradeAnim_Next();
    // RET;
}

void MobileTradeAnim_GetTrademon3(void){
    // LD_C(40);
    // LD_HL(wBGPals2 + PALETTE_SIZE * 6);
    uint16_t* hl = (uint16_t*)(wram->wBGPals2 + PALETTE_SIZE * 6);
    // CALL(aFunction1082f0);
    Function1082f0(hl, 40);
    // CALL(aFunction108af4);
    Function108af4();
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_0f(void){
    // LD_C(40);
    // CALL(aWaitMobileTradeSpriteAnims);
    WaitMobileTradeSpriteAnims(40);
    // FARCALL(aDeinitializeAllSprites);
    DeinitializeAllSprites();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aMobileTradeAnim_ClearTiles);
    MobileTradeAnim_ClearTiles();
    // CALL(aMobileTradeAnim_ClearBGMap);
    MobileTradeAnim_ClearBGMap();
    // CALL(aEnableLCD);
    EnableLCD();
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void MobileTradeAnim_FadeToBlack(void){
    uint8_t bgp;
    while((bgp = gb_read(rBGP), bgp != 0)) {
    // loop:
        // LDH_A_addr(rBGP);
        // AND_A_A;
        // IF_Z goto blank;
        // SLA_A;
        // SLA_A;
        // CALL(aDmgToCgbBGPals);
        DmgToCgbBGPals(bgp << 2);
        // CALL(aDmgToCgbObjPal0);
        DmgToCgbObjPal0(bgp << 2);
        // LD_C(4);
        // CALL(aDelayFrames);
        DelayFrames(4);
        // goto loop;
    }

// blank:
    // XOR_A_A;
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0);
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0(0);
    // CALL(aGetMobileTradeAnimByte);
    GetMobileTradeAnimByte();
    // RET;
}

void Function10895e(void){
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x30);
    // JR(masm_108966);
    return asm_108966(vram->vTiles0 + LEN_2BPP_TILE * 0x30);
}

void Function108963(void){
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    return asm_108966(vram->vTiles2 + LEN_2BPP_TILE * 0x31);
}

void asm_108966(const uint8_t* de){
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_HL(vTiles2);
    // LD_BC((BANK(aTradeGameBoyLZ) << 8) | 0x31);
    // CALL(aRequest2bpp);
    CopyBytes(vram->vTiles2, de, 0x31 * LEN_2BPP_TILE);
    // CALL(aWaitTop);
    WaitTop();
    // CALL(aMobileTradeAnim_ClearTilemap);
    MobileTradeAnim_ClearTilemap();
    // hlcoord(7, 2, wTilemap);
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram.hGraphicStartTile = 0;
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger(coord(7, 2, wram->wTilemap), 7, 7);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // RET;

}

void Function10898a(species_t species, uint16_t dvs){
    // LD_DE(vTiles2);
    // CALL(aMobileTradeAnim_GetFrontpic);
    MobileTradeAnim_GetFrontpic(vram->vTiles2, species, dvs);
    // CALL(aWaitTop);
    WaitTop();
    // CALL(aMobileTradeAnim_ClearTilemap);
    MobileTradeAnim_ClearTilemap();
    // hlcoord(7, 2, wTilemap);
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram.hGraphicStartTile = 0;
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger(coord(7, 2, wram->wTilemap), 7, 7);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // RET;
}

void MobileTradeAnim_DisplayMonToBeSent(void){
    // LD_DE(wPlayerTrademonSpecies);
    // LD_A_de;
    species_t species = wram->wPlayerTrademon.species;
    // CP_A(EGG);
    // JR_Z (mMobileTradeAnim_DisplayEggData);
    if(species == EGG)
        return MobileTradeAnim_DisplayEggData();
    // CALL(aMobileTradeAnim_LoadMonTemplate);
    MobileTradeAnim_LoadMonTemplate();
    // LD_DE(wPlayerTrademonSpecies);
    // CALL(aMobileTradeAnim_MonDisplay_PrintSpeciesNumber);
    MobileTradeAnim_MonDisplay_PrintSpeciesNumber(species);
    // LD_DE(wPlayerTrademonSpeciesName);
    // CALL(aMobileTradeAnim_MonDisplay_PrintSpeciesName);
    MobileTradeAnim_MonDisplay_PrintSpeciesName(wram->wPlayerTrademon.speciesName);
    // LD_A_addr(wPlayerTrademonCaughtData);
    // LD_DE(wPlayerTrademonOTName);
    // CALL(aMobileTradeAnim_MonDisplay_PrintOTNameAndGender);
    MobileTradeAnim_MonDisplay_PrintOTNameAndGender(wram->wPlayerTrademon.otName, wram->wPlayerTrademon.caughtData);
    // LD_DE(wPlayerTrademonID);
    // CALL(aMobileTradeAnim_MonDisplay_PrintIDNumber);
    MobileTradeAnim_MonDisplay_PrintIDNumber(&wram->wPlayerTrademon.id);
    // CALL(aMobileTradeAnim_MonDisplay_UpdateBGMap);
    MobileTradeAnim_MonDisplay_UpdateBGMap();
    // RET;
}

void MobileTradeAnim_DisplayReceivedMon(void){
    // LD_DE(wOTTrademonSpecies);
    // LD_A_de;
    species_t species = wram->wOTTrademon.species;
    // CP_A(EGG);
    // JR_Z (mMobileTradeAnim_DisplayEggData);
    if(species == EGG)
        return MobileTradeAnim_DisplayEggData();
    // CALL(aMobileTradeAnim_LoadMonTemplate);
    MobileTradeAnim_LoadMonTemplate();
    // LD_DE(wOTTrademonSpecies);
    // CALL(aMobileTradeAnim_MonDisplay_PrintSpeciesNumber);
    MobileTradeAnim_MonDisplay_PrintSpeciesNumber(species);
    // LD_DE(wOTTrademonSpeciesName);
    // CALL(aMobileTradeAnim_MonDisplay_PrintSpeciesName);
    MobileTradeAnim_MonDisplay_PrintSpeciesName(wram->wOTTrademon.speciesName);
    // LD_A_addr(wOTTrademonCaughtData);
    // LD_DE(wOTTrademonOTName);
    // CALL(aMobileTradeAnim_MonDisplay_PrintOTNameAndGender);
    MobileTradeAnim_MonDisplay_PrintOTNameAndGender(wram->wOTTrademon.otName, wram->wOTTrademon.caughtData);
    // LD_DE(wOTTrademonID);
    // CALL(aMobileTradeAnim_MonDisplay_PrintIDNumber);
    MobileTradeAnim_MonDisplay_PrintIDNumber(&wram->wOTTrademon.id);
    // CALL(aMobileTradeAnim_MonDisplay_UpdateBGMap);
    MobileTradeAnim_MonDisplay_UpdateBGMap();
    // RET;
}

void MobileTradeAnim_DisplayEggData(void){
    static const char EggTemplate[] =
                "" //db ['"タマゴ"'];
        t_next  "" //next ['"おや/？？？？？"']
        t_next  "" //next ['"<ID>№<DOT>？？？？？"']
                "";//db ['"@"'];
    // CALL(aWaitTop);
    WaitTop();
    // CALL(aMobileTradeAnim_ClearTilemap);
    MobileTradeAnim_ClearTilemap();
    // LD_A(HIGH(vBGMap1));
    // LDH_addr_A(hBGMapAddress + 1);
    hram.hBGMapAddress = (hram.hBGMapAddress & 0xff) | (vBGMap1 & 0xff00);
    // hlcoord(5, 0, wTilemap);
    // LD_B(6);
    // LD_C(9);
    // CALL(aTextbox);
    Textbox(coord(3, 0, wram->wTilemap), 6, 13);
    // hlcoord(6, 2, wTilemap);
    // LD_DE(mMobileTradeAnim_DisplayEggData_EggTemplate);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(EggTemplate), coord(4, 2, wram->wTilemap));
    // CALL(aMobileTradeAnim_MonDisplay_UpdateBGMap);
    MobileTradeAnim_MonDisplay_UpdateBGMap();
    // RET;
}

void Function108a33(void){
    static const char OddEgg[] = "";
    //db ['"なぞのタマゴ@"'];
    // CALL(aWaitTop);
    WaitTop();
    // CALL(aMobileTradeAnim_ClearTilemap);
    MobileTradeAnim_ClearTilemap();
    // LD_A(HIGH(vBGMap1));
    // LDH_addr_A(hBGMapAddress + 1);
    hram.hBGMapAddress = (hram.hBGMapAddress & 0xff) | (vBGMap1 & 0xff00);
    // hlcoord(5, 0, wTilemap);
    // LD_B(6);
    // LD_C(9);
    // CALL(aTextbox);
    Textbox(coord(4, 0, wram->wTilemap), 6, 10);
    // hlcoord(7, 4, wTilemap);
    // LD_DE(mFunction108a33_OddEgg);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(OddEgg), coord(6, 4, wram->wTilemap));
    // CALL(aMobileTradeAnim_MonDisplay_UpdateBGMap);
    MobileTradeAnim_MonDisplay_UpdateBGMap();
    // RET;
}

void MobileTradeAnim_LoadMonTemplate(void){
    static const char MonTemplate[] = 
                "─ №<DOT>"  //db ['"─\u3000№<DOT>"'];
        t_next  ""          //next ['""']
        t_next  ""          //next ['"おや／"']
        t_next  "<ID>№<DOT>"//next ['"<ID>№<DOT>"']
                "";         //db ['"@"'];
    // CALL(aWaitTop);
    WaitTop();
    // CALL(aMobileTradeAnim_ClearTilemap);
    MobileTradeAnim_ClearTilemap();
    // LD_A(HIGH(vBGMap1));
    // LDH_addr_A(hBGMapAddress + 1);
    hram.hBGMapAddress = (hram.hBGMapAddress & 0xff) | (vBGMap1 & 0xff00);
    // hlcoord(4, 0, wTilemap);
    // LD_B(6);
    // LD_C(10);
    // CALL(aTextbox);
    Textbox(coord(3, 0, wram->wTilemap), 6, 13);
    // hlcoord(5, 0, wTilemap);
    // LD_DE(mMobileTradeAnim_LoadMonTemplate_MonTemplate);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MonTemplate), coord(4, 0, wram->wTilemap));
    // RET;
}

void MobileTradeAnim_MonDisplay_UpdateBGMap(void){
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aWaitTop);
    WaitTop();
    // LD_A(HIGH(vBGMap0));
    // LDH_addr_A(hBGMapAddress + 1);
    hram.hBGMapAddress = (hram.hBGMapAddress & 0xff) | (vBGMap0 & 0xff00);
    // RET;
}

void MobileTradeAnim_MonDisplay_PrintSpeciesNumber(species_t species){
    // hlcoord(9, 0, wTilemap);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum(coord(10, 0, wram->wTilemap), &species, PRINTNUM_LEADINGZEROS | 1, 3);
    // RET;
}

void MobileTradeAnim_MonDisplay_PrintSpeciesName(uint8_t* de){
    // hlcoord(5, 2, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(de, coord(4, 2, wram->wTilemap));
    // RET;
}

void MobileTradeAnim_MonDisplay_PrintOTNameAndGender(uint8_t* de, uint8_t a){
    static const uint8_t GenderChars[] = {
        CHAR_SPACE, //db ['" "'];
        CHAR_MALE_ICON, //db ['"♂"'];
        CHAR_FEMALE_ICON, //db ['"♀"'];
    };
    // CP_A(0x3);
    // IF_C goto got_gender;
    if(a >= 0x3) {
        // XOR_A_A;
        a = 0;
    }

// got_gender:
    // PUSH_AF;
    // hlcoord(8, 4, wTilemap);
    // CALL(aPlaceString);
    struct TextPrintState st = {.de = de, .hl = coord(7, 4, wram->wTilemap)};
    PlaceString(&st, st.hl);
    // INC_BC;
    st.bc++;
    // POP_AF;
    // LD_HL(mMobileTradeAnim_MonDisplay_PrintOTNameAndGender_GenderChars);
    // LD_D(0);
    // LD_E_A;
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_bc_A;
    *st.bc = GenderChars[a];
    // RET;
}

void MobileTradeAnim_MonDisplay_PrintIDNumber(const void* de){
    // hlcoord(8, 6, wTilemap);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum(coord(7, 6, wram->wTilemap), de, PRINTNUM_LEADINGZEROS | 2, 5);
    // RET;
}

void MobileTradeAnim_ClearTilemap(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // RET;
}

void Function108ad4(uint8_t a){
    // AND_A_A;
    // IF_Z goto asm_108adc;
    // LD_DE(mMobileCable2GFX);
    // goto asm_108adf;

// asm_108adc:
    // LD_DE(mMobileCable1GFX);

// asm_108adf:
    const char* path = (a == 0)? MobileCable1GFX: MobileCable2GFX;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x4a);
    // LD_BC((BANK(aMobileCable1GFX) << 8) | 16);  // aka BANK(MobileCable2GFX)
    // CALL(aGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles5 + LEN_2BPP_TILE * 0x4a, path, 0, 16);
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // RET;
}

void Function108af4(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wcf65);
    // AND_A(0x1);
    // IF_Z goto copy_MobileTradeOB1Palettes;
    if((wram->wcf65 & 0x1)) {
        // LD_HL(mMobileTradeOB2Palettes);
        // LD_DE(wOBPals1);
        // LD_BC(8 * PALETTE_SIZE);
        // CALL(aCopyBytes);
        LoadPaletteAssetColorsToBuffer(wram->wOBPals1, 8 * PALETTE_SIZE, MobileTradeOB2Palettes, 0, 8 * NUM_PAL_COLORS);
        // LD_HL(mMobileTradeOB2Palettes);
        // LD_DE(wOBPals2);
        // LD_BC(8 * PALETTE_SIZE);
        // CALL(aCopyBytes);
        LoadPaletteAssetColorsToBuffer(wram->wOBPals2, 8 * PALETTE_SIZE, MobileTradeOB2Palettes, 0, 8 * NUM_PAL_COLORS);
        // goto done_copy;
    }
    else {
    // copy_MobileTradeOB1Palettes:
        // LD_HL(mMobileTradeOB1Palettes);
        // LD_DE(wOBPals1);
        // LD_BC(8 * PALETTE_SIZE);
        // CALL(aCopyBytes);
        LoadPaletteAssetColorsToBuffer(wram->wOBPals1, 8 * PALETTE_SIZE, MobileTradeOB1Palettes, 0, 8 * NUM_PAL_COLORS);
        // LD_HL(mMobileTradeOB1Palettes);
        // LD_DE(wOBPals2);
        // LD_BC(8 * PALETTE_SIZE);
        // CALL(aCopyBytes);
        LoadPaletteAssetColorsToBuffer(wram->wOBPals2, 8 * PALETTE_SIZE, MobileTradeOB1Palettes, 0, 8 * NUM_PAL_COLORS);
    }

// done_copy:
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0(0b11100100);
    // LD_A(0b11100100);  // 3,2,1,0
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0b11100100);
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void Function108b45(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_DE(PALRGB_WHITE);
    // LD_HL(wBGPals1);
    // LD_A_E;
    // LD_hli_A;
    wram->wBGPals1[0] = LOW(PALRGB_WHITE);
    // LD_D_A; // Shouldn't this be ld a, d
    // LD_hli_A;
    wram->wBGPals1[1] = HIGH(PALRGB_WHITE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void Function108b5a(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_DE((1 << 0) * 18 + (1 << 5) * 31 + (1 << 10) * 15);
    uint16_t de = (1 << 0) * 18 + (1 << 5) * 31 + (1 << 10) * 15;
    // LD_HL(wBGPals2 + 4 * PALETTE_SIZE);
    uint8_t* hl = wram->wBGPals2 + 4 * PALETTE_SIZE;
    // LD_C(0x10);
    uint8_t c = 0x10;

    do {
    // loop:
        // LD_A_E;
        // LD_hli_A;
        *(hl++) = LOW(de);
        // LD_A_D;
        // LD_hli_A;
        *(hl++) = HIGH(de);
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram.hCGBPalUpdate = TRUE;
    // RET;
}

void Function108b78(uint16_t* hl, uint8_t c){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_A_C;
    // AND_A(0x2);
    // IF_Z goto Orange;
    uint16_t de;
    if((c & 0x2) == 0) {
    // Orange:
        // LD_DE((1 << 0) * 31 + (1 << 5) * 15 + (1 << 10) * 1);
        de = (1 << 0) * 31 + (1 << 5) * 15 + (1 << 10) * 1;
    }
    else {
        // LD_DE(PALRGB_WHITE);
        de = PALRGB_WHITE;
        // goto load_pal;
    }

// load_pal:
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hld_A;
    *hl = de;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram.hCGBPalUpdate = TRUE;
    // RET;
}

void Palette_108b98(void){
//  removed
}

void Function108b98(void){
    // LD_D_A;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wcf65);
    // AND_A(0x1);
    // XOR_A_D;
    // IF_Z goto asm_108bad;
    // LD_HL(mPalette_108b98 + 1 * PALETTE_SIZE);
    // goto asm_108bb0;

// asm_108bad:
    // LD_HL(mPalette_108b98);

// asm_108bb0:
    // LD_DE(wBGPals1 + 7 * PALETTE_SIZE);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void MobileTradeAnim_DeleteSprites(void){
    // FARCALL(aDeinitializeAllSprites);
    DeinitializeAllSprites();
    // CALL(aClearSprites);
    ClearSprites();
    // RET;
}

void MobileTradeAnim_AnimateSentPulse(struct SpriteAnim* bc){
    // LD_A_addr(wcf64);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcf64 == 0)
        return;
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(-1 * 8 - 6);
    // IF_Z goto delete;
    if(bc->yCoord == (uint8_t)(-1 * 8 - 6)) {
    // delete:
        // FARCALL(aDeinitializeSprite);
        DeinitializeSprite(bc);
        // RET;
        return;
    }
    // SUB_A(1 * 8);
    // LD_hl_A;
    bc->yCoord -= 1 * 8;
    // RET;
}

void MobileTradeAnim_AnimateOTPulse(struct SpriteAnim* bc){
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(9 * 8 + 2);
    // RET_Z ;
    if(bc->yCoord == 9 * 8 + 2)
        return;
    // ADD_A(1 * 8);
    // LD_hl_A;
    bc->yCoord += 1 * 8;
    // RET;
}

void Function108bec(void){
    static const txt_cmd_s MobilePlayerWillTradeMonText[] = {
        text_far(v_MobilePlayerWillTradeMonText)
        text_end
    };
    static const txt_cmd_s MobileForPartnersMonText[] = {
        text_far(v_MobileForPartnersMonText)
        text_end
    };
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // LD_HL(mFunction108bec_MobilePlayerWillTradeMonText);
    // CALL(aPrintText);
    PrintText(MobilePlayerWillTradeMonText);
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames(80);
    // LD_HL(mFunction108bec_MobileForPartnersMonText);
    // CALL(aPrintText);
    PrintText(MobileForPartnersMonText);
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames(80);
    // RET;

// MobilePlayersMonTradeText:
//   //  unreferenced
    //text_far ['_MobilePlayersMonTradeText']
    //text_end ['?']
}

void Function108c16(void){
    static const txt_cmd_s MobileTakeGoodCareOfMonText[] = {
        text_far(v_MobileTakeGoodCareOfMonText)
        text_end
    };
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // LD_HL(mFunction108c16_MobileTakeGoodCareOfMonText);
    // CALL(aPrintText);
    PrintText(MobileTakeGoodCareOfMonText);
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames(80);
    // RET;
}

void Function108c2b(void){
    static const txt_cmd_s MobilePlayersMonTrade2Text[] = {
        text_far(v_MobilePlayersMonTrade2Text)
        text_end
    };
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // LD_HL(mFunction108c2b_MobilePlayersMonTrade2Text);
    // CALL(aPrintText);
    PrintText(MobilePlayersMonTrade2Text);
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames(80);
    // RET;
}

void Function108c40(void){
    static const txt_cmd_s MobileTakeGoodCareOfText[] = {
        text_far(v_MobileTakeGoodCareOfText)
        text_end
    };
    static const txt_cmd_s MobileTradeCameBackText[] = {
        text_far(v_MobileTradeCameBackText)
        text_end
    };
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram.hWY = 0x90;
    // LD_A_addr(wcf65);
    // AND_A(0b10000000);
    // IF_Z goto Getmon;
    if(wram->wcf65 & 0b10000000) {
        // LD_HL(mFunction108c40_MobileTradeCameBackText);
        // CALL(aPrintText);
        PrintText(MobileTradeCameBackText);
        // LD_C(80);
        // CALL(aDelayFrames);
        DelayFrames(80);
        // RET;
    }
    else {
    // Getmon:
        // LD_HL(mFunction108c40_MobileTakeGoodCareOfText);
        // CALL(aPrintText);
        PrintText(MobileTakeGoodCareOfText);
        // LD_C(80);
        // CALL(aDelayFrames);
        DelayFrames(80);
        // RET;
    }
}

void Function108c6d(void){
    // LD_HL(mMobileTradeTilemapLZ);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aDecompress);
    LoadAssetToBuffer(bgcoord(0, 0, vram->vBGMap0), sizeof(vram->vBGMap0), MobileTradeTilemapLZ);
    // LD_HL(mMobileTradeTilemapLZ);
    // debgcoord(0, 0, vBGMap1);
    // CALL(aDecompress);
    LoadAssetToBuffer(bgcoord(0, 0, vram->vBGMap1), sizeof(vram->vBGMap1), MobileTradeTilemapLZ);
    // RET;
}

void Function108c80(void){
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_HL(mMobileTradeAttrmapLZ);
    // debgcoord(0, 0, vBGMap0);
    // CALL(aDecompress);
    LoadAssetToBuffer(bgcoord(0, 0, vram->vBGMap2), sizeof(vram->vBGMap2), MobileTradeAttrmapLZ);
    // LD_HL(mMobileTradeAttrmapLZ);
    // debgcoord(0, 0, vBGMap1);
    // CALL(aDecompress);
    LoadAssetToBuffer(bgcoord(0, 0, vram->vBGMap3), sizeof(vram->vBGMap3), MobileTradeAttrmapLZ);
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // RET;
}

void DebugMobileTrade(void){
//  //  unreferenced
//  localization error: NAME_LENGTH (11) should be NAME_LENGTH_JAPANESE (6) here

    // LD_HL(mDebugMobileTrade_DebugTradeData);
    // LD_A_hli;
    // LD_addr_A(wPlayerTrademonSpecies);
    wram->wPlayerTrademon.species = VENUSAUR;

    // LD_DE(wPlayerTrademonSenderName);
    // LD_C(NAME_LENGTH);

// your_name_loop:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto your_name_loop;
    U82CA(wram->wPlayerTrademon.senderName, "GAMEFREAK");

    // LD_DE(wPlayerTrademonID);
    // LD_C(2);

// your_id_loop:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto your_id_loop;
    wram->wPlayerTrademon.id = 0x0123;

    // LD_DE(wPlayerTrademonOTName);
    // LD_C(NAME_LENGTH);

// your_ot_loop:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto your_ot_loop;
    U82CA(wram->wPlayerTrademon.otName, "KABIN");

    // LD_A_hli;
    // LD_addr_A(wOTTrademonSpecies);
    wram->wOTTrademon.species = CHARIZARD;

    // LD_DE(wOTTrademonSenderName);
    // LD_C(NAME_LENGTH);

// their_name_loop:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto their_name_loop;
    U82CA(wram->wOTTrademon.senderName, "CREATURE");

    // LD_DE(wOTTrademonID);
    // LD_C(2);

// their_id_loop:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto their_id_loop;
    wram->wOTTrademon.id = 0x0456;

    // LD_DE(wOTTrademonOTName);
    // LD_C(NAME_LENGTH);

// their_ot_loop:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto their_ot_loop;
    U82CA(wram->wOTTrademon.otName, "MATSUMIYA");

    // RET;


// DebugTradeData:
    //db ['VENUSAUR'];
    //db ['"ゲーフり@@"'];
    //dw ['0x0123'];
    //db ['"かびーん@@"'];
    //db ['CHARIZARD'];
    //db ['"クりーチャ@"'];
    //dw ['0x0456'];
    //db ['"マツミヤ@@"'];
}

void LoadMobileAdapterPalette(void){
    // LD_A_addr(wc74e);
    // AND_A(0x7f);
    uint8_t a = wram->wc74e[0] & 0x7f;
    // CP_A(0x8);  // CONST: Amount of mobile adapters
    // IF_C goto asm_108d12;
    if(a >= 0x8) {
        // LD_A(0x7);
        a = 0x7;
    }

// asm_108d12:
    // LD_BC(1 * PALETTE_SIZE);
    // LD_HL(mMobileAdapterPalettes);
    // CALL(aAddNTimes);
    // LD_A(BANK(wBGPals1));
    // LD_DE(wBGPals1 + 4 * PALETTE_SIZE);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1 + 4 * PALETTE_SIZE,
        MobileAdapterPalettes + a * PALETTE_SIZE,
        1 * PALETTE_SIZE);
    // RET;
}

const char MobileTradeSpritesGFX[] = "gfx/mobile/mobile_trade_sprites.png";
const char MobileTradeGFX[] = "gfx/mobile/mobile_trade.png";
const char MobileTradeTilemapLZ[] = "gfx/mobile/mobile_trade.tilemap";
const char MobileTradeAttrmapLZ[] = "gfx/mobile/mobile_trade.attrmap";

void UnusedMobilePulsePalettes(void){
//  //  unreferenced
// INCLUDE "gfx/mobile/unused_mobile_pulses.pal"
}

const char MobileTradeBGPalettes[] = "gfx/mobile/mobile_trade_bg.pal";
const char MobileTradeOB1Palettes[] = "gfx/mobile/mobile_trade_ob1.pal";
const char MobileTradeOB2Palettes[] = "gfx/mobile/mobile_trade_ob2.pal";
const char MobileCable1GFX[] = "gfx/mobile/mobile_cable_1.png";
const char MobileCable2GFX[] = "gfx/mobile/mobile_cable_2.png";
const uint16_t MobileAdapterPalettes[] = {
    rgb(18,31,15), rgb( 4,13,31), rgb( 0, 0,31), rgb( 0, 0, 0), // blue
	rgb(18,31,15), rgb(31,31, 0), rgb(31,15, 0), rgb( 0, 0, 0), // yellow
	rgb(18,31,15), rgb( 9,24, 0), rgb( 2,16, 0), rgb( 0, 0, 0), // green
	rgb(18,31,15), rgb(31, 7, 9), rgb(18, 0, 1), rgb( 0, 0, 0), // red
	rgb(18,31,15), rgb(28, 5,31), rgb(17, 0,17), rgb( 0, 0, 0), // purple
	rgb(18,31,15), rgb( 9, 9, 9), rgb( 4, 4, 4), rgb( 0, 0, 0), // black
	rgb(18,31,15), rgb(31,13,21), rgb(27, 7,12), rgb( 0, 0, 0), // pink
	rgb(18,31,15), rgb(21,20,20), rgb(14,14,31), rgb( 0, 0, 0), // gray
};
