#include "../../constants.h"
#include "tmhm2.h"
#include "../../data/moves/tmhm_moves.h"

void CanLearnTMHMMove(void){
    LD_A_addr(wCurPartySpecies);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_HL(wBaseTMHM);
    PUSH_HL;

    LD_A_addr(wPutativeTMHMMove);
    LD_B_A;
    LD_C(0);
    LD_HL(mTMHMMoves);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto end;
    CP_A_B;
    IF_Z goto found;
    INC_C;
    goto loop;


found:
    POP_HL;
    LD_B(CHECK_FLAG);
    PUSH_DE;
    LD_D(0);
    PREDEF(pSmallFarFlagAction);
    POP_DE;
    RET;


end:
    POP_HL;
    LD_C(0);
    RET;

}

void GetTMHMMove(void){
    LD_A_addr(wTempTMHM);
    DEC_A;
    LD_HL(mTMHMMoves);
    LD_B(0);
    LD_C_A;
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wTempTMHM);
    RET;

// INCLUDE "data/moves/tmhm_moves.asm"

}

move_t GetTMHMMove_Conv(uint8_t tmhm){
    // LD_A_addr(wTempTMHM);
    // DEC_A;
    // LD_HL(mTMHMMoves);
    // LD_B(0);
    // LD_C_A;
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_addr_A(wTempTMHM);
    // RET;
    return TMHMMoves[tmhm-1];
}
