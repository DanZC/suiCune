#include "../../../constants.h"
#include "mimic.h"
#include "../effect_commands.h"
#include "../../../home/names.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

void BattleCommand_Mimic(void){
//  mimic

    // CALL(aClearLastMove);
    ClearLastMove();
    // CALL(aBattleCommand_MoveDelay);
    BattleCommand_MoveDelay();
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto fail;
    if(wram->wAttackMissed)
        return FailMimic();
    // LD_HL(wBattleMonMoves);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto player_turn;
    // LD_HL(wEnemyMonMoves);
    struct BattleMon* mon = (hram->hBattleTurn == TURN_PLAYER)? &wram->wBattleMon: &wram->wEnemyMon;

// player_turn:
    // CALL(aCheckHiddenOpponent);
    // IF_NZ goto fail;
    if(CheckHiddenOpponent_Conv())
        return FailMimic();
    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // CALL(aGetBattleVar);
    move_t b = GetBattleVar(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // AND_A_A;
    // IF_Z goto fail;
    // CP_A(STRUGGLE);
    // IF_Z goto fail;
    if(b == NO_MOVE || b == STRUGGLE)
        return FailMimic();
    // LD_B_A;
    // LD_C(NUM_MOVES);

    for(uint32_t c = 0; c < NUM_MOVES; ++c) {
    // check_already_knows_move:
        // LD_A_hli;
        // CP_A_B;
        // IF_Z goto fail;
        if(mon->moves[c] == b)
            return FailMimic();
        // DEC_C;
        // IF_NZ goto check_already_knows_move;
    }
    // DEC_HL;

    uint32_t c = NUM_MOVES - 1;
    for(; mon->moves[c] != MIMIC; --c) {
    // find_mimic:
        // LD_A_hld;
        // CP_A(MIMIC);
        // IF_NZ goto find_mimic;
    }
    // INC_HL;
    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // CALL(aGetBattleVar);
    // LD_hl_A;
    mon->moves[c] = GetBattleVar(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // LD_addr_A(wNamedObjectIndex);
    // LD_BC(wBattleMonPP - wBattleMonMoves);
    // ADD_HL_BC;
    // LD_hl(5);
    mon->pp[c] = 5;
    // CALL(aGetMoveName);
    GetMoveName(mon->moves[c]);
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mMimicLearnedMoveText);
    // JP(mStdBattleTextbox);
    StdBattleTextbox(MimicLearnedMoveText);


// fail:
    // JP(mFailMimic);
}
