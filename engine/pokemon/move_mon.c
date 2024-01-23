#include "../../constants.h"
#include "move_mon.h"
#include "../math/get_square_root.h"
#include "../../home/print_text.h"
#include "../../home/sram.h"
#include "../../home/copy.h"
#include "../../data/moves/moves.h"

#define RANDY_OT_ID (01001)

void TryAddMonToParty(void){
//  Check if to copy wild mon or generate a new one
// Whose is it?
    LD_DE(wPartyCount);
    LD_A_addr(wMonType);
    AND_A(0xf);
    IF_Z goto getpartylocation;  // PARTYMON
    LD_DE(wOTPartyCount);


getpartylocation:
// Do we have room for it?
    LD_A_de;
    INC_A;
    CP_A(PARTY_LENGTH + 1);
    RET_NC ;
// Increase the party count
    LD_de_A;
    LD_A_de;  // Why are we doing this?
    LDH_addr_A(hMoveMon);  // HRAM backup
    ADD_A_E;
    LD_E_A;
    IF_NC goto loadspecies;
    INC_D;


loadspecies:
// Load the species of the Pokemon into the party list.
// The terminator is usually here, but it'll be back.
    LD_A_addr(wCurPartySpecies);
    LD_de_A;
// Load the terminator into the next slot.
    INC_DE;
    LD_A(-1);
    LD_de_A;
// Now let's load the OT name.
    LD_HL(wPartyMonOTs);
    LD_A_addr(wMonType);
    AND_A(0xf);
    IF_Z goto loadOTname;
    LD_HL(wOTPartyMonOTs);


loadOTname:
    LDH_A_addr(hMoveMon);  // Restore index from backup
    DEC_A;
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    LD_HL(wPlayerName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
// Only initialize the nickname for party mon
    LD_A_addr(wMonType);
    AND_A_A;
    IF_NZ goto skipnickname;
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(wPartyMonNicknames);
    LDH_A_addr(hMoveMon);
    DEC_A;
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    LD_HL(wStringBuffer1);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);


skipnickname:
    LD_HL(wPartyMon1Species);
    LD_A_addr(wMonType);
    AND_A(0xf);
    IF_Z goto initializeStats;
    LD_HL(wOTPartyMon1Species);


initializeStats:
    LDH_A_addr(hMoveMon);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    return GeneratePartyMonStats();
}

void GeneratePartyMonStats(void){
//  wBattleMode specifies whether it's a wild mon or not.
//  wMonType specifies whether it's an opposing mon or not.
//  wCurPartySpecies/wCurPartyLevel specify the species and level.
//  hl points to the wPartyMon struct to fill.

    LD_E_L;
    LD_D_H;
    PUSH_HL;

// Initialize the species
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_A_addr(wBaseDexNo);
    LD_de_A;
    INC_DE;

// Copy the item if it's a wild mon
    LD_A_addr(wBattleMode);
    AND_A_A;
    LD_A(0x0);
    IF_Z goto skipitem;
    LD_A_addr(wEnemyMonItem);

skipitem:
    LD_de_A;
    INC_DE;

// Copy the moves if it's a wild mon
    PUSH_DE;
    LD_H_D;
    LD_L_E;
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_Z goto randomlygeneratemoves;
    LD_A_addr(wMonType);
    AND_A_A;
    IF_NZ goto randomlygeneratemoves;
    LD_DE(wEnemyMonMoves);
    for(int rept = 0; rept < NUM_MOVES - 1; rept++){
    LD_A_de;
    INC_DE;
    LD_hli_A;
    }
    LD_A_de;
    LD_hl_A;
    goto next;


randomlygeneratemoves:
    XOR_A_A;
    for(int rept = 0; rept < NUM_MOVES - 1; rept++){
    LD_hli_A;
    }
    LD_hl_A;
    LD_addr_A(wSkipMovesBeforeLevelUp);
    PREDEF(pFillMoves);


next:
    POP_DE;
    for(int rept = 0; rept < NUM_MOVES; rept++){
    INC_DE;
    }

// Initialize ID.
    LD_A_addr(wPlayerID);
    LD_de_A;
    INC_DE;
    LD_A_addr(wPlayerID + 1);
    LD_de_A;
    INC_DE;

// Initialize Exp.
    PUSH_DE;
    LD_A_addr(wCurPartyLevel);
    LD_D_A;
    CALLFAR(aCalcExpAtLevel);
    POP_DE;
    LDH_A_addr(hProduct + 1);
    LD_de_A;
    INC_DE;
    LDH_A_addr(hProduct + 2);
    LD_de_A;
    INC_DE;
    LDH_A_addr(hProduct + 3);
    LD_de_A;
    INC_DE;

// Initialize stat experience.
    XOR_A_A;
    LD_B(MON_DVS - MON_STAT_EXP);

loop:
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto loop;

    POP_HL;
    PUSH_HL;
    LD_A_addr(wMonType);
    AND_A(0xf);
    IF_Z goto registerpokedex;

    PUSH_HL;
    FARCALL(aGetTrainerDVs);
    POP_HL;
    goto initializeDVs;


registerpokedex:
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wTempSpecies);
    DEC_A;
    PUSH_DE;
    CALL(aCheckCaughtMon);
    LD_A_addr(wTempSpecies);
    DEC_A;
    CALL(aSetSeenAndCaughtMon);
    POP_DE;

    POP_HL;
    PUSH_HL;
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_NZ goto copywildmonDVs;

    CALL(aRandom);
    LD_B_A;
    CALL(aRandom);
    LD_C_A;

initializeDVs:
    LD_A_B;
    LD_de_A;
    INC_DE;
    LD_A_C;
    LD_de_A;
    INC_DE;

// Initialize PP.
    PUSH_HL;
    PUSH_DE;
    INC_HL;
    INC_HL;
    CALL(aFillPP);
    POP_DE;
    POP_HL;
    for(int rept = 0; rept < NUM_MOVES; rept++){
    INC_DE;
    }

// Initialize happiness.
    LD_A(BASE_HAPPINESS);
    LD_de_A;
    INC_DE;

    XOR_A_A;
// PokerusStatus
    LD_de_A;
    INC_DE;
// CaughtData/CaughtTime/CaughtLevel
    LD_de_A;
    INC_DE;
// CaughtGender/CaughtLocation
    LD_de_A;
    INC_DE;

// Initialize level.
    LD_A_addr(wCurPartyLevel);
    LD_de_A;
    INC_DE;

    XOR_A_A;
// Status
    LD_de_A;
    INC_DE;
// Unused
    LD_de_A;
    INC_DE;

// Initialize HP.
    LD_BC(MON_STAT_EXP - 1);
    ADD_HL_BC;
    LD_A(1);
    LD_C_A;
    LD_B(FALSE);
    CALL(aCalcMonStatC);
    LDH_A_addr(hProduct + 2);
    LD_de_A;
    INC_DE;
    LDH_A_addr(hProduct + 3);
    LD_de_A;
    INC_DE;
    goto initstats;


copywildmonDVs:
    LD_A_addr(wEnemyMonDVs);
    LD_de_A;
    INC_DE;
    LD_A_addr(wEnemyMonDVs + 1);
    LD_de_A;
    INC_DE;

    PUSH_HL;
    LD_HL(wEnemyMonPP);
    LD_B(NUM_MOVES);

wildmonpploop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto wildmonpploop;
    POP_HL;

// Initialize happiness.
    LD_A(BASE_HAPPINESS);
    LD_de_A;
    INC_DE;

    XOR_A_A;
// PokerusStatus
    LD_de_A;
    INC_DE;
// CaughtData/CaughtTime/CaughtLevel
    LD_de_A;
    INC_DE;
// CaughtGender/CaughtLocation
    LD_de_A;
    INC_DE;

// Initialize level.
    LD_A_addr(wCurPartyLevel);
    LD_de_A;
    INC_DE;

    LD_HL(wEnemyMonStatus);
// Copy wEnemyMonStatus
    LD_A_hli;
    LD_de_A;
    INC_DE;
// Copy EnemyMonUnused
    LD_A_hli;
    LD_de_A;
    INC_DE;
// Copy wEnemyMonHP
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    INC_DE;


initstats:
    LD_A_addr(wBattleMode);
    DEC_A;
    IF_NZ goto generatestats;
    LD_HL(wEnemyMonMaxHP);
    LD_BC(PARTYMON_STRUCT_LENGTH - MON_MAXHP);
    CALL(aCopyBytes);
    POP_HL;
    goto registerunowndex;


generatestats:
    POP_HL;
    LD_BC(MON_STAT_EXP - 1);
    ADD_HL_BC;
    LD_B(FALSE);
    CALL(aCalcMonStats);


registerunowndex:
    LD_A_addr(wMonType);
    AND_A(0xf);
    IF_NZ goto done;
    LD_A_addr(wCurPartySpecies);
    CP_A(UNOWN);
    IF_NZ goto done;
    LD_HL(wPartyMon1DVs);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    PREDEF(pGetUnownLetter);
    CALLFAR(aUpdateUnownDex);


done:
    SCF;  // When this function returns, the carry flag indicates success vs failure.
    RET;

}

void FillPP(void){
    PUSH_BC;
    LD_B(NUM_MOVES);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto next;
    DEC_A;
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_HL(mMoves);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_DE(wStringBuffer1);
    LD_A(BANK(aMoves));
    CALL(aFarCopyBytes);
    POP_BC;
    POP_DE;
    POP_HL;
    LD_A_addr(wStringBuffer1 + MOVE_PP);


next:
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto loop;
    POP_BC;
    RET;

}

void FillPP_Conv(uint8_t* de, const move_t* hl){
    // PUSH_BC;
    // LD_B(NUM_MOVES);
    for(uint8_t i = 0; i < NUM_MOVES; ++i) {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto next;
        if(hl[i] != NO_MOVE) {
            // DEC_A;
            // PUSH_HL;
            // PUSH_DE;
            // PUSH_BC;
            // LD_HL(mMoves);
            // LD_BC(MOVE_LENGTH);
            // CALL(aAddNTimes);
            // LD_DE(wStringBuffer1);
            // LD_A(BANK(aMoves));
            // CALL(aFarCopyBytes);
            // POP_BC;
            // POP_DE;
            // POP_HL;
            // LD_A_addr(wStringBuffer1 + MOVE_PP);
            de[i] = Moves[hl[i]].pp;
        }
        else {
            de[i] = 0;
        }
    // next:
        // LD_de_A;
        // INC_DE;
        // DEC_B;
        // IF_NZ goto loop;
    }
    // POP_BC;
    // RET;
}

void AddTempmonToParty(void){
    LD_HL(wPartyCount);
    LD_A_hl;
    CP_A(PARTY_LENGTH);
    SCF;
    RET_Z ;

    INC_A;
    LD_hl_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wCurPartySpecies);
    LD_hli_A;
    LD_hl(0xff);

    LD_HL(wPartyMon1Species);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    LD_HL(wTempMonSpecies);
    CALL(aCopyBytes);

    LD_HL(wPartyMonOTs);
    LD_A_addr(wPartyCount);
    DEC_A;
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    LD_HL(wOTPartyMonOTs);
    LD_A_addr(wCurPartyMon);
    CALL(aSkipNames);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);

    LD_HL(wPartyMonNicknames);
    LD_A_addr(wPartyCount);
    DEC_A;
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    LD_HL(wOTPartyMonNicknames);
    LD_A_addr(wCurPartyMon);
    CALL(aSkipNames);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);

    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CP_A(EGG);
    IF_Z goto egg;
    DEC_A;
    CALL(aSetSeenAndCaughtMon);
    LD_HL(wPartyMon1Happiness);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_hl(BASE_HAPPINESS);

egg:

    LD_A_addr(wCurPartySpecies);
    CP_A(UNOWN);
    IF_NZ goto done;
    LD_HL(wPartyMon1DVs);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    PREDEF(pGetUnownLetter);
    CALLFAR(aUpdateUnownDex);
    LD_A_addr(wFirstUnownSeen);
    AND_A_A;
    IF_NZ goto done;
    LD_A_addr(wUnownLetter);
    LD_addr_A(wFirstUnownSeen);

done:

    AND_A_A;
    RET;

}

void SendGetMonIntoFromBox(void){
//  Sents/Gets mon into/from Box depending on Parameter
//  wPokemonWithdrawDepositParameter == 0: get mon into Party
//  wPokemonWithdrawDepositParameter == 1: sent mon into Box
//  wPokemonWithdrawDepositParameter == 2: get mon from DayCare
//  wPokemonWithdrawDepositParameter == 3: put mon into DayCare

    LD_A(BANK(sBoxCount));
    CALL(aOpenSRAM);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_Z goto check_IfPartyIsFull;
    CP_A(DAY_CARE_WITHDRAW);
    IF_Z goto check_IfPartyIsFull;
    CP_A(DAY_CARE_DEPOSIT);
    LD_HL(wBreedMon1Species);
    IF_Z goto breedmon;

// we want to sent a mon into the Box
// so check if there's enough space
    LD_HL(sBoxCount);
    LD_A_hl;
    CP_A(MONS_PER_BOX);
    IF_NZ goto there_is_room;
    JP(mCloseSRAM_And_SetCarryFlag);


check_IfPartyIsFull:
    LD_HL(wPartyCount);
    LD_A_hl;
    CP_A(PARTY_LENGTH);
    JP_Z (mCloseSRAM_And_SetCarryFlag);


there_is_room:
    INC_A;
    LD_hl_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wPokemonWithdrawDepositParameter);
    CP_A(DAY_CARE_WITHDRAW);
    LD_A_addr(wBreedMon1Species);
    IF_Z goto okay1;
    LD_A_addr(wCurPartySpecies);


okay1:
    LD_hli_A;
    LD_hl(0xff);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    DEC_A;
    LD_HL(wPartyMon1Species);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_addr(wPartyCount);
    IF_NZ goto okay2;
    LD_HL(sBoxMon1Species);
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_addr(sBoxCount);


okay2:
    DEC_A;  // wPartyCount - 1
    CALL(aAddNTimes);


breedmon:
    PUSH_HL;
    LD_E_L;
    LD_D_H;
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    LD_HL(sBoxMon1Species);
    LD_BC(BOXMON_STRUCT_LENGTH);
    IF_Z goto okay3;
    CP_A(DAY_CARE_WITHDRAW);
    LD_HL(wBreedMon1Species);
    IF_Z goto okay4;
    LD_HL(wPartyMon1Species);
    LD_BC(PARTYMON_STRUCT_LENGTH);


okay3:
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);


okay4:
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    CP_A(DAY_CARE_DEPOSIT);
    LD_DE(wBreedMon1OT);
    IF_Z goto okay5;
    DEC_A;
    LD_HL(wPartyMonOTs);
    LD_A_addr(wPartyCount);
    IF_NZ goto okay6;
    LD_HL(sBoxMonOTs);
    LD_A_addr(sBoxCount);


okay6:
    DEC_A;
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;


okay5:
    LD_HL(sBoxMonOTs);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_Z goto okay7;
    LD_HL(wBreedMon1OT);
    CP_A(DAY_CARE_WITHDRAW);
    IF_Z goto okay8;
    LD_HL(wPartyMonOTs);


okay7:
    LD_A_addr(wCurPartyMon);
    CALL(aSkipNames);


okay8:
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    CP_A(DAY_CARE_DEPOSIT);
    LD_DE(wBreedMon1Nickname);
    IF_Z goto okay9;
    DEC_A;
    LD_HL(wPartyMonNicknames);
    LD_A_addr(wPartyCount);
    IF_NZ goto okay10;
    LD_HL(sBoxMonNicknames);
    LD_A_addr(sBoxCount);


okay10:
    DEC_A;
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;


okay9:
    LD_HL(sBoxMonNicknames);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_Z goto okay11;
    LD_HL(wBreedMon1Nickname);
    CP_A(DAY_CARE_WITHDRAW);
    IF_Z goto okay12;
    LD_HL(wPartyMonNicknames);


okay11:
    LD_A_addr(wCurPartyMon);
    CALL(aSkipNames);


okay12:
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    POP_HL;

    LD_A_addr(wPokemonWithdrawDepositParameter);
    CP_A(PC_DEPOSIT);
    IF_Z goto took_out_of_box;
    CP_A(DAY_CARE_DEPOSIT);
    JP_Z (mSendGetMonIntoFromBox_CloseSRAM_And_ClearCarryFlag);

    PUSH_HL;
    SRL_A;
    ADD_A(0x2);
    LD_addr_A(wMonType);
    PREDEF(pCopyMonToTempMon);
    CALLFAR(aCalcLevel);
    LD_A_D;
    LD_addr_A(wCurPartyLevel);
    POP_HL;

    LD_B_H;
    LD_C_L;
    LD_HL(MON_LEVEL);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(MON_MAXHP);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(MON_STAT_EXP - 1);
    ADD_HL_BC;

    PUSH_BC;
    LD_B(TRUE);
    CALL(aCalcMonStats);
    POP_BC;

    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_NZ goto CloseSRAM_And_ClearCarryFlag;
    LD_HL(MON_STATUS);
    ADD_HL_BC;
    XOR_A_A;
    LD_hl_A;
    LD_HL(MON_HP);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    IF_Z goto egg;
    INC_HL;
    INC_HL;
    LD_A_hli;
    LD_de_A;
    LD_A_hl;
    INC_DE;
    LD_de_A;
    goto CloseSRAM_And_ClearCarryFlag;


egg:
    XOR_A_A;
    LD_de_A;
    INC_DE;
    LD_de_A;
    goto CloseSRAM_And_ClearCarryFlag;


took_out_of_box:
    LD_A_addr(sBoxCount);
    DEC_A;
    LD_B_A;
    CALL(aRestorePPOfDepositedPokemon);

CloseSRAM_And_ClearCarryFlag:
    CALL(aCloseSRAM);
    AND_A_A;
    RET;

}

void CloseSRAM_And_SetCarryFlag(void){
    CALL(aCloseSRAM);
    SCF;
    RET;

}

void RestorePPOfDepositedPokemon(void){
    LD_A_B;
    LD_HL(sBoxMons);
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_B_H;
    LD_C_L;
    LD_HL(MON_PP);
    ADD_HL_BC;
    PUSH_HL;
    PUSH_BC;
    LD_DE(wTempMonPP);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);
    POP_BC;
    LD_HL(MON_MOVES);
    ADD_HL_BC;
    PUSH_HL;
    LD_DE(wTempMonMoves);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);
    POP_HL;
    POP_DE;

    LD_A_addr(wMenuCursorY);
    PUSH_AF;
    LD_A_addr(wMonType);
    PUSH_AF;
    LD_B(0);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto done;
    LD_addr_A(wTempMonMoves);
    LD_A(BOXMON);
    LD_addr_A(wMonType);
    LD_A_B;
    LD_addr_A(wMenuCursorY);
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    FARCALL(aGetMaxPPOfMove);
    POP_DE;
    POP_HL;
    LD_A_addr(wTempPP);
    LD_B_A;
    LD_A_de;
    AND_A(0b11000000);
    ADD_A_B;
    LD_de_A;
    POP_BC;
    INC_DE;
    INC_B;
    LD_A_B;
    CP_A(NUM_MOVES);
    IF_C goto loop;


done:
    POP_AF;
    LD_addr_A(wMonType);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    RET;

}

void RetrieveMonFromDayCareMan(void){
    LD_A_addr(wBreedMon1Species);
    LD_addr_A(wCurPartySpecies);
    LD_DE(SFX_TRANSACTION);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    CALL(aGetBreedMon1LevelGrowth);
    LD_A_B;
    LD_addr_A(wPrevPartyLevel);
    LD_A_E;
    LD_addr_A(wCurPartyLevel);
    XOR_A_A;
    LD_addr_A(wPokemonWithdrawDepositParameter);
    JP(mRetrieveBreedmon);

}

void RetrieveMonFromDayCareLady(void){
    LD_A_addr(wBreedMon2Species);
    LD_addr_A(wCurPartySpecies);
    LD_DE(SFX_TRANSACTION);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    CALL(aGetBreedMon2LevelGrowth);
    LD_A_B;
    LD_addr_A(wPrevPartyLevel);
    LD_A_E;
    LD_addr_A(wCurPartyLevel);
    LD_A(PC_DEPOSIT);
    LD_addr_A(wPokemonWithdrawDepositParameter);
    JP(mRetrieveBreedmon);  // pointless

}

void RetrieveBreedmon(void){
    LD_HL(wPartyCount);
    LD_A_hl;
    CP_A(PARTY_LENGTH);
    IF_NZ goto room_in_party;
    SCF;
    RET;


room_in_party:
    INC_A;
    LD_hl_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    LD_A_addr(wBreedMon1Species);
    LD_DE(wBreedMon1Nickname);
    IF_Z goto okay;
    LD_A_addr(wBreedMon2Species);
    LD_DE(wBreedMon2Nickname);


okay:
    LD_hli_A;
    LD_addr_A(wCurSpecies);
    LD_A(0xff);
    LD_hl_A;
    LD_HL(wPartyMonNicknames);
    LD_A_addr(wPartyCount);
    DEC_A;
    CALL(aSkipNames);
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    POP_DE;
    CALL(aCopyBytes);
    PUSH_HL;
    LD_HL(wPartyMonOTs);
    LD_A_addr(wPartyCount);
    DEC_A;
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aCopyBytes);
    PUSH_HL;
    CALL(aGetLastPartyMon);
    POP_HL;
    LD_BC(BOXMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    CALL(aGetBaseData);
    CALL(aGetLastPartyMon);
    LD_B_D;
    LD_C_E;
    LD_HL(MON_LEVEL);
    ADD_HL_BC;
    LD_A_addr(wCurPartyLevel);
    LD_hl_A;
    LD_HL(MON_MAXHP);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(0xa);
    ADD_HL_BC;
    PUSH_BC;
    LD_B(TRUE);
    CALL(aCalcMonStats);
    LD_HL(wPartyMon1Moves);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_A(TRUE);
    LD_addr_A(wSkipMovesBeforeLevelUp);
    PREDEF(pFillMoves);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    FARCALL(aHealPartyMon);
    LD_A_addr(wCurPartyLevel);
    LD_D_A;
    CALLFAR(aCalcExpAtLevel);
    POP_BC;
    LD_HL(0x8);
    ADD_HL_BC;
    LDH_A_addr(hMultiplicand);
    LD_hli_A;
    LDH_A_addr(hMultiplicand + 1);
    LD_hli_A;
    LDH_A_addr(hMultiplicand + 2);
    LD_hl_A;
    AND_A_A;
    RET;

}

void GetLastPartyMon(void){
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1Species);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    RET;

}

void DepositMonWithDayCareMan(void){
    LD_DE(wBreedMon1Nickname);
    CALL(aDepositBreedmon);
    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    JP(mRemoveMonFromPartyOrBox);

}

void DepositMonWithDayCareLady(void){
    LD_DE(wBreedMon2Nickname);
    CALL(aDepositBreedmon);
    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    JP(mRemoveMonFromPartyOrBox);

}

void DepositBreedmon(void){
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonNicknames);
    CALL(aSkipNames);
    CALL(aCopyBytes);
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonOTs);
    CALL(aSkipNames);
    CALL(aCopyBytes);
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMon1Species);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_BC(BOXMON_STRUCT_LENGTH);
    JP(mCopyBytes);

}

void SendMonIntoBox(void){
//  Sends the mon into one of Bills Boxes
//  the data comes mainly from 'wEnemyMon:'
    LD_A(BANK(sBoxCount));
    CALL(aOpenSRAM);
    LD_DE(sBoxCount);
    LD_A_de;
    CP_A(MONS_PER_BOX);
    JP_NC (mSendMonIntoBox_full);
    INC_A;
    LD_de_A;

    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    LD_C_A;

loop:
    INC_DE;
    LD_A_de;
    LD_B_A;
    LD_A_C;
    LD_C_B;
    LD_de_A;
    INC_A;
    IF_NZ goto loop;

    CALL(aGetBaseData);
    CALL(aShiftBoxMon);

    LD_HL(wPlayerName);
    LD_DE(sBoxMonOTs);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);

    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);

    LD_DE(sBoxMonNicknames);
    LD_HL(wStringBuffer1);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);

    LD_HL(wEnemyMon);
    LD_DE(sBoxMon1);
    LD_BC(1 + 1 + NUM_MOVES);  // species + item + moves
    CALL(aCopyBytes);

    LD_HL(wPlayerID);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    INC_DE;
    PUSH_DE;
    LD_A_addr(wCurPartyLevel);
    LD_D_A;
    CALLFAR(aCalcExpAtLevel);
    POP_DE;
    LDH_A_addr(hProduct + 1);
    LD_de_A;
    INC_DE;
    LDH_A_addr(hProduct + 2);
    LD_de_A;
    INC_DE;
    LDH_A_addr(hProduct + 3);
    LD_de_A;
    INC_DE;

// Set all 5 Experience Values to 0
    XOR_A_A;
    LD_B(2 * 5);

loop2:
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto loop2;

    LD_HL(wEnemyMonDVs);
    LD_B(2 + NUM_MOVES);  // DVs and PP // wEnemyMonHappiness - wEnemyMonDVs

loop3:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto loop3;

    LD_A(BASE_HAPPINESS);
    LD_de_A;
    INC_DE;
    XOR_A_A;
    LD_de_A;
    INC_DE;
    LD_de_A;
    INC_DE;
    LD_de_A;
    INC_DE;
    LD_A_addr(wCurPartyLevel);
    LD_de_A;
    LD_A_addr(wCurPartySpecies);
    DEC_A;
    CALL(aSetSeenAndCaughtMon);
    LD_A_addr(wCurPartySpecies);
    CP_A(UNOWN);
    IF_NZ goto not_unown;
    LD_HL(sBoxMon1DVs);
    PREDEF(pGetUnownLetter);
    CALLFAR(aUpdateUnownDex);


not_unown:
    LD_HL(sBoxMon1Moves);
    LD_DE(wTempMonMoves);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);

    LD_HL(sBoxMon1PP);
    LD_DE(wTempMonPP);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);

    LD_B(0);
    CALL(aRestorePPOfDepositedPokemon);

    CALL(aCloseSRAM);
    SCF;
    RET;


full:
    CALL(aCloseSRAM);
    AND_A_A;
    RET;

}

void ShiftBoxMon(void){
    LD_HL(sBoxMonOTs);
    LD_BC(NAME_LENGTH);
    CALL(aShiftBoxMon_shift);

    LD_HL(sBoxMonNicknames);
    LD_BC(MON_NAME_LENGTH);
    CALL(aShiftBoxMon_shift);

    LD_HL(sBoxMons);
    LD_BC(BOXMON_STRUCT_LENGTH);


shift:
    LD_A_addr(sBoxCount);
    CP_A(2);
    RET_C ;

    PUSH_HL;
    CALL(aAddNTimes);
    DEC_HL;
    LD_E_L;
    LD_D_H;
    POP_HL;

    LD_A_addr(sBoxCount);
    DEC_A;
    CALL(aAddNTimes);
    DEC_HL;

    PUSH_HL;
    LD_A_addr(sBoxCount);
    DEC_A;
    LD_HL(0);
    CALL(aAddNTimes);
    LD_C_L;
    LD_B_H;
    POP_HL;

loop:
    LD_A_hld;
    LD_de_A;
    DEC_DE;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop;
    RET;

}

void GiveEgg(void){
    LD_A_addr(wCurPartySpecies);
    PUSH_AF;
    CALLFAR(aGetPreEvolution);
    CALLFAR(aGetPreEvolution);
    LD_A_addr(wCurPartySpecies);
    DEC_A;

//  TryAddMonToParty sets Seen and Caught flags
//  when it is successful.  This routine will make
//  sure that we aren't newly setting flags.
    PUSH_AF;
    CALL(aCheckCaughtMon);
    POP_AF;
    PUSH_BC;
    CALL(aCheckSeenMon);
    PUSH_BC;

    CALL(aTryAddMonToParty);

//  If we haven't caught this Pokemon before receiving
//  the Egg, reset the flag that was just set by
//  TryAddMonToParty.
    POP_BC;
    LD_A_C;
    AND_A_A;
    IF_NZ goto skip_caught_flag;
    LD_A_addr(wCurPartySpecies);
    DEC_A;
    LD_C_A;
    LD_D(0x0);
    LD_HL(wPokedexCaught);
    LD_B(RESET_FLAG);
    PREDEF(pSmallFarFlagAction);


skip_caught_flag:
//  If we haven't seen this Pokemon before receiving
//  the Egg, reset the flag that was just set by
//  TryAddMonToParty.
    POP_BC;
    LD_A_C;
    AND_A_A;
    IF_NZ goto skip_seen_flag;
    LD_A_addr(wCurPartySpecies);
    DEC_A;
    LD_C_A;
    LD_D(0x0);
    LD_HL(wPokedexSeen);
    LD_B(RESET_FLAG);
    PREDEF(pSmallFarFlagAction);


skip_seen_flag:
    POP_AF;
    LD_addr_A(wCurPartySpecies);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1Species);
    CALL(aAddNTimes);
    LD_A_addr(wCurPartySpecies);
    LD_hl_A;
    LD_HL(wPartyCount);
    LD_A_hl;
    LD_B(0);
    LD_C_A;
    ADD_HL_BC;
    LD_A(EGG);
    LD_hl_A;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMonNicknames);
    CALL(aSkipNames);
    LD_DE(mString_Egg);
    CALL(aCopyName2);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1Happiness);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_addr(wDebugFlags);
    BIT_A(DEBUG_FIELD_F);
    LD_A(1);
    IF_NZ goto got_init_happiness;
    LD_A_addr(wBaseEggSteps);


got_init_happiness:
    LD_hl_A;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1HP);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    AND_A_A;
    RET;

}

void String_Egg(void){
    //db ['"EGG@"'];

    return RemoveMonFromPartyOrBox();
}

void RemoveMonFromPartyOrBox(void){
    LD_HL(wPartyCount);

    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_Z goto okay;

    LD_A(BANK(sBoxCount));
    CALL(aOpenSRAM);
    LD_HL(sBoxCount);


okay:
    LD_A_hl;
    DEC_A;
    LD_hli_A;
    LD_A_addr(wCurPartyMon);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_E_L;
    LD_D_H;
    INC_DE;

loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    INC_A;
    IF_NZ goto loop;
    LD_HL(wPartyMonOTs);
    LD_D(PARTY_LENGTH - 1);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_Z goto party;
    LD_HL(sBoxMonOTs);
    LD_D(MONS_PER_BOX - 1);


party:
// If this is the last mon in our party (box),
// shift all the other mons up to close the gap.
    LD_A_addr(wCurPartyMon);
    CALL(aSkipNames);
    LD_A_addr(wCurPartyMon);
    CP_A_D;
    IF_NZ goto delete_inside;
    LD_hl(-1);
    JP(mRemoveMonFromPartyOrBox_finish);


delete_inside:
// Shift the OT names
    LD_D_H;
    LD_E_L;
    LD_BC(MON_NAME_LENGTH);
    ADD_HL_BC;
    LD_BC(wPartyMonNicknames);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_Z goto party2;
    LD_BC(sBoxMonNicknames);

party2:
    CALL(aCopyDataUntil);
// Shift the struct
    LD_HL(wPartyMons);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_Z goto party4;
    LD_HL(sBoxMons);
    LD_BC(BOXMON_STRUCT_LENGTH);

party4:
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_Z goto party5;
    LD_BC(BOXMON_STRUCT_LENGTH);
    ADD_HL_BC;
    LD_BC(sBoxMonOTs);
    goto copy;


party5:
    LD_BC(PARTYMON_STRUCT_LENGTH);
    ADD_HL_BC;
    LD_BC(wPartyMonOTs);

copy:
    CALL(aCopyDataUntil);
// Shift the nicknames
    LD_HL(wPartyMonNicknames);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_Z goto party6;
    LD_HL(sBoxMonNicknames);

party6:
    LD_BC(MON_NAME_LENGTH);
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_BC(MON_NAME_LENGTH);
    ADD_HL_BC;
    LD_BC(wPartyMonNicknamesEnd);
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    IF_Z goto party7;
    LD_BC(sBoxMonNicknamesEnd);

party7:
    CALL(aCopyDataUntil);
// Mail time!

finish:
    LD_A_addr(wPokemonWithdrawDepositParameter);
    AND_A_A;
    JP_NZ (mCloseSRAM);
    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;
// Shift mail
    LD_A(BANK(sPartyMail));
    CALL(aOpenSRAM);
// If this is the last mon in our party, no need to shift mail.
    LD_HL(wPartyCount);
    LD_A_addr(wCurPartyMon);
    CP_A_hl;
    IF_Z goto close_sram;
// Shift our mail messages up.
    LD_HL(sPartyMail);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    PUSH_HL;
    ADD_HL_BC;
    POP_DE;
    LD_A_addr(wCurPartyMon);
    LD_B_A;

loop2:
    PUSH_BC;
    PUSH_HL;
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aCopyBytes);
    POP_HL;
    PUSH_HL;
    LD_BC(MAIL_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_DE;
    POP_BC;
    INC_B;
    LD_A_addr(wPartyCount);
    CP_A_B;
    IF_NZ goto loop2;

close_sram:
    JP(mCloseSRAM);

}

void RemoveMonFromPartyOrBox_Conv(uint8_t param){
    // LD_HL(wPartyCount);

    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // IF_Z goto okay;

    uint16_t sptr;
    species_t* wptr;
    if(param == REMOVE_PARTY) {
    // okay:
        // LD_A_hl;
        // DEC_A;
        // LD_hli_A;
        wram->wPartyCount--;
        wptr = wram->wPartySpecies;
        species_t a;
        do {
        // loop:
            // LD_A_de;
            // INC_DE;
            a = wptr[1];
            // LD_hli_A;
            *(wptr++) = a;
            // INC_A;
            // IF_NZ goto loop;
        } while(a != 0xff);
        // LD_HL(wPartyMonOTs);
        // LD_D(PARTY_LENGTH - 1);
        uint8_t d = PARTY_LENGTH - 1;
        // LD_A_addr(wPokemonWithdrawDepositParameter);
        // AND_A_A;
        // IF_Z goto party;
        // LD_HL(sBoxMonOTs);
        // LD_D(MONS_PER_BOX - 1);


    // party:
    // If this is the last mon in our party (box),
    // shift all the other mons up to close the gap.
        // LD_A_addr(wCurPartyMon);
        // CALL(aSkipNames);
        // LD_A_addr(wCurPartyMon);
        // CP_A_D;
        // IF_NZ goto delete_inside;
        if(wram->wCurPartyMon == d) {
            // LD_hl(-1);
            wram->wPartyMonOT[wram->wCurPartyMon][0] = -1;
            // JP(mRemoveMonFromPartyOrBox_finish);
            // goto finish;
        }
        else {
        // delete_inside:
        // Shift the OT names
            // LD_D_H;
            // LD_E_L;
            // LD_BC(MON_NAME_LENGTH);
            // ADD_HL_BC;
            // LD_BC(wPartyMonNicknames);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party2;
            // LD_BC(sBoxMonNicknames);

        // party2:
            // CALL(aCopyDataUntil);
            CopyDataUntil_Conv2(wram->wPartyMonOT[wram->wCurPartyMon], 
                wram->wPartyMonOT[wram->wCurPartyMon] + MON_NAME_LENGTH,
                wram->wPartyMonNickname);
        // Shift the struct
            // LD_HL(wPartyMons);
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party4;
            // LD_HL(sBoxMons);
            // LD_BC(BOXMON_STRUCT_LENGTH);

        // party4:
            // LD_A_addr(wCurPartyMon);
            // CALL(aAddNTimes);
            // LD_D_H;
            // LD_E_L;
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party5;
            // LD_BC(BOXMON_STRUCT_LENGTH);
            // ADD_HL_BC;
            // LD_BC(sBoxMonOTs);
            // goto copy;


        // party5:
            // LD_BC(PARTYMON_STRUCT_LENGTH);
            // ADD_HL_BC;
            // LD_BC(wPartyMonOTs);

        // copy:
            // CALL(aCopyDataUntil);
            CopyDataUntil_Conv2(wram->wPartyMon + wram->wCurPartyMon, 
                wram->wPartyMon + wram->wCurPartyMon + 1,
                wram->wPartyMonOT);
        // Shift the nicknames
            // LD_HL(wPartyMonNicknames);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party6;
            // LD_HL(sBoxMonNicknames);

        // party6:
            // LD_BC(MON_NAME_LENGTH);
            // LD_A_addr(wCurPartyMon);
            // CALL(aAddNTimes);
            // LD_D_H;
            // LD_E_L;
            // LD_BC(MON_NAME_LENGTH);
            // ADD_HL_BC;
            // LD_BC(wPartyMonNicknamesEnd);
            // LD_A_addr(wPokemonWithdrawDepositParameter);
            // AND_A_A;
            // IF_Z goto party7;
            // LD_BC(sBoxMonNicknamesEnd);

        // party7:
            // CALL(aCopyDataUntil);
            CopyDataUntil_Conv2(wram->wPartyMonNickname[wram->wCurPartyMon], 
                wram->wPartyMonNickname[wram->wCurPartyMon + 1],
                wram->wPartyMonNicknamesEnd);
        // Mail time!
        }
    // finish:
        // LD_A_addr(wPokemonWithdrawDepositParameter);
        // AND_A_A;
        // JP_NZ (mCloseSRAM);
        if(param != REMOVE_PARTY)
            return CloseSRAM_Conv();
        // LD_A_addr(wLinkMode);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wLinkMode != 0)
            return;
    // Shift mail
        // LD_A(BANK(sPartyMail));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(sPartyMail));
    // If this is the last mon in our party, no need to shift mail.
        // LD_HL(wPartyCount);
        // LD_A_addr(wCurPartyMon);
        // CP_A_hl;
        // IF_Z goto close_sram;
        if(wram->wPartyCount == wram->wCurPartyMon)
            return CloseSRAM_Conv();
    // Shift our mail messages up.
        // LD_HL(sPartyMail);
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // PUSH_HL;
        // ADD_HL_BC;
        // POP_DE;
        uint16_t mail = sPartyMail + (wram->wCurPartyMon * MAIL_STRUCT_LENGTH);
        uint16_t mail2 = mail + MAIL_STRUCT_LENGTH;
        // LD_A_addr(wCurPartyMon);
        // LD_B_A;
        uint8_t b = wram->wCurPartyMon;

        do {
        // loop2:
            // PUSH_BC;
            // PUSH_HL;
            // LD_BC(MAIL_STRUCT_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes_Conv(mail, mail2, MAIL_STRUCT_LENGTH);
            // POP_HL;
            // PUSH_HL;
            // LD_BC(MAIL_STRUCT_LENGTH);
            mail = mail2;
            mail2 += MAIL_STRUCT_LENGTH;
            // ADD_HL_BC;
            // POP_DE;
            // POP_BC;
            // INC_B;
            // LD_A_addr(wPartyCount);
            // CP_A_B;
            // IF_NZ goto loop2;
        } while(++b != wram->wPartyCount);

    // close_sram:
        // JP(mCloseSRAM);
        return CloseSRAM_Conv();
    }
    else {
        // LD_A(BANK(sBoxCount));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(sBoxCount));
        // LD_HL(sBoxCount);
        gb_write(sBoxCount, gb_read(sBoxCount) - 1);
        sptr = sBoxCount + 1;
        species_t a;
        do {
        // loop:
            // LD_A_de;
            // INC_DE;
            a = gb_read(sptr + 1);
            // LD_hli_A;
            gb_write(sptr++, a);
            // INC_A;
            // IF_NZ goto loop;
        } while(a != 0xff);
    }
    // LD_A_addr(wCurPartyMon);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_E_L;
    // LD_D_H;
    // INC_DE;

    // LD_HL(wPartyMonOTs);
    // LD_D(PARTY_LENGTH - 1);
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // IF_Z goto party;
    // LD_HL(sBoxMonOTs);
    // LD_D(MONS_PER_BOX - 1);


// party:
// If this is the last mon in our party (box),
// shift all the other mons up to close the gap.
    // LD_A_addr(wCurPartyMon);
    // CALL(aSkipNames);
    // LD_A_addr(wCurPartyMon);
    // CP_A_D;
    // IF_NZ goto delete_inside;
    // LD_hl(-1);
    // JP(mRemoveMonFromPartyOrBox_finish);


// delete_inside:
// Shift the OT names
    // LD_D_H;
    // LD_E_L;
    // LD_BC(MON_NAME_LENGTH);
    // ADD_HL_BC;
    // LD_BC(wPartyMonNicknames);
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // IF_Z goto party2;
    // LD_BC(sBoxMonNicknames);

// party2:
    // CALL(aCopyDataUntil);
// Shift the struct
    // LD_HL(wPartyMons);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // IF_Z goto party4;
    // LD_HL(sBoxMons);
    // LD_BC(BOXMON_STRUCT_LENGTH);

// party4:
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // IF_Z goto party5;
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // ADD_HL_BC;
    // LD_BC(sBoxMonOTs);
    // goto copy;


// party5:
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // ADD_HL_BC;
    // LD_BC(wPartyMonOTs);

// copy:
    // CALL(aCopyDataUntil);
// Shift the nicknames
    // LD_HL(wPartyMonNicknames);
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // IF_Z goto party6;
    // LD_HL(sBoxMonNicknames);

// party6:
    // LD_BC(MON_NAME_LENGTH);
    // LD_A_addr(wCurPartyMon);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // LD_BC(MON_NAME_LENGTH);
    // ADD_HL_BC;
    // LD_BC(wPartyMonNicknamesEnd);
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // IF_Z goto party7;
    // LD_BC(sBoxMonNicknamesEnd);

// party7:
    // CALL(aCopyDataUntil);
// Mail time!

// finish:
    // LD_A_addr(wPokemonWithdrawDepositParameter);
    // AND_A_A;
    // JP_NZ (mCloseSRAM);
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_NZ ;
// Shift mail
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
// If this is the last mon in our party, no need to shift mail.
    // LD_HL(wPartyCount);
    // LD_A_addr(wCurPartyMon);
    // CP_A_hl;
    // IF_Z goto close_sram;
// Shift our mail messages up.
    // LD_HL(sPartyMail);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aAddNTimes);
    // PUSH_HL;
    // ADD_HL_BC;
    // POP_DE;
    // LD_A_addr(wCurPartyMon);
    // LD_B_A;

// loop2:
    // PUSH_BC;
    // PUSH_HL;
    // LD_BC(MAIL_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    // POP_HL;
    // PUSH_HL;
    // LD_BC(MAIL_STRUCT_LENGTH);
    // ADD_HL_BC;
    // POP_DE;
    // POP_BC;
    // INC_B;
    // LD_A_addr(wPartyCount);
    // CP_A_B;
    // IF_NZ goto loop2;

// close_sram:
    // JP(mCloseSRAM);

}

void ComputeNPCTrademonStats(void){
    LD_A(MON_LEVEL);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    LD_addr_A(MON_LEVEL);  // should be "ld [wCurPartyLevel], a"
    LD_A(MON_SPECIES);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_A(MON_MAXHP);
    CALL(aGetPartyParamLocation);
    LD_D_H;
    LD_E_L;
    PUSH_DE;
    LD_A(MON_STAT_EXP - 1);
    CALL(aGetPartyParamLocation);
    LD_B(TRUE);
    CALL(aCalcMonStats);
    POP_DE;
    LD_A(MON_HP);
    CALL(aGetPartyParamLocation);
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_A_de;
    LD_hl_A;
    RET;

}

void CalcMonStats(void){
//  Calculates all 6 Stats of a mon
//  b: Take into account stat EXP if TRUE
//  'c' counts from 1-6 and points with 'wBaseStats' to the base value
//  hl is the path to the Stat EXP
//  de points to where the final stats will be saved

    LD_C(STAT_HP - 1);  // first stat

loop:
    INC_C;
    CALL(aCalcMonStatC);
    LDH_A_addr(hMultiplicand + 1);
    LD_de_A;
    INC_DE;
    LDH_A_addr(hMultiplicand + 2);
    LD_de_A;
    INC_DE;
    LD_A_C;
    CP_A(STAT_SDEF);  // last stat
    IF_NZ goto loop;
    RET;

}

//  Calculates all 6 Stats of a mon
//  b: Take into account stat EXP if TRUE
//  'c' counts from 1-6 and points with 'wBaseStats' to the base value
//  hl is the path to the Stat EXP
//  de points to where the final stats will be saved
void CalcMonStats_Conv(uint16_t* stats, const uint16_t* statExp, uint16_t dvs, uint8_t b){
    // LD_C(STAT_HP - 1);  // first stat
    uint8_t c = STAT_HP;

    while(c < STAT_SDEF + 1) {
    // loop:
        // INC_C;
        // CALL(aCalcMonStatC);
        uint16_t stat = NativeToBigEndian16(CalcMonStatC_Conv(statExp, dvs, b, c));
        // LDH_A_addr(hMultiplicand + 1);
        // LD_de_A;
        // INC_DE;
        // LDH_A_addr(hMultiplicand + 2);
        // LD_de_A;
        // INC_DE;
        stats[c - STAT_HP] = stat;
        // LD_A_C;
        // CP_A(STAT_SDEF);  // last stat
        // IF_NZ goto loop;
        c++;
    }
    // RET;
}

void CalcMonStatC(void){
//  'c' is 1-6 and points to the BaseStat
//  1: HP
//  2: Attack
//  3: Defense
//  4: Speed
//  5: SpAtk
//  6: SpDef
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    LD_A_B;
    LD_D_A;
    PUSH_HL;
    LD_HL(wBaseStats);
    DEC_HL;  // has to be decreased, because 'c' begins with 1
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_E_A;
    POP_HL;
    PUSH_HL;
    LD_A_C;
    CP_A(STAT_SDEF);  // last stat
    IF_NZ goto not_spdef;
    DEC_HL;
    DEC_HL;


not_spdef:
    SLA_C;
    LD_A_D;
    AND_A_A;
    IF_Z goto no_stat_exp;
    ADD_HL_BC;
    PUSH_DE;
    LD_A_hld;
    LD_E_A;
    LD_D_hl;
    FARCALL(aGetSquareRoot);
    POP_DE;


no_stat_exp:
    SRL_C;
    POP_HL;
    PUSH_BC;
    LD_BC(MON_DVS - MON_HP_EXP + 1);
    ADD_HL_BC;
    POP_BC;
    LD_A_C;
    CP_A(STAT_ATK);
    IF_Z goto Attack;
    CP_A(STAT_DEF);
    IF_Z goto Defense;
    CP_A(STAT_SPD);
    IF_Z goto Speed;
    CP_A(STAT_SATK);
    IF_Z goto Special;
    CP_A(STAT_SDEF);
    IF_Z goto Special;
//  DV_HP = (DV_ATK & 1) << 3 | (DV_DEF & 1) << 2 | (DV_SPD & 1) << 1 | (DV_SPC & 1)
    PUSH_BC;
    LD_A_hl;
    SWAP_A;
    AND_A(1);
    ADD_A_A;
    ADD_A_A;
    ADD_A_A;
    LD_B_A;
    LD_A_hli;
    AND_A(1);
    ADD_A_A;
    ADD_A_A;
    ADD_A_B;
    LD_B_A;
    LD_A_hl;
    SWAP_A;
    AND_A(1);
    ADD_A_A;
    ADD_A_B;
    LD_B_A;
    LD_A_hl;
    AND_A(1);
    ADD_A_B;
    POP_BC;
    goto GotDV;


Attack:
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    goto GotDV;


Defense:
    LD_A_hl;
    AND_A(0xf);
    goto GotDV;


Speed:
    INC_HL;
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    goto GotDV;


Special:
    INC_HL;
    LD_A_hl;
    AND_A(0xf);


GotDV:
    LD_D(0);
    ADD_A_E;
    LD_E_A;
    IF_NC goto no_overflow_1;
    INC_D;


no_overflow_1:
    SLA_E;
    RL_D;
    SRL_B;
    SRL_B;
    LD_A_B;
    ADD_A_E;
    IF_NC goto no_overflow_2;
    INC_D;


no_overflow_2:
    LDH_addr_A(hMultiplicand + 2);
    LD_A_D;
    LDH_addr_A(hMultiplicand + 1);
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LD_A_addr(wCurPartyLevel);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LDH_A_addr(hProduct + 1);
    LDH_addr_A(hDividend + 0);
    LDH_A_addr(hProduct + 2);
    LDH_addr_A(hDividend + 1);
    LDH_A_addr(hProduct + 3);
    LDH_addr_A(hDividend + 2);
    LD_A(100);
    LDH_addr_A(hDivisor);
    LD_A(3);
    LD_B_A;
    CALL(aDivide);
    LD_A_C;
    CP_A(STAT_HP);
    LD_A(STAT_MIN_NORMAL);
    IF_NZ goto not_hp;
    LD_A_addr(wCurPartyLevel);
    LD_B_A;
    LDH_A_addr(hQuotient + 3);
    ADD_A_B;
    LDH_addr_A(hMultiplicand + 2);
    IF_NC goto no_overflow_3;
    LDH_A_addr(hQuotient + 2);
    INC_A;
    LDH_addr_A(hMultiplicand + 1);


no_overflow_3:
    LD_A(STAT_MIN_HP);


not_hp:
    LD_B_A;
    LDH_A_addr(hQuotient + 3);
    ADD_A_B;
    LDH_addr_A(hMultiplicand + 2);
    IF_NC goto no_overflow_4;
    LDH_A_addr(hQuotient + 2);
    INC_A;
    LDH_addr_A(hMultiplicand + 1);


no_overflow_4:
    LDH_A_addr(hQuotient + 2);
    CP_A(HIGH(MAX_STAT_VALUE + 1) + 1);
    IF_NC goto max_stat;
    CP_A(HIGH(MAX_STAT_VALUE + 1));
    IF_C goto stat_value_okay;
    LDH_A_addr(hQuotient + 3);
    CP_A(LOW(MAX_STAT_VALUE + 1));
    IF_C goto stat_value_okay;


max_stat:
    LD_A(HIGH(MAX_STAT_VALUE));
    LDH_addr_A(hMultiplicand + 1);
    LD_A(LOW(MAX_STAT_VALUE));
    LDH_addr_A(hMultiplicand + 2);


stat_value_okay:
    POP_BC;
    POP_DE;
    POP_HL;
    RET;

}

//  'c' is 1-6 and points to the BaseStat
//  1: HP
//  2: Attack
//  3: Defense
//  4: Speed
//  5: SpAtk
//  6: SpDef
uint16_t CalcMonStatC_Conv(const uint16_t* statExp, uint16_t dvs, uint8_t b, uint8_t c){
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // LD_A_B;
    // LD_D_A;
    uint8_t d = b;
    // PUSH_HL;
    // LD_HL(wBaseStats);
    // DEC_HL;  // has to be decreased, because 'c' begins with 1
    // LD_B(0);
    b = 0;
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_E_A;
    uint8_t e = wram->wBaseStats[c - 1];
    // POP_HL;
    // PUSH_HL;
    // LD_A_C;
    // CP_A(STAT_SDEF);  // last stat
    // IF_NZ goto not_spdef;
    if(c == STAT_SDEF) {
        // DEC_HL;
        // DEC_HL;
        statExp--;
    }

// not_spdef:
    // SLA_C;
    // LD_A_D;
    // AND_A_A;
    // IF_Z goto no_stat_exp;
    if(d) {
        // ADD_HL_BC;
        // PUSH_DE;
        // LD_A_hld;
        // LD_E_A;
        // LD_D_hl;
        uint16_t de = BigEndianToNative16(statExp[c]);
        // FARCALL(aGetSquareRoot);
        b = GetSquareRoot_Conv(de);
        // POP_DE;
    }

// no_stat_exp:
    // SRL_C;
    // POP_HL;
    // PUSH_BC;
    // LD_BC(MON_DVS - MON_HP_EXP + 1);
    // ADD_HL_BC;
    // POP_BC;
    // LD_A_C;
    uint8_t dv;
    switch(c) {
        // CP_A(STAT_ATK);
        // IF_Z goto Attack;
        case STAT_ATK:
        // Attack:
            // LD_A_hl;
            // SWAP_A;
            // AND_A(0xf);
            dv = (LOW(dvs) >> 4) & 0xf;
            // goto GotDV;
            break;
        // CP_A(STAT_DEF);
        // IF_Z goto Defense;
        case STAT_DEF:
        // Defense:
            // LD_A_hl;
            // AND_A(0xf);
            dv = LOW(dvs) & 0xf;
            // goto GotDV;
            break;
        // CP_A(STAT_SPD);
        // IF_Z goto Speed;
        case STAT_SPD:
        // Speed:
            // INC_HL;
            // LD_A_hl;
            // SWAP_A;
            // AND_A(0xf);
            dv = (HIGH(dvs) >> 4) & 0xf;
            // goto GotDV;
            break;
        // CP_A(STAT_SATK);
        // IF_Z goto Special;
        // CP_A(STAT_SDEF);
        // IF_Z goto Special;
        case STAT_SATK:
        case STAT_SDEF:
        // Special:
            // INC_HL;
            // LD_A_hl;
            // AND_A(0xf);
            dv = HIGH(dvs) & 0xf;
            break;
    //  DV_HP = (DV_ATK & 1) << 3 | (DV_DEF & 1) << 2 | (DV_SPD & 1) << 1 | (DV_SPC & 1)
        default:
        case STAT_HP:
            // PUSH_BC;
            // LD_A_hl;
            // SWAP_A;
            // AND_A(1);
            // ADD_A_A;
            // ADD_A_A;
            // ADD_A_A;
            // LD_B_A;
            dv = (LOW(dvs) & 0x10) >> 1;
            // LD_A_hli;
            // AND_A(1);
            // ADD_A_A;
            // ADD_A_A;
            // ADD_A_B;
            // LD_B_A;
            dv += (LOW(dvs) & 0x1) << 2;
            // LD_A_hl;
            // SWAP_A;
            // AND_A(1);
            // ADD_A_A;
            // ADD_A_B;
            // LD_B_A;
            dv += (HIGH(dvs) & 0x10) >> 3;
            // LD_A_hl;
            // AND_A(1);
            // ADD_A_B;
            dv += (HIGH(dvs) & 0x1);
            // POP_BC;
            // goto GotDV;
            break;
    }


// GotDV:
    // LD_D(0);
    // ADD_A_E;
    // LD_E_A;
    uint8_t carry = 0;
    e = AddCarry8(dv, e, 0, &carry);
    // IF_NC goto no_overflow_1;
    // INC_D;
    d = (carry)? 1: 0;

// no_overflow_1:
    // SLA_E;
    carry = (e >> 7);
    e <<= 1;
    // RL_D;
    d = RotateLeft8(d, carry, &carry);
    // SRL_B;
    // SRL_B;
    // LD_A_B;
    // ADD_A_E;
    dv = AddCarry8(b >> 2, e, 0, &carry);
    // IF_NC goto no_overflow_2;
    // INC_D;
    d += (carry)? 1: 0;

// no_overflow_2:
    // LDH_addr_A(hMultiplicand + 2);
    // LD_A_D;
    // LDH_addr_A(hMultiplicand + 1);
    // XOR_A_A;
    // LDH_addr_A(hMultiplicand + 0);
    uint32_t mul = (dv | (d << 8));
    // LD_A_addr(wCurPartyLevel);
    // LDH_addr_A(hMultiplier);
    // CALL(aMultiply);
    uint32_t prod = mul * wram->wCurPartyLevel;
    // LDH_A_addr(hProduct + 1);
    // LDH_addr_A(hDividend + 0);
    // LDH_A_addr(hProduct + 2);
    // LDH_addr_A(hDividend + 1);
    // LDH_A_addr(hProduct + 3);
    // LDH_addr_A(hDividend + 2);
    // LD_A(100);
    // LDH_addr_A(hDivisor);
    // LD_A(3);
    // LD_B_A;
    // CALL(aDivide);
    uint16_t quot = (uint16_t)(prod / 100);
    // LD_A_C;
    // CP_A(STAT_HP);
    // LD_A(STAT_MIN_NORMAL);
    uint16_t stat = STAT_MIN_NORMAL;
    // IF_NZ goto not_hp;
    if(c == STAT_HP) {
        // LD_A_addr(wCurPartyLevel);
        // LD_B_A;
        // LDH_A_addr(hQuotient + 3);
        // ADD_A_B;
        // LDH_addr_A(hMultiplicand + 2);
        // IF_NC goto no_overflow_3;
        // LDH_A_addr(hQuotient + 2);
        // INC_A;
        // LDH_addr_A(hMultiplicand + 1);
        quot += wram->wCurPartyLevel;


    // no_overflow_3:
        // LD_A(STAT_MIN_HP);
        stat = STAT_MIN_HP;
    }

// not_hp:
    // LD_B_A;
    // LDH_A_addr(hQuotient + 3);
    // ADD_A_B;
    // LDH_addr_A(hMultiplicand + 2);
    // IF_NC goto no_overflow_4;
    // LDH_A_addr(hQuotient + 2);
    // INC_A;
    // LDH_addr_A(hMultiplicand + 1);
    quot += stat;


// no_overflow_4:
    // LDH_A_addr(hQuotient + 2);
    // CP_A(HIGH(MAX_STAT_VALUE + 1) + 1);
    // IF_NC goto max_stat;
    if(HIGH(quot) < HIGH(MAX_STAT_VALUE + 1) + 1) {
        // CP_A(HIGH(MAX_STAT_VALUE + 1));
        // IF_C goto stat_value_okay;
        // LDH_A_addr(hQuotient + 3);
        // CP_A(LOW(MAX_STAT_VALUE + 1));
        // IF_C goto stat_value_okay;
        if(HIGH(quot) < HIGH(MAX_STAT_VALUE + 1) || LOW(quot) < LOW(MAX_STAT_VALUE + 1)) {
            return quot;
        }
    }

// max_stat:
    // LD_A(HIGH(MAX_STAT_VALUE));
    // LDH_addr_A(hMultiplicand + 1);
    // LD_A(LOW(MAX_STAT_VALUE));
    // LDH_addr_A(hMultiplicand + 2);
    return MAX_STAT_VALUE;

// stat_value_okay:
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

void GivePoke(void){
    PUSH_DE;
    PUSH_BC;
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    CALL(aTryAddMonToParty);
    IF_NC goto failed;
    LD_HL(wPartyMonNicknames);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    POP_BC;
    LD_A_B;
    LD_B(0);
    PUSH_BC;
    PUSH_DE;
    PUSH_AF;
    LD_A_addr(wCurItem);
    AND_A_A;
    IF_Z goto done;
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A_addr(wCurItem);
    LD_hl_A;
    goto done;


failed:
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wTempEnemyMonSpecies);
    CALLFAR(aLoadEnemyMon);
    CALL(aSendMonIntoBox);
    JP_NC (mGivePoke_FailedToGiveMon);
    LD_A(BOXMON);
    LD_addr_A(wMonType);
    XOR_A_A;
    LD_addr_A(wCurPartyMon);
    LD_DE(wMonOrItemNameBuffer);
    POP_BC;
    LD_A_B;
    LD_B(1);
    PUSH_BC;
    PUSH_DE;
    PUSH_AF;
    LD_A_addr(wCurItem);
    AND_A_A;
    IF_Z goto done;
    LD_A_addr(wCurItem);
    LD_addr_A(sBoxMon1Item);


done:
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wNamedObjectIndex);
    LD_addr_A(wTempEnemyMonSpecies);
    CALL(aGetPokemonName);
    LD_HL(wStringBuffer1);
    LD_DE(wMonOrItemNameBuffer);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    POP_AF;
    AND_A_A;
    JP_Z (mGivePoke_wildmon);
    POP_DE;
    POP_BC;
    POP_HL;
    PUSH_BC;
    PUSH_HL;
    LD_A_addr(wScriptBank);
    CALL(aGetFarWord);
    LD_BC(MON_NAME_LENGTH);
    LD_A_addr(wScriptBank);
    CALL(aFarCopyBytes);
    POP_HL;
    INC_HL;
    INC_HL;
    LD_A_addr(wScriptBank);
    CALL(aGetFarWord);
    POP_BC;
    LD_A_B;
    AND_A_A;
    PUSH_DE;
    PUSH_BC;
    IF_NZ goto send_to_box;

    PUSH_HL;
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMonOTs);
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    POP_HL;

otnameloop:
    LD_A_addr(wScriptBank);
    CALL(aGetFarByte);
    LD_de_A;
    INC_HL;
    INC_DE;
    CP_A(0x50);
    IF_NZ goto otnameloop;
    LD_A_addr(wScriptBank);
    CALL(aGetFarByte);
    LD_B_A;
    PUSH_BC;
    LD_A_addr(wCurPartyMon);
    LD_HL(wPartyMon1ID);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A(HIGH(RANDY_OT_ID));
    LD_hli_A;
    LD_hl(LOW(RANDY_OT_ID));
    POP_BC;
    FARCALL(aSetGiftPartyMonCaughtData);
    goto skip_nickname;


send_to_box:
    LD_A(BANK(sBoxMonOTs));
    CALL(aOpenSRAM);
    LD_DE(sBoxMonOTs);

loop:
    LD_A_addr(wScriptBank);
    CALL(aGetFarByte);
    LD_de_A;
    INC_HL;
    INC_DE;
    CP_A(0x50);
    IF_NZ goto loop;
    LD_A_addr(wScriptBank);
    CALL(aGetFarByte);
    LD_B_A;
    LD_HL(sBoxMon1ID);
    CALL(aRandom);
    LD_hli_A;
    CALL(aRandom);
    LD_hl_A;
    CALL(aCloseSRAM);
    FARCALL(aSetGiftBoxMonCaughtData);
    goto skip_nickname;


wildmon:
    POP_DE;
    POP_BC;
    PUSH_BC;
    PUSH_DE;
    LD_A_B;
    AND_A_A;
    IF_Z goto party;
    FARCALL(aSetBoxMonCaughtData);
    goto set_caught_data;


party:
    FARCALL(aSetCaughtData);

set_caught_data:
    FARCALL(aGiveANickname_YesNo);
    POP_DE;
    IF_C goto skip_nickname;
    CALL(aInitNickname);


skip_nickname:
    POP_BC;
    POP_DE;
    LD_A_B;
    AND_A_A;
    RET_Z ;
    LD_HL(mWasSentToBillsPCText);
    CALL(aPrintText);
    LD_A(BANK(sBoxMonNicknames));
    CALL(aOpenSRAM);
    LD_HL(wMonOrItemNameBuffer);
    LD_DE(sBoxMonNicknames);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    LD_B(0x1);
    RET;


FailedToGiveMon:
    POP_BC;
    POP_DE;
    LD_B(0x2);
    RET;

}

void WasSentToBillsPCText(void){
    //text_far ['_WasSentToBillsPCText']
    //text_end ['?']

    return InitNickname();
}

void InitNickname(void){
    PUSH_DE;
    CALL(aLoadStandardMenuHeader);
    CALL(aDisableSpriteUpdates);
    POP_DE;
    PUSH_DE;
    LD_B(NAME_MON);
    FARCALL(aNamingScreen);
    POP_HL;
    LD_DE(wStringBuffer1);
    CALL(aInitName);
    LD_A(0x4);  // ExitAllMenus is in bank 0// maybe it used to be in bank 4
    LD_HL(mExitAllMenus);
    RST(aFarCall);
    RET;

}
