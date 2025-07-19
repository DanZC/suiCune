#include "../../constants.h"
#include "poke_seer.h"
#include "../../home/joypad.h"
#include "../../home/text.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../../home/print_text.h"
#include "../../home/copy_name.h"
#include "../overworld/landmarks.h"
#include "../pokemon/party_menu.h"
#include "../../data/text/common.h"

enum {
    SEER_INTRO,
    SEER_CANT_TELL,
    SEER_MET_AT,
    SEER_TIME_LEVEL,
    SEER_TRADED,
    SEER_CANCEL,
    SEER_EGG,
    SEER_LEVEL_ONLY,
};

enum {
    SEERACTION_MET,
    SEERACTION_TRADED,
    SEERACTION_CANT_TELL_1,
    SEERACTION_CANT_TELL_2,
    SEERACTION_LEVEL_ONLY,
};

void PokeSeer(void){
    // LD_A(SEER_INTRO);
    // CALL(aPrintSeerText);
    PrintSeerText(SEER_INTRO);
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();

    // LD_B(PARTY_LENGTH);
    // FARCALL(aSelectMonFromParty);
    u8_flag_s res = SelectMonFromParty();
    // IF_C goto cancel;
    if(!res.flag) {
        // LD_A_addr(wCurPartySpecies);
        // CP_A(EGG);
        // IF_Z goto egg;
        if(wram->wCurPartySpecies == EGG) {
        // egg:
            // LD_A(SEER_EGG);
            // CALL(aPrintSeerText);
            PrintSeerText(SEER_EGG);
            // RET;
            return;
        }

        // CALL(aIsAPokemon);
        // IF_C goto no_mon;
        if(!IsAPokemon(wram->wCurPartySpecies)) {
        // no_mon:
            // RET;
            return;
        }

        // CALL(aReadCaughtData);
        ReadCaughtData();
        // CALL(aSeerAction);
        SeerAction();
        // RET;
        return;
    }
    else {
    // cancel:
        // LD_A(SEER_CANCEL);
        // CALL(aPrintSeerText);
        PrintSeerText(SEER_CANCEL);
        // RET;
        return;
    }
}

void SeerAction(void){
    // LD_A_addr(wSeerAction);
    // LD_HL(mSeerActions);
    // RST(aJumpTable);
    // RET;
    return SeerActions[wram->wSeerAction]();
}

void (*const SeerActions[])(void) = {
    SeerAction0,
    SeerAction1,
    SeerAction2,
    SeerAction3,
    SeerAction4,
};

void SeerAction0(void){
    // LD_A(SEER_MET_AT);
    // CALL(aPrintSeerText);
    PrintSeerText(SEER_MET_AT);
    // LD_A(SEER_TIME_LEVEL);
    // CALL(aPrintSeerText);
    PrintSeerText(SEER_TIME_LEVEL);
    // CALL(aSeerAdvice);
    SeerAdvice();
    // RET;
}

void SeerAction1(void){
    // CALL(aGetCaughtOT);
    GetCaughtOT();
    // LD_A(SEER_TRADED);
    // CALL(aPrintSeerText);
    PrintSeerText(SEER_TRADED);
    // LD_A(SEER_TIME_LEVEL);
    // CALL(aPrintSeerText);
    PrintSeerText(SEER_CANT_TELL);
    // CALL(aSeerAdvice);
    SeerAdvice();
    // RET;
    return;
}

void SeerAction2(void){
    // LD_A(SEER_CANT_TELL);
    // CALL(aPrintSeerText);
    // RET;
    return PrintSeerText(SEER_CANT_TELL);
}

void SeerAction3(void){
    // LD_A(SEER_CANT_TELL);
    // CALL(aPrintSeerText);
    // RET;
    return PrintSeerText(SEER_CANT_TELL);
}

void SeerAction4(void){
    // LD_A(SEER_LEVEL_ONLY);
    // CALL(aPrintSeerText);
    PrintSeerText(SEER_LEVEL_ONLY);
    // CALL(aSeerAdvice);
    SeerAdvice();
    // RET;
}

void ReadCaughtData(void){
    // LD_A(MON_CAUGHTDATA);
    // CALL(aGetPartyParamLocation);
    struct PartyMon* mon = gPokemon.partyMon + wram->wCurPartyMon;
    // LD_A_hli;
    // LD_addr_A(wSeerCaughtData);
    wram->wSeerCaughtData = mon->mon.caughtTimeLevel;
    // LD_A_hld;
    // LD_addr_A(wSeerCaughtGender);
    wram->wSeerCaughtGender = mon->mon.caughtGenderLocation;
    // OR_A_hl;
    // IF_Z goto error;

    if(wram->wSeerCaughtGender != 0) {
        // LD_A(SEERACTION_TRADED);
        // LD_addr_A(wSeerAction);
        wram->wSeerAction = SEERACTION_TRADED;

        // LD_A(MON_ID);
        // CALL(aGetPartyParamLocation);
        // LD_A_addr(wPlayerID);
        // CP_A_hl;
        // IF_NZ goto traded;

        // INC_HL;
        // LD_A_addr(wPlayerID + 1);
    // cp [hl]
        // IF_NZ goto traded;
        if(mon->mon.id == gPlayer.playerID) {
            // LD_A(SEERACTION_MET);
            // LD_addr_A(wSeerAction);
            wram->wSeerAction = SEERACTION_MET;
        }

    // traded:
        // CALL(aGetCaughtLevel);
        GetCaughtLevel();
        // CALL(aGetCaughtOT);
        GetCaughtOT();
        // CALL(aGetCaughtName);
        GetCaughtName();
        // CALL(aGetCaughtTime);
        GetCaughtTime();
        // CALL(aGetCaughtLocation);
        GetCaughtLocation();
        // AND_A_A;
        // RET;
        return;
    }

// error:
    // LD_A(SEERACTION_CANT_TELL_1);
    // LD_addr_A(wSeerAction);
    wram->wSeerAction = SEERACTION_CANT_TELL_1;
    // RET;
}

void GetCaughtName(void){
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMonNicknames);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aAddNTimes);
    // LD_DE(wSeerNickname);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wSeerNickname, gPokemon.partyMonNickname[wram->wCurPartyMon], MON_NAME_LENGTH);
    // RET;
}

void GetCaughtLevel(void){
    static const char unknown_level[] = "???@";
    // LD_A(0x50);
    // LD_HL(wSeerCaughtLevelString);
    // LD_BC(4);
    // CALL(aByteFill);
    ByteFill(wram->wSeerCaughtLevelString, 4, 0x50);

// caught level
// Limited to between 1 and 63 since it's a 6-bit quantity.
    // LD_A_addr(wSeerCaughtData);
    // AND_A(CAUGHT_LEVEL_MASK);
    uint8_t caughtLevel = wram->wSeerCaughtData & CAUGHT_LEVEL_MASK;
    // IF_Z goto unknown;
    if(caughtLevel == 0) {
    // unknown:
        // LD_DE(wSeerCaughtLevelString);
        // LD_HL(mGetCaughtLevel_unknown_level);
        // LD_BC(4);
        // CALL(aCopyBytes);
        CopyBytes(wram->wSeerCaughtLevelString, U82C(unknown_level), 4);
        // RET;
        return;
    }
    // CP_A(CAUGHT_EGG_LEVEL);  // egg marker value
    // IF_NZ goto print;
    if(caughtLevel == CAUGHT_EGG_LEVEL) {
        // LD_A(EGG_LEVEL);  // egg hatch level
        wram->wSeerCaughtLevel = EGG_LEVEL;
    }

// print:
    // LD_addr_A(wSeerCaughtLevel);
    wram->wSeerCaughtLevel = caughtLevel;
    // LD_HL(wSeerCaughtLevelString);
    // LD_DE(wSeerCaughtLevel);
    // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum(wram->wSeerCaughtLevelString, &wram->wSeerCaughtLevel, PRINTNUM_LEFTALIGN | 1, 3);
    // RET;
}

void GetCaughtTime(void){
    static const char *times[] = {
        "Morning@",
        "Day@",
        "Night@",
    };
    // LD_A_addr(wSeerCaughtData);
    // AND_A(CAUGHT_TIME_MASK);
    uint8_t caughtData = (wram->wSeerCaughtData & CAUGHT_TIME_MASK) >> 6;
    // IF_Z goto none;
    if(caughtData == 0) {
    // none:
        // LD_DE(wSeerTimeOfDay);
        // CALL(aUnknownCaughtData);
        UnknownCaughtData(wram->wSeerTimeOfDay);
        // RET;
        return;
    }

    // RLCA;
    // RLCA;
    // DEC_A;
    // LD_HL(mGetCaughtTime_times);
    // CALL(aGetNthString);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wSeerTimeOfDay);
    // CALL(aCopyName2);
    CopyName2(wram->wSeerTimeOfDay, U82C(times[caughtData - 1]));
    // AND_A_A;
    // RET;
}

void UnknownCaughtData(uint8_t* de){
    // LD_HL(mUnknownCaughtData_unknown);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    // RET;
    U82CB(de, NAME_LENGTH, "Unknown@");
    return;
// unknown:
    //db ['"Unknown@"'];
}

void GetCaughtLocation(void){
    // LD_A_addr(wSeerCaughtGender);
    // AND_A(CAUGHT_LOCATION_MASK);
    uint8_t caughtGender = wram->wSeerCaughtGender & CAUGHT_LOCATION_MASK;
    // IF_Z goto Unknown;
    if(caughtGender == 0) {
    // Unknown:
        // LD_DE(wSeerCaughtLocation);
        // JP(mUnknownCaughtData);
        return UnknownCaughtData(wram->wSeerCaughtLocation);
    }
    // CP_A(LANDMARK_EVENT);
    // IF_Z goto event;
    else if(caughtGender == LANDMARK_EVENT) {
    // event:
        // LD_A(SEERACTION_LEVEL_ONLY);
        // LD_addr_A(wSeerAction);
        wram->wSeerAction = SEERACTION_LEVEL_ONLY;
        // SCF;
        // RET;
        return;
    }
    // CP_A(LANDMARK_GIFT);
    // IF_Z goto fail;
    else if(caughtGender == LANDMARK_GIFT) {
    // fail:
        // LD_A(SEERACTION_CANT_TELL_2);
        // LD_addr_A(wSeerAction);
        wram->wSeerAction = SEERACTION_CANT_TELL_2;
        // SCF;
        // RET;
        return;
    }
    // LD_E_A;
    // FARCALL(aGetLandmarkName);
    uint8_t* de = GetLandmarkName(caughtGender);
    // LD_HL(wStringBuffer1);
    // LD_DE(wSeerCaughtLocation);
    // LD_BC(17);
    // CALL(aCopyBytes);
    CopyBytes(wram->wSeerCaughtLocation, de, 17);
    // AND_A_A;
    // RET;
}

void GetCaughtOT(void){
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMonOTs);
    // LD_BC(NAME_LENGTH);
    // CALL(aAddNTimes);
    // LD_DE(wSeerOT);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wSeerOT, gPokemon.partyMonOT[wram->wCurPartyMon], NAME_LENGTH);

//  this routine is useless in Western localizations
    // LD_HL(mGetCaughtOT_male);
    // LD_A_addr(wSeerCaughtGender);
    // BIT_A(7);
    // IF_Z goto got_grammar;
    // LD_HL(mGetCaughtOT_female);


// got_grammar:
    // LD_DE(wSeerOTGrammar);
    // LD_A(0x50);
    // LD_de_A;
    wram->wSeerOTGrammar = 0x50;
    // RET;

// male:
    //db ['"@"'];

// female:
    //db ['"@"'];
}

void PrintSeerText(uint8_t a){
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSeerTexts);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // CALL(aPrintText);
    PrintText(SeerTexts[a]);
    // RET;
}

const txt_cmd_s* SeerTexts[] = {
    [SEER_INTRO] = SeerSeeAllText,
    [SEER_CANT_TELL] = SeerCantTellAThingText,
    [SEER_MET_AT] = SeerNameLocationText,
    [SEER_TIME_LEVEL] = SeerTimeLevelText,
    [SEER_TRADED] = SeerTradeText,
    [SEER_CANCEL] = SeerDoNothingText,
    [SEER_EGG] = SeerEggText,
    [SEER_LEVEL_ONLY] = SeerNoLocationText,
};

const txt_cmd_s SeerSeeAllText[] = {
    text_far(v_SeerSeeAllText)
    text_end
};

const txt_cmd_s SeerCantTellAThingText[] = {
    text_far(v_SeerCantTellAThingText)
    text_end
};

const txt_cmd_s SeerNameLocationText[] = {
    text_far(v_SeerNameLocationText)
    text_end
};

const txt_cmd_s SeerTimeLevelText[] = {
    text_far(v_SeerTimeLevelText)
    text_end
};

const txt_cmd_s SeerTradeText[] = {
    text_far(v_SeerTradeText)
    text_end
};

const txt_cmd_s SeerNoLocationText[] = {
    text_far(v_SeerNoLocationText)
    text_end
};

const txt_cmd_s SeerEggText[] = {
    text_far(v_SeerEggText)
    text_end
};

const txt_cmd_s SeerDoNothingText[] = {
    text_far(v_SeerDoNothingText)
    text_end
};

struct LevelText {
    uint8_t level;
    const txt_cmd_s* text;
};

//  level, text
const struct LevelText SeerAdviceTexts[] = {
    {9,     SeerMoreCareText},
    {29,    SeerMoreConfidentText},
    {59,    SeerMuchStrengthText},
    {89,    SeerMightyText},
    {100,   SeerImpressedText},
    {255,   SeerMoreCareText},
};

void SeerAdvice(void){
    // LD_A(MON_LEVEL);
    // CALL(aGetPartyParamLocation);
    // LD_A_addr(wSeerCaughtLevel);
    // LD_C_A;
    // LD_A_hl;
    // SUB_A_C;
    // LD_C_A;
    uint8_t c = gPokemon.partyMon[wram->wCurPartyMon].mon.level - wram->wSeerCaughtLevel;

    // LD_HL(mSeerAdviceTexts);
    const struct LevelText* hl = SeerAdviceTexts;
    // LD_DE(3);

    while(1) {
    // next:
        // CP_A_hl;
        // IF_C goto print;
        // IF_Z goto print;
        if(c <= hl->level) {
        // print:
            // INC_HL;
            // LD_A_hli;
            // LD_H_hl;
            // LD_L_A;
            // CALL(aPrintText);
            PrintText(hl->text);
            // RET;
            return;
        }
        // ADD_HL_DE;
        hl++;
        // goto next;
    }

}

const txt_cmd_s SeerMoreCareText[] = {
    text_far(v_SeerMoreCareText)
    text_end
};

const txt_cmd_s SeerMoreConfidentText[] = {
    text_far(v_SeerMoreConfidentText)
    text_end
};

const txt_cmd_s SeerMuchStrengthText[] = {
    text_far(v_SeerMuchStrengthText)
    text_end
};

const txt_cmd_s SeerMightyText[] = {
    text_far(v_SeerMightyText)
    text_end
};

const txt_cmd_s SeerImpressedText[] = {
    text_far(v_SeerImpressedText)
    text_end
};

uint8_t GetCaughtGender(struct BoxMon* mon){
    // LD_HL(MON_CAUGHTGENDER);
    // ADD_HL_BC;

    // LD_A_hl;
    uint8_t a = mon->caughtGenderLocation;
    // AND_A(CAUGHT_LOCATION_MASK);
    // IF_Z goto genderless;
    // CP_A(LANDMARK_EVENT);
    // IF_Z goto genderless;
    if((a & CAUGHT_LOCATION_MASK) == 0
    || a == LANDMARK_EVENT) {
    // genderless:
        // LD_C(CAUGHT_BY_UNKNOWN);
        // RET;
        return CAUGHT_BY_UNKNOWN;
    }
    // LD_A_hl;
    // AND_A(CAUGHT_GENDER_MASK);
    // IF_NZ goto male;
    // LD_C(CAUGHT_BY_GIRL);
    // RET;
    return (a & CAUGHT_GENDER_MASK)? CAUGHT_BY_BOY: CAUGHT_BY_GIRL;

// male:
    // LD_C(CAUGHT_BY_BOY);
    // RET;
}
