#include "../constants.h"
#include "mobile_5f.h"
#include "mobile_12.h"
#include "mobile_41.h"
#include "mobile_46.h"
#include "fixed_words.h"
#include "../charmap.h"
#include "../home/audio.h"
#include "../home/menu.h"
#include "../home/lcd.h"
#include "../home/copy.h"
#include "../home/tilemap.h"
#include "../home/text.h"
#include "../home/clear_sprites.h"
#include "../home/delay.h"
#include "../home/joypad.h"
#include "../home/map.h"
#include "../home/mobile.h"
#include "../home/print_text.h"
#include "../home/sram.h"
#include "../home/fade.h"
#include "../home/pokedex_flags.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/color.h"
#include "../engine/gfx/load_pics.h"
#include "../engine/gfx/place_graphic.h"
#include "../engine/gfx/pic_animation.h"
#include "../engine/menus/save.h"
#include "../engine/pokedex/unown_dex.h"

uint8_t* sMobileCrashCheckPointer;
uint8_t* gMobile_wcd20_wcd21;
uint8_t* gMobile_wcd49_wcd4a;
uint8_t* gMobile_wcd4b_wcd4c;
uint8_t* gMobile_wcd4d_wcd4e;
uint8_t* gMobile_wcd52_wcd53;

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
        if(ch == CHAR_NULL) continue;
        // CP_A(0x5f + 1);
        // IF_NC goto next;
        if(ch >= CHAR_DEXEND + 1) continue;
        // CP_A(0x4e);
        // IF_Z goto next;
        // CP_A(0x50);
        // IF_Z goto next;
        if(ch == CHAR_NEXT || ch == CHAR_TERM) continue;

        // CP_A(0x05);
        // IF_C goto end;
        if(ch < CHAR_JP_05) return true;
        // CP_A(0x14);
        // IF_C goto next;
        else if(ch < CHAR_PLAY_G) continue;
        // CP_A(0x18 + 1);
        // IF_C goto end;
        else if(ch < CHAR_JP_18 + 1) return true;
        // CP_A(0x1d);
        // IF_C goto next;
        else if(ch < CHAR_JP_NI) continue;
        // CP_A(0x25 + 1);
        // IF_C goto end;
        else if(ch < CHAR_LM_SLB + 1) return true;
        // CP_A(0x35);
        // IF_C goto next;
        else if(ch < CHAR_ROUTE) continue;
        // CP_A(0x39 + 1);
        // IF_C goto end;
        else if(ch < CHAR_GREEN + 1) return true;
        // CP_A(0x3f);
        // IF_C goto next;
        else if(ch < CHAR_ENEMY) continue;
        // CP_A(0x3f + 1);
        // IF_C goto end;
        else if(ch < CHAR_ENEMY + 1) return true;
        // CP_A(0x49);
        // IF_C goto next;
        else if(ch < CHAR_MOM) continue;
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

// Mobile_SetReceiveMonPokedexFlags
void Function17d1f1(void){
    // LD_A_addr(wCurPartySpecies);
    // DEC_A;
    // CALL(aSetSeenAndCaughtMon);
    SetSeenAndCaughtMon_Conv(wram->wCurPartySpecies - 1);

    // LD_A_addr(wCurPartySpecies);
    // CP_A(UNOWN);
    // IF_NZ goto asm_17d223;
    if(wram->wCurPartySpecies == UNOWN) {
        // LD_HL(wPartyMon1DVs);
        // LD_A_addr(wPartyCount);
        // DEC_A;
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aAddNTimes);
        // PREDEF(pGetUnownLetter);
        unown_letter_t letter = GetUnownLetter_Conv(wram->wPartyMon[wram->wPartyCount - 1].mon.DVs);
        // CALLFAR(aUpdateUnownDex);
        UpdateUnownDex_Conv(letter);
        // LD_A_addr(wFirstUnownSeen);
        // AND_A_A;
        // IF_NZ goto asm_17d223;
        if(wram->wFirstUnownSeen == 0) {
            // LD_A_addr(wUnownLetter);
            // LD_addr_A(wFirstUnownSeen);
            wram->wFirstUnownSeen = letter;
        }
    }

// asm_17d223:
    // RET;
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
            "RECEIVE NEWS", //db ['"ニュース¯よみこむ@"'];
            "VIEW NEWS", //db ['"ニュース¯みる@"'];
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

// Mobile_DownloadNewsSpecial
void Function17d2b6(void){
    // CALL(aFunction17d2c0);
    Function17d2c0();
    // FARCALL(aFunction1181da);
    Function1181da();
    // RET;
}

// Mobile_ResetMenuJumptableIndexes
void Function17d2c0(void){
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // LD_addr_A(wcf64);
    wram->wcf64 = 0x0;
    // LD_addr_A(wcf65);
    wram->wcf65 = 0x0;
    // LD_addr_A(wcf66);
    wram->wcf66 = 0x0;
    // RET;
}

// Mobile_ViewDownloadedNewsSpecial
//  - wScriptVar = 0x0 -> OK
//  - wScriptVar = 0x1 -> No news downloaded
//  - wScriptVar = 0x2 -> News is corrupt
void Function17d2ce(void){
    // LD_A(BANK(s5_aa72));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_aa72));
    // LD_A_addr(s5_aa72);
    uint8_t aa72 = gb_read(s5_aa72);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // AND_A_A;
    // IF_NZ goto asm_17d2e2;
    if(aa72 == 0) {
        // LD_A(0x1);
        // LD_addr_A(wScriptVar);
        wram->wScriptVar = 0x1;
        // RET;
        return;
    }

// asm_17d2e2:
    // CALL(aFunction17d314);
    // RET_C ;
    if(Function17d314())
        return;
    // CALL(aSpeechTextbox);
    SpeechTextbox_Conv2();
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    uint8_t svbk = gb_read(rSVBK);
    // LD_A(0x4);
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, 0x4);
    // CALL(aFunction17d370);
    Function17d370();
    // CALL(aFunction17d45a);
    Function17d45a();
    // POP_AF;
    // LDH_addr_A(rSVBK);
    gb_write(rSVBK, svbk);
    // LD_DE(MUSIC_MOBILE_CENTER);
    // LD_A_E;
    // LD_addr_A(wMapMusic);
    wram->wMapMusic = MUSIC_MOBILE_CENTER;
    // LD_addr_A(wMusicFadeID);
    // LD_A_D;
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_MOBILE_CENTER;
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_MOBILE_CENTER);
    // CALL(aReturnToMapFromSubmenu);
    ReturnToMapFromSubmenu();
    // CALL(aCloseSubmenu);
    CloseSubmenu_Conv();
    // RET;
}

// MobileNews_CheckDownloadedNewsValidity
// Returns true if the downloaded news is corrupt or invalid.
bool Function17d314(void){
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_b1b1));
    // LD_A_addr(0xb1b1);
    uint8_t b1b1 = gb_read(s5_b1b1);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // CP_A(0x21);
    // IF_NC goto asm_17d354;
    if(b1b1 < 0x21) {
        // LD_A(0x6);
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(as6_a000));
        // LD_L(0x0);
        // LD_H_L;
    // Calculate checksum?
        uint16_t hl = 0;
        // LD_DE(0xa006);
        uint8_t* de = GBToRAMAddr(s6_a000 + 0x6);
        // LD_A_addr(0xa004);
        // LD_C_A;
        // LD_A_addr(0xa005);
        // LD_B_A;
        uint16_t bc = (gb_read(s6_a000 + 0x4) | (gb_read(s6_a000 + 0x5) << 8));

        do {
        // asm_17d336:
            // PUSH_BC;
            // LD_A_de;
            // INC_DE;
            // LD_C_A;
            // LD_B(0);
            // ADD_HL_BC;
            hl += *de;
            de++;
            // POP_BC;
            // DEC_BC;
            // LD_A_B;
            // OR_A_C;
            // IF_NZ goto asm_17d336;
        } while(--bc != 0);
    // Verify checksum
        // LD_A_addr(0xa002);
        // CP_A_L;
        // IF_NZ goto asm_17d354;
        // LD_A_addr(0xa003);
        // CP_A_H;
        // IF_NZ goto asm_17d354;
        uint16_t checksum = (gb_read(s6_a000 + 0x2) | (gb_read(s6_a000 + 0x3) << 8));
        if(hl == checksum) {
            // CALL(aCloseSRAM);
            CloseSRAM_Conv();
            // AND_A_A;
            // RET;
            return false;
        }
    }

// asm_17d354:
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_aa73));
    // XOR_A_A;
    // LD_HL(0xaa73);
    // LD_BC(0xc);
    // CALL(aByteFill);
    ByteFill(GBToRAMAddr(s5_aa73), 0xc, 0x0);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A(0x2);
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0x2;
    // SCF;
    // RET;
    return true;
}

// MobileNews_LoadGFX
void Function17d370(void){
    // XOR_A_A;
    // LD_addr_A(wcd77);
    wram->wcd77 = 0x0;
    // LD_addr_A(wMobileCrashCheckPointer);
    // LD_addr_A(wMobileCrashCheckPointer + 1);
    sMobileCrashCheckPointer = NULL;
    // DEC_A;
    // LD_addr_A(wcd6c);
    wram->wcd6c = 0xff;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0xee);
    // LD_DE(wc608);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc608, vram->vTiles0 + LEN_2BPP_TILE * 0xee, 1 * LEN_2BPP_TILE);
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_HL(mPokemonNewsGFX);
    // LD_DE(vTiles1);
    // LD_BC(0x48 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles4, PokemonNewsGFX, 0, 0x48);
    // XOR_A_A;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x7f);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aByteFill);
    ByteFill(vram->vTiles5 + LEN_2BPP_TILE * 0x7f, 1 * LEN_2BPP_TILE, 0x0);
    // LD_HL(wc608);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0xee);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    CopyBytes(vram->vTiles3 + LEN_2BPP_TILE * 0xee, wram->wc608, 1 * LEN_2BPP_TILE);
    // XOR_A_A;
    // LDH_addr_A(rVBK);
    // LD_HL(mPostalMarkGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x60);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x60, PostalMarkGFX, 0, 1);
    // CALL(aEnableLCD);
    EnableLCD();
    // CALL(aFunction17d60b);
    Function17d60b();
    // LD_A(0x0);
    // LD_addr_A(wBGMapBuffer);
    // LD_A(0xd0);
    // LD_addr_A(wcd21);
    gMobile_wcd20_wcd21 = wram->wram4;
    // LD_A(0x6);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as6_a000));
    // LD_HL(0xa006);
    // LD_DE(wBGPals1);
    // LD_BC(0x1000);
    // CALL(aCopyBytes);
    CopyBytes(wram->wram4, GBToRAMAddr(s6_a000 + 6), 0x1000);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void Function17d3f6(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();

    return Function17d405();
}

void Function17d405(void){
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_HL(vTiles0 + LEN_2BPP_TILE * 0xee);
    // LD_DE(wc608);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc608, vram->vTiles0 + LEN_2BPP_TILE * 0xee, 1 * LEN_2BPP_TILE);
    // LD_A(0x1);
    // LDH_addr_A(rVBK);
    // LD_HL(mPokemonNewsGFX);
    // LD_DE(vTiles1);
    // LD_BC(0x48 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles4, PokemonNewsGFX, 0, 0x48);
    // XOR_A_A;
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x7f);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aByteFill);
    ByteFill(vram->vTiles2 + LEN_2BPP_TILE * 0x7f, 1 * LEN_2BPP_TILE, 0x0);
    // LD_HL(wc608);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0xee);
    // LD_BC(1 * LEN_2BPP_TILE);
    // CALL(aCopyBytes);
    CopyBytes(vram->vTiles3 + LEN_2BPP_TILE * 0xee, wram->wc608, 1 * LEN_2BPP_TILE);
    // XOR_A_A;
    // LDH_addr_A(rVBK);
    // CALL(aEnableLCD);
    EnableLCD();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mPokemonNewsPalettes);
    // LD_DE(wBGPals1);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    LoadPaletteAssetColorsToBuffer(wram->wBGPals1, 8 * PALETTE_SIZE, PokemonNewsPalettes, 0, 8 * NUM_PAL_COLORS);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

// MobileNews_ReadNewsLoop
void Function17d45a(void){
    while(1) {
    // asm_17d45a:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LD_A_addr(wcd77);
        // BIT_A(7);
        // IF_NZ goto asm_17d46f;
        if(bit_test(wram->wcd77, 7))
            break;
        // CALL(aFunction17d474);
        Function17d474();
        // FARCALL(aReloadMapPart);
        ReloadMapPart_Conv();
        // goto asm_17d45a;
    }

// asm_17d46f:
    // XOR_A_A;
    // LD_addr_A(wScriptVar);
    wram->wScriptVar = 0;
    // RET;
}

// MobileNews_ReadNewsJumptable
void Function17d474(void){
    //jumptable ['Jumptable_17d483', 'wcd77']

    switch(wram->wcd77) {
        case 0: return Function17d48d();
        case 1: return Function17d5be();
        case 2: return Function17d5c4();
        case 3: return Function17d6fd();
        case 4: return Function17e427();
    }
}

void Function17d48d(void){
    // LD_HL(mPokemonNewsPalettes);
    // LD_DE(wc608);
    // LD_BC(0x40);
    // CALL(aCopyBytes);
    LoadPaletteAssetToBuffer(wram->wc608, 0x40, PokemonNewsPalettes, 0x40 / NUM_PAL_COLORS);
    // LD_HL(mPokemonNewsTileAttrmap);
    asset_s map = LoadAsset(PokemonNewsTileAttrmap);
    uint8_t* hl = map.ptr;
    // decoord(0, 0, wTilemap);
    tile_t* de = coord(0, 0, wram->wTilemap);
    // bccoord(0, 0, wAttrmap);
    uint8_t* bc = coord(0, 0, wram->wAttrmap);
    // LD_A(0x12);
    uint8_t a = SCREEN_HEIGHT;

    do {
    // asm_17d4a4:
        // PUSH_AF;
        // LD_A(0x14);
        uint8_t a2 = SCREEN_WIDTH;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // asm_17d4a8:
            // PUSH_AF;
            // LD_A_hli;
            uint8_t a3 = *(hl2++);
            // CP_A(0x7f);
            // IF_Z goto asm_17d4b0;
            if(a3 != 0x7f) {
                // ADD_A(0x80);
                a3 += 0x80;
            }

        // asm_17d4b0:
            // LD_de_A;
            *(de++) = a3;
            // INC_DE;
            // LD_A_hli;
            // LD_bc_A;
            // INC_BC;
            *(bc++) = *(hl2++);
            // POP_AF;
            // DEC_A;
            // IF_NZ goto asm_17d4a8;
        } while(--a2 != 0);
        // POP_HL;
        // PUSH_BC;
        // LD_BC(0x40);
        // ADD_HL_BC;
        hl += BG_MAP_WIDTH * 2;
        // POP_BC;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_17d4a4;
    } while(--a != 0);
    FreeAsset(map);
    // LD_A_addr(wBGMapBuffer);
    // LD_L_A;
    // LD_A_addr(wcd21);
    // LD_H_A;
    hl = gMobile_wcd20_wcd21;
    // LD_A_hli;
    // LD_E_A;
    uint8_t e = *(hl++);
    // LD_A_addr(wcd6c);
    // CP_A_E;
    // IF_Z goto asm_17d4e0;
    if(wram->wcd6c != e) {
        // LD_A_E;
        // LD_addr_A(wcd6c);
        wram->wcd6c = e;
        // LD_addr_A(wMapMusic);
        wram->wMapMusic = e;
        // LD_D(0x0);
        // CALL(aPlayMusic2);
        PlayMusic2(e);
    }

// asm_17d4e0:
    // LD_A_hli;
    a = *(hl++);
    // LD_DE(wc608);
    uint8_t* de2 = wram->wc608;
    // LD_C(0x8);
    uint8_t c = 0x8;

    do {
    // asm_17d4e6:
        // SRL_A;
        // IF_NC goto asm_17d4f6;
        if((a & 1) == 0) {
            a >>= 1;
        // asm_17d4f6:
            // PUSH_AF;
            // LD_A_E;
            // ADD_A(0x8);
            // LD_E_A;
            de2 += 0x8;
            // POP_AF;
        }
        else {
            a >>= 1;
            // LD_B(0x8);
            uint8_t b = 0x8;
            // PUSH_AF;

            do {
            // asm_17d4ed:
                // LD_A_hli;
                // LD_de_A;
                // INC_DE;
                *(de2++) = *(hl++);
                // DEC_B;
                // IF_NZ goto asm_17d4ed;
            } while(--b != 0);
            // POP_AF;
            // goto asm_17d4fc;
        }

    // asm_17d4fc:
        // DEC_C;
        // IF_NZ goto asm_17d4e6;
    } while(--c != 0);
    // PUSH_HL;
    // CALL(aFunction17d5f6);
    Function17d5f6();
    // POP_HL;
    // LD_A_hli;
    a = *(hl++);
    // AND_A_A;
    // IF_Z goto asm_17d539;
    if(a != 0) {
        do {
        // asm_17d508:
            // PUSH_AF;
            // LD_A_hli;
            // LD_addr_A(wcd4f);
            wram->wcd4f = *(hl++);
            // LD_A_hli;
            // LD_addr_A(wcd50);
            wram->wcd50 = *(hl++);
            // LD_A_hli;
            // LD_addr_A(wcd51);
            wram->wcd51 = *(hl++);
            // LD_A_hli;
            // LD_addr_A(wcd52);
            wram->wcd52 = *(hl++);
            // LD_A_hli;
            uint8_t a2 = *(hl++);
            // SLA_A;
            // SLA_A;
            // SLA_A;
            // ADD_A(0x98);
            // LD_addr_A(wcd53);
            wram->wcd53 = (a2 << 3) + 0x98;
            // LD_DE(wcd4f);
            // CALL(aFunction17e613);
            Function17e613(&wram->wcd4f);
            // LD_A_hli;
            // LD_addr_A(wcd53);
            wram->wcd53 = *(hl++);
            // LD_DE(wcd4f);
            // CALL(aFunction17e691);
            Function17e691(&wram->wcd4f);
            // POP_AF;
            // DEC_A;
            // IF_NZ goto asm_17d508;
        } while(--a != 0);
    }

// asm_17d539:
    // LD_A_hli;
    a = *(hl++);

    do {
    // asm_17d53a:
        // PUSH_AF;
        // LD_A_hli;
        // LD_C_A;
        // LD_A_hli;
        // LD_B_A;
        uint16_t bc = hl[0] | (hl[1] << 8);
        hl += 2;
        // PUSH_HL;
        // POP_DE;
        // hlcoord(0, 0, wTilemap);
        // ADD_HL_BC;
        // CALL(aPlaceString);
        struct TextPrintState st = {.de = hl, .hl = coord(0, 0, wram->wTilemap) + bc, .bc = coord(0, 0, wram->wTilemap)};
        PlaceString_Conv(&st, st.hl);
        // PUSH_DE;
        // POP_HL;
        // INC_HL;
        hl = st.de + 1;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_17d53a;
    } while(--a != 0);
    // LD_DE(wCreditsTimer);
    // LD_BC(0xc);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wcd22, hl, 0xc);
    hl += 0xc;
    // XOR_A_A;
    // LD_addr_A(wcd2e);
    // LD_addr_A(wcd2f);
    wram->wcd2e = 0x0;
    wram->wcd2f = 0x0;
    // INC_A;
    // LD_addr_A(wcd30);
    // LD_addr_A(wcd31);
    wram->wcd30 = 1;
    wram->wcd31 = 1;
    // LD_DE(wcd32);
    // LD_BC(0x10);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wcd32, hl, 0x10);
    hl += 0x10;
    // LD_A_hli;
    // LD_addr_A(wcd42);
    wram->wcd42 = *(hl++);
    // LD_A_hli;
    // LD_addr_A(wcd43);
    wram->wcd43[0] = *(hl++);
    // LD_A_hli;
    // LD_addr_A(wMobileInactivityTimerMinutes);
    wram->wMobileInactivityTimerMinutes = *(hl++);
    // LD_A_hli;
    // LD_addr_A(wMobileInactivityTimerSeconds);
    wram->wMobileInactivityTimerSeconds = *(hl++);
    // LD_A_hli;
    // LD_addr_A(wMobileInactivityTimerFrames);
    wram->wMobileInactivityTimerFrames = *(hl++);
    // LD_A_hli;
    a = *(hl++);
    // AND_A_A;
    // IF_Z goto asm_17d58a;
    if(a != 0) {
        // CALL(aFunction17d6a1);
        Function17d6a1();
    }

// asm_17d58a:
    // LD_A_L;
    // LD_addr_A(wcd49);
    // LD_A_H;
    // LD_addr_A(wcd4a);
    gMobile_wcd49_wcd4a = hl;
    // LD_A_addr(wcd42);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    hl += wram->wcd42 * 2;
    // LD_A_L;
    // LD_addr_A(wcd4b);
    // LD_A_H;
    // LD_addr_A(wcd4c);
    gMobile_wcd4b_wcd4c = hl;
    // ADD_HL_BC;
    // ADD_HL_BC;
    hl += wram->wcd42 * 2;
    // LD_A_L;
    // LD_addr_A(wcd4d);
    // LD_A_H;
    // LD_addr_A(wcd4e);
    gMobile_wcd4d_wcd4e = hl;
    // CALL(aFunction17e451);
    Function17e451();
    // CALL(aFunction17e55b);
    Function17e55b();
    // CALL(aFunction17e5af);
    Function17e5af();
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // JP(mFunction17e438);
    return Function17e438();
}

void Function17d5be(void){
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aFunction17e438);
    Function17e438();

    return Function17d5c4();
}

void Function17d5c4(void){
    // LDH_A_addr(hJoyPressed);
    // AND_A_A;
    // RET_Z ;
    if(hram->hJoyPressed == 0)
        return;
    // LD_C(0);
    uint8_t c = 0;
    // LD_B_C;
    // LD_HL(wcd32);
    uint8_t a = hram->hJoyPressed;

    while((a & 1) == 0) {
    // loop:
        // SRL_A;
        a >>= 1;
        // IF_C goto got_button;
        // INC_C;
        // INC_C;
        c++;
        // goto loop;
    }

// got_button:
    // ADD_HL_BC;
    uint8_t* hl = &wram->wcd32 + (c * 2);
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    uint16_t bc = hl[0] | (hl[1] << 8);
    hl += 2;
    // AND_A_C;
    // CP_A(0xff);
    // RET_Z ;
    if(bc == 0xffff)
        return;
    // LD_A_addr(wcd20);
    // LD_L_A;
    // LD_A_addr(wcd21);
    // LD_H_A;
    // ADD_HL_BC;
    // LD_A_L;
    // LD_addr_A(wMobileCrashCheckPointer);
    // LD_A_H;
    // LD_addr_A(wMobileCrashCheckPointer + 1);
    sMobileCrashCheckPointer = gMobile_wcd20_wcd21 + bc;
    // LD_A(0x3);
    // LD_addr_A(wcd77);
    wram->wcd77 = 0x3;
    // RET;
}

void Function17d5f6(void){
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(wc608);
    // LD_DE(wBGPals1);
    // LD_BC(8 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals1, wram->wc608, 8 * PALETTE_SIZE);
    // LD_A(0x4);
    // LDH_addr_A(rSVBK);
    // RET;
}

void Function17d60b(void){
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_b1d3));
    // LD_HL(0xb1d3);
    // LD_DE(wc608);
    // LD_BC(0x20);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc608, GBToRAMAddr(s5_b1d3), 0x20);
    // LD_A_addr(0xb1b1);
    // LD_C_A;
    uint8_t c = gb_read(s5_b1b1);
    // LD_A_addr(0xb1b2);
    // LD_B_A;
    uint8_t b = gb_read(s5_b1b2);
    // LD_A_addr(0xb1b3);
    // LD_L_A;
    // LD_A_addr(0xb1b4);
    // LD_H_A;
    uint16_t hl = gb_read16(s5_b1b3);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A(0x6);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as6_a000));
    // LD_DE(wc708);
    uint8_t* de = &wram->wc708;
    // LD_A_C;
    // AND_A_A;
    // IF_Z goto asm_17d684;
    if(c != 0) {
        while(1) {
        // asm_17d63b:
            // PUSH_BC;
            // LD_A_L;
            // LD_de_A;
            *(de++) = LOW(hl);
            // INC_DE;
            // LD_A_H;
            // LD_de_A;
            *(de++) = HIGH(hl);
            // INC_DE;
            // LD_BC(0xa);
            // ADD_HL_BC;
            // POP_BC;
            hl += 0xa;
            // LD_A_hli;
            // LD_addr_A(wcd4a);
            wram->wcd4a = gb_read(hl++);
            // LD_A_hli;
            // LD_addr_A(wcd49);
            wram->wcd49 = gb_read(hl++);
            // PUSH_HL;
            // PUSH_DE;
            // LD_HL(wc608);
            // LD_E_B;
            // LD_D(0x0);
            // ADD_HL_DE;
            // LD_A_hli;
            // LD_addr_A(wcd4b);
            wram->wcd4b = wram->wc608[b + 0];
            // LD_A_hl;
            // LD_addr_A(wcd4c);
            wram->wcd4c = wram->wc608[b + 1];
            // POP_DE;
            // POP_HL;
            // INC_B;
            // INC_B;
            b += 2;
            // DEC_C;
            // DEC_C;
            c -= 2;
            // IF_Z goto asm_17d684;
            if(c == 0)
                break;
            // PUSH_BC;
            // PUSH_DE;
            // LD_A_addr(wcd49);
            // LD_C_A;
            // LD_A_addr(wcd4a);
            // LD_B_A;
            uint16_t bc = wram->wcd49 | (wram->wcd4a << 8);
            // LD_A_addr(wcd4b);
            // LD_E_A;
            // LD_A_addr(wcd4c);
            // LD_D_A;
            uint16_t de2 = wram->wcd4b | (wram->wcd4c << 8);

            // do {
            // asm_17d67a:
                // ADD_HL_DE;
                // DEC_BC;
                // LD_A_C;
                // OR_A_B;
                // IF_NZ goto asm_17d67a;
            // } while(--bc != 0);
            hl += de2 * bc;
            // POP_DE;
            // POP_BC;
            // goto asm_17d63b;
        }
    }

// asm_17d684:
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_b1b1));
    // LD_HL(wc708);
    // LD_DE(0xb1b3);
    // LD_A_addr(0xb1b1);
    // LD_C_A;
    // LD_A_addr(0xb1b2);
    // LD_B_A;
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_b1b3), &wram->wc708, gb_read16(s5_b1b1));
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void Function17d6a1(void){
    // PUSH_HL;
    // LD_A_addr(wcd6e);
    uint8_t a = wram->wcd6e;
    // LD_C_A;
    // LD_B(0);
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_b1d3));
    // LD_HL(0xb1d3);
    // ADD_HL_BC;
    // ADD_HL_BC;
    uint8_t* hl = GBToRAMAddr(s5_b1d3 + (a * 2));
    // LD_A_hli;
    // LD_addr_A(wcd47);
    wram->wcd47 = *(hl++);
    // LD_A_hl;
    // LD_addr_A(wBGMapPalBuffer);
    wram->wcd20 = *hl;
    // LD_HL(0xb1b3);
    // ADD_HL_BC;
    // ADD_HL_BC;
    hl = GBToRAMAddr(s5_b1b3 + (a * 2));
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hl;
    // LD_H_A;
    // LD_L_C;
    uint16_t hl2 = hl[0] | (hl[1] << 8);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A(0x6);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as6_a000));
    // LD_A_L;
    // LD_addr_A(wcd5e);
    // LD_A_H;
    // LD_addr_A(wcd5f);
    wram->wcd5e = LOW(hl2);
    wram->wcd5f = HIGH(hl2);
    // LD_DE(wcd60);
    // LD_BC(0x4);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wcd60, GBToRAMAddr(hl2), 0x4);
    // INC_HL;
    // INC_HL;
    hl2 += 0x6;
    // LD_DE(wcd64);
    // LD_BC(0x4);
    // CALL(aCopyBytes);
    CopyBytes(wram->wcd64, GBToRAMAddr(hl2), 0x4);
    hl2 += 0x4;
    // LD_A_hli;
    // LD_addr_A(wcd69);
    wram->wcd69[0] = gb_read(hl2++);
    // LD_A_hli;
    // LD_addr_A(wcd68);
    wram->wcd68 = gb_read(hl2++);
    // LD_A_L;
    // LD_addr_A(wcd6a);
    wram->wcd6a = LOW(hl2);
    // LD_A_H;
    // LD_addr_A(wcd6b);
    wram->wcd6b = HIGH(hl2);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // POP_HL;
    // RET;
}

void Function17d6fd(void){
    // LD_A_addr(wcd77);
    // BIT_A(7);
    // JR_NZ (masm_17d721);
    if(bit_test(wram->wcd77, 7))
        return asm_17d721();
    // LD_A_addr(wMobileCrashCheckPointer);
    // LD_L_A;
    // LD_A_addr(wMobileCrashCheckPointer + 1);
    // LD_H_A;
    // LD_A_hl;
    // CP_A(0xff);
    // JR_Z (masm_17d721);
    if(*sMobileCrashCheckPointer == 0xff)
        return asm_17d721();

    return Function17d711(*sMobileCrashCheckPointer);
}

typedef void (*Jumptable17d72a_t)(void);
enum {
    NEWS_COMMAND_NOP,
    NEWS_COMMAND_LOAD_SCREEN,
    NEWS_COMMAND_PLAY_MUSIC,
    NEWS_COMMAND_PLAY_SFX,
    NEWS_COMMAND_PLAY_CRY,
    NEWS_COMMAND_05,
    NEWS_COMMAND_06,
    NEWS_COMMAND_07,
    NEWS_COMMAND_08,
    NEWS_COMMAND_09,
    NEWS_COMMAND_POKE_PIC,
    NEWS_COMMAND_TRAINER_PIC,
    NEWS_COMMAND_COPYVALRAM,
    NEWS_COMMAND_0D,
    NEWS_COMMAND_MENU_UP,
    NEWS_COMMAND_MENU_DOWN,
    NEWS_COMMAND_MENU_LEFT,
    NEWS_COMMAND_MENU_RIGHT,
    NEWS_COMMAND_12,
    NEWS_COMMAND_13,
    NEWS_COMMAND_14,
    NEWS_COMMAND_ROTATE_PALS_LEFT,
    NEWS_COMMAND_ROTATE_PALS_RIGHT,
    NEWS_COMMAND_CALL_SUB,
    NEWS_COMMAND_PLACE_TEXT,
    NEWS_COMMAND_CLEAR_TEXT,
    NEWS_COMMAND_1A,
    NEWS_COMMAND_EXIT = 48,
};
// TODO:  Finish news command table.
static const Jumptable17d72a_t Jumptable17d72a[] = {
    [NEWS_COMMAND_NOP]          = Function17d78c,
    [NEWS_COMMAND_LOAD_SCREEN]  = Function17d78d,
    [NEWS_COMMAND_PLAY_MUSIC]   = Function17d7b4,
    [NEWS_COMMAND_PLAY_SFX]     = Function17d7c2,
    [NEWS_COMMAND_PLAY_CRY]     = Function17d7d3,
    [NEWS_COMMAND_05] = Function17d7e5,
    [NEWS_COMMAND_06] = Function17d818,
    [NEWS_COMMAND_07] = Function17d833,
    // [8] = Function17d85d,
    // [9] = Function17d902,
    [NEWS_COMMAND_POKE_PIC] = Function17d93a,
    [NEWS_COMMAND_TRAINER_PIC] = Function17d98b,
    [NEWS_COMMAND_COPYVALRAM] = Function17d9e3,
    // [13] = Function17da31,
    [NEWS_COMMAND_MENU_UP] = Function17da9c,
    [NEWS_COMMAND_MENU_DOWN] = Function17dadc,
    [NEWS_COMMAND_MENU_LEFT] = Function17db2d,
    [NEWS_COMMAND_MENU_RIGHT] = Function17db56,
    // [18] = Function17db77,
    // [19] = Function17dbe9,
    // [20] = Function17dc1f,
    [NEWS_COMMAND_ROTATE_PALS_LEFT] = Function17dc9f,
    [NEWS_COMMAND_ROTATE_PALS_RIGHT] = Function17dca9,
    [23] = Function17dccf,
    [NEWS_COMMAND_PLACE_TEXT] = Function17dd13,
    [NEWS_COMMAND_CLEAR_TEXT] = Function17dd30,
    [26] = Function17dd49,
    // [27] = Function17ddcd,
    // [28] = Function17de32,
    // [29] = Function17de91,
    // [30] = Function17ded9,
    // [31] = Function17e0fd,
    // [32] = Function17e133,
    // [33] = Function17e165,
    [34] = Function17e1a1,
    [35] = Function17e254,
    [36] = Function17e261,
    [37] = Function17e270,
    [38] = Function17e27f,
    [39] = Function17e293,
    [40] = Function17e2a7,
    [41] = IncCrashCheckPointer_SaveGameData,
    [42] = IncCrashCheckPointer_SaveAfterLinkTrade,
    [43] = IncCrashCheckPointer_SaveBox,
    [44] = IncCrashCheckPointer_SaveChecksum,
    [45] = IncCrashCheckPointer_SaveTrainerRankingsChecksum,
    [46] = Function17e3e0,
    [47] = Function17e3f0,
    [NEWS_COMMAND_EXIT] = Function17e409,
};

// Mobile_RunNewsCommand
void Function17d711(uint8_t a){
// crash_loop:
    // CP_A(0x31);
    // IF_NC goto crash_loop;
    if(a >= 0x31)
        a = 0x30;  
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mJumptable17d72a);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // JP_hl;
    printf("RunNewsCommand(%d)\n", a);
    return Jumptable17d72a[a]();
}

void asm_17d721(void){
    // CALL(aFunction17e5af);
    Function17e5af();
    // LD_A(0x2);
    // LD_addr_A(wcd77);
    wram->wcd77 = 0x2;
    // RET;

}

void Function17d78c(void){
    // RET;

}

// NewsCommand_LoadScreen
void Function17d78d(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    uint16_t bc = hl[0] | (hl[1] << 8);
    // CALL(aHlToCrashCheckPointer);
    hl = HlToCrashCheckPointer(hl + 2);
    // LD_A(0x6);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as6_a000));
    // LD_HL(0xa006);
    // ADD_HL_BC;
    // LD_DE(wBGPals1);
    // LD_BC(0x1000);
    // CALL(aCopyBytes);
    CopyBytes(wram->wram4, GBToRAMAddr(s6_a000 + 0x6 + bc), 0x1000);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // XOR_A_A;
    // LD_addr_A(wcd77);
    wram->wcd77 = 0;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // RET;
}

// NewsCommand_PlayMusic
void Function17d7b4(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_E_A;
    // LD_D(0);
    uint16_t track = hl[0];
    // CALL(aPlayMusic2);
    PlayMusic2(track);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 1);
    // RET;
}

// NewsCommand_PlaySFX
void Function17d7c2(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_E_A;
    // LD_D(0);
    uint16_t sfx = hl[0];
    // CALL(aPlaySFX);
    PlaySFX(sfx);
    // CALL(aWaitSFX);
    WaitSFX();
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 1);
    // RET;

}

// NewsCommand_PlayCry
void Function17d7d3(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // DEC_A;
    // LD_E_A;
    // LD_D(0);
    uint16_t cry = hl[0] - 1;
    // CALL(aPlayCry);
    PlayCry(cry);
    // CALL(aWaitSFX);
    WaitSFX();
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 1);
    // RET;
}

// NewsCommand_DrawMenu?
void Function17d7e5(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_addr_A(wcd4f);
    wram->wcd4f = hl[0];
    // LD_A_hli;
    // LD_addr_A(wcd50);
    wram->wcd50 = hl[1];
    // LD_A_hli;
    // LD_addr_A(wcd51);
    wram->wcd51 = hl[2];
    // LD_A_hli;
    // LD_addr_A(wcd52);
    wram->wcd52 = hl[3];
    // LD_A_hli;
    // SLA_A;
    // SLA_A;
    // SLA_A;
    // ADD_A(0x98);
    // LD_addr_A(wcd53);
    wram->wcd53 = (hl[4] << 3) + 0x98;
    // LD_DE(wcd4f);
    // CALL(aFunction17e613);
    Function17e613(&wram->wcd4f);
    // LD_A_hli;
    // LD_addr_A(wcd53);
    wram->wcd53 = hl[5];
    // LD_DE(wcd4f);
    // CALL(aFunction17e691);
    Function17e691(&wram->wcd4f);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 6);
    // RET;
}

// NewsCommand_DrawString?
void Function17d818(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    uint16_t bc = hl[0] | (hl[1] << 8);
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t de = hl[2] | (hl[3] << 8);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 4);
    // CALL(aFunction17e447);
    uint8_t* str = Function17e447(de);
    // LD_E_L;
    // LD_D_H;
    // hlcoord(0, 0, wTilemap);
    // ADD_HL_BC;
    // CALL(aPlaceString);
    PlaceStringSimple(str, coord(0, 0, wram->wTilemap) + bc);
    // RET;
}

// NewsCommand_DrawEZChatMessage?
void Function17d833(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t de = hl[0] | (hl[1] << 8);
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    uint16_t bc = hl[2] | (hl[3] << 8);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 4);
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aFunction17e32b);
    Function17e32b();
    // POP_BC;
    // POP_DE;
    // CALL(aFunction17e43d);
    // LD_C_L;
    // LD_B_H;
    // hlcoord(0, 0, wTilemap);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    // FARCALL(aFunction11c08f);
    Function11c08f(coord(0, 0, wram->wTilemap) + de, Function17e43d(bc));
    // CALL(aFunction17e349);
    Function17e349();
    // RET;
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

// NewsCommand_DrawAnimatedPokemonPic
void Function17d93a(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_DE(wc708);
    // LD_BC(0x5);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wc708, hl, 0x5);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 5);
    // CALL(aFunction17e32b);
    Function17e32b();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wc70c);
    // CALL(aFunction17e6de);
    Function17e6de(wram->wc70c);
    // LD_A_addr(wc70a);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wc70a;
    // LD_A_addr(wc70c);
    // LD_E_A;
    // FARCALL(aLoadMonPaletteAsNthBGPal);
    LoadMonPaletteAsNthBGPal(wram->wc70c);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LD_A_addr(wc708);
    // LD_L_A;
    // LD_A_addr(wc709);
    // LD_H_A;
    uint16_t de = wram->wc708 | (wram->wc709 << 8);
    // LD_A_addr(wc70b);
    // LD_C_A;
    uint8_t c = wram->wc70b;
    // decoord(0, 0, wTilemap);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    // FARCALL(aHOF_AnimateFrontpic);
    HOF_AnimateFrontpic_Conv(coord(0, 0, wram->wTilemap) + de, c);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aFunction17e349);
    Function17e349();
    // RET;
}

// NewsCommand_DrawTrainerPic
void Function17d98b(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_DE(wc708);
    // LD_BC(0x4);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wc708, hl, 0x4);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 4);
    // CALL(aFunction17e32b);
    Function17e32b();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wc70b);
    // CALL(aFunction17e6de);
    Function17e6de(wram->wc70b);
    // LD_A_addr(wc70a);
    // LD_addr_A(wTrainerClass);
    wram->wTrainerClass = wram->wc70a;
    // LD_A_addr(wc70b);
    // LD_E_A;
    // FARCALL(aLoadTrainerClassPaletteAsNthBGPal);
    LoadTrainerClassPaletteAsNthBGPal(wram->wc70b);
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LD_A_addr(wc708);
    // LD_E_A;
    // LD_A_addr(wc709);
    // LD_D_A;
    // PUSH_DE;
    uint16_t de = wram->wc708 | (wram->wc709 << 8);
    // LD_DE(vTiles2);
    // FARCALL(aGetTrainerPic);
    GetTrainerPic_Conv(vram->vTiles2, wram->wTrainerClass);
    // POP_HL;
    // decoord(0, 0, wTilemap);
    // ADD_HL_DE;
    // LD_BC(0x707);
    // PREDEF(pPlaceGraphic);
    PlaceGraphicYStagger_Conv(coord(0, 0, wram->wTilemap) + de, 7, 7);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aFunction17e349);
    Function17e349();
    // RET;
}

void Function17d9e3(void){
    uint8_t svbk = gb_read(rSVBK);
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_DE(wc708);
    // LD_BC(0x7);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wc708, hl, 0x7);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 7);
    // LD_A_addr(wc70b);
    // PUSH_AF;
    uint8_t c70b = wram->wc70b;
    // CP_A(0xc0);
    // IF_C goto asm_17da01;
    // LD_A_addr(wc70c);
    // LDH_addr_A(rSVBK);
    // goto asm_17da07;
    if(c70b < 0xc0) {
    // asm_17da01:
        // LD_A_addr(wc70c);
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(wram->wc70c);
    }
    else {
        gb_write(rSVBK, wram->wc70c);
    }

// asm_17da07:
    // LD_A_addr(wc708);
    // LD_L_A;
    // LD_A_addr(wc709);
    // LD_H_A;
    // LD_A_addr(wc70a);
    // LD_E_A;
    // LD_A_addr(wc70b);
    // LD_D_A;
    // LD_A_addr(wc70d);
    // LD_C_A;
    // LD_A_addr(wc70e);
    // LD_B_A;
    // CALL(aCopyBytes);
    CopyBytes(
        GBToRAMAddr(wram->wc70a | (wram->wc70b << 8)), 
        GBToRAMAddr(wram->wc708 | (wram->wc709 << 8)), 
        wram->wc70d | (wram->wc70e << 8));
    // POP_AF;
    // CP_A(0xc0);
    // IF_C goto asm_17da2d;
    // LD_A(0x4);
    // LDH_addr_A(rSVBK);
    // goto asm_17da30;
    if(c70b < 0xc0) {
    // asm_17da2d:
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
    }

    gb_write(rSVBK, svbk);

// asm_17da30:
    // RET;
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

const uint8_t Unknown_17da8c[] = {
    // for(int x = 0; x < 8; x++){
    1 << 0,
    1 << 1,
    1 << 2,
    1 << 3,
    1 << 4,
    1 << 5,
    1 << 6,
    1 << 7,
    // }
};

const uint8_t Unknown_17da94[] = {
    // for(int x = 0; x < 8; x++){
    (uint8_t)~(1 << 0),
    (uint8_t)~(1 << 1),
    (uint8_t)~(1 << 2),
    (uint8_t)~(1 << 3),
    (uint8_t)~(1 << 4),
    (uint8_t)~(1 << 5),
    (uint8_t)~(1 << 6),
    (uint8_t)~(1 << 7),
    // }
};

void Function17da9c(void){
    // LD_A_addr(wcd31);
    // DEC_A;
    // IF_Z goto asm_17dabd;
    if(wram->wcd31 - 1 == 0) {
    // asm_17dabd:
        // LD_A_addr(wcd2f);
        // AND_A_A;
        // IF_Z goto asm_17daba;
        if(wram->wcd2f != 0) {
            // LD_HL(wcd24);
            // SUB_A_hl;
            // LD_addr_A(wcd2f);
            wram->wcd2f -= wram->wcd24;
            // LD_A_addr(wcd2e);
            // SUB_A_hl;
            // LD_addr_A(wcd2e);
            wram->wcd2e -= wram->wcd24;
            // CALL(aFunction17e451);
            Function17e451();
            // CALL(aFunction17e55b);
            Function17e55b();
            // CALL(aFunction17e5af);
            Function17e5af();
        }
        // goto asm_17daba;
    }
    else {
        // PUSH_AF;
        // CALL(aFunction17e566);
        Function17e566();
        // POP_AF;
        // LD_addr_A(wcd31);
        wram->wcd31--;
        // LD_HL(wcd24);
        // LD_A_addr(wcd2e);
        // SUB_A_hl;
        // LD_addr_A(wcd2e);
        wram->wcd2e -= wram->wcd24;
        // CALL(aFunction17e55b);
        Function17e55b();
        // CALL(aFunction17e5af);
        Function17e5af();
    }

// asm_17daba:
    // JP(mIncCrashCheckPointer);
    IncCrashCheckPointer();
}

void Function17dadc(void){
    // LD_A_addr(wcd2e);
    // LD_HL(wcd24);
    // ADD_A_hl;
    // LD_HL(wcd42);
    // CP_A_hl;
    // IF_Z goto asm_17db0e;
    // IF_NC goto asm_17db0e;
    if(wram->wcd2e + wram->wcd24 < wram->wcd42) {
        // LD_HL(wcd31);
        // LD_A_addr(wcd2b);
        // CP_A_hl;
        // IF_Z goto asm_17db11;
        if(wram->wcd2b == wram->wcd31) {
        // asm_17db11:
            // LD_HL(wcd24);
            // LD_A_addr(wcd2f);
            // ADD_A_hl;
            // LD_addr_A(wcd2f);
            wram->wcd2f += wram->wcd24;
            // LD_A_addr(wcd2e);
            // ADD_A_hl;
            // LD_addr_A(wcd2e);
            wram->wcd2e += wram->wcd24;
            // CALL(aFunction17e451);
            Function17e451();
            // CALL(aFunction17e55b);
            Function17e55b();
            // CALL(aFunction17e5af);
            Function17e5af();
            // goto asm_17db0e;
        }
        else {
            // CALL(aFunction17e566);
            Function17e566();
            // LD_A_addr(wcd31);
            // INC_A;
            // LD_addr_A(wcd31);
            wram->wcd31++;
            // LD_HL(wcd24);
            // LD_A_addr(wcd2e);
            // ADD_A_hl;
            // LD_addr_A(wcd2e);
            wram->wcd2e += wram->wcd24;
            // CALL(aFunction17e55b);
            Function17e55b();
            // CALL(aFunction17e5af);
            Function17e5af();
        }
    }

// asm_17db0e:
    // JP(mIncCrashCheckPointer);
    IncCrashCheckPointer();
}

// NewsCommand_MoveCursorLeft?
void Function17db2d(void){
    // LD_A_addr(wcd30);
    // LD_HL(wcd24);
    // CP_A_hl;
    // IF_Z goto asm_17db53;
    if(wram->wcd30 != wram->wcd24) {
        // LD_HL(wcd42);
        // LD_A_addr(wcd2e);
        // INC_A;
        // CP_A_hl;
        // IF_Z goto asm_17db53;
        if(wram->wcd2e + 1 != wram->wcd42) {
            // LD_addr_A(wcd2e);
            wram->wcd2e++;
            // CALL(aFunction17e566);
            Function17e566();
            // LD_A_addr(wcd30);
            // INC_A;
            // LD_addr_A(wcd30);
            wram->wcd30++;
            // CALL(aFunction17e55b);
            Function17e55b();
            // CALL(aFunction17e5af);
            Function17e5af();
        }
    }

// asm_17db53:
    // JP(mIncCrashCheckPointer);
    IncCrashCheckPointer();
}

// NewsCommand_MoveCursorRight?
void Function17db56(void){
    // LD_A_addr(wcd30);
    // CP_A(0x1);
    // IF_Z goto asm_17db74;
    if(wram->wcd30 != 0x1) {
        // CALL(aFunction17e566);
        Function17e566();
        // LD_A_addr(wcd30);
        // DEC_A;
        // LD_addr_A(wcd30);
        wram->wcd30--;
        // LD_A_addr(wcd2e);
        // DEC_A;
        // LD_addr_A(wcd2e);
        wram->wcd2e--;
        // CALL(aFunction17e55b);
        Function17e55b();
        // CALL(aFunction17e5af);
        Function17e5af();
    }

// asm_17db74:
    // JP(mIncCrashCheckPointer);
    IncCrashCheckPointer();
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

// NewsCommand_RotateFourPalsLeft
void Function17dc9f(void){
    // CALL(aIncCrashCheckPointer);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(IncCrashCheckPointer());
    // CALL(aRotateFourPalettesLeft);
    RotateFourPalettesLeft_Conv();
    // RET;
}

// NewsCommand_RotateFourPalsRight
void Function17dca9(void){
    // CALL(aIncCrashCheckPointer);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(IncCrashCheckPointer());

    return Function17dcaf();
}

void Function17dcaf(void){
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(wBGPals1);
    uint8_t* hl = wram->wBGPals1;
    // LD_DE(1 * PALETTE_SIZE);
    // LD_C(8);
    uint8_t c = 8;

    do {
    // asm_17dcbb:
        // PUSH_HL;
        // LD_A(0xff);
        // LD_hli_A;
        hl[0] = 0xff;
        // LD_A(0x7f);
        // LD_hl_A;
        hl[1] = 0xff;
        // POP_HL;
        // ADD_HL_DE;
        hl += PALETTE_SIZE;
        // DEC_C;
        // IF_NZ goto asm_17dcbb;
    } while(--c != 0);
    // CALL(aRotateThreePalettesRight);
    RotateThreePalettesRight_Conv();
    // LD_A(0x4);
    // LDH_addr_A(rSVBK);
    // RET;
}

// NewCommand_CallSubroutine?
void Function17dccf(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // PUSH_HL;
    // LD_A_addr(wcd4b);
    // LD_L_A;
    // LD_A_addr(wcd4c);
    // LD_H_A;
    // LD_A_addr(wcd2e);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    uint8_t* hl2 = gMobile_wcd4b_wcd4c + (wram->wcd2e * 2);
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hl;
    // LD_B_A;
    uint16_t bc = hl2[0] | (hl2[1] << 8);
    // CALL(aFunction17e43d);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(Function17e43d(bc));

    while(1) {
    // asm_17dced:
        // LD_A_addr(wMobileCrashCheckPointer);
        // LD_L_A;
        // LD_A_addr(wMobileCrashCheckPointer + 1);
        // LD_H_A;
        // LD_A_hl;
        uint8_t cmd = *sMobileCrashCheckPointer;
        // CP_A(0xff);
        // IF_Z goto asm_17dd0d;
        if(cmd == 0xff)
            break;

    // crash_loop:
        // CP_A(0x31);
        // IF_NC goto crash_loop;
        if(cmd >= 0x31)
            cmd = 0x30;
        // CALL(aFunction17d711);
        Function17d711(cmd);
        // LD_A_addr(wcd77);
        // BIT_A(7);
        // IF_NZ goto asm_17dd0d;
        if(bit_test(wram->wcd77, 7))
            break;
        // AND_A_A;
        // IF_Z goto asm_17dd11;
        if(wram->wcd77 == 0)
            return;
        // goto asm_17dced;
    }

// asm_17dd0d:
    // POP_HL;
    // JP(mHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl);

// asm_17dd11:
    // POP_HL;
    // RET;
}

// NewsCommand_PlaceText
void Function17dd13(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    uint16_t bc = hl[0] | (hl[1] << 8);
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t de = hl[2] | (hl[3] << 8);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 4);
    // CALL(aFunction17e447);
    // PUSH_HL;
    hl = Function17e447(de);
    // hlcoord(0, 0, wTilemap);
    // ADD_HL_BC;
    // PUSH_HL;
    // POP_BC;
    // POP_HL;
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv(hl, coord(0, 0, wram->wTilemap) + bc);
    // RET;
}

// NewsCommand_ClearText
void Function17dd30(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t de = hl[0] | (hl[1] << 8);
    // LD_A_hli;
    // LD_C_A;
    // LD_B(0);
    uint16_t bc = hl[2];
    // LD_A_hli;
    // PUSH_AF;
    uint8_t a = hl[3];
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 4);
    // POP_AF;
    // hlcoord(0, 0, wTilemap);
    // ADD_HL_DE;
    // CALL(aFunction17e600);
    Function17e600(coord(0, 0, wram->wTilemap) + de, bc, a);
    // RET;
}

void Function17dd49(void){
    uint8_t svbk = gb_read(rSVBK);
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_DE(wc708);
    // LD_BC(0xa);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wc708, hl, 0xa);
    // LD_A_addr(wc711);
    // LD_C_A;
    // LD_B(0);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc712, hl + 0xa, wram->wc711);
    // LD_A_addr(wc70a);
    // CP_A(0xc0);
    // IF_C goto sram;
    if(wram->wc70a < 0xc0) {
    // sram:
        // LD_A_addr(wc708);
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(wram->wc708);
    }
    else {
        // LD_A_addr(wc708);
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, wram->wc708);
        // goto got_bank;
    }

// got_bank:
    // LD_A_addr(wc709);
    // LD_L_A;
    // LD_A_addr(wc70a);
    // LD_H_A;
    // LD_DE(wc688);
    // LD_A_addr(wc711);
    // LD_C_A;
    // LD_B(0);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc688, GBToRAMAddr(wram->wc709 | (wram->wc70a << 8)), wram->wc711);
    // LD_A_addr(wc70a);
    // CP_A(0xc0);
    // IF_C goto close_sram;
    if(wram->wc70a < 0xc0) {
    // close_sram:
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
    }
    else {
        // LD_A(0x4);
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, svbk);
        // goto exited_bank;
    }

// exited_bank:
    // LD_A_addr(wc711);
    // LD_C_A;
    uint8_t c = wram->wc711;
    // LD_HL(wc712);
    // LD_DE(wc688);
    uint16_t ptr;
    hl = wram->wc712;
    const uint8_t* de = wram->wc688;

    do {
    // loop:
        // LD_A_de;
        // INC_DE;
        // CP_A_hl;
        // INC_HL;
        // IF_Z goto next;
        // IF_C goto load;
        if(*de < *hl) {
        // load:
            // LD_A_addr(wc70b);
            // LD_L_A;
            // LD_A_addr(wc70c);
            // LD_H_A;
            ptr = wram->wc70b | (wram->wc70c << 8);
            goto done;
        }
        // goto load2;
        else if(*de > *hl) {
        // load2:
            // LD_A_addr(wc70f);
            // LD_L_A;
            // LD_A_addr(wc710);
            // LD_H_A;
            ptr = wram->wc70f | (wram->wc710 << 8);
            goto done;
        }

    // next:
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_A_addr(wc70d);
    // LD_L_A;
    // LD_A_addr(wc70e);
    // LD_H_A;
    ptr = wram->wc70d | (wram->wc70e << 8);
    // goto done;

done:
    // CALL(aFunction17e40f);
    Function17e40f(ptr);
    // RET;
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

// NewsCommand_MemoryCompare?
void Function17e1a1(void){
    uint8_t svbk = gb_read(rSVBK);
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_DE(wc708);
    // LD_BC(0xd);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wc708, hl, 0xd);
    // LD_A_addr(wc70a);
    // CP_A(0xc0);
    // IF_C goto asm_17e1bb;
    if(wram->wc70a < 0xc0) {
    // asm_17e1bb:
        // LD_A_addr(wc708);
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(wram->wc708);
    }
    else {
        // LD_A_addr(wc708);
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, wram->wc708);
        // goto asm_17e1c1;
    }

// asm_17e1c1:
    // LD_A_addr(wc709);
    // LD_L_A;
    // LD_A_addr(wc70a);
    // LD_H_A;
    const uint8_t* src0 = GBToRAMAddr(wram->wc709 | (wram->wc70a << 8));
    // LD_DE(wc608);
    // LD_A_addr(wc70b);
    // LD_C_A;
    // LD_B(0);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc608, src0, wram->wc70b);
    // LD_A_addr(wc70a);
    // CP_A(0xc0);
    // IF_C goto asm_17e1e2;
    if(wram->wc70a < 0xc0) {
    // asm_17e1e2:
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
    }
    else {
        // LD_A(0x4);
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, svbk);
        // goto asm_17e1e5;
    }

// asm_17e1e5:
    // LD_A_addr(wc70e);
    // CP_A(0xc0);
    // IF_C goto asm_17e1f3;
    if(wram->wc70e < 0xc0) {
    // asm_17e1f3:
        // LD_A_addr(wc70c);
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(wram->wc70c);
    }
    else {
        // LD_A_addr(wc70c);
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, wram->wc70c);
        // goto asm_17e1f9;
    }

// asm_17e1f9:
    // LD_A_addr(wc70d);
    // LD_L_A;
    // LD_A_addr(wc70e);
    // LD_H_A;
    const uint8_t* src1 = GBToRAMAddr(wram->wc70d | (wram->wc70e << 8));
    // LD_DE(wc688);
    // LD_A_addr(wc70b);
    // LD_C_A;
    // LD_B(0);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc688, src1, wram->wc70b);
    // LD_A_addr(wc70e);
    // CP_A(0xc0);
    // IF_C goto asm_17e21a;
    if(wram->wc70e < 0xc0) {
    // asm_17e21a:
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
    }
    else {
        // LD_A(0x4);
        // LDH_addr_A(rSVBK);
        gb_write(rSVBK, svbk);
        // goto asm_17e21d;
    }

// asm_17e21d:
    // LD_A_addr(wc70b);
    // LD_C_A;
    uint8_t c = wram->wc70b;
    // LD_HL(wc688);
    hl = wram->wc688;
    // LD_DE(wc608);
    uint8_t* de = wram->wc608;

    do {
    // asm_17e227:
        // LD_A_de;
        // INC_DE;
        uint8_t a = *(de++);
        // CP_A_hl;
        // INC_HL;
        uint8_t b = *(hl++);
        // IF_Z goto asm_17e231;
        // IF_C goto asm_17e23e;
        if(a < b) {
        // asm_17e23e:
            // LD_A_addr(wc70f);
            // LD_L_A;
            // LD_A_addr(wc710);
            // LD_H_A;
            // goto asm_17e250;
            return Function17e40f(wram->wc70f | (wram->wc710 << 8));
        }
        // goto asm_17e248;
        else if(a > b) {
        // asm_17e248:
            // LD_A_addr(wc712 + 1);
            // LD_L_A;
            // LD_A_addr(wc712 + 2);
            // LD_H_A;
            return Function17e40f(wram->wc712[1] | (wram->wc712[2] << 8));
        }

    // asm_17e231:
        // DEC_C;
        // IF_NZ goto asm_17e227;
    } while(--c != 0);
    // LD_A_addr(wc711);
    // LD_L_A;
    // LD_A_addr(wc712);
    // LD_H_A;
    // goto asm_17e250;

// asm_17e250:
    // CALL(aFunction17e40f);
    // RET;
    return Function17e40f(wram->wc711 | (wram->wc712[0] << 8));
}

// NewsCommand_SetVal
void Function17e254(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint8_t* de = GBToRAMAddr(hl[0] | (hl[1] << 8));
    // LD_A_hli;
    // LD_de_A;
    *de = hl[2];
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 3);
    // RET;
}

// NewsCommand_AddVal
void Function17e261(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint8_t* de = GBToRAMAddr(hl[0] | (hl[1] << 8));
    // LD_A_de;
    // ADD_A_hl;
    // LD_de_A;
    *de += hl[2];
    // INC_HL;
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 3);
    // RET;
}

// NewsCommand_SubVal
void Function17e270(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint8_t* de = GBToRAMAddr(hl[0] | (hl[1] << 8));
    // LD_A_de;
    // SUB_A_hl;
    // LD_de_A;
    *de -= hl[2];
    // INC_HL;
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 3);
    // RET;
}

// NewsCommand_AddMem
void Function17e27f(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint8_t* de = GBToRAMAddr(hl[0] | (hl[1] << 8));
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    uint8_t* bc = GBToRAMAddr(hl[2] | (hl[3] << 8));
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 4);
    // LD_L_C;
    // LD_H_B;
    // LD_A_de;
    // ADD_A_hl;
    // LD_de_A;
    *de += *bc;
    // RET;
}

// NewsCommand_SubMem
void Function17e293(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint8_t* de = GBToRAMAddr(hl[0] | (hl[1] << 8));
    // LD_A_hli;
    // LD_C_A;
    // LD_A_hli;
    // LD_B_A;
    uint8_t* bc = GBToRAMAddr(hl[2] | (hl[3] << 8));
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl + 4);
    // LD_L_C;
    // LD_H_B;
    // LD_A_de;
    // SUB_A_hl;
    // LD_de_A;
    *de -= *bc;
    // RET;
}

void Function17e2a7(void){
    // CALL(aIncCrashCheckPointer);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(IncCrashCheckPointer());
    // CALL(aFunction17e32b);
    Function17e32b();
    // XOR_A_A;
    // LD_addr_A(wcf66);
    // FARCALL(aFunction118233);
    Function118233();
    // LD_DE(mPostalMarkGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x60);
    // LD_BC((BANK(aPostalMarkGFX) << 8) | 1);
    // CALL(aGet2bpp);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x60, PostalMarkGFX, 0, 1);
    // LD_A_addr(wMobileErrorCodeBuffer);
    // AND_A_A;
    // IF_Z goto asm_17e2d8;
    if(wram->wMobileErrorCodeBuffer[0] == 0) {
    // asm_17e2d8:
        // CALL(aFunction17d60b);
        Function17d60b();
        // CALL(aFunction17e349);
        Function17e349();
        // XOR_A_A;
        // LD_addr_A(wcd7a);
        // LD_A(0x5);
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(as5_aa7f));
        // LD_HL(0xaa73);
        // LD_DE(0xaa7f);
        // LD_BC(0xc);
        // CALL(aCopyBytes);
        CopyBytes(GBToRAMAddr(s5_aa7f), GBToRAMAddr(s5_aa73), 0xc);
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
        // RET;
        return;
    }
    // CP_A(0xa);
    // IF_Z goto asm_17e2f7;
    else if(wram->wMobileErrorCodeBuffer[0] == 0xa) {
    // asm_17e2f7:
        // CALL(aFunction17e349);
        Function17e349();
        // LD_A(0x1);
        // LD_addr_A(wcd7a);
        wram->wcd7a[0] = 0x1;
        // RET;
        return;
    }
    // CP_A(0xb);
    // IF_Z goto asm_17e300;
    else if(wram->wMobileErrorCodeBuffer[0] == 0xb) {
    // asm_17e300:
        // CALL(aFunction17e349);
        Function17e349();
        // LD_A(0x2);
        // LD_addr_A(wcd7a);
        wram->wcd7a[0] = 0x2;
        // RET;    
        return;
    }
    // CALL(aFunction17e309);
    Function17e309();
    // RET;
    return;
}

// News_ShowError
void Function17e309(void){
    // LD_A(0x2);
    // LD_addr_A(wc303);
    wram->wc303 = 0x2;
    // CALL(aFunction17dcaf);
    Function17dcaf();
    // CALL(aClearScreen);
    ClearScreen_Conv2();
    // CALL(aFunction17e349);
    Function17e349();
    // CALL(aFunction17d5f6);
    Function17d5f6();
    // FARCALL(aDisplayMobileError);
    DisplayMobileError();
    // CALL(aFunction17e349);
    Function17e349();
    // CALL(aFunction17dcaf);
    Function17dcaf();
    // XOR_A_A;
    // LD_addr_A(wcd77);
    wram->wcd77 = 0x0;
    // RET;

}

void Function17e32b(void){
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_b091));
    // LD_HL(wc608);
    // LD_DE(0xb0b1);
    // LD_BC(0x40);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_b091 + 0x20), wram->wc608, 0x40);
    // LD_HL(wBGMapBuffer);
    // LD_BC(0x5b);
    // CALL(aCopyBytes);
    CopyBytes(GBToRAMAddr(s5_b091 + 0x60), wram->wBGMapBuffer, 0x5b);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void Function17e349(void){
    // LD_A(0x5);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_b091));
    // LD_HL(0xb0b1);
    // LD_DE(wc608);
    // LD_BC(0x40);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc608, GBToRAMAddr(s5_b091 + 0x20), 0x40);
    // LD_DE(wBGMapBuffer);
    // LD_BC(0x5b);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGMapBuffer, GBToRAMAddr(s5_b091 + 0x60), 0x5b);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;

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

#define inc_crash_check_pointer_farcall(_body) do { IncCrashCheckPointer(); uint8_t svbk = gb_read(rSVBK); gb_write(rSVBK, 0x1); do _body while(0); gb_write(rSVBK, svbk); } while(0)

void IncCrashCheckPointer_SaveGameData(void){
    //inc_crash_check_pointer_farcall ['_SaveGameData']
    inc_crash_check_pointer_farcall({ v_SaveGameData(); });
}

void IncCrashCheckPointer_SaveAfterLinkTrade(void){
    //inc_crash_check_pointer_farcall ['SaveAfterLinkTrade']
    inc_crash_check_pointer_farcall({ SaveAfterLinkTrade(); });
}

void IncCrashCheckPointer_SaveBox(void){
    //inc_crash_check_pointer_farcall ['SaveBox']
    inc_crash_check_pointer_farcall({ SaveBox(); });
}

void IncCrashCheckPointer_SaveChecksum(void){
    //inc_crash_check_pointer_farcall ['SaveChecksum']
    inc_crash_check_pointer_farcall({ SaveChecksum(); });
}

void IncCrashCheckPointer_SaveTrainerRankingsChecksum(void){
    //inc_crash_check_pointer_farcall ['UpdateTrainerRankingsChecksum2', 'BackupMobileEventIndex']
    inc_crash_check_pointer_farcall({ UpdateTrainerRankingsChecksum2(); BackupMobileEventIndex(); });
}

// NewsCommand_DelayFrames
void Function17e3e0(void){
    // CALL(aIncCrashCheckPointer);
    uint8_t* hl = IncCrashCheckPointer();
    // LD_A_hli;
    // LD_C_A;
    uint8_t c = *(hl++);
    // CALL(aHlToCrashCheckPointer);
    HlToCrashCheckPointer(hl);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // CALL(aDelayFrames);
    DelayFrames(c);
    // RET;
}

// NewsCommand_WaitAOrB
void Function17e3f0(void){
    // CALL(aIncCrashCheckPointer);
    IncCrashCheckPointer();
    // CALL(aHlToCrashCheckPointer);

    while(1) {
    // asm_17e3f6:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // LD_HL(hJoyPressed);
        // LD_A_hl;
        // AND_A(0x1);
        // RET_NZ ;
        // LD_A_hl;
        // AND_A(0x2);
        // RET_NZ ;
        if((hram->hJoyPressed & A_BUTTON) || (hram->hJoyPressed & B_BUTTON))
            return;
        // CALL(aWaitBGMap);
        WaitBGMap_Conv();
        // goto asm_17e3f6;
    }
}

// NewsCommand_Exit
void Function17e409(void){
    // LD_HL(wcd77);
    // SET_hl(7);
    bit_set(wram->wcd77, 7);
    // RET;
}

void Function17e40f(uint16_t hl){
    // LD_DE(wBGPals1);
    // ADD_HL_DE;
    // JR(mHlToCrashCheckPointer);
    HlToCrashCheckPointer(wram->wram4 + hl);
}

uint8_t* IncCrashCheckPointer(void){
    // LD_A_addr(wMobileCrashCheckPointer);
    // LD_L_A;
    // LD_A_addr(wMobileCrashCheckPointer + 1);
    // LD_H_A;
    // INC_HL;

    return HlToCrashCheckPointer(sMobileCrashCheckPointer + 1);
}

uint8_t* HlToCrashCheckPointer(uint8_t* hl){
    // LD_A_L;
    // LD_addr_A(wMobileCrashCheckPointer);
    // LD_A_H;
    // LD_addr_A(wMobileCrashCheckPointer + 1);
    sMobileCrashCheckPointer = hl;
    // RET;
    return hl;
}

void Function17e427(void){
    // LD_HL(hJoyPressed);
    // LD_A_hl;
    // AND_A(0x1);
    // IF_NZ goto asm_17e432;
    // AND_A(0x2);
    // RET_Z ;
    if(hram->hJoyPressed & (A_BUTTON | B_BUTTON)) {
    // asm_17e432:
        // LD_A(0x3);
        // LD_addr_A(wcd77);
        wram->wcd77 = 0x3;
        // RET;
    }
}

// MobileNews_IncJumptableIndex
void Function17e438(void){
    // LD_HL(wcd77);
    // INC_hl;
    // RET;
    wram->wcd77++;
}

uint8_t* Function17e43d(uint16_t bc){
    // LD_A_addr(wBGMapBuffer);
    // LD_L_A;
    // LD_A_addr(wcd21);
    // LD_H_A;
    // ADD_HL_BC;
    // RET;
    return gMobile_wcd20_wcd21 + bc;
}

uint8_t* Function17e447(uint16_t de){
    // LD_A_addr(wBGMapBuffer);
    // LD_L_A;
    // LD_A_addr(wcd21);
    // LD_H_A;
    // ADD_HL_DE;
    // RET;
    return gMobile_wcd20_wcd21 + de;
}

void Function17e451(void){
    // LD_A_addr(wcd42);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd42 == 0)
        return;
    // CALL(aFunction17e51b);
    Function17e51b();
    // CALL(aFunction17e4dd);
    Function17e4dd();
    // LD_A_addr(wcd2e);
    // PUSH_AF;
    uint8_t a = wram->wcd2e;
    // LD_A_addr(wcd49);
    // LD_L_A;
    // LD_A_addr(wcd4a);
    // LD_H_A;
    // LD_A_addr(wcd2f);
    // LD_addr_A(wcd2e);
    wram->wcd2e = wram->wcd2f;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    uint8_t* bc = gMobile_wcd49_wcd4a + 2 * wram->wcd2e;
    // PUSH_HL;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(0x14);
    // LD_A_addr(wcd23);
    // CALL(aAddNTimes);
    // LD_A_addr(wCreditsTimer);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    tile_t* hl = coord(wram->wcd22, wram->wcd23, wram->wTilemap);
    // POP_BC;
    // LD_A_addr(wMobileCommsJumptableIndex);
    uint8_t a2 = wram->wMobileCommsJumptableIndex;

    do {
    // asm_17e48b:
        // PUSH_AF;
        // PUSH_HL;
        tile_t* hl2 = hl;
        // LD_A_addr(wcd24);
        uint8_t a3 = wram->wcd24;

        do {
        // asm_17e490:
            // PUSH_AF;
            // PUSH_HL;
            // LD_A_bc;
            // INC_BC;
            // LD_E_A;
            // LD_A_bc;
            // INC_BC;
            // LD_D_A;
            uint16_t de2 = bc[0] | (bc[1] << 8);
            bc += 2;
            // PUSH_BC;
            // PUSH_HL;
            // LD_A_addr(wBGMapBuffer);
            // LD_L_A;
            // LD_A_addr(wcd21);
            // LD_H_A;
            // ADD_HL_DE;
            // PUSH_HL;
            // POP_DE;
            // POP_HL;
            // CALL(aPlaceString);
            struct TextPrintState st = {.de = gMobile_wcd20_wcd21 + de2, .hl = hl2, .bc = bc};
            PlaceString_Conv(&st, st.hl);
            // POP_BC;
            // POP_HL;
            // LD_A_addr(wcd26);
            // LD_E_A;
            // LD_D(0);
            // ADD_HL_DE;
            hl2 += wram->wcd26;
            // LD_A_addr(wcd2e);
            // INC_A;
            // LD_addr_A(wcd2e);
            // LD_E_A;
            // LD_A_addr(wcd42);
            // CP_A_E;
            // IF_Z goto asm_17e4d5;
            if(++wram->wcd2e == wram->wcd42)
                goto asm_17e4d8;
            // POP_AF;
            // DEC_A;
            // IF_NZ goto asm_17e490;
        } while(--a3 != 0);
        // POP_HL;
        // LD_A_addr(wcd27);
        // LD_DE(0x14);

    // asm_17e4cb:
        // ADD_HL_DE;
        // DEC_A;
        // IF_NZ goto asm_17e4cb;
        hl += SCREEN_WIDTH * wram->wcd27;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_17e48b;
    } while(--a2 != 0);
    // goto asm_17e4d8;

// asm_17e4d5:
    // POP_AF;
    // POP_HL;
    // POP_AF;

asm_17e4d8:
    // POP_AF;
    // LD_addr_A(wcd2e);
    wram->wcd2e = a;
    // RET;
}

void Function17e4dd(void){
    // LD_A_addr(wcd2c);
    // AND_A(0x1);
    // RET_Z ;
    if((wram->wcd2c & 1) == 0)
        return;
    // LD_A_addr(wcd29);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(0x14);
    // CALL(aAddNTimes);
    // LD_A_addr(wcd28);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    tile_t* hl = coord(wram->wcd28, wram->wcd29, wram->wTilemap);
    // LD_A_addr(wcd2f);
    // AND_A_A;
    // IF_Z goto asm_17e4ff;
    if(wram->wcd2f != 0) {
        // LD_A(0x61);
        // LD_hl_A;
        *hl = 0x61;
    }

// asm_17e4ff:
    // LD_A_addr(wcd2a);
    // LD_BC(0x14);
    // CALL(aAddNTimes);
    hl += SCREEN_WIDTH * wram->wcd2a;
    // LD_A_addr(wcd42);
    // LD_C_A;
    // LD_A_addr(wcd2e);
    // LD_B_A;
    // LD_A_addr(wcd24);
    // ADD_A_B;
    // CP_A_C;
    // RET_Z ;
    // RET_NC ;
    if(wram->wcd2e + wram->wcd24 >= wram->wcd42)
        return;
    // LD_A(0xee);
    // LD_hl_A;
    *hl = 0xee;
    // RET;
}

void Function17e51b(void){
    // LD_A_addr(wcd28);
    // LD_HL(wCreditsTimer);
    // SUB_A_hl;
    // INC_A;
    // LD_addr_A(wcd4f);
    wram->wcd4f = (wram->wcd28 - wram->wcd22) + 1;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(0x14);
    // LD_A_addr(wcd23);
    // DEC_A;
    // CALL(aAddNTimes);
    // LD_A_addr(wCreditsTimer);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    tile_t* hl = coord(wram->wcd22, wram->wcd23, wram->wTilemap);
    // LD_A_addr(wMobileCommsJumptableIndex);
    // LD_C_A;
    // LD_A_addr(wcd27);
    // CALL(aSimpleMultiply);
    uint8_t a = wram->wMobileCommsJumptableIndex * wram->wcd27;

    do {
    // asm_17e544:
        // PUSH_AF;
        // PUSH_HL;
        // LD_A_addr(wcd4f);
        // LD_C_A;
        // LD_B(0);
        // LD_A(0x7f);
        // CALL(aByteFill);
        ByteFill(hl, wram->wcd4f, 0x7f);
        // POP_HL;
        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_17e544;
    } while(--a != 0);
    // RET;
}

void Function17e55b(void){
    // LD_A_addr(wcd42);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd42 == 0)
        return;
    // LD_A(0xed);
    // CALL(aFunction17e571);
    // RET;
    return Function17e571(0xed);
}

void Function17e566(void){
    // LD_A_addr(wcd42);
    // AND_A_A;
    // RET_Z ;
    if(wram->wcd42 == 0)
        return;
    // LD_A(0x7f);
    // CALL(aFunction17e571);
    // RET;
    return Function17e571(0x7f);
}

void Function17e571(uint8_t a){
    // PUSH_AF;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(0x14);
    // LD_A_addr(wcd23);
    // CALL(aAddNTimes);
    // LD_A_addr(wCreditsTimer);
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // DEC_HL;
    // PUSH_HL;
    tile_t* hl = coord(wram->wcd22, wram->wcd23, wram->wTilemap) - 1;
    // LD_A_addr(wcd31);
    // DEC_A;
    // LD_C_A;
    // LD_A_addr(wcd27);
    // CALL(aSimpleMultiply);
    uint8_t y = (wram->wcd31 - 1) * wram->wcd27;
    // LD_L(0x0);
    // LD_H_L;
    // LD_BC(0x14);
    // CALL(aAddNTimes);
    // LD_A_addr(wcd30);
    // DEC_A;
    // LD_C_A;
    // LD_A_addr(wcd26);
    // CALL(aSimpleMultiply);
    uint8_t x = (wram->wcd30 - 1) * wram->wcd26;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    uint16_t bc = coord(x, y, 0);
    // POP_BC;
    // ADD_HL_BC;
    // POP_AF;
    // LD_hl_A;
    hl[bc] = a;
    // RET;
}

void Function17e5af(void){
    // LD_A_addr(wcd2c);
    // AND_A(0x2);
    // RET_Z ;
    if((wram->wcd2c & 0x2) == 0)
        return;
    // LD_A_addr(wcd43);
    // LD_L_A;
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // LD_H_A;
    // bccoord(0, 0, wTilemap);
    // ADD_HL_BC;
    // LD_BC(0xffec); // -SCREEN_WIDTH
    // ADD_HL_BC;
    tile_t* hl = coord(0, 0, wram->wTilemap) + (wram->wcd43[0] | (wram->wMobileInactivityTimerMinutes << 8)) - SCREEN_WIDTH;
    // LD_A_addr(wMobileInactivityTimerSeconds);
    // LD_C_A;
    // LD_B(0);
    // LD_A_addr(wMobileInactivityTimerFrames);
    // CALL(aFunction17e600);
    Function17e600(hl, wram->wMobileInactivityTimerSeconds, wram->wMobileInactivityTimerFrames);
    // LD_A_addr(wcd2e);
    // LD_C_A;
    // LD_B(0);
    // LD_A_addr(wcd4d);
    // LD_L_A;
    // LD_A_addr(wcd4e);
    // LD_H_A;
    uint8_t* hl2 = gMobile_wcd4d_wcd4e;
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t de = hl2[wram->wcd2e * 2 + 0] | (hl2[wram->wcd2e * 2 + 1] << 8);
    // LD_A_addr(wBGMapBuffer);
    // LD_L_A;
    // LD_A_addr(wcd21);
    // LD_H_A;
    // ADD_HL_DE;
    // PUSH_HL;
    // POP_DE;
    uint8_t* de2 = gMobile_wcd20_wcd21 + de;
    // LD_A_addr(wcd43);
    // LD_L_A;
    // LD_A_addr(wMobileInactivityTimerMinutes);
    // LD_H_A;
    // bccoord(0, 0, wTilemap);
    // ADD_HL_BC;
    // CALL(aPlaceString);
    PlaceStringSimple(de2, coord(0, 0, wram->wTilemap) + (wram->wcd43[0] | (wram->wMobileInactivityTimerMinutes << 8)));
    // RET;
}

uint8_t* Function17e600(uint8_t* hl, uint16_t bc, uint8_t a){
    do {
    // asm_17e600:
        // PUSH_AF;
        // PUSH_HL;
        // PUSH_BC;
        // LD_A(0x7f);
        // CALL(aByteFill);
        ByteFill(hl, bc, 0x7f);
        // POP_BC;
        // POP_HL;
        // LD_DE(0x14);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_17e600;
    } while(--a != 0);
    // RET;
    return hl;
}

void Function17e613(const uint8_t* de){
    // PUSH_HL;
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    // LD_BC(0x14);
    // LD_A_de;
    // INC_DE;
    // PUSH_AF;
    uint8_t a = *(de++);
    // LD_A_de;
    // INC_DE;
    // AND_A_A;

// asm_17e620:
    // IF_Z goto asm_17e626;
    // ADD_HL_BC;
    // DEC_A;
    // goto asm_17e620;
    hl += SCREEN_WIDTH * *(de++);

// asm_17e626:
    // POP_AF;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    hl += a;
    tile_t* hl2 = hl;
    // PUSH_HL;
    // LD_A_addr(wcd53);
    // LD_hli_A;
    *(hl2++) = wram->wcd53;
    // LD_A_de;
    a = *(de++);
    // INC_DE;
    // DEC_A;
    // DEC_A;
    a -= 2;
    // IF_Z goto asm_17e63f;
    if(a != 0) {
        // LD_C_A;
        uint8_t c = a;
        // LD_A_addr(wcd53);
        // INC_A;

        do {
        // asm_17e63b:
            // LD_hli_A;
            *(hl2++) = wram->wcd53 + 1;
            // DEC_C;
            // IF_NZ goto asm_17e63b;
        } while(--c != 0);
    }

// asm_17e63f:
    // LD_A_addr(wcd53);
    // ADD_A(0x2);
    // LD_hl_A;
    *hl2 = wram->wcd53 + 0x2;
    // POP_HL;
    // LD_BC(0x14);
    // ADD_HL_BC;
    hl += SCREEN_WIDTH;
    // LD_A_de;
    // DEC_DE;
    a = *(de--);
    // DEC_A;
    // DEC_A;
    a -= 2;
    // IF_Z goto asm_17e674;
    if(a != 0) {
        // LD_B_A;
        uint8_t b = a;

        do {
        // asm_17e651:
            // PUSH_HL;
            tile_t* hl2 = hl;
            // LD_A_addr(wcd53);
            // ADD_A(0x3);
            // LD_hli_A;
            *(hl2++) = wram->wcd53 + 0x3;
            // LD_A_de;
            a = *de;
            // DEC_A;
            // DEC_A;
            a -= 2;
            // IF_Z goto asm_17e664;
            while(a != 0) {
                // LD_C_A;
                // LD_A(0x7f);

            // asm_17e660:
                // LD_hli_A;
                *(hl2++) = 0x7f;
                // DEC_C;
                --a;
                // IF_NZ goto asm_17e660;
            }

        // asm_17e664:
            // LD_A_addr(wcd53);
            // ADD_A(0x4);
            // LD_hl_A;
            *hl2 = wram->wcd53 + 0x4;
            // POP_HL;
            // PUSH_BC;
            // LD_BC(0x14);
            // ADD_HL_BC;
            hl += SCREEN_WIDTH;
            // POP_BC;
            // DEC_B;
            // IF_NZ goto asm_17e651;
        } while(--b != 0);
    }

// asm_17e674:
    // LD_A_addr(wcd53);
    // ADD_A(0x5);
    // LD_hli_A;
    *(hl++) = wram->wcd53 + 0x5;
    // LD_A_de;
    a = *de;
    // DEC_A;
    // DEC_A;
    a -= 2;
    // IF_Z goto asm_17e689;
    while(a != 0) {
        // LD_C_A;
        // LD_A_addr(wcd53);
        // ADD_A(0x6);

    // asm_17e685:
        // LD_hli_A;
        *(hl++) = wram->wcd53 + 0x6;
        // DEC_C;
        // IF_NZ goto asm_17e685;
        a--;
    }

// asm_17e689:
    // LD_A_addr(wcd53);
    // ADD_A(0x7);
    // LD_hl_A;
    *hl = wram->wcd53 + 0x7;
    // POP_HL;
    // RET;
}

void Function17e691(const uint8_t* de){
    // PUSH_HL;
    // LD_HL(0);
    uint16_t hl = 0;
    // LD_BC(0x14);
    // LD_A_de;
    // INC_DE;
    uint8_t a = *(de++);
    // PUSH_AF;
    // LD_A_de;
    // INC_DE;
    uint8_t a2 = *(de++);
    // INC_DE;
    de++;
    // AND_A_A;

// asm_17e69f:
    // IF_Z goto asm_17e6a5;
    // ADD_HL_BC;
    // DEC_A;
    // goto asm_17e69f;

// asm_17e6a5:
    // POP_AF;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    hl += (SCREEN_WIDTH * a2) + a;
    // LD_A_de;
    // DEC_DE;
    a = *(de--);

    do {
    // asm_17e6ac:
        // PUSH_AF;
        // PUSH_HL;
        uint16_t hl2 = hl;
        // LD_A_de;
        uint8_t a2 = *de;

        do {
        // asm_17e6af:
            // PUSH_AF;
            // PUSH_HL;
            // PUSH_HL;
            // bccoord(0, 0, wTilemap);
            // ADD_HL_BC;
            // LD_A_hl;
            // CP_A(0x7f);
            // IF_Z goto asm_17e6c2;
            // LD_A_addr(wcd53);
            // ADD_A(0x8);
            // goto asm_17e6c7;

        // asm_17e6c2:
            // LD_A_addr(wcd53);
            // goto asm_17e6c7;

        // asm_17e6c7:
            uint8_t a3 = (coord(0, 0, wram->wTilemap)[hl2] == 0x7f)? wram->wcd53: wram->wcd53 + 0x8;
            // POP_HL;
            // bccoord(0, 0, wAttrmap);
            // ADD_HL_BC;
            // LD_hl_A;
            coord(0, 0, wram->wAttrmap)[hl2] = a3;
            // POP_HL;
            // INC_HL;
            hl2++;
            // POP_AF;
            // DEC_A;
            // IF_NZ goto asm_17e6af;
        } while(--a2 != 0);
        // POP_HL;
        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_17e6ac;
    } while(--a != 0);
    // POP_HL;
    // RET;
}

void Function17e6de(uint8_t a){
    // PUSH_AF;
    // LD_A_addr(wc708);
    // LD_L_A;
    // LD_A_addr(wc709);
    // LD_H_A;
    uint16_t de = wram->wc708 | (wram->wc709 << 8);
    // decoord(0, 0, wAttrmap);
    // ADD_HL_DE;
    uint8_t* hl = coord(0, 0, wram->wAttrmap) + de;
    // POP_AF;
    // LD_B(0x7);
    uint8_t b = 0x7;

    do {
    // asm_17e6ee:
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_C(0x7);
        uint8_t c = 0x7;

        do {
        // asm_17e6f1:
            // LD_hli_A;
            *(hl2++) = a;
            // DEC_C;
            // IF_NZ goto asm_17e6f1;
        } while(--c != 0);
        // POP_HL;
        // LD_DE(0x14);
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto asm_17e6ee;
    } while(--b != 0);
    // RET;
}

const char PokemonNewsGFX[] = "gfx/mobile/pokemon_news.png";
const char PostalMarkGFX[] = "gfx/font/postal_mark.png";
const char PokemonNewsTileAttrmap[] = "gfx/mobile/pokemon_news.bin";
const char PokemonNewsPalettes[] = "gfx/mobile/pokemon_news.pal";

void RunMobileScript(struct TextPrintState* state){
    // LD_A(0x6);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as6_a000));
    // INC_DE;
    state->de++;

    bool done = false;
    do {
    // loop:
        // CALL(av_RunMobileScript);
        done = v_RunMobileScript(state);
        // IF_C goto finished;
        // goto loop;
    } while(!done);

// finished:
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

bool v_RunMobileScript(struct TextPrintState* state){
    // LD_A_de;
    // INC_DE;
    uint8_t ch = *(state->de++);
    // CP_A(0x50);
    // IF_Z goto finished;
    // CP_A(0x10);  // jumptable size
    // IF_NC goto finished;
    if(ch != 0x50 && ch < 0x10) {
        // DEC_A;
        // PUSH_DE;
        // LD_E_A;
        // LD_D(0);
        // LD_HL(mv_RunMobileScript_Jumptable);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_H_hl;
        // LD_L_A;
        // JP_hl;
        printf("RunMobileCommand(%d)\n", ch - 1);
        switch(ch - 1) {
        // Jumptable:
            case 0x0: return Function17f081(state, state->de);  // 0
            case 0x1: return Function17f0f8(state, state->de);  // 1
            case 0x2: return Function17f154(state, state->de);  // 2
            case 0x3: return Function17f181(state, state->de);  // 3
            case 0x4: //dw ['Function17f1d0'];  // 4
            case 0x5: return Function17f220(state, state->de);  // 5
            case 0x6: //dw ['Function17f27b'];  // 6
            case 0x7: return Function17f2cb(state, state->de);  // 7
            case 0x8: return MobileScript_PlayerName(state, state->de);  // 8
            case 0x9: return MobileScript_Prefecture(state, state->de);  // 9
            case 0xa: return Function17f382(state, state->de);  // a
            case 0xb: return Function17f3c9(state, state->de);  // b
            case 0xc: return Function17f3f0(state, state->de);  // c
            case 0xd: //dw ['Function17f41d'];  // d
            case 0xe: return Function17f44f(state, state->de);  // e
            case 0xf: return Function17f44f(state, state->de);  // f
        }
        return false;
    }

// finished:
    // SCF;
    // RET;
    return true;
}

bool Function17f081(struct TextPrintState* state, uint8_t* saved){
    // POP_HL;
    state->hl = saved;
    // CALL(aFunction17f524);
    // IF_C goto asm_17f09f;
    if(Function17f524()) {
    // asm_17f09f:
        // PUSH_BC;
        // LD_DE(wcd54);
        // LD_BC(7);
        // CALL(aCopyBytes);
        CopyBytes(&wram->wcd54, state->hl, 7);
        // POP_BC;
        // PUSH_HL;
        uint8_t* hl = state->hl + 7;
        // PUSH_BC;
        uint8_t* bc = state->bc;
        // CALL(aFunction17f4f6);
        // POP_BC;
        // LD_A_addr(wcd54);
        // LD_E_A;
        // LD_A_addr(wcd55);
        // LD_D_A;
        // ADD_HL_DE;
        // LD_E_L;
        // LD_D_H;
        uint16_t de2 = Function17f4f6() + (wram->wcd54 | (wram->wcd55 << 8));
        // LD_L_C;
        // LD_H_B;
        // PUSH_HL;
        state->hl = bc;
        // LD_A_addr(wcd56);
        // LD_B_A;
        // LD_A_addr(wcd57);
        // LD_C_A;
        // CALL(aMobilePrintNum);
        state->hl = MobilePrintNum(state->hl, GBToRAMAddr(de2), wram->wcd56, wram->wcd57);
        // LD_A_L;
        // LD_addr_A(wcd52);
        // LD_A_H;
        // LD_addr_A(wcd53);
        gMobile_wcd52_wcd53 = state->hl;
        // LD_A_addr(wcd59);
        // AND_A_A;
        // IF_Z goto asm_17f0ee;
        if(wram->wcd59 != 0) {
            // LD_C_A;
            uint8_t c = wram->wcd59;
            // LD_A_addr(wcd57);
            // INC_A;
            // LD_B_A;
            uint8_t b = wram->wcd57 + 1;
            // LD_E_L;
            // LD_D_H;
            // DEC_DE;
            uint8_t* de = state->hl - 1;
        
            while(c != b) {
            // asm_17f0e0:
                // LD_A_C;
                // CP_A_B;
                // IF_Z goto asm_17f0ea;
                // LD_A_de;
                // DEC_DE;
                // LD_hld_A;
                *(state->hl--) = *(de--);
                // DEC_B;
                --b;
                // goto asm_17f0e0;
            }
        
        
        // asm_17f0ea:
            // LD_A_addr(wcd5a);
            // LD_hl_A;
            *state->hl = wram->wcd5a;
        }
    
    // asm_17f0ee:
        // POP_HL;
        state->hl = bc;
        // LD_A_addr(wcd58);
        // CALL(aFunction17f50f);
        Function17f50f(state, wram->wcd58);
        // POP_DE;
        state->de = hl;
        // AND_A_A;
        // RET;    
        return false;
    }
    else {
        // LD_DE(4);
        // ADD_HL_DE;
        state->hl += 4;
        // LD_A_hli;
        uint8_t a = *(state->hl++);
        // INC_HL;
        // INC_HL;
        state->hl += 2;
        // LD_E_L;
        // LD_D_H;
        state->de = state->hl;
        // LD_L_C;
        // LD_H_B;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        state->hl = state->bc + a;
        // LD_A_de;
        // CP_A(0x50);
        // IF_Z goto asm_17f09d;
        if(*state->de == 0x50)
            return true;
        // AND_A_A;
        // RET;

    // asm_17f09d:
        // SCF;
        // RET;
        return false;
    }
}

bool Function17f0f8(struct TextPrintState* state, uint8_t* saved){
    // POP_HL;
    state->hl = saved;
    // CALL(aFunction17f524);
    // IF_C goto asm_17f114;
    if(Function17f524()) {
    // asm_17f114:
        // PUSH_BC;
        // LD_DE(wcd54);
        // LD_BC(0x4);
        // CALL(aCopyBytes);
        CopyBytes(&wram->wcd54, state->hl, 0x4);
        state->hl += 0x4;
        // POP_BC;
        // PUSH_HL;
        uint8_t* hl = state->hl;
        // PUSH_BC;
        uint8_t* bc = state->bc;
        // CALL(aFunction17f4f6);
        // LD_A_addr(wcd54);
        // LD_E_A;
        // LD_A_addr(wcd55);
        // LD_D_A;
        // ADD_HL_DE;
        // LD_DE(wc608);
        // LD_A_addr(wcd56);
        // LD_C_A;
        // LD_B(0);
        // CALL(aCopyBytes);
        CopyBytes(wram->wc608, GBToRAMAddr(Function17f4f6() + (wram->wcd54 | (wram->wcd55 << 8))), wram->wcd56);
        // LD_A(0x50);
        // LD_de_A;
        wram->wc608[wram->wcd56] = 0x50;
        // POP_HL;
        state->hl = bc;
        // LD_DE(wc608);
        state->de = wram->wc608;
        // CALL(aPlaceString);
        PlaceString_Conv(state, state->hl);
        // LD_A_C;
        // LD_addr_A(wcd52);
        // LD_A_B;
        // LD_addr_A(wcd53);
        gMobile_wcd52_wcd53 = state->bc;
        // LD_A_addr(wcd57);
        // CALL(aFunction17f50f);
        Function17f50f(state, wram->wcd57);
        // POP_DE;
        state->de = hl;
        // AND_A_A;
        // RET;
        return false;
    }
    else {
        // LD_DE(0x3);
        // ADD_HL_DE;
        state->hl += 0x3;
        // LD_A_hli;
        uint8_t a = *(state->hl++);
        // LD_E_L;
        // LD_D_H;
        state->de = state->hl;
        // LD_L_C;
        // LD_H_B;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        state->hl = state->bc + a;
        // LD_A_de;
        // CP_A(0x50);
        // IF_Z goto asm_17f112;
        if(*state->de == 0x50) {
        // asm_17f112:
            // SCF;
            // RET;
            return true;
        }
        // AND_A_A;
        // RET;
        return false;
    }
}

bool Function17f154(struct TextPrintState* state, uint8_t* saved){
    // POP_HL;
    state->hl = saved;
    // CALL(aFunction17f524);
    // IF_C goto asm_17f167;
    if(Function17f524()) {
    // asm_17f167:
        // PUSH_BC;
        uint8_t* bc = state->bc;
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint16_t de = state->hl[0] | (state->hl[1] << 8);
        state->hl += 2;
        // POP_BC;
        // PUSH_HL;
        uint8_t* hl = state->hl;
        // PUSH_BC;
        // CALL(aFunction17f4f6);
        uint16_t hl2 = Function17f4f6();
        // ADD_HL_DE;
        // LD_C_L;
        // LD_B_H;
        // POP_DE;
        // FARCALL(aFunction11c08f);
        EZChat_RenderWords(bc, GBToRAMAddr(hl2 + de));
        // LD_C_L;
        // LD_B_H;
        // POP_DE;
        state->de = hl;
        // AND_A_A;
        // RET;
        return false;
    }
    else {
        // INC_HL;
        // INC_HL;
        state->hl += 2;
        // LD_E_L;
        // LD_D_H;
        state->de = state->hl;
        // LD_A_de;
        // CP_A(0x50);
        // IF_Z goto asm_17f165;
        if(*state->de != 0x50) {
            // AND_A_A;
            // RET;
            return false;
        }
        else {
        // asm_17f165:
            // SCF;
            // RET;
            return true;
        }
    }
}

bool Function17f181(struct TextPrintState* state, uint8_t* saved){
    // POP_HL;
    state->hl = saved;
    // CALL(aFunction17f524);
    // IF_C goto asm_17f19d;
    if(Function17f524()) {
    // asm_17f19d:
        // PUSH_BC;
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint16_t de2 = state->hl[0] | (state->hl[1] << 8);
        // LD_A_hli;
        // LD_addr_A(wcd54);
        wram->wcd54 = state->hl[2];
        state->hl += 3;
        // POP_BC;
        // PUSH_HL;
        uint8_t* hl = state->hl;
        // PUSH_BC;
        uint8_t* bc = state->bc;
        // CALL(aFunction17f4f6);
        // ADD_HL_DE;
        uint8_t* hl2 = GBToRAMAddr(Function17f4f6() + de2);
        // LD_A_hl;
        // LD_C_A;
        // LD_DE(wc608);
        // FARCALL(aFunction48c63);
        Function48c63(wram->wc608, *hl2);
        // POP_HL;
        state->hl = bc;
        // LD_DE(wc608);
        state->de = wram->wc608;
        // CALL(aPlaceString);
        PlaceString_Conv(state, state->hl);
        // LD_A_C;
        // LD_addr_A(wcd52);
        // LD_A_B;
        // LD_addr_A(wcd53);
        gMobile_wcd52_wcd53 = state->bc;
        // LD_A_addr(wcd54);
        // CALL(aFunction17f50f);
        Function17f50f(state, wram->wcd54);
        // POP_DE;
        state->de = hl;
        // AND_A_A;
        // RET;    
        return false;
    }
    else {
        // LD_DE(0x2);
        // ADD_HL_DE;
        state->hl += 2;
        // LD_A_hli;
        uint8_t a = *(state->hl++);
        // LD_E_L;
        // LD_D_H;
        state->de = state->hl;
        // LD_L_C;
        // LD_H_B;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        state->hl = state->bc + a;
        // LD_A_de;
        // CP_A(0x50);
        // IF_Z goto asm_17f19b;
        if(*state->de == 0x50) {
        // asm_17f19b:
            // SCF;
            // RET;
            return true;
        }
        // AND_A_A;
        // RET;
        return false;
    }
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

bool Function17f220(struct TextPrintState* state, uint8_t* saved){
    static const char *const Genders[] = {
    // dw .Boy, .Girl  
    // Boy:
        "Boy@",
    // Girl:
        "Girl@"
    };
    uint8_t buffer[0x10];
    // POP_HL;
    state->hl = saved;
    // CALL(aFunction17f524);
    // IF_C goto asm_17f23c;
    if(Function17f524()) {
    // asm_17f23c:
        // PUSH_BC;
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint16_t de = state->hl[0] | (state->hl[1] << 8);
        // LD_A_hli;
        // LD_addr_A(wcd54);
        wram->wcd54 = state->hl[2];
        state->hl += 3;
        // POP_BC;
        // PUSH_HL;
        uint8_t* hl = state->hl;
        // PUSH_BC;
        uint8_t* bc = state->bc;
        // CALL(aFunction17f4f6);
        // ADD_HL_DE;
        // LD_A_hl;
        uint8_t* gender = GBToRAMAddr(Function17f4f6() + de);
        // LD_E_A;
        // LD_D(0);
        // LD_HL(mFunction17f220_Genders);
        // ADD_HL_DE;
        // ADD_HL_DE;
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hl;
        // LD_D_A;
        state->de = U82CA(buffer, Genders[*gender & 0x1]);
        // POP_HL;
        state->hl = bc;
        // CALL(aPlaceString);
        PlaceString_Conv(state, state->hl);
        // LD_A_C;
        // LD_addr_A(wcd52);
        // LD_A_B;
        // LD_addr_A(wcd53);
        gMobile_wcd52_wcd53 = state->bc;
        // LD_A_addr(wcd54);
        // CALL(aFunction17f50f);
        Function17f50f(state, wram->wcd54);
        // POP_DE;
        state->de = hl;
        // AND_A_A;
        // RET;
        return false;
    }
    else {
        // LD_DE(0x2);
        // ADD_HL_DE;
        state->hl += 0x2;
        // LD_A_hli;
        uint8_t a = *(state->hl++);
        // LD_E_L;
        // LD_D_H;
        state->de = state->hl;
        // LD_L_C;
        // LD_H_B;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        state->hl = state->bc + a;
        // LD_A_de;
        // CP_A(0x50);
        // IF_Z goto asm_17f23a;
        if(*state->de == 0x50) {
        // asm_17f23a:
            // SCF;
            // RET;
            return true;
        }
        // AND_A_A;
        // RET;
        return false;
    }
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

bool Function17f2cb(struct TextPrintState* state, uint8_t* saved){
    // POP_HL;
    state->hl = saved;
    // PUSH_BC;
    uint8_t* bc = state->bc;
    // LD_A_hli;
    // LD_addr_A(wcd54);
    wram->wcd54 = state->hl[0];
    // LD_A_hli;
    // LD_addr_A(wcd55);
    wram->wcd55 = state->hl[1];
    state->hl += 2;
    // LD_A_addr(wcd2e);
    // INC_A;
    // LD_addr_A(wcd56);
    wram->wcd56 = wram->wcd2e + 1;
    // POP_BC;
    // PUSH_HL;
    uint8_t* hl = state->hl;
    // LD_L_C;
    // LD_H_B;
    // PUSH_HL;
    uint8_t* hl2 = bc;
    // LD_DE(wcd56);
    // LD_B(0x1);
    // LD_A_addr(wcd54);
    // LD_C_A;
    // CALL(aMobilePrintNum);
    hl2 = MobilePrintNum(hl2, &wram->wcd56, 0x1, wram->wcd54);
    // LD_A_L;
    // LD_addr_A(wcd52);
    // LD_A_H;
    // LD_addr_A(wcd53);
    gMobile_wcd52_wcd53 = hl2;
    // POP_HL;
    state->hl = bc;
    // LD_A_addr(wcd55);
    // CALL(aFunction17f50f);
    Function17f50f(state, wram->wcd55);
    // POP_DE;
    state->de = hl;
    // AND_A_A;
    // RET;
    return false;
}

bool MobileScript_PlayerName(struct TextPrintState* state, uint8_t* saved){
    // POP_HL;
    state->hl = saved;
    // PUSH_BC;
    // LD_A_hli;
    // LD_addr_A(wcd54);
    wram->wcd54 = *(state->hl++);
    // POP_BC;
    // PUSH_HL;
    saved = state->hl;
    // PUSH_BC;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // LD_HL(wPlayerName);
    // LD_DE(wc608);
    // LD_BC(NAME_LENGTH_JAPANESE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wc608, wram->wPlayerName, NAME_LENGTH);
    // LD_A(0x4);
    // LDH_addr_A(rSVBK);
    // POP_HL;
    state->hl = state->bc;
    // LD_DE(wc608);
    state->de = wram->wc608;
    // CALL(aPlaceString);
    PlaceString_Conv(state, state->hl);
    // LD_A_C;
    // LD_addr_A(wcd52);
    // LD_A_B;
    // LD_addr_A(wcd53);
    gMobile_wcd52_wcd53 = state->bc;
    // LD_A_addr(wcd54);
    // CALL(aFunction17f50f);
    Function17f50f(state, wram->wcd54);
    // POP_DE;
    state->de = saved;
    // AND_A_A;
    // RET;
    return false;
}

bool MobileScript_Prefecture(struct TextPrintState* state, uint8_t* saved){
    // POP_HL;
    state->hl = saved;
    // PUSH_BC;
    // LD_A_hli;
    // LD_addr_A(wcd55);
    wram->wcd55 = *(state->hl++);
    // AND_A(0xf);
    // LD_addr_A(wcd54);
    wram->wcd54 = wram->wcd55 & 0xf;
    // POP_BC;
    // PUSH_HL;
    saved = state->hl;
    // LD_L_C;
    // LD_H_B;
    // PUSH_HL;
    state->hl = state->bc;
    // LD_A_addr(wcd55);
    // BIT_A(7);
    // IF_NZ goto asm_17f355;
    uint8_t c;
    if(bit_test(wram->wcd55, 7)) {
    // asm_17f355:
        // LD_A(BANK(s5_b2f3));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(as5_b2f3));
        // LD_A_addr(s5_b2f3);
        c = gb_read(s5_b2f3);
    }
    else {
        // LD_A(BANK(sCrystalData));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(asCrystalData));
        // LD_A_addr(sCrystalData + 2);
        // goto asm_17f35d;
        c = gb_read(sCrystalData + 2);
    }

// asm_17f35d:
    // LD_C_A;
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_DE(wc608);
    // FARCALL(aFunction48c63);
    Function48c63(wram->wc608, c);
    // POP_HL;
    // LD_DE(wc608);
    state->de = wram->wc608;
    // CALL(aPlaceString);
    PlaceString_Conv(state, state->hl);
    // LD_A_C;
    // LD_addr_A(wcd52);
    // LD_A_B;
    // LD_addr_A(wcd53);
    gMobile_wcd52_wcd53 = state->bc;
    // LD_A_addr(wcd54);
    // CALL(aFunction17f50f);
    Function17f50f(state, wram->wcd54);
    // POP_DE;
    state->de = saved;
    // AND_A_A;
    // RET;
    return false;

}

// MobileScript_ZipCode
bool Function17f382(struct TextPrintState* state, uint8_t* saved){
    // POP_HL;
    state->hl = saved;
    // PUSH_BC;
    uint8_t* bc = state->bc;
    // LD_A_hli;
    // LD_addr_A(wcd55);
    wram->wcd55 = *(state->hl++);
    // AND_A(0xf);
    // LD_addr_A(wcd54);
    wram->wcd54 = wram->wcd55 & 0xf;
    // POP_BC;
    // PUSH_HL;
    // PUSH_BC;
    uint8_t* hl2 = state->hl;
    // LD_L_C;
    // LD_H_B;
    uint8_t* hl = state->bc;
    // LD_A_addr(wcd55);
    // BIT_A(7);
    // IF_NZ goto asm_17f3a3;
    uint8_t* de;
    uint8_t pref;
    if(!bit_test(wram->wcd55, 7)) {
        // LD_A(BANK(sCrystalData));
        // CALL(aOpenSRAM);
        // OpenSRAM_Conv(MBANK(asCrystalData));
        // LD_DE(sCrystalData + 3);
        // de = GBToRAMAddr(sCrystalData + 3);
        OpenSRAM_Conv(MBANK(as5_b2f4));
        de = GBToRAMAddr(s5_b2f4);
        pref = wram->wPrefecture;
        // goto asm_17f3ab;
    }
    else {
    // asm_17f3a3:
        // LD_A(BANK(s5_b2f4));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(as5_b2f4));
        // LD_DE(s5_b2f4);
        de = GBToRAMAddr(s5_b2f4);
        pref = gb_read(s5_b2f3);
    }

// asm_17f3ab:
    // LD_A(PRINTNUM_LEADINGZEROS | 2);
    // LD_B_A;
    // LD_A(3);
    // LD_C_A;
    // CALL(aPrintNum);
// .display
    RetrieveZipcodeInfo(pref);
	// We can't just use PrintText, because there may be no "@" at the end of the wZipCode (because I wanted to save 1 stupid byte of WRAM...).
	// ld b, ZIPCODE_LENGTH + 1
    for(uint8_t b = 0; b < wram->wZipcodeFormatLength; ++b) {
    // .display_loop
        // dec b
        // jr z, .display_done

        // ld a, [de]
        uint8_t a = Mobile12_Index2Char(b, *de);
        // cp "@"
        // jr z, .display_done

        // cp -1
        // jr nz, .no_overflow
        // if(a == 0xff) {
            // ld a, "0"
            // a = 0xf6;
        // }

    // .no_overflow
        // ld [hli], a
        *(hl++) = a;
        // inc de
        de++;
        // jr .display_loop
    }

// .display_done
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // LD_A_L;
    // LD_addr_A(wcd52);
    // LD_A_H;
    // LD_addr_A(wcd53);
    gMobile_wcd52_wcd53 = hl;
    // POP_HL;
    state->hl = bc;
    // LD_A_addr(wcd54);
    // CALL(aFunction17f50f);
    Function17f50f(state, 0);
    // POP_DE;
    state->de = hl2;
    // AND_A_A;
    // RET;
    return false;
}

bool Function17f3c9(struct TextPrintState* state, uint8_t* saved){
    // PUSH_BC;
    uint8_t* bc = state->bc;
    // LD_HL(wcd36);
    // LD_DE(wc708);
    // LD_BC(12);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wc708, &wram->wcd36, 12);
    // POP_DE;
    // LD_C(0x0);
    // FARCALL(aFunction11c075);
    Function11c075(bc, 0x0);
    // PUSH_HL;
    uint8_t* hl = bc + 4 * SCREEN_WIDTH;
    // LD_HL(wc708);
    // LD_DE(wcd36);
    // LD_BC(12);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wcd36, &wram->wc708, 12);
    // POP_BC;
    state->bc = hl;
    // POP_DE;
    state->de = saved;
    // AND_A_A;
    // RET;
    return false;
}

bool Function17f3f0(struct TextPrintState* state, uint8_t* saved){
    // POP_HL;
    // PUSH_HL;
    state->hl = saved;
    printf("[%02x %02x%02x %02x%02x %02x%02x %02x%02x]",
        state->hl[0], state->hl[1], state->hl[2], state->hl[3],
        state->hl[4], state->hl[5], state->hl[6], state->hl[7],
        state->hl[8]);
    // LD_A_hli;
    // PUSH_AF;
    uint8_t a = *(state->hl++);
    printf("news_text_switch %d", a);
    // PUSH_BC;
    uint8_t* hl = state->bc;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint8_t* de = GBToRAMAddr(state->hl[0] | (state->hl[1] << 8));
    printf(", 0x%x", state->hl[0] | (state->hl[1] << 8));
    state->hl += 2;
    // LD_A_de;
    // LD_C_A;
    uint8_t c = *de;
    printf(" (%d)", c);
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    state->hl += 2 * c;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // LD_HL(wBGPals1);
    // ADD_HL_DE;
    // LD_E_L;
    // LD_D_H;
    state->de = wram->wram4 + (state->hl[0] | (state->hl[1] << 8));
    printf(", 0x%x\n", state->hl[0] | (state->hl[1] << 8));
    // POP_HL;
    state->hl = hl;
    // CALL(aPlaceString);
    PlaceString_Conv(state, state->hl);
    // POP_AF;
    // LD_E_A;
    // LD_D(0);
    // POP_HL;
    // ADD_HL_DE;
    // ADD_HL_DE;
    // INC_HL;
    // INC_HL;
    // INC_HL;
    // LD_E_L;
    // LD_D_H;
    state->de = saved + 2*a + 3;
    // LD_L_C;
    // LD_H_B;
    state->hl = state->bc;
    // SCF;
    // RET;
    return true;
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

bool Function17f44f(struct TextPrintState* state, uint8_t* saved){
    uint8_t svbk = gb_read(rSVBK);
    // POP_HL;
    state->hl = saved;
    // CALL(aFunction17f524);
    // IF_C goto asm_17f46d;
    if(Function17f524()) {
    // asm_17f46d:
        // PUSH_BC;
        // LD_DE(wcd54);
        // LD_BC(0x8);
        // CALL(aCopyBytes);
        CopyBytes(&wram->wcd54, state->hl, 0x8);
        // POP_BC;
        // PUSH_HL;
        uint8_t* hl = state->hl + 0x8;
        // PUSH_BC;
        uint8_t* bc = state->bc;
        // LD_A_addr(wcd56);
        // CP_A(0xc0);
        // IF_C goto asm_17f488;
        if(wram->wcd56 < 0xc0) {
        // asm_17f488:
            // LD_A_addr(wcd54);
            // CALL(aOpenSRAM);
            OpenSRAM_Conv(wram->wcd54);
        }
        else {
            // LD_A_addr(wcd54);
            // LDH_addr_A(rSVBK);
            gb_write(rSVBK, wram->wcd54);
            // goto asm_17f48e;
        }
    
    // asm_17f48e:
        // LD_A_addr(wcd55);
        // LD_L_A;
        // LD_A_addr(wcd56);
        // LD_H_A;
        // LD_DE(wc608);
        // LD_A_addr(wcd57);
        // LD_C_A;
        // LD_B(0);
        // CALL(aCopyBytes);
        CopyBytes(wram->wc608, GBToRAMAddr(wram->wcd55 | (wram->wcd56 << 8)), wram->wcd57);
        // LD_A_addr(wcd56);
        // CP_A(0xc0);
        // IF_C goto asm_17f4af;
        if(wram->wcd56 < 0xc0) {
            // LD_A(0x4);
            // LDH_addr_A(rSVBK);
            gb_write(rSVBK, svbk);
            // goto asm_17f4b7;
        }
        else {
        // asm_17f4af:
            // CALL(aCloseSRAM);
            CloseSRAM_Conv();
            // LD_A(0x6);
            // CALL(aOpenSRAM);
            OpenSRAM_Conv(MBANK(as6_a000));
        }
    
    // asm_17f4b7:
        // LD_DE(wc608);
        // POP_HL;
        // PUSH_HL;
        // LD_A_addr(wcd57);
        // LD_B_A;
        // LD_A_addr(wcd58);
        // LD_C_A;
        // CALL(aMobilePrintNum);
        uint8_t* hl2 = MobilePrintNum(bc, wram->wc608, wram->wcd57, wram->wcd58);
        // LD_A_L;
        // LD_addr_A(wcd52);
        // LD_A_H;
        // LD_addr_A(wcd53);
        gMobile_wcd52_wcd53 = hl2;
        // LD_A_addr(wcd5a);
        // AND_A_A;
        // IF_Z goto asm_17f4ec;
        if(wram->wcd5a != 0) {
            // LD_C_A;
            uint8_t c = wram->wcd5a;
            // LD_A_addr(wcd58);
            // INC_A;
            // LD_B_A;
            uint8_t b = wram->wcd58 + 1;
            // LD_E_L;
            // LD_D_H;
            // DEC_DE;
            uint8_t* de = hl2 - 1;
        
            while(c != b) {
            // asm_17f4de:
                // LD_A_C;
                // CP_A_B;
                // IF_Z goto asm_17f4e8;
                // LD_A_de;
                // DEC_DE;
                // LD_hld_A;
                *(hl2--) = *(de--);
                // DEC_B;
                --b;
                // goto asm_17f4de;
            }
        
        // asm_17f4e8:
            // LD_A_addr(wcd5b);
            // LD_hl_A;
            *hl2 = wram->wcd5b;
        }
    
    // asm_17f4ec:
        // POP_HL;
        state->hl = bc;
        // LD_A_addr(wcd59);
        // CALL(aFunction17f50f);
        Function17f50f(state, wram->wcd59);
        // POP_DE;
        state->de = hl;
        // AND_A_A;
        // RET;
        return false;
    }
    else {
        // LD_DE(0x5);
        // ADD_HL_DE;
        state->hl += 0x5;
        // LD_A_hli;
        uint8_t a = *(state->hl++);
        // INC_HL;
        // INC_HL;
        // LD_E_L;
        // LD_D_H;
        state->de = state->hl + 2;
        // LD_L_C;
        // LD_H_B;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        state->hl = state->bc + a;
        // LD_A_de;
        // CP_A(0x50);
        // IF_Z goto asm_17f46b;
        if(*state->de == 0x50) {
        // asm_17f46b:
            // SCF;
            // RET;
            return true;
        }
        // AND_A_A;
        // RET;
        return false;
    }
}

uint16_t Function17f4f6(void){
    // LD_A_addr(wcd6a);
    // LD_L_A;
    // LD_A_addr(wcd6b);
    // LD_H_A;
    uint16_t hl = wram->wcd6a | (wram->wcd6b << 8);
    // LD_A_addr(wcd47);
    // LD_C_A;
    // LD_A_addr(wBGMapPalBuffer);
    // LD_B_A;
    uint16_t bc = wram->wcd47 | (wram->wcd48 << 8);
    // LD_A_addr(wcd2e);

// asm_17f509:
    // AND_A_A;
    // RET_Z ;
    // DEC_A;
    // ADD_HL_BC;
    hl += bc * wram->wcd2e;
    // goto asm_17f509;
    return hl;
}

void Function17f50f(struct TextPrintState* state, uint8_t a){
    // AND_A_A;
    // IF_Z goto asm_17f519;
    if(a != 0) {
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        state->hl += a;
        // LD_C_L;
        // LD_B_H;
        state->bc = state->hl;
        // RET;
    }
    else {
    // asm_17f519:
        // LD_A_addr(wcd52);
        // LD_C_A;
        // LD_L_A;
        // LD_A_addr(wcd53);
        // LD_B_A;
        // LD_H_A;
        state->hl = state->bc = gMobile_wcd52_wcd53;
        // RET;
    }
}

bool Function17f524(void){
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_DE;
    // LD_A_addr(wcd42);
    // DEC_A;
    // LD_B_A;
    // LD_A_addr(wcd2e);
    // CP_A_B;
    // IF_Z goto asm_17f53a;
    if(wram->wcd2e == wram->wcd42 - 1) {
    // asm_17f53a:
        // SCF;
        // goto asm_17f536;
        return true;
    }
    // LD_HL(wcd68);
    // CP_A_hl;

// asm_17f536:
    // POP_DE;
    // POP_BC;
    // POP_HL;
    // RET;
    return wram->wcd2e < wram->wcd68;
}

void BattleTowerMobileError(void){
    // CALL(aFadeToMenu);
    FadeToMenu_Conv();
    // XOR_A_A;
    // LD_addr_A(wc303);
    wram->wc303 = 0x0;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);

    // CALL(aDisplayMobileError);
    DisplayMobileError();

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aExitAllMenus);
    ExitAllMenus_Conv();
    // RET;

}

static void DisplayMobileError_RunJumptable(void) {
    //jumptable ['.Jumptable', 'wc303']
    switch(wram->wc303) {
    // Jumptable:
        default:
        case 0: Function17f5c3(); break;
        case 1: Function17ff23(); break;
        case 2: Function17f5d2(); break;
    }
}

static void DisplayMobileError_deinit(void){
    // LD_A_addr(wMobileErrorCodeBuffer);
    uint8_t error0 = wram->wMobileErrorCodeBuffer[0];
    // CP_A(0x22);
    // IF_Z goto asm_17f597;
    if(error0 == 0x22) {
    // asm_17f597:
        // LD_A_addr(wMobileErrorCodeBuffer + 1);
        // AND_A_A;
        // RET_NZ ;
        // LD_A_addr(wMobileErrorCodeBuffer + 2);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wMobileErrorCodeBuffer[1] != 0 || wram->wMobileErrorCodeBuffer[2] != 0)
            return;
    }
    // CP_A(0x31);
    // IF_Z goto asm_17f58a;
    else if(error0 == 0x31) {
    // asm_17f58a:
        // LD_A_addr(wMobileErrorCodeBuffer + 1);
        // CP_A(0x3);
        // RET_NZ ;
        // LD_A_addr(wMobileErrorCodeBuffer + 2);
        // AND_A_A;
        // RET_NZ ;
        if(wram->wMobileErrorCodeBuffer[1] != 0x3 || wram->wMobileErrorCodeBuffer[2] != 0)
            return;
        // goto asm_17f5a1;
    }
    else {
        // CP_A(0x33);
        // RET_NZ ;
        // LD_A_addr(wMobileErrorCodeBuffer + 1);
        // CP_A(0x1);
        // RET_NZ ;
        // LD_A_addr(wMobileErrorCodeBuffer + 2);
        // CP_A(0x2);
        // RET_NZ ;
        if(error0 != 0x33 || wram->wMobileErrorCodeBuffer[1] != 0x1 || wram->wMobileErrorCodeBuffer[2] != 0x2)
            return;
        // goto asm_17f5a1;
    }

// asm_17f5a1:
    // LD_A(BANK(sMobileLoginPassword));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMobileLoginPassword));
    // XOR_A_A;
    // LD_addr_A(sMobileLoginPassword);
    gb_write(sMobileLoginPassword, 0x0);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void DisplayMobileError(void){
    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay_Conv();
        // CALL(aDisplayMobileError_RunJumptable);
        DisplayMobileError_RunJumptable();
        // LD_A_addr(wc303);
        // BIT_A(7);
        // IF_NZ goto quit;
        if(bit_test(wram->wc303, 7))
            break;
        // FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
        HDMATransferAttrmapAndTilemapToWRAMBank3_Conv();
        // goto loop;
    }

// quit:
    // CALL(aDisplayMobileError_deinit);
    DisplayMobileError_deinit();
    // RET;
}

void Function17f5c3(void){
    // CALL(aFunction17f5e4);
    Function17f5e4();
    // FARCALL(aFinishExitMenu);
    FinishExitMenu_Conv();
    // LD_A(0x1);
    // LD_addr_A(wc303);
    wram->wc303 = 0x1;
    // RET;
}

void Function17f5d2(void){
    // CALL(aFunction17f5e4);
    Function17f5e4();
    // FARCALL(aHDMATransferAttrmapAndTilemapToWRAMBank3);
    HDMATransferAttrmapAndTilemapToWRAMBank3_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // LD_A(0x1);
    // LD_addr_A(wc303);
    wram->wc303 = 0x1;
    // RET;

}

// Mobile_PrintErrorMessage?
void Function17f5e4(void){
    // LD_A(0x8);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0x8;
    // LD_DE(MUSIC_NONE);
    // LD_A_E;
    // LD_addr_A(wMusicFadeID);
    // LD_A_D;
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_NONE;
    // LD_A(0x7f);
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, CHAR_SPACE);
    // LD_A(0x6);
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x6);
    // hlcoord(2, 1, wTilemap);
    // LD_B(0x1);
    // LD_C(0xe);
    // CALL(aFunction3eea);
    Function3eea(coord(2, 1, wram->wTilemap), 0x1, 0xe);
    // hlcoord(1, 4, wTilemap);
    // LD_B(0xc);
    // LD_C(0x10);
    // CALL(aFunction3eea);
    Function3eea(coord(0, 4, wram->wTilemap), 0xc, 0x12);
    // hlcoord(3, 2, wTilemap);
    // LD_DE(mMobileCommunicationErrorText);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(MobileCommunicationErrorText), coord(3, 2, wram->wTilemap));
    // CALL(aFunction17ff3c);
    // IF_NC goto asm_17f632;
    if(Function17ff3c()) {
        // hlcoord(11, 2, wTilemap);
        // CALL(aFunction17f6b7);
        Function17f6b7(coord(11, 2, wram->wTilemap));
    }

// asm_17f632:
    // LD_A_addr(wMobileErrorCodeBuffer);
    uint8_t error = wram->wMobileErrorCodeBuffer[0];
    // CP_A(0xd0);
    // IF_NC goto asm_17f684;
    if(error < 0xd0) {
        // CP_A(0x10);
        // IF_C goto asm_17f679;
        // SUB_A(0x10);
        // CP_A(0x24);
        // IF_NC goto asm_17f679;
        if(error < 0x10 || error - 0x10 >= 0x24)
            goto asm_17f679;
        // LD_E_A;
        // LD_D(0);
        // LD_HL(mMobileErrorCodeTable);
        // ADD_HL_DE;
        // ADD_HL_DE;
        const errcodes_s* codes = MobileErrorCodeTable[error - 0x10];
        // LD_A_addr(wMobileErrorCodeBuffer + 1);
        // LD_E_A;
        // LD_A_addr(wMobileErrorCodeBuffer + 2);
        // LD_D_A;
        uint16_t target = (wram->wMobileErrorCodeBuffer[2]) | (wram->wMobileErrorCodeBuffer[1] << 8);
        // LD_A_hli;
        // LD_C_A;
        // LD_A_hl;
        // LD_H_A;
        // LD_L_C;
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto asm_17f679;
        if(codes->count == 0)
            goto asm_17f679;
        // LD_C_A;
        uint8_t c = codes->count;
        const errcode_s* hl = codes->codes;

        do {
        // asm_17f65d:
            // LD_A_hli;
            // LD_B_A;
            // LD_A_hli;
            // CP_A(0xff);
            // IF_NZ goto asm_17f667;
            // CP_A_B;
            // IF_Z goto asm_17f66e;

        // asm_17f667:
            // XOR_A_D;
            // IF_NZ goto asm_17f674;
            // LD_A_B;
            // XOR_A_E;
            // IF_NZ goto asm_17f674;

            if(hl->code == (uint16_t)-1 || hl->code == target) {
            // asm_17f66e:
                // LD_A_hli;
                // LD_E_A;
                // LD_A_hl;
                // LD_D_A;
                // goto asm_17f67d;
            // asm_17f67d:
                // hlcoord(2, 6, wTilemap);
                // CALL(aPlaceString);
                PlaceStringSimple(U82C(hl->text), coord(1, 6, wram->wTilemap));
                // RET;
                return;
            }


        // asm_17f674:
            // INC_HL;
            // INC_HL;
            hl++;
            // DEC_C;
            // IF_NZ goto asm_17f65d;
        } while(--c != 0);

    asm_17f679:
        // LD_A(0xd9);
        error = 0xd9;
        // goto asm_17f684;
    }

// asm_17f684:
    // SUB_A(0xd0);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mTable_17f699);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hl;
    // LD_D_A;
    // hlcoord(2, 6, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Table_17f699[error - 0xd0]), coord(1, 6, wram->wTilemap));
    // RET;
}

// MobileErrorCode_101_Table
const char* const Table_17f699[] = {
    MobileErrorCode_101_000_Text,
    MobileErrorCode_101_001_Text,
    MobileErrorCode_101_002_Text,
    MobileErrorCode_101_003_Text,
    MobileErrorCode_101_004_Text,
    MobileErrorCode_101_005_Text,
    MobileErrorCode_101_006_Text,
    MobileErrorCode_101_007_Text,
    MobileErrorCode_101_008_Text,
    MobileErrorCode_101_009_Text,
    MobileErrorCode_101_009_Text,
};

void Palette_17f6af(void){
//  //  unreferenced
    //rgb ['5', '5', '16']
    //rgb ['8', '19', '28']
    //rgb ['0', '0', '0']
    //rgb ['31', '31', '31']
}

static tile_t* Function17f6b7_bcd_digit(tile_t* hl, uint8_t a) {
    // ADD_A(0xf6);
    // LD_hli_A;
    *(hl++) = a + CHAR_0;
    // RET;
    return hl;
}

static tile_t* Function17f6b7_bcd_two_digits(tile_t* hl, uint8_t a) {
    // LD_C_A;
    // AND_A(0xf0);
    // SWAP_A;
    // CALL(aFunction17f6b7_bcd_digit);
    hl = Function17f6b7_bcd_digit(hl, (a & 0xf0) >> 4);
    // LD_A_C;
    // AND_A(0xf);
    return Function17f6b7_bcd_digit(hl, a & 0xf);
}

// Mobile_PrintErrorCodeDigits
void Function17f6b7(tile_t* hl){
    // LD_A_addr(wMobileErrorCodeBuffer);
    // CALL(aFunction17f6b7_bcd_two_digits);
    hl = Function17f6b7_bcd_two_digits(hl, wram->wMobileErrorCodeBuffer[0]);
    // INC_HL;
    hl++;
    // LD_A_addr(wMobileErrorCodeBuffer + 2);
    // AND_A(0xf);
    // CALL(aFunction17f6b7_bcd_digit);
    hl = Function17f6b7_bcd_digit(hl, wram->wMobileErrorCodeBuffer[2] & 0xf);
    // LD_A_addr(wMobileErrorCodeBuffer + 1);
    // CALL(aFunction17f6b7_bcd_two_digits);
    Function17f6b7_bcd_two_digits(hl, wram->wMobileErrorCodeBuffer[1]);
    // RET;
}

const char MobileCommunicationErrorText[] = "ERROR:    -@";//db ['"つうしんエラー\u3000\u3000\u3000ー@"'];

void String_17f6e8(void){
//  //  unreferenced
    //db ['"みていぎ<NO>エラーです"'];
    //next ['"プログラム<WO>"']
    //next ['"かくにん\u3000してください"']
    //db ['"@"'];
}

const errcodes_s* MobileErrorCodeTable[] = {
    &MobileErrorCodes_10,
    &MobileErrorCodes_11,
    &MobileErrorCodes_12,
    &MobileErrorCodes_13,
    &MobileErrorCodes_14,
    &MobileErrorCodes_15,
    &MobileErrorCodes_16,
    &MobileErrorCodes_17,
    &MobileErrorCodes_20,
    &MobileErrorCodes_20,
    &MobileErrorCodes_20,
    &MobileErrorCodes_20,
    &MobileErrorCodes_20,
    &MobileErrorCodes_20,
    &MobileErrorCodes_20,
    &MobileErrorCodes_20,
    &MobileErrorCodes_20,
    &MobileErrorCodes_21,
    &MobileErrorCodes_22,
    &MobileErrorCodes_23,
    &MobileErrorCodes_24,
    &MobileErrorCodes_25,
    &MobileErrorCodes_26,
    &MobileErrorCodes_30,
    &MobileErrorCodes_30,
    &MobileErrorCodes_30,
    &MobileErrorCodes_30,
    &MobileErrorCodes_30,
    &MobileErrorCodes_30,
    &MobileErrorCodes_30,
    &MobileErrorCodes_30,
    &MobileErrorCodes_30,
    &MobileErrorCodes_30,
    &MobileErrorCodes_31,
    &MobileErrorCodes_32,
    &MobileErrorCodes_33,
};

const errcodes_s MobileErrorCodes_10 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_10_000_Text},
    },
};

const errcodes_s MobileErrorCodes_11 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_11_000_Text},
    },
};

const errcodes_s MobileErrorCodes_12 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_12_000_Text},
    },
};

const errcodes_s MobileErrorCodes_13 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_13_000_Text},
    },
};

const errcodes_s MobileErrorCodes_14 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_14_000_Text},
    },
};

const errcodes_s MobileErrorCodes_15 = {
//db 4
    .count = 4,
    .codes = {
        {0x000, MobileErrorCode_15_000_Text},
        {0x001, MobileErrorCode_15_001_Text},
        {0x002, MobileErrorCode_15_002_Text},
        {0x003, MobileErrorCode_15_003_Text},
    },
};

const errcodes_s MobileErrorCodes_16 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_CommuncationErrorText},
    },
};

const errcodes_s MobileErrorCodes_17 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_CommuncationErrorText},
    },
};

const errcodes_s MobileErrorCodes_20 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_CommuncationErrorText},
    },
};

const errcodes_s MobileErrorCodes_21 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_CommuncationErrorText},
    },
};

const errcodes_s MobileErrorCodes_22 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_22_000_Text},
    },
};

const errcodes_s MobileErrorCodes_23 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_23_000_Text},
    },
};

const errcodes_s MobileErrorCodes_24 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_ServerConnectionFailedText},
    },
};

const errcodes_s MobileErrorCodes_25 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_25_000_Text},
    },
};

const errcodes_s MobileErrorCodes_26 = {
//db 1
    .count = 1,
    .codes = {
        {0x000, MobileErrorCode_26_000_Text},
    },
};

const errcodes_s MobileErrorCodes_30 = {
//db 17
    .count = 17,
    .codes = {
        {0x000,         MobileErrorCode_CommuncationErrorText},
        {0x221,         MobileErrorCode_ServerConnectionFailedText},
        {0x421,         MobileErrorCode_ServerConnectionFailedText},
        {0x450,         MobileErrorCode_30_450_Text},
        {0x451,         MobileErrorCode_ServerConnectionFailedText},
        {0x452,         MobileErrorCode_ServerConnectionFailedText},
        {0x500,         MobileErrorCode_CommuncationErrorText},
        {0x501,         MobileErrorCode_CommuncationErrorText},
        {0x502,         MobileErrorCode_CommuncationErrorText},
        {0x503,         MobileErrorCode_CommuncationErrorText},
        {0x504,         MobileErrorCode_CommuncationErrorText},
        {0x550,         MobileErrorCode_30_550_Text},
        {0x551,         MobileErrorCode_30_551_Text},
        {0x552,         MobileErrorCode_ServerConnectionFailedText},
        {0x553,         MobileErrorCode_30_553_Text},
        {0x554,         MobileErrorCode_ServerConnectionFailedText},
        {(uint16_t)-1,  MobileErrorCode_ServerConnectionFailedText},
    },
};

const errcodes_s MobileErrorCodes_31 = {
//db 5
    .count = 5,
    .codes = {
        {0x000,         MobileErrorCode_CommuncationErrorText},
        {0x002,         MobileErrorCode_31_002_Text},
        {0x003,         MobileErrorCode_31_003_Text},
        {0x004,         MobileErrorCode_CommuncationErrorText},
        {(uint16_t)-1,  MobileErrorCode_ServerConnectionFailedText},
    },
};

const errcodes_s MobileErrorCodes_32 = {
//db 17
    .count = 17,
    .codes = {
        {0x000,         MobileErrorCode_CommuncationErrorText},
        {0x301,         MobileErrorCode_CommuncationErrorText},
        {0x302,         MobileErrorCode_CommuncationErrorText},
        {0x400,         MobileErrorCode_CommuncationErrorText},
        {0x401,         MobileErrorCode_CommuncationErrorText},
        {0x403,         MobileErrorCode_ReadDataErrorText},
        {0x404,         MobileErrorCode_ReadDataErrorText},
        {0x405,         MobileErrorCode_CommuncationErrorText},
        {0x406,         MobileErrorCode_CommuncationErrorText},
        {0x407,         MobileErrorCode_CommuncationErrorText},
        {0x408,         MobileErrorCode_32_408_Text},
        {0x500,         MobileErrorCode_ServerErrorText},
        {0x501,         MobileErrorCode_CommuncationErrorText},
        {0x502,         MobileErrorCode_ServerErrorText},
        {0x503,         MobileErrorCode_32_503_Text},
        {0x504,         MobileErrorCode_ServerErrorText},
        {(uint8_t)-1,   MobileErrorCode_ServerErrorText},
    },
};

const errcodes_s MobileErrorCodes_33 = {
//db 19
    .count = 19,
    .codes = {
        {0x101,         MobileErrorCode_33_101_Text},
        {0x102,         MobileErrorCode_33_102_Text},
        {0x103,         MobileErrorCode_33_103_Text},
        {0x104,         MobileErrorCode_33_104_Text},
        {0x105,         MobileErrorCode_33_105_Text},
        {0x106,         MobileErrorCode_33_106_Text},
        {0x201,         MobileErrorCode_33_201_Text},
        {0x202,         MobileErrorCode_CommuncationErrorText},
        {0x203,         MobileErrorCode_33_203_Text},
        {0x204,         MobileErrorCode_CommuncationErrorText},
        {0x205,         MobileErrorCode_ServerErrorText},
        {0x206,         MobileErrorCode_33_206_Text},
        {0x299,         MobileErrorCode_33_299_Text},
        {0x301,         MobileErrorCode_ServerErrorText},
        {0x401,         MobileErrorCode_ServerErrorText},
        {0x402,         MobileErrorCode_ServerErrorText},
        {0x403,         MobileErrorCode_ServerErrorText},
        {0x404,         MobileErrorCode_ServerErrorText},
        {(uint8_t)-1,   MobileErrorCode_ServerErrorText},
    },
};

//  The Mobile Adapter is not properly plugged in.
//  Ensure you have taken a good look at and properly followed the instructions.
const char MobileErrorCode_10_000_Text[] = 
            "The Mobile Adapter"    //db ['"モバイルアダプタが\u3000ただしく"'];
    t_next  "is not connected"      //next ['"さしこまれていません"']
    t_next  "properly."             //next ['"とりあつかいせつめいしょを"']
    t_next  "Please check the"      //next ['"ごらんのうえ\u3000しっかりと"']
    t_next  "manual.@";             //next ['"さしこんで\u3000ください"']
    //db ['"@"'];

// void MobileErrorCode_11_000_Text(void){
//     return MobileErrorCode_13_000_Text();
// }

//  Could not connect because either the phone cannot make the call, or the telephone line is busy.
//  Please wait for a while and call again.
const char MobileErrorCode_13_000_Text[] = 
            "Could not connect"     //db ['"でんわが\u3000うまく\u3000かけられないか"'];
    t_next  "because the line"      //next ['"でんわかいせんが\u3000こんでいるので"']
    t_next  "is busy."              //next ['"つうしん\u3000できません"']
    t_next  "Please try again"      //next ['"しばらく\u3000まって"']
    t_next  "later.@";              //next ['"かけなおして\u3000ください"']
    //db ['"@"'];

//  As the telephone line is busy, the phone was not able to gather enough information (?)
//  Please wait for a while and call again.
const char MobileErrorCode_12_000_Text[] =
            "Could not connect"     //db ['"でんわかいせんが\u3000こんでいるため"'];
    t_next  "due to a high"         //next ['"でんわが\u3000かけられません"']
    t_next  "volume of calls."      //next ['"しばらく\u3000まって"']
    t_next  "Please try again"      //next ['"かけなおして\u3000ください"']
    t_next  "later.";               //db ['"@"'];

// void MobileErrorCode_15_000_Text(void){
//     return MobileErrorCode_15_001_Text();
// }

// void MobileErrorCode_15_001_Text(void){
//     return MobileErrorCode_15_002_Text();
// }

// void MobileErrorCode_15_002_Text(void){
//     return MobileErrorCode_15_003_Text();
// }

//  There is an error with the Mobile Adapter.
//  Please wait for a little while before calling again.
//  If the problem persists, please contact the Mobile Support Center.
const char MobileErrorCode_15_003_Text[] = 
            "Mobile Adapter"        // "モバイルアダプタの　エラーです"
    t_next  "error."                // "しばらく　まって"
    t_next  "Please try again."     // "かけなおして　ください"
    t_next  "If the problem"        // "なおらない　ときは"
    t_next  "persists, please"      // "モバイルサポートセンターへ"
    t_next  "contact support.@";    // "おといあわせください"

//  Communication error.
//  Please wait a moment, and then try again.
//  If the issue persists, please contact the Mobile Support Center.
const char MobileErrorCode_CommuncationErrorText[] = 
            "Communication"         // "つうしんエラーです"
    t_next  "error."                // "しばらく　まって"
    t_next  "Please try again."     // "かけなおして　ください"
    t_next  "If the problem"        // "なおらない　ときは"
    t_next  "persists, please"      // "モバイルサポートセンターへ"
    t_next  "contact support.@";    // "おといあわせください"

//  There is a mistake either with the login password, or the login ID.
//  Please confirm the password, wait for a while, and try again.
const char MobileErrorCode_22_000_Text[] =
            "Invalid Log-in"    // "ログインパスワードか"
    t_next  "ID or Password."   // "ログイン　アイディーに"
    t_next  "Please confirm"    // "まちがいがあります"
    t_next  "your Log-in"       // "パスワードを　かくにんして"
    t_next  "information"       // "しばらく　まって"
    t_next  "and try again.@";  // "かけなおして　ください"

//  The call was ended.
//  Please see the instruction manual, wait a moment, and try again.
const char MobileErrorCode_23_000_Text[] =
            "The phone was"     // "でんわが　きれました"
    t_next  "disconnected."     // "とりあつかいせつめいしょを"
    t_next  "Please check the"  // "ごらんのうえ"
    t_next  "manual and try"    // "しばらく　まって"
    t_next  "again later.@";    // "かけなおして　ください"

//  There was a communication error with the mobile center.
//  Please wait a moment and then try again.
const char MobileErrorCode_ServerErrorText[] =
            "Error connecting"  // "モバイルセンターの"
    t_next  "to the"            // "つうしんエラーです"
    t_next  "Mobile Center."    // "しばらくまって"
    t_next  "Please try again"  // "かけなおして　ください"
    t_next  "later.@";

// void MobileErrorCode_14_000_Text(void){
//     return MobileErrorCode_25_000_Text();
// }

//  The Mobile Adapter's details have expired and the information is not correct.
//  Please use the Mobile Trainer to repeat the initial registration (process).
const char MobileErrorCode_25_000_Text[] =
            "The Mobile Adapter"    // "モバイルアダプタに"
    t_next  "is not configured"     // "とうろくされた　じょうほうが"
    t_next  "properly."             // "ただしく　ありません"
    t_next  "Please register"       // "モバイルトレーナーで"
    t_next  "your information"      // "しょきとうろくを　してください"
    t_next  "in Mobile Trainer.@";


//  Could not connect because the Mobile Center is busy.
//  Please wait a moment and try again.
//  For details, please see the instruction manual.
const char MobileErrorCode_32_503_Text[] =
            "The Mobile Center" // "モバイルセンターが"
    t_next  "is busy."          // "こんでいて　つながりません"
    t_next  "Please check the"  // "しばらくまって"
    t_next  "manual and try"    // "かけなおして　ください"
    t_next  "calling again"     // "くわしくは　とりあつかい"
    t_next  "later.@";          // "せつめいしょを　ごらんください"

// void MobileErrorCode_30_450_Text(void){
//     return MobileErrorCode_30_550_Text();
// }

// void MobileErrorCode_30_550_Text(void){
//     return MobileErrorCode_30_551_Text();
// }

// void MobileErrorCode_30_551_Text(void){
//     return MobileErrorCode_30_553_Text();
// }

//  There is a mistake with the email address of the addressee.
//  Please replace with a / the correct email address.
const char MobileErrorCode_30_553_Text[] =
            "The email address" // "あてさき　メールアドレスに"
    t_next  "is incorrect."     // "まちがいがあります"
    t_next  "Please re-enter"   // "ただしい　メールアドレスを"
    t_next  "the email"         // "いれなおしてください"
    t_next  "address.@";

//  There is a mistake with the email address.
//  Please see the instruction manual, and use the Mobile Trainer to repeat the initial registration (process).
const char MobileErrorCode_31_002_Text[] =
	        "Your email address"    // "メールアドレスに"
	t_next  "is incorrect."         // "まちがいが　あります"
	t_next  "Please check the"      // "とりあつかいせつめいしょを"
	t_next  "manual and"            // "ごらんのうえ"
	t_next  "register using"        // "モバイルトレーナーで"
	t_next  "Mobile Trainer.@";     // "しょきとうろくを　してください"

// void MobileErrorCode_31_003_Text(void){
//     return MobileErrorCode_33_201_Text();
// }

//  There is either an error with the login password, or an error with the Mobile Center.
//  Please confirm the password, wait a moment, and then try again.
const char MobileErrorCode_33_201_Text[] =
            "Incorrect Log-in"  // "ログインパスワードに"
    t_next  "Password or"       // "まちがいが　あるか"
    t_next  "Mobile Center"     // "モバイルセンターの　エラーです"
    t_next  "error."            // "パスワードを　かくにんして"
    t_next  "Please try again"  // "しばらく　まって"
    t_next  "later.@";          // "かけなおして　ください"

// void MobileErrorCode_32_403_Text(void){
//     return MobileErrorCode_32_404_Text();
// }

//  Cannot read data.
//  Please wait a moment, and then try again.
//  If the issue persists, please contact the Mobile Support Center.
//  MobileErrorCode_32_404_Text
const char MobileErrorCode_ReadDataErrorText[] = 
            "Unable to read"        // "データの　よみこみが　できません"
    t_next  "the data."             // "しばらくまって"
    t_next  "Please try again."     // "かけなおして　ください"
    t_next  "If the problem"        // "なおらない　ときは"
    t_next  "persists, please"      // "モバイルサポートセンターへ"
    t_next  "contact support.@";    // "おといあわせください"

// void MobileErrorCode_26_000_Text(void){
//     return MobileErrorCode_32_408_Text();
// }

//  Out of time.
//  The call was ended.
//  Please try again.
//  For details, please see the instruction manual.
const char MobileErrorCode_32_408_Text[] = 
            "Time's up!"        // "じかんぎれです"
    t_next  "The call has"      // "でんわが　きれました"
    t_next  "ended."            // "でんわを　かけなおしてください"
    t_next  "Please check the"  // "くわしくは　とりあつかい"
    t_next  "manual and try"    // "せつめいしょを　ごらんください"
    t_next  "again later.";

//  The service cannot be used if payments for usage fees are late.
//  For details, please see the instruction manual.
const char MobileErrorCode_33_101_Text[] =
            "The service is"        // "おきゃくさまの　ごつごうにより"
    t_next  "unavailable due to"    // "ごりようできません"
    t_next  "a missed payment."     // "ごりようが　できなくなります"
    t_next  "Please check the"      // "くわしくは　とりあつかい"
    t_next  "manual.@";             // "せつめいしょを　ごらんください"
    //db ['"ごりよう\u3000りょうきんの\u3000"'];
    //next ['"おしはらいが\u3000おくれたばあいには"']
    //next ['"ごりようが\u3000できなくなります"']
    //next ['"くわしくは\u3000とりあつかい"']
    //next ['"せつめいしょを\u3000ごらんください"']
    //db ['"@"'];

// void MobileErrorCode_33_102_Text(void){
//     return MobileErrorCode_33_299_Text();
// }

//  Your access to this service has been restricted. Service cannot be used.
//  For details, please see the instruction manual.
const char MobileErrorCode_33_299_Text[] =
            "The service is"        // "おきゃくさまの　ごつごうにより"
    t_next  "unavailable at"        // "ごりようできません"
    t_next  "this time."            // "くわしくは　とりあつかい"
    t_next  "Please check the"      // "せつめいしょを　ごらんください"
    t_next  "manual.@";

//  The telephone line is busy. Due to this error, the Mobile Center cannot communicate.
//  Please wait for a little while and call again.
const char MobileErrorCode_ServerConnectionFailedText[] =
            "There was an error"    // "でんわかいせんが　こんでいるか"
    t_next  "with the phone or"     // "モバイルセンターの　エラーで"
    t_next  "the Mobile Center."    // "つうしんが　できません"
    t_next  "Please try again"      // "しばらく　まって"
    t_next  "later.@";              // "かけなおして　ください"

//  Service cannot be used this month because usage fees have exceeded conditions.
//  For details, please see the instruction manual.
const char MobileErrorCode_33_103_Text[] =
            "You have reached"  // "ごりよう　りょうきんが"
    t_next  "the monthly"       // "じょうげんを　こえているため"
    t_next  "spending limit."   // "こんげつは　ごりようできません"
    t_next  "Please check the"  // "くわしくは　とりあつかい"
    t_next  "manual for"        // "せつめいしょを　ごらんください"
    t_next  "details.@";

//  Cannot communicate because the Mobile Center is currently undergoing maintenance.
//  Please wait a moment, then try again.
const char MobileErrorCode_33_106_Text[] =
            "The Mobile Center" // "げんざい　モバイルセンターの"
    t_next  "is undergoing"     // "てんけんを　しているので"
    t_next  "maintenance."      // "つうしんが　できません"
    t_next  "Please try again"  // "しばらく　まって"
    t_next  "later.@";          // "かけなおして　ください"

// void MobileErrorCode_33_104_Text(void){
//     return MobileErrorCode_33_105_Text();
// }

// void MobileErrorCode_33_105_Text(void){
//     return MobileErrorCode_33_203_Text();
// }

// void MobileErrorCode_33_203_Text(void){
//     return MobileErrorCode_33_206_Text();
// }

// void MobileErrorCode_33_206_Text(void){
// }

//  Cannot read data.
//  For details, please see the instruction manual.
const char MobileErrorCode_101_004_Text[] = 
           "Unable to read"     //db ['"データの\u3000よみこみが\u3000できません"'];
    t_next "the data."          //next ['"くわしくは\u3000とりあつかい"']
    t_next "Please check the"   //next ['"せつめいしょを\u3000ごらんください"']
    t_next "manual for"         //db ['"@"'];
    t_next "details.@";

//  Call ended because more than 3 minutes elapsed with no input.
const char MobileErrorCode_101_006_Text[] =
           "The call was"   // "３ぷん\u3000いじょう\u3000なにも"
    t_next "ended due to"   // "にゅうりょく\u3000しなかったので"
    t_next "no input being" // "でんわが\u3000きれました"
    t_next "received for "  // "@"
    t_next "three minutes.@";

//  Could not connect properly.
//  Please try again from the beginning (of the process).
const char MobileErrorCode_101_002_Text[] = 
           "Communication"  // "つうしんが\u3000うまく"
    t_next "failed."        // "できませんでした"
    t_next "Please start"   // "もういちど\u3000はじめから"
    t_next "over and try"   // "やりなおしてください"
    t_next "again.";        // "@"

// void MobileErrorCode_101_003_Text(void){
//     return MobileErrorCode_101_008_Text();
// }

// void MobileErrorCode_101_008_Text(void){
//     return MobileErrorCode_101_009_Text();
// }

//  Cannot read data.
//  Please wait a moment, then try again.
//  If the issue persists, please contact the Mobile Support Center.
const char MobileErrorCode_101_009_Text[] =
           "Unable to read"     //db ['"データの\u3000よみこみが\u3000できません"'];
    t_next "the data."          //next ['"しばらくまって"']
    t_next "Please try again."  //next ['"かけなおして\u3000ください"']
    t_next "If the problem"     //next ['"なおらない\u3000ときは"']
    t_next "persists, please"   //next ['"モバイルサポートセンターへ"']
    t_next "contact support."   //next ['"おといあわせください"']
           "";                  //db ['"@"'];

//  Call ended due to long waiting time.
const char MobileErrorCode_101_007_Text[] =
           "The call was"    //db ['"まちじかんが\u3000ながいので"'];
    t_next "ended because"   //next ['"でんわが\u3000きれました"']
    t_next "of inactivity."; //db ['"@"'];

//  (Your adapter's) type differs from the other user’s Mobile Adapter.
//  For details, please see the instruction manual.
const char MobileErrorCode_101_005_Text[] = 
           "Your friend is"     // "あいての\u3000モバイルアダプタと"'
    t_next "using a different"  // "タイプが\u3000ちがいます"
    t_next "kind of"            // "くわしくは\u3000とりあつかい"
    t_next "Mobile Adapter."    // "せつめいしょを\u3000ごらんください"
    t_next "Check the manual"   // "@"
    t_next "for details.";

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
}

const char MobileErrorCode_101_000_Text[] = 
//  Either bad communication status, or the other user called was the incorrect user.
//  Please confirm and try again.
        "The signal is poor"    // "つうしんの\u3000じょうきょうが"
    t_next "or the number is"   // "よくないか\u3000かけるあいてが"
    t_next "incorrect."         // "まちがっています"
    t_next "Please try again"   // "もういちど\u3000かくにんをして"
    t_next "later.";            // "でんわを\u3000かけなおして\u3000ください"
    //db ['"@"'];

void Function17ff23(void){
    // LDH_A_addr(hJoyPressed);
    // AND_A_A;
    // RET_Z ;
    if(hram->hJoyPressed == 0)
        return;
    // LD_A(0x8);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0x8;
    // LD_A_addr(wMapMusic);
    // LD_addr_A(wMusicFadeID);
    wram->wMusicFadeID = wram->wMapMusic;
    // XOR_A_A;
    // LD_addr_A(wMusicFadeID + 1);
    // LD_HL(wc303);
    // SET_hl(7);
    bit_set(wram->wc303, 7);
    // RET;
}

bool Function17ff3c(void){
    // NOP;
    // LD_A_addr(wMobileErrorCodeBuffer);
    // CP_A(0xd0);
    // RET_C ;
    if(wram->wMobileErrorCodeBuffer[0] < 0xd0)
        return true;
    // hlcoord(10, 2, wTilemap);
    // LD_DE(mString_17ff68);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_17ff68), coord(10, 2, wram->wTilemap));
    // LD_A_addr(wMobileErrorCodeBuffer);
    // PUSH_AF;
    uint8_t temp = wram->wMobileErrorCodeBuffer[0];
    // SUB_A(0xd0);
    // INC_A;
    // LD_addr_A(wMobileErrorCodeBuffer);
    wram->wMobileErrorCodeBuffer[0] -= 0xd0;
    // hlcoord(14, 2, wTilemap);
    // LD_DE(wMobileErrorCodeBuffer);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 3);
    // CALL(aPrintNum);
    PrintNum_Conv2(coord(14, 2, wram->wTilemap), wram->wMobileErrorCodeBuffer, PRINTNUM_LEADINGZEROS | 1, 3);
    // POP_AF;
    // LD_addr_A(wMobileErrorCodeBuffer);
    wram->wMobileErrorCodeBuffer[0] = temp;
    // AND_A_A;
    // RET;
    return false;
}

const char String_17ff68[] = "101@"; // "１０１@"
