#include "../../constants.h"
#include "sine.h"

// void v_Sine(void){
// //  a = d * sin(e * pi/32)
//     // LD_A_E;
//     //calc_sine_wave ['?']

// }

//  a = d * sin(e * pi/32)
uint8_t v_Sine_Conv(uint8_t e, uint8_t d){
    static const uint16_t Sinetable[] = {
        0x0000,0x0019,0x0032,0x004a,0x0062,0x0079,0x008e,0x00a2,
        0x00b5,0x00c6,0x00d5,0x00e2,0x00ed,0x00f5,0x00fb,0x00ff,
        0x0100,0x00ff,0x00fb,0x00f5,0x00ed,0x00e2,0x00d5,0x00c6,
        0x00b5,0x00a2,0x008e,0x0079,0x0062,0x004a,0x0032,0x0019,
    };
    uint8_t a = e;
    // and %111111
	// cp  %100000
	// jr nc, .negative\@
    if((a & 0b111111) < 0b100000) {
    // .apply\@
        // ld e, a
        // ld a, d
        // ld d, 0
    // if _NARG == 1
        // ld hl, \1
    // else
        // ld hl, .sinetable\@
    // endc
        // add hl, de
        // add hl, de
        // uint16_t hl = mv_Sine_sinetable_u9392 + 2*(a & 0b111111);
        // ld e, [hl]
        // inc hl
        // ld d, [hl]
        // ld hl, 0
        uint16_t hl = Sinetable[a & 0b111111] * d;
        /*uint8_t carry;
        do {
        // .multiply\@ ; factor amplitude
            // srl a
            carry = d & 1;
            d = d >> 1;
            // jr nc, .even\@
            if(carry)
                hl += de.reg;// add hl, de
        // .even\@
            // sla e
            carry = (de.lo >> 7);
            de.lo = de.lo << 1;
            // rl d
            de.hi = (de.hi >> 7) | (de.hi << 1);
            // and a
            // jr nz, .multiply\@
        } while(d != 0);*/
        // ret
        // call .apply\@
        // ld a, h
        // ret
        return HIGH(hl);
    }
    else {
    // .negative\@
        // and %011111
        a &= 0b011111;
        // call .apply\@
    // .apply\@
        // ld e, a
        // ld a, d
        // ld d, 0
    // if _NARG == 1
        // ld hl, \1
    // else
        // ld hl, .sinetable\@
    // endc
        // add hl, de
        // add hl, de
        // uint16_t hl = mv_Sine_sinetable_u9392 + 2*a;
        // ld e, [hl]
        // inc hl
        // ld d, [hl]
        // ld hl, 0
        uint16_t hl = Sinetable[a] * d;
        // uint8_t carry;
        /*do {
        // .multiply\@ ; factor amplitude
            // srl a
            carry = d & 1;
            d = d >> 1;
            // jr nc, .even\@
            if(carry)
                hl += de.reg;// add hl, de
        // .even\@
            // sla e
            carry = (de.lo >> 7);
            de.lo = de.lo << 1;
            // rl d
            de.hi = (de.hi >> 7) | (de.hi << 1);
            // and a
            // jr nz, .multiply\@
        } while(d != 0);*/
        // ld a, h
        // xor $ff
        // inc a
        return (HIGH(hl) ^ 0xff) + 1;
        // ret
    }
    return 0;
}
