#include "../constants.h"
#include "mobile_12.h"

void InitMobileProfile(void){
    XOR_A_A;
    SET_A(6);
    LD_addr_A(wd002);
    LD_HL(wd003);
    SET_hl(0);
    LD_A_C;
    AND_A_A;
    CALL_Z (aInitCrystalData);
    CALL(aClearBGPalettes);
    CALL(aFunction48d3d);
    LD_A_addr(wd479);
    BIT_A(1);
    IF_Z goto not_yet_initialized;
    LD_A_addr(wd003);
    SET_A(0);
    SET_A(1);
    SET_A(2);
    SET_A(3);
    LD_addr_A(wd003);

not_yet_initialized:
    CALL(aFunction486bf);
    CALL(aLoadFontsExtra);
    LD_DE(mMobileUpArrowGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x10);
    LD_BC((BANK(aMobileUpArrowGFX) << 8) | 1);
    CALL(aRequest1bpp);
    LD_DE(mMobileDownArrowGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x11);
    LD_BC((BANK(aMobileDownArrowGFX) << 8) | 1);
    CALL(aRequest1bpp);
    CALL(aFunction4a3a7);
    CALL(aClearBGPalettes);
    LD_A_addr(wd002);
    BIT_A(6);
    IF_Z goto asm_4808a;
    CALL(aFunction48689);
    goto asm_480d7;

asm_4808a:
    LD_A(0x5);
    LD_addr_A(wMusicFade);
    LD_A(LOW(MUSIC_MOBILE_ADAPTER_MENU));
    LD_addr_A(wMusicFadeID);
    LD_A(HIGH(MUSIC_MOBILE_ADAPTER_MENU));
    LD_addr_A(wMusicFadeID + 1);
    LD_C(20);
    CALL(aDelayFrames);
    LD_B(CRYSTAL_CGB_MOBILE_1);
    CALL(aGetCrystalCGBLayout);
    CALL(aClearBGPalettes);
    hlcoord(0, 0, wTilemap);
    LD_B(2);
    LD_C(20);
    CALL(aClearBox);
    hlcoord(0, 1, wTilemap);
    LD_A(0xc);
    LD_hl_A;
    LD_BC(0x13);
    ADD_HL_BC;
    LD_hl_A;
    LD_DE(mMobileProfileString);
    hlcoord(1, 1, wTilemap);
    CALL(aPlaceString);
    hlcoord(0, 2, wTilemap);
    LD_B(0xa);
    LD_C(0x12);
    CALL(aFunction48cdc);
    hlcoord(2, 4, wTilemap);
    LD_DE(mMobileString_Gender);
    CALL(aPlaceString);

asm_480d7:
    hlcoord(2, 6, wTilemap);
    LD_DE(mMobileString_Age);
    CALL(aPlaceString);
    hlcoord(2, 8, wTilemap);
    LD_DE(mMobileString_Address);
    CALL(aPlaceString);
    hlcoord(2, 10, wTilemap);
    LD_DE(mMobileString_ZipCode);
    CALL(aPlaceString);
    hlcoord(2, 12, wTilemap);
    LD_DE(mMobileString_OK);
    CALL(aPlaceString);
    LD_A_addr(wd002);
    BIT_A(6);
    IF_NZ goto asm_48113;
    LD_A_addr(wPlayerGender);
    LD_HL(mStrings_484fb);
    CALL(aGetNthString);
    LD_D_H;
    LD_E_L;
    hlcoord(11, 4, wTilemap);
    CALL(aPlaceString);

asm_48113:
    hlcoord(11, 6, wTilemap);
    CALL(aFunction487ec);
    LD_A_addr(wd474);
    DEC_A;
    LD_HL(mPrefectures);
    CALL(aGetNthString);
    LD_D_H;
    LD_E_L;
    hlcoord(11, 8, wTilemap);
    CALL(aPlaceString);
    hlcoord(11, 10, wTilemap);
    CALL(aFunction489ea);
    hlcoord(0, 14, wTilemap);
    LD_B(0x2);
    LD_C(0x12);
    CALL(aTextbox);
    hlcoord(1, 16, wTilemap);
    LD_DE(mMobileString_PersonalInfo);
    CALL(aPlaceString);
    CALL(aFunction48187);
    CALL(aWaitBGMap2);
    CALL(aSetPalettes);
    CALL(aStaticMenuJoypad);
    LD_HL(wMenuCursorY);
    LD_B_hl;
    PUSH_BC;
    JR(masm_4815f);

}

void Function48157(void){
    CALL(aScrollingMenuJoypad);
    LD_HL(wMenuCursorY);
    LD_B_hl;
    PUSH_BC;
    return asm_4815f();
}

void asm_4815f(void){
    BIT_A(A_BUTTON_F);
    JP_NZ (mFunction4820d);
    LD_B_A;
    LD_A_addr(wd002);
    BIT_A(6);
    IF_Z goto dont_check_b_button;
    LD_HL(wd479);
    BIT_hl(1);
    IF_Z goto dont_check_b_button;
    BIT_B(B_BUTTON_F);
    IF_NZ goto b_button;

dont_check_b_button:
    JP(mFunction48272);


b_button:
    CALL(aClearBGPalettes);
    CALL(aFunction48d30);
    POP_BC;
    CALL(aClearTilemap);
    LD_A(0xff);
    RET;

}

void Function48187(void){
    LD_A_addr(wd479);
    BIT_A(1);
    IF_NZ goto asm_481f1;
    LD_A_addr(wd003);
    LD_D_A;
    CALL(aFunction48725);
    IF_C goto asm_481a2;
    LD_BC((1 << 8) | 4);
    hlcoord(2, 12, wTilemap);
    CALL(aClearBox);
    goto asm_481ad;

asm_481a2:
    PUSH_DE;
    hlcoord(2, 12, wTilemap);
    LD_DE(mMobileString_OK);
    CALL(aPlaceString);
    POP_DE;

asm_481ad:
    LD_A_addr(wd002);
    BIT_A(6);
    IF_NZ goto asm_481c1;
    BIT_D(0);
    IF_NZ goto asm_481c1;
    LD_BC((1 << 8) | 8);
    hlcoord(11, 4, wTilemap);
    CALL(aClearBox);

asm_481c1:
    BIT_D(1);
    IF_NZ goto asm_481ce;
    LD_BC((1 << 8) | 8);
    hlcoord(11, 6, wTilemap);
    CALL(aClearBox);

asm_481ce:
    BIT_D(2);
    IF_NZ goto asm_481db;
    LD_BC((2 << 8) | 8);
    hlcoord(11, 7, wTilemap);
    CALL(aClearBox);

asm_481db:
    BIT_D(3);
    IF_NZ goto asm_481f1;
    LD_A_addr(wd479);
    BIT_A(0);
    IF_NZ goto asm_481f8;
    LD_BC((1 << 8) | 8);
    hlcoord(11, 10, wTilemap);
    CALL(aClearBox);
    goto asm_48201;

asm_481f1:
    LD_A_addr(wd479);
    BIT_A(0);
    IF_NZ goto asm_48201;

asm_481f8:
    hlcoord(11, 10, wTilemap);
    LD_DE(mFunction48187_String_TellLater);
    CALL(aPlaceString);

asm_48201:
    RET;


String_TellLater:
    //db ['"Tell Later@"'];

    return Function4820d();
}

void Function4820d(void){
    CALL(aPlaceHollowCursor);
    LD_HL(wMenuCursorY);
    LD_A_hl;
    PUSH_AF;
    LD_A_addr(wd002);
    BIT_A(6);
    IF_Z goto asm_4821f;
    POP_AF;
    INC_A;
    PUSH_AF;

asm_4821f:
    POP_AF;
    CP_A(0x1);
    JR_Z (masm_4828d);
    CP_A(0x2);
    JP_Z (mFunction4876f);
    CP_A(0x3);
    JP_Z (mFunction48304);
    CP_A(0x4);
    JP_Z (mFunction488d3);
    LD_A(0x2);
    CALL(aMenuClickSound);
    LD_A_addr(wd002);
    BIT_A(6);
    IF_Z goto asm_4825c;
    goto asm_4825c;

    hlcoord(1, 15, wTilemap);
    LD_B(0x2);
    LD_C(0x12);
    CALL(aClearBox);
    LD_DE(mMobileString_ProfileChanged);
    hlcoord(1, 16, wTilemap);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    LD_C(48);
    CALL(aDelayFrames);


asm_4825c:
    CALL(aClearBGPalettes);
    CALL(aFunction48d30);
    POP_BC;
    CALL(aClearTilemap);
    LD_B(SCGB_DIPLOMA);
    CALL(aGetSGBLayout);
    LD_HL(wd479);
    SET_hl(1);
    XOR_A_A;
    RET;

}

void Function48272(void){
    JP(mFunction4840c);

}

void MobileString_PersonalInfo(void){
    //db ['"Personal Info@"'];

    return Function48283();
}

void Function48283(void){
    LD_BC((2 << 8) | 18);
    hlcoord(1, 15, wTilemap);
    CALL(aClearBox);
    RET;

}

void asm_4828d(void){
    CALL(aFunction48283);
    hlcoord(1, 16, wTilemap);
    LD_DE(mMobileDesc_Gender);
    CALL(aPlaceString);
    LD_HL(mMenuHeader_0x484f1);
    CALL(aLoadMenuHeader);
    CALL(aFunction4873c);
    hlcoord(11, 2, wTilemap);
    LD_B(0x4);
    LD_C(0x7);
    CALL(aFunction48cdc);
    hlcoord(13, 4, wTilemap);
    LD_DE(mString_484fb);
    CALL(aPlaceString);
    hlcoord(13, 6, wTilemap);
    LD_DE(mString_484ff);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    LD_A_addr(wPlayerGender);
    INC_A;
    LD_addr_A(wMenuCursorPosition);
    CALL(aStaticMenuJoypad);
    CALL(aPlayClickSFX);
    CALL(aExitMenu);
    BIT_A(0);
    JP_Z (mFunction4840c);
    LD_HL(wMenuCursorY);
    LD_A_hl;
    LD_HL(mStrings_484fb);
    CP_A(0x1);
    IF_Z goto asm_482ed;

asm_482e1:
    LD_A_hli;
    CP_A(0x50);
    IF_NZ goto asm_482e1;
    LD_A(1 << PLAYERGENDER_FEMALE_F);
    LD_addr_A(wPlayerGender);
    goto asm_482f1;

asm_482ed:
    XOR_A_A;
    LD_addr_A(wPlayerGender);

asm_482f1:
    LD_D_H;
    LD_E_L;
    hlcoord(11, 4, wTilemap);
    CALL(aPlaceString);
    LD_A_addr(wd003);
    SET_A(0);
    LD_addr_A(wd003);
    JP(mFunction4840c);

}

void Function48304(void){
    CALL(aFunction48283);
    hlcoord(1, 16, wTilemap);
    LD_DE(mMobileDesc_Address);
    CALL(aPlaceString);
    LD_HL(mMenuHeader_0x48504);
    CALL(aLoadMenuHeader);
    LD_HL(mMenuHeader_0x48513);
    CALL(aLoadMenuHeader);
    hlcoord(10, 0, wTilemap);
    LD_B(0xc);
    LD_C(0x8);
    CALL(aFunction48cdc);
    LD_A_addr(wMenuCursorPosition);
    LD_B_A;
    LD_A_addr(wMenuScrollPosition);
    LD_C_A;
    PUSH_BC;
    LD_A_addr(wd474);
    DEC_A;
    CP_A(0x29);
    IF_C goto asm_4833f;
    SUB_A(0x29);
    INC_A;
    LD_addr_A(wMenuCursorPosition);
    LD_A(0x29);

asm_4833f:
    LD_addr_A(wMenuScrollPosition);
    FARCALL(aMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);

asm_48348:
    CALL(aScrollingMenu);
    LD_DE(0x629);
    CALL(aFunction48383);
    IF_C goto asm_48348;
    LD_D_A;
    POP_BC;
    LD_A_B;
    LD_addr_A(wMenuCursorPosition);
    LD_A_C;
    LD_addr_A(wMenuScrollPosition);
    LD_A_D;
    PUSH_AF;
    CALL(aExitMenu);
    CALL(aExitMenu);
    POP_AF;
    LDH_A_addr(hJoyPressed);
    BIT_A(0);
    IF_Z goto asm_48377;
    CALL(aFunction483bb);
    LD_A_addr(wd003);
    SET_A(2);
    LD_addr_A(wd003);

asm_48377:
    CALL(aFunction48187);
    FARCALL(aMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    JP(mFunction4840c);

}

void Function48383(void){
    PUSH_BC;
    PUSH_AF;
    BIT_A(5);
    IF_NZ goto asm_48390;
    BIT_A(4);
    IF_NZ goto asm_4839f;
    AND_A_A;
    goto asm_483b7;

asm_48390:
    LD_A_addr(wMenuScrollPosition);
    SUB_A_D;
    LD_addr_A(wMenuScrollPosition);
    IF_NC goto asm_483af;
    XOR_A_A;
    LD_addr_A(wMenuScrollPosition);
    goto asm_483af;

asm_4839f:
    LD_A_addr(wMenuScrollPosition);
    ADD_A_D;
    LD_addr_A(wMenuScrollPosition);
    CP_A_E;
    IF_C goto asm_483af;
    LD_A_E;
    LD_addr_A(wMenuScrollPosition);
    goto asm_483af;

asm_483af:
    LD_HL(wMenuCursorY);
    LD_A_hl;
    LD_addr_A(wMenuCursorPosition);
    SCF;

asm_483b7:
    POP_BC;
    LD_A_B;
    POP_BC;
    RET;

}

void Function483bb(void){
    LD_HL(wScrollingMenuCursorPosition);
    LD_A_hl;
    INC_A;
    LD_addr_A(wd474);
    DEC_A;
    LD_B_A;
    LD_HL(mPrefectures);

asm_483c8:
    AND_A_A;
    IF_Z goto asm_483d5;

asm_483cb:
    LD_A_hli;
    CP_A(0x50);
    IF_NZ goto asm_483cb;
    LD_A_B;
    DEC_A;
    LD_B_A;
    goto asm_483c8;

asm_483d5:
    LD_D_H;
    LD_E_L;
    LD_B(0x2);
    LD_C(0x8);
    hlcoord(11, 7, wTilemap);
    CALL(aClearBox);
    hlcoord(11, 8, wTilemap);
    CALL(aPlaceString);
    RET;

}

void Function483e8(void){
    PUSH_DE;
    LD_HL(mPrefectures);
    LD_A_addr(wMenuSelection);
    CP_A(0xff);
    IF_NZ goto asm_483f8;
    LD_HL(mWakayama);  // last string
    goto asm_48405;


asm_483f8:
    LD_D_A;
    AND_A_A;
    IF_Z goto asm_48405;

asm_483fc:
    LD_A_hli;
    CP_A(0x50);
    IF_NZ goto asm_483fc;
    LD_A_D;
    DEC_A;
    goto asm_483f8;


asm_48405:
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aPlaceString);
    RET;

}

void Function4840c(void){
    CALL(aFunction48187);
    CALL(aFunction48283);
    hlcoord(1, 16, wTilemap);
    LD_DE(mMobileString_PersonalInfo);
    CALL(aPlaceString);
    CALL(aFunction486bf);
    POP_BC;
    LD_HL(wMenuCursorY);
    LD_hl_B;
    LD_A_addr(wd002);
    BIT_A(6);
    IF_NZ goto narrower_box;
    LD_B(9);
    LD_C(1);
    hlcoord(1, 4, wTilemap);
    CALL(aClearBox);
    JP(mFunction48157);


narrower_box:
    LD_B(7);
    LD_C(1);
    hlcoord(1, 6, wTilemap);
    CALL(aClearBox);
    JP(mFunction48157);

}

void Mobile12_Bin2Dec(void){
    PUSH_BC;
    PUSH_AF;
    PUSH_DE;
    PUSH_HL;
    LD_HL(mMobile12_Bin2Dec_DigitStrings);

loop:
    AND_A_A;
    IF_Z goto got_string;
    INC_HL;
    INC_HL;
    DEC_A;
    goto loop;

got_string:
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aPlaceString);
    POP_DE;
    POP_AF;
    POP_BC;
    RET;


DigitStrings:
    //db ['"0@"'];
    //db ['"1@"'];
    //db ['"2@"'];
    //db ['"3@"'];
    //db ['"4@"'];
    //db ['"5@"'];
    //db ['"6@"'];
    //db ['"7@"'];
    //db ['"8@"'];
    //db ['"9@"'];
}

const char MobileProfileString[] = "  Mobile Profile@";
const char MobileString_Gender[] = "Gender@";

void MobileString_Age(void){
//           db "Age@"
    return MobileString_Address();
}

void MobileString_Address(void){
//       db "Address@"
    return MobileString_ZipCode();
}

void MobileString_ZipCode(void){
//       db "Zip Code@"
    return MobileString_OK();
}

void MobileString_OK(void){
//            db "OK@"
    return MobileString_ProfileChanged();
}

void MobileString_ProfileChanged(void){
//db "Profile Changed@"
    return MobileDesc_Gender();
}

void MobileDesc_Gender(void){
//          db "Boy or girl?@"
    return MobileDesc_Age();
}

void MobileDesc_Age(void){
//             db "How old are you?@"
    return MobileDesc_Address();
}

void MobileDesc_Address(void){
//         db "Where do you live?@"
    return MobileDesc_ZipCode();
}

void MobileDesc_ZipCode(void){
//         db "Your zip code?@"

    return MenuHeader_0x484f1();
}

void MenuHeader_0x484f1(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['11', '2', 'SCREEN_WIDTH - 1', '7'];
    //dw ['MenuData_0x484f9'];
    //db ['1'];  // default option

    return MenuData_0x484f9();
}

void MenuData_0x484f9(void){
    //db ['STATICMENU_CURSOR | STATICMENU_WRAP'];  // flags
    //db ['2'];  // items
    return Strings_484fb();
}

void Strings_484fb(void){
    return String_484fb();
}

void String_484fb(void){
//db "Boy@"
    return String_484ff();
}

void String_484ff(void){
//db "Girl@"

    return MenuHeader_0x48504();
}

void MenuHeader_0x48504(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['10', '0', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];

    return MenuHeader_0x48509();
}

void MenuHeader_0x48509(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['10', '5', 'SCREEN_WIDTH - 1', '7'];

    return MenuHeader_0x4850e();
}

void MenuHeader_0x4850e(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['10', '9', 'SCREEN_WIDTH - 1', 'TEXTBOX_Y - 1'];

    return MenuHeader_0x48513();
}

void MenuHeader_0x48513(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['11', '1', '18', '12'];
    //dw ['MenuData_0x4851b'];
    //db ['1'];  // default option

    return MenuData_0x4851b();
}

void MenuData_0x4851b(void){
    //db ['SCROLLINGMENU_DISPLAY_ARROWS | SCROLLINGMENU_ENABLE_RIGHT | SCROLLINGMENU_ENABLE_LEFT | SCROLLINGMENU_CALL_FUNCTION1_CANCEL'];  // flags
    //db ['6', '0'];  // rows, columns
    //db ['SCROLLINGMENU_ITEMS_NORMAL'];  // item format
    //dba ['.Items']
    //dba ['Function483e8']
    //dba ['NULL']
    //dba ['NULL']


Items:
    //db ['46'];
    for(int x = 0; x < 46; x++){
    //db ['x'];
    }
    //db ['-1'];

    return Prefectures();
}

void Prefectures(void){
    return Aichi();
}

void Aichi(void){
//    db "あいちけん@"     //  Aichi
    return Aomori();
}

void Aomori(void){
//   db "あおもりけん@"   //  Aomori
    return Akita();
}

void Akita(void){
//    db "あきたけん@"     //  Akita
    return Ishikawa();
}

void Ishikawa(void){
// db "いしかわけん@"   //  Ishikawa
    return Ibaraki();
}

void Ibaraki(void){
//  db "いばらきけん@"   //  Ibaraki
    return Iwate();
}

void Iwate(void){
//    db "いわてけん@"     //  Iwate
    return Ehime();
}

void Ehime(void){
//    db "えひめけん@"     //  Ehime
    return Oita();
}

void Oita(void){
//     db "おおいたけん@"   //  Oita
    return Osakafu();
}

void Osakafu(void){
//  db "おおさかふ@"     //  Osakafu
    return Okayama();
}

void Okayama(void){
//  db "おかやまけん@"   //  Okayama
    return Okinawa();
}

void Okinawa(void){
//  db "おきなわけん@"   //  Okinawa
    return Kagawa();
}

void Kagawa(void){
//   db "かがわけん@"     //  Kagawa
    return Kagoshima();
}

void Kagoshima(void){
//db "かごしまけん@"   //  Kagoshima
    return Kanagawa();
}

void Kanagawa(void){
// db "かながわけん@"   //  Kanagawa
    return Gifu();
}

void Gifu(void){
//     db "ぎふけん@"       //  Gifu
    return Kyotofu();
}

void Kyotofu(void){
//  db "きょうとふ@"     //  Kyotofu
    return Kumamoto();
}

void Kumamoto(void){
// db "くまもとけん@"   //  Kumamoto
    return Gunma();
}

void Gunma(void){
//    db "ぐんまけん@"     //  Gunma
    return Kochi();
}

void Kochi(void){
//    db "こうちけん@"     //  Kochi
    return Saitama();
}

void Saitama(void){
//  db "さいたまけん@"   //  Saitama
    return Saga();
}

void Saga(void){
//     db "さがけん@"       //  Saga
    return Shiga();
}

void Shiga(void){
//    db "しがけん@"       //  Shiga
    return Shizuoka();
}

void Shizuoka(void){
// db "しずおかけん@"   //  Shizuoka
    return Shimane();
}

void Shimane(void){
//  db "しまねけん@"     //  Shimane
    return Chiba();
}

void Chiba(void){
//    db "ちばけん@"       //  Chiba
    return Tokyo();
}

void Tokyo(void){
//    db "とうきょうと@"   //  Tokyo
    return Tokushima();
}

void Tokushima(void){
//db "とくしまけん@"   //  Tokushima
    return Tochigi();
}

void Tochigi(void){
//  db "とちぎけん@"     //  Tochigi
    return Tottori();
}

void Tottori(void){
//  db "とっとりけん@"   //  Tottori
    return Toyama();
}

void Toyama(void){
//   db "とやまけん@"     //  Toyama
    return Nagasaki();
}

void Nagasaki(void){
// db "ながさきけん@"   //  Nagasaki
    return Nagano();
}

void Nagano(void){
//   db "ながのけん@"     //  Nagano
    return Naraken();
}

void Naraken(void){
//  db "ならけん@"       //  Naraken
    return Niigata();
}

void Niigata(void){
//  db "にいがたけん@"   //  Niigata
    return Hyogo();
}

void Hyogo(void){
//    db "ひょうごけん@"   //  Hyogo
    return Hiroshima();
}

void Hiroshima(void){
//db "ひろしまけん@"   //  Hiroshima
    return Fukui();
}

void Fukui(void){
//    db "ふくいけん@"     //  Fukui
    return Fukuoka();
}

void Fukuoka(void){
//  db "ふくおかけん@"   //  Fukuoka
    return Fukushima();
}

void Fukushima(void){
//db "ふくしまけん@"   //  Fukushima
    return Hokkaido();
}

void Hokkaido(void){
// db "ほっかいどう@"   //  Hokkaido
    return Mie();
}

void Mie(void){
//      db "みえけん@"       //  Mie
    return Miyagi();
}

void Miyagi(void){
//   db "みやぎけん@"     //  Miyagi
    return Miyazaki();
}

void Miyazaki(void){
// db "みやざきけん@"   //  Miyazaki
    return Yamagata();
}

void Yamagata(void){
// db "やまがたけん@"   //  Yamagata
    return Yamaguchi();
}

void Yamaguchi(void){
//db "やまぐちけん@"   //  Yamaguchi
    return Yamanashi();
}

void Yamanashi(void){
//db "やまなしけん@"   //  Yamanashi
    return Wakayama();
}

void Wakayama(void){
// db "わかやまけん@"   //  Wakayama

    return Function48689();
}

void Function48689(void){
    LD_C(7);
    CALL(aDelayFrames);
    LD_B(CRYSTAL_CGB_MOBILE_1);
    CALL(aGetCrystalCGBLayout);
    CALL(aClearBGPalettes);
    hlcoord(0, 0, wTilemap);
    LD_B(4);
    LD_C(SCREEN_WIDTH);
    CALL(aClearBox);
    hlcoord(0, 2, wTilemap);
    LD_A(0xc);
    LD_hl_A;
    LD_BC(SCREEN_WIDTH - 1);
    ADD_HL_BC;
    LD_hl_A;
    LD_DE(mMobileProfileString);
    hlcoord(1, 2, wTilemap);
    CALL(aPlaceString);
    hlcoord(0, 4, wTilemap);
    LD_B(0x8);
    LD_C(0x12);
    CALL(aFunction48cdc);
    RET;

}

void Function486bf(void){
    LD_HL(w2DMenuCursorInitY);
    LD_A_addr(wd002);
    BIT_A(6);
    IF_NZ goto start_at_6;
    LD_A(4);
    LD_hli_A;
    goto got_init_y;


start_at_6:
    LD_A(6);
    LD_hli_A;

got_init_y:
    LD_A(1);
    LD_hli_A;  // init x
    LD_A_addr(wd002);
    BIT_A(6);
    IF_NZ goto check_wd479;
    CALL(aFunction48725);
    LD_A(4);
    IF_NC goto got_num_rows_1;
    LD_A(5);

got_num_rows_1:
    LD_hli_A;
    goto got_num_rows_2;


check_wd479:
    LD_A_addr(wd479);
    BIT_A(1);
    IF_NZ goto four_rows;
    CALL(aFunction48725);
    IF_C goto four_rows;
    LD_A(3);
    LD_hli_A;
    goto got_num_rows_2;


four_rows:
    LD_A(4);
    LD_hli_A;

got_num_rows_2:
    LD_A(1);
    LD_hli_A;  // num cols
    LD_hl(0);  // flags 1
    SET_hl(5);
    INC_HL;
    XOR_A_A;
    LD_hli_A;  // flags 2
    LD_A(0x20);
    LD_hli_A;  // cursor offsets
    LD_A(A_BUTTON);
    ADD_A(D_UP);
    ADD_A(D_DOWN);
    PUSH_AF;
    LD_A_addr(wd002);
    BIT_A(6);
    IF_Z goto got_joypad_mask;
    POP_AF;
    ADD_A(B_BUTTON);
    PUSH_AF;

got_joypad_mask:
    POP_AF;
    LD_hli_A;
    LD_A(0x1);
    LD_hli_A;  // cursor y
    LD_hli_A;  // cursor x
    XOR_A_A;
    LD_hli_A;  // off char
    LD_hli_A;  // cursor tile
    LD_hli_A;  // cursor tile + 1
    RET;

}

void Function48725(void){
//      ld a, [wd003]
//      and $f
//      cp $f
//      jr nz, .clear_carry
//      scf
//      ret
//  .clear_carry
//      and a
//      ret

    LD_A_addr(wd003);
    BIT_A(0);
    IF_Z goto clear_carry;
    BIT_A(1);
    IF_Z goto clear_carry;
    BIT_A(2);
    IF_Z goto clear_carry;
    BIT_A(3);
    IF_Z goto clear_carry;
    SCF;
    RET;


clear_carry:
    AND_A_A;
    RET;

}

void Function4873c(void){
    LD_HL(w2DMenuCursorInitY);
    LD_A(4);
    LD_hli_A;
    LD_A(12);
    LD_hli_A;  // init x
    LD_A(2);
    LD_hli_A;  // num rows
    LD_A(1);
    LD_hli_A;  // num cols
    LD_hl(0);  // flags 1
    SET_hl(5);
    INC_HL;
    XOR_A_A;
    LD_hli_A;  // flags 2
    LD_A((2 << 4) | 0);
    LD_hli_A;  // cursor offsets
    LD_A(A_BUTTON);
    ADD_A(B_BUTTON);
    LD_hli_A;  // joypad filter
// ld a, [wPlayerGender]
// xor 1 << PLAYERGENDER_FEMALE_F
// inc a
    LD_A_addr(wPlayerGender);
    AND_A_A;
    IF_Z goto male;
    LD_A(2);
    goto okay_gender;


male:
    LD_A(1);

okay_gender:
    LD_hli_A;  // cursor y
    LD_A(0x1);
    LD_hli_A;  // cursor x
    XOR_A_A;
    LD_hli_A;  // off char
    LD_hli_A;  // cursor tile
    LD_hli_A;  // cursor tile + 1
    RET;

}

void Function4876f(void){
    CALL(aFunction48283);
    hlcoord(1, 16, wTilemap);
    LD_DE(mMobileDesc_Age);
    CALL(aPlaceString);
    LD_HL(mMenuHeader_0x48509);
    CALL(aLoadMenuHeader);
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    hlcoord(10, 5, wTilemap);
    LD_B(0x1);
    LD_C(0x8);
    CALL(aFunction48cdc);
    CALL(aWaitBGMap);
    LD_A_addr(wd473);
    AND_A_A;
    IF_Z goto asm_487ab;
    CP_A(0x64);
    IF_Z goto asm_487b2;
    hlcoord(12, 5, wTilemap);
    LD_hl(0x10);
    hlcoord(12, 7, wTilemap);
    LD_hl(0x11);
    goto asm_487b7;

asm_487ab:
    hlcoord(12, 5, wTilemap);
    LD_hl(0x10);
    goto asm_487b7;

asm_487b2:
    hlcoord(12, 7, wTilemap);
    LD_hl(0x11);

asm_487b7:
    hlcoord(11, 6, wTilemap);
    CALL(aFunction487ec);
    LD_C(10);
    CALL(aDelayFrames);
    LD_A_addr(wd473);
    PUSH_AF;

asm_487c6:
    CALL(aJoyTextDelay);
    CALL(aFunction4880e);
    IF_NC goto asm_487c6;
    LD_A(0x1);
    CALL(aMenuClickSound);
    POP_BC;
    IF_NZ goto asm_487da;
    LD_A_B;
    LD_addr_A(wd473);

asm_487da:
    LD_A_addr(wd473);
    CALL(aExitMenu);
    hlcoord(11, 6, wTilemap);
    CALL(aFunction487ec);
    POP_AF;
    LDH_addr_A(hInMenu);
    JP(mFunction4840c);

}

void Function487ec(void){
    PUSH_HL;
    LD_DE(wd473);
    CALL(aFunction487ff);
    POP_HL;
    for(int rept = 0; rept < 4; rept++){
    INC_HL;
    }
    LD_DE(mString_4880d);
    CALL(aPlaceString);
    RET;

}

void Function487ff(void){
    PUSH_HL;
    LD_A(0x7f);
    LD_hli_A;
    LD_hl_A;
    POP_HL;
    LD_B(PRINTNUM_LEADINGZEROS | 1);
    LD_C(3);
    CALL(aPrintNum);
    RET;

}

void String_4880d(void){
    //db ['"@"'];

    return Function4880e();
}

void Function4880e(void){
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON);
    JP_NZ (mFunction488b9);
    LDH_A_addr(hJoyPressed);
    AND_A(B_BUTTON);
    JP_NZ (mFunction488b4);
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto asm_48843;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto asm_48838;
    LD_A_hl;
    AND_A(D_LEFT);
    IF_NZ goto asm_4884f;
    LD_A_hl;
    AND_A(D_RIGHT);
    IF_NZ goto asm_4885f;
    CALL(aDelayFrame);
    AND_A_A;
    RET;

asm_48838:
    LD_HL(wd473);
    LD_A_hl;
    AND_A_A;
    IF_Z goto asm_48840;
    DEC_A;

asm_48840:
    LD_hl_A;
    goto asm_4886f;

asm_48843:
    LD_HL(wd473);
    LD_A_hl;
    CP_A(0x64);
    IF_NC goto asm_4884c;
    INC_A;

asm_4884c:
    LD_hl_A;
    goto asm_4886f;

asm_4884f:
    LD_A_addr(wd473);
    CP_A(0x5b);
    IF_C goto asm_48858;
    LD_A(0x5a);

asm_48858:
    ADD_A(0xa);
    LD_addr_A(wd473);
    goto asm_4886f;

asm_4885f:
    LD_A_addr(wd473);
    CP_A(0xa);
    IF_NC goto asm_48868;
    LD_A(0xa);

asm_48868:
    SUB_A(0xa);
    LD_addr_A(wd473);
    goto asm_4886f;

asm_4886f:
    LD_A_addr(wd473);
    AND_A_A;
    IF_Z goto asm_48887;
    CP_A(0x64);
    IF_Z goto asm_48898;
    IF_Z goto asm_488a7;
    hlcoord(12, 5, wTilemap);
    LD_hl(0x10);
    hlcoord(12, 7, wTilemap);
    LD_hl(0x11);
    goto asm_488a7;

asm_48887:
    hlcoord(10, 5, wTilemap);
    LD_B(0x1);
    LD_C(0x8);
    CALL(aFunction48cdc);
    hlcoord(12, 5, wTilemap);
    LD_hl(0x10);
    goto asm_488a7;

asm_48898:
    hlcoord(10, 5, wTilemap);
    LD_B(0x1);
    LD_C(0x8);
    CALL(aFunction48cdc);
    hlcoord(12, 7, wTilemap);
    LD_hl(0x11);

asm_488a7:
    hlcoord(11, 6, wTilemap);
    CALL(aFunction487ec);
    CALL(aWaitBGMap);
    LD_A(0x1);
    AND_A_A;
    RET;

}

void Function488b4(void){
    LD_A(0x0);
    AND_A_A;
    SCF;
    RET;

}

void Function488b9(void){
    LD_A_addr(wd003);
    SET_A(1);
    LD_addr_A(wd003);
    SCF;
    RET;

}

void MobileUpArrowGFX(void){
// INCBIN "gfx/mobile/up_arrow.1bpp"

    return MobileDownArrowGFX();
}

void MobileDownArrowGFX(void){
// INCBIN "gfx/mobile/down_arrow.1bpp"

    return Function488d3();
}

void Function488d3(void){
    CALL(aFunction48283);
    hlcoord(1, 16, wTilemap);
    LD_DE(mMobileDesc_ZipCode);
    CALL(aPlaceString);
    CALL(aFunction48a3a);
    JP_C (mFunction4840c);
    LD_HL(mMenuHeader_0x4850e);
    CALL(aLoadMenuHeader);
    LDH_A_addr(hInMenu);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(hInMenu);
    hlcoord(10, 9, wTilemap);
    LD_B(0x1);
    LD_C(0x8);
    CALL(aFunction48cdc);
    LD_A_addr(wd475);
    AND_A(0xf);
    LD_D(0x0);
    hlcoord(11, 10, wTilemap);
    CALL(aFunction489ea);
    CALL(aWaitBGMap);
    LD_A_addr(wd475);
    LD_B_A;
    LD_A_addr(wd476);
    LD_C_A;
    LD_A_addr(wd477);
    LD_D_A;
    LD_A_addr(wd478);
    LD_E_A;
    PUSH_DE;
    PUSH_BC;
    LD_D(0x0);
    LD_B(0x0);

    return asm_48922();
}

void asm_48922(void){
    PUSH_BC;
    CALL(aJoyTextDelay);
    LDH_A_addr(hJoyDown);
    AND_A_A;
    JP_Z (mFunction4896e);
    BIT_A(0);
    JP_NZ (mFunction4896e);
    BIT_A(1);
    JP_NZ (mFunction4896e);
    LD_A_addr(wd002);
    AND_A(0b11001111);
    RES_A(7);
    LD_addr_A(wd002);
    POP_BC;
    INC_B;
    LD_A_B;
    CP_A(0x5);
    PUSH_BC;
    IF_C goto asm_4894c;
    POP_BC;
    LD_B(0x4);
    PUSH_BC;

asm_4894c:
    POP_BC;
    PUSH_BC;
    LD_A_B;
    CP_A(0x4);
    JR_NZ (masm_48972);
    LD_C(10);
    CALL(aDelayFrames);
    JR(masm_48972);

}

void Function4895a(void){
//  //  unreferenced
    LDH_A_addr(hJoyPressed);
    AND_A_A;
    IF_Z goto asm_48965;
    POP_BC;
    LD_B(0x1);
    PUSH_BC;
    JR(masm_48972);


asm_48965:
    LDH_A_addr(hJoyLast);
    AND_A_A;
    JR_Z (masm_48972);

    POP_BC;
    LD_B(0x1);
    PUSH_BC;

    return Function4896e();
}

void Function4896e(void){
    POP_BC;
    LD_B(0x0);
    PUSH_BC;

    return asm_48972();
}

void asm_48972(void){
    CALL(aFunction48ab5);
    PUSH_AF;
    CP_A(0xf0);
    IF_Z goto asm_48994;
    CP_A(0xf);
    IF_NZ goto asm_48988;
    LD_A_addr(wd002);
    SET_A(7);
    AND_A(0xcf);
    LD_addr_A(wd002);

asm_48988:
    hlcoord(11, 10, wTilemap);
    LD_B(0x0);
    LD_C_D;
    ADD_HL_BC;
    LD_B(0x3);
    CALL(aFunction48c11);

asm_48994:
    CALL(aWaitBGMap);
    POP_AF;
    POP_BC;
    JR_NC (masm_48922);
    IF_NZ goto asm_489b1;
    POP_BC;
    LD_A_B;
    LD_addr_A(wd475);
    LD_A_C;
    LD_addr_A(wd476);
    POP_BC;
    LD_A_B;
    LD_addr_A(wd477);
    LD_A_C;
    LD_addr_A(wd478);
    goto asm_489c5;

asm_489b1:
    PUSH_AF;
    LD_A_addr(wd479);
    SET_A(0);
    LD_addr_A(wd479);
    LD_A_addr(wd003);
    SET_A(3);
    LD_addr_A(wd003);
    POP_AF;
    POP_BC;
    POP_BC;

asm_489c5:
    PUSH_AF;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_A(0x1);
    CALL(aMenuClickSound);
    POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
    CALL(aExitMenu);
    hlcoord(11, 10, wTilemap);
    CALL(aFunction489ea);
    hlcoord(11, 9, wTilemap);
    LD_BC((1 << 8) | 8);
    CALL(aClearBox);
    POP_AF;
    LDH_addr_A(hInMenu);
    JP(mFunction4840c);

}

void Function489ea(void){
    PUSH_DE;
    LD_A_addr(wd475);
    AND_A(0xf);
    CALL(aMobile12_Bin2Dec);
    LD_A_addr(wd476);
    AND_A(0xf0);
    SWAP_A;
    INC_HL;
    CALL(aMobile12_Bin2Dec);
    LD_A_addr(wd476);
    AND_A(0xf);
    INC_HL;
    CALL(aMobile12_Bin2Dec);
    INC_HL;
    LD_DE(mString_48a38);
    CALL(aPlaceString);
    LD_A_addr(wd477);
    AND_A(0xf0);
    SWAP_A;
    INC_HL;
    CALL(aMobile12_Bin2Dec);
    LD_A_addr(wd477);
    AND_A(0xf);
    INC_HL;
    CALL(aMobile12_Bin2Dec);
    LD_A_addr(wd478);
    AND_A(0xf0);
    SWAP_A;
    INC_HL;
    CALL(aMobile12_Bin2Dec);
    LD_A_addr(wd478);
    AND_A(0xf);
    INC_HL;
    CALL(aMobile12_Bin2Dec);
    POP_DE;
    RET;

}

void String_48a38(void){
    //db ['"-@"'];

    return Function48a3a();
}

void Function48a3a(void){
    LD_HL(mMenuHeader_0x48a9c);
    CALL(aLoadMenuHeader);
    CALL(aFunction4873c);
    LD_A(0xa);
    LD_addr_A(w2DMenuCursorInitY);
    LD_A(0xb);
    LD_addr_A(w2DMenuCursorInitX);
    LD_A(0x1);
    LD_addr_A(wMenuCursorY);
    hlcoord(10, 8, wTilemap);
    LD_B(0x4);
    LD_C(0x8);
    CALL(aFunction48cdc);
    hlcoord(12, 10, wTilemap);
    LD_DE(mString_48aa1);
    CALL(aPlaceString);
    CALL(aStaticMenuJoypad);
    PUSH_AF;
    CALL(aPlayClickSFX);
    CALL(aExitMenu);
    POP_AF;
    BIT_A(1);
    JP_NZ (mFunction48a9a);
    LD_A_addr(wMenuCursorY);
    CP_A(0x1);
    IF_Z goto asm_48a98;
    LD_A_addr(wd003);
    SET_A(3);
    LD_addr_A(wd003);
    LD_A_addr(wd479);
    RES_A(0);
    LD_addr_A(wd479);
    XOR_A_A;
    LD_BC(0x4);
    LD_HL(wd475);
    CALL(aByteFill);
    JR(mFunction48a9a);

asm_48a98:
    AND_A_A;
    RET;

}

void Function48a9a(void){
    SCF;
    RET;

}

void MenuHeader_0x48a9c(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['10', '8', 'SCREEN_WIDTH - 1', '13'];

    return String_48aa1();
}

void String_48aa1(void){
    //db ['"Tell Now"'];
    //next ['"Tell Later@"']

    return Function48ab5();
}

void Function48ab5(void){
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON);
    JP_NZ (mFunction48c0f);
    LDH_A_addr(hJoyPressed);
    AND_A(B_BUTTON);
    JP_NZ (mFunction48c0d);
    LD_A_D;
    AND_A_A;
    IF_Z goto asm_48adf;
    CP_A(0x1);
    IF_Z goto asm_48ae7;
    CP_A(0x2);
    IF_Z goto asm_48af1;
    CP_A(0x3);
    IF_Z goto asm_48af9;
    CP_A(0x4);
    IF_Z goto asm_48b03;
    CP_A(0x5);
    IF_Z goto asm_48b0b;
    CP_A(0x6);
    goto asm_48b15;

asm_48adf:
    LD_HL(wd475);
    LD_A_hl;
    AND_A(0xf);
    goto asm_48b1d;

asm_48ae7:
    LD_HL(wd476);
    LD_A_hl;
    SWAP_A;
    OR_A(0xf0);
    goto asm_48b1d;

asm_48af1:
    LD_HL(wd476);
    LD_A_hl;
    AND_A(0xf);
    goto asm_48b1d;

asm_48af9:
    LD_HL(wd477);
    LD_A_hl;
    SWAP_A;
    OR_A(0xf0);
    goto asm_48b1d;

asm_48b03:
    LD_HL(wd477);
    LD_A_hl;
    AND_A(0xf);
    goto asm_48b1d;

asm_48b0b:
    LD_HL(wd478);
    LD_A_hl;
    SWAP_A;
    OR_A(0xf0);
    goto asm_48b1d;

asm_48b15:
    LD_HL(wd478);
    LD_A_hl;
    AND_A(0xf);
    goto asm_48b1d;

asm_48b1d:
    PUSH_HL;
    PUSH_AF;
    LD_E(0x0);
    hlcoord(11, 10, wTilemap);
    LD_A_D;

asm_48b25:
    AND_A_A;
    IF_Z goto asm_48b2c;
    INC_E;
    DEC_A;
    goto asm_48b25;

asm_48b2c:
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto asm_48b8d;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto asm_48b55;
    LD_A_hl;
    AND_A(D_LEFT);
    JP_NZ (mFunction48bd7);
    LD_A_hl;
    AND_A(D_RIGHT);
    IF_NZ goto asm_48b9d;
    hlcoord(11, 10, wTilemap);
    CALL(aFunction489ea);
    LD_A_addr(wd002);
    BIT_A(7);
    IF_NZ goto asm_48b51;

asm_48b51:
    POP_BC;
    POP_BC;
    AND_A_A;
    RET;

asm_48b55:
    POP_AF;
    LD_B_A;
    AND_A(0xf);
    AND_A_A;
    LD_A_B;
    IF_NZ goto asm_48b61;
    AND_A(0xf0);
    ADD_A(0xa);

asm_48b61:
    DEC_A;

asm_48b62:
    PUSH_DE;
    PUSH_AF;
    hlcoord(10, 9, wTilemap);
    LD_B(0x1);
    LD_C(0x8);
    CALL(aFunction48cdc);
    POP_AF;
    POP_DE;
    hlcoord(11, 10, wTilemap);
    LD_B_A;
    LD_A_D;
    CP_A(0x3);
    IF_C goto asm_48b7a;
    INC_HL;

asm_48b7a:
    LD_A_B;
    POP_HL;
    BIT_A(7);
    IF_Z goto asm_48b85;
    CALL(aFunction48c4d);
    goto asm_48b88;

asm_48b85:
    CALL(aFunction48c5a);

asm_48b88:
    LD_A(0xf0);
    JP(mFunction48c00);

asm_48b8d:
    POP_AF;
    LD_B_A;
    AND_A(0xf);
    CP_A(0x9);
    LD_A_B;
    IF_C goto asm_48b9a;
    AND_A(0xf0);
    ADD_A(0xff);

asm_48b9a:
    INC_A;
    goto asm_48b62;

asm_48b9d:
    PUSH_DE;
    hlcoord(10, 9, wTilemap);
    LD_B(0x1);
    LD_C(0x8);
    CALL(aFunction48cdc);
    POP_DE;
    LD_A_D;
    CP_A(0x6);
    IF_NC goto asm_48baf;
    INC_D;

asm_48baf:
    POP_AF;
    POP_HL;
    LD_B_A;
    LD_A_D;
    CP_A(0x6);
    LD_A_B;
    IF_Z goto asm_48bc4;
    BIT_A(7);
    IF_NZ goto asm_48bc4;
    INC_HL;
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    JR(masm_48bc7);

asm_48bc4:
    LD_A_hl;
    AND_A(0xf);

    return asm_48bc7();
}

void asm_48bc7(void){
    hlcoord(11, 10, wTilemap);
    PUSH_AF;
    LD_A_D;
    CP_A(0x3);
    POP_BC;
    LD_A_B;
    IF_C goto asm_48bd3;
    INC_HL;

asm_48bd3:
    LD_A(0xf);
    JR(mFunction48c00);

}

void Function48bd7(void){
    PUSH_DE;
    hlcoord(10, 9, wTilemap);
    LD_B(0x1);
    LD_C(0x8);
    CALL(aFunction48cdc);
    POP_DE;
    LD_A_D;
    AND_A_A;
    POP_AF;
    POP_HL;
    LD_B_A;
    LD_A_D;
    AND_A_A;
    LD_A_B;
    IF_Z goto asm_48bf3;
    BIT_A(7);
    IF_Z goto asm_48bf8;
    DEC_D;
    DEC_HL;

asm_48bf3:
    LD_A_hl;
    AND_A(0xf);
    JR(masm_48bc7);

asm_48bf8:
    DEC_D;
    LD_A_hl;
    SWAP_A;
    AND_A(0xf);
    JR(masm_48bc7);

}

void Function48c00(void){
    PUSH_AF;
    hlcoord(11, 10, wTilemap);
    CALL(aFunction489ea);
    LD_A(0x1);
    AND_A_A;
    POP_BC;
    LD_A_B;
    RET;

}

void Function48c0d(void){
    XOR_A_A;
    AND_A_A;

    return Function48c0f();
}

void Function48c0f(void){
    SCF;
    RET;

}

void Function48c11(void){
    LD_A_addr(wd002);
    BIT_A(7);
    IF_Z goto asm_48c20;
    LD_A_D;
    CP_A(0x3);
    IF_C goto asm_48c1e;
    INC_HL;

asm_48c1e:
    LD_hl(0x7f);

asm_48c20:
    LD_A_addr(wd002);
    SWAP_A;
    AND_A(0x3);
    INC_A;
    CP_A_B;
    IF_NZ goto asm_48c40;
    LD_A_addr(wd002);
    BIT_A(7);
    IF_Z goto asm_48c3a;
    RES_A(7);
    LD_addr_A(wd002);
    XOR_A_A;
    goto asm_48c40;

asm_48c3a:
    SET_A(7);
    LD_addr_A(wd002);
    XOR_A_A;

asm_48c40:
    SWAP_A;
    LD_B_A;
    LD_A_addr(wd002);
    AND_A(0xcf);
    OR_A_B;
    LD_addr_A(wd002);
    RET;

}

void Function48c4d(void){
    SWAP_A;
    AND_A(0xf0);
    PUSH_AF;
    LD_A_hl;
    AND_A(0xf);
    LD_hl_A;
    POP_AF;
    OR_A_hl;
    LD_hl_A;
    RET;

}

void Function48c5a(void){
    PUSH_AF;
    LD_A_hl;
    AND_A(0xf0);
    LD_hl_A;
    POP_AF;
    OR_A_hl;
    LD_hl_A;
    RET;

}

void Function48c63(void){
    LD_A(0x50);
    LD_de_A;
    LD_A_C;
    CP_A(0x30);
    IF_NC goto asm_48c8c;
    AND_A_A;
    IF_Z goto asm_48c8c;
    DEC_C;
    PUSH_DE;
    LD_H_D;
    LD_L_E;
    LD_A(0x50);
    LD_B(7);

asm_48c76:
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_48c76;
    LD_HL(mPrefectures);
    LD_A_C;
    CALL(aGetNthString);

asm_48c81:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    CP_A(0x50);
    IF_NZ goto asm_48c81;
    AND_A_A;
    POP_DE;
    RET;


asm_48c8c:
    SCF;
    RET;

}

void Function48c8e(void){
//  //  unreferenced
    LD_HL(wd019 + 0x11);
    LD_D_H;
    LD_E_L;
    FARCALL(aFunction48c63);
    hlcoord(10, 7, wTilemap);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    RET;

}

void Function48ca3(void){
//  //  unreferenced
    PUSH_AF;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;
    LD_B(0);
    LD_C(0);
    LD_D(0);

asm_48cad:
    CP_A(100);
    IF_C goto asm_48cb6;
    SUB_A(100);
    INC_B;
    goto asm_48cad;


asm_48cb6:
    CP_A(10);
    IF_C goto asm_48cbf;
    SUB_A(10);
    INC_C;
    goto asm_48cb6;


asm_48cbf:
    CP_A(1);
    IF_C goto asm_48cc7;
    DEC_A;
    INC_D;
    goto asm_48cbf;


asm_48cc7:
    LD_A_B;
    CALL(aMobile12_Bin2Dec);
    INC_HL;
    LD_A_C;
    CALL(aMobile12_Bin2Dec);
    INC_HL;
    LD_A_D;
    CALL(aMobile12_Bin2Dec);
    POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
    RET;

}

void Function48cda(tile_t* de, uint8_t b, uint8_t c){
    // LD_H_D;
    // LD_L_E;

    return Function48cdc(de, b, c);
}

void Function48cdc(tile_t* hl, uint8_t b, uint8_t c){
    // PUSH_BC;
    // PUSH_HL;
    // CALL(aFunction48cfd);
    Function48cfd(hl, b, c);
    // POP_HL;
    // POP_BC;
    // LD_DE(wAttrmap - wTilemap);
    // ADD_HL_DE;
    hl += wAttrmap - wTilemap;
    // INC_B;
    // INC_B;
    b += 2;
    // INC_C;
    // INC_C;
    c += 2;
    // LD_A(0x0);
    uint8_t a = 0x0;

    do {
    // asm_48ced:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        tile_t* hl2 = hl;
        
        do {
        // asm_48cef:
            // LD_hli_A;
            *(hl2++) = a;
            // DEC_C;
            // IF_NZ goto asm_48cef;
        } while(--c2 != 0);
        // POP_HL;
        // LD_DE(0x14);
        // ADD_HL_DE;
        hl += 0x14;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto asm_48ced;
    } while(--b != 0);
    // RET;
}

void Function48cfd(tile_t* hl, uint8_t b, uint8_t c){
    // PUSH_HL;
    tile_t* hl2 = hl;
    // LD_A(0x4);
    // LD_hli_A;
    *(hl2++) = 0x4;
    // INC_A;
    // CALL(aFunction48d2a);
    hl2 = Function48d2a(hl2, 0x5, c);
    // INC_A;
    // LD_hl_A;
    *hl2 = 0x6;
    // POP_HL;
    // LD_DE(0x14);
    // ADD_HL_DE;
    hl += 0x14;

    do {
    // asm_48d0c:
        // PUSH_HL;
        hl2 = hl;
        // LD_A(0x7);
        // LD_hli_A;
        *(hl2++) = 0x7;
        // LD_A(0x7f);
        // CALL(aFunction48d2a);
        hl2 = Function48d2a(hl2, 0x7f, c);
        // LD_hl(0x8);
        *hl2 = 0x8;
        // POP_HL;
        // LD_DE(0x14);
        // ADD_HL_DE;
        hl += 0x14;
        // DEC_B;
        // IF_NZ goto asm_48d0c;
    } while(--b != 0);
    // LD_A(0x9);
    // LD_hli_A;
    *(hl++) = 0x9;
    // LD_A(0xa);
    // CALL(aFunction48d2a);
    hl = Function48d2a(hl, 0xa, c);
    // LD_hl(0xb);
    *hl = 0xb;
    // RET;
}

tile_t* Function48d2a(tile_t* hl, tile_t a, uint8_t c){
    // LD_D_C;

    do {
    // asm_48d2b:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_D;
        // IF_NZ goto asm_48d2b;
    } while(--c != 0);
    // RET;
    return hl;
}

void Function48d30(void){
    LD_HL(wd475);
    CALL(aFunction48d4a);
    LD_HL(wd477);
    CALL(aFunction48d4a);
    RET;

}

void Function48d3d(void){
    LD_HL(wd475);
    CALL(aFunction48d94);
    LD_HL(wd477);
    CALL(aFunction48d94);
    RET;

}

void Function48d4a(void){
    INC_HL;
    LD_A_hl;
    LD_B_A;
    AND_A(0xf);
    LD_C_A;
    SRL_B;
    SRL_B;
    SRL_B;
    SRL_B;
    PUSH_BC;
    LD_C(10);
    LD_A_B;
    CALL(aSimpleMultiply);
    POP_BC;
    ADD_A_C;
    LD_hld_A;
    XOR_A_A;
    LDH_addr_A(hMultiplicand + 0);
    LDH_addr_A(hMultiplicand + 1);
    LD_A_hl;
    SRL_A;
    SRL_A;
    SRL_A;
    SRL_A;
    LD_C(10);
    CALL(aSimpleMultiply);
    LD_B_A;
    LD_A_hli;
    AND_A(0xf);
    ADD_A_B;
    LDH_addr_A(hMultiplicand + 2);
    LD_A(100);
    LDH_addr_A(hMultiplier);
    CALL(aMultiply);
    LDH_A_addr(hProduct + 2);
    LD_B_A;
    LDH_A_addr(hProduct + 3);
    LD_C_A;
    LD_E_hl;
    ADD_A_E;
    LD_C_A;
    LD_A_B;
    ADC_A(0);
    LD_B_A;
    LD_A_C;
    LD_hld_A;
    LD_hl_B;
    RET;

}

void Function48d94(void){
    XOR_A_A;
    LDH_addr_A(hDividend + 0);
    LDH_addr_A(hDividend + 1);
    LD_A_hli;
    LDH_addr_A(hDividend + 0);
    LD_A_hl;
    LDH_addr_A(hDividend + 1);
    LD_A(100);
    LDH_addr_A(hDivisor);
    LD_B(2);
    CALL(aDivide);
    LDH_A_addr(hRemainder);
    LD_C(10);
    CALL(aSimpleDivide);
    SLA_B;
    SLA_B;
    SLA_B;
    SLA_B;
    OR_A_B;
    LD_hld_A;
    LDH_A_addr(hQuotient + 3);
    LD_C(10);
    CALL(aSimpleDivide);
    SLA_B;
    SLA_B;
    SLA_B;
    SLA_B;
    OR_A_B;
    LD_hl_A;
    RET;

}
