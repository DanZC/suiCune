#include "../../constants.h"
#include "items.h"
#include "../../data/items/attributes.h"

void v_ReceiveItem(void){
    CALL(aDoesHLEqualNumItems);
    JP_NZ (mPutItemInPocket);
    PUSH_HL;
    CALL(aCheckItemPocket);
    POP_DE;
    LD_A_addr(wItemAttributeValue);
    DEC_A;
    LD_HL(mv_ReceiveItem_Pockets);
    RST(aJumpTable);
    RET;


// Pockets:
//  entries correspond to item types
    //dw ['.Item'];
    //dw ['.KeyItem'];
    //dw ['.Ball'];
    //dw ['.TMHM'];


Item:
    LD_H_D;
    LD_L_E;
    JP(mPutItemInPocket);


KeyItem:
    LD_H_D;
    LD_L_E;
    JP(mReceiveKeyItem);


Ball:
    LD_HL(wNumBalls);
    JP(mPutItemInPocket);


TMHM:
    LD_H_D;
    LD_L_E;
    LD_A_addr(wCurItem);
    LD_C_A;
    CALL(aGetTMHMNumber);
    JP(mReceiveTMHM);

}

void v_TossItem(void){
    CALL(aDoesHLEqualNumItems);
    IF_NZ goto remove;
    PUSH_HL;
    CALL(aCheckItemPocket);
    POP_DE;
    LD_A_addr(wItemAttributeValue);
    DEC_A;
    LD_HL(mv_TossItem_Pockets);
    RST(aJumpTable);
    RET;


// Pockets:
//  entries correspond to item types
    //dw ['.Item'];
    //dw ['.KeyItem'];
    //dw ['.Ball'];
    //dw ['.TMHM'];


Ball:
    LD_HL(wNumBalls);
    JP(mRemoveItemFromPocket);


TMHM:
    LD_H_D;
    LD_L_E;
    LD_A_addr(wCurItem);
    LD_C_A;
    CALL(aGetTMHMNumber);
    JP(mTossTMHM);


KeyItem:
    LD_H_D;
    LD_L_E;
    JP(mTossKeyItem);


Item:
    LD_H_D;
    LD_L_E;


remove:
    JP(mRemoveItemFromPocket);

}

void v_CheckItem(void){
    CALL(aDoesHLEqualNumItems);
    IF_NZ goto nope;
    PUSH_HL;
    CALL(aCheckItemPocket);
    POP_DE;
    LD_A_addr(wItemAttributeValue);
    DEC_A;
    LD_HL(mv_CheckItem_Pockets);
    RST(aJumpTable);
    RET;


// Pockets:
//  entries correspond to item types
    //dw ['.Item'];
    //dw ['.KeyItem'];
    //dw ['.Ball'];
    //dw ['.TMHM'];


Ball:
    LD_HL(wNumBalls);
    JP(mCheckTheItem);


TMHM:
    LD_H_D;
    LD_L_E;
    LD_A_addr(wCurItem);
    LD_C_A;
    CALL(aGetTMHMNumber);
    JP(mCheckTMHM);


KeyItem:
    LD_H_D;
    LD_L_E;
    JP(mCheckKeyItems);


Item:
    LD_H_D;
    LD_L_E;


nope:
    JP(mCheckTheItem);

}

bool v_CheckItem_Conv(item_t item, item_t* hl){
    // CALL(aDoesHLEqualNumItems);
    // IF_NZ goto nope;
    if(hl != wram->wItems) {
        // PUSH_HL;
        // CALL(aCheckItemPocket);
        uint8_t pocket = CheckItemPocket_Conv(item);
        // POP_DE;
        // LD_A_addr(wItemAttributeValue);
        // DEC_A;
        // LD_HL(mv_CheckItem_Pockets);
        // RST(aJumpTable);
        switch(pocket)
        {
            case ITEM_POCKET: goto Item;
            case KEY_ITEM_POCKET: goto KeyItem;
            case BALL_POCKET: goto Ball;
            case TM_HM_POCKET: goto TMHM;
        }
        // RET;
        return false;


    // Pockets:
    //  entries correspond to item types
        //dw ['.Item'];
        //dw ['.KeyItem'];
        //dw ['.Ball'];
        //dw ['.TMHM'];


    Ball:
        // LD_HL(wNumBalls);
        // JP(mCheckTheItem);
        return CheckTheItem_Conv(item, wram->wBalls);


    TMHM:
        // LD_H_D;
        // LD_L_E;
        // LD_A_addr(wCurItem);
        // LD_C_A;
        // CALL(aGetTMHMNumber);
        // JP(mCheckTMHM);
        return CheckTMHM_Conv(GetTMHMNumber_Conv(item));

    KeyItem:
        // LD_H_D;
        // LD_L_E;
        // JP(mCheckKeyItems);
        return CheckKeyItems_Conv(pocket);


    Item:
        ;
        // LD_H_D;
        // LD_L_E;
    }

// nope:
    // JP(mCheckTheItem);
    return CheckTheItem_Conv(item, wram->wItems);
}

void DoesHLEqualNumItems(void){
    LD_A_L;
    CP_A(LOW(wNumItems));
    RET_NZ ;
    LD_A_H;
    CP_A(HIGH(wNumItems));
    RET;

}

bool DoesHLEqualNumItems_Conv(uint16_t hl){
    // LD_A_L;
    // CP_A(LOW(wNumItems));
    // RET_NZ ;
    // LD_A_H;
    // CP_A(HIGH(wNumItems));
    // RET;
    return hl == wram->wNumItems;
}

void GetPocketCapacity(void){
    LD_C(MAX_ITEMS);
    LD_A_E;
    CP_A(LOW(wNumItems));
    IF_NZ goto not_bag;
    LD_A_D;
    CP_A(HIGH(wNumItems));
    RET_Z ;


not_bag:
    LD_C(MAX_PC_ITEMS);
    LD_A_E;
    CP_A(LOW(wNumPCItems));
    IF_NZ goto not_pc;
    LD_A_D;
    CP_A(HIGH(wNumPCItems));
    RET_Z ;


not_pc:
    LD_C(MAX_BALLS);
    RET;

}

uint8_t GetPocketCapacity_Conv(item_t* pocket){
    // LD_C(MAX_ITEMS);
    // LD_A_E;
    // CP_A(LOW(wNumItems));
    // IF_NZ goto not_bag;
    // LD_A_D;
    // CP_A(HIGH(wNumItems));
    // RET_Z ;
    if(pocket == wram->wItems) {
        return MAX_ITEMS;
    }

// not_bag:
    // LD_C(MAX_PC_ITEMS);
    // LD_A_E;
    // CP_A(LOW(wNumPCItems));
    // IF_NZ goto not_pc;
    // LD_A_D;
    // CP_A(HIGH(wNumPCItems));
    // RET_Z ;
    if(pocket == wram->wPCItems) {
        return MAX_PC_ITEMS;
    }


// not_pc:
    // LD_C(MAX_BALLS);
    // RET;
    return MAX_BALLS;
}

void PutItemInPocket(void){
    LD_D_H;
    LD_E_L;
    INC_HL;
    LD_A_addr(wCurItem);
    LD_C_A;
    LD_B(0);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto terminator;
    CP_A_C;
    IF_NZ goto next;
    LD_A(MAX_ITEM_STACK);
    SUB_A_hl;
    ADD_A_B;
    LD_B_A;
    LD_A_addr(wItemQuantityChange);
    CP_A_B;
    IF_Z goto ok;
    IF_C goto ok;


next:
    INC_HL;
    goto loop;


terminator:
    CALL(aGetPocketCapacity);
    LD_A_de;
    CP_A_C;
    IF_C goto ok;
    AND_A_A;
    RET;


ok:
    LD_H_D;
    LD_L_E;
    LD_A_addr(wCurItem);
    LD_C_A;
    LD_A_addr(wItemQuantityChange);
    LD_addr_A(wItemQuantity);

loop2:
    INC_HL;
    LD_A_hli;
    CP_A(-1);
    IF_Z goto terminator2;
    CP_A_C;
    IF_NZ goto loop2;
    LD_A_addr(wItemQuantity);
    ADD_A_hl;
    CP_A(MAX_ITEM_STACK + 1);
    IF_NC goto newstack;
    LD_hl_A;
    goto done;


newstack:
    LD_hl(MAX_ITEM_STACK);
    SUB_A(MAX_ITEM_STACK);
    LD_addr_A(wItemQuantity);
    goto loop2;


terminator2:
    DEC_HL;
    LD_A_addr(wCurItem);
    LD_hli_A;
    LD_A_addr(wItemQuantity);
    LD_hli_A;
    LD_hl(-1);
    LD_H_D;
    LD_L_E;
    INC_hl;


done:
    SCF;
    RET;

}

void RemoveItemFromPocket(void){
    LD_D_H;
    LD_E_L;
    LD_A_hli;
    LD_C_A;
    LD_A_addr(wCurItemQuantity);
    CP_A_C;
    IF_NC goto ok;  // memory
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_addr(wCurItem);
    CP_A_hl;
    INC_HL;
    IF_Z goto skip;
    LD_H_D;
    LD_L_E;
    INC_HL;


ok:
    LD_A_addr(wCurItem);
    LD_B_A;

loop:
    LD_A_hli;
    CP_A_B;
    IF_Z goto skip;
    CP_A(-1);
    IF_Z goto nope;
    INC_HL;
    goto loop;


skip:
    LD_A_addr(wItemQuantityChange);
    LD_B_A;
    LD_A_hl;
    SUB_A_B;
    IF_C goto nope;
    LD_hl_A;
    LD_addr_A(wItemQuantity);
    AND_A_A;
    IF_NZ goto yup;
    DEC_HL;
    LD_B_H;
    LD_C_L;
    INC_HL;
    INC_HL;

loop2:
    LD_A_hli;
    LD_bc_A;
    INC_BC;
    CP_A(-1);
    IF_NZ goto loop2;
    LD_H_D;
    LD_L_E;
    DEC_hl;


yup:
    SCF;
    RET;


nope:
    AND_A_A;
    RET;

}

void CheckTheItem(void){
    LD_A_addr(wCurItem);
    LD_C_A;

loop:
    INC_HL;
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done;
    CP_A_C;
    IF_NZ goto loop;
    SCF;
    RET;


done:
    AND_A_A;
    RET;

}

bool CheckTheItem_Conv(item_t item, item_t* hl){
    // LD_A_addr(wCurItem);
    // LD_C_A;
    item_t a;

    do {
    // loop:
        // INC_HL;
        // LD_A_hli;
        a = *(hl++);
        // CP_A(-1);
        // IF_Z goto done;
        if(a == (item_t)-1)
            return false;
        // CP_A_C;
        // IF_NZ goto loop;
    } while(a != item);
    // SCF;
    // RET;
    return true;


// done:
    // AND_A_A;
    // RET;

}

void ReceiveKeyItem(void){
    LD_HL(wNumKeyItems);
    LD_A_hli;
    CP_A(MAX_KEY_ITEMS);
    IF_NC goto nope;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wCurItem);
    LD_hli_A;
    LD_hl(-1);
    LD_HL(wNumKeyItems);
    INC_hl;
    SCF;
    RET;


nope:
    AND_A_A;
    RET;

}

bool ReceiveKeyItem_Conv(item_t item){
    // LD_HL(wNumKeyItems);
    // LD_A_hli;
    // CP_A(MAX_KEY_ITEMS);
    // IF_NC goto nope;
    if(wram->wNumKeyItems >= MAX_KEY_ITEMS)
        return false;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_addr(wCurItem);
    // LD_hli_A;
    wram->wKeyItems[wram->wNumKeyItems++] = item;
    // LD_hl(-1);
    wram->wKeyItems[wram->wNumKeyItems] = (item_t)-1;
    // LD_HL(wNumKeyItems);
    // INC_hl;
    // SCF;
    // RET;
    return true;

// nope:
    // AND_A_A;
    // RET;
}

void TossKeyItem(void){
    LD_A_addr(wCurItemQuantity);
    LD_E_A;
    LD_D(0);
    LD_HL(wNumKeyItems);
    LD_A_hl;
    CP_A_E;
    IF_NC goto ok;
    CALL(aTossKeyItem_Toss);
    RET_NC ;
    goto ok2;


ok:
    DEC_hl;
    INC_HL;
    ADD_HL_DE;


ok2:
    LD_D_H;
    LD_E_L;
    INC_HL;

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    CP_A(-1);
    IF_NZ goto loop;
    SCF;
    RET;


Toss:
    LD_HL(wNumKeyItems);
    LD_A_addr(wCurItem);
    LD_C_A;

loop3:
    INC_HL;
    LD_A_hl;
    CP_A_C;
    IF_Z goto ok3;
    CP_A(-1);
    IF_NZ goto loop3;
    XOR_A_A;
    RET;


ok3:
    LD_A_addr(wNumKeyItems);
    DEC_A;
    LD_addr_A(wNumKeyItems);
    SCF;
    RET;

}

void CheckKeyItems(void){
    LD_A_addr(wCurItem);
    LD_C_A;
    LD_HL(wKeyItems);

loop:
    LD_A_hli;
    CP_A_C;
    IF_Z goto done;
    CP_A(-1);
    IF_NZ goto loop;
    AND_A_A;
    RET;


done:
    SCF;
    RET;

}

bool CheckKeyItems_Conv(uint8_t c){
    // LD_A_addr(wCurItem);
    // LD_C_A;
    // LD_HL(wKeyItems);
    
    // uint8_t c = wram->wCurItem;
    item_t* hl = wram->wKeyItems;
    uint8_t a;

    do {
    // loop:
        // LD_A_hli;
        // CP_A_C;
        // IF_Z goto done;
        a = *(hl++);
        if(a == c)
            return true;
        // CP_A(-1);
        // IF_NZ goto loop;
    } while(a != 0xff);
    // AND_A_A;
    // RET;
    return false;


// done:
    // SCF;
    // RET;
}

void ReceiveTMHM(void){
    DEC_C;
    LD_B(0);
    LD_HL(wTMsHMs);
    ADD_HL_BC;
    LD_A_addr(wItemQuantityChange);
    ADD_A_hl;
    CP_A(MAX_ITEM_STACK + 1);
    IF_NC goto toomany;
    LD_hl_A;
    SCF;
    RET;


toomany:
    AND_A_A;
    RET;

}

void TossTMHM(void){
    DEC_C;
    LD_B(0);
    LD_HL(wTMsHMs);
    ADD_HL_BC;
    LD_A_addr(wItemQuantityChange);
    LD_B_A;
    LD_A_hl;
    SUB_A_B;
    IF_C goto nope;
    LD_hl_A;
    LD_addr_A(wItemQuantity);
    IF_NZ goto yup;
    LD_A_addr(wTMHMPocketScrollPosition);
    AND_A_A;
    IF_Z goto yup;
    DEC_A;
    LD_addr_A(wTMHMPocketScrollPosition);


yup:
    SCF;
    RET;


nope:
    AND_A_A;
    RET;

}

void CheckTMHM(void){
    DEC_C;
    LD_B(0x0);
    LD_HL(wTMsHMs);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    SCF;
    RET;

}

bool CheckTMHM_Conv(uint8_t c){
    // DEC_C;
    // LD_B(0x0);
    // LD_HL(wTMsHMs);
    uint8_t* hl = wram->wTMsHMs;
    // ADD_HL_BC;
    // LD_A_hl;
    uint8_t a = hl[c - 1];
    // AND_A_A;
    // RET_Z ;
    if(a == 0)
        return false;
    // SCF;
    // RET;
    return true;
}

void GetTMHMNumber(void){
//  Return the number of a TM/HM by item id c.
    LD_A_C;
//  Skip any dummy items.
    CP_A(ITEM_C3);  // TM04-05
    IF_C goto done;
    CP_A(ITEM_DC);  // TM28-29
    IF_C goto skip;
    DEC_A;

skip:
    DEC_A;

done:
    SUB_A(TM01);
    INC_A;
    LD_C_A;
    RET;

}

//  Return the number of a TM/HM by item id c.
uint8_t GetTMHMNumber_Conv(item_t c){
    // LD_A_C;
//  Skip any dummy items.
    // CP_A(ITEM_C3);  // TM04-05
    // IF_C goto done;
    if(c >= ITEM_C3) {
        // CP_A(ITEM_DC);  // TM28-29
        // IF_C goto skip;
        if(c >= ITEM_DC) {
            // DEC_A;
            c--;
        }
    // skip:
        // DEC_A;
        c--;
    }

// done:
    // SUB_A(TM01);
    // INC_A;
    // LD_C_A;
    // RET;
    return (c - TM01) + 1;
}

void GetNumberedTMHM(void){
//  Return the item id of a TM/HM by number c.
    LD_A_C;
//  Skip any gaps.
    CP_A(ITEM_C3 - (TM01 - 1));
    IF_C goto done;
    CP_A(ITEM_DC - (TM01 - 1) - 1);
    IF_C goto skip_one;
//  skip two
    INC_A;

skip_one:
    INC_A;

done:
    ADD_A(TM01);
    DEC_A;
    LD_C_A;
    RET;

}

void v_CheckTossableItem(void){
//  Return 1 in wItemAttributeValue and carry if wCurItem can't be removed from the bag.
    LD_A(ITEMATTR_PERMISSIONS);
    CALL(aGetItemAttr);
    BIT_A(CANT_TOSS_F);
    JR_NZ (mItemAttr_ReturnCarry);
    AND_A_A;
    RET;

}

//  Return false if wCurItem can't be removed from the bag.
bool v_CheckTossableItem_Conv(item_t item){
    // LD_A(ITEMATTR_PERMISSIONS);
    // CALL(aGetItemAttr);
    if(bit_test(ItemAttributes[item].permissions, CANT_TOSS_F))
        return false;
    // BIT_A(CANT_TOSS_F);
    // JR_NZ (mItemAttr_ReturnCarry);
    // AND_A_A;
    // RET;
    return true;
}

void CheckSelectableItem(void){
//  Return 1 in wItemAttributeValue and carry if wCurItem can't be selected.
    LD_A(ITEMATTR_PERMISSIONS);
    CALL(aGetItemAttr);
    BIT_A(CANT_SELECT_F);
    JR_NZ (mItemAttr_ReturnCarry);
    AND_A_A;
    RET;

}

//  Return false if item can't be selected.
bool CheckSelectableItem_Conv(item_t item){
    // LD_A(ITEMATTR_PERMISSIONS);
    // CALL(aGetItemAttr);
    // BIT_A(CANT_SELECT_F);
    // JR_NZ (mItemAttr_ReturnCarry);
    if(bit_test(ItemAttributes[item].permissions, CANT_SELECT_F))
        return false;
    // AND_A_A;
    // RET;
    return true;
}

void CheckItemPocket(void){
//  Return the pocket for wCurItem in wItemAttributeValue.
    LD_A(ITEMATTR_POCKET);
    CALL(aGetItemAttr);
    AND_A(0xf);
    LD_addr_A(wItemAttributeValue);
    RET;

}

//  Return the pocket for wCurItem in wItemAttributeValue.
uint8_t CheckItemPocket_Conv(item_t item){
    // LD_A(ITEMATTR_POCKET);
    // CALL(aGetItemAttr);
    // AND_A(0xf);
    // LD_addr_A(wItemAttributeValue);
    // RET;
    return ItemAttributes[item].pocket & 0xf;
}

void CheckItemContext(void){
//  Return the context for wCurItem in wItemAttributeValue.
    LD_A(ITEMATTR_HELP);
    CALL(aGetItemAttr);
    AND_A(0xf);
    LD_addr_A(wItemAttributeValue);
    RET;

}

//  Return the context for wCurItem in wItemAttributeValue.
uint8_t CheckItemContext_Conv(item_t item){
    // LD_A(ITEMATTR_HELP);
    // CALL(aGetItemAttr);
    // AND_A(0xf);
    // LD_addr_A(wItemAttributeValue);
    // RET;
    return ItemAttributes[item].helpBattle;
}

void CheckItemMenu(void){
//  Return the menu for wCurItem in wItemAttributeValue.
    LD_A(ITEMATTR_HELP);
    CALL(aGetItemAttr);
    SWAP_A;
    AND_A(0xf);
    LD_addr_A(wItemAttributeValue);
    RET;

}

//  Return the menu for wCurItem in wItemAttributeValue.
uint8_t CheckItemMenu_Conv(item_t item){
    // LD_A(ITEMATTR_HELP);
    // CALL(aGetItemAttr);
    // SWAP_A;
    // AND_A(0xf);
    // LD_addr_A(wItemAttributeValue);
    // RET;
    return ItemAttributes[item].helpField;
}

void GetItemAttr(void){
//  Get attribute a of wCurItem.

    PUSH_HL;
    PUSH_BC;

    LD_HL(mItemAttributes);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;

    XOR_A_A;
    LD_addr_A(wItemAttributeValue);

    LD_A_addr(wCurItem);
    DEC_A;
    LD_C_A;
    LD_A(ITEMATTR_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aItemAttributes));
    CALL(aGetFarByte);

    POP_BC;
    POP_HL;
    RET;

}

void ItemAttr_ReturnCarry(void){
    LD_A(1);
    LD_addr_A(wItemAttributeValue);
    SCF;
    RET;

}

void GetItemPrice(void){
//  Return the price of wCurItem in de.
    PUSH_HL;
    PUSH_BC;
    LD_A(ITEMATTR_PRICE_LO);
    CALL(aGetItemAttr);
    LD_E_A;
    LD_A(ITEMATTR_PRICE_HI);
    CALL(aGetItemAttr);
    LD_D_A;
    POP_BC;
    POP_HL;
    RET;

}

//  Return the price of wCurItem in de.
uint16_t GetItemPrice_Conv(item_t item) {
    // PUSH_HL;
    // PUSH_BC;
    // LD_A(ITEMATTR_PRICE_LO);
    // CALL(aGetItemAttr);
    // LD_E_A;
    // LD_A(ITEMATTR_PRICE_HI);
    // CALL(aGetItemAttr);
    // LD_D_A;
    // POP_BC;
    // POP_HL;
    // RET;
    return ItemAttributes[item].price;
}
