#include "../constants.h"
#include "mobile_5b.h"
#include "mobile_40.h"
#include "mobile_41.h"
#include "../home/lcd.h"
#include "../home/copy.h"
#include "../home/delay.h"
#include "../home/clear_sprites.h"
#include "../home/tilemap.h"
#include "../home/text.h"
#include "../engine/gfx/color.h"

static void MobileAdapterCheck_RunJumptable(void){
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // LD_addr_A(wcf64);
    wram->wcf64 = 0x0;
    // LD_addr_A(wd002);
    wram->wd002 = 0x0;
    // LD_addr_A(wd003);
    wram->wd003 = 0x0;

    do {
    // loop:
        // CALL(aDelayFrame);
        DelayFrame();
        // FARCALL(aFunction10635c);
        Function10635c();
        // LD_A_addr(wd002);
        // LD_HL(mFunction16c000_Jumptable);
        // RST(aJumpTable);
        switch(wram->wd002) {
        // Jumptable:
            case 0:
            // init:
                // LD_A_addr(wcf64);
                // AND_A_A;
                // RET_Z ;
                if(wram->wcf64 == 0x0)
                    break;
                // LD_addr_A(wd002);
                wram->wd002 = wram->wcf64;
                // XOR_A_A;
                // LD_addr_A(wd003);
                wram->wd003 = 0x0;
                // RET;
                break;
            case 1: Function16c0ba(); break;
            case 2: Function16c089(); break;
            case 3: Function16c09e(); break;
            case 4: Function16c0a8(); break;
            case 5: Function16c0dc(); break;
            case 6: Function16c0ec(); break;
            case 7: Function16c0ba(); break;
            case 8: Function16c0ca(); break;
            case 9: Function16c0dc(); break;
            case 10: Function16c0ec(); break;
            case 11:
            // quit:
                // PUSH_AF;
                // LD_A(0xff);
                // LD_addr_A(wd002);
                wram->wd002 = 0xff;
                // POP_AF;
                // RET;
                break;
        }
        // CALL(aFunction16cb2e);
        Function16cb2e();
        // CALL(aFunction16cbae);
        Function16cbae();
        // LD_A_addr(wd002);
        // CP_A(0xff);
        // IF_NZ goto loop;
    } while(wram->wd002 != 0xff);
    // RET;
}

// Function16c000
void MobileAdapterCheck(void){
// Only for CGB
    // LDH_A_addr(hCGB);
    // AND_A_A;
    // RET_Z ;
    if(hram->hCGB == 0)
        return;
// Only do this once per boot cycle
    // LDH_A_addr(hSystemBooted);
    // AND_A_A;
    // RET_Z ;
    if(hram->hSystemBooted == 0)
        return;
// Disable the joypad during mobile setup
    // LD_A_addr(wJoypadDisable);
    // PUSH_AF;
    uint8_t joypadDisable = wram->wJoypadDisable;
    // SET_A(JOYPAD_DISABLE_SGB_TRANSFER_F);
    // LD_addr_A(wJoypadDisable);
    bit_set(wram->wJoypadDisable, JOYPAD_DISABLE_SGB_TRANSFER_F);
// Do stuff
    // CALL(aMobileSystemSplashScreen_InitGFX);  // Load GFX
    MobileSystemSplashScreen_InitGFX();
    // FARCALL(aSetRAMStateForMobile);
    SetRAMStateForMobile();
    // FARCALL(aEnableMobile);
    EnableMobile();
    // CALL(aFunction16c000_RunJumptable);
    MobileAdapterCheck_RunJumptable();
    // FARCALL(aDisableMobile);
    DisableMobile();
// Prevent this routine from running again
// until the next time the system is turned on
    // XOR_A_A;
    // LDH_addr_A(hSystemBooted);
    hram->hSystemBooted = 0x0;
// Restore the flag state
    // POP_AF;
    // LD_addr_A(wJoypadDisable);
    wram->wJoypadDisable = joypadDisable;
    // RET;
}

void Function16c089(void){
    // LD_A(0x1);
    // LD_addr_A(wd1eb);
    wram->wd1eb = 0x1;
    // LD_addr_A(wd1f1);
    wram->wd1f1 = 0x1;
    // XOR_A_A;
    // LDH_addr_A(hWY);
    hram->hWY = 0x0;
    // CALL(aFunction16c0fa);
    Function16c0fa();
    // LD_A_addr(wd002);
    // LD_addr_A(wcf64);
    wram->wcf64 = wram->wd002;
    // RET;
}

void Function16c09e(void){
    // LD_A_addr(wcf64);
    // CP_A(0x4);
    // RET_NZ ;
    if(wram->wcf64 != 0x4)
        return;
    // CALL(aFunction16c0fa);
    Function16c0fa();
    // RET;
}

void Function16c0a8(void){
    // XOR_A_A;
    // LD_addr_A(wd1eb);
    wram->wd1eb = 0x0;
    // LD_addr_A(wd1f1);
    wram->wd1f1 = 0x0;
    // CALL(aClearSprites);
    ClearSprites();
    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // CALL(aFunction16c0fa);
    Function16c0fa();
    // RET;
}

void Function16c0ba(void){
    // CALL(aFunction16c943);
    bool carry = Function16c943();
    // PUSH_AF;
    // LD_A_addr(wd003);
    // INC_A;
    // LD_addr_A(wd003);
    wram->wd003++;
    // POP_AF;
    // CALL_C (aFunction16c0fa);
    if(carry)
        Function16c0fa();
    // RET;
}

void Function16c0ca(void){
    // LD_A_addr(wd003);
    uint8_t d003 = wram->wd003;
    // CP_A(0x28);
    // PUSH_AF;
    // LD_A_addr(wd003);
    // INC_A;
    // LD_addr_A(wd003);
    wram->wd003++;
    // POP_AF;
    // CALL_Z (aFunction16c0fa);
    if(d003 == 0x28)
        Function16c0fa();
    // RET;
}

void Function16c0dc(void){
    // CALL(aFunction16ca11);
    bool carry = Function16ca11();
    // PUSH_AF;
    // LD_A_addr(wd003);
    // INC_A;
    // LD_addr_A(wd003);
    wram->wd003++;
    // POP_AF;
    // CALL_C (aFunction16c0fa);
    if(carry)
        Function16c0fa();
    // RET;

}

void Function16c0ec(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // PUSH_AF;
    // LD_A(0xff);
    // LD_addr_A(wd002);
    wram->wd002 = 0xff;
    // POP_AF;
    // RET;

}

void Function16c0fa(void){
    // PUSH_AF;
    // LD_A_addr(wd002);
    // INC_A;
    // LD_addr_A(wd002);
    wram->wd002++;
    // XOR_A_A;
    // LD_addr_A(wd003);
    wram->wd003 = 0x0;
    // POP_AF;
    // RET;
}

static void MobileSystemSplashScreen_InitGFX_LoadPals(void) {
    // LD_DE(wBGPals1);
    // LD_HL(mMobileSplashScreenPalettes);
    // LD_BC(8);
    // LD_A(0x5);
    LoadPaletteAssetToBuffer(wram->wBGPals1, sizeof(wram->wBGPals1) / sizeof(uint16_t), MobileSplashScreenPalettes, 2);
    // CALL(aFarCopyWRAM);
    // FARCALL(aApplyPals);
    ApplyPals_Conv();
    // RET;
}

static void MobileSystemSplashScreen_InitGFX_LoadTilemap(const char* path) {
    // hlcoord(0, 0, wTilemap);
    // LD_BC(20);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH, 0x0);
    // LD_HL(mMobileSystemSplashScreen_InitGFX_Tilemap);
    // decoord(0, 1, wTilemap);
    // LD_BC(0x0154);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 1, wram->wTilemap), 17 * SCREEN_WIDTH, path);
    // RET;
}

static void MobileSystemSplashScreen_InitGFX_LoadAttrmap(const char* path) {
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH, 0x0);
    // LD_HL(mMobileSystemSplashScreen_InitGFX_Attrmap);
    // decoord(0, 1, wAttrmap);
    // LD_BC(17 * SCREEN_WIDTH);
    // CALL(aCopyBytes);
    LoadAssetToBuffer(coord(0, 1, wram->wAttrmap), 17 * SCREEN_WIDTH, path);
    // RET;
}

void MobileSystemSplashScreen_InitGFX(void){
    static const char Tiles[] = "gfx/mobile/mobile_splash.png"; // 2bpp
    static const char Tilemap[] = "gfx/mobile/mobile_splash.tilemap";
    static const char Attrmap[] = "gfx/mobile/mobile_splash.attrmap";
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_HL(vTiles2);
    // LD_DE(mMobileSystemSplashScreen_InitGFX_Tiles);
    // LD_BC((BANK(aMobileSystemSplashScreen_InitGFX_Tiles) << 8) | 104);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 +  0 * LEN_2BPP_TILE, Tiles, 0x00, 9);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 +  9 * LEN_2BPP_TILE, Tiles, 0x0E, 12);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + 20 * LEN_2BPP_TILE, Tiles, 0x1C, 11);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + 31 * LEN_2BPP_TILE, Tiles, 0x2A, 12);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + 43 * LEN_2BPP_TILE, Tiles, 0x39, 7);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + 50 * LEN_2BPP_TILE, Tiles, 0x43, 2);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + 52 * LEN_2BPP_TILE, Tiles, 0x47, 12);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + 64 * LEN_2BPP_TILE, Tiles, 0x55, 12);
    // CALL(aMobileSystemSplashScreen_InitGFX_LoadPals);
    MobileSystemSplashScreen_InitGFX_LoadPals();
    // CALL(aMobileSystemSplashScreen_InitGFX_LoadTilemap);
    MobileSystemSplashScreen_InitGFX_LoadTilemap(Tilemap);
    // CALL(aMobileSystemSplashScreen_InitGFX_LoadAttrmap);
    MobileSystemSplashScreen_InitGFX_LoadAttrmap(Attrmap);
    // hlbgcoord(0, 0, vBGMap0);
    // CALL(aFunction16cc73);
    Function16cc73(bgcoord(0, 0, vram->vBGMap0), bgcoord(0, 0, vram->vBGMap2));
    // CALL(aFunction16cc02);
    Function16cc02();
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aEnableLCD);
    EnableLCD();
    // RET;
}

const char MobileSplashScreenPalettes[] = "gfx/mobile/mobile_splash.pal";

bool Function16c943(void){
    uint8_t buffer[128];
    // LD_A_addr(wd003);
    // AND_A_A;
    // IF_NZ goto asm_16c95e;
    if(wram->wd003 == 0) {
        // LDH_A_addr(rSVBK);
        // PUSH_AF;
        // LD_A(0x5);
        // LDH_addr_A(rSVBK);
        // LD_A(0xff);
        // LD_BC(1 * PALETTE_SIZE);
        // LD_HL(wBGPals1);
        // CALL(aByteFill);
        ByteFill(wram->wBGPals1, 1 * PALETTE_SIZE, 0xff);
        // POP_AF;
        // LDH_addr_A(rSVBK);
    }

// asm_16c95e:
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_E(0x0);
    uint8_t e = 0x0;
    // LD_A(0x0);
    uint8_t a = 0x0;
    LoadPaletteAssetToArray(buffer, MobileSplashScreenPalettes, 8);

    do {
    // asm_16c969:
        // LD_HL(mMobileSplashScreenPalettes);
        // CALL(aFunction16cab6);
        // CALL(aFunction16cabb);
        // LD_D_A;
        uint8_t d = Function16cabb(Function16cab6(buffer, e));
        // LD_HL(wBGPals1);
        // CALL(aFunction16cab6);
        // CALL(aFunction16cabb);
        a = Function16cabb(Function16cab6(wram->wBGPals1, e));
        // CP_A_D;
        // IF_Z goto asm_16c991;
        if(a != d) {
            // LD_B(0x1);
            uint8_t b = 0x1;

            do {
            // asm_16c981:
                // DEC_A;
                // CP_A_D;
                // IF_Z goto asm_16c988;
                if(--a == d)
                    break;
                // DEC_B;
                // IF_NZ goto asm_16c981;
            } while(--b != 0);

        // asm_16c988:
            // LD_HL(wBGPals1);
            // CALL(aFunction16cab6);
            // CALL(aFunction16cadc);
            Function16cadc(wram->wBGPals1 + e, a);
        }

    // asm_16c991:
        // LD_HL(mMobileSplashScreenPalettes);
        // CALL(aFunction16cab6);
        // CALL(aFunction16cad8);
        // LD_D_A;
        d = Function16cad8(Function16cab6(buffer, e));
        // LD_HL(wBGPals1);
        // CALL(aFunction16cab6);
        // CALL(aFunction16cad8);
        a = Function16cad8(Function16cab6(wram->wBGPals1, e));
        // CP_A_D;
        // IF_Z goto asm_16c9b9;
        if(a != d) {
            // LD_B(0x1);
            uint8_t b = 0x1;

            do {
            // asm_16c9a9:
                // DEC_A;
                // CP_A_D;
                // IF_Z goto asm_16c9b0;
                if(--a == d)
                    break;
                // DEC_B;
                // IF_NZ goto asm_16c9a9;
            } while(--b != 0);

        // asm_16c9b0:
            // LD_HL(wBGPals1);
            // CALL(aFunction16cab6);
            // CALL(aFunction16cb08);
            Function16cb08(wram->wBGPals1 + e, a);
        }

    // asm_16c9b9:
        // LD_HL(mMobileSplashScreenPalettes);
        // CALL(aFunction16cab6);
        // CALL(aFunction16cac4);
        // LD_D_A;
        d = Function16cac4(Function16cab6(buffer, e));
        // LD_HL(wBGPals1);
        // CALL(aFunction16cab6);
        // CALL(aFunction16cac4);
        a = Function16cac4(Function16cab6(wram->wBGPals1, e));
        // CP_A_D;
        // IF_Z goto asm_16c9e1;
        if(a != d) {
            // LD_B(0x1);
            uint8_t b = 0x1;

            do {
            // asm_16c9d1:
                // DEC_A;
                // CP_A_D;
                // IF_Z goto asm_16c9d8;
                if(--a == d)
                    break;
                // DEC_B;
                // IF_NZ goto asm_16c9d1;
            } while(--b != 0);

        // asm_16c9d8:
            // LD_HL(wBGPals1);
            // CALL(aFunction16cab6);
            // CALL(aFunction16cae8);
            Function16cae8(wram->wBGPals1 + e, a);
        }

    // asm_16c9e1:
        // INC_E;
        // INC_E;
        e += 2;
        // LD_A_E;
        // CP_A(0x8);
        // IF_NZ goto asm_16c969;
    } while(e != 0x8);
    // FARCALL(aApplyPals);
    ApplyPals_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wd003);
    // CP_A(0x1f);
    // IF_Z goto asm_16ca09;
    if(wram->wd003 != 0x1f) {
        // POP_AF;
        // LDH_addr_A(rSVBK);
        // LD_E(0x0);
        // POP_AF;
        // LDH_addr_A(rSVBK);
        // AND_A_A;
        // RET;
        return false;
    }

// asm_16ca09:
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // SCF;
    // RET;
    return true;
}

bool Function16ca11(void){
    // LD_A_addr(wd003);
    // AND_A_A;
    // IF_NZ goto asm_16ca1d;
    if(wram->wd003 == 0) {
        // FARCALL(aApplyPals);
        ApplyPals_Conv();
    }

// asm_16ca1d:
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_E(0x0);
    uint8_t e = 0x0;
    // LD_A(0x0);
    uint8_t a = 0x0;

    do {
    // asm_16ca28:
        // LD_HL(wBGPals1);
        // CALL(aFunction16cab6);
        // CALL(aFunction16cabb);
        a = Function16cabb(Function16cab6(wram->wBGPals1, e));
        // CP_A(0x1f);
        // IF_Z goto asm_16ca48;
        if(a != 0x1f) {
            // LD_B(0x1);
            uint8_t b = 0x1;

            do {
            // asm_16ca37:
                // INC_A;
                // CP_A(0x1f);
                // IF_Z goto asm_16ca3f;
                if(++a == 0x1f)
                    break;
                // DEC_B;
                // IF_NZ goto asm_16ca37;
            } while(--b != 0);

        // asm_16ca3f:
            // LD_HL(wBGPals1);
            // CALL(aFunction16cab6);
            // CALL(aFunction16cadc);
            Function16cadc(wram->wBGPals1 + e, a);
        }

    // asm_16ca48:
        // LD_HL(wBGPals1);
        // CALL(aFunction16cab6);
        // CALL(aFunction16cad8);
        a = Function16cad8(Function16cab6(wram->wBGPals1, e));
        // CP_A(0x1f);
        // IF_Z goto asm_16ca68;
        if(a != 0x1f) {
            // LD_B(0x1);
            uint8_t b = 0x1;

            do {
            // asm_16ca57:
                // INC_A;
                // CP_A(0x1f);
                // IF_Z goto asm_16ca5f;
                if(++a == 0x1f)
                    break;
                // DEC_B;
                // IF_NZ goto asm_16ca57;
            } while(--b != 0);

        // asm_16ca5f:
            // LD_HL(wBGPals1);
            // CALL(aFunction16cab6);
            // CALL(aFunction16cb08);
            Function16cb08(wram->wBGPals1 + e, a);
        }

    // asm_16ca68:
        // LD_HL(wBGPals1);
        // CALL(aFunction16cab6);
        // CALL(aFunction16cac4);
        a = Function16cac4(Function16cab6(wram->wBGPals1, e));
        // CP_A(0x1f);
        // IF_Z goto asm_16ca88;
        if(a != 0x1f) {
            // LD_B(0x1);
            uint8_t b = 0x1;

            do {
            // asm_16ca77:
                // INC_A;
                // CP_A(0x1f);
                // IF_Z goto asm_16ca7f;
                if(++a == 0x1f)
                    break;
                // DEC_B;
                // IF_NZ goto asm_16ca77;
            } while(--b != 0);

        // asm_16ca7f:
            // LD_HL(wBGPals1);
            // CALL(aFunction16cab6);
            // CALL(aFunction16cae8);
            Function16cae8(wram->wBGPals1 + e, a);
        }

    // asm_16ca88:
        // INC_E;
        // INC_E;
        e += 2;
        // LD_A_E;
        // CP_A(0x8);
        // IF_NZ goto asm_16ca28;
    } while(e != 0x8);
    // FARCALL(aApplyPals);
    ApplyPals_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wd003);
    // CP_A(0x1f);
    // IF_Z goto asm_16caae;
    if(wram->wd003 != 0x1f) {
        // POP_AF;
        // LDH_addr_A(rSVBK);
        // POP_AF;
        // LDH_addr_A(rSVBK);
        // AND_A_A;
        // RET;
        return false;
    }

// asm_16caae:
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // SCF;
    // RET;
    return true;
}

const uint8_t* Function16cab6(const uint8_t* hl, uint8_t e){
    // LD_B(0x0);
    // LD_C_E;
    // ADD_HL_BC;
    // RET;
    return hl + e;
}

uint8_t Function16cabb(const uint8_t* hl){
    // INC_HL;
    // LD_A_hl;
    // SRL_A;
    // SRL_A;
    // AND_A(0x1f);
    // RET;
    return (hl[1] >> 2) & 0x1f;
}

uint8_t Function16cac4(const uint8_t* hl){
    // INC_HL;
    // LD_A_hld;
    // AND_A(0x3);
    // LD_B_A;
    uint8_t b = hl[1] & 0x3;
    // LD_A_hl;
    // SLA_A;
    // RL_B;
    // SLA_A;
    // RL_B;
    // SLA_A;
    // RL_B;
    // LD_A_B;
    // RET;
    return (b << 3) | (hl[0] >> 5);
}

uint8_t Function16cad8(const uint8_t* hl){
    // LD_A_hl;
    // AND_A(0x1f);
    // RET;
    return *hl & 0x1f;
}

void Function16cadc(uint8_t* hl, uint8_t a){
    // SLA_A;
    // SLA_A;
    // LD_B_A;
    // INC_HL;
    // LD_A_hl;
    // AND_A(0x83);
    // OR_A_B;
    // LD_hl_A;
    hl[1] = (hl[1] & 0x83) | (a << 2);
    // RET;
}

void Function16cae8(uint8_t* hl, uint8_t a){
    // LD_C_A;
    // SRL_A;
    // SRL_A;
    // SRL_A;
    // LD_B_A;
    // INC_HL;
    // LD_A_hl;
    // AND_A(0xfc);
    // OR_A_B;
    // LD_hld_A;
    hl[1] = (hl[1] & 0xfc) | (a >> 3);
    // LD_A_C;
    // SLA_A;
    // SLA_A;
    // SLA_A;
    // SLA_A;
    // SLA_A;
    // LD_B_A;
    // LD_A_hl;
    // AND_A(0x1f);
    // OR_A_B;
    // LD_hl_A;
    hl[0] = (hl[0] & 0x1f) | (a << 5);
    // RET;
}

void Function16cb08(uint8_t* hl, uint8_t a){
    // LD_B_A;
    // LD_A_hl;
    // AND_A(0xe0);
    // OR_A_B;
    // LD_hl_A;
    *hl = (*hl & 0xe0) | a;
    // RET;
}

void Function16cb0f(void){
    // XOR_A_A;
    // LD_addr_A(wd1ea);
    wram->wd1ea = 0x0;
    // LD_addr_A(wd1eb);
    wram->wd1eb = 0x0;
    // XOR_A_A;
    // LD_addr_A(wd1ec);
    wram->wd1ec = 0x0;
    // LD_A(0x70);
    // LD_addr_A(wd1ee);
    wram->wd1ee = 0x70;
    // LD_A(0x4);
    // LD_addr_A(wd1ed);
    wram->wd1ed = 0x4;
    // LD_A(0xa0);
    // LD_addr_A(wd1ef);
    wram->wd1ef = 0xa0;
    // XOR_A_A;
    // LD_addr_A(wd1f0);
    wram->wd1f0 = 0x0;
    // RET;
}

void Function16cb2e(void){
    // LD_A_addr(wd1eb);
    // AND_A_A;
    // RET_Z ;
    if(wram->wd1eb == 0)
        return;
    // CALL(aFunction16cb40);
    Function16cb40();
    // LD_HL(mUnknown_16cb86);
    // LD_DE(wVirtualOAM);
    // CALL(aFunction16cb5d);
    Function16cb5d(wram->wVirtualOAMSprite, Unknown_16cb86);
    // RET;
}

void Function16cb40(void){
    // LD_HL(wd1ec);
    // INC_hl;
    // LD_A_hl;
    // CP_A(0x18);
    // RET_C ;
    if(++wram->wd1ec < 0x18)
        return;
    // XOR_A_A;
    // LD_hl_A;
    wram->wd1ec = 0x0;
    // LD_A_addr(wd1ef);
    // CP_A(0xa0);
    // IF_NZ goto asm_16cb57;
    if(wram->wd1ef == 0xa0) {
        // LD_A(0xa7);
        // LD_addr_A(wd1ef);
        wram->wd1ef = 0xa7;
        // RET;
        return;
    }
    else {
    // asm_16cb57:
        // LD_A(0xa0);
        // LD_addr_A(wd1ef);
        wram->wd1ef = 0xa0;
        // RET;
        return;
    }
}

// Mobile_CopySpriteOAMData
void Function16cb5d(struct SpriteOAM* oam, const uint8_t* hl){
    // LD_A_hli;
    uint8_t count = *(hl++);
    // AND_A_A;
    // RET_Z ;
    if(count == 0)
        return;

    do {
    // asm_16cb60:
        // PUSH_AF;
        // LD_A_addr(wd1ee);
        // ADD_A_hl;
        // ADD_A(0x10);
        // LD_de_A;
        oam->yCoord = wram->wd1ee + *hl + 0x10;
        // INC_HL;
        hl++;
        // INC_DE;
        // LD_A_addr(wd1ed);
        // ADD_A_hl;
        // ADD_A(0x8);
        // LD_de_A;
        oam->xCoord = wram->wd1ed + *hl + 0x8;
        // INC_HL;
        hl++;
        // INC_DE;
        // LD_A_addr(wd1ef);
        // ADD_A_hl;
        // LD_de_A;
        oam->tileID = wram->wd1ef + *hl;
        // INC_HL;
        hl++;
        // INC_DE;
        // LD_A_addr(wd1f0);
        // OR_A_hl;
        // LD_de_A;
        oam->attributes = wram->wd1f0 | *hl;
        // INC_HL;
        hl++;
        // INC_DE;
        oam++;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_16cb60;
    } while(--count != 0);
    // RET;
}

const uint8_t Unknown_16cb86[] = {
    7,
    dbsprite(0, 0, 0, 0, 0, 1),
    dbsprite(0, 1, 0, 0, 1, 1), //db ['8', '0', '1', '1'];
    dbsprite(1, 1, 0, 0, 2, 0), //db ['8', '8', '2', '0'];
    dbsprite(2, 1, 0, 0, 3, 0), //db ['8', '16', '3', '0'];
    dbsprite(0, 2, 0, 0, 4, 1), //db ['16', '0', '4', '1'];
    dbsprite(1, 2, 0, 0, 5, 0), //db ['16', '8', '5', '0'];
    dbsprite(2, 2, 0, 0, 6, 0), //db ['16', '16', '6', '0'];
};

// Mobile_Resetd1f1
void Function16cba3(void){
    // XOR_A_A;
    // LD_addr_A(wd1f1);
    wram->wd1f1 = 0x0;
    // LD_addr_A(wd1f2);
    wram->wd1f2 = 0x0;
    // LD_addr_A(wd1f3);
    wram->wd1f3 = 0x0;
    // RET;
}

void Function16cbae(void){
    // LD_A_addr(wd1f1);
    // AND_A_A;
    // RET_Z ;
    if(wram->wd1f1 == 0)
        return;
    // CALL(aFunction16cbba);
    Function16cbba();
    // CALL(aFunction16cbd1);
    Function16cbd1();
    // RET;
}

void Function16cbba(void){
    // LD_HL(wd1f2);
    // INC_hl;
    // LD_A_hl;
    // CP_A(0xc);
    // RET_C ;
    if(++wram->wd1f2 < 0xc)
        return;
    // XOR_A_A;
    // LD_hl_A;
    wram->wd1f2 = 0x0;
    // LD_A_addr(wd1f3);
    // INC_A;
    // CP_A(0x4);
    // IF_C goto asm_16cbcd;
    if(++wram->wd1f3 >= 0x4) {
        // XOR_A_A;
        wram->wd1f3 = 0x0;
    }

// asm_16cbcd:
    // LD_addr_A(wd1f3);
    // RET;
}

void Function16cbd1(void){
    // LD_A_addr(wd1f3);
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mUnknown_16cbfb);
    // ADD_HL_BC;
    // LD_A_hl;
    // LD_BC(2);
    // LD_HL(mUnknown_16cfa3);
    // CALL(aAddNTimes);
    // LD_DE(wBGPals1 + PALETTE_SIZE * 1 + PAL_COLOR_SIZE * 2);
    // LD_BC(PAL_COLOR_SIZE);
    // LD_A(0x5);
    // CALL(aFarCopyWRAM);
    CopyBytes(wram->wBGPals1 + PALETTE_SIZE * 1 + PAL_COLOR_SIZE * 2, Unknown_16cfa3 + Unknown_16cbfb[wram->wd1f3], PAL_COLOR_SIZE);
    // FARCALL(aApplyPals);
    ApplyPals_Conv();
    // LD_A(TRUE);
    // LDH_addr_A(hCGBPalUpdate);
    hram->hCGBPalUpdate = TRUE;
    // RET;
}

const uint8_t Unknown_16cbfb[] = {0, 1, 2, 1, 0, 1, 2};

void Function16cc02(void){
    // CALL(aFunction16cc18);
    Function16cc18();
    // CALL(aFunction16cc49);
    Function16cc49();
    // CALL(aFunction16cc62);
    Function16cc62();
    // CALL(aFunction16cc25);
    Function16cc25();
    // CALL(aFunction16cc6e);
    Function16cc6e();
    // CALL(aFunction16cb0f);
    Function16cb0f();
    // CALL(aFunction16cba3);
    Function16cba3();
    // RET;
}

// Mobile_LoadAdapterCheckGFX
void Function16cc18(void){
    // LD_HL(vTiles1);
    // LD_DE(mMobileAdapterCheckGFX);
    // LD_BC((BANK(aMobileAdapterCheckGFX) << 8) | 46);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles1, MobileAdapterCheckGFX, 0, 46);
    // RET;

}

// Mobile_CopyAdapterCheckPalettes
void Function16cc25(void){
    // LD_HL(mUnknown_16cfa9);
    // LD_DE(wBGPals1 + 1 * PALETTE_SIZE);
    // CALL(aFunction16cc25_CopyPal);
    CopyBytes(wram->wBGPals1 + 1 * PALETTE_SIZE, Unknown_16cfa9, 1 * PALETTE_SIZE);
    // LD_HL(mUnknown_16cfb1);
    // LD_DE(wOBPals1);
    // CALL(aFunction16cc25_CopyPal);
    CopyBytes(wram->wOBPals1, Unknown_16cfb1, 1 * PALETTE_SIZE);
    // LD_HL(mUnknown_16cfb9);
    // LD_DE(wOBPals1 + 1 * PALETTE_SIZE);
    // CALL(aFunction16cc25_CopyPal);
    CopyBytes(wram->wOBPals1 + 1 * PALETTE_SIZE, Unknown_16cfb9, 1 * PALETTE_SIZE);
    // RET;


// CopyPal:
    // LD_BC(1 * PALETTE_SIZE);
    // LD_A(0x5);
    // JP(mFarCopyWRAM);
}

// Mobile_DrawAdapterCheckTiles
void Function16cc49(void){
    // hlcoord(4, 15, wTilemap);
    // LD_A(0x80);
    // CALL(aFunction16cc5a);
    Function16cc5a(coord(4, 15, wram->wTilemap), 0x80);
    // hlcoord(4, 16, wTilemap);
    // LD_A(0x90);
    // CALL(aFunction16cc5a);
    Function16cc5a(coord(4, 16, wram->wTilemap), 0x90);
    // RET;

}

void Function16cc5a(tile_t* hl, tile_t a){
    // LD_C(0x10);
    uint8_t c = 0x10;

    do {
    // asm_16cc5c:
        // LD_hli_A;
        *(hl++) = a;
        // INC_A;
        a++;
        // DEC_C;
        // IF_NZ goto asm_16cc5c;
    } while(--c != 0);
    // RET;
}

// Mobile_FillAdapterCheckAttrmap?
void Function16cc62(void){
    // hlcoord(0, 15, wAttrmap);
    // LD_BC(0x0028);
    // LD_A(0x1);
    // CALL(aByteFill);
    ByteFill(coord(0, 15, wram->wAttrmap), 0x0028, 0x1);
    // RET;
}

void Function16cc6e(void){
    // hlbgcoord(0, 0, vBGMap1);
    // JR(mFunction16cc73);
    return Function16cc73(bgcoord(0, 0, vram->vBGMap1), bgcoord(0, 0, vram->vBGMap3));
}

// Mobile_CopyTilemapAttrmapToVRAM
void Function16cc73(uint8_t* tm, uint8_t* am){
    // LDH_A_addr(rVBK);
    // PUSH_AF;
    // LD_A(0x0);
    // LDH_addr_A(rVBK);
    // PUSH_HL;
    // decoord(0, 0, wTilemap);
    // CALL(aFunction16cc90);
    Function16cc90(tm, coord(0, 0, wram->wTilemap));
    // POP_HL;
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // decoord(0, 0, wAttrmap);
    // CALL(aFunction16cc90);
    Function16cc90(am, coord(0, 0, wram->wAttrmap));
    // POP_AF;
    // LDH_addr_A(rVBK);
    // RET;
}

// Mobile_CopyBufferToBGMap
void Function16cc90(uint8_t* hl, const uint8_t* de){
    // LD_BC(0x1214);
    uint8_t b = SCREEN_HEIGHT;

    do {
    // asm_16cc93:
        // PUSH_BC;
        uint8_t c = SCREEN_WIDTH;

        do {
        // asm_16cc94:
            // LD_A_de;
            // INC_DE;
            // LD_hli_A;
            *(hl++) = *(de++);
            // DEC_C;
            // IF_NZ goto asm_16cc94;
        } while(--c != 0);
        // LD_BC(0x000c);
        // ADD_HL_BC;
        hl += 0x000c;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto asm_16cc93;
    } while(--b != 0);
    // RET;
}

const char MobileAdapterCheckGFX[] = "gfx/mobile/mobile_splash_check.png"; // 2bpp

const uint16_t Unknown_16cfa3[] = {
    rgb(31, 31, 31),
    rgb(25, 27, 29),
    rgb(16, 19, 25),
};

const uint16_t Unknown_16cfa9[] = {
    rgb(31, 31, 31),
    rgb(25, 27, 29),
    rgb(31, 31, 31),
    rgb( 7,  7,  7),
};

const uint16_t Unknown_16cfb1[] = {
    rgb(31, 31, 31),
    rgb(13,  9, 18),
    rgb(26, 21, 16),
    rgb( 7,  7,  7),
};

const uint16_t Unknown_16cfb9[] = {
    rgb(31, 31, 31),
    rgb(18,  5,  2),
    rgb(27, 11, 12),
    rgb( 7,  7,  7),
};
