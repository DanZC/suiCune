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
#include "../../util/serialize.h"
#include "../../data/text/common.h"

static void SetBoxmonOrEggmonCaughtData(struct BoxMon* boxmon, uint8_t level);
static void SetGiftMonCaughtData(struct BoxMon* hl, uint8_t b);

void CheckPartyFullAfterContest(void){
    // LD_A_addr(wContestMonSpecies);
    // AND_A_A;
    // JP_Z (mCheckPartyFullAfterContest_DidntCatchAnything);
    if(gPokemon.contestMon.mon.species == 0) {
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
    GetBaseData(gPokemon.contestMon.mon.species);
    // LD_HL(wPartyCount);
    // LD_A_hl;
    // CP_A(PARTY_LENGTH);
    // JP_NC (mCheckPartyFullAfterContest_TryAddToBox);
    if(gPokemon.partyCount >= PARTY_LENGTH) {
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
            CopyBytes(&wram->wBufferMon, &gPokemon.contestMon, sizeof(wram->wBufferMon));
            // LD_HL(wPlayerName);
            // LD_DE(wBufferMonOT);
            // LD_BC(NAME_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes(wram->wBufferMonOT, gPlayer.playerName, NAME_LENGTH);
            // CALLFAR(aInsertPokemonIntoBox);
            InsertPokemonIntoBox();
            // LD_A_addr(wCurPartySpecies);
            // LD_addr_A(wNamedObjectIndex);
            // CALL(aGetPokemonName);
            GetPokemonName(gPokemon.contestMon.mon.species);
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
                InitNickname(wram->wMonOrItemNameBuffer);
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
        gPokemon.contestMon.mon.species = 0;
        // LD_A(BUGCONTEST_BOXED_MON);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = BUGCONTEST_BOXED_MON;
        // RET;
        return;
    }
    // INC_A;
    // LD_hl_A;
    uint8_t i = gPokemon.partyCount++;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_addr(wContestMonSpecies);
    // LD_hli_A;
    gPokemon.partySpecies[i] = gPokemon.contestMon.mon.species;
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = gPokemon.contestMon.mon.species;
    // LD_A(-1);
    // LD_hl_A;
    gPokemon.partySpecies[i+1] = (species_t)-1;
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
    CopyBytes(gPokemon.partyMon + i, &gPokemon.contestMon, sizeof(gPokemon.contestMon));
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMonOTs);
    // CALL(aSkipNames);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wPlayerName);
    // CALL(aCopyBytes);
    CopyBytes(gPokemon.partyMonOT[i], gPlayer.playerName, NAME_LENGTH);
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // LD_DE(wMonOrItemNameBuffer);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wMonOrItemNameBuffer, GetPokemonName(gPokemon.contestMon.mon.species), MON_NAME_LENGTH);
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
        InitNickname(wram->wMonOrItemNameBuffer);
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
    CopyBytes(gPokemon.partyMonNickname[i], wram->wMonOrItemNameBuffer, MON_NAME_LENGTH);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1Level);
    // CALL(aGetPartyLocation);
    // LD_A_hl;
    // LD_addr_A(wCurPartyLevel);
    // CALL(aSetCaughtData);
    SetCaughtData(gPokemon.contestMon.mon.level);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1CaughtLocation);
    // CALL(aGetPartyLocation);
    // LD_A_hl;
    // AND_A(CAUGHT_GENDER_MASK);
    // LD_B(LANDMARK_NATIONAL_PARK);
    // OR_A_B;
    // LD_hl_A;
    gPokemon.partyMon[i].mon.caughtGenderLocation = (gPokemon.partyMon[i].mon.caughtGenderLocation & CAUGHT_GENDER_MASK) | LANDMARK_NATIONAL_PARK;
    // XOR_A_A;
    // LD_addr_A(wContestMonSpecies);
    gPokemon.contestMon.mon.species = 0;
    // AND_A_A;  // BUGCONTEST_CAUGHT_MON
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = BUGCONTEST_CAUGHT_MON;
    // RET;
    return;

}

bool GiveANickname_YesNo(void){
    // LD_HL(mCaughtAskNicknameText);
    // CALL(aPrintText);
    PrintText(CaughtAskNicknameText);
    // JP(mYesNoBox);
    return YesNoBox();
}

const txt_cmd_s CaughtAskNicknameText[] = {
    text_far(v_CaughtAskNicknameText)
    text_end
};

void SetCaughtData(uint8_t level){
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMon1CaughtLevel);
    // CALL(aGetPartyLocation);
    // return SetBoxmonOrEggmonCaughtData();
    return SetBoxmonOrEggmonCaughtData(&gPokemon.partyMon[gPokemon.partyCount - 1].mon, level);
}

static void SetBoxmonOrEggmonCaughtData(struct BoxMon* boxmon, uint8_t level){
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
    uint8_t b = gCurMapData.mapGroup;
    // LD_A_addr(wMapNumber);
    // LD_C_A;
    uint8_t c = gCurMapData.mapNumber;
    // CP_A(MAP_POKECENTER_2F);
    // IF_NZ goto NotPokecenter2F;
    // LD_A_B;
    // CP_A(GROUP_POKECENTER_2F);
    // IF_NZ goto NotPokecenter2F;

    if(b == GROUP_POKECENTER_2F && c == MAP_POKECENTER_2F) {
        // LD_A_addr(wBackupMapGroup);
        // LD_B_A;
        b = gCurMapData.backupMapGroup;
        // LD_A_addr(wBackupMapNumber);
        // LD_C_A;
        c = gCurMapData.backupMapNumber;
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
    struct Box box;
    Deserialize_Box(&box, GBToRAMAddr(sBox));
    // LD_HL(sBoxMon1CaughtLevel);
    // CALL(aSetBoxmonOrEggmonCaughtData);
    SetBoxmonOrEggmonCaughtData(box.mons, level);
    Serialize_Box(GBToRAMAddr(sBox), &box);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void SetGiftBoxMonCaughtData(uint8_t b){
    // PUSH_BC;
    // LD_A(BANK(sBoxMon1CaughtLevel));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asBoxMon1));
    struct Box box;
    Deserialize_Box(&box, GBToRAMAddr(sBox));
    // LD_HL(sBoxMon1CaughtLevel);
    struct BoxMon* hl = box.mons;
    // POP_BC;
    // CALL(aSetGiftMonCaughtData);
    SetGiftMonCaughtData(hl, b);
    Serialize_Box(GBToRAMAddr(sBox), &box);
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
    struct PartyMon* hl = gPokemon.partyMon + (gPokemon.partyCount - 1);
    // POP_BC;
    return SetGiftMonCaughtData(&hl->mon, b);
}

static void SetGiftMonCaughtData(struct BoxMon* hl, uint8_t b){
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

void SetEggMonCaughtData(uint8_t a){
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1CaughtLevel);
    // CALL(aGetPartyLocation);
    // LD_A_addr(wCurPartyLevel);
    // PUSH_AF;
    // LD_A(CAUGHT_EGG_LEVEL);
    // LD_addr_A(wCurPartyLevel);
    // CALL(aSetBoxmonOrEggmonCaughtData);
    SetBoxmonOrEggmonCaughtData(&gPokemon.partyMon[a].mon, CAUGHT_EGG_LEVEL);
    // POP_AF;
    // LD_addr_A(wCurPartyLevel);
    // RET;
}
