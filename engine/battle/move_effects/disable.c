#include "../../../constants.h"
#include "disable.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../../../home/battle_vars.h"
#include "../../../home/names.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_Disable(void){
//  disable

    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto failed;
    if(wram->wAttackMissed)
        goto failed;

    // LD_DE(wEnemyDisableCount);
    // LD_HL(wEnemyMonMoves);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_moves;
    // LD_DE(wPlayerDisableCount);
    // LD_HL(wBattleMonMoves);
    uint8_t* disableCount = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemyDisableCount: &wram->wPlayerDisableCount;
    move_t* moves = (hram->hBattleTurn == TURN_PLAYER)? wram->wEnemyMon.moves: wram->wBattleMon.moves;

// got_moves:

    // LD_A_de;
    // AND_A_A;
    // IF_NZ goto failed;
    if(*disableCount != 0)
        goto failed;

    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // CALL(aGetBattleVar);
    move_t lastCounterMove = GetBattleVar(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // AND_A_A;
    // IF_Z goto failed;
    // CP_A(STRUGGLE);
    // IF_Z goto failed;
    if(lastCounterMove == NO_MOVE || lastCounterMove == STRUGGLE)
        goto failed;

    // LD_B_A;
    // LD_C(0xff);
    uint8_t c = 0;

    do {
    // loop:
        // INC_C;
        // LD_A_hli;
        // CP_A_B;
        // IF_NZ goto loop;
    } while(moves[c++] != lastCounterMove);

    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // LD_HL(wEnemyMonPP);
    // IF_Z goto got_pp;
    // LD_HL(wBattleMonPP);
    uint8_t* pp = (hram->hBattleTurn == TURN_PLAYER)? wram->wEnemyMon.pp: wram->wBattleMon.pp;

// got_pp:
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto failed;
    if(pp[c] == 0)
        goto failed;

    uint8_t a;
    do {
    // loop2:
        // CALL(aBattleRandom);
        // AND_A(7);
        a = v_BattleRandom_Conv() & 7;
        // IF_Z goto loop2;
    } while(a == 0);
    // INC_A;
    a++;
    // INC_C;
    // SWAP_C;
    // ADD_A_C;
    // LD_de_A;
    *disableCount = a + ((c << 4) | (c >> 4));
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // LD_HL(wDisabledMove);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_NZ goto got_disabled_move_pointer;
    // INC_HL;
    move_t* disabledMove = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemyDisabledMove: &wram->wDisabledMove;

// got_disabled_move_pointer:
    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // CALL(aGetBattleVar);
    // LD_hl_A;
    *disabledMove = lastCounterMove;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetMoveName);
    GetMoveName_Conv2(lastCounterMove);
    // LD_HL(mWasDisabledText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(WasDisabledText);

failed:
    // JP(mFailMove);
    return FailMove();

}
