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
    InitSound();
    hram->hMapAnims = 0;
    ClearPalettes_Conv();
    gb_write(rIF, 0);
    gb_write(rIE, 1 << VBLANK);
    bit_set(wram->wJoypadDisable, JOYPAD_DISABLE_SGB_TRANSFER_F);
    DelayFrames_Conv(32);
}

void v_Start(void) {
    hram->hCGB = (REG_A == 0x11) ? TRUE : FALSE;
    hram->hSystemBooted = TRUE;
}

void Init(void) {
    gb_write(rIF, 0);
    gb_write(rIE, 0);
    gb_write(rRP, 0);
    gb_write(rSCX, 0);
    gb_write(rSCY, 0);
    gb_write(rSB, 0);
    gb_write(rSC, 0);
    gb_write(rWX, 0);
    gb_write(rWY, 0);
    gb_write(rBGP, 0);
    gb_write(rOBP0, 0);
    gb_write(rOBP1, 0);
    gb_write(rTMA, 0);
    gb_write(rTAC, 0);
    wram->wBetaTitleSequenceOpeningType = 0;
    gb_write(rTAC, 0b100);
    gb_write(rLCDC, 0);
    ByteFill_Conv2(wram->wram0, sizeof(wram->wram0), 0);
    uint8_t cgb = hram->hCGB;
    uint8_t systemBooted = hram->hSystemBooted;
    ByteFill_Conv2(hram, sizeof(*hram), 0);
    hram->hSystemBooted = systemBooted;
    hram->hCGB = cgb;
    ClearWRAM();
    gb_write(rSVBK, 1);
    ClearVRAM();
    ClearSprites_Conv();
    ClearsScratch();
    hram->hMapAnims = 0;
    hram->hSCX = 0;
    hram->hSCY = 0;
    gb_write(rJOYP, 0);
    gb_write(rSTAT, 0x8);
    hram->hWY = 0x90;
    gb_write(rWY, 0x90);
    hram->hWX = 7;
    gb_write(rWX, 7);
    gb_write(rLCDC, LCDC_DEFAULT);
    hram->hSerialConnectionStatus = CONNECTION_NOT_ESTABLISHED;
    InitCGBPals_Conv();
    hram->hBGMapAddress = vBGMap1;
    StartClock_Conv();
    gb_write(MBC3LatchClock, 0);
    gb_write(MBC3SRamEnable, SRAM_DISABLE);
    gb_write(rIF, 0);
    gb_write(rIE, IE_DEFAULT);
    DelayFrame();
    InitSound();
    wram->wMapMusic = 0;
}

static void ClearVRAM_clear(void) {
    ByteFill_Conv(VRAM_Begin, (VRAM_End - VRAM_Begin), 0);
}
void ClearVRAM(void) {
    gb_write(rVBK, 1);
    ClearVRAM_clear();
    gb_write(rVBK, 0);
    ClearVRAM_clear();
}

void ClearWRAM(void) {
    uint8_t a = 1;

    do {
        gb_write(rSVBK, a);
        ByteFill_Conv(WRAM1_Begin, (WRAM1_End - WRAM1_Begin), 0);
    } while (++a < 8);
}

void ClearsScratch(void) {
    OpenSRAM_Conv(MBANK(asScratch));
    ByteFill_Conv(sScratch, 0x20, 0);
    CloseSRAM_Conv();
}

void Game_WarmStart(void) {
    Reset();
    Init();
}

void Game_ColdStart(void) {
    v_Start();
    Init();
}
