#include "../../constants.h"
#include "pokedex.h"
#include "pokedex_2.h"
#include "pokedex_3.h"
#include "unown_dex.h"
#include "../../home/delay.h"
#include "../../home/audio.h"
#include "../../home/clear_sprites.h"
#include "../../home/joypad.h"
#include "../../home/copy.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../../home/lcd.h"
#include "../../home/gfx.h"
#include "../../home/pokedex_flags.h"
#include "../../home/map.h"
#include "../../home/print_text.h"
#include "../../home/names.h"
#include "../../home/palettes.h"
#include "../../home/sram.h"
#include "../../home/pokemon.h"
#include "../gfx/load_pics.h"
#include "../pokegear/pokegear.h"
#include "../printer/printer.h"
#include "../../data/pokemon/dex_order_new.h"
#include "../../data/pokemon/dex_order_alpha.h"
#include "../../data/types/search_strings.h"
#include "../../data/types/search_types.h"
#include "../../gfx/misc.h"
#include "../../gfx/footprints.h"
#include "../../charmap.h"

//  Pokedex_RunJumptable.Jumptable indexes
enum {
    DEXSTATE_MAIN_SCR,
    DEXSTATE_UPDATE_MAIN_SCR,
    DEXSTATE_DEX_ENTRY_SCR,
    DEXSTATE_UPDATE_DEX_ENTRY_SCR,
    DEXSTATE_REINIT_DEX_ENTRY_SCR,
    DEXSTATE_SEARCH_SCR,
    DEXSTATE_UPDATE_SEARCH_SCR,
    DEXSTATE_OPTION_SCR,
    DEXSTATE_UPDATE_OPTION_SCR,
    DEXSTATE_SEARCH_RESULTS_SCR,
    DEXSTATE_UPDATE_SEARCH_RESULTS_SCR,
    DEXSTATE_UNOWN_MODE,
    DEXSTATE_UPDATE_UNOWN_MODE,
    DEXSTATE_EXIT,
};

#define POKEDEX_SCX (5)

const struct ArrowCursorData {
    uint8_t mask;
    uint8_t count;
    const uint16_t* coords;
} DexEntryScreen_ArrowCursorData = {
    .mask = D_RIGHT | D_LEFT,
    .count = 4,
    .coords = (const uint16_t[]) {
        coord(1, 17, 0),  // PAGE
        coord(6, 17, 0),  // AREA
        coord(11, 17, 0),  // CRY
        coord(15, 17, 0),  // PRNT
    },
};

void Pokedex(void){
    // LDH_A_addr(hWX);
    // LD_L_A;
    uint8_t wx = hram.hWX;
    // LDH_A_addr(hWY);
    // LD_H_A;
    uint8_t wy = hram.hWY;
    // PUSH_HL;
    // LDH_A_addr(hSCX);
    // PUSH_AF;
    uint8_t scx = hram.hSCX;
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = gOptions.options;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(gOptions.options, NO_TEXT_SCROLL);
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0;
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram.hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram.hInMenu = 0x1;

    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram.hMapAnims = 0;
    // CALL(aInitPokedex);
    InitPokedex();
    // CALL(aDelayFrame);
    DelayFrame();

    while(1) {
    // main:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto exit;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(aPokedex_RunJumptable);
        Pokedex_RunJumptable();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto main;
    }


// exit:
    // LD_DE(SFX_READ_TEXT_2);
    // CALL(aPlaySFX);
    PlaySFX(SFX_READ_TEXT_2);
    // CALL(aWaitSFX);
    WaitSFX();
    // CALL(aClearSprites);
    ClearSprites();
    // LD_A_addr(wCurDexMode);
    // LD_addr_A(wLastDexMode);
    gPlayer.lastDexMode = wram->wCurDexMode;

    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram.hInMenu = inMenu;
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LD_addr_A(wOptions);
    gOptions.options = options;
    // POP_AF;
    // LDH_addr_A(hSCX);
    hram.hSCX = scx;
    // POP_HL;
    // LD_A_L;
    // LDH_addr_A(hWX);
    hram.hWX = wx;
    // LD_A_H;
    // LDH_addr_A(hWY);
    hram.hWY = wy;
    // RET;
}

void InitPokedex(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aPokedex_LoadGFX);
    Pokedex_LoadGFX();

    // LD_HL(wPokedexDataStart);
    // LD_BC(wPokedexDataEnd - wPokedexDataStart);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wPokedexOrder, wPokedexDataEnd - wPokedexDataStart, 0);

    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // LD_addr_A(wPrevDexEntryJumptableIndex);
    wram->wPrevDexEntryJumptableIndex = 0;
    // LD_addr_A(wPrevDexEntryBackup);
    wram->wPrevDexEntryBackup = 0;
    // LD_addr_A(wUnusedPokedexByte);
    wram->wUnusedPokedexByte = 0;

    // CALL(aPokedex_CheckUnlockedUnownMode);
    Pokedex_CheckUnlockedUnownMode();

    // LD_A_addr(wLastDexMode);
    // LD_addr_A(wCurDexMode);
    wram->wCurDexMode = gPlayer.lastDexMode;

    // CALL(aPokedex_OrderMonsByMode);
    Pokedex_OrderMonsByMode();
    // CALL(aPokedex_InitCursorPosition);
    Pokedex_InitCursorPosition();
    // CALL(aPokedex_GetLandmark);
    Pokedex_GetLandmark();
    // FARCALL(aDrawDexEntryScreenRightEdge);
    DrawDexEntryScreenRightEdge();
    // CALL(aPokedex_ResetBGMapMode);
    Pokedex_ResetBGMapMode();
    // RET;
}

void Pokedex_CheckUnlockedUnownMode(void){
    // LD_A_addr(wStatusFlags);
    // BIT_A(STATUSFLAGS_UNOWN_DEX_F);
    // IF_NZ goto unlocked;
    if(bit_test(gPlayer.statusFlags, STATUSFLAGS_UNOWN_DEX_F)) {
    // unlocked:
        // LD_A(TRUE);
        // LD_addr_A(wUnlockedUnownMode);
        wram->wUnlockedUnownMode = TRUE;
        // RET;
        return;
    }

    // XOR_A_A;
    // LD_addr_A(wUnlockedUnownMode);
    wram->wUnlockedUnownMode = FALSE;
    // RET;
}

void Pokedex_InitCursorPosition(void){
    // LD_HL(wPokedexOrder);
    species_t* hl = wram->wPokedexOrder;
    // LD_A_addr(wPrevDexEntry);
    // AND_A_A;
    // IF_Z goto done;
    // CP_A(NUM_POKEMON + 1);
    // IF_NC goto done;
    if(wram->wPrevDexEntry == 0 || wram->wPrevDexEntry >= NUM_POKEMON + 1)
        return;

    // LD_B_A;
    species_t b = wram->wPrevDexEntry;
    // LD_A_addr(wDexListingEnd);
    // CP_A(0x8);
    // IF_C goto only_one_page;
    if(wram->wDexListingEnd >= 0x8) {
        // SUB_A(0x7);
        // LD_C_A;
        species_t c = wram->wDexListingEnd - 0x7;

        do {
        // loop1:
            // LD_A_B;
            // CP_A_hl;
            // IF_Z goto done;
            if(b == *hl) {
                return;
            }
            // INC_HL;
            hl++;
            // LD_A_addr(wDexListingScrollOffset);
            // INC_A;
            // LD_addr_A(wDexListingScrollOffset);
            wram->wDexListingScrollOffset++;
            // DEC_C;
            // IF_NZ goto loop1;
        } while(--c != 0);
    }

// only_one_page:
    // LD_C(0x7);
    species_t c = 0x7;

    do {
    // loop2:
        // LD_A_B;
        // CP_A_hl;
        // IF_Z goto done;
        if(b == *hl) {
            return;
        }
        // INC_HL;
        hl++;
        // LD_A_addr(wDexListingCursor);
        // INC_A;
        // LD_addr_A(wDexListingCursor);
        wram->wDexListingCursor++;
        // DEC_C;
        // IF_NZ goto loop2;
    } while(--c != 0);
// done:
    // RET;
}

void Pokedex_GetLandmark(void){
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    // CALL(aGetWorldMapLocation);
    uint8_t loc = GetWorldMapLocation(gCurMapData.mapGroup, gCurMapData.mapNumber);

    // CP_A(LANDMARK_SPECIAL);
    // IF_NZ goto load;

    if(loc == LANDMARK_SPECIAL) {
        // LD_A_addr(wBackupMapGroup);
        // LD_B_A;
        // LD_A_addr(wBackupMapNumber);
        // LD_C_A;
        // CALL(aGetWorldMapLocation);
        loc = GetWorldMapLocation(gCurMapData.backupMapGroup, gCurMapData.backupMapNumber);
    }

// load:
    // LD_addr_A(wDexCurLocation);
    wram->wDexCurLocation = loc;
    // RET;
}

void Pokedex_RunJumptable(void){
    // LD_A_addr(wJumptableIndex);
    // LD_HL(mPokedex_RunJumptable_Jumptable);
    // CALL(aPokedex_LoadPointer);
    // JP_hl;

    switch(wram->wJumptableIndex) {
    // Jumptable:
    //  entries correspond to DEXSTATE_* constants
        //dw ['Pokedex_InitMainScreen'];
        case DEXSTATE_MAIN_SCR: return Pokedex_InitMainScreen();
        //dw ['Pokedex_UpdateMainScreen'];
        case DEXSTATE_UPDATE_MAIN_SCR: return Pokedex_UpdateMainScreen();
        //dw ['Pokedex_InitDexEntryScreen'];
        case DEXSTATE_DEX_ENTRY_SCR: return Pokedex_InitDexEntryScreen();
        //dw ['Pokedex_UpdateDexEntryScreen'];
        case DEXSTATE_UPDATE_DEX_ENTRY_SCR: return Pokedex_UpdateDexEntryScreen();
        //dw ['Pokedex_ReinitDexEntryScreen'];
        case DEXSTATE_REINIT_DEX_ENTRY_SCR: return Pokedex_ReinitDexEntryScreen();
        //dw ['Pokedex_InitSearchScreen'];
        case DEXSTATE_SEARCH_SCR: return Pokedex_InitSearchScreen();
        //dw ['Pokedex_UpdateSearchScreen'];
        case DEXSTATE_UPDATE_SEARCH_SCR: return Pokedex_UpdateSearchScreen();
        //dw ['Pokedex_InitOptionScreen'];
        case DEXSTATE_OPTION_SCR: return Pokedex_InitOptionScreen();
        //dw ['Pokedex_UpdateOptionScreen'];
        case DEXSTATE_UPDATE_OPTION_SCR: return Pokedex_UpdateOptionScreen();
        //dw ['Pokedex_InitSearchResultsScreen'];
        case DEXSTATE_SEARCH_RESULTS_SCR: return Pokedex_InitSearchResultsScreen();
        //dw ['Pokedex_UpdateSearchResultsScreen'];
        case DEXSTATE_UPDATE_SEARCH_RESULTS_SCR: return Pokedex_UpdateSearchResultsScreen();
        //dw ['Pokedex_InitUnownMode'];
        case DEXSTATE_UNOWN_MODE: return Pokedex_InitUnownMode();
        //dw ['Pokedex_UpdateUnownMode'];
        case DEXSTATE_UPDATE_UNOWN_MODE: return Pokedex_UpdateUnownMode();
        //dw ['Pokedex_Exit'];
        default:
        case DEXSTATE_EXIT: return Pokedex_Exit();
    }
}

void Pokedex_IncrementDexPointer(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;
}

void Pokedex_Exit(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}

void Pokedex_InitMainScreen(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aClearSprites);
    ClearSprites();
    // XOR_A_A;
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_HEIGHT * SCREEN_WIDTH, 0);
    // FARCALL(aDrawPokedexListWindow);
    DrawPokedexListWindow();
    // hlcoord(0, 17, wTilemap);
    // LD_DE(mString_START_SEARCH);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(0, 17, wram->wTilemap), String_START_SEARCH);
    // LD_A(7);
    // LD_addr_A(wDexListingHeight);
    wram->wDexListingHeight = 7;
    // CALL(aPokedex_PrintListing);
    Pokedex_PrintListing();
    // CALL(aPokedex_SetBGMapMode_3ifDMG_4ifCGB);
    Pokedex_SetBGMapMode_3ifDMG_4ifCGB();
    // CALL(aPokedex_ResetBGMapMode);
    Pokedex_ResetBGMapMode();
    // CALL(aPokedex_DrawMainScreenBG);
    Pokedex_DrawMainScreenBG();
    // LD_A(POKEDEX_SCX);
    // LDH_addr_A(hSCX);
    hram.hSCX = POKEDEX_SCX;

    // LD_A_addr(wCurDexMode);
    // CP_A(DEXMODE_OLD);
    // LD_A(0x4a);
    // IF_Z goto okay;
    // LD_A(0x47);

// okay:
    // LDH_addr_A(hWX);
    hram.hWX = (wram->wCurDexMode == DEXMODE_OLD)? 0x4a: 0x47;
    // XOR_A_A;
    // LDH_addr_A(hWY);
    hram.hWY = 0;
    // CALL(aWaitBGMap);
    WaitBGMap();

    // CALL(aPokedex_ResetBGMapMode);
    Pokedex_ResetBGMapMode();
    // LD_A(-1);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = 0xff;
    // LD_A(SCGB_POKEDEX);
    // CALL(aPokedex_GetSGBLayout);
    Pokedex_GetSGBLayout(SCGB_POKEDEX);
    // CALL(aPokedex_UpdateCursorOAM);
    Pokedex_UpdateCursorOAM();
    // FARCALL(aDrawPokedexListWindow);
    DrawPokedexListWindow();
    // hlcoord(0, 17, wTilemap);
    // LD_DE(mString_START_SEARCH);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(0, 17, wram->wTilemap), String_START_SEARCH);
    // LD_A(7);
    // LD_addr_A(wDexListingHeight);
    wram->wDexListingHeight = 7;
    // CALL(aPokedex_PrintListing);
    Pokedex_PrintListing();
    // CALL(aPokedex_IncrementDexPointer);
    Pokedex_IncrementDexPointer();
    // RET;
}

void Pokedex_UpdateMainScreen(void){
    // LD_HL(hJoyPressed);
    uint8_t pressed = hram.hJoyPressed;
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto b;
    if(pressed & B_BUTTON) {
    // b:
        // LD_A(DEXSTATE_EXIT);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEXSTATE_EXIT;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto a;
    else if(pressed & A_BUTTON) {
    // a:
        // CALL(aPokedex_GetSelectedMon);
        species_t species = Pokedex_GetSelectedMon();
        // CALL(aPokedex_CheckSeen);
        // RET_Z ;
        if(!Pokedex_CheckSeen(species))
            return;
        // LD_A(DEXSTATE_DEX_ENTRY_SCR);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEXSTATE_DEX_ENTRY_SCR;
        // LD_A(DEXSTATE_MAIN_SCR);
        // LD_addr_A(wPrevDexEntryJumptableIndex);
        wram->wPrevDexEntryJumptableIndex = DEXSTATE_MAIN_SCR;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(SELECT);
    // IF_NZ goto select;
    else if(pressed & SELECT) {
    // select:
        // CALL(aPokedex_BlackOutBG);
        Pokedex_BlackOutBG();
        // LD_A(DEXSTATE_OPTION_SCR);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEXSTATE_OPTION_SCR;
        // XOR_A_A;
        // LDH_addr_A(hSCX);
        hram.hSCX = 0;
        // LD_A(0xa7);
        // LDH_addr_A(hWX);
        hram.hWX = 0xa7;
        // CALL(aDelayFrame);
        DelayFrame();
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(START);
    // IF_NZ goto start;
    else if(pressed & START) {
    // start:
        // CALL(aPokedex_BlackOutBG);
        Pokedex_BlackOutBG();
        // LD_A(DEXSTATE_SEARCH_SCR);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEXSTATE_SEARCH_SCR;
        // XOR_A_A;
        // LDH_addr_A(hSCX);
        hram.hSCX = 0;
        // LD_A(0xa7);
        // LDH_addr_A(hWX);
        hram.hWX = 0xa7;
        // CALL(aDelayFrame);
        DelayFrame();
        // RET;
        return;
    }
    // CALL(aPokedex_ListingHandleDPadInput);
    // RET_NC ;
    if(!Pokedex_ListingHandleDPadInput())
        return;
    // CALL(aPokedex_UpdateCursorOAM);
    Pokedex_UpdateCursorOAM();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aPokedex_PrintListing);
    Pokedex_PrintListing();
    // CALL(aPokedex_SetBGMapMode3);
    Pokedex_SetBGMapMode3();
    // CALL(aPokedex_ResetBGMapMode);
    Pokedex_ResetBGMapMode();
    // RET;
}

void Pokedex_InitDexEntryScreen(void){
    // CALL(aLowVolume);
    LowVolume();
    // XOR_A_A;  // page 1
    // LD_addr_A(wPokedexStatus);
    wram->wPokedexStatus = 0;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aPokedex_LoadCurrentFootprint);
    Pokedex_LoadCurrentFootprint();
    // CALL(aPokedex_DrawDexEntryScreenBG);
    Pokedex_DrawDexEntryScreenBG();
    // CALL(aPokedex_InitArrowCursor);
    Pokedex_InitArrowCursor();
    // CALL(aPokedex_GetSelectedMon);
    species_t mon = Pokedex_GetSelectedMon();
    // LD_addr_A(wPrevDexEntry);
    wram->wPrevDexEntry = mon;
    // FARCALL(aDisplayDexEntry);
    DisplayDexEntry(mon);
    // CALL(aPokedex_DrawFootprint);
    Pokedex_DrawFootprint();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_A(0xa7);
    // LDH_addr_A(hWX);
    hram.hWX = 0xa7;
    // CALL(aPokedex_GetSelectedMon);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = Pokedex_GetSelectedMon();
    // LD_A(SCGB_POKEDEX);
    // CALL(aPokedex_GetSGBLayout);
    Pokedex_GetSGBLayout(SCGB_POKEDEX);
    // LD_A_addr(wCurPartySpecies);
    // CALL(aPlayMonCry);
    PlayMonCry(wram->wCurPartySpecies);
    // CALL(aPokedex_IncrementDexPointer);
    Pokedex_IncrementDexPointer();
    // RET;
}

void Pokedex_UpdateDexEntryScreen(void){
    // LD_DE(mDexEntryScreen_ArrowCursorData);
    // CALL(aPokedex_MoveArrowCursor);
    Pokedex_MoveArrowCursor(&DexEntryScreen_ArrowCursorData);
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto return_to_prev_screen;
    if(hram.hJoyPressed & B_BUTTON) {
    // return_to_prev_screen:
        // LD_A_addr(wLastVolume);
        // AND_A_A;
        // IF_Z goto max_volume;
        if(wram->wLastVolume != 0) {
            // LD_A(MAX_VOLUME);
            // LD_addr_A(wLastVolume);
            wram->wLastVolume = MAX_VOLUME;
        }

    // max_volume:
        // CALL(aMaxVolume);
        MaxVolume();
        // LD_A_addr(wPrevDexEntryJumptableIndex);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = wram->wPrevDexEntryJumptableIndex;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto do_menu_action;
    if(hram.hJoyPressed & A_BUTTON) {
    // do_menu_action:
        // LD_A_addr(wDexArrowCursorPosIndex);
        // LD_HL(mDexEntryScreen_MenuActionJumptable);
        // CALL(aPokedex_LoadPointer);
        // JP_hl;
        return DexEntryScreen_MenuActionJumptable(wram->wDexArrowCursorPosIndex);
    }
    // CALL(aPokedex_NextOrPreviousDexEntry);
    // RET_NC ;
    if(!Pokedex_NextOrPreviousDexEntry())
        return;
    // CALL(aPokedex_IncrementDexPointer);
    Pokedex_IncrementDexPointer();
    // RET;
}

void Pokedex_Page(void){
    // LD_A_addr(wPokedexStatus);
    // XOR_A(1);  // toggle page
    // LD_addr_A(wPokedexStatus);
    wram->wPokedexStatus ^= 1;
    // CALL(aPokedex_GetSelectedMon);
    species_t species = Pokedex_GetSelectedMon();
    // LD_addr_A(wPrevDexEntry);
    wram->wPrevDexEntry = species;
    // FARCALL(aDisplayDexEntry);
    DisplayDexEntry(species);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // RET;
}

void Pokedex_ReinitDexEntryScreen(void){
//  Reinitialize the Pokédex entry screen after changing the selected mon.
    // CALL(aPokedex_BlackOutBG);
    Pokedex_BlackOutBG();
    // XOR_A_A;  // page 1
    // LD_addr_A(wPokedexStatus);
    wram->wPokedexStatus = 1;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aPokedex_DrawDexEntryScreenBG);
    Pokedex_DrawDexEntryScreenBG();
    // CALL(aPokedex_InitArrowCursor);
    Pokedex_InitArrowCursor();
    // CALL(aPokedex_LoadCurrentFootprint);
    Pokedex_LoadCurrentFootprint();
    // CALL(aPokedex_GetSelectedMon);
    species_t mon = Pokedex_GetSelectedMon();
    // LD_addr_A(wPrevDexEntry);
    wram->wPrevDexEntry = mon;
    // FARCALL(aDisplayDexEntry);
    DisplayDexEntry(mon);
    // CALL(aPokedex_DrawFootprint);
    Pokedex_DrawFootprint();
    // CALL(aPokedex_LoadSelectedMonTiles);
    Pokedex_LoadSelectedMonTiles();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aPokedex_GetSelectedMon);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = Pokedex_GetSelectedMon();
    // LD_A(SCGB_POKEDEX);
    // CALL(aPokedex_GetSGBLayout);
    Pokedex_GetSGBLayout(SCGB_POKEDEX);
    // LD_A_addr(wCurPartySpecies);
    // CALL(aPlayMonCry);
    PlayMonCry(mon);
    // LD_HL(wJumptableIndex);
    // DEC_hl;
    wram->wJumptableIndex--;
    // RET;
}

void DexEntryScreen_MenuActionJumptable(uint8_t a){
    //dw ['Pokedex_Page'];
    //dw ['.Area'];
    //dw ['.Cry'];
    //dw ['.Print'];
    switch(a) {
    case 0:
        return Pokedex_Page();
    case 1:
    // Area:
        // CALL(aPokedex_BlackOutBG);
        Pokedex_BlackOutBG();
        // XOR_A_A;
        // LDH_addr_A(hSCX);
        hram.hSCX = 0;
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A(0x7);
        // LDH_addr_A(hWX);
        hram.hWX = 0x7;
        // LD_A(0x90);
        // LDH_addr_A(hWY);
        hram.hWY = 0x90;
        // CALL(aPokedex_GetSelectedMon);
        // LD_A_addr(wDexCurLocation);
        // LD_E_A;
        // PREDEF(pPokedex_GetArea);
        Pokedex_GetArea(wram->wDexCurLocation, Pokedex_GetSelectedMon());
        // CALL(aPokedex_BlackOutBG);
        Pokedex_BlackOutBG();
        // CALL(aDelayFrame);
        DelayFrame();
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram.hBGMapMode = BGMAPMODE_NONE;
        // LD_A(0x90);
        // LDH_addr_A(hWY);
        hram.hWY = 0x90;
        // LD_A(POKEDEX_SCX);
        // LDH_addr_A(hSCX);
        hram.hSCX = POKEDEX_SCX;
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aPokedex_RedisplayDexEntry);
        Pokedex_RedisplayDexEntry();
        // CALL(aPokedex_LoadSelectedMonTiles);
        Pokedex_LoadSelectedMonTiles();
        // CALL(aWaitBGMap);
        WaitBGMap();
        // CALL(aPokedex_GetSelectedMon);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = Pokedex_GetSelectedMon();
        // LD_A(SCGB_POKEDEX);
        // CALL(aPokedex_GetSGBLayout);
        Pokedex_GetSGBLayout(SCGB_POKEDEX);
        // RET;
        return;

    case 2:
    // Cry:
        // CALL(aPokedex_GetSelectedMon);
        // LD_A_addr(wTempSpecies);
        // CALL(aGetCryIndex);
        // LD_E_C;
        // LD_D_B;
        // CALL(aPlayCry);
        PlayMonCry2(Pokedex_GetSelectedMon());
        // RET;
        return;

    case 3: {
    // Print:
        // CALL(aPokedex_ApplyPrintPals);
        Pokedex_ApplyPrintPals();
        // XOR_A_A;
        // LDH_addr_A(hSCX);
        hram.hSCX = 0x0;
        // LD_A_addr(wPrevDexEntryBackup);
        // PUSH_AF;
        uint8_t prevDexEntry = wram->wPrevDexEntryBackup;
        // LD_A_addr(wPrevDexEntryJumptableIndex);
        // PUSH_AF;
        uint8_t prevDexEntryJtIdx = wram->wPrevDexEntryJumptableIndex;
        // LD_A_addr(wJumptableIndex);
        // PUSH_AF;
        uint8_t jumptableIndex = wram->wJumptableIndex;
        // FARCALL(aPrintDexEntry);
        PrintDexEntry();
        // POP_AF;
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = jumptableIndex;
        // POP_AF;
        // LD_addr_A(wPrevDexEntryJumptableIndex);
        wram->wPrevDexEntryJumptableIndex = prevDexEntryJtIdx;
        // POP_AF;
        // LD_addr_A(wPrevDexEntryBackup);
        wram->wPrevDexEntryBackup = prevDexEntry;
        // CALL(aClearBGPalettes);
        ClearBGPalettes();
        // CALL(aDisableLCD);
        DisableLCD();
        // CALL(aPokedex_LoadInvertedFont);
        Pokedex_LoadInvertedFont();
        // CALL(aPokedex_RedisplayDexEntry);
        Pokedex_RedisplayDexEntry();
        // CALL(aEnableLCD);
        EnableLCD();
        // CALL(aWaitBGMap);
        WaitBGMap();
        // LD_A(POKEDEX_SCX);
        // LDH_addr_A(hSCX);
        hram.hSCX = POKEDEX_SCX;
        // CALL(aPokedex_ApplyUsualPals);
        Pokedex_ApplyUsualPals();
        // RET;
    } return;
    }
}

void Pokedex_RedisplayDexEntry(void){
    // CALL(aPokedex_DrawDexEntryScreenBG);
    Pokedex_DrawDexEntryScreenBG();
    // CALL(aPokedex_GetSelectedMon);
    // FARCALL(aDisplayDexEntry);
    DisplayDexEntry(Pokedex_GetSelectedMon());
    // CALL(aPokedex_DrawFootprint);
    Pokedex_DrawFootprint();
    // RET;
}

void Pokedex_InitOptionScreen(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aPokedex_DrawOptionScreenBG);
    Pokedex_DrawOptionScreenBG();
    // CALL(aPokedex_InitArrowCursor);
    Pokedex_InitArrowCursor();
// point cursor to the current dex mode (modes == menu item indexes)
    // LD_A_addr(wCurDexMode);
    // LD_addr_A(wDexArrowCursorPosIndex);
    wram->wDexArrowCursorPosIndex = wram->wCurDexMode;
    // CALL(aPokedex_DisplayModeDescription);
    Pokedex_DisplayModeDescription();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_A(SCGB_POKEDEX_SEARCH_OPTION);
    // CALL(aPokedex_GetSGBLayout);
    Pokedex_GetSGBLayout(SCGB_POKEDEX_SEARCH_OPTION);
    // CALL(aPokedex_IncrementDexPointer);
    Pokedex_IncrementDexPointer();
    // RET;
}

static const struct ArrowCursorData Pokedex_UpdateOptionScreen_NoUnownModeArrowCursorData = {
    .mask = D_UP | D_DOWN, 
    .count = 3,
    .coords = (const uint16_t[]){
        coord(2, 4, 0),  // NEW
        coord(2, 6, 0),  // OLD
        coord(2, 8, 0),  // ABC
    },
};

static const struct ArrowCursorData Pokedex_UpdateOptionScreen_ArrowCursorData = {
    .mask = D_UP | D_DOWN,
    .count = 4,
    .coords = (const uint16_t[]){
        coord(2,  4, 0),  // NEW
        coord(2,  6, 0),  // OLD
        coord(2,  8, 0),  // ABC
        coord(2, 10, 0),  // UNOWN
    },
};

void Pokedex_UpdateOptionScreen(void){
    // LD_A_addr(wUnlockedUnownMode);
    // AND_A_A;
    // IF_NZ goto okay;
    // LD_DE(mPokedex_UpdateOptionScreen_NoUnownModeArrowCursorData);
    // goto okay2;

// okay:
    // LD_DE(mPokedex_UpdateOptionScreen_ArrowCursorData);
    const struct ArrowCursorData* cursorData = (wram->wUnlockedUnownMode == 0)
        ? &Pokedex_UpdateOptionScreen_NoUnownModeArrowCursorData
        : &Pokedex_UpdateOptionScreen_ArrowCursorData;

// okay2:
    // CALL(aPokedex_MoveArrowCursor);
    // CALL_C (aPokedex_DisplayModeDescription);
    if(Pokedex_MoveArrowCursor(cursorData))
        Pokedex_DisplayModeDescription();
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(SELECT | B_BUTTON);
    // IF_NZ goto return_to_main_screen;
    if(hram.hJoyPressed & (SELECT | B_BUTTON)) {
    // return_to_main_screen:
        // CALL(aPokedex_BlackOutBG);
        Pokedex_BlackOutBG();
        // LD_A(DEXSTATE_MAIN_SCR);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEXSTATE_MAIN_SCR;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto do_menu_action;
    if(hram.hJoyPressed & A_BUTTON){
    // do_menu_action:
        // LD_A_addr(wDexArrowCursorPosIndex);
        // LD_HL(mPokedex_UpdateOptionScreen_MenuActionJumptable);
        // CALL(aPokedex_LoadPointer);
        // JP_hl;
        uint8_t b;
        switch(wram->wDexArrowCursorPosIndex){
        // MenuActionJumptable:
            //dw ['.MenuAction_NewMode'];
            //dw ['.MenuAction_OldMode'];
            //dw ['.MenuAction_ABCMode'];
            //dw ['.MenuAction_UnownMode'];

        case 0:
        // MenuAction_NewMode:
            // LD_B(DEXMODE_NEW);
            b = DEXMODE_NEW;
            // goto ChangeMode;
            break;

        case 1:
        // MenuAction_OldMode:
            // LD_B(DEXMODE_OLD);
            b = DEXMODE_OLD;
            // goto ChangeMode;
            break;

        case 2:
        // MenuAction_ABCMode:
            // LD_B(DEXMODE_ABC);
            b = DEXMODE_ABC;
            break;

        default:
        case 3:
        // MenuAction_UnownMode:
            // CALL(aPokedex_BlackOutBG);
            Pokedex_BlackOutBG();
            // LD_A(DEXSTATE_UNOWN_MODE);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = DEXSTATE_UNOWN_MODE;
            // RET;
            return;
        }

    // ChangeMode:
        // LD_A_addr(wCurDexMode);
        // CP_A_B;
        // IF_Z goto skip_changing_mode;  // Skip if new mode is same as current.
        if(wram->wCurDexMode != b){
            // LD_A_B;
            // LD_addr_A(wCurDexMode);
            wram->wCurDexMode = b;
            // CALL(aPokedex_OrderMonsByMode);
            Pokedex_OrderMonsByMode();
            // CALL(aPokedex_DisplayChangingModesMessage);
            Pokedex_DisplayChangingModesMessage();
            // XOR_A_A;
            // LD_addr_A(wDexListingScrollOffset);
            wram->wDexListingScrollOffset = 0;
            // LD_addr_A(wDexListingCursor);
            wram->wDexListingCursor = 0;
            // CALL(aPokedex_InitCursorPosition);
            Pokedex_InitCursorPosition();
        }

    // skip_changing_mode:
        // CALL(aPokedex_BlackOutBG);
        Pokedex_BlackOutBG();
        // LD_A(DEXSTATE_MAIN_SCR);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEXSTATE_MAIN_SCR;
        // RET;
        return;
    }
    // RET;
}

void Pokedex_InitSearchScreen(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aPokedex_DrawSearchScreenBG);
    Pokedex_DrawSearchScreenBG();
    // CALL(aPokedex_InitArrowCursor);
    Pokedex_InitArrowCursor();
    // LD_A(NORMAL + 1);
    // LD_addr_A(wDexSearchMonType1);
    wram->wDexSearchMonType1 = NORMAL + 1;
    // XOR_A_A;
    // LD_addr_A(wDexSearchMonType2);
    wram->wDexSearchMonType2 = 0;
    // CALL(aPokedex_PlaceSearchScreenTypeStrings);
    Pokedex_PlaceSearchScreenTypeStrings();
    // XOR_A_A;
    // LD_addr_A(wDexSearchSlowpokeFrame);
    wram->wDexSearchSlowpokeFrame = 0x0;
    // FARCALL(aDoDexSearchSlowpokeFrame);
    DoDexSearchSlowpokeFrame();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_A(SCGB_POKEDEX_SEARCH_OPTION);
    // CALL(aPokedex_GetSGBLayout);
    Pokedex_GetSGBLayout(SCGB_POKEDEX_SEARCH_OPTION);
    // CALL(aPokedex_IncrementDexPointer);
    Pokedex_IncrementDexPointer();
    // RET;
}

static const struct ArrowCursorData Pokedex_UpdateSearchScreen_ArrowCursorData = {
    .mask = D_UP | D_DOWN, 
    .count = 4,
    .coords = (const uint16_t[]){
        coord(2,  4, 0),  // TYPE 1
        coord(2,  6, 0),  // TYPE 2
        coord(2, 13, 0),  // BEGIN SEARCH
        coord(2, 15, 0),  // CANCEL
    },
};

void Pokedex_UpdateSearchScreen(void){
    // LD_DE(mPokedex_UpdateSearchScreen_ArrowCursorData);
    // CALL(aPokedex_MoveArrowCursor);
    Pokedex_MoveArrowCursor(&Pokedex_UpdateSearchScreen_ArrowCursorData);
    // CALL(aPokedex_UpdateSearchMonType);
    // CALL_C (aPokedex_PlaceSearchScreenTypeStrings);
    if(Pokedex_UpdateSearchMonType())
        Pokedex_PlaceSearchScreenTypeStrings();
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(START | B_BUTTON);
    // IF_NZ goto cancel;
    if(hram.hJoyPressed & (START | B_BUTTON)){
    // cancel:
        // CALL(aPokedex_BlackOutBG);
        Pokedex_BlackOutBG();
        // LD_A(DEXSTATE_MAIN_SCR);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEXSTATE_MAIN_SCR;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto do_menu_action;
    else if(hram.hJoyPressed & A_BUTTON){
    // do_menu_action:
        // LD_A_addr(wDexArrowCursorPosIndex);
        // LD_HL(mPokedex_UpdateSearchScreen_MenuActionJumptable);
        // CALL(aPokedex_LoadPointer);
        // JP_hl;
        switch(wram->wDexArrowCursorPosIndex){
        // MenuActionJumptable:
            //dw ['.MenuAction_MonSearchType'];
            //dw ['.MenuAction_MonSearchType'];
            //dw ['.MenuAction_BeginSearch'];
            //dw ['.MenuAction_Cancel'];
        case 0:
        case 1:
        // MenuAction_MonSearchType:
            // CALL(aPokedex_NextSearchMonType);
            Pokedex_NextSearchMonType();
            // CALL(aPokedex_PlaceSearchScreenTypeStrings);
            Pokedex_PlaceSearchScreenTypeStrings();
            // RET;
            return;

        case 2:
        // MenuAction_BeginSearch:
            // CALL(aPokedex_SearchForMons);
            Pokedex_SearchForMons();
            // FARCALL(aAnimateDexSearchSlowpoke);
            AnimateDexSearchSlowpoke();
            // LD_A_addr(wDexSearchResultCount);
            // AND_A_A;
            // IF_NZ goto show_search_results;
            if(wram->wDexSearchResultCount == 0){
            //  No mon with matching types was found.
                // CALL(aPokedex_OrderMonsByMode);
                Pokedex_OrderMonsByMode();
                // CALL(aPokedex_DisplayTypeNotFoundMessage);
                Pokedex_DisplayTypeNotFoundMessage();
                // XOR_A_A;
                // LDH_addr_A(hBGMapMode);
                hram.hBGMapMode = BGMAPMODE_NONE;
                // CALL(aPokedex_DrawSearchScreenBG);
                Pokedex_DrawSearchScreenBG();
                // CALL(aPokedex_InitArrowCursor);
                Pokedex_InitArrowCursor();
                // CALL(aPokedex_PlaceSearchScreenTypeStrings);
                Pokedex_PlaceSearchScreenTypeStrings();
                // CALL(aWaitBGMap);
                WaitBGMap();
                // RET;
                return;
            }

        // show_search_results:
            // LD_addr_A(wDexListingEnd);
            wram->wDexListingEnd = wram->wDexSearchResultCount;
            // LD_A_addr(wDexListingScrollOffset);
            // LD_addr_A(wDexListingScrollOffsetBackup);
            wram->wDexListingScrollOffsetBackup = wram->wDexListingScrollOffset;
            // LD_A_addr(wDexListingCursor);
            // LD_addr_A(wDexListingCursorBackup);
            wram->wDexListingCursorBackup = wram->wDexListingCursor;
            // LD_A_addr(wPrevDexEntry);
            // LD_addr_A(wPrevDexEntryBackup);
            wram->wPrevDexEntryBackup = wram->wPrevDexEntry;
            // XOR_A_A;
            // LD_addr_A(wDexListingScrollOffset);
            wram->wDexListingScrollOffset = 0;
            // LD_addr_A(wDexListingCursor);
            wram->wDexListingCursor = 0;
            // CALL(aPokedex_BlackOutBG);
            Pokedex_BlackOutBG();
            // LD_A(DEXSTATE_SEARCH_RESULTS_SCR);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = DEXSTATE_SEARCH_RESULTS_SCR;
            // RET;
            return;

        case 3:
        // MenuAction_Cancel:
            // CALL(aPokedex_BlackOutBG);
            Pokedex_BlackOutBG();
            // LD_A(DEXSTATE_MAIN_SCR);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = DEXSTATE_MAIN_SCR;
            // RET;
            return;
        }
    }
    // RET;
}

void Pokedex_InitSearchResultsScreen(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // XOR_A_A;
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x0);
    // CALL(aPokedex_SetBGMapMode4);
    Pokedex_SetBGMapMode4();
    // CALL(aPokedex_ResetBGMapMode);
    Pokedex_ResetBGMapMode();
    // FARCALL(aDrawPokedexSearchResultsWindow);
    DrawPokedexSearchResultsWindow();
    // CALL(aPokedex_PlaceSearchResultsTypeStrings);
    Pokedex_PlaceSearchResultsTypeStrings();
    // LD_A(4);
    // LD_addr_A(wDexListingHeight);
    wram->wDexListingHeight = 4;
    // CALL(aPokedex_PrintListing);
    Pokedex_PrintListing();
    // CALL(aPokedex_SetBGMapMode3);
    Pokedex_SetBGMapMode3();
    // CALL(aPokedex_ResetBGMapMode);
    Pokedex_ResetBGMapMode();
    // CALL(aPokedex_DrawSearchResultsScreenBG);
    Pokedex_DrawSearchResultsScreenBG();
    // LD_A(POKEDEX_SCX);
    // LDH_addr_A(hSCX);
    hram.hSCX = POKEDEX_SCX;
    // LD_A(0x4a);
    // LDH_addr_A(hWX);
    hram.hWX = 0x4a;
    // XOR_A_A;
    // LDH_addr_A(hWY);
    hram.hWY = 0x0;
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aPokedex_ResetBGMapMode);
    Pokedex_ResetBGMapMode();
    // FARCALL(aDrawPokedexSearchResultsWindow);
    DrawPokedexSearchResultsWindow();
    // CALL(aPokedex_PlaceSearchResultsTypeStrings);
    Pokedex_PlaceSearchResultsTypeStrings();
    // CALL(aPokedex_UpdateSearchResultsCursorOAM);
    Pokedex_UpdateSearchResultsCursorOAM();
    // LD_A(-1);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = (species_t)-1;
    // LD_A(SCGB_POKEDEX);
    // CALL(aPokedex_GetSGBLayout);
    Pokedex_GetSGBLayout(SCGB_POKEDEX);
    // CALL(aPokedex_IncrementDexPointer);
    Pokedex_IncrementDexPointer();
    // RET;
}

void Pokedex_UpdateSearchResultsScreen(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto return_to_search_screen;
    if(hram.hJoyPressed & B_BUTTON){
    // return_to_search_screen:
        // LD_A_addr(wDexListingScrollOffsetBackup);
        // LD_addr_A(wDexListingScrollOffset);
        wram->wDexListingScrollOffset = wram->wDexListingScrollOffsetBackup;
        // LD_A_addr(wDexListingCursorBackup);
        // LD_addr_A(wDexListingCursor);
        wram->wDexListingCursor = wram->wDexListingCursorBackup;
        // LD_A_addr(wPrevDexEntryBackup);
        // LD_addr_A(wPrevDexEntry);
        wram->wPrevDexEntry = wram->wPrevDexEntryBackup;
        // CALL(aPokedex_BlackOutBG);
        Pokedex_BlackOutBG();
        // CALL(aClearSprites);
        ClearSprites();
        // CALL(aPokedex_OrderMonsByMode);
        Pokedex_OrderMonsByMode();
        // LD_A(DEXSTATE_SEARCH_SCR);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEXSTATE_SEARCH_SCR;
        // XOR_A_A;
        // LDH_addr_A(hSCX);
        hram.hSCX = 0x0;
        // LD_A(0xa7);
        // LDH_addr_A(hWX);
        hram.hWX = 0xa7;
        // RET;
        return;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto go_to_dex_entry;
    if(hram.hJoyPressed & A_BUTTON){
    // go_to_dex_entry:
        // CALL(aPokedex_GetSelectedMon);
        // CALL(aPokedex_CheckSeen);
        // RET_Z ;
        if(!Pokedex_CheckSeen(Pokedex_GetSelectedMon()))
            return;
        // LD_A(DEXSTATE_DEX_ENTRY_SCR);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEXSTATE_DEX_ENTRY_SCR;
        // LD_A(DEXSTATE_SEARCH_RESULTS_SCR);
        // LD_addr_A(wPrevDexEntryJumptableIndex);
        wram->wPrevDexEntryJumptableIndex = DEXSTATE_SEARCH_RESULTS_SCR;
        // RET;
        return;
    }
    // CALL(aPokedex_ListingHandleDPadInput);
    // RET_NC ;
    if(!Pokedex_ListingHandleDPadInput())
        return;
    // CALL(aPokedex_UpdateSearchResultsCursorOAM);
    Pokedex_UpdateSearchResultsCursorOAM();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // CALL(aPokedex_PrintListing);
    Pokedex_PrintListing();
    // CALL(aPokedex_SetBGMapMode3);
    Pokedex_SetBGMapMode3();
    // CALL(aPokedex_ResetBGMapMode);
    Pokedex_ResetBGMapMode();
    // RET;
}

void Pokedex_InitUnownMode(void){
    // CALL(aPokedex_LoadUnownFont);
    Pokedex_LoadUnownFont();
    // CALL(aPokedex_DrawUnownModeBG);
    Pokedex_DrawUnownModeBG();
    // XOR_A_A;
    // LD_addr_A(wDexCurUnownIndex);
    wram->wDexCurUnownIndex = 0;
    // CALL(aPokedex_LoadUnownFrontpicTiles);
    Pokedex_LoadUnownFrontpicTiles();
    // CALL(aPokedex_UnownModePlaceCursor);
    Pokedex_UnownModePlaceCursor();
    // FARCALL(aPrintUnownWord);
    PrintUnownWord();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_A(SCGB_POKEDEX_UNOWN_MODE);
    // CALL(aPokedex_GetSGBLayout);
    Pokedex_GetSGBLayout(SCGB_POKEDEX_UNOWN_MODE);
    // CALL(aPokedex_IncrementDexPointer);
    Pokedex_IncrementDexPointer();
    // RET;
}

void Pokedex_UpdateUnownMode(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(A_BUTTON | B_BUTTON);
    // IF_NZ goto a_b;
    if(hram.hJoyPressed & (A_BUTTON | B_BUTTON)){
    // a_b:
        // CALL(aPokedex_BlackOutBG);
        Pokedex_BlackOutBG();
        // LD_A(DEXSTATE_OPTION_SCR);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = DEXSTATE_OPTION_SCR;
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aPokedex_CheckSGB);
        // IF_NZ goto decompress;
        if(Pokedex_CheckSGB()){
            // FARCALL(aLoadSGBPokedexGFX2);
            LoadSGBPokedexGFX2();
            // goto done;
        }
        else {
        // decompress:
            // LD_HL(mPokedexLZ);
            // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
            // LD_BC((BANK(aPokedexLZ) << 8) | 58);
            // CALL(aDecompressRequest2bpp);
            LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x31, PokedexLZ, 0, 58);
        }
    // done:
        // RET;
        return;
    }
    // CALL(aPokedex_UnownModeHandleDPadInput);
    Pokedex_UnownModeHandleDPadInput();
    // RET;
}

void Pokedex_UnownModeHandleDPadInput(void){
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    uint8_t index;
    if(hram.hJoyLast & D_RIGHT){
    // right:
        // LD_A_addr(wDexUnownCount);
        // LD_E_A;
        // LD_HL(wDexCurUnownIndex);
        // LD_A_hl;
        // INC_A;
        // CP_A_E;
        // RET_NC ;
        if(wram->wDexCurUnownIndex + 1 >= wram->wDexUnownCount)
            return;
        // LD_A_hl;
        // INC_hl;
        index = wram->wDexCurUnownIndex++;
        // goto update;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    else if(hram.hJoyLast & D_LEFT){
    // left:
        // LD_HL(wDexCurUnownIndex);
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(wram->wDexCurUnownIndex == 0)
            return;
        // LD_A_hl;
        // DEC_hl;
        index = wram->wDexCurUnownIndex--;
    }
    else {
        // RET;
        return;
    }

// update:
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // POP_AF;
    // CALL(aPokedex_UnownModeEraseCursor);
    Pokedex_UnownModeEraseCursor(index);
    // CALL(aPokedex_LoadUnownFrontpicTiles);
    Pokedex_LoadUnownFrontpicTiles();
    // CALL(aPokedex_UnownModePlaceCursor);
    Pokedex_UnownModePlaceCursor();
    // FARCALL(aPrintUnownWord);
    PrintUnownWord();
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void Pokedex_UnownModeEraseCursor(uint8_t a){
    // LD_C(0x7f);
    // JR(mPokedex_UnownModeUpdateCursorGfx);
    return Pokedex_UnownModeUpdateCursorGfx(a, 0x7f);
}

void Pokedex_UnownModePlaceCursor(void){
    // LD_A_addr(wDexCurUnownIndex);
    // LD_C(FIRST_UNOWN_CHAR + NUM_UNOWN);  // diamond cursor

    return Pokedex_UnownModeUpdateCursorGfx(wram->wDexCurUnownIndex, FIRST_UNOWN_CHAR + NUM_UNOWN);
}

void Pokedex_UnownModeUpdateCursorGfx(uint8_t a, uint8_t c){
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mUnownModeLetterAndCursorCoords + 2);
    // for(int rept = 0; rept < 4; rept++){
    // ADD_HL_DE;
    // }
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_hl_C;
    wram->wTilemap[UnownModeLetterAndCursorCoords[2*a + 1]] = c;
    // RET;
}

bool Pokedex_NextOrPreviousDexEntry(void){
    // LD_A_addr(wDexListingCursor);
    // LD_addr_A(wBackupDexListingCursor);
    wram->wBackupDexListingCursor = wram->wDexListingCursor;
    // LD_A_addr(wDexListingScrollOffset);
    // LD_addr_A(wBackupDexListingPage);
    wram->wBackupDexListingPage = wram->wDexListingScrollOffset;
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto up;
    if(hram.hJoyLast & D_UP) {
        while(1) {
        // up:
            // LD_A_addr(wDexListingHeight);
            // LD_D_A;
            // LD_A_addr(wDexListingEnd);
            // LD_E_A;
            // CALL(aPokedex_ListingMoveCursorUp);
            // IF_NC goto nope;
            if(!Pokedex_ListingMoveCursorUp())
                goto nope;
            // CALL(aPokedex_GetSelectedMon);
            // CALL(aPokedex_CheckSeen);
            // IF_NZ goto yep;
            if(Pokedex_CheckSeen(Pokedex_GetSelectedMon()))
                return true;
            // goto up;
        }
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(hram.hJoyLast & D_DOWN) {
        while(1) {
        // down:
            // LD_A_addr(wDexListingHeight);
            // LD_D_A;
            // LD_A_addr(wDexListingEnd);
            // LD_E_A;
            // CALL(aPokedex_ListingMoveCursorDown);
            // IF_NC goto nope;
            if(!Pokedex_ListingMoveCursorDown(wram->wDexListingHeight, wram->wDexListingEnd))
                goto nope;
            // CALL(aPokedex_GetSelectedMon);
            // CALL(aPokedex_CheckSeen);
            // IF_NZ goto yep;
            if(Pokedex_CheckSeen(Pokedex_GetSelectedMon()))
                return true;
            // goto down;
        }
    }
    // AND_A_A;
    // RET;
    return false;

// yep:
    // SCF;
    // RET;

nope:
    // LD_A_addr(wBackupDexListingCursor);
    // LD_addr_A(wDexListingCursor);
    wram->wDexListingCursor = wram->wBackupDexListingCursor; 
    // LD_A_addr(wBackupDexListingPage);
    // LD_addr_A(wDexListingScrollOffset);
    wram->wDexListingScrollOffset = wram->wBackupDexListingPage; 
    // AND_A_A;
    // RET;
    return false;
}

//  Handles D-pad input for a list of Pokémon.
bool Pokedex_ListingHandleDPadInput(void){
    // LD_A_addr(wDexListingHeight);
    // LD_D_A;
    uint8_t d = wram->wDexListingHeight;
    // LD_A_addr(wDexListingEnd);
    // LD_E_A;
    uint8_t e = wram->wDexListingEnd;
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mPokedex_ListingMoveCursorUp);
    if(hram.hJoyLast & D_UP)
        return Pokedex_ListingMoveCursorUp();
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mPokedex_ListingMoveCursorDown);
    if(hram.hJoyLast & D_DOWN)
        return Pokedex_ListingMoveCursorDown(d, e);
    // LD_A_D;
    // CP_A_E;
    // JR_NC (mPokedex_ListingPosStayedSame);
    if(d >= e)
        return Pokedex_ListingPosStayedSame();
    // LD_A_hl;
    // AND_A(D_LEFT);
    // JR_NZ (mPokedex_ListingMoveUpOnePage);
    if(hram.hJoyLast & D_LEFT)
        return Pokedex_ListingMoveUpOnePage(d);
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // JR_NZ (mPokedex_ListingMoveDownOnePage);
    if(hram.hJoyLast & D_RIGHT)
        return Pokedex_ListingMoveDownOnePage(d, e);
    // JR(mPokedex_ListingPosStayedSame);
    return Pokedex_ListingPosStayedSame();
}

bool Pokedex_ListingMoveCursorUp(void){
    // LD_HL(wDexListingCursor);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto try_scrolling;
    if(wram->wDexListingCursor != 0) {
        // DEC_hl;
        --wram->wDexListingCursor;
        // JR(mPokedex_ListingPosChanged);
        return Pokedex_ListingPosChanged();
    }

// try_scrolling:
    // LD_HL(wDexListingScrollOffset);
    // LD_A_hl;
    // AND_A_A;
    // JR_Z (mPokedex_ListingPosStayedSame);
    if(wram->wDexListingScrollOffset == 0)
        return Pokedex_ListingPosStayedSame();
    // DEC_hl;
    --wram->wDexListingScrollOffset;
    // JR(mPokedex_ListingPosChanged);
    return Pokedex_ListingPosChanged();
}

bool Pokedex_ListingMoveCursorDown(uint8_t d, uint8_t e){
    // LD_HL(wDexListingCursor);
    uint8_t cursor = wram->wDexListingCursor;
    // LD_A_hl;
    // INC_A;
    // CP_A_E;
    // JR_NC (mPokedex_ListingPosStayedSame);
    if(cursor + 1 >= e)
        return Pokedex_ListingPosStayedSame();
    // CP_A_D;
    // IF_NC goto try_scrolling;
    if(cursor + 1 < d) {
        // INC_hl;
        ++wram->wDexListingCursor;
        // JR(mPokedex_ListingPosChanged);
        return Pokedex_ListingPosChanged();
    }

// try_scrolling:
    // LD_HL(wDexListingScrollOffset);
    // ADD_A_hl;
    // CP_A_E;
    // JR_NC (mPokedex_ListingPosStayedSame);
    if(wram->wDexListingScrollOffset + cursor + 1 >= e)
        return Pokedex_ListingPosStayedSame();
    // INC_hl;
    wram->wDexListingScrollOffset++;
    // JR(mPokedex_ListingPosChanged);
    return Pokedex_ListingPosChanged();
}

bool Pokedex_ListingMoveUpOnePage(uint8_t d){
    // LD_HL(wDexListingScrollOffset);
    // LD_A_hl;
    // AND_A_A;
    // JR_Z (mPokedex_ListingPosStayedSame);
    if(wram->wDexListingScrollOffset == 0)
        return Pokedex_ListingPosStayedSame();
    // CP_A_D;
    // IF_NC goto not_near_top;
    if(wram->wDexListingScrollOffset < d) {
    //  If we're already less than page away from the top, go to the top.
        // XOR_A_A;
        // LD_hl_A;
        wram->wDexListingScrollOffset = 0;
        // JR(mPokedex_ListingPosChanged);
        return Pokedex_ListingPosChanged();
    }

// not_near_top:
    // SUB_A_D;
    // LD_hl_A;
    wram->wDexListingScrollOffset = wram->wDexListingScrollOffset - d;
    // JR(mPokedex_ListingPosChanged);
    return Pokedex_ListingPosChanged();
}

//  When moving down a page, the return value always report a change in position.
bool Pokedex_ListingMoveDownOnePage(uint8_t d, uint8_t e){
    // LD_HL(wDexListingScrollOffset);
    // LD_A_D;
    // ADD_A_A;
    // ADD_A_hl;
    uint16_t x = wram->wDexListingScrollOffset + (d << 1);
    // IF_C goto near_bottom;
    // CP_A_E;
    // IF_C goto not_near_bottom;
    if(x > 0xff || (x & 0xff) >= e) {
    // near_bottom:
        // LD_A_E;
        // SUB_A_D;
        // LD_hl_A;
        wram->wDexListingScrollOffset = e - d;
        // JR(mPokedex_ListingPosChanged);
        return Pokedex_ListingPosChanged();
    }

// not_near_bottom:
    // LD_A_hl;
    // ADD_A_D;
    // LD_hl_A;
    wram->wDexListingScrollOffset += d;
    // JR(mPokedex_ListingPosChanged);
    return Pokedex_ListingPosChanged();
}

bool Pokedex_ListingPosStayedSame(void){
    // AND_A_A;
    // RET;
    return false;
}

bool Pokedex_ListingPosChanged(void){
    // SCF;
    // RET;
    return true;
}

tile_t* Pokedex_FillColumn(tile_t* hl, uint8_t b, uint8_t a){
//  Fills a column starting at hl, going downwards.
//  b is the height of the column, and a is the tile it's filled with.
    // PUSH_DE;
    // LD_DE(SCREEN_WIDTH);

    do {
    // loop:
        // LD_hl_A;
        *hl = a;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // POP_DE;
    // RET;
    return hl;
}

void Pokedex_DrawMainScreenBG(void){
//  Draws the left sidebar and the bottom bar on the main screen.
    // hlcoord(0, 17, wTilemap);
    // LD_DE(mString_START_SEARCH);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(0, 17, wram->wTilemap), String_START_SEARCH);
    // LD_A(0x32);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x32);
    // hlcoord(0, 0, wTilemap);
    // LD_BC((7 << 8) | 7);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 0, wram->wTilemap), 7, 7);
    // hlcoord(0, 9, wTilemap);
    // LD_BC((6 << 8) | 7);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 9, wram->wTilemap), 6, 7);
    // hlcoord(1, 11, wTilemap);
    // LD_DE(mString_SEEN);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(1, 11, wram->wTilemap), U82C(String_SEEN));
    // LD_HL(wPokedexSeen);
    // LD_B(wEndPokedexSeen - wPokedexSeen);
    // CALL(aCountSetBits);
    uint8_t seen = CountSetBits(gPokemon.pokedexSeen, sizeof(gPokemon.pokedexSeen));
    // LD_DE(wNumSetBits);
    // hlcoord(5, 12, wTilemap);
    // LD_BC((1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum(coord(5, 12, wram->wTilemap), &seen, 1, 3);
    // hlcoord(1, 14, wTilemap);
    // LD_DE(mString_OWN);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(1, 14, wram->wTilemap), U82C(String_OWN));
    // LD_HL(wPokedexCaught);
    // LD_B(wEndPokedexCaught - wPokedexCaught);
    // CALL(aCountSetBits);
    uint8_t caught = CountSetBits(gPokemon.pokedexCaught, sizeof(gPokemon.pokedexCaught));
    // LD_DE(wNumSetBits);
    // hlcoord(5, 15, wTilemap);
    // LD_BC((1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum(coord(5, 15, wram->wTilemap), &caught, 1, 3);
    // hlcoord(1, 17, wTilemap);
    // LD_DE(mString_SELECT_OPTION);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(1, 17, wram->wTilemap), String_SELECT_OPTION);
    // hlcoord(8, 1, wTilemap);
    // LD_B(7);
    // LD_A(0x5a);
    // CALL(aPokedex_FillColumn);
    Pokedex_FillColumn(coord(8, 1, wram->wTilemap), 7, 0x5a);
    // hlcoord(8, 10, wTilemap);
    // LD_B(6);
    // LD_A(0x5a);
    // CALL(aPokedex_FillColumn);
    Pokedex_FillColumn(coord(8, 10, wram->wTilemap), 6, 0x5a);
    // hlcoord(8, 0, wTilemap);
    // LD_hl(0x59);
    *coord(8, 0, wram->wTilemap) = 0x59;
    // hlcoord(8, 8, wTilemap);
    // LD_hl(0x53);
    *coord(8, 8, wram->wTilemap) = 0x53;
    // hlcoord(8, 9, wTilemap);
    // LD_hl(0x54);
    *coord(8, 9, wram->wTilemap) = 0x54;
    // hlcoord(8, 16, wTilemap);
    // LD_hl(0x5b);
    *coord(8, 16, wram->wTilemap) = 0x5b;
    // CALL(aPokedex_PlaceFrontpicTopLeftCorner);
    Pokedex_PlaceFrontpicTopLeftCorner();
    // RET;
}

const char String_SEEN[] = "SEEN""@";
const char String_OWN[] = "OWN""@";

// SELECT > OPTION
const uint8_t String_SELECT_OPTION[] = {0x3b, 0x48, 0x49, 0x4a, 0x44, 0x45, 0x46, 0x47, 0x50};
// fallthrough

// START > SEARCH
const uint8_t String_START_SEARCH[] = {0x3c, 0x3b, 0x41, 0x42, 0x43, 0x4b, 0x4c, 0x4d, 0x4e, 0x3c, 0x50};

void Pokedex_DrawDexEntryScreenBG(void){
    static const char Height[] = "HT  ?<ROCKET>?\?<DEXEND>"; // "HT  ?"', '0x5e', '"??"', '0x5f', '-1';  // HT  ?'??"
    static const char Weight[] = "WT   ???lb"; // "WT   ???lb"', '-1'
    static const char MenuItems[] = "<3f> PAGE AREA CRY PRNT<ff>";
    // CALL(aPokedex_FillBackgroundColor2);
    Pokedex_FillBackgroundColor2();
    // hlcoord(0, 0, wTilemap);
    // LD_BC((15 << 8) | 18);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 0, wram->wTilemap), 15, 18);
    // hlcoord(19, 0, wTilemap);
    // LD_hl(0x34);
    *coord(19, 0, wram->wTilemap) = 0x34;
    // hlcoord(19, 1, wTilemap);
    // LD_A(0x7f);
    // LD_B(15);
    // CALL(aPokedex_FillColumn);
    tile_t* hl = Pokedex_FillColumn(coord(19, 1, wram->wTilemap), 15, 0x7f);
    // LD_hl(0x39);
    *hl = 0x39;
    // hlcoord(1, 10, wTilemap);
    // LD_BC(19);
    // LD_A(0x61);
    // CALL(aByteFill);
    ByteFill(coord(1, 10, wram->wTilemap), 19, 0x61);
    // hlcoord(1, 17, wTilemap);
    // LD_BC(18);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(1, 17, wram->wTilemap), 18, 0x7f);
    // hlcoord(9, 7, wTilemap);
    // LD_DE(mPokedex_DrawDexEntryScreenBG_Height);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(9, 7, wram->wTilemap), U82C(Height));
    // hlcoord(9, 9, wTilemap);
    // LD_DE(mPokedex_DrawDexEntryScreenBG_Weight);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(9, 9, wram->wTilemap), U82C(Weight));
    // hlcoord(0, 17, wTilemap);
    // LD_DE(mPokedex_DrawDexEntryScreenBG_MenuItems);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(0, 17, wram->wTilemap), U82C(MenuItems));
    // CALL(aPokedex_PlaceFrontpicTopLeftCorner);
    Pokedex_PlaceFrontpicTopLeftCorner();
    // RET;

// Number:
//   //  unreferenced
    //db ['0x5c', '0x5d', '-1'];  // No.
}

void Pokedex_DrawOptionScreenBG(void){
    static const char Title[] = "<3b> OPTION <3c>"; //db ['0x3b', '" OPTION "', '0x3c', '-1'];
    static const char Modes[] = 
               "NEW #DEX MODE"
        t_next "OLD #DEX MODE"
        t_next "A to Z MODE";
    static const char UnownMode[] = "UNOWN MODE";
    // CALL(aPokedex_FillBackgroundColor2);
    Pokedex_FillBackgroundColor2();
    // hlcoord(0, 2, wTilemap);
    // LD_BC((8 << 8) | 18);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 2, wram->wTilemap), 8, 18);
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 12, wram->wTilemap), 4, 18);
    // hlcoord(0, 1, wTilemap);
    // LD_DE(mPokedex_DrawOptionScreenBG_Title);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(0, 1, wram->wTilemap), U82C(Title));
    // hlcoord(3, 4, wTilemap);
    // LD_DE(mPokedex_DrawOptionScreenBG_Modes);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Modes), coord(3, 4, wram->wTilemap));
    // LD_A_addr(wUnlockedUnownMode);
    // AND_A_A;
    // RET_Z ;
    if(wram->wUnlockedUnownMode == 0)
        return;
    // hlcoord(3, 10, wTilemap);
    // LD_DE(mPokedex_DrawOptionScreenBG_UnownMode);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(UnownMode), coord(3, 10, wram->wTilemap));
    // RET;
}

void Pokedex_DrawSearchScreenBG(void){
    static const char Title[] = "<3b> SEARCH <3c>"; //db ['0x3b', '" SEARCH "', '0x3c', '-1'];
    static const char TypeLeftRightArrows[] = "<3d>        <3e>"; //db ['0x3d', '"\t    "', '0x3e', '-1'];
    static const char Types[] = 
               "TYPE1"
        t_next "TYPE2";
    static const char Menu[] = 
               "BEGIN SEARCH!!"
        t_next "CANCEL";
    // CALL(aPokedex_FillBackgroundColor2);
    Pokedex_FillBackgroundColor2();
    // hlcoord(0, 2, wTilemap);
    // LD_BC((14 << 8) | 18);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 2, wram->wTilemap), 14, 18);
    // hlcoord(0, 1, wTilemap);
    // LD_DE(mPokedex_DrawSearchScreenBG_Title);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(0, 1, wram->wTilemap), U82C(Title));
    // hlcoord(8, 4, wTilemap);
    // LD_DE(mPokedex_DrawSearchScreenBG_TypeLeftRightArrows);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(8, 4, wram->wTilemap), U82C(TypeLeftRightArrows));
    // hlcoord(8, 6, wTilemap);
    // LD_DE(mPokedex_DrawSearchScreenBG_TypeLeftRightArrows);
    // CALL(aPokedex_PlaceString);
    Pokedex_PlaceString(coord(8, 6, wram->wTilemap), U82C(TypeLeftRightArrows));
    // hlcoord(3, 4, wTilemap);
    // LD_DE(mPokedex_DrawSearchScreenBG_Types);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Types), coord(3, 4, wram->wTilemap));
    // hlcoord(3, 13, wTilemap);
    // LD_DE(mPokedex_DrawSearchScreenBG_Menu);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Menu), coord(3, 13, wram->wTilemap));
    // RET;
}

void Pokedex_DrawSearchResultsScreenBG(void){
    static const char BottomWindowText[] = 
               "SEARCH RESULTS"
        t_next "  TYPE"
        t_next "    FOUND!";
    // CALL(aPokedex_FillBackgroundColor2);
    Pokedex_FillBackgroundColor2();
    // hlcoord(0, 0, wTilemap);
    // LD_BC((7 << 8) | 7);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 0, wram->wTilemap), 7, 7);
    // hlcoord(0, 11, wTilemap);
    // LD_BC((5 << 8) | 18);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 11, wram->wTilemap), 5, 18);
    // hlcoord(1, 12, wTilemap);
    // LD_DE(mPokedex_DrawSearchResultsScreenBG_BottomWindowText);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(BottomWindowText), coord(1, 12, wram->wTilemap));
    // LD_DE(wDexSearchResultCount);
    // hlcoord(1, 16, wTilemap);
    // LD_BC((1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum(coord(1, 16, wram->wTilemap), &wram->wDexSearchResultCount, 1, 3);
    // hlcoord(8, 0, wTilemap);
    // LD_hl(0x59);
    *coord(8, 0, wram->wTilemap) = 0x59;
    // hlcoord(8, 1, wTilemap);
    // LD_B(7);
    // LD_A(0x5a);
    // CALL(aPokedex_FillColumn);
    Pokedex_FillColumn(coord(8, 1, wram->wTilemap), 7, 0x5a);
    // hlcoord(8, 8, wTilemap);
    // LD_hl(0x53);
    *coord(8, 8, wram->wTilemap) = 0x53;
    // hlcoord(8, 9, wTilemap);
    // LD_hl(0x69);
    *coord(8, 9, wram->wTilemap) = 0x69;
    // hlcoord(8, 10, wTilemap);
    // LD_hl(0x6a);
    *coord(8, 10, wram->wTilemap) = 0x6a;
    // CALL(aPokedex_PlaceFrontpicTopLeftCorner);
    Pokedex_PlaceFrontpicTopLeftCorner();
    // RET;
}

void Pokedex_PlaceSearchResultsTypeStrings(void){
    // LD_A_addr(wDexSearchMonType1);
    // hlcoord(0, 14, wTilemap);
    // CALL(aPokedex_PlaceTypeString);
    Pokedex_PlaceTypeString(coord(0, 14, wram->wTilemap), wram->wDexSearchMonType1);
    // LD_A_addr(wDexSearchMonType1);
    // LD_B_A;
    // LD_A_addr(wDexSearchMonType2);
    // AND_A_A;
    // IF_Z goto done;
    // CP_A_B;
    // IF_Z goto done;
    if(wram->wDexSearchMonType2 != 0 && wram->wDexSearchMonType2 != wram->wDexSearchMonType1){
        // hlcoord(2, 15, wTilemap);
        // CALL(aPokedex_PlaceTypeString);
        Pokedex_PlaceTypeString(coord(2, 15, wram->wTilemap), wram->wDexSearchMonType2);
        // hlcoord(1, 15, wTilemap);
        // LD_hl(0xf3);
        *coord(1, 15, wram->wTilemap) = 0xf3;
    }

// done:
    // RET;
}

void Pokedex_DrawUnownModeBG(void){
    // CALL(aPokedex_FillBackgroundColor2);
    Pokedex_FillBackgroundColor2();
    // hlcoord(2, 1, wTilemap);
    // LD_BC((10 << 8) | 13);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(2, 1, wram->wTilemap), 10, 13);
    // hlcoord(2, 14, wTilemap);
    // LD_BC((1 << 8) | 13);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(2, 14, wram->wTilemap), 1, 13);
    // hlcoord(2, 15, wTilemap);
    // LD_hl(0x3d);
    *coord(2, 15, wram->wTilemap) = 0x3d;
    // hlcoord(16, 15, wTilemap);
    // LD_hl(0x3e);
    *coord(16, 15, wram->wTilemap) = 0x3e;
    // hlcoord(6, 5, wTilemap);
    // CALL(aPokedex_PlaceFrontpicAtHL);
    Pokedex_PlaceFrontpicAtHL(coord(6, 5, wram->wTilemap));
    // LD_DE(0);
    uint16_t de = 0;
    // LD_B(0);
    uint8_t b = 0;
    // LD_C(NUM_UNOWN);
    uint8_t c = NUM_UNOWN;

    do {
    // loop:
        // LD_HL(wUnownDex);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto done;
        if(gPokemon.unownDex[de] == 0)
            break;
        // PUSH_AF;
        // LD_HL(mUnownModeLetterAndCursorCoords);
        // for(int rept = 0; rept < 4; rept++){
        // ADD_HL_DE;
        // }
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // POP_AF;
        // ADD_A(FIRST_UNOWN_CHAR - 1);  // Unown A
        // LD_hl_A;
        wram->wTilemap[UnownModeLetterAndCursorCoords[de * 2]] = (FIRST_UNOWN_CHAR - 1) + gPokemon.unownDex[de];
        // INC_DE;
        ++de;
        // INC_B;
        ++b;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

// done:
    // LD_A_B;
    // LD_addr_A(wDexUnownCount);
    wram->wDexUnownCount = b;
    // RET;
}

const uint16_t UnownModeLetterAndCursorCoords[] = {
//  entries correspond to Unown forms
//            letter, cursor
    coord( 4, 11, 0), coord( 3, 11, 0),  // A
    coord( 4, 10, 0), coord( 3, 10, 0),  // B
    coord( 4,  9, 0), coord( 3,  9, 0),  // C
    coord( 4,  8, 0), coord( 3,  8, 0),  // D
    coord( 4,  7, 0), coord( 3,  7, 0),  // E
    coord( 4,  6, 0), coord( 3,  6, 0),  // F
    coord( 4,  5, 0), coord( 3,  5, 0),  // G
    coord( 4,  4, 0), coord( 3,  4, 0),  // H
    coord( 4,  3, 0), coord( 3,  2, 0),  // I
    coord( 5,  3, 0), coord( 5,  2, 0),  // J
    coord( 6,  3, 0), coord( 6,  2, 0),  // K
    coord( 7,  3, 0), coord( 7,  2, 0),  // L
    coord( 8,  3, 0), coord( 8,  2, 0),  // M
    coord( 9,  3, 0), coord( 9,  2, 0),  // N
    coord(10,  3, 0), coord(10,  2, 0),  // O
    coord(11,  3, 0), coord(11,  2, 0),  // P
    coord(12,  3, 0), coord(12,  2, 0),  // Q
    coord(13,  3, 0), coord(13,  2, 0),  // R
    coord(14,  3, 0), coord(15,  2, 0),  // S
    coord(14,  4, 0), coord(15,  4, 0),  // T
    coord(14,  5, 0), coord(15,  5, 0),  // U
    coord(14,  6, 0), coord(15,  6, 0),  // V
    coord(14,  7, 0), coord(15,  7, 0),  // W
    coord(14,  8, 0), coord(15,  8, 0),  // X
    coord(14,  9, 0), coord(15,  9, 0),  // Y
    coord(14, 10, 0), coord(15, 10, 0),  // Z
};

void Pokedex_FillBackgroundColor2(void){
    // hlcoord(0, 0, wTilemap);
    // LD_A(0x32);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x32);
    // RET;
}

void Pokedex_PlaceFrontpicTopLeftCorner(void){
    // hlcoord(1, 1, wTilemap);
    return Pokedex_PlaceFrontpicAtHL(coord(1, 1, wram->wTilemap));
}

void Pokedex_PlaceFrontpicAtHL(tile_t* hl){
    // XOR_A_A;
    tile_t a = 0;
    // LD_B(0x7);
    uint8_t b = 0x7;

    do {
    // row:
        // LD_C(0x7);
        uint8_t c = 0x7;
        // PUSH_AF;
        tile_t a2 = a;
        // PUSH_HL;
        tile_t* hl2 = hl;

        do {
        // col:
            // LD_hli_A;
            *(hl2++) = a2;
            // ADD_A(0x7);
            a2++;
            // DEC_C;
            // IF_NZ goto col;
        } while(--c != 0);
        // POP_HL;
        // LD_DE(SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // POP_AF;
        // INC_A;
        // DEC_B;
        // IF_NZ goto row;
    } while(a = a + 7, --b != 0);
    // RET;
}

void Pokedex_PlaceString(uint8_t* hl, const uint8_t* de){
    while(*de != CHAR_TERM) {
    // loop:
        // LD_A_de;
        // CP_A(-1);
        // RET_Z ;
        // INC_DE;
        // LD_hli_A;
        *(hl++) = *(de++);
        // goto loop;
    }
}

static tile_t* Pokedex_PlaceBorder_FillRow(tile_t* hl, uint8_t c, uint8_t d);

void Pokedex_PlaceBorder(tile_t* hl, uint8_t b, uint8_t c){
    // PUSH_HL;
    tile_t* hl2 = hl;
    // LD_A(0x33);
    // LD_hli_A;
    *(hl2++) = 0x33;
    // LD_D(0x34);
    // CALL(aPokedex_PlaceBorder_FillRow);
    hl2 = Pokedex_PlaceBorder_FillRow(hl2, c, 0x34);
    // LD_A(0x35);
    // LD_hl_A;
    *hl2 = 0x35;
    // POP_HL;
    // LD_DE(SCREEN_WIDTH);
    hl += SCREEN_WIDTH;
    // ADD_HL_DE;

    do {
    // loop:
        // PUSH_HL;
        tile_t* hl2 = hl;
        // LD_A(0x36);
        // LD_hli_A;
        *(hl2++) = 0x36;
        // LD_D(0x7f);
        // CALL(aPokedex_PlaceBorder_FillRow);
        hl2 = Pokedex_PlaceBorder_FillRow(hl2, c, 0x7f);
        // LD_A(0x37);
        // LD_hl_A;
        *hl2 = 0x37;
        // POP_HL;
        // LD_DE(SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // LD_A(0x38);
    // LD_hli_A;
    *(hl++) = 0x38;
    // LD_D(0x39);
    // CALL(aPokedex_PlaceBorder_FillRow);
    hl = Pokedex_PlaceBorder_FillRow(hl, c, 0x39);
    // LD_A(0x3a);
    // LD_hl_A;
    *hl = 0x3a;
    // RET;
}

static tile_t* Pokedex_PlaceBorder_FillRow(tile_t* hl, uint8_t c, uint8_t d) {
    // LD_E_C;

    while(c) {
    // row_loop:
        // LD_A_E;
        // AND_A_A;
        // RET_Z ;
        // LD_A_D;
        // LD_hli_A;
        *(hl++) = d;
        // DEC_E;
        c--;
        // goto row_loop;
    }
    return hl;
}

static void Pokedex_PrintListing_PrintEntry(tile_t* hl, species_t a);

void Pokedex_PrintListing(void){
//  Prints the list of Pokémon on the main Pokédex screen.

//  This check is completely useless.
    // LD_A_addr(wCurDexMode);
    // CP_A(DEXMODE_OLD);
    // IF_Z goto okay;
    // LD_C(11);
    // goto resume;

// okay:
    // LD_C(11);
//  End useless check


// resume:
//  Clear (2 * [wDexListingHeight] + 1) by 11 box starting at 0,1
    // hlcoord(0, 1, wTilemap);
    // LD_A_addr(wDexListingHeight);
    // ADD_A_A;
    // INC_A;
    // LD_B_A;
    uint8_t b = wram->wDexListingHeight * 2 + 1;
    // LD_A(0x7f);
    // CALL(aPokedex_FillBox);
    Pokedex_FillBox(coord(0, 1, wram->wTilemap), 11, b, 0x7f);

//  Load de with wPokedexOrder + [wDexListingScrollOffset]
    // LD_A_addr(wDexListingScrollOffset);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPokedexOrder);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    species_t* de = wram->wPokedexOrder + wram->wDexListingScrollOffset;
    // hlcoord(0, 2, wTilemap);
    tile_t* hl = coord(0, 2, wram->wTilemap);
    // LD_A_addr(wDexListingHeight);
    uint8_t h = wram->wDexListingHeight;

    do {
    // loop:
        // PUSH_AF;
        // LD_A_de;
        // LD_addr_A(wTempSpecies);  // also sets wNamedObjectIndex
        wram->wTempSpecies = *de;
        //assert ['wTempSpecies == wNamedObjectIndex'];
        // PUSH_DE;
        // PUSH_HL;
        // CALL(aPokedex_PrintListing_PrintEntry);
        Pokedex_PrintListing_PrintEntry(hl, *de);
        // POP_HL;
        // LD_DE(2 * SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // POP_DE;
        // INC_DE;
        de++;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--h != 0);
    // CALL(aPokedex_LoadSelectedMonTiles);
    Pokedex_LoadSelectedMonTiles();
    // RET;
}

static void Pokedex_PrintListing_PrintEntry(tile_t* hl, species_t a) {
//  Prints one entry in the list of Pokémon on the main Pokédex screen.
    // AND_A_A;
    // RET_Z ;
    if(a == 0)
        return;
    // CALL(aPokedex_PrintNumberIfOldMode);
    Pokedex_PrintNumberIfOldMode(hl, a);
    // CALL(aPokedex_PlaceDefaultStringIfNotSeen);
    // RET_C ;
    if(Pokedex_PlaceDefaultStringIfNotSeen(hl, a))
        return;
    // CALL(aPokedex_PlaceCaughtSymbolIfCaught);
    hl = Pokedex_PlaceCaughtSymbolIfCaught(hl, a);
    // PUSH_HL;
    // CALL(aGetPokemonName);
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(GetPokemonName(a), hl);
    // RET;
}

void Pokedex_PrintNumberIfOldMode(tile_t* hl, species_t a){
    // LD_A_addr(wCurDexMode);
    // CP_A(DEXMODE_OLD);
    // IF_Z goto printnum;
    if(wram->wCurDexMode == DEXMODE_OLD) {
    // printnum:
        // PUSH_HL;
        // LD_DE(-SCREEN_WIDTH);
        // ADD_HL_DE;
        // LD_DE(wTempSpecies);
        // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 3);
        // CALL(aPrintNum);
        PrintNum(hl-SCREEN_WIDTH, &a, PRINTNUM_LEADINGZEROS | 1, 3);
        // POP_HL;
        // RET;
    }
    // RET;

}

tile_t* Pokedex_PlaceCaughtSymbolIfCaught(tile_t* hl, species_t a){
    // CALL(aPokedex_CheckCaught);
    // IF_NZ goto place_caught_symbol;
    if(Pokedex_CheckCaught(a)) {
    // place_caught_symbol:
        // LD_A(0x4f);
        // LD_hli_A;
        *(hl++) = 0x4f;
        // RET;
        return hl;
    }
    // INC_HL;
    hl++;
    // RET;
    return hl;
}

bool Pokedex_PlaceDefaultStringIfNotSeen(tile_t* hl, species_t species){
    static const char NameNotSeen[] = "-----@";
    // CALL(aPokedex_CheckSeen);
    // RET_NZ ;
    if(Pokedex_CheckSeen(species))
        return false;
    // INC_HL;
    hl++;
    // LD_DE(mPokedex_PlaceDefaultStringIfNotSeen_NameNotSeen);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(NameNotSeen), hl);
    // SCF;
    // RET;
    return true;
}

void Pokedex_DrawFootprint(void){
    // hlcoord(18, 1, wTilemap);
    // LD_A(0x62);
    // LD_hli_A;
    *coord(18, 1, wram->wTilemap) = 0x62;
    // INC_A;
    // LD_hl_A;
    *coord(19, 1, wram->wTilemap) = 0x63;
    // hlcoord(18, 2, wTilemap);
    // LD_A(0x64);
    // LD_hli_A;
    *coord(18, 2, wram->wTilemap) = 0x64;
    // INC_A;
    // LD_hl_A;
    *coord(19, 2, wram->wTilemap) = 0x65;
    // RET;
}

//  Gets the species of the currently selected Pokémon. This corresponds to the
//  position of the cursor in the main listing, but this function can be used
//  on all Pokédex screens.
species_t Pokedex_GetSelectedMon(void){
    // LD_A_addr(wDexListingCursor);
    // LD_HL(wDexListingScrollOffset);
    // ADD_A_hl;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPokedexOrder);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wTempSpecies);
    wram->wTempSpecies = wram->wPokedexOrder[wram->wDexListingCursor + wram->wDexListingScrollOffset];
    // RET;
    return wram->wPokedexOrder[wram->wDexListingCursor + wram->wDexListingScrollOffset];
}

bool Pokedex_CheckCaught(species_t species){
    // PUSH_DE;
    // PUSH_HL;
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // CALL(aCheckCaughtMon);
    return CheckCaughtMon(species - 1);
    // POP_HL;
    // POP_DE;
    // RET;
}

bool Pokedex_CheckSeen(species_t species){
    // PUSH_DE;
    // PUSH_HL;
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // CALL(aCheckSeenMon);
    return CheckSeenMon(species - 1);
    // POP_HL;
    // POP_DE;
    // RET;

}

static void Pokedex_OrderMonsByMode_FindLastSeen(void);

void Pokedex_OrderMonsByMode(void){
    // LD_HL(wPokedexOrder);
    // LD_BC(wPokedexOrderEnd - wPokedexOrder);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wPokedexOrder, sizeof(wram->wPokedexOrder), 0);
    // LD_A_addr(wCurDexMode);
    // LD_HL(mPokedex_OrderMonsByMode_Jumptable);
    // CALL(aPokedex_LoadPointer);
    // JP_hl;
    switch(wram->wCurDexMode) {
    // Jumptable:
        //dw ['.NewMode'];
        case DEXMODE_NEW: {
        // NewMode:
            // LD_DE(mNewPokedexOrder);
            const species_t* de = NewPokedexOrder;
            // LD_HL(wPokedexOrder);
            species_t* hl = wram->wPokedexOrder;
            // LD_C(NUM_POKEMON);
            uint16_t c = NUM_POKEMON;

            do {
            // loopnew:
                // LD_A_de;
                // INC_DE;
                // LD_hli_A;
                *(hl++) = *(de++);
                // DEC_C;
                // IF_NZ goto loopnew;
            } while(--c != 0);
            // CALL(aPokedex_OrderMonsByMode_FindLastSeen);
            Pokedex_OrderMonsByMode_FindLastSeen();
            // RET;
        } return;
        //dw ['.OldMode'];
        case DEXMODE_OLD: {
        // OldMode:
            // LD_HL(wPokedexOrder);
            species_t* hl = wram->wPokedexOrder;
            // LD_A(0x1);
            species_t a = 0x1;
            // LD_C(NUM_POKEMON);
            uint16_t c = NUM_POKEMON;

            do {
            // loopold:
                // LD_hli_A;
                // INC_A;
                *(hl++) = a++;
                // DEC_C;
                // IF_NZ goto loopold;
            } while(--c != 0);
            // CALL(aPokedex_OrderMonsByMode_FindLastSeen);
            Pokedex_OrderMonsByMode_FindLastSeen();
            // RET;
        } return;
        //dw ['Pokedex_ABCMode'];
        case DEXMODE_ABC: {
            Pokedex_ABCMode();
        } return;
    }

}

static void Pokedex_OrderMonsByMode_FindLastSeen(void){
    // LD_HL(wPokedexOrder + NUM_POKEMON - 1);
    species_t* hl = wram->wPokedexOrder + NUM_POKEMON - 1;
    // LD_D(NUM_POKEMON);
    uint8_t d = NUM_POKEMON;
    // LD_E_D;
    uint8_t e = NUM_POKEMON;

    do {
    // loopfindend:
        // LD_A_hld;
        // LD_addr_A(wTempSpecies);
        // CALL(aPokedex_CheckSeen);
        // IF_NZ goto foundend;
        if(Pokedex_CheckSeen(*(hl--)))
            break;
        // DEC_D;
        --d;
        // DEC_E;
        // IF_NZ goto loopfindend;
    } while(--e != 0);

// foundend:
    wram->wTempSpecies = hl[1];
    // LD_A_D;
    // LD_addr_A(wDexListingEnd);
    wram->wDexListingEnd = d;
    // RET;
}

void Pokedex_ABCMode(void){
    // XOR_A_A;
    // LD_addr_A(wDexListingEnd);
    wram->wDexListingEnd = 0;
    // LD_HL(wPokedexOrder);
    species_t* hl = wram->wPokedexOrder;
    // LD_DE(mAlphabeticalPokedexOrder);
    const species_t* de = AlphabeticalPokedexOrder;
    // LD_C(NUM_POKEMON);
    species_t c = NUM_POKEMON;

    do {
    // loop1abc:
        // PUSH_BC;
        // LD_A_de;
        // LD_addr_A(wTempSpecies);
        // CALL(aPokedex_CheckSeen);
        // IF_Z goto skipabc;
        if(Pokedex_CheckSeen(*de)) {
            // LD_A_addr(wTempSpecies);
            // LD_hli_A;
            *(hl++) = *de;
            // LD_A_addr(wDexListingEnd);
            // INC_A;
            // LD_addr_A(wDexListingEnd);
            wram->wDexListingEnd++;
        }

    // skipabc:
        // INC_DE;
        de++;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop1abc;
    } while(--c != 0);
    // LD_A_addr(wDexListingEnd);
    species_t a = wram->wDexListingEnd;
    // LD_C(0);

    while(a != NUM_POKEMON) {
    // loop2abc:
        // CP_A(NUM_POKEMON);
        // IF_Z goto doneabc;
        // LD_hl_C;
        // INC_HL;
        *(hl++) = 0;
        // INC_A;
        a++;
        // goto loop2abc;
    }

// doneabc:
    // RET;

// INCLUDE "data/pokemon/dex_order_alpha.asm"

// INCLUDE "data/pokemon/dex_order_new.asm"
}

void Pokedex_DisplayModeDescription(void){
    static const char NewMode[] = 
                "<PK><MN> are listed by"
        t_next  "evolution type.";

    static const char OldMode[] = 
                "<PK><MN> are listed by"
        t_next  "official type.";


    static const char ABCMode[] = 
                "<PK><MN> are listed"
        t_next  "alphabetically.";

    static const char UnownMode[] = 
                "UNOWN are listed"
        t_next  "in catching order.";

    static const char *const Modes[] = {
        NewMode,
        OldMode,
        ABCMode,
        UnownMode,
    };
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 12, wram->wTilemap), 4, 18);
    // LD_A_addr(wDexArrowCursorPosIndex);
    // LD_HL(mPokedex_DisplayModeDescription_Modes);
    // CALL(aPokedex_LoadPointer);
    // LD_E_L;
    // LD_D_H;
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Modes[wram->wDexArrowCursorPosIndex]), coord(1, 14, wram->wTilemap));
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

void Pokedex_DisplayChangingModesMessage(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 12, wram->wTilemap), 4, 18);
    // LD_DE(mString_ChangingModesPleaseWait);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_ChangingModesPleaseWait), coord(1, 14, wram->wTilemap));
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // LD_C(64);
    // CALL(aDelayFrames);
    DelayFrames(64);
    // LD_DE(SFX_CHANGE_DEX_MODE);
    // CALL(aPlaySFX);
    PlaySFX(SFX_CHANGE_DEX_MODE);
    // LD_C(64);
    // CALL(aDelayFrames);
    DelayFrames(64);
    // RET;
}

const char String_ChangingModesPleaseWait[] = "Changing modes."
    t_next "Please wait.";

bool Pokedex_UpdateSearchMonType(void){
    // LD_A_addr(wDexArrowCursorPosIndex);
    // CP_A(2);
    // IF_NC goto no_change;
    if(wram->wDexArrowCursorPosIndex < 2){
        // LD_HL(hJoyLast);
        // LD_A_hl;
        // AND_A(D_LEFT);
        // JR_NZ (mPokedex_PrevSearchMonType);
        if(hram.hJoyLast & D_LEFT)
            return Pokedex_PrevSearchMonType();
        // LD_A_hl;
        // AND_A(D_RIGHT);
        // JR_NZ (mPokedex_NextSearchMonType);
        if(hram.hJoyLast & D_RIGHT)
            return Pokedex_NextSearchMonType();
    }

// no_change:
    // AND_A_A;
    // RET;
    return false;
}

bool Pokedex_PrevSearchMonType(void){
    // LD_A_addr(wDexArrowCursorPosIndex);
    // AND_A_A;
    // IF_NZ goto type2;
    if(wram->wDexArrowCursorPosIndex == 0){
        // LD_HL(wDexSearchMonType1);
        // LD_A_hl;
        // CP_A(1);
        // IF_Z goto wrap_around;
        if(wram->wDexSearchMonType1 == 1)
            wram->wDexSearchMonType1 = NUM_TYPES;
        // DEC_hl;
        wram->wDexSearchMonType1--;
        // goto done;
    }
    else {
    // type2:
        // LD_HL(wDexSearchMonType2);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto wrap_around;
        if(wram->wDexSearchMonType2 == 0)
            wram->wDexSearchMonType2 = NUM_TYPES;
        // DEC_hl;
        wram->wDexSearchMonType2--;
        // goto done;
    }

// wrap_around:
    // LD_hl(NUM_TYPES);

// done:
    // SCF;
    // RET;
    return true;
}

bool Pokedex_NextSearchMonType(void){
    // LD_A_addr(wDexArrowCursorPosIndex);
    // AND_A_A;
    // IF_NZ goto type2;
    if(wram->wDexArrowCursorPosIndex == 0){
        // LD_HL(wDexSearchMonType1);
        // LD_A_hl;
        // CP_A(NUM_TYPES);
        // IF_NC goto type1_wrap_around;
        if(wram->wDexSearchMonType1 >= NUM_TYPES){
        // type1_wrap_around:
            // LD_hl(1);
            wram->wDexSearchMonType1 = 1;
            // goto done;
        }
        else {
            // INC_hl;
            wram->wDexSearchMonType1++;
            // goto done;
        }
    }
    else {
    // type2:
        // LD_HL(wDexSearchMonType2);
        // LD_A_hl;
        // CP_A(NUM_TYPES);
        // IF_NC goto type2_wrap_around;
        if(wram->wDexSearchMonType2 >= NUM_TYPES){
        // type2_wrap_around:
            // LD_hl(0);
            wram->wDexSearchMonType2 = 0;
        }
        else {
            // INC_hl;
            wram->wDexSearchMonType2++;
            // goto done;
        }
    }

// done:
    // SCF;
    // RET;
    return true;
}

void Pokedex_PlaceSearchScreenTypeStrings(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(9, 3, wTilemap);
    // LD_BC((4 << 8) | 8);
    // LD_A(0x7f);
    // CALL(aPokedex_FillBox);
    Pokedex_FillBox(coord(9, 3, wram->wTilemap), 8, 4, 0x7f);
    // LD_A_addr(wDexSearchMonType1);
    // hlcoord(9, 4, wTilemap);
    // CALL(aPokedex_PlaceTypeString);
    Pokedex_PlaceTypeString(coord(9, 4, wram->wTilemap), wram->wDexSearchMonType1);
    // LD_A_addr(wDexSearchMonType2);
    // hlcoord(9, 6, wTilemap);
    // CALL(aPokedex_PlaceTypeString);
    Pokedex_PlaceTypeString(coord(9, 6, wram->wTilemap), wram->wDexSearchMonType2);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

void Pokedex_PlaceTypeString(tile_t* hl, uint8_t a){
    // PUSH_HL;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mPokedexTypeSearchStrings);
    // for(int rept = 0; rept < POKEDEX_TYPE_STRING_LENGTH; rept++){
    // ADD_HL_DE;
    // }
    // LD_E_L;
    // LD_D_H;
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(PokedexTypeSearchStrings[a]), hl);
    // RET;

// INCLUDE "data/types/search_strings.asm"
}

static void Pokedex_SearchForMons_Search(uint8_t a);

void Pokedex_SearchForMons(void){
    // LD_A_addr(wDexSearchMonType2);
    // AND_A_A;
    // CALL_NZ (aPokedex_SearchForMons_Search);
    if(wram->wDexSearchMonType2 != 0)
        Pokedex_SearchForMons_Search(wram->wDexSearchMonType2);
    // LD_A_addr(wDexSearchMonType1);
    // AND_A_A;
    // CALL_NZ (aPokedex_SearchForMons_Search);
    if(wram->wDexSearchMonType1 != 0)
        Pokedex_SearchForMons_Search(wram->wDexSearchMonType1);
    // RET;

// INCLUDE "data/types/search_types.asm"
}

static void Pokedex_SearchForMons_Search(uint8_t a){
    // DEC_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mPokedexTypeSearchConversionTable);
    // ADD_HL_DE;
    // LD_A_hl;
    uint8_t type = PokedexTypeSearchConversionTable[a - 1];
    // LD_addr_A(wDexConvertedMonType);
    wram->wDexConvertedMonType = type;
    // LD_HL(wPokedexOrder);
    uint8_t* hl = wram->wPokedexOrder;
    // LD_DE(wPokedexOrder);
    uint8_t* de = wram->wPokedexOrder;

    // LD_C(NUM_POKEMON);
    uint8_t c = NUM_POKEMON;
    // XOR_A_A;
    // LD_addr_A(wDexSearchResultCount);
    wram->wDexSearchResultCount = 0;

    do {
    // loop:
        // PUSH_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next_mon;
        if(*hl == 0)
            continue;
        // LD_addr_A(wTempSpecies);
        wram->wTempSpecies = *hl;
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = *hl;
        // CALL(aPokedex_CheckCaught);
        // IF_Z goto next_mon;
        if(!Pokedex_CheckCaught(*hl))
            continue;
        // PUSH_HL;
        // PUSH_DE;
        // CALL(aGetBaseData);
        GetBaseData(*hl);
        // POP_DE;
        // POP_HL;
        // LD_A_addr(wDexConvertedMonType);
        // LD_B_A;
        // LD_A_addr(wBaseType1);
        // CP_A_B;
        // IF_Z goto match_found;
        // LD_A_addr(wBaseType2);
        // CP_A_B;
        // IF_NZ goto next_mon;
        if(wram->wDexConvertedMonType != wram->wBaseType1 && wram->wDexConvertedMonType != wram->wBaseType2)
            continue;

    // match_found:
        // LD_A_addr(wTempSpecies);
        // LD_de_A;
        // INC_DE;
        *(de++) = *hl;
        // LD_A_addr(wDexSearchResultCount);
        // INC_A;
        // LD_addr_A(wDexSearchResultCount);
        wram->wDexSearchResultCount++;

    // next_mon:
        // INC_HL;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(hl++, --c != 0);

    // LD_L_E;
    // LD_H_D;
    // LD_A_addr(wDexSearchResultCount);
    uint8_t count = wram->wDexSearchResultCount;
    // LD_C(0);

    while(count != NUM_POKEMON){
    // zero_remaining_mons:
        // CP_A(NUM_POKEMON);
        // IF_Z goto done;
        // LD_hl_C;
        // INC_HL;
        *(de++) = 0;
        // INC_A;
        count++;
        // goto zero_remaining_mons;
    }

// done:
    // RET;
    return;
}

void Pokedex_DisplayTypeNotFoundMessage(void){
    static const char TypeNotFound[] = "The specified type"
        t_next "was not found.";
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(0, 12, wTilemap);
    // LD_BC((4 << 8) | 18);
    // CALL(aPokedex_PlaceBorder);
    Pokedex_PlaceBorder(coord(0, 12, wram->wTilemap), 4, 18);
    // LD_DE(mPokedex_DisplayTypeNotFoundMessage_TypeNotFound);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(TypeNotFound), coord(1, 14, wram->wTilemap));
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // LD_C(0x80);
    // CALL(aDelayFrames);
    DelayFrames(0x80);
    // RET;
}

void Pokedex_UpdateCursorOAM(void){
    // LD_A_addr(wCurDexMode);
    // CP_A(DEXMODE_OLD);
    // JP_Z (mPokedex_PutOldModeCursorOAM);
    if(wram->wCurDexMode == DEXMODE_OLD)
        return Pokedex_PutOldModeCursorOAM();
    // CALL(aPokedex_PutNewModeABCModeCursorOAM);
    struct SpriteOAM* de = Pokedex_PutNewModeABCModeCursorOAM();
    // CALL(aPokedex_PutScrollbarOAM);
    Pokedex_PutScrollbarOAM(de);
    // RET;

}

void Pokedex_PutOldModeCursorOAM(void){
    static const uint8_t CursorOAM[] = {
        dbsprite(9, 3, -1, 0, 0x30, 7),
        dbsprite(9, 2, -1, 0, 0x31, 7),
        dbsprite(10, 2, -1, 0, 0x32, 7),
        dbsprite(11, 2, -1, 0, 0x32, 7),
        dbsprite(12, 2, -1, 0, 0x32, 7),
        dbsprite(13, 2, -1, 0, 0x33, 7),
        dbsprite(16, 2, -2, 0, 0x33, 7 | X_FLIP),
        dbsprite(17, 2, -2, 0, 0x32, 7 | X_FLIP),
        dbsprite(18, 2, -2, 0, 0x32, 7 | X_FLIP),
        dbsprite(19, 2, -2, 0, 0x32, 7 | X_FLIP),
        dbsprite(20, 2, -2, 0, 0x31, 7 | X_FLIP),
        dbsprite(20, 3, -2, 0, 0x30, 7 | X_FLIP),
        dbsprite(9, 4, -1, 0, 0x30, 7 | Y_FLIP),
        dbsprite(9, 5, -1, 0, 0x31, 7 | Y_FLIP),
        dbsprite(10, 5, -1, 0, 0x32, 7 | Y_FLIP),
        dbsprite(11, 5, -1, 0, 0x32, 7 | Y_FLIP),
        dbsprite(12, 5, -1, 0, 0x32, 7 | Y_FLIP),
        dbsprite(13, 5, -1, 0, 0x33, 7 | Y_FLIP),
        dbsprite(16, 5, -2, 0, 0x33, 7 | X_FLIP | Y_FLIP),
        dbsprite(17, 5, -2, 0, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(18, 5, -2, 0, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(19, 5, -2, 0, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(20, 5, -2, 0, 0x31, 7 | X_FLIP | Y_FLIP),
        dbsprite(20, 4, -2, 0, 0x30, 7 | X_FLIP | Y_FLIP),
        (uint8_t)-1
        //db ['-1'];
    };

    //  OAM data for when the cursor is at the top of the list. The tiles at the top
    //  are cut off so they don't show up outside the list area.
    static const uint8_t CursorAtTopOAM[] = {
        dbsprite(9, 3, -1, 0, 0x30, 7),
        dbsprite(9, 2, -1, 0, 0x34, 7),
        dbsprite(10, 2, -1, 0, 0x35, 7),
        dbsprite(11, 2, -1, 0, 0x35, 7),
        dbsprite(12, 2, -1, 0, 0x35, 7),
        dbsprite(13, 2, -1, 0, 0x36, 7),
        dbsprite(16, 2, -2, 0, 0x36, 7 | X_FLIP),
        dbsprite(17, 2, -2, 0, 0x35, 7 | X_FLIP),
        dbsprite(18, 2, -2, 0, 0x35, 7 | X_FLIP),
        dbsprite(19, 2, -2, 0, 0x35, 7 | X_FLIP),
        dbsprite(20, 2, -2, 0, 0x34, 7 | X_FLIP),
        dbsprite(20, 3, -2, 0, 0x30, 7 | X_FLIP),
        dbsprite(9, 4, -1, 0, 0x30, 7 | Y_FLIP),
        dbsprite(9, 5, -1, 0, 0x31, 7 | Y_FLIP),
        dbsprite(10, 5, -1, 0, 0x32, 7 | Y_FLIP),
        dbsprite(11, 5, -1, 0, 0x32, 7 | Y_FLIP),
        dbsprite(12, 5, -1, 0, 0x32, 7 | Y_FLIP),
        dbsprite(13, 5, -1, 0, 0x33, 7 | Y_FLIP),
        dbsprite(16, 5, -2, 0, 0x33, 7 | X_FLIP | Y_FLIP),
        dbsprite(17, 5, -2, 0, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(18, 5, -2, 0, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(19, 5, -2, 0, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(20, 5, -2, 0, 0x31, 7 | X_FLIP | Y_FLIP),
        dbsprite(20, 4, -2, 0, 0x30, 7 | X_FLIP | Y_FLIP),
        (uint8_t)-1,
        //db ['-1'];
    };
    // LD_HL(mPokedex_PutOldModeCursorOAM_CursorOAM);
    // LD_A_addr(wDexListingCursor);
    // OR_A_A;
    // IF_NZ goto okay;
    // LD_HL(mPokedex_PutOldModeCursorOAM_CursorAtTopOAM);
    const uint8_t* hl = (wram->wDexListingCursor != 0)? CursorOAM: CursorAtTopOAM;

// okay:
    // CALL(aPokedex_LoadCursorOAM);
    Pokedex_LoadCursorOAM(hl);
    // RET;
}

struct SpriteOAM* Pokedex_PutNewModeABCModeCursorOAM(void){
    static const uint8_t CursorOAM[] = {
        dbsprite(9, 3, -1, 3, 0x30, 7),
        dbsprite(9, 2, -1, 3, 0x31, 7),
        dbsprite(10, 2, -1, 3, 0x32, 7),
        dbsprite(11, 2, -1, 3, 0x32, 7),
        dbsprite(12, 2, -1, 3, 0x33, 7),
        dbsprite(16, 2, 0, 3, 0x33, 7 | X_FLIP),
        dbsprite(17, 2, 0, 3, 0x32, 7 | X_FLIP),
        dbsprite(18, 2, 0, 3, 0x32, 7 | X_FLIP),
        dbsprite(19, 2, 0, 3, 0x31, 7 | X_FLIP),
        dbsprite(19, 3, 0, 3, 0x30, 7 | X_FLIP),
        dbsprite(9, 4, -1, 3, 0x30, 7 | Y_FLIP),
        dbsprite(9, 5, -1, 3, 0x31, 7 | Y_FLIP),
        dbsprite(10, 5, -1, 3, 0x32, 7 | Y_FLIP),
        dbsprite(11, 5, -1, 3, 0x32, 7 | Y_FLIP),
        dbsprite(12, 5, -1, 3, 0x33, 7 | Y_FLIP),
        dbsprite(16, 5, 0, 3, 0x33, 7 | X_FLIP | Y_FLIP),
        dbsprite(17, 5, 0, 3, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(18, 5, 0, 3, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(19, 5, 0, 3, 0x31, 7 | X_FLIP | Y_FLIP),
        dbsprite(19, 4, 0, 3, 0x30, 7 | X_FLIP | Y_FLIP),
        (uint8_t)-1
    };
    // LD_HL(mPokedex_PutNewModeABCModeCursorOAM_CursorOAM);
    // CALL(aPokedex_LoadCursorOAM);
    return Pokedex_LoadCursorOAM(CursorOAM);
    // RET;
}

void Pokedex_UpdateSearchResultsCursorOAM(void){
    static const uint8_t CursorOAM[] = {
        dbsprite( 9, 3, -1, 3, 0x30, 7),
        dbsprite( 9, 2, -1, 3, 0x31, 7),
        dbsprite(10, 2, -1, 3, 0x32, 7),
        dbsprite(11, 2, -1, 3, 0x32, 7),
        dbsprite(12, 2, -1, 3, 0x32, 7),
        dbsprite(13, 2, -1, 3, 0x33, 7),
        dbsprite(16, 2, -2, 3, 0x33, 7 | X_FLIP),
        dbsprite(17, 2, -2, 3, 0x32, 7 | X_FLIP),
        dbsprite(18, 2, -2, 3, 0x32, 7 | X_FLIP),
        dbsprite(19, 2, -2, 3, 0x32, 7 | X_FLIP),
        dbsprite(20, 2, -2, 3, 0x31, 7 | X_FLIP),
        dbsprite(20, 3, -2, 3, 0x30, 7 | X_FLIP),
        dbsprite( 9, 4, -1, 3, 0x30, 7 | Y_FLIP),
        dbsprite( 9, 5, -1, 3, 0x31, 7 | Y_FLIP),
        dbsprite(10, 5, -1, 3, 0x32, 7 | Y_FLIP),
        dbsprite(11, 5, -1, 3, 0x32, 7 | Y_FLIP),
        dbsprite(12, 5, -1, 3, 0x32, 7 | Y_FLIP),
        dbsprite(13, 5, -1, 3, 0x33, 7 | Y_FLIP),
        dbsprite(16, 5, -2, 3, 0x33, 7 | X_FLIP | Y_FLIP),
        dbsprite(17, 5, -2, 3, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(18, 5, -2, 3, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(19, 5, -2, 3, 0x32, 7 | X_FLIP | Y_FLIP),
        dbsprite(20, 5, -2, 3, 0x31, 7 | X_FLIP | Y_FLIP),
        dbsprite(20, 4, -2, 3, 0x30, 7 | X_FLIP | Y_FLIP),
        (uint8_t)-1,
    };
    // LD_A_addr(wCurDexMode);
    // CP_A(DEXMODE_OLD);
    // JP_Z (mPokedex_PutOldModeCursorOAM);
    if(wram->wCurDexMode == DEXMODE_OLD)
        return Pokedex_PutOldModeCursorOAM();
    // LD_HL(mPokedex_UpdateSearchResultsCursorOAM_CursorOAM);
    // CALL(aPokedex_LoadCursorOAM);
    Pokedex_LoadCursorOAM(CursorOAM);
    // RET;
}

struct SpriteOAM* Pokedex_LoadCursorOAM(const uint8_t* hl){
    // LD_DE(wVirtualOAMSprite00);
    struct SpriteOAM* de = wram->wVirtualOAMSprite;

    while(*hl != 0xff) {
    // loop:
        // LD_A_hl;
        // CP_A(-1);
        // RET_Z ;
        // LD_A_addr(wDexListingCursor);
        // AND_A(0x7);
        // SWAP_A;
        uint8_t y = *hl + ((wram->wDexListingCursor & 0x7) << 4);
        // ADD_A_hl;  // y
        // INC_HL;
        hl++;
        // LD_de_A;
        de->yCoord = y;
        // INC_DE;
        // LD_A_hli;  // x
        // LD_de_A;
        // INC_DE;
        de->xCoord = *(hl++);
        // LD_A_hli;  // tile id
        // LD_de_A;
        // INC_DE;
        de->tileID = *(hl++);
        // LD_A_hli;  // attributes
        // LD_de_A;
        de->attributes = *(hl++);
        // INC_DE;
        de++;
        // goto loop;
    }

    return de;
}

//  Writes the OAM data for the scrollbar in the new mode and ABC mode.
void Pokedex_PutScrollbarOAM(struct SpriteOAM* de){
    // PUSH_DE;
    // LD_A_addr(wDexListingEnd);
    // DEC_A;
    // LD_E_A;
    uint8_t e = wram->wDexListingEnd - 1;
    // LD_A_addr(wDexListingCursor);
    // LD_HL(wDexListingScrollOffset);
    // ADD_A_hl;
    // CP_A_E;
    // IF_Z goto max;
    uint8_t b;
    if(wram->wDexListingCursor + wram->wDexListingScrollOffset != e) {
        // LD_HL(0);
        // LD_BC(121);  // max y - min y
        // CALL(aAddNTimes);
        uint16_t de2 = (wram->wDexListingCursor + wram->wDexListingScrollOffset) * 121;
        // LD_E_L;
        // LD_D_H;
        // LD_B(0);
        // LD_A_D;
        // OR_A_E;
        // IF_Z goto done;
        if(de2 != 0) {
            // LD_A_addr(wDexListingEnd);
            // LD_C_A;
            uint8_t c = wram->wDexListingEnd;

        // loop:
            // LD_A_E;
            // SUB_A_C;
            // LD_E_A;
            // LD_A_D;
            // SBC_A(0);
            // LD_D_A;
            // IF_C goto done;
            // INC_B;
            // goto loop;
            b = de2 / c;
        }
        else {
            b = 0;
        }
    }
    else {
    // max:
        // LD_B(121);  // max y - min y
        b = 121;
    }

// done:
    // LD_A(20);  // min y
    // ADD_A_B;
    // POP_HL;
    // LD_hli_A;
    de->yCoord = 20 + b;
    // LD_A(161);  // x
    // LD_hli_A;
    de->xCoord = 161;
    // LD_A(0x0f);  // tile id
    // LD_hli_A;
    de->tileID = 0x0f;
    // LD_hl(0);  // attributes
    de->attributes = 0;
    // RET;
}

void Pokedex_InitArrowCursor(void){
    // XOR_A_A;
    // LD_addr_A(wDexArrowCursorPosIndex);
    wram->wDexArrowCursorPosIndex = 0;
    // LD_addr_A(wDexArrowCursorDelayCounter);
    wram->wDexArrowCursorDelayCounter = 0;
    // LD_addr_A(wDexArrowCursorBlinkCounter);
    wram->wDexArrowCursorBlinkCounter = 0;
    // RET;
}

bool Pokedex_MoveArrowCursor(const struct ArrowCursorData* de){
//  bc = [de] - 1
    // LD_A_de;
    // LD_B_A;
    uint8_t b = de->mask;
    // INC_DE;
    // LD_A_de;
    // DEC_A;
    // LD_C_A;
    uint8_t c = de->count - 1;
    // INC_DE;
    // CALL(aPokedex_BlinkArrowCursor);
    Pokedex_BlinkArrowCursor(de);

    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(D_LEFT | D_UP);
    // AND_A_B;
    // IF_NZ goto move_left_or_up;
    if(hram.hJoyPressed & (D_LEFT | D_UP) & b)
        goto move_left_or_up;
    // LD_A_hl;
    // AND_A(D_RIGHT | D_DOWN);
    // AND_A_B;
    // IF_NZ goto move_right_or_down;
    if(hram.hJoyPressed & (D_RIGHT | D_DOWN) & b)
        goto move_right_or_down;
    // LD_A_hl;
    // AND_A(SELECT);
    // AND_A_B;
    // IF_NZ goto select;
    if(hram.hJoyPressed & SELECT & b)
        goto select;
    // CALL(aPokedex_ArrowCursorDelay);
    // IF_C goto no_action;
    if(Pokedex_ArrowCursorDelay())
        return false;
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_LEFT | D_UP);
    // AND_A_B;
    // IF_NZ goto move_left_or_up;
    if(hram.hJoyLast & (D_LEFT | D_UP) & b)
        goto move_left_or_up;
    // LD_A_hl;
    // AND_A(D_RIGHT | D_DOWN);
    // AND_A_B;
    // IF_NZ goto move_right_or_down;
    if(hram.hJoyLast & (D_RIGHT | D_DOWN) & b)
        goto move_right_or_down;
    // goto no_action;
    return false;

move_left_or_up:
    // LD_A_addr(wDexArrowCursorPosIndex);
    // AND_A_A;
    // IF_Z goto no_action;
    if(wram->wDexArrowCursorPosIndex == 0)
        return false;
    // CALL(aPokedex_GetArrowCursorPos);
    // LD_hl(0x7f);
    *Pokedex_GetArrowCursorPos(de) = 0x7f;
    // LD_HL(wDexArrowCursorPosIndex);
    // DEC_hl;
    wram->wDexArrowCursorPosIndex--;
    goto update_cursor_pos;


move_right_or_down:
    // LD_A_addr(wDexArrowCursorPosIndex);
    // CP_A_C;
    // IF_NC goto no_action;
    if(wram->wDexArrowCursorPosIndex >= c)
        return false;
    // CALL(aPokedex_GetArrowCursorPos);
    // LD_hl(0x7f);
    *Pokedex_GetArrowCursorPos(de) = 0x7f;
    // LD_HL(wDexArrowCursorPosIndex);
    // INC_hl;
    wram->wDexArrowCursorPosIndex++;


update_cursor_pos:
    // CALL(aPokedex_GetArrowCursorPos);
    // LD_hl(0xed);
    *Pokedex_GetArrowCursorPos(de) = 0xed;
    // LD_A(12);
    // LD_addr_A(wDexArrowCursorDelayCounter);
    wram->wDexArrowCursorDelayCounter = 12;
    // XOR_A_A;
    // LD_addr_A(wDexArrowCursorBlinkCounter);
    wram->wDexArrowCursorBlinkCounter = 0;
    // SCF;
    // RET;
    return true;

// no_action:
    // AND_A_A;
    // RET;

select:
    // CALL(aPokedex_GetArrowCursorPos);
    // LD_hl(0x7f);
    *Pokedex_GetArrowCursorPos(de) = 0x7f;
    // LD_A_addr(wDexArrowCursorPosIndex);
    // CP_A_C;
    // IF_C goto update;
    if(wram->wDexArrowCursorPosIndex >= c)
        // LD_A(-1);
        wram->wDexArrowCursorPosIndex = 0;
    else {
    // update:
        // INC_A;
        // LD_addr_A(wDexArrowCursorPosIndex);
        wram->wDexArrowCursorPosIndex++;
    }
    goto update_cursor_pos;
}

tile_t* Pokedex_GetArrowCursorPos(const struct ArrowCursorData* de){
    // LD_A_addr(wDexArrowCursorPosIndex);
    // ADD_A_A;
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // RET;
    return wram->wTilemap + de->coords[wram->wDexArrowCursorPosIndex];
}

void Pokedex_BlinkArrowCursor(const struct ArrowCursorData* de){
    // LD_HL(wDexArrowCursorBlinkCounter);
    // LD_A_hl;
    // INC_hl;
    // AND_A(0x8);
    // IF_Z goto blink_on;
    if(wram->wDexArrowCursorBlinkCounter++ & 0x8) {
        // CALL(aPokedex_GetArrowCursorPos);
        // LD_hl(0x7f);
        *Pokedex_GetArrowCursorPos(de) = 0x7f;
        // RET;
    }
    else {
    // blink_on:
        // CALL(aPokedex_GetArrowCursorPos);
        // LD_hl(0xed);
        *Pokedex_GetArrowCursorPos(de) = 0xed;
        // RET;
    }
}

//  Updates the delay counter set when moving the arrow cursor.
//  Returns whether the delay is active in carry.
bool Pokedex_ArrowCursorDelay(void){
    // LD_HL(wDexArrowCursorDelayCounter);
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(wram->wDexArrowCursorDelayCounter == 0)
        return false;

    // DEC_hl;
    --wram->wDexArrowCursorDelayCounter;
    // SCF;
    // RET;
    return true;
}

void Pokedex_FillBox(tile_t* hl, uint8_t w, uint8_t h, uint8_t byte){
    // JP(mFillBoxWithByte);
    return FillBoxWithByte(hl, w, h, byte);
}

void Pokedex_BlackOutBG(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);
    // LD_HL(wBGPals1);
    // LD_BC(8 * PALETTE_SIZE);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wBGPals1, 8 * PALETTE_SIZE, 0);
    // POP_AF;
    // LDH_addr_A(rSVBK);

    return Pokedex_ApplyPrintPals();
}

void Pokedex_ApplyPrintPals(void){
    // LD_A(0xff);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0xff);
    // LD_A(0xff);
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0(0xff);
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void Pokedex_GetSGBLayout(uint8_t a){
    // LD_B_A;
    // CALL(aGetSGBLayout);
    GetSGBLayout(a);

    return Pokedex_ApplyUsualPals();
}

void Pokedex_ApplyUsualPals(void){
//  This applies the palettes used for most Pokédex screens.
    // LD_A(0xe4);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0xe4);
    // LD_A(0xe0);
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0(0xe0);
    // RET;
}

void Pokedex_LoadPointer(void){
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;

}

//  Loads the tiles of the currently selected Pokémon.
void Pokedex_LoadSelectedMonTiles(void){
    // CALL(aPokedex_GetSelectedMon);
    species_t selected = Pokedex_GetSelectedMon();
    // CALL(aPokedex_CheckSeen);
    // IF_Z goto QuestionMark;
    if(!Pokedex_CheckSeen(selected)) {
    // QuestionMark:
        // LD_A(BANK(sScratch));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asScratch));
        // FARCALL(aLoadQuestionMarkPic);
        LoadQuestionMarkPic();
        // LD_HL(vTiles2);
        // LD_DE(sScratch);
        // LD_C(7 * 7);
        // LDH_A_addr(hROMBank);
        // LD_B_A;
        // CALL(aGet2bpp);
        CopyBytes(vram->vTiles2, GBToRAMAddr(sScratch), 7 * 7 * LEN_2BPP_TILE);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // RET;
        return;
    }
    // LD_A_addr(wFirstUnownSeen);
    // LD_addr_A(wUnownLetter);
    wram->wUnownLetter = gPokemon.firstUnownSeen;
    // LD_A_addr(wTempSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = selected;
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurPartySpecies);
    // LD_DE(vTiles2);
    // PREDEF(pGetMonFrontpic);
    GetMonFrontpic(vram->vTiles2);
    // RET;
}

void Pokedex_LoadCurrentFootprint(void){
    // CALL(aPokedex_GetSelectedMon);
    species_t mon = Pokedex_GetSelectedMon();

    return Pokedex_LoadAnyFootprint(mon);
}

void Pokedex_LoadAnyFootprint(species_t a){
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // AND_A(0b11111000);
    // SRL_A;
    // SRL_A;
    // SRL_A;
    // LD_E(0);
    // LD_D_A;
    // LD_A_addr(wTempSpecies);
    // DEC_A;
    // AND_A(0b111);
    // SWAP_A;  // * $10
    // LD_L_A;
    // LD_H(0);
    // ADD_HL_DE;
    // LD_DE(mFootprints);
    // ADD_HL_DE;
    const char* path = Footprints[a - 1];

    // PUSH_HL;
    // LD_E_L;
    // LD_D_H;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x62);
    // LD_BC((BANK(aFootprints) << 8) | 2);
    // CALL(aRequest1bpp);
    // POP_HL;

// Whoever was editing footprints forgot to fix their
// tile editor. Now each bottom half is 8 tiles off.
    // LD_DE(8 * LEN_2BPP_TILE);
    // ADD_HL_DE;

    // LD_E_L;
    // LD_D_H;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x64);
    // LD_BC((BANK(aFootprints) << 8) | 2);
    // CALL(aRequest1bpp);

    // RET;
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x62, path, 0, 4);
}

void Pokedex_LoadGFX(void){
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_HL(vTiles2);
    // LD_BC(0x31 * LEN_2BPP_TILE);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(vram->vTiles2, 0x31 * LEN_2BPP_TILE, 0);
    // CALL(aPokedex_LoadInvertedFont);
    Pokedex_LoadInvertedFont();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x60);
    // LD_BC(0x20 * LEN_2BPP_TILE);
    // CALL(aPokedex_InvertTiles);
    Pokedex_InvertTiles(vram->vTiles2 + LEN_2BPP_TILE * 0x60, 0x20 * LEN_2BPP_TILE);
    // CALL(aPokedex_CheckSGB);
    // IF_NZ goto LoadPokedexLZ;
    if(Pokedex_CheckSGB()) {
        // FARCALL(aLoadSGBPokedexGFX);
        LoadSGBPokedexGFX();
        // goto LoadPokedexSlowpokeLZ;
    }
    else {
    // LoadPokedexLZ:
        // LD_HL(mPokedexLZ);
        // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x31);
        // CALL(aDecompress);
        LoadPNG2bppAssetToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x31, PokedexLZ);
    }

// LoadPokedexSlowpokeLZ:
    // LD_HL(mPokedexSlowpokeLZ);
    // LD_DE(vTiles0);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles0, PokedexSlowpokeLZ);
    // LD_A(6);
    // CALL(aSkipMusic);
    SkipMusic(3);
    // CALL(aEnableLCD);
    EnableLCD();
    // RET;
}

void Pokedex_LoadInvertedFont(void){
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // LD_HL(vTiles1);
    // LD_BC(0x80 * LEN_2BPP_TILE);

    return Pokedex_InvertTiles(vram->vTiles1, 0x80 * LEN_2BPP_TILE);
}

void Pokedex_InvertTiles(uint8_t* hl, uint16_t bc){

    do {
    // loop:
        // LD_A_hl;
        // XOR_A(0xff);
        // LD_hli_A;
        *(hl++) ^= 0xff;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // RET;
}

const char PokedexLZ[] = "gfx/pokedex/pokedex.png";
const char PokedexSlowpokeLZ[] = "gfx/pokedex/slowpoke.png";

bool Pokedex_CheckSGB(void){
    // LDH_A_addr(hCGB);
    // OR_A_A;
    // RET_NZ ;
    if(hram.hCGB)
        return false;
    // LDH_A_addr(hSGB);
    // DEC_A;
    // RET;
    return hram.hSGB == 1;
}

void Pokedex_LoadUnownFont(void){
    // LD_A(BANK(sScratch));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asScratch));
    // LD_HL(mUnownFont);
// sScratch + $188 was the address of sDecompressBuffer in pokegold
    // LD_DE(sScratch + 0x188);
    // LD_BC(39 * LEN_2BPP_TILE);
    // LD_A(BANK(aUnownFont));
    // CALL(aFarCopyBytes);
    LoadPNG1bppAssetSectionToVRAM(GBToRAMAddr(sScratch + 0x188), UnownFont, 0, 39);
    // LD_HL(sScratch + 0x188);
    // LD_BC((NUM_UNOWN + 1) * LEN_2BPP_TILE);
    // CALL(aPokedex_InvertTiles);
    Pokedex_InvertTiles((uint8_t*)GBToRAMAddr(sScratch + 0x188), (NUM_UNOWN + 1) * LEN_2BPP_TILE);
    // LD_DE(sScratch + 0x188);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * FIRST_UNOWN_CHAR);
    // LD_BC((BANK(aPokedex_LoadUnownFont) << 8) | (NUM_UNOWN + 1));
    // CALL(aRequest2bpp);
    CopyBytes(vram->vTiles2 + LEN_2BPP_TILE * FIRST_UNOWN_CHAR, GBToRAMAddr(sScratch + 0x188), (NUM_UNOWN + 1) * LEN_2BPP_TILE);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void Pokedex_LoadUnownFrontpicTiles(void){
    // LD_A_addr(wUnownLetter);
    // PUSH_AF;
    unown_letter_t letter = wram->wUnownLetter;
    // LD_A_addr(wDexCurUnownIndex);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wUnownDex);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wUnownLetter);
    wram->wUnownLetter = gPokemon.unownDex[wram->wDexCurUnownIndex];
    // LD_A(UNOWN);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = UNOWN;
    // CALL(aGetBaseData);
    GetBaseData(UNOWN);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // PREDEF(pGetMonFrontpic);
    GetMonFrontpic(vram->vTiles2 + LEN_2BPP_TILE * 0x00);
    // POP_AF;
    // LD_addr_A(wUnownLetter);
    wram->wUnownLetter = letter;
    // RET;
}

void v_NewPokedexEntry(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // FARCALL(aDrawDexEntryScreenRightEdge);
    DrawDexEntryScreenRightEdge();
    // CALL(aPokedex_ResetBGMapMode);
    Pokedex_ResetBGMapMode(); // Useless?
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // CALL(aPokedex_LoadGFX);
    Pokedex_LoadGFX();
    // CALL(aPokedex_LoadAnyFootprint);
    Pokedex_LoadAnyFootprint(wram->wTempSpecies);
    // LD_A_addr(wTempSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wTempSpecies;
    // CALL(aPokedex_DrawDexEntryScreenBG);
    Pokedex_DrawDexEntryScreenBG();
    // CALL(aPokedex_DrawFootprint);
    Pokedex_DrawFootprint();
    // hlcoord(0, 17, wTilemap);
    // LD_hl(0x3b);
    *coord(0, 17, wram->wTilemap) = 0x3b;
    // INC_HL;
    // LD_BC(19);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(1, 17, wram->wTilemap), 19, 0x7f);
    // FARCALL(aDisplayDexEntry);
    DisplayDexEntry(wram->wTempSpecies);
    // CALL(aEnableLCD);
    EnableLCD();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aGetBaseData);
    GetBaseData(wram->wTempSpecies);
    // LD_DE(vTiles2);
    // PREDEF(pGetMonFrontpic);
    GetMonFrontpic(vram->vTiles2);
    // LD_A(SCGB_POKEDEX);
    // CALL(aPokedex_GetSGBLayout);
    Pokedex_GetSGBLayout(SCGB_POKEDEX);
    // LD_A_addr(wCurPartySpecies);
    // CALL(aPlayMonCry);
    PlayMonCry(wram->wTempSpecies);
    // RET;

}

void Pokedex_SetBGMapMode3(void){
    // LD_A(0x3);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_VTILES1;
    // LD_C(4);
    // CALL(aDelayFrames);
    DelayFrames(4);
    // RET;
}

void Pokedex_SetBGMapMode4(void){
    // LD_A(0x4);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_VATTRS1;
    // LD_C(4);
    // CALL(aDelayFrames);
    DelayFrames(4);
    // RET;

}

void Pokedex_SetBGMapMode_3ifDMG_4ifCGB(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto DMG;
    if(hram.hCGB) {
        // CALL(aPokedex_SetBGMapMode4);
        Pokedex_SetBGMapMode4();
    }

// DMG:
    // CALL(aPokedex_SetBGMapMode3);
    Pokedex_SetBGMapMode3();
    // RET;
}

void Pokedex_ResetBGMapMode(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // RET;
}
