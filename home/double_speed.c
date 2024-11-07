#include "../constants.h"
#include "double_speed.h"

//  The CGB hardware introduces Double Speed Mode.
//  While active, the clock speed is doubled.

//  The hardware can switch between normal speed
//  and double speed at any time, but LCD output
//  collapses during the switch.

void DoubleSpeed(void){
    // LD_HL(rKEY1);
    // BIT_hl(7);
    // JR_Z (mSwitchSpeed);
    gb.cgb.doubleSpeed = 1;
    // RET;
}

void NormalSpeed(void){
    // LD_HL(rKEY1);
    // BIT_hl(7);
    // RET_Z ;
    gb.cgb.doubleSpeed = 0;
    // return SwitchSpeed();
}

void SwitchSpeed(void){
    // SET_hl(0);
    // XOR_A_A;
    // LDH_addr_A(rIF);
    // LDH_addr_A(rIE);
    // LD_A(0x30);
    // LDH_addr_A(rJOYP);
    //stop ['']  // rgbasm adds a nop after this instruction by default
    // RET;
}
