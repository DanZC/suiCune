#include "../../constants.h"
#include "pack.h"
#include "pack_kris.h"
#include "update_item_description.h"
#include "../menus/menu_2.h"
#include "../events/catch_tutorial_input.h"
#include "../../home/audio.h"
#include "../../home/copy.h"
#include "../../home/joypad.h"
#include "../../home/delay.h"
#include "../../home/tilemap.h"
#include "../../home/text.h"
#include "../../home/clear_sprites.h"
#include "../../home/lcd.h"
#include "../../home/menu.h"
#include "../../home/scrolling_menu.h"
#include "../../data/text/common.h"

//  Pack.Jumptable and BattlePack.Jumptable indexes
enum {
    PACKSTATE_INITGFX,  //  0
    PACKSTATE_INITITEMSPOCKET,  //  1
    PACKSTATE_ITEMSPOCKETMENU,  //  2
    PACKSTATE_INITBALLSPOCKET,  //  3
    PACKSTATE_BALLSPOCKETMENU,  //  4
    PACKSTATE_INITKEYITEMSPOCKET,  //  5
    PACKSTATE_KEYITEMSPOCKETMENU,  //  6
    PACKSTATE_INITTMHMPOCKET,  //  7
    PACKSTATE_TMHMPOCKETMENU,  //  8
    PACKSTATE_QUITNOSCRIPT,  //  9
    PACKSTATE_QUITRUNSCRIPT,  // 10
};

void Pack(void){
    // LD_HL(wOptions);
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aInitPackBuffers);
    InitPackBuffers();

    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto done;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(aPack_RunJumptable);
        Pack_RunJumptable();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }


// done:
    // LD_A_addr(wCurPocket);
    // LD_addr_A(wLastPocket);
    wram->wLastPocket = wram->wCurPocket;
    // LD_HL(wOptions);
    // RES_hl(NO_TEXT_SCROLL);
    bit_reset(wram->wOptions, NO_TEXT_SCROLL);
    // RET;
    return;
}

void Pack_RunJumptable(void) {
    // LD_A_addr(wJumptableIndex);
    // LD_HL(mPack_Jumptable);
    // CALL(aPack_GetJumptablePointer);
    // JP_hl;

    switch(wram->wJumptableIndex) {
    // Jumptable:
    //  entries correspond to PACKSTATE_* constants
        //dw ['.InitGFX'];  //  0
        case PACKSTATE_INITGFX:
        // InitGFX:
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = 0;
            // CALL(aPack_InitGFX);
            Pack_InitGFX();
            // LD_A_addr(wPackJumptableIndex);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = wram->wPackJumptableIndex;
            // CALL(aPack_InitColors);
            Pack_InitColors();
            // RET;
            return;
        //dw ['.InitItemsPocket'];  //  1
        case PACKSTATE_INITITEMSPOCKET:
        // InitItemsPocket:
            // XOR_A_A;  // ITEM_POCKET
            // LD_addr_A(wCurPocket);
            wram->wCurPocket = ITEM_POCKET;
            // CALL(aClearPocketList);
            ClearPocketList();
            // CALL(aDrawPocketName);
            DrawPocketName(wram->wCurPocket);
            // CALL(aWaitBGMap_DrawPackGFX);
            WaitBGMap_DrawPackGFX();
            // CALL(aPack_JumptableNext);
            Pack_JumptableNext();
            // RET;
            return;
        //dw ['.ItemsPocketMenu'];  //  2
        case PACKSTATE_ITEMSPOCKETMENU:
        // ItemsPocketMenu:
            // LD_HL(mItemsPocketMenuHeader);
            // CALL(aCopyMenuHeader);
            CopyMenuHeader_Conv2(&ItemsPocketMenuHeader);
            // LD_A_addr(wItemsPocketCursor);
            // LD_addr_A(wMenuCursorPosition);
            wram->wMenuCursorPosition = wram->wItemsPocketCursor;
            // LD_A_addr(wItemsPocketScrollPosition);
            // LD_addr_A(wMenuScrollPosition);
            wram->wMenuScrollPosition = wram->wItemsPocketScrollPosition;
            // CALL(aScrollingMenu);
            ScrollingMenu_Conv();
            // LD_A_addr(wMenuScrollPosition);
            // LD_addr_A(wItemsPocketScrollPosition);
            wram->wItemsPocketScrollPosition = wram->wMenuScrollPosition;
            // LD_A_addr(wMenuCursorY);
            // LD_addr_A(wItemsPocketCursor);
            wram->wItemsPocketCursor = wram->wMenuCursorY;
            // LD_B(PACKSTATE_INITTMHMPOCKET);  // left
            // LD_C(PACKSTATE_INITBALLSPOCKET);  // right
            // CALL(aPack_InterpretJoypad);
            // RET_C ;
            if(Pack_InterpretJoypad_Conv(PACKSTATE_INITTMHMPOCKET, PACKSTATE_INITBALLSPOCKET))
                return;
            // CALL(aPack_ItemBallsKey_LoadSubmenu);
            SafeCallGBAuto(aPack_ItemBallsKey_LoadSubmenu);
            // RET;
            return;
        //dw ['.InitBallsPocket'];  //  3
        case PACKSTATE_INITBALLSPOCKET:
        // InitBallsPocket:
            // LD_A(BALL_POCKET);
            // LD_addr_A(wCurPocket);
            wram->wCurPocket = BALL_POCKET;
            // CALL(aClearPocketList);
            ClearPocketList();
            // CALL(aDrawPocketName);
            DrawPocketName(BALL_POCKET);
            // CALL(aWaitBGMap_DrawPackGFX);
            WaitBGMap_DrawPackGFX();
            // CALL(aPack_JumptableNext);
            Pack_JumptableNext();
            // RET;
            return;
        //dw ['.BallsPocketMenu'];  //  4
        case PACKSTATE_BALLSPOCKETMENU:
        // BallsPocketMenu:
            // LD_HL(mBallsPocketMenuHeader);
            // CALL(aCopyMenuHeader);
            CopyMenuHeader_Conv2(&BallsPocketMenuHeader);
            // LD_A_addr(wBallsPocketCursor);
            // LD_addr_A(wMenuCursorPosition);
            wram->wMenuCursorPosition = wram->wBallsPocketCursor;
            // LD_A_addr(wBallsPocketScrollPosition);
            // LD_addr_A(wMenuScrollPosition);
            wram->wMenuScrollPosition = wram->wBallsPocketScrollPosition;
            // CALL(aScrollingMenu);
            ScrollingMenu_Conv();
            // LD_A_addr(wMenuScrollPosition);
            // LD_addr_A(wBallsPocketScrollPosition);
            wram->wBallsPocketScrollPosition = wram->wMenuScrollPosition;
            // LD_A_addr(wMenuCursorY);
            // LD_addr_A(wBallsPocketCursor);
            wram->wBallsPocketCursor = wram->wMenuCursorY;
            // LD_B(PACKSTATE_INITITEMSPOCKET);  // left
            // LD_C(PACKSTATE_INITKEYITEMSPOCKET);  // right
            // CALL(aPack_InterpretJoypad);
            // RET_C ;
            if(Pack_InterpretJoypad_Conv(PACKSTATE_INITITEMSPOCKET, PACKSTATE_INITKEYITEMSPOCKET))
                return;
            // CALL(aPack_ItemBallsKey_LoadSubmenu);
            SafeCallGBAuto(aPack_ItemBallsKey_LoadSubmenu);
            // RET;
            return;
        //dw ['.InitKeyItemsPocket'];  //  5
        case PACKSTATE_INITKEYITEMSPOCKET:
        // InitKeyItemsPocket:
            // LD_A(KEY_ITEM_POCKET);
            // LD_addr_A(wCurPocket);
            wram->wCurPocket = KEY_ITEM_POCKET;
            // CALL(aClearPocketList);
            ClearPocketList();
            // CALL(aDrawPocketName);
            DrawPocketName(KEY_ITEM_POCKET);
            // CALL(aWaitBGMap_DrawPackGFX);
            WaitBGMap_DrawPackGFX();
            // CALL(aPack_JumptableNext);
            Pack_JumptableNext();
            // RET;
            return;
        //dw ['.KeyItemsPocketMenu'];  //  6
        case PACKSTATE_KEYITEMSPOCKETMENU:
        // KeyItemsPocketMenu:
            // LD_HL(mKeyItemsPocketMenuHeader);
            // CALL(aCopyMenuHeader);
            CopyMenuHeader_Conv2(&KeyItemsPocketMenuHeader);
            // LD_A_addr(wKeyItemsPocketCursor);
            // LD_addr_A(wMenuCursorPosition);
            wram->wMenuCursorPosition = wram->wKeyItemsPocketCursor;
            // LD_A_addr(wKeyItemsPocketScrollPosition);
            // LD_addr_A(wMenuScrollPosition);
            wram->wMenuScrollPosition = wram->wKeyItemsPocketScrollPosition;
            // CALL(aScrollingMenu);
            ScrollingMenu_Conv();
            // LD_A_addr(wMenuScrollPosition);
            // LD_addr_A(wKeyItemsPocketScrollPosition);
            wram->wKeyItemsPocketScrollPosition = wram->wMenuSelection;
            // LD_A_addr(wMenuCursorY);
            // LD_addr_A(wKeyItemsPocketCursor);
            wram->wKeyItemsPocketCursor = wram->wMenuCursorY;
            // LD_B(PACKSTATE_INITBALLSPOCKET);  // left
            // LD_C(PACKSTATE_INITTMHMPOCKET);  // right
            // CALL(aPack_InterpretJoypad);
            // RET_C ;
            if(Pack_InterpretJoypad_Conv(PACKSTATE_INITBALLSPOCKET, PACKSTATE_INITTMHMPOCKET))
                return;
            // CALL(aPack_ItemBallsKey_LoadSubmenu);
            SafeCallGBAuto(aPack_ItemBallsKey_LoadSubmenu);
            // RET;
            return;
        //dw ['.InitTMHMPocket'];  //  7
        case PACKSTATE_INITTMHMPOCKET:
        // InitTMHMPocket:
            // LD_A(TM_HM_POCKET);
            // LD_addr_A(wCurPocket);
            wram->wCurPocket = TM_HM_POCKET;
            // CALL(aClearPocketList);
            ClearPocketList();
            // CALL(aDrawPocketName);
            DrawPocketName(TM_HM_POCKET);
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = 0;
            // CALL(aWaitBGMap_DrawPackGFX);
            WaitBGMap_DrawPackGFX();
            // CALL(aPack_JumptableNext);
            Pack_JumptableNext();
            // RET;
            return;
        //dw ['.TMHMPocketMenu'];  //  8
        case PACKSTATE_TMHMPOCKETMENU:
            SafeCallGBAuto(aPack_TMHMPocketMenu);
            return;
        //dw ['Pack_QuitNoScript'];  //  9
        case PACKSTATE_QUITNOSCRIPT:
            return Pack_QuitNoScript();
        //dw ['Pack_QuitRunScript'];  // 10
        case PACKSTATE_QUITRUNSCRIPT:
            return Pack_QuitRunScript();
    }

TMHMPocketMenu:
    FARCALL(aTMHMPocket);
    LD_B(PACKSTATE_INITKEYITEMSPOCKET);  // left
    LD_C(PACKSTATE_INITITEMSPOCKET);  // right
    CALL(aPack_InterpretJoypad);
    RET_C ;
    FARCALL(av_CheckTossableItem);
    LD_A_addr(wItemAttributeValue);
    AND_A_A;
    IF_NZ goto use_quit;
    LD_HL(mPack_MenuHeader2);
    LD_DE(mPack_Jumptable2);
    goto load_jump;


use_quit:
    LD_HL(mPack_MenuHeader1);
    LD_DE(mPack_Jumptable1);

load_jump:
    PUSH_DE;
    CALL(aLoadMenuHeader);
    CALL(aVerticalMenu);
    CALL(aExitMenu);
    POP_HL;
    RET_C ;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    CALL(aPack_GetJumptablePointer);
    JP_hl;


MenuHeader1:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['13', '7', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['.MenuData_1'];
    //db ['1'];  // default option


MenuData_1:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['2'];  // items
    //db ['"USE@"'];
    //db ['"QUIT@"'];


Jumptable1:
    //dw ['.UseItem'];
    //dw ['QuitItemSubmenu'];


MenuHeader2:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['13', '5', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['.MenuData_2'];
    //db ['1'];  // default option


MenuData_2:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['3'];  // items
    //db ['"USE@"'];
    //db ['"GIVE@"'];
    //db ['"QUIT@"'];


Jumptable2:
    //dw ['.UseItem'];
    //dw ['GiveItem'];
    //dw ['QuitItemSubmenu'];


UseItem:
    FARCALL(aAskTeachTMHM);
    RET_C ;
    FARCALL(aChooseMonToLearnTMHM);
    IF_C goto declined;
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    RES_hl(NO_TEXT_SCROLL);
    FARCALL(aTeachTMHM);
    POP_AF;
    LD_addr_A(wOptions);

declined:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPack_InitGFX);
    CALL(aWaitBGMap_DrawPackGFX);
    CALL(aPack_InitColors);
    RET;


ItemBallsKey_LoadSubmenu:
    FARCALL(av_CheckTossableItem);
    LD_A_addr(wItemAttributeValue);
    AND_A_A;
    IF_NZ goto tossable;
    FARCALL(aCheckSelectableItem);
    LD_A_addr(wItemAttributeValue);
    AND_A_A;
    IF_NZ goto selectable;
    FARCALL(aCheckItemMenu);
    LD_A_addr(wItemAttributeValue);
    AND_A_A;
    IF_NZ goto usable;
    goto unusable;


selectable:
    FARCALL(aCheckItemMenu);
    LD_A_addr(wItemAttributeValue);
    AND_A_A;
    IF_NZ goto selectable_usable;
    goto selectable_unusable;


tossable:
    FARCALL(aCheckSelectableItem);
    LD_A_addr(wItemAttributeValue);
    AND_A_A;
    IF_NZ goto tossable_selectable;
    goto tossable_unselectable;


usable:
    LD_HL(mMenuHeader_UsableKeyItem);
    LD_DE(mJumptable_UseGiveTossRegisterQuit);
    goto build_menu;


selectable_usable:
    LD_HL(mMenuHeader_UsableItem);
    LD_DE(mJumptable_UseGiveTossQuit);
    goto build_menu;


tossable_selectable:
    LD_HL(mMenuHeader_UnusableItem);
    LD_DE(mJumptable_UseQuit);
    goto build_menu;


tossable_unselectable:
    LD_HL(mMenuHeader_UnusableKeyItem);
    LD_DE(mJumptable_UseRegisterQuit);
    goto build_menu;


unusable:
    LD_HL(mMenuHeader_HoldableKeyItem);
    LD_DE(mJumptable_GiveTossRegisterQuit);
    goto build_menu;


selectable_unusable:
    LD_HL(mMenuHeader_HoldableItem);
    LD_DE(mJumptable_GiveTossQuit);

build_menu:
    PUSH_DE;
    CALL(aLoadMenuHeader);
    CALL(aVerticalMenu);
    CALL(aExitMenu);
    POP_HL;
    RET_C ;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    CALL(aPack_GetJumptablePointer);
    JP_hl;
}

void MenuHeader_UsableKeyItem(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['13', '1', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['5'];  // items
    //db ['"USE@"'];
    //db ['"GIVE@"'];
    //db ['"TOSS@"'];
    //db ['"SEL@"'];
    //db ['"QUIT@"'];

    return Jumptable_UseGiveTossRegisterQuit();
}

void Jumptable_UseGiveTossRegisterQuit(void){
    //dw ['UseItem'];
    //dw ['GiveItem'];
    //dw ['TossMenu'];
    //dw ['RegisterItem'];
    //dw ['QuitItemSubmenu'];

    return MenuHeader_UsableItem();
}

void MenuHeader_UsableItem(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['13', '3', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['4'];  // items
    //db ['"USE@"'];
    //db ['"GIVE@"'];
    //db ['"TOSS@"'];
    //db ['"QUIT@"'];

    return Jumptable_UseGiveTossQuit();
}

void Jumptable_UseGiveTossQuit(void){
    //dw ['UseItem'];
    //dw ['GiveItem'];
    //dw ['TossMenu'];
    //dw ['QuitItemSubmenu'];

    return MenuHeader_UnusableItem();
}

void MenuHeader_UnusableItem(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['13', '7', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['2'];  // items
    //db ['"USE@"'];
    //db ['"QUIT@"'];

    return Jumptable_UseQuit();
}

void Jumptable_UseQuit(void){
    //dw ['UseItem'];
    //dw ['QuitItemSubmenu'];

    return MenuHeader_UnusableKeyItem();
}

void MenuHeader_UnusableKeyItem(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['13', '5', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['3'];  // items
    //db ['"USE@"'];
    //db ['"SEL@"'];
    //db ['"QUIT@"'];

    return Jumptable_UseRegisterQuit();
}

void Jumptable_UseRegisterQuit(void){
    //dw ['UseItem'];
    //dw ['RegisterItem'];
    //dw ['QuitItemSubmenu'];

    return MenuHeader_HoldableKeyItem();
}

void MenuHeader_HoldableKeyItem(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['13', '3', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['4'];  // items
    //db ['"GIVE@"'];
    //db ['"TOSS@"'];
    //db ['"SEL@"'];
    //db ['"QUIT@"'];

    return Jumptable_GiveTossRegisterQuit();
}

void Jumptable_GiveTossRegisterQuit(void){
    //dw ['GiveItem'];
    //dw ['TossMenu'];
    //dw ['RegisterItem'];
    //dw ['QuitItemSubmenu'];

    return MenuHeader_HoldableItem();
}

void MenuHeader_HoldableItem(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['13', '5', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['3'];  // items
    //db ['"GIVE@"'];
    //db ['"TOSS@"'];
    //db ['"QUIT@"'];

    return Jumptable_GiveTossQuit();
}

void Jumptable_GiveTossQuit(void){
    //dw ['GiveItem'];
    //dw ['TossMenu'];
    //dw ['QuitItemSubmenu'];

    return UseItem();
}

void UseItem(void){
    FARCALL(aCheckItemMenu);
    LD_A_addr(wItemAttributeValue);
    LD_HL(mUseItem_dw);
    RST(aJumpTable);
    RET;


dw:
//  entries correspond to ITEMMENU_* constants
    //dw ['.Oak'];  // ITEMMENU_NOUSE
    //dw ['.Oak'];
    //dw ['.Oak'];
    //dw ['.Oak'];
    //dw ['.Current'];  // ITEMMENU_CURRENT
    //dw ['.Party'];  // ITEMMENU_PARTY
    //dw ['.Field'];  // ITEMMENU_CLOSE


Oak:
    LD_HL(mOakThisIsntTheTimeText);
    CALL(aPack_PrintTextNoScroll);
    RET;


Current:
    CALL(aDoItemEffect);
    RET;


Party:
    LD_A_addr(wPartyCount);
    AND_A_A;
    IF_Z goto NoPokemon;
    CALL(aDoItemEffect);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPack_InitGFX);
    CALL(aWaitBGMap_DrawPackGFX);
    CALL(aPack_InitColors);
    RET;


NoPokemon:
    LD_HL(mYouDontHaveAMonText);
    CALL(aPack_PrintTextNoScroll);
    RET;


Field:
    CALL(aDoItemEffect);
    LD_A_addr(wItemEffectSucceeded);
    AND_A_A;
    IF_Z goto Oak;
    LD_A(PACKSTATE_QUITRUNSCRIPT);
    LD_addr_A(wJumptableIndex);
    RET;

}

void TossMenu(void){
    LD_HL(mAskThrowAwayText);
    CALL(aPack_PrintTextNoScroll);
    FARCALL(aSelectQuantityToToss);
    PUSH_AF;
    CALL(aExitMenu);
    POP_AF;
    IF_C goto finish;
    CALL(aPack_GetItemName);
    LD_HL(mAskQuantityThrowAwayText);
    CALL(aMenuTextbox);
    CALL(aYesNoBox);
    PUSH_AF;
    CALL(aExitMenu);
    POP_AF;
    IF_C goto finish;
    LD_HL(wNumItems);
    LD_A_addr(wCurItemQuantity);
    CALL(aTossItem);
    CALL(aPack_GetItemName);
    LD_HL(mThrewAwayText);
    CALL(aPack_PrintTextNoScroll);

finish:
    RET;

}

void ResetPocketCursorPositions(void){
//  //  unreferenced
    LD_A_addr(wCurPocket);
    AND_A_A;  // ITEM_POCKET
    IF_Z goto items;
    DEC_A;  // BALL_POCKET
    IF_Z goto balls;
    DEC_A;  // KEY_ITEM_POCKET
    IF_Z goto key;
    RET;


balls:
    XOR_A_A;
    LD_addr_A(wBallsPocketCursor);
    LD_addr_A(wBallsPocketScrollPosition);
    RET;


items:
    XOR_A_A;
    LD_addr_A(wItemsPocketCursor);
    LD_addr_A(wItemsPocketScrollPosition);
    RET;


key:
    XOR_A_A;
    LD_addr_A(wKeyItemsPocketCursor);
    LD_addr_A(wKeyItemsPocketScrollPosition);
    RET;

}

void RegisterItem(void){
    FARCALL(aCheckSelectableItem);
    LD_A_addr(wItemAttributeValue);
    AND_A_A;
    IF_NZ goto cant_register;
    LD_A_addr(wCurPocket);
    RRCA;
    RRCA;
    AND_A(REGISTERED_POCKET);
    LD_B_A;
    LD_A_addr(wCurItemQuantity);
    INC_A;
    AND_A(REGISTERED_NUMBER);
    OR_A_B;
    LD_addr_A(wWhichRegisteredItem);
    LD_A_addr(wCurItem);
    LD_addr_A(wRegisteredItem);
    CALL(aPack_GetItemName);
    LD_DE(SFX_FULL_HEAL);
    CALL(aWaitPlaySFX);
    LD_HL(mRegisteredItemText);
    CALL(aPack_PrintTextNoScroll);
    RET;


cant_register:
    LD_HL(mCantRegisterText);
    CALL(aPack_PrintTextNoScroll);
    RET;

}

void GiveItem(void){
    LD_A_addr(wPartyCount);
    AND_A_A;
    JP_Z (mGiveItem_NoPokemon);
    LD_A_addr(wOptions);
    PUSH_AF;
    RES_A(NO_TEXT_SCROLL);
    LD_addr_A(wOptions);
    LD_A(PARTYMENUACTION_GIVE_ITEM);
    LD_addr_A(wPartyMenuActionText);
    CALL(aClearBGPalettes);
    FARCALL(aLoadPartyMenuGFX);
    FARCALL(aInitPartyMenuWithCancel);
    FARCALL(aInitPartyMenuGFX);

loop:
    FARCALL(aWritePartyMenuTilemap);
    FARCALL(aPrintPartyMenuText);
    CALL(aWaitBGMap);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    FARCALL(aPartyMenuSelect);
    IF_C goto finish;
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_NZ goto give;
    LD_HL(mGiveItem_AnEggCantHoldAnItemText);
    CALL(aPrintText);
    goto loop;


give:
    LD_A_addr(wJumptableIndex);
    PUSH_AF;
    LD_A_addr(wPackJumptableIndex);
    PUSH_AF;
    CALL(aGetCurNickname);
    LD_HL(wStringBuffer1);
    LD_DE(wMonOrItemNameBuffer);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    CALL(aTryGiveItemToPartymon);
    POP_AF;
    LD_addr_A(wPackJumptableIndex);
    POP_AF;
    LD_addr_A(wJumptableIndex);

finish:
    POP_AF;
    LD_addr_A(wOptions);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPack_InitGFX);
    CALL(aWaitBGMap_DrawPackGFX);
    CALL(aPack_InitColors);
    RET;


NoPokemon:
    LD_HL(mYouDontHaveAMonText);
    CALL(aPack_PrintTextNoScroll);
    RET;

AnEggCantHoldAnItemText:
    //text_far ['_AnEggCantHoldAnItemText']
    //text_end ['?']

    return QuitItemSubmenu();
}

void QuitItemSubmenu(void){
    RET;

}

static void BattlePack_RunJumptable(void) {
    // LD_A_addr(wJumptableIndex);
    // LD_HL(mBattlePack_Jumptable);
    // CALL(aPack_GetJumptablePointer);
    // JP_hl;

    switch(wram->wJumptableIndex) {
    // Jumptable:
    //  entries correspond to PACKSTATE_* constants
        //dw ['.InitGFX'];  //  0
        case PACKSTATE_INITGFX:
        // InitGFX:
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = 0;
            // CALL(aPack_InitGFX);
            Pack_InitGFX();
            // LD_A_addr(wPackJumptableIndex);
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex = wram->wPackJumptableIndex;
            // CALL(aPack_InitColors);
            Pack_InitColors();
            // RET;
            return;
        //dw ['.InitItemsPocket'];  //  1
        case PACKSTATE_INITITEMSPOCKET:
        // InitItemsPocket:
            // XOR_A_A;  // ITEM_POCKET
            // LD_addr_A(wCurPocket);
            wram->wCurPocket = ITEM_POCKET;
            // CALL(aClearPocketList);
            ClearPocketList();
            // CALL(aDrawPocketName);
            DrawPocketName(ITEM_POCKET);
            // CALL(aWaitBGMap_DrawPackGFX);
            WaitBGMap_DrawPackGFX();
            // CALL(aPack_JumptableNext);
            Pack_JumptableNext();
            // RET;
            return;
        //dw ['.ItemsPocketMenu'];  //  2
        case PACKSTATE_ITEMSPOCKETMENU:
        // ItemsPocketMenu:
            // LD_HL(mItemsPocketMenuHeader);
            // CALL(aCopyMenuHeader);
            CopyMenuHeader_Conv2(&ItemsPocketMenuHeader);
            // LD_A_addr(wItemsPocketCursor);
            // LD_addr_A(wMenuCursorPosition);
            wram->wMenuCursorPosition = wram->wItemsPocketCursor;
            // LD_A_addr(wItemsPocketScrollPosition);
            // LD_addr_A(wMenuScrollPosition);
            wram->wMenuScrollPosition = wram->wItemsPocketScrollPosition;
            // CALL(aScrollingMenu);
            ScrollingMenu_Conv();
            // LD_A_addr(wMenuScrollPosition);
            // LD_addr_A(wItemsPocketScrollPosition);
            wram->wItemsPocketScrollPosition = wram->wMenuScrollPosition;
            // LD_A_addr(wMenuCursorY);
            // LD_addr_A(wItemsPocketCursor);
            wram->wItemsPocketCursor = wram->wMenuCursorY;
            // LD_B(PACKSTATE_INITTMHMPOCKET);  // left
            // LD_C(PACKSTATE_INITBALLSPOCKET);  // right
            // CALL(aPack_InterpretJoypad);
            // RET_C ;
            if(Pack_InterpretJoypad_Conv(PACKSTATE_INITTMHMPOCKET, PACKSTATE_INITBALLSPOCKET))
                return;
            // CALL(aItemSubmenu);
            SafeCallGBAuto(aItemSubmenu);
            // RET;
            return;
        //dw ['.InitBallsPocket'];  //  3
        case PACKSTATE_INITBALLSPOCKET:
        // InitBallsPocket:
            // LD_A(BALL_POCKET);
            // LD_addr_A(wCurPocket);
            wram->wCurPocket = BALL_POCKET;
            // CALL(aClearPocketList);
            ClearPocketList();
            // CALL(aDrawPocketName);
            DrawPocketName(BALL_POCKET);
            // CALL(aWaitBGMap_DrawPackGFX);
            WaitBGMap_DrawPackGFX();
            // CALL(aPack_JumptableNext);
            Pack_JumptableNext();
            // RET;
            return;
        //dw ['.BallsPocketMenu'];  //  4
        case PACKSTATE_BALLSPOCKETMENU:
        // BallsPocketMenu:
            // LD_HL(mBallsPocketMenuHeader);
            // CALL(aCopyMenuHeader);
            CopyMenuHeader_Conv2(&BallsPocketMenuHeader);
            // LD_A_addr(wBallsPocketCursor);
            // LD_addr_A(wMenuCursorPosition);
            wram->wMenuCursorPosition = wram->wBallsPocketCursor;
            // LD_A_addr(wBallsPocketScrollPosition);
            // LD_addr_A(wMenuScrollPosition);
            wram->wMenuScrollPosition = wram->wBallsPocketScrollPosition;
            // CALL(aScrollingMenu);
            ScrollingMenu_Conv();
            // LD_A_addr(wMenuScrollPosition);
            // LD_addr_A(wBallsPocketScrollPosition);
            wram->wBallsPocketScrollPosition = wram->wMenuScrollPosition;
            // LD_A_addr(wMenuCursorY);
            // LD_addr_A(wBallsPocketCursor);
            wram->wBallsPocketCursor = wram->wMenuCursorY;
            // LD_B(PACKSTATE_INITITEMSPOCKET);  // left
            // LD_C(PACKSTATE_INITKEYITEMSPOCKET);  // right
            // CALL(aPack_InterpretJoypad);
            // RET_C ;
            if(Pack_InterpretJoypad_Conv(PACKSTATE_INITITEMSPOCKET, PACKSTATE_INITKEYITEMSPOCKET))
                return;
            // CALL(aItemSubmenu);
            SafeCallGBAuto(aItemSubmenu);
            // RET;
            return;
        //dw ['.InitKeyItemsPocket'];  //  5
        case PACKSTATE_INITKEYITEMSPOCKET:
        // InitKeyItemsPocket:
            // LD_A(KEY_ITEM_POCKET);
            // LD_addr_A(wCurPocket);
            wram->wCurPocket = KEY_ITEM_POCKET;
            // CALL(aClearPocketList);
            ClearPocketList();
            // CALL(aDrawPocketName);
            DrawPocketName(KEY_ITEM_POCKET);
            // CALL(aWaitBGMap_DrawPackGFX);
            WaitBGMap_DrawPackGFX();
            // CALL(aPack_JumptableNext);
            Pack_JumptableNext();
            // RET;
            return;
        //dw ['.KeyItemsPocketMenu'];  //  6
        case PACKSTATE_KEYITEMSPOCKETMENU:
        // KeyItemsPocketMenu:
            // LD_HL(mKeyItemsPocketMenuHeader);
            // CALL(aCopyMenuHeader);
            CopyMenuHeader_Conv2(&KeyItemsPocketMenuHeader);
            // LD_A_addr(wKeyItemsPocketCursor);
            // LD_addr_A(wMenuCursorPosition);
            wram->wMenuCursorPosition = wram->wKeyItemsPocketCursor;
            // LD_A_addr(wKeyItemsPocketScrollPosition);
            // LD_addr_A(wMenuScrollPosition);
            wram->wMenuScrollPosition = wram->wKeyItemsPocketScrollPosition;
            // CALL(aScrollingMenu);
            ScrollingMenu_Conv();
            // LD_A_addr(wMenuScrollPosition);
            // LD_addr_A(wKeyItemsPocketScrollPosition);
            wram->wKeyItemsPocketScrollPosition = wram->wMenuScrollPosition;
            // LD_A_addr(wMenuCursorY);
            // LD_addr_A(wKeyItemsPocketCursor);
            wram->wKeyItemsPocketCursor = wram->wMenuCursorY;
            // LD_B(PACKSTATE_INITBALLSPOCKET);  // left
            // LD_C(PACKSTATE_INITTMHMPOCKET);  // right
            // CALL(aPack_InterpretJoypad);
            // RET_C ;
            if(Pack_InterpretJoypad_Conv(PACKSTATE_INITBALLSPOCKET, PACKSTATE_INITTMHMPOCKET))
                return;
            // CALL(aItemSubmenu);
            SafeCallGBAuto(aItemSubmenu);
            // RET;
            return;
        //dw ['.InitTMHMPocket'];  //  7
        case PACKSTATE_INITTMHMPOCKET:
        // InitTMHMPocket:
            // LD_A(TM_HM_POCKET);
            // LD_addr_A(wCurPocket);
            wram->wCurPocket = TM_HM_POCKET;
            // CALL(aClearPocketList);
            ClearPocketList();
            // CALL(aDrawPocketName);
            DrawPocketName(TM_HM_POCKET);
            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = 0;
            // CALL(aWaitBGMap_DrawPackGFX);
            WaitBGMap_DrawPackGFX();
            // LD_HL(mPackEmptyText);
            // CALL(aPack_PrintTextNoScroll);
            Pack_PrintTextNoScroll(PackEmptyText);
            // CALL(aPack_JumptableNext);
            Pack_JumptableNext();
            // RET;
            return;
        //dw ['.TMHMPocketMenu'];  //  8
        case PACKSTATE_TMHMPOCKETMENU:
        // TMHMPocketMenu:
            // FARCALL(aTMHMPocket);
            SafeCallGBAuto(aTMHMPocket);
            // LD_B(PACKSTATE_INITKEYITEMSPOCKET);  // left
            // LD_C(PACKSTATE_INITITEMSPOCKET);  // right
            // CALL(aPack_InterpretJoypad);
            // RET_C ;
            if(Pack_InterpretJoypad_Conv(PACKSTATE_INITKEYITEMSPOCKET, PACKSTATE_INITITEMSPOCKET))
                return;
            // XOR_A_A;
            // CALL(aTMHMSubmenu);
            SafeCallGB(aTMHMSubmenu, &(struct cpu_registers_s){.a = 0});
            // RET;
            return;
        //dw ['Pack_QuitNoScript'];  //  9
        case PACKSTATE_QUITNOSCRIPT:
            return Pack_QuitNoScript();
        //dw ['Pack_QuitRunScript'];  // 10
        case PACKSTATE_QUITRUNSCRIPT:
            return Pack_QuitRunScript();
    }
}

void BattlePack(void){
    // LD_HL(wOptions);
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aInitPackBuffers);
    InitPackBuffers();

    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto end;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(aBattlePack_RunJumptable);
        BattlePack_RunJumptable();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }


// end:
    // LD_A_addr(wCurPocket);
    // LD_addr_A(wLastPocket);
    wram->wLastPocket = wram->wCurPocket;
    // LD_HL(wOptions);
    // RES_hl(NO_TEXT_SCROLL);
    bit_reset(wram->wOptions, NO_TEXT_SCROLL);
    // RET;
    return;
}

void ItemSubmenu(void){
    FARCALL(aCheckItemContext);
    LD_A_addr(wItemAttributeValue);
    return TMHMSubmenu();
}

void TMHMSubmenu(void){
    AND_A_A;
    IF_Z goto NoUse;
    LD_HL(mTMHMSubmenu_UsableMenuHeader);
    LD_DE(mTMHMSubmenu_UsableJumptable);
    goto proceed;


NoUse:
    LD_HL(mTMHMSubmenu_UnusableMenuHeader);
    LD_DE(mTMHMSubmenu_UnusableJumptable);

proceed:
    PUSH_DE;
    CALL(aLoadMenuHeader);
    CALL(aVerticalMenu);
    CALL(aExitMenu);
    POP_HL;
    RET_C ;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    CALL(aPack_GetJumptablePointer);
    JP_hl;


UsableMenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['13', '7', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['.UsableMenuData'];
    //db ['1'];  // default option


UsableMenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['2'];  // items
    //db ['"USE@"'];
    //db ['"QUIT@"'];


UsableJumptable:
    //dw ['.Use'];
    //dw ['.Quit'];


UnusableMenuHeader:
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['13', '9', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['.UnusableMenuData'];
    //db ['1'];  // default option


UnusableMenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['1'];  // items
    //db ['"QUIT@"'];


UnusableJumptable:
    //dw ['.Quit'];


Use:
    FARCALL(aCheckItemContext);
    LD_A_addr(wItemAttributeValue);
    LD_HL(mTMHMSubmenu_ItemFunctionJumptable);
    RST(aJumpTable);
    RET;


ItemFunctionJumptable:
//  entries correspond to ITEMMENU_* constants
    //dw ['.Oak'];  // ITEMMENU_NOUSE
    //dw ['.Oak'];
    //dw ['.Oak'];
    //dw ['.Oak'];
    //dw ['.Unused'];  // ITEMMENU_CURRENT
    //dw ['.BattleField'];  // ITEMMENU_PARTY
    //dw ['.BattleOnly'];  // ITEMMENU_CLOSE


Oak:
    LD_HL(mOakThisIsntTheTimeText);
    CALL(aPack_PrintTextNoScroll);
    RET;


Unused:
    CALL(aDoItemEffect);
    LD_A_addr(wItemEffectSucceeded);
    AND_A_A;
    IF_NZ goto ReturnToBattle;
    RET;


BattleField:
    CALL(aDoItemEffect);
    LD_A_addr(wItemEffectSucceeded);
    AND_A_A;
    IF_NZ goto quit_run_script;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPack_InitGFX);
    CALL(aWaitBGMap_DrawPackGFX);
    CALL(aPack_InitColors);
    RET;


ReturnToBattle:
    CALL(aClearBGPalettes);
    goto quit_run_script;


BattleOnly:
    CALL(aDoItemEffect);
    LD_A_addr(wItemEffectSucceeded);
    AND_A_A;
    IF_Z goto Oak;
    CP_A(0x2);
    IF_Z goto didnt_use_item;

quit_run_script:
    LD_A(PACKSTATE_QUITRUNSCRIPT);
    LD_addr_A(wJumptableIndex);
    RET;


didnt_use_item:
    XOR_A_A;
    LD_addr_A(wItemEffectSucceeded);
    RET;

Quit:
    RET;

}

void InitPackBuffers(void){
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0;
// pocket id -> jumptable index
    // LD_A_addr(wLastPocket);
    // maskbits(NUM_POCKETS, 0);
    // LD_addr_A(wCurPocket);
    wram->wCurPocket = wram->wLastPocket & (NUM_POCKETS - 1);
    // INC_A;
    // ADD_A_A;
    // DEC_A;
    // LD_addr_A(wPackJumptableIndex);
    wram->wPackJumptableIndex = ((wram->wCurPocket + 1) * 2) - 1;
    // XOR_A_A;  // FALSE
    // LD_addr_A(wPackUsedItem);
    wram->wPackUsedItem = FALSE;
    // XOR_A_A;
    // LD_addr_A(wSwitchItem);
    wram->wSwitchItem = 0;
    // RET;
}

void DepositSellInitPackBuffers(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // LD_addr_A(wJumptableIndex);  // PACKSTATE_INITGFX
    wram->wJumptableIndex = PACKSTATE_INITGFX;
    // LD_addr_A(wPackJumptableIndex);  // PACKSTATE_INITGFX
    wram->wPackJumptableIndex = PACKSTATE_INITGFX;
    // LD_addr_A(wCurPocket);  // ITEM_POCKET
    wram->wCurPocket = ITEM_POCKET;
    // LD_addr_A(wPackUsedItem);
    wram->wPackUsedItem = 0;
    // LD_addr_A(wSwitchItem);
    wram->wSwitchItem = 0;
    // CALL(aPack_InitGFX);
    Pack_InitGFX();
    // CALL(aPack_InitColors);
    Pack_InitColors();
    // RET;
}

    // LD_A_addr(wJumptableIndex);
static void DepositSellPack_RunJumptable(void){
    // LD_HL(mDepositSellPack_Jumptable);
    // CALL(aPack_GetJumptablePointer);
    // JP_hl;
    switch(wram->wJumptableIndex){
    // Jumptable:
    //  entries correspond to *_POCKET constants
        //dw ['.ItemsPocket'];
        case ITEM_POCKET:
        // ItemsPocket:
            // XOR_A_A;  // ITEM_POCKET
            // CALL(aInitPocket);
            InitPocket(ITEM_POCKET);
            // LD_HL(mPC_Mart_ItemsPocketMenuHeader);
            // CALL(aCopyMenuHeader);
            CopyMenuHeader_Conv2(&PC_Mart_ItemsPocketMenuHeader);
            // LD_A_addr(wItemsPocketCursor);
            // LD_addr_A(wMenuCursorPosition);
            wram->wMenuCursorPosition = wram->wItemsPocketCursor;
            // LD_A_addr(wItemsPocketScrollPosition);
            // LD_addr_A(wMenuScrollPosition);
            wram->wMenuScrollPosition = wram->wItemsPocketScrollPosition;
            // CALL(aScrollingMenu);
            ScrollingMenu_Conv();
            // LD_A_addr(wMenuScrollPosition);
            // LD_addr_A(wItemsPocketScrollPosition);
            wram->wItemsPocketScrollPosition = wram->wMenuScrollPosition;
            // LD_A_addr(wMenuCursorY);
            // LD_addr_A(wItemsPocketCursor);
            wram->wItemsPocketCursor = wram->wMenuCursorY;
            // RET;
            return;
        //dw ['.BallsPocket'];
        case BALL_POCKET:
        // BallsPocket:
            // LD_A(BALL_POCKET);
            // CALL(aInitPocket);
            InitPocket(BALL_POCKET);
            // LD_HL(mPC_Mart_BallsPocketMenuHeader);
            // CALL(aCopyMenuHeader);
            CopyMenuHeader_Conv2(&PC_Mart_BallsPocketMenuHeader);
            // LD_A_addr(wBallsPocketCursor);
            // LD_addr_A(wMenuCursorPosition);
            wram->wMenuCursorPosition = wram->wBallsPocketCursor;
            // LD_A_addr(wBallsPocketScrollPosition);
            // LD_addr_A(wMenuScrollPosition);
            wram->wMenuScrollPosition = wram->wBallsPocketScrollPosition;
            // CALL(aScrollingMenu);
            ScrollingMenu_Conv();
            // LD_A_addr(wMenuScrollPosition);
            // LD_addr_A(wBallsPocketScrollPosition);
            wram->wBallsPocketScrollPosition = wram->wMenuScrollPosition;
            // LD_A_addr(wMenuCursorY);
            // LD_addr_A(wBallsPocketCursor);
            wram->wBallsPocketCursor = wram->wMenuCursorY;
            // RET;
            return;
        //dw ['.KeyItemsPocket'];
        case KEY_ITEM_POCKET:
        // KeyItemsPocket:
            // LD_A(KEY_ITEM_POCKET);
            // CALL(aInitPocket);
            InitPocket(KEY_ITEM_POCKET);
            // LD_HL(mPC_Mart_KeyItemsPocketMenuHeader);
            // CALL(aCopyMenuHeader);
            CopyMenuHeader_Conv2(&PC_Mart_KeyItemsPocketMenuHeader);
            // LD_A_addr(wKeyItemsPocketCursor);
            // LD_addr_A(wMenuCursorPosition);
            wram->wMenuCursorPosition = wram->wKeyItemsPocketCursor;
            // LD_A_addr(wKeyItemsPocketScrollPosition);
            // LD_addr_A(wMenuScrollPosition);
            wram->wMenuScrollPosition = wram->wKeyItemsPocketScrollPosition;
            // CALL(aScrollingMenu);
            ScrollingMenu_Conv();
            // LD_A_addr(wMenuScrollPosition);
            // LD_addr_A(wKeyItemsPocketScrollPosition);
            wram->wKeyItemsPocketScrollPosition = wram->wMenuScrollPosition;
            // LD_A_addr(wMenuCursorY);
            // LD_addr_A(wKeyItemsPocketCursor);
            wram->wKeyItemsPocketCursor = wram->wMenuCursorY;
            // RET;
            return;
        //dw ['.TMHMPocket'];
        case TM_HM_POCKET:
        // TMHMPocket:
            // LD_A(TM_HM_POCKET);
            // CALL(aInitPocket);
            InitPocket(TM_HM_POCKET);
            // CALL(aWaitBGMap_DrawPackGFX);
            WaitBGMap_DrawPackGFX();
            // FARCALL(aTMHMPocket);
            SafeCallGBAuto(aTMHMPocket);
            // LD_A_addr(wCurItem);
            // LD_addr_A(wCurItem);
            // RET;
            return;
    }
}

void DepositSellPack(void){
    bool quit = false;
    do {
    // loop:
        // CALL(aDepositSellPack_RunJumptable);
        DepositSellPack_RunJumptable();
        // CALL(aDepositSellTutorial_InterpretJoypad);
        quit = DepositSellTutorial_InterpretJoypad();
        // IF_C goto loop;
    } while(!quit);
    // RET;
}

void InitPocket(uint8_t pocket){
    // LD_addr_A(wCurPocket);
    wram->wCurPocket = pocket;
    // CALL(aClearPocketList);
    ClearPocketList();
    // CALL(aDrawPocketName);
    DrawPocketName(pocket);
    // CALL(aWaitBGMap_DrawPackGFX);
    WaitBGMap_DrawPackGFX();
    // RET;
}

bool DepositSellTutorial_InterpretJoypad(void){
    // LD_HL(wMenuJoypad);
    // LD_A_hl;
    uint8_t a = wram->wMenuJoypad;
    // AND_A(A_BUTTON);
    // IF_NZ goto a_button;
    if(a & A_BUTTON){
    // a_button:
        // LD_A(TRUE);
        // LD_addr_A(wPackUsedItem);
        wram->wPackUsedItem = TRUE;
        // AND_A_A;
        // RET;
        return true;
    }
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto b_button;
    if(a & B_BUTTON){
    // b_button:
        // XOR_A_A;  // FALSE
        // LD_addr_A(wPackUsedItem);
        wram->wPackUsedItem = FALSE;
        // AND_A_A;
        // RET;
        return true;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto d_left;
    if(a & D_LEFT){
    // d_left:
        // LD_A_addr(wJumptableIndex);
        // DEC_A;
        // maskbits(NUM_POCKETS, 0);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = (wram->wJumptableIndex - 1) & 3;
        // PUSH_DE;
        // LD_DE(SFX_SWITCH_POCKETS);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_SWITCH_POCKETS);
        // POP_DE;
        // SCF;
        // RET;
        return false;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto d_right;
    if(a & D_RIGHT){
    // d_right:
        // LD_A_addr(wJumptableIndex);
        // INC_A;
        // maskbits(NUM_POCKETS, 0);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = (wram->wJumptableIndex + 1) & 3;
        // PUSH_DE;
        // LD_DE(SFX_SWITCH_POCKETS);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_SWITCH_POCKETS);
        // POP_DE;
        // SCF;
        // RET;
        return false;
    }
    // SCF;
    // RET;
    return false;
}

static const struct MenuHeader TutorialPack_ItemsMenuHeader = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(7, 1, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.ItemsMenuData'];
    .data = &(struct MenuData) {
// ItemsMenuData:
        .flags = STATICMENU_ENABLE_SELECT | STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP | STATICMENU_CURSOR,  // flags
        .scrollingMenu = {
            .rows=5, .cols=8,  // rows, columns
            .format=SCROLLINGMENU_ITEMS_QUANTITY,  // item format
            //dbw ['0', 'wDudeNumItems']
            .list = wram_ptr(wDudeNumItems),
            //dba ['PlaceMenuItemName']
            .func1 = PlaceMenuItemName_Conv,
            //dba ['PlaceMenuItemQuantity']
            .func2 = PlaceMenuItemQuantity_Conv,
            //dba ['UpdateItemDescription']
            .func3 = UpdateItemDescription,
        },
    },
    .defaultOption=1,  // default option
};

static const struct MenuHeader TutorialPack_KeyItemsMenuHeader = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(7, 1, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.KeyItemsMenuData'];
    .data = &(struct MenuData) {
    // KeyItemsMenuData:
        .flags = STATICMENU_ENABLE_SELECT | STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP | STATICMENU_CURSOR,  // flags
        .scrollingMenu = {
            .rows=5, .cols=8,  // rows, columns
            .format = SCROLLINGMENU_ITEMS_NORMAL,  // item format
            //dbw ['0', 'wDudeNumKeyItems']
            .list = wram_ptr(wDudeNumKeyItems),
            //dba ['PlaceMenuItemName']
            .func1 = PlaceMenuItemName_Conv,
            //dba ['PlaceMenuItemQuantity']
            .func2 = PlaceMenuItemQuantity_Conv,
            //dba ['UpdateItemDescription']
            .func3 = UpdateItemDescription,
        },
    },
    .defaultOption=1,  // default option
};

static const struct MenuHeader TutorialPack_BallsMenuHeader = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(7, 1, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.BallsMenuData'];
    .data = &(struct MenuData) {
    // BallsMenuData:
        .flags = STATICMENU_ENABLE_SELECT | STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP | STATICMENU_CURSOR,  // flags
        .scrollingMenu = {
            .rows=5, .cols=8,  // rows, columns
            .format=SCROLLINGMENU_ITEMS_QUANTITY,  // item format
            //dbw ['0', 'wDudeNumBalls']
            .list = wram_ptr(wDudeNumBalls),
            //dba ['PlaceMenuItemName']
            .func1 = PlaceMenuItemName_Conv,
            //dba ['PlaceMenuItemQuantity']
            .func2 = PlaceMenuItemQuantity_Conv,
            //dba ['UpdateItemDescription']
            .func3 = UpdateItemDescription,
        },
    },
    .defaultOption=1,  // default option
};

static void TutorialPack_RunJumptable(void) {
// RunJumptable:
    // LD_A_addr(wJumptableIndex);
    // LD_HL(mTutorialPack_dw);
    // CALL(aPack_GetJumptablePointer);
    // JP_hl;


// dw:
//  entries correspond to *_POCKET constants
    switch(wram->wJumptableIndex) {
        //dw ['.Items'];
        case ITEM_POCKET:
        // Items:
            // XOR_A_A;  // ITEM_POCKET
            // LD_HL(mTutorialPack_ItemsMenuHeader);
            // goto DisplayPocket;
            InitPocket(ITEM_POCKET);
            CopyMenuHeader_Conv2(&TutorialPack_ItemsMenuHeader);
            break;
        //dw ['.Balls'];
        case BALL_POCKET:
        // Balls:
            // LD_A(BALL_POCKET);
            // LD_HL(mTutorialPack_BallsMenuHeader);
            // goto DisplayPocket;
            InitPocket(BALL_POCKET);
            CopyMenuHeader_Conv2(&TutorialPack_BallsMenuHeader);
            break;
        //dw ['.KeyItems'];
        case KEY_ITEM_POCKET:
        // KeyItems:
            // LD_A(KEY_ITEM_POCKET);
            // LD_HL(mTutorialPack_KeyItemsMenuHeader);
            // goto DisplayPocket;
            InitPocket(KEY_ITEM_POCKET);
            CopyMenuHeader_Conv2(&TutorialPack_KeyItemsMenuHeader);
            break;
        //dw ['.TMHM'];
        case TM_HM_POCKET:
        // TMHM:
            // LD_A(TM_HM_POCKET);
            // CALL(aInitPocket);
            InitPocket(TM_HM_POCKET);
            // CALL(aWaitBGMap_DrawPackGFX);
            WaitBGMap_DrawPackGFX();
            // FARCALL(aTMHMPocket);
            SafeCallGBAuto(aTMHMPocket);
            // LD_A_addr(wCurItem);
            // LD_addr_A(wCurItem);
            // RET;
            return;
    }


// DisplayPocket:
    // PUSH_HL;
    // CALL(aInitPocket);
    // POP_HL;
    // CALL(aCopyMenuHeader);
    // CALL(aScrollingMenu);
    ScrollingMenu_Conv();
    // RET;
}

void TutorialPack(void){
    // CALL(aDepositSellInitPackBuffers);
    DepositSellInitPackBuffers();
    // LD_A_addr(wInputType);
    // OR_A_A;
    // IF_Z goto loop;
    if(wram->wInputType != 0) {
        // FARCALL(av_DudeAutoInput_RightA);
        v_DudeAutoInput_RightA();
    }

    bool done;
    do {
    // loop:
        // CALL(aTutorialPack_RunJumptable);
        TutorialPack_RunJumptable();
        // CALL(aDepositSellTutorial_InterpretJoypad);
        done = DepositSellTutorial_InterpretJoypad();
        // IF_C goto loop;
    } while(!done);
    // XOR_A_A;  // FALSE
    // LD_addr_A(wPackUsedItem);
    wram->wPackUsedItem = FALSE;
    // RET;
}

void Pack_JumptableNext(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;
}

void Pack_GetJumptablePointer(void){
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;

}

void Pack_QuitNoScript(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // XOR_A_A;  // FALSE
    // LD_addr_A(wPackUsedItem);
    wram->wPackUsedItem = FALSE;
    // RET;
}

void Pack_QuitRunScript(void){
    // LD_HL(wJumptableIndex);
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // LD_A(TRUE);
    // LD_addr_A(wPackUsedItem);
    wram->wPackUsedItem = TRUE;
    // RET;
}

void Pack_PrintTextNoScroll(const txt_cmd_s* hl){
    // LD_A_addr(wOptions);
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_A(NO_TEXT_SCROLL);
    // LD_addr_A(wOptions);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aPrintText);
    PrintText_Conv2(hl);
    // POP_AF;
    // LD_addr_A(wOptions);
    wram->wOptions = options;
    // RET;
}

void WaitBGMap_DrawPackGFX(void){
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    return DrawPackGFX(wram->wCurPocket);
}

void DrawPackGFX(uint8_t pocket){
    // LD_A_addr(wCurPocket);
    // maskbits(NUM_POCKETS, 0);
    // LD_E_A;
    // LD_D(0);
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_TUTORIAL);
    // IF_Z goto male_dude;
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_NZ goto female;

    if(wram->wBattleType == BATTLETYPE_TUTORIAL
    || !bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F)) {
    // male_dude:
        // LD_HL(mPackGFXPointers);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_E_A;
        // LD_D_hl;
        // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x50);
        // LD_BC((BANK(aPackGFX) << 8) | 15);
        // CALL(aRequest2bpp);
        LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x50, PackGFX, PackGFXPointers[pocket & 3], 15);
        // RET;
        return;
    }

// female:
    // FARCALL(aDrawKrisPackGFX);
    DrawKrisPackGFX(pocket & 3);
    // RET;
}

const uint16_t PackGFXPointers[] = {
    // (15 * LEN_2BPP_TILE) * 1,  // ITEM_POCKET
    // (15 * LEN_2BPP_TILE) * 3,  // BALL_POCKET
    // (15 * LEN_2BPP_TILE) * 0,  // KEY_ITEM_POCKET
    // (15 * LEN_2BPP_TILE) * 2,  // TM_HM_POCKET
    [ITEM_POCKET]       = 15 * 1,
    [BALL_POCKET]       = 15 * 3,
    [KEY_ITEM_POCKET]   = 15 * 0,
    [TM_HM_POCKET]      = 15 * 2,
};

void Pack_InterpretJoypad(void){
    LD_HL(wMenuJoypad);
    LD_A_addr(wSwitchItem);
    AND_A_A;
    IF_NZ goto switching_item;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto a_button;
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto b_button;
    LD_A_hl;
    AND_A(D_LEFT);
    IF_NZ goto d_left;
    LD_A_hl;
    AND_A(D_RIGHT);
    IF_NZ goto d_right;
    LD_A_hl;
    AND_A(SELECT);
    IF_NZ goto select;
    SCF;
    RET;


a_button:
    AND_A_A;
    RET;


b_button:
    LD_A(PACKSTATE_QUITNOSCRIPT);
    LD_addr_A(wJumptableIndex);
    SCF;
    RET;


d_left:
    LD_A_B;
    LD_addr_A(wJumptableIndex);
    LD_addr_A(wPackJumptableIndex);
    PUSH_DE;
    LD_DE(SFX_SWITCH_POCKETS);
    CALL(aPlaySFX);
    POP_DE;
    SCF;
    RET;


d_right:
    LD_A_C;
    LD_addr_A(wJumptableIndex);
    LD_addr_A(wPackJumptableIndex);
    PUSH_DE;
    LD_DE(SFX_SWITCH_POCKETS);
    CALL(aPlaySFX);
    POP_DE;
    SCF;
    RET;


select:
    FARCALL(aSwitchItemsInBag);
    LD_HL(mAskItemMoveText);
    CALL(aPack_PrintTextNoScroll);
    SCF;
    RET;


switching_item:
    LD_A_hl;
    AND_A(A_BUTTON | SELECT);
    IF_NZ goto place_insert;
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto end_switch;
    SCF;
    RET;


place_insert:
    FARCALL(aSwitchItemsInBag);
    LD_DE(SFX_SWITCH_POKEMON);
    CALL(aWaitPlaySFX);
    LD_DE(SFX_SWITCH_POKEMON);
    CALL(aWaitPlaySFX);

end_switch:
    XOR_A_A;
    LD_addr_A(wSwitchItem);
    SCF;
    RET;

}

bool Pack_InterpretJoypad_Conv(uint8_t b, uint8_t c){
    // LD_HL(wMenuJoypad);
    // LD_A_addr(wSwitchItem);
    // AND_A_A;
    // IF_NZ goto switching_item;
    if(wram->wSwitchItem != 0) {
    // switching_item:
        // LD_A_hl;
        // AND_A(A_BUTTON | SELECT);
        // IF_NZ goto place_insert;
        if(wram->wMenuJoypad & (A_BUTTON | SELECT)) {
        // place_insert:
            // FARCALL(aSwitchItemsInBag);
            SafeCallGBAuto(aSwitchItemsInBag);
            // LD_DE(SFX_SWITCH_POKEMON);
            // CALL(aWaitPlaySFX);
            WaitPlaySFX_Conv(SFX_SWITCH_POKEMON);
            // LD_DE(SFX_SWITCH_POKEMON);
            // CALL(aWaitPlaySFX);
            WaitPlaySFX_Conv(SFX_SWITCH_POKEMON);

        end_switch:
            // XOR_A_A;
            // LD_addr_A(wSwitchItem);
            wram->wSwitchItem = 0;
            // SCF;
            // RET;
            return true;
        }
        // LD_A_hl;
        // AND_A(B_BUTTON);
        // IF_NZ goto end_switch;
        else if(wram->wMenuJoypad & B_BUTTON) {
            goto end_switch;
        }
        // SCF;
        // RET;
        return true;
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // IF_NZ goto a_button;
    if(wram->wMenuJoypad & A_BUTTON) {
    // a_button:
        // AND_A_A;
        // RET;
        return false;
    }
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // IF_NZ goto b_button;
    if(wram->wMenuJoypad & B_BUTTON) {
    // b_button:
        // LD_A(PACKSTATE_QUITNOSCRIPT);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = PACKSTATE_QUITNOSCRIPT;
        // SCF;
        // RET;
        return true;
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // IF_NZ goto d_left;
    if(wram->wMenuJoypad & D_LEFT) {
    // d_left:
        // LD_A_B;
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = b;
        // LD_addr_A(wPackJumptableIndex);
        wram->wPackJumptableIndex = b;
        // PUSH_DE;
        // LD_DE(SFX_SWITCH_POCKETS);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_SWITCH_POCKETS);
        // POP_DE;
        // SCF;
        // RET;
        return true;
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // IF_NZ goto d_right;
    if(wram->wMenuJoypad & D_RIGHT) {
    // d_right:
        // LD_A_C;
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = c;
        // LD_addr_A(wPackJumptableIndex);
        wram->wPackJumptableIndex = c;
        // PUSH_DE;
        // LD_DE(SFX_SWITCH_POCKETS);
        // CALL(aPlaySFX);
        PlaySFX_Conv(SFX_SWITCH_POCKETS);
        // POP_DE;
        // SCF;
        // RET;
        return true;
    }
    // LD_A_hl;
    // AND_A(SELECT);
    // IF_NZ goto select;
    if(wram->wMenuJoypad & SELECT) {
    // select:
        // FARCALL(aSwitchItemsInBag);
        SafeCallGBAuto(aSwitchItemsInBag);
        // LD_HL(mAskItemMoveText);
        // CALL(aPack_PrintTextNoScroll);
        Pack_PrintTextNoScroll(AskItemMoveText);
        // SCF;
        // RET;
        return true;
    }
    // SCF;
    // RET;
    return true;
}

void Pack_InitGFX(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_HL(mPackMenuGFX);
    // LD_DE(vTiles2);
    // LD_BC(0x60 * LEN_2BPP_TILE);
    // LD_A(BANK(aPackMenuGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, PackMenuGFX, 0, 0x60);
//  Background (blue if male, pink if female)
    // hlcoord(0, 1, wTilemap);
    // LD_BC(11 * SCREEN_WIDTH);
    // LD_A(0x24);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 1, wram->wTilemap), 11 * SCREEN_WIDTH, 0x24);
//  This is where the items themselves will be listed.
    // hlcoord(5, 1, wTilemap);
    // LD_BC((11 << 8) | 15);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(5, 1, wram->wTilemap), 15, 11);
//  ◀▶ POCKET       ▼▲ ITEMS
    // hlcoord(0, 0, wTilemap);
    // LD_A(0x28);
    // LD_C(SCREEN_WIDTH);

    for(uint8_t c = 0; c < SCREEN_WIDTH; ++c) {
    // loop:
        // LD_hli_A;
        // INC_A;
        // DEC_C;
        // IF_NZ goto loop;
        *coord(c, 0, wram->wTilemap) = 0x28 + c;
    }
    // CALL(aDrawPocketName);
    DrawPocketName(wram->wCurPocket);
    // CALL(aPlacePackGFX);
    PlacePackGFX();
//  Place the textbox for displaying the item description
    // hlcoord(0, SCREEN_HEIGHT - 4 - 2, wTilemap);
    // LD_BC((4 << 8) | SCREEN_WIDTH - 2);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, SCREEN_HEIGHT - 4 - 2, wram->wTilemap), 4, SCREEN_WIDTH - 2);
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // CALL(aDrawPackGFX);
    DrawPackGFX(wram->wCurPocket);
    // RET;
}

void PlacePackGFX(void){
    // hlcoord(0, 3, wTilemap);
    uint8_t* hl = coord(0, 3, wram->wTilemap);
    // LD_A(0x50);
    uint8_t a = 0x50;
    // LD_DE(SCREEN_WIDTH - 5);
    // LD_B(3);
    uint8_t b = 3;

    do {
    // row:
        // LD_C(5);
        uint8_t c = 5;

        do {
        // column:
            // LD_hli_A;
            // INC_A;
            *(hl++) = a++;
            // DEC_C;
            // IF_NZ goto column;
        } while(--c != 0);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH - 5;
        // DEC_B;
        // IF_NZ goto row;
    } while(--b != 0);
    // RET;
}

void DrawPocketName(uint8_t pocket){
    const char tilemap[] = "gfx/pack/pack_menu.tilemap";
//   //  5x12
//  the 5x3 pieces correspond to *_POCKET constants
// INCBIN "gfx/pack/pack_menu.tilemap"
    // LD_A_addr(wCurPocket);
// * 15
    // LD_D_A;
    // SWAP_A;
    // SUB_A_D;
    // LD_D(0);
    // LD_E_A;
    // LD_HL(mDrawPocketName_tilemap);
    asset_s a = LoadAsset(tilemap);
    // ADD_HL_DE;
    // LD_D_H;
    // LD_E_L;
    const uint8_t* de = (uint8_t*)a.ptr + (pocket * 15);
    // hlcoord(0, 7, wTilemap);
    uint8_t* hl = coord(0, 7, wram->wTilemap);
    // LD_C(3);
    uint8_t c = 3;

    do {
    // row:
        // LD_B(5);
        uint8_t b = 5;

        do {
        // col:
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            *(hl++) = *(de++);
            // DEC_B;
            // IF_NZ goto col;
        } while(--b != 0);
        // LD_A_C;
        // LD_C(SCREEN_WIDTH - 5);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH - 5;
        // LD_C_A;
        // DEC_C;
        // IF_NZ goto row;
    } while(--c != 0);
    FreeAsset(a);
    // RET;
}

void Pack_GetItemName(void){
    LD_A_addr(wCurItem);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    CALL(aCopyName1);
    RET;

}

void Pack_ClearTilemap(void){
//  //  unreferenced
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    LD_A(0x7f);
    CALL(aByteFill);
    RET;

}

void ClearPocketList(void){
    // hlcoord(5, 2, wTilemap);
    // LD_BC((10 << 8) | SCREEN_WIDTH - 5);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(5, 2, wram->wTilemap), SCREEN_WIDTH - 5, 10);
    // RET;
}

void Pack_InitColors(void){
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_B(SCGB_PACKPALS);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_PACKPALS);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

const struct MenuHeader ItemsPocketMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(7, 1, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_ENABLE_SELECT | STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP | STATICMENU_CURSOR,  // flags
        .scrollingMenu = {
            .flags = 0,
            //db ['5', '8'];  // rows, columns
            .rows = 5, .cols = 8,
            //db ['SCROLLINGMENU_ITEMS_QUANTITY'];  // item format
            .format = SCROLLINGMENU_ITEMS_QUANTITY,
        //dbw ['0', 'wNumItems']
            .list = wram_ptr(wNumItems),
        //dba ['PlaceMenuItemName']
            .func1 = PlaceMenuItemName_Conv,
        //dba ['PlaceMenuItemQuantity']
            .func2 = PlaceMenuItemQuantity_Conv,
        //dba ['UpdateItemDescription']
            .func3 = UpdateItemDescription,
        },
    },
    //db ['1'];  // default option
    .defaultOption = 1,
};

const struct MenuHeader PC_Mart_ItemsPocketMenuHeader = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord=menu_coords(7, 1, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData){
    // MenuData:
        .flags=STATICMENU_ENABLE_SELECT | STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP,  // flags
        .scrollingMenu = {
            .rows=5, .cols=8,  // rows, columns
            .format=SCROLLINGMENU_ITEMS_QUANTITY,  // item format
            //dbw ['0', 'wNumItems']
            .list=wram_ptr(wNumItems),
            //dba ['PlaceMenuItemName']
            .func1=PlaceMenuItemName_Conv,
            //dba ['PlaceMenuItemQuantity']
            .func2=PlaceMenuItemQuantity_Conv,
            //dba ['UpdateItemDescription']
            .func3=UpdateItemDescription,
        },
    },
    .defaultOption=1,  // default option
};

const struct MenuHeader KeyItemsPocketMenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(7, 1, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_ENABLE_SELECT | STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP | STATICMENU_CURSOR,  // flags
        .scrollingMenu = {
            //db ['5', '8'];  // rows, columns
            .rows = 5, .cols = 8,
            .format = SCROLLINGMENU_ITEMS_NORMAL,  // item format
            //dbw ['0', 'wNumKeyItems']
            .list = wram_ptr(wNumKeyItems),
            //dba ['PlaceMenuItemName']
            .func1 = PlaceMenuItemName_Conv,
            //dba ['PlaceMenuItemQuantity']
            .func2 = PlaceMenuItemQuantity_Conv,
            //dba ['UpdateItemDescription']
            .func3 = UpdateItemDescription,
        },
    },
    //db ['1'];  // default option
    .defaultOption = 1,
};

const struct MenuHeader PC_Mart_KeyItemsPocketMenuHeader = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord=menu_coords(7, 1, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags=STATICMENU_ENABLE_SELECT | STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP,  // flags
        .scrollingMenu = {
            .rows=5, .cols=8,  // rows, columns
            .format=SCROLLINGMENU_ITEMS_NORMAL,  // item format
            //dbw ['0', 'wNumKeyItems']
            .list = wram_ptr(wNumKeyItems),
            //dba ['PlaceMenuItemName']
            .func1=PlaceMenuItemName_Conv,
            //dba ['PlaceMenuItemQuantity']
            .func2=PlaceMenuItemQuantity_Conv,
            //dba ['UpdateItemDescription']
            .func3=UpdateItemDescription,
        },
    },
    .defaultOption=1,  // default option
};

const struct MenuHeader BallsPocketMenuHeader = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(7, 1, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData){
    // MenuData:
        .flags = STATICMENU_ENABLE_SELECT | STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP | STATICMENU_CURSOR,  // flags
        .scrollingMenu = {
            .rows=5, .cols=8,  // rows, columns
            .format=SCROLLINGMENU_ITEMS_QUANTITY,  // item format
            //dbw ['0', 'wNumBalls']
            .list = wram_ptr(wNumBalls),
            //dba ['PlaceMenuItemName']
            .func1 = PlaceMenuItemName_Conv,
            //dba ['PlaceMenuItemQuantity']
            .func2 = PlaceMenuItemQuantity_Conv,
            //dba ['UpdateItemDescription']
            .func3 = UpdateItemDescription,
        },
    },
    .defaultOption = 1,  // default option
};

const struct MenuHeader PC_Mart_BallsPocketMenuHeader = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord=menu_coords(7, 1, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
        .flags=STATICMENU_ENABLE_SELECT | STATICMENU_ENABLE_LEFT_RIGHT | STATICMENU_ENABLE_START | STATICMENU_WRAP,  // flags
        .scrollingMenu = {
            .rows=5, .cols=8,  // rows, columns
            .format=SCROLLINGMENU_ITEMS_QUANTITY,  // item format
            //dbw ['0', 'wNumBalls']
            .list = wram_ptr(wNumBalls),
            //dba ['PlaceMenuItemName']
            .func1=PlaceMenuItemName_Conv,
            //dba ['PlaceMenuItemQuantity']
            .func2=PlaceMenuItemQuantity_Conv,
            //dba ['UpdateItemDescription']
            .func3=UpdateItemDescription,
        },
    },
    .defaultOption=1,  // default option
};

//  //  unreferenced
const txt_cmd_s PackNoItemText[] = {
    text_far(v_PackNoItemText)
    text_end
};

const txt_cmd_s AskThrowAwayText[] = {
    text_far(v_AskThrowAwayText)
    text_end
};

const txt_cmd_s AskQuantityThrowAwayText[] = {
    text_far(v_AskQuantityThrowAwayText)
    text_end
};

const txt_cmd_s ThrewAwayText[] = {
    text_far(v_ThrewAwayText)
    text_end
};

const txt_cmd_s OakThisIsntTheTimeText[] = {
    text_far(v_OakThisIsntTheTimeText)
    text_end
};

const txt_cmd_s YouDontHaveAMonText[] = {
    text_far(v_YouDontHaveAMonText)
    text_end
};

const txt_cmd_s RegisteredItemText[] = {
    text_far(v_RegisteredItemText)
    text_end
};

const txt_cmd_s CantRegisterText[] = {
    text_far(v_CantRegisterText)
    text_end
};

const txt_cmd_s AskItemMoveText[] = {
    text_far(v_AskItemMoveText)
    text_end
};

const txt_cmd_s PackEmptyText[] = {
    text_far(v_PackEmptyText)
    text_end
};

const txt_cmd_s YouCantUseItInABattleText[] = {
//  //  unreferenced
    text_far(v_YouCantUseItInABattleText)
    text_end
};

const char PackMenuGFX[] = "gfx/pack/pack_menu.png";
const char PackGFX[] = "gfx/pack/pack.png";
