#include "../../constants.h"
#include "mart.h"
#include "items.h"
#include "update_item_description.h"
#include "buy_sell_toss.h"
#include "pack.h"
#include "../../home/audio.h"
#include "../../home/copy.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../home/item.h"
#include "../../home/joypad.h"
#include "../../home/map.h"
#include "../../home/print_text.h"
#include "../../home/scrolling_menu.h"
#include "../../home/flag.h"
#include "../../home/map_objects.h"
#include "../../home/sprite_updates.h"
#include "../overworld/player_object.h"
#include "../menus/menu_2.h"
#include "../events/money.h"
#include "../pokemon/mon_menu.h"
#include "../../data/text/common.h"
#include "../../data/items/marts.h"
#include "../../data/items/bargain_shop.h"
#include "../../data/items/rooftop_sale.h"

enum {
    MARTTEXT_HOW_MANY,
    MARTTEXT_COSTS_THIS_MUCH,
    MARTTEXT_NOT_ENOUGH_MONEY,
    MARTTEXT_BAG_FULL,
    MARTTEXT_HERE_YOU_GO,
    MARTTEXT_SOLD_OUT,
};

//  StandardMart.MartFunctions indexes
enum {
    STANDARDMART_HOWMAYIHELPYOU,  // 0
    STANDARDMART_TOPMENU,  // 1
    STANDARDMART_BUY,  // 2
    STANDARDMART_SELL,  // 3
    STANDARDMART_QUIT,  // 4
    STANDARDMART_ANYTHINGELSE,  // 5
};

#define STANDARDMART_EXIT (-1)

static const item_t* sMartPointer;
static struct {
    uint8_t count;
    item_t items[16];
} sCurMart;
static item_price_s sMartItems[16];

struct MartDialogGroup {
    const txt_cmd_s** texts;
    uint8_t group;
};

item_t* Marts[NUM_MARTS+1];
size_t MartsSizes[NUM_MARTS+1];

const struct MartDialogGroup* GetMartDialogGroup(uint8_t type);

uint32_t GetMartSize(uint16_t de) {
    if(de > NUM_MARTS)
        return 2;
    return MartsSizes[de];
}

void OpenMartDialog(void){
    return OpenMartDialog_Conv(REG_C, REG_DE);
    CALL(aGetMart);
    LD_A_C;
    LD_addr_A(wMartType);
    CALL(aLoadMartPointer);
    LD_A_addr(wMartType);
    LD_HL(mOpenMartDialog_dialogs);
    RST(aJumpTable);
    RET;


//dialogs:
    //dw ['MartDialog'];
    //dw ['HerbShop'];
    //dw ['BargainShop'];
    //dw ['Pharmacist'];
    //dw ['RooftopSale'];
}

void OpenMartDialog_Conv(uint8_t type, uint16_t id){
    // CALL(aGetMart);
    const item_t* mart = GetMart_Conv(id);
    // LD_A_C;
    // LD_addr_A(wMartType);
    wram->wMartType = type;
    // CALL(aLoadMartPointer);
    LoadMartPointer_Conv(mart, GetMartSize(id));
    // LD_A_addr(wMartType);
    // LD_HL(mOpenMartDialog_dialogs);
    // RST(aJumpTable);
    // RET;

    switch(wram->wMartType){
    // dialogs:
        case MARTTYPE_STANDARD: return MartDialog();
        case MARTTYPE_BITTER:   return HerbShop();
        case MARTTYPE_BARGAIN:  return BargainShop();
        case MARTTYPE_PHARMACY: return Pharmacist();
        case MARTTYPE_ROOFTOP:  return RooftopSale();
    }
}

void MartDialog(void){
    // LD_A(MARTTYPE_STANDARD);
    // LD_addr_A(wMartType);
    wram->wMartType = MARTTYPE_STANDARD;
    // XOR_A_A;  // STANDARDMART_HOWMAYIHELPYOU
    // LD_addr_A(wMartJumptableIndex);
    wram->wMartJumptableIndex = STANDARDMART_HOWMAYIHELPYOU;
    // CALL(aStandardMart);
    StandardMart();
    // RET;
}

void HerbShop(void){
    // CALL(aFarReadMart);
    FarReadMart_Conv();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // LD_HL(mHerbShopLadyIntroText);
    // CALL(aMartTextbox);
    MartTextbox(HerbShopLadyIntroText);
    // CALL(aBuyMenu);
    BuyMenu();
    // LD_HL(mHerbalLadyComeAgainText);
    // CALL(aMartTextbox);
    MartTextbox(HerbalLadyComeAgainText);
    // RET;
}

void BargainShop(void){
    // LD_B(BANK(aBargainShopData));
    // LD_DE(mBargainShopData);
    // CALL(aLoadMartPointer);
    LoadMartPointer_Conv((const item_t*)BargainShopData, BargainShopData_Size);
    // CALL(aReadMart);
    ReadMart();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // LD_HL(mBargainShopIntroText);
    // CALL(aMartTextbox);
    MartTextbox(BargainShopIntroText);
    // CALL(aBuyMenu);
    BuyMenu();
    // LD_HL(wBargainShopFlags);
    // LD_A_hli;
    // OR_A_hl;
    // IF_Z goto skip_set;
    if(wram->wBargainShopFlags != 0){
        // LD_HL(wDailyFlags1);
        // SET_hl(DAILYFLAGS1_GOLDENROD_UNDERGROUND_BARGAIN_F);
        bit_set(wram->wDailyFlags1, DAILYFLAGS1_GOLDENROD_UNDERGROUND_BARGAIN_F);
    }

// skip_set:
    // LD_HL(mBargainShopComeAgainText);
    // CALL(aMartTextbox);
    MartTextbox(BargainShopComeAgainText);
    // RET;
}

void Pharmacist(void){
    // CALL(aFarReadMart);
    FarReadMart_Conv();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // LD_HL(mPharmacyIntroText);
    // CALL(aMartTextbox);
    MartTextbox(PharmacyIntroText);
    // CALL(aBuyMenu);
    BuyMenu();
    // LD_HL(mPharmacyComeAgainText);
    // CALL(aMartTextbox);
    MartTextbox(PharmacyComeAgainText);
    // RET;
}

void RooftopSale(void){
    // LD_B(BANK(aRooftopSaleMart1));
    // LD_DE(mRooftopSaleMart1);
    // LD_HL(wStatusFlags);
    // BIT_hl(STATUSFLAGS_HALL_OF_FAME_F);
    // IF_Z goto ok;
    // LD_B(BANK(aRooftopSaleMart2));
    // LD_DE(mRooftopSaleMart2);
    const item_price_s* de = (bit_test(wram->wStatusFlags, STATUSFLAGS_HALL_OF_FAME_F))? RooftopSaleMart2: RooftopSaleMart1;
    const uint32_t de_size = (bit_test(wram->wStatusFlags, STATUSFLAGS_HALL_OF_FAME_F))? RooftopSaleMart2_Size: RooftopSaleMart1_Size;

// ok:
    // CALL(aLoadMartPointer);
    LoadMartPointer_Conv((const item_t*)de, de_size);
    // CALL(aReadMart);
    ReadMart();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // LD_HL(mMartWelcomeText);
    // CALL(aMartTextbox);
    MartTextbox(MartWelcomeText);
    // CALL(aBuyMenu);
    BuyMenu();
    // LD_HL(mMartComeAgainText);
    // CALL(aMartTextbox);
    MartTextbox(MartComeAgainText);
    // RET;
}

void LoadMartPointer(void){
    LD_A_B;
    LD_addr_A(wMartPointerBank);
    LD_A_E;
    LD_addr_A(wMartPointer);
    LD_A_D;
    LD_addr_A(wMartPointer + 1);
    LD_HL(wCurMartCount);
    //assert ['wCurMartCount + 1 == wCurMartItems'];
    XOR_A_A;
    LD_BC(16);
    CALL(aByteFill);
    XOR_A_A;  // STANDARDMART_HOWMAYIHELPYOU
    LD_addr_A(wMartJumptableIndex);
    LD_addr_A(wBargainShopFlags);
    LD_addr_A(wFacingDirection);
    RET;

}

void LoadMartPointer_Conv(const item_t* ptr, uint32_t size){
    // LD_A_B;
    // LD_addr_A(wMartPointerBank);
    // LD_A_E;
    // LD_addr_A(wMartPointer);
    // LD_A_D;
    // LD_addr_A(wMartPointer + 1);
    sMartPointer = ptr;
    // LD_HL(wCurMartCount);
    wram->wCurMartCount = size;
    //assert ['wCurMartCount + 1 == wCurMartItems'];
    // XOR_A_A;
    // LD_BC(16);
    // CALL(aByteFill);
    ByteFill(&sCurMart, sizeof(sCurMart), 0);
    sCurMart.count = (uint8_t)size;
    // XOR_A_A;  // STANDARDMART_HOWMAYIHELPYOU
    // LD_addr_A(wMartJumptableIndex);
    wram->wMartJumptableIndex = STANDARDMART_HOWMAYIHELPYOU;
    // LD_addr_A(wBargainShopFlags);
    wram->wBargainShopFlags = 0;
    // LD_addr_A(wFacingDirection);
    wram->wFacingDirection = 0;
    // RET;
}

void GetMart(void){
    LD_A_E;
    CP_A(NUM_MARTS);
    IF_C goto IsAMart;
    LD_B(BANK(aDefaultMart));
    LD_DE(mDefaultMart);
    RET;


IsAMart:
    LD_HL(mMarts);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_B(BANK(aMarts));
    RET;
}

const item_t* GetMart_Conv(uint16_t de){
    // LD_A_E;
    // CP_A(NUM_MARTS);
    // IF_C goto IsAMart;
    if(de > NUM_MARTS) {
        // LD_B(BANK(aDefaultMart));
        // LD_DE(mDefaultMart);
        // RET;
        return DefaultMart;
    }

// IsAMart:
    // LD_HL(mMarts);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // LD_B(BANK(aMarts));
    // RET;
    return Marts[de];
}

static uint8_t StandardMart_HowMayIHelpYou(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // LD_HL(mMartWelcomeText);
    // CALL(aPrintText);
    PrintText_Conv2(MartWelcomeText);
    // LD_A(STANDARDMART_TOPMENU);
    // RET;
    return STANDARDMART_TOPMENU;
}

static uint8_t StandardMart_TopMenu(void){
    // LD_HL(mMenuHeader_BuySell);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv2(&MenuHeader_BuySell);
    // CALL(aVerticalMenu);
    // IF_C goto quit;
    if(!VerticalMenu_Conv())
        return STANDARDMART_QUIT;
    // LD_A_addr(wMenuCursorY);
    // CP_A(0x1);
    // IF_Z goto buy;
    // CP_A(0x2);
    // IF_Z goto sell;
    switch(wram->wMenuCursorY) {
        case 0x1: return STANDARDMART_BUY;
        case 0x2: return STANDARDMART_SELL;
        default:  return STANDARDMART_QUIT;
    }
// quit:
    // LD_A(STANDARDMART_QUIT);
    // RET;
// buy:
    // LD_A(STANDARDMART_BUY);
    // RET;
// sell:
    // LD_A(STANDARDMART_SELL);
    // RET;
}

static uint8_t StandardMart_Buy(void) {
// Buy:
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // CALL(aFarReadMart);
    FarReadMart_Conv();
    // CALL(aBuyMenu);
    BuyMenu();
    // AND_A_A;
    // LD_A(STANDARDMART_ANYTHINGELSE);
    // RET;
    return STANDARDMART_ANYTHINGELSE;
}

static uint8_t StandardMart_Sell(void){
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // CALL(aSellMenu);
    SellMenu();
    // LD_A(STANDARDMART_ANYTHINGELSE);
    // RET;
    return STANDARDMART_ANYTHINGELSE;
}

static uint8_t StandardMart_Quit(void) {
// Quit:
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // LD_HL(mMartComeAgainText);
    // CALL(aMartTextbox);
    MartTextbox(MartComeAgainText);
    // LD_A(STANDARDMART_EXIT);
    // RET;
    return STANDARDMART_EXIT;
}

static uint8_t StandardMart_AnythingElse(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // LD_HL(mMartAskMoreText);
    // CALL(aPrintText);
    PrintText_Conv2(MartAskMoreText);
    // LD_A(STANDARDMART_TOPMENU);
    // RET;
    return STANDARDMART_TOPMENU;
}


void StandardMart(void){
    static uint8_t (*const MartFunctions[])(void) = {
    //  entries correspond to STANDARDMART_* constants
        //dw ['.HowMayIHelpYou'];
        StandardMart_HowMayIHelpYou,
        //dw ['.TopMenu'];
        StandardMart_TopMenu,
        //dw ['.Buy'];
        StandardMart_Buy,
        //dw ['.Sell'];
        StandardMart_Sell,
        //dw ['.Quit'];
        StandardMart_Quit,
        //dw ['.AnythingElse'];
        StandardMart_AnythingElse,
    };

    do {
    // loop:
        // LD_A_addr(wMartJumptableIndex);
        // LD_HL(mStandardMart_MartFunctions);
        // RST(aJumpTable);
        // LD_addr_A(wMartJumptableIndex);
        wram->wMartJumptableIndex = MartFunctions[wram->wMartJumptableIndex]();
        // CP_A(STANDARDMART_EXIT);
        // IF_NZ goto loop;
    } while(wram->wMartJumptableIndex != (uint8_t)STANDARDMART_EXIT);
    // RET;
    return;
}

void FarReadMart(void){
    LD_HL(wMartPointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wCurMartCount);

CopyMart:
    LD_A_addr(wMartPointerBank);
    CALL(aGetFarByte);
    LD_de_A;
    INC_HL;
    INC_DE;
    CP_A(-1);
    IF_NZ goto CopyMart;
    LD_HL(wMartItem1BCD);
    LD_DE(wCurMartItems);

ReadMartItem:
    LD_A_de;
    INC_DE;
    CP_A(-1);
    IF_Z goto done;
    PUSH_DE;
    CALL(aGetMartItemPrice);
    POP_DE;
    goto ReadMartItem;


done:
    RET;

}

void FarReadMart_Conv(void){
    // LD_HL(wMartPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(wCurMartCount);
    const item_t* hl = (const item_t*)sMartPointer;
    item_t* de = sCurMart.items;

    uint32_t i = 0;
    for(i = 0; i < wram->wCurMartCount; ++i) {
    // CopyMart:
        // LD_A_addr(wMartPointerBank);
        // CALL(aGetFarByte);
        // LD_de_A;
        de[i] = hl[i];
        // INC_HL;
        // INC_DE;
        // CP_A(-1);
        // IF_NZ goto CopyMart;
    }

    de[i] = (item_t)-1;
    // LD_HL(wMartItem1BCD);
    // LD_DE(wCurMartItems);
    de = sCurMart.items;
    item_price_s* bcd = sMartItems;

    for(i = 0; i < wram->wCurMartCount; ++i) {
    // ReadMartItem:
        // LD_A_de;
        // INC_DE;
        // CP_A(-1);
        // IF_Z goto done;
        // PUSH_DE;
        // CALL(aGetMartItemPrice);
        GetMartItemPrice_Conv(bcd + i, de[i]);
        // POP_DE;
        // goto ReadMartItem;
    }


// done:
    // RET;
}

void GetMartItemPrice(void){
//  Return the price of item a in BCD at hl and in tiles at wStringBuffer1.
    PUSH_HL;
    LD_addr_A(wCurItem);
    FARCALL(aGetItemPrice);
    POP_HL;

    return GetMartPrice();
}

//  Return the price of item a in BCD at hl and in tiles at wStringBuffer1.
void GetMartItemPrice_Conv(item_price_s* hl, item_t a){
    // PUSH_HL;
    // LD_addr_A(wCurItem);
    // FARCALL(aGetItemPrice);
    uint16_t de = GetItemPrice_Conv(a);
    // POP_HL;
    hl->id = a;
    hl->price = de;

    // return GetMartPrice_Conv(hl, de, a);
}

void GetMartPrice(void){
//  Return price de in BCD at hl and in tiles at wStringBuffer1.
    PUSH_HL;
    LD_A_D;
    LD_addr_A(wStringBuffer2);
    LD_A_E;
    LD_addr_A(wStringBuffer2 + 1);
    LD_HL(wStringBuffer1);
    LD_DE(wStringBuffer2);
    LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 6);  // 6 digits
    CALL(aPrintNum);
    POP_HL;

    LD_DE(wStringBuffer1);
    LD_C(6 / 2);  // 6 digits

loop:
    CALL(aGetMartPrice_CharToNybble);
    SWAP_A;
    LD_B_A;
    CALL(aGetMartPrice_CharToNybble);
    OR_A_B;
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    RET;


CharToNybble:
    LD_A_de;
    INC_DE;
    CP_A(0x7f);
    IF_NZ goto not_space;
    LD_A(0xf6);


not_space:
    SUB_A(0xf6);
    RET;

}

static uint8_t GetMartPrice_CharToNybble(uint8_t a){
    // LD_A_de;
    // INC_DE;
    // CP_A(0x7f);
    // IF_NZ goto not_space;
    if(a == 0x7f)
        // LD_A(0xf6);
        a = 0xf6;

// not_space:
    // SUB_A(0xf6);
    // RET;
    return a - 0xf6;
}

//  Return price de in BCD at hl and in tiles at wStringBuffer1.
void GetMartPrice_Conv(item_price_s* hl, uint16_t price){
    // PUSH_HL;
    // LD_A_D;
    // LD_addr_A(wStringBuffer2);
    // LD_A_E;
    // LD_addr_A(wStringBuffer2 + 1);
    uint16_t value = NativeToBigEndian16(price);
    // LD_HL(wStringBuffer1);
    // LD_DE(wStringBuffer2);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 6);  // 6 digits
    // CALL(aPrintNum);
    PrintNum_Conv2(wram->wStringBuffer1, &value, PRINTNUM_LEADINGZEROS | 2, 6);
    // POP_HL;

    // LD_DE(wStringBuffer1);
    uint8_t* de = wram->wStringBuffer1;
    // LD_C(6 / 2);  // 6 digits
    uint8_t c = 6 / 2;

    do {
    // loop:
        // CALL(aGetMartPrice_CharToNybble);
        // SWAP_A;
        // LD_B_A;
        uint8_t hi = GetMartPrice_CharToNybble(*(de++)) << 4;
        // CALL(aGetMartPrice_CharToNybble);
        // OR_A_B;
        uint8_t lo = GetMartPrice_CharToNybble(*(de++));
        // LD_hli_A;
        hl->price = lo | hi;

        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

//  Load the mart pointer.  Mart data is local (no need for bank).
void ReadMart(void){
    // LD_HL(wMartPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // PUSH_HL;
    const item_price_s* hl = (const item_price_s*)sMartPointer;
//  set hl to the first item
    // INC_HL;
    // LD_BC(wMartItem1BCD);
    item_price_s* bc = sMartItems;
    // LD_DE(wCurMartItems);
    item_t* de = sCurMart.items;

    uint32_t i = 0;
    while(i < wram->wCurMartCount) {
    // loop:
    //  copy the items to wCurMartItems
        // LD_A_hli;
        // LD_de_A;
        de[i] = hl[i].id;
        // INC_DE;
    //  -1 is the terminator
        // CP_A(-1);
        // IF_Z goto done;

        // PUSH_DE;
    //  copy the price to de
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
    //  convert the price to 3-byte BCD at [bc]
        // PUSH_HL;
        // LD_H_B;
        // LD_L_C;
        // CALL(aGetMartPrice);
        GetMartPrice_Conv(bc + i, hl[i].price);
        // LD_B_H;
        // LD_C_L;
        // POP_HL;

        // POP_DE;
        // goto loop;
        i++;
    }

    de[i] = (item_t)-1;
// done:
    // POP_HL;
    // LD_A_hl;
    // LD_addr_A(wCurMartCount);
    // RET;

// INCLUDE "data/items/bargain_shop.asm"
}

void BuyMenu(void){
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // FARCALL(aBlankScreen);
    BlankScreen();
    // XOR_A_A;
    // LD_addr_A(wMenuScrollPositionBackup);
    wram->wMenuScrollPositionBackup = 0;
    // LD_A(1);
    // LD_addr_A(wMenuCursorPositionBackup);
    wram->wMenuCursorPositionBackup = 1;

    bool quit = false;
    do {
    // loop:
        // CALL(aBuyMenuLoop);  // menu loop
        quit = BuyMenuLoop();
        // IF_NC goto loop;
    } while(!quit);
    // CALL(aCloseSubmenu);
    CloseSubmenu_Conv();
    // RET;
}

//  load text from a nested table
//  which table is in wMartType
//  which entry is in register a
void LoadBuyMenuText(uint8_t a){
    // PUSH_AF;
    // CALL(aGetMartDialogGroup);  // gets a pointer from GetMartDialogGroup.MartTextFunctionPointers
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // POP_AF;
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aPrintText);
    PrintText_Conv2(GetMartDialogGroup(wram->wMartType)->texts[a]);
    // RET;
}

bool MartAskPurchaseQuantity(void){
    // CALL(aGetMartDialogGroup);  // gets a pointer from GetMartDialogGroup.MartTextFunctionPointers
    // INC_HL;
    // INC_HL;
    // LD_A_hl;
    uint8_t group = GetMartDialogGroup(wram->wMartType)->group;
    // AND_A_A;
    // JP_Z (mStandardMartAskPurchaseQuantity);
    // CP_A(1);
    // JP_Z (mBargainShopAskPurchaseQuantity);
    // JP(mRooftopSaleAskPurchaseQuantity);
    switch(group) {
        case 0:  return StandardMartAskPurchaseQuantity();
        case 1:  return BargainShopAskPurchaseQuantity();
        default: return RooftopSaleAskPurchaseQuantity();
    }
}

const struct MartDialogGroup* GetMartDialogGroup(uint8_t type){
    static const txt_cmd_s* StandardMartPointers[] = {
        MartHowManyText,
        MartFinalPriceText,
        MartNoMoneyText,
        MartPackFullText,
        MartThanksText,
        NULL, //dw ['BuyMenuLoop'];
    };
    static const txt_cmd_s* HerbShopPointers[] = {
        HerbalLadyHowManyText,
        HerbalLadyFinalPriceText,
        HerbalLadyNoMoneyText,
        HerbalLadyPackFullText,
        HerbalLadyThanksText,
        NULL, //dw ['BuyMenuLoop'];
    };
    static const txt_cmd_s* BargainShopPointers[] = {
        NULL, //dw ['BuyMenuLoop'];
        BargainShopFinalPriceText,
        BargainShopNoFundsText,
        BargainShopPackFullText,
        BargainShopThanksText,
        BargainShopSoldOutText,
    };
    static const txt_cmd_s* PharmacyPointers[] = {
        PharmacyHowManyText,
        PharmacyFinalPriceText,
        PharmacyNoMoneyText,
        PharmacyPackFullText,
        PharmacyThanksText,
        NULL, //dw ['BuyMenuLoop'];
    };
    static const struct MartDialogGroup MartTextFunctionPointers[] = {
        {StandardMartPointers, 0},
        {HerbShopPointers, 0},
        {BargainShopPointers, 1},
        {PharmacyPointers, 0},
        {StandardMartPointers, 2},
    };
    // LD_A_addr(wMartType);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mGetMartDialogGroup_MartTextFunctionPointers);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // RET;
    return MartTextFunctionPointers + type;
}

bool BuyMenuLoop(void){
    // FARCALL(aPlaceMoneyTopRight);
    PlaceMoneyTopRight();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // LD_HL(mMenuHeader_Buy);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader_Conv2(&MenuHeader_Buy);
    // LD_A_addr(wMenuCursorPositionBackup);
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = wram->wMenuCursorPositionBackup;
    // LD_A_addr(wMenuScrollPositionBackup);
    // LD_addr_A(wMenuScrollPosition);
    wram->wMenuScrollPosition = wram->wMenuScrollPositionBackup;
    // CALL(aScrollingMenu);
    ScrollingMenu_Conv();
    // LD_A_addr(wMenuScrollPosition);
    // LD_addr_A(wMenuScrollPositionBackup);
    wram->wMenuScrollPositionBackup = wram->wMenuScrollPosition;
    // LD_A_addr(wMenuCursorY);
    // LD_addr_A(wMenuCursorPositionBackup);
    wram->wMenuCursorPositionBackup = wram->wMenuCursorY;
    // CALL(aSpeechTextbox);
    SpeechTextbox();
    // LD_A_addr(wMenuJoypad);
    // CP_A(B_BUTTON);
    // IF_Z goto set_carry;
    if(wram->wMenuJoypad == B_BUTTON)
        return true;
    // CP_A(A_BUTTON);
    // IF_Z goto useless_pointer;
    if(wram->wMenuJoypad != A_BUTTON)
        return false;

// useless_pointer:
    // CALL(aMartAskPurchaseQuantity);
    // IF_C goto cancel;
    // CALL(aMartConfirmPurchase);
    // IF_C goto cancel;
    if(!MartAskPurchaseQuantity() && MartConfirmPurchase()){
        // LD_DE(wMoney);
        // LD_BC(hMoneyTemp);
        // LD_A(3);  // useless load
        // CALL(aCompareMoney);
        // IF_C goto insufficient_funds;
        u8_flag_s res = CompareMoney_Conv(hram->hMoneyTemp, wram->wMoney);
        if(res.flag) {
        // insufficient_funds:
            // LD_A(MARTTEXT_NOT_ENOUGH_MONEY);
            // CALL(aLoadBuyMenuText);
            LoadBuyMenuText(MARTTEXT_NOT_ENOUGH_MONEY);
            // CALL(aJoyWaitAorB);
            JoyWaitAorB_Conv();
            // AND_A_A;
            // RET;
            return false;
        }

        // LD_HL(wNumItems);
        // CALL(aReceiveItem);
        // IF_NC goto insufficient_bag_space;
        if(!ReceiveItem_Conv((item_pocket_s*)&wram->wNumItems, wram->wCurItem, wram->wItemQuantityChange)){
        // insufficient_bag_space:
            // LD_A(MARTTEXT_BAG_FULL);
            // CALL(aLoadBuyMenuText);
            LoadBuyMenuText(MARTTEXT_BAG_FULL);
            // CALL(aJoyWaitAorB);
            JoyWaitAorB_Conv();
            // AND_A_A;
            // RET;
            return false;
        }
        // LD_A_addr(wMartItemID);
        // LD_E_A;
        // LD_D(0);
        // LD_B(SET_FLAG);
        // LD_HL(wBargainShopFlags);
        // CALL(aFlagAction);
        FlagAction(&wram->wBargainShopFlags, wram->wMartItemID, SET_FLAG);
        // CALL(aPlayTransactionSound);
        PlayTransactionSound();
        // LD_DE(wMoney);
        // LD_BC(hMoneyTemp);
        // CALL(aTakeMoney);
        TakeMoney_Conv(wram->wMoney, hram->hMoneyTemp);
        // LD_A(MARTTEXT_HERE_YOU_GO);
        // CALL(aLoadBuyMenuText);
        LoadBuyMenuText(MARTTEXT_HERE_YOU_GO);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB_Conv();
    }

// cancel:
    // CALL(aSpeechTextbox);
    SpeechTextbox();
    // AND_A_A;
    // RET;
    return false;

// set_carry:
    // SCF;
    // RET;
}

bool StandardMartAskPurchaseQuantity(void){
    // LD_A(MAX_ITEM_STACK);
    // LD_addr_A(wItemQuantity);
    wram->wItemQuantity = MAX_ITEM_STACK;
    // LD_A(MARTTEXT_HOW_MANY);
    // CALL(aLoadBuyMenuText);
    LoadBuyMenuText(MARTTEXT_HOW_MANY);
    // FARCALL(aSelectQuantityToBuy);
    bool cancel = SelectQuantityToBuy();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // RET;
    return cancel;
}

bool MartConfirmPurchase(void){
    // PREDEF(pPartyMonItemName);
    PartyMonItemName_Conv(wram->wCurItem);
    // LD_A(MARTTEXT_COSTS_THIS_MUCH);
    // CALL(aLoadBuyMenuText);
    LoadBuyMenuText(MARTTEXT_COSTS_THIS_MUCH);
    // CALL(aYesNoBox);
    // RET;
    return YesNoBox_Conv();
}

bool BargainShopAskPurchaseQuantity(void){
    // LD_A(1);
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = 1;
    // LD_A_addr(wMartItemID);
    // LD_E_A;
    // LD_D(0);
    // LD_B(CHECK_FLAG);
    // LD_HL(wBargainShopFlags);
    // CALL(aFlagAction);
    // LD_A_C;
    // AND_A_A;
    // IF_NZ goto SoldOut;
    if(FlagAction(&wram->wBargainShopFlags, wram->wMartItemID, CHECK_FLAG)){
    // SoldOut:
        // LD_A(MARTTEXT_SOLD_OUT);
        // CALL(aLoadBuyMenuText);
        LoadBuyMenuText(MARTTEXT_SOLD_OUT);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB_Conv();
        // SCF;
        // RET;
        return true;
    }
    // LD_A_addr(wMartItemID);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wMartPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // INC_HL;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // INC_HL;
    const item_price_s* hl = (const item_price_s*)sMartPointer;
    uint16_t price = hl->price;
    // LD_A_hli;
    // LDH_addr_A(hMoneyTemp + 2);
    hram->hMoneyTemp[2] = price & 0xff;
    // LD_A_hl;
    // LDH_addr_A(hMoneyTemp + 1);
    hram->hMoneyTemp[1] = (price >> 8) & 0xff;
    // XOR_A_A;
    // LDH_addr_A(hMoneyTemp);
    hram->hMoneyTemp[0] = 0;
    // AND_A_A;
    // RET;
    return false;
}

static uint16_t RooftopSaleAskPurchaseQuantity_GetSalePrice(void){
    // LD_A_addr(wMartItemID);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wMartPointer);
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // INC_HL;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // INC_HL;
    const item_price_s* hl = (const item_price_s*)sMartPointer;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // RET;
    return hl->price;
}

bool RooftopSaleAskPurchaseQuantity(void){
    // LD_A(MARTTEXT_HOW_MANY);
    // CALL(aLoadBuyMenuText);
    LoadBuyMenuText(MARTTEXT_HOW_MANY);
    // CALL(aRooftopSaleAskPurchaseQuantity_GetSalePrice);
    uint16_t price = RooftopSaleAskPurchaseQuantity_GetSalePrice();
    // LD_A(MAX_ITEM_STACK);
    // LD_addr_A(wItemQuantity);
    wram->wItemQuantity = MAX_ITEM_STACK;
    // FARCALL(aRooftopSale_SelectQuantityToBuy);
    bool cancel = RooftopSale_SelectQuantityToBuy(price);
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // RET;
    return cancel;
}

const txt_cmd_s MartHowManyText[] = {
    text_far(v_MartHowManyText)
    text_end
};

const txt_cmd_s MartFinalPriceText[] = {
    text_far(v_MartFinalPriceText)
    text_end
};

static void MenuHeader_PrintBCDPrices(const struct MenuData* data, tile_t* de){
    (void)data;
    uint8_t price[3];
    // LD_A_addr(wScrollingMenuCursorPosition);
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wMartItem1BCD);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // ADD_HL_BC;
    uint16_t price_x = sMartItems[wram->wScrollingMenuCursorPosition].price;
    price[0] = (price_x & 0xff0000) >> 16;
    price[1] = (price_x & 0x00ff00) >>  8;
    price[2] = (price_x & 0x0000ff);
    // PUSH_DE;
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    // LD_C(PRINTNUM_LEADINGZEROS | PRINTNUM_MONEY | 3);
    // CALL(aPrintBCDNumber);
    PrintNum_Conv2(de + SCREEN_WIDTH, price, PRINTNUM_MONEY | 3, 6);
    // RET;
}

const struct MenuHeader MenuHeader_Buy = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(1, 3, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
// MenuData:
        .flags=SCROLLINGMENU_DISPLAY_ARROWS | SCROLLINGMENU_ENABLE_FUNCTION3,  // flags
        .scrollingMenu = {
            .rows=4, .cols=8,  // rows, columns
            .format=SCROLLINGMENU_ITEMS_NORMAL,  // item format
            //dbw ['0', 'wCurMartCount']
            .list=&sCurMart.count,
            //dba ['PlaceMenuItemName']
            .func1=PlaceMenuItemName_Conv,
            //dba ['.PrintBCDPrices']
            .func2=MenuHeader_PrintBCDPrices,
            //dba ['UpdateItemDescription']
            .func3=UpdateItemDescription,
        },
    },
    .defaultOption = 1,  // default option
};

const txt_cmd_s HerbShopLadyIntroText[] = {
    text_far(v_HerbShopLadyIntroText)
    text_end
};

const txt_cmd_s HerbalLadyHowManyText[] = {
    text_far(v_HerbalLadyHowManyText)
    text_end
};

const txt_cmd_s HerbalLadyFinalPriceText[] = {
    text_far(v_HerbalLadyFinalPriceText)
    text_end
};

const txt_cmd_s HerbalLadyThanksText[] = {
    text_far(v_HerbalLadyThanksText)
    text_end
};

const txt_cmd_s HerbalLadyPackFullText[] = {
    text_far(v_HerbalLadyPackFullText)
    text_end
};

const txt_cmd_s HerbalLadyNoMoneyText[] = {
    text_far(v_HerbalLadyNoMoneyText)
    text_end
};

const txt_cmd_s HerbalLadyComeAgainText[] = {
    text_far(v_HerbalLadyComeAgainText)
    text_end
};

const txt_cmd_s BargainShopIntroText[] = {
    text_far(v_BargainShopIntroText)
    text_end
};

const txt_cmd_s BargainShopFinalPriceText[] = {
    text_far(v_BargainShopFinalPriceText)
    text_end
};

const txt_cmd_s BargainShopThanksText[] = {
    text_far(v_BargainShopThanksText)
    text_end
};

const txt_cmd_s BargainShopPackFullText[] = {
    text_far(v_BargainShopPackFullText)
    text_end
};

const txt_cmd_s BargainShopSoldOutText[] = {
    text_far(v_BargainShopSoldOutText)
    text_end
};

const txt_cmd_s BargainShopNoFundsText[] = {
    text_far(v_BargainShopNoFundsText)
    text_end
};

const txt_cmd_s BargainShopComeAgainText[] = {
    text_far(v_BargainShopComeAgainText)
    text_end
};

const txt_cmd_s PharmacyIntroText[] = {
    text_far(v_PharmacyIntroText)
    text_end
};

const txt_cmd_s PharmacyHowManyText[] = {
    text_far(v_PharmacyHowManyText)
    text_end
};

const txt_cmd_s PharmacyFinalPriceText[] = {
    text_far(v_PharmacyFinalPriceText)
    text_end
};

const txt_cmd_s PharmacyThanksText[] = {
    text_far(v_PharmacyThanksText)
    text_end
};

const txt_cmd_s PharmacyPackFullText[] = {
    text_far(v_PharmacyPackFullText)
    text_end
};

const txt_cmd_s PharmacyNoMoneyText[] = {
    text_far(v_PharmacyNoMoneyText)
    text_end
};

const txt_cmd_s PharmacyComeAgainText[] = {
    text_far(v_PharmacyComeAgainText)
    text_end
};

static void SellMenu_TryToSellItem(void) {
    // FARCALL(aCheckItemMenu);
    uint8_t attr = CheckItemMenu_Conv(wram->wCurItem);
    // LD_A_addr(wItemAttributeValue);
    // LD_HL(mSellMenu_dw);
    // RST(aJumpTable);
    // RET;
    switch(attr){
    // dw:
        //dw ['.try_sell'];
        case 0:
        case 4:
        case 5:
        case 6:
        // try_sell:
            // FARCALL(av_CheckTossableItem);
            // LD_A_addr(wItemAttributeValue);
            // AND_A_A;
            // IF_Z goto okay_to_sell;
            if(!v_CheckTossableItem_Conv(wram->wCurItem)){
                // LD_HL(mMartCantBuyText);
                // CALL(aPrintText);
                PrintText_Conv2(MartCantBuyText);
                // AND_A_A;
                // RET;
                return;
            }

        // okay_to_sell:
            // LD_HL(mMartSellHowManyText);
            // CALL(aPrintText);
            PrintText_Conv2(MartSellHowManyText);
            // FARCALL(aPlaceMoneyAtTopLeftOfTextbox);
            PlaceMoneyAtTopLeftOfTextbox();
            // FARCALL(aSelectQuantityToSell);
            bool declined = SelectQuantityToSell();
            // CALL(aExitMenu);
            ExitMenu_Conv2();
            // IF_C goto declined;
            if(!declined) {
                // hlcoord(1, 14, wTilemap);
                // LD_BC((3 << 8) | 18);
                // CALL(aClearBox);
                ClearBox(coord(1, 14, wram->wTilemap), 18, 3);
                // LD_HL(mMartSellPriceText);
                // CALL(aPrintTextboxText);
                PrintTextboxText_Conv2(MartSellPriceText);
                // CALL(aYesNoBox);
                // IF_C goto declined;
                if(YesNoBox_Conv()) {
                    // LD_DE(wMoney);
                    // LD_BC(hMoneyTemp);
                    // CALL(aGiveMoney);
                    GiveMoney_Conv(wram->wMoney, hram->hMoneyTemp);
                    // LD_A_addr(wMartItemID);
                    // LD_HL(wNumItems);
                    // CALL(aTossItem);
                    TossItem_Conv((item_pocket_s*)&wram->wNumItems, wram->wCurItem);
                    // PREDEF(pPartyMonItemName);
                    PartyMonItemName_Conv(wram->wCurItem);
                    // hlcoord(1, 14, wTilemap);
                    // LD_BC((3 << 8) | 18);
                    // CALL(aClearBox);
                    ClearBox(coord(1, 14, wram->wTilemap), 18, 3);
                    // LD_HL(mMartBoughtText);
                    // CALL(aPrintTextboxText);
                    PrintTextboxText_Conv2(MartBoughtText);
                    // CALL(aPlayTransactionSound);
                    PlayTransactionSound();
                    // FARCALL(aPlaceMoneyBottomLeft);
                    PlaceMoneyBottomLeft();
                    // CALL(aJoyWaitAorB);
                    JoyWaitAorB_Conv();
                }
            }

        // declined:
            // CALL(aExitMenu);
            ExitMenu_Conv2();
            // AND_A_A;
            // RET;
            return;
        //dw ['.cant_buy'];
        //dw ['.cant_buy'];
        //dw ['.cant_buy'];
        case 1:
        case 2:
        case 3:
        // cant_buy:
            // RET;
            return;
        //dw ['.try_sell'];
        //dw ['.try_sell'];
        //dw ['.try_sell'];
    }
}

void SellMenu(void){
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates();
    // FARCALL(aDepositSellInitPackBuffers);
    DepositSellInitPackBuffers();

    while(1) {
    // loop:
        // FARCALL(aDepositSellPack);
        DepositSellPack();
        // LD_A_addr(wPackUsedItem);
        // AND_A_A;
        // JP_Z (mSellMenu_quit);
        if(wram->wPackUsedItem == 0)
            break;
        // CALL(aSellMenu_TryToSellItem);
        SellMenu_TryToSellItem();
        // goto loop;
    }

// quit:
    // CALL(aReturnToMapWithSpeechTextbox);
    ReturnToMapWithSpeechTextbox_Conv();
    // AND_A_A;
    // RET;
    return;


NothingToSell:
//   //  unreferenced
    LD_HL(mSellMenu_NothingToSellText);
    CALL(aMenuTextboxBackup);
    AND_A_A;
    RET;


//NothingToSellText:
    //text_far(v_NothingToSellText)
    //text_end
}

const txt_cmd_s MartSellHowManyText[] = {
    text_far(v_MartSellHowManyText)
    text_end
};

const txt_cmd_s MartSellPriceText[] = {
    text_far(v_MartSellPriceText)
    text_end
};

void UnusedDummyString(void){
//  //  unreferenced
    //db ['"！ダミー！@"'];  // "!Dummy!"
}

const txt_cmd_s MartWelcomeText[] = {
    text_far(v_MartWelcomeText)
    text_end
};

const struct MenuHeader MenuHeader_BuySell = {
    .flags=MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, 7, 8),
    //dw ['.MenuData'];
    .data = &(struct MenuData) {
    // MenuData:
        .flags = STATICMENU_CURSOR,  // strings
        .verticalMenu = {
            .count = 3,
            //db ['3'];  // items
            .options = (const char*[]) {
                "BUY@",
                "SELL@",
                "QUIT@",
            },
        },
    },
    .defaultOption = 1,  // default option
};

const txt_cmd_s MartThanksText[] = {
    text_far(v_MartThanksText)
    text_end
};

const txt_cmd_s MartNoMoneyText[] = {
    text_far(v_MartNoMoneyText)
    text_end
};

const txt_cmd_s MartPackFullText[] = {
    text_far(v_MartPackFullText)
    text_end
};

const txt_cmd_s MartCantBuyText[] = {
    text_far(v_MartCantBuyText)
    text_end
};

const txt_cmd_s MartComeAgainText[] = {
    text_far(v_MartComeAgainText)
    text_end
};

const txt_cmd_s MartAskMoreText[] = {
    text_far(v_MartAskMoreText)
    text_end
};

const txt_cmd_s MartBoughtText[] = {
    text_far(v_MartBoughtText)
    text_end
};

void PlayTransactionSound(void){
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_DE(SFX_TRANSACTION);
    // CALL(aPlaySFX);
    PlaySFX(SFX_TRANSACTION);
    // RET;
}

void MartTextbox(const txt_cmd_s* hl){
    // CALL(aMenuTextbox);
    MenuTextbox_Conv(hl);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB_Conv();
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // RET;
}
