#include "../constants.h"
#include "init.h"

void Reset(void) {
        NOP;
    CALL(aInitSound);
    XOR_A_A;
    LDH_addr_A(hMapAnims);
    CALL(aClearPalettes);
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A(1 << VBLANK);
    LDH_addr_A(rIE);
    NOP;

    LD_HL(wJoypadDisable);
    SET_hl(JOYPAD_DISABLE_SGB_TRANSFER_F);

    LD_C(32);
    CALL(aDelayFrames);

    JR(mInit);
}

void v_Start(void) {
        CP_A(0x11);
    IF_Z goto cgb;
    XOR_A_A;  // FALSE
    goto load;

cgb:
        LD_A(TRUE);

load:
        LDH_addr_A(hCGB);
    LD_A(TRUE);
    LDH_addr_A(hSystemBooted);

    return Init();
}

void Init(void) {
        NOP;

    XOR_A_A;
    LDH_addr_A(rIF);
    LDH_addr_A(rIE);
    LDH_addr_A(rRP);
    LDH_addr_A(rSCX);
    LDH_addr_A(rSCY);
    LDH_addr_A(rSB);
    LDH_addr_A(rSC);
    LDH_addr_A(rWX);
    LDH_addr_A(rWY);
    LDH_addr_A(rBGP);
    LDH_addr_A(rOBP0);
    LDH_addr_A(rOBP1);
    LDH_addr_A(rTMA);
    LDH_addr_A(rTAC);
    LD_addr_A(wBetaTitleSequenceOpeningType);

    LD_A(0b100);  // Start timer at 4096Hz
    LDH_addr_A(rTAC);

wait:
        LDH_A_addr(rLY);
    CP_A(LY_VBLANK + 1);
    IF_NZ goto wait;

    XOR_A_A;
    LDH_addr_A(rLCDC);

    //  Clear WRAM bank 0
    LD_HL(WRAM0_Begin);
    LD_BC(WRAM0_End - WRAM0_Begin);

ByteFill:
        LD_hl(0);
    INC_HL;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto ByteFill;

    LD_SP(wStackTop);

    //  Clear HRAM
    LDH_A_addr(hCGB);
    PUSH_AF;
    LDH_A_addr(hSystemBooted);
    PUSH_AF;
    XOR_A_A;
    LD_HL(HRAM_Begin);
    LD_BC(HRAM_End - HRAM_Begin);
    CALL(aByteFill);
    POP_AF;
    LDH_addr_A(hSystemBooted);
    POP_AF;
    LDH_addr_A(hCGB);

    CALL(aClearWRAM);
    LD_A(1);
    LDH_addr_A(rSVBK);
    CALL(aClearVRAM);
    CALL(aClearSprites);
    CALL(aClearsScratch);

    LD_A(BANK(aWriteOAMDMACodeToHRAM));  // aka BANK(GameInit)
    RST(aBankswitch);

    CALL(aWriteOAMDMACodeToHRAM);

    XOR_A_A;
    LDH_addr_A(hMapAnims);
    LDH_addr_A(hSCX);
    LDH_addr_A(hSCY);
    LDH_addr_A(rJOYP);

    LD_A(0x8);  // HBlank int enable
    LDH_addr_A(rSTAT);

    LD_A(0x90);
    LDH_addr_A(hWY);
    LDH_addr_A(rWY);

    LD_A(7);
    LDH_addr_A(hWX);
    LDH_addr_A(rWX);

    LD_A(LCDC_DEFAULT);  // %11100011
                         // LCD on
                         // Win tilemap 1
                         // Win on
                         // BG/Win tiledata 0
                         // BG Tilemap 0
                         // OBJ 8x8
                         // OBJ on
                         // BG on
    LDH_addr_A(rLCDC);

    LD_A(CONNECTION_NOT_ESTABLISHED);
    LDH_addr_A(hSerialConnectionStatus);

    FARCALL(aInitCGBPals);

    LD_A(HIGH(vBGMap1));
    LDH_addr_A(hBGMapAddress + 1);
    XOR_A_A;  // LOW(vBGMap1)
    LDH_addr_A(hBGMapAddress);

    FARCALL(aStartClock);

    XOR_A_A;  // SRAM_DISABLE
    LD_addr_A(MBC3LatchClock);
    LD_addr_A(MBC3SRamEnable);

    LDH_A_addr(hCGB);
    AND_A_A;
    IF_Z goto no_double_speed;
    CALL(aNormalSpeed);

no_double_speed:
    
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A(IE_DEFAULT);
    LDH_addr_A(rIE);
    NOP;

    CALL(aDelayFrame);

    PREDEF(pInitSGBBorder);

    CALL(aInitSound);
    XOR_A_A;
    LD_addr_A(wMapMusic);
    JP(mGameInit);
}

void ClearVRAM(void) {
        //  Wipe VRAM banks 0 and 1

    LD_A(1);
    LDH_addr_A(rVBK);
    CALL(aClearVRAM_clear);

    XOR_A_A;  // 0
    LDH_addr_A(rVBK);

clear:
        LD_HL(VRAM_Begin);
    LD_BC(VRAM_End - VRAM_Begin);
    XOR_A_A;
    CALL(aByteFill);
    RET;
}

void ClearWRAM(void) {
        //  Wipe swappable WRAM banks (1-7)
    //  Assumes CGB or AGB

    LD_A(1);

bank_loop:
        PUSH_AF;
    LDH_addr_A(rSVBK);
    XOR_A_A;
    LD_HL(WRAM1_Begin);
    LD_BC(WRAM1_End - WRAM1_Begin);
    CALL(aByteFill);
    POP_AF;
    INC_A;
    CP_A(8);
    IF_NC goto bank_loop;  // Should be jr c
    RET;
}

void ClearsScratch(void) {
        //  Wipe the first 32 bytes of sScratch

    LD_A(BANK(sScratch));
    CALL(aOpenSRAM);
    LD_HL(sScratch);
    LD_BC(0x20);
    XOR_A_A;
    CALL(aByteFill);
    CALL(aCloseSRAM);
    RET;
}
