#include "../constants.h"
#include "sram.h"

//  if invalid bank, sram is disabled
void OpenSRAM(uint8_t a){
    // CP_A(NUM_SRAM_BANKS);
    // IF_C goto valid;
    if(a >= NUM_SRAM_BANKS)
    {
    #if DEBUG
        // PUSH_AF;
        // PUSH_BC;
        // LD_B(1);

    // loop:
        // SLA_B;
        // DEC_A;
        // IF_NZ goto loop;
        uint8_t b = 1 << a;
        // LD_A(MBANK(asOpenedInvalidSRAM));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(asOpenedInvalidSRAM));
        // LD_A_addr(sOpenedInvalidSRAM);
        // OR_A_B;
        // LD_addr_A(sOpenedInvalidSRAM);
        gb_write(sOpenedInvalidSRAM, gb_read(sOpenedInvalidSRAM) | b);
        // POP_BC;
        // POP_AF;
    #endif
        // JR(mCloseSRAM);
        return CloseSRAM();
    }

//  switch to sram bank a
    // PUSH_AF;
//  latch clock data
    // LD_A(1);
    // LD_addr_A(MBC3LatchClock);
    gb_write(MBC3LatchClock, 1);
//  enable sram/clock write
    // LD_A(SRAM_ENABLE);
    // LD_addr_A(MBC3SRamEnable);
    gb_write(MBC3SRamEnable, SRAM_ENABLE);
//  select sram bank
    // POP_AF;
    // LD_addr_A(MBC3SRamBank);
    // RET;
    gb_write(MBC3SRamBank, a);
}

void CloseSRAM(void){
//  reset clock latch for next time
    gb_write(MBC3LatchClock, SRAM_DISABLE);
//  disable sram/clock write
    gb_write(MBC3SRamEnable, SRAM_DISABLE);
}
