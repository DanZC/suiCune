#include "../../constants.h"
#include "print_party.h"
#include "../../charmap.h"
#include "../../home/copy.h"
#include "../../home/text.h"
#include "../../home/pokemon.h"
#include "../../home/pokedex_flags.h"
#include "../../home/tilemap.h"
#include "../../home/clear_sprites.h"
#include "../../home/gfx.h"
#include "../../home/print_text.h"
#include "../../home/names.h"
#include "../gfx/color.h"
#include "../gfx/load_pics.h"
#include "../pokemon/tempmon.h"
#include "../pokemon/mon_stats.h"
#include "../pokedex/pokedex_2.h"
#include "../../gfx/font.h"

#define PRINTPARTY_HP (0x71)  // "◀"

void PrintPage1(void){
    // hlcoord(0, 0, wTilemap);
    // decoord(0, 0, wPrinterTilemapBuffer);
    // LD_BC(17 * SCREEN_WIDTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(coord(0, 0, wram->wPrinterTilemapBuffer), coord(0, 0, wram->wTilemap), 17 * SCREEN_WIDTH);
    // hlcoord(17, 1, wPrinterTilemapBuffer);
    // LD_A(0x62);
    // LD_hli_A;
    *coord(17, 1, wram->wPrinterTilemapBuffer) = 0x62;
    // INC_A;  // $63
    // LD_hl_A;
    *coord(18, 1, wram->wPrinterTilemapBuffer) = 0x63;
    // hlcoord(17, 2, wPrinterTilemapBuffer);
    // LD_A(0x64);
    // LD_hli_A;
    *coord(17, 2, wram->wPrinterTilemapBuffer) = 0x64;
    // INC_A;  // $65
    // LD_hl_A;
    *coord(18, 2, wram->wPrinterTilemapBuffer) = 0x65;
    // hlcoord(1, 9, wPrinterTilemapBuffer);
    // LD_A(0x7f);
    // LD_hli_A;
    *coord(1, 9, wram->wPrinterTilemapBuffer) = CHAR_SPACE;
    // LD_hl_A;
    *coord(2, 9, wram->wPrinterTilemapBuffer) = CHAR_SPACE;
    // hlcoord(1, 10, wPrinterTilemapBuffer);
    // LD_A(0x61);
    // LD_hli_A;
    *coord(1, 10, wram->wPrinterTilemapBuffer) = 0x61;
    // LD_hl_A;
    *coord(2, 10, wram->wPrinterTilemapBuffer) = 0x61;
    // hlcoord(2, 11, wPrinterTilemapBuffer);
    // LD_BC((5 << 8) | 18);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(2, 11, wram->wPrinterTilemapBuffer), 18, 5);
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // CALL(aCheckCaughtMon);
    bool caught = CheckCaughtMon_Conv(wram->wTempSpecies - 1);
    // PUSH_AF;
    // LD_A_addr(wTempSpecies);
    // LD_B_A;
    // LD_C(1);  // get page 1
    // FARCALL(aGetDexEntryPagePointer);
    uint8_t* entryPage = GetDexEntryPagePointer_Conv(wram->wTempSpecies, 1);
    // POP_AF;
    // LD_A_B;
    // hlcoord(1, 11, wPrinterTilemapBuffer);
    // CALL_NZ (aPlaceFarString);
    if(caught) {
        PlaceStringSimple(entryPage, coord(1, 11, wram->wPrinterTilemapBuffer));
    }
    // hlcoord(19, 0, wPrinterTilemapBuffer);
    // LD_hl(0x35);
    *coord(19, 0, wram->wPrinterTilemapBuffer) = 0x35;
    // LD_DE(SCREEN_WIDTH);
    // ADD_HL_DE;
    tile_t* hl = coord(19, 1, wram->wPrinterTilemapBuffer);
    // LD_B(0xf);
    uint8_t b = 0xf;

    do {
    // column_loop:
        // LD_hl(0x37);
        *hl = 0x37;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto column_loop;
    } while(--b != 0);
    // LD_hl(0x3a);
    *hl = 0x3a;
    // RET;
}

static void PrintPage2_FillColumn(tile_t* hl, tile_t a, uint8_t b) {
    // PUSH_DE;
    // LD_DE(SCREEN_WIDTH);

    do {
    // column_loop:
        // LD_hl_A;
        *hl = a;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto column_loop;
    } while(--b != 0);
    // POP_DE;
    // RET;
}

void PrintPage2(void){
    // hlcoord(0, 0, wPrinterTilemapBuffer);
    // LD_BC(8 * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wPrinterTilemapBuffer), 8 * SCREEN_WIDTH, CHAR_SPACE);
    // hlcoord(0, 0, wPrinterTilemapBuffer);
    // LD_A(0x36);
    // LD_B(6);
    // CALL(aPrintPage2_FillColumn);
    PrintPage2_FillColumn(coord(0, 0, wram->wPrinterTilemapBuffer), 0x36, 6);
    // hlcoord(19, 0, wPrinterTilemapBuffer);
    // LD_A(0x37);
    // LD_B(6);
    // CALL(aPrintPage2_FillColumn);
    PrintPage2_FillColumn(coord(19, 0, wram->wPrinterTilemapBuffer), 0x37, 6);
    // hlcoord(0, 6, wPrinterTilemapBuffer);
    // LD_hl(0x38);
    *coord(0, 6, wram->wPrinterTilemapBuffer) = 0x38;
    // INC_HL;
    // LD_A(0x39);
    // LD_BC(SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(1, 6, wram->wPrinterTilemapBuffer), SCREEN_HEIGHT, 0x39);
    // LD_hl(0x3a);
    *coord(19, 6, wram->wPrinterTilemapBuffer) = 0x3a;
    // hlcoord(0, 7, wPrinterTilemapBuffer);
    // LD_BC(SCREEN_WIDTH);
    // LD_A(0x32);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 7, wram->wPrinterTilemapBuffer), SCREEN_HEIGHT, 0x32);
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // CALL(aCheckCaughtMon);
    bool caught = CheckCaughtMon_Conv(wram->wTempSpecies - 1);
    // PUSH_AF;
    // LD_A_addr(wTempSpecies);
    // LD_B_A;
    // LD_C(2);  // get page 2
    // FARCALL(aGetDexEntryPagePointer);
    uint8_t* entry = GetDexEntryPagePointer_Conv(wram->wTempSpecies, 2);
    // POP_AF;
    // hlcoord(1, 1, wPrinterTilemapBuffer);
    // LD_A_B;
    // CALL_NZ (aPlaceFarString);
    if(caught) {
        PlaceStringSimple(entry, coord(1, 1, wram->wPrinterTilemapBuffer));
    }
    // RET;
}

void GBPrinterStrings(void){
//  //  used only for BANK(GBPrinterStrings)
}

const char GBPrinterString_Null[] = "@";

const char GBPrinterString_CheckingLink[] = 
    t_next " CHECKING LINK...";

const char GBPrinterString_Transmitting[] =
    t_next "  TRANSMITTING..."; //next "  TRANSMITTING...@"

const char GBPrinterString_Printing[] = 
    t_next "    PRINTING..."; //next "    PRINTING...@"

const char GBPrinterString_PrinterError1[] =
           " Printer Error 1"
    t_next ""
    t_next "Check the Game Boy"
    t_next "Printer Manual.";

const char GBPrinterString_PrinterError2[] = 
           " Printer Error 2"
    t_next ""
    t_next "Check the Game Boy"
    t_next "Printer Manual.";

const char GBPrinterString_PrinterError3[] =
           " Printer Error 3"
    t_next ""
    t_next "Check the Game Boy"
    t_next "Printer Manual.";

const char GBPrinterString_PrinterError4[] = 
           " Printer Error 4"
    t_next ""
    t_next "Check the Game Boy"
    t_next "Printer Manual.";

void PrintPartyMonPage1(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra_Conv();

    // LD_DE(mGBPrinterHPIcon);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * PRINTPARTY_HP);
    // LD_BC((BANK(aGBPrinterHPIcon) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * PRINTPARTY_HP, GBPrinterHPIcon, 0, 1);

    // LD_DE(mGBPrinterLvIcon);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_LV);
    // LD_BC((BANK(aGBPrinterLvIcon) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * CHAR_LV, GBPrinterLvIcon, 0, 1);

    // LD_DE(mStatsScreenPageTilesGFX + 14 * LEN_2BPP_TILE);  // shiny icon
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_SHINY_ICON);
    // LD_BC((BANK(aStatsScreenPageTilesGFX) << 8) | 1);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * CHAR_SHINY_ICON, StatsScreenPageTilesGFX, 14, 1);

    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // FARCALL(aCopyMonToTempMon);
    CopyMonToTempMon_Conv();
    // hlcoord(0, 7, wTilemap);
    // LD_B(9);
    // LD_C(18);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 7, wram->wTilemap), 9, 18);
    // hlcoord(8, 2, wTilemap);
    // LD_A_addr(wTempMonLevel);
    // CALL(aPrintLevel_Force3Digits);
    PrintLevel_Force3Digits_Conv(coord(8, 2, wram->wTilemap), wram->wTempMon.mon.level);
    // hlcoord(12, 2, wTilemap);
    // LD_hl(PRINTPARTY_HP);
    *coord(12, 2, wram->wTilemap) = PRINTPARTY_HP;
    // INC_HL;
    // LD_DE(wTempMonMaxHP);
    // LD_BC((2 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(13, 2, wram->wTilemap), &wram->wTempMon.maxHP, 2, 3);
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wNamedObjectIndex);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies;
    // LD_HL(wPartyMonNicknames);
    // CALL(aGetCurPartyMonName);
    // hlcoord(8, 4, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wPartyMonNickname[wram->wCurPartyMon], coord(8, 4, wram->wTilemap));
    // hlcoord(9, 6, wTilemap);
    // LD_hl(0xf3);
    *coord(9, 6, wram->wTilemap) = CHAR_FWD_SLASH;
    // CALL(aGetPokemonName);
    // hlcoord(10, 6, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(GetPokemonName_Conv2(wram->wCurSpecies), coord(10, 6, wram->wTilemap));
    // hlcoord(8, 0, wTilemap);
    // LD_hl(0x74);
    *coord(8, 0, wram->wTilemap) = CHAR_NO;
    // INC_HL;
    // LD_hl(0xe8);
    *coord(9, 0, wram->wTilemap) = CHAR_PERIOD;
    // INC_HL;
    // LD_DE(wNamedObjectIndex);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(10, 0, wram->wTilemap), &wram->wCurSpecies, PRINTNUM_LEADINGZEROS | 1, 3);
    // hlcoord(1, 9, wTilemap);
    // LD_DE(mPrintParty_OTString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(PrintParty_OTString), coord(1, 9, wram->wTilemap));
    // LD_HL(wPartyMonOTs);
    // CALL(aGetCurPartyMonName);
    // hlcoord(4, 9, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wPartyMonOT[wram->wCurPartyMon], coord(4, 9, wram->wTilemap));
    // hlcoord(1, 11, wTilemap);
    // LD_DE(mPrintParty_IDNoString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(PrintParty_IDNoString), coord(1, 11, wram->wTilemap));
    // hlcoord(4, 11, wTilemap);
    // LD_DE(wTempMonID);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(4, 11, wram->wTilemap), &wram->wTempMon.mon.id, PRINTNUM_LEADINGZEROS | 2, 5);
    // hlcoord(1, 14, wTilemap);
    // LD_DE(mPrintParty_MoveString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(PrintParty_MoveString), coord(1, 14, wram->wTilemap));
    // hlcoord(7, 14, wTilemap);
    // LD_A_addr(wTempMonMoves + 0);
    // CALL(aPlaceMoveNameString);
    PlaceMoveNameString(coord(7, 14, wram->wTilemap), wram->wTempMon.mon.moves[0]);
    // CALL(aPlaceGenderAndShininess);
    PlaceGenderAndShininess();
    // LD_HL(wTempMonDVs);
    // PREDEF(pGetUnownLetter);
    GetUnownLetter_Conv(wram->wTempMon.mon.DVs);
    // LD_HL(wBoxAlignment);
    // XOR_A_A;
    // LD_hl_A;
    wram->wBoxAlignment = 0x0;
    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_Z goto got_alignment;
    if(wram->wCurPartySpecies != UNOWN) {
        // INC_hl;
        wram->wBoxAlignment = 0x1;
    }

// got_alignment:
    // hlcoord(0, 0, wTilemap);
    // CALL(av_PrepMonFrontpic);
    v_PrepMonFrontpic_Conv(coord(0, 0, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_B(SCGB_STATS_SCREEN_HP_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_STATS_SCREEN_HP_PALS);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // RET;
}

static void PrintPartyMonPage2_PrintTempMonStats(tile_t* hl, uint16_t de){
    // LD_BC((2 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum_Conv2(hl, &de, 2, 3);
    // RET;
}

void PrintPartyMonPage2(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra_Conv();
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // FARCALL(aCopyMonToTempMon);
    CopyMonToTempMon_Conv();
    // hlcoord(0, 0, wTilemap);
    // LD_B(15);
    // LD_C(18);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 0, wram->wTilemap), 15, 18);
    // LD_BC(SCREEN_WIDTH);
    // decoord(0, 0, wTilemap);
    // hlcoord(0, 1, wTilemap);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(coord(0, 0, wram->wTilemap), coord(0, 1, wram->wTilemap), SCREEN_WIDTH);
    // hlcoord(7, 0, wTilemap);
    // LD_A_addr(wTempMonMoves + 1);
    // CALL(aPlaceMoveNameString);
    PlaceMoveNameString(coord(7, 0, wram->wTilemap), wram->wTempMon.mon.moves[1]);
    // hlcoord(7, 2, wTilemap);
    // LD_A_addr(wTempMonMoves + 2);
    // CALL(aPlaceMoveNameString);
    PlaceMoveNameString(coord(7, 2, wram->wTilemap), wram->wTempMon.mon.moves[2]);
    // hlcoord(7, 4, wTilemap);
    // LD_A_addr(wTempMonMoves + 3);
    // CALL(aPlaceMoveNameString);
    PlaceMoveNameString(coord(7, 4, wram->wTilemap), wram->wTempMon.mon.moves[3]);
    // hlcoord(7, 7, wTilemap);
    // LD_DE(mPrintParty_StatsString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(PrintParty_StatsString), coord(7, 7, wram->wTilemap));
    // hlcoord(16, 7, wTilemap);
    // LD_DE(wTempMonAttack);
    // CALL(aPrintPartyMonPage2_PrintTempMonStats);
    PrintPartyMonPage2_PrintTempMonStats(coord(16, 7, wram->wTilemap), wram->wTempMon.attack);
    // hlcoord(16, 9, wTilemap);
    // LD_DE(wTempMonDefense);
    // CALL(aPrintPartyMonPage2_PrintTempMonStats);
    PrintPartyMonPage2_PrintTempMonStats(coord(16, 9, wram->wTilemap), wram->wTempMon.defense);
    // hlcoord(16, 11, wTilemap);
    // LD_DE(wTempMonSpclAtk);
    // CALL(aPrintPartyMonPage2_PrintTempMonStats);
    PrintPartyMonPage2_PrintTempMonStats(coord(16, 11, wram->wTilemap), wram->wTempMon.spclAtk);
    // hlcoord(16, 13, wTilemap);
    // LD_DE(wTempMonSpclDef);
    // CALL(aPrintPartyMonPage2_PrintTempMonStats);
    PrintPartyMonPage2_PrintTempMonStats(coord(16, 13, wram->wTilemap), wram->wTempMon.spclDef);
    // hlcoord(16, 15, wTilemap);
    // LD_DE(wTempMonSpeed);
    // CALL(aPrintPartyMonPage2_PrintTempMonStats);
    PrintPartyMonPage2_PrintTempMonStats(coord(16, 15, wram->wTilemap), wram->wTempMon.speed);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_B(SCGB_STATS_SCREEN_HP_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_STATS_SCREEN_HP_PALS);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // RET;
}

void GetCurPartyMonName(void){
    LD_BC(NAME_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    RET;

}

void PlaceMoveNameString(tile_t* hl, move_t move){
    // AND_A_A;
    // IF_Z goto no_move;
    uint8_t* de;
    if(move != NO_MOVE) {
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetMoveName);
        de = GetMoveName_Conv2(move);
        // goto got_string;
    }
    else {
    // no_move:
        // LD_DE(mPrintParty_NoMoveString);
        ByteFill_Conv2(wram->wStringBuffer1, sizeof(wram->wStringBuffer1), CHAR_TERM);
        de = U82CA(wram->wStringBuffer1, PrintParty_NoMoveString);
    }

// got_string:
    // CALL(aPlaceString);
    PlaceStringSimple(de, hl);
    // RET;
}

void PlaceGenderAndShininess(void){
    // FARCALL(aGetGender);
    u8_flag_s res = GetGender_Conv(wram->wMonType);
    uint8_t a;
    // LD_A(0x7f);
    // IF_C goto got_gender;
    if(res.flag)
        a = CHAR_SPACE;
    // LD_A(0xef);
    // IF_NZ goto got_gender;
    else if(res.a != 0)
        a = CHAR_MALE_ICON;
    // LD_A(0xf5);
    else
        a = CHAR_FEMALE_ICON;

// got_gender:
    // hlcoord(17, 2, wTilemap);
    // LD_hl_A;
    *coord(17, 2, wram->wTilemap) = a;
    // LD_BC(wTempMonDVs);
    // FARCALL(aCheckShininess);
    // RET_NC ;
    if(CheckShininess_Conv(wram->wTempMon.mon.DVs)) {
        // hlcoord(18, 2, wTilemap);
        // LD_hl(0x3f);
        *coord(18, 2, wram->wTilemap) = CHAR_SHINY_ICON;
    }
    // RET;

}

const char PrintParty_OTString[]= "OT/";
const char PrintParty_MoveString[] = "MOVE";
const char PrintParty_IDNoString[] = "<ID>№.";

const char PrintParty_StatsString[] = "ATTACK"
    t_next "DEFENSE"
    t_next "SPCL.ATK"
    t_next "SPCL.DEF"
    t_next "SPEED";

const char PrintParty_NoMoveString[] = "------------@";

const char GBPrinterHPIcon[] = "gfx/printer/hp.png";
const char GBPrinterLvIcon[] = "gfx/printer/lv.png";
