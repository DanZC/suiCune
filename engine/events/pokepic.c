#include "../../constants.h"
#include "pokepic.h"
#include "../../home/delay.h"
#include "../../home/menu.h"
#include "../../home/tilemap.h"
#include "../../home/map_objects.h"
#include "../../home/pokemon.h"
#include "../../home/map.h"
#include "../../home/gfx.h"
#include "../gfx/place_graphic.h"
#include "../gfx/load_pics.h"

static const struct MenuHeader PokepicMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(6, 4, 14, 13),
    .data = NULL,
    .defaultOption = 1,  // default option
};

void Pokepic(void){
    // LD_HL(mPokepicMenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(&PokepicMenuHeader);
    // CALL(aMenuBox);
    MenuBox();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // LD_B(SCGB_POKEPIC);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_POKEPIC);
    DelayFrames(10);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies;
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurPartySpecies);
    // LD_DE(vTiles1);
    // PREDEF(pGetMonFrontpic);
    GetMonFrontpic_Conv(vram->vTiles1);
    // LD_A_addr(wMenuBorderTopCoord);
    // INC_A;
    // LD_B_A;
    // LD_A_addr(wMenuBorderLeftCoord);
    // INC_A;
    // LD_C_A;
    // CALL(aCoord2Tile);
    uint8_t* hl = Coord2Tile(wram->wMenuBorderLeftCoord + 1, wram->wMenuBorderTopCoord + 1);
    // LD_A(0x80);
    // LDH_addr_A(hGraphicStartTile);
    hram->hGraphicStartTile = 0x80;
    // LD_BC((7 << 8) | 7);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger_Conv(hl, 7, 7);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // RET;

}

void ClosePokepic(void){
    // LD_HL(mPokepicMenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(&PokepicMenuHeader);
    // CALL(aClearMenuBoxInterior);
    ClearMenuBoxInterior();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aGetMemSGBLayout);
    GetMemSGBLayout();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aOverworldTextModeSwitch);
    OverworldTextModeSwitch();
    // CALL(aApplyTilemap);
    ApplyTilemap();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // RET;
}
