#include "../constants.h"
#include "mobile_5e.h"

const char MobileCardGFX[] = "gfx/mobile/card.png";
const char ChrisSilhouetteGFX[] = "gfx/mobile/chris_silhouette.png";
const char KrisSilhouetteGFX[] = "gfx/mobile/kris_silhouette.png";
const char MobileCard2GFX[] = "gfx/mobile/card_2.png";

// void CardLargeSpriteAndFolderGFX(void){
// INCBIN "gfx/mobile/card_large_sprite.2bpp"
// INCBIN "gfx/mobile/card_folder.2bpp"
// }
const char CardLargeSpriteGFX[] = "gfx/mobile/card_large_sprite.png";
const char CardFolderGFX[] = "gfx/mobile/card_folder.png";

const char CardSpriteGFX[] = "gfx/mobile/card_sprite.png";

void Function17a68f(void){
    CALL(aFunction17a6a8);
    CALL(aFunction17a751);
    LD_HL(0xd088);
    BIT_hl(5);
    IF_Z goto asm_17a6a6;
    LD_DE(wStringBuffer1);
    PUSH_DE;
    CALL(aFunction17a721);
    POP_DE;
    XOR_A_A;
    RET;


asm_17a6a6:
    SCF;
    RET;

}

void Function17a6a8(void){
    PUSH_DE;
    PUSH_BC;
    LD_HL(wStringBuffer2);
    LD_BC(0xa);
    XOR_A_A;
    CALL(aByteFill);
    LD_HL(wd1ea);
    LD_BC(0x10);
    LD_A(0xff);
    CALL(aByteFill);
    POP_BC;
    LD_A_C;
    AND_A_A;
    IF_Z goto asm_17a6c9;
    LD_HL(0xd088);
    SET_hl(4);

asm_17a6c9:
    POP_DE;
    CALL(aFunction17a6f5);
    CALL(aFunction17aba0);
    FARCALL(aFunction106464);
    CALL(aFunction17ac0c);
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    CALL(aFunction17abcf);
    FARCALL(aLoadOW_BGPal7);
    FARCALL(aFunction49420);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    RET;

}

void Function17a6f5(void){
    LD_HL(wd1ea);
    LD_C(0x0);
    LD_B(0x8);

asm_17a6fc:
    LD_A_de;
    CALL(aFunction17a713);
    IF_C goto asm_17a70e;
    LD_A_de;
    SWAP_A;
    CALL(aFunction17a713);
    IF_C goto asm_17a70e;
    INC_DE;
    DEC_B;
    IF_NZ goto asm_17a6fc;

asm_17a70e:
    LD_A_C;
    LD_addr_A(0xd08c);
    RET;

}

void Function17a713(void){
    AND_A(0xf);
    CP_A(0xa);
    IF_NC goto asm_17a71d;
    LD_hli_A;
    INC_C;
    AND_A_A;
    RET;


asm_17a71d:
    LD_hl(0xff);
    SCF;
    RET;

}

void Function17a721(void){
    PUSH_DE;
    LD_H_D;
    LD_L_E;
    LD_BC(0x8);
    LD_A(0xff);
    CALL(aByteFill);
    POP_DE;
    LD_HL(wd1ea);
    LD_B(0x8);

asm_17a732:
    LD_C(0x0);
    LD_A_hli;
    CP_A(0xa);
    IF_NC goto asm_17a748;
    LD_C_A;
    LD_A_hli;
    CP_A(0xa);
    IF_NC goto asm_17a74c;
    SWAP_A;
    OR_A_C;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto asm_17a732;
    RET;


asm_17a748:
    LD_A(0xff);
    LD_de_A;
    RET;


asm_17a74c:
    LD_A(0xf0);
    OR_A_C;
    LD_de_A;
    RET;

}

void Function17a751(void){
    XOR_A_A;
    LD_addr_A(0xd087);

asm_17a755:
    CALL(aFunction17a781);
    CALL(aFunction17a7ae);
    CALL(aFunction17a97b);
    CALL(aFunction17a770);
    CALL(aFunction17a78f);
    LD_HL(0xd08f);
    INC_hl;
    LD_A_addr(0xd087);
    BIT_A(7);
    IF_Z goto asm_17a755;
    RET;

}

void Function17a770(void){
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hOAMUpdate);
    CALL(aHideSprites);
    CALL(aFunction17a9cb);
    POP_AF;
    LDH_addr_A(hOAMUpdate);
    RET;

}

void Function17a781(void){
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    CALL(aJoyTextDelay);
    POP_AF;
    LDH_addr_A(hInMenu);
    RET;

}

void Function17a78f(void){
    LD_HL(0xd088);
    BIT_hl(7);
    RES_hl(7);
    IF_NZ goto asm_17a79f;
    FARCALL(aHDMATransferTilemapToWRAMBank3);
    RET;


asm_17a79f:
    FARCALL(aReloadMapPart);
    RET;

}

void Function17a7a6(void){
//  //  unreferenced
    LD_A_addr(0xd087);
    INC_A;
    LD_addr_A(0xd087);
    RET;

}

void Function17a7ae(void){
    LD_A_addr(0xd087);
    LD_HL(mJumptable_17a7b6);
    RST(aJumpTable);
    RET;

}

void Jumptable_17a7b6(void){
    //dw ['Function17a7c2'];
    //dw ['Function17a7cd'];
    //dw ['Function17a7d8'];
    //dw ['Function17a7ff'];
    //dw ['Function17a81a'];
    //dw ['Function17a7f4'];

    return Function17a7c2();
}

void Function17a7c2(void){
    LD_A(0x4);
    CALL(aFunction17aad3);
    LD_A(0x1);
    LD_addr_A(0xd087);
    RET;

}

void Function17a7cd(void){
    CALL(aFunction17a83c);
    CALL(aFunction17a8ae);
    RET_C ;
    CALL(aFunction17a848);
    RET;

}

void Function17a7d8(void){
    CALL(aFunction17a83c);
    CALL(aFunction17a848);
    LD_HL(0xd08b);
    DEC_hl;
    RET_NZ ;
    CALL(aFunction17ac1d);
    CALL(aFunction17ac2a);
    LD_HL(0xd088);
    SET_hl(7);
    LD_A(0x1);
    LD_addr_A(0xd087);
    RET;

}

void Function17a7f4(void){
    LD_HL(0xd08b);
    DEC_hl;
    RET_NZ ;
    LD_HL(0xd087);
    SET_hl(7);
    RET;

}

void Function17a7ff(void){
    LD_HL(0xd08b);
    DEC_hl;
    RET_NZ ;
    CALL(aFunction17ac1d);
    CALL(aFunction17ac2a);
    LD_HL(0xd088);
    SET_hl(7);
    LD_HL(0xd088);
    SET_hl(5);
    LD_HL(0xd087);
    SET_hl(7);
    RET;

}

void Function17a81a(void){
    CALL(aIsSFXPlaying);
    RET_NC ;
    LDH_A_addr(hJoyPressed);
    AND_A(0x3);
    RET_Z ;
    CALL(aExitMenu);
    CALL(aFunction17ac1d);
    CALL(aFunction17ac2a);
    LD_HL(0xd088);
    SET_hl(7);
    LD_HL(0xd088);
    RES_hl(6);
    LD_A(0x1);
    LD_addr_A(0xd087);
    RET;

}

void Function17a83c(void){
    LDH_A_addr(hJoyLast);
    AND_A(0xf0);
    LD_C_A;
    LDH_A_addr(hJoyPressed);
    AND_A(0xb);
    OR_A_C;
    LD_C_A;
    RET;

}

void Function17a848(void){
    LD_A_C;
    AND_A(0x60);
    CP_A(0x60);
    IF_Z goto asm_17a876;
    LD_A_C;
    AND_A(0x50);
    CP_A(0x50);
    IF_Z goto asm_17a87d;
    LD_A_C;
    AND_A(0xa0);
    CP_A(0xa0);
    IF_Z goto asm_17a884;
    LD_A_C;
    AND_A(0x90);
    CP_A(0x90);
    IF_Z goto asm_17a88b;
    BIT_C(6);
    IF_NZ goto asm_17a892;
    BIT_C(7);
    IF_NZ goto asm_17a899;
    BIT_C(5);
    IF_NZ goto asm_17a8a0;
    BIT_C(4);
    IF_NZ goto asm_17a8a7;
    XOR_A_A;
    RET;


asm_17a876:
    LD_A(0x9);
    CALL(aFunction17aad0);
    SCF;
    RET;


asm_17a87d:
    LD_A(0xa);
    CALL(aFunction17aad0);
    SCF;
    RET;


asm_17a884:
    LD_A(0xb);
    CALL(aFunction17aad0);
    SCF;
    RET;


asm_17a88b:
    LD_A(0xc);
    CALL(aFunction17aad0);
    SCF;
    RET;


asm_17a892:
    LD_A(0x5);
    CALL(aFunction17aad0);
    SCF;
    RET;


asm_17a899:
    LD_A(0x6);
    CALL(aFunction17aad0);
    SCF;
    RET;


asm_17a8a0:
    LD_A(0x7);
    CALL(aFunction17aad0);
    SCF;
    RET;


asm_17a8a7:
    LD_A(0x8);
    CALL(aFunction17aad0);
    SCF;
    RET;

}

void Function17a8ae(void){
    BIT_C(1);
    IF_NZ goto asm_17a8bc;
    BIT_C(0);
    IF_NZ goto asm_17a8cc;
    BIT_C(3);
    IF_NZ goto asm_17a8d7;
    XOR_A_A;
    RET;


asm_17a8bc:
    LD_A(0xb);
    LD_addr_A(0xd08a);
    CALL(aFunction17aa98);
    CALL(aFunction17a943);
    CALL(aFunction17aa88);
    SCF;
    RET;


asm_17a8cc:
    CALL(aFunction17aad7);
    CALL(aFunction17aa98);
    CALL(aFunction17a8de);
    SCF;
    RET;


asm_17a8d7:
    LD_A(0xc);
    CALL(aFunction17aad3);
    SCF;
    RET;

}

void Function17a8de(void){
    LD_A(0x2);
    CALL(aFunction17aae0);
    LD_A_hl;
    CP_A(0xf1);
    IF_Z goto asm_17a8fd;
    CP_A(0xf0);
    IF_Z goto asm_17a904;
    CP_A(0xf2);
    IF_Z goto asm_17a911;
    LD_E_A;
    CALL(aFunction17a964);
    LD_A(0x2);
    LD_addr_A(0xd087);
    CALL(aFunction17aa88);
    RET;


asm_17a8fd:
    CALL(aFunction17a943);
    CALL(aFunction17aa88);
    RET;


asm_17a904:
    CALL(aFunction17aad7);
    CALL(aFunction17aa98);
    CALL(aFunction17a91e);
    CALL(aFunction17aa88);
    RET;


asm_17a911:
    CALL(aFunction17aa98);
    LD_A(0x5);
    LD_addr_A(0xd087);
    XOR_A_A;
    CALL(aFunction17aa88);
    RET;

}

void Function17a91e(void){
    LD_A_addr(0xd08c);
    CP_A(0x7);
    IF_C goto asm_17a92c;
    LD_A(0x3);
    LD_addr_A(0xd087);
    XOR_A_A;
    RET;


asm_17a92c:
    CALL(aLoadStandardMenuHeader);
    CALL(aFunction17a99e);
    LD_HL(0xd088);
    SET_hl(7);
    LD_HL(0xd088);
    SET_hl(6);
    LD_A(0x4);
    LD_addr_A(0xd087);
    SCF;
    RET;

}

void Function17a943(void){
    LD_A_addr(0xd08c);
    AND_A_A;
    IF_Z goto asm_17a95d;
    DEC_A;
    LD_addr_A(0xd08c);
    LD_C_A;
    LD_B(0);
    LD_HL(wd1ea);
    ADD_HL_BC;
    LD_hl(0xff);
    LD_A(0x2);
    LD_addr_A(0xd087);
    AND_A_A;
    RET;


asm_17a95d:
    LD_A(0x5);
    LD_addr_A(0xd087);
    XOR_A_A;
    RET;

}

void Function17a964(void){
    LD_A_addr(0xd08c);
    CP_A(0x10);
    IF_NC goto asm_17a979;
    LD_C_A;
    LD_B(0);
    INC_A;
    LD_addr_A(0xd08c);
    LD_HL(wd1ea);
    ADD_HL_BC;
    LD_hl_E;
    AND_A_A;
    RET;


asm_17a979:
    SCF;
    RET;

}

void Function17a97b(void){
    hlcoord(1, 1, wTilemap);
    LD_BC((2 << 8) | 18);
    CALL(aClearBox);
    hlcoord(3, 2, wTilemap);
    LD_DE(wd1ea);
    LD_A_addr(0xd08c);
    AND_A_A;
    RET_Z ;
    LD_C_A;

asm_17a990:
    LD_A_de;
    INC_DE;
    CP_A(0xa);
    IF_NC goto asm_17a99d;
    ADD_A(0xf6);
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_17a990;
    RET;


asm_17a99d:
    RET;

}

void Function17a99e(void){
    hlcoord(0, 12, wTilemap);
    LD_B(0x4);
    LD_C(0x12);
    CALL(aFunction17ac46);
    hlcoord(2, 14, wTilemap);
    LD_DE(mString_17a9b2);
    CALL(aPlaceString);
    RET;

}

void String_17a9b2(void){
    //db ['"でんわばんごうが\u3000ただしく"'];
    //next ['"はいって\u3000いません！"']
    //db ['"@"'];

    return Function17a9cb();
}

void Function17a9cb(void){
    LD_DE(wVirtualOAM);
    LD_HL(0xd088);
    BIT_hl(6);
    IF_NZ goto bit_6_set;
    CALL(aFunction17a9e3);
    CALL(aFunction17aa22);
    CALL(aFunction17a9f5);
    RET;


bit_6_set:
    CALL(aFunction17a9e3);
    RET;

}

void Function17a9e3(void){
    LD_A(0x3);
    LD_addr_A(0xd08e);
    LD_HL(mUnknown_17aa77);
    LD_B(0x8);
    LD_C(0x8);
    LD_A(0x5);
    CALL(aFunction17aa4a);
    RET;

}

void Function17a9f5(void){
    LD_A_addr(0xd08c);
    CP_A(0x10);
    RET_NC ;
    LD_A_addr(0xd08f);
    SWAP_A;
    AND_A(0x1);
    ADD_A(0x1);
    LD_addr_A(0xd08e);
    LD_A_addr(0xd08c);
    CP_A(0x10);
    IF_C goto okay;
    DEC_A;

okay:
    LD_C(0x8);
    CALL(aSimpleMultiply);
    ADD_A(0x18);
    LD_B_A;
    LD_C(0x11);
    LD_HL(mUnknown_17aa72);
    LD_A(0x4);
    CALL(aFunction17aa4a);
    RET;

}

void Function17aa22(void){
    LD_A(0x0);
    LD_addr_A(0xd08e);
    PUSH_DE;
    LD_A(0x3);
    CALL(aFunction17aae0);
    ADD_A_A;
    ADD_A_A;
    ADD_A_A;
    ADD_A(0x0);
    PUSH_AF;
    LD_A(0x4);
    CALL(aFunction17aae0);
    ADD_A_A;
    ADD_A_A;
    ADD_A_A;
    ADD_A(0x8);
    LD_C_A;
    POP_AF;
    LD_B_A;
    POP_DE;
    LD_A(0x0);
    LD_HL(mUnknown_17aa77);
    CALL(aFunction17aa4a);
    RET;

}

void Function17aa4a(void){
    LD_addr_A(0xd08d);
    LD_A_B;
    ADD_A(0x8);
    LD_B_A;
    LD_A_C;
    ADD_A(0x10);
    LD_C_A;
    LD_A_hli;

loop:
    PUSH_AF;
    LD_A_hli;
    ADD_A_C;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    ADD_A_B;
    LD_de_A;
    INC_DE;
    LD_A_addr(0xd08d);
    ADD_A_hl;
    INC_HL;
    LD_de_A;
    INC_DE;
    LD_A_addr(0xd08e);
    OR_A_hl;
    INC_HL;
    LD_de_A;
    INC_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;
    RET;

}

void Unknown_17aa72(void){
    //db ['1'];
    //db ['0', '0', '0', '0'];

    return Unknown_17aa77();
}

void Unknown_17aa77(void){
    //db ['4'];
    //db ['0', '0', '0', '0'];
    //db ['0', '8', '1', '0'];
    //db ['8', '0', '2', '0'];
    //db ['8', '8', '3', '0'];

    return Function17aa88();
}

void Function17aa88(void){
    JR_C (masm_17aa91);
    LD_DE(SFX_SWITCH_POKEMON);
    CALL(aPlaySFX);
    RET;

}

void asm_17aa91(void){
    LD_DE(SFX_WRONG);
    CALL(aPlaySFX);
    RET;

}

void Function17aa98(void){
    LD_A(0x5);
    LD_addr_A(0xd08b);
    CALL(aFunction17aaa9);
    CALL(aFunction17aac3);
    LD_HL(0xd088);
    SET_hl(7);
    RET;

}

void Function17aaa9(void){
    LD_A(0x3);
    CALL(aFunction17aae3);
    LD_C_A;
    LD_B(0);
    hlcoord(0, 0, wAttrmap);
    ADD_HL_BC;
    PUSH_HL;
    LD_A(0x4);
    CALL(aFunction17aae3);
    LD_BC(0x14);
    POP_HL;
    CALL(aAddNTimes);
    RET;

}

void Function17aac3(void){
    LD_A(0xb);
    PUSH_HL;
    LD_hli_A;
    LD_hli_A;
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    LD_hli_A;
    LD_hli_A;
    RET;

}

void Function17aad0(void){
    CALL(aFunction17aae0);

    return Function17aad3();
}

void Function17aad3(void){
    LD_addr_A(0xd089);
    RET;

}

void Function17aad7(void){
    PUSH_AF;
    LD_A_addr(0xd089);
    LD_addr_A(0xd08a);
    POP_AF;
    RET;

}

void Function17aae0(void){
    CALL(aFunction17aad7);

    return Function17aae3();
}

void Function17aae3(void){
    PUSH_AF;
    LD_A_addr(0xd08a);
    LD_BC(0xd);
    LD_HL(mUnknown_17aaf7);
    CALL(aAddNTimes);
    POP_AF;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    RET;

}

void Unknown_17aaf7(void){
    //db ['0x0', '0x0', '0x1', '0x6', '0x5', '0x9', '0x3', '0x2', '0x1', '0x2', '0x1', '0x2', '0x4'];
    //db ['0x0', '0x0', '0x2', '0x9', '0x5', '0xa', '0x4', '0x0', '0x2', '0xa', '0xa', '0x3', '0x5'];
    //db ['0x0', '0x0', '0x3', '0xc', '0x5', '0xb', '0x5', '0x1', '0x0', '0x1', '0x0', '0x4', '0x0'];
    //db ['0x0', '0x0', '0x4', '0x6', '0x8', '0x0', '0x6', '0x5', '0x4', '0x5', '0x1', '0x5', '0x7'];
    //db ['0x0', '0x0', '0x5', '0x9', '0x8', '0x1', '0x7', '0x3', '0x5', '0x0', '0x2', '0x6', '0x8'];
    //db ['0x0', '0x0', '0x6', '0xc', '0x8', '0x2', '0x8', '0x4', '0x3', '0x1', '0x3', '0x7', '0x3'];
    //db ['0x0', '0x0', '0x7', '0x6', '0xb', '0x3', '0x9', '0x8', '0x7', '0x8', '0x4', '0x8', '0xa'];
    //db ['0x0', '0x0', '0x8', '0x9', '0xb', '0x4', '0xa', '0x6', '0x8', '0x3', '0x5', '0x9', '0xb'];
    //db ['0x0', '0x0', '0x9', '0xc', '0xb', '0x5', '0xb', '0x7', '0x6', '0x4', '0x6', '0xa', '0x6'];
    //db ['0x0', '0x0', '0xf2', '0x6', '0xe', '0x6', '0x0', '0xc', '0xa', '0xc', '0x7', '0xc', '0x0'];
    //db ['0x0', '0x0', '0x0', '0x9', '0xe', '0x7', '0x1', '0x9', '0xb', '0x6', '0x8', '0x1', '0x1'];
    //db ['0x0', '0x0', '0xf1', '0xc', '0xe', '0x8', '0x2', '0xa', '0xc', '0x7', '0xc', '0x2', '0xc'];
    //db ['0x0', '0x0', '0xf0', '0x10', '0xe', '0xc', '0xc', '0xb', '0x9', '0xb', '0x9', '0xb', '0x9'];

    return Function17aba0();
}

void Function17aba0(void){
    LDH_A_addr(rVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rVBK);

    LD_HL(vTiles5 + LEN_2BPP_TILE * 0x00);
    LD_DE(mDialpadGFX);
    LD_BC((BANK(aDialpadGFX) << 8) | 0x80);  // includes first 4 tiles of DialpadCursorGFX
    CALL(aGet2bpp);

    POP_AF;
    LDH_addr_A(rVBK);

    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
    LD_DE(mDialpadCursorGFX);
    LD_BC((BANK(aDialpadCursorGFX) << 8) | 5);
    CALL(aGet2bpp);

    LD_HL(vTiles0 + LEN_2BPP_TILE * 0x05);
    LD_DE(mMobileDialingGFX);
    LD_BC((BANK(aMobileDialingGFX) << 8) | 4);
    CALL(aGet2bpp);
    RET;

}

void Function17abcf(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(BANK(wBGPals1));
    LDH_addr_A(rSVBK);

    LD_HL(mPalette_17ac55);
    LD_DE(wBGPals1);
    LD_BC(6 * PALETTE_SIZE);
    CALL(aCopyBytes);

    LD_HL(mPalette_17ac95);
    LD_DE(wOBPals1);
    LD_BC(8 * PALETTE_SIZE);
    CALL(aCopyBytes);

    LD_HL(mPalette_17b4b5);
    LD_DE(wOBPals1 + PALETTE_SIZE * 1);
    LD_BC(2 * PALETTE_SIZE);
    CALL(aCopyBytes);

    LD_HL(mMapObjectPals + PALETTE_SIZE * 1);
    LD_DE(wOBPals1 + PALETTE_SIZE * 3);
    LD_BC(1 * PALETTE_SIZE);
    LD_A(BANK(aMapObjectPals));
    CALL(aFarCopyBytes);

    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function17ac0c(void){
    CALL(aFunction17ac1d);
    CALL(aFunction17ac2a);
    hlcoord(0, 0, wTilemap);
    LD_B(2);
    LD_C(SCREEN_WIDTH - 2);
    CALL(aFunction17ac46);
    RET;

}

void Function17ac1d(void){
    // LD_HL(mDialpadTilemap);
    // decoord(0, 4, wTilemap);
    // LD_BC((SCREEN_HEIGHT - 4) * SCREEN_WIDTH);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 4, wram->wTilemap), (SCREEN_HEIGHT - 4) * SCREEN_WIDTH, DialpadTilemap);
    // RET;
}

void Function17ac2a(void){
    LD_HL(mDialpadAttrmap);
    decoord(0, 4, wAttrmap);
    LD_BC((SCREEN_HEIGHT - 4) * SCREEN_WIDTH);
    CALL(aCopyBytes);
    hlcoord(0, 4, wAttrmap);
    LD_BC((SCREEN_HEIGHT - 4) * SCREEN_WIDTH);

loop:
    LD_A_hl;
    OR_A(0x8);
    LD_hli_A;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    RET;

}

void Function17ac46(void){
    LD_A_addr(0xd088);
    BIT_A(4);
    IF_NZ goto bit_4_set;
    CALL(aTextbox);
    RET;


bit_4_set:
    CALL(aFunction3eea);
    RET;

}

void Palette_17ac55(void){
    //rgb ['0', '0', '0']
    //rgb ['9', '10', '25']
    //rgb ['16', '19', '31']
    //rgb ['31', '31', '31']

    //rgb ['5', '11', '9']
    //rgb ['7', '14', '12']
    //rgb ['17', '24', '22']
    //rgb ['28', '31', '31']

    //rgb ['0', '0', '0']
    //rgb ['3', '0', '10']
    //rgb ['3', '3', '16']
    //rgb ['6', '8', '25']

    //rgb ['5', '11', '9']
    //rgb ['28', '31', '31']
    //rgb ['7', '14', '12']
    //rgb ['17', '24', '22']

    //rgb ['0', '0', '0']
    //rgb ['5', '2', '16']
    //rgb ['8', '8', '26']
    //rgb ['13', '9', '17']

    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']

    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']

    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']

    return Palette_17ac95();
}

void Palette_17ac95(void){
    //rgb ['31', '31', '31']
    //rgb ['4', '3', '3']
    //rgb ['31', '13', '0']
    //rgb ['31', '31', '31']

    //rgb ['31', '31', '31']
    //rgb ['0', '0', '0']
    //rgb ['31', '31', '31']
    //rgb ['31', '31', '31']

    //rgb ['31', '0', '0']
    //rgb ['16', '3', '0']
    //rgb ['28', '19', '11']
    //rgb ['31', '31', '31']

    //rgb ['31', '16', '0']
    //rgb ['9', '6', '4']
    //rgb ['31', '16', '0']
    //rgb ['31', '24', '0']

    //rgb ['31', '18', '6']
    //rgb ['0', '3', '0']
    //rgb ['0', '9', '0']
    //rgb ['0', '12', '0']

    //rgb ['0', '16', '0']
    //rgb ['0', '22', '0']
    //rgb ['0', '25', '0']
    //rgb ['0', '27', '0']

    //rgb ['0', '31', '0']
    //rgb ['3', '31', '0']
    //rgb ['8', '31', '0']
    //rgb ['14', '31', '0']

    //rgb ['16', '31', '0']
    //rgb ['22', '31', '0']
    //rgb ['27', '31', '0']
    //rgb ['31', '31', '0']
}

const char DialpadTilemap[] = "gfx/mobile/dialpad.tilemap";
const char DialpadAttrmap[] = "gfx/mobile/dialpad.attrmap";
const char DialpadGFX[] = "gfx/mobile/dialpad.png";
const char DialpadCursorGFX[] = "gfx/mobile/dialpad_cursor.png";

void Palette_17b4b5(void){
    //rgb ['2', '6', '10']
    //rgb ['24', '30', '29']
}

const char MobileCardListGFX[] = "gfx/mobile/card_list.png";
