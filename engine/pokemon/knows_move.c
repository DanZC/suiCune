#include "../../constants.h"
#include "knows_move.h"
#include "../../home/text.h"
#include "../../data/text/common.h"

void KnowsMove(void){
    LD_A(MON_MOVES);
    CALL(aGetPartyParamLocation);
    LD_A_addr(wPutativeTMHMMove);
    LD_B_A;
    LD_C(NUM_MOVES);

loop:
    LD_A_hli;
    CP_A_B;
    IF_Z goto knows_move;
    DEC_C;
    IF_NZ goto loop;
    AND_A_A;
    RET;


knows_move:
    LD_HL(mKnowsMove_KnowsMoveText);
    CALL(aPrintText);
    SCF;
    RET;

}

bool KnowsMove_Conv(const struct BoxMon* hl, move_t b) {
static const txt_cmd_s KnowsMoveText[] = {
    text_far(v_KnowsMoveText)
    text_end
};
    // LD_A(MON_MOVES);
    // CALL(aGetPartyParamLocation);
    // LD_A_addr(wPutativeTMHMMove);
    // LD_B_A;
    // LD_C(NUM_MOVES);

    for(uint32_t i = 0; i < NUM_MOVES; ++i) {
    // loop:
        // LD_A_hli;
        // CP_A_B;
        // IF_Z goto knows_move;
        if(hl->moves[i] == b) {
        // knows_move:
            // LD_HL(mKnowsMove_KnowsMoveText);
            // CALL(aPrintText);
            PrintText(KnowsMoveText);
            // SCF;
            // RET;
            return true;
        }
        // DEC_C;
        // IF_NZ goto loop;
    }
    // AND_A_A;
    // RET;
    return false;
}
