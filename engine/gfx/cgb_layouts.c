#include "../../constants.h"
#include "cgb_layouts.h"
#include "color.h"
#include "../../home/copy.h"

//  Replaces the functionality of sgb.asm to work with CGB hardware.

void CheckCGB(void){
    LDH_A_addr(hCGB);
    AND_A_A;
    RET;

}

bool CheckCGB_Conv(void) {
    return hram->hCGB != 0;
}

void LoadSGBLayoutCGB(void){
    LD_A_B;
    CP_A(SCGB_DEFAULT);
    IF_NZ goto not_default;
    LD_A_addr(wDefaultSGBLayout);

not_default:
    CP_A(SCGB_PARTY_MENU_HP_BARS);
    JP_Z (mCGB_ApplyPartyMenuHPPals);
    CALL(aResetBGPals);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    LD_DE(mCGBLayoutJumptable);
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(mLoadSGBLayoutCGB_done);
    PUSH_DE;
    JP_hl;

done:
    RET;

}

void (*const CGBLayoutJumptable[])(void) = {
    v_CGB_BattleGrayscale,
    v_CGB_BattleColors,
    v_CGB_PokegearPals,
    v_CGB_StatsScreenHPPals,
    v_CGB_Pokedex,
    v_CGB_SlotMachine,
    v_CGB_BetaTitleScreen,
    v_CGB_GSIntro,
    v_CGB_Diploma,
    v_CGB_MapPals,
    v_CGB_PartyMenu,
    v_CGB_Evolution,
    v_CGB_GSTitleScreen,
    v_CGB_Unused0D,
    v_CGB_MoveList,
    v_CGB_BetaPikachuMinigame,
    v_CGB_PokedexSearchOption,
    v_CGB_BetaPoker,
    v_CGB_Pokepic,
    v_CGB_MagnetTrain,
    v_CGB_PackPals,
    v_CGB_TrainerCard,
    v_CGB_PokedexUnownMode,
    v_CGB_BillsPC,
    v_CGB_UnownPuzzle,
    v_CGB_GamefreakLogo,
    v_CGB_PlayerOrMonFrontpicPals,
    v_CGB_TradeTube,
    v_CGB_TrainerOrMonFrontpicPals,
    v_CGB_MysteryGift,
    v_CGB_Unused1E,
    //assert_table_length ['NUM_SCGB_LAYOUTS']
};

static_assert(lengthof(CGBLayoutJumptable) == NUM_SCGB_LAYOUTS);

void LoadSGBLayoutCGB_Conv(uint8_t b){
    // LD_A_B;
    // CP_A(SCGB_DEFAULT);
    // IF_NZ goto not_default;
    // LD_A_addr(wDefaultSGBLayout);
    if(b == SCGB_DEFAULT)
        b = wram->wDefaultSGBLayout;

// not_default:
    // CP_A(SCGB_PARTY_MENU_HP_BARS);
    // JP_Z (mCGB_ApplyPartyMenuHPPals);
    if(b == SCGB_PARTY_MENU_HP_BARS)
        return CGB_ApplyPartyMenuHPPals_Conv();
    // CALL(aResetBGPals);
    ResetBGPals_Conv();
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // LD_DE(mCGBLayoutJumptable);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(mLoadSGBLayoutCGB_done);
    // PUSH_DE;
    // JP_hl;
    CGBLayoutJumptable[b]();

// done:
    // RET;

}

void v_CGB_BattleGrayscale(void){
    LD_HL(mPalPacket_BattleGrayscale + 1);
    LD_DE(wBGPals1);
    LD_C(4);
    CALL(aCopyPalettes);
    LD_HL(mPalPacket_BattleGrayscale + 1);
    LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BATTLE_BG_EXP);
    LD_C(4);
    CALL(aCopyPalettes);
    LD_HL(mPalPacket_BattleGrayscale + 1);
    LD_DE(wOBPals1);
    LD_C(2);
    CALL(aCopyPalettes);
    JR(mv_CGB_FinishBattleScreenLayout);

}

void v_CGB_BattleColors(void){
    LD_DE(wBGPals1);
    CALL(aGetBattlemonBackpicPalettePointer);
    PUSH_HL;
    CALL(aLoadPalette_White_Col1_Col2_Black);  // PAL_BATTLE_BG_PLAYER
    CALL(aGetEnemyFrontpicPalettePointer);
    PUSH_HL;
    CALL(aLoadPalette_White_Col1_Col2_Black);  // PAL_BATTLE_BG_ENEMY
    LD_A_addr(wEnemyHPPal);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_BC(mHPBarPals);
    ADD_HL_BC;
    CALL(aLoadPalette_White_Col1_Col2_Black);  // PAL_BATTLE_BG_ENEMY_HP
    LD_A_addr(wPlayerHPPal);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_BC(mHPBarPals);
    ADD_HL_BC;
    CALL(aLoadPalette_White_Col1_Col2_Black);  // PAL_BATTLE_BG_PLAYER_HP
    LD_HL(mExpBarPalette);
    CALL(aLoadPalette_White_Col1_Col2_Black);  // PAL_BATTLE_BG_EXP
    LD_DE(wOBPals1);
    POP_HL;
    CALL(aLoadPalette_White_Col1_Col2_Black);  // PAL_BATTLE_OB_ENEMY
    POP_HL;
    CALL(aLoadPalette_White_Col1_Col2_Black);  // PAL_BATTLE_OB_PLAYER
    LD_A(SCGB_BATTLE_COLORS);
    LD_addr_A(wDefaultSGBLayout);
    CALL(aApplyPals);
    return v_CGB_FinishBattleScreenLayout();
}

void v_CGB_FinishBattleScreenLayout(void){
    CALL(aInitPartyMenuBGPal7);
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    LD_A(PAL_BATTLE_BG_ENEMY_HP);
    CALL(aByteFill);
    hlcoord(0, 4, wAttrmap);
    LD_BC((8 << 8) | 10);
    LD_A(PAL_BATTLE_BG_PLAYER);
    CALL(aFillBoxCGB);
    hlcoord(10, 0, wAttrmap);
    LD_BC((7 << 8) | 10);
    LD_A(PAL_BATTLE_BG_ENEMY);
    CALL(aFillBoxCGB);
    hlcoord(0, 0, wAttrmap);
    LD_BC((4 << 8) | 10);
    LD_A(PAL_BATTLE_BG_ENEMY_HP);
    CALL(aFillBoxCGB);
    hlcoord(10, 7, wAttrmap);
    LD_BC((5 << 8) | 10);
    LD_A(PAL_BATTLE_BG_PLAYER_HP);
    CALL(aFillBoxCGB);
    hlcoord(10, 11, wAttrmap);
    LD_BC((1 << 8) | 9);
    LD_A(PAL_BATTLE_BG_EXP);
    CALL(aFillBoxCGB);
    hlcoord(0, 12, wAttrmap);
    LD_BC(6 * SCREEN_WIDTH);
    LD_A(PAL_BATTLE_BG_TEXT);
    CALL(aByteFill);
    LD_HL(mBattleObjectPals);
    LD_DE(wOBPals1 + PALETTE_SIZE * PAL_BATTLE_OB_GRAY);
    LD_BC(6 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);
    CALL(aApplyAttrmap);
    RET;

}

void InitPartyMenuBGPal7(void){
    FARCALL(aFunction100dc0);
    return Mobile_InitPartyMenuBGPal7();
}

void Mobile_InitPartyMenuBGPal7(void){
    LD_HL(mPartyMenuBGPalette);
    IF_NC goto not_mobile;
    LD_HL(mPartyMenuBGMobilePalette);

not_mobile:
    LD_DE(wBGPals1 + PALETTE_SIZE * 7);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    RET;

}

void InitPartyMenuBGPal0(void){
    FARCALL(aFunction100dc0);
    LD_HL(mPartyMenuBGPalette);
    IF_NC goto not_mobile;
    LD_HL(mPartyMenuBGMobilePalette);

not_mobile:
    LD_DE(wBGPals1 + PALETTE_SIZE * 0);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    RET;

}

void v_CGB_PokegearPals(void){
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto male;
    LD_HL(mFemalePokegearPals);
    goto got_pals;


male:
    LD_HL(mMalePokegearPals);

got_pals:
    LD_DE(wBGPals1);
    LD_BC(6 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_StatsScreenHPPals(void){
    uint16_t palbuf[3 * NUM_PAL_COLORS];
    // LD_DE(wBGPals1);
    uint16_t* de = (uint16_t*)((uint8_t*)wram + offsetof(struct wram_s, wBGPals1)); // Won't let me take pointer of packed wBGPals1, so I'm doing this ugly shit instead.
                                                                                    // Look what you made me do clang... Shame on you.
    // LD_A_addr(wCurHPPal);
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_BC(mHPBarPals);
    LoadPaletteAssetColorsToArray(palbuf, HPBarPals, wram->wCurHPPal << 1, 2);
    // ADD_HL_BC;
    // CALL(aLoadPalette_White_Col1_Col2_Black);  // hp palette
    de = LoadPalette_White_Col1_Col2_Black_Conv(de, palbuf);
    // LD_A_addr(wCurPartySpecies);
    // LD_BC(wTempMonDVs);
    // CALL(aGetPlayerOrMonPalettePointer);
    GetPlayerOrMonPalettePointer_Conv(palbuf, wram->wCurSpecies, wram->wTempMon.mon.DVs);
    // CALL(aLoadPalette_White_Col1_Col2_Black);  // mon palette
    de = LoadPalette_White_Col1_Col2_Black_Conv(de, palbuf);
    // LD_HL(mExpBarPalette);
    LoadPaletteAssetColorsToArray(palbuf, ExpBarPalette, 0, 2);
    // CALL(aLoadPalette_White_Col1_Col2_Black);  // exp palette
    de = LoadPalette_White_Col1_Col2_Black_Conv(de, palbuf);
    // LD_HL(mStatsScreenPagePals);
    // LD_DE(wBGPals1 + PALETTE_SIZE * 3);
    // LD_BC(3 * PALETTE_SIZE);  // pink, green, and blue page palettes
    // LD_A(BANK(wBGPals1));
    // CALL(aFarCopyWRAM);
    LoadPaletteAssetColorsToArray(palbuf, StatsScreenPagePals, 0, 3 * NUM_PAL_COLORS);
    CopyBytes_Conv2(wram->wBGPals1 + PALETTE_SIZE * 3, palbuf, 3 * PALETTE_SIZE);
    // CALL(aWipeAttrmap);
    WipeAttrmap();

    // hlcoord(0, 0, wAttrmap);
    // LD_BC((8 << 8) | SCREEN_WIDTH);
    // LD_A(0x1);  // mon palette
    // CALL(aFillBoxCGB);
    FillBoxCGB_Conv(coord(0, 0, wram->wAttrmap), 8, SCREEN_WIDTH, 0x1);

    // hlcoord(10, 16, wAttrmap);
    // LD_BC(10);
    // LD_A(0x2);  // exp palette
    // CALL(aByteFill);
    ByteFill_Conv2(coord(10, 16, wram->wAttrmap), 10, 0x2);

    // hlcoord(13, 5, wAttrmap);
    // LD_BC((2 << 8) | 2);
    // LD_A(0x3);  // pink page palette
    // CALL(aFillBoxCGB);
    FillBoxCGB_Conv(coord(13, 5, wram->wAttrmap), 2, 2, 0x3);

    // hlcoord(15, 5, wAttrmap);
    // LD_BC((2 << 8) | 2);
    // LD_A(0x4);  // green page palette
    // CALL(aFillBoxCGB);
    FillBoxCGB_Conv(coord(15, 5, wram->wAttrmap), 2, 2, 0x4);

    // hlcoord(17, 5, wAttrmap);
    // LD_BC((2 << 8) | 2);
    // LD_A(0x5);  // blue page palette
    // CALL(aFillBoxCGB);
    FillBoxCGB_Conv(coord(17, 5, wram->wAttrmap), 2, 2, 0x5);

    // CALL(aApplyAttrmap);
    ApplyAttrmap_Conv();
    // CALL(aApplyPals);
    ApplyPals_Conv();
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;
}

// void StatsScreenPagePals(void){
// INCLUDE "gfx/stats/pages.pal"

    // return StatsScreenPals();
// }

const char StatsScreenPagePals[] = "gfx/stats/pages.pal";

// void StatsScreenPals(void){
// INCLUDE "gfx/stats/stats.pal"

    // return v_CGB_Pokedex();
// }

const char StatsScreenPals[] = "gfx/stats/stats.pal";

void v_CGB_Pokedex(void){
    LD_DE(wBGPals1);
    LD_A(PREDEFPAL_POKEDEX);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);  // dex interface palette
    LD_A_addr(wCurPartySpecies);
    CP_A(0xff);
    IF_NZ goto is_pokemon;
    LD_HL(mPokedexQuestionMarkPalette);
    CALL(aLoadHLPaletteIntoDE);  // green question mark palette
    goto got_palette;


is_pokemon:
    CALL(aGetMonPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);  // mon palette

got_palette:
    CALL(aWipeAttrmap);
    hlcoord(1, 1, wAttrmap);
    LD_BC((7 << 8) | 7);
    LD_A(0x1);  // green question mark palette
    CALL(aFillBoxCGB);
    CALL(aInitPartyMenuOBPals);
    LD_HL(mPokedexCursorPalette);
    LD_DE(wOBPals1 + PALETTE_SIZE * 7);  // green cursor palette
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

// void PokedexQuestionMarkPalette(void){
// INCLUDE "gfx/pokedex/question_mark.pal"

    // return PokedexCursorPalette();
// }

const char PokedexQuestionMarkPalette[] = "gfx/pokedex/question_mark.pal";

// void PokedexCursorPalette(void){
// INCLUDE "gfx/pokedex/cursor.pal"

    // return v_CGB_BillsPC();
// }

const char PokedexCursorPalette[] = "gfx/pokedex/cursor.pal";

void v_CGB_BillsPC(void){
    LD_DE(wBGPals1);
    LD_A(PREDEFPAL_POKEDEX);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    LD_A_addr(wCurPartySpecies);
    CP_A(0xff);
    IF_NZ goto GetMonPalette;
    LD_HL(mBillsPCOrangePalette);
    CALL(aLoadHLPaletteIntoDE);
    goto GotPalette;


GetMonPalette:
    LD_BC(wTempMonDVs);
    CALL(aGetPlayerOrMonPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);

GotPalette:
    CALL(aWipeAttrmap);
    hlcoord(1, 4, wAttrmap);
    LD_BC((7 << 8) | 7);
    LD_A(0x1);  // mon palette
    CALL(aFillBoxCGB);
    CALL(aInitPartyMenuOBPals);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_Unknown(void){
//  //  unreferenced
    LD_HL(mBillsPCOrangePalette);
    CALL(aLoadHLPaletteIntoDE);
    goto GotPalette;


GetMonPalette:
//   //  unreferenced
    LD_BC(wTempMonDVs);
    CALL(aGetPlayerOrMonPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);

GotPalette:
    CALL(aWipeAttrmap);
    hlcoord(1, 1, wAttrmap);
    LD_BC((7 << 8) | 7);
    LD_A(0x1);  // mon palette
    CALL(aFillBoxCGB);
    CALL(aInitPartyMenuOBPals);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void BillsPCOrangePalette(void){
// INCLUDE "gfx/pc/orange.pal"

    return v_CGB_PokedexUnownMode();
}

void v_CGB_PokedexUnownMode(void){
    LD_DE(wBGPals1);
    LD_A(PREDEFPAL_POKEDEX);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    LD_A_addr(wCurPartySpecies);
    CALL(aGetMonPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    CALL(aWipeAttrmap);
    hlcoord(7, 5, wAttrmap);
    LD_BC((7 << 8) | 7);
    LD_A(0x1);  // mon palette
    CALL(aFillBoxCGB);
    CALL(aInitPartyMenuOBPals);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_SlotMachine(void){
    LD_HL(mSlotMachinePals);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    CALL(aWipeAttrmap);
    hlcoord(0, 2, wAttrmap);
    LD_BC((10 << 8) | 3);
    LD_A(0x2);  // "3" palette
    CALL(aFillBoxCGB);
    hlcoord(17, 2, wAttrmap);
    LD_BC((10 << 8) | 3);
    LD_A(0x2);  // "3" palette
    CALL(aFillBoxCGB);
    hlcoord(0, 4, wAttrmap);
    LD_BC((6 << 8) | 3);
    LD_A(0x3);  // "2" palette
    CALL(aFillBoxCGB);
    hlcoord(17, 4, wAttrmap);
    LD_BC((6 << 8) | 3);
    LD_A(0x3);  // "2" palette
    CALL(aFillBoxCGB);
    hlcoord(0, 6, wAttrmap);
    LD_BC((2 << 8) | 3);
    LD_A(0x4);  // "1" palette
    CALL(aFillBoxCGB);
    hlcoord(17, 6, wAttrmap);
    LD_BC((2 << 8) | 3);
    LD_A(0x4);  // "1" palette
    CALL(aFillBoxCGB);
    hlcoord(4, 2, wAttrmap);
    LD_BC((2 << 8) | 12);
    LD_A(0x1);  // Vileplume palette
    CALL(aFillBoxCGB);
    hlcoord(3, 2, wAttrmap);
    LD_BC((10 << 8) | 1);
    LD_A(0x1);  // lights palette
    CALL(aFillBoxCGB);
    hlcoord(16, 2, wAttrmap);
    LD_BC((10 << 8) | 1);
    LD_A(0x1);  // lights palette
    CALL(aFillBoxCGB);
    hlcoord(0, 12, wAttrmap);
    LD_BC(6 * SCREEN_WIDTH);
    LD_A(0x7);  // text palette
    CALL(aByteFill);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_BetaTitleScreen(void){
    LD_HL(mPalPacket_BetaTitleScreen + 1);
    CALL(aCopyFourPalettes);
    CALL(aWipeAttrmap);
    LD_DE(wOBPals1);
    LD_A(PREDEFPAL_PACK);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    hlcoord(0, 6, wAttrmap);
    LD_BC((12 << 8) | SCREEN_WIDTH);
    LD_A(0x1);
    CALL(aFillBoxCGB);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_GSIntro(void){
    LD_B(0);
    LD_HL(mv_CGB_GSIntro_Jumptable);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


Jumptable:
    //dw ['.ShellderLaprasScene'];
    //dw ['.JigglypuffPikachuScene'];
    //dw ['.StartersCharizardScene'];


ShellderLaprasScene:
    LD_HL(mv_CGB_GSIntro_ShellderLaprasBGPalette);
    LD_DE(wBGPals1);
    CALL(aLoadHLPaletteIntoDE);
    LD_HL(mv_CGB_GSIntro_ShellderLaprasOBPals);
    LD_DE(wOBPals1);
    LD_BC(2 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);
    CALL(aWipeAttrmap);
    RET;


ShellderLaprasBGPalette:
// INCLUDE "gfx/intro/gs_shellder_lapras_bg.pal"


ShellderLaprasOBPals:
// INCLUDE "gfx/intro/gs_shellder_lapras_ob.pal"


JigglypuffPikachuScene:
    LD_DE(wBGPals1);
    LD_A(PREDEFPAL_GS_INTRO_JIGGLYPUFF_PIKACHU_BG);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);

    LD_DE(wOBPals1);
    LD_A(PREDEFPAL_GS_INTRO_JIGGLYPUFF_PIKACHU_OB);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    CALL(aWipeAttrmap);
    RET;


StartersCharizardScene:
    LD_HL(mPalPacket_Pack + 1);
    CALL(aCopyFourPalettes);
    LD_DE(wOBPals1);
    LD_A(PREDEFPAL_GS_INTRO_STARTERS_TRANSITION);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    CALL(aWipeAttrmap);
    RET;

}

void v_CGB_BetaPoker(void){
    LD_HL(mBetaPokerPals);
    LD_DE(wBGPals1);
    LD_BC(5 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    CALL(aApplyPals);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    RET;

}

void v_CGB_Diploma(void){
    LD_HL(mDiplomaPalettes);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);

    LD_HL(mPalPacket_Diploma + 1);
    CALL(aCopyFourPalettes);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    RET;

}

void v_CGB_MapPals(void){
    CALL(aLoadMapPals);
    LD_A(SCGB_MAPPALS);
    LD_addr_A(wDefaultSGBLayout);
    RET;

}

void v_CGB_PartyMenu(void){
    LD_HL(mPalPacket_PartyMenu + 1);
    CALL(aCopyFourPalettes);
    CALL(aInitPartyMenuBGPal0);
    CALL(aInitPartyMenuBGPal7);
    CALL(aInitPartyMenuOBPals);
    CALL(aApplyAttrmap);
    RET;

}

void v_CGB_Evolution(void){
    LD_DE(wBGPals1);
    LD_A_C;
    AND_A_A;
    IF_Z goto pokemon;
    LD_A(PREDEFPAL_BLACKOUT);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    goto got_palette;


pokemon:
    LD_HL(wPartyMon1DVs);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_C_L;
    LD_B_H;
    LD_A_addr(wPlayerHPPal);
    CALL(aGetPlayerOrMonPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    LD_HL(mBattleObjectPals);
    LD_DE(wOBPals1 + PALETTE_SIZE * PAL_BATTLE_OB_GRAY);
    LD_BC(6 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);


got_palette:
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_GSTitleScreen(void){
    LD_HL(mUnusedGSTitleBGPals);
    LD_DE(wBGPals1);
    LD_BC(5 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    LD_HL(mUnusedGSTitleOBPals);
    LD_DE(wOBPals1);
    LD_BC(2 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);
    LD_A(SCGB_DIPLOMA);
    LD_addr_A(wDefaultSGBLayout);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_Unused0D(void){
    LD_HL(mPalPacket_Diploma + 1);
    CALL(aCopyFourPalettes);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    RET;

}

void v_CGB_UnownPuzzle(void){
    LD_HL(mPalPacket_UnownPuzzle + 1);
    CALL(aCopyFourPalettes);
    LD_DE(wOBPals1);
    LD_A(PREDEFPAL_UNOWN_PUZZLE);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wOBPals1));
    LDH_addr_A(rSVBK);
    LD_HL(wOBPals1);
    LD_A(LOW((1 << 0) * 31 + (1 << 5) * 0 + (1 << 10) * 0));  // (1 << 0) * 31 + (1 << 5) * 0 + (1 << 10) * 0
    LD_hli_A;
    LD_A(HIGH((1 << 0) * 31 + (1 << 5) * 0 + (1 << 10) * 0));  // (1 << 0) * 31 + (1 << 5) * 0 + (1 << 10) * 0
    LD_hl_A;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    RET;

}

void v_CGB_TrainerCard(void){
    LD_DE(wBGPals1);
    XOR_A_A;  // CHRIS
    CALL(aGetTrainerPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    LD_A(FALKNER);  // KRIS
    CALL(aGetTrainerPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    LD_A(BUGSY);
    CALL(aGetTrainerPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    LD_A(WHITNEY);
    CALL(aGetTrainerPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    LD_A(MORTY);
    CALL(aGetTrainerPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    LD_A(CHUCK);
    CALL(aGetTrainerPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    LD_A(JASMINE);
    CALL(aGetTrainerPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    LD_A(PRYCE);
    CALL(aGetTrainerPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    LD_A(PREDEFPAL_CGB_BADGE);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);

// fill screen with opposite-gender palette for the card border
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    LD_A_addr(wPlayerGender);
    AND_A_A;
    LD_A(0x1);  // kris
    IF_Z goto got_gender;
    LD_A(0x0);  // chris

got_gender:
    CALL(aByteFill);
// fill trainer sprite area with same-gender palette
    hlcoord(14, 1, wAttrmap);
    LD_BC((7 << 8) | 5);
    LD_A_addr(wPlayerGender);
    AND_A_A;
    LD_A(0x0);  // chris
    IF_Z goto got_gender2;
    LD_A(0x1);  // kris

got_gender2:
    CALL(aFillBoxCGB);
// top-right corner still uses the border's palette
    hlcoord(18, 1, wAttrmap);
    LD_hl(0x1);
    hlcoord(2, 11, wAttrmap);
    LD_BC((2 << 8) | 4);
    LD_A(0x1);  // falkner
    CALL(aFillBoxCGB);
    hlcoord(6, 11, wAttrmap);
    LD_BC((2 << 8) | 4);
    LD_A(0x2);  // bugsy
    CALL(aFillBoxCGB);
    hlcoord(10, 11, wAttrmap);
    LD_BC((2 << 8) | 4);
    LD_A(0x3);  // whitney
    CALL(aFillBoxCGB);
    hlcoord(14, 11, wAttrmap);
    LD_BC((2 << 8) | 4);
    LD_A(0x4);  // morty
    CALL(aFillBoxCGB);
    hlcoord(2, 14, wAttrmap);
    LD_BC((2 << 8) | 4);
    LD_A(0x5);  // chuck
    CALL(aFillBoxCGB);
    hlcoord(6, 14, wAttrmap);
    LD_BC((2 << 8) | 4);
    LD_A(0x6);  // jasmine
    CALL(aFillBoxCGB);
    hlcoord(10, 14, wAttrmap);
    LD_BC((2 << 8) | 4);
    LD_A(0x7);  // pryce
    CALL(aFillBoxCGB);
// clair uses kris's palette
    LD_A_addr(wPlayerGender);
    AND_A_A;
    PUSH_AF;
    IF_Z goto got_gender3;
    hlcoord(14, 14, wAttrmap);
    LD_BC((2 << 8) | 4);
    LD_A(0x1);
    CALL(aFillBoxCGB);

got_gender3:
    POP_AF;
    LD_C(0x0);
    IF_NZ goto got_gender4;
    INC_C;

got_gender4:
    LD_A_C;
    hlcoord(18, 1, wAttrmap);
    LD_hl_A;
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_MoveList(void){
    LD_DE(wBGPals1);
    LD_A(PREDEFPAL_GOLDENROD);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    LD_A_addr(wPlayerHPPal);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    LD_BC(mHPBarPals);
    ADD_HL_BC;
    CALL(aLoadPalette_White_Col1_Col2_Black);
    CALL(aWipeAttrmap);
    hlcoord(11, 1, wAttrmap);
    LD_BC((2 << 8) | 9);
    LD_A(0x1);
    CALL(aFillBoxCGB);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_BetaPikachuMinigame(void){
    LD_HL(mPalPacket_BetaPikachuMinigame + 1);
    CALL(aCopyFourPalettes);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_PokedexSearchOption(void){
    LD_DE(wBGPals1);
    LD_A(PREDEFPAL_POKEDEX);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_PackPals(void){
//  pack pals
    LD_A_addr(wBattleType);
    CP_A(BATTLETYPE_TUTORIAL);
    IF_Z goto tutorial_male;

    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto tutorial_male;

    LD_HL(mv_CGB_PackPals_KrisPackPals);
    goto got_gender;


tutorial_male:
    LD_HL(mv_CGB_PackPals_ChrisPackPals);


got_gender:
    LD_DE(wBGPals1);
    LD_BC(8 * PALETTE_SIZE);  // 6 palettes?
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    CALL(aWipeAttrmap);
    hlcoord(0, 0, wAttrmap);
    LD_BC((1 << 8) | 10);
    LD_A(0x1);
    CALL(aFillBoxCGB);
    hlcoord(10, 0, wAttrmap);
    LD_BC((1 << 8) | 10);
    LD_A(0x2);
    CALL(aFillBoxCGB);
    hlcoord(7, 2, wAttrmap);
    LD_BC((9 << 8) | 1);
    LD_A(0x3);
    CALL(aFillBoxCGB);
    hlcoord(0, 7, wAttrmap);
    LD_BC((3 << 8) | 5);
    LD_A(0x4);
    CALL(aFillBoxCGB);
    hlcoord(0, 3, wAttrmap);
    LD_BC((3 << 8) | 5);
    LD_A(0x5);
    CALL(aFillBoxCGB);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;


ChrisPackPals:
// INCLUDE "gfx/pack/pack.pal"


KrisPackPals:
// INCLUDE "gfx/pack/pack_f.pal"

    return v_CGB_Pokepic();
}

void v_CGB_Pokepic(void){
    CALL(av_CGB_MapPals);
    LD_DE(SCREEN_WIDTH);
    hlcoord(0, 0, wAttrmap);
    LD_A_addr(wMenuBorderTopCoord);

loop:
    AND_A_A;
    IF_Z goto found_top;
    DEC_A;
    ADD_HL_DE;
    goto loop;


found_top:
    LD_A_addr(wMenuBorderLeftCoord);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_addr(wMenuBorderTopCoord);
    LD_B_A;
    LD_A_addr(wMenuBorderBottomCoord);
    INC_A;
    SUB_A_B;
    LD_B_A;
    LD_A_addr(wMenuBorderLeftCoord);
    LD_C_A;
    LD_A_addr(wMenuBorderRightCoord);
    SUB_A_C;
    INC_A;
    LD_C_A;
    LD_A(PAL_BG_GRAY);
    CALL(aFillBoxCGB);
    CALL(aApplyAttrmap);
    RET;

}

void v_CGB_MagnetTrain(void){
//  //  unused
    LD_HL(mPalPacket_MagnetTrain + 1);
    CALL(aCopyFourPalettes);
    CALL(aWipeAttrmap);
    hlcoord(0, 4, wAttrmap);
    LD_BC((10 << 8) | SCREEN_WIDTH);
    LD_A(PAL_BG_GREEN);
    CALL(aFillBoxCGB);
    hlcoord(0, 6, wAttrmap);
    LD_BC((6 << 8) | SCREEN_WIDTH);
    LD_A(PAL_BG_RED);
    CALL(aFillBoxCGB);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void v_CGB_GamefreakLogo(void){
    LD_DE(wBGPals1);
    LD_A(PREDEFPAL_GAMEFREAK_LOGO_BG);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    LD_HL(mv_CGB_GamefreakLogo_GamefreakDittoPalette);
    LD_DE(wOBPals1);
    CALL(aLoadHLPaletteIntoDE);
    LD_HL(mv_CGB_GamefreakLogo_GamefreakDittoPalette);
    LD_DE(wOBPals1 + PALETTE_SIZE * 1);
    CALL(aLoadHLPaletteIntoDE);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    RET;


GamefreakDittoPalette:
// INCLUDE "gfx/splash/ditto.pal"

    return v_CGB_PlayerOrMonFrontpicPals();
}

void v_CGB_PlayerOrMonFrontpicPals(void){
    LD_DE(wBGPals1);
    LD_A_addr(wCurPartySpecies);
    LD_BC(wTempMonDVs);
    CALL(aGetPlayerOrMonPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    RET;

}

void v_CGB_Unused1E(void){
    LD_DE(wBGPals1);
    LD_A_addr(wCurPartySpecies);
    CALL(aGetMonPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    RET;

}

void v_CGB_TradeTube(void){
    LD_HL(mPalPacket_TradeTube + 1);
    CALL(aCopyFourPalettes);
    LD_HL(mPartyMenuOBPals);
    LD_DE(wOBPals1);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);
    LD_DE(wOBPals1 + PALETTE_SIZE * 7);
    LD_A(PREDEFPAL_TRADE_TUBE);
    CALL(aGetPredefPal);
    CALL(aLoadHLPaletteIntoDE);
    CALL(aWipeAttrmap);
    RET;

}

void v_CGB_TrainerOrMonFrontpicPals(void){
    LD_DE(wBGPals1);
    LD_A_addr(wCurPartySpecies);
    LD_BC(wTempMonDVs);
    CALL(aGetFrontpicPalettePointer);
    CALL(aLoadPalette_White_Col1_Col2_Black);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    CALL(aApplyPals);
    RET;

}

void v_CGB_MysteryGift(void){
    LD_HL(mv_CGB_MysteryGift_MysteryGiftPalettes);
    LD_DE(wBGPals1);
    LD_BC(2 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    CALL(aApplyPals);
    CALL(aWipeAttrmap);
    hlcoord(3, 7, wAttrmap);
    LD_BC((8 << 8) | 14);
    LD_A(0x1);
    CALL(aFillBoxCGB);
    hlcoord(1, 5, wAttrmap);
    LD_BC((1 << 8) | 18);
    LD_A(0x1);
    CALL(aFillBoxCGB);
    hlcoord(1, 16, wAttrmap);
    LD_BC((1 << 8) | 18);
    LD_A(0x1);
    CALL(aFillBoxCGB);
    hlcoord(0, 0, wAttrmap);
    LD_BC((17 << 8) | 2);
    LD_A(0x1);
    CALL(aFillBoxCGB);
    hlcoord(18, 5, wAttrmap);
    LD_BC((12 << 8) | 1);
    LD_A(0x1);
    CALL(aFillBoxCGB);
    CALL(aApplyAttrmap);
    RET;


MysteryGiftPalettes:
// INCLUDE "gfx/mystery_gift/mystery_gift.pal"

    return GS_CGB_MysteryGift();
}

void GS_CGB_MysteryGift(void){
//  //  unreferenced
    LD_HL(mGS_CGB_MysteryGift_MysteryGiftPalette);
    LD_DE(wBGPals1);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    CALL(aApplyPals);
    CALL(aWipeAttrmap);
    CALL(aApplyAttrmap);
    RET;


MysteryGiftPalette:
// INCLUDE "gfx/mystery_gift/gs_mystery_gift.pal"

}
