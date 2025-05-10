#include "../../constants.h"
#include "tempmon.h"
#include "bills_pc_top.h"
#include "move_mon.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../../home/sram.h"

static void v_TempMonStatsCalculation(struct PartyMon* bc);
static species_t GetMonSpecies(uint8_t e);

//  gets the BaseData of a mon
//  and copies the party_struct to wTempMon
void CopyMonToTempMon(void){
    // LD_A_addr(wCurPartyMon);
    // LD_E_A;
    // CALL(aGetMonSpecies);
    GetMonSpecies(wram->wCurPartyMon);
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies;
    // CALL(aGetBaseData);
    GetBaseData(wram->wCurPartySpecies);

    // LD_A_addr(wMonType);
    // LD_HL(wPartyMon1Species);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // AND_A_A;
    // IF_Z goto copywholestruct;
    // LD_HL(wOTPartyMon1Species);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CP_A(OTPARTYMON);
    // IF_Z goto copywholestruct;
    if(wram->wMonType != PARTYMON && wram->wMonType != OTPARTYMON) {
        // LD_BC(BOXMON_STRUCT_LENGTH);
        // CALLFAR(aCopyBoxmonToTempMon);
        CopyBoxmonToTempMon();
        // goto done;
    }
    else {
        struct PartyMon* hl = (wram->wMonType == PARTYMON)? wram->wPartyMon: wram->wOTPartyMon;
    // copywholestruct:
        // LD_A_addr(wCurPartyMon);
        // CALL(aAddNTimes);
        // LD_DE(wTempMon);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes(&wram->wTempMon, hl + wram->wCurPartyMon, sizeof(wram->wTempMon));
    }
// done:
    // RET;
}

void CalcBufferMonStats(void){
    // LD_BC(wBufferMon);
    // JR(mv_TempMonStatsCalculation);
    return v_TempMonStatsCalculation(&wram->wBufferMon);
}

void CalcTempmonStats(void){
    // LD_BC(wTempMon);
    return v_TempMonStatsCalculation(&wram->wTempMon);
}

static void v_TempMonStatsCalculation(struct PartyMon* bc){
    // LD_HL(MON_LEVEL);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = bc->mon.level;
    // LD_HL(MON_MAXHP);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    // REG_DE = RAMAddrToGB(&bc->maxHP);
    // LD_HL(MON_STAT_EXP - 1);
    // ADD_HL_BC;
    // PUSH_BC;
    // REG_HL = RAMAddrToGB(bc->mon.statExp);
    // LD_B(TRUE);
    // PREDEF(pCalcMonStats);
    CalcMonStats_PartyMon(bc, TRUE);
    // POP_BC;
    // LD_HL(MON_HP);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_NZ goto not_egg;
    if(wram->wCurPartySpecies == EGG) {
        // XOR_A_A;
        // LD_de_A;
        // INC_DE;
        // LD_de_A;
        bc->HP = 0;
        // goto zero_status;
    }
    else {
    // not_egg:
        // PUSH_BC;
        // LD_HL(MON_MAXHP);
        // ADD_HL_BC;
        // LD_BC(2);
        // CALL(aCopyBytes);
        bc->HP = bc->maxHP;
        // POP_BC;
    }

// zero_status:
    // LD_HL(MON_STATUS);
    // ADD_HL_BC;
    // XOR_A_A;
    // LD_hli_A;
    // LD_hl_A;
    bc->status = 0;
    bc->unused = 0;
    // RET;
}

//  [wMonType] has the type of the mon
//  e = Nr. of mon (i.e. [wCurPartyMon])
static species_t GetMonSpecies(uint8_t e) {
    uint8_t* hl;
    species_t a;
    // LD_A_addr(wMonType);
    // AND_A_A;  // PARTYMON
    // IF_Z goto partymon;
    // CP_A(OTPARTYMON);
    // IF_Z goto otpartymon;
    // CP_A(BOXMON);
    // IF_Z goto boxmon;
    // CP_A(TEMPMON);
    // IF_Z goto breedmon;
// WILDMON
    switch(wram->wMonType) {
        default:
        case PARTYMON:
        // partymon:
            // LD_HL(wPartySpecies);
            hl = wram->wPartySpecies;
            break;
        case OTPARTYMON:
        // otpartymon:
            // LD_HL(wOTPartySpecies);
            hl = wram->wOTPartySpecies;
            break;
        case BOXMON:
        // boxmon:
            // LD_A(BANK(sBoxSpecies));
            // CALL(aOpenSRAM);
            OpenSRAM(MBANK(asBoxSpecies));
            // LD_HL(sBoxSpecies);
            // CALL(aGetMonSpecies_done);
            a = gb_read(sBoxSpecies + e);
            wram->wCurPartySpecies = a;
            // CALL(aCloseSRAM);
            CloseSRAM();
            // RET;
            return a;
        case TEMPMON:
        // breedmon:
            // LD_A_addr(wBreedMon1Species);
            // goto done2;
            a = wram->wBreedMon1.species;
            wram->wCurPartySpecies = a;
            return a;
    }


// done:
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hl;
    a = hl[e];


// done2:
    // LD_addr_A(wCurPartySpecies);
    // RET;
    wram->wCurPartySpecies = a;
    return a;
}