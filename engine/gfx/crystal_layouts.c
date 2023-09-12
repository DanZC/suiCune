#include "../../constants.h"
#include "crystal_layouts.h"
#include "../../home/copy.h"

void GetCrystalCGBLayout(void){
    LD_A_B;
    CP_A(SCGB_DEFAULT);
    IF_NZ goto not_default;
    LD_A_addr(wDefaultSGBLayout);

not_default:
    PUSH_AF;
    FARCALL(aResetBGPals);
    POP_AF;
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    LD_DE(mGetCrystalCGBLayout_Jumptable);
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(mGetCrystalCGBLayout_done);
    PUSH_DE;
    JP_hl;

done:
    RET;


Jumptable:
    //dw ['_CrystalCGB_MobileLayout0'];
    //dw ['_CrystalCGB_MobileLayout1'];
    //dw ['_CrystalCGB_NameCard'];

    return Crystal_FillBoxCGB();
}

void Crystal_FillBoxCGB(void){
//  This is a copy of FillBoxCGB.

row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    RET;

}

void Crystal_WipeAttrmap(void){
//  This is a copy of WipeAttrmap.
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    XOR_A_A;
    CALL(aByteFill);
    RET;

}

void MG_Mobile_Layout_LoadPals(void){
    LD_DE(wBGPals1);
    LD_HL(mPalette_MysteryGiftMobile);
    LD_BC(5 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
    LD_HL(mPalette_TextBG7);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    RET;

}

void v_CrystalCGB_MobileLayout0(void){
    CALL(aMG_Mobile_Layout_LoadPals);
    CALL(aCrystal_WipeAttrmap);
    CALL(aMG_Mobile_Layout_CreatePalBoxes);
    FARCALL(aApplyAttrmap);
    FARCALL(aApplyPals);
    RET;

}

void MG_Mobile_Layout_CreatePalBoxes(void){
    hlcoord(0, 0, wAttrmap);
    LD_BC((4 << 8) | 1);
    LD_A(0x1);
    CALL(aCrystal_FillBoxCGB);
    LD_BC((2 << 8) | 1);
    LD_A(0x2);
    CALL(aCrystal_FillBoxCGB);
    LD_BC((6 << 8) | 1);
    LD_A(0x3);
    CALL(aCrystal_FillBoxCGB);
    hlcoord(1, 0, wAttrmap);
    LD_A(0x1);
    LD_BC((3 << 8) | 18);
    CALL(aCrystal_FillBoxCGB);
    LD_BC((2 << 8) | 18);
    LD_A(0x2);
    CALL(aCrystal_FillBoxCGB);
    LD_BC((12 << 8) | 18);
    LD_A(0x3);
    CALL(aCrystal_FillBoxCGB);
    hlcoord(19, 0, wAttrmap);
    LD_BC((4 << 8) | 1);
    LD_A(0x1);
    CALL(aCrystal_FillBoxCGB);
    LD_BC((2 << 8) | 1);
    LD_A(0x2);
    CALL(aCrystal_FillBoxCGB);
    LD_BC((6 << 8) | 1);
    LD_A(0x3);
    CALL(aCrystal_FillBoxCGB);
    hlcoord(0, 12, wAttrmap);
    LD_BC(6 * SCREEN_WIDTH);
    LD_A(0x7);
    CALL(aByteFill);
    RET;

}

void Palette_MysteryGiftMobile(void){
// INCLUDE "gfx/mystery_gift/mg_mobile.pal"

    return LoadOW_BGPal7();
}

static const uint16_t Palette_TextBG7[] = {
    rgb(31, 31, 31),
    rgb( 8, 19, 28),
    rgb( 5,  5, 16),
    rgb( 0,  0,  0),
};

void LoadOW_BGPal7(void){
    // LD_HL(mPalette_TextBG7);
    // LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // CALL(aFarCopyWRAM);
    CopyBytes_Conv2(wram->wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT, Palette_TextBG7, 1 * PALETTE_SIZE);
    RET;
}

// void Palette_TextBG7(void){
// // INCLUDE "gfx/font/bg_text.pal"

//     return Function49420();
// }

void Function49420(void){
    LD_HL(mMansionPalette1 + 8 * PALETTE_SIZE);
    LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_ROOF);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    RET;

}

void v_CrystalCGB_MobileLayout1(void){
    CALL(aMG_Mobile_Layout_LoadPals);
    LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_TEXT);
    LD_HL(mv_CrystalCGB_MobileLayout1_TextPalette);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    CALL(aCrystal_WipeAttrmap);
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    XOR_A_A;
    CALL(aByteFill);
    hlcoord(0, 14, wAttrmap);
    LD_BC(4 * SCREEN_WIDTH);
    LD_A(0x7);
    CALL(aByteFill);
    LD_A_addr(wd002);
    BIT_A(6);
    IF_Z goto asm_49464;
    CALL(av_CrystalCGB_MobileLayout1_Function49480);
    goto done;


asm_49464:
    CALL(av_CrystalCGB_MobileLayout1_Function49496);

done:
    FARCALL(aApplyAttrmap);
    FARCALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;


TextPalette:
// INCLUDE "gfx/mystery_gift/mobile_text.pal"


Function49480:
    hlcoord(0, 0, wAttrmap);
    LD_BC((4 << 8) | SCREEN_WIDTH);
    LD_A(0x7);
    CALL(aCrystal_FillBoxCGB);
    hlcoord(0, 2, wAttrmap);
    LD_A(0x4);
    LD_hl_A;
    hlcoord(19, 2, wAttrmap);
    LD_hl_A;
    RET;


Function49496:
    hlcoord(0, 0, wAttrmap);
    LD_BC((2 << 8) | SCREEN_WIDTH);
    LD_A(0x7);
    CALL(aCrystal_FillBoxCGB);
    hlcoord(0, 1, wAttrmap);
    LD_A(0x4);
    LD_hl_A;
    hlcoord(19, 1, wAttrmap);
    LD_hl_A;
    RET;

// INCLUDE "engine/tilesets/tileset_palettes.asm"

    return v_CrystalCGB_NameCard();
}

void v_CrystalCGB_NameCard(void){
    LD_HL(mv_CrystalCGB_NameCard_BGPalette);
    LD_DE(wBGPals1);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    FARCALL(aApplyPals);
    CALL(aCrystal_WipeAttrmap);
    FARCALL(aApplyAttrmap);
    LD_HL(mv_CrystalCGB_NameCard_OBPalette);
    LD_DE(wOBPals1);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(wOBPals1));
    CALL(aFarCopyWRAM);
    RET;


BGPalette:
// INCLUDE "gfx/mystery_gift/name_card_bg.pal"


OBPalette:
// INCLUDE "gfx/mystery_gift/name_card_ob.pal"

    return Function49742();
}

void Function49742(void){
    LD_HL(mFunction49742_MobileBorderPalettes);
    LD_DE(wBGPals1);
    LD_BC(8 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    FARCALL(aApplyPals);
    RET;


MobileBorderPalettes:
// INCLUDE "gfx/trade/mobile_border.pal"

    return v_InitMG_Mobile_LinkTradePalMap();
}

void v_InitMG_Mobile_LinkTradePalMap(void){
    hlcoord(0, 0, wAttrmap);
    LD_BC((16 << 8) | 2);
    LD_A(0x4);
    CALL(aCrystal_FillBoxCGB);
    LD_A(0x3);
    ldcoord_a(0, 1, wAttrmap);
    ldcoord_a(0, 14, wAttrmap);
    hlcoord(2, 0, wAttrmap);
    LD_BC((8 << 8) | 18);
    LD_A(0x5);
    CALL(aCrystal_FillBoxCGB);
    hlcoord(2, 8, wAttrmap);
    LD_BC((8 << 8) | 18);
    LD_A(0x6);
    CALL(aCrystal_FillBoxCGB);
    hlcoord(0, 16, wAttrmap);
    LD_BC((2 << 8) | SCREEN_WIDTH);
    LD_A(0x4);
    CALL(aCrystal_FillBoxCGB);
    LD_A(0x3);
    LD_BC((6 << 8) | 1);
    hlcoord(6, 1, wAttrmap);
    CALL(aCrystal_FillBoxCGB);
    LD_A(0x3);
    LD_BC((6 << 8) | 1);
    hlcoord(17, 1, wAttrmap);
    CALL(aCrystal_FillBoxCGB);
    LD_A(0x3);
    LD_BC((6 << 8) | 1);
    hlcoord(6, 9, wAttrmap);
    CALL(aCrystal_FillBoxCGB);
    LD_A(0x3);
    LD_BC((6 << 8) | 1);
    hlcoord(17, 9, wAttrmap);
    CALL(aCrystal_FillBoxCGB);
    LD_A(0x2);
    hlcoord(2, 16, wAttrmap);
    LD_hli_A;
    LD_A(0x7);
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_A(0x2);
    LD_hl_A;
    hlcoord(2, 17, wAttrmap);
    LD_A(0x3);
    LD_BC(6);
    CALL(aByteFill);
    RET;

}

void v_LoadTradeRoomBGPals(void){
    LD_HL(mTradeRoomPalette);
    LD_DE(wBGPals1 + PALETTE_SIZE * PAL_BG_GREEN);
    LD_BC(6 * PALETTE_SIZE);
    LD_A(BANK(wBGPals1));
    CALL(aFarCopyWRAM);
    FARCALL(aApplyPals);
    RET;

}

void TradeRoomPalette(void){
// INCLUDE "gfx/trade/border.pal"

    return InitMG_Mobile_LinkTradePalMap();
}

void InitMG_Mobile_LinkTradePalMap(void){
    CALL(av_InitMG_Mobile_LinkTradePalMap);
    RET;

}
