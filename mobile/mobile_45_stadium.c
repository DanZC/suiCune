#include "../constants.h"
#include "mobile_45_stadium.h"
#include "mobile_5c.h"
#include "../home/clear_sprites.h"
#include "../home/copy.h"
#include "../home/joypad.h"
#include "../home/sram.h"
#include "../home/text.h"
#include "../home/tilemap.h"
#include "../home/menu.h"
#include "../home/sprite_anims.h"
#include "../engine/events/odd_egg.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/sprites.h"
#include "../data/text/common.h"

void GiveOddEgg(void){
    // FARCALL(av_GiveOddEgg);
    // RET;
    return v_GiveOddEgg();
}

// MobilePassword
//  TODO: Add password censoring mechanism.
void Function11765d(void){
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // CALL(aFunction11766b);
    Function11766b();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // RET;
}

void Function11766b(void){
    // CALL(aFunction117699);
    Function117699();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // CALL(aFunction1176ee);
    Function1176ee();
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_b1d3));
    // LD_HL(0xb1f3);
    // LD_DE(wcd49);
    // LD_BC(0x8);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wcd49, GBToRAMAddr(s5_b1d3 + 0x20), 0x8);
    // LD_DE(0xc708);
    // LD_BC(0x11);
    // CALL(aCopyBytes);
    CopyBytes(wram->wMobilePasswordBuffer, GBToRAMAddr(s5_b1d3 + 0x28), MOBILE_LOGIN_PASSWORD_LENGTH);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void Function117699(void){
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_b1d3));
    // LD_HL(wcd49);
    // LD_DE(0xb1f3);
    // LD_BC(0x8);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_b1d3 + 0x20), &wram->wcd49, 0x8);
    // LD_HL(0xc708);
    // LD_BC(0x11);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_b1d3 + 0x28), wram->wMobilePasswordBuffer, MOBILE_LOGIN_PASSWORD_LENGTH);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // XOR_A_A;
    // LD_addr_A(wcd49);
    wram->wcd49 = 0;
    // LD_addr_A(wcd4a);
    wram->wcd4a = 0;
    // LD_addr_A(wcd4b);
    wram->wcd4b = 0;
    // LD_addr_A(wcd4c);
    wram->wcd4c = 0;
    // LD_addr_A(wcd4d);
    wram->wcd4d = 0;
    // LD_addr_A(wcd4e);
    wram->wcd4e = 0;
    // LD_addr_A(wcd4f);
    wram->wcd4f = 0;
    // LD_HL(0xc708);
    // LD_BC(0x11);
    // CALL(aByteFill);
    ByteFill(wram->wMobilePasswordBuffer, MOBILE_LOGIN_PASSWORD_LENGTH, 0x0);
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // FARCALL(aFunction171c87);
    Function171c87();
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // RET;
}

// MobilePassword_MenuLoop
void Function1176ee(void){
    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LD_A_addr(wcd49);
        // BIT_A(7);
        // IF_NZ goto quit;
        if(bit_test(wram->wcd49, 7))
            break;
        // CALL(aFunction117719);
        Jumptable_117728();
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations_Conv();
        // FARCALL(aReloadMapPart);
        ReloadMapPart_Conv();
        // goto loop;
    }

// quit:
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // CALL(aClearSprites);
    ClearSprites();
    // RET;
}

// void Function117719(void){
    //jumptable ['Jumptable_117728', 'wcd49']
// }

// MobilePassword_Jumptable
void Jumptable_117728(void){
    switch(wram->wcd49) {
        case 0: return Function117738();
        case 1: return Function117764();
        case 2: return Function1178aa();
        case 3: return Function1178e8();
        case 4: return Function117942();
        case 5: return Function117976();
        case 6: return Function117984();
        case 7: return Function1179a7();
    }
}

// MobilePassword_InitSprites
void Function117738(void){
    // FARCALL(aFunction171ccd);
    Function171ccd();
    // depixel2(6, 3);
    // LD_A(0x1d);
    // CALL(aInitSpriteAnimStruct);
    struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_EZCHAT_CURSOR, pixel2(6, 3));
    // LD_HL(0xc);
    // ADD_HL_BC;
    // LD_A(0x6);
    // LD_hl_A;
    bc->var1 = 0x6;
    // depixel2(9, 4);
    // LD_A(0x1d);
    // CALL(aInitSpriteAnimStruct);
    bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_EZCHAT_CURSOR, pixel2(9, 4));
    // LD_HL(0xc);
    // ADD_HL_BC;
    // LD_A(0x7);
    // LD_hl_A;
    bc->var1 = 0x7;
    // LD_A(0x3);
    // LD_addr_A(wcd23);
    wram->wcd23 = 0x3;
    // JP(mMobilePassword_IncrementJumptable);
    return MobilePassword_IncrementJumptable();
}

// MobilePassword_LetterSelect
void Function117764(void){
    // LD_A_addr(wcd4a);
    // CP_A(0x10);
    // IF_NZ goto asm_11776f;
    // LD_A(0x1);
    // goto asm_117770;

// asm_11776f:
    // XOR_A_A;

// asm_117770:
    // LD_addr_A(wcd24);
    wram->wcd24 = (wram->wcd4a == 0x10)? 0x1: 0x0;
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(SELECT);
    // JR_NZ (mFunction117764_select);
    if(hram->hJoyPressed & SELECT) {
        return Function117764_select();
    }
    // LD_A_hl;
    // AND_A(START);
    // JR_NZ (mFunction117764_start);
    else if(hram->hJoyPressed & START) {
        return Function117764_start();
    }
    // LD_A_hl;
    // AND_A(A_BUTTON);
    // JP_NZ (mFunction117764_a_button);
    else if(hram->hJoyPressed & A_BUTTON) {
        return Function117764_a_button();
    }
    // LD_A_hl;
    // AND_A(B_BUTTON);
    // JR_NZ (mFunction117764_b_button);
    else if(hram->hJoyPressed & B_BUTTON) {
        return Function117764_b_button();
    }
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // JR_NZ (mFunction117764_d_up);
    else if(hram->hJoyLast & D_UP) {
        return Function117764_d_up();
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // JR_NZ (mFunction117764_d_down);
    else if(hram->hJoyLast & D_DOWN) {
        return Function117764_d_down();
    }
    // LD_A_hl;
    // AND_A(D_LEFT);
    // JP_NZ (mFunction117764_d_left);
    else if(hram->hJoyLast & D_LEFT) {
        return Function117764_d_left();
    }
    // LD_A_hl;
    // AND_A(D_RIGHT);
    // JP_NZ (mFunction117764_d_right);
    else if(hram->hJoyLast & D_RIGHT) {
        return Function117764_d_right();
    }
    // RET;
}

void Function117764_select(void){
    // FARCALL(aFunction171cf0);
    Function171cf0();
    // RET;
}

void Function117764_start(void){
    // LD_A(0x2);
    // LD_addr_A(wcd4c);
    wram->wcd4c = 0x2;
    // LD_A(0x4);
    // LD_addr_A(wcd4d);
    wram->wcd4d = 0x4;
    // RET;
}

void Function1177b7(void){
    // LD_A(0x3);
    // LD_addr_A(wcd24);
    wram->wcd24 = 0x3;
    // LD_A_addr(wcd4a);
    // AND_A_A;
    // IF_Z goto asm_1177c5;
    if(wram->wcd4a != 0) {
        // JP(mMobilePassword_IncrementJumptable);
        return MobilePassword_IncrementJumptable();
    }

// asm_1177c5:
    // LD_A(0x6);
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x6;
    // RET;
}

void Function1177cb(void){
    // LD_A(0x80);
    // LD_addr_A(wcd49);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wcd49 = 0x80;
    // JP(mMobilePassword_IncrementJumptable);
    return MobilePassword_IncrementJumptable();
}

void Function117764_b_button(void){
    // CALL(aPlayClickSFX);
    PlayClickSFX_Conv();
    // LD_A_addr(wcd4a);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd4a == 0)
        return;
    // DEC_A;
    // LD_addr_A(wcd4a);
    uint8_t e = --wram->wcd4a;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(0xc708);
    // ADD_HL_DE;
    // XOR_A_A;
    // LD_hl_A;
    wram->wMobilePasswordBuffer[e] = 0;
    // hlcoord(2, 4, wTilemap);
    // ADD_HL_DE;
    // LD_hl_A;
    coord(2, 4, wram->wTilemap)[e] = 0;
    // RET;
}

void Function117764_d_up(void){
    // LD_A_addr(wcd4d);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd4d == 0)
        return;
    // DEC_A;
    // LD_addr_A(wcd4d);
    // CP_A(0x3);
    // RET_NZ ;
    if(--wram->wcd4d != 0x3)
        return;
    // LD_A_addr(wcd4c);
    // LD_E_A;
    // SLA_A;
    // SLA_A;
    // ADD_A_E;
    uint8_t a = wram->wcd4c + (wram->wcd4c << 2); // a = wcd4c * 5?
    return Function117764_d_vertical_load(a);
}

void Function117764_d_vertical_load(uint8_t a){
    // LD_addr_A(wcd4c);
    wram->wcd4c = a;
    // RET;
}

void Function117764_d_down(void){
    // LD_A_addr(wcd4d);
    // CP_A(0x4);
    // RET_Z ;
    if(wram->wcd4d == 0x4)
        return;
    // INC_A;
    // LD_addr_A(wcd4d);
    // CP_A(0x4);
    // RET_NZ ;
    if(++wram->wcd4d != 0x4)
        return;
    // LD_A_addr(wcd4c);
    // CP_A(0xa);
    // IF_NC goto asm_117825;
    if(wram->wcd4c >= 0xa) {
    // asm_117825:
        // LD_A(0x2);
        // JR(mFunction117764_d_vertical_load);
        return Function117764_d_vertical_load(0x2);
    }
    // CP_A(0x5);
    // IF_NC goto asm_117829;
    else if(wram->wcd4c >= 0x5) {
    // asm_117829:
        // LD_A(0x1);
        // JR(mFunction117764_d_vertical_load);
        return Function117764_d_vertical_load(0x1);
    }
    else {
        // XOR_A_A;
        // JR(mFunction117764_d_vertical_load);
        return Function117764_d_vertical_load(0x0);
    }
}

void Function117764_d_left(void){
    // LD_A_addr(wcd4c);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd4c == 0)
        return;
    // DEC_A;
    // LD_addr_A(wcd4c);
    wram->wcd4c--;
    // RET;
}

void Function117764_d_right(void){
    // LD_E(0xd);
    // LD_A_addr(wcd4d);
    // CP_A(0x4);
    // IF_NZ goto wrap;
    // LD_E(0x2);
    uint8_t e = (wram->wcd4d == 0x4)? 0x2: 0xd;

// wrap:
    // LD_A_addr(wcd4c);
    // CP_A_E;
    // RET_Z ;
    if(wram->wcd4c == e)
        return;
    // INC_A;
    // LD_addr_A(wcd4c);
    wram->wcd4c++;
    // RET;
}

void Function117764_a_button(void){
    // CALL(aPlayClickSFX);
    PlayClickSFX_Conv();
    // LD_A_addr(wcd4d);
    // CP_A(0x4);
    // IF_NZ goto not_4;
    if(wram->wcd4d == 0x4) {
        // LD_A_addr(wcd4c);
        // CP_A(0x2);
        // JP_Z (mFunction1177b7);
        if(wram->wcd4c == 0x2)
            return Function1177b7();
        // CP_A(0x1);
        // JP_Z (mFunction1177cb);
        else if(wram->wcd4c == 0x1)
            return Function1177cb();
        // JP(mFunction117764_select);
        return Function117764_select();
    }

// not_4:
    // LD_A_addr(wcd4a);
    // LD_E_A;
    uint8_t e = wram->wcd4a;
    // CP_A(0x10);
    // JP_Z (mFunction117764_start);
    if(wram->wcd4a == 0x10)
        return Function117764_start();
    // INC_A;
    // LD_addr_A(wcd4a);
    ++wram->wcd4a;
    // LD_D(0x0);
    // LD_A_addr(wcd4b);
    // AND_A_A;
    // IF_NZ goto ascii_symbols;
    const char* hl;
    if(wram->wcd4b == 0) {
        // LD_HL(mUnknown_117a0f);
        hl = Unknown_117a0f;
        // goto got_ascii;
    }
    else {
    // ascii_symbols:
        // LD_HL(mUnknown_117a47);
        hl = Unknown_117a47;
    }

// got_ascii:
    // PUSH_DE;
    // LD_A_addr(wcd4c);
    // LD_B_A;
    // LD_A_addr(wcd4d);
    // LD_C(0xe);
    // CALL(aSimpleMultiply);
    // ADD_A_B;
    // LD_C_A;
    uint8_t c = (wram->wcd4d * 0xe) + wram->wcd4c;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_HL(0xc708);
    // ADD_HL_DE;
    // LD_hl_A;
    wram->wMobilePasswordBuffer[e] = hl[c];
    // POP_DE;
    // hlcoord(2, 4, wTilemap);
    // ADD_HL_DE;
    // SUB_A(0x20);
    // LD_hl_A;
    coord(2, 4, wram->wTilemap)[e] = hl[c] - 0x20;
    // LD_A_E;
    // CP_A(0xf);
    // RET_NZ ;
    if(e != 0xf)
        return;
    // JP(mFunction117764_start);
    return Function117764_start();
}

// MobilePassword_SetupSavePassword
void Function1178aa(void){
    // LD_HL(mMenuHeader_1179b5);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_1179b5);
    // CALL(aMenuBox);
    MenuBox_Conv();
    // CALL(aMenuBoxCoord2Tile);
    MenuBoxCoord2Tile_Conv();
    // LD_HL(mMenuHeader_1179bd);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_1179bd);
    // CALL(aMenuBox);
    MenuBox_Conv();
    // CALL(aMenuBoxCoord2Tile);
    MenuBoxCoord2Tile_Conv();
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // hlcoord(16, 8, wTilemap);
    // LD_DE(mYessNoString_1179c5);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(YessNoString_1179c5), coord(16, 8, wram->wTilemap));
    // hlcoord(15, 10, wTilemap);
    // LD_A(0xed);
    // LD_hl_A;
    *coord(15, 10, wram->wTilemap) = 0xed;
    // hlcoord(1, 14, wTilemap);
    // LD_DE(mAskSavePasswordString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(AskSavePasswordString), coord(1, 14, wram->wTilemap));
    // LD_A(0x1);
    // LD_addr_A(wcd4e);
    wram->wcd4e = 0x1;
    // JP(mMobilePassword_IncrementJumptable);
    return MobilePassword_IncrementJumptable();
}

// MobilePassword_SavePassword
void Function1178e8(void){
    // LDH_A_addr(hJoyPressed);
    // CP_A(B_BUTTON);
    // IF_Z goto b_button;
    if(hram->hJoyPressed == B_BUTTON) {
    b_button:
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // JP(mMobilePassword_IncrementJumptable);
        return MobilePassword_IncrementJumptable();
    }
    // CP_A(A_BUTTON);
    // IF_Z goto a_button;
    else if(hram->hJoyPressed == A_BUTTON) {
    // a_button:
        // CALL(aPlayClickSFX);
        PlayClickSFX_Conv();
        // LD_A_addr(wcd4e);
        // AND_A_A;
        // IF_NZ goto b_button;
        if(wram->wcd4e != 0)
            goto b_button;
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // LD_A(0x1);
        // LD_addr_A(wcd4f);
        wram->wcd4f = 0x1;
        // JP(mMobilePassword_IncrementJumptable);    
        return MobilePassword_IncrementJumptable();
    }
    // CP_A(D_DOWN);
    // IF_Z goto d_down;
    else if(hram->hJoyPressed == D_DOWN) {
    // d_down:
        // LD_A_addr(wcd4e);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wcd4e != 0)
            return;
        // INC_A;
        // LD_addr_A(wcd4e);
        wram->wcd4e++;
        // hlcoord(15, 8, wTilemap);
        // LD_A(0x7f);
        // LD_hl_A;
        *coord(15, 8, wram->wTilemap) = 0x7f;
        // hlcoord(15, 10, wTilemap);
        // LD_A(0xed);
        // LD_hl_A;
        *coord(15, 10, wram->wTilemap) = 0xed;
        // RET;
        return;
    }
    // CP_A(D_UP);
    // RET_NZ ;
    else if(hram->hJoyPressed == D_UP) {
        // LD_A_addr(wcd4e);
        // AND_A_A;
        // RET_Z ;
        if(wram->wcd4e == 0)
            return;
        // DEC_A;
        // LD_addr_A(wcd4e);
        wram->wcd4e--;
        // hlcoord(15, 8, wTilemap);
        // LD_A(0xed);
        // LD_hl_A;
        *coord(15, 8, wram->wTilemap) = 0xed;
        // hlcoord(15, 10, wTilemap);
        // LD_A(0x7f);
        // LD_hl_A;
        *coord(15, 10, wram->wTilemap) = 0x7f;
        // RET;
        return;
    }
}

// MobilePassword_SavedPasswordConfirmation
void Function117942(void){
    // CALL(aSpeechTextbox);
    SpeechTextbox_Conv2();
    // hlcoord(1, 14, wTilemap);
    // LD_DE(mSavedPasswordString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(SavedPasswordString), coord(1, 14, wram->wTilemap));
    // LD_A(0x1e);
    // LD_addr_A(wcd4e);
    wram->wcd4e = 0x1e;
    // LD_A(BANK(sMobileLoginPassword));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileLoginPassword));
    // LD_A_addr(wcd4f);
    // LD_addr_A(sMobileLoginPassword);
    gb_write(sMobileLoginPassword, wram->wcd4f);
    // LD_HL(0xc708);
    // LD_DE(sMobileLoginPassword + 1);
    // LD_BC(MOBILE_LOGIN_PASSWORD_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(sMobileLoginPassword + 1), wram->wMobilePasswordBuffer, MOBILE_LOGIN_PASSWORD_LENGTH);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A_addr(wcd4f);
    // AND_A_A;
    // JR_Z (masm_11797e);
    if(wram->wcd4f == 0)
        return asm_11797e();
    // CALL(aMobilePassword_IncrementJumptable);
    MobilePassword_IncrementJumptable();

    return Function117976();
}

void Function117976(void){
    // LD_HL(wcd4e);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wcd4e != 0)
        return;
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    return asm_11797e();
}

void asm_11797e(void){
    // LD_A(0x80);
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x80;
    // RET;
}

// MobilePassword_NotAPassword
void Function117984(void){
    // LD_HL(mMenuHeader_1179b5);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader_Conv2(&MenuHeader_1179b5);
    // CALL(aMenuBox);
    MenuBox_Conv();
    // CALL(aMenuBoxCoord2Tile);
    MenuBoxCoord2Tile_Conv();
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // hlcoord(1, 14, wTilemap);
    // LD_DE(mNotAPokemonPasswordString);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(NotAPokemonPasswordString), coord(1, 14, wram->wTilemap));
    // LD_A(0x1e);
    // LD_addr_A(wcd4e);
    wram->wcd4e = 0x1e;
    // CALL(aMobilePassword_IncrementJumptable);
    MobilePassword_IncrementJumptable();

    return Function1179a7();
}

void Function1179a7(void){
    // LD_HL(wcd4e);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wcd4e != 0)
        return;
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // LD_A(0x1);
    // LD_addr_A(wcd49);
    wram->wcd49 = 0x1;
    // RET;
}

const struct MenuHeader MenuHeader_1179b5 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 12, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = NULL,
    .defaultOption = 0,  // default option
};

const struct MenuHeader MenuHeader_1179bd = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(14, 7, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    .data = NULL,
    .defaultOption = 0,  // default option
};

const char YessNoString_1179c5[] =
            "YES" //db ['"はい"'];
    t_next  "NO"; //next ['"いいえ@"']

const char AskSavePasswordString[] = 
            "Save this" //db ['"こ<NO>パスワード¯ほぞんして"'];
    t_line  "PASSWORD?@";//line ['"おきますか？@"']

const char NotAPokemonPasswordString[] = 
            "Invalid PASSWORD!@"; //db ['"パスワード<PKMN>にゅうりょく"'];
    //line ['"されていません！@"']

const char SavedPasswordString[] =
            "Saved the LOG-IN" //db ['"ログインパスワード¯ほぞん"'];
    t_line  "PASSWORD.@"; //line ['"しました@"']

void MobilePassword_IncrementJumptable(void){
    // LD_HL(wcd49);
    // INC_hl;
    wram->wcd49++;
    // RET;
}

// pushc
// setcharmap ascii

const char Unknown_117a0f[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ  "
    "abcdefghijklmnopqrstuvwxyz  ";

const char Unknown_117a47[] =
    "0123456789    "
    "!\"#$%&\'()*+   "
    ",-./:;<=>?@   "
    "[\\]^_`{|}~    ";
// popc

//  everything from here to the end of the bank is related to the
//  Mobile Stadium option from the continue/newgame menu.
//  Needs better function names

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
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // FARCALL(aFunction172e78);
    Function172e78();
    // FARCALL(aFunction172eb9);
    Function172eb9();
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // RET;
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
    // LD_HL(mMobileStadiumEntryText);
    // CALL(aPrintText);
    PrintText_Conv2(MobileStadiumEntryText);
    // JP(mMobileStudium_JumptableIncrement);
    return MobileStudium_JumptableIncrement();
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

const struct MenuHeader MenuHeader_117cbc = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 12, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
    .data = NULL,
    .defaultOption = 0,  // default option
};

const struct MenuHeader MenuHeader_117cc4 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(14, 7, SCREEN_WIDTH - 1, TEXTBOX_Y - 1),
    .data = NULL,
    .defaultOption = 0,  // default item
};

void YesNo117ccc(void){
    //db ['"はい"'];
    //next ['"いいえ@"']
}

const txt_cmd_s MobileStadiumEntryText[] = {
    text_far(v_MobileStadiumEntryText)
    text_end
};

const txt_cmd_s MobileStadiumSuccessText[] = {
    text_far(v_MobileStadiumSuccessText)
    text_end
};

void MobileStudium_JumptableIncrement(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;
}
