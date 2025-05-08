#include "../../../constants.h"
#include "conversion2.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../../pokemon/types.h"
#include "../../../home/battle.h"
#include "../../../data/moves/moves.h"
#include "../../../data/text/battle.h"

void BattleCommand_Conversion2(void){
//  conversion2

    // LD_A_addr(wAttackMissed);
    // AND_A_A;
    // IF_NZ goto failed;
    if(wram->wAttackMissed)
        goto failed;
    // LD_HL(wBattleMonType1);
    // LDH_A_addr(hBattleTurn);
    // AND_A_A;
    // IF_Z goto got_type;
    // LD_HL(wEnemyMonType1);
    struct BattleMon* mon = (hram->hBattleTurn == TURN_PLAYER)? &wram->wBattleMon: &wram->wEnemyMon;

// got_type:
    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // CALL(aGetBattleVar);
    move_t lastCounterMove = GetBattleVar(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // AND_A_A;
    // IF_Z goto failed;
    if(lastCounterMove == NO_MOVE)
        return;
    // PUSH_HL;
    // DEC_A;
    // LD_HL(mMoves + MOVE_TYPE);
    // CALL(aGetMoveAttr);
    // LD_D_A;
    // POP_HL;
    uint8_t type = Moves[lastCounterMove].type;
    // CP_A(CURSE_TYPE);
    // IF_Z goto failed;
    if(type == CURSE_TYPE)
        goto failed;
    // CALL(aAnimateCurrentMove);
    AnimateCurrentMove();
    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();

    uint8_t a;
    do {
        do {
        // loop:
            // CALL(aBattleRandom);
            // maskbits(TYPES_END, 0);
            a = v_BattleRandom();
            // CP_A(UNUSED_TYPES);
            // IF_C goto okay;
            if(a < UNUSED_TYPES)
                break;
            // CP_A(UNUSED_TYPES_END);
            // IF_C goto loop;
            // CP_A(TYPES_END);
            // IF_NC goto loop;
        } while(a < UNUSED_TYPES_END || a >= TYPES_END);

    // okay:
        // LD_hli_A;
        mon->types[0] = a;
        // LD_hld_A;
        mon->types[1] = a;
        // PUSH_HL;
        // LD_A(BATTLE_VARS_MOVE_TYPE);
        // CALL(aGetBattleVarAddr);
        uint8_t* moveType = GetBattleVarAddr(BATTLE_VARS_MOVE_TYPE);
        // PUSH_AF;
        // PUSH_HL;
        // LD_A_D;
        // LD_hl_A;
        *moveType = type;
        // CALL(aBattleCheckTypeMatchup);
        BattleCheckTypeMatchup();
        // POP_HL;
        // POP_AF;
        // LD_hl_A;
        *moveType = a;
        // POP_HL;
        // LD_A_addr(wTypeMatchup);
        // CP_A(EFFECTIVE);
        // IF_NC goto loop;
    } while(wram->wTypeMatchup >= EFFECTIVE);
    // CALL(aBattleCommand_SwitchTurn);
    BattleCommand_SwitchTurn();

    // LD_A_hl;
    // LD_addr_A(wNamedObjectIndex);
    // PREDEF(pGetTypeName);
    GetTypeName(mon->types[0]);
    // LD_HL(mTransformedTypeText);
    // JP(mStdBattleTextbox);
    return StdBattleTextbox(TransformedTypeText);

failed:
    // JP(mFailMove);
    return FailMove();
}
