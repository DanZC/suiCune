#include "../../constants.h"
#include "daycare.h"
#include "money.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../../home/audio.h"
#include "../../home/delay.h"
#include "../../home/random.h"
#include "../../home/copy_name.h"
#include "../pokemon/breeding.h"
#include "../pokemon/breedmon_level_growth.h"
#include "../pokemon/bills_pc_top.h"
#include "../pokemon/mail_2.h"
#include "../pokemon/party_menu.h"
#include "../pokemon/move_mon.h"
#include "../pokemon/mon_stats.h"
#include "../pokemon/evolve.h"
#include "../pokemon/experience.h"
#include "../../data/text/common.h"

//  PrintDayCareText.TextTable indexes
enum {
    DAYCARETEXT_MAN_INTRO,
    DAYCARETEXT_MAN_INTRO_EGG,
    DAYCARETEXT_LADY_INTRO,
    DAYCARETEXT_LADY_INTRO_EGG,
    DAYCARETEXT_WHICH_ONE,
    DAYCARETEXT_DEPOSIT,
    DAYCARETEXT_CANT_BREED_EGG,
    DAYCARETEXT_LAST_MON,
    DAYCARETEXT_LAST_ALIVE_MON,
    DAYCARETEXT_COME_BACK_LATER,
    DAYCARETEXT_REMOVE_MAIL,
    DAYCARETEXT_GENIUSES,
    DAYCARETEXT_ASK_WITHDRAW,
    DAYCARETEXT_WITHDRAW,
    DAYCARETEXT_GOT_BACK,
    DAYCARETEXT_TOO_SOON,
    DAYCARETEXT_PARTY_FULL,
    DAYCARETEXT_NOT_ENOUGH_MONEY,
    DAYCARETEXT_OH_FINE,
    DAYCARETEXT_COME_AGAIN,
};

void DayCareMan(void){
    // LD_HL(wDayCareMan);
    // BIT_hl(DAYCAREMAN_HAS_MON_F);
    // IF_NZ goto AskWithdrawMon;
    if(!bit_test(wram->wDayCareMan, DAYCAREMAN_HAS_MON_F)) {
        // LD_HL(wDayCareMan);
        // LD_A(DAYCARETEXT_MAN_INTRO);
        // CALL(aDayCareManIntroText);
        // IF_C goto cancel;
        if(DayCareManIntroText(&wram->wDayCareMan, DAYCARETEXT_MAN_INTRO)) {
            // CALL(aDayCareAskDepositPokemon);
            u8_flag_s res = DayCareAskDepositPokemon();
            // IF_C goto print_text;
            if(res.flag) {
            // print_text:
                // CALL(aPrintDayCareText);
                PrintDayCareText(res.a);
            }
            else {
                // FARCALL(aDepositMonWithDayCareMan);
                DepositMonWithDayCareMan_Conv(res.a);
                // LD_HL(wDayCareMan);
                // SET_hl(DAYCAREMAN_HAS_MON_F);
                bit_set(wram->wDayCareMan, DAYCAREMAN_HAS_MON_F);
                // CALL(aDayCare_DepositPokemonText);
                DayCare_DepositPokemonText();
                // CALL(aDayCare_InitBreeding);
                DayCare_InitBreeding();
                // RET;
                return;
            }
        }
    }
    else {
    // AskWithdrawMon:
        // FARCALL(aGetBreedMon1LevelGrowth);
        u8_pair_s levelGrowth = GetBreedMon1LevelGrowth();
        // LD_HL(wBreedMon1Nickname);
        // CALL(aGetPriceToRetrieveBreedmon);
        GetPriceToRetrieveBreedmon(wram->wBreedMon1Nickname, levelGrowth);
        // CALL(aDayCare_AskWithdrawBreedMon);
        u8_flag_s res = DayCare_AskWithdrawBreedMon();
        // IF_C goto print_text;
        if(res.flag) {
            PrintDayCareText(res.a);
        }
        else {
            // FARCALL(aRetrieveMonFromDayCareMan);
            RetrieveMonFromDayCareMan_Conv();
            // CALL(aDayCare_GetBackMonForMoney);
            DayCare_GetBackMonForMoney();
            // LD_HL(wDayCareMan);
            // RES_hl(DAYCAREMAN_HAS_MON_F);
            bit_reset(wram->wDayCareMan, DAYCAREMAN_HAS_MON_F);
            // RES_hl(DAYCAREMAN_MONS_COMPATIBLE_F);
            bit_reset(wram->wDayCareMan, DAYCAREMAN_MONS_COMPATIBLE_F);
            // goto cancel;
        }
    }

// cancel:
    // LD_A(DAYCARETEXT_COME_AGAIN);
    // CALL(aPrintDayCareText);
    PrintDayCareText(DAYCARETEXT_COME_AGAIN);
    // RET;
}

void DayCareLady(void){
    // LD_HL(wDayCareLady);
    // BIT_hl(DAYCARELADY_HAS_MON_F);
    // IF_NZ goto AskWithdrawMon;
    if(!bit_test(wram->wDayCareLady, DAYCARELADY_HAS_MON_F)) {
        // LD_HL(wDayCareLady);
        // LD_A(DAYCARETEXT_LADY_INTRO);
        // CALL(aDayCareLadyIntroText);
        // IF_C goto cancel;
        if(DayCareLadyIntroText(&wram->wDayCareLady, DAYCARETEXT_LADY_INTRO)) {
            // CALL(aDayCareAskDepositPokemon);
            u8_flag_s res = DayCareAskDepositPokemon();
            // IF_C goto print_text;
            if(res.flag) {
                PrintDayCareText(res.a);
            }
            else {
                // FARCALL(aDepositMonWithDayCareLady);
                DepositMonWithDayCareLady_Conv(res.a);
                // LD_HL(wDayCareLady);
                // SET_hl(DAYCARELADY_HAS_MON_F);
                bit_set(wram->wDayCareLady, DAYCARELADY_HAS_MON_F);
                // CALL(aDayCare_DepositPokemonText);
                DayCare_DepositPokemonText();
                // CALL(aDayCare_InitBreeding);
                DayCare_InitBreeding();
                // RET;
                return;
            }
        }
    }
    else {
    // AskWithdrawMon:
        // FARCALL(aGetBreedMon2LevelGrowth);
        u8_pair_s lvlGrowth = GetBreedMon2LevelGrowth();
        // LD_HL(wBreedMon2Nickname);
        // CALL(aGetPriceToRetrieveBreedmon);
        GetPriceToRetrieveBreedmon(wram->wBreedMon2Nickname, lvlGrowth);
        // CALL(aDayCare_AskWithdrawBreedMon);
        u8_flag_s res = DayCare_AskWithdrawBreedMon();
        // IF_C goto print_text;
        if(res.flag) {
            PrintDayCareText(res.a);
        }
        else {
            // FARCALL(aRetrieveMonFromDayCareLady);
            RetrieveMonFromDayCareLady_Conv();
            // CALL(aDayCare_GetBackMonForMoney);
            DayCare_GetBackMonForMoney();
            // LD_HL(wDayCareLady);
            // RES_hl(DAYCARELADY_HAS_MON_F);
            bit_reset(wram->wDayCareLady, DAYCARELADY_HAS_MON_F);
            // LD_HL(wDayCareMan);
            // RES_hl(DAYCAREMAN_MONS_COMPATIBLE_F);
            bit_reset(wram->wDayCareMan, DAYCARELADY_HAS_MON_F);
            // goto cancel;
        }
    // print_text:
        // CALL(aPrintDayCareText);
    }

// cancel:
    // LD_A(DAYCARETEXT_COME_AGAIN);
    // CALL(aPrintDayCareText);
    PrintDayCareText(DAYCARETEXT_COME_AGAIN);
    // RET;
}

bool DayCareLadyIntroText(uint8_t* hl, uint8_t a){
    // BIT_hl(DAYCARELADY_ACTIVE_F);
    // IF_NZ goto okay;
    if(!bit_test(*hl, DAYCARELADY_ACTIVE_F)) {
        // SET_hl(DAYCARELADY_ACTIVE_F);
        bit_set(*hl, DAYCARELADY_ACTIVE_F);
        // INC_A;
        a++;
    }

// okay:
    // CALL(aPrintDayCareText);
    PrintDayCareText(a);
    // CALL(aYesNoBox);
    // RET;
    return YesNoBox_Conv();
}

bool DayCareManIntroText(uint8_t* hl, uint8_t a){
    // SET_hl(DAYCAREMAN_ACTIVE_F);
    bit_set(*hl, DAYCAREMAN_ACTIVE_F);
    // CALL(aPrintDayCareText);
    PrintDayCareText(a);
    // CALL(aYesNoBox);
    // RET;
    return YesNoBox_Conv();
}

u8_flag_s DayCareAskDepositPokemon(void){
    // LD_A_addr(wPartyCount);
    // CP_A(2);
    // IF_C goto OnlyOneMon;
    if(wram->wPartyCount < 2) {
    // OnlyOneMon:
        // LD_A(DAYCARETEXT_LAST_MON);
        // SCF;
        // RET;
        return u8_flag(DAYCARETEXT_LAST_MON, true);
    }
    // LD_A(DAYCARETEXT_WHICH_ONE);
    // CALL(aPrintDayCareText);
    PrintDayCareText(DAYCARETEXT_WHICH_ONE);
    // LD_B(PARTYMENUACTION_GIVE_MON);
    // FARCALL(aSelectTradeOrDayCareMon);
    // IF_C goto Declined;
    u8_flag_s res = SelectTradeOrDayCareMon_Conv(PARTYMENUACTION_GIVE_MON);
    if(res.flag) {
    // Declined:
        // LD_A(DAYCARETEXT_OH_FINE);
        // SCF;
        // RET;
        return u8_flag(DAYCARETEXT_OH_FINE, true);
    }
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto Egg;
    if(wram->wCurPartySpecies == EGG) {
    // Egg:
        // LD_A(DAYCARETEXT_CANT_BREED_EGG);
        // SCF;
        // RET;
        return u8_flag(DAYCARETEXT_CANT_BREED_EGG, true);
    }
    // FARCALL(aCheckCurPartyMonFainted);
    // IF_C goto OutOfUsableMons;
    if(CheckCurPartyMonFainted_Conv()) {
    // OutOfUsableMons:
        // LD_A(DAYCARETEXT_LAST_ALIVE_MON);
        // SCF;
        // RET;
        return u8_flag(DAYCARETEXT_LAST_ALIVE_MON, true);
    }
    // LD_HL(wPartyMon1Item);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_D_hl;
    // FARCALL(aItemIsMail);
    // IF_C goto HoldingMail;
    if(ItemIsMail_Conv(wram->wPartyMon[res.a].mon.item)) {
    // HoldingMail:
        // LD_A(DAYCARETEXT_REMOVE_MAIL);
        // SCF;
        // RET;
        return u8_flag(DAYCARETEXT_REMOVE_MAIL, true);
    }
    // LD_HL(wPartyMonNicknames);
    // LD_A_addr(wCurPartyMon);
    // CALL(aGetNickname);
    GetNickname_Conv(wram->wPartyMonNickname[0], res.a);
    // AND_A_A;
    // RET;
    return u8_flag(res.a, false);


// DaycareDummyText
//   //  unreferenced
    //text_far(v_DaycareDummyText)
    //text_end
}

void DayCare_DepositPokemonText(void){
    // LD_A(DAYCARETEXT_DEPOSIT);
    // CALL(aPrintDayCareText);
    PrintDayCareText(DAYCARETEXT_DEPOSIT);
    // LD_A_addr(wCurPartySpecies);
    // CALL(aPlayMonCry);
    PlayMonCry_Conv(wram->wCurPartySpecies);
    // LD_A(DAYCARETEXT_COME_BACK_LATER);
    // CALL(aPrintDayCareText);
    PrintDayCareText(DAYCARETEXT_COME_BACK_LATER);
    // RET;
}

u8_flag_s DayCare_AskWithdrawBreedMon(void){
    // LD_A_addr(wStringBuffer2 + 1);
    // AND_A_A;
    // IF_NZ goto grew_at_least_one_level;
    if(wram->wStringBuffer2[1] != 0) {
    // grew_at_least_one_level:
        // LD_A(DAYCARETEXT_GENIUSES);
        // CALL(aPrintDayCareText);
        PrintDayCareText(DAYCARETEXT_GENIUSES);
        // CALL(aYesNoBox);
        // IF_C goto refused;
        if(!YesNoBox_Conv()) {
        // refused:
            // LD_A(DAYCARETEXT_OH_FINE);
            // SCF;
            // RET;
            return u8_flag(DAYCARETEXT_OH_FINE, true);
        }
        // LD_A(DAYCARETEXT_ASK_WITHDRAW);
        // CALL(aPrintDayCareText);
        PrintDayCareText(DAYCARETEXT_ASK_WITHDRAW);
        // CALL(aYesNoBox);
        // IF_C goto refused;
        if(!YesNoBox_Conv()) {
        // refused:
            // LD_A(DAYCARETEXT_OH_FINE);
            // SCF;
            // RET;
            return u8_flag(DAYCARETEXT_OH_FINE, true);
        }
    }
    else {
        // LD_A(DAYCARETEXT_TOO_SOON);
        // CALL(aPrintDayCareText);
        PrintDayCareText(DAYCARETEXT_TOO_SOON);
        // CALL(aYesNoBox);
        // IF_C goto refused;
        // goto check_money;
        if(!YesNoBox_Conv()) {
        // refused:
            // LD_A(DAYCARETEXT_OH_FINE);
            // SCF;
            // RET;
            return u8_flag(DAYCARETEXT_OH_FINE, true);
        }
    }

// check_money:
    // LD_DE(wMoney);
    // LD_BC(wStringBuffer2 + 2);
    // FARCALL(aCompareMoney);
    u8_flag_s res = CompareMoney_Conv(wram->wStringBuffer2 + 2, wram->wMoney);
    // IF_C goto not_enough_money;
    if(res.flag) {
    // not_enough_money:
        // LD_A(DAYCARETEXT_NOT_ENOUGH_MONEY);
        // SCF;
        // RET;
        return u8_flag(DAYCARETEXT_NOT_ENOUGH_MONEY, true);
    }
    // LD_A_addr(wPartyCount);
    // CP_A(PARTY_LENGTH);
    // IF_NC goto party_full;
    if(wram->wPartyCount >= PARTY_LENGTH) {
    // party_full:
        // LD_A(DAYCARETEXT_PARTY_FULL);
        // SCF;
        // RET;
        return u8_flag(DAYCARETEXT_PARTY_FULL, true);
    }
    // AND_A_A;
    // RET;
    return u8_flag(0, false);
}

void DayCare_GetBackMonForMoney(void){
    // LD_BC(wStringBuffer2 + 2);
    // LD_DE(wMoney);
    // FARCALL(aTakeMoney);
    TakeMoney_Conv(wram->wMoney, wram->wStringBuffer2 + 2);
    // LD_A(DAYCARETEXT_WITHDRAW);
    // CALL(aPrintDayCareText);
    PrintDayCareText(DAYCARETEXT_WITHDRAW);
    // LD_A_addr(wCurPartySpecies);
    // CALL(aPlayMonCry);
    PlayMonCry_Conv(wram->wCurPartySpecies);
    // LD_A(DAYCARETEXT_GOT_BACK);
    // CALL(aPrintDayCareText);
    PrintDayCareText(DAYCARETEXT_GOT_BACK);
    // RET;
}

void GetPriceToRetrieveBreedmon(const uint8_t* hl, u8_pair_s lvlGrowth){
    // LD_A_B;
    // LD_addr_A(wStringBuffer2);
    wram->wStringBuffer2[0] = lvlGrowth.a;
    // LD_A_D;
    // LD_addr_A(wStringBuffer2 + 1);
    wram->wStringBuffer2[1] = lvlGrowth.b;
    // LD_DE(wStringBuffer1);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wStringBuffer1, hl, NAME_LENGTH);
    // LD_HL(0);
    // LD_BC(100);
    // LD_A_addr(wStringBuffer2 + 1);
    // CALL(aAddNTimes);
    // LD_DE(100);
    // ADD_HL_DE;
    uint16_t money = 100 + (lvlGrowth.b * 100);
    // XOR_A_A;
    // LD_addr_A(wStringBuffer2 + 2);
    wram->wStringBuffer2[2] = 0;
    // LD_A_H;
    // LD_addr_A(wStringBuffer2 + 3);
    wram->wStringBuffer2[3] = HIGH(money);
    // LD_A_L;
    // LD_addr_A(wStringBuffer2 + 4);
    wram->wStringBuffer2[4] = LOW(money);
    // RET;
}

void PrintDayCareText(uint8_t a){
    static const txt_cmd_s DayCareManIntroText[] = {
        text_far(v_DayCareManIntroText)
        text_end
    };

    static const txt_cmd_s DayCareManIntroEggText[] = {
        text_far(v_DayCareManIntroEggText)
        text_end
    };

    static const txt_cmd_s DayCareLadyIntroText[] = {
        text_far(v_DayCareLadyIntroText)
        text_end
    };

    static const txt_cmd_s DayCareLadyIntroEggText[] = {
        text_far(v_DayCareLadyIntroEggText)
        text_end
    };

    static const txt_cmd_s WhatShouldIRaiseText[] = {
        text_far(v_WhatShouldIRaiseText)
        text_end
    };

    static const txt_cmd_s OnlyOneMonText[] = {
        text_far(v_OnlyOneMonText)
        text_end
    };

    static const txt_cmd_s CantAcceptEggText[] = {
        text_far(v_CantAcceptEggText)
        text_end
    };

    static const txt_cmd_s RemoveMailText[] = {
        text_far(v_RemoveMailText)
        text_end
    };

    static const txt_cmd_s LastHealthyMonText[] = {
        text_far(v_LastHealthyMonText)
        text_end
    };

    static const txt_cmd_s IllRaiseYourMonText[] = {
        text_far(v_IllRaiseYourMonText)
        text_end
    };

    static const txt_cmd_s ComeBackLaterText[] = {
        text_far(v_ComeBackLaterText)
        text_end
    };

    static const txt_cmd_s AreWeGeniusesText[] = {
        text_far(v_AreWeGeniusesText)
        text_end
    };

    static const txt_cmd_s YourMonHasGrownText[] = {
        text_far(v_YourMonHasGrownText)
        text_end
    };

    static const txt_cmd_s PerfectHeresYourMonText[] = {
        text_far(v_PerfectHeresYourMonText)
        text_end
    };

    static const txt_cmd_s GotBackMonText[] = {
        text_far(v_GotBackMonText)
        text_end
    };

    static const txt_cmd_s BackAlreadyText[] = {
        text_far(v_BackAlreadyText)
        text_end
    };

    static const txt_cmd_s HaveNoRoomText[] = {
        text_far(v_HaveNoRoomText)
        text_end
    };

    static const txt_cmd_s NotEnoughMoneyText[] = {
        text_far(v_NotEnoughMoneyText)
        text_end
    };

    static const txt_cmd_s OhFineThenText[] = {
        text_far(v_OhFineThenText)
        text_end
    };

    static const txt_cmd_s ComeAgainText[] = {
        text_far(v_ComeAgainText)
        text_end
    };

    static const txt_cmd_s *TextTable[] = {
    //  entries correspond to DAYCARETEXT_* constants
        [DAYCARETEXT_MAN_INTRO]         = DayCareManIntroText,  // 00
        [DAYCARETEXT_MAN_INTRO_EGG]     = DayCareManIntroEggText,  // 01
        [DAYCARETEXT_LADY_INTRO]        = DayCareLadyIntroText,  // 02
        [DAYCARETEXT_LADY_INTRO_EGG]    = DayCareLadyIntroEggText,  // 03
        [DAYCARETEXT_WHICH_ONE]         = WhatShouldIRaiseText,  // 04
        [DAYCARETEXT_DEPOSIT]           = IllRaiseYourMonText,  // 05
        [DAYCARETEXT_CANT_BREED_EGG]    = CantAcceptEggText,  // 06
        [DAYCARETEXT_LAST_MON]          = OnlyOneMonText,  // 07
        [DAYCARETEXT_LAST_ALIVE_MON]    = LastHealthyMonText,  // 08
        [DAYCARETEXT_COME_BACK_LATER]   = ComeBackLaterText,  // 09
        [DAYCARETEXT_REMOVE_MAIL]       = RemoveMailText,  // 0a
        [DAYCARETEXT_GENIUSES]          = AreWeGeniusesText,  // 0b
        [DAYCARETEXT_ASK_WITHDRAW]      = YourMonHasGrownText,  // 0c
        [DAYCARETEXT_WITHDRAW]          = PerfectHeresYourMonText,  // 0d
        [DAYCARETEXT_GOT_BACK]          = GotBackMonText,  // 0e
        [DAYCARETEXT_TOO_SOON]          = BackAlreadyText,  // 0f
        [DAYCARETEXT_PARTY_FULL]        = HaveNoRoomText,  // 10
        [DAYCARETEXT_NOT_ENOUGH_MONEY]  = NotEnoughMoneyText,  // 11
        [DAYCARETEXT_OH_FINE]           = OhFineThenText,  // 12
        [DAYCARETEXT_COME_AGAIN]        = ComeAgainText,  // 13
    };
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mPrintDayCareText_TextTable);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aPrintText);
    // RET;
    PrintText_Conv2(TextTable[a]);
}

void DayCareManOutside(void){
static const txt_cmd_s NotYetText[] = {
    text_far(v_NotYetText)
    text_end
};

static const txt_cmd_s FoundAnEggText[] = {
    text_far(v_FoundAnEggText)
    text_end
};

static const txt_cmd_s ReceivedEggText[] = {
    text_far(v_ReceivedEggText)
    text_end
};

static const txt_cmd_s TakeGoodCareOfEggText[] = {
    text_far(v_TakeGoodCareOfEggText)
    text_end
};

static const txt_cmd_s IllKeepItThanksText[] = {
    text_far(v_IllKeepItThanksText)
    text_end
};

static const txt_cmd_s NoRoomForEggText[] = {
    text_far(v_NoRoomForEggText)
    text_end
};
    // LD_HL(wDayCareMan);
    // BIT_hl(DAYCAREMAN_HAS_EGG_F);
    // IF_NZ goto AskGiveEgg;
    if(!bit_test(wram->wDayCareMan, DAYCAREMAN_HAS_EGG_F)) {
        // LD_HL(mDayCareManOutside_NotYetText);
        // CALL(aPrintText);
        PrintText_Conv2(NotYetText);
        // RET;
        return;
    }

// AskGiveEgg:
    // LD_HL(mDayCareManOutside_FoundAnEggText);
    // CALL(aPrintText);
    PrintText_Conv2(FoundAnEggText);
    // CALL(aYesNoBox);
    // IF_C goto Declined;
    if(!YesNoBox_Conv()) {
        PrintText_Conv2(IllKeepItThanksText);
        wram->wScriptVar = FALSE;
        return;
    }
    // LD_A_addr(wPartyCount);
    // CP_A(PARTY_LENGTH);
    // IF_NC goto PartyFull;
    if(wram->wPartyCount >= PARTY_LENGTH) {
    // PartyFull:
        // LD_HL(mDayCareManOutside_NoRoomForEggText);
        // CALL(aPrintText);
        PrintText_Conv2(NoRoomForEggText);
        // LD_A(TRUE);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = TRUE;
        // RET;
        return;
    }
    // CALL(aDayCare_GiveEgg);
    DayCare_GiveEgg();
    // LD_HL(wDayCareMan);
    // RES_hl(DAYCAREMAN_HAS_EGG_F);
    bit_reset(wram->wDayCareMan, DAYCAREMAN_HAS_EGG_F);
    // CALL(aDayCare_InitBreeding);
    DayCare_InitBreeding();
    // LD_HL(mDayCareManOutside_ReceivedEggText);
    // CALL(aPrintText);
    PrintText_Conv2(ReceivedEggText);
    // LD_DE(SFX_GET_EGG);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_GET_EGG);
    // LD_C(120);
    // CALL(aDelayFrames);
    DelayFrames(120);
    // LD_HL(mDayCareManOutside_TakeGoodCareOfEggText);
    // goto Load0;

// Declined:
    // LD_HL(mDayCareManOutside_IllKeepItThanksText);

// Load0:
    // CALL(aPrintText);
    PrintText_Conv2(TakeGoodCareOfEggText);
    // XOR_A_A;  // FALSE
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // RET;
}

bool DayCare_GiveEgg(void){
    // LD_A_addr(wEggMonLevel);
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = wram->wEggMon.level;
    // LD_HL(wPartyCount);
    // LD_A_hl;
    // CP_A(PARTY_LENGTH);
    // IF_NC goto PartyFull;
    if(wram->wPartyCount >= PARTY_LENGTH) {
    // PartyFull:
        // SCF;
        // RET;
        return true;
    }
    // INC_A;
    // LD_hl_A;
    uint8_t c = wram->wPartyCount++;

    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A(EGG);
    // LD_hli_A;
    wram->wPartySpecies[c] = EGG;
    // LD_A_addr(wEggMonSpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wEggMon.species;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wEggMon.species;
    // LD_A(-1);
    // LD_hl_A;
    wram->wPartySpecies[c + 1] = (species_t)-1;

    // LD_HL(wPartyMonNicknames);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aDayCare_GetCurrentPartyMember);
    // LD_HL(wEggMonNickname);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPartyMonNickname[c], wram->wEggMonNickname, MON_NAME_LENGTH);

    // LD_HL(wPartyMonOTs);
    // LD_BC(NAME_LENGTH);
    // CALL(aDayCare_GetCurrentPartyMember);
    // LD_HL(wEggMonOT);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPartyMonOT[c], wram->wEggMonOT, MON_NAME_LENGTH);

    // LD_HL(wPartyMon1);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aDayCare_GetCurrentPartyMember);
    // LD_HL(wEggMon);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wPartyMon[c].mon, &wram->wEggMon, BOXMON_STRUCT_LENGTH);

    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wEggMon.species);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_B_H;
    // LD_C_L;
    struct PartyMon* bc = wram->wPartyMon + c;
    // LD_HL(MON_ID + 1);
    // ADD_HL_BC;
    // PUSH_HL;
    // LD_HL(MON_MAXHP);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // PUSH_BC;
    // LD_B(FALSE);
    // PREDEF(pCalcMonStats);
    CalcMonStats_Conv((uint16_t*)(wram_ptr(wPartyMon1Stats) + (c * PARTYMON_STRUCT_LENGTH)), 
        (uint16_t*)(wram_ptr(wPartyMon1StatExp) + (c * PARTYMON_STRUCT_LENGTH)), bc->mon.DVs, FALSE);
    // POP_BC;
    // LD_HL(MON_HP);
    // ADD_HL_BC;
    // XOR_A_A;
    // LD_hli_A;
    // LD_hl_A;
    bc->HP = 0;
    // AND_A_A;
    // RET;
    return false;
}

void DayCare_GetCurrentPartyMember(void){
    LD_A_addr(wPartyCount);
    DEC_A;
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    RET;

}

void DayCare_InitBreeding(void){
    // LD_A_addr(wDayCareLady);
    // BIT_A(DAYCARELADY_HAS_MON_F);
    // RET_Z ;
    // LD_A_addr(wDayCareMan);
    // BIT_A(DAYCAREMAN_HAS_MON_F);
    // RET_Z ;
    if(!bit_test(wram->wDayCareLady, DAYCARELADY_HAS_MON_F) || !bit_test(wram->wDayCareMan, DAYCARELADY_HAS_MON_F))
        return;
    // CALLFAR(aCheckBreedmonCompatibility);
    CheckBreedmonCompatibility_Conv();
    // LD_A_addr(wBreedingCompatibility);
    // AND_A_A;
    // RET_Z ;
    // INC_A;
    // RET_Z ;
    if(wram->wBreedingCompatibility == 0 || wram->wBreedingCompatibility == 0xff)
        return;
    // LD_HL(wDayCareMan);
    // SET_hl(DAYCAREMAN_MONS_COMPATIBLE_F);
    bit_set(wram->wDayCareMan, DAYCAREMAN_MONS_COMPATIBLE_F);

    uint8_t a;
    do {
    // loop:
        // CALL(aRandom);
        a = Random();
        // CP_A(150);
        // IF_C goto loop;
    } while(a < 150);
    // LD_addr_A(wStepsToEgg);
    wram->wStepsToEgg = a;
    // JP(mDayCare_InitBreeding_UselessJump);

// UselessJump:
    // XOR_A_A;
    // LD_HL(wEggMon);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // CALL(aByteFill);
    ByteFill(&wram->wEggMon, BOXMON_STRUCT_LENGTH, 0);
    // LD_HL(wEggMonNickname);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aByteFill);
    ByteFill(wram->wEggMonNickname, MON_NAME_LENGTH, 0);
    // LD_HL(wEggMonOT);
    // LD_BC(NAME_LENGTH);
    // CALL(aByteFill);
    ByteFill(wram->wEggMonOT, NAME_LENGTH, 0);
    // LD_A_addr(wBreedMon1DVs);
    // LD_addr_A(wTempMonDVs);
    wram->wTempMon.mon.DVs = wram->wBreedMon1.DVs;
    // LD_A_addr(wBreedMon1DVs + 1);
    // LD_addr_A(wTempMonDVs + 1);
    // LD_A_addr(wBreedMon1Species);
    // LD_addr_A(wCurPartySpecies);
    wram->wTempMon.mon.species = wram->wBreedMon1.species;
    // LD_A(0x3);
    // LD_addr_A(wMonType);
    wram->wMonType = 0x3;
    // LD_A_addr(wBreedMon1Species);
    // CP_A(DITTO);
    // LD_A(0x1);
    // IF_Z goto LoadWhichBreedmonIsTheMother;
    // LD_A_addr(wBreedMon2Species);
    // CP_A(DITTO);
    // LD_A(0x0);
    // IF_Z goto LoadWhichBreedmonIsTheMother;
    // FARCALL(aGetGender);
    // LD_A(0x0);
    // IF_Z goto LoadWhichBreedmonIsTheMother;
    // INC_A;

// LoadWhichBreedmonIsTheMother:
    // LD_addr_A(wBreedMotherOrNonDitto);
    wram->wBreedMotherOrNonDitto = (wram->wBreedMon1.species == DITTO || (wram->wBreedMon2.species != DITTO && GetGender_Conv(TEMPMON).a != 0))? 0x1: 0x0;
    // AND_A_A;
    // LD_A_addr(wBreedMon1Species);
    // IF_Z goto GotMother;
    // LD_A_addr(wBreedMon2Species);

// GotMother:
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = (wram->wBreedMotherOrNonDitto)? wram->wBreedMon2.species: wram->wBreedMon1.species;
    // CALLFAR(aGetPreEvolution);
    // CALLFAR(aGetPreEvolution);
    wram->wCurPartySpecies = GetPreEvolution_Conv(GetPreEvolution_Conv(wram->wCurPartySpecies));
    // LD_A(EGG_LEVEL);
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = EGG_LEVEL;

//  Nidoran♀ can give birth to either gender of Nidoran
    // LD_A_addr(wCurPartySpecies);
    // CP_A(NIDORAN_F);
    // IF_NZ goto GotEggSpecies;
    if(wram->wCurPartySpecies == NIDORAN_F) {
        // CALL(aRandom);
        // CP_A(50 percent + 1);
        // LD_A(NIDORAN_F);
        // IF_C goto GotEggSpecies;
        // LD_A(NIDORAN_M);
        wram->wCurPartySpecies = (Random() >= 50 percent + 1)? NIDORAN_M: NIDORAN_F;
    }

// GotEggSpecies:
    // LD_addr_A(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies;
    // LD_addr_A(wEggMonSpecies);
    wram->wEggMon.species = wram->wCurPartySpecies;

    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wEggMon.species);
    // LD_HL(wEggMonNickname);
    // LD_DE(mDayCare_InitBreeding_String_EGG);
    // CALL(aCopyName2);
    CopyName2(wram->wEggMonNickname, U82C("EGG@"));
    // LD_HL(wPlayerName);
    // LD_DE(wEggMonOT);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wEggMonOT, wram->wPlayerName, NAME_LENGTH);
    // XOR_A_A;
    // LD_addr_A(wEggMonItem);
    wram->wEggMon.item = NO_ITEM;
    // LD_DE(wEggMonMoves);
    // XOR_A_A;  // FALSE
    // LD_addr_A(wSkipMovesBeforeLevelUp);
    wram->wSkipMovesBeforeLevelUp = FALSE;
    // PREDEF(pFillMoves);
    FillMoves_Conv(wram->wEggMon.moves, wram->wEggMon.PP, wram->wEggMon.species, wram->wEggMon.level);
    // FARCALL(aInitEggMoves);
    InitEggMoves_Conv();
    // LD_HL(wEggMonID);
    // LD_A_addr(wPlayerID);
    // LD_hli_A;
    // LD_A_addr(wPlayerID + 1);
    // LD_hl_A;
    wram->wEggMon.id = wram->wPlayerID;
    // LD_A_addr(wCurPartyLevel);
    // LD_D_A;
    // CALLFAR(aCalcExpAtLevel);
    uint32_t exp = CalcExpAtLevel_Conv(wram->wCurPartyLevel);
    // LD_HL(wEggMonExp);
    // LDH_A_addr(hMultiplicand);
    // LD_hli_A;
    wram->wEggMon.exp[0] = exp & 0xff;
    // LDH_A_addr(hMultiplicand + 1);
    // LD_hli_A;
    wram->wEggMon.exp[1] = (exp >> 8) & 0xff;
    // LDH_A_addr(hMultiplicand + 2);
    // LD_hl_A;
    wram->wEggMon.exp[2] = (exp >> 16) & 0xff;
    // XOR_A_A;
    // LD_B(wEggMonDVs - wEggMonStatExp);
    // LD_HL(wEggMonStatExp);

// loop2:
    // LD_hli_A;
    // DEC_B;
    // IF_NZ goto loop2;
    ByteFill(wram->wEggMon.statExp, sizeof(wram->wEggMon.statExp), 0);
    // LD_HL(wEggMonDVs);
    // CALL(aRandom);
    uint16_t dv = (Random() | (Random() << 8));
    // LD_hli_A;
    wram->wEggMon.DVs = dv;
    // LD_addr_A(wTempMonDVs);
    wram->wTempMon.mon.DVs = dv;
    // CALL(aRandom);
    // LD_hld_A;
    // LD_addr_A(wTempMonDVs + 1);
    uint16_t dvs;
    // LD_DE(wBreedMon1DVs);
    // LD_A_addr(wBreedMon1Species);
    // CP_A(DITTO);
    // IF_Z goto GotDVs;
    // LD_DE(wBreedMon2DVs);
    // LD_A_addr(wBreedMon2Species);
    // CP_A(DITTO);
    // IF_Z goto GotDVs;
    if(wram->wBreedMon1.species == DITTO) {
        dvs = wram->wBreedMon1.species;
    }
    else if(wram->wBreedMon2.species == DITTO) {
        dvs = wram->wBreedMon2.species;
    }
    else {
        // LD_A(TEMPMON);
        // LD_addr_A(wMonType);
        wram->wMonType = TEMPMON;
        // PUSH_HL;
        // FARCALL(aGetGender);
        u8_flag_s gender = GetGender_Conv(TEMPMON);
        // POP_HL;
        // LD_DE(wBreedMon1DVs);
        // LD_BC(wBreedMon2DVs);
        // IF_C goto SkipDVs;
        if(gender.flag) 
            goto SkipDVs;
        // IF_Z goto ParentCheck2;
        if(gender.a != 0) {
            // LD_A_addr(wBreedMotherOrNonDitto);
            // AND_A_A;
            // IF_Z goto GotDVs;
            // LD_D_B;
            // LD_E_C;
            dvs = (wram->wBreedMotherOrNonDitto)? wram->wBreedMon2.DVs: wram->wBreedMon1.DVs;
            // goto GotDVs;
        }
        else {
        // ParentCheck2:
            // LD_A_addr(wBreedMotherOrNonDitto);
            // AND_A_A;
            // IF_NZ goto GotDVs;
            // LD_D_B;
            // LD_E_C;
            dvs = (wram->wBreedMotherOrNonDitto)? wram->wBreedMon1.DVs: wram->wBreedMon2.DVs;
        }
    }

// GotDVs:
    // LD_A_de;
    // INC_DE;
    // AND_A(0xf);
    // LD_B_A;
    // LD_A_hl;
    // AND_A(0xf0);
    // ADD_A_B;
    // LD_hli_A;
    uint8_t dv1 = (dv & 0xf0) + (dvs & 0xf);
    // LD_A_de;
    // AND_A(0x7);
    // LD_B_A;
    // LD_A_hl;
    // AND_A(0xf8);
    // ADD_A_B;
    uint8_t dv2 = ((dv >> 8) & 0xf8) + ((dvs >> 8) & 0x7);
    // LD_hl_A;
    wram->wEggMon.DVs = (dv2 << 8) + dv1;

SkipDVs:
    // LD_HL(wStringBuffer1);
    // LD_DE(wMonOrItemNameBuffer);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wMonOrItemNameBuffer, wram->wStringBuffer1, NAME_LENGTH);
    // LD_HL(wEggMonMoves);
    // LD_DE(wEggMonPP);
    // PREDEF(pFillPP);
    FillPP_Conv(wram->wEggMon.PP, wram->wEggMon.moves);
    // LD_HL(wMonOrItemNameBuffer);
    // LD_DE(wStringBuffer1);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wStringBuffer1, wram->wMonOrItemNameBuffer, NAME_LENGTH);
    // LD_A_addr(wBaseEggSteps);
    // LD_HL(wEggMonHappiness);
    // LD_hli_A;
    wram->wEggMon.happiness = wram->wBaseEggSteps;
    // XOR_A_A;
    // LD_hli_A;
    wram->wEggMon.pokerusStatus = 0;
    // LD_hli_A;
    wram->wEggMon.caughtData[0] = 0;
    // LD_hl_A;
    wram->wEggMon.caughtData[1] = 0;
    // LD_A_addr(wCurPartyLevel);
    // LD_addr_A(wEggMonLevel);
    wram->wEggMon.level = wram->wCurPartyLevel;
    // RET;

// String_EGG:
    //db [''];
}
