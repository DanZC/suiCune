#include "../constants.h"
#include "header.h"

void FarCall(void) {
    JP(mFarCall_hl);
}

void Bankswitch(void) {
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);
}

void JumpTable(void) {
    REG_HL = gb_read16(REG_HL + (REG_A * 2));
    JP_hl;
}

// void JumpTable(void) {
//     PUSH_DE;
//     LD_E_A;
//     LD_D(0);
//     ADD_HL_DE;
//     ADD_HL_DE;
//     LD_A_hli;
//     LD_H_hl;
//     LD_L_A;
//     POP_DE;
//     JP_hl;
// }

void Start(void) {
    NOP;
    JP(mv_Start);
}
