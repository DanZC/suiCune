#include "../../constants.h"
#include "bills_pc.h"
#include "bills_pc_top.h"
#include "mon_stats.h"
#include "mail_2.h"
#include "stats_screen.h"
#include "move_mon.h"
#include "move_mon_wo_mail.h"
#include "tempmon.h"
#include "../gfx/load_pics.h"
#include "../menus/save.h"
#include "../menus/naming_screen.h"
#include "../printer/printer.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../../home/text.h"
#include "../../home/tilemap.h"
#include "../../home/clear_sprites.h"
#include "../../home/lcd.h"
#include "../../home/gfx.h"
#include "../../home/audio.h"
#include "../../home/palettes.h"
#include "../../home/sram.h"
#include "../../home/delay.h"
#include "../../home/joypad.h"
#include "../../home/names.h"
#include "../../home/menu.h"
#include "../../home/scrolling_menu.h"
#include "../../home/print_text.h"
#include "../../home/string.h"
#include "../../home/copy_name.h"

static void v_DepositPKMN_RunJumptable(void);

void v_DepositPKMN(void){
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0;
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0;
    // CALL(aBillsPC_InitRAM);
    BillsPC_InitRAM();
    // XOR_A_A;
    // LD_addr_A(wBillsPC_LoadedBox);
    wram->wBillsPC_LoadedBox = 0;
    // CALL(aDelayFrame);
    DelayFrame();

    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto done;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(av_DepositPKMN_RunJumptable);
        v_DepositPKMN_RunJumptable();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// done:
    // CALL(aClearSprites);
    ClearSprites();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // RET;
    return;
}

static void v_DepositPKMN_RunJumptable(void) {
    // LD_A_addr(wJumptableIndex);
    // LD_HL(mv_DepositPKMN_Jumptable);
    // CALL(aBillsPC_Jumptable);
    // JP_hl;


// Jumptable:
    switch(wram->wJumptableIndex) {
    //dw ['.Init'];
    case 0:
    // Init:
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aClearSprites);
        ClearSprites();
        // CALL(aCopyBoxmonSpecies);
        CopyBoxmonSpecies();
        // CALL(aBillsPC_BoxName);
        BillsPC_BoxName();
        // LD_DE(mPCString_ChooseaPKMN);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_ChooseaPKMN));
        // LD_A(0x5);
        // LD_addr_A(wBillsPC_NumMonsOnScreen);
        wram->wBillsPC_NumMonsOnScreen = 0x5;
        // CALL(aBillsPC_RefreshTextboxes);
        BillsPC_RefreshTextboxes();
        // CALL(aPCMonInfo);
        PCMonInfo();
        // LD_A(0xff);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = (species_t)-1;
        // LD_A(SCGB_BILLS_PC);
        // CALL(aBillsPC_ApplyPalettes);
        BillsPC_ApplyPalettes(SCGB_BILLS_PC);
        // CALL(aWaitBGMap);
        WaitBGMap();
        // CALL(aBillsPC_UpdateSelectionCursor);
        BillsPC_UpdateSelectionCursor();
        // CALL(aBillsPC_IncrementJumptableIndex);
        BillsPC_IncrementJumptableIndex();
        // RET;
        return;
    //dw ['.HandleJoypad'];
    case 1: {
    // HandleJoypad:
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // IF_NZ goto b_button;
        if(hram->hJoyPressed & B_BUTTON) {
        b_button:
            // LD_A(0x4);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x4;
            // RET;
            return;
        }
        // LD_A_hl;
        // AND_A(A_BUTTON);
        // IF_NZ goto a_button;
        if(hram->hJoyPressed & A_BUTTON) {
        // a_button:
            species_t a;
            // CALL(aBillsPC_GetSelectedPokemonSpecies);
            a = BillsPC_GetSelectedPokemonSpecies_Conv();
            // AND_A_A;
            // RET_Z ;
            if(a == 0)
                return;
            // CP_A(-1);
            // IF_Z goto b_button;
            else if(a == (species_t)-1)
                goto b_button;
            // LD_A(0x2);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x2;
            // RET;
            return;
        }
        // CALL(aWithdraw_UpDown);
        u8_flag_s upDown = Withdraw_UpDown_Conv();
        // AND_A_A;
        // RET_Z ;
        if(upDown.a == 0)
            return;
        // CALL(aBillsPC_UpdateSelectionCursor);
        BillsPC_UpdateSelectionCursor();
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aBillsPC_RefreshTextboxes);
        BillsPC_RefreshTextboxes();
        // CALL(aPCMonInfo);
        PCMonInfo();
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDelayFrame);
        DelayFrame();
        // RET;
    } return;
    // go_back:
    //   //  unreferenced
        // LD_HL(wJumptableIndex);
        // DEC_hl;
        // RET;
    //dw ['.WhatsUp'];
    case 2:
    // WhatsUp:
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aClearSprites);
        ClearSprites();
        // CALL(aBillsPC_GetSelectedPokemonSpecies);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = BillsPC_GetSelectedPokemonSpecies_Conv();
        // LD_A(SCGB_BILLS_PC);
        // CALL(aBillsPC_ApplyPalettes);
        BillsPC_ApplyPalettes(SCGB_BILLS_PC);
        // LD_DE(mPCString_WhatsUp);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_WhatsUp));
        // LD_A(0x1);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 0x1;
        // CALL(aBillsPC_IncrementJumptableIndex);
        BillsPC_IncrementJumptableIndex();
        // RET;
        return;
    //dw ['.Submenu'];
    case 3: {
    // Submenu:
        // LD_HL(mBillsPCDepositMenuHeader);
        // CALL(aCopyMenuHeader);
        CopyMenuHeader(&BillsPCDepositMenuHeader);
        // LD_A_addr(wMenuCursorY);
        // CALL(aStoreMenuCursorPosition);
        StoreMenuCursorPosition(wram->wMenuCursorY);
        // CALL(aVerticalMenu);
        bool cancel = VerticalMenu();
        // JP_C (mBillsPCDepositFuncCancel);
        if(cancel) {
            return BillsPCDepositFuncCancel();
        }
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // AND_A(0b11);
        // LD_E_A;
        // LD_D(0);
        // LD_HL(mBillsPCDepositJumptable);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        switch((wram->wMenuCursorY - 1) & 0b11) {
            //dw ['BillsPCDepositFuncDeposit'];  // Deposit Pokemon
            case 0: return BillsPCDepositFuncDeposit();
            //dw ['BillsPCDepositFuncStats'];  // Pokemon Stats
            case 1: return BillsPCDepositFuncStats();
            //dw ['BillsPCDepositFuncRelease'];  // Release Pokemon
            case 2: return BillsPCDepositFuncRelease();
            //dw ['BillsPCDepositFuncCancel'];  // Cancel
            case 3: return BillsPCDepositFuncCancel();
        }
        // JP_hl;
    } return;
    //dw ['BillsPC_EndJumptableLoop'];
    case 4:
        return BillsPC_EndJumptableLoop();
    }
}

void BillsPCDepositFuncDeposit(void){
    // CALL(aBillsPC_CheckMail_PreventBlackout);
    // JP_C (mBillsPCDepositFuncCancel);
    if(BillsPC_CheckMail_PreventBlackout_Conv())
        return BillsPCDepositFuncCancel();
    // CALL(aDepositPokemon);
    // IF_C goto box_full;
    if(DepositPokemon_Conv()) {
    // box_full:
        // LD_DE(mPCString_WhatsUp);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_WhatsUp));
        // RET;
        return;
    }
    // LD_A(0x0);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // XOR_A_A;
    // LD_addr_A(wBillsPC_CursorPosition);
    wram->wBillsPC_CursorPosition = 0;
    // LD_addr_A(wBillsPC_ScrollPosition);
    wram->wBillsPC_ScrollPosition = 0;
    // RET;
    return;

}

void BillsPCDepositFuncStats(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // CALL(aBillsPC_StatsScreen);
    BillsPC_StatsScreen_Conv();
    // CALL(aExitMenu);
    ExitMenu();
    // CALL(aPCMonInfo);
    PCMonInfo();
    // CALL(aBillsPC_GetSelectedPokemonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = BillsPC_GetSelectedPokemonSpecies_Conv();
    // LD_A(SCGB_BILLS_PC);
    // CALL(aBillsPC_ApplyPalettes);
    BillsPC_ApplyPalettes(SCGB_BILLS_PC);
    // RET;
}

void BillsPCDepositFuncRelease(void){
    // CALL(aBillsPC_CheckMail_PreventBlackout);
    // JR_C (mBillsPCDepositFuncCancel);
    if(BillsPC_CheckMail_PreventBlackout_Conv())
        return BillsPCDepositFuncCancel();
    // CALL(aBillsPC_IsMonAnEgg);
    // JR_C (mBillsPCDepositFuncCancel);
    if(BillsPC_IsMonAnEgg_Conv())
        return BillsPCDepositFuncCancel();
    // LD_A_addr(wMenuCursorY);
    // PUSH_AF;
    uint8_t menuCursorY = wram->wMenuCursorY;
    // LD_DE(mPCString_ReleasePKMN);
    // CALL(aBillsPC_PlaceString);
    BillsPC_PlaceString_Conv(U82C(PCString_ReleasePKMN));
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // LD_BC((14 << 8) | 11);
    // CALL(aPlaceYesNoBox);
    PlaceYesNoBox(14, 11);
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // CALL(aExitMenu);
    // AND_A_A;
    // IF_NZ goto failed_release;
    if(wram->wMenuCursorY != 1) {
    // failed_release:
        // LD_DE(mPCString_WhatsUp);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_WhatsUp));
        // POP_AF;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = menuCursorY;
        // RET;
        return;
    }
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition;
    // XOR_A_A;  // REMOVE_PARTY
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // FARCALL(aRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox_Conv(REMOVE_PARTY);
    // CALL(aReleasePKMN_ByePKMN);
    ReleasePKMN_ByePKMN();
    // LD_A(0x0);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // XOR_A_A;
    // LD_addr_A(wBillsPC_CursorPosition);
    wram->wBillsPC_CursorPosition = 0;
    // LD_addr_A(wBillsPC_ScrollPosition);
    wram->wBillsPC_ScrollPosition = 0;
    // POP_AF;
    // RET;
}

void BillsPCDepositFuncCancel(void){
    // LD_A(0x0);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // RET;
}

const struct MenuHeader BillsPCDepositMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(9, 4, SCREEN_WIDTH - 1, 13),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
// MenuData:
        .flags = STATICMENU_CURSOR,  // flags
        .verticalMenu = {
            .count = 4,  // items
            .options = (const char*[]) {
                "DEPOSIT@",
                "STATS@",
                "RELEASE@",
                "CANCEL@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

void BillsPCClearThreeBoxes(void){
//  //  unreferenced
    hlcoord(0, 0, wTilemap);
    LD_B(4);
    LD_C(8);
    CALL(aClearBox);
    hlcoord(0, 4, wTilemap);
    LD_B(10);
    LD_C(9);
    CALL(aClearBox);
    hlcoord(0, 14, wTilemap);
    LD_B(2);
    LD_C(8);
    CALL(aClearBox);
    RET;

}

static void v_WithdrawPKMN_RunJumptable(void);

void v_WithdrawPKMN(void){
    // LD_HL(wOptions);
    // LD_A_hl;
    uint8_t options = wram->wOptions;
    // PUSH_AF;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0x0;
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = FALSE;
    // CALL(aBillsPC_InitRAM);
    BillsPC_InitRAM();
    // LD_A(NUM_BOXES + 1);
    // LD_addr_A(wBillsPC_LoadedBox);
    wram->wBillsPC_LoadedBox = NUM_BOXES + 1;
    // CALL(aDelayFrame);
    DelayFrame();

    while(1){
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto done;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(av_WithdrawPKMN_RunJumptable);
        v_WithdrawPKMN_RunJumptable();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// done:
    // CALL(aClearSprites);
    ClearSprites();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // RET;
    return;
}

static void v_WithdrawPKMN_RunJumptable(void){
    // LD_A_addr(wJumptableIndex);
    // LD_HL(mv_WithdrawPKMN_Jumptable);
    // CALL(aBillsPC_Jumptable);
    // JP_hl;

    switch(wram->wJumptableIndex){
    // Jumptable:
        //dw ['.Init'];
    case 0:
    // Init:
        // LD_A(NUM_BOXES + 1);
        // LD_addr_A(wBillsPC_LoadedBox);
        wram->wBillsPC_LoadedBox = NUM_BOXES + 1;
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aClearSprites);
        ClearSprites();
        // CALL(aCopyBoxmonSpecies);
        CopyBoxmonSpecies();
        // CALL(aBillsPC_BoxName);
        BillsPC_BoxName();
        // LD_DE(mPCString_ChooseaPKMN);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_ChooseaPKMN));
        // LD_A(0x5);
        // LD_addr_A(wBillsPC_NumMonsOnScreen);
        wram->wBillsPC_NumMonsOnScreen = 0x5;
        // CALL(aBillsPC_RefreshTextboxes);
        BillsPC_RefreshTextboxes();
        // CALL(aPCMonInfo);
        PCMonInfo();
        // LD_A(0xff);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = (species_t)-1;
        // LD_A(SCGB_BILLS_PC);
        // CALL(aBillsPC_ApplyPalettes);
        BillsPC_ApplyPalettes(SCGB_BILLS_PC);
        // CALL(aWaitBGMap);
        WaitBGMap();
        // CALL(aBillsPC_UpdateSelectionCursor);
        BillsPC_UpdateSelectionCursor();
        // CALL(aBillsPC_IncrementJumptableIndex);
        BillsPC_IncrementJumptableIndex();
        // RET;
        return;

        //dw ['.Joypad'];
    case 1: {
    // Joypad:
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // IF_NZ goto b_button;
        if(hram->hJoyPressed & B_BUTTON) {
        b_button:
            // LD_A(0x4);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x4;
            // RET;
            return;
        }
        // LD_A_hl;
        // AND_A(A_BUTTON);
        // IF_NZ goto a_button;
        if(hram->hJoyPressed & A_BUTTON) {
        // a_button:
            // CALL(aBillsPC_GetSelectedPokemonSpecies);
            species_t a = BillsPC_GetSelectedPokemonSpecies_Conv();
            // AND_A_A;
            // RET_Z ;
            if(a == 0)
                return;
            // CP_A(-1);
            // IF_Z goto b_button;
            if(a == (species_t)-1)
                goto b_button;
            // LD_A(0x2);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x2;
            // RET;
            return;
        }
        // CALL(aWithdraw_UpDown);
        // AND_A_A;
        // RET_Z ;
        if(Withdraw_UpDown_Conv().a == 0)
            return;
        // CALL(aBillsPC_UpdateSelectionCursor);
        BillsPC_UpdateSelectionCursor();
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aBillsPC_RefreshTextboxes);
        BillsPC_RefreshTextboxes();
        // CALL(aPCMonInfo);
        PCMonInfo();
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDelayFrame);
        DelayFrame();
        // RET;
    } return;


    // go_back:
    //   //  unreferenced
        // LD_HL(wJumptableIndex);
        // DEC_hl;
        // RET;


        //dw ['.PrepSubmenu'];
    case 2:
    // PrepSubmenu:
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aClearSprites);
        ClearSprites();
        // CALL(aBillsPC_GetSelectedPokemonSpecies);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = BillsPC_GetSelectedPokemonSpecies_Conv();
        // LD_A(SCGB_BILLS_PC);
        // CALL(aBillsPC_ApplyPalettes);
        BillsPC_ApplyPalettes(SCGB_BILLS_PC);
        // LD_DE(mPCString_WhatsUp);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_WhatsUp));
        // LD_A(0x1);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 0x1;
        // CALL(aBillsPC_IncrementJumptableIndex);
        BillsPC_IncrementJumptableIndex();
        // RET;
        return;

    case 3:
        //dw ['BillsPC_Withdraw'];
        return BillsPC_Withdraw();

    case 4:
        //dw ['BillsPC_EndJumptableLoop'];
        return BillsPC_EndJumptableLoop();
    }
}

const struct MenuHeader BillsPC_Withdraw_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(9, 4, SCREEN_WIDTH - 1, 13),
    //dw ['.MenuData'];
    // MenuData:
    .data = &(struct MenuData){
        .flags = STATICMENU_CURSOR,  // flags
        .verticalMenu = {
            .count = 4,  // items
            .options = (const char*[]) {
                "WITHDRAW@",
                "STATS@",
                "RELEASE@",
                "CANCEL@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

void BillsPC_Withdraw(void){
    // LD_HL(mBillsPC_Withdraw_MenuHeader);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(&BillsPC_Withdraw_MenuHeader);
    // LD_A_addr(wMenuCursorY);
    // CALL(aStoreMenuCursorPosition);
    StoreMenuCursorPosition(wram->wMenuCursorY);
    // CALL(aVerticalMenu);
    bool cancel = VerticalMenu();
    // JP_C (mBillsPC_Withdraw_cancel);
    if(cancel)
        goto cancel;
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // AND_A(0b11);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mBillsPC_Withdraw_dw);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;

    switch((wram->wMenuCursorY - 1) & 0b11) {
    // dw:
        //dw ['.withdraw'];  // Withdraw
        //dw ['.stats'];  // Stats
        //dw ['.release'];  // Release
        //dw ['.cancel'];  // Cancel

    case 0:
    // withdraw:
        // CALL(aBillsPC_CheckMail_PreventBlackout);
        // JP_C (mBillsPC_Withdraw_cancel);
        if(BillsPC_CheckMail_PreventBlackout_Conv())
            goto cancel;
        // CALL(aTryWithdrawPokemon);
        // IF_C goto FailedWithdraw;
        if(TryWithdrawPokemon_Conv()) {
        // FailedWithdraw:
            // LD_DE(mPCString_WhatsUp);
            // CALL(aBillsPC_PlaceString);
            BillsPC_PlaceString_Conv(U82C(PCString_WhatsUp));
            // RET;
            return;
        }
        // LD_A(0x0);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x0;
        // XOR_A_A;
        // LD_addr_A(wBillsPC_CursorPosition);
        // LD_addr_A(wBillsPC_ScrollPosition);
        wram->wBillsPC_CursorPosition = 0x0;
        wram->wBillsPC_ScrollPosition = 0x0;
        // RET;
        return;

    case 1:
    // stats:
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader();
        // CALL(aBillsPC_StatsScreen);
        BillsPC_StatsScreen_Conv();
        // CALL(aExitMenu);
        ExitMenu();
        // CALL(aPCMonInfo);
        PCMonInfo();
        // CALL(aBillsPC_GetSelectedPokemonSpecies);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = BillsPC_GetSelectedPokemonSpecies_Conv();
        // LD_A(SCGB_BILLS_PC);
        // CALL(aBillsPC_ApplyPalettes);
        BillsPC_ApplyPalettes(SCGB_BILLS_PC);
        // RET;
        return;

    case 2: {
    // release:
        // LD_A_addr(wMenuCursorY);
        uint8_t menuCursorY = wram->wMenuCursorY;
        // PUSH_AF;
        // CALL(aBillsPC_IsMonAnEgg);
        // IF_C goto FailedRelease;
        if(BillsPC_IsMonAnEgg_Conv()) {
        FailedRelease:
            // LD_DE(mPCString_WhatsUp);
            // CALL(aBillsPC_PlaceString);
            BillsPC_PlaceString_Conv(U82C(PCString_WhatsUp));
            // POP_AF;
            // LD_addr_A(wMenuCursorY);
            wram->wMenuCursorY = menuCursorY;
            // RET;
            return;
        }
        // LD_DE(mPCString_ReleasePKMN);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_ReleasePKMN));
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader();
        // LD_BC((14 << 8) | 11);
        // CALL(aPlaceYesNoBox);
        bool yes = PlaceYesNoBox(14, 11);
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // CALL(aExitMenu);
        ExitMenu();
        // AND_A_A;
        // IF_NZ goto FailedRelease;
        if(!yes)
            goto FailedRelease;
        // LD_A_addr(wBillsPC_CursorPosition);
        // LD_HL(wBillsPC_ScrollPosition);
        // ADD_A_hl;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon = wram->wBillsPC_ScrollPosition + wram->wBillsPC_CursorPosition;
        // LD_A(REMOVE_BOX);
        // LD_addr_A(wPokemonWithdrawDepositParameter);
        // FARCALL(aRemoveMonFromPartyOrBox);
        RemoveMonFromPartyOrBox_Conv(REMOVE_BOX);
        // CALL(aReleasePKMN_ByePKMN);
        ReleasePKMN_ByePKMN();
        // LD_A(0x0);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x0;
        // XOR_A_A;
        // LD_addr_A(wBillsPC_CursorPosition);
        // LD_addr_A(wBillsPC_ScrollPosition);
        wram->wBillsPC_CursorPosition = 0x0;
        wram->wBillsPC_ScrollPosition = 0x0;
        // POP_AF;
        // RET;
    } return;

    case 3:
    cancel:
        // LD_A(0x0);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x0;
        // RET;
        return;
    }
}

static void v_MovePKMNWithoutMail_RunJumptable(void);

void v_MovePKMNWithoutMail(void){
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // LD_A_addr(wVramState);
    // PUSH_AF;
    uint8_t vramState = wram->wVramState;
    // XOR_A_A;
    // LD_addr_A(wVramState);
    wram->wVramState = 0x0;
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = FALSE;
    // CALL(aBillsPC_InitRAM);
    BillsPC_InitRAM();
    // LD_A_addr(wCurBox);
    // AND_A(0xf);
    // INC_A;
    // LD_addr_A(wBillsPC_LoadedBox);
    wram->wBillsPC_LoadedBox = (wram->wCurBox & 0xf) + 1;
    // CALL(aDelayFrame);
    DelayFrame();

    while(1){
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto done;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(av_MovePKMNWithoutMail_RunJumptable);
        v_MovePKMNWithoutMail_RunJumptable();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// done:
    // CALL(aClearSprites);
    ClearSprites();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // POP_AF;
    // LD_addr_A(wVramState);
    wram->wVramState = vramState;
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // RET;
    return;
}

const struct MenuHeader v_MovePKMNWithoutMail_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(9, 4, SCREEN_WIDTH - 1, 13),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR,  // flags
        .verticalMenu = {
            .count = 3,  // items
            .options = (const char*[]) {
                "MOVE@",
                "STATS@",
                "CANCEL@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

static void v_MovePKMNWithoutMail_RunJumptable(void){
    // LD_A_addr(wJumptableIndex);
    // LD_HL(mv_MovePKMNWithoutMail_Jumptable);
    // CALL(aBillsPC_Jumptable);
    // JP_hl;
    switch(wram->wJumptableIndex) {
    // Jumptable:
        //dw ['.Init'];
        //dw ['.Joypad'];
        //dw ['.PrepSubmenu'];
        //dw ['.MoveMonWOMailSubmenu'];
        //dw ['.PrepInsertCursor'];
        //dw ['.Joypad2'];
        //dw ['BillsPC_EndJumptableLoop'];

    case 0:
    // Init:
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aClearSprites);
        ClearSprites();
        // CALL(aCopyBoxmonSpecies);
        CopyBoxmonSpecies();
        // LD_DE(mPCString_ChooseaPKMN);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_ChooseaPKMN));
        // LD_A(5);
        // LD_addr_A(wBillsPC_NumMonsOnScreen);
        wram->wBillsPC_NumMonsOnScreen = 5;
        // CALL(aBillsPC_RefreshTextboxes);
        BillsPC_RefreshTextboxes();
        // CALL(aBillsPC_MoveMonWOMail_BoxNameAndArrows);
        BillsPC_MoveMonWOMail_BoxNameAndArrows();
        // CALL(aPCMonInfo);
        PCMonInfo();
        // LD_A(0xff);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = (species_t)-1;
        // LD_A(SCGB_BILLS_PC);
        // CALL(aBillsPC_ApplyPalettes);
        BillsPC_ApplyPalettes(SCGB_BILLS_PC);
        // CALL(aWaitBGMap);
        WaitBGMap();
        // CALL(aBillsPC_UpdateSelectionCursor);
        BillsPC_UpdateSelectionCursor();
        // CALL(aBillsPC_IncrementJumptableIndex);
        BillsPC_IncrementJumptableIndex();
        // RET;
        return;

    case 1:
    // Joypad:
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // IF_NZ goto b_button;
        if(hram->hJoyPressed & B_BUTTON) {
        b_button:
            // LD_A(0x6);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x6;
            // RET;
            return;
        }
        // LD_A_hl;
        // AND_A(A_BUTTON);
        // IF_NZ goto a_button;
        else if(hram->hJoyPressed & A_BUTTON) {
        // a_button:
            // CALL(aBillsPC_GetSelectedPokemonSpecies);
            species_t species = BillsPC_GetSelectedPokemonSpecies_Conv();
            // AND_A_A;
            // RET_Z ;
            if(species == 0)
                return;
            // CP_A(-1);
            // IF_Z goto b_button;
            if(species == (species_t)-1)
                goto b_button;
            // LD_A(0x2);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x2;
            // RET;
            return;
        }
        // CALL(aMoveMonWithoutMail_DPad);
        u8_flag_s res = MoveMonWithoutMail_DPad_Conv();
        // IF_C goto d_pad;
        if(res.flag) {
        // d_pad:
            // XOR_A_A;
            // LD_addr_A(wBillsPC_CursorPosition);
            wram->wBillsPC_CursorPosition = 0x0;
            // LD_addr_A(wBillsPC_ScrollPosition);
            wram->wBillsPC_ScrollPosition = 0x0;
            // LD_A(0x0);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x0;
            // RET;
            return;
        }
        // AND_A_A;
        // RET_Z ;
        if(res.a == 0)
            return;
        // CALL(aBillsPC_UpdateSelectionCursor);
        BillsPC_UpdateSelectionCursor();
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aBillsPC_RefreshTextboxes);
        BillsPC_RefreshTextboxes();
        // CALL(aPCMonInfo);
        PCMonInfo();
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDelayFrame);
        DelayFrame();
        // RET;
        return;

    // go_back:
    //   //  unreferenced
        // LD_HL(wJumptableIndex);
        // DEC_hl;
        // RET;

    case 2:
    // PrepSubmenu:
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aClearSprites);
        ClearSprites();
        // CALL(aBillsPC_GetSelectedPokemonSpecies);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = BillsPC_GetSelectedPokemonSpecies_Conv();
        // LD_A(SCGB_BILLS_PC);
        // CALL(aBillsPC_ApplyPalettes);
        BillsPC_ApplyPalettes(SCGB_BILLS_PC);
        // LD_DE(mPCString_WhatsUp);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_WhatsUp));
        // LD_A(0x1);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 0x1;
        // CALL(aBillsPC_IncrementJumptableIndex);
        BillsPC_IncrementJumptableIndex();
        // RET;
        return;

    case 3: {
    // MoveMonWOMailSubmenu:
        // LD_HL(mv_MovePKMNWithoutMail_MenuHeader);
        // CALL(aCopyMenuHeader);
        CopyMenuHeader(&v_MovePKMNWithoutMail_MenuHeader);
        // LD_A_addr(wMenuCursorY);
        // CALL(aStoreMenuCursorPosition);
        StoreMenuCursorPosition(wram->wMenuCursorY);
        // CALL(aVerticalMenu);
        bool cancel = VerticalMenu();
        // JP_C (mv_MovePKMNWithoutMail_Cancel);
        if(cancel)
            goto Cancel;
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // AND_A(0b11);
        // LD_E_A;
        // LD_D(0);
        // LD_HL(mv_MovePKMNWithoutMail_Jumptable2);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // JP_hl;
        switch((wram->wMenuCursorY - 1) & 0b11) {
        // Jumptable2:
            //dw ['.Move'];
        case 0:
        // Move:
            // CALL(aBillsPC_CheckMail_PreventBlackout);
            // JP_C (mv_MovePKMNWithoutMail_Cancel);
            if(BillsPC_CheckMail_PreventBlackout_Conv())
                goto Cancel;
            // LD_A_addr(wBillsPC_ScrollPosition);
            // LD_addr_A(wBillsPC_BackupScrollPosition);
            wram->wBillsPC_BackupScrollPosition = wram->wBillsPC_ScrollPosition;
            // LD_A_addr(wBillsPC_CursorPosition);
            // LD_addr_A(wBillsPC_BackupCursorPosition);
            wram->wBillsPC_BackupCursorPosition = wram->wBillsPC_CursorPosition;
            // LD_A_addr(wBillsPC_LoadedBox);
            // LD_addr_A(wBillsPC_BackupLoadedBox);
            wram->wBillsPC_BackupLoadedBox = wram->wBillsPC_LoadedBox;
            // LD_A(0x4);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x4;
            // RET;
            return;

            //dw ['.Stats'];
        case 1:
        // Stats:
            // CALL(aLoadStandardMenuHeader);
            LoadStandardMenuHeader();
            // CALL(aBillsPC_StatsScreen);
            BillsPC_StatsScreen_Conv();
            // CALL(aExitMenu);
            ExitMenu();
            // CALL(aPCMonInfo);
            PCMonInfo();
            // CALL(aBillsPC_GetSelectedPokemonSpecies);
            // LD_addr_A(wCurPartySpecies);
            wram->wCurPartySpecies = BillsPC_GetSelectedPokemonSpecies_Conv();
            // LD_A(SCGB_BILLS_PC);
            // CALL(aBillsPC_ApplyPalettes);
            BillsPC_ApplyPalettes(SCGB_BILLS_PC);
            // RET;
            return;

            //dw ['.Cancel'];
        case 2:
        Cancel:
            // LD_A(0x0);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x0;
            // RET;
            break;
        }
    } return;

    case 4:
    // PrepInsertCursor:
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aCopyBoxmonSpecies);
        CopyBoxmonSpecies();
        // LD_DE(mPCString_MoveToWhere);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_MoveToWhere));
        // LD_A(0x5);
        // LD_addr_A(wBillsPC_NumMonsOnScreen);
        wram->wBillsPC_NumMonsOnScreen = 0x5;
        // CALL(aBillsPC_RefreshTextboxes);
        BillsPC_RefreshTextboxes();
        // CALL(aBillsPC_MoveMonWOMail_BoxNameAndArrows);
        BillsPC_MoveMonWOMail_BoxNameAndArrows();
        // CALL(aClearSprites);
        ClearSprites();
        // CALL(aBillsPC_UpdateInsertCursor);
        BillsPC_UpdateInsertCursor();
        // CALL(aWaitBGMap);
        WaitBGMap();
        // CALL(aBillsPC_IncrementJumptableIndex);
        BillsPC_IncrementJumptableIndex();
        // RET;
        return;

    case 5: {
    // Joypad2:
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // IF_NZ goto b_button_2;
        if(hram->hJoyPressed & B_BUTTON) {
        // b_button_2:
            // LD_A_addr(wBillsPC_BackupScrollPosition);
            // LD_addr_A(wBillsPC_ScrollPosition);
            wram->wBillsPC_ScrollPosition = wram->wBillsPC_BackupScrollPosition;
            // LD_A_addr(wBillsPC_BackupCursorPosition);
            // LD_addr_A(wBillsPC_CursorPosition);
            wram->wBillsPC_CursorPosition = wram->wBillsPC_BackupCursorPosition;
            // LD_A_addr(wBillsPC_BackupLoadedBox);
            // LD_addr_A(wBillsPC_LoadedBox);
            wram->wBillsPC_LoadedBox = wram->wBillsPC_BackupLoadedBox;
            // LD_A(0x0);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x0;
            // RET;
            return;
        }
        // LD_A_hl;
        // AND_A(A_BUTTON);
        // IF_NZ goto a_button_2;
        else if(hram->hJoyPressed & A_BUTTON){
        // a_button_2:
            // CALL(aBillsPC_CheckSpaceInDestination);
            // IF_C goto no_space;
            if(BillsPC_CheckSpaceInDestination()) {
                // CALL(aMovePKMNWitoutMail_InsertMon);
                MovePKMNWitoutMail_InsertMon();
                // LD_A(0x0);
                // LD_addr_A(wJumptableIndex);
                wram->wJumptableIndex = 0x0;
                // RET;
                return;
            }

        // no_space:
            // LD_HL(wJumptableIndex);
            // DEC_hl;
            wram->wJumptableIndex--;
            // RET;
            return;
        }
        // CALL(aMoveMonWithoutMail_DPad_2);
        u8_flag_s res = MoveMonWithoutMail_DPad_2_Conv();
        // IF_C goto dpad_2;
        if(res.flag) {
        // dpad_2:
            // XOR_A_A;
            // LD_addr_A(wBillsPC_CursorPosition);
            wram->wBillsPC_CursorPosition = 0x0;
            // LD_addr_A(wBillsPC_ScrollPosition);
            wram->wBillsPC_ScrollPosition = 0x0;
            // LD_A(0x4);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = 0x4;
            // RET;
            return;
        }
        // AND_A_A;
        // RET_Z ;
        if(res.a == 0)
            return;
        // CALL(aBillsPC_UpdateInsertCursor);
        BillsPC_UpdateInsertCursor();
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aBillsPC_RefreshTextboxes);
        BillsPC_RefreshTextboxes();
        // LD_A(0x1);
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDelayFrame);
        DelayFrame();
        // RET;
    } return;
    }
}

void BillsPC_InitRAM(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearTilemap);
    ClearTilemap();
    // CALL(aBillsPC_InitGFX);
    BillsPC_InitGFX();
    // LD_HL(wBillsPCData);
    // LD_BC(wBillsPCDataEnd - wBillsPCData);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wBillsPCPokemonList, (wBillsPCDataEnd - wBillsPCData), 0);
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
    // LD_addr_A(wUnusedBillsPCData);
    wram->wUnusedBillsPCData[0] = 0;
    // LD_addr_A(wUnusedBillsPCData+1);
    wram->wUnusedBillsPCData[1] = 0;
    // LD_addr_A(wUnusedBillsPCData+2);
    wram->wUnusedBillsPCData[2] = 0;
    // LD_addr_A(wBillsPC_CursorPosition);
    wram->wBillsPC_CursorPosition = 0;
    // LD_addr_A(wBillsPC_ScrollPosition);
    wram->wBillsPC_ScrollPosition = 0;
    // RET;
}

void BillsPC_IncrementJumptableIndex(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    // RET;
    wram->wJumptableIndex++;
}

void BillsPC_EndJumptableLoop(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    // RET;
    bit_set(wram->wJumptableIndex, 7);
}

void v_StatsScreenDPad(void){
    LD_A_addr(wBillsPC_NumMonsOnScreen);
    LD_D_A;
    LD_A_addr(wBillsPC_NumMonsInBox);
    AND_A_A;
    IF_Z goto empty;
    DEC_A;
    CP_A(0x1);
    IF_Z goto empty;
    LD_E_A;
    LD_A_hl;
    AND_A(D_UP);
    JR_NZ (mBillsPC_PressUp);
    LD_A_hl;
    AND_A(D_DOWN);
    JR_NZ (mBillsPC_PressDown);

empty:
    JP(mBillsPC_JoypadDidNothing);

}

u8_flag_s v_StatsScreenDPad_Conv(uint8_t* hl){
    // LD_A_addr(wBillsPC_NumMonsOnScreen);
    // LD_D_A;
    uint8_t d = wram->wBillsPC_NumMonsOnScreen;
    // LD_A_addr(wBillsPC_NumMonsInBox);
    uint8_t e = wram->wBillsPC_NumMonsInBox;
    // AND_A_A;
    // IF_Z goto empty;
    if(e == 0) {
        return BillsPC_JoypadDidNothing_Conv();
    }
    // DEC_A;
    // CP_A(0x1);
    // IF_Z goto empty;
    if(--e == 0x1) {
        return BillsPC_JoypadDidNothing_Conv();
    }
    // LD_E_A;
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mBillsPC_PressUp);
    if(*hl & D_UP)
        return BillsPC_PressUp_Conv();
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mBillsPC_PressDown);
    if(*hl & D_DOWN)
        return BillsPC_PressDown_Conv(d, e);

// empty:
    // JP(mBillsPC_JoypadDidNothing);
    return BillsPC_JoypadDidNothing_Conv();
}

void Withdraw_UpDown(void){
    LD_HL(hJoyLast);
    LD_A_addr(wBillsPC_NumMonsOnScreen);
    LD_D_A;
    LD_A_addr(wBillsPC_NumMonsInBox);
    LD_E_A;
    AND_A_A;
    IF_Z goto empty;
    LD_A_hl;
    AND_A(D_UP);
    JR_NZ (mBillsPC_PressUp);
    LD_A_hl;
    AND_A(D_DOWN);
    JR_NZ (mBillsPC_PressDown);

empty:
    JP(mBillsPC_JoypadDidNothing);

}

u8_flag_s Withdraw_UpDown_Conv(void){
    // LD_HL(hJoyLast);
    // LD_A_addr(wBillsPC_NumMonsOnScreen);
    // LD_D_A;
    // LD_A_addr(wBillsPC_NumMonsInBox);
    // LD_E_A;
    // AND_A_A;
    // IF_Z goto empty;
    if(wram->wBillsPC_NumMonsInBox == 0)
        return BillsPC_JoypadDidNothing_Conv();
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mBillsPC_PressUp);
    if(hram->hJoyLast & D_UP)
        return BillsPC_PressUp_Conv();
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mBillsPC_PressDown);
    if(hram->hJoyLast & D_DOWN)
        return BillsPC_PressDown_Conv(wram->wBillsPC_NumMonsOnScreen, wram->wBillsPC_NumMonsInBox);

// empty:
    // JP(mBillsPC_JoypadDidNothing);
    return BillsPC_JoypadDidNothing_Conv();
}

void MoveMonWithoutMail_DPad(void){
    LD_HL(hJoyLast);
    LD_A_addr(wBillsPC_NumMonsOnScreen);
    LD_D_A;
    LD_A_addr(wBillsPC_NumMonsInBox);
    LD_E_A;
    AND_A_A;
    IF_Z goto check_left_right;
    LD_A_hl;
    AND_A(D_UP);
    JR_NZ (mBillsPC_PressUp);
    LD_A_hl;
    AND_A(D_DOWN);
    JR_NZ (mBillsPC_PressDown);


check_left_right:
    LD_A_hl;
    AND_A(D_LEFT);
    JR_NZ (mBillsPC_PressLeft);
    LD_A_hl;
    AND_A(D_RIGHT);
    JR_NZ (mBillsPC_PressRight);
    JR(mBillsPC_JoypadDidNothing);

}

u8_flag_s MoveMonWithoutMail_DPad_Conv(void){
    // LD_HL(hJoyLast);
    // LD_A_addr(wBillsPC_NumMonsOnScreen);
    // LD_D_A;
    uint8_t d = wram->wBillsPC_NumMonsOnScreen;
    // LD_A_addr(wBillsPC_NumMonsInBox);
    // LD_E_A;
    uint8_t e = wram->wBillsPC_NumMonsInBox;
    // AND_A_A;
    // IF_Z goto check_left_right;
    if(e != 0) {
        // LD_A_hl;
        // AND_A(D_UP);
        // JR_NZ (mBillsPC_PressUp);
        if(hram->hJoyLast & D_UP)
            return BillsPC_PressUp_Conv();
        // LD_A_hl;
        // AND_A(D_DOWN);
        // JR_NZ (mBillsPC_PressDown);
        if(hram->hJoyLast & D_DOWN)
            return BillsPC_PressDown_Conv(d, e);
    }

// check_left_right:
    // LD_A_hl;
    // AND_A(D_LEFT);
    // JR_NZ (mBillsPC_PressLeft);
    if(hram->hJoyLast & D_LEFT)
        return BillsPC_PressLeft_Conv();
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // JR_NZ (mBillsPC_PressRight);
    if(hram->hJoyLast & D_RIGHT)
        return BillsPC_PressRight_Conv();
    // JR(mBillsPC_JoypadDidNothing);
    return BillsPC_JoypadDidNothing_Conv();
}

void MoveMonWithoutMail_DPad_2(void){
    LD_HL(hJoyLast);
    LD_A_addr(wBillsPC_NumMonsOnScreen);
    LD_D_A;
    LD_A_addr(wBillsPC_NumMonsInBox);
    LD_E_A;
    AND_A_A;
    IF_Z goto check_left_right;

    LD_A_hl;
    AND_A(D_UP);
    JR_NZ (mBillsPC_PressUp);
    LD_A_hl;
    AND_A(D_DOWN);
    JR_NZ (mBillsPC_PressDown);


check_left_right:
    LD_A_hl;
    AND_A(D_LEFT);
    JR_NZ (mBillsPC_PressLeft);
    LD_A_hl;
    AND_A(D_RIGHT);
    JR_NZ (mBillsPC_PressRight);
    JR(mBillsPC_JoypadDidNothing);

}

u8_flag_s MoveMonWithoutMail_DPad_2_Conv(void){
    // LD_HL(hJoyLast);
    // LD_A_addr(wBillsPC_NumMonsOnScreen);
    // LD_D_A;
    uint8_t d = wram->wBillsPC_NumMonsOnScreen;
    // LD_A_addr(wBillsPC_NumMonsInBox);
    // LD_E_A;
    uint8_t e = wram->wBillsPC_NumMonsInBox;
    // AND_A_A;
    // IF_Z goto check_left_right;
    if(e != 0) {
        // LD_A_hl;
        // AND_A(D_UP);
        // JR_NZ (mBillsPC_PressUp);
        if(hram->hJoyLast & D_UP)
            return BillsPC_PressUp_Conv();
        // LD_A_hl;
        // AND_A(D_DOWN);
        // JR_NZ (mBillsPC_PressDown);
        if(hram->hJoyLast & D_DOWN)
            return BillsPC_PressDown_Conv(d, e);
    }

// check_left_right:
    // LD_A_hl;
    // AND_A(D_LEFT);
    // JR_NZ (mBillsPC_PressLeft);
    if(hram->hJoyLast & D_LEFT)
        return BillsPC_PressLeft_Conv();
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // JR_NZ (mBillsPC_PressRight);
    if(hram->hJoyLast & D_RIGHT)
        return BillsPC_PressRight_Conv();
    // JR(mBillsPC_JoypadDidNothing);
    return BillsPC_JoypadDidNothing_Conv();

}

void BillsPC_PressUp(void){
    LD_HL(wBillsPC_CursorPosition);
    LD_A_hl;
    AND_A_A;
    IF_Z goto top;
    DEC_hl;
    JR(mBillsPC_UpDownDidSomething);


top:
    LD_HL(wBillsPC_ScrollPosition);
    LD_A_hl;
    AND_A_A;
    JR_Z (mBillsPC_JoypadDidNothing);
    DEC_hl;
    JR(mBillsPC_UpDownDidSomething);

}

u8_flag_s BillsPC_PressUp_Conv(void){
    // LD_HL(wBillsPC_CursorPosition);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto top;
    if(wram->wBillsPC_CursorPosition != 0) {
        // DEC_hl;
        // JR(mBillsPC_UpDownDidSomething);
        --wram->wBillsPC_CursorPosition;
        return BillsPC_UpDownDidSomething_Conv();
    }

// top:
    // LD_HL(wBillsPC_ScrollPosition);
    // LD_A_hl;
    // AND_A_A;
    // JR_Z (mBillsPC_JoypadDidNothing);
    if(wram->wBillsPC_ScrollPosition == 0)
        return BillsPC_JoypadDidNothing_Conv();
    // DEC_hl;
    // JR(mBillsPC_UpDownDidSomething);
    --wram->wBillsPC_ScrollPosition;
    return BillsPC_UpDownDidSomething_Conv();
}

void BillsPC_PressDown(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    INC_A;
    CP_A_E;
    JR_NC (mBillsPC_JoypadDidNothing);

    LD_HL(wBillsPC_CursorPosition);
    LD_A_hl;
    INC_A;
    CP_A_D;
    IF_NC goto not_bottom;
    INC_hl;
    JR(mBillsPC_UpDownDidSomething);


not_bottom:
    LD_HL(wBillsPC_ScrollPosition);
    INC_hl;
    JR(mBillsPC_UpDownDidSomething);

}

u8_flag_s BillsPC_PressDown_Conv(uint8_t d, uint8_t e){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // INC_A;
    // CP_A_E;
    // JR_NC (mBillsPC_JoypadDidNothing);
    if(wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition + 1 >= e)
        return BillsPC_JoypadDidNothing_Conv();

    // LD_HL(wBillsPC_CursorPosition);
    // LD_A_hl;
    // INC_A;
    // CP_A_D;
    // IF_NC goto not_bottom;
    if(wram->wBillsPC_CursorPosition + 1 < d) {
        // INC_hl;
        // JR(mBillsPC_UpDownDidSomething);
        wram->wBillsPC_CursorPosition++;
        return BillsPC_UpDownDidSomething_Conv();
    }

// not_bottom:
    // LD_HL(wBillsPC_ScrollPosition);
    // INC_hl;
    // JR(mBillsPC_UpDownDidSomething);
    wram->wBillsPC_ScrollPosition++;
    return BillsPC_UpDownDidSomething_Conv();
}

void BillsPC_PressLeft(void){
    LD_HL(wBillsPC_LoadedBox);
    LD_A_hl;
    AND_A_A;
    IF_Z goto wrap_around;
    DEC_hl;
    JR(mBillsPC_LeftRightDidSomething);


wrap_around:
    LD_hl(NUM_BOXES);
    JR(mBillsPC_LeftRightDidSomething);

}

u8_flag_s BillsPC_PressLeft_Conv(void){
    // LD_HL(wBillsPC_LoadedBox);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto wrap_around;
    if(wram->wBillsPC_LoadedBox != 0) {
        // DEC_hl;
        wram->wBillsPC_LoadedBox--;
        // JR(mBillsPC_LeftRightDidSomething);
        return BillsPC_LeftRightDidSomething_Conv();
    }


// wrap_around:
    // LD_hl(NUM_BOXES);
    wram->wBillsPC_LoadedBox = NUM_BOXES;
    // JR(mBillsPC_LeftRightDidSomething);
    return BillsPC_LeftRightDidSomething_Conv();

}

void BillsPC_PressRight(void){
    LD_HL(wBillsPC_LoadedBox);
    LD_A_hl;
    CP_A(NUM_BOXES);
    IF_Z goto wrap_around;
    INC_hl;
    JR(mBillsPC_LeftRightDidSomething);


wrap_around:
    LD_hl(0);
    JR(mBillsPC_LeftRightDidSomething);

}

u8_flag_s BillsPC_PressRight_Conv(void){
    // LD_HL(wBillsPC_LoadedBox);
    // LD_A_hl;
    // CP_A(NUM_BOXES);
    // IF_Z goto wrap_around;
    if(wram->wBillsPC_LoadedBox != NUM_BOXES) {
        // INC_hl;
        wram->wBillsPC_LoadedBox++;
        // JR(mBillsPC_LeftRightDidSomething);
        return BillsPC_LeftRightDidSomething_Conv();
    }

// wrap_around:
    // LD_hl(0);
    wram->wBillsPC_LoadedBox = 0;
    // JR(mBillsPC_LeftRightDidSomething);
    return BillsPC_LeftRightDidSomething_Conv();

}

void BillsPC_JoypadDidNothing(void){
    XOR_A_A;
    AND_A_A;
    RET;

}

u8_flag_s BillsPC_JoypadDidNothing_Conv(void){
    // XOR_A_A;
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

void BillsPC_UpDownDidSomething(void){
    LD_A(TRUE);
    AND_A_A;
    RET;

}

u8_flag_s BillsPC_UpDownDidSomething_Conv(void){
    // LD_A(TRUE);
    // AND_A_A;
    // RET;
    return u8_flag(TRUE, false);
}

void BillsPC_LeftRightDidSomething(void){
    SCF;
    RET;

}

u8_flag_s BillsPC_LeftRightDidSomething_Conv(void){
    // SCF;
    // RET;
    return u8_flag(0, true);
}

void BillsPC_PlaceString(void){
    PUSH_DE;
    hlcoord(0, 15, wTilemap);
    LD_BC((1 << 8) | 18);
    CALL(aTextbox);
    POP_DE;
    hlcoord(1, 16, wTilemap);
    CALL(aPlaceString);
    RET;

}

void BillsPC_PlaceString_Conv(uint8_t* de){
    // PUSH_DE;
    // hlcoord(0, 15, wTilemap);
    // LD_BC((1 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 15, wram->wTilemap), 1, 18);
    // POP_DE;
    // hlcoord(1, 16, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(de, coord(1, 16, wram->wTilemap));
    // RET;
}

void BillsPC_MoveMonWOMail_BoxNameAndArrows(void){
    // CALL(aBillsPC_BoxName);
    BillsPC_BoxName();
    // hlcoord(8, 1, wTilemap);
    // LD_hl(0x5f);
    *coord(8, 1, wram->wTilemap) = 0x5f;
    // hlcoord(19, 1, wTilemap);
    // LD_hl(0x5e);
    *coord(19, 1, wram->wTilemap) = 0x5e;
    // RET;
}

void BillsPC_BoxName(void){
    // hlcoord(8, 0, wTilemap);
    // LD_BC((1 << 8) | 10);
    // CALL(aTextbox);
    Textbox(coord(8, 0, wram->wTilemap), 1, 10);

    uint8_t* de;
    // LD_A_addr(wBillsPC_LoadedBox);
    // AND_A_A;
    // IF_Z goto party;
    if(wram->wBillsPC_LoadedBox != 0) {
        // CP_A(NUM_BOXES + 1);
        // IF_NZ goto gotbox;
        uint8_t box = wram->wBillsPC_LoadedBox;
        if(box == NUM_BOXES + 1) {
            // LD_A_addr(wCurBox);
            // INC_A;
            box = wram->wCurBox + 1;
        }
    // gotbox:
        // DEC_A;
        // LD_HL(wBoxNames);
        // LD_BC(BOX_NAME_LENGTH);
        // CALL(aAddNTimes);
        // LD_E_L;
        // LD_D_H;
        de = wram->wBoxNames + (BOX_NAME_LENGTH * (box - 1));
        // goto print;
    }
    else {
    // party:
        // LD_DE(mBillsPC_BoxName_PartyPKMN);
        de = U82C("PARTY <PK><MN>@");
    }
// print:
    // hlcoord(10, 1, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(de, coord(10, 1, wram->wTilemap));
    // RET;
}

//  Display a monster's pic and
//  attributes when highlighting
//  it in a PC menu.
//  Includes the neat cascading
//  effect when showing the pic.
//  Example: Species, level, gender,
//  whether it's holding an item.
void PCMonInfo(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC((15 << 8) | 8);
    // CALL(aClearBox);
    ClearBox(coord(0, 0, wram->wTilemap), 8, 15);

    // hlcoord(8, 14, wTilemap);
    // LD_BC((1 << 8) | 3);
    // CALL(aClearBox);
    ClearBox(coord(8, 14, wram->wTilemap), 3, 1);

    // CALL(aBillsPC_GetSelectedPokemonSpecies);
    species_t species = BillsPC_GetSelectedPokemonSpecies_Conv();
    // AND_A_A;
    // RET_Z ;
    // CP_A(-1);
    // RET_Z ;
    if(species == 0 || species == (species_t)-1)
        return;

    // LD_addr_A(wTempSpecies);
    wram->wTempSpecies = species;
    // hlcoord(1, 4, wTilemap);
    tile_t* hl = coord(1, 4, wram->wTilemap);
    // XOR_A_A;
    uint8_t a = 0;
    // LD_B(7);
    uint8_t b = 7;

    do {
    // row:
        // LD_C(7);
        uint8_t c = 7;
        // PUSH_AF;
        uint8_t a2 = a;
        // PUSH_HL;
        tile_t* hl2 = hl;

        do {
        // col:
            // LD_hli_A;
            *(hl2++) = a2;
            // ADD_A(7);
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
        a += 7;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);

    // CALL(aBillsPC_LoadMonStats);
    BillsPC_LoadMonStats_Conv();
    // LD_A_addr(wTempSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = species;
    // LD_addr_A(wCurSpecies);
    // LD_HL(wTempMonDVs);
    // PREDEF(pGetUnownLetter);
    GetUnownLetter(wram->wTempMon.mon.DVs);
    // CALL(aGetBaseData);
    GetBaseData(species);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // PREDEF(pGetMonFrontpic);
    GetMonFrontpic(vram->vTiles2 + LEN_2BPP_TILE * 0x00);
    // XOR_A_A;
    // LD_addr_A(wBillsPC_MonHasMail);
    wram->wBillsPC_MonHasMail = FALSE;
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wTempSpecies);
    wram->wTempSpecies = species;
    // CP_A(EGG);
    // RET_Z ;
    if(species == EGG)
        return;

    // CALL(aGetBasePokemonName);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(GetBasePokemonName(species), coord(1, 14, wram->wTilemap));

    // hlcoord(1, 12, wTilemap);
    // CALL(aPrintLevel);
    PrintLevel(coord(1, 12, wram->wTilemap), wram->wTempMon.mon.level);

    // LD_A(0x3);
    // LD_addr_A(wMonType);
    // FARCALL(aGetGender);
    u8_flag_s gender = GetGender_Conv(0x3);
    // IF_C goto skip_gender;
    if(!gender.flag) {
        // LD_A(0xef);
        // IF_NZ goto printgender;
        // LD_A(0xf5);

    // printgender:
        // hlcoord(5, 12, wTilemap);
        // LD_hl_A;
        *coord(5, 12, wram->wTilemap) = (gender.a != 0)? 0xef: 0xf5;
    }

// skip_gender:
    // LD_A_addr(wTempMonItem);
    // AND_A_A;
    // RET_Z ;
    if(wram->wTempMon.mon.item == NO_ITEM)
        return;

    // LD_D_A;
    // CALLFAR(aItemIsMail);
    // IF_C goto mail;
    tile_t icon;
    if(ItemIsMail_Conv(wram->wTempMon.mon.item)) {
    // mail:
        // LD_A(0x1);
        // LD_addr_A(wBillsPC_MonHasMail);
        wram->wBillsPC_MonHasMail = TRUE;
        // LD_A(0x5c);  // mail icon
        icon = 0x5c;
    }
    else {
        // LD_A(0x5d);  // item icon
        icon = 0x5d;
        // goto printitem;
    }

// printitem:
    // hlcoord(7, 12, wTilemap);
    // LD_hl_A;
    *coord(7, 12, wram->wTilemap) = icon;
    // RET;
}

void BillsPC_LoadMonStats(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_E_A;
    LD_D(0);
    LD_HL(wBillsPCPokemonList + 1);  // box number
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hl;
    AND_A_A;
    IF_Z goto party;
    CP_A(NUM_BOXES + 1);
    IF_Z goto sBox;
    LD_B_A;
    CALL(aGetBoxPointer);
    LD_A_B;
    CALL(aOpenSRAM);
    PUSH_HL;
    LD_BC(sBoxMon1Level - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonLevel);
    POP_HL;
    PUSH_HL;
    LD_BC(sBoxMon1Item - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonItem);
    POP_HL;
    LD_BC(sBoxMon1DVs - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wTempMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    CALL(aCloseSRAM);
    RET;


party:
    LD_HL(wPartyMon1Level);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonLevel);
    LD_HL(wPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonItem);
    LD_HL(wPartyMon1DVs);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wTempMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    RET;


sBox:
    LD_A(BANK(sBox));
    CALL(aOpenSRAM);
    LD_HL(sBoxMon1Level);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonLevel);

    LD_HL(sBoxMon1Item);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_A_hl;
    LD_addr_A(wTempMonItem);

    LD_HL(sBoxMon1DVs);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_E;
    CALL(aAddNTimes);
    LD_DE(wTempMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;

    CALL(aCloseSRAM);
    RET;

}

void BillsPC_LoadMonStats_Conv(void){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_E_A;
    uint8_t e = wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition;
    // LD_D(0);
    // LD_HL(wBillsPCPokemonList + 1);  // box number
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hl;
    uint8_t a = wram->wBillsPCPokemonList[e].boxNumber;
    // AND_A_A;
    // IF_Z goto party;
    if(a == 0){
    // party:
        // LD_HL(wPartyMon1Level);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_E;
        // CALL(aAddNTimes);
        struct PartyMon* bc = wram->wPartyMon + e;
        // LD_A_hl;
        // LD_addr_A(wTempMonLevel);
        wram->wTempMon.mon.level = bc->mon.level;
        // LD_HL(wPartyMon1Item);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_E;
        // CALL(aAddNTimes);
        // LD_A_hl;
        // LD_addr_A(wTempMonItem);
        wram->wTempMon.mon.item = bc->mon.item;
        // LD_HL(wPartyMon1DVs);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_E;
        // CALL(aAddNTimes);
        // LD_DE(wTempMonDVs);
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        // LD_A_hl;
        // LD_de_A;
        wram->wTempMon.mon.DVs = bc->mon.DVs;
        // RET;
        return;
    }
    // CP_A(NUM_BOXES + 1);
    // IF_Z goto sBox;
    if(a != NUM_BOXES + 1) {
        // LD_B_A;
        // CALL(aGetBoxPointer);
        uint32_t boxptr = GetBoxPointer_Conv(a);
        // LD_A_B;
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(boxptr));
        uint16_t ptr = (uint16_t)(boxptr & 0xffff);
        // PUSH_HL;
        // LD_BC(sBoxMon1Level - sBox);
        // ADD_HL_BC;
        // LD_BC(BOXMON_STRUCT_LENGTH);
        // LD_A_E;
        // CALL(aAddNTimes);
        // LD_A_hl;
        // LD_addr_A(wTempMonLevel);
        wram->wTempMon.mon.level = ((struct BoxMon*)GBToRAMAddr(ptr + (sBoxMon1 - sBox) + e * BOXMON_STRUCT_LENGTH))->level;
        // POP_HL;
        // PUSH_HL;
        // LD_BC(sBoxMon1Item - sBox);
        // ADD_HL_BC;
        // LD_BC(BOXMON_STRUCT_LENGTH);
        // LD_A_E;
        // CALL(aAddNTimes);
        // LD_A_hl;
        // LD_addr_A(wTempMonItem);
        wram->wTempMon.mon.item = ((struct BoxMon*)GBToRAMAddr(ptr + (sBoxMon1 - sBox) + e * BOXMON_STRUCT_LENGTH))->item;
        // POP_HL;
        // LD_BC(sBoxMon1DVs - sBox);
        // ADD_HL_BC;
        // LD_BC(BOXMON_STRUCT_LENGTH);
        // LD_A_E;
        // CALL(aAddNTimes);
        // LD_DE(wTempMonDVs);
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        // LD_A_hl;
        // LD_de_A;
        wram->wTempMon.mon.DVs = ((struct BoxMon*)GBToRAMAddr(ptr + (sBoxMon1 - sBox) + e * BOXMON_STRUCT_LENGTH))->DVs;
        // CALL(aCloseSRAM);
        CloseSRAM();
        // RET;
        return;
    }

// sBox:
    // LD_A(BANK(sBox));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBox));
    // LD_HL(sBoxMon1Level);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // LD_A_E;
    // CALL(aAddNTimes);
    // LD_A_hl;
    // LD_addr_A(wTempMonLevel);
    wram->wTempMon.mon.level = gb_read(sBoxMon1Level + e * BOXMON_STRUCT_LENGTH);

    // LD_HL(sBoxMon1Item);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // LD_A_E;
    // CALL(aAddNTimes);
    // LD_A_hl;
    // LD_addr_A(wTempMonItem);
    wram->wTempMon.mon.item = gb_read(sBoxMon1Item + e * BOXMON_STRUCT_LENGTH);

    // LD_HL(sBoxMon1DVs);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // LD_A_E;
    // CALL(aAddNTimes);
    // LD_DE(wTempMonDVs);
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // LD_A_hl;
    // LD_de_A;
    wram->wTempMon.mon.DVs = gb_read16(sBoxMon1DVs + e * BOXMON_STRUCT_LENGTH);

    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;

}

static void BillsPC_RefreshTextboxes_PlaceNickname(const struct BillsPCMonEntry* de, tile_t* hl) {
    static const char CancelString[] = "CANCEL@";
    static const char Placeholder[] = "-----@";
    // LD_A_de;
    // AND_A_A;
    // RET_Z ;
    if(de->species == 0)
        return;
    // CP_A(-1);
    // IF_NZ goto get_nickname;
    if(de->species == (species_t)-1) {
        // LD_DE(mBillsPC_RefreshTextboxes_CancelString);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(CancelString), hl);
        // RET;
        return;
    }

// get_nickname:
    // INC_DE;
    // LD_A_de;
    // LD_B_A;
    uint8_t b = de->boxNumber;
    // INC_DE;
    // LD_A_de;
    // LD_E_A;
    uint8_t e = de->listIndex;
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto party;
    if(b != 0) {
        // CP_A(NUM_BOXES + 1);
        // IF_Z goto sBox;
        if(b == NUM_BOXES + 1) {
        // sBox:
            // PUSH_HL;
            // LD_A(BANK(sBox));
            // CALL(aOpenSRAM);
            OpenSRAM(MBANK(asBox));
            // LD_HL(sBoxSpecies);
            // LD_D(0x0);
            // ADD_HL_DE;
            species_t* species = GBToRAMAddr(sBoxSpecies);
            // LD_A_hl;
            // AND_A_A;
            // IF_Z goto sBoxFail;
            if(species[e] != 0x0) {
                // LD_HL(sBoxMonNicknames);
                uint8_t (*nick)[MON_NAME_LENGTH] = GBToRAMAddr(sBoxMonNicknames);
                // LD_BC(MON_NAME_LENGTH);
                // LD_A_E;
                // CALL(aAddNTimes);
                // LD_DE(wStringBuffer1);
                // LD_BC(MON_NAME_LENGTH);
                // CALL(aCopyBytes);
                CopyBytes(wram->wStringBuffer1, nick[e], MON_NAME_LENGTH);
                // CALL(aCloseSRAM);
                CloseSRAM();
                // POP_HL;
                // LD_DE(wStringBuffer1);
                // CALL(aPlaceString);
                PlaceStringSimple(wram->wStringBuffer1, hl);
                // RET;
                return;
            }
            else {
            // sBoxFail:
                // CALL(aCloseSRAM);
                CloseSRAM();
                // POP_HL;
            }
        }
        else {
            // PUSH_HL;
            // CALL(aGetBoxPointer);
            uint32_t box = GetBoxPointer_Conv(b);
            // LD_A_B;
            // CALL(aOpenSRAM);
            OpenSRAM(MBANK(box));
            uint16_t ptr = (uint16_t)(box & 0xffff);
            // PUSH_HL;
            // LD_BC(sBoxMons - sBox);
            // ADD_HL_BC;
            struct BoxMon* mon = GBToRAMAddr(ptr + (sBoxMons - sBox));
            // LD_BC(BOXMON_STRUCT_LENGTH);
            // LD_A_E;
            // CALL(aAddNTimes);

            // LD_A_hl;
            // POP_HL;
            // AND_A_A;
            // IF_Z goto boxfail;
            if(mon[e].species != 0) {
                // LD_BC(sBoxMonNicknames - sBox);
                // ADD_HL_BC;
                // LD_BC(MON_NAME_LENGTH);
                // LD_A_E;
                // CALL(aAddNTimes);
                // LD_DE(wStringBuffer1);
                // LD_BC(MON_NAME_LENGTH);
                // CALL(aCopyBytes);
                CopyBytes(wram->wStringBuffer1, GBToRAMAddr(ptr + (sBoxMonNicknames - sBox) + (e * MON_NAME_LENGTH)), MON_NAME_LENGTH);
                // CALL(aCloseSRAM);
                CloseSRAM();
                // POP_HL;
                // LD_DE(wStringBuffer1);
                // CALL(aPlaceString);
                PlaceStringSimple(wram->wStringBuffer1, hl);

                // RET;
                return;
            }
            else {
            // boxfail:
                // CALL(aCloseSRAM);
                CloseSRAM();
                // POP_HL;
                // goto placeholder_string;
            }
        }
    }
    else {
    // party:
        // PUSH_HL;
        // LD_HL(wPartySpecies);
        // LD_D(0x0);
        // ADD_HL_DE;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto partyfail;
        if(wram->wPartySpecies[e] != 0x0) {
            // LD_HL(wPartyMonNicknames);
            // LD_BC(MON_NAME_LENGTH);
            // LD_A_E;
            // CALL(aAddNTimes);
            // LD_DE(wStringBuffer1);
            // LD_BC(MON_NAME_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes(wram->wStringBuffer1, wram->wPartyMonNickname[e], MON_NAME_LENGTH);
            // POP_HL;
            // LD_DE(wStringBuffer1);
            // CALL(aPlaceString);
            PlaceStringSimple(wram->wStringBuffer1, hl);
            // RET;
            return;
        }
    // partyfail:
        // POP_HL;
        // goto placeholder_string;
    }

// placeholder_string:
    // LD_DE(mBillsPC_RefreshTextboxes_Placeholder);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Placeholder), hl);
    // RET;
    return;
}

void BillsPC_RefreshTextboxes(void){
    // hlcoord(8, 2, wTilemap);
    // LD_BC((10 << 8) | 10);
    // CALL(aTextbox);
    Textbox(coord(8, 2, wram->wTilemap), 10, 10);

    // hlcoord(8, 2, wTilemap);
    // LD_hl(0x7d);
    *coord(8, 2, wram->wTilemap) = 0x7d;
    // hlcoord(19, 2, wTilemap);
    // LD_hl(0x7e);
    *coord(19, 2, wram->wTilemap) = 0x7e;

    // LD_A_addr(wBillsPC_ScrollPosition);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wBillsPCPokemonList);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    struct BillsPCMonEntry* de = wram->wBillsPCPokemonList + wram->wBillsPC_ScrollPosition;
    // hlcoord(9, 4, wTilemap);
    tile_t* hl = coord(9, 4, wram->wTilemap);
    // LD_A_addr(wBillsPC_NumMonsOnScreen);
    uint8_t num = wram->wBillsPC_NumMonsOnScreen;

    do {
    // loop:
        // PUSH_AF;
        // PUSH_DE;
        // PUSH_HL;
        // CALL(aBillsPC_RefreshTextboxes_PlaceNickname);
        BillsPC_RefreshTextboxes_PlaceNickname(de, hl);
        // POP_HL;
        // LD_DE(2 * SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // POP_DE;
        // INC_DE;
        // INC_DE;
        // INC_DE;
        de++;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--num != 0);
    // RET;
}

void CopyBoxmonSpecies(void){
    #define copy_box_data0 do { \
            while(1) {\
                if(*hl == (species_t)-1 || *hl == 0)\
                    break;\
                de->species = *hl;\
                de->boxNumber = wram->wBillsPC_LoadedBox;\
                de->listIndex = wram->wBillsPCTempListIndex++;\
                de++;\
                hl++;\
                wram->wBillsPCTempBoxCount++;\
            }\
            de->species = (species_t)-1;\
            wram->wBillsPC_NumMonsInBox = wram->wBillsPCTempBoxCount + 1;\
        } while(0)
    #define copy_box_data1 do { \
            while(1) {\
                if(*hl == (species_t)-1 || *hl == 0)\
                    break;\
                de->species = *hl;\
                de->boxNumber = wram->wBillsPC_LoadedBox;\
                de->listIndex = wram->wBillsPCTempListIndex++;\
                de++;\
                hl++;\
                wram->wBillsPCTempBoxCount++;\
            }\
            CloseSRAM();\
            de->species = (species_t)-1;\
            wram->wBillsPC_NumMonsInBox = wram->wBillsPCTempBoxCount + 1;\
        } while(0)
// copy_box_data: MACRO
// .loop\@
//     ld a, [hl]
//     cp -1
//     jr z, .done\@
//     and a
//     jr z, .done\@
//     ld [de], a ; species
//     inc de
//     ld a, [wBillsPC_LoadedBox]
//     ld [de], a ; box number
//     inc de
//     ld a, [wBillsPCTempListIndex]
//     ld [de], a ; list index
//     inc a
//     ld [wBillsPCTempListIndex], a
//     inc de
//     inc hl
//     ld a, [wBillsPCTempBoxCount]
//     inc a
//     ld [wBillsPCTempBoxCount], a
//     jr .loop\@

// .done\@
// if \1
//     call CloseSRAM
// endc
//     ld a, -1
//     ld [de], a
//     ld a, [wBillsPCTempBoxCount]
//     inc a
//     ld [wBillsPC_NumMonsInBox], a
// ENDM
    // XOR_A_A;
    // LD_HL(wBillsPCPokemonList);
    // LD_BC(3 * 30);
    // CALL(aByteFill);
    ByteFill(wram->wBillsPCPokemonList, sizeof(wram->wBillsPCPokemonList), 0);
    // LD_DE(wBillsPCPokemonList);
    struct BillsPCMonEntry* de = wram->wBillsPCPokemonList;
    // XOR_A_A;
    // LD_addr_A(wBillsPCTempListIndex);
    wram->wBillsPCTempListIndex = 0;
    // LD_addr_A(wBillsPCTempBoxCount);
    wram->wBillsPCTempBoxCount = 0;
    // LD_A_addr(wBillsPC_LoadedBox);
    // AND_A_A;
    // IF_Z goto party;
    if(wram->wBillsPC_LoadedBox == 0) {
    // party:
        // LD_HL(wPartySpecies);
        species_t* hl = wram->wPartySpecies;
        //copy_box_data ['0']
        copy_box_data0;
        // RET;
        return;
    }
    // CP_A(NUM_BOXES + 1);
    // IF_Z goto sBox;
    else if(wram->wBillsPC_LoadedBox == NUM_BOXES + 1) {
    // sBox:
        // LD_A(BANK(sBox));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asBox));
        // LD_HL(sBoxSpecies);
        species_t* hl = GBToRAMAddr(sBoxSpecies);
        //copy_box_data ['1']
        copy_box_data1;
        // RET;
        return;
    }
    // LD_B_A;
    // CALL(aGetBoxPointer);
    uint32_t boxptr = GetBoxPointer_Conv(wram->wBillsPC_LoadedBox);
    // LD_A_B;
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(boxptr));
    // INC_HL;
    uint8_t* hl = GBToRAMAddr((boxptr & 0xffff) + 1);
    //copy_box_data ['1']
    copy_box_data1;
    // RET;
}

void BillsPC_GetSelectedPokemonSpecies(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_E_A;
    LD_D(0);
    LD_HL(wBillsPCPokemonList);
    ADD_HL_DE;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hl;
    RET;

}

species_t BillsPC_GetSelectedPokemonSpecies_Conv(void){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wBillsPCPokemonList);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hl;
    // RET;
    return wram->wBillsPCPokemonList[wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition].species;
}

void BillsPC_UpdateSelectionCursor(void){
    static const uint8_t OAM[] = {
        dbsprite(10, 4, 0, 6, 0x00, 0),
        dbsprite(11, 4, 0, 6, 0x00, 0),
        dbsprite(12, 4, 0, 6, 0x00, 0),
        dbsprite(13, 4, 0, 6, 0x00, 0),
        dbsprite(14, 4, 0, 6, 0x00, 0),
        dbsprite(15, 4, 0, 6, 0x00, 0),
        dbsprite(16, 4, 0, 6, 0x00, 0),
        dbsprite(17, 4, 0, 6, 0x00, 0),
        dbsprite(18, 4, 0, 6, 0x00, 0),
        dbsprite(18, 4, 7, 6, 0x00, 0),
        dbsprite(10, 7, 0, 1, 0x00, 0 | Y_FLIP),
        dbsprite(11, 7, 0, 1, 0x00, 0 | Y_FLIP),
        dbsprite(12, 7, 0, 1, 0x00, 0 | Y_FLIP),
        dbsprite(13, 7, 0, 1, 0x00, 0 | Y_FLIP),
        dbsprite(14, 7, 0, 1, 0x00, 0 | Y_FLIP),
        dbsprite(15, 7, 0, 1, 0x00, 0 | Y_FLIP),
        dbsprite(16, 7, 0, 1, 0x00, 0 | Y_FLIP),
        dbsprite(17, 7, 0, 1, 0x00, 0 | Y_FLIP),
        dbsprite(18, 7, 0, 1, 0x00, 0 | Y_FLIP),
        dbsprite(18, 7, 7, 1, 0x00, 0 | Y_FLIP),
        dbsprite(9, 5, 6, 6, 0x01, 0),
        dbsprite(9, 6, 6, 1, 0x01, 0 | Y_FLIP),
        dbsprite(19, 5, 1, 6, 0x01, 0 | X_FLIP),
        dbsprite(19, 6, 1, 1, 0x01, 0 | X_FLIP | Y_FLIP),
        (uint8_t)-1,
    };
    // LD_A_addr(wBillsPC_NumMonsInBox);
    // AND_A_A;
    // IF_NZ goto place_cursor;
    if(wram->wBillsPC_NumMonsInBox == 0) {
        // CALL(aClearSprites);
        ClearSprites();
        // RET;
        return;
    }

// place_cursor:
    // LD_HL(mBillsPC_UpdateSelectionCursor_OAM);
    const uint8_t* hl = OAM;
    // LD_DE(wVirtualOAMSprite00);
    struct SpriteOAM* de = wram->wVirtualOAMSprite;

    while(*hl != 0xff) {
    // loop:
        // LD_A_hl;
        // CP_A(-1);
        // RET_Z ;
        // LD_A_addr(wBillsPC_CursorPosition);
        // AND_A(0x7);
        // SWAP_A;
        // ADD_A_hl;
        // INC_HL;
        // LD_de_A;  // y
        de->yCoord = ((wram->wBillsPC_CursorPosition & 0x7) << 4) + *(hl++);
        // INC_DE;
        de->xCoord = *(hl++);
        de->tileID = *(hl++);
        de->attributes = *(hl++);
        // for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        // }
        de++;
        // goto loop;
    }
}

void BillsPC_UpdateInsertCursor(void){
    static const uint8_t OAM[] = {
        dbsprite(10, 4, 0, 7, 0x06, 0),
        dbsprite(11, 5, 0, 3, 0x00, 0 | Y_FLIP),
        dbsprite(12, 5, 0, 3, 0x00, 0 | Y_FLIP),
        dbsprite(13, 5, 0, 3, 0x00, 0 | Y_FLIP),
        dbsprite(14, 5, 0, 3, 0x00, 0 | Y_FLIP),
        dbsprite(15, 5, 0, 3, 0x00, 0 | Y_FLIP),
        dbsprite(16, 5, 0, 3, 0x00, 0 | Y_FLIP),
        dbsprite(17, 5, 0, 3, 0x00, 0 | Y_FLIP),
        dbsprite(18, 5, 0, 3, 0x00, 0 | Y_FLIP),
        dbsprite(19, 4, 0, 7, 0x07, 0),
        (uint8_t)-1,
    };
    // LD_HL(mBillsPC_UpdateInsertCursor_OAM);
    const uint8_t* hl = OAM;
    // LD_DE(wVirtualOAMSprite00);
    struct SpriteOAM* de = wram->wVirtualOAMSprite;

    while(*hl != (uint8_t)-1){ 
    // loop:
        // LD_A_hl;
        // CP_A(-1);
        // RET_Z ;
        // LD_A_addr(wBillsPC_CursorPosition);
        // AND_A(0x7);
        // SWAP_A;
        // ADD_A_hl;
        // INC_HL;
        // LD_de_A;  // y
        de->yCoord = ((wram->wBillsPC_CursorPosition & 0x7) << 4) + *hl;
        hl++;
        // INC_DE;
        // for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH - 1; rept++){
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        // }
        de->xCoord = *(hl++);
        de->tileID = *(hl++);
        de->attributes = *(hl++);
        de++;
        // goto loop;
    }
}

void BillsPC_FillBox(void){
//  //  unreferenced

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

bool BillsPC_CheckSpaceInDestination(void){
//  If moving within a box, no need to be here.
    // LD_HL(wBillsPC_LoadedBox);
    // LD_A_addr(wBillsPC_BackupLoadedBox);
    // CP_A_hl;
    // IF_Z goto same_box;
    if(wram->wBillsPC_LoadedBox == wram->wBillsPC_BackupLoadedBox)
        return true;

//  Exceeding box or party capacity is a big no-no.
    // LD_A_addr(wBillsPC_LoadedBox);
    // AND_A_A;
    // IF_Z goto party;
    // LD_E(MONS_PER_BOX + 1);
    // goto compare;

// party:
    // LD_E(PARTY_LENGTH + 1);
    uint8_t e = (wram->wBillsPC_LoadedBox == 0)? PARTY_LENGTH + 1: MONS_PER_BOX + 1;

// compare:
    // LD_A_addr(wBillsPC_NumMonsInBox);
    // CP_A_E;
    // IF_NC goto no_room;
    if(wram->wBillsPC_NumMonsInBox >= e) {
    // no_room:
        // LD_DE(mPCString_TheresNoRoom);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_TheresNoRoom));
        // LD_DE(SFX_WRONG);
        // CALL(aWaitPlaySFX);
        WaitPlaySFX(SFX_WRONG);
        // CALL(aWaitSFX);
        WaitSFX();
        // LD_C(50);
        // CALL(aDelayFrames);
        DelayFrames(50);
        // SCF;
        // RET;
        return false;
    }

// same_box:
    // AND_A_A;
    // RET;
    return true;
}

void BillsPC_CheckMail_PreventBlackout(void){
    LD_A_addr(wBillsPC_LoadedBox);
    AND_A_A;
    IF_NZ goto Okay;
    LD_A_addr(wBillsPC_NumMonsInBox);
    CP_A(0x3);
    IF_C goto ItsYourLastPokemon;
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    FARCALL(aCheckCurPartyMonFainted);
    IF_C goto AllOthersFainted;
    LD_A_addr(wBillsPC_MonHasMail);
    AND_A_A;
    IF_NZ goto HasMail;

Okay:
    AND_A_A;
    RET;


HasMail:
    LD_DE(mPCString_RemoveMail);
    goto NotOkay;


AllOthersFainted:
    LD_DE(mPCString_NoMoreUsablePKMN);
    goto NotOkay;


ItsYourLastPokemon:
    LD_DE(mPCString_ItsYourLastPKMN);

NotOkay:
    CALL(aBillsPC_PlaceString);
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    LD_C(50);
    CALL(aDelayFrames);
    SCF;
    RET;

}

bool BillsPC_CheckMail_PreventBlackout_Conv(void){
    // LD_A_addr(wBillsPC_LoadedBox);
    // AND_A_A;
    // IF_NZ goto Okay;
    if(wram->wBillsPC_LoadedBox != 0)
        return false;
    // LD_A_addr(wBillsPC_NumMonsInBox);
    // CP_A(0x3);
    // IF_C goto ItsYourLastPokemon;
    uint8_t* de;
    if(wram->wBillsPC_NumMonsInBox < 0x3) {
    // ItsYourLastPokemon:
        // LD_DE(mPCString_ItsYourLastPKMN);
        de = U82C(PCString_ItsYourLastPKMN);
        goto NotOkay;
    }
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition;
    // FARCALL(aCheckCurPartyMonFainted);
    // IF_C goto AllOthersFainted;
    if(CheckCurPartyMonFainted_Conv()) {
    // AllOthersFainted:
        // LD_DE(mPCString_NoMoreUsablePKMN);
        de = U82C(PCString_NoMoreUsablePKMN);
        goto NotOkay;
    }
    // LD_A_addr(wBillsPC_MonHasMail);
    // AND_A_A;
    // IF_NZ goto HasMail;
    if(wram->wBillsPC_MonHasMail) {
    // HasMail:
        // LD_DE(mPCString_RemoveMail);
        de = U82C(PCString_RemoveMail);
        goto NotOkay;
    }

// Okay:
    // AND_A_A;
    // RET;
    return false;

NotOkay:
    // CALL(aBillsPC_PlaceString);
    BillsPC_PlaceString_Conv(de);
    // LD_DE(SFX_WRONG);
    // CALL(aWaitPlaySFX);
    WaitPlaySFX(SFX_WRONG);
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames(50);
    // SCF;
    // RET;
    return true;
}

void BillsPC_IsMonAnEgg(void){
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_Z goto egg;
    AND_A_A;
    RET;


egg:
    LD_DE(mPCString_NoReleasingEGGS);
    CALL(aBillsPC_PlaceString);
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    LD_C(50);
    CALL(aDelayFrames);
    SCF;
    RET;

}

bool BillsPC_IsMonAnEgg_Conv(void){
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto egg;
    if(wram->wCurPartySpecies != EGG) {
        // AND_A_A;
        // RET;
        return false;
    }

// egg:
    // LD_DE(mPCString_NoReleasingEGGS);
    // CALL(aBillsPC_PlaceString);
    BillsPC_PlaceString_Conv(U82C(PCString_NoReleasingEGGS));
    // LD_DE(SFX_WRONG);
    // CALL(aWaitPlaySFX);
    WaitPlaySFX(SFX_WRONG);
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames(50);
    // SCF;
    // RET;
    return true;
}

void BillsPC_StatsScreen(void){
    CALL(aLowVolume);
    CALL(aBillsPC_CopyMon);
    LD_A(TEMPMON);
    LD_addr_A(wMonType);
    PREDEF(pStatsScreenInit);
    CALL(aBillsPC_InitGFX);
    CALL(aMaxVolume);
    RET;

}

void BillsPC_StatsScreen_Conv(void){
    // CALL(aLowVolume);
    LowVolume();
    // CALL(aBillsPC_CopyMon);
    BillsPC_CopyMon_Conv();
    // LD_A(TEMPMON);
    // LD_addr_A(wMonType);
    wram->wMonType = TEMPMON;
    // PREDEF(pStatsScreenInit);
    StatsScreenInit();
    // CALL(aBillsPC_InitGFX);
    BillsPC_InitGFX();
    // CALL(aMaxVolume);
    MaxVolume();
    // RET;
}

void StatsScreenDPad(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(A_BUTTON | B_BUTTON | D_RIGHT | D_LEFT);
    LD_addr_A(wMenuJoypad);
    IF_NZ goto pressed_a_b_right_left;
    LD_A_hl;
    AND_A(D_DOWN | D_UP);
    LD_addr_A(wMenuJoypad);
    IF_NZ goto pressed_down_up;
    goto pressed_a_b_right_left;


pressed_down_up:
    CALL(av_StatsScreenDPad);
    AND_A_A;
    IF_Z goto did_nothing;
    CALL(aBillsPC_GetSelectedPokemonSpecies);
    LD_addr_A(wTempSpecies);
    CALL(aBillsPC_LoadMonStats);
    LD_A_addr(wTempSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    LD_HL(wTempMonDVs);
    PREDEF(pGetUnownLetter);
    CALL(aGetBaseData);
    CALL(aBillsPC_CopyMon);

pressed_a_b_right_left:
    RET;


did_nothing:
    XOR_A_A;
    LD_addr_A(wMenuJoypad);
    RET;

}

void StatsScreenDPad_Conv(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(A_BUTTON | B_BUTTON | D_RIGHT | D_LEFT);
    // LD_addr_A(wMenuJoypad);
    wram->wMenuJoypad = hram->hJoyPressed & (A_BUTTON | B_BUTTON | D_RIGHT | D_LEFT);
    // IF_NZ goto pressed_a_b_right_left;
    if(wram->wMenuJoypad != 0)
        return;
    // LD_A_hl;
    // AND_A(D_DOWN | D_UP);
    // LD_addr_A(wMenuJoypad);
    wram->wMenuJoypad = hram->hJoyPressed & (D_DOWN | D_UP);
    // IF_NZ goto pressed_down_up;
    if(wram->wMenuJoypad != 0) {
    // pressed_down_up:
        // CALL(av_StatsScreenDPad);
        // AND_A_A;
        // IF_Z goto did_nothing;
        if(v_StatsScreenDPad_Conv(&hram->hJoyPressed).a == 0) {
        // did_nothing:
            // XOR_A_A;
            // LD_addr_A(wMenuJoypad);
            wram->wMenuJoypad = NO_INPUT;
            // RET;
            return;
        }
        // CALL(aBillsPC_GetSelectedPokemonSpecies);
        // LD_addr_A(wTempSpecies);
        wram->wTempSpecies = BillsPC_GetSelectedPokemonSpecies_Conv();
        // CALL(aBillsPC_LoadMonStats);
        BillsPC_LoadMonStats_Conv();
        // LD_A_addr(wTempSpecies);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = wram->wTempSpecies;
        // LD_addr_A(wCurSpecies);
        wram->wCurSpecies = wram->wTempSpecies;
        // LD_HL(wTempMonDVs);
        // PREDEF(pGetUnownLetter);
        GetUnownLetter(wram->wTempMon.mon.DVs);
        // CALL(aGetBaseData);
        GetBaseData(wram->wCurSpecies);
        // CALL(aBillsPC_CopyMon);
        BillsPC_CopyMon_Conv();

    // pressed_a_b_right_left:
        // RET;
    }
    // goto pressed_a_b_right_left;
    return;
}

void BillsPC_CopyMon(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    LD_A_addr(wBillsPC_LoadedBox);
    AND_A_A;
    IF_Z goto party;
    CP_A(NUM_BOXES + 1);
    IF_NZ goto box;
    LD_A(BANK(sBox));
    CALL(aOpenSRAM);
    LD_HL(sBoxSpecies);
    CALL(aCopySpeciesToTemp);
    LD_HL(sBoxMonNicknames);
    CALL(aCopyNicknameToTemp);
    LD_HL(sBoxMonOTs);
    CALL(aCopyOTNameToTemp);
    LD_HL(sBoxMons);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMon);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    FARCALL(aCalcBufferMonStats);
    RET;


party:
    LD_HL(wPartySpecies);
    CALL(aCopySpeciesToTemp);
    LD_HL(wPartyMonNicknames);
    CALL(aCopyNicknameToTemp);
    LD_HL(wPartyMonOTs);
    CALL(aCopyOTNameToTemp);
    LD_HL(wPartyMon1);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMon);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    RET;


box:
    LD_B_A;
    CALL(aGetBoxPointer);
    LD_A_B;
    CALL(aOpenSRAM);
    PUSH_HL;
    INC_HL;
    CALL(aCopySpeciesToTemp);
    POP_HL;
    PUSH_HL;
    LD_BC(sBoxMonNicknames - sBox);
    ADD_HL_BC;
    CALL(aCopyNicknameToTemp);
    POP_HL;
    PUSH_HL;
    LD_BC(sBoxMonOTs - sBox);
    ADD_HL_BC;
    CALL(aCopyOTNameToTemp);
    POP_HL;
    LD_BC(sBoxMons - sBox);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aCopyMonToTemp);
    CALL(aCloseSRAM);
    FARCALL(aCalcBufferMonStats);
    RET;

}

void BillsPC_CopyMon_Conv(void){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition;
    // LD_A_addr(wBillsPC_LoadedBox);
    // AND_A_A;
    // IF_Z goto party;
    if(wram->wBillsPC_LoadedBox == 0) {
    // party:
        // LD_HL(wPartySpecies);
        // CALL(aCopySpeciesToTemp);
        CopySpeciesToTemp_Conv(wram->wPartySpecies);
        // LD_HL(wPartyMonNicknames);
        // CALL(aCopyNicknameToTemp);
        CopyNicknameToTemp_Conv(wram->wPartyMonNickname);
        // LD_HL(wPartyMonOTs);
        // CALL(aCopyOTNameToTemp);
        CopyOTNameToTemp_Conv(wram->wPartyMonOT);
        // LD_HL(wPartyMon1);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // LD_A_addr(wCurPartyMon);
        // CALL(aAddNTimes);
        // LD_DE(wBufferMon);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        // RET;
        return CopyBytes(&wram->wBufferMon, &wram->wPartyMon[wram->wCurPartyMon], sizeof(struct PartyMon));
    }
    // CP_A(NUM_BOXES + 1);
    // IF_NZ goto box;
    else if(wram->wBillsPC_LoadedBox == NUM_BOXES + 1) {
        // LD_A(BANK(sBox));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asBox));
        // LD_HL(sBoxSpecies);
        // CALL(aCopySpeciesToTemp);
        CopySpeciesToTemp_Conv((species_t*)GBToRAMAddr(sBoxSpecies));
        // LD_HL(sBoxMonNicknames);
        // CALL(aCopyNicknameToTemp);
        CopyNicknameToTemp_Conv((const uint8_t (*)[11])GBToRAMAddr(sBoxMonNicknames));
        // LD_HL(sBoxMonOTs);
        // CALL(aCopyOTNameToTemp);
        CopyOTNameToTemp_Conv((const uint8_t (*)[11])GBToRAMAddr(sBoxMonOTs));
        // LD_HL(sBoxMons);
        struct BoxMon* hl = (struct BoxMon*)GBToRAMAddr(sBoxMons);
        // LD_BC(BOXMON_STRUCT_LENGTH);
        // LD_A_addr(wCurPartyMon);
        // CALL(aAddNTimes);
        // LD_DE(wBufferMon);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(&wram->wBufferMon, hl + wram->wCurPartyMon, sizeof(struct PartyMon));
        // CALL(aCloseSRAM);
        CloseSRAM();
        // FARCALL(aCalcBufferMonStats);
        CalcBufferMonStats_Conv();
        // RET;
        return;
    }
    else {
    // box:
        // LD_B_A;
        // CALL(aGetBoxPointer);
        uint32_t ptr = GetBoxPointer_Conv(wram->wBillsPC_LoadedBox);
        // LD_A_B;
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(ptr));
        // PUSH_HL;
        // INC_HL;
        // CALL(aCopySpeciesToTemp);
        CopySpeciesToTemp_Conv((const uint8_t*)GBToRAMAddr((uint16_t)ptr + 1));
        // POP_HL;
        // PUSH_HL;
        // LD_BC(sBoxMonNicknames - sBox);
        // ADD_HL_BC;
        // CALL(aCopyNicknameToTemp);
        CopyNicknameToTemp_Conv((const uint8_t (*)[MON_NAME_LENGTH])GBToRAMAddr((uint16_t)ptr + (sBoxMonNicknames - sBox)));
        // POP_HL;
        // PUSH_HL;
        // LD_BC(sBoxMonOTs - sBox);
        // ADD_HL_BC;
        // CALL(aCopyOTNameToTemp);
        CopyOTNameToTemp_Conv((const uint8_t (*)[NAME_LENGTH])GBToRAMAddr((uint16_t)ptr + (sBoxMonOTs - sBox)));
        // POP_HL;
        // LD_BC(sBoxMons - sBox);
        // ADD_HL_BC;
        // LD_BC(BOXMON_STRUCT_LENGTH);
        // CALL(aCopyMonToTemp);
        CopyBoxMonToTemp_Conv((struct BoxMon*)GBToRAMAddr((uint16_t)ptr + (sBoxMons - sBox)));
        // CALL(aCloseSRAM);
        CloseSRAM();
        // FARCALL(aCalcBufferMonStats);
        CalcBufferMonStats_Conv();
        // RET;
        return;
    }
}

void DepositPokemon(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    LD_HL(wPartyMonNicknames);
    LD_A_addr(wCurPartyMon);
    CALL(aGetNickname);
    LD_A(PC_DEPOSIT);
    LD_addr_A(wPokemonWithdrawDepositParameter);
    PREDEF(pSendGetMonIntoFromBox);
    IF_C goto BoxFull;
    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    LD_A_addr(wCurPartySpecies);
    CALL(aPlayMonCry);
    hlcoord(0, 0, wTilemap);
    LD_BC((15 << 8) | 8);
    CALL(aClearBox);
    hlcoord(8, 14, wTilemap);
    LD_BC((1 << 8) | 3);
    CALL(aClearBox);
    hlcoord(0, 15, wTilemap);
    LD_BC((1 << 8) | 18);
    CALL(aTextbox);
    CALL(aWaitBGMap);
    hlcoord(1, 16, wTilemap);
    LD_DE(mPCString_Stored);
    CALL(aPlaceString);
    LD_L_C;
    LD_H_B;
    LD_DE(wStringBuffer1);
    CALL(aPlaceString);
    LD_A(0xe7);
    LD_bc_A;
    LD_C(50);
    CALL(aDelayFrames);
    AND_A_A;
    RET;


BoxFull:
    LD_DE(mPCString_BoxFull);
    CALL(aBillsPC_PlaceString);
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    LD_C(50);
    CALL(aDelayFrames);
    SCF;
    RET;

}

bool DepositPokemon_Conv(void){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition;
    // LD_HL(wPartyMonNicknames);
    // LD_A_addr(wCurPartyMon);
    // CALL(aGetNickname);
    GetNickname(wram->wPartyMonNickname[0], wram->wCurPartyMon);
    // LD_A(PC_DEPOSIT);
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // PREDEF(pSendGetMonIntoFromBox);
    // IF_C goto BoxFull;
    if(SendGetMonIntoFromBox_Conv(PC_DEPOSIT)) {
    // BoxFull:
        // LD_DE(mPCString_BoxFull);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_BoxFull));
        // LD_DE(SFX_WRONG);
        // CALL(aWaitPlaySFX);
        WaitPlaySFX(SFX_WRONG);
        // CALL(aWaitSFX);
        WaitSFX();
        // LD_C(50);
        // CALL(aDelayFrames);
        DelayFrames(50);
        // SCF;
        // RET;
        return true;
    }
    // XOR_A_A;  // REMOVE_PARTY
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // FARCALL(aRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox_Conv(REMOVE_PARTY);
    // LD_A_addr(wCurPartySpecies);
    // CALL(aPlayMonCry);
    PlayMonCry(wram->wCurPartySpecies);
    // hlcoord(0, 0, wTilemap);
    // LD_BC((15 << 8) | 8);
    // CALL(aClearBox);
    ClearBox(coord(0, 0, wram->wTilemap), 8, 15);
    // hlcoord(8, 14, wTilemap);
    // LD_BC((1 << 8) | 3);
    // CALL(aClearBox);
    ClearBox(coord(8, 14, wram->wTilemap), 3, 1);
    // hlcoord(0, 15, wTilemap);
    // LD_BC((1 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 15, wram->wTilemap), 1, 18);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mPCString_Stored);
    struct TextPrintState st = {.hl = coord(1, 16, wram->wTilemap), .de = U82C(PCString_Stored)};
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // LD_L_C;
    // LD_H_B;
    st.hl = st.bc;
    // LD_DE(wStringBuffer1);
    st.de = wram->wStringBuffer1;
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // LD_A(0xe7);
    // LD_bc_A;
    *st.bc = 0xe7;
    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames(50);
    // AND_A_A;
    // RET;
    return false;
}

void TryWithdrawPokemon(void){
    LD_A_addr(wBillsPC_CursorPosition);
    LD_HL(wBillsPC_ScrollPosition);
    ADD_A_hl;
    LD_addr_A(wCurPartyMon);
    LD_A(BANK(sBoxMonNicknames));
    CALL(aOpenSRAM);
    LD_A_addr(wCurPartyMon);
    LD_HL(sBoxMonNicknames);
    CALL(aGetNickname);
    CALL(aCloseSRAM);
    XOR_A_A;
    LD_addr_A(wPokemonWithdrawDepositParameter);
    PREDEF(pSendGetMonIntoFromBox);
    IF_C goto PartyFull;
    LD_A(REMOVE_BOX);
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    LD_A_addr(wCurPartySpecies);
    CALL(aPlayMonCry);
    hlcoord(0, 0, wTilemap);
    LD_BC((15 << 8) | 8);
    CALL(aClearBox);
    hlcoord(8, 14, wTilemap);
    LD_BC((1 << 8) | 3);
    CALL(aClearBox);
    hlcoord(0, 15, wTilemap);
    LD_BC((1 << 8) | 18);
    CALL(aTextbox);
    CALL(aWaitBGMap);
    hlcoord(1, 16, wTilemap);
    LD_DE(mPCString_Got);
    CALL(aPlaceString);
    LD_L_C;
    LD_H_B;
    LD_DE(wStringBuffer1);
    CALL(aPlaceString);
    LD_A(0xe7);
    LD_bc_A;
    LD_C(50);
    CALL(aDelayFrames);
    AND_A_A;
    RET;


PartyFull:
    LD_DE(mPCString_PartyFull);
    CALL(aBillsPC_PlaceString);
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    LD_C(50);
    CALL(aDelayFrames);
    SCF;
    RET;

}

bool TryWithdrawPokemon_Conv(void){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition;
    // LD_A(BANK(sBoxMonNicknames));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxMonNicknames));
    // LD_A_addr(wCurPartyMon);
    // LD_HL(sBoxMonNicknames);
    // CALL(aGetNickname);
    GetNickname((const uint8_t*)GBToRAMAddr(sBoxMonNicknames), wram->wCurPartyMon);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // XOR_A_A;
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // PREDEF(pSendGetMonIntoFromBox);
    // IF_C goto PartyFull;
    if(SendGetMonIntoFromBox_Conv(PC_WITHDRAW)) {
    // PartyFull:
        // LD_DE(mPCString_PartyFull);
        // CALL(aBillsPC_PlaceString);
        BillsPC_PlaceString_Conv(U82C(PCString_PartyFull));
        // LD_DE(SFX_WRONG);
        // CALL(aWaitPlaySFX);
        WaitPlaySFX(SFX_WRONG);
        // CALL(aWaitSFX);
        WaitSFX();
        // LD_C(50);
        // CALL(aDelayFrames);
        DelayFrames(50);
        // SCF;
        // RET;
        return true;
    }
    // LD_A(REMOVE_BOX);
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // FARCALL(aRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox_Conv(REMOVE_BOX);
    // LD_A_addr(wCurPartySpecies);
    // CALL(aPlayMonCry);
    PlayMonCry(wram->wCurPartySpecies);
    // hlcoord(0, 0, wTilemap);
    // LD_BC((15 << 8) | 8);
    // CALL(aClearBox);
    ClearBox(coord(0, 0, wram->wTilemap), 8, 15);
    // hlcoord(8, 14, wTilemap);
    // LD_BC((1 << 8) | 3);
    // CALL(aClearBox);
    ClearBox(coord(8, 14, wram->wTilemap), 3, 1);
    // hlcoord(0, 15, wTilemap);
    // LD_BC((1 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 15, wram->wTilemap), 1, 18);
    // CALL(aWaitBGMap);
    WaitBGMap();
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mPCString_Got);
    // CALL(aPlaceString);
    struct TextPrintState st = {.hl = coord(1, 16, wram->wTilemap), .de = U82C(PCString_Got)};
    PlaceString(&st, st.hl);
    // LD_L_C;
    // LD_H_B;
    st.hl = st.bc;
    // LD_DE(wStringBuffer1);
    st.de = wram->wStringBuffer1;
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // LD_A(0xe7);
    // LD_bc_A;
    *st.bc = 0xe7;
    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames(50);
    // AND_A_A;
    // RET;
    return false;
}

void ReleasePKMN_ByePKMN(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC((15 << 8) | 8);
    // CALL(aClearBox);
    ClearBox(coord(0, 0, wram->wTilemap), 8, 15);
    // hlcoord(8, 14, wTilemap);
    // LD_BC((1 << 8) | 3);
    // CALL(aClearBox);
    ClearBox(coord(8, 14, wram->wTilemap), 3, 1);
    // hlcoord(0, 15, wTilemap);
    // LD_BC((1 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 15, wram->wTilemap), 1, 18);

    // CALL(aWaitBGMap);
    WaitBGMap();
    // LD_A_addr(wCurPartySpecies);
    // CALL(aGetCryIndex);
    int16_t cry = GetCryIndex(wram->wCurPartySpecies);
    // IF_C goto skip_cry;
    if(cry >= 0) {
        // LD_E_C;
        // LD_D_B;
        // CALL(aPlayCry);
        PlayCry((uint16_t)cry);
    }

// skip_cry:
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wTempSpecies);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wCurPartySpecies);
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mPCString_ReleasedPKMN);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(PCString_ReleasedPKMN), coord(1, 16, wram->wTilemap));
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames(80);
    // hlcoord(0, 15, wTilemap);
    // LD_BC((1 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 15, wram->wTilemap), 1, 18);
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mPCString_Bye);
    struct TextPrintState st = {.hl = coord(1, 16, wram->wTilemap), .de = U82C(PCString_Bye)};
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // LD_L_C;
    // LD_H_B;
    st.hl = st.bc;
    // INC_HL;
    st.hl++;
    // LD_DE(wStringBuffer1);
    st.de = wram->wStringBuffer1;
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // LD_L_C;
    // LD_H_B;
    // LD_hl(0xe7);
    *st.bc = 0xe7;
    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames(50);
    // RET;

}

static void MovePKMNWitoutMail_InsertMon_CheckTrivialMove(void);
static void MovePKMNWitoutMail_InsertMon_CopyFromBox(void);
static void MovePKMNWitoutMail_InsertMon_CopyToBox(void);
static void MovePKMNWitoutMail_InsertMon_CopyFromParty(void);
static void MovePKMNWitoutMail_InsertMon_CopyToParty(void);

void MovePKMNWitoutMail_InsertMon(void){
    static const char Saving_LeaveOn[] = "Saving… Leave ON!@";
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // PUSH_AF;
    // hlcoord(0, 15, wTilemap);
    // LD_BC((1 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 15, wram->wTilemap), 1, 18);
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mMovePKMNWitoutMail_InsertMon_Saving_LeaveOn);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Saving_LeaveOn), coord(1, 16, wram->wTilemap));
    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames(20);
    // POP_AF;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // LD_A_addr(wCurBox);
    // PUSH_AF;
    uint8_t box = wram->wCurBox;
    // LD_BC(0);
    // LD_A_addr(wBillsPC_BackupLoadedBox);
    // AND_A_A;
    // IF_NZ goto moving_from_box;
    // SET_C(0);
    uint8_t c = (wram->wBillsPC_BackupLoadedBox != 0)? 0: 1;

// moving_from_box:
    // LD_A_addr(wBillsPC_LoadedBox);
    // AND_A_A;
    // IF_NZ goto moving_to_box;
    // SET_C(1);
    if(wram->wBillsPC_LoadedBox == 0)
       bit_set(c, 1);

// moving_to_box:
    // LD_HL(mMovePKMNWitoutMail_InsertMon_Jumptable);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(mMovePKMNWitoutMail_InsertMon_dw_return);
    // PUSH_DE;
    // JP_hl;
    switch(c) {
    // Jumptable:
        //dw ['.BoxToBox'];
    case 0:
    // BoxToBox:
        // LD_HL(wBillsPC_BackupLoadedBox);
        // LD_A_addr(wBillsPC_LoadedBox);
        // CP_A_hl;
        // IF_Z goto same_box;
        if(wram->wBillsPC_BackupLoadedBox == wram->wBillsPC_LoadedBox) {
        // same_box:
            // CALL(aMovePKMNWitoutMail_InsertMon_CopyFromBox);
            MovePKMNWitoutMail_InsertMon_CopyFromBox();
            // CALL(aMovePKMNWitoutMail_InsertMon_CheckTrivialMove);
            MovePKMNWitoutMail_InsertMon_CheckTrivialMove();
            // CALL(aMovePKMNWitoutMail_InsertMon_CopyToBox);
            MovePKMNWitoutMail_InsertMon_CopyToBox();
            // RET;
            break;
        }
        // CALL(aMovePKMNWitoutMail_InsertMon_CopyFromBox);
        MovePKMNWitoutMail_InsertMon_CopyFromBox();
        // CALL(aMovePKMNWitoutMail_InsertMon_CopyToBox);
        MovePKMNWitoutMail_InsertMon_CopyToBox();
        // RET;
        break;

        //dw ['.PartyToBox'];
    case 1:
    // PartyToBox:
        // CALL(aMovePKMNWitoutMail_InsertMon_CopyFromParty);
        MovePKMNWitoutMail_InsertMon_CopyFromParty();
        // LD_A(0x1);
        // LD_addr_A(wGameLogicPaused);
        wram->wGameLogicPaused = 0x1;
        // FARCALL(aSaveGameData);
        SaveGameData();
        // XOR_A_A;
        // LD_addr_A(wGameLogicPaused);
        wram->wGameLogicPaused = 0x0;
        // CALL(aMovePKMNWitoutMail_InsertMon_CopyToBox);
        MovePKMNWitoutMail_InsertMon_CopyToBox();
        // RET;
        break;

        //dw ['.BoxToParty'];
    case 2:
    // BoxToParty:
        // CALL(aMovePKMNWitoutMail_InsertMon_CopyFromBox);
        MovePKMNWitoutMail_InsertMon_CopyFromBox();
        // CALL(aMovePKMNWitoutMail_InsertMon_CopyToParty);
        MovePKMNWitoutMail_InsertMon_CopyToParty();
        // RET;
        break;

        //dw ['.PartyToParty'];
    case 3:
    // PartyToParty:
        // CALL(aMovePKMNWitoutMail_InsertMon_CopyFromParty);
        MovePKMNWitoutMail_InsertMon_CopyFromParty();
        // CALL(aMovePKMNWitoutMail_InsertMon_CheckTrivialMove);
        MovePKMNWitoutMail_InsertMon_CheckTrivialMove();
        // CALL(aMovePKMNWitoutMail_InsertMon_CopyToParty);
        MovePKMNWitoutMail_InsertMon_CopyToParty();
        // RET;
        break;
    }

// dw_return:
    // POP_AF;
    // LD_E_A;
    // FARCALL(aMoveMonWOMail_InsertMon_SaveGame);
    MoveMonWOMail_InsertMon_SaveGame(box);
    // RET;
    return;
}

static void MovePKMNWitoutMail_InsertMon_CheckTrivialMove(void){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_E_A;
    uint8_t pos = wram->wBillsPC_CursorPosition + wram->wBillsPC_ScrollPosition;
    // LD_A_addr(wBillsPC_BackupCursorPosition);
    // LD_HL(wBillsPC_BackupScrollPosition);
    // ADD_A_hl;
    uint8_t backupPos = wram->wBillsPC_BackupCursorPosition + wram->wBillsPC_BackupScrollPosition;
    // CP_A_E;
    // RET_NC ;
    if(backupPos >= pos)
        return;
    // LD_HL(wBillsPC_CursorPosition);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto top_of_screen;
    if(wram->wBillsPC_CursorPosition != 0) {
        // DEC_hl;
        wram->wBillsPC_CursorPosition--;
        // RET;
        return;
    }

// top_of_screen:
    // LD_HL(wBillsPC_ScrollPosition);
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(wram->wBillsPC_ScrollPosition != 0) {
        // DEC_hl;
        wram->wBillsPC_ScrollPosition--;
        // RET;
    }
}

static void MovePKMNWitoutMail_InsertMon_CopyFromBox(void){
    // LD_A_addr(wBillsPC_BackupLoadedBox);
    // DEC_A;
    // LD_E_A;
    // FARCALL(aMoveMonWOMail_SaveGame);
    MoveMonWOMail_SaveGame(wram->wBillsPC_BackupLoadedBox - 1);
    // LD_A_addr(wBillsPC_BackupCursorPosition);
    // LD_HL(wBillsPC_BackupScrollPosition);
    // ADD_A_hl;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wBillsPC_BackupScrollPosition + wram->wBillsPC_BackupCursorPosition;
    // LD_A(BANK(sBox));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBox));
    // LD_HL(sBoxSpecies);
    // CALL(aCopySpeciesToTemp);
    CopySpeciesToTemp_Conv(GBToRAMAddr(sBoxSpecies));
    // LD_HL(sBoxMonNicknames);
    // CALL(aCopyNicknameToTemp);
    CopyNicknameToTemp_Conv((const uint8_t (*)[11])GBToRAMAddr(sBoxMonNicknames));
    // LD_HL(sBoxMonOTs);
    // CALL(aCopyOTNameToTemp);
    CopyOTNameToTemp_Conv((const uint8_t (*)[11])GBToRAMAddr(sBoxMonOTs));
    // LD_HL(sBoxMons);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aCopyMonToTemp);
    CopyMonToTemp_Conv((struct PartyMon*)GBToRAMAddr(sBoxMons));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // FARCALL(aCalcBufferMonStats);
    CalcBufferMonStats_Conv();
    // LD_A(REMOVE_BOX);
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // FARCALL(aRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox_Conv(REMOVE_BOX);
    // RET;
}

static void MovePKMNWitoutMail_InsertMon_CopyToBox(void){
    // LD_A_addr(wBillsPC_LoadedBox);
    // DEC_A;
    // LD_E_A;
    // FARCALL(aMoveMonWOMail_SaveGame);
    MoveMonWOMail_SaveGame(wram->wBillsPC_LoadedBox - 1);
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wBillsPC_ScrollPosition + wram->wBillsPC_CursorPosition;
    // FARCALL(aInsertPokemonIntoBox);
    InsertPokemonIntoBox();
    // RET;
}

static void MovePKMNWitoutMail_InsertMon_CopyFromParty(void){
    // LD_A_addr(wBillsPC_BackupCursorPosition);
    // LD_HL(wBillsPC_BackupScrollPosition);
    // ADD_A_hl;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wBillsPC_BackupScrollPosition + wram->wBillsPC_BackupCursorPosition;
    // LD_HL(wPartySpecies);
    // CALL(aCopySpeciesToTemp);
    CopySpeciesToTemp_Conv(wram->wPartySpecies);
    // LD_HL(wPartyMonNicknames);
    // CALL(aCopyNicknameToTemp);
    CopyNicknameToTemp_Conv(wram->wPartyMonNickname);
    // LD_HL(wPartyMonOTs);
    // CALL(aCopyOTNameToTemp);
    CopyOTNameToTemp_Conv(wram->wPartyMonOT);
    // LD_HL(wPartyMon1Species);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aCopyMonToTemp);
    CopyMonToTemp_Conv(wram->wPartyMon);
    // XOR_A_A;  // REMOVE_PARTY
    // LD_addr_A(wPokemonWithdrawDepositParameter);
    // FARCALL(aRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox_Conv(REMOVE_PARTY);
    // RET;
}

static void MovePKMNWitoutMail_InsertMon_CopyToParty(void){
    // LD_A_addr(wBillsPC_CursorPosition);
    // LD_HL(wBillsPC_ScrollPosition);
    // ADD_A_hl;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wBillsPC_ScrollPosition + wram->wBillsPC_CursorPosition;
    // FARCALL(aInsertPokemonIntoParty);
    InsertPokemonIntoParty();
    // RET;
}

void CopySpeciesToTemp(void){
    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurPartySpecies);
    RET;

}

void CopySpeciesToTemp_Conv(const uint8_t* hl){
    // LD_A_addr(wCurPartyMon);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wCurPartySpecies);
    // RET;
    wram->wCurPartySpecies = hl[wram->wCurPartyMon];
}

void CopyNicknameToTemp(void){
    LD_BC(MON_NAME_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMonNickname);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    RET;

}

void CopyNicknameToTemp_Conv(const uint8_t (*hl)[MON_NAME_LENGTH]){
    // LD_BC(MON_NAME_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_DE(wBufferMonNickname);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    // RET;
    CopyBytes(wram->wBufferMonNickname, hl[wram->wCurPartyMon], MON_NAME_LENGTH);
}

void CopyOTNameToTemp(void){
    LD_BC(NAME_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMonOT);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    RET;

}

void CopyOTNameToTemp_Conv(const uint8_t (*hl)[NAME_LENGTH]){
    // LD_BC(NAME_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_DE(wBufferMonOT);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    // RET;
    CopyBytes(wram->wBufferMonOT, hl[wram->wCurPartyMon], NAME_LENGTH);
}

void CopyMonToTemp(void){
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wBufferMon);
    CALL(aCopyBytes);
    RET;

}

void CopyMonToTemp_Conv(const struct PartyMon* hl){
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_DE(wBufferMon);
    // CALL(aCopyBytes);
    // RET;
    CopyBytes(&wram->wBufferMon, hl + wram->wCurPartyMon, sizeof(*hl));
}

void CopyBoxMonToTemp_Conv(const struct BoxMon* hl){
    CopyBytes(&wram->wBufferMon.mon, hl + wram->wCurPartyMon, sizeof(*hl));
}

void GetBoxPointer(void){
    DEC_B;
    LD_C_B;
    LD_B(0);
    LD_HL(mGetBoxPointer_BoxBankAddresses);
    ADD_HL_BC;
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;


// BoxBankAddresses:
    //table_width ['3', 'GetBoxPointer.BoxBankAddresses']
    //dba ['sBox1']
    //dba ['sBox2']
    //dba ['sBox3']
    //dba ['sBox4']
    //dba ['sBox5']
    //dba ['sBox6']
    //dba ['sBox7']
    //dba ['sBox8']
    //dba ['sBox9']
    //dba ['sBox10']
    //dba ['sBox11']
    //dba ['sBox12']
    //dba ['sBox13']
    //dba ['sBox14']
    //assert_table_length ['NUM_BOXES']
}

uint32_t GetBoxPointer_Conv(uint8_t b){
    static uint32_t BoxBankAddresses[] = {
    //table_width ['3', 'GetBoxPointer.BoxBankAddresses']
        asBox1,
        asBox2,
        asBox3,
        asBox4,
        asBox5,
        asBox6,
        asBox7,
        asBox8,
        asBox9,
        asBox10,
        asBox11,
        asBox12,
        asBox13,
        asBox14,
    };
    static_assert(lengthof(BoxBankAddresses) == NUM_BOXES, "");
    // DEC_B;
    // LD_C_B;
    // LD_B(0);
    // LD_HL(mGetBoxPointer_BoxBankAddresses);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // RET;
    return BoxBankAddresses[b - 1];
}

void BillsPC_ApplyPalettes(uint8_t a){
    // LD_B_A;
    // CALL(aGetSGBLayout);
    GetSGBLayout(a);
    // LD_A(0b11100100);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals(0b11100100);
    // LD_A(0b11111100);
    // CALL(aDmgToCgbObjPal0);
    DmgToCgbObjPal0(0b11111100);
    // RET;
}

void BillsPC_Jumptable(void){
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;

}

void BillsPC_InitGFX(void){
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x00);
    // LD_BC(0x31 * LEN_2BPP_TILE);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(vram->vTiles2 + LEN_2BPP_TILE * 0x00, 0x31 * LEN_2BPP_TILE, 0x0);
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra();
    // LD_HL(mPCMailGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x5c);
    // LD_BC(4 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x5c, PCMailGFX, 0, 4);
    // LD_HL(mPCSelectLZ);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, PCSelectLZ);
    // LD_A(6);
    // CALL(aSkipMusic);
    SkipMusic(3);
    // CALL(aEnableLCD);
    EnableLCD();
    // RET;
}

const char PCSelectLZ[] = "gfx/pc/pc.png";
const char PCMailGFX[] = "gfx/pc/pc_mail.png";

const char PCString_ChooseaPKMN[] = "Choose a <PK><MN>.@";
const char PCString_WhatsUp[] = "What's up?@";
const char PCString_ReleasePKMN[] = "Release <PK><MN>?@";
const char PCString_MoveToWhere[] = "Move to where?@";
const char PCString_ItsYourLastPKMN[] = "It's your last <PK><MN>!@";
const char PCString_TheresNoRoom[] = "There's no room!@";
const char PCString_NoMoreUsablePKMN[] = "No more usable <PK><MN>!@";
const char PCString_RemoveMail[] = "Remove MAIL.@";
const char PCString_ReleasedPKMN[] = "Released <PK><MN>.@";
const char PCString_Bye[] = "Bye,@";
const char PCString_Stored[] = "Stored @";
const char PCString_Got[] = "Got @";

void PCString_Non(void){
//db "Non.@"   //  unreferenced
}

const char PCString_BoxFull[] = "The BOX is full.@";
const char PCString_PartyFull[] = "The party's full!@";
const char PCString_NoReleasingEGGS[] = "No releasing EGGS!@";

void v_ChangeBox(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // CALL(aBillsPC_ClearTilemap);
    BillsPC_ClearTilemap();

    while(1) {
    // loop:
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aBillsPC_PrintBoxName);
        BillsPC_PrintBoxName();
        // CALL(aBillsPC_PlaceChooseABoxString);
        BillsPC_PlaceChooseABoxString();
        // LD_HL(mv_ChangeBox_MenuHeader);
        // CALL(aCopyMenuHeader);
        CopyMenuHeader(&v_ChangeBox_MenuHeader);
        // XOR_A_A;
        // LD_addr_A(wMenuScrollPosition);
        wram->wMenuScrollPosition = 0;
        // hlcoord(0, 4, wTilemap);
        // LD_BC((8 << 8) | 9);
        // CALL(aTextbox);
        Textbox(coord(0, 4, wram->wTilemap), 8, 9);
        // CALL(aScrollingMenu);
        uint8_t joypad = ScrollingMenu();
        // LD_A_addr(wMenuJoypad);
        // CP_A(B_BUTTON);
        // IF_Z goto done;
        if(joypad == B_BUTTON)
            break;
        // CALL(aBillsPC_PlaceWhatsUpString);
        BillsPC_PlaceWhatsUpString();
        // CALL(aBillsPC_ChangeBoxSubmenu);
        BillsPC_ChangeBoxSubmenu();
        // goto loop;
    }

// done:
    // CALL(aCloseWindow);
    CloseWindow();
    // RET;
}

void BillsPC_ClearTilemap(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // RET;
}

static const uint8_t v_ChangeBox_MenuHeader_Boxes[] = {
    NUM_BOXES,
    // for(int x = 0; x < NUM_BOXES; x++){
    //db ['x + 1'];
    // }
    1,2,3,4,5,6,7,8,9,10,11,12,13,14,
    (uint8_t)-1,
};

static void v_ChangeBox_MenuHeader_PrintBoxNames(const struct MenuData* data, tile_t* hl) {
    (void)data;
    // PUSH_DE;
    // LD_A_addr(wMenuSelection);
    // DEC_A;
    // CALL(aGetBoxName);
    // POP_HL;
    // CALL(aPlaceString);
    PlaceStringSimple(GetBoxName_Conv(wram->wMenuSelection - 1), hl);
    // RET;
}

const struct MenuHeader v_ChangeBox_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(1, 5, 9, 12),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = SCROLLINGMENU_CALL_FUNCTION3_NO_SWITCH | SCROLLINGMENU_ENABLE_FUNCTION3,  // flags
        .scrollingMenu = {
            .rows = 4, .cols = 0,  // rows, columns
            .format = SCROLLINGMENU_ITEMS_NORMAL,  // item format
            .list = (uint8_t*)v_ChangeBox_MenuHeader_Boxes,
            //dba ['.PrintBoxNames']
            .func1 = v_ChangeBox_MenuHeader_PrintBoxNames,
            //dba ['NULL']
            .func2 = NULL,
            //dba ['BillsPC_PrintBoxCountAndCapacity']
            .func3 = BillsPC_PrintBoxCountAndCapacity,
        },
    },
    .defaultOption = 1,  // default option

};

void GetBoxName(void){
    LD_BC(BOX_NAME_LENGTH);
    LD_HL(wBoxNames);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    RET;

}

uint8_t* GetBoxName_Conv(uint8_t a){
    // LD_BC(BOX_NAME_LENGTH);
    // LD_HL(wBoxNames);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // RET;
    return wram->wBoxNames + (BOX_NAME_LENGTH * a);
}

void BillsPC_PrintBoxCountAndCapacity(void){
    static const char Pokemon[] = "#MON@";
    static const char OutOf20[] = "/" _s(MONS_PER_BOX) "@";  // "/20@"
    // hlcoord(11, 7, wTilemap);
    // LD_BC((5 << 8) | 7);
    // CALL(aTextbox);
    Textbox(coord(11, 7, wram->wTilemap), 5, 7);
    // LD_A_addr(wMenuSelection);
    // CP_A(-1);
    // RET_Z ;
    if(wram->wMenuSelection == (uint8_t)-1)
        return;
    // hlcoord(12, 9, wTilemap);
    // LD_DE(mBillsPC_PrintBoxCountAndCapacity_Pokemon);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Pokemon), coord(12, 9, wram->wTilemap));
    // CALL(aGetBoxCount);
    // LD_addr_A(wTextDecimalByte);
    uint8_t count = GetBoxCount();
    // hlcoord(13, 11, wTilemap);
    // LD_DE(wTextDecimalByte);
    // LD_BC((1 << 8) | 2);
    // CALL(aPrintNum);
    uint8_t* hl = PrintNum(coord(13, 11, wram->wTilemap), &count, 1, 2);
    // LD_DE(mBillsPC_PrintBoxCountAndCapacity_OutOf20);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(OutOf20), hl);
    // RET;
}

uint8_t GetBoxCount(void){
    static const uint32_t BoxBankAddresses[] = {
        //table_width ['3', 'GetBoxCount.BoxBankAddresses']
        asBox1,
        asBox2,
        asBox3,
        asBox4,
        asBox5,
        asBox6,
        asBox7,
        asBox8,
        asBox9,
        asBox10,
        asBox11,
        asBox12,
        asBox13,
        asBox14,
    };
    static_assert(lengthof(BoxBankAddresses) == NUM_BOXES, "");
    // LD_A_addr(wCurBox);
    // LD_C_A;
    // LD_A_addr(wMenuSelection);
    // DEC_A;
    // CP_A_C;
    uint8_t sel = wram->wMenuSelection - 1;
    // IF_Z goto activebox;
    if(sel == wram->wCurBox) {
    // activebox:
        // LD_A(BANK(sBoxCount));
        // LD_B_A;
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asBoxCount));
        // LD_HL(sBoxCount);
        // LD_A_hl;
        uint8_t count = gb_read(sBoxCount);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // RET;
        return count;
    }
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mGetBoxCount_BoxBankAddresses);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // ADD_HL_BC;
    uint32_t boxAddress = BoxBankAddresses[sel];
    // LD_A_hli;
    // LD_B_A;
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(boxAddress));
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_hl;
    uint8_t count = gb_read(boxAddress & 0xffff);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_C_A;
    // LD_A_addr(wSavedAtLeastOnce);
    // AND_A_A;
    // IF_Z goto newfile;
    if(wram->wSavedAtLeastOnce == 0) {
    // newfile:
        // XOR_A_A;
        // RET;
        return 0;
    }
    // LD_A_C;
    // RET;
    return count;
}

void BillsPC_PrintBoxName(void){
    static const char Current[] = "CURRENT@";
    // hlcoord(0, 0, wTilemap);
    // LD_B(2);
    // LD_C(18);
    // CALL(aTextbox);
    Textbox(coord(0, 0, wram->wTilemap), 2, 18);
    // hlcoord(1, 2, wTilemap);
    // LD_DE(mBillsPC_PrintBoxName_Current);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Current), coord(1, 2, wram->wTilemap));
    // LD_A_addr(wCurBox);
    // AND_A(0xf);
    // CALL(aGetBoxName);
    // hlcoord(11, 2, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(GetBoxName_Conv(wram->wCurBox & 0xf), coord(11, 2, wram->wTilemap));
    // RET;
}

static const struct MenuHeader BillsPC_ChangeBoxSubmenu_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(11, 4, SCREEN_WIDTH - 1, 13),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR,  // flags
        .verticalMenu = {
            .count = 4,  // items
            .options = (const char*[]) {
                "SWITCH@",
                "NAME@",
                "PRINT@",
                "QUIT@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

void BillsPC_ChangeBoxSubmenu(void){
    // LD_HL(mBillsPC_ChangeBoxSubmenu_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&BillsPC_ChangeBoxSubmenu_MenuHeader);
    // CALL(aVerticalMenu);
    bool cancel = VerticalMenu();
    // CALL(aExitMenu);
    ExitMenu();
    // RET_C ;
    if(cancel)
        return;
    // LD_A_addr(wMenuCursorY);
    switch(wram->wMenuCursorY) {
    // CP_A(0x1);
    // IF_Z goto Switch;
    case 0x1:
    // Switch:
        // LD_A_addr(wMenuSelection);
        // DEC_A;
        // LD_E_A;
        // LD_A_addr(wCurBox);
        // CP_A_E;
        // RET_Z ;
        if(wram->wMenuSelection - 1 == wram->wCurBox)
            return;
        // FARCALL(aChangeBoxSaveGame);
        ChangeBoxSaveGame(wram->wMenuSelection - 1);
        // RET;
        return;
    // CP_A(0x2);
    // IF_Z goto Name;
    case 0x2: {
    // Name:
        // LD_B(NAME_BOX);
        // LD_DE(wBoxNameBuffer);
        // FARCALL(aNamingScreen);
        NamingScreen(wram->wBoxNameBuffer, NAME_BOX);
        // CALL(aClearTilemap);
        ClearTilemap();
        // CALL(aLoadStandardFont);
        LoadStandardFont();
        // CALL(aLoadFontsBattleExtra);
        LoadFontsBattleExtra();
        // LD_A_addr(wMenuSelection);
        // DEC_A;
        // CALL(aGetBoxName);
        // LD_E_L;
        // LD_D_H;
        // LD_HL(wBoxNameBuffer);
        // LD_C(BOX_NAME_LENGTH - 1);
        // CALL(aInitString);
        InitString(wram->wBoxNameBuffer, GetBoxName_Conv(wram->wMenuSelection - 1), BOX_NAME_LENGTH - 1);
        // LD_A_addr(wMenuSelection);
        // DEC_A;
        // CALL(aGetBoxName);
        // LD_DE(wBoxNameBuffer);
        // CALL(aCopyName2);
        CopyName2(GetBoxName_Conv(wram->wMenuSelection - 1), wram->wBoxNameBuffer);
        // RET;
    } return;
    // CP_A(0x3);
    // IF_Z goto Print;
    case 0x3: {
    // Print:
        // CALL(aGetBoxCount);
        // AND_A_A;
        // IF_Z goto EmptyBox;
        if(GetBoxCount() == 0) {
        // EmptyBox:
            // CALL(aBillsPC_PlaceEmptyBoxString_SFX);
            BillsPC_PlaceEmptyBoxString_SFX();
            // AND_A_A;
            // RET;
            return;
        }
        // LD_E_L;
        // LD_D_H;
        uint32_t de = GetBoxPointer_Conv(wram->wMenuSelection);
        // LD_A_addr(wMenuSelection);
        // DEC_A;
        // LD_C_A;
        // FARCALL(aPrintPCBox);
        PrintPCBox(de, wram->wMenuSelection - 1);
        // CALL(aBillsPC_ClearTilemap);
        BillsPC_ClearTilemap();
        // AND_A_A;
        // RET;
    } return;
    default:
        // AND_A_A;
        // RET;
        return;
    }

    // hlcoord(11, 7, wTilemap);  // unreferenced
}

void BillsPC_PlaceChooseABoxString(void){
    static const char ChooseABox[] = "Choose a BOX.@";
    // LD_DE(mBillsPC_PlaceChooseABoxString_ChooseABox);
    // JR(mBillsPC_PlaceChangeBoxString);
    return BillsPC_PlaceChangeBoxString_Conv(U82C(ChooseABox));
}

void BillsPC_PlaceWhatsUpString(void){
    static const char WhatsUp[] = "What\'s up?@";
    // LD_DE(mBillsPC_PlaceWhatsUpString_WhatsUp);
    // JR(mBillsPC_PlaceChangeBoxString);
    return BillsPC_PlaceChangeBoxString_Conv(U82C(WhatsUp));
}

void BillsPC_PlaceEmptyBoxString_SFX(void){
    static const char NoMonString[] = "There\'s no #MON.@";
    // LD_DE(mBillsPC_PlaceEmptyBoxString_SFX_NoMonString);
    // CALL(aBillsPC_PlaceChangeBoxString);
    BillsPC_PlaceChangeBoxString_Conv(U82C(NoMonString));
    // LD_DE(SFX_WRONG);
    // CALL(aWaitPlaySFX);
    WaitPlaySFX(SFX_WRONG);
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames(50);
    // RET;
}

void BillsPC_PlaceChangeBoxString(void){
    PUSH_DE;
    hlcoord(0, 14, wTilemap);
    LD_BC((2 << 8) | 18);
    CALL(aTextbox);
    POP_DE;
    hlcoord(1, 16, wTilemap);
    CALL(aPlaceString);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;

}

void BillsPC_PlaceChangeBoxString_Conv(uint8_t* de){
    // PUSH_DE;
    // hlcoord(0, 14, wTilemap);
    // LD_BC((2 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 14, wram->wTilemap), 2, 18);
    // POP_DE;
    // hlcoord(1, 16, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(de, coord(1, 16, wram->wTilemap));
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;

}
