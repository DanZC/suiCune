#include "../../constants.h"
#include "buy_sell_toss.h"
#include "items.h"
#include "../../home/menu.h"
#include "../../home/print_text.h"
#include "../../home/joypad.h"
#include "../../home/scrolling_menu.h"
#include "../../home/tilemap.h"

static uint32_t sBuySellItemPrice;

bool SelectQuantityToToss(void){
    // LD_HL(mTossItem_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&TossItem_MenuHeader);
    // CALL(aToss_Sell_Loop);
    // RET;
    return Toss_Sell_Loop();
}

bool SelectQuantityToBuy(void){
    // FARCALL(aGetItemPrice);
    uint16_t price = GetItemPrice_Conv(wram->wCurItem);
    return RooftopSale_SelectQuantityToBuy(price);
}

bool RooftopSale_SelectQuantityToBuy(uint16_t price){
    // LD_A_D;
    // LD_addr_A(wBuySellItemPrice + 0);
    // LD_A_E;
    // LD_addr_A(wBuySellItemPrice + 1);
    sBuySellItemPrice = (uint32_t)price;
    // LD_HL(mBuyItem_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&BuyItem_MenuHeader);
    // CALL(aToss_Sell_Loop);
    // RET;
    return Toss_Sell_Loop();
}

bool SelectQuantityToSell(void){
    // FARCALL(aGetItemPrice);
    uint16_t price = GetItemPrice_Conv(wram->wCurItem);
    // LD_A_D;
    // LD_addr_A(wBuySellItemPrice + 0);
    // LD_A_E;
    // LD_addr_A(wBuySellItemPrice + 1);
    sBuySellItemPrice = (uint32_t)price;
    // LD_HL(mSellItem_MenuHeader);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&SellItem_MenuHeader);
    // CALL(aToss_Sell_Loop);
    // RET;
    return Toss_Sell_Loop();
}

bool Toss_Sell_Loop(void){
    // LD_A(1);
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = 1;

    u8_flag_s res = {};
    do {
    // loop:
        // CALL(aBuySellToss_UpdateQuantityDisplay);  // update display
        BuySellToss_UpdateQuantityDisplay();
        // CALL(aBuySellToss_InterpretJoypad);  // joy action
        // IF_NC goto loop;
        res = BuySellToss_InterpretJoypad();
    } while(!res.flag);
    // CP_A(-1);
    // IF_NZ goto nope;  // pressed B
    if(res.a != 0xff) {
    // nope:
        // AND_A_A;
        // RET;
        return false;
    }
    // SCF;
    // RET;
    return true;
}

u8_flag_s BuySellToss_InterpretJoypad(void){
    // CALL(aJoyTextDelay_ForcehJoyDown);  // get joypad
    uint8_t c = JoyTextDelay_ForcehJoyDown_Conv();
    // BIT_C(B_BUTTON_F);
    // IF_NZ goto b;
    if(bit_test(c, B_BUTTON_F)){
    // b:
        // LD_A(-1);
        // SCF;
        // RET;
        return u8_flag(0xff, true);
    }
    // BIT_C(A_BUTTON_F);
    // IF_NZ goto a;
    if(bit_test(c, A_BUTTON_F)){
    // a:
        // LD_A(0);
        // SCF;
        // RET;
        return u8_flag(0, true);
    }
    // BIT_C(D_DOWN_F);
    // IF_NZ goto down;
    if(bit_test(c, D_DOWN_F)){
    // down:
        // LD_HL(wItemQuantityChange);
        // DEC_hl;
        // IF_NZ goto finish_down;
        if(--wram->wItemQuantityChange == 0){
            // LD_A_addr(wItemQuantity);
            // LD_hl_A;
            wram->wItemQuantityChange = wram->wItemQuantity;
        }

    // finish_down:
        // AND_A_A;
        // RET;
        return u8_flag(0, false);
    }
    // BIT_C(D_UP_F);
    // IF_NZ goto up;
    if(bit_test(c, D_UP_F)){
    // up:
        // LD_HL(wItemQuantityChange);
        // INC_hl;
        // LD_A_addr(wItemQuantity);
        // CP_A_hl;
        // IF_NC goto finish_up;
        if(++wram->wItemQuantityChange > wram->wItemQuantity){
            // LD_hl(1);
            wram->wItemQuantityChange = 1;
        }

    // finish_up:
        // AND_A_A;
        // RET;
        return u8_flag(0, false);
    }
    // BIT_C(D_LEFT_F);
    // IF_NZ goto left;
    if(bit_test(c, D_LEFT_F)){
    // left:
        // LD_A_addr(wItemQuantityChange);
        // SUB_A(10);
        // IF_C goto load_1;
        // IF_Z goto load_1;
        // goto finish_left;

        if(wram->wItemQuantityChange <= 10) {
        // load_1:
            // LD_A(1);
            wram->wItemQuantityChange = 1;
        }
        else {
            wram->wItemQuantityChange -= 10;
        }

    // finish_left:
        // LD_addr_A(wItemQuantityChange);
        // AND_A_A;
        // RET;
        return u8_flag(0, false);
    }
    // BIT_C(D_RIGHT_F);
    // IF_NZ goto right;
    if(bit_test(c, D_RIGHT_F)){
    // right:
        // LD_A_addr(wItemQuantityChange);
        // ADD_A(10);
        // LD_B_A;
        // LD_A_addr(wItemQuantity);
        // CP_A_B;
        // IF_NC goto finish_right;
        if(wram->wItemQuantityChange + 10 > wram->wItemQuantity){
            // LD_B_A;
            wram->wItemQuantityChange = wram->wItemQuantity;
        }
        else {
            wram->wItemQuantityChange += 10;
        }

    // finish_right:
        // LD_A_B;
        // LD_addr_A(wItemQuantityChange);
        // AND_A_A;
        // RET;
        return u8_flag(0, false);
    }
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

void BuySellToss_UpdateQuantityDisplay(void){
    // CALL(aMenuBox);
    MenuBox_Conv();
    // CALL(aMenuBoxCoord2Tile);
    tile_t* hl = MenuBoxCoord2Tile_Conv();
    // LD_DE(SCREEN_WIDTH + 1);
    // ADD_HL_DE;
    // LD_hl(0xf1);
    hl[SCREEN_WIDTH + 1] = 0xf1;
    // INC_HL;
    // LD_DE(wItemQuantityChange);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // CALL(aPrintNum);
    hl = PrintNum_Conv2(hl + SCREEN_WIDTH + 2, &wram->wItemQuantityChange, PRINTNUM_LEADINGZEROS | 1, 2);

    void (*const func)(tile_t*) = (void (*)(tile_t*))GetMenuData();
    // LD_A_addr(wMenuDataPointer);
    // LD_E_A;
    // LD_A_addr(wMenuDataPointer + 1);
    // LD_D_A;
    // LD_A_addr(wMenuDataBank);

    // CALL(aFarCall_de);
    func(hl);
    // RET;
}

void NoPriceToDisplay(tile_t* hl){
//  Does nothing.
    // RET;
    (void)hl;
}

void DisplayPurchasePrice(tile_t* hl){
    // CALL(aBuySell_MultiplyPrice);
    uint32_t price = BuySell_MultiplyPrice();
    // CALL(aBuySell_DisplaySubtotal);
    BuySell_DisplaySubtotal(hl, price);
    // RET;
}

void DisplaySellingPrice(tile_t* hl){
    // CALL(aBuySell_MultiplyPrice);
    uint32_t price = BuySell_MultiplyPrice();
    // CALL(aSell_HalvePrice);
    price = Sell_HalvePrice(price);
    // CALL(aBuySell_DisplaySubtotal);
    BuySell_DisplaySubtotal(hl, price);
    // RET;
}

uint32_t BuySell_MultiplyPrice(void){
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    // LD_A_addr(wBuySellItemPrice + 0);
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A_addr(wBuySellItemPrice + 1);
    // LDH_addr_A(hMultiplicand + 2);
    // LD_A_addr(wItemQuantityChange);
    // LDH_addr_A(hMultiplier);
    // PUSH_HL;
    // CALL(aMultiply);
    // POP_HL;
    // RET;
    return sBuySellItemPrice * wram->wItemQuantityChange;
}

uint32_t Sell_HalvePrice(uint32_t price){
    // PUSH_HL;
    // LD_HL(hProduct + 1);
    // LD_A_hl;
    // SRL_A;
    // LD_hli_A;
    // LD_A_hl;
    // RRA;
    // LD_hli_A;
    // LD_A_hl;
    // RRA;
    // LD_hl_A;
    // POP_HL;
    // RET;
    return price / 2;
}

void BuySell_DisplaySubtotal(tile_t* hl, uint32_t price){
    // PUSH_HL;
    // LD_HL(hMoneyTemp);
    // LDH_A_addr(hProduct + 1);
    // LD_hli_A;
    hram->hMoneyTemp[0] = (price >> 16) & 0xff;
    // LDH_A_addr(hProduct + 2);
    // LD_hli_A;
    hram->hMoneyTemp[1] = (price >> 8) & 0xff;
    // LDH_A_addr(hProduct + 3);
    // LD_hl_A;
    hram->hMoneyTemp[2] = (price) & 0xff;
    // POP_HL;
    // INC_HL;
    // LD_DE(hMoneyTemp);
    // LD_BC((PRINTNUM_MONEY | 3 << 8) | 6);
    // CALL(aPrintNum);
    PrintNum_Conv2(hl, hram->hMoneyTemp, PRINTNUM_MONEY | 3, 6);
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // RET;
}

const struct MenuHeader TossItem_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(15, 9, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['NoPriceToDisplay'];
    .data = NoPriceToDisplay,
    .defaultOption = 0,  // default option
};

const struct MenuHeader BuyItem_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(7, 15, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    //dw ['DisplayPurchasePrice'];
    .data = DisplayPurchasePrice,
    .defaultOption = -1,  // default option
};

const struct MenuHeader SellItem_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(7, 15, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    //dw ['DisplaySellingPrice'];
    .data = DisplaySellingPrice,
    .defaultOption = 0,  // default option

};
