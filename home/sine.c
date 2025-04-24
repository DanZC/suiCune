#include "../constants.h"
#include "sine.h"
#include "../engine/math/sine.h"

uint8_t Cosine(uint8_t a, uint8_t d){
    //  //  unreferenced
//  a = d * cos(a * pi/32)
    // ADD_A(0b010000);  // cos(x) = sin(x + pi/2)
// fallthrough
    return Sine(a + 0b010000, d);
}

uint8_t Sine(uint8_t a, uint8_t d){
    //  a = d * sin(a * pi/32)
    // LD_E_A;
    // HOMECALL(av_Sine);
    // RET;
    return v_Sine(a, d);
}
