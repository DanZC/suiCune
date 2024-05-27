#include "../constants.h"
#include "mobile_45_stadium.h"
#include "../engine/events/odd_egg.h"

void GiveOddEgg(void){
    // FARCALL(av_GiveOddEgg);
    // RET;
    return v_GiveOddEgg();
}

void Function11765d(void){
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    CALL(aFunction11766b);
    POP_AF;
    LDH_addr_A(hInMenu);
    RET;

}

void Function11766b(void){
    CALL(aFunction117699);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    CALL(aFunction1176ee);
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_HL(0xb1f3);
    LD_DE(wcd49);
    LD_BC(0x8);
    CALL(aCopyBytes);
    LD_DE(0xc708);
    LD_BC(0x11);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function117699(void){
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_HL(wcd49);
    LD_DE(0xb1f3);
    LD_BC(0x8);
    CALL(aCopyBytes);
    LD_HL(0xc708);
    LD_BC(0x11);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    XOR_A_A;
    LD_addr_A(wcd49);
    LD_addr_A(wcd4a);
    LD_addr_A(wcd4b);
    LD_addr_A(wcd4c);
    LD_addr_A(wcd4d);
    LD_addr_A(wcd4e);
    LD_addr_A(wcd4f);
    LD_HL(0xc708);
    LD_BC(0x11);
    CALL(aByteFill);
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    FARCALL(aFunction171c87);
    FARCALL(aReloadMapPart);
    FARCALL(aClearSpriteAnims);
    RET;

}

void Function1176ee(void){

loop:
    CALL(aJoyTextDelay);
    LD_A_addr(wcd49);
    BIT_A(7);
    IF_NZ goto quit;
    CALL(aFunction117719);
    FARCALL(aPlaySpriteAnimations);
    FARCALL(aReloadMapPart);
    goto loop;


quit:
    FARCALL(aClearSpriteAnims);
    CALL(aClearBGPalettes);
    CALL(aClearScreen);
    CALL(aClearSprites);
    RET;

}

void Function117719(void){
    //jumptable ['Jumptable_117728', 'wcd49']

    return Jumptable_117728();
}

void Jumptable_117728(void){
    //dw ['Function117738'];
    //dw ['Function117764'];
    //dw ['Function1178aa'];
    //dw ['Function1178e8'];
    //dw ['Function117942'];
    //dw ['Function117976'];
    //dw ['Function117984'];
    //dw ['Function1179a7'];

    return Function117738();
}

void Function117738(void){
    FARCALL(aFunction171ccd);
    depixel2(6, 3);
    LD_A(0x1d);
    CALL(aInitSpriteAnimStruct);
    LD_HL(0xc);
    ADD_HL_BC;
    LD_A(0x6);
    LD_hl_A;
    depixel2(9, 4);
    LD_A(0x1d);
    CALL(aInitSpriteAnimStruct);
    LD_HL(0xc);
    ADD_HL_BC;
    LD_A(0x7);
    LD_hl_A;
    LD_A(0x3);
    LD_addr_A(wcd23);
    JP(mMobilePassword_IncrementJumptable);

}

void Function117764(void){
    LD_A_addr(wcd4a);
    CP_A(0x10);
    IF_NZ goto asm_11776f;
    LD_A(0x1);
    goto asm_117770;


asm_11776f:
    XOR_A_A;

asm_117770:
    LD_addr_A(wcd24);
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(SELECT);
    JR_NZ (mFunction117764_select);
    LD_A_hl;
    AND_A(START);
    JR_NZ (mFunction117764_start);
    LD_A_hl;
    AND_A(A_BUTTON);
    JP_NZ (mFunction117764_a_button);
    LD_A_hl;
    AND_A(B_BUTTON);
    JR_NZ (mFunction117764_b_button);
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    JR_NZ (mFunction117764_d_up);
    LD_A_hl;
    AND_A(D_DOWN);
    JR_NZ (mFunction117764_d_down);
    LD_A_hl;
    AND_A(D_LEFT);
    JP_NZ (mFunction117764_d_left);
    LD_A_hl;
    AND_A(D_RIGHT);
    JP_NZ (mFunction117764_d_right);
    RET;

}

void Function117764_select(void){
    FARCALL(aFunction171cf0);
    RET;

}

void Function117764_start(void){
    LD_A(0x2);
    LD_addr_A(wcd4c);
    LD_A(0x4);
    LD_addr_A(wcd4d);
    RET;

}

void Function1177b7(void){
    LD_A(0x3);
    LD_addr_A(wcd24);
    LD_A_addr(wcd4a);
    AND_A_A;
    IF_Z goto asm_1177c5;
    JP(mMobilePassword_IncrementJumptable);


asm_1177c5:
    LD_A(0x6);
    LD_addr_A(wcd49);
    RET;

}

void Function1177cb(void){
    LD_A(0x80);
    LD_addr_A(wcd49);
    LD_addr_A(wScriptVar);
    JP(mMobilePassword_IncrementJumptable);

}

void Function117764_b_button(void){
    CALL(aPlayClickSFX);
    LD_A_addr(wcd4a);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wcd4a);
    LD_E_A;
    LD_D(0);
    LD_HL(0xc708);
    ADD_HL_DE;
    XOR_A_A;
    LD_hl_A;
    hlcoord(2, 4, wTilemap);
    ADD_HL_DE;
    LD_hl_A;
    RET;

}

void Function117764_d_up(void){
    LD_A_addr(wcd4d);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wcd4d);
    CP_A(0x3);
    RET_NZ ;
    LD_A_addr(wcd4c);
    LD_E_A;
    SLA_A;
    SLA_A;
    ADD_A_E;
    return Function117764_d_vertical_load();
}

void Function117764_d_vertical_load(void){
    LD_addr_A(wcd4c);
    RET;

}

void Function117764_d_down(void){
    LD_A_addr(wcd4d);
    CP_A(0x4);
    RET_Z ;
    INC_A;
    LD_addr_A(wcd4d);
    CP_A(0x4);
    RET_NZ ;
    LD_A_addr(wcd4c);
    CP_A(0xa);
    IF_NC goto asm_117825;
    CP_A(0x5);
    IF_NC goto asm_117829;
    XOR_A_A;
    JR(mFunction117764_d_vertical_load);


asm_117825:
    LD_A(0x2);
    JR(mFunction117764_d_vertical_load);


asm_117829:
    LD_A(0x1);
    JR(mFunction117764_d_vertical_load);

}

void Function117764_d_left(void){
    LD_A_addr(wcd4c);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wcd4c);
    RET;

}

void Function117764_d_right(void){
    LD_E(0xd);
    LD_A_addr(wcd4d);
    CP_A(0x4);
    IF_NZ goto wrap;
    LD_E(0x2);

wrap:
    LD_A_addr(wcd4c);
    CP_A_E;
    RET_Z ;
    INC_A;
    LD_addr_A(wcd4c);
    RET;

}

void Function117764_a_button(void){
    CALL(aPlayClickSFX);
    LD_A_addr(wcd4d);
    CP_A(0x4);
    IF_NZ goto not_4;
    LD_A_addr(wcd4c);
    CP_A(0x2);
    JP_Z (mFunction1177b7);
    CP_A(0x1);
    JP_Z (mFunction1177cb);
    JP(mFunction117764_select);


not_4:
    LD_A_addr(wcd4a);
    LD_E_A;
    CP_A(0x10);
    JP_Z (mFunction117764_start);
    INC_A;
    LD_addr_A(wcd4a);
    LD_D(0x0);
    LD_A_addr(wcd4b);
    AND_A_A;
    IF_NZ goto ascii_symbols;
    LD_HL(mUnknown_117a0f);
    goto got_ascii;


ascii_symbols:
    LD_HL(mUnknown_117a47);

got_ascii:
    PUSH_DE;
    LD_A_addr(wcd4c);
    LD_B_A;
    LD_A_addr(wcd4d);
    LD_C(0xe);
    CALL(aSimpleMultiply);
    ADD_A_B;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(0xc708);
    ADD_HL_DE;
    LD_hl_A;
    POP_DE;
    hlcoord(2, 4, wTilemap);
    ADD_HL_DE;
    SUB_A(0x20);
    LD_hl_A;
    LD_A_E;
    CP_A(0xf);
    RET_NZ ;
    JP(mFunction117764_start);

}

void Function1178aa(void){
    LD_HL(mMenuHeader_1179b5);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    CALL(aMenuBoxCoord2Tile);
    LD_HL(mMenuHeader_1179bd);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    CALL(aMenuBoxCoord2Tile);
    FARCALL(aReloadMapPart);
    hlcoord(16, 8, wTilemap);
    LD_DE(mYessNoString_1179c5);
    CALL(aPlaceString);
    hlcoord(15, 10, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    hlcoord(1, 14, wTilemap);
    LD_DE(mAskSavePasswordString);
    CALL(aPlaceString);
    LD_A(0x1);
    LD_addr_A(wcd4e);
    JP(mMobilePassword_IncrementJumptable);

}

void Function1178e8(void){
    LDH_A_addr(hJoyPressed);
    CP_A(B_BUTTON);
    IF_Z goto b_button;
    CP_A(A_BUTTON);
    IF_Z goto a_button;
    CP_A(D_DOWN);
    IF_Z goto d_down;
    CP_A(D_UP);
    RET_NZ ;
    LD_A_addr(wcd4e);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wcd4e);
    hlcoord(15, 8, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    hlcoord(15, 10, wTilemap);
    LD_A(0x7f);
    LD_hl_A;
    RET;


d_down:
    LD_A_addr(wcd4e);
    AND_A_A;
    RET_NZ ;
    INC_A;
    LD_addr_A(wcd4e);
    hlcoord(15, 8, wTilemap);
    LD_A(0x7f);
    LD_hl_A;
    hlcoord(15, 10, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    RET;


a_button:
    CALL(aPlayClickSFX);
    LD_A_addr(wcd4e);
    AND_A_A;
    IF_NZ goto b_button;
    CALL(aExitMenu);
    LD_A(0x1);
    LD_addr_A(wcd4f);
    JP(mMobilePassword_IncrementJumptable);


b_button:
    CALL(aExitMenu);
    CALL(aExitMenu);
    JP(mMobilePassword_IncrementJumptable);

}

void Function117942(void){
    CALL(aSpeechTextbox);
    hlcoord(1, 14, wTilemap);
    LD_DE(mSavedPasswordString);
    CALL(aPlaceString);
    LD_A(0x1e);
    LD_addr_A(wcd4e);
    LD_A(BANK(sMobileLoginPassword));
    CALL(aOpenSRAM);
    LD_A_addr(wcd4f);
    LD_addr_A(sMobileLoginPassword);
    LD_HL(0xc708);
    LD_DE(sMobileLoginPassword + 1);
    LD_BC(MOBILE_LOGIN_PASSWORD_LENGTH);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    LD_A_addr(wcd4f);
    AND_A_A;
    JR_Z (masm_11797e);
    CALL(aMobilePassword_IncrementJumptable);

    return Function117976();
}

void Function117976(void){
    LD_HL(wcd4e);
    DEC_hl;
    RET_NZ ;
    CALL(aExitMenu);
    return asm_11797e();
}

void asm_11797e(void){
    LD_A(0x80);
    LD_addr_A(wcd49);
    RET;

}

void Function117984(void){
    LD_HL(mMenuHeader_1179b5);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    CALL(aMenuBoxCoord2Tile);
    FARCALL(aReloadMapPart);
    hlcoord(1, 14, wTilemap);
    LD_DE(mNotAPokemonPasswordString);
    CALL(aPlaceString);
    LD_A(0x1e);
    LD_addr_A(wcd4e);
    CALL(aMobilePassword_IncrementJumptable);

    return Function1179a7();
}

void Function1179a7(void){
    LD_HL(wcd4e);
    DEC_hl;
    RET_NZ ;
    CALL(aExitMenu);
    LD_A(0x1);
    LD_addr_A(wcd49);
    RET;

}

void MenuHeader_1179b5(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '12', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return MenuHeader_1179bd();
}

void MenuHeader_1179bd(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['14', '7', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return YessNoString_1179c5();
}

void YessNoString_1179c5(void){
    //db ['"はい"'];
    //next ['"いいえ@"']

    return AskSavePasswordString();
}

void AskSavePasswordString(void){
    //db ['"こ<NO>パスワード¯ほぞんして"'];
    //line ['"おきますか？@"']

    return NotAPokemonPasswordString();
}

void NotAPokemonPasswordString(void){
    //db ['"パスワード<PKMN>にゅうりょく"'];
    //line ['"されていません！@"']

    return SavedPasswordString();
}

void SavedPasswordString(void){
    //db ['"ログインパスワード¯ほぞん"'];
    //line ['"しました@"']

    return MobilePassword_IncrementJumptable();
}

void MobilePassword_IncrementJumptable(void){
    LD_HL(wcd49);
    INC_hl;
    RET;

// pushc
// setcharmap ascii
}

const char Unknown_117a0f[][29] = {
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ  ",
    "abcdefghijklmnopqrstuvwxyz  ",
};

void Unknown_117a47(void){
    //db ['"0123456789\t"'];
    //db ['"!\\"#0x0b&\'()*+   "'];
    //db ['"', '-./:'];  //<=>?@   "
    //db ['"[\\\\]^_`\\{|}~    "'];
// popc

//  everything from here to the end of the bank is related to the
//  Mobile Stadium option from the continue/newgame menu.
//  Needs better function names
    // return MobileStudium();
}

void MobileStudium(void){
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    CALL(aFunction117a8d);
    POP_AF;
    LDH_addr_A(hInMenu);
    RET;

}

void Function117a8d(void){
    CALL(aFunction117a94);
    CALL(aFunction117acd);
    RET;

}

void Function117a94(void){
    XOR_A_A;
    LD_addr_A(wJumptableIndex);
    LD_addr_A(wcf64);
    LD_addr_A(wcf65);
    LD_addr_A(wcf66);
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    FARCALL(aFunction172e78);
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    RET;

}

void Function117ab4(void){
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    FARCALL(aFunction172e78);
    FARCALL(aFunction172eb9);
    FARCALL(aReloadMapPart);
    RET;

}

void Function117acd(void){
    CALL(aJoyTextDelay);
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto asm_117ae2;
    CALL(aFunction117ae9);
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    JR(mFunction117acd);


asm_117ae2:
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    RET;

}

void Function117ae9(void){
    //jumptable ['.Jumptable', 'wJumptableIndex']


Jumptable:
    //dw ['Function117b06'];
    //dw ['Function117b14'];
    //dw ['Function117b28'];
    //dw ['Function117b31'];
    //dw ['Function117b4f'];
    //dw ['Function117bb6'];
    //dw ['Function117c4a'];

    return Function117b06();
}

void Function117b06(void){
    FARCALL(aFunction172eb9);
    LD_A(0x10);
    LD_addr_A(wcf64);
    JP(mMobileStudium_JumptableIncrement);

}

void Function117b14(void){
    LD_HL(wcf64);
    DEC_hl;
    RET_NZ ;
    LD_HL(mMenuHeader_117cbc);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    CALL(aMenuBoxCoord2Tile);
    JP(mMobileStudium_JumptableIncrement);

}

void Function117b28(void){
    LD_HL(mMobileStadiumEntryText);
    CALL(aPrintText);
    JP(mMobileStudium_JumptableIncrement);

}

void Function117b31(void){
    LD_HL(mMenuHeader_117cc4);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    CALL(aMenuBoxCoord2Tile);
    hlcoord(16, 8, wTilemap);
    LD_DE(mYesNo117ccc);
    CALL(aPlaceString);
    hlcoord(15, 8, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    JP(mMobileStudium_JumptableIncrement);

}

void Function117b4f(void){
    LDH_A_addr(hJoyPressed);
    CP_A(B_BUTTON);
    IF_Z goto b_button;
    CP_A(A_BUTTON);
    IF_Z goto a_button;
    CP_A(D_DOWN);
    IF_Z goto d_down;
    CP_A(D_UP);
    RET_NZ ;
    LD_A_addr(wcf64);
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wcf64);
    hlcoord(15, 8, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    hlcoord(15, 10, wTilemap);
    LD_A(0x7f);
    LD_hl_A;
    RET;


d_down:
    LD_A_addr(wcf64);
    AND_A_A;
    RET_NZ ;
    INC_A;
    LD_addr_A(wcf64);
    hlcoord(15, 8, wTilemap);
    LD_A(0x7f);
    LD_hl_A;
    hlcoord(15, 10, wTilemap);
    LD_A(0xed);
    LD_hl_A;
    RET;


a_button:
    CALL(aPlayClickSFX);
    LD_A_addr(wcf64);
    AND_A_A;
    IF_NZ goto b_button;
    CALL(aExitMenu);
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    JP(mMobileStudium_JumptableIncrement);


b_button:
    CALL(aExitMenu);
    CALL(aExitMenu);
    FARCALL(aReloadMapPart);
    LD_A(0x80);
    LD_addr_A(wJumptableIndex);
    RET;

}

void Function117bb6(void){
    CALL(aFunction117c89);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    FARCALL(aFunction118284);
    CALL(aClearSprites);
    LD_A_addr(wMobileErrorCodeBuffer);
    AND_A_A;
    IF_Z goto asm_117be7;
    CP_A(0xa);
    IF_Z goto asm_117be1;

asm_117bd0:
    LD_A(0x2);
    LD_addr_A(wc303);
    FARCALL(aDisplayMobileError);
    LD_A(0x80);
    LD_addr_A(wJumptableIndex);
    RET;


asm_117be1:
    LD_A(0x80);
    LD_addr_A(wJumptableIndex);
    RET;


asm_117be7:
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);
    LD_A_addr(wcd89);
    AND_A(0x1);
    IF_NZ goto asm_117c16;
    LD_A_addr(w3_d000);
    CP_A(0xfe);
    IF_NZ goto asm_117c16;
    LD_A_addr(w3_d001);
    CP_A(0xf);
    IF_NZ goto asm_117c16;
    LD_HL(w3_dfec);
    LD_DE(wcd69);
    LD_C(0x10);

asm_117c0b:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    IF_NZ goto asm_117c16;
    INC_HL;
    DEC_C;
    IF_NZ goto asm_117c0b;
    goto asm_117c20;


asm_117c16:
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(0xd3);
    LD_addr_A(wMobileErrorCodeBuffer);
    goto asm_117bd0;


asm_117c20:
    POP_AF;
    LDH_addr_A(rSVBK);
    FARCALL(aFunction172eb9);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);
    LD_A(0x7);
    CALL(aOpenSRAM);
    LD_HL(w3_d002);
    LD_DE(0xb000);
    LD_BC(0x1000);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    POP_AF;
    LDH_addr_A(rSVBK);
    JP(mMobileStudium_JumptableIncrement);

}

void Function117c4a(void){
    LD_HL(mMenuHeader_117cbc);
    CALL(aLoadMenuHeader);
    CALL(aMenuBox);
    CALL(aMenuBoxCoord2Tile);
    FARCALL(aReloadMapPart);
    LD_HL(mMobileStadiumSuccessText);
    CALL(aPrintText);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(wBGPals1);
    LD_DE(1 * PALETTE_SIZE);
    LD_C(8);

loop:
    PUSH_HL;
    LD_A(LOW(PALRGB_WHITE));
    LD_hli_A;
    LD_A(HIGH(PALRGB_WHITE));
    LD_hl_A;
    POP_HL;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop;
    CALL(aRotateThreePalettesRight);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(0x80);
    LD_addr_A(wJumptableIndex);
    RET;

}

void Function117c89(void){
    LD_A(0x7);
    CALL(aOpenSRAM);
    LD_L(0x0);
    LD_H_L;
    LD_DE(0xb000);
    LD_BC(0x0ffc);

asm_117c97:
    PUSH_BC;
    LD_A_de;
    INC_DE;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto asm_117c97;
    LD_A_L;
    LD_addr_A(wcd83);
    LD_A_H;
    LD_addr_A(wcd84);
    LD_HL(0xbfea);
    LD_DE(wcd69);
    LD_BC(0x10);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void MenuHeader_117cbc(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '12', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return MenuHeader_117cc4();
}

void MenuHeader_117cc4(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['14', '7', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];
    //dw ['NULL'];
    //db ['0'];  // default item

    return YesNo117ccc();
}

void YesNo117ccc(void){
    //db ['"はい"'];
    //next ['"いいえ@"']

    return MobileStadiumEntryText();
}

void MobileStadiumEntryText(void){
    //text_far ['_MobileStadiumEntryText']
    //text_end ['?']

    return MobileStadiumSuccessText();
}

void MobileStadiumSuccessText(void){
    //text_far ['_MobileStadiumSuccessText']
    //text_end ['?']

    return MobileStudium_JumptableIncrement();
}

void MobileStudium_JumptableIncrement(void){
    LD_HL(wJumptableIndex);
    INC_hl;
    RET;

}
