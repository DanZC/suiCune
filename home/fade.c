#include "../constants.h"
#include "fade.h"
#include "palettes.h"
#include "delay.h"

#define dc(a, b, c, d) ((a & 0x3) << 6) | ((b & 0x3) << 4) | ((c & 0x3) << 2) | (d & 0x3)

static const uint8_t IncGradGBPalTable[][3] = {
    {dc(3,3,3,3), dc(3,3,3,3), dc(3,3,3,3)}, // 00
    {dc(3,3,3,2), dc(3,3,3,2), dc(3,3,3,2)}, // 01
    {dc(3,3,2,1), dc(3,3,2,1), dc(3,3,2,1)}, // 02
    {dc(3,2,1,0), dc(3,2,1,0), dc(3,2,1,0)}, // 03
    {dc(3,2,1,0), dc(3,2,1,0), dc(3,2,1,0)}, // 04
    {dc(2,1,0,0), dc(2,1,0,0), dc(2,1,0,0)}, // 05
    {dc(1,0,0,0), dc(1,0,0,0), dc(1,0,0,0)}, // 06
    {dc(0,0,0,0), dc(0,0,0,0), dc(0,0,0,0)}, // 07
    {dc(3,3,3,3), dc(3,3,3,3), dc(3,3,3,3)}, // 08
    {dc(3,3,3,2), dc(3,3,3,2), dc(3,3,3,2)}, // 09
    {dc(3,3,2,1), dc(3,3,2,1), dc(3,3,2,1)}, // 10
    {dc(3,2,1,0), dc(3,2,1,0), dc(3,2,1,0)}, // 11
    {dc(3,2,1,0), dc(3,2,1,0), dc(3,2,1,0)}, // 12
    {dc(2,1,0,0), dc(2,1,0,0), dc(2,1,0,0)}, // 13
    {dc(1,0,0,0), dc(1,0,0,0), dc(1,0,0,0)}, // 14
    {dc(0,0,0,0), dc(0,0,0,0), dc(0,0,0,0)}, // 15
};

//  Functions to fade the screen in and out.

static void RotatePalettesRight(const uint8_t* pal, uint8_t amount);
static void RotatePalettesLeft(const uint8_t* pal, uint8_t amount);

void TimeOfDayFade(void){
    //  //  unreferenced
    LD_A_addr(wTimeOfDayPal);
    LD_B_A;
    LD_HL(mIncGradGBPalTable_11);
    LD_A_L;
    SUB_A_B;
    LD_L_A;
    IF_NC goto okay;
    DEC_H;


okay:
        LD_A_hli;
    LDH_addr_A(rBGP);
    LD_A_hli;
    LDH_addr_A(rOBP0);
    LD_A_hli;
    LDH_addr_A(rOBP1);
    RET;

}

void RotateFourPalettesRight(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto dmg;
    if(hram->hCGB) {
        // LD_HL(mIncGradGBPalTable_00);
        // LD_B(4);
        // JR(mRotatePalettesRight);
        return RotatePalettesRight(IncGradGBPalTable[0], 4);
    }
    // LD_HL(mIncGradGBPalTable_08);
    // LD_B(4);
    // JR(mRotatePalettesRight);
    return RotatePalettesRight(IncGradGBPalTable[8], 4);
}

void RotateThreePalettesRight(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto dmg;
    if(hram->hCGB) {
        // LD_HL(mIncGradGBPalTable_05);
        // LD_B(3);
        // JR(mRotatePalettesRight);
        return RotatePalettesRight(IncGradGBPalTable[5], 3);
    }
    // LD_HL(mIncGradGBPalTable_13);
    // LD_B(3);
    return RotatePalettesRight(IncGradGBPalTable[13], 3);
}

//  Rotate palettes to the right and fill with loaded colors from the left
//  If we're already at the leftmost color, fill with the leftmost color
static void RotatePalettesRight(const uint8_t* pal, uint8_t amount){
    do {
        // PUSH_DE;
        // LD_A_hli;
        // CALL(aDmgToCgbBGPals);
        DmgToCgbBGPals(*pal);
        pal++;
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        // CALL(aDmgToCgbObjPals);
        DmgToCgbObjPals(pal[1], pal[0]);
        pal += 2;
        // LD_C(8);
        // CALL(aDelayFrames);
        DelayFrames(8);
        // POP_DE;
        // DEC_B;
        // JR_NZ (mRotatePalettesRight);
    } while(--amount != 0);
    // RET;

}

void RotateFourPalettesLeft(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto dmg;
    if(hram->hCGB) {
        // LD_HL(mIncGradGBPalTable_04 - 1);
        // LD_B(4);
        // JR(mRotatePalettesLeft);
        return RotatePalettesLeft(&IncGradGBPalTable[4][-1], 4);
    }
    
    // LD_HL(mIncGradGBPalTable_12 - 1);
    // LD_B(4);
    // JR(mRotatePalettesLeft);
    return RotatePalettesLeft(&IncGradGBPalTable[12][-1], 4);
}

void RotateThreePalettesLeft(void){
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto dmg;
    if(hram->hCGB) {
        // LD_HL(mIncGradGBPalTable_07 - 1);
        // LD_B(3);
        // JR(mRotatePalettesLeft);
        return RotatePalettesLeft(&IncGradGBPalTable[07][-1], 3);
    }

    // LD_HL(mIncGradGBPalTable_15 - 1);
    // LD_B(3);
    return RotatePalettesLeft(&IncGradGBPalTable[15][-1], 3);
}

//  Rotate palettes to the left and fill with loaded colors from the right
//  If we're already at the rightmost color, fill with the rightmost color
static void RotatePalettesLeft(const uint8_t* pal, uint8_t amount){
    do {
        // PUSH_DE;
        // LD_A_hld;
        // LD_D_A;
        // LD_A_hld;
        // LD_E_A;
        // CALL(aDmgToCgbObjPals);
        DmgToCgbObjPals(pal[0], pal[-1]);
        pal -= 2;
        // LD_A_hld;
        // CALL(aDmgToCgbBGPals);
        DmgToCgbBGPals(pal[0]);
        pal--;
        // LD_C(8);
        // CALL(aDelayFrames);
        DelayFrames(8);
        // POP_DE;
        // DEC_B;
        // JR_NZ (mRotatePalettesLeft);
    } while(--amount != 0);
    // RET;
}

// void IncGradGBPalTable_00(void){
//     //dc 3,3,3,3, 3,3,3,3, 3,3,3,3
//     return IncGradGBPalTable_01();
// }

// void IncGradGBPalTable_01(void){
//     //dc 3,3,3,2, 3,3,3,2, 3,3,3,2
//     return IncGradGBPalTable_02();
// }

// void IncGradGBPalTable_02(void){
//     //dc 3,3,2,1, 3,3,2,1, 3,3,2,1
//     return IncGradGBPalTable_03();
// }

// void IncGradGBPalTable_03(void){
//     //dc 3,2,1,0, 3,2,1,0, 3,2,1,0

//     return IncGradGBPalTable_04();
// }

// void IncGradGBPalTable_04(void){
//     //dc 3,2,1,0, 3,2,1,0, 3,2,1,0
//     return IncGradGBPalTable_05();
// }

// void IncGradGBPalTable_05(void){
//     //dc 2,1,0,0, 2,1,0,0, 2,1,0,0
//     return IncGradGBPalTable_06();
// }

// void IncGradGBPalTable_06(void){
//     //dc 1,0,0,0, 1,0,0,0, 1,0,0,0

//     return IncGradGBPalTable_07();
// }

// void IncGradGBPalTable_07(void){
//     //dc 0,0,0,0, 0,0,0,0, 0,0,0,0
// //                            bgp      obp1     obp2
//     return IncGradGBPalTable_08();
// }

// void IncGradGBPalTable_08(void){
//     //dc 3,3,3,3, 3,3,3,3, 3,3,3,3
//     return IncGradGBPalTable_09();
// }

// void IncGradGBPalTable_09(void){
//     //dc 3,3,3,2, 3,3,3,2, 3,3,2,0
//     return IncGradGBPalTable_10();
// }

// void IncGradGBPalTable_10(void){
//     //dc 3,3,2,1, 3,2,1,0, 3,2,1,0
//     return IncGradGBPalTable_11();
// }

// void IncGradGBPalTable_11(void){
//     //dc 3,2,1,0, 3,1,0,0, 3,2,0,0

//     return IncGradGBPalTable_12();
// }

// void IncGradGBPalTable_12(void){
//     //dc 3,2,1,0, 3,1,0,0, 3,2,0,0
//     return IncGradGBPalTable_13();
// }

// void IncGradGBPalTable_13(void){
//     //dc 2,1,0,0, 2,0,0,0, 2,1,0,0
//     return IncGradGBPalTable_14();
// }

// void IncGradGBPalTable_14(void){
//     //dc 1,0,0,0, 1,0,0,0, 1,0,0,0

//     return IncGradGBPalTable_15();
// }

// void IncGradGBPalTable_15(void){
//     //dc 0,0,0,0, 0,0,0,0, 0,0,0,0

// }
