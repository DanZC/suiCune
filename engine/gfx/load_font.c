#include "../../constants.h"
#include "load_font.h"
#include "../../home/gfx.h"
#include "../../gfx/font.h"
#include "../../charmap.h"

// INCLUDE "gfx/font.asm"

// static const uint8_t EnableHDMAForGraphics = FALSE;

void Get1bppOptionalHDMA(void){
//  //  unreferenced
    LD_A_addr(mEnableHDMAForGraphics);
    AND_A_A;
    JP_NZ (mGet1bppViaHDMA);
    JP(mGet1bpp);

}

void Get2bppOptionalHDMA(void){
//  //  unreferenced
    LD_A_addr(mEnableHDMAForGraphics);
    AND_A_A;
    JP_NZ (mGet2bppViaHDMA);
    JP(mGet2bpp);

}

void v_LoadStandardFont(void){
    // LD_DE(mFont);
    // LD_HL(vTiles1);
    // LD_BC((BANK(aFont) << 8) | 128);  // "A" to "9"
    // LDH_A_addr(rLCDC);
    // BIT_A(rLCDC_ENABLE);
    // JP_Z (mCopy1bpp);
    // if(!bit_test(gb_read(rLCDC), rLCDC_ENABLE))
        // return Copy1bpp(vTiles1, BANK(aFont), mFont, 128);

    // LD_DE(mFont);
    // LD_HL(vTiles1);
    // LD_BC((BANK(aFont) << 8) | 32);  // "A" to "]"
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles1, "gfx/font/font.png", 0, 32);
    // LD_DE(mFont + 32 * LEN_1BPP_TILE);
    // LD_HL(vTiles1 + LEN_2BPP_TILE * 0x20);
    // LD_BC((BANK(aFont) << 8) | 32);  // "a" to $bf
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles1 + LEN_2BPP_TILE * 0x20, "gfx/font/font.png", 32, 32);
    // LD_DE(mFont + 64 * LEN_1BPP_TILE);
    // LD_HL(vTiles1 + LEN_2BPP_TILE * 0x40);
    // LD_BC((BANK(aFont) << 8) | 32);  // "Ä" to "←"
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles1 + LEN_2BPP_TILE * 0x40, "gfx/font/font.png", 64, 32);
    // LD_DE(mFont + 96 * LEN_1BPP_TILE);
    // LD_HL(vTiles1 + LEN_2BPP_TILE * 0x60);
    // LD_BC((BANK(aFont) << 8) | 32);  // "'" to "9"
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles1 + LEN_2BPP_TILE * 0x60, "gfx/font/font.png", 96, 32);
    // RET;
}

void v_LoadFontsExtra1(void){
    // LD_DE(mFontsExtra_SolidBlackGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_BLACK_SQUARE);  // $60
    // LD_BC((BANK(aFontsExtra_SolidBlackGFX) << 8) | 1);
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * CHAR_BLACK_SQUARE, "gfx/font/black.png", 0, 1);
    // LD_DE(mPokegearPhoneIconGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_PHONE_ICON);  // $62
    // LD_BC((BANK(aPokegearPhoneIconGFX) << 8) | 1);
    // CALL(aGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * CHAR_PHONE_ICON, "gfx/font/phone_icon.png", 0, 1);
    // LD_DE(mFontExtra + 3 * LEN_2BPP_TILE);  // "<BOLD_D>"
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_BOLD_D);
    // LD_BC((BANK(aFontExtra) << 8) | 22);  // "<BOLD_D>" to "ぉ"
    // CALL(aGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * CHAR_BOLD_D, "gfx/font/font_extra.png", 3, 22);
    // JR(mLoadFrame);
    return LoadFrame();
}

void v_LoadFontsExtra2(void){
    // LD_DE(mFontsExtra2_UpArrowGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_UP_ARROW);  // $61
    // LD_B(BANK(aFontsExtra2_UpArrowGFX));
    // LD_C(1);
    // CALL(aGet2bppViaHDMA);
    // RET;
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * CHAR_UP_ARROW, "gfx/font/up_arrow.png", 0, 1);
}

void v_LoadFontsBattleExtra(void){
    // LD_DE(mFontBattleExtra);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x60);
    // LD_BC((BANK(aFontBattleExtra) << 8) | 25);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x60, FontBattleExtra, 0, 25);
    // CALL(aGet2bppViaHDMA);
    // JR(mLoadFrame);
    return LoadFrame();
}

void LoadFrame(void){
    static const char* FramePaths[] = {
        "gfx/frames/1.png",
        "gfx/frames/2.png",
        "gfx/frames/3.png",
        "gfx/frames/4.png",
        "gfx/frames/5.png",
        "gfx/frames/6.png",
        "gfx/frames/7.png",
        "gfx/frames/8.png",
        "gfx/frames/9.png"
    };
    // LD_A_addr(wTextboxFrame);
    // maskbits(NUM_FRAMES, 0);
    // LD_BC(TEXTBOX_FRAME_TILES * LEN_1BPP_TILE);
    // LD_HL(mFrames);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_FRAME_TOP_LEFT);  // $79
    // LD_BC((BANK(aFrames) << 8) | TEXTBOX_FRAME_TILES);  // "┌" to "┘"
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * CHAR_FRAME_TOP_LEFT, FramePaths[wram->wTextboxFrame & 0x7], 0, TEXTBOX_FRAME_TILES);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * CHAR_SPACE);  // $7f
    // LD_DE(mTextboxSpaceGFX);
    // LD_BC((BANK(aTextboxSpaceGFX) << 8) | 1);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * CHAR_SPACE, "gfx/font/space.png", 0, 1);
    // CALL(aGet1bppViaHDMA);
    // RET;
}

void LoadBattleFontsHPBar(void){
    // LD_DE(mFontBattleExtra);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x60);
    // LD_BC((BANK(aFontBattleExtra) << 8) | 12);
    // CALL(aGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x60, FontBattleExtra, 0, 12);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x70);
    // LD_DE(mFontBattleExtra + 16 * LEN_2BPP_TILE);  // "<DO>"
    // LD_BC((BANK(aFontBattleExtra) << 8) | 3);  // "<DO>" to "『"
    // CALL(aGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x70, FontBattleExtra, 16, 3);
    // CALL(aLoadFrame);
    LoadFrame();

    return LoadHPBar();
}

void LoadHPBar(void){
    // LD_DE(mEnemyHPBarBorderGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x6c);
    // LD_BC((BANK(aEnemyHPBarBorderGFX) << 8) | 4);
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x6c, EnemyHPBarBorderGFX, 0, 4);
    // LD_DE(mHPExpBarBorderGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x73);
    // LD_BC((BANK(aHPExpBarBorderGFX) << 8) | 6);
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x73, HPExpBarBorderGFX, 0, 6);
    // LD_DE(mExpBarGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x55);
    // LD_BC((BANK(aExpBarGFX) << 8) | 9);
    // CALL(aGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x55, ExpBarGFX, 0, 9);
    // LD_DE(mMobilePhoneTilesGFX + 7 * LEN_2BPP_TILE);  // mobile phone icon
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x5e);
    // LD_BC((BANK(aMobilePhoneTilesGFX) << 8) | 2);
    // CALL(aGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x5e, MobilePhoneTilesGFX, 7, 1);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x5f, MobilePhoneTilesGFX, 9, 1);
    // RET;
}

void StatsScreen_LoadFont(void){
    // CALL(av_LoadFontsBattleExtra);
    v_LoadFontsBattleExtra();
    // LD_DE(mEnemyHPBarBorderGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x6c);
    // LD_BC((BANK(aEnemyHPBarBorderGFX) << 8) | 4);
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x6c, EnemyHPBarBorderGFX, 0, 4);
    // LD_DE(mHPExpBarBorderGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x78);
    // LD_BC((BANK(aHPExpBarBorderGFX) << 8) | 1);
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x78, HPExpBarBorderGFX, 0, 1);
    // LD_DE(mHPExpBarBorderGFX + 3 * LEN_1BPP_TILE);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x76);
    // LD_BC((BANK(aHPExpBarBorderGFX) << 8) | 2);
    // CALL(aGet1bppViaHDMA);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x76, HPExpBarBorderGFX, 3, 2);
    // LD_DE(mExpBarGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x55);
    // LD_BC((BANK(aExpBarGFX) << 8) | 8);
    // CALL(aGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x55, ExpBarGFX, 0, 8);
    return LoadStatsScreenPageTilesGFX();
}

void LoadStatsScreenPageTilesGFX(void){
    // LD_DE(mStatsScreenPageTilesGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x31);
    // LD_BC((BANK(aStatsScreenPageTilesGFX) << 8) | 17);
    // CALL(aGet2bppViaHDMA);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x31, StatsScreenPageTilesGFX, 0, 17);
    // RET;
}
