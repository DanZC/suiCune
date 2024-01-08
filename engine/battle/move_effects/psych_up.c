#include "../../../constants.h"
#include "psych_up.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_PsychUp(void){
//  psychup

    // LD_HL(wEnemyStatLevels);
    // LD_DE(wPlayerStatLevels);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto pointers_correct;
//  It's the enemy's turn, so swap the pointers.
    // PUSH_HL;
    // LD_H_D;
    // LD_L_E;
    // POP_DE;
    uint8_t* hl = (hram->hBattleTurn == 0)? wram->wEnemyStatLevels: wram->wPlayerStatLevels;
    uint8_t* de = (hram->hBattleTurn == 0)? wram->wPlayerStatLevels: wram->wEnemyStatLevels;

// pointers_correct:
    // PUSH_HL;
    // LD_B(NUM_LEVEL_STATS);
//  If any of the enemy's stats is modified from its base level,
//  the move succeeds.  Otherwise, it fails.

    for(int i = 0; i < NUM_LEVEL_STATS; ++i) {
    // loop:
        // LD_A_hli;
        // CP_A(BASE_STAT_LEVEL);
        // IF_NZ goto l_break;
        if(hl[i] != BASE_STAT_LEVEL) 
            break;
        // DEC_B;
        // IF_NZ goto loop;
        if(i + 1 == NUM_LEVEL_STATS) {
            // POP_HL;
            // CALL(aAnimateFailedMove);
            AnimateFailedMove();
            // JP(mPrintButItFailed);
            return PrintButItFailed();
        }
    }

// l_break:
    // POP_HL;
    // LD_B(NUM_LEVEL_STATS);

    for(int i = 0; i < NUM_LEVEL_STATS; ++i) {
    // loop2:
        // LD_A_hli;
        // LD_de_A;
        // INC_DE;
        de[i] = hl[i];
        // DEC_B;
        // IF_NZ goto loop2;
    }
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_NZ goto calc_enemy_stats;
    if(hram->hBattleTurn == 0) {
        // CALL(aCalcPlayerStats);
        CalcPlayerStats();
        // goto merge;
    }
    else {
    // calc_enemy_stats:
        // CALL(aCalcEnemyStats);
        CalcEnemyStats();
    }

// merge:
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mCopiedStatsText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox_Conv2(CopiedStatsText);
}
