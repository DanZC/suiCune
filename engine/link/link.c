#include "../../constants.h"
#include "link.h"
#include "../../home/delay.h"
#include "../../home/serial.h"
#include "../../data/text/common.h"

void LinkCommunications(void){
    CALL(aClearBGPalettes);
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames_Conv(80);
    CALL(aClearScreen);
    CALL(aClearSprites);
    CALL(aUpdateSprites);
    // XOR_A_A;
    // LDH_addr_A(hSCX);
    hram->hSCX = 0;
    // LDH_addr_A(hSCY);
    hram->hSCY = 0;
    // LD_C(80);
    // CALL(aDelayFrames);
    DelayFrames_Conv(80);
    CALL(aClearScreen);
    CALL(aUpdateSprites);
    CALL(aLoadStandardFont);
    CALL(aLoadFontsBattleExtra);
    FARCALL(aLinkComms_LoadPleaseWaitTextboxBorderGFX);
    CALL(aWaitBGMap2);
    hlcoord(3, 8, wTilemap);
    LD_B(2);
    LD_C(12);
    LD_D_H;
    LD_E_L;
    FARCALL(aLinkTextbox2);
    hlcoord(4, 10, wTilemap);
    LD_DE(mString_PleaseWait);
    CALL(aPlaceString);
    CALL(aSetTradeRoomBGPals);
    CALL(aWaitBGMap2);
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
    CALL(aClearLinkData);
    CALL(aLink_PrepPartyData_Gen2);
    CALL(aFixDataForLinkTransfer);
    CALL(aCheckLinkTimeout_Gen2);
    LD_A_addr(wScriptVar);
    AND_A_A;
    JP_Z (mLinkTimeout);
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
    LD_BC(SERIAL_PREAMBLE_LENGTH + NAME_LENGTH + 1 + PARTY_LENGTH + 1 + 2 + (PARTYMON_STRUCT_LENGTH + NAME_LENGTH * 2) * PARTY_LENGTH + 3);
    CALL(aSerial_ExchangeBytes);
    LD_A(SERIAL_NO_DATA_BYTE);
    LD_de_A;

    LD_HL(wPlayerPatchLists);
    LD_DE(wOTPatchLists);
    LD_BC(200);
    CALL(aSerial_ExchangeBytes);

    LD_A_addr(wLinkMode);
    CP_A(LINK_TRADECENTER);
    IF_NZ goto not_trading;
    LD_HL(wLinkPlayerMail);
    LD_DE(wLinkOTMail);
    LD_BC(wLinkPlayerMailEnd - wLinkPlayerMail);
    CALL(aExchangeBytes);


not_trading:
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A((1 << JOYPAD) | (1 << SERIAL) | (1 << TIMER) | (1 << VBLANK));
    LDH_addr_A(rIE);
    LD_DE(MUSIC_NONE);
    CALL(aPlayMusic);

    CALL(aLink_CopyRandomNumbers);

    LD_HL(wOTPartyData);
    CALL(aLink_FindFirstNonControlCharacter_SkipZero);
    LD_DE(wLinkData);
    LD_BC(NAME_LENGTH + 1 + PARTY_LENGTH + 1 + 2 + (PARTYMON_STRUCT_LENGTH + NAME_LENGTH * 2) * PARTY_LENGTH);
    CALL(aLink_CopyOTData);

    LD_DE(wPlayerTrademon);
    LD_HL(wLinkPatchList1);
    LD_C(2);

loop1:
    LD_A_de;
    INC_DE;
    AND_A_A;
    IF_Z goto loop1;
    CP_A(SERIAL_PREAMBLE_BYTE);
    IF_Z goto loop1;
    CP_A(SERIAL_NO_DATA_BYTE);
    IF_Z goto loop1;
    CP_A(SERIAL_PATCH_LIST_PART_TERMINATOR);
    IF_Z goto next1;
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
    goto loop1;


next1:
    LD_HL(wLinkPatchList2);
    DEC_C;
    IF_NZ goto loop1;

    LD_A_addr(wLinkMode);
    CP_A(LINK_TRADECENTER);
    JP_NZ (mGen2ToGen2LinkComms_skip_mail);
    LD_HL(wLinkOTMail);

loop2:
    LD_A_hli;
    CP_A(SERIAL_MAIL_PREAMBLE_BYTE);
    IF_NZ goto loop2;

loop3:
    LD_A_hli;
    CP_A(SERIAL_NO_DATA_BYTE);
    IF_Z goto loop3;
    CP_A(SERIAL_MAIL_PREAMBLE_BYTE);
    IF_Z goto loop3;
    DEC_HL;
    LD_DE(wLinkOTMail);
    LD_BC(wLinkDataEnd - wLinkOTMail);  // should be wLinkOTMailEnd - wLinkOTMail
    CALL(aCopyBytes);
    LD_HL(wLinkOTMail);
    LD_BC((MAIL_MSG_LENGTH + 1) * PARTY_LENGTH);

loop4:
    LD_A_hl;
    CP_A(SERIAL_MAIL_REPLACEMENT_BYTE);
    IF_NZ goto okay1;
    LD_hl(SERIAL_NO_DATA_BYTE);

okay1:
    INC_HL;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop4;
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


skip_mail:
    LD_HL(wLinkPlayerName);
    LD_DE(wOTPlayerName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);

    LD_DE(wOTPartyCount);
    LD_BC(1 + PARTY_LENGTH + 1);
    CALL(aCopyBytes);

    LD_DE(wOTPlayerID);
    LD_BC(2);
    CALL(aCopyBytes);

    LD_DE(wOTPartyMons);
    LD_BC(wOTPartyDataEnd - wOTPartyMons);
    CALL(aCopyBytes);

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
    LD_A_addr(wLinkMode);
    CP_A(LINK_COLOSSEUM);
    IF_NZ goto ready_to_trade;
    LD_A(CAL);
    LD_addr_A(wOtherTrainerClass);
    CALL(aClearScreen);
    FARCALL(aLink_WaitBGMap);

    LD_HL(wOptions);
    LD_A_hl;
    PUSH_AF;
    AND_A(1 << STEREO);
    OR_A(TEXT_DELAY_MED);
    LD_hl_A;
    LD_HL(wOTPlayerName);
    LD_DE(wOTClassName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
    CALL(aReturnToMapFromSubmenu);
    LD_A_addr(wDisableTextAcceleration);
    PUSH_AF;
    LD_A(1);
    LD_addr_A(wDisableTextAcceleration);
    LDH_A_addr(rIE);
    PUSH_AF;
    LDH_A_addr(rIF);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(rIF);
    LDH_A_addr(rIE);
    SET_A(LCD_STAT);
    LDH_addr_A(rIE);
    POP_AF;
    LDH_addr_A(rIF);

// LET'S DO THIS
    PREDEF(pStartBattle);

    LDH_A_addr(rIF);
    LD_H_A;
    XOR_A_A;
    LDH_addr_A(rIF);
    POP_AF;
    LDH_addr_A(rIE);
    LD_A_H;
    LDH_addr_A(rIF);
    POP_AF;
    LD_addr_A(wDisableTextAcceleration);
    POP_AF;
    LD_addr_A(wOptions);

    FARCALL(aLoadPokemonData);
    JP(mExitLinkCommunications);


ready_to_trade:
    LD_DE(MUSIC_ROUTE_30);
    CALL(aPlayMusic);
    JP(mInitTradeMenuDisplay);

}

void LinkTimeout(void){
    LD_DE(mLinkTimeout_LinkTimeoutText);
    LD_B(10);

loop:
    CALL(aDelayFrame);
    CALL(aLinkDataReceived);
    DEC_B;
    IF_NZ goto loop;
    XOR_A_A;
    LD_hld_A;
    LD_hl_A;
    LDH_addr_A(hVBlank);
    PUSH_DE;
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    PUSH_DE;
    LD_D_H;
    LD_E_L;
    FARCALL(aLinkTextbox2);
    POP_DE;
    POP_HL;
    bccoord(1, 14, wTilemap);
    CALL(aPlaceHLTextAtBC);
    CALL(aRotateThreePalettesRight);
    CALL(aClearScreen);
    LD_B(SCGB_DIPLOMA);
    CALL(aGetSGBLayout);
    CALL(aWaitBGMap2);
    RET;


LinkTimeoutText:
    //text_far ['_LinkTimeoutText']
    //text_end ['?']

    return ExchangeBytes();
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

void String_PleaseWait(void){
    //db ['"PLEASE WAIT!@"'];

    return ClearLinkData();
}

void ClearLinkData(void){
    LD_HL(wLinkData);
    LD_BC(wLinkDataEnd - wLinkData);

loop:
    XOR_A_A;
    LD_hli_A;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop;
    RET;

}

void FixDataForLinkTransfer(void){
    LD_HL(wLinkBattleRNPreamble);
    LD_A(SERIAL_PREAMBLE_BYTE);
    LD_B(SERIAL_RN_PREAMBLE_LENGTH);

preamble_loop:
    LD_hli_A;
    DEC_B;
    IF_NZ goto preamble_loop;

    //assert ['wLinkBattleRNPreamble + SERIAL_RN_PREAMBLE_LENGTH == wLinkBattleRNs'];
    LD_B(SERIAL_RNS_LENGTH);

rn_loop:
    CALL(aRandom);
    CP_A(SERIAL_PREAMBLE_BYTE);
    IF_NC goto rn_loop;
    LD_hli_A;
    DEC_B;
    IF_NZ goto rn_loop;

    LD_HL(wPlayerPatchLists);
    LD_A(SERIAL_PREAMBLE_BYTE);
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;

    LD_B(200);
    XOR_A_A;

loop1:
    LD_hli_A;
    DEC_B;
    IF_NZ goto loop1;

    LD_HL((wLinkData + SERIAL_PREAMBLE_LENGTH + NAME_LENGTH + 1 + PARTY_LENGTH + 1) - 1);
    LD_DE(wPlayerPatchLists + 10);  // ???
    LD_BC((0 << 8) | 0);

loop2:
    INC_C;
    LD_A_C;
    CP_A(SERIAL_PATCH_LIST_LENGTH + 1);
    IF_Z goto next1;
    LD_A_B;
    DEC_A;
    IF_NZ goto next2;
    PUSH_BC;
    LD_A_addr(wLinkMode);
    CP_A(LINK_TIMECAPSULE);
    LD_B(REDMON_STRUCT_LENGTH * PARTY_LENGTH - SERIAL_PATCH_LIST_LENGTH + 1);
    IF_Z goto got_value;
    LD_B(2 + PARTYMON_STRUCT_LENGTH * PARTY_LENGTH - SERIAL_PATCH_LIST_LENGTH + 1);

got_value:
    LD_A_C;
    CP_A_B;
    POP_BC;
    IF_Z goto done;

next2:
    INC_HL;
    LD_A_hl;
    CP_A(SERIAL_NO_DATA_BYTE);
    IF_NZ goto loop2;
    LD_A_C;
    LD_de_A;
    INC_DE;
    LD_hl(SERIAL_PATCH_REPLACEMENT_BYTE);
    goto loop2;


next1:
    LD_A(SERIAL_PATCH_LIST_PART_TERMINATOR);
    LD_de_A;
    INC_DE;
    LD_BC((1 << 8) | 0);
    goto loop2;


done:
    LD_A(SERIAL_PATCH_LIST_PART_TERMINATOR);
    LD_de_A;
    RET;

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

    LD_HL(wPartyCount);
    LD_BC(1 + PARTY_LENGTH + 1);
    CALL(aCopyBytes);

    LD_HL(wPlayerID);
    LD_BC(2);
    CALL(aCopyBytes);

    LD_HL(wPartyMon1Species);
    LD_BC(PARTY_LENGTH * PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);

    LD_HL(wPartyMonOTs);
    LD_BC(PARTY_LENGTH * NAME_LENGTH);
    CALL(aCopyBytes);

    LD_HL(wPartyMonNicknames);
    LD_BC(PARTY_LENGTH * MON_NAME_LENGTH);
    CALL(aCopyBytes);

//  Okay, we did all that.  Now, are we in the trade center?
    LD_A_addr(wLinkMode);
    CP_A(LINK_TRADECENTER);
    RET_NZ ;

//  Fill 5 bytes at wLinkPlayerMailPreamble with $20
    LD_DE(wLinkPlayerMailPreamble);
    LD_A(SERIAL_MAIL_PREAMBLE_BYTE);
    CALL(aLink_CopyMailPreamble);

//  Copy all the mail messages to wLinkPlayerMailMessages
    LD_A(BANK(sPartyMail));
    CALL(aOpenSRAM);
    LD_HL(sPartyMail);
    LD_B(PARTY_LENGTH);

loop2:
    PUSH_BC;
    LD_BC(MAIL_MSG_LENGTH + 1);
    CALL(aCopyBytes);
    LD_BC(MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1));
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto loop2;
//  Copy the mail data to wLinkPlayerMailMetadata
    LD_HL(sPartyMail);
    LD_B(PARTY_LENGTH);

loop3:
    PUSH_BC;
    LD_BC(MAIL_MSG_LENGTH + 1);
    ADD_HL_BC;
    LD_BC(MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1));
    CALL(aCopyBytes);
    POP_BC;
    DEC_B;
    IF_NZ goto loop3;
    LD_B(PARTY_LENGTH);
    LD_DE(sPartyMail);
    LD_HL(wLinkPlayerMailMessages);

loop4:
    PUSH_BC;
    PUSH_HL;
    PUSH_DE;
    PUSH_HL;
    FARCALL(aIsMailEuropean);
    POP_DE;
    LD_A_C;
    OR_A_A;
    IF_Z goto next;
    SUB_A(0x3);
    IF_NC goto italian_spanish;
    FARCALL(aConvertFrenchGermanMailToEnglish);
    goto next;

italian_spanish:
    CP_A(0x2);
    IF_NC goto next;
    FARCALL(aConvertSpanishItalianMailToEnglish);

next:
    POP_DE;
    LD_HL(MAIL_STRUCT_LENGTH);
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_BC(MAIL_MSG_LENGTH + 1);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto loop4;
    CALL(aCloseSRAM);

    LD_HL(wLinkPlayerMailMessages);
    LD_BC((MAIL_MSG_LENGTH + 1) * PARTY_LENGTH);

loop5:
    LD_A_hl;
    CP_A(SERIAL_NO_DATA_BYTE);
    IF_NZ goto skip2;
    LD_hl(SERIAL_MAIL_REPLACEMENT_BYTE);

skip2:
    INC_HL;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto loop5;

    LD_HL(wLinkPlayerMailMetadata);
    LD_DE(wLinkPlayerMailPatchSet);
    LD_B((MAIL_STRUCT_LENGTH - (MAIL_MSG_LENGTH + 1)) * PARTY_LENGTH);
    LD_C(0);

loop6:
    INC_C;
    LD_A_hl;
    CP_A(SERIAL_NO_DATA_BYTE);
    IF_NZ goto skip3;
    LD_hl(SERIAL_PATCH_REPLACEMENT_BYTE);
    LD_A_C;
    LD_de_A;
    INC_DE;

skip3:
    INC_HL;
    DEC_B;
    IF_NZ goto loop6;

    LD_A(SERIAL_PATCH_LIST_PART_TERMINATOR);
    LD_de_A;
    RET;

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

void Link_CopyRandomNumbers(void){
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_INTERNAL_CLOCK);
    RET_Z ;
    LD_HL(wEnemyMonSpecies);
    CALL(aLink_FindFirstNonControlCharacter_AllowZero);
    LD_DE(wLinkBattleRNs);
    LD_C(10);

loop:
    LD_A_hli;
    CP_A(SERIAL_NO_DATA_BYTE);
    IF_Z goto loop;
    CP_A(SERIAL_PREAMBLE_BYTE);
    IF_Z goto loop;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void Link_FindFirstNonControlCharacter_SkipZero(void){

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto loop;
    CP_A(SERIAL_PREAMBLE_BYTE);
    IF_Z goto loop;
    CP_A(SERIAL_NO_DATA_BYTE);
    IF_Z goto loop;
    DEC_HL;
    RET;

}

void Link_FindFirstNonControlCharacter_AllowZero(void){

loop:
    LD_A_hli;
    CP_A(SERIAL_PREAMBLE_BYTE);
    IF_Z goto loop;
    CP_A(SERIAL_NO_DATA_BYTE);
    IF_Z goto loop;
    DEC_HL;
    RET;

}

void InitTradeMenuDisplay(void){
    CALL(aClearScreen);
    CALL(aLoadTradeScreenBorderGFX);
    FARCALL(aInitTradeSpeciesList);
    XOR_A_A;
    LD_HL(wOtherPlayerLinkMode);
    LD_hli_A;
    LD_hli_A;
    LD_hli_A;
    LD_hl_A;
    LD_A(1);
    LD_addr_A(wMenuCursorY);
    INC_A;
    LD_addr_A(wPlayerLinkAction);
    JP(mLinkTrade_PlayerPartyMenu);

}

void LinkTrade_OTPartyMenu(void){
    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);
    LD_A(A_BUTTON | D_UP | D_DOWN);
    LD_addr_A(wMenuJoypadFilter);
    LD_A_addr(wOTPartyCount);
    LD_addr_A(w2DMenuNumRows);
    LD_A(1);
    LD_addr_A(w2DMenuNumCols);
    LD_A(9);
    LD_addr_A(w2DMenuCursorInitY);
    LD_A(6);
    LD_addr_A(w2DMenuCursorInitX);
    LD_A(1);
    LD_addr_A(wMenuCursorX);
    LD_A((1 << 4) | 0);
    LD_addr_A(w2DMenuCursorOffsets);
    LD_A(MENU_UNUSED_3);
    LD_addr_A(w2DMenuFlags1);
    XOR_A_A;
    LD_addr_A(w2DMenuFlags2);

    return LinkTradeOTPartymonMenuLoop();
}

void LinkTradeOTPartymonMenuLoop(void){
    FARCALL(aLinkTradeMenu);
    LD_A_D;
    AND_A_A;
    JP_Z (mLinkTradePartiesMenuMasterLoop);
    BIT_A(A_BUTTON_F);
    IF_Z goto not_a_button;
    LD_A(INIT_ENEMYOT_LIST);
    LD_addr_A(wInitListType);
    CALLFAR(aInitList);
    LD_HL(wOTPartyMon1Species);
    FARCALL(aLinkMonStatsScreen);
    JP(mLinkTradePartiesMenuMasterLoop);


not_a_button:
    BIT_A(D_UP_F);
    IF_Z goto not_d_up;
    LD_A_addr(wMenuCursorY);
    LD_B_A;
    LD_A_addr(wOTPartyCount);
    CP_A_B;
    JP_NZ (mLinkTradePartiesMenuMasterLoop);
    XOR_A_A;
    LD_addr_A(wMonType);
    CALL(aHideCursor);
    PUSH_HL;
    PUSH_BC;
    LD_BC(NAME_LENGTH);
    ADD_HL_BC;
    LD_hl(0x7f);
    POP_BC;
    POP_HL;
    LD_A_addr(wPartyCount);
    LD_addr_A(wMenuCursorY);
    JR(mLinkTrade_PlayerPartyMenu);


not_d_up:
    BIT_A(D_DOWN_F);
    JP_Z (mLinkTradePartiesMenuMasterLoop);
    JP(mLinkTradeOTPartymonMenuCheckCancel);

}

void LinkTrade_PlayerPartyMenu(void){
    FARCALL(aInitMG_Mobile_LinkTradePalMap);
    XOR_A_A;
    LD_addr_A(wMonType);
    LD_A(A_BUTTON | D_UP | D_DOWN);
    LD_addr_A(wMenuJoypadFilter);
    LD_A_addr(wPartyCount);
    LD_addr_A(w2DMenuNumRows);
    LD_A(1);
    LD_addr_A(w2DMenuNumCols);
    LD_A(1);
    LD_addr_A(w2DMenuCursorInitY);
    LD_A(6);
    LD_addr_A(w2DMenuCursorInitX);
    LD_A(1);
    LD_addr_A(wMenuCursorX);
    LD_A((1 << 4) | 0);
    LD_addr_A(w2DMenuCursorOffsets);
    LD_A(MENU_UNUSED_3);
    LD_addr_A(w2DMenuFlags1);
    XOR_A_A;
    LD_addr_A(w2DMenuFlags2);
    CALL(aWaitBGMap2);

    return LinkTradePartymonMenuLoop();
}

void LinkTradePartymonMenuLoop(void){
    FARCALL(aLinkTradeMenu);
    LD_A_D;
    AND_A_A;
    IF_NZ goto check_joypad;
    JP(mLinkTradePartiesMenuMasterLoop);


check_joypad:
    BIT_A(A_BUTTON_F);
    IF_Z goto not_a_button;
    JP(mLinkTrade_TradeStatsMenu);


not_a_button:
    BIT_A(D_DOWN_F);
    IF_Z goto not_d_down;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    JP_NZ (mLinkTradePartiesMenuMasterLoop);
    LD_A(OTPARTYMON);
    LD_addr_A(wMonType);
    CALL(aHideCursor);
    PUSH_HL;
    PUSH_BC;
    LD_BC(NAME_LENGTH);
    ADD_HL_BC;
    LD_hl(0x7f);
    POP_BC;
    POP_HL;
    LD_A(1);
    LD_addr_A(wMenuCursorY);
    JP(mLinkTrade_OTPartyMenu);


not_d_down:
    BIT_A(D_UP_F);
    JR_Z (mLinkTradePartiesMenuMasterLoop);
    LD_A_addr(wMenuCursorY);
    LD_B_A;
    LD_A_addr(wPartyCount);
    CP_A_B;
    JR_NZ (mLinkTradePartiesMenuMasterLoop);
    CALL(aHideCursor);
    PUSH_HL;
    PUSH_BC;
    LD_BC(NAME_LENGTH);
    ADD_HL_BC;
    LD_hl(0x7f);
    POP_BC;
    POP_HL;
    JP(mLinkTradePartymonMenuCheckCancel);

}

void LinkTradePartiesMenuMasterLoop(void){
    LD_A_addr(wMonType);
    AND_A_A;
    JP_Z (mLinkTradePartymonMenuLoop);  // PARTYMON
    JP(mLinkTradeOTPartymonMenuLoop);  // OTPARTYMON

}

void LinkTrade_TradeStatsMenu(void){
    CALL(aLoadTilemapToTempTilemap);
    LD_A_addr(wMenuCursorY);
    PUSH_AF;
    hlcoord(0, 15, wTilemap);
    LD_B(1);
    LD_C(18);
    CALL(aLinkTextboxAtHL);
    hlcoord(2, 16, wTilemap);
    LD_DE(mLinkTrade_TradeStatsMenu_String_Stats_Trade);
    CALL(aPlaceString);
    FARCALL(aLink_WaitBGMap);


joy_loop:
    LD_A(0x7f);
    ldcoord_a(11, 16, wTilemap);
    LD_A(A_BUTTON | B_BUTTON | D_RIGHT);
    LD_addr_A(wMenuJoypadFilter);
    LD_A(1);
    LD_addr_A(w2DMenuNumRows);
    LD_A(1);
    LD_addr_A(w2DMenuNumCols);
    LD_A(16);
    LD_addr_A(w2DMenuCursorInitY);
    LD_A(1);
    LD_addr_A(w2DMenuCursorInitX);
    LD_A(1);
    LD_addr_A(wMenuCursorY);
    LD_addr_A(wMenuCursorX);
    LD_A((2 << 4) | 0);
    LD_addr_A(w2DMenuCursorOffsets);
    XOR_A_A;
    LD_addr_A(w2DMenuFlags1);
    LD_addr_A(w2DMenuFlags2);
    CALL(aScrollingMenuJoypad);
    BIT_A(D_RIGHT_F);
    IF_NZ goto d_right;
    BIT_A(B_BUTTON_F);
    IF_Z goto show_stats;

b_button:
    POP_AF;
    LD_addr_A(wMenuCursorY);
    CALL(aSafeLoadTempTilemapToTilemap);
    JP(mLinkTrade_PlayerPartyMenu);


d_right:
    LD_A(0x7f);
    ldcoord_a(1, 16, wTilemap);
    LD_A(A_BUTTON | B_BUTTON | D_LEFT);
    LD_addr_A(wMenuJoypadFilter);
    LD_A(1);
    LD_addr_A(w2DMenuNumRows);
    LD_A(1);
    LD_addr_A(w2DMenuNumCols);
    LD_A(16);
    LD_addr_A(w2DMenuCursorInitY);
    LD_A(11);
    LD_addr_A(w2DMenuCursorInitX);
    LD_A(1);
    LD_addr_A(wMenuCursorY);
    LD_addr_A(wMenuCursorX);
    LD_A((2 << 4) | 0);
    LD_addr_A(w2DMenuCursorOffsets);
    XOR_A_A;
    LD_addr_A(w2DMenuFlags1);
    LD_addr_A(w2DMenuFlags2);
    CALL(aScrollingMenuJoypad);
    BIT_A(D_LEFT_F);
    JP_NZ (mLinkTrade_TradeStatsMenu_joy_loop);
    BIT_A(B_BUTTON_F);
    IF_NZ goto b_button;
    goto try_trade;


show_stats:
    POP_AF;
    LD_addr_A(wMenuCursorY);
    LD_A(INIT_PLAYEROT_LIST);
    LD_addr_A(wInitListType);
    CALLFAR(aInitList);
    FARCALL(aLinkMonStatsScreen);
    CALL(aSafeLoadTempTilemapToTilemap);
    hlcoord(6, 1, wTilemap);
    LD_BC((6 << 8) | 1);
    LD_A(0x7f);
    CALL(aLinkEngine_FillBox);
    hlcoord(17, 1, wTilemap);
    LD_BC((6 << 8) | 1);
    LD_A(0x7f);
    CALL(aLinkEngine_FillBox);
    JP(mLinkTrade_PlayerPartyMenu);


try_trade:
    CALL(aPlaceHollowCursor);
    POP_AF;
    LD_addr_A(wMenuCursorY);
    DEC_A;
    LD_addr_A(wCurTradePartyMon);
    LD_addr_A(wPlayerLinkAction);
    FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
    LD_A_addr(wOtherPlayerLinkMode);
    CP_A(0xf);
    JP_Z (mInitTradeMenuDisplay);
    LD_addr_A(wCurOTTradePartyMon);
    CALL(aLinkTradePlaceArrow);
    LD_C(100);
    CALL(aDelayFrames);
    FARCALL(aValidateOTTrademon);
    IF_C goto abnormal;
    FARCALL(aCheckAnyOtherAliveMonsForTrade);
    JP_NC (mLinkTrade);
    XOR_A_A;
    LD_addr_A(wUnusedLinkAction);
    LD_addr_A(wOtherPlayerLinkAction);
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    CALL(aLinkTextboxAtHL);
    FARCALL(aLink_WaitBGMap);
    LD_HL(mLinkTrade_TradeStatsMenu_LinkTradeCantBattleText);
    bccoord(1, 14, wTilemap);
    CALL(aPlaceHLTextAtBC);
    goto cancel_trade;


abnormal:
    XOR_A_A;
    LD_addr_A(wUnusedLinkAction);
    LD_addr_A(wOtherPlayerLinkAction);
    LD_A_addr(wCurOTTradePartyMon);
    LD_HL(wOTPartySpecies);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    CALL(aLinkTextboxAtHL);
    FARCALL(aLink_WaitBGMap);
    LD_HL(mLinkTrade_TradeStatsMenu_LinkAbnormalMonText);
    bccoord(1, 14, wTilemap);
    CALL(aPlaceHLTextAtBC);


cancel_trade:
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    CALL(aLinkTextboxAtHL);
    hlcoord(1, 14, wTilemap);
    LD_DE(mString_TooBadTheTradeWasCanceled);
    CALL(aPlaceString);
    LD_A(0x1);
    LD_addr_A(wPlayerLinkAction);
    FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
    LD_C(100);
    CALL(aDelayFrames);
    JP(mInitTradeMenuDisplay);


LinkTradeCantBattleText:
    //text_far ['_LinkTradeCantBattleText']
    //text_end ['?']


String_Stats_Trade:
    //db ['"STATS\t TRADE@"'];


LinkAbnormalMonText:
    //text_far ['_LinkAbnormalMonText']
    //text_end ['?']

    return LinkTradeOTPartymonMenuCheckCancel();
}

void LinkTradeOTPartymonMenuCheckCancel(void){
    LD_A_addr(wMenuCursorY);
    CP_A(1);
    JP_NZ (mLinkTradePartiesMenuMasterLoop);
    CALL(aHideCursor);

    PUSH_HL;
    PUSH_BC;
    LD_BC(NAME_LENGTH);
    ADD_HL_BC;
    LD_hl(0x7f);
    POP_BC;
    POP_HL;
// fallthrough

    return LinkTradePartymonMenuCheckCancel();
}

void LinkTradePartymonMenuCheckCancel(void){

loop1:
    LD_A(0xed);
    ldcoord_a(9, 17, wTilemap);

loop2:
    CALL(aJoyTextDelay);
    LDH_A_addr(hJoyLast);
    AND_A_A;
    IF_Z goto loop2;
    BIT_A(A_BUTTON_F);
    IF_NZ goto a_button;
    PUSH_AF;
    LD_A(0x7f);
    ldcoord_a(9, 17, wTilemap);
    POP_AF;
    BIT_A(D_UP_F);
    IF_Z goto d_up;
    LD_A_addr(wOTPartyCount);
    LD_addr_A(wMenuCursorY);
    JP(mLinkTrade_OTPartyMenu);


d_up:
    LD_A(0x1);
    LD_addr_A(wMenuCursorY);
    JP(mLinkTrade_PlayerPartyMenu);


a_button:
    LD_A(0xec);
    ldcoord_a(9, 17, wTilemap);
    LD_A(0xf);
    LD_addr_A(wPlayerLinkAction);
    FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
    LD_A_addr(wOtherPlayerLinkMode);
    CP_A(0xf);
    IF_NZ goto loop1;
// fallthrough

    return ExitLinkCommunications();
}

void ExitLinkCommunications(void){
    CALL(aRotateThreePalettesRight);
    CALL(aClearScreen);
    LD_B(SCGB_DIPLOMA);
    CALL(aGetSGBLayout);
    CALL(aWaitBGMap2);
    XOR_A_A;
    LD_addr_A(wUnusedLinkCommunicationByte);
    XOR_A_A;
    LDH_addr_A(rSB);
    LDH_addr_A(hSerialSend);
    LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);
    RET;

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

void LinkTradePlaceArrow(void){
//  Indicates which pokemon the other player has selected to trade
    LD_A_addr(wOtherPlayerLinkMode);
    hlcoord(6, 9, wTilemap);
    LD_BC(SCREEN_WIDTH);
    CALL(aAddNTimes);
    LD_hl(0xec);
    RET;

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

void LinkTrade(void){
    XOR_A_A;
    LD_addr_A(wUnusedLinkAction);
    LD_addr_A(wOtherPlayerLinkAction);
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    CALL(aLinkTextboxAtHL);
    FARCALL(aLink_WaitBGMap);
    LD_A_addr(wCurTradePartyMon);
    LD_HL(wPartySpecies);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(wStringBuffer1);
    LD_DE(wBufferTrademonNickname);
    LD_BC(MON_NAME_LENGTH);
    CALL(aCopyBytes);
    LD_A_addr(wCurOTTradePartyMon);
    LD_HL(wOTPartySpecies);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    LD_HL(mLinkAskTradeForText);
    bccoord(1, 14, wTilemap);
    CALL(aPlaceHLTextAtBC);
    CALL(aLoadStandardMenuHeader);
    hlcoord(10, 7, wTilemap);
    LD_B(3);
    LD_C(7);
    CALL(aLinkTextboxAtHL);
    LD_DE(mString_TradeCancel);
    hlcoord(12, 8, wTilemap);
    CALL(aPlaceString);
    LD_A(8);
    LD_addr_A(w2DMenuCursorInitY);
    LD_A(11);
    LD_addr_A(w2DMenuCursorInitX);
    LD_A(1);
    LD_addr_A(w2DMenuNumCols);
    LD_A(2);
    LD_addr_A(w2DMenuNumRows);
    XOR_A_A;
    LD_addr_A(w2DMenuFlags1);
    LD_addr_A(w2DMenuFlags2);
    LD_A(0x20);
    LD_addr_A(w2DMenuCursorOffsets);
    LD_A(A_BUTTON | B_BUTTON);
    LD_addr_A(wMenuJoypadFilter);
    LD_A(1);
    LD_addr_A(wMenuCursorY);
    LD_addr_A(wMenuCursorX);
    FARCALL(aLink_WaitBGMap);
    CALL(aScrollingMenuJoypad);
    PUSH_AF;
    CALL(aCall_ExitMenu);
    CALL(aWaitBGMap2);
    POP_AF;
    BIT_A(1);
    IF_NZ goto canceled;
    LD_A_addr(wMenuCursorY);
    DEC_A;
    IF_Z goto try_trade;


canceled:
    LD_A(0x1);
    LD_addr_A(wPlayerLinkAction);
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    CALL(aLinkTextboxAtHL);
    hlcoord(1, 14, wTilemap);
    LD_DE(mString_TooBadTheTradeWasCanceled);
    CALL(aPlaceString);
    FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
    JP(mInitTradeMenuDisplay_Delay);


try_trade:
    LD_A(0x2);
    LD_addr_A(wPlayerLinkAction);
    FARCALL(aPrintWaitingTextAndSyncAndExchangeNybble);
    LD_A_addr(wOtherPlayerLinkMode);
    DEC_A;
    IF_NZ goto do_trade;
//  If we're here, the other player canceled the trade
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    CALL(aLinkTextboxAtHL);
    hlcoord(1, 14, wTilemap);
    LD_DE(mString_TooBadTheTradeWasCanceled);
    CALL(aPlaceString);
    JP(mInitTradeMenuDisplay_Delay);


do_trade:
    LD_HL(sPartyMail);
    LD_A_addr(wCurTradePartyMon);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(sPartyMail));
    CALL(aOpenSRAM);
    LD_D_H;
    LD_E_L;
    LD_BC(MAIL_STRUCT_LENGTH);
    ADD_HL_BC;
    LD_A_addr(wCurTradePartyMon);
    LD_C_A;

copy_mail:
    INC_C;
    LD_A_C;
    CP_A(PARTY_LENGTH);
    IF_Z goto copy_player_data;
    PUSH_BC;
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aCopyBytes);
    POP_BC;
    goto copy_mail;


copy_player_data:
    LD_HL(sPartyMail);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    PUSH_HL;
    LD_HL(wLinkPlayerMail);
    LD_A_addr(wCurOTTradePartyMon);
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aAddNTimes);
    POP_DE;
    LD_BC(MAIL_STRUCT_LENGTH);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);

//  Buffer player data
//  nickname
    LD_HL(wPlayerName);
    LD_DE(wPlayerTrademonSenderName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
//  species
    LD_A_addr(wCurTradePartyMon);
    LD_HL(wPartySpecies);
    LD_B(0);
    LD_C_A;
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wPlayerTrademonSpecies);
    PUSH_AF;
//  OT name
    LD_A_addr(wCurTradePartyMon);
    LD_HL(wPartyMonOTs);
    CALL(aSkipNames);
    LD_DE(wPlayerTrademonOTName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
//  ID
    LD_HL(wPartyMon1ID);
    LD_A_addr(wCurTradePartyMon);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wPlayerTrademonID);
    LD_A_hl;
    LD_addr_A(wPlayerTrademonID + 1);
//  DVs
    LD_HL(wPartyMon1DVs);
    LD_A_addr(wCurTradePartyMon);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wPlayerTrademonDVs);
    LD_A_hl;
    LD_addr_A(wPlayerTrademonDVs + 1);
//  caught data
    LD_A_addr(wCurTradePartyMon);
    LD_HL(wPartyMon1Species);
    CALL(aGetPartyLocation);
    LD_B_H;
    LD_C_L;
    FARCALL(aGetCaughtGender);
    LD_A_C;
    LD_addr_A(wPlayerTrademonCaughtData);

//  Buffer other player data
//  nickname
    LD_HL(wOTPlayerName);
    LD_DE(wOTTrademonSenderName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
//  species
    LD_A_addr(wCurOTTradePartyMon);
    LD_HL(wOTPartySpecies);
    LD_B(0);
    LD_C_A;
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wOTTrademonSpecies);
//  OT name
    LD_A_addr(wCurOTTradePartyMon);
    LD_HL(wOTPartyMonOTs);
    CALL(aSkipNames);
    LD_DE(wOTTrademonOTName);
    LD_BC(NAME_LENGTH);
    CALL(aCopyBytes);
//  ID
    LD_HL(wOTPartyMon1ID);
    LD_A_addr(wCurOTTradePartyMon);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wOTTrademonID);
    LD_A_hl;
    LD_addr_A(wOTTrademonID + 1);
//  DVs
    LD_HL(wOTPartyMon1DVs);
    LD_A_addr(wCurOTTradePartyMon);
    CALL(aGetPartyLocation);
    LD_A_hli;
    LD_addr_A(wOTTrademonDVs);
    LD_A_hl;
    LD_addr_A(wOTTrademonDVs + 1);
//  caught data
    LD_A_addr(wCurOTTradePartyMon);
    LD_HL(wOTPartyMon1Species);
    CALL(aGetPartyLocation);
    LD_B_H;
    LD_C_L;
    FARCALL(aGetCaughtGender);
    LD_A_C;
    LD_addr_A(wOTTrademonCaughtData);

    LD_A_addr(wCurTradePartyMon);
    LD_addr_A(wCurPartyMon);
    LD_HL(wPartySpecies);
    LD_B(0);
    LD_C_A;
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurTradePartyMon);

    XOR_A_A;  // REMOVE_PARTY
    LD_addr_A(wPokemonWithdrawDepositParameter);
    CALLFAR(aRemoveMonFromPartyOrBox);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    LD_A(TRUE);
    LD_addr_A(wForceEvolution);
    LD_A_addr(wCurOTTradePartyMon);
    PUSH_AF;
    LD_HL(wOTPartySpecies);
    LD_B(0);
    LD_C_A;
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wCurOTTradePartyMon);

    LD_C(100);
    CALL(aDelayFrames);
    CALL(aClearTilemap);
    CALL(aLoadFontsBattleExtra);
    LD_B(SCGB_DIPLOMA);
    CALL(aGetSGBLayout);
    LDH_A_addr(hSerialConnectionStatus);
    CP_A(USING_EXTERNAL_CLOCK);
    IF_Z goto player_2;
    PREDEF(pTradeAnimation);
    goto done_animation;


player_2:
    PREDEF(pTradeAnimationPlayer2);


done_animation:
    POP_AF;
    LD_C_A;
    LD_addr_A(wCurPartyMon);
    LD_HL(wOTPartySpecies);
    LD_D(0);
    LD_E_A;
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wCurPartySpecies);
    LD_HL(wOTPartyMon1Species);
    LD_A_C;
    CALL(aGetPartyLocation);
    LD_DE(wTempMonSpecies);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aCopyBytes);
    PREDEF(pAddTempmonToParty);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_addr_A(wCurPartyMon);
    CALLFAR(aEvolvePokemon);
    CALL(aClearScreen);
    CALL(aLoadTradeScreenBorderGFX);
    CALL(aSetTradeRoomBGPals);
    FARCALL(aLink_WaitBGMap);

//  Check if either of the Pokémon sent was a Mew or Celebi, and send a different
//  byte depending on that. Presumably this would've been some prevention against
//  illicit trade machines, but it doesn't seem like a very effective one.
//  Removing this code breaks link compatibility with the vanilla gen2 games, but
//  has otherwise no consequence.
    LD_B(1);
    POP_AF;
    LD_C_A;
    CP_A(MEW);
    IF_Z goto send_checkbyte;
    LD_A_addr(wCurPartySpecies);
    CP_A(MEW);
    IF_Z goto send_checkbyte;
    LD_B(2);
    LD_A_C;
    CP_A(CELEBI);
    IF_Z goto send_checkbyte;
    LD_A_addr(wCurPartySpecies);
    CP_A(CELEBI);
    IF_Z goto send_checkbyte;

//  Send the byte in a loop until the desired byte has been received.
    LD_B(0);

send_checkbyte:
    LD_A_B;
    LD_addr_A(wPlayerLinkAction);
    PUSH_BC;
    CALL(aSerial_PrintWaitingTextAndSyncAndExchangeNybble);
    POP_BC;
    LD_A_addr(wLinkMode);
    CP_A(LINK_TIMECAPSULE);
    IF_Z goto save;
    LD_A_B;
    AND_A_A;
    IF_Z goto save;
    LD_A_addr(wOtherPlayerLinkAction);
    CP_A_B;
    IF_NZ goto send_checkbyte;


save:
    FARCALL(aSaveAfterLinkTrade);
    FARCALL(aStubbedTrainerRankings_Trades);
    FARCALL(aBackupMobileEventIndex);
    LD_C(40);
    CALL(aDelayFrames);
    hlcoord(0, 12, wTilemap);
    LD_B(4);
    LD_C(18);
    CALL(aLinkTextboxAtHL);
    hlcoord(1, 14, wTilemap);
    LD_DE(mString_TradeCompleted);
    CALL(aPlaceString);
    FARCALL(aLink_WaitBGMap);
    LD_C(50);
    CALL(aDelayFrames);
    LD_A_addr(wLinkMode);
    CP_A(LINK_TIMECAPSULE);
    JP_Z (mGen2ToGen1LinkComms);
    JP(mGen2ToGen2LinkComms);

}

void InitTradeMenuDisplay_Delay(void){
    LD_C(100);
    CALL(aDelayFrames);
    JP(mInitTradeMenuDisplay);

}

void String_TradeCancel(void){
    //db ['"TRADE"'];
    //next ['"CANCEL@"']
}

const struct TextCmd LinkAskTradeForText[] = {
    text_far(v_LinkAskTradeForText)
    text_end
};

void String_TradeCompleted(void){
    //db ['"Trade completed!@"'];

    return String_TooBadTheTradeWasCanceled();
}

void String_TooBadTheTradeWasCanceled(void){
    //db ['"Too bad! The trade"'];
    //next ['"was canceled!@"']

    return LinkTextboxAtHL();
}

void LinkTextboxAtHL(void){
    LD_D_H;
    LD_E_L;
    FARCALL(aLinkTextbox);
    RET;

}

void LoadTradeScreenBorderGFX(void){
    FARCALL(av_LoadTradeScreenBorderGFX);
    RET;

}

void SetTradeRoomBGPals(void){
    FARCALL(aLoadTradeRoomBGPals);  // just a nested farcall// so wasteful
    CALL(aSetPalettes);
    RET;

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
    LD_C(3);
    CALL(aDelayFrames);
    LD_A(CONNECTION_NOT_ESTABLISHED);
    LDH_addr_A(hSerialConnectionStatus);
    XOR_A_A;
    LDH_addr_A(rSB);
    LDH_addr_A(hSerialReceive);
    LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_C(3);
    CALL(aDelayFrames);
    XOR_A_A;
    LDH_addr_A(rSB);
    LDH_addr_A(hSerialReceive);
    LD_A((0 << rSC_ON) | (0 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_A((1 << rSC_ON) | (0 << rSC_CLOCK));
    LDH_addr_A(rSC);
    LD_C(3);
    CALL(aDelayFrames);
    XOR_A_A;
    LDH_addr_A(rSB);
    LDH_addr_A(hSerialReceive);
    LDH_addr_A(rSC);
    LD_C(3);
    CALL(aDelayFrames);
    LD_A(CONNECTION_NOT_ESTABLISHED);
    LDH_addr_A(hSerialConnectionStatus);
    LDH_A_addr(rIF);
    PUSH_AF;
    XOR_A_A;
    LDH_addr_A(rIF);
    LD_A(IE_DEFAULT);
    LDH_addr_A(rIE);
    POP_AF;
    LDH_addr_A(rIF);
    LD_HL(wLinkTimeoutFrames);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    LDH_addr_A(hVBlank);
    LD_addr_A(wLinkMode);
    RET;

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
        gb_write(rSB, USING_EXTERNAL_CLOCK);
        // LD_A((0 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        gb_write(rSC, (0 << rSC_ON) | (1 << rSC_CLOCK));
        // LD_A((1 << rSC_ON) | (1 << rSC_CLOCK));
        // LDH_addr_A(rSC);
        gb_write(rSC, (1 << rSC_ON) | (1 << rSC_CLOCK));
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
    LD_A(0x1);
    LD_addr_A(wPlayerLinkAction);
    LD_HL(wLinkTimeoutFrames);
    LD_A(3);
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    CALL(aWaitBGMap);
    LD_A(0x2);
    LDH_addr_A(hVBlank);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    CALL(aLink_CheckCommunicationError);
    XOR_A_A;
    LDH_addr_A(hVBlank);
    LD_A_addr(wScriptVar);
    AND_A_A;
    RET_NZ ;
    JP(mLink_ResetSerialRegistersAfterLinkClosure);

}

void CheckLinkTimeout_Gen2(void){
//  if wScriptVar = 0 on exit, link connection is closed
    LD_A(0x5);
    LD_addr_A(wPlayerLinkAction);
    LD_HL(wLinkTimeoutFrames);
    LD_A(3);
    LD_hli_A;
    XOR_A_A;
    LD_hl_A;
    CALL(aWaitBGMap);
    LD_A(0x2);
    LDH_addr_A(hVBlank);
    CALL(aDelayFrame);
    CALL(aDelayFrame);
    CALL(aLink_CheckCommunicationError);
    LD_A_addr(wScriptVar);
    AND_A_A;
    IF_Z goto exit;

//  Wait for ~$70000 cycles to give the other GB time to be ready
    LD_BC(0xffff);

wait:
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto wait;

//  If other GB is not ready at this point, disconnect due to timeout
    LD_A_addr(wOtherPlayerLinkMode);
    CP_A(0x5);
    IF_NZ goto timeout;

//  Another check to increase reliability
    LD_A(0x6);
    LD_addr_A(wPlayerLinkAction);
    LD_HL(wLinkTimeoutFrames);
    LD_A(1);
    LD_hli_A;
    LD_hl(50);
    CALL(aLink_CheckCommunicationError);
    LD_A_addr(wOtherPlayerLinkMode);
    CP_A(0x6);
    IF_Z goto exit;


timeout:
    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;


exit:
    XOR_A_A;
    LDH_addr_A(hVBlank);
    RET;

}

void Link_CheckCommunicationError(void){
    XOR_A_A;
    LDH_addr_A(hSerialReceivedNewData);
    LD_A_addr(wLinkTimeoutFrames);
    LD_H_A;
    LD_A_addr(wLinkTimeoutFrames + 1);
    LD_L_A;
    PUSH_HL;
    CALL(aLink_CheckCommunicationError_CheckConnected);
    POP_HL;
    IF_NZ goto load_true;
    CALL(aLink_CheckCommunicationError_AcknowledgeSerial);
    CALL(aLink_CheckCommunicationError_ConvertDW);
    CALL(aLink_CheckCommunicationError_CheckConnected);
    IF_NZ goto load_true;
    CALL(aLink_CheckCommunicationError_AcknowledgeSerial);
    XOR_A_A;  // FALSE
    goto done;


load_true:
    LD_A(TRUE);


done:
    LD_addr_A(wScriptVar);
    LD_HL(wLinkTimeoutFrames);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    RET;


CheckConnected:
    CALL(aWaitLinkTransfer);
    LD_HL(wLinkTimeoutFrames);
    LD_A_hli;
    INC_A;
    RET_NZ ;
    LD_A_hl;
    INC_A;
    RET;


AcknowledgeSerial:
    LD_B(10);

loop:
    CALL(aDelayFrame);
    CALL(aLinkDataReceived);
    DEC_B;
    IF_NZ goto loop;
    RET;


ConvertDW:
// [wLinkTimeoutFrames] = ((hl - $100) / 4) + $100
//                      = (hl / 4) + $c0
    DEC_H;
    SRL_H;
    RR_L;
    SRL_H;
    RR_L;
    INC_H;
    LD_A_H;
    LD_addr_A(wLinkTimeoutFrames);
    LD_A_L;
    LD_addr_A(wLinkTimeoutFrames + 1);
    RET;

}

void TryQuickSave(void){
    LD_A_addr(wChosenCableClubRoom);
    PUSH_AF;
    FARCALL(aLink_SaveGame);
    LD_A(TRUE);
    IF_NC goto return_result;
    XOR_A_A;  // FALSE

return_result:
    LD_addr_A(wScriptVar);
    LD_C(30);
    CALL(aDelayFrames);
    POP_AF;
    LD_addr_A(wChosenCableClubRoom);
    RET;

}

void CheckBothSelectedSameRoom(void){
    LD_A_addr(wChosenCableClubRoom);
    CALL(aLink_EnsureSync);
    PUSH_AF;
    CALL(aLinkDataReceived);
    CALL(aDelayFrame);
    CALL(aLinkDataReceived);
    POP_AF;
    LD_B_A;
    LD_A_addr(wChosenCableClubRoom);
    CP_A_B;
    IF_NZ goto fail;
    LD_A_addr(wChosenCableClubRoom);
    INC_A;
    LD_addr_A(wLinkMode);
    XOR_A_A;
    LDH_addr_A(hVBlank);
    LD_A(TRUE);
    LD_addr_A(wScriptVar);
    RET;


fail:
    XOR_A_A;  // FALSE
    LD_addr_A(wScriptVar);
    RET;

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
    LD_A(LINK_TRADECENTER);
    LD_addr_A(wLinkMode);
    CALL(aDisableSpriteUpdates);
    CALLFAR(aLinkCommunications);
    CALL(aEnableSpriteUpdates);
    XOR_A_A;
    LDH_addr_A(hVBlank);
    RET;

}

void Colosseum(void){
    LD_A(LINK_COLOSSEUM);
    LD_addr_A(wLinkMode);
    CALL(aDisableSpriteUpdates);
    CALLFAR(aLinkCommunications);
    CALL(aEnableSpriteUpdates);
    XOR_A_A;
    LDH_addr_A(hVBlank);
    RET;

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
    LD_C(40);
    CALL(aDelayFrames);
    LD_A(0xe);
    JP(mLink_EnsureSync);

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
