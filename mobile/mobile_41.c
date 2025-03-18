#include "../constants.h"
#include "mobile_41.h"
#include "../home/copy.h"
#include "../home/sram.h"
#include "../home/mobile.h"
#include "../engine/gfx/load_font.h"
#include "../gfx/font.h"

//  These functions deal with miscellaneous statistics
//  which were used for Trainer Rankings in Pokémon News.

//  Copies certain values at the time the player enters the Hall of Fame.
void StubbedTrainerRankings_HallOfFame2(void){
    // RET;
    // LD_A(BANK(sTrainerRankingGameTimeHOF));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asTrainerRankingGameTimeHOF));

    // LD_HL(wGameTimeHours);
    // LD_DE(sTrainerRankingGameTimeHOF);
    uint8_t* time = GBToRAMAddr(sTrainerRankingGameTimeHOF);
    // LD_BC(4);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(time, &wram->wGameTimeHours, 2);
    time[2] = wram->wGameTimeMinutes;
    time[3] = wram->wGameTimeSeconds;

    // LD_HL(sTrainerRankingStepCount);
    // LD_DE(sTrainerRankingStepCountHOF);
    // LD_BC(4);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(GBToRAMAddr(sTrainerRankingStepCountHOF), GBToRAMAddr(sTrainerRankingStepCount), 4);

// sTrainerRankingHealings is only a 3-byte value.
// One extraneous byte is copied from sTrainerRankingMysteryGift.
#if BUGFIX_HALLOFFAME_RANKING_HEALINGS
    CopyBytes_Conv2(GBToRAMAddr(sTrainerRankingHealingsHOF), GBToRAMAddr(sTrainerRankingHealings), 3);
#else
    // LD_HL(sTrainerRankingHealings);
    // LD_DE(sTrainerRankingHealingsHOF);
    // LD_BC(4);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(GBToRAMAddr(sTrainerRankingHealingsHOF), GBToRAMAddr(sTrainerRankingHealings), 4);
#endif

    // LD_HL(sTrainerRankingBattles);
    // LD_DE(sTrainerRankingBattlesHOF);
    // LD_BC(3);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(GBToRAMAddr(sTrainerRankingBattlesHOF), GBToRAMAddr(sTrainerRankingBattles), 3);

    // CALL(aUpdateTrainerRankingsChecksum);
    UpdateTrainerRankingsChecksum();
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void StubbedTrainerRankings_MagikarpLength(void){
    // RET;
    // LD_A(BANK(sTrainerRankingLongestMagikarp));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asTrainerRankingLongestMagikarp));
    // LD_DE(wMagikarpLength);
    uint16_t curLength = BigEndianToNative16(wram->wMagikarpLength);
    // LD_HL(sTrainerRankingLongestMagikarp);
    uint16_t longestLength = gb_read(sTrainerRankingLongestMagikarp + 1) | (gb_read(sTrainerRankingLongestMagikarp) << 8);

// Is this Magikarp the longest measured?
    // LD_A_de;
    // CP_A_hl;
    // IF_Z goto isLowByteHigher;
    // IF_NC goto newRecordLongest;
    // goto checkShortest;

// isLowByteHigher:
    // INC_HL;
    // INC_DE;
    // LD_A_de;
    // CP_A_hl;
    // DEC_HL;
    // DEC_DE;
    // IF_C goto checkShortest;
    if(curLength >= longestLength) {
    // newRecordLongest:
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;
        // LD_A_de;
        // DEC_DE;
        // LD_hl_A;
        gb_write16(sTrainerRankingLongestMagikarp, NativeToBigEndian16(curLength));
    }

// checkShortest:
    uint16_t shortestLength = gb_read(sTrainerRankingShortestMagikarp + 1) | (gb_read(sTrainerRankingShortestMagikarp) << 8);
// First, check if the record for shortest Magikarp is 0.
// This seems unnecessary, because the value is initialized to 100.0 cm.
    // LD_HL(sTrainerRankingShortestMagikarp);
    // LD_A_hli;
    // OR_A_hl;
    // DEC_HL;
    // IF_Z goto newRecordShortest;

// Now check if this Magikarp is the shortest
    // LD_A_de;
    // CP_A_hl;
    // IF_Z goto isLowByteLower;
    // IF_C goto newRecordShortest;
    // goto done;


// isLowByteLower:
    // INC_HL;
    // INC_DE;
    // LD_A_de;
    // CP_A_hl;
    // IF_NC goto done;
    // DEC_HL;
    // DEC_DE;

    if(curLength < shortestLength) {
    // newRecordShortest:
        // LD_A_de;
        // INC_DE;
        // LD_hli_A;
        // LD_A_de;
        // LD_hl_A;
        gb_write16(sTrainerRankingShortestMagikarp, NativeToBigEndian16(curLength));
    }

// done:
    // CALL(aUpdateTrainerRankingsChecksum);
    UpdateTrainerRankingsChecksum();
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void StubbedTrainerRankings_BugContestScore(uint16_t new_score){
    // RET;
    // LD_A(BANK(sTrainerRankingBugContestScore));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asTrainerRankingBugContestScore));
    // LDH_A_addr(hProduct);
    // LD_HL(sTrainerRankingBugContestScore);
    uint16_t saved_score = (gb_read(sTrainerRankingBugContestScore) << 8) | gb_read(sTrainerRankingBugContestScore + 1);
    // CP_A_hl;
    // IF_Z goto isLowByteHigher;
    // IF_NC goto newHighScore;
    // goto done;

// isLowByteHigher:
    // INC_HL;
    // LDH_A_addr(hMultiplicand);
    // CP_A_hl;
    // IF_C goto done;
    // DEC_HL;
    
    if(new_score > saved_score) {
    // newHighScore:
        // LDH_A_addr(hProduct);
        // LD_hli_A;
        gb_write(sTrainerRankingBugContestScore, HIGH(new_score));
        // LDH_A_addr(hMultiplicand);
        // LD_hl_A;
        gb_write(sTrainerRankingBugContestScore + 1, LOW(new_score));
    }

// done:
    // CALL(aUpdateTrainerRankingsChecksum);
    UpdateTrainerRankingsChecksum();
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void StubbedTrainerRankings_AddToSlotsWinStreak(void){
    // RET;
    // LD_A(BANK(sTrainerRankingCurrentSlotsStreak));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asTrainerRankingCurrentSlotsStreak));
    uint16_t streak = gb_read(sTrainerRankingCurrentSlotsStreak + 1) | (gb_read(sTrainerRankingCurrentSlotsStreak) << 8);

// Increment the current streak
    streak++;
    // LD_HL(sTrainerRankingCurrentSlotsStreak + 1);
    // INC_hl;
    // IF_NZ goto noCarry;
    // DEC_HL;
    // INC_hl;
    // INC_HL;
    gb_write(sTrainerRankingCurrentSlotsStreak, HIGH(streak));
    gb_write(sTrainerRankingCurrentSlotsStreak + 1, LOW(streak));

// noCarry:
    // DEC_HL;
// Now check if this is a new record for longest streak
    uint16_t longestStreak = gb_read(sTrainerRankingLongestSlotsStreak + 1) | (gb_read(sTrainerRankingLongestSlotsStreak) << 8);
    // LD_A_addr(sTrainerRankingLongestSlotsStreak);
    // CP_A_hl;
    // IF_Z goto isLowByteHigher;
    // IF_C goto newRecordStreak;
    // goto done;

// isLowByteHigher:
    // INC_HL;
    // LD_A_addr(sTrainerRankingLongestSlotsStreak + 1);
    // CP_A_hl;
    // IF_NC goto done;
    // DEC_HL;
    if(longestStreak < streak) {
    // newRecordStreak:
        // LD_A_hli;
        // LD_addr_A(sTrainerRankingLongestSlotsStreak);
        // LD_A_hl;
        // LD_addr_A(sTrainerRankingLongestSlotsStreak + 1);
        gb_write(sTrainerRankingLongestSlotsStreak, HIGH(streak));
        gb_write(sTrainerRankingLongestSlotsStreak + 1, LOW(streak));
    }

// done:
    // CALL(aUpdateTrainerRankingsChecksum);
    UpdateTrainerRankingsChecksum();
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void StubbedTrainerRankings_EndSlotsWinStreak(void){
    // RET;
    // LD_A(BANK(sTrainerRankingCurrentSlotsStreak));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asTrainerRankingCurrentSlotsStreak));
    // LD_HL(sTrainerRankingCurrentSlotsStreak);
    // XOR_A_A;
    // LD_hli_A;
    // LD_hl_A;
    gb_write16(sTrainerRankingCurrentSlotsStreak, 0);
    // CALL(aUpdateTrainerRankingsChecksum);
    UpdateTrainerRankingsChecksum();
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void StubbedTrainerRankings_AddToSlotsPayouts(void){
    RET;
    LD_A(BANK(sTrainerRankingTotalSlotsPayouts));
    CALL(aOpenSRAM);
    LD_HL(sTrainerRankingTotalSlotsPayouts + 3);
    LD_A_E;
    ADD_A_hl;
    LD_hld_A;
    LD_A_D;
    ADC_A_hl;
    LD_hld_A;
    IF_NC goto done;
    INC_hl;
    IF_NZ goto done;
    DEC_HL;
    INC_hl;
    IF_NZ goto done;
    LD_A(0xff);
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;


done:
    CALL(aUpdateTrainerRankingsChecksum);
    CALL(aCloseSRAM);
    RET;

}

void StubbedTrainerRankings_AddToBattlePayouts(const uint8_t* bc){
    // RET;
    // LD_A(BANK(sTrainerRankingTotalBattlePayouts));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asTrainerRankingTotalBattlePayouts));
    // LD_HL(sTrainerRankingTotalBattlePayouts + 3);
    uint8_t* hl = GBToRAMAddr(sTrainerRankingTotalBattlePayouts);
    // LD_A_bc;
    // DEC_BC;
    // ADD_A_hl;
    uint16_t temp = bc[2] + hl[3];
    // LD_hld_A;
    hl[3] = (temp & 0xff);
    // LD_A_bc;
    // DEC_BC;
    // ADC_A_hl;
    temp = bc[1] + hl[2] + ((temp & 0xff00) > 0)? 1: 0;
    // LD_hld_A;
    hl[2] = (temp & 0xff);
    // LD_A_bc;
    // ADC_A_hl;
    temp = bc[0] + hl[1] + ((temp & 0xff00) > 0)? 1: 0;
    // LD_hld_A;
    hl[1] = (temp & 0xff);
    // IF_NC goto done;
    if((temp & 0xff00) > 0) {
        // INC_hl;
        // IF_NZ goto done;
        if(++hl[0] == 0) {
            // LD_A(0xff);
            // LD_hli_A;
            hl[0] = 0xff;
            // LD_hli_A;
            hl[1] = 0xff;
            // LD_hli_A;
            hl[2] = 0xff;
            // LD_hl_A;
            hl[3] = 0xff;
        }
    }

// done:
    // CALL(aUpdateTrainerRankingsChecksum);
    UpdateTrainerRankingsChecksum();
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void StubbedTrainerRankings_StepCount(void){
    // RET;
    // LD_HL(sTrainerRankingStepCount);
    // JP(mStubbedTrainerRankings_Increment4Byte);
    return StubbedTrainerRankings_Increment4Byte(sTrainerRankingStepCount);
}

void StubbedTrainerRankings_BattleTowerWins(void){
//  //  unreferenced
    // RET;
    // LD_A(BANK(s5_aa8d));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_aa8d));
    // LD_A_addr(s5_aa8d);
    // AND_A_A;
    uint8_t a = gb_read(s5_aa8d);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET_NZ ;
    if(a != 0)
        return;
    // LD_HL(sTrainerRankingBattleTowerWins);
    // JP(mStubbedTrainerRankings_Increment2Byte);
    return StubbedTrainerRankings_Increment2Byte(sTrainerRankingBattleTowerWins);
}

void StubbedTrainerRankings_TMsHMsTaught(void){
    // RET;
    // LD_HL(sTrainerRankingTMsHMsTaught);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingTMsHMsTaught);
}

void StubbedTrainerRankings_Battles(void){
    // RET;
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_TUTORIAL);  // Exclude the Dude’s tutorial battle
    // RET_Z ;
    if(wram->wBattleType == BATTLETYPE_TUTORIAL)
        return;
    // LD_HL(sTrainerRankingBattles);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingBattles);
}

void StubbedTrainerRankings_WildBattles(void){
    // RET;
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_TUTORIAL);  // Exclude the Dude’s tutorial battle
    // RET_Z ;
    if(wram->wBattleType == BATTLETYPE_TUTORIAL)
        return;
    // LD_HL(sTrainerRankingWildBattles);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingWildBattles);
}

void StubbedTrainerRankings_TrainerBattles(void){
    // RET;
    // LD_HL(sTrainerRankingTrainerBattles);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingTrainerBattles);
}

void StubbedTrainerRankings_Unused1(void){
//  //  unreferenced
    // RET;
    // LD_HL(sTrainerRankingUnused1);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingUnused1);
}

void StubbedTrainerRankings_HallOfFame(void){
    // RET;
    // LD_HL(sTrainerRankingHOFEntries);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingHOFEntries);
}

void StubbedTrainerRankings_WildMonsCaught(void){
    // RET;
    // LD_HL(sTrainerRankingWildMonsCaught);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingWildMonsCaught);
}

void StubbedTrainerRankings_HookedEncounters(void){
    // RET;
    // LD_HL(sTrainerRankingHookedEncounters);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingHookedEncounters);
}

void StubbedTrainerRankings_EggsHatched(void){
    // RET;
    // LD_HL(sTrainerRankingEggsHatched);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingEggsHatched);
}

void StubbedTrainerRankings_MonsEvolved(void){
    // RET;
    // LD_HL(sTrainerRankingMonsEvolved);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingMonsEvolved);
}

void StubbedTrainerRankings_FruitPicked(void){
    // RET;
    // LD_HL(sTrainerRankingFruitPicked);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingFruitPicked);
}

void StubbedTrainerRankings_Healings(void){
    // RET;
    // LD_HL(sTrainerRankingHealings);
    // JP(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingHealings);
}

void StubbedTrainerRankings_MysteryGift(void){
    // RET;
    // LD_HL(sTrainerRankingMysteryGift);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingMysteryGift);
}

void StubbedTrainerRankings_Trades(void){
    // RET;
    // LD_HL(sTrainerRankingTrades);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingTrades);
}

void StubbedTrainerRankings_Fly(void){
    // RET;
    // LD_HL(sTrainerRankingFly);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingFly);
}

void StubbedTrainerRankings_Surf(void){
    // RET;
    // LD_HL(sTrainerRankingSurf);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingSurf);
}

void StubbedTrainerRankings_Waterfall(void){
    // RET;
    // LD_HL(sTrainerRankingWaterfall);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingWaterfall);
}

void StubbedTrainerRankings_WhiteOuts(void){
    // RET;
    // LD_HL(sTrainerRankingWhiteOuts);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingWhiteOuts);
}

void StubbedTrainerRankings_LuckyNumberShow(void){
    // RET;
    // LD_HL(sTrainerRankingLuckyNumberShow);
    // JR(mStubbedTrainerRankings_Increment2Byte);
    return StubbedTrainerRankings_Increment2Byte(sTrainerRankingLuckyNumberShow);
}

void StubbedTrainerRankings_PhoneCalls(void){
    // RET;
    // LD_HL(sTrainerRankingPhoneCalls);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingPhoneCalls);
}

void StubbedTrainerRankings_Unused2(void){
//  //  unreferenced
    // RET;
    // LD_HL(sTrainerRankingUnused2);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingUnused2);
}

void StubbedTrainerRankings_LinkBattles(void){
    // RET;
    // LD_HL(sTrainerRankingLinkBattles);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingLinkBattles);
}

void StubbedTrainerRankings_Splash(void){
    // RET;
// Only counts if it’s the player’s turn
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // RET_NZ ;
    if(hram->hBattleTurn != TURN_PLAYER)
        return;
    // LD_HL(sTrainerRankingSplash);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingSplash);
}

void StubbedTrainerRankings_TreeEncounters(void){
    // RET;
    // LD_HL(sTrainerRankingTreeEncounters);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingTreeEncounters);
}

void StubbedTrainerRankings_Unused3(void){
//  //  unreferenced
    // RET;
    // LD_HL(sTrainerRankingUnused3);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingUnused3);
}

void StubbedTrainerRankings_ColosseumWins(void){
//  //  win
    // RET;
    // LD_HL(sTrainerRankingColosseumWins);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingColosseumWins);
}

void StubbedTrainerRankings_ColosseumLosses(void){
//  //  lose
    // RET;
    // LD_HL(sTrainerRankingColosseumLosses);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingColosseumLosses);
}

void StubbedTrainerRankings_ColosseumDraws(void){
//  //  draw
    // RET;
    // LD_HL(sTrainerRankingColosseumDraws);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingColosseumDraws);
}

//  Counts uses of both Selfdestruct and Explosion.
void StubbedTrainerRankings_Selfdestruct(void){
    // RET;
// Only counts if it’s the player’s turn
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // RET_NZ ;
    if(hram->hBattleTurn != TURN_PLAYER)
        return;
    // LD_HL(sTrainerRankingSelfdestruct);
    // JR(mStubbedTrainerRankings_Increment3Byte);
    return StubbedTrainerRankings_Increment3Byte(sTrainerRankingSelfdestruct);
}

void StubbedTrainerRankings_Increment4Byte(uint16_t hl){
    // PUSH_BC;
    // LD_BC(3);
    // JR(mStubbedTrainerRankings_Increment);
    return StubbedTrainerRankings_Increment(hl, 3);
}

void StubbedTrainerRankings_Increment3Byte(uint16_t hl){
    // PUSH_BC;
    // LD_BC(2);
    // JR(mStubbedTrainerRankings_Increment);
    return StubbedTrainerRankings_Increment(hl, 2);
}

void StubbedTrainerRankings_Increment2Byte(uint16_t hl){
    // PUSH_BC;
    // LD_BC(1);
    // JR(mStubbedTrainerRankings_Increment);
    return StubbedTrainerRankings_Increment(hl, 1);
}

void StubbedTrainerRankings_Increment1Byte(uint16_t hl){
//  //  unreferenced
    // PUSH_BC;
    // LD_BC(0);

//  Increments a big-endian value of bc + 1 bytes at hl
    return StubbedTrainerRankings_Increment(hl, 0);
}

void StubbedTrainerRankings_Increment(uint16_t v, uint16_t bc){
    // LD_A(BANK(sTrainerRankings));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asTrainerRankings));
    // PUSH_HL;
    uint8_t* hl = GBToRAMAddr(v);
    // PUSH_DE;
    // LD_E_C;
    uint8_t e = LOW(bc);
    // INC_E;
    e++;
    bool z = true;

    do {
    // asm_106136:
        // LD_A_hli;
        uint8_t a = *(hl++);
        // INC_A;
        // IF_NZ goto asm_10613d;
        if(++a != 0) {
            z = false;
            break;
        }
        // DEC_E;
        // IF_NZ goto asm_106136;
    } while(--e != 0);

// asm_10613d:
    // POP_DE;
    // POP_HL;
    hl = GBToRAMAddr(v);
    // IF_Z goto asm_10614d;
    if(!z) {
        // ADD_HL_BC;
        hl += bc;
        do {
        // asm_106142:
            // INC_hl;
            ++*hl;
            // IF_NZ goto asm_10614d;
            if(*hl != 0)
                break;
            // LD_A_C;
            // AND_A_A;
            // IF_Z goto asm_10614d;
            if(bc == 0)
                break;
            // DEC_HL;
            hl--;
            // DEC_C;
            bc--;
            // goto asm_106142;
        } while(1);
    }

// asm_10614d:
    // CALL(aUpdateTrainerRankingsChecksum);
    UpdateTrainerRankingsChecksum();
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // POP_BC;
    // RET;
}

//  Used when SRAM bank 5 isn’t already loaded — what’s the point of this?
void UpdateTrainerRankingsChecksum2(void){
    // RET;
    // LD_A(BANK(sTrainerRankings));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asTrainerRankings));
    // CALL(aUpdateTrainerRankingsChecksum);
    UpdateTrainerRankingsChecksum();
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void UpdateTrainerRankingsChecksum(void){
    // PUSH_DE;
    // CALL(aCalculateTrainerRankingsChecksum);
    uint16_t de = CalculateTrainerRankingsChecksum();
    // LD_HL(sTrainerRankingsChecksum);
    // LD_hl_D;
    gb_write(sTrainerRankingsChecksum, HIGH(de));
    // INC_HL;
    // LD_hl_E;
    gb_write(sTrainerRankingsChecksum + 1, LOW(de));
    // POP_DE;
    // RET;
}

uint16_t CalculateTrainerRankingsChecksum(void){
    // PUSH_BC;
    // LD_HL(sTrainerRankings);
    uint8_t* hl = GBToRAMAddr(sTrainerRankings);
    // LD_BC(sTrainerRankingsChecksum - sTrainerRankings);
    uint16_t bc = sTrainerRankingsChecksum - sTrainerRankings;
    // XOR_A_A;
    // LD_DE(0);
    uint16_t de = 0;

    do {
    // asm_106179:
        // LD_A_E;
        // ADD_A_hl;
        // LD_E_A;
        // IF_NC goto asm_10617f;
        // INC_D;

    // asm_10617f:
        de += *hl;
        // INC_HL;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto asm_106179;
    } while(hl++, --bc != 0);
    // POP_BC;
    // RET;
    return de;
}

void BackupMobileEventIndex(void){
    // LD_A(BANK(sMobileEventIndex));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileEventIndex));
    // LD_A_addr(sMobileEventIndex);
    // PUSH_AF;
    uint8_t mobileEventIndex = gb_read(sMobileEventIndex);
    // LD_A(BANK(sMobileEventIndexBackup));
    // CALL(aOpenSRAM);
    CloseSRAM_Conv();
    OpenSRAM_Conv(MBANK(asMobileEventIndexBackup));
    // POP_AF;
    // LD_addr_A(sMobileEventIndexBackup);
    gb_write(sMobileEventIndexBackup, mobileEventIndex);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void RestoreMobileEventIndex(void){
    // LD_A(BANK(sMobileEventIndexBackup));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileEventIndexBackup));
    // LD_A_addr(sMobileEventIndexBackup);
    // PUSH_AF;
    uint8_t mobileEventIndexBackup = gb_read(sMobileEventIndexBackup);
    // LD_A(BANK(sMobileEventIndex));
    // CALL(aOpenSRAM);
    CloseSRAM_Conv();
    OpenSRAM_Conv(MBANK(asMobileEventIndex));
    // POP_AF;
    // LD_addr_A(sMobileEventIndex);
    gb_write(sMobileEventIndex, mobileEventIndexBackup);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void VerifyTrainerRankingsChecksum(void){
//  //  unreferenced
    CALL(aCalculateTrainerRankingsChecksum);
    LD_HL(sTrainerRankingsChecksum);
    LD_A_D;
    CP_A_hl;
    RET_NZ ;
    INC_HL;
    LD_A_E;
    CP_A_hl;
    RET;

}

void DeleteMobileEventIndex(void){
    // LD_A(BANK(sMobileEventIndex));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileEventIndex));
    // XOR_A_A;
    // LD_addr_A(sMobileEventIndex);
    gb_write(sMobileEventIndex, 0);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void InitializeTrainerRankings(void){
//  //  unreferenced
//  Initializes Trainer Rankings data for a new save file in JP Crystal.
    LD_HL(sTrainerRankings);
    LD_BC(sTrainerRankingsEnd - sTrainerRankings);
    XOR_A_A;
    CALL(aByteFill);

// Initialize the shortest Magikarp to 100.0 cm
    LD_HL(sTrainerRankingShortestMagikarp);
    LD_A(0x3);
    LD_hli_A;
    LD_hl(0xe8);

    CALL(aUpdateTrainerRankingsChecksum);
    LD_HL(sTrainerRankings);
    LD_DE(sTrainerRankingsBackup);
    LD_BC(sTrainerRankingsEnd - sTrainerRankings);
    CALL(aCopyBytes);
    RET;

}

static void v_MobilePrintNum_Function1062b2(uint8_t* hl, uint32_t num) {
// Function1062b2:
    // LD_C(0x0);
    uint8_t c = 0;
    uint8_t cy = 0;

    while(1) {
    // asm_1062b4:
        // LD_A_de;
        // DEC_DE;
        // LD_B_A;
        uint8_t b = num & 0xff;
        // LDH_A_addr(hPrintNumBuffer + 3);
        // SUB_A_B;
        // LDH_addr_A(hPrintNumBuffer + 7);
        hram->hPrintNumBuffer[7] = SubCarry8(hram->hPrintNumBuffer[3], b, cy, &cy);
        // LD_A_de;
        // DEC_DE;
        // LD_B_A;
        b = (num >> 8) & 0xff;
        // LDH_A_addr(hPrintNumBuffer + 2);
        // SBC_A_B;
        // LDH_addr_A(hPrintNumBuffer + 6);
        hram->hPrintNumBuffer[6] = SubCarry8(hram->hPrintNumBuffer[2], b, cy, &cy);
        // LD_A_de;
        // DEC_DE;
        // LD_B_A;
        b = (num >> 16) & 0xff;
        // LDH_A_addr(hPrintNumBuffer + 1);
        // SBC_A_B;
        // LDH_addr_A(hPrintNumBuffer + 5);
        hram->hPrintNumBuffer[5] = SubCarry8(hram->hPrintNumBuffer[1], b, cy, &cy);
        // LD_A_de;
        b = (num >> 24) & 0xff;
        // INC_DE;
        // INC_DE;
        // INC_DE;
        // LD_B_A;
        // LDH_A_addr(hPrintNumBuffer + 0);
        // SBC_A_B;
        // LDH_addr_A(hPrintNumBuffer + 4);
        hram->hPrintNumBuffer[4] = SubCarry8(hram->hPrintNumBuffer[0], b, cy, &cy);
        // IF_C goto asm_1062eb;
        if(cy)
            break;
        // LDH_A_addr(hPrintNumBuffer + 4);
        // LDH_addr_A(hPrintNumBuffer + 0);
        // LDH_A_addr(hPrintNumBuffer + 5);
        // LDH_addr_A(hPrintNumBuffer + 1);
        // LDH_A_addr(hPrintNumBuffer + 6);
        // LDH_addr_A(hPrintNumBuffer + 2);
        // LDH_A_addr(hPrintNumBuffer + 7);
        // LDH_addr_A(hPrintNumBuffer + 3);
        CopyBytes_Conv2(hram->hPrintNumBuffer, hram->hPrintNumBuffer + 4, 4);
        // INC_C;
        c++;
        // goto asm_1062b4;
    }

// asm_1062eb:
    // LDH_A_addr(hPrintNumBuffer + 8);
    // OR_A_C;
    // IF_Z goto LoadMinusTenIfNegative;
    if((hram->hPrintNumBuffer[8] | c) == 0) {
    // LoadMinusTenIfNegative:
        // LDH_A_addr(hPrintNumBuffer + 9);
        // BIT_A(7);
        // RET_Z ;
        if(!bit_test(hram->hPrintNumBuffer[9], 7))
            return;
        // LD_hl(-10);
        *hl = 0xf6;
        // RET;
        return;
    }
    else {
        // LD_A(-10);
        // ADD_A_C;
        // LD_hl_A;
        // LDH_addr_A(hPrintNumBuffer + 8);
        hram->hPrintNumBuffer[8] = *hl = 0xf6 + c;
        // RET;
        return;
    }
}

static uint8_t* v_MobilePrintNum_Function1062ff(uint8_t* hl) {
    // LDH_A_addr(hPrintNumBuffer + 9);
    // BIT_A(7);
    // IF_NZ goto asm_10630d;
    // BIT_A(6);
    // IF_Z goto asm_10630d;
    // LDH_A_addr(hPrintNumBuffer + 8);
    // AND_A_A;
    // RET_Z ;
    if(!bit_test(hram->hPrintNumBuffer[9], 7)
    && bit_test(hram->hPrintNumBuffer[9], 6)
    && hram->hPrintNumBuffer[8] == 0)
        return hl;

// asm_10630d:
    // INC_HL;
    // RET;
    return hl + 1;
}

//  Supports signed 31-bit integers (up to 10 digits)
//  b: Bits 0-4 = # bytes
//     Bit 7 = set if negative
//  c: Number of digits
//  de: highest byte of number to convert
//  hl: where to print the converted string
uint8_t* v_MobilePrintNum(uint8_t* hl, const void* de_, uint8_t b, uint8_t c){
    static const uint32_t PowerOfTen[] = {
        1,
        10,
        100,
        1000,
        10000,
        100000,
        1000000,
        10000000,
        100000000,
        1000000000
    };
    const uint8_t* de = de_;
    // PUSH_BC;
    // XOR_A_A;
    // LDH_addr_A(hPrintNumBuffer + 0);
    // LDH_addr_A(hPrintNumBuffer + 1);
    // LDH_addr_A(hPrintNumBuffer + 2);
    hram->hPrintNumBuffer[0] = 0;
    hram->hPrintNumBuffer[1] = 0;
    hram->hPrintNumBuffer[2] = 0;
    // LD_A_B;
    // AND_A(0xf);
    // CP_A(0x1);
    // IF_Z goto one_byte;
    // CP_A(0x2);
    // IF_Z goto two_bytes;
    // CP_A(0x3);
    // IF_Z goto three_bytes;
    switch(b & 0xf) {
    //  four bytes
    default:
        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 0);
        hram->hPrintNumBuffer[0] = *(de++);
        // INC_DE;
        fallthrough;

    case 3:
    // three_bytes:
        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 1);
        hram->hPrintNumBuffer[1] = *(de++);
        // INC_DE;
        fallthrough;

    case 2:
    // two_bytes:
        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 2);
        hram->hPrintNumBuffer[2] = *(de++);
        // INC_DE;
        fallthrough;

    case 1:
    // one_byte:
        // LD_A_de;
        // LDH_addr_A(hPrintNumBuffer + 3);
        hram->hPrintNumBuffer[3] = *(de++);
        // INC_DE;
        break;

    case 0: 
        return hl;
    }

    // PUSH_DE;
    // XOR_A_A;
    // LDH_addr_A(hPrintNumBuffer + 8);
    hram->hPrintNumBuffer[8] = 0;
    // LD_A_B;
    // LDH_addr_A(hPrintNumBuffer + 9);
    hram->hPrintNumBuffer[9] = b;
    // LD_A_C;
    uint8_t a = c;
    // CP_A(2);
    // IF_Z goto two_digits;
    const uint32_t* digit_ptr;
    if(a != 2) {
        // LD_DE(mv_MobilePrintNum__2);
        // CP_A(3);
        // IF_Z goto three_to_nine_digits;
        // LD_DE(mv_MobilePrintNum__3);
        // CP_A(4);
        // IF_Z goto three_to_nine_digits;
        // LD_DE(mv_MobilePrintNum__4);
        // CP_A(5);
        // IF_Z goto three_to_nine_digits;
        // LD_DE(mv_MobilePrintNum__5);
        // CP_A(6);
        // IF_Z goto three_to_nine_digits;
        // LD_DE(mv_MobilePrintNum__6);
        // CP_A(7);
        // IF_Z goto three_to_nine_digits;
        // LD_DE(mv_MobilePrintNum__7);
        // CP_A(8);
        // IF_Z goto three_to_nine_digits;
        // LD_DE(mv_MobilePrintNum__8);
        // CP_A(9);
        // IF_Z goto three_to_nine_digits;
        // LD_DE(mv_MobilePrintNum__9);
        digit_ptr = PowerOfTen + (a - 1);

    // three_to_nine_digits:
        // INC_DE;
        // INC_DE;
        // INC_DE;
        // DEC_A;
        // DEC_A;
        a -= 2;

        do {
        // digit_loop:
            // PUSH_AF;
            // CALL(av_MobilePrintNum_Function1062b2);
            v_MobilePrintNum_Function1062b2(hl, *digit_ptr);
            // CALL(av_MobilePrintNum_Function1062ff);
            hl = v_MobilePrintNum_Function1062ff(hl);
            // for(int rept = 0; rept < 4; rept++){
            // INC_DE;
            // }
            --digit_ptr;
            // POP_AF;
            // DEC_A;
            // IF_NZ goto digit_loop;
        } while(--a != 0);
    }

// two_digits:
    // LD_C(0);
    // LDH_A_addr(hPrintNumBuffer + 3);

// mod_ten_loop:
    // CP_A(10);
    // IF_C goto simple_divide_done;
    // SUB_A(10);
    // INC_C;
    // goto mod_ten_loop;
    uint8_t quot = hram->hPrintNumBuffer[3] / 10;
    uint8_t rem = hram->hPrintNumBuffer[3] % 10;

// simple_divide_done:
    // LD_B_A;
    // LDH_A_addr(hPrintNumBuffer + 8);
    // OR_A_C;
    // LDH_addr_A(hPrintNumBuffer + 8);
    // IF_NZ goto create_digit;
    if((hram->hPrintNumBuffer[8] | quot) == 0) {
        // CALL(av_MobilePrintNum_LoadMinusTenIfNegative);
    // inlined
        // LDH_A_addr(hPrintNumBuffer + 9);
        // BIT_A(7);
        // RET_Z ;
        if(bit_test(hram->hPrintNumBuffer[9], 7)) {
            // LD_hl(-10);
            *hl = 0xf6;
            // RET;
        }
        // goto done;
    }
    else {
    // create_digit:
        // LD_A(0xf6);
        // ADD_A_C;
        // LD_hl_A;
        *hl = 0xf6 + quot;
    }

// done:
    // CALL(av_MobilePrintNum_Function1062ff);
    hl = v_MobilePrintNum_Function1062ff(hl);
    // LD_A(0xf6);
    // ADD_A_B;
    // LD_hli_A;
    *(hl++) = 0xf6 + rem;
    // POP_DE;
    // POP_BC;
    // RET;
    return hl;
}

//  functions related to the cable club and various NPC scripts referencing communications

// Special to check mobile adapater status.
// Determines whether the mobile adapter has been activated.
// Has the following effects in JP Crystal:
// - Activates the Pokemon Communication Center and changes the map's music to MUSIC_MOBILE_CENTER
// - Adds option to battle or trade with mobile adapter in Pokemon Cable Club.
// - Activates the GS Ball event
// - Opens the Battle Tower
void Mobile_DummyReturnFalse(void){
#if PM_HIDDEN_NETWORK
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    // RET;
    wram->wScriptVar = FALSE;
#else
    u8_flag_s res = CheckMobileAdapterStatus();
    wram->wScriptVar = res.a;
#endif
}

// Sets Mobile Adapter status?
// Stubbed_Function106314
void SetMobileAdapterStatus(uint8_t c){
    // RET;
    // LD_A(BANK(s4_b000));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as4_b000));
    // LD_A_C;
    // CPL;
    // LD_addr_A(s4_b000);
    gb_write(s4_b000, ~c);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A(BANK(s7_a800));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as7_a800));
    // LD_A_C;
    // LD_addr_A(s7_a800);
    gb_write(s7_a800, c);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

u8_flag_s Mobile_AlwaysReturnNotCarry(void){
#if PM_HIDDEN_NETWORK
    // OR_A_A;
    // RET;
    return false;
#else
    return CheckMobileAdapterStatus();
#endif
}

//  called by Mobile_DummyReturnFalse in JP Crystal
// check ~[s4_b000] == [s7_a800]
u8_flag_s CheckMobileAdapterStatus(void){
    // LD_A(BANK(s4_b000));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as4_b000));
    // LD_A_addr(s4_b000);
    // CPL;
    // LD_B_A;
    uint8_t b = ~gb_read(s4_b000);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A(BANK(s7_a800));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as7_a800));
    // LD_A_addr(s7_a800);
    // LD_C_A;
    uint8_t c = gb_read(s7_a800);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A_C;
    // CP_A_B;
    // IF_NZ goto nope;
    if(c == b) {
    // check [s7_a800] != 0
        // AND_A_A;
        // IF_Z goto nope;

    // check !([s7_a800] & %01110000)
        // AND_A(0b10001111);
        // CP_A_C;
        // IF_NZ goto nope;

        if(c != 0 && !(c & 0b01110000)) {
            // LD_C_A;
            // SCF;
            // RET;
            return u8_flag(c & 0b10001111, true);
        }
    }

// nope:
    // XOR_A_A;
    // LD_C_A;
    // RET;
    return u8_flag(0, false);
}

// Mobile_DoMobileCommsLoop
void Function10635c(void){
    // LD_A_addr(wMobileCommsJumptableIndex);
    // BIT_A(7);
    // RET_NZ ;
    if(bit_test(wram->wMobileCommsJumptableIndex, 7))
        return;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // LD_HL(mFunction10635c_Jumptable);
    // RST(aJumpTable);
    // RET;
    switch(wram->wMobileCommsJumptableIndex) {
    // Jumptable:
        case 0:
        // init:
            // LD_DE(wcd30);
            // LD_HL(0x41);
            // LD_BC(0x41);
            // LD_A(MOBILEAPI_20);
            // CALL(aMobileAPI);
            MobileAPI(MOBILEAPI_20, &(mobile_api_data_s){.bc = 0x41, .h = 0x0, .l = 0x41, .de = &wram->wcd30});
            // LD_A_addr(wMobileCommsJumptableIndex);
            // INC_A;
            // LD_addr_A(wMobileCommsJumptableIndex);
            wram->wMobileCommsJumptableIndex++;
            // RET;
            return;
        case 1: return Function106392();
        case 2: return Function1063cc();
        case 3: return Function1063d8();
        case 4: return Function1063e5();
        case 5: return Function1063f3();
        case 6: return Function106403();
        case 7: return Function106442();
        case 8: return Function106453();
    }
}

void Function106392(void){
    // XOR_A_A;
    // LD_addr_A(wcf64);
    wram->wcf64 = 0x0;
    // LD_A_addr(wc821);
    // BIT_A(1);
    // IF_NZ goto asm_1063a2;
    if(bit_test(wram->wc821, 1)) {
    // asm_1063a2:
        // CALL(aMobile_AlwaysReturnNotCarry);
        u8_flag_s res = Mobile_AlwaysReturnNotCarry();
        // LD_A_C;
        // AND_A_A;
        // IF_NZ goto asm_1063b4;
        if(res.a == 0x0) {
            // LD_A(0xb);
            // LD_addr_A(wcf64);
            wram->wcf64 = 0xb;
            // LD_A(0x7);
            // LD_addr_A(wMobileCommsJumptableIndex);
            wram->wMobileCommsJumptableIndex = 0x7;
            // RET;
            return;
        }
        else {
        // asm_1063b4:
            // LD_A(0x7);
            // LD_addr_A(wcf64);
            wram->wcf64 = 0x7;
            // LD_A(0x7);
            // LD_addr_A(wMobileCommsJumptableIndex);
            wram->wMobileCommsJumptableIndex = 0x7;
            // RET;
            return;
        }
    }
    // BIT_A(0);
    // IF_Z goto asm_1063bf;
    else if(!bit_test(wram->wc821, 0)) {
    // asm_1063bf:
        // LD_A(0x1);
        // LD_addr_A(wcf64);
        wram->wcf64 = 0x1;
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
        return;
    }
    // RET;
}

void Function1063cc(void){
    // LD_A(0x78);
    // LD_addr_A(wcd42);
    wram->wcd42 = 0x78;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;

    return Function1063d8();
}

void Function1063d8(void){
    // LD_HL(wcd42);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wcd42 != 0)
        return;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;

}

void Function1063e5(void){
    // LD_A_addr(wcf64);
    // CP_A(0x3);
    // RET_NZ ;
    if(wram->wcf64 != 0x3)
        return;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function1063f3(void){
    // LD_DE(wcd31);
    // LD_A(MOBILEAPI_19);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_19, &(mobile_api_data_s){.de = &wram->wcd31});
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;
    // RET;
}

void Function106403(void){
    // LD_A_addr(wc821);
    // BIT_A(1);
    // IF_NZ goto asm_106426;
    if(bit_test(wram->wc821, 1)) {
    // asm_106426:
        // CALL(aMobile_AlwaysReturnNotCarry);
        u8_flag_s res = CheckMobileAdapterStatus();
        // LD_A_C;
        // AND_A_A;
        // IF_Z goto asm_106435;
        if(res.a != 0) {
            // LD_A_addr(wMobileCommsJumptableIndex);
            // INC_A;
            // LD_addr_A(wMobileCommsJumptableIndex);
            wram->wMobileCommsJumptableIndex++;
            // RET;
            return;
        }

    // asm_106435:
        // LD_C(0x0);
        // CALL(aStubbed_Function106314);
        SetMobileAdapterStatus(0x0);
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
        return;
    }
    // BIT_A(0);
    // IF_Z goto asm_10640f;
    if(!bit_test(wram->wc821, 0)) {
    // asm_10640f:
        // LD_A_addr(wcd31);
        // AND_A(0x80);
        // LD_C_A;
        // LD_A_addr(wcd30);
        // OR_A_C;
        // INC_A;
        // LD_C_A;
        // CALL(aStubbed_Function106314);
        SetMobileAdapterStatus(((wram->wcd31 & 0x80) | wram->wcd30) + 1);
        // LD_A_addr(wMobileCommsJumptableIndex);
        // INC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
        wram->wMobileCommsJumptableIndex++;
        // RET;
    }
    // RET;
}

void Function106442(void){
    // LD_A(MOBILEAPI_1B);
    // CALL(aMobileAPI);
    MobileAPI(MOBILEAPI_1B, &(mobile_api_data_s){0});
    // XOR_A_A;
    // LDH_addr_A(hMobile);
    hram->hMobile = 0x0;
    // LDH_addr_A(hMobileReceive);
    hram->hMobileReceive = 0x0;
    // LD_A_addr(wMobileCommsJumptableIndex);
    // INC_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex++;

    return Function106453();
}

void Function106453(void){
    // LD_A_addr(wMobileCommsJumptableIndex);
    // SET_A(7);
    // LD_addr_A(wMobileCommsJumptableIndex);
    bit_set(wram->wMobileCommsJumptableIndex, 7);
    // NOP;
    // LD_A(0x4);
    // LD_addr_A(wcf64);
    wram->wcf64 = 0x4;
    // RET;
}

void Stubbed_Function106462(void){
    // RET;
    // RET;
}

// Mobile_LoadDialingGFX
void Function106464(void){
    // LD_DE(mFontsExtra_SolidBlackGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * "■");  // $60
    // LD_BC((BANK(aFontsExtra_SolidBlackGFX) << 8) | 1);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x60, FontsExtra_SolidBlackGFX, 0, 1);
    // LD_DE(mFontsExtra2_UpArrowGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * "▲");  // $61
    // LD_BC((BANK(aFontsExtra2_UpArrowGFX) << 8) | 1);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x61, FontsExtra2_UpArrowGFX, 0, 1);
    // LD_DE(mMobileDialingFrameGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * "☎");  // $62
    // LD_C(9);
    // LD_B(BANK(aMobileDialingFrameGFX));
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x62, MobileDialingFrameGFX, 0, 9);
    // LD_DE(0x40b0);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x6b);
    // LD_B(0x0f);  // no graphics at 0f:40b0// JP leftover???
    // CALL(aGet2bpp);
    // FARCALL(aLoadFrame);
    LoadFrame_Conv();
    // RET;
}

void Function10649b(void){
//  //  unreferenced
    // LD_A_addr(wTextboxFrame);
    // maskbits(NUM_FRAMES, 0);
    // LD_BC(6 * LEN_1BPP_TILE);
    // LD_HL(mFrames);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * "┌");  // $79
    // LD_C(6);  // "┌" to "┘"
    // LD_B(BANK(aFrames));
    // CALL(aFunction1064c3);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * " ");  // $7f
    // LD_DE(mTextboxSpaceGFX);
    // LD_C(1);
    // LD_B(BANK(aTextboxSpaceGFX));
    // CALL(aFunction1064c3);
    // RET;
}

void Function1064c3(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x6);
    LDH_addr_A(rSVBK);
    PUSH_BC;
    PUSH_HL;
    LD_HL(mFunction3f88);
    LD_A_B;
    RST(aFarCall);
    POP_HL;
    POP_BC;
    POP_AF;
    LDH_addr_A(rSVBK);
    JR(masm_1064ed);

}

void Function1064d8(void){
//  //  unreferenced
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x6);
    LDH_addr_A(rSVBK);
    PUSH_BC;
    PUSH_HL;
    LD_HL(mFunction3f9f);
    LD_A_B;
    RST(aFarCall);
    POP_HL;
    POP_BC;
    POP_AF;
    LDH_addr_A(rSVBK);
    JR(masm_1064ed);

}

void asm_1064ed(void){
    LD_DE(wDecompressScratch);
    LD_B(0x0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x6);
    LDH_addr_A(rSVBK);
    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rVBK);
    CALL(aGet2bpp);
    POP_AF;
    LDH_addr_A(rVBK);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function10650a(void){
//  //  unreferenced
    LD_DE(mMobilePhoneTilesGFX);
    LD_BC((BANK(aMobilePhoneTilesGFX) << 8) | 17);
    CALL(aGet2bpp);
    RET;

}

const char MobileDialingFrameGFX[] = "gfx/mobile/dialing_frame.png";
