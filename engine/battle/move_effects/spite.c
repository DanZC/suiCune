#include "../../../constants.h"
#include "spite.h"
#include "../core.h"
#include "../effect_commands.h"
#include "../../../home/battle.h"
#include "../../../home/battle_vars.h"
#include "../../../home/names.h"
#include "../../../data/text/battle.h"

void BattleCommand_Spite(void){
//  spite

    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // JP_NZ (mBattleCommand_Spite_failed);
    if(wram->wAttackMissed)
        goto failed;
    // LD_BC(PARTYMON_STRUCT_LENGTH);  // unused
    // LD_HL(wEnemyMonMoves);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_moves;
    // LD_HL(wBattleMonMoves);
    struct BattleMon* mon = (hram->hBattleTurn == TURN_PLAYER)? &wram->wEnemyMon: &wram->wBattleMon;

// got_moves:
    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // CALL(aGetBattleVar);
    move_t move = GetBattleVar(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // AND_A_A;
    // IF_Z goto failed;
    // CP_A(STRUGGLE);
    // IF_Z goto failed;
    if(move == NO_MOVE || move == STRUGGLE)
        goto failed;
    // LD_B_A;
    // LD_C(-1);
    uint8_t c = 0;

    while(mon->moves[c] != move) {
    // loop:
        // INC_C;
        c++;
        // LD_A_hli;
        // CP_A_B;
        // IF_NZ goto loop;
    }
    // LD_addr_A(wNamedObjectIndex);
    // DEC_HL;
    // LD_B(0);
    // PUSH_BC;
    // LD_C(wBattleMonPP - wBattleMonMoves);
    // ADD_HL_BC;
    // POP_BC;
    // LD_A_hl;
    // AND_A(PP_MASK);
    // IF_Z goto failed;
    if((mon->pp[c] & PP_MASK) == 0)
        goto failed;
    // PUSH_BC;
    // CALL(aGetMoveName);
    GetMoveName(move);
// lose 2-5 PP
    // CALL(aBattleRandom);
    // AND_A(0b11);
    // INC_A;
    // INC_A;
    // LD_B_A;
    uint8_t b = (v_BattleRandom() & 0b11) + 2;
    // LD_A_hl;
    // AND_A(PP_MASK);
    // CP_A_B;
    // IF_NC goto deplete_pp;
    if((mon->pp[c] & PP_MASK) < b) {
        // LD_B_A;
        b = mon->pp[c] & PP_MASK;
    }

// deplete_pp:
    // LD_A_hl;
    // SUB_A_B;
    // LD_hl_A;
    mon->pp[c] -= b;
    // PUSH_AF;
    // LD_A(MON_PP);
    // CALL(aOpponentPartyAttr);
    uint8_t* pp = OpponentPartyMon()->mon.PP;
    // LD_D_B;
    // POP_AF;
    // POP_BC;
    // ADD_HL_BC;
    // LD_E_A;
    uint8_t e = mon->pp[c];
    // LD_A(BATTLE_VARS_SUBSTATUS5_OPP);
    // CALL(aGetBattleVar);
    // BIT_A(SUBSTATUS_TRANSFORMED);
    // IF_NZ goto transformed;
    if(!bit_test(GetBattleVar(BATTLE_VARS_SUBSTATUS5_OPP), SUBSTATUS_TRANSFORMED)) {
        // LDH_A_addr(hBattleTurn);
        // AND_A_A;
        // IF_NZ goto not_wildmon;
        // LD_A_addr(wBattleMode);
        // DEC_A;
        // IF_NZ goto not_wildmon;
        if(hram->hBattleTurn == TURN_PLAYER && wram->wBattleMode == WILD_BATTLE) {
            // LD_HL(wWildMonPP);
            // ADD_HL_BC;
            pp = wram->wWildMonPP;
        }

    // not_wildmon:
        // LD_hl_E;
        pp[c] = e;
    }

// transformed:
    // PUSH_DE;
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // POP_DE;
    // LD_A_D;
    // LD_addr_A(wTextDecimalByte);
    wram->wTextDecimalByte = b;
    // LD_HL(mSpiteEffectText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(SpiteEffectText);

failed:
    // JP(mPrintDidntAffect2);
    return PrintDidntAffect2();

}
