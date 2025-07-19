#include "../../constants.h"
#include "shuckle.h"
#include "../pokemon/move_mon.h"
#include "../pokemon/caught_data.h"
#include "../pokemon/party_menu.h"
#include "../pokemon/bills_pc_top.h"
#include "../../home/copy_name.h"

#define MANIA_OT_ID (  518)

void GiveShuckle(void){
//  Adding to the party.
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;

//  Level 15 Shuckle.
    // LD_A(SHUCKLE);
    // LD_addr_A(wCurPartySpecies);
    // LD_A(15);
    // LD_addr_A(wCurPartyLevel);

    // PREDEF(pTryAddMonToParty);
    // IF_NC goto NotGiven;
    if(!TryAddMonToParty(SHUCKLE, 15)) {
    // NotGiven:
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = FALSE;
        // RET;
        return;
    }

//  Caught data.
    // LD_B(CAUGHT_BY_UNKNOWN);
    // FARCALL(aSetGiftPartyMonCaughtData);
    SetGiftPartyMonCaughtData(CAUGHT_BY_UNKNOWN);

//  Holding a Berry.
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // PUSH_AF;
    // PUSH_BC;
    // LD_HL(wPartyMon1Item);
    // CALL(aAddNTimes);
    // LD_hl(BERRY);
    gPokemon.partyMon[gPokemon.partyCount - 1].mon.item = BERRY;
    // POP_BC;
    // POP_AF;

//  OT ID.
    // LD_HL(wPartyMon1ID);
    // CALL(aAddNTimes);
    // LD_A(HIGH(MANIA_OT_ID));
    // LD_hli_A;
    // LD_hl(LOW(MANIA_OT_ID));
    gPokemon.partyMon[gPokemon.partyCount - 1].mon.id = NativeToBigEndian16(MANIA_OT_ID); // Is this correct?

//  Nickname.
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMonNicknames);
    // CALL(aSkipNames);
    // LD_DE(mSpecialShuckleNickname);
    // CALL(aCopyName2);
    CopyName2(gPokemon.partyMonNickname[gPokemon.partyCount - 1], U82C(SpecialShuckleNickname));

//  OT.
    // LD_A_addr(wPartyCount);
    // DEC_A;
    // LD_HL(wPartyMonOTs);
    // CALL(aSkipNames);
    // LD_DE(mSpecialShuckleOT);
    // CALL(aCopyName2);
    CopyName2(gPokemon.partyMonOT[gPokemon.partyCount - 1], U82C(SpecialShuckleOT));

//  Engine flag for this event.
    // LD_HL(wDailyFlags1);
    // SET_hl(DAILYFLAGS1_GOT_SHUCKIE_TODAY_F);
    bit_set(gPlayer.dailyFlags1, DAILYFLAGS1_GOT_SHUCKIE_TODAY_F);
    // LD_A(1);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
}

const char SpecialShuckleOT[] = "MANIA@";
const char SpecialShuckleNickname[] = "SHUCKIE@";

void ReturnShuckie(void){
    // FARCALL(aSelectMonFromParty);
    u8_flag_s res = SelectMonFromParty();
    // IF_C goto refused;
    if(res.flag) {
    // refused:
        // LD_A(SHUCKIE_REFUSED);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = SHUCKIE_REFUSED;
        // RET;
        return;
    }

    // LD_A_addr(wCurPartySpecies);
    // CP_A(SHUCKLE);
    // IF_NZ goto DontReturn;

    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1ID);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aAddNTimes);

//  OT ID
    // LD_A_hli;
    // CP_A(HIGH(MANIA_OT_ID));
    // IF_NZ goto DontReturn;
    // LD_A_hl;
    // CP_A(LOW(MANIA_OT_ID));
    // IF_NZ goto DontReturn;
    if(wram->wCurPartySpecies == SHUCKLE && gPokemon.partyMon[wram->wCurPartyMon].mon.id == NativeToBigEndian16(MANIA_OT_ID)) {
    //  OT
        // LD_A_addr(wCurPartyMon);
        // LD_HL(wPartyMonOTs);
        // CALL(aSkipNames);
        // LD_DE(mSpecialShuckleOT);
        const uint8_t* de = U82C(SpecialShuckleOT);
        const uint8_t* hl = gPokemon.partyMonOT[wram->wCurPartyMon];

        while(*hl == *de) {
        // CheckOT:
            // LD_A_de;
            // CP_A_hl;
            // IF_NZ goto DontReturn;
            // CP_A(0x50);
            // IF_Z goto done;
            if(*hl == 0x50) {
            // done:
                // FARCALL(aCheckCurPartyMonFainted);
                // IF_C goto fainted;
                if(CheckCurPartyMonFainted()) {
                // fainted:
                    // LD_A(SHUCKIE_FAINTED);
                    // LD_addr_A(wScriptVar);
                    wram->wScriptVar = SHUCKIE_FAINTED;
                    // RET;
                    return;
                }
                // LD_A_addr(wCurPartyMon);
                // LD_HL(wPartyMon1Happiness);
                // LD_BC(PARTYMON_STRUCT_LENGTH);
                // CALL(aAddNTimes);
                // LD_A_hl;
                // CP_A(150);
                // LD_A(SHUCKIE_HAPPY);
                // IF_NC goto HappyToStayWithYou;
                uint8_t a;
                if(gPokemon.partyMon[wram->wCurPartyMon].mon.happiness >= 150) {
                    a = SHUCKIE_HAPPY;
                }
                else {
                    // XOR_A_A;  // REMOVE_PARTY
                    // LD_addr_A(wPokemonWithdrawDepositParameter);
                    // CALLFAR(aRemoveMonFromPartyOrBox);
                    RemoveMonFromPartyOrBox(REMOVE_PARTY);
                    // LD_A(SHUCKIE_RETURNED);
                    a = SHUCKIE_RETURNED;
                }
            // HappyToStayWithYou:
                // LD_addr_A(wScriptVar);
                wram->wScriptVar = a;
                // RET;
                return;
            }
            // INC_DE;
            de++;
            // INC_HL;
            hl++;
            // goto CheckOT;
        }
    }

// DontReturn:
    // XOR_A_A;  // SHUCKIE_WRONG_MON
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = SHUCKIE_WRONG_MON;
    // RET;
    return;

}
