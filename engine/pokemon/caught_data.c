#include "../../constants.h"
#include "caught_data.h"
#include "move_mon.h"
#include "move_mon_wo_mail.h"
#include "../../home/map.h"
#include "../../home/menu.h"
#include "../../home/text.h"
#include "../../home/sram.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../../home/names.h"
#include "../../data/text/common.h"

void CheckPartyFullAfterContest(void){
    // LD_A_addr(wContestMonSpecies);
    // AND_A_A;
    // JP_Z (mCheckPartyFullAfterContest_DidntCatchAnything);
    if(wram->wContestMon.mon.species == 0) {
    // DidntCatchAnything:
        // LD_A(BUGCONTEST_NO_CATCH);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = BUGCONTEST_NO_CATCH;
        // RET;
        return;
    }

    // LD_addr_A(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wContestMon.mon.species);
    // LD_HL(wPartyCount);
    // LD_A_hl;
    // CP_A(PARTY_LENGTH);
    // JP_NC (mCheckPartyFullAfterContest_TryAddToBox);
    if(wram->wPartyCount >= PARTY_LENGTH) {
    // TryAddToBox:
        // LD_A(BANK(sBoxCount));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asBoxCount));
        // LD_HL(sBoxCount);
        // LD_A_hl;
        uint8_t boxCount = gb_read(sBoxCount);
        // CP_A(MONS_PER_BOX);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // IF_NC goto BoxFull;
        if(boxCount < MONS_PER_BOX) {
            // XOR_A_A;
            // LD_addr_A(wCurPartyMon);
            wram->wCurPartyMon = 0;
            // LD_HL(wContestMon);
            // LD_DE(wBufferMon);
            // LD_BC(BOXMON_STRUCT_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes(&wram->wBufferMon, &wram->wContestMon, sizeof(wram->wBufferMon));
            // LD_HL(wPlayerName);
            // LD_DE(wBufferMonOT);
            // LD_BC(NAME_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes(wram->wBufferMonOT, wram->wPlayerName, NAME_LENGTH);
            // CALLFAR(aInsertPokemonIntoBox);
            InsertPokemonIntoBox();
            // LD_A_addr(wCurPartySpecies);
            // LD_addr_A(wNamedObjectIndex);
            // CALL(aGetPokemonName);
            GetPokemonName(wram->wContestMon.mon.species);
            // CALL(aGiveANickname_YesNo);
            // LD_HL(wStringBuffer1);
            uint8_t* hl = wram->wStringBuffer1;
            // IF_C goto Box_SkipNickname;
            if(GiveANickname_YesNo()) {
                // LD_A(BOXMON);
                // LD_addr_A(wMonType);
                wram->wMonType = BOXMON;
                // LD_DE(wMonOrItemNameBuffer);
                // CALLFAR(aInitNickname);
                InitNickname_Conv(wram->wMonOrItemNameBuffer);
                // LD_HL(wMonOrItemNameBuffer);
                hl = wram->wMonOrItemNameBuffer;
            }

        // Box_SkipNickname:
            // LD_A(BANK(sBoxMonNicknames));
            // CALL(aOpenSRAM);
            OpenSRAM(MBANK(asBoxMonNicknames));
            // LD_DE(sBoxMonNicknames);
            // LD_BC(MON_NAME_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes(GBToRAMAddr(sBoxMonNicknames), hl, MON_NAME_LENGTH);
            // CALL(aCloseSRAM);
            CloseSRAM();
        }

    // BoxFull:
        // LD_A(BANK(sBoxMon1Level));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asBoxMon1Level));
        // LD_A_addr(sBoxMon1Level);
        // LD_addr_A(wCurPartyLevel);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // CALL(aSetBoxMonCaughtData);
        SetBoxMonCaughtData(gb_read(sBoxMon1Level));
        // LD_A(BANK(sBoxMon1CaughtLocation));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asBoxMon1CaughtLocation));
        // LD_HL(sBoxMon1CaughtLocation);
        // LD_A_hl;
        // AND_A(CAUGHT_GENDER_MASK);
        // LD_B(LANDMARK_NATIONAL_PARK);
        // OR_A_B;
        // LD_hl_A;
        gb_write(sBoxMon1CaughtLocation, (gb_read(sBoxMon1CaughtLocation) & CAUGHT_GENDER_MASK) | LANDMARK_NATIONAL_PARK);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // XOR_A_A;
        // LD_addr_A(wContestMon);
        wram->wContestMon.mon.species = 0;
        // LD_A(BUGCONTEST_BOXED_MON);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = BUGCONTEST_BOXED_MON;
        // RET;
        return;
    }
    // INC_A;
    // LD_hl_A;
    uint8_t i = wram->wPartyCount++;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_addr(wContestMonSpecies);
    // LD_hli_A;
    wram->wPartySpecies[i] = wram->wContestMon.mon.species;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wContestMon.mon.species;
    // LD_A(-1);
    // LD_hl_A;
    wram->wPartySpecies[i+1] = (species_t)-1;
    // LD_HL(wPartyMon1Species);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wContestMon);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPartyMon + i, &wram->wContestMon, sizeof(wram->wContestMon));
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMonOTs);
    // CALL(aSkipNames);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wPlayerName);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPartyMonOT[i], wram->wPlayerName, NAME_LENGTH);
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // LD_DE(wMonOrItemNameBuffer);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wMonOrItemNameBuffer, GetPokemonName(wram->wContestMon.mon.species), MON_NAME_LENGTH);
    // CALL(aGiveANickname_YesNo);
    // IF_C goto Party_SkipNickname;
    if(GiveANickname_YesNo()) {
        // LD_A_addr(wPartyCount);
        // DEC_A;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon = i;
        // XOR_A_A;
        // LD_addr_A(wMonType);
        wram->wMonType = 0;
        // LD_DE(wMonOrItemNameBuffer);
        // CALLFAR(aInitNickname);
        InitNickname_Conv(wram->wMonOrItemNameBuffer);
    }

// Party_SkipNickname:
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMonNicknames);
    // CALL(aSkipNames);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wMonOrItemNameBuffer);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPartyMonNickname[i], wram->wMonOrItemNameBuffer, MON_NAME_LENGTH);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1Level);
    // CALL(aGetPartyLocation);
    // LD_A_hl;
    // LD_addr_A(wCurPartyLevel);
    // CALL(aSetCaughtData);
    SetCaughtData_Conv(wram->wContestMon.mon.level);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1CaughtLocation);
    // CALL(aGetPartyLocation);
    // LD_A_hl;
    // AND_A(CAUGHT_GENDER_MASK);
    // LD_B(LANDMARK_NATIONAL_PARK);
    // OR_A_B;
    // LD_hl_A;
    wram->wPartyMon[i].mon.caughtGenderLocation = (wram->wPartyMon[i].mon.caughtGenderLocation & CAUGHT_GENDER_MASK) | LANDMARK_NATIONAL_PARK;
    // XOR_A_A;
    // LD_addr_A(wContestMonSpecies);
    wram->wContestMon.mon.species = 0;
    // AND_A_A;  // BUGCONTEST_CAUGHT_MON
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = BUGCONTEST_CAUGHT_MON;
    // RET;
    return;

}

bool GiveANickname_YesNo(void){
    // LD_HL(mCaughtAskNicknameText);
    // CALL(aPrintText);
    PrintText_Conv2(CaughtAskNicknameText);
    // JP(mYesNoBox);
    return YesNoBox();
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

void SetCaughtData_Conv(uint8_t level){
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1CaughtLevel);
    // CALL(aGetPartyLocation);
    // return SetBoxmonOrEggmonCaughtData();
    return SetBoxmonOrEggmonCaughtData_Conv(&wram->wPartyMon[wram->wPartyCount - 1].mon, level);
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

void SetBoxmonOrEggmonCaughtData_Conv(struct BoxMon* boxmon, uint8_t level){
    // LD_A_addr(wTimeOfDay);
    // INC_A;
    // RRCA;
    // RRCA;
    // LD_B_A;
    uint8_t time = ((wram->wTimeOfDay + 1) << 6);
    // LD_A_addr(wCurPartyLevel);
    // OR_A_B;
    // LD_hli_A;
    boxmon->caughtTimeLevel = (time | level);
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
    uint8_t loc = GetWorldMapLocation(b, c);
    // LD_A_addr(wPlayerGender);
    // RRCA;  // shift bit 0 (PLAYERGENDER_FEMALE_F) to bit 7 (CAUGHT_GENDER_MASK)
    uint8_t gender = (wram->wPlayerGender << 7);
    // OR_A_B;
    // LD_hl_A;
    // RET;
    boxmon->caughtGenderLocation = (loc | gender);
}

void SetBoxMonCaughtData(uint8_t level){
    // LD_A(BANK(sBoxMon1CaughtLevel));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxMon1CaughtLevel));
    // LD_HL(sBoxMon1CaughtLevel);
    // CALL(aSetBoxmonOrEggmonCaughtData);
    SetBoxmonOrEggmonCaughtData_Conv((struct BoxMon*)GBToRAMAddr(sBoxMon1CaughtLevel), level);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void SetGiftBoxMonCaughtData(uint8_t b){
    // PUSH_BC;
    // LD_A(BANK(sBoxMon1CaughtLevel));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxMon1CaughtLevel));
    // LD_HL(sBoxMon1CaughtLevel);
    struct BoxMon* hl = (struct BoxMon*)GBToRAMAddr(sBoxMon1CaughtLevel);
    // POP_BC;
    // CALL(aSetGiftMonCaughtData);
    SetGiftMonCaughtData_Conv(hl, b);
    // CALL(aCloseSRAM);
    CloseSRAM();
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

void SetEggMonCaughtData_Conv(uint8_t a){
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1CaughtLevel);
    // CALL(aGetPartyLocation);
    // LD_A_addr(wCurPartyLevel);
    // PUSH_AF;
    // LD_A(CAUGHT_EGG_LEVEL);
    // LD_addr_A(wCurPartyLevel);
    // CALL(aSetBoxmonOrEggmonCaughtData);
    SetBoxmonOrEggmonCaughtData_Conv(&wram->wPartyMon[a].mon, CAUGHT_EGG_LEVEL);
    // POP_AF;
    // LD_addr_A(wCurPartyLevel);
    // RET;
}
