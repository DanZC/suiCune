#include "../../../constants.h"
#include "encore.h"
#include "../core.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../data/text/battle.h"

// TODO: Clean up gotos.
void BattleCommand_Encore(void){
//  encore

    // LD_HL(wEnemyMonMoves);
    // LD_DE(wEnemyEncoreCount);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto ok;
    // LD_HL(wBattleMonMoves);
    // LD_DE(wPlayerEncoreCount);
    struct BattleMon* mon = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemyMon: &wram->wBattleMon;
    uint8_t* de = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemyEncoreCount: &wram->wPlayerEncoreCount;

// ok:
    // LD_A(BATTLE_VARS_LAST_MOVE_OPP);
    // CALL(aGetBattleVar);
    move_t b = GetBattleVar(BATTLE_VARS_LAST_MOVE_OPP);
    // AND_A_A;
    // JP_Z (mBattleCommand_Encore_failed);
    // CP_A(STRUGGLE);
    // JP_Z (mBattleCommand_Encore_failed);
    // CP_A(ENCORE);
    // JP_Z (mBattleCommand_Encore_failed);
    // CP_A(MIRROR_MOVE);
    // JP_Z (mBattleCommand_Encore_failed);
    if(b == NO_MOVE
    || b == STRUGGLE
    || b == ENCORE
    || b == MIRROR_MOVE) {
        goto failed;
    }
    // LD_B_A;

    uint8_t c = 0;
    while(mon->moves[c] != b) {
    // got_move:
        // LD_A_hli;
        // CP_A_B;
        // IF_NZ goto got_move;
        c++;
    } 

    // LD_BC(wBattleMonPP - wBattleMonMoves - 1);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(PP_MASK);
    // JP_Z (mBattleCommand_Encore_failed);
    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JP_NZ (mBattleCommand_Encore_failed);
    if((mon->pp[c] & PP_MASK) == 0 || wram->wAttackMissed)
        goto failed;
    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVarAddr);
    uint8_t* ss5 = GetBattleVarAddr(BATTLE_VARS_SUBSTATUS5_OPP);
    // BIT_hl(SUBSTATUS_ENCORED);
    // JP_NZ (mBattleCommand_Encore_failed);
    if(bit_test(*ss5, SUBSTATUS_ENCORED))
        goto failed;
    // SET_hl(SUBSTATUS_ENCORED);
    bit_set(*ss5, SUBSTATUS_ENCORED);
    // CALL(aBattleRandom);
    // AND_A(0x3);
    // INC_A;
    // INC_A;
    // INC_A;
    // LD_de_A;
    *de = (v_BattleRandom_Conv() & 0x3) + 3;
    // CALL(aCheckOpponentWentFirst);
    // IF_NZ goto finish_move;
    if(!CheckOpponentWentFirst_Conv()) {
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_Z goto force_last_enemy_move;
        if(hram->hBattleTurn != TURN_PLAYER) {
            // PUSH_HL;
            // LD_A_addr(wLastPlayerMove);
            // LD_B_A;
            move_t pmove = wram->wLastPlayerMove;
            uint8_t idx = 0;
            // LD_C(0);
            // LD_HL(wBattleMonMoves);
            move_t* pmoves = wram->wBattleMon.moves;

            while(1) {
            // find_player_move:
                // LD_A_hli;
                // CP_A_B;
                // IF_Z goto got_player_move;
                if(pmoves[idx] == pmove)
                    break;
                // INC_C;
                // LD_A_C;
                // CP_A(NUM_MOVES);
                // IF_C goto find_player_move;
                if(++idx < NUM_MOVES)
                    continue;
                // POP_HL;
                // RES_hl(SUBSTATUS_ENCORED);
                bit_reset(*ss5, SUBSTATUS_ENCORED);
                // XOR_A_A;
                // LD_de_A;
                *de = 0;
                goto failed;
            }


        // got_player_move:
            // POP_HL;
            // LD_A_C;
            // LD_addr_A(wCurMoveNum);
            wram->wCurMoveNum = idx;
            // LD_A_B;
            // LD_addr_A(wCurPlayerMove);
            wram->wCurPlayerMove = pmove;
            // DEC_A;
            // LD_DE(wPlayerMoveStruct);
            // CALL(aGetMoveData);
            GetMoveData_Conv(&wram->wPlayerMoveStruct, pmove);
            // goto finish_move;
        }
        else {
        // force_last_enemy_move:
            // PUSH_HL;
            // LD_A_addr(wLastEnemyMove);
            move_t emove = wram->wLastEnemyMove;
            // LD_B_A;
            // LD_C(0);
            uint8_t idx = 0;
            // LD_HL(wEnemyMonMoves);
            move_t* emoves = wram->wEnemyMon.moves;

            while(1) {
            // find_enemy_move:
                // LD_A_hli;
                // CP_A_B;
                // IF_Z goto got_enemy_move;
                if(emoves[idx] == emove)
                    break;
                // INC_C;
                // LD_A_C;
                // CP_A(NUM_MOVES);
                // IF_C goto find_enemy_move;
                if(++idx < NUM_MOVES)
                    continue;
                // POP_HL;
                // RES_hl(SUBSTATUS_ENCORED);
                bit_reset(*ss5, SUBSTATUS_ENCORED);
                // XOR_A_A;
                // LD_de_A;
                *de = 0;
                goto failed;
            }


        // got_enemy_move:
            // POP_HL;
            // LD_A_C;
            // LD_addr_A(wCurEnemyMoveNum);
            wram->wCurEnemyMoveNum = idx;
            // LD_A_B;
            // LD_addr_A(wCurEnemyMove);
            wram->wCurEnemyMove = emove;
            // DEC_A;
            // LD_DE(wEnemyMoveStruct);
            // CALL(aGetMoveData);
            GetMoveData_Conv(&wram->wEnemyMoveStruct, emove);
        }
    }

// finish_move:
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(mGotAnEncoreText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(GotAnEncoreText);


failed:
    // JP(mPrintDidntAffect2);
    return PrintDidntAffect2();

}
