#include "../constants.h"
#include "delay.h"
#include "vblank.h"

void DelayFrame_Old(void){
    //  Wait for one frame
    LD_A(1);
    LD_addr_A(wVBlankOccurred);

//  Wait for the next VBlank, halting to conserve battery

halt:
        //halt ['']  // rgbasm adds a nop after this instruction by default
    LD_A_addr(wVBlankOccurred);
    AND_A_A;
    IF_NZ goto halt;
    RET;

}

void DelayFrame(void){
    //  Wait for one frame
    gb_finish_frame();
    VBlank_Conv();
    // do {
    //     gb_finish_frame();
    //     CALL(aVBlank);
    //     // VBlank();
    // } while(gb_read(wVBlankOccurred) != 0);
    // gb_finish_frame();
    // CALL(aVBlank);
    // CALL(aVBlank);
    // gb_finish_frame();
    // gb.gb_reg.LY = 0;
}

void DelayFrames(void){
    //  Wait c frames
    do {
        CALL(aDelayFrame);
    } while(--REG_C != 0);
    // RET;

}


void DelayFrames_Conv(uint8_t count) {
    do {
        //  Wait for one frame
        VBlank_Conv();
        gb_finish_frame();
    } while(--count > 0);
}