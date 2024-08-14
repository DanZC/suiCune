#include "../constants.h"
#include "mobile_5f.h"
#include "../charmap.h"
#include "../home/menu.h"

void Function17c000(void){
    CALL(aDisableLCD);

    LD_HL(vTiles2);
    LD_BC(0x31 * LEN_2BPP_TILE);
    XOR_A_A;
    CALL(aByteFill);

    CALL(aLoadStandardFont);
    CALL(aLoadFontsExtra);

    LD_HL(mHaveWantMap);
    decoord(0, 0, wTilemap);
    bccoord(0, 0, wAttrmap);

    LD_A(SCREEN_HEIGHT);

y:
    PUSH_AF;
    LD_A(SCREEN_WIDTH);

    PUSH_HL;

x:
    PUSH_AF;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_bc_A;
    INC_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto x;
    POP_HL;

    PUSH_BC;
    LD_BC(BG_MAP_WIDTH * 2);
    ADD_HL_BC;
    POP_BC;

    POP_AF;
    DEC_A;
    IF_NZ goto y;

    LDH_A_addr(rSVBK);
    PUSH_AF;

    LD_A(BANK(wBGPals1));
    LDH_addr_A(rSVBK);

    LD_HL(mHaveWantPals);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);

    POP_AF;
    LDH_addr_A(rSVBK);

    LD_HL(mMobileSelectGFX);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0x30);
    LD_BC(0x20 * LEN_2BPP_TILE);
    CALL(aCopyBytes);

    LD_A(1);
    LDH_addr_A(rVBK);

    LD_HL(mHaveWantGFX);
    LD_DE(vTiles2);
    LD_BC(0x80 * LEN_2BPP_TILE);
    CALL(aCopyBytes);

    LD_HL(mHaveWantGFX + 0x80 * LEN_2BPP_TILE);
    LD_DE(vTiles1);
    LD_BC(0x10 * LEN_2BPP_TILE);
    CALL(aCopyBytes);

    XOR_A_A;
    LDH_addr_A(rVBK);

    CALL(aEnableLCD);
    FARCALL(aReloadMapPart);
    RET;

}

void HaveWantGFX(void){
// INCBIN "gfx/mobile/havewant.2bpp"

    return MobileSelectGFX();
}

void MobileSelectGFX(void){
// INCBIN "gfx/mobile/select.2bpp"

    return HaveWantMap();
}

void HaveWantMap(void){
//  Interleaved tile/palette map.
// INCBIN "gfx/mobile/havewant_map.bin"

    return HaveWantPals();
}

void HaveWantPals(void){
//  BG and OBJ palettes.
    //rgb ['0', '0', '0']
    //rgb ['21', '21', '21']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']

    //rgb ['0', '0', '0']
    //rgb ['4', '17', '29']
    //rgb ['6', '19', '31']
    //rgb ['31', '31', '31']

    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']

    //rgb ['0', '0', '0']
    //rgb ['2', '13', '18']
    //rgb ['6', '19', '31']
    //rgb ['31', '31', '31']

    //rgb ['0', '0', '0']
    //rgb ['31', '5', '5']
    //rgb ['29', '21', '21']
    //rgb ['31', '31', '31']

    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']

    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']

    //rgb ['0', '0', '0']
    //rgb ['4', '17', '29']
    //rgb ['6', '19', '31']
    //rgb ['2', '15', '27']

    //rgb ['0', '0', '0']
    //rgb ['28', '19', '18']
    //rgb ['25', '9', '0']
    //rgb ['0', '0', '0']

    //rgb ['0', '0', '0']
    //rgb ['31', '27', '27']
    //rgb ['31', '10', '4']
    //rgb ['29', '0', '0']

    //rgb ['0', '0', '0']
    //rgb ['31', '31', '31']
    //rgb ['26', '8', '23']
    //rgb ['22', '0', '16']

    //rgb ['0', '0', '0']
    //rgb ['31', '31', '31']
    //rgb ['20', '8', '31']
    //rgb ['15', '1', '26']

    //rgb ['0', '0', '0']
    //rgb ['31', '31', '31']
    //rgb ['17', '12', '31']
    //rgb ['12', '6', '31']

    //rgb ['0', '16', '0']
    //rgb ['11', '11', '14']
    //rgb ['5', '5', '7']
    //rgb ['31', '31', '31']

    //rgb ['0', '31', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']

    //rgb ['16', '31', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']
    //rgb ['0', '0', '0']

    return CheckStringForErrors();
}

void CheckStringForErrors(void){
//  Valid character ranges:
//  $0, $5 - $13, $19 - $1c, $26 - $34, $3a - $3e, $40 - $48, $60 - $ff

loop:
    LD_A_de;
    INC_DE;
    AND_A_A;  // "<NULL>"
    IF_Z goto NextChar;
    CP_A(FIRST_REGULAR_TEXT_CHAR);
    IF_NC goto NextChar;
    CP_A(0x4e);
    IF_Z goto NextChar;
    CP_A(0x50);
    IF_Z goto Done;
    CP_A(0x05);
    IF_C goto Fail;
    CP_A(0x14);
    IF_C goto NextChar;
    CP_A(0x18 + 1);
    IF_C goto Fail;
    CP_A(0x1d);
    IF_C goto NextChar;
    CP_A(0x25 + 1);
    IF_C goto Fail;
    CP_A(0x35);
    IF_C goto NextChar;
    CP_A(0x39 + 1);
    IF_C goto Fail;
    CP_A(0x3f);
    IF_C goto NextChar;
    CP_A(0x3f + 1);
    IF_C goto Fail;
    CP_A(0x49);
    IF_C goto NextChar;


Fail:
    SCF;
    RET;


NextChar:
    DEC_C;
    IF_NZ goto loop;


Done:
    AND_A_A;
    RET;

}

//  Valid character ranges:
//  $0, $5 - $13, $19 - $1c, $26 - $34, $3a - $3e, $40 - $48, $60 - $ff
bool CheckStringForErrors_Conv(const uint8_t* de, uint8_t c){
    do {
    // loop:
        // LD_A_de;
        uint8_t ch = *(de++);
        // INC_DE;
        // AND_A_A;  // "<NULL>"
        // IF_Z goto NextChar;
        if(ch == CHAR_NULL) continue;
        // CP_A(FIRST_REGULAR_TEXT_CHAR);
        // IF_NC goto NextChar;
        if(ch >= FIRST_REGULAR_TEXT_CHAR) continue;
        // CP_A(0x4e);
        // IF_Z goto NextChar;
        if(ch == 0x4e) continue;
        // CP_A(0x50);
        // IF_Z goto Done;
        if(ch == CHAR_TERM) return false;
        // CP_A(0x05);
        // IF_C goto Fail;
        if(ch < 0x05) return true;
        // CP_A(0x14);
        // IF_C goto NextChar;
        if(ch < 0x14) continue;
        // CP_A(0x18 + 1);
        // IF_C goto Fail;
        if(ch <= 0x18) return true;
        // CP_A(0x1d);
        // IF_C goto NextChar;
        if(ch < 0x1d) continue;
        // CP_A(0x25 + 1);
        // IF_C goto Fail;
        if(ch <= 0x25) return true;
        // CP_A(0x35);
        // IF_C goto NextChar;
        if(ch < 0x35) continue;
        // CP_A(0x39 + 1);
        // IF_C goto Fail;
        if(ch <= 0x39) return true;
        // CP_A(0x3f);
        // IF_C goto NextChar;
        if(ch < 0x3f) continue;
        // CP_A(0x3f + 1);
        // IF_C goto Fail;
        if(ch <= 0x3f) return true;
        // CP_A(0x49);
        // IF_C goto NextChar;
        if(ch < 0x49) continue;

    // Fail:
        // SCF;
        // RET;
        return true;

    // NextChar:
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

// Done:
    // AND_A_A;
    // RET;
    return false;
}

void CheckStringForErrors_IgnoreTerminator(void){
//  Find control chars

loop:
    LD_A_de;
    INC_DE;
    AND_A_A;
    IF_Z goto next;
    CP_A(0x5f + 1);
    IF_NC goto next;
    CP_A(0x4e);
    IF_Z goto next;
    CP_A(0x50);
    IF_Z goto next;

    CP_A(0x05);
    IF_C goto end;
    CP_A(0x14);
    IF_C goto next;
    CP_A(0x18 + 1);
    IF_C goto end;
    CP_A(0x1d);
    IF_C goto next;
    CP_A(0x25 + 1);
    IF_C goto end;
    CP_A(0x35);
    IF_C goto next;
    CP_A(0x39 + 1);
    IF_C goto end;
    CP_A(0x3f);
    IF_C goto next;
    CP_A(0x3f + 1);
    IF_C goto end;
    CP_A(0x49);
    IF_C goto next;


end:
    SCF;
    RET;


next:
    DEC_C;
    IF_NZ goto loop;
    AND_A_A;
    RET;

}

//  Find control chars
bool CheckStringForErrors_IgnoreTerminator_Conv(const uint8_t* de, uint8_t c){
    do {
    // loop:
        // LD_A_de;
        // INC_DE;
        // AND_A_A;
        uint8_t ch = *(de++);
        // IF_Z goto next;
        if(ch == 0) continue;
        // CP_A(0x5f + 1);
        // IF_NC goto next;
        if(ch >= 0x5f + 1) continue;
        // CP_A(0x4e);
        // IF_Z goto next;
        // CP_A(0x50);
        // IF_Z goto next;
        if(ch == 0x4e || ch == 0x50) continue;

        // CP_A(0x05);
        // IF_C goto end;
        if(ch < 0x05) return true;
        // CP_A(0x14);
        // IF_C goto next;
        else if(ch < 0x14) continue;
        // CP_A(0x18 + 1);
        // IF_C goto end;
        else if(ch < 0x18 + 1) return true;
        // CP_A(0x1d);
        // IF_C goto next;
        else if(ch < 0x1d) continue;
        // CP_A(0x25 + 1);
        // IF_C goto end;
        else if(ch < 0x25 + 1) return true;
        // CP_A(0x35);
        // IF_C goto next;
        else if(ch < 0x35) continue;
        // CP_A(0x39 + 1);
        // IF_C goto end;
        else if(ch < 0x39 + 1) return true;
        // CP_A(0x3f);
        // IF_C goto next;
        else if(ch < 0x3f) continue;
        // CP_A(0x3f + 1);
        // IF_C goto end;
        else if(ch < 0x3f + 1) return true;
        // CP_A(0x49);
        // IF_C goto next;
        else if(ch < 0x49) continue;
        else {
        // end:
            // SCF;
            // RET;
            return true;
        }

    // next:
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // AND_A_A;
    // RET;
    return false;
}

void Function17d0f3(void){
    LD_A_addr(wc608 + 5);
    LD_addr_A(wOTTrademonSpecies);
    LD_addr_A(wCurPartySpecies);
    LD_A_addr(wcd81);
    LD_addr_A(wc74e);
    LD_HL(wc608 + 53);
    LD_DE(wOTTrademonOTName);
    LD_BC(5);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    LD_A_addr(wc608 + 11);
    LD_addr_A(wOTTrademonID);
    LD_A_addr(wc608 + 12);
    LD_addr_A(wOTTrademonID + 1);
    LD_HL(wc608 + 26);
    LD_A_hli;
    LD_addr_A(wOTTrademonDVs);
    LD_A_hl;
    LD_addr_A(wOTTrademonDVs + 1);
    LD_BC(wc608 + 5);
    FARCALL(aGetCaughtGender);
    LD_A_C;
    LD_addr_A(wOTTrademonCaughtData);
    CALL(aSpeechTextbox);
    CALL(aFadeToMenu);
    FARCALL(aFunction10804d);
    FARCALL(aFunction17d1f1);
    LD_A(0x1);
    LD_addr_A(wForceEvolution);
    LD_A(LINK_TRADECENTER);
    LD_addr_A(wLinkMode);
    FARCALL(aEvolvePokemon);
    XOR_A_A;
    LD_addr_A(wLinkMode);
    FARCALL(aSaveAfterLinkTrade);
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_A(0x5);
    LD_addr_A(0xa800);
    CALL(aCloseSRAM);
    LD_A_addr(wMapGroup);
    LD_B_A;
    LD_A_addr(wMapNumber);
    LD_C_A;
    CALL(aGetMapSceneID);
    LD_A_D;
    OR_A_E;
    IF_Z goto asm_17d180;
    LD_A(0x1);
    LD_de_A;


asm_17d180:
    CALL(aCloseSubmenu);
    CALL(aRestartMapMusic);
    RET;

}

void Mobile_CopyDefaultOTName(void){
    LD_HL(mMobile5F_PlayersName);
    LD_DE(wc63d);
    LD_BC(5);
    CALL(aCopyBytes);
    RET;

}

void Mobile5F_PlayersName(void){
    //db ['"クりス@@"'];

    return Mobile_CopyDefaultNickname();
}

void Mobile_CopyDefaultNickname(void){
    LD_HL(mMobile_CopyDefaultNickname_DefaultNickname);
    LD_DE(wc642);
    LD_BC(5);
    CALL(aCopyBytes);
    RET;


DefaultNickname:
    //db ['"？？？？？"'];

    return Mobile_CopyDefaultMail();
}

void Mobile_CopyDefaultMail(void){
    LD_A(0x50);
    LD_HL(wc647);
    LD_BC(MAIL_MSG_LENGTH + 1);
    CALL(aByteFill);
    LD_HL(mMobile_CopyDefaultMail_DefaultMessage);
    LD_DE(wc647);
    LD_BC(6);
    CALL(aCopyBytes);
    RET;


DefaultMessage:
    //db ['"こんにちは@"'];

    return Mobile_CopyDefaultMailAuthor();
}

void Mobile_CopyDefaultMailAuthor(void){
    LD_A(0x50);
    LD_DE(wc668);
    LD_BC(5);
    CALL(aByteFill);
    LD_HL(mMobile5F_PlayersName);
    LD_DE(wc668);
    LD_BC(5);
    CALL(aCopyBytes);
    RET;

}

void CheckStringContainsLessThanBNextCharacters(void){

loop:
    LD_A_de;
    INC_DE;
    CP_A(0x4e);
    IF_NZ goto next_char;
    DEC_B;
    IF_Z goto done;


next_char:
    DEC_C;
    IF_NZ goto loop;
    AND_A_A;
    RET;


done:
    SCF;
    RET;

}

bool CheckStringContainsLessThanBNextCharacters_Conv(const uint8_t* de, uint8_t b, uint8_t c){
    do {
    // loop:
        // LD_A_de;
        // INC_DE;
        uint8_t ch = *(de++);
        // CP_A(0x4e);
        // IF_NZ goto next_char;
        if(ch != 0x4e)
            continue;
        // DEC_B;
        // IF_Z goto done;
        if(--b == 0)
            return true;

    // next_char:
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // AND_A_A;
    // RET;
    return false;

// done:
    // SCF;
    // RET;
}

void Function17d1f1(void){
    LD_A_addr(wCurPartySpecies);
    DEC_A;
    CALL(aSetSeenAndCaughtMon);

    LD_A_addr(wCurPartySpecies);
    CP_A(UNOWN);
    IF_NZ goto asm_17d223;

    LD_HL(wPartyMon1DVs);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aAddNTimes);
    PREDEF(pGetUnownLetter);
    CALLFAR(aUpdateUnownDex);
    LD_A_addr(wFirstUnownSeen);
    AND_A_A;
    IF_NZ goto asm_17d223;

    LD_A_addr(wUnownLetter);
    LD_addr_A(wFirstUnownSeen);


asm_17d223:
    RET;
}

//
//  Parameter: [wScriptVar] = 0..1
//
//  if [wScriptVar] == FALSE
//     Show japanese menu options
//     - News - News - ??? - Cancel
//  if [wScriptVar] == TRUE
//     Show BattleTower-Menu with 3 options in english language
//     - Challenge - Explanation - Cancel
void Menu_ChallengeExplanationCancel(void){
    // LD_A_addr(wScriptVar);
    // AND_A_A;
    // IF_NZ goto English;
    if(wram->wScriptVar == 0x0){
        // LD_A(0x4);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x4;
        // LD_HL(mMenuHeader_17d26a);  // Japanese Menu, where you can choose 'News' as an option
        LoadMenuHeader_Conv2(&MenuHeader_17d26a);
        // goto Load_Interpret;
    }
    else {
    // English:
        // LD_A(0x4);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x4;
        // LD_HL(mMenuHeader_ChallengeExplanationCancel);  // English Menu
        LoadMenuHeader_Conv2(&MenuHeader_ChallengeExplanationCancel);
    }

// Load_Interpret:
    // CALL(aLoadMenuHeader);
    // CALL(aFunction17d246);
    Function17d246();
    // CALL(aCloseWindow);
    CloseWindow_Conv2();
    // RET;
}

// Mobile_RunChallengeExplanationMenu
void Function17d246(void){
    // CALL(aVerticalMenu);
    // IF_C goto Exit;
    if(!VerticalMenu_Conv()){
    // Exit:
        // LD_A(0x4);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x4;
        // RET;
        return;
    }
    // LD_A_addr(wScriptVar);
    // CP_A(0x5);
    // IF_NZ goto UsewMenuCursorY;
    if(wram->wScriptVar == 0x5){
        // LD_A_addr(wMenuCursorY);
        // CP_A(0x3);
        // RET_Z ;
        if(wram->wMenuCursorY == 0x3)
            return;
        // IF_C goto UsewMenuCursorY;
        if(wram->wMenuCursorY > 0x3){
            // DEC_A;
            // goto LoadToScriptVar;
            wram->wScriptVar = wram->wMenuCursorY - 1;
            return;
        }
    }

// UsewMenuCursorY:
    // LD_A_addr(wMenuCursorY);

// LoadToScriptVar:
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = wram->wMenuCursorY;
    // RET;
}

const struct MenuHeader MenuHeader_17d26a = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, 14, 9),
    .data = &MenuData_17d272,
    .defaultOption = 1,  // default option
};

const struct MenuData MenuData_17d272 = {
    .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
    .verticalMenu = {
        .count = 4,
        .options = (const char*[]){
            "NEWS", //db ['"ニュース¯よみこむ@"'];
            "NEWS", //db ['"ニュース¯みる@"'];
            "INFO", //db ['"せつめい@"'];
            "CANCEL", //db ['"やめる@"'];
        },
    },
};

const struct MenuHeader MenuHeader_ChallengeExplanationCancel = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 0, 14, 7),
    .data = &MenuData_ChallengeExplanationCancel,
    .defaultOption = 1,  // default option
};

const struct MenuData MenuData_ChallengeExplanationCancel = {
    .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
    .verticalMenu = {
        .count = 3,
        .options = (const char*[]){
            "Challenge@",
            "Explanation@",
            "Cancel@",
        },
    },
};

void Function17d2b6(void){
    CALL(aFunction17d2c0);
    FARCALL(aFunction1181da);
    RET;

}

void Function17d2c0(void){
    XOR_A_A;
    LD_addr_A(wJumptableIndex);
    LD_addr_A(wcf64);
    LD_addr_A(wcf65);
    LD_addr_A(wcf66);
    RET;

}

void Function17d2ce(void){
    LD_A(BANK(s5_aa72));
    CALL(aOpenSRAM);
    LD_A_addr(s5_aa72);
    CALL(aCloseSRAM);
    AND_A_A;
    IF_NZ goto asm_17d2e2;
    LD_A(0x1);
    LD_addr_A(wScriptVar);
    RET;


asm_17d2e2:
    CALL(aFunction17d314);
    RET_C ;
    CALL(aSpeechTextbox);
    CALL(aFadeToMenu);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    CALL(aFunction17d370);
    CALL(aFunction17d45a);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_DE(MUSIC_MOBILE_CENTER);
    LD_A_E;
    LD_addr_A(wMapMusic);
    LD_addr_A(wMusicFadeID);
    LD_A_D;
    LD_addr_A(wMusicFadeID + 1);
    CALL(aPlayMusic);
    CALL(aReturnToMapFromSubmenu);
    CALL(aCloseSubmenu);
    RET;

}

void Function17d314(void){
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_A_addr(0xb1b1);
    CALL(aCloseSRAM);
    CP_A(0x21);
    IF_NC goto asm_17d354;
    LD_A(0x6);
    CALL(aOpenSRAM);
    LD_L(0x0);
    LD_H_L;
    LD_DE(0xa006);
    LD_A_addr(0xa004);
    LD_C_A;
    LD_A_addr(0xa005);
    LD_B_A;

asm_17d336:
    PUSH_BC;
    LD_A_de;
    INC_DE;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;
    DEC_BC;
    LD_A_B;
    OR_A_C;
    IF_NZ goto asm_17d336;
    LD_A_addr(0xa002);
    CP_A_L;
    IF_NZ goto asm_17d354;
    LD_A_addr(0xa003);
    CP_A_H;
    IF_NZ goto asm_17d354;
    CALL(aCloseSRAM);
    AND_A_A;
    RET;


asm_17d354:
    CALL(aCloseSRAM);
    LD_A(0x5);
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_HL(0xaa73);
    LD_BC(0xc);
    CALL(aByteFill);
    CALL(aCloseSRAM);
    LD_A(0x2);
    LD_addr_A(wScriptVar);
    SCF;
    RET;

}

void Function17d370(void){
    XOR_A_A;
    LD_addr_A(wcd77);
    LD_addr_A(wMobileCrashCheckPointer);
    LD_addr_A(wMobileCrashCheckPointer + 1);
    DEC_A;
    LD_addr_A(wcd6c);
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    CALL(aClearScreen);
    FARCALL(aReloadMapPart);
    CALL(aDisableLCD);
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0xee);
    LD_DE(wc608);
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aCopyBytes);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mPokemonNewsGFX);
    LD_DE(vTiles1);
    LD_BC(0x48 * LEN_2BPP_TILE);
    CALL(aCopyBytes);
    XOR_A_A;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x7f);
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aByteFill);
    LD_HL(wc608);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0xee);
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aCopyBytes);
    XOR_A_A;
    LDH_addr_A(rVBK);
    LD_HL(mPostalMarkGFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x60);
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aCopyBytes);
    CALL(aEnableLCD);
    CALL(aFunction17d60b);
    LD_A(0x0);
    LD_addr_A(wBGMapBuffer);
    LD_A(0xd0);
    LD_addr_A(wcd21);
    LD_A(0x6);
    CALL(aOpenSRAM);
    LD_HL(0xa006);
    LD_DE(wBGPals1);
    LD_BC(0x1000);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void Function17d3f6(void){
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    CALL(aClearScreen);
    FARCALL(aReloadMapPart);

    return Function17d405();
}

void Function17d405(void){
    CALL(aDisableLCD);
    LD_HL(vTiles0 + LEN_2BPP_TILE * 0xee);
    LD_DE(wc608);
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aCopyBytes);
    LD_A(0x1);
    LDH_addr_A(rVBK);
    LD_HL(mPokemonNewsGFX);
    LD_DE(vTiles1);
    LD_BC(0x48 * LEN_2BPP_TILE);
    CALL(aCopyBytes);
    XOR_A_A;
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x7f);
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aByteFill);
    LD_HL(wc608);
    LD_DE(vTiles0 + LEN_2BPP_TILE * 0xee);
    LD_BC(1 * LEN_2BPP_TILE);
    CALL(aCopyBytes);
    XOR_A_A;
    LDH_addr_A(rVBK);
    CALL(aEnableLCD);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(mPokemonNewsPalettes);
    LD_DE(wBGPals1);
    LD_BC(8 * PALETTE_SIZE);
    CALL(aCopyBytes);
    CALL(aSetPalettes);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Function17d45a(void){

asm_17d45a:
    CALL(aJoyTextDelay);
    LD_A_addr(wcd77);
    BIT_A(7);
    IF_NZ goto asm_17d46f;
    CALL(aFunction17d474);
    FARCALL(aReloadMapPart);
    goto asm_17d45a;


asm_17d46f:
    XOR_A_A;
    LD_addr_A(wScriptVar);
    RET;

}

void Function17d474(void){
    //jumptable ['Jumptable_17d483', 'wcd77']

    return Jumptable_17d483();
}

void Jumptable_17d483(void){
    //dw ['Function17d48d'];
    //dw ['Function17d5be'];
    //dw ['Function17d5c4'];
    //dw ['Function17d6fd'];
    //dw ['Function17e427'];

    return Function17d48d();
}

void Function17d48d(void){
    LD_HL(mPokemonNewsPalettes);
    LD_DE(wc608);
    LD_BC(0x40);
    CALL(aCopyBytes);
    LD_HL(mPokemonNewsTileAttrmap);
    decoord(0, 0, wTilemap);
    bccoord(0, 0, wAttrmap);
    LD_A(0x12);

asm_17d4a4:
    PUSH_AF;
    LD_A(0x14);
    PUSH_HL;

asm_17d4a8:
    PUSH_AF;
    LD_A_hli;
    CP_A(0x7f);
    IF_Z goto asm_17d4b0;
    ADD_A(0x80);


asm_17d4b0:
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_bc_A;
    INC_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17d4a8;
    POP_HL;
    PUSH_BC;
    LD_BC(0x40);
    ADD_HL_BC;
    POP_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17d4a4;
    LD_A_addr(wBGMapBuffer);
    LD_L_A;
    LD_A_addr(wcd21);
    LD_H_A;
    LD_A_hli;
    LD_E_A;
    LD_A_addr(wcd6c);
    CP_A_E;
    IF_Z goto asm_17d4e0;
    LD_A_E;
    LD_addr_A(wcd6c);
    LD_addr_A(wMapMusic);
    LD_D(0x0);
    CALL(aPlayMusic2);


asm_17d4e0:
    LD_A_hli;
    LD_DE(wc608);
    LD_C(0x8);

asm_17d4e6:
    SRL_A;
    IF_NC goto asm_17d4f6;
    LD_B(0x8);
    PUSH_AF;

asm_17d4ed:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_B;
    IF_NZ goto asm_17d4ed;
    POP_AF;
    goto asm_17d4fc;


asm_17d4f6:
    PUSH_AF;
    LD_A_E;
    ADD_A(0x8);
    LD_E_A;
    POP_AF;


asm_17d4fc:
    DEC_C;
    IF_NZ goto asm_17d4e6;
    PUSH_HL;
    CALL(aFunction17d5f6);
    POP_HL;
    LD_A_hli;
    AND_A_A;
    IF_Z goto asm_17d539;

asm_17d508:
    PUSH_AF;
    LD_A_hli;
    LD_addr_A(wcd4f);
    LD_A_hli;
    LD_addr_A(wcd50);
    LD_A_hli;
    LD_addr_A(wcd51);
    LD_A_hli;
    LD_addr_A(wcd52);
    LD_A_hli;
    SLA_A;
    SLA_A;
    SLA_A;
    ADD_A(0x98);
    LD_addr_A(wcd53);
    LD_DE(wcd4f);
    CALL(aFunction17e613);
    LD_A_hli;
    LD_addr_A(wcd53);
    LD_DE(wcd4f);
    CALL(aFunction17e691);
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17d508;


asm_17d539:
    LD_A_hli;

asm_17d53a:
    PUSH_AF;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    PUSH_HL;
    POP_DE;
    hlcoord(0, 0, wTilemap);
    ADD_HL_BC;
    CALL(aPlaceString);
    PUSH_DE;
    POP_HL;
    INC_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17d53a;
    LD_DE(wCreditsTimer);
    LD_BC(0xc);
    CALL(aCopyBytes);
    XOR_A_A;
    LD_addr_A(wcd2e);
    LD_addr_A(wcd2f);
    INC_A;
    LD_addr_A(wcd30);
    LD_addr_A(wcd31);
    LD_DE(wcd32);
    LD_BC(0x10);
    CALL(aCopyBytes);
    LD_A_hli;
    LD_addr_A(wcd42);
    LD_A_hli;
    LD_addr_A(wcd43);
    LD_A_hli;
    LD_addr_A(wMobileInactivityTimerMinutes);
    LD_A_hli;
    LD_addr_A(wMobileInactivityTimerSeconds);
    LD_A_hli;
    LD_addr_A(wMobileInactivityTimerFrames);
    LD_A_hli;
    AND_A_A;
    IF_Z goto asm_17d58a;
    CALL(aFunction17d6a1);


asm_17d58a:
    LD_A_L;
    LD_addr_A(wcd49);
    LD_A_H;
    LD_addr_A(wcd4a);
    LD_A_addr(wcd42);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_L;
    LD_addr_A(wcd4b);
    LD_A_H;
    LD_addr_A(wcd4c);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_L;
    LD_addr_A(wcd4d);
    LD_A_H;
    LD_addr_A(wcd4e);
    CALL(aFunction17e451);
    CALL(aFunction17e55b);
    CALL(aFunction17e5af);
    FARCALL(aReloadMapPart);
    JP(mFunction17e438);

}

void Function17d5be(void){
    CALL(aSetPalettes);
    CALL(aFunction17e438);

    return Function17d5c4();
}

void Function17d5c4(void){
    LDH_A_addr(hJoyPressed);
    AND_A_A;
    RET_Z ;
    LD_C(0);
    LD_B_C;
    LD_HL(wcd32);

loop:
    SRL_A;
    IF_C goto got_button;
    INC_C;
    INC_C;
    goto loop;


got_button:
    ADD_HL_BC;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    AND_A_C;
    CP_A(0xff);
    RET_Z ;
    LD_A_addr(wcd20);
    LD_L_A;
    LD_A_addr(wcd21);
    LD_H_A;
    ADD_HL_BC;
    LD_A_L;
    LD_addr_A(wMobileCrashCheckPointer);
    LD_A_H;
    LD_addr_A(wMobileCrashCheckPointer + 1);
    LD_A(0x3);
    LD_addr_A(wcd77);
    RET;

}

void Function17d5f6(void){
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(wc608);
    LD_DE(wBGPals1);
    LD_BC(8 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    RET;

}

void Function17d60b(void){
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_HL(0xb1d3);
    LD_DE(wc608);
    LD_BC(0x20);
    CALL(aCopyBytes);
    LD_A_addr(0xb1b1);
    LD_C_A;
    LD_A_addr(0xb1b2);
    LD_B_A;
    LD_A_addr(0xb1b3);
    LD_L_A;
    LD_A_addr(0xb1b4);
    LD_H_A;
    CALL(aCloseSRAM);
    LD_A(0x6);
    CALL(aOpenSRAM);
    LD_DE(wc708);
    LD_A_C;
    AND_A_A;
    IF_Z goto asm_17d684;

asm_17d63b:
    PUSH_BC;
    LD_A_L;
    LD_de_A;
    INC_DE;
    LD_A_H;
    LD_de_A;
    INC_DE;
    LD_BC(0xa);
    ADD_HL_BC;
    POP_BC;
    LD_A_hli;
    LD_addr_A(wcd4a);
    LD_A_hli;
    LD_addr_A(wcd49);
    PUSH_HL;
    PUSH_DE;
    LD_HL(wc608);
    LD_E_B;
    LD_D(0x0);
    ADD_HL_DE;
    LD_A_hli;
    LD_addr_A(wcd4b);
    LD_A_hl;
    LD_addr_A(wcd4c);
    POP_DE;
    POP_HL;
    INC_B;
    INC_B;
    DEC_C;
    DEC_C;
    IF_Z goto asm_17d684;
    PUSH_BC;
    PUSH_DE;
    LD_A_addr(wcd49);
    LD_C_A;
    LD_A_addr(wcd4a);
    LD_B_A;
    LD_A_addr(wcd4b);
    LD_E_A;
    LD_A_addr(wcd4c);
    LD_D_A;

asm_17d67a:
    ADD_HL_DE;
    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto asm_17d67a;
    POP_DE;
    POP_BC;
    goto asm_17d63b;


asm_17d684:
    CALL(aCloseSRAM);
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_HL(wc708);
    LD_DE(0xb1b3);
    LD_A_addr(0xb1b1);
    LD_C_A;
    LD_A_addr(0xb1b2);
    LD_B_A;
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void Function17d6a1(void){
    PUSH_HL;
    LD_A_addr(wcd6e);
    LD_C_A;
    LD_B(0);
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_HL(0xb1d3);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_addr_A(wcd47);
    LD_A_hl;
    LD_addr_A(wBGMapPalBuffer);
    LD_HL(0xb1b3);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_C_A;
    LD_A_hl;
    LD_H_A;
    LD_L_C;
    CALL(aCloseSRAM);
    LD_A(0x6);
    CALL(aOpenSRAM);
    LD_A_L;
    LD_addr_A(wcd5e);
    LD_A_H;
    LD_addr_A(wcd5f);
    LD_DE(wcd60);
    LD_BC(0x4);
    CALL(aCopyBytes);
    INC_HL;
    INC_HL;
    LD_DE(wcd64);
    LD_BC(0x4);
    CALL(aCopyBytes);
    LD_A_hli;
    LD_addr_A(wcd69);
    LD_A_hli;
    LD_addr_A(wcd68);
    LD_A_L;
    LD_addr_A(wcd6a);
    LD_A_H;
    LD_addr_A(wcd6b);
    CALL(aCloseSRAM);
    POP_HL;
    RET;

}

void Function17d6fd(void){
    LD_A_addr(wcd77);
    BIT_A(7);
    JR_NZ (masm_17d721);
    LD_A_addr(wMobileCrashCheckPointer);
    LD_L_A;
    LD_A_addr(wMobileCrashCheckPointer + 1);
    LD_H_A;
    LD_A_hl;
    CP_A(0xff);
    JR_Z (masm_17d721);

    return Function17d711();
}

void Function17d711(void){

crash_loop:
    CP_A(0x31);
    IF_NC goto crash_loop;
    LD_E_A;
    LD_D(0);
    LD_HL(mJumptable17d72a);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;

}

void asm_17d721(void){
    CALL(aFunction17e5af);
    LD_A(0x2);
    LD_addr_A(wcd77);
    RET;

}

void Jumptable17d72a(void){
    //dw ['Function17d78c'];
    //dw ['Function17d78d'];
    //dw ['Function17d7b4'];
    //dw ['Function17d7c2'];
    //dw ['Function17d7d3'];
    //dw ['Function17d7e5'];
    //dw ['Function17d818'];
    //dw ['Function17d833'];
    //dw ['Function17d85d'];
    //dw ['Function17d902'];
    //dw ['Function17d93a'];
    //dw ['Function17d98b'];
    //dw ['Function17d9e3'];
    //dw ['Function17da31'];
    //dw ['Function17da9c'];
    //dw ['Function17dadc'];
    //dw ['Function17db2d'];
    //dw ['Function17db56'];
    //dw ['Function17db77'];
    //dw ['Function17dbe9'];
    //dw ['Function17dc1f'];
    //dw ['Function17dc9f'];
    //dw ['Function17dca9'];
    //dw ['Function17dccf'];
    //dw ['Function17dd13'];
    //dw ['Function17dd30'];
    //dw ['Function17dd49'];
    //dw ['Function17ddcd'];
    //dw ['Function17de32'];
    //dw ['Function17de91'];
    //dw ['Function17ded9'];
    //dw ['Function17e0fd'];
    //dw ['Function17e133'];
    //dw ['Function17e165'];
    //dw ['Function17e1a1'];
    //dw ['Function17e254'];
    //dw ['Function17e261'];
    //dw ['Function17e270'];
    //dw ['Function17e27f'];
    //dw ['Function17e293'];
    //dw ['Function17e2a7'];
    //dw ['IncCrashCheckPointer_SaveGameData'];
    //dw ['IncCrashCheckPointer_SaveAfterLinkTrade'];
    //dw ['IncCrashCheckPointer_SaveBox'];
    //dw ['IncCrashCheckPointer_SaveChecksum'];
    //dw ['IncCrashCheckPointer_SaveTrainerRankingsChecksum'];
    //dw ['Function17e3e0'];
    //dw ['Function17e3f0'];
    //dw ['Function17e409'];

    return Function17d78c();
}

void Function17d78c(void){
    RET;

}

void Function17d78d(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    CALL(aHlToCrashCheckPointer);
    LD_A(0x6);
    CALL(aOpenSRAM);
    LD_HL(0xa006);
    ADD_HL_BC;
    LD_DE(wBGPals1);
    LD_BC(0x1000);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    XOR_A_A;
    LD_addr_A(wcd77);
    CALL(aClearBGPalettes);
    RET;

}

void Function17d7b4(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_D(0);
    CALL(aPlayMusic2);
    CALL(aHlToCrashCheckPointer);
    RET;

}

void Function17d7c2(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_D(0);
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    CALL(aHlToCrashCheckPointer);
    RET;

}

void Function17d7d3(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    DEC_A;
    LD_E_A;
    LD_D(0);
    CALL(aPlayCry);
    CALL(aWaitSFX);
    CALL(aHlToCrashCheckPointer);
    RET;

}

void Function17d7e5(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_addr_A(wcd4f);
    LD_A_hli;
    LD_addr_A(wcd50);
    LD_A_hli;
    LD_addr_A(wcd51);
    LD_A_hli;
    LD_addr_A(wcd52);
    LD_A_hli;
    SLA_A;
    SLA_A;
    SLA_A;
    ADD_A(0x98);
    LD_addr_A(wcd53);
    LD_DE(wcd4f);
    CALL(aFunction17e613);
    LD_A_hli;
    LD_addr_A(wcd53);
    LD_DE(wcd4f);
    CALL(aFunction17e691);
    CALL(aHlToCrashCheckPointer);
    RET;

}

void Function17d818(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    CALL(aHlToCrashCheckPointer);
    CALL(aFunction17e447);
    LD_E_L;
    LD_D_H;
    hlcoord(0, 0, wTilemap);
    ADD_HL_BC;
    CALL(aPlaceString);
    RET;

}

void Function17d833(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    CALL(aHlToCrashCheckPointer);
    PUSH_DE;
    PUSH_BC;
    CALL(aFunction17e32b);
    POP_BC;
    POP_DE;
    CALL(aFunction17e43d);
    LD_C_L;
    LD_B_H;
    hlcoord(0, 0, wTilemap);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    FARCALL(aFunction11c08f);
    CALL(aFunction17e349);
    RET;

}

void Function17d85d(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    PUSH_HL;
    LD_HL(wBGPals1);
    ADD_HL_DE;
    LD_DE(wcc60);

asm_17d86c:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    AND_A_A;
    IF_NZ goto asm_17d86c;
    POP_HL;
    LD_DE(wc608);
    LD_C(0x0);

asm_17d878:
    LD_A_hli;
    CP_A(0xff);
    IF_Z goto asm_17d8c7;
    LD_addr_A(wcd4f);
    LD_A_hli;
    LD_addr_A(wcd50);
    LD_A_hli;
    LD_addr_A(wcd51);
    LD_A_hli;
    LD_addr_A(wcd52);
    LD_A_addr(wcd51);
    PUSH_AF;
    CP_A(0xc0);
    IF_C goto asm_17d89b;
    LD_A_addr(wcd4f);
    LDH_addr_A(rSVBK);
    goto asm_17d8a1;


asm_17d89b:
    LD_A_addr(wcd4f);
    CALL(aOpenSRAM);


asm_17d8a1:
    PUSH_HL;
    LD_A_addr(wcd50);
    LD_L_A;
    LD_A_addr(wcd51);
    LD_H_A;
    LD_A_addr(wcd52);

asm_17d8ad:
    PUSH_AF;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    INC_C;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17d8ad;
    POP_HL;
    POP_AF;
    CP_A(0xc0);
    IF_C goto asm_17d8c2;
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    goto asm_17d878;


asm_17d8c2:
    CALL(aCloseSRAM);
    goto asm_17d878;


asm_17d8c7:
    CALL(aHlToCrashCheckPointer);
    PUSH_BC;
    LD_A(0x3);
    LDH_addr_A(rSVBK);
    LD_HL(wc608);
    LD_DE(wBGPals1);
    LD_B(0x0);
    CALL(aCopyBytes);
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    CALL(aFunction17e32b);
    POP_BC;
    LD_A_C;
    LD_addr_A(wcd3b);
    XOR_A_A;
    LD_addr_A(wcf66);
    FARCALL(aFunction118329);
    LD_A_addr(wMobileErrorCodeBuffer);
    AND_A_A;
    IF_Z goto asm_17d8fe;
    CP_A(0xa);
    IF_Z goto asm_17d8fe;
    CALL(aFunction17e309);
    RET;


asm_17d8fe:
    CALL(aFunction17e349);
    RET;

}

void Function17d902(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    PUSH_DE;
    CALL(aHlToCrashCheckPointer);
    CALL(aFunction17e32b);
    POP_DE;
    LD_HL(wBGPals1);
    ADD_HL_DE;
    LD_DE(wcc60);

asm_17d918:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    AND_A_A;
    IF_NZ goto asm_17d918;
    XOR_A_A;
    LD_addr_A(wcf66);
    FARCALL(aFunction11837a);
    LD_A_addr(wMobileErrorCodeBuffer);
    AND_A_A;
    IF_Z goto asm_17d936;
    CP_A(0xa);
    IF_Z goto asm_17d936;
    CALL(aFunction17e309);
    RET;


asm_17d936:
    CALL(aFunction17e349);
    RET;

}

void Function17d93a(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x5);
    CALL(aCopyBytes);
    CALL(aHlToCrashCheckPointer);
    CALL(aFunction17e32b);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_A_addr(wc70c);
    CALL(aFunction17e6de);
    LD_A_addr(wc70a);
    LD_addr_A(wCurPartySpecies);
    LD_A_addr(wc70c);
    LD_E_A;
    FARCALL(aLoadMonPaletteAsNthBGPal);
    CALL(aSetPalettes);
    LD_A_addr(wc708);
    LD_L_A;
    LD_A_addr(wc709);
    LD_H_A;
    LD_A_addr(wc70b);
    LD_C_A;
    decoord(0, 0, wTilemap);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    FARCALL(aHOF_AnimateFrontpic);
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aFunction17e349);
    RET;

}

void Function17d98b(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x4);
    CALL(aCopyBytes);
    CALL(aHlToCrashCheckPointer);
    CALL(aFunction17e32b);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_A_addr(wc70b);
    CALL(aFunction17e6de);
    LD_A_addr(wc70a);
    LD_addr_A(wTrainerClass);
    LD_A_addr(wc70b);
    LD_E_A;
    FARCALL(aLoadTrainerClassPaletteAsNthBGPal);
    CALL(aSetPalettes);
    LD_A_addr(wc708);
    LD_E_A;
    LD_A_addr(wc709);
    LD_D_A;
    PUSH_DE;
    LD_DE(vTiles2);
    FARCALL(aGetTrainerPic);
    POP_HL;
    decoord(0, 0, wTilemap);
    ADD_HL_DE;
    LD_BC(0x707);
    PREDEF(pPlaceGraphic);
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aFunction17e349);
    RET;

}

void Function17d9e3(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x7);
    CALL(aCopyBytes);
    CALL(aHlToCrashCheckPointer);
    LD_A_addr(wc70b);
    PUSH_AF;
    CP_A(0xc0);
    IF_C goto asm_17da01;
    LD_A_addr(wc70c);
    LDH_addr_A(rSVBK);
    goto asm_17da07;


asm_17da01:
    LD_A_addr(wc70c);
    CALL(aOpenSRAM);


asm_17da07:
    LD_A_addr(wc708);
    LD_L_A;
    LD_A_addr(wc709);
    LD_H_A;
    LD_A_addr(wc70a);
    LD_E_A;
    LD_A_addr(wc70b);
    LD_D_A;
    LD_A_addr(wc70d);
    LD_C_A;
    LD_A_addr(wc70e);
    LD_B_A;
    CALL(aCopyBytes);
    POP_AF;
    CP_A(0xc0);
    IF_C goto asm_17da2d;
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    goto asm_17da30;


asm_17da2d:
    CALL(aCloseSRAM);


asm_17da30:
    RET;

}

void Function17da31(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x4);
    CALL(aCopyBytes);
    CALL(aHlToCrashCheckPointer);
    LD_A_addr(wc709);
    PUSH_AF;
    CP_A(0xc0);
    IF_C goto asm_17da4f;
    LD_A_addr(wc70a);
    LDH_addr_A(rSVBK);
    goto asm_17da55;


asm_17da4f:
    LD_A_addr(wc70a);
    CALL(aOpenSRAM);


asm_17da55:
    LD_A_addr(wc708);
    LD_E_A;
    LD_A_addr(wc709);
    LD_D_A;
    LD_A_addr(wc70b);
    LD_C_A;
    BIT_C(7);
    IF_NZ goto asm_17da70;
    LD_HL(mUnknown_17da8c);
    LD_B(0x0);
    ADD_HL_BC;
    LD_A_de;
    OR_A_hl;
    LD_de_A;
    goto asm_17da7d;


asm_17da70:
    LD_HL(mUnknown_17da94);
    LD_A_C;
    AND_A(0x7f);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    AND_A_hl;
    LD_de_A;


asm_17da7d:
    POP_AF;
    CP_A(0xc0);
    IF_C goto asm_17da88;
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    goto asm_17da8b;


asm_17da88:
    CALL(aCloseSRAM);


asm_17da8b:
    RET;

}

void Unknown_17da8c(void){
    for(int x = 0; x < 8; x++){
    //db ['1 << x'];
    }

    return Unknown_17da94();
}

void Unknown_17da94(void){
    for(int x = 0; x < 8; x++){
    //db ['~(1 << x)'];
    }

    return Function17da9c();
}

void Function17da9c(void){
    LD_A_addr(wcd31);
    DEC_A;
    IF_Z goto asm_17dabd;
    PUSH_AF;
    CALL(aFunction17e566);
    POP_AF;
    LD_addr_A(wcd31);
    LD_HL(wcd24);
    LD_A_addr(wcd2e);
    SUB_A_hl;
    LD_addr_A(wcd2e);
    CALL(aFunction17e55b);
    CALL(aFunction17e5af);

asm_17daba:
    JP(mIncCrashCheckPointer);


asm_17dabd:
    LD_A_addr(wcd2f);
    AND_A_A;
    IF_Z goto asm_17daba;
    LD_HL(wcd24);
    SUB_A_hl;
    LD_addr_A(wcd2f);
    LD_A_addr(wcd2e);
    SUB_A_hl;
    LD_addr_A(wcd2e);
    CALL(aFunction17e451);
    CALL(aFunction17e55b);
    CALL(aFunction17e5af);
    goto asm_17daba;

    return Function17dadc();
}

void Function17dadc(void){
    LD_A_addr(wcd2e);
    LD_HL(wcd24);
    ADD_A_hl;
    LD_HL(wcd42);
    CP_A_hl;
    IF_Z goto asm_17db0e;
    IF_NC goto asm_17db0e;
    LD_HL(wcd31);
    LD_A_addr(wcd2b);
    CP_A_hl;
    IF_Z goto asm_17db11;
    CALL(aFunction17e566);
    LD_A_addr(wcd31);
    INC_A;
    LD_addr_A(wcd31);
    LD_HL(wcd24);
    LD_A_addr(wcd2e);
    ADD_A_hl;
    LD_addr_A(wcd2e);
    CALL(aFunction17e55b);
    CALL(aFunction17e5af);


asm_17db0e:
    JP(mIncCrashCheckPointer);


asm_17db11:
    LD_HL(wcd24);
    LD_A_addr(wcd2f);
    ADD_A_hl;
    LD_addr_A(wcd2f);
    LD_A_addr(wcd2e);
    ADD_A_hl;
    LD_addr_A(wcd2e);
    CALL(aFunction17e451);
    CALL(aFunction17e55b);
    CALL(aFunction17e5af);
    goto asm_17db0e;

    return Function17db2d();
}

void Function17db2d(void){
    LD_A_addr(wcd30);
    LD_HL(wcd24);
    CP_A_hl;
    IF_Z goto asm_17db53;
    LD_HL(wcd42);
    LD_A_addr(wcd2e);
    INC_A;
    CP_A_hl;
    IF_Z goto asm_17db53;
    LD_addr_A(wcd2e);
    CALL(aFunction17e566);
    LD_A_addr(wcd30);
    INC_A;
    LD_addr_A(wcd30);
    CALL(aFunction17e55b);
    CALL(aFunction17e5af);


asm_17db53:
    JP(mIncCrashCheckPointer);

}

void Function17db56(void){
    LD_A_addr(wcd30);
    CP_A(0x1);
    IF_Z goto asm_17db74;
    CALL(aFunction17e566);
    LD_A_addr(wcd30);
    DEC_A;
    LD_addr_A(wcd30);
    LD_A_addr(wcd2e);
    DEC_A;
    LD_addr_A(wcd2e);
    CALL(aFunction17e55b);
    CALL(aFunction17e5af);


asm_17db74:
    JP(mIncCrashCheckPointer);

}

void Function17db77(void){
    LD_HL(wcd2d);
    LD_A_addr(wcd2f);
    ADD_A_hl;
    LD_HL(wcd42);
    CP_A_hl;
    IF_Z goto asm_17dbae;
    IF_NC goto asm_17dbae;
    CALL(aFunction17e566);
    LD_HL(wcd2d);
    LD_A_addr(wcd2f);
    ADD_A_hl;
    LD_addr_A(wcd2f);
    LD_A_addr(wcd2e);
    ADD_A_hl;
    LD_HL(wcd42);
    CP_A_hl;
    IF_C goto asm_17db9f;
    LD_A_hl;
    DEC_A;


asm_17db9f:
    LD_addr_A(wcd2e);
    CALL(aFunction17dbb1);
    CALL(aFunction17e451);
    CALL(aFunction17e55b);
    CALL(aFunction17e5af);


asm_17dbae:
    JP(mIncCrashCheckPointer);

}

void Function17dbb1(void){
    LD_HL(wcd2f);
    LD_A_addr(wcd42);
    SUB_A_hl;
    LD_HL(wcd2d);
    CP_A_hl;
    RET_NC ;
    LD_A(0x1);
    LD_addr_A(wcd30);
    LD_addr_A(wcd31);
    LD_A_addr(wcd24);
    LD_C_A;
    LD_A_addr(wcd24);
    LD_B_A;
    LD_A_addr(wcd2e);
    LD_HL(wcd2f);
    SUB_A_hl;

asm_17dbd4:
    AND_A_A;
    RET_Z ;
    PUSH_AF;
    LD_HL(wcd30);
    LD_A_B;
    CP_A_hl;
    IF_NZ goto asm_17dbe4;
    LD_A(0x1);
    LD_hl_A;
    LD_HL(wcd31);


asm_17dbe4:
    INC_hl;
    POP_AF;
    DEC_A;
    goto asm_17dbd4;

    return Function17dbe9();
}

void Function17dbe9(void){
    LD_HL(wcd2d);
    LD_A_addr(wcd2f);
    SUB_A_hl;
    BIT_A(7);
    IF_Z goto asm_17dbf5;
    XOR_A_A;


asm_17dbf5:
    LD_addr_A(wcd2f);
    LD_A_addr(wcd30);
    DEC_A;
    LD_C_A;
    LD_A_addr(wcd31);
    LD_B_A;
    XOR_A_A;
    LD_HL(wcd24);

asm_17dc05:
    DEC_B;
    IF_Z goto asm_17dc0b;
    ADD_A_hl;
    goto asm_17dc05;


asm_17dc0b:
    ADD_A_C;
    LD_HL(wcd2f);
    ADD_A_hl;
    LD_addr_A(wcd2e);
    CALL(aFunction17e451);
    CALL(aFunction17e55b);
    CALL(aFunction17e5af);
    JP(mIncCrashCheckPointer);

}

void Function17dc1f(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc688);
    LD_BC(0x6);
    CALL(aCopyBytes);
    CALL(aFunction17e32b);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_HL(wc688);
    LD_A(0x40);
    LD_addr_A(wc708);
    LD_A_hli;
    LD_addr_A(wc70a);
    ADD_A(0x5);
    LD_addr_A(wc70c);
    LD_A_hli;
    LD_addr_A(wc709);
    ADD_A(0x4);
    LD_addr_A(wc70b);
    LD_A(0x96);
    LD_addr_A(wc70d);
    LD_A(0x5c);
    LD_addr_A(wc70e);
    LD_A(0x1);
    LD_addr_A(wc70f);
    LD_HL(wc708);
    CALL(aLoadMenuHeader);
    CALL(aVerticalMenu);
    IF_NC goto asm_17dc6e;
    LD_A(0x2);
    LD_addr_A(wMenuCursorY);


asm_17dc6e:
    CALL(aCloseWindow);
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A_addr(wMenuCursorY);
    CP_A(0x1);
    IF_NZ goto asm_17dc85;
    LD_A_addr(wc68a);
    LD_L_A;
    LD_A_addr(wc68a + 1);
    LD_H_A;
    goto asm_17dc8d;


asm_17dc85:
    LD_A_addr(wc68a + 2);
    LD_L_A;
    LD_A_addr(wc68a + 3);
    LD_H_A;


asm_17dc8d:
    PUSH_HL;
    CALL(aFunction17e349);
    POP_HL;
    CALL(aFunction17e40f);
    RET;

}

void MenuData_17dc96(void){
//  //  unreferenced
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING | STATICMENU_WRAP'];  // flags
    //db ['2'];
    //db ['"はい@"'];
    //db ['"いいえ@"'];

    return Function17dc9f();
}

void Function17dc9f(void){
    CALL(aIncCrashCheckPointer);
    CALL(aHlToCrashCheckPointer);
    CALL(aRotateFourPalettesLeft);
    RET;

}

void Function17dca9(void){
    CALL(aIncCrashCheckPointer);
    CALL(aHlToCrashCheckPointer);

    return Function17dcaf();
}

void Function17dcaf(void){
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(wBGPals1);
    LD_DE(1 * PALETTE_SIZE);
    LD_C(8);

asm_17dcbb:
    PUSH_HL;
    LD_A(0xff);
    LD_hli_A;
    LD_A(0x7f);
    LD_hl_A;
    POP_HL;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto asm_17dcbb;
    CALL(aRotateThreePalettesRight);
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    RET;

}

void Function17dccf(void){
    CALL(aIncCrashCheckPointer);
    PUSH_HL;
    LD_A_addr(wcd4b);
    LD_L_A;
    LD_A_addr(wcd4c);
    LD_H_A;
    LD_A_addr(wcd2e);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_C_A;
    LD_A_hl;
    LD_B_A;
    CALL(aFunction17e43d);
    CALL(aHlToCrashCheckPointer);

asm_17dced:
    LD_A_addr(wMobileCrashCheckPointer);
    LD_L_A;
    LD_A_addr(wMobileCrashCheckPointer + 1);
    LD_H_A;
    LD_A_hl;
    CP_A(0xff);
    IF_Z goto asm_17dd0d;

crash_loop:
    CP_A(0x31);
    IF_NC goto crash_loop;
    CALL(aFunction17d711);
    LD_A_addr(wcd77);
    BIT_A(7);
    IF_NZ goto asm_17dd0d;
    AND_A_A;
    IF_Z goto asm_17dd11;
    goto asm_17dced;


asm_17dd0d:
    POP_HL;
    JP(mHlToCrashCheckPointer);


asm_17dd11:
    POP_HL;
    RET;

}

void Function17dd13(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    CALL(aHlToCrashCheckPointer);
    CALL(aFunction17e447);
    PUSH_HL;
    hlcoord(0, 0, wTilemap);
    ADD_HL_BC;
    PUSH_HL;
    POP_BC;
    POP_HL;
    CALL(aPlaceHLTextAtBC);
    RET;

}

void Function17dd30(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_C_A;
    LD_B(0);
    LD_A_hli;
    PUSH_AF;
    CALL(aHlToCrashCheckPointer);
    POP_AF;
    hlcoord(0, 0, wTilemap);
    ADD_HL_DE;
    CALL(aFunction17e600);
    RET;

}

void Function17dd49(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0xa);
    CALL(aCopyBytes);
    LD_A_addr(wc711);
    LD_C_A;
    LD_B(0);
    CALL(aCopyBytes);
    LD_A_addr(wc70a);
    CP_A(0xc0);
    IF_C goto sram;
    LD_A_addr(wc708);
    LDH_addr_A(rSVBK);
    goto got_bank;


sram:
    LD_A_addr(wc708);
    CALL(aOpenSRAM);


got_bank:
    LD_A_addr(wc709);
    LD_L_A;
    LD_A_addr(wc70a);
    LD_H_A;
    LD_DE(wc688);
    LD_A_addr(wc711);
    LD_C_A;
    LD_B(0);
    CALL(aCopyBytes);
    LD_A_addr(wc70a);
    CP_A(0xc0);
    IF_C goto close_sram;
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    goto exited_bank;


close_sram:
    CALL(aCloseSRAM);


exited_bank:
    LD_A_addr(wc711);
    LD_C_A;
    LD_HL(wc712);
    LD_DE(wc688);

loop:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_Z goto next;
    IF_C goto load;
    goto load2;


next:
    DEC_C;
    IF_NZ goto loop;
    LD_A_addr(wc70d);
    LD_L_A;
    LD_A_addr(wc70e);
    LD_H_A;
    goto done;


load2:
    LD_A_addr(wc70f);
    LD_L_A;
    LD_A_addr(wc710);
    LD_H_A;
    goto done;


load:
    LD_A_addr(wc70b);
    LD_L_A;
    LD_A_addr(wc70c);
    LD_H_A;


done:
    CALL(aFunction17e40f);
    RET;

}

void Function17ddcd(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x8);
    CALL(aCopyBytes);
    LD_A_addr(wc70a);
    CP_A(0xc0);
    IF_C goto asm_17dde7;
    LD_A_addr(wc708);
    LDH_addr_A(rSVBK);
    goto asm_17dded;


asm_17dde7:
    LD_A_addr(wc708);
    CALL(aOpenSRAM);


asm_17dded:
    LD_A_addr(wc709);
    LD_E_A;
    LD_A_addr(wc70a);
    LD_D_A;
    LD_A_de;
    LD_addr_A(wc710);
    LD_A_addr(wc70b);
    LD_C_A;
    LD_B(0);
    LD_A_addr(wc70a);
    CP_A(0xc0);
    IF_C goto asm_17de0c;
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    goto asm_17de0f;


asm_17de0c:
    CALL(aCloseSRAM);


asm_17de0f:
    PUSH_HL;
    LD_HL(mUnknown_17da8c);
    ADD_HL_BC;
    LD_A_hl;
    LD_HL(wc710);
    AND_A_hl;
    POP_HL;
    IF_NZ goto asm_17de26;
    LD_A_addr(wc70e);
    LD_L_A;
    LD_A_addr(wc70f);
    LD_H_A;
    goto asm_17de2e;


asm_17de26:
    LD_A_addr(wc70c);
    LD_L_A;
    LD_A_addr(wc70d);
    LD_H_A;


asm_17de2e:
    CALL(aFunction17e40f);
    RET;

}

void Function17de32(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x9);
    CALL(aCopyBytes);
    LD_A_addr(wc710);
    LD_C_A;
    LD_B(0);
    CALL(aCopyBytes);
    LD_A(0x6);
    CALL(aOpenSRAM);
    CALL(aFunction17f4f6);
    LD_A_addr(wc708);
    LD_E_A;
    LD_A_addr(wc709);
    LD_D_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_A_addr(wc710);
    LD_C_A;
    LD_HL(wc711);

asm_17de61:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_Z goto asm_17de6b;
    IF_C goto asm_17de82;
    goto asm_17de78;


asm_17de6b:
    DEC_C;
    IF_NZ goto asm_17de61;
    LD_A_addr(wc70c);
    LD_L_A;
    LD_A_addr(wc70d);
    LD_H_A;
    goto asm_17de8a;


asm_17de78:
    LD_A_addr(wc70e);
    LD_L_A;
    LD_A_addr(wc70f);
    LD_H_A;
    goto asm_17de8a;


asm_17de82:
    LD_A_addr(wc70a);
    LD_L_A;
    LD_A_addr(wc70b);
    LD_H_A;


asm_17de8a:
    CALL(aCloseSRAM);
    CALL(aFunction17e40f);
    RET;

}

void Function17de91(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x7);
    CALL(aCopyBytes);
    LD_A(0x6);
    CALL(aOpenSRAM);
    CALL(aFunction17f4f6);
    LD_A_addr(wc708);
    LD_E_A;
    LD_A_addr(wc709);
    LD_D_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_A_addr(wc70a);
    LD_C_A;
    LD_B(0);
    LD_HL(mUnknown_17da8c);
    ADD_HL_BC;
    LD_A_hl;
    LD_L_E;
    LD_H_D;
    AND_A_hl;
    IF_NZ goto asm_17deca;
    LD_A_addr(wc70d);
    LD_L_A;
    LD_A_addr(wc70e);
    LD_H_A;
    goto asm_17ded2;


asm_17deca:
    LD_A_addr(wc70b);
    LD_L_A;
    LD_A_addr(wc70c);
    LD_H_A;


asm_17ded2:
    CALL(aCloseSRAM);
    CALL(aFunction17e40f);
    RET;

}

void Function17ded9(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x1f);
    CALL(aCopyBytes);
    CALL(aFunction17e32b);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_HL(wc708);
    LD_A_hli;
    LD_addr_A(wCurPartySpecies);
    LD_addr_A(wTempEnemyMonSpecies);
    LD_A_hli;
    LD_addr_A(wCurPartyLevel);
    LD_A_hli;
    LD_B_A;
    LD_A_addr(wPartyCount);
    CP_A(0x6);
    JP_NC (mFunction17e026);
    XOR_A_A;
    LD_addr_A(wMonType);
    PUSH_HL;
    PUSH_BC;
    PREDEF(pTryAddMonToParty);
    FARCALL(aSetCaughtData);
    POP_BC;
    POP_HL;
    BIT_B(1);
    IF_Z goto asm_17df33;
    PUSH_BC;
    PUSH_HL;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMonNicknames);
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aCopyBytes);
    POP_BC;
    goto asm_17df37;


asm_17df33:
    LD_DE(0x6);
    ADD_HL_DE;


asm_17df37:
    BIT_B(2);
    IF_Z goto asm_17df5a;
    PUSH_BC;
    PUSH_HL;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMonOTs);
    CALL(aSkipNames);
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aCopyBytes);
    LD_A_hli;
    LD_B_A;
    PUSH_HL;
    FARCALL(aSetGiftPartyMonCaughtData);
    POP_HL;
    POP_BC;
    goto asm_17df5e;


asm_17df5a:
    LD_DE(0x7);
    ADD_HL_DE;


asm_17df5e:
    BIT_B(3);
    IF_Z goto asm_17df79;
    PUSH_BC;
    PUSH_HL;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1ID);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    POP_BC;
    goto asm_17df7b;


asm_17df79:
    INC_HL;
    INC_HL;


asm_17df7b:
    BIT_B(4);
    IF_Z goto asm_17dfd0;
    PUSH_BC;
    PUSH_HL;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1DVs);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    PUSH_HL;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1Species);
    CALL(aGetPartyLocation);
    LD_A_hl;
    LD_addr_A(wCurSpecies);
    CALL(aGetBaseData);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1MaxHP);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;
    PUSH_HL;
    LD_B(FALSE);
    FARCALL(aCalcMonStats);
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1HP);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hl;
    LD_de_A;
    POP_HL;
    POP_BC;
    goto asm_17dfd2;


asm_17dfd0:
    INC_HL;
    INC_HL;


asm_17dfd2:
    BIT_B(5);
    IF_Z goto asm_17dfea;
    PUSH_BC;
    PUSH_HL;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1Item);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_A_hli;
    LD_de_A;
    POP_BC;
    goto asm_17dfeb;


asm_17dfea:
    INC_HL;


asm_17dfeb:
    BIT_B(6);
    IF_Z goto asm_17e01f;
    PUSH_BC;
    PUSH_HL;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1Moves);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;
    POP_HL;
    PUSH_DE;
    LD_BC(0x4);
    CALL(aCopyBytes);
    POP_DE;
    PUSH_HL;
    PUSH_DE;
    LD_A_addr(wPartyCount);
    DEC_A;
    LD_HL(wPartyMon1PP);
    CALL(aGetPartyLocation);
    LD_D_H;
    LD_E_L;
    POP_HL;
    PREDEF(pFillPP);
    POP_HL;
    POP_BC;
    JP(masm_17e0ee);


asm_17e01f:
    LD_DE(0x4);
    ADD_HL_DE;
    JP(masm_17e0ee);

}

void Function17e026(void){
    LD_A(BANK(sBoxCount));
    CALL(aOpenSRAM);
    LD_A_addr(sBoxCount);
    CALL(aCloseSRAM);
    CP_A(0x14);
    JP_NC (mFunction17e026_asm_17e0ea);
    BIT_B(0);
    JP_Z (mFunction17e026_asm_17e0ea);
    PUSH_BC;
    PUSH_HL;
    FARCALL(aLoadEnemyMon);
    FARCALL(aSendMonIntoBox);
    FARCALL(aSetBoxMonCaughtData);
    POP_HL;
    POP_BC;
    LD_A(BANK(sBoxMonNicknames));
    CALL(aOpenSRAM);
    BIT_B(1);
    IF_Z goto asm_17e067;
    PUSH_BC;
    LD_BC(0xb);
    LD_DE(sBoxMonNicknames);
    CALL(aCopyBytes);
    POP_BC;
    goto asm_17e06b;


asm_17e067:
    LD_DE(0x6);
    ADD_HL_DE;


asm_17e06b:
    BIT_B(2);
    IF_Z goto asm_17e08e;
    PUSH_BC;
    LD_BC(0x6);
    LD_DE(sBoxMonOTs);
    CALL(aCopyBytes);
    LD_A_hli;
    LD_B_A;
    PUSH_HL;
    CALL(aCloseSRAM);
    FARCALL(aSetGiftBoxMonCaughtData);
    LD_A(0x1);
    CALL(aOpenSRAM);
    POP_HL;
    POP_BC;
    goto asm_17e092;


asm_17e08e:
    LD_DE(0x7);
    ADD_HL_DE;


asm_17e092:
    BIT_B(3);
    IF_Z goto asm_17e0a2;
    PUSH_BC;
    LD_DE(sBoxMon1ID);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    POP_BC;
    goto asm_17e0a4;


asm_17e0a2:
    INC_HL;
    INC_HL;


asm_17e0a4:
    BIT_B(4);
    IF_Z goto asm_17e0b4;
    PUSH_BC;
    LD_DE(sBoxMon1DVs);
    LD_A_hli;
    LD_de_A;
    INC_DE;
    LD_A_hli;
    LD_de_A;
    POP_BC;
    goto asm_17e0b6;


asm_17e0b4:
    INC_HL;
    INC_HL;


asm_17e0b6:
    BIT_B(5);
    LD_A_hli;
    IF_Z goto asm_17e0be;
    LD_addr_A(sBoxMon1Item);


asm_17e0be:
    BIT_B(6);
    IF_Z goto asm_17e0e1;
    PUSH_BC;
    LD_DE(sBoxMon1Moves);
    LD_BC(0x4);
    CALL(aCopyBytes);
    PUSH_HL;
    LD_HL(sBoxMon1Moves);
    LD_DE(sBoxMon1PP);
    PREDEF(pFillPP);
    CALL(aCloseSRAM);
    POP_HL;
    POP_BC;
    INC_HL;
    INC_HL;
    JR(masm_17e0ee);


asm_17e0e1:
    CALL(aCloseSRAM);
    LD_DE(0x6);
    ADD_HL_DE;
    JR(masm_17e0ee);


asm_17e0ea:
    LD_BC(0x1a);
    ADD_HL_BC;

    return asm_17e0ee();
}

void asm_17e0ee(void){
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    POP_AF;
    LDH_addr_A(rSVBK);
    PUSH_HL;
    CALL(aFunction17e349);
    POP_HL;
    CALL(aFunction17e40f);
    RET;

}

void Function17e0fd(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x6);
    CALL(aCopyBytes);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_HL(wc708);
    LD_A_hli;
    LD_addr_A(wCurItem);
    LD_A_hli;
    LD_addr_A(wItemQuantityChange);
    PUSH_HL;
    LD_HL(wNumItems);
    CALL(aReceiveItem);
    POP_HL;
    IF_C goto asm_17e127;
    INC_HL;
    INC_HL;


asm_17e127:
    LD_A_hli;
    LD_B_A;
    LD_A_hl;
    LD_H_A;
    LD_L_B;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aFunction17e40f);
    RET;

}

void Function17e133(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x5);
    CALL(aCopyBytes);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_HL(wc708);
    LD_A_hli;
    LD_addr_A(wScriptVar);
    PUSH_HL;
    FARCALL(aMobileCheckOwnMonAnywhere);
    POP_HL;
    IF_C goto asm_17e159;
    INC_HL;
    INC_HL;


asm_17e159:
    LD_A_hli;
    LD_B_A;
    LD_A_hl;
    LD_H_A;
    LD_L_B;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aFunction17e40f);
    RET;

}

void Function17e165(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0x5);
    CALL(aCopyBytes);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_HL(wc708);
    LD_A_hli;
    LD_addr_A(wCurItem);
    PUSH_HL;
    LD_HL(wNumItems);
    CALL(aCheckItem);
    POP_HL;
    IF_C goto asm_17e195;
    PUSH_HL;
    LD_HL(wNumPCItems);
    CALL(aCheckItem);
    POP_HL;
    IF_C goto asm_17e195;
    INC_HL;
    INC_HL;


asm_17e195:
    LD_A_hli;
    LD_B_A;
    LD_A_hl;
    LD_H_A;
    LD_L_B;
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aFunction17e40f);
    RET;

}

void Function17e1a1(void){
    CALL(aIncCrashCheckPointer);
    LD_DE(wc708);
    LD_BC(0xd);
    CALL(aCopyBytes);
    LD_A_addr(wc70a);
    CP_A(0xc0);
    IF_C goto asm_17e1bb;
    LD_A_addr(wc708);
    LDH_addr_A(rSVBK);
    goto asm_17e1c1;


asm_17e1bb:
    LD_A_addr(wc708);
    CALL(aOpenSRAM);


asm_17e1c1:
    LD_A_addr(wc709);
    LD_L_A;
    LD_A_addr(wc70a);
    LD_H_A;
    LD_DE(wc608);
    LD_A_addr(wc70b);
    LD_C_A;
    LD_B(0);
    CALL(aCopyBytes);
    LD_A_addr(wc70a);
    CP_A(0xc0);
    IF_C goto asm_17e1e2;
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    goto asm_17e1e5;


asm_17e1e2:
    CALL(aCloseSRAM);


asm_17e1e5:
    LD_A_addr(wc70e);
    CP_A(0xc0);
    IF_C goto asm_17e1f3;
    LD_A_addr(wc70c);
    LDH_addr_A(rSVBK);
    goto asm_17e1f9;


asm_17e1f3:
    LD_A_addr(wc70c);
    CALL(aOpenSRAM);


asm_17e1f9:
    LD_A_addr(wc70d);
    LD_L_A;
    LD_A_addr(wc70e);
    LD_H_A;
    LD_DE(wc688);
    LD_A_addr(wc70b);
    LD_C_A;
    LD_B(0);
    CALL(aCopyBytes);
    LD_A_addr(wc70e);
    CP_A(0xc0);
    IF_C goto asm_17e21a;
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    goto asm_17e21d;


asm_17e21a:
    CALL(aCloseSRAM);


asm_17e21d:
    LD_A_addr(wc70b);
    LD_C_A;
    LD_HL(wc688);
    LD_DE(wc608);

asm_17e227:
    LD_A_de;
    INC_DE;
    CP_A_hl;
    INC_HL;
    IF_Z goto asm_17e231;
    IF_C goto asm_17e23e;
    goto asm_17e248;


asm_17e231:
    DEC_C;
    IF_NZ goto asm_17e227;
    LD_A_addr(wc711);
    LD_L_A;
    LD_A_addr(wc712);
    LD_H_A;
    goto asm_17e250;


asm_17e23e:
    LD_A_addr(wc70f);
    LD_L_A;
    LD_A_addr(wc710);
    LD_H_A;
    goto asm_17e250;


asm_17e248:
    LD_A_addr(wc712 + 1);
    LD_L_A;
    LD_A_addr(wc712 + 2);
    LD_H_A;


asm_17e250:
    CALL(aFunction17e40f);
    RET;

}

void Function17e254(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_de_A;
    CALL(aHlToCrashCheckPointer);
    RET;

}

void Function17e261(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_de;
    ADD_A_hl;
    LD_de_A;
    INC_HL;
    CALL(aHlToCrashCheckPointer);
    RET;

}

void Function17e270(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_de;
    SUB_A_hl;
    LD_de_A;
    INC_HL;
    CALL(aHlToCrashCheckPointer);
    RET;

}

void Function17e27f(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    CALL(aHlToCrashCheckPointer);
    LD_L_C;
    LD_H_B;
    LD_A_de;
    ADD_A_hl;
    LD_de_A;
    RET;

}

void Function17e293(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
    CALL(aHlToCrashCheckPointer);
    LD_L_C;
    LD_H_B;
    LD_A_de;
    SUB_A_hl;
    LD_de_A;
    RET;

}

void Function17e2a7(void){
    CALL(aIncCrashCheckPointer);
    CALL(aHlToCrashCheckPointer);
    CALL(aFunction17e32b);
    XOR_A_A;
    LD_addr_A(wcf66);
    FARCALL(aFunction118233);
    LD_DE(mPostalMarkGFX);
    LD_HL(vTiles2 + LEN_2BPP_TILE * 0x60);
    LD_BC((BANK(aPostalMarkGFX) << 8) | 1);
    CALL(aGet2bpp);
    LD_A_addr(wMobileErrorCodeBuffer);
    AND_A_A;
    IF_Z goto asm_17e2d8;
    CP_A(0xa);
    IF_Z goto asm_17e2f7;
    CP_A(0xb);
    IF_Z goto asm_17e300;
    CALL(aFunction17e309);
    RET;


asm_17e2d8:
    CALL(aFunction17d60b);
    CALL(aFunction17e349);
    XOR_A_A;
    LD_addr_A(wcd7a);
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_HL(0xaa73);
    LD_DE(0xaa7f);
    LD_BC(0xc);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;


asm_17e2f7:
    CALL(aFunction17e349);
    LD_A(0x1);
    LD_addr_A(wcd7a);
    RET;


asm_17e300:
    CALL(aFunction17e349);
    LD_A(0x2);
    LD_addr_A(wcd7a);
    RET;

}

void Function17e309(void){
    LD_A(0x2);
    LD_addr_A(wc303);
    CALL(aFunction17dcaf);
    CALL(aClearScreen);
    CALL(aFunction17e349);
    CALL(aFunction17d5f6);
    FARCALL(aDisplayMobileError);
    CALL(aFunction17e349);
    CALL(aFunction17dcaf);
    XOR_A_A;
    LD_addr_A(wcd77);
    RET;

}

void Function17e32b(void){
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_HL(wc608);
    LD_DE(0xb0b1);
    LD_BC(0x40);
    CALL(aCopyBytes);
    LD_HL(wBGMapBuffer);
    LD_BC(0x5b);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

}

void Function17e349(void){
    LD_A(0x5);
    CALL(aOpenSRAM);
    LD_HL(0xb0b1);
    LD_DE(wc608);
    LD_BC(0x40);
    CALL(aCopyBytes);
    LD_DE(wBGMapBuffer);
    LD_BC(0x5b);
    CALL(aCopyBytes);
    CALL(aCloseSRAM);
    RET;

// inc_crash_check_pointer_farcall: MACRO
//     call IncCrashCheckPointer
//     call HlToCrashCheckPointer ; redundant
//     ldh a, [rSVBK]
//     push af
//     ld a, $1
//     ldh [rSVBK], a
// rept _NARG
//     farcall \1
//     shift
// endr
//     pop af
//     ldh [rSVBK], a
//     ret
// ENDM

}

void IncCrashCheckPointer_SaveGameData(void){
    //inc_crash_check_pointer_farcall ['_SaveGameData']

    return IncCrashCheckPointer_SaveAfterLinkTrade();
}

void IncCrashCheckPointer_SaveAfterLinkTrade(void){
    //inc_crash_check_pointer_farcall ['SaveAfterLinkTrade']

    return IncCrashCheckPointer_SaveBox();
}

void IncCrashCheckPointer_SaveBox(void){
    //inc_crash_check_pointer_farcall ['SaveBox']

    return IncCrashCheckPointer_SaveChecksum();
}

void IncCrashCheckPointer_SaveChecksum(void){
    //inc_crash_check_pointer_farcall ['SaveChecksum']

    return IncCrashCheckPointer_SaveTrainerRankingsChecksum();
}

void IncCrashCheckPointer_SaveTrainerRankingsChecksum(void){
    //inc_crash_check_pointer_farcall ['UpdateTrainerRankingsChecksum2', 'BackupMobileEventIndex']

    return Function17e3e0();
}

void Function17e3e0(void){
    CALL(aIncCrashCheckPointer);
    LD_A_hli;
    LD_C_A;
    CALL(aHlToCrashCheckPointer);
    LD_A(0x1);
    LDH_addr_A(hBGMapMode);
    CALL(aDelayFrames);
    RET;

}

void Function17e3f0(void){
    CALL(aIncCrashCheckPointer);
    CALL(aHlToCrashCheckPointer);

asm_17e3f6:
    CALL(aJoyTextDelay);
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(0x1);
    RET_NZ ;
    LD_A_hl;
    AND_A(0x2);
    RET_NZ ;
    CALL(aWaitBGMap);
    goto asm_17e3f6;

    return Function17e409();
}

void Function17e409(void){
    LD_HL(wcd77);
    SET_hl(7);
    RET;

}

void Function17e40f(void){
    LD_DE(wBGPals1);
    ADD_HL_DE;
    JR(mHlToCrashCheckPointer);

}

void IncCrashCheckPointer(void){
    LD_A_addr(wMobileCrashCheckPointer);
    LD_L_A;
    LD_A_addr(wMobileCrashCheckPointer + 1);
    LD_H_A;
    INC_HL;

    return HlToCrashCheckPointer();
}

void HlToCrashCheckPointer(void){
    LD_A_L;
    LD_addr_A(wMobileCrashCheckPointer);
    LD_A_H;
    LD_addr_A(wMobileCrashCheckPointer + 1);
    RET;

}

void Function17e427(void){
    LD_HL(hJoyPressed);
    LD_A_hl;
    AND_A(0x1);
    IF_NZ goto asm_17e432;
    AND_A(0x2);
    RET_Z ;


asm_17e432:
    LD_A(0x3);
    LD_addr_A(wcd77);
    RET;

}

void Function17e438(void){
    LD_HL(wcd77);
    INC_hl;
    RET;

}

void Function17e43d(void){
    LD_A_addr(wBGMapBuffer);
    LD_L_A;
    LD_A_addr(wcd21);
    LD_H_A;
    ADD_HL_BC;
    RET;

}

void Function17e447(void){
    LD_A_addr(wBGMapBuffer);
    LD_L_A;
    LD_A_addr(wcd21);
    LD_H_A;
    ADD_HL_DE;
    RET;

}

void Function17e451(void){
    LD_A_addr(wcd42);
    AND_A_A;
    RET_Z ;
    CALL(aFunction17e51b);
    CALL(aFunction17e4dd);
    LD_A_addr(wcd2e);
    PUSH_AF;
    LD_A_addr(wcd49);
    LD_L_A;
    LD_A_addr(wcd4a);
    LD_H_A;
    LD_A_addr(wcd2f);
    LD_addr_A(wcd2e);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    PUSH_HL;
    hlcoord(0, 0, wTilemap);
    LD_BC(0x14);
    LD_A_addr(wcd23);
    CALL(aAddNTimes);
    LD_A_addr(wCreditsTimer);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;
    LD_A_addr(wMobileCommsJumptableIndex);

asm_17e48b:
    PUSH_AF;
    PUSH_HL;
    LD_A_addr(wcd24);

asm_17e490:
    PUSH_AF;
    PUSH_HL;
    LD_A_bc;
    INC_BC;
    LD_E_A;
    LD_A_bc;
    INC_BC;
    LD_D_A;
    PUSH_BC;
    PUSH_HL;
    LD_A_addr(wBGMapBuffer);
    LD_L_A;
    LD_A_addr(wcd21);
    LD_H_A;
    ADD_HL_DE;
    PUSH_HL;
    POP_DE;
    POP_HL;
    CALL(aPlaceString);
    POP_BC;
    POP_HL;
    LD_A_addr(wcd26);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_addr(wcd2e);
    INC_A;
    LD_addr_A(wcd2e);
    LD_E_A;
    LD_A_addr(wcd42);
    CP_A_E;
    IF_Z goto asm_17e4d5;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17e490;
    POP_HL;
    LD_A_addr(wcd27);
    LD_DE(0x14);

asm_17e4cb:
    ADD_HL_DE;
    DEC_A;
    IF_NZ goto asm_17e4cb;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17e48b;
    goto asm_17e4d8;


asm_17e4d5:
    POP_AF;
    POP_HL;
    POP_AF;


asm_17e4d8:
    POP_AF;
    LD_addr_A(wcd2e);
    RET;

}

void Function17e4dd(void){
    LD_A_addr(wcd2c);
    AND_A(0x1);
    RET_Z ;
    LD_A_addr(wcd29);
    hlcoord(0, 0, wTilemap);
    LD_BC(0x14);
    CALL(aAddNTimes);
    LD_A_addr(wcd28);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wcd2f);
    AND_A_A;
    IF_Z goto asm_17e4ff;
    LD_A(0x61);
    LD_hl_A;


asm_17e4ff:
    LD_A_addr(wcd2a);
    LD_BC(0x14);
    CALL(aAddNTimes);
    LD_A_addr(wcd42);
    LD_C_A;
    LD_A_addr(wcd2e);
    LD_B_A;
    LD_A_addr(wcd24);
    ADD_A_B;
    CP_A_C;
    RET_Z ;
    RET_NC ;
    LD_A(0xee);
    LD_hl_A;
    RET;

}

void Function17e51b(void){
    LD_A_addr(wcd28);
    LD_HL(wCreditsTimer);
    SUB_A_hl;
    INC_A;
    LD_addr_A(wcd4f);
    hlcoord(0, 0, wTilemap);
    LD_BC(0x14);
    LD_A_addr(wcd23);
    DEC_A;
    CALL(aAddNTimes);
    LD_A_addr(wCreditsTimer);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_addr(wMobileCommsJumptableIndex);
    LD_C_A;
    LD_A_addr(wcd27);
    CALL(aSimpleMultiply);

asm_17e544:
    PUSH_AF;
    PUSH_HL;
    LD_A_addr(wcd4f);
    LD_C_A;
    LD_B(0);
    LD_A(0x7f);
    CALL(aByteFill);
    POP_HL;
    LD_BC(0x14);
    ADD_HL_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17e544;
    RET;

}

void Function17e55b(void){
    LD_A_addr(wcd42);
    AND_A_A;
    RET_Z ;
    LD_A(0xed);
    CALL(aFunction17e571);
    RET;

}

void Function17e566(void){
    LD_A_addr(wcd42);
    AND_A_A;
    RET_Z ;
    LD_A(0x7f);
    CALL(aFunction17e571);
    RET;

}

void Function17e571(void){
    PUSH_AF;
    hlcoord(0, 0, wTilemap);
    LD_BC(0x14);
    LD_A_addr(wcd23);
    CALL(aAddNTimes);
    LD_A_addr(wCreditsTimer);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    DEC_HL;
    PUSH_HL;
    LD_A_addr(wcd31);
    DEC_A;
    LD_C_A;
    LD_A_addr(wcd27);
    CALL(aSimpleMultiply);
    LD_L(0x0);
    LD_H_L;
    LD_BC(0x14);
    CALL(aAddNTimes);
    LD_A_addr(wcd30);
    DEC_A;
    LD_C_A;
    LD_A_addr(wcd26);
    CALL(aSimpleMultiply);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;
    ADD_HL_BC;
    POP_AF;
    LD_hl_A;
    RET;

}

void Function17e5af(void){
    LD_A_addr(wcd2c);
    AND_A(0x2);
    RET_Z ;
    LD_A_addr(wcd43);
    LD_L_A;
    LD_A_addr(wMobileInactivityTimerMinutes);
    LD_H_A;
    bccoord(0, 0, wTilemap);
    ADD_HL_BC;
    LD_BC(0xffec);
    ADD_HL_BC;
    LD_A_addr(wMobileInactivityTimerSeconds);
    LD_C_A;
    LD_B(0);
    LD_A_addr(wMobileInactivityTimerFrames);
    CALL(aFunction17e600);
    LD_A_addr(wcd2e);
    LD_C_A;
    LD_B(0);
    LD_A_addr(wcd4d);
    LD_L_A;
    LD_A_addr(wcd4e);
    LD_H_A;
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_addr(wBGMapBuffer);
    LD_L_A;
    LD_A_addr(wcd21);
    LD_H_A;
    ADD_HL_DE;
    PUSH_HL;
    POP_DE;
    LD_A_addr(wcd43);
    LD_L_A;
    LD_A_addr(wMobileInactivityTimerMinutes);
    LD_H_A;
    bccoord(0, 0, wTilemap);
    ADD_HL_BC;
    CALL(aPlaceString);
    RET;

}

void Function17e600(void){

asm_17e600:
    PUSH_AF;
    PUSH_HL;
    PUSH_BC;
    LD_A(0x7f);
    CALL(aByteFill);
    POP_BC;
    POP_HL;
    LD_DE(0x14);
    ADD_HL_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17e600;
    RET;

}

void Function17e613(void){
    PUSH_HL;
    hlcoord(0, 0, wTilemap);
    LD_BC(0x14);
    LD_A_de;
    INC_DE;
    PUSH_AF;
    LD_A_de;
    INC_DE;
    AND_A_A;

asm_17e620:
    IF_Z goto asm_17e626;
    ADD_HL_BC;
    DEC_A;
    goto asm_17e620;


asm_17e626:
    POP_AF;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    PUSH_HL;
    LD_A_addr(wcd53);
    LD_hli_A;
    LD_A_de;
    INC_DE;
    DEC_A;
    DEC_A;
    IF_Z goto asm_17e63f;
    LD_C_A;
    LD_A_addr(wcd53);
    INC_A;

asm_17e63b:
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_17e63b;


asm_17e63f:
    LD_A_addr(wcd53);
    ADD_A(0x2);
    LD_hl_A;
    POP_HL;
    LD_BC(0x14);
    ADD_HL_BC;
    LD_A_de;
    DEC_DE;
    DEC_A;
    DEC_A;
    IF_Z goto asm_17e674;
    LD_B_A;

asm_17e651:
    PUSH_HL;
    LD_A_addr(wcd53);
    ADD_A(0x3);
    LD_hli_A;
    LD_A_de;
    DEC_A;
    DEC_A;
    IF_Z goto asm_17e664;
    LD_C_A;
    LD_A(0x7f);

asm_17e660:
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_17e660;


asm_17e664:
    LD_A_addr(wcd53);
    ADD_A(0x4);
    LD_hl_A;
    POP_HL;
    PUSH_BC;
    LD_BC(0x14);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto asm_17e651;


asm_17e674:
    LD_A_addr(wcd53);
    ADD_A(0x5);
    LD_hli_A;
    LD_A_de;
    DEC_A;
    DEC_A;
    IF_Z goto asm_17e689;
    LD_C_A;
    LD_A_addr(wcd53);
    ADD_A(0x6);

asm_17e685:
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_17e685;


asm_17e689:
    LD_A_addr(wcd53);
    ADD_A(0x7);
    LD_hl_A;
    POP_HL;
    RET;

}

void Function17e691(void){
    PUSH_HL;
    LD_HL(0);
    LD_BC(0x14);
    LD_A_de;
    INC_DE;
    PUSH_AF;
    LD_A_de;
    INC_DE;
    INC_DE;
    AND_A_A;

asm_17e69f:
    IF_Z goto asm_17e6a5;
    ADD_HL_BC;
    DEC_A;
    goto asm_17e69f;


asm_17e6a5:
    POP_AF;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    DEC_DE;

asm_17e6ac:
    PUSH_AF;
    PUSH_HL;
    LD_A_de;

asm_17e6af:
    PUSH_AF;
    PUSH_HL;
    PUSH_HL;
    bccoord(0, 0, wTilemap);
    ADD_HL_BC;
    LD_A_hl;
    CP_A(0x7f);
    IF_Z goto asm_17e6c2;
    LD_A_addr(wcd53);
    ADD_A(0x8);
    goto asm_17e6c7;


asm_17e6c2:
    LD_A_addr(wcd53);
    goto asm_17e6c7;


asm_17e6c7:
    POP_HL;
    bccoord(0, 0, wAttrmap);
    ADD_HL_BC;
    LD_hl_A;
    POP_HL;
    INC_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17e6af;
    POP_HL;
    LD_BC(0x14);
    ADD_HL_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_17e6ac;
    POP_HL;
    RET;

}

void Function17e6de(void){
    PUSH_AF;
    LD_A_addr(wc708);
    LD_L_A;
    LD_A_addr(wc709);
    LD_H_A;
    decoord(0, 0, wAttrmap);
    ADD_HL_DE;
    POP_AF;
    LD_B(0x7);

asm_17e6ee:
    PUSH_HL;
    LD_C(0x7);

asm_17e6f1:
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_17e6f1;
    POP_HL;
    LD_DE(0x14);
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto asm_17e6ee;
    RET;

}

void PokemonNewsGFX(void){
// INCBIN "gfx/mobile/pokemon_news.2bpp"

    return PostalMarkGFX();
}

void PostalMarkGFX(void){
// INCBIN "gfx/font/postal_mark.2bpp"

    return PokemonNewsTileAttrmap();
}

void PokemonNewsTileAttrmap(void){
// INCBIN "gfx/mobile/pokemon_news.bin"

    return PokemonNewsPalettes();
}

void PokemonNewsPalettes(void){
// INCLUDE "gfx/mobile/pokemon_news.pal"

    return RunMobileScript();
}

void RunMobileScript(void){
    LD_A(0x6);
    CALL(aOpenSRAM);
    INC_DE;

loop:
    CALL(av_RunMobileScript);
    IF_C goto finished;
    goto loop;


finished:
    CALL(aCloseSRAM);
    RET;

}

void v_RunMobileScript(void){
    LD_A_de;
    INC_DE;
    CP_A(0x50);
    IF_Z goto finished;
    CP_A(0x10);  // jumptable size
    IF_NC goto finished;
    DEC_A;
    PUSH_DE;
    LD_E_A;
    LD_D(0);
    LD_HL(mv_RunMobileScript_Jumptable);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    JP_hl;


finished:
    SCF;
    RET;


Jumptable:
    //dw ['Function17f081'];  // 0
    //dw ['Function17f0f8'];  // 1
    //dw ['Function17f154'];  // 2
    //dw ['Function17f181'];  // 3
    //dw ['Function17f1d0'];  // 4
    //dw ['Function17f220'];  // 5
    //dw ['Function17f27b'];  // 6
    //dw ['Function17f2cb'];  // 7
    //dw ['MobileScript_PlayerName'];  // 8
    //dw ['MobileScript_Prefecture'];  // 9
    //dw ['Function17f382'];  // a
    //dw ['Function17f3c9'];  // b
    //dw ['Function17f3f0'];  // c
    //dw ['Function17f41d'];  // d
    //dw ['Function17f44f'];  // e
    //dw ['Function17f44f'];  // f

    return Function17f081();
}

void Function17f081(void){
    POP_HL;
    CALL(aFunction17f524);
    IF_C goto asm_17f09f;
    LD_DE(4);
    ADD_HL_DE;
    LD_A_hli;
    INC_HL;
    INC_HL;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    CP_A(0x50);
    IF_Z goto asm_17f09d;
    AND_A_A;
    RET;


asm_17f09d:
    SCF;
    RET;


asm_17f09f:
    PUSH_BC;
    LD_DE(wcd54);
    LD_BC(7);
    CALL(aCopyBytes);
    POP_BC;
    PUSH_HL;
    PUSH_BC;
    CALL(aFunction17f4f6);
    POP_BC;
    LD_A_addr(wcd54);
    LD_E_A;
    LD_A_addr(wcd55);
    LD_D_A;
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;
    PUSH_HL;
    LD_A_addr(wcd56);
    LD_B_A;
    LD_A_addr(wcd57);
    LD_C_A;
    CALL(aMobilePrintNum);
    LD_A_L;
    LD_addr_A(wcd52);
    LD_A_H;
    LD_addr_A(wcd53);
    LD_A_addr(wcd59);
    AND_A_A;
    IF_Z goto asm_17f0ee;
    LD_C_A;
    LD_A_addr(wcd57);
    INC_A;
    LD_B_A;
    LD_E_L;
    LD_D_H;
    DEC_DE;

asm_17f0e0:
    LD_A_C;
    CP_A_B;
    IF_Z goto asm_17f0ea;
    LD_A_de;
    DEC_DE;
    LD_hld_A;
    DEC_B;
    goto asm_17f0e0;


asm_17f0ea:
    LD_A_addr(wcd5a);
    LD_hl_A;


asm_17f0ee:
    POP_HL;
    LD_A_addr(wcd58);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f0f8(void){
    POP_HL;
    CALL(aFunction17f524);
    IF_C goto asm_17f114;
    LD_DE(0x3);
    ADD_HL_DE;
    LD_A_hli;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    CP_A(0x50);
    IF_Z goto asm_17f112;
    AND_A_A;
    RET;


asm_17f112:
    SCF;
    RET;


asm_17f114:
    PUSH_BC;
    LD_DE(wcd54);
    LD_BC(0x4);
    CALL(aCopyBytes);
    POP_BC;
    PUSH_HL;
    PUSH_BC;
    CALL(aFunction17f4f6);
    LD_A_addr(wcd54);
    LD_E_A;
    LD_A_addr(wcd55);
    LD_D_A;
    ADD_HL_DE;
    LD_DE(wc608);
    LD_A_addr(wcd56);
    LD_C_A;
    LD_B(0);
    CALL(aCopyBytes);
    LD_A(0x50);
    LD_de_A;
    POP_HL;
    LD_DE(wc608);
    CALL(aPlaceString);
    LD_A_C;
    LD_addr_A(wcd52);
    LD_A_B;
    LD_addr_A(wcd53);
    LD_A_addr(wcd57);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f154(void){
    POP_HL;
    CALL(aFunction17f524);
    IF_C goto asm_17f167;
    INC_HL;
    INC_HL;
    LD_E_L;
    LD_D_H;
    LD_A_de;
    CP_A(0x50);
    IF_Z goto asm_17f165;
    AND_A_A;
    RET;


asm_17f165:
    SCF;
    RET;


asm_17f167:
    PUSH_BC;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    POP_BC;
    PUSH_HL;
    PUSH_BC;
    CALL(aFunction17f4f6);
    ADD_HL_DE;
    LD_C_L;
    LD_B_H;
    POP_DE;
    FARCALL(aFunction11c08f);
    LD_C_L;
    LD_B_H;
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f181(void){
    POP_HL;
    CALL(aFunction17f524);
    IF_C goto asm_17f19d;
    LD_DE(0x2);
    ADD_HL_DE;
    LD_A_hli;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    CP_A(0x50);
    IF_Z goto asm_17f19b;
    AND_A_A;
    RET;


asm_17f19b:
    SCF;
    RET;


asm_17f19d:
    PUSH_BC;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_addr_A(wcd54);
    POP_BC;
    PUSH_HL;
    PUSH_BC;
    CALL(aFunction17f4f6);
    ADD_HL_DE;
    LD_A_hl;
    LD_C_A;
    LD_DE(wc608);
    FARCALL(aFunction48c63);
    POP_HL;
    LD_DE(wc608);
    CALL(aPlaceString);
    LD_A_C;
    LD_addr_A(wcd52);
    LD_A_B;
    LD_addr_A(wcd53);
    LD_A_addr(wcd54);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f1d0(void){
    POP_HL;
    CALL(aFunction17f524);
    IF_C goto asm_17f1ec;
    LD_DE(0x2);
    ADD_HL_DE;
    LD_A_hli;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    CP_A(0x50);
    IF_Z goto asm_17f1ea;
    AND_A_A;
    RET;


asm_17f1ea:
    SCF;
    RET;


asm_17f1ec:
    PUSH_BC;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_addr_A(wcd54);
    POP_BC;
    PUSH_HL;
    PUSH_BC;
    CALL(aFunction17f4f6);
    ADD_HL_DE;
    LD_A_hl;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetPokemonName);
    POP_HL;
    CALL(aPlaceString);
    LD_A_C;
    LD_addr_A(wcd52);
    LD_A_B;
    LD_addr_A(wcd53);
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    LD_A_addr(wcd54);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f220(void){
    POP_HL;
    CALL(aFunction17f524);
    IF_C goto asm_17f23c;
    LD_DE(0x2);
    ADD_HL_DE;
    LD_A_hli;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    CP_A(0x50);
    IF_Z goto asm_17f23a;
    AND_A_A;
    RET;


asm_17f23a:
    SCF;
    RET;


asm_17f23c:
    PUSH_BC;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_addr_A(wcd54);
    POP_BC;
    PUSH_HL;
    PUSH_BC;
    CALL(aFunction17f4f6);
    ADD_HL_DE;
    LD_A_hl;
    LD_E_A;
    LD_D(0);
    LD_HL(mFunction17f220_Genders);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    POP_HL;
    CALL(aPlaceString);
    LD_A_C;
    LD_addr_A(wcd52);
    LD_A_B;
    LD_addr_A(wcd53);
    LD_A_addr(wcd54);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;


Genders:
// dw .Boy, .Girl

Boy:
//     db "Boy@"

Girl:
//    db "Girl@"

    return Function17f27b();
}

void Function17f27b(void){
    POP_HL;
    CALL(aFunction17f524);
    IF_C goto asm_17f297;
    LD_DE(0x2);
    ADD_HL_DE;
    LD_A_hli;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    CP_A(0x50);
    IF_Z goto asm_17f295;
    AND_A_A;
    RET;


asm_17f295:
    SCF;
    RET;


asm_17f297:
    PUSH_BC;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_addr_A(wcd54);
    POP_BC;
    PUSH_HL;
    PUSH_BC;
    CALL(aFunction17f4f6);
    ADD_HL_DE;
    LD_A_hl;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    POP_HL;
    CALL(aPlaceString);
    LD_A_C;
    LD_addr_A(wcd52);
    LD_A_B;
    LD_addr_A(wcd53);
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    LD_A_addr(wcd54);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f2cb(void){
    POP_HL;
    PUSH_BC;
    LD_A_hli;
    LD_addr_A(wcd54);
    LD_A_hli;
    LD_addr_A(wcd55);
    LD_A_addr(wcd2e);
    INC_A;
    LD_addr_A(wcd56);
    POP_BC;
    PUSH_HL;
    LD_L_C;
    LD_H_B;
    PUSH_HL;
    LD_DE(wcd56);
    LD_B(0x1);
    LD_A_addr(wcd54);
    LD_C_A;
    CALL(aMobilePrintNum);
    LD_A_L;
    LD_addr_A(wcd52);
    LD_A_H;
    LD_addr_A(wcd53);
    POP_HL;
    LD_A_addr(wcd55);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;

}

void MobileScript_PlayerName(void){
    POP_HL;
    PUSH_BC;
    LD_A_hli;
    LD_addr_A(wcd54);
    POP_BC;
    PUSH_HL;
    PUSH_BC;
    LD_A(0x1);
    LDH_addr_A(rSVBK);
    LD_HL(wPlayerName);
    LD_DE(wc608);
    LD_BC(NAME_LENGTH_JAPANESE);
    CALL(aCopyBytes);
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    POP_HL;
    LD_DE(wc608);
    CALL(aPlaceString);
    LD_A_C;
    LD_addr_A(wcd52);
    LD_A_B;
    LD_addr_A(wcd53);
    LD_A_addr(wcd54);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;

}

void MobileScript_Prefecture(void){
    POP_HL;
    PUSH_BC;
    LD_A_hli;
    LD_addr_A(wcd55);
    AND_A(0xf);
    LD_addr_A(wcd54);
    POP_BC;
    PUSH_HL;
    LD_L_C;
    LD_H_B;
    PUSH_HL;
    LD_A_addr(wcd55);
    BIT_A(7);
    IF_NZ goto asm_17f355;
    LD_A(BANK(sCrystalData));
    CALL(aOpenSRAM);
    LD_A_addr(sCrystalData + 2);
    goto asm_17f35d;


asm_17f355:
    LD_A(BANK(s5_b2f3));
    CALL(aOpenSRAM);
    LD_A_addr(s5_b2f3);


asm_17f35d:
    LD_C_A;
    CALL(aCloseSRAM);
    LD_DE(wc608);
    FARCALL(aFunction48c63);
    POP_HL;
    LD_DE(wc608);
    CALL(aPlaceString);
    LD_A_C;
    LD_addr_A(wcd52);
    LD_A_B;
    LD_addr_A(wcd53);
    LD_A_addr(wcd54);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f382(void){
    POP_HL;
    PUSH_BC;
    LD_A_hli;
    LD_addr_A(wcd55);
    AND_A(0xf);
    LD_addr_A(wcd54);
    POP_BC;
    PUSH_HL;
    PUSH_BC;
    LD_L_C;
    LD_H_B;
    LD_A_addr(wcd55);
    BIT_A(7);
    IF_NZ goto asm_17f3a3;
    LD_A(BANK(sCrystalData));
    CALL(aOpenSRAM);
    LD_DE(sCrystalData + 3);
    goto asm_17f3ab;


asm_17f3a3:
    LD_A(BANK(s5_b2f4));
    CALL(aOpenSRAM);
    LD_DE(s5_b2f4);


asm_17f3ab:
    LD_A(PRINTNUM_LEADINGZEROS | 2);
    LD_B_A;
    LD_A(3);
    LD_C_A;
    CALL(aPrintNum);
    CALL(aCloseSRAM);
    LD_A_L;
    LD_addr_A(wcd52);
    LD_A_H;
    LD_addr_A(wcd53);
    POP_HL;
    LD_A_addr(wcd54);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f3c9(void){
    PUSH_BC;
    LD_HL(wcd36);
    LD_DE(wc708);
    LD_BC(12);
    CALL(aCopyBytes);
    POP_DE;
    LD_C(0x0);
    FARCALL(aFunction11c075);
    PUSH_HL;
    LD_HL(wc708);
    LD_DE(wcd36);
    LD_BC(12);
    CALL(aCopyBytes);
    POP_BC;
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f3f0(void){
    POP_HL;
    PUSH_HL;
    LD_A_hli;
    PUSH_AF;
    PUSH_BC;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_de;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_HL(wBGPals1);
    ADD_HL_DE;
    LD_E_L;
    LD_D_H;
    POP_HL;
    CALL(aPlaceString);
    POP_AF;
    LD_E_A;
    LD_D(0);
    POP_HL;
    ADD_HL_DE;
    ADD_HL_DE;
    INC_HL;
    INC_HL;
    INC_HL;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;
    SCF;
    RET;

}

void Function17f41d(void){
    POP_HL;
    LD_A_hli;
    PUSH_HL;
    PUSH_AF;
    LD_L_C;
    LD_H_B;
    LD_BC(-wTilemap + 0x10000);
    ADD_HL_BC;
    LD_DE(-SCREEN_WIDTH);
    LD_C(0x1);

asm_17f42c:
    LD_A_H;
    AND_A_A;
    IF_NZ goto asm_17f435;
    LD_A_L;
    CP_A(SCREEN_WIDTH);
    IF_C goto asm_17f439;


asm_17f435:
    ADD_HL_DE;
    INC_C;
    goto asm_17f42c;


asm_17f439:
    hlcoord(0, 0, wTilemap);
    LD_DE(SCREEN_WIDTH);
    LD_A_C;

asm_17f440:
    AND_A_A;
    IF_Z goto asm_17f447;
    ADD_HL_DE;
    DEC_A;
    goto asm_17f440;


asm_17f447:
    POP_AF;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f44f(void){
    POP_HL;
    CALL(aFunction17f524);
    IF_C goto asm_17f46d;
    LD_DE(0x5);
    ADD_HL_DE;
    LD_A_hli;
    INC_HL;
    INC_HL;
    LD_E_L;
    LD_D_H;
    LD_L_C;
    LD_H_B;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_de;
    CP_A(0x50);
    IF_Z goto asm_17f46b;
    AND_A_A;
    RET;


asm_17f46b:
    SCF;
    RET;


asm_17f46d:
    PUSH_BC;
    LD_DE(wcd54);
    LD_BC(0x8);
    CALL(aCopyBytes);
    POP_BC;
    PUSH_HL;
    PUSH_BC;
    LD_A_addr(wcd56);
    CP_A(0xc0);
    IF_C goto asm_17f488;
    LD_A_addr(wcd54);
    LDH_addr_A(rSVBK);
    goto asm_17f48e;


asm_17f488:
    LD_A_addr(wcd54);
    CALL(aOpenSRAM);


asm_17f48e:
    LD_A_addr(wcd55);
    LD_L_A;
    LD_A_addr(wcd56);
    LD_H_A;
    LD_DE(wc608);
    LD_A_addr(wcd57);
    LD_C_A;
    LD_B(0);
    CALL(aCopyBytes);
    LD_A_addr(wcd56);
    CP_A(0xc0);
    IF_C goto asm_17f4af;
    LD_A(0x4);
    LDH_addr_A(rSVBK);
    goto asm_17f4b7;


asm_17f4af:
    CALL(aCloseSRAM);
    LD_A(0x6);
    CALL(aOpenSRAM);


asm_17f4b7:
    LD_DE(wc608);
    POP_HL;
    PUSH_HL;
    LD_A_addr(wcd57);
    LD_B_A;
    LD_A_addr(wcd58);
    LD_C_A;
    CALL(aMobilePrintNum);
    LD_A_L;
    LD_addr_A(wcd52);
    LD_A_H;
    LD_addr_A(wcd53);
    LD_A_addr(wcd5a);
    AND_A_A;
    IF_Z goto asm_17f4ec;
    LD_C_A;
    LD_A_addr(wcd58);
    INC_A;
    LD_B_A;
    LD_E_L;
    LD_D_H;
    DEC_DE;

asm_17f4de:
    LD_A_C;
    CP_A_B;
    IF_Z goto asm_17f4e8;
    LD_A_de;
    DEC_DE;
    LD_hld_A;
    DEC_B;
    goto asm_17f4de;


asm_17f4e8:
    LD_A_addr(wcd5b);
    LD_hl_A;


asm_17f4ec:
    POP_HL;
    LD_A_addr(wcd59);
    CALL(aFunction17f50f);
    POP_DE;
    AND_A_A;
    RET;

}

void Function17f4f6(void){
    LD_A_addr(wcd6a);
    LD_L_A;
    LD_A_addr(wcd6b);
    LD_H_A;
    LD_A_addr(wcd47);
    LD_C_A;
    LD_A_addr(wBGMapPalBuffer);
    LD_B_A;
    LD_A_addr(wcd2e);

asm_17f509:
    AND_A_A;
    RET_Z ;
    DEC_A;
    ADD_HL_BC;
    goto asm_17f509;

    return Function17f50f();
}

void Function17f50f(void){
    AND_A_A;
    IF_Z goto asm_17f519;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_C_L;
    LD_B_H;
    RET;


asm_17f519:
    LD_A_addr(wcd52);
    LD_C_A;
    LD_L_A;
    LD_A_addr(wcd53);
    LD_B_A;
    LD_H_A;
    RET;

}

void Function17f524(void){
    PUSH_HL;
    PUSH_BC;
    PUSH_DE;
    LD_A_addr(wcd42);
    DEC_A;
    LD_B_A;
    LD_A_addr(wcd2e);
    CP_A_B;
    IF_Z goto asm_17f53a;
    LD_HL(wcd68);
    CP_A_hl;

asm_17f536:
    POP_DE;
    POP_BC;
    POP_HL;
    RET;


asm_17f53a:
    SCF;
    goto asm_17f536;

    return BattleTowerMobileError();
}

void BattleTowerMobileError(void){
    CALL(aFadeToMenu);
    XOR_A_A;
    LD_addr_A(wc303);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x1);
    LDH_addr_A(rSVBK);

    CALL(aDisplayMobileError);

    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aExitAllMenus);
    RET;

}

void DisplayMobileError(void){

loop:
    CALL(aJoyTextDelay);
    CALL(aDisplayMobileError_RunJumptable);
    LD_A_addr(wc303);
    BIT_A(7);
    IF_NZ goto quit;
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    goto loop;


quit:
    CALL(aDisplayMobileError_deinit);
    RET;


deinit:
    LD_A_addr(wMobileErrorCodeBuffer);
    CP_A(0x22);
    IF_Z goto asm_17f597;
    CP_A(0x31);
    IF_Z goto asm_17f58a;
    CP_A(0x33);
    RET_NZ ;
    LD_A_addr(wMobileErrorCodeBuffer + 1);
    CP_A(0x1);
    RET_NZ ;
    LD_A_addr(wMobileErrorCodeBuffer + 2);
    CP_A(0x2);
    RET_NZ ;
    goto asm_17f5a1;


asm_17f58a:
    LD_A_addr(wMobileErrorCodeBuffer + 1);
    CP_A(0x3);
    RET_NZ ;
    LD_A_addr(wMobileErrorCodeBuffer + 2);
    AND_A_A;
    RET_NZ ;
    goto asm_17f5a1;


asm_17f597:
    LD_A_addr(wMobileErrorCodeBuffer + 1);
    AND_A_A;
    RET_NZ ;
    LD_A_addr(wMobileErrorCodeBuffer + 2);
    AND_A_A;
    RET_NZ ;


asm_17f5a1:
    LD_A(BANK(sMobileLoginPassword));
    CALL(aOpenSRAM);
    XOR_A_A;
    LD_addr_A(sMobileLoginPassword);
    CALL(aCloseSRAM);
    RET;


RunJumptable:
    //jumptable ['.Jumptable', 'wc303']


Jumptable:
    //dw ['Function17f5c3'];
    //dw ['Function17ff23'];
    //dw ['Function17f5d2'];

    return Function17f5c3();
}

void Function17f5c3(void){
    CALL(aFunction17f5e4);
    FARCALL(aFinishExitMenu);
    LD_A(0x1);
    LD_addr_A(wc303);
    RET;

}

void Function17f5d2(void){
    CALL(aFunction17f5e4);
    FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    CALL(aSetPalettes);
    LD_A(0x1);
    LD_addr_A(wc303);
    RET;

}

void Function17f5e4(void){
    LD_A(0x8);
    LD_addr_A(wMusicFade);
    LD_DE(MUSIC_NONE);
    LD_A_E;
    LD_addr_A(wMusicFadeID);
    LD_A_D;
    LD_addr_A(wMusicFadeID + 1);
    LD_A(0x7f);
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    LD_A(0x6);
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    hlcoord(2, 1, wTilemap);
    LD_B(0x1);
    LD_C(0xe);
    CALL(aFunction3eea);
    hlcoord(1, 4, wTilemap);
    LD_B(0xc);
    LD_C(0x10);
    CALL(aFunction3eea);
    hlcoord(3, 2, wTilemap);
    LD_DE(mMobileCommunicationErrorText);
    CALL(aPlaceString);
    CALL(aFunction17ff3c);
    IF_NC goto asm_17f632;
    hlcoord(11, 2, wTilemap);
    CALL(aFunction17f6b7);


asm_17f632:
    LD_A_addr(wMobileErrorCodeBuffer);
    CP_A(0xd0);
    IF_NC goto asm_17f684;
    CP_A(0x10);
    IF_C goto asm_17f679;
    SUB_A(0x10);
    CP_A(0x24);
    IF_NC goto asm_17f679;
    LD_E_A;
    LD_D(0);
    LD_HL(mMobileErrorCodeTable);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_addr(wMobileErrorCodeBuffer + 1);
    LD_E_A;
    LD_A_addr(wMobileErrorCodeBuffer + 2);
    LD_D_A;
    LD_A_hli;
    LD_C_A;
    LD_A_hl;
    LD_H_A;
    LD_L_C;
    LD_A_hli;
    AND_A_A;
    IF_Z goto asm_17f679;
    LD_C_A;

asm_17f65d:
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    CP_A(0xff);
    IF_NZ goto asm_17f667;
    CP_A_B;
    IF_Z goto asm_17f66e;


asm_17f667:
    XOR_A_D;
    IF_NZ goto asm_17f674;
    LD_A_B;
    XOR_A_E;
    IF_NZ goto asm_17f674;


asm_17f66e:
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    goto asm_17f67d;


asm_17f674:
    INC_HL;
    INC_HL;
    DEC_C;
    IF_NZ goto asm_17f65d;


asm_17f679:
    LD_A(0xd9);
    goto asm_17f684;


asm_17f67d:
    hlcoord(2, 6, wTilemap);
    CALL(aPlaceString);
    RET;


asm_17f684:
    SUB_A(0xd0);
    LD_E_A;
    LD_D(0);
    LD_HL(mTable_17f699);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    hlcoord(2, 6, wTilemap);
    CALL(aPlaceString);
    RET;

}

void Table_17f699(void){
    //dw ['MobileErrorCode_101_000_Text'];
    //dw ['MobileErrorCode_101_001_Text'];
    //dw ['MobileErrorCode_101_002_Text'];
    //dw ['MobileErrorCode_101_003_Text'];
    //dw ['MobileErrorCode_101_004_Text'];
    //dw ['MobileErrorCode_101_005_Text'];
    //dw ['MobileErrorCode_101_006_Text'];
    //dw ['MobileErrorCode_101_007_Text'];
    //dw ['MobileErrorCode_101_008_Text'];
    //dw ['MobileErrorCode_101_009_Text'];
    //dw ['MobileErrorCode_101_009_Text'];

    return Palette_17f6af();
}

void Palette_17f6af(void){
//  //  unreferenced
    //rgb ['5', '5', '16']
    //rgb ['8', '19', '28']
    //rgb ['0', '0', '0']
    //rgb ['31', '31', '31']

    return Function17f6b7();
}

void Function17f6b7(void){
    LD_A_addr(wMobileErrorCodeBuffer);
    CALL(aFunction17f6b7_bcd_two_digits);
    INC_HL;
    LD_A_addr(wMobileErrorCodeBuffer + 2);
    AND_A(0xf);
    CALL(aFunction17f6b7_bcd_digit);
    LD_A_addr(wMobileErrorCodeBuffer + 1);
    CALL(aFunction17f6b7_bcd_two_digits);
    RET;


bcd_two_digits:
    LD_C_A;
    AND_A(0xf0);
    SWAP_A;
    CALL(aFunction17f6b7_bcd_digit);
    LD_A_C;
    AND_A(0xf);


bcd_digit:
    ADD_A(0xf6);
    LD_hli_A;
    RET;

}

void MobileCommunicationErrorText(void){
    //db ['"つうしんエラー\u3000\u3000\u3000ー@"'];

    return String_17f6e8();
}

void String_17f6e8(void){
//  //  unreferenced
    //db ['"みていぎ<NO>エラーです"'];
    //next ['"プログラム<WO>"']
    //next ['"かくにん\u3000してください"']
    //db ['"@"'];

    return MobileErrorCodeTable();
}

void MobileErrorCodeTable(void){
    //dw ['MobileErrorCodes_10'];
    //dw ['MobileErrorCodes_11'];
    //dw ['MobileErrorCodes_12'];
    //dw ['MobileErrorCodes_13'];
    //dw ['MobileErrorCodes_14'];
    //dw ['MobileErrorCodes_15'];
    //dw ['MobileErrorCodes_16'];
    //dw ['MobileErrorCodes_17'];
    //dw ['MobileErrorCodes_20'];
    //dw ['MobileErrorCodes_20'];
    //dw ['MobileErrorCodes_20'];
    //dw ['MobileErrorCodes_20'];
    //dw ['MobileErrorCodes_20'];
    //dw ['MobileErrorCodes_20'];
    //dw ['MobileErrorCodes_20'];
    //dw ['MobileErrorCodes_20'];
    //dw ['MobileErrorCodes_20'];
    //dw ['MobileErrorCodes_21'];
    //dw ['MobileErrorCodes_22'];
    //dw ['MobileErrorCodes_23'];
    //dw ['MobileErrorCodes_24'];
    //dw ['MobileErrorCodes_25'];
    //dw ['MobileErrorCodes_26'];
    //dw ['MobileErrorCodes_30'];
    //dw ['MobileErrorCodes_30'];
    //dw ['MobileErrorCodes_30'];
    //dw ['MobileErrorCodes_30'];
    //dw ['MobileErrorCodes_30'];
    //dw ['MobileErrorCodes_30'];
    //dw ['MobileErrorCodes_30'];
    //dw ['MobileErrorCodes_30'];
    //dw ['MobileErrorCodes_30'];
    //dw ['MobileErrorCodes_30'];
    //dw ['MobileErrorCodes_31'];
    //dw ['MobileErrorCodes_32'];
    //dw ['MobileErrorCodes_33'];

    return MobileErrorCodes_10();
}

void MobileErrorCodes_10(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_10_000_Text'];

    return MobileErrorCodes_11();
}

void MobileErrorCodes_11(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_11_000_Text'];

    return MobileErrorCodes_12();
}

void MobileErrorCodes_12(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_12_000_Text'];

    return MobileErrorCodes_13();
}

void MobileErrorCodes_13(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_13_000_Text'];

    return MobileErrorCodes_14();
}

void MobileErrorCodes_14(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_14_000_Text'];

    return MobileErrorCodes_15();
}

void MobileErrorCodes_15(void){
//db 4
    //dw ['0x000', 'MobileErrorCode_15_000_Text'];
    //dw ['0x001', 'MobileErrorCode_15_001_Text'];
    //dw ['0x002', 'MobileErrorCode_15_002_Text'];
    //dw ['0x003', 'MobileErrorCode_15_003_Text'];

    return MobileErrorCodes_16();
}

void MobileErrorCodes_16(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_CommuncationErrorText'];

    return MobileErrorCodes_17();
}

void MobileErrorCodes_17(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_CommuncationErrorText'];

    return MobileErrorCodes_20();
}

void MobileErrorCodes_20(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_CommuncationErrorText'];

    return MobileErrorCodes_21();
}

void MobileErrorCodes_21(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_CommuncationErrorText'];

    return MobileErrorCodes_22();
}

void MobileErrorCodes_22(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_22_000_Text'];

    return MobileErrorCodes_23();
}

void MobileErrorCodes_23(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_23_000_Text'];

    return MobileErrorCodes_24();
}

void MobileErrorCodes_24(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_ServerConnectionFailedText'];

    return MobileErrorCodes_25();
}

void MobileErrorCodes_25(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_25_000_Text'];

    return MobileErrorCodes_26();
}

void MobileErrorCodes_26(void){
//db 1
    //dw ['0x000', 'MobileErrorCode_26_000_Text'];

    return MobileErrorCodes_30();
}

void MobileErrorCodes_30(void){
//db 17
    //dw ['0x000', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x221', 'MobileErrorCode_ServerConnectionFailedText'];
    //dw ['0x421', 'MobileErrorCode_ServerConnectionFailedText'];
    //dw ['0x450', 'MobileErrorCode_30_450_Text'];
    //dw ['0x451', 'MobileErrorCode_ServerConnectionFailedText'];
    //dw ['0x452', 'MobileErrorCode_ServerConnectionFailedText'];
    //dw ['0x500', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x501', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x502', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x503', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x504', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x550', 'MobileErrorCode_30_550_Text'];
    //dw ['0x551', 'MobileErrorCode_30_551_Text'];
    //dw ['0x552', 'MobileErrorCode_ServerConnectionFailedText'];
    //dw ['0x553', 'MobileErrorCode_30_553_Text'];
    //dw ['0x554', 'MobileErrorCode_ServerConnectionFailedText'];
    //dw ['-1', 'MobileErrorCode_ServerConnectionFailedText'];

    return MobileErrorCodes_31();
}

void MobileErrorCodes_31(void){
//db 5
    //dw ['0x000', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x002', 'MobileErrorCode_31_002_Text'];
    //dw ['0x003', 'MobileErrorCode_31_003_Text'];
    //dw ['0x004', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['-1', 'MobileErrorCode_ServerConnectionFailedText'];

    return MobileErrorCodes_32();
}

void MobileErrorCodes_32(void){
//db 17
    //dw ['0x000', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x301', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x302', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x400', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x401', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x403', 'MobileErrorCode_32_403_Text'];
    //dw ['0x404', 'MobileErrorCode_32_404_Text'];
    //dw ['0x405', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x406', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x407', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x408', 'MobileErrorCode_32_408_Text'];
    //dw ['0x500', 'MobileErrorCode_ServerErrorText'];
    //dw ['0x501', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x502', 'MobileErrorCode_ServerErrorText'];
    //dw ['0x503', 'MobileErrorCode_32_503_Text'];
    //dw ['0x504', 'MobileErrorCode_ServerErrorText'];
    //dw ['-1', 'MobileErrorCode_ServerErrorText'];

    return MobileErrorCodes_33();
}

void MobileErrorCodes_33(void){
//db 19
    //dw ['0x101', 'MobileErrorCode_33_101_Text'];
    //dw ['0x102', 'MobileErrorCode_33_102_Text'];
    //dw ['0x103', 'MobileErrorCode_33_103_Text'];
    //dw ['0x104', 'MobileErrorCode_33_104_Text'];
    //dw ['0x105', 'MobileErrorCode_33_105_Text'];
    //dw ['0x106', 'MobileErrorCode_33_106_Text'];
    //dw ['0x201', 'MobileErrorCode_33_201_Text'];
    //dw ['0x202', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x203', 'MobileErrorCode_33_203_Text'];
    //dw ['0x204', 'MobileErrorCode_CommuncationErrorText'];
    //dw ['0x205', 'MobileErrorCode_ServerErrorText'];
    //dw ['0x206', 'MobileErrorCode_33_206_Text'];
    //dw ['0x299', 'MobileErrorCode_33_299_Text'];
    //dw ['0x301', 'MobileErrorCode_ServerErrorText'];
    //dw ['0x401', 'MobileErrorCode_ServerErrorText'];
    //dw ['0x402', 'MobileErrorCode_ServerErrorText'];
    //dw ['0x403', 'MobileErrorCode_ServerErrorText'];
    //dw ['0x404', 'MobileErrorCode_ServerErrorText'];
    //dw ['-1', 'MobileErrorCode_ServerErrorText'];

    return MobileErrorCode_10_000_Text();
}

void MobileErrorCode_10_000_Text(void){
//  The Mobile Adapter is not properly plugged in.
//  Ensure you have taken a good look at and properly followed the instructions.
    //db ['"モバイルアダプタが\u3000ただしく"'];
    //next ['"さしこまれていません"']
    //next ['"とりあつかいせつめいしょを"']
    //next ['"ごらんのうえ\u3000しっかりと"']
    //next ['"さしこんで\u3000ください"']
    //db ['"@"'];

    return MobileErrorCode_11_000_Text();
}

void MobileErrorCode_11_000_Text(void){
    return MobileErrorCode_13_000_Text();
}

void MobileErrorCode_13_000_Text(void){
//  Could not connect because either the phone cannot make the call, or the telephone line is busy.
//  Please wait for a while and call again.
    //db ['"でんわが\u3000うまく\u3000かけられないか"'];
    //next ['"でんわかいせんが\u3000こんでいるので"']
    //next ['"つうしん\u3000できません"']
    //next ['"しばらく\u3000まって"']
    //next ['"かけなおして\u3000ください"']
    //db ['"@"'];

    return MobileErrorCode_12_000_Text();
}

void MobileErrorCode_12_000_Text(void){
//  As the telephone line is busy, the phone was not able to gather enough information (?)
//  Please wait for a while and call again.
    //db ['"でんわかいせんが\u3000こんでいるため"'];
    //next ['"でんわが\u3000かけられません"']
    //next ['"しばらく\u3000まって"']
    //next ['"かけなおして\u3000ください"']
    //db ['"@"'];

    return MobileErrorCode_15_000_Text();
}

void MobileErrorCode_15_000_Text(void){
    return MobileErrorCode_15_001_Text();
}

void MobileErrorCode_15_001_Text(void){
    return MobileErrorCode_15_002_Text();
}

void MobileErrorCode_15_002_Text(void){
    return MobileErrorCode_15_003_Text();
}

void MobileErrorCode_15_003_Text(void){
//  There is an error with the Mobile Adapter.
//  Please wait for a little while before calling again.
//  If the problem persists, please contact the Mobile Support Center.
    //db ['"モバイルアダプタの\u3000エラーです"'];
    //next ['"しばらく\u3000まって"']
    //next ['"かけなおして\u3000ください"']
    //next ['"なおらない\u3000ときは"']
    //next ['"モバイルサポートセンターへ"']
    //next ['"おといあわせください"']
    //db ['"@"'];

    return MobileErrorCode_CommuncationErrorText();
}

void MobileErrorCode_CommuncationErrorText(void){
//  Communication error.
//  Please wait a moment, and then try again.
//  If the issue persists, please contact the Mobile Support Center.
    //db ['"つうしんエラーです"'];
    //next ['"しばらく\u3000まって"']
    //next ['"かけなおして\u3000ください"']
    //next ['"なおらない\u3000ときは"']
    //next ['"モバイルサポートセンターへ"']
    //next ['"おといあわせください"']
    //db ['"@"'];

    return MobileErrorCode_22_000_Text();
}

void MobileErrorCode_22_000_Text(void){
//  There is a mistake either with the login password, or the login ID.
//  Please confirm the password, wait for a while, and try again.
    //db ['"ログインパスワードか"'];
    //next ['"ログイン\u3000アイディーに"']
    //next ['"まちがいがあります"']
    //next ['"パスワードを\u3000かくにんして"']
    //next ['"しばらく\u3000まって"']
    //next ['"かけなおして\u3000ください"']
    //db ['"@"'];

    return MobileErrorCode_23_000_Text();
}

void MobileErrorCode_23_000_Text(void){
//  The call was ended.
//  Please see the instruction manual, wait a moment, and try again.
    //db ['"でんわが\u3000きれました"'];
    //next ['"とりあつかいせつめいしょを"']
    //next ['"ごらんのうえ"']
    //next ['"しばらく\u3000まって"']
    //next ['"かけなおして\u3000ください"']
    //db ['"@"'];

    return MobileErrorCode_ServerErrorText();
}

void MobileErrorCode_ServerErrorText(void){
//  There was a communication error with the mobile center.
//  Please wait a moment and then try again.
    //db ['"モバイルセンターの"'];
    //next ['"つうしんエラーです"']
    //next ['"しばらくまって"']
    //next ['"かけなおして\u3000ください"']
    //db ['"@"'];

    return MobileErrorCode_14_000_Text();
}

void MobileErrorCode_14_000_Text(void){
    return MobileErrorCode_25_000_Text();
}

void MobileErrorCode_25_000_Text(void){
//  The Mobile Adapter's details have expired and the information is not correct.
//  Please use the Mobile Trainer to repeat the initial registration (process).
    //db ['"モバイルアダプタに"'];
    //next ['"とうろくされた\u3000じょうほうが"']
    //next ['"ただしく\u3000ありません"']
    //next ['"モバイルトレーナーで"']
    //next ['"しょきとうろくを\u3000してください"']
    //db ['"@"'];

    return MobileErrorCode_32_503_Text();
}

void MobileErrorCode_32_503_Text(void){
//  Could not connect because the Mobile Center is busy.
//  Please wait a moment and try again.
//  For details, please see the instruction manual.
    //db ['"モバイルセンターが"'];
    //next ['"こんでいて\u3000つながりません"']
    //next ['"しばらくまって"']
    //next ['"かけなおして\u3000ください"']
    //next ['"くわしくは\u3000とりあつかい"']
    //next ['"せつめいしょを\u3000ごらんください"']
    //db ['"@"'];

    return MobileErrorCode_30_450_Text();
}

void MobileErrorCode_30_450_Text(void){
    return MobileErrorCode_30_550_Text();
}

void MobileErrorCode_30_550_Text(void){
    return MobileErrorCode_30_551_Text();
}

void MobileErrorCode_30_551_Text(void){
    return MobileErrorCode_30_553_Text();
}

void MobileErrorCode_30_553_Text(void){
//  There is a mistake with the email address of the addressee.
//  Please replace with a / the correct email address.
    //db ['"あてさき\u3000メールアドレスに"'];
    //next ['"まちがいがあります"']
    //next ['"ただしい\u3000メールアドレスを"']
    //next ['"いれなおしてください"']
    //db ['"@"'];

    return MobileErrorCode_31_002_Text();
}

void MobileErrorCode_31_002_Text(void){
//  There is a mistake with the email address.
//  Please see the instruction manual, and use the Mobile Trainer to repeat the initial registration (process).
    //db ['"メールアドレスに"'];
    //next ['"まちがいが\u3000あります"']
    //next ['"とりあつかいせつめいしょを"']
    //next ['"ごらんのうえ"']
    //next ['"モバイルトレーナーで"']
    //next ['"しょきとうろくを\u3000してください"']
    //db ['"@"'];

    return MobileErrorCode_31_003_Text();
}

void MobileErrorCode_31_003_Text(void){
    return MobileErrorCode_33_201_Text();
}

void MobileErrorCode_33_201_Text(void){
//  There is either an error with the login password, or an error with the Mobile Center.
//  Please confirm the password, wait a moment, and then try again.
    //db ['"ログインパスワードに"'];
    //next ['"まちがいが\u3000あるか"']
    //next ['"モバイルセンターの\u3000エラーです"']
    //next ['"パスワードを\u3000かくにんして"']
    //next ['"しばらく\u3000まって"']
    //next ['"かけなおして\u3000ください"']
    //db ['"@"'];

    return MobileErrorCode_32_403_Text();
}

void MobileErrorCode_32_403_Text(void){
    return MobileErrorCode_32_404_Text();
}

void MobileErrorCode_32_404_Text(void){
//  Cannot read data.
//  Please wait a moment, and then try again.
//  If the issue persists, please contact the Mobile Support Center.
    //db ['"データの\u3000よみこみが\u3000できません"'];
    //next ['"しばらくまって"']
    //next ['"かけなおして\u3000ください"']
    //next ['"なおらない\u3000ときは"']
    //next ['"モバイルサポートセンターへ"']
    //next ['"おといあわせください"']
    //db ['"@"'];

    return MobileErrorCode_26_000_Text();
}

void MobileErrorCode_26_000_Text(void){
    return MobileErrorCode_32_408_Text();
}

void MobileErrorCode_32_408_Text(void){
//  Out of time.
//  The call was ended.
//  Please try again.
//  For details, please see the instruction manual.
    //db ['"じかんぎれです"'];
    //next ['"でんわが\u3000きれました"']
    //next ['"でんわを\u3000かけなおしてください"']
    //next ['"くわしくは\u3000とりあつかい"']
    //next ['"せつめいしょを\u3000ごらんください"']
    //db ['"@"'];

    return MobileErrorCode_33_101_Text();
}

void MobileErrorCode_33_101_Text(void){
//  The service cannot be used if payments for usage fees are late.
//  For details, please see the instruction manual.
    //db ['"ごりよう\u3000りょうきんの\u3000"'];
    //next ['"おしはらいが\u3000おくれたばあいには"']
    //next ['"ごりようが\u3000できなくなります"']
    //next ['"くわしくは\u3000とりあつかい"']
    //next ['"せつめいしょを\u3000ごらんください"']
    //db ['"@"'];

    return MobileErrorCode_33_102_Text();
}

void MobileErrorCode_33_102_Text(void){
    return MobileErrorCode_33_299_Text();
}

void MobileErrorCode_33_299_Text(void){
//  Your access to this service has been restricted. Service cannot be used.
//  For details, please see the instruction manual.
    //db ['"おきゃくさまの\u3000ごつごうにより"'];
    //next ['"ごりようできません"']
    //next ['"くわしくは\u3000とりあつかい"']
    //next ['"せつめいしょを\u3000ごらんください"']
    //db ['"@"'];

    return MobileErrorCode_ServerConnectionFailedText();
}

void MobileErrorCode_ServerConnectionFailedText(void){
//  The telephone line is busy. Due to this error, the Mobile Center cannot communicate.
//  Please wait for a little while and call again.
    //db ['"でんわかいせんが\u3000こんでいるか"'];
    //next ['"モバイルセンターの\u3000エラーで"']
    //next ['"つうしんが\u3000できません"']
    //next ['"しばらく\u3000まって"']
    //next ['"かけなおして\u3000ください"']
    //db ['"@"'];

    return MobileErrorCode_33_103_Text();
}

void MobileErrorCode_33_103_Text(void){
//  Service cannot be used this month because usage fees have exceeded conditions.
//  For details, please see the instruction manual.
    //db ['"ごりよう\u3000りょうきんが"'];
    //next ['"じょうげんを\u3000こえているため"']
    //next ['"こんげつは\u3000ごりようできません"']
    //next ['"くわしくは\u3000とりあつかい"']
    //next ['"せつめいしょを\u3000ごらんください"']
    //db ['"@"'];

    return MobileErrorCode_33_106_Text();
}

void MobileErrorCode_33_106_Text(void){
//  Cannot communicate because the Mobile Center is currently undergoing maintenance.
//  Please wait a moment, then try again.
    //db ['"げんざい\u3000モバイルセンターの"'];
    //next ['"てんけんを\u3000しているので"']
    //next ['"つうしんが\u3000できません"']
    //next ['"しばらく\u3000まって"']
    //next ['"かけなおして\u3000ください"']
    //db ['"@"'];

    return MobileErrorCode_33_104_Text();
}

void MobileErrorCode_33_104_Text(void){
    return MobileErrorCode_33_105_Text();
}

void MobileErrorCode_33_105_Text(void){
    return MobileErrorCode_33_203_Text();
}

void MobileErrorCode_33_203_Text(void){
    return MobileErrorCode_33_206_Text();
}

void MobileErrorCode_33_206_Text(void){
    return MobileErrorCode_101_004_Text();
}

void MobileErrorCode_101_004_Text(void){
//  Cannot read data.
//  For details, please see the instruction manual.
    //db ['"データの\u3000よみこみが\u3000できません"'];
    //next ['"くわしくは\u3000とりあつかい"']
    //next ['"せつめいしょを\u3000ごらんください"']
    //db ['"@"'];

    return MobileErrorCode_101_006_Text();
}

void MobileErrorCode_101_006_Text(void){
//  Call ended because more than 3 minutes elapsed with no input.
    //db ['"３ぷん\u3000いじょう\u3000なにも"'];
    //next ['"にゅうりょく\u3000しなかったので"']
    //next ['"でんわが\u3000きれました"']
    //db ['"@"'];

    return MobileErrorCode_101_001_Text();
}

void MobileErrorCode_101_001_Text(void){
    return MobileErrorCode_101_002_Text();
}

void MobileErrorCode_101_002_Text(void){
//  Could not connect properly.
//  Please try again from the beginning (of the process).
    //db ['"つうしんが\u3000うまく"'];
    //next ['"できませんでした"']
    //next ['"もういちど\u3000はじめから"']
    //next ['"やりなおしてください"']
    //db ['"@"'];

    return MobileErrorCode_101_003_Text();
}

void MobileErrorCode_101_003_Text(void){
    return MobileErrorCode_101_008_Text();
}

void MobileErrorCode_101_008_Text(void){
    return MobileErrorCode_101_009_Text();
}

void MobileErrorCode_101_009_Text(void){
//  Cannot read data.
//  Please wait a moment, then try again.
//  If the issue persists, please contact the Mobile Support Center.
    //db ['"データの\u3000よみこみが\u3000できません"'];
    //next ['"しばらくまって"']
    //next ['"かけなおして\u3000ください"']
    //next ['"なおらない\u3000ときは"']
    //next ['"モバイルサポートセンターへ"']
    //next ['"おといあわせください"']
    //db ['"@"'];

    return MobileErrorCode_101_007_Text();
}

void MobileErrorCode_101_007_Text(void){
//  Call ended due to long waiting time.
    //db ['"まちじかんが\u3000ながいので"'];
    //next ['"でんわが\u3000きれました"']
    //db ['"@"'];

    return MobileErrorCode_101_005_Text();
}

void MobileErrorCode_101_005_Text(void){
//  (Your adapter's) type differs from the other user’s Mobile Adapter.
//  For details, please see the instruction manual.
    //db ['"あいての\u3000モバイルアダプタと"'];
    //next ['"タイプが\u3000ちがいます"']
    //next ['"くわしくは\u3000とりあつかい"']
    //next ['"せつめいしょを\u3000ごらんください"']
    //db ['"@"'];

    return String_17fe9a();
}

void String_17fe9a(void){
//  //  unreferenced
//  Cannot send your save data because Pokémon News is being updated.
//  Please send your save data after loading new Pokémon News.
    //db ['"ポケモンニュースが"'];
    //next ['"あたらしくなっているので"']
    //next ['"レポートを\u3000おくれません"']
    //next ['"あたらしい\u3000ポケモンニュースの"']
    //next ['"よみこみを\u3000さきに\u3000してください"']
    //db ['"@"'];

    return MobileErrorCode_101_000_Text();
}

void MobileErrorCode_101_000_Text(void){
//  Either bad communication status, or the other user called was the incorrect user.
//  Please confirm and try again.
    //db ['"つうしんの\u3000じょうきょうが"'];
    //next ['"よくないか\u3000かけるあいてが"']
    //next ['"まちがっています"']
    //next ['"もういちど\u3000かくにんをして"']
    //next ['"でんわを\u3000かけなおして\u3000ください"']
    //db ['"@"'];

    return Function17ff23();
}

void Function17ff23(void){
    LDH_A_addr(hJoyPressed);
    AND_A_A;
    RET_Z ;
    LD_A(0x8);
    LD_addr_A(wMusicFade);
    LD_A_addr(wMapMusic);
    LD_addr_A(wMusicFadeID);
    XOR_A_A;
    LD_addr_A(wMusicFadeID + 1);
    LD_HL(wc303);
    SET_hl(7);
    RET;

}

void Function17ff3c(void){
    NOP;
    LD_A_addr(wMobileErrorCodeBuffer);
    CP_A(0xd0);
    RET_C ;
    hlcoord(10, 2, wTilemap);
    LD_DE(mString_17ff68);
    CALL(aPlaceString);
    LD_A_addr(wMobileErrorCodeBuffer);
    PUSH_AF;
    SUB_A(0xd0);
    INC_A;
    LD_addr_A(wMobileErrorCodeBuffer);
    hlcoord(14, 2, wTilemap);
    LD_DE(wMobileErrorCodeBuffer);
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 3);
    CALL(aPrintNum);
    POP_AF;
    LD_addr_A(wMobileErrorCodeBuffer);
    AND_A_A;
    RET;

}

void String_17ff68(void){
    //db ['"１０１@"'];

}
