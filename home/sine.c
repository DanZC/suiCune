#include "../constants.h"
#include "sine.h"
#include "../engine/math/sine.h"

void Cosine(void){
    //  //  unreferenced
//  a = d * cos(a * pi/32)
    ADD_A(0b010000);  // cos(x) = sin(x + pi/2)
// fallthrough
    return Sine();
}

void Sine(void){
    //  a = d * sin(a * pi/32)
    // LD_E_A;
    // HOMECALL(av_Sine);
    // RET;
    REG_A = v_Sine_Conv(REG_A, REG_D);

}

uint8_t Sine_Conv(uint8_t a, uint8_t d){
    //  a = d * sin(a * pi/32)
    // LD_E_A;
    // HOMECALL(av_Sine);
    // RET;
    return v_Sine_Conv(a, d);
}
