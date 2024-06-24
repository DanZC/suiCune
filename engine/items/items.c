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

bool v_ReceiveItem_Conv(item_pocket_s* hl, item_t a, uint8_t count){
    // CALL(aDoesHLEqualNumItems);
    // JP_NZ (mPutItemInPocket);
    if(hl != (item_pocket_s*)&wram->wNumItems)
        return PutItemInPocket_Conv(hl, a, count);
    // PUSH_HL;
    // CALL(aCheckItemPocket);
    uint8_t pocket = CheckItemPocket_Conv(a);
    // POP_DE;
    // LD_A_addr(wItemAttributeValue);
    // DEC_A;
    // LD_HL(mv_ReceiveItem_Pockets);
    // RST(aJumpTable);
    // RET;
    switch(pocket) {
    // Pockets:
    //  entries correspond to item types
        //dw ['.Item'];
        //dw ['.KeyItem'];
        //dw ['.Ball'];
        //dw ['.TMHM'];
    case ITEM:
    // Item:
        // LD_H_D;
        // LD_L_E;
        // JP(mPutItemInPocket);
        return PutItemInPocket_Conv(hl, a, count);

    case KEY_ITEM:
    // KeyItem:
        // LD_H_D;
        // LD_L_E;
        // JP(mReceiveKeyItem);
        return ReceiveKeyItem_Conv(a);

    case BALL:
    // Ball:
        // LD_HL(wNumBalls);
        // JP(mPutItemInPocket);
        return PutItemInPocket_Conv((item_pocket_s*)&wram->wNumBalls, a, count);

    case TM_HM:
    // TMHM:
        // LD_H_D;
        // LD_L_E;
        // LD_A_addr(wCurItem);
        // LD_C_A;
        // CALL(aGetTMHMNumber);
        // JP(mReceiveTMHM);
        return ReceiveTMHM_Conv(GetTMHMNumber_Conv(a), count);
    }
    return false;
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

bool v_TossItem_Conv(item_pocket_s* hl, item_t item, uint8_t count){
    // CALL(aDoesHLEqualNumItems);
    // IF_NZ goto remove;
    if(hl != (item_pocket_s*)&wram->wNumItems)
        return RemoveItemFromPocket_Conv(hl, item, count);
    // PUSH_HL;
    // CALL(aCheckItemPocket);
    uint8_t pocket = CheckItemPocket_Conv(item);
    // POP_DE;
    // LD_A_addr(wItemAttributeValue);
    // DEC_A;
    // LD_HL(mv_TossItem_Pockets);
    // RST(aJumpTable);
    // RET;

    switch(pocket){
    // Pockets:
    //  entries correspond to item types
        //dw ['.Item'];
        default:
        case ITEM:
        // Item:
            // LD_H_D;
            // LD_L_E;

        // remove:
            // JP(mRemoveItemFromPocket);
            return RemoveItemFromPocket_Conv(hl, item, count);
        //dw ['.KeyItem'];
        case KEY_ITEM:
        // KeyItem:
            // LD_H_D;
            // LD_L_E;
            // JP(mTossKeyItem);
            return TossKeyItem_Conv(item, count);
        //dw ['.Ball'];
        case BALL:
        // Ball:
            // LD_HL(wNumBalls);
            // JP(mRemoveItemFromPocket);
            return RemoveItemFromPocket_Conv((item_pocket_s*)&wram->wNumBalls, item, count);
        //dw ['.TMHM'];
        case TM_HM: {
        // TMHM:
            // LD_H_D;
            // LD_L_E;
            // LD_A_addr(wCurItem);
            // LD_C_A;
            // CALL(aGetTMHMNumber);
            uint8_t tmhm = GetTMHMNumber_Conv(item);
            // JP(mTossTMHM);
            return TossTMHM_Conv(tmhm, count);
        }
    }
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
    if(hl == wram->wItems) {
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
            case ITEM:
                break;
            case KEY_ITEM:
            // KeyItem:
                // LD_H_D;
                // LD_L_E;
                // JP(mCheckKeyItems);
                return CheckKeyItems_Conv(item);
            case BALL:
            // Ball:
                // LD_HL(wNumBalls);
                // JP(mCheckTheItem);
                return CheckTheItem_Conv(item, wram->wBalls);
            case TM_HM:
            // TMHM:
                // LD_H_D;
                // LD_L_E;
                // LD_A_addr(wCurItem);
                // LD_C_A;
                // CALL(aGetTMHMNumber);
                // JP(mCheckTMHM);
                return CheckTMHM_Conv(GetTMHMNumber_Conv(item));
            default:
                return false;
        }
        // RET;


    // Pockets:
    //  entries correspond to item types
        //dw ['.Item'];
        //dw ['.KeyItem'];
        //dw ['.Ball'];
        //dw ['.TMHM'];


    // Item:
        // ;
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

uint8_t GetPocketCapacity_Conv(item_pocket_s* pocket){
    // LD_C(MAX_ITEMS);
    // LD_A_E;
    // CP_A(LOW(wNumItems));
    // IF_NZ goto not_bag;
    // LD_A_D;
    // CP_A(HIGH(wNumItems));
    // RET_Z ;
    if(pocket == (item_pocket_s*)&wram->wNumItems) {
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
    if(pocket == (item_pocket_s*)&wram->wNumPCItems) {
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

bool PutItemInPocket_Conv(item_pocket_s* pocket, item_t item, uint8_t count){
    // LD_D_H;
    // LD_E_L;
    // INC_HL;
    // LD_A_addr(wCurItem);
    // LD_C_A;
    // LD_B(0);

    uint8_t c = 0;
    for(uint8_t b = 0; ; c++) {
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto terminator;
        if(pocket->pocket[c].item == 0xff) {
        // terminator:
            // CALL(aGetPocketCapacity);
            uint8_t capacity = GetPocketCapacity_Conv(pocket);
            // LD_A_de;
            // CP_A_C;
            // IF_C goto ok;
            if(c < capacity)
                break;
            // AND_A_A;
            // RET;
            return false;
        }
        // CP_A_C;
        // IF_NZ goto next;
        if(pocket->pocket[c].item != item)
            continue;
        // LD_A(MAX_ITEM_STACK);
        // SUB_A_hl;
        // ADD_A_B;
        // LD_B_A;
        b += (MAX_ITEM_STACK - pocket->pocket[c].quantity);
        // LD_A_addr(wItemQuantityChange);
        // CP_A_B;
        // IF_Z goto ok;
        // IF_C goto ok;
        if(count <= b)
            break;

    // next:
        // INC_HL;
        // goto loop;
    }


// ok:
    // LD_H_D;
    // LD_L_E;
    item_pocket_en_s* hl = pocket->pocket + c;
    // LD_A_addr(wCurItem);
    // LD_C_A;
    // LD_A_addr(wItemQuantityChange);
    // LD_addr_A(wItemQuantity);
    wram->wItemQuantity = count;

    while(1) {
    // loop2:
        // INC_HL;
        // LD_A_hli;
        item_t a = hl->item;
        // CP_A(-1);
        // IF_Z goto terminator2;
        if(a == 0xff) {
        // terminator2:
            // DEC_HL;
            // LD_A_addr(wCurItem);
            // LD_hli_A;
            hl->item = item;
            // LD_A_addr(wItemQuantity);
            // LD_hli_A;
            hl->quantity = wram->wItemQuantity;
            // LD_hl(-1);
            hl[1].item = 0xff;
            // LD_H_D;
            // LD_L_E;
            // INC_hl;
            pocket->count++;
            // break;
            return true;
        }
        // CP_A_C;
        // IF_NZ goto loop2;
        if(a != item) {     
            hl++;
            continue;
        }
        // LD_A_addr(wItemQuantity);
        // ADD_A_hl;
        a = wram->wItemQuantity + hl->quantity;
        // CP_A(MAX_ITEM_STACK + 1);
        // IF_NC goto newstack;
        if(a >= MAX_ITEM_STACK) {
        // newstack:
            // LD_hl(MAX_ITEM_STACK);
            hl->quantity = MAX_ITEM_STACK;
            // SUB_A(MAX_ITEM_STACK);
            // LD_addr_A(wItemQuantity);
            wram->wItemQuantity = a - MAX_ITEM_STACK;
            // goto loop2;
            hl++;
            continue;
        }
        // LD_hl_A;
        // goto done;
        hl->quantity = a;
        return true;
    }

// done:
    // SCF;
    // RET;

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

bool RemoveItemFromPocket_Conv(item_pocket_s* hl, item_t item, item_t count){
    // LD_D_H;
    // LD_E_L;
    // LD_A_hli;
    // LD_C_A;
    // LD_A_addr(wCurItemQuantity);
    uint32_t i = 0;
    // CP_A_C;
    // IF_NC goto ok;  // memory
    if(hl->count < wram->wCurItemQuantity) {
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_addr(wCurItem);
        // CP_A_hl;
        // INC_HL;
        // IF_Z goto skip;
        if(hl->pocket[wram->wCurItemQuantity].item == item) {
            i = wram->wCurItemQuantity;
            goto skip;
        }
        // LD_H_D;
        // LD_L_E;
        // INC_HL;
    }

// ok:
    // LD_A_addr(wCurItem);
    // LD_B_A;
    i = 0;

    while(1) {
    // loop:
        // LD_A_hli;
        // CP_A_B;
        // IF_Z goto skip;
        if(hl->pocket[i].item == item)
            break;
        // CP_A(-1);
        // IF_Z goto nope;
        if(hl->pocket[i].item == 0xff)
            return false;
        // INC_HL;
        i++;
        // goto loop;
    }


skip:
    // LD_A_addr(wItemQuantityChange);
    // LD_B_A;
    // LD_A_hl;
    // SUB_A_B;
    // IF_C goto nope;
    if(hl->pocket[i].quantity >= count){
        // LD_hl_A;
        hl->pocket[i].quantity -= count;
        // LD_addr_A(wItemQuantity);
        wram->wItemQuantity = hl->pocket[i].quantity;
        // AND_A_A;
        // IF_NZ goto yup;
        if(wram->wItemQuantity != 0)
            return true;
        // DEC_HL;
        // LD_B_H;
        // LD_C_L;
        uint32_t bc = i;
        // INC_HL;
        // INC_HL;

        do {
        // loop2:
            // LD_A_hli;
            // LD_bc_A;
            hl->pocket[bc++] = hl->pocket[++i];
            // INC_BC;
            // CP_A(-1);
            // IF_NZ goto loop2;
        } while(hl->pocket[bc - 1].item != 0xff);
        // LD_H_D;
        // LD_L_E;
        // DEC_hl;
        hl->count--;

    // yup:
        // SCF;
        // RET;
        return true;
    }

// nope:
    // AND_A_A;
    // RET;
    return false;
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

static item_t* TossKeyItem_Toss(item_t item){
// Toss:
    // LD_HL(wNumKeyItems);
    item_t* hl = wram->wKeyItems;
    // LD_A_addr(wCurItem);
    item_t a;
    // LD_C_A;

    do {
    // loop3:
        // INC_HL;
        // LD_A_hl;
        a = *(hl++);
        // CP_A_C;
        // IF_Z goto ok3;
        if(a == item){
        // ok3:
            // LD_A_addr(wNumKeyItems);
            // DEC_A;
            // LD_addr_A(wNumKeyItems);
            wram->wNumKeyItems--;
            // SCF;
            // RET;
            return hl;
        }
        // CP_A(-1);
        // IF_NZ goto loop3;
    } while(a != (item_t)-1);
    // XOR_A_A;
    // RET;
    return NULL;
}

bool TossKeyItem_Conv(item_t item, uint8_t count){
    // LD_A_addr(wCurItemQuantity);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wNumKeyItems);
    item_t* hl;
    // LD_A_hl;
    // CP_A_E;
    // IF_NC goto ok;
    if(wram->wNumKeyItems < count){
        // CALL(aTossKeyItem_Toss);
        hl = TossKeyItem_Toss(item);
        // RET_NC ;
        if(!hl)
            return false;
        // goto ok2;
    }
    else {
    // ok:
        // DEC_hl;
        --wram->wNumKeyItems;
        // INC_HL;
        // ADD_HL_DE;
        hl = wram->wKeyItems + count;
    }

// ok2:
    // LD_D_H;
    // LD_E_L;
    // INC_HL;
    item_t* de = hl;
    hl++;

    item_t a;
    do {
    // loop:
        // LD_A_hli;
        a = *(hl++);
        // LD_de_A;
        // INC_DE;
        *(de++) = a;
        // CP_A(-1);
        // IF_NZ goto loop;
    } while(a != (item_t)-1);
    // SCF;
    // RET;
    return true;
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

bool CheckKeyItems_Conv(item_t c){
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

bool ReceiveTMHM_Conv(uint8_t id, uint8_t count){
    // DEC_C;
    // LD_B(0);
    // LD_HL(wTMsHMs);
    // ADD_HL_BC;

    // LD_A_addr(wItemQuantityChange);
    // ADD_A_hl;
    uint8_t a = count + wram->wTMsHMs[id - 1];
    // CP_A(MAX_ITEM_STACK + 1);
    // IF_NC goto toomany;
    if(a >= MAX_ITEM_STACK + 1)
        return false;
    // LD_hl_A;
    wram->wTMsHMs[id - 1] = a;
    // SCF;
    // RET;
    return true;

// toomany:
    // AND_A_A;
    // RET;
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

bool TossTMHM_Conv(uint8_t tmhm, uint8_t count){
    // DEC_C;
    // LD_B(0);
    // LD_HL(wTMsHMs);
    // ADD_HL_BC;
    // LD_A_addr(wItemQuantityChange);
    // LD_B_A;
    // LD_A_hl;
    // SUB_A_B;
    // IF_C goto nope;
    if(wram->wTMsHMs[tmhm] < count)
        return false;
    uint8_t c = wram->wTMsHMs[tmhm] - count;
    // LD_hl_A;
    wram->wTMsHMs[tmhm] = c;
    // LD_addr_A(wItemQuantity);
    wram->wItemQuantity = c;
    // IF_NZ goto yup;
    if(c != 0)
        return true;
    // LD_A_addr(wTMHMPocketScrollPosition);
    // AND_A_A;
    // IF_Z goto yup;
    if(wram->wTMHMPocketScrollPosition != 0) {
        // DEC_A;
        // LD_addr_A(wTMHMPocketScrollPosition);
        wram->wTMHMPocketScrollPosition--;
    }

// yup:
    // SCF;
    // RET;
    return true;

// nope:
    // AND_A_A;
    // RET;
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

//  Return the item id of a TM/HM by number c.
item_t GetNumberedTMHM_Conv(uint8_t tmhm){
    // LD_A_C;
//  Skip any gaps.
    // CP_A(ITEM_C3 - (TM01 - 1));
    // IF_C goto done;
    if(tmhm >= ITEM_C3 - (TM01 - 1)) {
        // CP_A(ITEM_DC - (TM01 - 1) - 1);
        // IF_C goto skip_one;
        if(tmhm >= ITEM_DC - (TM01 - 1) - 1) {
        //  skip two
            // INC_A;
            tmhm++;
        }
    // skip_one:
        // INC_A;
        tmhm++;
    }
// done:
    // ADD_A(TM01);
    // DEC_A;
    // LD_C_A;
    // RET;
    return (tmhm + TM01) - 1;
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
