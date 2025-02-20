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
    hMapAnims = 0;
    ClearPalettes_Conv();
    gb_write(rIF, 0);
    gb_write(rIE, 1 << VBLANK);
    bit_set(wram->wJoypadDisable, JOYPAD_DISABLE_SGB_TRANSFER_F);
    DelayFrames_Conv(32);
}

void v_Start(void) {
    hCGB = (REG_A == 0x11) ? TRUE : FALSE;
    hSystemBooted = TRUE;
}

void FillHRam(void) {
    hROMBankBackup = 0;
    hFarByte = 0;
    hTempBank = 0;
    hSRAMBank = 0;
    hRTCDayHi = 0;
    hRTCDayLo = 0;
    hRTCHours = 0;
    hRTCMinutes = 0;
    hRTCSeconds = 0;
    hHours = 0;
    hMinutes = 0;
    hSeconds = 0;
    hVBlankCounter = 0;
    hROMBank = 0;
    hVBlank = 0;
    hMapEntryMethod = 0;
    hMenuReturn = 0;
    hUnusedByte = 0;
    hJoypadReleased = 0;
    hJoypadPressed = 0;
    hJoypadDown = 0;
    hJoypadSum = 0;
    hJoyReleased = 0;
    hJoyPressed = 0;
    hJoyDown = 0;
    hJoyLast = 0;
    hInMenu = 0;
    hPrinter = 0;
    hGraphicStartTile = 0;
    hMoveMon = 0;
    hMapObjectIndex = 0;
    hObjectStructIndex = 0;
    hConnectionStripLength = 0;
    hConnectedMapWidth = 0;
    hEnemyMonSpeed = 0;
    uint8_t hMultiplicand[3] = { 0 };
    hMultiplier = 0;
    hProduct = 0;
    hDividend = 0;
    hDivisor = 0;
    hQuotient = 0;
    hRemainder = 0;
    uint8_t hMathBuffer = 0;
    uint8_t hPrintNumBuffer = 0;
    hMGExchangedByte = 0;
    hMGExchangedWord = 0;
    hMGNumBits = 0;
    hMGChecksum = 0;
    hMGUnusedMsgLength = 0;
    hMGRole = 0;
    hMGStatusFlags = 0;
    hUsedSpriteIndex = 0;
    hUsedSpriteTile = 0;
    hCurSpriteXCoord = 0;
    hCurSpriteYCoord = 0;
    hCurSpriteXPixel = 0;
    hCurSpriteYPixel = 0;
    hCurSpriteTile = 0;
    hCurSpriteOAMFlags = 0;
    uint8_t hMoneyTemp = 0;
    hMGJoypadPressed = 0;
    hMGJoypadReleased = 0;
    hMGPrevTIMA = 0;
    hLCDCPointer = 0;
    hLYOverrideStart = 0;
    hLYOverrideEnd = 0;
    hMobileReceive = 0;
    hSerialReceivedNewData = 0;
    hSerialConnectionStatus = 0;
    hSerialIgnoringInitialData = 0;
    hSerialSend = 0;
    hSerialReceive = 0;
    hSCX = 0;
    hSCY = 0;
    hWX = 0;
    hWY = 0;
    hTilesPerCycle = 0;
    hBGMapMode = 0;
    hBGMapThird = 0;
    hBGMapAddress = 0;
    hOAMUpdate = 0;
    hSPBuffer = 0;
    hBGMapUpdate = 0;
    hBGMapTileCount = 0;
    hMapAnims = 0;
    hTileAnimFrame = 0;
    hLastTalked = 0;
    hRandomAdd = 0;
    hRandomSub = 0;
    hUnusedBackup = 0;
    hBattleTurn = 0;
    hCGBPalUpdate = 0;
    hCGB = 0;
    hSGB = 0;
    hDMATransfer = 0;
    hMobile = 0;
    hSystemBooted = 0;
    hClockResetTrigger = 0;
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
    uint8_t cgb = hCGB;
    uint8_t systemBooted = hSystemBooted;
    //ByteFill_Conv2(hram, sizeof(*hram), 0);
	FillHRam();
    hSystemBooted = systemBooted;
    hCGB = cgb;
    ClearWRAM();
    gb_write(rSVBK, 1);
    ClearVRAM();
    ClearSprites_Conv();
    ClearsScratch();
    hMapAnims = 0;
    hSCX = 0;
    hSCY = 0;
    gb_write(rJOYP, 0);
    gb_write(rSTAT, 0x8);
    hWY = 0x90;
    gb_write(rWY, 0x90);
    hWX = 7;
    gb_write(rWX, 7);
    gb_write(rLCDC, LCDC_DEFAULT);
    hSerialConnectionStatus = CONNECTION_NOT_ESTABLISHED;
    InitCGBPals_Conv();
    hBGMapAddress = vBGMap1;
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
