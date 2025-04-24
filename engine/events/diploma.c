#include "../../constants.h"
#include "diploma.h"
#include "../../home/joypad.h"
#include "../../home/tilemap.h"
#include "../../home/lcd.h"
#include "../../home/clear_sprites.h"
#include "../../home/text.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/print_text.h"

void v_Diploma(void){
    // CALL(aPlaceDiplomaOnScreen);
    PlaceDiplomaOnScreen();
    // CALL(aWaitPressAorB_BlinkCursor);
    WaitPressAorB_BlinkCursor_Conv();
    // RET;
}

void PlaceDiplomaOnScreen(void){
    static const char Certification[] = "This certifies"
        t_next "that you have"
        t_next "completed the"
        t_next "new #DEX."
        t_next "Congratulations!";
    // CALL(aClearBGPalettes);
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_HL(mDiplomaGFX);
    // LD_DE(vTiles2);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles2, DiplomaGFX);
    // LD_HL(mDiplomaPage1Tilemap);
    // decoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, DiplomaPage1Tilemap);
    // LD_DE(mPlaceDiplomaOnScreen_Player);
    // hlcoord(2, 5, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("PLAYER"), coord(2, 5, wram->wTilemap));
    // LD_DE(mPlaceDiplomaOnScreen_EmptyString);
    // hlcoord(15, 5, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(""), coord(15, 5, wram->wTilemap));
    // LD_DE(wPlayerName);
    // hlcoord(9, 5, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wPlayerName, coord(9, 5, wram->wTilemap));
    // LD_DE(mPlaceDiplomaOnScreen_Certification);
    // hlcoord(2, 8, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Certification), coord(2, 8, wram->wTilemap));
    // CALL(aEnableLCD);
    EnableLCD();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_DIPLOMA);
    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void PrintDiplomaPage2(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // LD_HL(mDiplomaPage2Tilemap);
    // decoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, DiplomaPage2Tilemap);
    // LD_DE(mPrintDiplomaPage2_GameFreak);
    // hlcoord(8, 0, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("GAME FREAK"), coord(8, 0, wram->wTilemap));
    // LD_DE(mPrintDiplomaPage2_PlayTime);
    // hlcoord(3, 15, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("PLAY TIME"), coord(3, 15, wram->wTilemap));
    // hlcoord(12, 15, wTilemap);
    // LD_DE(wGameTimeHours);
    // LD_BC((2 << 8) | 4);
    // CALL(aPrintNum);
    tile_t* hl = PrintNum_Conv2(coord(12, 15, wram->wTilemap), &wram->wGameTimeHours, 2, 4);
    // LD_hl(0x67);  // colon
    *(hl++) = 0x67;
    // INC_HL;
    // LD_DE(wGameTimeMinutes);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // CALL(aPrintNum);
    PrintNum_Conv2(hl, &wram->wGameTimeMinutes, PRINTNUM_LEADINGZEROS | 1, 2);
    // RET;


// PlayTime:
// db "PLAY TIME@"

// GameFreak:
// db "GAME FREAK@"
}

const char DiplomaGFX[] = "gfx/diploma/diploma.png";
const char DiplomaPage1Tilemap[] = "gfx/diploma/page1.tilemap";
const char DiplomaPage2Tilemap[] = "gfx/diploma/page2.tilemap";

void Diploma_DummyFunction(void){
//  //  unreferenced
    // RET;

}
