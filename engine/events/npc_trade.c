#include "../../constants.h"
#include "npc_trade.h"
#include "poke_seer.h"
#include "../smallflag.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/audio.h"
#include "../../home/sprite_updates.h"
#include "../../home/map.h"
#include "../../home/names.h"
#include "../pokemon/party_menu.h"
#include "../pokemon/mon_stats.h"
#include "../pokemon/move_mon.h"
#include "../pokemon/caught_data.h"
#include "../movie/trade_animation.h"
#include "../../data/events/npc_trades.h"
#include "../../data/text/common.h"

static void NPCTrade_TradeAnimation(void);

void NPCTrade(uint8_t e){
    // LD_A_E;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = e;
    // CALL(aTrade_GetDialog);
    Trade_GetDialog();
    // LD_B(CHECK_FLAG);
    // CALL(aTradeFlagAction);
    // LD_A(TRADE_DIALOG_AFTER);
    // IF_NZ goto done;
    if(TradeFlagAction(CHECK_FLAG) != 0) {
        return PrintTradeText(TRADE_DIALOG_AFTER);
    }

    // LD_A(TRADE_DIALOG_INTRO);
    // CALL(aPrintTradeText);
    PrintTradeText(TRADE_DIALOG_INTRO);

    // CALL(aYesNoBox);
    // LD_A(TRADE_DIALOG_CANCEL);
    // IF_C goto done;
    if(!YesNoBox()) {
        return PrintTradeText(TRADE_DIALOG_CANCEL);
    }

//  Select givemon from party
    // LD_B(PARTYMENUACTION_GIVE_MON);
    // FARCALL(aSelectTradeOrDayCareMon);
    u8_flag_s sel_res = SelectTradeOrDayCareMon(PARTYMENUACTION_GIVE_MON);
    // LD_A(TRADE_DIALOG_CANCEL);
    // IF_C goto done;
    if(sel_res.flag) {
        return PrintTradeText(TRADE_DIALOG_CANCEL);
    }

    // LD_E(NPCTRADE_GIVEMON);
    // CALL(aGetTradeAttr);
    // LD_A_addr(wCurPartySpecies);
    // CP_A_hl;
    // LD_A(TRADE_DIALOG_WRONG);
    // IF_NZ goto done;
    if(GetTradeAttr()->requestedMon != wram->wCurPartySpecies) {
        return PrintTradeText(TRADE_DIALOG_WRONG);
    }

    // CALL(aCheckTradeGender);
    // LD_A(TRADE_DIALOG_WRONG);
    // IF_C goto done;
    if(!CheckTradeGender()) {
        return PrintTradeText(TRADE_DIALOG_WRONG);
    }

    // LD_B(SET_FLAG);
    // CALL(aTradeFlagAction);
    TradeFlagAction(SET_FLAG);

    // LD_HL(mNPCTradeCableText);
    // CALL(aPrintText);
    PrintText(NPCTradeCableText);

    // CALL(aDoNPCTrade);
    DoNPCTrade();
    // CALL(aNPCTrade_TradeAnimation);
    NPCTrade_TradeAnimation();
    // CALL(aGetTradeMonNames);
    GetTradeMonNames();

    // LD_HL(mTradedForText);
    // CALL(aPrintText);
    PrintText(TradedForText);

    // CALL(aRestartMapMusic);
    RestartMapMusic();

    // LD_A(TRADE_DIALOG_COMPLETE);


// done:
    // CALL(aPrintTradeText);
    PrintTradeText(TRADE_DIALOG_COMPLETE);
    // RET;
    return;
}

static void NPCTrade_TradeAnimation(void){
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates();
    // LD_A_addr(wJumptableIndex);
    // PUSH_AF;
    uint8_t jumptableIndex = wram->wJumptableIndex;
// wTradeDialog aliases wFrameCounter, which TradeAnimation uses
    // LD_A_addr(wTradeDialog);
    // PUSH_AF;
    uint8_t tradeDialog = wram->wTradeDialog;
    // PREDEF(pTradeAnimation);
    TradeAnimation();
    // POP_AF;
    // LD_addr_A(wTradeDialog);
    wram->wTradeDialog = tradeDialog;
    // POP_AF;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = jumptableIndex;
    // CALL(aReturnToMapWithSpeechTextbox);
    ReturnToMapWithSpeechTextbox();
    // RET;
}

bool CheckTradeGender(void){
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = 0;

    // LD_E(NPCTRADE_GENDER);
    // CALL(aGetTradeAttr);
    uint8_t gender = GetTradeAttr()->genderRequested;
    // LD_A_hl;
    // AND_A_A;  // TRADE_GENDER_EITHER
    // IF_Z goto matching;
    if(gender == TRADE_GENDER_EITHER)
        return true;
    // CP_A(TRADE_GENDER_MALE);
    // IF_Z goto check_male;
    u8_flag_s res = GetGender(0);
    if(gender == TRADE_GENDER_MALE) {
    // check_male:
        // FARCALL(aGetGender);
        // IF_Z goto not_matching;
        return (res.a != 0);
    }
    else {
    // TRADE_GENDER_FEMALE
        // FARCALL(aGetGender);
        // IF_NZ goto not_matching;
        // goto matching;
        return (res.a == 0);
    }


// matching:
    // AND_A_A;
    // RET;


// not_matching:
    // SCF;
    // RET;
}

uint8_t TradeFlagAction(uint8_t b){
    // LD_HL(wTradeFlags);
    // LD_A_addr(wJumptableIndex);
    // LD_C_A;
    // PREDEF(pSmallFarFlagAction);
    uint8_t c = SmallFarFlagAction(gPlayer.tradeFlags, wram->wJumptableIndex, b);
    // LD_A_C;
    // AND_A_A;
    // RET;
    return c;
}

void Trade_GetDialog(void){
    // LD_E(NPCTRADE_DIALOG);
    // CALL(aGetTradeAttr);
    // LD_A_hl;
    // LD_addr_A(wTradeDialog);
    wram->wTradeDialog = GetTradeAttr()->dialogSet;
    // RET;
}

void DoNPCTrade(void){
    // LD_E(NPCTRADE_GIVEMON);
    // CALL(aGetTradeAttr);
    // LD_A_hl;
    // LD_addr_A(wPlayerTrademonSpecies);
    wram->wPlayerTrademon.species = GetTradeAttr()->requestedMon;

    // LD_E(NPCTRADE_GETMON);
    // CALL(aGetTradeAttr);
    // LD_A_hl;
    // LD_addr_A(wOTTrademonSpecies);
    wram->wOTTrademon.species = GetTradeAttr()->offeredMon;

    // LD_A_addr(wPlayerTrademonSpecies);
    // LD_DE(wPlayerTrademonSpeciesName);
    // CALL(aGetTradeMonName);
    // CALL(aCopyTradeName);
    CopyTradeName(wram->wPlayerTrademon.speciesName, GetTradeMonName(wram->wPlayerTrademon.species));

    // LD_A_addr(wOTTrademonSpecies);
    // LD_DE(wOTTrademonSpeciesName);
    // CALL(aGetTradeMonName);
    // CALL(aCopyTradeName);
    CopyTradeName(wram->wOTTrademon.speciesName, GetTradeMonName(wram->wOTTrademon.species));

    // LD_HL(wPartyMonOTs);
    // LD_BC(NAME_LENGTH);
    // CALL(aTrade_GetAttributeOfCurrentPartymon);
    // LD_DE(wPlayerTrademonOTName);
    // CALL(aCopyTradeName);
    CopyTradeName(wram->wPlayerTrademon.otName, gPokemon.partyMonOT[wram->wCurPartyMon]);

    // LD_HL(wPlayerName);
    // LD_DE(wPlayerTrademonSenderName);
    // CALL(aCopyTradeName);
    CopyTradeName(wram->wPlayerTrademon.senderName, gPlayer.playerName);

    // LD_HL(wPartyMon1ID);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aTrade_GetAttributeOfCurrentPartymon);
    // LD_DE(wPlayerTrademonID);
    // CALL(aTrade_CopyTwoBytes);
    wram->wPlayerTrademon.id = gPokemon.partyMon[wram->wCurPartyMon].mon.id;

    // LD_HL(wPartyMon1DVs);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aTrade_GetAttributeOfCurrentPartymon);
    // LD_DE(wPlayerTrademonDVs);
    // CALL(aTrade_CopyTwoBytes);
    wram->wPlayerTrademon.dvs = gPokemon.partyMon[wram->wCurPartyMon].mon.DVs;

    // LD_HL(wPartyMon1Species);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aTrade_GetAttributeOfCurrentPartymon);
    // LD_B_H;
    // LD_C_L;
    // FARCALL(aGetCaughtGender);
    // LD_A_C;
    // LD_addr_A(wPlayerTrademonCaughtData);
    wram->wPlayerTrademon.caughtData = GetCaughtGender(&gPokemon.partyMon[wram->wCurPartyMon].mon);

    // LD_E(NPCTRADE_DIALOG);
    // CALL(aGetTradeAttr);
    // LD_A_hl;
    uint8_t dialogSet = GetTradeAttr()->dialogSet;
    // CP_A(TRADE_DIALOGSET_GIRL);
    // LD_A(CAUGHT_BY_GIRL);
    // IF_C goto okay;
    if(dialogSet < TRADE_DIALOGSET_GIRL)
        wram->wOTTrademon.caughtData = CAUGHT_BY_GIRL;
    // LD_A(CAUGHT_BY_BOY);

// okay:
    // LD_addr_A(wOTTrademonCaughtData);
    wram->wOTTrademon.caughtData = CAUGHT_BY_BOY;

    // LD_HL(wPartyMon1Level);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aTrade_GetAttributeOfCurrentPartymon);
    // LD_A_hl;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = gPokemon.partyMon[wram->wCurPartyMon].mon.level;
    // LD_A_addr(wOTTrademonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wOTTrademon.species;
    // XOR_A_A;
    // LD_addr_A(wMonType);  // PARTYMON
    wram->wMonType = PARTYMON;
    // LD_addr_A(wPokemonWithdrawDepositParameter);  // REMOVE_PARTY
    // CALLFAR(aRemoveMonFromPartyOrBox);
    RemoveMonFromPartyOrBox(REMOVE_PARTY);
    // PREDEF(pTryAddMonToParty);
    TryAddMonToParty(wram->wOTTrademon.species, wram->wCurPartyLevel);

    // LD_E(NPCTRADE_DIALOG);
    // CALL(aGetTradeAttr);
    // LD_A_hl;
    // CP_A(TRADE_DIALOGSET_GIRL);
    // LD_B(CAUGHT_BY_UNKNOWN);
    // IF_C goto incomplete;
    if(dialogSet < TRADE_DIALOGSET_GIRL)
        SetGiftPartyMonCaughtData(CAUGHT_BY_UNKNOWN);
    // LD_B(CAUGHT_BY_GIRL);
    else
        SetGiftPartyMonCaughtData(CAUGHT_BY_GIRL);
    // incomplete:
        // FARCALL(aSetGiftPartyMonCaughtData);

    // LD_E(NPCTRADE_NICKNAME);
    // CALL(aGetTradeAttr);
    // LD_DE(wOTTrademonNickname);
    // CALL(aCopyTradeName);
    CopyTradeName(wram->wOTTrademon.nickname, U82C(GetTradeAttr()->nickname));

    // LD_HL(wPartyMonNicknames);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aTrade_GetAttributeOfLastPartymon);
    // LD_HL(wOTTrademonNickname);
    // CALL(aCopyTradeName);
    CopyTradeName(gPokemon.partyMonNickname[gPokemon.partyCount - 1], wram->wOTTrademon.nickname);

    uint8_t* tempName = U82C(GetTradeAttr()->OTName);
    // LD_E(NPCTRADE_OT_NAME);
    // CALL(aGetTradeAttr);
    // PUSH_HL;
    // LD_DE(wOTTrademonOTName);
    // CALL(aCopyTradeName);
    CopyTradeName(wram->wOTTrademon.otName, tempName);
    // POP_HL;
    // LD_DE(wOTTrademonSenderName);
    // CALL(aCopyTradeName);
    CopyTradeName(wram->wOTTrademon.senderName, tempName);

    // LD_HL(wPartyMonOTs);
    // LD_BC(NAME_LENGTH);
    // CALL(aTrade_GetAttributeOfLastPartymon);
    // LD_HL(wOTTrademonOTName);
    // CALL(aCopyTradeName);
    CopyTradeName(gPokemon.partyMonOT[gPokemon.partyCount - 1], wram->wOTTrademon.otName);

    // LD_E(NPCTRADE_DVS);
    // CALL(aGetTradeAttr);
    // LD_DE(wOTTrademonDVs);
    // CALL(aTrade_CopyTwoBytes);
    CopyBytes(&wram->wOTTrademon.dvs, GetTradeAttr()->dvs, 2);

    // LD_HL(wPartyMon1DVs);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aTrade_GetAttributeOfLastPartymon);
    // LD_HL(wOTTrademonDVs);
    // CALL(aTrade_CopyTwoBytes);
    CopyBytes(&gPokemon.partyMon[gPokemon.partyCount - 1].mon.DVs, &wram->wOTTrademon.dvs, 2);

    // LD_E(NPCTRADE_OT_ID);
    // CALL(aGetTradeAttr);
    // LD_DE(wOTTrademonID + 1);
    // CALL(aTrade_CopyTwoBytesReverseEndian);
    wram->wOTTrademon.id = NativeToBigEndian16(GetTradeAttr()->OTID);

    // LD_HL(wPartyMon1ID);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aTrade_GetAttributeOfLastPartymon);
    // LD_HL(wOTTrademonID);
    // CALL(aTrade_CopyTwoBytes);
    gPokemon.partyMon[gPokemon.partyCount - 1].mon.id = wram->wOTTrademon.id;

    // LD_E(NPCTRADE_ITEM);
    // CALL(aGetTradeAttr);
    // PUSH_HL;
    // LD_HL(wPartyMon1Item);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aTrade_GetAttributeOfLastPartymon);
    // POP_HL;
    // LD_A_hl;
    // LD_de_A;
    gPokemon.partyMon[gPokemon.partyCount - 1].mon.item = GetTradeAttr()->item;

    // PUSH_AF;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;
    // LD_A_addr(wCurPartyMon);
    // PUSH_AF;
    uint8_t curPartyMon = wram->wCurPartyMon;
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_addr_A(wCurPartyMon);
    // FARCALL(aComputeNPCTrademonStats);
    ComputeNPCTrademonStats(gPokemon.partyCount - 1);
    // POP_AF;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = curPartyMon;
    // POP_HL;
    // POP_DE;
    // POP_BC;
    // POP_AF;
    // RET;
}

const struct NPCTrade* GetTradeAttr(void){
    // LD_D(0);
    // PUSH_DE;
    // LD_A_addr(wJumptableIndex);
    // AND_A(0xf);
    // SWAP_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mNPCTrades);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // POP_DE;
    // ADD_HL_DE;
    // RET;
    return NPCTrades + (wram->wJumptableIndex & 0xf);
}

void Trade_GetAttributeOfCurrentPartymon(void){
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    RET;

}

void Trade_GetAttributeOfLastPartymon(void){
    LD_A_addr(wPartyCount);
    DEC_A;
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    RET;

}

uint8_t* GetTradeMonName(species_t a){
    // PUSH_DE;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetBasePokemonName);
    GetBasePokemonName(a);
    // LD_HL(wStringBuffer1);
    // POP_DE;
    // RET;
    return wram->wStringBuffer1;
}

void CopyTradeName(uint8_t* de, const uint8_t* hl){
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    // RET;
    CopyBytes(de, hl, NAME_LENGTH);
}

void Trade_CopyFourCharString(void){
//  //  unreferenced
    LD_BC(4);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    RET;

}

void Trade_CopyThreeCharString(void){
//  //  unreferenced
    LD_BC(3);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    RET;

}

void Trade_CopyTwoBytes(void){
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    RET;

}

void Trade_CopyTwoBytesReverseEndian(void){
    LD_A_hli;
    LD_de_A;
    DEC_DE;
    LD_A_hl;
    LD_de_A;
    RET;

}

void GetTradeMonNames(void){
    // LD_E(NPCTRADE_GETMON);
    // CALL(aGetTradeAttr);
    // LD_A_hl;
    // CALL(aGetTradeMonName);

    // LD_DE(wStringBuffer2);
    // CALL(aCopyTradeName);
    CopyTradeName(wram->wStringBuffer2, GetTradeMonName(GetTradeAttr()->offeredMon));

    // LD_E(NPCTRADE_GIVEMON);
    // CALL(aGetTradeAttr);
    // LD_A_hl;
    // CALL(aGetTradeMonName);

    // LD_DE(wMonOrItemNameBuffer);
    // CALL(aCopyTradeName);
    CopyTradeName(wram->wMonOrItemNameBuffer, GetTradeMonName(GetTradeAttr()->requestedMon));

    // LD_HL(wStringBuffer1);
    uint8_t* hl = wram->wStringBuffer1;

    while(*(hl++) != 0x50) {
    // loop:
        // LD_A_hli;
        // CP_A(0x50);
        // IF_NZ goto loop;
    }

    // DEC_HL;
    // PUSH_HL;
    uint8_t* hl2 = --hl;
    // LD_E(NPCTRADE_GENDER);
    // CALL(aGetTradeAttr);
    // LD_A_hl;
    uint8_t gender = GetTradeAttr()->genderRequested;
    // POP_HL;
    // AND_A_A;  // TRADE_GENDER_EITHER
    // RET_Z ;
    if(gender == TRADE_GENDER_EITHER)
        return;
    // CP_A(TRADE_GENDER_MALE);
    // LD_A(0xef);
    // IF_Z goto done;
    if(gender == TRADE_GENDER_MALE)
        *(hl2++) = 0xef;
// TRADE_GENDER_FEMALE
    else
        *(hl2++) = 0xf5;
    // LD_A(0xf5);

// done:
    // LD_hli_A;
    // LD_hl(0x50);
    *hl2 = 0x50;
    // RET;

// INCLUDE "data/events/npc_trades.asm"
}

void PrintTradeText(uint8_t a){
    // PUSH_AF;
    // CALL(aGetTradeMonNames);
    GetTradeMonNames();
    // POP_AF;
    // LD_BC(2 * 4);
    // LD_HL(mTradeTexts);
    // CALL(aAddNTimes);
    // LD_A_addr(wTradeDialog);
    // LD_C_A;
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aPrintText);
    PrintText(TradeTexts[a*4 + wram->wTradeDialog]);
    // RET;
}

const txt_cmd_s* const TradeTexts[] = {
//  entries correspond to TRADE_DIALOG_* × TRADE_DIALOGSET_* constants
//  TRADE_DIALOG_INTRO
    NPCTradeIntroText1,
    NPCTradeIntroText2,
    NPCTradeIntroText2,
    NPCTradeIntroText3,
//  TRADE_DIALOG_CANCEL
    NPCTradeCancelText1,
    NPCTradeCancelText2,
    NPCTradeCancelText2,
    NPCTradeCancelText3,
//  TRADE_DIALOG_WRONG
    NPCTradeWrongText1,
    NPCTradeWrongText2,
    NPCTradeWrongText2,
    NPCTradeWrongText3,
//  TRADE_DIALOG_COMPLETE
    NPCTradeCompleteText1,
    NPCTradeCompleteText2,
    NPCTradeCompleteText4,
    NPCTradeCompleteText3,
//  TRADE_DIALOG_AFTER
    NPCTradeAfterText1,
    NPCTradeAfterText2,
    NPCTradeAfterText4,
    NPCTradeAfterText3,
};

const txt_cmd_s NPCTradeCableText[] = {
    text_far(v_NPCTradeCableText)
    text_end
};

static void TradedForText_Function(struct TextCmdState* hl) {
    static const txt_cmd_s done[] = {
        text_far(v_NPCTradeFanfareText)
        text_end
    };
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_NONE);
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_HL(mTradedForText_done);
    hl->hl = done;
    // RET;
}

const txt_cmd_s TradedForText[] = {
// traded givemon for getmon
    text_far(v_Text_NPCTraded)
    text_asm(TradedForText_Function)
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    // CALL(aDelayFrame);
    // LD_HL(mTradedForText_done);
    // RET;
};

const txt_cmd_s NPCTradeIntroText1[] = {
    text_far(v_NPCTradeIntroText1)
    text_end
};

const txt_cmd_s NPCTradeCancelText1[] = {
    text_far(v_NPCTradeCancelText1)
    text_end
};

const txt_cmd_s NPCTradeWrongText1[] = {
    text_far(v_NPCTradeWrongText1)
    text_end
};

const txt_cmd_s NPCTradeCompleteText1[] = {
    text_far(v_NPCTradeCompleteText1)
    text_end
};

const txt_cmd_s NPCTradeAfterText1[] = {
    text_far(v_NPCTradeAfterText1)
    text_end
};

const txt_cmd_s NPCTradeIntroText2[] = {
    text_far(v_NPCTradeIntroText2)
    text_end
};

const txt_cmd_s NPCTradeCancelText2[] = {
    text_far(v_NPCTradeCancelText2)
    text_end
};

const txt_cmd_s NPCTradeWrongText2[] = {
    text_far(v_NPCTradeWrongText2)
    text_end
};

const txt_cmd_s NPCTradeCompleteText2[] = {
    text_far(v_NPCTradeCompleteText2)
    text_end
};

const txt_cmd_s NPCTradeAfterText2[] = {
    text_far(v_NPCTradeAfterText2)
    text_end
};

const txt_cmd_s NPCTradeIntroText3[] = {
    text_far(v_NPCTradeIntroText3)
    text_end
};

const txt_cmd_s NPCTradeCancelText3[] = {
    text_far(v_NPCTradeCancelText3)
    text_end
};

const txt_cmd_s NPCTradeWrongText3[] = {
    text_far(v_NPCTradeWrongText3)
    text_end
};

const txt_cmd_s NPCTradeCompleteText3[] = {
    text_far(v_NPCTradeCompleteText3)
    text_end
};

const txt_cmd_s NPCTradeAfterText3[] = {
    text_far(v_NPCTradeAfterText3)
    text_end
};

const txt_cmd_s NPCTradeCompleteText4[] = {
    text_far(v_NPCTradeCompleteText4)
    text_end
};

const txt_cmd_s NPCTradeAfterText4[] = {
    text_far(v_NPCTradeAfterText4)
    text_end
};
