#include "../../constants.h"
#include "name_rater.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../menus/naming_screen.h"
#include "../pokemon/party_menu.h"
#include "../../data/text/common.h"

static const txt_cmd_s NameRaterHelloText[] = {
    text_far(v_NameRaterHelloText)
    text_end
};

static const txt_cmd_s NameRaterWhichMonText[] = {
    text_far(v_NameRaterWhichMonText)
    text_end
};

static const txt_cmd_s NameRaterBetterNameText[] = {
    text_far(v_NameRaterBetterNameText)
    text_end
};

static const txt_cmd_s NameRaterWhatNameText[] = {
    text_far(v_NameRaterWhatNameText)
    text_end
};

static const txt_cmd_s NameRaterFinishedText[] = {
    text_far(v_NameRaterFinishedText)
    text_end
};

static const txt_cmd_s NameRaterComeAgainText[] = {
    text_far(v_NameRaterComeAgainText)
    text_end
};

static const txt_cmd_s NameRaterPerfectNameText[] = {
    text_far(v_NameRaterPerfectNameText)
    text_end
};

static const txt_cmd_s NameRaterEggText[] = {
    text_far(v_NameRaterEggText)
    text_end
};

static const txt_cmd_s NameRaterSameNameText[] = {
    text_far(v_NameRaterSameNameText)
    text_end
};

static const txt_cmd_s NameRaterNamedText[] = {
    text_far(v_NameRaterNamedText)
    text_end
};

void v_NameRater(void){
//  Introduce himself
    // LD_HL(mNameRaterHelloText);
    // CALL(aPrintText);
    PrintText_Conv2(NameRaterHelloText);
    // CALL(aYesNoBox);
    // JP_C (mv_NameRater_cancel);
    if(!YesNoBox_Conv())
        return PrintText_Conv2(NameRaterComeAgainText);
//  Select a Pokemon from your party
    // LD_HL(mNameRaterWhichMonText);
    // CALL(aPrintText);
    PrintText_Conv2(NameRaterWhichMonText);
    // FARCALL(aSelectMonFromParty);
    u8_flag_s res = SelectMonFromParty();
    // IF_C goto cancel;
    if(res.flag)
        return PrintText_Conv2(NameRaterComeAgainText);
//  He can't rename an egg...
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto egg;
    if(wram->wCurPartySpecies == EGG) {
        return PrintText_Conv2(NameRaterEggText);
    }
//  ... or a Pokemon you got from a trade.
    // CALL(aGetCurNickname);
    GetCurNickname_Conv();
    // CALL(aCheckIfMonIsYourOT);
    // IF_C goto traded;
    if(!CheckIfMonIsYourOT_Conv(wram->wCurPartyMon))
        return PrintText_Conv2(NameRaterPerfectNameText);
//  This name is good, but we can do better.  How about it?
    // LD_HL(mNameRaterBetterNameText);
    // CALL(aPrintText);
    PrintText_Conv2(NameRaterBetterNameText);
    // CALL(aYesNoBox);
    // IF_C goto cancel;
    if(!YesNoBox_Conv())
        return PrintText_Conv2(NameRaterComeAgainText);
//  What name shall I give it then?
    // LD_HL(mNameRaterWhatNameText);
    // CALL(aPrintText);
    PrintText_Conv2(NameRaterWhatNameText);
//  Load the new nickname into wStringBuffer2
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wNamedObjectIndex);
    // LD_addr_A(wCurSpecies);
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wCurPartySpecies);
    // LD_B(NAME_MON);
    // LD_DE(wStringBuffer2);
    // FARCALL(av_NamingScreen);
    v_NamingScreen_Conv(wram->wStringBuffer2, NAME_MON);
//  If the new name is empty, treat it as unchanged.
    // CALL(aIsNewNameEmpty);
    // LD_HL(mNameRaterSameNameText);
    // IF_C goto samename;
//  If the new name is the same as the old name, treat it as unchanged.
    // CALL(aCompareNewToOld);
    // LD_HL(mNameRaterSameNameText);
    // IF_C goto samename;
    const txt_cmd_s* txt = NameRaterSameNameText;
    if(!IsNewNameEmpty_Conv() && !CompareNewToOld_Conv(wram->wCurPartyMon)) {
    //  Copy the new name from wStringBuffer2
        // LD_HL(wPartyMonNicknames);
        // LD_BC(MON_NAME_LENGTH);
        // LD_A_addr(wCurPartyMon);
        // CALL(aAddNTimes);
        // LD_E_L;
        // LD_D_H;
        // LD_HL(wStringBuffer2);
        // LD_BC(MON_NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(wram->wPartyMonNickname[wram->wCurPartyMon], wram->wStringBuffer2, MON_NAME_LENGTH);
        // LD_HL(mNameRaterFinishedText);
        txt = NameRaterFinishedText;
    }

// samename:
    // PUSH_HL;
    // CALL(aGetCurNickname);
    GetCurNickname_Conv();
    // LD_HL(mNameRaterNamedText);
    // CALL(aPrintText);
    PrintText_Conv2(NameRaterNamedText);
    // POP_HL;
    // goto done;
    return PrintText_Conv2(txt);

// traded:
    // LD_HL(mNameRaterPerfectNameText);
    // goto done;


// cancel:
    // LD_HL(mNameRaterComeAgainText);
    // goto done;


// egg:
    // LD_HL(mNameRaterEggText);


// done:
    // CALL(aPrintText);
    // RET;
}

void CheckIfMonIsYourOT(void){
//  Checks to see if the partymon loaded in [wCurPartyMon] has the different OT as you.  Returns carry if not.
    LD_HL(wPartyMonOTs);
    LD_BC(NAME_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wPlayerName);
    LD_C(NAME_LENGTH);
    CALL(aCheckIfMonIsYourOT_loop);
    IF_C goto nope;

    LD_HL(wPartyMon1ID);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wPlayerID);
    LD_C(2);  // number of bytes in which your ID is stored

loop:
    LD_A_de;
    CP_A_hl;
    IF_NZ goto nope;
    INC_HL;
    INC_DE;
    DEC_C;
    IF_NZ goto loop;
    AND_A_A;
    RET;


nope:
    SCF;
    RET;

}

//  Checks to see if the partymon loaded in [wCurPartyMon] has the different OT as you.  Returns false (c) if not.
bool CheckIfMonIsYourOT_Conv(uint8_t partyMon){
    // LD_HL(wPartyMonOTs);
    // LD_BC(NAME_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_DE(wPlayerName);
    // LD_C(NAME_LENGTH);
    // CALL(aCheckIfMonIsYourOT_loop);
    for(uint32_t i = 0; i < NAME_LENGTH; ++i) {
        if(wram->wPartyMonOT[partyMon][i] != wram->wPlayerName[i])
            return false;
    }
    // IF_C goto nope;

    // LD_HL(wPartyMon1ID);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_DE(wPlayerID);
    // LD_C(2);  // number of bytes in which your ID is stored
    if(wram->wPartyMon[partyMon].mon.id != wram->wPlayerID)
        return false;

// loop:
    // LD_A_de;
    // CP_A_hl;
    // IF_NZ goto nope;
    // INC_HL;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto loop;
    // AND_A_A;
    // RET;
    return true;

// nope:
    // SCF;
    // RET;
}

void IsNewNameEmpty(void){
//  Checks to see if the nickname loaded in wStringBuffer2 is empty.  If so, return carry.
    LD_HL(wStringBuffer2);
    LD_C(MON_NAME_LENGTH - 1);

loop:
    LD_A_hli;
    CP_A(0x50);
    IF_Z goto terminator;
    CP_A(0x7f);
    IF_NZ goto nonspace;
    DEC_C;
    IF_NZ goto loop;


terminator:
    SCF;
    RET;


nonspace:
    AND_A_A;
    RET;

}

//  Checks to see if the nickname loaded in wStringBuffer2 is empty.  If so, return carry.
bool IsNewNameEmpty_Conv(void){
    // LD_HL(wStringBuffer2);
    uint8_t* hl = wram->wStringBuffer2;
    // LD_C(MON_NAME_LENGTH - 1);
    uint8_t c = MON_NAME_LENGTH - 1;

    uint8_t a;
    do {
    // loop:
        // LD_A_hli;
        a = *(hl++);
        // CP_A(0x50);
        // IF_Z goto terminator;
        if(a == 0x50) 
            break;
        // CP_A(0x7f);
        // IF_NZ goto nonspace;
        if(a != 0x7f) {
        // nonspace:
            // AND_A_A;
            // RET;
            return false;
        }
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);


// terminator:
    // SCF;
    // RET;
    return true;
}

void CompareNewToOld(void){
//  Compares the nickname in wStringBuffer2 to the previous nickname.  If they are the same, return carry.
    LD_HL(wPartyMonNicknames);
    LD_BC(MON_NAME_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    PUSH_HL;
    CALL(aGetNicknamenameLength);
    LD_B_C;
    LD_HL(wStringBuffer2);
    CALL(aGetNicknamenameLength);
    POP_HL;
    LD_A_C;
    CP_A_B;
    IF_NZ goto different;
    LD_DE(wStringBuffer2);

loop:
    LD_A_de;
    CP_A(0x50);
    IF_Z goto terminator;
    CP_A_hl;
    IF_NZ goto different;
    INC_HL;
    INC_DE;
    goto loop;


different:
    AND_A_A;
    RET;


terminator:
    SCF;
    RET;

}

//  Compares the nickname in wStringBuffer2 to the previous nickname.  If they are the same, return carry.
bool CompareNewToOld_Conv(uint8_t curPartyMon){
    // LD_HL(wPartyMonNicknames);
    // LD_BC(MON_NAME_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    uint8_t* hl = wram->wPartyMonNickname[curPartyMon];
    // PUSH_HL;
    // CALL(aGetNicknamenameLength);
    uint8_t b = GetNicknamenameLength_Conv(hl);
    // LD_B_C;
    // LD_HL(wStringBuffer2);
    // CALL(aGetNicknamenameLength);
    uint8_t c = GetNicknamenameLength_Conv(wram->wStringBuffer2);
    // POP_HL;
    // LD_A_C;
    // CP_A_B;
    // IF_NZ goto different;
    if(b != c) {
        return false;
    }
    // LD_DE(wStringBuffer2);
    uint8_t* de = wram->wStringBuffer2;

    for(int i = 0; de[i] != 0x50; ++i) {
    // loop:
        // LD_A_de;
        // CP_A(0x50);
        // IF_Z goto terminator;
        // CP_A_hl;
        // IF_NZ goto different;
        if(de[i] != hl[i])
            return false;
        // INC_HL;
        // INC_DE;
        // goto loop;


    // different:
        // AND_A_A;
        // RET;
    }

// terminator:
    // SCF;
    // RET;
    return true;
}

void GetNicknamenameLength(void){
//  Gets the length of the name starting at hl and returns it in c.
    LD_C(0);

loop:
    LD_A_hli;
    CP_A(0x50);
    RET_Z ;
    INC_C;
    LD_A_C;
    CP_A(MON_NAME_LENGTH - 1);
    IF_NZ goto loop;
    RET;

}

//  Gets the length of the name starting at hl and returns it in c.
uint8_t GetNicknamenameLength_Conv(const uint8_t* hl){
    // LD_C(0);
    uint8_t c = 0;

    do {
    // loop:
        // LD_A_hli;
        // CP_A(0x50);
        // RET_Z ;
        if(*(hl++) == 0x50)
            return c;
        // INC_C;
        c++;
        // LD_A_C;
        // CP_A(MON_NAME_LENGTH - 1);
        // IF_NZ goto loop;
    } while(c < MON_NAME_LENGTH - 1);
    // RET;
    return c;
}

