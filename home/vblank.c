#include "../constants.h"
#include "vblank.h"

//  VBlank is the interrupt responsible for updating VRAM.

//  In Pokemon Crystal, VBlank has been hijacked to act as the
//  main loop. After time-sensitive graphics operations have been
//  performed, joypad input and sound functions are executed.

//  This prevents the display and audio output from lagging.

void TransferVirtualOAM(void) {
    // initiate DMA
    LD_A(HIGH(wVirtualOAM));
    LDH_addr_A(rDMA);
    // wait for DMA to finish
    LD_A(NUM_SPRITE_OAM_STRUCTS);
wait:
    DEC_A;
    IF_NZ goto wait;
    return;
}

void VBlank(void) {
    PUSH_AF;
    PUSH_BC;
    PUSH_DE;
    PUSH_HL;

    LDH_A_addr(hVBlank);
    AND_A(7);

    /*
    LD_E_A;
    LD_D(0);
    LD_HL(mVBlank_VBlanks);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;

    CALL(av_hl_);
    */
    switch(REG_A)
    {
        case 7:
        case 0: CALL(aVBlank0); break;
        case 1: CALL(aVBlank1); break;
        case 2: CALL(aVBlank2); break;
        case 3: CALL(aVBlank3); break;
        case 4: CALL(aVBlank4); break;
        case 5: CALL(aVBlank5); break;
        case 6: CALL(aVBlank6); break;
    }

    CALL(aGameTimer);

    POP_HL;
    POP_DE;
    POP_BC;
    POP_AF;
    RET;

VBlanks:
        // dw ['VBlank0'];
    // dw ['VBlank1'];
    // dw ['VBlank2'];
    // dw ['VBlank3'];
    // dw ['VBlank4'];
    // dw ['VBlank5'];
    // dw ['VBlank6'];
    // dw ['VBlank0'];  // just in case

    return VBlank0();
}

void VBlank0(void) {
        //  normal operation

    //  rng
    //  scx, scy, wy, wx
    //  bg map buffer
    //  palettes
    //  dma transfer
    //  bg map
    //  tiles
    //  oam
    //  joypad
    //  sound

    // inc frame counter
    LD_HL(hVBlankCounter);
    INC_hl;

    // advance random variables
    LDH_A_addr(rDIV);
    LD_B_A;
    LDH_A_addr(hRandomAdd);
    ADC_A_B;
    LDH_addr_A(hRandomAdd);

    LDH_A_addr(rDIV);
    LD_B_A;
    LDH_A_addr(hRandomSub);
    SBC_A_B;
    LDH_addr_A(hRandomSub);

    LDH_A_addr(hROMBank);
    LDH_addr_A(hROMBankBackup);

    LDH_A_addr(hSCX);
    LDH_addr_A(rSCX);
    LDH_A_addr(hSCY);
    LDH_addr_A(rSCY);
    LDH_A_addr(hWY);
    LDH_addr_A(rWY);
    LDH_A_addr(hWX);
    LDH_addr_A(rWX);

    // There's only time to call one of these in one vblank.
    // Calls are in order of priority.

    CALL(aUpdateBGMapBuffer);
    IF_C goto done;
    CALL(aUpdatePalsIfCGB);
    IF_C goto done;
    CALL(aDMATransfer);
    IF_C goto done;
    CALL(aUpdateBGMap);

    // These have their own timing checks.

    CALL(aServe2bppRequest);
    CALL(aServe1bppRequest);
    CALL(aAnimateTileset);

done:
    
    LDH_A_addr(hOAMUpdate);
    AND_A_A;
    IF_NZ goto done_oam;
    TransferVirtualOAM();

done_oam:
    
    // vblank-sensitive operations are done

    XOR_A_A;
    LD_addr_A(wVBlankOccurred);

    LD_A_addr(wOverworldDelay);
    AND_A_A;
    IF_Z goto ok;
    DEC_A;
    LD_addr_A(wOverworldDelay);

ok:
    
    LD_A_addr(wTextDelayFrames);
    AND_A_A;
    IF_Z goto ok2;
    DEC_A;
    LD_addr_A(wTextDelayFrames);

ok2:
    
    CALL(aUpdateJoypad);

    LD_A(BANK(av_UpdateSound));
    RST(mBankswitch);
    CALL(av_UpdateSound);
    LDH_A_addr(hROMBankBackup);
    RST(mBankswitch);

    LDH_A_addr(hSeconds);
    LDH_addr_A(hUnusedBackup);

    RET;
}

void VBlank2(void) {
        //  sound only

    LDH_A_addr(hROMBank);
    LDH_addr_A(hROMBankBackup);

    LD_A(BANK(av_UpdateSound));
    RST(mBankswitch);
    CALL(av_UpdateSound);

    LDH_A_addr(hROMBankBackup);
    RST(mBankswitch);

    XOR_A_A;
    LD_addr_A(wVBlankOccurred);
    RET;
}

void VBlank1(void) {
        //  scx, scy
    //  palettes
    //  bg map
    //  tiles
    //  oam
    //  sound / lcd stat

    LDH_A_addr(hROMBank);
    LDH_addr_A(hROMBankBackup);

    LDH_A_addr(hSCX);
    LDH_addr_A(rSCX);
    LDH_A_addr(hSCY);
    LDH_addr_A(rSCY);

    CALL(aUpdatePals);
    IF_C goto done;

    CALL(aUpdateBGMap);
    CALL(aServe2bppRequest_VBlank);

    TransferVirtualOAM();

done:
        XOR_A_A;
    LD_addr_A(wVBlankOccurred);

    // get requested ints
    LDH_A_addr(rIF);
    LD_B_A;
    // discard requested ints
    XOR_A_A;
    LDH_addr_A(rIF);
    // enable lcd stat
    LD_A(1 << LCD_STAT);
    LDH_addr_A(rIE);
    // rerequest serial int if applicable (still disabled)
    // request lcd stat
    LD_A_B;
    AND_A(1 << SERIAL);
    OR_A(1 << LCD_STAT);
    LDH_addr_A(rIF);

    NOP;
    LD_A(BANK(av_UpdateSound));
    RST(mBankswitch);
    CALL(av_UpdateSound);
    LDH_A_addr(hROMBankBackup);
    RST(mBankswitch);
    NOP;

    // get requested ints
    LDH_A_addr(rIF);
    LD_B_A;
    // discard requested ints
    XOR_A_A;
    LDH_addr_A(rIF);
    // enable ints besides joypad
    LD_A(IE_DEFAULT);
    LDH_addr_A(rIE);
    // rerequest ints
    LD_A_B;
    LDH_addr_A(rIF);
    RET;
}

void UpdatePals(void) {
        //  update pals for either dmg or cgb

    LDH_A_addr(hCGB);
    AND_A_A;
    JP_NZ(mUpdateCGBPals);

    // update gb pals
    LD_A_addr(wBGP);
    LDH_addr_A(rBGP);
    LD_A_addr(wOBP0);
    LDH_addr_A(rOBP0);
    LD_A_addr(wOBP1);
    LDH_addr_A(rOBP1);

    AND_A_A;
    RET;
}

void VBlank3(void) {
        //  scx, scy
    //  palettes
    //  bg map
    //  tiles
    //  oam
    //  sound / lcd stat

    LDH_A_addr(hROMBank);
    LDH_addr_A(hROMBankBackup);

    LDH_A_addr(hSCX);
    LDH_addr_A(rSCX);
    LDH_A_addr(hSCY);
    LDH_addr_A(rSCY);

    LDH_A_addr(hCGBPalUpdate);
    AND_A_A;
    CALL_NZ(aForceUpdateCGBPals);
    IF_C goto done;

    CALL(aUpdateBGMap);
    CALL(aServe2bppRequest_VBlank);

    TransferVirtualOAM();

done:
    
    XOR_A_A;
    LD_addr_A(wVBlankOccurred);

    LDH_A_addr(rIF);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A(1 << LCD_STAT);
    LDH_addr_A(rIE);
    LDH_addr_A(rIF);

    NOP;
    LD_A(BANK(av_UpdateSound));
    RST(mBankswitch);
    CALL(av_UpdateSound);
    LDH_A_addr(hROMBankBackup);
    RST(mBankswitch);
    NOP;

    // request lcdstat
    LDH_A_addr(rIF);
    LD_B_A;
    // and any other ints
    POP_AF;
    OR_A_B;
    LD_B_A;
    // reset ints
    XOR_A_A;
    LDH_addr_A(rIF);
    // enable ints besides joypad
    LD_A(IE_DEFAULT);
    LDH_addr_A(rIE);
    // request ints
    LD_A_B;
    LDH_addr_A(rIF);
    RET;
}

void VBlank4(void) {
        //  bg map
    //  tiles
    //  oam
    //  joypad
    //  serial
    //  sound

    LDH_A_addr(hROMBank);
    LDH_addr_A(hROMBankBackup);

    CALL(aUpdateBGMap);
    CALL(aServe2bppRequest);

    CALL(0xff80);  // TransferVirtualOAM

    CALL(aUpdateJoypad);

    XOR_A_A;
    LD_addr_A(wVBlankOccurred);

    CALL(aAskSerial);

    LD_A(BANK(av_UpdateSound));
    RST(mBankswitch);
    CALL(av_UpdateSound);

    LDH_A_addr(hROMBankBackup);
    RST(mBankswitch);
    RET;
}

void VBlank5(void) {
        //  scx
    //  palettes
    //  bg map
    //  tiles
    //  joypad
    //

    LDH_A_addr(hROMBank);
    LDH_addr_A(hROMBankBackup);

    LDH_A_addr(hSCX);
    LDH_addr_A(rSCX);

    CALL(aUpdatePalsIfCGB);
    IF_C goto done;

    CALL(aUpdateBGMap);
    CALL(aServe2bppRequest);

done:
    
    XOR_A_A;
    LD_addr_A(wVBlankOccurred);

    CALL(aUpdateJoypad);

    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A(1 << LCD_STAT);
    LDH_addr_A(rIE);
    // request lcd stat
    LDH_addr_A(rIF);

    NOP;
    LD_A(BANK(av_UpdateSound));
    RST(mBankswitch);
    CALL(av_UpdateSound);
    LDH_A_addr(hROMBankBackup);
    RST(mBankswitch);
    NOP;

    XOR_A_A;
    LDH_addr_A(rIF);
    // enable ints besides joypad
    LD_A(IE_DEFAULT);
    LDH_addr_A(rIE);
    RET;
}

void VBlank6(void) {
        //  palettes
    //  tiles
    //  dma transfer
    //  sound

    LDH_A_addr(hROMBank);
    LDH_addr_A(hROMBankBackup);

    // inc frame counter
    LD_HL(hVBlankCounter);
    INC_hl;

    CALL(aUpdateCGBPals);
    IF_C goto done;

    CALL(aServe2bppRequest);
    CALL(aServe1bppRequest);
    CALL(aDMATransfer);

done:
    
    XOR_A_A;
    LD_addr_A(wVBlankOccurred);

    LD_A(BANK(av_UpdateSound));
    RST(mBankswitch);
    CALL(av_UpdateSound);

    LDH_A_addr(hROMBankBackup);
    RST(mBankswitch);
    RET;
}
