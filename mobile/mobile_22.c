#include "../constants.h"
#include "mobile_22.h"
#include "mobile_22_2.h"
#include "mobile_12.h"
#include "mobile_5e.h"
#include "mobile_menu.h"
#include "fixed_words.h"
#include "../home/copy.h"
#include "../home/sram.h"
#include "../home/tilemap.h"
#include "../home/joypad.h"
#include "../home/menu.h"
#include "../home/lcd.h"
#include "../home/clear_sprites.h"
#include "../home/gfx.h"
#include "../home/delay.h"
#include "../home/text.h"
#include "../home/print_text.h"
#include "../home/audio.h"
#include "../home/scrolling_menu.h"
#include "../home/string.h"
#include "../engine/menus/menu.h"
#include "../engine/menus/naming_screen.h"
#include "../engine/menus/save.h"
#include "../engine/gfx/color.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/crystal_layouts.h"
#include "../engine/gfx/load_pics.h"
#include "../engine/gfx/place_graphic.h"
#include "../engine/link/lan.h"
#include "../engine/link/mystery_gift.h"
#include "../engine/printer/printer.h"
#include "../engine/events/battle_tower/get_trainer_class.h"
#include "../data/trainers/palettes.h"
#include "../data/text/common.h"

const char String_89116[] = "-------@"; //db ['"-----@"'];
const char String_EmptyIDNo[] = "-----@";

const char String_8911c[] = 
            "Please enter a"  //db ['"でんわばんごうが\u3000ただしく"'];  // Phone number is not
    t_next  "phone number.@"; //next ['"はいって\u3000いません！@"']  // entered correctly!

const char String_89135[] = 
            "Discard changes to" //db ['"データが\u3000かわって\u3000いますが"'];  // The data has changed.
    t_next  "this CARD?@"; //next ['"かきかえないで\u3000やめますか？@"']  // Quit anyway?

const char String_89153[] = "No message.@"; //db ['"メッセージは\u3000ありません@"'];  // No message


// NOTE: I'm unsure exactly which WRAM bank the game would expect to be used with the wd000 variables.
// Further testing of the original game is required.

void OpenSRAMBank4(void){
    // PUSH_AF;
    // LD_A(0x4);
    // CALL(aOpenSRAM);
    OpenSRAM(0x4);
    // POP_AF;
    // RET;
}

void Function89168(void){
    // LD_HL(wGameTimerPaused);
    // SET_hl(GAME_TIMER_MOBILE_F);
    bit_set(wram->wGameTimerPaused, GAME_TIMER_MOBILE_F);
    // RET;
}

void Function8916e(void){
    // LD_HL(wGameTimerPaused);
    // RES_hl(GAME_TIMER_MOBILE_F);
    bit_reset(wram->wGameTimerPaused, GAME_TIMER_MOBILE_F);
    // RET;
}

bool Function89174(void){
    // LD_HL(wGameTimerPaused);
    // BIT_hl(GAME_TIMER_MOBILE_F);
    // RET;
    return bit_test(wram->wGameTimerPaused, GAME_TIMER_MOBILE_F);
}

void Function8917a(void){
    // LD_HL(wd002);
    // LD_BC(0x32);
    // XOR_A_A;
    // CALL(aByteFill);
    // RET;
    ByteFill(&wram->wd002, 0x32, 0);
}

// Mobile22_MemCmp
bool Function89185(const uint8_t* hl, const uint8_t* de, uint8_t c){
//  strcmp(hl, de, c)
//  Compares c bytes starting at de and hl and incrementing together until a mismatch is found.
//  Preserves hl and de.
    // PUSH_DE;
    // PUSH_HL;

    do {
    // loop:
        // LD_A_de;
        // INC_DE;
        // CP_A_hl;
        // IF_NZ goto done;
        if(*de != *hl)
            return false;
        // INC_HL;
        de++, hl++;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

// done:
    // POP_HL;
    // POP_DE;
    // RET;
    return true;
}

//  copy(hl, de, 4)
//  Copies c bytes from hl to de.
//  Preserves hl and de.
void Function89193(void* de, const void* hl, uint8_t c){
    // PUSH_DE;
    // PUSH_HL;

// loop:
    // LD_A_hli;
    // LD_de_A;
    // INC_DE;
    // DEC_C;
    // IF_NZ goto loop;
    // POP_HL;
    // POP_DE;
    CopyBytes(de, hl, c);
    // RET;
    return;
}

void Function8919e(void){
//  Searches for the c'th string starting at de.  Returns the pointer in de.
    LD_A_C;
    AND_A_A;
    RET_Z ;

loop:
    LD_A_de;
    INC_DE;
    CP_A(0x50);
    IF_NZ goto loop;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

// Mobile22_ReloadMapPart
void Function891ab(void){
    // CALL(aMobile22_SetBGMapMode1);
    Mobile22_SetBGMapMode1();
    // FARCALL(aReloadMapPart);
    ReloadMapPart();
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // RET;
}

// Mobile22_ClearScreen
void Function891b8(void){
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // hlcoord(0, 0, wTilemap);
    // LD_A(0x7f);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // CALL(aDelayFrame);
    DelayFrame();
    // RET;
}

// Mobile22_ClearScreenAndWaitBGMap
void Function891ca(void){
    // PUSH_BC;
    // CALL(aFunction891b8);
    Function891b8();
    // CALL(aWaitBGMap);
    WaitBGMap();
    // POP_BC;
    // RET;
}

// Mobile22_ClearScreenAndWaitBGMapPlus10Frames
void Function891d3(void){
    // PUSH_BC;
    // CALL(aFunction891ca);
    Function891ca();
    // LD_C(0x10);
    // CALL(aDelayFrames);
    DelayFrames(0x10);
    // POP_BC;
    // RET;
}

// Mobile22_ClearScreen?
void Function891de(void){
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // CALL(aClearPalettes);
    ClearPalettes();
    // hlcoord(0, 0, wAttrmap);
    // LD_A(0x7);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7);
    // hlcoord(0, 0, wTilemap);
    // LD_A(0x7f);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // CALL(aFunction891ab);
    Function891ab();
    // RET;

}

// Mobile22_ClearScreenAndWait16Frames
void Function891fe(void){
    // PUSH_BC;
    // CALL(aFunction891de);
    Function891de();
    // LD_C(0x10);
    // CALL(aDelayFrames);
    DelayFrames(0x10);
    // POP_BC;
    // RET;
}

void Mobile_EnableSpriteUpdates(void){
    // LD_A(1);
    // LD_addr_A(wSpriteUpdatesEnabled);
    wram->wSpriteUpdatesEnabled = 1;
    // RET;
}

void Mobile_DisableSpriteUpdates(void){
    // LD_A(0);
    // LD_addr_A(wSpriteUpdatesEnabled);
    wram->wSpriteUpdatesEnabled = 0;
    // RET;
}

void Function89215(tile_t* hl, uint8_t a){
    // PUSH_HL;
    // PUSH_BC;
    // LD_BC(wAttrmap - wTilemap);
    // ADD_HL_BC;
    // LD_hl_A;
// This should continue working even if tile_t is changed to uint16_t or something
    wram->wAttrmap[hl - wram->wTilemap] = a;
    // POP_BC;
    // POP_HL;
    // RET;
}

void Function8921f(tile_t* hl, uint8_t b, uint8_t c){
    // PUSH_DE;
    // LD_DE(SCREEN_WIDTH);
    // ADD_HL_DE;
    hl += SCREEN_WIDTH;
    // INC_HL;
    hl++;
    // LD_A(0x7f);

    do {
    // loop:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        tile_t* hl2 = hl;

        do {
        // asm_89229:
            // LD_hli_A;
            *(hl2++) = 0x7f;
            // DEC_C;
            // IF_NZ goto asm_89229;
        } while(--c2 != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // POP_DE;
    // RET;
}

void Mobile22_PromptButton(void){
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // RET;
}

void Mobile22_SetBGMapMode0(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_NONE;
    // RET;
}

void Mobile22_SetBGMapMode1(void){
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram.hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // RET;
}

// Mobile22_TryLoadSaveFile
// Returns false (c) if the file is corrupted.
// Returns true (nc) on success.
bool Function89245(void){
    // FARCALL(aTryLoadSaveFile);
    // RET_C ;
    if(!TryLoadSaveFile())
        return false;
    // FARCALL(av_LoadData);
    v_LoadData();
    // AND_A_A;
    // RET;
    return true;
}

// CardMenu_YesNoMenu_Coord_7_13
bool Function89254(uint8_t a){
    // LD_BC(0xd07);
    // JR(mFunction89261);
    return Function89261(a, 0xd, 0x7);
}

// CardMenu_YesNoMenu_Coord_7_14
bool Function89259(uint8_t a){
    // LD_BC(0x0e07);
    // JR(mFunction89261);
    return Function89261(a, 0xe, 0x7);
}

// CardMenu_YesNoMenu_Coord_12_14
bool Function8925e(uint8_t a){
    // LD_BC(0x0e0c);

    return Function89261(a, 0xe, 0xc);
}

// CardMenu_YesNoMenu
bool Function89261(uint8_t a, uint8_t b, uint8_t c){
    // PUSH_AF;
    // PUSH_BC;
    // LD_HL(mMenuHeader_0x892a3);
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(&MenuHeader_0x892a3);
    // POP_BC;
    // LD_HL(wMenuBorderTopCoord);
    // LD_A_C;
    // LD_hli_A;
    wram->wMenuBorderTopCoord = c;
    // LD_A_B;
    // LD_hli_A;
    wram->wMenuBorderLeftCoord = b;
    // LD_A_C;
    // ADD_A(0x4);
    // LD_hli_A;
    wram->wMenuBorderBottomCoord = c + 0x4;
    // LD_A_B;
    // ADD_A(0x5);
    // LD_hl_A;
    wram->wMenuBorderRightCoord = b + 0x5;
    // POP_AF;
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = a;
    // CALL(aPushWindow);
    PushWindow();
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // CALL(aMobile_EnableSpriteUpdates);
    Mobile_EnableSpriteUpdates();
    // CALL(aVerticalMenu);
    bool cancel = VerticalMenu();
    // PUSH_AF;
    // LD_C(0xa);
    // CALL(aDelayFrames);
    DelayFrames(0xa);
    // CALL(aCloseWindow);
    CloseWindow();
    // CALL(aMobile_DisableSpriteUpdates);
    Mobile_DisableSpriteUpdates();
    // POP_AF;
    // IF_C goto done;
    // LD_A_addr(wMenuCursorY);
    // CP_A(0x2);
    // IF_Z goto done;
    if(cancel || wram->wMenuCursorY == 0x2)
        return true;
    // AND_A_A;
    // RET;
    return false;

// done:
    // SCF;
    // RET;
}

// CardMenu_YesNoMenuHeader
const struct MenuHeader MenuHeader_0x892a3 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(10, 5, 15, 9),
    .data = &MenuData_0x892ab,
    .defaultOption = 1,  // default option
};

// CardMenu_YesNoMenuData
const struct MenuData MenuData_0x892ab = {
    .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING,  // flags
    .verticalMenu = {
        .count = 2,  // items
        .options = (const char*[]) {
            "YES",  //db ['"はい@"'];
            "NO",   //db ['"いいえ@"'];
        },
    },
};

void Function892b4(void){
    // CALL(aFunction8931b);
    uint8_t* bc = Function8931b();

    return Function892b7(bc);
}

// This function just initializes a bunch of data at bc,
// but does it in a weird and obtuse way.
void Function892b7(uint8_t* bc){
    // LD_D_B;
    // LD_E_C;
    // LD_HL(0);
    // ADD_HL_BC;
    // LD_A(0x50);
    // LD_BC(6);
    // CALL(aByteFill);
    ByteFill(bc, 6, 0x50);
    // LD_B_D;
    // LD_C_E;
    // LD_HL(6);
    // ADD_HL_BC;
    // LD_A(0x50);
    // LD_BC(6);
    // CALL(aByteFill);
    ByteFill(bc + 6, 6, 0x50);
    // LD_B_D;
    // LD_C_E;
    // LD_HL(12);
    // ADD_HL_BC;
    // XOR_A_A;
    // LD_hli_A;
    bc[12] = 0;
    // LD_hl_A;
    bc[13] = 0;
    // LD_HL(14);
    // ADD_HL_BC;
    // LD_hli_A;
    bc[14] = 0;
    // LD_hl_A;
    bc[15] = 0;
    // LD_HL(16);
    // ADD_HL_BC;
    // LD_hl_A;
    bc[16] = 0;
    // LD_HL(17);
    // ADD_HL_BC;
    // LD_A(-1);
    // LD_BC(8);
    // CALL(aByteFill);
    ByteFill(bc + 17, 8, 0xff);
    // LD_B_D;
    // LD_C_E;
    // LD_E(6);
    uint8_t e = 6;
    // LD_HL(25);
    // ADD_HL_BC;
    uint8_t* hl = bc + 25;

    do {
    // loop:
        // LD_A(-1);
        // LD_hli_A;
        *(hl++) = 0xff;
        // LD_A(-1);
        // LD_hli_A;
        *(hl++) = 0xff;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
    // RET;
}

void Function89305(void){
    // XOR_A_A;
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = 0;
    // LD_C(40);
    uint8_t c = 40;

    do {
    // loop:
        // LD_A_addr(wMenuSelection);
        // INC_A;
        // LD_addr_A(wMenuSelection);
        wram->wMenuSelection++;
        // PUSH_BC;
        // CALL(aFunction892b4);
        Function892b4();
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // RET;
}

// Mobile22_GetSelectedCardFolderEntryInBC
uint8_t* Function8931b(void){
    // PUSH_HL;
    // LD_HL(s4_a03b);
    // LD_A_addr(wMenuSelection);
    // DEC_A;
    // LD_BC(37);
    // CALL(aAddNTimes);
    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // RET;
    return GBToRAMAddr(s4_a03b + 37 * (wram->wMenuSelection - 1));
}

// Mobile22_CheckEmptyOrBlankPlayerNameInBC
uint8_t* Function8932d(uint8_t* bc){
    // LD_HL(0);
    // ADD_HL_BC;

    return Function89331(bc);
}

// Mobile22_CheckEmptyOrBlankPlayerNameInHL
uint8_t* Function89331(uint8_t* hl){
//  Scans up to 5 characters starting at hl, looking for a nonspace character up to the next terminator.
//  Sets carry if it does not find a nonspace character.
//  Returns the location of the following character in hl.
    // PUSH_BC;
    // LD_C(NAME_LENGTH_JAPANESE - 1);
    uint8_t c = PLAYER_NAME_LENGTH - 1;

    do {
    // loop:
        // LD_A_hli;
        uint8_t a = *(hl++);
        // CP_A(0x50);
        // IF_Z goto terminator;
        if(a == 0x50)
            return NULL;
        // CP_A(0x7f);
        // IF_NZ goto nonspace;
        if(a != 0x7f)
            return hl;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

// terminator:
    // SCF;
    // goto done;

// nonspace:
    // AND_A_A;

// done:
    // POP_BC;
    // RET;
    return NULL;
}

// StringSearchForNonWhitespace
// Returns NULL (c) if it does not find a nonspace character
const uint8_t* Function89346(const uint8_t* bc){
    // LD_H_B;
    // LD_L_C;
    // JR(mv_incave);
    return Function89346_incave(bc);
}

const uint8_t* Function8934a(const uint8_t* bc){
    // LD_HL(NAME_LENGTH_JAPANESE);
    // ADD_HL_BC;
    // return v_incave();
    return Function89346_incave(bc + PLAYER_NAME_LENGTH);
}

const uint8_t* Function89346_incave(const uint8_t* hl){
//  Scans up to 5 characters starting at hl, looking for a nonspace character up to the next terminator.  Sets carry if it does not find a nonspace character.  Returns the location of the following character in hl.
    // PUSH_BC;
    // LD_C(NAME_LENGTH_JAPANESE - 1);
    uint8_t c = PLAYER_NAME_LENGTH - 1;

    do {
    // loop:
        // LD_A_hli;
        uint8_t a = *(hl++);
        // CP_A(0x50);
        // IF_Z goto terminator;
        if(a == 0x50)
            break;
        // CP_A(0x7f);
        // IF_NZ goto nonspace;
        if(a != 0x7f)
            return hl;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

// terminator:
    // SCF;
    // goto done;

// nonspace:
    // AND_A_A;

// done:
    // POP_BC;
    // RET;
    return NULL;
}

//  Scans six byte pairs starting at bc to find $ff.  Sets carry if it does not find a $ff.  Returns the location of the byte after the first $ff found in hl.
uint8_t* Function89363(uint8_t* bc){
    // LD_H_B;
    // LD_L_C;
    // goto _incave;

    // LD_HL(25);
    // ADD_HL_BC;

// _incave:
    // PUSH_DE;
    // LD_E(NAME_LENGTH_JAPANESE);
    uint8_t e = EASY_CHAT_MESSAGE_WORD_COUNT;

    do {
    // loop:
        // LD_A_hli;
        uint8_t a = *(bc++);
        // CP_A(-1);
        // IF_NZ goto ok;
        if(a == 0xff)
            return bc;
        // LD_A_hli;
        a = *(bc++);
        // CP_A(-1);
        // IF_NZ goto ok;
        if(a == 0xff)
            return bc;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
    // SCF;
    // goto done;

// ok:
    // AND_A_A;

// done:
    // POP_DE;
    // RET;
    return NULL;
}

void Function89381(uint8_t* de, uint8_t* hl){
    // PUSH_BC;
    // PUSH_DE;
    // CALL(aFunction89b45);
    // IF_C goto ok;
    if(!Function89b45(hl)) {
        // PUSH_HL;
        // LD_A(-1);
        // LD_BC(8);
        // CALL(aByteFill);
        ByteFill(hl, PHONE_NUMBER_LENGTH, 0xff);
        // POP_HL;
    }

// ok:
    // POP_DE;
    // LD_C(8);
    // CALL(aFunction89193);
    Function89193(de, hl, PHONE_NUMBER_LENGTH);
    // POP_BC;
    // RET;
}

void Function8939a(uint8_t* bc){
    // PUSH_BC;
    // LD_HL(0);
    // ADD_HL_BC;
    // LD_DE(wd002);
    // LD_C(6);
    // CALL(aFunction89193);
    Function89193(&wram->wd002, bc + 0, PLAYER_NAME_LENGTH);
    // POP_BC;
    // LD_HL(17);
    // ADD_HL_BC;
    // LD_DE(wd008);
    // CALL(aFunction89381);
    Function89381(wram->wCardPhoneNumber, bc + PLAYER_NAME_LENGTH * 2 + 2 + 2 + 1);
    // RET;
}

// Mobile22_LoadFontAndCardGFX
void Function893b3(void){
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // CALL(aFunction893ef);
    Function893ef();
    // CALL(aFunction8942b);
    Function8942b();
    // CALL(aFunction89455);
    Function89455();
    // CALL(aEnableLCD);
    EnableLCD();
    // RET;
}

// Mobile22_LoadEZChatAndCardGFX
void Function893cc(void){
    // CALL(aDisableLCD);
    DisableLCD();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra();
    // CALL(aFunction893ef);
    Function893ef();
    // CALL(aFunction89464);
    Function89464();
    // CALL(aEnableLCD);
    EnableLCD();
    // RET;
}

void Function893e2(void){
    // CALL(aFunction89b1e);
    Function89b1e();
    // CALL(aFunction893b3);
    Function893b3();
    // CALL(aFunction8a5b6);
    Function8a5b6();
    // CALL(aFunction8949c);
    Function8949c();
    // RET;
}

// MobileCard_LoadEZChatCursorGFX
void Function893ef(void){
    // LD_DE(vTiles0);
    // LD_HL(mEZChatCursorGFX);
    // LD_BC(0x20);
    // LD_A(BANK(aEZChatCursorGFX));
    // CALL(aFarCopyBytes);
    // RET;
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0, EZChatCursorGFX, 0, 0x20 / LEN_2BPP_TILE);
}

void Function893fe(void){
//  //  unreferenced
    CALL(aDisableLCD);
    CALL(aFunction893ef);
    CALL(aEnableLCD);
    CALL(aDelayFrame);
    RET;

}

const char EZChatCursorGFX[] = "gfx/mobile/ez_chat_cursor.png";

// Mobile22_LoadCardAndFolderGFX
void Function8942b(void){
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x02);
    // LD_HL(mCardLargeSpriteAndFolderGFX);
    // LD_BC(8 * LEN_2BPP_TILE);  // just the large card sprite
    // LD_A(BANK(aCardLargeSpriteAndFolderGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x02, CardLargeSpriteGFX, 0, 8);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x0a);
    // LD_HL(mCardSpriteGFX);
    // LD_BC(4 * LEN_2BPP_TILE);
    // LD_A(BANK(aCardSpriteGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * 0x0a, CardSpriteGFX, 0, 4);
    // RET;
}

// Mobile22_ClearSpriteArray
void Function89448(void){
//  Clears the sprite array
    // PUSH_AF;
    // LD_HL(wVirtualOAM);
    // LD_D(24 * SPRITEOAMSTRUCT_LENGTH);
    // XOR_A_A;

// loop:
    // LD_hli_A;
    // DEC_D;
    // IF_NZ goto loop;
    // POP_AF;
    // RET;
    ByteFill(wram->wVirtualOAMSprite, 24 * SPRITEOAMSTRUCT_LENGTH, 0);
}

// Mobile22_LoadLargeCardSpriteAndFolderGFX
void Function89455(void){
    // LD_HL(mCardLargeSpriteAndFolderGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x0c);
    // LD_BC((8 + 65) * LEN_2BPP_TILE);  // large card sprite + folder
    // LD_A(BANK(aCardLargeSpriteAndFolderGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x0c, CardLargeSpriteGFX, 0, 8);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x14, CardFolderGFX, 0, 69);
    // RET;
}

// Mobile22_LoadMobileCardGFX
void Function89464(void){
    // LD_HL(mMobileCardGFX);
    // LD_DE(vTiles2);
    // LD_BC(0x20 * LEN_2BPP_TILE);
    // LD_A(BANK(aMobileCardGFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, MobileCardGFX, 0, 0x20);
    // LD_HL(mMobileCard2GFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x20);
    // LD_BC(0x17 * LEN_2BPP_TILE);
    // LD_A(BANK(aMobileCard2GFX));
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x20, MobileCard2GFX, 0, 0x17);
    // RET;
}

uint8_t Function89481(uint8_t* bc){
    // LD_D(2);
    // CALL(aFunction8934a);
    const uint8_t* hl = Function8934a(bc);
    // RET_C ;
    if(hl == NULL)
        return 2;
    // LD_D(0);
    // LD_HL(16);
    // ADD_HL_BC;
    // BIT_hl(0);
    // RET_Z ;
    if(!bit_test(bc[16], 0))
        return 0;
    // INC_D;
    // RET;
    return 1;
}

// Mobile22_SetDToPlayerGender
uint8_t Function89492(void){
    // LD_D(0);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // RET_Z ;
    // INC_D;
    // RET;
    return (bit_test(gCrystal.playerGender, PLAYERGENDER_FEMALE_F))? 1: 0;
}

// Mobile22_LoadPalettes2
void Function8949c(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mPalette_894b3);
    // LD_DE(wBGPals1 + PALETTE_SIZE * 7);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals1 + PALETTE_SIZE * 7, Palette_894b3, 1 * PALETTE_SIZE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

const uint16_t Palette_894b3[] = {
    rgb(31, 31, 31),
    rgb(31, 31, 31),
    rgb(31, 31, 31),
    rgb( 0,  0,  0),
};

void Function894bb(uint8_t* bc, uint8_t d){
    // CALL(aFunction894dc);
    Function894dc(d);
    // PUSH_BC;
    // CALL(aFunction8956f);
    Function8956f(bc);
    // CALL(aFunction8949c);
    Function8949c();
    // CALL(aFunction8a60d);
    Function8a60d();
    // POP_BC;
    // RET;
}

// Mobile_CardMenu_LoadAndSetPalettes
void Function894ca(uint8_t d){
    // PUSH_BC;
    // CALL(aFunction894dc);
    Function894dc(d);
    // CALL(aFunction895c7);
    Function895c7();
    // CALL(aFunction8949c);
    Function8949c();
    // CALL(aFunction8a60d);
    Function8a60d();
    // CALL(aSetPalettes);
    SetPalettes();
    // POP_BC;
    // RET;
}

// Mobile_CardMenu_LoadGenderDependentPalettes
void Function894dc(uint8_t d){
static const uint16_t Pals012a[] = {
    rgb(31, 31, 31),
    rgb(10, 17, 13),
    rgb(10,  8, 22),
    rgb( 0,  0,  0),

    rgb(31, 31, 31),
    rgb(16, 20, 31),
    rgb(10,  8, 22),
    rgb( 0,  0,  0),

    rgb(31, 31, 31),
    rgb(16, 20, 31),
    rgb(10, 17, 13),
    rgb( 0,  0,  0),
};

static const uint16_t Pals012b[] = {
    rgb(31, 31, 31),
    rgb(30, 22, 11),
    rgb(31,  8, 15),
    rgb( 0,  0,  0),

    rgb(31, 31, 31),
    rgb(16, 20, 31),
    rgb(31,  8, 15),
    rgb( 0,  0,  0),

    rgb(31, 31, 31),
    rgb(16, 20, 31),
    rgb(30, 22, 11),
    rgb( 0,  0,  0),
};

// Never used?
static const uint16_t Pals012c[] = {
    rgb(31, 31, 31),
    rgb(15, 20, 26),
    rgb(25,  7, 20),
    rgb( 0,  0,  0),

    rgb(31, 31, 31),
    rgb(16, 20, 31),
    rgb(25,  7, 20),
    rgb( 0,  0,  0),

    rgb(31, 31, 31),
    rgb(16, 20, 31),
    rgb(15, 20, 26),
    rgb( 0,  0,  0),
};

static const uint16_t *const PalettePointers[] = {
    Pals012a,
    Pals012b,
    Pals012c, // Never used?
};

static const uint16_t Pals345[] = {
    rgb(31, 31, 31),
    rgb(31, 31, 31),
    rgb(31, 13,  0),
    rgb(14,  8,  0),

    rgb(31, 31, 31),
    rgb(16, 16, 31),
    rgb( 0,  0, 31),
    rgb( 0,  0,  0),

    rgb(19, 31, 11),
    rgb( 0,  0,  0),
    rgb( 0,  0,  0),
    rgb( 0,  0,  0),
};
    // PUSH_BC;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(5);
    // LDH_addr_A(rSVBK);

    // LD_C_D;
    // LD_B(0);
    // LD_HL(mFunction894dc_PalettePointers);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(wBGPals1);
    // LD_BC(3 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals1, PalettePointers[d], 3 * PALETTE_SIZE);
    // LD_HL(mFunction894dc_Pals345);
    // LD_DE(wBGPals1 + 3 * PALETTE_SIZE);
    // LD_BC(3 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals1 + 3 * PALETTE_SIZE, Pals345, 3 * PALETTE_SIZE);

    // POP_AF;
    // LDH_addr_A(rSVBK);
    // POP_BC;
    // RET;
}

// Mobile22_LoadMobileOTTrainerClassPalette
void Function8956f(uint8_t* bc){
    uint16_t buffer[8];
    // PUSH_BC;
    // LD_HL(16);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    // LD_HL(0x000c);
    // ADD_HL_BC;
    // LD_B_H;
    // LD_C_L;
    // FARCALL(aGetMobileOTTrainerClass);
    // LD_A_C;
    // LD_addr_A(wTrainerClass);
    wram->wTrainerClass = GetMobileOTTrainerClass(bc + 16, bc + 0xc);
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(5);
    // LDH_addr_A(rSVBK);
    // LD_HL(wd030);
    // LD_A(-1);
    // LD_hli_A;
    wram->wBGPals1[0x30] = 0xff;
    // LD_A(0x7f);
    // LD_hl_A;
    wram->wBGPals1[0x31] = 0x7f;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // LD_A_addr(wTrainerClass);
    // LD_H(0);
    // LD_L_A;
    // ADD_HL_HL;
    // ADD_HL_HL;
    // LD_DE(mTrainerPalettes);
    // ADD_HL_DE;
    ExtractPaletteFromPNGAssetToBuffer(buffer, TrainerPalettes[wram->wTrainerClass]);
    uint8_t* hl = (uint8_t*)buffer;
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_DE(wd032);
    uint8_t* de = wram->wBGPals1 + 0x32;
    // LD_C(4);
    uint8_t c = 4;

    do {
    // loop:
        // LD_A(BANK(aTrainerPalettes));
        // CALL(aGetFarByte);
        // LD_de_A;
        *de = *hl;
        // INC_DE;
        de++, hl++;
        // INC_HL;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);
    // LD_HL(wd036);
    // XOR_A_A;
    // LD_hli_A;
    wram->wd036[0] = 0;
    // LD_hl_A;
    wram->wd036[1] = 0;
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // POP_BC;
    // RET;
}

void Function895c7(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mPalette_895de);
    // LD_DE(wd030);
    // LD_BC(8);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals1 + 6 * PALETTE_SIZE, Palette_895de, 1 * PALETTE_SIZE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

const uint16_t Palette_895de[] = {
    rgb(31, 31, 31),
    rgb( 7,  7,  6),
    rgb( 7,  7,  6),
    rgb( 0,  0,  0),
};

void Function895e6(void){
//  //  unreferenced
    LD_A(7);
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    RET;

}

// Mobile22_ResetAttrmap
void Function895f2(void){
    // PUSH_BC;
    // XOR_A_A;
    // hlcoord(0, 0, wAttrmap);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0);
    // CALL(aFunction89605);
    Function89605();
    // CALL(aFunction89655);
    Function89655();
    // POP_BC;
    // RET;
}

void Function89605(void){
    // hlcoord(19, 2, wAttrmap);
    uint8_t* hl = coord(19, 2, wram->wAttrmap);
    // LD_A(1);
    uint8_t a = 1;
    // LD_DE(SCREEN_WIDTH);
    // LD_C(14);
    uint8_t c = 14;

    do {
    // loop:
        // LD_hl_A;
        hl[0] = a;
        // DEC_C;
        // IF_Z goto done;
        if(--c == 0)
            break;
        // ADD_HL_DE;
        // INC_A;
        // LD_hl_A;
        hl[SCREEN_WIDTH] = a + 1;
        // DEC_A;
        // ADD_HL_DE;
        hl += 2 * SCREEN_WIDTH;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

// done:
    // hlcoord(0, 16, wAttrmap);
    hl = coord(0, 16, wram->wAttrmap);
    // LD_C(10);
    c = 10;
    // LD_A(2);
    a = 2;

    do {
    // loop2:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_A;
        // LD_hli_A;
        *(hl++) = a - 1;
        // INC_A;
        // DEC_C;
        // IF_NZ goto loop2;
    } while(--c != 0);
    // hlcoord(1, 11, wAttrmap);
    // LD_A(4);
    // LD_BC(4);
    // CALL(aByteFill);
    ByteFill(coord(1, 11, wram->wAttrmap), 4, 4);
    // LD_A(5);
    // LD_BC(14);
    // CALL(aByteFill);
    ByteFill(coord(1, 11, wram->wAttrmap) + 4, 14, 5);
    // RET;
}

void Function8963d(void){
    // hlcoord(12, 3, wAttrmap);
    uint8_t* hl = coord(12, 3, wram->wAttrmap);
    // LD_A(6);
    // LD_DE(SCREEN_WIDTH);
    // LD_BC((7 << 8) | 7);
    uint8_t b = 7;

    do {
    // loop:
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_C(7);
        uint8_t c = 7;

        do {
        // next:
            // LD_hli_A;
            *(hl2++) = 6;
            // DEC_C;
            // IF_NZ goto next;
        } while(--c != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

void Function89655(void){
    // hlcoord(1, 12, wAttrmap);
    uint8_t* hl = coord(1, 12, wram->wAttrmap);
    // LD_DE(SCREEN_WIDTH);
    // LD_A(5);
    // LD_B(4);
    uint8_t b = 4;

    do {
    // loop:
        // LD_C(18);
        uint8_t c = 18;
        // PUSH_HL;
        uint8_t* hl2 = hl;

        do {
        // next:
            // LD_hli_A;
            *(hl2++) = 5;
            // DEC_C;
            // IF_NZ goto next;
        } while(--c != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto loop;
    } while(--b != 0);
    // RET;
}

void Function8966c(void){
    // PUSH_BC;
    // CALL(aFunction89688);
    Function89688(); // create the background
    // hlcoord(4, 0, wTilemap);
    // LD_C(8);
    // CALL(aFunction896f5);
    Function896f5(coord(3, 0, wram->wTilemap), 10); // create borders
    // POP_BC;
    // RET;
}

void Function8967a(void){
    // PUSH_BC;
    // CALL(aFunction89688);
    Function89688(); // create the background
    // hlcoord(2, 0, wTilemap);
    // LD_C(12);
    // CALL(aFunction896f5);
    Function896f5(coord(1, 0, wram->wTilemap), 14); // create borders
    // POP_BC;
    // RET;
}

void Function89688(void){
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    // LD_A(1);
    // LD_E(SCREEN_WIDTH);
    // CALL(aFunction896e1);
    hl = Function896e1(hl, 1, SCREEN_WIDTH);
    // LD_A(2);
    // LD_E(SCREEN_WIDTH);
    // CALL(aFunction896eb);
    hl = Function896eb(hl, 2, SCREEN_WIDTH);
    // LD_A(3);
    // LD_hli_A;
    *(hl++) = 3;
    // LD_A(4);
    // LD_E(SCREEN_HEIGHT);
    // CALL(aFunction896e1);
    hl = Function896e1(hl, 4, SCREEN_HEIGHT);
    // LD_A(6);
    // LD_hli_A;
    *(hl++) = 6;
    // PUSH_BC;
    // LD_C(13);
    uint8_t c = 13;

    do {
    // loop:
        // CALL(aFunction896cb);
        hl = Function896cb(hl);
        // DEC_C;
        // IF_Z goto done;
        if(--c == 0)
            break;
        // CALL(aFunction896d6);
        hl = Function896d6(hl);
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

// done:
    // POP_BC;
    // LD_A(25);
    // LD_hli_A;
    *(hl++) = 25;
    // LD_A(26);
    // LD_E(SCREEN_HEIGHT);
    // CALL(aFunction896e1);
    hl = Function896e1(hl, 26, SCREEN_HEIGHT);
    // LD_A(28);
    // LD_hli_A;
    *(hl++) = 28;
    // LD_A(2);
    // LD_E(SCREEN_WIDTH);
    // CALL(aFunction896eb);
    Function896eb(hl, 2, SCREEN_WIDTH);
    // RET;
}

tile_t* Function896cb(tile_t* hl){
    // LD_DE(SCREEN_WIDTH - 1);
    // LD_A(7);
    // LD_hl_A;
    hl[0] = 7;
    // ADD_HL_DE;
    // LD_A(9);
    // LD_hli_A;
    hl[SCREEN_WIDTH - 1] = 9;
    // RET;
    return hl + SCREEN_WIDTH;
}

tile_t* Function896d6(tile_t* hl){
    // LD_DE(SCREEN_WIDTH - 1);
    // LD_A(10);
    // LD_hl_A;
    hl[0] = 10;
    // ADD_HL_DE;
    // LD_A(11);
    // LD_hli_A;
    hl[SCREEN_WIDTH - 1] = 11;
    // RET;
    return hl + SCREEN_WIDTH;
}

tile_t* Function896e1(tile_t* hl, uint8_t a, uint8_t e){
    do {
    // loop:
        // LD_hli_A;
        *(hl++) = a;
        // INC_A;
        // DEC_E;
        // RET_Z ;
        if(--e == 0)
            return hl;
        // LD_hli_A;
        *(hl++) = a + 1;
        // DEC_A;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
    // RET;
    return hl;
}

tile_t* Function896eb(tile_t* hl, uint8_t a, uint8_t e){
    do {
    // loop:
        // LD_hli_A;
        *(hl++) = a;
        // DEC_A;
        // DEC_E;
        // RET_Z ;
        if(--e == 0)
            return hl;
        // LD_hli_A;
        *(hl++) = a - 1;
        // INC_A;
        // DEC_E;
        // IF_NZ goto loop;
    } while(--e != 0);
    // RET;
    return hl;
}

void Function896f5(tile_t* hl, uint8_t c){
    // CALL(aFunction8971f);
    Function8971f(hl);
    // CALL(aFunction89736);
    Function89736(hl, c);
    // INC_HL;
    // INC_HL;
    hl += 2;
    // LD_B(2);

    return Function896ff(hl, 2, c);
}

//  //  unreferenced // uh, no?
//  INPUT:
//  hl = address of upper left corner of the area
//  b = height
//  c = width
void Function896ff(tile_t* hl, uint8_t b, uint8_t c){
//  clears an area of the screen
    // LD_A(0x7f);
    // LD_DE(SCREEN_WIDTH);
    do {
    // row_loop:
        // PUSH_BC;
        uint8_t c2 = c;
        // PUSH_HL;
        tile_t* hl2 = hl;

        do {
        // col_loop:
            // LD_hli_A;
            *(hl2++) = 0x7f;
            // DEC_C;
            // IF_NZ goto col_loop;
        } while(--c2 != 0);
        // POP_HL;
        // POP_BC;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto row_loop;
    } while(--b != 0);

//  alternates tiles $36 and $18 at the bottom of the area
    // DEC_HL;
    --hl;
    // INC_C;
    // INC_C;
    c += 2;

    do {
    // bottom_loop:
        // LD_A(0x36);
        // LD_hli_A;
        *(hl++) = 0x36;
        // DEC_C;
        // RET_Z ;
        if(--c == 0)
            return;
        // LD_A(0x18);
        // LD_hli_A;
        *(hl++) = 0x18;
        // DEC_C;
        // IF_NZ goto bottom_loop;
    } while(--c != 0);
    // RET;
}

void Function8971f(tile_t* hl){
    // LD_A(0x2c);
    // LD_hli_A;
    hl[0] = 0x2c;
    // LD_A(0x2d);
    // LD_hld_A;
    hl[1] = 0x2d;
    // PUSH_HL;
    // LD_DE(SCREEN_WIDTH);
    // ADD_HL_DE;
    // LD_A(0x31);
    // LD_hli_A;
    hl[SCREEN_WIDTH] = 0x31;
    // LD_A(0x32);
    // LD_hld_A;
    hl[SCREEN_WIDTH + 1] = 0x32;
    // ADD_HL_DE;
    // LD_A(0x35);
    // LD_hl_A;
    hl[2 * SCREEN_WIDTH] = 0x35;
    // POP_HL;
    // RET;
}

void Function89736(tile_t* hl, uint8_t c){
    // PUSH_HL;
    // INC_HL;
    // INC_HL;
    // LD_E_C;
    // LD_D(0x0);
    // ADD_HL_DE;
    hl += c + 2;
    // LD_A(0x2f);
    // LD_hli_A;
    hl[0] = 0x2f;
    // LD_A(0x30);
    // LD_hld_A;
    hl[1] = 0x30;
    // LD_DE(SCREEN_WIDTH);
    // ADD_HL_DE;
    // LD_A(0x33);
    // LD_hli_A;
    hl[SCREEN_WIDTH] = 0x33;
    // LD_A(0x34);
    // LD_hl_A;
    hl[SCREEN_WIDTH+1] = 0x34;
    // ADD_HL_DE;
    // LD_A(0x1f);
    // LD_hl_A;
    hl[SCREEN_WIDTH*2+1] = 0x1f;
    // POP_HL;
    // RET;

}

void Function89753(tile_t* hl){
    // LD_A(0xc);
    // LD_hl_A;
    *hl = 0xc;
    // XOR_A_A;
    // CALL(aFunction89215);
    Function89215(hl, 0);
    // RET;
}

void FunctionLine(tile_t* hl){
    // ld a, $e
    // ld [hl], a
    *hl = 0xe;
    // ret
}

void Function8975b(tile_t* hl){
    // LD_A(0x1d);
    // LD_hli_A;
    hl[0] = 0x1d;
    // INC_A;
    // LD_hli_A;
    hl[1] = 0x1e;
    // LD_A(0xd);
    // LD_hl_A;
    hl[2] = 0xd;
    // DEC_HL;
    // DEC_HL;
    // LD_A(0x4);
    // LD_E(0x3);

    for(uint8_t i = 0; i < 0x3; ++i) {
    // asm_89769:
        // CALL(aFunction89215);
        Function89215(hl + i, 0x4);
        // INC_HL;
        // DEC_E;
        // IF_NZ goto asm_89769;
    }
    // RET;
}

void Function89771(tile_t* hl){
    // LD_A(0x12);
    // LD_hl_A;
    *hl = 0x12;
    // LD_A(0x3);
    // CALL(aFunction89215);
    Function89215(hl, 0x3);
    // RET;
}

void Function8977a(tile_t* hl){
    // LD_E(0x4);
    uint8_t e = 0x4;
    // LD_D(0x13);
    uint8_t d = 0x13;

    do {
    // asm_8977e:
        // LD_A_D;
        // LD_hl_A;
        *hl = d;
        // LD_A(0x4);
        // CALL(aFunction89215);
        Function89215(hl, 0x4);
        // INC_HL;
        hl++;
        // INC_D;
        d++;
        // DEC_E;
        // IF_NZ goto asm_8977e;
    } while(--e != 0);
    // LD_E(0xe);
    e = 0xe;

    do {
    // asm_8978c:
        // LD_A_D;
        // LD_hl_A;
        *hl = d;
        // XOR_A_A;
        // CALL(aFunction89215);
        Function89215(hl, 0);
        // INC_HL;
        hl++;
        // DEC_E;
        // IF_NZ goto asm_8978c;
    } while(--e != 0);
    // RET;
}

void Function89797(tile_t* hl){
    // PUSH_BC;
    // LD_A(0xe);
    // LD_hl_A;
    *hl = 0x8;
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    hl += SCREEN_WIDTH;
    // LD_A(0x11);
    // LD_hli_A;
    *(hl++) = 0x11;
    // LD_A(0x10);
    // LD_C(0x8);
    uint8_t c = 0x8;

    do {
    // asm_897a6:
        // LD_hli_A;
        *(hl++) = 0x10;
        // DEC_C;
        // IF_NZ goto asm_897a6;
    } while(--c != 0);
    // LD_A(0xf);
    // LD_hl_A;
    *hl = 0xf;
    // POP_BC;
    // RET;
}

// Mobile22_LoadMobileOTTrainerPic
void Function897af(uint8_t* bc){
    // PUSH_BC;
    // LD_HL(0x0010);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    // LD_HL(0x000c);
    // ADD_HL_BC;
    // LD_B_H;
    // LD_C_L;
    // FARCALL(aGetMobileOTTrainerClass);
    // LD_A_C;
    // LD_addr_A(wTrainerClass);
    wram->wTrainerClass = GetMobileOTTrainerClass(bc + PLAYER_NAME_LENGTH * 2 + 2 + 2, bc + 2 * PLAYER_NAME_LENGTH);
    // XOR_A_A;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = 0;
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x37);
    // FARCALL(aGetTrainerPic);
    GetTrainerPic(vram->vTiles2 + LEN_2BPP_TILE * 0x37, wram->wTrainerClass);
    // POP_BC;
    // RET;
}

void Function897d5(const uint8_t* bc){
    // PUSH_BC;
    // CALL(aFunction8934a);
    // IF_NC goto asm_897f3;
    if(Function8934a(bc)) {
    // asm_897f3:
        // LD_A(0x37);
        // LDH_addr_A(hGraphicStartTile);
        hram.hGraphicStartTile = 0x37;
        // hlcoord(12, 3, wTilemap);
        // LD_BC((7 << 8) | 7);
        // PREDEF(pPlaceGraphic);
        PlaceGraphicYStagger(coord(12, 3, wram->wTilemap), 7, 7);
        // CALL(aFunction8963d);
        Function8963d();
        // POP_BC;
        // RET;
        return;
    }
    // hlcoord(12, 3, wAttrmap);
    uint8_t* hl = coord(12, 3, wram->wAttrmap);
    // XOR_A_A;
    // LD_DE(SCREEN_WIDTH);
    // LD_BC((7 << 8) | 7);
    uint8_t b = 7;

    do {
    // asm_897e5:
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_C(0x7);
        uint8_t c = 7;

        do {
        // asm_897e8:
            // LD_hli_A;
            *(hl2++) = 0;
            // DEC_C;
            // IF_NZ goto asm_897e8;
        } while(--c != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto asm_897e5;
    } while(--b != 0);
    // POP_BC;
    // RET;
}

// Mobile_CardMenu_LoadPlayerSilhouetteGFX
void Function89807(void){
    // LD_HL(mChrisSilhouetteGFX);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // IF_Z goto asm_89814;
    // LD_HL(mKrisSilhouetteGFX);

// asm_89814:
    const char* path = (bit_test(gCrystal.playerGender, PLAYERGENDER_FEMALE_F))? KrisSilhouetteGFX: ChrisSilhouetteGFX;
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x37);
    // LD_BC((5 * 7) * LEN_2BPP_TILE);
    // LD_A(BANK(aChrisSilhouetteGFX));  // aka BANK(KrisSilhouetteGFX)
    // CALL(aFarCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x37, path, 0, (5 * 7));
    // CALL(aEnableLCD);
    EnableLCD();
    // CALL(aDelayFrame);
    DelayFrame(); // Is this really needed?
    // RET;
}

void Function89829(tile_t* hl){
    // PUSH_BC;
    // LD_BC(0x705);
    uint8_t b = 0x7;
    // LD_DE(0x14);
    // LD_A(0x37);
    uint8_t a = 0x37;

    do {
    // asm_89832:
        // PUSH_BC;
        uint8_t c = 0x5;
        // PUSH_HL;
        tile_t* hl2 = hl;

        do {
        // asm_89834:
            // LD_hli_A;
            // INC_A;
            *(hl2++) = a++;
            // DEC_C;
            // IF_NZ goto asm_89834;
        } while(--c != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto asm_89832;
    } while(--b != 0);
    // CALL(aFunction8963d);
    Function8963d();
    // POP_BC;
    // RET;
}

void Function89844(uint8_t* bc){
    // CALL(aFunction89481);
    uint8_t d = Function89481(bc);
    // CALL(aFunction894bb);
    Function894bb(bc, d);
    // CALL(aFunction897af);
    Function897af(bc);
    // PUSH_BC;
    // CALL(aWaitBGMap2);
    WaitBGMap2();
    // CALL(aSetPalettes);
    SetPalettes();
    // POP_BC;
    // RET;
}

void Function89856(uint8_t* bc){
    // PUSH_BC;
    // CALL(aFunction891b8);
    Function891b8();
    // POP_BC;
    // CALL(aFunction895f2);
    Function895f2();
    // CALL(aFunction8966c);
    Function8966c();
    // CALL(aFunction899d3);
    Function899d3();
    // CALL(aFunction898aa);
    Function898aa();
    // CALL(aFunction898be);
    Function898be();
    // CALL(aFunction898dc);
    Function898dc(bc);
    // CALL(aFunction898f3);
    Function898f3(bc);
    // PUSH_BC;
    // LD_BC(wd008);
    // hlcoord(2, 10, wTilemap);
    // CALL(aFunction89975);
    Function89975(coord(2, 10, wram->wTilemap), wram->wCardPhoneNumber);
    // POP_BC;
    // CALL(aFunction897d5);
    Function897d5(bc);
    // RET;
}

void Function8987f(void){
    // CALL(aFunction891b8);
    Function891b8();
    // CALL(aFunction895f2);
    Function895f2();
    // CALL(aFunction8967a);
    Function8967a();
    // CALL(aFunction899d3);
    Function899d3();
    // hlcoord(5, 1, wTilemap);
    // CALL(aFunction8999c);
    Function8999c(coord(3, 1, wram->wTilemap));
    // hlcoord(13, 3, wTilemap);
    // CALL(aFunction89829);
    Function89829(coord(13, 3, wram->wTilemap));
    // CALL(aFunction899b2);
    Function899b2();
    // hlcoord(5, 5, wTilemap);
    // CALL(aFunction899c9);
    Function899c9(coord(5, 6, wram->wTilemap));
    // LD_BC(wd008);
    // hlcoord(2, 10, wTilemap);
    // CALL(aFunction89975);
    Function89975(coord(2, 10, wram->wTilemap), wram->wCardPhoneNumber);
    // RET;
}

void Function898aa(void){
    // LD_A_addr(wMenuSelection);
    // AND_A_A;
    // RET_Z ;
    if(wram->wMenuSelection == 0)
        return;
    // PUSH_BC;
    // hlcoord(6, 1, wTilemap);
    // LD_DE(wMenuSelection);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // CALL(aPrintNum);
    PrintNum(coord(5, 1, wram->wTilemap), &wram->wMenuSelection, PRINTNUM_LEADINGZEROS | 1, 2);
    // POP_BC;
    // RET;
}

void Function898be(void){
    // PUSH_BC;
    // LD_DE(wd002);
    uint8_t* de = &wram->wd002;
    // LD_HL(wd002);
    // CALL(aFunction89331);
    // IF_NC goto asm_898cd;
    if(Function89331(&wram->wd002) == NULL) {
        // LD_DE(mString_89116);
        de = U82C(String_89116);
    }

// asm_898cd:
    // hlcoord(9, 1, wTilemap);
    // LD_A_addr(wMenuSelection);
    // AND_A_A;
    // IF_NZ goto asm_898d7;
    // DEC_HL;
    tile_t* hl = (wram->wMenuSelection == 0)? coord(7, 1, wram->wTilemap): coord(8, 1, wram->wTilemap);

// asm_898d7:
    // CALL(aPlaceString);
    PlaceStringSimple(de, hl);
    // POP_BC;
    // RET;
}

void Function898dc(uint8_t* bc){
    // LD_HL(0x0006);
    // ADD_HL_BC;
    // PUSH_BC;
    // LD_D_H;
    // LD_E_L;
    uint8_t* de = bc + PLAYER_NAME_LENGTH;
    // CALL(aFunction8934a);
    // IF_NC goto asm_898eb;
    if(Function8934a(bc) == NULL) {
        // LD_DE(mString_89116);
        de = U82C(String_89116);
    }

// asm_898eb:
    // hlcoord(6, 4, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(de, coord(4, 5, wram->wTilemap));
    // POP_BC;
    // RET;
}

void Function898f3(uint8_t* bc){
    // PUSH_BC;
    // LD_HL(0x000c);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    // CALL(aFunction8934a);
    // IF_C goto asm_8990a;
    if(Function8934a(bc) == NULL) {
    // asm_8990a:
        // hlcoord(5, 5, wTilemap);
        // LD_DE(mString_89116);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_EmptyIDNo), coord(5, 6, wram->wTilemap));
    }
    else {
        // hlcoord(5, 5, wTilemap);
        // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
        // CALL(aPrintNum);
        PrintNum(coord(5, 6, wram->wTilemap), bc + PLAYER_NAME_LENGTH * 2, PRINTNUM_LEADINGZEROS | 2, 5);
        // goto asm_89913;
    }

// asm_89913:
    // POP_BC;
    // RET;
}

void Function89915(tile_t* hl){
    // PUSH_BC;
    // PUSH_HL;
    tile_t* hl2 = hl;
    // LD_DE(mUnknown_89942);
    const uint8_t* de = Unknown_89942;
    // LD_C(0x8);
    uint8_t c = 0x8;
    do {
    // asm_8991c:
        // LD_A_de;
        // LD_hl_A;
        *hl2 = *de;
        // LD_A(0x4);
        // CALL(aFunction89215);
        Function89215(hl2, 0x4);
        // INC_HL;
        hl2++;
        // INC_DE;
        de++;
        // DEC_C;
        // IF_NZ goto asm_8991c;
    } while(--c != 0);
    // POP_HL;
#if defined(_CRYSTAL_JP) // places the japanese accent things, no longer needed
    // LD_B(0x4);
    // LD_C(0x2b);
    // LD_A(0x8);
    uint8_t a = 0x8;
    // LD_DE(mUnknown_8994a);
    de = Unknown_8994a;

    do {
    // asm_89932:
        // PUSH_AF;
        // LD_A_de;
        // CP_A_hl;
        // IF_NZ goto asm_8993b;
        if(*de == *hl) {
            // CALL(aFunction8994e);
            Function8994e(hl, 0x4, 0x2b);
            // INC_DE;
            de++;
        }

    // asm_8993b:
        // INC_HL;
        hl++;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_89932;
    } while(--a != 0);
#endif
    // POP_BC;
    // RET;
}

const uint8_t Unknown_89942[] = {
#if !defined(_CRYSTAL_JP)
    0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b
#else
    0x24, 0x25, 0x26, ' ', 0x27, 0x28, 0x29, 0x2a
#endif
};

const uint8_t Unknown_8994a[] = {
    0x24, 0x27, 0x29, 0xff
};

void Function8994e(tile_t* hl, uint8_t b, uint8_t c){
    // PUSH_HL;
    // PUSH_DE;
    // LD_DE(SCREEN_WIDTH);
    // LD_A_L;
    // SUB_A_E;
    // LD_L_A;
    // LD_A_H;
    // SBC_A_D;
    // LD_H_A;
    hl -= SCREEN_WIDTH;
    // LD_A_C;
    // LD_hl_A;
    *hl = c;
    // LD_A_B;
    // CALL(aFunction89215);
    Function89215(hl, b);
    // POP_DE;
    // POP_HL;
    // RET;
}

void Function89962(tile_t* hl){
    // PUSH_BC;
    // LD_C(0x4);
    uint8_t c = 0x4;
    // LD_B(0x20);
    uint8_t b = 0x20;

    do {
    // asm_89967:
        // LD_A_B;
        // LD_hl_A;
        *hl = b;
        // LD_A(0x4);
        // CALL(aFunction89215);
        Function89215(hl, 0x4);
        // INC_HL;
        hl++;
        // INC_B;
        b++;
        // DEC_C;
        // IF_NZ goto asm_89967;
    } while(--c != 0);
    // POP_BC;
    // RET;
}

void Function89975(tile_t* hl, const uint8_t* bc){
    // PUSH_BC;
    // LD_E(0x8);
    uint8_t e = 0x8;

    do {
    // asm_89978:
        // LD_A_bc;
        // LD_D_A;
        uint8_t d = *bc;
        // CALL(aFunction8998b);
        Function8998b(hl + 0, d);
        // SWAP_D;
        d = (d << 4) | (d >> 4);
        // INC_HL;
        // LD_A_D;
        // CALL(aFunction8998b);
        Function8998b(hl + 1, d);
        // INC_BC;
        bc++;
        // INC_HL;
        hl += 2;
        // DEC_E;
        // IF_NZ goto asm_89978;
    } while(--e != 0);
    // POP_BC;
    // RET;
}

void Function8998b(tile_t* hl, uint8_t a){
    // PUSH_BC;
    // AND_A(0xf);
    // CP_A(0xa);
    // IF_NC goto asm_89997;
    if((a & 0xf) >= 0xa) {
    // asm_89997:
        // LD_A(0x7f);
        a = 0x7f;
    }
    else {
        // LD_C(0xf6);
        // ADD_A_C;
        a = (a & 0xf) + 0xf6;
        // goto asm_89999;
    }
// asm_89999:
    // LD_hl_A;
    *hl = a;
    // POP_BC;
    // RET;
}

// MobileCard_PrintPlayerNamesCard
void Function8999c(tile_t* hl){
    // LD_DE(wPlayerName);
    // CALL(aPlaceString);
    struct TextPrintState st = {.de = gPlayer.playerName, .hl = hl};
    PlaceString(&st, st.hl);
    // INC_BC;
    // LD_H_B;
    // LD_L_C;
    st.hl = st.bc;
    // LD_DE(mString_899ac);
    st.de = U82C(String_899ac);
    // CALL(aPlaceString);
    PlaceString(&st, st.hl);
    // RET;
}

const char String_899ac[] = "'S CARD@"; //db ['"の\u3000めいし@"'];

// Mobile_CardMenu_PrintPlayerName
void Function899b2(void){
    // LD_BC(wPlayerName);
    // CALL(aFunction89346);
    // IF_C goto asm_899bf;
    // LD_DE(wPlayerName);
    // goto asm_899c2;
    
// asm_899bf:
    // LD_DE(mString_89116);
    
// asm_899c2:
    uint8_t* de = (Function89346(gPlayer.playerName) == NULL)? U82C(String_89116): gPlayer.playerName;
    // hlcoord(6, 4, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(de, coord(4, 5, wram->wTilemap));
    // RET;
}

void Function899c9(tile_t* hl){
    // LD_DE(wPlayerID);
    // LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    // CALL(aPrintNum);
    PrintNum(hl, &gPlayer.playerID, PRINTNUM_LEADINGZEROS | 2, 5);
    // RET;
}

void Function899d3(void){
    // hlcoord(1, 4, wTilemap);
    // CALL(aFunction89753);
    Function89753(coord(1, 4, wram->wTilemap));
    FunctionLine(coord(1, 5, wram->wTilemap));
    // hlcoord(2, 5, wTilemap);
    // CALL(aFunction8975b);
    Function8975b(coord(2, 6, wram->wTilemap));
    // hlcoord(1, 9, wTilemap);
    // CALL(aFunction89771);
    Function89771(coord(1, 9, wram->wTilemap));
    // hlcoord(1, 11, wTilemap);
    // CALL(aFunction8977a);
    Function8977a(coord(1, 11, wram->wTilemap));
    // hlcoord(1, 5, wTilemap);
    // CALL(aFunction89797);
    Function89797(coord(1, 6, wram->wTilemap));
    // hlcoord(2, 4, wTilemap);
    // CALL(aFunction89962);
    Function89962(coord(2, 4, wram->wTilemap));
    // hlcoord(2, 9, wTilemap);
    // CALL(aFunction89915);
    Function89915(coord(2, 9, wram->wTilemap));
    // RET;
}

void Function899fe(tile_t* hl, uint8_t* bc){
    // PUSH_BC;
    // PUSH_HL;
    // LD_HL(0x0019);
    // ADD_HL_BC;
    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // CALL(aFunction89a0c);
    Function89a0c(hl, bc + 0x0019);
    // POP_BC;
    // RET;
}

// Mobile_CardMenu_PrintEZChatMessage
void Function89a0c(tile_t* hl, uint8_t* bc){
    // PUSH_HL;
    // CALL(aFunction89363);
    uint8_t* hl2 = Function89363(bc);
    // POP_HL;
    // IF_C goto asm_89a1c;
    if(hl2) {
        // LD_D_H;
        // LD_E_L;
        // FARCALL(aFunction11c08f);
        EZChat_RenderWords(hl, (const u8_pair_s*)bc);
        // RET;
        return;
    }

// asm_89a1c:
    // LD_DE(mString_89153);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_89153), hl);
    // RET;
}

void Function89a23(void){
    // hlcoord(0, 11, wTilemap);
    // LD_B(0x4);
    // LD_C(0x12);
    // CALL(aFunction8921f);
    Function8921f(coord(0, 11, wram->wTilemap), 0x4, 0x12);
    // RET;
}

// PlaceSaveCancelText
void Function89a2e(void){
    // hlcoord(11, 12, wTilemap);
    // LD_B(0x2);
    // LD_C(0x6);
    // CALL(aTextbox);
    Textbox(coord(9, 12, wram->wTilemap), 0x2, 0x8);
    // hlcoord(13, 13, wTilemap);
    // LD_DE(mString_89a4e);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_89a4e), coord(11, 13, wram->wTilemap));
    // hlcoord(13, 14, wTilemap);
    // LD_DE(mString_89a53);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_89a53), coord(11, 14, wram->wTilemap));
    // CALL(aFunction89655);
    Function89655();
    // RET;
}

const char String_89a4e[] = "SAVE"; //db ['"けってい@"'];
const char String_89a53[] = "CANCEL"; //db ['"やめる@"'];

static void Function89a57_PlayPocketSwitchSFX(void){
    // PUSH_AF;
    // LD_DE(SFX_SWITCH_POCKETS);
    // CALL(aPlaySFX);
    PlaySFX(SFX_SWITCH_POCKETS);
    // POP_AF;
    // RET;
}

static bool Function89a57_Function89ad4(uint8_t* bc){
    // PUSH_DE;
    // CALL(aFunction8932d);  // find a non-space character within 5 bytes of bc
    // IF_C goto no_nonspace_character;
    if(Function8932d(bc) != NULL) {
        // LD_HL(17);
        // ADD_HL_BC;
        uint8_t* hl = bc + PLAYER_NAME_LENGTH * 2 + 2 + 2 + 1;
        // CALL(aFunction89b45);
        // IF_C goto finish_decode;
        if(Function89b45(hl))
            return true;
    }

// no_nonspace_character:
    // AND_A_A;

// finish_decode:
    // POP_DE;
    // RET;
    return false;
}

static void Function89a57_Function89ae6(void){
    // LD_HL(wd031);
    // XOR_A_A;
    // LD_hl_A;
    wram->wd031[0] = 0;
    // LD_A_addr(wMenuSelection);
    uint8_t sel = wram->wMenuSelection;

    while(sel >= 6) {
    // loop2:
        // CP_A(6);
        // IF_C goto load_and_ret;
        // SUB_A(5);
        // LD_C_A;
        sel -= 5;
        // LD_A_hl;
        // ADD_A(5);
        // LD_hl_A;
        wram->wd031[0] += 5;
        // LD_A_C;
        // goto loop2;
    }

// load_and_ret:
    // LD_addr_A(wd030);
    wram->wd030[0] = sel;
    // RET;
}

static bool Function89a57_Function89ac7(void){
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // CALL(aFunction8931b);
    // CALL(aFunction89a57_Function89ad4);
    bool res = Function89a57_Function89ad4(Function8931b());
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
    return res;
}

static bool Function89a57_ApplyCursorMovement(uint8_t d, uint8_t e){
    // LD_A_addr(wMenuSelection);
    // LD_C_A;
    uint8_t c = wram->wMenuSelection;
    // PUSH_BC;

    do {
    // loop:
        // LD_A_addr(wMenuSelection);
        // CP_A_D;
        // IF_Z goto equal_to_d;
        if(wram->wMenuSelection == d) {
        // equal_to_d:
            // POP_BC;
            // LD_A_C;
            // LD_addr_A(wMenuSelection);
            wram->wMenuSelection = c;
            // SCF;
            // RET;
            return true;
        }
        // ADD_A_E;
        // IF_NZ goto not_zero;
        if((uint8_t)(wram->wMenuSelection + e) == 0) {
            // INC_A;
            wram->wMenuSelection = 1;
        }
        else {
        // not_zero:
            // LD_addr_A(wMenuSelection);
            wram->wMenuSelection += e;
        }
        // CALL(aFunction89a57_Function89ac7);  // BCD conversion of data in SRAM?
        // IF_NC goto loop;
    } while(!Function89a57_Function89ac7());
    // CALL(aFunction89a57_Function89ae6);  // split [wMenuSelection] into [wd030] + [wd031] where [wd030] <= 5
    Function89a57_Function89ae6();
    // POP_BC;
    // AND_A_A;
    // RET;
    return false;
}

static bool Function89a57_MoveCursorDown(void){
    // LD_D(40);
    // LD_E(1);
    // CALL(aFunction89a57_ApplyCursorMovement);
    // RET;
    return Function89a57_ApplyCursorMovement(40, 1);
}

static bool Function89a57_MoveCursorUp(void){
    // LD_D(1);
    // LD_E(-1);
    // CALL(aFunction89a57_ApplyCursorMovement);
    // RET;
    return Function89a57_ApplyCursorMovement(1, (uint8_t)-1);
}

u8_flag_s Function89a57(void){
    // CALL(aJoyTextDelay_ForcehJoyDown);  // joypad
    uint8_t c = JoyTextDelay_ForcehJoyDown();
    // BIT_C(D_UP_F);
    // IF_NZ goto d_up;
    if(bit_test(c, D_UP_F)) {
    // d_up:
        // CALL(aFunction89a57_MoveCursorUp);
        bool same = Function89a57_MoveCursorUp();
        // CALL_NC (aFunction89a57_PlayPocketSwitchSFX);
        if(!same)
            Function89a57_PlayPocketSwitchSFX();
        // LD_A(0x0);
        // RET;
        return u8_flag(0x0, same);
    }
    // BIT_C(D_DOWN_F);
    // IF_NZ goto d_down;
    else if(bit_test(c, D_DOWN_F)) {
    // d_down:
        // CALL(aFunction89a57_MoveCursorDown);
        bool same = Function89a57_MoveCursorDown();
        // CALL_NC (aFunction89a57_PlayPocketSwitchSFX);
        if(!same)
            Function89a57_PlayPocketSwitchSFX();
        // LD_A(0x0);
        // RET;
        return u8_flag(0x0, same);
    }
    // BIT_C(A_BUTTON_F);
    // IF_NZ goto a_b_button;
    // BIT_C(B_BUTTON_F);
    // IF_NZ goto a_b_button;
    else if(bit_test(c, A_BUTTON_F) || bit_test(c, B_BUTTON_F)) {
    // a_b_button:
        // LD_A(0x1);
        // AND_A_A;
        // RET;
        return u8_flag(0x1, false);
    }
    // BIT_C(START_F);
    // IF_NZ goto start_button;
    else if(bit_test(c, START_F)) {
    // start_button:
        // LD_A(0x2);
        // AND_A_A;
        // RET;
        return u8_flag(0x2, false);
    }
    // SCF;
    // RET;
    return u8_flag(c, true);
}

// Mobile22_Mobile_Layout_LoadPals
void Function89b00(void){
    // FARCALL(aMG_Mobile_Layout_LoadPals);
    MG_Mobile_Layout_LoadPals();
    // RET;
}

void Function89b07(void){
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // CALL(aDelayFrame);
    DelayFrame();
    // FARCALL(aFunction4a3a7);
    Function4a3a7();
    // RET;
}

void Function89b14(void){
//  //  unreferenced
    CALL(aClearBGPalettes);
    CALL(aFunction89b07);
    CALL(aFunction89b00);
    RET;

}

// Mobile22_LoadMobileGFXAndPals
void Function89b1e(void){
    // FARCALL(aFunction4a485);
    Function4a485();
    // CALL(aFunction89b00);
    Function89b00();
    // RET;
}

void Function89b28(void){
    // CALL(aFunction891de);
    Function891de();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893e2);
    Function893e2();
    // CALL(aCall_ExitMenu);
    ExitMenu();
    // CALL(aFunction891ab);
    Function891ab();
    // CALL(aSetPalettes);
    SetPalettes();
    // RET;
}

void Function89b3b(tile_t* de, uint8_t b, uint8_t c){
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // FARCALL(aFunction48cda);
    Function48cda(de, b, c);
    // RET;
}

bool Function89b45(uint8_t* hl){
// some sort of decoder?
// BCD?
    // PUSH_HL;
    // PUSH_BC;
    // LD_C(0x10);
    uint8_t c = 0x10;
    // LD_E(0x0);
    uint8_t e = 0;

    do {
    // loop:
        // LD_A_hli;
        // LD_B_A;
        uint8_t b = *(hl++);
        // AND_A(0xf);
        // CP_A(10);
        // IF_C goto low_nybble_less_than_10;
        if((b & 0xf) >= 10) {
            // LD_A_C;
            // CP_A(0xb);
            // IF_NC goto clear_carry;
            // goto set_carry;
            return c < 0xb;
        }

    // low_nybble_less_than_10:
        // DEC_C;
        --c;
        // SWAP_B;
        b = (b >> 4);
        // INC_E;
        e++;
        // LD_A_B;
        // AND_A(0xf);
        // CP_A(10);
        // IF_C goto high_nybble_less_than_10;
        if((b & 0xf) >= 10) {
            // LD_A_C;
            // CP_A(0xb);
            // IF_NC goto clear_carry;
            // goto set_carry;
            return c < 0xb;
        }

    // high_nybble_less_than_10:
        // INC_E;
        // DEC_C;
        // IF_NZ goto loop;
    } while(++e, --c != 0);
    // DEC_E;
    --e;

// set_carry:
    // SCF;
    // goto finish;
    return true;

// clear_carry:
    // AND_A_A;

// finish:
    // POP_BC;
    // POP_HL;
    // RET;
}

void Function89b78(tile_t* hl, uint8_t e){
    // PUSH_BC;
    // LD_A_addr(wd010);
    // CP_A(0x10);
    // IF_C goto asm_89b8c;
    if(wram->wd010[0] >= 0x10) {
        // LD_A_E;
        // AND_A_A;
        // IF_Z goto asm_89b89;
        if(e != 0) {
            // LD_C_E;
        // asm_89b85:
            // INC_HL;
            // DEC_C;
            // IF_NZ goto asm_89b85;
            hl += e;
        }

    // asm_89b89:
        // LD_A(0x7f);
        // LD_hl_A;
        *hl = 0x7f;
    }

// asm_89b8c:
    // LD_A_addr(wd010);
    // INC_A;
    // AND_A(0x1f);
    // LD_addr_A(wd010);
    wram->wd010[0] = (wram->wd010[0] + 1) & 0x1f;
    // POP_BC;
    // RET;
}

void Function89b97(void){
    // CALL(aFunction89c34);
    // IF_C goto asm_89ba0;
    if(!Function89c34()) {
        // CALL(aFunction89448);
        Function89448();
        // RET;
        return;
    }

// asm_89ba0:
    // LD_A_addr(wd011);
    // LD_HL(mUnknown_89bd8);
    // AND_A_A;
    // IF_Z goto asm_89bae;

// asm_89ba9:
    // INC_HL;
    // INC_HL;
    // DEC_A;
    // IF_NZ goto asm_89ba9;
    const uint8_t* hl = Unknown_89bd8[wram->wd014];

// asm_89bae:
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(wVirtualOAMSprite00);
    struct SpriteOAM* de = wram->wVirtualOAMSprite;

    while(*hl != 0xff) {
    // asm_89bb4:
        // LD_A_hli;
        // CP_A(0xff);
        // RET_Z ;
        // LD_C_A;
        uint8_t c = *(hl++);
        // LD_B(0);
        uint8_t b = 0;

        do {
        // asm_89bbb:
            // PUSH_HL;
            // LD_A_hli;
            // LD_de_A;  // y
            // INC_DE;
            de->yCoord = hl[0];
            // LD_A_hli;
            // ADD_A_B;
            // LD_de_A;  // x
            // INC_DE;
            de->xCoord = hl[1] + b;
            // LD_A(0x08);
            // ADD_A_B;
            // LD_B_A;
            b += 0x8;
            // LD_A_hli;  // tile id
            // LD_de_A;
            // INC_DE;
            de->tileID = hl[2];
            // LD_A_hli;  // attributes
            // LD_de_A;
            // INC_DE;
            de->attributes = hl[3];
            de++;
            // POP_HL;
            // DEC_C;
            // IF_NZ goto asm_89bbb;
        } while(--c != 0);
        // LD_B(0x0);
        // LD_C(0x4);
        // ADD_HL_BC;
        hl += 0x4;
        // goto asm_89bb4;
    }
}

const uint8_t* const Unknown_89bd8[] = {
    Unknown_89be0, // name
    Unknown_89bf5, // phone number
    Unknown_89c0a, // save
    Unknown_89c1f, // cancel
};

const uint8_t Unknown_89be0[] = {
    0x01, 0x12, 0x46, 0x01, 0, // 0x01, 0x12, 0x4e, 0x01, 0,
    0x01, 0x19, 0x46, 0x01, 0 | Y_FLIP, // 0x01, 0x19, 0x4e, 0x01, 0 | Y_FLIP,
    0x01, 0x12, 0x7a, 0x01, 0 | X_FLIP, // 0x01, 0x12, 0x72, 0x01, 0 | X_FLIP,
    0x01, 0x19, 0x7a, 0x01, 0 | X_FLIP | Y_FLIP, // 0x01, 0x19, 0x72, 0x01, 0 | X_FLIP | Y_FLIP,
    (uint8_t)-1,  // end
};

const uint8_t Unknown_89bf5[] = {
    0x01, 0x60, 0x16, 0x01, 0,
    0x01, 0x62, 0x16, 0x01, 0 | Y_FLIP,
    0x01, 0x60, 0x92, 0x01, 0 | X_FLIP,
    0x01, 0x62, 0x92, 0x01, 0 | X_FLIP | Y_FLIP,
    (uint8_t)-1,  // end
};

const uint8_t Unknown_89c0a[] = {
    0x01, 0x78, 0x56, 0x01, 0, // 0x01, 0x78, 0x66, 0x01, 0,
    0x01, 0x78, 0x56, 0x01, 0 | Y_FLIP, // 0x01, 0x78, 0x66, 0x01, 0 | Y_FLIP,
    0x01, 0x78, 0x92, 0x01, 0 | X_FLIP,
    0x01, 0x78, 0x92, 0x01, 0 | X_FLIP | Y_FLIP,
    (uint8_t)-1,  // end
};

const uint8_t Unknown_89c1f[] = {
    0x01, 0x80, 0x56, 0x01, 0, // 0x01, 0x80, 0x66, 0x01, 0,
    0x01, 0x80, 0x56, 0x01, 0 | Y_FLIP,  // 0x01, 0x80, 0x66, 0x01, 0 | Y_FLIP,
    0x01, 0x80, 0x92, 0x01, 0 | X_FLIP,
    0x01, 0x80, 0x92, 0x01, 0 | X_FLIP | Y_FLIP,
    (uint8_t)-1,  // end
};

bool Function89c34(void){
    // PUSH_BC;
    // LD_A_addr(wd012);
    // LD_C_A;
    uint8_t c = wram->wd012;
    // INC_A;
    // AND_A(0xf);
    // LD_addr_A(wd012);
    wram->wd012 = (c + 1) & 0xf;
    // LD_A_C;
    // CP_A(0x8);
    // POP_BC;
    // RET;
    return c < 0x8;
}

void Function89c44(uint8_t d, uint8_t e, uint8_t b, uint8_t c){
    // CALL(aFunction89c34);
    // IF_C goto asm_89c4f;
    if(!Function89c34()) {
        // PUSH_DE;
        // CALL(aFunction89448);
        Function89448();
        // POP_DE;
        // RET;
        return;
    }

// asm_89c4f:
    // LD_HL(wVirtualOAMSprite00);
    // PUSH_DE;
    // LD_A_B;
    // LD_hli_A;  // y
    wram->wVirtualOAMSprite[0].yCoord = b;
    // LD_D(0x8);
    // LD_A_E;
    // AND_A_A;
    // LD_A_C;
    uint8_t x = c;
    // IF_Z goto asm_89c60;
    if(e != 0) {
    // asm_89c5c:
        // ADD_A_D;
        // DEC_E;
        // IF_NZ goto asm_89c5c;
        x += 0x8 * e;
    }

// asm_89c60:
    // POP_DE;
    // LD_hli_A;  // x
    wram->wVirtualOAMSprite[0].xCoord = x;
    // LD_A_D;
    // LD_hli_A;  // tile id
    wram->wVirtualOAMSprite[0].tileID = d;
    // XOR_A_A;
    // LD_hli_A;  // attributes
    wram->wVirtualOAMSprite[0].attributes = 0;
    // RET;
}

u8_flag_s Function89c67(void){
//  menu scrolling?
static const uint8_t ScrollData0[] = {
    0, 2, 0, 0,
    1, 3, 0, 0,
    2, 4, 0, 0,
    3, 0, 0, 0,
};

static const uint8_t ScrollData1[] = {
    0, 0, 0, 0,
    0, 3, 0, 0,
    2, 4, 0, 0,
    3, 0, 0, 0,
};
    // CALL(aJoyTextDelay_ForcehJoyDown);  // joypad
    uint8_t c = JoyTextDelay_ForcehJoyDown();
    // LD_B(0x0);
    // BIT_C(A_BUTTON_F);
    // IF_Z goto not_a_button;
    if(bit_test(c, A_BUTTON_F)) {
        // LD_B(0x1);
        // AND_A_A;
        // RET;
        return u8_flag(0x1, false);
    }

// not_a_button:
    // BIT_C(B_BUTTON_F);
    // IF_Z goto not_b_button;
    if(bit_test(c, B_BUTTON_F)) {
        // SCF;
        // RET;
        return u8_flag(0x0, true);
    }

// not_b_button:
    uint8_t a = 0;
    // XOR_A_A;
    // BIT_C(D_UP_F);
    // IF_Z goto not_d_up;
    // LD_A(0x1);
    if(bit_test(c, D_UP_F))
        a = 0x1;

// not_d_up:
    // BIT_C(D_DOWN_F);
    // IF_Z goto not_d_down;
    // LD_A(0x2);
    if(bit_test(c, D_DOWN_F))
        a = 0x2;

// not_d_down:
    // BIT_C(D_LEFT_F);
    // IF_Z goto not_d_left;
    // LD_A(0x3);
    if(bit_test(c, D_LEFT_F))
        a = 0x3;

// not_d_left:
    // BIT_C(D_RIGHT_F);
    // IF_Z goto not_d_right;
    // LD_A(0x4);
    if(bit_test(c, D_RIGHT_F))
        a = 0x4;

// not_d_right:
    // AND_A_A;
    // RET_Z ;  // no dpad pressed
    if(a == 0)
        return u8_flag(0x0, false);
    // DEC_A;
    // LD_C_A;
    c = a - 1;
    // LD_D(0x0);
    // LD_HL(mFunction89c67_ScrollData0);
    // LD_A_addr(wd02f);
    // AND_A_A;
    // IF_Z goto got_data;
    // LD_HL(mFunction89c67_ScrollData1);
    const uint8_t* hl = (wram->wd02f[0] == 0)? ScrollData0: ScrollData1;

// got_data:
    // LD_A_addr(wd011);
    uint8_t e = wram->wd014;
    // AND_A_A;
    // IF_Z goto got_row;
    // LD_E(0x4);

// add_n_times:
    // ADD_HL_DE;
    // DEC_A;
    // IF_NZ goto add_n_times;

// got_row:
    // LD_E_C;
    // ADD_HL_DE;
    hl += (e * 0x4) + c;
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    if(*hl == 0)
        return u8_flag(0x0, false);
    // DEC_A;
    // LD_addr_A(wd011);
    wram->wd014 = (*hl) - 1;
    // XOR_A_A;
    // LD_addr_A(wd012);
    wram->wd012 = 0;
    // RET;
    return u8_flag(0x0, false);
}

void Function89cdf(uint8_t b, uint8_t c){
    // LD_A(0x10);
    // ADD_A_B;
    // LD_B_A;
    b += 0x10;
    // LD_A(0x8);
    // ADD_A_C;
    // LD_C_A;
    c += 0x8;
    // LD_E(0x2);
    uint8_t e = 2;
    // LD_A(0x2);
    uint8_t a = 2;
    // LD_HL(wVirtualOAMSprite00);
    struct SpriteOAM* hl = wram->wVirtualOAMSprite;

    do {
    // asm_89cee:
        // PUSH_AF;
        // PUSH_BC;
        // LD_D(0x4);
        uint8_t d = 4;

        do {
        // asm_89cf2:
            // LD_A_B;
            // LD_hli_A;  // y
            hl->yCoord = b;
            // LD_A_C;
            // LD_hli_A;  // x
            hl->xCoord = c;
            // LD_A_E;
            // LD_hli_A;  // tile id
            hl->tileID = e;
            // LD_A(0x1);
            // LD_hli_A;  // attributes
            hl->attributes = 0x1;
            hl++;
            // LD_A(0x8);
            // ADD_A_C;
            // LD_C_A;
            c += 0x8;
            // INC_E;
            // DEC_D;
            // IF_NZ goto asm_89cf2;
        } while(e++, --d != 0);
        // POP_BC;
        // LD_A(0x8);
        // ADD_A_B;
        // LD_B_A;
        b += 0x8;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_89cee;
    } while(--a != 0);
    // RET;
}

void Function89d0d(void){
    static const uint16_t Palette1[] = {
        rgb(31, 31, 31),
        rgb(19, 19, 19),
        rgb(15, 15, 15),
        rgb( 0,  0,  0),
    };
    static const uint16_t Palette2[] = {
        rgb(31, 31, 31),
        rgb(19, 19, 19),
        rgb(19, 19, 19),
        rgb( 0,  0,  0),
    };
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);

    // LD_C(8);
    uint8_t c = 8;
    // LD_DE(wBGPals1);
    uint8_t* de = wram->wBGPals1;

    do {
    // loop:
        // PUSH_BC;
        // LD_HL(mFunction89d0d_Palette1);
        // LD_BC(1 * PALETTE_SIZE);
        // CALL(aCopyBytes);
        CopyBytes(de, Palette1, 1 * PALETTE_SIZE);
        de += 1 * PALETTE_SIZE;
        // POP_BC;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

    // LD_HL(mFunction89d0d_Palette2);
    // LD_DE(wBGPals1 + 2 * PALETTE_SIZE);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(de, Palette2, 1 * PALETTE_SIZE);

    // POP_AF;
    // LDH_addr_A(rSVBK);

    // CALL(aSetPalettes);
    SetPalettes();
    // FARCALL(aPrintMail);
    PrintMail();
    // CALL(aMobile22_SetBGMapMode1);
    Mobile22_SetBGMapMode1();
    // LD_C(24);
    // CALL(aDelayFrames);
    DelayFrames(24);
    // CALL(aRestartMapMusic);
    RestartMapMusic();
    // RET;
}

void Function89d5e(const struct MenuHeader *hl, uint8_t a){
    // PUSH_AF;
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(hl);
    // POP_AF;
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = a;
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // CALL(aPlaceVerticalMenuItems);
    PlaceVerticalMenuItems();
    // CALL(aInitVerticalMenuCursor);
    InitVerticalMenuCursor(GetMenuData());
    // LD_HL(w2DMenuFlags1);
    // SET_hl(7);
    bit_set(wram->w2DMenuFlags1, 7);
    // RET;
}

u8_flag_s Function89d75(void (*const func)(void)){
    // PUSH_HL;
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // CALL(av_hl_);
    func();
    // FARCALL(aMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    Mobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap();
    // POP_HL;
    // JR(masm_89d90);
    return asm_89d90(func);
}

u8_flag_s Function89d85(void (*const func)(void)){
    // PUSH_HL;
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // CALL(av_hl_);
    func();
    // CALL(aCGBOnly_CopyTilemapAtOnce);
    CGBOnly_CopyTilemapAtOnce();
    // POP_HL;

    return asm_89d90(func);
}

u8_flag_s asm_89d90(void (*const func)(void)){
    u8_flag_s res;
    do {
        // CALL(aMobile22_SetBGMapMode0);
        Mobile22_SetBGMapMode0();
        // PUSH_HL;
        // CALL(av_hl_);
        func();
        // CALL(aFunction89dab);
        res = Function89dab();
        // LD_A_addr(wMenuCursorY);
        // PUSH_AF;
        uint8_t y = wram->wMenuCursorY;
        // CALL(aFunction891ab);
        Function891ab();
        // POP_AF;
        // POP_HL;
        // IF_C goto asm_89da9;
        if(res.flag) {
        // asm_89da9:
            // AND_A_A;
            // RET;
            return u8_flag(y, false);
        }
        // JR_Z (masm_89d90);
    } while(res.a == 0);
    // SCF;
    // RET;
    return u8_flag(res.a, true);
}

// CardMenu_CheckJoypad?
u8_flag_s Function89dab(void){
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // FARCALL(aMobileMenuJoypad);
    uint8_t c = MobileMenuJoypad();
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // LD_A_C;
    // LD_HL(wMenuJoypadFilter);
    // AND_A_hl;
    c &= wram->wMenuJoypadFilter;
    // RET_Z ;
    if(c == 0)
        return u8_flag(0, false);
    // BIT_A(0);
    // IF_NZ goto asm_89dc7;
    if(bit_test(c, A_BUTTON_F)) {
    // asm_89dc7:
        if(wram->wMenuCursorY == wram->w2DMenuNumRows)
            goto asm_89dd9;
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_A_addr(w2DMenuNumRows);
        // LD_C_A;
        // LD_A_addr(wMenuCursorY);
        // CP_A_C;
        // IF_Z goto asm_89dd9;
        // CALL(aPlaceHollowCursor);
        PlaceHollowCursor();
        // SCF;
        // RET;
        return u8_flag(wram->wMenuCursorY, true);
    }
    // BIT_A(1);
    // IF_NZ goto asm_89dd9;
    else if(bit_test(c, B_BUTTON_F)) {
    asm_89dd9:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_A(0x1);
        // AND_A_A;
        // RET;
        return u8_flag(0x1, false);
    }
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

// Mobile_CardMenu_Top?
void Function89de0(void){
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aFunction89e0a);
    // IF_C goto asm_89e00;
    if(!Function89e0a()) {
        // LD_C(0x1);
        uint8_t c = 0x1;
        uint8_t e;

        while((e = Function8a31c(c), e != 0)) {
        // asm_89dea:
            // CALL(aFunction8a31c);
            // IF_Z goto asm_89dfd;
            // LD_A_addr(wMenuCursorY);
            // LD_C_A;
            c = wram->wMenuCursorY;
            // PUSH_BC;
            // LD_HL(mJumptable_89e04);
            // LD_A_E;
            // DEC_A;
            // RST(aJumpTable);
            Jumptable_89e04(e - 1);
            // POP_BC;
            // goto asm_89dea;
        }

    // asm_89dfd:
        // CALL(aFunction891fe);
        Function891fe();
    }

// asm_89e00:
    // CALL(aFunction8917a);
    Function8917a();
    // RET;
}

void Jumptable_89e04(uint8_t a){
    switch(a) {
        case 0: return Function8a62c();
        case 1: return Function8a999();
        case 2: return Function8ab93();
    }
}

bool Function89e0a(void){
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // CALL(aFunction8b3b0);
    u8_flag_s res = Function8b3b0();
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_HL(mJumptable_89e18);
    // RST(aJumpTable);
    // RET;
    return Jumptable_89e18(res.a);
}

bool Jumptable_89e18(uint8_t a){
    switch(a) {
        default:
        case 0: return Function89e1e();
        case 1: return Function8a116();
        case 2: return Function8a2aa();
    }
}

bool Function89e1e(void){
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // LD_BC(0xa037);
    // CALL(aFunction8b36c);
    Function8b36c(GBToRAMAddr(s4_a037));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // XOR_A_A;
    // LD_addr_A(wd02d);
    wram->wd02d = 0;

    return asm_89e2e();
}

bool asm_89e2e(void){
    // LD_A_addr(wd02d);
    // LD_HL(mJumptable_89e3c);
    // RST(aJumpTable);
    // RET;
    return Jumptable_89e3c();
}

void Function89e36(void){
    // LD_HL(wd02d);
    // INC_hl;
    wram->wd02d++;
    // JR(masm_89e2e);
}

// MobileCardFolder_IntroJumptable
bool Jumptable_89e3c(void){
    while(1) {
        switch(wram->wd02d) {
            case  0: Function89e6f(); continue;
            case  1: Function89fed(); continue;
            case  2: Function89ff6(); continue;
            case  3: Function8a03d(); continue;
            case  4: Function89eb9(); continue;
            case  5: Function89efd(); continue;
            case  6: Function89fce(); continue;
            case  7: Function8a04c(); continue;
            case  8: Function8a055(); continue;
            case  9: Function8a0e6(); continue;
            case 10: Function8a0ec(); continue;
            case 11: Function8a0f5(); continue;
            case 12: return Function89e58();
            case 13: return Function89e68();
        }
    }
}

bool Function89e58(void){
    // LD_A(0x1);
    // CALL(aFunction8a2fe);
    Function8a2fe(0x1);
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aFunction893e2);
    Function893e2();
    // CALL(aFunction89168);
    Function89168();
    // AND_A_A;
    // RET;
    return false;
}

bool Function89e68(void){
    // CALL(aFunction891fe);
    Function891fe();
    // LD_A(0x1);
    // SCF;
    // RET;
    return true;
}

void Function89e6f(void){
    // CALL(aFunction891de);
    Function891de();
    // CALL(aFunction89245);
    Function89245();
    // CALL(aFunction89ee1);
    Function89ee1();
    // CALL(aFunction89e9a);
    Function89e9a();
    // hlcoord(7, 4, wTilemap);
    // CALL(aFunction8a58d);
    Function8a58d(coord(7, 4, wram->wTilemap));
    // LD_A(0x5);
    // hlcoord(7, 4, wAttrmap);
    // CALL(aFunction8a5a3);
    Function8a5a3(coord(7, 4, wram->wAttrmap), 0x5);
    // LD_A(0x6);
    // hlcoord(10, 4, wAttrmap);
    // CALL(aFunction8a5a3);
    Function8a5a3(coord(10, 4, wram->wAttrmap), 0x6);
    // CALL(aFunction891ab);
    Function891ab();
    // CALL(aSetPalettes);
    SetPalettes();
    // JP(mFunction89e36);
    Function89e36();
}

void Function89e9a(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mPalette_89eb1);
    // LD_DE(wBGPals1 + PALETTE_SIZE * 5);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals1 + PALETTE_SIZE * 5, Palette_89eb1, 1 * PALETTE_SIZE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

const uint16_t Palette_89eb1[] = {
    rgb(31, 31, 31),
    rgb(31, 31, 31),
    rgb(27, 19,  0),
    rgb( 0,  0,  0),
};

void Function89eb9(void){
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aFunction89ee1);
    Function89ee1();
    // CALL(aFunction89e9a);
    Function89e9a();
    // hlcoord(7, 4, wTilemap);
    // CALL(aFunction8a58d);
    Function8a58d(coord(7, 4, wram->wTilemap));
    // LD_A(0x5);
    // hlcoord(7, 4, wAttrmap);
    // CALL(aFunction8a5a3);
    Function8a5a3(coord(7, 4, wram->wAttrmap), 0x5);
    // LD_A(0x6);
    // hlcoord(10, 4, wAttrmap);
    // CALL(aFunction8a5a3);
    Function8a5a3(coord(10, 4, wram->wAttrmap), 0x6);
    // CALL(aFunction891ab);
    Function891ab();
    // CALL(aSetPalettes);
    SetPalettes();
    // JP(mFunction89e36);
    Function89e36();
}

void Function89ee1(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893e2);
    Function893e2();
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // FARCALL(aFunction4a3a7);
    Function4a3a7();
    // FARCALL(aMG_Mobile_Layout_CreatePalBoxes);
    MG_Mobile_Layout_CreatePalBoxes();
    // hlcoord(1, 0, wTilemap);
    // CALL(aFunction8a53d);
    Function8a53d(coord(1, 0, wram->wTilemap));
    // RET;
}

void Function89efd(void){
    // LD_HL(wd012);
    // LD_A(0xff);
    // LD_hli_A;
    wram->wd012 = 0xff;
    // XOR_A_A;
    // for(int rept = 0; rept < 4; rept++){
    // LD_hli_A;
    // }
    // LD_hl_A;
    ByteFill(&wram->wd013, 5, 0);

asm_89f09:
    // LD_HL(wd012);
    // INC_hl;
    // LD_A_hli;
    // AND_A(0x3);
    // IF_NZ goto asm_89f2e;
    // LD_A_hl;
    // CP_A(0x4);
    // IF_NC goto asm_89f2e;
    if((++wram->wd012 & 0x3) == 0 && wram->wd013 < 0x4) {
        // LD_B(0x32);
        uint8_t b = 0x32;
        // INC_hl;
        // LD_A_hl;
        // DEC_A;
        uint8_t a = (++wram->wd013) - 1;
        // IF_Z goto asm_89f26;
        if(a != 0) {
            // LD_C_A;

            // do {
            // asm_89f1f:
                // LD_A(0xb);
                // ADD_A_B;
                // LD_B_A;
                // DEC_C;
                // IF_NZ goto asm_89f1f;
            // } while(--c != 0);
            b += (0xb * a);
        }

    // asm_89f26:
        // LD_C(0xe8);
        // LD_A_addr(wd013);
        // CALL(aFunction89fa5);
        Function89fa5(wram->wd013, b, 0xe8);
    }

// asm_89f2e:
    // LD_A_addr(wd013);
    // AND_A_A;
    // IF_Z goto asm_89f58;
    for(uint8_t a = wram->wd013; a != 0; --a) {
    // asm_89f34:
        uint8_t b, c;
        // CALL(aFunction89f6a);
        Function89f6a(a, &b, &c);
        // LD_E_A;
        // LD_A_C;
        // CP_A(0xa8);
        // IF_NC goto asm_89f4d;
        // CP_A(0x46);
        // IF_C goto asm_89f4d;
        if(c < 0xa8 && c >= 0x46) {
            // LD_D(0x0);
            // DEC_E;
            // LD_HL(wd014);
            // ADD_HL_DE;
            // SET_hl(0);
            bit_set((&wram->wd014)[a - 1], 0);
            // INC_E;
            // goto asm_89f51;
        }
        else {
        // asm_89f4d:
            // LD_A(0x2);
            // ADD_A_C;
            // LD_C_A;
            c += 0x2;
        }

    // asm_89f51:
        // LD_A_E;
        // CALL(aFunction89f77);
        Function89f77(a, b, c);
        // DEC_A;
        // IF_NZ goto asm_89f34;
    }

// asm_89f58:
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_HL(wd014);
    uint8_t* hl = &wram->wd014;
    // LD_C(0x4);
    uint8_t c = 0x4;

    do {
    // asm_89f60:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto asm_89f09;
        if(*(hl++) == 0)
            goto asm_89f09;
        // DEC_C;
        // IF_NZ goto asm_89f60;
    } while(--c != 0);
    // JP(mFunction89e36);
    Function89e36();
}

void Function89f6a(uint8_t a, uint8_t* b, uint8_t* c){
    // PUSH_AF;
    // LD_DE(0x10);
    // CALL(aFunction89f9a);
    struct SpriteOAM* hl = Function89f9a(a, 0x10);
    // LD_A_hli;
    // LD_B_A;
    *b = hl->yCoord;
    // LD_A_hl;
    // LD_C_A;
    *c = hl->xCoord;
    // POP_AF;
    // RET;
}

void Function89f77(uint8_t a, uint8_t b, uint8_t c){
    // PUSH_AF;
    // LD_DE(0x10);
    // CALL(aFunction89f9a);
    struct SpriteOAM* hl = Function89f9a(a, 0x10);
    // LD_D(0x2);
    uint8_t d = 0x2;

    do {
    // asm_89f80:
        // PUSH_BC;
        uint8_t c2 = c;
        // LD_E(0x2);
        uint8_t e = 0x2;

        do {
        // asm_89f83:
            // LD_A_B;
            // LD_hli_A;
            hl->yCoord = b;
            // LD_A_C;
            // LD_hli_A;
            hl->xCoord = c2;
            // INC_HL;
            // INC_HL;
            hl++;
            // LD_A(0x8);
            // ADD_A_C;
            // LD_C_A;
            c2 += 0x8;
            // DEC_E;
            // IF_NZ goto asm_89f83;
        } while(--e != 0);
        // POP_BC;
        // LD_A(0x8);
        // ADD_A_B;
        // LD_B_A;
        b += 0x8;
        // DEC_D;
        // IF_NZ goto asm_89f80;
    } while(--d != 0);
    // POP_AF;
    // RET;
}

struct SpriteOAM* Function89f9a(uint8_t a, uint16_t de){
    // DEC_A;
    // LD_HL(wVirtualOAM);
    // AND_A_A;
    // RET_Z ;

// asm_89fa0:
    // ADD_HL_DE;
    // DEC_A;
    // IF_NZ goto asm_89fa0;
    // RET;
    return wram->wVirtualOAMSprite + ((a - 1) * (de / sizeof(wram->wVirtualOAMSprite[0])));
}

void Function89fa5(uint8_t a, uint8_t b, uint8_t c){
    // LD_DE(0x10);
    // CALL(aFunction89f9a);
    struct SpriteOAM* hl = Function89f9a(a, 0x10);
    // LD_E(0x2);
    uint8_t e = 0x2;
    // LD_D(0xa);
    uint8_t d = 0xa;

    do {
    // asm_89faf:
        // PUSH_BC;
        uint8_t c2 = c;
        // LD_A(0x2);
        uint8_t a2 = 0x2;

        do {
        // asm_89fb2:
            // PUSH_AF;
            // LD_A_B;
            // LD_hli_A;
            hl->yCoord = b;
            // LD_A_C;
            // LD_hli_A;
            hl->xCoord = c2;
            // LD_A_D;
            // INC_D;
            // LD_hli_A;
            hl->tileID = d++;
            // LD_A(0x1);
            // LD_hli_A;
            hl->attributes = 0x1;
            hl++;
            // LD_A(0x8);
            // ADD_A_C;
            // LD_C_A;
            c2 += 0x8;
            // POP_AF;
            // DEC_A;
            // IF_NZ goto asm_89fb2;
        } while(--a2 != 0);
        // POP_BC;
        // LD_A(0x8);
        // ADD_A_B;
        // LD_B_A;
        b += 0x8;
        // DEC_E;
        // IF_NZ goto asm_89faf;
    } while(--e != 0);
    // RET;
}

void Function89fce(void){
    // CALL(aFunction8a5b6);
    Function8a5b6();
    // LD_A(0x5);
    // hlcoord(7, 4, wAttrmap);
    // CALL(aFunction8a5a3);
    Function8a5a3(coord(7, 4, wram->wAttrmap), 0x5);
    // LD_A(0x6);
    // hlcoord(10, 4, wAttrmap);
    // CALL(aFunction8a5a3);
    Function8a5a3(coord(10, 4, wram->wAttrmap), 0x6);
    // CALL(aFunction89448);
    Function89448();
    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aFunction891ab);
    Function891ab();
    // JP(mFunction89e36);
    Function89e36(); // Goto the next function
}

void Function89fed(void){
    // LD_HL(mMobileCardFolderIntro1Text);
    // CALL(aPrintText);
    PrintText(MobileCardFolderIntro1Text);
    // JP(mFunction89e36);
    Function89e36(); // Goto the next function
}

void Function89ff6(void){
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893cc);
    Function893cc();
    // CALL(aFunction89807);
    Function89807();
    // CALL(aFunction89492);
    // CALL(aFunction894ca);
    Function894ca(Function89492());
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // LD_HL(0xa603);
    // LD_A(-1);
    // LD_BC(8);
    // CALL(aByteFill);
    ByteFill(GBToRAMAddr(s4_a603), 8, 0xff);
    // LD_HL(0xa603);
    // LD_DE(wd008);
    // CALL(aFunction89381);
    Function89381(wram->wd008, GBToRAMAddr(s4_a603));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // CALL(aFunction8987f);
    Function8987f();
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // hlcoord(1, 13, wTilemap);
    // LD_BC(0xa007);
    // CALL(aFunction89a0c);
    Function89a0c(coord(1, 13, wram->wTilemap), GBToRAMAddr(s4_a007));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // CALL(aFunction891ab);
    Function891ab();
    // CALL(aMobile22_PromptButton);
    Mobile22_PromptButton();
    // JP(mFunction89e36);
    Function89e36();
}

void Function8a03d(void){
    // LD_HL(mMobileCardFolderIntro2Text);
    // CALL(aMobile_EnableSpriteUpdates);
    Mobile_EnableSpriteUpdates();
    // CALL(aPrintText);
    PrintText(MobileCardFolderIntro2Text);
    // CALL(aMobile_DisableSpriteUpdates);
    Mobile_DisableSpriteUpdates();
    // JP(mFunction89e36);
    Function89e36();
}

void Function8a04c(void){
    // LD_HL(mMobileCardFolderIntro3Text);
    // CALL(aPrintText);
    PrintText(MobileCardFolderIntro3Text);
    // JP(mFunction89e36);
    Function89e36();
}

void Function8a055(void){
    // LD_C(0x7);
    uint8_t c = 0x7;
    // LD_B(0x4);
    uint8_t b = 0x4;

    do {
    // asm_8a059:
        // CALL(aFunction8a0a1);
        Function8a0a1(b, c);
        // INC_C;
        c++;
        // CALL(aFunction8a0c9);
        // PUSH_BC;
        // CALL(aFunction8a58d);
        Function8a58d(Function8a0c9(b, c));
        // POP_BC;
        // CALL(aFunction8a0de);
        uint8_t* attr = Function8a0de(b, c);
        // PUSH_BC;
        // PUSH_HL;
        // LD_A(0x5);
        // CALL(aFunction8a5a3);
        Function8a5a3(attr, 0x5);
        // POP_HL;
        // INC_HL;
        // INC_HL;
        // INC_HL;
        // LD_A(0x6);
        // CALL(aFunction8a5a3);
        Function8a5a3(attr + 3, 0x6);
        // CALL(aCGBOnly_CopyTilemapAtOnce);
        CGBOnly_CopyTilemapAtOnce();
        // POP_BC;
        // LD_A_C;
        // CP_A(0xb);
        // IF_NZ goto asm_8a059;
    } while(c != 0xb);
    // CALL(aFunction8a0a1);
    Function8a0a1(b, c);
    // hlcoord(12, 4, wTilemap);
    // CALL(aFunction8a58d);
    Function8a58d(coord(12, 4, wram->wTilemap));
    // LD_A(0x5);
    // hlcoord(12, 4, wAttrmap);
    // CALL(aFunction8a5a3);
    Function8a5a3(coord(12, 4, wram->wAttrmap), 0x5);
    // POP_HL;
    // LD_A(0x6);
    // hlcoord(15, 4, wAttrmap);
    // CALL(aFunction8a5a3);
    Function8a5a3(coord(15, 4, wram->wAttrmap), 0x6);
    // CALL(aCGBOnly_CopyTilemapAtOnce);
    CGBOnly_CopyTilemapAtOnce();
    // JP(mFunction89e36);
    Function89e36();
}

void Function8a0a1(uint8_t b, uint8_t c){
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // PUSH_BC;
    // CALL(aFunction8a0c9);
    tile_t* hl = Function8a0c9(b, c);
    // LD_E(0x6);
    uint8_t e = 0x6;

    do {
    // asm_8a0aa:
        // PUSH_HL;
        // LD_BC(0x6);
        // ADD_HL_BC;
        // LD_D_hl;
        uint8_t d = hl[0x6];
        // CALL(aFunction8a0c1);
        uint8_t a = Function8a0c1(hl + 0x6);
        // POP_HL;
        // LD_hl_D;
        *hl = d;
        // CALL(aFunction89215);
        Function89215(hl, a);
        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // DEC_E;
        // IF_NZ goto asm_8a0aa;
    } while(--e != 0);
    // POP_BC;
    // RET;
}

uint8_t Function8a0c1(tile_t* hl){
    // PUSH_HL;
    // LD_BC(wAttrmap - wTilemap);
    // ADD_HL_BC;
    // LD_A_hl;
    // POP_HL;
    // RET;
    return wram->wAttrmap[hl - wram->wTilemap];
}

// Returns wTilemap + (b * SCREEN_WIDTH) + c 
//         AKA coord(c, b, wTilemap)
tile_t* Function8a0c9(uint8_t b, uint8_t c){
    // PUSH_BC;
    // hlcoord(0, 0, wTilemap);
    // LD_DE(0x14);
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto asm_8a0d8;

// asm_8a0d4:
    // ADD_HL_DE;
    // DEC_B;
    // IF_NZ goto asm_8a0d4;

// asm_8a0d8:
    // LD_D(0x0);
    // LD_E_C;
    // ADD_HL_DE;
    // POP_BC;
    // RET;
    return coord(c, b, wram->wTilemap);
}

uint8_t* Function8a0de(uint8_t b, uint8_t c){
    // CALL(aFunction8a0c9);
    // LD_DE(wAttrmap - wTilemap);
    // ADD_HL_DE;
    // RET;
    return coord(c, b, wram->wAttrmap);
}

void Function8a0e6(void){
    // CALL(aFunction8b539);
    Function8b539();
    // JP(mFunction89e36);
    Function89e36();
}

void Function8a0ec(void){
    // LD_HL(mMobileCardFolderIntro4Text);
    // CALL(aPrintText);
    PrintText(MobileCardFolderIntro4Text);
    // JP(mFunction89e36);
    Function89e36();
}

void Function8a0f5(void){
    // CALL(aFunction8b555);
    // JP_NC (mFunction8a0ff);
    if(Function8b555()) {
        // LD_HL(wd02d);
        // INC_hl;
        wram->wd02d++;
    }

    return Function8a0ff();
}

void Function8a0ff(void){
    // JP(mFunction89e36);
    return Function89e36();
}

const txt_cmd_s MobileCardFolderIntro1Text[] = {
    text_far(v_MobileCardFolderIntro1Text)
    text_end
};

const txt_cmd_s MobileCardFolderIntro2Text[] = {
    text_far(v_MobileCardFolderIntro2Text)
    text_end
};

const txt_cmd_s MobileCardFolderIntro3Text[] = {
    text_far(v_MobileCardFolderIntro3Text)
    text_end
};

const txt_cmd_s MobileCardFolderIntro4Text[] = {
    text_far(v_MobileCardFolderIntro4Text)
    text_end
};

bool Function8a116(void){
    // LD_A(0x1);
    // LD_addr_A(wd030);
    wram->wd030[0] = 0x1;
    // LD_HL(mMenuHeader_0x8a176);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_0x8a176);

asm_8a121:
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // CALL(aFunction8a17b);
    u8_flag_s res = Function8a17b();
    // IF_C goto asm_8a16b;
    if(!res.flag) {
        // LD_A_addr(wMenuCursorY);
        // LD_addr_A(wd030);
        wram->wd030[0] = wram->wMenuCursorY;
        // DEC_D;
        // IF_Z goto asm_8a140;
        if(res.a - 1 == 0) {
        // asm_8a140:
            // CALL(aFunction89174);
            // IF_NZ goto asm_8a14c;
            if(Function89174()) {
            // asm_8a14c:
                // CALL(aWaitSFX);
                WaitSFX();
                // LD_DE(SFX_TWINKLE);
                // CALL(aPlaySFX);
                PlaySFX(SFX_TWINKLE);
                // LD_C(0x10);
                // CALL(aDelayFrames);
                DelayFrames(0x10);
            }
            // CALL(aFunction8a241);
            // IF_C goto asm_8a121;
            else if(Function8a241())
                goto asm_8a121;
            // goto asm_8a15a;
        // asm_8a15a:
            // CALL(aExitMenu);
            ExitMenu();
            // CALL(aFunction891de);
            Function891de();
            // CALL(aFunction893e2);
            Function893e2();
            // CALL(aFunction89245);
            Function89245();
            // CALL(aFunction89168);
            Function89168();
            // AND_A_A;
            // RET;
            return false;
        }
        // CALL(aFunction8a20d);
        // IF_C goto asm_8a121;
        if(Function8a20d())
            goto asm_8a121;
        // XOR_A_A;
        // CALL(aFunction8a2fe);
        Function8a2fe(0);
        // CALL(aFunction8916e);
        Function8916e();
        // goto asm_8a16b;
    }
// asm_8a16b:
    // CALL(aMobile_EnableSpriteUpdates);
    Mobile_EnableSpriteUpdates();
    // CALL(aCloseWindow);
    CloseWindow();
    // CALL(aMobile_DisableSpriteUpdates);
    Mobile_DisableSpriteUpdates();
    // SCF;
    // RET;
    return true;
}

const struct MenuHeader MenuHeader_0x8a176 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(14, 0, SCREEN_WIDTH - 1, 6),
};

u8_flag_s Function8a17b(void){
    // decoord(14, 0, wTilemap);
    // LD_B(0x5);
    // LD_C(0x4);
    // CALL(aFunction89b3b);
    Function89b3b(coord(11, 0, wram->wTilemap), 0x5, 0x7);
    // LD_HL(mMenuHeader_0x8a19a);
    // LD_A_addr(wd030);
    // CALL(aFunction89d5e);
    Function89d5e(&MenuHeader_0x8a19a, wram->wd030[0]);
    // LD_HL(mFunction8a1b0);
    // CALL(aFunction89d75);
    u8_flag_s res = Function89d75(&Function8a1b0);
    // IF_NC goto asm_8a198;
    if(res.flag) {
        // LD_A(0x0);
        res.a = 0;
    }

// asm_8a198:
    // LD_D_A;
    // RET;
    return res;
}

const struct MenuHeader MenuHeader_0x8a19a = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(11, 0, SCREEN_WIDTH - 1, 6),
    .data = &MenuData_0x8a1a2,
    .defaultOption = 1,  // default option
};

const struct MenuData MenuData_0x8a1a2 = {
    .flags = STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING | STATICMENU_WRAP,  // flags
    .verticalMenu = {
        .count = 3,  // items
        .options = (const char*[]) {
            "Open@", //db ['"ひらく@"'];
            "Delete@", //db ['"すてる@"'];
            "Cancel@" //db ['"もどる@"'];
        },
    },
};

void Function8a1b0(void){
    // hlcoord(0, 12, wTilemap);
    // LD_B(0x4);
    // LD_C(0x12);
    // CALL(aTextbox);
    Textbox(coord(0, 12, wram->wTilemap), 0x4, 0x12);
    // hlcoord(1, 14, wTilemap);
    // LD_A_addr(wMenuCursorY);
    // LD_DE(mStrings_8a1cc);
    // DEC_A;
    // LD_C_A;
    // CALL(aFunction8919e);
    // CALL(aPlaceString);
    // RET;
    PlaceStringSimple(U82C(Strings_8a1cc[wram->wMenuCursorY - 1]), coord(1, 14, wram->wTilemap));
}

const char* const Strings_8a1cc[] = {
            "Open the"          //db ['"めいし<NO>せいりと\u3000へんしゅうを"'];
    t_next  "CARD FOLDER.",     //next ['"おこないます"']
                                //db ['"@"'];

            "Delete the"        //db ['"めいしフォルダー<NO>めいしと"'];
    t_next  "CARD FOLDER.",     //next ['"あんしょうばんごう<WO>けします"']
                                //db ['"@"'];

            "Return to the"     //db ['"まえ<NO>がめん<NI>もどります"'];
    t_next  "previous screen."  //db ['"@"'];
};

// MobileCardFolder_AskDelete
bool Function8a20d(void){
    // LD_HL(mMobileCardFolderAskDeleteText);
    // CALL(aPrintText);
    PrintText(MobileCardFolderAskDeleteText);
    // LD_A(0x2);
    // CALL(aFunction89259);
    // RET_C ;
    if(Function89259(0x2))
        return true;
    // LD_HL(mMobileCardFolderDeleteAreYouSureText);
    // CALL(aPrintText);
    PrintText(MobileCardFolderDeleteAreYouSureText);
    // LD_A(0x2);
    // CALL(aFunction89259);
    // RET_C ;
    if(Function89259(0x2))
        return true;
    // XOR_A_A;
    // CALL(aFunction8a2fe);
    Function8a2fe(0);
    // LD_HL(mMobileCardFolderDeletedText);
    // CALL(aPrintText);
    PrintText(MobileCardFolderDeletedText);
    // XOR_A_A;
    // AND_A_A;
    // RET;
    return false;
}

const txt_cmd_s MobileCardFolderAskDeleteText[] = {
    text_far(v_MobileCardFolderAskDeleteText)
    text_end
};

const txt_cmd_s MobileCardFolderDeleteAreYouSureText[] = {
    text_far(v_MobileCardFolderDeleteAreYouSureText)
    text_end
};

const txt_cmd_s MobileCardFolderDeletedText[] = {
    text_far(v_MobileCardFolderDeletedText)
    text_end
};

bool Function8a241(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aFunction8a262);
    // IF_NC goto asm_8a254;
    if(Function8a262()) {
        // CALL(aFunction891fe);
        Function891fe();
        // CALL(aFunction89b28);
        Function89b28();
        // SCF;
        // RET;
        return true;
    }
    else {
    // asm_8a254:
        // CALL(aFunction891de);
        Function891de();
        // CALL(aClearBGPalettes);
        ClearBGPalettes();
        // CALL(aCall_ExitMenu);
        ExitMenu();
        // CALL(aFunction891de);
        Function891de();
        // AND_A_A;
        // RET;
        return false;
    }
}

bool Function8a262(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893e2);
    Function893e2();
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // FARCALL(aFunction4a3a7);
    Function4a3a7();
    // FARCALL(aMG_Mobile_Layout_CreatePalBoxes);
    MG_Mobile_Layout_CreatePalBoxes();
    // hlcoord(1, 0, wTilemap);
    // CALL(aFunction8a53d);
    Function8a53d(coord(1, 0, wram->wTilemap));
    // hlcoord(12, 4, wTilemap);
    // CALL(aFunction8a58d);
    Function8a58d(coord(12, 4, wram->wTilemap));
    // LD_A(0x5);
    // hlcoord(12, 4, wAttrmap);
    // CALL(aFunction8a5a3);
    Function8a5a3(coord(12, 4, wram->wAttrmap), 0x5);
    // LD_A(0x6);
    // hlcoord(15, 4, wAttrmap);
    // CALL(aFunction8a5a3);
    Function8a5a3(coord(15, 4, wram->wAttrmap), 0x6);
    // XOR_A_A;
    // LD_addr_A(wd02e);
    wram->wd02e[0] = 0;
    // LD_BC(wd013);
    // CALL(aFunction8b36c);
    Function8b36c(wram->wd013_arr);
    // CALL(aFunction8b493);
    Function8b493(wram->wd013_arr);
    // CALL(aFunction891ab);
    Function891ab();
    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aFunction8b5e7);
    // RET;
    return Function8b5e7();
}

bool Function8a2aa(void){
    // LD_HL(mMenuHeader_0x8a2ef);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_0x8a2ef);
    // LD_HL(mMobileCardFolderAskOpenOldText);
    // CALL(aPrintText);
    PrintText(MobileCardFolderAskOpenOldText);
    // LD_A(0x1);
    // CALL(aFunction89259);
    // IF_NC goto asm_8a2cf;
    if(Function89259(0x1)) {
        // LD_HL(mMobileCardFolderAskDeleteOldText);
        // CALL(aPrintText);
        PrintText(MobileCardFolderAskDeleteOldText);
        // LD_A(0x2);
        // CALL(aFunction89259);
        // IF_C goto asm_8a2ea;
        if(!Function89259(0x2)) {
            // CALL(aFunction8a20d);
            Function8a20d();
            // goto asm_8a2ea;
        }
    }
    else {
    // asm_8a2cf:
        // CALL(aExitMenu);
        ExitMenu();
        // CALL(aFunction8a241);
        // IF_C goto asm_8a2ed;
        if(!Function8a241()) {
            // LD_A(0x1);
            // CALL(aFunction8a313);
            Function8a313(0x1);
            // CALL(aCloseSRAM);
            CloseSRAM();
            // CALL(aFunction891de);
            Function891de();
            // CALL(aFunction89245);
            Function89245();
            // CALL(aFunction89168);
            Function89168();
            // AND_A_A;
            // RET;
            return false;
        }
        else {
            return true;
        }
    }

// asm_8a2ea:
    // CALL(aCloseWindow);
    CloseWindow();

// asm_8a2ed:
    // SCF;
    // RET;
    return true;
}

const struct MenuHeader MenuHeader_0x8a2ef = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 12, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1),
};

const txt_cmd_s MobileCardFolderAskOpenOldText[] = {
    text_far(v_MobileCardFolderAskOpenOldText)
    text_end
};

const txt_cmd_s MobileCardFolderAskDeleteOldText[] = {
    text_far(v_MobileCardFolderAskDeleteOldText)
    text_end
};

void Function8a2fe(uint8_t a){
    // CALL(aFunction8a313);
    Function8a313(a);
    // CALL(aFunction89305);
    Function89305();
    // LD_HL(0xa603);
    // LD_BC(0x8);
    // LD_A(-1);
    // CALL(aByteFill);
    ByteFill(GBToRAMAddr(s4_a603), 0x8, 0xff);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void Function8a313(uint8_t a){
    // LD_C_A;
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // LD_A_C;
    // LD_addr_A(0xa60b);
    gb_write(s4_a60b, a);
    // RET;
}

uint8_t Function8a31c(uint8_t c){
    // PUSH_BC;
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // FARCALL(aFunction4a3a7);
    Function4a3a7();
    // FARCALL(aMG_Mobile_Layout_CreatePalBoxes);
    MG_Mobile_Layout_CreatePalBoxes();
    // hlcoord(1, 0, wTilemap);
    // CALL(aFunction8a53d);
    Function8a53d(coord(1, 0, wram->wTilemap));
    // hlcoord(12, 4, wTilemap);
    // CALL(aFunction8a58d);
    Function8a58d(coord(12, 4, wram->wTilemap));
    // CALL(aFunction8a3b2);
    Function8a3b2();
    // POP_BC;
    // LD_A_C;
    // LD_addr_A(wMenuCursorPosition);
    wram->wMenuCursorPosition = c;
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = c;
    // CALL(aPlaceVerticalMenuItems);
    PlaceVerticalMenuItems();
    // CALL(aInitVerticalMenuCursor);
    InitVerticalMenuCursor(GetMenuData());
    // LD_HL(w2DMenuFlags1);
    // SET_hl(7);
    bit_set(wram->w2DMenuFlags1, 7);
    u8_flag_s res;

    do {
    // asm_8a34e:
        // CALL(aFunction8a3a2);
        Function8a3a2();
        // CALL(aMobile22_SetBGMapMode0);
        Mobile22_SetBGMapMode0();
        // CALL(aFunction8a453);
        Function8a453();
        // CALL(aFunction8a4d3);
        Function8a4d3();
        // CALL(aFunction8a4fc);
        Function8a4fc();
        // CALL(aFunction891ab);
        Function891ab();
        // CALL(aSetPalettes);
        SetPalettes();
        // CALL(aFunction8a383);
        res = Function8a383();
        // IF_C goto asm_8a370;
        if(res.flag) {
        // asm_8a370:
            // CALL(aFunction89448);
            Function89448();
            // CALL(aPlaceHollowCursor);
            PlaceHollowCursor();
            // CALL(aFunction8a3a2);
            Function8a3a2();
            // LD_A_addr(wMenuSelection);
            // CP_A(0xff);
            // IF_Z goto asm_8a36a;
            if(wram->wMenuSelection == 0xff)
                break;
            // LD_E_A;
            // AND_A_A;
            // RET;
            return wram->wMenuSelection;
        }
        // IF_Z goto asm_8a34e;
    } while(res.a == 0);

// asm_8a36a:
    // CALL(aFunction89448);
    Function89448();
    // XOR_A_A;
    // LD_E_A;
    // RET;
    return 0;
}

u8_flag_s Function8a383(void){
    // FARCALL(aMobileMenuJoypad);
    uint8_t c = MobileMenuJoypad() & wram->wMenuJoypadFilter;
    // LD_A_C;
    // LD_HL(wMenuJoypadFilter);
    // AND_A_hl;
    // RET_Z ;
    if(c == 0)
        return u8_flag(0, false);
    // BIT_A(0);
    // IF_NZ goto asm_8a399;
    if(bit_test(c, A_BUTTON_F)) {
    // asm_8a399:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // SCF;
        // RET;
        return u8_flag(1, true);
    }
    // BIT_A(1);
    // IF_NZ goto asm_8a39e;
    if(bit_test(c, B_BUTTON_F)) {
    // asm_8a39e:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // RET;
        return u8_flag(1, false);
    }
    // XOR_A_A;
    // RET;
    return u8_flag(0, false);
}

// Mobile22_GetCardMenuSelection
void Function8a3a2(void){
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // LD_HL(wd002);
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = (&wram->wd002)[wram->wMenuCursorY - 1];
    // RET;
}

// LoadCardFolderMenu
void Function8a3b2(void){
    // LD_A(0x1);
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = 0x1;
    // CALL(aFunction8a4fc);
    Function8a4fc();
    // CALL(aFunction8a3df);
    // IF_NC goto asm_8a3ce;
    const struct MenuHeader* hl;
    if(Function8a3df()) {
        // decoord(0, 2, wTilemap);
        // LD_B(0x6);
        // LD_C(0x9);
        // CALL(aFunction89b3b);
        Function89b3b(coord(0, 2, wram->wTilemap), 0x6, 0x9);
        // LD_HL(mMenuHeader_0x8a435);
        hl = &MenuHeader_0x8a435;
        // goto asm_8a3db;
    }
    else {
    // asm_8a3ce:
        // decoord(0, 2, wTilemap);
        // LD_B(0x8);
        // LD_C(0x9);
        // CALL(aFunction89b3b);
        Function89b3b(coord(0, 2, wram->wTilemap), 0x8, 0x9);
        // LD_HL(mMenuHeader_0x8a40f);
        hl = &MenuHeader_0x8a40f;
    }

// asm_8a3db:
    // CALL(aCopyMenuHeader);
    CopyMenuHeader(hl);
    // RET;
}

bool Function8a3df(void){
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // LD_HL(0xa603);
    uint8_t* hl = GBToRAMAddr(s4_a603);
    // CALL(aFunction89b45);
    bool res = Function89b45(hl);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // LD_HL(wd002);
    // IF_C goto asm_8a3f8;
    if(res) {
    // asm_8a3f8:
        // LD_DE(mUnknown_8a40b);
        // CALL(aFunction8a400);
        Function8a400(&wram->wd002, Unknown_8a40b);
        // AND_A_A;
        // RET;
        return false;
    }
    else {
        // LD_DE(mUnknown_8a408);
        // CALL(aFunction8a400);
        Function8a400(&wram->wd002, Unknown_8a408);
        // SCF;
        // RET;
        return true;
    }
}

void Function8a400(uint8_t* hl, const uint8_t* de){
    uint8_t a;
    do {
        // LD_A_de;
        // INC_DE;
        a = *(de++);
        // LD_hli_A;
        *(hl++) = a;
        // CP_A(0xff);
        // JR_NZ (mFunction8a400);
    } while(a != 0xff);
    // RET;
}

const uint8_t Unknown_8a408[] = {1, 2, 0xff};
const uint8_t Unknown_8a40b[] = {1, 2, 3, 0xff};

// MenuHeader_CardFolderLayout
const struct MenuHeader MenuHeader_0x8a40f = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 2, 10, TEXTBOX_Y - 1),
    .data = &MenuData_0x8a417,
    .defaultOption = 1,  // default option
};

const struct MenuData MenuData_0x8a417 = {
    .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
    .verticalMenu = {
        .count = 4,  // items
        .options = (const char*[]) {
            "Cards@",   //db ['"めいしりスト@"'];
            "My Card@", //db ['"じぶんの\u3000めいし@"'];
            "Trade@",   //db ['"めいしこうかん@"'];
            "Cancel@"   //db ['"やめる@"'];
        },
    },
};

// MenuHeader_CardFolderLayout2
const struct MenuHeader MenuHeader_0x8a435 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(0, 2, 10, 9),
    .data = &MenuData_0x8a43d,
    .defaultOption = 1,  // default option
};

const struct MenuData MenuData_0x8a43d = {
    .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
    .verticalMenu = {
        .count = 3,  // items
        .options = (const char*[]) {
            "Cards@",   //db ['"めいしりスト@"'];
            "My Card@", //db ['"じぶんの\u3000めいし@"'];
            "Cancel@"   //db ['"やめる@"'];
        },
    },
};

void Function8a453(void){
    // hlcoord(0, 12, wTilemap);
    // LD_B(0x4);
    // LD_C(0x12);
    // CALL(aTextbox);
    Textbox(coord(0, 12, wram->wTilemap), 0x4, 0x12);
    // hlcoord(1, 14, wTilemap);
    // LD_DE(mString_8a476);
    // LD_A_addr(wMenuSelection);
    // CP_A(0xff);
    // IF_Z goto asm_8a472;
    if(wram->wMenuSelection == 0xff) {
        PlaceStringSimple(U82C(String_8a476), coord(1, 14, wram->wTilemap));
        return;
    }
    // LD_DE(mStrings_8a483);
    // DEC_A;
    // LD_C_A;
    // CALL(aFunction8919e);

// asm_8a472:
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(Strings_8a483[wram->wMenuSelection - 1]), coord(1, 14, wram->wTilemap));
    // RET;
}

const char String_8a476[] =
            "Return to the"         //db ['"まえ<NO>がめん<NI>もどります@"'];
    t_next  "previous screen.";

const char* const Strings_8a483[] = {
            "Friends' CARDS"        //db ['"おともだち<NO>めいしは"'];
    t_next  "are stored here.",    //next ['"ここ<NI>いれておきます@"']

            "Enter your number"     //db ['"でんわばんごう<WO>いれると"'];
    t_next  "to trade CARDS.",     //next ['"めいしこうかん<GA>できます@"']

            "Trade CARDS with"      //db ['"ともだちと\u3000じぶん<NO>めいしを"'];
    t_next  "friends via IR."      //next ['"せきがいせんで\u3000こうかん\u3000します@"']
};

void Function8a4d3(void){
    // LD_A_addr(wMenuSelection);
    // CP_A(0x1);
    // IF_NZ goto asm_8a4eb;
    if(wram->wMenuSelection == 0x1) {
        // LD_A(0x5);
        // hlcoord(12, 4, wAttrmap);
        // CALL(aFunction8a5a3);
        Function8a5a3(coord(12, 4, wram->wAttrmap), 0x5);
        // LD_A(0x7);
        // hlcoord(15, 4, wAttrmap);
        // CALL(aFunction8a5a3);
        Function8a5a3(coord(15, 4, wram->wAttrmap), 0x7);
        // RET;
    }
    else {
    // asm_8a4eb:
        // LD_A(0x7);
        // hlcoord(12, 4, wAttrmap);
        // CALL(aFunction8a5a3);
        Function8a5a3(coord(12, 4, wram->wAttrmap), 0x7);
        // LD_A(0x6);
        // hlcoord(15, 4, wAttrmap);
        // CALL(aFunction8a5a3);
        Function8a5a3(coord(15, 4, wram->wAttrmap), 0x6);
        // RET;
    }
}

void Function8a4fc(void){
    // LD_A_addr(wMenuSelection);
    // CP_A(0x3);
    // JR_NZ (masm_8a529);
    if(wram->wMenuSelection != 0x3)
        return asm_8a529();
    // LD_HL(wd012);
    // LD_A_hli;
    // LD_B_A;
    // LD_A_hld;
    // ADD_A_B;
    // LD_hl_A;
    wram->wd012 = (wram->wd012 + wram->wd013);
    // LD_B_A;
    // LD_C(0x80);
    // CALL(aFunction89cdf);
    Function89cdf(wram->wd012, 0x80);
    // CALL(aFunction8a515);
    Function8a515();
    // RET;
}

void Function8a515(void){
    // LD_HL(wd012);
    // LD_A_hl;
    // CP_A(0x38);
    // IF_C goto asm_8a520;
    // CP_A(0x3c);
    // RET_C ;
    if(wram->wd012 >= 0x38 && wram->wd012 < 0x3c)
        return;

// asm_8a520:
    // LD_A_addr(wd013);
    // CPL;
    // INC_A;
    // LD_addr_A(wd013);
    wram->wd013 = -wram->wd013;
    // RET;
}

void asm_8a529(void){
    // LD_HL(wd012);
    // LD_A(0x3c);
    // LD_hli_A;
    wram->wd012 = 0x3c;
    // LD_A(0xff);
    // LD_hli_A;
    wram->wd013 = 0xff;
    // LD_HL(wVirtualOAM);
    // XOR_A_A;
    // LD_BC(8 * SPRITEOAMSTRUCT_LENGTH);
    // CALL(aByteFill);
    ByteFill(wram->wVirtualOAMSprite, 8 * SPRITEOAMSTRUCT_LENGTH, 0);
    // RET;

}

void Function8a53d(tile_t* hl){
    // PUSH_HL;
    tile_t* hl2 = hl;
    // LD_A(0x15);
    // LD_C(0x8);
    // LD_DE(0x14);
    // CALL(aFunction8a573);
    hl2 = Function8a573(hl2, 0x15, 0x8);
    hl2 = Function8a573(hl2, 0x55, 0x2);
    // LD_A(0x1d);
    // LD_C(0x9);
    // CALL(aFunction8a57c);
    hl2 = Function8a57c(hl2, 0x1d, 0x7);
    // INC_A;
    // LD_hl_A;
    *hl2 = 0x1e;
    // CALL(aFunction8a584);
    Function8a584(hl2);
    // POP_HL;
    // ADD_HL_DE;
    hl2 = hl + SCREEN_WIDTH;
    // LD_A(0x1f);
    // LD_C(0x8);
    // CALL(aFunction8a573);
    hl2 = Function8a573(hl2, 0x1f, 0x8);
    // DEC_HL;
    --hl2;
    // LD_A(0x51);
    // LD_hli_A;
    *(hl2++) = 0x51;
    // LD_A(0x26);
    // LD_C(0x1);
    // CALL(aFunction8a57c);
    // hl2 = Function8a57c(hl2, 0x26, 0x1);
    hl2 = Function8a573(hl2, 0x57, 0x2);
    // LD_A(0x52);
    // LD_C(0x3);
    // CALL(aFunction8a573);
    hl2 = Function8a573(hl2, 0x53, 0x2);
    // LD_A(0x27);
    // LD_C(0x6);
    Function8a573(hl2, 0x27, 0x6);
    return;
}

tile_t* Function8a573(tile_t* hl, uint8_t a, uint8_t c){
    do {
        // LD_hl_A;
        *hl = a;
        // CALL(aFunction8a584);
        hl = Function8a584(hl);
        // INC_A;
        // DEC_C;
        // JR_NZ (mFunction8a573);
    } while(++a, --c != 0);
    // RET;
    return hl;
}

tile_t* Function8a57c(tile_t* hl, uint8_t a, uint8_t c){
    do {
        // LD_hl_A;
        *hl = a;
        // CALL(aFunction8a584);
        hl = Function8a584(hl);
        // DEC_C;
        // JR_NZ (mFunction8a57c);
    } while(--c != 0);
    // RET;
    return hl;
}

tile_t* Function8a584(tile_t* hl){
    // PUSH_AF;
    // LD_A(0x4);
    // CALL(aFunction89215);
    Function89215(hl, 0x4);
    // INC_HL;
    // POP_AF;
    // RET;
    return ++hl;
}

void Function8a58d(tile_t* hl){
    // LD_A(0x2d);
    uint8_t a = 0x2d;
    // LD_BC(0x606);
    uint8_t b = 0x6;
    // LD_DE(0x14);

    do {
    // asm_8a595:
        // PUSH_BC;
        uint8_t c = 0x6;
        // PUSH_HL;
        tile_t* hl2 = hl;

        do {
        // asm_8a597:
            // LD_hli_A;
            *(hl2++) = a;
            // INC_A;
            a++;
            // DEC_C;
            // IF_NZ goto asm_8a597;
        } while(--c != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto asm_8a595;
    } while(--b != 0);
    // RET;

}

void Function8a5a3(tile_t* hl, uint8_t a){
    // LD_BC(0x603);
    uint8_t b = 0x6;
    // LD_DE(0x14);

    do {
    // asm_8a5a9:
        // PUSH_BC;
        uint8_t c = 0x3;
        // PUSH_HL;
        tile_t* hl2 = hl;

        do {
        // asm_8a5ab:
            // LD_hli_A;
            *(hl2++) = a;
            // DEC_C;
            // IF_NZ goto asm_8a5ab;
        } while(--c != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto asm_8a5a9;
    } while(--b != 0);
    // RET;
}

// Mobile22_LoadPalettes
void Function8a5b6(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mPalette_8a5e5);
    // LD_DE(wBGPals1 + 4 * PALETTE_SIZE);
    // LD_BC(3 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals1 + 4 * PALETTE_SIZE, Palette_8a5e5, 3 * PALETTE_SIZE);
    // LD_HL(mPalette_8a5fd);
    // LD_DE(wOBPals1);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wOBPals1, Palette_8a5fd, 1 * PALETTE_SIZE);
    // LD_HL(mPalette_8a605);
    // LD_DE(wOBPals1 + 1 * PALETTE_SIZE);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wOBPals1 + 1 * PALETTE_SIZE, Palette_8a605, 1 * PALETTE_SIZE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;

}

const uint16_t Palette_8a5e5[] = {
    rgb(31, 31, 31),
    rgb(27, 19,  0),
    rgb( 7, 11, 22),
    rgb( 0,  0,  0),

    rgb(31, 31, 31),
    rgb(16, 16, 31),
    rgb(27, 19,  0),
    rgb( 0,  0,  0),

    rgb(31, 31, 31),
    rgb(31,  0,  0),
    rgb(27, 19,  0),
    rgb( 0,  0,  0),
};

const uint16_t Palette_8a5fd[] = {
    rgb( 0,  0,  0),
    rgb( 0,  0,  0),
    rgb( 0,  0,  0),
    rgb(31, 31, 31),
};

const uint16_t Palette_8a605[] = {
    rgb( 0,  0,  0),
    rgb(14, 18, 31),
    rgb(16, 16, 31),
    rgb(31, 31, 31),
};

// Mobile22_CopyOBPPals?
void Function8a60d(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mPalette_8a624);
    // LD_DE(wOBPals1);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wOBPals1, Palette_8a624, 1 * PALETTE_SIZE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

const uint16_t Palette_8a624[] = {
    rgb(31, 31, 31),
    rgb(31, 31, 31),
    rgb(31, 31, 31),
    rgb( 0,  0,  0),
};

void Function8a62c(void){
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // CALL(aFunction891fe);
    Function891fe();
    // XOR_A_A;
    // CALL(aFunction8b94a);
    Function8b94a(0);
    // CALL(aFunction8b677);
    Function8b677();

    while(1) {
    // asm_8a639:
        // XOR_A_A;
        // LD_addr_A(wd033);
        wram->wd033[0] = 0;
        // LD_addr_A(wd032);
        wram->wd032[0] = 0;
        // LD_addr_A(wd0e3);
        wram->wd0e3 = 0;
        // CALL(aFunction8b7bd);
        uint8_t c = Function8b7bd();
        // LD_A_C;
        // AND_A_A;
        // IF_Z goto asm_8a66a;
        if(c == 0)
            break;
        // LD_addr_A(wMenuSelection);
        wram->wMenuSelection = c;
        // LD_B_A;
        uint8_t b = c;
        // LD_A_addr(wScrollingMenuCursorPosition);
        // INC_A;
        // LD_addr_A(wd034);
        wram->wd034[0] = wram->wScrollingMenuCursorPosition + 1;
        // PUSH_BC;
        // CALL(aFunction8b960);
        // LD_A_C;
        uint8_t a = Function8b960();
        // POP_BC;
        // IF_Z goto asm_8a639;
        if(a != 0) {
            // LD_C_A;
            // LD_HL(mJumptable_8a671);
            // LD_A_B;
            // LD_addr_A(wMenuSelection);
            wram->wMenuSelection = b;
            // LD_A_C;
            // DEC_A;
            // RST(aJumpTable);
            Jumptable_8a671(a - 1);
        }
        // goto asm_8a639;
    }

// asm_8a66a:
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aFunction89b28);
    Function89b28();
    // RET;
}

void Jumptable_8a671(uint8_t c){
    switch(c) {
        case 0: return Function8a679();
        case 1: return Function8a6cd();
        case 2: return Function8a8c3();
        case 3: return Function8a930();
    }
}

void Function8a679(void){
    u8_flag_s res;
    do {
        // CALL(aFunction891de);
        Function891de();
        // CALL(aClearBGPalettes);
        ClearBGPalettes();
        // CALL(aFunction893cc);
        Function893cc();
        // CALL(aOpenSRAMBank4);
        OpenSRAMBank4();
        // CALL(aFunction8931b);
        uint8_t* bc = Function8931b();
        // CALL(aFunction89844);
        Function89844(bc);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // CALL(aOpenSRAMBank4);
        OpenSRAMBank4();
        // CALL(aFunction8939a);
        Function8939a(bc);
        // CALL(aFunction89856);
        Function89856(bc);
        // hlcoord(1, 13, wTilemap);
        // CALL(aFunction899fe);
        Function899fe(coord(1, 13, wram->wTilemap), bc);
        // CALL(aFunction891ab);
        Function891ab();
        // CALL(aCloseSRAM);
        CloseSRAM();

        do {
        // asm_8a6a3:
            // CALL(aFunction89a57);
            res = Function89a57();
            // IF_C goto asm_8a6a3;
        } while(res.flag);
        // AND_A_A;
        // JR_Z (mFunction8a679);
        // LD_HL(mJumptable_8a6bc);
        // DEC_A;
        // RST(aJumpTable);
        // JR_C (mFunction8a679);
    } while(res.a == 0 || Jumptable_8a6bc(res.a - 1));
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aFunction8b677);
    Function8b677();
    // CALL(aFunction89448);
    Function89448();
    // RET;
}

bool Jumptable_8a6bc(uint8_t a){
    switch(a) {
        default:
        case 0: return Function8a6c0();
        case 1: return Function8a6c5();
    }
}

bool Function8a6c0(void){
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // AND_A_A;
    // RET;
    return false;
}

bool Function8a6c5(void){
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // CALL(aFunction89d0d);
    Function89d0d();
    // SCF;
    // RET;
    return true;
}

void Function8a6cd(void){
    // CALL(aFunction891de);
    Function891de();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893cc);
    Function893cc();
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // CALL(aFunction8931b);
    uint8_t* bc = Function8931b();
    // CALL(aFunction89844);
    Function89844(bc);
    // CALL(aFunction8a757);
    Function8a757(bc);
    // CALL(aCloseSRAM);
    CloseSRAM();

    bool done = false;
    do {
    asm_8a6e5:
        // CALL(aOpenSRAMBank4);
        OpenSRAMBank4();
        // CALL(aFunction8931b);
        bc = Function8931b();
        // CALL(aFunction89856);
        Function89856(bc);
        // CALL(aFunction89a2e);
        Function89a2e();
        // CALL(aFunction891ab);
        Function891ab();
        // XOR_A_A;
        // LD_addr_A(wd02f);
        wram->wd02f[0] = 0;
        // CALL(aCloseSRAM);
        CloseSRAM();

        u8_flag_s res;
        do {
        // asm_8a6fb:
            // CALL(aFunction89b97);
            Function89b97();
            // CALL(aFunction89c67);
            res = Function89c67();
            // IF_C goto asm_8a718;
            if(res.flag) {
            // asm_8a718:
                // CALL(aOpenSRAMBank4);
                OpenSRAMBank4();
                // CALL(aFunction8a765);
                bool carry = Function8a765();
                // CALL(aCloseSRAM);
                CloseSRAM();
                // IF_NC goto asm_8a73f;
                if(carry) {
                    // CALL(aMobile22_SetBGMapMode0);
                    Mobile22_SetBGMapMode0();
                    // CALL(aFunction89448);
                    Function89448();
                    // CALL(aFunction89a23);
                    Function89a23();
                    // hlcoord(1, 13, wTilemap);
                    // LD_DE(mString_89135);
                    // CALL(aPlaceString);
                    PlaceStringSimple(U82C(String_89135), coord(1, 13, wram->wTilemap));
                    // CALL(aWaitBGMap);
                    WaitBGMap();
                    // LD_A(0x2);
                    // CALL(aFunction89254);
                    // IF_C goto asm_8a6e5;
                    if(Function89254(0x2))
                        goto asm_8a6e5;
                }
            
            // asm_8a73f:
                // CALL(aCloseSRAM);
                CloseSRAM();
            }
            // LD_A_B;
            // AND_A_A;
            // IF_Z goto asm_8a6fb;
        } while(res.a == 0);
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // CALL(aFunction89448);
        Function89448();
        // LD_A_addr(wd011);
        // LD_HL(mJumptable_8a74f);
        // RST(aJumpTable);
        done = Jumptable_8a74f(wram->wd014);
        // IF_NC goto asm_8a6e5;
    } while(!done);
    // goto asm_8a742;

// asm_8a742:
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction89448);
    Function89448();
    // CALL(aFunction891d3);
    Function891d3();
    // CALL(aFunction8b677);
    Function8b677();
    // RET;
}

bool Jumptable_8a74f(uint8_t a){
    switch(a) {
        case 0: return Function8a78c();
        case 1: return Function8a7cb();
        case 2: return Function8a818();
        case 3: return Function8a8a1();
    }
    return false;
}

void Function8a757(uint8_t* bc){
    // CALL(aFunction8939a);
    Function8939a(bc);
    // XOR_A_A;
    // LD_addr_A(wd010);
    wram->wd013 = 0;
    // LD_addr_A(wd011);
    wram->wd014 = 0;
    // LD_addr_A(wd012);
    wram->wd012 = 0;
    // RET;
}

bool Function8a765(void){
    // CALL(aFunction8931b);
    uint8_t* bc = Function8931b();
    // PUSH_BC;
    // LD_HL(0x0);
    // ADD_HL_BC;
    // LD_DE(wd002);
    // LD_C(0x6);
    // CALL(aFunction89185);
    // POP_BC;
    // IF_NZ goto asm_8a78a;
    // PUSH_BC;
    // LD_HL(0x11);
    // ADD_HL_BC;
    // LD_DE(wd008);
    // LD_C(0x8);
    // CALL(aFunction89185);
    // POP_BC;
    // IF_NZ goto asm_8a78a;
    if(Function89185(bc + 0x0, &wram->wd002, 0x6) || Function89185(bc + PLAYER_NAME_LENGTH + 2 + 2 + 1, wram->wCardPhoneNumber, PHONE_NUMBER_LENGTH))
        return true;
    // AND_A_A;
    // RET;
    return false;

// asm_8a78a:
    // SCF;
    // RET;
}

bool Function8a78c(void){
    // CALL(aFunction891fe);
    Function891fe();
    // LD_DE(wd002);
    // LD_B(NAME_FRIEND);
    // FARCALL(aNamingScreen);
    NamingScreen(&wram->wd002, NAME_FRIEND);
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // CALL(aFunction8931b);
    uint8_t* bc = Function8931b();
    // PUSH_BC;
    // LD_HL(0x0);
    // ADD_HL_BC;
    // LD_D_H;
    // LD_E_L;
    // LD_HL(wd002);
    // CALL(aInitName);
    InitName(&wram->wd002, bc + 0x0);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // CALL(aDelayFrame);
    DelayFrame();
    // CALL(aJoyTextDelay);
    JoyTextDelay();
    // CALL(aFunction891de);
    Function891de();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893cc);
    Function893cc();
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // POP_BC;
    // CALL(aFunction89844);
    Function89844(bc);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // AND_A_A;
    // RET;
    return false;
}

bool Function8a7cb(void){
    // LD_A_addr(wMenuSelection);
    // PUSH_AF;
    uint8_t menuSelection = wram->wMenuSelection;
    // CALL(aFunction891de);
    Function891de();
    // LD_DE(wd008);
    // LD_C(0x0);
    // FARCALL(aFunction17a68f);
    // IF_C goto asm_8a7f4;
    if(!Function17a68f(wram->wCardPhoneNumber, 0x0)) {
        // LD_HL(wd008);
        // LD_A(0xff);
        // LD_BC(0x8);
        // CALL(aByteFill);
        ByteFill(wram->wCardPhoneNumber, PHONE_NUMBER_LENGTH, 0xff);
        // LD_H_D;
        // LD_L_E;
        // LD_DE(wd008);
        // LD_C(0x8);
        // CALL(aFunction89193);
        Function89193(wram->wCardPhoneNumber, wram->wStringBuffer1, PHONE_NUMBER_LENGTH);
    }

// asm_8a7f4:
    // POP_AF;
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = menuSelection;
    // CALL(aFunction891de);
    Function891de();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893cc);
    Function893cc();
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // CALL(aFunction8931b);
    uint8_t* bc = Function8931b();
    // CALL(aFunction89844);
    Function89844(bc);
    // CALL(aFunction89856);
    Function89856(bc);
    // CALL(aFunction89a2e);
    Function89a2e();
    // CALL(aFunction891ab);
    Function891ab();
    // CALL(aCloseSRAM);
    CloseSRAM();
    // AND_A_A;
    // RET;
    return false;
}

bool Function8a818(void){
    static const char string_8a868[] = 
            "The CARD was"
    t_next  "updated."; //db ['"めいし<WO>かきかえ\u3000まし<TA!>@"'];
    // CALL(aFunction89a23);
    Function89a23();
    // LD_HL(wd002);
    // CALL(aFunction89331);
    // IF_C goto asm_8a875;
    uint8_t* de;
    if(Function89331(&wram->wd002) == NULL) {
    // asm_8a875:
        // LD_DE(mString_8a88b);
        de = U82C(String_8a88b);
        // goto asm_8a87d;
    }
    // LD_HL(wd008);
    // CALL(aFunction89b45);
    // IF_NC goto asm_8a87a;
    else if(Function89b45(wram->wCardPhoneNumber)) {
    // asm_8a87a:
        // LD_DE(mString_8911c);
        de = U82C(String_8911c);
        // goto asm_8a87d;
    }
    else {
        // CALL(aOpenSRAMBank4);
        OpenSRAMBank4();
        // CALL(aFunction8a765);
        // IF_NC goto asm_8a863;
        if(Function8a765()) {
            // CALL(aFunction8931b);
            uint8_t* bc = Function8931b();
            // PUSH_BC;
            // LD_HL(0x0);
            // ADD_HL_BC;
            // LD_D_H;
            // LD_E_L;
            // LD_HL(wd002);
            // LD_C(0x6);
            // CALL(aFunction89193);
            Function89193(bc, &wram->wd002, PLAYER_NAME_LENGTH);
            // POP_BC;
            // LD_HL(0x11);
            // ADD_HL_BC;
            // LD_D_H;
            // LD_E_L;
            // LD_HL(wd008);
            // LD_C(0x8);
            // CALL(aFunction89193);
            Function89193(bc + PLAYER_NAME_LENGTH * 2 + 2 + 2 + 1, wram->wCardPhoneNumber, PHONE_NUMBER_LENGTH);
            // hlcoord(1, 13, wTilemap);
            // LD_DE(mFunction8a818_string_8a868);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(string_8a868), coord(1, 13, wram->wTilemap));
            // CALL(aWaitBGMap);
            WaitBGMap();
            // CALL(aJoyWaitAorB);
            JoyWaitAorB();
        }

    // asm_8a863:
        // CALL(aCloseSRAM);
        CloseSRAM();
        // SCF;
        // RET;
        return true;
    }

// asm_8a87d:
    // hlcoord(1, 13, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(de, coord(1, 13, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aJoyWaitAorB);
    JoyWaitAorB();
    // AND_A_A;
    // RET;
    return false;
}

const char String_8a88b[] =
            "Please enter a"    //db ['"おともだち<NO>なまえが"'];
    t_next  "name.";            //next ['"かかれて\u3000いません！@"']

bool Function8a8a1(void){
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // CALL(aFunction8a765);
    bool carry = Function8a765();
    // CALL(aCloseSRAM);
    CloseSRAM();
    // IF_NC goto asm_8a8bf;
    if(carry) {
        // CALL(aFunction89a23);
        Function89a23();
        // hlcoord(1, 13, wTilemap);
        // LD_DE(mString_89135);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_89135), coord(1, 13, wram->wTilemap));
        // LD_A(0x2);
        // CALL(aFunction89254);
        // IF_C goto asm_8a8c1;
        if(Function89254(0x2))
            return false;
    }

// asm_8a8bf:
    // SCF;
    // RET;
    return true;

// asm_8a8c1:
    // AND_A_A;
    // RET;
}

void Function8a8c3(void){
    // CALL(aFunction891de);
    Function891de();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893cc);
    Function893cc();
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // CALL(aFunction8931b);
    uint8_t* bc = Function8931b();
    // CALL(aFunction89844);
    Function89844(bc);
    // CALL(aFunction8939a);
    Function8939a(bc);
    // CALL(aFunction89856);
    Function89856(bc);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // CALL(aFunction891ab);
    Function891ab();
    // hlcoord(1, 13, wTilemap);
    // LD_DE(mString_8a919);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_8a919), coord(1, 13, wram->wTilemap));
    // LD_A(0x2);
    // CALL(aFunction89254);
    // IF_C goto asm_8a90f;
    if(!Function89254(0x2)) {
        // CALL(aOpenSRAMBank4);
        OpenSRAMBank4();
        // CALL(aFunction892b4);
        Function892b4();
        // CALL(aCloseSRAM);
        CloseSRAM();
        // CALL(aFunction89a23);
        Function89a23();
        // CALL(aMobile22_SetBGMapMode0);
        Mobile22_SetBGMapMode0();
        // hlcoord(1, 13, wTilemap);
        // LD_DE(mString_8a926);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_8a926), coord(1, 13, wram->wTilemap));
        // CALL(aWaitBGMap);
        WaitBGMap();
        // CALL(aJoyWaitAorB);
        JoyWaitAorB();
    }

// asm_8a90f:
    // CALL(aFunction89448);
    Function89448();
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aFunction8b677);
    Function8b677();
    // RET;
}

const char String_8a919[] = 
            "Delete this CARD?"; //db ['"このデータ<WO>けしますか？@"'];
const char String_8a926[] = 
            "The CARD has"  //db ['"データ<WO>けしまし<TA!>@"'];
    t_next  "been deleted."; 

// Mobile22_SwapEntries
void Function8a930(void){
    // LD_A_addr(wMenuSelection);
    // PUSH_AF;
    uint8_t menuSelection = wram->wMenuSelection;
    // XOR_A_A;
    // LD_addr_A(wd032);
    wram->wd032[0] = 0;
    // LD_A(0x1);
    // LD_addr_A(wd033);
    wram->wd033[0] = 0x1;
    // LD_A_addr(wd034);
    // LD_addr_A(wd0e3);
    wram->wd0e3 = wram->wd034[0];

    uint8_t c;
    do {
    // asm_8a943:
        // CALL(aFunction8b7bd);
        c = Function8b7bd();
        // LD_A_addr(wMenuJoypad);
        // AND_A(0x1);
        // IF_NZ goto asm_8a953;
        if((wram->wMenuJoypad & A_BUTTON) != 0) {
        // asm_8a953:
            // CALL(aOpenSRAMBank4);
            OpenSRAMBank4();
            // POP_AF;
            // CP_A_C;
            // IF_Z goto asm_8a995;
            if(c != menuSelection) {
                // PUSH_BC;
                // LD_addr_A(wMenuSelection);
                wram->wMenuSelection = menuSelection;
                // CALL(aFunction8931b);
                uint8_t* bc = Function8931b();
                // PUSH_BC;
                // LD_H_B;
                // LD_L_C;
                // LD_DE(wd002);
                // LD_BC(0x25);
                // CALL(aCopyBytes);
                CopyBytes(&wram->wd002, bc, 0x25);
                // POP_DE;
                // POP_BC;
                // LD_A_C;
                // LD_addr_A(wMenuSelection);
                wram->wMenuSelection = c;
                // CALL(aFunction8931b);
                uint8_t* bc2 = Function8931b();
                // PUSH_BC;
                // LD_H_B;
                // LD_L_C;
                // LD_BC(0x25);
                // CALL(aCopyBytes);
                CopyBytes(bc, bc2, 0x25);
                // POP_DE;
                // LD_HL(wd002);
                // LD_BC(0x25);
                // CALL(aCopyBytes);
                CopyBytes(bc2, &wram->wd002, 0x25);
                // LD_DE(SFX_SWITCH_POKEMON);
                // CALL(aWaitPlaySFX);
                WaitPlaySFX(SFX_SWITCH_POKEMON);
                // LD_DE(SFX_SWITCH_POKEMON);
                // CALL(aWaitPlaySFX);
                WaitPlaySFX(SFX_SWITCH_POKEMON);
            }
        
        // asm_8a995:
            // CALL(aCloseSRAM);
            CloseSRAM();
            // RET;        
            return;
        }
        // LD_A_C;
        // AND_A_A;
        // IF_NZ goto asm_8a943;
    } while(c != 0);
    // POP_AF;
    // RET;
}

void Function8a999(void){
    // LD_HL(mMenuHeader_0x8a9c9);
    // CALL(aLoadMenuHeader);
    LoadMenuHeader(&MenuHeader_0x8a9c9);
    // LD_C(0x1);
    uint8_t c = 0x1;
    u8_pair_flag_s res;

    while((res = Function8a9ce(c), !res.flag)) {
    // asm_8a9a1:
        // CALL(aFunction8a9ce);
        // IF_C goto asm_8a9bb;
        // PUSH_BC;
        // PUSH_DE;
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader();
        // POP_DE;
        // DEC_E;
        // LD_A_E;
        // LD_HL(mJumptable_8a9c5);
        Jumptable_8a9c5(res.b - 1);
        // RST(aJumpTable);
        // CALL(aFunction891fe);
        Function891fe();
        // CALL(aFunction89b28);
        Function89b28();
        // POP_BC;
        c = res.a;
        // goto asm_8a9a1;
    }

// asm_8a9bb:
    // CALL(aMobile_EnableSpriteUpdates);
    Mobile_EnableSpriteUpdates();
    // CALL(aCloseWindow);
    CloseWindow();
    // CALL(aMobile_DisableSpriteUpdates);
    Mobile_DisableSpriteUpdates();
    // RET;
}

void Jumptable_8a9c5(uint8_t a){
    switch(a) {
        case 0: return Function8aa0a();
        case 1: return Function8ab3b();
    }
}

const struct MenuHeader MenuHeader_0x8a9c9 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(11, 4, 18, TEXTBOX_Y - 1),
};

u8_pair_flag_s Function8a9ce(uint8_t c){
    // PUSH_BC;
    // decoord(11, 4, wTilemap);
    // LD_B(0x6);
    // LD_C(0x6);
    // CALL(aFunction89b3b);
    Function89b3b(coord(11, 4, wram->wTilemap), 0x6, 0x6);
    // POP_BC;
    // LD_A_C;
    // LD_HL(mMenuHeader_0x8a9f2);
    // CALL(aFunction89d5e);
    Function89d5e(&MenuHeader_0x8a9f2, c);
    // LD_HL(mFunction8aa09);
    // CALL(aFunction89d85);
    u8_flag_s res = Function89d85(Function8aa09);
    // IF_C goto asm_8a9ed;
    if(res.flag) {
    // asm_8a9ed:
        // LD_C_A;
        // LD_E(0x0);
        // SCF;
        // RET;
        return u8_pair_flag(res.a, 0x0, true);
    }
    else {
        // LD_C_A;
        // LD_E_A;
        // AND_A_A;
        // RET;
        return u8_pair_flag(res.a, res.a, false);
    }
}

const struct MenuHeader MenuHeader_0x8a9f2 = {
    .flags = MENU_BACKUP_TILES,  // flags
    .coord = menu_coords(11, 4, 18, TEXTBOX_Y - 1),
    .data = &MenuData_0x8a9fa,
    .defaultOption = 1,  // default option
};

const struct MenuData MenuData_0x8a9fa = {
    .flags = STATICMENU_CURSOR | STATICMENU_WRAP,  // flags
    .verticalMenu = {
        .count = 3,  // items
        .options = (const char*[]) {
            "EDIT", //db ['"へんしゅう@"'];
            "VIEW", //db ['"みる@"'];
            "QUIT", //db ['"やめる@"'];
        },
    },
};

void Function8aa09(void){
    // RET;
}

void Function8aa0a(void){
    // LD_A(0x1);
    // LD_addr_A(wd02f);
    wram->wd02f[0] = 0x1;
    // LD_addr_A(wd011);
    wram->wd014 = 0x1;
    // XOR_A_A;
    // LD_addr_A(wd010);
    wram->wd013 = 0;
    // LD_addr_A(wd012);
    wram->wd012 = 0;
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // LD_HL(0xa603);
    // LD_DE(wd008);
    // CALL(aFunction89381);
    Function89381(wram->wCardPhoneNumber, GBToRAMAddr(s4_a603));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893cc);
    Function893cc();
    // CALL(aFunction89807);
    Function89807();
    // CALL(aFunction89492);
    // CALL(aFunction894ca);
    Function894ca(Function89492());

asm_8aa3a:
    // CALL(aFunction8987f);
    Function8987f();
    // CALL(aFunction89a2e);
    Function89a2e();
    // CALL(aFunction891ab);
    Function891ab();

asm_8aa43:
    // CALL(aFunction89b97);
    Function89b97();
    // CALL(aFunction89c67);
    u8_flag_s res = Function89c67();
    // IF_C goto asm_8aa61;
    if(res.flag) {
    // asm_8aa61:
        // CALL(aFunction89448);
        Function89448();
        // CALL(aFunction8ab11);
        // IF_NC goto asm_8aa3a;
        if(Function8ab11())
            goto asm_8aa3a;
        goto asm_8aa69;
    }
    // LD_A_B;
    // AND_A_A;
    // IF_Z goto asm_8aa43;
    if(res.a == 0)
        goto asm_8aa43;
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // CALL(aFunction89448);
    Function89448();
    // LD_A_addr(wd011);
    // DEC_A;
    // LD_HL(mJumptable_8aa6d);
    // RST(aJumpTable);
    // IF_NC goto asm_8aa3a;
    if(!Jumptable_8aa6d(wram->wd014 - 1))
        goto asm_8aa3a;
    // goto asm_8aa69;

asm_8aa69:
    // CALL(aFunction89448);
    Function89448();
    // RET;
}

bool Jumptable_8aa6d(uint8_t a){
    switch(a) {
        default:
        case 0: return Function8aa73();
        case 1: return Function8aab6();
        case 2: return Function8ab11();
    }
}

bool Function8aa73(void){
    // LD_A_addr(wMenuSelection);
    // LD_E_A;
    uint8_t e = wram->wMenuSelection;
    // PUSH_DE;
    // CALL(aFunction891de);
    Function891de();
    // LD_DE(wd008);
    // LD_C(0x0);
    // FARCALL(aFunction17a68f);
    // IF_C goto asm_8aa9d;
    if(!Function17a68f(wram->wCardPhoneNumber, 0x0)) {
        // LD_HL(wd008);
        // LD_A(0xff);
        // LD_BC(0x8);
        // CALL(aByteFill);
        ByteFill(wram->wCardPhoneNumber, PHONE_NUMBER_LENGTH, 0xff);
        // LD_H_D;
        // LD_L_E;
        // LD_DE(wd008);
        // LD_C(0x8);
        // CALL(aFunction89193);
        Function89193(wram->wCardPhoneNumber, wram->wStringBuffer1, PHONE_NUMBER_LENGTH);
    }

// asm_8aa9d:
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893cc);
    Function893cc();
    // CALL(aFunction89807);
    Function89807();
    // CALL(aFunction89492);
    // CALL(aFunction894ca);
    Function894ca(Function89492());
    // POP_DE;
    // LD_A_E;
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = e;
    // AND_A_A;
    // RET;
    return false;
}

bool Function8aab6(void){
    // CALL(aFunction89a23);
    Function89a23();
    // LD_HL(wd008);
    uint8_t* hl = wram->wCardPhoneNumber;
    // CALL(aFunction89b45);
    // JR_NC (mFunction8ab00);
    if(!Function89b45(hl))
        return Function8ab00();
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // LD_DE(wd008);
    // LD_HL(0xa603);
    // LD_C(0x8);
    // CALL(aFunction89185);
    // IF_Z goto asm_8aaeb;
    if(!Function89185(GBToRAMAddr(s4_a603), wram->wCardPhoneNumber, 0x8)) {
        // LD_HL(wd008);
        // LD_DE(0xa603);
        // LD_C(0x8);
        // CALL(aFunction89193);
        Function89193(GBToRAMAddr(s4_a603), wram->wCardPhoneNumber, 0x8);
        // hlcoord(1, 13, wTilemap);
        // LD_DE(mString_8aaf0);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_8aaf0), coord(1, 13, wram->wTilemap));
        // CALL(aWaitBGMap);
        WaitBGMap();
        // CALL(aJoyWaitAorB);
        JoyWaitAorB();
    }

// asm_8aaeb:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // SCF;
    // RET;
    return true;
}

const char String_8aaf0[] =
            "Your CARD was" //db ['"あたらしい\u3000めいし<PKMN>できまし<LF>@"'];
    t_next  "updated.";

bool Function8ab00(void){
    // LD_DE(mString_8911c);
    // hlcoord(1, 13, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_8911c), coord(1, 13, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap();
    // CALL(aMobile22_PromptButton);
    Mobile22_PromptButton();
    // AND_A_A;
    // RET;
    return false;
}

bool Function8ab11(void){
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // LD_HL(0xa603);
    // LD_DE(wd008);
    // LD_C(0x8);
    // CALL(aFunction89185);
    bool eq = Function89185(GBToRAMAddr(s4_a603), wram->wCardPhoneNumber, PHONE_NUMBER_LENGTH);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // IF_Z goto asm_8ab37;
    if(eq)
        return true;
    // CALL(aFunction89a23);
    Function89a23();
    // hlcoord(1, 13, wTilemap);
    // LD_DE(mString_89135);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_89135), coord(1, 13, wram->wTilemap));
    // LD_A(0x2);
    // CALL(aFunction89254);
    // IF_C goto asm_8ab39;
    if(!Function89254(0x2)) {
    // asm_8ab37:
        // SCF;
        // RET;
        return true;
    }

// asm_8ab39:
    // AND_A_A;
    // RET;
    return false;
}

static bool Function8ab3b_JoypadLoop(void){
    while(1) {
        // CALL(aJoyTextDelay_ForcehJoyDown);
        uint8_t c = JoyTextDelay_ForcehJoyDown();
        // BIT_C(A_BUTTON_F);
        // IF_NZ goto a_b_button;
        // BIT_C(B_BUTTON_F);
        // IF_NZ goto a_b_button;
        if(bit_test(c, A_BUTTON_F) || bit_test(c, B_BUTTON_F)) {
        // a_b_button:
            // CALL(aPlayClickSFX);
            PlayClickSFX();
            // AND_A_A;
            // RET;
            return false;
        }
        // BIT_C(START_F);
        // IF_Z goto JoypadLoop;
        else if(bit_test(c, START_F)) {
            // CALL(aPlayClickSFX);
            PlayClickSFX();
            // CALL(aFunction89d0d);
            Function89d0d();
            // SCF;
            // RET;
            return true;
        }
    }
}

void Function8ab3b(void){
    do {
    // pressed_start:
        // CALL(aFunction891fe);
        Function891fe();
        // CALL(aClearBGPalettes);
        ClearBGPalettes();
        // CALL(aFunction893cc);
        Function893cc();
        // CALL(aFunction89807);
        Function89807();
        // CALL(aFunction89492);
        // CALL(aFunction894ca);
        Function894ca(Function89492());
        // CALL(aOpenSRAMBank4);
        OpenSRAMBank4();
        // LD_HL(0xa603);
        // LD_DE(wd008);
        // CALL(aFunction89381);
        Function89381(wram->wd008, GBToRAMAddr(s4_a603));
        // CALL(aCloseSRAM);
        CloseSRAM();
        // CALL(aFunction8987f);
        Function8987f();
        // CALL(aOpenSRAMBank4);
        OpenSRAMBank4();
        // hlcoord(1, 13, wTilemap);
        // LD_BC(0xa007);
        // CALL(aFunction89a0c);
        Function89a0c(coord(1, 13, wram->wTilemap), GBToRAMAddr(s4_a007));
        // CALL(aCloseSRAM);
        CloseSRAM();
        // CALL(aFunction891ab);
        Function891ab();
        // CALL(aFunction8ab3b_JoypadLoop);
        // IF_C goto pressed_start;
    } while(Function8ab3b_JoypadLoop());
    // RET;
}

void Function8ab93(void){
    if(!LANTryConnection())
        return;
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // FARCALL(aDoNameCardSwap);
    DoNameCardSwap();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aFunction89b28);
    Function89b28();
    // RET;
    LANCloseConnection();
}

uint8_t Function8aba9(void){
    // LD_A(0x2);
    // CALL(aFunction8b94a);
    Function8b94a(0x2);
    // LD_A(0x1);
    // LD_addr_A(wd032);
    wram->wd032[0] = 0x1;

    do {
    // asm_8abb3:
        // CALL(aFunction891fe);
        Function891fe();
        // CALL(aFunction8b677);
        Function8b677();

        while(1) {
        // asm_8abb9:
            // CALL(aFunction8b7bd);
            uint8_t c = Function8b7bd();
            // IF_Z goto asm_8abdf;
            if(c == 0) {
            // asm_8abdf:
                // XOR_A_A;
                // LD_C_A;
                // RET;
                return 0;
            }
            // LD_A_C;
            // LD_addr_A(wMenuSelection);
            wram->wMenuSelection = c;
            // CALL(aOpenSRAMBank4);
            OpenSRAMBank4();
            // CALL(aFunction8931b);
            uint8_t* bc = Function8931b();
            // LD_HL(0x0011);
            // ADD_HL_BC;
            // CALL(aFunction89b45);
            bool carry = Function89b45(bc + PLAYER_NAME_LENGTH * 2 + 2 + 2 + 1);
            // CALL(aCloseSRAM);
            CloseSRAM();
            // IF_C goto asm_8abe2;
            if(carry)
                break;
            // LD_DE(SFX_WRONG);
            // CALL(aWaitPlaySFX);
            WaitPlaySFX(SFX_WRONG);
            // CALL(aCloseSRAM);
            // goto asm_8abb9;
        }

    // asm_8abe2:
        // CALL(aPlayClickSFX);
        PlayClickSFX();

    asm_8abe5:
        // CALL(aFunction891de);
        Function891de();
        // CALL(aClearBGPalettes);
        ClearBGPalettes();
        // CALL(aFunction893cc);
        Function893cc();
        // CALL(aOpenSRAMBank4);
        OpenSRAMBank4();
        // CALL(aFunction8931b);
        uint8_t* bc = Function8931b();
        // CALL(aFunction89844);
        Function89844(bc);
        // CALL(aCloseSRAM);
        // CALL(aOpenSRAMBank4);
        // CALL(aFunction8939a);
        Function8939a(bc);
        // CALL(aFunction89856);
        Function89856(bc);
        // hlcoord(1, 13, wTilemap);
        // CALL(aFunction899fe);
        Function899fe(coord(1, 13, wram->wTilemap), bc);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // CALL(aFunction891ab);
        Function891ab();

        u8_flag_s res;
        do {
        // asm_8ac0f:
            // CALL(aFunction89a57);
            res = Function89a57();
            // IF_C goto asm_8ac0f;
            if(res.flag)
                continue;
            // AND_A_A;
            // IF_Z goto asm_8abe5;
            if(res.a == 0)
                goto asm_8abe5;
            // CP_A(0x2);
            // IF_Z goto asm_8ac0f;
        } while(res.a == 0x2);
        // hlcoord(0, 12, wTilemap);
        // LD_B(0x4);
        // LD_C(0x12);
        // CALL(aTextbox);
        Textbox(coord(0, 12, wram->wTilemap), 0x4, 0x12);
        // hlcoord(1, 14, wTilemap);
        // LD_DE(mString_8ac3b);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(String_8ac3b), coord(1, 14, wram->wTilemap));
        // LD_A(0x1);
        // CALL(aFunction8925e);
        // JP_C (mFunction8aba9_asm_8abb3);
    } while(Function8925e(0x1));
    // LD_A_addr(wMenuSelection);
    // LD_C_A;
    // RET;
    return wram->wMenuSelection;
}

const char String_8ac3b[] =
            "Call this" //db ['"こ<NO>ともだち<NI>でんわを"'];
    t_next  "friend?"; //next ['"かけますか？@"']

void Function8ac4e(uint8_t* de){
    // XOR_A_A;
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = 0;
    // PUSH_DE;
    // CALL(aFunction891de);
    Function891de();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893cc);
    Function893cc();
    // POP_BC;
    // CALL(aFunction89844);
    Function89844(de);
    // CALL(aFunction8939a);
    Function8939a(de);
    // CALL(aFunction89856);
    Function89856(de);
    // hlcoord(1, 13, wTilemap);
    // CALL(aFunction899fe);
    Function899fe(coord(1, 13, wram->wTilemap), de);
    // CALL(aFunction891ab);
    Function891ab();
    // RET;
}

u8_flag_s Function8ac70(uint8_t* de){
    // PUSH_DE;
    // LD_A(0x3);
    // CALL(aFunction8b94a);
    Function8b94a(0x3);

    Function8ac76();
    return Function8ac7c(de);
}

void Function8ac76(void){
    // CALL(aFunction891fe);
    Function891fe();
    // CALL(aFunction8b677);
    Function8b677();

    // return Function8ac7c(de);
}

u8_flag_s Function8ac7c(uint8_t* hl){
    uint8_t c;
start:
    // CALL(aFunction8b7bd);
    c = Function8b7bd();
    // IF_Z goto asm_8acf0;
    if(c == 0) {
    // asm_8acf0:
        // LD_HL(mMobileCardFolderFinishRegisteringCardsText);
        // CALL(aPrintText);
        PrintText(MobileCardFolderFinishRegisteringCardsText);
        // LD_A(0x2);
        // CALL(aFunction89259);
        // JP_C (mFunction8ac7c);
        if(Function89259(0x2))
            goto start;
        // CALL(aLoadStandardFont);
        LoadStandardFont();
        // POP_DE;
        // LD_C(0x0);
        // SCF;
        // RET;
        return u8_flag(0x0, true);
    }
    // LD_A_C;
    // LD_addr_A(wd02f);
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = wram->wd02f[0] = c;
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // CALL(aFunction8931b);
    uint8_t* bc = Function8931b();
    // CALL(aFunction8932d);
    uint8_t* res = Function8932d(bc);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // IF_NC goto asm_8acb0;
    if(res == NULL) {
        // CALL(aOpenSRAMBank4);
        OpenSRAMBank4();
        // LD_HL(0x0011);
        // ADD_HL_BC;
        // CALL(aFunction89b45);
        bool carry = Function89b45(bc + PLAYER_NAME_LENGTH * 2 + 2 + 2 + 1);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // IF_NC goto asm_8accc;
        if(carry) {
            // CALL(aOpenSRAMBank4);
            OpenSRAMBank4();
            // CALL(aFunction892b7);
            Function892b7(bc);
            // CALL(aCloseSRAM);
            CloseSRAM();
            // goto asm_8accc;
        }
    }
    else {
    // asm_8acb0:
        // CALL(aFunction8ad0b);
        u8_flag_s res = Function8ad0b();
        // JR_C (mFunction8ac76);
        if(res.flag) {
            Function8ac76();
            goto start;
        }
        // AND_A_A;
        // IF_NZ goto asm_8accc;
        if(res.a == 0) {
            // CALL(aOpenSRAMBank4);
            OpenSRAMBank4();
            // LD_H_B;
            // LD_L_C;
            // LD_D(0x0);
            // LD_E(0x6);
            // ADD_HL_DE;
            // LD_D_H;
            // LD_E_L;
            // POP_HL;
            // LD_C(0x1f);
            // CALL(aFunction89193);
            Function89193(bc + PLAYER_NAME_LENGTH, hl, 0x1f);
            goto asm_8ace4;
        }
    }

// asm_8accc:
    // POP_HL;
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // LD_D_B;
    // LD_E_C;
    // LD_C(0x6);
    // CALL(aFunction89193);
    Function89193(bc, hl, PLAYER_NAME_LENGTH);
    // LD_A(0x6);
    // ADD_A_E;
    // LD_E_A;
    // LD_A(0x0);
    // ADC_A_D;
    // LD_D_A;
    // LD_C(0x1f);
    // CALL(aFunction89193);
    Function89193(bc + PLAYER_NAME_LENGTH, hl, PLAYER_NAME_LENGTH);

asm_8ace4:
    // CALL(aCloseSRAM);
    CloseSRAM();
    // CALL(aLoadStandardFont);
    LoadStandardFont();
    // LD_A_addr(wd02f);
    // LD_C_A;
    // AND_A_A;
    // RET;
    return u8_flag(wram->wd02f[0], false);
}

const txt_cmd_s MobileCardFolderFinishRegisteringCardsText[] = {
    text_far(v_MobileCardFolderFinishRegisteringCardsText)
    text_end
};

u8_flag_s Function8ad0b(void){

asm_8ad0b:
    // LD_A_addr(wMenuSelection);
    // LD_addr_A(wd02f);
    wram->wd02f[0] = wram->wMenuSelection;
    // CALL(aFunction891de);
    Function891de();
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aFunction893cc);
    Function893cc();
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // CALL(aFunction8931b);
    // PUSH_BC;
    uint8_t* bc = Function8931b();
    // CALL(aFunction89844);
    Function89844(bc);
    // CALL(aFunction8939a);
    Function8939a(bc);
    // CALL(aFunction89856);
    Function89856(bc);
    // hlcoord(1, 13, wTilemap);
    // CALL(aFunction899fe);
    Function899fe(coord(1, 13, wram->wTilemap), bc);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // CALL(aFunction891ab);
    Function891ab();
    // POP_BC;

    u8_flag_s res;
    do {
        do {
        // asm_8ad37:
            // PUSH_BC;
            // CALL(aFunction89a57);
            res = Function89a57();
            // POP_BC;
            // IF_C goto asm_8ad37;
        } while(res.flag);
        // AND_A_A;
        // IF_Z goto asm_8ad0b;
        if(res.a == 0)
            goto asm_8ad0b;
        // CP_A(0x2);
        // IF_Z goto asm_8ad37;
    } while(res.a == 0x2);
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // PUSH_BC;
    // hlcoord(0, 12, wTilemap);
    // LD_B(0x4);
    // LD_C(0x12);
    // CALL(aTextbox);
    Textbox(coord(0, 12, wram->wTilemap), 0x4, 0x12);
    // LD_DE(mString_8ad89);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_8ad89), coord(1, 14, wram->wTilemap));
    // LD_A(0x2);
    // CALL(aFunction8925e);
    // IF_C goto asm_8ad87;
    if(Function8925e(0x2))
        return u8_flag(wram->wMenuCursorY, true);
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // hlcoord(0, 12, wTilemap);
    // LD_B(0x4);
    // LD_C(0x12);
    // CALL(aTextbox);
    Textbox(coord(0, 12, wram->wTilemap), 0x4, 0x12);
    // LD_DE(mString_8ad9c);
    // hlcoord(1, 14, wTilemap);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_8ad9c), coord(1, 14, wram->wTilemap));
    // LD_A(0x1);
    // CALL(aFunction8925e);
    // IF_C goto asm_8ad84;
    if(Function8925e(0x1))
        return u8_flag(0x1, false);
    // LD_A(0x0);
    // goto asm_8ad86;

// asm_8ad84:
    // LD_A(0x1);

// asm_8ad86:
    // AND_A_A;

// asm_8ad87:
    // POP_BC;
    // RET;
    return u8_flag(0x0, false);
}

const char String_8ad89[] =
            "Overwrite"     //db ['"こ<NO>めいし<WO>けして"'];
    t_next  "this data?@";  //next ['"いれかえますか？@"']

const char String_8ad9c[] = 
            "Keep the"          //db ['"おともだち<NO>なまえを"'];
    t_next  "friend's name?@";  //next ['"のこして\u3000おきますか？@"']

bool Function8adb3(void){
    // CALL(aFunction891de);
    Function891de();
    // CALL(aFunction8a262);
    bool carry = Function8a262();
    // PUSH_AF;
    // CALL(aFunction891de);
    Function891de();
    // POP_AF;
    // RET;
    return carry;
}

void Function8adbf(void){
//  //  unreferenced
    CALL(aOpenSRAMBank4);
    LD_HL(0xa603);
    CALL(aFunction89b45);
    CALL(aCloseSRAM);
    RET;

}

bool Function8adcc(void){
    // CALL(aOpenSRAMBank4);
    OpenSRAMBank4();
    // CALL(aFunction8b3b0);
    u8_flag_s res = Function8b3b0();
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET_NC ;
    if(!res.flag)
        return false;
    // CP_A(0x2);
    // RET_Z ;
    if(res.a == 0x2)
        return false;
    // SCF;
    // RET;
    return true;
}
