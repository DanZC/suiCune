#include "../../constants.h"
#include "new_pokedex_entry.h"
#include "pokedex.h"
#include "pokedex_2.h"
#include "../battle/core.h"
#include "../../home/audio.h"
#include "../../home/tilemap.h"
#include "../../home/map.h"
#include "../../home/clear_sprites.h"
#include "../../home/text.h"
#include "../../home/map_objects.h"
#include "../../home/joypad.h"
#include "../../home/gfx.h"
#include "../../home/fade.h"

#define POKEDEX_SCX (5)

static void NewPokedexEntry_ReturnFromDexRegistration(void) {
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // FARCALL(aPokedex_PlaceFrontpicTopLeftCorner);
    Pokedex_PlaceFrontpicTopLeftCorner();
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // FARCALL(aGetEnemyMonDVs);
    // LD_A_hli;
    // LD_addr_A(wTempMonDVs);
    // LD_A_hl;
    // LD_addr_A(wTempMonDVs + 1);
    wram->wTempMon.mon.DVs = GetEnemyMonDVs_Conv();
    // LD_B(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout(SCGB_TRAINER_OR_MON_FRONTPIC_PALS);
    // CALL(aSetPalettes);
    SetPalettes();
    // RET;
}

void NewPokedexEntry(void){
    // LDH_A_addr(hMapAnims);
    // PUSH_AF;
    uint8_t mapAnims = hram->hMapAnims;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0;
    // CALL(aLowVolume);
    LowVolume();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aUpdateSprites);
    UpdateSprites();
    // CALL(aClearSprites);
    ClearSprites();
    // LD_A_addr(wPokedexStatus);
    // PUSH_AF;
    uint8_t pokedexStatus = wram->wPokedexStatus;
    // LDH_A_addr(hSCX);
    // ADD_A(POKEDEX_SCX);
    // LDH_addr_A(hSCX);
    hram->hSCX += POKEDEX_SCX;
    // XOR_A_A;
    // LD_addr_A(wPokedexStatus);
    wram->wPokedexStatus = 0;
    // FARCALL(av_NewPokedexEntry);
    v_NewPokedexEntry();
    // CALL(aWaitPressAorB_BlinkCursor);
    WaitPressAorB_BlinkCursor();
    // LD_A(1);  // page 2
    // LD_addr_A(wPokedexStatus);
    wram->wPokedexStatus = 1;
    // FARCALL(aDisplayDexEntry);
    DisplayDexEntry(wram->wTempSpecies);
    // CALL(aWaitPressAorB_BlinkCursor);
    WaitPressAorB_BlinkCursor();
    // POP_AF;
    // LD_addr_A(wPokedexStatus);
    wram->wPokedexStatus = pokedexStatus;
    // CALL(aMaxVolume);
    MaxVolume();
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight();
    // LDH_A_addr(hSCX);
    // ADD_A(-POKEDEX_SCX);
    // LDH_addr_A(hSCX);
    hram->hSCX -= POKEDEX_SCX;
    // CALL(aNewPokedexEntry_ReturnFromDexRegistration);
    NewPokedexEntry_ReturnFromDexRegistration();
    // POP_AF;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = mapAnims;
    // RET;
    return;

}
