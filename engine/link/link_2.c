#include "../../constants.h"
#include "link_2.h"
#include "../../home/audio.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../pokemon/stats_screen.h"
#include "link.h"
#include "link_trade.h"
#include "../../charmap.h"

void LinkMonStatsScreen(void){
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wMenuCursorY - 1;
    // CALL(aLowVolume);
    LowVolume();
    // PREDEF(pStatsScreenInit);
    StatsScreenInit();
    // LD_A_addr(wCurPartyMon);
    // INC_A;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = wram->wCurPartyMon + 1;
    // CALL(aClearScreen);
    ClearScreen();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aMaxVolume);
    MaxVolume();
    // FARCALL(aLoadTradeScreenBorderGFX);
    LoadTradeScreenBorderGFX();
    // FARCALL(aLink_WaitBGMap);
    Link_WaitBGMap();
    // FARCALL(aInitTradeSpeciesList);
    InitTradeSpeciesList();
    // FARCALL(aSetTradeRoomBGPals);
    SetTradeRoomBGPals();
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // RET;
}

void Link_WaitBGMap(void){
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // RET;
}

static tile_t* LinkTextbox2_PlaceRow(tile_t* hl, uint8_t c, uint8_t a) {
    // LD_D_C;

    for(uint32_t i = 0; i < c; ++i) {
    // row_loop:
        // LD_hli_A;
        hl[i] = a;
        // DEC_D;
        // IF_NZ goto row_loop;
    }
    // RET;
    return hl + c;
}

static void LinkTextbox2_PlaceBorder(tile_t* hl, uint8_t b, uint8_t c) {
    // PUSH_HL;
    tile_t* hl2 = hl;
    // LD_A(0x76);
    // LD_hli_A;
    *(hl++) = 0x76;
    // INC_A;
    // CALL(aLinkTextbox2_PlaceRow);
    hl = LinkTextbox2_PlaceRow(hl, c, 0x77);
    // INC_A;
    // LD_hl_A;
    *hl = 0x78;
    // POP_HL;
    // LD_DE(SCREEN_WIDTH);
    // ADD_HL_DE;
    hl = hl2 + SCREEN_WIDTH;

    do {
    // loop:
        // PUSH_HL;
        hl2 = hl;
        // LD_A(0x79);
        // LD_hli_A;
        *(hl++) = CHAR_FRAME_TOP_LEFT;
        // LD_A(0x7f);
        // CALL(aLinkTextbox2_PlaceRow);
        hl = LinkTextbox2_PlaceRow(hl, c, CHAR_SPACE);
        // LD_hl(0x7a);
        *hl = CHAR_FRAME_TOP;
        // POP_HL;
        // LD_DE(SCREEN_WIDTH);
        // ADD_HL_DE;
        hl = hl2 + SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);

    // LD_A(0x7b);
    // LD_hli_A;
    *(hl++) = CHAR_FRAME_TOP_RIGHT;
    // LD_A(0x7c);
    // CALL(aLinkTextbox2_PlaceRow);
    hl = LinkTextbox2_PlaceRow(hl, c, CHAR_FRAME_SIDE);
    // LD_hl(0x7d);
    *hl = CHAR_FRAME_BOTTOM_LEFT;
    // RET;
}


void LinkTextbox2(tile_t* de, uint8_t b, uint8_t c){
    // LD_H_D;
    // LD_L_E;
    // PUSH_BC;
    // PUSH_HL;
    // CALL(aLinkTextbox2_PlaceBorder);
    LinkTextbox2_PlaceBorder(de, b, c);
    // POP_HL;
    // POP_BC;

    // LD_DE(wAttrmap - wTilemap);
    // ADD_HL_DE;
    uint8_t* hl = wram->wAttrmap + (de - wram->wTilemap);
    // INC_B;
    // INC_B;
    b += 2;
    // INC_C;
    // INC_C;
    c += 2;
    // LD_A(PAL_BG_TEXT);

    do {
    // row:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // col:
            // LD_hli_A;
            *(hl++) = PAL_BG_TEXT;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // POP_HL;
        // LD_DE(SCREEN_WIDTH);
        // ADD_HL_DE;
        hl = hl2 + SCREEN_WIDTH;
        // POP_BC;
        c = c2;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}
