#include "../../constants.h"
#include "tempmon.h"
#include "bills_pc_top.h"
#include "../../home/pokemon.h"
#include "../../home/copy.h"
#include "../../home/sram.h"

void CopyMonToTempMon(void){
//  gets the BaseData of a mon
//  and copies the party_struct to wTempMon

    LD_A_addr(wCurPartyMon);
    LD_E_A;
    CALL(aGetMonSpecies);
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);

    LD_A_addr(wMonType);
    LD_HL(wPartyMon1Species);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    AND_A_A;
    IF_Z goto copywholestruct;
    LD_HL(wOTPartyMon1Species);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CP_A(OTPARTYMON);
    IF_Z goto copywholestruct;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALLFAR(aCopyBoxmonToTempMon);
    goto done;


copywholestruct:
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_DE(wTempMon);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);


done:
    RET;

}

//  gets the BaseData of a mon
//  and copies the party_struct to wTempMon
void CopyMonToTempMon_Conv(void){
    // LD_A_addr(wCurPartyMon);
    // LD_E_A;
    // CALL(aGetMonSpecies);
    GetMonSpecies_Conv(wram->wCurPartyMon);
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies;
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wCurPartySpecies);

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
        CopyBoxmonToTempMon_Conv();
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
        CopyBytes_Conv2(&wram->wTempMon, hl + wram->wCurPartyMon, sizeof(wram->wTempMon));
    }
// done:
    // RET;
}

void CalcBufferMonStats(void){
    LD_BC(wBufferMon);
    JR(mv_TempMonStatsCalculation);

}

void CalcTempmonStats(void){
    LD_BC(wTempMon);
    return v_TempMonStatsCalculation();
}

void CalcTempmonStats_Conv(void){
    // LD_BC(wTempMon);
    return v_TempMonStatsCalculation_Conv(&wram->wTempMon);
}

void v_TempMonStatsCalculation(void){
    LD_HL(MON_LEVEL);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurPartyLevel);
    LD_HL(MON_MAXHP);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(MON_STAT_EXP - 1);
    ADD_HL_BC;
    PUSH_BC;
    LD_B(TRUE);
    PREDEF(pCalcMonStats);
    POP_BC;
    LD_HL(MON_HP);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_NZ goto not_egg;
    XOR_A_A;
    LD_de_A;
    INC_DE;
    LD_de_A;
    goto zero_status;


not_egg:
    PUSH_BC;
    LD_HL(MON_MAXHP);
    ADD_HL_BC;
    LD_BC(2);
    CALL(aCopyBytes);
    POP_BC;


zero_status:
    LD_HL(MON_STATUS);
    ADD_HL_BC;
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    RET;

}

void v_TempMonStatsCalculation_Conv(struct PartyMon* bc){
    // LD_HL(MON_LEVEL);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = bc->mon.level;
    // LD_HL(MON_MAXHP);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    SAVE_REGS;
    REG_DE = RAMAddrToGB(&bc->maxHP);
    // LD_HL(MON_STAT_EXP - 1);
    // ADD_HL_BC;
    // PUSH_BC;
    REG_HL = RAMAddrToGB(bc->mon.statExp);
    // LD_B(TRUE);
    REG_B = TRUE;
    PREDEF(pCalcMonStats);
    RESTORE_REGS;
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

void GetMonSpecies(void){
//  [wMonType] has the type of the mon
//  e = Nr. of mon (i.e. [wCurPartyMon])

    LD_A_addr(wMonType);
    AND_A_A;  // PARTYMON
    IF_Z goto partymon;
    CP_A(OTPARTYMON);
    IF_Z goto otpartymon;
    CP_A(BOXMON);
    IF_Z goto boxmon;
    CP_A(TEMPMON);
    IF_Z goto breedmon;
// WILDMON


partymon:
    LD_HL(wPartySpecies);
    goto done;


otpartymon:
    LD_HL(wOTPartySpecies);
    goto done;


boxmon:
    LD_A(MBANK(asBoxSpecies));
    CALL(aOpenSRAM);
    LD_HL(sBoxSpecies);
    CALL(aGetMonSpecies_done);
    CALL(aCloseSRAM);
    RET;


breedmon:
    LD_A_addr(wBreedMon1Species);
    goto done2;


done:
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;


done2:
    LD_addr_A(wCurPartySpecies);
    RET;

}

//  [wMonType] has the type of the mon
//  e = Nr. of mon (i.e. [wCurPartyMon])
species_t GetMonSpecies_Conv(uint8_t e) {

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
            OpenSRAM_Conv(MBANK(asBoxSpecies));
            // LD_HL(sBoxSpecies);
            // CALL(aGetMonSpecies_done);
            a = gb_read(sBoxSpecies + e);
            wram->wCurPartySpecies = a;
            // CALL(aCloseSRAM);
            CloseSRAM_Conv();
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