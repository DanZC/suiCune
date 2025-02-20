#include "../../../constants.h"
#include "sleep_talk.h"
#include "../effect_commands.h"
#include "../../../home/battle_vars.h"
#include "../core.h"

static bool BattleCommand_SleepTalk_check_two_turn_move(move_t b) {
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;

    // LD_B_A;
    // CALLFAR(aGetMoveEffect);
    uint8_t effect = GetMoveEffect_Conv(b);
    // LD_A_B;

    // POP_BC;
    // POP_DE;
    // POP_HL;

    // CP_A(EFFECT_SKULL_BASH);
    // RET_Z ;
    // CP_A(EFFECT_RAZOR_WIND);
    // RET_Z ;
    // CP_A(EFFECT_SKY_ATTACK);
    // RET_Z ;
    // CP_A(EFFECT_SOLARBEAM);
    // RET_Z ;
    // CP_A(EFFECT_FLY);
    // RET_Z ;
    // CP_A(EFFECT_BIDE);
    // RET;
    return effect == EFFECT_SKULL_BASH
        || effect == EFFECT_RAZOR_WIND
        || effect == EFFECT_SKY_ATTACK
        || effect == EFFECT_SOLARBEAM
        || effect == EFFECT_FLY
        || effect == EFFECT_BIDE;
}

// Returns true (nc) if the move is usable.
static bool BattleCommand_SleepTalk_check_has_usable_move(struct BattleMon* mon) {
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_A_addr(wDisabledMove);
    // IF_Z goto got_move_2;

    // LD_A_addr(wEnemyDisabledMove);
    move_t disabledMove = (hBattleTurn == 0)? wram->wDisabledMove: wram->wEnemyDisabledMove;

// got_move_2:
    // LD_B_A;
    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVar);
    // LD_C_A;
    move_t c = GetBattleVar_Conv(BATTLE_VARS_MOVE);
    // DEC_HL;
    // LD_D(NUM_MOVES);

    for(int i = 0; i < NUM_MOVES; ++i) {
    // loop2:
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto carry;
        if(mon->moves[i] == NO_MOVE)
            return false;

        // CP_A_C;
        // IF_Z goto nope;
        // CP_A_B;
        // IF_Z goto nope;
        if(mon->moves[i] == c || mon->moves[i] == disabledMove)
            continue;

        // CALL(aBattleCommand_SleepTalk_check_two_turn_move);
        // IF_NZ goto no_carry;
        if(!BattleCommand_SleepTalk_check_two_turn_move(mon->moves[i]))
            return true;


    // nope:
        // INC_HL;
        // DEC_D;
        // IF_NZ goto loop2;
    }

    return false;

// carry:
    // SCF;
    // RET;

// no_carry:
    // AND_A_A;
    // RET;
}

void BattleCommand_SleepTalk(void){
//  sleeptalk

    // CALL(aClearLastMove);
    ClearLastMove();
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto fail;
    if(wram->wAttackMissed)
        goto fail;
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_HL(wBattleMonMoves + 1);
    // LD_A_addr(wDisabledMove);
    // LD_D_A;
    // IF_Z goto got_moves;
    // LD_HL(wEnemyMonMoves + 1);
    // LD_A_addr(wEnemyDisabledMove);
    // LD_D_A;
    struct BattleMon* mon = (hBattleTurn == 0)? &wram->wBattleMon: &wram->wEnemyMon;
    move_t d = (hBattleTurn == 0)? wram->wDisabledMove: wram->wEnemyDisabledMove;

// got_moves:
    // LD_A(BATTLE_VARS_STATUS);
    // CALL(aGetBattleVar);
    // AND_A(SLP);
    // IF_Z goto fail;
    if((GetBattleVar_Conv(BATTLE_VARS_STATUS) & SLP) == 0)
        goto fail;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto fail;
    if(mon->moves[1] == NO_MOVE)
        goto fail;
    // CALL(aBattleCommand_SleepTalk_safely_check_has_usable_move);
    // IF_C goto fail;
    if(!BattleCommand_SleepTalk_check_has_usable_move(mon))
        goto fail;
    // DEC_HL;

    move_t e;
    while(1) {
    // sample_move:
        // PUSH_HL;
        // CALL(aBattleRandom);
        // maskbits(NUM_MOVES, 0);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hl;
        e = mon->moves[v_BattleRandom_Conv() & 3];
        // POP_HL;
        // AND_A_A;
        // IF_Z goto sample_move;
        if(e == NO_MOVE)
            continue;
        // LD_E_A;
        // LD_A(BATTLE_VARS_MOVE_ANIM);
        // CALL(aGetBattleVar);
        // CP_A_E;
        // IF_Z goto sample_move;
        if(GetBattleVar_Conv(BATTLE_VARS_MOVE_ANIM) == e)
            continue;
        // LD_A_E;
        // CP_A_D;
        // IF_Z goto sample_move;
        if(e == d)
            continue;
        // CALL(aBattleCommand_SleepTalk_check_two_turn_move);
        // IF_Z goto sample_move;
        if(BattleCommand_SleepTalk_check_two_turn_move(e))
            continue;
        break;
    }
    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVarAddr);
    move_t* move = GetBattleVarAddr_Conv(BATTLE_VARS_MOVE);
    // LD_A_E;
    // LD_hl_A;
    *move = e;
    // CALL(aCheckUserIsCharging);
    // IF_NZ goto charging;
    if(!CheckUserIsCharging_Conv()) {
        // LD_A_addr(wBattleAnimParam);
        uint8_t param = wram->wBattleAnimParam;
        // PUSH_AF;
        // CALL(aBattleCommand_LowerSub);
        BattleCommand_LowerSub();
        // POP_AF;
        // LD_addr_A(wBattleAnimParam);
        wram->wBattleAnimParam = param;
    }

// charging:
    // CALL(aLoadMoveAnim);
    LoadMoveAnim();
    // CALL(aUpdateMoveData);
    UpdateMoveData();
    // JP(mResetTurn);
    return ResetTurn();


fail:
    // CALL(aAnimateFailedMove);
    AnimateFailedMove();
    // JP(mTryPrintButItFailed);
    return TryPrintButItFailed();

}
