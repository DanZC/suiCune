#include "../constants.h"
#include "mobile_45_sprite_engine.h"
#include "../home/copy.h"

void Function115d99(void){
    // LD_DE(mMobileDialingGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0x60);
    // LD_BC((BANK(aMobileDialingGFX) << 8) | 20);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x60, MobileDialingGFX, 0, 20);
    // XOR_A_A;
    // LD_addr_A(wc305);
    wram->wc305 = 0;
    // LD_addr_A(wc306);
    wram->wc306 = 0;
    // LD_addr_A(wc309);
    wram->wc309 = 0;
    // LD_addr_A(wc30a);
    wram->wc30a = 0;
    // LD_addr_A(wc30b);
    wram->wc30b = 0;
    // LD_addr_A(wc30c);
    wram->wc30c = 0;
    // LD_A(0x10);
    // LD_addr_A(wc307);
    wram->wc307 = 0x10;
    // LD_A(0x18);
    // LD_addr_A(wc308);
    wram->wc308 = 0x18;
    // RET;

}

void Function115dc3(void){
    XOR_A_A;
    LD_addr_A(wc305);
    LD_A(0xa0);
    LD_HL(wVirtualOAMSprite31);
    LD_BC(8 * SPRITEOAMSTRUCT_LENGTH);
    CALL(aByteFill);
    RET;

}

void Function115dd3(void){
    // LD_A_addr(wc305);
    // AND_A_A;
    // RET_Z ;
    if(wram->wc305 == 0)
        return;
    // LD_A(0xa0);
    // LD_HL(wVirtualOAMSprite31);
    // LD_BC(8 * SPRITEOAMSTRUCT_LENGTH);
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wVirtualOAMSprite, 8 * SPRITEOAMSTRUCT_LENGTH, 0xa0);
    // CALL(aFunction115e22);
    Function115e22();
    // LD_A_addr(wc309);
    // SLA_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mUnknown_115e86);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hl;
    // LD_D_A;
    // PUSH_DE;
    // POP_HL;
    const uint8_t* hl = Unknown_115e86[wram->wc309];
    // LD_DE(wVirtualOAMSprite31);
    struct SpriteOAM* de = wram->wVirtualOAMSprite + 31;
    // LD_A_addr(wc307);
    // LD_C_A;
    uint8_t c = wram->wc307;
    // LD_A_addr(wc308);
    // LD_B_A;
    uint8_t b = wram->wc308;
    // LD_A_hli;
    uint8_t a = *(hl++);

    do {
    // asm_115e04:
        // PUSH_AF;
        // LD_A_hli;
        // ADD_A_B;
        // LD_de_A;  // y
        de->yCoord = b + *(hl++);
        // INC_DE;
        // LD_A_hli;
        // ADD_A_C;
        // LD_de_A;  // x
        de->xCoord = c + *(hl++);
        // INC_DE;
        // LD_A_hli;
        // LD_de_A;  // tile id
        de->tileID = *(hl++);
        // INC_DE;
        // LD_A_hli;
        // LD_de_A;  // attributes
        de->attributes = *(hl++);
        // INC_DE;
        de++;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_115e04;
    } while(--a != 0);
    // RET;

}

void Function115e18(void){
    LD_A_C;
    LD_addr_A(wc30a);
    XOR_A_A;
    LD_addr_A(wc30b);
    JR(mFunction115e2b);

}

void Function115e22(void){
    // LD_HL(wc30c);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wc30c != 0)
        return;
    // LD_HL(wc30b);
    // INC_hl;
    wram->wc30b++;

    return Function115e2b();
}

void Function115e2b(void){
    while(1) {
        // LD_A_addr(wc30a);
        // SLA_A;
        // LD_C_A;
        // LD_B(0);
        uint8_t c = wram->wc30a;
        // LD_HL(mUnknown_115e59);
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        const uint8_t* de = Unknown_115e59[c];
        // PUSH_DE;
        // POP_HL;
        // LD_A_addr(wc30b);
        // SLA_A;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        const uint8_t* hl = de + (wram->wc30b << 1);
        // LD_A_hli;
        uint8_t a = *(hl++);
        // CP_A(0xff);
        // IF_NZ goto not_end;
        if(a == 0xff) {
            // XOR_A_A;
            // LD_addr_A(wc30b);
            wram->wc30b = 0;
            // JR(mFunction115e2b);
            continue;
        }

    // not_end:
        // LD_addr_A(wc309);
        wram->wc309 = a;
        // LD_A_hl;
        // LD_addr_A(wc30c);
        wram->wc30c = *hl;
        // RET;
        return;
    }
}

const uint8_t* Unknown_115e59[] = {
    Unknown_115e61,
    Unknown_115e6c,
    Unknown_115e76,
    Unknown_115e79,
};

//  OAM idx (see Unknown_115e86), flip flags/duration
const uint8_t Unknown_115e61[] = {
    0x04, 0x08,
    0x05, 0x08,
    0x06, 0x08,
    0x07, 0x08,
    0x08, 0x08,
    (uint8_t)-1,
};

const uint8_t Unknown_115e6c[] = {
    0x01, 0x08,
    0x02, 0x08,
    0x03, 0x08,
    0x09, 0x08,
    0x0a, 0x08,
    // Unknown_115e76
    0x00, 0x08,
    (uint8_t)-1,
};

const uint8_t Unknown_115e76[] = {
    0x00, 0x08,
    (uint8_t)-1,
};

const uint8_t Unknown_115e79[] = {
    0x0b, 0x08,
    0x0c, 0x08,
    0x0d, 0x08,
    0x0e, 0x08,
    0x0f, 0x08,
    0x00, 0x08,
    (uint8_t)-1,
};

const uint8_t* Unknown_115e86[] = {
    Unknown_115ea6,
    Unknown_115eb7,
    Unknown_115ecc,
    Unknown_115ee1,
    Unknown_115ef6,
    Unknown_115f13,
    Unknown_115f30,
    Unknown_115f4d,
    Unknown_115f6a,
    Unknown_115f87,
    Unknown_115f9c,
    Unknown_115fb1,
    Unknown_115fc6,
    Unknown_115fdb,
    Unknown_115ff0,
    Unknown_116005,
};

const uint8_t Unknown_115ea6[] = {
    4,
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const uint8_t Unknown_115eb7[] = {
    5,
    dbsprite(1, 0, 0, 0, 0x64, 0x00),
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const uint8_t Unknown_115ecc[] = {
    5,
    dbsprite(1, 0, 0, 0, 0x65, 0x00),
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const uint8_t Unknown_115ee1[] = {
    5,
    dbsprite(1, 0, 0, 0, 0x66, 0x00),
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const uint8_t Unknown_115ef6[] = {
    7,
    dbsprite(0, 0, 0, 0, 0x67, 0x01),
    dbsprite(0, 1, 0, 0, 0x68, 0x01),
    dbsprite(0, 2, 0, 0, 0x6d, 0x00),
    dbsprite(1, 2, 0, 0, 0x69, 0x00),
    dbsprite(2, 2, 0, 0, 0x6a, 0x00),
    dbsprite(1, 3, 0, 0, 0x6b, 0x00),
    dbsprite(2, 3, 0, 0, 0x6c, 0x00),
};

const uint8_t Unknown_115f13[] = {
    7,
    dbsprite(0, 0, 0, 0, 0x67, 0x01),
    dbsprite(0, 1, 0, 0, 0x68, 0x01),
    dbsprite(0, 2, 0, 0, 0x6e, 0x00),
    dbsprite(1, 2, 0, 0, 0x69, 0x00),
    dbsprite(2, 2, 0, 0, 0x6a, 0x00),
    dbsprite(1, 3, 0, 0, 0x6b, 0x00),
    dbsprite(2, 3, 0, 0, 0x6c, 0x00),
};

const uint8_t Unknown_115f30[] = {
    7,
    dbsprite(0, 0, 0, 0, 0x67, 0x01),
    dbsprite(0, 1, 0, 0, 0x68, 0x01),
    dbsprite(0, 2, 0, 0, 0x6f, 0x00),
    dbsprite(1, 2, 0, 0, 0x69, 0x00),
    dbsprite(2, 2, 0, 0, 0x6a, 0x00),
    dbsprite(1, 3, 0, 0, 0x6b, 0x00),
    dbsprite(2, 3, 0, 0, 0x6c, 0x00),
};

const uint8_t Unknown_115f4d[] = {
    7,
    dbsprite(0, 0, 0, 0, 0x67, 0x01),
    dbsprite(0, 1, 0, 0, 0x68, 0x01),
    dbsprite(0, 2, 0, 0, 0x70, 0x00),
    dbsprite(1, 2, 0, 0, 0x69, 0x00),
    dbsprite(2, 2, 0, 0, 0x6a, 0x00),
    dbsprite(1, 3, 0, 0, 0x6b, 0x00),
    dbsprite(2, 3, 0, 0, 0x6c, 0x00),
};

const uint8_t Unknown_115f6a[] = {
    7,
    dbsprite(0, 0, 0, 0, 0x67, 0x01),
    dbsprite(0, 1, 0, 0, 0x68, 0x01),
    dbsprite(0, 2, 0, 0, 0x71, 0x00),
    dbsprite(1, 2, 0, 0, 0x69, 0x00),
    dbsprite(2, 2, 0, 0, 0x6a, 0x00),
    dbsprite(1, 3, 0, 0, 0x6b, 0x00),
    dbsprite(2, 3, 0, 0, 0x6c, 0x00),
};

const uint8_t Unknown_115f87[] = {
    5,
    dbsprite(1, 0, 0, 0, 0x72, 0x00),
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const uint8_t Unknown_115f9c[] = {
    5,
    dbsprite(1, 0, 0, 0, 0x73, 0x00),
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const uint8_t Unknown_115fb1[] = {
    5,
    dbsprite(1, 0, 0, 1, 0x64, 0x60),
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const uint8_t Unknown_115fc6[] = {
    5,
    dbsprite(1, 0, 0, 1, 0x65, 0x60),
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const uint8_t Unknown_115fdb[] = {
    5,
    dbsprite(1, 0, 0, 1, 0x66, 0x60),
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const uint8_t Unknown_115ff0[] = {
    5,
    dbsprite(1, 0, 0, 1, 0x72, 0x60),
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const uint8_t Unknown_116005[] = {
    5,
    dbsprite(1, 0, 0, 1, 0x73, 0x60),
    dbsprite(0, 1, 0, 0, 0x60, 0x01),
    dbsprite(1, 1, 0, 0, 0x61, 0x01),
    dbsprite(0, 2, 0, 0, 0x62, 0x01),
    dbsprite(1, 2, 0, 0, 0x63, 0x01),
};

const char MobileDialingGFX[] = "gfx/mobile/dialing.png";

void Function11615a(void){
    // XOR_A_A;
    // LD_addr_A(wc30d);
    wram->wc30d = 0;
    // LD_addr_A(wc319);
    wram->wc319 = 0;
    // LD_addr_A(wc310);
    wram->wc310 = 0;
    // LD_addr_A(wc311);
    wram->wc311 = 0;
    // LD_addr_A(wc312);
    wram->wc312 = 0;
    // LD_addr_A(wc313);
    wram->wc313 = 0;
    // LD_addr_A(wc314);
    wram->wc314[0] = 0;
    // LD_addr_A(wc314 + 1);
    wram->wc314[1] = 0;
    // LD_addr_A(wc314 + 4);
    wram->wc314[4] = 0;
    // LD_addr_A(wc3f6);
    wram->wc3f6 = 0;
    // LD_addr_A(wc3f8);
    wram->wc3f8 = 0;
    // LD_addr_A(wc3f2);
    wram->wc3f2 = 0;
    // LD_addr_A(wc3f4);
    wram->wc3f4 = 0;
    // LD_A(0x24);
    // LD_addr_A(wc3f5);
    wram->wc3f5 = 0x24;
    // LD_A(0x7);
    // LD_addr_A(wc3f7);
    wram->wc3f7 = 0x7;
    // LD_A(0xb0);
    // LD_addr_A(wc30e);
    wram->wc30e = 0xb0;
    // LD_addr_A(wc3f1);
    wram->wc3f1 = 0xb0;
    // LD_A(0x48);
    // LD_addr_A(wc30f);
    wram->wc30f = 0x48;
    // LD_addr_A(wc3f3);
    wram->wc3f3 = 0x48;
    // RET;

}

void Function11619d(void){
    // LD_A_addr(wc30d);
    // AND_A_A;
    // RET_Z ;
    if(wram->wc30d == 0)
        return;
    // LD_A_addr(wc319);
    // CP_A(0x2);
    // IF_C goto asm_1161b4;
    if(wram->wc319 >= 0x2) {
        // LD_A(0xa0);
        // LD_HL(wVirtualOAM);
        // LD_BC(25 * SPRITEOAMSTRUCT_LENGTH);
        // CALL(aByteFill);
        ByteFill_Conv2(wram->wVirtualOAMSprite, 25 * SPRITEOAMSTRUCT_LENGTH, 0xa0);
    }

// asm_1161b4:
    // CALL(aFunction1161b8);
    // Function1161b8(); // TODO: Actually convert this function
    // RET;
}

void Function1161b8(void){
    //jumptable ['.Jumptable', 'wc319']


Jumptable:
    //dw ['Function1161d5'];
    //dw ['Function116294'];
    //dw ['Function1162cb'];
    //dw ['Function1162f2'];
    //dw ['Function1163c0'];
    //dw ['Function11636e'];
    //dw ['Function116441'];

    return Function1161d5();
}

void Function1161d5(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;

    LD_A(0x6);
    LDH_addr_A(rSVBK);

    LD_HL(mPichuBorderMobileTilemapAttrmap);
    LD_DE(wDecompressScratch);
    LD_BC(32 * 12 * 2);
    CALL(aCopyBytes);

    NOP;


wait_for_vblank:
//  Wait until a vblank would occur had interrupts not just been disabled.
    LDH_A_addr(rLY);
    CP_A(LY_VBLANK + 1);
    IF_NZ goto wait_for_vblank;

    LD_A(0xd0);
    LDH_addr_A(rHDMA1);
    LD_A(0x0);
    LDH_addr_A(rHDMA2);
    LD_A(0x1c);
    LDH_addr_A(rHDMA3);
    XOR_A_A;
    LDH_addr_A(rHDMA4);
    LD_A(0x8);
    LDH_addr_A(rHDMA5);

    LD_A(0xd0);
    LDH_addr_A(rHDMA1);
    LD_A(0x80);
    LDH_addr_A(rHDMA2);
    LD_A(0x1c);
    LDH_addr_A(rHDMA3);
    LD_A(0x80);
    LDH_addr_A(rHDMA4);
    LD_A(0x8);
    LDH_addr_A(rHDMA5);

    LD_A(0xd1);
    LDH_addr_A(rHDMA1);
    LD_A(0x0);
    LDH_addr_A(rHDMA2);
    LD_A(0x1d);
    LDH_addr_A(rHDMA3);
    XOR_A_A;
    LDH_addr_A(rHDMA4);
    LD_A(0x8);
    LDH_addr_A(rHDMA5);

    LD_A(0x1);
    LDH_addr_A(rVBK);

    LD_A(0xd1);
    LDH_addr_A(rHDMA1);
    LD_A(0x80);
    LDH_addr_A(rHDMA2);
    LD_A(0x1c);
    LDH_addr_A(rHDMA3);
    XOR_A_A;
    LDH_addr_A(rHDMA4);
    LD_A(0x8);
    LDH_addr_A(rHDMA5);

    LD_A(0xd2);
    LDH_addr_A(rHDMA1);
    LD_A(0x0);
    LDH_addr_A(rHDMA2);
    LD_A(0x1c);
    LDH_addr_A(rHDMA3);
    LD_A(0x80);
    LDH_addr_A(rHDMA4);
    LD_A(0x8);
    LDH_addr_A(rHDMA5);

    LD_A(0xd2);
    LDH_addr_A(rHDMA1);
    LD_A(0x80);
    LDH_addr_A(rHDMA2);
    LD_A(0x1d);
    LDH_addr_A(rHDMA3);
    XOR_A_A;
    LDH_addr_A(rHDMA4);
    LD_A(0x8);
    LDH_addr_A(rHDMA5);

    XOR_A_A;
    LDH_addr_A(rVBK);

    NOP;

    POP_AF;
    LDH_addr_A(rSVBK);

    FARCALL(aReloadMapPart);
    LD_A(0x8);
    LD_addr_A(wMusicFade);
    LD_DE(MUSIC_MOBILE_ADAPTER);
    LD_A_E;
    LD_addr_A(wMusicFadeID);
    LD_A_D;
    LD_addr_A(wMusicFadeID + 1);
    LD_A_addr(wc319);
    INC_A;
    LD_addr_A(wc319);
    RET;

}

void MenuHeader_11628c(void){
//  //  unreferenced
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '6', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];
    //dw ['NULL'];
    //db ['0'];  // default option

    return Function116294();
}

void Function116294(void){
    FARCALL(aFunction170d02);
    LD_A_addr(wc319);
    INC_A;
    LD_addr_A(wc319);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(wBGPals1 + PALETTE_SIZE * 6);
    LD_DE(wc320);
    LD_BC(2 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mPichuBorderMobileBGPalettes);
    LD_DE(wBGPals1 + PALETTE_SIZE * 7);
    LD_BC(1 * PALETTE_SIZE);
    CALL(aCopyBytes);
    CALL(aSetPalettes);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A(0x30);
    LDH_addr_A(hWY);
    RET;

}

void Function1162cb(void){
    FARCALL(aFunction170cc6);
    LD_A_addr(wc319);
    INC_A;
    LD_addr_A(wc319);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(mPichuBorderMobileOBPalettes);
    LD_DE(wOBPals1 + 2 * PALETTE_SIZE);
    LD_BC(6 * PALETTE_SIZE);
    CALL(aCopyBytes);
    CALL(aSetPalettes);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function1162f2(void){
    CALL(aFunction11659d);
    CALL(aFunction116758);
    CALL(aFunction1167a6);
    LD_A_addr(wc310);
    CP_A(EGG);
    RET_Z ;
    SLA_A;
    LD_C_A;
    LD_B(0);
    LD_HL(mUnknown_1168c5);
    ADD_HL_BC;
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    PUSH_DE;
    POP_HL;
    LD_A_addr(wc30e);
    LD_C_A;
    LD_A_addr(wc30f);
    LD_B_A;
    LD_A_addr(wc314 + 4);
    LD_E_A;
    LD_A_hli;
    SUB_A_E;
    LD_DE(wVirtualOAMSprite09);

asm_116321:
    PUSH_AF;
    LD_A_hli;
    ADD_A_B;
    LD_de_A;  // y
    INC_DE;
    LD_A_hli;
    ADD_A_C;
    LD_de_A;  // x
    INC_DE;
    LD_A_hli;
    LD_de_A;  // tile id
    INC_DE;
    LD_A_hli;
    LD_de_A;  // attributes
    INC_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_116321;
    CALL(aFunction116468);
    LD_A_addr(wc3f5);
    SLA_A;
    LD_C_A;
    LD_B(0);
    LD_HL(mUnknown_1168c5);
    ADD_HL_BC;
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    PUSH_DE;
    POP_HL;
    LD_A_addr(wc3f1);
    LD_C_A;
    LD_A_addr(wc3f3);
    LD_B_A;
    LD_A_addr(wc3f8);
    LD_E_A;
    LD_A_hli;
    SUB_A_E;
    LD_DE(wVirtualOAMSprite00);

asm_11635a:
    PUSH_AF;
    LD_A_hli;
    ADD_A_B;
    LD_de_A;  // y
    INC_DE;
    LD_A_hli;
    ADD_A_C;
    LD_de_A;  // x
    INC_DE;
    LD_A_hli;
    LD_de_A;  // tile id
    INC_DE;
    LD_A_hli;
    LD_de_A;  // attributes
    INC_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_11635a;
    RET;

}

void Function11636e(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(wBGPals2);
    LD_DE(wBGPals1);
    LD_BC(8 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aSetPalettes);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_A(0xa0);
    LD_HL(wVirtualOAM);
    LD_BC(16 * SPRITEOAMSTRUCT_LENGTH);
    CALL(aByteFill);
    LD_A(0x90);
    LDH_addr_A(hWY);
    CALL(aUpdateSprites);
    POP_AF;
    LDH_addr_A(rSVBK);
    FARCALL(aReloadMapPart);
    LD_A(0x8);
    LD_addr_A(wMusicFade);
    LD_A_addr(wMapMusic);
    LD_addr_A(wMusicFadeID);
    XOR_A_A;
    LD_addr_A(wMusicFadeID + 1);
    XOR_A_A;
    LD_addr_A(wc319);
    LD_addr_A(wc30d);
    RET;

}

void Function1163c0(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_A(0xa0);
    LD_HL(wVirtualOAM);
    LD_BC(16 * SPRITEOAMSTRUCT_LENGTH);
    CALL(aByteFill);
    CALL(aDelayFrame);
    FARCALL(av_RefreshSprites);
    LD_B(SCGB_MAPPALS);
    CALL(aGetSGBLayout);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(0xc320);
    LD_DE(wd030);
    LD_BC(0x0010);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aSetPalettes);
    CALL(aDelayFrame);
    LD_A(0x90);
    LDH_addr_A(hWY);
    CALL(aUpdateSprites);
    FARCALL(av_ClearSprites);
    POP_AF;
    LDH_addr_A(rSVBK);
    FARCALL(aReloadMapPart);
    LD_A_addr(wLinkMode);
    CP_A(LINK_MOBILE);
    IF_Z goto asm_11642a;
    LD_A(0x8);
    LD_addr_A(wMusicFade);
    LD_A_addr(wMapMusic);
    LD_addr_A(wMusicFadeID);
    XOR_A_A;
    LD_addr_A(wMusicFadeID + 1);
    goto asm_116439;


asm_11642a:
    LD_A(0x8);
    LD_addr_A(wMusicFade);
    LD_A(LOW(MUSIC_NONE));
    LD_addr_A(wMusicFadeID);
    LD_A(HIGH(MUSIC_NONE));
    LD_addr_A(wMusicFadeID + 1);


asm_116439:
    XOR_A_A;
    LD_addr_A(wc319);
    LD_addr_A(wc30d);
    RET;

}

void Function116441(void){
    FARCALL(aFunction17d405);
    LD_A(0x90);
    LDH_addr_A(hWY);
    FARCALL(aReloadMapPart);
    LD_A(0x8);
    LD_addr_A(wMusicFade);
    LD_A_addr(wMapMusic);
    LD_addr_A(wMusicFadeID);
    XOR_A_A;
    LD_addr_A(wMusicFadeID + 1);
    XOR_A_A;
    LD_addr_A(wc319);
    LD_addr_A(wc30d);
    RET;

}

void Function116468(void){
    CALL(aFunction116567);
    LD_A_addr(wc314);
    CP_A(0xd);
    IF_NZ goto asm_1164a8;
    LD_HL(wc30e);
    LD_A_hl;
    CP_A(0x50);
    IF_NC goto asm_116484;
    LD_A(0x50);
    SUB_A_hl;
    ADD_A(0x50);
    LD_addr_A(wc3f1);
    goto asm_11648d;


asm_116484:
    SUB_A(0x50);
    LD_C_A;
    LD_A(0x50);
    SUB_A_C;
    LD_addr_A(wc3f1);


asm_11648d:
    LD_HL(wc30f);
    LD_A_hl;
    CP_A(0x60);
    IF_NC goto asm_11649e;
    LD_A(0x60);
    SUB_A_hl;
    ADD_A(0x60);
    LD_addr_A(wc3f3);
    RET;


asm_11649e:
    SUB_A(0x60);
    LD_C_A;
    LD_A(0x60);
    SUB_A_C;
    LD_addr_A(wc3f3);
    RET;


asm_1164a8:
    LD_HL(wc30e);
    LD_A(0xb0);
    CP_A_hl;
    IF_NC goto asm_1164b8;
    LD_A_addr(wc3f1);
    AND_A_A;
    IF_Z goto asm_11650b;
    goto asm_1164f2;


asm_1164b8:
    LD_A_addr(wc3f1);
    SUB_A_hl;
    IF_NC goto asm_1164c1;
    XOR_A(0xff);
    INC_A;


asm_1164c1:
    LD_B_A;
    LD_C(0x0);
    LD_A(0x5);

asm_1164c6:
    SRL_B;
    RR_C;
    DEC_A;
    IF_NZ goto asm_1164c6;
    LD_A_C;
    LD_addr_A(wc3fa);
    LD_A_B;
    LD_addr_A(wc3f9);
    LD_A_addr(wc3f1);
    SUB_A_hl;
    IF_C goto asm_1164f2;
    LD_C(0x0);
    LD_A_addr(wc3fa);
    XOR_A(0xff);
    ADD_A(0x1);
    RL_C;
    LD_addr_A(wc3fa);
    LD_A_addr(wc3f9);
    XOR_A(0xff);
    ADD_A_C;
    LD_addr_A(wc3f9);


asm_1164f2:
    LD_A_addr(wc3f2);
    LD_L_A;
    LD_A_addr(wc3f1);
    LD_H_A;
    LD_A_addr(wc3fa);
    LD_E_A;
    LD_A_addr(wc3f9);
    LD_D_A;
    ADD_HL_DE;
    LD_A_L;
    LD_addr_A(wc3f2);
    LD_A_H;
    LD_addr_A(wc3f1);


asm_11650b:
    LD_HL(wc30f);
    LD_A(0xb0);
    CP_A_hl;
    IF_C goto asm_11654d;
    LD_A_addr(wc3f3);
    SUB_A_hl;
    IF_NC goto asm_11651c;
    XOR_A(0xff);
    INC_A;


asm_11651c:
    LD_B_A;
    LD_C(0x0);
    LD_A(0x5);

asm_116521:
    SRL_B;
    RR_C;
    DEC_A;
    IF_NZ goto asm_116521;
    LD_A_C;
    LD_addr_A(wc3fc);
    LD_A_B;
    LD_addr_A(wc3fb);
    LD_A_addr(wc3f3);
    SUB_A_hl;
    IF_C goto asm_11654d;
    LD_C(0x0);
    LD_A_addr(wc3fc);
    XOR_A(0xff);
    ADD_A(0x1);
    RL_C;
    LD_addr_A(wc3fc);
    LD_A_addr(wc3fb);
    XOR_A(0xff);
    ADD_A_C;
    LD_addr_A(wc3fb);


asm_11654d:
    LD_A_addr(wc3f4);
    LD_L_A;
    LD_A_addr(wc3f3);
    LD_H_A;
    LD_A_addr(wc3fc);
    LD_E_A;
    LD_A_addr(wc3fb);
    LD_D_A;
    ADD_HL_DE;
    LD_A_L;
    LD_addr_A(wc3f4);
    LD_A_H;
    LD_addr_A(wc3f3);
    RET;

}
