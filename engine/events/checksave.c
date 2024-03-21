#include "../../constants.h"
#include "checksave.h"
#include "../../home/sram.h"

void CheckSave(void){
    LD_A(BANK(sCheckValue1));  // aka BANK(sCheckValue2)
    CALL(aOpenSRAM);
    LD_A_addr(sCheckValue1);
    LD_B_A;
    LD_A_addr(sCheckValue2);
    LD_C_A;
    CALL(aCloseSRAM);
    LD_A_B;
    CP_A(SAVE_CHECK_VALUE_1);
    IF_NZ goto ok;
    LD_A_C;
    CP_A(SAVE_CHECK_VALUE_2);
    IF_NZ goto ok;
    LD_C(0x1);
    RET;


ok:
    LD_C(0x0);
    RET;

}

uint8_t CheckSave_Conv(void){
    // LD_A(BANK(sCheckValue1));  // aka BANK(sCheckValue2)
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(sCheckValue1));
    // LD_A_addr(sCheckValue1);
    // LD_B_A;
    uint8_t b = gb_read(sCheckValue1);
    // LD_A_addr(sCheckValue2);
    // LD_C_A;
    uint8_t c = gb_read(sCheckValue2);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A_B;
    // CP_A(SAVE_CHECK_VALUE_1);
    // IF_NZ goto ok;
    // LD_A_C;
    // CP_A(SAVE_CHECK_VALUE_2);
    // IF_NZ goto ok;
    if(b == SAVE_CHECK_VALUE_1 && c == SAVE_CHECK_VALUE_2) {
        // LD_C(0x1);
        // RET;
        return 0x1;
    }
// ok:
    // LD_C(0x0);
    // RET;
    return 0x0;
}
