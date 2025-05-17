#include "../constants.h"
#include "header.h"

// Unused
void FarCall(void) {
    // JP(mFarCall_hl);
}

void Bankswitch(uint8_t new_bank) {
    hram.hROMBank = new_bank;
    gb_write(MBC3RomBank, new_bank);
}

// UNUSED
void JumpTable(void) {
    // REG_HL = gb_read16(REG_HL + (REG_A * 2));
    // JP_hl;
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

// Unused
void Start(void) {
    // NOP;
    // JP(mv_Start);
}
