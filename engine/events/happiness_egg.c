#include "../../constants.h"
#include "happiness_egg.h"
#include "haircut.h"
#include "../pokemon/breeding.h"
#include "../../home/names.h"
#include "../../home/random.h"

void GetFirstPokemonHappiness(void){
    // LD_HL(wPartyMon1Happiness);
    struct PartyMon* hl = wram->wPartyMon;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_DE(wPartySpecies);
    species_t* de = wram->wPartySpecies;

    while(*de == EGG) {
    // loop:
        // LD_A_de;
        // CP_A(EGG);
        // IF_NZ goto done;
        // INC_DE;
        // ADD_HL_BC;
        // goto loop;
        de++;
        hl++;
    }


// done:
    // LD_addr_A(wNamedObjectIndex);
    // LD_A_hl;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = hl->mon.happiness;
    // CALL(aGetPokemonName);
    GetPokemonName(*de);
    // JP(mCopyPokemonName_Buffer1_Buffer3);
    CopyPokemonName_Buffer1_Buffer3();
}

void CheckFirstMonIsEgg(void){
    // LD_A_addr(wPartySpecies);
    // LD_addr_A(wNamedObjectIndex);
    // CP_A(EGG);
    // LD_A(TRUE);
    // IF_Z goto egg;
    // XOR_A_A;
    wram->wScriptVar = (wram->wPartySpecies[0] == EGG)? TRUE: FALSE;

// egg:
    // LD_addr_A(wScriptVar);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wPartySpecies[0]);
    // JP(mCopyPokemonName_Buffer1_Buffer3);
    return CopyPokemonName_Buffer1_Buffer3();
}


//  Perform happiness action c on wCurPartyMon
void ChangeHappiness(uint8_t c){
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

//  Raise the party's happiness by 1 point every other step cycle.
void StepHappiness(void){
    // LD_HL(wHappinessStepCount);
    // LD_A_hl;
    uint8_t stepCount = (wram->wHappinessStepCount + 1) & 1;
    // INC_A;
    // AND_A(1);
    // LD_hl_A;
    wram->wHappinessStepCount = stepCount;
    // RET_NZ ;
    if(stepCount != 0)
        return;

    // LD_DE(wPartyCount);
    // LD_A_de;
    // AND_A_A;
    // RET_Z ;
    if(wram->wPartyCount != 0)
        return;

    // LD_C_A;
    uint8_t c = wram->wPartyCount;
    // LD_HL(wPartyMon1Happiness);
    struct PartyMon* hl = wram->wPartyMon;
    species_t* de = wram->wPartySpecies;

    do {
    // loop:
        // INC_DE;
        // LD_A_de;
        // CP_A(EGG);
        // IF_Z goto next;
        if(*de != EGG) {
            // INC_hl;
            // IF_NZ goto next;
            // LD_hl(0xff);
            if(++hl->mon.happiness == 0)
                hl->mon.happiness = 0xff;
        }

    // next:
        // PUSH_DE;
        // LD_DE(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_DE;
        // POP_DE;
        // DEC_C;
        // IF_NZ goto loop;
    } while(hl++, de++, --c != 0);
    // RET;
}

static void IncBreedMonExp(uint8_t* exp){
    if(++exp[2] != 0)
        return;
    if(++exp[1] != 0)
        return;
    uint8_t hi = ++exp[0];
    if(hi > HIGH(MAX_DAY_CARE_EXP >> 8))
        exp[0] = HIGH(MAX_DAY_CARE_EXP >> 8);
}

//  Raise the experience of Day-Care Pokémon every step cycle.
void DayCareStep(void){
    // LD_A_addr(wDayCareMan);
    // BIT_A(DAYCAREMAN_HAS_MON_F);
    // IF_Z goto day_care_lady;
    if(bit_test(wram->wDayCareMan, DAYCAREMAN_HAS_MON_F)){
        // LD_A_addr(wBreedMon1Level);  // level
        // CP_A(MAX_LEVEL);
        // IF_NC goto day_care_lady;
        if(wram->wBreedMon1.level < MAX_LEVEL){
            // LD_HL(wBreedMon1Exp + 2);  // exp
            // INC_hl;
            // IF_NZ goto day_care_lady;
            // DEC_HL;
            // INC_hl;
            // IF_NZ goto day_care_lady;
            // DEC_HL;
            // INC_hl;
            // LD_A_hl;
            // CP_A(HIGH(MAX_DAY_CARE_EXP >> 8));
            // IF_C goto day_care_lady;
            // LD_A(HIGH(MAX_DAY_CARE_EXP >> 8));
            // LD_hl_A;
            IncBreedMonExp(wram->wBreedMon1.exp);
        }
    }

// day_care_lady:
    // LD_A_addr(wDayCareLady);
    // BIT_A(DAYCARELADY_HAS_MON_F);
    // IF_Z goto check_egg;
    if(bit_test(wram->wDayCareLady, DAYCARELADY_HAS_MON_F)){
        // LD_A_addr(wBreedMon2Level);  // level
        // CP_A(MAX_LEVEL);
        // IF_NC goto check_egg;
        if(wram->wBreedMon2.level < MAX_LEVEL){
            // LD_HL(wBreedMon2Exp + 2);  // exp
            // INC_hl;
            // IF_NZ goto check_egg;
            // DEC_HL;
            // INC_hl;
            // IF_NZ goto check_egg;
            // DEC_HL;
            // INC_hl;
            // LD_A_hl;
            // CP_A(HIGH(MAX_DAY_CARE_EXP >> 8));
            // IF_C goto check_egg;
            // LD_A(HIGH(MAX_DAY_CARE_EXP >> 8));
            // LD_hl_A;
            IncBreedMonExp(wram->wBreedMon2.exp);
        }
    }

// check_egg:
    // LD_HL(wDayCareMan);
    // BIT_hl(DAYCAREMAN_MONS_COMPATIBLE_F);
    // RET_Z ;
    if(!bit_test(wram->wDayCareMan, DAYCAREMAN_MONS_COMPATIBLE_F))
        return;
    // LD_HL(wStepsToEgg);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wStepsToEgg != 0)
        return;

    // CALL(aRandom);
    // LD_hl_A;
    wram->wStepsToEgg = Random();
    // CALLFAR(aCheckBreedmonCompatibility);
    // LD_A_addr(wBreedingCompatibility);
    uint8_t b;
    uint8_t compat = CheckBreedmonCompatibility();
    // CP_A(230);
    // LD_B(31 percent + 1);
    // IF_NC goto okay;
    if(compat >= 230)
        b = 31 percent + 1;
    // LD_A_addr(wBreedingCompatibility);
    // CP_A(170);
    // LD_B(16 percent);
    // IF_NC goto okay;
    else if(compat >= 170)
        b = 16 percent;
    // LD_A_addr(wBreedingCompatibility);
    // CP_A(110);
    // LD_B(12 percent);
    // IF_NC goto okay;
    else if(compat >= 110)
        b = 12 percent;
    // LD_B(4 percent);
    else
        b = 4 percent;

// okay:
    // CALL(aRandom);
    // CP_A_B;
    // RET_NC ;
    if(Random() < b){
        // LD_HL(wDayCareMan);
        // RES_hl(DAYCAREMAN_MONS_COMPATIBLE_F);
        bit_reset(wram->wDayCareMan, DAYCAREMAN_MONS_COMPATIBLE_F);
        // SET_hl(DAYCAREMAN_HAS_EGG_F);
        bit_set(wram->wDayCareMan, DAYCAREMAN_HAS_EGG_F);
        // RET;
    }
}
