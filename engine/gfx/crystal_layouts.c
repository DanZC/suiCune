#include "../../constants.h"
#include "crystal_layouts.h"
#include "../../home/copy.h"
#include "color.h"

static tile_t* Crystal_FillBoxCGB(tile_t* hl, uint8_t b, uint8_t c, uint8_t a);

static const uint16_t Palette_TextBG7[] = {
    rgb(31, 31, 31),
    rgb( 8, 19, 28),
    rgb( 5,  5, 16),
    rgb( 0,  0,  0),
};

void GetCrystalCGBLayout(uint8_t b){
    // LD_A_B;
    // CP_A(SCGB_DEFAULT);
    // IF_NZ goto not_default;
    // LD_A_addr(wDefaultSGBLayout);
    if(b == SCGB_DEFAULT) {
        b = wram->wDefaultSGBLayout;
    }

// not_default:
    // PUSH_AF;
    // FARCALL(aResetBGPals);
    ResetBGPals();
    // POP_AF;
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_HL;
    // LD_DE(mGetCrystalCGBLayout_Jumptable);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(mGetCrystalCGBLayout_done);
    // PUSH_DE;
    // JP_hl;

// done:
    // RET;


// Jumptable:
    switch(b) {
        case CRYSTAL_CGB_MOBILE_0:  return v_CrystalCGB_MobileLayout0(); //dw ['_CrystalCGB_MobileLayout0'];
        case CRYSTAL_CGB_MOBILE_1:  return v_CrystalCGB_MobileLayout1(); //dw ['_CrystalCGB_MobileLayout1'];
        case CRYSTAL_CGB_NAME_CARD: return v_CrystalCGB_NameCard(); //dw ['_CrystalCGB_NameCard'];
    }
}

//  This is a copy of FillBoxCGB.
static tile_t* Crystal_FillBoxCGB(tile_t* hl, uint8_t b, uint8_t c, uint8_t a){

// row:
    // PUSH_BC;
    // PUSH_HL;

// col:
    // LD_hli_A;
    // DEC_C;
    // IF_NZ goto col;
    // POP_HL;
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    // POP_BC;
    // DEC_B;
    // IF_NZ goto row;
    // RET;
    return FillBoxCGB(hl, b, c, a);
}

void Crystal_WipeAttrmap(void){
//  This is a copy of WipeAttrmap.
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // XOR_A_A;
    // CALL(aByteFill);
    // RET;
    return ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_HEIGHT * SCREEN_WIDTH, 0);
}

void MG_Mobile_Layout_LoadPals(void){
    // LD_DE(wBGPals1);
    // LD_HL(mPalette_MysteryGiftMobile);
    // LD_BC(5 * PALETTE_SIZE);
    // LD_A(MBANK(awBGPals1));
    // CALL(aFarCopyWRAM);
    LoadPaletteAssetColorsToArray(wram->wBGPals1, Palette_MysteryGiftMobile, 0, 5 * NUM_PAL_COLORS);
    // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
    // LD_HL(mPalette_TextBG7);
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(MBANK(awBGPals1));
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT, Palette_TextBG7, sizeof(Palette_TextBG7));
    // RET;
}

void v_CrystalCGB_MobileLayout0(void){
    // CALL(aMG_Mobile_Layout_LoadPals);
    MG_Mobile_Layout_LoadPals();
    // CALL(aCrystal_WipeAttrmap);
    Crystal_WipeAttrmap();
    // CALL(aMG_Mobile_Layout_CreatePalBoxes);
    MG_Mobile_Layout_CreatePalBoxes();
    // FARCALL(aApplyAttrmap);
    ApplyAttrmap();
    // FARCALL(aApplyPals);
    ApplyPals();
    // RET;
}

void MG_Mobile_Layout_CreatePalBoxes(void){
    // hlcoord(0, 0, wAttrmap);
    // LD_BC((4 << 8) | 1);
    // LD_A(0x1);
    // CALL(aCrystal_FillBoxCGB);
    tile_t* hl = Crystal_FillBoxCGB(coord(0, 0, wram->wAttrmap), 4, 1, 0x1);
    // LD_BC((2 << 8) | 1);
    // LD_A(0x2);
    // CALL(aCrystal_FillBoxCGB);
    hl = Crystal_FillBoxCGB(hl, 2, 1, 0x2);
    // LD_BC((6 << 8) | 1);
    // LD_A(0x3);
    // CALL(aCrystal_FillBoxCGB);
    hl = Crystal_FillBoxCGB(hl, 6, 8, 0x3);
    // hlcoord(1, 0, wAttrmap);
    // LD_A(0x1);
    // LD_BC((3 << 8) | 18);
    // CALL(aCrystal_FillBoxCGB);
    hl = Crystal_FillBoxCGB(coord(1, 0, wram->wAttrmap), 3, 18, 0x1);
    // LD_BC((2 << 8) | 18);
    // LD_A(0x2);
    // CALL(aCrystal_FillBoxCGB);
    hl = Crystal_FillBoxCGB(hl, 2, 18, 0x2);
    // LD_BC((12 << 8) | 18);
    // LD_A(0x3);
    // CALL(aCrystal_FillBoxCGB);
    hl = Crystal_FillBoxCGB(hl, 12, 18, 0x3);
    // hlcoord(19, 0, wAttrmap);
    // LD_BC((4 << 8) | 1);
    // LD_A(0x1);
    // CALL(aCrystal_FillBoxCGB);
    hl = Crystal_FillBoxCGB(coord(19, 0, wram->wAttrmap), 4, 1, 0x1);
    // LD_BC((2 << 8) | 1);
    // LD_A(0x2);
    // CALL(aCrystal_FillBoxCGB);
    hl = Crystal_FillBoxCGB(hl, 2, 1, 0x2);
    // LD_BC((6 << 8) | 1);
    // LD_A(0x3);
    // CALL(aCrystal_FillBoxCGB);
    hl = Crystal_FillBoxCGB(hl, 6, 1, 0x3);
    // hlcoord(0, 12, wAttrmap);
    // LD_BC(6 * SCREEN_WIDTH);
    // LD_A(0x7);
    // CALL(aByteFill);
    ByteFill(coord(0, 12, wram->wAttrmap), 6 * SCREEN_WIDTH, 0x7);
    // RET;
}

const char Palette_MysteryGiftMobile[] = "gfx/mystery_gift/mg_mobile.pal";

void LoadOW_BGPal7(void){
    // LD_HL(mPalette_TextBG7);
    // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT, Palette_TextBG7, 1 * PALETTE_SIZE);
    // RET;
}

// void Palette_TextBG7(void){
// // INCLUDE "gfx/font/bg_text.pal"

//     return Function49420();
// }

// CopyMansionPalRoof
void Function49420(void){
    // LD_HL(mMansionPalette1 + 8 * PALETTE_SIZE);
    // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_ROOF);
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_ROOF, MansionPalette1 + 8 * NUM_PAL_COLORS, PALETTE_SIZE);
    // RET;
}

static void Function49480(void) {
    // hlcoord(0, 0, wAttrmap);
    // LD_BC((4 << 8) | SCREEN_WIDTH);
    // LD_A(0x7);
    // CALL(aCrystal_FillBoxCGB);
    Crystal_FillBoxCGB(coord(0, 0, wram->wAttrmap), 4, SCREEN_WIDTH, 0x7);
    // hlcoord(0, 2, wAttrmap);
    // LD_A(0x4);
    // LD_hl_A;
    *coord(0, 2, wram->wAttrmap) = 0x4;
    // hlcoord(19, 2, wAttrmap);
    // LD_hl_A;
    *coord(19, 2, wram->wAttrmap) = 0x4;
    // RET;
}

static void Function49496(void) {
    // hlcoord(0, 0, wAttrmap);
    // LD_BC((2 << 8) | SCREEN_WIDTH);
    // LD_A(0x7);
    // CALL(aCrystal_FillBoxCGB);
    Crystal_FillBoxCGB(coord(0, 0, wram->wAttrmap), 2, SCREEN_WIDTH, 0x7);
    // hlcoord(0, 1, wAttrmap);
    // LD_A(0x4);
    // LD_hl_A;
    *coord(0, 1, wram->wAttrmap) = 0x4;
    // hlcoord(19, 1, wAttrmap);
    // LD_hl_A;
    *coord(19, 1, wram->wAttrmap) = 0x4;
    // RET;
}

void v_CrystalCGB_MobileLayout1(void){
    static const char TextPalette[] = "gfx/mystery_gift/mobile_text.pal";
    // CALL(aMG_Mobile_Layout_LoadPals);
    MG_Mobile_Layout_LoadPals();
    // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
    // LD_HL(mv_CrystalCGB_MobileLayout1_TextPalette);
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // CALL(aFarCopyWRAM);
    LoadPaletteAssetToBuffer(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT, 1 * PALETTE_SIZE, TextPalette, 1 * PAL_COLOR_SIZE);
    // CALL(aCrystal_WipeAttrmap);
    Crystal_WipeAttrmap();
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x0);
    // hlcoord(0, 14, wAttrmap);
    // LD_BC(4 * SCREEN_WIDTH);
    // LD_A(0x7);
    // CALL(aByteFill);
    ByteFill(coord(0, 14, wram->wAttrmap), SCREEN_WIDTH * 4, 0x7);
    // LD_A_addr(wd002);
    // BIT_A(6);
    // IF_Z goto asm_49464;
    if(bit_test(wram->wd002, 6)) {
        // CALL(av_CrystalCGB_MobileLayout1_Function49480);
        Function49480();
        // goto done;
    }
    else {
    // asm_49464:
        // CALL(av_CrystalCGB_MobileLayout1_Function49496);
        Function49496();
    }

// done:
    // FARCALL(aApplyAttrmap);
    ApplyAttrmap();
    // FARCALL(aApplyPals);
    ApplyPals();
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;

// INCLUDE "engine/tilesets/tileset_palettes.asm"
}

void v_CrystalCGB_NameCard(void){
static const char BGPalette[] = "gfx/mystery_gift/name_card_bg.pal";
static const char OBPalette[] = "gfx/mystery_gift/name_card_ob.pal";
    // LD_HL(mv_CrystalCGB_NameCard_BGPalette);
    // LD_DE(wBGPals1);
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // CALL(aFarCopyWRAM);
    LoadPaletteAssetToBuffer(wram->wBGPals1, 1 * PALETTE_SIZE, BGPalette, 1 * PAL_COLOR_SIZE);
    // FARCALL(aApplyPals);
    ApplyPals();
    // CALL(aCrystal_WipeAttrmap);
    Crystal_WipeAttrmap();
    // FARCALL(aApplyAttrmap);
    ApplyAttrmap();
    // LD_HL(mv_CrystalCGB_NameCard_OBPalette);
    // LD_DE(wOBPals1);
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(BANK(wOBPals1));
    // CALL(aFarCopyWRAM);
    LoadPaletteAssetToBuffer(wram->wOBPals1, 1 * PALETTE_SIZE, OBPalette, 1 * PAL_COLOR_SIZE);
    // RET;
}

void Function49742(void){
    static const uint16_t MobileBorderPalettes[] = {
    // INCLUDE "gfx/trade/mobile_border.pal"
        0xffff, // RGB 31, 31, 63
        rgb( 0,  0,  0),
        rgb( 0,  0,  0),
        rgb( 0,  0,  0),
    
        0xffff, // RGB 31, 31, 63
        rgb( 0,  0,  0),
        rgb( 0,  0,  0),
        rgb( 0,  0,  0),
    
        rgb( 4,  2, 15),
        rgb(21,  0, 21),
        rgb(31,  0,  0),
        rgb(31, 31, 31),
    
        rgb( 4,  2, 15),
        rgb(21,  0, 21),
        rgb(30, 16, 26),
        rgb(31, 31, 31),
    
        rgb( 4,  2, 15),
        rgb(21,  0, 21),
        rgb(16, 16, 16),
        rgb(31, 31, 31),
    
        rgb( 4,  2, 15),
        rgb(21,  0, 21),
        rgb(31, 12, 12),
        rgb(31, 31, 31),
    
        rgb( 4,  2, 15),
        rgb(21,  0, 21),
        rgb( 7,  8, 31),
        rgb(31, 31, 31),
    
        rgb( 4,  2, 15),
        rgb(21,  0, 21),
        rgb(29, 28,  9),
        rgb(31, 31, 31),
    };
    // LD_HL(mFunction49742_MobileBorderPalettes);
    // LD_DE(wBGPals1);
    // LD_BC(8 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1, MobileBorderPalettes, 8 * PALETTE_SIZE);
    // FARCALL(aApplyPals);
    ApplyPals();
    // RET;
}

void v_InitMG_Mobile_LinkTradePalMap(void){
    // hlcoord(0, 0, wAttrmap);
    // LD_BC((16 << 8) | 2);
    // LD_A(0x4);
    // CALL(aCrystal_FillBoxCGB);
    Crystal_FillBoxCGB(coord(0, 0, wram->wAttrmap), 16, 2, 0x4);
    // LD_A(0x3);
    // ldcoord_a(0, 1, wAttrmap);
    *coord(0, 1, wram->wAttrmap) = 0x3;
    // ldcoord_a(0, 14, wAttrmap);
    *coord(0, 14, wram->wAttrmap) = 0x3;
    // hlcoord(2, 0, wAttrmap);
    // LD_BC((8 << 8) | 18);
    // LD_A(0x5);
    // CALL(aCrystal_FillBoxCGB);
    Crystal_FillBoxCGB(coord(2, 0, wram->wAttrmap), 8, 18, 0x5);
    // hlcoord(2, 8, wAttrmap);
    // LD_BC((8 << 8) | 18);
    // LD_A(0x6);
    // CALL(aCrystal_FillBoxCGB);
    Crystal_FillBoxCGB(coord(2, 8, wram->wAttrmap), 8, 18, 0x6);
    // hlcoord(0, 16, wAttrmap);
    // LD_BC((2 << 8) | SCREEN_WIDTH);
    // LD_A(0x4);
    // CALL(aCrystal_FillBoxCGB);
    Crystal_FillBoxCGB(coord(0, 16, wram->wAttrmap), 2, SCREEN_WIDTH, 0x4);
    // LD_A(0x3);
    // LD_BC((6 << 8) | 1);
    // hlcoord(6, 1, wAttrmap);
    // CALL(aCrystal_FillBoxCGB);
    Crystal_FillBoxCGB(coord(6, 1, wram->wAttrmap), 6, 1, 0x3);
    // LD_A(0x3);
    // LD_BC((6 << 8) | 1);
    // hlcoord(17, 1, wAttrmap);
    // CALL(aCrystal_FillBoxCGB);
    Crystal_FillBoxCGB(coord(17, 1, wram->wAttrmap), 6, 1, 0x3);
    // LD_A(0x3);
    // LD_BC((6 << 8) | 1);
    // hlcoord(6, 9, wAttrmap);
    // CALL(aCrystal_FillBoxCGB);
    Crystal_FillBoxCGB(coord(6, 9, wram->wAttrmap), 6, 1, 0x3);
    // LD_A(0x3);
    // LD_BC((6 << 8) | 1);
    // hlcoord(17, 9, wAttrmap);
    // CALL(aCrystal_FillBoxCGB);
    Crystal_FillBoxCGB(coord(17, 9, wram->wAttrmap), 6, 1, 0x3);
    // LD_A(0x2);
    // hlcoord(2, 16, wAttrmap);
    tile_t* hl = coord(2, 16, wram->wAttrmap);
    // LD_hli_A;
    *(hl++) = 0x2;
    // LD_A(0x7);
    // LD_hli_A;
    *(hl++) = 0x7;
    // LD_hli_A;
    *(hl++) = 0x7;
    // LD_hli_A;
    *(hl++) = 0x7;
    // LD_A(0x2);
    // LD_hl_A;
    *hl = 0x2;
    // hlcoord(2, 17, wAttrmap);
    // LD_A(0x3);
    // LD_BC(6);
    // CALL(aByteFill);
    ByteFill(coord(2, 17, wram->wAttrmap), 6, 0x3);
    // RET;
}

void v_LoadTradeRoomBGPals(void){
    // LD_HL(mTradeRoomPalette);
    // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_GREEN);
    // LD_BC(6 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // CALL(aFarCopyWRAM);
    LoadPaletteAssetColorsToBuffer(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_GREEN,
        6 * NUM_PAL_COLORS, TradeRoomPalette, 0, 6 * NUM_PAL_COLORS);
    // FARCALL(aApplyPals);
    ApplyPals();
    // RET;
}

const char TradeRoomPalette[] = "gfx/trade/border.pal";

void InitMG_Mobile_LinkTradePalMap(void){
    // CALL(av_InitMG_Mobile_LinkTradePalMap);
    v_InitMG_Mobile_LinkTradePalMap();
    // RET;
}
