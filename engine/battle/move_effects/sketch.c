#include "../../../constants.h"
#include "sketch.h"
#include "../effect_commands.h"
#include "../../../home/battle_vars.h"
#include "../../../home/battle.h"
#include "../../../home/names.h"
#include "../../../data/text/battle.h"

void BattleCommand_Sketch(void){
//  sketch

    // CALL(aClearLastMove);
    ClearLastMove();
//  Don't sketch during a link battle
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_Z goto not_linked;
    if(wram->wLinkMode != LINK_NULL) {
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();
        // JP(mPrintNothingHappened);
        PrintNothingHappened();
    }

// not_linked:
//  If the opponent has a substitute up, fail.
    // CALL(aCheckSubstituteOpp);
    // JP_NZ (mBattleCommand_Sketch_fail);
    if(CheckSubstituteOpp_Conv())
        goto fail;
#if BUGFIX_TRANSFORM_SKETCH
//  If the user is transformed, fail.
    // LD_A(BATTLE_VARS_SUBSTATUS5);
    // CALL(aGetBattleVarAddr);
    // BIT_hl(SUBSTATUS_TRANSFORMED);
    // JP_NZ (mBattleCommand_Sketch_fail);
    if(bit_test(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5), SUBSTATUS_TRANSFORMED))
        goto fail;
#else
//  If the opponent is transformed, fail.
    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVarAddr);
    // BIT_hl(SUBSTATUS_TRANSFORMED);
    // JP_NZ (mBattleCommand_Sketch_fail);
    if(bit_test(*GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5_OPP), SUBSTATUS_TRANSFORMED))
        goto fail;
#endif
//  Get the user's moveset in its party struct.
//  This move replacement shall be permanent.
//  Pointer will be in de.
    // LD_A(MON_MOVES);
    // CALL(aUserPartyAttr);
    // LD_D_H;
    // LD_E_L;
    struct PartyMon* de = UserPartyMon();
//  Get the battle move structs.
    // LD_HL(wBattleMonMoves);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto get_last_move;
    // LD_HL(wEnemyMonMoves);
    struct BattleMon* hl = (hram->hBattleTurn == TURN_PLAYER)? &wram->wBattleMon: &wram->wEnemyMon;

// get_last_move:
    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // CALL(aGetBattleVar);
    // LD_addr_A(wNamedObjectIndex);
    // LD_B_A;
    move_t b = GetBattleVar(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
//  Fail if move is invalid or is Struggle.
    // AND_A_A;
    // IF_Z goto fail;
    // CP_A(STRUGGLE);
    // IF_Z goto fail;
    if(b == NO_MOVE || b == STRUGGLE)
        goto fail;
//  Fail if user already knows that move
    // LD_C(NUM_MOVES);
    uint8_t c = NUM_MOVES;

    move_t a;
    uint8_t i = 0;
    do {
    // does_user_already_know_move:
        // LD_A_hli;
        a = hl->moves[i++];
        // CP_A_B;
        // IF_Z goto fail;
        if(a == b)
            goto fail;
        // DEC_C;
        // IF_NZ goto does_user_already_know_move;
    } while(--c != 0);
//  Find Sketch in the user's moveset.
//  Pointer in hl, and index in c.
    // DEC_HL;
    --i;
    // LD_C(NUM_MOVES);
    c = NUM_MOVES;

    do {
    // find_sketch:
        // DEC_C;
        --c;
        // LD_A_hld;
        a = hl->moves[i--];
        // CP_A(SKETCH);
        // IF_NZ goto find_sketch;
    } while(a != SKETCH);
    // INC_HL;
    i++;
//  The Sketched move is loaded to that slot.
    // LD_A_B;
    // LD_hl_A;
    hl->moves[i] = b;
//  Copy the base PP from that move.
    // PUSH_BC;
    // PUSH_HL;
    // DEC_A;
    // LD_HL(mMoves + MOVE_PP);
    // CALL(aGetMoveAttr);
    const struct Move* data = GetMoveAttr_Conv(b-1);
    // POP_HL;
    // LD_BC(wBattleMonPP - wBattleMonMoves);
    // ADD_HL_BC;
    // LD_hl_A;
    hl->pp[i] = data->pp;
    // POP_BC;

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto user_trainer;
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // IF_NZ goto user_trainer;
    if(hram->hBattleTurn != 0 && wram->wBattleMode == WILD_BATTLE) {
    //  wildmon
        // LD_A_hl;
        // PUSH_BC;
        // LD_HL(wWildMonPP);
        // LD_B(0);
        // ADD_HL_BC;
        // LD_hl_A;
        wram->wWildMonPP[i] = data->pp;
        // LD_HL(wWildMonMoves);
        // ADD_HL_BC;
        // POP_BC;
        // LD_hl_B;
        wram->wWildMonMoves[i] = b;
        // goto done_copy;
    }
    else {
    // user_trainer:
        // LD_A_hl;
        // PUSH_AF;
        // LD_L_C;
        // LD_H(0);
        // ADD_HL_DE;
        // LD_A_B;
        // LD_hl_A;
        de->mon.moves[i] = b;
        // POP_AF;
        // LD_DE(MON_PP - MON_MOVES);
        // ADD_HL_DE;
        // LD_hl_A;
        de->mon.PP[i] = data->pp;
    }

// done_copy:
    // CALL(aGetMoveName);
    GetMoveName(b);
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mSketchedText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(SketchedText);


fail:
    // CALL(aAnimateFailedMove);
    AnimateFailedMove();
    // JP(mPrintDidntAffect);
    return PrintDidntAffect();
}
