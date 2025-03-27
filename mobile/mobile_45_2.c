#include "../constants.h"
#include "mobile_45_2.h"
#include "../home/random.h"

void Function116567(void){
    // LD_HL(wc3f7);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wc3f7 != 0)
        return;
    // LD_HL(wc3f6);
    // INC_hl;
    wram->wc3f6++;

    while(1) {
    // asm_116570:
        // LD_A(0x7);
        // SLA_A;
        // LD_C_A;
        // LD_B(0);
        // LD_HL(mUnknown_1167eb);
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        // PUSH_DE;
        // POP_HL;
        const uint8_t* hl = Unknown_1167eb[0x7];
        // LD_A_addr(wc3f6);
        // SLA_A;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hli;
        // CP_A(0xfe);
        // IF_NZ goto asm_116595;
        if(hl[2*wram->wc3f6] != 0xfe) {
        // asm_116595:
            // LD_addr_A(wc3f5);
            wram->wc3f5 = hl[2*wram->wc3f6];
            // LD_A_hl;
            // LD_addr_A(wc3f7);
            wram->wc3f7 = hl[2*wram->wc3f6 + 1];
            // RET;
            return;
        }
        // XOR_A_A;
        // LD_addr_A(wc3f6);
        wram->wc3f6 = 0x0;
        // goto asm_116570;
    }
}

void Function11659d(void){
    // LD_A_addr(wc314);
    // CP_A(0x12);
    // RET_NC ;
    if(wram->wc314[0] >= 0x12)
        return;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mJumptable_1165af);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    return Jumptable_1165af();
}

void Jumptable_1165af(void){
    switch(wram->wc314[0]) {
        case 0:  Function11677e(); break;
        case 1:  Function1165d5(); break;
        case 2:  Function1165d8(); break;
        case 3:  Function1165e3(); break;
        case 4:  Function1165f5(); break;
        case 5:  Function116600(); break;
        case 6:  Function116615(); break;
        case 7:  Function116618(); break;
        case 8:  Function116623(); break;
        case 9:  Function116635(); break;
        case 10: Function116640(); break;
        case 11: Function116655(); break;
        case 12: Function11665c(); break;
        case 13: Function11668d(); break;
        case 14: Function11669f(); break;
        case 15: Function1166a2(); break;
        case 16: Function1166c4(); break;
        case 17: Function1166d6(); break;
        case 18: Function1166d6(); break;
    }
}

void Function1165d5(void){
    // CALL(aFunction11678e);
    Function11678e();

    return Function1165d8();
}

void Function1165d8(void){
    // LD_A(0x0);
    // LD_C_A;
    // LD_A(0xff);
    // LD_B_A;
    // LD_A(0xa8);
    // CALL(aFunction1166f4);
    Function1166f4(0xa8, 0xff, 0x0);

    return Function1165e3();
}

void Function1165e3(void){
    // CALL(aFunction116747);
    Function116747();
    // LD_A_addr(wc30e);
    // CP_A(0xe8);
    // RET_NZ ;
    if(wram->wc30e != 0xe8)
        return;
    // LD_A(0x1);
    // CALL(aFunction116780);
    // RET_C ;
    if(Function116780(0x1))
        return;
    // JP(mFunction116797);
    return Function116797();
}

void Function1165f5(void){
    // LD_A(0x1);
    // LD_C_A;
    // LD_A(0x1);
    // LD_B_A;
    // LD_A(0xe8);
    // CALL(aFunction1166f4);
    Function1166f4(0xe8, 0x1, 0x1);

    return Function116600();
}

void Function116600(void){
    // CALL(aFunction116747);
    Function116747();
    // LD_A_addr(wc30e);
    // CP_A(0xa8);
    // RET_NZ ;
    if(wram->wc30e != 0xa8)
        return;
    // LD_A(0x1);
    // CALL(aFunction116780);
    // RET_C ;
    if(Function116780(0x1))
        return;
    // LD_A(0x2);
    // LD_addr_A(wc314);
    wram->wc314[0] = 0x2;
    // RET;
}

void Function116615(void){
    // CALL(aFunction11678e);
    Function11678e();

    return Function116618();
}

void Function116618(void){
    // LD_A(0x3);
    // LD_C_A;
    // LD_A(0x1);
    // LD_B_A;
    // LD_A(0x28);
    // CALL(aFunction11671f);
    Function11671f(0x28, 0x1, 0x3);

    return Function116623();
}

void Function116623(void){
    // CALL(aFunction116747);
    Function116747();
    // LD_A_addr(wc30f);
    // CP_A(0xa0);
    // RET_NZ ;
    if(wram->wc30f != 0xa0)
        return;
    // LD_A(0x6);
    // CALL(aFunction116780);
    // RET_C ;
    if(Function116780(0x6))
        return;
    // JP(mFunction116797);
    return Function116797();
}

void Function116635(void){
    // LD_A(0x2);
    // LD_C_A;
    // LD_A(0xff);
    // LD_B_A;
    // LD_A(0xa0);
    // CALL(aFunction11671f);
    Function11671f(0xa0, 0xff, 0x2);

    return Function116640();
}

void Function116640(void){
    // CALL(aFunction116747);
    Function116747();
    // LD_A_addr(wc30f);
    // CP_A(0x28);
    // RET_NZ ;
    if(wram->wc30f != 0x28)
        return;
    // LD_A(0x6);
    // CALL(aFunction116780);
    // RET_C ;
    if(Function116780(0x6))
        return;
    // LD_A(0x7);
    // LD_addr_A(wc314);
    wram->wc314[0] = 0x7;
    // RET;

}

void Function116655(void){
    // XOR_A_A;
    // LD_addr_A(wc314 + 3);
    wram->wc314[3] = 0x0;
    // CALL(aFunction11678e);
    Function11678e();

    return Function11665c();
}

void Function11665c(void){
    // LD_HL(wc314 + 3);
    // LD_A(0x1);
    // XOR_A_hl;
    // LD_hl_A;
    wram->wc314[3] ^= 0x1;
    // ADD_A(0x4);
    // LD_C_A;
    uint8_t c = wram->wc314[3] + 0x4;
    // CALL(aFunction11679c);
    Function11679c(c);
    // LD_A_addr(wc314 + 3);
    // AND_A_A;
    // IF_NZ goto asm_116673;
    // LD_A(0x48);
    // goto asm_116675;

// asm_116673:
    // LD_A(0x78);

// asm_116675:
    // LD_addr_A(wc30f);
    wram->wc30f = (wram->wc314[3] != 0)? 0x78: 0x48;
    // CALL(aRandom);
    Random();
    // LDH_A_addr(hRandomAdd);
    // AND_A(0x7);
    uint8_t a = hram->hRandomAdd & 0x7;
    // SLA_A;
    // SLA_A;
    // SLA_A;
    // ADD_A(0x30);
    // LD_addr_A(wc30e);
    wram->wc30e = (a << 3) + 0x30;
    // CALL(aFunction116797);
    Function116797();

    return Function11668d();
}

void Function11668d(void){
    // LD_A_addr(wc311);
    // CP_A(0xff);
    // RET_NZ ;
    if(wram->wc311 != 0xff)
        return;
    // LD_A(0xb);
    // CALL(aFunction116780);
    // RET_C ;
    if(Function116780(0xb))
        return;
    // LD_A(0xc);
    // LD_addr_A(wc314);
    wram->wc314[0] = 0xc;
    // RET;
}

void Function11669f(void){
    // CALL(aFunction11678e);
    Function11678e();

    return Function1166a2();
}

void Function1166a2(void){
    // LD_A(0xa8);
    // LD_addr_A(wc30e);
    wram->wc30e = 0xa8;
    // LD_addr_A(wc3f1);
    wram->wc3f1 = 0xa8;
    // LD_A(0x60);
    // LD_addr_A(wc30f);
    wram->wc30f = 0x60;
    // LD_addr_A(wc3f3);
    wram->wc3f3 = 0x60;
    // LD_A(0xff);
    // LD_addr_A(wc314 + 2);
    wram->wc314[2] = 0xff;
    // XOR_A_A;
    // LD_addr_A(wc314 + 3);
    wram->wc314[3] = 0x0;
    // LD_A(0x0);
    // LD_C_A;
    // CALL(aFunction11679c);
    Function11679c(0x0);
    // CALL(aFunction116797);
    Function116797();

    return Function1166c4();
}

void Function1166c4(void){
    // CALL(aFunction116747);
    Function116747();
    // LD_A_addr(wc30e);
    // CP_A(0x58);
    // RET_NZ ;
    if(wram->wc30e != 0x58)
        return;
    // LD_A(0x6);
    // LD_C_A;
    // CALL(aFunction11679c);
    Function11679c(0x6);
    // CALL(aFunction116797);
    Function116797();

    return Function1166d6();
}

void Function1166d6(void){
    // CALL(aFunction116747);
    Function116747();
    // LD_A_addr(wc30e);
    // CP_A(0x48);
    // IF_NZ goto asm_1166e4;
    if(wram->wc30e == 0x48) {
        // XOR_A_A;
        // LD_addr_A(wc314 + 2);
        wram->wc314[2] = 0x0;
    }

// asm_1166e4:
    // LD_A_addr(wc311);
    // CP_A(0xff);
    // RET_NZ ;
    if(wram->wc311 != 0xff)
        return;
    // LD_A(0x4);
    // LD_addr_A(0xc319);
    wram->wc319 = 0x4;
    // XOR_A_A;
    // LD_addr_A(wc314);
    wram->wc314[0] = 0x0;
    // RET;
}

void Function1166f4(uint8_t a, uint8_t b, uint8_t c){
    // LD_addr_A(wc30e);
    wram->wc30e = a;
    // LD_A_B;
    // LD_addr_A(wc314 + 2);
    wram->wc314[2] = b;
    // XOR_A_A;
    // LD_addr_A(wc314 + 3);
    wram->wc314[3] = 0;
    // LD_HL(wc30f);
    uint8_t* hl = &wram->wc30f;
    uint8_t a2;

    do {
    // asm_116702:
        // CALL(aRandom);
        Random();
        // LDH_A_addr(hRandomAdd);
        // AND_A(0x7);
        a2 = hram->hRandomAdd & 0x7;
        // IF_Z goto asm_11670c;
        if(a2 != 0) {
            // DEC_A;
            a2--;
        }

    // asm_11670c:
        // SLA_A;
        // SLA_A;
        // SLA_A;
        // ADD_A(0x48);
        a2 = (a2 << 3) + 0x48;
        // CP_A_hl;
        // IF_Z goto asm_116702;
    } while(a2 == *hl);
    // LD_hl_A;
    *hl = a2;
    // CALL(aFunction11679c);
    Function11679c(c);
    // CALL(aFunction116797);
    Function116797();
    // RET;

}

void Function11671f(uint8_t a, uint8_t b, uint8_t c){
    // LD_addr_A(wc30f);
    wram->wc30f = a;
    // LD_A_B;
    // LD_addr_A(wc314 + 3);
    wram->wc314[3] = b;
    // XOR_A_A;
    // LD_addr_A(wc314 + 2);
    wram->wc314[2] = 0x0;
    // LD_HL(wc30e);
    uint8_t* hl = &wram->wc30e;
    uint8_t a2;

    do {
    // asm_11672d:
        // CALL(aRandom);
        Random();
        // LDH_A_addr(hRandomAdd);
        // AND_A(0x7);
        a2 = hram->hRandomAdd & 0x7;
        // SLA_A;
        // SLA_A;
        // SLA_A;
        // ADD_A(0x30);
        a2 = (a2 << 3) + 0x30;
        // CP_A_hl;
        // IF_Z goto asm_11672d;
    } while(a2 == *hl);
    // LD_hl_A;
    *hl = a2;
    // CALL(aFunction11679c);
    Function11679c(c);
    // CALL(aFunction116797);
    Function116797();
    // RET;
}

void Function116747(void){
    // LD_HL(wc30e);
    // LD_A_addr(wc314 + 2);
    // ADD_A_hl;
    // LD_hl_A;
    wram->wc30e += wram->wc314[2];
    // LD_HL(wc30f);
    // LD_A_addr(wc314 + 3);
    // ADD_A_hl;
    // LD_hl_A;
    wram->wc30f += wram->wc314[3];
    // RET;
}

void Function116758(void){
    uint8_t a;
    // LD_A_addr(wc30f);
    // CP_A(0x30);
    // IF_C goto asm_116770;
    // IF_Z goto asm_116770;
    if(wram->wc30f <= 0x30) {
    // asm_116770:
        // LD_A(0xc);
        a = 0xc;
        // goto asm_11677a;
    }
    // CP_A(0x38);
    // IF_C goto asm_116774;
    // IF_Z goto asm_116774;
    else if(wram->wc30f <= 0x38) {
    // asm_116774:
        // LD_A(0x8);
        a = 0x8;
        // goto asm_11677a;
    }
    // CP_A(0x40);
    // IF_C goto asm_116778;
    // IF_Z goto asm_116778;
    else if(wram->wc30f <= 0x40) {
    // asm_116778:
        // LD_A(0x4);
        a = 0x4;
    }
    else {
        // XOR_A_A;
        a = 0x0;
        // goto asm_11677a;
    }

// asm_11677a:
    // LD_addr_A(wc314 + 4);
    wram->wc314[4] = a;
    // RET;
}

bool Function11677e(void){
    // LD_A(0x0);

    return Function116780(0x0);
}

bool Function116780(uint8_t a){
    // LD_HL(wc314 + 1);
    // CP_A_hl;
    // IF_Z goto asm_11678c;
    if(wram->wc314[1] == a) {
    // asm_11678c:
        // AND_A_A;
        // RET;
        return false;
    }
    // LD_A_hl;
    // LD_addr_A(wc314);
    wram->wc314[0] = wram->wc314[1];
    // SCF;
    // RET;
    return true;
}

void Function11678e(void){
    // LD_HL(wc314);
    // LD_A_hl;
    // LD_addr_A(wc314 + 1);
    wram->wc314[1] = wram->wc314[0];
    // INC_hl;
    wram->wc314[0]++;
    // RET;

}

void Function116797(void){
    // LD_HL(wc314);
    // INC_hl;
    wram->wc314[0]++;
    // RET;
}

void Function11679c(uint8_t c){
    // LD_A_C;
    // LD_addr_A(wc311);
    wram->wc311 = c;
    // XOR_A_A;
    // LD_addr_A(wc312);
    wram->wc312 = 0x0;
    // JR(masm_1167af);
    return asm_1167af();
}

void Function1167a6(void){
    // LD_HL(wc313);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wc313 != 0)
        return;
    // LD_HL(wc312);
    // INC_hl;
    wram->wc312++;

    return asm_1167af();
}

void asm_1167af(void){
    uint8_t a;
    while(1) {
        // LD_A_addr(wc311);
        // CP_A(0xff);
        // RET_Z ;
        if(wram->wc311 == 0xff)
            return;
        // SLA_A;
        // LD_C_A;
        // LD_B(0);
        // LD_HL(mUnknown_1167eb);
        // ADD_HL_BC;
        const uint8_t* hl = Unknown_1167eb[wram->wc311];
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        // PUSH_DE;
        // POP_HL;
        // LD_A_addr(wc312);
        // SLA_A;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hli;
        a = hl[wram->wc312*2];
        // CP_A(0xff);
        // IF_Z goto asm_1167dc;
        if(a == 0xff) {
        // asm_1167dc:
            // LD_A(0xff);
            // LD_addr_A(wc311);
            wram->wc311 = 0xff;
            // LD_A(0xfd);
            a = 0xfd;
            goto asm_1167e3;
        }
        // CP_A(0xfe);
        // IF_NZ goto asm_1167e3;
        else if(a != 0xfe) {
        asm_1167e3:
            // LD_addr_A(wc310);
            wram->wc310 = a;
            // LD_A_hl;
            // LD_addr_A(wc313);
            wram->wc313 = hl[wram->wc312*2 + 1];
            // RET;
            return;
        }
        // XOR_A_A;
        // LD_addr_A(wc312);
        wram->wc312 = 0x0;
        // JR(masm_1167af);
    }
}

const uint8_t* const Unknown_1167eb[] = {
    Unknown_1167fb,
    Unknown_116808,
    Unknown_116867,
    Unknown_116870,
    Unknown_116815,
    Unknown_11683e,
    Unknown_116881,
    Unknown_1168ae,
};

const uint8_t Unknown_1167fb[] = {
    0x0, 0x6,
    0x1, 0x4,
    0x2, 0x4,
    0x3, 0x6,
    0x2, 0x4,
    0x1, 0x4,
    0xfe,
};

const uint8_t Unknown_116808[] = {
    0x4, 0x6,
    0x5, 0x4,
    0x6, 0x4,
    0x7, 0x6,
    0x6, 0x4,
    0x5, 0x4,
    0xfe
};

const uint8_t Unknown_116815[] = {
    0xfd, 0x20,
    0x8, 0xc,
    0x9, 0x24,
    0xa, 0x4,
    0xb, 0x8,
    0xa, 0x4,
    0x9, 0x6,
    0xc, 0x4,
    0xd, 0x8,
    0xc, 0x5,
    0x9, 0x24,
    0xa, 0x4,
    0xb, 0x8,
    0xa, 0x4,
    0x9, 0x6,
    0xc, 0x4,
    0xd, 0x8,
    0xc, 0x5,
    0x9, 0x8,
    0x8, 0x4,
    (uint8_t)-1,  // end
};

const uint8_t Unknown_11683e[] = {
    0xfd, 0x20,
    0xe,  0xc,
    0xf,  0x24,
    0x10, 0x4,
    0x11, 0x8,
    0x10, 0x4,
    0xf,  0x6,
    0x12, 0x4,
    0x13, 0x8,
    0x12, 0x5,
    0xf,  0x24,
    0x10, 0x4,
    0x11, 0x8,
    0x10, 0x4,
    0xf,  0x6,
    0x12, 0x4,
    0x13, 0x8,
    0x12, 0x5,
    0xf,  0x8,
    0xe,  0x4,
    (uint8_t)-1  // end
};

const uint8_t Unknown_116867[] = {
    0x14, 0x8,
    0x15, 0x8,
    0x16, 0x8,
    0x15, 0x8,
    0xfe
};

const uint8_t Unknown_116870[] = {
    0x17, 0x5,
    0x18, 0x5,
    0x19, 0x5,
    0x1a, 0x5,
    0x1b, 0x5,
    0x1a, 0x5,
    0x19, 0x5,
    0x18, 0x5,
    0xfe
};

const uint8_t Unknown_116881[] = {
    0x1c, 0x7,
    0x1d, 0x7,
    0x1e, 0xa,
    0x1f, 0xa,
    0x20, 0x5,
    0x21, 0x5,
    0x20, 0x5,
    0x21, 0x5,
    0x20, 0x18,
    0x22, 0x4,
    0x23, 0x2,
    0x22, 0x2,
    0x23, 0x2,
    0x22, 0x1,
    0x23, 0x1,
    0x22, 0x1,
    0x23, 0x4,
    0xfd, 0x1,
    0x23, 0x1,
    0xfd, 0x2,
    0x23, 0x2,
    0xfd, 0x40,
    (uint8_t)-1  // end
};

const uint8_t Unknown_1168ae[] = {
    0x24, 0x4,
    0x25, 0x4,
    0x26, 0x4,
    0x27, 0x4,
    0x28, 0x4,
    0x29, 0x4,
    0x2a, 0x4,
    0x2b, 0x4,
    0x2c, 0x4,
    0x2d, 0x4,
    0x2e, 0x4,
    0xfe
};

// Sprite data lists
const uint8_t* const Unknown_1168c5[] = {
    Unknown_116923,
    Unknown_116960,
    Unknown_1169a1,
    Unknown_1169de,
    Unknown_116a1b,
    Unknown_116a58,
    Unknown_116a99,
    Unknown_116ad6,
    Unknown_116d1b,
    Unknown_116d4c,
    Unknown_116d85,
    Unknown_116dbe,
    Unknown_116df7,
    Unknown_116e30,
    Unknown_116e69,
    Unknown_116e9a,
    Unknown_116ed3,
    Unknown_116f0c,
    Unknown_116f45,
    Unknown_116f7e,
    Unknown_116b13,
    Unknown_116b54,
    Unknown_116b95,
    Unknown_116bd6,
    Unknown_116c17,
    Unknown_116c58,
    Unknown_116c99,
    Unknown_116cda,
    Unknown_116fb7,
    Unknown_116fec,
    Unknown_117025,
    Unknown_117056,
    Unknown_117083,
    Unknown_1170c0,
    Unknown_1170fd,
    Unknown_11713a,
    Unknown_117177,
    Unknown_11719c,
    Unknown_1171c1,
    Unknown_1171e6,
    Unknown_11720b,
    Unknown_117230,
    Unknown_117255,
    Unknown_11727a,
    Unknown_11729f,
    Unknown_1172c4,
    Unknown_1172e9,
};

const uint8_t Unknown_116923[] = {
    0xf,
    0x0,  0x0,  0x1,  0xa,
    0x0,  0x8,  0x2,  0xd,
    0x0,  0x10, 0x3,  0xd,
    0x0,  0x18, 0x4,  0xd,
    0x8,  0x0,  0x11, 0xa,
    0x8,  0x8,  0x12, 0xa,
    0x8,  0x10, 0x13, 0xa,
    0x8,  0x18, 0x14, 0xd,
    0x10, 0x0,  0x21, 0xa,
    0x10, 0x8,  0x22, 0xa,
    0x10, 0x10, 0x23, 0xa,
    0x10, 0x18, 0x24, 0xa,
    0x18, 0x0,  0x31, 0xa,
    0x18, 0x8,  0x32, 0xa,
    0x18, 0x10, 0x33, 0xa,
};

const uint8_t Unknown_116960[] = {
    0x10,
    0x1,  0x0,  0x1,  0xa,
    0x1,  0x8,  0x2,  0xd,
    0x1,  0x10, 0x3,  0xd,
    0x1,  0x18, 0x4,  0xd,
    0x9,  0x0,  0x11, 0xa,
    0x9,  0x8,  0x12, 0xa,
    0x9,  0x10, 0x13, 0xa,
    0x9,  0x18, 0x14, 0xd,
    0x11, 0x0,  0x5,  0xa,
    0x11, 0x8,  0x6,  0xa,
    0x11, 0x10, 0x7,  0xa,
    0x11, 0x18, 0x34, 0xa,
    0x19, 0x0,  0x15, 0xa,
    0x19, 0x8,  0x16, 0xa,
    0x19, 0x10, 0x17, 0xa,
    0x19, 0x18, 0x35, 0xa,
};

const uint8_t Unknown_1169a1[] = {
    0xf,
    0x1,  0x0,  0x1,  0xa,
    0x1,  0x8,  0x2,  0xd,
    0x1,  0x10, 0x3,  0xd,
    0x1,  0x18, 0x4,  0xd,
    0x9,  0x0,  0x11, 0xa,
    0x9,  0x8,  0x12, 0xa,
    0x9,  0x10, 0x13, 0xa,
    0x9,  0x18, 0x14, 0xd,
    0x11, 0x0,  0x25, 0xa,
    0x11, 0x8,  0x26, 0xa,
    0x11, 0x10, 0x27, 0xa,
    0x11, 0x18, 0x34, 0xa,
    0x19, 0x8,  0x36, 0xa,
    0x19, 0x10, 0x37, 0xa,
    0x19, 0x18, 0x35, 0xa,
};

const uint8_t Unknown_1169de[] = {
    0xf,
    0x0,  0x0,  0x1,  0xa,
    0x0,  0x8,  0x2,  0xd,
    0x0,  0x10, 0x3,  0xd,
    0x0,  0x18, 0x4,  0xd,
    0x8,  0x0,  0x11, 0xa,
    0x8,  0x8,  0x12, 0xa,
    0x8,  0x10, 0x13, 0xa,
    0x8,  0x18, 0x14, 0xd,
    0x10, 0x0,  0x10, 0xa,
    0x10, 0x8,  0x20, 0xa,
    0x10, 0x10, 0x30, 0xa,
    0x10, 0x18, 0x24, 0xa,
    0x18, 0x0,  0x31, 0xa,
    0x18, 0x8,  0x32, 0xa,
    0x18, 0x10, 0x33, 0xa,
};

const uint8_t Unknown_116a1b[] = {
    0xf,
    0x0, 0x0, 0x4, 0x2d,
    0x0, 0x8, 0x3, 0x2d,
    0x0, 0x10, 0x2, 0x2d,
    0x0, 0x18, 0x1, 0x2a,
    0x8, 0x0, 0x14, 0x2d,
    0x8, 0x8, 0x13, 0x2a,
    0x8, 0x10, 0x12, 0x2a,
    0x8, 0x18, 0x11, 0x2a,
    0x10, 0x0, 0x24, 0x2a,
    0x10, 0x8, 0x23, 0x2a,
    0x10, 0x10, 0x22, 0x2a,
    0x10, 0x18, 0x21, 0x2a,
    0x18, 0x8, 0x33, 0x2a,
    0x18, 0x10, 0x32, 0x2a,
    0x18, 0x18, 0x31, 0x2a,
};

const uint8_t Unknown_116a58[] = {
    0x10,
    0x1, 0x0, 0x4, 0x2d,
    0x1, 0x8, 0x3, 0x2d,
    0x1, 0x10, 0x2, 0x2d,
    0x1, 0x18, 0x1, 0x2a,
    0x9, 0x0, 0x14, 0x2d,
    0x9, 0x8, 0x13, 0x2a,
    0x9, 0x10, 0x12, 0x2a,
    0x9, 0x18, 0x11, 0x2a,
    0x11, 0x0, 0x34, 0x2a,
    0x11, 0x8, 0x7, 0x2a,
    0x11, 0x10, 0x6, 0x2a,
    0x11, 0x18, 0x5, 0x2a,
    0x19, 0x0, 0x35, 0x2a,
    0x19, 0x8, 0x17, 0x2a,
    0x19, 0x10, 0x16, 0x2a,
    0x19, 0x18, 0x15, 0x2a,
};

const uint8_t Unknown_116a99[] = {
    0xf,
    0x1, 0x0, 0x4, 0x2d,
    0x1, 0x8, 0x3, 0x2d,
    0x1, 0x10, 0x2, 0x2d,
    0x1, 0x18, 0x1, 0x2a,
    0x9, 0x0, 0x14, 0x2d,
    0x9, 0x8, 0x13, 0x2a,
    0x9, 0x10, 0x12, 0x2a,
    0x9, 0x18, 0x11, 0x2a,
    0x11, 0x0, 0x34, 0x2a,
    0x11, 0x8, 0x27, 0x2a,
    0x11, 0x10, 0x26, 0x2a,
    0x11, 0x18, 0x25, 0x2a,
    0x19, 0x0, 0x35, 0x2a,
    0x19, 0x8, 0x37, 0x2a,
    0x19, 0x10, 0x36, 0x2a,
};

const uint8_t Unknown_116ad6[] = {
    0xf,
    0x0, 0x0, 0x4, 0x2d,
    0x0, 0x8, 0x3, 0x2d,
    0x0, 0x10, 0x2, 0x2d,
    0x0, 0x18, 0x1, 0x2a,
    0x8, 0x0, 0x14, 0x2d,
    0x8, 0x8, 0x13, 0x2a,
    0x8, 0x10, 0x12, 0x2a,
    0x8, 0x18, 0x11, 0x2a,
    0x10, 0x0, 0x24, 0x2a,
    0x10, 0x8, 0x30, 0x2a,
    0x10, 0x10, 0x20, 0x2a,
    0x10, 0x18, 0x10, 0x2a,
    0x18, 0x8, 0x33, 0x2a,
    0x18, 0x10, 0x32, 0x2a,
    0x18, 0x18, 0x31, 0x2a,
};

const uint8_t Unknown_116b13[] = {
    0x10,
    0x18, 0x0, 0x0, 0xb,
    0x18, 0x8, 0x8, 0xb,
    0x18, 0x10, 0x5c, 0xb,
    0x18, 0x18, 0x0, 0xb,
    0x10, 0x0, 0x0, 0xb,
    0x10, 0x8, 0x5d, 0xb,
    0x10, 0x10, 0x5e, 0xb,
    0x10, 0x18, 0x0, 0xb,
    0x8, 0x0, 0x50, 0xb,
    0x8, 0x8, 0x51, 0xb,
    0x8, 0x10, 0x52, 0xb,
    0x8, 0x18, 0x50, 0x2b,
    0x0, 0x0, 0x43, 0xb,
    0x0, 0x8, 0x44, 0xb,
    0x0, 0x10, 0x44, 0x2b,
    0x0, 0x18, 0x43, 0x2b,
};

const uint8_t Unknown_116b54[] = {
    0x10,
    0x19, 0x0, 0x0, 0xb,
    0x19, 0x8, 0x18, 0xb,
    0x19, 0x10, 0xc, 0xb,
    0x19, 0x18, 0x0, 0xb,
    0x11, 0x0, 0x42, 0xb,
    0x11, 0x8, 0x3a, 0xb,
    0x11, 0x10, 0x3a, 0x2b,
    0x11, 0x18, 0x42, 0x2b,
    0x9, 0x0, 0x58, 0xb,
    0x9, 0x8, 0x45, 0xb,
    0x9, 0x10, 0x45, 0x2b,
    0x9, 0x18, 0x58, 0x2b,
    0x1, 0x0, 0xd, 0xb,
    0x1, 0x8, 0x44, 0xb,
    0x1, 0x10, 0x44, 0x2b,
    0x1, 0x18, 0xd, 0x2b,
};

const uint8_t Unknown_116b95[] = {
    0x10,
    0x18, 0x0, 0x0, 0xb,
    0x18, 0x8, 0x5c, 0x2b,
    0x18, 0x10, 0x8, 0x2b,
    0x18, 0x18, 0x0, 0xb,
    0x10, 0x0, 0x0, 0xb,
    0x10, 0x8, 0x5e, 0x2b,
    0x10, 0x10, 0x5d, 0x2b,
    0x10, 0x18, 0x0, 0xb,
    0x8, 0x0, 0x50, 0xb,
    0x8, 0x8, 0x52, 0x2b,
    0x8, 0x10, 0x51, 0x2b,
    0x8, 0x18, 0x50, 0x2b,
    0x0, 0x0, 0x43, 0xb,
    0x0, 0x8, 0x44, 0xb,
    0x0, 0x10, 0x44, 0x2b,
    0x0, 0x18, 0x43, 0x2b,
};

const uint8_t Unknown_116bd6[] = {
    0x10,
    0x18, 0x0, 0x0, 0xa,
    0x18, 0x8, 0x56, 0xa,
    0x18, 0x10, 0x57, 0xa,
    0x18, 0x18, 0x0, 0xa,
    0x10, 0x0, 0x64, 0xa,
    0x10, 0x8, 0x4a, 0xa,
    0x10, 0x10, 0x4b, 0xa,
    0x10, 0x18, 0x71, 0xa,
    0x8, 0x0, 0x54, 0xa,
    0x8, 0x8, 0x55, 0xa,
    0x8, 0x10, 0x55, 0x2a,
    0x8, 0x18, 0x54, 0x2a,
    0x0, 0x0, 0x48, 0xa,
    0x0, 0x8, 0x49, 0xa,
    0x0, 0x10, 0x49, 0x2a,
    0x0, 0x18, 0x48, 0x2a,
};

const uint8_t Unknown_116c17[] = {
    0x10,
    0x19, 0x0, 0x0, 0xa,
    0x19, 0x8, 0x76, 0xa,
    0x19, 0x10, 0x77, 0xa,
    0x19, 0x18, 0x0, 0xa,
    0x11, 0x0, 0x64, 0xa,
    0x11, 0x8, 0x69, 0xa,
    0x11, 0x10, 0x6a, 0xa,
    0x11, 0x18, 0x6b, 0xa,
    0x9, 0x0, 0x6f, 0xa,
    0x9, 0x8, 0x70, 0xa,
    0x9, 0x10, 0x70, 0x2a,
    0x9, 0x18, 0x6f, 0x2a,
    0x1, 0x0, 0x63, 0xa,
    0x1, 0x8, 0x19, 0xa,
    0x1, 0x10, 0x19, 0x2a,
    0x1, 0x18, 0x63, 0x2a,
};

const uint8_t Unknown_116c58[] = {
    0x10,
    0x1a, 0x0, 0x6c, 0xa,
    0x1a, 0x8, 0x6d, 0xa,
    0x1a, 0x10, 0x6e, 0xa,
    0x1a, 0x18, 0x0, 0xa,
    0x12, 0x0, 0x5f, 0xa,
    0x12, 0x8, 0x60, 0xa,
    0x12, 0x10, 0x61, 0xa,
    0x12, 0x18, 0x62, 0xa,
    0xa, 0x0, 0x53, 0xa,
    0xa, 0x8, 0x55, 0xa,
    0xa, 0x10, 0x55, 0x2a,
    0xa, 0x18, 0x53, 0x2a,
    0x2, 0x0, 0x46, 0xa,
    0x2, 0x8, 0x47, 0xa,
    0x2, 0x10, 0x47, 0x2a,
    0x2, 0x18, 0x46, 0x2a,
};

const uint8_t Unknown_116c99[] = {
    0x10,
    0x19, 0x0, 0x0, 0x2a,
    0x19, 0x8, 0x77, 0x2a,
    0x19, 0x10, 0x76, 0x2a,
    0x19, 0x18, 0x0, 0x2a,
    0x11, 0x0, 0x6b, 0x2a,
    0x11, 0x8, 0x6a, 0x2a,
    0x11, 0x10, 0x69, 0x2a,
    0x11, 0x18, 0x64, 0x2a,
    0x9, 0x0, 0x6f, 0xa,
    0x9, 0x8, 0x70, 0xa,
    0x9, 0x10, 0x70, 0x2a,
    0x9, 0x18, 0x6f, 0x2a,
    0x1, 0x0, 0x63, 0xa,
    0x1, 0x8, 0x19, 0xa,
    0x1, 0x10, 0x19, 0x2a,
    0x1, 0x18, 0x63, 0x2a,
};

const uint8_t Unknown_116cda[] = {
    0x10,
    0x18, 0x0, 0x0, 0xa,
    0x18, 0x8, 0x57, 0x2a,
    0x18, 0x10, 0x56, 0x2a,
    0x18, 0x18, 0x0, 0xa,
    0x10, 0x0, 0x71, 0x2a,
    0x10, 0x8, 0x4b, 0x2a,
    0x10, 0x10, 0x4a, 0x2a,
    0x10, 0x18, 0x64, 0x2a,
    0x8, 0x0, 0x54, 0xa,
    0x8, 0x8, 0x55, 0xa,
    0x8, 0x10, 0x55, 0x2a,
    0x8, 0x18, 0x54, 0x2a,
    0x0, 0x0, 0x48, 0xa,
    0x0, 0x8, 0x49, 0xa,
    0x0, 0x10, 0x49, 0x2a,
    0x0, 0x18, 0x48, 0x2a,
};

const uint8_t Unknown_116d1b[] = {
    0xc,
    0x0, 0x0, 0x38, 0x4a,
    0x0, 0x8, 0x39, 0x4a,
    0x0, 0x10, 0x39, 0x6a,
    0x0, 0x18, 0x38, 0x6a,
    0x8, 0x0, 0x28, 0x4a,
    0x8, 0x8, 0x29, 0x4a,
    0x8, 0x10, 0x29, 0x6a,
    0x8, 0x18, 0x28, 0x6a,
    0x10, 0x0, 0x9, 0x4d,
    0x10, 0x8, 0x19, 0x4a,
    0x10, 0x10, 0x19, 0x6a,
    0x10, 0x18, 0x9, 0x6d,
};

const uint8_t Unknown_116d4c[] = {
    0xe,
    0x0, 0x8, 0x3b, 0x4a,
    0x0, 0x10, 0x3b, 0x6a,
    0x8, 0x0, 0x2a, 0x4a,
    0x8, 0x8, 0x2b, 0x4a,
    0x8, 0x10, 0x2b, 0x6a,
    0x8, 0x18, 0x2a, 0x6a,
    0x10, 0x0, 0x1a, 0x4a,
    0x10, 0x8, 0x1b, 0x4a,
    0x10, 0x10, 0x1b, 0x6a,
    0x10, 0x18, 0x1a, 0x6a,
    0x18, 0x0, 0xa, 0x4a,
    0x18, 0x8, 0xb, 0x4a,
    0x18, 0x10, 0xb, 0x6a,
    0x18, 0x18, 0xa, 0x6a,
};

const uint8_t Unknown_116d85[] = {
    0xe,
    0x0, 0x0, 0x35, 0x2a,
    0x0, 0x8, 0x3c, 0x4a,
    0x0, 0x10, 0x3d, 0x4a,
    0x0, 0x18, 0x3e, 0x4a,
    0x8, 0x0, 0x2c, 0x4a,
    0x8, 0x8, 0x2d, 0x4a,
    0x8, 0x10, 0x2e, 0x4a,
    0x8, 0x18, 0x2f, 0x4a,
    0x10, 0x0, 0x1c, 0x4a,
    0x10, 0x8, 0x1d, 0x4a,
    0x10, 0x10, 0x1e, 0x4d,
    0x10, 0x18, 0x1f, 0x4d,
    0x18, 0x10, 0xe, 0x4d,
    0x18, 0x18, 0xf, 0x4a,
};

const uint8_t Unknown_116dbe[] = {
    0xe,
    0x0, 0x0, 0x65, 0x4a,
    0x0, 0x8, 0x66, 0x4a,
    0x0, 0x10, 0x67, 0x4a,
    0x0, 0x18, 0x68, 0x4a,
    0x8, 0x8, 0x59, 0x4a,
    0x8, 0x10, 0x5a, 0x4a,
    0x8, 0x18, 0x5b, 0x4a,
    0x10, 0x0, 0x4c, 0x4a,
    0x10, 0x8, 0x4d, 0x4d,
    0x10, 0x10, 0x4e, 0x4d,
    0x10, 0x18, 0x4f, 0x4a,
    0x18, 0x0, 0x3f, 0x4d,
    0x18, 0x8, 0x40, 0x4d,
    0x18, 0x10, 0x41, 0x4d,
};

const uint8_t Unknown_116df7[] = {
    0xe,
    0x0, 0x0, 0x3e, 0x6a,
    0x0, 0x8, 0x3d, 0x6a,
    0x0, 0x10, 0x3c, 0x6a,
    0x0, 0x18, 0x35, 0xa,
    0x8, 0x0, 0x2f, 0x6a,
    0x8, 0x8, 0x2e, 0x6a,
    0x8, 0x10, 0x2d, 0x6a,
    0x8, 0x18, 0x2c, 0x6a,
    0x10, 0x0, 0x1f, 0x6d,
    0x10, 0x8, 0x1e, 0x6d,
    0x10, 0x10, 0x1d, 0x6a,
    0x10, 0x18, 0x1c, 0x6a,
    0x18, 0x0, 0xf, 0x6a,
    0x18, 0x8, 0xe, 0x6d,
};

const uint8_t Unknown_116e30[] = {
    0xe,
    0x0, 0x0, 0x68, 0x6a,
    0x0, 0x8, 0x67, 0x6a,
    0x0, 0x10, 0x66, 0x6a,
    0x0, 0x18, 0x65, 0x6a,
    0x8, 0x0, 0x5b, 0x6a,
    0x8, 0x8, 0x5a, 0x6a,
    0x8, 0x10, 0x59, 0x6a,
    0x10, 0x0, 0x4f, 0x6a,
    0x10, 0x8, 0x4e, 0x6d,
    0x10, 0x10, 0x4d, 0x6d,
    0x10, 0x18, 0x4c, 0x6a,
    0x18, 0x8, 0x41, 0x6d,
    0x18, 0x10, 0x40, 0x6d,
    0x18, 0x18, 0x3f, 0x6d,
};

const uint8_t Unknown_116e69[] = {
    0xc,
    0x8, 0x0, 0x9, 0xd,
    0x8, 0x8, 0x19, 0xa,
    0x8, 0x10, 0x19, 0x2a,
    0x8, 0x18, 0x9, 0x2d,
    0x10, 0x0, 0x28, 0xa,
    0x10, 0x8, 0x29, 0xa,
    0x10, 0x10, 0x29, 0x2a,
    0x10, 0x18, 0x28, 0x2a,
    0x18, 0x0, 0x38, 0xa,
    0x18, 0x8, 0x39, 0xa,
    0x18, 0x10, 0x39, 0x2a,
    0x18, 0x18, 0x38, 0x2a,
};

const uint8_t Unknown_116e9a[] = {
    0xe,
    0x0, 0x0, 0xa, 0xa,
    0x0, 0x8, 0xb, 0xa,
    0x0, 0x10, 0xb, 0x2a,
    0x0, 0x18, 0xa, 0x2a,
    0x8, 0x0, 0x1a, 0xa,
    0x8, 0x8, 0x1b, 0xa,
    0x8, 0x10, 0x1b, 0x2a,
    0x8, 0x18, 0x1a, 0x2a,
    0x10, 0x0, 0x2a, 0xa,
    0x10, 0x8, 0x2b, 0xa,
    0x10, 0x10, 0x2b, 0x2a,
    0x10, 0x18, 0x2a, 0x2a,
    0x18, 0x8, 0x3b, 0xa,
    0x18, 0x10, 0x3b, 0x2a,
};

const uint8_t Unknown_116ed3[] = {
    0xe,
    0x0, 0x10, 0xe, 0xd,
    0x0, 0x18, 0xf, 0xa,
    0x8, 0x0, 0x1c, 0xa,
    0x8, 0x8, 0x1d, 0xa,
    0x8, 0x10, 0x1e, 0xd,
    0x8, 0x18, 0x1f, 0xd,
    0x10, 0x0, 0x2c, 0xa,
    0x10, 0x8, 0x2d, 0xa,
    0x10, 0x10, 0x2e, 0xa,
    0x10, 0x18, 0x2f, 0xa,
    0x18, 0x0, 0x35, 0x6a,
    0x18, 0x8, 0x3c, 0xa,
    0x18, 0x10, 0x3d, 0xa,
    0x18, 0x18, 0x3e, 0xa,
};

const uint8_t Unknown_116f0c[] = {
    0xe,
    0x0, 0x0, 0x3f, 0xd,
    0x0, 0x8, 0x40, 0xd,
    0x0, 0x10, 0x41, 0xd,
    0x8, 0x0, 0x4c, 0xa,
    0x8, 0x8, 0x4d, 0xd,
    0x8, 0x10, 0x4e, 0xd,
    0x8, 0x18, 0x4f, 0xa,
    0x10, 0x8, 0x59, 0xa,
    0x10, 0x10, 0x5a, 0xa,
    0x10, 0x18, 0x5b, 0xa,
    0x18, 0x0, 0x65, 0xa,
    0x18, 0x8, 0x66, 0xa,
    0x18, 0x10, 0x67, 0xa,
    0x18, 0x18, 0x68, 0xa,
};

const uint8_t Unknown_116f45[] = {
    0xe,
    0x0, 0x0, 0xf, 0x2a,
    0x0, 0x8, 0xe, 0x2d,
    0x8, 0x0, 0x1f, 0x2d,
    0x8, 0x8, 0x1e, 0x2d,
    0x8, 0x10, 0x1d, 0x2a,
    0x8, 0x18, 0x1c, 0x2a,
    0x10, 0x0, 0x2f, 0x2a,
    0x10, 0x8, 0x2e, 0x2a,
    0x10, 0x10, 0x2d, 0x2a,
    0x10, 0x18, 0x2c, 0x2a,
    0x18, 0x0, 0x3e, 0x2a,
    0x18, 0x8, 0x3d, 0x2a,
    0x18, 0x10, 0x3c, 0x2a,
    0x18, 0x18, 0x35, 0x4a,
};

const uint8_t Unknown_116f7e[] = {
    0xe,
    0x0, 0x8, 0x41, 0x2d,
    0x0, 0x10, 0x40, 0x2d,
    0x0, 0x18, 0x3f, 0x2d,
    0x8, 0x0, 0x4f, 0x2a,
    0x8, 0x8, 0x4e, 0x2d,
    0x8, 0x10, 0x4d, 0x2d,
    0x8, 0x18, 0x4c, 0x2a,
    0x10, 0x0, 0x5b, 0x2a,
    0x10, 0x8, 0x5a, 0x2a,
    0x10, 0x10, 0x59, 0x2a,
    0x18, 0x0, 0x68, 0x2a,
    0x18, 0x8, 0x67, 0x2a,
    0x18, 0x10, 0x66, 0x2a,
    0x18, 0x18, 0x65, 0x2a,
};

const uint8_t Unknown_116fb7[] = {
    0xd,
    0xfa, 0x0, 0x72, 0xa,
    0xfa, 0x8, 0x73, 0xd,
    0xfa, 0x10, 0x74, 0xd,
    0xfa, 0x18, 0x75, 0xd,
    0x2, 0x0, 0x81, 0xa,
    0x2, 0x8, 0x82, 0xa,
    0x2, 0x10, 0x83, 0xa,
    0x2, 0x18, 0x84, 0xa,
    0xa, 0x0, 0x91, 0xa,
    0xa, 0x8, 0x92, 0xa,
    0xa, 0x10, 0x93, 0xa,
    0xa, 0x18, 0x94, 0xa,
    0x12, 0x10, 0xa3, 0xa,
};

const uint8_t Unknown_116fec[] = {
    0xe,
    0xfd, 0x0, 0x85, 0xd,
    0xfd, 0x8, 0x86, 0xd,
    0x5, 0x0, 0x95, 0xd,
    0x5, 0x8, 0x96, 0xa,
    0x5, 0x10, 0x97, 0xa,
    0x5, 0x18, 0x98, 0xa,
    0xd, 0x0, 0xa5, 0xa,
    0xd, 0x8, 0xa6, 0xa,
    0xd, 0x10, 0xa7, 0xa,
    0xd, 0x18, 0xa8, 0xa,
    0x15, 0x0, 0xb3, 0xa,
    0x15, 0x8, 0xb4, 0xa,
    0x15, 0x10, 0xb5, 0xa,
    0x15, 0x18, 0xb6, 0xa,
};

const uint8_t Unknown_117025[] = {
    0xc,
    0x8, 0x0, 0x79, 0xd,
    0x8, 0x8, 0x7a, 0xd,
    0x8, 0x10, 0x7b, 0xa,
    0x8, 0x18, 0x7c, 0xa,
    0x10, 0x0, 0x89, 0xd,
    0x10, 0x8, 0x8a, 0xa,
    0x10, 0x10, 0x8b, 0xa,
    0x10, 0x18, 0x8c, 0xa,
    0x18, 0x0, 0x99, 0xa,
    0x18, 0x8, 0x9a, 0xa,
    0x18, 0x10, 0x9b, 0xa,
    0x18, 0x18, 0x9c, 0xa,
};

const uint8_t Unknown_117056[] = {
    0xb,
    0x8, 0x0, 0x7d, 0xa,
    0x8, 0x8, 0x7e, 0xd,
    0x8, 0x10, 0x7f, 0xd,
    0x8, 0x18, 0x80, 0xa,
    0x10, 0x0, 0x8d, 0xa,
    0x10, 0x8, 0x8e, 0xa,
    0x10, 0x10, 0x8f, 0xa,
    0x10, 0x18, 0x90, 0xa,
    0x18, 0x8, 0x9e, 0xa,
    0x18, 0x10, 0x9f, 0xa,
    0x18, 0x18, 0xa0, 0xa,
};

const uint8_t Unknown_117083[] = {
    0xf,
    0x0, 0x0, 0xa1, 0xa,
    0x0, 0x8, 0xa2, 0xa,
    0x0, 0x10, 0xa2, 0x2a,
    0x0, 0x18, 0xa1, 0x2a,
    0x8, 0x0, 0xb1, 0xa,
    0x8, 0x8, 0xb2, 0xd,
    0x8, 0x10, 0xb2, 0x2d,
    0x8, 0x18, 0xb1, 0x2a,
    0x10, 0x0, 0xab, 0xa,
    0x10, 0x8, 0xac, 0xa,
    0x10, 0x10, 0xac, 0x2a,
    0x10, 0x18, 0xab, 0x2a,
    0x18, 0x8, 0xa4, 0xa,
    0x18, 0x10, 0x87, 0xa,
    0x18, 0x18, 0x88, 0xa,
};

const uint8_t Unknown_1170c0[] = {
    0xf,
    0x0, 0x0, 0xa1, 0xa,
    0x0, 0x8, 0xa2, 0xd,
    0x0, 0x10, 0xa2, 0x2a,
    0x0, 0x18, 0xa1, 0x2a,
    0x8, 0x0, 0xb1, 0xa,
    0x8, 0x8, 0x78, 0xd,
    0x8, 0x10, 0x78, 0x2d,
    0x8, 0x18, 0xb1, 0x2a,
    0x10, 0x0, 0xab, 0xa,
    0x10, 0x8, 0xac, 0xa,
    0x10, 0x10, 0xac, 0x2a,
    0x10, 0x18, 0xab, 0x2a,
    0x18, 0x8, 0xa4, 0xa,
    0x18, 0x10, 0x87, 0xa,
    0x18, 0x18, 0x88, 0xa,
};

const uint8_t Unknown_1170fd[] = {
    0xf,
    0x0, 0x0, 0xa9, 0xa,
    0x0, 0x8, 0xaa, 0xa,
    0x0, 0x10, 0xaa, 0x2a,
    0x0, 0x18, 0xa9, 0x2a,
    0x8, 0x0, 0xb7, 0xa,
    0x8, 0x8, 0xb8, 0xa,
    0x8, 0x10, 0xb8, 0x2a,
    0x8, 0x18, 0xb7, 0x2a,
    0x10, 0x0, 0xab, 0xa,
    0x10, 0x8, 0xac, 0xa,
    0x10, 0x10, 0xac, 0x2a,
    0x10, 0x18, 0xad, 0xa,
    0x18, 0x8, 0xa4, 0xa,
    0x18, 0x10, 0xba, 0xa,
    0x18, 0x18, 0xbb, 0xa,
};

const uint8_t Unknown_11713a[] = {
    0xf,
    0x0, 0x0, 0xae, 0xc,
    0x0, 0x8, 0xaf, 0xc,
    0x0, 0x10, 0xaf, 0x2c,
    0x0, 0x18, 0xae, 0x2c,
    0x8, 0x0, 0xbc, 0xc,
    0x8, 0x8, 0xbd, 0xc,
    0x8, 0x10, 0xbd, 0x2c,
    0x8, 0x18, 0xbc, 0x2c,
    0x10, 0x0, 0xbf, 0xc,
    0x10, 0x8, 0x9d, 0xc,
    0x10, 0x10, 0x9d, 0x2c,
    0x10, 0x18, 0xb0, 0xc,
    0x18, 0x8, 0xb9, 0xc,
    0x18, 0x10, 0xc0, 0xc,
    0x18, 0x18, 0xbe, 0xc,
};

const uint8_t Unknown_117177[] = {
    0x9,
    0x14, 0x0, 0x1f, 0x6,
    0x14, 0x8, 0x20, 0x6,
    0x14, 0x10, 0x21, 0x6,
    0xc, 0x0, 0x10, 0x6,
    0xc, 0x8, 0x11, 0x6,
    0xc, 0x10, 0x12, 0x6,
    0x4, 0x0, 0x1, 0x6,
    0x4, 0x8, 0x2, 0x6,
    0x4, 0x10, 0x3, 0x6,
};

const uint8_t Unknown_11719c[] = {
    0x9,
    0x14, 0x0, 0x22, 0x6,
    0x14, 0x8, 0x23, 0x6,
    0x14, 0x10, 0x24, 0x6,
    0xc, 0x0, 0x13, 0x6,
    0xc, 0x8, 0x14, 0x6,
    0xc, 0x10, 0x15, 0x6,
    0x4, 0x0, 0x4, 0x6,
    0x4, 0x8, 0x5, 0x6,
    0x4, 0x10, 0x6, 0x6,
};

const uint8_t Unknown_1171c1[] = {
    0x9,
    0x14, 0x0, 0x25, 0x6,
    0x14, 0x8, 0x26, 0x6,
    0x14, 0x10, 0x27, 0x6,
    0xc, 0x0, 0x16, 0x6,
    0xc, 0x8, 0x17, 0x6,
    0xc, 0x10, 0x18, 0x6,
    0x4, 0x0, 0x7, 0x6,
    0x4, 0x8, 0x8, 0x6,
    0x4, 0x10, 0x9, 0x6,
};

const uint8_t Unknown_1171e6[] = {
    0x9,
    0x14, 0x0, 0x28, 0x6,
    0x14, 0x8, 0x29, 0x6,
    0x14, 0x10, 0x2a, 0x6,
    0xc, 0x0, 0x19, 0x6,
    0xc, 0x8, 0x1a, 0x6,
    0xc, 0x10, 0x1b, 0x6,
    0x4, 0x0, 0xa, 0x6,
    0x4, 0x8, 0xb, 0x6,
    0x4, 0x10, 0xc, 0x6,
};

const uint8_t Unknown_11720b[] = {
    0x9,
    0x14, 0x0, 0x2b, 0x6,
    0x14, 0x8, 0x2c, 0x6,
    0x14, 0x10, 0x2d, 0x6,
    0xc, 0x0, 0x1c, 0x6,
    0xc, 0x8, 0x1d, 0x6,
    0xc, 0x10, 0x1e, 0x6,
    0x4, 0x0, 0xd, 0x6,
    0x4, 0x8, 0xe, 0x6,
    0x4, 0x10, 0xf, 0x6,
};

const uint8_t Unknown_117230[] = {
    0x9,
    0x14, 0x0, 0x47, 0x6,
    0x14, 0x8, 0x48, 0x6,
    0x14, 0x10, 0x49, 0x6,
    0xc, 0x0, 0x3b, 0x6,
    0xc, 0x8, 0x3c, 0x6,
    0xc, 0x10, 0x3b, 0x26,
    0x4, 0x0, 0x2e, 0x6,
    0x4, 0x8, 0x2f, 0x6,
    0x4, 0x10, 0x30, 0x6,
};

const uint8_t Unknown_117255[] = {
    0x9,
    0x14, 0x0, 0x35, 0x6,
    0x14, 0x8, 0x4a, 0x6,
    0x14, 0x10, 0x35, 0x6,
    0xc, 0x0, 0x3d, 0x6,
    0xc, 0x8, 0x35, 0x6,
    0xc, 0x10, 0x3d, 0x26,
    0x4, 0x0, 0x31, 0x6,
    0x4, 0x8, 0x32, 0x6,
    0x4, 0x10, 0x31, 0x26,
};

const uint8_t Unknown_11727a[] = {
    0x9,
    0x14, 0x0, 0x4b, 0x6,
    0x14, 0x8, 0x4c, 0x6,
    0x14, 0x10, 0x4d, 0x6,
    0xc, 0x0, 0x3e, 0x6,
    0xc, 0x8, 0x3f, 0x6,
    0xc, 0x10, 0x40, 0x6,
    0x4, 0x0, 0x33, 0x6,
    0x4, 0x8, 0x34, 0x6,
    0x4, 0x10, 0x35, 0x6,
};

const uint8_t Unknown_11729f[] = {
    0x9,
    0x14, 0x0, 0x4e, 0x6,
    0x14, 0x8, 0x4f, 0x6,
    0x14, 0x10, 0x50, 0x6,
    0xc, 0x0, 0x41, 0x6,
    0xc, 0x8, 0x42, 0x6,
    0xc, 0x10, 0x43, 0x6,
    0x4, 0x0, 0x35, 0x6,
    0x4, 0x8, 0x36, 0x6,
    0x4, 0x10, 0x37, 0x6,
};

const uint8_t Unknown_1172c4[] = {
    0x9,
    0x14, 0x0, 0x51, 0x6,
    0x14, 0x8, 0x52, 0x6,
    0x14, 0x10, 0x35, 0x6,
    0xc, 0x0, 0x44, 0x6,
    0xc, 0x8, 0x45, 0x6,
    0xc, 0x10, 0x46, 0x6,
    0x4, 0x0, 0x38, 0x6,
    0x4, 0x8, 0x39, 0x6,
    0x4, 0x10, 0x3a, 0x6,
};

const uint8_t Unknown_1172e9[] = {
    0x9,
    0x10, 0x0, 0x0, 0x2,
    0x10, 0x8, 0x0, 0x2,
    0x10, 0x10, 0x0, 0x2,
    0x8, 0x0, 0x0, 0x2,
    0x8, 0x8, 0x0, 0x2,
    0xc, 0x10, 0x1f, 0x6,
    0x0, 0x0, 0x0, 0x2,
    0x0, 0x8, 0x0, 0x2,
    0x4, 0x10, 0x10, 0x6,
};

const char PichuBorderMobileOBPalettes[] = "gfx/mobile/pichu_border_ob.pal";
const char PichuBorderMobileBGPalettes[] = "gfx/mobile/pichu_border_bg.pal";

// void PichuBorderMobileTilemapAttrmap(void){
const char PichuBorderMobileTilemap[] = "gfx/mobile/pichu_border.tilemap";
const char PichuBorderMobileAttrmap[] = "gfx/mobile/pichu_border.attrmap";
