#include "../../../constants.h"
#include "metronome.h"
#include "../effect_commands.h"
#include "../core.h"
#include "../../../home/battle_vars.h"
#include "../../../data/moves/metronome_exception_moves.h"

// static inline bool IsInMoveArray(const move_t* array, move_t a) {
//     for(int i = 0; array[i] != (move_t)-1; ++i) {
//         if(array[i] == a)
//             return true;
//     }
//     return false;
// }

void BattleCommand_Metronome(void){
//  metronome

    // CALL(aClearLastMove);
    ClearLastMove();
    // CALL(aCheckUserIsCharging);
    // IF_NZ goto charging;

    if(!CheckUserIsCharging_Conv()) {
        // LD_A_addr(wBattleAnimParam);
        // PUSH_AF;
        uint8_t param = wram->wBattleAnimParam;
        // CALL(aBattleCommand_LowerSub);
        BattleCommand_LowerSub();
        // POP_AF;
        // LD_addr_A(wBattleAnimParam);
        wram->wBattleAnimParam = param;
    }

// charging:
    // CALL(aLoadMoveAnim);
    LoadMoveAnim();

    move_t b;

    do {
    // GetMove:
        // CALL(aBattleRandom);
        b = v_BattleRandom_Conv();

    //  No invalid moves.
        // CP_A(NUM_ATTACKS + 1);
        // IF_NC goto GetMove;

    //  None of the moves in MetronomeExcepts.
        // PUSH_AF;
        // LD_DE(1);
        // LD_HL(mMetronomeExcepts);
        // CALL(aIsInArray);
        
        // POP_BC;
        // IF_C goto GetMove;

    //  No moves the user already has.
        // LD_A_B;
        // CALL(aCheckUserMove);
        // IF_Z goto GetMove;
    } while(b >= NUM_ATTACKS + 1 || IsInMoveArray(MetronomeExcepts, b) || CheckUserMove_Conv(b));

    // LD_A(BATTLE_VARS_MOVE);
    // CALL(aGetBattleVarAddr);
    // LD_hl_B;
    *GetBattleVarAddr_Conv(BATTLE_VARS_MOVE) = b;
    // CALL(aUpdateMoveData);
    UpdateMoveData();
    // JP(mResetTurn);
    return ResetTurn();

// INCLUDE "data/moves/metronome_exception_moves.asm"

}
