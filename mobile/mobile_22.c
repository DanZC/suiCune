#include "../constants.h"
#include "mobile_22.h"
#include "mobile_22_2.h"
#include "mobile_12.h"
#include "mobile_menu.h"
#include "../home/copy.h"
#include "../home/sram.h"
#include "../home/tilemap.h"
#include "../home/joypad.h"
#include "../home/menu.h"
#include "../home/lcd.h"
#include "../home/clear_sprites.h"
#include "../home/gfx.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/crystal_layouts.h"
#include "../data/text/common.h"

const char String_89116[] = "-----@"; //db ['"-----@"'];

const char String_8911c[] = 
            "Please enter a"  //db ['"でんわばんごうが\u3000ただしく"'];  // Phone number is not
    t_next  "phone number.@"; //next ['"はいって\u3000いません！@"']  // entered correctly!

const char String_89135[] = 
            "Discard changes to" //db ['"データが\u3000かわって\u3000いますが"'];  // The data has changed.
    t_next  "this CARD?@"; //next ['"かきかえないで\u3000やめますか？@"']  // Quit anyway?

const char String_89153[] = "No message.@"; //db ['"メッセージは\u3000ありません@"'];  // No message

void OpenSRAMBank4(void){
    // PUSH_AF;
    // LD_A(0x4);
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(0x4);
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
    ByteFill_Conv2(&wram->wd002, 0x32, 0);
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
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);

// done:
    // POP_HL;
    // POP_DE;
    // RET;
    return true;
}

void Function89193(void){
//  copy(hl, de, 4)
//  Copies c bytes from hl to de.
//  Preserves hl and de.
    PUSH_DE;
    PUSH_HL;

loop:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto loop;
    POP_HL;
    POP_DE;
    RET;

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
    ReloadMapPart_Conv();
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // RET;
}

void Function891b8(void){
    CALL(aMobile22_SetBGMapMode0);
    hlcoord(0, 0, wTilemap);
    LD_A(0x7f);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    CALL(aDelayFrame);
    RET;

}

void Function891ca(void){
    PUSH_BC;
    CALL(aFunction891b8);
    CALL(aWaitBGMap);
    POP_BC;
    RET;

}

void Function891d3(void){
    PUSH_BC;
    CALL(aFunction891ca);
    LD_C(0x10);
    CALL(aDelayFrames);
    POP_BC;
    RET;

}

// Mobile22_ClearScreen?
void Function891de(void){
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // CALL(aClearPalettes);
    ClearPalettes_Conv();
    // hlcoord(0, 0, wAttrmap);
    // LD_A(0x7);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wAttrmap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7);
    // hlcoord(0, 0, wTilemap);
    // LD_A(0x7f);
    // LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_WIDTH * SCREEN_HEIGHT, 0x7f);
    // CALL(aFunction891ab);
    Function891ab();
    // RET;

}

void Function891fe(void){
    PUSH_BC;
    CALL(aFunction891de);
    LD_C(0x10);
    CALL(aDelayFrames);
    POP_BC;
    RET;

}

void Mobile_EnableSpriteUpdates(void){
    LD_A(1);
    LD_addr_A(wSpriteUpdatesEnabled);
    RET;

}

void Mobile_DisableSpriteUpdates(void){
    LD_A(0);
    LD_addr_A(wSpriteUpdatesEnabled);
    RET;

}

void Function89215(tile_t* hl, uint8_t a){
    // PUSH_HL;
    // PUSH_BC;
    // LD_BC(wAttrmap - wTilemap);
    // ADD_HL_BC;
    // LD_hl_A;
    hl[wAttrmap - wTilemap] = a;
    // POP_BC;
    // POP_HL;
    // RET;
}

void Function8921f(void){
    PUSH_DE;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    INC_HL;
    LD_A(0x7f);

loop:
    PUSH_BC;
    PUSH_HL;

asm_89229:
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_89229;
    POP_HL;
    ADD_HL_DE;
    POP_BC;
    DEC_B;
    IF_NZ goto loop;
    POP_DE;
    RET;

}

void Mobile22_PromptButton(void){
    // CALL(aJoyWaitAorB);
    JoyWaitAorB_Conv();
    // CALL(aPlayClickSFX);
    PlayClickSFX_Conv();
    // RET;
}

void Mobile22_SetBGMapMode0(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // RET;
}

void Mobile22_SetBGMapMode1(void){
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // RET;
}

void Function89245(void){
    FARCALL(aTryLoadSaveFile);
    RET_C ;
    FARCALL(av_LoadData);
    AND_A_A;
    RET;

}

void Function89254(void){
    LD_BC(0xd07);
    JR(mFunction89261);

}

void Function89259(void){
    LD_BC(0x0e07);
    JR(mFunction89261);

}

void Function8925e(void){
    LD_BC(0x0e0c);

    return Function89261();
}

void Function89261(void){
    PUSH_AF;
    PUSH_BC;
    LD_HL(mMenuHeader_0x892a3);
    CALL(aCopyMenuHeader);
    POP_BC;
    LD_HL(wMenuBorderTopCoord);
    LD_A_C;
    LD_hli_A;
    LD_A_B;
    LD_hli_A;
    LD_A_C;
    ADD_A(0x4);
    LD_hli_A;
    LD_A_B;
    ADD_A(0x5);
    LD_hl_A;
    POP_AF;
    LD_addr_A(wMenuCursorPosition);
    CALL(aPushWindow);
    CALL(aMobile22_SetBGMapMode0);
    CALL(aMobile_EnableSpriteUpdates);
    CALL(aVerticalMenu);
    PUSH_AF;
    LD_C(0xa);
    CALL(aDelayFrames);
    CALL(aCloseWindow);
    CALL(aMobile_DisableSpriteUpdates);
    POP_AF;
    IF_C goto done;
    LD_A_addr(wMenuCursorY);
    CP_A(0x2);
    IF_Z goto done;
    AND_A_A;
    RET;


done:
    SCF;
    RET;

}

void MenuHeader_0x892a3(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['10', '5', '15', '9'];
    //dw ['MenuData_0x892ab'];
    //db ['1'];  // default option

    return MenuData_0x892ab();
}

void MenuData_0x892ab(void){
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING'];  // flags
    //db ['2'];  // items
    //db ['"はい@"'];
    //db ['"いいえ@"'];

    return Function892b4();
}

void Function892b4(void){
    CALL(aFunction8931b);

    return Function892b7();
}

void Function892b7(void){
    LD_D_B;
    LD_E_C;
    LD_HL(0);
    ADD_HL_BC;
    LD_A(0x50);
    LD_BC(6);
    CALL(aByteFill);
    LD_B_D;
    LD_C_E;
    LD_HL(6);
    ADD_HL_BC;
    LD_A(0x50);
    LD_BC(6);
    CALL(aByteFill);
    LD_B_D;
    LD_C_E;
    LD_HL(12);
    ADD_HL_BC;
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    LD_HL(14);
    ADD_HL_BC;
    LD_hli_A;
    LD_hl_A;
    LD_HL(16);
    ADD_HL_BC;
    LD_hl_A;
    LD_HL(17);
    ADD_HL_BC;
    LD_A(-1);
    LD_BC(8);
    CALL(aByteFill);
    LD_B_D;
    LD_C_E;
    LD_E(6);
    LD_HL(25);
    ADD_HL_BC;

loop:
    LD_A(-1);
    LD_hli_A;
    LD_A(-1);
    LD_hli_A;
    DEC_E;
    IF_NZ goto loop;
    RET;

}

void Function89305(void){
    XOR_A_A;
    LD_addr_A(wMenuSelection);
    LD_C(40);

loop:
    LD_A_addr(wMenuSelection);
    INC_A;
    LD_addr_A(wMenuSelection);
    PUSH_BC;
    CALL(aFunction892b4);
    POP_BC;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void Function8931b(void){
    PUSH_HL;
    LD_HL(s4_a03b);
    LD_A_addr(wMenuSelection);
    DEC_A;
    LD_BC(37);
    CALL(aAddNTimes);
    LD_B_H;
    LD_C_L;
    POP_HL;
    RET;

}

void Function8932d(void){
    LD_HL(0);
    ADD_HL_BC;

    return Function89331();
}

void Function89331(void){
//  Scans up to 5 characters starting at hl, looking for a nonspace character up to the next terminator.
//  Sets carry if it does not find a nonspace character.
//  Returns the location of the following character in hl.
    PUSH_BC;
    LD_C(NAME_LENGTH_JAPANESE - 1);

loop:
    LD_A_hli;
    CP_A(0x50);
    IF_Z goto terminator;
    CP_A(0x7f);
    IF_NZ goto nonspace;
    DEC_C;
    IF_NZ goto loop;


terminator:
    SCF;
    goto done;


nonspace:
    AND_A_A;


done:
    POP_BC;
    RET;

}

void Function89346(void){
    LD_H_B;
    LD_L_C;
    JR(mv_incave);

}

void Function8934a(void){
    LD_HL(NAME_LENGTH_JAPANESE);
    ADD_HL_BC;
    return v_incave();
}

void v_incave(void){
//  Scans up to 5 characters starting at hl, looking for a nonspace character up to the next terminator.  Sets carry if it does not find a nonspace character.  Returns the location of the following character in hl.
    PUSH_BC;
    LD_C(NAME_LENGTH_JAPANESE - 1);

loop:
    LD_A_hli;
    CP_A(0x50);
    IF_Z goto terminator;
    CP_A(0x7f);
    IF_NZ goto nonspace;
    DEC_C;
    IF_NZ goto loop;


terminator:
    SCF;
    goto done;


nonspace:
    AND_A_A;


done:
    POP_BC;
    RET;

}

void Function89363(void){
//  Scans six byte pairs starting at bc to find $ff.  Sets carry if it does not find a $ff.  Returns the location of the byte after the first $ff found in hl.
    LD_H_B;
    LD_L_C;
    goto _incave;

    LD_HL(25);
    ADD_HL_BC;


_incave:
    PUSH_DE;
    LD_E(NAME_LENGTH_JAPANESE);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_NZ goto ok;
    LD_A_hli;
    CP_A(-1);
    IF_NZ goto ok;
    DEC_E;
    IF_NZ goto loop;
    SCF;
    goto done;


ok:
    AND_A_A;


done:
    POP_DE;
    RET;

}

void Function89381(void){
    PUSH_BC;
    PUSH_DE;
    CALL(aFunction89b45);
    IF_C goto ok;
    PUSH_HL;
    LD_A(-1);
    LD_BC(8);
    CALL(aByteFill);
    POP_HL;


ok:
    POP_DE;
    LD_C(8);
    CALL(aFunction89193);
    POP_BC;
    RET;

}

void Function8939a(void){
    PUSH_BC;
    LD_HL(0);
    ADD_HL_BC;
    LD_DE(wd002);
    LD_C(6);
    CALL(aFunction89193);
    POP_BC;
    LD_HL(17);
    ADD_HL_BC;
    LD_DE(wd008);
    CALL(aFunction89381);
    RET;

}

// Mobile22_LoadFontAndCardGFX
void Function893b3(void){
    // CALL(aDisableLCD);
    DisableLCD_Conv();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // CALL(aLoadFontsExtra);
    LoadFontsExtra_Conv();
    // CALL(aFunction893ef);
    Function893ef();
    // CALL(aFunction8942b);
    Function8942b();
    // CALL(aFunction89455);
    Function89455();
    // CALL(aEnableLCD);
    EnableLCD_Conv();
    // RET;
}

void Function893cc(void){
    CALL(aDisableLCD);
    CALL(aClearSprites);
    CALL(aLoadStandardFont);
    CALL(aLoadFontsExtra);
    CALL(aFunction893ef);
    CALL(aFunction89464);
    CALL(aEnableLCD);
    RET;

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
// TODO: Convert mobile_5e for the card gfx paths.
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x02);
    // LD_HL(mCardLargeSpriteAndFolderGFX);
    // LD_BC(8 * LEN_2BPP_TILE);  // just the large card sprite
    // LD_A(BANK(aCardLargeSpriteAndFolderGFX));
    // CALL(aFarCopyBytes);
    // LD_DE(vTiles0 + LEN_2BPP_TILE * 0x0a);
    // LD_HL(mCardSpriteGFX);
    // LD_BC(4 * LEN_2BPP_TILE);
    // LD_A(BANK(aCardSpriteGFX));
    // CALL(aFarCopyBytes);
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
    ByteFill_Conv2(wram->wVirtualOAMSprite, 24 * SPRITEOAMSTRUCT_LENGTH, 0);
}

// Mobile22_LoadLargeCardSpriteAndFolderGFX
void Function89455(void){
    // LD_HL(mCardLargeSpriteAndFolderGFX);
    // LD_DE(vTiles2 + LEN_2BPP_TILE * 0x0c);
    // LD_BC((8 + 65) * LEN_2BPP_TILE);  // large card sprite + folder
    // LD_A(BANK(aCardLargeSpriteAndFolderGFX));
    // CALL(aFarCopyBytes);
    // RET;
}

void Function89464(void){
    LD_HL(mMobileCardGFX);
    LD_DE(vTiles2);
    LD_BC(0x20 * LEN_2BPP_TILE);
    LD_A(BANK(aMobileCardGFX));
    CALL(aFarCopyBytes);
    LD_HL(mMobileCard2GFX);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x20);
    LD_BC(0x17 * LEN_2BPP_TILE);
    LD_A(BANK(aMobileCard2GFX));
    CALL(aFarCopyBytes);
    RET;

}

void Function89481(void){
    LD_D(2);
    CALL(aFunction8934a);
    RET_C ;
    LD_D(0);
    LD_HL(16);
    ADD_HL_BC;
    BIT_hl(0);
    RET_Z ;
    INC_D;
    RET;

}

// Mobile22_SetDToPlayerGender
uint8_t Function89492(void){
    // LD_D(0);
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // RET_Z ;
    // INC_D;
    // RET;
    return (bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F))? 1: 0;
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
    CopyBytes_Conv2(wram->wBGPals1 + PALETTE_SIZE * 7, Palette_894b3, 1 * PALETTE_SIZE);
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

void Function894bb(void){
    CALL(aFunction894dc);
    PUSH_BC;
    CALL(aFunction8956f);
    CALL(aFunction8949c);
    CALL(aFunction8a60d);
    POP_BC;
    RET;

}

void Function894ca(void){
    PUSH_BC;
    CALL(aFunction894dc);
    CALL(aFunction895c7);
    CALL(aFunction8949c);
    CALL(aFunction8a60d);
    CALL(aSetPalettes);
    POP_BC;
    RET;

}

void Function894dc(void){
    PUSH_BC;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(5);
    LDH_addr_A(rSVBK);

    LD_C_D;
    LD_B(0);
    LD_HL(mFunction894dc_PalettePointers);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wBGPals1);
    LD_BC(3 * PALETTE_SIZE);
    CALL(aCopyBytes);
    LD_HL(mFunction894dc_Pals345);
    LD_DE(wBGPals1 + 3 * PALETTE_SIZE);
    LD_BC(3 * PALETTE_SIZE);
    CALL(aCopyBytes);

    POP_AF;
    LDH_addr_A(rSVBK);
    POP_BC;
    RET;


PalettePointers:
    //dw ['.Pals012a'];
    //dw ['.Pals012b'];
    //dw ['.Pals012c'];


Pals012a:
    //rgb ['31', '31', '31']
    //rgb ['10', '17', '13']
    //rgb ['10', '08', '22']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['16', '20', '31']
    //rgb ['10', '08', '22']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['16', '20', '31']
    //rgb ['10', '17', '13']
    //rgb ['00', '00', '00']


Pals012b:
    //rgb ['31', '31', '31']
    //rgb ['30', '22', '11']
    //rgb ['31', '08', '15']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['16', '20', '31']
    //rgb ['31', '08', '15']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['16', '20', '31']
    //rgb ['30', '22', '11']
    //rgb ['00', '00', '00']


Pals012c:
    //rgb ['31', '31', '31']
    //rgb ['15', '20', '26']
    //rgb ['25', '07', '20']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['16', '20', '31']
    //rgb ['25', '07', '20']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['16', '20', '31']
    //rgb ['15', '20', '26']
    //rgb ['00', '00', '00']


Pals345:
    //rgb ['31', '31', '31']
    //rgb ['31', '31', '31']
    //rgb ['31', '13', '00']
    //rgb ['14', '08', '00']

    //rgb ['31', '31', '31']
    //rgb ['16', '16', '31']
    //rgb ['00', '00', '31']
    //rgb ['00', '00', '00']

    //rgb ['19', '31', '11']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    return Function8956f();
}

void Function8956f(void){
    PUSH_BC;
    LD_HL(16);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(0x000c);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    FARCALL(aGetMobileOTTrainerClass);
    LD_A_C;
    LD_addr_A(wTrainerClass);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(5);
    LDH_addr_A(rSVBK);
    LD_HL(wd030);
    LD_A(-1);
    LD_hli_A;
    LD_A(0x7f);
    LD_hl_A;
    POP_AF;
    LDH_addr_A(rSVBK);
    LD_A_addr(wTrainerClass);
    LD_H(0);
    LD_L_A;
    ADD_HL_HL;
    ADD_HL_HL;
    LD_DE(mTrainerPalettes);
    ADD_HL_DE;
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_DE(wd032);
    LD_C(4);

loop:
    LD_A(BANK(aTrainerPalettes));
    CALL(aGetFarByte);
    LD_de_A;
    INC_DE;
    INC_HL;
    DEC_C;
    IF_NZ goto loop;
    LD_HL(wd036);
    XOR_A_A;
    LD_hli_A;
    LD_hl_A;
    POP_AF;
    LDH_addr_A(rSVBK);
    POP_BC;
    RET;

}

void Function895c7(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(5);
    LDH_addr_A(rSVBK);
    LD_HL(mPalette_895de);
    LD_DE(wd030);
    LD_BC(8);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Palette_895de(void){
    //rgb ['31', '31', '31']
    //rgb ['07', '07', '06']
    //rgb ['07', '07', '06']
    //rgb ['00', '00', '00']

    return Function895e6();
}

void Function895e6(void){
//  //  unreferenced
    LD_A(7);
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    RET;

}

void Function895f2(void){
    PUSH_BC;
    XOR_A_A;
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    CALL(aFunction89605);
    CALL(aFunction89655);
    POP_BC;
    RET;

}

void Function89605(void){
    hlcoord(19, 2, wAttrmap);
    LD_A(1);
    LD_DE(SCREEN_WIDTH);
    LD_C(14);

loop:
    LD_hl_A;
    DEC_C;
    IF_Z goto done;
    ADD_HL_DE;
    INC_A;
    LD_hl_A;
    DEC_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop;


done:
    hlcoord(0, 16, wAttrmap);
    LD_C(10);
    LD_A(2);

loop2:
    LD_hli_A;
    DEC_A;
    LD_hli_A;
    INC_A;
    DEC_C;
    IF_NZ goto loop2;
    hlcoord(1, 11, wAttrmap);
    LD_A(4);
    LD_BC(4);
    CALL(aByteFill);
    LD_A(5);
    LD_BC(14);
    CALL(aByteFill);
    RET;

}

void Function8963d(void){
    hlcoord(12, 3, wAttrmap);
    LD_A(6);
    LD_DE(SCREEN_WIDTH);
    LD_BC((7 << 8) | 7);

loop:
    PUSH_HL;
    LD_C(7);

next:
    LD_hli_A;
    DEC_C;
    IF_NZ goto next;
    POP_HL;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void Function89655(void){
    hlcoord(1, 12, wAttrmap);
    LD_DE(SCREEN_WIDTH);
    LD_A(5);
    LD_B(4);

loop:
    LD_C(18);
    PUSH_HL;

next:
    LD_hli_A;
    DEC_C;
    IF_NZ goto next;
    POP_HL;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop;
    RET;

}

void Function8966c(void){
    PUSH_BC;
    CALL(aFunction89688);
    hlcoord(4, 0, wTilemap);
    LD_C(8);
    CALL(aFunction896f5);
    POP_BC;
    RET;

}

void Function8967a(void){
    PUSH_BC;
    CALL(aFunction89688);
    hlcoord(2, 0, wTilemap);
    LD_C(12);
    CALL(aFunction896f5);
    POP_BC;
    RET;

}

void Function89688(void){
    hlcoord(0, 0, wTilemap);
    LD_A(1);
    LD_E(SCREEN_WIDTH);
    CALL(aFunction896e1);
    LD_A(2);
    LD_E(SCREEN_WIDTH);
    CALL(aFunction896eb);
    LD_A(3);
    LD_hli_A;
    LD_A(4);
    LD_E(SCREEN_HEIGHT);
    CALL(aFunction896e1);
    LD_A(6);
    LD_hli_A;
    PUSH_BC;
    LD_C(13);

loop:
    CALL(aFunction896cb);
    DEC_C;
    IF_Z goto done;
    CALL(aFunction896d6);
    DEC_C;
    IF_NZ goto loop;


done:
    POP_BC;
    LD_A(25);
    LD_hli_A;
    LD_A(26);
    LD_E(SCREEN_HEIGHT);
    CALL(aFunction896e1);
    LD_A(28);
    LD_hli_A;
    LD_A(2);
    LD_E(SCREEN_WIDTH);
    CALL(aFunction896eb);
    RET;

}

void Function896cb(void){
    LD_DE(SCREEN_WIDTH - 1);
    LD_A(7);
    LD_hl_A;
    ADD_HL_DE;
    LD_A(9);
    LD_hli_A;
    RET;

}

void Function896d6(void){
    LD_DE(SCREEN_WIDTH - 1);
    LD_A(10);
    LD_hl_A;
    ADD_HL_DE;
    LD_A(11);
    LD_hli_A;
    RET;

}

void Function896e1(void){

loop:
    LD_hli_A;
    INC_A;
    DEC_E;
    RET_Z ;
    LD_hli_A;
    DEC_A;
    DEC_E;
    IF_NZ goto loop;
    RET;

}

void Function896eb(void){

loop:
    LD_hli_A;
    DEC_A;
    DEC_E;
    RET_Z ;
    LD_hli_A;
    INC_A;
    DEC_E;
    IF_NZ goto loop;
    RET;

}

void Function896f5(void){
    CALL(aFunction8971f);
    CALL(aFunction89736);
    INC_HL;
    INC_HL;
    LD_B(2);

    return Function896ff();
}

void Function896ff(void){
//  //  unreferenced
//  INPUT:
//  hl = address of upper left corner of the area
//  b = height
//  c = width

//  clears an area of the screen
    LD_A(0x7f);
    LD_DE(SCREEN_WIDTH);

row_loop:
    PUSH_BC;
    PUSH_HL;

col_loop:
    LD_hli_A;
    DEC_C;
    IF_NZ goto col_loop;
    POP_HL;
    POP_BC;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto row_loop;

//  alternates tiles $36 and $18 at the bottom of the area
    DEC_HL;
    INC_C;
    INC_C;

bottom_loop:
    LD_A(0x36);
    LD_hli_A;
    DEC_C;
    RET_Z ;
    LD_A(0x18);
    LD_hli_A;
    DEC_C;
    IF_NZ goto bottom_loop;
    RET;

}

void Function8971f(void){
    LD_A(0x2c);
    LD_hli_A;
    LD_A(0x2d);
    LD_hld_A;
    PUSH_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    LD_A(0x31);
    LD_hli_A;
    LD_A(0x32);
    LD_hld_A;
    ADD_HL_DE;
    LD_A(0x35);
    LD_hl_A;
    POP_HL;
    RET;

}

void Function89736(void){
    PUSH_HL;
    INC_HL;
    INC_HL;
    LD_E_C;
    LD_D(0x0);
    ADD_HL_DE;
    LD_A(0x2f);
    LD_hli_A;
    LD_A(0x30);
    LD_hld_A;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    LD_A(0x33);
    LD_hli_A;
    LD_A(0x34);
    LD_hl_A;
    ADD_HL_DE;
    LD_A(0x1f);
    LD_hl_A;
    POP_HL;
    RET;

}

void Function89753(void){
    LD_A(0xc);
    LD_hl_A;
    XOR_A_A;
    CALL(aFunction89215);
    RET;

}

void Function8975b(void){
    LD_A(0x1d);
    LD_hli_A;
    INC_A;
    LD_hli_A;
    LD_A(0xd);
    LD_hl_A;
    DEC_HL;
    DEC_HL;
    LD_A(0x4);
    LD_E(0x3);

asm_89769:
    CALL(aFunction89215);
    INC_HL;
    DEC_E;
    IF_NZ goto asm_89769;
    RET;

}

void Function89771(void){
    LD_A(0x12);
    LD_hl_A;
    LD_A(0x3);
    CALL(aFunction89215);
    RET;

}

void Function8977a(void){
    LD_E(0x4);
    LD_D(0x13);

asm_8977e:
    LD_A_D;
    LD_hl_A;
    LD_A(0x4);
    CALL(aFunction89215);
    INC_HL;
    INC_D;
    DEC_E;
    IF_NZ goto asm_8977e;
    LD_E(0xe);

asm_8978c:
    LD_A_D;
    LD_hl_A;
    XOR_A_A;
    CALL(aFunction89215);
    INC_HL;
    DEC_E;
    IF_NZ goto asm_8978c;
    RET;

}

void Function89797(void){
    PUSH_BC;
    LD_A(0xe);
    LD_hl_A;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    LD_A(0x11);
    LD_hli_A;
    LD_A(0x10);
    LD_C(0x8);

asm_897a6:
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_897a6;
    LD_A(0xf);
    LD_hl_A;
    POP_BC;
    RET;

}

void Function897af(void){
    PUSH_BC;
    LD_HL(0x0010);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(0x000c);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    FARCALL(aGetMobileOTTrainerClass);
    LD_A_C;
    LD_addr_A(wTrainerClass);
    XOR_A_A;
    LD_addr_A(wCurPartySpecies);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x37);
    FARCALL(aGetTrainerPic);
    POP_BC;
    RET;

}

void Function897d5(void){
    PUSH_BC;
    CALL(aFunction8934a);
    IF_NC goto asm_897f3;
    hlcoord(12, 3, wAttrmap);
    XOR_A_A;
    LD_DE(SCREEN_WIDTH);
    LD_BC((7 << 8) | 7);

asm_897e5:
    PUSH_HL;
    LD_C(0x7);

asm_897e8:
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_897e8;
    POP_HL;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto asm_897e5;
    POP_BC;
    RET;


asm_897f3:
    LD_A(0x37);
    LDH_addr_A(hGraphicStartTile);
    hlcoord(12, 3, wTilemap);
    LD_BC((7 << 8) | 7);
    PREDEF(pPlaceGraphic);
    CALL(aFunction8963d);
    POP_BC;
    RET;

}

void Function89807(void){
    LD_HL(mChrisSilhouetteGFX);
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    IF_Z goto asm_89814;
    LD_HL(mKrisSilhouetteGFX);

asm_89814:
    CALL(aDisableLCD);
    LD_DE(vTiles2 + LEN_2BPP_TILE * 0x37);
    LD_BC((5 * 7) * LEN_2BPP_TILE);
    LD_A(BANK(aChrisSilhouetteGFX));  // aka BANK(KrisSilhouetteGFX)
    CALL(aFarCopyBytes);
    CALL(aEnableLCD);
    CALL(aDelayFrame);
    RET;

}

void Function89829(void){
    PUSH_BC;
    LD_BC(0x705);
    LD_DE(0x14);
    LD_A(0x37);

asm_89832:
    PUSH_BC;
    PUSH_HL;

asm_89834:
    LD_hli_A;
    INC_A;
    DEC_C;
    IF_NZ goto asm_89834;
    POP_HL;
    ADD_HL_DE;
    POP_BC;
    DEC_B;
    IF_NZ goto asm_89832;
    CALL(aFunction8963d);
    POP_BC;
    RET;

}

void Function89844(void){
    CALL(aFunction89481);
    CALL(aFunction894bb);
    CALL(aFunction897af);
    PUSH_BC;
    CALL(aWaitBGMap2);
    CALL(aSetPalettes);
    POP_BC;
    RET;

}

void Function89856(void){
    PUSH_BC;
    CALL(aFunction891b8);
    POP_BC;
    CALL(aFunction895f2);
    CALL(aFunction8966c);
    CALL(aFunction899d3);
    CALL(aFunction898aa);
    CALL(aFunction898be);
    CALL(aFunction898dc);
    CALL(aFunction898f3);
    PUSH_BC;
    LD_BC(wd008);
    hlcoord(2, 10, wTilemap);
    CALL(aFunction89975);
    POP_BC;
    CALL(aFunction897d5);
    RET;

}

void Function8987f(void){
    CALL(aFunction891b8);
    CALL(aFunction895f2);
    CALL(aFunction8967a);
    CALL(aFunction899d3);
    hlcoord(5, 1, wTilemap);
    CALL(aFunction8999c);
    hlcoord(13, 3, wTilemap);
    CALL(aFunction89829);
    CALL(aFunction899b2);
    hlcoord(5, 5, wTilemap);
    CALL(aFunction899c9);
    LD_BC(wd008);
    hlcoord(2, 10, wTilemap);
    CALL(aFunction89975);
    RET;

}

void Function898aa(void){
    LD_A_addr(wMenuSelection);
    AND_A_A;
    RET_Z ;
    PUSH_BC;
    hlcoord(6, 1, wTilemap);
    LD_DE(wMenuSelection);
    LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    CALL(aPrintNum);
    POP_BC;
    RET;

}

void Function898be(void){
    PUSH_BC;
    LD_DE(wd002);
    LD_HL(wd002);
    CALL(aFunction89331);
    IF_NC goto asm_898cd;
    LD_DE(mString_89116);


asm_898cd:
    hlcoord(9, 1, wTilemap);
    LD_A_addr(wMenuSelection);
    AND_A_A;
    IF_NZ goto asm_898d7;
    DEC_HL;


asm_898d7:
    CALL(aPlaceString);
    POP_BC;
    RET;

}

void Function898dc(void){
    LD_HL(0x0006);
    ADD_HL_BC;
    PUSH_BC;
    LD_D_H;
    LD_E_L;
    CALL(aFunction8934a);
    IF_NC goto asm_898eb;
    LD_DE(mString_89116);


asm_898eb:
    hlcoord(6, 4, wTilemap);
    CALL(aPlaceString);
    POP_BC;
    RET;

}

void Function898f3(void){
    PUSH_BC;
    LD_HL(0x000c);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    CALL(aFunction8934a);
    IF_C goto asm_8990a;
    hlcoord(5, 5, wTilemap);
    LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    CALL(aPrintNum);
    goto asm_89913;


asm_8990a:
    hlcoord(5, 5, wTilemap);
    LD_DE(mString_89116);
    CALL(aPlaceString);


asm_89913:
    POP_BC;
    RET;

}

void Function89915(void){
    PUSH_BC;
    PUSH_HL;
    LD_DE(mUnknown_89942);
    LD_C(0x8);

asm_8991c:
    LD_A_de;
    LD_hl_A;
    LD_A(0x4);
    CALL(aFunction89215);
    INC_HL;
    INC_DE;
    DEC_C;
    IF_NZ goto asm_8991c;
    POP_HL;
    LD_B(0x4);
    LD_C(0x2b);
    LD_A(0x8);
    LD_DE(mUnknown_8994a);

asm_89932:
    PUSH_AF;
    LD_A_de;
    CP_A_hl;
    IF_NZ goto asm_8993b;
    CALL(aFunction8994e);
    INC_DE;


asm_8993b:
    INC_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_89932;
    POP_BC;
    RET;

}

void Unknown_89942(void){
    //db ['0x24', '0x25', '0x26', '" "', '0x27', '0x28', '0x29', '0x2a'];
    return Unknown_8994a();
}

void Unknown_8994a(void){
    //db ['0x24', '0x27', '0x29', '0xff'];

    return Function8994e();
}

void Function8994e(void){
    PUSH_HL;
    PUSH_DE;
    LD_DE(SCREEN_WIDTH);
    LD_A_L;
    SUB_A_E;
    LD_L_A;
    LD_A_H;
    SBC_A_D;
    LD_H_A;
    LD_A_C;
    LD_hl_A;
    LD_A_B;
    CALL(aFunction89215);
    POP_DE;
    POP_HL;
    RET;

}

void Function89962(void){
    PUSH_BC;
    LD_C(0x4);
    LD_B(0x20);

asm_89967:
    LD_A_B;
    LD_hl_A;
    LD_A(0x4);
    CALL(aFunction89215);
    INC_HL;
    INC_B;
    DEC_C;
    IF_NZ goto asm_89967;
    POP_BC;
    RET;

}

void Function89975(void){
    PUSH_BC;
    LD_E(0x8);

asm_89978:
    LD_A_bc;
    LD_D_A;
    CALL(aFunction8998b);
    SWAP_D;
    INC_HL;
    LD_A_D;
    CALL(aFunction8998b);
    INC_BC;
    INC_HL;
    DEC_E;
    IF_NZ goto asm_89978;
    POP_BC;
    RET;

}

void Function8998b(tile_t* hl, uint8_t a){
    // PUSH_BC;
    // AND_A(0xf);
    // CP_A(0xa);
    // IF_NC goto asm_89997;
    if((a & 0xf) >= 0x7f) {
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

void Function8999c(void){
    LD_DE(wPlayerName);
    CALL(aPlaceString);
    INC_BC;
    LD_H_B;
    LD_L_C;
    LD_DE(mString_899ac);
    CALL(aPlaceString);
    RET;

}

void String_899ac(void){
    //db ['"の\u3000めいし@"'];

    return Function899b2();
}

void Function899b2(void){
    LD_BC(wPlayerName);
    CALL(aFunction89346);
    IF_C goto asm_899bf;
    LD_DE(wPlayerName);
    goto asm_899c2;

asm_899bf:
    LD_DE(mString_89116);

asm_899c2:
    hlcoord(6, 4, wTilemap);
    CALL(aPlaceString);
    RET;

}

void Function899c9(void){
    LD_DE(wPlayerID);
    LD_BC((PRINTNUM_LEADINGZEROS | 2 << 8) | 5);
    CALL(aPrintNum);
    RET;

}

void Function899d3(void){
    hlcoord(1, 4, wTilemap);
    CALL(aFunction89753);
    hlcoord(2, 5, wTilemap);
    CALL(aFunction8975b);
    hlcoord(1, 9, wTilemap);
    CALL(aFunction89771);
    hlcoord(1, 11, wTilemap);
    CALL(aFunction8977a);
    hlcoord(1, 5, wTilemap);
    CALL(aFunction89797);
    hlcoord(2, 4, wTilemap);
    CALL(aFunction89962);
    hlcoord(2, 9, wTilemap);
    CALL(aFunction89915);
    RET;

}

void Function899fe(void){
    PUSH_BC;
    PUSH_HL;
    LD_HL(0x0019);
    ADD_HL_BC;
    LD_B_H;
    LD_C_L;
    POP_HL;
    CALL(aFunction89a0c);
    POP_BC;
    RET;

}

void Function89a0c(void){
    PUSH_HL;
    CALL(aFunction89363);
    POP_HL;
    IF_C goto asm_89a1c;
    LD_D_H;
    LD_E_L;
    FARCALL(aFunction11c08f);
    RET;


asm_89a1c:
    LD_DE(mString_89153);
    CALL(aPlaceString);
    RET;

}

void Function89a23(void){
    hlcoord(0, 11, wTilemap);
    LD_B(0x4);
    LD_C(0x12);
    CALL(aFunction8921f);
    RET;

}

void Function89a2e(void){
    hlcoord(11, 12, wTilemap);
    LD_B(0x2);
    LD_C(0x6);
    CALL(aTextbox);
    hlcoord(13, 13, wTilemap);
    LD_DE(mString_89a4e);
    CALL(aPlaceString);
    hlcoord(13, 14, wTilemap);
    LD_DE(mString_89a53);
    CALL(aPlaceString);
    CALL(aFunction89655);
    RET;

}

void String_89a4e(void){
    //db ['"けってい@"'];

    return String_89a53();
}

void String_89a53(void){
    //db ['"やめる@"'];

    return Function89a57();
}

void Function89a57(void){
    CALL(aJoyTextDelay_ForcehJoyDown);  // joypad
    BIT_C(D_UP_F);
    IF_NZ goto d_up;
    BIT_C(D_DOWN_F);
    IF_NZ goto d_down;
    BIT_C(A_BUTTON_F);
    IF_NZ goto a_b_button;
    BIT_C(B_BUTTON_F);
    IF_NZ goto a_b_button;
    BIT_C(START_F);
    IF_NZ goto start_button;
    SCF;
    RET;


a_b_button:
    LD_A(0x1);
    AND_A_A;
    RET;


start_button:
    LD_A(0x2);
    AND_A_A;
    RET;


d_up:
    CALL(aFunction89a57_MoveCursorUp);
    CALL_NC (aFunction89a57_PlayPocketSwitchSFX);
    LD_A(0x0);
    RET;


d_down:
    CALL(aFunction89a57_MoveCursorDown);
    CALL_NC (aFunction89a57_PlayPocketSwitchSFX);
    LD_A(0x0);
    RET;


PlayPocketSwitchSFX:
    PUSH_AF;
    LD_DE(SFX_SWITCH_POCKETS);
    CALL(aPlaySFX);
    POP_AF;
    RET;


MoveCursorDown:
    LD_D(40);
    LD_E(1);
    CALL(aFunction89a57_ApplyCursorMovement);
    RET;


MoveCursorUp:
    LD_D(1);
    LD_E(-1);
    CALL(aFunction89a57_ApplyCursorMovement);
    RET;


ApplyCursorMovement:
    LD_A_addr(wMenuSelection);
    LD_C_A;
    PUSH_BC;

loop:
    LD_A_addr(wMenuSelection);
    CP_A_D;
    IF_Z goto equal_to_d;
    ADD_A_E;
    IF_NZ goto not_zero;
    INC_A;


not_zero:
    LD_addr_A(wMenuSelection);
    CALL(aFunction89a57_Function89ac7);  // BCD conversion of data in SRAM?
    IF_NC goto loop;
    CALL(aFunction89a57_Function89ae6);  // split [wMenuSelection] into [wd030] + [wd031] where [wd030] <= 5
    POP_BC;
    AND_A_A;
    RET;


equal_to_d:
    POP_BC;
    LD_A_C;
    LD_addr_A(wMenuSelection);
    SCF;
    RET;


Function89ac7:
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    CALL(aFunction89a57_Function89ad4);
    CALL(aCloseSRAM);
    RET;


Function89ad4:
    PUSH_DE;
    CALL(aFunction8932d);  // find a non-space character within 5 bytes of bc
    IF_C goto no_nonspace_character;
    LD_HL(17);
    ADD_HL_BC;
    CALL(aFunction89b45);
    IF_C goto finish_decode;


no_nonspace_character:
    AND_A_A;


finish_decode:
    POP_DE;
    RET;


Function89ae6:
    LD_HL(wd031);
    XOR_A_A;
    LD_hl_A;
    LD_A_addr(wMenuSelection);

loop2:
    CP_A(6);
    IF_C goto load_and_ret;
    SUB_A(5);
    LD_C_A;
    LD_A_hl;
    ADD_A(5);
    LD_hl_A;
    LD_A_C;
    goto loop2;


load_and_ret:
    LD_addr_A(wd030);
    RET;

}

// Mobile22_Mobile_Layout_LoadPals
void Function89b00(void){
    // FARCALL(aMG_Mobile_Layout_LoadPals);
    MG_Mobile_Layout_LoadPals();
    // RET;
}

void Function89b07(void){
    CALL(aMobile22_SetBGMapMode0);
    CALL(aDelayFrame);
    FARCALL(aFunction4a3a7);
    RET;

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
    CALL(aFunction891de);
    CALL(aClearBGPalettes);
    CALL(aFunction893e2);
    CALL(aCall_ExitMenu);
    CALL(aFunction891ab);
    CALL(aSetPalettes);
    RET;

}

void Function89b3b(tile_t* de, uint8_t b, uint8_t c){
    // CALL(aMobile22_SetBGMapMode0);
    Mobile22_SetBGMapMode0();
    // FARCALL(aFunction48cda);
    Function48cda(de, b, c);
    // RET;
}

void Function89b45(void){
// some sort of decoder?
// BCD?
    PUSH_HL;
    PUSH_BC;
    LD_C(0x10);
    LD_E(0x0);

loop:
    LD_A_hli;
    LD_B_A;
    AND_A(0xf);
    CP_A(10);
    IF_C goto low_nybble_less_than_10;
    LD_A_C;
    CP_A(0xb);
    IF_NC goto clear_carry;
    goto set_carry;


low_nybble_less_than_10:
    DEC_C;
    SWAP_B;
    INC_E;
    LD_A_B;
    AND_A(0xf);
    CP_A(10);
    IF_C goto high_nybble_less_than_10;
    LD_A_C;
    CP_A(0xb);
    IF_NC goto clear_carry;
    goto set_carry;


high_nybble_less_than_10:
    INC_E;
    DEC_C;
    IF_NZ goto loop;
    DEC_E;


set_carry:
    SCF;
    goto finish;


clear_carry:
    AND_A_A;


finish:
    POP_BC;
    POP_HL;
    RET;

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
    CALL(aFunction89c34);
    IF_C goto asm_89ba0;
    CALL(aFunction89448);
    RET;

asm_89ba0:
    LD_A_addr(wd011);
    LD_HL(mUnknown_89bd8);
    AND_A_A;
    IF_Z goto asm_89bae;

asm_89ba9:
    INC_HL;
    INC_HL;
    DEC_A;
    IF_NZ goto asm_89ba9;

asm_89bae:
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_DE(wVirtualOAMSprite00);

asm_89bb4:
    LD_A_hli;
    CP_A(0xff);
    RET_Z ;
    LD_C_A;
    LD_B(0);

asm_89bbb:
    PUSH_HL;
    LD_A_hli;
    LD_de_A;  // y
    INC_DE;
    LD_A_hli;
    ADD_A_B;
    LD_de_A;  // x
    INC_DE;
    LD_A(0x08);
    ADD_A_B;
    LD_B_A;
    LD_A_hli;  // tile id
    LD_de_A;
    INC_DE;
    LD_A_hli;  // attributes
    LD_de_A;
    INC_DE;
    POP_HL;
    DEC_C;
    IF_NZ goto asm_89bbb;
    LD_B(0x0);
    LD_C(0x4);
    ADD_HL_BC;
    goto asm_89bb4;

    return Unknown_89bd8();
}

void Unknown_89bd8(void){
    //dw ['Unknown_89be0'];
    //dw ['Unknown_89bf5'];
    //dw ['Unknown_89c0a'];
    //dw ['Unknown_89c1f'];

    return Unknown_89be0();
}

void Unknown_89be0(void){
    //db ['0x01', '0x12', '0x4e', '0x01', '0'];
    //db ['0x01', '0x19', '0x4e', '0x01', '0 | Y_FLIP'];
    //db ['0x01', '0x12', '0x72', '0x01', '0 | X_FLIP'];
    //db ['0x01', '0x19', '0x72', '0x01', '0 | X_FLIP | Y_FLIP'];
    //db ['-1'];  // end

    return Unknown_89bf5();
}

void Unknown_89bf5(void){
    //db ['0x01', '0x60', '0x16', '0x01', '0'];
    //db ['0x01', '0x62', '0x16', '0x01', '0 | Y_FLIP'];
    //db ['0x01', '0x60', '0x92', '0x01', '0 | X_FLIP'];
    //db ['0x01', '0x62', '0x92', '0x01', '0 | X_FLIP | Y_FLIP'];
    //db ['-1'];  // end

    return Unknown_89c0a();
}

void Unknown_89c0a(void){
    //db ['0x01', '0x78', '0x66', '0x01', '0'];
    //db ['0x01', '0x78', '0x66', '0x01', '0 | Y_FLIP'];
    //db ['0x01', '0x78', '0x92', '0x01', '0 | X_FLIP'];
    //db ['0x01', '0x78', '0x92', '0x01', '0 | X_FLIP | Y_FLIP'];
    //db ['-1'];  // end

    return Unknown_89c1f();
}

void Unknown_89c1f(void){
    //db ['0x01', '0x80', '0x66', '0x01', '0'];
    //db ['0x01', '0x80', '0x66', '0x01', '0 | Y_FLIP'];
    //db ['0x01', '0x80', '0x92', '0x01', '0 | X_FLIP'];
    //db ['0x01', '0x80', '0x92', '0x01', '0 | X_FLIP | Y_FLIP'];
    //db ['-1'];  // end
}

bool Function89c34(void){
    // PUSH_BC;
    // LD_A_addr(wd012);
    // LD_C_A;
    uint8_t c = wram->wd012[0];
    // INC_A;
    // AND_A(0xf);
    // LD_addr_A(wd012);
    wram->wd012[0] = (c + 1) & 0xf;
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

void Function89c67(void){
//  menu scrolling?
    CALL(aJoyTextDelay_ForcehJoyDown);  // joypad
    LD_B(0x0);
    BIT_C(A_BUTTON_F);
    IF_Z goto not_a_button;
    LD_B(0x1);
    AND_A_A;
    RET;


not_a_button:
    BIT_C(B_BUTTON_F);
    IF_Z goto not_b_button;
    SCF;
    RET;


not_b_button:
    XOR_A_A;
    BIT_C(D_UP_F);
    IF_Z goto not_d_up;
    LD_A(0x1);

not_d_up:
    BIT_C(D_DOWN_F);
    IF_Z goto not_d_down;
    LD_A(0x2);

not_d_down:
    BIT_C(D_LEFT_F);
    IF_Z goto not_d_left;
    LD_A(0x3);

not_d_left:
    BIT_C(D_RIGHT_F);
    IF_Z goto not_d_right;
    LD_A(0x4);

not_d_right:
    AND_A_A;
    RET_Z ;  // no dpad pressed
    DEC_A;
    LD_C_A;
    LD_D(0x0);
    LD_HL(mFunction89c67_ScrollData0);
    LD_A_addr(wd02f);
    AND_A_A;
    IF_Z goto got_data;
    LD_HL(mFunction89c67_ScrollData1);

got_data:
    LD_A_addr(wd011);
    AND_A_A;
    IF_Z goto got_row;
    LD_E(0x4);

add_n_times:
    ADD_HL_DE;
    DEC_A;
    IF_NZ goto add_n_times;

got_row:
    LD_E_C;
    ADD_HL_DE;
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_A;
    LD_addr_A(wd011);
    XOR_A_A;
    LD_addr_A(wd012);
    RET;


ScrollData0:
    //db ['0', '2', '0', '0'];
    //db ['1', '3', '0', '0'];
    //db ['2', '4', '0', '0'];
    //db ['3', '0', '0', '0'];


ScrollData1:
    //db ['0', '0', '0', '0'];
    //db ['0', '3', '0', '0'];
    //db ['2', '4', '0', '0'];
    //db ['3', '0', '0', '0'];

    return Function89cdf();
}

void Function89cdf(void){
    LD_A(0x10);
    ADD_A_B;
    LD_B_A;
    LD_A(0x8);
    ADD_A_C;
    LD_C_A;
    LD_E(0x2);
    LD_A(0x2);
    LD_HL(wVirtualOAMSprite00);

asm_89cee:
    PUSH_AF;
    PUSH_BC;
    LD_D(0x4);

asm_89cf2:
    LD_A_B;
    LD_hli_A;  // y
    LD_A_C;
    LD_hli_A;  // x
    LD_A_E;
    LD_hli_A;  // tile id
    LD_A(0x1);
    LD_hli_A;  // attributes
    LD_A(0x8);
    ADD_A_C;
    LD_C_A;
    INC_E;
    DEC_D;
    IF_NZ goto asm_89cf2;
    POP_BC;
    LD_A(0x8);
    ADD_A_B;
    LD_B_A;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_89cee;
    RET;

}

void Function89d0d(void){
    CALL(aMobile22_SetBGMapMode0);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);

    LD_C(8);
    LD_DE(wBGPals1);

loop:
    PUSH_BC;
    LD_HL(mFunction89d0d_Palette1);
    LD_BC(1 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_BC;
    DEC_C;
    IF_NZ goto loop;

    LD_HL(mFunction89d0d_Palette2);
    LD_DE(wBGPals1 + 2 * PALETTE_SIZE);
    LD_BC(1 * PALETTE_SIZE);
    CALL(aCopyBytes);

    POP_AF;
    LDH_addr_A(rSVBK);

    CALL(aSetPalettes);
    FARCALL(aPrintMail);
    CALL(aMobile22_SetBGMapMode1);
    LD_C(24);
    CALL(aDelayFrames);
    CALL(aRestartMapMusic);
    RET;


Palette1:
    //rgb ['31', '31', '31']
    //rgb ['19', '19', '19']
    //rgb ['15', '15', '15']
    //rgb ['00', '00', '00']


Palette2:
    //rgb ['31', '31', '31']
    //rgb ['19', '19', '19']
    //rgb ['19', '19', '19']
    //rgb ['00', '00', '00']

    return Function89d5e();
}

void Function89d5e(void){
    PUSH_AF;
    CALL(aCopyMenuHeader);
    POP_AF;
    LD_addr_A(wMenuCursorPosition);
    CALL(aMobile22_SetBGMapMode0);
    CALL(aPlaceVerticalMenuItems);
    CALL(aInitVerticalMenuCursor);
    LD_HL(w2DMenuFlags1);
    SET_hl(7);
    RET;

}

void Function89d75(void){
    PUSH_HL;
    CALL(aMobile22_SetBGMapMode0);
    CALL(av_hl_);
    FARCALL(aMobile_OpenAndCloseMenu_HDMATransferTilemapAndAttrmap);
    POP_HL;
    JR(masm_89d90);

}

void Function89d85(void){
    PUSH_HL;
    CALL(aMobile22_SetBGMapMode0);
    CALL(av_hl_);
    CALL(aCGBOnly_CopyTilemapAtOnce);
    POP_HL;

    return asm_89d90();
}

void asm_89d90(void){
    CALL(aMobile22_SetBGMapMode0);
    PUSH_HL;
    CALL(av_hl_);
    CALL(aFunction89dab);
    LD_A_addr(wMenuCursorY);
    PUSH_AF;
    CALL(aFunction891ab);
    POP_AF;
    POP_HL;
    IF_C goto asm_89da9;
    JR_Z (masm_89d90);
    SCF;
    RET;

asm_89da9:
    AND_A_A;
    RET;

}

void Function89dab(void){
    CALL(aMobile22_SetBGMapMode0);
    FARCALL(aMobileMenuJoypad);
    CALL(aMobile22_SetBGMapMode0);
    LD_A_C;
    LD_HL(wMenuJoypadFilter);
    AND_A_hl;
    RET_Z ;
    BIT_A(0);
    IF_NZ goto asm_89dc7;
    BIT_A(1);
    IF_NZ goto asm_89dd9;
    XOR_A_A;
    RET;

asm_89dc7:
    CALL(aPlayClickSFX);
    LD_A_addr(w2DMenuNumRows);
    LD_C_A;
    LD_A_addr(wMenuCursorY);
    CP_A_C;
    IF_Z goto asm_89dd9;
    CALL(aPlaceHollowCursor);
    SCF;
    RET;

asm_89dd9:
    CALL(aPlayClickSFX);
    LD_A(0x1);
    AND_A_A;
    RET;

}

void Function89de0(void){
    CALL(aClearSprites);
    CALL(aFunction89e0a);
    IF_C goto asm_89e00;
    LD_C(0x1);

asm_89dea:
    CALL(aFunction8a31c);
    IF_Z goto asm_89dfd;
    LD_A_addr(wMenuCursorY);
    LD_C_A;
    PUSH_BC;
    LD_HL(mJumptable_89e04);
    LD_A_E;
    DEC_A;
    RST(aJumpTable);
    POP_BC;
    goto asm_89dea;

asm_89dfd:
    CALL(aFunction891fe);

asm_89e00:
    CALL(aFunction8917a);
    RET;

}

void Jumptable_89e04(void){
    //dw ['Function8a62c'];
    //dw ['Function8a999'];
    //dw ['Function8ab93'];

    return Function89e0a();
}

void Function89e0a(void){
    CALL(aOpenSRAMBank4);
    CALL(aFunction8b3b0);
    CALL(aCloseSRAM);
    LD_HL(mJumptable_89e18);
    RST(aJumpTable);
    RET;

}

void Jumptable_89e18(void){
    //dw ['Function89e1e'];
    //dw ['Function8a116'];
    //dw ['Function8a2aa'];

    return Function89e1e();
}

void Function89e1e(void){
    CALL(aOpenSRAMBank4);
    LD_BC(0xa037);
    CALL(aFunction8b36c);
    CALL(aCloseSRAM);
    XOR_A_A;
    LD_addr_A(wd02d);

    return asm_89e2e();
}

void asm_89e2e(void){
    LD_A_addr(wd02d);
    LD_HL(mJumptable_89e3c);
    RST(aJumpTable);
    RET;

}

void Function89e36(void){
    LD_HL(wd02d);
    INC_hl;
    JR(masm_89e2e);

}

void Jumptable_89e3c(void){
    //dw ['Function89e6f'];
    //dw ['Function89fed'];
    //dw ['Function89ff6'];
    //dw ['Function8a03d'];
    //dw ['Function89eb9'];
    //dw ['Function89efd'];
    //dw ['Function89fce'];
    //dw ['Function8a04c'];
    //dw ['Function8a055'];
    //dw ['Function8a0e6'];
    //dw ['Function8a0ec'];
    //dw ['Function8a0f5'];
    //dw ['Function89e58'];
    //dw ['Function89e68'];

    return Function89e58();
}

void Function89e58(void){
    LD_A(0x1);
    CALL(aFunction8a2fe);
    CALL(aFunction891fe);
    CALL(aFunction893e2);
    CALL(aFunction89168);
    AND_A_A;
    RET;

}

void Function89e68(void){
    CALL(aFunction891fe);
    LD_A(0x1);
    SCF;
    RET;

}

void Function89e6f(void){
    CALL(aFunction891de);
    CALL(aFunction89245);
    CALL(aFunction89ee1);
    CALL(aFunction89e9a);
    hlcoord(7, 4, wTilemap);
    CALL(aFunction8a58d);
    LD_A(0x5);
    hlcoord(7, 4, wAttrmap);
    CALL(aFunction8a5a3);
    LD_A(0x6);
    hlcoord(10, 4, wAttrmap);
    CALL(aFunction8a5a3);
    CALL(aFunction891ab);
    CALL(aSetPalettes);
    JP(mFunction89e36);

}

void Function89e9a(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(mPalette_89eb1);
    LD_DE(wBGPals1 + PALETTE_SIZE * 5);
    LD_BC(1 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Palette_89eb1(void){
    //rgb ['31', '31', '31']
    //rgb ['31', '31', '31']
    //rgb ['27', '19', '00']
    //rgb ['00', '00', '00']

    return Function89eb9();
}

void Function89eb9(void){
    CALL(aFunction891fe);
    CALL(aFunction89ee1);
    CALL(aFunction89e9a);
    hlcoord(7, 4, wTilemap);
    CALL(aFunction8a58d);
    LD_A(0x5);
    hlcoord(7, 4, wAttrmap);
    CALL(aFunction8a5a3);
    LD_A(0x6);
    hlcoord(10, 4, wAttrmap);
    CALL(aFunction8a5a3);
    CALL(aFunction891ab);
    CALL(aSetPalettes);
    JP(mFunction89e36);

}

void Function89ee1(void){
    CALL(aClearBGPalettes);
    CALL(aFunction893e2);
    CALL(aMobile22_SetBGMapMode0);
    FARCALL(aFunction4a3a7);
    FARCALL(aMG_Mobile_Layout_CreatePalBoxes);
    hlcoord(1, 0, wTilemap);
    CALL(aFunction8a53d);
    RET;

}

void Function89efd(void){
    LD_HL(wd012);
    LD_A(0xff);
    LD_hli_A;
    XOR_A_A;
    for(int rept = 0; rept < 4; rept++){
    LD_hli_A;
    }
    LD_hl_A;

asm_89f09:
    LD_HL(wd012);
    INC_hl;
    LD_A_hli;
    AND_A(0x3);
    IF_NZ goto asm_89f2e;
    LD_A_hl;
    CP_A(0x4);
    IF_NC goto asm_89f2e;
    LD_B(0x32);
    INC_hl;
    LD_A_hl;
    DEC_A;
    IF_Z goto asm_89f26;
    LD_C_A;

asm_89f1f:
    LD_A(0xb);
    ADD_A_B;
    LD_B_A;
    DEC_C;
    IF_NZ goto asm_89f1f;

asm_89f26:
    LD_C(0xe8);
    LD_A_addr(wd013);
    CALL(aFunction89fa5);

asm_89f2e:
    LD_A_addr(wd013);
    AND_A_A;
    IF_Z goto asm_89f58;

asm_89f34:
    CALL(aFunction89f6a);
    LD_E_A;
    LD_A_C;
    CP_A(0xa8);
    IF_NC goto asm_89f4d;
    CP_A(0x46);
    IF_C goto asm_89f4d;
    LD_D(0x0);
    DEC_E;
    LD_HL(wd014);
    ADD_HL_DE;
    SET_hl(0);
    INC_E;
    goto asm_89f51;

asm_89f4d:
    LD_A(0x2);
    ADD_A_C;
    LD_C_A;

asm_89f51:
    LD_A_E;
    CALL(aFunction89f77);
    DEC_A;
    IF_NZ goto asm_89f34;

asm_89f58:
    CALL(aDelayFrame);
    LD_HL(wd014);
    LD_C(0x4);

asm_89f60:
    LD_A_hli;
    AND_A_A;
    IF_Z goto asm_89f09;
    DEC_C;
    IF_NZ goto asm_89f60;
    JP(mFunction89e36);

}

void Function89f6a(void){
    PUSH_AF;
    LD_DE(0x10);
    CALL(aFunction89f9a);
    LD_A_hli;
    LD_B_A;
    LD_A_hl;
    LD_C_A;
    POP_AF;
    RET;

}

void Function89f77(void){
    PUSH_AF;
    LD_DE(0x10);
    CALL(aFunction89f9a);
    LD_D(0x2);

asm_89f80:
    PUSH_BC;
    LD_E(0x2);

asm_89f83:
    LD_A_B;
    LD_hli_A;
    LD_A_C;
    LD_hli_A;
    INC_HL;
    INC_HL;
    LD_A(0x8);
    ADD_A_C;
    LD_C_A;
    DEC_E;
    IF_NZ goto asm_89f83;
    POP_BC;
    LD_A(0x8);
    ADD_A_B;
    LD_B_A;
    DEC_D;
    IF_NZ goto asm_89f80;
    POP_AF;
    RET;

}

void Function89f9a(void){
    DEC_A;
    LD_HL(wVirtualOAM);
    AND_A_A;
    RET_Z ;

asm_89fa0:
    ADD_HL_DE;
    DEC_A;
    IF_NZ goto asm_89fa0;
    RET;

}

void Function89fa5(void){
    LD_DE(0x10);
    CALL(aFunction89f9a);
    LD_E(0x2);
    LD_D(0xa);

asm_89faf:
    PUSH_BC;
    LD_A(0x2);

asm_89fb2:
    PUSH_AF;
    LD_A_B;
    LD_hli_A;
    LD_A_C;
    LD_hli_A;
    LD_A_D;
    INC_D;
    LD_hli_A;
    LD_A(0x1);
    LD_hli_A;
    LD_A(0x8);
    ADD_A_C;
    LD_C_A;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_89fb2;
    POP_BC;
    LD_A(0x8);
    ADD_A_B;
    LD_B_A;
    DEC_E;
    IF_NZ goto asm_89faf;
    RET;

}

void Function89fce(void){
    CALL(aFunction8a5b6);
    LD_A(0x5);
    hlcoord(7, 4, wAttrmap);
    CALL(aFunction8a5a3);
    LD_A(0x6);
    hlcoord(10, 4, wAttrmap);
    CALL(aFunction8a5a3);
    CALL(aFunction89448);
    CALL(aSetPalettes);
    CALL(aFunction891ab);
    JP(mFunction89e36);

}

void Function89fed(void){
    LD_HL(mMobileCardFolderIntro1Text);
    CALL(aPrintText);
    JP(mFunction89e36);

}

void Function89ff6(void){
    CALL(aFunction891fe);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aFunction89807);
    CALL(aFunction89492);
    CALL(aFunction894ca);
    CALL(aOpenSRAMBank4);
    LD_HL(0xa603);
    LD_A(-1);
    LD_BC(8);
    CALL(aByteFill);
    LD_HL(0xa603);
    LD_DE(wd008);
    CALL(aFunction89381);
    CALL(aCloseSRAM);
    CALL(aFunction8987f);
    CALL(aOpenSRAMBank4);
    hlcoord(1, 13, wTilemap);
    LD_BC(0xa007);
    CALL(aFunction89a0c);
    CALL(aCloseSRAM);
    CALL(aFunction891ab);
    CALL(aMobile22_PromptButton);
    JP(mFunction89e36);

}

void Function8a03d(void){
    LD_HL(mMobileCardFolderIntro2Text);
    CALL(aMobile_EnableSpriteUpdates);
    CALL(aPrintText);
    CALL(aMobile_DisableSpriteUpdates);
    JP(mFunction89e36);

}

void Function8a04c(void){
    LD_HL(mMobileCardFolderIntro3Text);
    CALL(aPrintText);
    JP(mFunction89e36);

}

void Function8a055(void){
    LD_C(0x7);
    LD_B(0x4);

asm_8a059:
    CALL(aFunction8a0a1);
    INC_C;
    CALL(aFunction8a0c9);
    PUSH_BC;
    CALL(aFunction8a58d);
    POP_BC;
    CALL(aFunction8a0de);
    PUSH_BC;
    PUSH_HL;
    LD_A(0x5);
    CALL(aFunction8a5a3);
    POP_HL;
    INC_HL;
    INC_HL;
    INC_HL;
    LD_A(0x6);
    CALL(aFunction8a5a3);
    CALL(aCGBOnly_CopyTilemapAtOnce);
    POP_BC;
    LD_A_C;
    CP_A(0xb);
    IF_NZ goto asm_8a059;
    CALL(aFunction8a0a1);
    hlcoord(12, 4, wTilemap);
    CALL(aFunction8a58d);
    LD_A(0x5);
    hlcoord(12, 4, wAttrmap);
    CALL(aFunction8a5a3);
    POP_HL;
    LD_A(0x6);
    hlcoord(15, 4, wAttrmap);
    CALL(aFunction8a5a3);
    CALL(aCGBOnly_CopyTilemapAtOnce);
    JP(mFunction89e36);

}

void Function8a0a1(void){
    CALL(aMobile22_SetBGMapMode0);
    PUSH_BC;
    CALL(aFunction8a0c9);
    LD_E(0x6);

asm_8a0aa:
    PUSH_HL;
    LD_BC(0x6);
    ADD_HL_BC;
    LD_D_hl;
    CALL(aFunction8a0c1);
    POP_HL;
    LD_hl_D;
    CALL(aFunction89215);
    LD_BC(0x14);
    ADD_HL_BC;
    DEC_E;
    IF_NZ goto asm_8a0aa;
    POP_BC;
    RET;

}

void Function8a0c1(void){
    PUSH_HL;
    LD_BC(wAttrmap - wTilemap);
    ADD_HL_BC;
    LD_A_hl;
    POP_HL;
    RET;

}

void Function8a0c9(void){
    PUSH_BC;
    hlcoord(0, 0, wTilemap);
    LD_DE(0x14);
    LD_A_B;
    AND_A_A;
    IF_Z goto asm_8a0d8;

asm_8a0d4:
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto asm_8a0d4;

asm_8a0d8:
    LD_D(0x0);
    LD_E_C;
    ADD_HL_DE;
    POP_BC;
    RET;

}

void Function8a0de(void){
    CALL(aFunction8a0c9);
    LD_DE(wAttrmap - wTilemap);
    ADD_HL_DE;
    RET;

}

void Function8a0e6(void){
    CALL(aFunction8b539);
    JP(mFunction89e36);

}

void Function8a0ec(void){
    LD_HL(mMobileCardFolderIntro4Text);
    CALL(aPrintText);
    JP(mFunction89e36);

}

void Function8a0f5(void){
    CALL(aFunction8b555);
    JP_NC (mFunction8a0ff);
    LD_HL(wd02d);
    INC_hl;

    return Function8a0ff();
}

void Function8a0ff(void){
    JP(mFunction89e36);

}

void MobileCardFolderIntro1Text(void){
    //text_far ['_MobileCardFolderIntro1Text']
    //text_end ['?']

    return MobileCardFolderIntro2Text();
}

void MobileCardFolderIntro2Text(void){
    //text_far ['_MobileCardFolderIntro2Text']
    //text_end ['?']

    return MobileCardFolderIntro3Text();
}

void MobileCardFolderIntro3Text(void){
    //text_far ['_MobileCardFolderIntro3Text']
    //text_end ['?']

    return MobileCardFolderIntro4Text();
}

void MobileCardFolderIntro4Text(void){
    //text_far ['_MobileCardFolderIntro4Text']
    //text_end ['?']

    return Function8a116();
}

void Function8a116(void){
    LD_A(0x1);
    LD_addr_A(wd030);
    LD_HL(mMenuHeader_0x8a176);
    CALL(aLoadMenuHeader);

asm_8a121:
    CALL(aMobile22_SetBGMapMode0);
    CALL(aFunction8a17b);
    IF_C goto asm_8a16b;
    LD_A_addr(wMenuCursorY);
    LD_addr_A(wd030);
    DEC_D;
    IF_Z goto asm_8a140;
    CALL(aFunction8a20d);
    IF_C goto asm_8a121;
    XOR_A_A;
    CALL(aFunction8a2fe);
    CALL(aFunction8916e);
    goto asm_8a16b;

asm_8a140:
    CALL(aFunction89174);
    IF_NZ goto asm_8a14c;
    CALL(aFunction8a241);
    IF_C goto asm_8a121;
    goto asm_8a15a;

asm_8a14c:
    CALL(aWaitSFX);
    LD_DE(SFX_TWINKLE);
    CALL(aPlaySFX);
    LD_C(0x10);
    CALL(aDelayFrames);

asm_8a15a:
    CALL(aExitMenu);
    CALL(aFunction891de);
    CALL(aFunction893e2);
    CALL(aFunction89245);
    CALL(aFunction89168);
    AND_A_A;
    RET;

asm_8a16b:
    CALL(aMobile_EnableSpriteUpdates);
    CALL(aCloseWindow);
    CALL(aMobile_DisableSpriteUpdates);
    SCF;
    RET;

}

void MenuHeader_0x8a176(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['14', '0', 'SCREEN_WIDTH - 1', '6'];

    return Function8a17b();
}

void Function8a17b(void){
    decoord(14, 0, wTilemap);
    LD_B(0x5);
    LD_C(0x4);
    CALL(aFunction89b3b);
    LD_HL(mMenuHeader_0x8a19a);
    LD_A_addr(wd030);
    CALL(aFunction89d5e);
    LD_HL(mFunction8a1b0);
    CALL(aFunction89d75);
    IF_NC goto asm_8a198;
    LD_A(0x0);

asm_8a198:
    LD_D_A;
    RET;

}

void MenuHeader_0x8a19a(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['14', '0', 'SCREEN_WIDTH - 1', '6'];
    //dw ['MenuData_0x8a1a2'];
    //db ['1'];  // default option

    return MenuData_0x8a1a2();
}

void MenuData_0x8a1a2(void){
    //db ['STATICMENU_CURSOR | STATICMENU_NO_TOP_SPACING | STATICMENU_WRAP'];  // flags
    //db ['3'];  // items
    //db ['"ひらく@"'];
    //db ['"すてる@"'];
    //db ['"もどる@"'];

    return Function8a1b0();
}

void Function8a1b0(void){
    hlcoord(0, 12, wTilemap);
    LD_B(0x4);
    LD_C(0x12);
    CALL(aTextbox);
    hlcoord(1, 14, wTilemap);
    LD_A_addr(wMenuCursorY);
    LD_DE(mStrings_8a1cc);
    DEC_A;
    LD_C_A;
    CALL(aFunction8919e);
    CALL(aPlaceString);
    RET;

}

void Strings_8a1cc(void){
    //db ['"めいし<NO>せいりと\u3000へんしゅうを"'];
    //next ['"おこないます"']
    //db ['"@"'];

    //db ['"めいしフォルダー<NO>めいしと"'];
    //next ['"あんしょうばんごう<WO>けします"']
    //db ['"@"'];

    //db ['"まえ<NO>がめん<NI>もどります"'];
    //db ['"@"'];

    return Function8a20d();
}

void Function8a20d(void){
    LD_HL(mMobileCardFolderAskDeleteText);
    CALL(aPrintText);
    LD_A(0x2);
    CALL(aFunction89259);
    RET_C ;
    LD_HL(mMobileCardFolderDeleteAreYouSureText);
    CALL(aPrintText);
    LD_A(0x2);
    CALL(aFunction89259);
    RET_C ;
    XOR_A_A;
    CALL(aFunction8a2fe);
    LD_HL(mMobileCardFolderDeletedText);
    CALL(aPrintText);
    XOR_A_A;
    AND_A_A;
    RET;

}

void MobileCardFolderAskDeleteText(void){
    //text_far ['_MobileCardFolderAskDeleteText']
    //text_end ['?']

    return MobileCardFolderDeleteAreYouSureText();
}

void MobileCardFolderDeleteAreYouSureText(void){
    //text_far ['_MobileCardFolderDeleteAreYouSureText']
    //text_end ['?']

    return MobileCardFolderDeletedText();
}

void MobileCardFolderDeletedText(void){
    //text_far ['_MobileCardFolderDeletedText']
    //text_end ['?']

    return Function8a241();
}

void Function8a241(void){
    CALL(aLoadStandardMenuHeader);
    CALL(aFunction891fe);
    CALL(aFunction8a262);
    IF_NC goto asm_8a254;
    CALL(aFunction891fe);
    CALL(aFunction89b28);
    SCF;
    RET;

asm_8a254:
    CALL(aFunction891de);
    CALL(aClearBGPalettes);
    CALL(aCall_ExitMenu);
    CALL(aFunction891de);
    AND_A_A;
    RET;

}

bool Function8a262(void){
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
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
    Function8b36c(wram->wd013);
    // CALL(aFunction8b493);
    Function8b493(wram->wd013);
    // CALL(aFunction891ab);
    Function891ab();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aFunction8b5e7);
    // RET;
    return Function8b5e7();
}

void Function8a2aa(void){
    LD_HL(mMenuHeader_0x8a2ef);
    CALL(aLoadMenuHeader);
    LD_HL(mMobileCardFolderAskOpenOldText);
    CALL(aPrintText);
    LD_A(0x1);
    CALL(aFunction89259);
    IF_NC goto asm_8a2cf;
    LD_HL(mMobileCardFolderAskDeleteOldText);
    CALL(aPrintText);
    LD_A(0x2);
    CALL(aFunction89259);
    IF_C goto asm_8a2ea;
    CALL(aFunction8a20d);
    goto asm_8a2ea;

asm_8a2cf:
    CALL(aExitMenu);
    CALL(aFunction8a241);
    IF_C goto asm_8a2ed;
    LD_A(0x1);
    CALL(aFunction8a313);
    CALL(aCloseSRAM);
    CALL(aFunction891de);
    CALL(aFunction89245);
    CALL(aFunction89168);
    AND_A_A;
    RET;

asm_8a2ea:
    CALL(aCloseWindow);

asm_8a2ed:
    SCF;
    RET;

}

void MenuHeader_0x8a2ef(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '12', 'SCREEN_WIDTH - 1', 'SCREEN_HEIGHT - 1'];

    return MobileCardFolderAskOpenOldText();
}

void MobileCardFolderAskOpenOldText(void){
    //text_far ['_MobileCardFolderAskOpenOldText']
    //text_end ['?']

    return MobileCardFolderAskDeleteOldText();
}

void MobileCardFolderAskDeleteOldText(void){
    //text_far ['_MobileCardFolderAskDeleteOldText']
    //text_end ['?']

    return Function8a2fe();
}

void Function8a2fe(void){
    CALL(aFunction8a313);
    CALL(aFunction89305);
    LD_HL(0xa603);
    LD_BC(0x8);
    LD_A(-1);
    CALL(aByteFill);
    CALL(aCloseSRAM);
    RET;

}

void Function8a313(void){
    LD_C_A;
    CALL(aOpenSRAMBank4);
    LD_A_C;
    LD_addr_A(0xa60b);
    RET;

}

void Function8a31c(void){
    PUSH_BC;
    CALL(aMobile22_SetBGMapMode0);
    FARCALL(aFunction4a3a7);
    FARCALL(aMG_Mobile_Layout_CreatePalBoxes);
    hlcoord(1, 0, wTilemap);
    CALL(aFunction8a53d);
    hlcoord(12, 4, wTilemap);
    CALL(aFunction8a58d);
    CALL(aFunction8a3b2);
    POP_BC;
    LD_A_C;
    LD_addr_A(wMenuCursorPosition);
    LD_addr_A(wMenuSelection);
    CALL(aPlaceVerticalMenuItems);
    CALL(aInitVerticalMenuCursor);
    LD_HL(w2DMenuFlags1);
    SET_hl(7);

asm_8a34e:
    CALL(aFunction8a3a2);
    CALL(aMobile22_SetBGMapMode0);
    CALL(aFunction8a453);
    CALL(aFunction8a4d3);
    CALL(aFunction8a4fc);
    CALL(aFunction891ab);
    CALL(aSetPalettes);
    CALL(aFunction8a383);
    IF_C goto asm_8a370;
    IF_Z goto asm_8a34e;

asm_8a36a:
    CALL(aFunction89448);
    XOR_A_A;
    LD_E_A;
    RET;

asm_8a370:
    CALL(aFunction89448);
    CALL(aPlaceHollowCursor);
    CALL(aFunction8a3a2);
    LD_A_addr(wMenuSelection);
    CP_A(0xff);
    IF_Z goto asm_8a36a;
    LD_E_A;
    AND_A_A;
    RET;

}

void Function8a383(void){
    FARCALL(aMobileMenuJoypad);
    LD_A_C;
    LD_HL(wMenuJoypadFilter);
    AND_A_hl;
    RET_Z ;
    BIT_A(0);
    IF_NZ goto asm_8a399;
    BIT_A(1);
    IF_NZ goto asm_8a39e;
    XOR_A_A;
    RET;

asm_8a399:
    CALL(aPlayClickSFX);
    SCF;
    RET;

asm_8a39e:
    CALL(aPlayClickSFX);
    RET;

}

void Function8a3a2(void){
    LD_A_addr(wMenuCursorY);
    DEC_A;
    LD_HL(wd002);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    LD_addr_A(wMenuSelection);
    RET;

}

void Function8a3b2(void){
    LD_A(0x1);
    LD_addr_A(wMenuSelection);
    CALL(aFunction8a4fc);
    CALL(aFunction8a3df);
    IF_NC goto asm_8a3ce;
    decoord(0, 2, wTilemap);
    LD_B(0x6);
    LD_C(0x9);
    CALL(aFunction89b3b);
    LD_HL(mMenuHeader_0x8a435);
    goto asm_8a3db;

asm_8a3ce:
    decoord(0, 2, wTilemap);
    LD_B(0x8);
    LD_C(0x9);
    CALL(aFunction89b3b);
    LD_HL(mMenuHeader_0x8a40f);

asm_8a3db:
    CALL(aCopyMenuHeader);
    RET;

}

void Function8a3df(void){
    CALL(aOpenSRAMBank4);
    LD_HL(0xa603);
    CALL(aFunction89b45);
    CALL(aCloseSRAM);
    LD_HL(wd002);
    IF_C goto asm_8a3f8;
    LD_DE(mUnknown_8a408);
    CALL(aFunction8a400);
    SCF;
    RET;

asm_8a3f8:
    LD_DE(mUnknown_8a40b);
    CALL(aFunction8a400);
    AND_A_A;
    RET;

}

void Function8a400(void){
    LD_A_de;
    INC_DE;
    LD_hli_A;
    CP_A(0xff);
    JR_NZ (mFunction8a400);
    RET;

}

void Unknown_8a408(void){
//db 1, 2, -1
    return Unknown_8a40b();
}

void Unknown_8a40b(void){
//db 1, 2, 3, -1

    return MenuHeader_0x8a40f();
}

void MenuHeader_0x8a40f(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '2', '10', 'TEXTBOX_Y - 1'];
    //dw ['MenuData_0x8a417'];
    //db ['1'];  // default option

    return MenuData_0x8a417();
}

void MenuData_0x8a417(void){
    //db ['STATICMENU_CURSOR | STATICMENU_WRAP'];  // flags
    //db ['4'];  // items
    //db ['"めいしりスト@"'];
    //db ['"じぶんの\u3000めいし@"'];
    //db ['"めいしこうかん@"'];
    //db ['"やめる@"'];

    return MenuHeader_0x8a435();
}

void MenuHeader_0x8a435(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['0', '2', '10', '9'];
    //dw ['MenuData_0x8a43d'];
    //db ['1'];  // default option

    return MenuData_0x8a43d();
}

void MenuData_0x8a43d(void){
    //db ['STATICMENU_CURSOR | STATICMENU_WRAP'];  // flags
    //db ['3'];  // items
    //db ['"めいしりスト@"'];
    //db ['"じぶんの\u3000めいし@"'];
    //db ['"やめる@"'];

    return Function8a453();
}

void Function8a453(void){
    hlcoord(0, 12, wTilemap);
    LD_B(0x4);
    LD_C(0x12);
    CALL(aTextbox);
    hlcoord(1, 14, wTilemap);
    LD_DE(mString_8a476);
    LD_A_addr(wMenuSelection);
    CP_A(0xff);
    IF_Z goto asm_8a472;
    LD_DE(mStrings_8a483);
    DEC_A;
    LD_C_A;
    CALL(aFunction8919e);

asm_8a472:
    CALL(aPlaceString);
    RET;

}

void String_8a476(void){
    //db ['"まえ<NO>がめん<NI>もどります@"'];

    return Strings_8a483();
}

void Strings_8a483(void){
    //db ['"おともだち<NO>めいしは"'];
    //next ['"ここ<NI>いれておきます@"']

    //db ['"でんわばんごう<WO>いれると"'];
    //next ['"めいしこうかん<GA>できます@"']

    //db ['"ともだちと\u3000じぶん<NO>めいしを"'];
    //next ['"せきがいせんで\u3000こうかん\u3000します@"']

    return Function8a4d3();
}

void Function8a4d3(void){
    LD_A_addr(wMenuSelection);
    CP_A(0x1);
    IF_NZ goto asm_8a4eb;
    LD_A(0x5);
    hlcoord(12, 4, wAttrmap);
    CALL(aFunction8a5a3);
    LD_A(0x7);
    hlcoord(15, 4, wAttrmap);
    CALL(aFunction8a5a3);
    RET;

asm_8a4eb:
    LD_A(0x7);
    hlcoord(12, 4, wAttrmap);
    CALL(aFunction8a5a3);
    LD_A(0x6);
    hlcoord(15, 4, wAttrmap);
    CALL(aFunction8a5a3);
    RET;

}

void Function8a4fc(void){
    LD_A_addr(wMenuSelection);
    CP_A(0x3);
    JR_NZ (masm_8a529);
    LD_HL(wd012);
    LD_A_hli;
    LD_B_A;
    LD_A_hld;
    ADD_A_B;
    LD_hl_A;
    LD_B_A;
    LD_C(0x80);
    CALL(aFunction89cdf);
    CALL(aFunction8a515);
    RET;

}

void Function8a515(void){
    LD_HL(wd012);
    LD_A_hl;
    CP_A(0x38);
    IF_C goto asm_8a520;
    CP_A(0x3c);
    RET_C ;

asm_8a520:
    LD_A_addr(wd013);
    CPL;
    INC_A;
    LD_addr_A(wd013);
    RET;

}

void asm_8a529(void){
    LD_HL(wd012);
    LD_A(0x3c);
    LD_hli_A;
    LD_A(0xff);
    LD_hli_A;
    LD_HL(wVirtualOAM);
    XOR_A_A;
    LD_BC(8 * SPRITEOAMSTRUCT_LENGTH);
    CALL(aByteFill);
    RET;

}

void Function8a53d(tile_t* hl){
    // PUSH_HL;
    tile_t* hl2 = hl;
    // LD_A(0x15);
    // LD_C(0x8);
    // LD_DE(0x14);
    // CALL(aFunction8a573);
    hl2 = Function8a573(hl2, 0x15, 0x8);
    // LD_A(0x1d);
    // LD_C(0x9);
    // CALL(aFunction8a57c);
    hl2 = Function8a57c(hl2, 0x1d, 0x9);
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
    hl2 = Function8a57c(hl2, 0x26, 0x1);
    // LD_A(0x52);
    // LD_C(0x3);
    // CALL(aFunction8a573);
    hl2 = Function8a573(hl2, 0x52, 0x3);
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
    CopyBytes_Conv2(wram->wBGPals1 + 4 * PALETTE_SIZE, Palette_8a5e5, 3 * PALETTE_SIZE);
    // LD_HL(mPalette_8a5fd);
    // LD_DE(wOBPals1);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wOBPals1, Palette_8a5fd, 1 * PALETTE_SIZE);
    // LD_HL(mPalette_8a605);
    // LD_DE(wOBPals1 + 1 * PALETTE_SIZE);
    // LD_BC(1 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wOBPals1 + 1 * PALETTE_SIZE, Palette_8a605, 1 * PALETTE_SIZE);
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

void Function8a60d(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(mPalette_8a624);
    LD_DE(wOBPals1);
    LD_BC(1 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Palette_8a624(void){
    //rgb ['31', '31', '31']
    //rgb ['31', '31', '31']
    //rgb ['31', '31', '31']
    //rgb ['00', '00', '00']

    return Function8a62c();
}

void Function8a62c(void){
    CALL(aLoadStandardMenuHeader);
    CALL(aFunction891fe);
    XOR_A_A;
    CALL(aFunction8b94a);
    CALL(aFunction8b677);

asm_8a639:
    XOR_A_A;
    LD_addr_A(wd033);
    LD_addr_A(wd032);
    LD_addr_A(wd0e3);
    CALL(aFunction8b7bd);
    LD_A_C;
    AND_A_A;
    IF_Z goto asm_8a66a;
    LD_addr_A(wMenuSelection);
    LD_B_A;
    LD_A_addr(wScrollingMenuCursorPosition);
    INC_A;
    LD_addr_A(wd034);
    PUSH_BC;
    CALL(aFunction8b960);
    LD_A_C;
    POP_BC;
    IF_Z goto asm_8a639;
    LD_C_A;
    LD_HL(mJumptable_8a671);
    LD_A_B;
    LD_addr_A(wMenuSelection);
    LD_A_C;
    DEC_A;
    RST(aJumpTable);
    goto asm_8a639;

asm_8a66a:
    CALL(aFunction891fe);
    CALL(aFunction89b28);
    RET;

}

void Jumptable_8a671(void){
    //dw ['Function8a679'];
    //dw ['Function8a6cd'];
    //dw ['Function8a8c3'];
    //dw ['Function8a930'];

    return Function8a679();
}

void Function8a679(void){
    CALL(aFunction891de);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    CALL(aFunction89844);
    CALL(aCloseSRAM);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8939a);
    CALL(aFunction89856);
    hlcoord(1, 13, wTilemap);
    CALL(aFunction899fe);
    CALL(aFunction891ab);
    CALL(aCloseSRAM);

asm_8a6a3:
    CALL(aFunction89a57);
    IF_C goto asm_8a6a3;
    AND_A_A;
    JR_Z (mFunction8a679);
    LD_HL(mJumptable_8a6bc);
    DEC_A;
    RST(aJumpTable);
    JR_C (mFunction8a679);
    CALL(aFunction891fe);
    CALL(aFunction8b677);
    CALL(aFunction89448);
    RET;

}

void Jumptable_8a6bc(void){
    //dw ['Function8a6c0'];
    //dw ['Function8a6c5'];

    return Function8a6c0();
}

void Function8a6c0(void){
    CALL(aPlayClickSFX);
    AND_A_A;
    RET;

}

void Function8a6c5(void){
    CALL(aPlayClickSFX);
    CALL(aFunction89d0d);
    SCF;
    RET;

}

void Function8a6cd(void){
    CALL(aFunction891de);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    CALL(aFunction89844);
    CALL(aFunction8a757);
    CALL(aCloseSRAM);

asm_8a6e5:
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    CALL(aFunction89856);
    CALL(aFunction89a2e);
    CALL(aFunction891ab);
    XOR_A_A;
    LD_addr_A(wd02f);
    CALL(aCloseSRAM);

asm_8a6fb:
    CALL(aFunction89b97);
    CALL(aFunction89c67);
    IF_C goto asm_8a718;
    LD_A_B;
    AND_A_A;
    IF_Z goto asm_8a6fb;
    CALL(aPlayClickSFX);
    CALL(aFunction89448);
    LD_A_addr(wd011);
    LD_HL(mJumptable_8a74f);
    RST(aJumpTable);
    IF_NC goto asm_8a6e5;
    goto asm_8a742;

asm_8a718:
    CALL(aOpenSRAMBank4);
    CALL(aFunction8a765);
    CALL(aCloseSRAM);
    IF_NC goto asm_8a73f;
    CALL(aMobile22_SetBGMapMode0);
    CALL(aFunction89448);
    CALL(aFunction89a23);
    hlcoord(1, 13, wTilemap);
    LD_DE(mString_89135);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    LD_A(0x2);
    CALL(aFunction89254);
    IF_C goto asm_8a6e5;

asm_8a73f:
    CALL(aCloseSRAM);

asm_8a742:
    CALL(aClearBGPalettes);
    CALL(aFunction89448);
    CALL(aFunction891d3);
    CALL(aFunction8b677);
    RET;

}

void Jumptable_8a74f(void){
    //dw ['Function8a78c'];
    //dw ['Function8a7cb'];
    //dw ['Function8a818'];
    //dw ['Function8a8a1'];

    return Function8a757();
}

void Function8a757(void){
    CALL(aFunction8939a);
    XOR_A_A;
    LD_addr_A(wd010);
    LD_addr_A(wd011);
    LD_addr_A(wd012);
    RET;

}

void Function8a765(void){
    CALL(aFunction8931b);
    PUSH_BC;
    LD_HL(0x0);
    ADD_HL_BC;
    LD_DE(wd002);
    LD_C(0x6);
    CALL(aFunction89185);
    POP_BC;
    IF_NZ goto asm_8a78a;
    PUSH_BC;
    LD_HL(0x11);
    ADD_HL_BC;
    LD_DE(wd008);
    LD_C(0x8);
    CALL(aFunction89185);
    POP_BC;
    IF_NZ goto asm_8a78a;
    AND_A_A;
    RET;

asm_8a78a:
    SCF;
    RET;

}

void Function8a78c(void){
    CALL(aFunction891fe);
    LD_DE(wd002);
    LD_B(NAME_FRIEND);
    FARCALL(aNamingScreen);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    PUSH_BC;
    LD_HL(0x0);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(wd002);
    CALL(aInitName);
    CALL(aCloseSRAM);
    CALL(aDelayFrame);
    CALL(aJoyTextDelay);
    CALL(aFunction891de);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aOpenSRAMBank4);
    POP_BC;
    CALL(aFunction89844);
    CALL(aCloseSRAM);
    AND_A_A;
    RET;

}

void Function8a7cb(void){
    LD_A_addr(wMenuSelection);
    PUSH_AF;
    CALL(aFunction891de);
    LD_DE(wd008);
    LD_C(0x0);
    FARCALL(aFunction17a68f);
    IF_C goto asm_8a7f4;
    LD_HL(wd008);
    LD_A(0xff);
    LD_BC(0x8);
    CALL(aByteFill);
    LD_H_D;
    LD_L_E;
    LD_DE(wd008);
    LD_C(0x8);
    CALL(aFunction89193);

asm_8a7f4:
    POP_AF;
    LD_addr_A(wMenuSelection);
    CALL(aFunction891de);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    CALL(aFunction89844);
    CALL(aFunction89856);
    CALL(aFunction89a2e);
    CALL(aFunction891ab);
    CALL(aCloseSRAM);
    AND_A_A;
    RET;

}

void Function8a818(void){
    CALL(aFunction89a23);
    LD_HL(wd002);
    CALL(aFunction89331);
    IF_C goto asm_8a875;
    LD_HL(wd008);
    CALL(aFunction89b45);
    IF_NC goto asm_8a87a;
    CALL(aOpenSRAMBank4);
    CALL(aFunction8a765);
    IF_NC goto asm_8a863;
    CALL(aFunction8931b);
    PUSH_BC;
    LD_HL(0x0);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(wd002);
    LD_C(0x6);
    CALL(aFunction89193);
    POP_BC;
    LD_HL(0x11);
    ADD_HL_BC;
    LD_D_H;
    LD_E_L;
    LD_HL(wd008);
    LD_C(0x8);
    CALL(aFunction89193);
    hlcoord(1, 13, wTilemap);
    LD_DE(mFunction8a818_string_8a868);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    CALL(aJoyWaitAorB);

asm_8a863:
    CALL(aCloseSRAM);
    SCF;
    RET;


string_8a868:
    //db ['"めいし<WO>かきかえ\u3000まし<TA!>@"'];


asm_8a875:
    LD_DE(mString_8a88b);
    goto asm_8a87d;

asm_8a87a:
    LD_DE(mString_8911c);

asm_8a87d:
    hlcoord(1, 13, wTilemap);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    CALL(aJoyWaitAorB);
    AND_A_A;
    RET;

}

void String_8a88b(void){
    //db ['"おともだち<NO>なまえが"'];
    //next ['"かかれて\u3000いません！@"']

    return Function8a8a1();
}

void Function8a8a1(void){
    CALL(aOpenSRAMBank4);
    CALL(aFunction8a765);
    CALL(aCloseSRAM);
    IF_NC goto asm_8a8bf;
    CALL(aFunction89a23);
    hlcoord(1, 13, wTilemap);
    LD_DE(mString_89135);
    CALL(aPlaceString);
    LD_A(0x2);
    CALL(aFunction89254);
    IF_C goto asm_8a8c1;

asm_8a8bf:
    SCF;
    RET;

asm_8a8c1:
    AND_A_A;
    RET;

}

void Function8a8c3(void){
    CALL(aFunction891de);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    CALL(aFunction89844);
    CALL(aFunction8939a);
    CALL(aFunction89856);
    CALL(aCloseSRAM);
    CALL(aFunction891ab);
    hlcoord(1, 13, wTilemap);
    LD_DE(mString_8a919);
    CALL(aPlaceString);
    LD_A(0x2);
    CALL(aFunction89254);
    IF_C goto asm_8a90f;
    CALL(aOpenSRAMBank4);
    CALL(aFunction892b4);
    CALL(aCloseSRAM);
    CALL(aFunction89a23);
    CALL(aMobile22_SetBGMapMode0);
    hlcoord(1, 13, wTilemap);
    LD_DE(mString_8a926);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    CALL(aJoyWaitAorB);

asm_8a90f:
    CALL(aFunction89448);
    CALL(aFunction891fe);
    CALL(aFunction8b677);
    RET;

}

void String_8a919(void){
    //db ['"このデータ<WO>けしますか？@"'];

    return String_8a926();
}

void String_8a926(void){
    //db ['"データ<WO>けしまし<TA!>@"'];

    return Function8a930();
}

void Function8a930(void){
    LD_A_addr(wMenuSelection);
    PUSH_AF;
    XOR_A_A;
    LD_addr_A(wd032);
    LD_A(0x1);
    LD_addr_A(wd033);
    LD_A_addr(wd034);
    LD_addr_A(wd0e3);

asm_8a943:
    CALL(aFunction8b7bd);
    LD_A_addr(wMenuJoypad);
    AND_A(0x1);
    IF_NZ goto asm_8a953;
    LD_A_C;
    AND_A_A;
    IF_NZ goto asm_8a943;
    POP_AF;
    RET;

asm_8a953:
    CALL(aOpenSRAMBank4);
    POP_AF;
    CP_A_C;
    IF_Z goto asm_8a995;
    PUSH_BC;
    LD_addr_A(wMenuSelection);
    CALL(aFunction8931b);
    PUSH_BC;
    LD_H_B;
    LD_L_C;
    LD_DE(wd002);
    LD_BC(0x25);
    CALL(aCopyBytes);
    POP_DE;
    POP_BC;
    LD_A_C;
    LD_addr_A(wMenuSelection);
    CALL(aFunction8931b);
    PUSH_BC;
    LD_H_B;
    LD_L_C;
    LD_BC(0x25);
    CALL(aCopyBytes);
    POP_DE;
    LD_HL(wd002);
    LD_BC(0x25);
    CALL(aCopyBytes);
    LD_DE(SFX_SWITCH_POKEMON);
    CALL(aWaitPlaySFX);
    LD_DE(SFX_SWITCH_POKEMON);
    CALL(aWaitPlaySFX);

asm_8a995:
    CALL(aCloseSRAM);
    RET;

}

void Function8a999(void){
    LD_HL(mMenuHeader_0x8a9c9);
    CALL(aLoadMenuHeader);
    LD_C(0x1);

asm_8a9a1:
    CALL(aFunction8a9ce);
    IF_C goto asm_8a9bb;
    PUSH_BC;
    PUSH_DE;
    CALL(aLoadStandardMenuHeader);
    POP_DE;
    DEC_E;
    LD_A_E;
    LD_HL(mJumptable_8a9c5);
    RST(aJumpTable);
    CALL(aFunction891fe);
    CALL(aFunction89b28);
    POP_BC;
    goto asm_8a9a1;

asm_8a9bb:
    CALL(aMobile_EnableSpriteUpdates);
    CALL(aCloseWindow);
    CALL(aMobile_DisableSpriteUpdates);
    RET;

}

void Jumptable_8a9c5(void){
    //dw ['Function8aa0a'];
    //dw ['Function8ab3b'];

    return MenuHeader_0x8a9c9();
}

void MenuHeader_0x8a9c9(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['11', '4', '18', 'TEXTBOX_Y - 1'];

    return Function8a9ce();
}

void Function8a9ce(void){
    PUSH_BC;
    decoord(11, 4, wTilemap);
    LD_B(0x6);
    LD_C(0x6);
    CALL(aFunction89b3b);
    POP_BC;
    LD_A_C;
    LD_HL(mMenuHeader_0x8a9f2);
    CALL(aFunction89d5e);
    LD_HL(mFunction8aa09);
    CALL(aFunction89d85);
    IF_C goto asm_8a9ed;
    LD_C_A;
    LD_E_A;
    AND_A_A;
    RET;

asm_8a9ed:
    LD_C_A;
    LD_E(0x0);
    SCF;
    RET;

}

void MenuHeader_0x8a9f2(void){
    //db ['MENU_BACKUP_TILES'];  // flags
    //menu_coords ['11', '4', '18', 'TEXTBOX_Y - 1'];
    //dw ['MenuData_0x8a9fa'];
    //db ['1'];  // default option

    return MenuData_0x8a9fa();
}

void MenuData_0x8a9fa(void){
    //db ['STATICMENU_CURSOR | STATICMENU_WRAP'];  // flags
    //db ['3'];  // items
    //db ['"へんしゅう@"'];
    //db ['"みる@"'];
    //db ['"やめる@"'];

    return Function8aa09();
}

void Function8aa09(void){
    RET;

}

void Function8aa0a(void){
    LD_A(0x1);
    LD_addr_A(wd02f);
    LD_addr_A(wd011);
    XOR_A_A;
    LD_addr_A(wd010);
    LD_addr_A(wd012);
    CALL(aOpenSRAMBank4);
    LD_HL(0xa603);
    LD_DE(wd008);
    CALL(aFunction89381);
    CALL(aCloseSRAM);
    CALL(aFunction891fe);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aFunction89807);
    CALL(aFunction89492);
    CALL(aFunction894ca);

asm_8aa3a:
    CALL(aFunction8987f);
    CALL(aFunction89a2e);
    CALL(aFunction891ab);

asm_8aa43:
    CALL(aFunction89b97);
    CALL(aFunction89c67);
    IF_C goto asm_8aa61;
    LD_A_B;
    AND_A_A;
    IF_Z goto asm_8aa43;
    CALL(aPlayClickSFX);
    CALL(aFunction89448);
    LD_A_addr(wd011);
    DEC_A;
    LD_HL(mJumptable_8aa6d);
    RST(aJumpTable);
    IF_NC goto asm_8aa3a;
    goto asm_8aa69;

asm_8aa61:
    CALL(aFunction89448);
    CALL(aFunction8ab11);
    IF_NC goto asm_8aa3a;

asm_8aa69:
    CALL(aFunction89448);
    RET;

}

void Jumptable_8aa6d(void){
    //dw ['Function8aa73'];
    //dw ['Function8aab6'];
    //dw ['Function8ab11'];

    return Function8aa73();
}

void Function8aa73(void){
    LD_A_addr(wMenuSelection);
    LD_E_A;
    PUSH_DE;
    CALL(aFunction891de);
    LD_DE(wd008);
    LD_C(0x0);
    FARCALL(aFunction17a68f);
    IF_C goto asm_8aa9d;
    LD_HL(wd008);
    LD_A(0xff);
    LD_BC(0x8);
    CALL(aByteFill);
    LD_H_D;
    LD_L_E;
    LD_DE(wd008);
    LD_C(0x8);
    CALL(aFunction89193);

asm_8aa9d:
    CALL(aFunction891fe);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aFunction89807);
    CALL(aFunction89492);
    CALL(aFunction894ca);
    POP_DE;
    LD_A_E;
    LD_addr_A(wMenuSelection);
    AND_A_A;
    RET;

}

void Function8aab6(void){
    CALL(aFunction89a23);
    LD_HL(wd008);
    CALL(aFunction89b45);
    JR_NC (mFunction8ab00);
    CALL(aOpenSRAMBank4);
    LD_DE(wd008);
    LD_HL(0xa603);
    LD_C(0x8);
    CALL(aFunction89185);
    IF_Z goto asm_8aaeb;
    LD_HL(wd008);
    LD_DE(0xa603);
    LD_C(0x8);
    CALL(aFunction89193);
    hlcoord(1, 13, wTilemap);
    LD_DE(mString_8aaf0);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    CALL(aJoyWaitAorB);

asm_8aaeb:
    CALL(aCloseSRAM);
    SCF;
    RET;

}

void String_8aaf0(void){
    //db ['"あたらしい\u3000めいし<PKMN>できまし<LF>@"'];

    return Function8ab00();
}

void Function8ab00(void){
    LD_DE(mString_8911c);
    hlcoord(1, 13, wTilemap);
    CALL(aPlaceString);
    CALL(aWaitBGMap);
    CALL(aMobile22_PromptButton);
    AND_A_A;
    RET;

}

void Function8ab11(void){
    CALL(aOpenSRAMBank4);
    LD_HL(0xa603);
    LD_DE(wd008);
    LD_C(0x8);
    CALL(aFunction89185);
    CALL(aCloseSRAM);
    IF_Z goto asm_8ab37;
    CALL(aFunction89a23);
    hlcoord(1, 13, wTilemap);
    LD_DE(mString_89135);
    CALL(aPlaceString);
    LD_A(0x2);
    CALL(aFunction89254);
    IF_C goto asm_8ab39;

asm_8ab37:
    SCF;
    RET;

asm_8ab39:
    AND_A_A;
    RET;

}

void Function8ab3b(void){

pressed_start:
    CALL(aFunction891fe);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aFunction89807);
    CALL(aFunction89492);
    CALL(aFunction894ca);
    CALL(aOpenSRAMBank4);
    LD_HL(0xa603);
    LD_DE(wd008);
    CALL(aFunction89381);
    CALL(aCloseSRAM);
    CALL(aFunction8987f);
    CALL(aOpenSRAMBank4);
    hlcoord(1, 13, wTilemap);
    LD_BC(0xa007);
    CALL(aFunction89a0c);
    CALL(aCloseSRAM);
    CALL(aFunction891ab);
    CALL(aFunction8ab3b_JoypadLoop);
    IF_C goto pressed_start;
    RET;


JoypadLoop:
    CALL(aJoyTextDelay_ForcehJoyDown);
    BIT_C(A_BUTTON_F);
    IF_NZ goto a_b_button;
    BIT_C(B_BUTTON_F);
    IF_NZ goto a_b_button;
    BIT_C(START_F);
    IF_Z goto JoypadLoop;
    CALL(aPlayClickSFX);
    CALL(aFunction89d0d);
    SCF;
    RET;


a_b_button:
    CALL(aPlayClickSFX);
    AND_A_A;
    RET;

}

void Function8ab93(void){
    CALL(aClearBGPalettes);
    CALL(aLoadStandardMenuHeader);
    FARCALL(aDoNameCardSwap);
    CALL(aClearSprites);
    CALL(aFunction891fe);
    CALL(aFunction89b28);
    RET;

}

void Function8aba9(void){
    LD_A(0x2);
    CALL(aFunction8b94a);
    LD_A(0x1);
    LD_addr_A(wd032);

asm_8abb3:
    CALL(aFunction891fe);
    CALL(aFunction8b677);

asm_8abb9:
    CALL(aFunction8b7bd);
    IF_Z goto asm_8abdf;
    LD_A_C;
    LD_addr_A(wMenuSelection);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    LD_HL(0x0011);
    ADD_HL_BC;
    CALL(aFunction89b45);
    CALL(aCloseSRAM);
    IF_C goto asm_8abe2;
    LD_DE(SFX_WRONG);
    CALL(aWaitPlaySFX);
    CALL(aCloseSRAM);
    goto asm_8abb9;


asm_8abdf:
    XOR_A_A;
    LD_C_A;
    RET;


asm_8abe2:
    CALL(aPlayClickSFX);

asm_8abe5:
    CALL(aFunction891de);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    CALL(aFunction89844);
    CALL(aCloseSRAM);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8939a);
    CALL(aFunction89856);
    hlcoord(1, 13, wTilemap);
    CALL(aFunction899fe);
    CALL(aCloseSRAM);
    CALL(aFunction891ab);

asm_8ac0f:
    CALL(aFunction89a57);
    IF_C goto asm_8ac0f;
    AND_A_A;
    IF_Z goto asm_8abe5;
    CP_A(0x2);
    IF_Z goto asm_8ac0f;
    hlcoord(0, 12, wTilemap);
    LD_B(0x4);
    LD_C(0x12);
    CALL(aTextbox);
    hlcoord(1, 14, wTilemap);
    LD_DE(mString_8ac3b);
    CALL(aPlaceString);
    LD_A(0x1);
    CALL(aFunction8925e);
    JP_C (mFunction8aba9_asm_8abb3);
    LD_A_addr(wMenuSelection);
    LD_C_A;
    RET;

}

void String_8ac3b(void){
    //db ['"こ<NO>ともだち<NI>でんわを"'];
    //next ['"かけますか？@"']

    return Function8ac4e();
}

void Function8ac4e(void){
    // XOR_A_A;
    // LD_addr_A(wMenuSelection);
    wram->wMenuSelection = 0;
    PUSH_DE;
    CALL(aFunction891de);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    POP_BC;
    CALL(aFunction89844);
    CALL(aFunction8939a);
    CALL(aFunction89856);
    hlcoord(1, 13, wTilemap);
    CALL(aFunction899fe);
    CALL(aFunction891ab);
    RET;

}

void Function8ac70(void){
    PUSH_DE;
    LD_A(0x3);
    CALL(aFunction8b94a);

    return Function8ac76();
}

void Function8ac76(void){
    CALL(aFunction891fe);
    CALL(aFunction8b677);

    return Function8ac7c();
}

void Function8ac7c(void){
    CALL(aFunction8b7bd);
    IF_Z goto asm_8acf0;
    LD_A_C;
    LD_addr_A(wd02f);
    LD_addr_A(wMenuSelection);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    CALL(aFunction8932d);
    CALL(aCloseSRAM);
    IF_NC goto asm_8acb0;
    CALL(aOpenSRAMBank4);
    LD_HL(0x0011);
    ADD_HL_BC;
    CALL(aFunction89b45);
    CALL(aCloseSRAM);
    IF_NC goto asm_8accc;
    CALL(aOpenSRAMBank4);
    CALL(aFunction892b7);
    CALL(aCloseSRAM);
    goto asm_8accc;


asm_8acb0:
    CALL(aFunction8ad0b);
    JR_C (mFunction8ac76);
    AND_A_A;
    IF_NZ goto asm_8accc;
    CALL(aOpenSRAMBank4);
    LD_H_B;
    LD_L_C;
    LD_D(0x0);
    LD_E(0x6);
    ADD_HL_DE;
    LD_D_H;
    LD_E_L;
    POP_HL;
    LD_C(0x1f);
    CALL(aFunction89193);
    goto asm_8ace4;


asm_8accc:
    POP_HL;
    CALL(aOpenSRAMBank4);
    LD_D_B;
    LD_E_C;
    LD_C(0x6);
    CALL(aFunction89193);
    LD_A(0x6);
    ADD_A_E;
    LD_E_A;
    LD_A(0x0);
    ADC_A_D;
    LD_D_A;
    LD_C(0x1f);
    CALL(aFunction89193);


asm_8ace4:
    CALL(aCloseSRAM);
    CALL(aLoadStandardFont);
    LD_A_addr(wd02f);
    LD_C_A;
    AND_A_A;
    RET;


asm_8acf0:
    LD_HL(mMobileCardFolderFinishRegisteringCardsText);
    CALL(aPrintText);
    LD_A(0x2);
    CALL(aFunction89259);
    JP_C (mFunction8ac7c);
    CALL(aLoadStandardFont);
    POP_DE;
    LD_C(0x0);
    SCF;
    RET;

}

const txt_cmd_s MobileCardFolderFinishRegisteringCardsText[] = {
    text_far(v_MobileCardFolderFinishRegisteringCardsText)
    text_end
};

void Function8ad0b(void){

asm_8ad0b:
    LD_A_addr(wMenuSelection);
    LD_addr_A(wd02f);
    CALL(aFunction891de);
    CALL(aClearBGPalettes);
    CALL(aFunction893cc);
    CALL(aOpenSRAMBank4);
    CALL(aFunction8931b);
    PUSH_BC;
    CALL(aFunction89844);
    CALL(aFunction8939a);
    CALL(aFunction89856);
    hlcoord(1, 13, wTilemap);
    CALL(aFunction899fe);
    CALL(aCloseSRAM);
    CALL(aFunction891ab);
    POP_BC;

asm_8ad37:
    PUSH_BC;
    CALL(aFunction89a57);
    POP_BC;
    IF_C goto asm_8ad37;
    AND_A_A;
    IF_Z goto asm_8ad0b;
    CP_A(0x2);
    IF_Z goto asm_8ad37;
    CALL(aMobile22_SetBGMapMode0);
    PUSH_BC;
    hlcoord(0, 12, wTilemap);
    LD_B(0x4);
    LD_C(0x12);
    CALL(aTextbox);
    LD_DE(mString_8ad89);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    LD_A(0x2);
    CALL(aFunction8925e);
    IF_C goto asm_8ad87;
    CALL(aMobile22_SetBGMapMode0);
    hlcoord(0, 12, wTilemap);
    LD_B(0x4);
    LD_C(0x12);
    CALL(aTextbox);
    LD_DE(mString_8ad9c);
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    LD_A(0x1);
    CALL(aFunction8925e);
    IF_C goto asm_8ad84;
    LD_A(0x0);
    goto asm_8ad86;


asm_8ad84:
    LD_A(0x1);


asm_8ad86:
    AND_A_A;


asm_8ad87:
    POP_BC;
    RET;

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
    CloseSRAM_Conv();
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
