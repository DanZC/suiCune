#include "../../constants.h"
#include "link.h"
#include "link_trade.h"
#include "link_2.h"
#include "time_capsule.h"
#include "../gfx/crystal_layouts.h"
#include "../events/poke_seer.h"
#include "../pokemon/move_mon.h"
#include "../pokemon/evolve.h"
#include "../menus/save.h"
#include "../battle/core.h"
#include "../../home/map.h"
#include "../../home/audio.h"
#include "../../home/copy.h"
#include "../../home/delay.h"
#include "../../home/serial.h"
#include "../../home/sprite_updates.h"
#include "../../home/gfx.h"
#include "../../home/text.h"
#include "../../home/copy_tilemap.h"
#include "../../home/tilemap.h"
#include "../../home/fade.h"
#include "../../home/menu.h"
#include "../../home/names.h"
#include "../../home/map_objects.h"
#include "../../home/joypad.h"
#include "../../home/clear_sprites.h"
#include "../../home/sram.h"
#include "../../home/random.h"
#include "../../mobile/mobile_41.h"
#include "../../data/text/common.h"
#include "../../data/items/catch_rate_items.h"
#include "../../util/network.h"

#define USE_NETWORK_XCHG_BYTES 1

void LinkCommunications(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames_Conv(80);
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames_Conv(80);
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // CALL(aLoadFontsBattleExtra);
    LoadFontsBattleExtra_Conv();
    // FARCALL(aLinkComms_LoadPleaseWaitTextboxBorderGFX);
    LinkComms_LoadPleaseWaitTextboxBorderGFX();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // hlcoord(3, 8, wTilemap);
    // LD_B(2);
    // LD_C(12);
    // LD_D_H;
    // LD_E_L;
    // FARCALL(aLinkTextbox2);
    LinkTextbox2_Conv(coord(3, 8, wram->wTilemap), 2, 12);
    // hlcoord(4, 10, wTilemap);
    // LD_DE(mString_PleaseWait);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_PleaseWait), coord(4, 10, wram->wTilemap));
    // CALL(aSetTradeRoomBGPals);
    SetTradeRoomBGPals();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // LD_HL(wLinkByteTimeout);
    //assert ['LOW(SERIAL_LINK_BYTE_TIMEOUT) == 0'];
    // XOR_A_A;  // LOW(SERIAL_LINK_BYTE_TIMEOUT)
    // LD_hli_A;
    // LD_hl(HIGH(SERIAL_LINK_BYTE_TIMEOUT));
    wram->wLinkByteTimeout = SERIAL_LINK_BYTE_TIMEOUT;
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_TIMECAPSULE);
    if(wram->wLinkMode == LINK_TIMECAPSULE) {
        return Gen2ToGen1LinkComms();
    }
    // JP_NZ (mGen2ToGen2LinkComms);

    return Gen2ToGen2LinkComms();
}

void Gen2ToGen1LinkComms(void){
    CALL(aClearLinkData);
    CALL(aLink_PrepPartyData_Gen1);
    CALL(aFixDataForLinkTransfer);
    XOR_A_A;
    LD_addr_A(wPlayerLinkAction);
    CALL(aWaitLinkTransfer);
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    IF_NZ goto player_1;

    LD_C(3);
    CALL(aDelayFrames);
    XOR_A_A;
    LDH_addr_A(hSerialSend);
    LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);

    CALL(aDelayFrame);
    XOR_A_A;
    LDH_addr_A(hSerialSend);
    LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);


player_1:
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    LD_C(3);
    CALL(aDelayFrames);
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A(1 << SERIAL);
    LDH_addr_A(rIE);

    LD_HL(wLinkBattleRNPreamble);
    LD_DE(wEnemyMon);
    LD_BC(SERIAL_RN_PREAMBLE_LENGTH + SERIAL_RNS_LENGTH);
    CALL(aSerial_ExchangeBytes);
    LD_A(SERIAL_NO_DATA_BYTE);
    LD_de_A;

    LD_HL(wLinkData);
    LD_DE(wOTPartyData);
    LD_BC(SERIAL_PREAMBLE_LENGTH + NAME_LENGTH + 1 + PARTY_LENGTH + 1 + (REDMON_STRUCT_LENGTH + NAME_LENGTH * 2) * PARTY_LENGTH + 3);
    CALL(aSerial_ExchangeBytes);
    LD_A(SERIAL_NO_DATA_BYTE);
    LD_de_A;

    LD_HL(wPlayerPatchLists);
    LD_DE(wOTPatchLists);
    LD_BC(200);
    CALL(aSerial_ExchangeBytes);

    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A((1 << JOYPAD) | (1 << SERIAL) | (1 << TIMER) | (1 << VBLANK));
    LDH_addr_A(rIE);

    CALL(aLink_CopyRandomNumbers);

    LD_HL(wOTPartyData);
    CALL(aLink_FindFirstNonControlCharacter_SkipZero);
    PUSH_HL;
    LD_BC(NAME_LENGTH);
    ADD_HL_BC;
    LD_A_hl;
    POP_HL;
    AND_A_A;
    JP_Z (mExitLinkCommunications);
    CP_A(0x7);
    JP_NC (mExitLinkCommunications);

    LD_DE(wLinkData);
    LD_BC(NAME_LENGTH + 1 + PARTY_LENGTH + 1 + (REDMON_STRUCT_LENGTH + NAME_LENGTH * 2) * PARTY_LENGTH + 3);
    CALL(aLink_CopyOTData);

    LD_DE(wOTPatchLists);
    LD_HL(wLinkPatchList1);
    LD_C(2);

loop:
    LD_A_de;
    INC_DE;
    AND_A_A;
    IF_Z goto loop;
    CP_A(SERIAL_PREAMBLE_BYTE);
    IF_Z goto loop;
    CP_A(SERIAL_NO_DATA_BYTE);
    IF_Z goto loop;
    CP_A(SERIAL_PATCH_LIST_PART_TERMINATOR);
    IF_Z goto next;
    PUSH_HL;
    PUSH_BC;
    LD_B(0);
    DEC_A;
    LD_C_A;
    ADD_HL_BC;
    LD_A(SERIAL_NO_DATA_BYTE);
    LD_hl_A;
    POP_BC;
    POP_HL;
    goto loop;


next:
    LD_HL(wLinkPatchList2);
    DEC_C;
    IF_NZ goto loop;

    LD_HL(wLinkPlayerName);
    LD_DE(wOTPlayerName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);

    LD_DE(wOTPartyCount);
    LD_A_hli;
    LD_de_A;
    INC_DE;


party_loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done_party;
    LD_addr_A(wTempSpecies);
    PUSH_HL;
    PUSH_DE;
    CALLFAR(aConvertMon_1to2);
    POP_DE;
    POP_HL;
    LD_A_addr(wTempSpecies);
    LD_de_A;
    INC_DE;
    goto party_loop;


done_party:
    LD_de_A;
    LD_HL(wTimeCapsulePlayerData);
    CALL(aLink_ConvertPartyStruct1to2);

    LD_A(LOW(wOTPartyMonOTs));
    LD_addr_A(wUnusedNamesPointer);
    LD_A(HIGH(wOTPartyMonOTs));
    LD_addr_A(wUnusedNamesPointer + 1);

    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    LD_C(66);
    CALL_Z (aDelayFrames);
    LD_DE(MUSIC_ROUTE_30);
    CALL(aPlayMusic);
    JP(mInitTradeMenuDisplay);

}

void Gen2ToGen2LinkComms(void){
    // CALL(aClearLinkData);
    ClearLinkData();
    // CALL(aLink_PrepPartyData_Gen2);
    Link_PrepPartyData_Gen2();
    // CALL(aFixDataForLinkTransfer);
    FixDataForLinkTransfer();
    // CALL(aCheckLinkTimeout_Gen2);
    CheckLinkTimeout_Gen2();
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // JP_Z (mLinkTimeout);
    if(wram->wScriptVar == FALSE) 
        return LinkTimeout();
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_INTERNAL_CLOCK);
    // IF_NZ goto player_1;
    if(hram->hSerialConnectionStatus == USING_INTERNAL_CLOCK) {
        // LD_C(3);
        // CALL(aDelayFrames);
        // DelayFrames_Conv(3);
        // XOR_A_A;
        // LDH_addr_A(hSerialSend);
        hram->hSerialSend = 0;
        // LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CLOCK));
        // LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CLOCK));
        // Network_SendByte(0);

        // CALL(aDelayFrame);
        // DelayFrame();
        // XOR_A_A;
        // LDH_addr_A(hSerialSend);
        hram->hSerialSend = 0;
        // LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CLOCK));
        // LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CLOCK));
        // Network_SendByte(0);
    }

// player_1:
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_NONE);
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames_Conv(3);
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // LD_A(1 << SERIAL);
    // LDH_addr_A(rIE);
    gb_write(rIE, (1 << SERIAL));

    uint8_t* de;
    // LD_HL(wLinkBattleRNPreamble);
    // LD_DE(wEnemyMon);
    // LD_BC(SERIAL_RN_PREAMBLE_LENGTH + SERIAL_RNS_LENGTH);
    // CALL(aSerial_ExchangeBytes);
    Network_SafeExchangeBytes(&wram->wEnemyMon, wram->wLinkBattleRNs, SERIAL_RNS_LENGTH);
    // LD_A(SERIAL_NO_DATA_BYTE);
    // LD_de_A;

    // LD_HL(wLinkData);
    // LD_DE(wOTPartyData);
    // LD_BC(SERIAL_PREAMBLE_LENGTH + NAME_LENGTH + 1 + PARTY_LENGTH + 1 + 2 + (PARTYMON_STRUCT_LENGTH + NAME_LENGTH * 2) * PARTY_LENGTH + 3);
    // CALL(aSerial_ExchangeBytes);
    Network_SafeExchangeBytes(wram->wOTPlayerName, wram->wLinkPlayerName, 
        NAME_LENGTH + 1 + PARTY_LENGTH + 1 + 2 + (PARTYMON_STRUCT_LENGTH + NAME_LENGTH * 2) * PARTY_LENGTH + 3);
    // LD_A(SERIAL_NO_DATA_BYTE);
    // LD_de_A;

    // LD_HL(wPlayerPatchLists);
    // LD_DE(wOTPatchLists);
    // LD_BC(200);
    // CALL(aSerial_ExchangeBytes);
    Network_SafeExchangeBytes(wram->wOTPatchLists, wram->wPlayerPatchLists, 200);

    // LD_A_addr(wLinkMode);
    // CP_A(LINK_TRADECENTER);
    // IF_NZ goto not_trading;
    if(wram->wLinkMode == LINK_TRADECENTER) {
        // LD_HL(wLinkPlayerMail);
        // LD_DE(wLinkOTMail);
        // LD_BC(wLinkPlayerMailEnd - wLinkPlayerMail);
        // CALL(aExchangeBytes);
        Network_SafeExchangeBytes(wram->wLinkOTMailMessages, wram->wLinkPlayerMailPreamble, wLinkPlayerMailEnd - wLinkPlayerMail);
    }

// not_trading:
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // LD_A((1 << JOYPAD) | (1 << SERIAL) | (1 << TIMER) | (1 << VBLANK));
    // LDH_addr_A(rIE);
    gb_write(rIE, ((1 << JOYPAD) | (1 << SERIAL) | (1 << TIMER) | (1 << VBLANK)));
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_NONE);

    // CALL(aLink_CopyRandomNumbers);
    Link_CopyRandomNumbers();

    // LD_HL(wOTPartyData);
    // CALL(aLink_FindFirstNonControlCharacter_SkipZero);
    // LD_DE(wLinkData);
    // LD_BC(NAME_LENGTH + 1 + PARTY_LENGTH + 1 + 2 + (PARTYMON_STRUCT_LENGTH + NAME_LENGTH * 2) * PARTY_LENGTH);
    // CALL(aLink_CopyOTData);
    Link_CopyOTData_Conv(wram->wLinkData, Link_FindFirstNonControlCharacter_SkipZero(wram->wOTPlayerName), 
        NAME_LENGTH + 1 + PARTY_LENGTH + 1 + 2 + (PARTYMON_STRUCT_LENGTH + NAME_LENGTH * 2) * PARTY_LENGTH);

    // LD_DE(wPlayerTrademon);
    de = (uint8_t*)&wram->wPlayerTrademon;
    // LD_HL(wLinkPatchList1);
    uint8_t* hl = wram->wLinkPatchList1;
    // LD_C(2);
    uint8_t c = 2;

    do {
        uint8_t a;
        while(1) {
        // loop1:
            // LD_A_de;
            a = *(de++);
            // INC_DE;
            // AND_A_A;
            // IF_Z goto loop1;
            // CP_A(SERIAL_PREAMBLE_BYTE);
            // IF_Z goto loop1;
            // CP_A(SERIAL_NO_DATA_BYTE);
            // IF_Z goto loop1;
            if(a == 0 || a == SERIAL_PREAMBLE_BYTE || a == SERIAL_NO_DATA_BYTE)
                continue;
            // CP_A(SERIAL_PATCH_LIST_PART_TERMINATOR);
            // IF_Z goto next1;
            if(a == SERIAL_PATCH_LIST_PART_TERMINATOR)
                break;
            // PUSH_HL;
            // PUSH_BC;
            // LD_B(0);
            // DEC_A;
            // LD_C_A;
            // ADD_HL_BC;
            // LD_A(SERIAL_NO_DATA_BYTE);
            // LD_hl_A;
            hl[a - 1] = SERIAL_NO_DATA_BYTE;
            // POP_BC;
            // POP_HL;
            // goto loop1;
        }

    // next1:
        // LD_HL(wLinkPatchList2);
        hl = wram->wLinkPatchList2;
        // DEC_C;
        // IF_NZ goto loop1;
    } while(--c != 0);

    // LD_A_addr(wLinkMode);
    // CP_A(LINK_TRADECENTER);
    // JP_NZ (mGen2ToGen2LinkComms_skip_mail);
// TODO: Finish converting this section. For now, mail will not be copyed.
#if 0
    if(wram->wLinkMode == LINK_TRADECENTER) {
        hl = wram->wLinkOTMailMessages;
        // LD_HL(wLinkOTMail);
        uint8_t a;

        do {
        // loop2:
            // LD_A_hli;
            a = *(hl++);
            // CP_A(SERIAL_MAIL_PREAMBLE_BYTE);
            // IF_NZ goto loop2;
        } while(a != SERIAL_MAIL_PREAMBLE_BYTE);

        do {
        // loop3:
            // LD_A_hli;
            a = *(hl++);
            // CP_A(SERIAL_NO_DATA_BYTE);
            // IF_Z goto loop3;
            // CP_A(SERIAL_MAIL_PREAMBLE_BYTE);
            // IF_Z goto loop3;
        } while(a == SERIAL_NO_DATA_BYTE || a == SERIAL_MAIL_PREAMBLE_BYTE);
        // DEC_HL;
        hl--;
        // LD_DE(wLinkOTMail);
        // LD_BC(wLinkDataEnd - wLinkOTMail);  // should be wLinkOTMailEnd - wLinkOTMail
        // CALL(aCopyBytes);
        CopyBytes_Conv2(wram->wLinkOTMailMessages, hl, sizeof(wram->wLinkOTMailMessages) + sizeof(wram->wLinkOTMailMetadata) + sizeof(wram->wOTPlayerMailPatchSet));
        // LD_HL(wLinkOTMail);
        hl = wram->wLinkOTMailMessages;
        // LD_BC((MAIL_MSG_LENGTH + 1) * PARTY_LENGTH);
        uint16_t bc = (MAIL_MSG_LENGTH + 1) * PARTY_LENGTH;

        do {
        // loop4:
            // LD_A_hl;
            // CP_A(SERIAL_MAIL_REPLACEMENT_BYTE);
            // IF_NZ goto okay1;
            // LD_hl(SERIAL_NO_DATA_BYTE);
            if(*hl == SERIAL_MAIL_REPLACEMENT_BYTE)
                *hl = SERIAL_NO_DATA_BYTE;

        // okay1:
            // INC_HL;
            // DEC_BC;
            // LD_A_B;
            // OR_A_C;
            // IF_NZ goto loop4;
        } while(hl++, --bc != 0);
        LD_DE(wOTPlayerMailPatchSet);

    loop5:
        LD_A_de;
        INC_DE;
        CP_A(SERIAL_PATCH_LIST_PART_TERMINATOR);
        IF_Z goto start_copying_mail;
        LD_HL(wLinkOTMailMetadata);
        DEC_A;
        LD_B(0);
        LD_C_A;
        ADD_HL_BC;
        LD_hl(SERIAL_NO_DATA_BYTE);
        goto loop5;


    start_copying_mail:
        LD_HL(wLinkOTMail);
        LD_DE(wLinkReceivedMail);
        LD_B(PARTY_LENGTH);

    copy_mail_loop:
        PUSH_BC;
        LD_BC(MAIL_MSG_LENGTH + 1);
        CALL(aCopyBytes);
        LD_A(LOW(MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1)));
        ADD_A_E;
        LD_E_A;
        LD_A(HIGH(MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1)));
        ADC_A_D;
        LD_D_A;
        POP_BC;
        DEC_B;
        IF_NZ goto copy_mail_loop;
        LD_DE(wLinkReceivedMail);
        LD_B(PARTY_LENGTH);

    copy_author_loop:
        PUSH_BC;
        LD_A(LOW(MAIL_MSG_LENGTH + 1));
        ADD_A_E;
        LD_E_A;
        LD_A(HIGH(MAIL_MSG_LENGTH + 1));
        ADC_A_D;
        LD_D_A;
        LD_BC(MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1));
        CALL(aCopyBytes);
        POP_BC;
        DEC_B;
        IF_NZ goto copy_author_loop;
        LD_B(PARTY_LENGTH);
        LD_DE(wLinkReceivedMail);

    fix_mail_loop:
        PUSH_BC;
        PUSH_DE;
        FARCALL(aIsMailEuropean);
        LD_A_C;
        OR_A_A;
        IF_Z goto next;
        SUB_A(0x3);
        IF_NC goto skip;
        FARCALL(aConvertEnglishMailToFrenchGerman);
        goto next;


    skip:
        CP_A(0x2);
        IF_NC goto next;
        FARCALL(aConvertEnglishMailToSpanishItalian);


    next:
        POP_DE;
        LD_HL(MAIL_STRUCT_LENGTH);
        ADD_HL_DE;
        LD_D_H;
        LD_E_L;
        POP_BC;
        DEC_B;
        IF_NZ goto fix_mail_loop;
        LD_DE(wLinkReceivedMailEnd);
        XOR_A_A;
        LD_de_A;
    }
#endif
// skip_mail:
    // LD_HL(wLinkPlayerName);
    hl = wram->wLinkPlayerName;
    // LD_DE(wOTPlayerName);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wOTPlayerName, hl, NAME_LENGTH);
    hl += NAME_LENGTH;

    // LD_DE(wOTPartyCount);
    // LD_BC(1 + PARTY_LENGTH + 1);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(&wram->wOTPartyCount, hl, 1 + PARTY_LENGTH + 1);
    hl += 1 + PARTY_LENGTH + 1;

    // LD_DE(wOTPlayerID);
    // LD_BC(2);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(&wram->wOTPlayerID, hl, 2);
    hl += 2;

    // LD_DE(wOTPartyMons);
    // LD_BC(wOTPartyDataEnd - wOTPartyMons);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wOTPartyMon, hl, wOTPartyDataEnd - wOTPartyMons);
    hl += wOTPartyDataEnd - wOTPartyMons;


    // LD_A(LOW(wOTPartyMonOTs));
    // LD_addr_A(wUnusedNamesPointer);
    // LD_A(HIGH(wOTPartyMonOTs));
    // LD_addr_A(wUnusedNamesPointer + 1);

    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic_Conv(MUSIC_NONE);
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_INTERNAL_CLOCK);
    if(hram->hSerialConnectionStatus == USING_INTERNAL_CLOCK) {
        // LD_C(66);
        // CALL_Z (aDelayFrames);
        DelayFrames_Conv(66);
    }
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_COLOSSEUM);
    // IF_NZ goto ready_to_trade;
    if(wram->wLinkMode == LINK_COLOSSEUM) {
        // LD_A(CAL);
        // LD_addr_A(wOtherTrainerClass);
        wram->wOtherTrainerClass = (bit_test(gOtherPlayerGender, PLAYERGENDER_FEMALE_F))? JODI: CAL;
        // CALL(aClearScreen);
        ClearScreen_Conv2();
        // FARCALL(aLink_WaitBGMap);
        Link_WaitBGMap();

        // LD_HL(wOptions);
        // LD_A_hl;
        // PUSH_AF;
        uint8_t options = wram->wOptions;
        // AND_A(1 << STEREO);
        // OR_A(TEXT_DELAY_MED);
        // LD_hl_A;
        wram->wOptions = (options & (1 << STEREO)) | TEXT_DELAY_MED;
        // LD_HL(wOTPlayerName);
        // LD_DE(wOTClassName);
        // LD_BC(NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(wram->wOTClassName, wram->wOTPlayerName, NAME_LENGTH);
        // CALL(aReturnToMapFromSubmenu);
        ReturnToMapFromSubmenu();
        // LD_A_addr(wDisableTextAcceleration);
        // PUSH_AF;
        uint8_t disableTextAcc = wram->wDisableTextAcceleration;
        // LD_A(1);
        // LD_addr_A(wDisableTextAcceleration);
        wram->wDisableTextAcceleration = 1;
        // LDH_A_addr(rIE);
        // PUSH_AF;
        uint8_t rie = gb_read(rIE);
        // LDH_A_addr(rIF);
        // PUSH_AF;
        uint8_t rif = gb_read(rIF);
        // XOR_A_A;
        // LDH_addr_A(rIF);
        gb_write(rIF, 0);
        // LDH_A_addr(rIE);
        // SET_A(LCD_STAT);
        // LDH_addr_A(rIE);
        uint8_t temp = gb_read(rIE);
        bit_set(temp, LCD_STAT);
        gb_write(rIE, temp);
        // POP_AF;
        // LDH_addr_A(rIF);
        gb_write(rIF, rif);

    // LET'S DO THIS
        // PREDEF(pStartBattle);
        StartBattle_Conv();

        // LDH_A_addr(rIF);
        // LD_H_A;
        rif = gb_read(rIF);
        // XOR_A_A;
        // LDH_addr_A(rIF);
        gb_write(rIF, 0);
        // POP_AF;
        // LDH_addr_A(rIE);
        gb_write(rIE, rie);
        // LD_A_H;
        // LDH_addr_A(rIF);
        gb_write(rIF, rif);
        // POP_AF;
        // LD_addr_A(wDisableTextAcceleration);
        wram->wDisableTextAcceleration = disableTextAcc;
        // POP_AF;
        // LD_addr_A(wOptions);
        wram->wOptions = options;

        // FARCALL(aLoadPokemonData);
        LoadPokemonData();
        // JP(mExitLinkCommunications);
        return ExitLinkCommunications();
    }
    else {
    // ready_to_trade:
        // LD_DE(MUSIC_ROUTE_30);
        // CALL(aPlayMusic);
        PlayMusic_Conv(MUSIC_ROUTE_30);
        // JP(mInitTradeMenuDisplay);
        return InitTradeMenuDisplay();
    }
}

void LinkTimeout(void){
    static const txt_cmd_s LinkTimeoutText[] = {
        text_far(v_LinkTimeoutText)
        text_end
    };
    // LD_DE(mLinkTimeout_LinkTimeoutText);
    // LD_B(10);
    uint8_t b = 10;

    do {
    // loop:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aLinkDataReceived);
        LinkDataReceived();
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // XOR_A_A;
    // LD_hld_A;
    // LD_hl_A;
    wram->wLinkTimeoutFrames = 0;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0;
    // PUSH_DE;
    // hlcoord(0, 12, wTilemap);
    // LD_B(4);
    // LD_C(18);
    // PUSH_DE;
    // LD_D_H;
    // LD_E_L;
    // FARCALL(aLinkTextbox2);
    LinkTextbox2_Conv(coord(0, 12, wram->wTilemap), 4, 18);
    // POP_DE;
    // POP_HL;
    // bccoord(1, 14, wTilemap);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), LinkTimeoutText);
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight_Conv();
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // RET;
}

void ExchangeBytes(void){
//  This is similar to Serial_ExchangeBytes,
//  but without a SERIAL_PREAMBLE_BYTE check.
    LD_A(TRUE);
    LDH_addr_A(hSerialIgnoringInitialData);

loop:
    LD_A_hl;
    LDH_addr_A(hSerialSend);
    CALL(aSerial_ExchangeByte);
    PUSH_BC;
    LD_B_A;
    INC_HL;
    LD_A(48);

wait:
    DEC_A;
    IF_NZ goto wait;
    LDH_A_addr(hSerialIgnoringInitialData);
    AND_A_A;
    LD_A_B;
    POP_BC;
    IF_Z goto load;
    DEC_HL;
    XOR_A_A;
    LDH_addr_A(hSerialIgnoringInitialData);
    goto loop;


load:
    LD_de_A;
    INC_DE;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    RET;

}

//  This is similar to Serial_ExchangeBytes,
//  but without a SERIAL_PREAMBLE_BYTE check.
void ExchangeBytes_Conv(void* de_, const void* hl_, uint16_t bc){
    uint8_t* de = de_;
    const uint8_t* hl = hl_;
    // LD_A(TRUE);
    // LDH_addr_A(hSerialIgnoringInitialData);
    hram->hSerialIgnoringInitialData = TRUE;

    while(1) {
    // loop:
        // LD_A_hl;
        // LDH_addr_A(hSerialSend);
        hram->hSerialSend = *hl;
        // CALL(aSerial_ExchangeByte);
        uint8_t byte = Serial_ExchangeByte_Conv(hl);
        // PUSH_BC;
        // LD_B_A;
        // INC_HL;
        hl++;
        // LD_A(48);

        // wait:
            // DEC_A;
            // IF_NZ goto wait;
        // LDH_A_addr(hSerialIgnoringInitialData);
        // AND_A_A;
        // LD_A_B;
        // POP_BC;
        // IF_Z goto load;
        if(hram->hSerialIgnoringInitialData == FALSE) {
        // load:
            // LD_de_A;
            // INC_DE;
            *(de++) = byte;
            // DEC_BC;
            // LD_A_B;
            // OR_A_C;
            // IF_NZ goto loop;
            if(--bc != 0)
                continue;
            // RET;
            return;
        }
        // DEC_HL;
        --hl;
        // XOR_A_A;
        // LDH_addr_A(hSerialIgnoringInitialData);
        hram->hSerialIgnoringInitialData = FALSE;
        // goto loop;
    }
}

const char String_PleaseWait[] = "PLEASE WAIT!@";

void ClearLinkData(void){
    // LD_HL(wLinkData);
    // LD_BC(wLinkDataEnd - wLinkData);
    static_assert(sizeof(wram->wLinkData) == wLinkDataEnd - wLinkData, "");

    for(uint32_t i = 0; i < sizeof(wram->wLinkData); ++i) {
    // loop:
        // XOR_A_A;
        // LD_hli_A;
        wram->wLinkData[i] = 0;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    }
    // RET;
}

void FixDataForLinkTransfer(void){
    // LD_HL(wLinkBattleRNPreamble);
    // LD_A(SERIAL_PREAMBLE_BYTE);
    // LD_B(SERIAL_RN_PREAMBLE_LENGTH);

    for(uint32_t i = 0; i < SERIAL_RN_PREAMBLE_LENGTH; ++i) {
    // preamble_loop:
        // LD_hli_A;
        wram->wLinkBattleRNPreamble[i] = 0;
        // DEC_B;
        // IF_NZ goto preamble_loop;
    }

    //assert ['wLinkBattleRNPreamble + SERIAL_RN_PREAMBLE_LENGTH == wLinkBattleRNs'];
    uint8_t* hl = wram->wLinkBattleRNPreamble;
    // LD_B(SERIAL_RNS_LENGTH);
    uint8_t b = SERIAL_RNS_LENGTH;

    do {
    // rn_loop:
        uint8_t num;
        do {
            // CALL(aRandom);
            num = Random_Conv();
            // CP_A(SERIAL_PREAMBLE_BYTE);
            // IF_NC goto rn_loop;
        } while(num >= SERIAL_PREAMBLE_BYTE);
        // LD_hli_A;
        *(hl++) = num;
        // DEC_B;
        // IF_NZ goto rn_loop;
    } while(--b != 0);

    // LD_HL(wPlayerPatchLists);
    hl = wram->wPlayerPatchLists;
    // LD_A(SERIAL_PREAMBLE_BYTE);
    // LD_hli_A;
    *(hl++) = SERIAL_PREAMBLE_BYTE;
    // LD_hli_A;
    *(hl++) = SERIAL_PREAMBLE_BYTE;
    // LD_hli_A;
    *(hl++) = SERIAL_PREAMBLE_BYTE;

    // LD_B(200);
    b = 200;
    // XOR_A_A;

    do {
    // loop1:
        // LD_hli_A;
        *(hl++) = 0;
        // DEC_B;
        // IF_NZ goto loop1;
    } while(--b != 0);

    // LD_HL((wLinkData + SERIAL_PREAMBLE_LENGTH + NAME_LENGTH + 1 + PARTY_LENGTH + 1) - 1);
    hl = (wram->wLinkData + SERIAL_PREAMBLE_LENGTH + NAME_LENGTH + 1 + PARTY_LENGTH + 1) - 1;
    // LD_DE(wPlayerPatchLists + 10);  // ???
    uint8_t* de = wram->wPlayerPatchLists + 10;
    // LD_BC((0 << 8) | 0);
    b = 0;
    uint8_t c = 0;

    while(1) {
    // loop2:
        // INC_C;
        c++;
        // LD_A_C;
        // CP_A(SERIAL_PATCH_LIST_LENGTH + 1);
        // IF_Z goto next1;
        if(c == SERIAL_PATCH_LIST_LENGTH + 1) {
        // next1:
            // LD_A(SERIAL_PATCH_LIST_PART_TERMINATOR);
            // LD_de_A;
            *(de++) = SERIAL_PATCH_LIST_PART_TERMINATOR;
            // INC_DE;
            // LD_BC((1 << 8) | 0);
            b = 1;
            c = 0;
            // goto loop2;
            continue;
        }
        // LD_A_B;
        // DEC_A;
        // IF_NZ goto next2;
        if(b == 1) {
            // PUSH_BC;
            // LD_A_addr(wLinkMode);
            // CP_A(LINK_TIMECAPSULE);
            // LD_B(REDMON_STRUCT_LENGTH * PARTY_LENGTH - SERIAL_PATCH_LIST_LENGTH + 1);
            // IF_Z goto got_value;
            // LD_B(2 + PARTYMON_STRUCT_LENGTH * PARTY_LENGTH - SERIAL_PATCH_LIST_LENGTH + 1);
            uint8_t cmp = (wram->wLinkMode == LINK_TIMECAPSULE)
                ? REDMON_STRUCT_LENGTH * PARTY_LENGTH - SERIAL_PATCH_LIST_LENGTH + 1
                : 2 + PARTYMON_STRUCT_LENGTH * PARTY_LENGTH - SERIAL_PATCH_LIST_LENGTH + 1;

        // got_value:
            // LD_A_C;
            // CP_A_B;
            // POP_BC;
            // IF_Z goto done;
            if(c == cmp)
                break;
        }

    // next2:
        // INC_HL;
        hl++;
        // LD_A_hl;
        // CP_A(SERIAL_NO_DATA_BYTE);
        // IF_NZ goto loop2;
        if(*hl == SERIAL_NO_DATA_BYTE) {
            // LD_A_C;
            // LD_de_A;
            // INC_DE;
            *(de++) = c;
            // LD_hl(SERIAL_PATCH_REPLACEMENT_BYTE);
            // goto loop2;
        }
    }

// done:
    // LD_A(SERIAL_PATCH_LIST_PART_TERMINATOR);
    // LD_de_A;
    *de = SERIAL_PATCH_LIST_PART_TERMINATOR;
    // RET;
}

void Link_PrepPartyData_Gen1(void){
    LD_DE(wLinkData);
    LD_A(SERIAL_PREAMBLE_BYTE);
    LD_B(SERIAL_PREAMBLE_LENGTH);

loop1:
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto loop1;

    LD_HL(wPlayerName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);

    PUSH_DE;
    LD_HL(wPartyCount);
    LD_A_hli;
    LD_de_A;
    INC_DE;

loop2:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done_party;
    LD_addr_A(wTempSpecies);
    PUSH_HL;
    PUSH_DE;
    CALLFAR(aConvertMon_2to1);
    POP_DE;
    POP_HL;
    LD_A_addr(wTempSpecies);
    LD_de_A;
    INC_DE;
    goto loop2;

done_party:
    LD_de_A;
    POP_DE;
    LD_HL(1 + PARTY_LENGTH + 1);
    ADD_HL_DE;

    LD_D_H;
    LD_E_L;
    LD_HL(wPartyMon1Species);
    LD_C(PARTY_LENGTH);

mon_loop:
    PUSH_BC;
    CALL(aLink_PrepPartyData_Gen1_ConvertPartyStruct2to1);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    ADD_HL_BC;
    POP_BC;
    DEC_C;
    IF_NZ goto mon_loop;

    LD_HL(wPartyMonOTs);
    CALL(aLink_PrepPartyData_Gen1_copy_ot_nicks);

    LD_HL(wPartyMonNicknames);

copy_ot_nicks:
    LD_BC(PARTY_LENGTH * NAME_LENGTH);
    JP(mCopyBytes);


ConvertPartyStruct2to1:
    LD_B_H;
    LD_C_L;
    PUSH_DE;
    PUSH_BC;
    LD_A_hl;
    LD_addr_A(wTempSpecies);
    CALLFAR(aConvertMon_2to1);
    POP_BC;
    POP_DE;
    LD_A_addr(wTempSpecies);
    LD_de_A;
    INC_DE;
    LD_HL(MON_HP);
    ADD_HL_BC;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    INC_DE;
    XOR_A_A;
    LD_de_A;
    INC_DE;
    LD_HL(MON_STATUS);
    ADD_HL_BC;
    LD_A_hl;
    LD_de_A;
    INC_DE;
    LD_A_bc;
    CP_A(MAGNEMITE);
    IF_Z goto steel_type;
    CP_A(MAGNETON);
    IF_NZ goto skip_steel;


steel_type:
    LD_A(ELECTRIC);
    LD_de_A;
    INC_DE;
    LD_de_A;
    INC_DE;
    goto done_steel;


skip_steel:
    PUSH_BC;
    DEC_A;
    LD_HL(mBaseData + BASE_TYPES);
    LD_BC(BASE_DATA_SIZE);
    CALL(aAddNTimes);
    LD_BC(BASE_CATCH_RATE - BASE_TYPES);
    LD_A(BANK(aBaseData));
    CALL(aFarCopyBytes);
    POP_BC;


done_steel:
    PUSH_BC;
    LD_HL(MON_ITEM);
    ADD_HL_BC;
    LD_BC(MON_HAPPINESS - MON_ITEM);
    CALL(aCopyBytes);
    POP_BC;

    LD_HL(MON_LEVEL);
    ADD_HL_BC;
    LD_A_hl;
    LD_de_A;
    LD_addr_A(wCurPartyLevel);
    INC_DE;

    PUSH_BC;
    LD_HL(MON_MAXHP);
    ADD_HL_BC;
    LD_BC(MON_SAT - MON_MAXHP);
    CALL(aCopyBytes);
    POP_BC;

    PUSH_DE;
    PUSH_BC;

    LD_A_bc;
    DEC_A;
    PUSH_BC;
    LD_B(0);
    LD_C_A;
    LD_HL(mKantoMonSpecials);
    ADD_HL_BC;
    LD_A(BANK(aKantoMonSpecials));
    CALL(aGetFarByte);
    LD_addr_A(wBaseSpecialAttack);
    POP_BC;

    LD_HL(MON_STAT_EXP - 1);
    ADD_HL_BC;
    LD_C(STAT_SATK);
    LD_B(TRUE);
    PREDEF(pCalcMonStatC);

    POP_BC;
    POP_DE;

    LDH_A_addr(hQuotient + 2);
    LD_de_A;
    INC_DE;
    LDH_A_addr(hQuotient + 3);
    LD_de_A;
    INC_DE;
    LD_H_B;
    LD_L_C;
    RET;

}

void Link_PrepPartyData_Gen2(void){
    // LD_DE(wLinkData);
    uint8_t* de = wram->wLinkData;
    // LD_A(SERIAL_PREAMBLE_BYTE);
    // LD_B(SERIAL_PREAMBLE_LENGTH);
    uint8_t b = SERIAL_PREAMBLE_LENGTH;

    do {
    // loop1:
        // LD_de_A;
        *(de++) = SERIAL_PREAMBLE_BYTE;
        // INC_DE;
        // DEC_B;
        // IF_NZ goto loop1;
    } while(--b != 0);

    // LD_HL(wPlayerName);
    // LD_BC(NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(de, wram->wPlayerName, NAME_LENGTH);
    de += NAME_LENGTH;

    CopyBytes_Conv2(de, &wram->wPartyCount, sizeof(wram->wPartyCount));
    de += sizeof(wram->wPartyCount);
    // LD_HL(wPartyCount);
    // LD_BC(1 + PARTY_LENGTH + 1);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(de, &wram->wPartySpecies, sizeof(wram->wPartySpecies));
    de += sizeof(wram->wPartySpecies);
    CopyBytes_Conv2(de, &wram->wPartyEnd, sizeof(wram->wPartyEnd));
    de += sizeof(wram->wPartyEnd);

    // LD_HL(wPlayerID);
    // LD_BC(2);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(de, &wram->wPlayerID, sizeof(wram->wPlayerID));
    de += sizeof(wram->wPlayerID);

    // LD_HL(wPartyMon1Species);
    // LD_BC(PARTY_LENGTH * PARTYMON_STRUCT_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(de, wram->wPartyMon, sizeof(wram->wPartyMon));
    de += sizeof(wram->wPartyMon);

    // LD_HL(wPartyMonOTs);
    // LD_BC(PARTY_LENGTH * NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(de, wram->wPartyMonOT, sizeof(wram->wPartyMonOT));
    de += sizeof(wram->wPartyMonOT);

    // LD_HL(wPartyMonNicknames);
    // LD_BC(PARTY_LENGTH * MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(de, wram->wPartyMonNickname, sizeof(wram->wPartyMonNickname));
    de += sizeof(wram->wPartyMonNickname);

//  Okay, we did all that.  Now, are we in the trade center?
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_TRADECENTER);
    // RET_NZ ;
    if(wram->wLinkMode != LINK_TRADECENTER)
        return;

//  Fill 5 bytes at wLinkPlayerMailPreamble with $20
    // LD_DE(wLinkPlayerMailPreamble);
    // LD_A(SERIAL_MAIL_PREAMBLE_BYTE);
    // CALL(aLink_CopyMailPreamble);
    Link_CopyMailPreamble_Conv(wram->wLinkPlayerMailPreamble, SERIAL_MAIL_PREAMBLE_BYTE);

//  Copy all the mail messages to wLinkPlayerMailMessages
    // LD_A(BANK(sPartyMail));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asPartyMail));
    // LD_HL(sPartyMail);
    const struct MailMsg* hl = (const struct MailMsg*)GBToRAMAddr(sPartyMail);
    // LD_B(PARTY_LENGTH);
    b = PARTY_LENGTH;

    do {
    // loop2:
        // PUSH_BC;
        // LD_BC(MAIL_MSG_LENGTH + 1);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(de, hl->message, sizeof(hl->message));
        de += sizeof(hl->message);
        hl++;
        // LD_BC(MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1));
        // ADD_HL_BC;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop2;
    } while(--b != 0);
//  Copy the mail data to wLinkPlayerMailMetadata
    // LD_HL(sPartyMail);
    hl = (const struct MailMsg*)GBToRAMAddr(sPartyMail);
    // LD_B(PARTY_LENGTH);
    b = PARTY_LENGTH;

    do {
    // loop3:
        // PUSH_BC;
        // LD_BC(MAIL_MSG_LENGTH + 1);
        // ADD_HL_BC;
        // LD_BC(MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1));
        // CALL(aCopyBytes);
        CopyBytes_Conv2(de, hl->author, sizeof(*hl) - sizeof(hl->message));
        de += sizeof(*hl) - sizeof(hl->message);
        hl++;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop3;
    } while(--b != 0);
    // LD_B(PARTY_LENGTH);
    // LD_DE(sPartyMail);
    // LD_HL(wLinkPlayerMailMessages);

// loop4:
    // PUSH_BC;
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_HL;
    // FARCALL(aIsMailEuropean);
    // POP_DE;
    // LD_A_C;
    // OR_A_A;
    // IF_Z goto next;
    // SUB_A(0x3);
    // IF_NC goto italian_spanish;
    // FARCALL(aConvertFrenchGermanMailToEnglish);
    // goto next;

// italian_spanish:
    // CP_A(0x2);
    // IF_NC goto next;
    // FARCALL(aConvertSpanishItalianMailToEnglish);

// next:
    // POP_DE;
    // LD_HL(MAIL_STRUCT_LENGTH);
    // ADD_HL_DE;
    // LD_D_H;
    // LD_E_L;
    // POP_HL;
    // LD_BC(MAIL_MSG_LENGTH + 1);
    // ADD_HL_BC;
    // POP_BC;
    // DEC_B;
    // IF_NZ goto loop4;
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();

    // LD_HL(wLinkPlayerMailMessages);
    uint8_t* hl2 = wram->wLinkPlayerMailMessages;
    // LD_BC((MAIL_MSG_LENGTH + 1) * PARTY_LENGTH);
    uint16_t bc = sizeof(wram->wLinkPlayerMailMessages);

    do {
    // loop5:
        // LD_A_hl;
        // CP_A(SERIAL_NO_DATA_BYTE);
        // IF_NZ goto skip2;
        // LD_hl(SERIAL_MAIL_REPLACEMENT_BYTE);
        if(*hl2 == SERIAL_NO_DATA_BYTE) {
            *hl2 = SERIAL_MAIL_REPLACEMENT_BYTE;
        }

    // skip2:
        // INC_HL;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop5;
    } while(hl2++, --bc != 0);

    // LD_HL(wLinkPlayerMailMetadata);
    hl2 = wram->wLinkPlayerMailMetadata;
    // LD_DE(wLinkPlayerMailPatchSet);
    de = wram->wLinkPlayerMailPatchSet;
    // LD_B((MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1)) * PARTY_LENGTH);
    b = (MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1)) * PARTY_LENGTH;
    // LD_C(0);
    uint8_t c = 0;

    do {
    // loop6:
        // INC_C;
        c++;
        // LD_A_hl;
        // CP_A(SERIAL_NO_DATA_BYTE);
        // IF_NZ goto skip3;
        if(*hl2 == SERIAL_NO_DATA_BYTE) {
            // LD_hl(SERIAL_PATCH_REPLACEMENT_BYTE);
            *hl2 = SERIAL_PATCH_REPLACEMENT_BYTE;
            // LD_A_C;
            // LD_de_A;
            *de = c;
            // INC_DE;
            de++;
        }

    // skip3:
        // INC_HL;
        // DEC_B;
        // IF_NZ goto loop6;
    } while(hl2++, --b != 0);

    // LD_A(SERIAL_PATCH_LIST_PART_TERMINATOR);
    // LD_de_A;
    *de = SERIAL_PATCH_LIST_PART_TERMINATOR;
    // RET;
}

void Link_CopyMailPreamble(void){
//  fill 5 bytes with the value of a, starting at de
    LD_C(SERIAL_MAIL_PREAMBLE_LENGTH);

loop:
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void Link_CopyMailPreamble_Conv(uint8_t* de, uint8_t a){
//  fill 5 bytes with the value of a, starting at de
    // LD_C(SERIAL_MAIL_PREAMBLE_LENGTH);
    for(uint32_t i = 0; i < SERIAL_MAIL_PREAMBLE_LENGTH; ++i) {
    // loop:
        // LD_de_A;
        de[i] = a;
        // INC_DE;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
}

void Link_ConvertPartyStruct1to2(void){
    PUSH_HL;
    LD_D_H;
    LD_E_L;
    LD_BC(wLinkOTPartyMonTypes);
    LD_HL(wCurLinkOTPartyMonTypePointer);
    LD_A_C;
    LD_hli_A;
    LD_hl_B;
    LD_HL(wOTPartyMon1Species);
    LD_C(PARTY_LENGTH);

loop:
    PUSH_BC;
    CALL(aLink_ConvertPartyStruct1to2_ConvertToGen2);
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    POP_HL;
    LD_BC(PARTY_LENGTH * REDMON_STRUCT_LENGTH);
    ADD_HL_BC;
    LD_DE(wOTPartyMonOTs);
    LD_BC(PARTY_LENGTH * NAME_LENGTH);
    CALL(aCopyBytes);
    LD_DE(wOTPartyMonNicknames);
    LD_BC(PARTY_LENGTH * MON_NAME_LENGTH);
    JP(mCopyBytes);


ConvertToGen2:
    LD_B_H;
    LD_C_L;
    LD_A_de;
    INC_DE;
    PUSH_BC;
    PUSH_DE;
    LD_addr_A(wTempSpecies);
    CALLFAR(aConvertMon_1to2);
    POP_DE;
    POP_BC;
    LD_A_addr(wTempSpecies);
    LD_bc_A;
    LD_addr_A(wCurSpecies);
    LD_HL(MON_HP);
    ADD_HL_BC;
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_A_de;
    INC_DE;
    LD_hl_A;
    INC_DE;
    LD_HL(MON_STATUS);
    ADD_HL_BC;
    LD_A_de;
    INC_DE;
    LD_hl_A;
    LD_HL(wCurLinkOTPartyMonTypePointer);
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_A_de;
    LD_hli_A;
    INC_DE;
    LD_A_de;
    LD_hli_A;
    INC_DE;
    LD_A_L;
    LD_addr_A(wCurLinkOTPartyMonTypePointer);
    LD_A_H;
    LD_addr_A(wCurLinkOTPartyMonTypePointer + 1);
    PUSH_BC;
    LD_HL(MON_ITEM);
    ADD_HL_BC;
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    POP_DE;
    PUSH_BC;
    LD_A_hli;
    LD_B_A;
    CALL(aTimeCapsule_ReplaceTeruSama);
    LD_A_B;
    LD_de_A;
    INC_DE;
    POP_BC;
    LD_BC(0x19);
    CALL(aCopyBytes);
    POP_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(0x1f);
    ADD_HL_BC;
    LD_A_de;
    INC_DE;
    LD_hl_A;
    LD_addr_A(wCurPartyLevel);
    PUSH_BC;
    LD_HL(0x24);
    ADD_HL_BC;
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    POP_DE;
    LD_BC(8);
    CALL(aCopyBytes);
    POP_BC;
    CALL(aGetBaseData);
    PUSH_DE;
    PUSH_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(MON_STAT_EXP - 1);
    ADD_HL_BC;
    LD_C(STAT_SATK);
    LD_B(TRUE);
    PREDEF(pCalcMonStatC);
    POP_BC;
    POP_HL;
    LDH_A_addr(hQuotient + 2);
    LD_hli_A;
    LDH_A_addr(hQuotient + 3);
    LD_hli_A;
    PUSH_HL;
    PUSH_BC;
    LD_HL(MON_STAT_EXP - 1);
    ADD_HL_BC;
    LD_C(STAT_SDEF);
    LD_B(TRUE);
    PREDEF(pCalcMonStatC);
    POP_BC;
    POP_HL;
    LDH_A_addr(hQuotient + 2);
    LD_hli_A;
    LDH_A_addr(hQuotient + 3);
    LD_hli_A;
    PUSH_HL;
    LD_HL(0x1b);
    ADD_HL_BC;
    LD_A(0x46);
    LD_hli_A;
    XOR_A_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    POP_HL;
    INC_DE;
    INC_DE;
    RET;

}

void TimeCapsule_ReplaceTeruSama(void){
    LD_A_B;
    AND_A_A;
    RET_Z ;
    PUSH_HL;
    LD_HL(mTimeCapsule_CatchRateItems);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto end;
    CP_A_B;
    IF_Z goto found;
    INC_HL;
    goto loop;


found:
    LD_B_hl;


end:
    POP_HL;
    RET;

// INCLUDE "data/items/catch_rate_items.asm"

    return Link_CopyOTData();
}

item_t TimeCapsule_ReplaceTeruSama_Conv(item_t item){
    // LD_A_B;
    // AND_A_A;
    // RET_Z ;
    if(item == NO_ITEM)
        return item;
    // PUSH_HL;
    // LD_HL(mTimeCapsule_CatchRateItems);

    for(uint32_t i = 0; TimeCapsule_CatchRateItems[i] != 0; i += 2) {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto end;
        // CP_A_B;
        // IF_Z goto found;
        if(TimeCapsule_CatchRateItems[i] == item) {
        // found:
            // LD_B_hl;
            return TimeCapsule_CatchRateItems[i + 1];
        }
        // INC_HL;
        // goto loop;
    }

// end:
    // POP_HL;
    // RET;
    return item;
// INCLUDE "data/items/catch_rate_items.asm"
}

void Link_CopyOTData(void){

loop:
    LD_A_hli;
    CP_A(SERIAL_NO_DATA_BYTE);
    IF_Z goto loop;
    LD_de_A;
    INC_DE;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    RET;

}

void Link_CopyOTData_Conv(void* de_, const void* hl_, uint16_t bc){
    uint8_t* de = de_;
    const uint8_t* hl = hl_;
    uint8_t a;
    do {
    // loop:
        do {
            // LD_A_hli;
            a = *(hl++);
            // CP_A(SERIAL_NO_DATA_BYTE);
            // IF_Z goto loop;
        } while(a == SERIAL_NO_DATA_BYTE);
        // LD_de_A;
        // INC_DE;
        *(de++) = a;
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto loop;
    } while(--bc != 0);
    // RET;
}

void Link_CopyRandomNumbers(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_INTERNAL_CLOCK);
    // RET_Z ;
    if(hram->hSerialConnectionStatus == USING_INTERNAL_CLOCK)
        return;
    // LD_HL(wEnemyMonSpecies);
    // CALL(aLink_FindFirstNonControlCharacter_AllowZero);
    uint8_t* hl = (uint8_t*)Link_FindFirstNonControlCharacter_AllowZero(&wram->wEnemyMon);
    // LD_DE(wLinkBattleRNs);
    uint8_t* de = wram->wLinkBattleRNs;
    // LD_C(10);
    uint8_t c = 10;

    do {
        uint8_t a;
        do {
        // loop:
            // LD_A_hli;
            a = *(hl++);
            // CP_A(SERIAL_NO_DATA_BYTE);
            // IF_Z goto loop;
            // CP_A(SERIAL_PREAMBLE_BYTE);
            // IF_Z goto loop;
        } while(a == SERIAL_NO_DATA_BYTE || a == SERIAL_PREAMBLE_BYTE);
        // LD_de_A;
        // INC_DE;
        *(de++) = a;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

const void* Link_FindFirstNonControlCharacter_SkipZero(const void* hl_){
    const uint8_t* hl = hl_;
    uint8_t a;
    do {
    // loop:
        // LD_A_hli;
        a = *(hl++);
        // AND_A_A;
        // IF_Z goto loop;
        // CP_A(SERIAL_PREAMBLE_BYTE);
        // IF_Z goto loop;
        // CP_A(SERIAL_NO_DATA_BYTE);
        // IF_Z goto loop;
    } while(a == 0 || a == SERIAL_PREAMBLE_BYTE || a == SERIAL_NO_DATA_BYTE);
    // DEC_HL;
    // RET;
    return hl - 1;
}

const void* Link_FindFirstNonControlCharacter_AllowZero(const void* hl_){
    const uint8_t* hl = hl_;
    uint8_t a;

    do {
    // loop:
        // LD_A_hli;
        a = *(hl++);
        // CP_A(SERIAL_PREAMBLE_BYTE);
        // IF_Z goto loop;
        // CP_A(SERIAL_NO_DATA_BYTE);
        // IF_Z goto loop;
    } while(a == SERIAL_PREAMBLE_BYTE || a == SERIAL_NO_DATA_BYTE);
    // DEC_HL;
    // RET;
    return hl - 1;
}

// All functions have been combined into a single function
// to prevent stack overflow during iterative calls. 
void InitTradeMenuDisplay(void){
    static const char String_Stats_Trade[] = "STATS     TRADE@";

    static const txt_cmd_s LinkTradeCantBattleText[] = {
        text_far(v_LinkTradeCantBattleText)
        text_end
    };

    static const txt_cmd_s LinkAbnormalMonText[] = {
        text_far(v_LinkAbnormalMonText)
        text_end
    };
    tile_t* hl;
    uint8_t ctl;
    uint8_t menuY = 1;

InitTradeMenuDisplay:
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // CALL(aLoadTradeScreenBorderGFX);
    LoadTradeScreenBorderGFX();
    // FARCALL(aInitTradeSpeciesList);
    InitTradeSpeciesList();
    // XOR_A_A;
    // LD_HL(wOtherPlayerLinkMode);
    // LD_hli_A;
    wram->wOtherPlayerLinkMode = 0;
    // LD_hli_A;
    wram->wOtherPlayerLinkAction = 0;
    // LD_hli_A;
    wram->skip_49[0] = 0;
    // LD_hl_A;
    wram->skip_49[1] = 0;
    // LD_A(1);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 1;
    // INC_A;
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = 2;
    // JP(mLinkTrade_PlayerPartyMenu);
    goto LinkTrade_PlayerPartyMenu;
LinkTrade_OTPartyMenu:
    // LD_A(OTPARTYMON);
    // LD_addr_A(wMonType);
    wram->wMonType = OTPARTYMON;
    // LD_A(A_BUTTON | D_UP | D_DOWN);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = A_BUTTON | D_UP | D_DOWN;
    // LD_A_addr(wOTPartyCount);
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = wram->wOTPartyCount;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 1;
    // LD_A(9);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = 9;
    // LD_A(6);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = 6;
    // LD_A(1);
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 1;
    // LD_A((1 << 4) | 0);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = (1 << 4) | 0;
    // LD_A(MENU_UNUSED_3);
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = MENU_UNUSED_3;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0;
    goto LinkTradeOTPartymonMenuLoop;

LinkTrade_PlayerPartyMenu:
    // FARCALL(aInitMG_Mobile_LinkTradePalMap);
    InitMG_Mobile_LinkTradePalMap();
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = 0;
    // LD_A(A_BUTTON | D_UP | D_DOWN);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = A_BUTTON | D_UP | D_DOWN;
    // LD_A_addr(wPartyCount);
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = wram->wPartyCount;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 1;
    // LD_A(1);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = 1;
    // LD_A(6);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = 6;
    // LD_A(1);
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 1;
    // LD_A((1 << 4) | 0);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = (1 << 4) | 0;
    // LD_A(MENU_UNUSED_3);
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = MENU_UNUSED_3;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0;
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    goto LinkTradePartymonMenuLoop;

LinkTradePartiesMenuMasterLoop:
    // LD_A_addr(wMonType);
    // AND_A_A;
    // JP_Z (mLinkTradePartymonMenuLoop);  // PARTYMON
    if(wram->wMonType == PARTYMON)
        goto LinkTradePartymonMenuLoop;
    // JP(mLinkTradeOTPartymonMenuLoop);  // OTPARTYMON
    goto LinkTradeOTPartymonMenuLoop;

LinkTrade_TradeStatsMenu:
    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // LD_A_addr(wMenuCursorY);
    // PUSH_AF;
    menuY = wram->wMenuCursorY;
    // hlcoord(0, 15, wTilemap);
    // LD_B(1);
    // LD_C(18);
    // CALL(aLinkTextboxAtHL);
    LinkTextboxAtHL_Conv(coord(0, 15, wram->wTilemap), 1, 18);
    // hlcoord(2, 16, wTilemap);
    // LD_DE(mLinkTrade_TradeStatsMenu_String_Stats_Trade);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_Stats_Trade), coord(2, 16, wram->wTilemap));
    // FARCALL(aLink_WaitBGMap);
    Link_WaitBGMap();


joy_loop:
    // LD_A(0x7f);
    // ldcoord_a(11, 16, wTilemap);
    *coord(11, 16, wram->wTilemap) = 0x7f;
    // LD_A(A_BUTTON | B_BUTTON | D_RIGHT);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = (A_BUTTON | B_BUTTON | D_RIGHT);
    // LD_A(1);
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = 1;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 1;
    // LD_A(16);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = 16;
    // LD_A(1);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = 1;
    // LD_A(1);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 1;
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 1;
    // LD_A((2 << 4) | 0);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = (2 << 4) | 0;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = 0;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0;
    // CALL(aScrollingMenuJoypad);
    uint8_t a = ScrollingMenuJoypad_Conv();
    // BIT_A(D_RIGHT_F);
    // IF_NZ goto d_right;
    if(bit_test(a, D_RIGHT_F)) {
    // d_right:
        // LD_A(0x7f);
        // ldcoord_a(1, 16, wTilemap);
        *coord(1, 16, wram->wTilemap) = 0x7f;
        // LD_A(A_BUTTON | B_BUTTON | D_LEFT);
        // LD_addr_A(wMenuJoypadFilter);
        wram->wMenuJoypadFilter = (A_BUTTON | B_BUTTON | D_LEFT);
        // LD_A(1);
        // LD_addr_A(w2DMenuNumRows);
        wram->w2DMenuNumRows = 1;
        // LD_A(1);
        // LD_addr_A(w2DMenuNumCols);
        wram->w2DMenuNumCols = 1;
        // LD_A(16);
        // LD_addr_A(w2DMenuCursorInitY);
        wram->w2DMenuCursorInitY = 16;
        // LD_A(11);
        // LD_addr_A(w2DMenuCursorInitX);
        wram->w2DMenuCursorInitX = 11;
        // LD_A(1);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 1;
        // LD_addr_A(wMenuCursorX);
        wram->wMenuCursorX = 1;
        // LD_A((2 << 4) | 0);
        // LD_addr_A(w2DMenuCursorOffsets);
        wram->w2DMenuCursorOffsets = (2 << 4) | 0;
        // XOR_A_A;
        // LD_addr_A(w2DMenuFlags1);
        wram->w2DMenuFlags1 = 0;
        // LD_addr_A(w2DMenuFlags2);
        wram->w2DMenuFlags2 = 0;
        // CALL(aScrollingMenuJoypad);
        uint8_t joy = ScrollingMenuJoypad_Conv();
        // BIT_A(D_LEFT_F);
        // JP_NZ (mLinkTrade_TradeStatsMenu_joy_loop);
        if(bit_test(joy, D_LEFT_F))
            goto joy_loop;
        // BIT_A(B_BUTTON_F);
        // IF_NZ goto b_button;
        if(bit_test(joy, B_BUTTON_F))
            goto b_button;
        // goto try_trade;
    }
    // BIT_A(B_BUTTON_F);
    // IF_Z goto show_stats;
    else if(bit_test(a, B_BUTTON_F)) {
    b_button:
        // POP_AF;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = menuY;
        // CALL(aSafeLoadTempTilemapToTilemap);
        SafeLoadTempTilemapToTilemap_Conv();
        // JP(mLinkTrade_PlayerPartyMenu);
        goto LinkTrade_PlayerPartyMenu;
    }
    else {
    show_stats:
        // POP_AF;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = menuY;
        // LD_A(INIT_PLAYEROT_LIST);
        // LD_addr_A(wInitListType);
        // CALLFAR(aInitList);
        // FARCALL(aLinkMonStatsScreen);
        LinkMonStatsScreen();
        // CALL(aSafeLoadTempTilemapToTilemap);
        SafeLoadTempTilemapToTilemap_Conv();
        // hlcoord(6, 1, wTilemap);
        // LD_BC((6 << 8) | 1);
        // LD_A(0x7f);
        // CALL(aLinkEngine_FillBox);
        LinkEngine_FillBox_Conv(coord(6, 1, wram->wTilemap), 6, 1, 0x7f);
        // hlcoord(17, 1, wTilemap);
        // LD_BC((6 << 8) | 1);
        // LD_A(0x7f);
        // CALL(aLinkEngine_FillBox);
        LinkEngine_FillBox_Conv(coord(17, 1, wram->wTilemap), 6, 1, 0x7f);
        // JP(mLinkTrade_PlayerPartyMenu);
        goto LinkTrade_PlayerPartyMenu;
    }

// try_trade:
    // CALL(aPlaceHollowCursor);
    PlaceHollowCursor_Conv();
    // POP_AF;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = menuY;
    // DEC_A;
    // LD_addr_A(wCurTradePartyMon);
    wram->wCurTradePartyMon = menuY - 1;
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = menuY - 1;
    // FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
    PrintWaitingTextAndSyncAndExchangeNybble();
    // LD_A_addr(wOtherPlayerLinkMode);
    // CP_A(0xf);
    // JP_Z (mInitTradeMenuDisplay);
    if(wram->wOtherPlayerLinkMode == 0xf)
        goto InitTradeMenuDisplay;
    // LD_addr_A(wCurOTTradePartyMon);
    wram->wCurOTTradePartyMon = wram->wOtherPlayerLinkMode & 0xf;
    // CALL(aLinkTradePlaceArrow);
    LinkTradePlaceArrow();
    // LD_C(100);
    // CALL(aDelayFrames);
    DelayFrames_Conv(100);
    // FARCALL(aValidateOTTrademon);
    // IF_C goto abnormal;
    if(!ValidateOTTrademon_Conv(wram->wCurOTTradePartyMon)) {
    // abnormal:
        // XOR_A_A;
        // LD_addr_A(wUnusedLinkAction);
        // LD_addr_A(wOtherPlayerLinkAction);
        // LD_A_addr(wCurOTTradePartyMon);
        // LD_HL(wOTPartySpecies);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetPokemonName);
        GetPokemonName_Conv2(wram->wOTPartySpecies[wram->wCurOTTradePartyMon]);
        // hlcoord(0, 12, wTilemap);
        // LD_B(4);
        // LD_C(18);
        // CALL(aLinkTextboxAtHL);
        LinkTextboxAtHL_Conv(coord(0, 12, wram->wTilemap), 4, 18);
        // FARCALL(aLink_WaitBGMap);
        Link_WaitBGMap();
        // LD_HL(mLinkTrade_TradeStatsMenu_LinkAbnormalMonText);
        // bccoord(1, 14, wTilemap);
        // CALL(aPlaceHLTextAtBC);
        PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), LinkAbnormalMonText);
    }
    else {
        // FARCALL(aCheckAnyOtherAliveMonsForTrade);
        // JP_NC (mLinkTrade);
        if(CheckAnyOtherAliveMonsForTrade_Conv(wram->wCurTradePartyMon))
            return LinkTrade();
        // XOR_A_A;
        // LD_addr_A(wUnusedLinkAction);
        wram->wUnusedLinkAction = 0;
        // LD_addr_A(wOtherPlayerLinkAction);
        wram->wOtherPlayerLinkAction = 0;
        // hlcoord(0, 12, wTilemap);
        // LD_B(4);
        // LD_C(18);
        // CALL(aLinkTextboxAtHL);
        LinkTextboxAtHL_Conv(coord(0, 12, wram->wTilemap), 4, 18);
        // FARCALL(aLink_WaitBGMap);
        Link_WaitBGMap();
        // LD_HL(mLinkTrade_TradeStatsMenu_LinkTradeCantBattleText);
        // bccoord(1, 14, wTilemap);
        // CALL(aPlaceHLTextAtBC);
        PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), LinkTradeCantBattleText);
        // goto cancel_trade;
    }

// cancel_trade:
    // hlcoord(0, 12, wTilemap);
    // LD_B(4);
    // LD_C(18);
    // CALL(aLinkTextboxAtHL);
    LinkTextboxAtHL_Conv(coord(0, 12, wram->wTilemap), 4, 18);
    // hlcoord(1, 14, wTilemap);
    // LD_DE(mString_TooBadTheTradeWasCanceled);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_TooBadTheTradeWasCanceled), coord(1, 14, wram->wTilemap));
    // LD_A(0x1);
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = 0x1;
    // FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
    PrintWaitingTextAndSyncAndExchangeNybble();
    // LD_C(100);
    // CALL(aDelayFrames);
    DelayFrames_Conv(100);
    // JP(mInitTradeMenuDisplay);
    goto InitTradeMenuDisplay;

LinkTradeOTPartymonMenuLoop:
    // FARCALL(aLinkTradeMenu);
    // LD_A_D;
    ctl = LinkTradeMenu_Conv();
    // AND_A_A;
    // JP_Z (mLinkTradePartiesMenuMasterLoop);
    if(ctl == 0)
        goto LinkTradePartiesMenuMasterLoop;
    // BIT_A(A_BUTTON_F);
    // IF_Z goto not_a_button;
    if(bit_test(ctl, A_BUTTON_F)) {
        // LD_A(INIT_ENEMYOT_LIST);
        // LD_addr_A(wInitListType);
        // CALLFAR(aInitList);
        // LD_HL(wOTPartyMon1Species);
        // FARCALL(aLinkMonStatsScreen);
        LinkMonStatsScreen();
        // JP(mLinkTradePartiesMenuMasterLoop);
        goto LinkTradePartiesMenuMasterLoop;
    }

// not_a_button:
    // BIT_A(D_UP_F);
    // IF_Z goto not_d_up;
    if(!bit_test(ctl, D_UP_F)) {
    // not_d_up:
        // BIT_A(D_DOWN_F);
        // JP_Z (mLinkTradePartiesMenuMasterLoop);
        if(!bit_test(ctl, D_DOWN_F))
            goto LinkTradePartiesMenuMasterLoop;
        // JP(mLinkTradeOTPartymonMenuCheckCancel);
        goto LinkTradeOTPartymonMenuCheckCancel;
    }
    // LD_A_addr(wMenuCursorY);
    // LD_B_A;
    // LD_A_addr(wOTPartyCount);
    // CP_A_B;
    // JP_NZ (mLinkTradePartiesMenuMasterLoop);
    if(wram->wMenuCursorY == wram->wOTPartyCount)
        goto LinkTradePartiesMenuMasterLoop;
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = 0;
    // CALL(aHideCursor);
    hl = HideCursor_Conv();
    // PUSH_HL;
    // PUSH_BC;
    // LD_BC(NAME_LENGTH);
    // ADD_HL_BC;
    // LD_hl(0x7f);
    hl[NAME_LENGTH] = 0x7f;
    // POP_BC;
    // POP_HL;
    // LD_A_addr(wPartyCount);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = wram->wPartyCount;
    // JR(mLinkTrade_PlayerPartyMenu);
    goto LinkTrade_PlayerPartyMenu;

LinkTradePartymonMenuLoop:
    // FARCALL(aLinkTradeMenu);
    // LD_A_D;
    ctl = LinkTradeMenu_Conv();
    // AND_A_A;
    // IF_NZ goto check_joypad;
    if(ctl == 0)
        goto LinkTradePartiesMenuMasterLoop;
        // JP(mLinkTradePartiesMenuMasterLoop);

// check_joypad:
    // BIT_A(A_BUTTON_F);
    // IF_Z goto not_a_button;
    // JP(mLinkTrade_TradeStatsMenu);
    if(bit_test(ctl, A_BUTTON_F))
        goto LinkTrade_TradeStatsMenu;


// not_a_button:
    // BIT_A(D_DOWN_F);
    // IF_Z goto not_d_down;
    if(bit_test(ctl, D_DOWN_F)) {
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // JP_NZ (mLinkTradePartiesMenuMasterLoop);
        if(wram->wMenuCursorY != 1)
            goto LinkTradePartiesMenuMasterLoop;
        // LD_A(OTPARTYMON);
        // LD_addr_A(wMonType);
        wram->wMonType = OTPARTYMON;
        // CALL(aHideCursor);
        tile_t* hl = HideCursor_Conv();
        // PUSH_HL;
        // PUSH_BC;
        // LD_BC(NAME_LENGTH);
        // ADD_HL_BC;
        // LD_hl(0x7f);
        hl[NAME_LENGTH] = 0x7f;
        // POP_BC;
        // POP_HL;
        // LD_A(1);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 1;
        // JP(mLinkTrade_OTPartyMenu);
        goto LinkTrade_OTPartyMenu;
    }

// not_d_down:
    // BIT_A(D_UP_F);
    // JR_Z (mLinkTradePartiesMenuMasterLoop);
    if(!bit_test(ctl, D_UP_F))
        goto LinkTradePartiesMenuMasterLoop;
    // LD_A_addr(wMenuCursorY);
    // LD_B_A;
    // LD_A_addr(wPartyCount);
    // CP_A_B;
    // JR_NZ (mLinkTradePartiesMenuMasterLoop);
    if(wram->wMenuCursorY != wram->wPartyCount)
        goto LinkTradePartiesMenuMasterLoop;
    // CALL(aHideCursor);
    hl = HideCursor_Conv();
    // PUSH_HL;
    // PUSH_BC;
    // LD_BC(NAME_LENGTH);
    // ADD_HL_BC;
    // LD_hl(0x7f);
    hl[NAME_LENGTH] = 0x7f;
    // POP_BC;
    // POP_HL;
    // JP(mLinkTradePartymonMenuCheckCancel);
    goto LinkTradePartymonMenuCheckCancel;

LinkTradeOTPartymonMenuCheckCancel:
    // LD_A_addr(wMenuCursorY);
    // CP_A(1);
    // JP_NZ (mLinkTradePartiesMenuMasterLoop);
    if(wram->wMenuCursorY != 1)
        goto LinkTradePartiesMenuMasterLoop;
    // CALL(aHideCursor);
    hl = HideCursor_Conv();

    // PUSH_HL;
    // PUSH_BC;
    // LD_BC(NAME_LENGTH);
    // ADD_HL_BC;
    // LD_hl(0x7f);
    hl[NAME_LENGTH] = 0x7f;
    // POP_BC;
    // POP_HL;
// fallthrough

LinkTradePartymonMenuCheckCancel:

    do {
    // loop1:
        // LD_A(0xed);
        // ldcoord_a(9, 17, wTilemap);
        *coord(9, 17, wram->wTilemap) = 0xed;

        do {
        // loop2:
            // CALL(aJoyTextDelay);
            JoyTextDelay_Conv();
            DelayFrame();
            // LDH_A_addr(hJoyLast);
            // AND_A_A;
            // IF_Z goto loop2;
        } while(hram->hJoyLast == 0);
        // BIT_A(A_BUTTON_F);
        // IF_NZ goto a_button;
        if(!bit_test(hram->hJoyLast, A_BUTTON_F)) {
            // PUSH_AF;
            // LD_A(0x7f);
            // ldcoord_a(9, 17, wTilemap);
            *coord(9, 17, wram->wTilemap) = 0x7f;
            // POP_AF;
            // BIT_A(D_UP_F);
            // IF_Z goto d_up;
            if(bit_test(hram->hJoyLast, D_UP_F)) {
                // LD_A_addr(wOTPartyCount);
                // LD_addr_A(wMenuCursorY);
                wram->wMenuCursorY = wram->wOTPartyCount;
                // JP(mLinkTrade_OTPartyMenu);
                goto LinkTrade_OTPartyMenu;
            }
            else {
            // d_up:
                // LD_A(0x1);
                // LD_addr_A(wMenuCursorY);
                wram->wMenuCursorY = 0x1;
                // JP(mLinkTrade_PlayerPartyMenu);
                goto LinkTrade_PlayerPartyMenu;
            }
        }

    // a_button:
        // LD_A(0xec);
        // ldcoord_a(9, 17, wTilemap);
        *coord(9, 17, wram->wTilemap) = 0xec;
        // LD_A(0xf);
        // LD_addr_A(wPlayerLinkAction);
        wram->wPlayerLinkAction = 0xf;
        // FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
        PrintWaitingTextAndSyncAndExchangeNybble();
        // LD_A_addr(wOtherPlayerLinkMode);
        // CP_A(0xf);
        // IF_NZ goto loop1;
    } while(wram->wOtherPlayerLinkMode != 0xf);
// fallthrough

    return ExitLinkCommunications();
}

void LinkTrade_OTPartyMenu(void){
    // LD_A(OTPARTYMON);
    // LD_addr_A(wMonType);
    wram->wMonType = OTPARTYMON;
    // LD_A(A_BUTTON | D_UP | D_DOWN);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = A_BUTTON | D_UP | D_DOWN;
    // LD_A_addr(wOTPartyCount);
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = wram->wOTPartyCount;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 1;
    // LD_A(9);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = 9;
    // LD_A(6);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = 6;
    // LD_A(1);
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 1;
    // LD_A((1 << 4) | 0);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = (1 << 4) | 0;
    // LD_A(MENU_UNUSED_3);
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = MENU_UNUSED_3;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0;

    return LinkTradeOTPartymonMenuLoop();
}

void LinkTradeOTPartymonMenuLoop(void){
    // FARCALL(aLinkTradeMenu);
    // LD_A_D;
    uint8_t ctl = LinkTradeMenu_Conv();
    // AND_A_A;
    // JP_Z (mLinkTradePartiesMenuMasterLoop);
    if(ctl == 0)
        return LinkTradePartiesMenuMasterLoop();
    // BIT_A(A_BUTTON_F);
    // IF_Z goto not_a_button;
    if(bit_test(ctl, A_BUTTON_F)) {
        // LD_A(INIT_ENEMYOT_LIST);
        // LD_addr_A(wInitListType);
        // CALLFAR(aInitList);
        // LD_HL(wOTPartyMon1Species);
        // FARCALL(aLinkMonStatsScreen);
        LinkMonStatsScreen();
        // JP(mLinkTradePartiesMenuMasterLoop);
        return LinkTradePartiesMenuMasterLoop();
    }

// not_a_button:
    // BIT_A(D_UP_F);
    // IF_Z goto not_d_up;
    if(!bit_test(ctl, D_UP_F)) {
    // not_d_up:
        // BIT_A(D_DOWN_F);
        // JP_Z (mLinkTradePartiesMenuMasterLoop);
        if(!bit_test(ctl, D_DOWN_F))
            return LinkTradePartiesMenuMasterLoop();
        // JP(mLinkTradeOTPartymonMenuCheckCancel);
        return LinkTradeOTPartymonMenuCheckCancel();
    }
    // LD_A_addr(wMenuCursorY);
    // LD_B_A;
    // LD_A_addr(wOTPartyCount);
    // CP_A_B;
    // JP_NZ (mLinkTradePartiesMenuMasterLoop);
    if(wram->wMenuCursorY == wram->wOTPartyCount)
        return LinkTradePartiesMenuMasterLoop();
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = 0;
    // CALL(aHideCursor);
    tile_t* hl = HideCursor_Conv();
    // PUSH_HL;
    // PUSH_BC;
    // LD_BC(NAME_LENGTH);
    // ADD_HL_BC;
    // LD_hl(0x7f);
    hl[NAME_LENGTH] = 0x7f;
    // POP_BC;
    // POP_HL;
    // LD_A_addr(wPartyCount);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = wram->wPartyCount;
    // JR(mLinkTrade_PlayerPartyMenu);
    return LinkTrade_PlayerPartyMenu();
}

void LinkTrade_PlayerPartyMenu(void){
    // FARCALL(aInitMG_Mobile_LinkTradePalMap);
    InitMG_Mobile_LinkTradePalMap();
    // XOR_A_A;
    // LD_addr_A(wMonType);
    wram->wMonType = 0;
    // LD_A(A_BUTTON | D_UP | D_DOWN);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = A_BUTTON | D_UP | D_DOWN;
    // LD_A_addr(wPartyCount);
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = wram->wPartyCount;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 1;
    // LD_A(1);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = 1;
    // LD_A(6);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = 6;
    // LD_A(1);
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 1;
    // LD_A((1 << 4) | 0);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = (1 << 4) | 0;
    // LD_A(MENU_UNUSED_3);
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = MENU_UNUSED_3;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0;
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();

    return LinkTradePartymonMenuLoop();
}

void LinkTradePartymonMenuLoop(void){
    // FARCALL(aLinkTradeMenu);
    // LD_A_D;
    uint8_t ctl = LinkTradeMenu_Conv();
    // AND_A_A;
    // IF_NZ goto check_joypad;
    if(ctl == 0)
        return LinkTradePartiesMenuMasterLoop();
        // JP(mLinkTradePartiesMenuMasterLoop);

// check_joypad:
    // BIT_A(A_BUTTON_F);
    // IF_Z goto not_a_button;
    // JP(mLinkTrade_TradeStatsMenu);
    if(bit_test(ctl, A_BUTTON_F))
        return LinkTrade_TradeStatsMenu();


// not_a_button:
    // BIT_A(D_DOWN_F);
    // IF_Z goto not_d_down;
    if(bit_test(ctl, D_DOWN_F)) {
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // JP_NZ (mLinkTradePartiesMenuMasterLoop);
        if(wram->wMenuCursorY != 1)
            return LinkTradePartiesMenuMasterLoop();
        // LD_A(OTPARTYMON);
        // LD_addr_A(wMonType);
        wram->wMonType = OTPARTYMON;
        // CALL(aHideCursor);
        tile_t* hl = HideCursor_Conv();
        // PUSH_HL;
        // PUSH_BC;
        // LD_BC(NAME_LENGTH);
        // ADD_HL_BC;
        // LD_hl(0x7f);
        hl[NAME_LENGTH] = 0x7f;
        // POP_BC;
        // POP_HL;
        // LD_A(1);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 1;
        // JP(mLinkTrade_OTPartyMenu);
        return LinkTrade_OTPartyMenu();
    }

// not_d_down:
    // BIT_A(D_UP_F);
    // JR_Z (mLinkTradePartiesMenuMasterLoop);
    if(!bit_test(ctl, D_UP_F))
        return LinkTradePartiesMenuMasterLoop();
    // LD_A_addr(wMenuCursorY);
    // LD_B_A;
    // LD_A_addr(wPartyCount);
    // CP_A_B;
    // JR_NZ (mLinkTradePartiesMenuMasterLoop);
    if(wram->wMenuCursorY != wram->wPartyCount)
        return LinkTradePartiesMenuMasterLoop();
    // CALL(aHideCursor);
    tile_t* hl = HideCursor_Conv();
    // PUSH_HL;
    // PUSH_BC;
    // LD_BC(NAME_LENGTH);
    // ADD_HL_BC;
    // LD_hl(0x7f);
    hl[NAME_LENGTH] = 0x7f;
    // POP_BC;
    // POP_HL;
    // JP(mLinkTradePartymonMenuCheckCancel);
    return LinkTradePartymonMenuCheckCancel();
}

void LinkTradePartiesMenuMasterLoop(void){
    // LD_A_addr(wMonType);
    // AND_A_A;
    // JP_Z (mLinkTradePartymonMenuLoop);  // PARTYMON
    if(wram->wMonType == PARTYMON)
        return LinkTradePartymonMenuLoop();
    // JP(mLinkTradeOTPartymonMenuLoop);  // OTPARTYMON
    return LinkTradeOTPartymonMenuLoop();
}

void LinkTrade_TradeStatsMenu(void){
    static const char String_Stats_Trade[] = "STATS\t TRADE@";

    static const txt_cmd_s LinkTradeCantBattleText[] = {
        text_far(v_LinkTradeCantBattleText)
        text_end
    };

    static const txt_cmd_s LinkAbnormalMonText[] = {
        text_far(v_LinkAbnormalMonText)
        text_end
    };

    // CALL(aLoadTilemapToTempTilemap);
    LoadTilemapToTempTilemap_Conv();
    // LD_A_addr(wMenuCursorY);
    // PUSH_AF;
    uint8_t menuY = wram->wMenuCursorY;
    // hlcoord(0, 15, wTilemap);
    // LD_B(1);
    // LD_C(18);
    // CALL(aLinkTextboxAtHL);
    LinkTextboxAtHL_Conv(coord(0, 15, wram->wTilemap), 1, 18);
    // hlcoord(2, 16, wTilemap);
    // LD_DE(mLinkTrade_TradeStatsMenu_String_Stats_Trade);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_Stats_Trade), coord(2, 16, wram->wTilemap));
    // FARCALL(aLink_WaitBGMap);
    Link_WaitBGMap();


joy_loop:
    // LD_A(0x7f);
    // ldcoord_a(11, 16, wTilemap);
    *coord(11, 16, wram->wTilemap) = 0x7f;
    // LD_A(A_BUTTON | B_BUTTON | D_RIGHT);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = (A_BUTTON | B_BUTTON | D_RIGHT);
    // LD_A(1);
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = 1;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 1;
    // LD_A(16);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = 16;
    // LD_A(1);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = 1;
    // LD_A(1);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 1;
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 1;
    // LD_A((2 << 4) | 0);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = (2 << 4) | 0;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = 0;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0;
    // CALL(aScrollingMenuJoypad);
    uint8_t a = ScrollingMenuJoypad_Conv();
    // BIT_A(D_RIGHT_F);
    // IF_NZ goto d_right;
    if(bit_test(a, D_RIGHT_F)) {
    // d_right:
        // LD_A(0x7f);
        // ldcoord_a(1, 16, wTilemap);
        *coord(1, 16, wram->wTilemap) = 0x7f;
        // LD_A(A_BUTTON | B_BUTTON | D_LEFT);
        // LD_addr_A(wMenuJoypadFilter);
        wram->wMenuJoypadFilter = (A_BUTTON | B_BUTTON | D_LEFT);
        // LD_A(1);
        // LD_addr_A(w2DMenuNumRows);
        wram->w2DMenuNumRows = 1;
        // LD_A(1);
        // LD_addr_A(w2DMenuNumCols);
        wram->w2DMenuNumCols = 1;
        // LD_A(16);
        // LD_addr_A(w2DMenuCursorInitY);
        wram->w2DMenuCursorInitY = 16;
        // LD_A(11);
        // LD_addr_A(w2DMenuCursorInitX);
        wram->w2DMenuCursorInitX = 11;
        // LD_A(1);
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = 1;
        // LD_addr_A(wMenuCursorX);
        wram->wMenuCursorX = 1;
        // LD_A((2 << 4) | 0);
        // LD_addr_A(w2DMenuCursorOffsets);
        wram->w2DMenuCursorOffsets = (2 << 4) | 0;
        // XOR_A_A;
        // LD_addr_A(w2DMenuFlags1);
        wram->w2DMenuFlags1 = 0;
        // LD_addr_A(w2DMenuFlags2);
        wram->w2DMenuFlags2 = 0;
        // CALL(aScrollingMenuJoypad);
        uint8_t joy = ScrollingMenuJoypad_Conv();
        // BIT_A(D_LEFT_F);
        // JP_NZ (mLinkTrade_TradeStatsMenu_joy_loop);
        if(bit_test(joy, D_LEFT_F))
            goto joy_loop;
        // BIT_A(B_BUTTON_F);
        // IF_NZ goto b_button;
        if(bit_test(joy, B_BUTTON_F))
            goto b_button;
        // goto try_trade;
    }
    // BIT_A(B_BUTTON_F);
    // IF_Z goto show_stats;
    else if(bit_test(a, B_BUTTON_F)) {
    b_button:
        // POP_AF;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = menuY;
        // CALL(aSafeLoadTempTilemapToTilemap);
        SafeLoadTempTilemapToTilemap_Conv();
        // JP(mLinkTrade_PlayerPartyMenu);
        return LinkTrade_PlayerPartyMenu();
    }
    else {
    show_stats:
        // POP_AF;
        // LD_addr_A(wMenuCursorY);
        wram->wMenuCursorY = menuY;
        // LD_A(INIT_PLAYEROT_LIST);
        // LD_addr_A(wInitListType);
        // CALLFAR(aInitList);
        // FARCALL(aLinkMonStatsScreen);
        LinkMonStatsScreen();
        // CALL(aSafeLoadTempTilemapToTilemap);
        SafeLoadTempTilemapToTilemap_Conv();
        // hlcoord(6, 1, wTilemap);
        // LD_BC((6 << 8) | 1);
        // LD_A(0x7f);
        // CALL(aLinkEngine_FillBox);
        LinkEngine_FillBox_Conv(coord(6, 1, wram->wTilemap), 6, 1, 0x7f);
        // hlcoord(17, 1, wTilemap);
        // LD_BC((6 << 8) | 1);
        // LD_A(0x7f);
        // CALL(aLinkEngine_FillBox);
        LinkEngine_FillBox_Conv(coord(17, 1, wram->wTilemap), 6, 1, 0x7f);
        // JP(mLinkTrade_PlayerPartyMenu);
        return LinkTrade_PlayerPartyMenu();
    }

// try_trade:
    // CALL(aPlaceHollowCursor);
    PlaceHollowCursor_Conv();
    // POP_AF;
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = menuY;
    // DEC_A;
    // LD_addr_A(wCurTradePartyMon);
    wram->wCurTradePartyMon = menuY - 1;
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = menuY - 1;
    // FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
    PrintWaitingTextAndSyncAndExchangeNybble();
    // LD_A_addr(wOtherPlayerLinkMode);
    // CP_A(0xf);
    // JP_Z (mInitTradeMenuDisplay);
    if(wram->wOtherPlayerLinkMode & 0xf)
        return InitTradeMenuDisplay();
    // LD_addr_A(wCurOTTradePartyMon);
    wram->wCurOTTradePartyMon = wram->wOtherPlayerLinkMode & 0xf;
    // CALL(aLinkTradePlaceArrow);
    LinkTradePlaceArrow();
    // LD_C(100);
    // CALL(aDelayFrames);
    DelayFrames_Conv(100);
    // FARCALL(aValidateOTTrademon);
    // IF_C goto abnormal;
    if(!ValidateOTTrademon_Conv(wram->wCurOTTradePartyMon)) {
    // abnormal:
        // XOR_A_A;
        // LD_addr_A(wUnusedLinkAction);
        // LD_addr_A(wOtherPlayerLinkAction);
        // LD_A_addr(wCurOTTradePartyMon);
        // LD_HL(wOTPartySpecies);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetPokemonName);
        GetPokemonName_Conv2(wram->wOTPartySpecies[wram->wCurOTTradePartyMon]);
        // hlcoord(0, 12, wTilemap);
        // LD_B(4);
        // LD_C(18);
        // CALL(aLinkTextboxAtHL);
        LinkTextboxAtHL_Conv(coord(0, 12, wram->wTilemap), 4, 18);
        // FARCALL(aLink_WaitBGMap);
        Link_WaitBGMap();
        // LD_HL(mLinkTrade_TradeStatsMenu_LinkAbnormalMonText);
        // bccoord(1, 14, wTilemap);
        // CALL(aPlaceHLTextAtBC);
        PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), LinkAbnormalMonText);
    }
    else {
        // FARCALL(aCheckAnyOtherAliveMonsForTrade);
        // JP_NC (mLinkTrade);
        if(CheckAnyOtherAliveMonsForTrade_Conv(wram->wCurTradePartyMon))
            return LinkTrade();
        // XOR_A_A;
        // LD_addr_A(wUnusedLinkAction);
        wram->wUnusedLinkAction = 0;
        // LD_addr_A(wOtherPlayerLinkAction);
        wram->wOtherPlayerLinkAction = 0;
        // hlcoord(0, 12, wTilemap);
        // LD_B(4);
        // LD_C(18);
        // CALL(aLinkTextboxAtHL);
        LinkTextboxAtHL_Conv(coord(0, 12, wram->wTilemap), 4, 18);
        // FARCALL(aLink_WaitBGMap);
        Link_WaitBGMap();
        // LD_HL(mLinkTrade_TradeStatsMenu_LinkTradeCantBattleText);
        // bccoord(1, 14, wTilemap);
        // CALL(aPlaceHLTextAtBC);
        PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), LinkTradeCantBattleText);
        // goto cancel_trade;
    }

// cancel_trade:
    // hlcoord(0, 12, wTilemap);
    // LD_B(4);
    // LD_C(18);
    // CALL(aLinkTextboxAtHL);
    LinkTextboxAtHL_Conv(coord(0, 12, wram->wTilemap), 4, 18);
    // hlcoord(1, 14, wTilemap);
    // LD_DE(mString_TooBadTheTradeWasCanceled);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_TooBadTheTradeWasCanceled), coord(1, 14, wram->wTilemap));
    // LD_A(0x1);
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = 0x1;
    // FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
    PrintWaitingTextAndSyncAndExchangeNybble();
    // LD_C(100);
    // CALL(aDelayFrames);
    DelayFrames_Conv(100);
    // JP(mInitTradeMenuDisplay);
    return InitTradeMenuDisplay();
}

void LinkTradeOTPartymonMenuCheckCancel(void){
    // LD_A_addr(wMenuCursorY);
    // CP_A(1);
    // JP_NZ (mLinkTradePartiesMenuMasterLoop);
    if(wram->wMenuCursorY != 1)
        return LinkTradePartiesMenuMasterLoop();
    // CALL(aHideCursor);
    uint8_t* hl = HideCursor_Conv();

    // PUSH_HL;
    // PUSH_BC;
    // LD_BC(NAME_LENGTH);
    // ADD_HL_BC;
    // LD_hl(0x7f);
    hl[NAME_LENGTH] = 0x7f;
    // POP_BC;
    // POP_HL;
// fallthrough

    return LinkTradePartymonMenuCheckCancel();
}

void LinkTradePartymonMenuCheckCancel(void){

    do {
    // loop1:
        // LD_A(0xed);
        // ldcoord_a(9, 17, wTilemap);
        *coord(9, 17, wram->wTilemap) = 0xed;

        do {
        // loop2:
            // CALL(aJoyTextDelay);
            JoyTextDelay_Conv();
            // LDH_A_addr(hJoyLast);
            // AND_A_A;
            // IF_Z goto loop2;
        } while(hram->hJoyLast == 0);
        // BIT_A(A_BUTTON_F);
        // IF_NZ goto a_button;
        if(!bit_test(hram->hJoyLast, A_BUTTON_F)) {
            // PUSH_AF;
            // LD_A(0x7f);
            // ldcoord_a(9, 17, wTilemap);
            *coord(9, 17, wram->wTilemap) = 0x7f;
            // POP_AF;
            // BIT_A(D_UP_F);
            // IF_Z goto d_up;
            if(bit_test(hram->hJoyLast, D_UP_F)) {
                // LD_A_addr(wOTPartyCount);
                // LD_addr_A(wMenuCursorY);
                wram->wMenuCursorY = wram->wOTPartyCount;
                // JP(mLinkTrade_OTPartyMenu);
                return LinkTrade_OTPartyMenu();
            }
            else {
            // d_up:
                // LD_A(0x1);
                // LD_addr_A(wMenuCursorY);
                wram->wMenuCursorY = 0x1;
                // JP(mLinkTrade_PlayerPartyMenu);
                return LinkTrade_PlayerPartyMenu();
            }
        }

    // a_button:
        // LD_A(0xec);
        // ldcoord_a(9, 17, wTilemap);
        *coord(9, 17, wram->wTilemap) = 0xec;
        // LD_A(0xf);
        // LD_addr_A(wPlayerLinkAction);
        wram->wPlayerLinkAction = 0xf;
        // FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
        PrintWaitingTextAndSyncAndExchangeNybble();
        // LD_A_addr(wOtherPlayerLinkMode);
        // CP_A(0xf);
        // IF_NZ goto loop1;
    } while(wram->wOtherPlayerLinkMode != 0xf);
// fallthrough

    return ExitLinkCommunications();
}

void ExitLinkCommunications(void){
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight_Conv();
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // XOR_A_A;
    // LD_addr_A(wUnusedLinkCommunicationByte);
    wram->wUnusedLinkCommunicationByte = 0;
    // XOR_A_A;
    // LDH_addr_A(rSB);
    // gb_write(rSB, 0);
    // LDH_addr_A(hSerialSend);
    // hram->hSerialSend = 0;
    // LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
    // LDH_addr_A(rSC);
    // gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CLOCK));
    // LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
    // LDH_addr_A(rSC);
    // gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CLOCK));
    Network_SendByte(0);
    // RET;
}

void GSPlaceTradeScreenFooter(void){
//  //  unreferenced
//  Fill the screen footer with pattern tile
    hlcoord(0, 16, wTilemap);
    LD_A(0x7e);
    LD_BC(2 * SCREEN_WIDTH);
    CALL(aByteFill);
//  Clear out area for cancel string
    hlcoord(1, 16, wTilemap);
    LD_A(0x7f);
    LD_BC(SCREEN_WIDTH - 2);
    CALL(aByteFill);
//  Place the string
    hlcoord(2, 16, wTilemap);
    LD_DE(mGSPlaceTradeScreenFooter_CancelString);
    JP(mPlaceString);


CancelString:
    //db ['"CANCEL@"'];

    return LinkTradePlaceArrow();
}

//  Indicates which pokemon the other player has selected to trade
void LinkTradePlaceArrow(void){
    // LD_A_addr(wOtherPlayerLinkMode);
    // hlcoord(6, 9, wTilemap);
    // LD_BC(SCREEN_WIDTH);
    // CALL(aAddNTimes);
    // LD_hl(0xec);
    coord(6, 9, wram->wTilemap)[SCREEN_WIDTH * wram->wOtherPlayerLinkMode] = 0xec;
    // RET;
}

void LinkEngine_FillBox(void){

row:
    PUSH_BC;
    PUSH_HL;

col:
    LD_hli_A;
    DEC_C;
    IF_NZ goto col;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto row;
    RET;

}

void LinkEngine_FillBox_Conv(tile_t* hl, uint8_t b, uint8_t c, uint8_t a){

    for(uint32_t x = 0; x < b; ++x) {
    // row:
        // PUSH_BC;
        // PUSH_HL;

        for(uint32_t y = 0; y < c; ++y) {
        // col:
            // LD_hli_A;
            *coord(x, y, hl) = a;
            // DEC_C;
            // IF_NZ goto col;
        }
        // POP_HL;
        // LD_BC(SCREEN_WIDTH);
        // ADD_HL_BC;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto row;
    }
    // RET;
}

void LinkTrade(void){
    // XOR_A_A;
    // LD_addr_A(wUnusedLinkAction);
    wram->wUnusedLinkAction = 0;
    // LD_addr_A(wOtherPlayerLinkAction);
    wram->wOtherPlayerLinkAction = 0;
    // hlcoord(0, 12, wTilemap);
    // LD_B(4);
    // LD_C(18);
    // CALL(aLinkTextboxAtHL);
    LinkTextboxAtHL_Conv(coord(0, 12, wram->wTilemap), 4, 18);
    // FARCALL(aLink_WaitBGMap);
    Link_WaitBGMap();
    // LD_A_addr(wCurTradePartyMon);
    // LD_HL(wPartySpecies);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    species_t s = wram->wPartySpecies[wram->wCurTradePartyMon];
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    // LD_HL(wStringBuffer1);
    // LD_DE(wBufferTrademonNickname);
    // LD_BC(MON_NAME_LENGTH);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wBufferTrademonNickname,
        GetPokemonName_Conv2(s), MON_NAME_LENGTH);
    // LD_A_addr(wCurOTTradePartyMon);
    // LD_HL(wOTPartySpecies);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_A_hl;
    s = wram->wOTPartySpecies[wram->wCurOTTradePartyMon];
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetPokemonName);
    GetPokemonName_Conv2(s);
    // LD_HL(mLinkAskTradeForText);
    // bccoord(1, 14, wTilemap);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), LinkAskTradeForText);
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader_Conv();
    // hlcoord(10, 7, wTilemap);
    // LD_B(3);
    // LD_C(7);
    // CALL(aLinkTextboxAtHL);
    LinkTextboxAtHL_Conv(coord(10, 7, wram->wTilemap), 3, 7);
    // LD_DE(mString_TradeCancel);
    // hlcoord(12, 8, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_TradeCancel), coord(12, 8, wram->wTilemap));
    // LD_A(8);
    // LD_addr_A(w2DMenuCursorInitY);
    wram->w2DMenuCursorInitY = 8;
    // LD_A(11);
    // LD_addr_A(w2DMenuCursorInitX);
    wram->w2DMenuCursorInitX = 11;
    // LD_A(1);
    // LD_addr_A(w2DMenuNumCols);
    wram->w2DMenuNumCols = 1;
    // LD_A(2);
    // LD_addr_A(w2DMenuNumRows);
    wram->w2DMenuNumRows = 2;
    // XOR_A_A;
    // LD_addr_A(w2DMenuFlags1);
    wram->w2DMenuFlags1 = 0;
    // LD_addr_A(w2DMenuFlags2);
    wram->w2DMenuFlags2 = 0;
    // LD_A(0x20);
    // LD_addr_A(w2DMenuCursorOffsets);
    wram->w2DMenuCursorOffsets = 0x20;
    // LD_A(A_BUTTON | B_BUTTON);
    // LD_addr_A(wMenuJoypadFilter);
    wram->wMenuJoypadFilter = (A_BUTTON | B_BUTTON);
    // LD_A(1);
    // LD_addr_A(wMenuCursorY);
    wram->wMenuCursorY = 1;
    // LD_addr_A(wMenuCursorX);
    wram->wMenuCursorX = 1;
    // FARCALL(aLink_WaitBGMap);
    Link_WaitBGMap();
    // CALL(aScrollingMenuJoypad);
    // PUSH_AF;
    uint8_t joypad = ScrollingMenuJoypad_Conv();
    // CALL(aCall_ExitMenu);
    ExitMenu_Conv2();
    // CALL(aWaitBGMap2);
    WaitBGMap2_Conv();
    // POP_AF;
    // BIT_A(1);
    // IF_NZ goto canceled;
    if(bit_test(joypad, 1) || wram->wMenuCursorY != 1) {
    // canceled:
        // LD_A(0x1);
        // LD_addr_A(wPlayerLinkAction);
        wram->wPlayerLinkAction = 0x1;
        // hlcoord(0, 12, wTilemap);
        // LD_B(4);
        // LD_C(18);
        // CALL(aLinkTextboxAtHL);
        LinkTextboxAtHL_Conv(coord(0, 12, wram->wTilemap), 4, 18);
        // hlcoord(1, 14, wTilemap);
        // LD_DE(mString_TooBadTheTradeWasCanceled);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_TooBadTheTradeWasCanceled), coord(1, 14, wram->wTilemap));
        // FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
        PrintWaitingTextAndSyncAndExchangeNybble();
        // JP(mInitTradeMenuDisplay_Delay);
        return InitTradeMenuDisplay_Delay();
    }
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // IF_Z goto try_trade;
    else {
    // try_trade:
        // LD_A(0x2);
        // LD_addr_A(wPlayerLinkAction);
        wram->wPlayerLinkAction = 0x2;
        // FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
        PrintWaitingTextAndSyncAndExchangeNybble();
        // LD_A_addr(wOtherPlayerLinkMode);
        // DEC_A;
        // IF_NZ goto do_trade;
        if(wram->wOtherPlayerLinkMode == 1) {
        //  If we're here, the other player canceled the trade
            // hlcoord(0, 12, wTilemap);
            // LD_B(4);
            // LD_C(18);
            // CALL(aLinkTextboxAtHL);
            LinkTextboxAtHL_Conv(coord(0, 12, wram->wTilemap), 4, 18);
            // hlcoord(1, 14, wTilemap);
            // LD_DE(mString_TooBadTheTradeWasCanceled);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(String_TooBadTheTradeWasCanceled), coord(1, 14, wram->wTilemap));
            // JP(mInitTradeMenuDisplay_Delay);
            return InitTradeMenuDisplay_Delay();
        }

    // do_trade:
        // LD_HL(sPartyMail);
        // LD_A_addr(wCurTradePartyMon);
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        uint16_t de = sPartyMail + (wram->wCurTradePartyMon * MAIL_STRUCT_LENGTH); 
        // LD_A(BANK(sPartyMail));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(asPartyMail));
        // LD_D_H;
        // LD_E_L;
        // LD_BC(MAIL_STRUCT_LENGTH);
        // ADD_HL_BC;
        uint16_t hl = de + MAIL_STRUCT_LENGTH;
        // LD_A_addr(wCurTradePartyMon);
        // LD_C_A;

        for(uint16_t c = wram->wCurTradePartyMon; c < PARTY_LENGTH; ++c) {
        // copy_mail:
            // INC_C;
            // LD_A_C;
            // CP_A(PARTY_LENGTH);
            // IF_Z goto copy_player_data;
            // PUSH_BC;
            // LD_BC(MAIL_STRUCT_LENGTH);
            // CALL(aCopyBytes);
            CopyBytes_Conv(de + (c * MAIL_STRUCT_LENGTH), 
                hl + (c * MAIL_STRUCT_LENGTH), MAIL_STRUCT_LENGTH);
            // POP_BC;
            // goto copy_mail;
        }


    // copy_player_data:
        // LD_HL(sPartyMail);
        // LD_A_addr(wPartyCount);
        // DEC_A;
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        uint16_t de2 = sPartyMail + ((wram->wPartyCount - 1) * MAIL_STRUCT_LENGTH);
        // PUSH_HL;
        // LD_HL(wLinkPlayerMail);
        // LD_A_addr(wCurOTTradePartyMon);
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // POP_DE;
        uint8_t* src = wram->wLinkPlayerMailPreamble + (wram->wCurOTTradePartyMon * MAIL_STRUCT_LENGTH);
        // LD_BC(MAIL_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        for(uint32_t i = 0; i < MAIL_STRUCT_LENGTH; ++i) {
            gb_write(de2 + i, src[i]);
        }
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();

    //  Buffer player data
    //  nickname
        // LD_HL(wPlayerName);
        // LD_DE(wPlayerTrademonSenderName);
        // LD_BC(NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(wram->wPlayerTrademon.senderName, wram->wPlayerName, NAME_LENGTH);
    //  species
        // LD_A_addr(wCurTradePartyMon);
        // LD_HL(wPartySpecies);
        // LD_B(0);
        // LD_C_A;
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wPlayerTrademonSpecies);
        wram->wPlayerTrademon.species = wram->wPartySpecies[wram->wCurTradePartyMon];
        // PUSH_AF;
    //  OT name
        // LD_A_addr(wCurTradePartyMon);
        // LD_HL(wPartyMonOTs);
        // CALL(aSkipNames);
        // LD_DE(wPlayerTrademonOTName);
        // LD_BC(NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(wram->wPlayerTrademon.otName, wram->wPartyMonOT[wram->wCurTradePartyMon],
            NAME_LENGTH);
    //  ID
        // LD_HL(wPartyMon1ID);
        // LD_A_addr(wCurTradePartyMon);
        // CALL(aGetPartyLocation);
        // LD_A_hli;
        // LD_addr_A(wPlayerTrademonID);
        // LD_A_hl;
        // LD_addr_A(wPlayerTrademonID + 1);
        wram->wPlayerTrademon.id = wram->wPartyMon[wram->wCurTradePartyMon].mon.id;
    //  DVs
        // LD_HL(wPartyMon1DVs);
        // LD_A_addr(wCurTradePartyMon);
        // CALL(aGetPartyLocation);
        // LD_A_hli;
        // LD_addr_A(wPlayerTrademonDVs);
        // LD_A_hl;
        // LD_addr_A(wPlayerTrademonDVs + 1);
        wram->wPlayerTrademon.dvs = wram->wPartyMon[wram->wCurTradePartyMon].mon.DVs;
    //  caught data
        // LD_A_addr(wCurTradePartyMon);
        // LD_HL(wPartyMon1Species);
        // CALL(aGetPartyLocation);
        // LD_B_H;
        // LD_C_L;
        // FARCALL(aGetCaughtGender);
        // LD_A_C;
        // LD_addr_A(wPlayerTrademonCaughtData);
        wram->wPlayerTrademon.caughtData = GetCaughtGender_Conv(&wram->wPartyMon[wram->wCurTradePartyMon].mon);

    //  Buffer other player data
    //  nickname
        // LD_HL(wOTPlayerName);
        // LD_DE(wOTTrademonSenderName);
        // LD_BC(NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(wram->wOTTrademon.senderName, wram->wOTPlayerName, NAME_LENGTH);
    //  species
        // LD_A_addr(wCurOTTradePartyMon);
        // LD_HL(wOTPartySpecies);
        // LD_B(0);
        // LD_C_A;
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wOTTrademonSpecies);
        wram->wOTTrademon.species = wram->wOTPartySpecies[wram->wCurOTTradePartyMon];
    //  OT name
        // LD_A_addr(wCurOTTradePartyMon);
        // LD_HL(wOTPartyMonOTs);
        // CALL(aSkipNames);
        // LD_DE(wOTTrademonOTName);
        // LD_BC(NAME_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(wram->wOTTrademon.otName, wram->wOTPartyMonOT[wram->wCurOTTradePartyMon],
            NAME_LENGTH);
    //  ID
        // LD_HL(wOTPartyMon1ID);
        // LD_A_addr(wCurOTTradePartyMon);
        // CALL(aGetPartyLocation);
        // LD_A_hli;
        // LD_addr_A(wOTTrademonID);
        // LD_A_hl;
        // LD_addr_A(wOTTrademonID + 1);
        wram->wOTTrademon.id = wram->wOTPartyMon[wram->wCurOTTradePartyMon].mon.id;
    //  DVs
        // LD_HL(wOTPartyMon1DVs);
        // LD_A_addr(wCurOTTradePartyMon);
        // CALL(aGetPartyLocation);
        // LD_A_hli;
        // LD_addr_A(wOTTrademonDVs);
        // LD_A_hl;
        // LD_addr_A(wOTTrademonDVs + 1);
        wram->wOTTrademon.dvs = wram->wOTPartyMon[wram->wCurOTTradePartyMon].mon.DVs;
    //  caught data
        // LD_A_addr(wCurOTTradePartyMon);
        // LD_HL(wOTPartyMon1Species);
        // CALL(aGetPartyLocation);
        // LD_B_H;
        // LD_C_L;
        // FARCALL(aGetCaughtGender);
        // LD_A_C;
        // LD_addr_A(wOTTrademonCaughtData);
        wram->wOTTrademon.caughtData = GetCaughtGender_Conv(&wram->wOTPartyMon[wram->wCurOTTradePartyMon].mon);

        // LD_A_addr(wCurTradePartyMon);
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon = wram->wCurTradePartyMon;
        // LD_HL(wPartySpecies);
        // LD_B(0);
        // LD_C_A;
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wCurTradePartyMon);
        wram->wCurTradePartyMon = wram->wPartySpecies[wram->wCurTradePartyMon];

        // XOR_A_A;  // REMOVE_PARTY
        // LD_addr_A(wPokemonWithdrawDepositParameter);
        // CALLFAR(aRemoveMonFromPartyOrBox);
        RemoveMonFromPartyOrBox_Conv(REMOVE_PARTY);
        // LD_A_addr(wPartyCount);
        // DEC_A;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon = wram->wPartyCount - 1;
        // LD_A(TRUE);
        // LD_addr_A(wForceEvolution);
        wram->wForceEvolution = TRUE;
        // LD_A_addr(wCurOTTradePartyMon);
        // PUSH_AF;
        uint8_t otmon = wram->wCurOTTradePartyMon;
        // LD_HL(wOTPartySpecies);
        // LD_B(0);
        // LD_C_A;
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wCurOTTradePartyMon);
        wram->wCurOTTradePartyMon = wram->wOTPartySpecies[wram->wCurOTTradePartyMon];

        // LD_C(100);
        // CALL(aDelayFrames);
        DelayFrames_Conv(100);
        // CALL(aClearTilemap);
        ClearTilemap_Conv2();
        // CALL(aLoadFontsBattleExtra);
        LoadFontsBattleExtra_Conv();
        // LD_B(SCGB_DIPLOMA);
        // CALL(aGetSGBLayout);
        GetSGBLayout_Conv(SCGB_DIPLOMA);
        // LDH_A_addr(hSerialConnectionStatus);
        // CP_A(USING_EXTERNAL_CLOCK);
        // IF_Z goto player_2;
        if(hram->hSerialConnectionStatus != USING_EXTERNAL_CLOCK) {
            // PREDEF(pTradeAnimation);
            TradeAnimation();
            // goto done_animation;
        }
        else {
        // player_2:
            // PREDEF(pTradeAnimationPlayer2);
            TradeAnimationPlayer2();
        }

    // done_animation:
        // POP_AF;
        // LD_C_A;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon = otmon;
        // LD_HL(wOTPartySpecies);
        // LD_D(0);
        // LD_E_A;
        // ADD_HL_DE;
        // LD_A_hl;
        // LD_addr_A(wCurPartySpecies);
        wram->wCurPartySpecies = wram->wOTPartySpecies[otmon];
        // LD_HL(wOTPartyMon1Species);
        // LD_A_C;
        // CALL(aGetPartyLocation);
        // LD_DE(wTempMonSpecies);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aCopyBytes);
        CopyBytes_Conv2(&wram->wTempMon.mon.species,
            wram->wOTPartyMon + otmon,
            PARTYMON_STRUCT_LENGTH);
        // PREDEF(pAddTempmonToParty);
        AddTempmonToParty_Conv();
        // LD_A_addr(wPartyCount);
        // DEC_A;
        // LD_addr_A(wCurPartyMon);
        wram->wCurPartyMon = wram->wPartyCount - 1;
        // CALLFAR(aEvolvePokemon);
        EvolvePokemon();
        // CALL(aClearScreen);
        ClearScreen_Conv2();
        // CALL(aLoadTradeScreenBorderGFX);
        LoadTradeScreenBorderGFX();
        // CALL(aSetTradeRoomBGPals);
        SetTradeRoomBGPals();
        // FARCALL(aLink_WaitBGMap);
        Link_WaitBGMap();

        // TODO: Convert this part???
    //  Check if either of the Pokémon sent was a Mew or Celebi, and send a different
    //  byte depending on that. Presumably this would've been some prevention against
    //  illicit trade machines, but it doesn't seem like a very effective one.
    //  Removing this code breaks link compatibility with the vanilla gen2 games, but
    //  has otherwise no consequence.
        // LD_B(1);
        // POP_AF;
        // LD_C_A;
        // CP_A(MEW);
        // IF_Z goto send_checkbyte;
        // LD_A_addr(wCurPartySpecies);
        // CP_A(MEW);
        // IF_Z goto send_checkbyte;
        // LD_B(2);
        // LD_A_C;
        // CP_A(CELEBI);
        // IF_Z goto send_checkbyte;
        // LD_A_addr(wCurPartySpecies);
        // CP_A(CELEBI);
        // IF_Z goto send_checkbyte;

    //  Send the byte in a loop until the desired byte has been received.
        // LD_B(0);

    // send_checkbyte:
        // LD_A_B;
        // LD_addr_A(wPlayerLinkAction);
        // PUSH_BC;
        // CALL(aSerial_PrintWaitingTextAndSyncAndExchangeNybble);
        // POP_BC;
        // LD_A_addr(wLinkMode);
        // CP_A(LINK_TIMECAPSULE);
        // IF_Z goto save;
        // LD_A_B;
        // AND_A_A;
        // IF_Z goto save;
        // LD_A_addr(wOtherPlayerLinkAction);
        // CP_A_B;
        // IF_NZ goto send_checkbyte;


    // save:
        // FARCALL(aSaveAfterLinkTrade);
        SaveAfterLinkTrade();
        // FARCALL(aStubbedTrainerRankings_Trades);
        StubbedTrainerRankings_Trades();
        // FARCALL(aBackupMobileEventIndex);
        BackupMobileEventIndex();
        // LD_C(40);
        // CALL(aDelayFrames);
        DelayFrames_Conv(40);
        // hlcoord(0, 12, wTilemap);
        // LD_B(4);
        // LD_C(18);
        // CALL(aLinkTextboxAtHL);
        LinkTextboxAtHL_Conv(coord(0, 12, wram->wTilemap), 4, 18);
        // hlcoord(1, 14, wTilemap);
        // LD_DE(mString_TradeCompleted);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_TradeCompleted), 
            coord(1, 14, wram->wTilemap));
        // FARCALL(aLink_WaitBGMap);
        Link_WaitBGMap();
        // LD_C(50);
        // CALL(aDelayFrames);
        DelayFrames_Conv(50);
        // LD_A_addr(wLinkMode);
        // CP_A(LINK_TIMECAPSULE);
        // JP_Z (mGen2ToGen1LinkComms);
        if(wram->wLinkMode == LINK_TIMECAPSULE)
            return Gen2ToGen1LinkComms();
        // JP(mGen2ToGen2LinkComms);
        return Gen2ToGen2LinkComms();
    }
}

void InitTradeMenuDisplay_Delay(void){
    // LD_C(100);
    // CALL(aDelayFrames);
    DelayFrames_Conv(100);
    // JP(mInitTradeMenuDisplay);
    return InitTradeMenuDisplay();
}

const char String_TradeCancel[] = "TRADE"
    t_next "CANCEL@";

const txt_cmd_s LinkAskTradeForText[] = {
    text_far(v_LinkAskTradeForText)
    text_end
};

const char String_TradeCompleted[] = "Trade completed!@";

const char String_TooBadTheTradeWasCanceled[] = "Too bad! The trade"
    t_next "was canceled!@";

void LinkTextboxAtHL(void){
    LD_D_H;
    LD_E_L;
    FARCALL(aLinkTextbox);
    RET;

}

void LinkTextboxAtHL_Conv(tile_t* hl, uint8_t b, uint8_t c){
    // LD_D_H;
    // LD_E_L;
    // FARCALL(aLinkTextbox);
    LinkTextbox_Conv(hl, b, c);
    // RET;
}

void LoadTradeScreenBorderGFX(void){
    // FARCALL(av_LoadTradeScreenBorderGFX);
    // RET;
    return v_LoadTradeScreenBorderGFX();

}

void SetTradeRoomBGPals(void){
    // FARCALL(aLoadTradeRoomBGPals);  // just a nested farcall// so wasteful
    LoadTradeRoomBGPals();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // RET;
}

void PlaceTradeScreenTextbox(void){
//  //  unreferenced
    hlcoord(0, 0, wTilemap);
    LD_B(6);
    LD_C(18);
    CALL(aLinkTextboxAtHL);
    hlcoord(0, 8, wTilemap);
    LD_B(6);
    LD_C(18);
    CALL(aLinkTextboxAtHL);
    FARCALL(aPlaceTradePartnerNamesAndParty);
    RET;

// INCLUDE "engine/movie/trade_animation.asm"

    return CheckTimeCapsuleCompatibility();
}

void CheckTimeCapsuleCompatibility(void){
//  Checks to see if your party is compatible with the Gen 1 games.
//  Returns the following in wScriptVar:
//  0: Party is okay
//  1: At least one Pokémon was introduced in Gen 2
//  2: At least one Pokémon has a move that was introduced in Gen 2
//  3: At least one Pokémon is holding mail

//  If any party Pokémon was introduced in the Gen 2 games, don't let it in.
    LD_HL(wPartySpecies);
    LD_B(PARTY_LENGTH);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto checkitem;
    CP_A(JOHTO_POKEMON);
    IF_NC goto mon_too_new;
    DEC_B;
    IF_NZ goto loop;

//  If any party Pokémon is holding mail, don't let it in.

checkitem:
    LD_A_addr(wPartyCount);
    LD_B_A;
    LD_HL(wPartyMon1Item);

itemloop:
    PUSH_HL;
    PUSH_BC;
    LD_D_hl;
    FARCALL(aItemIsMail);
    POP_BC;
    POP_HL;
    IF_C goto mon_has_mail;
    LD_DE(PARTYMON_STRUCT_LENGTH);
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto itemloop;

//  If any party Pokémon has a move that was introduced in the Gen 2 games, don't let it in.
    LD_HL(wPartyMon1Moves);
    LD_A_addr(wPartyCount);
    LD_B_A;

move_loop:
    LD_C(NUM_MOVES);

move_next:
    LD_A_hli;
    CP_A(STRUGGLE + 1);
    IF_NC goto move_too_new;
    DEC_C;
    IF_NZ goto move_next;
    LD_DE(PARTYMON_STRUCT_LENGTH - NUM_MOVES);
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto move_loop;
    XOR_A_A;
    goto done;


mon_too_new:
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_A(0x1);
    goto done;


move_too_new:
    PUSH_BC;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetMoveName);
    CALL(aCopyName1);
    POP_BC;
    CALL(aGetIncompatibleMonName);
    LD_A(0x2);
    goto done;


mon_has_mail:
    CALL(aGetIncompatibleMonName);
    LD_A(0x3);


done:
    LD_addr_A(wScriptVar);
    RET;

}

void GetIncompatibleMonName(void){
//  Calulate which pokemon is incompatible, and get that pokemon's name
    LD_A_addr(wPartyCount);
    SUB_A_B;
    LD_C_A;
    INC_C;
    LD_B(0);
    LD_HL(wPartyCount);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    RET;

}

void EnterTimeCapsule(void){
    LD_C(10);
    CALL(aDelayFrames);
    LD_A(0x4);
    CALL(aLink_EnsureSync);
    LD_C(40);
    CALL(aDelayFrames);
    XOR_A_A;
    LDH_addr_A(hVBlank);
    INC_A;  // LINK_TIMECAPSULE
    LD_addr_A(wLinkMode);
    RET;

}

void WaitForOtherPlayerToExit(void){
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames_Conv(3);
    // LD_A(CONNECTION_NOT_ESTABLISHED);
    // LDH_addr_A(hSerialConnectionStatus);
    hram->hSerialConnectionStatus = CONNECTION_NOT_ESTABLISHED;
    // XOR_A_A;
    // LDH_addr_A(rSB);
    // gb_write(rSB, 0);
    // LDH_addr_A(hSerialReceive);
    hram->hSerialReceive = 0;
    // LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
    // LDH_addr_A(rSC);
    // gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CLOCK));
    // LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
    // LDH_addr_A(rSC);
    // gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CLOCK));
    Network_SendByte(0);
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames_Conv(3);
    // XOR_A_A;
    // LDH_addr_A(rSB);
    // gb_write(rSB, 0);
    // LDH_addr_A(hSerialReceive);
    hram->hSerialReceive = 0;
    // LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
    // LDH_addr_A(rSC);
    // gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CLOCK));
    // LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
    // LDH_addr_A(rSC);
    // gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CLOCK));
    Network_SendByte(0);
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames_Conv(3);
    // XOR_A_A;
    // LDH_addr_A(rSB);
    gb_write(rSB, 0);
    // LDH_addr_A(hSerialReceive);
    hram->hSerialReceive = 0;
    // LDH_addr_A(rSC);
    gb_write(rSC, 0);
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames_Conv(3);
    // LD_A(CONNECTION_NOT_ESTABLISHED);
    // LDH_addr_A(hSerialConnectionStatus);
    hram->hSerialConnectionStatus = CONNECTION_NOT_ESTABLISHED;
    gOtherPlayerGender = 0;
    // LDH_A_addr(rIF);
    // PUSH_AF;
    uint8_t rif = gb_read(rIF);
    // XOR_A_A;
    // LDH_addr_A(rIF);
    gb_write(rIF, 0);
    // LD_A(IE_DEFAULT);
    // LDH_addr_A(rIE);
    gb_write(rIE, IE_DEFAULT);
    // POP_AF;
    // LDH_addr_A(rIF);
    gb_write(rIF, rif);
    // LD_HL(wLinkTimeoutFrames);
    // XOR_A_A;
    // LD_hli_A;
    // LD_hl_A;
    wram->wLinkTimeoutFrames = 0;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0;
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = LINK_NULL;
    NetworkCloseConnection();
    // RET;
}

void SetBitsForLinkTradeRequest(void){
    // LD_A(LINK_TRADECENTER - 1);
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = LINK_TRADECENTER - 1;
    // LD_addr_A(wChosenCableClubRoom);
    wram->wChosenCableClubRoom = LINK_TRADECENTER - 1;
    // RET;
}

void SetBitsForBattleRequest(void){
    // LD_A(LINK_COLOSSEUM - 1);
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = LINK_COLOSSEUM - 1;
    // LD_addr_A(wChosenCableClubRoom);
    wram->wChosenCableClubRoom = LINK_COLOSSEUM - 1;
    // RET;

}

void SetBitsForTimeCapsuleRequest(void){
    LD_A(USING_INTERNAL_CLOCK);
    LDH_addr_A(rSB);
    XOR_A_A;
    LDH_addr_A(hSerialReceive);
    LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
    LDH_addr_A(rSC);
    XOR_A_A;  // LINK_TIMECAPSULE - 1
    LD_addr_A(wPlayerLinkAction);
    LD_addr_A(wChosenCableClubRoom);
    RET;

}

void WaitForLinkedFriend(void){
    // LD_A_addr(wPlayerLinkAction);
    // AND_A_A;
    // IF_Z goto no_link_action;
    if(wram->wPlayerLinkAction != 0) {
        // LD_A(USING_INTERNAL_CLOCK);
        // LDH_addr_A(rSB);
        // gb_write(rSB, USING_INTERNAL_CLOCK);
        // XOR_A_A;
        // LDH_addr_A(hSerialReceive);
        hram->hSerialReceive = 0;
        // LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (0 << rSC_ON) | (0 << rSC_CLOCK));
        // LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (1 << rSC_ON) | (0 << rSC_CLOCK));
        Network_SendByte(USING_INTERNAL_CLOCK);
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aDelayFrame);
        DelayFrame();
    }

// no_link_action:
    // LD_A(0x2);
    // LD_addr_A(wLinkTimeoutFrames + 1);
    // LD_A(0xff);
    // LD_addr_A(wLinkTimeoutFrames);
    wram->wLinkTimeoutFrames = 0x02ff;

    while(hram->hSerialConnectionStatus != USING_INTERNAL_CLOCK && hram->hSerialConnectionStatus != USING_EXTERNAL_CLOCK) {
    // loop:
        // LDH_A_addr(hSerialConnectionStatus);
        // CP_A(USING_INTERNAL_CLOCK);
        // IF_Z goto connected;
        // CP_A(USING_EXTERNAL_CLOCK);
        // IF_Z goto connected;
        // LD_A(CONNECTION_NOT_ESTABLISHED);
        // LDH_addr_A(hSerialConnectionStatus);
        hram->hSerialConnectionStatus = CONNECTION_NOT_ESTABLISHED;
        // LD_A(USING_INTERNAL_CLOCK);
        // LDH_addr_A(rSB);
        gb_write(rSB, USING_INTERNAL_CLOCK);
        // XOR_A_A;
        // LDH_addr_A(hSerialReceive);
        hram->hSerialReceive = 0;
        // LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        gb_write(rSC, (0 << rSC_ON) | (0 << rSC_CLOCK));
        // LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        gb_write(rSC, (1 << rSC_ON) | (0 << rSC_CLOCK));
        // LD_A_addr(wLinkTimeoutFrames);
        // DEC_A;
        // LD_addr_A(wLinkTimeoutFrames);
        // IF_NZ goto not_done;
        // LD_A_addr(wLinkTimeoutFrames + 1);
        // DEC_A;
        // LD_addr_A(wLinkTimeoutFrames + 1);
        // IF_Z goto done;
        if(--wram->wLinkTimeoutFrames == 0) {
        // done:
            // XOR_A_A;
            // LD_addr_A(wScriptVar);
            wram->wScriptVar = FALSE;
            // RET;
            return;
        }


    // not_done:
        // LD_A(USING_EXTERNAL_CLOCK);
        // LDH_addr_A(rSB);
        // gb_write(rSB, USING_EXTERNAL_CLOCK);
        // LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CLOCK));
        // LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        // gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CLOCK));
        Network_SendByte(USING_EXTERNAL_CLOCK);
        // CALL(aDelayFrame);
        DelayFrame();
        // goto loop;
    }

// connected:
    // CALL(aLinkDataReceived);
    LinkDataReceived();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aLinkDataReceived);
    LinkDataReceived();
    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames_Conv(50);
    // LD_A(0x1);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = TRUE;
    // RET;
}

void CheckLinkTimeout_Receptionist(void){
    PEEK("");
    // LD_A(0x1);
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = 0x1;
    // LD_HL(wLinkTimeoutFrames);
    // LD_A(3);
    // LD_hli_A;
    // XOR_A_A;
    // LD_hl_A;
    wram->wLinkTimeoutFrames = 0x300;
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // LD_A(0x2);
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0x2;
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aLink_CheckCommunicationError);
    Link_CheckCommunicationError();
    // XOR_A_A;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0;
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // RET_NZ ;
    if(wram->wScriptVar == FALSE)
        // JP(mLink_ResetSerialRegistersAfterLinkClosure);
        return Link_ResetSerialRegistersAfterLinkClosure();
}

//  if wScriptVar = 0 on exit, link connection is closed
void CheckLinkTimeout_Gen2(void){
    // LD_A(0x5);
    // LD_addr_A(wPlayerLinkAction);
    wram->wPlayerLinkAction = 0x5;
    // LD_HL(wLinkTimeoutFrames);
    // LD_A(3);
    // LD_hli_A;
    // XOR_A_A;
    // LD_hl_A;
    wram->wLinkTimeoutFrames = 0x300;
    // CALL(aWaitBGMap);
    // LD_A(0x2);
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0x2;
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aLink_CheckCommunicationError);
    Link_CheckCommunicationError();
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // IF_Z goto exit;
    if(wram->wScriptVar == FALSE) {
    // exit:
        // XOR_A_A;
        // LDH_addr_A(hVBlank);
        hram->hVBlank = 0;
        // RET;
        return;
    }
//  Wait for ~$70000 cycles to give the other GB time to be ready
    // LD_BC(0xffff);

    // do {
    // wait:
        // DEC_BC;
        // LD_A_B;
        // OR_A_C;
        // IF_NZ goto wait;
    // } while(--bc != 0);
    DelayFrame();
    DelayFrame();
    DelayFrame();

//  If other GB is not ready at this point, disconnect due to timeout
    // LD_A_addr(wOtherPlayerLinkMode);
    // CP_A(0x5);
    // IF_NZ goto timeout;

    printf("Check wOtherPlayerLinkMode == 5: %d\n", wram->wOtherPlayerLinkMode);
    if(wram->wOtherPlayerLinkMode == 0x5) {
    //  Another check to increase reliability
        // LD_A(0x6);
        // LD_addr_A(wPlayerLinkAction);
        wram->wPlayerLinkAction = 0x6;
        // LD_HL(wLinkTimeoutFrames);
        // LD_A(1);
        // LD_hli_A;
        // LD_hl(50);
        wram->wLinkTimeoutFrames = 0x132;
        // CALL(aLink_CheckCommunicationError);
        Link_CheckCommunicationError();
        // LD_A_addr(wOtherPlayerLinkMode);
        // CP_A(0x6);
        // IF_Z goto exit;
        printf("Check wOtherPlayerLinkMode == 6: %d\n", wram->wOtherPlayerLinkMode);
        if(wram->wOtherPlayerLinkMode == 0x6) {
        // exit:
            // XOR_A_A;
            // LDH_addr_A(hVBlank);
            hram->hVBlank = 0;
            wram->wScriptVar = TRUE;
            // RET;
            return;
        }
    }

// timeout:
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = FALSE;
    // RET;
    return;
}

static bool Link_CheckCommunicationError_CheckConnected(void) {
    // CALL(aWaitLinkTransfer);
    WaitLinkTransfer();
    // LD_HL(wLinkTimeoutFrames);
    // LD_A_hli;
    // INC_A;
    // RET_NZ ;
    // LD_A_hl;
    // INC_A;
    // RET;
    return (wram->wLinkTimeoutFrames != 0xffff);
}

static void Link_CheckComminicationError_AcknowledgeSerial(void) {
    // LD_B(10);
    uint8_t b = 10;

    do {
    // loop:
        // CALL(aDelayFrame);
        DelayFrame();
        // CALL(aLinkDataReceived);
        LinkDataReceived();
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

// [wLinkTimeoutFrames] = ((hl - $100) / 4) + $100
//                      = (hl / 4) + $c0
static void Link_CheckCommunicationError_ConvertDW(uint16_t hl) {
    // DEC_H;
    // SRL_H;
    // RR_L;
    // SRL_H;
    // RR_L;
    // INC_H;
    // LD_A_H;
    // LD_addr_A(wLinkTimeoutFrames);
    // LD_A_L;
    // LD_addr_A(wLinkTimeoutFrames + 1);
    wram->wLinkTimeoutFrames = ((hl - 0x100) / 4) + 0x100;
    // RET;
}

void Link_CheckCommunicationError(void){
    // XOR_A_A;
    // LDH_addr_A(hSerialReceivedNewData);
    hram->hSerialReceivedNewData = FALSE;
    // LD_A_addr(wLinkTimeoutFrames);
    // LD_H_A;
    // LD_A_addr(wLinkTimeoutFrames + 1);
    // LD_L_A;
    // PUSH_HL;
    uint16_t frames = wram->wLinkTimeoutFrames;
    // CALL(aLink_CheckCommunicationError_CheckConnected);
    // POP_HL;
    // IF_NZ goto load_true;
    uint8_t a;
    if(Link_CheckCommunicationError_CheckConnected()) {
    // load_true:
        // LD_A(TRUE);
        a = TRUE;
    }
    else {
        // CALL(aLink_CheckCommunicationError_AcknowledgeSerial);
        Link_CheckComminicationError_AcknowledgeSerial();
        // CALL(aLink_CheckCommunicationError_ConvertDW);
        Link_CheckCommunicationError_ConvertDW(frames);
        // CALL(aLink_CheckCommunicationError_CheckConnected);
        // IF_NZ goto load_true;
        if(Link_CheckCommunicationError_CheckConnected()) {
            a = TRUE;
        }
        else {
            // CALL(aLink_CheckCommunicationError_AcknowledgeSerial);
            Link_CheckComminicationError_AcknowledgeSerial();
            // XOR_A_A;  // FALSE
            a = FALSE;
            // goto done;
        }
    }

// done:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = a;
    // LD_HL(wLinkTimeoutFrames);
    // XOR_A_A;
    // LD_hli_A;
    // LD_hl_A;
    wram->wLinkTimeoutFrames = 0;
    // RET;

}

void TryQuickSave(void){
    // LD_A_addr(wChosenCableClubRoom);
    // PUSH_AF;
    uint8_t room = wram->wChosenCableClubRoom;
    // FARCALL(aLink_SaveGame);
    // LD_A(TRUE);
    // IF_NC goto return_result;
    // XOR_A_A;  // FALSE

// return_result:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (Link_SaveGame())? TRUE: FALSE;
    // LD_C(30);
    // CALL(aDelayFrames);
    DelayFrames_Conv(30);
    // POP_AF;
    // LD_addr_A(wChosenCableClubRoom);
    wram->wChosenCableClubRoom = room;
    // RET;
}

void CheckBothSelectedSameRoom(void){
    PEEK("");
    // LD_A_addr(wChosenCableClubRoom);
    // CALL(aLink_EnsureSync);
    uint8_t byte = Link_EnsureSync_Conv(wram->wChosenCableClubRoom);
    // PUSH_AF;
    // CALL(aLinkDataReceived);
    LinkDataReceived();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aLinkDataReceived);
    LinkDataReceived();
    // POP_AF;
    // LD_B_A;
    // LD_A_addr(wChosenCableClubRoom);
    // CP_A_B;
    // IF_NZ goto fail;
    if(wram->wChosenCableClubRoom == byte) {
        // LD_A_addr(wChosenCableClubRoom);
        // INC_A;
        // LD_addr_A(wLinkMode);
        wram->wLinkMode = wram->wChosenCableClubRoom + 1;
        // XOR_A_A;
        // LDH_addr_A(hVBlank);
        hram->hVBlank = 0;
        // LD_A(TRUE);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = TRUE;
        // RET;
        return;
    }
    else {
    // fail:
        // XOR_A_A;  // FALSE
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = FALSE;
        // RET;
        return;
    }
}

void TimeCapsule(void){
    LD_A(LINK_TIMECAPSULE);
    LD_addr_A(wLinkMode);
    CALL(aDisableSpriteUpdates);
    CALLFAR(aLinkCommunications);
    CALL(aEnableSpriteUpdates);
    XOR_A_A;
    LDH_addr_A(hVBlank);
    RET;

}

void TradeCenter(void){
    // LD_A(LINK_TRADECENTER);
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = LINK_TRADECENTER;
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates_Conv();
    // CALLFAR(aLinkCommunications);
    LinkCommunications();
    // CALL(aEnableSpriteUpdates);
    EnableSpriteUpdates_Conv();
    // XOR_A_A;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0;
    // RET;

}

void Colosseum(void){
    // LD_A(LINK_COLOSSEUM);
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = LINK_COLOSSEUM;
    // CALL(aDisableSpriteUpdates);
    DisableSpriteUpdates_Conv();
    // CALLFAR(aLinkCommunications);
    LinkCommunications();
    // CALL(aEnableSpriteUpdates);
    EnableSpriteUpdates_Conv();
    // XOR_A_A;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0;
    // RET;
}

void CloseLink(void){
    // XOR_A_A;
    // LD_addr_A(wLinkMode);
    wram->wLinkMode = 0;
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames_Conv(3);
    // JP(mLink_ResetSerialRegistersAfterLinkClosure);
    return Link_ResetSerialRegistersAfterLinkClosure();
}

void FailedLinkToPast(void){
    // LD_C(40);
    // CALL(aDelayFrames);
    DelayFrames_Conv(40);
    // LD_A(0xe);
    // JP(mLink_EnsureSync);
    Link_EnsureSync_Conv(0xe);
}

void Link_ResetSerialRegistersAfterLinkClosure(void){
    // LD_C(3);
    // CALL(aDelayFrames);
    DelayFrames_Conv(3);
    // LD_A(CONNECTION_NOT_ESTABLISHED);
    // LDH_addr_A(hSerialConnectionStatus);
    hram->hSerialConnectionStatus = CONNECTION_NOT_ESTABLISHED;
    // LD_A(USING_INTERNAL_CLOCK);
    // LDH_addr_A(rSB);
    gb_write(rSB, USING_INTERNAL_CLOCK);
    // XOR_A_A;
    // LDH_addr_A(hSerialReceive);
    hram->hSerialReceive = 0;
    // LDH_addr_A(rSC);
    gb_write(rSC, 0);
    // RET;
}

void Link_EnsureSync(void){
    ADD_A(0xd0);
    LD_addr_A(wLinkPlayerSyncBuffer);
    LD_addr_A(wLinkPlayerSyncBuffer + 1);
    LD_A(0x2);
    LDH_addr_A(hVBlank);
    CALL(aDelayFrame);
    CALL(aDelayFrame);

receive_loop:
    CALL(aSerial_ExchangeSyncBytes);
    LD_A_addr(wLinkReceivedSyncBuffer);
    LD_B_A;
    AND_A(0xf0);
    CP_A(0xd0);
    IF_Z goto done;
    LD_A_addr(wLinkReceivedSyncBuffer + 1);
    LD_B_A;
    AND_A(0xf0);
    CP_A(0xd0);
    IF_NZ goto receive_loop;


done:
    XOR_A_A;
    LDH_addr_A(hVBlank);
    LD_A_B;
    AND_A(0xf);
    RET;

}

uint8_t Link_EnsureSync_Conv(uint8_t a){
    printf("%s:\n", __func__);
    Network_FlushPendingPacketsAndSync();
    // ADD_A(0xd0);
    // LD_addr_A(wLinkPlayerSyncBuffer);
    wram->wLinkPlayerSyncBuffer[0] = a + 0xd0;
    // LD_addr_A(wLinkPlayerSyncBuffer + 1);
    wram->wLinkPlayerSyncBuffer[1] = a + 0xd0;
    // LD_A(0x2);
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0x2;
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aDelayFrame);
    DelayFrame();

    uint8_t b;
    do {
    // receive_loop:
        // CALL(aSerial_ExchangeSyncBytes);
        Serial_ExchangeSyncBytes();
        // LD_A_addr(wLinkReceivedSyncBuffer);
        // LD_B_A;
        b = wram->wLinkReceivedSyncBuffer[0];
        // AND_A(0xf0);
        // CP_A(0xd0);
        // IF_Z goto done;
        if((b & 0xf0) == 0xd0)
            break;
        // LD_A_addr(wLinkReceivedSyncBuffer + 1);
        b = wram->wLinkReceivedSyncBuffer[1];
        // LD_B_A;
        // AND_A(0xf0);
        // CP_A(0xd0);
        // IF_NZ goto receive_loop;
    } while((b & 0xf0) != 0xd0);


// done:
    // XOR_A_A;
    // LDH_addr_A(hVBlank);
    hram->hVBlank = 0;
    // LD_A_B;
    // AND_A(0xf);
    // RET;
    return b & 0xf;
}

void CableClubCheckWhichChris(void){
    // LDH_A_addr(hSerialConnectionStatus);
    // CP_A(USING_EXTERNAL_CLOCK);
    // LD_A(TRUE);
    // IF_Z goto yes;
    // DEC_A;  // FALSE


// yes:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = (hram->hSerialConnectionStatus == USING_EXTERNAL_CLOCK)? TRUE: FALSE;
    // RET;
}

// Returns true if the other player is playing as Kris, false otherwise.
void CableClubCheckOtherPlayerGender(void) {
    wram->wScriptVar = (bit_test(gOtherPlayerGender, PLAYERGENDER_FEMALE_F))? TRUE: FALSE;
}

void GSLinkCommsBorderGFX(void){
//  //  unreferenced
// INCBIN "gfx/trade/unused_gs_border_tiles.2bpp"

    return CheckSRAM0Flag();
}

void CheckSRAM0Flag(void){
//  //  unreferenced
//  input: hl = unknown flag array in "SRAM Bank 0"
    LD_A(MBANK(asScratch)); // LD_A(BANK("SRAM Bank 0"));
    CALL(aOpenSRAM);
    LD_D(0);
    LD_B(CHECK_FLAG);
    PREDEF(pSmallFarFlagAction);
    CALL(aCloseSRAM);
    LD_A_C;
    AND_A_A;
    RET;

}
