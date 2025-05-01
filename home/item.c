#include "../constants.h"
#include "item.h"
#include "../engine/items/items.h"
#include "../engine/items/item_effects.h"

void DoItemEffect(void){
    // FARCALL(av_DoItemEffect);
    // RET;
    v_DoItemEffect_Conv(wram->wCurItem);
}

//  Return false if item can't be removed from the bag.
bool CheckTossableItem(item_t item){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // FARCALL(av_CheckTossableItem);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return v_CheckTossableItem(item);
}

bool TossItem(item_pocket_u* pocket, item_t item, uint8_t quantity){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(av_TossItem));
    // RST(aBankswitch);

    // CALL(av_TossItem);
    return v_TossItem(pocket, item, quantity);

    // POP_BC;
    // LD_A_B;
    // RST(aBankswitch);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

bool ReceiveItem(item_pocket_u* pocket, item_t item, uint8_t quantity){
    // PUSH_BC;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(av_ReceiveItem));
    // RST(aBankswitch);
    // PUSH_HL;
    // PUSH_DE;

    // CALL(av_ReceiveItem);
    // return v_ReceiveItem(item, quantity);
    return v_ReceiveItem(pocket, item, quantity);

    // POP_DE;
    // POP_HL;
    // POP_BC;
    // LD_A_B;
    // RST(aBankswitch);
    // POP_BC;
    // RET;
}

bool CheckItem(item_pocket_u *pocket, item_t item){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    // LD_A(BANK(av_CheckItem));
    // RST(aBankswitch);

    // CALL(av_CheckItem);
    bool b = v_CheckItem(pocket, item);

    // POP_BC;
    // LD_A_B;
    // RST(aBankswitch);
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
    return b;
}

item_pocket_u* GetItemPocket(uint8_t pocket) {
    switch(pocket) {
        default:
        case ITEM_POCKET: return (item_pocket_u*)&wram->wNumItems;
        case BALL_POCKET: return (item_pocket_u*)&wram->wNumBalls;
        case KEY_ITEM_POCKET: return (item_pocket_u*)&wram->wNumKeyItems;
        case TM_HM_POCKET: return (item_pocket_u*)&wram->wTMsHMs;
        case PC_ITEM_POCKET: return (item_pocket_u*)&wram->wNumPCItems;
    }
}
