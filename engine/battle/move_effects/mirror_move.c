#include "../../../constants.h"
#include "mirror_move.h"
#include "../effect_commands.h"
#include "../../../home/names.h"
#include "../../../home/copy_name.h"
#include "../../../home/battle_vars.h"
#include "../../../home/battle.h"
#include "../../../data/text/battle.h"

void BattleCommand_MirrorMove(void){
//  mirrormove

    // CALL(aClearLastMove);
    ClearLastMove();

    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVarAddr);
    move_t* hl = GetBattleVarAddr(BATTLE_VARS_MOVE);

    // LD_A(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // CALL(aGetBattleVar);
    move_t a = GetBattleVar(BATTLE_VARS_LAST_COUNTER_MOVE_OPP);
    // AND_A_A;
    // IF_Z goto failed;

    // CALL(aCheckUserMove);
    // IF_NZ goto use;
    if(a == NO_MOVE
    || CheckUserMove_Conv(a)) {
    // failed:
        // CALL(aAnimateFailedMove);
        AnimateFailedMove();

        // LD_HL(mMirrorMoveFailedText);
        // CALL(aStdBattleTextbox);
        StdBattleTextbox(MirrorMoveFailedText);
        // JP(mEndMoveEffect);
        return EndMoveEffect();
    }


// use:
    // LD_A_B;
    // LD_hl_A;
    *hl = a;
    // LD_addr_A(wNamedObjectIndex);

    // PUSH_AF;
    // LD_A(BATTLE_VARS_MOVE_ANIM);
    // CALL(aGetBattleVarAddr);
    // LD_D_H;
    // LD_E_L;
    // POP_AF;
    struct Move* de = (struct Move*)GetBattleVarAddr(BATTLE_VARS_MOVE_ANIM);

    // DEC_A;
    // CALL(aGetMoveData);
    GetMoveData_Conv(de, a);
    // CALL(aGetMoveName);
    // CALL(aCopyName1);
    CopyName1_Conv2(GetMoveName_Conv2(a));
    // CALL(aCheckUserIsCharging);
    // IF_NZ goto done;
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

// done:
    // CALL(aBattleCommand_MoveDelay);
    BattleCommand_MoveDelay();
    // JP(mResetTurn);
    return ResetTurn();
}
