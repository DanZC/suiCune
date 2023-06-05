#include "../../constants.h"
#include "savemenu_copytilemapatonce.h"

void SaveMenu_CopyTilemapAtOnce(void) {
    SET_PC(aSaveMenu_CopyTilemapAtOnce);
    LDH_A_addr(hCGB);
    AND_A_A;
    JP_Z(mWaitBGMap);

    //  The following is a modified version of _CopyTilemapAtOnce
    //  that waits for [rLY] to be $60 instead of $80 - 1.
    LDH_A_addr(hBGMapMode);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    LDH_A_addr(hMapAnims);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hMapAnims);

wait:

    LDH_A_addr(rLY);
    CP_A(0x60);
    // IF_C goto wait;

    NOP;
    LD_A(MBANK(avBGMap2));
    LDH_addr_A(rVBK);
    hlcoord(0, 0, wAttrmap);
    CALL(aSaveMenu_CopyTilemapAtOnce_CopyBGMapViaStack);
    LD_A(MBANK(avBGMap0));
    LDH_addr_A(rVBK);
    hlcoord(0, 0, wTilemap);
    CALL(aSaveMenu_CopyTilemapAtOnce_CopyBGMapViaStack);

wait2:

    LDH_A_addr(rLY);
    CP_A(0x60);
    // IF_C goto wait2;
    NOP;

    POP_AF;
    LDH_addr_A(hMapAnims);
    POP_AF;
    LDH_addr_A(hBGMapMode);
    RET;
}

void SaveMenu_CopyTilemapAtOnce_CopyBGMapViaStack(void) {
    //  Copy all tiles to vBGMap
    LD_addr_SP(hSPBuffer);
    LD_SP_HL;
    LDH_A_addr(hBGMapAddress + 1);
    LD_H_A;
    LD_L(0);
    LD_A(SCREEN_HEIGHT);
    LDH_addr_A(hTilesPerCycle);
    LD_B(1 << 1);  // not in v/hblank
    LD_C(LOW(rSTAT));

loop:

    for (int rept = 0; rept < SCREEN_WIDTH / 2; rept++) {
        POP_DE;
        //  if in v/hblank, wait until not in v/hblank

        // loop\@:

        LDH_A_c;
        AND_A_B;
        // IF_NZ goto loop\@;
        //  load vBGMap
        LD_hl_E;
        INC_L;
        LD_hl_D;
        INC_L;
    }

    LD_DE(BG_MAP_WIDTH - SCREEN_WIDTH);
    ADD_HL_DE;
    LDH_A_addr(hTilesPerCycle);
    DEC_A;
    LDH_addr_A(hTilesPerCycle);
    IF_NZ goto loop;

    LDH_A_addr(hSPBuffer);
    LD_L_A;
    LDH_A_addr(hSPBuffer + 1);
    LD_H_A;
    LD_SP_HL;
    RET;
}
