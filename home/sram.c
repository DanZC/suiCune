#include "../constants.h"
#include "sram.h"

void OpenSRAM(void){
//  if invalid bank, sram is disabled
    CP_A(NUM_SRAM_BANKS);
    IF_C goto valid;
#if defined(_DEBUG) && !defined(_MSC_VER)
    PUSH_AF;
    PUSH_BC;
    LD_B(1);

loop:
    SLA_B;
    DEC_A;
    IF_NZ goto loop;
    LD_A(BANK(sOpenedInvalidSRAM));
    CALL(aOpenSRAM);
    LD_A_addr(sOpenedInvalidSRAM);
    OR_A_B;
    LD_addr_A(sOpenedInvalidSRAM);
    POP_BC;
    POP_AF;
#endif
    JR(mCloseSRAM);


valid:
//  switch to sram bank a
    PUSH_AF;
//  latch clock data
    LD_A(1);
    LD_addr_A(MBC3LatchClock);
//  enable sram/clock write
    LD_A(SRAM_ENABLE);
    LD_addr_A(MBC3SRamEnable);
//  select sram bank
    POP_AF;
    LD_addr_A(MBC3SRamBank);
    RET;

}

//  if invalid bank, sram is disabled
void OpenSRAM_Conv(uint8_t a){
    // CP_A(NUM_SRAM_BANKS);
    // IF_C goto valid;
    if(a >= NUM_SRAM_BANKS)
    {
    #if defined(_DEBUG) && !defined(_MSC_VER)
        PUSH_AF;
        PUSH_BC;
        LD_B(1);

    loop:
        SLA_B;
        DEC_A;
        IF_NZ goto loop;
        LD_A(BANK(sOpenedInvalidSRAM));
        CALL(aOpenSRAM);
        LD_A_addr(sOpenedInvalidSRAM);
        OR_A_B;
        LD_addr_A(sOpenedInvalidSRAM);
        POP_BC;
        POP_AF;
    #endif
        // JR(mCloseSRAM);
        return CloseSRAM_Conv();
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
    PUSH_AF;
    LD_A(SRAM_DISABLE);
//  reset clock latch for next time
    LD_addr_A(MBC3LatchClock);
//  disable sram/clock write
    LD_addr_A(MBC3SRamEnable);
    POP_AF;
    RET;

}

void CloseSRAM_Conv(void){
//  reset clock latch for next time
    gb_write(MBC3LatchClock, SRAM_DISABLE);
//  disable sram/clock write
    gb_write(MBC3SRamEnable, SRAM_DISABLE);
}
