#include "../../constants.h"
#include "printer.h"
#include "print_party.h"
#include "../../home/audio.h"
#include "../../home/copy.h"
#include "../../home/map.h"
#include "../../home/delay.h"
#include "../../home/text.h"
#include "../../home/palettes.h"
#include "../../home/joypad.h"
#include "../../home/names.h"
#include "../../home/sram.h"
#include "../../home/pokemon.h"
#include "../../home/copy_tilemap.h"
#include "../pokemon/mon_stats.h"
#include "../events/diploma.h"
#include "../events/print_unown.h"
#include "../../gfx/misc.h"
#include "../../util/printer.h"

bool SendScreenToPrinter(void){
    uint8_t frames = 30;
    do {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // CALL(aCheckCancelPrint);
        // IF_C goto cancel;
        if(CheckCancelPrint()) {
        // cancel:
            // SCF;
            // RET;
            return true;
        }
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto finished;
        // CALL(aPrinterJumptableIteration);
        // CALL(aCheckPrinterStatus);
        wram->wPrinterStatus = 0x3;
        // CALL(aPlacePrinterStatusString);
        PlacePrinterStatusString();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    } while(--frames != 0);

    Printer_AppendTilemap(wram->wPrinterTilemapBuffer, wram->wAttrmap, wram->wPrinterQueueLength * 2);


// finished:
    // AND_A_A;
    // RET;
    return false;
}

void Printer_CleanUpAfterSend(void){
    // XOR_A_A;
    // LD_addr_A(wPrinterConnectionOpen);
    wram->wPrinterConnectionOpen = FALSE;
    // LD_addr_A(wPrinterOpcode);
    wram->wPrinterOpcode = 0x0;
    // RET;
}

void Printer_PrepareTilemapForPrint(uint8_t margins){
    // PUSH_AF;
    // CALL(aPrinter_StartTransmission);
    // POP_AF;
    // LD_addr_A(wPrinterMargins);
    wram->wPrinterMargins = margins;
    // CALL(aPrinter_CopyTilemapToBuffer);
    Printer_CopyTilemapToBuffer();
    // RET;
}

void Printer_ExitPrinter(void){
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // CALL(aPrinter_RestartMapMusic);
    Printer_RestartMapMusic();
    // RET;
}

void PrintDexEntry(void){
    // LD_A_addr(wPrinterQueueLength);
    // PUSH_AF;
    uint8_t queueLength = wram->wPrinterQueueLength;

    // LD_HL(vTiles1);
    // LD_DE(mFontInversed);
    // LD_BC((BANK(aFontInversed) << 8) | 0x80);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles1, FontInversed, 0, 0x80);

    // XOR_A_A;
    // LDH_addr_A(hPrinter);
    hram->hPrinter = 0x0;
    // CALL(aPrinter_PlayMusic);
    Printer_PlayMusic();

    // LDH_A_addr(rIE);
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(rIF);
    // LD_A((1 << SERIAL) | (1 << VBLANK));
    // LDH_addr_A(rIE);

    // CALL(aPrinter_StartTransmission);
    Printer_Begin();
    // LD_A((1 << 4) | 0);
    // LD_addr_A(wPrinterMargins);
    wram->wPrinterMargins = (1 << 4) | 0;
    // FARCALL(aPrintPage1);
    PrintPage1();
    // CALL(aClearTilemap);
    ClearTilemap();
    // LD_A(0b11100100);
    // CALL(aDmgToCgbBGPals);
    DmgToCgbBGPals_Conv(0b11100100);
    // CALL(aDelayFrame);
    DelayFrame();

    // LD_HL(hVBlank);
    // LD_A_hl;
    // PUSH_AF;
    // LD_hl(4);  // vblank mode that calls AskSerial

    // LD_A(8);  // 16 rows
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = 16 / 2;
    // CALL(aPrinter_ResetJoypadRegisters);
    Printer_ResetJoypadRegisters();
    // CALL(aSendScreenToPrinter);
    // IF_C goto skip_second_page;  // canceled or got an error
    if(!SendScreenToPrinter()) {
        // CALL(aPrinter_CleanUpAfterSend);
        Printer_CleanUpAfterSend();
        // LD_C(12);
        // CALL(aDelayFrames);
        DelayFrames(12);
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aPrinter_StartTransmission);
        // LD_A((0 << 4) | 3);
        // LD_addr_A(wPrinterMargins);
        wram->wPrinterMargins = (0 << 4) | 3;
        // FARCALL(aPrintPage2);
        PrintPage2();
        // CALL(aPrinter_ResetJoypadRegisters);
        Printer_ResetJoypadRegisters();
        // LD_A(4);
        // LD_addr_A(wPrinterQueueLength);
        wram->wPrinterQueueLength = 8 / 2;
        // CALL(aSendScreenToPrinter);
        if(!SendScreenToPrinter())
            Printer_SaveToDisk();
    }

// skip_second_page:
    // POP_AF;
    // LDH_addr_A(hVBlank);
    // CALL(aPrinter_CleanUpAfterSend);
    Printer_CleanUpAfterSend();
    Printer_CleanUp();

    // XOR_A_A;
    // LDH_addr_A(rIF);
    // POP_AF;
    // LDH_addr_A(rIE);

    // CALL(aPrinter_ExitPrinter);
    Printer_ExitPrinter();
    // LD_C(8);
    uint8_t c = 8;

    do {
    // low_volume_delay_frames:
        // CALL(aLowVolume);
        LowVolume();
        // CALL(aDelayFrame);
        DelayFrame();
        // DEC_C;
        // IF_NZ goto low_volume_delay_frames;
    } while(--c != 0);

    // POP_AF;
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = queueLength;
    // RET;
}

void PrintPCBox(uint32_t de, uint8_t c){
    // LD_A_addr(wPrinterQueueLength);
    // PUSH_AF;
    uint8_t queueLength = wram->wPrinterQueueLength;
    // LD_A(18 / 2);
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = 18 / 2;

    // LD_A_E;
    // LD_addr_A(wAddrOfBoxToPrint);
    // LD_A_D;
    // LD_addr_A(wAddrOfBoxToPrint + 1);
    wram->wAddrOfBoxToPrint = (de & 0xffff);
    // LD_A_B;
    // LD_addr_A(wBankOfBoxToPrint);
    wram->wBankOfBoxToPrint = MBANK(de);
    // LD_A_C;
    // LD_addr_A(wWhichBoxToPrint);
    wram->wWhichBoxToPrint = c;

    // XOR_A_A;
    // LDH_addr_A(hPrinter);
    hram->hPrinter = 0;
    // LD_addr_A(wFinishedPrintingBox);
    wram->wFinishedPrintingBox = 0;
    // CALL(aPrinter_PlayMusic);
    Printer_PlayMusic();

    // LDH_A_addr(rIE);
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(rIF);
    // LD_A((1 << SERIAL) | (1 << VBLANK));
    // LDH_addr_A(rIE);

    // LD_HL(hVBlank);
    // LD_A_hl;
    // PUSH_AF;
    // LD_hl(4);  // vblank mode that calls AskSerial
    Printer_Begin();

    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aPrintPCBox_Page1);
    PrintPCBox_Page1();
    // LD_A((1 << 4) | 0);  // to be loaded to wPrinterMargins
    // CALL(aPrinter_PrepareTilemapForPrint);
    Printer_PrepareTilemapForPrint((1 << 4) | 0);
    // CALL(aPrinter_ResetRegistersAndStartDataSend);
    // IF_C goto cancel;
    if(!Printer_ResetRegistersAndStartDataSend()) {
        // CALL(aPrinter_CleanUpAfterSend);
        Printer_CleanUpAfterSend();
        // LD_C(12);
        // CALL(aDelayFrames);
        DelayFrames(12);
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // CALL(aPrintPCBox_Page2);
        PrintPCBox_Page2();
        // LD_A((0 << 4) | 0);  // to be loaded to wPrinterMargins
        // CALL(aPrinter_PrepareTilemapForPrint);
        Printer_PrepareTilemapForPrint((0 << 4) | 0);
        // CALL(aPrinter_ResetRegistersAndStartDataSend);
        // IF_C goto cancel;
        if(!Printer_ResetRegistersAndStartDataSend()) {
            // CALL(aPrinter_CleanUpAfterSend);
            Printer_CleanUpAfterSend();
            // LD_C(12);
            // CALL(aDelayFrames);
            DelayFrames(12);

            // XOR_A_A;
            // LDH_addr_A(hBGMapMode);
            hram->hBGMapMode = BGMAPMODE_NONE;
            // CALL(aPrintPCBox_Page3);
            PrintPCBox_Page3();
            // LD_A((0 << 4) | 0);  // to be loaded to wPrinterMargins
            // CALL(aPrinter_PrepareTilemapForPrint);
            Printer_PrepareTilemapForPrint((0 << 4) | 0);
            // CALL(aPrinter_ResetRegistersAndStartDataSend);
            // IF_C goto cancel;
            if(!Printer_ResetRegistersAndStartDataSend()) {
                // CALL(aPrinter_CleanUpAfterSend);
                Printer_CleanUpAfterSend();
                // LD_C(12);
                // CALL(aDelayFrames);
                DelayFrames(12);

                // XOR_A_A;
                // LDH_addr_A(hBGMapMode);
                hram->hBGMapMode = BGMAPMODE_NONE;
                // CALL(aPrintPCBox_Page4);
                PrintPCBox_Page4();
                // LD_A((0 << 4) | 3);  // to be loaded to wPrinterMargins
                // CALL(aPrinter_PrepareTilemapForPrint);
                Printer_PrepareTilemapForPrint((0 << 4) | 3);
                // CALL(aPrinter_ResetRegistersAndStartDataSend);
                if(!Printer_ResetRegistersAndStartDataSend())
                    Printer_SaveToDisk();
            }
        }
    }

cancel:
    // POP_AF;
    // LDH_addr_A(hVBlank);
    // CALL(aPrinter_CleanUpAfterSend);
    Printer_CleanUpAfterSend();
    Printer_CleanUp();

    // XOR_A_A;
    // LDH_addr_A(rIF);
    // POP_AF;
    // LDH_addr_A(rIE);
    // CALL(aPrinter_ExitPrinter);
    Printer_ExitPrinter();

    // POP_AF;
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = queueLength;
    // RET;
}

bool Printer_ResetRegistersAndStartDataSend(void){
    // CALL(aPrinter_ResetJoypadRegisters);
    Printer_ResetJoypadRegisters();
    // CALL(aSendScreenToPrinter);
    // RET;
    return SendScreenToPrinter();
}

void PrintUnownStamp(void){
    PEEK("");
    // LD_A_addr(wPrinterQueueLength);
    // PUSH_AF;
    uint8_t queueLength = wram->wPrinterQueueLength;

    // XOR_A_A;
    // LDH_addr_A(hPrinter);
    hram->hPrinter = 0x0;
    // CALL(aPrinter_PlayMusic);
    Printer_PlayMusic();

    // LDH_A_addr(rIE);
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(rIF);
    // LD_A((1 << SERIAL) | (1 << VBLANK));
    // LDH_addr_A(rIE);

    // LD_HL(hVBlank);
    // LD_A_hl;
    // PUSH_AF;
    // LD_hl(4);  // vblank mode that calls AskSerial
    Printer_Begin();

    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap();
    // FARCALL(aPlaceUnownPrinterFrontpic);
    PlaceUnownPrinterFrontpic();
    // LD_A((0 << 4) | 0);  // to be loaded to wPrinterMargins
    // CALL(aPrinter_PrepareTilemapForPrint);
    Printer_PrepareTilemapForPrint((0 << 4) | 0);
    // CALL(aSafeLoadTempTilemapToTilemap);
    SafeLoadTempTilemapToTilemap();
    // CALL(aPrinter_ResetJoypadRegisters);
    Printer_ResetJoypadRegisters();

    // LD_A(18 / 2);
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = 18 / 2;
    uint8_t frames = 30;

    while(1){
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // CALL(aCheckCancelPrint);
        // IF_C goto done;
        if(CheckCancelPrint())
            break;
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto done;
        if(--frames == 0){
            Printer_AppendTilemap(wram->wPrinterTilemapBuffer, wram->wAttrmap, wram->wPrinterQueueLength * 2);
            Printer_SaveToDisk();
            break;
        }
        // CALL(aPrinterJumptableIteration);
        // LD_A_addr(wJumptableIndex);
        // CP_A(0x2);
        // IF_NC goto check_status;
        // LD_A(6 / 2);
        // LD_addr_A(wPrinterRowIndex);

    // check_status:
        // CALL(aCheckPrinterStatus);
        wram->wPrinterStatus = 0x3;
        // CALL(aPlacePrinterStatusString);
        PlacePrinterStatusString();
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// done:
    // POP_AF;
    // LDH_addr_A(hVBlank);
    // CALL(aPrinter_CleanUpAfterSend);
    Printer_CleanUpAfterSend();
    Printer_CleanUp();
    // CALL(aSafeLoadTempTilemapToTilemap);
    SafeLoadTempTilemapToTilemap();

    // XOR_A_A;
    // LDH_addr_A(rIF);
    // POP_AF;
    // LDH_addr_A(rIE);

    // POP_AF;
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = queueLength;
    // RET;
}

void PrintMailAndExit(void){
    // CALL(aPrintMail);
    PrintMail();
    // CALL(aPrinter_ExitPrinter);
    Printer_ExitPrinter();
    // RET;
}

void PrintMail(void){
    // LD_A_addr(wPrinterQueueLength);
    // PUSH_AF;
    uint8_t queueLength = wram->wPrinterQueueLength;
    // XOR_A_A;
    // LDH_addr_A(hPrinter);
    hram->hPrinter = 0x0;
    // CALL(aPrinter_PlayMusic);
    Printer_PlayMusic();

    // LDH_A_addr(rIE);
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(rIF);
    // LD_A((1 << SERIAL) | (1 << VBLANK));
    // LDH_addr_A(rIE);
    Printer_Begin();

    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;

    // LD_A((1 << 4) | 3);  // to be loaded to wPrinterMargins
    // CALL(aPrinter_PrepareTilemapForPrint);
    Printer_PrepareTilemapForPrint((1 << 4) | 3);
    // LD_HL(hVBlank);
    // LD_A_hl;
    // PUSH_AF;
    // LD_hl(4);  // vblank mode that calls AskSerial

    // LD_A(18 / 2);
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = 18 / 2;
    // CALL(aSendScreenToPrinter);
    SendScreenToPrinter();

    // POP_AF;
    // LDH_addr_A(hVBlank);
    // CALL(aPrinter_CleanUpAfterSend);
    Printer_CleanUpAfterSend();
    // CALL(aPrinter_CopyBufferToTilemap);
    Printer_CopyBufferToTilemap();
    Printer_CleanUp();

    // XOR_A_A;
    // LDH_addr_A(rIF);
    // POP_AF;
    // LDH_addr_A(rIE);

    // POP_AF;
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = queueLength;
    // RET;
}

void PrintPartymon(void){
    // LD_A_addr(wPrinterQueueLength);
    // PUSH_AF;
    uint8_t queueLength = wram->wPrinterQueueLength;
    // XOR_A_A;
    // LDH_addr_A(hPrinter);
    hram->hPrinter = 0x0;
    // CALL(aPrinter_PlayMusic);
    Printer_PlayMusic();

    // LDH_A_addr(rIE);
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(rIF);
    // LD_A((1 << SERIAL) | (1 << VBLANK));
    // LDH_addr_A(rIE);

    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // FARCALL(aPrintPartyMonPage1);
    PrintPartyMonPage1();
    // LD_A((1 << 4) | 0);  // to be loaded to wPrinterMargins
    // CALL(aPrinter_PrepareTilemapForPrint);
    Printer_Begin();
    Printer_PrepareTilemapForPrint((1 << 4) | 0);

    // LD_HL(hVBlank);
    // LD_A_hl;
    // PUSH_AF;
    // LD_hl(4);  // vblank mode that calls AskSerial

    // LD_A(16 / 2);
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = 16 / 2;
    // CALL(aPrinter_ResetJoypadRegisters);
    Printer_ResetJoypadRegisters();
    // CALL(aSendScreenToPrinter);
    // IF_C goto cancel;
    if(!SendScreenToPrinter()) {
        // CALL(aPrinter_CleanUpAfterSend);
        Printer_CleanUpAfterSend();
        // LD_C(12);
        // CALL(aDelayFrames);
        DelayFrames(12);

        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;
        // FARCALL(aPrintPartyMonPage2);
        PrintPartyMonPage2();
        // LD_A((0 << 4) | 3);  // to be loaded to wPrinterMargins
        // CALL(aPrinter_PrepareTilemapForPrint);
        Printer_PrepareTilemapForPrint((0 << 4) | 3);

        // LD_A(18 / 2);
        // LD_addr_A(wPrinterQueueLength);
        wram->wPrinterQueueLength = 18 / 2;
        // CALL(aPrinter_ResetJoypadRegisters);
        Printer_ResetJoypadRegisters();
        // CALL(aSendScreenToPrinter);
        if(!SendScreenToPrinter())
            Printer_SaveToDisk();
    }

// cancel:
    // POP_AF;
    // LDH_addr_A(hVBlank);
    // CALL(aPrinter_CleanUpAfterSend);
    Printer_CleanUpAfterSend();
    Printer_CleanUp();

    // CALL(aPrinter_CopyBufferToTilemap);
    Printer_CopyBufferToTilemap();
    // XOR_A_A;
    // LDH_addr_A(rIF);
    // POP_AF;
    // LDH_addr_A(rIE);
    // CALL(aPrinter_ExitPrinter);
    Printer_ExitPrinter();

    // POP_AF;
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = queueLength;
    // RET;
}

void v_PrintDiploma(void){
    // LD_A_addr(wPrinterQueueLength);
    // PUSH_AF;
    uint8_t queueLength = wram->wPrinterQueueLength;

    // FARCALL(aPlaceDiplomaOnScreen);
    PlaceDiplomaOnScreen();

    // XOR_A_A;
    // LDH_addr_A(hPrinter);
    hram->hPrinter = 0x0;
    // CALL(aPrinter_PlayMusic);
    Printer_PlayMusic();

    // LDH_A_addr(rIE);
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(rIF);
    // LD_A((1 << SERIAL) | (1 << VBLANK));
    // LDH_addr_A(rIE);

    // LD_HL(hVBlank);
    // LD_A_hl;
    // PUSH_AF;
    // LD_hl(4);  // vblank mode that calls AskSerial

    Printer_Begin();
    // LD_A((1 << 4) | 0);  // to be loaded to wPrinterMargins
    // CALL(aPrinter_PrepareTilemapForPrint);
    Printer_PrepareTilemapForPrint((1 << 4) | 0);
    // CALL(aPrinter_ResetJoypadRegisters);
    Printer_ResetJoypadRegisters();

    // LD_A(18 / 2);
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = 18 / 2;
    // CALL(aSendScreenToPrinter);
    // IF_C goto cancel;
    if(!SendScreenToPrinter()) {
        // CALL(aPrinter_CleanUpAfterSend);
        Printer_CleanUpAfterSend();
        // LD_C(12);
        // CALL(aDelayFrames);
        DelayFrames(12);

        // CALL(aLoadTilemapToTempTilemap);
        LoadTilemapToTempTilemap();
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = BGMAPMODE_NONE;

        // FARCALL(aPrintDiplomaPage2);
        PrintDiplomaPage2();

        // LD_A((0 << 4) | 3);  // to be loaded to wPrinterMargins
        // CALL(aPrinter_PrepareTilemapForPrint);
        Printer_PrepareTilemapForPrint((0 << 4) | 3);
        // CALL(aSafeLoadTempTilemapToTilemap);
        SafeLoadTempTilemapToTilemap();
        // CALL(aPrinter_ResetJoypadRegisters);
        Printer_ResetJoypadRegisters();

        // LD_A(18 / 2);
        // LD_addr_A(wPrinterQueueLength);
        wram->wPrinterQueueLength = 18 / 2;
        // CALL(aSendScreenToPrinter);
        if(!SendScreenToPrinter())
            Printer_SaveToDisk();
    }

// cancel:
    // POP_AF;
    // LDH_addr_A(hVBlank);
    // CALL(aPrinter_CleanUpAfterSend);
    Printer_CleanUpAfterSend();
    Printer_CleanUp();

    // XOR_A_A;
    // LDH_addr_A(rIF);
    // POP_AF;
    // LDH_addr_A(rIE);
    // CALL(aPrinter_ExitPrinter);
    Printer_ExitPrinter();

    // POP_AF;
    // LD_addr_A(wPrinterQueueLength);
    wram->wPrinterQueueLength = queueLength;
    // RET;
}

bool CheckCancelPrint(void){
    // LDH_A_addr(hJoyDown);
    // AND_A(B_BUTTON);
    // IF_NZ goto pressed_b;
    if(hram->hJoyDown & B_BUTTON) {
    // pressed_b:
        // LD_A_addr(wUnusedGameboyPrinterSafeCancelFlag);
        // CP_A(0x0c);
        // IF_NZ goto cancel;
#if 0
        if(wram->wUnusedGameboyPrinterSafeCancelFlag == 0x0c) {
        //  wait for printer activity to finish before canceling?
        loop:
            LD_A_addr(wPrinterOpcode);
            AND_A_A;
            IF_NZ goto loop;
            LD_A(0x16);  // cancel
            LD_addr_A(wPrinterOpcode);
            LD_A(0x88);
            LDH_addr_A(rSB);
            LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
            LDH_addr_A(rSC);
            LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
            LDH_addr_A(rSC);

        loop2:
            LD_A_addr(wPrinterOpcode);
            AND_A_A;
            IF_NZ goto loop2;
        }
#endif
    // cancel:
        // LD_A(0x1);
        // LDH_addr_A(hPrinter);
        hram->hPrinter = 0x1;
        // SCF;
        // RET;
        return true;
    }
    // AND_A_A;
    // RET;
    return false;
}

void Printer_CopyTilemapToBuffer(void){
    // hlcoord(0, 0, wTilemap);
    // LD_DE(wPrinterTilemapBuffer);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aCopyBytes);
    CopyBytes(wram->wPrinterTilemapBuffer, coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT);
    // RET;

}

void Printer_CopyBufferToTilemap(void){
    // LD_HL(wPrinterTilemapBuffer);
    // decoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aCopyBytes);
    CopyBytes(coord(0, 0, wram->wTilemap), wram->wPrinterTilemapBuffer, SCREEN_WIDTH * SCREEN_HEIGHT);
    // RET;
}

void Printer_ResetJoypadRegisters(void){
    // XOR_A_A;
    // LDH_addr_A(hJoyReleased);
    hram->hJoyReleased = 0;
    // LDH_addr_A(hJoyPressed);
    hram->hJoyPressed = 0;
    // LDH_addr_A(hJoyDown);
    hram->hJoyDown = 0;
    // LDH_addr_A(hJoyLast);
    hram->hJoyLast = 0;
    // RET;
}

void Printer_PlayMusic(void){
    // LD_DE(MUSIC_PRINTER);
    // CALL(aPlayMusic2);
    PlayMusic2(MUSIC_PRINTER);
    // RET;
}

void Printer_RestartMapMusic(void){
    // CALL(aRestartMapMusic);
    RestartMapMusic();
    // RET;
}

void CheckPrinterStatus(void){
//  Check for printer errors
//  If [wPrinterHandshake] == -1, we're disconnected
    LD_A_addr(wPrinterHandshake);
    CP_A(-1);
    IF_NZ goto printer_connected;
    LD_A_addr(wPrinterStatusFlags);
    CP_A(-1);
    IF_Z goto error_2;

printer_connected:
    LD_A_addr(wPrinterStatusFlags);
    AND_A(0b11100000);
    RET_Z ;  // no error

    BIT_A(7);
    IF_NZ goto error_1;
    BIT_A(6);
    IF_NZ goto error_4;
// paper error
    LD_A(PRINTER_ERROR_3);
    goto load_text_index;


error_4:
// temperature error
    LD_A(PRINTER_ERROR_4);
    goto load_text_index;


error_1:
// printer battery low
    LD_A(PRINTER_ERROR_1);
    goto load_text_index;


error_2:
// connection error
    LD_A(PRINTER_ERROR_2);

load_text_index:
    LD_addr_A(wPrinterStatus);
    RET;

}

void PlacePrinterStatusString(void){
//  Print nonzero printer status
    // LD_A_addr(wPrinterStatus);
    // AND_A_A;
    // RET_Z ;
    if(wram->wPrinterStatus == 0)
        return;
    // PUSH_AF;
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(0, 5, wTilemap);
    // LD_BC((10 << 8) | 18);
    // CALL(aTextbox);
    Textbox(coord(0, 5, wram->wTilemap), 10, 18);
    // POP_AF;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mPrinterStatusStringPointers);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    uint8_t* str = U82C(PrinterStatusStringPointers[wram->wPrinterStatus]);
    // hlcoord(1, 7, wTilemap);
    // LD_A(BANK(aGBPrinterStrings));
    // CALL(aPlaceFarString);
    PlaceStringSimple(str, coord(1, 7, wram->wTilemap));
    // hlcoord(2, 15, wTilemap);
    // LD_DE(mString_PressBToCancel);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_PressBToCancel), coord(2, 15, wram->wTilemap));
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // XOR_A_A;
    // LD_addr_A(wPrinterStatus);
    wram->wPrinterStatus = 0x0;
    // RET;
}

void PlacePrinterStatusStringBorderless(void){
//  //  unreferenced
//  Similar to PlacePrinterStatusString, but with different hlcoords
//  and ClearBox instead of TextBox.
    LD_A_addr(wPrinterStatus);
    AND_A_A;
    RET_Z ;
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    hlcoord(2, 4, wTilemap);
    LD_BC((13 << 8) | 16);
    CALL(aClearBox);
    POP_AF;
    LD_E_A;
    LD_D(0);
    LD_HL(mPrinterStatusStringPointers);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    hlcoord(4, 7, wTilemap);
    LD_A(BANK(aGBPrinterStrings));
    CALL(aPlaceFarString);
    hlcoord(4, 15, wTilemap);
    LD_DE(mString_PressBToCancel);
    CALL(aPlaceString);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    XOR_A_A;
    LD_addr_A(wPrinterStatus);
    RET;

}

const char String_PressBToCancel[] = "Press B to Cancel";

const char* PrinterStatusStringPointers[] = {
    GBPrinterString_Null,  // @
    GBPrinterString_CheckingLink,  // CHECKING LINK
    GBPrinterString_Transmitting,  // TRANSMITTING
    GBPrinterString_Printing,  // PRINTING
    GBPrinterString_PrinterError1,  // error 1
    GBPrinterString_PrinterError2,  // error 2
    GBPrinterString_PrinterError3,  // error 3
    GBPrinterString_PrinterError4,  // error 4
};

void PrintPCBox_Page1(void){
    // XOR_A_A;
    // LD_addr_A(wWhichBoxMonToPrint);
    wram->wWhichBoxMonToPrint = 0x0;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x7f);
    // CALL(aPrinter_PlaceEmptyBoxSlotString);
    Printer_PlaceEmptyBoxSlotString();

    // hlcoord(0, 0, wTilemap);
    // LD_BC(9 * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), 9 * SCREEN_WIDTH, 0x7f);

    // CALL(aPrinter_PlaceSideBorders);
    Printer_PlaceSideBorders();
    // CALL(aPrinter_PlaceTopBorder);
    Printer_PlaceTopBorder();

    // hlcoord(4, 3, wTilemap);
    // LD_DE(mPrintPCBox_Page1_String_PokemonList);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C("#MON LIST@"), coord(4, 3, wram->wTilemap));

    // LD_A_addr(wWhichBoxToPrint);
    // LD_BC(BOX_NAME_LENGTH);
    // LD_HL(wBoxNames);
    // CALL(aAddNTimes);
    // LD_D_H;
    // LD_E_L;
    // hlcoord(6, 5, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(wram->wBoxNames + wram->wWhichBoxToPrint * BOX_NAME_LENGTH, coord(6, 5, wram->wTilemap));
    // LD_A(1);
    // CALL(aPrinter_GetBoxMonSpecies);
    uint16_t de = Printer_GetBoxMonSpecies(1);
    // hlcoord(2, 9, wTilemap);
    // LD_C(3);
    // CALL(aPrinter_PrintBoxListSegment);
    Printer_PrintBoxListSegment(coord(2, 9, wram->wTilemap), de, 3);
    // RET;
}

void PrintPCBox_Page2(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x7f);
    // CALL(aPrinter_PlaceEmptyBoxSlotString);
    Printer_PlaceEmptyBoxSlotString();
    // CALL(aPrinter_PlaceSideBorders);
    Printer_PlaceSideBorders();
    // LD_A_addr(wFinishedPrintingBox);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wFinishedPrintingBox)
        return;
    // LD_A(4);
    // CALL(aPrinter_GetBoxMonSpecies);
    uint16_t de = Printer_GetBoxMonSpecies(4);
    // hlcoord(2, 0, wTilemap);
    // LD_C(6);
    // CALL(aPrinter_PrintBoxListSegment);
    Printer_PrintBoxListSegment(coord(2, 0, wram->wTilemap), de, 6);
    // RET;

}

void PrintPCBox_Page3(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x7f);
    // CALL(aPrinter_PlaceEmptyBoxSlotString);
    Printer_PlaceEmptyBoxSlotString();
    // CALL(aPrinter_PlaceSideBorders);
    Printer_PlaceSideBorders();
    // LD_A_addr(wFinishedPrintingBox);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wFinishedPrintingBox)
        return;
    // LD_A(10);
    // CALL(aPrinter_GetBoxMonSpecies);
    uint16_t de = Printer_GetBoxMonSpecies(10);
    // hlcoord(2, 0, wTilemap);
    // LD_C(6);
    // CALL(aPrinter_PrintBoxListSegment);
    Printer_PrintBoxListSegment(coord(2, 0, wram->wTilemap), de, 6);
    // RET;
}

void PrintPCBox_Page4(void){
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x7f);
    // CALL(aPrinter_PlaceEmptyBoxSlotString);
    Printer_PlaceEmptyBoxSlotString();
    // hlcoord(1, 15, wTilemap);
    // LD_BC((2 << 8) | 18);
    // CALL(aClearBox);
    ClearBox(coord(1, 15, wram->wTilemap), 18, 2);
    // CALL(aPrinter_PlaceSideBorders);
    Printer_PlaceSideBorders();
    // CALL(aPrinter_PlaceBottomBorders);
    Printer_PlaceBottomBorders();
    // LD_A_addr(wFinishedPrintingBox);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wFinishedPrintingBox)
        return;
    // LD_A(16);
    // CALL(aPrinter_GetBoxMonSpecies);
    uint16_t de = Printer_GetBoxMonSpecies(16);
    // hlcoord(2, 0, wTilemap);
    // LD_C(5);
    // CALL(aPrinter_PrintBoxListSegment);
    Printer_PrintBoxListSegment(coord(2, 0, wram->wTilemap), de, 5);
    // RET;
}

void Printer_PrintBoxListSegment(tile_t* hl, uint16_t de, uint8_t c){
    // LD_A_addr(wBankOfBoxToPrint);
    // CALL(aOpenSRAM);
    OpenSRAM(wram->wBankOfBoxToPrint);
    species_t* boxSpecies = (species_t*)GBToRAMAddr(de);

    while(1) {
    // loop:
        // LD_A_C;
        // AND_A_A;
        // JP_Z (mPrinter_PrintBoxListSegment_max_length);
        if(c == 0)
            goto max_length;
        // DEC_C;
        --c;
        // LD_A_de;
        // CP_A(0xff);
        // JP_Z (mPrinter_PrintBoxListSegment_finish);
        printf("species = %d vs %d vs %d\n", *boxSpecies, boxSpecies[1], boxSpecies[-1]);
        if(*boxSpecies == (species_t)-1)
            break;
        // LD_addr_A(wNamedObjectIndex);
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = *boxSpecies;

        // PUSH_BC;
        // PUSH_HL;
        // PUSH_DE;

        // PUSH_HL;
        // LD_BC(16);
        // LD_A(0x7f);
        // CALL(aByteFill);
        ByteFill(hl, 16, 0x7f);
        // POP_HL;

        // PUSH_HL;
        // CALL(aGetBasePokemonName);
        // POP_HL;

        // PUSH_HL;
        // CALL(aPlaceString);
        PlaceStringSimple(GetBasePokemonName(*boxSpecies), hl);
        // LD_A_addr(wCurPartySpecies);
        // CP_A(EGG);
        // POP_HL;
        // IF_Z goto ok2;
        if(wram->wCurPartySpecies != EGG) {
            // LD_BC(MON_NAME_LENGTH);
            // ADD_HL_BC;
            tile_t* hl2 = hl + MON_NAME_LENGTH;
            // CALL(aPrinter_GetMonGender);
            hl2 = Printer_GetMonGender(hl2);
            // LD_BC(SCREEN_WIDTH - MON_NAME_LENGTH);
            // ADD_HL_BC;
            hl2 += SCREEN_WIDTH - MON_NAME_LENGTH;
            // LD_A(0xf3);
            // LD_hli_A;
            *(hl2++) = 0xf3;

            // PUSH_HL;
            // LD_BC(14);
            // LD_A(0x7f);
            // CALL(aByteFill);
            ByteFill(hl2, 14, 0x7f);
            // POP_HL;

            // PUSH_HL;
            // LD_A_addr(wAddrOfBoxToPrint);
            // LD_L_A;
            // LD_A_addr(wAddrOfBoxToPrint + 1);
            // LD_H_A;
            // LD_BC(sBoxMonNicknames - sBox);
            // ADD_HL_BC;
            uint8_t* nicknames = (uint8_t*)GBToRAMAddr(wram->wAddrOfBoxToPrint + (sBoxMonNicknames - sBox));
            // LD_BC(MON_NAME_LENGTH);
            // LD_A_addr(wWhichBoxMonToPrint);
            // CALL(aAddNTimes);
            // LD_E_L;
            // LD_D_H;
            uint8_t* nick = nicknames + (wram->wWhichBoxMonToPrint * MON_NAME_LENGTH);
            // POP_HL;

            // PUSH_HL;
            // CALL(aPlaceString);
            PlaceStringSimple(nick, hl2);
            // POP_HL;

            // LD_BC(MON_NAME_LENGTH);
            // ADD_HL_BC;
            // PUSH_HL;
            hl2 += MON_NAME_LENGTH;
            // LD_A_addr(wAddrOfBoxToPrint);
            // LD_L_A;
            // LD_A_addr(wAddrOfBoxToPrint + 1);
            // LD_H_A;
            // LD_BC(2 + MONS_PER_BOX + MON_LEVEL);
            // ADD_HL_BC;
            // LD_BC(BOXMON_STRUCT_LENGTH);
            // LD_A_addr(wWhichBoxMonToPrint);
            // CALL(aAddNTimes);
            // LD_A_hl;
            uint8_t level = ((struct BoxMon*)GBToRAMAddr(wram->wAddrOfBoxToPrint + 2 + MONS_PER_BOX))[wram->wWhichBoxMonToPrint].level;
            // POP_HL;
            // CALL(aPrintLevel_Force3Digits);
            PrintLevel_Force3Digits_Conv(hl2, level);
        }
    // ok2:
        // LD_HL(wWhichBoxMonToPrint);
        // INC_hl;
        wram->wWhichBoxMonToPrint++;
        // POP_DE;
        // POP_HL;
        // LD_BC(3 * SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += 3 * SCREEN_WIDTH;
        // POP_BC;
        // INC_DE;
        boxSpecies++;
        // JP(mPrinter_PrintBoxListSegment_loop);
    }

// finish:
    // LD_A(0x1);
    // LD_addr_A(wFinishedPrintingBox);
    wram->wFinishedPrintingBox = 0x1;

max_length:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

tile_t* Printer_GetMonGender(tile_t* hl){
    // PUSH_HL;
    // LD_A_addr(wAddrOfBoxToPrint);
    // LD_L_A;
    // LD_A_addr(wAddrOfBoxToPrint + 1);
    // LD_H_A;
    // LD_BC(2 + MONS_PER_BOX + MON_DVS);
    // ADD_HL_BC;
    struct BoxMon* boxMon = (struct BoxMon*)GBToRAMAddr(wram->wAddrOfBoxToPrint + 2 + MONS_PER_BOX);
    // LD_BC(BOXMON_STRUCT_LENGTH);
    // LD_A_addr(wWhichBoxMonToPrint);
    // CALL(aAddNTimes);
    // LD_DE(wTempMonDVs);
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // LD_A_hli;
    // LD_de_A;
    wram->wTempMon.mon.DVs = boxMon[wram->wWhichBoxMonToPrint].DVs;
    // LD_A_addr(wWhichBoxMonToPrint);
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wWhichBoxMonToPrint;
    // LD_A(TEMPMON);
    // LD_addr_A(wMonType);
    // FARCALL(aGetGender);
    u8_flag_s res = GetGender_Conv(TEMPMON);
    // LD_A(0x7f);
    // IF_C goto got_gender;
    // LD_A(0xef);
    // IF_NZ goto got_gender;
    // LD_A(0xf5);

// got_gender:
    // POP_HL;
    // LD_hli_A;
    *(hl++) = (res.flag)? 0x7f: (res.a != 0)? 0xef: 0xf5;
    // RET;
    return hl;
}

uint16_t Printer_GetBoxMonSpecies(uint8_t a){
    // PUSH_HL;
    // LD_E_A;
    // LD_D(0);
    // LD_A_addr(wAddrOfBoxToPrint);
    // LD_L_A;
    // LD_A_addr(wAddrOfBoxToPrint + 1);
    // LD_H_A;
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    // POP_HL;
    // RET;
    return wram->wAddrOfBoxToPrint + a;
}

void Printer_PlaceTopBorder(void){
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    // LD_A(0x79);
    // LD_hli_A;
    *(hl++) = 0x79;
    // LD_A(0x7a);
    // LD_C(SCREEN_WIDTH - 2);
    uint8_t c = SCREEN_WIDTH - 2;

    do {
    // loop:
        // LD_hli_A;
        *(hl++) = 0x7a;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_A(0x7b);
    // LD_hl_A;
    *hl = 0x7b;
    // RET;
}

void Printer_PlaceSideBorders(void){
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    // LD_DE(SCREEN_WIDTH - 1);
    // LD_C(SCREEN_HEIGHT);
    uint8_t c = SCREEN_HEIGHT;

    do {
    // loop:
        // LD_A(0x7c);
        // LD_hl_A;
        hl[0] = 0x7c;
        // ADD_HL_DE;
        // LD_A(0x7c);
        // LD_hli_A;
        hl[SCREEN_WIDTH - 1] = 0x7c;
        hl += SCREEN_WIDTH;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

void Printer_PlaceBottomBorders(void){
    // hlcoord(0, 17, wTilemap);
    tile_t* hl = coord(0, 17, wram->wTilemap);
    // LD_A(0x7d);
    // LD_hli_A;
    *(hl++) = 0x7d;
    // LD_A(0x7a);
    // LD_C(SCREEN_WIDTH - 2);
    uint8_t c = SCREEN_WIDTH - 2;

    do {
    // loop:
        // LD_hli_A;
        *(hl++) = 0x7a;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_A(0x7e);
    // LD_hl_A;
    *hl = 0x7e;
    // RET;
}

void Printer_PlaceEmptyBoxSlotString(void){
    static const char EmptyBoxSlotString[] = "  ------@";
    // hlcoord(2, 0, wTilemap);
    tile_t* hl = coord(2, 0, wram->wTilemap);
    // LD_C(6);
    uint8_t c = 6;
    uint8_t* str = U82C(EmptyBoxSlotString);

    do {
    // loop:
        // PUSH_BC;
        // PUSH_HL;
        // LD_DE(mPrinter_PlaceEmptyBoxSlotString_EmptyBoxSlotString);
        // CALL(aPlaceString);
        PlaceStringSimple(str, hl);
        // POP_HL;
        // LD_BC(3 * SCREEN_WIDTH);
        // ADD_HL_BC;
        hl += 3 * SCREEN_WIDTH;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;

}
