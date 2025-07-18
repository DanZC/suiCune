#include "../../constants.h"
#include "select_menu.h"
#include "../../home/map.h"
#include "../../home/joypad.h"
#include "../../home/window.h"
#include "../../home/item.h"
#include "../pokemon/mon_menu.h"
#include "../items/items.h"
#include "../../data/text/common.h"

static const txt_cmd_s MayRegisterItemText[] = {
    text_far(v_MayRegisterItemText)
    text_end
};

bool SelectMenu(void){
    // CALL(aCheckRegisteredItem);
    // IF_C goto NotRegistered;
    if(!CheckRegisteredItem()) {
    // NotRegistered:
        // CALL(aOpenText);
        OpenText();
        // LD_B(BANK(aMayRegisterItemText));
        // LD_HL(mMayRegisterItemText);
        // CALL(aMapTextbox);
        MapTextbox(MayRegisterItemText);
        // CALL(aWaitButton);
        WaitButton();
        // JP(mCloseText);
        CloseText();
        return false;
    }
    // JP(mUseRegisteredItem);
    return UseRegisteredItem();
}

static bool CheckRegisteredItem_CheckRegisteredNo(uint8_t count) {
    // LD_A_addr(wWhichRegisteredItem);
    // AND_A(REGISTERED_NUMBER);
    // DEC_A;
    // CP_A_hl;
    // IF_NC goto NotEnoughItems;
    if((gPlayer.whichRegisteredItem & REGISTERED_NUMBER) - 1 >= count) {
    // NotEnoughItems:
        // SCF;
        // RET;
        return true;
    }
    // LD_addr_A(wCurItemQuantity);
    wram->wCurItemQuantity = (gPlayer.whichRegisteredItem & REGISTERED_NUMBER) - 1;
    // AND_A_A;
    // RET;
    return false;
}

static bool CheckRegisteredItem_IsSameItem(item_t hl) {
    // LD_A_addr(wRegisteredItem);
    // CP_A_hl;
    // IF_NZ goto NotSameItem;
    if(gPlayer.registeredItem != hl) {
    // NotSameItem:
        // SCF;
        // RET;
        return false;
    }
    // LD_addr_A(wCurItem);
    wram->wCurItem = hl;
    // AND_A_A;
    // RET;
    return true;
}

bool CheckRegisteredItem(void){
    // LD_A_addr(wWhichRegisteredItem);
    // AND_A_A;
    // IF_Z goto NoRegisteredItem;
    if(gPlayer.whichRegisteredItem != NO_ITEM) {
        // AND_A(REGISTERED_POCKET);
        // RLCA;
        // RLCA;
        // LD_HL(mCheckRegisteredItem_Pockets);
        // RST(aJumpTable);
        // RET;


    // Pockets:
    //  entries correspond to *_POCKET constants
        switch((gPlayer.whichRegisteredItem & REGISTERED_POCKET) >> 6) {
            //dw ['.CheckItem'];
            default:
            case ITEM_POCKET:
            // CheckItem:
                // LD_HL(wNumItems);
                // CALL(aCheckRegisteredItem_CheckRegisteredNo);
                // IF_C goto NoRegisteredItem;
                if(CheckRegisteredItem_CheckRegisteredNo(gPlayer.numItems))
                    break;
                // INC_HL;
                // LD_E_A;
                // LD_D(0);
                // ADD_HL_DE;
                // ADD_HL_DE;
                // CALL(aCheckRegisteredItem_IsSameItem);
                // IF_C goto NoRegisteredItem;
                if(!CheckRegisteredItem_IsSameItem(gPlayer.items[wram->wCurItemQuantity * 2]))
                    break;
                // AND_A_A;
                // RET;
                return true;
            //dw ['.CheckBall'];
            case BALL_POCKET:
            // CheckBall:
                // LD_HL(wNumBalls);
                // CALL(aCheckRegisteredItem_CheckRegisteredNo);
                // IF_NC goto NoRegisteredItem;
                if(CheckRegisteredItem_CheckRegisteredNo(gPlayer.numBalls))
                    break;
                // INC_HL;
                // LD_E_A;
                // LD_D(0);
                // ADD_HL_DE;
                // ADD_HL_DE;
                // CALL(aCheckRegisteredItem_IsSameItem);
                // IF_C goto NoRegisteredItem;
                if(!CheckRegisteredItem_IsSameItem(gPlayer.balls[wram->wCurItemQuantity * 2]))
                    break;
                // RET;
                return true;
            //dw ['.CheckKeyItem'];
            case KEY_ITEM_POCKET:
            // CheckKeyItem:
                // LD_A_addr(wRegisteredItem);
                // LD_HL(wKeyItems);
                // LD_DE(1);
                // CALL(aIsInArray);
                // IF_NC goto NoRegisteredItem;
                for(uint32_t i = 0; gPlayer.keyItems[i] != (item_t)-1; ++i) {
                    if(gPlayer.keyItems[i] == gPlayer.registeredItem) {
                        // LD_A_addr(wRegisteredItem);
                        // LD_addr_A(wCurItem);
                        wram->wCurItem = gPlayer.registeredItem;
                        // AND_A_A;
                        // RET;
                        return true;
                    }
                }
                break;
            //dw ['.CheckTMHM'];
            case TM_HM_POCKET:
            // CheckTMHM:
                // goto NoRegisteredItem;
                break;
        }
    }

// NoRegisteredItem:
    // XOR_A_A;
    // LD_addr_A(wWhichRegisteredItem);
    gPlayer.whichRegisteredItem = NO_ITEM;
    // LD_addr_A(wRegisteredItem);
    gPlayer.registeredItem = NO_ITEM;
    // SCF;
    // RET;
    return false;
}

bool UseRegisteredItem(void){
    // FARCALL(aCheckItemMenu);
    // LD_A_addr(wItemAttributeValue);
    uint8_t menu = CheckItemMenu(wram->wCurItem);
    // LD_HL(mUseRegisteredItem_SwitchTo);
    // RST(aJumpTable);
    // RET;


SwitchTo:
//  entries correspond to ITEMMENU_* constants
    switch(menu) {
    //dw ['.CantUse'];
    default:
    case ITEMMENU_NOUSE:
    // CantUse:
        // CALL(aRefreshScreen);
        RefreshScreen();
        goto _cantuse;
    //dw ['.NoFunction'];
    //dw ['.NoFunction'];
    //dw ['.NoFunction'];
    case 1:
    case 2:
    case 3:
    // NoFunction:
        // CALL(aOpenText);
        OpenText();
        // CALL(aCantUseItem);
        CantUseItem();
        // CALL(aCloseText);
        CloseText();
        // AND_A_A;
        // RET;
        return false;
    //dw ['.Current'];
    case ITEMMENU_CURRENT:
    // Current:
        // CALL(aOpenText);
        OpenText();
        // CALL(aDoItemEffect);
        DoItemEffect();
        // CALL(aCloseText);
        CloseText();
        // AND_A_A;
        // RET;
        return false;
    //dw ['.Party'];
    case ITEMMENU_PARTY:
    // Party:
        // CALL(aRefreshScreen);
        RefreshScreen();
        // CALL(aFadeToMenu);
        FadeToMenu();
        // CALL(aDoItemEffect);
        DoItemEffect();
        // CALL(aCloseSubmenu);
        CloseSubmenu();
        // CALL(aCloseText);
        CloseText();
        // AND_A_A;
        // RET;
        return false;
    //dw ['.Overworld'];
    case ITEMMENU_CLOSE:
    // Overworld:
        // CALL(aRefreshScreen);
        RefreshScreen();
        // LD_A(1);
        // LD_addr_A(wUsingItemWithSelect);
        wram->wUsingItemWithSelect = TRUE;
        // CALL(aDoItemEffect);
        DoItemEffect();
        // XOR_A_A;
        // LD_addr_A(wUsingItemWithSelect);
        wram->wUsingItemWithSelect = FALSE;
        // LD_A_addr(wItemEffectSucceeded);
        // CP_A(1);
        // IF_NZ goto _cantuse;
        if(wram->wItemEffectSucceeded != 1) {
        _cantuse:
            // CALL(aCantUseItem);
            CantUseItem();
            // CALL(aCloseText);
            CloseText();
            // AND_A_A;
            // RET;
            return false;
        }
        // SCF;
        // LD_A(HMENURETURN_SCRIPT);
        // LDH_addr_A(hMenuReturn);
        hram.hMenuReturn = HMENURETURN_SCRIPT;
        // RET;
        return true;
    }
}
