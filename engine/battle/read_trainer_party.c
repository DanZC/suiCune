#include "../../constants.h"
#include "read_trainer_party.h"
#include "../../home/sram.h"
#include "../../home/copy.h"
#include "../../data/trainers/parties.h"
#include "../../data/moves/moves.h"
#include "../pokemon/move_mon.h"

static void TrainerType1(const struct TrainerParty* de);
static void TrainerType2(const struct TrainerParty* de);
static void TrainerType3(const struct TrainerParty* de);
static void TrainerType4(const struct TrainerParty* de);

void ReadTrainerParty(void){
    PEEK("");
    // LD_A_addr(wInBattleTowerBattle);
    // BIT_A(0);
    // RET_NZ ;
    if(bit_test(wram->wInBattleTowerBattle, 0))
        return;

    PEEK("not in battle tower");
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wLinkMode != LINK_NULL)
        return;

    PEEK("not in link battle");
    // LD_HL(wOTPartyCount);
    // XOR_A_A;
    // LD_hli_A;
    // DEC_A;
    // LD_hl_A;
    wram->wOTPartyCount = 0;
    wram->wOTPartySpecies[0] = 0xff;

    // LD_HL(wOTPartyMons);
    // LD_BC(PARTYMON_STRUCT_LENGTH * PARTY_LENGTH);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(wram->wOTPartyMon, sizeof(wram->wOTPartyMon), 0);

    // LD_A_addr(wOtherTrainerClass);
    // CP_A(CAL);
    // IF_NZ goto not_cal2;
    // LD_A_addr(wOtherTrainerID);
    // CP_A(CAL2);
    // LD_A_addr(wOtherTrainerClass);
    printf("tclass %d, tid %d\n", wram->wOtherTrainerClass, wram->wOtherTrainerID);
    uint8_t tclass = wram->wOtherTrainerClass;
    if((tclass == CAL || tclass == JODI) && wram->wOtherTrainerID == CAL2) {
        // IF_Z goto cal2;
    // cal2:
        // LD_A(MBANK(asMysteryGiftTrainer));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asMysteryGiftTrainer));
        // LD_DE(sMysteryGiftTrainer);
        // CALL(aTrainerType2);
        // REG_DE = sMysteryGiftTrainer;
        // TrainerType2();
        struct TrainerPartyMoves* moves = GBToRAMAddr(sMysteryGiftTrainer);
        uint8_t size = 0;
        for(; size < 6 && moves[size].species != 0xff && moves[size].level != 0xff; size++) {}
        struct TrainerParty p = {.pmoves = moves, .size = size};
        TrainerType2(&p);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // goto done;
    }
    else {

    // not_cal2:

        // DEC_A;
        // LD_C_A;
        // LD_B(0);
        // LD_HL(mTrainerGroups);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        const struct TrainerParty * parties = TrainerGroups[tclass - 1].parties;

        // LD_A_addr(wOtherTrainerID);
        // LD_B_A;

    // skip_trainer:
        // DEC_B;
        // IF_Z goto got_trainer;

    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // IF_NZ goto loop;
        // goto skip_trainer;

    // got_trainer:
        const struct TrainerParty *de = &parties[wram->wOtherTrainerID - 1];


    // skip_name:
        // LD_A_hli;
        // CP_A(0x50);
        // IF_NZ goto skip_name;

        // LD_A_hli;
        // LD_C_A;
        // LD_B(0);
        // LD_D_H;
        // LD_E_L;
        // LD_HL(mTrainerTypes);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // LD_BC(mReadTrainerParty_done);
        // PUSH_BC;
        // JP_hl;
        switch(de->trainer_type)
        {
            case TRAINERTYPE_NORMAL: TrainerType1(de); break;
            case TRAINERTYPE_MOVES: TrainerType2(de); break;
            case TRAINERTYPE_ITEM: TrainerType3(de); break;
            case TRAINERTYPE_ITEM_MOVES: TrainerType4(de); break;
            default: printf("Bad trainer type %d.\n", de->trainer_type); break;
        }
    }
done:
    // JP(mComputeTrainerReward);
    ComputeTrainerReward();
    return;
}

//  entries correspond to TRAINERTYPE_* constants
// void (*const TrainerTypes[])(void) = {
    // [TRAINERTYPE_NORMAL] = TrainerType1,
    // [TRAINERTYPE_MOVES] = TrainerType2,
    // [TRAINERTYPE_ITEM] = TrainerType3,
    // [TRAINERTYPE_ITEM_MOVES] = TrainerType4,
// };

void TrainerType1(const struct TrainerParty* de){
//  normal (level, species)
    // LD_H_D;
    // LD_L_E;
    printf("Trainer type 1 (%d)\n", de->size);

    for(uint8_t i = 0; i < de->size; ++i) {
    // loop:
        // LD_A_hli;
        // CP_A(0xff);
        // RET_Z ;

        // LD_addr_A(wCurPartyLevel);
        wram->wCurPartyLevel = de->pnormal[i].level;
        printf("level=%d ", wram->wCurPartyLevel);
        // LD_A_hli;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = de->pnormal[i].species;
        printf("species=%d\n", wram->wCurPartySpecies);
        // LD_A(OTPARTYMON);
        // LD_addr_A(wMonType);
        wram->wMonType = OTPARTYMON;
        // PUSH_HL;
        // PREDEF(pTryAddMonToParty);
        TryAddMonToParty(de->pnormal[i].species, de->pnormal[i].level);
        // POP_HL;
        // goto loop;
    }

    // return TrainerType2();
}

void TrainerType2(const struct TrainerParty* de){
//  moves
    // LD_H_D;
    // LD_L_E;

    for(uint8_t i = 0; i < de->size; ++i) {
    // loop:
        // LD_A_hli;
        // CP_A(0xff);
        // RET_Z ;

        // LD_addr_A(wCurPartyLevel);
        wram->wCurPartyLevel = de->pmoves[i].level;
        // LD_A_hli;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = de->pmoves[i].species;
        // LD_A(OTPARTYMON);
        // LD_addr_A(wMonType);
        wram->wMonType = OTPARTYMON;

        // PUSH_HL;
        // PREDEF(pTryAddMonToParty);
        TryAddMonToParty(de->pmoves[i].species, de->pmoves[i].level);
        // LD_A_addr(wOTPartyCount);
        // DEC_A;
        // LD_HL(wOTPartyMon1Moves);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // LD_D_H;
        // LD_E_L;
        // POP_HL;

        for(uint8_t j = 0; j < NUM_MOVES; ++j) {
        // LD_B(NUM_MOVES);

        // copy_moves:
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            // DEC_B;
            // IF_NZ goto copy_moves;
            wram->wOTPartyMon[wram->wOTPartyCount - 1].mon.moves[j] = de->pmoves[i].moves[j];
        }

        // PUSH_HL;

        // LD_A_addr(wOTPartyCount);
        // DEC_A;
        // LD_HL(wOTPartyMon1Species);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // LD_D_H;
        // LD_E_L;
        // LD_HL(MON_PP);
        // ADD_HL_DE;
        // PUSH_HL;
        // LD_HL(MON_MOVES);
        // ADD_HL_DE;
        // POP_DE;

        // LD_B(NUM_MOVES);
        uint8_t j = 0;
        while(j < NUM_MOVES && de->pmoves[i].moves[j] != NO_MOVE) {
        // copy_pp:
            // LD_A_hli;
            // AND_A_A;
            // IF_Z goto copied_pp;

            // PUSH_HL;
            // PUSH_BC;
            // DEC_A;
            move_t a = de->pmoves[i].moves[j];
            // LD_HL(mMoves + MOVE_PP);
            // LD_BC(MOVE_LENGTH);
            // CALL(aAddNTimes);
            // LD_A(BANK(aMoves));
            // CALL(aGetFarByte);
            // POP_BC;
            // POP_HL;

            // LD_de_A;
            // INC_DE;
            // DEC_B;
            // IF_NZ goto copy_pp;
            wram->wOTPartyMon[wram->wOTPartyCount - 1].mon.PP[j] = Moves[a].pp;
            j++;
        }

    // copied_pp:

        // POP_HL;
        // goto loop;
    }
    // return TrainerType3();
}

//  item
void TrainerType3(const struct TrainerParty* de){
    // LD_H_D;
    // LD_L_E;

    for(uint8_t i = 0; i < de->size; ++i) {
    // loop:
        // LD_A_hli;
        // CP_A(0xff);
        // RET_Z ;

        // LD_addr_A(wCurPartyLevel);
        // LD_A_hli;
        wram->wCurPartyLevel = de->pitem[i].level;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = de->pitem[i].species;
        // LD_A(OTPARTYMON);
        // LD_addr_A(wMonType);
        wram->wMonType = OTPARTYMON;
        // PUSH_HL;
        // PREDEF(pTryAddMonToParty);
        TryAddMonToParty(de->pitem[i].species, de->pitem[i].level);
        // LD_A_addr(wOTPartyCount);
        // DEC_A;
        // LD_HL(wOTPartyMon1Item);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // LD_D_H;
        // LD_E_L;
        // POP_HL;
        // LD_A_hli;
        // LD_de_A;
        wram->wOTPartyMon[wram->wOTPartyCount - 1].mon.item = de->pitem[i].item;
        // goto loop;
    }

    // return TrainerType4();
}

void TrainerType4(const struct TrainerParty* de){
//  item + moves
    // LD_H_D;
    // LD_L_E;

    for(uint8_t i = 0; i < de->size; ++i) {
    // loop:
        // LD_A_hli;
        // CP_A(0xff);
        // RET_Z ;

        // LD_addr_A(wCurPartyLevel);
        // LD_A_hli;
        wram->wCurPartyLevel = de->pitemmoves[i].level;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = de->pitemmoves[i].species;

        // LD_A(OTPARTYMON);
        // LD_addr_A(wMonType);
        wram->wMonType = OTPARTYMON;

        // PUSH_HL;
        // PREDEF(pTryAddMonToParty);
        TryAddMonToParty(de->pitemmoves[i].species, de->pitemmoves[i].level);
        // LD_A_addr(wOTPartyCount);
        // DEC_A;
        // LD_HL(wOTPartyMon1Item);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // LD_D_H;
        // LD_E_L;
        // POP_HL;

        // LD_A_hli;
        // LD_de_A;
        wram->wOTPartyMon[wram->wOTPartyCount - 1].mon.item = de->pitemmoves[i].item;

        // PUSH_HL;
        // LD_A_addr(wOTPartyCount);
        // DEC_A;
        // LD_HL(wOTPartyMon1Moves);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // LD_D_H;
        // LD_E_L;
        // POP_HL;

        for(uint8_t j = 0; j < NUM_MOVES; ++j) {
        // LD_B(NUM_MOVES);

        // copy_moves:
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            // DEC_B;
            // IF_NZ goto copy_moves;
            wram->wOTPartyMon[wram->wOTPartyCount - 1].mon.moves[j] = de->pitemmoves[i].moves[j];
        }

        // PUSH_HL;

        // LD_A_addr(wOTPartyCount);
        // DEC_A;
        // LD_HL(wOTPartyMon1);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // LD_D_H;
        // LD_E_L;
        // LD_HL(MON_PP);
        // ADD_HL_DE;

        // PUSH_HL;
        // LD_HL(MON_MOVES);
        // ADD_HL_DE;
        // POP_DE;

        // LD_B(NUM_MOVES);

        uint8_t j = 0;
        while(j < NUM_MOVES && de->pitemmoves[i].moves[j] != NO_MOVE) {
        // copy_pp:
            // LD_A_hli;
            // AND_A_A;
            // IF_Z goto copied_pp;

            // PUSH_HL;
            // PUSH_BC;
            // DEC_A;
            move_t a = de->pitemmoves[i].moves[j];
            // LD_HL(mMoves + MOVE_PP);
            // LD_BC(MOVE_LENGTH);
            // CALL(aAddNTimes);
            // LD_A(BANK(aMoves));
            // CALL(aGetFarByte);
            // POP_BC;
            // POP_HL;

            // LD_de_A;
            // INC_DE;
            // DEC_B;
            // IF_NZ goto copy_pp;
            wram->wOTPartyMon[wram->wOTPartyCount - 1].mon.PP[j] = Moves[a].pp;
            j++;
        }

    // copied_pp:

        // POP_HL;
        // goto loop;
    }

    // return ComputeTrainerReward();
}

void ComputeTrainerReward(void){
    printf("Trainer reward: base %d, level %d\n", wram->wEnemyTrainerBaseReward, wram->wCurPartyLevel);
    // LD_HL(hProduct);
    // XOR_A_A;
    // LD_hli_A;
    // LD_hli_A;  // hMultiplicand + 0
    // LD_hli_A;  // hMultiplicand + 1
    // LD_A_addr(wEnemyTrainerBaseReward);
    // LD_hli_A;  // hMultiplicand + 2
    // LD_A_addr(wCurPartyLevel);
    // LD_hl_A;  // hMultiplier
    // CALL(aMultiply);
    uint32_t reward = wram->wEnemyTrainerBaseReward * wram->wCurPartyLevel;
    // LD_HL(wBattleReward);
    // XOR_A_A;
    // LD_hli_A;
    wram->wBattleReward[0] = HIGH(reward >> 8);
    // LDH_A_addr(hProduct + 2);
    // LD_hli_A;
    wram->wBattleReward[1] = HIGH(reward);
    // LDH_A_addr(hProduct + 3);
    // LD_hl_A;
    wram->wBattleReward[2] = LOW(reward);
    // RET;

}

uint8_t* Battle_GetTrainerName(void){
    // LD_A_addr(wInBattleTowerBattle);
    // BIT_A(0);
    // LD_HL(wOTPlayerName);
    // JP_NZ (mCopyTrainerName);
    if(bit_test(wram->wInBattleTowerBattle, 0))
        return CopyTrainerName(wram->wOTPlayerName);

    // LD_A_addr(wOtherTrainerID);
    // LD_B_A;
    uint8_t b = wram->wOtherTrainerID;
    // LD_A_addr(wOtherTrainerClass);
    // LD_C_A;
    uint8_t c = wram->wOtherTrainerClass;

    return GetTrainerName(b - 1, c);
}

uint8_t* GetTrainerName(uint8_t tid, uint8_t tclass){
    PEEK("");
    printf("GetTrainerName: class:%d, id:%d\n", tclass, tid);
    // LD_A_C;
    // CP_A(CAL);
    // IF_NZ goto not_cal2;
    if(tclass == CAL || tclass == JODI) {
        // LD_A(MBANK(asMysteryGiftTrainerHouseFlag));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asMysteryGiftTrainerHouseFlag));
        // LD_A_addr(sMysteryGiftTrainerHouseFlag);
        // AND_A_A;
        uint8_t flag = gb_read(sMysteryGiftTrainerHouseFlag);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // IF_Z goto not_cal2;
        if(flag != 0) {
            // LD_A(BANK(asMysteryGiftPartnerName));
            // CALL(aOpenSRAM);
            OpenSRAM(MBANK(asMysteryGiftPartnerName));
            // LD_HL(sMysteryGiftPartnerName);
            // CALL(aCopyTrainerName);
            // JP(mCloseSRAM);
            uint8_t* name = CopyTrainerName(GBToRAMAddr(sMysteryGiftPartnerName));
            CloseSRAM();
            return name;
        }
    }

// not_cal2:
    // bank_push(BANK(aTrainerGroups));
    // REG_C = tclass;
    // REG_B = tid;
    // DEC_C;
    // PUSH_BC;
    // LD_B(0);
    // LD_HL(mTrainerGroups);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // POP_BC;


// loop:
    // DEC_B;
    // JR_Z (mCopyTrainerName);
    // while(--REG_B != 0) {


    // skip:
        // do {
        //     // LD_A_hli;
        //     // CP_A(0xff);
        //     // IF_NZ goto skip;
        // } while(gb_read(REG_HL++) != 0xff);
        // goto loop;
    // }

    // CopyTrainerName(GBToRAMAddr(REG_HL));
    CopyTrainerName(U82C(TrainerGroups[tclass - 1].parties[tid].name));

    // POP_HL;
    // POP_DE;
    // POP_BC;
    // POP_AF;
    // bank_pop;
    // return CopyTrainerName();
    return wram->wStringBuffer1;
}

uint8_t* CopyTrainerName(const uint8_t* hl){
    // LD_DE(wStringBuffer1);
    // PUSH_DE;
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wStringBuffer1, hl, NAME_LENGTH);
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
