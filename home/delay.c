#include "../constants.h"
#include "delay.h"
#include "vblank.h"

void DelayFrame(void){
    //  Wait for one frame
    VBlank_Conv();
    gb.display.WY = gb.gb_reg.WY;
    gb.display.window_clear = 0;
    gb_finish_frame();
}

void DelayFrames(uint8_t count) {
    do {
        //  Wait for one frame
        DelayFrame();
    } while(--count > 0);
}