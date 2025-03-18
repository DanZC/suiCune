#include "../../constants.h"
#include "mystery_gift.h"
#include "mystery_gift_2.h"
#include "lan.h"
#include "../../util/network.h"
#include "../../home/sram.h"
#include "../../home/copy.h"
#include "../../home/tilemap.h"
#include "../../home/lcd.h"
#include "../../home/text.h"
#include "../../home/clear_sprites.h"
#include "../../home/names.h"
#include "../../home/delay.h"
#include "../../home/joypad.h"
#include "../smallflag.h"
#include "../overworld/decorations.h"
#include "../../mobile/mobile_41.h"
#include "../../data/text/common.h"

//  hMGRole values
#define IR_RECEIVER (1)
#define IR_SENDER (2)

//  hMGStatusFlags error bits
#define MG_WRONG_CHECKSUM_F (0)
#define MG_TIMED_OUT_F     (1)
#define MG_CANCELED_F (4)
#define MG_WRONG_PREFIX_F (7)

//  hMGStatusFlags values
#define MG_WRONG_CHECKSUM (1 << MG_WRONG_CHECKSUM_F)
#define MG_TIMED_OUT (1 << MG_TIMED_OUT_F)
#define MG_CANCELED (1 << MG_CANCELED_F)
#define MG_WRONG_PREFIX (1 << MG_WRONG_PREFIX_F)
#define MG_NOT_OKAY (MG_WRONG_CHECKSUM | MG_TIMED_OUT | MG_CANCELED | MG_WRONG_PREFIX)
#define MG_OKAY ((uint8_t)~MG_NOT_OKAY)
#define MG_START_END (0b11111111)

#define REGION_PREFIX (0x96)
#define REGION_CODE (0x90)  //  USA

#define MESSAGE_PREFIX (0x5a)

#define NAME_CARD_PREFIX (0x3c)

// static bool DoMysteryGift_CheckAlreadyGotFiveGiftsToday(void){
//     // CALL(aGetMysteryGiftBank);
//     GetMysteryGiftBank();
//     // LD_A_addr(sNumDailyMysteryGiftPartnerIDs);
//     // CP_A(MAX_MYSTERY_GIFT_PARTNERS);
//     bool res = gb_read(sNumDailyMysteryGiftPartnerIDs) >= MAX_MYSTERY_GIFT_PARTNERS;
//     // JP(mCloseSRAM);
//     CloseSRAM_Conv();
//     return res;
// }

// static bool DoMysteryGift_CheckAlreadyGotAGiftFromThatPerson(void){
//     // CALL(aGetMysteryGiftBank);
//     GetMysteryGiftBank();
//     // LD_A_addr(wMysteryGiftPartnerID);
//     // LD_B_A;
//     // LD_A_addr(wMysteryGiftPartnerID + 1);
//     // LD_C_A;
//     uint16_t bc = ReverseEndian16(wram->wMysteryGiftPartnerID);
//     // LD_A_addr(sNumDailyMysteryGiftPartnerIDs);
//     // LD_D_A;
//     uint8_t d = gb_read(sNumDailyMysteryGiftPartnerIDs);
//     // LD_HL(sDailyMysteryGiftPartnerIDs);
//     uint16_t* hl = (uint16_t*)GBToRAMAddr(sDailyMysteryGiftPartnerIDs);

//     do {
//     // loop:
//         // LD_A_D;
//         // AND_A_A;
//         // IF_Z goto No;
//         // LD_A_hli;
//         // CP_A_B;
//         // IF_NZ goto skip;
//         // LD_A_hl;
//         // CP_A_C;
//         // IF_Z goto Yes;
//         if(ReverseEndian16(*hl) == bc) {
//         // Yes:
//             // SCF;
//             CloseSRAM_Conv();
//             return true;
//         }

//     // skip:
//         // INC_HL;
//         // DEC_D;
//         // goto loop;
//     } while(hl++, --d != 0);

// // No:
//     // JP(mCloseSRAM);
//     CloseSRAM_Conv();
//     return false;
// }

static void DoMysteryGift_AddMysteryGiftPartnerID(void){
    // CALL(aGetMysteryGiftBank);
    GetMysteryGiftBank();
    // LD_HL(sNumDailyMysteryGiftPartnerIDs);
    // LD_A_hl;
    uint8_t numIDs = gb_read(sNumDailyMysteryGiftPartnerIDs);
    // INC_hl;
    gb_write(sNumDailyMysteryGiftPartnerIDs, numIDs + 1);
    // LD_HL(sDailyMysteryGiftPartnerIDs);  // could have done "inc hl" instead
    uint16_t* hl = (uint16_t*)GBToRAMAddr(sDailyMysteryGiftPartnerIDs);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_addr(wMysteryGiftPartnerID);
    // LD_hli_A;
    // LD_A_addr(wMysteryGiftPartnerID + 1);
    // LD_hl_A;
    hl[numIDs] = wram->wMysteryGiftPartnerID;
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

static void DoMysteryGift_SaveMysteryGiftTrainerName(void){
    // CALL(aGetMysteryGiftBank);
    GetMysteryGiftBank();
    // LD_A(TRUE);
    // LD_addr_A(sMysteryGiftTrainerHouseFlag);
    gb_write(sMysteryGiftTrainerHouseFlag, TRUE);
    // LD_HL(wMysteryGiftPartnerName);
    // LD_DE(sMysteryGiftPartnerName);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(sMysteryGiftPartnerName), wram->wMysteryGiftPartnerName, NAME_LENGTH);
    //assert ['sMysteryGiftPartnerName + NAME_LENGTH == sMysteryGiftUnusedFlag'];
    // LD_A(TRUE);
    // LD_de_A;
    gb_write(sMysteryGiftUnusedFlag, TRUE);
    // INC_DE;
    //assert ['sMysteryGiftUnusedFlag + 1 == sMysteryGiftTrainer'];
    // LD_HL(wMysteryGiftTrainer);
    // LD_BC(wMysteryGiftTrainerEnd - wMysteryGiftTrainer);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(sMysteryGiftTrainer), wram->wMysteryGiftTrainer, sizeof(wram->wMysteryGiftTrainer));
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

void DoMysteryGift(void){
    static const txt_cmd_s MysteryGiftCanceledText[] = {
        text_far(v_MysteryGiftCanceledText)
        text_end
    };
    static const txt_cmd_s MysteryGiftCommErrorText[] = {
        text_far(v_MysteryGiftCommErrorText)
        text_end
    };
    static const txt_cmd_s RetrieveMysteryGiftText[] = {
        text_far(v_RetrieveMysteryGiftText)
        text_end
    };

    static const txt_cmd_s YourFriendIsNotReadyText[] = {
        text_far(v_YourFriendIsNotReadyText)
        text_end
    };

    // static const txt_cmd_s MysteryGiftFiveADayText[] = {
    //     text_far(v_MysteryGiftFiveADayText)
    //     text_end
    // };
    // static const txt_cmd_s MysteryGiftOneADayText[] = {
    //     text_far(v_MysteryGiftOneADayText)
    //     text_end
    // };
    static const txt_cmd_s MysteryGiftSentHomeText[] = {
        text_far(v_MysteryGiftSentHomeText)
        text_end
    };
    static const txt_cmd_s MysteryGiftSentText[] = {
        text_far(v_MysteryGiftSentText)
        text_end
    };
    OpenSRAM_Conv(MBANK(asPlayerData));
    wram->wPlayerGender = gb_read(sCrystalData);
    CopyBytes(&wram->wPlayerID,  GBToRAMAddr(sPlayerData + (wPlayerID - wPlayerData)), 2);
    CopyBytes(wram->wPlayerName, GBToRAMAddr(sPlayerData + (wPlayerName - wPlayerData)), NAME_LENGTH);
    CloseSRAM_Conv();
    // static const char String_PressAToLink_BToCancel[] = 
    //            "Press A to"
    //     t_next "link IR-Device"
    //     t_next "Press B to"
    //     t_next "cancel it.";
    while(1) {
        // CALL(aClearTilemap);
        ClearTilemap_Conv2();
        // CALL(aClearSprites);
        ClearSprites();
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        // CALL(aInitMysteryGiftLayout);
        InitMysteryGiftLayout();
        // hlcoord(3, 8, wTilemap);
        // LD_DE(mDoMysteryGift_String_PressAToLink_BToCancel);
        // CALL(aPlaceString);
        // PlaceStringSimple(U82C(String_PressAToLink_BToCancel), coord(3, 8, wram->wTilemap));
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();

    // Prepare the first of two messages for wMysteryGiftPartnerData
        // FARCALL(aStageDataForMysteryGift);
        StageDataForMysteryGift();
        // CALL(aClearMysteryGiftTrainer);
        ClearMysteryGiftTrainer();
        // LD_A(2);
        // LD_addr_A(wMysteryGiftMessageCount);
        wram->wMysteryGiftMessageCount = 2;
        // LD_A(wMysteryGiftPartnerDataEnd - wMysteryGiftPartnerData);
        // LD_addr_A(wMysteryGiftStagedDataLength);
        wram->wMysteryGiftStagedDataLength = wMysteryGiftPartnerDataEnd - wMysteryGiftPartnerData;

        // LDH_A_addr(rIE);
        // PUSH_AF;
        // CALL(aExchangeMysteryGiftData);
    // TODO: Actually implement mystery gift exchange.
        uint8_t d = ExchangeMysteryGiftData();
        // LD_D_A;
        // XOR_A_A;
        // LDH_addr_A(rIF);
        // POP_AF;
        // LDH_addr_A(rIE);

        // PUSH_DE;
        // CALL(aClearTilemap);
        ClearTilemap_Conv2();
        // CALL(aEnableLCD);
        EnableLCD();
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        // LD_B(SCGB_DIPLOMA);
        // CALL(aGetSGBLayout);
        GetSGBLayout_Conv(SCGB_DIPLOMA);
        // CALL(aSetPalettes);
        SetPalettes_Conv();
        // POP_DE;

        // hlcoord(2, 8, wTilemap);
        // LD_A_D;
        // LD_DE(mDoMysteryGift_MysteryGiftCanceledText);  // Link has been canceled
        // CP_A(MG_CANCELED);
        // JP_Z (mDoMysteryGift_LinkCanceled);
        if(d == MG_CANCELED) {
        // LinkCanceled:
            // LD_HL(mDoMysteryGift_MysteryGiftCanceledText);  // Link has been canceled
            // goto PrintTextAndExit;
            // CALL(aPrintText);
            PrintText_Conv2(MysteryGiftCanceledText);
            // LD_A(LCDC_DEFAULT);
            // LDH_addr_A(rLCDC);
            gb_write(rLCDC, LCDC_DEFAULT);
            // RET;
            return;
        }
        // CP_A(MG_OKAY);
        // JP_NZ (mDoMysteryGift_CommunicationError);
        else if(d != MG_OKAY) {
        // CommunicationError:
            // LD_HL(mDoMysteryGift_MysteryGiftCommErrorText);  // Communication error
            // CALL(aPrintText);
            PrintText_Conv2(MysteryGiftCommErrorText);
            // JP(mDoMysteryGift);
            continue;
        }
        // LD_A_addr(wMysteryGiftGameVersion);
        // CP_A(POKEMON_PIKACHU_2_VERSION);
        // IF_Z goto skip_checks;
    // Temporary fix
#if 0
        if(wram->wMysteryGiftGameVersion != POKEMON_PIKACHU_2_VERSION) {
            // CALL(aDoMysteryGift_CheckAlreadyGotFiveGiftsToday);
            // LD_HL(mDoMysteryGift_MysteryGiftFiveADayText);  // Only 5 gifts a day
            // JP_NC (mDoMysteryGift_PrintTextAndExit);
            if(DoMysteryGift_CheckAlreadyGotFiveGiftsToday()) {
                PrintText_Conv2(MysteryGiftFiveADayText);
                // LD_A(LCDC_DEFAULT);
                // LDH_addr_A(rLCDC);
                gb_write(rLCDC, LCDC_DEFAULT);
                // RET;
                return;
            }
            // CALL(aDoMysteryGift_CheckAlreadyGotAGiftFromThatPerson);
            // LD_HL(mDoMysteryGift_MysteryGiftOneADayText);  // Only one gift a day per person
            // JP_C (mDoMysteryGift_PrintTextAndExit);
            if(DoMysteryGift_CheckAlreadyGotAGiftFromThatPerson()) {
                PrintText_Conv2(MysteryGiftOneADayText);
                // LD_A(LCDC_DEFAULT);
                // LDH_addr_A(rLCDC);
                gb_write(rLCDC, LCDC_DEFAULT);
                // RET;
                return;
            }
        }
#endif

    // skip_checks:
        // LD_A_addr(wMysteryGiftPlayerBackupItem);
        // AND_A_A;
        // JP_NZ (mDoMysteryGift_GiftWaiting);
        if(wram->wMysteryGiftPlayerBackupItem != NO_ITEM) {
        // GiftWaiting:
            // LD_HL(mDoMysteryGift_RetrieveMysteryGiftText);  // receive gift at counter
            // goto PrintTextAndExit;
            // CALL(aPrintText);
            PrintText_Conv2(RetrieveMysteryGiftText);
            // LD_A(LCDC_DEFAULT);
            // LDH_addr_A(rLCDC);
            gb_write(rLCDC, LCDC_DEFAULT);
            // RET;
            return;
        }
        // LD_A_addr(wMysteryGiftPartnerBackupItem);
        // AND_A_A;
        // JP_NZ (mDoMysteryGift_FriendNotReady);
        if(wram->wMysteryGiftPartnerBackupItem != NO_ITEM) {
        // FriendNotReady:
            // LD_HL(mDoMysteryGift_YourFriendIsNotReadyText);  // friend not ready
            // CALL(aPrintText);
            PrintText_Conv2(YourFriendIsNotReadyText);
            // LD_A(LCDC_DEFAULT);
            // LDH_addr_A(rLCDC);
            gb_write(rLCDC, LCDC_DEFAULT);
            // RET;
            return;
        }
        // LD_A_addr(wMysteryGiftGameVersion);
        // CP_A(POKEMON_PIKACHU_2_VERSION);
        // IF_Z goto skip_append_save;
        if(wram->wMysteryGiftGameVersion != POKEMON_PIKACHU_2_VERSION) {
            // CALL(aDoMysteryGift_AddMysteryGiftPartnerID);
            DoMysteryGift_AddMysteryGiftPartnerID();
            // LD_A_addr(wMysteryGiftGameVersion);
            // CP_A(RESERVED_GAME_VERSION);
            // IF_Z goto skip_append_save;
            if(wram->wMysteryGiftGameVersion != RESERVED_GAME_VERSION) {
                // CALL(aDoMysteryGift_SaveMysteryGiftTrainerName);
                DoMysteryGift_SaveMysteryGiftTrainerName();
                // FARCALL(aRestoreMobileEventIndex);
                RestoreMobileEventIndex();
                // FARCALL(aStubbedTrainerRankings_MysteryGift);
                StubbedTrainerRankings_MysteryGift();
                // FARCALL(aBackupMobileEventIndex);
                BackupMobileEventIndex();
            }
        }

    // skip_append_save:
        // LD_A_addr(wMysteryGiftPartnerSentDeco);
        // AND_A_A;
        // IF_Z goto SentItem;
        if(wram->wMysteryGiftPartnerSentDeco) {
        //  sent decoration
            // LD_A_addr(wMysteryGiftPartnerWhichDeco);
            // LD_C_A;
            // FARCALL(aMysteryGiftGetDecoration);
            uint8_t deco = MysteryGiftGetDecoration(wram->wMysteryGiftPartnerWhichDeco);
            // PUSH_BC;
            // CALL(aCheckAndSetMysteryGiftDecorationAlreadyReceived);
            // POP_BC;
            // IF_NZ goto SentItem;
            if(!CheckAndSetMysteryGiftDecorationAlreadyReceived(deco)) {
            //  keep the decoration if it wasn't already received
                // CALLFAR(aGetDecorationName_c);
                // LD_H_D;
                // LD_L_E;
                // LD_DE(wStringBuffer1);
                // LD_BC(ITEM_NAME_LENGTH);
                // CALL(aCopyBytes);
                GetDecorationName_c(deco);
                // LD_HL(mDoMysteryGift_MysteryGiftSentHomeText);  // sent decoration to home
                // goto PrintTextAndExit;
                // CALL(aPrintText);
                PrintText_Conv2(MysteryGiftSentHomeText);
                // LD_A(LCDC_DEFAULT);
                // LDH_addr_A(rLCDC);
                gb_write(rLCDC, LCDC_DEFAULT);
                // RET;
                return;
            }
        }

    // SentItem:
        // CALL(aGetMysteryGiftBank);
        GetMysteryGiftBank();
        // LD_A_addr(wMysteryGiftPartnerWhichItem);
        // LD_C_A;
        // FARCALL(aMysteryGiftGetItem);
        // LD_A_C;
        item_t item = MysteryGiftGetItem(wram->wMysteryGiftPartnerWhichItem);
        // LD_addr_A(sBackupMysteryGiftItem);
        gb_write(sBackupMysteryGiftItem, item);
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
        // CALL(aGetItemName);
        GetItemName(item);
        // LD_HL(mDoMysteryGift_MysteryGiftSentText);  // sent item/decoration
        // goto PrintTextAndExit;
        // CALL(aPrintText);
        PrintText_Conv2(MysteryGiftSentText);
        // LD_A(LCDC_DEFAULT);
        // LDH_addr_A(rLCDC);
        gb_write(rLCDC, LCDC_DEFAULT);
        // RET;
        return;

    // LinkCanceled:
        // LD_HL(mDoMysteryGift_MysteryGiftCanceledText);  // Link has been canceled
        // goto PrintTextAndExit;


    // CommunicationError:
        // LD_HL(mDoMysteryGift_MysteryGiftCommErrorText);  // Communication error
        // CALL(aPrintText);
        // JP(mDoMysteryGift);


    // GiftWaiting:
        // LD_HL(mDoMysteryGift_RetrieveMysteryGiftText);  // receive gift at counter
        // goto PrintTextAndExit;


    // FriendNotReady:
        // LD_HL(mDoMysteryGift_YourFriendIsNotReadyText);  // friend not ready
    // fallthrough


    // PrintTextAndExit:
        // CALL(aPrintText);
        // LD_A(LCDC_DEFAULT);
        // LDH_addr_A(rLCDC);
        // RET;
    }

}

uint8_t ExchangeMysteryGiftData(void){
    static const char String_ExchangingData_BToCancel[] = 
               "Exchanging"
        t_next "data<...> <...>"
        t_next "Press B to"
        t_next "cancel.";
    // NOP;
    // FARCALL(aClearChannels);
    // CALL(aInitializeIRCommunicationInterrupts);
    LANConnection();
    if(wram->wScriptVar == FALSE)
        return MG_CANCELED;

    PlaceStringSimple(U82C(String_ExchangingData_BToCancel), coord(3, 8, wram->wTilemap));
    Network_FlushPendingPacketsAndSync();

    int res;
    do {
    // restart:
        GetJoypad_Conv2();
        // CALL(aBeginIRCommunication);
        // CALL(aInitializeIRCommunicationRoles);
        res = Network_ExchangeBytes(&wram->wMysteryGiftGameVersion, wram->wMysteryGiftStaging, 80);
        // LDH_A_addr(hMGStatusFlags);
        // CP_A(MG_CANCELED);
        // JP_Z (mEndOrContinueMysteryGiftIRCommunication);
        if(res == NETWORK_XCHG_NO_CONNECTION || bit_test(hram->hJoyPressed, B_BUTTON_F)) {
            LANCloseConnection();
            return MG_CANCELED;
        }
        // CP_A(MG_OKAY);
        // IF_NZ goto restart;
        DelayFrame();
    } while(res != NETWORK_XCHG_OK);

    Network_FlushPendingPacketsAndSync();
    StagePartyDataForMysteryGift();
    do {
    // restart:
        GetJoypad_Conv2();
        // CALL(aBeginIRCommunication);
        // CALL(aInitializeIRCommunicationRoles);
        res = Network_ExchangeBytes(wram->wMysteryGiftTrainer, wram->wMysteryGiftStaging, sizeof(wram->wMysteryGiftTrainer));
        // LDH_A_addr(hMGStatusFlags);
        // CP_A(MG_CANCELED);
        // JP_Z (mEndOrContinueMysteryGiftIRCommunication);
        if(res == NETWORK_XCHG_NO_CONNECTION || bit_test(hram->hJoyPressed, B_BUTTON_F)) {
            LANCloseConnection();
            return MG_CANCELED;
        }
        // CP_A(MG_OKAY);
        // IF_NZ goto restart;
        DelayFrame();
    } while(res != NETWORK_XCHG_OK);

    LANCloseConnection();
    return MG_OKAY;

    // LDH_A_addr(hMGRole);
    // CP_A(IR_SENDER);
    // JR_Z (mSenderExchangeMysteryGiftDataPayloads);
//  receiver
    // LD_HL(hMGExchangedByte);
    // LD_B(1);
    // CALL(aTryReceivingIRDataBlock);
    // IF_NZ goto failed;
    // CALL(aReceiveMysteryGiftDataPayload_GotRegionPrefix);
    // JP_NZ (mEndOrContinueMysteryGiftIRCommunication);
    // JR(mReceiverExchangeMysteryGiftDataPayloads_GotPayload);


// failed:
// Delay frame

// wait_frame:
    // LDH_A_addr(rLY);
    // CP_A(LY_VBLANK);
    // IF_C goto wait_frame;

    // LD_C(LOW(rRP));
    // LD_A(rRP_ENABLE_READ_MASK);
    // LDH_c_A;

    // LD_B(60 * 4);  // 4 seconds

// continue_:
    // PUSH_BC;
    // CALL(aMysteryGift_UpdateJoypad);
    // LD_B(1 << rRP_RECEIVING);
    // LD_C(LOW(rRP));

// in_vblank:
    // LDH_A_c;
    // AND_A_B;
    // LD_B_A;
    // LDH_A_addr(rLY);
    // CP_A(LY_VBLANK);
    // IF_NC goto in_vblank;

// wait_vblank:
    // LDH_A_c;
    // AND_A_B;
    // LD_B_A;
    // LDH_A_addr(rLY);
    // CP_A(LY_VBLANK);
    // IF_C goto wait_vblank;
    // LD_A_B;
    // POP_BC;
// Restart if the 4-second timeout has elapsed
    // DEC_B;
    // IF_Z goto restart;
// Restart if rRP is not receiving data
    // OR_A_A;
    // IF_NZ goto restart;
// Check if we've pressed the B button to cancel
    // LDH_A_addr(hMGJoypadReleased);
    // BIT_A(B_BUTTON_F);
    // IF_Z goto continue_;
    // LD_A(MG_CANCELED);
    // LDH_addr_A(hMGStatusFlags);
    // JP(mEndOrContinueMysteryGiftIRCommunication);

}

void ReceiverExchangeMysteryGiftDataPayloads(void){
// Receive the data payload
    CALL(aReceiveMysteryGiftDataPayload);
    JP_NZ (mEndOrContinueMysteryGiftIRCommunication);
// fallthrough
    return ReceiverExchangeMysteryGiftDataPayloads_GotPayload();
}

void ReceiverExchangeMysteryGiftDataPayloads_GotPayload(void){
// Switch roles
    CALL(aBeginSendingIRCommunication);
    JP_NZ (mEndOrContinueMysteryGiftIRCommunication);
// Send the data payload
    CALL(aSendMysteryGiftDataPayload);
    JP_NZ (mEndOrContinueMysteryGiftIRCommunication);
// Switch roles
    CALL(aBeginReceivingIRCommunication);
    JP_NZ (mEndOrContinueMysteryGiftIRCommunication);
// Receive an empty block
    CALL(aReceiveEmptyIRDataBlock);
    JP(mEndOrContinueMysteryGiftIRCommunication);

}

void SenderExchangeMysteryGiftDataPayloads(void){
// Send the data payload
    CALL(aSendMysteryGiftDataPayload);
    JP_NZ (mEndOrContinueMysteryGiftIRCommunication);
// Switch roles
    CALL(aBeginReceivingIRCommunication);
    JP_NZ (mEndOrContinueMysteryGiftIRCommunication);
// Receive the data payload
    CALL(aReceiveMysteryGiftDataPayload);
    JP_NZ (mEndOrContinueMysteryGiftIRCommunication);
// Switch roles
    CALL(aBeginSendingIRCommunication);
    JP_NZ (mEndOrContinueMysteryGiftIRCommunication);
// Send an empty block
    CALL(aSendEmptyIRDataBlock);
    JP(mEndOrContinueMysteryGiftIRCommunication);

}

void ReceiveMysteryGiftDataPayload(void){
// Receive the region prefix
    LD_HL(hMGExchangedByte);
    LD_B(1);
    CALL(aTryReceivingIRDataBlock);
    RET_NZ ;
// fallthrough
    return ReceiveMysteryGiftDataPayload_GotRegionPrefix();
}

void ReceiveMysteryGiftDataPayload_GotRegionPrefix(void){
// Receive an empty block
    CALL(aReceiveEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET_NZ ;
// Verify the received region prefix
    LDH_A_addr(hMGExchangedByte);
    CP_A(REGION_PREFIX);
    JP_NZ (mWrongMysteryGiftRegion);
    LD_A(REGION_CODE);
    LDH_addr_A(hMGExchangedByte);
// Switch roles
    CALL(aBeginSendingIRCommunication);
    RET_NZ ;
// Send the region code
    LD_HL(hMGExchangedByte);
    LD_B(1);
    CALL(aTrySendingIRDataBlock);
    RET_NZ ;
// Send an empty block
    CALL(aSendEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET_NZ ;
// Switch roles
    CALL(aBeginReceivingIRCommunication);
    RET_NZ ;
// Receive the staged data
    LD_HL(wMysteryGiftTrainer);
    LD_A_addr(wMysteryGiftStagedDataLength);
    LD_B_A;
    CALL(aTryReceivingIRDataBlock);
    RET_NZ ;
// Receive an empty block
    CALL(aReceiveEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET;

}

void SendMysteryGiftDataPayload(void){
// Send the region prefix
    LD_A(REGION_PREFIX);
    LDH_addr_A(hMGExchangedByte);
    LD_HL(hMGExchangedByte);
    LD_B(1);
    CALL(aTrySendingIRDataBlock);
    RET_NZ ;
// Send an empty block
    CALL(aSendEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET_NZ ;
// Switch roles
    CALL(aBeginReceivingIRCommunication);
    RET_NZ ;
// Receive the region code
    LD_HL(hMGExchangedByte);
    LD_B(1);
    CALL(aTryReceivingIRDataBlock);
    RET_NZ ;
// Receive an empty block
    CALL(aReceiveEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET_NZ ;
// Verify the received region code
    LDH_A_addr(hMGExchangedByte);
    CP_A(REGION_CODE);
    JP_NZ (mWrongMysteryGiftRegion);
// Switch roles
    CALL(aBeginSendingIRCommunication);
    RET_NZ ;
// Send the staged data
    LD_HL(wMysteryGiftStaging);
    LD_A_addr(wMysteryGiftStagedDataLength);
    LD_B_A;
    CALL(aTrySendingIRDataBlock);
    RET_NZ ;
// Send an empty block
    CALL(aSendEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET;

}

void EndOrContinueMysteryGiftIRCommunication(void){
    NOP;
    LDH_A_addr(hMGStatusFlags);
// Quit if player canceled
    CP_A(MG_CANCELED);
    IF_Z goto quit;
// Quit if there was a communication error
    CP_A(MG_OKAY);
    IF_NZ goto quit;
// Quit if all messages are sent/received
    LD_HL(wMysteryGiftMessageCount);
    DEC_hl;
    IF_Z goto quit;
// Quit if communicating with Pokémon Pikachu 2 device
    LD_HL(wMysteryGiftTrainer);
    LD_DE(wMysteryGiftPartnerData);
    LD_BC(wMysteryGiftPartnerDataEnd - wMysteryGiftPartnerData);
    CALL(aCopyBytes);
    LD_A_addr(wMysteryGiftTrainer);  // first byte is the version
    CP_A(POKEMON_PIKACHU_2_VERSION);
    IF_NC goto quit;

// Prepare the second message for wMysteryGiftTrainer
    FARCALL(aStagePartyDataForMysteryGift);
    CALL(aClearMysteryGiftTrainer);
    LD_A(wMysteryGiftTrainerEnd - wMysteryGiftTrainer);
    LD_addr_A(wMysteryGiftStagedDataLength);

    LDH_A_addr(hMGRole);
    CP_A(IR_SENDER);
    IF_Z goto sender;
//  receiver
    CALL(aBeginReceivingIRCommunication);
    JR_NZ (mEndOrContinueMysteryGiftIRCommunication);
    JP(mReceiverExchangeMysteryGiftDataPayloads);


sender:
    CALL(aBeginSendingIRCommunication);
    JR_NZ (mEndOrContinueMysteryGiftIRCommunication);
    JP(mSenderExchangeMysteryGiftDataPayloads);


quit:
    LDH_A_addr(hMGStatusFlags);
    PUSH_AF;
    CALL(aEndIRCommunication);
    XOR_A_A;
    LDH_addr_A(rIF);
    LDH_A_addr(rIE);
    OR_A(1 << VBLANK);
    LDH_addr_A(rIE);
    NOP;
    CALL(aDelayFrame);
    POP_AF;
    RET;

}

void ExchangeNameCardData(void){
    NOP;
    FARCALL(aClearChannels);
    CALL(aInitializeIRCommunicationInterrupts);


restart:
    CALL(aBeginIRCommunication);
    CALL(aInitializeIRCommunicationRoles);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_CANCELED);
    JP_Z (mEndNameCardIRCommunication);
    CP_A(MG_OKAY);
    IF_NZ goto restart;

    LDH_A_addr(hMGRole);
    CP_A(IR_SENDER);
    IF_Z goto sender;
//  receiver
// Receive the data payload
    CALL(aReceiveNameCardDataPayload);
    JP_NZ (mEndNameCardIRCommunication);
// Switch roles
    CALL(aBeginSendingIRCommunication);
    JP_NZ (mEndNameCardIRCommunication);
// Send the data payload
    CALL(aSendNameCardDataPayload);
    JP_NZ (mEndNameCardIRCommunication);
// Switch roles
    CALL(aBeginReceivingIRCommunication);
    JP_NZ (mEndNameCardIRCommunication);
// Receive an empty block
    CALL(aReceiveEmptyIRDataBlock);
    JP(mEndNameCardIRCommunication);


sender:
// Send the data payload
    CALL(aSendNameCardDataPayload);
    JP_NZ (mEndNameCardIRCommunication);
// Switch roles
    CALL(aBeginReceivingIRCommunication);
    JP_NZ (mEndNameCardIRCommunication);
// Receive the data payload
    CALL(aReceiveNameCardDataPayload);
    JP_NZ (mEndNameCardIRCommunication);
// Switch roles
    CALL(aBeginSendingIRCommunication);
    JP_NZ (mEndNameCardIRCommunication);
// Send an empty block
    CALL(aSendEmptyIRDataBlock);
    JP(mEndNameCardIRCommunication);

}

void ReceiveNameCardDataPayload(void){
// Receive the Name Card prefix
    LD_HL(hMGExchangedByte);
    LD_B(1);
    CALL(aTryReceivingIRDataBlock);
    RET_NZ ;
// Receive an empty block
    CALL(aReceiveEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET_NZ ;
// Verify the received Name Card prefix
    LDH_A_addr(hMGExchangedByte);
    CP_A(NAME_CARD_PREFIX);
    JP_NZ (mWrongMysteryGiftRegion);
    SWAP_A;
    LDH_addr_A(hMGExchangedByte);
// Switch roles
    CALL(aBeginSendingIRCommunication);
    RET_NZ ;
// Send the swapped Name Card prefix
    LD_HL(hMGExchangedByte);
    LD_B(1);
    CALL(aTrySendingIRDataBlock);
    RET_NZ ;
// Send an empty block
    CALL(aSendEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET_NZ ;
// Switch roles
    CALL(aBeginReceivingIRCommunication);
    RET_NZ ;
// Receive the staged data
    LD_HL(wNameCardData);
    LD_A_addr(wMysteryGiftStagedDataLength);
    LD_B_A;
    CALL(aTryReceivingIRDataBlock);
    RET_NZ ;
// Receive an empty block
    CALL(aReceiveEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET;

}

void SendNameCardDataPayload(void){
// Send the Name Card prefix
    LD_A(NAME_CARD_PREFIX);
    LDH_addr_A(hMGExchangedByte);
    LD_HL(hMGExchangedByte);
    LD_B(1);
    CALL(aTrySendingIRDataBlock);
    RET_NZ ;
// Send an empty block
    CALL(aSendEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET_NZ ;
// Switch roles
    CALL(aBeginReceivingIRCommunication);
    RET_NZ ;
// Receive the swapped Name Card prefix
    LD_HL(hMGExchangedByte);
    LD_B(1);
    CALL(aTryReceivingIRDataBlock);
    RET_NZ ;
// Receive an empty block
    CALL(aReceiveEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET_NZ ;
// Verify the received swapped Name Card prefix
    LDH_A_addr(hMGExchangedByte);
    SWAP_A;
    CP_A(NAME_CARD_PREFIX);
    JP_NZ (mWrongMysteryGiftRegion);
// Switch roles
    CALL(aBeginSendingIRCommunication);
    RET_NZ ;
// Send the staged data
    LD_HL(wMysteryGiftStaging);
    LD_A_addr(wMysteryGiftStagedDataLength);
    LD_B_A;
    CALL(aTrySendingIRDataBlock);
    RET_NZ ;
// Send an empty block
    CALL(aSendEmptyIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET;

}

void EndNameCardIRCommunication(void){
    NOP;
    LDH_A_addr(hMGStatusFlags);
    PUSH_AF;
    CALL(aEndIRCommunication);
    XOR_A_A;
    LDH_addr_A(rIF);
    LDH_A_addr(rIE);
    OR_A(1 << VBLANK);
    LDH_addr_A(rIE);
    NOP;
    CALL(aDelayFrame);
    POP_AF;
    RET;

}

void WrongMysteryGiftRegion(void){
    LD_A(MG_WRONG_PREFIX);
    LDH_addr_A(hMGStatusFlags);
    AND_A_A;
    RET;

}

void BeginSendingIRCommunication(void){
    CALL(aBeginIRCommunication);
    CALL(aSendIRHelloMessage);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET;

}

void BeginReceivingIRCommunication(void){
    CALL(aBeginIRCommunication);
    CALL(aReceiveIRHelloMessage);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET;

}

void TrySendingIRDataBlock(void){
    CALL(aSendIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET;

}

void TryReceivingIRDataBlock(void){
    CALL(aReceiveIRDataBlock);
    LDH_A_addr(hMGStatusFlags);
    CP_A(MG_OKAY);
    RET;

}

void InitializeIRCommunicationInterrupts(void){
    CALL(aStartFastIRTimer);
    LD_A(1 << TIMER);
    LDH_addr_A(rIE);
    XOR_A_A;
    LDH_addr_A(rIF);
    CALL(aBeginIRCommunication);
//  waits for ~$40400 cycles = ~0.25 seconds
    XOR_A_A;
    LD_B_A;

busy_wait:
    INC_A;
    IF_NZ goto busy_wait;
    INC_B;
    IF_NZ goto busy_wait;
    RET;

}

void StartFastIRTimer(void){
//  Starts a 65,536 Hz timer that interrupts every 3 increments (21,845 Hz).
    XOR_A_A;
    LDH_addr_A(rTAC);
    LD_A(-2);
    LDH_addr_A(rTMA);
    LDH_addr_A(rTIMA);
    LD_A(rTAC_65536_HZ);
    LDH_addr_A(rTAC);
    OR_A(1 << rTAC_ON);
    LDH_addr_A(rTAC);
    RET;

}

void StartSlowIRTimer(void){
//  Starts a 65,536 Hz timer that interrupts every 256 increments (256 Hz).
    XOR_A_A;
    LDH_addr_A(rTAC);
    LDH_addr_A(rTMA);
    LDH_addr_A(rTIMA);
    LD_A(rTAC_65536_HZ);
    LDH_addr_A(rTAC);
    OR_A(1 << rTAC_ON);
    LDH_addr_A(rTAC);
    RET;

}

void BeginIRCommunication(void){
    LD_A(rRP_ENABLE_READ_MASK);
    CALL(aToggleIRCommunication);
    LD_A(IR_RECEIVER);
    LDH_addr_A(hMGRole);
    RET;

}

void EndIRCommunication(void){
    XOR_A_A;
    CALL(aToggleIRCommunication);
    LD_A(rTAC_65536_HZ);
    LDH_addr_A(rTAC);
    RET;

}

void ReceiveInfraredLEDOn(void){
//  Count interrupts of the partner's IR LED on

recv_loop:
    INC_D;
    RET_Z ;
    XOR_A_A;
    LDH_addr_A(rIF);
    //halt ['?']
    LDH_A_c;
    BIT_A(rRP_RECEIVING);
    IF_Z goto recv_loop;
    OR_A_A;
    RET;

}

void ReceiveInfraredLEDOff(void){
//  Count interrupts of the partner's IR LED off

no_recv_loop:
    INC_D;
    RET_Z ;
    XOR_A_A;
    LDH_addr_A(rIF);
    //halt ['?']
    LDH_A_c;
    BIT_A(rRP_RECEIVING);
    IF_NZ goto no_recv_loop;
    OR_A_A;
    RET;

}

void SendInfraredLEDOn(void){
//  Holds the IR LED on for d-1 interrupts.
    LD_A(rRP_ENABLE_READ_MASK | (1 << rRP_LED_ON));
    LDH_c_A;

wait:
    DEC_D;
    RET_Z ;
    XOR_A_A;
    LDH_addr_A(rIF);
    //halt ['?']
    goto wait;

    return SendInfraredLEDOff();
}

void SendInfraredLEDOff(void){
//  Holds the IR LED off for d-1 interrupts.
    LD_A(rRP_ENABLE_READ_MASK);
    LDH_c_A;

wait:
    DEC_D;
    RET_Z ;
    XOR_A_A;
    LDH_addr_A(rIF);
    //halt ['?']
    goto wait;

    return InitializeIRCommunicationRoles();
}

void InitializeIRCommunicationRoles(void){
    LD_D(0);
    LD_E_D;

    LD_A(IR_RECEIVER);
    LDH_addr_A(hMGRole);

loop:
    CALL(aMysteryGift_UpdateJoypad);
    LD_B(1 << rRP_RECEIVING);
    LD_C(LOW(rRP));
// Check if we've pressed the B button to cancel
    LDH_A_addr(hMGJoypadReleased);
    BIT_A(B_BUTTON_F);
    IF_Z goto not_canceled;
    LD_A(MG_CANCELED);
    LDH_addr_A(hMGStatusFlags);
    RET;


not_canceled:
// Check if we've pressed the A button to start sending
    BIT_A(A_BUTTON_F);
    JR_NZ (mSendIRHelloMessageAfterDelay);
// If rRP is not receiving data, keep checking for input
    LDH_A_c;
    AND_A_B;
    IF_NZ goto loop;
// fallthrough

    return ReceiveIRHelloMessage();
}

void ReceiveIRHelloMessage(void){
    LD_C(LOW(rRP));
    LD_D(0);
    LD_E_D;

    CALL(aReceiveInfraredLEDOff);
    JP_Z (mInfraredLEDReceiveTimedOut);
    LD_D_E;
    CALL(aReceiveInfraredLEDOn);
    JP_Z (mInfraredLEDReceiveTimedOut);
    CALL(aReceiveInfraredLEDOff);
    JP_Z (mInfraredLEDReceiveTimedOut);
    CALL(aReceiveInfraredLEDOn);
    JP_Z (mInfraredLEDReceiveTimedOut);

    LD_A(MG_OKAY);
    LDH_addr_A(hMGStatusFlags);

    LD_D(61);
    CALL(aSendInfraredLEDOff);
    LD_D(5);
    CALL(aSendInfraredLEDOn);
    LD_D(21);
    CALL(aSendInfraredLEDOff);
    LD_D(5);
    CALL(aSendInfraredLEDOn);
    LD_D(5);
    CALL(aSendInfraredLEDOff);
    RET;

}

void SendIRHelloMessageAfterDelay(void){
// Wait a random amount of time
    CALL(aRandom);
    LD_E_A;
    AND_A(0xf);
    LD_D_A;

wait_loop:
    DEC_DE;
    LD_A_D;
    OR_A_E;
    IF_NZ goto wait_loop;
// fallthrough

    return SendIRHelloMessage();
}

void SendIRHelloMessage(void){
    LD_A(IR_SENDER);
    LDH_addr_A(hMGRole);

    LD_C(LOW(rRP));
    LD_D(0);
    LD_E_D;

    LD_D(61);
    CALL(aSendInfraredLEDOff);
    LD_D(5);
    CALL(aSendInfraredLEDOn);
    LD_D(21);
    CALL(aSendInfraredLEDOff);
    LD_D(5);
    CALL(aSendInfraredLEDOn);
    LD_D(5);
    CALL(aSendInfraredLEDOff);

    LD_D_E;
    CALL(aReceiveInfraredLEDOff);
    JP_Z (mInfraredLEDReceiveTimedOut);
    LD_D_E;
    CALL(aReceiveInfraredLEDOn);
    JP_Z (mInfraredLEDReceiveTimedOut);
    CALL(aReceiveInfraredLEDOff);
    JP_Z (mInfraredLEDReceiveTimedOut);
    CALL(aReceiveInfraredLEDOn);
    JP_Z (mInfraredLEDReceiveTimedOut);

    LD_D(61);
    CALL(aSendInfraredLEDOff);

    LD_A(MG_OKAY);
    LDH_addr_A(hMGStatusFlags);
    RET;

}

void ToggleIRCommunication(void){
    LDH_addr_A(rRP);
    LD_A(MG_START_END);
    LDH_addr_A(hMGStatusFlags);
    RET;

}

void SendIRDataBlock(void){
//  Send b bytes of data in three messages:
//  1. two bytes: MESSAGE_PREFIX and the length b
//  2. b bytes: the actual data
//  3. two bytes: a little-endian checksum
//  Then receive a one-byte acknowledgement message: the status.
    XOR_A_A;
    LDH_addr_A(hMGChecksum + 0);
    LDH_addr_A(hMGChecksum + 1);
    PUSH_HL;
    PUSH_BC;
    LD_C(LOW(rRP));
    LD_D(61);
    CALL(aSendInfraredLEDOff);
    LD_HL(hMGExchangedWord);
    LD_A(MESSAGE_PREFIX);
    LD_hli_A;
    LD_hl_B;
    DEC_HL;
    LD_B(2);
    CALL(aSendIRDataMessage);
    POP_BC;
    POP_HL;
    CALL(aSendIRDataMessage);
    LDH_A_addr(hMGChecksum + 0);
    LDH_addr_A(hMGExchangedWord + 0);
    LDH_A_addr(hMGChecksum + 1);
    LDH_addr_A(hMGExchangedWord + 1);
    PUSH_HL;
    LD_HL(hMGExchangedWord);
    LD_B(2);
    CALL(aSendIRDataMessage);
    LD_HL(hMGStatusFlags);
    LD_B(1);
    CALL(aReceiveIRDataMessage);
    LDH_A_addr(hMGExchangedWord + 0);
    LDH_addr_A(hMGChecksum + 0);
    LDH_A_addr(hMGExchangedWord + 1);
    LDH_addr_A(hMGChecksum + 1);
    POP_HL;
    RET;

}

void SendIRDataMessage(void){
//  Send b bytes of data one bit at a time, and update the checksum.
    LD_C(LOW(rRP));

    LD_D(5);
    CALL(aSendInfraredLEDOff);
    LD_D(5);
    CALL(aSendInfraredLEDOn);
    LD_D(21);
    CALL(aSendInfraredLEDOff);

// b = -b - 1// then count up to 0
    LD_A_B;
    CPL;
    LD_B_A;

    LD_A(-12);
    LDH_addr_A(rTMA);

byte_loop:
    INC_B;
    IF_Z goto done;
    LD_A(8);
    LDH_addr_A(hMGNumBits);
// Get the next data byte
    LD_A_hli;
    LD_E_A;
// Add the next data byte to the checksum
    LDH_A_addr(hMGChecksum + 0);
    ADD_A_E;
    LDH_addr_A(hMGChecksum + 0);
    LDH_A_addr(hMGChecksum + 1);
    ADC_A(0);
    LDH_addr_A(hMGChecksum + 1);
// Send each bit of the byte

bit_loop:
    XOR_A_A;
    LDH_addr_A(rIF);
    //halt ['?']
    LD_A(rRP_ENABLE_READ_MASK | (1 << rRP_LED_ON));
    LDH_addr_A(rRP);
// Turn the LED off for longer if the bit is 1
    LD_D(1);
    LD_A_E;
    RLCA;
    LD_E_A;
    IF_NC goto wait;
    INC_D;

wait:
    LDH_A_addr(rTIMA);
    CP_A(-8);
    IF_C goto wait;
    LD_A(rRP_ENABLE_READ_MASK);
    LDH_addr_A(rRP);
    DEC_D;
    IF_Z goto no_halt;
    XOR_A_A;
    LDH_addr_A(rIF);
    //halt ['?']

no_halt:
    LDH_A_addr(hMGNumBits);
    DEC_A;
    IF_Z goto byte_loop;
    LDH_addr_A(hMGNumBits);
    goto bit_loop;


done:
    LD_A(-2);
    LDH_addr_A(rTMA);
    XOR_A_A;
    LDH_addr_A(rIF);
    //halt ['?']

    LD_D(5);
    CALL(aSendInfraredLEDOn);
    LD_D(17);
    CALL(aSendInfraredLEDOff);
    RET;

}

void InfraredLEDReceiveTimedOut(void){
    LDH_A_addr(hMGStatusFlags);
    OR_A(MG_TIMED_OUT);
    LDH_addr_A(hMGStatusFlags);
    RET;

}

void ReceivedWrongIRChecksum(void){
    LDH_A_addr(hMGStatusFlags);
    OR_A(MG_WRONG_CHECKSUM);
    LDH_addr_A(hMGStatusFlags);
    RET;

}

void ReceivedWrongIRMessagePrefix(void){
    LDH_A_addr(hMGStatusFlags);
    OR_A(MG_WRONG_PREFIX);
    LDH_addr_A(hMGStatusFlags);
    RET;

}

void ReceiveIRDataBlock(void){
//  Receive b bytes of data in three messages:
//  1. two bytes: MESSAGE_PREFIX and the length b
//  2. b bytes: the actual data
//  3. two bytes: a little-endian checksum
//  Then send a one-byte acknowledgement message: the status.
    XOR_A_A;
    LDH_addr_A(hMGChecksum + 0);
    LDH_addr_A(hMGChecksum + 1);
    PUSH_BC;
    PUSH_HL;
    LD_HL(hMGExchangedWord);
    LD_B(2);
    CALL(aReceiveIRDataMessage);
    LDH_A_addr(hMGExchangedWord + 1);
    LDH_addr_A(hMGUnusedMsgLength);
    LD_B_A;
    POP_HL;
    POP_AF;
    CP_A_B;
    JP_C (mReceivedWrongIRMessagePrefix);
    LDH_A_addr(hMGExchangedWord + 0);
    CP_A(MESSAGE_PREFIX);
    JP_NZ (mReceivedWrongIRMessagePrefix);
    CALL(aReceiveIRDataMessage);
    LDH_A_addr(hMGChecksum + 0);
    LD_D_A;
    LDH_A_addr(hMGChecksum + 1);
    LD_E_A;
    PUSH_HL;
    PUSH_DE;
    LD_HL(hMGExchangedWord);
    LD_B(2);
    CALL(aReceiveIRDataMessage);
    POP_DE;
    LD_HL(hMGExchangedWord);
    LD_A_hli;
    XOR_A_D;
    LD_B_A;
    LD_A_hl;
    XOR_A_E;
    OR_A_B;
    CALL_NZ (aReceivedWrongIRChecksum);
    PUSH_DE;

    LD_D(61);
    CALL(aSendInfraredLEDOff);

    LD_HL(hMGStatusFlags);
    LD_B(1);
    CALL(aSendIRDataMessage);

    POP_DE;
    POP_HL;
    LD_A_D;
    LDH_addr_A(hMGChecksum + 0);
    LD_A_E;
    LDH_addr_A(hMGChecksum + 1);
    RET;

}

void ReceiveIRDataMessage(void){
    LD_C(LOW(rRP));

    LD_D(0);
    CALL(aReceiveInfraredLEDOff);
    JP_Z (mInfraredLEDReceiveTimedOut);
    LD_D(0);
    CALL(aReceiveInfraredLEDOn);
    JP_Z (mInfraredLEDReceiveTimedOut);
    LD_D(0);
    CALL(aReceiveInfraredLEDOff);
    JP_Z (mInfraredLEDReceiveTimedOut);

    LD_A_B;
    CPL;
    LD_B_A;
    XOR_A_A;
    LDH_addr_A(hMGPrevTIMA);

    CALL(aStartSlowIRTimer);

main_loop:
    INC_B;
    IF_Z goto done;
    LD_A(8);
    LDH_addr_A(hMGNumBits);

inner_loop:
    LD_D(0);

recv_loop:
    INC_D;
    IF_Z goto recv_done;
    LDH_A_c;
    BIT_A(rRP_RECEIVING);
    IF_Z goto recv_loop;
    LD_D(0);

recv_done:

send_loop:
    INC_D;
    IF_Z goto send_done;
    LDH_A_c;
    BIT_A(rRP_RECEIVING);
    IF_NZ goto send_loop;

send_done:
    LDH_A_addr(hMGPrevTIMA);
    LD_D_A;
    LDH_A_addr(rTIMA);
    LDH_addr_A(hMGPrevTIMA);
    SUB_A_D;
    CP_A(0x12);
    IF_C goto zero;
    SET_E(0);
    goto ok;

zero:
    RES_E(0);

ok:
    LDH_A_addr(hMGNumBits);
    DEC_A;
    LDH_addr_A(hMGNumBits);
    IF_Z goto continue_;
    LD_A_E;
    RLCA;
    LD_E_A;
    goto inner_loop;


continue_:
    LD_A_E;
    LD_hli_A;
    LDH_A_addr(hMGChecksum + 0);
    ADD_A_E;
    LDH_addr_A(hMGChecksum + 0);
    LDH_A_addr(hMGChecksum + 1);
    ADC_A(0);
    LDH_addr_A(hMGChecksum + 1);
    goto main_loop;


done:
    CALL(aStartFastIRTimer);
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_D(0);
    CALL(aReceiveInfraredLEDOn);
    JP_Z (mInfraredLEDReceiveTimedOut);

    LD_D(16);
    CALL(aSendInfraredLEDOff);
    RET;

}

void SendEmptyIRDataBlock(void){
    LD_B(0);
    JP(mSendIRDataBlock);

}

void ReceiveEmptyIRDataBlock(void){
    LD_B(0);
    JP(mReceiveIRDataBlock);

}

void MysteryGift_UpdateJoypad(void){
//  We can only get four inputs at a time.
//  We take d-pad first for no particular reason.
    LD_A(R_DPAD);
    LDH_addr_A(rJOYP);
//  Read twice to give the request time to take.
    LDH_A_addr(rJOYP);
    LDH_A_addr(rJOYP);

//  The Joypad register output is in the lo nybble (inversed).
//  We make the hi nybble of our new container d-pad input.
    CPL;
    AND_A(0xf);
    SWAP_A;

//  We'll keep this in b for now.
    LD_B_A;

//  Buttons make 8 total inputs (A, B, Select, Start).
//  We can fit this into one byte.
    LD_A(R_BUTTONS);
    LDH_addr_A(rJOYP);
//  Wait for input to stabilize.
    for(int rept = 0; rept < 6; rept++){
    LDH_A_addr(rJOYP);
    }
//  Buttons take the lo nybble.
    CPL;
    AND_A(0xf);
    OR_A_B;
    LD_C_A;
//  To get the delta we xor the last frame's input with the new one.
    LDH_A_addr(hMGJoypadPressed);
    XOR_A_C;
//  Released this frame:
    AND_A_C;
    LDH_addr_A(hMGJoypadReleased);
//  Pressed this frame:
    LD_A_C;
    LDH_addr_A(hMGJoypadPressed);
    LD_A(0x30);
//  Reset the joypad register since we're done with it.
    LDH_addr_A(rJOYP);
    RET;

}

//  Return true (nz) if decoration c was already received
bool CheckAndSetMysteryGiftDecorationAlreadyReceived(uint8_t c){
    // CALL(aGetMysteryGiftBank);
    GetMysteryGiftBank();
    // LD_D(0);
    // LD_B(CHECK_FLAG);
    // LD_HL(sMysteryGiftDecorationsReceived);
    // LDA_PREDEF(pSmallFarFlagAction);
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aPredef);
    uint8_t res = SmallFarFlagAction_Conv((uint8_t*)GBToRAMAddr(sMysteryGiftDecorationsReceived), c, CHECK_FLAG);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A_C;
    // AND_A_A;
    // POP_BC;
    // POP_HL;
    // RET_NZ ;
    if(res != 0)
        return true;
    // CALL(aGetMysteryGiftBank);
    GetMysteryGiftBank();
    // LD_B(SET_FLAG);
    // PREDEF(pSmallFarFlagAction);
    SmallFarFlagAction_Conv((uint8_t*)GBToRAMAddr(sMysteryGiftDecorationsReceived), c, SET_FLAG);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // XOR_A_A;
    // RET;
    return false;
}

void CopyMysteryGiftReceivedDecorationsToPC(void){
    // CALL(aGetMysteryGiftBank);
    GetMysteryGiftBank();
    uint8_t* hl = GBToRAMAddr(sMysteryGiftDecorationsReceived);
    // LD_C(0);
    for(uint32_t c = 0; c < NUM_NON_TROPHY_DECOS; ++c) {
    // loop:
        // PUSH_BC;
        // LD_D(0);
        // LD_B(CHECK_FLAG);
        // LD_HL(sMysteryGiftDecorationsReceived);
        // PREDEF(pSmallFarFlagAction);
        uint8_t a = SmallFarFlagAction_Conv(hl, c, CHECK_FLAG);
        // LD_A_C;
        // AND_A_A;
        // POP_BC;
        // IF_Z goto skip;
        if(a != 0) { // Is this logic correct? Only set flags for decorations received before? 
            // PUSH_BC;
            // CALLFAR(aSetSpecificDecorationFlag);
            SetSpecificDecorationFlag_Conv(c);
            // POP_BC;
        }

    // skip:
        // INC_C;
        // LD_A_C;
        // CP_A(NUM_NON_TROPHY_DECOS);
        // IF_C goto loop;
    }
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

//  If [sMysteryGiftUnlocked] was -1, this sets both
//  [sMysteryGiftUnlocked] and [sMysteryGiftItem] to 0.
void UnlockMysteryGift(void){
    // CALL(aGetMysteryGiftBank);
    GetMysteryGiftBank();
    // LD_HL(sMysteryGiftUnlocked);
    // LD_A_hl;
    // INC_A;
    // IF_NZ goto ok;
    if(gb_read(sMysteryGiftUnlocked) == 0xff) {
        // LD_hld_A;
        //assert ['sMysteryGiftUnlocked - 1 == sMysteryGiftItem'];
        // LD_hl_A;
        gb_write(sMysteryGiftItem, 0);
        gb_write(sMysteryGiftUnlocked, 0);
    }
// ok:
    // JP(mCloseSRAM);
    return CloseSRAM_Conv();
}

void ResetDailyMysteryGiftLimitIfUnlocked(void){
    // CALL(aGetMysteryGiftBank);
    GetMysteryGiftBank();
    // LD_A_addr(sNumDailyMysteryGiftPartnerIDs);
    // CP_A(-1);  // locked?
    // IF_Z goto dont_clear;
    if(gb_read(sNumDailyMysteryGiftPartnerIDs) != 0xff) {
        // XOR_A_A;
        // LD_addr_A(sNumDailyMysteryGiftPartnerIDs);
        gb_write(sNumDailyMysteryGiftPartnerIDs, 0);
    }

// dont_clear:
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

void BackupMysteryGift(void){
//  Copies [sMysteryGiftItem] to [sBackupMysteryGiftItem],
//  and [sMysteryGiftUnlocked] to [sNumDailyMysteryGiftPartnerIDs].
    // CALL(aGetMysteryGiftBank);
    GetMysteryGiftBank();
    // LD_HL(sMysteryGiftItem);
    // LD_DE(sBackupMysteryGiftItem);
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    gb_write(sBackupMysteryGiftItem, gb_read(sMysteryGiftItem));
    //assert ['sMysteryGiftItem + 1 == sMysteryGiftUnlocked'];
    //assert ['sBackupMysteryGiftItem + 1 == sNumDailyMysteryGiftPartnerIDs'];
    // LD_A_hl;
    // LD_de_A;
    gb_write(sBackupMysteryGiftItem + 1, gb_read(sMysteryGiftItem + 1));
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

void RestoreMysteryGift(void){
//  Copies [sBackupMysteryGiftItem] to [sMysteryGiftItem],
//  and [sNumDailyMysteryGiftPartnerIDs] to [sMysteryGiftUnlocked].
    // CALL(aGetMysteryGiftBank);
    GetMysteryGiftBank();
    // LD_HL(sBackupMysteryGiftItem);
    // LD_DE(sMysteryGiftItem);
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    gb_write(sMysteryGiftItem, gb_read(sBackupMysteryGiftItem));
    //assert ['sBackupMysteryGiftItem + 1 == sNumDailyMysteryGiftPartnerIDs'];
    //assert ['sMysteryGiftItem + 1 == sMysteryGiftUnlocked'];
    // LD_A_hl;
    // LD_de_A;
    gb_write(sMysteryGiftItem + 1, gb_read(sBackupMysteryGiftItem + 1));
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

void ClearMysteryGiftTrainer(void){
    // LD_HL(wMysteryGiftTrainer);
    // XOR_A_A;
    // LD_B(wMysteryGiftTrainerEnd - wMysteryGiftTrainer);
    for(uint32_t i = 0; i < lengthof(wram->wMysteryGiftTrainer); ++i) {
    // loop:
        // LD_hli_A;
        wram->wMysteryGiftTrainer[i] = 0;
        // DEC_B;
        // IF_NZ goto loop;
    }
    // RET;
}

void GetMysteryGiftBank(void){
    // LD_A(BANK(sMysteryGiftData));
    // JP(mOpenSRAM);
    OpenSRAM_Conv(MBANK(asMysteryGiftData));
}

//  You will be sending this data to your mystery gift partner.
//  Structure is the same as a trainer with species and moves
//  defined.
void StagePartyDataForMysteryGift(void){
    // LD_A(BANK(sPokemonData));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asPokemonData));
    // LD_DE(wMysteryGiftStaging);
    uint8_t* de = wram->wMysteryGiftStaging;
    // LD_BC(sPokemonData + wPartyMons - wPokemonData);
    struct PartyMon* bc = (struct PartyMon*)GBToRAMAddr(sPokemonData + wPartyMons - wPokemonData);
    // LD_HL(sPokemonData + wPartySpecies - wPokemonData);
    species_t* hl = (species_t*)GBToRAMAddr(sPokemonData + wPartySpecies - wPokemonData);

    while(*hl != (species_t)-1) {
    // loop:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto party_end;
        // CP_A(EGG);
        // IF_Z goto next;
        if(*hl != EGG) {
            // PUSH_HL;
        // copy level
            // LD_HL(MON_LEVEL);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_de_A;
            // INC_DE;
            *(de++) = bc->mon.level;
        // copy species
            // LD_HL(MON_SPECIES);
            // ADD_HL_BC;
            // LD_A_hl;
            // LD_de_A;
            // INC_DE;
            CopyBytes(de, &bc->mon.species, sizeof(bc->mon.species));
            de += sizeof(bc->mon.species);
        // copy moves
            // LD_HL(MON_MOVES);
            // ADD_HL_BC;
            // PUSH_BC;
            // LD_BC(NUM_MOVES);
            // CALL(aCopyBytes);
            CopyBytes(de, bc->mon.moves, sizeof(bc->mon.moves));
            de += sizeof(bc->mon.moves);
            // POP_BC;
            // POP_HL;
        }

    // next:
        // PUSH_HL;
        // LD_HL(PARTYMON_STRUCT_LENGTH);
        // ADD_HL_BC;
        // LD_B_H;
        // LD_C_L;
        bc++;
        // POP_HL;
        hl++;
        // goto loop;
    }

// party_end:
    // LD_A(-1);
    // LD_de_A;
    *(de++) = (species_t)-1;
    // LD_A(wMysteryGiftTrainerEnd - wMysteryGiftTrainer);
    // LD_addr_A(wUnusedMysteryGiftStagedDataLength);
    // JP(mCloseSRAM);
    CloseSRAM_Conv();
}

static void InitMysteryGiftLayout_LoadNGFX(tile_t* hl, tile_t a, uint8_t b) {
// Load5GFX:
    // LD_B(5);
    // goto gfx_loop;

// Load6GFX:
//   //  unreferenced
    // LD_B(6);
    // goto gfx_loop;

// Load16GFX:
    // LD_B(16);
    do {
    // gfx_loop:
        // LD_hli_A;
        *(hl++) = a++;
        // INC_A;
        // DEC_B;
        // IF_NZ goto gfx_loop;
    } while(--b != 0);
    // RET;
}

static void InitMysteryGiftLayout_LoadNColumn(tile_t* hl, tile_t a, uint8_t b) {
// Load9Column:
    // LD_B(9);
    // goto col_loop;

// Load11Column:
    // LD_B(11);
    // goto col_loop;

// Load14Column:
    // LD_B(14);
    do {
    // col_loop:
        // LD_hl_A;
        *hl = a;
        // LD_DE(SCREEN_WIDTH);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto col_loop;
    } while(--b != 0);
    // RET;
}

static void InitMysteryGiftLayout_Load16Row(tile_t* hl, tile_t a) {
    // LD_B(16);
    uint8_t b = 16;
    do {
    // row_loop:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_B;
        // IF_NZ goto row_loop;
    } while(--b != 0);
    // RET;
}

void InitMysteryGiftLayout(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_HL(mMysteryGiftGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    // LD_A(BANK(aMysteryGiftGFX));
    // LD_BC(0x43 * LEN_2BPP_TILE);
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, MysteryGiftGFX, 0, 0x43);
    // hlcoord(0, 0, wTilemap);
    // LD_A(0x42);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0x42);
    // hlcoord(3, 7, wTilemap);
    // LD_BC((9 << 8) | 15);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(3, 7, wram->wTilemap), 15, 9);
    // hlcoord(0, 0, wTilemap);
    // LD_A(0x0);
    // LD_hli_A;
    *coord(0, 0, wram->wTilemap) = 0x0;
    // INC_A;
    // LD_hl_A;
    *coord(1, 0, wram->wTilemap) = 0x1;
    // hlcoord(0, 1, wTilemap);
    // INC_A;
    // LD_hli_A;
    *coord(0, 1, wram->wTilemap) = 0x2;
    // INC_A;
    // LD_hl_A;
    *coord(1, 1, wram->wTilemap) = 0x3;
    // hlcoord(7, 1, wTilemap);
    // LD_A(0x12);
    // CALL(aInitMysteryGiftLayout_Load5GFX);
    InitMysteryGiftLayout_LoadNGFX(coord(7, 1, wram->wTilemap), 0x12, 5);
    // hlcoord(2, 2, wTilemap);
    // LD_A(0x17);
    // CALL(aInitMysteryGiftLayout_Load16GFX);
    InitMysteryGiftLayout_LoadNGFX(coord(2, 2, wram->wTilemap), 0x17, 16);
    // hlcoord(2, 3, wTilemap);
    // LD_A(0x27);
    // CALL(aInitMysteryGiftLayout_Load16GFX);
    InitMysteryGiftLayout_LoadNGFX(coord(2, 3, wram->wTilemap), 0x27, 16);
    // hlcoord(9, 4, wTilemap);
    // LD_A(0x37);
    // LD_hli_A;
    *coord(9, 4, wram->wTilemap) = 0x37;
    // INC_A;
    // LD_hl_A;
    *coord(10, 4, wram->wTilemap) = 0x38;
    // hlcoord(1, 2, wTilemap);
    // LD_hl(0x4);
    *coord(1, 2, wram->wTilemap) = 0x4;
    // hlcoord(1, 3, wTilemap);
    // LD_A(0x5);
    // CALL(aInitMysteryGiftLayout_Load14Column);
    InitMysteryGiftLayout_LoadNColumn(coord(1, 3, wram->wTilemap), 0x5, 14);
    // LD_A(0x9);
    // hlcoord(18, 5, wTilemap);
    // CALL(aInitMysteryGiftLayout_Load11Column);
    InitMysteryGiftLayout_LoadNColumn(coord(18, 5, wram->wTilemap), 0x9, 11);
    // hlcoord(2, 5, wTilemap);
    // LD_A(0xb);
    // CALL(aInitMysteryGiftLayout_Load16Row);
    InitMysteryGiftLayout_Load16Row(coord(2, 5, wram->wTilemap), 0xb);
    // hlcoord(2, 16, wTilemap);
    // LD_A(0x7);
    // CALL(aInitMysteryGiftLayout_Load16Row);
    InitMysteryGiftLayout_Load16Row(coord(2, 16, wram->wTilemap), 0x7);
    // hlcoord(2, 5, wTilemap);
    // LD_A(0xd);
    // CALL(aInitMysteryGiftLayout_Load5GFX);
    InitMysteryGiftLayout_LoadNGFX(coord(2, 5, wram->wTilemap), 0xd, 5);
    // hlcoord(7, 5, wTilemap);
    // LD_hl(0xc);
    *coord(7, 5, wram->wTilemap) = 0xc;
    // hlcoord(18, 5, wTilemap);
    // LD_hl(0xa);
    *coord(18, 5, wram->wTilemap) = 0xa;
    // hlcoord(18, 16, wTilemap);
    // LD_hl(0x8);
    *coord(18, 16, wram->wTilemap) = 0x8;
    // hlcoord(1, 16, wTilemap);
    // LD_hl(0x6);
    *coord(1, 16, wram->wTilemap) = 0x6;
    // hlcoord(2, 6, wTilemap);
    // LD_A(0x3a);
    // CALL(aInitMysteryGiftLayout_Load16Row);
    InitMysteryGiftLayout_Load16Row(coord(2, 6, wram->wTilemap), 0x3a);
    // hlcoord(2, 15, wTilemap);
    // LD_A(0x40);
    // CALL(aInitMysteryGiftLayout_Load16Row);
    InitMysteryGiftLayout_Load16Row(coord(2, 15, wram->wTilemap), 0x40);
    // hlcoord(2, 6, wTilemap);
    // LD_A(0x3c);
    // CALL(aInitMysteryGiftLayout_Load9Column);
    InitMysteryGiftLayout_LoadNColumn(coord(2, 6, wram->wTilemap), 0x3c, 9);
    // hlcoord(17, 6, wTilemap);
    // LD_A(0x3e);
    // CALL(aInitMysteryGiftLayout_Load9Column);
    InitMysteryGiftLayout_LoadNColumn(coord(17, 6, wram->wTilemap), 0x3e, 9);
    // hlcoord(2, 6, wTilemap);
    // LD_hl(0x39);
    *coord(2, 6, wram->wTilemap) = 0x39;
    // hlcoord(17, 6, wTilemap);
    // LD_hl(0x3b);
    *coord(17, 6, wram->wTilemap) = 0x3b;
    // hlcoord(2, 15, wTilemap);
    // LD_hl(0x3f);
    *coord(2, 15, wram->wTilemap) = 0x3f;
    // hlcoord(17, 15, wTilemap);
    // LD_hl(0x41);
    *coord(17, 15, wram->wTilemap) = 0x41;
    // CALL(aEnableLCD);
    EnableLCD();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_B(SCGB_MYSTERY_GIFT);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_MYSTERY_GIFT);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // RET;
}

const char MysteryGiftGFX[] = "gfx/mystery_gift/mystery_gift.png";

void DoNameCardSwap(void){
    CALL(aClearTilemap);
    CALL(aClearSprites);
    CALL(aWaitBGMap);
    CALL(aInitNameCardLayout);
    hlcoord(3, 8, wTilemap);
    LD_DE(mDoNameCardSwap_String_PressAToLink_BToCancel_JP);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    CALL(aStageDataForNameCard);
    CALL(aClearMysteryGiftTrainer);
    LD_A(wNameCardDataEnd - wNameCardData);
    LD_addr_A(wMysteryGiftStagedDataLength);
    LDH_A_addr(rIE);
    PUSH_AF;
    CALL(aExchangeNameCardData);
    LD_D_A;
    XOR_A_A;
    LDH_addr_A(rIF);
    POP_AF;
    LDH_addr_A(rIE);
    LD_A_D;
    CP_A(0x10);
    JP_Z (mDoNameCardSwap_LinkCanceled);
    CP_A(MG_OKAY);
    JP_NZ (mDoNameCardSwap_CommunicationError);
    CALL(aDoNameCardSwap_SlideNameCardUpOffScreen);
    LD_C(60);
    CALL(aDelayFrames);
    CALL(aDoNameCardSwap_ClearScreen);
    LD_HL(mDoNameCardSwap_NameCardReceivedCardText);
    CALL(aPrintText);
    LD_DE(wNameCardData);
    FARCALL(aFunction8ac70);
    LD_A_C;
    LD_addr_A(wTextDecimalByte);
    LD_HL(mDoNameCardSwap_NameCardNotRegisteredCardText);
    IF_C goto PrintTextAndExit;
    LD_HL(mDoNameCardSwap_NameCardListedCardText);
    goto PrintTextAndExit;


SlideNameCardUpOffScreen:
    LD_C(16);

loop:
    LD_HL(wVirtualOAMSprite00YCoord);
    LD_B(8);

dec_y_loop:
    DEC_hl;
    for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH; rept++){
    INC_HL;
    }
    DEC_B;
    IF_NZ goto dec_y_loop;
    LD_HL(wVirtualOAMSprite08YCoord);
    LD_B(8);

inc_y_loop:
    INC_hl;
    for(int rept = 0; rept < SPRITEOAMSTRUCT_LENGTH; rept++){
    INC_HL;
    }
    DEC_B;
    IF_NZ goto inc_y_loop;
    DEC_C;
    RET_Z ;
    PUSH_BC;
    LD_C(4);
    CALL(aDelayFrames);
    POP_BC;
    goto loop;


LinkCanceled:
    CALL(aDoNameCardSwap_ClearScreen);
    LD_HL(mDoNameCardSwap_NameCardLinkCancelledText);
    goto PrintTextAndExit;


CommunicationError:
    CALL(aDoNameCardSwap_ClearScreen);
    LD_HL(mDoNameCardSwap_NameCardCommErrorText);
    CALL(aPrintText);
    JP(mDoNameCardSwap);


PrintTextAndExit:
    CALL(aPrintText);
    LD_A(LCDC_DEFAULT);
    LDH_addr_A(rLCDC);
    RET;


String_PressAToLink_BToCancel_JP:
    //db ['"エーボタン<WO>おすと"'];
    //next ['"つうしん<PKMN>おこなわれるよ！"']
    //next ['"ビーボタン<WO>おすと"']
    //next ['"つうしん<WO>ちゅうし\u3000します"']
    //db ['"@"'];


NameCardReceivedCardText:
    //text_far ['_NameCardReceivedCardText']
    //text_end ['?']


NameCardListedCardText:
    //text_far ['_NameCardListedCardText']
    //text_end ['?']


NameCardNotRegisteredCardText:
    //text_far ['_NameCardNotRegisteredCardText']
    //text_end ['?']


NameCardLinkCancelledText:
    //text_far ['_NameCardLinkCancelledText']
    //text_end ['?']


NameCardCommErrorText:
    //text_far ['_NameCardLinkCommErrorText']
    //text_end ['?']


ClearScreen:
    CALL(aClearSprites);
    CALL(aClearTilemap);
    CALL(aEnableLCD);
    CALL(aWaitBGMap);
    LD_B(SCGB_DIPLOMA);
    CALL(aGetSGBLayout);
    CALL(aSetPalettes);
    RET;

}

void StageDataForNameCard(void){
    LD_DE(wMysteryGiftStaging);
    LD_A(BANK(sPlayerData));
    CALL(aOpenSRAM);
    LD_HL(sPlayerData + wPlayerName - wPlayerData);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    LD_HL(sPlayerData + wPlayerID - wPlayerData);
    LD_BC(2);
    CALL(aCopyBytes);
    LD_HL(sPlayerData + wSecretID - wPlayerData);
    LD_BC(2);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    LD_A(BANK(sCrystalData));
    CALL(aOpenSRAM);
    LD_A_addr(sCrystalData + 0);
    LD_de_A;
    INC_DE;
    LD_A(BANK(s4_a603));  // aka BANK(s4_a007) // MBC30 bank used by JP Crystal// inaccessible by MBC3
    CALL(aOpenSRAM);
    LD_HL(s4_a603);  // address of MBC30 bank
    LD_BC(8);
    CALL(aCopyBytes);
    LD_HL(s4_a007);  // address of MBC30 bank
    LD_BC(12);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void InitNameCardLayout(void){
    CALL(aClearBGPalettes);
    CALL(aDisableLCD);
    LD_HL(mCardTradeGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x00);
    LD_A(BANK(aCardTradeGFX));
    LD_BC(0x40 * LEN_2BPP_TILE);
    CALL(aFarCopyBytes);
    LD_HL(mCardTradeSpriteGFX);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x00);
    LD_A(BANK(aCardTradeSpriteGFX));
    LD_BC(8 * LEN_2BPP_TILE);
    CALL(aFarCopyBytes);
    hlcoord(0, 0, wTilemap);
    LD_A(0x3f);
    LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    CALL(aByteFill);
    hlcoord(3, 7, wTilemap);
    LD_BC((9 << 8) | 15);
    CALL(aClearBox);
    hlcoord(0, 0, wTilemap);
    LD_A(0x0);
    LD_hli_A;
    INC_A;
    LD_hl_A;
    hlcoord(0, 1, wTilemap);
    INC_A;
    LD_hli_A;
    INC_A;
    LD_hl_A;
    hlcoord(4, 2, wTilemap);
    LD_A(0x13);
    CALL(aInitNameCardLayout_Load11Row);
    hlcoord(4, 3, wTilemap);
    LD_A(0x1e);
    CALL(aInitNameCardLayout_Load12Row);
    hlcoord(4, 4, wTilemap);
    LD_A(0x2a);
    CALL(aInitNameCardLayout_Load12Row);
    hlcoord(1, 2, wTilemap);
    LD_hl(0x4);
    hlcoord(1, 3, wTilemap);
    LD_A(0x5);
    CALL(aInitNameCardLayout_Load14Column);
    LD_A(0x9);
    hlcoord(18, 5, wTilemap);
    CALL(aInitNameCardLayout_Load11Column);
    hlcoord(2, 5, wTilemap);
    LD_A(0xb);
    CALL(aInitNameCardLayout_Load16Row);
    hlcoord(2, 16, wTilemap);
    LD_A(0x7);
    CALL(aInitNameCardLayout_Load16Row);
    hlcoord(2, 5, wTilemap);
    LD_A(0xd);
    CALL(aInitNameCardLayout_Load6Row);
    hlcoord(8, 5, wTilemap);
    LD_hl(0xc);
    hlcoord(18, 5, wTilemap);
    LD_hl(0xa);
    hlcoord(18, 16, wTilemap);
    LD_hl(0x8);
    hlcoord(1, 16, wTilemap);
    LD_hl(0x6);
    hlcoord(2, 6, wTilemap);
    LD_A(0x37);
    CALL(aInitNameCardLayout_Load16Row);
    hlcoord(2, 15, wTilemap);
    LD_A(0x3d);
    CALL(aInitNameCardLayout_Load16Row);
    hlcoord(2, 6, wTilemap);
    LD_A(0x39);
    CALL(aInitNameCardLayout_Load9Column);
    hlcoord(17, 6, wTilemap);
    LD_A(0x3b);
    CALL(aInitNameCardLayout_Load9Column);
    hlcoord(2, 6, wTilemap);
    LD_hl(0x36);
    hlcoord(17, 6, wTilemap);
    LD_hl(0x38);
    hlcoord(2, 15, wTilemap);
    LD_hl(0x3c);
    hlcoord(17, 15, wTilemap);
    LD_hl(0x3e);
    LD_DE(wVirtualOAMSprite00);
    LD_HL(mInitNameCardLayout_NameCardOAMData);
    LD_BC(16 * SPRITEOAMSTRUCT_LENGTH);
    CALL(aCopyBytes);
    CALL(aEnableLCD);
    CALL(aWaitBGMap);
    LD_B(CRYSTAL_CGB_NAME_CARD);
    FARCALL(aGetCrystalCGBLayout);
    JP(mSetPalettes);


Load6Row:
    LD_B(6);
    goto row_loop;


Load11Row:
    LD_B(11);
    goto row_loop;


Load12Row:
    LD_B(12);


row_loop:
    LD_hli_A;
    INC_A;
    DEC_B;
    IF_NZ goto row_loop;
    RET;


Load9Column:
    LD_B(9);
    goto column_loop;


Load11Column:
    LD_B(11);
    goto column_loop;


Load14Column:
    LD_B(14);


column_loop:
    LD_hl_A;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto column_loop;
    RET;


Load16Row:
    LD_B(16);

row_loop_no_inc:
    LD_hli_A;
    DEC_B;
    IF_NZ goto row_loop_no_inc;
    RET;


NameCardOAMData:
    //dbsprite ['6', '2', '4', '1', '0x00', '0']
    //dbsprite ['7', '2', '4', '1', '0x01', '0']
    //dbsprite ['8', '2', '4', '1', '0x02', '0']
    //dbsprite ['9', '2', '4', '1', '0x03', '0']
    //dbsprite ['6', '3', '4', '1', '0x04', '0']
    //dbsprite ['7', '3', '4', '1', '0x05', '0']
    //dbsprite ['8', '3', '4', '1', '0x06', '0']
    //dbsprite ['9', '3', '4', '1', '0x07', '0']
    //dbsprite ['11', '0', '4', '1', '0x00', '0']
    //dbsprite ['12', '0', '4', '1', '0x01', '0']
    //dbsprite ['13', '0', '4', '1', '0x02', '0']
    //dbsprite ['14', '0', '4', '1', '0x03', '0']
    //dbsprite ['11', '1', '4', '1', '0x04', '0']
    //dbsprite ['12', '1', '4', '1', '0x05', '0']
    //dbsprite ['13', '1', '4', '1', '0x06', '0']
    //dbsprite ['14', '1', '4', '1', '0x07', '0']

    return CardTradeGFX();
}

void CardTradeGFX(void){
// INCBIN "gfx/mystery_gift/card_trade.2bpp"

    return CardTradeSpriteGFX();
}

void CardTradeSpriteGFX(void){
// INCBIN "gfx/mystery_gift/card_sprite.2bpp"

}
