#include "../../constants.h"
#include "poke_seer.h"

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
    LD_A(SEER_INTRO);
    CALL(aPrintSeerText);
    CALL(aJoyWaitAorB);

    LD_B(PARTY_LENGTH);
    FARCALL(aSelectMonFromParty);
    IF_C goto cancel;

    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_Z goto egg;

    CALL(aIsAPokemon);
    IF_C goto no_mon;

    CALL(aReadCaughtData);
    CALL(aSeerAction);
    RET;


cancel:
    LD_A(SEER_CANCEL);
    CALL(aPrintSeerText);
    RET;


no_mon:
    RET;


egg:
    LD_A(SEER_EGG);
    CALL(aPrintSeerText);
    RET;

}

void SeerAction(void){
    LD_A_addr(wSeerAction);
    LD_HL(mSeerActions);
    RST(aJumpTable);
    RET;

}

void SeerActions(void){
    //dw ['SeerAction0'];
    //dw ['SeerAction1'];
    //dw ['SeerAction2'];
    //dw ['SeerAction3'];
    //dw ['SeerAction4'];

    return SeerAction0();
}

void SeerAction0(void){
    LD_A(SEER_MET_AT);
    CALL(aPrintSeerText);
    LD_A(SEER_TIME_LEVEL);
    CALL(aPrintSeerText);
    CALL(aSeerAdvice);
    RET;

}

void SeerAction1(void){
    CALL(aGetCaughtOT);
    LD_A(SEER_TRADED);
    CALL(aPrintSeerText);
    LD_A(SEER_TIME_LEVEL);
    CALL(aPrintSeerText);
    CALL(aSeerAdvice);
    RET;

}

void SeerAction2(void){
    LD_A(SEER_CANT_TELL);
    CALL(aPrintSeerText);
    RET;

}

void SeerAction3(void){
    LD_A(SEER_CANT_TELL);
    CALL(aPrintSeerText);
    RET;

}

void SeerAction4(void){
    LD_A(SEER_LEVEL_ONLY);
    CALL(aPrintSeerText);
    CALL(aSeerAdvice);
    RET;

}

void ReadCaughtData(void){
    LD_A(MON_CAUGHTDATA);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LD_addr_A(wSeerCaughtData);
    LD_A_hld;
    LD_addr_A(wSeerCaughtGender);
    OR_A_hl;
    IF_Z goto error;

    LD_A(SEERACTION_TRADED);
    LD_addr_A(wSeerAction);

    LD_A(MON_ID);
    CALL(aGetPartyParamLocation);
    LD_A_addr(wPlayerID);
    CP_A_hl;
    IF_NZ goto traded;

    INC_HL;
    LD_A_addr(wPlayerID + 1);
// cp [hl]
    IF_NZ goto traded;

    LD_A(SEERACTION_MET);
    LD_addr_A(wSeerAction);


traded:
    CALL(aGetCaughtLevel);
    CALL(aGetCaughtOT);
    CALL(aGetCaughtName);
    CALL(aGetCaughtTime);
    CALL(aGetCaughtLocation);
    AND_A_A;
    RET;


error:
    LD_A(SEERACTION_CANT_TELL_1);
    LD_addr_A(wSeerAction);
    RET;

}

void GetCaughtName(void){
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonNicknames);
    LD_BC(MON_NAME_LENGTH);
    CALL(aAddNTimes);
    LD_DE(wSeerNickname);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    RET;

}

void GetCaughtLevel(void){
    LD_A(0x50);
    LD_HL(wSeerCaughtLevelString);
    LD_BC(4);
    CALL(aByteFill);

// caught level
// Limited to between 1 and 63 since it's a 6-bit quantity.
    LD_A_addr(wSeerCaughtData);
    AND_A(CAUGHT_LEVEL_MASK);
    IF_Z goto unknown;
    CP_A(CAUGHT_EGG_LEVEL);  // egg marker value
    IF_NZ goto print;
    LD_A(EGG_LEVEL);  // egg hatch level


print:
    LD_addr_A(wSeerCaughtLevel);
    LD_HL(wSeerCaughtLevelString);
    LD_DE(wSeerCaughtLevel);
    LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 3);
    CALL(aPrintNum);
    RET;


unknown:
    LD_DE(wSeerCaughtLevelString);
    LD_HL(mGetCaughtLevel_unknown_level);
    LD_BC(4);
    CALL(aCopyBytes);
    RET;


unknown_level:
    //db ['"???@"'];

    return GetCaughtTime();
}

void GetCaughtTime(void){
    LD_A_addr(wSeerCaughtData);
    AND_A(CAUGHT_TIME_MASK);
    IF_Z goto none;

    RLCA;
    RLCA;
    DEC_A;
    LD_HL(mGetCaughtTime_times);
    CALL(aGetNthString);
    LD_D_H;
    LD_E_L;
    LD_HL(wSeerTimeOfDay);
    CALL(aCopyName2);
    AND_A_A;
    RET;


none:
    LD_DE(wSeerTimeOfDay);
    CALL(aUnknownCaughtData);
    RET;


times:
    //db ['"Morning@"'];
    //db ['"Day@"'];
    //db ['"Night@"'];

    return UnknownCaughtData();
}

void UnknownCaughtData(void){
    LD_HL(mUnknownCaughtData_unknown);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    RET;


unknown:
    //db ['"Unknown@"'];

    return GetCaughtLocation();
}

void GetCaughtLocation(void){
    LD_A_addr(wSeerCaughtGender);
    AND_A(CAUGHT_LOCATION_MASK);
    IF_Z goto Unknown;
    CP_A(LANDMARK_EVENT);
    IF_Z goto event;
    CP_A(LANDMARK_GIFT);
    IF_Z goto fail;
    LD_E_A;
    FARCALL(aGetLandmarkName);
    LD_HL(wStringBuffer1);
    LD_DE(wSeerCaughtLocation);
    LD_BC(17);
    CALL(aCopyBytes);
    AND_A_A;
    RET;


Unknown:
    LD_DE(wSeerCaughtLocation);
    JP(mUnknownCaughtData);


event:
    LD_A(SEERACTION_LEVEL_ONLY);
    LD_addr_A(wSeerAction);
    SCF;
    RET;


fail:
    LD_A(SEERACTION_CANT_TELL_2);
    LD_addr_A(wSeerAction);
    SCF;
    RET;

}

void GetCaughtOT(void){
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonOTs);
    LD_BC(NAME_LENGTH);
    CALL(aAddNTimes);
    LD_DE(wSeerOT);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);

//  this routine is useless in Western localizations
    LD_HL(mGetCaughtOT_male);
    LD_A_addr(wSeerCaughtGender);
    BIT_A(7);
    IF_Z goto got_grammar;
    LD_HL(mGetCaughtOT_female);


got_grammar:
    LD_DE(wSeerOTGrammar);
    LD_A(0x50);
    LD_de_A;
    RET;


male:
    //db ['"@"'];

female:
    //db ['"@"'];

    return PrintSeerText();
}

void PrintSeerText(void){
    LD_E_A;
    LD_D(0);
    LD_HL(mSeerTexts);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aPrintText);
    RET;

}

void SeerTexts(void){
    //dw ['SeerSeeAllText'];
    //dw ['SeerCantTellAThingText'];
    //dw ['SeerNameLocationText'];
    //dw ['SeerTimeLevelText'];
    //dw ['SeerTradeText'];
    //dw ['SeerDoNothingText'];
    //dw ['SeerEggText'];
    //dw ['SeerNoLocationText'];

    return SeerSeeAllText();
}

void SeerSeeAllText(void){
    //text_far ['_SeerSeeAllText']
    //text_end ['?']

    return SeerCantTellAThingText();
}

void SeerCantTellAThingText(void){
    //text_far ['_SeerCantTellAThingText']
    //text_end ['?']

    return SeerNameLocationText();
}

void SeerNameLocationText(void){
    //text_far ['_SeerNameLocationText']
    //text_end ['?']

    return SeerTimeLevelText();
}

void SeerTimeLevelText(void){
    //text_far ['_SeerTimeLevelText']
    //text_end ['?']

    return SeerTradeText();
}

void SeerTradeText(void){
    //text_far ['_SeerTradeText']
    //text_end ['?']

    return SeerNoLocationText();
}

void SeerNoLocationText(void){
    //text_far ['_SeerNoLocationText']
    //text_end ['?']

    return SeerEggText();
}

void SeerEggText(void){
    //text_far ['_SeerEggText']
    //text_end ['?']

    return SeerDoNothingText();
}

void SeerDoNothingText(void){
    //text_far ['_SeerDoNothingText']
    //text_end ['?']

    return SeerAdvice();
}

void SeerAdvice(void){
    LD_A(MON_LEVEL);
    CALL(aGetPartyParamLocation);
    LD_A_addr(wSeerCaughtLevel);
    LD_C_A;
    LD_A_hl;
    SUB_A_C;
    LD_C_A;

    LD_HL(mSeerAdviceTexts);
    LD_DE(3);

next:
    CP_A_hl;
    IF_C goto print;
    IF_Z goto print;
    ADD_HL_DE;
    goto next;


print:
    INC_HL;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aPrintText);
    RET;

}

void SeerAdviceTexts(void){
//  level, text
    //dbw ['9', 'SeerMoreCareText']
    //dbw ['29', 'SeerMoreConfidentText']
    //dbw ['59', 'SeerMuchStrengthText']
    //dbw ['89', 'SeerMightyText']
    //dbw ['100', 'SeerImpressedText']
    //dbw ['255', 'SeerMoreCareText']

    return SeerMoreCareText();
}

void SeerMoreCareText(void){
    //text_far ['_SeerMoreCareText']
    //text_end ['?']

    return SeerMoreConfidentText();
}

void SeerMoreConfidentText(void){
    //text_far ['_SeerMoreConfidentText']
    //text_end ['?']

    return SeerMuchStrengthText();
}

void SeerMuchStrengthText(void){
    //text_far ['_SeerMuchStrengthText']
    //text_end ['?']

    return SeerMightyText();
}

void SeerMightyText(void){
    //text_far ['_SeerMightyText']
    //text_end ['?']

    return SeerImpressedText();
}

void SeerImpressedText(void){
    //text_far ['_SeerImpressedText']
    //text_end ['?']

    return GetCaughtGender();
}

void GetCaughtGender(void){
    LD_HL(MON_CAUGHTGENDER);
    ADD_HL_BC;

    LD_A_hl;
    AND_A(CAUGHT_LOCATION_MASK);
    IF_Z goto genderless;
    CP_A(LANDMARK_EVENT);
    IF_Z goto genderless;

    LD_A_hl;
    AND_A(CAUGHT_GENDER_MASK);
    IF_NZ goto male;
    LD_C(CAUGHT_BY_GIRL);
    RET;


male:
    LD_C(CAUGHT_BY_BOY);
    RET;


genderless:
    LD_C(CAUGHT_BY_UNKNOWN);
    RET;

}

uint8_t GetCaughtGender_Conv(struct BoxMon* mon){
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
