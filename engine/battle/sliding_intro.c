#include "../../constants.h"
#include "sliding_intro.h"
#include "../../home/vblank.h"
#include "../../home/copy.h"
#include "../../home/palettes.h"
#include "../../home/delay.h"

// void BattleIntroSlidingPics_GBC(void){
//     LDH_A_addr(rSVBK);
//     PUSH_AF;
//     LD_A(MBANK(awLYOverrides));
//     LDH_addr_A(rSVBK);
//     CALL(aBattleIntroSlidingPics_subfunction1);
//     LD_A(LOW(rSCX));
//     LDH_addr_A(hLCDCPointer);
//     CALL(aBattleIntroSlidingPics_subfunction2);
//     XOR_A_A;
//     LDH_addr_A(hLCDCPointer);
//     POP_AF;
//     LDH_addr_A(rSVBK);
//     RET;


// subfunction1:
//     CALL(aBattleIntroSlidingPics_subfunction4);
//     LD_A(0x90);
//     LDH_addr_A(hSCX);
//     LD_A(0b11100100);
//     CALL(aDmgToCgbBGPals);
//     LD_DE((0b11100100 << 8) | 0b11100100);
//     CALL(aDmgToCgbObjPals);
//     RET;


// subfunction2:
//     LD_D(0x90);
//     LD_E(0x72);
//     LD_A(0x48);
//     INC_A;

// loop1:
//     PUSH_AF;

// loop2:
//     LDH_A_addr(rLY);
//     CP_A(0x60);
//     //IF_C goto loop2;
//     NOP;
//     LD_A_D;
//     LDH_addr_A(hSCX);
//     CALL(aBattleIntroSlidingPics_subfunction5);
//     INC_E;
//     INC_E;
//     DEC_D;
//     DEC_D;
//     POP_AF;
//     PUSH_AF;
//     CP_A(0x1);
//     IF_Z goto skip1;
//     PUSH_DE;
//     CALL(aBattleIntroSlidingPics_subfunction3);
//     POP_DE;


// skip1:
//     CALL(aDelayFrame);
//     POP_AF;
//     DEC_A;
//     IF_NZ goto loop1;
//     RET;


// subfunction3:
//     LD_HL(wVirtualOAMSprite00XCoord);
//     LD_C(0x12);  // 18
//     LD_DE(SPRITEOAMSTRUCT_LENGTH);

// loop3:
//     DEC_hl;
//     DEC_hl;
//     ADD_HL_DE;
//     DEC_C;
//     IF_NZ goto loop3;
//     RET;


// subfunction4:
//     LD_HL(wLYOverrides);
//     LD_A(0x90);
//     LD_BC(SCREEN_HEIGHT_PX);
//     CALL(aByteFill);
//     RET;


// subfunction5:
//     LD_HL(wLYOverrides);
//     LD_A_D;
//     LD_C(0x3e);  // 62

// loop4:
//     LD_hli_A;
//     DEC_C;
//     IF_NZ goto loop4;
//     LD_A_E;
//     LD_C(0x22);  // 34

// loop5:
//     LD_hli_A;
//     DEC_C;
//     IF_NZ goto loop5;
//     XOR_A_A;
//     LD_C(0x30);  // 48

// loop6:
//     LD_hli_A;
//     DEC_C;
//     IF_NZ goto loop6;
//     RET;

// }

static void BattleIntroSlidingPics_subfunction1(void);
static void BattleIntroSlidingPics_subfunction2(void);
static void BattleIntroSlidingPics_subfunction3(void);
// static void BattleIntroSlidingPics_subfunction4(void);
static void BattleIntroSlidingPics_subfunction5(uint8_t d, uint8_t e);


// static void BattleIntroSlidingPics_subfunction4(void) {
//     // LD_HL(wLYOverrides);
//     // LD_A(0x90);
//     // LD_BC(SCREEN_HEIGHT_PX);
//     // CALL(aByteFill);
//     ByteFill_Conv(wLYOverrides, SCREEN_HEIGHT_PX, 0x90);
// }

static void BattleIntroSlidingPics_subfunction1(void) {
    // CALL(aBattleIntroSlidingPics_subfunction4);
    // BattleIntroSlidingPics_subfunction4();
    ByteFill_Conv(wLYOverrides, SCREEN_HEIGHT_PX, 0x90);
    // LD_A(0x90);
    // LDH_addr_A(hSCX);
    gb_write(hSCX, 0x90);
    // LD_A(0b11100100);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // LD_DE((0b11100100 << 8) | 0b11100100);
    // CALL(aDmgToCgbObjPals);
    DmgToCgbObjPals_Conv(0b11100100, 0b11100100);
    // RET;
}

static void BattleIntroSlidingPics_subfunction3(void) {
    // LD_HL(wVirtualOAMSprite00XCoord);
    // LD_C(0x12);  // 18
    // LD_DE(SPRITEOAMSTRUCT_LENGTH);
    uint16_t hl = wVirtualOAMSprite00XCoord;
    uint8_t i = 0x12;

    do {
        // DEC_hl;
        // DEC_hl;
        gb_write(hl, gb_read(hl) - 1);
        gb_write(hl, gb_read(hl) - 1);
        // ADD_HL_DE;
        hl += SPRITEOAMSTRUCT_LENGTH;
        // DEC_C;
        // IF_NZ goto loop3;
    } while(--i != 0);
    // RET;
}

static void BattleIntroSlidingPics_subfunction5(uint8_t d, uint8_t e) {
    // LD_HL(wLYOverrides);
    // LD_A_D;
    // LD_C(0x3e);  // 62
    uint16_t hl = wLYOverrides;
    uint8_t c = 0x3e; // 62

    do {
        // LD_hli_A;
        gb_write(hl++, d);
        // DEC_C;
        // IF_NZ goto loop4;
    } while(--c != 0);
    // LD_A_E;
    // LD_C(0x22);  // 34
    c = 0x22; // 34

    do {
        // LD_hli_A;
        gb_write(hl++, e);
        // DEC_C;
        // IF_NZ goto loop5;
    } while(--c != 0);
    // XOR_A_A;
    // LD_C(0x30);  // 48
    c = 0x30; // 48

    do {
        // LD_hli_A;
        gb_write(hl++, 0);
        // DEC_C;
        // IF_NZ goto loop6;
    } while(--c != 0);
    // RET;
}

static void BattleIntroSlidingPics_subfunction2(void) {
    // LD_D(0x90);
    // LD_E(0x72);
    // LD_A(0x48);
    // INC_A;
    uint8_t d = 0x90, e = 0x72, count = 0x48 + 1;

    do {
        // PUSH_AF;

    // loop2:
    //     LDH_A_addr(rLY);
    //     CP_A(0x60);
    //     IF_C goto loop2;
        // NOP;
        // LD_A_D;
        // LDH_addr_A(hSCX);
        gb_write(hSCX, d);
        // CALL(aBattleIntroSlidingPics_subfunction5);
        BattleIntroSlidingPics_subfunction5(d, e);
        // INC_E;
        // INC_E;
        e += 2;
        // DEC_D;
        // DEC_D;
        d -= 2;
        // POP_AF;
        // PUSH_AF;

        // CP_A(0x1);
        // IF_Z goto skip1;
        if(count != 0x1) {
            // PUSH_DE;
            BattleIntroSlidingPics_subfunction3();
            // CALL(aBattleIntroSlidingPics_subfunction3);
            // POP_DE;
        }

        // CALL(aDelayFrame);
        DelayFrame();
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--count != 0);
    // RET;
}

void BattleIntroSlidingPics(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t tempVBK = gb_read(rSVBK);
    // LD_A(MBANK(awLYOverrides));
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, MBANK(awLYOverrides));

    // CALL(aBattleIntroSlidingPics_subfunction1);
    BattleIntroSlidingPics_subfunction1();
    // LD_A(LOW(rSCX));
    // LDH_addr_A(hLCDCPointer);
    gb_write(hLCDCPointer, LOW(rSCX));
    // CALL(aBattleIntroSlidingPics_subfunction2);
    BattleIntroSlidingPics_subfunction2();
    // XOR_A_A;
    // LDH_addr_A(hLCDCPointer);
    gb_write(hLCDCPointer, 0);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, tempVBK);
    // RET;
}
