#include "../../constants.h"
#include "init_gender.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/gfx.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../gfx/color.h"
#include "../../data/text/common.h"

void InitCrystalData(void){
    // LD_A(0x1);
    // LD_addr_A(wd474);
    wram->wPrefecture = 0x1;
    // XOR_A_A;
    // LD_addr_A(wd473);
    wram->wAge = 0;
    // LD_addr_A(wPlayerGender);
    wram->wPlayerGender = 0;
    // LD_addr_A(wd475);
    wram->wd475 = 0;
    // LD_addr_A(wd476);
    wram->wd476 = 0;
    // LD_addr_A(wd477);
    wram->wd477 = 0;
    // LD_addr_A(wd478);
    wram->wd478 = 0;
    // LD_addr_A(wd002);
    wram->wd002 = 0;
    // LD_addr_A(wd003);
    wram->wd003 = 0;
    // LD_A_addr(wd479);
    // RES_A(0);  // ???
    // LD_addr_A(wd479);
    bit_reset(wram->wd479[0], 0);  // ???
    // LD_A_addr(wd479);
    // RES_A(1);  // ???
    // LD_addr_A(wd479);
    bit_reset(wram->wd479[0], 1);  // ???
    // RET;

// INCLUDE "mobile/mobile_12.asm"
}

const struct MenuHeader InitGender_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(6, 4, 12, 9),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR | STATICMENU_WRAP | STATICMENU_DISABLE_B,  // flags
        .verticalMenu = {
            .count = 2,  // items
            .options = (const char*[]) {
                "Boy@",
                "Girl@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

static const txt_cmd_s AreYouABoyOrAreYouAGirlText[] = {
    text_far(v_AreYouABoyOrAreYouAGirlText)
    text_end
};

void InitGender(void){
    // CALL(aInitGenderScreen);
    InitGenderScreen();
    // CALL(aLoadGenderScreenPal);
    LoadGenderScreenPal();
    // CALL(aLoadGenderScreenLightBlueTile);
    LoadGenderScreenLightBlueTile();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LD_HL(mAreYouABoyOrAreYouAGirlText);
    // CALL(aPrintText);
    PrintText_Conv2(AreYouABoyOrAreYouAGirlText);
    // LD_HL(mInitGender_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&InitGender_MenuHeader);
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // CALL(aVerticalMenu);
    VerticalMenu_Conv();
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_addr_A(wPlayerGender);
    wram->wPlayerGender = wram->wMenuCursorY - 1;
    // LD_C(10);
    // CALL(aDelayFrames);
    DelayFrames_Conv(10);
    // RET;
}

void InitGenderScreen(void){
    // LD_A(0x10);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0x10;
    // LD_A(LOW(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID);
    // LD_A(HIGH(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_NONE;
    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames_Conv(8);
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aInitCrystalData);
    InitCrystalData();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // LD_A(0x0);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x0);
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wAttrmap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x0);
    // RET;
}

void LoadGenderScreenPal(void){
    static const uint16_t Palette[] = {
        rgb(31, 31, 31),
        rgb( 9, 30, 31),
        rgb( 1, 11, 31),
        rgb( 0,  0,  0),
    };
    // LD_HL(mLoadGenderScreenPal_Palette);
    // LD_DE(wBGPals1);
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(BANK(wBGPals1));
    // CALL(aFarCopyWRAM);
    CopyBytes_Conv2(wram->wBGPals1, Palette, 1 * PALETTE_SIZE);
    // FARCALL(aApplyPals);
    ApplyPals_Conv();
    // RET;
// INCLUDE "gfx/new_game/gender_screen.pal"
}

void LoadGenderScreenLightBlueTile(void){
    static const char LightBlueTile[] = "gfx/new_game/gender_screen.png";
    // LD_DE(mLoadGenderScreenLightBlueTile_LightBlueTile);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x00);
    // LD_BC((BANK(aLoadGenderScreenLightBlueTile_LightBlueTile) << 8) | 1);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, LightBlueTile, 0x0, 1);
    // RET;
}
