#include "../../constants.h"
#include "start_menu.h"
#include "menu.h"
#include "menu_2.h"
#include "intro_menu.h"
#include "save.h"
#include "trainer_card.h"
#include "../pokegear/pokegear.h"
#include "../items/pack.h"
#include "../pokemon/party_menu.h"
#include "../../home/audio.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../../home/map.h"
#include "../../home/gfx.h"
#include "../../home/window.h"
#include "../../home/palettes.h"
#include "../../home/map_objects.h"
#include "../../home/time_palettes.h"
#include "../overworld/init_map.h"
#include "../../data/text/common.h"
#include "../../home/queue_script.h"

//  StartMenu.Items indexes
enum {
    STARTMENUITEM_POKEDEX,  // 0
    STARTMENUITEM_POKEMON,  // 1
    STARTMENUITEM_PACK,  // 2
    STARTMENUITEM_STATUS,  // 3
    STARTMENUITEM_SAVE,  // 4
    STARTMENUITEM_OPTION,  // 5
    STARTMENUITEM_EXIT,  // 6
    STARTMENUITEM_POKEGEAR,  // 7
    STARTMENUITEM_QUIT,  // 8
};

enum {
    STARTMENURET_REOPEN,
    STARTMENURET_EXIT,
    STARTMENURET_EXIT_MENU_CALL_FUNC_CLOSE_TEXT,
    STARTMENURET_EXIT_MENU_RUN_SCRIPT_CLOSE_TEXT,
    STARTMENURET_EXIT_MENU_RUN_SCRIPT,
    STARTMENURET_RETURN_END,
    STARTMENURET_RETURN_REDRAW,
};

static uint8_t* StartMenu_FillMenuList(void) {
    // XOR_A_A;
    // LD_HL(wMenuItemsList);
    // LD_hli_A;
    wram->wMenuItemsList[0] = 0;
    // LD_A(-1);
    // LD_BC(wMenuItemsListEnd - (wMenuItemsList + 1));
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wMenuItemsList + 1, sizeof(wram->wMenuItemsList) - 1, 0xff);
    // LD_DE(wMenuItemsList + 1);
    // LD_C(0);
    // RET;
    return wram->wMenuItemsList + 1;
}

static uint8_t* StartMenu_AppendMenuList(uint8_t* de, uint8_t a) {
    // LD_de_A;
    *de = a;
    // INC_DE;
    de++;
    // INC_C;
    // RET;
    return de;
}

static void StartMenu_SetUpMenuItems(void) {
    // XOR_A_A;
    // LD_addr_A(wWhichIndexSet);
    wram->wWhichIndexSet = 0;
    // CALL(aStartMenu_FillMenuList);
    uint8_t* de = StartMenu_FillMenuList();
    uint8_t* start = de;

    // LD_HL(wStatusFlags);
    // BIT_hl(STATUSFLAGS_POKEDEX_F);
    // IF_Z goto no_pokedex;
    // LD_A(STARTMENUITEM_POKEDEX);
    // CALL(aStartMenu_AppendMenuList);
    if(bit_test(wram->wStatusFlags, STATUSFLAGS_POKEDEX_F)) {
        de = StartMenu_AppendMenuList(de, STARTMENUITEM_POKEDEX);
    }

// no_pokedex:
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // IF_Z goto no_pokemon;
    // LD_A(STARTMENUITEM_POKEMON);
    // CALL(aStartMenu_AppendMenuList);
    if(wram->wPartyCount != 0) {
        de = StartMenu_AppendMenuList(de, STARTMENUITEM_POKEMON);
    }

// no_pokemon:
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto no_pack;
    // LD_HL(wStatusFlags2);
    // BIT_hl(STATUSFLAGS2_BUG_CONTEST_TIMER_F);
    // IF_NZ goto no_pack;
    // LD_A(STARTMENUITEM_PACK);
    // CALL(aStartMenu_AppendMenuList);
    if(wram->wLinkMode == 0 && !bit_test(wram->wStatusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F)) {
        de = StartMenu_AppendMenuList(de, STARTMENUITEM_PACK);
    }

// no_pack:
    // LD_HL(wPokegearFlags);
    // BIT_hl(POKEGEAR_OBTAINED_F);
    // IF_Z goto no_pokegear;
    // LD_A(STARTMENUITEM_POKEGEAR);
    // CALL(aStartMenu_AppendMenuList);
    if(bit_test(wram->wPokegearFlags, POKEGEAR_OBTAINED_F)) {
        de = StartMenu_AppendMenuList(de, STARTMENUITEM_POKEGEAR);
    }

// no_pokegear:
    // LD_A(STARTMENUITEM_STATUS);
    // CALL(aStartMenu_AppendMenuList);
    de = StartMenu_AppendMenuList(de, STARTMENUITEM_STATUS);

    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto no_save;
    if(wram->wLinkMode == 0) {
        // LD_HL(wStatusFlags2);
        // BIT_hl(STATUSFLAGS2_BUG_CONTEST_TIMER_F);
        // LD_A(STARTMENUITEM_QUIT);
        // IF_NZ goto write;
        // LD_A(STARTMENUITEM_SAVE);

    // write:
        // CALL(aStartMenu_AppendMenuList);
        if(bit_test(wram->wStatusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F)) {
            de = StartMenu_AppendMenuList(de, STARTMENUITEM_QUIT);
        }
        else {
            de = StartMenu_AppendMenuList(de, STARTMENUITEM_SAVE);
        }
    }

// no_save:
    // LD_A(STARTMENUITEM_OPTION);
    // CALL(aStartMenu_AppendMenuList);
    de = StartMenu_AppendMenuList(de, STARTMENUITEM_OPTION);
    // LD_A(STARTMENUITEM_EXIT);
    // CALL(aStartMenu_AppendMenuList);
    de = StartMenu_AppendMenuList(de, STARTMENUITEM_EXIT);
    // LD_A_C;
    // LD_addr_A(wMenuItemsList);
    wram->wMenuItemsList[0] = (uint8_t)(de - start);
    // RET;
}

static bool StartMenu_IsMenuAccountOn(void) {
    // LD_A_addr(wOptions2);
    // AND_A(1 << MENU_ACCOUNT);
    // RET;
    return (wram->wOptions2 & (1 << MENU_ACCOUNT)) != 0;
}

static void StartMenu_DrawMenuAccount(void) {
    // CALL(aStartMenu_IsMenuAccountOn);
    // RET_Z ;
    if(!StartMenu_IsMenuAccountOn())
        return;
    // hlcoord(0, 13, wTilemap);
    // LD_BC((5 << 8) | 10);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(0, 13, wram->wTilemap), 10, 5);
    // hlcoord(0, 13, wTilemap);
    // LD_B(3);
    // LD_C(8);
    // JP(mTextboxPalette);
    TextboxPalette_Conv2(coord(0, 13, wram->wTilemap), 8, 3);
}

static void StartMenu__DrawBugContestStatusBox(void) {
    // LD_HL(wStatusFlags2);
    // BIT_hl(STATUSFLAGS2_BUG_CONTEST_TIMER_F);
    // RET_Z ;
    if(!bit_test(wram->wStatusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F))
        return;
    // FARCALL(aStartMenu_DrawBugContestStatusBox);
    StartMenu_DrawBugContestStatusBox();
    // RET;
}

static void StartMenu_DrawBugContestStatus(void) {
    // LD_HL(wStatusFlags2);
    // BIT_hl(STATUSFLAGS2_BUG_CONTEST_TIMER_F);
    // IF_NZ goto contest;
    // RET;
    if(bit_test(wram->wStatusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F)) {
    // contest:
        // FARCALL(aStartMenu_PrintBugContestStatus);
        StartMenu_PrintBugContestStatus();
    }
    // RET;
}

static const struct StartMenuItem* StartMenu_GetMenuAccountTextPointer(uint8_t a) {
    const struct MenuData* data = GetMenuData();
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wMenuDataPointerTableAddr);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // for(int rept = 0; rept < 6; rept++){
    // ADD_HL_DE;
    // }
    // RET;
    return data->setupMenu.startMenuList + a;
}

static void StartMenu_MenuDesc(uint8_t* de) {
    // PUSH_DE;
    // LD_A_addr(wMenuSelection);
    // CP_A(0xff);
    // IF_Z goto none;
    if(wram->wMenuSelection == 0xff)
        return;
    // CALL(aStartMenu_GetMenuAccountTextPointer);
    const struct StartMenuItem* item = StartMenu_GetMenuAccountTextPointer(wram->wMenuSelection);
    // for(int rept = 0; rept < 4; rept++){
    // INC_HL;
    // }
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    uint8_t* str = U82C(item->desc);
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(str, de);
    // RET;

// none:
    // POP_DE;
    // RET;
}

static void StartMenu_PrintMenuAccount(void) {
    // CALL(aStartMenu_IsMenuAccountOn);
    // RET_Z ;
    if(!StartMenu_IsMenuAccountOn())
        return;
    // CALL(aStartMenu__DrawMenuAccount);
    StartMenu_DrawMenuAccount();
    // decoord(0, 14, wTilemap);
    // JP(mStartMenu_MenuDesc);
    return StartMenu_MenuDesc(coord(0, 14, wram->wTilemap));
}

static bool StartMenu_GetInput(void) {
//  Return carry on exit, and no-carry on selection.
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aStartMenu__DrawMenuAccount);
    StartMenu_DrawMenuAccount();
    // CALL(aSetUpMenu);
    SetUpMenu_Conv();
    // LD_A(0xff);
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = 0xff;

    while(1) {
    // loop:
        // CALL(aStartMenu_PrintMenuAccount);
        StartMenu_PrintMenuAccount();
        // CALL(aGetScrollingMenuJoypad);
        GetScrollingMenuJoypad_Conv2();
        // LD_A_addr(wMenuJoypad);
        // CP_A(B_BUTTON);
        // IF_Z goto b;
        if(wram->wMenuJoypad == B_BUTTON) {
        // b:
            // SCF;
            // RET;
            return true;
        }
        // CP_A(A_BUTTON);
        // IF_Z goto a;
        if(wram->wMenuJoypad == A_BUTTON) {
        // a:
            // CALL(aPlayClickSFX);
            PlayClickSFX_Conv();
            // AND_A_A;
            // RET;
            return false;
        }
        // goto loop;
    }
}

static uint8_t StartMenu_OpenMenu(void) {
    // LD_A_addr(wMenuSelection);
    // CALL(aStartMenu_GetMenuAccountTextPointer);
    const struct StartMenuItem *hl = StartMenu_GetMenuAccountTextPointer(wram->wMenuSelection);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    return hl->function();
}

static void StartMenu_MenuString(const char** items, uint8_t* de, uint8_t a) {
    (void)items;
    // PUSH_DE;
    // LD_A_addr(wMenuSelection);
    // CALL(aStartMenu_GetMenuAccountTextPointer);
    const struct StartMenuItem *hl = StartMenu_GetMenuAccountTextPointer(a);
    // INC_HL;
    // INC_HL;
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    uint8_t* str = U82C(hl->label);
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(str, de);
    // RET;
}

static void StartMenu_Clear(void) {
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aCall_ExitMenu);
    ExitMenu_Conv2();
    // CALL(aReloadTilesetAndPalettes);
    ReloadTilesetAndPalettes();
    // CALL(aStartMenu_DrawMenuAccount);
    StartMenu_DrawMenuAccount();
    // CALL(aDrawVariableLengthMenuBox);
    DrawVariableLengthMenuBox_Conv();
    // CALL(aStartMenu_DrawBugContestStatus);
    StartMenu_DrawBugContestStatus();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aGSReloadPalettes);
    GSReloadPalettes();
    // CALL(aFinishExitMenu);
    FinishExitMenu_Conv();
    // RET;
}

void StartMenu(void){
static const char PokedexDesc[] = 
            "#MON"
    t_next  "database@";

static const char PartyDesc[] = 
            "Party <PKMN>"
    t_next  "status@";

static const char PackDesc[] = 
            "Contains"
    t_next  "items@";

static const char PokegearDesc[] =
            "Trainer\'s"
    t_next  "key device@";

static const char StatusDesc[] = 
            "Your own"
    t_next  "status@";

static const char SaveDesc[] = 
            "Save your"
    t_next  "progress@";

static const char OptionDesc[] = 
            "Change"
    t_next  "settings@";

static const char ExitDesc[] = 
            "Close this"
    t_next  "menu@";

static const char QuitDesc[] = 
            "Quit and"
    t_next  "be judged.@";

static const struct StartMenuItem Items[] = {
//  entries correspond to STARTMENUITEM_* constants
    [STARTMENUITEM_POKEDEX] = {StartMenu_Pokedex_Conv, "#DEX@", PokedexDesc},
    [STARTMENUITEM_POKEMON] = {StartMenu_Pokemon_Conv, "#MON@", PartyDesc},
    [STARTMENUITEM_PACK]    = {StartMenu_Pack_Conv, "PACK@", PackDesc},
    [STARTMENUITEM_STATUS]  = {StartMenu_Status_Conv, "<PLAYER>@", StatusDesc},
    [STARTMENUITEM_SAVE]    = {StartMenu_Save_Conv, "SAVE@", SaveDesc},
    [STARTMENUITEM_OPTION]  = {StartMenu_Option_Conv, "OPTION@", OptionDesc},
    [STARTMENUITEM_EXIT]    = {StartMenu_Exit_Conv, "EXIT@", ExitDesc},
    [STARTMENUITEM_POKEGEAR]= {StartMenu_Pokegear_Conv, "<POKE>GEAR@", PokegearDesc},
    [STARTMENUITEM_QUIT]    = {StartMenu_Quit_Conv, "QUIT@", QuitDesc},
};

static const uint8_t* sMenuItemsList[] = {
    ((struct wram_s*)gb.wram)->wMenuItemsList
};

static const struct MenuData menuData = {
    .flags = STATICMENU_CURSOR | STATICMENU_WRAP | STATICMENU_ENABLE_START,  // flags
    .setupMenu = {
        .rows = 0, .cols = 0,  // rows, columns
        //dw ['wMenuItemsList'];
        .itemList = sMenuItemsList,
        //dw ['.MenuString'];
        .displayFunction = StartMenu_MenuString,
        //dw ['.Items'];
        .startMenuList = Items,
    },
};

static const struct MenuHeader contestMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(10, 2, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = &menuData,
    .defaultOption = 1,  // default selection
};

static const struct MenuHeader menuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(10, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = &menuData,
    .defaultOption = 1,  // default selection
};

    // CALL(aClearWindowData);
    ClearWindowData_Conv();

    // LD_DE(SFX_MENU);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_MENU);

    // FARCALL(aReanchorBGMap_NoOAMUpdate);
    ReanchorBGMap_NoOAMUpdate_Conv();

    // LD_HL(wStatusFlags2);
    // BIT_hl(STATUSFLAGS2_BUG_CONTEST_TIMER_F);
    // LD_HL(mStartMenu_MenuHeader);
    // IF_Z goto GotMenuData;
    // LD_HL(mStartMenu_ContestMenuHeader);
    if(bit_test(wram->wStatusFlags2, STATUSFLAGS2_BUG_CONTEST_TIMER_F)) {
        LoadMenuHeader_Conv2(&contestMenuHeader);
    }
    else {
        LoadMenuHeader_Conv2(&menuHeader);
    }


// GotMenuData:
    // CALL(aLoadMenuHeader);
    // CALL(aStartMenu_SetUpMenuItems);
    StartMenu_SetUpMenuItems();
    // LD_A_addr(wBattleMenuCursorPosition);
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = wram->wBattleMenuCursorPosition;
    // CALL(aStartMenu_DrawMenuAccount);
    StartMenu_DrawMenuAccount();
    // CALL(aDrawVariableLengthMenuBox);
    DrawVariableLengthMenuBox_Conv();
    // CALL(aStartMenu_DrawBugContestStatusBox);
    StartMenu__DrawBugContestStatusBox();
    // CALL(aSafeUpdateSprites);
    SafeUpdateSprites_Conv();
    // CALL(av_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    v_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
    // FARCALL(aLoadFonts_NoOAMUpdate);
    LoadFonts_NoOAMUpdate_Conv();
    // CALL(aStartMenu_DrawBugContestStatus);
    StartMenu_DrawBugContestStatus();
    // CALL(aUpdateTimePals);
    UpdateTimePals();
    // goto Select;

    while(1) {
    // Select:
        // CALL(aStartMenu_GetInput);
        // IF_C goto Exit;
        if(StartMenu_GetInput())
            goto Exit;
        // CALL(aStartMenu__DrawMenuAccount);
        StartMenu_DrawMenuAccount();
        // LD_A_addr(wMenuCursorPosition);
        // LD_addr_A(wBattleMenuCursorPosition);
        wram->wBattleMenuCursorPosition = wram->wMenuCursorPosition;
        // CALL(aPlayClickSFX);
        PlayClickSFX_Conv();
        // CALL(aPlaceHollowCursor);
        PlaceHollowCursor_Conv();
        // CALL(aStartMenu_OpenMenu);
        uint8_t a = StartMenu_OpenMenu();

    //  Menu items have different return functions.
    //  For example, saving exits the menu.
        // LD_HL(mStartMenu_MenuReturns);
        // LD_E_A;
        // LD_D(0);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // JP_hl;
        switch(a) {
            case STARTMENURET_REOPEN: 
                // goto Reopen;
                break;
            case STARTMENURET_EXIT:
            Exit:
                {
                    // LDH_A_addr(hOAMUpdate);
                    // PUSH_AF;
                    uint8_t oamUpdate = hram->hOAMUpdate;
                    // LD_A(1);
                    // LDH_addr_A(hOAMUpdate);
                    hram->hOAMUpdate = 1;
                    // CALL(aLoadFontsExtra);
                    LoadFontsExtra_Conv();
                    // POP_AF;
                    // LDH_addr_A(hOAMUpdate);
                    hram->hOAMUpdate = oamUpdate;
                }
                // fallthrough
            case STARTMENURET_RETURN_END:
            // ReturnEnd:
                // CALL(aExitMenu);
                ExitMenu_Conv2();

            ReturnEnd2:
                // CALL(aCloseText);
                CloseText_Conv();
                // CALL(aUpdateTimePals);
                UpdateTimePals();
                // RET;
                return;
            case STARTMENURET_EXIT_MENU_CALL_FUNC_CLOSE_TEXT:
            // ExitMenuCallFuncCloseText:
                // CALL(aExitMenu);
                ExitMenu_Conv2();
                // LD_HL(wQueuedScriptAddr);
                // LD_A_hli;
                // LD_H_hl;
                // LD_L_A;
                // LD_A_addr(wQueuedScriptBank);
                // RST(aFarCall);
                gQueuedFuncAddr();
                goto ReturnEnd2;
            case STARTMENURET_EXIT_MENU_RUN_SCRIPT_CLOSE_TEXT:
            // ExitMenuRunScriptCloseText:
                // CALL(aExitMenu);
                ExitMenu_Conv2();
                // LD_A(HMENURETURN_SCRIPT);
                // LDH_addr_A(hMenuReturn);
                hram->hMenuReturn = HMENURETURN_SCRIPT;
                goto ReturnEnd2;
            case STARTMENURET_EXIT_MENU_RUN_SCRIPT:
            // ExitMenuRunScript:
                // CALL(aExitMenu);
                ExitMenu_Conv2();
                // LD_A(HMENURETURN_SCRIPT);
                // LDH_addr_A(hMenuReturn);
                hram->hMenuReturn = HMENURETURN_SCRIPT;
                // RET;
                return;
            case STARTMENURET_RETURN_REDRAW:
            // ReturnRedraw:
                // CALL(aStartMenu_Clear);
                StartMenu_Clear();
                // JP(mStartMenu_Reopen);
                break;
        }

    // Reopen:
        // CALL(aUpdateSprites);
        UpdateSprites_Conv();
        // CALL(aUpdateTimePals);
        UpdateTimePals();
        // CALL(aStartMenu_SetUpMenuItems);
        StartMenu_SetUpMenuItems();
        // LD_A_addr(wBattleMenuCursorPosition);
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = wram->wBattleMenuCursorPosition;
    }


// MenuReturns:
    //dw ['.Reopen'];
    //dw ['.Exit'];
    //dw ['.ExitMenuCallFuncCloseText'];
    //dw ['.ExitMenuRunScriptCloseText'];
    //dw ['.ExitMenuRunScript'];
    //dw ['.ReturnEnd'];
    //dw ['.ReturnRedraw'];


// DrawMenuAccount:
    // JP(mStartMenu__DrawMenuAccount);

}

void StartMenu_Exit(void){
//  Exit the menu.
    LD_A(STARTMENURET_EXIT);
    RET;
}

//  Exit the menu.
uint8_t StartMenu_Exit_Conv(void) {
    // struct cpu_registers_s regs = {};
    // SafeCallGB(aStartMenu_Exit, &regs);
    // return regs.a;
    return STARTMENURET_EXIT;
}

//  Retire from the bug catching contest.
void StartMenu_Quit(void){
    // static const txt_cmd_s StartMenuContestEndText[] = {
    //     text_far(v_StartMenuContestEndText)
    //     text_end
    // };
    LD_HL(mStartMenu_Quit_StartMenuContestEndText);
    CALL(aStartMenuYesNo);
    IF_C goto DontEndContest;
    LD_A(BANK(aBugCatchingContestReturnToGateScript));
    LD_HL(mBugCatchingContestReturnToGateScript);
    CALL(aFarQueueScript);
    LD_A(STARTMENURET_EXIT_MENU_RUN_SCRIPT);
    RET;


DontEndContest:
    LD_A(STARTMENURET_REOPEN);
    RET;
}

//  Retire from the bug catching contest.
uint8_t StartMenu_Quit_Conv(void) {
    struct cpu_registers_s regs = {};
    SafeCallGB(aStartMenu_Quit, &regs);
    return regs.a;
}

void StartMenu_Save(void){
//  Save the game.

    CALL(aBufferScreen);
    FARCALL(aSaveMenu);
    IF_NC goto saved;
    LD_A(STARTMENURET_REOPEN);
    RET;


saved:
    LD_A(STARTMENURET_EXIT);
    RET;

}

//  Save the game.
uint8_t StartMenu_Save_Conv(void) {
    // struct cpu_registers_s regs = {};
    // SafeCallGB(aStartMenu_Save, &regs);
    // return regs.a;

    // CALL(aBufferScreen);
    BufferScreen_Conv();
    // FARCALL(aSaveMenu);
    // IF_NC goto saved;
    if(SaveMenu()) {
    // saved:
        // LD_A(STARTMENURET_EXIT);
        // RET;
        return STARTMENURET_EXIT;
    }
    // LD_A(STARTMENURET_REOPEN);
    // RET;
    return STARTMENURET_REOPEN;
}

void StartMenu_Option(void){
//  Game options.

    CALL(aFadeToMenu);
    FARCALL(aOption);
    LD_A(STARTMENURET_RETURN_REDRAW);
    RET;

}

//  Game options.
uint8_t StartMenu_Option_Conv(void) {
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // FARCALL(aOption);
    Option_Conv();
    // LD_A(STARTMENURET_RETURN_REDRAW);
    // RET;
    return STARTMENURET_RETURN_REDRAW;
}

void StartMenu_Status(void){
//  Player status.

    CALL(aFadeToMenu);
    FARCALL(aTrainerCard);
    CALL(aCloseSubmenu);
    LD_A(STARTMENURET_REOPEN);
    RET;

}

//  Player status.
uint8_t StartMenu_Status_Conv(void) {
    // struct cpu_registers_s regs = {};
    // SafeCallGB(aStartMenu_Status, &regs);
    // return regs.a;
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // FARCALL(aTrainerCard);
    TrainerCard();
    // CALL(aCloseSubmenu);
    CloseSubmenu_Conv();
    // LD_A(STARTMENURET_REOPEN);
    // RET;
    return STARTMENURET_REOPEN;
}

void StartMenu_Pokedex(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    IF_Z goto empty;

    CALL(aFadeToMenu);
    FARCALL(aPokedex);
    CALL(aCloseSubmenu);


empty:
    LD_A(STARTMENURET_REOPEN);
    RET;

}

//  Pokedex
uint8_t StartMenu_Pokedex_Conv(void) {
    struct cpu_registers_s regs = {};
    SafeCallGB(aStartMenu_Pokedex, &regs);
    return regs.a;
}

void StartMenu_Pokegear(void){
    CALL(aFadeToMenu);
    FARCALL(aPokeGear);
    CALL(aCloseSubmenu);
    LD_A(STARTMENURET_REOPEN);
    RET;

}

//  Pokegear
uint8_t StartMenu_Pokegear_Conv(void) {
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // FARCALL(aPokeGear);
    PokeGear();
    // CALL(aCloseSubmenu);
    CloseSubmenu_Conv();
    // LD_A(STARTMENURET_REOPEN);
    // RET;
    return STARTMENURET_REOPEN;
}

void StartMenu_Pack(void){
    CALL(aFadeToMenu);
    FARCALL(aPack);
    LD_A_addr(wPackUsedItem);
    AND_A_A;
    IF_NZ goto used_item;
    CALL(aCloseSubmenu);
    LD_A(STARTMENURET_REOPEN);
    RET;


used_item:
    CALL(aExitAllMenus);
    LD_A(STARTMENURET_EXIT_MENU_RUN_SCRIPT);
    RET;

}

uint8_t StartMenu_Pack_Conv(void) {
    // struct cpu_registers_s regs = {};
    // SafeCallGB(aStartMenu_Pack, &regs);
    // return regs.a;
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // FARCALL(aPack);
    Pack();
    // LD_A_addr(wPackUsedItem);
    // AND_A_A;
    // IF_NZ goto used_item;
    if(wram->wPackUsedItem == NO_ITEM){
        // CALL(aCloseSubmenu);
        CloseSubmenu_Conv();
        // LD_A(STARTMENURET_REOPEN);
        // RET;
        return STARTMENURET_REOPEN;
    }

// used_item:
    // CALL(aExitAllMenus);
    ExitAllMenus_Conv();
    // LD_A(STARTMENURET_EXIT_MENU_RUN_SCRIPT);
    // RET;
    return STARTMENURET_EXIT_MENU_RUN_SCRIPT;
}

void StartMenu_Pokemon(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    IF_Z goto l_return;

    CALL(aFadeToMenu);


choosemenu:
    XOR_A_A;
    LD_addr_A(wPartyMenuActionText);  // Choose a POKéMON.
    CALL(aClearBGPalettes);


menu:
    FARCALL(aLoadPartyMenuGFX);
    FARCALL(aInitPartyMenuWithCancel);
    FARCALL(aInitPartyMenuGFX);


menunoreload:
    FARCALL(aWritePartyMenuTilemap);
    FARCALL(aPrintPartyMenuText);
    CALL(aWaitBGMap);
    CALL(aSetPalettes);  // load regular palettes?
    CALL(aDelayFrame);
    FARCALL(aPartyMenuSelect);
    IF_C goto l_return;  // if cancelled or pressed B

    CALL(aPokemonActionSubmenu);
    CP_A(3);
    IF_Z goto menu;
    CP_A(0);
    IF_Z goto choosemenu;
    CP_A(1);
    IF_Z goto menunoreload;
    CP_A(2);
    IF_Z goto quit;


l_return:
    CALL(aCloseSubmenu);
    LD_A(STARTMENURET_REOPEN);
    RET;


quit:
    LD_A_B;
    PUSH_AF;
    CALL(aExitAllMenus);
    POP_AF;
    RET;

}

uint8_t StartMenu_Pokemon_Conv(void) {
    // struct cpu_registers_s regs = {};
    // SafeCallGB(aStartMenu_Pokemon, &regs);
    // return regs.a;
    u8_flag_s res;
    struct cpu_registers_s regs;
    // LD_A_addr(wPartyCount);
    // AND_A_A;
    // IF_Z goto l_return;
    if(wram->wPartyCount == 0)
        goto l_return;

    // CALL(aFadeToMenu);
    FadeToMenu_Conv();


choosemenu:
    // XOR_A_A;
    // LD_addr_A(wPartyMenuActionText);  // Choose a POKéMON.
    wram->wPartyMenuActionText = 0;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();

menu:
    // FARCALL(aLoadPartyMenuGFX);
    LoadPartyMenuGFX();
    // FARCALL(aInitPartyMenuWithCancel);
    InitPartyMenuWithCancel();
    // FARCALL(aInitPartyMenuGFX);
    InitPartyMenuGFX();


menunoreload:
    // FARCALL(aWritePartyMenuTilemap);
    WritePartyMenuTilemap();
    // FARCALL(aPrintPartyMenuText);
    PrintPartyMenuText();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aSetPalettes);  // load regular palettes?
    SetPalettes_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // FARCALL(aPartyMenuSelect);
    res = PartyMenuSelect();
    // IF_C goto l_return;  // if cancelled or pressed B
    if(res.flag) goto l_return;

    // CALL(aPokemonActionSubmenu);
    regs = SafeCallGBAutoRet(aPokemonActionSubmenu);
    // CP_A(3);
    // IF_Z goto menu;
    if(regs.a == 3) goto menu;
    // CP_A(0);
    // IF_Z goto choosemenu;
    if(regs.a == 0) goto choosemenu;
    // CP_A(1);
    // IF_Z goto menunoreload;
    if(regs.a == 1) goto menunoreload;
    // CP_A(2);
    // IF_Z goto quit;
    if(regs.a == 2) goto quit;


l_return:
    // CALL(aCloseSubmenu);
    CloseSubmenu_Conv();
    // LD_A(STARTMENURET_REOPEN);
    // RET;
    return STARTMENURET_REOPEN;


quit:
    // LD_A_B;
    // PUSH_AF;
    // CALL(aExitAllMenus);
    ExitAllMenus_Conv();
    // POP_AF;
    // RET;
    return regs.a;
}
