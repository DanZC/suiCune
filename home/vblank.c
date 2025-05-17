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
    CopyBytes(gb.oam, wram->wVirtualOAMSprite, sizeof(gb.oam));
    return;
}

static void VBlank0(void);
static void VBlank1(void);
static void VBlank2(void);
static void VBlank3(void);
static void VBlank4(void);
static void VBlank5(void);
static void VBlank6(void);

void VBlank(void)
{
    // SET_PC(aVBlank);
    // PUSH_AF;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;

    switch(hram.hVBlank & 7)
    {
        case 7:
        case 0: VBlank0(); break;
        case 1: VBlank1(); break;
        case 2: VBlank2(); break;
        case 3: VBlank3(); break;
        case 4: VBlank4(); break;
        case 5: VBlank5(); break;
        case 6: VBlank6(); break;
    }

    GameTimer();

    // POP_HL;
    // POP_DE;
    // POP_BC;
    // POP_AF;
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
static void VBlank0(void) {
    uint8_t temp, carry;

    // inc frame counter
    // LD_HL(hVBlankCounter);
    // INC_hl;
    hram.hVBlankCounter++;

    // advance random variables
    // LDH_A_addr(rDIV);
    // LD_B_A;
    // LDH_A_addr(hRandomAdd);
    // ADC_A_B;
    // LDH_addr_A(hRandomAdd);
    temp = gb_read(rDIV);
    carry = ((uint16_t)temp + (uint16_t)hram.hRandomAdd > 0xff)? 1: 0;
    hram.hRandomAdd = (temp + hram.hRandomAdd + REG_F_C) & 0xff;
    REG_F_C = carry;

    // LDH_A_addr(rDIV);
    // LD_B_A;
    // LDH_A_addr(hRandomSub);
    // SBC_A_B;
    // LDH_addr_A(hRandomSub);
    temp = gb_read(rDIV);
    carry = (temp > hram.hRandomSub)? 1: 0;
    hram.hRandomSub = (temp - hram.hRandomSub - REG_F_C) & 0xff;
    REG_F_C = carry;

    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hram.hROMBankBackup = hram.hROMBank;

    // LDH_A_addr(hSCX);
    // LDH_addr_A(rSCX);
    gb_write(rSCX, hram.hSCX);

    // LDH_A_addr(hSCY);
    // LDH_addr_A(rSCY);
    gb_write(rSCY, hram.hSCY);

    // LDH_A_addr(hWY);
    // LDH_addr_A(rWY);
    gb_write(rWY, hram.hWY);

    // LDH_A_addr(hWX);
    // LDH_addr_A(rWX);
    gb_write(rWX, hram.hWX);

    // There's only time to call one of these in one vblank.
    // Calls are in order of priority.

    do {
        // CALL(aUpdateBGMapBuffer);
        // IF_C goto done;
        if(UpdateBGMapBuffer()) break;

        // CALL(aUpdatePalsIfCGB);
        // IF_C goto done;
        if(UpdateCGBPals()) break;

        // CALL(aDMATransfer);
        // IF_C break;
        if(DMATransfer()) break;

        // CALL(aUpdateBGMap);
        UpdateBGMap();

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
    if(hram.hOAMUpdate == 0)
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
    UpdateJoypad();

    // LD_A(BANK(av_UpdateSound));
    // RST(mBankswitch);
    // CALL(av_UpdateSound);
    v_UpdateSound();
    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);

    // LDH_A_addr(hSeconds);
    // LDH_addr_A(hUnusedBackup);
    hram.hUnusedBackup = hram.hSeconds;
}

//  sound
static void VBlank2(void) {
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);

    // LD_A(BANK(av_UpdateSound));
    // RST(mBankswitch);
    // CALL(av_UpdateSound);
    v_UpdateSound();

    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);

    // XOR_A_A;
    // LD_addr_A(wVBlankOccurred);
    wram->wVBlankOccurred = 0;
    // RET;
}

//  scx, scy
//  palettes
//  bg map
//  tiles
//  oam
//  sound / lcd stat
static void VBlank1(void) {
    // CALL(aVBlank1);
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hram.hROMBankBackup = hram.hROMBank;

    // LDH_A_addr(hSCX);
    // LDH_addr_A(rSCX);
    // LDH_A_addr(hSCY);
    // LDH_addr_A(rSCY);
    gb_write(rSCX, hram.hSCX);
    gb_write(rSCY, hram.hSCY);

    // CALL(aUpdatePals);
    // IF_C goto done;
    if(!UpdatePals()) {
        // CALL(aUpdateBGMap);
        UpdateBGMap();
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
    // CALL(av_UpdateSound);
    v_UpdateSound();
    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);
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

//  update pals for either dmg or cgb
bool UpdatePals(void) {
    if(hram.hCGB != 0)
        return UpdateCGBPals();

    // update gb pals
    gb_write(rBGP, wram->wBGP);
    gb_write(rOBP0, wram->wOBP0);
    gb_write(rOBP1, wram->wOBP1);

    return false;
}

//  scx, scy
//  palettes
//  bg map
//  tiles
//  oam
//  sound / lcd stat
static void VBlank3(void) {
    // CALL(aVBlank3);
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hram.hROMBankBackup = hram.hROMBank;

    // LDH_A_addr(hSCX);
    // LDH_addr_A(rSCX);
    // LDH_A_addr(hSCY);
    // LDH_addr_A(rSCY);
    gb_write(rSCX, hram.hSCX);
    gb_write(rSCY, hram.hSCY);

    // LDH_A_addr(hCGBPalUpdate);
    // AND_A_A;
    // CALL_NZ(aForceUpdateCGBPals);
    // IF_C goto done;
    if(hram.hCGBPalUpdate == 0 || !ForceUpdateCGBPals()) {

        // CALL(aUpdateBGMap);
        UpdateBGMap();
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
    // CALL(av_UpdateSound);
    v_UpdateSound();
    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);
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

//  bg map
//  tiles
//  oam
//  joypad
//  serial
//  sound
static void VBlank4(void) {
    // CALL(aVBlank4);
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hram.hROMBankBackup = hram.hROMBank;

    // CALL(aUpdateBGMap);
    UpdateBGMap();
    // CALL(aServe2bppRequest);
    Serve2bppRequest();

    // CALL(0xff80);  // TransferVirtualOAM
    TransferVirtualOAM();  // TransferVirtualOAM

    // CALL(aUpdateJoypad);
    UpdateJoypad();

    // XOR_A_A;
    // LD_addr_A(wVBlankOccurred);
    wram->wVBlankOccurred = 0;

    // CALL(aAskSerial);

    // LD_A(BANK(av_UpdateSound));
    // RST(mBankswitch);
    // CALL(av_UpdateSound);
    v_UpdateSound();

    // LDH_A_addr(hROMBankBackup);
    // RST(mBankswitch);
    // RET;
}

//  scx
//  palettes
//  bg map
//  tiles
//  joypad
//
static void VBlank5(void) {
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hram.hROMBankBackup = hram.hROMBank;

    // LDH_A_addr(hSCX);
    // LDH_addr_A(rSCX);
    gb_write(rSCX, hram.hSCX);

    // CALL(aUpdatePalsIfCGB);
    // IF_C goto done;
    if(!UpdatePalsIfCGB()){
        // CALL(aUpdateBGMap);
        UpdateBGMap();
        // CALL(aServe2bppRequest);
        Serve2bppRequest();
    }

// done:    
    // XOR_A_A;
    // LD_addr_A(wVBlankOccurred);
    wram->wVBlankOccurred = FALSE;

    // CALL(aUpdateJoypad);
    UpdateJoypad();

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

//  palettes
//  tiles
//  dma transfer
//  sound
static void VBlank6(void) {
    // LDH_A_addr(hROMBank);
    // LDH_addr_A(hROMBankBackup);
    hram.hROMBankBackup = hram.hROMBank;

    // inc frame counter
    // LD_HL(hVBlankCounter);
    // INC_hl;
    hram.hVBlankCounter++;

    // CALL(aUpdateCGBPals);
    // IF_C goto done;
    if(!UpdateCGBPals()){
        // CALL(aServe2bppRequest);
        Serve2bppRequest();
        // CALL(aServe1bppRequest);
        Serve1bppRequest();
        // CALL(aDMATransfer);
        DMATransfer();
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
    // RET;
}
