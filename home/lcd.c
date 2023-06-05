#include "../constants.h"
#include "lcd.h"

//  LCD handling

void Function547(void) {
        //  //  unreferenced
    LDH_A_addr(hLCDCPointer);
    CP_A(LOW(rSCX));
    RET_NZ;
    LD_C_A;
    LD_A_addr(wLYOverrides);
    LDH_c_A;
    RET;
}

void LCD(void) {  // called from the rendering function, once per line
    if (gb_read(hLCDCPointer)) {
        gb_write(0xFF00 | gb_read(hLCDCPointer), gb_read(wLYOverrides + gb.gb_reg.LY));
    }
}

void DisableLCD(void) {
        //  Turn the LCD off

    //  Don't need to do anything if the LCD is already off
    LDH_A_addr(rLCDC);
    BIT_A(rLCDC_ENABLE);
    RET_Z;

    XOR_A_A;
    LDH_addr_A(rIF);
    LDH_A_addr(rIE);
    LD_B_A;

    //  Disable VBlank
    RES_A(VBLANK);
    LDH_addr_A(rIE);

wait:
        //  Wait until VBlank would normally happen
    LDH_A_addr(rLY);
    CP_A(LY_VBLANK + 1);
    // IF_NZ goto wait;

    LDH_A_addr(rLCDC);
    AND_A(~(1 << rLCDC_ENABLE));
    LDH_addr_A(rLCDC);

    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A_B;
    LDH_addr_A(rIE);
    RET;
}

void EnableLCD(void) {
        LDH_A_addr(rLCDC);
    SET_A(rLCDC_ENABLE);
    LDH_addr_A(rLCDC);
    RET;
}
