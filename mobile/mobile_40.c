#include "../constants.h"
#include "mobile_40.h"
#include "mobile_41.h"
#include "../home/delay.h"
#include "../home/copy.h"
#include "../home/sram.h"
#include "../home/menu.h"
#include "../home/text.h"
#include "../home/joypad.h"
#include "../home/serial.h"
#include "../home/map.h"
#include "../engine/battle/core.h"
#include "../engine/link/place_waiting_text.h"
#include "../engine/events/battle_tower/rules.h"
#include "../data/text/common.h"

void Function100000(void){
//  d: 1 or 2
//  e: bank
//  bc: addr
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(1);
    LDH_addr_A(rSVBK);

    CALL(aFunction100022);
    CALL(aFunction1000ba);
    CALL(aFunction100675);
    CALL(aFunction100057);
    CALL(aFunction10016f);
    CALL(aFunction100276);

    PUSH_BC;
    CALL(aFunction100301);
    POP_BC;

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function100022(void){
    PUSH_DE;
    PUSH_BC;
    CALL(aSetRAMStateForMobile);
    POP_BC;
    POP_DE;
    LD_A_D;
    LD_addr_A(wcd21);
    LD_A_E;
    LD_addr_A(wcd22);
    LD_A_C;
    LD_addr_A(wcd23);
    LD_A_B;
    LD_addr_A(wcd24);
    FARCALL(aFunction10127e);
    FARCALL(aStubbed_Function106462);
    FARCALL(aFunction106464);  // load broken gfx
    FARCALL(aFunction11615a);  // init RAM
    LD_HL(wVramState);
    SET_hl(1);
    RET;

}

void Function100057(void){
    // CALL(aDisableMobile);
    DisableMobile();
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // LD_HL(wVramState);
    // RES_hl(1);
    bit_reset(wram->wVramState, 1);
    // RET;

}

void SetRAMStateForMobile(void){
    // XOR_A_A;
    // LD_HL(wBGMapBuffer);
    // LD_BC(0x65);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wBGMapBuffer, 0x65, 0x0);
    // XOR_A_A;
    // LD_HL(wMobileWRAM);
    // LD_BC(wMobileWRAMEnd - wMobileWRAM);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wMobileErrorCodeBuffer, wMobileWRAMEnd - wMobileWRAM, 0x0);
    // LDH_A_addr(rIE);
    // LD_addr_A(wBGMapBuffer);
    wram->wBGMapBuffer[0] = gb_read(rIE);
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0x0;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0x0;
    // RET;

}

void EnableMobile(void){
    // XOR_A_A;
    // LD_HL(wOverworldMapBlocks);
    // LD_BC(wOverworldMapBlocksEnd - wOverworldMapBlocks);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wOverworldMapBlocks, sizeof(wram->wOverworldMapBlocks), 0x0);

    // NOP;
    // CALL(aDoubleSpeed);
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0x0);
    // LD_A(IE_DEFAULT);
    // LDH_addr_A(rIE);
    gb_write(rIE, IE_DEFAULT);
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0x0;
    // LDH_addr_A(hLCDCPointer);
    hram->hLCDCPointer = 0x0;
    // LD_A(0x01);
    // LDH_addr_A(hMobileReceive);
    hram->hMobileReceive = 0x01;
    // LDH_addr_A(hMobile);
    hram->hMobile = 0x01;
    // NOP;

    // RET;
}

void DisableMobile(void){
    // NOP;
    // XOR_A_A;
    // LDH_addr_A(hMobileReceive);
    hram->hMobileReceive = 0x0;
    // LDH_addr_A(hMobile);
    hram->hMobile = 0x0;
    // XOR_A_A;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0x0;
    // CALL(aNormalSpeed);
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0x0);
    // LD_A_addr(wBGMapBuffer);
    // LDH_addr_A(rIE);
    gb_write(rIE, wram->wBGMapBuffer[0]);
    // NOP;
    // RET;
}

void Function1000ba(void){

loop:
// call [wcd22]:([wcd23][wcd24] + [wMobileCommsJumptableIndex])
    LD_HL(wcd23);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(wMobileCommsJumptableIndex);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_addr(wcd22);
    CALL(aGetFarWord);
    LD_A_addr(wcd22);
    RST(aFarCall);

    CALL(aFunction1000e8);
    CALL(aFunction1000fa);
    CALL(aFunction100144);
    CALL(aFunction100163);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_Z goto loop;
    CALL(aDelayFrame);
    RET;

}

void Function1000e8(void){
    LD_HL(wcd29);
    BIT_hl(7);
    RET_Z ;
    FARCALL(aFunction115dd3);
    LD_HL(wcd29);
    SET_hl(6);
    RET;

}

void Function1000fa(void){
    LD_A_addr(wc30d);
    AND_A_A;
    RET_Z ;
    LD_HL(wcd29);
    BIT_hl(4);
    RET_Z ;
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_100117;
    FARCALL(aFunction11619d);
    LD_HL(wcd29);
    SET_hl(6);
    RET;


asm_100117:
    NOP;
    XOR_A_A;
    LDH_addr_A(rIF);
    LDH_A_addr(rIE);
    AND_A(0x1f ^ (1 << SERIAL | 1 << TIMER));
    LDH_addr_A(rIE);
    XOR_A_A;
    LDH_addr_A(hMobileReceive);
    LDH_addr_A(hMobile);
    NOP;

    LD_A_addr(wLinkMode);
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wLinkMode);
    LD_A(0x04);
    LD_addr_A(wc314 + 5);
    FARCALL(aFunction11619d);
    LD_HL(wcd29);
    SET_hl(6);
    POP_AF;
    LD_addr_A(wLinkMode);
    RET;

}

void Function100144(void){
    LD_HL(wcd29);
    BIT_hl(5);
    IF_Z goto asm_100155;
    RES_hl(5);
    RES_hl(2);
    RES_hl(6);
    CALL(aFunction100320);
    RET;


asm_100155:
    BIT_hl(2);
    RET_Z ;
    RES_hl(2);
    RES_hl(6);
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    RET;

}

void Function100163(void){
    LD_HL(wcd29);
    BIT_hl(6);
    RET_Z ;
    RES_hl(6);
    CALL(aDelayFrame);
    RET;

}

void Function10016f(void){
    LD_A_addr(wcd2b);
    CP_A(0x01);
    RET_Z ;
    CP_A(0x02);
    RET_Z ;
    CP_A(0xff);
    JP_Z (mFunction10016f_asm_1001f5);
    CP_A(0xfe);
    IF_Z goto asm_1001c4;
    CP_A(0xf5);
    IF_Z goto asm_1001e7;
    CP_A(0xf6);
    IF_Z goto asm_1001b6;
    CP_A(0xfa);
    JP_Z (mFunction10016f_asm_1001bd);
    CP_A(0xf7);
    JP_Z (mFunction10016f_asm_1001ee);
    CP_A(0xf4);
    IF_Z goto asm_1001d2;
    CP_A(0xf3);
    IF_Z goto asm_1001cb;
    CP_A(0xf1);
    IF_Z goto asm_1001c4;
    CP_A(0xf2);
    IF_Z goto asm_1001c4;
    CP_A(0xfc);
    IF_Z goto asm_1001e6;
    CP_A(0xfb);
    IF_Z goto asm_1001af;
    CP_A(0xf8);
    RET_Z ;
    RET;  // ????????????????????????????


asm_1001af:
    LD_A(0xd7);
    LD_DE(0);
    goto asm_1001d7;


asm_1001b6:
    LD_A(0xd5);
    LD_DE(0);
    goto asm_1001d7;


asm_1001bd:
    LD_A(0xd6);
    LD_DE(0);
    goto asm_1001d7;


asm_1001c4:
    LD_A(0xd2);
    LD_DE(2);
    goto asm_1001d7;


asm_1001cb:
    LD_A(0xd1);
    LD_DE(1);
    goto asm_1001d7;


asm_1001d2:
    LD_A(0xd0);
    LD_DE(0);


asm_1001d7:
    LD_addr_A(wMobileErrorCodeBuffer);
    LD_A_D;
    LD_addr_A(wMobileErrorCodeBuffer + 2);
    LD_A_E;
    LD_addr_A(wMobileErrorCodeBuffer + 1);
    CALL(aFunction10020b);
    RET;


asm_1001e6:
    RET;


asm_1001e7:
    LD_DE(mString10025e);
    CALL(aFunction100232);
    RET;


asm_1001ee:
    LD_DE(mString10024d);
    CALL(aFunction100232);
    RET;


asm_1001f5:
    LD_A_addr(wcd2c);
    LD_addr_A(wMobileErrorCodeBuffer);
    LD_A_addr(wcd2d);
    LD_addr_A(wMobileErrorCodeBuffer + 2);
    LD_A_addr(wcd2d);
    LD_addr_A(wMobileErrorCodeBuffer + 1);
    CALL(aFunction10020b);
    RET;

}

void Function10020b(void){
    XOR_A_A;
    LD_addr_A(wc303);
    FARCALL(aFadeOutPalettes);
    FARCALL(aFunction106464);
    CALL(aHideSprites);
    CALL(aDelayFrame);

    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x01);
    LDH_addr_A(rSVBK);

    FARCALL(aDisplayMobileError);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function100232(void){
    PUSH_DE;
    FARCALL(aFunction106464);
    CALL(aFunction3f20);
    CALL(aUpdateSprites);
    hlcoord(1, 2, wTilemap);
    POP_DE;
    CALL(aPlaceString);
    CALL(aFunction100320);
    CALL(aJoyWaitAorB);
    RET;

}

void String10024d(void){
    //db ['"つうしんを\u3000キャンセル\u3000しました@"'];

    return String10025e();
}

void String10025e(void){
    //db ['"おともだちと\u3000えらんだ\u3000へやが"'];
    //next ['"ちがうようです@"']

    return Function100276();
}

void Function100276(void){
    LD_A_addr(wcd2b);
    CP_A(0x01);
    IF_Z goto asm_10029f;
    CP_A(0x02);
    IF_Z goto asm_100296;
    CP_A(0xf5);
    IF_Z goto asm_1002a5;
    CP_A(0xf6);
    IF_Z goto asm_1002a5;
    CP_A(0xf7);
    IF_Z goto asm_100293;
    CP_A(0xf8);
    IF_Z goto asm_1002b1;
    goto asm_1002c0;


asm_100293:
    LD_C(0x02);
    RET;


asm_100296:
    FARCALL(aScript_reloadmappart);
    LD_C(0x04);
    RET;


asm_10029f:
    CALL(aFunction1002dc);
    LD_C(0);
    RET;


asm_1002a5:
    FARCALL(aScript_reloadmappart);
    CALL(aFunction1002ed);
    LD_C(0x03);
    RET;


asm_1002b1:
    CALL(aFunction1002c9);
    CALL(aFunction1002dc);
    LD_DE(mString10024d);
    CALL(aFunction100232);
    LD_C(0x02);
    RET;


asm_1002c0:
    CALL(aFunction1002c9);
    CALL(aFunction1002dc);
    LD_C(0x01);
    RET;

}

void Function1002c9(void){
    LD_HL(wcd2a);
    BIT_hl(0);
    RET_Z ;
    FARCALL(aCleanUpBattleRAM);
    FARCALL(aLoadPokemonData);
    RET;

}

void Function1002dc(void){
    LD_A(MAPSETUP_LINKRETURN);
    LDH_addr_A(hMapEntryMethod);
    FARCALL(aRunMapSetupScript);
    XOR_A_A;
    LDH_addr_A(hMapEntryMethod);
    CALL(aLoadStandardFont);
    RET;

}

void Function1002ed(void){
    FARCALL(aLoadOW_BGPal7);
    FARCALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    CALL(aDelayFrame);
    RET;

}

void Function100301(void){
    LD_HL(wcd2a);
    BIT_hl(1);
    RET_Z ;
    FARCALL(aFunction106464);
    FARCALL(aFunction10202c);
    FARCALL(aFunction115dd3);
    CALL(aFunction100320);
    CALL(aJoyWaitAorB);
    RET;

}

void Function100320(void){
    FARCALL(aMobile_ReloadMapPart);
    RET;

}

void Function100327(void){
//  //  unreferenced
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    RET;

}

void Function10032e(void){
    CALL(aFunction10034d);
    LD_E_A;
    RET_NC ;
    LD_addr_A(wcd2b);
    RET;

}

void Function100337(void){
    CALL(aFunction10032e);
    RET_C ;
    LD_A_addr(wc821);
    BIT_A(4);
    IF_Z goto asm_100345;
    LD_A_E;
    AND_A_A;
    RET;


asm_100345:
    LD_A(0xf9);
    LD_E_A;
    LD_addr_A(wcd2b);
    SCF;
    RET;

}

void Function10034d(void){
    LD_A_addr(wc821);
    BIT_A(1);
    IF_NZ goto asm_10036a;
    BIT_A(2);
    IF_NZ goto asm_10037e;
    BIT_A(3);
    IF_NZ goto asm_100366;
    BIT_A(0);
    IF_NZ goto asm_100364;
    LD_A(0x01);
    AND_A_A;
    RET;


asm_100364:
    XOR_A_A;
    RET;


asm_100366:
    LD_A(0x02);
    AND_A_A;
    RET;


asm_10036a:
    LD_A(MOBILEAPI_00);
    CALL(aMobileAPI);
    LD_addr_A(wcd2c);
    LD_A_H;
    LD_addr_A(wcd2d);
    LD_A_L;
    LD_addr_A(wcd2e);
    LD_A(0xff);
    SCF;
    RET;


asm_10037e:
    LD_A(0xfe);
    SCF;
    RET;

}

void Function100382(void){
    LD_A_addr(wcd27);
    LD_HL(mJumptable_10044e);
    RST(aJumpTable);
    RET;

}

void Function10038a(void){
    LD_HL(wccb4);
    LD_A(MOBILEAPI_17);
    CALL(aMobileAPI);
    RET;

}

void Function100393(void){
    LD_HL(wcc60);
    LD_A(MOBILEAPI_1D);
    CALL(aMobileAPI);
    RET;

}

void Function10039c(void){
    LD_HL(wcc60);
    LD_DE(w3_d000);
    LD_BC(0x54);
    LD_A(0x03);
    CALL(aFarCopyWRAM);
    RET;

}

void Function1003ab(void){
//  //  unreferenced
    LD_HL(w3_d000);
    LD_DE(wcc60);
    LD_BC(0x54);
    LD_A(0x03);
    CALL(aFarCopyWRAM);
    RET;

}

void Function1003ba(void){
    LD_HL(wccb4);
    LD_DE(w3_d080);
    LD_BC(0x54);
    LD_A(0x03);
    CALL(aFarCopyWRAM);
    RET;

}

void Function1003c9(void){
    LD_HL(w3_d080);
    LD_DE(wccb4);
    LD_BC(0x54);
    LD_A(0x03);
    CALL(aFarCopyWRAM);
    RET;

}

void Function1003d8(void){
    LD_HL(wccb4);
    LD_A_hli;
    LD_C_A;
    LD_B(0);
    PUSH_HL;
    ADD_HL_BC;
    LD_A_addr(wBGMapPalBuffer);
    LD_hl_A;
    POP_HL;
    INC_BC;
    CALL(aFunction10043a);
    ADD_HL_BC;
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    LD_A_C;
    ADD_A(0x02);
    LD_addr_A(wccb4);
    RET;

}

void Function1003f5(void){
    LD_A_addr(wcc60);
    SUB_A(0x03);
    LD_addr_A(wcc60);
    LD_A_addr(wccb4);
    SUB_A(0x03);
    LD_addr_A(wccb4);
    RET;

}

void Function100406(void){
    LD_A_addr(wcc60);
    SUB_A(0x02);
    LD_C_A;
    LD_B(0);
    LD_HL(wcc61);
    CALL(aFunction10043a);
    ADD_HL_BC;
    LD_A_hli;
    CP_A_E;
    IF_NZ goto asm_100426;
    LD_A_hld;
    CP_A_D;
    IF_NZ goto asm_100426;
    DEC_HL;
    LD_A_addr(wBGMapPalBuffer);
    CP_A_hl;
    IF_NZ goto asm_10042d;
    XOR_A_A;
    RET;


asm_100426:
    LD_A(0xf4);
    LD_addr_A(wcd2b);
    goto asm_100432;


asm_10042d:
    LD_A(0xf3);
    LD_addr_A(wcd2b);


asm_100432:
    PUSH_HL;
    LD_HL(wcd7c);
    INC_hl;
    POP_HL;
    SCF;
    RET;

}

void Function10043a(void){
    PUSH_HL;
    PUSH_BC;
    LD_DE(0);

asm_10043f:
    LD_A_hli;
    ADD_A_E;
    LD_E_A;
    LD_A_D;
    ADC_A(0);
    LD_D_A;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto asm_10043f;
    POP_BC;
    POP_HL;
    RET;

}

void Jumptable_10044e(void){
    //dw ['Function10046a'];
    //dw ['Function10047c'];
    //dw ['Function100493'];
    //dw ['Function1004ba'];
    //dw ['Function1004f4'];
    //dw ['Function1004ce'];
    //dw ['Function1004de'];
    //dw ['Function1004a4'];
    //dw ['Function100495'];
    //dw ['Function1004ce'];
    //dw ['Function1004de'];
    //dw ['Function1004e9'];
    //dw ['Function1004f4'];
    //dw ['Function1004a4'];

    return Function10046a();
}

void Function10046a(void){
    LD_HL(wBGMapPalBuffer);
    INC_hl;
    CALL(aFunction1003d8);
    CALL(aFunction1003ba);
    LD_A_addr(wcd27);
    INC_A;
    LD_addr_A(wcd27);
    RET;

}

void Function10047c(void){
    CALL(aFunction100337);
    RET_C ;
    RET_Z ;
    CP_A(0x02);
    IF_Z goto asm_100487;
    goto asm_10048d;


asm_100487:
    LD_A(0x08);
    LD_addr_A(wcd27);
    RET;


asm_10048d:
    LD_A(0x02);
    LD_addr_A(wcd27);
    RET;

}

void Function100493(void){
    JR(masm_100497);

}

void Function100495(void){
    JR(masm_100497);

}

void asm_100497(void){
    CALL(aFunction100337);
    RET_C ;
    RET_Z ;
    LD_A_addr(wcd27);
    INC_A;
    LD_addr_A(wcd27);
    RET;

}

void Function1004a4(void){
    CALL(aFunction100406);
    IF_C goto asm_1004b8;
    CALL(aFunction1003c9);
    CALL(aFunction1003f5);
    LD_A_addr(wcd27);
    SET_A(7);
    LD_addr_A(wcd27);
    RET;


asm_1004b8:
    SCF;
    RET;

}

void Function1004ba(void){
    CALL(aFunction10038a);
    AND_A_A;
    IF_NZ goto asm_1004c8;
    LD_A_addr(wcd27);
    INC_A;
    LD_addr_A(wcd27);
    RET;


asm_1004c8:
    LD_A(0x08);
    LD_addr_A(wcd27);
    RET;

}

void Function1004ce(void){
    CALL(aFunction100337);
    RET_C ;
    RET_Z ;
    CP_A(0x02);
    RET_NZ ;
    LD_A_addr(wcd27);
    INC_A;
    LD_addr_A(wcd27);
    RET;

}

void Function1004de(void){
    CALL(aFunction100393);
    LD_A_addr(wcd27);
    INC_A;
    LD_addr_A(wcd27);
    RET;

}

void Function1004e9(void){
    CALL(aFunction10038a);
    LD_A_addr(wcd27);
    INC_A;
    LD_addr_A(wcd27);
    RET;

}

void Function1004f4(void){
    CALL(aFunction100337);
    RET_C ;
    RET_Z ;
    LD_A_addr(wcd27);
    INC_A;
    LD_addr_A(wcd27);
    CALL(aFunction10039c);
    RET;

}

void Function100504(void){
    PUSH_DE;
    CALL(aFunction3f20);
    CALL(aUpdateSprites);
    POP_DE;
    hlcoord(4, 2, wTilemap);
    CALL(aPlaceString);
    RET;

}

void Function100513(void){
    CALL(aFunction3f7c);
    CALL(aPlaceVerticalMenuItems);
    CALL(aInitVerticalMenuCursor);
    LD_HL(w2DMenuFlags1);
    SET_hl(7);
    RET;

}

void Function100522(void){
    LD_A_addr(wcd28);
    LD_HL(mJumptable_10052a);
    RST(aJumpTable);
    RET;

}

void Jumptable_10052a(void){
    //dw ['Function100534'];
    //dw ['Function100545'];
    //dw ['Function100545'];
    //dw ['Function100545'];
    //dw ['Function10054d'];

    return Function100534();
}

void Function100534(void){
    CALL(aFunction100513);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    LD_A_addr(wcd28);
    INC_A;
    LD_addr_A(wcd28);
    RET;

}

void Function100545(void){
    LD_A_addr(wcd28);
    INC_A;
    LD_addr_A(wcd28);
    RET;

}

void Function10054d(void){
    FARCALL(aMobileMenuJoypad);
    LD_A_C;
    LD_HL(wMenuJoypadFilter);
    AND_A_hl;
    RET_Z ;
    CALL(aMenuClickSound);
    BIT_A(0);
    IF_NZ goto asm_100565;
    BIT_A(1);
    IF_NZ goto asm_10056f;
    RET;


asm_100565:
    LD_A_addr(wcd28);
    SET_A(7);
    LD_addr_A(wcd28);
    AND_A_A;
    RET;


asm_10056f:
    LD_A_addr(wcd28);
    SET_A(7);
    LD_addr_A(wcd28);
    SCF;
    RET;

}

void Function100579(void){
    LD_A_addr(wcd26);
    LD_HL(mJumptable_100581);
    RST(aJumpTable);
    RET;

}

void Jumptable_100581(void){
    //dw ['Function100585'];
    //dw ['Function100597'];

    return Function100585();
}

void Function100585(void){
    LD_HL(mMenuHeader_1005b2);
    CALL(aLoadMenuHeader);
    LD_A(0);
    LD_addr_A(wcd28);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);

    return Function100597();
}

void Function100597(void){
    CALL(aFunction100522);
    LD_A_addr(wcd28);
    BIT_A(7);
    RET_Z ;
    IF_NC goto asm_1005a6;
    XOR_A_A;
    LD_addr_A(wMenuCursorY);


asm_1005a6:
    CALL(aExitMenu);
    LD_A_addr(wcd26);
    SET_A(7);
    LD_addr_A(wcd26);
    RET;

}

void MenuHeader_1005b2(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //db ['6', '14'];
    //db ['10', '19'];
    //dw ['MenuData_1005ba'];
    //db ['1'];  // default option

    return MenuData_1005ba();
}

void MenuData_1005ba(void){
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['2'];
    //db ['"はい@"'];
    //db ['"いいえ@"'];

    return Function1005c3();
}

void Function1005c3(void){
    LD_A_addr(wcd26);
    LD_HL(mJumptable_1005cb);
    RST(aJumpTable);
    RET;

}

void Jumptable_1005cb(void){
    //dw ['Function1005cf'];
    //dw ['Function1005e1'];

    return Function1005cf();
}

void Function1005cf(void){
    LD_HL(mMenuHeader_1005fc);
    CALL(aLoadMenuHeader);
    LD_A(0);
    LD_addr_A(wcd28);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);

    return Function1005e1();
}

void Function1005e1(void){
    CALL(aFunction100522);
    LD_A_addr(wcd28);
    BIT_A(7);
    RET_Z ;
    IF_NC goto asm_1005f0;
    XOR_A_A;
    LD_addr_A(wMenuCursorY);

asm_1005f0:
    CALL(aExitMenu);
    LD_A_addr(wcd26);
    SET_A(7);
    LD_addr_A(wcd26);
    RET;

}

void MenuHeader_1005fc(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //db ['6', '14'];
    //db ['10', '19'];
    //dw ['MenuData_100604'];
    //db ['1'];  // default option

    return MenuData_100604();
}

void MenuData_100604(void){
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['2'];
    //db ['"かける@"'];
    //db ['"まつ@"'];

    return Mobile_CommunicationStandby();
}

void Mobile_CommunicationStandby(void){
    hlcoord(3, 10, wTilemap);
    LD_B(1);
    LD_C(11);
    CALL(aFunction3eea);
    LD_DE(mMobile_CommunicationStandby_String);
    hlcoord(4, 11, wTilemap);
    CALL(aPlaceString);
    RET;


String:
    //db ['"つうしんたいきちゅう！@"'];

    return AdvanceMobileInactivityTimerAndCheckExpired();
}

void AdvanceMobileInactivityTimerAndCheckExpired(void){
    PUSH_BC;
    CALL(aIncrementMobileInactivityTimerByCFrames);
    POP_BC;
    LD_A_addr(wMobileInactivityTimerMinutes);
    CP_A_B;
    IF_NC goto timed_out;
    AND_A_A;
    RET;


timed_out:
    LD_A(0xfa);
    LD_addr_A(wcd2b);
    SCF;
    RET;

}

void StartMobileInactivityTimer(void){
    // XOR_A_A;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = 0;
    // LD_addr_A(wMobileInactivityTimerSeconds);
    wram->wMobileInactivityTimerSeconds = 0;
    // LD_addr_A(wMobileInactivityTimerFrames);
    wram->wMobileInactivityTimerFrames = 0;
    // RET;
}

void IncrementMobileInactivityTimerBy1Frame(void){
    LD_C(1);
    return IncrementMobileInactivityTimerByCFrames();
}

void IncrementMobileInactivityTimerByCFrames(void){
    LD_HL(wMobileInactivityTimerFrames);  // timer?
    LD_A_hl;
    ADD_A_C;
    CP_A(60);
    IF_C goto seconds;
    XOR_A_A;


seconds:
    LD_hld_A;
    RET_C ;
    LD_A_hl;
    INC_A;
    CP_A(60);
    IF_C goto minutes;
    XOR_A_A;


minutes:
    LD_hld_A;
    RET_C ;
    INC_hl;
    RET;

}

void Function100665(void){
    CALL(aUpdateTime);
    LD_HL(wcd36);
    LDH_A_addr(hHours);
    LD_hli_A;
    LDH_A_addr(hMinutes);
    LD_hli_A;
    LDH_A_addr(hSeconds);
    LD_hl_A;
    RET;

}

void Function100675(void){
    LD_HL(wcd2a);
    BIT_hl(2);
    SET_hl(2);
    RET_NZ ;
    CALL(aFunction1006d3);
    RET;

}

void Function100681(void){
    PUSH_HL;
    LD_HL(wcd2a);
    BIT_hl(2);
    LD_HL(wcd2a);
    SET_hl(2);
    POP_HL;
    IF_NZ goto asm_100694;
    PUSH_HL;
    CALL(aFunction1006d3);
    POP_HL;

asm_100694:
    LD_DE(wcd32);

    return Function100697();
}

void Function100697(void){
    LD_A_de;
    AND_A_A;
    IF_NZ goto asm_1006bb;
    INC_DE;
    PUSH_DE;
    CALL(aFunction100697_asm_1006b4);
    LD_DE(mString1006c2);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    POP_DE;
    INC_DE;
    CALL(aFunction100697_asm_1006b4);
    LD_DE(mString1006c6);
    CALL(aPlaceString);
    RET;


asm_1006b4:
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    CALL(aPrintNum);
    RET;


asm_1006bb:
    LD_DE(mString1006ca);
    CALL(aPlaceString);
    RET;

}

void String1006c2(void){
    //db ['"ふん\u3000@"'];
    return String1006c6();
}

void String1006c6(void){
    //db ['"びょう@"'];
    return String1006ca();
}

void String1006ca(void){
    //db ['"１じかんいじょう@"'];

    return Function1006d3();
}

void Function1006d3(void){
    CALL(aUpdateTime);
    LD_DE(wcd34);
    LD_HL(wcd38);

    return Function1006dc();
}

void Function1006dc(void){
    LD_A_hld;
    LD_C_A;
    LDH_A_addr(hSeconds);
    SUB_A_C;
    IF_NC goto asm_1006e5;
    ADD_A(0x3c);


asm_1006e5:
    LD_de_A;
    DEC_DE;
    LD_A_hld;
    LD_C_A;
    LDH_A_addr(hMinutes);
    SBC_A_C;
    IF_NC goto asm_1006f0;
    ADD_A(0x3c);


asm_1006f0:
    LD_de_A;
    DEC_DE;
    LD_A_hl;
    LD_C_A;
    LDH_A_addr(hHours);
    SBC_A_C;
    IF_NC goto asm_1006fb;
    ADD_A(MAX_HOUR);


asm_1006fb:
    LD_de_A;
    RET;

}

void MobileBattleResetTimer(void){
    LD_A(BANK(sMobileBattleTimer));
    LD_HL(sMobileBattleTimer);
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    CALL(aCloseSRAM);
    RET;

}

void MobileBattleFixTimer(void){
    // LD_A(BANK(sMobileBattleTimer));
    // LD_HL(sMobileBattleTimer);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileBattleTimer));
    // XOR_A_A;  // MOBILE_BATTLE_ALLOWED_SECONDS
    // LD_hli_A;
    gb_write(sMobileBattleTimer, MOBILE_BATTLE_ALLOWED_SECONDS);
    // LD_A(MOBILE_BATTLE_ALLOWED_MINUTES);
    // LD_hli_A;
    gb_write(sMobileBattleTimer + 1, MOBILE_BATTLE_ALLOWED_MINUTES);
    // XOR_A_A;
    // LD_hli_A;
    gb_write(sMobileBattleTimer + 2, 0);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void Function100720(void){
    XOR_A_A;
    LD_addr_A(wcd6a);
    CALL(aUpdateTime);
    LDH_A_addr(hHours);
    LD_addr_A(wcd72);
    LDH_A_addr(hMinutes);
    LD_addr_A(wcd73);
    LDH_A_addr(hSeconds);
    LD_addr_A(wcd74);
    LD_A(BANK(sMobileBattleTimer));
    LD_HL(sMobileBattleTimer);
    CALL(aOpenSRAM);
    LD_A_hli;
    LD_addr_A(wcd6c);
    LD_A_hli;
    LD_addr_A(wcd6d);
    LD_A_hli;
    LD_addr_A(wcd6e);
    CALL(aCloseSRAM);
    LD_A_addr(wcd6d);
    LD_addr_A(wcd6b);
    RET;

}

void Function100754(void){
    CALL(aUpdateTime);
    LDH_A_addr(hHours);
    LD_addr_A(wcd72);
    LDH_A_addr(hMinutes);
    LD_addr_A(wcd73);
    LDH_A_addr(hSeconds);
    LD_addr_A(wcd74);
    LD_A_addr(wcd6d);
    LD_addr_A(wcd6b);
    LD_HL(wcd2a);
    RES_hl(6);
    RET;

}

void Function100772(void){
    PUSH_DE;
    LD_HL(wcd6c);
    LD_A_de;
    CP_A_hl;
    IF_C goto asm_10079a;
    IF_NZ goto asm_10078c;
    INC_HL;
    INC_DE;
    LD_A_de;
    CP_A_hl;
    IF_C goto asm_10079a;
    IF_NZ goto asm_10078c;
    INC_HL;
    INC_DE;
    LD_A_de;
    CP_A_hl;
    IF_C goto asm_10079a;
    IF_Z goto asm_10079a;


asm_10078c:
    POP_HL;
    LD_A_hli;
    LD_addr_A(wcd6c);
    LD_A_hli;
    LD_addr_A(wcd6d);
    LD_A_hli;
    LD_addr_A(wcd6e);
    RET;


asm_10079a:
    POP_DE;
    RET;

}

void Function10079c(void){
    LD_A_addr(wcd21);
    CP_A(0x01);
    IF_NZ goto dont_quit;
    LD_HL(wcd2a);
    BIT_hl(5);
    IF_NZ goto dont_quit;
    LD_HL(wcd2a);
    BIT_hl(6);
    IF_NZ goto dont_quit;
    LD_A_addr(wcd6a);
    ADD_A_C;
    CP_A(60);
    IF_NC goto overflow;
    LD_addr_A(wcd6a);
    AND_A_A;
    RET;


overflow:
    SUB_A(60);
    LD_addr_A(wcd6a);
    LD_D_B;
    PUSH_DE;
    CALL(aFunction1007f6);
    POP_DE;
    IF_C goto quit;
    LD_A_C;
    AND_A_A;
    IF_NZ goto quit;
    LD_A_B;
    CP_A(10);
    IF_NC goto quit;
    LD_A_D;
    AND_A_A;
    RET_Z ;
    LD_A_addr(wcd6b);
    CP_A_B;
    RET_Z ;
    LD_A_B;
    LD_addr_A(wcd6b);
    CALL(aFunction1008e0);
    AND_A_A;
    RET;


quit:
    CALL(aFunction1008e0);
    LD_HL(wcd2a);
    SET_hl(4);
    LD_A(0xfc);
    LD_addr_A(wcd2b);
    SCF;
    RET;


dont_quit:
    AND_A_A;
    RET;

}

void Function1007f6(void){
    CALL(aUpdateTime);
    LD_HL(wcd74);
    LD_DE(wcd71);
    CALL(aFunction1006dc);
    LD_A(0x04);
    CALL(aOpenSRAM);
    LD_HL(0xa802);
    CALL(aFunction100826);
    CALL(aCloseSRAM);
    LD_HL(wcd6e);
    CALL(aFunction100826);
    LDH_A_addr(hHours);
    LD_addr_A(wcd72);
    LDH_A_addr(hMinutes);
    LD_addr_A(wcd73);
    LDH_A_addr(hSeconds);
    LD_addr_A(wcd74);
    RET;

}

void Function100826(void){
    LD_A_addr(wcd71);
    ADD_A_hl;
    SUB_A(0x3c);
    IF_NC goto asm_100830;
    ADD_A(0x3c);


asm_100830:
    LD_hld_A;
    CCF;
    LD_A_addr(wcd70);
    ADC_A_hl;
    SUB_A(0x3c);
    IF_NC goto asm_10083c;
    ADD_A(0x3c);


asm_10083c:
    LD_hld_A;
    LD_B_A;
    CCF;
    LD_A_addr(wcd6f);
    ADC_A_hl;
    LD_hl_A;
    LD_C_A;
    RET;

}

void Function100846(void){
    LD_HL(wcd2a);
    BIT_hl(5);
    IF_NZ goto asm_10087c;
    LD_A_addr(wcd6e);
    LD_C_A;
    LD_A(0);
    SUB_A_C;
    IF_NC goto asm_100858;
    ADD_A(0x3c);


asm_100858:
    LD_addr_A(wStringBuffer2 + 2);
    LD_A_addr(wcd6d);
    LD_C_A;
    LD_A(0x0a);
    SBC_A_C;
    LD_addr_A(wStringBuffer2 + 1);
    XOR_A_A;
    LD_addr_A(wStringBuffer2);
    LD_DE(mString_10088e);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    LD_DE(wStringBuffer2);
    hlcoord(4, 16, wTilemap);
    CALL(aFunction100697);
    RET;


asm_10087c:
    LD_DE(mString_10088e);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(mString_10089f);
    CALL(aPlaceString);
    RET;

}

void String_10088e(void){
    //db ['"モバイルたいせん\u3000できる"'];
    //next ['"じかん@"']

    return String_10089f();
}

void String_10089f(void){
    //db ['"\u3000むせいげん@"'];
}

//  Calculates the difference between 10 minutes and sMobileBattleTimer
//  Returns minutes in c and seconds in b
u8_pair_s MobileBattleGetRemainingTime(void){
    // LD_A(BANK(sMobileBattleTimer));
    // LD_HL(sMobileBattleTimer);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileBattleTimer));
    // LD_A_hli;
    // LD_addr_A(wStringBuffer2);
    // LD_A_hli;
    // LD_addr_A(wStringBuffer2 + 1);
    // LD_A_hli;
    // LD_addr_A(wStringBuffer2 + 2);
    CopyBytes_Conv2(wram->wStringBuffer2, GBToRAMAddr(sMobileBattleTimer), 3);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A_addr(wStringBuffer2 + 2);
    // LD_B_A;
    uint8_t b = wram->wStringBuffer2[2];
    uint8_t carry = 0;
    // LD_A(MOBILE_BATTLE_ALLOWED_SECONDS);
    // SUB_A_B;
    // IF_NC goto no_carry_seconds;
    if(MOBILE_BATTLE_ALLOWED_SECONDS < b){
        // ADD_A(60);
        b = (MOBILE_BATTLE_ALLOWED_SECONDS - b) + 60;
        carry = 1;
    }
    else {
        b = MOBILE_BATTLE_ALLOWED_SECONDS - b;
    }
// no_carry_seconds:
    // LD_B_A;
    // LD_A_addr(wStringBuffer2 + 1);
    // LD_C_A;
    uint8_t c = wram->wStringBuffer2[1];
    // LD_A(MOBILE_BATTLE_ALLOWED_MINUTES);
    // SBC_A_C;
    // LD_C_A;
    // IF_C goto fail;
    if(MOBILE_BATTLE_ALLOWED_MINUTES - carry >= c){
        c = MOBILE_BATTLE_ALLOWED_MINUTES - carry - c;
        // LD_A_addr(wStringBuffer2);
        // AND_A_A;
        // IF_NZ goto fail;
        if(wram->wStringBuffer2[0] == 0){
            // RET;
            return u8_pair(b, c);
        }
    }

// fail:
    // CALL(aMobileBattleFixTimer);
    MobileBattleFixTimer();
    // LD_C(0);
    // RET;
    return u8_pair(b, 0);
}

void Function1008e0(void){
    LDH_A_addr(hBGMapMode);
    LD_B_A;
    LDH_A_addr(hVBlank);
    LD_C_A;
    PUSH_BC;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_A(0x03);
    LDH_addr_A(hVBlank);
    CALL(aFunction100970);
    CALL(aFunction100902);
    CALL(aFunction100989);
    CALL(aDelayFrame);
    POP_BC;
    LD_A_C;
    LDH_addr_A(hVBlank);
    LD_A_B;
    LDH_addr_A(hBGMapMode);
    RET;

}

void Function100902(void){
    hlcoord(3, 10, wTilemap);
    LD_B(0x01);
    LD_C(0x0b);
    CALL(aTextbox);
    LD_A_addr(wcd6d);
    LD_C_A;
    LD_A(0x0a);
    SUB_A_C;
    LD_addr_A(wStringBuffer2);
    IF_Z goto asm_10093f;
    LD_DE(mFunction100902_string_100966);
    hlcoord(4, 11, wTilemap);
    CALL(aPlaceString);
    hlcoord(8, 11, wTilemap);
    LD_BC((1 << 8) | 2);
    LD_DE(wStringBuffer2);
    CALL(aPrintNum);
    LD_DE(SFX_TWO_PC_BEEPS);
    CALL(aPlaySFX);
    FARCALL(aReloadMapPart);
    LD_C(0x3c);
    CALL(aDelayFrames);
    RET;


asm_10093f:
    LD_DE(mFunction100902_string_10095a);
    hlcoord(4, 11, wTilemap);
    CALL(aPlaceString);
    LD_DE(SFX_4_NOTE_DITTY);
    CALL(aPlaySFX);
    FARCALL(aReloadMapPart);
    LD_C(120);
    CALL(aDelayFrames);
    RET;


string_10095a:
    //db ['"たいせん\u3000しゅうりょう@"'];

string_100966:
    //db ['"のこり\u3000\u3000\u3000ふん！@"'];

    return Function100970();
}

void Function100970(void){
    hlcoord(0, 0, wTilemap);
    LD_DE(w3_dc00);
    CALL(aFunction1009a5);
    hlcoord(0, 0, wAttrmap);
    LD_DE(w3_dd68);
    CALL(aFunction1009a5);
    CALL(aFunction1009d2);
    CALL(aFunction1009ae);
    RET;

}

void Function100989(void){
    LD_HL(w3_dc00);
    decoord(0, 0, wTilemap);
    CALL(aFunction1009a5);
    CALL(aFunction1009ae);
    FARCALL(aReloadMapPart);
    LD_HL(w3_dd68);
    decoord(0, 0, wAttrmap);
    CALL(aFunction1009a5);
    RET;

}

void Function1009a5(void){
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    LD_A(0x03);
    CALL(aFarCopyWRAM);
    RET;

}

void Function1009ae(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x03);
    LDH_addr_A(rSVBK);

    LD_HL(w3_d800);
    decoord(0, 0, wAttrmap);
    LD_C(SCREEN_WIDTH);
    LD_B(SCREEN_HEIGHT);

loop_row:
    PUSH_BC;

loop_col:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop_col;
    LD_BC(BG_MAP_WIDTH - SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto loop_row;

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function1009d2(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x03);
    LDH_addr_A(rSVBK);

    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(0x01);
    LDH_addr_A(rVBK);

    LD_HL(w3_d800);
    debgcoord(0, 0, vBGMap0);
    LD_BC((0x03 << 8) | 0x24);
    CALL(aGet2bpp);

    POP_AF;
    LDH_addr_A(rVBK);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function1009f3(void){
    LDH_A_addr(hJoyDown);
    AND_A(SELECT + A_BUTTON);
    CP_A(SELECT + A_BUTTON);
    IF_NZ goto select_a;
    LD_HL(wcd2a);
    SET_hl(4);
    LD_A(0xf8);
    LD_addr_A(wcd2b);
    SCF;
    RET;


select_a:
    XOR_A_A;
    RET;

}

static uint8_t v_LinkBattleSendReceiveAction_StageForSend(void){
    // LD_A_addr(wBattlePlayerAction);
    // AND_A_A;  // BATTLEPLAYERACTION_USEMOVE?
    // IF_NZ goto switch_;
    if(wram->wBattlePlayerAction == BATTLEPLAYERACTION_USEMOVE) {
        // LD_A_addr(wCurPlayerMove);
        // LD_B(BATTLEACTION_STRUGGLE);
        // CP_A(STRUGGLE);
        // IF_Z goto struggle;
        if(wram->wCurPlayerMove == STRUGGLE)
            return BATTLEACTION_STRUGGLE & 0x0f;
        // LD_B(BATTLEACTION_SKIPTURN);
        // CP_A(0xff);
        // IF_Z goto struggle;
        if(wram->wCurPlayerMove == 0xff)
            return BATTLEACTION_SKIPTURN & 0x0f;
        // LD_A_addr(wCurMoveNum);
        // goto use_move;
        return (wram->wCurMoveNum) & 0x0f;
    }
    else {
    // switch_:
        // LD_A_addr(wCurPartyMon);
        // ADD_A(BATTLEACTION_SWITCH1);
        // goto use_move;
        return (wram->wCurPartyMon + BATTLEACTION_SWITCH1) & 0x0f;
    }

// struggle:
    // LD_A_B;

// use_move:
    // AND_A(0x0f);
    // RET;
}

static void v_LinkBattleSendReceiveAction_MobileBattle_SendReceiveAction(void){
    CALL(aFunction100acf);
    CALL(aStartMobileInactivityTimer);
    LD_A(0);
    LD_addr_A(wcd27);

asm_100a92:
    CALL(aDelayFrame);
    CALL(aGetJoypad);
    FARCALL(aFunction100382);
    LD_C(0x01);
    LD_B(0x03);
    PUSH_BC;
    CALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    POP_BC;
    IF_C goto asm_100ac7;
    LD_B(0x01);
    CALL(aFunction10079c);
    IF_C goto asm_100ac7;
    CALL(aFunction1009f3);
    IF_C goto asm_100ac7;
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_100ac7;
    LD_A_addr(wcd27);
    BIT_A(7);
    IF_Z goto asm_100a92;
    CALL(aFunction100ae7);
    goto asm_100ace;


asm_100ac7:
    LD_A(0x0f);
    LD_addr_A(wd430);
    goto asm_100ace;


asm_100ace:
    RET;
}

static void v_LinkBattleSendReceiveAction_LinkBattle_SendReceiveAction(void){
    // LD_A_addr(wLinkBattleSentAction);
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = wram->wLinkBattleSentAction;
    // LD_A(0xff);
    // LD_addr_A(wOtherPlayerLinkAction);
    wram->wOtherPlayerLinkAction = 0xff;

    do {
    // waiting:
        // CALL(aLinkTransfer);
        LinkTransfer();
        // CALL(aDelayFrame);
        DelayFrame();
        // LD_A_addr(wOtherPlayerLinkAction);
        // INC_A;
        // IF_Z goto waiting;
    } while(wram->wOtherPlayerLinkAction == 0xff);

    // LD_B(10);
    uint8_t b = 10;

    do {
    // receive:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aLinkTransfer);
        LinkTransfer();
        // DEC_B;
        // IF_NZ goto receive;
    } while(--b != 0);

    // LD_B(10);
    b = 10;

    do {
    // acknowledge:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aLinkDataReceived);
        LinkDataReceived();
        // DEC_B;
        // IF_NZ goto acknowledge;
    } while(--b != 0);

    // LD_A_addr(wOtherPlayerLinkAction);
    // LD_addr_A(wBattleAction);
    wram->wBattleAction = wram->wOtherPlayerLinkAction;
    // RET;
}

void v_LinkBattleSendReceiveAction(void){
    // CALL(av_LinkBattleSendReceiveAction_StageForSend);
    // LD_addr_A(wLinkBattleSentAction);
    wram->wLinkBattleSentAction = v_LinkBattleSendReceiveAction_StageForSend();
    // FARCALL(aPlaceWaitingText);
    PlaceWaitingText();
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // IF_NZ goto not_mobile;
    if(wram->wLinkMode == LINK_MOBILE) {
        // CALL(av_LinkBattleSendReceiveAction_MobileBattle_SendReceiveAction);
        v_LinkBattleSendReceiveAction_MobileBattle_SendReceiveAction();
        // CALL(aFunction100da5);
        Function100da5();
        // FARCALL(aFinishBattleAnim);
        FinishBattleAnim();
        // goto done;
    }
    else {
    // not_mobile:
        // CALL(av_LinkBattleSendReceiveAction_LinkBattle_SendReceiveAction);
        v_LinkBattleSendReceiveAction_LinkBattle_SendReceiveAction();
    }

// done:
    // RET;
    return;

}

void Function100acf(void){
    LD_DE(mUnknown_100b0a);
    LD_HL(wccb5);
    LD_A_addr(wLinkBattleSentAction);
    LD_hli_A;
    LD_C(0x01);

asm_100adb:
    LD_A_de;
    INC_DE;
    LD_hli_A;
    INC_C;
    AND_A_A;
    IF_NZ goto asm_100adb;
    LD_A_C;
    LD_addr_A(wccb4);
    RET;

}

void Function100ae7(void){
    LD_DE(mUnknown_100b0a);
    LD_HL(wcc62);

asm_100aed:
    LD_A_de;
    INC_DE;
    AND_A_A;
    IF_Z goto asm_100af8;
    CP_A_hl;
    IF_NZ goto asm_100aff;
    INC_HL;
    goto asm_100aed;


asm_100af8:
    LD_A_addr(wcc61);
    LD_addr_A(wd430);
    RET;


asm_100aff:
    LD_A(0x0f);
    LD_addr_A(wd430);
    LD_A(0xf1);
    LD_addr_A(wcd2b);
    RET;
}

// pushc
// setcharmap ascii
const char Unknown_100b0a[] = "tetsuji";
// popc

void Mobile_LoadBattleMenu(void){
    CALL(aFunction100dd8);
    RET_C ;
    LD_HL(mBattleMenuHeader);
    LD_A(BANK(aBattleMenuHeader));
    LD_DE(mLoadMenuHeader);
    CALL(aFarCall_de);
    LD_A(BANK(aBattleMenuHeader));
    LD_addr_A(wMenuData_2DMenuItemStringsBank);
    LD_A_addr(wBattleMenuCursorPosition);
    LD_addr_A(wMenuCursorPosition);
    CALL(aFunction100e72);
    CALL(aFunction100b45);
    FARCALL(aInitPartyMenuBGPal7);
    CALL(aFunction100ed4);
    LD_A_addr(wMenuCursorPosition);
    LD_addr_A(wBattleMenuCursorPosition);
    CALL(aExitMenu);
    RET;

}

void Function100b45(void){
    CALL(aFunction100b7a);

loop:
    CALL(aMobile_SetOverworldDelay);
    FARCALL(aMobileMenuJoypad);
    PUSH_BC;
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    CALL(aFunction100e2d);
    POP_BC;
    IF_C goto asm_100b6b;
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    IF_Z goto loop;
    FARCALL(aMobile_GetMenuSelection);
    RET;


asm_100b6b:
    LD_A_addr(w2DMenuNumCols);
    LD_C_A;
    LD_A_addr(w2DMenuNumRows);
    CALL(aSimpleMultiply);
    LD_addr_A(wMenuCursorPosition);
    AND_A_A;
    RET;

}

void Function100b7a(void){
    LD_HL(mCopyMenuData);
    LD_A_addr(wMenuData_2DMenuItemStringsBank);
    RST(aFarCall);
    FARCALL(aDraw2DMenu);
    FARCALL(aMobileTextBorder);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    FARCALL(aInit2DMenuCursorPosition);
    LD_HL(w2DMenuFlags1);
    SET_hl(7);
    RET;

}

void Mobile_MoveSelectionScreen(void){
    XOR_A_A;
    LD_addr_A(wSwappingMove);
    FARCALL(aCheckPlayerHasUsableMoves);
    RET_Z ;
    CALL(aFunction100dd8);
    JP_C (mxor_a_dec_a);
    CALL(aFunction100e72);
    CALL(aMobile_MoveSelectionScreen_GetMoveSelection);
    PUSH_AF;
    FARCALL(aInitPartyMenuBGPal7);
    CALL(aFunction100ed4);
    POP_AF;
    RET;


GetMoveSelection:
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aMobile_MoveSelectionScreen_ListMoves);
    CALL(aFunction100c98);

master_loop:
    FARCALL(aMoveInfoBox);

loop:
    CALL(aMobile_SetOverworldDelay);
    FARCALL(aMobileMenuJoypad);
    PUSH_BC;
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    CALL(aFunction100e2d);
    POP_BC;
    IF_C goto b_button;
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    BIT_A(D_UP_F);
    JP_NZ (mMobile_MoveSelectionScreen_d_up);
    BIT_A(D_DOWN_F);
    JP_NZ (mMobile_MoveSelectionScreen_d_down);
    BIT_A(A_BUTTON_F);
    IF_NZ goto a_button;
    BIT_A(B_BUTTON_F);
    IF_NZ goto b_button;
    goto loop;


d_up:
    LD_A_addr(wMenuCursorY);
    AND_A_A;
    JP_NZ (mMobile_MoveSelectionScreen_master_loop);
    LD_A_addr(wNumMoves);
    INC_A;
    LD_addr_A(wMenuCursorY);
    JP(mMobile_MoveSelectionScreen_master_loop);


d_down:
    LD_A_addr(wMenuCursorY);
    LD_B_A;
    LD_A_addr(wNumMoves);
    INC_A;
    INC_A;
    CP_A_B;
    JP_NZ (mMobile_MoveSelectionScreen_master_loop);
    LD_A(0x01);
    LD_addr_A(wMenuCursorY);
    JP(mMobile_MoveSelectionScreen_master_loop);


b_button:
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_addr_A(wCurMoveNum);
    LD_A(0x01);
    AND_A_A;
    RET;


a_button:
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_addr_A(wCurMoveNum);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wBattleMonPP);
    ADD_HL_BC;
    LD_A_hl;
    AND_A(0x3f);
    IF_Z goto no_pp_left;
    LD_A_addr(wPlayerDisableCount);
    SWAP_A;
    AND_A(0x0f);
    DEC_A;
    CP_A_C;
    IF_Z goto move_disabled;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wBattleMonMoves);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurPlayerMove);
    XOR_A_A;
    RET;


move_disabled:
    LD_HL(mBattleText_TheMoveIsDisabled);
    goto print_text;


no_pp_left:
    LD_HL(mBattleText_TheresNoPPLeftForThisMove);


print_text:
    CALL(aStdBattleTextbox);
    CALL(aSafeLoadTempTilemapToTilemap);
    JP(mMobile_MoveSelectionScreen_GetMoveSelection);


ListMoves:
    hlcoord(0, 8, wTilemap);
    LD_B(8);
    LD_C(8);
    CALL(aTextbox);
    LD_HL(wBattleMonMoves);
    LD_DE(wListMoves_MoveIndicesBuffer);
    LD_BC(NUM_MOVES);
    CALL(aCopyBytes);
    LD_A(SCREEN_WIDTH * 2);
    LD_addr_A(wListMovesLineSpacing);
    hlcoord(2, 10, wTilemap);
    PREDEF(pListMoves);
    RET;

}

void Function100c98(void){
    LD_DE(mFunction100c98_data);
    CALL(aLoad2DMenuData);
    LD_A_addr(wNumMoves);
    INC_A;
    LD_addr_A(w2DMenuNumRows);
    LD_A_addr(wCurMoveNum);
    INC_A;
    LD_addr_A(wMenuCursorY);
    RET;


data:
    //db ['10', '1'];  // cursor start y, x
    //db ['-1', '1'];  // rows, columns
    //db ['0xa0', '0x00'];  // flags
    //dn ['2', '0'];  // cursor offsets
    //db ['D_UP | D_DOWN | A_BUTTON | B_BUTTON'];  // accepted buttons

    return Mobile_PartyMenuSelect();
}

void Mobile_PartyMenuSelect(void){
    CALL(aFunction100dd8);
    RET_C ;
    LD_HL(w2DMenuFlags1);
    SET_hl(7);
    RES_hl(6);

loop:
    CALL(aMobile_SetOverworldDelay);
    FARCALL(aMobileMenuJoypad);
    PUSH_BC;
    FARCALL(aPlaySpriteAnimations);
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    CALL(aMobileComms_CheckInactivityTimer);
    POP_BC;
    IF_C goto done;
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    IF_Z goto loop;
    CALL(aPlaceHollowCursor);
    LD_A_addr(wPartyCount);
    INC_A;
    LD_B_A;
    LD_A_addr(wMenuCursorY);
    CP_A_B;
    IF_Z goto done;
    LD_addr_A(wPartyMenuCursor);
    LDH_A_addr(hJoyLast);
    LD_B_A;
    BIT_B(1);
    IF_NZ goto done;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    LD_C_A;
    LD_B(0);
    LD_HL(wPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurPartySpecies);
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    AND_A_A;
    RET;


done:
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    SCF;
    RET;

}

void MobileBattleMonMenu(void){
    CALL(aFunction100dd8);
    RET_C ;
    CALL(aFunction100d67);
    LD_HL(w2DMenuFlags1);
    SET_hl(7);
    RES_hl(6);

asm_100d30:
    CALL(aMobile_SetOverworldDelay);
    FARCALL(aMobileMenuJoypad);
    PUSH_BC;
    FARCALL(aPlaySpriteAnimations);
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    CALL(aMobileComms_CheckInactivityTimer);
    POP_BC;
    IF_C goto asm_100d54;
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    IF_NZ goto asm_100d56;
    goto asm_100d30;


asm_100d54:
    SCF;
    RET;


asm_100d56:
    PUSH_AF;
    LD_DE(SFX_READ_TEXT_2);
    CALL(aPlaySFX);
    POP_AF;
    BIT_A(1);
    IF_Z goto asm_100d65;
    RET_Z ;
    SCF;
    RET;


asm_100d65:
    AND_A_A;
    RET;

}

void Function100d67(void){
    LD_HL(mFunction100d67_MenuHeader);
    CALL(aCopyMenuHeader);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aMenuBox);
    CALL(aUpdateSprites);
    CALL(aPlaceVerticalMenuItems);
    CALL(aWaitBGMap);
    CALL(aCopyMenuData);
    CALL(aInitVerticalMenuCursor);
    LD_HL(w2DMenuFlags1);
    SET_hl(6);
    RET;


MenuHeader:
    //db ['0'];  // flags
    //menu_coords ['11', '11', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['.MenuData'];
    //db ['1'];  // default option


MenuData:
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['3'];
    //db ['"いれかえる@"'];  // TRADE
    //db ['"つよさをみる@"'];  // STATS
    //db ['"キャンセル@"'];  // CANCEL

    return Function100da5();
}

void Function100da5(void){
    // LD_HL(wcd2a);
    // RES_hl(3);
    bit_reset(wram->wcd2a, 3);
    // LD_HL(wcd29);
    // RES_hl(0);
    bit_reset(wram->wcd29, 0);
    // RET;
}

void Function100db0(void){
    LD_HL(wcd2a);
    BIT_hl(3);
    IF_NZ goto asm_100dbe;
    LD_HL(wcd2a);
    SET_hl(3);
    SCF;
    RET;


asm_100dbe:
    XOR_A_A;
    RET;

}

bool Function100dc0(void){
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_MOBILE);
    // IF_NZ goto mobile;
    // LD_HL(wcd2a);
    // BIT_hl(3);
    // IF_Z goto mobile;
    if(wram->wLinkMode == LINK_MOBILE && bit_test(wram->wcd2a, 3)) {
        // SCF;
        // RET;
        return true;
    }

// mobile:
    // XOR_A_A;
    // RET;
    return false;
}

void Mobile_SetOverworldDelay(void){
    // LD_A(30);
    // LD_addr_A(wOverworldDelay);
    wram->wOverworldDelay = 30;
    // RET;
}

void Function100dd8(void){
    LD_C(0x01);
    LD_B(0x03);
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    IF_C goto asm_100dfb;
    LD_C(0x3c);
    LD_B(0x01);
    CALL(aFunction10079c);
    IF_C goto asm_100dfb;
    FARCALL(aFunction10032e);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_100dfb;
    XOR_A_A;
    RET;


asm_100dfb:
    SCF;
    RET;

}

void MobileComms_CheckInactivityTimer(void){
    LD_A_addr(wOverworldDelay);
    LD_C_A;
    LD_A(30);
    SUB_A_C;
    LD_C_A;
    LD_B(3);
    PUSH_BC;
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);  // useless to farcall
    POP_BC;
    IF_C goto quit;
    LD_B(1);
    CALL(aFunction10079c);
    IF_C goto quit;
    CALL(aFunction1009f3);
    IF_C goto quit;
    FARCALL(aFunction10032e);  // useless to farcall
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto quit;
    XOR_A_A;
    RET;


quit:
    SCF;
    RET;

}

void Function100e2d(void){
    LD_A_addr(wOverworldDelay);
    LD_C_A;
    LD_A(30);
    SUB_A_C;
    LD_C_A;
    LD_B(3);
    PUSH_BC;
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    POP_BC;
    IF_C goto asm_100e61;
    LD_B(1);
    CALL(aFunction10079c);
    IF_C goto asm_100e61;
    CALL(aFunction1009f3);
    IF_C goto asm_100e61;
    FARCALL(aFunction10032e);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_100e61;
    CALL(aFunction100e63);
    CALL(aFunction100e84);
    XOR_A_A;
    RET;


asm_100e61:
    SCF;
    RET;

}

void Function100e63(void){
    LD_A_E;
    CP_A(0x02);
    RET_NZ ;
    CALL(aFunction100db0);
    RET_NC ;
    LD_DE(SFX_ELEVATOR_END);
    CALL(aPlaySFX);
    RET;

}

void Function100e72(void){
    XOR_A_A;
    LD_HL(wcd29);
    BIT_hl(0);
    IF_Z goto asm_100e7c;
    LD_A(0x0a);


asm_100e7c:
    LD_addr_A(wcd67);
    XOR_A_A;
    LD_addr_A(wcd68);
    RET;

}

void Function100e84(void){
    LD_A_addr(wcd67);
    LD_HL(mJumptable_100e8c);
    RST(aJumpTable);
    RET;

}

void Jumptable_100e8c(void){
    //dw ['Function100ea2'];
    //dw ['Function100eae'];
    //dw ['Function100eb4'];
    //dw ['Function100eae'];
    //dw ['Function100eb4'];
    //dw ['Function100eae'];
    //dw ['Function100eb4'];
    //dw ['Function100eae'];
    //dw ['Function100eb4'];
    //dw ['Function100eae'];
    //dw ['Function100ec4'];

    return Function100ea2();
}

void Function100ea2(void){
    CALL(aFunction100dc0);
    RET_NC ;
    LD_HL(wcd29);
    SET_hl(0);
    CALL(aFunction100ec5);

    return Function100eae();
}

void Function100eae(void){
    SCF;
    CALL(aFunction100eca);
    JR(masm_100eb8);

}

void Function100eb4(void){
    AND_A_A;
    CALL(aFunction100eca);

    return asm_100eb8();
}

void asm_100eb8(void){
    LD_HL(wcd68);
    INC_hl;
    LD_A_hl;
    CP_A(0x02);
    RET_C ;
    LD_hl(0);
    JR(mFunction100ec5);

}

void Function100ec4(void){
    RET;

}

void Function100ec5(void){
    LD_HL(wcd67);
    INC_hl;
    RET;

}

void Function100eca(void){
    FARCALL(aMobile_InitPartyMenuBGPal7);
    CALL(aFunction100ed4);
    RET;

}

void Function100ed4(void){
    FARCALL(aApplyPals);
    LD_A(TRUE);
    LDH_addr_A(hCGBPalUpdate);
    RET;

}

void Function100edf(void){
    LD_HL(mUnknown_100fc0);
    LD_C(1);
    JR(mFunction100f02);

}

void Function100ee6(void){
    LD_HL(mUnknown_100fc0);
    LD_C(2);
    JR(mFunction100f02);

}

void Function100eed(void){
    LD_HL(mUnknown_100feb);
    LD_C(1);
    JR(mFunction100f02);

}

void Function100ef4(void){
    LD_HL(mUnknown_100ff3);
    LD_C(1);
    JR(mFunction100f02);

}

void Function100efb(void){
//  //  unreferenced
    LD_HL(mUnknown_10102c);
    LD_C(1);
    JR(mFunction100f02);

}

void Function100f02(void){
    LD_A_C;
    LD_addr_A(wStringBuffer2);
// someting that was previously stored in de gets backed up to here
    LD_A_E;
    LD_addr_A(wStringBuffer2 + 1);
    LD_A_D;
    LD_addr_A(wStringBuffer2 + 2);
// empty this
    XOR_A_A;
    LD_addr_A(wStringBuffer2 + 4);
    LD_addr_A(wStringBuffer2 + 5);

loop:
    LD_A_hl;
    CP_A(0xff);
    IF_Z goto done;
    LD_addr_A(wStringBuffer2 + 3);  // bank
    PUSH_HL;
    INC_HL;
// addr 1
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
// size
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
// addr 2
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    CALL(aFunction100f3d);
// next line
    POP_HL;
    LD_DE(7);
    ADD_HL_DE;
    goto loop;


done:
// recover the values into bc
    LD_A_addr(wStringBuffer2 + 4);
    LD_C_A;
    LD_A_addr(wStringBuffer2 + 5);
    LD_B_A;
    RET;

}

void Function100f3d(void){
// parameter
    LD_A_addr(wStringBuffer2);
    CP_A(0x02);
    IF_Z goto two;
    CP_A(0x01);
    IF_Z goto one;
    CP_A(0x03);
    IF_Z goto three;
    RET;


three:
// what was once in de gets copied to hl,
// modified by Function100f8d, and put back
// into this backup
    LD_A_addr(wStringBuffer2 + 1);
    LD_L_A;
    LD_A_addr(wStringBuffer2 + 2);
    LD_H_A;
    CALL(aFunction100f8d);
    LD_A_L;
    LD_addr_A(wStringBuffer2 + 1);
    LD_A_H;
    LD_addr_A(wStringBuffer2 + 2);
    RET;


two:
// hl gets backed up to de, then
// do the same as in .three
    LD_D_H;
    LD_E_L;
    LD_A_addr(wStringBuffer2 + 1);
    LD_L_A;
    LD_A_addr(wStringBuffer2 + 2);
    LD_H_A;
    CALL(aFunction100f8d);
    LD_A_L;
    LD_addr_A(wStringBuffer2 + 1);
    LD_A_H;
    LD_addr_A(wStringBuffer2 + 2);
    RET;


one:
// de gets copied to hl, then
// load the backup into de,
// finally run Function100f8d
// and store the de result
    LD_H_D;
    LD_L_E;
    LD_A_addr(wStringBuffer2 + 1);
    LD_E_A;
    LD_A_addr(wStringBuffer2 + 2);
    LD_D_A;
    CALL(aFunction100f8d);
    LD_A_E;
    LD_addr_A(wStringBuffer2 + 1);
    LD_A_D;
    LD_addr_A(wStringBuffer2 + 2);
    RET;

}

void Function100f8d(void){
    PUSH_HL;
    LD_A_addr(wStringBuffer2 + 4);
    LD_L_A;
    LD_A_addr(wStringBuffer2 + 5);
    LD_H_A;
    ADD_HL_BC;
    LD_A_L;
    LD_addr_A(wStringBuffer2 + 4);
    LD_A_H;
    LD_addr_A(wStringBuffer2 + 5);
    POP_HL;
    LD_A_addr(wStringBuffer2 + 3);
    BIT_A(7);
    RES_A(7);
    IF_Z goto sram;
    AND_A_A;
    IF_NZ goto far_wram;
    CALL(aCopyBytes);
    RET;


far_wram:
    AND_A(0x7f);
    CALL(aFarCopyWRAM);
    RET;


sram:
    CALL(aOpenSRAM);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

// macro_100fc0: MACRO
//     ; first byte:
//     ;     Bit 7 set: Not SRAM
//     ;     Lower 7 bits: Bank if SRAM
//     ; address, size[, OT address]
//     db ($80 * (\1 >= SRAM_End)) | (BANK(\1) * (\1 < SRAM_End))
//     dw \1, \2
//     if _NARG == 3
//         dw \3
//     else
//         dw NULL
//     endc
// ENDM

}

void Unknown_100fc0(void){
    //macro_100fc0 ['wPlayerName', 'NAME_LENGTH', 'wOTPlayerName']
    //macro_100fc0 ['wPartyCount', '1 + PARTY_LENGTH + 1', 'wOTPartyCount']
    //macro_100fc0 ['wPlayerID', '2', 'wOTPlayerID']
    //macro_100fc0 ['wPartyMons', 'PARTYMON_STRUCT_LENGTH * PARTY_LENGTH', 'wOTPartyMons']
    //macro_100fc0 ['wPartyMonOTs', 'NAME_LENGTH * PARTY_LENGTH', 'wOTPartyMonOTs']
    //macro_100fc0 ['wPartyMonNicknames', 'MON_NAME_LENGTH * PARTY_LENGTH', 'wOTPartyMonNicknames']
    //db ['-1'];  // end

    return Unknown_100feb();
}

void Unknown_100feb(void){
    //macro_100fc0 ['sPartyMail', 'MAIL_STRUCT_LENGTH * PARTY_LENGTH']
    //db ['-1'];  // end

    return Unknown_100ff3();
}

void Unknown_100ff3(void){
    //macro_100fc0 ['wdc41', '1']
    //macro_100fc0 ['wPlayerName', 'NAME_LENGTH']
    //macro_100fc0 ['wPlayerName', 'NAME_LENGTH']
    //macro_100fc0 ['wPlayerID', '2']
    //macro_100fc0 ['wSecretID', '2']
    //macro_100fc0 ['wPlayerGender', '1']
    //macro_100fc0 ['s4_a603', '8']
    //macro_100fc0 ['s4_a007', 'PARTYMON_STRUCT_LENGTH']
    //db ['-1'];  // end

    return Unknown_10102c();
}

void Unknown_10102c(void){
    //macro_100fc0 ['wOTPlayerName', 'NAME_LENGTH']
    //macro_100fc0 ['wOTPlayerID', '2']
    //macro_100fc0 ['wOTPartyMonNicknames', 'MON_NAME_LENGTH * PARTY_LENGTH']
    //macro_100fc0 ['wOTPartyMonOTs', 'NAME_LENGTH * PARTY_LENGTH']
    //macro_100fc0 ['wOTPartyMons', 'PARTYMON_STRUCT_LENGTH * PARTY_LENGTH']
    //db ['-1'];  // end

    return Function101050();
}

void Function101050(void){
    CALL(aFunction10107d);
    LD_A_addr(wOTPartyCount);
    for(int rept = 0; rept < 2; rept++){  //  ???
    LD_HL(wc608);
    }
    LD_BC(wc7bb - wc608);
    CALL(aFunction1010de);
    LD_HL(wc7bb);
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    LD_A(0x07);
    CALL(aOpenSRAM);
    LD_HL(wc608);
    LD_DE(0xa001);
    LD_BC(wc7bd - wc608);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void Function10107d(void){
    XOR_A_A;
    LD_HL(wc608);
    LD_BC(wc7bd - wc608);
    CALL(aByteFill);
    LD_HL(wOTPlayerName);
    LD_DE(wc608);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_HL(wd271);
    LD_A_hli;
    LD_addr_A(wc608 + 11);
    LD_A_hl;
    LD_addr_A(wc608 + 12);
    LD_HL(wOTPartyMonNicknames);
    LD_DE(wc608 + 13);
    LD_BC(NAME_LENGTH);
    CALL(aFunction10107d_CopyAllFromOT);
    LD_HL(wOTPartyMonOTs);
    LD_DE(wOTClassName + 1);
    LD_BC(NAME_LENGTH);
    CALL(aFunction10107d_CopyAllFromOT);
    LD_HL(wOTPartyMon1Species);
    LD_DE(0xc699);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aFunction10107d_CopyAllFromOT);
    LD_A(0x50);
    LD_addr_A(wc7b9);
    LD_A(0x33);
    LD_addr_A(wc7ba);
    RET;


CopyAllFromOT:
    PUSH_HL;
    LD_HL(0);
    LD_A_addr(wOTPartyCount);
    CALL(aAddNTimes);
    LD_B_H;
    LD_C_L;
    POP_HL;
    CALL(aCopyBytes);
    RET;

}

void Function1010de(void){
    PUSH_HL;
    PUSH_BC;
    LD_DE(0);

loop:
    LD_A_hli;
    ADD_A_E;
    LD_E_A;
    LD_A_D;
    ADC_A(0);
    LD_D_A;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    POP_BC;
    POP_HL;
    RET;

}

void LoadSelectedPartiesForColosseum(void){
    XOR_A_A;
    LD_HL(wStringBuffer2);
    LD_BC(9);
    CALL(aByteFill);
    LD_HL(wPlayerMonSelection);
    LD_DE(wPartyCount);
    CALL(aLoadSelectedPartiesForColosseum_CopyThreeSpecies);
    LD_HL(wPlayerMonSelection);
    LD_DE(wPartyMon1Species);
    CALL(aLoadSelectedPartiesForColosseum_CopyPartyStruct);
    LD_HL(wPlayerMonSelection);
    LD_DE(wPartyMonOTs);
    CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LD_HL(wPlayerMonSelection);
    LD_DE(wPartyMonNicknames);
    CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LD_HL(wOTMonSelection);
    LD_DE(wOTPartyCount);
    CALL(aLoadSelectedPartiesForColosseum_CopyThreeSpecies);
    LD_HL(wOTMonSelection);
    LD_DE(wOTPartyMon1Species);
    CALL(aLoadSelectedPartiesForColosseum_CopyPartyStruct);
    LD_HL(wOTMonSelection);
    LD_DE(wOTPartyMonOTs);
    CALL(aLoadSelectedPartiesForColosseum_CopyName);
    LD_HL(wOTMonSelection);
    LD_DE(wOTPartyMonNicknames);
    CALL(aLoadSelectedPartiesForColosseum_CopyName);
    RET;


CopyThreeSpecies:
//  Load the 3 choices to the buffer
    PUSH_DE;
    LD_BC(wStringBuffer2 + NAME_LENGTH_JAPANESE);
    XOR_A_A;

party_loop:
    PUSH_AF;
    CALL(aLoadSelectedPartiesForColosseum_GetNthSpecies);
    LD_bc_A;
    INC_BC;
    POP_AF;
    INC_A;
    CP_A(3);
    IF_NZ goto party_loop;
    POP_DE;
//  Copy the 3 choices to the party
    LD_A(3);
    LD_de_A;
    INC_DE;
    LD_HL(wStringBuffer2 + NAME_LENGTH_JAPANESE);
    LD_BC(3);
    CALL(aCopyBytes);
    LD_A(0xff);
    LD_de_A;
    RET;


GetNthSpecies:
//  Preserves hl and de
//  Get the index of the Nth selection
    PUSH_HL;
    ADD_A_L;
    LD_L_A;
    LD_A_H;
    ADC_A(0);
    LD_H_A;
    LD_A_hl;
    POP_HL;
//  Get the corresponding species
    PUSH_DE;
    INC_DE;
    ADD_A_E;
    LD_E_A;
    LD_A_D;
    ADC_A(0);
    LD_D_A;
    LD_A_de;
    POP_DE;
    RET;


CopyPartyStruct:
    LD_BC(PARTYMON_STRUCT_LENGTH);
    goto ContinueCopy;


CopyName:
    LD_BC(NAME_LENGTH);


ContinueCopy:
// Copy, via wc608...
    LD_A(LOW(wc608));
    LD_addr_A(wStringBuffer2);
    LD_A(HIGH(wc608));
    LD_addr_A(wStringBuffer2 + 1);
// ... bc bytes...
    LD_A_C;
    LD_addr_A(wStringBuffer2 + 2);
    LD_A_B;
    LD_addr_A(wStringBuffer2 + 3);
// ... to de...
    LD_A_E;
    LD_addr_A(wStringBuffer2 + 4);
    LD_A_D;
    LD_addr_A(wStringBuffer2 + 5);
// ... 3 times.
    LD_A(3);

big_copy_loop:
    PUSH_AF;
    LD_A_hli;
    PUSH_HL;
    PUSH_AF;
    CALL(aLoadSelectedPartiesForColosseum_GetDestinationAddress);
    CALL(aLoadSelectedPartiesForColosseum_GetCopySize);
    POP_AF;
    CALL(aAddNTimes);
    LD_A_addr(wStringBuffer2);
    LD_E_A;
    LD_A_addr(wStringBuffer2 + 1);
    LD_D_A;
    CALL(aCopyBytes);
    LD_A_E;
    LD_addr_A(wStringBuffer2);
    LD_A_D;
    LD_addr_A(wStringBuffer2 + 1);
    POP_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto big_copy_loop;
    CALL(aLoadSelectedPartiesForColosseum_GetCopySize);
    LD_A(3);
    LD_HL(0);
    CALL(aAddNTimes);
    LD_B_H;
    LD_C_L;
    CALL(aLoadSelectedPartiesForColosseum_GetDestinationAddress);
    LD_D_H;
    LD_E_L;
    LD_HL(wc608);
    CALL(aCopyBytes);
    RET;


GetDestinationAddress:
    LD_A_addr(wStringBuffer2 + 4);
    LD_L_A;
    LD_A_addr(wStringBuffer2 + 5);
    LD_H_A;
    RET;


GetCopySize:
    LD_A_addr(wStringBuffer2 + 2);
    LD_C_A;
    LD_A_addr(wStringBuffer2 + 3);
    LD_B_A;
    RET;

}

void Function1011f1(void){
    LD_A(BANK(s4_a60c));
    CALL(aOpenSRAM);
    LD_A_addr(s4_a60c);
    LD_addr_A(wdc41);
    CALL(aCloseSRAM);
    LD_HL(wdc41);
    RES_hl(4);
    LD_HL(wGameTimerPaused);
    BIT_hl(GAME_TIMER_MOBILE_F);
    IF_Z goto skip;
    LD_HL(wdc41);
    SET_hl(4);


skip:
    CALL(aFunction10209c);
    XOR_A_A;
    LD_addr_A(wdc5f);
    LD_addr_A(wdc60);
    LD_A(LINK_MOBILE);
    LD_addr_A(wLinkMode);
    RET;

}

// Mobile_EndLinkMode?
void Function101220(void){
    // XOR_A_A;
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = LINK_NULL;
    // RET;
}

// Mobile_DoConnectionForMobileBattle
void Function101225(void){
    LD_D(1);
    LD_E(BANK(aJumptable_101297));
    LD_BC(mJumptable_101297);
    CALL(aFunction100000);
    JR(mFunction10123d);

}

// Mobile_DoConnectionForMobileTrade
void Function101231(void){
    LD_D(2);
    LD_E(BANK(aJumptable_101297));
    LD_BC(mJumptable_101297);
    CALL(aFunction100000);
    JR(mFunction10123d);

}

void Function10123d(void){
    XOR_A_A;
    LD_addr_A(wScriptVar);
    LD_A_C;
    LD_HL(mJumptable_101247);
    RST(aJumpTable);
    RET;

}

void Jumptable_101247(void){
    //dw ['Function101251'];
    //dw ['Function10127d'];
    //dw ['Function10127c'];
    //dw ['Function10126c'];
    //dw ['Function101265'];

    return Function101251();
}

void Function101251(void){
    CALL(aUpdateSprites);
    CALL(aRefreshScreen);
    LD_HL(mClosingLinkText);
    CALL(aFunction1021e0);
    CALL(aFunction1020ea);
    RET_C ;
    CALL(aFunction102142);
    RET;

}

void Function101265(void){
    LD_HL(mLinkTerminatedText);
    CALL(aFunction1021e0);
    RET;

}

void Function10126c(void){
    CALL(aUpdateSprites);
    FARCALL(aScript_reloadmappart);
    LD_HL(mClosingLinkText);
    CALL(aFunction1021e0);
    RET;

}

void Function10127c(void){
    RET;

}

void Function10127d(void){
    RET;

}

void Function10127e(void){
    LD_A_addr(wdc5f);
    AND_A_A;
    IF_Z goto zero;
    CP_A(1);
    LD_C(0x27);
    IF_Z goto load;
    CP_A(2);
    LD_C(0x37);
    IF_Z goto load;

zero:
    LD_C(0);

load:
    LD_A_C;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Jumptable_101297(void){
    //dw ['Function101a97'];  // 00
    //dw ['Function101ab4'];  // 01
    //dw ['Function101475'];  // 02
    //dw ['Function101b0f'];  // 03
    //dw ['Function101438'];  // 04
    //dw ['Function101b2b'];  // 05
    //dw ['Function101b59'];  // 06
    //dw ['Function101475'];  // 07
    //dw ['Function101b70'];  // 08
    //dw ['Function101438'];  // 09
    //dw ['Function101b8f'];  // 0a
    //dw ['Function101d7b'];  // 0b
    //dw ['Function101d95'];  // 0c
    //dw ['Function101475'];  // 0d
    //dw ['Function101db2'];  // 0e
    //dw ['Function101e4f'];  // 0f
    //dw ['Function101475'];  // 10
    //dw ['Function101e64'];  // 11
    //dw ['Function101e4f'];  // 12
    //dw ['Function101475'];  // 13
    //dw ['Function101e64'];  // 14
    //dw ['Function101d95'];  // 15
    //dw ['Function101475'];  // 16
    //dw ['Function101db2'];  // 17
    //dw ['Function101dd0'];  // 18
    //dw ['Function101de3'];  // 19
    //dw ['Function101e39'];  // 1a
    //dw ['Function101e09'];  // 1b
    //dw ['Function101e4f'];  // 1c
    //dw ['Function101475'];  // 1d
    //dw ['Function101e64'];  // 1e
    //dw ['Function101d95'];  // 1f
    //dw ['Function101475'];  // 20
    //dw ['Function101db2'];  // 21
    //dw ['Function101e09'];  // 22
    //dw ['Function101e31'];  // 23
    //dw ['Function101bc8'];  // 24
    //dw ['Function101438'];  // 25
    //dw ['Function101be5'];  // 26
    //dw ['Function101ac6'];  // 27
    //dw ['Function101ab4'];  // 28
    //dw ['Function101475'];  // 29
    //dw ['Function101c11'];  // 2a
    //dw ['Function1014f4'];  // 2b
    //dw ['Function101cc8'];  // 2c
    //dw ['Function1014e2'];  // 2d
    //dw ['Function1014e2'];  // 2e
    //dw ['Function101d10'];  // 2f
    //dw ['Function101d2a'];  // 30
    //dw ['Function101d2a'];  // 31
    //dw ['Function101507'];  // 32
    //dw ['Function10156d'];  // 33
    //dw ['Function101557'];  // 34
    //dw ['Function10158a'];  // 35
    //dw ['Function101c42'];  // 36
    //dw ['Function101aed'];  // 37
    //dw ['Function101ab4'];  // 38
    //dw ['Function101475'];  // 39
    //dw ['Function101c2b'];  // 3a
    //dw ['Function1014f4'];  // 3b
    //dw ['Function101cdf'];  // 3c
    //dw ['Function1014e2'];  // 3d
    //dw ['Function1014e2'];  // 3e
    //dw ['Function101d1e'];  // 3f
    //dw ['Function101d2a'];  // 40
    //dw ['Function101d2a'];  // 41
    //dw ['Function101507'];  // 42
    //dw ['Function10156d'];  // 43
    //dw ['Function101544'];  // 44
    //dw ['Function10158a'];  // 45
    //dw ['Function101c42'];  // 46
    //dw ['Function101c50'];  // 47
    //dw ['Function1014ce'];  // 48
    //dw ['Function101cf6'];  // 49
    //dw ['Function101826'];  // 4a
    //dw ['Function1017e4'];  // 4b
    //dw ['Function1017f1'];  // 4c
    //dw ['Function1018a8'];  // 4d
    //dw ['Function1018d6'];  // 4e
    //dw ['Function1017e4'];  // 4f
    //dw ['Function1017f1'];  // 50
    //dw ['Function1018e1'];  // 51
    //dw ['Function1015df'];  // 52
    //dw ['Function10167d'];  // 53
    //dw ['Function10168a'];  // 54
    //dw ['Function10162a'];  // 55
    //dw ['Function1015be'];  // 56
    //dw ['Function10167d'];  // 57
    //dw ['Function10168a'];  // 58
    //dw ['Function10161f'];  // 59
    //dw ['Function10159d'];  // 5a
    //dw ['Function10167d'];  // 5b
    //dw ['Function10168a'];  // 5c
    //dw ['Function101600'];  // 5d
    //dw ['Function101d03'];  // 5e
    //dw ['Function101d6b'];  // 5f
    //dw ['Function10159d'];  // 60
    //dw ['Function1014ce'];  // 61
    //dw ['Function10168e'];  // 62
    //dw ['Function101600'];  // 63
    //dw ['Function101913'];  // 64
    //dw ['Function10194b'];  // 65
    //dw ['_SelectMonsForMobileBattle'];  // 66
    //dw ['Function1017e4'];  // 67
    //dw ['Function1017f5'];  // 68
    //dw ['_StartMobileBattle'];  // 69
    //dw ['Function101537'];  // 6a
    //dw ['Function101571'];  // 6b
    //dw ['Function101c92'];  // 6c
    //dw ['Function10152a'];  // 6d
    //dw ['Function101571'];  // 6e
    //dw ['Function101a4f'];  // 6f
    //dw ['Function101cbc'];  // 70
    //dw ['Function101c62'];  // 71
    //dw ['Function101537'];  // 72
    //dw ['Function101571'];  // 73
    //dw ['Function101c92'];  // 74
    //dw ['Function10152a'];  // 75
    //dw ['Function101571'];  // 76
    //dw ['Function101ca0'];  // 77
    //dw ['Function101475'];  // 78
    //dw ['Function101cbc'];  // 79

    return Function10138b();
}

void Function10138b(void){
    FARCALL(aFunction8adcc);
    LD_C(0);
    IF_C goto asm_101396;
    INC_C;


asm_101396:
    SLA_C;
    LD_A_addr(wcd2f);
    AND_A_A;
    IF_Z goto asm_10139f;
    INC_C;


asm_10139f:
    SLA_C;
    LD_A_addr(wcd21);
    CP_A(0x01);
    IF_Z goto asm_1013a9;
    INC_C;


asm_1013a9:
    RET;

}

void Function1013aa(void){
    CALL(aClearBGPalettes);
    CALL(aCall_ExitMenu);
    CALL(aReloadTilesetAndPalettes);
    FARCALL(aFunction106464);
    CALL(aUpdateSprites);
    CALL(aFinishExitMenu);
    RET;

}

void Function1013c0(void){
    FARCALL(aBlankScreen);
    FARCALL(aStubbed_Function106462);
    FARCALL(aFunction106464);
    CALL(aFinishExitMenu);
    RET;

}

void Function1013d6(void){
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    RET;

}

void Function1013dd(void){
    CALL(aCGBOnly_CopyTilemapAtOnce);
    RET;

}

void Function1013e1(void){
//  //  unreferenced
    PUSH_DE;
    INC_DE;
    LD_B_A;
    LD_C(0);

asm_1013e6:
    INC_C;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    AND_A_A;
    IF_Z goto asm_1013f1;
    DEC_B;
    IF_NZ goto asm_1013e6;
    SCF;


asm_1013f1:
    POP_DE;
    LD_A_C;
    LD_de_A;
    RET;

}

void Function1013f5(void){
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_C_A;

asm_1013f9:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto asm_1013f9;
    RET;

}

void Function101400(void){
//  //  unreferenced
    LD_A_de;
    INC_DE;
    CP_A_hl;
    JR_NZ (masm_101416);
    INC_HL;

    return Function101406();
}

void Function101406(void){
    LD_C_A;
    LD_B(0);

asm_101409:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    JR_NZ (masm_101416);
    INC_HL;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto asm_101409;
    AND_A_A;
    RET;

}

void asm_101416(void){
    SCF;
    RET;

}

void Function101418(void){
    CALL(aGetJoypad);
    LDH_A_addr(hJoyDown);
    AND_A(SELECT + A_BUTTON);
    CP_A(SELECT + A_BUTTON);
    IF_Z goto asm_101425;
    XOR_A_A;
    RET;


asm_101425:
    LD_A(0xf7);
    LD_addr_A(wcd2b);
    SCF;
    RET;

}

void Function10142c(void){
    LD_A(0x01);
    LD_addr_A(wc305);
    FARCALL(aFunction115e18);
    RET;

}

void Function101438(void){
    LD_HL(wcd29);
    SET_hl(6);
    LD_A_addr(wcd26);
    LD_HL(mJumptable_101457);
    RST(aJumpTable);
    LD_A_addr(wcd26);
    BIT_A(7);
    RET_Z ;
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Jumptable_101457(void){
    //dw ['Function10145b'];
    //dw ['Function101467'];

    return Function10145b();
}

void Function10145b(void){
    LD_A(0x3c);
    LD_addr_A(wcd42);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);

    return Function101467();
}

void Function101467(void){
    LD_HL(wcd42);
    DEC_hl;
    RET_NZ ;
    LD_A_addr(wcd26);
    SET_A(7);
    LD_addr_A(wcd26);
    RET;

}

void Function101475(void){
    LD_HL(wcd29);
    SET_hl(6);
    LD_A_addr(wcd26);
    LD_HL(mJumptable_101494);
    RST(aJumpTable);
    LD_A_addr(wcd26);
    BIT_A(7);
    RET_Z ;
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Jumptable_101494(void){
    //dw ['Function10149a'];
    //dw ['Function1014a6'];
    //dw ['Function1014b7'];

    return Function10149a();
}

void Function10149a(void){
    LD_A(0x28);
    LD_addr_A(wcd42);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);

    return Function1014a6();
}

void Function1014a6(void){
    LD_HL(wcd42);
    DEC_hl;
    RET_NZ ;
    LD_A(0x50);
    LD_addr_A(wcd42);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);

    return Function1014b7();
}

void Function1014b7(void){
    CALL(aGetJoypad);
    LDH_A_addr(hJoyPressed);
    AND_A(0x03);
    IF_NZ goto asm_1014c5;
    LD_HL(wcd42);
    DEC_hl;
    RET_NZ ;


asm_1014c5:
    LD_A_addr(wcd26);
    SET_A(7);
    LD_addr_A(wcd26);
    RET;

}

void Function1014ce(void){
    FARCALL(aFunction100720);
    FARCALL(aStartMobileInactivityTimer);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function1014e2(void){
    LD_HL(wcd29);
    SET_hl(6);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function1014f4(void){
    FARCALL(aEnableMobile);
    LD_HL(wcd29);
    SET_hl(6);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101507(void){
    LD_DE(wcd30);
    LD_HL(0x40);
    LD_BC(0x40);
    LD_A(MOBILEAPI_01);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10151d(void){
//  //  unreferenced
    LD_A(MOBILEAPI_1A);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10152a(void){
    LD_A(MOBILEAPI_1B);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101537(void){
    LD_A(MOBILEAPI_05);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101544(void){
    FARCALL(aStartMobileInactivityTimer);
    LD_A(MOBILEAPI_09);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101557(void){
    FARCALL(aStartMobileInactivityTimer);
    LD_HL(wcd53);
    LD_A(MOBILEAPI_04);
    CALL(aMobileAPI);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10156d(void){
    CALL(aFunction101418);
    RET_C ;

    return Function101571();
}

void Function101571(void){
    FARCALL(aFunction10032e);
    RET_C ;
    RET_Z ;
    LD_A_E;
    CP_A(0x01);
    IF_Z goto asm_101582;
    LD_addr_A(wcd2b);
    RET;


asm_101582:
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10158a(void){
    FARCALL(aIncrementMobileInactivityTimerBy1Frame);
    LD_A_addr(wMobileInactivityTimerMinutes);
    CP_A(0x0a);
    JR_C (mFunction10156d);
    LD_A(0xfb);
    LD_addr_A(wcd2b);
    RET;

}

void Function10159d(void){
    LD_DE(wc608);
    FARCALL(aFunction100edf);
    LD_DE(wc608);
    LD_A(0x05);
    LD_HL(w5_d800);
    CALL(aFunction10174c);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function1015be(void){
    LD_DE(wc608);
    FARCALL(aFunction100eed);
    LD_DE(wc608);
    LD_A(0x05);
    LD_HL(w5_d800);
    CALL(aFunction10174c);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function1015df(void){
    LD_DE(wc608);
    FARCALL(aFunction100ef4);
    LD_DE(wc608);
    LD_A(0x05);
    LD_HL(w5_d800);
    CALL(aFunction10174c);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101600(void){
    LD_HL(w5_d800);
    LD_DE(wc608);
    LD_BC(0x1e0);
    LD_A(0x05);
    CALL(aFarCopyWRAM);
    LD_DE(wc608);
    FARCALL(aFunction100ee6);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10161f(void){
    CALL(aFunction101649);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10162a(void){
    CALL(aFunction101663);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void MobileCopyTransferData(void){
    LD_DE(wMobileTransferData);
    LD_BC(0x1e0);
    CALL(aFarCopyWRAM);
    RET;

}

void MobileCopyTransferData2(void){
    LD_HL(wMobileTransferData);
    LD_BC(0x1e0);
    CALL(aFarCopyWRAM);
    RET;

}

void Function101649(void){
    LD_A(BANK(w5_d800));
    LD_HL(w5_d800);
    CALL(aMobileCopyTransferData);
    LD_A(BANK(w5_da00));
    LD_DE(w5_da00);
    CALL(aMobileCopyTransferData2);
    RET;

}

void Function10165a(void){
    LD_A(BANK(w5_da00));
    LD_HL(w5_da00);
    CALL(aMobileCopyTransferData);
    RET;

}

void Function101663(void){
    LD_A(BANK(w5_dc00));
    LD_HL(w5_d800);
    CALL(aMobileCopyTransferData);
    LD_A(BANK(w5_dc00));
    LD_DE(w5_dc00);
    CALL(aMobileCopyTransferData2);
    RET;

}

void Function101674(void){
//  //  unreferenced
    LD_A(BANK(w5_dc00));
    LD_HL(w5_dc00);
    CALL(aMobileCopyTransferData);
    RET;

}

void Function10167d(void){
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10168a(void){
    CALL(aFunction101418);
    RET_C ;

    return Function10168e();
}

void Function10168e(void){
    LD_B(0);
    LD_C(0x01);
    FARCALL(aFunction10079c);
    RET_C ;
    LD_C(0x01);
    LD_B(0x03);
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    RET_C ;
    LD_A_addr(wcd26);
    LD_HL(mJumptable_1016c3);
    RST(aJumpTable);
    LD_HL(wcd29);
    SET_hl(6);
    LD_A_addr(wcd26);
    BIT_A(7);
    RET_Z ;
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Jumptable_1016c3(void){
    //dw ['Function1016cf'];
    //dw ['Function1016de'];
    //dw ['Function1016f8'];
    //dw ['Function101705'];
    //dw ['Function101719'];
    //dw ['Function101724'];

    return Function1016cf();
}

void Function1016cf(void){
    LD_HL(wcd3a);
    INC_hl;
    CALL(aFunction10176f);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;

}

void Function1016de(void){
    CALL(aFunction10177b);
    IF_NC goto asm_1016eb;
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;


asm_1016eb:
    LD_A(0xff);
    LD_addr_A(wcd39);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;

}

void Function1016f8(void){
    LD_A(0);
    LD_addr_A(wcd27);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;

}

void Function101705(void){
    FARCALL(aFunction100382);
    LD_A_addr(wcd27);
    BIT_A(7);
    RET_Z ;
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;

}

void Function101719(void){
    CALL(aFunction1017c7);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);
    RET;

}

void Function101724(void){
    LD_A_addr(wcd39);
    CP_A(0xff);
    IF_Z goto asm_101731;
    LD_A(0);
    LD_addr_A(wcd26);
    RET;


asm_101731:
    LD_A_addr(wcd26);
    SET_A(7);
    LD_addr_A(wcd26);
    RET;

}

void Unknown_10173a(void){
    //db ['0x50'];

    return Function10173b();
}

void Function10173b(void){
    PUSH_BC;
    PUSH_AF;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_addr(mUnknown_10173a);
    LD_C_A;
    LD_B(0);
    POP_AF;
    CALL(aAddNTimes);
    POP_BC;
    RET;

}

void Function10174c(void){
    LD_addr_A(wcd3d);
    LD_A_L;
    LD_addr_A(wcd3e);
    LD_A_H;
    LD_addr_A(wcd3f);
    LD_A_E;
    LD_addr_A(wcd3b);
    LD_A_D;
    LD_addr_A(wBattleTowerRoomMenu2JumptableIndex);
    LD_A_C;
    LD_addr_A(wcd40);
    LD_A_B;
    LD_addr_A(wcd41);
    XOR_A_A;
    LD_addr_A(wcd39);
    LD_addr_A(wcd3a);
    RET;

}

void Function10176f(void){
    LD_HL(wccb4);
    LD_BC(0x54);
    LD_A(0x11);
    CALL(aByteFill);
    RET;

}

void Function10177b(void){
    LD_A_addr(mUnknown_10173a);
    LD_C_A;
    LD_B(0);
    LD_A_addr(wcd3a);
    LD_HL(0);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    LD_HL(wcd40);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_L;
    SUB_A_E;
    LD_L_A;
    LD_A_H;
    SBC_A_D;
    LD_H_A;
    IF_C goto asm_1017a0;
    ADD_HL_BC;
    CALL(aFunction1017b0);
    SCF;
    RET;


asm_1017a0:
    LD_A(0xff);
    LD_addr_A(wcd39);
    ADD_HL_BC;
    LD_A_H;
    OR_A_L;
    RET_Z ;
    LD_C_L;
    LD_B_H;
    CALL(aFunction1017b0);
    XOR_A_A;
    RET;

}

void Function1017b0(void){
    LD_A_C;
    LD_addr_A(wccb4);
    PUSH_BC;
    LD_A_addr(wcd3a);
    DEC_A;
    LD_HL(wcd3b);
    CALL(aFunction10173b);
    POP_BC;
    LD_DE(wccb5);
    CALL(aCopyBytes);
    RET;

}

void Function1017c7(void){
    LD_A_addr(wcc60);
    LD_C_A;
    LD_B(0);
    LD_A_addr(wcd3a);
    DEC_A;
    LD_HL(wcd3e);
    CALL(aFunction10173b);
    LD_E_L;
    LD_D_H;
    LD_HL(wcc61);
    LD_A_addr(wcd3d);
    CALL(aFarCopyWRAM);
    AND_A_A;
    RET;

}

void Function1017e4(void){
    LD_A(0);
    LD_addr_A(wcd27);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function1017f1(void){
    CALL(aFunction101418);
    RET_C ;

    return Function1017f5();
}

void Function1017f5(void){
    LD_B(0);
    LD_C(0x01);
    FARCALL(aFunction10079c);
    RET_C ;
    LD_C(0x01);
    LD_B(0x03);
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    RET_C ;
    FARCALL(aFunction100382);
    LD_A_addr(wcd27);
    BIT_A(7);
    IF_NZ goto next;
    LD_HL(wcd29);
    SET_hl(6);
    RET;


next:
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101826(void){
    LD_A_addr(wcd21);
    CP_A(0x02);
    IF_Z goto asm_101833;
    CP_A(0x01);
    IF_Z goto asm_101844;
    goto asm_101869;


asm_101833:
    LD_HL(mUnknown_10186f);
    LD_DE(wccb4);
    CALL(aFunction1013f5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101844:
    FARCALL(aFunction103654);
    LD_A_C;
    LD_HL(mUnknown_101882);
    CP_A(0x01);
    IF_Z goto asm_10185b;
    LD_HL(mUnknown_101895);
    CP_A(0x02);
    IF_Z goto asm_10185b;
    goto asm_101869;


asm_10185b:
    LD_DE(wccb4);
    CALL(aFunction1013f5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101869:
    LD_A(0xfe);
    LD_addr_A(wcd2b);
    RET;
}

// pushc
// setcharmap ascii
void Unknown_10186f(void){
    //db ['.end - @'];
    //db ['0x19', '0x73', '0x09', '0x13', '"trade_crystal"'];

// end    db:
// 0

    return Unknown_101882();
}

void Unknown_101882(void){
    //db ['.end - @'];
    //db ['0x19', '0x67', '0x10', '0x01', '"free__crystal"'];

// end    db:
// 0

    return Unknown_101895();
}

void Unknown_101895(void){
    //db ['.end - @'];
    //db ['0x19', '0x67', '0x10', '0x01', '"limit_crystal"'];

// end    db:
// 0

// popc

    return Function1018a8();
}

void Function1018a8(void){
    LD_HL(wccb5);
    LD_DE(wcc61);
    LD_A(0x04);
    CALL(aFunction101406);
    IF_C goto asm_1018d0;
    LD_HL(wccb9);
    LD_DE(wcc65);
    LD_A(0x06);
    CALL(aFunction101406);
    IF_C goto asm_1018ca;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_1018ca:
    LD_A(0xf6);
    LD_addr_A(wcd2b);
    RET;


asm_1018d0:
    LD_A(0xf5);
    LD_addr_A(wcd2b);
    RET;

}

void Function1018d6(void){
    CALL(aFunction1018ec);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function1018e1(void){
    CALL(aFunction1018fb);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function1018ec(void){
    LD_A(0x0a);
    LD_HL(wccb4);
    LD_hli_A;
    LD_C_A;

asm_1018f3:
    CALL(aRandom);
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_1018f3;
    RET;

}

void Function1018fb(void){
    LD_A_addr(wcd2f);
    AND_A_A;
    IF_Z goto asm_101906;
    LD_HL(wcc61);
    goto asm_101909;


asm_101906:
    LD_HL(wccb5);


asm_101909:
    LD_DE(wLinkBattleRNs);
    LD_BC(10);
    CALL(aCopyBytes);
    RET;

}

void Function101913(void){
    LD_HL(wcd2a);
    SET_hl(0);
    XOR_A_A;
    LD_addr_A(wc30d);
    LD_HL(wcd29);
    RES_hl(4);
    XOR_A_A;
    LD_addr_A(wc305);
    LD_HL(wcd29);
    RES_hl(7);
    LD_A(0x90);
    LDH_addr_A(hWY);
    LD_A_addr(wcd21);
    CP_A(0x01);
    IF_Z goto asm_10193f;
    CP_A(0x02);
    IF_Z goto asm_101945;
    LD_A(0x71);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_10193f:
    LD_A(0x66);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101945:
    LD_A(0x65);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function10194b(void){
    CALL(aDisableSpriteUpdates);
    CALL(aClearSprites);
    FARCALL(aFunction1021f9);
    LD_HL(wcd29);
    BIT_hl(3);
    IF_NZ goto asm_101967;
    CALL(aFunction1013c0);
    LD_A(0x71);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101967:
    LD_A(0x60);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void v_SelectMonsForMobileBattle(void){
    FARCALL(aBlankScreen);
    FARCALL(aMobile_CommunicationStandby);
    LD_HL(wcd29);
    SET_hl(5);
    LD_HL(wcd2a);
    SET_hl(6);
    LD_A(0x06);
    LD_addr_A(wccb4);
    LD_HL(wPlayerMonSelection);
    LD_DE(wccb5);
    LD_BC(3);
    CALL(aCopyBytes);
    LD_HL(wcd6c);
    LD_A_hli;
    LD_addr_A(wccb8);
    LD_A_hli;
    LD_addr_A(wccb9);
    LD_A_hl;
    LD_addr_A(wccba);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void v_StartMobileBattle(void){
    CALL(aCopyOtherPlayersBattleMonSelection);
    FARCALL(aFunction100754);
    XOR_A_A;
    LD_addr_A(wdc5f);
    LD_addr_A(wdc60);
    FARCALL(aBlankScreen);
    CALL(aSpeechTextbox);
    FARCALL(aFunction100846);
    LD_C(120);
    CALL(aDelayFrames);
    FARCALL(aClearTilemap);
    CALL(av_StartMobileBattle_CopyOTDetails);
    CALL(aStartMobileBattle);
    LD_A_addr(wcd2b);
    CP_A(0xfc);
    IF_NZ goto asm_1019e6;
    XOR_A_A;
    LD_addr_A(wcd2b);

asm_1019e6:
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


CopyOTDetails:
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(5);
    LDH_addr_A(rSVBK);

    LD_BC(w5_dc0d);
    LD_DE(w5_dc11);
    FARCALL(aGetMobileOTTrainerClass);

    POP_AF;
    LDH_addr_A(rSVBK);

    LD_A_C;
    LD_addr_A(wOtherTrainerClass);
    LD_HL(wOTPlayerName);
    LD_DE(wOTClassName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wcd2f);
    AND_A_A;
    LD_A(USING_INTERNAL_CLOCK);
    IF_Z goto got_link_player_number;
    LD_A(USING_EXTERNAL_CLOCK);

got_link_player_number:
    LDH_addr_A(hSerialConnectionStatus);
    RET;

}

void StartMobileBattle(void){
// force stereo and fast text speed
    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    AND_A((1 << STEREO));
    OR_A(1);  // 1 frame per character i.e. fast text
    LD_hl_A;
    LD_A(1);
    LD_addr_A(wDisableTextAcceleration);
    FARCALL(aBattleIntro);
    FARCALL(aDoBattle);
    FARCALL(aShowLinkBattleParticipantsAfterEnd);
    XOR_A_A;
    LD_addr_A(wDisableTextAcceleration);
    LD_A(CONNECTION_NOT_ESTABLISHED);
    LDH_addr_A(hSerialConnectionStatus);
    POP_AF;
    LD_addr_A(wOptions);
    RET;

}

void Function101a4f(void){
    LD_A(1);
    LD_addr_A(wDisableTextAcceleration);
    FARCALL(aDisplayLinkBattleResult);
    XOR_A_A;
    LD_addr_A(wDisableTextAcceleration);
    FARCALL(aCleanUpBattleRAM);
    FARCALL(aLoadPokemonData);
    CALL(aFunction1013c0);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void CopyOtherPlayersBattleMonSelection(void){
    LD_HL(wcc61);
    LD_DE(wOTMonSelection);
    LD_BC(3);
    CALL(aCopyBytes);
    LD_DE(wcc64);
    FARCALL(aFunction100772);
    FARCALL(aFunction101050);
    FARCALL(aLoadSelectedPartiesForColosseum);
    RET;

}

void Function101a97(void){
    FARCALL(aFunction115d99);
    LD_HL(wcd29);
    SET_hl(7);
    LD_C(0x02);
    CALL(aFunction10142c);
    LD_HL(wcd29);
    SET_hl(6);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101ab4(void){
    LD_E(0x01);
    CALL(aFunction101ee4);
    LD_HL(wcd29);
    SET_hl(5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101ac6(void){
    FARCALL(aFunction115d99);
    LD_HL(wcd29);
    SET_hl(7);
    LD_C(0x02);
    CALL(aFunction10142c);
    LD_HL(wcd29);
    SET_hl(6);
    XOR_A_A;
    LD_addr_A(wcd2f);
    LD_DE(wdc42);
    CALL(aFunction102068);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101aed(void){
    FARCALL(aFunction115d99);
    LD_HL(wcd29);
    SET_hl(7);
    LD_C(0x02);
    CALL(aFunction10142c);
    LD_HL(wcd29);
    SET_hl(6);
    LD_A(0x01);
    LD_addr_A(wcd2f);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101b0f(void){
    LD_C(0);
    CALL(aFunction10142c);
    LD_E(0x03);
    CALL(aFunction101ee4);
    LD_HL(wcd29);
    SET_hl(5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    LD_A(0);
    LD_addr_A(wcd26);
    RET;

}

void Function101b2b(void){
    FARCALL(aFunction100579);
    LD_HL(wcd29);
    SET_hl(2);
    LD_A_addr(wcd26);
    BIT_A(7);
    RET_Z ;
    CALL(aFunction1013dd);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMenuCursorY);
    CP_A(0x01);
    IF_Z goto asm_101b51;
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;


asm_101b51:
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101b59(void){
    LD_C(0x02);
    CALL(aFunction10142c);
    LD_E(0x02);
    CALL(aFunction101ee4);
    LD_HL(wcd29);
    SET_hl(5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101b70(void){
    LD_C(0x02);
    CALL(aFunction10142c);
    LD_E(0x04);
    CALL(aFunction101ee4);
    LD_HL(wcd29);
    SET_hl(5);
    CALL(aUpdateSprites);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    LD_A(0);
    LD_addr_A(wcd26);
    RET;

}

void Function101b8f(void){
    FARCALL(aFunction1005c3);
    LD_HL(wcd29);
    SET_hl(2);
    LD_A_addr(wcd26);
    BIT_A(7);
    RET_Z ;
    CALL(aFunction1013dd);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMenuCursorY);
    CP_A(0x01);
    IF_Z goto asm_101bbc;
    LD_A(0x01);
    LD_addr_A(wcd2f);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101bbc:
    XOR_A_A;
    LD_addr_A(wcd2f);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101bc8(void){
    LD_C(0x02);
    CALL(aFunction10142c);
    LD_E(0x08);
    CALL(aFunction101ee4);
    CALL(aFunction102048);
    CALL(aFunction1013dd);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101be5(void){
    FARCALL(aFunction100579);
    LD_HL(wcd29);
    SET_hl(2);
    LD_A_addr(wcd26);
    BIT_A(7);
    RET_Z ;
    CALL(aFunction1013dd);
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMenuCursorY);
    CP_A(0x01);
    IF_NZ goto asm_101c0b;
    LD_A(0x2a);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101c0b:
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

}

void Function101c11(void){
    LD_A(0x01);
    LD_addr_A(wdc5f);
    LD_E(0x09);
    CALL(aFunction101ee4);
    CALL(aFunction102048);
    LD_HL(wcd29);
    SET_hl(5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101c2b(void){
    LD_A(0x02);
    LD_addr_A(wdc5f);
    LD_E(0x07);
    CALL(aFunction101ee4);
    LD_HL(wcd29);
    SET_hl(5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101c42(void){
    LD_HL(wcd2a);
    SET_hl(1);
    CALL(aFunction100665);
    LD_A(0x47);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101c50(void){
    LD_E(0x0a);
    CALL(aFunction101ee4);
    LD_HL(wcd29);
    SET_hl(2);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101c62(void){
    FARCALL(aFunction115d99);
    LD_HL(wcd29);
    SET_hl(7);
    LD_C(0x01);
    CALL(aFunction10142c);
    XOR_A_A;
    LD_addr_A(wc30d);
    LD_HL(wcd29);
    RES_hl(4);
    LD_E(0x0b);
    CALL(aFunction101ee4);
    LD_HL(wcd29);
    SET_hl(5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    LD_A(0);
    LD_addr_A(wcd26);
    RET;

}

void Function101c92(void){
    FARCALL(aFunction100675);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101ca0(void){
    LD_C(0x02);
    CALL(aFunction10142c);
    LD_E(0x0c);
    CALL(aFunction101ee4);
    LD_HL(wcd29);
    SET_hl(5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    LD_A(0);
    LD_addr_A(wcd26);
    RET;

}

void Function101cbc(void){
    LD_A(0x01);
    LD_addr_A(wcd2b);
    RET;

}

void Function101cc2(void){
//  //  unreferenced
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

}

void Function101cc8(void){
    LD_A(0x01);
    LD_addr_A(wc314);
    LD_A(0x01);
    LD_addr_A(wc30d);
    LD_HL(wcd29);
    SET_hl(4);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101cdf(void){
    LD_A(0x06);
    LD_addr_A(wc314);
    LD_A(0x01);
    LD_addr_A(wc30d);
    LD_HL(wcd29);
    SET_hl(4);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101cf6(void){
    LD_A(0x0b);
    LD_addr_A(wc314 + 1);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101d03(void){
    LD_A(0x0e);
    LD_addr_A(wc314 + 1);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101d10(void){
    LD_C(0x01);
    CALL(aFunction10142c);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    JR(mFunction101d2a);

}

void Function101d1e(void){
    LD_C(0x03);
    CALL(aFunction10142c);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);

    return Function101d2a();
}

void Function101d2a(void){
    CALL(aFunction101418);
    RET_C ;
    LD_HL(wcd29);
    SET_hl(6);
    LD_A_addr(wcd26);
    LD_HL(mJumptable_101d4d);
    RST(aJumpTable);
    LD_A_addr(wcd26);
    BIT_A(7);
    RET_Z ;
    LD_A(0);
    LD_addr_A(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Jumptable_101d4d(void){
    //dw ['Function101d51'];
    //dw ['Function101d5d'];

    return Function101d51();
}

void Function101d51(void){
    LD_A(0x3c);
    LD_addr_A(wcd42);
    LD_A_addr(wcd26);
    INC_A;
    LD_addr_A(wcd26);

    return Function101d5d();
}

void Function101d5d(void){
    LD_HL(wcd42);
    DEC_hl;
    RET_NZ ;
    LD_A_addr(wcd26);
    SET_A(7);
    LD_addr_A(wcd26);
    RET;

}

void Function101d6b(void){
    LD_A_addr(wc30d);
    AND_A_A;
    RET_NZ ;
    LD_HL(wcd29);
    RES_hl(4);
    LD_A(0x64);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101d7b(void){
    FARCALL(aFunction10138b);
    LD_B(0);
    LD_HL(mUnknown_101d8d);
    ADD_HL_BC;
    LD_C_hl;
    LD_A_C;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Unknown_101d8d(void){
    //db ['0x15', '0x15', '0x1f', '0x1f', '0x0c', '0x12', '0x3a', '0x3a'];

    return Function101d95();
}

void Function101d95(void){
    CALL(aFunction101ee2);
    CALL(aLoadStandardMenuHeader);
    LD_E(0x0e);
    CALL(aFunction101ee4);
    LD_HL(wcd29);
    SET_hl(5);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    LD_A(0);
    LD_addr_A(wcd26);
    RET;

}

void Function101db2(void){
    FARCALL(aFunction103302);
    CALL(aExitMenu);
    LD_HL(wcd29);
    SET_hl(5);
    IF_C goto asm_101dca;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101dca:
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

}

void Function101dd0(void){
    LD_HL(wdc41);
    BIT_hl(1);
    IF_NZ goto asm_101ddd;
    LD_A(0x19);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101ddd:
    LD_A(0x1b);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101de3(void){
    CALL(aFunction101ecc);
    CALL(aFunction101ead);
    IF_C goto asm_101df3;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101df3:
    CALL(aFunction101e98);
    IF_C goto asm_101e00;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101e00:
    CALL(aFunction101ed3);
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

}

void Function101e09(void){
    CALL(aFunction101ead);
    IF_C goto asm_101e16;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101e16:
    CALL(aFunction101ecc);
    CALL(aFunction101e98);
    PUSH_AF;
    CALL(aFunction101ed3);
    POP_AF;
    IF_C goto asm_101e2b;
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101e2b:
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

}

void Function101e31(void){
    LD_A(0x3a);
    LD_addr_A(wMobileCommsJumptableIndex);
    JP(mFunction101c2b);

}

void Function101e39(void){
    CALL(aFunction1020bf);
    PUSH_AF;
    CALL(aFunction101ed3);
    POP_AF;
    IF_C goto asm_101e49;
    LD_A(0x2a);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101e49:
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

}

void Function101e4f(void){
    LD_E(0x06);
    CALL(aFunction101ee4);
    CALL(aFunction1013d6);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    LD_A(0);
    LD_addr_A(wcd26);
    RET;

}

void Function101e64(void){
    CALL(aFunction101ecc);
    CALL(aFunction1020a8);
    PUSH_AF;
    CALL(aFunction101ed3);
    POP_AF;
    IF_C goto asm_101e77;
    LD_A(0x24);
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;


asm_101e77:
    LD_HL(wcd29);
    SET_hl(5);
    LD_A(0x02);
    LD_addr_A(wcd2b);
    RET;

}

void Function101e82(void){
//  //  unreferenced
    CALL(aFunction101ecc);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101e8d(void){
//  //  unreferenced
    CALL(aFunction101ed3);
    LD_A_addr(wMobileCommsJumptableIndex);
    INC_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    RET;

}

void Function101e98(void){
    CALL(aClearSprites);
    FARCALL(aFunction8adb3);
    RET_C ;
    LD_HL(wGameTimerPaused);
    SET_hl(GAME_TIMER_MOBILE_F);
    LD_HL(wdc41);
    SET_hl(4);
    RET;

}

void Function101ead(void){
    LD_HL(wGameTimerPaused);
    BIT_hl(GAME_TIMER_MOBILE_F);
    IF_NZ goto asm_101ec8;
    LD_HL(wdc41);
    BIT_hl(2);
    IF_Z goto asm_101eca;
    LD_A_addr(wcd2f);
    AND_A_A;
    IF_NZ goto asm_101ec8;
    LD_HL(wdc41);
    BIT_hl(1);
    IF_Z goto asm_101eca;


asm_101ec8:
    XOR_A_A;
    RET;


asm_101eca:
    SCF;
    RET;

}

void Function101ecc(void){
    CALL(aFunction101ee2);
    CALL(aFadeToMenu);
    RET;

}

void Function101ed3(void){
    CALL(aFunction1013aa);
    FARCALL(aFunction115d99);
    LD_HL(wcd29);
    SET_hl(7);
    RET;

}

void Function101ee2(void){
    LD_E(0);

    return Function101ee4();
}

void Function101ee4(void){
    LD_D(0);
    LD_HL(mUnknown_101ef5);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    FARCALL(aFunction100504);
    RET;

}

void Unknown_101ef5(void){
    //dw ['String_101f13'];
    //dw ['String_101f14'];
    //dw ['String_101f32'];
    //dw ['String_101f4f'];
    //dw ['String_101f69'];
    //dw ['String_101f81'];
    //dw ['String_101f93'];
    //dw ['String_101faa'];
    //dw ['String_101fc5'];
    //dw ['String_101fd2'];
    //dw ['String_101fe1'];
    //dw ['String_101fef'];
    //dw ['String_102000'];
    //dw ['String_10200c'];
    //dw ['String_102014'];

    return String_101f13();
}

void String_101f13(void){
    //db ['"@"'];

    return String_101f14();
}

void String_101f14(void){
    //db ['"モバイルアダプタを\u3000つかって"'];
    //next ['"おともだちと\u3000つうしんします@"']

    return String_101f32();
}

void String_101f32(void){
    //db ['"でんわを\u3000かけるひとには"'];
    //next ['"つうわりょうきんが\u3000かかります@"']

    return String_101f4f();
}

void String_101f4f(void){
    //db ['"モバイルアダプタの\u3000じゅんびは"'];
    //next ['"できて\u3000いますか？@"']

    return String_101f69();
}

void String_101f69(void){
    //db ['"あなたが\u3000おともだちに"'];
    //next ['"でんわを\u3000かけますか？@"']

    return String_101f81();
}

void String_101f81(void){
    //db ['"めいしフォルダーを"'];
    //next ['"つかいますか？@"']

    return String_101f93();
}

void String_101f93(void){
    //db ['"でんわばんごうを\u3000にゅうりょく"'];
    //next ['"してください@"']

    return String_101faa();
}

void String_101faa(void){
    //db ['"それでは\u3000おともだちからの"'];
    //next ['"でんわを\u3000おまちします⋯@"']

    return String_101fc5();
}

void String_101fc5(void){
    //next ['"に\u3000でんわを\u3000かけます@"']

    return String_101fd2();
}

void String_101fd2(void){
    //next ['"に\u3000でんわを\u3000かけています@"']

    return String_101fe1();
}

void String_101fe1(void){
    //db ['"でんわが\u3000つながりました!@"'];

    return String_101fef();
}

void String_101fef(void){
    //db ['"つうわを"'];
    //next ['"しゅうりょう\u3000します⋯@"']

    return String_102000();
}

void String_102000(void){
    //db ['"つうしん\u3000しゅうりょう@"'];

    return String_10200c();
}

void String_10200c(void){
    //db ['"つうわ\u3000じかん@"'];

    return String_102014();
}

void String_102014(void){
    //db ['"それでは\u3000つうしんの"'];
    //next ['"せっていを\u3000してください@"']

    return Function10202c();
}

void Function10202c(void){
    FARCALL(aFunction115d99);
    LD_HL(wcd29);
    SET_hl(7);
    LD_C(0x02);
    CALL(aFunction10142c);
    LD_E(0x0d);
    CALL(aFunction101ee4);
    hlcoord(4, 4, wTilemap);
    CALL(aFunction100681);
    RET;

}

void Function102048(void){
    CALL(aFunction10204c);
    RET;

}

void Function10204c(void){
    hlcoord(3, 2, wTilemap);
    LD_C(0x10);
    LD_DE(wcd53);

asm_102054:
    LD_A_de;
    INC_DE;
    AND_A_A;
    IF_Z goto asm_102067;
    SUB_A(0x30);
    IF_C goto asm_102067;
    CP_A(0x0a);
    IF_NC goto asm_102067;
    ADD_A(0xf6);
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_102054;


asm_102067:
    RET;

}

void Function102068(void){
    LD_HL(wcd53);
    LD_C(0x08);

asm_10206d:
    LD_A_de;
    CALL(aFunction102080);
    IF_C goto asm_10207f;
    LD_A_de;
    SWAP_A;
    CALL(aFunction102080);
    IF_C goto asm_10207f;
    INC_DE;
    DEC_C;
    IF_NZ goto asm_10206d;


asm_10207f:
    RET;

}

void Function102080(void){
    AND_A(0x0f);
    CP_A(0x0f);
    IF_Z goto asm_10208a;
    ADD_A(0x30);
    LD_hli_A;
    RET;


asm_10208a:
    LD_hl(0);
    SCF;
    RET;

}

void Function10208e(void){
    PUSH_DE;
    LD_H_D;
    LD_L_E;
    LD_DE(wdc42);
    LD_BC(8);
    CALL(aCopyBytes);
    POP_DE;
    RET;

}

void Function10209c(void){
    LD_A(0xff);
    LD_HL(wdc42);
    LD_BC(8);
    CALL(aByteFill);
    RET;

}

void Function1020a8(void){
    CALL(aFunction10209c);
    LD_C(0x01);
    LD_DE(wdc42);
    FARCALL(aFunction17a68f);
    RET_C ;
    CALL(aFunction10208e);
    CALL(aFunction102068);
    XOR_A_A;
    RET;

}

void Function1020bf(void){
    CALL(aClearSprites);
    FARCALL(aFunction8aba9);
    LD_A_C;
    AND_A_A;
    IF_Z goto asm_1020e8;
    DEC_A;
    LD_HL(0xa04c);
    LD_BC(0x25);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    LD_A(0x04);
    CALL(aOpenSRAM);
    CALL(aFunction10208e);
    CALL(aFunction102068);
    CALL(aCloseSRAM);
    XOR_A_A;
    RET;


asm_1020e8:
    SCF;
    RET;

}

void Function1020ea(void){
    LD_HL(wdc41);
    BIT_hl(4);
    IF_Z goto quit;
    LD_HL(wdc41);
    BIT_hl(2);
    IF_NZ goto quit;
    CALL(aFunction10218d);
    LD_HL(wc608);
    BIT_hl(4);
    IF_Z goto quit;
    LD_HL(wc608);
    BIT_hl(2);
    IF_NZ goto quit;
    CALL(aFunction102112);
    IF_Z goto quit;
    AND_A_A;
    RET;


quit:
    SCF;
    RET;

}

void Function102112(void){
    LD_A(0x04);
    CALL(aOpenSRAM);
    LD_HL(0xa041);
    LD_C(40);

outer_loop:
    PUSH_HL;
    LD_DE(0xc60f);
    LD_B(31);

inner_loop:
    LD_A_de;
    CP_A_hl;
    IF_NZ goto not_matching;
    INC_DE;
    INC_HL;
    DEC_B;
    IF_NZ goto inner_loop;
    POP_HL;
    XOR_A_A;
    goto done;


not_matching:
    POP_HL;
    LD_DE(37);
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto outer_loop;
    LD_A(0x01);
    AND_A_A;
    goto done;  // useless jr


done:
    PUSH_AF;
    CALL(aCloseSRAM);
    POP_AF;
    RET;

}

void Function102142(void){
    CALL(aFunction10218d);
    CALL(aFunction102180);
    LD_HL(mNewCardArrivedText);
    CALL(aMenuTextbox);
    LD_DE(SFX_LEVEL_UP);
    CALL(aPlaySFX);
    CALL(aJoyWaitAorB);
    CALL(aExitMenu);
    CALL(aFunction10219f);
    LD_HL(mPutCardInCardFolderText);
    CALL(aMenuTextbox);
    CALL(aYesNoBox);
    CALL(aExitMenu);
    IF_C goto asm_10217c;
    CALL(aFunction1021b8);
    IF_C goto asm_10217c;
    CALL(aFunction10218d);
    CALL(aFunction102180);
    LD_HL(mCardWasListedText);
    CALL(aPrintText);


asm_10217c:
    CALL(aFunction1013d6);
    RET;

}

void Function102180(void){
    LD_HL(wc608 + 1);
    LD_DE(wStringBuffer2);
    LD_BC(11);
    CALL(aCopyBytes);
    RET;

}

void Function10218d(void){
    LD_HL(w5_dc00);
    LD_DE(wc608);
    LD_BC(0x26);
    LD_A(0x05);
    CALL(aFarCopyWRAM);
    LD_DE(wc608 + 1);  // useless
    RET;

}

void Function10219f(void){
    CALL(aFadeToMenu);
    CALL(aFunction10218d);
    LD_DE(wc608 + 1);
    FARCALL(aFunction8ac4e);
    CALL(aJoyWaitAorB);
    CALL(aPlayClickSFX);
    CALL(aFunction1013aa);
    RET;

}

void Function1021b8(void){
    CALL(aFadeToMenu);
    CALL(aFunction10218d);
    LD_DE(wPlayerMoveStruct);
    FARCALL(aFunction8ac70);
    LD_A_C;
    LD_addr_A(wStringBuffer1);
    PUSH_AF;
    CALL(aFunction1013aa);
    POP_AF;
    RET;

}

void NewCardArrivedText(void){
    //text_far ['_NewCardArrivedText']
    //text_end ['?']

    return PutCardInCardFolderText();
}

void PutCardInCardFolderText(void){
    //text_far ['_PutCardInCardFolderText']
    //text_end ['?']

    return CardWasListedText();
}

void CardWasListedText(void){
    //text_far ['_CardWasListedText']
    //text_end ['?']

    return Function1021e0();
}

void Function1021e0(void){
    CALL(aMenuTextbox);
    CALL(aJoyWaitAorB);
    CALL(aExitMenu);
    RET;

}

void StartingLinkText(void){
//  //  unreferenced
    //text_far ['_StartingLinkText']
    //text_end ['?']

    return LinkTerminatedText();
}

void LinkTerminatedText(void){
    //text_far ['_LinkTerminatedText']
    //text_end ['?']

    return ClosingLinkText();
}

void ClosingLinkText(void){
    //text_far ['_ClosingLinkText']
    //text_end ['?']

    return Function1021f9();
}

void Function1021f9(void){
    CALL(aFunction102233);
    LD_A(0x0);  // Function10234b
    LD_addr_A(wcd49);
    LD_HL(wcd29);
    BIT_hl(3);
    RES_hl(3);
    IF_Z goto asm_10220f;
    LD_A(0x1);  // Function102361
    LD_addr_A(wcd49);


asm_10220f:
    CALL(aFunction1022ca);
    LD_A_addr(wcd49);
    LD_HL(mJumptable_1022f5);
    RST(aJumpTable);
    CALL(aFunction102241);
    CALL(aFunction1022d0);
    IF_C goto asm_102231;
    LD_A_addr(wcd49);
    BIT_A(7);
    IF_Z goto asm_10220f;
    XOR_A_A;
    LD_HL(wcd29);
    BIT_hl(3);
    RET_Z ;
    SCF;
    RET;


asm_102231:
    XOR_A_A;
    RET;

}

void Function102233(void){
    LD_HL(wcd49);
    LD_BC(10);
    XOR_A_A;
    CALL(aByteFill);
    CALL(aFunction10304f);
    RET;

}

void Function102241(void){
    CALL(aFunction10226a);
    CALL(aFunction102274);
    CALL(aFunction10224b);
    RET;

}

void Function10224b(void){
    LD_HL(wcd4b);
    BIT_hl(1);
    IF_NZ goto asm_10225e;
    BIT_hl(2);
    IF_NZ goto asm_10225e;
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    XOR_A_A;
    RET;


asm_10225e:
    RES_hl(1);
    RES_hl(2);
    FARCALL(aMobile_ReloadMapPart);
    SCF;
    RET;

}

void Function10226a(void){
    LD_HL(wcd4b);
    BIT_hl(0);
    RET_Z ;
    CALL(aFunction10305d);
    RET;

}

void Function102274(void){
    LD_HL(wcd4b);
    BIT_hl(3);
    RET_Z ;
    RES_hl(3);
    LD_DE(8);
    CALL(aPlaySFX);
    RET;

}

void Function102283(void){
    LD_A(0x01);
    LD_addr_A(wAttrmapEnd);
    LD_HL(wcd4b);
    SET_hl(0);
    RET;

}

void Function10228e(void){
    XOR_A_A;
    LD_addr_A(wAttrmapEnd);
    LD_HL(wcd4b);
    RES_hl(0);
    RET;

}

void Function102298(void){
    LD_A_E;
    CP_A(0x02);
    RET_NZ ;
    LD_HL(wcd4b);
    BIT_hl(6);
    IF_Z goto asm_1022b6;
    LD_HL(wcd4b);
    BIT_hl(7);
    LD_HL(wcd4b);
    SET_hl(7);
    RET_NZ ;
    LD_DE(SFX_ELEVATOR_END);
    CALL(aPlaySFX);
    goto asm_1022c1;


asm_1022b6:
    LD_HL(wcd4b);
    BIT_hl(7);
    LD_HL(wcd4b);
    RES_hl(7);
    RET_Z ;


asm_1022c1:
    CALL(aFunction10304f);
    LD_A(0x01);
    LD_addr_A(wAttrmapEnd);
    RET;

}

void Function1022ca(void){
    LD_A(30);
    LD_addr_A(wOverworldDelay);
    RET;

}

void Function1022d0(void){
    FARCALL(aFunction10032e);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_1022f3;
    CALL(aFunction102298);
    LD_A_addr(wOverworldDelay);
    LD_C_A;
    LD_A(30);
    SUB_A_C;
    LD_C_A;
    LD_B(03);
    FARCALL(aAdvanceMobileInactivityTimerAndCheckExpired);
    IF_C goto asm_1022f3;
    XOR_A_A;
    RET;


asm_1022f3:
    SCF;
    RET;

}

void Jumptable_1022f5(void){
    //dw ['Function10234b'];  // 00
    //dw ['Function102361'];  // 01
    //dw ['Function10236e'];  // 02
    //dw ['Function102387'];  // 03
    //dw ['Function1023a1'];  // 04
    //dw ['Function1025c7'];  // 05
    //dw ['Function1025dc'];  // 06
    //dw ['Function1024f6'];  // 07
    //dw ['Function10250c'];  // 08
    //dw ['Function1024a8'];  // 09
    //dw ['Function102591'];  // 0a
    //dw ['Function1024a8'];  // 0b
    //dw ['Function1025b0'];  // 0c
    //dw ['Function1025bd'];  // 0d
    //dw ['Function102814'];  // 0e
    //dw ['Function10283c'];  // 0f
    //dw ['Function102862'];  // 10
    //dw ['Function10286f'];  // 11
    //dw ['Function1024a8'];  // 12
    //dw ['Function1028a5'];  // 13
    //dw ['Function1028ab'];  // 14
    //dw ['Function1023b5'];  // 15
    //dw ['Function1023c6'];  // 16
    //dw ['Function1024af'];  // 17
    //dw ['Function102416'];  // 18
    //dw ['Function102423'];  // 19
    //dw ['Function10244b'];  // 1a
    //dw ['Function1024af'];  // 1b
    //dw ['Function10246a'];  // 1c
    //dw ['Function102652'];  // 1d
    //dw ['Function10266b'];  // 1e
    //dw ['Function1025e9'];  // 1f
    //dw ['Function1025ff'];  // 20
    //dw ['Function102738'];  // 21
    //dw ['Function102754'];  // 22
    //dw ['Function1026b7'];  // 23
    //dw ['Function1026c8'];  // 24
    //dw ['Function1028bf'];  // 25
    //dw ['Function1028c6'];  // 26
    //dw ['Function1028d3'];  // 27
    //dw ['Function1028da'];  // 28
    //dw ['Function1024a8'];  // 29
    //dw ['Function10248d'];  // 2a

    return Function10234b();
}

void Function10234b(void){
    CALL(aFunction102d9a);
    CALL(aFunction102dd3);
    CALL(aFunction102dec);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function102361(void){
    LD_A(0xcc);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10236e(void){
    CALL(aFunction1028fc);
    RET_NC ;
    LD_A_addr(wcd51);
    CP_A(0xcc);
    IF_Z goto asm_10237f;
    LD_A(0xf2);
    LD_addr_A(wcd2b);
    RET;


asm_10237f:
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function102387(void){
    LD_HL(wcd4b);
    SET_hl(6);
    XOR_A_A;
    LD_addr_A(wdc5f);
    LD_DE(MUSIC_ROUTE_30);
    CALL(aPlayMusic);
    CALL(aFunction102d9a);
    CALL(aFunction102dd3);
    LD_A(0x01);
    LD_addr_A(wMenuCursorY);

    return Function1023a1();
}

void Function1023a1(void){
    CALL(aFunction102283);
    CALL(aFunction102db7);
    CALL(aFunction102dec);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x1d);
    LD_addr_A(wcd49);
    RET;

}

void Function1023b5(void){
    CALL(aFunction10228e);
    CALL(aFunction102a3b);
    CALL(aFunction102b12);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1023c6(void){
    CALL(aFunction102c48);
    CALL(aFunction102c87);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    FARCALL(aRemoveMonFromPartyOrBox);
    LD_HL(wPartyCount);
    INC_hl;
    LD_A_hli;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_hl(0xff);
    LD_A_addr(wPartyCount);
    LD_addr_A(wcd4c);
    CALL(aFunction102c07);
    CALL(aFunction102d48);
    CALL(aFunction102b32);
    CALL(aFunction102f50);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x14);
    LD_addr_A(wcd4e);
    LD_A(0);
    LD_addr_A(wcd4f);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function102416(void){
    LD_A(0xaa);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function102423(void){
    CALL(aFunction102921);
    RET_NC ;
    FARCALL(aSaveAfterLinkTrade);
    FARCALL(aStubbedTrainerRankings_Trades);
    FARCALL(aBackupMobileEventIndex);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10244b(void){
    CALL(aFunction102f32);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x19);
    LD_addr_A(wcd4e);
    LD_A(0);
    LD_addr_A(wcd4f);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10246a(void){
    CALL(aFunction102d9a);
    LD_HL(wcd29);
    SET_hl(3);
    CALL(aFunction102e07);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x2a);
    LD_addr_A(wcd49);
    RET;

}

void Function102480(void){
//  //  unreferenced
    LD_C(0x32);
    CALL(aDelayFrames);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10248d(void){
    LD_A_addr(wcd49);
    SET_A(7);
    LD_addr_A(wcd49);
    RET;

}

void Function102496(void){
//  //  unreferenced
    LD_HL(wcd4e);
    DEC_hl;
    RET_NZ ;
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1024a8(void){
    FARCALL(aFunction1009f3);
    RET_C ;

    return Function1024af();
}

void Function1024af(void){
    CALL(aGetJoypad);
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_1024ba);
    RST(aJumpTable);
    RET;

}

void Jumptable_1024ba(void){
    //dw ['Function1024c0'];
    //dw ['Function1024cb'];
    //dw ['Function1024de'];

    return Function1024c0();
}

void Function1024c0(void){
    LD_HL(wcd4e);
    INC_hl;
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);

    return Function1024cb();
}

void Function1024cb(void){
    LD_HL(wcd4e);
    DEC_hl;
    RET_NZ ;
    LD_A_addr(wcd4f);
    INC_A;
    LD_addr_A(wcd4e);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);

    return Function1024de();
}

void Function1024de(void){
    LD_HL(wcd4e);
    DEC_hl;
    IF_Z goto asm_1024e9;
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON | B_BUTTON);
    RET_Z ;


asm_1024e9:
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1024f6(void){
    CALL(aPlaceHollowCursor);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A_addr(wcd4c);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10250c(void){
    CALL(aFunction1028fc);
    RET_NC ;
    LD_A_addr(wcd51);
    CP_A(0x0f);
    IF_Z goto asm_10254b;
    AND_A_A;
    IF_Z goto asm_102572;
    CP_A(0xaa);
    IF_Z goto asm_102572;
    CP_A(0x07);
    IF_NC goto asm_102572;
    LD_addr_A(wcd4d);
    DEC_A;
    LD_addr_A(wd003);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_addr_A(wd002);
    CALL(aFunction102b9c);
    CALL(aFunction102bdc);
    IF_C goto asm_10256d;
    FARCALL(aCheckAnyOtherAliveMonsForTrade);
    IF_C goto asm_102568;
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x0e);
    LD_addr_A(wcd49);
    RET;


asm_10254b:
    CALL(aFunction103021);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A(0x1e);
    LD_addr_A(wcd4e);
    LD_A(0x1e);
    LD_addr_A(wcd4f);
    LD_A(0x29);
    LD_addr_A(wcd49);
    RET;


asm_102568:
    CALL(aFunction102ff5);
    goto asm_102577;


asm_10256d:
    CALL(aFunction102f85);
    goto asm_102577;


asm_102572:
    CALL(aFunction102fce);
    goto asm_102577;


asm_102577:
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A(0x1e);
    LD_addr_A(wcd4e);
    LD_A(0x3c);
    LD_addr_A(wcd4f);
    LD_A(0x09);
    LD_addr_A(wcd49);
    RET;

}

void Function102591(void){
    CALL(aFunction102ee7);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A(0x1e);
    LD_addr_A(wcd4e);
    LD_A(0x3c);
    LD_addr_A(wcd4f);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1025b0(void){
    LD_A(0x09);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1025bd(void){
    CALL(aFunction1028fc);
    RET_NC ;
    LD_A(0x04);
    LD_addr_A(wcd49);
    RET;

}

void Function1025c7(void){
    CALL(aFunction102f6d);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x0f);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1025dc(void){
    CALL(aFunction1028fc);
    RET_NC ;
    LD_A_addr(wcd49);
    SET_A(7);
    LD_addr_A(wcd49);
    RET;

}

void Function1025e9(void){
    NOP;
    LD_HL(wcd4b);
    SET_hl(6);
    CALL(aFunction102b4e);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1025ff(void){
    LD_HL(wcd4b);
    SET_hl(2);
    FARCALL(aFunction1009f3);
    RET_C ;
    FARCALL(aMobileMenuJoypad);
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    RET_Z ;
    BIT_C(A_BUTTON_F);
    IF_NZ goto a_button;
    BIT_C(D_UP_F);
    IF_NZ goto d_up;
    BIT_C(D_DOWN_F);
    IF_NZ goto d_down;
    RET;


a_button:
    LD_HL(wcd4b);
    SET_hl(3);
    LD_A(0x27);  // Function1028d3
    LD_addr_A(wcd49);
    RET;


d_up:
    LD_A_addr(wMenuCursorY);
    LD_B_A;
    LD_A_addr(wOTPartyCount);
    CP_A_B;
    RET_NZ ;
    CALL(aHideCursor);
    LD_A_addr(wPartyCount);
    LD_addr_A(wMenuCursorY);
    LD_A(0x1d);  // Function102652
    LD_addr_A(wcd49);
    RET;


d_down:
    LD_A_addr(wMenuCursorY);
    CP_A(0x01);
    RET_NZ ;
    LD_A(0x23);  // Function1026b7
    LD_addr_A(wcd49);
    RET;

}

void Function102652(void){
    NOP;
    LD_HL(wcd4b);
    SET_hl(6);
    NOP;
    CALL(aFunction102b7b);
    NOP;
    LD_HL(wcd4b);
    SET_hl(1);
    NOP;
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10266b(void){
    LD_HL(wcd4b);
    SET_hl(2);
    FARCALL(aFunction1009f3);
    RET_C ;
    FARCALL(aMobileMenuJoypad);
    LD_A_addr(wMenuJoypadFilter);
    AND_A_C;
    RET_Z ;
    BIT_C(A_BUTTON_F);
    IF_NZ goto a_button;
    BIT_C(D_DOWN_F);
    IF_NZ goto d_down;
    BIT_C(D_UP_F);
    IF_NZ goto d_up;
    RET;


a_button:
    LD_HL(wcd4b);
    SET_hl(3);
    LD_A(0x21);  // Function102738
    LD_addr_A(wcd49);
    RET;


d_down:
    LD_A_addr(wMenuCursorY);
    DEC_A;
    RET_NZ ;
    CALL(aHideCursor);
    LD_A(0x1f);  // Function1025e9
    LD_addr_A(wcd49);
    RET;


d_up:
    LD_A_addr(wMenuCursorY);
    LD_B_A;
    LD_A_addr(wPartyCount);
    CP_A_B;
    RET_NZ ;
    LD_A(0x23);  // Function1026b7
    LD_addr_A(wcd49);
    RET;

}

void Function1026b7(void){
    LD_HL(wcd4b);
    SET_hl(6);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    LD_A(0);
    LD_addr_A(wcd4a);

    return Function1026c8();
}

void Function1026c8(void){
    CALL(aGetJoypad);
    FARCALL(aFunction1009f3);
    RET_C ;
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_1026da);
    RST(aJumpTable);
    RET;

}

void Jumptable_1026da(void){
    //dw ['Function1026de'];
    //dw ['Function1026f3'];

    return Function1026de();
}

void Function1026de(void){
    CALL(aHideCursor);
    hlcoord(9, 17, wTilemap);
    LD_hl(0xed);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    LD_HL(wcd4b);
    SET_hl(1);
    RET;

}

void Function1026f3(void){
    LDH_A_addr(hJoyPressed);
    BIT_A(A_BUTTON_F);
    IF_NZ goto asm_102723;
    BIT_A(D_UP_F);
    IF_NZ goto asm_102712;
    BIT_A(D_DOWN_F);
    IF_NZ goto asm_102702;
    RET;


asm_102702:
    hlcoord(9, 17, wTilemap);
    LD_hl(0x7f);
    LD_A(0x01);
    LD_addr_A(wMenuCursorY);
    LD_A(0x1d);  // Function102652
    LD_addr_A(wcd49);
    RET;


asm_102712:
    hlcoord(9, 17, wTilemap);
    LD_hl(0x7f);
    LD_A_addr(wOTPartyCount);
    LD_addr_A(wMenuCursorY);
    LD_A(0x1f);  // Function1025e9
    LD_addr_A(wcd49);
    RET;


asm_102723:
    hlcoord(9, 17, wTilemap);
    LD_hl(0xec);
    LD_HL(wcd4b);
    SET_hl(3);
    LD_HL(wcd4b);
    SET_hl(2);
    LD_A(0x5);  // Function1025c7
    LD_addr_A(wcd49);
    RET;

}

void Function102738(void){
    LD_HL(wcd4b);
    SET_hl(6);
    CALL(aPlaceHollowCursor);
    CALL(aFunction1027eb);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    LD_A(0);
    LD_addr_A(wcd4a);

    return Function102754();
}

void Function102754(void){
    CALL(aGetJoypad);
    FARCALL(aFunction1009f3);
    RET_C ;
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_102766);
    RST(aJumpTable);
    RET;

}

void Jumptable_102766(void){
    //dw ['Function102770'];
    //dw ['Function102775'];
    //dw ['Function10278c'];
    //dw ['Function1027a0'];
    //dw ['Function1027b7'];

    return Function102770();
}

void Function102770(void){
    LD_A(0x01);
    LD_addr_A(wcd4a);

    return Function102775();
}

void Function102775(void){
    hlcoord(1, 16, wTilemap);
    LD_hl(0xed);
    hlcoord(11, 16, wTilemap);
    LD_hl(0x7f);
    LD_HL(wcd4b);
    SET_hl(2);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    RET;

}

void Function10278c(void){
    LDH_A_addr(hJoyPressed);
    BIT_A(A_BUTTON_F);
    JR_NZ (masm_1027c6);
    BIT_A(B_BUTTON_F);
    JR_NZ (masm_1027e2);
    BIT_A(D_RIGHT_F);
    IF_NZ goto asm_10279b;
    RET;


asm_10279b:
    LD_A(0x03);
    LD_addr_A(wcd4a);
    return Function1027a0();
}

void Function1027a0(void){
    hlcoord(1, 16, wTilemap);
    LD_hl(0x7f);
    hlcoord(11, 16, wTilemap);
    LD_hl(0xed);
    LD_HL(wcd4b);
    SET_hl(2);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    RET;

}

void Function1027b7(void){
    LDH_A_addr(hJoyPressed);
    BIT_A(A_BUTTON_F);
    JR_NZ (masm_1027d1);
    BIT_A(B_BUTTON_F);
    JR_NZ (masm_1027e2);
    BIT_A(D_LEFT_F);
    JR_NZ (mFunction102770);
    RET;

}

void asm_1027c6(void){
    LD_HL(wcd4b);
    SET_hl(3);
    LD_A(0x25);  // Function1028bf
    LD_addr_A(wcd49);
    RET;

}

void asm_1027d1(void){
    LD_HL(wcd4b);
    SET_hl(3);
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wcd4c);
    LD_A(0x7);  // Function1024f6
    LD_addr_A(wcd49);
    RET;

}

void asm_1027e2(void){
    CALL(aFunction102db7);
    LD_A(0x1d);  // Function102652
    LD_addr_A(wcd49);
    RET;

}

void Function1027eb(void){
    hlcoord(0, 14, wTilemap);
    LD_B(2);
    LD_C(18);
    LD_D_H;
    LD_E_L;
    FARCALL(av_LinkTextbox);
    LD_DE(mFunction1027eb_Stats_Trade);
    hlcoord(2, 16, wTilemap);
    CALL(aPlaceString);
    RET;


Stats_Trade:
    //db ['"STATS     TRADE@"'];

    return Function102814();
}

void Function102814(void){
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wcd52);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_addr_A(wd002);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_addr_A(wd003);
    CALL(aFunction102ea8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_HL(wcd4b);
    SET_hl(1);

    return Function10283c();
}

void Function10283c(void){
    LD_HL(wcd4b);
    SET_hl(2);
    CALL(aFunction1029c3);
    RET_Z ;
    IF_C goto asm_102852;
    LD_A(0x10);  // Function102862
    LD_addr_A(wcd49);
    LD_HL(wcd4b);
    SET_hl(1);
    RET;


asm_102852:
    LD_A(0x14);  // Function1028ab
    LD_addr_A(wcd49);
    LD_HL(wcd4b);
    SET_hl(3);
    LD_HL(wcd4b);
    SET_hl(1);
    RET;

}

void Function102862(void){
    LD_A(0x08);
    CALL(aFunction1028e8);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function10286f(void){
    CALL(aFunction1028fc);
    RET_NC ;
    LD_A_addr(wcd52);
    LD_addr_A(wMenuCursorY);
    LD_A_addr(wcd51);
    CP_A(0x08);
    IF_NZ goto asm_102886;
    LD_A(0x15);  // Function1023b5
    LD_addr_A(wcd49);
    RET;


asm_102886:
    CALL(aFunction102ee7);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0x1e);
    LD_addr_A(wcd4e);
    LD_A(0x3c);
    LD_addr_A(wcd4f);
    LD_A(0);
    LD_addr_A(wcd4a);
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);
    RET;

}

void Function1028a5(void){
    LD_A(0x4);  // Function1023a1
    LD_addr_A(wcd49);
    RET;

}

void Function1028ab(void){
    LD_A_addr(wcd52);
    LD_addr_A(wMenuCursorY);
    CALL(aFunction102f15);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A(0xc);  // Function1025b0
    LD_addr_A(wcd49);
    RET;

}

void Function1028bf(void){
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);

    return Function1028c6();
}

void Function1028c6(void){
    XOR_A_A;
    LD_addr_A(wMonType);
    CALL(aFunction102bac);
    LD_A(0x1d);  // Function102652
    LD_addr_A(wcd49);
    RET;

}

void Function1028d3(void){
    LD_A_addr(wcd49);
    INC_A;
    LD_addr_A(wcd49);

    return Function1028da();
}

void Function1028da(void){
    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);
    CALL(aFunction102bac);
    LD_A(0x1f);  // Function1025e9
    LD_addr_A(wcd49);
    RET;

}

void Function1028e8(void){
    LD_HL(wcd4b);
    RES_hl(6);
    LD_addr_A(wcd50);
    FARCALL(aStartMobileInactivityTimer);
    LD_A(0);
    LD_addr_A(wcd4a);
    RET;

}

void Function1028fc(void){
    CALL(aGetJoypad);
    FARCALL(aFunction1009f3);
    IF_NC goto asm_102909;
    AND_A_A;
    RET;


asm_102909:
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_102917);
    RST(aJumpTable);
    RET_NC ;
    LD_A(0);
    LD_addr_A(wcd4a);
    RET;

}

void Jumptable_102917(void){
    //dw ['Function102933'];
    //dw ['Function10294f'];
    //dw ['Function10295d'];
    //dw ['Function10296e'];
    //dw ['Function102996'];

    return Function102921();
}

void Function102921(void){
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_10292f);
    RST(aJumpTable);
    RET_NC ;
    LD_A(0);
    LD_addr_A(wcd4a);
    RET;

}

void Jumptable_10292f(void){
    //dw ['Function10295d'];
    //dw ['Function102984'];

    return Function102933();
}

void Function102933(void){
    LD_HL(mMenuHeader_1029bb);
    CALL(aLoadMenuHeader);
    CALL(aFunction102e07);
    LD_A(0x32);
    LD_addr_A(wTextDelayFrames);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    AND_A_A;
    RET;

}

void Function10294f(void){
    LD_A_addr(wTextDelayFrames);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    AND_A_A;
    RET;

}

void Function10295d(void){
    CALL(aFunction10299e);
    LD_A(0);
    LD_addr_A(wcd27);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    AND_A_A;
    RET;

}

void Function10296e(void){
    FARCALL(aFunction100382);
    AND_A_A;
    LD_A_addr(wcd27);
    BIT_A(7);
    RET_Z ;
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    AND_A_A;
    RET;

}

void Function102984(void){
    FARCALL(aFunction100382);
    AND_A_A;
    LD_A_addr(wcd27);
    BIT_A(7);
    RET_Z ;
    CALL(aFunction1029af);
    SCF;
    RET;

}

void Function102996(void){
    CALL(aFunction1029af);
    CALL(aExitMenu);
    SCF;
    RET;

}

void Function10299e(void){
    LD_A(0x01);
    LD_addr_A(wccb4);
    LD_A_addr(wcd50);
    LD_addr_A(wccb5);
    LD_A(0xaa);
    LD_addr_A(wcd51);
    RET;

}

void Function1029af(void){
    LD_HL(wcd4b);
    RES_hl(7);
    LD_A_addr(wcc61);
    LD_addr_A(wcd51);
    RET;

}

void MenuHeader_1029bb(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['3', '10', '15', '12'];
    //dw ['NULL'];
    //db ['1'];  // default option

    return Function1029c3();
}

void Function1029c3(void){
    LD_A_addr(wcd4a);
    LD_HL(mJumptable_1029cb);
    RST(aJumpTable);
    RET;

}

void Jumptable_1029cb(void){
    //dw ['Function1029cf'];
    //dw ['Function1029fe'];

    return Function1029cf();
}

void Function1029cf(void){
    CALL(aLoadStandardMenuHeader);
    hlcoord(10, 7, wTilemap);
    LD_B(3);
    LD_C(8);
    LD_D_H;
    LD_E_L;
    FARCALL(av_LinkTextbox);
    LD_DE(mString_102a26);
    hlcoord(12, 8, wTilemap);
    CALL(aPlaceString);
    LD_HL(wcd4b);
    SET_hl(1);
    LD_DE(mMenuData3_102a33);
    CALL(aLoad2DMenuData);
    LD_A_addr(wcd4a);
    INC_A;
    LD_addr_A(wcd4a);
    XOR_A_A;
    RET;

}

void Function1029fe(void){
    FARCALL(aFunction1009f3);
    RET_C ;
    FARCALL(aMobileMenuJoypad);
    LD_A_C;
    LD_HL(wMenuJoypadFilter);
    AND_A_hl;
    RET_Z ;
    PUSH_AF;
    CALL(aExitMenu);
    POP_AF;
    LD_A_addr(wMenuCursorY);
    CP_A(0x01);
    IF_NZ goto asm_102a21;
    LD_A(0x01);
    AND_A_A;
    RET;


asm_102a21:
    LD_A(0x01);
    AND_A_A;
    SCF;
    RET;

}

void String_102a26(void){
    //db ['"TRADE"'];
    //next ['"CANCEL"']
    //db ['"@"'];

    return MenuData3_102a33();
}

void MenuData3_102a33(void){
    //db ['8', '11'];  // cursor start y, x
    //db ['2', '1'];  // rows, columns
    //db ['0x80', '0x00'];  // flags
    //dn ['2', '0'];  // cursor offset
    //db ['A_BUTTON'];  // accepted buttons

    return Function102a3b();
}

void Function102a3b(void){
    LD_A_addr(wcd30);
    LD_addr_A(wc74e);
    LD_HL(wPlayerName);
    LD_DE(wPlayerTrademonSenderName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wPlayerTrademonSpecies);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_HL(wPartyMonOTs);
    CALL(aSkipNames);
    LD_DE(wPlayerTrademonOTName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_HL(wPartyMon1ID);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wPlayerTrademonID);
    LD_A_hl;
    LD_addr_A(wPlayerTrademonID + 1);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_HL(wPartyMon1DVs);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wPlayerTrademonDVs);
    LD_A_hl;
    LD_addr_A(wPlayerTrademonDVs + 1);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_HL(wPartyMon1Species);
    CALL(aGetPartyLocation);
    LD_B_H;
    LD_C_L;
    FARCALL(aGetCaughtGender);
    LD_A_C;
    LD_addr_A(wPlayerTrademonCaughtData);
    LD_HL(wOTPlayerName);
    LD_DE(wOTTrademonSenderName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);

    LD_A_addr(wcd4d);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wOTTrademonSpecies);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_HL(wOTPartyMonOTs);
    CALL(aSkipNames);
    LD_DE(wOTTrademonOTName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_HL(wOTPartyMon1ID);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wOTTrademonID);
    LD_A_hl;
    LD_addr_A(wOTTrademonID + 1);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_HL(wOTPartyMon1DVs);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wOTTrademonDVs);
    LD_A_hl;
    LD_addr_A(wOTTrademonDVs + 1);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_HL(wOTPartyMon1Species);
    CALL(aGetPartyLocation);
    LD_B_H;
    LD_C_L;
    FARCALL(aGetCaughtGender);
    LD_A_C;
    LD_addr_A(wOTTrademonCaughtData);
    RET;

}

void Function102b12(void){
    LD_C(100);
    CALL(aDelayFrames);
    CALL(aFunction102d9a);
    CALL(aLoadFontsBattleExtra);
    LD_A_addr(wcd2f);
    AND_A_A;
    IF_NZ goto asm_102b2b;
    FARCALL(aFunction108026);
    goto asm_102b31;


asm_102b2b:
    FARCALL(aFunction10802a);


asm_102b31:
    RET;

}

void Function102b32(void){
    LD_A_addr(wcd4c);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    LD_A(0x01);
    LD_addr_A(wForceEvolution);
    FARCALL(aEvolvePokemon);
    CALL(aFunction102d9a);
    CALL(aFunction102dd3);
    CALL(aFunction102dec);
    RET;

}

void Function102b4e(void){
    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);
    LD_A_addr(wMenuCursorY);
    PUSH_AF;
    LD_DE(mMenuData_102b73);
    CALL(aLoad2DMenuData);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    LD_A_addr(wOTPartyCount);
    LD_addr_A(w2DMenuNumRows);
    RET;

}

void Function102b68(void){
//  //  unreferenced
    XOR_A_A;
    LD_HL(wWindowStackPointer);
    LD_BC(0x10);
    CALL(aByteFill);
    RET;

}

void MenuData_102b73(void){
    //db ['9', '6'];  // cursor start y, x
    //db ['-1', '1'];  // rows, columns
    //db ['0xa0', '0x00'];  // flags
    //dn ['1', '0'];  // cursor offset
    //db ['D_UP | D_DOWN | A_BUTTON'];  // accepted buttons

    return Function102b7b();
}

void Function102b7b(void){
    XOR_A_A;
    LD_addr_A(wMonType);
    LD_A_addr(wMenuCursorY);
    PUSH_AF;
    LD_DE(mMenuData_102b94);
    CALL(aLoad2DMenuData);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    LD_A_addr(wPartyCount);
    LD_addr_A(w2DMenuNumRows);
    RET;

}

void MenuData_102b94(void){
    //db ['1', '6'];  // cursor start y, x
    //db ['255', '1'];  // rows, columns
    //db ['0xa0', '0x00'];  // flags
    //dn ['1', '0'];  // cursor offset
    //db ['D_UP | D_DOWN | A_BUTTON'];  // accepted buttons

    return Function102b9c();
}

void Function102b9c(void){
    LD_A_addr(wcd4d);
    DEC_A;
    hlcoord(6, 9, wTilemap);
    LD_BC(0x14);
    CALL(aAddNTimes);
    LD_hl(0xec);
    RET;

}

void Function102bac(void){
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    CALL(aLowVolume);
    CALL(aClearSprites);
    FARCALL(av_MobileStatsScreenInit);
    LD_A_addr(wCurPartyMon);
    INC_A;
    LD_addr_A(wMenuCursorY);
    CALL(aFunction102d9a);
    CALL(aClearPalettes);
    CALL(aDelayFrame);
    CALL(aMaxVolume);
    CALL(aFunction102dd3);
    CALL(aFunction102dec);
    CALL(aFunction102db7);
    RET;

}

void Function102bdc(void){
    LD_A_addr(wcd4d);
    DEC_A;
    LD_HL(wOTPartyMon1Species);
    CALL(aGetPartyLocation);
    PUSH_HL;
    LD_A_addr(wcd4d);
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartyCount);
    ADD_HL_BC;
    LD_A_hl;
    POP_HL;
    CP_A(EGG);
    IF_Z goto asm_102bfa;
    CP_A_hl;
    IF_NZ goto asm_102c05;


asm_102bfa:
    LD_BC(MON_LEVEL);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(MAX_LEVEL + 1);
    IF_NC goto asm_102c05;
    AND_A_A;
    RET;


asm_102c05:
    SCF;
    RET;

}

void Function102c07(void){
    CALL(aFunction102c14);
    CALL(aFunction102c3b);
    CALL(aFunction102c21);
    CALL(aFunction102c2e);
    RET;

}

void Function102c14(void){
    LD_HL(wPartySpecies);
    LD_DE(wOTPartySpecies);
    LD_BC(1);
    CALL(aFunction102c71);
    RET;

}

void Function102c21(void){
    LD_HL(wPartyMonNicknames);
    LD_DE(wOTPartyMonNicknames);
    LD_BC(11);
    CALL(aFunction102c71);
    RET;

}

void Function102c2e(void){
    LD_HL(wPartyMonOTs);
    LD_DE(wOTPartyMonOTs);
    LD_BC(11);
    CALL(aFunction102c71);
    RET;

}

void Function102c3b(void){
    LD_HL(wPartyMon1);
    LD_DE(wOTPartyMon1);
    LD_BC(0x30);
    CALL(aFunction102c71);
    RET;

}

void Function102c48(void){
    FARCALL(aFunction10165a);
    LD_A(0);
    CALL(aOpenSRAM);
    LD_HL(0xa600);
    LD_DE(wc608);
    LD_BC(0x2f);
    CALL(aFunction102c71);
    CALL(aCloseSRAM);
    LD_HL(wc608);
    LD_DE(w5_da00);
    LD_BC(0x1e0);
    LD_A(0x05);
    CALL(aFarCopyWRAM);
    RET;

}

void Function102c71(void){
    LD_A_addr(wcd4c);
    DEC_A;
    CALL(aAddNTimes);
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    LD_A_addr(wcd4d);
    DEC_A;
    CALL(aAddNTimes);
    POP_DE;
    CALL(aSwapBytes);
    RET;

}

void Function102c87(void){
    LD_A_addr(wJumptableIndex);
    PUSH_AF;
    LD_A_addr(wcf64);
    PUSH_AF;
    LD_A_addr(wcd4c);
    LD_addr_A(wJumptableIndex);
    LD_A_addr(wPartyCount);
    LD_addr_A(wcf64);
    LD_A(0);
    LD_HL(0xa600);
    LD_DE(wc608);
    LD_BC(0x11a);
    CALL(aFunction102d3e);
    CALL(aFunction102cee);
    LD_A(0);
    LD_HL(wc608);
    LD_DE(0xa600);
    LD_BC(0x11a);
    CALL(aFunction102d3e);
    LD_A_addr(wcd4d);
    LD_addr_A(wJumptableIndex);
    LD_A_addr(wOTPartyCount);
    LD_addr_A(wcf64);
    LD_A(0x05);
    LD_HL(w5_da00);
    LD_DE(wc608);
    LD_BC(0x11a);
    CALL(aFarCopyWRAM);
    CALL(aFunction102cee);
    LD_A(0x05);
    LD_HL(wc608);
    LD_DE(w5_da00);
    LD_BC(0x11a);
    CALL(aFarCopyWRAM);
    POP_AF;
    LD_addr_A(wcf64);
    POP_AF;
    LD_addr_A(wJumptableIndex);
    RET;

}

void Function102cee(void){
    LD_A_addr(wJumptableIndex);
    DEC_A;
    CALL(aFunction102d34);
    LD_DE(wd002);
    LD_BC(0x2f);
    CALL(aCopyBytes);
    LD_A_addr(wJumptableIndex);
    LD_C_A;
    LD_A(0x06);
    SUB_A_C;
    RET_Z ;
    LD_BC(0x2f);
    LD_HL(0);
    CALL(aAddNTimes);
    PUSH_HL;
    LD_A_addr(wJumptableIndex);
    DEC_A;
    CALL(aFunction102d34);
    LD_D_H;
    LD_E_L;
    LD_HL(0x2f);
    ADD_HL_DE;
    POP_BC;
    CALL(aCopyBytes);
    LD_A_addr(wcf64);
    DEC_A;
    CALL(aFunction102d34);
    LD_D_H;
    LD_E_L;
    LD_HL(wd002);
    LD_BC(0x2f);
    CALL(aCopyBytes);
    RET;

}

void Function102d34(void){
    LD_HL(wc608);
    LD_BC(0x2f);
    CALL(aAddNTimes);
    RET;

}

void Function102d3e(void){
    CALL(aOpenSRAM);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void Function102d48(void){
    LD_A_addr(wcd4c);
    LD_E_A;
    LD_D(0);
    LD_HL(wPartyCount);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wTempSpecies);
    CP_A(EGG);
    IF_Z goto asm_102d6d;
    DEC_A;
    CALL(aSetSeenAndCaughtMon);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1Happiness);
    CALL(aAddNTimes);
    LD_hl(BASE_HAPPINESS);


asm_102d6d:
    LD_A_addr(wTempSpecies);
    CP_A(UNOWN);
    IF_NZ goto asm_102d98;
    LD_A_addr(wcd4c);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    LD_HL(wPartyMon1DVs);
    CALL(aAddNTimes);
    PREDEF(pGetUnownLetter);
    FARCALL(aUpdateUnownDex);
    LD_A_addr(wFirstUnownSeen);
    AND_A_A;
    IF_NZ goto asm_102d98;
    LD_A_addr(wUnownLetter);
    LD_addr_A(wFirstUnownSeen);


asm_102d98:
    AND_A_A;
    RET;

}

void Function102d9a(void){
    LD_A(0x7f);
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    LD_A(0x07);
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    RET;

}

void Function102db7(void){
    CALL(aFunction102e4f);
    CALL(aFunction102e3e);
    LD_HL(wcd4b);
    SET_hl(1);
    RET;

}

void Function102dc3(void){
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    LD_D_H;
    LD_E_L;
    FARCALL(av_LinkTextbox);
    RET;

}

void Function102dd3(void){
    CALL(aDisableLCD);
    LD_DE(mMobileTradeLightsGFX);
    LD_HL(vTiles0);
    LD_BC((BANK(aMobileTradeLightsGFX) << 8) | 4);
    CALL(aGet2bpp);
    FARCALL(av__LoadTradeScreenBorderGFX);
    CALL(aEnableLCD);
    RET;

}

void Function102dec(void){
    LD_HL(mMobileTradeLightsPalettes);
    LD_DE(wOBPals1);
    LD_BC(4 * PALETTE_SIZE);
    LD_A(0x05);
    CALL(aFarCopyWRAM);
    FARCALL(aFunction49742);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    RET;

}

void Function102e07(void){
    hlcoord(3, 10, wTilemap);
    LD_B(1);
    LD_C(11);
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_Z goto link_battle;
    CALL(aTextbox);
    goto okay;


link_battle:
//  the next three operations are pointless
    hlcoord(3, 10, wTilemap);
    LD_B(1);
    LD_C(11);
    LD_D_H;
    LD_E_L;
    FARCALL(av_LinkTextbox);


okay:
    LD_DE(mFunction102e07_waiting);
    hlcoord(4, 11, wTilemap);
    CALL(aPlaceString);
    RET;


waiting:
    //db ['"Waiting...!@"'];

    return Function102e3e();
}

void Function102e3e(void){
    LD_DE(mFunction102e3e_CancelString);
    hlcoord(10, 17, wTilemap);
    CALL(aPlaceString);
    RET;


CancelString:
    //db ['"CANCEL@"'];

    return Function102e4f();
}

void Function102e4f(void){
    FARCALL(aLoadMobileTradeBorderTilemap);
    FARCALL(av_InitMG_Mobile_LinkTradePalMap);
    LD_DE(wPlayerName);
    hlcoord(4, 0, wTilemap);
    CALL(aPlaceString);
    LD_A(0x14);
    LD_bc_A;
    LD_DE(wOTPlayerName);
    hlcoord(4, 8, wTilemap);
    CALL(aPlaceString);
    LD_A(0x14);
    LD_bc_A;
    hlcoord(7, 1, wTilemap);
    LD_DE(wPartySpecies);
    CALL(aFunction102e4f_PlaceSpeciesNames);
    hlcoord(7, 9, wTilemap);
    LD_DE(wOTPartySpecies);
    CALL(aFunction102e4f_PlaceSpeciesNames);
    RET;


PlaceSpeciesNames:
    LD_C(0);

count_loop:
    LD_A_de;
    CP_A(0xff);
    RET_Z ;
    LD_addr_A(wNamedObjectIndex);
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    PUSH_HL;
    LD_A_C;
    LDH_addr_A(hDividend);
    CALL(aGetPokemonName);
    POP_HL;
    CALL(aPlaceString);
    POP_DE;
    INC_DE;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    INC_C;
    goto count_loop;

    return Function102ea8();
}

void Function102ea8(void){
    CALL(aFunction102dc3);
    LD_A_addr(wcd4c);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(wStringBuffer1);
    LD_DE(wStringBuffer2);
    LD_BC(11);
    CALL(aCopyBytes);
    LD_A_addr(wcd4d);
    DEC_A;
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(mTradingMonForOTMonText);
    CALL(aPrintTextboxText);
    RET;

}

void TradingMonForOTMonText(void){
    //text_far ['_TradingMonForOTMonText']
    //text_end ['?']

    return Function102ee7();
}

void Function102ee7(void){
    CALL(aFunction102dc3);
    LD_DE(mString_102ef4);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;

}

void String_102ef4(void){
    //db ['"Too bad! The trade"'];
    //next ['"was canceled!"']
    //db ['"@"'];

    return Function102f15();
}

void Function102f15(void){
    CALL(aFunction102dc3);
    LD_DE(mFunction102f15_TooBadTheTradeWasCanceled);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;


TooBadTheTradeWasCanceled:
    //db ['"こうかんを\u3000キャンセルしました@"'];

    return Function102f32();
}

void Function102f32(void){
    CALL(aFunction102dc3);
    LD_DE(mFunction102f32_TradeCompleted);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;


TradeCompleted:
    //db ['"Trade completed!@"'];

    return Function102f50();
}

void Function102f50(void){
    CALL(aFunction102dc3);
    LD_DE(mFunction102f50_PleaseWait);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;


PleaseWait:
    //db ['"しょうしょう\u3000おまち\u3000ください@"'];

    return Function102f6d();
}

void Function102f6d(void){
    CALL(aFunction102dc3);
    LD_DE(mFunction102f6d_Finished);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;


Finished:
    //db ['"しゅうりょう\u3000します@"'];

    return Function102f85();
}

void Function102f85(void){
    LD_A_addr(wd003);
    LD_C_A;
    LD_B(0);
    LD_HL(wOTPartySpecies);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    CALL(aFunction102dc3);
    LD_DE(mString_102fb2);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    LD_DE(wStringBuffer1);
    hlcoord(13, 14, wTilemap);
    CALL(aPlaceString);
    LD_DE(mString_102fcc);
    CALL(aPlaceString);
    RET;

}

void String_102fb2(void){
    //db ['"あいてがわ<PKMN>えらんだ\u3000"'];
    //next ['"いじょう<PKMN>あるようです！！"']
    //db ['"@"'];

    return String_102fcc();
}

void String_102fcc(void){
    //db ['"に@"'];

    return Function102fce();
}

void Function102fce(void){
    CALL(aFunction102dc3);
    LD_DE(mString_102fdb);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;

}

void String_102fdb(void){
    //db ['"あいてがわ<NO>せんたくに"'];
    //next ['"いじょう<PKMN>あるようです！！"']
    //done ['?']

    return Function102ff5();
}

void Function102ff5(void){
    CALL(aFunction102dc3);
    LD_DE(mString_103002);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;

}

void String_103002(void){
    //db ['"その#を\u3000こうかんすると"'];
    //next ['"せんとう\u3000できなく\u3000なっちゃうよ！"']
    //db ['"@"'];

    return Function103021();
}

void Function103021(void){
    CALL(aFunction102dc3);
    LD_DE(mString_10302e);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;

}

void String_10302e(void){
    //db ['"あいてが\u3000ちゅうしを\u3000えらんだので"'];
    //next ['"こうかんを\u3000ちゅうし\u3000します"']
    //db ['"@"'];

    return Function10304f();
}

void Function10304f(void){
    XOR_A_A;
    LD_addr_A(wAttrmapEnd);
    LD_addr_A(wcf42);
    LD_addr_A(wcf44);
    LD_addr_A(wcf45);
    RET;

}

void Function10305d(void){
    NOP;
    LD_A_addr(wAttrmapEnd);
    AND_A_A;
    RET_Z ;
    CALL(aFunction10307f);
    RET_C ;
    CALL(aFunction103094);
    CALL(aFunction10306e);
    RET;

}

void Function10306e(void){
    LD_A(0x01);
    LDH_addr_A(hOAMUpdate);
    CALL(aClearSprites);
    LD_DE(wVirtualOAM);
    CALL(aFunction1030cd);
    XOR_A_A;
    LDH_addr_A(hOAMUpdate);
    RET;

}

void Function10307f(void){
    LD_C(0x02);
    LD_HL(wcd4b);
    BIT_hl(7);
    IF_Z goto asm_10308a;
    LD_C(0x01);


asm_10308a:
    LD_HL(wcf45);
    INC_hl;
    LD_A_hl;
    CP_A_C;
    RET_C ;
    XOR_A_A;
    LD_hl_A;
    RET;

}

void Function103094(void){
    LD_HL(wcd4b);
    BIT_hl(7);
    IF_NZ goto asm_1030c0;
    LD_A_addr(wcf42);
    BIT_A(7);
    IF_NZ goto asm_1030b2;
    LD_A_addr(wcf44);
    INC_A;
    LD_addr_A(wcf44);
    CP_A(0x2c);
    RET_NZ ;
    LD_HL(wcf42);
    SET_hl(7);
    RET;


asm_1030b2:
    LD_A_addr(wcf44);
    DEC_A;
    LD_addr_A(wcf44);
    RET_NZ ;
    LD_HL(wcf42);
    RES_hl(7);
    RET;


asm_1030c0:
    LD_HL(wcf44);
    LD_A_hl;
    AND_A_A;
    IF_Z goto asm_1030ca;
    DEC_A;
    LD_hl_A;
    RET_NZ ;


asm_1030ca:
    LD_hl(0x2c);
    RET;

}

void Function1030cd(void){
    LD_A_addr(wcf44);
    LD_L_A;
    LD_H(0);
    ADD_HL_HL;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_BC(mUnknown_103112);
    ADD_HL_BC;
    LD_B(0x30);
    LD_C(0x08);

asm_1030de:
    PUSH_HL;
    LD_HL(wcd4b);
    BIT_hl(7);
    POP_HL;
    LD_A(0);
    IF_Z goto asm_1030eb;
    LD_A(0x05);

asm_1030eb:

    ADD_A_hl;
    INC_HL;
    PUSH_HL;

    ADD_A_A;
    ADD_A_A;

    ADD_A(LOW(aUnknown_10327a));
    LD_L_A;
    LD_A(HIGH(aUnknown_10327a));
    ADC_A(0);
    LD_H_A;

    LD_A_B;
    ADD_A_hl;
    INC_HL;
    LD_de_A;
    INC_DE;
    LD_A(0x0a);
    ADD_A_hl;
    INC_HL;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    POP_HL;
    LD_A_B;
    ADD_A(0x08);
    LD_B_A;
    DEC_C;
    IF_NZ goto asm_1030de;
    RET;

}

void Unknown_103112(void){
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x01', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x02', '0x01', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x03', '0x02', '0x01', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x04', '0x03', '0x02', '0x01', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x04', '0x04', '0x03', '0x02', '0x01', '0x00', '0x00', '0x00'];
    //db ['0x04', '0x04', '0x04', '0x03', '0x02', '0x01', '0x00', '0x00'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x03', '0x02', '0x01', '0x00'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x03', '0x02', '0x01'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x03', '0x02'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x03'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x03', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x02', '0x03', '0x04', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x01', '0x02', '0x03', '0x04', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x00', '0x01', '0x02', '0x03', '0x04', '0x04', '0x04', '0x04'];
    //db ['0x00', '0x00', '0x01', '0x02', '0x03', '0x04', '0x04', '0x04'];
    //db ['0x00', '0x00', '0x00', '0x01', '0x02', '0x03', '0x04', '0x04'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x01', '0x02', '0x03', '0x04'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x01', '0x02', '0x03'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x01', '0x02'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x01'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00', '0x00'];

    return Unknown_10327a();
}

void Unknown_10327a(void){
    //db ['0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x01', '0x00'];
    //db ['0x00', '0x00', '0x02', '0x00'];
    //db ['0x00', '0x00', '0x03', '0x00'];
    //db ['0x00', '0x00', '0x01', '0x01'];
    //db ['0x00', '0x00', '0x00', '0x00'];
    //db ['0x00', '0x00', '0x01', '0x02'];
    //db ['0x00', '0x00', '0x02', '0x02'];
    //db ['0x00', '0x00', '0x03', '0x02'];
    //db ['0x00', '0x00', '0x01', '0x03'];

    return MobileTradeLightsGFX();
}

void MobileTradeLightsGFX(void){
// INCBIN "gfx/mobile/mobile_trade_lights.2bpp"

    return MobileTradeLightsPalettes();
}

void MobileTradeLightsPalettes(void){
// INCLUDE "gfx/mobile/mobile_trade_lights.pal"

    return Function103302();
}

void Function103302(void){
    CALL(aFunction103309);
    CALL(aFunction103362);
    RET;

}

void Function103309(void){
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    LD_HL(wd1ea);
    LD_BC(10);
    XOR_A_A;
    CALL(aByteFill);
    LD_A(BANK(s4_a60c));
    CALL(aOpenSRAM);
    LD_A_addr(wdc41);
    LD_addr_A(s4_a60c);
    LD_addr_A(wd1ea);
    CALL(aCloseSRAM);
    CALL(aFunction1035c6);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_addr_A(wd1ef);
    LD_A_hli;
    LD_addr_A(wd1ec);
    LD_A_hli;
    LD_addr_A(wd1ed);
    LD_H_D;
    LD_L_E;
    CALL(aFunction3eea);
    LD_HL(wd1ec);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hl;
    LD_addr_A(wd1ee);
    CALL(aFunction1034be);
    CALL(aUpdateSprites);
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    LD_A(0x01);
    LD_addr_A(wd1f0);
    CALL(aFunction10339a);
    RET;

}

void Function103362(void){

asm_103362:
    LD_A_addr(wd1f0);
    LD_addr_A(wd1f1);
    CALL(aFunction1033af);
    CALL(aFunction10339a);
    CALL(aFunction10342c);
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    LD_A_addr(wd1eb);
    BIT_A(7);
    IF_Z goto asm_103362;
    LD_HL(wd1eb);
    BIT_hl(6);
    IF_Z goto asm_103398;
    LD_A(BANK(s4_a60c));
    CALL(aOpenSRAM);
    LD_A_addr(wd1ea);
    LD_addr_A(s4_a60c);
    LD_addr_A(wdc41);
    CALL(aCloseSRAM);
    XOR_A_A;
    RET;


asm_103398:
    SCF;
    RET;

}

void Function10339a(void){
    LD_A_addr(wd1f0);
    LD_addr_A(wd1f2);
    LD_C_A;
    LD_B(0);
    LD_HL(wd1ec);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wd1f3);
    RET;

}

void Function1033af(void){
    CALL(aGetJoypad);
    LDH_A_addr(hJoyPressed);
    BIT_A(D_LEFT_F);
    IF_NZ goto left;
    BIT_A(D_RIGHT_F);
    IF_NZ goto right;
    BIT_A(B_BUTTON_F);
    IF_NZ goto b;
    BIT_A(A_BUTTON_F);
    IF_NZ goto a;
    BIT_A(D_UP_F);
    IF_NZ goto up;
    BIT_A(D_DOWN_F);
    IF_NZ goto down;
    RET;


up:
    LD_A_addr(wd1f0);
    DEC_A;
    LD_addr_A(wd1f0);
    CP_A(1);
    RET_NC ;
    LD_A_addr(wd1ee);
    LD_addr_A(wd1f0);
    RET;


down:
    LD_A_addr(wd1f0);
    INC_A;
    LD_addr_A(wd1f0);
    LD_C_A;
    LD_A_addr(wd1ee);
    CP_A_C;
    RET_NC ;
    LD_A(1);
    LD_addr_A(wd1f0);
    RET;


b:
    CALL(aPlayClickSFX);
    LD_HL(wd1eb);
    SET_hl(7);
    RET;


a:
    LD_A_addr(wd1f3);
    CP_A(3);
    IF_NZ goto a_return;
    LD_DE(SFX_TRANSACTION);
    CALL(aPlaySFX);
    LD_HL(wd1eb);
    SET_hl(7);
    LD_HL(wd1eb);
    SET_hl(6);
    RET;


left:

right:

a_return:
    LD_A_addr(wd1f3);
    CP_A(3);
    RET_Z ;
    LD_DE(SFX_PUSH_BUTTON);
    CALL(aPlaySFX);
    LD_BC(8);
    CALL(aFunction10350f);
    LD_A_addr(wd1ea);
    XOR_A_E;
    LD_addr_A(wd1ea);
    RET;

}

void Function10342c(void){
    LD_A_addr(wd1f0);
    LD_addr_A(wd1f2);
    CALL(aFunction103490);
    CALL(aFunction10343c);
    CALL(aFunction1034a7);
    RET;

}

void Function10343c(void){
    LD_A_addr(wd1f3);
    CP_A(0x02);
    IF_NZ goto asm_103452;
    LD_BC(1);
    CALL(aFunction1034f7);
    LD_C(0x12);
    LD_B(0x01);
    CALL(aFunction1034e0);
    goto asm_10345f;


asm_103452:
    LD_BC(0xffed);
    CALL(aFunction1034f7);
    LD_C(0x12);
    LD_B(0x02);
    CALL(aFunction1034e0);


asm_10345f:
    LD_BC(0);
    CALL(aFunction10350f);
    LD_BC(1);
    CALL(aFunction103487);
    LD_BC(8);
    CALL(aFunction10350f);
    LD_A_addr(wd1ea);
    AND_A_E;
    LD_BC(2);
    IF_Z goto asm_10347d;
    LD_BC(4);


asm_10347d:
    CALL(aFunction10350f);
    LD_BC(11);
    CALL(aFunction103487);
    RET;

}

void Function103487(void){
    PUSH_DE;
    CALL(aFunction1034f7);
    POP_DE;
    CALL(aPlaceString);
    RET;

}

void Function103490(void){
    hlcoord(0, 15, wTilemap);
    LD_C(0x14);
    LD_B(0x03);
    CALL(aFunction1034e0);
    LD_BC(6);
    CALL(aFunction10350f);
    hlcoord(1, 16, wTilemap);
    CALL(aPlaceString);
    RET;

}

void Function1034a7(void){
    LD_A_addr(wd1f1);
    LD_addr_A(wd1f2);
    LD_BC(10);
    CALL(aFunction1034f7);
    LD_hl(0x7f);
    LD_BC(10);
    CALL(aFunction1034f1);
    LD_hl(0xed);
    RET;

}

void Function1034be(void){
    LD_A(0x01);
    LD_addr_A(wd1f2);
    LD_HL(wd1ec);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_hli;

asm_1034ca:
    PUSH_AF;
    LD_A_hli;
    PUSH_HL;
    LD_addr_A(wd1f3);
    CALL(aFunction10343c);
    LD_HL(wd1f2);
    INC_hl;
    POP_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_1034ca;
    CALL(aFunction103490);
    RET;

}

void Function1034e0(void){
    PUSH_BC;
    PUSH_HL;
    CALL(aClearBox);
    POP_HL;
    LD_BC(wAttrmap - wTilemap);
    ADD_HL_BC;
    POP_BC;
    LD_A(0x06);
    CALL(aFillBoxWithByte);
    RET;

}

void Function1034f1(void){
    LD_A_addr(wd1f0);
    LD_addr_A(wd1f2);

    return Function1034f7();
}

void Function1034f7(void){
    hlcoord(0, 0, wTilemap);
    ADD_HL_BC;
    LD_A_addr(wd1ef);
    LD_BC(SCREEN_WIDTH);
    CALL(aAddNTimes);
    LD_A_addr(wd1f2);
    DEC_A;
    LD_BC(40);
    CALL(aAddNTimes);
    RET;

}

void Function10350f(void){
    LD_A_addr(wd1f3);
    PUSH_BC;
    LD_HL(mUnknown_103522);
    LD_BC(9);
    CALL(aAddNTimes);
    POP_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_D_hl;
    LD_E_A;
    RET;

}

void Unknown_103522(void){
    //dw ['String_103546'];
    //dw ['String_103598'];
    //dw ['String_1035a0'];
    //dw ['String_10355f'];
    //db ['0x01'];
    //dw ['String_10354f'];
    //dw ['String_1035a8'];
    //dw ['String_1035b1'];
    //dw ['String_103571'];
    //db ['0x02'];
    //dw ['String_103557'];
    //dw ['String_1035ba'];
    //dw ['String_1035bd'];
    //dw ['String_103585'];
    //db ['0x04'];
    //dw ['String_103545'];
    //dw ['String_1035c1'];
    //dw ['String_1035c1'];
    //dw ['String_103545'];

    return String_103545();
}

void String_103545(void){
//db "@"
    return String_103546();
}

void String_103546(void){
//db "せんとう　アニメ@"
    return String_10354f();
}

void String_10354f(void){
//db "でんわばんごう@"
    return String_103557();
}

void String_103557(void){
//db "めいしこうかん@"
    return String_10355f();
}

void String_10355f(void){
//db "でんわを　かけるひとが　きめられる@"
    return String_103571();
}

void String_103571(void){
//db "でんわばんごうの　にゅうりょくのしかた@"
    return String_103585();
}

void String_103585(void){
//db "あたらしいめいしが　あれば　こうかん@"
    return String_103598();
}

void String_103598(void){
//db "とばして　みる@"
    return String_1035a0();
}

void String_1035a0(void){
//db "じっくり　みる@"
    return String_1035a8();
}

void String_1035a8(void){
//db "めいしからえらぶ@"
    return String_1035b1();
}

void String_1035b1(void){
//db "すうじで　いれる@"
    return String_1035ba();
}

void String_1035ba(void){
//db "する@"
    return String_1035bd();
}

void String_1035bd(void){
//db "しない@"
    return String_1035c1();
}

void String_1035c1(void){
//db "けってい@"

    return Function1035c6();
}

void Function1035c6(void){
    FARCALL(aFunction10138b);
    LD_B(0);
    LD_HL(mUnknown_1035d7);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    RET;

}

void Unknown_1035d7(void){
    //dw ['Unknown_1035e7'];
    //dw ['Unknown_1035f3'];
    //dw ['Unknown_103608'];
    //dw ['Unknown_103608'];
    //dw ['Unknown_1035fe'];
    //dw ['AskMobileOrCable'];
    //dw ['AskMobileOrCable'];
    //dw ['AskMobileOrCable'];

    return Unknown_1035e7();
}

void Unknown_1035e7(void){
    //dwcoord ['0', '6'];
    //db ['0x12', '0x07', '0x07'];
    //dw ['.this'];

this:
    //db ['4', '2', '1', '0', '3'];

    return Unknown_1035f3();
}

void Unknown_1035f3(void){
    //dwcoord ['0', '7'];
    //db ['0x12', '0x06', '0x09'];
    //dw ['.this'];

this:
    //db ['3', '2', '1', '3'];

    return Unknown_1035fe();
}

void Unknown_1035fe(void){
    //dwcoord ['0', '9'];
    //db ['0x12', '0x04', '0x0b'];
    //dw ['.this'];

this:
    //db ['2', '0', '3'];

    return Unknown_103608();
}

void Unknown_103608(void){
    //dwcoord ['0', '9'];
    //db ['0x12', '0x04', '0x0b'];
    //dw ['.this'];

// this:
    //db ['2', '2', '3'];
}

void AskMobileOrCable(void){
    // LD_HL(mMenuHeader_103640);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_103640);
    // LD_A_addr(wMobileOrCable_LastSelection);
    // AND_A(0x0f);
    // IF_Z goto skip_load;
    if((wram->wMobileOrCable_LastSelection & 0x0f) != 0){
        // LD_addr_A(wMenuCursorPosition);
        wram->wMenuCursorPosition = wram->wMobileOrCable_LastSelection & 0x0f;
    }

// skip_load:
    // CALL(aVerticalMenu);
    bool cancel = !VerticalMenu_Conv();
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
    // IF_C goto pressed_b;
    if(cancel){
    // pressed_b:
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x0;
        // RET;
        return;
    }
    // LD_A_addr(wMenuCursorY);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wMenuCursorY;
    // LD_C_A;
    // LD_A_addr(wMobileOrCable_LastSelection);
    // AND_A(0xf0);
    // OR_A_C;
    // LD_addr_A(wMobileOrCable_LastSelection);
    wram->wMobileOrCable_LastSelection = (wram->wMobileOrCable_LastSelection & 0xf0) | wram->wMenuCursorY;
    // RET;
}

const struct MenuData MenuData_103648 = {
    .flags = STATICMENU_CURSOR,  // flags
    .verticalMenu = {
        .count = 2,
        .options = (const char*[]){
            "NETWORK", //db ['"モバイル@"'];
            "LAN", //db ['"ケーブル@"'];
        },
    },
};

const struct MenuHeader MenuHeader_103640 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(13, 6, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['MenuData_103648'];
    .data = &MenuData_103648,
    .defaultOption = 1,  // default option
};

void Function103654(void){
    FARCALL(aMobile_AlwaysReturnNotCarry);
    BIT_C(7);
    IF_NZ goto asm_103666;
    LD_HL(wcd2a);
    RES_hl(5);
    LD_C(0x02);
    RET;


asm_103666:
    LD_HL(wcd2a);
    SET_hl(5);
    LD_C(0x01);
    RET;

}

void Mobile_SelectThreeMons(void){
    // FARCALL(aMobile_AlwaysReturnNotCarry);
    u8_flag_s res = Mobile_AlwaysReturnNotCarry();
    // BIT_C(7);
    // IF_Z goto asm_10369b;
    if(bit_test(res.a, 7)){
        // LD_HL(mMobileBattleMustPickThreeMonText);
        // CALL(aPrintText);
        PrintText_Conv2(MobileBattleMustPickThreeMonText);
        // CALL(aYesNoBox);
        // IF_C goto asm_103696;
        if(YesNoBox_Conv()){
            // FARCALL(aCheckForMobileBattleRules);
            // IF_NC goto asm_103690;
            if(!CheckForMobileBattleRules()){
            // asm_103690:
                // LD_A(0x01);
                // LD_addr_A(wScriptVar);
                wram->wScriptVar = 0x01;
                // RET;
                return;
            }
            // CALL(aJoyWaitAorB);
            // goto asm_103696;
            JoyWaitAorB_Conv();
        }

    // asm_103696:
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x00;
        // RET;
        return;
    }
    else {
    // asm_10369b:
        // LD_HL(wMobileOrCable_LastSelection);
        // BIT_hl(7);
        bool test = bit_test(wram->wMobileOrCable_LastSelection, 7) != 0;
        // SET_hl(7);
        bit_set(wram->wMobileOrCable_LastSelection, 7);
        // IF_NZ goto asm_1036b5;
        if(!test){
            // LD_HL(mMobileBattleMoreInfoText);
            // CALL(aPrintText);
            PrintText_Conv2(MobileBattleMoreInfoText);
            // CALL(aYesNoBox);
            // IF_C goto asm_1036b5;
            if(YesNoBox_Conv()){
                // CALL(aFunction1036f9);
                Function1036f9();
                // CALL(aJoyWaitAorB);
                JoyWaitAorB_Conv();
            }
        }

        while(!Function103700()){
        // asm_1036b5:
            // CALL(aFunction103700);
            // IF_C goto asm_1036f4;
            // LD_HL(mMenuHeader_103747);
            // CALL(aLoadMenuHeader);
            LoadMenuHeader_Conv2(&MenuHeader_103747);
            // CALL(aVerticalMenu);
            bool quit = !VerticalMenu_Conv();
            // CALL(aExitMenu);
            ExitMenu_Conv2();
            // IF_C goto asm_1036f4;
            if(quit)
                break;
            // LD_A_addr(wMenuCursorY);
            // CP_A(0x01);
            // IF_Z goto asm_1036d9;
            if(wram->wMenuCursorY == 0x01){
            // asm_1036d9:
                // FARCALL(aCheckForMobileBattleRules);
                // IF_NC goto asm_1036e6;
                if(!CheckForMobileBattleRules()){
                // asm_1036e6:
                    // LD_A(0x01);
                    // LD_addr_A(wScriptVar);
                    wram->wScriptVar = TRUE;
                    // RET;
                    return;
                }
                // CALL(aJoyWaitAorB);
                JoyWaitAorB_Conv();
                // goto asm_1036f4;
                break;
            }
            // CP_A(0x02);
            // IF_Z goto asm_1036f4;
            else if(wram->wMenuCursorY == 0x02)
                break;
            // CP_A(0x03);
            // IF_Z goto asm_1036ec;
            else if(wram->wMenuCursorY == 0x03){
            // asm_1036ec:
                // CALL(aFunction1036f9);
                Function1036f9();
                // CALL(aJoyWaitAorB);
                JoyWaitAorB_Conv();
                // goto asm_1036b5;
                continue;
            }
            // goto asm_1036b5;
        }

    // asm_1036f4:
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = FALSE;
        // RET;
        return;
    }
}

// Mobile_PrintBattleRules
void Function1036f9(void){
    // LD_HL(mMobileBattleRulesText);
    // CALL(aPrintText);
    PrintText_Conv2(MobileBattleRulesText);
    // RET;
}

// Mobile_CheckRemainingTime
bool Function103700(void){
    // LD_C(10);
    uint8_t c = 10;
    // LD_HL(wSwarmFlags);
    // BIT_hl(SWARMFLAGS_MOBILE_4_F);
    // IF_Z goto asm_10370f;
    if(bit_test(wram->wSwarmFlags, SWARMFLAGS_MOBILE_4_F)){
        // FARCALL(aMobileBattleGetRemainingTime);
        c = MobileBattleGetRemainingTime().b;
    }

// asm_10370f:
    // LD_A_C;
    // LD_addr_A(wStringBuffer2);
    wram->wStringBuffer2[0] = c;
    // LD_A_addr(wStringBuffer2);
    // CP_A(5);
    // IF_NC goto five_or_more_mins;
    if(c >= 5){
    // five_or_more_mins:
        // LD_HL(mWouldYouLikeToMobileBattleText);
        // CALL(aPrintText);
        PrintText_Conv2(WouldYouLikeToMobileBattleText);
        // AND_A_A;
        // RET;
        return false;
    }
    // CP_A(2);
    // IF_NC goto two_to_five_mins;
    else if(c >= 2){
    // two_to_five_mins:
        // LD_HL(mWantAQuickMobileBattleText);
        // CALL(aPrintText);
        PrintText_Conv2(WantAQuickMobileBattleText);
        // AND_A_A;
        // RET;
        return false;
    }
    // CP_A(1);
    // IF_NC goto one_min;
    else if(c >= 1){
    // one_min:
        // LD_HL(mWantToRushThroughAMobileBattleText);
        // CALL(aPrintText);
        PrintText_Conv2(WantToRushThroughAMobileBattleText);
        // AND_A_A;
        // RET;
        return false;
    }
    // goto times_up;
    else {
    // times_up:
        // LD_HL(mPleaseTryAgainTomorrowText);
        // CALL(aPrintText);
        PrintText_Conv2(PleaseTryAgainTomorrowText);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB_Conv();
        // SCF;
        // RET;
        return true;
    }
}

const struct MenuData MenuData_10374f = {
    .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
    .verticalMenu = {
        .count = 3,
        .options = (const char*[]){
            "YES",  // "はい@"
            "NO",   // "やめる@"
            "INFO", // "せつめい@"
        },
    },
};

const struct MenuHeader MenuHeader_103747 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(13, 5, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    //dw ['MenuData_10374f'];
    .data = &MenuData_10374f,
    .defaultOption = 1,  // default option
};

const txt_cmd_s MobileBattleMustPickThreeMonText[] = {
    text_far(v_MobileBattleMustPickThreeMonText)
    text_end
};

const txt_cmd_s MobileBattleMoreInfoText[] = {
    text_far(v_MobileBattleMoreInfoText)
    text_end
};

const txt_cmd_s MobileBattleRulesText[] = {
    text_far(v_MobileBattleRulesText)
    text_end
};

const txt_cmd_s WouldYouLikeToMobileBattleText[] = {
    text_far(v_WouldYouLikeToMobileBattleText)
    text_end
};

const txt_cmd_s WantAQuickMobileBattleText[] = {
    text_far(v_WantAQuickMobileBattleText)
    text_end
};

const txt_cmd_s WantToRushThroughAMobileBattleText[] = {
    text_far(v_WantToRushThroughAMobileBattleText)
    text_end
};

const txt_cmd_s PleaseTryAgainTomorrowText[] = {
    text_far(v_PleaseTryAgainTomorrowText)
    text_end
};

void Function103780(void){
    LD_A_addr(wChosenCableClubRoom);
    PUSH_AF;
    CALL(aFunction10378c);
    POP_AF;
    LD_addr_A(wChosenCableClubRoom);
    RET;

}

void Function10378c(void){
    LD_C(0);
    LD_HL(wSwarmFlags);
    BIT_hl(SWARMFLAGS_MOBILE_4_F);
    IF_NZ goto already_set;
    LD_C(1);
    LD_HL(wSwarmFlags);
    SET_hl(SWARMFLAGS_MOBILE_4_F);


already_set:
    PUSH_BC;
    FARCALL(aLink_SaveGame);
    POP_BC;
    IF_C goto failed_to_save;
    LD_A(1);
    LD_addr_A(wScriptVar);
    LD_A_C;
    AND_A_A;
    RET_Z ;
    FARCALL(aMobileBattleResetTimer);
    RET;


failed_to_save:
    XOR_A_A;
    LD_addr_A(wScriptVar);
    LD_A_C;
    AND_A_A;
    RET_Z ;
    LD_HL(wSwarmFlags);
    RES_hl(SWARMFLAGS_MOBILE_4_F);
    RET;

}

void Function1037c2(void){
    CALL(aMobileCheckRemainingBattleTime);
    IF_C goto nope;
    LD_A_addr(wdc5f);
    AND_A_A;
    IF_Z goto nope;
    LD_HL(mTryAgainUsingSameSettingsText);
    CALL(aPrintText);
    CALL(aYesNoBox);
    IF_C goto nope;
    LD_A(0x01);
    LD_addr_A(wScriptVar);
    RET;


nope:
    XOR_A_A;
    LD_addr_A(wdc5f);
    LD_addr_A(wScriptVar);
    RET;

}

void TryAgainUsingSameSettingsText(void){
    //text_far ['_TryAgainUsingSameSettingsText']
    //text_end ['?']

    return Function1037eb();
}

// CheckAbleToMobileBattle
//  wScriptVar == 0x0 -> Don't connect
//  wScriptVar == 0x1 -> Can connect
//  wScriptVar == 0x2 -> Already connected
void Function1037eb(void){
    // CALL(aMobileCheckRemainingBattleTime);
    // IF_NC goto asm_103807;
    if(MobileCheckRemainingBattleTime()) {
        // LD_HL(mMobileBattleLessThanOneMinuteLeftText);
        // CALL(aPrintText);
        PrintText_Conv2(MobileBattleLessThanOneMinuteLeftText);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB_Conv();
        // LD_HL(mMobileBattleNoTimeLeftForLinkingText);
        // CALL(aPrintText);
        PrintText_Conv2(MobileBattleNoTimeLeftForLinkingText);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB_Conv();
        // XOR_A_A;
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x0;
        // RET;
        return;
    }

// asm_103807:
    // LD_A_addr(wdc60);
    // AND_A_A;
    // IF_NZ goto asm_103813;
    else if(wram->wdc60 == 0) {
        // LD_A(0x01);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x1;
        // RET;
        return;
    }
    else {
    // asm_103813:
        // LD_A(0x02);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x2;
        // RET;
        return;
    }
}

const txt_cmd_s MobileBattleLessThanOneMinuteLeftText[] = {
    text_far(v_MobileBattleLessThanOneMinuteLeftText)
    text_end
};

const txt_cmd_s MobileBattleNoTimeLeftForLinkingText[] = {
    text_far(v_MobileBattleNoTimeLeftForLinkingText)
    text_end
};

//  Returns carry if less than one minute remains
bool MobileCheckRemainingBattleTime(void){
    // FARCALL(aMobile_AlwaysReturnNotCarry);
    u8_flag_s res = Mobile_AlwaysReturnNotCarry();
    // BIT_C(7);
    // IF_NZ goto ok;
    if(bit_test(res.a, 7))
        return false;
    // FARCALL(aMobileBattleGetRemainingTime);
    u8_pair_s time = MobileBattleGetRemainingTime();
    // LD_A_C;
    // CP_A(1);
    // IF_C goto fail;
    if(time.a < 1)
        return true;

// ok:
    // XOR_A_A;
    // RET;
    return false;

// fail:
    // SCF;
    // RET;
}

void Function10383c(void){
    LD_A(0x01);
    LD_addr_A(wdc60);
    XOR_A_A;
    LD_HL(wPlayerMonSelection);
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    LD_HL(mPickThreeMonForMobileBattleText);
    CALL(aPrintText);
    CALL(aJoyWaitAorB);
    FARCALL(aScript_reloadmappart);
    FARCALL(aFunction4a94e);
    IF_C goto asm_103870;
    LD_HL(wd002);
    LD_DE(wPlayerMonSelection);
    LD_BC(3);
    CALL(aCopyBytes);
    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;


asm_103870:
    LD_A(0x01);
    LD_addr_A(wScriptVar);
    RET;

}

void PickThreeMonForMobileBattleText(void){
    //text_far ['_PickThreeMonForMobileBattleText']
    //text_end ['?']

    return Function10387b();
}

void Function10387b(void){
    FARCALL(aMobile_AlwaysReturnNotCarry);
    BIT_C(7);
    RET_NZ ;
    FARCALL(aMobileBattleGetRemainingTime);
    LD_A_C;
    LD_addr_A(wStringBuffer2);
    LD_HL(mMobileBattleRemainingTimeText);
    CALL(aPrintText);
    CALL(aJoyWaitAorB);
    RET;

}

void MobileBattleRemainingTimeText(void){
    //text_far ['_MobileBattleRemainingTimeText']
    //text_end ['?']

}
