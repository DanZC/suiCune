#include "../constants.h"
#include "mobile_5e.h"
#include "mobile_41.h"
#include "mobile_45_sprite_engine.h"
#include "../home/text.h"
#include "../home/mobile.h"
#include "../home/joypad.h"
#include "../home/copy.h"
#include "../home/delay.h"
#include "../home/clear_sprites.h"
#include "../home/audio.h"
#include "../home/menu.h"
#include "../home/tilemap.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/color.h"
#include "../engine/gfx/crystal_layouts.h"

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

bool Function17a68f(uint8_t* de, uint8_t c){
    // CALL(aFunction17a6a8);
    Function17a6a8(de, c);
    // CALL(aFunction17a751);
    Function17a751();
    // LD_HL(0xd088);
    // BIT_hl(5);
    // IF_Z goto asm_17a6a6;
    if(bit_test(wram->wd088, 5)) {
        // LD_DE(wStringBuffer1);
        // PUSH_DE;
        // CALL(aFunction17a721);
        Function17a721(wram->wStringBuffer1);
        // POP_DE;
        // XOR_A_A;
        // RET;
        return false;
    }
    else {
    // asm_17a6a6:
        // SCF;
        // RET;
        return true;
    }
}

void Function17a6a8(uint8_t* de, uint8_t c){
    // PUSH_DE;
    // PUSH_BC;
    // LD_HL(wStringBuffer2);
    // LD_BC(0xa);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wStringBuffer2, 0xa, 0);
    // LD_HL(wd1ea);
    // LD_BC(0x10);
    // LD_A(0xff);
    // CALL(aByteFill);
    ByteFill_Conv2(&wram->wd1ea, 0x10, 0xff);
    // POP_BC;
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto asm_17a6c9;
    if(c != 0) {
        // LD_HL(0xd088);
        // SET_hl(4);
        bit_set(wram->wd088, 4);
    }

// asm_17a6c9:
    // POP_DE;
    // CALL(aFunction17a6f5);
    Function17a6f5(de);
    // CALL(aFunction17aba0);
    Function17aba0();
    // FARCALL(aFunction106464);
    Function106464();
    // CALL(aFunction17ac0c);
    Function17ac0c();
    // FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    HDMATransferAttrmapAndTilemapToWRAMBank3_Conv();
    // CALL(aFunction17abcf);
    Function17abcf();
    // FARCALL(aLoadOW_BGPal7);
    LoadOW_BGPal7();
    // FARCALL(aFunction49420);
    Function49420();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

void Function17a6f5(uint8_t* de){
    // LD_HL(wd1ea);
    uint8_t* hl = &wram->wd1ea;
    // LD_C(0x0);
    uint8_t c = 0x0;
    // LD_B(0x8);
    uint8_t b = 0x8;

    do {
    // asm_17a6fc:
        // LD_A_de;
        // CALL(aFunction17a713);
        // IF_C goto asm_17a70e;
        if(Function17a713(&hl, &c, *de))
            break;
        // LD_A_de;
        // SWAP_A;
        // CALL(aFunction17a713);
        // IF_C goto asm_17a70e;
        if(Function17a713(&hl, &c, (*de >> 4)))
            break;
        // INC_DE;
        de++;
        // DEC_B;
        // IF_NZ goto asm_17a6fc;
    } while(--b != 0);

// asm_17a70e:
    // LD_A_C;
    // LD_addr_A(0xd08c);
    wram->wStringBuffer2[6] = c;
    // RET;
}

bool Function17a713(uint8_t** hl, uint8_t* c, uint8_t a){
    // AND_A(0xf);
    // CP_A(0xa);
    // IF_NC goto asm_17a71d;
    if((a & 0xf) < 0xa) {
        // LD_hli_A;
        *((*hl)++) = (a & 0xf);
        // INC_C;
        (*c)++;
        // AND_A_A;
        // RET;
        return false;
    }

// asm_17a71d:
    // LD_hl(0xff);
    **hl = 0xff;
    // SCF;
    // RET;
    return true;
}

void Function17a721(uint8_t* de){
    // PUSH_DE;
    // LD_H_D;
    // LD_L_E;
    // LD_BC(0x8);
    // LD_A(0xff);
    // CALL(aByteFill);
    ByteFill_Conv2(de, 0x8, 0xff);
    // POP_DE;
    // LD_HL(wd1ea);
    uint8_t* hl = &wram->wd1ea;
    // LD_B(0x8);
    uint8_t b = 0x8;

    do {
    // asm_17a732:
        // LD_C(0x0);
        uint8_t c = 0x0;
        // LD_A_hli;
        uint8_t a = *(hl++);
        // CP_A(0xa);
        // IF_NC goto asm_17a748;
        if(a >= 0xa) {
        // asm_17a748:
            // LD_A(0xff);
            // LD_de_A;
            *de = 0xff;
            // RET;
            return;
        }
        // LD_C_A;
        c = a;
        // LD_A_hli;
        a = *(hl++);
        // CP_A(0xa);
        // IF_NC goto asm_17a74c;
        if(a >= 0xa) {
        // asm_17a74c:
            // LD_A(0xf0);
            // OR_A_C;
            // LD_de_A;
            *de = 0xf0 | c;
            // RET;
            return;
        }
        // SWAP_A;
        // OR_A_C;
        // LD_de_A;
        *de = (a << 4) | c;
        // INC_DE;
        de++;
        // DEC_B;
        // IF_NZ goto asm_17a732;
    } while(--b != 0);
    // RET;
}

void Function17a751(void){
    // XOR_A_A;
    // LD_addr_A(0xd087);
    wram->wd087 = 0;

    do {
    // asm_17a755:
        // CALL(aFunction17a781);
        Function17a781();
        // CALL(aFunction17a7ae);
        Function17a7ae();
        // CALL(aFunction17a97b);
        Function17a97b();
        // CALL(aFunction17a770);
        Function17a770();
        // CALL(aFunction17a78f);
        Function17a78f();
        // LD_HL(0xd08f);
        // INC_hl;
        wram->wd08f++;
        // LD_A_addr(0xd087);
        // BIT_A(7);
        // IF_Z goto asm_17a755;
    } while(!bit_test(wram->wd087, 7));
    // RET;
}

void Function17a770(void){
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t oamUpdate = hram->hOAMUpdate;
    // LD_A(0x1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 0x1;
    // CALL(aHideSprites);
    HideSprites_Conv();
    // CALL(aFunction17a9cb);
    Function17a9cb();
    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = oamUpdate;
    // RET;
}

void Function17a781(void){
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // CALL(aJoyTextDelay);
    JoyTextDelay_Conv();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // RET;
}

void Function17a78f(void){
    // LD_HL(0xd088);
    // BIT_hl(7);
    // RES_hl(7);
    // IF_NZ goto asm_17a79f;
    if(bit_test(wram->wd088, 7)) {
    // asm_17a79f:
        bit_reset(wram->wd088, 7);
        // FARCALL(aReloadMapPart);
        ReloadMapPart_Conv();
        // RET;
    }
    else {
        bit_reset(wram->wd088, 7);
        // FARCALL(aHDMATransferTilemapToWRAMBank3);
        HDMATransferTilemapToWRAMBank3_Conv();
        // RET;
    }
}

void Function17a7a6(void){
//  //  unreferenced
    LD_A_addr(0xd087);
    INC_A;
    LD_addr_A(0xd087);
    RET;

}

void Function17a7ae(void){
    // LD_A_addr(0xd087);
    // LD_HL(mJumptable_17a7b6);
    // RST(aJumpTable);
    // RET;
    return Jumptable_17a7b6(wram->wd087);
}

void Jumptable_17a7b6(uint8_t a){
    switch(a) {
        case 0: return Function17a7c2();
        case 1: return Function17a7cd();
        case 2: return Function17a7d8();
        case 3: return Function17a7ff();
        case 4: return Function17a81a();
        case 5: return Function17a7f4();
    }
}

void Function17a7c2(void){
    // LD_A(0x4);
    // CALL(aFunction17aad3);
    Function17aad3(0x4);
    // LD_A(0x1);
    // LD_addr_A(0xd087);
    wram->wd087 = 0x1;
    // RET;
}

void Function17a7cd(void){
    // CALL(aFunction17a83c);
    uint8_t c = Function17a83c();
    // CALL(aFunction17a8ae);
    // RET_C ;
    if(Function17a8ae(c))
        return;
    // CALL(aFunction17a848);
    Function17a848(c);
    // RET;
}

void Function17a7d8(void){
    // CALL(aFunction17a83c);
    // CALL(aFunction17a848);
    Function17a848(Function17a83c());
    // LD_HL(0xd08b);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wd08b)
        return;
    // CALL(aFunction17ac1d);
    Function17ac1d();
    // CALL(aFunction17ac2a);
    Function17ac2a();
    // LD_HL(0xd088);
    // SET_hl(7);
    bit_set(wram->wd088, 7);
    // LD_A(0x1);
    // LD_addr_A(0xd087);
    wram->wd087 = 0x1;
    // RET;
}

void Function17a7f4(void){
    // LD_HL(0xd08b);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wd08b)
        return;
    // LD_HL(0xd087);
    // SET_hl(7);
    bit_set(wram->wd087, 7);
    // RET;
}

void Function17a7ff(void){
    // LD_HL(0xd08b);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wd08b)
        return;
    // CALL(aFunction17ac1d);
    Function17ac1d();
    // CALL(aFunction17ac2a);
    Function17ac2a();
    // LD_HL(0xd088);
    // SET_hl(7);
    // LD_HL(0xd088);
    // SET_hl(5);
    wram->wd088 |= ((1 << 7) | (1 << 5));
    // LD_HL(0xd087);
    // SET_hl(7);
    bit_set(wram->wd087, 7);
    // RET;
}

void Function17a81a(void){
    // CALL(aIsSFXPlaying);
    // RET_NC ;
    if(IsSFXPlaying_Conv())
        return;
    // LDH_A_addr(hJoyPressed);
    // AND_A(0x3);
    // RET_Z ;
    if((hram->hJoyPressed & (A_BUTTON | B_BUTTON)) == 0)
        return;
    // CALL(aExitMenu);
    ExitMenu_Conv2();
    // CALL(aFunction17ac1d);
    Function17ac1d();
    // CALL(aFunction17ac2a);
    Function17ac2a();
    // LD_HL(0xd088);
    // SET_hl(7);
    bit_set(wram->wd088, 7);
    // LD_HL(0xd088);
    // RES_hl(6);
    bit_reset(wram->wd088, 6);
    // LD_A(0x1);
    // LD_addr_A(0xd087);
    wram->wd087 = 0x1;
    // RET;
}

uint8_t Function17a83c(void){
    // LDH_A_addr(hJoyLast);
    // AND_A(0xf0);
    // LD_C_A;
    // LDH_A_addr(hJoyPressed);
    // AND_A(0xb);
    // OR_A_C;
    // LD_C_A;
    // RET;
    return (hram->hJoyLast & 0xf0) | (hram->hJoyPressed & 0xb);
}

bool Function17a848(uint8_t c){
    // LD_A_C;
    // AND_A(0x60);
    // CP_A(0x60);
    // IF_Z goto asm_17a876;
    if((c & (D_UP | D_LEFT)) == (D_UP | D_LEFT)) {
    // asm_17a876:
        // LD_A(0x9);
        // CALL(aFunction17aad0);
        Function17aad0(0x9);
        // SCF;
        // RET;
        return true;
    }
    // LD_A_C;
    // AND_A(0x50);
    // CP_A(0x50);
    // IF_Z goto asm_17a87d;
    if((c & (D_UP | D_RIGHT)) == (D_UP | D_RIGHT)) {
    // asm_17a87d:
        // LD_A(0xa);
        // CALL(aFunction17aad0);
        Function17aad0(0xa);
        // SCF;
        // RET;
        return true;
    }
    // LD_A_C;
    // AND_A(0xa0);
    // CP_A(0xa0);
    // IF_Z goto asm_17a884;
    if((c & (D_DOWN | D_LEFT)) == (D_DOWN | D_LEFT)) {
    // asm_17a884:
        // LD_A(0xb);
        // CALL(aFunction17aad0);
        Function17aad0(0xb);
        // SCF;
        // RET;
        return true;
    }
    // LD_A_C;
    // AND_A(0x90);
    // CP_A(0x90);
    // IF_Z goto asm_17a88b;
    if((c & (D_DOWN | D_RIGHT)) == (D_DOWN | D_RIGHT)) {
    // asm_17a88b:
        // LD_A(0xc);
        // CALL(aFunction17aad0);
        Function17aad0(0xc);
        // SCF;
        // RET;
        return true;
    }
    // BIT_C(6);
    // IF_NZ goto asm_17a892;
    if(bit_test(c, D_UP_F)) {
    // asm_17a892:
        // LD_A(0x5);
        // CALL(aFunction17aad0);
        Function17aad0(0x5);
        // SCF;
        // RET;
        return true;
    }
    // BIT_C(7);
    // IF_NZ goto asm_17a899;
    if(bit_test(c, D_DOWN_F)) {
    // asm_17a899:
        // LD_A(0x6);
        // CALL(aFunction17aad0);
        Function17aad0(0x6);
        // SCF;
        // RET;
        return true;
    }
    // BIT_C(5);
    // IF_NZ goto asm_17a8a0;
    if(bit_test(c, D_LEFT_F)) {
    // asm_17a8a0:
        // LD_A(0x7);
        // CALL(aFunction17aad0);
        Function17aad0(0x7);
        // SCF;
        // RET;
        return true;
    }
    // BIT_C(4);
    // IF_NZ goto asm_17a8a7;
    if(bit_test(c, D_RIGHT_F)) {
    // asm_17a8a7:
        // LD_A(0x8);
        // CALL(aFunction17aad0);
        Function17aad0(0x8);
        // SCF;
        // RET;
        return true;
    }
    // XOR_A_A;
    // RET;
    return false;
}

bool Function17a8ae(uint8_t c){
    // BIT_C(1);
    // IF_NZ goto asm_17a8bc;
    if(bit_test(c, B_BUTTON_F)) {
    // asm_17a8bc:
        // LD_A(0xb);
        // LD_addr_A(0xd08a);
        wram->wd08a = 0xb;
        // CALL(aFunction17aa98);
        Function17aa98();
        // CALL(aFunction17a943);
        // CALL(aFunction17aa88);
        Function17aa88(Function17a943());
        // SCF;
        // RET;
        return true;
    }
    // BIT_C(0);
    // IF_NZ goto asm_17a8cc;
    if(bit_test(c, A_BUTTON_F)) {
    // asm_17a8cc:
        // CALL(aFunction17aad7);
        Function17aad7();
        // CALL(aFunction17aa98);
        Function17aa98();
        // CALL(aFunction17a8de);
        Function17a8de();
        // SCF;
        // RET;
        return true;
    }
    // BIT_C(3);
    // IF_NZ goto asm_17a8d7;
    if(bit_test(c, START_F)) {
    // asm_17a8d7:
        // LD_A(0xc);
        // CALL(aFunction17aad3);
        Function17aad3(0xc);
        // SCF;
        // RET;
        return true;
    }
    // XOR_A_A;
    // RET;
    return false;
}

void Function17a8de(void){
    // LD_A(0x2);
    // CALL(aFunction17aae0);
    const uint8_t* hl = Function17aae0(0x2);
    // LD_A_hl;
    switch(*hl) {
    // CP_A(0xf1);
    // IF_Z goto asm_17a8fd;
    case 0xf1:
    // asm_17a8fd:
        // CALL(aFunction17a943);
        // CALL(aFunction17aa88);
        Function17aa88(Function17a943());
        // RET;
        return;
    // CP_A(0xf0);
    // IF_Z goto asm_17a904;
    case 0xf0:
    // asm_17a904:
        // CALL(aFunction17aad7);
        Function17aad7();
        // CALL(aFunction17aa98);
        Function17aa98();
        // CALL(aFunction17a91e);
        // CALL(aFunction17aa88);
        Function17aa88(Function17a91e());
        // RET;
        return;
    // CP_A(0xf2);
    // IF_Z goto asm_17a911;
    case 0xf2:
    // asm_17a911:
        // CALL(aFunction17aa98);
        Function17aa98();
        // LD_A(0x5);
        // LD_addr_A(0xd087);
        wram->wd087 = 0x5;
        // XOR_A_A;
        // CALL(aFunction17aa88);
        Function17aa88(false);
        // RET;
        return;
    default:
        // LD_E_A;
        // CALL(aFunction17a964);
        Function17a964(*hl);
        // LD_A(0x2);
        // LD_addr_A(0xd087);
        wram->wd087 = 0x2;
        // CALL(aFunction17aa88);
        Function17aa88(false);
        // RET;
        return;
    }
}

bool Function17a91e(void){
    // LD_A_addr(0xd08c);
    // CP_A(0x7);
    // IF_C goto asm_17a92c;
    if(wram->wd08c >= 7) {
        // LD_A(0x3);
        // LD_addr_A(0xd087);
        wram->wd087 = 0x3;
        // XOR_A_A;
        // RET;
        return false;
    }

// asm_17a92c:
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // CALL(aFunction17a99e);
    Function17a99e();
    // LD_HL(0xd088);
    // SET_hl(7);
    bit_set(wram->wd088, 7);
    // LD_HL(0xd088);
    // SET_hl(6);
    bit_set(wram->wd088, 6);
    // LD_A(0x4);
    // LD_addr_A(0xd087);
    wram->wd087 = 0x4;
    // SCF;
    // RET;
    return true;
}

bool Function17a943(void){
    // LD_A_addr(0xd08c);
    // AND_A_A;
    // IF_Z goto asm_17a95d;
    if(wram->wd08c == 0) {
    // asm_17a95d:
        // LD_A(0x5);
        // LD_addr_A(0xd087);
        wram->wd087 = 0x5;
        // XOR_A_A;
        // RET;
        return false;
    }
    // DEC_A;
    // LD_addr_A(0xd08c);
    uint8_t c = --wram->wd08c;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(wd1ea);
    // ADD_HL_BC;
    // LD_hl(0xff);
    (&wram->wd1ea)[c] = 0xff;
    // LD_A(0x2);
    // LD_addr_A(0xd087);
    wram->wd087 = 0x2;
    // AND_A_A;
    // RET;
    return false;
}

bool Function17a964(uint8_t e){
    // LD_A_addr(0xd08c);
    // CP_A(0x10);
    // IF_NC goto asm_17a979;
    if(wram->wd08c >= 0x10) {
    // asm_17a979:
        // SCF;
        // RET;
        return true;
    }
    // LD_C_A;
    uint8_t c = wram->wd08c;
    // LD_B(0);
    // INC_A;
    // LD_addr_A(0xd08c);
    wram->wd08c = c + 1;
    // LD_HL(wd1ea);
    // ADD_HL_BC;
    // LD_hl_E;
    (&wram->wd1ea)[c] = e;
    // AND_A_A;
    // RET;
    return false;
}

void Function17a97b(void){
    // hlcoord(1, 1, wTilemap);
    // LD_BC((2 << 8) | 18);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 1, wram->wTilemap), 18, 2);
    // hlcoord(3, 2, wTilemap);
    tile_t* hl = coord(3, 2, wram->wTilemap);
    // LD_DE(wd1ea);
    uint8_t* de = &wram->wd1ea;
    // LD_A_addr(0xd08c);
    // AND_A_A;
    // RET_Z ;
    if(wram->wd08c == 0)
        return;
    // LD_C_A;
    uint8_t c = wram->wd08c;

    do {
    // asm_17a990:
        // LD_A_de;
        // INC_DE;
        uint8_t a = *(de++);
        // CP_A(0xa);
        // IF_NC goto asm_17a99d;
        if(a >= 0xa)
            break;
        // ADD_A(0xf6);
        // LD_hli_A;
        *(hl++) = 0xf6 + a;
        // DEC_C;
        // IF_NZ goto asm_17a990;
    } while(--c != 0);
    // RET;


// asm_17a99d:
    // RET;
}

void Function17a99e(void){
    // hlcoord(0, 12, wTilemap);
    // LD_B(0x4);
    // LD_C(0x12);
    // CALL(aFunction17ac46);
    Function17ac46(coord(0, 12, wram->wTilemap), 0x4, 0x12);
    // hlcoord(2, 14, wTilemap);
    // LD_DE(mString_17a9b2);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_17a9b2), coord(2, 14, wram->wTilemap));
    // RET;
}

const char String_17a9b2[] = 
            "Invalid phone" //db ['"でんわばんごうが\u3000ただしく"'];
    t_next  "number!";      //next ['"はいって\u3000いません！"']

void Function17a9cb(void){
    // LD_DE(wVirtualOAM);
    struct SpriteOAM* de = wram->wVirtualOAMSprite;
    // LD_HL(0xd088);
    // BIT_hl(6);
    // IF_NZ goto bit_6_set;
    if(bit_test(wram->wd088, 6)) {
    // bit_6_set:
        // CALL(aFunction17a9e3);
        Function17a9e3(de);
        // RET;
        return;
    }
    else {
        // CALL(aFunction17a9e3);
        de = Function17a9e3(de);
        // CALL(aFunction17aa22);
        de = Function17aa22(de);
        // CALL(aFunction17a9f5);
        Function17a9f5(de);
        // RET;
    }
}

struct SpriteOAM* Function17a9e3(struct SpriteOAM* de){
    // LD_A(0x3);
    // LD_addr_A(0xd08e);
    // LD_HL(mUnknown_17aa77);
    // LD_B(0x8);
    // LD_C(0x8);
    // LD_A(0x5);
    // CALL(aFunction17aa4a);
    return Function17aa4a(de, Unknown_17aa77, 0x8, 0x8, 0x5);
    // RET;
}

void Function17a9f5(struct SpriteOAM* de){
    // LD_A_addr(0xd08c);
    // CP_A(0x10);
    // RET_NC ;
    if(wram->wd08c >= 0x10)
        return;
    // LD_A_addr(0xd08f);
    // SWAP_A;
    // AND_A(0x1);
    // ADD_A(0x1);
    // LD_addr_A(0xd08e);
    wram->wd08e = ((wram->wd08f >> 4) & 1) + 1;
    // LD_A_addr(0xd08c);
    uint8_t a = wram->wd08c;
    // CP_A(0x10);
    // IF_C goto okay;
    if(a >= 10) {
        // DEC_A;
        a--;
    }

// okay:
    // LD_C(0x8);
    // CALL(aSimpleMultiply);
    // ADD_A(0x18);
    // LD_B_A;
    uint8_t b = a * 0x8 + 0x18;
    // LD_C(0x11);
    // LD_HL(mUnknown_17aa72);
    // LD_A(0x4);
    // CALL(aFunction17aa4a);
    Function17aa4a(de, Unknown_17aa72, b, 0x11, 0x4);
    // RET;
}

struct SpriteOAM* Function17aa22(struct SpriteOAM* de){
    // LD_A(0x0);
    // LD_addr_A(0xd08e);
    wram->wd08e = 0x0;
    // PUSH_DE;
    // LD_A(0x3);
    // CALL(aFunction17aae0);
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A(0x0);
    // PUSH_AF;
    uint8_t b = (*Function17aae0(0x3) << 3);
    // LD_A(0x4);
    // CALL(aFunction17aae0);
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A_A;
    // ADD_A(0x8);
    // LD_C_A;
    uint8_t c = (*Function17aae0(0x4) << 3) + 0x8;
    // POP_AF;
    // LD_B_A;
    // POP_DE;
    // LD_A(0x0);
    // LD_HL(mUnknown_17aa77);
    // CALL(aFunction17aa4a);
    // RET;
    return Function17aa4a(de, Unknown_17aa77, b, c, 0x0);
}

struct SpriteOAM* Function17aa4a(struct SpriteOAM* de, const uint8_t* hl, uint8_t b, uint8_t c, uint8_t a){
    // LD_addr_A(0xd08d);
    wram->wd08d = a;
    // LD_A_B;
    // ADD_A(0x8);
    // LD_B_A;
    b += 0x8;
    // LD_A_C;
    // ADD_A(0x10);
    // LD_C_A;
    c += 0x10;
    // LD_A_hli;
    a = *(hl++);

    do {
    // loop:
        // PUSH_AF;
        // LD_A_hli;
        // ADD_A_C;
        // LD_de_A;
        de->yCoord = *(hl++) + c;
        // INC_DE;
        // LD_A_hli;
        // ADD_A_B;
        // LD_de_A;
        de->xCoord = *(hl++) + b;
        // INC_DE;
        // LD_A_addr(0xd08d);
        // ADD_A_hl;
        // INC_HL;
        // LD_de_A;
        de->tileID = *(hl++) + wram->wd08d;
        // INC_DE;
        // LD_A_addr(0xd08e);
        // OR_A_hl;
        // INC_HL;
        // LD_de_A;
        de->attributes = *hl | wram->wd08e;
        // INC_DE;
        de++, hl++;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);
    // RET;
    return de;
}

const uint8_t Unknown_17aa72[] = {
    1,
    dbsprite(0, 0, 0, 0, 0, 0), // 0, 0, 0, 0,
};

const uint8_t Unknown_17aa77[] = {
    4,
    dbsprite(0, 0, 0, 0, 0, 0), // 0, 0, 0, 0,
    dbsprite(1, 0, 0, 0, 1, 0), // 0, 8, 1, 0,
    dbsprite(0, 1, 0, 0, 2, 0), // 8, 0, 2, 0,
    dbsprite(1, 1, 0, 0, 3, 0), // 8, 8, 3, 0,
};

// Dialpad_PlaySwitchOrWrongSFX
void Function17aa88(bool carry){
    // JR_C (masm_17aa91);
    if(carry)
        return asm_17aa91();
    // LD_DE(SFX_SWITCH_POKEMON);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_SWITCH_POKEMON);
    // RET;
}

void asm_17aa91(void){
    // LD_DE(SFX_WRONG);
    // CALL(aPlaySFX);
    PlaySFX_Conv(SFX_WRONG);
    // RET;
}

void Function17aa98(void){
    // LD_A(0x5);
    // LD_addr_A(0xd08b);
    wram->wd08b = 0x5;
    // CALL(aFunction17aaa9);
    // CALL(aFunction17aac3);
    Function17aac3(Function17aaa9());
    // LD_HL(0xd088);
    // SET_hl(7);
    bit_set(wram->wd088, 7);
    // RET;
}

uint8_t* Function17aaa9(void){
    // LD_A(0x3);
    // CALL(aFunction17aae3);
    // LD_C_A;
    uint8_t c = *Function17aae3(0x3);
    // LD_B(0);
    // hlcoord(0, 0, wAttrmap);
    // ADD_HL_BC;
    uint8_t* hl = coord(0, 0, wram->wAttrmap);
    // PUSH_HL;
    // LD_A(0x4);
    // CALL(aFunction17aae3);
    uint8_t a = *Function17aae3(0x4);
    // LD_BC(0x14);
    // POP_HL;
    // CALL(aAddNTimes);
    // RET;
    return hl + SCREEN_WIDTH * a + c;
}

uint8_t* Function17aac3(uint8_t* hl){
    // LD_A(0xb);
    // PUSH_HL;
    // LD_hli_A;
    hl[0] = 0xb;
    // LD_hli_A;
    hl[1] = 0xb;
    // POP_HL;
    // LD_DE(SCREEN_WIDTH);
    // ADD_HL_DE;
    // LD_hli_A;
    hl[SCREEN_WIDTH + 0] = 0xb;
    // LD_hli_A;
    hl[SCREEN_WIDTH + 1] = 0xb;
    // RET;
    return hl + SCREEN_WIDTH + 2;
}

void Function17aad0(uint8_t a){
    // CALL(aFunction17aae0);
    a = *Function17aae0(a);

    return Function17aad3(a);
}

void Function17aad3(uint8_t a){
    // LD_addr_A(0xd089);
    wram->wd089 = a;
    // RET;
}

void Function17aad7(void){
    // PUSH_AF;
    // LD_A_addr(0xd089);
    // LD_addr_A(0xd08a);
    wram->wd08a = wram->wd089;
    // POP_AF;
    // RET;
}

const uint8_t* Function17aae0(uint8_t a){
    // CALL(aFunction17aad7);
    Function17aad7();

    return Function17aae3(a);
}

const uint8_t* Function17aae3(uint8_t a){
    // PUSH_AF;
    // LD_A_addr(0xd08a);
    // LD_BC(0xd);
    // LD_HL(mUnknown_17aaf7);
    // CALL(aAddNTimes);
    // POP_AF;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    // RET;
    return Unknown_17aaf7 + (0xd * wram->wd08a + a);
}

const uint8_t Unknown_17aaf7[] = {
    0x0, 0x0, 0x1, 0x6, 0x5, 0x9, 0x3, 0x2, 0x1, 0x2, 0x1, 0x2, 0x4,
    0x0, 0x0, 0x2, 0x9, 0x5, 0xa, 0x4, 0x0, 0x2, 0xa, 0xa, 0x3, 0x5,
    0x0, 0x0, 0x3, 0xc, 0x5, 0xb, 0x5, 0x1, 0x0, 0x1, 0x0, 0x4, 0x0,
    0x0, 0x0, 0x4, 0x6, 0x8, 0x0, 0x6, 0x5, 0x4, 0x5, 0x1, 0x5, 0x7,
    0x0, 0x0, 0x5, 0x9, 0x8, 0x1, 0x7, 0x3, 0x5, 0x0, 0x2, 0x6, 0x8,
    0x0, 0x0, 0x6, 0xc, 0x8, 0x2, 0x8, 0x4, 0x3, 0x1, 0x3, 0x7, 0x3,
    0x0, 0x0, 0x7, 0x6, 0xb, 0x3, 0x9, 0x8, 0x7, 0x8, 0x4, 0x8, 0xa,
    0x0, 0x0, 0x8, 0x9, 0xb, 0x4, 0xa, 0x6, 0x8, 0x3, 0x5, 0x9, 0xb,
    0x0, 0x0, 0x9, 0xc, 0xb, 0x5, 0xb, 0x7, 0x6, 0x4, 0x6, 0xa, 0x6,
    0x0, 0x0, 0xf2, 0x6, 0xe, 0x6, 0x0, 0xc, 0xa, 0xc, 0x7, 0xc, 0x0,
    0x0, 0x0, 0x0, 0x9, 0xe, 0x7, 0x1, 0x9, 0xb, 0x6, 0x8, 0x1, 0x1,
    0x0, 0x0, 0xf1, 0xc, 0xe, 0x8, 0x2, 0xa, 0xc, 0x7, 0xc, 0x2, 0xc,
    0x0, 0x0, 0xf0, 0x10, 0xe, 0xc, 0xc, 0xb, 0x9, 0xb, 0x9, 0xb, 0x9,
};

// Dialpad_LoadGFX
void Function17aba0(void){
    // LDH_A_addr(rVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);

    // LD_HL(vTiles5 + LEN_2BPP_TILE * 0x00);
    // LD_DE(mDialpadGFX);
    // LD_BC((BANK(aDialpadGFX) << 8) | 0x80);  // includes first 4 tiles of DialpadCursorGFX
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles5 + LEN_2BPP_TILE * 0x00, DialpadGFX, 0, 0x7c);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles5 + LEN_2BPP_TILE * 0x7c, DialpadCursorGFX, 0, 4);

    // POP_AF;
    // LDH_addr_A(rVBK);

    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x00);
    // LD_DE(mDialpadCursorGFX);
    // LD_BC((BANK(aDialpadCursorGFX) << 8) | 5);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x00, DialpadCursorGFX, 0, 5);

    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x05);
    // LD_DE(mMobileDialingGFX);
    // LD_BC((BANK(aMobileDialingGFX) << 8) | 4);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x05, MobileDialingGFX, 0, 4);
    // RET;
}

void Function17abcf(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(BANK(wBGPals1));
    // LDH_addr_A(rSVBK);

    // LD_HL(mPalette_17ac55);
    // LD_DE(wBGPals1);
    // LD_BC(6 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wBGPals1, Palette_17ac55, 6 * PALETTE_SIZE);

    // LD_HL(mPalette_17ac95);
    // LD_DE(wOBPals1);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wOBPals1, Palette_17ac95, 8 * PALETTE_SIZE);

    // LD_HL(mPalette_17b4b5);
    // LD_DE(wOBPals1 + PALETTE_SIZE * 1);
    // LD_BC(2 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wOBPals1 + PALETTE_SIZE * 1, Palette_17b4b5, 2 * PALETTE_SIZE);

    // LD_HL(mMapObjectPals + PALETTE_SIZE * 1);
    // LD_DE(wOBPals1 + PALETTE_SIZE * 3);
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(BANK(aMapObjectPals));
    // CALL(aFarCopyBytes);
    CopyBytes_Conv2(wram->wOBPals1 + PALETTE_SIZE * 3, MapObjectPals + PALETTE_SIZE * 1, 1 * PALETTE_SIZE);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

// Dialpad_LayoutScreen
void Function17ac0c(void){
    // CALL(aFunction17ac1d);
    Function17ac1d();
    // CALL(aFunction17ac2a);
    Function17ac2a();
    // hlcoord(0, 0, wTilemap);
    // LD_B(2);
    // LD_C(SCREEN_WIDTH - 2);
    // CALL(aFunction17ac46);
    Function17ac46(coord(0, 0, wram->wTilemap), 2, SCREEN_WIDTH - 2);
    // RET;
}

// Dialpad_LoadTilemap
void Function17ac1d(void){
    // LD_HL(mDialpadTilemap);
    // decoord(0, 4, wTilemap);
    // LD_BC((SCREEN_HEIGHT - 4) * SCREEN_WIDTH);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 4, wram->wTilemap), (SCREEN_HEIGHT - 4) * SCREEN_WIDTH, DialpadTilemap);
    // RET;
}

// Dialpad_LoadAttrmap
void Function17ac2a(void){
    // LD_HL(mDialpadAttrmap);
    // decoord(0, 4, wAttrmap);
    // LD_BC((SCREEN_HEIGHT - 4) * SCREEN_WIDTH);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 4, wram->wAttrmap), (SCREEN_HEIGHT - 4) * SCREEN_WIDTH, DialpadAttrmap);
    // hlcoord(0, 4, wAttrmap);
    uint8_t* hl = coord(0, 4, wram->wAttrmap);
    // LD_BC((SCREEN_HEIGHT - 4) * SCREEN_WIDTH);
    for(uint32_t i = 0; i < (SCREEN_HEIGHT - 4) * SCREEN_WIDTH; ++i) {
    // loop:
        // LD_A_hl;
        // OR_A(0x8);
        // LD_hli_A;
        hl[i] |= 0x8;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    }
    // RET;
}

// Dialpad_DrawTopTextbox
void Function17ac46(tile_t* hl, uint8_t b, uint8_t c){
    // LD_A_addr(0xd088);
    // BIT_A(4);
    // IF_NZ goto bit_4_set;
    if(bit_test(wram->wd088, 4)) {
    // bit_4_set:
        // CALL(aFunction3eea);
        Function3eea(hl, b, c);
        // RET;
    }
    else {
        // CALL(aTextbox);
        Textbox_Conv2(hl, b, c);
        // RET;
    }
}

const uint16_t Palette_17ac55[] = {
    rgb(0, 0, 0),
    rgb(9, 10, 25),
    rgb(16, 19, 31),
    rgb(31, 31, 31),

    rgb(5, 11, 9),
    rgb(7, 14, 12),
    rgb(17, 24, 22),
    rgb(28, 31, 31),

    rgb(0, 0, 0),
    rgb(3, 0, 10),
    rgb(3, 3, 16),
    rgb(6, 8, 25),

    rgb(5, 11, 9),
    rgb(28, 31, 31),
    rgb(7, 14, 12),
    rgb(17, 24, 22),

    rgb(0, 0, 0),
    rgb(5, 2, 16),
    rgb(8, 8, 26),
    rgb(13, 9, 17),

    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),

    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),

    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
    rgb(0, 0, 0),
};

const uint16_t Palette_17ac95[] = {
    rgb(31, 31, 31),
    rgb(4, 3, 3),
    rgb(31, 13, 0),
    rgb(31, 31, 31),

    rgb(31, 31, 31),
    rgb(0, 0, 0),
    rgb(31, 31, 31),
    rgb(31, 31, 31),

    rgb(31, 0, 0),
    rgb(16, 3, 0),
    rgb(28, 19, 11),
    rgb(31, 31, 31),

    rgb(31, 16, 0),
    rgb(9, 6, 4),
    rgb(31, 16, 0),
    rgb(31, 24, 0),

    rgb(31, 18, 6),
    rgb(0, 3, 0),
    rgb(0, 9, 0),
    rgb(0, 12, 0),

    rgb(0, 16, 0),
    rgb(0, 22, 0),
    rgb(0, 25, 0),
    rgb(0, 27, 0),

    rgb(0, 31, 0),
    rgb(3, 31, 0),
    rgb(8, 31, 0),
    rgb(14, 31, 0),

    rgb(16, 31, 0),
    rgb(22, 31, 0),
    rgb(27, 31, 0),
    rgb(31, 31, 0),
};

const char DialpadTilemap[] = "gfx/mobile/dialpad.tilemap";
const char DialpadAttrmap[] = "gfx/mobile/dialpad.attrmap";
const char DialpadGFX[] = "gfx/mobile/dialpad.png";
const char DialpadCursorGFX[] = "gfx/mobile/dialpad_cursor.png";

const uint16_t Palette_17b4b5[] = {
    rgb(2, 6, 10),
    rgb(24, 30, 29),
};

const char MobileCardListGFX[] = "gfx/mobile/card_list.png";
