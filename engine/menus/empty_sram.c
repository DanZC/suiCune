#include "../../constants.h"
#include "empty_sram.h"
#include "../../home/sram.h"
#include "../../home/copy.h"

static void EmptyBank(uint8_t bank) {
    // CALL(aOpenSRAM);
    OpenSRAM(bank);
    // LD_HL(SRAM_Begin);
    // LD_BC(SRAM_End - SRAM_Begin);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_GB(SRAM_Begin, SRAM_End - SRAM_Begin, 0x0);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void EmptyAllSRAMBanks(void){
    // LD_A(0);
    // CALL(aEmptyAllSRAMBanks_EmptyBank);
    EmptyBank(0);
    // LD_A(1);
    // CALL(aEmptyAllSRAMBanks_EmptyBank);
    EmptyBank(1);
    // LD_A(2);
    // CALL(aEmptyAllSRAMBanks_EmptyBank);
    EmptyBank(2);
    // LD_A(3);
    // CALL(aEmptyAllSRAMBanks_EmptyBank);
    EmptyBank(3);
    // RET;
}
