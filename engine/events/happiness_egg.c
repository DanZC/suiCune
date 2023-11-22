#include "../../constants.h"
#include "happiness_egg.h"

void GetFirstPokemonHappiness(void){
    LD_HL(wPartyMon1Happiness);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_DE(wPartySpecies);

loop:
    LD_A_de;
    CP_A(EGG);
    IF_NZ goto done;
    INC_DE;
    ADD_HL_BC;
    goto loop;


done:
    LD_addr_A(wNamedObjectIndex);
    LD_A_hl;
    LD_addr_A(wScriptVar);
    CALL(aGetPokemonName);
    JP(mCopyPokemonName_Buffer1_Buffer3);

}

void CheckFirstMonIsEgg(void){
    LD_A_addr(wPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CP_A(EGG);
    LD_A(TRUE);
    IF_Z goto egg;
    XOR_A_A;


egg:
    LD_addr_A(wScriptVar);
    CALL(aGetPokemonName);
    JP(mCopyPokemonName_Buffer1_Buffer3);

}

void ChangeHappiness(void){
//  Perform happiness action c on wCurPartyMon

    LD_A_addr(wCurPartyMon);
    INC_A;
    LD_E_A;
    LD_D(0);
    LD_HL(wPartySpecies - 1);
    ADD_HL_DE;
    LD_A_hl;
    CP_A(EGG);
    RET_Z ;

    PUSH_BC;
    LD_HL(wPartyMon1Happiness);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    POP_BC;

    LD_D_H;
    LD_E_L;

    PUSH_DE;
    LD_A_de;
    CP_A(HAPPINESS_THRESHOLD_1);
    LD_E(0);
    IF_C goto ok;
    INC_E;
    CP_A(HAPPINESS_THRESHOLD_2);
    IF_C goto ok;
    INC_E;


ok:
    DEC_C;
    LD_B(0);
    LD_HL(mHappinessChanges);
    ADD_HL_BC;
    ADD_HL_BC;
    ADD_HL_BC;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    CP_A(0x64);  // why not $80?
    POP_DE;

    LD_A_de;
    IF_NC goto negative;
    ADD_A_hl;
    IF_NC goto done;
    LD_A(-1);
    goto done;


negative:
    ADD_A_hl;
    IF_C goto done;
    XOR_A_A;


done:
    LD_de_A;
    LD_A_addr(wBattleMode);
    AND_A_A;
    RET_Z ;
    LD_A_addr(wCurPartyMon);
    LD_B_A;
    LD_A_addr(wPartyMenuCursor);
    CP_A_B;
    RET_NZ ;
    LD_A_de;
    LD_addr_A(wBattleMonHappiness);
    RET;

// INCLUDE "data/events/happiness_changes.asm"

    return StepHappiness();
}


//  Perform happiness action c on wCurPartyMon
void ChangeHappiness_Conv(uint8_t c){
    // LD_A_addr(wCurPartyMon);
    // INC_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wPartySpecies - 1);
    // ADD_HL_DE;
    // LD_A_hl;
    // CP_A(EGG);
    // RET_Z ;
    if(wram->wPartySpecies[wram->wCurPartyMon] == EGG)
        return;

    // PUSH_BC;
    // LD_HL(wPartyMon1Happiness);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // POP_BC;

    // LD_D_H;
    // LD_E_L;
    struct PartyMon* const de = wram->wPartyMon + wram->wCurPartyMon;

    uint8_t e;
    // PUSH_DE;
    // LD_A_de;
    // CP_A(HAPPINESS_THRESHOLD_1);
    // LD_E(0);
    // IF_C goto ok;
    if(de->mon.happiness < HAPPINESS_THRESHOLD_1)
        e = 0;
    // INC_E;
    // CP_A(HAPPINESS_THRESHOLD_2);
    // IF_C goto ok;
    else if(de->mon.happiness < HAPPINESS_THRESHOLD_2)
        e = 1;
    // INC_E;
    else 
        e = 2;


// ok:
    // DEC_C;
    // LD_B(0);
    // LD_HL(mHappinessChanges);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_D(0);
    // ADD_HL_DE;
    int8_t chg = HappinessChanges[c-1][e];
    // LD_A_hl;
    // CP_A(0x64);  // why not $80?
    // POP_DE;

    // LD_A_de;
    // IF_NC goto negative;
    uint8_t a = de->mon.happiness;
    if(chg < 0) {
    // negative:
        // ADD_A_hl;
        uint16_t temp = a + chg;
        // IF_C goto done;
        if((temp & 0xff00) == 0)
            a = 0;
        else
            a = temp & 0xff;
        // XOR_A_A;
    }
    else {
        // ADD_A_hl;
        uint16_t temp = a + chg;
        // IF_NC goto done;
        if((temp & 0xff00) == 0)
            a = 0xff;
        // LD_A(-1);
        else 
            a = temp & 0xff;
        // goto done;
    }

// done:
    // LD_de_A;
    de->mon.happiness = a;
    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // RET_Z ;
    if(wram->wBattleMode != 0) {
        // LD_A_addr(wCurPartyMon);
        // LD_B_A;
        // LD_A_addr(wPartyMenuCursor);
        // CP_A_B;
        // RET_NZ ;
        if(wram->wCurPartyMon == wram->wPartyMenuCursor) {
            // LD_A_de;
            // LD_addr_A(wBattleMonHappiness);
            wram->wBattleMon.happiness = a;
            // RET;
        }
    }
}

void StepHappiness(void){
//  Raise the party's happiness by 1 point every other step cycle.

    LD_HL(wHappinessStepCount);
    LD_A_hl;
    INC_A;
    AND_A(1);
    LD_hl_A;
    RET_NZ ;

    LD_DE(wPartyCount);
    LD_A_de;
    AND_A_A;
    RET_Z ;

    LD_C_A;
    LD_HL(wPartyMon1Happiness);

loop:
    INC_DE;
    LD_A_de;
    CP_A(EGG);
    IF_Z goto next;
    INC_hl;
    IF_NZ goto next;
    LD_hl(0xff);


next:
    PUSH_DE;
    LD_DE(PARTYMON_STRUCT_LENGTH);
    ADD_HL_DE;
    POP_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void DayCareStep(void){
//  Raise the experience of Day-Care Pokémon every step cycle.

    LD_A_addr(wDayCareMan);
    BIT_A(DAYCAREMAN_HAS_MON_F);
    IF_Z goto day_care_lady;

    LD_A_addr(wBreedMon1Level);  // level
    CP_A(MAX_LEVEL);
    IF_NC goto day_care_lady;
    LD_HL(wBreedMon1Exp + 2);  // exp
    INC_hl;
    IF_NZ goto day_care_lady;
    DEC_HL;
    INC_hl;
    IF_NZ goto day_care_lady;
    DEC_HL;
    INC_hl;
    LD_A_hl;
    CP_A(HIGH(MAX_DAY_CARE_EXP >> 8));
    IF_C goto day_care_lady;
    LD_A(HIGH(MAX_DAY_CARE_EXP >> 8));
    LD_hl_A;


day_care_lady:
    LD_A_addr(wDayCareLady);
    BIT_A(DAYCARELADY_HAS_MON_F);
    IF_Z goto check_egg;

    LD_A_addr(wBreedMon2Level);  // level
    CP_A(MAX_LEVEL);
    IF_NC goto check_egg;
    LD_HL(wBreedMon2Exp + 2);  // exp
    INC_hl;
    IF_NZ goto check_egg;
    DEC_HL;
    INC_hl;
    IF_NZ goto check_egg;
    DEC_HL;
    INC_hl;
    LD_A_hl;
    CP_A(HIGH(MAX_DAY_CARE_EXP >> 8));
    IF_C goto check_egg;
    LD_A(HIGH(MAX_DAY_CARE_EXP >> 8));
    LD_hl_A;


check_egg:
    LD_HL(wDayCareMan);
    BIT_hl(DAYCAREMAN_MONS_COMPATIBLE_F);
    RET_Z ;
    LD_HL(wStepsToEgg);
    DEC_hl;
    RET_NZ ;

    CALL(aRandom);
    LD_hl_A;
    CALLFAR(aCheckBreedmonCompatibility);
    LD_A_addr(wBreedingCompatibility);
    CP_A(230);
    LD_B(31 percent + 1);
    IF_NC goto okay;
    LD_A_addr(wBreedingCompatibility);
    CP_A(170);
    LD_B(16 percent);
    IF_NC goto okay;
    LD_A_addr(wBreedingCompatibility);
    CP_A(110);
    LD_B(12 percent);
    IF_NC goto okay;
    LD_B(4 percent);


okay:
    CALL(aRandom);
    CP_A_B;
    RET_NC ;
    LD_HL(wDayCareMan);
    RES_hl(DAYCAREMAN_MONS_COMPATIBLE_F);
    SET_hl(DAYCAREMAN_HAS_EGG_F);
    RET;

}
