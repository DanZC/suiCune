#include "../constants.h"
#include "serial.h"
#include "delay.h"
#include "mobile.h"
#include "../engine/link/place_waiting_text.h"
#include "copy_tilemap.h"
#include "../util/network.h"

static uint8_t SerialDisconnected(uint8_t a);

//  The serial interrupt.
void Serial(void){
    // PUSH_AF;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;

    // LDH_A_addr(hMobileReceive);
    // AND_A_A;
    // IF_NZ goto mobile;
    if(hram.hMobileReceive != FALSE) {
    // mobile:
        // CALL(aMobileReceive);
        MobileReceive();
    // TODO: Convert MobileReceive
        // goto end;
        return;
    }

    // LD_A_addr(wPrinterConnectionOpen);
    // BIT_A(0);
    // IF_NZ goto printer;
    else if(bit_test(wram->wPrinterConnectionOpen, 0)) {
    // printer:
        // CALL(aPrinterReceive);
    // TODO: Convert PrinterReceive
        // goto end;
        return;
    }

    // LDH_A_addr(hSerialConnectionStatus);
    // INC_A;  // is it equal to CONNECTION_NOT_ESTABLISHED?
    // IF_Z goto establish_connection;
    else if(hram.hSerialConnectionStatus == CONNECTION_NOT_ESTABLISHED) {
    // establish_connection:
        // LDH_A_addr(rSB);
        uint8_t status = gb_read(rSB);
        // CP_A(USING_EXTERNAL_CLOCK);
        // IF_Z goto player1;
        // CP_A(USING_INTERNAL_CLOCK);
        // IF_NZ goto player2;
        if(status == USING_EXTERNAL_CLOCK || status == USING_INTERNAL_CLOCK) {
        // player1:
            // LDH_addr_A(hSerialReceive);
            hram.hSerialReceive = status;
            // LDH_addr_A(hSerialConnectionStatus);
            hram.hSerialConnectionStatus = status;
            // CP_A(USING_INTERNAL_CLOCK);
            // IF_Z goto _player2;
            if(status == USING_INTERNAL_CLOCK) {
            // _player2:
                // XOR_A_A;
                // LDH_addr_A(rSB);
                gb_write(rSB, 0);
            }
            else {
                // XOR_A_A;
                // LDH_addr_A(rSB);
                gb_write(rSB, 0);

                // LD_A(3);
                // LDH_addr_A(rDIV);

            // delay_loop:
                // LDH_A_addr(rDIV);
                // BIT_A(7);
                // IF_NZ goto delay_loop;

                // LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
                // LDH_addr_A(rSC);
                gb_write(rSC, (0 << rSC_ON) | (0 << rSC_CLOCK));
                // LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
                // LDH_addr_A(rSC);
                gb_write(rSC, (1 << rSC_ON) | (0 << rSC_CLOCK));
                // goto player2;
            }
        }
    }
    else {
        // LDH_A_addr(rSB);
        // LDH_addr_A(hSerialReceive);
        hram.hSerialReceive = gb_read(rSB);

        // LDH_A_addr(hSerialSend);
        // LDH_addr_A(rSB);
        gb_write(rSB, hram.hSerialSend);

        // LDH_A_addr(hSerialConnectionStatus);
        // CP_A(USING_INTERNAL_CLOCK);
        // IF_Z goto player2;
        if(hram.hSerialConnectionStatus != USING_INTERNAL_CLOCK) {
            // LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
            // LDH_addr_A(rSC);
            gb_write(rSC, (0 << rSC_ON) | (0 << rSC_CLOCK));
            // LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
            // LDH_addr_A(rSC);
            gb_write(rSC, (1 << rSC_ON) | (0 << rSC_CLOCK));
            // goto player2;
        }
    }

// player2:
    // LD_A(TRUE);
    // LDH_addr_A(hSerialReceivedNewData);
    hram.hSerialReceivedNewData = TRUE;
    // LD_A(SERIAL_NO_DATA_BYTE);
    // LDH_addr_A(hSerialSend);
    hram.hSerialSend = SERIAL_NO_DATA_BYTE;

// end:
    // POP_HL;
    // POP_DE;
    // POP_BC;
    // POP_AF;
    // RET;
}

//  send bc bytes from hl, receive bc bytes to de
uint8_t* Serial_ExchangeBytes(void* de_, const void* hl_, uint16_t bc){
    uint8_t* de = de_;
    const uint8_t* hl = hl_;
    // LD_A(TRUE);
    // LDH_addr_A(hSerialIgnoringInitialData);
    hram.hSerialIgnoringInitialData = TRUE;

    while(1) {
    // loop:
        // LD_A_hl;
        // LDH_addr_A(hSerialSend);
        hram.hSerialSend = *hl;
        // CALL(aSerial_ExchangeByte);
        uint8_t byte;
        Network_SafeExchangeBytes(&byte, &hram.hSerialSend, 1);
        // PUSH_BC;
        // LD_B_A;
        // INC_HL;
        hl++;

        // LD_A(48);

        // do {
        // wait:
            // DEC_A;
            // IF_NZ goto wait;
        // } while(--a != 0);

        // LDH_A_addr(hSerialIgnoringInitialData);
        // AND_A_A;
        // LD_A_B;
        // POP_BC;
        // IF_Z goto load;
        if(!hram.hSerialIgnoringInitialData) {
        // load:
            // LD_de_A;
            // INC_DE;
            *(de++) = byte;
            // DEC_BC;
            --bc;
            // LD_A_B;
            // OR_A_C;
            // IF_NZ goto loop;
            if(bc != 0)
                continue;
            // RET;
            return de;
        }
        // DEC_HL;
        hl--;
        // CP_A(SERIAL_PREAMBLE_BYTE);
        // IF_NZ goto loop;
        if(byte != SERIAL_PREAMBLE_BYTE)
            continue;
        // XOR_A_A;
        // LDH_addr_A(hSerialIgnoringInitialData);
        hram.hSerialIgnoringInitialData = 0;
        // goto loop;
    }
}

static void Serial_ExchangeByte_ShortDelay(void) {
    DelayFrame();
}

uint8_t Serial_ExchangeByte(const uint8_t* hl){ 
    printf("%s:\n", __func__);
timeout_loop:
    // XOR_A_A;
    // LDH_addr_A(hSerialReceivedNewData);
    hram.hSerialReceivedNewData = 0;
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_INTERNAL_CLOCK);
    // IF_NZ goto not_player_2;
    if(hram.hSerialConnectionStatus == USING_INTERNAL_CLOCK) {
        // LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CLOCK));
        // LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CLOCK));
        Network_SendByte(hram.hSerialSend);
    }

// not_player_2:
    do {
    // loop:
        // LDH_A_addr(hSerialReceivedNewData);
        // AND_A_A;
        // IF_NZ goto await_new_data;
        if(hram.hSerialReceivedNewData != 0)
            goto await_new_data;
        // LDH_A_addr(hSerialConnectionStatus);
        // CP_A(USING_EXTERNAL_CLOCK);
        if(hram.hSerialConnectionStatus != USING_EXTERNAL_CLOCK || !CheckLinkTimeoutFramesNonzero()) {
        // not_player_1_or_timed_out:
            // LDH_A_addr(rIE);
            // AND_A((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK));
            // CP_A(1 << SERIAL);
            // IF_NZ goto loop;
            if((gb_read(rIE) & ((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK))) != (1 << SERIAL)) {
                DelayFrame();
                continue;
            }
            // LD_A_addr(wLinkByteTimeout);
            // DEC_A;
            // LD_addr_A(wLinkByteTimeout);
            // IF_NZ goto loop;
            // LD_A_addr(wLinkByteTimeout + 1);
            // DEC_A;
            // LD_addr_A(wLinkByteTimeout + 1);
            // IF_NZ goto loop;
            if(--wram->wLinkByteTimeout != 0)
                continue;
            // LDH_A_addr(hSerialConnectionStatus);
            // CP_A(USING_EXTERNAL_CLOCK);
            // IF_Z goto await_new_data;
            if(hram.hSerialConnectionStatus != USING_EXTERNAL_CLOCK) {

                // LD_A(255);

            // long_delay_loop:
                // DEC_A;
                // IF_NZ goto long_delay_loop;
            }

        await_new_data:
            // XOR_A_A;
            // LDH_addr_A(hSerialReceivedNewData);
            hram.hSerialReceivedNewData = 0;
            // LDH_A_addr(rIE);
            // AND_A((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK));
            // SUB_A(1 << SERIAL);
            // IF_NZ goto non_serial_interrupts_enabled;
            if((gb_read(rIE) & ((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK))) - (1 << SERIAL) == 0) {

            // a == 0
                //assert ['LOW(SERIAL_LINK_BYTE_TIMEOUT) == 0'];
                // LD_addr_A(wLinkByteTimeout);
                // LD_A(HIGH(SERIAL_LINK_BYTE_TIMEOUT));
                // LD_addr_A(wLinkByteTimeout + 1);
                wram->wLinkByteTimeout = SERIAL_LINK_BYTE_TIMEOUT;
            }


        // non_serial_interrupts_enabled:
            // LDH_A_addr(hSerialReceive);
            // CP_A(SERIAL_NO_DATA_BYTE);
            // RET_NZ ;
            if(hram.hSerialReceive != SERIAL_NO_DATA_BYTE)
                return hram.hSerialReceive;
            // CALL(aCheckLinkTimeoutFramesNonzero);
            // IF_Z goto timed_out;
            if(!CheckLinkTimeoutFramesNonzero()) {
            // timed_out:
                // LDH_A_addr(rIE);
                // AND_A((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK));
                // CP_A(1 << SERIAL);
                // LD_A(SERIAL_NO_DATA_BYTE);
                // RET_Z ;
                if((gb_read(rIE) & ((1 << SERIAL) | (1 << TIMER) | (1 << LCD_STAT) | (1 << VBLANK))) == (1 << SERIAL)) {
                    return SERIAL_NO_DATA_BYTE;
                }
                // LD_A_hl;
                // LDH_addr_A(hSerialSend);
                hram.hSerialSend = *hl;
                // CALL(aDelayFrame);
                DelayFrame();
                // JP(mSerial_ExchangeByte_timeout_loop);
                goto timeout_loop;
            }
            // PUSH_HL;
            // LD_HL(wLinkTimeoutFrames + 1);
            // LD_A_hl;
            // DEC_A;
            // LD_hld_A;
            // INC_A;
            // IF_NZ goto no_rollover;
            // DEC_hl;
            wram->wLinkTimeoutFrames = NativeToBigEndian16(BigEndianToNative16(wram->wLinkTimeoutFrames) - 1);


        // no_rollover:
            // POP_HL;
            // CALL(aCheckLinkTimeoutFramesNonzero);
            // JR_Z (mSerialDisconnected);
            if(!CheckLinkTimeoutFramesNonzero())
                return SerialDisconnected(0);

        // ShortDelay:
            // LD_A(15);

        // short_delay_loop:
            // DEC_A;
            // IF_NZ goto short_delay_loop;
            // RET;
        }
        // IF_NZ goto not_player_1_or_timed_out;
        // CALL(aCheckLinkTimeoutFramesNonzero);
        // IF_Z goto not_player_1_or_timed_out;
        // CALL(aSerial_ExchangeByte_ShortDelay);
        Serial_ExchangeByte_ShortDelay();
        // PUSH_HL;
        // LD_HL(wLinkTimeoutFrames + 1);
        // INC_hl;
        // IF_NZ goto no_rollover_up;
        // if(++r2.hi == 0) {
            // DEC_HL;
            // INC_hl;
            // r2.lo++;
        // }

        wram->wLinkTimeoutFrames = NativeToBigEndian16(BigEndianToNative16(wram->wLinkTimeoutFrames) + 1);

    // no_rollover_up:
        // POP_HL;
        // CALL(aCheckLinkTimeoutFramesNonzero);
        // IF_NZ goto loop;
        if(CheckLinkTimeoutFramesNonzero())
            continue;
        
        return SerialDisconnected(0);
    } while(1);
    // JP(mSerialDisconnected);
    return 0;
}

bool CheckLinkTimeoutFramesNonzero(void){
    // PUSH_HL;
    // LD_HL(wLinkTimeoutFrames);
    // LD_A_hli;
    // OR_A_hl;
    // POP_HL;
    // RET;
    return wram->wLinkTimeoutFrames != 0;
}

//  This sets wLinkTimeoutFrames to $ffff, since
//  a is always 0 when it is called.
static uint8_t SerialDisconnected(uint8_t a){
    // DEC_A;
    --a;
    // LD_addr_A(wLinkTimeoutFrames);
    // LD_addr_A(wLinkTimeoutFrames + 1);
    wram->wLinkTimeoutFrames = (a << 8) | a;
    // RET;
    return a;
}

void Serial_ExchangeSyncBytes(void){
    PEEK("");
    // LD_HL(wLinkPlayerSyncBuffer);
    const uint8_t* hl = wram->wLinkPlayerSyncBuffer;
    // LD_DE(wLinkReceivedSyncBuffer);
    uint8_t* de = wram->wLinkReceivedSyncBuffer;
    // LD_C(2);
    // LD_A(TRUE);
    // LDH_addr_A(hSerialIgnoringInitialData);
    bool result;
    do {
        DelayFrame();
        result = Network_SafeExchangeBytes(de, hl, 2);
    } while(!result);
    // hram.hSerialIgnoringInitialData = TRUE;

    // do {
        // uint8_t b, ignore;
        // do {
        // // exchange:
        //     // CALL(aDelayFrame);
        //     DelayFrame();
        //     // LD_A_hl;
        //     // LDH_addr_A(hSerialSend);
        //     hram.hSerialSend = *hl;
        //     // CALL(aSerial_ExchangeByte);
        //     // LD_B_A;
        //     b = Serial_ExchangeByte(hl);
        //     // INC_HL;
        //     hl++;
        //     // LDH_A_addr(hSerialIgnoringInitialData);
        //     ignore = hram.hSerialIgnoringInitialData;
        //     // AND_A_A;
        //     // LD_A(FALSE);
        //     // LDH_addr_A(hSerialIgnoringInitialData);
        //     hram.hSerialIgnoringInitialData = FALSE;
        //     // IF_NZ goto exchange;
        // } while(ignore);
        // LD_A_B;
        // LD_de_A;
        // *(de++) = b;
        // INC_DE;
        // DEC_C;
        // IF_NZ goto exchange;
    // } while(--c != 0);
    // RET;
}

void Serial_PrintWaitingTextAndSyncAndExchangeNybble(void){
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap();
    // CALLFAR(aPlaceWaitingText);
    PlaceWaitingText();
    // CALL(aWaitLinkTransfer);
    WaitLinkTransfer();
    // JP(mSafeLoadTempTilemapToTilemap);
    return SafeLoadTempTilemapToTilemap();
}

void Serial_SyncAndExchangeNybble(void){
    //  //  unreferenced
    CALL(aLoadTilemapToTempTilemap);
    CALLFAR(aPlaceWaitingText);
    JP(mWaitLinkTransfer);  // pointless

}

void WaitLinkTransfer(void){
    Network_FlushPendingPacketsAndSync();
    // LD_A(0xff);
    // LD_addr_A(wOtherPlayerLinkAction);
    wram->wOtherPlayerLinkAction = 0xff;

    do {
    // loop:
        // CALL(aLinkTransfer);
        LinkTransfer();
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aCheckLinkTimeoutFramesNonzero);
        // IF_Z goto check;
        if(!CheckLinkTimeoutFramesNonzero())
            continue;
        // PUSH_HL;
        // LD_HL(wLinkTimeoutFrames + 1);
        // DEC_hl;
        // IF_NZ goto skip;
        // DEC_HL;
        // DEC_hl;
        // IF_NZ goto skip;
    // We might be disconnected
        if(--wram->wLinkTimeoutFrames == 0) {
            // POP_HL;
            // XOR_A_A;
            // JP(mSerialDisconnected);
            return SerialDisconnected(0), (void)0;
        }

    // skip:
        // POP_HL;


    // check:
        // LD_A_addr(wOtherPlayerLinkAction);
        // INC_A;
        // IF_Z goto loop;
    } while(wram->wOtherPlayerLinkAction == 0xff);

    // LD_B(10);
    uint8_t b = 10;

    do {
    // receive:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aLinkTransfer);
        // LinkTransfer();
        // DEC_B;
        // IF_NZ goto receive;
    } while(--b != 0);

    // LD_B(10);
    b = 10;

    do {
    // acknowledge:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aLinkDataReceived);
        LinkDataReceived();
        // DEC_B;
        // IF_NZ goto acknowledge;
    } while(--b != 0);

    // LD_A_addr(wOtherPlayerLinkAction);
    // LD_addr_A(wOtherPlayerLinkMode);
    wram->wOtherPlayerLinkMode = wram->wOtherPlayerLinkAction;
    printf("wOtherPlayerLinkMode = %d\n", wram->wOtherPlayerLinkMode);
    // RET;
}

static void LinkTransfer_Receive(uint8_t b) {
#if 0
    // LDH_A_addr(hSerialReceive);
    // LD_addr_A(wOtherPlayerLinkMode);
    Network_SafeTryRecvByte(&wram->wOtherPlayerLinkMode);
    printf("wOtherPlayerLinkMode = %d\n", wram->wOtherPlayerLinkMode);
    // AND_A(0xf0);
    // CP_A_B;
    // RET_NZ ;
    if((hram.hSerialReceive & 0xf0) != b)
        return;
    // XOR_A_A;
    // LDH_addr_A(hSerialReceive);
    hram.hSerialReceive = 0;
    // LD_A_addr(wOtherPlayerLinkMode);
    // AND_A(0xf);
    // LD_addr_A(wOtherPlayerLinkAction);
    wram->wOtherPlayerLinkAction = wram->wOtherPlayerLinkMode & 0xf;
    printf("wOtherPlayerLinkAction = %d\n", wram->wOtherPlayerLinkAction);
    // RET;
#else
    if(Network_SafeExchangeBytes(&wram->wOtherPlayerLinkMode, &b, 1)) {
        printf("%d ?= %d\n", wram->wOtherPlayerLinkMode, b);
        if((wram->wOtherPlayerLinkMode & 0xf0) != (b & 0xf0))
            return;
        wram->wOtherPlayerLinkAction = wram->wOtherPlayerLinkMode & 0xf;
    }
#endif
}

void LinkTransfer(void){
    // PUSH_BC;
    uint8_t b;
    // LD_B(SERIAL_TIMECAPSULE);
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_TIMECAPSULE);
    // IF_Z goto got_high_nybble;
    // LD_B(SERIAL_TIMECAPSULE);
    // IF_C goto got_high_nybble;
    if(wram->wLinkMode <= LINK_TIMECAPSULE) {
        b = SERIAL_TIMECAPSULE;
    }
    // CP_A(LINK_TRADECENTER);
    // LD_B(SERIAL_TRADECENTER);
    // IF_Z goto got_high_nybble;
    else if(wram->wLinkMode == LINK_TRADECENTER) {
        b = SERIAL_TRADECENTER;
    }
    // LD_B(SERIAL_BATTLE);
    else {
        b = SERIAL_BATTLE;
    }

// got_high_nybble:
    // CALL(aLinkTransfer_Receive);
    // LinkTransfer_Receive(b);
    // LD_A_addr(wPlayerLinkAction);
    // ADD_A_B;
    // LDH_addr_A(hSerialSend);
    // hram.hSerialSend += wram->wPlayerLinkAction;
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_INTERNAL_CLOCK);
    // IF_NZ goto player_1;
    if(hram.hSerialConnectionStatus == USING_INTERNAL_CLOCK) {
        // LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CLOCK));
        // LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CLOCK));
    }

// player_1:
    // CALL(aLinkTransfer_Receive);
    LinkTransfer_Receive(b + wram->wPlayerLinkAction);
    // POP_BC;
    // RET;
}

//  Let the other system know that the data has been received.
void LinkDataReceived(void){
    // XOR_A_A;
    // LDH_addr_A(hSerialSend);
    hram.hSerialSend = 0;
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_INTERNAL_CLOCK);
    // RET_NZ ;
    if(hram.hSerialConnectionStatus == USING_INTERNAL_CLOCK) {
        // LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CLOCK));
        // LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CLOCK));
        // Network_SendByte(hram.hSerialSend);
    }
    // RET;
}

//  //  unreferenced
//  Similar to SetBitsForTimeCapsuleRequest (see engine/link/link.asm).
void SetBitsForTimeCapsuleRequestIfNotLinked(void){
    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wLinkMode != LINK_NULL)
        return;
    // LD_A(USING_INTERNAL_CLOCK);
    // LDH_addr_A(rSB);
    gb_write(rSB, USING_INTERNAL_CLOCK);
    // XOR_A_A;
    // LDH_addr_A(hSerialReceive);
    hram.hSerialReceive = 0;
    // LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
    // LDH_addr_A(rSC);
    gb_write(rSC, (0 << rSC_ON) | (0 << rSC_CLOCK));
    // LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
    // LDH_addr_A(rSC);
    gb_write(rSC, (1 << rSC_ON) | (0 << rSC_CLOCK));
    // RET;
}
