#include "../../constants.h"
#include "credits.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/clear_sprites.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/audio.h"
#include "../../data/credits_script.h"
#include "../../data/credits_strings.h"
#include "../../gfx/misc.h"

// INCLUDE "constants.asm"


// SECTION "Credits", ROMX

void Credits(uint8_t b){
    // BIT_B(6);  // Hall Of Fame
    // LD_A(0x0);
    // IF_Z goto okay;
    // LD_A(0x40);

// okay:
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = (!bit_test(b, 6))? 0x0: 0x40;

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wGBCPalettes));
    // LDH_addr_A(rSVBK);

    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();

    // LD_HL(wCreditsBlankFrame2bpp);
    // LD_C((wCreditsBlankFrame2bppEnd - wCreditsBlankFrame2bpp) / 2);
    // LD_DE(0b1010101010101010);  // eight pixels, each color #2 (dark)

//  Fill wCreditsBlankFrame2bpp with 4x4=16 tiles, all solid dark color
//  (the same color used for the four border frame mons' backgrounds)

    for(uint32_t i = 0; i < 16 * LEN_2BPP_TILE; i += 2) {
    // load_loop:
        // LD_A_E;
        // LD_hli_A;
        // LD_A_D;
        // LD_hli_A;
        wram->wCreditsBlankFrame2bpp[i] = 0;
        wram->wCreditsBlankFrame2bpp[i + 1] = 0xff;
        // DEC_C;
        // IF_NZ goto load_loop;
    }

    // LD_DE(mCreditsBorderGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x20);
    // LD_BC((BANK(aCreditsBorderGFX) << 8) | 9);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x20, CreditsBorderGFX, 0, 9);

    // LD_DE(mCopyrightGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x60);
    // LD_BC((BANK(aCopyrightGFX) << 8) | 29);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x60, CopyrightGFX, 0, 29);

    // LD_DE(mTheEndGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x40);
    // LD_BC((BANK(aTheEndGFX) << 8) | 16);
    // CALL(aRequest2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x40, TheEndGFX, 0, 16);

    // LD_A(0xff);
    // LD_addr_A(wCreditsBorderFrame);
    wram->wCreditsBorderFrame = 0xff;
    // XOR_A_A;
    // LD_addr_A(wCreditsBorderMon);
    wram->wCreditsBorderMon = 0;

    // CALL(aCredits_LoadBorderGFX);
    // LD_E_L;
    // LD_D_H;
    // LD_HL(vTiles2);
    // LD_BC((BANK(aCreditsMonsGFX) << 8) | 16);
    // CALL(aRequest2bpp);
    CopyBytes_Conv2(vram->vTiles2, Credits_LoadBorderGFX(), 16 * LEN_2BPP_TILE);

    // CALL(aConstructCreditsTilemap);
    ConstructCreditsTilemap();
    // XOR_A_A;
    // LD_addr_A(wCreditsLYOverride);
    wram->wCreditsLYOverride = 0x0;

    // LD_HL(wLYOverrides);
    // LD_BC(0x100);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wLYOverrides, 0x100, 0x0);

    // LD_A(LOW(rSCX));
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = LOW(rSCX);

    // CALL(aGetCreditsPalette);
    GetCreditsPalette();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LDH_A_addr(hVBlank);
    // PUSH_AF;
    uint8_t vblank = hram->hVBlank;
    // LD_A(0x5);
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0x5;
#if BUGFIX_HINMENU_NOT_PRESERVED
    uint8_t inMenu = hram->hInMenu;
#endif
    // LD_A(TRUE);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = TRUE;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // LD_addr_A(wCreditsPos);
    // LD_addr_A(wCreditsPos + 1);
    wram->wCreditsPos = 0;
    // LD_addr_A(wCreditsTimer);
    wram->wCreditsTimer = 0;

    while(1) {
    // execution_loop:
        // CALL(aCredits_HandleBButton);
        Credits_HandleBButton();
        // CALL(aCredits_HandleAButton);
        // IF_NZ goto exit_credits;
        if(Credits_HandleAButton())
            break;

        // CALL(aCredits_Jumptable);
        Credits_Jumptable();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto execution_loop;
    }

// exit_credits:
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0x0;
    // LDH_addr_A(hBGMapAddress);
    hram->hBGMapAddress = (hram->hBGMapAddress & 0xff00) | 0x0;
#if BUGFIX_HINMENU_NOT_PRESERVED
    hram->hInMenu = inMenu;
#endif
    // POP_AF;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = vblank;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

bool Credits_HandleAButton(void){
    // LDH_A_addr(hJoypadDown);
    // AND_A(A_BUTTON);
    // RET_Z ;
    if(hram->hJoypadDown & A_BUTTON) {
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        return bit_test(wram->wJumptableIndex, 7) != 0;
    }
    // RET;
    return false;
}

void Credits_HandleBButton(void){
    // LDH_A_addr(hJoypadDown);
    // AND_A(B_BUTTON);
    // RET_Z ;
    if((hram->hJoypadDown & B_BUTTON) == 0)
        return;
    // LD_A_addr(wJumptableIndex);
    // BIT_A(6);
    // RET_Z ;
    if(!bit_test(wram->wJumptableIndex, 6))
        return;
    // LD_HL(wCreditsPos);
    // LD_A_hli;
    // CP_A(0xd);
    // IF_NC goto okay;
    // LD_A_hli;
    // AND_A_A;
    // RET_Z ;
    if(wram->wCreditsPos < 0x000d)
        return;

// okay:
    // LD_HL(wCreditsTimer);
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(wram->wCreditsTimer == 0)
        return;
    // DEC_hl;
    wram->wCreditsTimer--;
    // RET;
}

void Credits_Jumptable(void){
    // LD_A_addr(wJumptableIndex);
    // AND_A(0xf);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mCredits_Jumptable_Jumptable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;

// Jumptable:
    switch(wram->wJumptableIndex & 0xf) {
        //dw ['ParseCredits'];
        case 0x0: return ParseCredits();
        //dw ['Credits_Next'];
        case 0x1: return Credits_Next();
        //dw ['Credits_Next'];
        case 0x2: return Credits_Next();
        //dw ['Credits_PrepBGMapUpdate'];
        case 0x3: return Credits_PrepBGMapUpdate();
        //dw ['Credits_UpdateGFXRequestPath'];
        case 0x4: return Credits_UpdateGFXRequestPath();
        //dw ['Credits_RequestGFX'];
        case 0x5: return Credits_RequestGFX();
        //dw ['Credits_LYOverride'];
        case 0x6: return Credits_LYOverride();
        //dw ['Credits_Next'];
        case 0x7: return Credits_Next();
        //dw ['Credits_Next'];
        case 0x8: return Credits_Next();
        //dw ['Credits_Next'];
        case 0x9: return Credits_Next();
        //dw ['Credits_UpdateGFXRequestPath'];
        case 0xa: return Credits_UpdateGFXRequestPath();
        //dw ['Credits_RequestGFX'];
        case 0xb: return Credits_RequestGFX();
        //dw ['Credits_LoopBack'];
        default:
        case 0xc: return Credits_LoopBack();
    }
}

void Credits_Next(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;

}

void Credits_LoopBack(void){
    // LD_HL(wJumptableIndex);
    // LD_A_hl;
    // AND_A(0xf0);
    // LD_hl_A;
    wram->wJumptableIndex &= 0xf0;
    // RET;
}

void Credits_PrepBGMapUpdate(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // JP(mCredits_Next);
    return Credits_Next();
}

void Credits_UpdateGFXRequestPath(void){
    // CALL(aCredits_LoadBorderGFX);
    uint8_t* hl = Credits_LoadBorderGFX();
    // LD_A_L;
    // LD_addr_A(wRequested2bppSource);
    // LD_A_H;
    // LD_addr_A(wRequested2bppSource + 1);
    // LD_A(LOW(vTiles2));
    // LD_addr_A(wRequested2bppDest);
    // LD_A(HIGH(vTiles2));
    // LD_addr_A(wRequested2bppDest + 1);
    CopyBytes_Conv2(vram->vTiles2, hl, 16 * LEN_2BPP_TILE);
    // JR(mCredits_RequestGFX);
    return Credits_RequestGFX();
}

void Credits_RequestGFX(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // LD_A(8);
    // LD_addr_A(wRequested2bppSize);
    // JP(mCredits_Next);
    return Credits_Next();
}

static void Credits_LYOverride_Fill(uint8_t* hl, uint8_t a) {
// Fill:
    // LD_C(0x8);
    uint8_t c = 0x8;

    do {
    // loop:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void Credits_LYOverride(void){
    // LDH_A_addr(rLY);
    // CP_A(0x30);
    // JR_C (mCredits_LYOverride);
    // LD_A_addr(wCreditsLYOverride);
    uint8_t override = wram->wCreditsLYOverride - 2;
    // DEC_A;
    // DEC_A;
    // LD_addr_A(wCreditsLYOverride);
    wram->wCreditsLYOverride = override;
    // LD_HL(wLYOverrides + 0x1f);
    // CALL(aCredits_LYOverride_Fill);
    Credits_LYOverride_Fill(wram->wLYOverrides + 0x1f, override);
    // LD_HL(wLYOverrides + 0x87);
    // CALL(aCredits_LYOverride_Fill);
    Credits_LYOverride_Fill(wram->wLYOverrides + 0x87, override);
    // JP(mCredits_Next);
    return Credits_Next();
}

static uint8_t ParseCredits_get(void) {
//  Get byte wCreditsPos from CreditsScript
    // PUSH_HL;
    // PUSH_DE;
    // LD_A_addr(wCreditsPos);
    // LD_E_A;
    // LD_A_addr(wCreditsPos + 1);
    // LD_D_A;
    // LD_HL(mCreditsScript);
    // ADD_HL_DE;

    // INC_DE;
    // LD_A_E;
    // LD_addr_A(wCreditsPos);
    // LD_A_D;
    // LD_addr_A(wCreditsPos + 1);
    // LD_A_hl;
    // POP_DE;
    // POP_HL;
    // RET;
    return CreditsScript[wram->wCreditsPos++];
}

void ParseCredits(void){
    // LD_HL(wJumptableIndex);
    // BIT_hl(7);
    // JP_NZ (mParseCredits_done);
    if(bit_test(wram->wJumptableIndex, 7))
        return Credits_Next();

//  Wait until the timer has run out to parse the next command.
    // LD_HL(wCreditsTimer);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto parse;
    if(wram->wCreditsTimer != 0) {
    //  One tick has passed.
        // DEC_hl;
        --wram->wCreditsTimer;
        // JP(mParseCredits_done);
        return Credits_Next();
    }

// parse:
//  First, let's clear the current text display,
//  starting from line 5.
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // hlcoord(0, 5, wTilemap);
    // LD_BC(SCREEN_WIDTH * 12);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 5, wram->wTilemap), SCREEN_WIDTH * 12, 0x7f);

//  Then read the script.

    while(1) {
    // loop:
        // CALL(aParseCredits_get);
        uint8_t cmd = ParseCredits_get();

    //  Commands:
        switch(cmd) {
            // CP_A(CREDITS_END);
            // JP_Z (mParseCredits_end);
            case CREDITS_END:
            // end:
            //  Stop execution.
                // LD_HL(wJumptableIndex);
                // SET_hl(7);
                bit_set(wram->wJumptableIndex, 7);
                // LD_A(32);
                // LD_addr_A(wMusicFade);
                wram->wMusicFade = 32;
                // LD_A(LOW(MUSIC_POST_CREDITS));
                // LD_addr_A(wMusicFadeID);
                // LD_A(HIGH(MUSIC_POST_CREDITS));
                // LD_addr_A(wMusicFadeID + 1);
                wram->wMusicFadeID = MUSIC_POST_CREDITS;
                // RET;
                return;
            // CP_A(CREDITS_WAIT);
            // IF_Z goto wait;
            case CREDITS_WAIT:
            // wait:
            //  Wait for some amount of ticks, and do something else.
                // CALL(aParseCredits_get);
                // LD_addr_A(wCreditsTimer);
                wram->wCreditsTimer = ParseCredits_get();

                // XOR_A_A;
                // LDH_addr_A(hBGMapThird);
                hram->hBGMapThird = 0x0;
                // LD_A(1);
                // LDH_addr_A(hBGMapMode);
                hram->hBGMapMode = 1;

            // done:
                // JP(mCredits_Next);
                return Credits_Next();
            // CP_A(CREDITS_SCENE);
            // IF_Z goto scene;
            case CREDITS_SCENE:
            // scene:
            //  Update the scene number and corresponding palette.
                // CALL(aParseCredits_get);
                // LD_addr_A(wCreditsBorderMon);  // scene
                wram->wCreditsBorderMon = ParseCredits_get();
                // XOR_A_A;
                // LD_addr_A(wCreditsBorderFrame);  // frame
                wram->wCreditsBorderFrame = 0x0;
                // CALL(aGetCreditsPalette);
                GetCreditsPalette();
                // CALL(aSetPalettes);  // update hw pal registers
                SetPalettes_Conv();
                // goto loop;
                continue;
            // CP_A(CREDITS_CLEAR);
            // IF_Z goto clear;
            case CREDITS_CLEAR:
            // clear:
            //  Clear the banner.
                // LD_A(0xff);
                // LD_addr_A(wCreditsBorderFrame);  // frame
                wram->wCreditsBorderFrame = 0xff;
                // goto loop;
                continue;
            // CP_A(CREDITS_MUSIC);
            // IF_Z goto music;
            case CREDITS_MUSIC:
            // music:
            //  Play the credits music.
                // LD_DE(MUSIC_CREDITS);
                // PUSH_DE;
                // LD_DE(MUSIC_NONE);
                // CALL(aPlayMusic);
                PlayMusic_Conv(MUSIC_NONE);
                // CALL(aDelayFrame);
                DelayFrame();
                // POP_DE;
                // CALL(aPlayMusic);
                PlayMusic_Conv(MUSIC_CREDITS);
                // JP(mParseCredits_loop);
                continue;
            // CP_A(CREDITS_WAIT2);
            // IF_Z goto wait2;
            case CREDITS_WAIT2:
            // wait2:
            //  Wait for some amount of ticks.
                // CALL(aParseCredits_get);
                // LD_addr_A(wCreditsTimer);
                wram->wCreditsTimer = ParseCredits_get();
                // goto done;
                return Credits_Next();
            // CP_A(CREDITS_THEEND);
            // IF_Z goto theend;
            case CREDITS_THEEND:
            // theend:
            //  Display "The End" graphic.
                // CALL(aCredits_TheEnd);
                Credits_TheEnd();
                // goto loop;
                continue;
            default: {
                //  If it's not a command, it's a string identifier.
                // PUSH_AF;
                // LD_E_A;
                // LD_D(0);
                // LD_HL(mCreditsStringsPointers);
                // ADD_HL_DE;
                // ADD_HL_DE;
                // LD_A_hli;
                // LD_D_hl;
                // LD_E_A;
                // POP_AF;
                const char* string = CreditsStringsPointers[cmd];
                uint8_t* str;
                tile_t* dest;

            //  Strings spanning multiple lines have special cases.

                // CP_A(COPYRIGHT);
                // IF_Z goto copyright;

                // CP_A(STAFF);
                // IF_C goto staff;
                if(cmd == COPYRIGHT) {
                    str = (uint8_t*)Credits_Copyright; // To get around type qualifier errors.
                    dest = coord(2, 6, wram->wTilemap);
                }
                else {
                    str = U82C(string);
                    dest = coord(0, 6, wram->wTilemap);
                }

            //  The rest start from line 6.

                // hlcoord(0, 6, wTilemap);
                // goto print;

            // copyright:
                // hlcoord(2, 6, wTilemap);
                // goto print;

            // staff:
                // hlcoord(0, 6, wTilemap);

            // print:
            //  Print strings spaced every two lines.
                // CALL(aParseCredits_get);
                uint8_t line = ParseCredits_get();
                // LD_BC(SCREEN_WIDTH * 2);
                // CALL(aAddNTimes);
                // CALL(aPlaceString);
                PlaceStringSimple(str, dest + (SCREEN_WIDTH * 2) * line);
                // goto loop;
            } continue;
        }
    }
}

static void ConstructCreditsTilemap_InitTopPortion(tile_t* hl) {
    // LD_B(5);
    uint8_t b = 5;

    do {
    // outer_loop:
        // PUSH_HL;
        tile_t* hl2 = hl;
        // LD_DE(SCREEN_WIDTH - 3);
        // LD_C(4);
        uint8_t c = 4;
        // XOR_A_A;
        uint8_t a = 0;

        do {
        // inner_loop:
            // for(int rept = 0; rept < 3; rept++){
            // LD_hli_A;
            *(hl2++) = a++;
            *(hl2++) = a++;
            *(hl2++) = a++;
            // INC_A;
            // }
            // LD_hl_A;
            // INC_A;
            *hl2 = a++;
            // ADD_HL_DE;
            hl2 += SCREEN_WIDTH - 3;
            // DEC_C;
            // IF_NZ goto inner_loop;
        } while(--c != 0);
        // POP_HL;
        // for(int rept = 0; rept < 4; rept++){
        // INC_HL;
        // }
        hl += 4;
        // DEC_B;
        // IF_NZ goto outer_loop;
    } while(--b != 0);
    // RET;
}

void ConstructCreditsTilemap(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // LD_A(0xc);
    // LDH_addr_A(hBGMapAddress);
    hram->hBGMapAddress = (hram->hBGMapAddress & 0xff00) | 0xc;

    // LD_A(0x28);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x28);

    // LD_A(0x7f);
    // hlcoord(0, 4, wTilemap);
    // LD_BC((SCREEN_HEIGHT - 4) * SCREEN_WIDTH);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 4, wram->wTilemap), (SCREEN_HEIGHT - 4) * SCREEN_WIDTH, 0x7f);

    // hlcoord(0, 4, wTilemap);
    // LD_A(0x24);
    // CALL(aDrawCreditsBorder);
    DrawCreditsBorder(coord(0, 4, wram->wTilemap), 0x24);

    // hlcoord(0, 17, wTilemap);
    // LD_A(0x20);
    // CALL(aDrawCreditsBorder);
    DrawCreditsBorder(coord(0, 17, wram->wTilemap), 0x20);

    // hlcoord(0, 0, wAttrmap);
    // LD_BC(4 * SCREEN_WIDTH);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wAttrmap), 4 * SCREEN_WIDTH, 0x0);

    // hlcoord(0, 4, wAttrmap);
    // LD_BC(SCREEN_WIDTH);
    // LD_A(0x1);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 4, wram->wAttrmap), SCREEN_WIDTH, 0x1);

    // hlcoord(0, 5, wAttrmap);
    // LD_BC(12 * SCREEN_WIDTH);
    // LD_A(0x2);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 5, wram->wAttrmap), 12 * SCREEN_WIDTH, 0x2);

    // hlcoord(0, 17, wAttrmap);
    // LD_BC(SCREEN_WIDTH);
    // LD_A(0x1);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 17, wram->wAttrmap), SCREEN_WIDTH, 0x1);

    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x0;
    // LDH_addr_A(hBGMapAddress);
    hram->hBGMapAddress = (hram->hBGMapAddress & 0xff00) | 0x0;
    // hlcoord(0, 0, wTilemap);
    // CALL(aConstructCreditsTilemap_InitTopPortion);
    ConstructCreditsTilemap_InitTopPortion(coord(0, 0, wram->wTilemap));
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // RET;

}

void DrawCreditsBorder(tile_t* hl, uint8_t a){
    // LD_C(SCREEN_WIDTH / 4);
    uint8_t c = SCREEN_WIDTH / 4;

    do {
    // loop:
        // PUSH_AF;
        uint8_t a2 = a;
        // for(int rept = 0; rept < 3; rept++){
        // LD_hli_A;
        *(hl++) = a2++;
        *(hl++) = a2++;
        *(hl++) = a2++;
        // INC_A;
        // }
        // LD_hli_A;
        *(hl++) = a2;
        // POP_AF;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

//  Each set of palette data is 24 bytes long.
static const uint16_t* GetCreditsPalette_GetPalAddress(void) {
    // LD_A_addr(wCreditsBorderMon);  // scene
    // AND_A(0b11);
    // ADD_A_A;
    // ADD_A_A;  // * 8
    // ADD_A_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mCreditsPalettes);
    // ADD_HL_DE;
    // ADD_HL_DE;  // * 3
    // ADD_HL_DE;
    // RET;
    return CreditsPalettes + 12 * (wram->wCreditsBorderMon & 0b11);
}

static void GetCreditsPalette_UpdatePals(const uint16_t* hl, uint8_t a) {
//  Update the first three colors in both palette buffers.
    // PUSH_AF;
    // PUSH_HL;
    // ADD_A(LOW(wBGPals1));
    // LD_E_A;
    // LD_A(0);
    // ADC_A(HIGH(wBGPals1));
    // LD_D_A;
    // LD_BC(24);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wBGPals1 + a, hl, 24);

    // POP_HL;
    // POP_AF;
    // ADD_A(LOW(wBGPals2));
    // LD_E_A;
    // LD_A(0);
    // ADC_A(HIGH(wBGPals2));
    // LD_D_A;
    // LD_BC(24);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wBGPals2 + a, hl, 24);
    // RET;
}

void GetCreditsPalette(void){
    // CALL(aGetCreditsPalette_GetPalAddress);
    const uint16_t* pal = GetCreditsPalette_GetPalAddress();

    // PUSH_HL;
    // LD_A(0);
    // CALL(aGetCreditsPalette_UpdatePals);
    GetCreditsPalette_UpdatePals(pal, 0);

    // POP_HL;
    // RET;

}

const uint16_t CreditsPalettes[] = {
// INCLUDE "gfx/credits/credits.pal"
// pichu
    rgb(31, 0,31), rgb(31,25, 0), rgb(11,14,31), rgb( 7, 7, 7),
    rgb(31, 5, 5), rgb(11,14,31), rgb(11,14,31), rgb(31,31,31),
    rgb(31, 5, 5), rgb( 0, 0, 0), rgb(31,31,31), rgb(31,31,31),

// smoochum
    rgb(31,31,31), rgb(31,27, 0), rgb(26, 6,31), rgb( 7, 7, 7),
    rgb( 3,13,31), rgb(20, 0,24), rgb(26, 6,31), rgb(31,31,31),
    rgb( 3,13,31), rgb( 0, 0, 0), rgb(31,31,31), rgb(31,31,31),

// ditto
    rgb(31,31,31), rgb(23,12,28), rgb(31,22, 0), rgb( 7, 7, 7),
    rgb( 3,20, 0), rgb(31,22, 0), rgb(31,22, 0), rgb(31,31,31),
    rgb( 3,20, 0), rgb( 0, 0, 0), rgb(31,31,31), rgb(31,31,31),

// igglybuff
    rgb(31,31,31), rgb(31,10,31), rgb(31, 0, 9), rgb( 7, 7, 7),
    rgb(31,14, 0), rgb(31, 0, 9), rgb(31, 0, 9), rgb(31,31,31),
    rgb(31,14, 0), rgb(31,31,31), rgb(31,31,31), rgb(31,31,31),
};

uint8_t* Credits_LoadBorderGFX(void){
    struct FrameOffset {
        const char* path;
        uint8_t offset;
    };
    static const struct FrameOffset Frames[] = {
        {CreditsPichuGFX,  0},
        {CreditsPichuGFX, 16},
        {CreditsPichuGFX, 32},
        {CreditsPichuGFX, 48},

        {CreditsSmoochumGFX,  0},
        {CreditsSmoochumGFX, 16},
        {CreditsSmoochumGFX, 32},
        {CreditsSmoochumGFX, 48},

        {CreditsDittoGFX,  0},
        {CreditsDittoGFX, 16},
        {CreditsDittoGFX, 32},
        {CreditsDittoGFX, 48},

        {CreditsIgglybuffGFX,  0},
        {CreditsIgglybuffGFX, 16},
        {CreditsIgglybuffGFX, 32},
        {CreditsIgglybuffGFX, 48},
    };
    // LD_HL(wCreditsBorderFrame);
    uint8_t frame = wram->wCreditsBorderFrame;
    // LD_A_hl;
    // CP_A(0xff);
    // IF_Z goto init;
    if(frame == 0xff)
        return wram->wCreditsBlankFrame2bpp;

    // AND_A(0b11);
    // LD_E_A;
    uint8_t e = frame & 0b11;
    // INC_A;
    // AND_A(0b11);
    // LD_hl_A;
    wram->wCreditsBorderFrame = (e + 1) & 0b11;
    // LD_A_addr(wCreditsBorderMon);
    // AND_A(0b11);
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_E;
    // ADD_A_A;
    // LD_E_A;
    // LD_D(0);
    const struct FrameOffset FrameOffset = Frames[((wram->wCreditsBorderMon & 0b11) << 2) + e];
    // LD_HL(mCredits_LoadBorderGFX_Frames);
    LoadPNG2bppAssetSectionToVRAM(wram->wCreditsBlankFrame2bpp, FrameOffset.path, FrameOffset.offset, 16);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // RET;
    return wram->wCreditsBlankFrame2bpp;

// init:
    // LD_HL(wCreditsBlankFrame2bpp);
    // RET;
}

static void Credits_TheEnd_Load(tile_t* hl, uint8_t* a) {
    // LD_C(8);
    uint8_t c = 8;

    do {
    // loop:
        // LD_hli_A;
        *(hl++) = *a;
        // INC_A;
        (*a)++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void Credits_TheEnd(void){
    // LD_A(0x40);
    uint8_t a = 0x40;
    // hlcoord(6, 9, wTilemap);
    // CALL(aCredits_TheEnd_Load);
    Credits_TheEnd_Load(coord(6, 9, wram->wTilemap), &a);
    // hlcoord(6, 10, wTilemap);
    return Credits_TheEnd_Load(coord(6, 10, wram->wTilemap), &a);
}

const char CreditsBorderGFX[] = "gfx/credits/border.png";

// void CreditsMonsGFX(void){
//  //  used only for BANK(CreditsMonsGFX)
//     return CreditsPichuGFX();
// }

const char CreditsPichuGFX[] = "gfx/credits/pichu.png";
const char CreditsSmoochumGFX[] = "gfx/credits/smoochum.png";
const char CreditsDittoGFX[] = "gfx/credits/ditto.png";
const char CreditsIgglybuffGFX[] = "gfx/credits/igglybuff.png";

// INCLUDE "data/credits_script.asm"
// INCLUDE "data/credits_strings.asm"
