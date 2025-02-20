#include "../constants.h"
#include "vblank.h"
#include "game_time.h"
#include "joypad.h"
#include "palettes.h"
#include "video.h"
#include "copy.h"
#include "../audio/engine.h"

//  VBlank is the interrupt responsible for updating VRAM.

//  In Pokemon Crystal, VBlank has been hijacked to act as the
//  main loop. After time-sensitive graphics operations have been
//  performed, joypad input and sound functions are executed.

//  This prevents the display and audio output from lagging.

void TransferVirtualOAM(void) {
    // initiate DMA
    // LD_A(HIGH(wVirtualOAM));
    // LDH_addr_A(rDMA);
    // wait for DMA to finish
    // LD_A(NUM_SPRITE_OAM_STRUCTS);
// wait:
    // DEC_A;
    // IF_NZ goto wait;
    CopyBytes_Conv2(gb.oam, wram->wVirtualOAMSprite, sizeof(gb.oam));
    return;
}

void VBlank1_Conv(void);
void VBlank2_Conv(void);
void VBlank3_Conv(void);
void VBlank4_Conv(void);
void VBlank5_Conv(void);
void VBlank6_Conv(void);

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

void VBlank_Conv(void)
{
    SET_PC(aVBlank);
    // PUSH_AF;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;
    struct cpu_registers_s reg = gb.cpu_reg;

    switch(hVBlank & 7)
    {
        case 7:
        case 0: VBlank0_Conv(); break;
        case 1: VBlank1_Conv(); break;
        case 2: VBlank2_Conv(); break;
        case 3: VBlank3_Conv(); break;
        case 4: VBlank4_Conv(); break;
        case 5: VBlank5_Conv(); break;
        case 6: VBlank6_Conv(); break;
    }

    GameTimer_Conv();

    // POP_HL;
    // POP_DE;
    // POP_BC;
    // POP_AF;
    gb.cpu_reg = reg;
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
void VBlank0_Conv(void) {
    uint8_t temp, carry;

    // inc frame counter
    // LD_HL(hVBlankCounter);
    // INC_hl;
    // (hVBlankCounter, (hVBlankCounter) + 1);
    hVBlankCounter++;

    // advance random variables
    // LDH_A_addr(rDIV);
    // LD_B_A;
    // LDH_A_addr(hRandomAdd);
    // ADC_A_B;
    // LDH_addr_A(hRandomAdd);
    temp = gb_read(rDIV);
    carry = ((uint16_t)temp + (uint16_t)hRandomAdd > 0xff)? 1: 0;
    hRandomAdd = (temp + hRandomAdd + REG_F_C) & 0xff;
    REG_F_C = carry;

    // LDH_A_addr(rDIV);
    // LD_B_A;
    // LDH_A_addr(hRandomSub);
    // SBC_A_B;
    // LDH_addr_A(hRandomSub);
    temp = gb_read(rDIV);
    carry = (temp > hRandomSub)? 1: 0;
    hRandomSub = (temp - hRandomSub - REG_F_C) & 0xff;
    // (hRandomSub, (temp - (hRandomSub) - REG_F_C) & 0xff);
    REG_F_C = carry;

    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hROMBankBackup = hROMBank;

    // LDH_A_addr(hSCX);
    // LDH_addr_A(rSCX);
    gb_write(rSCX, hSCX);

    // LDH_A_addr(hSCY);
    // LDH_addr_A(rSCY);
    gb_write(rSCY, hSCY);

    // LDH_A_addr(hWY);
    // LDH_addr_A(rWY);
    gb_write(rWY, hWY);

    // LDH_A_addr(hWX);
    // LDH_addr_A(rWX);
    gb_write(rWX, hWX);

    // There's only time to call one of these in one vblank.
    // Calls are in order of priority.

    do {
        // CALL(aUpdateBGMapBuffer);
        // IF_C goto done;
        if(UpdateBGMapBuffer_Conv()) break;

        // CALL(aUpdatePalsIfCGB);
        // IF_C goto done;
        if(UpdateCGBPals_Conv()) break;

        // CALL(aDMATransfer);
        // IF_C break;
        if(DMATransfer_Conv()) break;

        // CALL(aUpdateBGMap);
        UpdateBGMap_Conv();

        // These have their own timing checks.

        // CALL(aServe2bppRequest);
        Serve2bppRequest();
        // CALL(aServe1bppRequest);
        Serve1bppRequest();
        // CALL(aAnimateTileset);
        AnimateTileset();
    } while(0);
done:
    
    // LDH_A_addr(hOAMUpdate);
    // AND_A_A;
    // IF_NZ goto done_oam;
    if(hOAMUpdate == 0)
        TransferVirtualOAM();
    
    // vblank-sensitive operations are done

    // XOR_A_A;
    // LD_addr_A(wVBlankOccurred);
    // gb_write(wVBlankOccurred, 0);
    wram->wVBlankOccurred = 0;

    // LD_A_addr(wOverworldDelay);
    // AND_A_A;
    // IF_Z goto ok;
    // delay = gb_read(wOverworldDelay);
    if(wram->wOverworldDelay != 0) {
        // DEC_A;
        // LD_addr_A(wOverworldDelay);
        // gb_write(wOverworldDelay, delay - 1);
        wram->wOverworldDelay--;
    }
    
    // LD_A_addr(wTextDelayFrames);
    // AND_A_A;
    // IF_Z goto ok2;
    // delay = gb_read(wTextDelayFrames);
    if(wram->wTextDelayFrames != 0) {
        // DEC_A;
        // LD_addr_A(wTextDelayFrames);
        wram->wTextDelayFrames--;
        // gb_write(wTextDelayFrames, delay - 1);
    }
    
    // CALL(aUpdateJoypad);
    UpdateJoypad_Conv();

    // LD_A(BANK(av_UpdateSound));
    // RST(mBankswitch);
    Bankswitch_Conv(BANK(av_UpdateSound));
    // CALL(av_UpdateSound);
    v_UpdateSound();
    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);
    Bankswitch_Conv(hROMBankBackup);

    // LDH_A_addr(hSeconds);
    // LDH_addr_A(hUnusedBackup);
    hUnusedBackup = hSeconds;
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

void VBlank2_Conv(void) {
    hROMBankBackup = hROMBank;
    Bankswitch_Conv(BANK(av_UpdateSound));
    // CALL(av_UpdateSound);
    v_UpdateSound();
    Bankswitch_Conv(hROMBankBackup);
    wram->wVBlankOccurred = 0;
    // CALL(aVBlank2);
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

//  scx, scy
//  palettes
//  bg map
//  tiles
//  oam
//  sound / lcd stat
void VBlank1_Conv(void) {
    // CALL(aVBlank1);
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hROMBankBackup = hROMBank;

    // LDH_A_addr(hSCX);
    // LDH_addr_A(rSCX);
    // LDH_A_addr(hSCY);
    // LDH_addr_A(rSCY);
    gb_write(rSCX, hSCX);
    gb_write(rSCY, hSCY);

    // CALL(aUpdatePals);
    // IF_C goto done;
    if(!UpdatePals_Conv()) {

        // CALL(aUpdateBGMap);
        UpdateBGMap_Conv();
        // CALL(aServe2bppRequest_VBlank);
        Serve2bppRequest_VBlank();

        TransferVirtualOAM();
    }

// done:
    //     XOR_A_A;
    // LD_addr_A(wVBlankOccurred);
    wram->wVBlankOccurred = 0;

    // get requested ints
    // LDH_A_addr(rIF);
    // LD_B_A;
    uint8_t b = gb_read(rIF);
    // discard requested ints
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // enable lcd stat
    // LD_A(1 << LCD_STAT);
    // LDH_addr_A(rIE);
    gb_write(rIE, 1 << LCD_STAT);
    // rerequest serial int if applicable (still disabled)
    // request lcd stat
    // LD_A_B;
    // AND_A(1 << SERIAL);
    // OR_A(1 << LCD_STAT);
    // LDH_addr_A(rIF);
    gb_write(rIF, (b & (1 << SERIAL)) | (1 << LCD_STAT));

    // NOP;
    // LD_A(BANK(av_UpdateSound));
    // RST(mBankswitch);
    Bankswitch_Conv(BANK(av_UpdateSound));
    // CALL(av_UpdateSound);
    v_UpdateSound();
    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);
    Bankswitch_Conv(hROMBankBackup);
    // NOP;

    // get requested ints
    // LDH_A_addr(rIF);
    // LD_B_A;
    b = gb_read(rIF);
    // discard requested ints
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // enable ints besides joypad
    // LD_A(IE_DEFAULT);
    // LDH_addr_A(rIE);
    gb_write(rIE, IE_DEFAULT);
    // rerequest ints
    // LD_A_B;
    // LDH_addr_A(rIF);
    gb_write(rIF, b);
    // RET;
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

//  update pals for either dmg or cgb
bool UpdatePals_Conv(void) {
    if(hCGB != 0)
        return UpdateCGBPals_Conv();

    // update gb pals
    gb_write(rBGP, wram->wBGP);
    gb_write(rOBP0, wram->wOBP0);
    gb_write(rOBP1, wram->wOBP1);

    return false;
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

//  scx, scy
//  palettes
//  bg map
//  tiles
//  oam
//  sound / lcd stat
void VBlank3_Conv(void) {
    // CALL(aVBlank3);
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hROMBankBackup = hROMBank;

    // LDH_A_addr(hSCX);
    // LDH_addr_A(rSCX);
    // LDH_A_addr(hSCY);
    // LDH_addr_A(rSCY);
    gb_write(rSCX, hSCX);
    gb_write(rSCY, hSCY);

    // LDH_A_addr(hCGBPalUpdate);
    // AND_A_A;
    // CALL_NZ(aForceUpdateCGBPals);
    // IF_C goto done;
    if(hCGBPalUpdate == 0 || !ForceUpdateCGBPals_Conv()) {

        // CALL(aUpdateBGMap);
        UpdateBGMap_Conv();
        // CALL(aServe2bppRequest_VBlank);
        Serve2bppRequest_VBlank();

        TransferVirtualOAM();
    }
// done:
    
    // XOR_A_A;
    // LD_addr_A(wVBlankOccurred);
    wram->wVBlankOccurred = 0;

    // LDH_A_addr(rIF);
    // PUSH_AF;
    uint8_t i_f = gb_read(rIF);
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // LD_A(1 << LCD_STAT);
    // LDH_addr_A(rIE);
    gb_write(rIE, 1 << LCD_STAT);
    // LDH_addr_A(rIF);
    gb_write(rIF, 1 << LCD_STAT);

    // NOP;
    // LD_A(BANK(av_UpdateSound));
    // RST(mBankswitch);
    Bankswitch_Conv(BANK(av_UpdateSound));
    // CALL(av_UpdateSound);
    v_UpdateSound();
    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);
    Bankswitch_Conv(hROMBankBackup);
    // NOP;

    // request lcdstat
    // LDH_A_addr(rIF);
    // LD_B_A;
    // and any other ints
    // POP_AF;
    // OR_A_B;
    // LD_B_A;
    uint8_t b = gb_read(rIF) | i_f;
    // reset ints
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // enable ints besides joypad
    // LD_A(IE_DEFAULT);
    // LDH_addr_A(rIE);
    gb_write(rIE, IE_DEFAULT);
    // request ints
    // LD_A_B;
    // LDH_addr_A(rIF);
    gb_write(rIF, b);
    // RET;
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

    // CALL(0xff80);  // TransferVirtualOAM
    TransferVirtualOAM();

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

//  bg map
//  tiles
//  oam
//  joypad
//  serial
//  sound
void VBlank4_Conv(void) {
    // CALL(aVBlank4);
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hROMBankBackup = hROMBank;

    // CALL(aUpdateBGMap);
    UpdateBGMap_Conv();
    // CALL(aServe2bppRequest);
    Serve2bppRequest();

    TransferVirtualOAM();  // TransferVirtualOAM

    // CALL(aUpdateJoypad);
    UpdateJoypad_Conv();

    // XOR_A_A;
    // LD_addr_A(wVBlankOccurred);
    wram->wVBlankOccurred = 0;

    // CALL(aAskSerial);

    // LD_A(BANK(av_UpdateSound));
    // RST(mBankswitch);
    // CALL(av_UpdateSound);
    Bankswitch_Conv(BANK(av_UpdateSound));
    // CALL(av_UpdateSound);
    v_UpdateSound();

    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);
    Bankswitch_Conv(hROMBankBackup);
    // RET;
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

//  scx
//  palettes
//  bg map
//  tiles
//  joypad
//
void VBlank5_Conv(void) {
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hROMBankBackup = hROMBank;

    // LDH_A_addr(hSCX);
    // LDH_addr_A(rSCX);
    gb_write(rSCX, hSCX);

    // CALL(aUpdatePalsIfCGB);
    // IF_C goto done;
    if(!UpdatePalsIfCGB_Conv()){
        // CALL(aUpdateBGMap);
        UpdateBGMap_Conv();
        // CALL(aServe2bppRequest);
        Serve2bppRequest();
    }

// done:    
    // XOR_A_A;
    // LD_addr_A(wVBlankOccurred);
    wram->wVBlankOccurred = FALSE;

    // CALL(aUpdateJoypad);
    UpdateJoypad_Conv();

    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0x0);
    // LD_A(1 << LCD_STAT);
    // LDH_addr_A(rIE);
    gb_write(rIE, 1 << LCD_STAT);
    // request lcd stat
    // LDH_addr_A(rIF);
    gb_write(rIF, 1 << LCD_STAT);

    // NOP;
    // LD_A(BANK(av_UpdateSound));
    // RST(mBankswitch);
    // CALL(av_UpdateSound);
    v_UpdateSound();
    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);
    Bankswitch_Conv(hROMBankBackup);
    // NOP;

    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0x0);
    // enable ints besides joypad
    // LD_A(IE_DEFAULT);
    // LDH_addr_A(rIE);
    gb_write(rIE, IE_DEFAULT);
    // RET;
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

//  palettes
//  tiles
//  dma transfer
//  sound
void VBlank6_Conv(void) {
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hROMBankBackup = hROMBank;

    // inc frame counter
    // LD_HL(hVBlankCounter);
    // INC_hl;
    hVBlankCounter++;

    // CALL(aUpdateCGBPals);
    // IF_C goto done;
    if(!UpdateCGBPals_Conv()){
        // CALL(aServe2bppRequest);
        Serve2bppRequest();
        // CALL(aServe1bppRequest);
        Serve1bppRequest();
        // CALL(aDMATransfer);
        DMATransfer_Conv();
    }

// done:
    // XOR_A_A;
    // LD_addr_A(wVBlankOccurred);
    wram->wVBlankOccurred = 0x0;

    // LD_A(BANK(av_UpdateSound));
    // RST(mBankswitch);
    // CALL(av_UpdateSound);
    v_UpdateSound();

    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);
    Bankswitch_Conv(hROMBankBackup);
    // RET;
}
