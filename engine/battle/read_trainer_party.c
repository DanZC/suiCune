#include "../../constants.h"
#include "read_trainer_party.h"
#include "../../home/sram.h"
#include "../../home/copy.h"

void ReadTrainerParty(void){
    PEEK("");
    LD_A_addr(wInBattleTowerBattle);
    BIT_A(0);
    RET_NZ ;

    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;

    LD_HL(wOTPartyCount);
    XOR_A_A;
    LD_hli_A;
    DEC_A;
    LD_hl_A;

    LD_HL(wOTPartyMons);
    LD_BC(PARTYMON_STRUCT_LENGTH * PARTY_LENGTH);
    XOR_A_A;
    CALL(aByteFill);

    LD_A_addr(wOtherTrainerClass);
    CP_A(CAL);
    IF_NZ goto not_cal2;
    LD_A_addr(wOtherTrainerID);
    CP_A(CAL2);
    IF_Z goto cal2;
    LD_A_addr(wOtherTrainerClass);

not_cal2:

    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(mTrainerGroups);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    LD_A_addr(wOtherTrainerID);
    LD_B_A;

skip_trainer:
    DEC_B;
    IF_Z goto got_trainer;

loop:
    LD_A_hli;
    CP_A(-1);
    IF_NZ goto loop;
    goto skip_trainer;

got_trainer:


skip_name:
    LD_A_hli;
    CP_A(0x50);
    IF_NZ goto skip_name;

    LD_A_hli;
    LD_C_A;
    LD_B(0);
    LD_D_H;
    LD_E_L;
    // LD_HL(mTrainerTypes);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_BC(mReadTrainerParty_done);
    // PUSH_BC;
    // JP_hl;
    switch(REG_BC)
    {
        case TRAINERTYPE_NORMAL: CALL(aTrainerType1); break;
        case TRAINERTYPE_MOVES: CALL(aTrainerType2); break;
        case TRAINERTYPE_ITEM: CALL(aTrainerType3); break;
        case TRAINERTYPE_ITEM_MOVES: CALL(aTrainerType4); break;
    }


done:
    // JP(mComputeTrainerReward);
    return ComputeTrainerReward();


cal2:
    LD_A(MBANK(asMysteryGiftTrainer));
    CALL(aOpenSRAM);
    LD_DE(sMysteryGiftTrainer);
    CALL(aTrainerType2);
    CALL(aCloseSRAM);
    goto done;
}

// void TrainerTypes(void){
    //dw ['TrainerType1'];  // level, species
    //dw ['TrainerType2'];  // level, species, moves
    //dw ['TrainerType3'];  // level, species, item
    //dw ['TrainerType4'];  // level, species, item, moves

    // return TrainerType1();
// }

//  entries correspond to TRAINERTYPE_* constants
void (*const TrainerTypes[])(void) = {
    [TRAINERTYPE_NORMAL] = TrainerType1,
    [TRAINERTYPE_MOVES] = TrainerType2,
    [TRAINERTYPE_ITEM] = TrainerType3,
    [TRAINERTYPE_ITEM_MOVES] = TrainerType4,
};

void TrainerType1(void){
//  normal (level, species)
    LD_H_D;
    LD_L_E;

loop:
    LD_A_hli;
    CP_A(0xff);
    RET_Z ;

    LD_addr_A(wCurPartyLevel);
    LD_A_hli;
    LD_addr_A(wCurPartySpecies);
    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);
    PUSH_HL;
    PREDEF(pTryAddMonToParty);
    POP_HL;
    goto loop;

    return TrainerType2();
}

void TrainerType2(void){
//  moves
    LD_H_D;
    LD_L_E;

loop:
    LD_A_hli;
    CP_A(0xff);
    RET_Z ;

    LD_addr_A(wCurPartyLevel);
    LD_A_hli;
    LD_addr_A(wCurPartySpecies);
    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);

    PUSH_HL;
    PREDEF(pTryAddMonToParty);
    LD_A_addr(wOTPartyCount);
    DEC_A;
    LD_HL(wOTPartyMon1Moves);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    POP_HL;

    LD_B(NUM_MOVES);

copy_moves:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto copy_moves;

    PUSH_HL;

    LD_A_addr(wOTPartyCount);
    DEC_A;
    LD_HL(wOTPartyMon1Species);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_HL(MON_PP);
    ADD_HL_DE;
    PUSH_HL;
    LD_HL(MON_MOVES);
    ADD_HL_DE;
    POP_DE;

    LD_B(NUM_MOVES);

copy_pp:
    LD_A_hli;
    AND_A_A;
    IF_Z goto copied_pp;

    PUSH_HL;
    PUSH_BC;
    DEC_A;
    LD_HL(mMoves + MOVE_PP);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aMoves));
    CALL(aGetFarByte);
    POP_BC;
    POP_HL;

    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto copy_pp;

copied_pp:

    POP_HL;
    goto loop;

    return TrainerType3();
}

void TrainerType3(void){
//  item
    LD_H_D;
    LD_L_E;

loop:
    LD_A_hli;
    CP_A(0xff);
    RET_Z ;

    LD_addr_A(wCurPartyLevel);
    LD_A_hli;
    LD_addr_A(wCurPartySpecies);
    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);
    PUSH_HL;
    PREDEF(pTryAddMonToParty);
    LD_A_addr(wOTPartyCount);
    DEC_A;
    LD_HL(wOTPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_A_hli;
    LD_de_A;
    goto loop;

    return TrainerType4();
}

void TrainerType4(void){
//  item + moves
    LD_H_D;
    LD_L_E;

loop:
    LD_A_hli;
    CP_A(0xff);
    RET_Z ;

    LD_addr_A(wCurPartyLevel);
    LD_A_hli;
    LD_addr_A(wCurPartySpecies);

    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);

    PUSH_HL;
    PREDEF(pTryAddMonToParty);
    LD_A_addr(wOTPartyCount);
    DEC_A;
    LD_HL(wOTPartyMon1Item);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    POP_HL;

    LD_A_hli;
    LD_de_A;

    PUSH_HL;
    LD_A_addr(wOTPartyCount);
    DEC_A;
    LD_HL(wOTPartyMon1Moves);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    POP_HL;

    LD_B(NUM_MOVES);

copy_moves:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto copy_moves;

    PUSH_HL;

    LD_A_addr(wOTPartyCount);
    DEC_A;
    LD_HL(wOTPartyMon1);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_HL(MON_PP);
    ADD_HL_DE;

    PUSH_HL;
    LD_HL(MON_MOVES);
    ADD_HL_DE;
    POP_DE;

    LD_B(NUM_MOVES);

copy_pp:
    LD_A_hli;
    AND_A_A;
    IF_Z goto copied_pp;

    PUSH_HL;
    PUSH_BC;
    DEC_A;
    LD_HL(mMoves + MOVE_PP);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aMoves));
    CALL(aGetFarByte);
    POP_BC;
    POP_HL;

    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto copy_pp;

copied_pp:

    POP_HL;
    goto loop;

    return ComputeTrainerReward();
}

void ComputeTrainerReward(void){
    LD_HL(hProduct);
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;  // hMultiplicand + 0
    LD_hli_A;  // hMultiplicand + 1
    LD_A_addr(wEnemyTrainerBaseReward);
    LD_hli_A;  // hMultiplicand + 2
    LD_A_addr(wCurPartyLevel);
    LD_hl_A;  // hMultiplier
    CALL(aMultiply);
    LD_HL(wBattleReward);
    XOR_A_A;
    LD_hli_A;
    LDH_A_addr(hProduct + 2);
    LD_hli_A;
    LDH_A_addr(hProduct + 3);
    LD_hl_A;
    RET;

}

void Battle_GetTrainerName(void){
    LD_A_addr(wInBattleTowerBattle);
    BIT_A(0);
    LD_HL(wOTPlayerName);
    JP_NZ (mCopyTrainerName);

    LD_A_addr(wOtherTrainerID);
    LD_B_A;
    LD_A_addr(wOtherTrainerClass);
    LD_C_A;

    return GetTrainerName();
}

uint8_t* Battle_GetTrainerName_Conv(void){
    // LD_A_addr(wInBattleTowerBattle);
    // BIT_A(0);
    // LD_HL(wOTPlayerName);
    // JP_NZ (mCopyTrainerName);
    if(bit_test(wram->wInBattleTowerBattle, 0))
        return CopyTrainerName_Conv(wram->wOTPlayerName);

    // LD_A_addr(wOtherTrainerID);
    // LD_B_A;
    uint8_t b = wram->wOtherTrainerID;
    // LD_A_addr(wOtherTrainerClass);
    // LD_C_A;
    uint8_t c = wram->wOtherTrainerClass;

    return GetTrainerName_Conv(b, c);
}

void GetTrainerName(void){
    LD_A_C;
    CP_A(CAL);
    IF_NZ goto not_cal2;

    LD_A(BANK(asMysteryGiftTrainerHouseFlag));
    CALL(aOpenSRAM);
    LD_A_addr(sMysteryGiftTrainerHouseFlag);
    AND_A_A;
    CALL(aCloseSRAM);
    IF_Z goto not_cal2;

    LD_A(BANK(asMysteryGiftPartnerName));
    CALL(aOpenSRAM);
    LD_HL(sMysteryGiftPartnerName);
    CALL(aCopyTrainerName);
    JP(mCloseSRAM);


not_cal2:
    DEC_C;
    PUSH_BC;
    LD_B(0);
    LD_HL(mTrainerGroups);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_BC;


loop:
    DEC_B;
    JR_Z (mCopyTrainerName);


skip:
    LD_A_hli;
    CP_A(0xff);
    IF_NZ goto skip;
    goto loop;

    return CopyTrainerName();
}

uint8_t* GetTrainerName_Conv(uint8_t tid, uint8_t tclass){
    // LD_A_C;
    // CP_A(CAL);
    // IF_NZ goto not_cal2;
    if(tclass == CAL) {

        // LD_A(MBANK(asMysteryGiftTrainerHouseFlag));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(asMysteryGiftTrainerHouseFlag));
        // LD_A_addr(sMysteryGiftTrainerHouseFlag);
        // AND_A_A;
        uint8_t flag = gb_read(sMysteryGiftTrainerHouseFlag);
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
        // IF_Z goto not_cal2;
        if(flag != 0) {

            // LD_A(BANK(asMysteryGiftPartnerName));
            // CALL(aOpenSRAM);
            OpenSRAM_Conv(MBANK(asMysteryGiftPartnerName));
            // LD_HL(sMysteryGiftPartnerName);
            // CALL(aCopyTrainerName);
            // JP(mCloseSRAM);
            uint8_t* name = CopyTrainerName_Conv(GBToRAMAddr(sMysteryGiftPartnerName));
            CloseSRAM_Conv();
            return name;
        }
    }
    PUSH_AF;
    PUSH_BC; 
    PUSH_DE;
    PUSH_HL;


// not_cal2:
    bank_push(BANK(aTrainerGroups));
    REG_C = tclass;
    REG_B = tid;
    DEC_C;
    PUSH_BC;
    LD_B(0);
    LD_HL(mTrainerGroups);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_BC;


// loop:
    // DEC_B;
    // JR_Z (mCopyTrainerName);
    while(--REG_B != 0) {


    // skip:
        do {
            // LD_A_hli;
            // CP_A(0xff);
            // IF_NZ goto skip;
        } while(gb_read(REG_HL++) != 0xff);
        // goto loop;
    }

    CopyTrainerName_Conv(GBToRAMAddr(REG_HL));

    POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
    bank_pop;
    // return CopyTrainerName();
    return wram->wStringBuffer1;
}

void CopyTrainerName(void){
    LD_DE(wStringBuffer1);
    PUSH_DE;
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    POP_DE;
    RET;

}

uint8_t* CopyTrainerName_Conv(const uint8_t* hl){
    // LD_DE(wStringBuffer1);
    // PUSH_DE;
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wStringBuffer1, hl, NAME_LENGTH);
    // POP_DE;
    // RET;
    return wram->wStringBuffer1;
}

void IncompleteCopyNameFunction(void){
//  //  unreferenced
//  Copy of CopyTrainerName but without "call CopyBytes"
    LD_DE(wStringBuffer1);
    PUSH_DE;
    LD_BC(NAME_LENGTH);
    POP_DE;
    RET;

// INCLUDE "data/trainers/parties.asm"

}
