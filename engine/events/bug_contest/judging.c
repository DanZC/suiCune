#include "../../../constants.h"
#include "judging.h"
#include "contest_2.h"
#include "../../../mobile/mobile_41.h"
#include "../../battle/read_trainer_attributes.h"
#include "../../battle/read_trainer_party.h"
#include "../../../home/audio.h"
#include "../../../home/copy.h"
#include "../../../home/compare.h"
#include "../../../home/names.h"
#include "../../../home/text.h"
#include "../../../home/random.h"
#include "../../../data/text/common.h"
#include "../../../data/events/bug_contest_winners.h"

uint8_t v_BugContestJudging(void){
    // CALL(aContestScore);
    uint16_t score = ContestScore();
    // FARCALL(aStubbedTrainerRankings_BugContestScore);
    StubbedTrainerRankings_BugContestScore(score);
    // CALL(aBugContest_JudgeContestants);
    BugContest_JudgeContestants(score);
    // LD_A_addr(wBugContestThirdPlaceWinnerID);
    // CALL(aLoadContestantName);
    LoadContestantName(wram->wBugContestWinners[2].winnerID);
    // LD_A_addr(wBugContestThirdPlaceMon);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wBugContestWinners[2].mon);
    // LD_HL(mContestJudging_ThirdPlaceText);
    // CALL(aPrintText);
    PrintText(ContestJudging_ThirdPlaceText);
    // LD_A_addr(wBugContestSecondPlaceWinnerID);
    // CALL(aLoadContestantName);
    LoadContestantName(wram->wBugContestWinners[1].winnerID);
    // LD_A_addr(wBugContestSecondPlaceMon);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wBugContestWinners[1].mon);
    // LD_HL(mContestJudging_SecondPlaceText);
    // CALL(aPrintText);
    PrintText(ContestJudging_SecondPlaceText);
    // LD_A_addr(wBugContestFirstPlaceWinnerID);
    // CALL(aLoadContestantName);
    LoadContestantName(wram->wBugContestWinners[0].winnerID);
    // LD_A_addr(wBugContestFirstPlaceMon);
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName(wram->wBugContestWinners[0].mon);
    // LD_HL(mContestJudging_FirstPlaceText);
    // CALL(aPrintText);
    PrintText(ContestJudging_FirstPlaceText);
    // JP(mBugContest_GetPlayersResult);
    return BugContest_GetPlayersResult();
}

static void ConstestJudging_FirstPlaceText_Function(struct TextCmdState* state);
const txt_cmd_s ContestJudging_FirstPlaceText[] = {
    text_far(v_ContestJudging_FirstPlaceText)
    text_asm(ConstestJudging_FirstPlaceText_Function)
};

const txt_cmd_s ContestJudging_FirstPlaceScoreText[] = {
    text_far(v_ContestJudging_FirstPlaceScoreText)
    text_end
};

static void ConstestJudging_FirstPlaceText_Function(struct TextCmdState* state) {
    // LD_DE(SFX_1ST_PLACE);
    // CALL(aPlaySFX);
    PlaySFX(SFX_1ST_PLACE);
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_HL(mContestJudging_FirstPlaceScoreText);
    state->hl = ContestJudging_FirstPlaceScoreText;
    // RET;
}

static void ContestJudging_SecondPlaceText_Function(struct TextCmdState* state);
// Placing second was @ , who caught a @ !@ @
const txt_cmd_s ContestJudging_SecondPlaceText[] = {
    text_far(v_ContestJudging_SecondPlaceText)
    text_asm(ContestJudging_SecondPlaceText_Function)
};

const txt_cmd_s ContestJudging_SecondPlaceScoreText[] = {
    text_far(v_ContestJudging_SecondPlaceScoreText)
    text_end
};

static void ContestJudging_SecondPlaceText_Function(struct TextCmdState* state){
    // LD_DE(SFX_2ND_PLACE);
    // CALL(aPlaySFX);
    PlaySFX(SFX_2ND_PLACE);
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_HL(mContestJudging_SecondPlaceScoreText);
    state->hl = ContestJudging_SecondPlaceScoreText;
    // RET;
}

static void ContestJudging_ThirdPlaceText_Function(struct TextCmdState* state);
// Placing third was @ , who caught a @ !@ @
const txt_cmd_s ContestJudging_ThirdPlaceText[] = {
    text_far(v_ContestJudging_ThirdPlaceText)
    text_asm(ContestJudging_ThirdPlaceText_Function)
};

const txt_cmd_s ContestJudging_ThirdPlaceScoreText[] = {
    text_far(v_ContestJudging_ThirdPlaceScoreText)
    text_end
};

static void ContestJudging_ThirdPlaceText_Function(struct TextCmdState* state) {
    // LD_DE(SFX_3RD_PLACE);
    // CALL(aPlaySFX);
    PlaySFX(SFX_3RD_PLACE);
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_HL(mContestJudging_ThirdPlaceScoreText);
    state->hl = ContestJudging_ThirdPlaceScoreText;
    // RET;
}

void LoadContestantName(uint8_t a){
//  If a = 1, get your name.
    //assert ['BUG_CONTEST_PLAYER == 1'];
    // DEC_A;
    // IF_Z goto player;
    if(a == 1) {
    // player:
        // LD_HL(wPlayerName);
        // LD_DE(wBugContestWinnerName);
        // LD_BC(NAME_LENGTH);
        // JP(mCopyBytes);
        return CopyBytes(wram->wBugContestWinnerName, wram->wPlayerName, NAME_LENGTH);
    }
//  Find the pointer for the trainer class of the Bug Catching Contestant whose ID is in a.
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mBugContestantPointers);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    const struct BugContestant* contestant = BugContestantPointers[a];
//  Copy the Trainer Class to c.
    // LD_A_hli;
    // LD_C_A;
//  Save hl and bc for later.
    // PUSH_HL;
    // PUSH_BC;
//  Get the Trainer Class name and copy it into wBugContestWinnerName.
    // CALLFAR(aGetTrainerClassName);
    // LD_HL(wStringBuffer1);
    // LD_DE(wBugContestWinnerName);
    // LD_BC(TRAINER_CLASS_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBugContestWinnerName, GetTrainerClassName_Conv(contestant->tclass), TRAINER_CLASS_NAME_LENGTH);
    // LD_HL(wBugContestWinnerName);
    uint8_t* hl = wram->wBugContestWinnerName;
//  Delete the trailing terminator and replace it with a space.

    while(*hl != 0x50) {
    // next:
        // LD_A_hli;
        // CP_A(0x50);
        // IF_NZ goto next;
        hl++;
    }
    // DEC_HL;
    // LD_hl(0x7f);
    *hl = 0x7f;
    // INC_HL;
    hl++;
    // LD_D_H;
    // LD_E_L;
//  Restore the Trainer Class ID and Trainer ID pointer.  Save de for later.
    // POP_BC;
    // POP_HL;
    // PUSH_DE;
//  Get the name of the trainer with class c and ID b.
    // LD_A_hl;
    // LD_B_A;
    // CALLFAR(aGetTrainerName);
//  Append the name to wBugContestWinnerName.
    // LD_HL(wStringBuffer1);
    // POP_DE;
    // LD_BC(NAME_LENGTH - 1);
    // JP(mCopyBytes);

    return CopyBytes(hl, GetTrainerName_Conv(contestant->tid, contestant->tclass), NAME_LENGTH - 1);
// INCLUDE "data/events/bug_contest_winners.asm"
}

uint8_t BugContest_GetPlayersResult(void){
    // LD_HL(wBugContestThirdPlaceWinnerID);
    // LD_DE(-BUG_CONTESTANT_SIZE);
    // LD_B(3);  // 3rd, 2nd, or 1st
    uint8_t b = 3;

    do {
    // loop:
        // LD_A_hl;
        // CP_A(BUG_CONTEST_PLAYER);
        // IF_Z goto done;
        if(wram->wBugContestWinners[b-1].winnerID == BUG_CONTEST_PLAYER)
            break;
        // ADD_HL_DE;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);


// done:
    // RET;
    return b;
}

void BugContest_JudgeContestants(uint16_t playerScore){
    // CALL(aClearContestResults);
    ClearContestResults();
    // CALL(aComputeAIContestantScores);
    ComputeAIContestantScores();
    // LD_HL(wBugContestTempWinnerID);
    // LD_A(BUG_CONTEST_PLAYER);
    // LD_hli_A;
    wram->wBugContestTemp.winnerID = BUG_CONTEST_PLAYER;
    // LD_A_addr(wContestMon);
    // LD_hli_A;
    wram->wBugContestTemp.mon = wram->wContestMon.mon.species;
    // LDH_A_addr(hProduct);
    // LD_hli_A;
    // LDH_A_addr(hProduct + 1);
    // LD_hl_A;
    wram->wBugContestTemp.score = NativeToBigEndian16(playerScore);
    // CALL(aDetermineContestWinners);
    DetermineContestWinners();
    // RET;
}

void ClearContestResults(void){
    // LD_HL(wBugContestResults);
    // LD_B(wBugContestWinnersEnd - wBugContestResults);
    // XOR_A_A;

// loop:
    // LD_hli_A;
    // DEC_B;
    // IF_NZ goto loop;
    ByteFill(wram->wBugContestWinners, sizeof(wram->wBugContestWinners), 0);
    // RET;

}

void DetermineContestWinners(void){
    // LD_DE(wBugContestTempScore);
    // LD_HL(wBugContestFirstPlaceScore);
    // LD_C(2);
    // CALL(aCompareBytes);
    // IF_C goto not_first_place;
    if(BigEndianToNative16(wram->wBugContestTemp.score) >= BigEndianToNative16(wram->wBugContestWinners[0].score)) {
        // LD_HL(wBugContestSecondPlaceWinnerID);
        // LD_DE(wBugContestThirdPlaceWinnerID);
        // LD_BC(BUG_CONTESTANT_SIZE);
        // CALL(aCopyBytes);
        CopyBytes(wram->wBugContestWinners + 2, wram->wBugContestWinners + 1, BUG_CONTESTANT_SIZE);
        // LD_HL(wBugContestFirstPlaceWinnerID);
        // LD_DE(wBugContestSecondPlaceWinnerID);
        // LD_BC(BUG_CONTESTANT_SIZE);
        // CALL(aCopyBytes);
        CopyBytes(wram->wBugContestWinners + 1, wram->wBugContestWinners + 0, BUG_CONTESTANT_SIZE);
        // LD_HL(wBugContestFirstPlaceWinnerID);
        // CALL(aCopyTempContestant);
        CopyTempContestant(wram->wBugContestWinners + 0);
        // goto done;
    }

// not_first_place:
    // LD_DE(wBugContestTempScore);
    // LD_HL(wBugContestSecondPlaceScore);
    // LD_C(2);
    // CALL(aCompareBytes);
    // IF_C goto not_second_place;
    else if(BigEndianToNative16(wram->wBugContestTemp.score) >= BigEndianToNative16(wram->wBugContestWinners[1].score)) {
        // LD_HL(wBugContestSecondPlaceWinnerID);
        // LD_DE(wBugContestThirdPlaceWinnerID);
        // LD_BC(BUG_CONTESTANT_SIZE);
        // CALL(aCopyBytes);
        CopyBytes(wram->wBugContestWinners + 2, wram->wBugContestWinners + 1, BUG_CONTESTANT_SIZE);
        // LD_HL(wBugContestSecondPlaceWinnerID);
        // CALL(aCopyTempContestant);
        CopyTempContestant(wram->wBugContestWinners + 1);
        // goto done;
    }

// not_second_place:
    // LD_DE(wBugContestTempScore);
    // LD_HL(wBugContestThirdPlaceScore);
    // LD_C(2);
    // CALL(aCompareBytes);
    // IF_C goto done;
    else if(BigEndianToNative16(wram->wBugContestTemp.score) >= BigEndianToNative16(wram->wBugContestWinners[2].score)) {
        // LD_HL(wBugContestThirdPlaceWinnerID);
        // CALL(aCopyTempContestant);
        CopyTempContestant(wram->wBugContestWinners + 2);
    }

// done:
    // RET;

}

void CopyTempContestant(struct BugContestWinner *hl){
//  Could've just called CopyBytes.
    // LD_DE(wBugContestTempWinnerID);
    // for(int rept = 0; rept < BUG_CONTESTANT_SIZE - 1; rept++){
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;
    // }
    // LD_A_de;
    // INC_DE;
    // LD_hl_A;
    // RET;
    CopyBytes(hl, &wram->wBugContestTemp, sizeof(*hl));
}

void ComputeAIContestantScores(void){
    // LD_E(0);
    uint8_t e = 0;

    do {
    // loop:
        // PUSH_DE;
        // CALL(aCheckBugContestContestantFlag);
        // POP_DE;
        // IF_NZ goto done;
        if(CheckBugContestContestantFlag(e) != 0)
            continue;
        // LD_A_E;
        // INC_A;
        // INC_A;
        // LD_addr_A(wBugContestTempWinnerID);
        wram->wBugContestTemp.winnerID = e + 2;
        // DEC_A;
        // LD_C_A;
        // LD_B(0);
        // LD_HL(mBugContestantPointers);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        const struct BugContestant* contestant = BugContestantPointers[e + 1];
        // INC_HL;
        // INC_HL;
        const struct BugPlaceMon* mon = contestant->place;

        uint8_t a;
        do {
        // loop2:
        // 0, 1, or 2 for 1st, 2nd, or 3rd
            // CALL(aRandom);
            a = Random() & 3;
            // AND_A(3);
            // CP_A(3);
            // IF_Z goto loop2;
        } while(a == 3);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_addr_A(wBugContestTempMon);
        wram->wBugContestTemp.mon = mon[a].mon;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        uint16_t score = mon[a].score;
    // randomly perturb score
        // CALL(aRandom);
        // AND_A(0b111);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        score += Random() & 0b111;
        // LD_A_H;
        // LD_addr_A(wBugContestTempScore);
        // LD_A_L;
        // LD_addr_A(wBugContestTempScore + 1);
        wram->wBugContestTemp.score = NativeToBigEndian16(score);
        // PUSH_DE;
        // CALL(aDetermineContestWinners);
        DetermineContestWinners();
        // POP_DE;

    // done:
        // INC_E;
        // LD_A_E;
        // CP_A(NUM_BUG_CONTESTANTS);
        // IF_NZ goto loop;
    } while(++e != NUM_BUG_CONTESTANTS);
    // RET;
}

// static uint16_t ContestScore_AddContestStat(uint16_t score, uint8_t a) {
    // LD_HL(hMultiplicand);
    // ADD_A_hl;
    // LD_hl_A;
    // RET_NC ;
    // DEC_HL;
    // INC_hl;
    // RET;
    // return score + a;
// }

//  Determine the player's score in the Bug Catching Contest.
uint16_t ContestScore(void){
    // XOR_A_A;
    // LDH_addr_A(hProduct);
    // LDH_addr_A(hMultiplicand);
    uint16_t score = 0;

    // LD_A_addr(wContestMonSpecies);  // Species
    // AND_A_A;
    // IF_Z goto done;
    if(wram->wContestMon.mon.species == 0)
        return score;

// Tally the following:

// Max HP * 4
    // LD_A_addr(wContestMonMaxHP + 1);
    // CALL(aContestScore_AddContestStat);
    // LD_A_addr(wContestMonMaxHP + 1);
    // CALL(aContestScore_AddContestStat);
    // LD_A_addr(wContestMonMaxHP + 1);
    // CALL(aContestScore_AddContestStat);
    // LD_A_addr(wContestMonMaxHP + 1);
    // CALL(aContestScore_AddContestStat);
    score += (BigEndianToNative16(wram->wContestMon.maxHP) & 0xff) * 4;

// Stats
    // LD_A_addr(wContestMonAttack + 1);
    // CALL(aContestScore_AddContestStat);
    score += BigEndianToNative16(wram->wContestMon.attack) & 0xff;
    // LD_A_addr(wContestMonDefense + 1);
    // CALL(aContestScore_AddContestStat);
    score += BigEndianToNative16(wram->wContestMon.defense) & 0xff;
    // LD_A_addr(wContestMonSpeed + 1);
    // CALL(aContestScore_AddContestStat);
    score += BigEndianToNative16(wram->wContestMon.speed) & 0xff;
    // LD_A_addr(wContestMonSpclAtk + 1);
    // CALL(aContestScore_AddContestStat);
    score += BigEndianToNative16(wram->wContestMon.spclAtk) & 0xff;
    // LD_A_addr(wContestMonSpclDef + 1);
    // CALL(aContestScore_AddContestStat);
    score += BigEndianToNative16(wram->wContestMon.spclDef) & 0xff;

// DVs
    // LD_A_addr(wContestMonDVs + 0);
    // LD_B_A;
    // AND_A(0b0010);
    // ADD_A_A;
    // ADD_A_A;
    // LD_C_A;

    // SWAP_B;
    // LD_A_B;
    // AND_A(0b0010);
    // ADD_A_A;
    // ADD_A_C;
    // LD_D_A;
    uint8_t d = (((wram->wContestMon.mon.DVs >> 4) & 0b0010) << 1) + ((wram->wContestMon.mon.DVs & 0b0010) << 2);

    // LD_A_addr(wContestMonDVs + 1);
    // LD_B_A;
    // AND_A(0b0010);
    // LD_C_A;

    // SWAP_B;
    // LD_A_B;
    // AND_A(0b0010);
    // SRL_A;
    // ADD_A_C;
    // ADD_A_C;
    // ADD_A_D;
    uint8_t a = ((wram->wContestMon.mon.DVs >> 8) & 0b0010) + (((wram->wContestMon.mon.DVs >> 12) & 0b0010) >> 1) + d;
    // ADD_A_D;

    // CALL(aContestScore_AddContestStat);
    score += a;

// Remaining HP / 8
    // LD_A_addr(wContestMonHP + 1);
    // SRL_A;
    // SRL_A;
    // SRL_A;
    // CALL(aContestScore_AddContestStat);
    score += (BigEndianToNative16(wram->wContestMon.HP) & 0xff) >> 3;

// Whether it's holding an item
    // LD_A_addr(wContestMonItem);
    // AND_A_A;
    // IF_Z goto done;

    // LD_A(1);
    // CALL(aContestScore_AddContestStat);
    if(wram->wContestMon.mon.item != NO_ITEM) 
        score += 1;


// done:
    // RET;
    return score;
}
