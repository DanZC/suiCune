#include "../../constants.h"
#include "catch_tutorial_input.h"
#include "../../home/joypad.h"

void v_DudeAutoInput_A(void){
    // LD_HL(mDudeAutoInput_A);
    // JR(mv_DudeAutoInput);
    static const uint8_t DudeAutoInput_A[] = {
        NO_INPUT, 0x50,
        A_BUTTON, 0x00,
        NO_INPUT, 0xff,  // end
    };
    return v_DudeAutoInput(DudeAutoInput_A);
}

void v_DudeAutoInput_RightA(void){
    // LD_HL(mDudeAutoInput_RightA);
    // JR(mv_DudeAutoInput);
    static const uint8_t DudeAutoInput_RightA[] = {
        NO_INPUT, 0x08,
        D_RIGHT, 0x00,
        NO_INPUT, 0x08,
        A_BUTTON, 0x00,
        NO_INPUT, 0xff,  // end
    };
    return v_DudeAutoInput(DudeAutoInput_RightA);
}

void v_DudeAutoInput_DownA(void){
    // LD_HL(mDudeAutoInput_DownA);
    // JR(mv_DudeAutoInput);
    static const uint8_t DudeAutoInput_DownA[] = {
        // NO_INPUT, 0xfe,
        // NO_INPUT, 0xfe,
        // NO_INPUT, 0xfe,
        // NO_INPUT, 0xfe,
        NO_INPUT, 60,
        D_DOWN, 0x00,
        // NO_INPUT, 0xfe,
        // NO_INPUT, 0xfe,
        // NO_INPUT, 0xfe,
        // NO_INPUT, 0xfe,
        NO_INPUT, 60,
        A_BUTTON, 0x00,
        NO_INPUT, 0xff,  // end
    };
    return v_DudeAutoInput(DudeAutoInput_DownA);
}

void v_DudeAutoInput(const uint8_t* hl){
    // LD_A(BANK(aDudeAutoInputs));
    // CALL(aStartAutoInput);
    // RET;
    return StartAutoInput(hl);
}

