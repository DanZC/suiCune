#include "../constants.h"
#include "mobile_menu.h"
#include "mobile_12.h"
#include "mobile_5c.h"
#include "fixed_words.h"
#include "../engine/menus/main_menu.h"
#include "../engine/menus/save.h"
#include "../engine/gfx/crystal_layouts.h"
#include "../engine/gfx/dma_transfer.h"
#include "../home/tilemap.h"
#include "../home/delay.h"
#include "../home/copy.h"
#include "../home/menu.h"
#include "../home/text.h"
#include "../home/gfx.h"
#include "../home/sram.h"
#include "../home/joypad.h"
#include "../data/text/common.h"

bool MainMenu_Mobile(void){
    // return false; // Dummied out. TODO: Finishing converting Mobile menu.
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // LD_A(MUSIC_MOBILE_ADAPTER_MENU);
    // LD_addr_A(wMapMusic);
    wram->wMapMusic = MUSIC_MOBILE_ADAPTER_MENU;
    // LD_DE(MUSIC_MOBILE_ADAPTER_MENU);
    // CALL(aFunction4a6c5);
    Function4a6c5(MUSIC_MOBILE_ADAPTER_MENU);
    Function49f0a();
    Function49f16();
    return false;
}

// MobileMenu_Init
void Function49f0a(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aFunction4a3a7);
    Function4a3a7();
    // CALL(aFunction4a492);
    Function4a492();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // return Function49f16();
    //  TODO: Finish converting Function49f16
}

// MobileMenu_Top
void Function49f16(void){
entry:
    // CALL(aMobileMenu_InitMenuBuffers);
    MobileMenu_InitMenuBuffers();
    // LD_C(12);
    // CALL(aDelayFrames);
    DelayFrames_Conv(12);
    // hlcoord(4, 0, wTilemap);
    // LD_B(10);
    // LD_C(10);
    // CALL(aFunction48cdc);
    Function48cdc(coord(3, 0, wram->wTilemap), 10, 12);
    // hlcoord(6, 2, wTilemap);
    // LD_DE(mMobileString1);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileString1), coord(5, 2, wram->wTilemap));
    // hlcoord(0, 12, wTilemap);
    // LD_B(4);
    // LD_C(SCREEN_HEIGHT);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, SCREEN_HEIGHT);
    // XOR_A_A;
    // LD_DE(mString_0x49fe9);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileStrings2[0]), coord(1, 14, wram->wTilemap));
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aStaticMenuJoypad);
    uint8_t joypad = StaticMenuJoypad_Conv();
    // LD_HL(wMenuCursorY);
    // LD_B_hl;
    uint8_t cursorY = wram->wMenuCursorY;
    // PUSH_BC;
    // goto check_buttons;
    while(1) {
    // check_buttons:
        // BIT_A(A_BUTTON_F);
        // IF_NZ goto a_button;
        if(bit_test(joypad, A_BUTTON_F)) {
        // a_button:
            // LD_HL(wMenuCursorY);
            // LD_A_hl;
            switch(wram->wMenuCursorY) {
                // CP_A(1);
                // JP_Z (mFunction4a098);
                case 1: Function4a098(); goto entry;
                // CP_A(2);
                // JP_Z (mFunction4a0b9);
                case 2: Function4a0b9(); goto entry;
                // CP_A(3);
                // JP_Z (mFunction4a0c2);
                case 3: Function4a0c2(); goto entry;
                // CP_A(4);
                // JP_Z (mFunction4a100);
                case 4: Function4a100(); goto entry;
                default: break;
            }
            // LD_A(1);
            // CALL(aMenuClickSound);
            MenuClickSound_Conv(1);
            goto b_button;
        }
        // BIT_A(B_BUTTON_F);
        // IF_NZ goto b_button;
        else if(bit_test(joypad, B_BUTTON_F)) {
        b_button:
            // POP_BC;
            // CALL(aClearBGPalettes);
            ClearBGPalettes_Conv();
            // CALL(aClearTilemap);
            ClearTilemap_Conv2();
            // LD_A(MUSIC_MAIN_MENU);
            // LD_addr_A(wMapMusic);
            wram->wMapMusic = MUSIC_MAIN_MENU;
            // LD_DE(MUSIC_MAIN_MENU);
            // CALL(aFunction4a6c5);
            Function4a6c5(MUSIC_MAIN_MENU);
            // RET;
            return;
        }
        // goto next;

    // next:
        // LD_HL(wMenuCursorY);
        // LD_A_hl;
        // DEC_A;
        // LD_HL(mMobileStrings2);
        // CALL(aGetNthString);
        // LD_D_H;
        // LD_E_L;
        // hlcoord(1, 13, wTilemap);
        // LD_B(4);
        // LD_C(SCREEN_HEIGHT);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(1, 13, wram->wTilemap), SCREEN_HEIGHT, 4);
        // hlcoord(1, 14, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(MobileStrings2[wram->wMenuCursorY - 1]), coord(1, 14, wram->wTilemap));
        // JP(mFunction49f16_useless_jump);

    // useless_jump:
        // CALL(aMobileMenu_InitMenuBuffers);
        MobileMenu_InitMenuBuffers();
        // POP_BC;
        // LD_HL(wMenuCursorY);
        // LD_hl_B;
        wram->wMenuCursorY = cursorY;
        // LD_B(0xa);
        // LD_C(0x1);
        // hlcoord(5, 1, wTilemap);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(4, 1, wram->wTilemap), 0x1, 0xa);
        // JP(mFunction49f16_joy_loop);

    // joy_loop:
        // CALL(aScrollingMenuJoypad);
        joypad = ScrollingMenuJoypad_Conv();
        // LD_HL(wMenuCursorY);
        // LD_B_hl;
        // PUSH_BC;
        cursorY = wram->wMenuCursorY;
    }
}

const char MobileString1[] = ""
            "CARD FOLDER" //db ['"めいしフォルダー"'];
    t_next  "MESSAGES" //next ['"あいさつ"']
    t_next  "PROFILE" //next ['"プロフィール"']
    t_next  "SETTINGS" //next ['"せ<TTE>い"']
    t_next  "EXIT" //next ['"もどる"']
            "@"; //db ['"@"'];

const char* MobileStrings2[] = {
//  string 0 (String_0x49fe9)
           "Create and view"        //db ['"めいし¯つくったり"'];
    t_next "friends' CARDS.",       //next ['"ほぞんしておける\u3000フォルダーです@"']
//  string 1
            "Set MESSAGES"          //db ['"モバイルたいせんや\u3000じぶんのめいしで"'];
    t_next  "shown to others.@",    //next ['"つかう\u3000あいさつ¯つくります@"']
//  string 2
            "Change your age"       //db ['"あなた<NO>じゅうしょや\u3000ねんれいの"'];
    t_next  "and address.@",        //next ['"せ<TTE>い¯かえられます@"']
//  string 3
            "Change settings"       //db ['"モバイルセンター<NI>せつぞくするとき"'];
    t_next  "used to connect.@",    //next ['"ひつような\u3000こと¯きめます@"']
//  string 4
            "Return to the"         //db ['"まえ<NO>がめん\u3000<NI>もどります"'];
    t_next  "previous screen.@",    //next ['"@"']
};

void MobileMenu_InitMenuBuffers(void){
    // LD_HL(w2DMenuCursorInitY);
    // LD_A(2);
    // LD_hli_A;
    wram->w2DMenuCursorInitY = 2;
    // LD_A(5);  // w2DMenuCursorInitX
    // LD_hli_A;
    wram->w2DMenuCursorInitX = 4;
    // LD_A(5);  // w2DMenuNumRows
    // LD_hli_A;
    wram->w2DMenuNumRows = 5;
    // LD_A(1);  // w2DMenuNumCols
    // LD_hli_A;
    wram->w2DMenuNumCols = 1;
    // LD_hl(0x0);  // w2DMenuFlags1
    // SET_hl(5);
    wram->w2DMenuFlags1 = (1 << 5);
    // INC_HL;
    // XOR_A_A;  // w2DMenuFlags2
    // LD_hli_A;
    wram->w2DMenuFlags2 = 0;
    // LD_A(0x20);  // w2DMenuCursorOffsets
    // LD_hli_A;
    wram->w2DMenuCursorOffsets = 0x20;
// could have done "ld a, A_BUTTON | D_UP | D_DOWN | B_BUTTON" instead
    // LD_A(A_BUTTON);
    // ADD_A(D_UP);
    // ADD_A(D_DOWN);
    // ADD_A(B_BUTTON);
    // LD_hli_A;  // wMenuJoypadFilter
    wram->wMenuJoypadFilter = A_BUTTON | D_UP | D_DOWN | B_BUTTON;
    // LD_A(1);
    // LD_hli_A;  // wMenuCursorY, wMenuCursorX
    wram->wMenuCursorY = 1;
    // LD_hli_A;  // wMenuCursorY, wMenuCursorX
    wram->wMenuCursorX = 1;
    // RET;
}

// MobileMenu_CardFolder
void Function4a098(void){
    // LD_A(2);
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(2);
    // CALL(aPlaceHollowCursor);
    PlaceHollowCursor_Conv();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // FARCALL(aFunction89de0); // TODO: Convert Function89de0
    // CALL(aCall_ExitMenu);
    ExitMenu_Conv2();
    // CALL(aMG_Mobile_Layout_LoadPals);
    MG_Mobile_Layout_LoadPals();
    // CALL(aFunction4a485);
    Function4a485();
    // POP_BC;
    // JP(mFunction49f16);
    // Just return and have the caller loop
}

// MobileMenu_Messages
void Function4a0b9(void){
    // LD_A(2);
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(2);
    // POP_BC;
    // JP(mFunction4a4c4);
    Function4a4c4();
}

// MobileMenu_Profile
void Function4a0c2(void){
    // return asm_4a111(); // Dummied out
    // LD_A(2);
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(2);
    // LD_A(BANK(sPlayerData));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asPlayerData));
    // LD_HL(sPlayerData + wPlayerName - wPlayerData);
    // LD_DE(wPlayerName);
    // LD_BC(NAME_LENGTH_JAPANESE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wPlayerName, GBToRAMAddr(sPlayerData + wPlayerName - wPlayerData), NAME_LENGTH);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // FARCALL(av_LoadData);
    v_LoadData();
    // LD_C(2);
    // CALL(aDelayFrames);
    DelayFrames_Conv(2);
    // LD_C(0x1);
    // CALL(aInitMobileProfile);
    uint8_t a = InitMobileProfile(0x1);
    // PUSH_AF;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // POP_AF;
    // AND_A_A;
    // IF_NZ goto skip_save;
    if(a == 0) {
        // FARCALL(av_SaveData);
        v_SaveData();
    }

// skip_save:
    // LD_C(5);
    // CALL(aDelayFrames);
    DelayFrames_Conv(5);
    // JR(masm_4a111);
    return asm_4a111();
}

// MobileMenu_Settings
void Function4a100(void){
    // LD_A(2);
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(2);
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aFunction4a13b);
    Function4a13b();
    Function4a149();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();

    return asm_4a111();
}

// MobileMenu_ReturnToMobileMenuTop
void asm_4a111(void){
    // POP_BC;
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // JP(mFunction49f0a);
    Function49f0a();
    // Just return and have the caller loop
}

void Function4a118(void){
    // LD_HL(w2DMenuCursorInitY);
    // LD_A(0x1);
    // LD_hli_A;
    wram->w2DMenuCursorInitY = 0x1;
    // LD_A(0xd);
    // LD_hli_A;
    wram->w2DMenuCursorInitX = 0xd;
    // LD_A(0x3);
    // LD_hli_A;
    wram->w2DMenuNumRows = 0x3;
    // LD_A(0x1);
    // LD_hli_A;
    wram->w2DMenuNumCols = 0x1;
    // LD_hl(0x0);
    // SET_hl(5);
    wram->w2DMenuFlags1 = MENU_UNUSED_3;
    // INC_HL;
    // XOR_A_A;
    // LD_hli_A;
    wram->w2DMenuFlags2 = 0x0;
    // LD_A(0x20);
    // LD_hli_A;
    wram->w2DMenuCursorOffsets = (2 << 4) | 0;
    // LD_A(0x1);
    // ADD_A(0x2);
    // LD_hli_A;
    wram->wMenuJoypadFilter = (A_BUTTON | B_BUTTON);
    // LD_A(0x1);
    // LD_hli_A;
    wram->wMenuCursorY = 0x1;
    // LD_hli_A;
    wram->wMenuCursorX = 0x1;
    // RET;
}

void Function4a13b(void){
    // CALL(aFunction4a3a7);
    Function4a3a7();
    // CALL(aFunction4a492);
    Function4a492();
    // CALL(aFunction4a373);
    Function4a373();
    // LD_C(10);
    // CALL(aDelayFrames);
    DelayFrames_Conv(10);
    // return Function4a149();
}

void Function4a149(void){
entry:
    // hlcoord(1, 2, wTilemap);
    // LD_B(0x6);
    // LD_C(0x10);
    // CALL(aFunction48cdc);
    Function48cdc(coord(1, 2, wram->wTilemap), 0x6, 0x11);
    // hlcoord(3, 4, wTilemap);
    // LD_DE(mString_4a1ef);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_4a1ef), coord(3, 4, wram->wTilemap));
    // hlcoord(0, 12, wTilemap);
    // LD_B(0x4);
    // LD_C(0x12);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 12, wram->wTilemap), 0x4, 0x12);
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_HL(mStrings_4a23d);
    // CALL(aGetNthString);
    // LD_D_H;
    // LD_E_L;
    // hlcoord(1, 13, wTilemap);
    // LD_B(0x4);
    // LD_C(0x12);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 13, wram->wTilemap), 0x12, 0x4);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Strings_4a23d[wram->wMenuCursorY - 1]), coord(1, 14, wram->wTilemap));
    // FARCALL(aMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    Mobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aStaticMenuJoypad);
    uint8_t joypad = StaticMenuJoypad_Conv();
    // LD_HL(wMenuCursorY);
    // LD_B_hl;
    // PUSH_BC;
    uint8_t cursorY = wram->wMenuCursorY;
    // JR(masm_4a19d); // Inlined
    while(1) {
        // BIT_A(0);
        // IF_NZ goto asm_4a1a7;
        if(bit_test(joypad, A_BUTTON_F)) {
        // asm_4a1a7:
            // LD_HL(wMenuCursorY);
            // LD_A_hl;
            switch(wram->wMenuCursorY) {
                // CP_A(0x1);
                // JP_Z (mFunction4a20e);
                case 0x1: Function4a20e(); goto entry;
                // CP_A(0x2);
                // JP_Z (mFunction4a221);
                case 0x2: Function4a221(); goto entry;
            }
            // LD_A(0x1);
            // CALL(aMenuClickSound);
            MenuClickSound_Conv(0x1);
            goto asm_4a1ba;
        }
        // BIT_A(1);
        // IF_NZ goto asm_4a1ba;
        else if(bit_test(joypad, B_BUTTON_F)) {
        asm_4a1ba:
            // POP_BC;
            // RET;
            return;
        }
        // goto asm_4a1bc;

    // asm_4a1bc:
        // LD_HL(wMenuCursorY);
        // LD_A_hl;
        // DEC_A;
        // LD_HL(mStrings_4a23d);
        // CALL(aGetNthString);
        // LD_D_H;
        // LD_E_L;
        // hlcoord(1, 13, wTilemap);
        // LD_B(0x4);
        // LD_C(0x12);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(1, 13, wram->wTilemap), 0x12, 0x4);
        // hlcoord(1, 14, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(Strings_4a23d[wram->wMenuCursorY - 1]), coord(1, 14, wram->wTilemap));
        // goto asm_4a1db;

    // asm_4a1db:
        // CALL(aFunction4a373);
        Function4a373();
        // POP_BC;
        // LD_HL(wMenuCursorY);
        // LD_hl_B;
        wram->wMenuCursorY = cursorY;
        // LD_BC((6 << 8) | 1);
        // hlcoord(2, 3, wTilemap);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(2, 3, wram->wTilemap), 1, 6);
        // JP(mFunction4a195); // Inlined
        // CALL(aScrollingMenuJoypad);
        joypad = ScrollingMenuJoypad_Conv();
        // LD_HL(wMenuCursorY);
        // LD_B_hl;
        // PUSH_BC;
        cursorY = wram->wMenuCursorY;

        // return asm_4a19d();
    }
}

// void Function4a195(void){
//     CALL(aScrollingMenuJoypad);
//     LD_HL(wMenuCursorY);
//     LD_B_hl;
//     PUSH_BC;

//     return asm_4a19d();
// }

// void asm_4a19d(void){
//     BIT_A(0);
//     IF_NZ goto asm_4a1a7;
//     BIT_A(1);
//     IF_NZ goto asm_4a1ba;
//     goto asm_4a1bc;

// asm_4a1a7:
//     LD_HL(wMenuCursorY);
//     LD_A_hl;
//     CP_A(0x1);
//     JP_Z (mFunction4a20e);
//     CP_A(0x2);
//     JP_Z (mFunction4a221);
//     LD_A(0x1);
//     CALL(aMenuClickSound);

// asm_4a1ba:
//     POP_BC;
//     RET;

// asm_4a1bc:
//     LD_HL(wMenuCursorY);
//     LD_A_hl;
//     DEC_A;
//     LD_HL(mStrings_4a23d);
//     CALL(aGetNthString);
//     LD_D_H;
//     LD_E_L;
//     hlcoord(1, 13, wTilemap);
//     LD_B(0x4);
//     LD_C(0x12);
//     CALL(aClearBox);
//     hlcoord(1, 14, wTilemap);
//     CALL(aPlaceString);
//     goto asm_4a1db;

// asm_4a1db:
//     CALL(aFunction4a373);
//     POP_BC;
//     LD_HL(wMenuCursorY);
//     LD_hl_B;
//     LD_BC((6 << 8) | 1);
//     hlcoord(2, 3, wTilemap);
//     CALL(aClearBox);
//     JP(mFunction4a195);

// }

const char String_4a1ef[] =
           "MOBILE CENTER"      //db ['"モバイルセンター¯えらぶ"'];
    t_next "LOG-IN PASSWORD"    //next ['"ログインパスワード¯いれる"']
    t_next "BACK";              //next ['"もどる@"']

// MobileMenu_MobileCenter
void Function4a20e(void){
    // LD_A(0x1);
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(0x1);
    // FARCALL(aFunction1719c8);
    Function1719c8();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // JR(mFunction4a239);
    return Function4a239();
}

// MobileMenu_PasswordSet
void Function4a221(void){
    // LD_A(0x1);
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(0x1);
    // CALL(aFunction4a28a);
    // JR_C (mFunction4a239);
    if(Function4a28a())
        return Function4a239();
    // CALL(aFunction4a373);
    Function4a373();
    // LD_A(0x2);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 0x2;
    // goto asm_4a235;

// asm_4a235:
    // POP_BC;
    // JP(mFunction4a149);
}

void Function4a239(void){
    // POP_BC;
    // JP(mFunction4a13b);
    Function4a13b();
}

const char* Strings_4a23d[] = {
            "Choose the MOBILE" //db ['"いつも\u3000せつぞく¯する"'];
    t_next  "CENTER to use.",   //next ['"モバイルセンター¯えらびます@"']

            "The PASSWORD used" //db ['"モバイルセンター<NI>せつぞくするとき"'];
    t_next  "to connect.",      //next ['"つかうパスワード¯ほぞんできます@"']

            "Return to the"     //db ['"まえ<NO>がめん\u3000<NI>もどります@"'];
    t_next  "previous screen.",

            "" //db ['"@"'];
};

// MobileMenu_ChangePasswordMenu
bool Function4a28a(void){
    // hlcoord(2, 3, wTilemap);
    // LD_BC((6 << 8) | 1);
    // LD_A(0x7f);
    // CALL(aFunction4a6d8);
    Function4a6d8(coord(2, 3, wram->wTilemap), 6, 1, 0x7f);
    // CALL(aPlaceHollowCursor);
    PlaceHollowCursor_Conv();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileLoginPassword));
    // LD_A_addr(0xaa4b);
    uint8_t a = gb_read(sMobileLoginPassword);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // AND_A_A;
    // IF_Z goto asm_4a2df;
    if(a != 0) {
        // hlcoord(12, 0, wTilemap);
        // LD_B(0x5);
        // LD_C(0x6);
        // CALL(aFunction48cdc);
        Function48cdc(coord(12, 0, wram->wTilemap), 0x5, 0x6);
        // hlcoord(14, 1, wTilemap);
        // LD_DE(mString_4a34b);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_4a34b), coord(14, 1, wram->wTilemap));
        // FARCALL(aMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
        Mobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
        // CALL(aFunction4a118);
        Function4a118();
        // CALL(aScrollingMenuJoypad);
        // PUSH_AF;
        uint8_t joypad = ScrollingMenuJoypad_Conv();
        // CALL(aPlayClickSFX);
        PlayClickSFX_Conv();
        // POP_AF;
        // BIT_A(B_BUTTON_F);
        // IF_NZ goto quit;
        // LD_A_addr(wMenuCursorY);
        // CP_A(0x2);
        // IF_Z goto DeleteLoginPassword;
        // CP_A(0x3);
        // IF_Z goto quit;
        if(bit_test(joypad, B_BUTTON_F) || wram->wMenuCursorY == 0x3)
            goto quit;

        else if(wram->wMenuCursorY == 0x2) {
        // DeleteLoginPassword:
            // CALL(aPlaceHollowCursor);
            PlaceHollowCursor_Conv();
            // LD_HL(mDeleteSavedLoginPasswordText);
            // CALL(aPrintText);
            PrintText_Conv2(DeleteSavedLoginPasswordText);
            // hlcoord(14, 7, wTilemap);
            // LD_B(3);
            // LD_C(4);
            // CALL(aTextbox);
            Textbox_Conv2(coord(14, 7, wram->wTilemap), 3, 4);
            // FARCALL(aMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
            Mobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
            // LD_HL(mDeletePassword_YesNo_MenuHeader);
            // CALL(aLoadMenuHeader);
            LoadMenuHeader_Conv2(&DeletePassword_YesNo_MenuHeader);
            // CALL(aVerticalMenu);
            bool cancel = !VerticalMenu_Conv();
            // BIT_A(B_BUTTON_F);
            // IF_NZ goto dont_delete_password;
            // LD_A_addr(wMenuCursorY);
            // CP_A(0x2);
            // IF_Z goto dont_delete_password;
            if(!cancel && wram->wMenuCursorY != 0x2) {
                // LD_A(BANK(sMobileLoginPassword));
                // CALL(aOpenSRAM);
                OpenSRAM_Conv(MBANK(asMobileLoginPassword));
                // LD_HL(sMobileLoginPassword);
                // XOR_A_A;
                // LD_BC(MOBILE_LOGIN_PASSWORD_LENGTH);
                // CALL(aByteFill);
                ByteFill_Conv2(GBToRAMAddr(sMobileLoginPassword), MOBILE_LOGIN_PASSWORD_LENGTH, 0x0);
                // CALL(aCloseSRAM);
                CloseSRAM_Conv();
                // LD_HL(mDeletedTheLoginPasswordText);
                // CALL(aPrintText);
                PrintText_Conv2(DeletedTheLoginPasswordText);
                // CALL(aJoyWaitAorB);
                JoyWaitAorB_Conv();
            }

        // dont_delete_password:
            // CALL(aExitMenu);
            ExitMenu_Conv2();

        quit:
            // CALL(aCall_ExitMenu);
            ExitMenu_Conv2();
            // FARCALL(aMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
            Mobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap_Conv();
            // XOR_A_A;
            // RET;
            return false;
        }
    }

// asm_4a2df:
    // FARCALL(aFunction11765d); // TOOD: Convert Function Function11765d
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aCall_ExitMenu);
    ExitMenu_Conv2();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // SCF;
    // RET;
    return true;
}

void MenuHeader_0x4a346(void){
//  //  unreferenced
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['12', '0', 'SCREEN_WIDTH - 1', '6'];
}

const char String_4a34b[] = 
            "CHANGE"    //db ['"いれなおす"'];
    t_next  "DELETE"    //next ['"けす"']
    t_next  "CANCEL@";  //next ['"もどる@"']

const txt_cmd_s DeleteSavedLoginPasswordText[] = {
    text_far(v_DeleteSavedLoginPasswordText)
    text_end
};

const txt_cmd_s DeletedTheLoginPasswordText[] = {
    text_far(v_DeletedTheLoginPasswordText)
    text_end
};

static const struct MenuData MenuData_0x4a36a = {
    .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING | STATICMENU_WRAP,  // flags
    .verticalMenu = {
        .count = 2,  // items
        .options = (const char*[]) {
            "YES@", //db ['"はい@"'];
            "NO@",  //db ['"いいえ@"'];
        },
    },
};

const struct MenuHeader DeletePassword_YesNo_MenuHeader = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(14, 7, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    .data = &MenuData_0x4a36a,
    .defaultOption = 2,  // default option
};

void Function4a373(void){
    // LD_HL(w2DMenuCursorInitY);
    // LD_A(0x4);
    // LD_hli_A;
    wram->w2DMenuCursorInitY = 0x4;
    // LD_A(0x2);
    // LD_hli_A;
    wram->w2DMenuCursorInitX = 0x2;
    // LD_A(0x3);
    // LD_hli_A;
    wram->w2DMenuNumRows = 0x3;
    // LD_A(0x1);
    // LD_hli_A;
    wram->w2DMenuNumCols = 0x3;
    // LD_hl(0x0);
    // SET_hl(5);
    wram->w2DMenuFlags1 = MENU_UNUSED_3;
    // INC_HL;
    // XOR_A_A;
    // LD_hli_A;
    wram->w2DMenuFlags2 = 0x0;
    // LD_A(0x20);
    // LD_hli_A;
    wram->w2DMenuCursorOffsets = (2 << 4) | 0;
    // LD_A(0x1);
    // ADD_A(0x40);
    // ADD_A(0x80);
    // ADD_A(0x2);
    // LD_hli_A;
    wram->wMenuJoypadFilter = (A_BUTTON | B_BUTTON | D_UP | D_DOWN);
    // LD_A(0x1);
    // LD_hli_A;
    wram->wMenuCursorY = 0x1;
    // LD_hli_A;
    wram->wMenuCursorX = 0x1;
    // RET;

}

void Function4a39a(void){
//  //  unreferenced
    CALL(aFunction4a485);
    CALL(aFunction4a492);
    CALL(aFunction4a3aa);
    CALL(aSetPalettes);
    RET;

}

// MobileMenu_InitGFX
void Function4a3a7(void){
    // CALL(aFunction4a485);
    Function4a485();
    return Function4a3aa();
}

// MobileMenu_InitTilemap
void Function4a3aa(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC((3 << 8) | 1);
    // XOR_A_A;
    // CALL(aFunction4a6d8);
    tile_t* hl = Function4a6d8(coord(0, 0, wram->wTilemap), 3, 1, 0x0);
    // LD_BC((1 << 8) | 1);
    // LD_A(0x1);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 1, 0x1);
    // LD_BC((1 << 8) | 1);
    // XOR_A_A;
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 1, 0x0);
    // LD_BC((1 << 8) | 1);
    // LD_A(0x1);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 1, 0x1);
    // LD_BC((4 << 8) | 1);
    // LD_A(0x2);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 4, 1, 0x2);
    // LD_BC((1 << 8) | 1);
    // LD_A(0x3);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 1, 0x3);
    // LD_BC((1 << 8) | 1);
    // LD_A(0x7f);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 1, 0x7f);
    // hlcoord(1, 0, wTilemap);
    // LD_A(0x1);
    // LD_BC((3 << 8) | 18);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(coord(1, 0, wram->wTilemap), 3, 18, 0x1);
    // LD_BC((1 << 8) | 18);
    // LD_A(0x0);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 18, 0x0);
    // LD_BC((1 << 8) | 18);
    // LD_A(0x1);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 18, 0x1);
    // LD_BC((1 << 8) | 18);
    // LD_A(0x2);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 18, 0x2);
    // LD_BC((11 << 8) | 18);
    // LD_A(0x7f);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 11, 18, 0x7f);
    // hlcoord(19, 0, wTilemap);
    // LD_BC((3 << 8) | 1);
    // LD_A(0x0);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(coord(19, 0, wram->wTilemap), 3, 1, 0x0);
    // LD_BC((1 << 8) | 1);
    // LD_A(0x1);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 1, 0x1);
    // LD_BC((1 << 8) | 1);
    // XOR_A_A;
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 1, 0x0);
    // LD_BC((1 << 8) | 1);
    // LD_A(0x1);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 1, 0x1);
    // LD_BC((4 << 8) | 1);
    // LD_A(0x2);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 4, 1, 0x2);
    // LD_BC((1 << 8) | 1);
    // LD_A(0x3);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 1, 0x3);
    // LD_BC((1 << 8) | 1);
    // LD_A(0x7f);
    // CALL(aFunction4a6d8);
    hl = Function4a6d8(hl, 1, 1, 0x7f);
    // RET;
}

void Function4a449(void){
//  //  unreferenced
    LD_BC(3 * SCREEN_WIDTH);
    LD_A(0x0);
    hlcoord(0, 0, wTilemap);
    CALL(aByteFill);
    LD_BC(2 * SCREEN_WIDTH);
    LD_A(0x1);
    CALL(aByteFill);
    LD_BC(2 * SCREEN_WIDTH);
    LD_A(0x0);
    CALL(aByteFill);
    LD_BC(2 * SCREEN_WIDTH);
    LD_A(0x1);
    CALL(aByteFill);
    LD_BC(SCREEN_WIDTH);
    LD_A(0x2);
    CALL(aByteFill);
    LD_BC(SCREEN_WIDTH);
    LD_A(0x3);
    CALL(aByteFill);
    LD_BC(SCREEN_WIDTH);
    LD_A(0x7f);
    CALL(aByteFill);
    RET;

}

// MobileMenu_LoadGFX
void Function4a485(void){
    // LD_DE(mMobileMenuGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x00);
    // LD_BC((BANK(aMobileMenuGFX) << 8) | 13);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, MobileMenuGFX, 0, 13);
    // RET;
}

// MobileMenu_GetLayout
void Function4a492(void){
    // CALL(av_CrystalCGB_MobileLayout0);
    v_CrystalCGB_MobileLayout0();
    // RET;
}

bool MainMenu_MobileStudium(void){
    // LD_A_addr(wStartDay);
    // LD_B_A;
    uint8_t day = wram->wStartDay;
    // LD_A_addr(wStartHour);
    // LD_C_A;
    uint8_t hour = wram->wStartHour;
    // LD_A_addr(wStartMinute);
    // LD_D_A;
    uint8_t min = wram->wStartMinute;
    // LD_A_addr(wStartSecond);
    // LD_E_A;
    uint8_t sec = wram->wStartSecond;
    // PUSH_BC;
    // PUSH_DE;
    // FARCALL(aMobileStudium);
    //  TODO: Convert Mobile Stadium
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // POP_DE;
    // POP_BC;
    // LD_A_B;
    // LD_addr_A(wStartDay);
    wram->wStartDay = day;
    // LD_A_C;
    // LD_addr_A(wStartHour);
    wram->wStartHour = hour;
    // LD_A_D;
    // LD_addr_A(wStartMinute);
    wram->wStartMinute = min;
    // LD_A_E;
    // LD_addr_A(wStartSecond);
    wram->wStartSecond = sec;
    // RET;
    return false;
}

// MobileMenu_MessagesLoop
void Function4a4c4(void){
entry:
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aFunction4a3a7);
    Function4a3a7();
    // CALL(aFunction4a492);
    Function4a492();
    // CALL(aFunction4a680);
    Function4a680();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames_Conv(20);
    // hlcoord(2, 0, wTilemap);
    // LD_B(0xa);
    // LD_C(0xe);
    // CALL(aFunction48cdc);
    Function48cdc(coord(2, 0, wram->wTilemap), 0xa, 0xe);
    // hlcoord(4, 2, wTilemap);
    // LD_DE(mString_4a5c5);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_4a5c5), coord(4, 2, wram->wTilemap));
    // hlcoord(4, 4, wTilemap);
    // LD_DE(mString_4a5cd);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_4a5cd), coord(4, 4, wram->wTilemap));
    // hlcoord(4, 6, wTilemap);
    // LD_DE(mString_4a5da);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_4a5da), coord(4, 6, wram->wTilemap));
    // hlcoord(4, 8, wTilemap);
    // LD_DE(mString_4a5e6);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_4a5e6), coord(4, 8, wram->wTilemap));
    // hlcoord(4, 10, wTilemap);
    // LD_DE(mString_4a5f2);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_4a5f2), coord(4, 10, wram->wTilemap));
    // hlcoord(0, 12, wTilemap);
    // LD_B(0x4);
    // LD_C(0x12);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 12, wram->wTilemap), 0x4, 0x12);
    // XOR_A_A;
    // LD_HL(mStrings_4a5f6);
    // LD_D_H;
    // LD_E_L;
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Strings_4a5f6[0]), coord(1, 14, wram->wTilemap));
    // LD_A(0x1);
    // LD_HL(mStrings_4a5f6);
    // CALL(aGetNthString);
    // LD_D_H;
    // LD_E_L;
    // hlcoord(1, 16, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Strings_4a5f6[1]), coord(1, 16, wram->wTilemap));
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aStaticMenuJoypad);
    uint8_t joypad = StaticMenuJoypad_Conv();
    // LD_HL(wMenuCursorY);
    // LD_B_hl;
    // PUSH_BC;
    uint8_t b = wram->wMenuCursorY;
    // JR(masm_4a54d);
    // return asm_4a54d(joypad, b); // inlined
    while(1) {
        // BIT_A(0);
        // IF_NZ goto asm_4a557;
        if(bit_test(joypad, A_BUTTON_F)) {
        // asm_4a557:
            // LD_HL(wMenuCursorY);
            // LD_A_hl;
            // CP_A(0x1);
            // JP_Z (mFunction4a6ab);
            // CP_A(0x2);
            // JP_Z (mFunction4a6ab);
            // CP_A(0x3);
            // JP_Z (mFunction4a6ab);
            // CP_A(0x4);
            // JP_Z (mFunction4a6ab);
            if(wram->wMenuCursorY == 0x1
            || wram->wMenuCursorY == 0x2
            || wram->wMenuCursorY == 0x3
            || wram->wMenuCursorY == 0x4) { // Dummied out menu?
                Function4a6ab();
                goto entry;
            }
            // LD_A(0x1);
            // CALL(aMenuClickSound);
            MenuClickSound_Conv(0x1);
            goto asm_4a574;
        }
        // BIT_A(1);
        // IF_NZ goto asm_4a574;
        else if(bit_test(joypad, B_BUTTON_F)) {
        asm_4a574:
            // POP_BC;
            // CALL(aClearBGPalettes);
            ClearBGPalettes_Conv();
            // CALL(aClearTilemap);
            ClearTilemap_Conv2();
            // JP(mFunction49f0a);
            Function49f0a();
            return;
        }
        // goto asm_4a57e;

    // asm_4a57e:
        // LD_HL(wMenuCursorY);
        // LD_A_hl;
        // DEC_A;
        // ADD_A_A;
        // PUSH_AF;
        uint8_t y = (wram->wMenuCursorY - 1) * 2;
        // LD_HL(mStrings_4a5f6);
        // CALL(aGetNthString);
        // LD_D_H;
        // LD_E_L;
        // hlcoord(1, 13, wTilemap);
        // LD_B(0x4);
        // LD_C(0x12);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(1, 13, wram->wTilemap), 0x12, 0x4);
        // hlcoord(1, 14, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(Strings_4a5f6[y]), coord(1, 14, wram->wTilemap));
        // POP_AF;
        // INC_A;
        // LD_HL(mStrings_4a5f6);
        // CALL(aGetNthString);
        // LD_D_H;
        // LD_E_L;
        // hlcoord(1, 16, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(Strings_4a5f6[y+1]), coord(1, 16, wram->wTilemap));
        // JP(mFunction4a5b0);
        // return Function4a5b0(b); // inlined
        // CALL(aFunction4a680);
        Function4a680();
        // POP_BC;
        // LD_HL(wMenuCursorY);
        // LD_hl_B;
        wram->wMenuCursorY = b;
        // LD_B(0xa);
        // LD_C(0x1);
        // hlcoord(3, 1, wTilemap);
        // CALL(aClearBox);
        ClearBox_Conv2(coord(3, 1, wram->wTilemap), 0x1, 0xa);
        // JP(mFunction4a545); // inlined
        // CALL(aScrollingMenuJoypad);
        joypad = ScrollingMenuJoypad_Conv();
        // LD_HL(wMenuCursorY);
        // LD_B_hl;
        // PUSH_BC;
        b = wram->wMenuCursorY;

        // return asm_4a54d(joypad, b);
    }
}

// MobileMenu_MessagesContinue
// void Function4a545(void){
//     // CALL(aScrollingMenuJoypad);
//     uint8_t joypad = ScrollingMenuJoypad_Conv();
//     // LD_HL(wMenuCursorY);
//     // LD_B_hl;
//     // PUSH_BC;
//     uint8_t b = wram->wMenuCursorY;

//     return asm_4a54d(joypad, b);
// }

// void asm_4a54d(uint8_t joypad, uint8_t b){
//     // BIT_A(0);
//     // IF_NZ goto asm_4a557;
//     if(bit_test(joypad, A_BUTTON_F)) {
//     // asm_4a557:
//         // LD_HL(wMenuCursorY);
//         // LD_A_hl;
//         // CP_A(0x1);
//         // JP_Z (mFunction4a6ab);
//         // CP_A(0x2);
//         // JP_Z (mFunction4a6ab);
//         // CP_A(0x3);
//         // JP_Z (mFunction4a6ab);
//         // CP_A(0x4);
//         // JP_Z (mFunction4a6ab);
//         if(wram->wMenuCursorY == 0x1
//         || wram->wMenuCursorY == 0x2
//         || wram->wMenuCursorY == 0x3
//         || wram->wMenuCursorY == 0x4) {
//             return Function4a6ab();
//         }
//         // LD_A(0x1);
//         // CALL(aMenuClickSound);
//         MenuClickSound_Conv(0x1);
//         goto asm_4a574;
//     }
//     // BIT_A(1);
//     // IF_NZ goto asm_4a574;
//     else if(bit_test(joypad, B_BUTTON_F)) {
//     asm_4a574:
//         // POP_BC;
//         // CALL(aClearBGPalettes);
//         ClearBGPalettes_Conv();
//         // CALL(aClearTilemap);
//         ClearTilemap_Conv2();
//         // JP(mFunction49f0a);
//         return Function49f0a();
//     }
//     // goto asm_4a57e;

// // asm_4a57e:
//     // LD_HL(wMenuCursorY);
//     // LD_A_hl;
//     // DEC_A;
//     // ADD_A_A;
//     // PUSH_AF;
//     uint8_t y = (wram->wMenuCursorY - 1) * 2;
//     // LD_HL(mStrings_4a5f6);
//     // CALL(aGetNthString);
//     // LD_D_H;
//     // LD_E_L;
//     // hlcoord(1, 13, wTilemap);
//     // LD_B(0x4);
//     // LD_C(0x12);
//     // CALL(aClearBox);
//     ClearBox_Conv2(coord(1, 13, wram->wTilemap), 0x12, 0x4);
//     // hlcoord(1, 14, wTilemap);
//     // CALL(aPlaceString);
//     PlaceStringSimple(U82C(Strings_4a5f6[y]), coord(1, 14, wram->wTilemap));
//     // POP_AF;
//     // INC_A;
//     // LD_HL(mStrings_4a5f6);
//     // CALL(aGetNthString);
//     // LD_D_H;
//     // LD_E_L;
//     // hlcoord(1, 16, wTilemap);
//     // CALL(aPlaceString);
//     PlaceStringSimple(U82C(Strings_4a5f6[y+1]), coord(1, 16, wram->wTilemap));
//     // JP(mFunction4a5b0);
//     return Function4a5b0(b);
// }

// void Function4a5b0(uint8_t b){
//     // CALL(aFunction4a680);
//     Function4a680();
//     // POP_BC;
//     // LD_HL(wMenuCursorY);
//     // LD_hl_B;
//     wram->wMenuCursorY = b;
//     // LD_B(0xa);
//     // LD_C(0x1);
//     // hlcoord(3, 1, wTilemap);
//     // CALL(aClearBox);
//     ClearBox_Conv2(coord(3, 1, wram->wTilemap), 0x1, 0xa);
//     // JP(mFunction4a545);
// }

const char String_4a5c5[] = "MYSELF"; // "じこしょうかい@";
const char String_4a5cd[] = "BEGIN BATTLE"; //"たいせん\u3000<GA>はじまるとき@";
const char String_4a5da[] = "WIN BATTLE"; //"たいせん\u3000<NI>かったとき@";
const char String_4a5e6[] = "LOSE BATTLE"; //"たいせん\u3000<NI>まけたとき@";
const char String_4a5f2[] = "BACK"; //"もどる@";

const char* Strings_4a5f6[] = {
    "Put on your CARD@", // "めいし\u3000や\u3000ニュース\u3000<NI>のせる@",
    "and the NEWS.@", // "あなた<NO>あいさつです@",
    "Shown when a@", // "モバイル\u3000たいせん<GA>はじまるとき@",
    "battle begins.@", // "あいて<NI>みえる\u3000あいさつです@",
    "Shown when you@", // "モバイル\u3000たいせんで\u3000かったとき@",
    "win a battle.@", // "あいて<NI>みえる\u3000あいさつです@",
    "Shown when you@", // "モバイル\u3000たいせんで\u3000まけたとき@",
    "lose a battle.@", // "あいて<NI>みえる\u3000あいさつです@",
    "Return to the@", // "まえ<NO>がめん\u3000<NI>もどります@",
    "previous screen.@",
};

void Function4a680(void){
    // LD_HL(w2DMenuCursorInitY);
    // LD_A(0x2);
    // LD_hli_A;
    wram->w2DMenuCursorInitY = 0x2;
    // LD_A(0x3);
    // LD_hli_A;
    wram->w2DMenuCursorInitX = 0x3;
    // LD_A(0x5);
    // LD_hli_A;
    wram->w2DMenuNumRows = 0x5;
    // LD_A(0x1);
    // LD_hli_A;
    wram->w2DMenuNumCols = 0x1;
    // LD_hl(0x0);
    // SET_hl(5);
    wram->w2DMenuFlags1 = MENU_UNUSED_3;
    // INC_HL;
    // XOR_A_A;
    // LD_hli_A;
    wram->w2DMenuFlags2 = 0x0;
    // LD_A(0x20);
    // LD_hli_A;
    wram->w2DMenuCursorOffsets = (2 << 4) | 0;
    // LD_A(0x1);
    // ADD_A(0x40);
    // ADD_A(0x80);
    // ADD_A(0x2);
    // LD_hli_A;
    wram->wMenuJoypadFilter = (A_BUTTON | B_BUTTON | D_UP | D_DOWN);
    // LD_A(0x1);
    // LD_hli_A;
    wram->wMenuCursorY = 0x1;
    // LD_hli_A;
    wram->wMenuCursorX = 0x1;
    // XOR_A_A;
    // LD_hli_A;
    wram->wCursorOffCharacter = 0x0;
    // LD_hli_A;
    // LD_hli_A;
    wram->wCursorCurrentTile = 0x0;
    // RET;
}

// MobileMenu_Messages_ModifyMessage?
void Function4a6ab(void){
    // LD_A(0x2);
    // CALL(aMenuClickSound);
    MenuClickSound_Conv(0x2);
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // FARCALL(aFunction11c1ab); //  TODO: Convert EZ Chat stuff
    Function11c1ab();
    // POP_BC;
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // JP(mFunction4a4c4);
    // return Function4a4c4();
    // Just return and have caller return to this function
}

// MobileMenu_FadeMusic
void Function4a6c5(uint16_t de){
    // LD_A(0x5);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0x5;
    // LD_A_E;
    // LD_addr_A(wMusicFadeID);
    // LD_A_D;
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = de;
    // LD_C(22);
    // CALL(aDelayFrames);
    DelayFrames_Conv(22);
    // RET;
}

// MobileMenu_FillBox?
tile_t* Function4a6d8(tile_t* hl, uint8_t b, uint8_t c, uint8_t a){
    do {
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // asm_4a6da:
            // LD_hli_A;
            *(hl2++) = a;
            // DEC_C;
            // IF_NZ goto asm_4a6da;
        } while(--c2 != 0);
        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // JR_NZ (mFunction4a6d8);
    } while(--b != 0);
    // RET;
    return hl;
//  if DEF(_DEBUG)
//  MainMenu_DebugRoom:
//      farcall _DebugRoom
//      ret
//  endc

}
