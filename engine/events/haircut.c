#include "../../constants.h"
#include "haircut.h"
#include "happiness_egg.h"
#include "../../home/copy.h"
#include "../../home/names.h"
#include "../../home/pokemon.h"
#include "../../home/random.h"
#include "../pokemon/party_menu.h"
#include "../../data/events/happiness_probabilities.h"

static void HaircutOrGrooming(const uint8_t (*hl)[3]);

void BillsGrandfather(void){
    // FARCALL(aSelectMonFromParty);
    // IF_C goto cancel;
    u8_flag_s res = SelectMonFromParty();
    if(res.flag) {
    // cancel:
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = FALSE;
        // RET;
        return;
    }
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wCurPartySpecies;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wCurPartySpecies);
    // JP(mCopyPokemonName_Buffer1_Buffer3);
    return CopyPokemonName_Buffer1_Buffer3();
}

void OlderHaircutBrother(void){
    // LD_HL(mHappinessData_OlderHaircutBrother);
    // JR(mHaircutOrGrooming);
    return HaircutOrGrooming(HappinessData_OlderHaircutBrother);
}

void YoungerHaircutBrother(void){
    // LD_HL(mHappinessData_YoungerHaircutBrother);
    // JR(mHaircutOrGrooming);
    return HaircutOrGrooming(HappinessData_YoungerHaircutBrother);
}

void DaisysGrooming(void){
    // LD_HL(mHappinessData_DaisysGrooming);
// fallthrough

    return HaircutOrGrooming(HappinessData_DaisysGrooming);
}

static void HaircutOrGrooming(const uint8_t (*hl)[3]){
    // PUSH_HL;
    // FARCALL(aSelectMonFromParty);
    u8_flag_s res = SelectMonFromParty();
    // POP_HL;
    // IF_C goto nope;
    if(res.flag) {
    // nope:
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x0;
        // RET;
        return;
    }
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_Z goto egg;
    if(wram->wCurPartySpecies == EGG) {
    // egg:
        // LD_A(1);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 1;
        // RET;
        return;
    }
    // PUSH_HL;
    // CALL(aGetCurNickname);
    GetCurNickname();
    // CALL(aCopyPokemonName_Buffer1_Buffer3);
    CopyPokemonName_Buffer1_Buffer3();
    // POP_HL;
    // CALL(aRandom);
    uint8_t a = Random();
//  Bug: Subtracting $ff from $ff fails to set c.
//  This can result in overflow into the next data array.
//  In the case of getting a grooming from Daisy, we bleed
//  into CopyPokemonName_Buffer1_Buffer3, which passes
//  $d0 to ChangeHappiness and returns $73 to the script.
//  The end result is that there is a 0.4% chance your
//  Pokemon's happiness will not change at all.

#if BUGFIX_HAIRCUT_PCT_FAIL
    while(a < (*hl)[0] && (*hl)[0] != 0xff)
#else
    while(a < (*hl)[0])
#endif
    {
    // loop:
        // SUB_A_hl;
        // IF_C goto ok;
        // INC_HL;
        // INC_HL;
        // INC_HL;
        // goto loop;
        hl++;
    }


// ok:
    // INC_HL;
    // LD_A_hli;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (*hl)[1];
    // LD_C_hl;
    // CALL(aChangeHappiness);
    ChangeHappiness((*hl)[2]);
    // RET;
}

void CopyPokemonName_Buffer1_Buffer3(void){
    // LD_HL(wStringBuffer1);
    // LD_DE(wStringBuffer3);
    // LD_BC(MON_NAME_LENGTH);
    // JP(mCopyBytes);
    return CopyBytes(wram->wStringBuffer3, wram->wStringBuffer1, MON_NAME_LENGTH);
}

void DummyPredef1(void){
    // RET;

}
