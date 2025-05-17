#include "../../constants.h"
#include "print_unown.h"
#include "print_unown_2.h"
#include "../../home/audio.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/joypad.h"
#include "../../home/map.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/sram.h"
#include "../gfx/place_graphic.h"
#include "../gfx/load_pics.h"
#include "../printer/printer.h"

#define UNOWNSTAMP_BOLD_A (0xef)  //  "♂"
#define UNOWNSTAMP_BOLD_B (0xf5)  //  "♀"

static void v_UnownPrinter_UpdateUnownFrontpic(void);
static void v_UnownPrinter_LeftRight(void);

void v_UnownPrinter(void){
    // LD_A_addr(wUnownDex);
    // AND_A_A;
    // RET_Z ;
    if(wram->wUnownDex[0] == 0)
        return;

    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram.hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram.hInMenu = 0x1;
    // LD_A_addr(wOptions);
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_A(NO_TEXT_SCROLL);
    // LD_addr_A(wOptions);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearTilemap);
    ClearTilemap();

    // LD_DE(mUnownDexATile);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * UNOWNSTAMP_BOLD_A);
    // LD_BC((BANK(aUnownDexATile) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * UNOWNSTAMP_BOLD_A, UnownDexATile, 0, 1);

    // LD_DE(mUnownDexBTile);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * UNOWNSTAMP_BOLD_B);
    // LD_BC((BANK(aUnownDexBTile) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * UNOWNSTAMP_BOLD_B, UnownDexBTile, 0, 1);

    // hlcoord(0, 0, wTilemap);
    // LD_BC((3 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 0, wram->wTilemap), 3, 18);

    // hlcoord(0, 5, wTilemap);
    // LD_BC((7 << 8) | 7);
    // CALL(aTextbox);
    Textbox(coord(0, 5, wram->wTilemap), 7, 7);

    // hlcoord(0, 14, wTilemap);
    // LD_BC((2 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 14, wram->wTilemap), 2, 8);

    // hlcoord(1, 2, wTilemap);
    // LD_DE(mAlphRuinsStampString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(AlphRuinsStampString), coord(1, 2, wram->wTilemap));

    // hlcoord(1, 16, wTilemap);
    // LD_DE(mUnownDexDoWhatString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(UnownDexDoWhatString), coord(1, 16, wram->wTilemap));

    // hlcoord(10, 6, wTilemap);
    // LD_DE(mUnownDexMenuString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(UnownDexDoWhatString), coord(1, 16, wram->wTilemap));

    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // CALL(av_UnownPrinter_UpdateUnownFrontpic);
    v_UnownPrinter_UpdateUnownFrontpic();
    // CALL(aWaitBGMap);
    WaitBGMap();

    // LD_A(UNOWN);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = UNOWN;
    // XOR_A_A;
    // LD_addr_A(wTempMonDVs);
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = 0;

    // LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aSetPalettes);
    SetPalettes();

    while(1){
    // joy_loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();

        // LDH_A_addr(hJoyPressed);
        // AND_A(B_BUTTON);
        // IF_NZ goto pressed_b;
        if(hram.hJoyPressed & B_BUTTON)
            break;

        // LDH_A_addr(hJoyPressed);
        // AND_A(A_BUTTON);
        // IF_NZ goto pressed_a;
        if(hram.hJoyPressed & A_BUTTON){
        // pressed_a:
            // LD_A_addr(wJumptableIndex);
            // PUSH_AF;
            uint8_t jt = wram->wJumptableIndex;
            // FARCALL(aPrintUnownStamp);
            PrintUnownStamp();
            // CALL(aRestartMapMusic);
            RestartMapMusic();
            // POP_AF;
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = jt;
            // goto joy_loop;
            continue;
        }

        // CALL(av_UnownPrinter_LeftRight);
        v_UnownPrinter_LeftRight();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto joy_loop;
    }

// pressed_b:
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram.hInMenu = inMenu;
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // RET;
}

static void v_UnownPrinter_Load2bppToSRAM(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wDecompressScratch));
    // LDH_addr_A(rSVBK);

    // LD_A(BANK(sScratch));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asScratch));
    // LD_DE(wDecompressScratch);
    // LD_HL(sScratch);
    // LDH_A_addr(hROMBank);
    // LD_B_A;
    // LD_C(0x31);
    // CALL(aGet2bpp);
    CopyBytes(GBToRAMAddr(sScratch), wram->wDecompressScratch, 0x31 * LEN_2BPP_TILE);
    // CALL(aCloseSRAM);
    CloseSRAM();

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

static void v_UnownPrinter_UpdateUnownFrontpic(void){
    // LD_A_addr(wJumptableIndex);
    // CP_A(NUM_UNOWN);
    // IF_Z goto vacant;
    if(wram->wJumptableIndex == NUM_UNOWN){
    // vacant:
        // hlcoord(1, 6, wTilemap);
        // LD_BC((7 << 8) | 7);
        // CALL(aClearBox);
        ClearBox(coord(1, 6, wram->wTilemap), 7, 7);
        // hlcoord(1, 9, wTilemap);
        // LD_DE(mUnownDexVacantString);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(UnownDexVacantString), coord(1, 9, wram->wTilemap));
        // XOR_A_A;  // sScratch
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asScratch));
        // LD_HL(sScratch);
        // LD_BC(0x31 * LEN_2BPP_TILE);
        // XOR_A_A;
        // CALL(aByteFill);
        ByteFill(GBToRAMAddr(sScratch), 0x31 * LEN_2BPP_TILE, 0x0);
        // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
        // LD_DE(sScratch);
        // LD_C(0x31);
        // LDH_A_addr(hROMBank);
        // LD_B_A;
        // CALL(aGet2bpp);
        CopyBytes(vram->vTiles2 + LEN_2BPP_TILE * 0x31, GBToRAMAddr(sScratch), 0x31 * LEN_2BPP_TILE);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // LD_C(20);
        // CALL(aDelayFrames);
        DelayFrames(20);
        // RET;
        return;
    }
    // INC_A;
    // LD_addr_A(wUnownLetter);
    wram->wUnownLetter = wram->wJumptableIndex + 1;
    // LD_A(UNOWN);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = UNOWN;
    // XOR_A_A;
    // LD_addr_A(wBoxAlignment);
    wram->wBoxAlignment = 0x0;
    // LD_DE(vTiles2);
    // PREDEF(pGetMonFrontpic);
    GetMonFrontpic(vram->vTiles2);
    // CALL(av_UnownPrinter_Load2bppToSRAM);
    v_UnownPrinter_Load2bppToSRAM();
    // hlcoord(1, 6, wTilemap);
    // XOR_A_A;
    // LDH_addr_A(hGraphicStartTile);
    hram.hGraphicStartTile = 0x0;
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger(coord(1, 6, wram->wTilemap), 7, 7);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
    // FARCALL(aRotateUnownFrontpic);
    RotateUnownFrontpic(vram->vTiles2 + LEN_2BPP_TILE * 0x31);
    // RET;
}

static void v_UnownPrinter_LeftRight(void){
    // LDH_A_addr(hJoyLast);
    // AND_A(D_RIGHT);
    // IF_NZ goto press_right;
    if(hram.hJoyLast & D_RIGHT){
    // press_right:
        // LD_HL(wJumptableIndex);
        // LD_A_hl;
        // CP_A(NUM_UNOWN);
        // IF_C goto wrap_around_right;
        if(wram->wJumptableIndex >= NUM_UNOWN){
            // LD_hl(-1);
            wram->wJumptableIndex = 0xff;
        }

    // wrap_around_right:
        // INC_hl;
        wram->wJumptableIndex++;
    }
    // LDH_A_addr(hJoyLast);
    // AND_A(D_LEFT);
    // IF_NZ goto press_left;
    else if(hram.hJoyLast & D_LEFT){
    // press_left:
        // LD_HL(wJumptableIndex);
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto wrap_around_left;
        if(wram->wJumptableIndex == 0){
            // LD_hl(NUM_UNOWN + 1);
            wram->wJumptableIndex = NUM_UNOWN + 1;
        }

    // wrap_around_left:
        // DEC_hl;
        wram->wJumptableIndex--;
        // goto l_return;
    }
    else {
        // RET;
        return;
    }

// l_return:
    // CALL(av_UnownPrinter_UpdateUnownFrontpic);
    v_UnownPrinter_UpdateUnownFrontpic();
    // RET;
}

const char AlphRuinsStampString[] = " ALPH RUINS STAMP";
const char UnownDexDoWhatString[] = "Do what?";

const char UnownDexMenuString[] = 
           "♂ PRINT" // UNOWNSTAMP_BOLD_A, " PRINT"
    t_next "♀ CANCEL" // UNOWNSTAMP_BOLD_B, " CANCEL"
    t_next "← PREVIOUS"
    t_next "→ NEXT";

const char UnownDexVacantString[] = "VACANT";

const char UnownDexATile[] = "gfx/printer/bold_a.png";
const char UnownDexBTile[] = "gfx/printer/bold_b.png";

void PlaceUnownPrinterFrontpic(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // hlcoord(7, 11, wTilemap);
    // LD_A(0x31);
    // LDH_addr_A(hGraphicStartTile);
    hram.hGraphicStartTile = 0x31;
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger(coord(7, 11, wram->wTilemap), 7, 7);
    // RET;
}
