#include "../../../constants.h"
#include "move.h"
#include "scoring.h"

//  entries correspond to AI_* constants
static void (*const AIScoringPointers[])(void) = {
    AI_Basic,
    AI_Setup,
    AI_Types,
    AI_Offensive,
    AI_Smart,
    AI_Opportunist,
    AI_Aggressive,
    AI_Cautious,
    AI_Status,
    AI_Risky,
    AI_None,
    AI_None,
    AI_None,
    AI_None,
    AI_None,
    AI_None,
};

void AIChooseMove(void){
    (void)AIScoringPointers;
//  Score each move of wEnemyMonMoves in wEnemyAIMoveScores. Lower is better.
//  Pick the move with the lowest score.

//  Wildmons attack at random.
    LD_A_addr(wBattleMode);
    DEC_A;
    RET_Z ;

    LD_A_addr(wLinkMode);
    AND_A_A;
    RET_NZ ;

//  No use picking a move if there's no choice.
    FARCALL(aCheckEnemyLockedIn);
    RET_NZ ;

//  The default score is 20. Unusable moves are given a score of 80.
    LD_A(20);
    LD_HL(wEnemyAIMoveScores);
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;

//  Don't pick disabled moves.
    LD_A_addr(wEnemyDisabledMove);
    AND_A_A;
    IF_Z goto CheckPP;

    LD_HL(wEnemyMonMoves);
    LD_C(0);

CheckDisabledMove:
    CP_A_hl;
    IF_Z goto ScoreDisabledMove;
    INC_C;
    INC_HL;
    goto CheckDisabledMove;

ScoreDisabledMove:
    LD_HL(wEnemyAIMoveScores);
    LD_B(0);
    ADD_HL_BC;
    LD_hl(80);

//  Don't pick moves with 0 PP.

CheckPP:
    LD_HL(wEnemyAIMoveScores - 1);
    LD_DE(wEnemyMonPP);
    LD_B(0);

CheckMovePP:
    INC_B;
    LD_A_B;
    CP_A(NUM_MOVES + 1);
    IF_Z goto ApplyLayers;
    INC_HL;
    LD_A_de;
    INC_DE;
    AND_A(PP_MASK);
    IF_NZ goto CheckMovePP;
    LD_hl(80);
    goto CheckMovePP;

//  Apply AI scoring layers depending on the trainer class.

ApplyLayers:
    LD_HL(mTrainerClassAttributes + TRNATTR_AI_MOVE_WEIGHTS);

// If we have a battle in BattleTower just load the Attributes of the first trainer class in wTrainerClass (Falkner)
// so we have always the same AI, regardless of the loaded class of trainer
    LD_A_addr(wInBattleTowerBattle);
    BIT_A(0);
    IF_NZ goto battle_tower_skip;

    LD_A_addr(wTrainerClass);
    DEC_A;
    LD_BC(7);  // Trainer2AI - Trainer1AI
    CALL(aAddNTimes);


battle_tower_skip:
    LD_BC((CHECK_FLAG << 8) | 0);
    PUSH_BC;
    PUSH_HL;


CheckLayer:
    POP_HL;
    POP_BC;

    LD_A_C;
    CP_A(16);  // up to 16 scoring layers
    IF_Z goto DecrementScores;

    PUSH_BC;
    LD_D(BANK(aTrainerClassAttributes));
    PREDEF(pSmallFarFlagAction);
    LD_D_C;
    POP_BC;

    INC_C;
    PUSH_BC;
    PUSH_HL;

    LD_A_D;
    AND_A_A;
    IF_Z goto CheckLayer;

    LD_HL(mAIScoringPointers);
    DEC_C;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    // LD_A(BANK(aAIScoring));
    bank_push(BANK(aAIScoring));
    CALL(REG_HL + (REG_HL < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE)));
    bank_pop;

    goto CheckLayer;

//  Decrement the scores of all moves one by one until one reaches 0.

DecrementScores:
    LD_HL(wEnemyAIMoveScores);
    LD_DE(wEnemyMonMoves);
    LD_C(NUM_MOVES);


DecrementNextScore:
// If the enemy has no moves, this will infinite.
    LD_A_de;
    INC_DE;
    AND_A_A;
    IF_Z goto DecrementScores;

// We are done whenever a score reaches 0
    DEC_hl;
    IF_Z goto PickLowestScoreMoves;

// If we just decremented the fourth move's score, go back to the first move
    INC_HL;
    DEC_C;
    IF_Z goto DecrementScores;

    goto DecrementNextScore;

//  In order to avoid bias towards the moves located first in memory, increment the scores
//  that were decremented one more time than the rest (in case there was a tie).
//  This means that the minimum score will be 1.

PickLowestScoreMoves:
    LD_A_C;


move_loop:
    INC_hl;
    DEC_HL;
    INC_A;
    CP_A(NUM_MOVES + 1);
    IF_NZ goto move_loop;

    LD_HL(wEnemyAIMoveScores);
    LD_DE(wEnemyMonMoves);
    LD_C(NUM_MOVES);

//  Give a score of 0 to a blank move

loop2:
    LD_A_de;
    AND_A_A;
    IF_NZ goto skip_load;
    LD_hl_A;

//  Disregard the move if its score is not 1

skip_load:
    LD_A_hl;
    DEC_A;
    IF_Z goto keep;
    XOR_A_A;
    LD_hli_A;
    goto after_toss;


keep:
    LD_A_de;
    LD_hli_A;

after_toss:
    INC_DE;
    DEC_C;
    IF_NZ goto loop2;

//  Randomly choose one of the moves with a score of 1

ChooseMove:
    LD_HL(wEnemyAIMoveScores);
    CALL(aRandom);
    maskbits(NUM_MOVES, 0);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto ChooseMove;

    LD_addr_A(wCurEnemyMove);
    LD_A_C;
    LD_addr_A(wCurEnemyMoveNum);
    RET;

}

// void AIScoringPointers(void){
//  entries correspond to AI_* constants
    //dw ['AI_Basic'];
    //dw ['AI_Setup'];
    //dw ['AI_Types'];
    //dw ['AI_Offensive'];
    //dw ['AI_Smart'];
    //dw ['AI_Opportunist'];
    //dw ['AI_Aggressive'];
    //dw ['AI_Cautious'];
    //dw ['AI_Status'];
    //dw ['AI_Risky'];
    //dw ['AI_None'];
    //dw ['AI_None'];
    //dw ['AI_None'];
    //dw ['AI_None'];
    //dw ['AI_None'];
    //dw ['AI_None'];

// }
