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
#include "../../gfx/misc.h"
#include "../../util/printer.h"

bool SendScreenToPrinter(void){
    uint8_t frames = 60;
    do {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
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

    PrinterSaveTilemapToDisk(wram->wPrinterTilemapBuffer, wram->wAttrmap, SCREEN_WIDTH, wram->wPrinterQueueLength * 2);


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
    // LD_A((1 << 4) | 0);
    // LD_addr_A(wPrinterMargins);
    wram->wPrinterMargins = (1 << 4) | 0;
    // FARCALL(aPrintPage1);
    PrintPage1();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
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
        DelayFrames_Conv(12);
        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x0;
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
        SendScreenToPrinter();
    }

// skip_second_page:
    // POP_AF;
    // LDH_addr_A(hVBlank);
    // CALL(aPrinter_CleanUpAfterSend);
    Printer_CleanUpAfterSend();

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
        LowVolume_Conv();
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

void PrintPCBox(void){
    LD_A_addr(wPrinterQueueLength);
    PUSH_AF;
    LD_A(18 / 2);
    LD_addr_A(wPrinterQueueLength);

    LD_A_E;
    LD_addr_A(wAddrOfBoxToPrint);
    LD_A_D;
    LD_addr_A(wAddrOfBoxToPrint + 1);
    LD_A_B;
    LD_addr_A(wBankOfBoxToPrint);
    LD_A_C;
    LD_addr_A(wWhichBoxToPrint);

    XOR_A_A;
    LDH_addr_A(hPrinter);
    LD_addr_A(wFinishedPrintingBox);
    CALL(aPrinter_PlayMusic);

    LDH_A_addr(rIE);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A((1 << SERIAL) | (1 << VBLANK));
    LDH_addr_A(rIE);

    LD_HL(hVBlank);
    LD_A_hl;
    PUSH_AF;
    LD_hl(4);  // vblank mode that calls AskSerial

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPrintPCBox_Page1);
    LD_A((1 << 4) | 0);  // to be loaded to wPrinterMargins
    CALL(aPrinter_PrepareTilemapForPrint);
    CALL(aPrinter_ResetRegistersAndStartDataSend);
    IF_C goto cancel;

    CALL(aPrinter_CleanUpAfterSend);
    LD_C(12);
    CALL(aDelayFrames);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPrintPCBox_Page2);
    LD_A((0 << 4) | 0);  // to be loaded to wPrinterMargins
    CALL(aPrinter_PrepareTilemapForPrint);
    CALL(aPrinter_ResetRegistersAndStartDataSend);
    IF_C goto cancel;

    CALL(aPrinter_CleanUpAfterSend);
    LD_C(12);
    CALL(aDelayFrames);

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPrintPCBox_Page3);
    LD_A((0 << 4) | 0);  // to be loaded to wPrinterMargins
    CALL(aPrinter_PrepareTilemapForPrint);
    CALL(aPrinter_ResetRegistersAndStartDataSend);
    IF_C goto cancel;

    CALL(aPrinter_CleanUpAfterSend);
    LD_C(12);
    CALL(aDelayFrames);

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aPrintPCBox_Page4);
    LD_A((0 << 4) | 3);  // to be loaded to wPrinterMargins
    CALL(aPrinter_PrepareTilemapForPrint);
    CALL(aPrinter_ResetRegistersAndStartDataSend);

cancel:
    POP_AF;
    LDH_addr_A(hVBlank);
    CALL(aPrinter_CleanUpAfterSend);

    XOR_A_A;
    LDH_addr_A(rIF);
    POP_AF;
    LDH_addr_A(rIE);
    CALL(aPrinter_ExitPrinter);

    POP_AF;
    LD_addr_A(wPrinterQueueLength);
    RET;

}

void Printer_ResetRegistersAndStartDataSend(void){
    CALL(aPrinter_ResetJoypadRegisters);
    CALL(aSendScreenToPrinter);
    RET;

}

void PrintUnownStamp(void){
    LD_A_addr(wPrinterQueueLength);
    PUSH_AF;

    XOR_A_A;
    LDH_addr_A(hPrinter);
    CALL(aPrinter_PlayMusic);

    LDH_A_addr(rIE);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A((1 << SERIAL) | (1 << VBLANK));
    LDH_addr_A(rIE);

    LD_HL(hVBlank);
    LD_A_hl;
    PUSH_AF;
    LD_hl(4);  // vblank mode that calls AskSerial

    XOR_A_A;
    LDH_addr_A(hBGMapMode);
    CALL(aLoadTilemapToTempTilemap);
    FARCALL(aPlaceUnownPrinterFrontpic);
    LD_A((0 << 4) | 0);  // to be loaded to wPrinterMargins
    CALL(aPrinter_PrepareTilemapForPrint);
    CALL(aSafeLoadTempTilemapToTilemap);
    CALL(aPrinter_ResetJoypadRegisters);

    LD_A(18 / 2);
    LD_addr_A(wPrinterQueueLength);

loop:
    CALL(aJoyTextDelay);
    CALL(aCheckCancelPrint);
    IF_C goto done;
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto done;
    CALL(aPrinterJumptableIteration);
    LD_A_addr(wJumptableIndex);
    CP_A(0x2);
    IF_NC goto check_status;
    LD_A(6 / 2);
    LD_addr_A(wPrinterRowIndex);


check_status:
    CALL(aCheckPrinterStatus);
    CALL(aPlacePrinterStatusString);
    CALL(aDelayFrame);
    goto loop;


done:
    POP_AF;
    LDH_addr_A(hVBlank);
    CALL(aPrinter_CleanUpAfterSend);
    CALL(aSafeLoadTempTilemapToTilemap);

    XOR_A_A;
    LDH_addr_A(rIF);
    POP_AF;
    LDH_addr_A(rIE);

    POP_AF;
    LD_addr_A(wPrinterQueueLength);
    RET;

}

void PrintMailAndExit(void){
    CALL(aPrintMail);
    CALL(aPrinter_ExitPrinter);
    RET;

}

void PrintMail(void){
    LD_A_addr(wPrinterQueueLength);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(hPrinter);
    CALL(aPrinter_PlayMusic);

    LDH_A_addr(rIE);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A((1 << SERIAL) | (1 << VBLANK));
    LDH_addr_A(rIE);

    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    LD_A((1 << 4) | 3);  // to be loaded to wPrinterMargins
    CALL(aPrinter_PrepareTilemapForPrint);
    LD_HL(hVBlank);
    LD_A_hl;
    PUSH_AF;
    LD_hl(4);  // vblank mode that calls AskSerial

    LD_A(18 / 2);
    LD_addr_A(wPrinterQueueLength);
    CALL(aSendScreenToPrinter);

    POP_AF;
    LDH_addr_A(hVBlank);
    CALL(aPrinter_CleanUpAfterSend);
    CALL(aPrinter_CopyBufferToTilemap);

    XOR_A_A;
    LDH_addr_A(rIF);
    POP_AF;
    LDH_addr_A(rIE);

    POP_AF;
    LD_addr_A(wPrinterQueueLength);
    RET;

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
    hram->hBGMapMode = 0x0;
    // FARCALL(aPrintPartyMonPage1);
    PrintPartyMonPage1();
    // LD_A((1 << 4) | 0);  // to be loaded to wPrinterMargins
    // CALL(aPrinter_PrepareTilemapForPrint);
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
        DelayFrames_Conv(12);

        // XOR_A_A;
        // LDH_addr_A(hBGMapMode);
        hram->hBGMapMode = 0x0;
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
        SendScreenToPrinter();
    }

// cancel:
    // POP_AF;
    // LDH_addr_A(hVBlank);
    // CALL(aPrinter_CleanUpAfterSend);
    Printer_CleanUpAfterSend();

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
    LD_A_addr(wPrinterQueueLength);
    PUSH_AF;

    FARCALL(aPlaceDiplomaOnScreen);

    XOR_A_A;
    LDH_addr_A(hPrinter);
    CALL(aPrinter_PlayMusic);

    LDH_A_addr(rIE);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A((1 << SERIAL) | (1 << VBLANK));
    LDH_addr_A(rIE);

    LD_HL(hVBlank);
    LD_A_hl;
    PUSH_AF;
    LD_hl(4);  // vblank mode that calls AskSerial

    LD_A((1 << 4) | 0);  // to be loaded to wPrinterMargins
    CALL(aPrinter_PrepareTilemapForPrint);
    CALL(aPrinter_ResetJoypadRegisters);

    LD_A(18 / 2);
    LD_addr_A(wPrinterQueueLength);
    CALL(aSendScreenToPrinter);
    IF_C goto cancel;
    CALL(aPrinter_CleanUpAfterSend);
    LD_C(12);
    CALL(aDelayFrames);

    CALL(aLoadTilemapToTempTilemap);
    XOR_A_A;
    LDH_addr_A(hBGMapMode);

    FARCALL(aPrintDiplomaPage2);

    LD_A((0 << 4) | 3);  // to be loaded to wPrinterMargins
    CALL(aPrinter_PrepareTilemapForPrint);
    CALL(aSafeLoadTempTilemapToTilemap);
    CALL(aPrinter_ResetJoypadRegisters);

    LD_A(18 / 2);
    LD_addr_A(wPrinterQueueLength);
    CALL(aSendScreenToPrinter);

cancel:
    POP_AF;
    LDH_addr_A(hVBlank);
    CALL(aPrinter_CleanUpAfterSend);

    XOR_A_A;
    LDH_addr_A(rIF);
    POP_AF;
    LDH_addr_A(rIE);
    CALL(aPrinter_ExitPrinter);

    POP_AF;
    LD_addr_A(wPrinterQueueLength);
    RET;

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
    CopyBytes_Conv2(wram->wPrinterTilemapBuffer, coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT);
    // RET;

}

void Printer_CopyBufferToTilemap(void){
    // LD_HL(wPrinterTilemapBuffer);
    // decoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(coord(0, 0, wram->wTilemap), wram->wPrinterTilemapBuffer, SCREEN_WIDTH * SCREEN_HEIGHT);
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
    PlayMusic2_Conv(MUSIC_PRINTER);
    // RET;
}

void Printer_RestartMapMusic(void){
    // CALL(aRestartMapMusic);
    RestartMapMusic_Conv();
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
    hram->hBGMapMode = 0x0;
    // hlcoord(0, 5, wTilemap);
    // LD_BC((10 << 8) | 18);
    // CALL(aTextbox);
    Textbox_Conv2(coord(0, 5, wram->wTilemap), 10, 18);
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
    hram->hBGMapMode = 0x1;
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
    XOR_A_A;
    LD_addr_A(wWhichBoxMonToPrint);
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    LD_A(0x7f);
    CALL(aByteFill);
    CALL(aPrinter_PlaceEmptyBoxSlotString);

    hlcoord(0, 0, wTilemap);
    LD_BC(9 * SCREEN_WIDTH);
    LD_A(0x7f);
    CALL(aByteFill);

    CALL(aPrinter_PlaceSideBorders);
    CALL(aPrinter_PlaceTopBorder);

    hlcoord(4, 3, wTilemap);
    LD_DE(mPrintPCBox_Page1_String_PokemonList);
    CALL(aPlaceString);

    LD_A_addr(wWhichBoxToPrint);
    LD_BC(BOX_NAME_LENGTH);
    LD_HL(wBoxNames);
    CALL(aAddNTimes);
    LD_D_H;
    LD_E_L;
    hlcoord(6, 5, wTilemap);
    CALL(aPlaceString);
    LD_A(1);
    CALL(aPrinter_GetBoxMonSpecies);
    hlcoord(2, 9, wTilemap);
    LD_C(3);
    CALL(aPrinter_PrintBoxListSegment);
    RET;


String_PokemonList:
    //db ['"#MON LIST@"'];

    return PrintPCBox_Page2();
}

void PrintPCBox_Page2(void){
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    LD_A(0x7f);
    CALL(aByteFill);
    CALL(aPrinter_PlaceEmptyBoxSlotString);
    CALL(aPrinter_PlaceSideBorders);
    LD_A_addr(wFinishedPrintingBox);
    AND_A_A;
    RET_NZ ;
    LD_A(4);
    CALL(aPrinter_GetBoxMonSpecies);
    hlcoord(2, 0, wTilemap);
    LD_C(6);
    CALL(aPrinter_PrintBoxListSegment);
    RET;

}

void PrintPCBox_Page3(void){
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    LD_A(0x7f);
    CALL(aByteFill);
    CALL(aPrinter_PlaceEmptyBoxSlotString);
    CALL(aPrinter_PlaceSideBorders);
    LD_A_addr(wFinishedPrintingBox);
    AND_A_A;
    RET_NZ ;
    LD_A(10);
    CALL(aPrinter_GetBoxMonSpecies);
    hlcoord(2, 0, wTilemap);
    LD_C(6);
    CALL(aPrinter_PrintBoxListSegment);
    RET;

}

void PrintPCBox_Page4(void){
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    LD_A(0x7f);
    CALL(aByteFill);
    CALL(aPrinter_PlaceEmptyBoxSlotString);
    hlcoord(1, 15, wTilemap);
    LD_BC((2 << 8) | 18);
    CALL(aClearBox);
    CALL(aPrinter_PlaceSideBorders);
    CALL(aPrinter_PlaceBottomBorders);
    LD_A_addr(wFinishedPrintingBox);
    AND_A_A;
    RET_NZ ;
    LD_A(16);
    CALL(aPrinter_GetBoxMonSpecies);
    hlcoord(2, 0, wTilemap);
    LD_C(5);
    CALL(aPrinter_PrintBoxListSegment);
    RET;

}

void Printer_PrintBoxListSegment(void){
    LD_A_addr(wBankOfBoxToPrint);
    CALL(aOpenSRAM);

loop:
    LD_A_C;
    AND_A_A;
    JP_Z (mPrinter_PrintBoxListSegment_max_length);
    DEC_C;
    LD_A_de;
    CP_A(0xff);
    JP_Z (mPrinter_PrintBoxListSegment_finish);
    LD_addr_A(wNamedObjectIndex);
    LD_addr_A(wCurPartySpecies);

    PUSH_BC;
    PUSH_HL;
    PUSH_DE;

    PUSH_HL;
    LD_BC(16);
    LD_A(0x7f);
    CALL(aByteFill);
    POP_HL;

    PUSH_HL;
    CALL(aGetBasePokemonName);
    POP_HL;

    PUSH_HL;
    CALL(aPlaceString);
    LD_A_addr(wCurPartySpecies);
    CP_A(EGG);
    POP_HL;
    IF_Z goto ok2;

    LD_BC(MON_NAME_LENGTH);
    ADD_HL_BC;
    CALL(aPrinter_GetMonGender);
    LD_BC(SCREEN_WIDTH - MON_NAME_LENGTH);
    ADD_HL_BC;
    LD_A(0xf3);
    LD_hli_A;

    PUSH_HL;
    LD_BC(14);
    LD_A(0x7f);
    CALL(aByteFill);
    POP_HL;

    PUSH_HL;
    LD_A_addr(wAddrOfBoxToPrint);
    LD_L_A;
    LD_A_addr(wAddrOfBoxToPrint + 1);
    LD_H_A;
    LD_BC(sBoxMonNicknames - sBox);
    ADD_HL_BC;
    LD_BC(MON_NAME_LENGTH);
    LD_A_addr(wWhichBoxMonToPrint);
    CALL(aAddNTimes);
    LD_E_L;
    LD_D_H;
    POP_HL;

    PUSH_HL;
    CALL(aPlaceString);
    POP_HL;

    LD_BC(MON_NAME_LENGTH);
    ADD_HL_BC;
    PUSH_HL;
    LD_A_addr(wAddrOfBoxToPrint);
    LD_L_A;
    LD_A_addr(wAddrOfBoxToPrint + 1);
    LD_H_A;
    LD_BC(2 + MONS_PER_BOX + MON_LEVEL);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_addr(wWhichBoxMonToPrint);
    CALL(aAddNTimes);
    LD_A_hl;
    POP_HL;
    CALL(aPrintLevel_Force3Digits);

ok2:
    LD_HL(wWhichBoxMonToPrint);
    INC_hl;
    POP_DE;
    POP_HL;
    LD_BC(3 * SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    INC_DE;
    JP(mPrinter_PrintBoxListSegment_loop);


finish:
    LD_A(0x1);
    LD_addr_A(wFinishedPrintingBox);

max_length:
    CALL(aCloseSRAM);
    RET;

}

void Printer_GetMonGender(void){
    PUSH_HL;
    LD_A_addr(wAddrOfBoxToPrint);
    LD_L_A;
    LD_A_addr(wAddrOfBoxToPrint + 1);
    LD_H_A;
    LD_BC(2 + MONS_PER_BOX + MON_DVS);
    ADD_HL_BC;
    LD_BC(BOXMON_STRUCT_LENGTH);
    LD_A_addr(wWhichBoxMonToPrint);
    CALL(aAddNTimes);
    LD_DE(wTempMonDVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    LD_A_addr(wWhichBoxMonToPrint);
    LD_addr_A(wCurPartyMon);
    LD_A(TEMPMON);
    LD_addr_A(wMonType);
    FARCALL(aGetGender);
    LD_A(0x7f);
    IF_C goto got_gender;
    LD_A(0xef);
    IF_NZ goto got_gender;
    LD_A(0xf5);

got_gender:
    POP_HL;
    LD_hli_A;
    RET;

}

void Printer_GetBoxMonSpecies(void){
    PUSH_HL;
    LD_E_A;
    LD_D(0);
    LD_A_addr(wAddrOfBoxToPrint);
    LD_L_A;
    LD_A_addr(wAddrOfBoxToPrint + 1);
    LD_H_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    POP_HL;
    RET;

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
    hlcoord(0, 0, wTilemap);
    LD_DE(SCREEN_WIDTH - 1);
    LD_C(SCREEN_HEIGHT);

loop:
    LD_A(0x7c);
    LD_hl_A;
    ADD_HL_DE;
    LD_A(0x7c);
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void Printer_PlaceBottomBorders(void){
    hlcoord(0, 17, wTilemap);
    LD_A(0x7d);
    LD_hli_A;
    LD_A(0x7a);
    LD_C(SCREEN_WIDTH - 2);

loop:
    LD_hli_A;
    DEC_C;
    IF_NZ goto loop;
    LD_A(0x7e);
    LD_hl_A;
    RET;

}

void Printer_PlaceEmptyBoxSlotString(void){
    hlcoord(2, 0, wTilemap);
    LD_C(6);

loop:
    PUSH_BC;
    PUSH_HL;
    LD_DE(mPrinter_PlaceEmptyBoxSlotString_EmptyBoxSlotString);
    CALL(aPlaceString);
    POP_HL;
    LD_BC(3 * SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;


EmptyBoxSlotString:
    //db ['"  ------@"'];

}
