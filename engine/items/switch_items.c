#include "../../constants.h"
#include "switch_items.h"
#include "../../home/copy.h"
#include "../../home/menu.h"

static bool SwitchItemsInBag_try_combining_stacks(void){
    // LD_A_addr(wSwitchItem);
    // CALL(aItemSwitch_GetNthItem);
    // LD_D_H;
    // LD_E_L;
    const uint8_t* de = ItemSwitch_GetNthItem(wram->wSwitchItem);
    // LD_A_addr(wScrollingMenuCursorPosition);
    // CALL(aItemSwitch_GetNthItem);
    const uint8_t* hl = ItemSwitch_GetNthItem(wram->wScrollingMenuCursorPosition);
    // LD_A_de;
    // CP_A_hl;
    // IF_NZ goto no_combine;
    if(*de != *hl){
    // no_combine:
        // AND_A_A;
        // RET;
        return false;
    }
    // LD_A_addr(wScrollingMenuCursorPosition);
    // CALL(aItemSwitch_GetItemQuantity);
    // CP_A(MAX_ITEM_STACK);
    // IF_Z goto no_combine;
    if(ItemSwitch_GetItemQuantity(wram->wScrollingMenuCursorPosition) == MAX_ITEM_STACK)
        return false;
    // LD_A_addr(wSwitchItem);
    // CALL(aItemSwitch_GetItemQuantity);
    // CP_A(MAX_ITEM_STACK);
    // IF_NZ goto combine;
    if(ItemSwitch_GetItemQuantity(wram->wSwitchItem) == MAX_ITEM_STACK)
        return false;

// no_combine:
    // AND_A_A;
    // RET;

// combine:
    // SCF;
    // RET;
    return true;
}

static void SwitchItemsInBag_combine_stacks(void){
    // LD_A_addr(wSwitchItem);
    // CALL(aItemSwitch_GetNthItem);
    // INC_HL;
    // PUSH_HL;
    uint8_t* hl = ItemSwitch_GetNthItem(wram->wSwitchItem) + 1;
    // LD_A_addr(wScrollingMenuCursorPosition);
    // CALL(aItemSwitch_GetNthItem);
    // INC_HL;
    // LD_A_hl;
    uint8_t x = ItemSwitch_GetNthItem(wram->wSwitchItem)[1];
    // POP_HL;
    // ADD_A_hl;
    // CP_A(MAX_ITEM_STACK + 1);
    // IF_C goto merge_stacks;
    if(x + *hl >= MAX_ITEM_STACK + 1){
        // SUB_A(MAX_ITEM_STACK);
        // PUSH_AF;
        uint8_t rem = (x + *hl) - MAX_ITEM_STACK;
        // LD_A_addr(wScrollingMenuCursorPosition);
        // CALL(aItemSwitch_GetNthItem);
        // INC_HL;
        // LD_hl(MAX_ITEM_STACK);
        ItemSwitch_GetNthItem(wram->wScrollingMenuCursorPosition)[1] = MAX_ITEM_STACK;
        // LD_A_addr(wSwitchItem);
        // CALL(aItemSwitch_GetNthItem);
        // INC_HL;
        // POP_AF;
        // LD_hl_A;
        ItemSwitch_GetNthItem(wram->wSwitchItem)[1] = rem;
        // XOR_A_A;
        // LD_addr_A(wSwitchItem);
        wram->wSwitchItem = 0x0;
        // RET;
        return;
    }

// merge_stacks:
    // PUSH_AF;
    uint8_t amt = (x + *hl);
    // LD_A_addr(wScrollingMenuCursorPosition);
    // CALL(aItemSwitch_GetNthItem);
    // INC_HL;
    // POP_AF;
    // LD_hl_A;
    ItemSwitch_GetNthItem(wram->wScrollingMenuCursorPosition)[1] = amt;
    // LD_HL(wMenuData_ItemsPointerAddr);
    const struct MenuData* data = GetMenuData();
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_A_addr(wSwitchItem);
    // CP_A_hl;
    // IF_NZ goto not_combining_last_item;
    if(wram->wSwitchItem == data->scrollingMenu.list[0]){
        // DEC_hl;
        data->scrollingMenu.list[0]--;
        // LD_A_addr(wSwitchItem);
        // CALL(aItemSwitch_GetNthItem);
        // LD_hl(-1);  // end
        ItemSwitch_GetNthItem(wram->wSwitchItem)[0] = 0xff;
        // XOR_A_A;
        // LD_addr_A(wSwitchItem);
        wram->wSwitchItem = 0;
        // RET;
        return;
    }

// not_combining_last_item:
    // DEC_hl;
    data->scrollingMenu.list[0]--;
    // CALL(aItemSwitch_GetItemFormatSize);
    // PUSH_BC;
    // LD_A_addr(wSwitchItem);
    // CALL(aItemSwitch_GetNthItem);
    // POP_BC;
    uint8_t* de = ItemSwitch_GetNthItem(wram->wSwitchItem);
    // PUSH_HL;
    // ADD_HL_BC;
    hl = de + ItemSwitch_GetItemFormatSize();
    // POP_DE;

    uint8_t a;
    do {
    // copy_loop:
        // LD_A_hli;
        a = *(hl++);
        // LD_de_A;
        *(de++) = a;
        // INC_DE;
        // CP_A(-1);  // end?
        // IF_NZ goto copy_loop;
    } while(a != 0xff);
    // XOR_A_A;
    // LD_addr_A(wSwitchItem);
    wram->wSwitchItem = 0;
    // RET;
}

void SwitchItemsInBag(void){
    // LD_A_addr(wSwitchItem);
    // AND_A_A;
    // IF_Z goto init;
    if(wram->wSwitchItem == 0){
    // init:
        // LD_A_addr(wScrollingMenuCursorPosition);
        // INC_A;
        // LD_addr_A(wSwitchItem);
        wram->wSwitchItem = wram->wScrollingMenuCursorPosition + 1;
        // RET;
        return;
    }
    // LD_B_A;
    // LD_A_addr(wScrollingMenuCursorPosition);
    // INC_A;
    // CP_A_B;
    // IF_Z goto trivial;
    if(wram->wScrollingMenuCursorPosition + 1 == wram->wSwitchItem){
    // trivial:
        // XOR_A_A;
        // LD_addr_A(wSwitchItem);
        wram->wSwitchItem = 0;
        // RET;
        return;
    }
    // LD_A_addr(wScrollingMenuCursorPosition);
    // CALL(aItemSwitch_GetNthItem);
    const uint8_t* nthItem = ItemSwitch_GetNthItem(wram->wScrollingMenuCursorPosition);
    // LD_A_hl;
    // CP_A(-1);
    // RET_Z ;
    if(*nthItem == 0xff)
        return;
    // LD_A_addr(wSwitchItem);
    // DEC_A;
    // LD_addr_A(wSwitchItem);
    wram->wSwitchItem--;
    // CALL(aSwitchItemsInBag_try_combining_stacks);
    // JP_C (mSwitchItemsInBag_combine_stacks);
    if(SwitchItemsInBag_try_combining_stacks())
        return SwitchItemsInBag_combine_stacks();
    printf("%d -> %d\n", wram->wSwitchItem, wram->wScrollingMenuCursorPosition);
    // LD_A_addr(wScrollingMenuCursorPosition);
    // LD_C_A;
    // LD_A_addr(wSwitchItem);
    // CP_A_C;
    // IF_C goto above;
    if(wram->wSwitchItem < wram->wScrollingMenuCursorPosition){
    // above:
        // LD_A_addr(wSwitchItem);
        // CALL(aItemSwitch_CopyItemToBuffer);
        ItemSwitch_CopyItemToBuffer(wram->wSwitchItem);
        // LD_A_addr(wScrollingMenuCursorPosition);
        // LD_D_A;
        // LD_A_addr(wSwitchItem);
        // LD_E_A;
        // CALL(aItemSwitch_GetItemOffset);
        // int16_t offset = ItemSwitch_GetItemOffset(wram->wScrollingMenuCursorPosition, wram->wSwitchItem);
        // PUSH_BC;
        // LD_A_addr(wSwitchItem);
        // CALL(aItemSwitch_GetNthItem);
        // LD_D_H;
        // LD_E_L;
        // CALL(aItemSwitch_GetItemFormatSize);
        // ADD_HL_BC;
        // POP_BC;
        // CALL(aCopyBytes);
        // CopyBytes_Conv2(de, de + ItemSwitch_GetItemFormatSize(), offset);
        CopyBytes_Conv2(ItemSwitch_GetNthItem(wram->wSwitchItem), ItemSwitch_GetNthItem(wram->wScrollingMenuCursorPosition), ItemSwitch_GetItemFormatSize());
        // LD_A_addr(wScrollingMenuCursorPosition);
        // CALL(aItemSwitch_CopyBufferToItem);
        ItemSwitch_CopyBufferToItem(wram->wScrollingMenuCursorPosition);
        // XOR_A_A;
        // LD_addr_A(wSwitchItem);
        wram->wSwitchItem = 0;
        // RET;
        return;
    }
    // goto below;
    else {
    // below:
        // LD_A_addr(wSwitchItem);
        // CALL(aItemSwitch_CopyItemToBuffer);
        ItemSwitch_CopyItemToBuffer(wram->wSwitchItem);
        // LD_A_addr(wScrollingMenuCursorPosition);
        // LD_D_A;
        // LD_A_addr(wSwitchItem);
        // LD_E_A;
        // CALL(aItemSwitch_GetItemOffset);
        // int16_t offset = ItemSwitch_GetItemOffset(wram->wScrollingMenuCursorPosition, wram->wSwitchItem);
        // PUSH_BC;
        // LD_A_addr(wSwitchItem);
        // CALL(aItemSwitch_GetNthItem);
        // DEC_HL;
        // PUSH_HL;
        // CALL(aItemSwitch_GetItemFormatSize);
        // ADD_HL_BC;
        // LD_D_H;
        // LD_E_L;
        // uint8_t* de = ItemSwitch_GetNthItem(wram->wSwitchItem) - 1;
        // POP_HL;
        // POP_BC;
        // CALL(aItemSwitch_BackwardsCopyBytes);
        // ItemSwitch_BackwardsCopyBytes(de + offset, de, ItemSwitch_GetItemFormatSize());
        ItemSwitch_BackwardsCopyBytes(ItemSwitch_GetNthItem(wram->wSwitchItem), ItemSwitch_GetNthItem(wram->wScrollingMenuCursorPosition), ItemSwitch_GetItemFormatSize());
        // LD_A_addr(wScrollingMenuCursorPosition);
        // CALL(aItemSwitch_CopyBufferToItem);
        ItemSwitch_CopyBufferToItem(wram->wScrollingMenuCursorPosition);
        // XOR_A_A;
        // LD_addr_A(wSwitchItem);
        wram->wSwitchItem = 0;
        // RET;
        return;
    }
}

void ItemSwitch_CopyItemToBuffer(uint8_t a){
    // CALL(aItemSwitch_GetNthItem);
    // LD_DE(wSwitchItemBuffer);
    // CALL(aItemSwitch_GetItemFormatSize);
    // CALL(aCopyBytes);
    // RET;
    CopyBytes_Conv2(wram->wSwitchItemBuffer, ItemSwitch_GetNthItem(a), ItemSwitch_GetItemFormatSize());
}

void ItemSwitch_CopyBufferToItem(uint8_t a){
    // CALL(aItemSwitch_GetNthItem);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wSwitchItemBuffer);
    // CALL(aItemSwitch_GetItemFormatSize);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(ItemSwitch_GetNthItem(a), wram->wSwitchItemBuffer, ItemSwitch_GetItemFormatSize());
    // RET;
}

uint8_t* ItemSwitch_GetNthItem(uint8_t n){
    // PUSH_AF;
    // CALL(aItemSwitch_GetItemFormatSize);
    uint16_t size = ItemSwitch_GetItemFormatSize();
    // LD_HL(wMenuData_ItemsPointerAddr);
    const struct MenuData* data = GetMenuData();
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // INC_HL;
    // POP_AF;
    // CALL(aAddNTimes);
    // RET;
    return data->scrollingMenu.list + 1 + (size * n);
}

int16_t ItemSwitch_GetItemOffset(uint8_t d, uint8_t e){
    // PUSH_HL;
    // CALL(aItemSwitch_GetItemFormatSize);
    uint16_t bc = ItemSwitch_GetItemFormatSize();
    // LD_A_D;
    // SUB_A_E;
    // IF_NC goto dont_negate;
    int8_t a = d - e;
    // DEC_A;
    // CPL;

// dont_negate:
    // LD_HL(0);
    // CALL(aAddNTimes);
    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // RET;
    return a * bc;
}

uint16_t ItemSwitch_GetItemFormatSize(void){
    static const uint16_t item_format_sizes[] = {
    //  entries correspond to SCROLLINGMENU_ITEMS_* constants
        // 0,  // unused
        [SCROLLINGMENU_ITEMS_NORMAL] = 1,  // SCROLLINGMENU_ITEMS_NORMAL
        [SCROLLINGMENU_ITEMS_QUANTITY] = 2,  // SCROLLINGMENU_ITEMS_QUANTITY
    };
    // PUSH_HL;
    // LD_A_addr(wMenuData_ScrollingMenuItemFormat);
    const struct MenuData* data = GetMenuData();
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mItemSwitch_GetItemFormatSize_item_format_sizes);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_C_hl;
    // INC_HL;
    // LD_B_hl;
    // POP_HL;
    // RET;
    return item_format_sizes[data->scrollingMenu.format];
}

uint8_t ItemSwitch_GetItemQuantity(uint8_t n){
    // PUSH_AF;
    // CALL(aItemSwitch_GetItemFormatSize);
    // LD_A_C;
    // CP_A(2);
    // IF_NZ goto no_quantity;
    if(ItemSwitch_GetItemFormatSize() == 2){
        // POP_AF;
        // CALL(aItemSwitch_GetNthItem);
        // INC_HL;
        // LD_A_hl;
        // RET;
        return *(ItemSwitch_GetNthItem(n) + 1);
    }

// no_quantity:
    // POP_AF;
    // LD_A(1);
    // RET;
    return 1;
}

void ItemSwitch_BackwardsCopyBytes(uint8_t* de, const uint8_t* hl, uint16_t bc){
    do {
    // loop:
        // LD_A_hld;
        // LD_de_A;
        *(de--) = *(hl--);
        // DEC_DE;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // RET;
}
