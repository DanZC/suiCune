#include "../constants.h"
#include "init.h"
#include "sram.h"
#include "copy.h"
#include "audio.h"
#include "delay.h"
#include "tilemap.h"
#include "clear_sprites.h"
#include "../engine/gfx/color.h"
#include "../engine/rtc/rtc.h"

void Reset(void) {
    // NOP;
    // CALL(aInitSound);
    InitSound();
    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0;
    // CALL(aClearPalettes);
    ClearPalettes();
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // LD_A(1 << VBLANK);
    // LDH_addr_A(rIE);
    gb_write(rIE, 1 << VBLANK);
    // NOP;

    // LD_HL(wJoypadDisable);
    // SET_hl(JOYPAD_DISABLE_SGB_TRANSFER_F);
    bit_set(wram->wJoypadDisable, JOYPAD_DISABLE_SGB_TRANSFER_F);

    // LD_C(32);
    // CALL(aDelayFrames);
    DelayFrames(32);

    // JR(mInit);
}

void v_Start(void) {
    // CP_A(0x11);
    // IF_Z goto cgb;
    // XOR_A_A;  // FALSE
    // goto load;

// cgb:
    // LD_A(TRUE);

// load:
    // LDH_addr_A(hCGB);
    hram->hCGB = (REG_A == 0x11)? TRUE: FALSE;
    // LD_A(TRUE);
    // LDH_addr_A(hSystemBooted);
    hram->hSystemBooted = TRUE;
    // return Init();
}

void Init(void) {
    // NOP;

    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // LDH_addr_A(rIE);
    gb_write(rIE, 0);
    // LDH_addr_A(rRP);
    gb_write(rRP, 0);
    // LDH_addr_A(rSCX);
    gb_write(rSCX, 0);
    // LDH_addr_A(rSCY);
    gb_write(rSCY, 0);
    // LDH_addr_A(rSB);
    gb_write(rSB, 0);
    // LDH_addr_A(rSC);
    gb_write(rSC, 0);
    // LDH_addr_A(rWX);
    gb_write(rWX, 0);
    // LDH_addr_A(rWY);
    gb_write(rWY, 0);
    // LDH_addr_A(rBGP);
    gb_write(rBGP, 0);
    // LDH_addr_A(rOBP0);
    gb_write(rOBP0, 0);
    // LDH_addr_A(rOBP1);
    gb_write(rOBP1, 0);
    // LDH_addr_A(rTMA);
    gb_write(rTMA, 0);
    // LDH_addr_A(rTAC);
    gb_write(rTAC, 0);
    // LD_addr_A(wBetaTitleSequenceOpeningType);
    wram->wBetaTitleSequenceOpeningType = 0;

    // LD_A(0b100);  // Start timer at 4096Hz
    // LDH_addr_A(rTAC);
    gb_write(rTAC, 0b100);

// wait:
    // LDH_A_addr(rLY);
    // CP_A(LY_VBLANK + 1);
    // IF_NZ goto wait;
    // NOP;

    // XOR_A_A;
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, 0);

    //  Clear WRAM bank 0
    // LD_HL(WRAM0_Begin);
    // LD_BC(WRAM0_End - WRAM0_Begin);

// ByteFill:
    // LD_hl(0);
    // INC_HL;
    // DEC_BC;
    // LD_A_B;
    // OR_A_C;
    // IF_NZ goto ByteFill;
    ByteFill(wram->wram0, sizeof(wram->wram0), 0);

    // LD_SP(wStackTop);

    //  Clear HRAM
    // LDH_A_addr(hCGB);
    // PUSH_AF;
    uint8_t cgb = hram->hCGB;
    // LDH_A_addr(hSystemBooted);
    // PUSH_AF;
    uint8_t systemBooted = hram->hSystemBooted;
    // XOR_A_A;
    // LD_HL(HRAM_Begin);
    // LD_BC(HRAM_End - HRAM_Begin);
    // CALL(aByteFill);
    ByteFill(hram, sizeof(*hram), 0);
    // POP_AF;
    // LDH_addr_A(hSystemBooted);
    hram->hSystemBooted = systemBooted;
    // POP_AF;
    // LDH_addr_A(hCGB);
    hram->hCGB = cgb;

    // CALL(aClearWRAM);
    ClearWRAM();
    // LD_A(1);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, 1);
    // CALL(aClearVRAM);
    ClearVRAM();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearsScratch);
    ClearsScratch();

/// Don't need to do any of this on PC
    // LD_A(BANK(aWriteOAMDMACodeToHRAM));  // aka BANK(GameInit)
    // RST(aBankswitch);
    // Bankswitch(BANK(aWriteOAMDMACodeToHRAM));

    // CALL(aWriteOAMDMACodeToHRAM);
    // SafeCallGBAuto(aWriteOAMDMACodeToHRAM);
///

    // XOR_A_A;
    // LDH_addr_A(hMapAnims);
    hram->hMapAnims = 0;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;
    // LDH_addr_A(rJOYP);
    gb_write(rJOYP, 0);

    // LD_A(0x8);  // HBlank int enable
    // LDH_addr_A(rSTAT);
    gb_write(rSTAT, 0x8);

    // LD_A(0x90);
    // LDH_addr_A(hWY);
    hram->hWY = 0x90;
    // LDH_addr_A(rWY);
    gb_write(rWY, 0x90);

    // LD_A(7);
    // LDH_addr_A(hWX);
    hram->hWX = 7;
    // LDH_addr_A(rWX);
    gb_write(rWX, 7);

    // LD_A(LCDC_DEFAULT);  // %11100011
                            // LCD on
                            // Win tilemap 1
                            // Win on
                            // BG/Win tiledata 0
                            // BG Tilemap 0
                            // OBJ 8x8
                            // OBJ on
                            // BG on
    // LDH_addr_A(rLCDC);
    gb_write(rLCDC, LCDC_DEFAULT);

    // LD_A(CONNECTION_NOT_ESTABLISHED);
    // LDH_addr_A(hSerialConnectionStatus);
    hram->hSerialConnectionStatus = CONNECTION_NOT_ESTABLISHED;

    // FARCALL(aInitCGBPals);
    InitCGBPals_Conv();

    // LD_A(HIGH(vBGMap1));
    // LDH_addr_A(hBGMapAddress + 1);
    // XOR_A_A;  // LOW(vBGMap1)
    // LDH_addr_A(hBGMapAddress);
    hram->hBGMapAddress = vBGMap1;

    // FARCALL(aStartClock);
    StartClock();

    // XOR_A_A;  // SRAM_DISABLE
    // LD_addr_A(MBC3LatchClock);
    gb_write(MBC3LatchClock, 0);
    // LD_addr_A(MBC3SRamEnable);
    gb_write(MBC3SRamEnable, SRAM_DISABLE);

    // LDH_A_addr(hCGB);
    // AND_A_A;
    // IF_Z goto no_double_speed;
    // CALL(aNormalSpeed);

// no_double_speed:    
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // LD_A(IE_DEFAULT);
    // LDH_addr_A(rIE);
    gb_write(rIE, IE_DEFAULT);
    // NOP;

    // CALL(aDelayFrame);
    DelayFrame();

    // PREDEF(pInitSGBBorder);
    // InitSGBBorder(); // Skip this since we can't be on SGB.

    // CALL(aInitSound);
    InitSound();
    // XOR_A_A;
    // LD_addr_A(wMapMusic);
    wram->wMapMusic = 0;
    // JP(mGameInit);
}

//  Wipe VRAM banks 0 and 1
void ClearVRAM(void) {
    // LD_A(1);
    // LDH_addr_A(rVBK);
    // ClearVRAM_clear_Conv();

    // XOR_A_A;  // 0
    // LDH_addr_A(rVBK);
    // ClearVRAM_clear_Conv();
    ByteFill(vram, sizeof(*vram), 0);
}

//  Wipe swappable WRAM banks (1-7)
//  Assumes CGB or AGB
void ClearWRAM(void) {
    // LD_A(1);
    uint8_t a = 1;

    do {
        // PUSH_AF;
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, a);

        // XOR_A_A;
        // LD_HL(WRAM1_Begin);
        // LD_BC(WRAM1_End - WRAM1_Begin);
        // CALL(aByteFill);
        ByteFill_GB(WRAM1_Begin, (WRAM1_End - WRAM1_Begin), 0);

        // POP_AF;
        // INC_A;
        // CP_A(8);
        // IF_NC goto bank_loop;  // Should be jr c
    } while(++a < 8);
}

//  Wipe the first 32 bytes of sScratch
void ClearsScratch(void) {
    // LD_A(BANK(sScratch));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asScratch));

    // LD_HL(sScratch);
    // LD_BC(0x20);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_GB(sScratch, 0x20, 0);

    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void Game_WarmStart(void) {
    Reset();
    Init();
}

void Game_ColdStart(void) {
    v_Start();
    Init();
}
