#include "../constants.h"
#include "mobile_46.h"
#include "mobile_41.h"
#include "mobile_45_sprite_engine.h"
#include "mobile_5f.h"
#include "../home/copy.h"
#include "../home/sram.h"
#include "../home/joypad.h"
#include "../home/map.h"
#include "../home/text.h"
#include "../home/delay.h"

static uint8_t* gMobileMessagePtr; // wc31b-wc31c
static tile_t* gMobileMessageDestPtr; // wc31d-wc31e

void Function118000(void){
    LD_A(0x1);
    LD_addr_A(wcd38);
    JR(masm_11800b);

}

void Function118007(void){
    XOR_A_A;
    LD_addr_A(wcd38);

    return asm_11800b();
}

void asm_11800b(void){
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x18);
    LD_addr_A(wcd33);
    LD_A(0x19);
    LD_addr_A(wcd34);
    LD_A(0x4);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

loop:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x1b);
    IF_C goto skip;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


skip:
    CALL(aFunction1184a5);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto loop;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    CALL(aReturnToMapFromSubmenu);
    return BattleTowerRoomMenu_DoNothing();
}

void BattleTowerRoomMenu_DoNothing(void){
    RET;

}

void Function11805f(void){
    LD_A(0x1);
    LD_addr_A(wcd38);
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x18);
    LD_addr_A(wcd33);
    LD_A(0x19);
    LD_addr_A(wcd34);
    LD_A(0x4);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_11807d:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x1b);
    IF_C goto asm_118090;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


asm_118090:
    CALL(aFunction11857c);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_11807d;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    CALL(aReturnToMapFromSubmenu);
    RET;

}

void Function1180b8(void){
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x22);
    LD_addr_A(wcd33);
    LD_A(0x23);
    LD_addr_A(wcd34);
    LD_A(0x4);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_1180d1:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x28);
    IF_C goto asm_1180e4;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


asm_1180e4:
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x10);
    IF_C goto asm_1180f2;
    CP_A(0x16);
    IF_NC goto asm_1180f2;
    CALL(aFunction11884c);


asm_1180f2:
    CALL(aFunction1184ec);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_1180d1;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    CALL(aReturnToMapFromSubmenu);
    RET;

}

void Function11811a(void){
    LD_A(1);
    LD_addr_A(wcd38);
    JR(mFunction118125);

}

void v_BattleTowerRoomMenu(void){
    // XOR_A_A;
    // LD_addr_A(wcd38);
    wram->wcd38 = 0;
    return Function118125();
}

void Function118125(void){
    // CALL(aBattleTowerRoomMenu_InitRAM);
    BattleTowerRoomMenu_InitRAM();
    // LD_A(0x3);
    // LD_addr_A(wcd33);
    wram->wcd33 = 0x3;
    // LD_A(0xd);
    // LD_addr_A(wcd34);
    wram->wcd34 = 0xd;
    // LD_A(0x4);
    // LD_addr_A(wc3f0);
    wram->wc3f0 = 0x4;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);

    do {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // CALL(aFunction118473);
        Function118473();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // CP_A(0xf);
        // IF_C goto skip;
        if(wram->wBattleTowerRoomMenuJumptableIndex >= 0xf) {
            // LD_A_addr(wcd34);
            // LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
            wram->wBattleTowerRoomMenuJumptableIndex = wram->wcd34;
        }

    // skip:
        // CALL(aBattleTowerRoomMenu_Jumptable);
        BattleTowerRoomMenu_Jumptable();
        // CALL(aBattleTowerRoomMenu_WriteMessage);
        BattleTowerRoomMenu_WriteMessage();
        // FARCALL(aFunction115dd3);
        Function115dd3();
        // FARCALL(aFunction11619d);
        Function11619d();
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
        // LD_HL(wcd33);
        // CP_A_hl;
        // IF_NZ goto loop;
    } while(wram->wBattleTowerRoomMenuJumptableIndex != wram->wcd33);
    // XOR_A_A;
    // LD_addr_A(w3_d000);
    wram->w3_d000[0] = 0;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aBattleTowerRoomMenu_Cleanup);
    BattleTowerRoomMenu_Cleanup();
    // CALL(aFunction118180);
    Function118180();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // RET;
}

void Function118180(void){
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wScriptVar != 0)
        return;
    // LD_A_addr(wcd38);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd38 == 0)
        return;
    // LD_A(BANK(s5_a89c));  // aka BANK(s5_a8b2)
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_a89c));
    // LD_HL(wcd69);
    // LD_DE(s5_a89c);
    // LD_BC(22);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(GBToRAMAddr(s5_a89c), wram->wcd69, 22);

    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(w3_d202));
    // LDH_addr_A(rSVBK);

    // LD_DE(w3_d202);
    // LD_C(0x96);
    // FARCALL(aCheckStringForErrors_IgnoreTerminator);
    // IF_C goto return_d3;

    // LD_DE(w3_d202);
    // LD_BC((1 << 8) | 0x96);
    // FARCALL(aCheckStringContainsLessThanBNextCharacters);
    // IF_C goto return_d3;
    if(CheckStringForErrors_IgnoreTerminator_Conv((const uint8_t*)&wram->w3_d202, 0x96)
    || CheckStringContainsLessThanBNextCharacters_Conv((const uint8_t*)&wram->w3_d202, 1, 0x96)) {
    // return_d3:
        // LD_A(0xd3);
        // LD_addr_A(wMobileErrorCodeBuffer);
        wram->wMobileErrorCodeBuffer[0] = 0xd3;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0xd3;
        // goto reset_banks;
    }
    else {
        // LD_HL(w3_d202);
        // LD_DE(s5_a8b2);
        // LD_BC(150);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(GBToRAMAddr(s5_a8b2), &wram->w3_d202, 150);
    }

// reset_banks:
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void Function1181da(void){
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x2);
    LD_addr_A(wcd38);
    LD_A(0x21);
    LD_addr_A(wcd33);
    LD_A(0x22);
    LD_addr_A(wcd34);
    LD_A(0x4);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_1181f8:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x28);
    IF_C goto asm_11820b;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


asm_11820b:
    CALL(aFunction1185c3);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_1181f8;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    CALL(aReturnToMapFromSubmenu);
    RET;

}

void Function118233(void){
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x1b);
    LD_addr_A(wcd33);
    LD_A(0x1c);
    LD_addr_A(wcd34);
    LD_A(0x6);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_11824c:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x1e);
    IF_C goto asm_11825f;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


asm_11825f:
    CALL(aFunction118624);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_11824c;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    RET;

}

void Function118284(void){
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x19);
    LD_addr_A(wcd33);
    LD_A(0x1e);
    LD_addr_A(wcd34);
    LD_A(0x5);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_11829d:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x20);
    IF_C goto asm_1182b0;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);

asm_1182b0:
    CALL(aFunction1186f5);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_11829d;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    RET;

}

void Function1182d5(void){
//  //  unreferenced
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x18);
    LD_addr_A(wcd33);
    LD_A(0x19);
    LD_addr_A(wcd34);
    LD_A(0x4);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_1182ee:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x1b);
    IF_C goto asm_118301;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


asm_118301:
    CALL(aFunction118746);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_1182ee;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    CALL(aReturnToMapFromSubmenu);
    RET;

}

void Function118329(void){
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x15);
    LD_addr_A(wcd33);
    LD_A(0x16);
    LD_addr_A(wcd34);
    LD_A(0x6);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_118342:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x18);
    IF_C goto asm_118355;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


asm_118355:
    CALL(aFunction118671);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_118342;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    RET;

}

void Function11837a(void){
    CALL(aBattleTowerRoomMenu_InitRAM);
    LD_A(0x16);
    LD_addr_A(wcd33);
    LD_A(0x17);
    LD_addr_A(wcd34);
    LD_A(0x6);
    LD_addr_A(wc3f0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_118393:
    CALL(aJoyTextDelay);
    CALL(aFunction118473);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    CP_A(0x19);
    IF_C goto asm_1183a6;
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);


asm_1183a6:
    CALL(aFunction1186b2);
    CALL(aBattleTowerRoomMenu_WriteMessage);
    FARCALL(aFunction115dd3);
    FARCALL(aFunction11619d);
    CALL(aDelayFrame);
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    LD_HL(wcd33);
    CP_A_hl;
    IF_NZ goto asm_118393;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_Cleanup);
    RET;

}

void BattleTowerRoomMenu_InitRAM(void){
    // NOP;
    // LDH_A_addr(rIE);
    // LD_addr_A(wcd32);
    wram->wcd32 = gb_read(rIE);
    // CALL(aDoubleSpeed);
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // LD_addr_A(wMobileErrorCodeBuffer);
    wram->wMobileErrorCodeBuffer[0] = 0;
    // LD_addr_A(wMobileErrorCodeBuffer + 1);
    wram->wMobileErrorCodeBuffer[1] = 0;
    // LD_addr_A(wMobileErrorCodeBuffer + 2);
    wram->wMobileErrorCodeBuffer[2] = 0;
    // LD_addr_A(wcd80);
    wram->wcd80 = 0;
    // LD_addr_A(wcd65);
    wram->wcd65 = 0;
    // LD_addr_A(wcd66);
    wram->wcd66 = 0;
    // LD_addr_A(wcd67);
    wram->wcd67 = 0;
    // LD_addr_A(wcd68);
    wram->wcd68 = 0;
    // LD_addr_A(wc31a);
    wram->wc31a = 0;
    // LD_addr_A(wcd89);
    wram->wcd89 = 0;
    // LD_addr_A(wcd8a);
    wram->wcd8a = 0;
    // LD_addr_A(wcd8b);
    wram->wcd8b = 0;
    // LD_addr_A(wc3ec);
    wram->wc3ec = 0;
    // LD_addr_A(wc3ed);
    wram->wc3ed = 0;
    // LD_addr_A(wc3ee);
    wram->wc3ee = 0;
    // LD_addr_A(wc3ef);
    wram->wc3ef = 0;
    // LD_HL(wVramState);
    // LD_A_hl;
    // LD_addr_A(wcd7f);
    wram->wcd7f = wram->wVramState;
    // SET_hl(1);
    bit_set(wram->wVramState, 1);
    // LD_A((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK));
    // LDH_addr_A(rIE);
    gb_write(rIE, (1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK));
    // LD_A(0x1);
    // LDH_addr_A(hMobileReceive);
    hram->hMobileReceive = 0x1;
    // LDH_addr_A(hMobile);
    hram->hMobile = 0x1;
    // NOP;
    // FARCALL(aStubbed_Function106462);
    Stubbed_Function106462();
    // FARCALL(aFunction106464);
    Function106464();
    // FARCALL(aFunction115d99);
    Function115d99();
    // FARCALL(aFunction11615a);
    Function11615a();
    // LD_A(BANK(s5_bfff));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_bfff));
    // XOR_A_A;
    // LD_addr_A(s5_bfff);
    gb_write(s5_bfff, 0);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void Function118440(void){
    PUSH_AF;
    LD_A(BANK(s5_bfff));
    CALL(aOpenSRAM);
    LD_A_addr(s5_bfff);
    INC_A;
    LD_addr_A(s5_bfff);
    CALL(aCloseSRAM);
    POP_AF;
    RET;

}

void BattleTowerRoomMenu_Cleanup(void){
    // NOP;
    // XOR_A_A;
    // LDH_addr_A(hMobileReceive);
    hram->hMobileReceive = 0;
    // LDH_addr_A(hMobile);
    hram->hMobile = 0;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0;
    // CALL(aNormalSpeed);
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0x0);
    // LD_A_addr(wcd32);
    // LDH_addr_A(rIE);
    gb_write(rIE, wram->wcd32);
    // NOP;
    // LD_A_addr(wcd7f);
    // LD_addr_A(wVramState);
    wram->wVramState = wram->wcd7f;
    // LD_A_addr(wMobileErrorCodeBuffer);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wMobileErrorCodeBuffer[0];
    // RET;
}

void Function118473(void){
    // LD_A_addr(wcd65);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd65 == 0)
        return;
    // LD_A_addr(wcd66);
    // INC_A;
    // LD_addr_A(wcd66);
    // CP_A(60);
    // RET_NZ ;
    if(++wram->wcd66 != 60)
        return;
    // XOR_A_A;
    // LD_addr_A(wcd66);
    wram->wcd66 = 0;
    // LD_A_addr(wcd67);
    // INC_A;
    // LD_addr_A(wcd67);
    // CP_A(60);
    // RET_NZ ;
    if(++wram->wcd67 != 60)
        return;
    // LD_A_addr(wcd68);
    // INC_A;
    // LD_addr_A(wcd68);
    // CP_A(99);
    // IF_Z goto ninety_nine;
    if(++wram->wcd68 == 99) {
    // ninety_nine:
        // XOR_A_A;
        // LD_addr_A(wcd65);
        wram->wcd65 = 0;
        // RET;
        return;
    }
    // XOR_A_A;
    // LD_addr_A(wcd67);
    wram->wcd67 = 0;
    // RET;
}

void Function1184a5(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function11886e'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function118a8f'];
    //dw ['Function11878d'];
    //dw ['Function118d80'];
    //dw ['Function118d9b'];
    //dw ['Function11878d'];
    //dw ['Function118ded'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function11984e'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function1184ec();
}

void Function1184ec(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function11886e'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function119954'];
    //dw ['Function11878d'];
    //dw ['Function119973'];
    //dw ['Function11878d'];
    //dw ['Function119987'];
    //dw ['Function11878d'];
    //dw ['Function1199b4'];
    //dw ['Function1199ca'];
    //dw ['Function11878d'];
    //dw ['Function1199e2'];
    //dw ['Function119b0d'];
    //dw ['Function11878d'];
    //dw ['Function119b6b'];
    //dw ['Function119b3b'];
    //dw ['Function11878d'];
    //dw ['Function119b52'];
    //dw ['Function11878d'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function119b45'];
    //dw ['Function11878d'];
    //dw ['Function119ac9'];
    //dw ['Function118e76'];

    return BattleTowerRoomMenu_Jumptable();
}

// TODO: Finish this jumptable.
void BattleTowerRoomMenu_Jumptable(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']

// Jumptable:
    switch(wram->wBattleTowerRoomMenuJumptableIndex) {
        //dw ['BattleTowerRoomMenu_PickLevelMessage'];
        case 0: return BattleTowerRoomMenu_PickLevelMessage();
        //dw ['BattleTowerRoomMenu_PlacePickLevelMenu'];
        //dw ['BattleTowerRoomMenu_UpdatePickLevelMenu'];
        //dw ['BattleTowerRoomMenu_DoNothing'];
        //dw ['BattleTowerRoomMenu_PartyMonTopsThisLevelMessage'];
        //dw ['BattleTowerRoomMenu_WaitForMessage'];
        //dw ['BattleTowerRoomMenu_DelayRestartMenu'];
        //dw ['BattleTowerRoomMenu_QuitMessage'];
        //dw ['BattleTowerRoomMenu_PlaceYesNoMenu'];
        //dw ['BattleTowerRoomMenu_UpdateYesNoMenu'];
        //dw ['BattleTowerRoomMenu_UberRestrictionMessage'];
        //dw ['BattleTowerRoomMenu_WaitForMessage'];
        //dw ['BattleTowerRoomMenu_DelayRestartMenu'];
        //dw ['Function118e76'];  // mobile
        //dw ['BattleTowerRoomMenu_CallRoomMenu2'];  // mobile
        //dw ['Function118e76'];  // mobile
    }
}

void Function11857c(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function11886e'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function118a7a'];
    //dw ['Function11878d'];
    //dw ['Function11891c'];
    //dw ['Function1198ee'];
    //dw ['Function1198f7'];
    //dw ['Function11878d'];
    //dw ['Function119937'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function1185c3();
}

void Function1185c3(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function11886e'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function118aa4'];
    //dw ['Function11878d'];
    //dw ['Function118e92'];
    //dw ['Function11878d'];
    //dw ['Function118eb0'];
    //dw ['Function118ec6'];
    //dw ['Function118f0d'];
    //dw ['Function118f14'];
    //dw ['Function118f5e'];
    //dw ['Function11878d'];
    //dw ['Function118fc0'];
    //dw ['Function11878d'];
    //dw ['Function119054'];
    //dw ['Function1190d0'];
    //dw ['Function11878d'];
    //dw ['Function1190ec'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['BattleTowerRoomMenu_QuitMessage'];
    //dw ['BattleTowerRoomMenu_PlaceYesNoMenu'];
    //dw ['BattleTowerRoomMenu_UpdateYesNoMenu'];
    //dw ['Function11914e'];
    //dw ['Function118e76'];

    return Function118624();
}

void Function118624(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function118866'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function118aa4'];
    //dw ['Function11878d'];
    //dw ['Function118e92'];
    //dw ['Function11878d'];
    //dw ['Function11915d'];
    //dw ['Function118f68'];
    //dw ['Function11878d'];
    //dw ['Function119009'];
    //dw ['Function11878d'];
    //dw ['Function119054'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function118671();
}

void Function118671(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function118866'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function119380'];
    //dw ['Function119388'];
    //dw ['Function1193a0'];
    //dw ['Function11878d'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function1186b2();
}

void Function1186b2(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function118866'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function119380'];
    //dw ['Function1193e3'];
    //dw ['Function1193fb'];
    //dw ['Function11878d'];
    //dw ['Function119413'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function1186f5();
}

void Function1186f5(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function11886a'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function118abc'];
    //dw ['Function11878d'];
    //dw ['Function119451'];
    //dw ['Function1195f8'];
    //dw ['Function119612'];
    //dw ['Function119629'];
    //dw ['Function119648'];
    //dw ['Function11878d'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function11967d'];
    //dw ['Function119685'];
    //dw ['Function119665'];
    //dw ['Function11966d'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function118746();
}

void Function118746(void){
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenuJumptableIndex']


Jumptable:
    //dw ['Function11886e'];
    //dw ['Function118880'];
    //dw ['Function11878d'];
    //dw ['Function1188b0'];
    //dw ['Function11878d'];
    //dw ['Function1188b8'];
    //dw ['Function11878d'];
    //dw ['Function1188c0'];
    //dw ['Function11878d'];
    //dw ['Function1188c8'];
    //dw ['Function11878d'];
    //dw ['Function118903'];
    //dw ['Function118ad0'];
    //dw ['Function11878d'];
    //dw ['Function1196f2'];
    //dw ['Function1197c9'];
    //dw ['Function1197dc'];
    //dw ['Function11878d'];
    //dw ['Function118e6d'];
    //dw ['Function11878d'];
    //dw ['Function119800'];
    //dw ['Function118e76'];
    //dw ['Function118e7e'];
    //dw ['Function11878d'];
    //dw ['BattleTowerRoomMenu_DoNothing'];
    //dw ['Function118e76'];
    //dw ['BattleTowerRoomMenu_CallRoomMenu2'];
    //dw ['Function118e76'];

    return Function11878d();
}

void Function11878d(void){
    LD_A_addr(wc821);
    BIT_A(1);
    IF_NZ goto asm_1187af;
    BIT_A(2);
    IF_NZ goto asm_1187d1;
    BIT_A(0);
    IF_NZ goto asm_1187aa;
    LD_A_addr(wcd89);
    AND_A(0x1);
    IF_Z goto asm_1187a7;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

asm_1187a7:
    JP(mBattleTowerRoomMenu_IncrementJumptable);

asm_1187aa:
    CALL(aFunction118821);
    RET_C ;
    RET;

asm_1187af:
    LD_A(MOBILEAPI_00);
    CALL(aMobileAPI);
    LD_addr_A(wMobileErrorCodeBuffer);
    LD_A_L;
    LD_addr_A(wMobileErrorCodeBuffer + 1);
    LD_A_H;
    LD_addr_A(wMobileErrorCodeBuffer + 2);
    LD_A(MOBILEAPI_05);
    CALL(aMobileAPI);
    LD_A_addr(wc3f0);
    LD_addr_A(wc319);
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    RET;

asm_1187d1:
    LD_HL(wcd89);
    BIT_hl(0);
    IF_NZ goto asm_118803;
    SET_hl(0);
    LD_A(BANK(w6_d000));
    LDH_addr_A(rSVBK);
    LD_DE(w6_d000);
    LD_BC(0x1000);
    LD_A_hl;
    SLA_A;
    IF_C goto asm_1187f9;
    SLA_A;
    IF_C goto asm_1187fd;
    SLA_A;
    IF_C goto asm_1187f5;
    LD_A(MOBILEAPI_12);
    goto asm_1187ff;

asm_1187f5:
    LD_A(MOBILEAPI_14);
    goto asm_1187ff;

asm_1187f9:
    LD_A(MOBILEAPI_15);
    goto asm_1187ff;

asm_1187fd:
    LD_A(MOBILEAPI_16);

asm_1187ff:
    CALL(aMobileAPI);
    RET;

asm_118803:
    LD_A(0xd3);

    return SetMobileErrorCode();
}

void SetMobileErrorCode(void){
    LD_addr_A(wMobileErrorCodeBuffer);
    XOR_A_A;
    LD_addr_A(wMobileErrorCodeBuffer + 1);
    LD_addr_A(wMobileErrorCodeBuffer + 2);
    LD_A(MOBILEAPI_05);
    CALL(aMobileAPI);
    LD_A_addr(wc3f0);
    LD_addr_A(wc319);
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    RET;

}

void Function118821(void){
    LD_A_addr(wc319);
    CP_A(0x3);
    IF_C goto asm_11884a;
    CP_A(0x4);
    IF_Z goto asm_11884a;
    LDH_A_addr(hJoyDown);
    CP_A(0x5);
    IF_NZ goto asm_11884a;
    LD_A(MOBILEAPI_05);
    CALL(aMobileAPI);
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    LD_A_addr(wc3f0);
    LD_addr_A(wc319);
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    SCF;
    RET;

asm_11884a:
    AND_A_A;
    RET;

}

void Function11884c(void){
    LDH_A_addr(hJoyDown);
    CP_A(0x5);
    IF_NZ goto asm_118864;
    LD_A(MOBILEAPI_05);
    CALL(aMobileAPI);
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    LD_A_addr(wcd34);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    SCF;
    RET;


asm_118864:
    AND_A_A;
    RET;

}

void Function118866(void){
    LD_A(2);
    JR(masm_11886f);

}

void Function11886a(void){
    LD_A(1);
    JR(masm_11886f);

}

void Function11886e(void){
    XOR_A_A;

    return asm_11886f();
}

void asm_11886f(void){
    LD_addr_A(wBGMapPalBuffer);
    LD_A(0x0);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    LD_A_addr(wcd33);
    LD_addr_A(wMobileInactivityTimerSeconds);

    return Function118880();
}

void Function118880(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    XOR_A_A;
    LD_addr_A(wcf64);
    LD_addr_A(wc807);
    LD_DE(wcd81);
    LD_HL(0x46);
    LD_A(MOBILEAPI_01);
    JP(mFunction119e2b);

}

void Function118896(void){
//  //  unreferenced
    LD_A_addr(wc821);
    BIT_A(1);
    IF_NZ goto asm_1188a5;
    BIT_A(2);
    IF_NZ goto asm_1188a5;
    BIT_A(0);
    IF_Z goto asm_1188aa;


asm_1188a5:
    LD_A(MOBILEAPI_1A);
    JP(mFunction119e2b);


asm_1188aa:
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function1188b0(void){
    LD_DE(wc346);
    LD_A(MOBILEAPI_06);
    JP(mFunction119e2b);

}

void Function1188b8(void){
    LD_DE(wc3ac);
    LD_A(MOBILEAPI_07);
    JP(mFunction119e2b);

}

void Function1188c0(void){
    LD_DE(wc3cd);
    LD_A(MOBILEAPI_08);
    JP(mFunction119e2b);

}

void Function1188c8(void){
    LD_A(0x1);
    LD_addr_A(wcd65);
    CALL(aFunction1188e7);
    LD_HL(wc708);

asm_1188d3:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    AND_A_A;
    IF_NZ goto asm_1188d3;
    CALL(aFunction119eb4);
    CALL(aFunction119ec2);
    LD_HL(wc708);
    LD_A(MOBILEAPI_03);
    JP(mFunction119e2b);

}

void Function1188e7(void){
    LD_DE(wc346);
    LD_A(BANK(s5_aa4a));
    CALL(aOpenSRAM);
    LD_A_addr(s5_aa4a);
    CALL(aCloseSRAM);
    AND_A_A;
    RET_Z ;
    SLA_A;
    LD_C_A;

asm_1188fa:
    LD_A_de;
    INC_DE;
    AND_A_A;
    IF_NZ goto asm_1188fa;
    DEC_C;
    IF_NZ goto asm_1188fa;
    RET;

}

void Function118903(void){
    LD_A_addr(wc3f0);
    LD_addr_A(wc319);
    LD_C(0x1);
    FARCALL(aFunction115e18);
    LD_A(0x8);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function11891c(void){
    CALL(aFunction118b42);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void BattleTowerRoomMenu_PickLevelMessage(void){
    LD_A_addr(wcd38);
    AND_A_A;
    IF_NZ goto asm_11892d;
    LD_HL(mText_WhatLevelDoYouWantToChallenge);
    goto asm_118930;


asm_11892d:
    LD_HL(mText_CheckBattleRoomListByMaxLevel);


asm_118930:
    CALL(aBattleTowerRoomMenu_SetMessage);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return BattleTowerRoomMenu_PlacePickLevelMenu();
}

void BattleTowerRoomMenu_PlacePickLevelMenu(void){
    LD_A_addr(wc31a);
    AND_A_A;
    RET_NZ ;
    LD_HL(mMenuHeader_119cf7);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    CALL(aMenuBoxCoord2Tile);
    CALL(aApplyTilemap);
    hlcoord(16, 8, wAttrmap);
    LD_A(0x40);
    OR_A_hl;
    LD_hl_A;
    CALL(aWaitBGMap2);
    LD_A(0x1);
    LD_addr_A(wcd4f);
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_A_addr(wStatusFlags);
    BIT_A(STATUSFLAGS_HALL_OF_FAME_F);
    IF_NZ goto asm_11896b;
    LD_HL(mStrings_Ll0ToL40);  // Address to list of strings with the choosable levels
    LD_A(5);  // 4 levels to choose from, including 'Cancel'-option
    goto asm_118970;


asm_11896b:
    LD_HL(mStrings_L10ToL100);  // Address to list of strings with the choosable levels
    LD_A(11);  // 10 levels to choose from, including 'Cancel'-option


asm_118970:
    LD_addr_A(wcd4a);
    LD_A_L;
    LD_addr_A(wcd4b);
    LD_A_H;
    LD_addr_A(wcd4c);
    LD_A(0x3);
    LDH_addr_A(rSVBK);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return BattleTowerRoomMenu_UpdatePickLevelMenu();
}

void BattleTowerRoomMenu_UpdatePickLevelMenu(void){
    hlcoord(13, 8, wTilemap);
    LD_DE(mString_119d07);
    CALL(aPlaceString);
    hlcoord(13, 10, wTilemap);
    LD_DE(mString_119d07);
    CALL(aPlaceString);
    LD_A_addr(wcd4b);
    LD_L_A;
    LD_A_addr(wcd4c);
    LD_H_A;
    LD_D(0x0);
    LD_A_addr(wcd4f);
    DEC_A;
    RLCA;
    RLCA;
    RLCA;
    LD_E_A;
    ADD_HL_DE;
    LD_A_L;
    LD_E_A;
    LD_A_H;
    LD_D_A;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_BC(wStringBuffer3);

asm_1189b5:
    LD_A_hli;
    CP_A(0x50);
    IF_Z goto asm_1189c4;
    CP_A(0x7f);
    IF_Z goto asm_1189c2;
    LD_bc_A;
    INC_BC;
    goto asm_1189b5;


asm_1189c2:
    LD_A(0x50);


asm_1189c4:
    LD_bc_A;
    POP_AF;
    LDH_addr_A(rSVBK);
    hlcoord(13, 9, wTilemap);
    CALL(aPlaceString);
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto b_button;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto a_button;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto d_down;
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto d_up;

asm_1189e5:
    RET;


d_down:
    LD_HL(wcd4f);
    DEC_hl;
    IF_NZ goto asm_1189e5;
    LD_A_addr(wcd4a);
    LD_hl_A;
    goto asm_1189e5;


d_up:
    LD_A_addr(wcd4a);
    LD_HL(wcd4f);
    INC_hl;
    CP_A_hl;
    IF_NC goto asm_1189e5;
    LD_A(0x1);
    LD_hl_A;
    goto asm_1189e5;


a_button:
    CALL(aPlayClickSFX);
    LD_A_addr(wcd4f);
    LD_HL(wcd4a);
    CP_A_hl;
    IF_Z goto asm_118a3c;
    DEC_A;
    AND_A(0xfe);
    SRL_A;
    LD_addr_A(wcf65);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    CALL(aCloseWindow);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A_addr(wcd38);
    AND_A_A;
    IF_NZ goto asm_118a30;
    CALL(aBattleTower_LevelCheck);
    RET_C ;
    CALL(aBattleTower_UbersCheck);
    RET_C ;


asm_118a30:
    LD_A_addr(wcd4f);
    LD_addr_A(w3_d800);
    JP(mBattleTowerRoomMenu_IncrementJumptable);


b_button:
    CALL(aPlayClickSFX);


asm_118a3c:
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    CALL(aCloseWindow);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(0x7);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    LD_A(0x0);
    LD_addr_A(wMobileInactivityTimerFrames);
    RET;

}

void Function118a54(void){
//  //  unreferenced
    LD_A_addr(wcd55);
    LD_L_A;
    LD_A_addr(wcd56);
    LD_H_A;
    LD_DE(wc3ec);
    LD_BC(0x0004);
    JP(mFunction118ae4);

}

void Function118a65(void){
//  //  unreferenced
    LD_HL(mBattleDownloadURL);
    LD_DE(wcc60);
    LD_BC(0x80);
    CALL(aCopyBytes);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    JP(mFunction118b10);

}

void Function118a7a(void){
    LD_HL(mBattleDownloadURL);
    LD_DE(wcc60);
    LD_BC(0x80);
    CALL(aCopyBytes);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    JP(mFunction118b10);

}

void Function118a8f(void){
    LD_HL(mExchangeDownloadURL);
    LD_DE(wcc60);
    LD_BC(0x80);
    CALL(aCopyBytes);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    JP(mFunction118b10);

}

void Function118aa4(void){
    LD_HL(mNewsDownloadURL);
    LD_DE(wcc60);
    LD_BC(0x80);
    CALL(aCopyBytes);
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_DE(w3_d100);
    LD_BC(0xe00);
    JR(mFunction118b10);

}

void Function118abc(void){
    LD_HL(mMenuDownloadURL);
    LD_DE(wcc60);
    LD_BC(0x80);
    CALL(aCopyBytes);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    JR(mFunction118b10);

}

void Function118ad0(void){
    LD_HL(mIndexDownloadURL);
    LD_DE(wcc60);
    LD_BC(0x80);
    CALL(aCopyBytes);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    JR(mFunction118b10);

}

void Function118ae4(void){
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_A(0x8);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    POP_HL;
    LD_C(0x0);
    LD_DE(wcc60);

asm_118af5:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    AND_A_A;
    IF_Z goto asm_118b06;
    INC_C;
    LD_A_C;
    CP_A(0xa6);
    IF_C goto asm_118af5;
    LD_A(0xda);
    JP(mSetMobileErrorCode);


asm_118b06:
    CALL(aFunction118b24);
    POP_DE;
    POP_BC;
    LD_A(MOBILEAPI_15);
    JP(mFunction119e2b);

}

void Function118b10(void){
    PUSH_DE;
    PUSH_BC;
    LD_A(0x8);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    CALL(aFunction118b24);
    POP_BC;
    POP_DE;
    LD_A(MOBILEAPI_15);
    JP(mFunction119e2b);

}

void Function118b24(void){
    LD_HL(wc346);
    LD_A(0x8);
    LD_hli_A;
    LD_A(0xc7);
    LD_hli_A;
    LD_A(0x60);
    LD_hli_A;
    LD_A(0xcc);
    LD_hli_A;
    CALL(aFunction119eb4);
    CALL(aFunction119ec2);
    LD_A(0x80);
    LD_addr_A(wcd89);
    LD_HL(wc346);
    RET;

}

void Function118b42(void){
    LD_HL(wd002);
    LD_A_L;
    LD_addr_A(wcd51);
    LD_A_H;
    LD_addr_A(wcd52);
    CALL(aFunction118b8c);
    LD_A_L;
    LD_addr_A(wcd55);
    LD_addr_A(wcd59);
    LD_A_H;
    LD_addr_A(wcd56);
    LD_addr_A(wcd5a);
    CALL(aFunction118b8c);
    LD_A_L;
    LD_addr_A(wcd53);
    LD_addr_A(wcd5d);
    LD_A_H;
    LD_addr_A(wcd54);
    LD_addr_A(wcd5e);
    CALL(aFunction118b8c);
    LD_A_L;
    LD_addr_A(wcd57);
    LD_addr_A(wcd5b);
    LD_A_H;
    LD_addr_A(wcd58);
    LD_addr_A(wcd5c);
    CALL(aFunction118b8c);
    LD_A_L;
    LD_addr_A(wcd5f);
    LD_A_H;
    LD_addr_A(wcd60);
    RET;

}

void Function118b8c(void){

asm_118b8c:
    CALL(aFunction118b9a);
    RET_NC ;
    LD_A_hli;
    CP_A(0xd);
    IF_NZ goto asm_118b8c;
    DEC_HL;
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    RET;

}

void Function118b9a(void){
    LD_A_H;
    CP_A(0xe0);
    RET_C ;
    LD_A(0xd3);
    CALL(aSetMobileErrorCode);
    AND_A_A;
    RET;

//pushc
//setcharmap ascii
}

const char ExchangeDownloadURL[] = "http://gameboy.datacenter.ne.jp/cgb/download?name=/01/CGB-BXTJ/exchange/index.txt";

void BattleDownloadURL(void){
    //db ['"http://gameboy.datacenter.ne.jp/cgb/download?name=/01/CGB-BXTJ/battle/index.txt"', '0'];

    return NewsDownloadURL();
}

void NewsDownloadURL(void){
    //db ['"http://gameboy.datacenter.ne.jp/cgb/download?name=/01/CGB-BXTJ/news/index.txt"', '0'];

    return MenuDownloadURL();
}

void MenuDownloadURL(void){
    //db ['"http://gameboy.datacenter.ne.jp/cgb/download?name=/01/CGB-BXTJ/POKESTA/menu.cgb"', '0'];
}

const char IndexDownloadURL[] = "http://gameboy.datacenter.ne.jp/cgb/download?name=/01/CGB-BXTJ/tamago/index.txt";

// popc

void Function118d35(void){
//  //  unreferenced
    LD_HL(0xd200);
    LD_A_addr(wcd38);
    AND_A_A;
    IF_NZ goto asm_118d6e;
    LD_A_hli;
    CP_A(0x94);
    IF_NZ goto asm_118d7b;
    LD_A_hl;
    CP_A(0x5);
    IF_NZ goto asm_118d7b;
    LD_A_addr(wcd4f);
    SLA_A;
    LD_B_A;
    SLA_A;
    SLA_A;
    ADD_A_B;
    LD_B_A;
    LD_A(BANK(s5_b2fb));
    CALL(aOpenSRAM);
    LD_A_B;
    LD_addr_A(s5_b2fb);
    CALL(aCloseSRAM);
    FARCALL(aFunction170be4);
    FARCALL(aFunction1700c4);
    goto asm_118d78;


asm_118d6e:
    LD_A_hli;
    CP_A(0x96);
    IF_NZ goto asm_118d7b;
    LD_A_hl;
    CP_A(0x0);
    IF_NZ goto asm_118d7b;


asm_118d78:
    JP(mBattleTowerRoomMenu_IncrementJumptable);


asm_118d7b:
    LD_A(0xd3);
    JP(mSetMobileErrorCode);

}

void Function118d80(void){
    CALL(aFunction118e06);
    LD_A_addr(wcd38);
    AND_A_A;
    IF_Z goto asm_118d8e;
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    JR(masm_118d9f);


asm_118d8e:
    LD_A(0x9);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x12);
    LD_addr_A(wMobileInactivityTimerSeconds);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function118d9b();
}

void Function118d9b(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;

    return asm_118d9f();
}

void asm_118d9f(void){
    LD_HL(wc608);
    CALL(aFunction119940);
    LD_A_addr(wcd38);
    AND_A_A;
    IF_NZ goto asm_118db2;
    LD_A(0x8f);
    LD_addr_A(wcd3b);
    goto asm_118db7;


asm_118db2:
    LD_A(0x26);
    LD_addr_A(wcd3b);


asm_118db7:
    LD_HL(w3_d800);
    LD_A(0x8);
    LD_hli_A;
    LD_A(0xc6);
    LD_hli_A;
    LD_A_addr(wcd3b);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_A(0x8);
    LD_hli_A;
    LD_A(0xc7);
    LD_hli_A;
    LD_A_addr(wcd39);
    LD_hli_A;
    LD_A_addr(wcd3a);
    LD_hli_A;
    CALL(aFunction119eb4);
    CALL(aFunction119ec2);
    LD_A(0x40);
    LD_addr_A(wcd89);
    LD_HL(w3_d800);
    LD_DE(w3_de00);
    LD_BC(0x200);
    LD_A(MOBILEAPI_16);
    JP(mFunction119e2b);

}

void Function118ded(void){
    LD_A_addr(wcd38);
    AND_A_A;
    IF_Z goto asm_118e03;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    FARCALL(aFunction11b93b);
    POP_AF;
    LDH_addr_A(rSVBK);


asm_118e03:
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function118e06(void){
    LD_HL(wd002);
    LD_A_addr(wcd38);
    AND_A_A;
    IF_Z goto asm_118e1d;

asm_118e0f:
    CALL(aFunction118b9a);
    RET_NC ;
    LD_A_hli;
    CP_A(0xd);
    IF_NZ goto asm_118e0f;
    LD_A_hli;
    CP_A(0xa);
    IF_NZ goto asm_118e0f;


asm_118e1d:
    LD_A_L;
    LD_addr_A(wcd39);
    LD_A_H;
    LD_addr_A(wcd3a);

asm_118e25:
    CALL(aFunction118b9a);
    RET_NC ;
    LD_A_hli;
    CP_A(0xd);
    IF_NZ goto asm_118e25;
    LD_A_hli;
    CP_A(0xa);
    IF_NZ goto asm_118e25;
    DEC_HL;
    XOR_A_A;
    LD_hld_A;
    LD_hl_A;
    JR(masm_118e3e);

}

void Function118e39(void){
    LD_A_hli;
    AND_A_A;
    JR_NZ (mFunction118e39);
    DEC_HL;

    return asm_118e3e();
}

void asm_118e3e(void){
    LD_A_hld;
    CP_A(0x2f);
    JR_NZ (masm_118e3e);
    INC_HL;
    INC_HL;
    LD_DE(wcd85);
    LD_C(0x4);

asm_118e4a:
    LD_A_hli;
    CP_A(0x2e);
    IF_Z goto asm_118e63;
    CP_A(0x30);
    IF_C goto asm_118e67;
    CP_A(0x3a);
    IF_NC goto asm_118e67;
    SUB_A(0x30);
    ADD_A(0xf6);
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto asm_118e4a;
    LD_DE(wcd85);

asm_118e63:
    LD_A(0x50);
    LD_de_A;
    RET;

asm_118e67:
    LD_A(0xf3);
    LD_de_A;
    INC_DE;
    goto asm_118e63;

    return Function118e6d();
}

void Function118e6d(void){
    XOR_A_A;
    LD_addr_A(wcd65);
    LD_A(MOBILEAPI_05);
    JP(mFunction119e2b);

}

void Function118e76(void){
// Call $c in BattleTowerRoomMenu2
    LD_A(0xc);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function118e7e(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    LD_A(MOBILEAPI_1B);
    JP(mFunction119e2b);

}

void BattleTowerRoomMenu_CallRoomMenu2(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    LD_A_addr(wcd33);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    RET;

}

void Function118e92(void){
    CALL(aFunction118440);
    CALL(aFunction1191d3);
    LD_A_addr(wcd53);
    LD_L_A;
    LD_A_addr(wcd54);
    LD_H_A;
    LD_DE(wcc60);
    CALL(aFunction1191ad);
    RET_C ;
    LD_DE(w3_d800);
    LD_BC(0x0800);
    JP(mFunction118b10);

}

void Function118eb0(void){
    CALL(aFunction118440);
    LD_HL(w3_d802);
    LD_DE(wBGMapBuffer);
    LD_BC(0x000c);
    CALL(aCopyBytes);
    CALL(aFunction1192cc);
    RET_C ;
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function118ec6(void){
    CALL(aFunction118440);
    CALL(aSpeechTextbox);
    LD_HL(w3_d80e);
    LD_DE(wc320);
    LD_BC(0x0026);
    CALL(aCopyBytes);
    XOR_A_A;
    LD_addr_A(wc31f);
    LD_A(0x20);
    LD_addr_A(wc31b);
    LD_A(0xc3);
    LD_addr_A(wc31c);
    hlcoord(1, 14, wTilemap);
    LD_A_L;
    LD_addr_A(wc31d);
    LD_A_H;
    LD_addr_A(wc31e);
    LD_A(0x2);
    LD_addr_A(wc31a);
    LD_A(0x1d);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x24);
    LD_addr_A(wMobileInactivityTimerSeconds);
    LD_A(0x11);
    LD_addr_A(wMobileInactivityTimerFrames);
    LD_A(0x1c);
    LD_addr_A(wcd47);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function118f0d(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    CALL(aFunction118440);

    return Function118f14();
}

void Function118f14(void){
    CALL(aFunction118440);
    LD_A_addr(wcd51);
    LD_L_A;
    LD_A_addr(wcd52);
    LD_H_A;
    LD_DE(wcc60);
    CALL(aFunction1191ad);
    RET_C ;
    LD_A_addr(wcc60);
    AND_A_A;
    IF_Z goto DontSendSaveFile;
    LD_HL(mText_SaveFileWillBeSent);
    CALL(aBattleTowerRoomMenu_SetMessage);


DontSendSaveFile:
    LD_A_addr(wcd57);
    LD_L_A;
    LD_A_addr(wcd58);
    LD_H_A;
    LD_DE(wcc60);
    CALL(aFunction1191ad);
    RET_C ;
    LD_HL(wcc60);
    CALL(aFunction118e39);
    LD_A(0x9);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x24);
    LD_addr_A(wMobileInactivityTimerSeconds);
    LD_A(0x13);
    LD_addr_A(wMobileInactivityTimerFrames);
    LD_A(0x1c);
    LD_addr_A(wcd47);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function118f5e(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    CALL(aFunction118440);
    CALL(aDelayFrame);

    return Function118f68();
}

void Function118f68(void){
    CALL(aFunction119223);
    RET_C ;
    CALL(aFunction118440);
    LD_A_addr(wcd51);
    LD_L_A;
    LD_A_addr(wcd52);
    LD_H_A;
    LD_DE(wcc60);
    CALL(aFunction1191ad);
    RET_C ;
    LD_A_addr(wcc60);
    AND_A_A;
    IF_Z goto asm_118fba;
    LD_HL(wc346);
    LD_A(LOW(0xc608));
    LD_hli_A;
    LD_A(HIGH(0xc608));
    LD_hli_A;
    LD_A_addr(wcd4b);
    LD_hli_A;
    LD_A_addr(wcd4c);
    LD_hli_A;
    LD_A(LOW(0xc708));
    LD_hli_A;
    LD_A(HIGH(0xc708));
    LD_hli_A;
    LD_A(0x60);
    LD_hli_A;
    LD_A(0xcc);
    LD_hli_A;
    CALL(aFunction119eb4);
    CALL(aFunction119ec2);
    LD_A(0x40);
    LD_addr_A(wcd89);
    LD_HL(wc346);
    LD_DE(w3_de00);
    LD_BC(0x200);
    LD_A(MOBILEAPI_16);
    JP(mFunction119e2b);


asm_118fba:
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function118fc0(void){
    CALL(aFunction118440);
    LD_A_addr(wcd55);
    LD_L_A;
    LD_A_addr(wcd56);
    LD_H_A;
    LD_DE(wcc60);
    CALL(aFunction1191ad);
    RET_C ;
    LD_A_addr(wcc60);
    AND_A_A;
    IF_Z goto asm_118ffa;
    LD_A_addr(wcd51);
    LD_L_A;
    LD_A_addr(wcd52);
    LD_H_A;
    LD_DE(wcc60);
    CALL(aFunction1191ad);
    RET_C ;
    LD_A_addr(wcc60);
    AND_A_A;
    IF_Z goto asm_118ff2;
    LD_HL(mText_SentSaveFileReadingNews);
    goto asm_118ff5;


asm_118ff2:
    LD_HL(mText_ReadingNews);


asm_118ff5:
    CALL(aBattleTowerRoomMenu_SetMessage);
    JR(mFunction119009);


asm_118ffa:
    LD_HL(mText_ReadingNews);
    CALL(aBattleTowerRoomMenu_SetMessage);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119009(void){
    CALL(aFunction118440);
    CALL(aFunction119300);
    LD_A_addr(wcd55);
    LD_L_A;
    LD_A_addr(wcd56);
    LD_H_A;
    LD_DE(wcc60);
    CALL(aFunction1191ad);
    RET_C ;
    LD_HL(wc346);
    LD_A(0x8);
    LD_hli_A;
    LD_A(0xc6);
    LD_hli_A;
    LD_A_addr(wcd4b);
    LD_hli_A;
    LD_A_addr(wcd4c);
    LD_hli_A;
    LD_A(0x8);
    LD_hli_A;
    LD_A(0xc7);
    LD_hli_A;
    LD_A(0x60);
    LD_hli_A;
    LD_A(0xcc);
    LD_hli_A;
    CALL(aFunction119eb4);
    CALL(aFunction119ec2);
    LD_A(0x40);
    LD_addr_A(wcd89);
    LD_HL(wc346);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    LD_A(MOBILEAPI_16);
    JP(mFunction119e2b);

}

void Function119054(void){
    LD_A(0x6);
    CALL(aOpenSRAM);
    LD_HL(wd002);
    LD_A_addr(wcd4f);
    LD_E_A;
    LD_A_addr(wcd50);
    LD_D_A;
    LD_A_addr(w3_d000);
    LD_C_A;
    LD_A_addr(w3_d000 + 1);
    LD_B_A;
    CALL(aFunction119192);
    RET_C ;
    LD_A_addr(wcd89);
    AND_A(0x1);
    IF_Z goto asm_11908a;
    LD_A(0x6);
    LDH_addr_A(rSVBK);
    LD_HL(wd002);
    LD_A_addr(w3_d000);
    LD_C_A;
    LD_A_addr(w3_d000 + 1);
    LD_B_A;
    CALL(aFunction119192);
    RET_C ;


asm_11908a:
    CALL(aCloseSRAM);
    LD_A(0x3);  // ???
    LDH_addr_A(rSVBK);
    LD_A(BANK(s5_b1b3));  // aka BANK(s5_b1b4) and BANK(s5_aa7f) and BANK(s5_b2f3) and BANK(s5_b2f4)
    CALL(aOpenSRAM);
    LD_A_addr(wcd4f);
    LD_addr_A(s5_b1b3);
    LD_A_addr(wcd50);
    LD_addr_A(s5_b1b4);
    LD_HL(wcd20);
    LD_DE(s5_aa7f);
    LD_BC(12);
    CALL(aCopyBytes);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wd474));  // aka BANK(wd475)
    LDH_addr_A(rSVBK);
    LD_A_addr(wd474);
    LD_addr_A(s5_b2f3);
    LD_HL(wd475);
    LD_DE(s5_b2f4);
    LD_BC(4);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aCloseSRAM);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function1190d0(void){
    LD_A(BANK(w3_d000));
    LDH_addr_A(rSVBK);
    LD_A_addr(wcd57);
    LD_L_A;
    LD_A_addr(wcd58);
    LD_H_A;
    LD_DE(wcc60);
    CALL(aFunction1191ad);
    RET_C ;
    LD_DE(w3_d000);
    LD_BC(0x1000);
    JP(mFunction118b10);

}

void Function1190ec(void){
    LD_A(BANK(s5_aa73));
    CALL(aOpenSRAM);
    LD_HL(wBGMapBuffer);
    LD_DE(s5_aa73);
    LD_BC(12);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    LD_A(BANK(s5_aa72));
    CALL(aOpenSRAM);
    LD_A(0x1);
    LD_addr_A(s5_aa72);
    CALL(aCloseSRAM);
    LD_A(BANK(s6_a000));
    CALL(aOpenSRAM);
    LD_A_addr(w3_d000);
    LD_C_A;
    LD_A_addr(w3_d000 + 1);
    LD_B_A;
    LD_HL(wd002);
    LD_DE(s6_a000);
    CALL(aFunction119192);
    RET_C ;
    LD_A_addr(wcd89);
    AND_A(0x1);
    IF_Z goto asm_11913e;
    LD_A(BANK(w6_d000));
    LDH_addr_A(rSVBK);
    LD_A_addr(w6_d000);
    LD_C_A;
    LD_A_addr(w6_d000 + 1);
    LD_B_A;
    LD_HL(w6_d000 + 2);
    CALL(aFunction119192);
    RET_C ;


asm_11913e:
    LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    LDH_addr_A(rSVBK);
    CALL(aCloseSRAM);
    LD_HL(mText_ReceivedNews);
    CALL(aBattleTowerRoomMenu_SetMessage);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function11914e(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    LD_A(0x1c);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    RET;

}

void Function11915d(void){
    LD_HL(w3_d802);
    LD_DE(wcd20);
    LD_BC(12);
    CALL(aCopyBytes);
    LD_A(BANK(s5_aa7f));
    CALL(aOpenSRAM);
    LD_HL(wBGMapBuffer);
    LD_DE(s5_aa7f);
    LD_C(12);

asm_119176:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto asm_119184;
    INC_HL;
    DEC_C;
    IF_NZ goto asm_119176;
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    goto asm_11918e;


asm_119184:
    LD_A(0x16);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    LD_A(0xb);
    LD_addr_A(wMobileErrorCodeBuffer);


asm_11918e:
    CALL(aCloseSRAM);
    RET;

}

void Function119192(void){
    INC_B;
    INC_C;
    goto asm_11919e;


asm_119196:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A(0xbf);
    CP_A_D;
    IF_C goto asm_1191a6;


asm_11919e:
    DEC_C;
    IF_NZ goto asm_119196;
    DEC_B;
    IF_NZ goto asm_119196;
    AND_A_A;
    RET;


asm_1191a6:
    LD_A(0xd3);
    CALL(aSetMobileErrorCode);
    SCF;
    RET;

}

void Function1191ad(void){
    PUSH_BC;
    LD_C(0x0);
    LD_A(0x5);
    LDH_addr_A(rSVBK);

asm_1191b4:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    AND_A_A;
    IF_Z goto asm_1191cc;
    INC_C;
    LD_A_C;
    CP_A(0xa6);
    IF_C goto asm_1191b4;
    LD_A(0xda);
    CALL(aSetMobileErrorCode);
    LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    LDH_addr_A(rSVBK);
    POP_BC;
    SCF;
    RET;


asm_1191cc:
    LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    LDH_addr_A(rSVBK);
    POP_BC;
    AND_A_A;
    RET;

}

void Function1191d3(void){
    LD_HL(w3_d100 + 2);
    LD_A_L;
    LD_addr_A(wcd53);
    LD_A_H;
    LD_addr_A(wcd54);
    CALL(aFunction11920f);
    LD_A_L;
    LD_addr_A(wcd51);
    LD_A_addr(wcd4a);
    LD_A_H;
    LD_addr_A(wcd52);
    CALL(aFunction11920f);
    LD_A_L;
    LD_addr_A(wcd55);
    LD_A_addr(wcd4a);
    LD_A_H;
    LD_addr_A(wcd56);
    CALL(aFunction11920f);
    LD_A_addr(wcd49);
    LD_A_L;
    LD_addr_A(wcd57);
    LD_A_addr(wcd4a);
    LD_A_H;
    LD_addr_A(wcd58);
    CALL(aFunction11920f);
    RET;

}

void Function11920f(void){

asm_11920f:
    CALL(aFunction118b9a);
    RET_NC ;
    LD_A_hli;
    CP_A(0xd);
    IF_NZ goto asm_11920f;
    LD_A_hli;
    CP_A(0xa);
    IF_NZ goto asm_11920f;
    DEC_HL;
    XOR_A_A;
    LD_hld_A;
    LD_hli_A;
    INC_HL;
    RET;

}

void Function119223(void){
    XOR_A_A;
    LD_addr_A(wcd4b);
    LD_addr_A(wcd4c);
    LD_A(BANK(s5_b092));  // aka BANK(s5_b1b1) and BANK(s5_b1b2) and BANK(s5_b1d3)
    CALL(aOpenSRAM);
    LD_HL(wc3cd);
    LD_DE(s5_b092);
    LD_BC(31);
    CALL(aCopyBytes);
    DEC_DE;
    XOR_A_A;
    LD_de_A;
    LD_HL(w3_d810);

asm_119241:
    LD_A_hli;
    CP_A(0x50);
    IF_NZ goto asm_119241;
    LD_A_hli;
    LD_addr_A(wcd4f);
    LD_A_hli;
    LD_addr_A(wcd50);
    LD_A_hli;
    LD_addr_A(s5_b1b1);
    LD_C_A;
    LD_A_hli;
    LD_addr_A(s5_b1b2);
    LD_B_A;
    LD_DE(s5_b1d3);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    LD_E_L;
    LD_D_H;
    LD_HL(wc608);

asm_119266:
    LD_A_de;
    INC_DE;
    CP_A(0xff);
    IF_Z goto asm_1192c2;
    CP_A(0xfe);
    IF_Z goto asm_1192a5;
    CALL(aOpenSRAM);
    LD_A_de;
    INC_DE;
    LD_C_A;
    LD_A_de;
    INC_DE;
    LD_B_A;
    LD_A_de;
    INC_DE;
    PUSH_DE;
    PUSH_AF;
    LD_A_addr(wcd4b);
    LD_E_A;
    LD_A_addr(wcd4c);
    LD_D_A;
    POP_AF;

asm_119286:
    PUSH_AF;
    LD_A_bc;
    INC_BC;
    LD_hli_A;
    INC_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_119286;
    CALL(aCloseSRAM);
    LD_A_E;
    LD_addr_A(wcd4b);
    LD_A_D;
    LD_addr_A(wcd4c);
    POP_DE;

asm_11929b:
    AND_A_A;
    IF_Z goto asm_119266;
    LD_A(0xd3);
    CALL(aSetMobileErrorCode);
    SCF;
    RET;


asm_1192a5:
    LD_A_addr(wcd4b);
    LD_C_A;
    LD_A_addr(wcd4c);
    LD_B_A;
    LD_A_de;
    INC_DE;

asm_1192af:
    PUSH_AF;
    LD_A_de;
    INC_DE;
    LD_hli_A;
    INC_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_1192af;
    LD_A_C;
    LD_addr_A(wcd4b);
    LD_A_B;
    LD_addr_A(wcd4c);
    goto asm_11929b;


asm_1192c2:
    LD_A_E;
    LD_addr_A(wcd4d);
    LD_A_D;
    LD_addr_A(wcd4e);
    AND_A_A;
    RET;

}

void Function1192cc(void){
    LD_A(BANK(s5_aa73));
    CALL(aOpenSRAM);
    LD_HL(s5_aa73);
    LD_DE(wc608);
    LD_BC(12);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    LD_HL(wc608);
    LD_DE(wcd20);
    LD_C(0xc);

asm_1192e8:
    LD_A_de;
    INC_DE;
    LD_B_A;
    LD_A_hli;
    CP_A_B;
    IF_NZ goto asm_1192fe;
    DEC_C;
    IF_NZ goto asm_1192e8;
    LD_A(0x1f);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x27);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    SCF;
    RET;


asm_1192fe:
    AND_A_A;
    RET;

}

void Function119300(void){
    XOR_A_A;
    LD_addr_A(wcd4b);
    LD_addr_A(wcd4c);
    LD_A_addr(wcd4d);
    LD_E_A;
    LD_A_addr(wcd4e);
    LD_D_A;
    LD_HL(wc608);
    LD_A_addr(wcd4b);
    LD_C_A;
    LD_A_addr(wcd4c);
    LD_B_A;

asm_11931a:
    LD_A_de;
    INC_DE;
    CP_A(0x50);
    IF_Z goto asm_119324;
    LD_hli_A;
    INC_BC;
    goto asm_11931a;


asm_119324:
    LD_A(0x3d);
    LD_hli_A;
    INC_BC;
    LD_A_C;
    LD_addr_A(wcd4b);
    LD_A_B;
    LD_addr_A(wcd4c);
    LD_A_de;
    INC_DE;
    CALL(aOpenSRAM);
    LD_A_de;
    INC_DE;
    LD_C_A;
    LD_A_de;
    INC_DE;
    LD_B_A;
    LD_A_de;
    INC_DE;
    PUSH_DE;
    PUSH_AF;
    LD_A_addr(wcd4b);
    LD_E_A;
    LD_A_addr(wcd4c);
    LD_D_A;
    POP_AF;

asm_119348:
    PUSH_AF;
    LD_A_bc;
    AND_A(0xf0);
    SWAP_A;
    CALL(aFunction1197bf);
    LD_hli_A;
    INC_DE;
    LD_A_bc;
    INC_BC;
    AND_A(0xf);
    CALL(aFunction1197bf);
    LD_hli_A;
    INC_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_119348;
    CALL(aCloseSRAM);
    LD_A_E;
    LD_addr_A(wcd4b);
    LD_A_D;
    LD_addr_A(wcd4c);
    POP_DE;
    LD_A_de;
    CP_A(0x50);
    IF_Z goto asm_11937f;
    LD_A_addr(wcd4b);
    LD_C_A;
    LD_A_addr(wcd4c);
    LD_B_A;
    LD_A(0x26);
    LD_hli_A;
    INC_BC;
    goto asm_11931a;


asm_11937f:
    RET;

}

void Function119380(void){
    LD_A(0x80);
    LD_addr_A(wcd49);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119388(void){
    LD_HL(wcd49);
    DEC_hl;
    RET_NZ ;
    LD_HL(wcc60);
    CALL(aFunction118e39);
    LD_A(0x9);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x10);
    LD_addr_A(wMobileInactivityTimerSeconds);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function1193a0();
}

void Function1193a0(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    CALL(aDelayFrame);
    LD_A(0x8);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    LD_HL(wc346);
    LD_A(LOW(w3_d000));
    LD_hli_A;
    LD_A(HIGH(w3_d000));
    LD_hli_A;
    LD_A_addr(wcd3b);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_A(LOW(wc708));
    LD_hli_A;
    LD_A(HIGH(wc708));
    LD_hli_A;
    LD_A(0x60);
    LD_hli_A;
    LD_A(0xcc);
    LD_hli_A;
    CALL(aFunction119eb4);
    CALL(aFunction119ec2);
    LD_A(0x40);
    LD_addr_A(wcd89);
    LD_HL(wc346);
    LD_DE(w3_de00);
    LD_BC(0x200);
    LD_A(MOBILEAPI_16);
    JP(mFunction119e2b);

}

void Function1193e3(void){
    LD_HL(wcd49);
    DEC_hl;
    RET_NZ ;
    LD_HL(wcc60);
    CALL(aFunction118e39);
    LD_A(0x9);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x11);
    LD_addr_A(wMobileInactivityTimerSeconds);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function1193fb();
}

void Function1193fb(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    CALL(aDelayFrame);
    LD_A(0x8);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    JP(mFunction118b10);

}

void Function119413(void){
    LD_A(0x6);  // ???
    CALL(aOpenSRAM);
    LD_A_addr(w3_d000);
    LD_C_A;
    LD_A_addr(w3_d000 + 1);
    LD_B_A;
    DEC_BC;
    DEC_BC;
    LD_HL(wd002);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    CALL(aFunction119192);
    RET_C ;
    LD_A_addr(wcd89);
    AND_A(0x1);
    IF_Z goto asm_119447;
    LD_A(BANK(w6_d000));
    LDH_addr_A(rSVBK);
    LD_A_addr(w6_d000);
    LD_C_A;
    LD_A_addr(w6_d000 + 1);
    LD_B_A;
    LD_HL(w6_d000 + 2);
    CALL(aFunction119192);
    RET_C ;


asm_119447:
    LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    LDH_addr_A(rSVBK);
    CALL(aCloseSRAM);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119451(void){
    LD_A_addr(wcd89);
    AND_A(0x1);
    IF_Z goto asm_11945d;
    LD_A(0xd3);
    JP(mSetMobileErrorCode);

asm_11945d:
    XOR_A_A;
    LD_addr_A(wcd50);
    CALL(aFunction119694);
    LD_A_B;
    LD_addr_A(wcd49);
    CALL(aFunction1196cd);
    LD_A_addr(wd002);
    LD_HL(wd003);

    return Function119471();
}

void Function119471(void){
    PUSH_AF;
    LD_A_hli;
    LD_addr_A(wc608);
    LD_A_hli;
    LD_addr_A(wc608 + 3);
    LD_A_hli;
    LD_addr_A(wc608 + 1);
    LD_A_hli;
    LD_addr_A(wc608 + 2);
    LD_A_hli;
    LD_addr_A(wc608 + 4);
    LD_A_hli;
    LD_addr_A(wc608 + 5);
    PUSH_HL;
    LD_A_addr(wc608);
    CP_A(0xff);
    IF_Z goto asm_1194a7;
    LD_A_addr(wc608 + 2);
    CP_A(0xff);
    IF_Z goto asm_1194a7;
    LD_A_addr(wc608 + 1);
    CP_A(0xff);
    IF_NZ goto asm_1194a7;
    CALL(aFunction119584);
    IF_C goto asm_11950c;
    goto asm_1194f0;

asm_1194a7:
    LD_HL(wc608);
    LD_DE(wc608 + 3);
    LD_C(0x3);

asm_1194af:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_C goto asm_1194f3;
    IF_Z goto asm_1194b9;
    IF_NC goto asm_1194bc;

asm_1194b9:
    DEC_C;
    IF_NZ goto asm_1194af;

asm_1194bc:
    LD_C(0x3);
    LD_HL(wcd49);
    LD_DE(wc608);

asm_1194c4:
    LD_A_de;
    INC_DE;
    CP_A(0xff);
    IF_Z goto asm_1194d1;
    CP_A_hl;
    IF_Z goto asm_1194d1;
    IF_C goto asm_1194d5;
    IF_NC goto asm_1194f0;

asm_1194d1:
    INC_HL;
    DEC_C;
    IF_NZ goto asm_1194c4;

asm_1194d5:
    LD_C(0x3);
    LD_HL(wcd49);
    LD_DE(wc608 + 3);

asm_1194dd:
    LD_A_de;
    INC_DE;
    CP_A(0xff);
    IF_Z goto asm_1194ea;
    CP_A_hl;
    IF_C goto asm_1194f0;
    IF_Z goto asm_1194ea;
    IF_NC goto asm_11950c;

asm_1194ea:
    INC_HL;
    DEC_C;
    IF_NZ goto asm_1194dd;
    goto asm_11950c;

asm_1194f0:
    POP_HL;
    goto asm_119557;

asm_1194f3:
    LD_C(0x3);
    LD_HL(wcd49);
    LD_DE(wc608);

asm_1194fb:
    LD_A_de;
    INC_DE;
    CP_A(0xff);
    IF_Z goto asm_119508;
    CP_A_hl;
    IF_C goto asm_11950c;
    IF_Z goto asm_119508;
    IF_NC goto asm_1194d5;

asm_119508:
    INC_HL;
    DEC_C;
    IF_NZ goto asm_1194fb;

asm_11950c:
    POP_HL;
    LD_A(0x1);
    LD_addr_A(wcd50);
    LD_A_L;
    LD_addr_A(wc608);
    LD_A_H;
    LD_addr_A(wc608 + 1);
    LD_DE(wcd69);
    LD_C(0x10);
    LD_B(0x0);

asm_119521:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_NZ goto asm_119528;
    INC_B;

asm_119528:
    DEC_C;
    IF_NZ goto asm_119521;
    LD_A(0x10);
    CP_A_B;
    IF_Z goto asm_119536;
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }
    goto asm_11957a;

asm_119536:
    LD_A_hli;
    CP_A(0x50);
    IF_NZ goto asm_119552;
    LD_A_hli;
    CP_A(0x33);
    IF_NZ goto asm_119553;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    LD_A_addr(wcd83);
    CP_A_C;
    IF_NZ goto asm_119576;
    LD_A_addr(wcd84);
    CP_A_B;
    IF_NZ goto asm_119576;
    goto asm_11955b;

asm_119552:
    INC_HL;

asm_119553:
    INC_HL;
    INC_HL;
    goto asm_11955b;

asm_119557:
    LD_DE(0x14);
    ADD_HL_DE;

asm_11955b:
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    ADD_HL_DE;
    POP_AF;
    DEC_A;
    JP_NZ (mFunction119471);
    LD_A_addr(wcd50);
    AND_A_A;
    IF_Z goto asm_119571;
    LD_A(0x1a);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    RET;

asm_119571:
    LD_A(0xd8);
    JP(mSetMobileErrorCode);

asm_119576:
    LD_A(0x10);
    goto asm_11957c;

asm_11957a:
    LD_A(0xf);

asm_11957c:
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    POP_AF;
    CALL(aFunction1195c4);
    RET;

}

void Function119584(void){
    LD_A_addr(wc608);
    LD_B_A;
    LD_A_addr(wc608 + 3);
    LD_C_A;
    CP_A_B;
    IF_C goto asm_11959c;
    LD_A_addr(wcd49);
    CP_A_B;
    IF_C goto asm_1195c2;

asm_119595:
    CP_A_C;
    IF_C goto asm_1195a2;
    IF_Z goto asm_1195a2;
    goto asm_1195c2;

asm_11959c:
    LD_A_addr(wcd49);
    CP_A_B;
    IF_C goto asm_119595;

asm_1195a2:
    LD_A_addr(wc608 + 2);
    LD_B_A;
    LD_A_addr(wc608 + 5);
    LD_C_A;
    CP_A_B;
    IF_C goto asm_1195ba;
    LD_A_addr(wcd4b);
    CP_A_B;
    IF_C goto asm_1195c2;

asm_1195b3:
    CP_A_C;
    IF_C goto asm_1195c0;
    IF_Z goto asm_1195c0;
    goto asm_1195c2;

asm_1195ba:
    LD_A_addr(wcd4b);
    CP_A_B;
    IF_C goto asm_1195b3;

asm_1195c0:
    SCF;
    RET;

asm_1195c2:
    AND_A_A;
    RET;

}

void Function1195c4(void){
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    LD_DE(0xa5);
    LD_A_B;
    CP_A_D;
    IF_C goto asm_1195d9;
    IF_Z goto asm_1195d3;
    IF_NC goto asm_1195f3;

asm_1195d3:
    LD_A_C;
    CP_A_E;
    IF_Z goto asm_1195d9;
    IF_NC goto asm_1195f3;

asm_1195d9:
    LD_DE(wcc60);
    CALL(aCopyBytes);
    XOR_A_A;
    LD_de_A;
    LD_A_addr(wc608);
    LD_L_A;
    LD_A_addr(wc608 + 1);
    LD_H_A;
    LD_DE(wcd69);
    LD_BC(0x10);
    CALL(aCopyBytes);
    RET;

asm_1195f3:
    LD_A(0xd8);
    JP(mSetMobileErrorCode);

}

void Function1195f8(void){
    LD_A(0x11);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x1c);
    LD_addr_A(wMobileInactivityTimerSeconds);
    LD_A(0xf);
    LD_addr_A(wMobileInactivityTimerFrames);
    LD_A(0x14);
    LD_addr_A(wcd47);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119612(void){
    LD_A(0x14);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x1c);
    LD_addr_A(wMobileInactivityTimerSeconds);
    LD_A(0x10);
    LD_addr_A(wMobileInactivityTimerFrames);
    LD_A(0x14);
    LD_addr_A(wcd47);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119629(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    LD_A(0x60);
    LD_L_A;
    LD_A(0xcc);
    LD_H_A;
    CALL(aFunction118e39);
    LD_A(0x9);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x1c);
    LD_addr_A(wMobileInactivityTimerSeconds);
    LD_A(0x14);
    LD_addr_A(wcd47);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function119648();
}

void Function119648(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    CALL(aDelayFrame);
    LD_A(0x8);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    CALL(aFunction118b24);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    LD_A(MOBILEAPI_15);
    JP(mFunction119e2b);

}

void Function119665(void){
    LD_A(0x1a);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function11966d();
}

void Function11966d(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    LD_A_addr(wcd47);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    RET;

}

void Function11967d(void){
    LD_A(0x18);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function119685();
}

void Function119685(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    LD_A(0x14);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    RET;

}

void Function119694(void){
    LD_B(0);
    LD_HL(mUnknown_1196b8);

asm_119699:
    LD_DE(wc708);
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_NZ goto asm_1196af;
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_NZ goto asm_1196b0;
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_NZ goto asm_1196b1;
    RET;

asm_1196af:
    INC_HL;

asm_1196b0:
    INC_HL;

asm_1196b1:
    INC_B;
    LD_A_B;
    CP_A(0x7);
    IF_NZ goto asm_119699;
    RET;

// pushc
// setcharmap ascii
}

const char Unknown_1196b8[][4] = {
    "Mon",
    "Tue",
    "Wed",
    "Thu",
    "Fri",
    "Sat",
    "Sun",

// popc
};

void Function1196cd(void){
    LD_DE(wc719);
    CALL(aFunction1196de);
    LD_addr_A(wcd4a);
    INC_DE;
    CALL(aFunction1196de);
    LD_addr_A(wcd4b);
    RET;

}

void Function1196de(void){
    LD_A_de;
    INC_DE;
// b = ([de] - 48) * 2
// c = ([de] - 48) * 10
    SUB_A(0x30);
    SLA_A;
    LD_B_A;
    SLA_A;
    SLA_A;
    ADD_A_B;
    LD_C_A;
    ADD_HL_BC;
    LD_A_de;
    INC_DE;
    SUB_A(0x30);
    ADD_A_C;
    RET;

}

void Function1196f2(void){
    LD_HL(wd002);

asm_1196f5:
    CALL(aFunction118b9a);
    RET_NC ;
    LD_A_hli;
    CP_A(0xd);
    IF_NZ goto asm_1196f5;
    LD_A_hl;
    CP_A(0xa);
    IF_NZ goto asm_1196f5;
    XOR_A_A;
    LD_hld_A;
    LD_hli_A;
    LD_A_L;
    LD_addr_A(wcd5b);
    LD_A_H;
    LD_addr_A(wcd5c);
    INC_HL;
    LD_E_L;
    LD_D_H;
    LD_A_de;
    INC_DE;
    CP_A(0xd);
    IF_NZ goto asm_119722;
    LD_A_de;
    INC_DE;
    CP_A(0xa);
    IF_NZ goto asm_119722;
    LD_A(0xb);
    JP(mSetMobileErrorCode);


asm_119722:
    CALL(aRandom);
    LD_C(0x0);
    LD_B_C;

asm_119728:
    CALL(aFunction119798);
    LD_A_D;
    CP_A(0xff);
    IF_NZ goto asm_119735;
    LD_A_E;
    CP_A(0xff);
    IF_Z goto asm_11974c;


asm_119735:
    LDH_A_addr(hRandomSub);
    CP_A_D;
    IF_C goto asm_11974c;
    IF_Z goto asm_11973e;
    goto asm_119745;


asm_11973e:
    LDH_A_addr(hRandomAdd);
    CP_A_E;
    IF_C goto asm_11974c;
    IF_Z goto asm_11974c;


asm_119745:
    INC_BC;
    LD_A_C;
    OR_A_B;
    IF_Z goto asm_119770;
    goto asm_119728;


asm_11974c:
    LD_A_addr(wcd5b);
    LD_L_A;
    LD_A_addr(wcd5c);
    LD_H_A;

asm_119754:
    LD_A_hld;
    CP_A(0x58);
    IF_NZ goto asm_119754;
    LD_D(0x0);

asm_11975b:
    INC_D;
    LD_A_hld;
    CP_A(0x58);
    IF_Z goto asm_11975b;
    INC_HL;
    INC_HL;
    LD_A_D;
    DEC_A;
    IF_Z goto asm_11978e;
    DEC_A;
    IF_Z goto asm_119785;
    DEC_A;
    IF_Z goto asm_11977e;
    DEC_A;
    IF_Z goto asm_119775;


asm_119770:
    LD_A(0xd3);
    JP(mSetMobileErrorCode);


asm_119775:
    LD_A_B;
    AND_A(0xf0);
    SWAP_A;
    CALL(aFunction1197bf);
    LD_hli_A;


asm_11977e:
    LD_A_B;
    AND_A(0xf);
    CALL(aFunction1197bf);
    LD_hli_A;


asm_119785:
    LD_A_C;
    AND_A(0xf0);
    SWAP_A;
    CALL(aFunction1197bf);
    LD_hli_A;


asm_11978e:
    LD_A_C;
    AND_A(0xf);
    CALL(aFunction1197bf);
    LD_hli_A;
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119798(void){
    LD_D(0x0);
    LD_E_D;
    CALL(aFunction1197b4);
    SWAP_A;
    OR_A_D;
    LD_D_A;
    CALL(aFunction1197b4);
    OR_A_D;
    LD_D_A;
    CALL(aFunction1197b4);
    SWAP_A;
    OR_A_E;
    LD_E_A;
    CALL(aFunction1197b4);
    OR_A_E;
    LD_E_A;
    RET;

}

void Function1197b4(void){
    LD_A_hli;
    CP_A(0x61);
    IF_NC goto asm_1197bc;
    SUB_A(0x30);
    RET;


asm_1197bc:
    SUB_A(0x57);
    RET;

}

void Function1197bf(void){
    CP_A(0xa);
    IF_NC goto asm_1197c6;
    ADD_A(0x30);
    RET;


asm_1197c6:
    ADD_A(0x57);
    RET;

}

void Function1197c9(void){
    LD_HL(wd002);
    CALL(aFunction118e39);
    LD_A(0x9);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A(0x12);
    LD_addr_A(wMobileInactivityTimerSeconds);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function1197dc();
}

void Function1197dc(void){
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    CALL(aDelayFrame);
    LD_HL(wd002);
    LD_DE(wcc60);
    LD_BC(0x0080);
    CALL(aCopyBytes);
    DEC_DE;
    XOR_A_A;
    LD_de_A;
    CALL(aFunction118b24);
    LD_DE(w3_d000);
    LD_BC(0x1000);
    LD_A(MOBILEAPI_15);
    JP(mFunction119e2b);

}

void Function119800(void){
    LD_A(0xfd);
    LD_addr_A(wc6d0);
    LD_addr_A(wOTTrademonSpecies);
    LD_A_addr(wcd81);
    LD_addr_A(wc74e);
    LD_A_addr(wJumptableIndex);
    PUSH_AF;
    LD_A_addr(wcf64);
    PUSH_AF;
    LD_A_addr(wcf65);
    PUSH_AF;
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    CALL(aFadeToMenu);
    FARCALL(aFunction10803d);
    CALL(aFunction11a9ce);
    CALL(aRestartMapMusic);
    LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    LDH_addr_A(rSVBK);
    POP_AF;
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    POP_AF;
    LD_addr_A(wcf65);
    POP_AF;
    LD_addr_A(wcf64);
    POP_AF;
    LD_addr_A(wJumptableIndex);
    FARCALL(aFunction115dc3);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function11984e(void){
    LD_A_addr(wcd80);
    AND_A_A;
    IF_NZ goto asm_1198a0;
    LD_A_addr(wcd38);
    AND_A_A;
    IF_NZ goto asm_1198a8;
    FARCALL(aFunction170000);
    LD_A_addr(wJumptableIndex);
    PUSH_AF;
    LD_A_addr(wcf64);
    PUSH_AF;
    LD_A_addr(wcf65);
    PUSH_AF;
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    CALL(aFadeToMenu);
    FARCALL(aMobileTradeAnimation_SendGivemonToGTS);
    CALL(aFunction11a9ce);
    CALL(aRestartMapMusic);
    LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    LDH_addr_A(rSVBK);
    POP_AF;
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    POP_AF;
    LD_addr_A(wcf65);
    POP_AF;
    LD_addr_A(wcf64);
    POP_AF;
    LD_addr_A(wJumptableIndex);
    FARCALL(aFunction115dc3);
    JP(mBattleTowerRoomMenu_IncrementJumptable);


asm_1198a0:
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    JP(mBattleTowerRoomMenu_IncrementJumptable);


asm_1198a8:
    FARCALL(aFunction17005a);
    LD_A_addr(wJumptableIndex);
    PUSH_AF;
    LD_A_addr(wcf64);
    PUSH_AF;
    LD_A_addr(wcf65);
    PUSH_AF;
    LD_A_addr(wBattleTowerRoomMenuJumptableIndex);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    CALL(aFadeToMenu);
    FARCALL(aMobileTradeAnimation_RetrieveGivemonFromGTS);
    CALL(aFunction11a9ce);
    CALL(aRestartMapMusic);
    LD_A(MBANK(aw3_d000)); // BANK("Battle Tower RAM")
    LDH_addr_A(rSVBK);
    POP_AF;
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    POP_AF;
    LD_addr_A(wcf65);
    POP_AF;
    LD_addr_A(wcf64);
    POP_AF;
    LD_addr_A(wJumptableIndex);
    FARCALL(aFunction115dc3);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function1198ee(void){
    LD_HL(mText_RegisteringRecord);
    CALL(aBattleTowerRoomMenu_SetMessage);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return Function1198f7();
}

void Function1198f7(void){
    LD_A_addr(wc31a);
    AND_A_A;
    RET_NZ ;
    LD_HL(wc608 + 2);
    CALL(aFunction119940);
    LD_HL(w3_d800);
    LD_A(LOW(wc608));
    LD_hli_A;
    LD_A(HIGH(wc608));
    LD_hli_A;
    LD_A(0xf6);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_A(LOW(wc708));
    LD_hli_A;
    LD_A(HIGH(wc708));
    LD_hli_A;
    LD_A_addr(wcd51);
    LD_hli_A;
    LD_A_addr(wcd52);
    LD_hli_A;
    CALL(aFunction119eb4);
    CALL(aFunction119ec2);
    LD_A(0x40);
    LD_addr_A(wcd89);
    LD_HL(w3_d800);
    LD_DE(w3_de00);
    LD_BC(0x200);
    LD_A(MOBILEAPI_16);
    JP(mFunction119e2b);

}

void Function119937(void){
    FARCALL(aFunction1707f4);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

}

void Function119940(void){
    LD_DE(wc3cd);
    LD_C(0x1e);

asm_119945:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    DEC_C;
    IF_Z goto asm_119953;
    AND_A_A;
    IF_NZ goto asm_119945;
    XOR_A_A;

asm_11994f:
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_11994f;


asm_119953:
    RET;

}

void Function119954(void){
    LD_A(0x1c);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    LD_HL(wc608);
    LD_DE(wc3cd);

asm_119962:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    AND_A_A;
    IF_NZ goto asm_119962;
    CALL(aFunction119ec2);
    LD_HL(wc608);
    LD_A(MOBILEAPI_0F);
    JP(mFunction119e2b);

}

void Function119973(void){
    LD_A(0x1);
    LD_addr_A(wcf64);
    XOR_A_A;
    LD_addr_A(wcf65);
    LD_addr_A(w3_d090);
    LD_DE(w3_d000);
    LD_A(MOBILEAPI_10);
    JP(mFunction119e2b);

}

void Function119987(void){
    LD_HL(w3_d000 + 1);
    LD_A_addr(w3_d000);
    OR_A_hl;
    IF_Z goto asm_1199a0;
    LD_A_addr(wcf64);
    LD_L_A;
    LD_A_addr(wcf65);
    LD_H_A;
    LD_DE(wBGPals2);
    LD_A(MOBILEAPI_11);
    JP(mFunction119e2b);


asm_1199a0:
    LD_A_addr(w3_d090);
    AND_A_A;
    IF_Z goto asm_1199ae;
    LD_A(0x16);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    JP(mFunction119b0d);


asm_1199ae:
    LD_A(0x1b);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    RET;

}

void Function1199b4(void){
    LD_A_addr(w3_d081 + 1);
    AND_A_A;
    IF_NZ goto asm_1199c7;
    LD_A_addr(w3_d081);
    CP_A(0x7);
    IF_NC goto asm_1199c7;
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    JP(mFunction1199ca);


asm_1199c7:
    JP(mFunction119ac9);

}

void Function1199ca(void){
    LD_A(0x20);
    LD_addr_A(wcd89);
    LD_A_addr(wcf64);
    LD_L_A;
    LD_A_addr(wcf65);
    LD_H_A;
    LD_DE(w3_d100);
    LD_BC(0x0700);
    LD_A(MOBILEAPI_14);
    JP(mFunction119e2b);

}

void Function1199e2(void){
    LD_C(0xc);
    LD_DE(mXGameCodePrefix);
    CALL(aFunction119e4f);
    JP_C (mFunction119ac9);
    LD_A_C;
    CP_A(0x1);
    JP_NZ (mFunction119ac9);
    LD_HL(w3_d880);
    LD_BC(mXGameCode);

loop:
    LD_A_bc;
    AND_A_A;
    IF_Z goto game_result_prefix;
    CP_A_hl;
    JP_NZ (mFunction119ac9);
    INC_BC;
    INC_HL;
    goto loop;


game_result_prefix:
    LD_C(0x17);
    LD_DE(mXGameResultPrefix);
    CALL(aFunction119e4f);
    JP_C (mFunction1199e2_asm_119aa7);
    LD_A_C;
    CP_A(0x1);
    JP_NZ (mFunction1199e2_asm_119aa7);
    LD_A_addr(w3_d880);
    CP_A(0x31);
    JP_NZ (mFunction1199e2_asm_119aa7);
    LD_A_addr(w3_d881);
    CP_A(0x20);
    JP_NZ (mFunction1199e2_asm_119aa7);
    LD_A_addr(w3_d88a);
    CP_A(0x20);
    JP_NZ (mFunction1199e2_asm_119aa7);
    LD_A_addr(w3_d894);
    CP_A(0x20);
    JP_NZ (mFunction1199e2_asm_119aa7);
    XOR_A_A;
    LD_addr_A(w3_d8a0);
    LD_addr_A(w3_d8a1);
    LD_addr_A(w3_d8a2);
    LD_addr_A(w3_d8a3);
    LD_HL(w3_d8a0);
    LD_BC(w3_d889);
    CALL(aFunction119e98);
    CALL(aFunction119e98);
    LD_HL(w3_d8a0);
    LD_A_addr(wcd2d);
    CP_A_hl;
    JR_NZ (mFunction119ac9);
    INC_HL;
    LD_A_addr(wcd2c);
    CP_A_hl;
    JR_NZ (mFunction119ac9);
    INC_HL;
    LD_A_addr(wcd2b);
    CP_A_hl;
    JR_NZ (mFunction119ac9);
    INC_HL;
    LD_A_addr(wcd2a);
    CP_A_hl;
    JR_NZ (mFunction119ac9);
    XOR_A_A;
    LD_addr_A(w3_d8a0);
    LD_addr_A(w3_d8a1);
    LD_addr_A(w3_d8a2);
    LD_addr_A(w3_d8a3);
    LD_HL(w3_d8a0);
    LD_BC(w3_d88e);
    CALL(aFunction119e98);
    LD_BC(w3_d893);
    CALL(aFunction119e98);
    LD_HL(w3_d8a0);
    LD_A_addr(wcd2f);
    CP_A_hl;
    IF_NZ goto asm_119aa7;
    INC_HL;
    LD_A_addr(wcd2e);
    CP_A_hl;
    IF_NZ goto asm_119aa7;
    INC_HL;
    LD_A_addr(wcd31);
    CP_A_hl;
    IF_NZ goto asm_119aa7;
    INC_HL;
    LD_A_addr(wcd30);
    CP_A_hl;
    IF_Z goto asm_119aaf;


asm_119aa7:
    LD_A(0x25);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    JP(mFunction119b45);


asm_119aaf:
    LD_A_addr(w3_d090);
    AND_A_A;
    IF_NZ goto asm_119aa7;
    LD_A_addr(w3_d895);
    SUB_A(0x30);
    LD_addr_A(w3_d090);
    LD_A_addr(wcf64);
    LD_addr_A(w3_d090 + 1);
    LD_A_addr(wcf65);
    LD_addr_A(w3_d090 + 2);

    return Function119ac9();
}

void Function119ac9(void){
    LD_A_addr(w3_d000);
    LD_L_A;
    LD_A_addr(w3_d000 + 1);
    LD_H_A;
    DEC_HL;
    LD_A_L;
    LD_addr_A(w3_d000);
    LD_A_H;
    LD_addr_A(w3_d000 + 1);
    LD_A_addr(wcf64);
    LD_L_A;
    LD_A_addr(wcf65);
    LD_H_A;
    INC_HL;
    LD_A_L;
    LD_addr_A(wcf64);
    LD_A_H;
    LD_addr_A(wcf65);
    LD_A(0x10);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    RET;

// pushc
// setcharmap ascii
}

const char XGameCode[] = "CGB-BXTJ-00""\0";

//  //  unreferenced
const char XGameResult[] = "pokemon_crystal";

// popc

void Function119b0d(void){
    LD_A(0x8);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu2);
    LD_A_addr(w3_d090);
    CP_A(0x1);
    IF_Z goto asm_119b23;
    LD_A(0x19);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    JR(mFunction119b3b);


asm_119b23:
    LD_A(0x10);
    LD_addr_A(wcd89);
    LD_A_addr(w3_d090 + 1);
    LD_L_A;
    LD_A_addr(w3_d090 + 2);
    LD_H_A;
    LD_DE(w3_d100);
    LD_BC(0x0700);
    LD_A(MOBILEAPI_12);
    JP(mFunction119e2b);

}

void Function119b3b(void){
    LD_A_addr(w3_d090 + 1);
    LD_L_A;
    LD_A_addr(w3_d090 + 2);
    LD_H_A;
    JR(masm_119b4d);

}

void Function119b45(void){
    LD_A_addr(wcf64);
    LD_L_A;
    LD_A_addr(wcf65);
    LD_H_A;

    return asm_119b4d();
}

void asm_119b4d(void){
    LD_A(MOBILEAPI_13);
    JP(mFunction119e2b);

}

void Function119b52(void){
    LD_A_addr(w3_d090);
    CP_A(0x1);
    IF_NZ goto asm_119b66;
    LD_A(BANK(s5_a800));
    CALL(aOpenSRAM);
    LD_A(0x4);
    LD_addr_A(s5_a800);
    CALL(aCloseSRAM);


asm_119b66:
    LD_A(MOBILEAPI_0E);
    JP(mFunction119e2b);

}

void Function119b6b(void){
    LD_A_addr(w3_d090);
    CP_A(0x1);
    IF_Z goto asm_119b75;
    JP(mBattleTowerRoomMenu_IncrementJumptable);


asm_119b75:
    LD_A_addr(w3_d100);
    LD_B_A;
    LD_A_addr(w3_d100 + 1);
    OR_A_B;
    IF_Z goto asm_119be3;
    LD_HL(w3_d800);
    LD_DE(w3_d100 + 2);

asm_119b85:
    LD_A_de;
    INC_DE;
    CP_A(0xd);
    IF_NZ goto asm_119b85;
    INC_DE;
    LD_A_de;
    CP_A(0xd);
    IF_NZ goto asm_119b85;
    INC_DE;
    INC_DE;

asm_119b93:
    LD_A_de;
    INC_DE;
    CP_A(0xd);
    IF_Z goto asm_119bfa;
    CALL(aFunction119b6b_decodeBase64Character);
    RET_C ;
    LD_hli_A;
    LD_A_de;
    INC_DE;
    CALL(aFunction119b6b_decodeBase64Character);
    RET_C ;
    LD_hli_A;
    LD_A_de;
    INC_DE;
    CALL(aFunction119b6b_decodeBase64Character);
    RET_C ;
    LD_hli_A;
    LD_A_de;
    INC_DE;
    CALL(aFunction119b6b_decodeBase64Character);
    RET_C ;
    LD_hl_A;
    PUSH_DE;
    LD_D_hl;
    DEC_HL;
    LD_C_hl;
    DEC_HL;
    LD_B_hl;
    DEC_HL;
    LD_A_hl;
    SLA_B;
    SLA_B;
    SLA_B;
    RLA;
    SLA_B;
    RLA;
    LD_hli_A;
    LD_hl_B;
    INC_HL;
    RRC_C;
    RRC_C;
    LD_hl_C;
    DEC_HL;
    LD_A(0xf);
    AND_A_C;
    OR_A_hl;
    LD_hli_A;
    LD_A_hli;
    AND_A(0xc0);
    OR_A_hl;
    DEC_HL;
    LD_hld_A;
    DEC_HL;
    POP_DE;
    INC_HL;
    INC_HL;
    INC_HL;
    LD_A_H;
    CP_A(0xe0);
    IF_C goto asm_119b93;


asm_119be3:
    LD_A(0x19);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    LD_A(BANK(s5_a800));
    CALL(aOpenSRAM);
    LD_A(0x1);
    LD_addr_A(s5_a800);
    CALL(aCloseSRAM);
    XOR_A_A;
    LD_addr_A(w3_d090);
    RET;


asm_119bfa:
    INC_DE;
    LD_A_de;
    CP_A(0xd);
    IF_NZ goto asm_119b93;
    LD_A_L;
    CP_A(LOW(w3_d869));
    IF_NZ goto asm_119be3;
    LD_A_H;
    CP_A(HIGH(w3_d869));
    IF_NZ goto asm_119be3;
    LD_A(BANK(s5_b090));  // aka BANK(s5_b091) and BANK(s5_b023)
    CALL(aOpenSRAM);
    LD_A_addr(wcf64);
    LD_addr_A(s5_b090);
    LD_A_addr(wcf65);
    LD_addr_A(s5_b091);
    LD_HL(w3_d800);
    LD_DE(s5_b023);
    LD_BC(105);
    CALL(aCopyBytes);
    LD_A(0x3);
    LD_addr_A(s5_a800);
    CALL(aCloseSRAM);
    LD_HL(w3_d800);
    LD_DE(wc608);
    LD_BC(105);
    CALL(aCopyBytes);
    JP(mBattleTowerRoomMenu_IncrementJumptable);

// pushc
// setcharmap ascii


decodeBase64Character:
    CP_A('+');  // "+"
    IF_C goto asm_119c68;
    IF_Z goto asm_119c80;
    CP_A('/');  // "/"
    IF_C goto asm_119c68;
    IF_Z goto asm_119c84;
    CP_A('0');  // "0"
    IF_C goto asm_119c68;
    CP_A('9' + 1);  // "9" + 1
    IF_C goto asm_119c88;
    CP_A('=');  // "="
    IF_C goto asm_119c68;
    IF_Z goto asm_119c8c;
    CP_A('A');  // "A"
    IF_C goto asm_119c68;
    CP_A('Z' + 1);  // "Z" + 1
    IF_C goto asm_119c8f;
    CP_A('a');  // "a"
    IF_C goto asm_119c68;
    CP_A('z' + 1);  // "z" + 1
    IF_C goto asm_119c93;

// popc


asm_119c68:
    LD_A(0x19);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    LD_A(BANK(s5_a800));
    CALL(aOpenSRAM);
    LD_A(0x1);
    LD_addr_A(s5_a800);
    CALL(aCloseSRAM);
    XOR_A_A;
    LD_addr_A(w3_d090);
    SCF;
    RET;


asm_119c80:
    LD_A(0x3e);
    AND_A_A;
    RET;


asm_119c84:
    LD_A(0x3f);
    AND_A_A;
    RET;


asm_119c88:
    ADD_A(0x4);
    AND_A_A;
    RET;


asm_119c8c:
    XOR_A_A;
    AND_A_A;
    RET;


asm_119c8f:
    SUB_A(0x41);
    AND_A_A;
    RET;


asm_119c93:
    SUB_A(0x47);
    AND_A_A;
    RET;

}

void BattleTowerRoomMenu_UberRestrictionMessage(void){
    LD_HL(mText_UberRestriction);
    CALL(aBattleTowerRoomMenu_SetMessage);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);
    JR(mBattleTowerRoomMenu_WaitForMessage);

}

void BattleTowerRoomMenu_PartyMonTopsThisLevelMessage(void){
    LD_HL(mText_PartyMonTopsThisLevel);
    CALL(aBattleTowerRoomMenu_SetMessage);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return BattleTowerRoomMenu_WaitForMessage();
}

void BattleTowerRoomMenu_WaitForMessage(void){
    LD_A_addr(wc31a);
    AND_A_A;
    RET_NZ ;
    LD_A(0x80);
    LD_addr_A(wcd50);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return BattleTowerRoomMenu_DelayRestartMenu();
}

void BattleTowerRoomMenu_DelayRestartMenu(void){
// Loops while (--[wcd50] != 0),
//   to create some sort of "delay" after the message is written on the screen,
//   before starting the menu again.
    LD_HL(wcd50);
    DEC_hl;
    RET_NZ ;
    LD_A(0x0);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    RET;

}

void BattleTowerRoomMenu_QuitMessage(void){
    LD_A_addr(wcd38);
    AND_A_A;
    IF_Z goto asm_119cd1;
    DEC_A;
    IF_Z goto asm_119cd6;
    LD_HL(mText_QuitReadingNews);
    goto asm_119cd9;


asm_119cd1:
    LD_HL(mText_CancelBattleRoomChallenge);
    goto asm_119cd9;


asm_119cd6:
    LD_HL(mText_ExitGymLeaderHonorRoll);


asm_119cd9:
    CALL(aBattleTowerRoomMenu_SetMessage);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return BattleTowerRoomMenu_PlaceYesNoMenu();
}

void BattleTowerRoomMenu_PlaceYesNoMenu(void){
    LD_A_addr(wc31a);
    AND_A_A;
    RET_NZ ;
    LD_A(0xf);
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    CALL(aBattleTowerRoomMenu_IncrementJumptable);

    return BattleTowerRoomMenu_UpdateYesNoMenu();
}

void BattleTowerRoomMenu_UpdateYesNoMenu(void){
// Only ever called when [wBattleTowerRoomMenu2JumptableIndex] is $10
    CALL(aBattleTowerRoomMenu2);
    RET_C ;
    LD_A_addr(wMobileInactivityTimerFrames);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    RET;

}

void MenuHeader_119cf7(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['12', '7', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return MenuData_119cff();
}

void MenuData_119cff(void){
//  //  unreferenced
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['15', '7', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return String_119d07();
}

void String_119d07(void){
    //db ['"   ▼@"'];

    return Strings_L10ToL100();
}

void Strings_L10ToL100(void){
    //db ['" L:10 @@"'];
    //db ['" L:20 @@"'];
    //db ['" L:30 @@"'];
    //db ['" L:40 @@"'];
    //db ['" L:50 @@"'];
    //db ['" L:60 @@"'];
    //db ['" L:70 @@"'];
    //db ['" L:80 @@"'];
    //db ['" L:90 @@"'];
    //db ['" L:100@@"'];
    //db ['"CANCEL@@"'];

    return Strings_Ll0ToL40();
}

void Strings_Ll0ToL40(void){
    //db ['" L:10 @@"'];
    //db ['" L:20 @@"'];
    //db ['" L:30 @@"'];
    //db ['" L:40 @@"'];
    //db ['"CANCEL@@"'];

    return BattleTowerCancelString();
}

void BattleTowerCancelString(void){
//  //  unreferenced
    //db ['"CANCEL@"'];

    return BattleTower_LevelCheck();
}

void BattleTower_LevelCheck(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wPartyMons));
    LDH_addr_A(rSVBK);
    LD_A_addr(wcd4f);
    LD_C(10);
    CALL(aSimpleMultiply);
    LD_HL(wcd50);
    LD_hl_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_DE(wPartyMon1Level);
    LD_A_addr(wPartyCount);

party_loop:
    PUSH_AF;
    LD_A_de;
    PUSH_HL;
    PUSH_DE;
    POP_HL;
    ADD_HL_BC;
    PUSH_HL;
    POP_DE;
    POP_HL;
    CP_A_hl;
    IF_Z goto equal;
    IF_NC goto exceeds;

equal:
    POP_AF;
    DEC_A;
    IF_NZ goto party_loop;
    POP_AF;
    LDH_addr_A(rSVBK);
    AND_A_A;
    RET;


exceeds:
    POP_AF;
    LD_A(0x4);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    POP_AF;
    LDH_addr_A(rSVBK);
    SCF;
    RET;

}

void BattleTower_UbersCheck(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A_addr(wcd4f);
    CP_A(70 / 10);
    IF_NC goto level_70_or_more;
    LD_A(BANK(wPartyMons));
    LDH_addr_A(rSVBK);
    LD_HL(wPartyMon1Level);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_DE(wPartySpecies);
    LD_A_addr(wPartyCount);

loop:
    PUSH_AF;
    LD_A_de;
    CP_A(MEWTWO);
    IF_Z goto uber;
    CP_A(MEW);
    IF_Z goto uber;
    CP_A(LUGIA);
    IF_C goto next;
    CP_A(NUM_POKEMON + 1);
    IF_NC goto next;

uber:
    LD_A_hl;
    CP_A(70);
    IF_C goto uber_under_70;

next:
    ADD_HL_BC;
    INC_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;

level_70_or_more:
    POP_AF;
    LDH_addr_A(rSVBK);
    AND_A_A;
    RET;


uber_under_70:
    POP_AF;
    LD_A_de;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(wStringBuffer1);
    LD_DE(wcd49);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A(0xa);
    LD_addr_A(wBattleTowerRoomMenuJumptableIndex);
    POP_AF;
    LDH_addr_A(rSVBK);
    SCF;
    RET;

}

void Function119e2b(void){
    CALL(aMobileAPI);

    return BattleTowerRoomMenu_IncrementJumptable();
}

void BattleTowerRoomMenu_IncrementJumptable(void){
    LD_HL(wBattleTowerRoomMenuJumptableIndex);
    INC_hl;
    RET;
}

// pushc
// setcharmap ascii
const char XGameCodePrefix[] = "X-Game-code:\n";
const char XGameResultPrefix[] = "X-Game-result:\n";

void Function119e4f(void){
    PUSH_BC;
    LD_HL(w3_d100);
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;

loop:
    LD_A_de;
    CP_A_hl;
    IF_Z goto found_equality;

next:
    INC_HL;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;

return_carry:
    POP_BC;
    SCF;
    RET;


found_equality:
    PUSH_DE;

loop2:
    LD_A_de;
    INC_DE;
    CP_A('\n');  // "\n"
    IF_Z goto newline;
    CP_A_hl;
    IF_NZ goto unequal;
    INC_HL;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop2;
    POP_DE;
    goto return_carry;


unequal:
    POP_DE;
    goto next;


newline:
    POP_DE;
    POP_BC;
    INC_HL;
    LD_DE(w3_d880);

loop3:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    CP_A(0xd);
    IF_Z goto finish;
    DEC_C;
    IF_NZ goto loop3;
    SCF;
    RET;


finish:
    AND_A_A;
    RET;

}

void Function119e8e(void){
    CP_A(0x60);
    IF_C goto less_than_0x60;
    SUB_A(0x57);
    RET;


less_than_0x60:
    SUB_A(0x30);
    RET;

}

void Function119e98(void){
    LD_A(0x2);

loop:
    PUSH_AF;
    LD_A_bc;
    DEC_BC;
    CALL(aFunction119e8e);
    OR_A_hl;
    LD_hl_A;
    LD_A_bc;
    DEC_BC;
    CALL(aFunction119e8e);
    RLCA;
    RLCA;
    RLCA;
    RLCA;
    OR_A_hl;
    LD_hl_A;
    INC_HL;
    POP_AF;
    DEC_A;
    AND_A_A;
    IF_NZ goto loop;
    RET;

}

void Function119eb4(void){
    XOR_A_A;
    LD_addr_A(wc3cc);
    LD_DE(wc3ac);

loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    AND_A_A;
    IF_NZ goto loop;
    RET;

}

void Function119ec2(void){
    LD_A(BANK(sMobileLoginPassword));
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_addr_A(sMobileLoginPassword + MOBILE_LOGIN_PASSWORD_LENGTH);
    LD_DE(sMobileLoginPassword + 1);

loop:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    AND_A_A;
    IF_NZ goto loop;
    CALL(aCloseSRAM);
    RET;

}

void BattleTowerRoomMenu2(void){
    LDH_A_addr(rSVBK);
    LD_addr_A(wcd8c);
    LD_A(0x1);
    LDH_addr_A(rSVBK);

    CALL(aBattleTowerRoomMenu2_RunJumptable);

    LD_A_addr(wcd8c);
    LDH_addr_A(rSVBK);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;


RunJumptable:
    //jumptable ['.Jumptable', 'wBattleTowerRoomMenu2JumptableIndex']


Jumptable:
    //dw ['Function119f3f'];
    //dw ['Function119f45'];
    //dw ['Function119f56'];
    //dw ['Function119f76'];
    //dw ['Function119f98'];
    //dw ['Function11a113'];
    //dw ['Function11a129'];
    //dw ['Function11a131'];
    //dw ['Function11a13d'];
    //dw ['Function11a14b'];
    //dw ['Function11a16d'];
    //dw ['Function11a192'];
    //dw ['Function11a2e6'];
    //dw ['Function11a302'];
    //dw ['Function11a33a'];
    //dw ['BattleTowerRoomMenu2_PlaceYesNoMenu'];
    //dw ['BattleTowerRoomMenu2_UpdateYesNoMenu'];
    //dw ['Function11a357'];
    //dw ['Function11a36b'];
    //dw ['Function11a38d'];
    //dw ['Function11a3c5'];
    //dw ['Function11a3d9'];
    //dw ['Function11a3f9'];
    //dw ['Function11a41b'];
    //dw ['Function11a452'];
    //dw ['Function11a47a'];
    //dw ['Function11a488'];
    //dw ['Function11a49e'];
    //dw ['Function11a4db'];
    //dw ['Function11a4e8'];
    //dw ['Function11a4fe'];
    //dw ['Function11a466'];
    //dw ['Function11a47a'];

    return Function119f3f();
}

void Function119f3f(void){
    CALL(aFunction11a5b9);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function119f45(void){
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a661);
    CALL(aPlaceString);
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function119f56(void){
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_119f62;
    DEC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    SCF;
    RET;


asm_119f62:
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a6aa);
    CALL(aPlaceString);
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function119f76(void){
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_119f82;
    DEC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    SCF;
    RET;


asm_119f82:
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a679);
    CALL(aPlaceString);
    CALL(aFunction11a5f5);
    XOR_A_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function119f98(void){
    CALL(aFunction11a536);
    RET_C ;
    CALL(aPlayClickSFX);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_NZ goto asm_119fef;
    CALL(aExitMenu);
    CALL(aFunction11a63c);
    XOR_A_A;
    LD_addr_A(wScriptVar);
    CALL(aFunction11a00e);
    LD_A_addr(wScriptVar);
    AND_A_A;
    IF_Z goto asm_119fd4;
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    FARCALL(aFunction115dc3);
    LD_A_addr(wcd33);
    LD_addr_A(wcf66);
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    SCF;
    RET;


asm_119fd4:
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a692);
    CALL(aPlaceString);
    LD_A(0x1);
    LD_addr_A(wc30d);
    LD_A(0x1);
    LD_addr_A(wc314);
    FARCALL(aReloadMapPart);
    AND_A_A;
    RET;


asm_119fef:
    CALL(aExitMenu);
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    LD_A_addr(wMobileInactivityTimerSeconds);
    LD_addr_A(wcf66);
    FARCALL(aFunction115dc3);
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    SCF;
    RET;

}

void Function11a00e(void){
    LD_A(BANK(sMobileLoginPassword));
    CALL(aOpenSRAM);
    LD_A_addr(sMobileLoginPassword);
    AND_A_A;
    IF_Z goto asm_11a02a;
    LD_A_addr(sMobileLoginPassword + 1);
    CALL(aCloseSRAM);
    AND_A_A;
    RET_NZ ;
    LD_A(BANK(sMobileLoginPassword));
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_addr_A(sMobileLoginPassword);


asm_11a02a:
    CALL(aCloseSRAM);
    LD_A_addr(wBGMapPalBuffer);
    AND_A_A;
    IF_Z goto asm_11a039;
    DEC_A;
    IF_Z goto asm_11a081;
    JP(mFunction11a0ca);


asm_11a039:
    LD_A(BANK(w3_d800));
    LDH_addr_A(rSVBK);
    LD_HL(wc608);
    LD_DE(w3_d800);
    LD_BC(246);
    CALL(aCopyBytes);
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    CALL(aFadeToMenu);
    FARCALL(aFunction11765d);
    CALL(aFunction11a9ce);
    LD_A(BANK(w3_d800));
    LDH_addr_A(rSVBK);
    LD_HL(w3_d800);
    LD_DE(wc608);
    LD_BC(246);
    CALL(aCopyBytes);
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    FARCALL(aFunction115d99);
    LD_C(0x0);
    FARCALL(aFunction115e18);
    LD_A(0x1);
    LD_addr_A(wc305);
    RET;


asm_11a081:
    XOR_A_A;
    LD_addr_A(wMenuBorderLeftCoord);
    LD_addr_A(wMenuBorderTopCoord);
    LD_A(0x13);
    LD_addr_A(wMenuBorderRightCoord);
    LD_A(0x5);
    LD_addr_A(wMenuBorderBottomCoord);
    CALL(aPushWindow);
    FARCALL(aFunction11765d);
    FARCALL(aFunction117ab4);
    FARCALL(aStubbed_Function106462);
    FARCALL(aFunction106464);
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    FARCALL(aFunction115d99);
    LD_C(0x0);
    FARCALL(aFunction115e18);
    LD_A(0x1);
    LD_addr_A(wc305);
    RET;

}

void Function11a0ca(void){
    XOR_A_A;
    LD_addr_A(wMenuBorderLeftCoord);
    LD_addr_A(wMenuBorderTopCoord);
    LD_A(0x13);
    LD_addr_A(wMenuBorderRightCoord);
    LD_A(0x11);
    LD_addr_A(wMenuBorderBottomCoord);
    CALL(aPushWindow);
    FARCALL(aFunction11765d);
    FARCALL(aFunction17d3f6);
    FARCALL(aStubbed_Function106462);
    FARCALL(aFunction106464);
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    FARCALL(aFunction115d99);
    LD_C(0x0);
    FARCALL(aFunction115e18);
    LD_A(0x1);
    LD_addr_A(wc305);
    RET;

}

void Function11a113(void){
    CALL(aFunction11a63c);
    LD_C(0x1);
    FARCALL(aFunction115e18);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a6c8);
    CALL(aPlaceString);
    AND_A_A;
    RET;

}

void Function11a129(void){
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a131(void){
    LD_HL(wMobileInactivityTimerMinutes);
    DEC_hl;
    RET_NZ ;
    LD_A_addr(wBattleTowerRoomMenu2JumptableIndex);
    INC_A;
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);

    return Function11a13d();
}

void Function11a13d(void){
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a6d2);
    CALL(aPlaceString);
    AND_A_A;
    RET;

}

void Function11a14b(void){
    LD_HL(wcd85);
    LD_A_hl;
    CP_A(0xf3);
    IF_NZ goto asm_11a155;
    AND_A_A;
    RET;


asm_11a155:
    CALL(aFunction11a1d6);
    RET_C ;
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a6f1);
    CALL(aPlaceString);
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a16d(void){
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_11a179;
    DEC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    SCF;
    RET;


asm_11a179:
    CALL(aFunction11a63c);
    CALL(aFunction11a1e6);
    hlcoord(4, 2, wTilemap);
    LD_DE(wc346);
    CALL(aPlaceString);
    CALL(aFunction11a5f5);
    XOR_A_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a192(void){
    CALL(aFunction11a536);
    RET_C ;
    CALL(aPlayClickSFX);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_NZ goto asm_11a1b6;
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a6d2);
    CALL(aPlaceString);
    AND_A_A;
    RET;


asm_11a1b6:
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    LD_A_addr(wMobileInactivityTimerSeconds);
    LD_addr_A(wcf66);
    LD_addr_A(wcd80);
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a6d2);
    CALL(aPlaceString);
    SCF;
    RET;

}

void Function11a1d6(void){
    LD_A_addr(wcd85);
    CP_A(0x50);
    IF_NZ goto asm_11a1e4;
    LD_A(0xd3);
    CALL(aSetMobileErrorCode);
    SCF;
    RET;


asm_11a1e4:
    AND_A_A;
    RET;

}

void Function11a1e6(void){
    LD_HL(mString_11a706);
    LD_DE(wc346);
    CALL(aFunction11a1ff);
    LD_HL(wcd85);
    CALL(aFunction11a1ff);
    LD_HL(mString_11a70b);
    CALL(aFunction11a1ff);
    LD_A(0x50);
    LD_de_A;
    RET;

}

void Function11a1ff(void){

asm_11a1ff:
    LD_A_hli;
    CP_A(0x50);
    RET_Z ;
    LD_de_A;
    INC_DE;
    goto asm_11a1ff;

    return BattleTowerRoomMenu2_PlaceYesNoMenu();
}

void BattleTowerRoomMenu2_PlaceYesNoMenu(void){
    LD_HL(mMenuHeader_11a2de);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    CALL(aMenuBoxCoord2Tile);
    CALL(aApplyTilemap);
    hlcoord(16, 8, wTilemap);
    LD_DE(mString_11a2cf);
    CALL(aPlaceString);
    hlcoord(16, 10, wTilemap);
    LD_DE(mString_11a2d3);
    CALL(aPlaceString);
    hlcoord(15, 8, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void BattleTowerRoomMenu2_UpdateYesNoMenu(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto a_button;
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto b_button;
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto d_up;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto d_down;

asm_11a24c:
    CALL(aFunction11a9f0);
    SCF;
    RET;


d_up:
    XOR_A_A;
    LD_addr_A(wcd8a);
    LD_addr_A(wcd8b);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_11a24c;
    XOR_A_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    hlcoord(15, 8, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    hlcoord(15, 10, wTilemap);
    LD_A(0x7f);
    LD_hl_A;
    goto asm_11a24c;


d_down:
    XOR_A_A;
    LD_addr_A(wcd8a);
    LD_addr_A(wcd8b);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_NZ goto asm_11a24c;
    INC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    hlcoord(15, 8, wTilemap);
    LD_A(0x7f);
    LD_hl_A;
    hlcoord(15, 10, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    goto asm_11a24c;


a_button:
    XOR_A_A;
    LD_addr_A(wcd8a);
    LD_addr_A(wcd8b);
    CALL(aPlayClickSFX);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_NZ goto exit_no_carry;
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    LD_A_addr(wMobileInactivityTimerFrames);
    CP_A(0x0);
    IF_Z goto asm_11a2b4;
    LD_A_addr(wcd47);
    goto exit_carry;


asm_11a2b4:
    LD_A_addr(wcd33);


exit_carry:
    LD_addr_A(wcf66);
    LD_A(0xa);
    LD_addr_A(wMobileErrorCodeBuffer);
    SCF;
    RET;


b_button:
    CALL(aPlayClickSFX);


exit_no_carry:
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    AND_A_A;
    RET;

}

void String_11a2cf(void){
    //db ['"YES@"'];

    return String_11a2d3();
}

void String_11a2d3(void){
    //db ['"NO@"'];

    return MenuHeader_11a2d6();
}

void MenuHeader_11a2d6(void){
//  //  unreferenced
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['14', '6', 'SCREEN_WIDTH - 1', '10'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return MenuHeader_11a2de();
}

void MenuHeader_11a2de(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['14', '7', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return Function11a2e6();
}

void Function11a2e6(void){
    CALL(aFunction11a63c);
    LD_C(0x2);
    FARCALL(aFunction115e18);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a71e);
    CALL(aPlaceString);
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a302(void){
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_11a30e;
    DEC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    SCF;
    RET;


asm_11a30e:
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a72a);
    CALL(aPlaceString);
    hlcoord(9, 4, wTilemap);
    LD_DE(wcd68);
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    CALL(aPrintNum);
    hlcoord(14, 4, wTilemap);
    LD_DE(wcd67);
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    CALL(aPrintNum);
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a33a(void){
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_11a346;
    DEC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    SCF;
    RET;


asm_11a346:
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    FARCALL(aFunction115dc3);
    AND_A_A;
    RET;

}

void Function11a357(void){
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a743);
    CALL(aPlaceString);
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a36b(void){
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_11a377;
    DEC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    SCF;
    RET;


asm_11a377:
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a755);
    CALL(aPlaceString);
    CALL(aFunction11a5f5);
    XOR_A_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a38d(void){
    CALL(aFunction11a536);
    RET_C ;
    CALL(aPlayClickSFX);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_NZ goto asm_11a3b1;
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a6d2);
    CALL(aPlaceString);
    AND_A_A;
    RET;


asm_11a3b1:
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    LD_A_addr(wMobileInactivityTimerSeconds);
    LD_addr_A(wcf66);
    LD_addr_A(wcd80);
    SCF;
    RET;

}

void Function11a3c5(void){
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a762);
    CALL(aPlaceString);
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a3d9(void){
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_11a3e5;
    DEC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    SCF;
    RET;


asm_11a3e5:
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a779);
    CALL(aPlaceString);
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a3f9(void){
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_11a405;
    DEC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    SCF;
    RET;


asm_11a405:
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a755);
    CALL(aPlaceString);
    CALL(aFunction11a5f5);
    XOR_A_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a41b(void){
    CALL(aFunction11a536);
    RET_C ;
    CALL(aPlayClickSFX);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_NZ goto asm_11a43f;
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a6d2);
    CALL(aPlaceString);
    AND_A_A;
    RET;


asm_11a43f:
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    LD_A(0x1c);
    LD_addr_A(wcf66);
    LD_addr_A(wcd80);
    SCF;
    RET;

}

void Function11a452(void){
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a791);
    CALL(aPlaceString);
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a466(void){
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a7c1);
    CALL(aPlaceString);
    LD_A(0x80);
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a47a(void){
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_11a486;
    DEC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    SCF;
    RET;


asm_11a486:
    AND_A_A;
    RET;

}

void Function11a488(void){
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a7ac);
    CALL(aPlaceString);
    CALL(aFunction11a5f5);
    XOR_A_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a49e(void){
    CALL(aFunction11a536);
    RET_C ;
    CALL(aPlayClickSFX);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_NZ goto asm_11a4c7;
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a6d2);
    CALL(aPlaceString);
    LD_A(0x14);
    LD_addr_A(wcf66);
    AND_A_A;
    RET;


asm_11a4c7:
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    LD_A_addr(wMobileInactivityTimerFrames);
    LD_addr_A(wcf66);
    LD_addr_A(wcd80);
    SCF;
    RET;

}

void Function11a4db(void){
    CALL(aFunction11a63c);
    LD_DE(mString_11a6db);
    hlcoord(4, 2, wTilemap);
    CALL(aPlaceString);
    RET;

}

void Function11a4e8(void){
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a7d7);
    CALL(aPlaceString);
    CALL(aFunction11a5f5);
    XOR_A_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    JP(mBattleTowerRoomMenu2_IncrementJumptable);

}

void Function11a4fe(void){
    CALL(aFunction11a536);
    RET_C ;
    CALL(aPlayClickSFX);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_NZ goto asm_11a522;
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    CALL(aFunction11a63c);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a6d2);
    CALL(aPlaceString);
    AND_A_A;
    RET;


asm_11a522:
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    LD_A_addr(wMobileInactivityTimerSeconds);
    LD_addr_A(wcf66);
    LD_addr_A(wcd80);
    SCF;
    RET;

}

void Function11a536(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto asm_11a5a7;
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto asm_11a5a2;
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto asm_11a564;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto asm_11a583;

asm_11a54d:
    LD_A_addr(wBattleTowerRoomMenu2JumptableIndex);
    CP_A(0x4);
    IF_Z goto asm_11a562;
    CALL(aFunction11a9f0);
    IF_NZ goto asm_11a562;
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);


asm_11a562:
    SCF;
    RET;


asm_11a564:
    XOR_A_A;
    LD_addr_A(wcd8a);
    LD_addr_A(wcd8b);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_Z goto asm_11a54d;
    XOR_A_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    hlcoord(15, 7, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    hlcoord(15, 9, wTilemap);
    LD_A(0x7f);
    LD_hl_A;
    goto asm_11a54d;


asm_11a583:
    XOR_A_A;
    LD_addr_A(wcd8a);
    LD_addr_A(wcd8b);
    LD_A_addr(wMobileInactivityTimerMinutes);
    AND_A_A;
    IF_NZ goto asm_11a54d;
    INC_A;
    LD_addr_A(wMobileInactivityTimerMinutes);
    hlcoord(15, 7, wTilemap);
    LD_A(0x7f);
    LD_hl_A;
    hlcoord(15, 9, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    goto asm_11a54d;


asm_11a5a2:
    LD_A(0x1);
    LD_addr_A(wMobileInactivityTimerMinutes);


asm_11a5a7:
    XOR_A_A;
    LD_addr_A(wcd8a);
    LD_addr_A(wcd8b);
    AND_A_A;
    RET;

}

void BattleTowerRoomMenu2_IncrementJumptable(void){
    LD_A_addr(wBattleTowerRoomMenu2JumptableIndex);
    INC_A;
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    SCF;
    RET;

}

void Function11a5b9(void){
    XOR_A_A;
    LD_addr_A(wMenuBorderLeftCoord);
    LD_addr_A(wMenuBorderTopCoord);
    LD_A(0x13);
    LD_addr_A(wMenuBorderRightCoord);
    LD_A(0x5);
    LD_addr_A(wMenuBorderBottomCoord);
    CALL(aPushWindow);
    hlcoord(0, 0, wAttrmap);
    LD_B(0x6);
    LD_C(0x14);
    hlcoord(0, 0, wTilemap);
    LD_B(0x4);
    LD_C(0x12);
    CALL(aFunction3eea);
    FARCALL(aReloadMapPart);
    CALL(aUpdateSprites);
    LD_C(0x0);
    FARCALL(aFunction115e18);
    LD_A(0x1);
    LD_addr_A(wc305);
    RET;

}

void Function11a5f5(void){
    LD_A(0xe);
    LD_addr_A(wMenuBorderLeftCoord);
    LD_A(0x13);
    LD_addr_A(wMenuBorderRightCoord);
    LD_A(0x6);
    LD_addr_A(wMenuBorderTopCoord);
    LD_A(0xa);
    LD_addr_A(wMenuBorderBottomCoord);
    CALL(aPushWindow);
    hlcoord(14, 6, wAttrmap);
    LD_B(0x5);
    LD_C(0x6);
    hlcoord(14, 6, wTilemap);
    LD_B(0x3);
    LD_C(0x4);
    CALL(aFunction3eea);
    hlcoord(16, 7, wTilemap);
    LD_DE(mString_11a2cf);
    CALL(aPlaceString);
    hlcoord(16, 9, wTilemap);
    LD_DE(mString_11a2d3);
    CALL(aPlaceString);
    hlcoord(15, 7, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    FARCALL(aReloadMapPart);
    RET;

}

void Function11a63c(void){
    hlcoord(4, 1, wTilemap);
    LD_DE(mString_11a7f4);
    CALL(aPlaceString);
    hlcoord(4, 2, wTilemap);
    LD_DE(mString_11a7f4);
    CALL(aPlaceString);
    hlcoord(4, 3, wTilemap);
    LD_DE(mString_11a7f4);
    CALL(aPlaceString);
    hlcoord(4, 4, wTilemap);
    LD_DE(mString_11a7f4);
    CALL(aPlaceString);
    RET;

}

void String_11a661(void){
    //db ['"これから\u3000モバイルセンターに"'];
    //next ['"でんわ<WO>かけます@"']

    return String_11a679();
}

void String_11a679(void){
    //db ['"モバイルアダプタ<NO>じゅんびは"'];
    //next ['"できて\u3000いますか？@"']

    return String_11a692();
}

void String_11a692(void){
    //db ['"でんわ<WO>かけています"'];
    //next ['"しばらく\u3000おまちください@"']

    return String_11a6aa();
}

void String_11a6aa(void){
    //db ['"でんわをかけると\u3000つうわりょう"'];
    //next ['"せつぞくりょう<GA>かかります@"']

    return String_11a6c8();
}

void String_11a6c8(void){
    //db ['"せつぞく\u3000しました@"'];

    return String_11a6d2();
}

void String_11a6d2(void){
    //db ['"つうしん\u3000ちゅう@"'];

    return String_11a6db();
}

void String_11a6db(void){
    //db ['"つうしん\u3000ちゅう"'];
    //next ['"セレクト\u3000エーでちゅうし@"']

    return String_11a6f1();
}

void String_11a6f1(void){
    //db ['"この\u3000サービスには"'];
    //next ['"つうわりょう<NO>ほかに@"']

    return String_11a706();
}

void String_11a706(void){
    //db ['"おかね<GA>@"'];

    return String_11a70b();
}

void String_11a70b(void){
    //db ['"えん"'];
    //next ['"かかります\u3000よろしい\u3000ですか？@"']

    return String_11a71e();
}

void String_11a71e(void){
    //db ['"つうしん\u3000しゅうりょう@"'];

    return String_11a72a();
}

void String_11a72a(void){
    //db ['"つないだ\u3000じかん"'];
    //next ['"\u3000\u3000やく\u3000\u3000\u3000ふん\u3000\u3000\u3000びょう@"']

    return String_11a743();
}

void String_11a743(void){
    //db ['"もっていない\u3000データが"'];
    //next ['"あります！@"']

    return String_11a755();
}

void String_11a755(void){
    //db ['"データ<WO>よみこみますか？@"'];

    return String_11a762();
}

void String_11a762(void){
    //db ['"おなじ\u3000データ<WO>よみこんだ"'];
    //next ['"こと<GA>ありますが@"']

    return String_11a779();
}

void String_11a779(void){
    //db ['"そのデータ<WA>なくなっているか"'];
    //next ['"こわれて\u3000います@"']

    return String_11a791();
}

void String_11a791(void){
    //db ['"もっている\u3000データと"'];
    //next ['"おなじデータしか\u3000ありません！@"']

    return String_11a7ac();
}

void String_11a7ac(void){
    //db ['"データ<NO>よみこみを"'];
    //next ['"ちゅうし\u3000しますか？@"']

    return String_11a7c1();
}

void String_11a7c1(void){
    //db ['"あたらしい\u3000ニュースは"'];
    //next ['"ありません\u3000でした@"']

    return String_11a7d7();
}

void String_11a7d7(void){
    //db ['"あたらしいニュース<GA>あります"'];
    //next ['"ニュース<WO>よみこみますか？@"']

    return String_11a7f4();
}

void String_11a7f4(void){
    //db ['"\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000\u3000@"'];

    return MenuHeader_11a804();
}

void MenuHeader_11a804(void){
//  //  unreferenced
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '0', 'SCREEN_WIDTH - 1', '5'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return Function11a80c();
}

void Function11a80c(void){
    LD_DE(hDivisor);
    LD_BC(hDividend);
    LD_HL(mUnknown_11a89a);
    CALL(aFunction11a88c);
    LD_BC(hQuotient + 1);
    LD_HL(mUnknown_11a8ba);
    CALL(aFunction11a88c);
    LD_BC(hPrintNumBuffer + 2);
    LD_HL(mUnknown_11a8da);
    CALL(aFunction11a88c);
    XOR_A_A;
    LD_B_A;
    LDH_A_addr(hDivisor);
    AND_A(0xf);
    LD_E_A;
    LDH_A_addr(hPrintNumBuffer + 6);
    AND_A(0xf);
    CALL(aFunction11a884);
    LD_E_A;
    LDH_A_addr(hPrintNumBuffer + 8);
    AND_A(0xf);
    CALL(aFunction11a884);
    LD_addr_A(wcd62);
    LD_E_B;
    XOR_A_A;
    LD_B_A;
    LDH_A_addr(hDivisor);
    AND_A(0xf0);
    SWAP_A;
    CALL(aFunction11a884);
    LD_E_A;
    LDH_A_addr(hPrintNumBuffer + 6);
    AND_A(0xf0);
    SWAP_A;
    CALL(aFunction11a884);
    LD_E_A;
    LDH_A_addr(hPrintNumBuffer + 8);
    AND_A(0xf0);
    SWAP_A;
    CALL(aFunction11a884);
    LD_addr_A(wcd63);
    LD_E_B;
    XOR_A_A;
    LD_B_A;
    LDH_A_addr(hMathBuffer);
    AND_A(0xf);
    CALL(aFunction11a884);
    LD_E_A;
    LDH_A_addr(hPrintNumBuffer + 7);
    AND_A(0xf);
    CALL(aFunction11a884);
    LD_E_A;
    LDH_A_addr(hPrintNumBuffer + 9);
    AND_A(0xf);
    CALL(aFunction11a884);
    LD_addr_A(wcd64);
    RET;

}

void Function11a884(void){
    ADD_A_E;
    CP_A(0xa);
    RET_C ;
    SUB_A(0xa);
    INC_B;
    RET;

}

void Function11a88c(void){
    LD_A_bc;
    SLA_A;
    LD_C_A;
    XOR_A_A;
    LD_B_A;
    ADD_HL_BC;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    INC_DE;
    RET;

}

// void Unknown_11a89a(void){
//     for(int x = 0; x < 16; x++){
//     //bcd ['x 0b 100', 'x / 100']
//     }

//     return Unknown_11a8ba();
// }

// void Unknown_11a8ba(void){
//     for(int x = 0; x < 0, 16**2, 16; x++){
//     //bcd ['x 0b 100', 'x / 100']
//     }

//     return Unknown_11a8da();
// }

// void Unknown_11a8da(void){
//     for(int x = 0; x < 0, 16**3, 16**2; x++){
//     //bcd ['x 0b 100', 'x / 100']
//     }

//     return BattleTowerRoomMenu_WriteMessage();
// }

void BattleTowerRoomMenu_WriteMessage(void){
    //jumptable ['.Jumptable', 'wc31a']
    switch(wram->wc31a) {
    // Jumptable:
        //dw ['BattleTowerRoomMenu_WriteMessage_DoNothing'];
        case 0: return BattleTowerRoomMenu_WriteMessage_DoNothing();
        //dw ['Function11a90f'];
        case 1: return Function11a90f();
        //dw ['Function11a971'];
        case 2: return Function11a971();
    }
}

void Function11a90f(void){
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // CALL(aSpeechTextbox);
    SpeechTextbox_Conv2();
    // LD_A(0x50);
    // LD_HL(wc320);
    // LD_BC(0x008c);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wc320, 0x008c, 0x50);
    // LD_A_addr(wc31b);
    // LD_L_A;
    // LD_A_addr(wc31c);
    // LD_H_A;
    const uint8_t* hl = gMobileMessagePtr;
    // LD_DE(wc320);
    uint8_t* de = wram->wc320;

    uint8_t a;

asm_11a92c:
    // LD_A_hli;
    a = *(hl++);
    // CP_A(0x57);
    // IF_Z goto asm_11a94f;
    if(a == 0x57)
        goto asm_11a94f;
    // CP_A(0x0);
    // IF_Z goto asm_11a92c;
    // CP_A(0x50);
    // IF_Z goto asm_11a92c;
    if(a == 0x0 || a == 0x50)
        goto asm_11a92c;
    // CP_A(0x1);
    // IF_Z goto asm_11a941;
    if(a != 0x1) {
        // LD_de_A;
        // INC_DE;
        *(de++) = a;
        goto asm_11a92c;
    }

// asm_11a941:
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    const uint8_t* bc = GBToRAMAddr(hl[0] | (hl[1] << 8));

    do {
    // asm_11a945:
        // LD_A_bc;
        uint8_t n = *bc;
        // INC_BC;
        bc++;
        // CP_A(0x50);
        // IF_Z goto asm_11a92c;
        if(n == 0x50)
            goto asm_11a92c;
        // LD_de_A;
        *de = n;
        // INC_DE;
        de++;
        // goto asm_11a945;
    } while(1);


asm_11a94f:
    // XOR_A_A;
    // LD_addr_A(wc31f);
    wram->wc31f = 0;
    // LD_A(LOW(wc320));
    // LD_addr_A(wc31b);
    // LD_A(HIGH(wc320));
    // LD_addr_A(wc31c);
    gMobileMessagePtr = wram->wc320;
    // hlcoord(1, 14, wTilemap);
    // LD_A_L;
    // LD_addr_A(wc31d);
    // LD_A_H;
    // LD_addr_A(wc31e);
    gMobileMessageDestPtr = coord(1, 14, wram->wTilemap);
    // LD_HL(wc31a);
    // INC_hl;
    wram->wc31a++;
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);

    return BattleTowerRoomMenu_WriteMessage_DoNothing();
}

void BattleTowerRoomMenu_WriteMessage_DoNothing(void){
    // RET;
}

void Function11a971(void){
    // LD_HL(wc31f);
    // LDH_A_addr(hJoyDown);
    // AND_A_A;
    // IF_NZ goto asm_11a97f;
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto asm_11a97f;
    if(hram->hJoyDown != 0 || wram->wc31f == 0) {
    // asm_11a97f:
        // LD_A_addr(wOptions);
        // AND_A(0x7);
        // LD_hl_A;
        wram->wOptions &= 0x7;
        // LD_HL(wcd8d);
        uint8_t* hl = wram->wcd8d;
        // LD_A_addr(wc31b);
        // LD_E_A;
        // LD_A_addr(wc31c);
        // LD_D_A;
        // LD_A_de;
        // INC_DE;
        *(hl++) = *(gMobileMessagePtr++);
        // LD_hli_A;
        // LD_A_E;
        // LD_addr_A(wc31b);
        // LD_A_D;
        // LD_addr_A(wc31c);
        // LD_A(0x50);
        // LD_hl_A;
        *hl = 0x50;
        // LD_A_addr(wc31d);
        // LD_L_A;
        // LD_A_addr(wc31e);
        // LD_H_A;
        // LD_DE(wcd8d);
        struct TextPrintState st = {.de = wram->wcd8d, .hl = gMobileMessageDestPtr};
        // CALL(aPlaceString);
        PlaceString_Conv(&st, st.hl);
        // LD_A_C;
        // LD_addr_A(wc31d);
        // LD_A_B;
        // LD_addr_A(wc31e);
        gMobileMessageDestPtr = st.bc;
        // LD_A_addr(wcd8d);
        // CP_A(0x50);
        // IF_NZ goto asm_11a9bf;
        if(wram->wcd8d[0] == 0x50) {
            // XOR_A_A;
            // LD_addr_A(wc31a);
            wram->wc31a = 0;
        }

    // asm_11a9bf:
        // RET;
        return;
    }
    // DEC_hl;
    --wram->wc31f;
    // RET;
    return;
}

void BattleTowerRoomMenu_SetMessage(uint8_t* hl){
    // LD_A_L;
    // LD_addr_A(wc31b);
    // LD_A_H;
    // LD_addr_A(wc31c);
    gMobileMessagePtr = hl;
    // LD_A(0x1);
    // LD_addr_A(wc31a);
    wram->wc31a = 0x1;
    // RET;
}

void Function11a9ce(void){
    CALL(aClearBGPalettes);
    CALL(aReloadTilesetAndPalettes);
    CALL(aCall_ExitMenu);
    FARCALL(aStubbed_Function106462);
    FARCALL(aFunction106464);
    CALL(aGSReloadPalettes);
    FARCALL(aFinishExitMenu);
    CALL(aUpdateSprites);
    RET;

}

void Function11a9f0(void){
    LD_A(0x1);
    AND_A_A;
    RET;

}

void Function11a9f4(void){
//  //  unreferenced
    LD_A_addr(wcd8a);
    LD_L_A;
    LD_A_addr(wcd8b);
    LD_H_A;
    INC_HL;
    LD_A_L;
    LD_addr_A(wcd8a);
    LD_A_H;
    LD_addr_A(wcd8b);
    LD_DE(0xd5d0);
    ADD_HL_DE;
    BIT_H(7);
    RET_NZ ;
    LD_A(0xd6);
    CALL(aSetMobileErrorCode);
    AND_A_A;
    RET;

}

void Text_SaveFileWillBeSent(void){
    //text ['"SAVE FILE will be"']
    //line ['"sent."']
    //done ['?']

    return Text_SentSaveFileReadingNews();
}

void Text_SentSaveFileReadingNews(void){
    //text ['"Sent SAVE FILE."']
    //line ['"Reading NEWS…"']
    //done ['?']

    return Text_ReadingNews();
}

void Text_ReadingNews(void){
    //text ['"Reading NEWS…"']
    //done ['?']

    return Text_ReceivedNews();
}

void Text_ReceivedNews(void){
    //text ['"Received NEWS!"']
    //done ['?']

    return Text_QuitReadingNews();
}

void Text_QuitReadingNews(void){
    //text ['"Quit reading NEWS?"']
    //done ['?']

    return Text_CanceledSendingSaveFile();
}

void Text_CanceledSendingSaveFile(void){
//  //  unreferenced
    //text ['"Canceled sending"']
    //line ['"SAVE FILE."']
    //done ['?']

    return Text_ReceivedOddEgg();
}

void Text_ReceivedOddEgg(void){
//  //  unreferenced
    //text ['"ODD EGG"']
    //line ['"was received!"']
    //done ['?']

    return Text_RegisteringRecord();
}

void Text_RegisteringRecord(void){
    //text ['"Registering your"']
    //line ['"record…"']
    //done ['?']

    return Text_BattleRoomVisitLimit();
}

void Text_BattleRoomVisitLimit(void){
//  //  unreferenced
    //text ['"One visit per day"']
    //line ['"per BATTLE ROOM!"']
    //done ['?']

    return Text_PartyMonTopsThisLevel();
}

void Text_PartyMonTopsThisLevel(void){
    //text ['"A party #MON"']
    //line ['"tops this level."']
    //done ['?']

    return Text_UberRestriction();
}

void Text_UberRestriction(void){
    //text_ram ['wcd49']
    //text ['" may go"']
    //line ['"only to BATTLE"']

    //para ['"ROOMS that are"']
    //line ['"Lv.70 or higher."']
    //done ['?']

    return Text_CancelBattleRoomChallenge();
}

void Text_CancelBattleRoomChallenge(void){
    //text ['"Cancel your BATTLE"']
    //line ['"ROOM challenge?"']
    //done ['?']

    return Text_ExitGymLeaderHonorRoll();
}

void Text_ExitGymLeaderHonorRoll(void){
    //text ['"Exit GYM LEADER"']
    //line ['"HONOR ROLL?"']
    //done ['?']

    return Text_LinkingWithCenter();
}

void Text_LinkingWithCenter(void){
//  //  unreferenced
    //text ['"Linking with the"']
    //line ['"CENTER…"']
    //done ['?']

    return Text_WhatLevelDoYouWantToChallenge();
}

void Text_WhatLevelDoYouWantToChallenge(void){
    //text ['"What level do you"']
    //line ['"want to challenge?"']
    //done ['?']

    return Text_CheckBattleRoomListByMaxLevel();
}

void Text_CheckBattleRoomListByMaxLevel(void){
    //text ['"Check BATTLE ROOM"']
    //line ['"list by max level?"']
    //done ['?']

    return Text_EnterWhichBattleRoom();
}

void Text_EnterWhichBattleRoom(void){
//  //  unreferenced
    //text ['"Enter which"']
    //line ['"BATTLE ROOM?"']
    //done ['?']

    return Text_WhichBattleRoom();
}

void Text_WhichBattleRoom(void){
//  //  unreferenced
    //text ['"Which BATTLE ROOM?"']
    //done ['?']

    return Text_ThisBattleRoomPleaseWait();
}

void Text_ThisBattleRoomPleaseWait(void){
//  //  unreferenced
    //text_ram ['wStringBuffer3']
    //text ['"\'s ROOM"']
    //line ['"@"']
    //text_ram ['wStringBuffer4']
    //text ['"?"']
    //cont ['"Please wait…"']
    //done ['?']

    return Function11ac3e();
}

void Function11ac3e(void){
    CALL(aSpeechTextbox);
    CALL(aFadeToMenu);
    CALLFAR(aClearSpriteAnims2);
    CALL(aFunction11ac51);
    CALL(aCloseSubmenu);
    RET;

}

void Function11ac51(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    SET_hl(4);
    LD_A_addr(wVramState);
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wVramState);
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    LD_addr_A(wcd49);
    LD_addr_A(wcd4a);
    LD_addr_A(wcd4c);
    LD_addr_A(wcd4d);
    LD_addr_A(wcd4e);
    CALL(aFunction11ad1b);
    CALL(aDelayFrame);

loop:
    CALL(aJoyTextDelay);
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto asm_11aca8;
    CALL(aFunction11b314);
    CALL(aFunction11acb7);
    CALL(aFunction11ad6e);
    LD_A(30 * SPRITEOAMSTRUCT_LENGTH);
    LD_addr_A(wCurSpriteOAMAddr);
    FARCALL(aDoNextFrameForAllSprites);
    FARCALL(aReloadMapPart);
    goto loop;


asm_11aca8:
    CALL(aClearSprites);
    POP_AF;
    LDH_addr_A(hInMenu);
    POP_AF;
    LD_addr_A(wVramState);
    POP_AF;
    LD_addr_A(wOptions);
    RET;

}

void Function11acb7(void){
    LD_HL(mTilemapPack_11ba44);
    LD_A_addr(wcd49);
    LD_C_A;
    LD_B(0);
    SLA_C;
    RL_B;
    SLA_C;
    RL_B;
    SLA_C;
    RL_B;
    ADD_HL_BC;
    decoord(6, 6, wTilemap);
    LD_A_hli;
    LD_de_A;
    decoord(0, 7, wTilemap);
    LD_BC(7);
    CALL(aCopyBytes);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    LD_A_hl;
    CP_A(0xff);
    IF_NZ goto get_the_other;
    XOR_A_A;
    LD_addr_A(wcd49);

get_the_other:
    LD_HL(mTilemapPack_11bb7d);
    LD_A_addr(wcd4a);
    LD_C_A;
    LD_B(0);
    SLA_C;
    RL_B;
    SLA_C;
    RL_B;
    SLA_C;
    RL_B;
    ADD_HL_BC;
    decoord(3, 9, wTilemap);
    LD_BC(7);
    CALL(aCopyBytes);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    INC_HL;
    LD_A_hl;
    CP_A(0xff);
    RET_NZ ;
    XOR_A_A;
    LD_addr_A(wcd4a);
    RET;

}

void Function11ad1b(void){
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    CALL(aClearTilemap);
    FARCALL(aFunction17c000);
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wcd82);
    DEC_A;
    LDH_addr_A(hObjectStructIndex);
    LD_A(0x10);
    LD_addr_A(wCurIconTile);
    LD_HL(mLoadMenuMonIcon);
    LD_A(BANK(aLoadMenuMonIcon));
    LD_E(MONICON_MOBILE1);
    RST(aFarCall);
    LD_HL(mLoadMenuMonIcon);
    LD_A(BANK(aLoadMenuMonIcon));
    LD_E(MONICON_MOBILE2);
    RST(aFarCall);
    LD_HL(wPokedexOrder);
    LD_BC(0x0115);
    XOR_A_A;
    CALL(aByteFill);
    XOR_A_A;
    LD_addr_A(wJumptableIndex);
    LD_addr_A(wcf64);
    LD_addr_A(wcf65);
    LD_addr_A(wcf66);
    LD_addr_A(wcd30);
    LD_A(DEXMODE_ABC);
    LD_addr_A(wCurDexMode);
    FARCALL(aPokedex_OrderMonsByMode);
    RET;

}

void Function11ad6e(void){
    LD_A_addr(wJumptableIndex);
    LD_HL(mJumptable_11ad78);
    CALL(aFunction11b239);
    JP_hl;

}

void Jumptable_11ad78(void){
    //dw ['Function11b082'];
    //dw ['Function11b0ff'];
    //dw ['Function11ad95'];
    //dw ['Function11adc4'];
    //dw ['Function11ae4e'];
    //dw ['Function11ae98'];
    //dw ['Function11ad8f'];
    //dw ['Function11af04'];
    //dw ['Function11af4e'];

    return Function11ad8a();
}

void Function11ad8a(void){
    LD_HL(wJumptableIndex);
    INC_hl;
    RET;

}

void Function11ad8f(void){
    LD_HL(wJumptableIndex);
    SET_hl(7);
    RET;

}

void Function11ad95(void){
    LD_HL(mMenuHeader_11ae38);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    hlcoord(12, 12, wTilemap);
    LD_DE(mString_11ae40);
    CALL(aPlaceString);
    hlcoord(10, 10, wAttrmap);
    LD_BC((8 << 8) | 8);
    CALL(aFunction11afd6);
    FARCALL(aReloadMapPart);
    CALL(aFunction11ad8a);
    LD_A(0x1);
    LD_addr_A(wMenuCursorY);
    LD_HL(mUnknown_11afcc);
    CALL(aFunction11afb7);

    return Function11adc4();
}

void Function11adc4(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto asm_11ade6;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto asm_11aded;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto asm_11ae06;
    LD_A_hl;
    AND_A(B_BUTTON);
    RET_Z ;
    CALL(aPlayClickSFX);
    XOR_A_A;
    LD_addr_A(wJumptableIndex);
    goto asm_11ae2e;


asm_11ade6:
    LD_A_addr(wMenuCursorY);
    DEC_A;
    RET_Z ;
    goto asm_11adf4;


asm_11aded:
    LD_A_addr(wMenuCursorY);
    INC_A;
    CP_A(0x4);
    RET_Z ;


asm_11adf4:
    PUSH_AF;
    LD_HL(mUnknown_11afcc);
    CALL(aFunction11afbb);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    LD_HL(mUnknown_11afcc);
    CALL(aFunction11afb7);
    RET;


asm_11ae06:
    CALL(aPlayClickSFX);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_HL(wcd30);
    LD_hl_A;
    AND_A_A;
    IF_Z goto asm_11ae28;
    hlcoord(2, 14, wTilemap);
    LD_A_addr(wMenuCursorY);
    CP_A(0x2);
    IF_Z goto asm_11ae23;
    CALL(aFunction11b272);
    goto asm_11ae2b;


asm_11ae23:
    CALL(aFunction11b267);
    goto asm_11ae2b;


asm_11ae28:
    LD_A(0x3);
    LD_hl_A;


asm_11ae2b:
    CALL(aFunction11ad8a);


asm_11ae2e:
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    RET;

}

void MenuHeader_11ae38(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['10', '10', '17', 'SCREEN_HEIGHT - 1'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return String_11ae40();
}

void String_11ae40(void){
    //db ['"どちらでも"'];
    //next ['"♂オス"']
    //next ['"♀メス"']
    //db ['"@"'];

    return Function11ae4e();
}

void Function11ae4e(void){
    LD_HL(mMenuHeader_11afe8);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    hlcoord(10, 14, wTilemap);
    LD_DE(mString_11aff0);
    CALL(aPlaceString);
    LD_HL(mMenuHeader_11b013);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    hlcoord(16, 8, wTilemap);
    LD_DE(mString_11b01b);
    CALL(aPlaceString);
    hlcoord(14, 7, wAttrmap);
    LD_BC((5 << 8) | 6);
    CALL(aFunction11afd6);
    hlcoord(9, 12, wAttrmap);
    LD_BC((6 << 8) | 11);
    CALL(aFunction11afd6);
    FARCALL(aReloadMapPart);
    CALL(aFunction11ad8a);
    LD_A(0x1);
    LD_addr_A(wMenuCursorY);
    LD_HL(mUnknown_11afd2);
    CALL(aFunction11afb7);

    return Function11ae98();
}

void Function11ae98(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto asm_11aec1;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto asm_11aec8;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto asm_11aee1;
    LD_A_hl;
    AND_A(B_BUTTON);
    RET_Z ;
    CALL(aPlayClickSFX);

asm_11aeb4:
    hlcoord(2, 14, wTilemap);
    LD_A(0x7f);
    LD_hl_A;
    LD_A(0x1);
    LD_addr_A(wJumptableIndex);
    goto asm_11aef7;


asm_11aec1:
    LD_A_addr(wMenuCursorY);
    DEC_A;
    RET_Z ;
    goto asm_11aecf;


asm_11aec8:
    LD_A_addr(wMenuCursorY);
    INC_A;
    CP_A(0x3);
    RET_Z ;


asm_11aecf:
    PUSH_AF;
    LD_HL(mUnknown_11afd2);
    CALL(aFunction11afbb);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    LD_HL(mUnknown_11afd2);
    CALL(aFunction11afb7);
    RET;


asm_11aee1:
    CALL(aPlayClickSFX);
    LD_A_addr(wMenuCursorY);
    CP_A(0x2);
    IF_Z goto asm_11aeb4;
    LD_A_addr(wcd4b);
    LD_addr_A(wScriptVar);
    CALL(aFunction11b022);
    CALL(aFunction11ad8a);


asm_11aef7:
    CALL(aExitMenu);
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    RET;

}

void Function11af04(void){
    LD_HL(mMenuHeader_11afe8);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    hlcoord(10, 14, wTilemap);
    LD_DE(mString_11b003);
    CALL(aPlaceString);
    LD_HL(mMenuHeader_11b013);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    hlcoord(16, 8, wTilemap);
    LD_DE(mString_11b01b);
    CALL(aPlaceString);
    hlcoord(14, 7, wAttrmap);
    LD_BC((5 << 8) | 6);
    CALL(aFunction11afd6);
    hlcoord(9, 12, wAttrmap);
    LD_BC((6 << 8) | 11);
    CALL(aFunction11afd6);
    FARCALL(aReloadMapPart);
    CALL(aFunction11ad8a);
    LD_A(0x2);
    LD_addr_A(wMenuCursorY);
    LD_HL(mUnknown_11afd2);
    CALL(aFunction11afb7);

    return Function11af4e();
}

void Function11af4e(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto asm_11af77;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto asm_11af7e;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto asm_11af97;
    LD_A_hl;
    AND_A(B_BUTTON);
    RET_Z ;
    CALL(aPlayClickSFX);

asm_11af6a:
    hlcoord(2, 14, wTilemap);
    LD_A(0x7f);
    LD_hl_A;
    LD_A(0x1);
    LD_addr_A(wJumptableIndex);
    goto asm_11afaa;


asm_11af77:
    LD_A_addr(wMenuCursorY);
    DEC_A;
    RET_Z ;
    goto asm_11af85;


asm_11af7e:
    LD_A_addr(wMenuCursorY);
    INC_A;
    CP_A(0x3);
    RET_Z ;


asm_11af85:
    PUSH_AF;
    LD_HL(mUnknown_11afd2);
    CALL(aFunction11afbb);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    LD_HL(mUnknown_11afd2);
    CALL(aFunction11afb7);
    RET;


asm_11af97:
    CALL(aPlayClickSFX);
    LD_A_addr(wMenuCursorY);
    CP_A(0x2);
    IF_Z goto asm_11af6a;
    LD_A(0x6);
    LD_addr_A(wJumptableIndex);
    XOR_A_A;
    LD_addr_A(wScriptVar);


asm_11afaa:
    CALL(aExitMenu);
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    RET;

}

void Function11afb7(void){
    LD_E(0xed);
    JR(masm_11afbd);

}

void Function11afbb(void){
    LD_E(0x7f);

    return asm_11afbd();
}

void asm_11afbd(void){
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_E;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    LD_de_A;
    RET;

}

void Unknown_11afcc(void){
    //dwcoord ['11', '12'];
    //dwcoord ['11', '14'];
    //dwcoord ['11', '16'];

    return Unknown_11afd2();
}

void Unknown_11afd2(void){
    //dwcoord ['15', '8'];
    //dwcoord ['15', '10'];

    return Function11afd6();
}

void Function11afd6(void){
    LD_DE(SCREEN_WIDTH);
    LD_A(0x3);

row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    ADD_HL_DE;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    RET;

}

void MenuHeader_11afe8(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['9', '12', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return String_11aff0();
}

void String_11aff0(void){
    //db ['"この\u3000じょうけんで"'];
    //next ['"よろしいですか?@"']

    return String_11b003();
}

void String_11b003(void){
    //db ['"こうかんを"'];
    //next ['"ちゅうししますか？@"']

    return MenuHeader_11b013();
}

void MenuHeader_11b013(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['14', '7', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['NULL'];
    //db ['1'];  // default option

    return String_11b01b();
}

void String_11b01b(void){
    //db ['"はい"'];
    //next ['"いいえ@"']

    return Function11b022();
}

void Function11b022(void){
    LD_A_addr(wcd2e);
    AND_A_A;
    IF_Z goto asm_11b02e;
    LD_HL(wStringBuffer3);
    CALL(aFunction11b03d);


asm_11b02e:
    LD_A_addr(wcd30);
    AND_A_A;
    RET_Z ;
    CP_A(0x3);
    RET_Z ;
    LD_HL(wStringBuffer4);
    CALL(aFunction11b03d);
    RET;

}

void Function11b03d(void){
    PUSH_HL;
    PUSH_AF;
    LD_C(0x1);

loop:
    LD_A_hli;
    CP_A(0xef);
    IF_Z goto gender;
    CP_A(0xf5);
    IF_Z goto gender;
    CP_A(0x50);
    IF_Z goto done;
    INC_C;
    goto loop;


gender:
    DEC_HL;
    LD_A(0x50);
    LD_hli_A;


done:
    DEC_HL;
    PUSH_HL;
    LD_E(4);
    LD_D(0);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    POP_HL;

loop2:
    LD_A_hld;
    LD_de_A;
    DEC_DE;
    DEC_C;
    IF_NZ goto loop2;
    POP_AF;
    POP_DE;
    CP_A(0x1);
    IF_NZ goto female;
    LD_HL(mFunction11b03d_MaleString);
    goto got_string;


female:
    LD_HL(mFunction11b03d_FemaleString);


got_string:
    LD_BC(4);  // string length
    CALL(aCopyBytes);
    RET;


MaleString:
// db "オスの　"

FemaleString:
// db "メスの　"

    return Function11b082();
}

void Function11b082(void){
    CALL(aFunction11b242);
    LD_A(0x7);
    LD_addr_A(wc7d3);
    CALL(aFunction11b099);
    CALL(aFunction11b295);
    CALL(aFunction11b275);
    CALL(aSetPalettes);
    JP(mFunction11ad8a);

}

void Function11b099(void){
    LD_C(0x6);
    hlcoord(11, 1, wTilemap);
    LD_A_addr(wc7d3);
    ADD_A_A;
    LD_B_A;
    XOR_A_A;
    CALL(aFunction11b236);
    LD_A_addr(wc7d0);
    LD_E_A;
    LD_D(0);
    LD_HL(wPokedexOrder);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    hlcoord(11, 2, wTilemap);
    LD_A_addr(wc7d3);

loop:
    PUSH_AF;
    LD_A_de;
    LD_addr_A(wTempSpecies);
    PUSH_DE;
    PUSH_HL;
    CALL(aFunction11b099_PlaceMonNameOrPlaceholderString);
    POP_HL;
    LD_DE(2 * SCREEN_WIDTH);
    ADD_HL_DE;
    POP_DE;
    INC_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;
    RET;


PlaceMonNameOrPlaceholderString:
    AND_A_A;
    RET_Z ;

    CALL(aFunction11b099_CheckSeenFlag);
    RET_C ;

    CALL(aFunction11b099_SetCaughtFlag);
    PUSH_HL;
    CALL(aGetPokemonName);
    POP_HL;
    CALL(aPlaceString);
    RET;


SetCaughtFlag:
    CALL(aCheckCaughtMemMon);
    IF_NZ goto okay;
    INC_HL;
    RET;


okay:
    LD_A(0x1);
    LD_hli_A;
    RET;


CheckSeenFlag:
    CALL(aCheckSeenMemMon);
    RET_NZ ;

    INC_HL;
    LD_DE(mFunction11b099_EmptySlot);
    CALL(aPlaceString);
    SCF;
    RET;


EmptySlot:
    //db ['"ーーーーー@"'];

    return Function11b0ff();
}

void Function11b0ff(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(B_BUTTON);
    IF_NZ goto asm_11b141;
    LD_A_hl;
    AND_A(A_BUTTON);
    IF_NZ goto asm_11b131;
    CALL(aFunction11b175);
    IF_NC goto asm_11b125;
    LD_A_addr(wcd4c);
    INC_A;
    AND_A(0x3);
    LD_addr_A(wcd4c);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aFunction11b099);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    RET;


asm_11b125:
    LD_A_addr(wcd4c);
    AND_A_A;
    RET_Z ;
    INC_A;
    AND_A(0x3);
    LD_addr_A(wcd4c);
    RET;


asm_11b131:
    CALL(aFunction11b20b);
    CALL(aCheckSeenMemMon);
    IF_Z goto asm_11b13d;
    LD_A(0x1);
    goto asm_11b148;


asm_11b13d:
    LD_A(0x2);
    goto asm_11b148;


asm_11b141:
    LD_HL(wJumptableIndex);
    LD_A(0x7);
    LD_hl_A;
    RET;


asm_11b148:
    CALL(aPlayClickSFX);
    LD_addr_A(wcd4b);
    AND_A_A;
    IF_Z goto asm_11b16c;
    LD_A_addr(wcf65);
    CP_A(0x0);
    IF_Z goto asm_11b163;
    CP_A(0xfe);
    IF_Z goto asm_11b167;
    CP_A(0xff);
    IF_Z goto asm_11b16b;
    JP(mFunction11ad8a);


asm_11b163:
    LD_A(0x1);
    goto asm_11b16c;


asm_11b167:
    LD_A(0x2);
    goto asm_11b16c;


asm_11b16b:
    XOR_A_A;


asm_11b16c:
    LD_addr_A(wcd30);
    LD_A(0x4);
    LD_addr_A(wJumptableIndex);
    RET;

}

void Function11b175(void){
    LD_A_addr(wc7d3);
    LD_D_A;
    LD_A_addr(wc7d2);
    LD_E_A;
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto asm_11b19a;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto asm_11b1ae;
    LD_A_D;
    CP_A_E;
    IF_NC goto asm_11b1ed;
    LD_A_hl;
    AND_A(D_LEFT);
    IF_NZ goto asm_11b1c6;
    LD_A_hl;
    AND_A(D_RIGHT);
    IF_NZ goto asm_11b1d8;
    goto asm_11b1ed;


asm_11b19a:
    LD_HL(wc7d1);
    LD_A_hl;
    AND_A_A;
    IF_Z goto asm_11b1a4;
    DEC_hl;
    goto asm_11b1ef;


asm_11b1a4:
    LD_HL(wc7d0);
    LD_A_hl;
    AND_A_A;
    IF_Z goto asm_11b1ed;
    DEC_hl;
    goto asm_11b1ef;


asm_11b1ae:
    LD_HL(wc7d1);
    LD_A_hl;
    INC_A;
    CP_A_E;
    IF_NC goto asm_11b1ed;
    CP_A_D;
    IF_NC goto asm_11b1bc;
    INC_hl;
    goto asm_11b1ef;


asm_11b1bc:
    LD_HL(wc7d0);
    ADD_A_hl;
    CP_A_E;
    IF_NC goto asm_11b1ed;
    INC_hl;
    goto asm_11b1ef;


asm_11b1c6:
    LD_HL(wc7d0);
    LD_A_hl;
    AND_A_A;
    IF_Z goto asm_11b1ed;
    CP_A_D;
    IF_NC goto asm_11b1d4;
    XOR_A_A;
    LD_hl_A;
    goto asm_11b1ef;


asm_11b1d4:
    SUB_A_D;
    LD_hl_A;
    goto asm_11b1ef;


asm_11b1d8:
    LD_HL(wc7d0);
    LD_A_D;
    ADD_A_A;
    ADD_A_hl;
    IF_C goto asm_11b1e3;
    CP_A_E;
    IF_C goto asm_11b1e8;


asm_11b1e3:
    LD_A_E;
    SUB_A_D;
    LD_hl_A;
    goto asm_11b1ef;


asm_11b1e8:
    LD_A_hl;
    ADD_A_D;
    LD_hl_A;
    goto asm_11b1ef;


asm_11b1ed:
    AND_A_A;
    RET;


asm_11b1ef:
    CALL(aFunction11b295);
    CALL(aFunction11b275);
    SCF;
    RET;

}

void FillScreenWithTile32(void){
//  //  unreferenced
    hlcoord(0, 0, wTilemap);
    LD_A(0x32);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    RET;

}

void CopyDataUntilFF(void){
//  //  unreferenced

loop:
    LD_A_de;
    CP_A(0xff);
    RET_Z ;
    INC_DE;
    LD_hli_A;
    goto loop;

    return Function11b20b();
}

void Function11b20b(void){
    LD_A_addr(wc7d1);
    LD_HL(wc7d0);
    ADD_A_hl;
    LD_E_A;
    LD_D(0);
    LD_HL(0xc6d0);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wTempSpecies);
    RET;

}

void CheckCaughtMemMon(void){
    PUSH_DE;
    PUSH_HL;
    LD_A_addr(wTempSpecies);
    DEC_A;
    CALL(aCheckCaughtMon);
    POP_HL;
    POP_DE;
    RET;

}

void CheckSeenMemMon(void){
    PUSH_DE;
    PUSH_HL;
    LD_A_addr(wTempSpecies);
    DEC_A;
    CALL(aCheckSeenMon);
    POP_HL;
    POP_DE;
    RET;

}

void Function11b236(void){
    JP(mFillBoxWithByte);

}

void Function11b239(void){
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;

}

void Function11b242(void){
    hlcoord(3, 4, wTilemap);
    LD_DE(wStringBuffer3);
    CALL(aPlaceString);
    XOR_A_A;
    LD_addr_A(wMonType);
    FARCALL(aGetGender);
    hlcoord(1, 4, wTilemap);
    LD_A_addr(wCurPartySpecies);
    LD_BC(wcd2f);
    LD_bc_A;
    DEC_BC;
    JR_C (masm_11b26a);
    JR_Z (masm_11b26f);
    LD_A(0x1);
    LD_bc_A;

    return Function11b267();
}

void Function11b267(void){
    LD_hl(0xef);
    RET;

}

void asm_11b26a(void){
    XOR_A_A;
    LD_bc_A;
    LD_hl(0x7f);
    RET;

}

void asm_11b26f(void){
    LD_A(0x2);
    LD_bc_A;

    return Function11b272();
}

void Function11b272(void){
    LD_hl(0xf5);
    RET;

}

void Function11b275(void){
    CALL(aFunction11b279);
    RET;

}

void Function11b279(void){
    LD_A_addr(wTempSpecies);
    LD_addr_A(wCurSpecies);
    CALL(aCheckSeenMemMon);
    IF_Z goto asm_11b28f;
    CALL(aGetBaseData);
    LD_A_addr(wBaseGender);
    LD_addr_A(wcf65);
    goto asm_11b294;


asm_11b28f:
    LD_A(0xff);
    LD_addr_A(wcf65);


asm_11b294:
    RET;

}

void Function11b295(void){
    hlcoord(4, 13, wTilemap);
    LD_DE(mString_11b308);
    CALL(aPlaceString);
    hlcoord(4, 14, wTilemap);
    LD_DE(mString_11b308);
    CALL(aPlaceString);
    CALL(aFunction11b20b);
    CALL(aCheckSeenMemMon);
    IF_Z goto asm_11b2d1;
    LD_A_addr(0xc608);
    LD_C_A;
    LD_A_addr(0xc608 + 1);
    LD_B_A;
    LD_HL(0x0007);
    ADD_HL_BC;
    XOR_A_A;
    LD_hl_A;
    LD_HL(0x0003);
    ADD_HL_BC;
    LD_E_hl;
    FARCALL(aFlyFunction_GetMonIcon);
    hlcoord(4, 14, wTilemap);
    PUSH_HL;
    CALL(aGetPokemonName);
    goto asm_11b2e7;


asm_11b2d1:
    LD_A_addr(0xc608);
    LD_C_A;
    LD_A_addr(0xc608 + 1);
    LD_B_A;
    LD_HL(0x0007);
    ADD_HL_BC;
    LD_A(0x50);
    LD_hl_A;
    hlcoord(4, 13, wTilemap);
    PUSH_HL;
    LD_DE(mString_11b30e);


asm_11b2e7:
    LD_A(0x6);
    LD_BC(wStringBuffer4);

asm_11b2ec:
    PUSH_AF;
    LD_A_de;
    LD_bc_A;
    INC_DE;
    INC_BC;
    POP_AF;
    DEC_A;
    AND_A_A;
    IF_NZ goto asm_11b2ec;
    POP_HL;
    LD_DE(wStringBuffer4);
    CALL(aPlaceString);
    RET;

}

void String_11b2fe(void){
//  //  unreferenced
    //db ['"あげる#@"'];

    return String_11b303();
}

void String_11b303(void){
//  //  unreferenced
    //db ['"ほしい#@"'];

    return String_11b308();
}

void String_11b308(void){
    //db ['"\u3000\u3000\u3000\u3000\u3000@"'];

    return String_11b30e();
}

void String_11b30e(void){
    //db ['"みはっけん@"'];

    return Function11b314();
}

void Function11b314(void){
    CALL(aFunction11b31b);
    CALL(aFunction11b3d9);
    RET;

}

void Function11b31b(void){
    LD_HL(mFunction11b31b_Coords);
    LD_A_addr(wJumptableIndex);
    CP_A(2);
    IF_C goto tilemap_1;
    LD_A_addr(wc7d1);
    CP_A(4);
    IF_NC goto tilemap_3;
    CP_A(3);
    IF_C goto tilemap_1;
    LD_A_addr(wJumptableIndex);
    CP_A(2);
    IF_Z goto tilemap_1;
    CP_A(3);
    IF_Z goto tilemap_1;
    CP_A(6);
    IF_Z goto tilemap_1;

    LD_BC(mFunction11b31b_Tilemap2);
    goto load_sprites;


tilemap_3:
    LD_BC(mFunction11b31b_Tilemap3);
    goto load_sprites;


tilemap_1:
    LD_BC(mFunction11b31b_Tilemap1);


load_sprites:
    CALL(aFunction11b397);
    RET;


Coords:
    //dbpixel ['3', '11', '2', '6']  //  0
    //dbpixel ['3', '12', '2', '6']  //  1
    //dbpixel ['3', '13', '2', '6']  //  2
    //dbpixel ['3', '14', '2', '6']  //  3
    //dbpixel ['3', '15', '2', '6']  //  4
    //dbpixel ['3', '16', '2', '6']  //  5
    //dbpixel ['3', '17', '2', '6']  //  6
    //dbpixel ['4', '11', '2', '6']  //  7
    //dbpixel ['4', '12', '2', '6']  //  8
    //dbpixel ['4', '13', '2', '6']  //  9
    //dbpixel ['4', '14', '2', '6']  // 10
    //dbpixel ['4', '15', '2', '6']  // 11
    //dbpixel ['4', '16', '2', '6']  // 12
    //dbpixel ['4', '17', '2', '6']  // 13
    //db ['-1'];


Tilemap1:
//   //  vtiles
    //db ['0x30'];  //  0
    //db ['0x31'];  //  1
    //db ['0x31'];  //  2
    //db ['0x31'];  //  3
    //db ['0x31'];  //  4
    //db ['0x31'];  //  5
    //db ['0x32'];  //  6
    //db ['0x40'];  //  7
    //db ['0x41'];  //  8
    //db ['0x41'];  //  9
    //db ['0x41'];  // 10
    //db ['0x41'];  // 11
    //db ['0x41'];  // 12
    //db ['0x42'];  // 13


Tilemap2:
//   //  vtiles
    //db ['0x30'];  //  0
    //db ['0x31'];  //  1
    //db ['0x31'];  //  2
    //db ['0x39'];  //  3
    //db ['0x39'];  //  4
    //db ['0x39'];  //  5
    //db ['0x39'];  //  6
    //db ['0x40'];  //  7
    //db ['0x41'];  //  8
    //db ['0x41'];  //  9
    //db ['0x39'];  // 10
    //db ['0x39'];  // 11
    //db ['0x39'];  // 12
    //db ['0x39'];  // 13


Tilemap3:
//   //  vtiles
    //db ['0x39'];  //  0
    //db ['0x39'];  //  1
    //db ['0x39'];  //  2
    //db ['0x39'];  //  3
    //db ['0x39'];  //  4
    //db ['0x39'];  //  5
    //db ['0x39'];  //  6
    //db ['0x39'];  //  7
    //db ['0x39'];  //  8
    //db ['0x39'];  //  9
    //db ['0x39'];  // 10
    //db ['0x39'];  // 11
    //db ['0x39'];  // 12
    //db ['0x39'];  // 13

    return Function11b397();
}

void Function11b397(void){
    LD_DE(wVirtualOAMSprite00);

loop:
    LD_A_hl;
    CP_A(0xff);
    RET_Z ;
    LD_A_addr(wc7d1);
    AND_A(0x7);
    SWAP_A;
    ADD_A_hl;
    INC_HL;
    LD_de_A;  // y
    INC_DE;

    LD_A_hli;
    LD_de_A;  // x
    INC_DE;

    LD_A_bc;
    INC_BC;
    LD_de_A;  // tile id
    INC_DE;
    LD_A(0x5);
    LD_de_A;  // attributes
    INC_DE;
    goto loop;

    return Function11b3b6();
}

void Function11b3b6(void){
//  //  unreferenced

loop:
    LD_A_hl;
    CP_A(-1);
    RET_Z ;
    LD_A_addr(wcd4d);
    AND_A(0x7);
    SWAP_A;
    ADD_A_hl;
    INC_HL;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    PUSH_HL;
    LD_L_C;
    LD_H_B;
    LD_A_addr(wcd4e);
    ADD_A_hl;
    INC_BC;
    LD_de_A;
    INC_DE;
    POP_HL;
    LD_A(0x5);
    LD_de_A;
    INC_DE;
    goto loop;

    return Function11b3d9();
}

void Function11b3d9(void){
    LD_DE(wVirtualOAMSprite28);
    PUSH_DE;
    LD_A_addr(wc7d2);
    DEC_A;
    LD_E_A;
    LD_A_addr(wc7d1);
    LD_HL(wc7d0);
    ADD_A_hl;
    CP_A_E;
    IF_Z goto skip;
    LD_HL(0);
    LD_BC(0x70);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    LD_B(0);
    LD_A_D;
    OR_A_E;
    IF_Z goto load_sprites;
    LD_A_addr(wc7d2);
    LD_C_A;

loop1:
    LD_A_E;
    SUB_A_C;
    LD_E_A;
    LD_A_D;
    SBC_A(0x0);
    LD_D_A;
    IF_C goto load_sprites;
    INC_B;
    goto loop1;


skip:
    LD_B(14 * 8);


load_sprites:
    LD_A(2 * 8 + 5);
    ADD_A_B;
    POP_HL;
    LD_hli_A;
    CP_A(0x41);
    IF_C goto version1;
    LD_A_addr(wJumptableIndex);
    CP_A(4);
    IF_Z goto version2;
    CP_A(5);
    IF_Z goto version2;
    CP_A(7);
    IF_Z goto version2;
    CP_A(8);
    IF_Z goto version2;


version1:
    LD_A(19 * 8 + 3);
    LD_hli_A;
    LD_A_addr(wcd4c);
    ADD_A(0x3c);
    LD_hli_A;
    LD_A_addr(wcd4c);
    ADD_A(0x1);
    LD_hl_A;
    RET;


version2:
    LD_A(19 * 8 + 3);
    LD_hli_A;
    LD_A(0x39);
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    RET;

}

void Function11b444(void){
//  special
    CALL(aMobile46_InitJumptable);
    CALL(aMobile46_RunJumptable);
    RET;

}

void Mobile46_InitJumptable(void){
    XOR_A_A;
    LD_addr_A(wJumptableIndex);
    LD_addr_A(wcf64);
    LD_addr_A(wcf65);
    LD_addr_A(wcf66);
    CALL(aUpdateTime);
    RET;

}

void Mobile46_RunJumptable(void){

loop:
    CALL(aMobile46_RunJumptable_IterateJumptable);
    CALL(aDelayFrame);
    LD_A_addr(wJumptableIndex);
    CP_A(4);
    IF_NZ goto loop;
    RET;


IterateJumptable:
    //jumptable ['.Jumptable', 'wJumptableIndex']


Jumptable:
    //dw ['Function11b483'];
    //dw ['Function11b570'];
    //dw ['Function11b5c0'];
    //dw ['Function11b5e0'];
    //dw ['Function11b5e7'];  // unused

    return Function11b483();
}

void Function11b483(void){
    CALL(aFunction11b483_InitRAM);
    LD_HL(wPlayerName);
    LD_A(NAME_LENGTH_JAPANESE - 1);

loop1:
    PUSH_AF;
    LD_A_hli;
    LD_bc_A;
    INC_BC;
    POP_AF;
    DEC_A;
    AND_A_A;
    IF_NZ goto loop1;

    LD_DE(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1Species);
    LD_A_addr(wcd82);
    DEC_A;
    PUSH_AF;

loop2:
    AND_A_A;
    IF_Z goto okay;
    ADD_HL_DE;
    DEC_A;
    goto loop2;


okay:
    PUSH_BC;
    LD_A(PARTYMON_STRUCT_LENGTH);

loop3:
    PUSH_AF;
    LD_A_hli;
    LD_bc_A;
    INC_BC;
    POP_AF;
    DEC_A;
    AND_A_A;
    IF_NZ goto loop3;

    POP_DE;
    PUSH_BC;
    LD_A_de;
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_HL(MON_LEVEL);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wCurPartyLevel);
    LD_HL(MON_MAXHP);
    ADD_HL_DE;
    PUSH_HL;
    LD_HL(MON_STAT_EXP - 1);
    ADD_HL_DE;
    POP_DE;
    PUSH_DE;
    LD_B(TRUE);
    PREDEF(pCalcMonStats);
    POP_DE;
    LD_H_D;
    LD_L_E;
    DEC_HL;
    DEC_HL;
    LD_A_de;
    LD_hli_A;
    INC_DE;
    LD_A_de;
    LD_hl_A;
    POP_BC;
    LD_DE(NAME_LENGTH);
    LD_HL(wPartyMonOTs);
    POP_AF;
    PUSH_AF;

loop4:
    AND_A_A;
    IF_Z goto okay2;
    ADD_HL_DE;
    DEC_A;
    goto loop4;


okay2:
    LD_A(NAME_LENGTH - 1);

loop5:
    PUSH_AF;
    LD_A_hli;
    LD_bc_A;
    INC_BC;
    POP_AF;
    DEC_A;
    AND_A_A;
    IF_NZ goto loop5;
    LD_DE(NAME_LENGTH);
    LD_HL(wPartyMonNicknames);
    POP_AF;
    PUSH_AF;

loop6:
    AND_A_A;
    IF_Z goto okay3;
    ADD_HL_DE;
    DEC_A;
    goto loop6;


okay3:
    LD_A(NAME_LENGTH - 1);

loop7:
    PUSH_AF;
    LD_A_hli;
    LD_bc_A;
    INC_BC;
    POP_AF;
    DEC_A;
    AND_A_A;
    IF_NZ goto loop7;
    LD_DE(MAIL_STRUCT_LENGTH);
    LD_HL(sPartyMail);
    POP_AF;

loop8:
    AND_A_A;
    IF_Z goto okay4;
    ADD_HL_DE;
    DEC_A;
    goto loop8;


okay4:
    LD_A(BANK(sPartyMail));
    CALL(aOpenSRAM);
    LD_A(MAIL_STRUCT_LENGTH);

loop9:
    PUSH_AF;
    LD_A_hli;
    LD_bc_A;
    INC_BC;
    POP_AF;
    DEC_A;
    AND_A_A;
    IF_NZ goto loop9;
    CALL(aCloseSRAM);
    JP(mFunction11ad8a);


InitRAM:
    LD_BC(0xc626);
    LD_A_addr(wPlayerID);
    LD_addr_A(wcd2a);
    LD_bc_A;
    INC_BC;

    LD_A_addr(wPlayerID + 1);
    LD_addr_A(wcd2b);
    LD_bc_A;
    INC_BC;

    LD_A_addr(wSecretID);
    LD_addr_A(wcd2c);
    LD_bc_A;
    INC_BC;

    LD_A_addr(wSecretID + 1);
    LD_addr_A(wcd2d);
    LD_bc_A;
    INC_BC;

    LD_A_addr(wcd2e);
    LD_bc_A;
    INC_BC;

    LD_A_addr(wcd2f);
    LD_bc_A;
    INC_BC;

    LD_A_addr(wcd30);
    LD_bc_A;
    INC_BC;

    LD_A_addr(wd265);
    LD_bc_A;
    INC_BC;
    RET;

}

void Function11b570(void){
    CALL(aFunction118007);
    LD_A_addr(wScriptVar);
    AND_A_A;
    IF_NZ goto exit;
    CALL(aFunction11b570_SaveData);
    JP(mFunction11ad8a);


exit:
    LD_A(0x4);
    LD_addr_A(wJumptableIndex);
    RET;


SaveData:
    LD_A(0x3);
    LDH_addr_A(rSVBK);

    LD_HL(w3_d800);
    LD_DE(0xc608);
    LD_BC(w3_d88f - w3_d800);
    CALL(aCopyBytes);

    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_A(BANK(s5_a800));
    CALL(aOpenSRAM);

    LD_DE(s5_a800);
    LD_A(0x1);
    LD_de_A;
    INC_DE;
    LD_HL(0xc608);
    LD_BC(w3_d88f - w3_d800);
    CALL(aCopyBytes);

    PUSH_DE;
    POP_HL;

    LDH_A_addr(hRTCMinutes);
    LD_hli_A;
    LDH_A_addr(hRTCHours);
    LD_hli_A;
    LDH_A_addr(hRTCDayLo);
    LD_hli_A;
    LDH_A_addr(hRTCDayHi);
    LD_hl_A;

    CALL(aCloseSRAM);
    RET;

}

void Function11b5c0(void){
    LD_A_addr(wcd82);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    FARCALL(aFunction170807);
    FARCALL(aSaveAfterLinkTrade);
    JP(mFunction11ad8a);

}

void Function11b5e0(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    JP(mFunction11ad8a);

}

void Function11b5e7(void){
    RET;

}

void Function11b5e8(void){
    LD_A(0x0);
    CALL(aOpenSRAM);
    LD_HL(wRTC);
    LD_DE(0xc608);
    LD_BC(4);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_HL(0xc608);
    LD_DE(0xb08c);
    LD_BC(4);
    CALL(aCopyBytes);
    LD_A(0x2);
    LD_addr_A(0xa800);
    LD_A_addr(0xa81f);
    LD_addr_A(wcd2a);
    LD_A_addr(0xa820);
    LD_addr_A(wcd2b);
    LD_A_addr(0xa821);
    LD_addr_A(wcd2c);
    LD_A_addr(0xa822);
    LD_addr_A(wcd2d);
    LD_A_addr(0xa823);
    LD_addr_A(wcd2e);
    LD_A_addr(0xa824);
    LD_addr_A(wcd2f);
    LD_A_addr(0xa825);
    LD_addr_A(wcd30);
    LD_A_addr(0xa826);
    LD_addr_A(wcd31);
    CALL(aCloseSRAM);
    CALL(aMobile46_InitJumptable);
    CALL(aFunction11b5e8_loop);
    RET;


loop:
    CALL(aFunction11b5e8_RunJumptable);
    CALL(aDelayFrame);
    LD_A_addr(wJumptableIndex);
    CP_A(0x1);
    IF_NZ goto loop;
    RET;


RunJumptable:
    //jumptable ['.Jumptable', 'wJumptableIndex']


Jumptable:
    //dw ['Function11b66d'];
    //dw ['Function11b6b3'];

    return Function11b66d();
}

void Function11b66d(void){
    CALL(aFunction1180b8);
    LD_A_addr(wScriptVar);
    AND_A_A;
    IF_NZ goto asm_11b6b0;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);
    LD_A_addr(w3_d090);
    LD_B_A;
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A_B;
    AND_A_A;
    IF_Z goto asm_11b691;
    CP_A(0x1);
    IF_NZ goto asm_11b6b0;
    CALL(aFunction11b6b4);
    goto asm_11b6b0;


asm_11b691:
    FARCALL(aFunction17081d);
    LD_A_addr(wScriptVar);
    AND_A_A;
    IF_Z goto asm_11b6b0;
    XOR_A_A;
    LD_addr_A(wScriptVar);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);
    LD_A(0x2);
    LD_addr_A(w3_d090);
    POP_AF;
    LDH_addr_A(rSVBK);


asm_11b6b0:
    JP(mFunction11ad8a);

}

void Function11b6b3(void){
    RET;

}

void Function11b6b4(void){
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_A_addr(wcd30);
    LD_addr_A(0xc708);
    LD_A_addr(wcd31);
    LD_addr_A(0xc709);

    LD_A(LOW(0xc708));  // Species
    LD_addr_A(wMobileMonSpeciesPointer);
    LD_A(HIGH(0xc708));
    LD_addr_A(wMobileMonSpeciesPointer + 1);

    LD_A(LOW(0xc60d));  // Partymon Struct
    LD_addr_A(wMobileMonStructPointer);
    LD_A(HIGH(0xc60d));
    LD_addr_A(wMobileMonStructPointer + 1);

    LD_A(LOW(0xc63d));  // OT
    LD_addr_A(wMobileMonOTPointer);
    LD_A(HIGH(0xc63d));
    LD_addr_A(wMobileMonOTPointer + 1);

    LD_A(LOW(0xc642));  // Nickname
    LD_addr_A(wMobileMonNicknamePointer);
    LD_A(HIGH(0xc642));
    LD_addr_A(wMobileMonNicknamePointer + 1);

    LD_A(LOW(0xc647));  // Mail
    LD_addr_A(wMobileMonMailPointer);
    LD_A(HIGH(0xc647));
    LD_addr_A(wMobileMonMailPointer + 1);

    LD_A(0x46);
    LD_addr_A(0xc628);

    LD_DE(0xc63d);
    LD_C(5);
    FARCALL(aCheckStringForErrors);
    IF_NC goto length_check_OT;
    FARCALL(aMobile_CopyDefaultOTName);


length_check_OT:
    LD_DE(0xc63d);
    LD_BC((1 << 8) | 5);
    FARCALL(aCheckStringContainsLessThanBNextCharacters);
    IF_NC goto error_check_nick;
    FARCALL(aMobile_CopyDefaultOTName);


error_check_nick:
    LD_DE(0xc642);
    LD_C(5);
    FARCALL(aCheckStringForErrors);
    IF_NC goto length_check_nick;
    FARCALL(aMobile_CopyDefaultNickname);


length_check_nick:
    LD_DE(0xc642);
    LD_BC((1 << 8) | 5);
    FARCALL(aCheckStringContainsLessThanBNextCharacters);
    IF_NC goto error_check_mail;
    FARCALL(aMobile_CopyDefaultNickname);


error_check_mail:
    LD_DE(0xc647);
    LD_C(MAIL_MSG_LENGTH + 1);
    FARCALL(aCheckStringForErrors);
    IF_NC goto length_check_mail;
    FARCALL(aMobile_CopyDefaultMail);


length_check_mail:
    LD_DE(0xc647);
    LD_BC((2 << 8) | (MAIL_MSG_LENGTH + 1));
    FARCALL(aCheckStringContainsLessThanBNextCharacters);
    IF_C goto fix_mail;
    LD_A_B;
    CP_A(0x2);
    IF_NZ goto mail_ok;


fix_mail:
    FARCALL(aMobile_CopyDefaultMail);


mail_ok:
    LD_DE(0xc668);
    LD_C(0x5);
    FARCALL(aCheckStringForErrors);
    IF_NC goto length_check_author;
    FARCALL(aMobile_CopyDefaultMailAuthor);


length_check_author:
    LD_DE(0xc668);
    LD_BC((1 << 8) | 5);
    FARCALL(aCheckStringContainsLessThanBNextCharacters);
    IF_NC goto author_okay;
    FARCALL(aMobile_CopyDefaultMailAuthor);


author_okay:
    LD_A_addr(0xc60e);
    CP_A(-1);
    IF_NZ goto item_okay;
    XOR_A_A;
    LD_addr_A(0xc60e);


item_okay:
    LD_A_addr(wcd31);
    LD_addr_A(0xc60d);
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);

    LD_HL(0xc60d + MON_LEVEL);
    LD_A_hl;
    CP_A(MIN_LEVEL);
    LD_A(MIN_LEVEL);
    IF_C goto replace_level;
    LD_A_hl;
    CP_A(MAX_LEVEL);
    IF_C goto done_level;
    LD_A(MAX_LEVEL);

replace_level:
    LD_hl_A;

done_level:
    LD_addr_A(wCurPartyLevel);

    LD_HL(0xc60d + MON_STAT_EXP - 1);
    LD_DE(0xc60d + MON_MAXHP);
    LD_B(TRUE);
    PREDEF(pCalcMonStats);
    LD_DE(0xc60d + MON_MAXHP);
    LD_HL(0xc60d + MON_HP);
    LD_A_de;
    LD_hli_A;
    INC_DE;
    LD_A_de;
    LD_hl_A;
    CALL(aAddMobileMonToParty);
    RET;

}

void Function11b7e5(void){
    LD_A_addr(0xc60d);  // species
    LD_addr_A(wOTTrademonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_A_addr(wcd81);
    LD_addr_A(wc74e);
    LD_HL(0xc63d);  // OT
    LD_DE(wOTTrademonOTName);
    LD_BC(5);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    LD_A_addr(0xc60d + MON_ID);  // id
    LD_addr_A(wOTTrademonID);
    LD_A_addr(0xc60d + MON_ID + 1);
    LD_addr_A(wOTTrademonID + 1);
    LD_HL(0xc60d + MON_DVS);  // dvs
    LD_A_hli;
    LD_addr_A(wOTTrademonDVs);
    LD_A_hl;
    LD_addr_A(wOTTrademonDVs + 1);
    LD_BC(0xc60d);  // pokemon_data_start
    FARCALL(aGetCaughtGender);
    LD_A_C;
    LD_addr_A(wOTTrademonCaughtData);
    CALL(aSpeechTextbox);
    CALL(aFadeToMenu);
    FARCALL(aMobileTradeAnimation_ReceiveGetmonFromGTS);
    FARCALL(aFunction17d1f1);
    LD_A(0x1);
    LD_addr_A(wForceEvolution);
    LD_A(LINK_TRADECENTER);
    LD_addr_A(wLinkMode);
    FARCALL(aEvolvePokemon);
    XOR_A_A;
    LD_addr_A(wLinkMode);
    FARCALL(aSaveAfterLinkTrade);
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_A(0x5);
    LD_addr_A(0xa800);
    CALL(aCloseSRAM);
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetMapSceneID);
    LD_A_D;
    OR_A_E;
    IF_Z goto asm_11b872;
    LD_A(0x1);
    LD_de_A;


asm_11b872:
    CALL(aCloseSubmenu);
    CALL(aRestartMapMusic);
    RET;

}

void Function11b879(void){
    FARCALL(aBattleTower_CheckSaveFileExistsAndIsYours);
    LD_A_addr(wScriptVar);
    AND_A_A;
    RET_Z ;
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_A_addr(0xa800);
    LD_addr_A(wScriptVar);
    LD_A_addr(0xa890);
    LD_addr_A(wcd49);
    LD_A_addr(0xa891);
    LD_addr_A(wcd4a);
    LD_A_addr(0xa892);
    LD_addr_A(wcd4b);
    LD_A_addr(0xa893);
    LD_addr_A(wcd4c);
    CALL(aCloseSRAM);
    LD_A_addr(wScriptVar);
    AND_A_A;
    RET_Z ;
    LD_HL(wcd4c);
    LDH_A_addr(hRTCDayHi);
    CP_A_hl;
    RET_NZ ;
    DEC_HL;
    LDH_A_addr(hRTCDayLo);
    CP_A_hl;
    RET_NZ ;
    LD_HL(wcd4a);
    LDH_A_addr(hRTCHours);
    CP_A_hl;
    IF_NC goto asm_11b8d8;
    LD_A(0x18);
    SUB_A_hl;
    LD_HL(hRTCHours);
    ADD_A_hl;
    LD_addr_A(wcd4c);
    LDH_A_addr(hRTCMinutes);
    LD_addr_A(wcd4b);
    XOR_A_A;
    LD_addr_A(wcd4a);
    goto asm_11b8e2;


asm_11b8d8:
    LDH_A_addr(hRTCMinutes);
    LD_addr_A(wcd4b);
    LDH_A_addr(hRTCHours);
    LD_addr_A(wcd4c);


asm_11b8e2:
    XOR_A_A;
    LD_L_A;
    LD_H_A;
    LD_B_A;
    LD_D_A;
    LD_A_addr(wcd4b);
    LD_E_A;
    LD_A_addr(wcd4c);
    LD_C(0x3c);
    CALL(aAddNTimes);
    ADD_HL_DE;
    PUSH_HL;
    XOR_A_A;
    LD_L_A;
    LD_H_A;
    LD_B_A;
    LD_D_A;
    LD_A_addr(wcd49);
    LD_E_A;
    LD_A_addr(wcd4a);
    LD_C(0x3c);
    CALL(aAddNTimes);
    ADD_HL_DE;
    LD_A_L;
    CPL;
    ADD_A(0x1);
    LD_E_A;
    LD_A_H;
    CPL;
    ADC_A(0);
    LD_D_A;
    POP_HL;
    ADD_HL_DE;
    LD_DE(0xff88);
    ADD_HL_DE;
    BIT_H(7);
    RET_Z ;
    LD_A(0x2);
    LD_addr_A(wScriptVar);
    RET;

}

void Function11b920(void){
    CALL(aMobile46_InitJumptable);
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_HL(0xa81f);
    LD_DE(0xc626);
    LD_BC(8);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    CALL(aFunction118000);
    RET;

}

void Function11b93b(void){
    LD_A(0x5);
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_addr_A(0xa800);
    LD_HL(0xa823);
    LD_DE(0xc608);
    LD_BC(0x008f);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);

    LD_A(LOW(0xc608));
    LD_addr_A(wMobileMonSpeciesPointer);
    LD_A(HIGH(0xc608));
    LD_addr_A(wMobileMonSpeciesPointer + 1);

    LD_A(LOW(0xc611));
    LD_addr_A(wMobileMonStructPointer);
    LD_A(HIGH(0xc611));
    LD_addr_A(wMobileMonStructPointer + 1);

    LD_A(LOW(0xc641));
    LD_addr_A(wMobileMonOTPointer);
    LD_A(HIGH(0xc641));
    LD_addr_A(wMobileMonOTPointer + 1);

    LD_A(LOW(0xc646));
    LD_addr_A(wMobileMonNicknamePointer);
    LD_A(HIGH(0xc646));
    LD_addr_A(wMobileMonNicknamePointer + 1);

    LD_A(LOW(0xc64b));
    LD_addr_A(wMobileMonMailPointer);
    LD_A(HIGH(0xc64b));
    LD_addr_A(wMobileMonMailPointer + 1);
    CALL(aAddMobileMonToParty);
    FARCALL(aSaveAfterLinkTrade);
    RET;

}

void AddMobileMonToParty(const species_t* species, const struct PartyMon* mobilemon, const uint8_t* ot, const uint8_t* nick, const struct MailMsg* mail){
    // LD_HL(wPartyCount);
    // LD_A_hl;
    // LD_E_A;
    // INC_hl;
    uint8_t e = wram->wPartyCount++;

    // LD_A_addr(wMobileMonSpeciesPointer);
    // LD_L_A;
    // LD_A_addr(wMobileMonSpeciesPointer + 1);
    // LD_H_A;
    // INC_HL;
    // LD_BC(wPartySpecies);
    species_t* bc = wram->wPartySpecies + e;
    // LD_D_E;

// loop1:
    // INC_BC;
    // DEC_D;
    // IF_NZ goto loop1;
    // LD_A_E;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = e;
    // LD_A_hl;
    // LD_bc_A;
    *bc = *species;
    // INC_BC;
    // LD_A(-1);
    // LD_bc_A;
    bc[1] = (species_t)-1;

    // LD_HL(wPartyMon1Species);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    struct PartyMon* mon = wram->wPartyMon + e;
    // LD_A_E;
    // LD_addr_A(wMobileMonSpecies);
    wram->wMobileMonSpecies = e;

// loop2:
    // ADD_HL_BC;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop2;
    // LD_E_L;
    // LD_D_H;
    // LD_A_addr(wMobileMonStructPointer);
    // LD_L_A;
    // LD_A_addr(wMobileMonStructPointer + 1);
    // LD_H_A;
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(mon, mobilemon, PARTYMON_STRUCT_LENGTH);

    // LD_HL(wPartyMonOTs);
    // LD_BC(NAME_LENGTH);
    // LD_A_addr(wMobileMonSpecies);
    uint8_t* ot2 = wram->wPartyMonOT[e];

// loop3:
    // ADD_HL_BC;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop3;
    // LD_E_L;
    // LD_D_H;
    // LD_A_addr(wMobileMonOTPointer);
    // LD_L_A;
    // LD_A_addr(wMobileMonOTPointer + 1);
    // LD_H_A;
    // LD_BC(MON_NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(ot2, ot, MON_NAME_LENGTH - 1);
    // LD_A(0x50);
    // LD_de_A;
    ot2[MON_NAME_LENGTH - 1] = 0x50;

    // LD_HL(wPartyMonNicknames);
    // LD_BC(MON_NAME_LENGTH);
    // LD_A_addr(wMobileMonSpecies);
    uint8_t* nickname2 = wram->wPartyMonNickname[e];

// loop4:
    // ADD_HL_BC;
    // DEC_A;
    // AND_A_A;
    // IF_NZ goto loop4;
    // LD_E_L;
    // LD_D_H;
    // LD_A_addr(wMobileMonNicknamePointer);
    // LD_L_A;
    // LD_A_addr(wMobileMonNicknamePointer + 1);
    // LD_H_A;
    // LD_BC(MON_NAME_LENGTH - 1);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(nickname2, nick, MON_NAME_LENGTH - 1);
    // LD_A(0x50);
    // LD_de_A;
    nickname2[MON_NAME_LENGTH - 1] = 0x50;

    // LD_HL(sPartyMail);
    // LD_BC(MAIL_STRUCT_LENGTH);
    // LD_A_addr(wMobileMonSpecies);

// loop5:
    if(mail != NULL) {
        // ADD_HL_BC;
        // DEC_A;
        // AND_A_A;
        // IF_NZ goto loop5;
        // LD_A(BANK(sPartyMail));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(asPartyMail));
        // LD_E_L;
        // LD_D_H;
        // LD_A_addr(wMobileMonMailPointer);
        // LD_L_A;
        // LD_A_addr(wMobileMonMailPointer + 1);
        // LD_H_A;
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(GBToRAMAddr(sPartyMail + MAIL_STRUCT_LENGTH * e), mail, MAIL_STRUCT_LENGTH);

        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
    }
    // RET;
}

void Function11ba38(void){
    FARCALL(aCheckCurPartyMonFainted);
    RET_C ;
    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;

}

void TilemapPack_11ba44(void){
    //db ['0x47', '0x30', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x56'];  // 00
    //db ['0x46', '0x2f', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x55'];  // 01
    //db ['0x45', '0x3d', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x54'];  // 02
    //db ['0x44', '0x30', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x53'];  // 03
    //db ['0x43', '0x2f', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x52'];  // 04
    //db ['0x4a', '0x3d', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x51'];  // 05
    //db ['0x4a', '0x30', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x50'];  // 06
    //db ['0x4a', '0x2f', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x4f'];  // 07
    //db ['0x4a', '0x3d', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x4e'];  // 08
    //db ['0x4a', '0x30', '0x0a', '0x0a', '0x0a', '0x0a', '0x4d', '0x42'];  // 09
    //db ['0x4a', '0x2f', '0x0a', '0x0a', '0x0a', '0x0a', '0x6b', '0x58'];  // 0a
    //db ['0x4a', '0x3d', '0x0a', '0x0a', '0x0a', '0x0a', '0x6a', '0x58'];  // 0b
    //db ['0x4a', '0x30', '0x0a', '0x0a', '0x0a', '0x0a', '0x69', '0x58'];  // 0c
    //db ['0x4a', '0x2f', '0x0a', '0x0a', '0x0a', '0x0a', '0x68', '0x58'];  // 0d
    //db ['0x4a', '0x3d', '0x0a', '0x0a', '0x0a', '0x66', '0x67', '0x58'];  // 0e
    //db ['0x4a', '0x30', '0x0a', '0x0a', '0x0a', '0x65', '0x0a', '0x58'];  // 0f
    //db ['0x4a', '0x2f', '0x0a', '0x0a', '0x0a', '0x64', '0x0a', '0x58'];  // 10
    //db ['0x4a', '0x3d', '0x0a', '0x0a', '0x0a', '0x63', '0x0a', '0x58'];  // 11
    //db ['0x4a', '0x30', '0x0a', '0x0a', '0x61', '0x62', '0x0a', '0x58'];  // 12
    //db ['0x4a', '0x2f', '0x0a', '0x0a', '0x5f', '0x60', '0x0a', '0x58'];  // 13
    //db ['0x4a', '0x3d', '0x0a', '0x61', '0x62', '0x0a', '0x0a', '0x58'];  // 14
    //db ['0x4a', '0x30', '0x0a', '0x63', '0x0a', '0x0a', '0x0a', '0x58'];  // 15
    //db ['0x4a', '0x2f', '0x69', '0x0a', '0x0a', '0x0a', '0x0a', '0x58'];  // 16
    //db ['0x4a', '0x3d', '0x81', '0x0a', '0x0a', '0x0a', '0x0a', '0x58'];  // 17
    //db ['0x4a', '0x30', '0x80', '0x0a', '0x0a', '0x0a', '0x0a', '0x58'];  // 18
    //db ['0x4a', '0x2f', '0x7f', '0x0a', '0x0a', '0x0a', '0x0a', '0x58'];  // 19
    //db ['0x4a', '0x3d', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x58'];  // 1a
    //db ['0x4a', '0x30', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x58'];  // 1b
    //db ['0x4a', '0x2f', '0x68', '0x87', '0x88', '0x89', '0x0a', '0x58'];  // 1c
    //db ['0x4a', '0x3d', '0x6e', '0x6f', '0x70', '0x75', '0x76', '0x58'];  // 1d
    //db ['0x4a', '0x30', '0x75', '0x76', '0x5c', '0x5d', '0x5e', '0x58'];  // 1e
    //db ['0x4a', '0x2f', '0x71', '0x72', '0x73', '0x74', '0x6d', '0x58'];  // 1f
    //db ['0x4a', '0x3d', '0x75', '0x76', '0x77', '0x8a', '0x8b', '0x58'];  // 20
    //db ['0x4a', '0x30', '0x66', '0x67', '0x65', '0x0a', '0x6a', '0x58'];  // 21
    //db ['0x4a', '0x2f', '0x83', '0x84', '0x0a', '0x83', '0x84', '0x58'];  // 22
    //db ['0x4a', '0x3d', '0x0a', '0x85', '0x82', '0x84', '0x0a', '0x58'];  // 23
    //db ['0x4a', '0x30', '0x41', '0x80', '0x40', '0x0a', '0x0a', '0x58'];  // 24
    //db ['0x4a', '0x2f', '0x83', '0x0a', '0x0a', '0x0a', '0x0a', '0x58'];  // 25
    //db ['0x4a', '0x3d', '0x40', '0x0a', '0x0a', '0x0a', '0x0a', '0x58'];  // 26
    //db ['-1'];

    return TilemapPack_11bb7d();
}

void TilemapPack_11bb7d(void){
    //db ['0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x16', '0x00'];  // 00
    //db ['0x78', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x8c', '0x00'];  // 01
    //db ['0x79', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x8d', '0x00'];  // 02
    //db ['0x7a', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x8e', '0x00'];  // 03
    //db ['0x7b', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x8c', '0x00'];  // 04
    //db ['0x7c', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x8d', '0x00'];  // 05
    //db ['0x7d', '0x0a', '0x0a', '0x0a', '0x0a', '0x0a', '0x8e', '0x00'];  // 06
    //db ['0x2e', '0x7e', '0x0a', '0x0a', '0x0a', '0x0a', '0x8c', '0x00'];  // 07
    //db ['0x2e', '0x80', '0x0a', '0x0a', '0x0a', '0x0a', '0x8d', '0x00'];  // 08
    //db ['0x2e', '0x81', '0x0a', '0x0a', '0x0a', '0x0a', '0x8e', '0x00'];  // 09
    //db ['0x2e', '0x82', '0x0a', '0x0a', '0x0a', '0x0a', '0x8c', '0x00'];  // 0a
    //db ['0x2e', '0x69', '0x0a', '0x0a', '0x0a', '0x0a', '0x8d', '0x00'];  // 0b
    //db ['0x2e', '0x6a', '0x0a', '0x0a', '0x0a', '0x0a', '0x8e', '0x00'];  // 0c
    //db ['0x2e', '0x6b', '0x0a', '0x0a', '0x0a', '0x0a', '0x8c', '0x00'];  // 0d
    //db ['0x2e', '0x0a', '0x68', '0x0a', '0x0a', '0x0a', '0x8d', '0x00'];  // 0e
    //db ['0x2e', '0x0a', '0x69', '0x0a', '0x0a', '0x0a', '0x8e', '0x00'];  // 0f
    //db ['0x2e', '0x0a', '0x0a', '0x6a', '0x0a', '0x0a', '0x8c', '0x00'];  // 10
    //db ['0x2e', '0x0a', '0x0a', '0x6b', '0x0a', '0x0a', '0x8d', '0x00'];  // 11
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x80', '0x0a', '0x8e', '0x00'];  // 12
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x82', '0x0a', '0x8c', '0x00'];  // 13
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x6c', '0x0a', '0x8d', '0x00'];  // 14
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x0a', '0x83', '0x8e', '0x00'];  // 15
    //db ['0x2e', '0x0a', '0x6b', '0x0a', '0x0a', '0x0a', '0x8c', '0x00'];  // 16
    //db ['0x2e', '0x0a', '0x0a', '0x69', '0x0a', '0x0a', '0x8d', '0x00'];  // 17
    //db ['0x2e', '0x0a', '0x0a', '0x6a', '0x0a', '0x0a', '0x8e', '0x00'];  // 18
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x68', '0x0a', '0x8c', '0x00'];  // 19
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x63', '0x0a', '0x8d', '0x00'];  // 1a
    //db ['0x2e', '0x0a', '0x0a', '0x61', '0x62', '0x0a', '0x8e', '0x00'];  // 1b
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x5f', '0x60', '0x8c', '0x00'];  // 1c
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x63', '0x0a', '0x8d', '0x00'];  // 1d
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x0a', '0x69', '0x8c', '0x00'];  // 1e
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x0a', '0x6b', '0x8d', '0x00'];  // 1f
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x0a', '0x83', '0x8e', '0x00'];  // 20
    //db ['0x2e', '0x0a', '0x0a', '0x0a', '0x0a', '0x86', '0x8c', '0x00'];  // 21
    //db ['0x2e', '0x0a', '0x85', '0x0a', '0x0a', '0x0a', '0x8d', '0x00'];  // 22
    //db ['0x2e', '0x0a', '0x0a', '0x84', '0x0a', '0x0a', '0x8e', '0x00'];  // 23
    //db ['-1'];

}
