#include "../../constants.h"
#include "caught_data.h"
#include "../../home/map.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../home/sram.h"
#include "../../data/text/common.h"

void CheckPartyFullAfterContest(void){
    LD_A_addr(wContestMonSpecies);
    AND_A_A;
    JP_Z (mCheckPartyFullAfterContest_DidntCatchAnything);
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_HL(wPartyCount);
    LD_A_hl;
    CP_A(PARTY_LENGTH);
    JP_NC (mCheckPartyFullAfterContest_TryAddToBox);
    INC_A;
    LD_hl_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wContestMonSpecies);
    LD_hli_A;
    LD_addr_A(wCurSpecies);
    LD_A(-1);
    LD_hl_A;
    LD_HL(wPartyMon1Species);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_HL(wContestMon);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMonOTs);
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    LD_HL(wPlayerName);
    CALL(aCopyBytes);
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(wStringBuffer1);
    LD_DE(wMonOrItemNameBuffer);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    CALL(aGiveANickname_YesNo);
    IF_C goto Party_SkipNickname;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    XOR_A_A;
    LD_addr_A(wMonType);
    LD_DE(wMonOrItemNameBuffer);
    CALLFAR(aInitNickname);


Party_SkipNickname:
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMonNicknames);
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    LD_HL(wMonOrItemNameBuffer);
    CALL(aCopyBytes);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1Level);
    CALL(aGetPartyLocation);
    LD_A_hl;
    LD_addr_A(wCurPartyLevel);
    CALL(aSetCaughtData);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1CaughtLocation);
    CALL(aGetPartyLocation);
    LD_A_hl;
    AND_A(CAUGHT_GENDER_MASK);
    LD_B(LANDMARK_NATIONAL_PARK);
    OR_A_B;
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wContestMonSpecies);
    AND_A_A;  // BUGCONTEST_CAUGHT_MON
    LD_addr_A(wScriptVar);
    RET;


TryAddToBox:
    LD_A(BANK(sBoxCount));
    CALL(aOpenSRAM);
    LD_HL(sBoxCount);
    LD_A_hl;
    CP_A(MONS_PER_BOX);
    CALL(aCloseSRAM);
    IF_NC goto BoxFull;
    XOR_A_A;
    LD_addr_A(wCurPartyMon);
    LD_HL(wContestMon);
    LD_DE(wBufferMon);
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    LD_HL(wPlayerName);
    LD_DE(wBufferMonOT);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    CALLFAR(aInsertPokemonIntoBox);
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    CALL(aGiveANickname_YesNo);
    LD_HL(wStringBuffer1);
    IF_C goto Box_SkipNickname;
    LD_A(BOXMON);
    LD_addr_A(wMonType);
    LD_DE(wMonOrItemNameBuffer);
    CALLFAR(aInitNickname);
    LD_HL(wMonOrItemNameBuffer);


Box_SkipNickname:
    LD_A(BANK(sBoxMonNicknames));
    CALL(aOpenSRAM);
    LD_DE(sBoxMonNicknames);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);


BoxFull:
    LD_A(BANK(sBoxMon1Level));
    CALL(aOpenSRAM);
    LD_A_addr(sBoxMon1Level);
    LD_addr_A(wCurPartyLevel);
    CALL(aCloseSRAM);
    CALL(aSetBoxMonCaughtData);
    LD_A(BANK(sBoxMon1CaughtLocation));
    CALL(aOpenSRAM);
    LD_HL(sBoxMon1CaughtLocation);
    LD_A_hl;
    AND_A(CAUGHT_GENDER_MASK);
    LD_B(LANDMARK_NATIONAL_PARK);
    OR_A_B;
    LD_hl_A;
    CALL(aCloseSRAM);
    XOR_A_A;
    LD_addr_A(wContestMon);
    LD_A(BUGCONTEST_BOXED_MON);
    LD_addr_A(wScriptVar);
    RET;


DidntCatchAnything:
    LD_A(BUGCONTEST_NO_CATCH);
    LD_addr_A(wScriptVar);
    RET;

}

bool GiveANickname_YesNo(void){
    // LD_HL(mCaughtAskNicknameText);
    // CALL(aPrintText);
    PrintText_Conv2(CaughtAskNicknameText);
    // JP(mYesNoBox);
    return YesNoBox_Conv();
}

const txt_cmd_s CaughtAskNicknameText[] = {
    text_far(v_CaughtAskNicknameText)
    text_end
};

void SetCaughtData(void){
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1CaughtLevel);
    CALL(aGetPartyLocation);
    return SetBoxmonOrEggmonCaughtData();
}

void SetCaughtData_Conv(void){
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1CaughtLevel);
    // CALL(aGetPartyLocation);
    // return SetBoxmonOrEggmonCaughtData();
    return SetBoxmonOrEggmonCaughtData_Conv(&wram->wPartyMon[wram->wPartyCount - 1].mon);
}

void SetBoxmonOrEggmonCaughtData(void){
    LD_A_addr(wTimeOfDay);
    INC_A;
    RRCA;
    RRCA;
    LD_B_A;
    LD_A_addr(wCurPartyLevel);
    OR_A_B;
    LD_hli_A;
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CP_A(MAP_POKECENTER_2F);
    IF_NZ goto NotPokecenter2F;
    LD_A_B;
    CP_A(GROUP_POKECENTER_2F);
    IF_NZ goto NotPokecenter2F;

    LD_A_addr(wBackupMapGroup);
    LD_B_A;
    LD_A_addr(wBackupMapNumber);
    LD_C_A;


NotPokecenter2F:
    CALL(aGetWorldMapLocation);
    LD_B_A;
    LD_A_addr(wPlayerGender);
    RRCA;  // shift bit 0 (PLAYERGENDER_FEMALE_F) to bit 7 (CAUGHT_GENDER_MASK)
    OR_A_B;
    LD_hl_A;
    RET;

}

void SetBoxmonOrEggmonCaughtData_Conv(struct BoxMon* boxmon){
    // LD_A_addr(wTimeOfDay);
    // INC_A;
    // RRCA;
    // RRCA;
    // LD_B_A;
    uint8_t time = ((wram->wTimeOfDay + 1) << 6);
    // LD_A_addr(wCurPartyLevel);
    // OR_A_B;
    // LD_hli_A;
    boxmon->caughtTimeLevel = (time | wram->wCurPartyLevel);
    // LD_A_addr(wMapGroup);
    // LD_B_A;
    uint8_t b = wram->wMapGroup;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    uint8_t c = wram->wMapNumber;
    // CP_A(MAP_POKECENTER_2F);
    // IF_NZ goto NotPokecenter2F;
    // LD_A_B;
    // CP_A(GROUP_POKECENTER_2F);
    // IF_NZ goto NotPokecenter2F;

    if(b == GROUP_POKECENTER_2F && c == MAP_POKECENTER_2F) {
        // LD_A_addr(wBackupMapGroup);
        // LD_B_A;
        b = wram->wBackupMapGroup;
        // LD_A_addr(wBackupMapNumber);
        // LD_C_A;
        c = wram->wBackupMapNumber;
    }

// NotPokecenter2F:
    // CALL(aGetWorldMapLocation);
    // LD_B_A;
    uint8_t loc = GetWorldMapLocation_Conv(b, c);
    // LD_A_addr(wPlayerGender);
    // RRCA;  // shift bit 0 (PLAYERGENDER_FEMALE_F) to bit 7 (CAUGHT_GENDER_MASK)
    uint8_t gender = (wram->wPlayerGender << 7);
    // OR_A_B;
    // LD_hl_A;
    // RET;
    boxmon->caughtGenderLocation = (loc | gender);
}

void SetBoxMonCaughtData(void){
    LD_A(BANK(sBoxMon1CaughtLevel));
    CALL(aOpenSRAM);
    LD_HL(sBoxMon1CaughtLevel);
    CALL(aSetBoxmonOrEggmonCaughtData);
    CALL(aCloseSRAM);
    RET;

}

void SetGiftBoxMonCaughtData(uint8_t b){
    // PUSH_BC;
    // LD_A(BANK(sBoxMon1CaughtLevel));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asBoxMon1CaughtLevel));
    // LD_HL(sBoxMon1CaughtLevel);
    uint16_t hl = sBoxMon1CaughtLevel;
    // POP_BC;
    // CALL(aSetGiftMonCaughtData);
    gb_write(hl++, 0);
    gb_write(hl, LANDMARK_GIFT | ((b & 1) << 7));
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void SetGiftPartyMonCaughtData(uint8_t b){
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1CaughtLevel);
    // PUSH_BC;
    // CALL(aGetPartyLocation);
    struct PartyMon* hl = wram->wPartyMon + (wram->wPartyCount - 1);
    // POP_BC;
    return SetGiftMonCaughtData_Conv(&hl->mon, b);
}

void SetGiftMonCaughtData(void){
    XOR_A_A;
    LD_hli_A;
    LD_A(LANDMARK_GIFT);
    RRC_B;
    OR_A_B;
    LD_hl_A;
    RET;

}

void SetGiftMonCaughtData_Conv(struct BoxMon* hl, uint8_t b){
    // XOR_A_A;
    // LD_hli_A;
    hl->caughtTimeLevel = 0;
    // LD_A(LANDMARK_GIFT);
    // RRC_B;
    // OR_A_B;
    // LD_hl_A;
    hl->caughtGenderLocation = LANDMARK_GIFT | ((b & 1) << 7);
    // RET;
}

void SetEggMonCaughtData(void){
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMon1CaughtLevel);
    CALL(aGetPartyLocation);
    LD_A_addr(wCurPartyLevel);
    PUSH_AF;
    LD_A(CAUGHT_EGG_LEVEL);
    LD_addr_A(wCurPartyLevel);
    CALL(aSetBoxmonOrEggmonCaughtData);
    POP_AF;
    LD_addr_A(wCurPartyLevel);
    RET;

}
