#include "../constants.h"
#include "call_regs.h"

//  Register aliases

void v_hl_(void) {
        // JP_hl;
}

void v_de_(void) {
        // JP(gb.cpu_reg.de + (gb.cpu_reg.de < 0x4000 ? 0 : ((gb.selected_rom_bank - 1) * ROM_BANK_SIZE)));
}
