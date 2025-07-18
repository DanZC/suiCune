#include "../../constants.h"
#include "mom_phone.h"
#include "money.h"
#include "../overworld/events.h"
#include "../overworld/decorations.h"
#include "../../home/item.h"
#include "../../home/random.h"
#include "../../home/map.h"
#include "../../util/scripting.h"
#include "../../data/text/common.h"
#include "../phone/phone.h"

enum {
    MOM_ITEM = 1,
    MOM_DOLL
};

struct MomPhoneItem {
    uint32_t moneyToTrigger;
    uint32_t cost;
    uint8_t kind;
    item_t item;
};

const struct MomPhoneItem MomItems_1[] = {
    {      0,   600, MOM_ITEM, SUPER_POTION},
    {      0,    90, MOM_ITEM, ANTIDOTE},
    {      0,   180, MOM_ITEM, POKE_BALL},
    {      0,   450, MOM_ITEM, ESCAPE_ROPE},
    {      0,   500, MOM_ITEM, GREAT_BALL},
};

#define NUM_MOM_ITEMS_1 lengthof(MomItems_1)

const struct MomPhoneItem MomItems_2[] = {
    {    900,   600, MOM_ITEM, SUPER_POTION},
    {   4000,   270, MOM_ITEM, REPEL},
    {   7000,   600, MOM_ITEM, SUPER_POTION},
    {  10000,  1800, MOM_DOLL, DECO_CHARMANDER_DOLL},
    {  15000,  3000, MOM_ITEM, MOON_STONE},
    {  19000,   600, MOM_ITEM, SUPER_POTION},
    {  30000,  4800, MOM_DOLL, DECO_CLEFAIRY_DOLL},
    {  40000,   900, MOM_ITEM, HYPER_POTION},
    {  50000,  8000, MOM_DOLL, DECO_PIKACHU_DOLL},
    { 100000, 22800, MOM_DOLL, DECO_BIG_SNORLAX_DOLL},
};

#define NUM_MOM_ITEMS_2 lengthof(MomItems_2)
// NUM_MOM_ITEMS_2 EQUS "((MomItems_2.End - MomItems_2) / 8)"

static bool CheckBalance_MomItem2(void);
static void MomBuysItem_DeductFunds(void);
static bool Mom_GiveItemOrDoll(void);
static Script_fn_t Mom_GetScriptPointer(void);
static const struct MomPhoneItem* GetItemFromMom(void);

static void MomTriesToBuySomething_ASMFunction(void) {
    // CALL(aMomBuysItem_DeductFunds);
    MomBuysItem_DeductFunds();
    // CALL(aMom_GetScriptPointer);
    Script_fn_t script = Mom_GetScriptPointer();
    // LD_A_addr(wWhichMomItemSet);
    // AND_A_A;
    // IF_NZ goto ok;
    if(gPlayer.whichMomItemSet == 0) {
        // LD_HL(wWhichMomItem);
        // INC_hl;
        gPlayer.whichMomItem++;
    }

// ok:
    // LD_A(PHONE_MOM);
    // LD_addr_A(wCurCaller);
    gPlayer.curCaller = PHONE_MOM;
    // LD_BC(wCallerContact);
    // LD_HL(PHONE_CONTACT_TRAINER_CLASS);
    // ADD_HL_BC;
    // LD_hl(TRAINER_NONE);
    gCallerContact.trainerClass = TRAINER_NONE;
    // INC_HL;
    // LD_hl(PHONE_MOM);
    gCallerContact.trainerId = PHONE_MOM;
    // LD_HL(PHONE_CONTACT_SCRIPT2_BANK);
    // ADD_HL_BC;
    // LD_A(BANK(aMom_GetScriptPointer));
    // LD_hli_A;
    // LD_A_E;
    // LD_hli_A;
    // LD_A_D;
    // LD_hl_A;
    gCallerContact.callerScript = script;
    // RET;
}

static bool MomTriesToBuySomething_Script(script_s* s) {
    SCRIPT_BEGIN
    //callasm ['.ASMFunction']
    MomTriesToBuySomething_ASMFunction();
    sjump(Script_ReceivePhoneCall)
    SCRIPT_END
}


void MomTriesToBuySomething(void){
    // LD_A_addr(wMapReentryScriptQueueFlag);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wMapReentryScriptQueueFlag != 0)
        return;
    // CALL(aGetMapPhoneService);
    // AND_A_A;
    // RET_NZ ;
    if(GetMapPhoneService())
        return;
    // XOR_A_A;
    // LD_addr_A(wWhichMomItemSet);
    gPlayer.whichMomItemSet = 0;
    // CALL(aCheckBalance_MomItem2);
    // RET_NC ;
    if(!CheckBalance_MomItem2())
        return;
    // CALL(aMom_GiveItemOrDoll);
    // RET_NC ;
    if(!Mom_GiveItemOrDoll())
        return;
    // LD_B(BANK(aMomTriesToBuySomething_Script));
    // LD_DE(mMomTriesToBuySomething_Script);
    // FARCALL(aLoadScriptBDE);
    LoadScriptBDE(MomTriesToBuySomething_Script);
    // SCF;
    // RET;
    return;
}

static void CheckBalance_MomItem2_AddMoney(void) {
    // LD_DE(wMomItemTriggerBalance);
    // LD_BC(hMoneyTemp);
    // FARCALL(aAddMoney);
    // RET;
    return AddMoney(gPlayer.momItemTriggerBalance, hram.hMoneyTemp);
}

static bool CheckBalance_MomItem2(void){
    // LD_A_addr(wWhichMomItem);
    // CP_A(NUM_MOM_ITEMS_2);
    // IF_NC goto nope;
    if(gPlayer.whichMomItem < NUM_MOM_ITEMS_2) {
        // CALL(aGetItemFromMom);
        const struct MomPhoneItem* item = GetItemFromMom();
        // LD_A_hli;
        // LDH_addr_A(hMoneyTemp);
        hram.hMoneyTemp[0] = HIGH(item->cost >> 8);
        // LD_A_hli;
        // LDH_addr_A(hMoneyTemp + 1);
        hram.hMoneyTemp[1] = HIGH(item->cost);
        // LD_A_hli;
        // LDH_addr_A(hMoneyTemp + 2);
        hram.hMoneyTemp[2] = LOW(item->cost);
        // LD_DE(wMomsMoney);
        // LD_BC(hMoneyTemp);
        // FARCALL(aCompareMoney);
        u8_flag_s res = CompareMoney(hram.hMoneyTemp, gPlayer.momsMoney);
        // IF_NC goto have_enough_money;
        if(!res.flag) {
        // have_enough_money:
            // SCF;
            // RET;
            return true;
        }
    }

// nope:
    // goto check_have_2300;

// check_have_2300:
    // LD_HL(hMoneyTemp);
    // LD_hl(HIGH(MOM_MONEY >> 8));
    hram.hMoneyTemp[0] = HIGH(MOM_MONEY >> 8);
    // INC_HL;
    // LD_hl(HIGH(MOM_MONEY));  // mid
    hram.hMoneyTemp[1] = HIGH(MOM_MONEY);
    // INC_HL;
    // LD_hl(LOW(MOM_MONEY));
    hram.hMoneyTemp[2] = LOW(MOM_MONEY);

    while(1) {
    // loop:
        // LD_DE(wMomItemTriggerBalance);
        // LD_BC(wMomsMoney);
        // FARCALL(aCompareMoney);
        u8_flag_s res = CompareMoney(gPlayer.momsMoney, gPlayer.momItemTriggerBalance);
        // IF_Z goto exact;
        if(res.a == 0) {
        // exact:
            // CALL(aCheckBalance_MomItem2_AddMoney);
            CheckBalance_MomItem2_AddMoney();
            // LD_A(NUM_MOM_ITEMS_1);
            // CALL(aRandomRange);
            // INC_A;
            // LD_addr_A(wWhichMomItemSet);
            gPlayer.whichMomItemSet = RandomRange(NUM_MOM_ITEMS_1) + 1;
            // SCF;
            // RET;
            return true;
        }
        // IF_NC goto less_than;
        if(!res.flag) {
        // less_than:
            // XOR_A_A;
            // RET;
            return false;
        }
        // CALL(aCheckBalance_MomItem2_AddMoney);
        CheckBalance_MomItem2_AddMoney();
        // goto loop;
    }
}

static void MomBuysItem_DeductFunds(void){
    // CALL(aGetItemFromMom);
    const struct MomPhoneItem* item = GetItemFromMom();
    // LD_DE(3);  // cost
    // ADD_HL_DE;
    // LD_A_hli;
    // LDH_addr_A(hMoneyTemp);
    hram.hMoneyTemp[0] = HIGH(item->cost >> 8);
    // LD_A_hli;
    // LDH_addr_A(hMoneyTemp + 1);
    hram.hMoneyTemp[1] = HIGH(item->cost);
    // LD_A_hli;
    // LDH_addr_A(hMoneyTemp + 2);
    hram.hMoneyTemp[2] = LOW(item->cost);
    // LD_DE(wMomsMoney);
    // LD_BC(hMoneyTemp);
    // FARCALL(aTakeMoney);
    TakeMoney(gPlayer.momsMoney, hram.hMoneyTemp);
    // RET;
}

static bool Mom_GiveItemOrDoll(void){
    // CALL(aGetItemFromMom);
    const struct MomPhoneItem* item = GetItemFromMom();
    // LD_DE(6);  // item type
    // ADD_HL_DE;
    // LD_A_hli;
    // CP_A(MOM_ITEM);
    // IF_Z goto not_doll;
    if(item->kind != MOM_ITEM) {
        // LD_A_hl;
        // LD_C_A;
        // LD_B(1);
        // FARCALL(aDecorationFlagAction_c);
        DecorationFlagAction_c(item->item, 1);
        // SCF;
        // RET;
        return true;
    }
    else {
    // not_doll:
        // LD_A_hl;
        // LD_addr_A(wCurItem);
        // LD_A(1);
        // LD_addr_A(wItemQuantityChange);
        // LD_HL(wNumPCItems);
        // CALL(aReceiveItem);
        // RET;
        return ReceiveItem(GetItemPocket(PC_ITEM_POCKET), item->item, 1);
    }
}

static const txt_cmd_s MomHiHowAreYouText[] = {
    text_far(v_MomHiHowAreYouText)
    text_end
};

static const txt_cmd_s MomFoundAnItemText[] = {
    text_far(v_MomFoundAnItemText)
    text_end
};

static const txt_cmd_s MomBoughtWithYourMoneyText[] = {
    text_far(v_MomBoughtWithYourMoneyText)
    text_end
};

static const txt_cmd_s MomItsInPCText[] = {
    text_far(v_MomItsInPCText)
    text_end
};

static const txt_cmd_s MomFoundADollText[] = {
    text_far(v_MomFoundADollText)
    text_end
};

static const txt_cmd_s MomItsInYourRoomText[] = {
    text_far(v_MomItsInYourRoomText)
    text_end
};

static bool Mom_ItemScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(MomHiHowAreYouText)
    writetext(MomFoundAnItemText)
    writetext(MomBoughtWithYourMoneyText)
    writetext(MomItsInPCText)
    s_end
    SCRIPT_END
}

static bool Mom_DollScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(MomHiHowAreYouText)
    writetext(MomFoundADollText)
    writetext(MomBoughtWithYourMoneyText)
    writetext(MomItsInYourRoomText)
    s_end
    SCRIPT_END
}

static Script_fn_t Mom_GetScriptPointer(void){
    // CALL(aGetItemFromMom);
    // LD_DE(6);  // item type
    // ADD_HL_DE;
    const struct MomPhoneItem* item = GetItemFromMom();
    // LD_A_hli;
    // LD_DE(mMom_GetScriptPointer_ItemScript);
    // CP_A(MOM_ITEM);
    // RET_Z ;
    if(item->kind == MOM_ITEM)
        return Mom_ItemScript;
    // LD_DE(mMom_GetScriptPointer_DollScript);
    // RET;
    return Mom_DollScript;
}

static const struct MomPhoneItem* GetItemFromMom(void){
    uint8_t a;
    const struct MomPhoneItem* de;
    // LD_A_addr(wWhichMomItemSet);
    // AND_A_A;
    // IF_Z goto zero;
    if(gPlayer.whichMomItemSet != 0) {
        // DEC_A;
        a = gPlayer.whichMomItemSet - 1;
        // LD_DE(mMomItems_1);
        de = MomItems_1;
        // goto GetFromList1;
    }
    else {
    // zero:
        // LD_A_addr(wWhichMomItem);
        // CP_A(NUM_MOM_ITEMS_2);
        // IF_C goto ok;
        if(gPlayer.whichMomItem >= NUM_MOM_ITEMS_2) {
            // XOR_A_A;
            a = 0;
        }
        else {
            a = gPlayer.whichMomItem;
        }

    // ok:
        // LD_DE(mMomItems_2);
        de = MomItems_2;
    }

// GetFromList1:
    // LD_L_A;
    // LD_H(0);
    // for(int rept = 0; rept < 3; rept++){  //  multiply hl by 8
    // ADD_HL_HL;
    // }
    // ADD_HL_DE;
    // RET;
    return de + a;

// INCLUDE "data/items/mom_phone.asm"
}

void DummyPredef3A_DummyData(void){
//  //  unreferenced
    //db ['0'];

    return DummyPredef3A();
}

void DummyPredef3A(void){
    RET;

}

void DummyPredef3A_DummyFunction(void){
//  //  unreferenced
    RET;

}
