#include "../constants.h"
#include "item.h"
#include "../engine/items/items.h"

void DoItemEffect(void){
        FARCALL(av_DoItemEffect);
    RET;

}

void CheckTossableItem(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    FARCALL(av_CheckTossableItem);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

//  Return false if item can't be removed from the bag.
bool CheckTossableItem_Conv(item_t item){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // FARCALL(av_CheckTossableItem);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return v_CheckTossableItem_Conv(item);
}

void TossItem(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_TossItem));
    RST(aBankswitch);

    CALL(av_TossItem);

    POP_BC;
    LD_A_B;
    RST(aBankswitch);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

void ReceiveItem(void){
        PUSH_BC;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_ReceiveItem));
    RST(aBankswitch);
    PUSH_HL;
    PUSH_DE;

    CALL(av_ReceiveItem);

    POP_DE;
    POP_HL;
    POP_BC;
    LD_A_B;
    RST(aBankswitch);
    POP_BC;
    RET;

}

bool ReceiveItem_Conv(item_t item, item_t* hl, uint8_t quantity){
    // PUSH_BC;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(av_ReceiveItem));
    // RST(aBankswitch);
    // PUSH_HL;
    // PUSH_DE;

    // CALL(av_ReceiveItem);
    // return v_ReceiveItem_Conv(item, quantity);
    (void)item, (void)hl, (void)quantity;
    return true;

    // POP_DE;
    // POP_HL;
    // POP_BC;
    // LD_A_B;
    // RST(aBankswitch);
    // POP_BC;
    // RET;
}

void CheckItem(void){
        PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LD_A(BANK(av_CheckItem));
    RST(aBankswitch);

    CALL(av_CheckItem);

    POP_BC;
    LD_A_B;
    RST(aBankswitch);
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

bool CheckItem_Conv(item_t item, item_t* hl){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(av_CheckItem));
    // RST(aBankswitch);
    bank_push(BANK(av_CheckItem));

    // CALL(av_CheckItem);
    bool b = v_CheckItem_Conv(item, hl);

    // POP_BC;
    // LD_A_B;
    // RST(aBankswitch);
    bank_pop;
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return b;
}
