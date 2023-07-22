#include "../constants.h"
#include "farcall.h"

void FarCall_de(void) {
    //  Call a:de.
    //  Preserves other registers.
    LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);
    CALL(aFarCall_JumpToDE);
    JR(mReturnFarCall);
}

void FarCall_JumpToDE(void) {
    JP(gb.cpu_reg.de + (gb.cpu_reg.de < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE)));
}

void FarCall_hl(void) {
    //  Call a:hl.
    //  Preserves other registers.
    LDH_addr_A(hTempBank);
    LDH_A_addr(hROMBank);
    PUSH_AF;
    LDH_A_addr(hTempBank);
    RST(aBankswitch);
    // CALL(aFarCall_JumpToHL);
    CALL_hl;
    PEEK("Return from far call.");
    // fallthrough

    return ReturnFarCall();
}

void ReturnFarCall(void) {
    //  We want to retain the contents of f.
    //  To do this, we can pop to bc instead of af.
    LD_A_B;
    LD_addr_A(wFarCallBC);
    LD_A_C;
    LD_addr_A(wFarCallBC + 1);

    //  Restore the working bank.
    POP_BC;
    LD_A_B;
    RST(aBankswitch);

    //  Restore the contents of bc.
    LD_A_addr(wFarCallBC);
    LD_B_A;
    LD_A_addr(wFarCallBC + 1);
    LD_C_A;
    RET;
}

void FarCall_JumpToHL(void) {
    JP_hl;
}
