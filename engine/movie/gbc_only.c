#include "../../constants.h"
#include "gbc_only.h"
#include "../../home/audio.h"
#include "../../home/delay.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../gfx/font.h"

static const char GBCOnlyString[] = "This Game Pak is"\
    t_next "designed only for" \
    t_next "use on the" \
    t_next "Game Boy Color.@";

static const char GBCOnlyGFX[] = "gfx/sgb/gbc_only.png";

void GBCOnlyScreen(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_NZ ;
    if(hram->hCGB != 0)
        return;

    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_NONE);

    // CALL(aClearTilemap);
    ClearTilemap_Conv2();

    // LD_HL(mGBCOnlyGFX);
    // LD_DE(wGBCOnlyDecompressBuffer);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0);  // this has the same effect as selecting bank 1
    // LDH_addr_A(rSVBK);
    // CALL(aDecompress);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    GetSGBLayout_Conv(SCGB_1E);
    SetPalettes_Conv();

    // LD_DE(wGBCOnlyDecompressBuffer);
    // LD_HL(vTiles2);
    // LD_BC((BANK(aGBCOnlyGFX) << 8) | 84);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, GBCOnlyGFX, 0, 84);

    // LD_DE(mFont);
    // LD_HL(vTiles1);
    // LD_BC((BANK(aFont) << 8) | 0x80);
    // CALL(aGet1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles1, Font, 0, 0x80);

    // CALL(aDrawGBCOnlyScreen);
    DrawGBCOnlyScreen();

    // CALL(aWaitBGMap);
    WaitBGMap_Conv();

//  better luck next time

    while(1) {
    // loop:
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }
}

void DrawGBCOnlyScreen(void){
    // CALL(aDrawGBCOnlyBorder);
    DrawGBCOnlyBorder();

// Pokemon
    // hlcoord(3, 2, wTilemap);
    // LD_B(14);
    // LD_C(4);
    // LD_A(0x8);
    // CALL(aDrawGBCOnlyGraphic);
    DrawGBCOnlyGraphic(coord(3, 2, wram->wTilemap), 14, 4, 0x8);

// Crystal
    // hlcoord(5, 6, wTilemap);
    // LD_B(10);
    // LD_C(2);
    // LD_A(0x40);
    // CALL(aDrawGBCOnlyGraphic);
    DrawGBCOnlyGraphic(coord(5, 6, wram->wTilemap), 10, 2, 0x40);

    // LD_DE(mGBCOnlyString);
    // hlcoord(1, 10, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(GBCOnlyString), coord(1, 10, wram->wTilemap));

    // RET;
}

static uint8_t* DrawGBCOnlyBorder_FillRow(uint8_t* hl, uint8_t a) {
    // LD_C(SCREEN_WIDTH - 2);
    uint8_t c = SCREEN_WIDTH - 2;

    do {
    // next_column:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_C;
        // IF_NZ goto next_column;
    } while(--c != 0);
    return hl;
}

static void DrawGBCOnlyBorder_FillColumn(uint8_t* hl, uint8_t a) {
    // LD_DE(SCREEN_WIDTH);
    // LD_C(SCREEN_HEIGHT - 2);
    uint8_t c = SCREEN_WIDTH - 2;

    do {
    // next_row:
        // LD_hl_A;
        *hl = a;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_C;
        // IF_NZ goto next_row;
    } while(--c != 0);
    // RET;
}

void DrawGBCOnlyBorder(void){
    uint8_t* hl;
    // hlcoord(0, 0, wTilemap);
    // LD_hl(0);  // top-left
    *coord(0, 0, wram->wTilemap) = 0;

    // INC_HL;
    // LD_A(1);  // top
    hl = DrawGBCOnlyBorder_FillRow(coord(1, 0, wram->wTilemap), 1);
    // CALL(aDrawGBCOnlyBorder_FillRow);
    

    // LD_hl(2);  // top-right
    *hl = 2;

    // hlcoord(0, 1, wTilemap);
    // LD_A(3);  // left
    // CALL(aDrawGBCOnlyBorder_FillColumn);
    DrawGBCOnlyBorder_FillColumn(coord(0, 1, wram->wTilemap), 3);

    // hlcoord(19, 1, wTilemap);
    // LD_A(4);  // right
    // CALL(aDrawGBCOnlyBorder_FillColumn);
    DrawGBCOnlyBorder_FillColumn(coord(19, 1, wram->wTilemap), 4);

    // hlcoord(0, 17, wTilemap);
    // LD_hl(5);  // bottom-left
    *coord(0, 17, wram->wTilemap) = 5;

    // INC_HL;
    // LD_A(6);  // bottom
    // CALL(aDrawGBCOnlyBorder_FillRow);
    hl = DrawGBCOnlyBorder_FillRow(coord(1, 17, wram->wTilemap), 6);

    // LD_hl(7);  // bottom-right
    *hl = 7;
    // RET;
}

void DrawGBCOnlyGraphic(uint8_t* hl, uint8_t b, uint8_t c, uint8_t a){
    // LD_DE(SCREEN_WIDTH);

    do {
    // y:
        // PUSH_BC;
        uint8_t b2 = b;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // x:
            // LD_hli_A;
            // INC_A;
            *(hl++) = a++;
            // DEC_B;
            // IF_NZ goto x;
        } while(--b != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl = hl2 + SCREEN_WIDTH;
        // POP_BC;
        b = b2;
        // DEC_C;
        // IF_NZ goto y;
    } while(--c != 0);
    // RET;
}


static void DrawErrorScreen(const char* text){
    DrawGBCOnlyBorder();

// Pokemon
    DrawGBCOnlyGraphic(coord(3, 2, wram->wTilemap), 14, 4, 0x8);

// Crystal
    DrawGBCOnlyGraphic(coord(5, 6, wram->wTilemap), 10, 2, 0x40);

    PlaceStringSimple(U82C(text), coord(1, 10, wram->wTilemap));
}

void ErrorScreen(const char* text){
    PlayMusic_Conv(MUSIC_NONE);
    ClearTilemap_Conv2();
    GetSGBLayout_Conv(SCGB_1E);
    SetPalettes_Conv();
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, GBCOnlyGFX, 0, 84);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles1, Font, 0, 0x80);
    DrawErrorScreen(text);
    WaitBGMap_Conv();

//  better luck next time

    while(1) {
        DelayFrame();
    }
}
