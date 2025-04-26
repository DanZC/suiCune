#include "../constants.h"
#include "fixed_words.h"
#include "../home/sram.h"
#include "../home/text.h"
#include "../home/copy.h"
#include "../home/names.h"
#include "../home/lcd.h"
#include "../home/tilemap.h"
#include "../home/clear_sprites.h"
#include "../home/joypad.h"
#include "../home/sprite_anims.h"
#include "../home/menu.h"
#include "../home/audio.h"
#include "../home/delay.h"
#include "../home/pokedex_flags.h"
#include "../home/math.h"
#include "../engine/gfx/dma_transfer.h"
#include "../engine/gfx/sprites.h"
#include "../engine/menus/save.h"
#include "../engine/pokedex/pokedex.h"
#include "../data/pokemon/ezchat_order.h"
#include "../charmap.h"

uint8_t gEZChatTextStringBuffer[32];
const txt_cmd_s EZChatTextBuffer[] = {
    text_ram(gEZChatTextStringBuffer)
    text_end
};

uint8_t* gEZChatSortedWordPointers[128];

#define EZCHAT_WORD_COUNT           EASY_CHAT_MESSAGE_WORD_COUNT
#define EZCHAT_WORD_LENGTH          8
#define EZCHAT_WORDS_PER_ROW        2
#define EZCHAT_WORDS_PER_COL        4
#define EZCHAT_WORDS_IN_MENU        EZCHAT_WORDS_PER_ROW * EZCHAT_WORDS_PER_COL
#define EZCHAT_CUSTOM_BOX_BIG_SIZE  9
#define EZCHAT_CUSTOM_BOX_BIG_START 4
#define EZCHAT_CUSTOM_BOX_START_X   5
#define EZCHAT_CUSTOM_BOX_START_Y   0x1B
#define EZCHAT_CHARS_PER_LINE       18
#define EZCHAT_BLANK_SIZE           5

enum {
	EZCHAT_SORTED_A,
	EZCHAT_SORTED_B,
	EZCHAT_SORTED_C,
	EZCHAT_SORTED_D,
	EZCHAT_SORTED_E,
	EZCHAT_SORTED_F,
	EZCHAT_SORTED_G,
	EZCHAT_SORTED_H,
	EZCHAT_SORTED_I,
	EZCHAT_SORTED_J,
	EZCHAT_SORTED_K,
	EZCHAT_SORTED_L,
	EZCHAT_SORTED_M,
	EZCHAT_SORTED_N,
	EZCHAT_SORTED_O,
	EZCHAT_SORTED_P,
	EZCHAT_SORTED_Q,
	EZCHAT_SORTED_R,
	EZCHAT_SORTED_S,
	EZCHAT_SORTED_T,
	EZCHAT_SORTED_U,
	EZCHAT_SORTED_V,
	EZCHAT_SORTED_W,
	EZCHAT_SORTED_X,
	EZCHAT_SORTED_Y,
	EZCHAT_SORTED_Z,
	EZCHAT_SORTED_ETC,
	EZCHAT_SORTED_ERASE,
	EZCHAT_SORTED_MODE,
	EZCHAT_SORTED_CANCEL,
    NUM_EZCHAT_SORTED,
};
#define EZCHAT_SORTED_NULL (0xff)

//  These functions seem to be related to the selection of preset phrases
//  for use in mobile communications.  Annoyingly, they separate the
//  Battle Tower function above from the data it references.

// EZChat_LoadOneWord
bool Function11c05d(struct TextPrintState* state, uint8_t d, uint8_t e){
    // LD_A_E;
    // OR_A_D;
    // IF_Z goto error;
    // LD_A_E;
    // AND_A_D;
    // CP_A(0xff);
    // IF_Z goto error;
    if((e | d) != 0 && (e & d) != 0xff) { // e and d aren't zero or 0xff.
        // PUSH_HL;
        // CALL(aCopyMobileEZChatToC608);
        state->de = CopyMobileEZChatToC608(d, e);
        // POP_HL;
        // CALL(aPlaceString);
        // AND_A_A;
        // RET;
        return false;
    }

// error:
    // LD_C_L;
    // LD_B_H;
    state->bc = state->hl;
    // SCF;
    // RET;
    return true;
}

void Function11c075(uint8_t* de, uint8_t c){
    // PUSH_DE;
    // LD_A_C;
    // CALL(aFunction11c254);
    Function11c254(c);
    // POP_DE;
    // LD_BC(wcd36);
    // CALL(aFunction11c08f);
    EZChat_RenderWords(de, wram->wEZChatWord);
    // RET;
}

void EZChat_RenderOneWord(struct TextPrintState* st, uint8_t d, uint8_t e) {
// hl = where to place it to
// d,e = params?
    // push hl
    tile_t* hl = st->hl;
    // call EZChat_LoadOneWord
    bool carry = Function11c05d(st, d, e);
    // pop hl
    st->hl = hl;
    // ld a, 0
    // ret c
    if(carry)
        return;
    // call PlaceString
    PlaceString_Conv(st, hl);
    // and a
    // ret
    return;
}

void Function11c082(void){
//  //  unreferenced
    PUSH_DE;
    LD_A_C;
    CALL(aFunction11c254);
    POP_DE;
    LD_BC(wcd36);
    CALL(aPrintEZChatBattleMessage);
    RET;

}

void Function11c08f(uint8_t* de, const uint8_t* bc){
    // LD_L_E;
    // LD_H_D;
    // PUSH_HL;
    uint8_t* hl = de;
    // LD_A(3);
    uint8_t a = 3;
    uint8_t* hl2 = hl;

    do {
    // loop:
        // PUSH_AF;
        // LD_A_bc;
        // LD_E_A;
        uint8_t e = *(bc++);
        // INC_BC;
        // LD_A_bc;
        // LD_D_A;
        // INC_BC;
        uint8_t d = *(bc++);
        // PUSH_BC;
        struct TextPrintState st = {.de = de, .hl = hl2};
        // CALL(aFunction11c05d);
        // IF_C goto okay;
        if(!Function11c05d(&st, d, e)) {
            // INC_BC;
            st.bc++;
        }

    // okay:
        // LD_L_C;
        // LD_H_B;
        hl2 = st.bc;
        // POP_BC;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);
    // POP_HL;
    // LD_DE(2 * SCREEN_WIDTH);
    // ADD_HL_DE;
    hl += 2 * SCREEN_WIDTH;
    // LD_A(0x3);
    a = 0x3;

    do {
    // loop2:
        // PUSH_AF;
        // LD_A_bc;
        // LD_E_A;
        uint8_t e = *(bc++);
        // INC_BC;
        // LD_A_bc;
        // LD_D_A;
        uint8_t d = *(bc++);
        // INC_BC;
        // PUSH_BC;
        struct TextPrintState st = {.de = de, .hl = hl};
        // CALL(aFunction11c05d);
        // IF_C goto okay2;
        if(!Function11c05d(&st, d, e)) {
            // INC_BC;
            st.bc++;
        }

    // okay2:
        // LD_L_C;
        // LD_H_B;
        hl = st.bc;
        // POP_BC;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop2;
    } while(--a != 0);
    // RET;
}

const u8_pair_s* EZChat_RenderLine(uint8_t* hl, const u8_pair_s* bc, uint8_t a) {
// .single_line
    struct TextPrintState st = {.hl = hl};
    // push hl
    do {
    // .loop
        // push af
        // ld a, [bc]
        // ld e, a
        uint8_t e = bc->a;
        // inc bc
        // ld a, [bc]
        // ld d, a
        uint8_t d = bc->b;
        // inc bc
        bc++;
        // push bc
        // call EZChat_RenderOneWord
        // jr c, .okay
        EZChat_RenderOneWord(&st, d, e);
        // inc bc
        st.bc++;

    // .okay
        // ld l, c
        // ld h, b
        st.hl = st.bc;
        // pop bc
        // pop af
        // dec a
        // jr nz, .loop
    } while(--a != 0);
    // pop hl
    // ret
    return bc;
}

void EZChat_RenderWords(uint8_t* de, const u8_pair_s* bc){
    // ld l, e
    // ld h, d
    // ld a, EZCHAT_WORDS_PER_ROW ; Determines the number of easy chat words displayed before going onto the next line
    // call .single_line
    bc = EZChat_RenderLine(de, bc, EZCHAT_WORDS_PER_ROW);
    // ld de, 2 * SCREEN_WIDTH
    // add hl, de
    // ld a, EZCHAT_WORDS_PER_ROW
    EZChat_RenderLine(de + 2 * SCREEN_WIDTH, bc, EZCHAT_WORDS_PER_ROW);
}

void PrintEZChatBattleMessage(tile_t* de, const uint8_t* bc){
//  Use up to 6 words from bc to print text starting at de.
// Preserve [wJumptableIndex], [wcf64]
    // LD_A_addr(wJumptableIndex);
    // LD_L_A;
    uint8_t l = wram->wJumptableIndex;
    // LD_A_addr(wcf64);
    // LD_H_A;
    uint8_t h = wram->wcf64;
    // PUSH_HL;
// reset value at [wc618] (not preserved)
    // LD_HL(wc618);
    // LD_A(0x0);
    // LD_hli_A;
    uint8_t* hl = gEZChatTextStringBuffer;
// preserve de
    // PUSH_DE;
// [wJumptableIndex] keeps track of which line we're on (0, 1, or 2)
// [wcf64] keeps track of how much room we have left in the current line
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // LD_A(18);
    // LD_addr_A(wcf64);
    wram->wcf64 = 18;
    // LD_A(6);
    uint8_t a = EASY_CHAT_MESSAGE_WORD_COUNT;

    do {
    // loop:
        // PUSH_AF;
    // load the 2-byte word data pointed to by bc
        // LD_A_bc;
        // LD_E_A;
        // INC_BC;
        // LD_A_bc;
        // LD_D_A;
        // INC_BC;
        const uint16_t de2 = (bc[0]) | (bc[1] << 8);
        bc += 2;
    // if $0000, we're done
        // OR_A_E;
        // IF_Z goto done;
        if(de2 == 0)
            continue;
    // preserving hl and bc, get the length of the word
        // PUSH_HL;
        // PUSH_BC;
        // CALL(aCopyMobileEZChatToC608);
        CopyMobileEZChatToC608(HIGH(de2), LOW(de2));
        // CALL(aGetLengthOfWordAtC608);
        // LD_E_C;
        uint8_t e = GetLengthOfWordAtC608();
        // POP_BC;
        // POP_HL;
    // if the functions return 0, we're done
        // LD_A_E;
        // OR_A_A;
        // IF_Z goto done;
        if(e == 0)
            continue;

        while(1) {
        // loop2:
        // e contains the length of the word
        // add 1 for the space, unless we're at the start of the line
            // LD_A_addr(wcf64);
            // CP_A(18);
            // IF_Z goto skip_inc;
            // INC_E;
            if(wram->wcf64 != 18) {
                e++;
            }

        // skip_inc:
        // if the word fits, put it on the same line
            // CP_A_E;
            // IF_NC goto same_line;
            if(wram->wcf64 >= e)
                break;
        // otherwise, go to the next line
            // LD_A_addr(wJumptableIndex);
            // INC_A;
            // LD_addr_A(wJumptableIndex);
            wram->wJumptableIndex++;
        // if we're on line 2, insert "<NEXT>"
            // LD_hl(0x4e);
            *hl = CHAR_NEXT;
            // RRA;
            // IF_C goto got_line_terminator;
            if((wram->wJumptableIndex & 1) == 0x0) {
            // else, insert "<CONT>"
                // LD_hl(0x55);
                *hl = CHAR_CONT;
            }

        // got_line_terminator:
            // INC_HL;
            hl++;
        // init the next line, holding on to the same word
            // LD_A(18);
            // LD_addr_A(wcf64);
            wram->wcf64 = 18;
            // DEC_E;
            --e;
            // goto loop2;
        }

    // same_line:
    // add the space, unless we're at the start of the line
        // CP_A(18);
        // IF_Z goto skip_space;
        if(a != 18) {
            // LD_hl(0x7f);
            // INC_HL;
            *(hl++) = CHAR_SPACE;
        }

    // skip_space:
    // deduct the length of the word
        // SUB_A_E;
        // LD_addr_A(wcf64);
        wram->wcf64 = a - e;
        // LD_DE(wc608);
        uint8_t* de3 = wram->wc608;

        while(*de3 != CHAR_TERM) {
        // place_string_loop:
        // load the string from de to hl
            // LD_A_de;
            // CP_A(0x50);
            // IF_Z goto done;
            // INC_DE;
            // LD_hli_A;
            *(hl++) = *(de3++);
            // goto place_string_loop;
        }

    // done:
    // next word?
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);
// we're finished, place "<DONE>"
    // LD_hl(0x57);
    *hl = CHAR_DONE;
// now, let's place the string from wc618 to bc
    // POP_BC;
    // LD_HL(wc618);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv2(de, EZChatTextBuffer);
// restore the original values of [wJumptableIndex] and [wcf64]
    // POP_HL;
    // LD_A_L;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = l;
    // LD_A_H;
    // LD_addr_A(wcf64);
    wram->wcf64 = h;
    // RET;
}

uint8_t GetLengthOfWordAtC608(void){
    // LD_C(0x0);
    uint8_t c = 0x0;
    // LD_HL(wc608);
    uint8_t* hl = wram->wc608;

    while(1) {
    // loop:
        // LD_A_hli;
        uint8_t a = *(hl++);
        // CP_A(0x50);
        // RET_Z ;
        if(a == CHAR_TERM)
            return c;
        // INC_C;
        c++;
        // goto loop;
    }
}

uint8_t* CopyMobileEZChatToC608(uint8_t d, uint8_t e){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x1);
    // LDH_addr_A(rSVBK);
    // LD_A(0x50);
    // LD_HL(wc608);
    // LD_BC(NAME_LENGTH);
    // CALL(aByteFill);
    ByteFill(wram->wc608, NAME_LENGTH, CHAR_TERM);
    // LD_A_D;
    // AND_A_A;
    // IF_Z goto get_name;
    uint8_t* hl;
    uint16_t bc;
    if(d == 0) {
    // get_name:
        // LD_A_E;
        // LD_addr_A(wNamedObjectIndex);
        // CALL(aGetPokemonName);
        GetPokemonName(e);
        // LD_HL(wStringBuffer1);
        hl = wram->wStringBuffer1;
        // LD_BC(MON_NAME_LENGTH - 1);
        bc = MON_NAME_LENGTH - 1;
        // goto copy_string;
    }
    else {
        // LD_HL(mMobileEZChatCategoryPointers);
        // DEC_D;
        // SLA_D;
        // LD_C_D;
        // LD_B(0x0);
        // ADD_HL_BC;
        // LD_A_hli;
        // LD_C_A;
        // LD_A_hl;
        // LD_B_A;
        // PUSH_BC;
        // POP_HL;
        // LD_C_E;
        // LD_B(0x0);
        // SLA_C;
        // RL_B;
        // SLA_C;
        // RL_B;
        // SLA_C;
        // RL_B;
        const char* word = MobileEZChatCategoryPointers[d - 1][e].word;
        // ADD_HL_BC;
        // LD_BC(NAME_LENGTH_JAPANESE - 1);
        ByteFill(wram->wStringBuffer1, NAME_LENGTH, CHAR_TERM);
        hl = U82CA(wram->wStringBuffer1, word);
        bc = NAME_LENGTH - 1;
    }

// copy_string:
    // LD_DE(wc608);
    // CALL(aCopyBytes);
    CopyBytes(&wram->wc608, hl, bc);
    // LD_DE(wc608);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
    return wram->wc608;
}

// EZChat_EditMenuSpecial
void Function11c1ab(void){
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // CALL(aFunction11c1b9);
    Function11c1b9();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // RET;
}

static void EZChat_EditMenu_InitKanaMode(void){
    // XOR_A_A;
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = 0x0;
    // LD_addr_A(wcf64);
    wram->wcf64 = 0x0;
    // LD_addr_A(wcf65);
    wram->wcf65 = 0x0;
    // LD_addr_A(wcf66);
    wram->wcf66 = 0x0;
    // LD_addr_A(wcd23);
    wram->wEZChatBlinkingMask = 0x0;
    // LD_addr_A(wcd20);
    wram->wEZChatSelection = 0x0;
    // LD_addr_A(wcd21);
    wram->wEZChatCategorySelection = 0x0;
    // LD_addr_A(wcd22);
    wram->wEZChatSortedSelection = 0x0;
    // LD_addr_A(wcd35);
    wram->wcd35 = 0x0;
    // LD_addr_A(wcd2b);
    wram->wEZChatCategoryMode = 0x0;
    // LD_A(0xff);
    // LD_addr_A(wcd24);
    wram->wEZChatSpritesMask = 0xff;
    // LD_A_addr(wMenuCursorY);
    // DEC_A;
    // CALL(aFunction11c254);
    Function11c254(wram->wMenuCursorY - 1);
    // CALL(aClearBGPalettes);
    ClearBGPalettes();
    // CALL(aClearSprites);
    ClearSprites();
    // CALL(aClearScreen);
    ClearScreen();
    // CALL(aFunction11d323);
    Function11d323();
    // CALL(aSetPalettes);
    SetPalettes();
    // CALL(aDisableLCD);
    DisableLCD();
    // LD_HL(mSelectStartGFX);
    // LD_DE(vTiles2);
    // LD_BC(0x60);
    // CALL(aCopyBytes);
    LoadPNG2bppAssetSectionToVRAM(vram->vTiles2, SelectStartGFX, 0, 0x60 / LEN_2BPP_TILE);
    // LD_HL(mEZChatSlowpokeLZ);
    // LD_DE(vTiles0);
    // CALL(aDecompress);
    LoadPNG2bppAssetToVRAM(vram->vTiles0, EZChatSlowpokeLZ);
    // CALL(aEnableLCD);
    EnableLCD();
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // FARCALL(aLoadPokemonData);
    LoadPokemonData();
    // FARCALL(aPokedex_ABCMode);
    Pokedex_ABCMode();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(wc6d0);
    // LD_DE(wLYOverrides);
    // LD_BC(0x100);
    // CALL(aCopyBytes);
    CopyBytes(wram->wLYOverrides, wram->wc6d0, 0x100);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // CALL(aEZChat_GetCategoryWordsByKana);
    EZChat_GetCategoryWordsByKana();
    // CALL(aEZChat_GetSeenPokemonByKana);
    EZChat_GetSeenPokemonByKana(); // TODO: Convert this function.
    // RET;
}

// EZChat_EditMenu
void Function11c1b9(void){
    // CALL(aFunction11c1b9_InitKanaMode);
    EZChat_EditMenu_InitKanaMode();
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // CALL(aEZChat_MasterLoop);
    EZChat_MasterLoop();
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void Function11c254(uint8_t a){
    // PUSH_AF;
    // LD_A(BANK(s4_a007));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(as4_a007));
    // LD_HL(s4_a007);
    uint8_t* hl = GBToRAMAddr(s4_a007);
    // POP_AF;
    // SLA_A;
    // SLA_A;
    // LD_C_A;
    // SLA_A;
    // ADD_A_C;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_DE(wcd36);
    // LD_BC(12);
    // CALL(aCopyBytes);
    CopyBytes(wram->wEZChatWord, hl + a*12, 12);
// If the word data is corrupted, just erase it so that it doesn't crash.
    for(uint32_t i = 0; i < EZCHAT_WORD_COUNT; ++i) {
        if(wram->wEZChatWord[i].b > 14 || wram->wEZChatWord[i].a >= MobileEZChatData_WordAndPageCounts[wram->wEZChatWord[i].b].a) {
            wram->wEZChatWord[i].b = 0;
            wram->wEZChatWord[i].a = 0;
        }
    }
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void EZChat_ClearBottom12Rows(void){
    // LD_A(0x7f);
    // hlcoord(0, 6, wTilemap);
    // LD_BC((SCREEN_HEIGHT - 6) * SCREEN_WIDTH);
    // CALL(aByteFill);
    ByteFill(coord(0, 6, wram->wTilemap), (SCREEN_HEIGHT - 6) * SCREEN_WIDTH, 0x7f);
    // RET;
}

enum {
    EZCHAT_SPAWN_OBJECTS, // 00
    EZCHAT_INIT_RAM, // 01
    EZCHAT_02, // 02
    EZCHAT_03, // 03
    EZCHAT_DRAW_CHAT_WORDS, // 04
    EZCHAT_MENU_CHAT_WORDS, // 05
    EZCHAT_DRAW_CATEGORY_MENU, // 06
    EZCHAT_MENU_CATEGORY_MENU, // 07
    EZCHAT_DRAW_WORD_SUBMENU, // 08
    EZCHAT_MENU_WORD_SUBMENU, // 09
    EZCHAT_DRAW_ERASE_SUBMENU, // 0a
    EZCHAT_MENU_ERASE_SUBMENU, // 0b
    EZCHAT_DRAW_EXIT_SUBMENU, // 0c
    EZCHAT_MENU_EXIT_SUBMENU, // 0d
    EZCHAT_DRAW_MESSAGE_TYPE_MENU, // 0e
    EZCHAT_MENU_MESSAGE_TYPE_MENU, // 0f
    EZCHAT_10, // 10 (Something related to sound)
    EZCHAT_MENU_WARN_EMPTY_MESSAGE, // 11 (Something related to SortBy menus)
    EZCHAT_12, // 12 (Something related to input)
    EZCHAT_DRAW_SORT_BY_MENU, // 13
    EZCHAT_MENU_SORT_BY_MENU, // 14
    EZCHAT_DRAW_SORT_BY_CHARACTER, // 15
    EZCHAT_MENU_SORT_BY_CHARACTER, // 16
};

static void EZChat_MasterLoop_DoJumptableFunction(void);

void EZChat_MasterLoop(void){

    while(1) {
    // loop:
        // CALL(aJoyTextDelay);
        JoyTextDelay();
        // LDH_A_addr(hJoyPressed);
        // LDH_addr_A(hJoypadPressed);
        hram->hJoypadPressed = hram->hJoyPressed;
        // LD_A_addr(wJumptableIndex);
        // BIT_A(7);
        // IF_NZ goto exit;
        if(bit_test(wram->wJumptableIndex, 7))
            break;
        // CALL(aEZChat_MasterLoop_DoJumptableFunction);
        EZChat_MasterLoop_DoJumptableFunction();
        // FARCALL(aPlaySpriteAnimations);
        PlaySpriteAnimations_Conv();
        // FARCALL(aReloadMapPart);
        ReloadMapPart_Conv();
        // goto loop;
    }

// exit:
    // FARCALL(aClearSpriteAnims);
    ClearSpriteAnims_Conv();
    // CALL(aClearSprites);
    ClearSprites();
    // RET;
    return;
}

static void EZChat_MasterLoop_DoJumptableFunction(void){
    //jumptable ['.Jumptable', 'wJumptableIndex']

    switch(wram->wJumptableIndex) {
    // Jumptable:
        case EZCHAT_SPAWN_OBJECTS: { //dw ['.SpawnObjects'];  // 00
        // SpawnObjects:
            // depixel4(3, 1, 2, 5);
            // LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
            // CALL(aInitSpriteAnimStruct);
            InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_EZCHAT_CURSOR, pixel4(3, 1, 2, 5));
            // depixel4(8, 1, 2, 5);

            // LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
            // CALL(aInitSpriteAnimStruct);
            struct SpriteAnim* bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_EZCHAT_CURSOR, pixel4(8, 1, 2, 5));
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A(0x1);
            // LD_hl_A;
            bc->var1 = 0x1;

            // depixel4(9, 2, 2, 0);
            // LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
            // CALL(aInitSpriteAnimStruct);
            bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_EZCHAT_CURSOR, pixel4(9, 2, 2, 0));
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A(0x3);
            // LD_hl_A;
            bc->var1 = 0x3;

            // depixel2(10, 16);
            // LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
            // CALL(aInitSpriteAnimStruct);
            bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_EZCHAT_CURSOR, pixel2(10, 16));
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A(0x4);
            // LD_hl_A;
            bc->var1 = 0x4;

            // depixel2(10, 4);
            // LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
            // CALL(aInitSpriteAnimStruct);
            bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_EZCHAT_CURSOR, pixel2(10, 4));
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A(0x5);
            // LD_hl_A;
            bc->var1 = 0x5;

            // depixel2(10, 2);
            // LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
            // CALL(aInitSpriteAnimStruct);
            bc = InitSpriteAnimStruct_Conv(SPRITE_ANIM_INDEX_EZCHAT_CURSOR, pixel2(10, 2));
            // LD_HL(SPRITEANIMSTRUCT_VAR1);
            // ADD_HL_BC;
            // LD_A(0x2);
            // LD_hl_A;
            bc->var1 = 0x2;

            // LD_HL(wcd23);
            // SET_hl(1);
            // SET_hl(2);
            wram->wEZChatBlinkingMask |= (1 << 1) | (1 << 2);
            // JP(mFunction11cfb5);
        } return Function11cfb5();
        case EZCHAT_INIT_RAM: { //dw ['.InitRAM'];  // 01
        // InitRAM:
            // LD_A(0x9);
            // LD_addr_A(wcd2d);
            wram->wcd2d = 0x9;
            // LD_A(0x2);
            // LD_addr_A(wcd2e);
            wram->wcd2e = 0x2;
            // LD_addr_A(wcd2f);
            wram->wcd2f = 0x2;
            // LD_addr_A(wcd30);
            wram->wcd30 = 0x2;
            // LD_DE(wcd2d);
            // CALL(aFunction11cfce);
            Function11cfce(&wram->wcd2d);
            // JP(mFunction11cfb5);
        } return Function11cfb5();
        case EZCHAT_02: return Function11c35f(); //dw ['Function11c35f'];  // 02
        case EZCHAT_03: return Function11c373(); //dw ['Function11c373'];  // 03
        case EZCHAT_DRAW_CHAT_WORDS: return Function11c3c2(); //dw ['Function11c3c2'];  // 04
        case EZCHAT_MENU_CHAT_WORDS: return Function11c3ed(); //dw ['Function11c3ed'];  // 05
        case EZCHAT_DRAW_CATEGORY_MENU: return Function11c52c(); //dw ['Function11c52c'];  // 06
        case EZCHAT_MENU_CATEGORY_MENU: return Function11c53d(); //dw ['Function11c53d'];  // 07
        case EZCHAT_DRAW_WORD_SUBMENU: return Function11c658(); //dw ['Function11c658'];  // 08
        case EZCHAT_MENU_WORD_SUBMENU: return Function11c675(); //dw ['Function11c675'];  // 09
        case EZCHAT_DRAW_ERASE_SUBMENU: return Function11c9bd(); //dw ['Function11c9bd'];  // 0a
        case EZCHAT_MENU_ERASE_SUBMENU: return Function11c9c3(); //dw ['Function11c9c3'];  // 0b
        case EZCHAT_DRAW_EXIT_SUBMENU: return Function11caad(); //dw ['Function11caad'];  // 0c
        case EZCHAT_MENU_EXIT_SUBMENU: return Function11cab3(); //dw ['Function11cab3'];  // 0d
        case EZCHAT_DRAW_MESSAGE_TYPE_MENU: return Function11cb52(); //dw ['Function11cb52'];  // 0e
        case EZCHAT_MENU_MESSAGE_TYPE_MENU: return Function11cb66(); //dw ['Function11cb66'];  // 0f
        case EZCHAT_10: return Function11cbf5(); //dw ['Function11cbf5'];  // 10
        case EZCHAT_MENU_WARN_EMPTY_MESSAGE: return Function11ccef(); //dw ['Function11ccef'];  // 11
        case EZCHAT_12: return Function11cd04(); //dw ['Function11cd04'];  // 12
        //dw ['Function11cd20'];  // 13
        //dw ['Function11cd54'];  // 14
        //dw ['Function11ce0b'];  // 15
        //dw ['Function11ce2b'];  // 16
    }
}

void Function11c35f(void){
    // LD_HL(wcd2f);
    // INC_hl;
    // INC_hl;
    wram->wcd2f += 2;
    // DEC_HL;
    // DEC_HL;
    // DEC_hl;
    uint8_t a = --wram->wcd2d;
    // PUSH_AF;
    // LD_DE(wcd2d);
    // CALL(aFunction11cfce);
    Function11cfce(&wram->wcd2d);
    // POP_AF;
    // RET_NZ ;
    if(a != 0)
        return;
    // JP(mFunction11cfb5);
    return Function11cfb5();
}

void Function11c373(void){
    // LD_HL(wcd30);
    // INC_hl;
    wram->wcd30 += 2;
    // INC_hl;
    // DEC_HL;
    // DEC_HL;
    // DEC_hl;
    uint8_t a = --wram->wcd2e;
    // PUSH_AF;
    // LD_DE(wcd2d);
    // CALL(aFunction11cfce);
    Function11cfce(&wram->wcd2d);
    // POP_AF;
    // RET_NZ ;
    if(a != 0)
        return;
    // CALL(aFunction11c38a);
    EZChatMenu_MessageSetup();
    // JP(mFunction11cfb5);
    return Function11cfb5();
}

void Function11c38a(void){
    // LD_HL(mUnknown_11c986);
    const uint16_t* hl = Unknown_11c986;
    // LD_BC(wcd36);
    uint8_t* bc = &wram->wcd36;
    // LD_A(0x6);
    uint8_t a = 0x6;

    do {
    // asm_11c392:
        // PUSH_AF;
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint8_t* de = (*(hl++)) + wram->wTilemap;
        // PUSH_HL;
        // PUSH_DE;
        // POP_HL;
        // LD_A_bc;
        // INC_BC;
        // LD_E_A;
        // LD_A_bc;
        // INC_BC;
        // LD_D_A;
        uint16_t de2 = bc[0] | (bc[1] << 8);
        bc += 2;
        // PUSH_BC;
        // OR_A_E;
        // IF_Z goto asm_11c3af;
        // LD_A_E;
        // AND_A_D;
        // CP_A(0xff);
        // IF_Z goto asm_11c3af;
        if(de2 != 0 && de2 != 0xffff) {
            struct TextPrintState st = {.hl = de, .bc = de};
            // CALL(aFunction11c05d);
            Function11c05d(&st, HIGH(de2), LOW(de2));
            // goto asm_11c3b5;
        }
        else {
        // asm_11c3af:
            // LD_DE(mString_11c3bc);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(String_11c3bc), de);
        }

    // asm_11c3b5:
        // POP_BC;
        // POP_HL;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_11c392;
    } while(--a != 0);
    // RET;
}

// EZChatString_EmptyWord
const char String_11c3bc[] = "-----@"; //db ['"ーーーーー@"'];

// ezchat main options
enum {
    EZCHAT_MAIN_WORD1,
    EZCHAT_MAIN_WORD2,
    EZCHAT_MAIN_WORD3,
    EZCHAT_MAIN_WORD4,
    // EZCHAT_MAIN_WORD5,
    // EZCHAT_MAIN_WORD6,
    
    EZCHAT_MAIN_RESET,
    EZCHAT_MAIN_QUIT,
    EZCHAT_MAIN_OK,
};

void EZChatMenu_MessageLocationSetup(tile_t* hl){
    // push de
    // push bc
    // ld bc, wMobileBoxSpritePositionDataTotal
    // ld a, [bc]
    // cp EZCHAT_WORDS_PER_ROW
    // decoord 0, 2
    // ld a, EZCHAT_CUSTOM_BOX_START_Y
    // jr c, .after_initial_setup
    tile_t* de;
    uint8_t a;
    if(wram->wMobileBoxSpritePositionDataTotal < EZCHAT_WORDS_PER_ROW) {
        de = coord(0, 2, wram->wTilemap);
        a = EZCHAT_CUSTOM_BOX_START_Y;
    }
    else {
        // decoord 0, 4
        de = coord(0, 4, wram->wTilemap);
        // add $0F
        a = EZCHAT_CUSTOM_BOX_START_Y + 0x0f;
    }
// .after_initial_setup
    // ld d, a
    uint8_t d = a;
    // ld a, l
    // sub e
    // sla a
    // sla a
    // sla a
    // add EZCHAT_CUSTOM_BOX_START_X
    // ld e, a
    uint8_t e = ((hl - de) * 8) + EZCHAT_CUSTOM_BOX_START_X;
    // ld a, [bc]
    // inc a
    // ld [bc], a
    wram->wMobileBoxSpritePositionDataTotal++;
    // dec a
    a = wram->wMobileBoxSpritePositionDataTotal - 1;
    // inc bc
    uint8_t* bc = wram->wMobileBoxSpritePositionData;
    // push hl
    // sla a
    // ld h, 0
    // ld l, a
    // add hl, bc
    // ld [hl], e
    bc[2*a + 0] = e;
    // inc hl
    // ld [hl], d
    bc[2*a + 1] = d;
    // pop hl
    // pop bc
    // pop de
    // ret
}

static u8_pair_s* EZChatMenu_MessageSetup_print_word_of_line(u8_pair_s* bc, tile_t* hl, uint8_t a) {
    // ld d, a
    uint8_t b = a;
    // ld a, [bc]
    // inc bc
    // push bc
    // ld e, a
    uint8_t e = bc->a;
    // ld a, [bc]
    // ld b, d
    // ld d, a
    uint8_t d = bc->b;
    // or e
    // jr z, .emptystring
    // ld a, e
    // and d
    // cp $ff
    // jr z, .emptystring
    if((d | e) == 0 || (d & e) == 0xff) {
    // .emptystring
        // ld de, EZChatString_EmptyWord
        uint8_t* de = U82C(String_11c3bc);
        // ld a, b
        // sub EZCHAT_CHARS_PER_LINE - EZCHAT_BLANK_SIZE
        // jr c, .after_shrink
        if(b >= EZCHAT_CHARS_PER_LINE - EZCHAT_BLANK_SIZE) {
            // add e
            // ld e, a
            // adc d
            // sub e
            // ld d, a
            de += (b - (EZCHAT_CHARS_PER_LINE - EZCHAT_BLANK_SIZE));
        }
    // .after_shrink
        // call EZChatMenu_MessageLocationSetup
        EZChatMenu_MessageLocationSetup(hl);
        // call PlaceString
        PlaceStringSimple(de, hl);
    }
    else {
        // call EZChatMenu_MessageLocationSetup
        EZChatMenu_MessageLocationSetup(hl);
        // call EZChat_RenderOneWord
        EZChat_RenderOneWord(&(struct TextPrintState){.hl = hl}, d, e);
        // jr .asm_11c3b5
    }
// .asm_11c3b5
    // pop bc
    // inc bc
    bc++;
    // ret
    return bc;
}

static u8_pair_s* EZChatMenu_MessageSetup_after_initial_setup(u8_pair_s* bc, tile_t* hl, uint8_t a){
    // push af
    // inc a
    // call EZChatMenu_GetRealChosenWordSize
    uint8_t size = EZChatMenu_GetRealChosenWordSize(a + 1);
    // push af
    // push hl
    // call .print_word_of_line
    bc = EZChatMenu_MessageSetup_print_word_of_line(bc, hl, size);
    // pop hl
    // pop de
    // pop af
    // call EZChatMenu_GetRealChosenWordSize
    uint8_t size2 = EZChatMenu_GetRealChosenWordSize(a);
    // sub EZCHAT_CHARS_PER_LINE - ((EZCHAT_CHARS_PER_LINE - 1) / 2)
    // ld e, EZCHAT_CHARS_PER_LINE - ((EZCHAT_CHARS_PER_LINE - 1) / 2) + 1
    // jr nc, .after_size_calcs
    uint8_t d = size, e;
    if(size2 < EZCHAT_CHARS_PER_LINE - ((EZCHAT_CHARS_PER_LINE - 1) / 2)) {
        // dec e
        e = EZCHAT_CHARS_PER_LINE - ((EZCHAT_CHARS_PER_LINE - 1) / 2);
        // ld a, d
        // cp ((EZCHAT_CHARS_PER_LINE - 1) / 2) + 1
        // jr c, .after_size_set
        if(size >= ((EZCHAT_CHARS_PER_LINE - 1) / 2) + 1) {
            // sub ((EZCHAT_CHARS_PER_LINE - 1) / 2)
            // ld d, a
            d = size - ((EZCHAT_CHARS_PER_LINE - 1) / 2);
            // ld a, e
            // sub d
            // jr .after_size_increase
            e -= d;
        }
    }
    else {
    // .after_size_calcs
        // add e
        e = (size2 - EZCHAT_CHARS_PER_LINE - ((EZCHAT_CHARS_PER_LINE - 1) / 2)) + (EZCHAT_CHARS_PER_LINE - ((EZCHAT_CHARS_PER_LINE - 1) / 2) + 1);
    }
// .after_size_increase
    // ld e, a
// .after_size_set
    // ld d, 0
    // add hl, de
    return EZChatMenu_MessageSetup_print_word_of_line(bc, hl + e, e);
}

void EZChatMenu_MessageSetup(void){
    // ld a, EZCHAT_MAIN_RESET
    // ld [wMobileBoxSpriteLoadedIndex], a
    wram->wMobileBoxSpriteLoadedIndex = EZCHAT_MAIN_RESET;
    // xor a
    // ld [wMobileBoxSpritePositionDataTotal], a
    wram->wMobileBoxSpritePositionDataTotal = 0x0;
    // hlcoord 1, 2
    // ld bc, wEZChatWords
    u8_pair_s* bc = wram->wEZChatWord;
    // call .after_initial_setup
    bc = EZChatMenu_MessageSetup_after_initial_setup(bc, coord(1, 2, wram->wTilemap), 0x0);
    // ld a, EZCHAT_WORDS_PER_ROW
    // hlcoord 1, 4
    EZChatMenu_MessageSetup_after_initial_setup(bc, coord(1, 4, wram->wTilemap), EZCHAT_WORDS_PER_ROW);
}

// EZChatDraw_ChatWords
void Function11c3c2(void){
    // CALL(aEZChat_ClearBottom12Rows);
    EZChat_ClearBottom12Rows();
    // LD_DE(mUnknown_11cfbe);
    // CALL(aFunction11d035);
    Function11d035(Unknown_11cfbe);
    // hlcoord(1, 7, wTilemap);
    // LD_DE(mString_11c4db);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11c4db), coord(1, 7, wram->wTilemap));
    // hlcoord(1, 16, wTilemap);
    // LD_DE(mString_11c51b);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11c51b), coord(1, 16, wram->wTilemap));
    // CALL(aFunction11c4be);
    Function11c4be();
    // LD_HL(wcd23);
    // SET_hl(0);
    // LD_HL(wcd24);
    // RES_hl(0);
    bit_reset(wram->wEZChatSpritesMask, 0);
    // CALL(aFunction11cfb5);
    Function11cfb5();

    return Function11c3ed();
}

// EZChatMenu_ChatWords
void Function11c3ed(void){
    // LD_HL(wcd20);
    uint8_t a;
    // LD_DE(hJoypadPressed);
    // LD_A_de;
    // AND_A(0x8);
    // IF_NZ goto asm_11c426;
    if(hram->hJoypadPressed & START) {
    // asm_11c426:
        // LD_A(0x8);
        // LD_addr_A(wcd20);
        wram->wEZChatSelection = EZCHAT_MAIN_OK;
        // RET;
        return;
    }
    // LD_A_de;
    // AND_A(0x2);
    // IF_NZ goto asm_11c41a;
    else if(hram->hJoypadPressed & B_BUTTON) {
    // asm_11c41a:
        // CALL(aPlayClickSFX);
        PlayClickSFX();

    asm_11c41d:
        // LD_HL(wcd24);
        // SET_hl(0);
        bit_set(wram->wEZChatSpritesMask, 0);
        // LD_A(0xc);
        a = EZCHAT_DRAW_EXIT_SUBMENU;
        // goto asm_11c475;
    }
    // LD_A_de;
    // AND_A(0x1);
    // IF_NZ goto asm_11c42c;
    else if(hram->hJoypadPressed & A_BUTTON) {
    // asm_11c42c:
        // LD_A_addr(wcd20);
        // CP_A(0x6);
        // IF_C goto asm_11c472;
        if(wram->wEZChatSelection < EZCHAT_MAIN_RESET) {
        // asm_11c472:
            // CALL(aFunction11c4a5);
            a = Function11c4a5();
            // goto asm_11c475;
        }
        // SUB_A(0x6);
        // IF_Z goto asm_11c469;
        else if(wram->wEZChatSelection == EZCHAT_MAIN_RESET) {
        // asm_11c469:
            // LD_HL(wcd24);
            // SET_hl(0);
            bit_set(wram->wcd24, 0);
            // LD_A(0xa);
            a = EZCHAT_DRAW_ERASE_SUBMENU;
            // goto asm_11c475;
        }
        // DEC_A;
        // IF_Z goto asm_11c41d;
        else if(wram->wEZChatSelection == EZCHAT_MAIN_QUIT)
            goto asm_11c41d;
        else {
            // LD_HL(wcd36);
            const uint8_t* hl = &wram->wcd36;
            // LD_C(0xc);
            uint8_t c = 12;
            // XOR_A_A;
            a = 0;
            do {
            // asm_11c440:
                // OR_A_hl;
                a |= *hl;
                // INC_HL;
                hl++;
                // DEC_C;
                // IF_NZ goto asm_11c440;
            } while(--c != 0);
            // AND_A_A;
            // IF_Z goto asm_11c460;
            if(a != 0) {
                // LD_DE(mUnknown_11cfba);
                // CALL(aFunction11cfce);
                Function11cfce(Unknown_11cfba);
                // decoord(1, 2, wTilemap);
                // LD_BC(wcd36);
                // CALL(aFunction11c08f);
                EZChat_RenderWords(coord(1, 2, wram->wTilemap), wram->wEZChatWord);
                // LD_HL(wcd24);
                // SET_hl(0);
                bit_set(wram->wEZChatSpritesMask, 0);
                // LD_A(0xe);
                a = EZCHAT_DRAW_MESSAGE_TYPE_MENU;
                // goto asm_11c475;
            }
            else {
            // asm_11c460:
                // LD_HL(wcd24);
                // SET_hl(0);
                bit_set(wram->wEZChatSpritesMask, 0);
                // LD_A(0x11);
                a = EZCHAT_MENU_WARN_EMPTY_MESSAGE;
                // goto asm_11c475;
            }
        }
    }
    // LD_DE(hJoyLast);
    // LD_A_de;
    // AND_A(0x40);
    // IF_NZ goto asm_11c47c;
    else if(hram->hJoyLast & D_UP) {
    // asm_11c47c:
        // LD_A_hl;
        // CP_A(0x3);
        // RET_C ;
        if(wram->wEZChatSelection < EZCHAT_MAIN_WORD3)
            return;
        // SUB_A(0x3);
        a = wram->wEZChatSelection - 2;
        // cp EZCHAT_MAIN_WORD4
        // jr nz, .keep_checking_up
        if(a == EZCHAT_MAIN_WORD4) {
            // dec a
            --a;
        }
    // .keep_checking_up
        // cp EZCHAT_MAIN_RESET
        // jr nz, .finish_dpad
        if(a == EZCHAT_MAIN_RESET) {
            // dec a
            --a;
        }
    // .finish_dpad
        // ld [hl], a
        wram->wEZChatSelection = a;
        // ret
        // goto asm_11c4a3;
        return;
    }
    // LD_A_de;
    // AND_A(0x80);
    // IF_NZ goto asm_11c484;
    else if(hram->hJoyLast & D_DOWN) {
    // asm_11c484:
        // LD_A_hl;
        // CP_A(0x6);
        // RET_NC ;
        if(wram->wEZChatSelection >= EZCHAT_MAIN_RESET)
            return;
        // ADD_A(0x3);
        // goto asm_11c4a3;
        wram->wEZChatSelection += 2;
        return;
    }
    // LD_A_de;
    // AND_A(0x20);
    // IF_NZ goto asm_11c48c;
    else if(hram->hJoyLast & D_LEFT) {
    // asm_11c48c:
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(wram->wEZChatSelection == EZCHAT_MAIN_WORD1)
            return;
        // CP_A(0x3);
        // RET_Z ;
        if(wram->wEZChatSelection == EZCHAT_MAIN_WORD3)
            return;
        // CP_A(0x6);
        // RET_Z ;
        if(wram->wEZChatSelection == EZCHAT_MAIN_RESET)
            return;
        // DEC_A;
        // goto asm_11c4a3;
        wram->wEZChatSelection--;
        return;
    }
    // LD_A_de;
    // AND_A(0x10);
    // IF_NZ goto asm_11c498;
    else if(hram->hJoyLast & D_RIGHT) {
    // asm_11c498:
        // LD_A_hl;
        // CP_A(0x2);
        // RET_Z ;
        if(wram->wEZChatSelection == EZCHAT_MAIN_WORD2)
            return;
        // CP_A(0x5);
        // RET_Z ;
        if(wram->wEZChatSelection == EZCHAT_MAIN_WORD4)
            return;
        // CP_A(0x8);
        // RET_Z ;
        if(wram->wEZChatSelection == EZCHAT_MAIN_OK)
            return;
        // INC_A;

    // asm_11c4a3:
        // LD_hl_A;
        wram->wEZChatSelection++;
        // RET;
        return;
    }
    else {
        // RET;
        return;
    }

// asm_11c475:
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = a;
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // RET;
    return;
}

void EZChat_CheckCategorySelectionConsistency(void) {
    // ld a, [wEZChatCategoryMode]
    // bit 7, a
    // ret z
    if(!bit_test(wram->wcd2b, 7))
        return;
    // set 0, a
    // ld [wEZChatCategoryMode], a
    bit_set(wram->wcd2b, 0);
    // ret
}

// EZChat_MoveToCategoryOrSortMenu
uint8_t Function11c4a5(void){
    EZChat_CheckCategorySelectionConsistency();
    // LD_HL(wcd23);
    // RES_hl(0);
    bit_reset(wram->wEZChatBlinkingMask, 0);
    // LD_A_addr(wcd2b);
    // AND_A_A;
    // IF_NZ goto asm_11c4b7;
    if(bit_test(wram->wEZChatCategoryMode, 0)) {
    // asm_11c4b7:
        // XOR_A_A;
        // LD_addr_A(wcd22);
        wram->wEZChatSortedSelection = 0x0;
        // LD_A(0x15);
        // RET;
        return EZCHAT_DRAW_SORT_BY_CHARACTER; // 0x15 
    }
    // XOR_A_A;
    // LD_addr_A(wcd21);
    wram->wEZChatCategorySelection = 0x0;
    // LD_A(0x6);
    // RET;
    return EZCHAT_DRAW_CATEGORY_MENU; // 0x6
}

// EZChatDrawBKG_ChatWords
void Function11c4be(void){
    // LD_A(0x1);
    // hlcoord(0, 6, wAttrmap);
    // LD_BC(0xa0);
    // CALL(aByteFill);
    ByteFill(coord(0, 6, wram->wAttrmap), 0xa0, 0x1);
    // LD_A(0x7);
    // hlcoord(0, 14, wAttrmap);
    // LD_BC(0x28);
    // CALL(aByteFill);
    ByteFill(coord(0, 14, wram->wAttrmap), 0x28, 0x7);
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // RET;
}

// EZChatString_ChatExplanation
const char String_11c4db[] = 
            "Combine four words"    // "６つのことば¯くみあわせます"
    t_next  "or phrases."           // "かえたいところ¯えらぶと\u3000でてくる"
    t_next  "Select a place"        // "ことばのグループから\u3000いれかえたい"
    t_next  "and choose a word.@";  // "たんご¯えらんでください@"

const char String_11c51b[] = "RESET QUIT   OK@"; // "ぜんぶけす\u3000やめる\u3000\u3000\u3000けってい@"


// ezchat categories defines
#define EZCHAT_CATEGORIES_ROWS      5
#define EZCHAT_CATEGORIES_COLUMNS   2
#define EZCHAT_DISPLAYED_CATEGORIES (EZCHAT_CATEGORIES_ROWS * EZCHAT_CATEGORIES_COLUMNS)
#define EZCHAT_NUM_CATEGORIES       15
#define EZCHAT_NUM_EXTRA_ROWS       ((EZCHAT_NUM_CATEGORIES + 1 - EZCHAT_DISPLAYED_CATEGORIES) / 2)
#define EZCHAT_EMPTY_VALUE          ((EZCHAT_NUM_EXTRA_ROWS << 5) | (EZCHAT_DISPLAYED_CATEGORIES - 1))

enum {
	EZCHAT_CATEGORY_CANC = EZCHAT_DISPLAYED_CATEGORIES,
	EZCHAT_CATEGORY_MODE,
	EZCHAT_CATEGORY_OK,
};

// EZChatDraw_CategoryMenu
void Function11c52c(void){
    // CALL(aEZChat_ClearBottom12Rows);
    EZChat_ClearBottom12Rows();
    // CALL(aEZChat_PlaceCategoryNames);
    EZChat_PlaceCategoryNames();
    // CALL(aFunction11c618);
    Function11c618();
    // LD_HL(wcd24);
    // RES_hl(1);
    bit_reset(wram->wcd24, 1);
    // CALL(aFunction11cfb5);
    Function11cfb5();

    return Function11c53d();
}

// EZChatMenu_CategoryMenu
void Function11c53d(void){
    // LD_HL(wcd21);
    uint8_t* hl = &wram->wEZChatCategorySelection;
    uint8_t a;
    // LD_DE(hJoypadPressed);

    // LD_A_de;
    // AND_A(START);
    // IF_NZ goto start;
    if(hram->hJoypadPressed & START) {
    // start:
        // LD_HL(wcd24);
        // SET_hl(0);
        bit_set(wram->wcd24, 0);
        // LD_A(0x8);
        // LD_addr_A(wcd20);
        wram->wcd20 = EZCHAT_MAIN_OK;
        goto b;
    }

    // LD_A_de;
    // AND_A(SELECT);
    // IF_NZ goto select;
    else if(hram->hJoypadPressed & SELECT) {
    // select:
        // LD_A_addr(wcd2b);
        // XOR_A(0x1);
        // LD_addr_A(wcd2b);
        wram->wcd2b ^= (1 << 0) | (1 << 7);
        // LD_A(0x15);
        a = EZCHAT_DRAW_SORT_BY_CHARACTER;
        // goto go_to_function;
    }

    // LD_A_de;
    // AND_A(B_BUTTON);
    // IF_NZ goto b;
    else if(hram->hJoypadPressed & B_BUTTON) {
    b:
        // LD_A(0x4);
        a = EZCHAT_DRAW_CHAT_WORDS;
        // goto go_to_function;
    }

    // LD_A_de;
    // AND_A(A_BUTTON);
    // IF_NZ goto a;
    else if(hram->hJoypadPressed & A_BUTTON) {
    // a:
        // LD_A_addr(wcd21);
        // CP_A(15);
        // IF_C goto got_category;
        if(wram->wEZChatCategorySelection < EZCHAT_CATEGORY_CANC) {
        // got_category:
            // LD_A(0x8);
            a = EZCHAT_DRAW_WORD_SUBMENU;
            // goto go_to_function;
        }
        // SUB_A(0xf);
        // IF_Z goto done;
        else if(wram->wEZChatCategorySelection == EZCHAT_CATEGORY_CANC) {
        // done:
            // LD_A_addr(wcd20);
            // CALL(aFunction11ca6a);
            Function11ca6a(wram->wEZChatSelection);
            EZChatMenu_RerenderMessage();
            // CALL(aPlayClickSFX);
            PlayClickSFX();
            // RET;
            return;
        }
        // DEC_A;
        // IF_Z goto mode;
        else if(wram->wEZChatCategorySelection == EZCHAT_CATEGORY_MODE) {
        // mode:
            // LD_A(0x13);
            a = EZCHAT_DRAW_SORT_BY_MENU;
            // goto go_to_function;
        }
        else {
            goto b;
        }
    }

    // LD_DE(hJoyLast);

    // LD_A_de;
    // AND_A(D_UP);
    // IF_NZ goto up;
    else if(hram->hJoyLast & D_UP) {
    // up:
        // LD_A_hl;
        // CP_A(0x3);
        // RET_C ;
        if(*hl < EZCHAT_CATEGORIES_COLUMNS)
            return;
        // SUB_A(0x3);
        // ld e, a
        uint8_t e = *hl & 0xf;
        // and $f0
        // ld d, a
        uint8_t d = *hl & 0xf0;
        // ld a, e
        // and $0f
        // cp EZCHAT_CATEGORIES_COLUMNS
        // jr nc, .normal_up
        if(e >= EZCHAT_CATEGORIES_COLUMNS) {
        // .normal_up
            // ld a, e
            // and $0f
            a = e;
            // cp EZCHAT_CATEGORY_MODE
            // jr c, .continue_normal_up
            if(a > EZCHAT_CATEGORY_CANC) {
                // ld a, EZCHAT_CATEGORY_CANC
                a = EZCHAT_CATEGORY_CANC;
            }
        // .continue_normal_up
            // sub EZCHAT_CATEGORIES_COLUMNS
            a -= EZCHAT_CATEGORIES_COLUMNS;
        // .up_end
            // or d
            // jr .finish_dpad
            a |= d;
            // goto finish_dpad;
            *hl = a;
            return;
        }
        // ld a, e
        // sub EZCHAT_CATEGORIES_COLUMNS << 4
        // ld [hl], a
        *hl -= (EZCHAT_CATEGORIES_COLUMNS << 4);
        // ld a, EZCHAT_DRAW_CATEGORY_MENU
        a = EZCHAT_DRAW_CATEGORY_MENU;
        // jr .go_to_function
        // goto go_to_function;
        // goto finish_dpad;
    }

    // LD_A_de;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(hram->hJoyLast & D_DOWN) {
    // down:
        // LD_A_hl;
        // CP_A(0xf);
        // RET_NC ;
        // ADD_A(0x3);
    // .down
        // ld a, [hl]
        a = *hl;
        // cp EZCHAT_EMPTY_VALUE - EZCHAT_CATEGORIES_COLUMNS
        // jr nz, .continue_down
        if(a == EZCHAT_EMPTY_VALUE - EZCHAT_CATEGORIES_COLUMNS) {
            // dec a
            --a;
        }
    // .continue_down
        // ld e, a
        uint8_t e = a & 0x0f;
        // and $f0
        // ld d, a
        uint8_t d = a & 0xf0;
        // ld a, e
        // and $0f
        // cp EZCHAT_CATEGORY_CANC
        // ret nc
        if(e >= EZCHAT_CATEGORY_CANC)
            return;
        // cp EZCHAT_DISPLAYED_CATEGORIES - EZCHAT_CATEGORIES_COLUMNS
        // jr c, .normal_down
        if(e < EZCHAT_DISPLAYED_CATEGORIES - EZCHAT_CATEGORIES_COLUMNS) {
        // .normal_down
            // add EZCHAT_CATEGORIES_COLUMNS
        // .down_end
            // or d
            *hl = (e + EZCHAT_CATEGORIES_COLUMNS) | d;
            // jr .finish_dpad
            return;
        }
        // ld a, d
        // cp EZCHAT_NUM_EXTRA_ROWS << 5
        // jr nz, .print_down
        if(d == EZCHAT_NUM_EXTRA_ROWS << 5) {
            // ld a, EZCHAT_CATEGORY_CANC
            // jr .down_end
            *hl = EZCHAT_CATEGORY_CANC | d;
            // goto finish_dpad;
            return;
        }
    // .print_down
        // ld a, e
        // add EZCHAT_CATEGORIES_COLUMNS << 4
        a = e + (EZCHAT_CATEGORIES_COLUMNS << 4);
        // cp EZCHAT_EMPTY_VALUE
        // jr nz, .continue_print_down
        if(a == EZCHAT_EMPTY_VALUE) {
            // dec a
            --a;
        }
    // .continue_print_down
        // ld [hl], a
        *hl = a;
        // ld a, EZCHAT_DRAW_CATEGORY_MENU
        a = EZCHAT_DRAW_CATEGORY_MENU;
        // jr .go_to_function
        // goto go_to_function;
    }

    // LD_A_de;
    // AND_A(D_LEFT);
    // IF_NZ goto left;
    else if(hram->hJoyLast & D_LEFT) {
    // .left
        // ld a, [hl]
        a = *hl;
        // and $0f
        // cp EZCHAT_CATEGORY_OK
        // jr z, .left_okay
        // bit 0, a
        // ret z
        if((a & 0xf) != 0 && !bit_test(a, 0))
            return;
    // .left_okay
        // ld a, [hl]
        // dec a
        (*hl)--;
        // jr .finish_dpad
        return;
    }

    // LD_A_de;
    // AND_A(D_RIGHT);
    // IF_NZ goto right;
    else if(hram->hJoyLast & D_RIGHT) {
    // .right
        // ld a, [hl]
        a = *hl;
        // cp EZCHAT_EMPTY_VALUE - 1
        // ret z
        if(a == EZCHAT_EMPTY_VALUE - 1)
            return;
        // and $0f
        a &= 0xf;
        // cp EZCHAT_CATEGORY_MODE
        // jr z, .right_okay
        // bit 0, a
        // ret nz
        // cp EZCHAT_CATEGORY_OK
        // ret z
        if(a != EZCHAT_CATEGORY_MODE && (bit_test(a, 0) || a == EZCHAT_CATEGORY_OK))
            return;
    // .right_okay
        // ld a, [hl]
        // inc a
        (*hl)++;
        return;
    }
    else {
        // RET;
        return;
    }

// go_to_function:
    // LD_HL(wcd24);
    // SET_hl(1);
    bit_set(wram->wcd24, 1);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = a;
    // CALL(aPlayClickSFX);
    PlayClickSFX();
    // RET;
    return;

// left:
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    // CP_A(0x3);
    // RET_Z ;
    // CP_A(0x6);
    // RET_Z ;
    // CP_A(0x9);
    // RET_Z ;
    // CP_A(0xc);
    // RET_Z ;
    // CP_A(0xf);
    // RET_Z ;
    // DEC_A;
    // goto finish_dpad;


// right:
    // LD_A_hl;
    // CP_A(0x2);
    // RET_Z ;
    // CP_A(0x5);
    // RET_Z ;
    // CP_A(0x8);
    // RET_Z ;
    // CP_A(0xb);
    // RET_Z ;
    // CP_A(0xe);
    // RET_Z ;
    // CP_A(0x11);
    // RET_Z ;
    // INC_A;


// finish_dpad:
    // LD_hl_A;
    // RET;
}

void EZChat_PlaceCategoryNames(void){
    // LD_DE(mMobileEZChatCategoryNames);
    const char* const* de = MobileEZChatCategoryNames + ((wram->wEZChatCategorySelection >> 4) & 0xf);
    // LD_BC(mCoords_11c63a);
    // LD_A(15);
    uint8_t a = 5;
    tile_t* hl = coord(1, 7, wram->wTilemap);

    do {
    // loop:
        // PUSH_AF;
        // LD_A_bc;
        // INC_BC;
        // LD_L_A;
        // LD_A_bc;
        // INC_BC;
        // LD_H_A;
        // PUSH_BC;
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(*de), hl);
        hl += SCREEN_WIDTH - 10;
        de++;
        PlaceStringSimple(U82C(*de), hl);
        hl += SCREEN_WIDTH + 10;
    // The category names are padded with "@".
    // To find the next category, the system must
    // find the first character at de that is not "@".

    // find_next_string_loop:
        // INC_DE;
        // LD_A_de;
        // CP_A(0x50);
        // IF_Z goto find_next_string_loop;
        de++;
        // POP_BC;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop;
    } while(--a != 0);
    // hlcoord(1, 17, wTilemap);
    // LD_DE(mEZChatString_Stop_Mode_Cancel);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(EZChatString_Stop_Mode_Cancel), coord(1, 17, wram->wTilemap));
    // RET;
}

// EZChat_SortMenuBackground
void Function11c618(void){
    // LD_A(0x2);
    // hlcoord(0, 6, wAttrmap);
    // LD_BC(0xc8);
    // CALL(aByteFill);
    ByteFill(coord(0, 6, wram->wAttrmap), 0xc8, 0x2);
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // RET;
}

const char EZChatString_Stop_Mode_Cancel[] = " DEL  MODE  QUIT@"; // "けす\u3000\u3000\u3000\u3000モード\u3000\u3000\u3000やめる@";

const uint16_t Coords_11c63a[] = {
    coord( 1,  7, 0),
    coord( 7,  7, 0),
    coord(13,  7, 0),
    coord( 1,  9, 0),
    coord( 7,  9, 0),
    coord(13,  9, 0),
    coord( 1, 11, 0),
    coord( 7, 11, 0),
    coord(13, 11, 0),
    coord( 1, 13, 0),
    coord( 7, 13, 0),
    coord(13, 13, 0),
    coord( 1, 15, 0),
    coord( 7, 15, 0),
    coord(13, 15, 0),
};

// EZChatDraw_WordSubmenu
void Function11c658(void){
    // CALL(aEZChat_ClearBottom12Rows);
    EZChat_ClearBottom12Rows();
    // CALL(aFunction11c770);
    EZChat_DetermineWordCounts();
    // LD_DE(mUnknown_11cfc2);
    // CALL(aFunction11d035);
    Function11d035(Unknown_11cfc2);
    // CALL(aFunction11c9ab);
    Function11c9ab();
    // CALL(aFunction11c7bc);
    EZChat_RenderWordChoices();
    // CALL(aFunction11c86e);
    Function11c86e();
    // LD_HL(wcd24);
    // RES_hl(3);
    bit_reset(wram->wEZChatSpritesMask, 3);

    wram->wEZChatScrollBufferIndex = 0;
    wram->wEZChatScrollBufferUsed = 0;
    wram->wEZChatScrollBuffer[0] = 0;

    // CALL(aFunction11cfb5);
    Function11cfb5();

    return Function11c675();
}

static bool Function11c675_move_menu_up_by_one(void) {
    // ld a, [wEZChatPageOffset]
    // and a
    // ret z
    if(wram->wEZChatPageOffset == 0)
        return false;
    // ld hl, wEZChatScrollBufferIndex
    // ld a, [hl]
    // and a
    // ret z
    if(wram->wEZChatScrollBufferIndex == 0)
        return false;
    // dec a
    uint8_t l = --wram->wEZChatScrollBufferIndex;
    // ld [hli], a
    wram->wEZChatScrollBufferIndex =  l;
    // inc hl
    // add l
    // ld l, a
    // adc h
    // sub l
    // ld h, a
    // ld a, [hl]
    // ld [wEZChatPageOffset], a
    wram->wEZChatPageOffset = wram->wEZChatScrollBuffer[l];
    // scf
    // ret
    return true;
}

static bool Function11c675_force_menu_down_by_one(void){
// .force_menu_down_by_one
    // ld hl, wEZChatScrollBufferIndex
    // ld a, [hli]
    uint8_t index = wram->wEZChatScrollBufferIndex;
    // cp [hl]
    // jr nc, .not_found_previous_value
    if(index >= wram->wEZChatScrollBufferUsed) {
    // .not_found_previous_value
        // ld a, 1
        // call EZChatGetValidWordsLine
        u8_pair_flag_s res = EZChatGetValidWordsLine(1);
        // ld a, d
        // ld [wEZChatPageOffset], a
        wram->wEZChatPageOffset = res.a;
        // ld hl, wEZChatScrollBufferIndex
        // ld a, [hl]
        // inc a
        // jr z, .after_scroll_buffer_setup
        if(wram->wEZChatScrollBufferIndex + 1 == 0)
            return true;
        // ld [hli], a
        uint8_t a = ++wram->wEZChatScrollBufferIndex;
        // cp [hl]
        // jr c, .after_scroll_max_increase
        if(a >= wram->wEZChatScrollBufferUsed) {
            // ld [hl], a
            wram->wEZChatScrollBufferUsed = a;
        }
    // .after_scroll_max_increase
        // inc hl
        // add l
        // ld l, a
        // adc h
        // sub l
        // ld h, a
        // ld [hl], d
        wram->wEZChatScrollBuffer[a] = res.a;
    // .after_scroll_buffer_setup
        // scf
        // ret
        return true;
    }
    // dec hl
    // inc a
    // ld [hli], a
    wram->wEZChatScrollBufferIndex = ++index;
    // inc hl
    // add l
    // ld l, a
    // adc h
    // sub l
    // ld h, a
    // ld a, [hl]
    // ld [wEZChatPageOffset], a
    wram->wEZChatPageOffset = wram->wEZChatScrollBuffer[index];
    // jr .after_scroll_buffer_setup
    return true;
}

static bool Function11c675_move_menu_down_by_one(void){
    // ld a, EZCHAT_WORDS_PER_COL
    // call EZChatGetValidWordsLine
    u8_pair_flag_s res = EZChatGetValidWordsLine(EZCHAT_WORDS_PER_COL);
    // ret nc
    if(!res.flag)
        return false;
    // ld a, d
    // ld hl, wEZChatLoadedItems
    // cp [hl]
    // ret nc
    if(res.a >= wram->wEZChatLoadedItems[0])
        return false;

    return Function11c675_force_menu_down_by_one();
}

// EZChatMenu_WordSubmenu
void Function11c675(void){
    uint8_t a;
    // LD_HL(wMobileCommsJumptableIndex);
    // LD_DE(hJoypadPressed);
    // LD_A_de;
    // AND_A(A_BUTTON);
    // IF_NZ goto a;
    if(hram->hJoypadPressed & A_BUTTON) {
    // a:
        // call EZChat_SetOneWord
        // jr nc, .failure_to_set
        if(!EZChat_SetOneWord()) {
        // .failure_to_set
            // ld de, SFX_WRONG
            // call PlaySFX
            PlaySFX(SFX_WRONG);
            // jp WaitSFX
            return WaitSFX();
        }
        // call EZChat_VerifyWordPlacement
        // call EZChatMenu_RerenderMessage
        EZChatMenu_RerenderMessage();
        // ld a, EZCHAT_DRAW_CHAT_WORDS
        // ld [wcd35], a
        wram->wcd35 = EZCHAT_DRAW_CHAT_WORDS;

    // autoselect "OK" if all words filled
    // not when only word #4 is filled
        // push af
        // ld hl, wEZChatWords
        u8_pair_s* hl = wram->wEZChatWord;
        // ld c, EZCHAT_WORD_COUNT
        uint8_t c = EZCHAT_WORD_COUNT;
        do {
        // .check_word
            // ld b, [hl]
            // inc hl
            // ld a, [hli]
            // or b
            // jr z, .check_done
            if((hl->a | hl->b) == 0)
                goto check_done;
            // dec c
            // jr nz, .check_word
        } while(hl++, --c != 0);
        // ld a, $6 ; OK
        // ld [wEZChatSelection], a
        wram->wEZChatSelection = 0x6;
    check_done:
        // pop af
        wram->wJumptableIndex = EZCHAT_DRAW_CHAT_WORDS;
        // jr .jump_to_index
        goto jump_to_index;
    }
    // LD_A_de;
    // AND_A(B_BUTTON);
    // IF_NZ goto b;
    if(hram->hJoypadPressed & B_BUTTON) {
    // b:
        // call EZChat_CheckCategorySelectionConsistency
        EZChat_CheckCategorySelectionConsistency();
        // ld a, [wEZChatCategoryMode]
        // bit 0, a
        // jr nz, .to_sorted_menu
        if(bit_test(wram->wEZChatCategoryMode, 0)) {
        // .to_sorted_menu
            // ld a, EZCHAT_DRAW_SORT_BY_CHARACTER
            wram->wJumptableIndex = EZCHAT_DRAW_SORT_BY_CHARACTER;
        }
        else {
            // ld a, EZCHAT_DRAW_CATEGORY_MENU
            // jr .jump_to_index
            wram->wJumptableIndex = EZCHAT_DRAW_CATEGORY_MENU;
        }
    
    jump_to_index:
        // ld [wJumptableIndex], a
        // ld hl, wEZChatSpritesMask
        // set 3, [hl]
        bit_set(wram->wEZChatSpritesMask, 3);
        // call PlayClickSFX
        PlayClickSFX();
        // ret
        return;
    }
    // LD_A_de;
    // AND_A(START);
    // IF_NZ goto start;
    if(hram->hJoypadPressed & START) {
    // start:
        // LD_HL(wcd28);
        // LD_A_addr(wcd26);
        // ADD_A(0xc);
        // CP_A_hl;
        // RET_NC ;
        // LD_addr_A(wcd26);
        // LD_A_hl;
        // LD_B_A;
        // LD_HL(wMobileCommsJumptableIndex);
        // LD_A_addr(wcd26);
        // ADD_A_hl;
        // IF_C goto asm_11c6b9;
        // CP_A_B;
        // IF_C goto asm_11c6c4;

    // .next_page
        // ld a, EZCHAT_WORDS_PER_COL
        // call EZChatGetValidWordsLine
        u8_pair_flag_s res = EZChatGetValidWordsLine(EZCHAT_WORDS_PER_COL);
        // ret nc
        if(!res.flag)
            return;
        // ld a, d
        // ld hl, wEZChatLoadedItems
        // cp [hl]
        // ret nc
        if(res.a >= wram->wEZChatLoadedItems[0])
            return;
        // ld e, EZCHAT_WORDS_PER_COL
        uint8_t e = EZCHAT_WORDS_PER_COL;
        do {
        // .start_loop
            // push de
            // call .force_menu_down_by_one
            Function11c675_force_menu_down_by_one();
            // pop de
            // dec e
            // jr nz, .start_loop
        } while(--e != 0);
        goto navigate_to_page;

    // asm_11c6b9:
        // LD_A_addr(wcd28);
        // LD_HL(wcd26);
        // SUB_A_hl;
        // DEC_A;
        // LD_addr_A(wMobileCommsJumptableIndex);
    }
    // LD_A_de;
    // AND_A(SELECT);
    // IF_Z goto select;
    if((hram->hJoypadPressed & SELECT) == 0) {
    // select:
        // LD_DE(hJoyLast);
        // LD_A_de;
        // AND_A(D_UP);
        // IF_NZ goto asm_11c708;
        if(hram->hJoyLast & D_UP) {
        // up:
            // ld a, [hl]
            // sub EZCHAT_WORDS_PER_ROW
            // jr nc, .finish_dpad
            if(wram->wEZChatWordSelection < EZCHAT_WORDS_PER_ROW) {
                // call .move_menu_up_by_one
                // ret nc
                if(!Function11c675_move_menu_up_by_one())
                    return;
                // jp .navigate_to_page
                goto navigate_to_page;
            }
            a = wram->wEZChatWordSelection - EZCHAT_WORDS_PER_ROW;
        }
        // LD_A_de;
        // AND_A(D_DOWN);
        // IF_NZ goto asm_11c731;
        else if(hram->hJoyLast & D_DOWN) {
            // ld a, [hl]
            // add EZCHAT_WORDS_PER_ROW
            // cp EZCHAT_WORDS_IN_MENU
            // jr c, .finish_dpad
            if(wram->wEZChatWordSelection + EZCHAT_WORDS_PER_ROW >= EZCHAT_WORDS_IN_MENU) {
                // call .move_menu_down_by_one
                // ret nc
                if(!Function11c675_move_menu_down_by_one())
                    return;
                // jp .navigate_to_page
                goto navigate_to_page;
            }
            a = wram->wEZChatWordSelection + EZCHAT_WORDS_PER_ROW;
        }
        // LD_A_de;
        // AND_A(D_LEFT);
        // IF_NZ goto asm_11c746;
        else if(hram->hJoyLast & D_LEFT) {
        // .left
            // ld a, [hl]
            // and a ; cp a, 0
            // ret z
            if(wram->wEZChatWordSelection == 0)
                return;
            // and 1
            // ret z
            if((wram->wEZChatWordSelection & 1) == 0)
                return;
            // ld a, [hl]
            // dec a
            a = wram->wEZChatWordSelection - 1;
            // jr .finish_dpad
        }
        // LD_A_de;
        // AND_A(D_RIGHT);
        // IF_NZ goto asm_11c755;
        else if(hram->hJoyLast & D_RIGHT) {
        // .right
            // ld a, [hl]
            // and 1
            // ret nz
            if((wram->wEZChatWordSelection & 1) != 0)
                return;
            // ld a, [hl]
            // inc a
            a = wram->wEZChatWordSelection + 1;
        }
        else {
            // RET;
            return;
        }

    finish_dpad: {
        // push af
        uint8_t b = a;
        // srl a
        // inc a
        // call EZChatGetValidWordsLine
        u8_pair_flag_s res = EZChatGetValidWordsLine((a >> 1) + 1);
        // pop bc
        // and a
        // ld c, a
        uint8_t c = res.b;
        // ld a, b
        a = b;
        // jr nz, .after_y_positioning
        if(res.b == 0) {
            // sub EZCHAT_WORDS_PER_ROW
            // jr nc, .finish_dpad
            if(a >= EZCHAT_WORDS_PER_ROW) {
                a -= EZCHAT_WORDS_PER_ROW;
                goto finish_dpad;
            }
            // xor a
            a = 0;
            // ld b, a
            b = 0;
        }
    // .after_y_positioning
        // and 1
        // jr z, .done
        if((a & 1) != 0) {
            // dec c
            --c;
            // jr nz, .done
            if(c == 0) {
                // dec b
                --b;
            }
        }
    // .done
        // ld a, b
        // ld [wEZChatWordSelection], a
        wram->wEZChatWordSelection = b;
        // ret
        return;
    }
    }

    // LD_A_addr(wcd26);
    // AND_A_A;
    // RET_Z ;
    // SUB_A(0xc);
    // IF_NC goto asm_11c699;
    // XOR_A_A;

// asm_11c699:
    // LD_addr_A(wcd26);
    // goto asm_11c6c4;
// ; select
	// ld a, [wEZChatPageOffset]
	// and a
	// ret z
    if(wram->wEZChatPageOffset == 0)
        return;
	// ld e, EZCHAT_WORDS_PER_COL
    uint8_t e = EZCHAT_WORDS_PER_COL;
    do {
    // .select_loop
        // call .move_menu_up_by_one
        Function11c675_move_menu_up_by_one();
        // dec e
        // jr nz, .select_loop
    } while(--e != 0);
	// jr .navigate_to_page
    goto navigate_to_page;

// asm_11c6c4:
    // CALL(aFunction11c992);
    // CALL(aFunction11c7bc);
    // CALL(aFunction11c86e);
    // RET;

navigate_to_page:
    // call DelayFrame
    DelayFrame();
    // call Function11c992
    Function11c992();
    // call EZChat_RenderWordChoices
    EZChat_RenderWordChoices();
    // call EZChatMenu_WordSubmenuBottom
    Function11c86e();
    // ld hl, wEZChatWordSelection
    // ld a, [hl]
    a = wram->wEZChatWordSelection;
    // jp .finish_dpad
    goto finish_dpad;

// a:
    // CALL(aFunction11c8f6);
    // LD_A(0x4);
    // LD_addr_A(wcd35);
    // goto asm_11c6fc;

// b:
    // LD_A_addr(wcd2b);
    // AND_A_A;
    // IF_NZ goto asm_11c6fa;
    // LD_A(0x6);
    // goto asm_11c6fc;

// asm_11c6fa:
    // LD_A(0x15);

// asm_11c6fc:
    // LD_addr_A(wJumptableIndex);
    // LD_HL(wcd24);
    // SET_hl(3);
    // CALL(aPlayClickSFX);
    // RET;


// asm_11c708:
    // LD_A_hl;
    // CP_A(0x3);
    // IF_C goto asm_11c711;
    // SUB_A(0x3);
    // goto asm_11c76e;

// asm_11c711:
    // LD_A_addr(wcd26);
    // SUB_A(0x3);
    // RET_C ;
    // LD_addr_A(wcd26);
    // goto asm_11c6c4;

// asm_11c71c:
    // LD_HL(wcd28);
    // LD_A_addr(wcd26);
    // ADD_A(0xc);
    // RET_C ;
    // CP_A_hl;
    // RET_NC ;
    // LD_A_addr(wcd26);
    // ADD_A(0x3);
    // LD_addr_A(wcd26);
    // goto asm_11c6c4;

// asm_11c731:
    // LD_A_addr(wcd28);
    // LD_B_A;
    // LD_A_addr(wcd26);
    // ADD_A_hl;
    // ADD_A(0x3);
    // CP_A_B;
    // RET_NC ;
    // LD_A_hl;
    // CP_A(0x9);
    // IF_NC goto asm_11c71c;
    // ADD_A(0x3);
    // goto asm_11c76e;

// asm_11c746:
    // LD_A_hl;
    // AND_A_A;
    // RET_Z ;
    // CP_A(0x3);
    // RET_Z ;
    // CP_A(0x6);
    // RET_Z ;
    // CP_A(0x9);
    // RET_Z ;
    // DEC_A;
    // goto asm_11c76e;

// asm_11c755:
    // LD_A_addr(wcd28);
    // LD_B_A;
    // LD_A_addr(wcd26);
    // ADD_A_hl;
    // INC_A;
    // CP_A_B;
    // RET_NC ;
    // LD_A_hl;
    // CP_A(0x2);
    // RET_Z ;
    // CP_A(0x5);
    // RET_Z ;
    // CP_A(0x8);
    // RET_Z ;
    // CP_A(0xb);
    // RET_Z ;
    // INC_A;

// asm_11c76e:
    // LD_hl_A;
    // RET;

}

void Function11c770(void){
    // XOR_A_A;
    // LD_addr_A(wMobileCommsJumptableIndex);
    wram->wMobileCommsJumptableIndex = 0x0;
    // LD_addr_A(wcd26);
    wram->wcd26 = 0x0;
    // LD_addr_A(wcd27);
    wram->wcd27 = 0x0;
    // LD_A_addr(wcd2b);
    // AND_A_A;
    // IF_NZ goto cd2b_is_nonzero;
    if(wram->wcd2b != 0) {
    // cd2b_is_nonzero:
    // compute from [wc6a8 + 2 * [wcd22]]
        // LD_HL(wc6a8);
        // LD_A_addr(wcd22);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_addr_A(wcd28);
        wram->wcd28 = wram->wc6a8[wram->wcd22 * 2];
        // goto div_12;
    }
    // LD_A_addr(wcd21);
    // AND_A_A;
    // IF_Z goto cd21_is_zero;
    else if(wram->wcd21 == 0) {
    // cd21_is_zero:
    // compute from [wc7d2]
        // LD_A_addr(wc7d2);
        // LD_addr_A(wcd28);
        wram->wcd28 = wram->wc7d2[0];
    }
    else {
    // load from data array
        // DEC_A;
        // SLA_A;
        // LD_HL(mMobileEZChatData_WordAndPageCounts);
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        u8_pair_s pair = MobileEZChatData_WordAndPageCounts[wram->wcd21 - 1];
        // LD_A_hli;
        // LD_addr_A(wcd28);
        wram->wcd28 = pair.a;
        // LD_A_hl;

    // load:
        // LD_addr_A(wcd29);
        wram->wcd29 = pair.b;
        // RET;
        return;
    }

// div_12:
    // LD_C(12);
    // CALL(aSimpleDivide);
    struct DivideResult_t res = SimpleDivide(wram->wcd28, 12);
    // AND_A_A;
    // IF_NZ goto no_need_to_floor;
    if(res.rem == 0) {
        // DEC_B;
        res.quot--;
    }

// no_need_to_floor:
    // LD_A_B;
    // goto load;
    wram->wcd29 = res.quot;
    return;
}

void EZChat_DetermineWordCounts(void){
    // xor a
    // ld [wEZChatWordSelection], a
    wram->wEZChatWordSelection = 0x0;
    // ld [wEZChatPageOffset], a
    wram->wEZChatPageOffset = 0x0;
    // ld [wcd27], a
    wram->wcd27 = 0x0;
    // ld [wcd29], a
    wram->wcd29 = 0x0;
    // ld a, [wEZChatCategoryMode]
    // bit 0, a
    // jr nz, .is_sorted_mode
    uint8_t a;
    if(bit_test(wram->wEZChatCategoryMode, 0)) {
    // .is_sorted_mode
        // compute from [c6a8 + 2 * [cd22]]
        // ld hl, wc6a8 ; $c68a + 30
        // ld a, [wEZChatSortedSelection]
        // ld c, a
        // ld b, 0
        // add hl, bc
        // jr .prepare_items_load
        a = wram->wc6a8[wram->wEZChatSortedSelection * 2];
    }
    // ld a, [wEZChatCategorySelection]
    // and a
    // jr z, .is_pokemon_selection
    else if(wram->wEZChatCategorySelection == 0) {
    // .is_pokemon_selection
        // compute from [wc7d2]
        // ld a, [wc7d2]
        // jr .set_loaded_items
        a = wram->wc7d2[0];
    }
    else {
        // load from data array
        // call EZChat_GetSelectedCategory
        // dec a
        // sla a
        // ld hl, MobileEZChatData_WordAndPageCounts
        // ld c, a
        // ld b, 0
    // .prepare_items_load
        // add hl, bc
        // ld a, [hl]
        a = MobileEZChatData_WordAndPageCounts[EZChat_GetSelectedCategory(wram->wEZChatCategorySelection) - 1].a;
    }
// .set_loaded_items
    // ld [wEZChatLoadedItems], a
    wram->wEZChatLoadedItems[0] = a;
    // ret
    return;
}

// EZChat_RenderWordChoices_JP
void Function11c7bc(void){
    // LD_BC(mUnknown_11c854);
    // LD_A_addr(wcd2b);
    // AND_A_A;
    // IF_NZ goto asm_11c814;
    LD_A_addr(wcd21);
    LD_D_A;
    AND_A_A;
    IF_Z goto asm_11c7e9;
    LD_A_addr(wcd26);
    LD_E_A;

asm_11c7d0:
    LD_A_bc;
    LD_L_A;
    INC_BC;
    LD_A_bc;
    LD_H_A;
    INC_BC;
    AND_A_L;
    CP_A(0xff);
    RET_Z ;
    PUSH_BC;
    PUSH_DE;
    CALL(aFunction11c05d);
    POP_DE;
    POP_BC;
    INC_E;
    LD_A_addr(wcd28);
    CP_A_E;
    IF_NZ goto asm_11c7d0;
    RET;


asm_11c7e9:
    LD_HL(wListPointer);
    LD_A_addr(wcd26);
    LD_E_A;
    ADD_HL_DE;

asm_11c7f1:
    PUSH_DE;
    LD_A_hli;
    LD_E_A;
    LD_D(0);
    PUSH_HL;
    LD_A_bc;
    LD_L_A;
    INC_BC;
    LD_A_bc;
    LD_H_A;
    INC_BC;
    AND_A_L;
    CP_A(0xff);
    IF_Z goto asm_11c811;
    PUSH_BC;
    CALL(aFunction11c05d);
    POP_BC;
    POP_HL;
    POP_DE;
    INC_E;
    LD_A_addr(wcd28);
    CP_A_E;
    IF_NZ goto asm_11c7f1;
    RET;


asm_11c811:
    POP_HL;
    POP_DE;
    RET;


asm_11c814:
    LD_HL(wc648);
    LD_A_addr(wcd22);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    PUSH_DE;
    POP_HL;
    LD_A_addr(wcd26);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_addr(wcd26);
    LD_E_A;

asm_11c831:
    PUSH_DE;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    PUSH_HL;
    LD_A_bc;
    LD_L_A;
    INC_BC;
    LD_A_bc;
    LD_H_A;
    INC_BC;
    AND_A_L;
    CP_A(0xff);
    IF_Z goto asm_11c851;
    PUSH_BC;
    CALL(aFunction11c05d);
    POP_BC;
    POP_HL;
    POP_DE;
    INC_E;
    LD_A_addr(wcd28);
    CP_A_E;
    IF_NZ goto asm_11c831;
    RET;


asm_11c851:
    POP_HL;
    POP_DE;
    RET;

}

static uint8_t* EZChat_RenderWordChoices_get_next_word(uint8_t* hl, uint8_t* d, uint8_t* e){
    // ld a, d
    // and $7F
    // ret nz
    if(*d & 0x7f)
        return hl;
    // ld a, [hli]
    // ld e, a
    *e = *(hl++);
    // ld a, d
    // and a
    // ret z
    if(*d == 0)
        return hl;
    // ld a, [hli]
    // ld d, a
    *d = *(hl++);
    // ret
    return hl;
}

static uint8_t EZChat_RenderWordChoices_printing_one_word(uint8_t** hl, const uint16_t** bc, uint8_t d, uint8_t e){
    // push de
    // call .get_next_word
    *hl = EZChat_RenderWordChoices_get_next_word(*hl, &d, &e);
    // push hl
    // ld a, [bc]
    // ld l, a
    // inc bc
    // ld a, [bc]
    // ld h, a
    uint16_t coord = *((*bc)++);
    uint8_t a = (uint8_t)coord;
    // inc bc
    // and l
    // cp -1
    // jr z, .printing_loop_exit
    if(coord != (uint16_t)-1) {
        // push bc
        struct TextPrintState st = {.hl = wram->wTilemap + coord};
        // call EZChat_RenderOneWord
        EZChat_RenderOneWord(&st, d, e);
        // ld a, c
        // sub l
        a = (st.bc - st.hl);
        // pop bc
    }
// .printing_loop_exit
    // pop hl
    // pop de
    // ret
    return a;
}

void EZChat_RenderWordChoices(void){
    // ld bc, EZChatCoord_WordSubmenu
    const uint16_t* bc = Unknown_11c854;
    // ld a, [wEZChatCategoryMode]
    // bit 0, a
    // jr nz, .is_sorted
    uint8_t d, e;
    uint8_t* hl = NULL;
    if(bit_test(wram->wEZChatCategoryMode, 0)) {
    // .is_sorted
        // ld hl, wEZChatSortedWordPointers
        // ld a, [wEZChatSortedSelection]
        // ld e, a
        // ld d, 0
        // add hl, de
        // add hl, de
    // got word
        // ld a, [hli]
        // ld e, a
        // ld a, [hl]
        // ld d, a
        uint8_t* word = gEZChatSortedWordPointers[wram->wEZChatSortedSelection];
    // de -> hl
        // push de
        // pop hl
        hl = word + wram->wEZChatPageOffset * 2;
        // ld a, [wEZChatPageOffset]
        // ld e, a
        // ld d, 0
        // add hl, de
        // add hl, de
        // ld a, [wEZChatPageOffset]
        // ld e, a
        e = *hl;
        // ld d, $80
        d = 0x80;
        // jr .loop
    }
    else {
    // grouped
        // ld a, [wEZChatCategorySelection]
        // call EZChat_GetSelectedCategory
        // ld d, a
        d = EZChat_GetSelectedCategory(wram->wEZChatCategorySelection);
        // and a
        // ld a, [wEZChatPageOffset]
        // ld e, a
        e = wram->wEZChatPageOffset;
        // jr nz, .loop
        if(d == 0) {
            // ld hl, wListPointer
            hl = wram_ptr(wListPointer);
            // add hl, de
        }
    }

    do {
    // .loop
        // call .printing_one_word
        uint8_t a = EZChat_RenderWordChoices_printing_one_word(&hl, &bc, d, e);
        // cp -1
        // ret z
        if(a == (uint8_t)-1)
            return;
        // cp ((EZCHAT_CHARS_PER_LINE - 2) / 2) + 1
        // jr nc, .skip_one
        if(a >= ((EZCHAT_CHARS_PER_LINE - 2) / 2) + 1) {
            bc += 2;
            continue;
        }
        // push de
        // inc e
        uint8_t d2 = d;
        uint8_t e2 = e;
        // push hl
        // call .get_next_word
        EZChat_RenderWordChoices_get_next_word(hl, &d2, &e2);
        // call EZChatMenu_DirectGetRealChosenWordSize
        a = EZChatMenu_DirectGetRealChosenWordSize(d2, e2);
        // pop hl
        // pop de
        // cp ((EZCHAT_CHARS_PER_LINE - 2) / 2) + 1
        // jr nc, .skip_one
        if(a >= ((EZCHAT_CHARS_PER_LINE - 2) / 2) + 1) {
            bc += 2;
            continue;
        }
        // inc e
        e++;
        // ld a, [wEZChatLoadedItems]
        // cp e
        // ret z
        if(e == wram->wEZChatLoadedItems[0])
            return;
        // call .printing_one_word
        EZChat_RenderWordChoices_printing_one_word(&hl, &bc, d, e);
        // jr .after_skip
    // .skip_one
        // inc bc
        // inc bc
    // .after_skip
        // inc e
        // ld a, [wEZChatLoadedItems]
        // cp e
        // jr nz, .loop
    } while(wram->wEZChatLoadedItems[0] != ++e);
    // ret
    return;
}

// EZChatCoord_WordSubmenu
const uint16_t Unknown_11c854[] = {
#if defined(_CRYSTAL_JP)
    coord(2, 8, 0),
    coord(8, 8, 0),
    coord(14, 8, 0),
    coord(2, 10, 0),
    coord(8, 10, 0),
    coord(14, 10, 0),
    coord(2, 12, 0),
    coord(8, 12, 0),
    coord(14, 12, 0),
    coord(2, 14, 0),
    coord(8, 14, 0),
    coord(14, 14, 0),
#else
    coord(2,  8, 0),
    coord(11,  8, 0), // 8, 8 MENU_WIDTH
    coord(2, 10, 0),
    coord(11, 10, 0), // 8, 10 MENU_WIDTH
    coord(2, 12, 0),
    coord(11, 12, 0), // 8, 12 MENU_WIDTH
    coord(2, 14, 0),
    coord(11, 14, 0), // 8, 14 MENU_WIDTH
#endif
    -1,
};

// EZChatMenu_WordSubmenuBottom
void Function11c86e(void){
    // LD_A_addr(wcd26);
    // AND_A_A;
    // IF_Z goto asm_11c88a;
    if(wram->wcd26 != 0) {
        // hlcoord(2, 17, wTilemap);
        // LD_DE(mMobileString_Prev);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(MobileString_Prev), coord(1, 17, wram->wTilemap));
        // hlcoord(6, 17, wTilemap);
        uint8_t* hl = coord(6, 17, wram->wTilemap);
        // LD_C(0x3);
        uint8_t c = 0x3;
        // XOR_A_A;
        uint8_t a = 0x0;

        do {
        // asm_11c883:
            // LD_hli_A;
            *(hl++) = a++;
            // INC_A;
            // DEC_C;
            // IF_NZ goto asm_11c883;
        } while(--c != 0);
        // goto asm_11c895;
    }
    else {
    // asm_11c88a:
        // hlcoord(2, 17, wTilemap);
        uint8_t* hl = coord(2, 17, wram->wTilemap);
        // LD_C(0x7);
        uint8_t c = 0x7;
        // LD_A(0x7f);

        do {
        // asm_11c891:
            // LD_hli_A;
            *(hl++) = 0x7f;
            // DEC_C;
            // IF_NZ goto asm_11c891;
        } while(--c != 0);
    }

// asm_11c895:
    // LD_HL(wcd28);
    // LD_A_addr(wcd26);
    // ADD_A(0xc);
    // IF_C goto asm_11c8b7;
    // CP_A_hl;
    // IF_NC goto asm_11c8b7;
    if((uint16_t)wram->wcd26 + 0xc < 0xff && (uint16_t)wram->wcd26 + 0xc < wram->wcd28) {
        // hlcoord(16, 17, wTilemap);
        // LD_DE(mMobileString_Next);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(MobileString_Next), coord(16, 17, wram->wTilemap));
        // hlcoord(11, 17, wTilemap);
        uint8_t* hl = coord(11, 17, wram->wTilemap);
        // LD_A(0x3);
        uint8_t a = 0x3;
        // LD_C_A;
        uint8_t c = a;

        do {
        // asm_11c8b1:
            // LD_hli_A;
            // INC_A;
            *(hl++) = a++;
            // DEC_C;
            // IF_NZ goto asm_11c8b1;
        } while(--c != 0);
        // RET;
    }
    else {
    // asm_11c8b7:
        // hlcoord(17, 16, wTilemap);
        // LD_A(0x7f);
        // LD_hl_A;
        *coord(17, 16, wram->wTilemap) = 0x7f;
        // hlcoord(11, 17, wTilemap);
        uint8_t* hl = coord(11, 17, wram->wTilemap);
        // LD_C(0x7);
        uint8_t c = 0x7;

        do {
        // asm_11c8c2:
            // LD_hli_A;
            *(hl++) = 0x7f;
            // DEC_C;
            // IF_NZ goto asm_11c8c2;
        } while(--c != 0);
        // RET;
    }
}

void BCD2String(void){
//  //  unreferenced
    INC_A;
    PUSH_AF;
    AND_A(0xf);
    LDH_addr_A(hDividend);
    POP_AF;
    AND_A(0xf0);
    SWAP_A;
    LDH_addr_A(hDividend + 1);
    XOR_A_A;
    LDH_addr_A(hDividend + 2);
    PUSH_HL;
    FARCALL(aFunction11a80c);
    POP_HL;
    LD_A_addr(wcd63);
    ADD_A(0xf6);
    LD_hli_A;
    LD_A_addr(wcd62);
    ADD_A(0xf6);
    LD_hli_A;
    RET;

}

void MobileString_Page(void){
//  //  unreferenced
    //db ['"ぺージ@"'];
}

const char MobileString_Prev[] = "PREV"; //db ['"まえ@"'];
const char MobileString_Next[] = "NEXT"; //db ['"つぎ@"'];

void Function11c8f6(void){
    LD_A_addr(wcd20);
    CALL(aFunction11c95d);
    PUSH_HL;
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_11c938;
    LD_A_addr(wcd21);
    LD_D_A;
    AND_A_A;
    IF_Z goto asm_11c927;
    LD_HL(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    ADD_A_hl;

asm_11c911:
    LD_E_A;

asm_11c912:
    POP_HL;
    PUSH_DE;
    CALL(aFunction11c05d);
    POP_DE;
    LD_A_addr(wcd20);
    LD_C_A;
    LD_B(0);
    LD_HL(wcd36);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_hl_E;
    INC_HL;
    LD_hl_D;
    RET;


asm_11c927:
    LD_HL(wcd26);
    LD_A_addr(wMobileCommsJumptableIndex);
    ADD_A_hl;
    LD_C_A;
    LD_B(0);
    LD_HL(wListPointer);
    ADD_HL_BC;
    LD_A_hl;
    goto asm_11c911;

asm_11c938:
    LD_HL(wc648);
    LD_A_addr(wcd22);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    PUSH_DE;
    POP_HL;
    LD_A_addr(wcd26);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_addr(wMobileCommsJumptableIndex);
    LD_E_A;
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    goto asm_11c912;

    return Function11c95d();
}

void Function11c95d(void){
    SLA_A;
    LD_C_A;
    LD_B(0);
    LD_HL(mUnknown_11c986);
    ADD_HL_BC;
    LD_A_hli;
    LD_C_A;
    LD_A_hl;
    LD_B_A;
    PUSH_BC;
    PUSH_BC;
    POP_HL;
    LD_A(0x5);
    LD_C_A;
    LD_A(0x7f);

asm_11c972:
    LD_hli_A;
    DEC_C;
    IF_NZ goto asm_11c972;
    DEC_HL;
    LD_BC(-20);
    ADD_HL_BC;
    LD_A(0x5);
    LD_C_A;
    LD_A(0x7f);

asm_11c980:
    LD_hld_A;
    DEC_C;
    IF_NZ goto asm_11c980;
    POP_HL;
    RET;

}

bool EZChat_SetOneWord(void){
// get which category mode
    // ld a, [wEZChatWordSelection]
    // srl a
    // call EZChatGetValidWordsLine
    u8_pair_flag_s res = EZChatGetValidWordsLine(wram->wEZChatWordSelection >> 1);
    // ld a, [wEZChatWordSelection]
    // and 1
    // add d
    // ld b, 0
    // ld c, a
    uint8_t c = (wram->wEZChatWordSelection & 1) + res.a;
    // ld a, [wEZChatCategoryMode]
    // bit 0, a
    // jr nz, .alphabetical
    uint8_t d, e;
    if(bit_test(wram->wEZChatCategoryMode, 0)) {
    // .alphabetical
        // ld hl, wEZChatSortedWordPointers
        // ld a, [wEZChatSortedSelection]
        // ld e, a
        // ld d, 0
        // add hl, de
        // add hl, de
        // ld a, [hli]
        // ld h, [hl]
        // ld l, a
        uint8_t* word = gEZChatSortedWordPointers[wram->wEZChatSortedSelection];
        // add hl, bc
        // add hl, bc
        // ld a, [hli]
        // ld e, a
        e = word[2*c + 0];
        // ld a, [hl]
        // ld d, a
        d = word[2*c + 1];
        // jr .put_word
    }
    else {
    // categorical
        // ld a, [wEZChatCategorySelection]
        // call EZChat_GetSelectedCategory
        uint8_t cat = EZChat_GetSelectedCategory(wram->wEZChatCategorySelection);
        // ld d, a
        d = cat;
        // and a
        // jr z, .pokemon
        if(cat == 0) {
        // .pokemon
            // ld hl, wListPointer
            // add hl, bc
            // ld a, [hl]
            // ld e, a
            e = c;
            // jr .put_word
        }
        else {
            // ld e, c
            e = c;
        }
    }
// .put_word
    // call EZChatMenu_DirectGetRealChosenWordSize
    // ld b, a
    uint8_t b = EZChatMenu_DirectGetRealChosenWordSize(d, e);
    // ld a, [wEZChatSelection]
    // ld c, a
    c = wram->wEZChatSelection;
    uint8_t a = c;
    // and 1
    // ld a, c
    // jr z, .after_dec
    if((a & 1) != 0) {
        // dec a
        // dec a
        a -= 2;
    }
// .after_dec
    // inc a
    a += 1;
    // call EZChatMenu_GetRealChosenWordSize
    // add b
    // inc a
    a = EZChatMenu_GetRealChosenWordSize(a) + b + 1;
    // cp EZCHAT_CHARS_PER_LINE + 1
    // ret nc
    if(a >= EZCHAT_CHARS_PER_LINE + 1)
        return false;
    // ld b, 0
    // ld hl, wEZChatWords
    // add hl, bc
    // add hl, bc
    // ld [hl], e
    wram->wEZChatWord[c].a = e;
    // inc hl
    // ld [hl], d
    wram->wEZChatWord[c].b = d;
// finished
    // scf
    // ret
    return true;
}

void EZChatMenu_RerenderMessage(void){
// nugget of a solution
	// ld de, EZChatBKG_ChatWords
	// call EZChat_Textbox
    Function11cfce(Unknown_11cfba);
	// call EZChat_ClearAllWords
    EZChat_ClearAllWords();
	// jr EZChatMenu_MessageSetup
    return EZChatMenu_MessageSetup();
}

uint8_t EZChatMenu_GetRealChosenWordSize(uint8_t a) {
	// push hl
	// push de
	// ld hl, wEZChatWords
	// sla a
	// ld d, 0
	// ld e, a
	// add hl, de
	// ld a, [hli]
	// ld e, a
    uint8_t e = wram->wEZChatWord[a].a;
	// ld d, [hl]
    uint8_t d = wram->wEZChatWord[a].b;
	// jr EZChatMenu_DirectGetRealChosenWordSize.after_initial_setup
    return EZChatMenu_DirectGetRealChosenWordSize(d, e);
}

uint8_t EZChatMenu_DirectGetRealChosenWordSize(uint8_t d, uint8_t e){
    // push hl
    // push de
// after_initial_setup:
    // push bc
    // ld a, e
    // or d
    // jr z, .emptystring
    // ld a, e
    // and d
    // cp $ff
    // jr z, .emptystring
    if((d | e) == 0 || (d & e) == 0xff) {
    // .emptystring
        // xor a
        // jr .done
        return 8;
    }
    struct TextPrintState st = {0};
    // call EZChat_LoadOneWord
    bool carry = Function11c05d(&st, d, e);
    // ld a, 0
    // jr c, .done
    if(carry)
        return 0;
    // call GetLengthOfWordAtC608
    // ld a, c
// .done
    // pop bc
    // pop de
    // pop hl
    // ret
    return GetLengthOfWordAtC608();
}

uint8_t EZChat_GetSelectedCategory(uint8_t a) {
    // push de
    // ld e, a
    // and $0f
    // ld d, a
    // ld a, e
    // swap a
    // and $0f
    // add d
    // pop de
    // ret
    return ((a >> 4) & 0xf) + (a & 0xf);
}

uint8_t EZChat_GetWordSize(uint8_t a) {
// get which category mode
    // push hl
    // push de
    // push bc
    // push af
    // ld a, [wEZChatCategoryMode]
    // bit 0, a
    // jr nz, .alphabetical
    uint8_t d, e;
    if(bit_test(wram->wEZChatCategoryMode, 0)) {
    // alphabetical:
        // ld hl, wEZChatSortedWordPointers
        // ld a, [wEZChatSortedSelection]
        // ld e, a
        // ld d, 0
        // add hl, de
        // add hl, de
        // ld a, [hli]
        // ld h, [hl]
        // ld l, a
        uint8_t* word = gEZChatSortedWordPointers[wram->wEZChatSortedSelection];
        // pop af
        // ld e, a
        // ld d, 0
        // add hl, de
        // add hl, de
        // ld a, [hli]
        // ld e, a
        // ld a, [hl]
        // ld d, a
        // jr .get_word_size
        e = word[2*a];
        d = word[2*a + 1];
    }
    else {
    // categorical
        // ld a, [wEZChatCategorySelection]
        // call EZChat_GetSelectedCategory
        uint8_t cat = EZChat_GetSelectedCategory(wram->wEZChatCategorySelection);
        // ld d, a
        d = cat;
        // and a
        // jr z, .pokemon
        if(cat == 0) {
        // .pokemon
            // pop af
            // ld c, a
            // ld b, 0
            // ld hl, wListPointer
            // add hl, bc
            // ld a, [hl]
            e = a;
            // jr .got_word_entry
        }
        else {
            // pop af
        // .got_word_entry
            // ld e, a
            e = a;
        }
    }
// .get_word_size
    // call EZChatMenu_DirectGetRealChosenWordSize
    // pop bc
    // pop de
    // pop hl
    // ret
    return EZChatMenu_DirectGetRealChosenWordSize(d, e);
}

u8_pair_flag_s EZChatGetValidWordsLine(uint8_t a){
    // push af
    // ld a, [wEZChatPageOffset]
    // ld d, a
    uint8_t d = wram->wEZChatPageOffset;
    // pop af
    // and a
    // ret z
    if(a == 0)
        return u8_pair_flag(d, a, false);
    // push bc
    // ld hl, wEZChatLoadedItems
    uint8_t* hl = wram->wEZChatLoadedItems;
    // ld e, a
    uint8_t e = a;
    uint8_t c;
    do {
    // .loop
        // ld c, 0
        c = 0;
        // ld a, d
        // cp [hl]
        // jr nc, .early_end
        if(d >= *hl)
            goto early_end;
        // inc c
        c++;
        // call EZChat_GetWordSize
        a = EZChat_GetWordSize(a);
        // inc d
        d++;
        // cp ((EZCHAT_CHARS_PER_LINE - 2) / 2) + 1
        // jr nc, .decrease_e
        if(a < ((EZCHAT_CHARS_PER_LINE - 2) / 2) + 1) {
            // ld a, d
            // cp [hl]
            // jr nc, .early_end
            if(d >= *hl)
                goto early_end;
            // call EZChat_GetWordSize
            a = EZChat_GetWordSize(a);
            // cp ((EZCHAT_CHARS_PER_LINE - 2) / 2) + 1
            // jr nc, .decrease_e
            if(a < ((EZCHAT_CHARS_PER_LINE - 2) / 2) + 1) {
                // inc c
                c++;
                // inc d
                d++;
            }
        }

    // .decrease_e
        // dec e
        // jr nz, .loop
    } while(--e != 0);
	// scf
// .end
	// ld a, c
	// pop bc
	// ret
    return u8_pair_flag(d, c, true);

early_end:
	// dec e
	// jr z, .after_end_sanitization
    if(--e != 0) {
	    // ld c, 0
        c = 0;
    }

// after_end_sanitization:
    // and a
    // jr .end
    return u8_pair_flag(d, c, false);
}

const uint16_t Unknown_11c986[] = {
    coord(1, 2, 0),
    coord(7, 2, 0),
    coord(13, 2, 0),
    coord(1, 4, 0),
    coord(7, 4, 0),
    coord(13, 4, 0),
};

static void EZChat_ClearAllWords_clear_line(tile_t* hl) {
    // ld c, EZCHAT_CHARS_PER_LINE
    uint8_t c = EZCHAT_CHARS_PER_LINE;
    // ld a, " "
    tile_t a = 0x7f;
    do {
    // .clear_word
        // ld [hli], a
        *(hl++) = a;
        // dec c
        // jr nz, .clear_word
    } while(--c != 0);
    // ret
}

static void EZChat_ClearAllWords_after_initial_position(tile_t* hl){
    // push hl
    // call .clear_line
    EZChat_ClearAllWords_clear_line(hl);
    // pop hl
    // ld de, SCREEN_WIDTH
    EZChat_ClearAllWords_clear_line(hl + SCREEN_WIDTH);
    // add hl, de
}

void EZChat_ClearAllWords(void) {
    // hlcoord 1, 1
    // call .after_initial_position
    EZChat_ClearAllWords_after_initial_position(coord(1, 1, wram->wTilemap));
    // hlcoord 1, 3
    EZChat_ClearAllWords_after_initial_position(coord(1, 3, wram->wTilemap));
}

void Function11c992(void){
    // LD_A(0x8);
    uint8_t a = 0x8;
    // hlcoord(2, 7, wTilemap);
    tile_t* hl = coord(2, 7, wram->wTilemap);

    do {
    // asm_11c997:
        // PUSH_AF;
        // LD_A(0x7f);
        // PUSH_HL;
        // LD_BC(0x11);
        // CALL(aByteFill);
        ByteFill(hl, SCREEN_WIDTH - 3, 0x7f);
        // POP_HL;
        // LD_BC(0x14);
        // ADD_HL_BC;
        hl += SCREEN_WIDTH;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto asm_11c997;
    } while(--a != 0);
    // RET;
}

// EZChat_WhiteOutLowerMenu
void Function11c9ab(void){
    // LD_A(0x7);
    // hlcoord(0, 6, wAttrmap);
    // LD_BC(0xc8);
    // CALL(aByteFill);
    ByteFill(coord(0, 6, wram->wAttrmap), 0xc8, 0x7);
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // RET;
}

// EZChatDraw_EraseSubmenu
void Function11c9bd(void){
    // LD_DE(mString_11ca38);
    // CALL(aFunction11ca7f);
    Function11ca7f(String_11ca38);

    return Function11c9c3();
}

// EZChatMenu_EraseSubmenu
void Function11c9c3(void){
    // LD_HL(wcd2a);
    // LD_DE(hJoypadPressed);
    // LD_A_de;
    // AND_A(0x1);
    // IF_NZ goto asm_11c9de;
    if(hram->hJoypadPressed & A_BUTTON) {
    // asm_11c9de:
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto asm_11c9e9;
        if(wram->wcd2a == 0) {
            // CALL(aFunction11ca5e);
            Function11ca5e();
            // XOR_A_A;
            // LD_addr_A(wcd20);
            wram->wcd20 = 0;
        }
        goto asm_11c9e9;
    }
    // LD_A_de;
    // AND_A(0x2);
    // IF_NZ goto asm_11c9e9;
    else if(hram->hJoypadPressed & B_BUTTON) {
    asm_11c9e9:
        // LD_HL(wcd24);
        // SET_hl(4);
        bit_set(wram->wcd24, 4);
        // LD_A(0x4);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x4;
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // RET;
        return;
    }
    // LD_A_de;
    // AND_A(0x40);
    // IF_NZ goto asm_11c9f7;
    else if(hram->hJoypadPressed & D_UP) {
    // asm_11c9f7:
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(wram->wcd2a == 0)
            return;
        // DEC_hl;
        wram->wcd2a--;
        // RET;
        return;
    }
    // LD_A_de;
    // AND_A(0x80);
    // IF_NZ goto asm_11c9fc;
    else if(hram->hJoypadPressed & D_DOWN) {
    // asm_11c9fc:
        // LD_A_hl;
        // AND_A_A;
        // RET_NZ ;
        if(wram->wcd2a != 0)
            return;
        // INC_hl;
        wram->wcd2a++;
        // RET;
        return;
    }
    // RET;
}

void Function11ca01(void){
    // hlcoord(14, 7, wAttrmap);
    uint8_t* hl = coord(14, 7, wram->wAttrmap);
    // LD_DE(0x14);
    // LD_A(0x5);
    // LD_C_A;
    uint8_t c = 0x5;

    do {
    // asm_11ca0a:
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_A(0x6);
        // LD_B_A;
        uint8_t b = 0x6;
        // LD_A(0x7);
        do {
        // asm_11ca10:
            // LD_hli_A;
            *(hl2++) = 0x7;
            // DEC_B;
            // IF_NZ goto asm_11ca10;
        } while(--b != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_C;
        // IF_NZ goto asm_11ca0a;
    } while(--c != 0);

    return Function11ca19();
}

void Function11ca19(void){
    // hlcoord(0, 12, wAttrmap);
    uint8_t* hl = coord(0, 12, wram->wAttrmap);
    // LD_DE(0x14);
    // LD_A(0x6);
    // LD_C_A;
    uint8_t c = 0x6;

    do {
    // asm_11ca22:
        // PUSH_HL;
        uint8_t* hl2 = hl;
        // LD_A(0x14);
        // LD_B_A;
        uint8_t b = SCREEN_WIDTH;
        // LD_A(0x7);

        do {
        // asm_11ca28:
            // LD_hli_A;
            *(hl2++) = 0x7;
            // DEC_B;
            // IF_NZ goto asm_11ca28;
        } while(--b != 0);
        // POP_HL;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_C;
        // IF_NZ goto asm_11ca22;
    } while(--c != 0);
    // FARCALL(aReloadMapPart);
    ReloadMapPart_Conv();
    // RET;
}

// EZChatString_EraseMenu
const char String_11ca38[] =
            "All words will"    //db ['"とうろくちゅう<NO>あいさつ¯ぜんぶ"'];
    t_next  "be erased. OK?@";  //next ['"けしても\u3000よろしいですか？@"']

// EZChatString_EraseConfirmation
const char String_11ca57[] =
           "YES"   //db ['"はい"'];
    t_next "NO@";  //next ['"いいえ@"']

// EZChatMenu_EraseWordsAccept
void Function11ca5e(void){
    // XOR_A_A;
    uint8_t a = 0x0;

    do {
    // loop:
        // PUSH_AF;
        // CALL(aFunction11ca6a);
        Function11ca6a(a);
        // POP_AF;
        // INC_A;
        // CP_A(0x6);
        // IF_NZ goto loop;
    } while(++a != EZCHAT_WORD_COUNT);
    EZChatMenu_RerenderMessage();
    // RET;
}

// EZChatDraw_EraseWordsLoop
void Function11ca6a(uint8_t a){
    // LD_HL(wcd36);
    u8_pair_s* hl = wram->wEZChatWord;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_hl_B;
    hl[a].a = 0;
    // INC_HL;
    // LD_hl_B;
    hl[a].b = 0;
    // CALL(aFunction11c95d); // TODO: Convert Function11c95d
    // LD_DE(mString_11c3bc);
    // CALL(aPlaceString);
    // RET;
}

// EZChatDraw_ConfirmationSubmenu
void Function11ca7f(const char* de){
    // PUSH_DE;
    // LD_DE(mUnknown_11cfc6);
    // CALL(aFunction11cfce);
    Function11cfce(Unknown_11cfc6);
    // LD_DE(mUnknown_11cfca);
    // CALL(aFunction11cfce);
    Function11cfce(Unknown_11cfca);
    // hlcoord(1, 14, wTilemap);
    // POP_DE;
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(de), coord(1, 14, wram->wTilemap));
    // hlcoord(16, 8, wTilemap);
    // LD_DE(mString_11ca57);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11ca57), coord(16, 8, wram->wTilemap));
    // CALL(aFunction11ca01);
    Function11ca01();
    // LD_A(0x1);
    // LD_addr_A(wcd2a);
    wram->wcd2a = 0x1;
    // LD_HL(wcd24);
    // RES_hl(4);
    bit_reset(wram->wEZChatSpritesMask, 4);
    // CALL(aFunction11cfb5);
    // RET;
    return Function11cfb5();
}

// EZChatDraw_ExitSubmenu
void Function11caad(void){
    // LD_DE(mString_11cb1c);
    // CALL(aFunction11ca7f);
    Function11ca7f(String_11cb1c);

    return Function11cab3();
}

// EZChatMenu_ExitSubmenu
void Function11cab3(void){
    // LD_HL(wcd2a);
    // LD_DE(hJoypadPressed);
    // LD_A_de;
    // AND_A(0x1);
    // IF_NZ goto asm_11cace;
    if(hram->hJoypadPressed & A_BUTTON) {
    // asm_11cace:
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto asm_11cafc;
        if(wram->wcd2a != 0)
            goto asm_11cafc;
        // LD_A_addr(wcd35);
        // AND_A_A;
        // IF_Z goto asm_11caf3;
        // CP_A(0xff);
        // IF_Z goto asm_11caf3;
        if(wram->wcd35 != 0 && wram->wcd35 != 0xff) {
            // LD_A(0xff);
            // LD_addr_A(wcd35);
            wram->wcd35 = 0xff;
            // hlcoord(1, 14, wTilemap);
            // LD_DE(mString_11cb31);
            // CALL(aPlaceString);
            PlaceStringSimple(U82C(String_11cb31), coord(1, 14, wram->wTilemap));
            // LD_A(0x1);
            // LD_addr_A(wcd2a);
            wram->wcd2a = 0x1;
            // RET;
            return;
        }

    // asm_11caf3:
        // LD_HL(wJumptableIndex);
        // SET_hl(7);
        bit_set(wram->wJumptableIndex, 7);
        // RET;
        return;
    }
    // LD_A_de;
    // AND_A(0x2);
    // IF_NZ goto asm_11caf9;
    else if(hram->hJoypadPressed & B_BUTTON) {
    // asm_11caf9:
        // CALL(aPlayClickSFX);
        PlayClickSFX();

    asm_11cafc:
        // LD_HL(wcd24);
        // SET_hl(4);
        bit_set(wram->wEZChatSpritesMask, 4);
        // LD_A(0x4);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x4;
        // LD_A_addr(wcd35);
        // CP_A(0xff);
        // RET_NZ ;
        if(wram->wcd35 != 0xff)
            return;
        // LD_A(0x1);
        // LD_addr_A(wcd35);
        wram->wcd35 = 0x1;
        // RET;
        return;
    }
    // LD_A_de;
    // AND_A(0x40);
    // IF_NZ goto asm_11cb12;
    else if(hram->hJoypadPressed & D_UP) {
    // asm_11cb12:
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(wram->wcd2a == 0)
            return;
        // DEC_hl;
        --wram->wcd2a;
        // RET;
        return;
    }
    // LD_A_de;
    // AND_A(0x80);
    // IF_NZ goto asm_11cb17;
    else if(hram->hJoypadPressed & D_DOWN) {
    // asm_11cb17:
        // LD_A_hl;
        // AND_A_A;
        // RET_NZ ;
        if(wram->wcd2a != 0)
            return;
        // INC_hl;
        ++wram->wcd2a;
        // RET;
        return;
    }
    // RET;
    return;
}

// EZChatString_ExitPrompt
const char String_11cb1c[] = 
            "Want to stop"          //db ['"あいさつ<NO>とうろく¯ちゅうし"'];
    t_next  "setting a message?@";  //next ['"しますか？@"']

// EZChatString_ExitConfirmation
const char String_11cb31[] = 
            "Quit without"          //db ['"とうろくちゅう<NO>あいさつ<WA>ほぞん"'];
    t_next  "saving a message? @";  //next ['"されません<GA>よろしい\u3000ですか？@"']

// EZChatDraw_MessageTypeMenu
// Message Type Menu Drawing (Intro/Battle Start/Win/Lose menu)
void Function11cb52(void){
    // LD_HL(mUnknown_11cc01);
    // LD_A_addr(wMenuCursorY);

    // asm_11cb58:
        // DEC_A;
        // IF_Z goto asm_11cb5f;
        // INC_HL;
        // INC_HL;
        // goto asm_11cb58;

// asm_11cb5f:
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hl;
    // LD_D_A;
    // CALL(aFunction11ca7f);
    Function11ca7f(Unknown_11cc01[wram->wMenuCursorY - 1]);

    return Function11cb66();
}

// EZChatMenu_MessageTypeMenu
void Function11cb66(void){
    // LD_HL(wcd2a);
    // LD_DE(hJoypadPressed);
    // LD_A_de;
    // AND_A(0x1);
    // IF_NZ goto asm_11cb81;
    if(hram->hJoypadPressed & A_BUTTON) {
    // asm_11cb81:
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto asm_11cbd4;
        if(wram->wcd2a != 0) {
        // asm_11cbd4:
            // CALL(aPlayClickSFX);
            PlayClickSFX();
            goto asm_11cbd7;
        }
        // LD_A(BANK(s4_a007));
        // CALL(aOpenSRAM);
        OpenSRAM(MBANK(as4_a007));
        // LD_HL(s4_a007);
        // LD_A_addr(wMenuCursorY);
        // DEC_A;
        // SLA_A;
        // SLA_A;
        // LD_C_A;
        // SLA_A;
        // ADD_A_C;
        // LD_C_A;
        // LD_B(0);
        // ADD_HL_BC;
        uint8_t* hl = (uint8_t*)GBToRAMAddr(s4_a007) + ((wram->wMenuCursorY - 1) * 12);
        // LD_DE(wcd36);
        const uint8_t* de = &wram->wcd36;
        // LD_C(12);

        for(uint8_t c = 0; c < 12; ++c) {
        // asm_11cba2:
            // LD_A_de;
            // LD_hli_A;
            hl[c] = de[c];
            // INC_DE;
            // DEC_C;
            // IF_NZ goto asm_11cba2;
        }
        // CALL(aCloseSRAM);
        CloseSRAM();
        // CALL(aPlayClickSFX);
        PlayClickSFX();
        // LD_DE(mUnknown_11cfc6);
        // CALL(aFunction11cfce);
        Function11cfce(Unknown_11cfc6);
        // LD_HL(mUnknown_11cc7e);
        // LD_A_addr(wMenuCursorY);

    // asm_11cbba:
        // DEC_A;
        // IF_Z goto asm_11cbc1;
        // INC_HL;
        // INC_HL;
        // goto asm_11cbba;

    // asm_11cbc1:
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hl;
        // LD_D_A;
        // hlcoord(1, 14, wTilemap);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(Unknown_11cc7e[wram->wMenuCursorY - 1]), coord(1, 14, wram->wTilemap));
        // LD_HL(wJumptableIndex);
        // INC_hl;
        wram->wJumptableIndex++;
        // INC_HL;
        // LD_A(0x10);
        // LD_hl_A;
        wram->wcf64 = 0x10;
        // RET;
        return;
    }
    // LD_A_de;
    // AND_A(0x2);
    // IF_NZ goto asm_11cbd7;
    else if(hram->hJoypadPressed & B_BUTTON) {
    asm_11cbd7:
        // LD_DE(mUnknown_11cfba);
        // CALL(aFunction11cfce);
        Function11cfce(Unknown_11cfba);
        // CALL(aFunction11c38a);
        EZChatMenu_MessageSetup();
        // LD_HL(wcd24);
        // SET_hl(4);
        bit_set(wram->wcd24, 4);
        // LD_A(0x4);
        // LD_addr_A(wJumptableIndex);
        wram->wJumptableIndex = 0x4;
        // RET;
        return;
    }
    // LD_A_de;
    // AND_A(0x40);
    // IF_NZ goto asm_11cbeb;
    else if(hram->hJoypadPressed & D_UP) {
    // asm_11cbeb:
        // LD_A_hl;
        // AND_A_A;
        // RET_Z ;
        if(wram->wcd2a == 0)
            return;
        // DEC_hl;
        wram->wcd2a--;
        // RET;
        return;
    }
    // LD_A_de;
    // AND_A(0x80);
    // IF_NZ goto asm_11cbf0;
    else if(hram->hJoypadPressed & D_DOWN) {
    // asm_11cbf0:
        // LD_A_hl;
        // AND_A_A;
        // RET_NZ ;
        if(wram->wcd2a != 0)
            return;
        // INC_hl;
        wram->wcd2a++;
        // RET;
        return;
    }
    // RET;
}

void Function11cbf5(void){
    // CALL(aWaitSFX);
    WaitSFX();
    // LD_HL(wcf64);
    // DEC_hl;
    // RET_NZ ;
    if(--wram->wcf64 != 0)
        return;
    // DEC_HL;
    // SET_hl(7);
    bit_set(wram->wJumptableIndex, 7);
    // RET;
}

// EZChatString_MessageDescription
const char* const Unknown_11cc01[] = {
    String_11cc09,
    String_11cc23,
    String_11cc42,
    String_11cc60,
};

// EZChatString_MessageIntroDescription
const char String_11cc09[] =
            "Shown as an"         //db ['"じこしょうかい\u3000は"'];
    t_next  "introduction. OK?@"; //next ['"この\u3000あいさつで\u3000いいですか？@"']

// EZChatString_MessageBattleStartDescription
const char String_11cc23[] =
            "Shown when a"          //db ['"たいせん\u3000<GA>はじまるとき\u3000は"'];
    t_next  "battle starts. OK?@";  //next ['"この\u3000あいさつで\u3000いいですか？@"']

// EZChatString_MessageBattleWinDescription
const char String_11cc42[] = 
	        "Shown if you"        // "たいせん　<NI>かったとき　は"
	t_next  "win a battle. OK?@"; // "この　あいさつで　いいですか？@"

// EZChatString_MessageBattleLoseDescription
const char String_11cc60[] =
	        "Shown if you"          // "たいせん　<NI>まけたとき　は"
	t_next  "lose a battle. OK?@";  // "この　あいさつで　いいですか？@"

// EZChatString_MessageSet
const char* const Unknown_11cc7e[] = {
    String_11cc86,
    String_11cc9d,
    String_11ccb9,
    String_11ccd4,
};

// EZChatString_MessageIntroSet
const char String_11cc86[] = 
            "Introduction"      //db ['"じこしょうかい\u3000の"'];
    t_next  "greeting set!@";   //next ['"あいさつ¯とうろくした！@"']

// EZChatString_MessageBattleStartSet
const char String_11cc9d[] = 
            "Begin battle"      //db ['"たいせん\u3000<GA>はじまるとき\u3000の"'];
    t_next  "greeting set!@";   //next ['"あいさつ¯とうろくした！@"']

// EZChatString_MessageBattleWinSet
const char String_11ccb9[] = 
            "Win battle"        //db ['"たいせん\u3000<NI>かったとき\u3000の"'];
    t_next  "greeting set!@";   //next ['"あいさつ¯とうろくした！@"']

// EZChatString_MessageBattleLoseSet
const char String_11ccd4[] = 
            "Lose battle"       //db ['"たいせん\u3000<NI>まけたとき\u3000の"'];
    t_next  "greeting set!@";   //next ['"あいさつ¯とうろくした！@"']

// EZChatMenu_WarnEmptyMessage
void Function11ccef(void){
    // LD_DE(mUnknown_11cfc6);
    // CALL(aFunction11cfce);
    Function11cfce(Unknown_11cfc6);
    // hlcoord(1, 14, wTilemap);
    // LD_DE(mString_11cd10);
    // CALL(aPlaceString);
    PlaceStringSimple(U82C(String_11cd10), coord(1, 14, wram->wTilemap));
    // CALL(aFunction11ca19);
    Function11ca19();
    // CALL(aFunction11cfb5);
    Function11cfb5();

    return Function11cd04();
}

void Function11cd04(void){
    // LD_DE(hJoypadPressed);
    // LD_A_de;
    // AND_A_A;
    // RET_Z ;
    if(hram->hJoypadPressed == 0)
        return;
    // LD_A(0x4);
    // LD_addr_A(wJumptableIndex);
    wram->wJumptableIndex = EZCHAT_DRAW_CHAT_WORDS;
    // RET;
}

// EZChatString_EnterSomeWords
const char String_11cd10[] =
           "Please enter a"     //db ['"なにか\u3000ことば¯いれてください@"'];
    t_next "phrase or word.@";

void Function11cd20(void){
    CALL(aEZChat_ClearBottom12Rows);
    LD_DE(mUnknown_11cfc6);
    CALL(aFunction11cfce);
    hlcoord(1, 14, wTilemap);
    LD_A_addr(wcd2b);
    LD_addr_A(wcd2c);
    AND_A_A;
    IF_NZ goto asm_11cd3a;
    LD_DE(mString_11cdc7);
    goto asm_11cd3d;

asm_11cd3a:
    LD_DE(mString_11cdd9);

asm_11cd3d:
    CALL(aPlaceString);
    hlcoord(4, 8, wTilemap);
    LD_DE(mString_11cdf5);
    CALL(aPlaceString);
    CALL(aFunction11cdaa);
    LD_HL(wcd24);
    RES_hl(5);
    CALL(aFunction11cfb5);

    return Function11cd54();
}

void Function11cd54(void){
    LD_HL(wcd2c);
    LD_DE(hJoypadPressed);
    LD_A_de;
    AND_A(A_BUTTON);
    IF_NZ goto asm_11cd6f;
    LD_A_de;
    AND_A(B_BUTTON);
    IF_NZ goto asm_11cd73;
    LD_A_de;
    AND_A(D_UP);
    IF_NZ goto asm_11cd8b;
    LD_A_de;
    AND_A(D_DOWN);
    IF_NZ goto asm_11cd94;
    RET;


asm_11cd6f:
    LD_A_hl;
    LD_addr_A(wcd2b);

asm_11cd73:
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_11cd7d;
    LD_A(0x6);
    goto asm_11cd7f;


asm_11cd7d:
    LD_A(0x15);

asm_11cd7f:
    LD_addr_A(wJumptableIndex);
    LD_HL(wcd24);
    SET_hl(5);
    CALL(aPlayClickSFX);
    RET;


asm_11cd8b:
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_hl;
    LD_DE(mString_11cdc7);
    goto asm_11cd9b;


asm_11cd94:
    LD_A_hl;
    AND_A_A;
    RET_NZ ;
    INC_hl;
    LD_DE(mString_11cdd9);

asm_11cd9b:
    PUSH_DE;
    LD_DE(mUnknown_11cfc6);
    CALL(aFunction11cfce);
    POP_DE;
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    RET;

}

void Function11cdaa(void){
    LD_A(0x2);
    hlcoord(0, 6, wAttrmap);
    LD_BC(6 * SCREEN_WIDTH);
    CALL(aByteFill);
    LD_A(0x7);
    hlcoord(0, 12, wAttrmap);
    LD_BC(4 * SCREEN_WIDTH);
    CALL(aByteFill);
    FARCALL(aReloadMapPart);
    RET;

}

void String_11cdc7(void){
//  Words will be displayed by category
    //db ['"ことば¯しゅるいべつに"'];
    //next ['"えらべます@"']

    return String_11cdd9();
}

void String_11cdd9(void){
//  Words will be displayed in alphabetical order
    //db ['"ことば¯アイウエオ\u3000の"'];
    //next ['"じゅんばんで\u3000ひょうじ\u3000します@"']

    return String_11cdf5();
}

void String_11cdf5(void){
    //db ['"しゅるいべつ\u3000モード"'];  // Category mode
    //next ['"アイウエオ\u3000\u3000モード@"']  // ABC mode

    return Function11ce0b();
}

void Function11ce0b(void){
    CALL(aEZChat_ClearBottom12Rows);
    hlcoord(1, 7, wTilemap);
    LD_DE(mString_11cf79);
    CALL(aPlaceString);
    hlcoord(1, 17, wTilemap);
    LD_DE(mEZChatString_Stop_Mode_Cancel);
    CALL(aPlaceString);
    CALL(aFunction11c618);
    LD_HL(wcd24);
    RES_hl(2);
    CALL(aFunction11cfb5);

    return Function11ce2b();
}

void Function11ce2b(void){
    LD_A_addr(wcd22);
    SLA_A;
    SLA_A;
    LD_C_A;
    LD_B(0);
    LD_HL(mUnknown_11ceb9);
    ADD_HL_BC;

    LD_DE(hJoypadPressed);
    LD_A_de;
    AND_A(START);
    IF_NZ goto start;
    LD_A_de;
    AND_A(SELECT);
    IF_NZ goto select;
    LD_A_de;
    AND_A(A_BUTTON);
    IF_NZ goto a;
    LD_A_de;
    AND_A(B_BUTTON);
    IF_NZ goto b;

    LD_DE(hJoyLast);
    LD_A_de;
    AND_A(D_UP);
    IF_NZ goto up;
    LD_A_de;
    AND_A(D_DOWN);
    IF_NZ goto down;
    LD_A_de;
    AND_A(D_LEFT);
    IF_NZ goto left;
    LD_A_de;
    AND_A(D_RIGHT);
    IF_NZ goto right;

    RET;


a:
    LD_A_addr(wcd22);
    CP_A(NUM_KANA);
    IF_C goto place;
    SUB_A(NUM_KANA);
    IF_Z goto done;
    DEC_A;
    IF_Z goto mode;
    goto b;


start:
    LD_HL(wcd24);
    SET_hl(0);
    LD_A(0x8);
    LD_addr_A(wcd20);

b:
    LD_A(0x4);
    goto load;


select:
    LD_A_addr(wcd2b);
    XOR_A(0x1);
    LD_addr_A(wcd2b);
    LD_A(0x6);
    goto load;


place:
    LD_A(0x8);
    goto load;


mode:
    LD_A(0x13);

load:
    LD_addr_A(wJumptableIndex);
    LD_HL(wcd24);
    SET_hl(2);
    CALL(aPlayClickSFX);
    RET;


done:
    LD_A_addr(wcd20);
    CALL(aFunction11ca6a);
    CALL(aPlayClickSFX);
    RET;


left:
    INC_HL;

down:
    INC_HL;

right:
    INC_HL;

up:
    LD_A_hl;
    CP_A(0xff);
    RET_Z ;
    LD_addr_A(wcd22);
    RET;

}

void Unknown_11ceb9(void){
// up left down right
    //db ['0xff', '0x01'];
    //db ['0x05', '0xff'];
    //db ['0xff', '0x02'];
    //db ['0x06', '0x00'];
    //db ['0xff', '0x03'];
    //db ['0x07', '0x01'];
    //db ['0xff', '0x04'];
    //db ['0x08', '0x02'];
    //db ['0xff', '0x14'];
    //db ['0x09', '0x03'];
    //db ['0x00', '0x06'];
    //db ['0x0a', '0xff'];
    //db ['0x01', '0x07'];
    //db ['0x0b', '0x05'];
    //db ['0x02', '0x08'];
    //db ['0x0c', '0x06'];
    //db ['0x03', '0x09'];
    //db ['0x0d', '0x07'];
    //db ['0x04', '0x19'];
    //db ['0x0e', '0x08'];
    //db ['0x05', '0x0b'];
    //db ['0x0f', '0xff'];
    //db ['0x06', '0x0c'];
    //db ['0x10', '0x0a'];
    //db ['0x07', '0x0d'];
    //db ['0x11', '0x0b'];
    //db ['0x08', '0x0e'];
    //db ['0x12', '0x0c'];
    //db ['0x09', '0x1e'];
    //db ['0x13', '0x0d'];
    //db ['0x0a', '0x10'];
    //db ['0x2d', '0xff'];
    //db ['0x0b', '0x11'];
    //db ['0x2d', '0x0f'];
    //db ['0x0c', '0x12'];
    //db ['0x2d', '0x10'];
    //db ['0x0d', '0x13'];
    //db ['0x2d', '0x11'];
    //db ['0x0e', '0x26'];
    //db ['0x2d', '0x12'];
    //db ['0xff', '0x15'];
    //db ['0x19', '0x04'];
    //db ['0xff', '0x16'];
    //db ['0x1a', '0x14'];
    //db ['0xff', '0x17'];
    //db ['0x1b', '0x15'];
    //db ['0xff', '0x18'];
    //db ['0x1c', '0x16'];
    //db ['0xff', '0x23'];
    //db ['0x1d', '0x17'];
    //db ['0x14', '0x1a'];
    //db ['0x1e', '0x09'];
    //db ['0x15', '0x1b'];
    //db ['0x1f', '0x19'];
    //db ['0x16', '0x1c'];
    //db ['0x20', '0x1a'];
    //db ['0x17', '0x1d'];
    //db ['0x21', '0x1b'];
    //db ['0x18', '0x2b'];
    //db ['0x22', '0x1c'];
    //db ['0x19', '0x1f'];
    //db ['0x26', '0x0e'];
    //db ['0x1a', '0x20'];
    //db ['0x27', '0x1e'];
    //db ['0x1b', '0x21'];
    //db ['0x28', '0x1f'];
    //db ['0x1c', '0x22'];
    //db ['0x29', '0x20'];
    //db ['0x1d', '0x2c'];
    //db ['0x2a', '0x21'];
    //db ['0xff', '0x24'];
    //db ['0x2b', '0x18'];
    //db ['0xff', '0x25'];
    //db ['0x2b', '0x23'];
    //db ['0xff', '0xff'];
    //db ['0x2b', '0x24'];
    //db ['0x1e', '0x27'];
    //db ['0x2e', '0x13'];
    //db ['0x1f', '0x28'];
    //db ['0x2e', '0x26'];
    //db ['0x20', '0x29'];
    //db ['0x2e', '0x27'];
    //db ['0x21', '0x2a'];
    //db ['0x2e', '0x28'];
    //db ['0x22', '0xff'];
    //db ['0x2e', '0x29'];
    //db ['0x23', '0xff'];
    //db ['0x2c', '0x1d'];
    //db ['0x2b', '0xff'];
    //db ['0x2f', '0x22'];
    //db ['0x0f', '0x2e'];
    //db ['0xff', '0xff'];
    //db ['0x26', '0x2f'];
    //db ['0xff', '0x2d'];
    //db ['0x2c', '0xff'];
    //db ['0xff', '0x2e'];

    return String_11cf79();
}

void String_11cf79(void){
//  Hiragana table
    //db ['"あいうえお\u3000なにぬねの\u3000や\u3000ゆ\u3000よ"'];
    //next ['"かきくけこ\u3000はひふへほ\u3000わ"']
    //next ['"さしすせそ\u3000まみむめも\u3000そのた"']
    //next ['"たちつてと\u3000らりるれろ"']
    //db ['"@"'];

    return Function11cfb5();
}

// IncrementJumptableIndex
void Function11cfb5(void){
    // LD_HL(wJumptableIndex);
    // INC_hl;
    wram->wJumptableIndex++;
    // RET;
}

// EZChatBKG_ChatWords
const uint8_t Unknown_11cfba[] = {
    0, 0,  // start coords
    20, 6,  // end coords
};

const uint8_t Unknown_11cfbe[] = {
    0, 14,  // start coords
    20, 4,  // end coords
};

const uint8_t Unknown_11cfc2[] = {
    0, 6,  // start coords
    20, 10,  // end coords
};

// EZChatBKG_SortBy
const uint8_t Unknown_11cfc6[] = {
    0, 12,  // start coords
    20, 6,  // end coords
};

// EZChatBKG_SortByConfirmation
const uint8_t Unknown_11cfca[] = {
    14, 7,  // start coords
    6, 5,  // end coords
};

// EZChat_Textbox
void Function11cfce(const uint8_t* de){
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    // LD_BC(SCREEN_WIDTH);
    // LD_A_de;
    // INC_DE;
    // PUSH_AF;
    uint8_t x = *(de++);
    // LD_A_de;
    // INC_DE;
    // AND_A_A;
    uint8_t y = *(de++);

// add_n_times:
    // IF_Z goto done_add_n_times;
    // ADD_HL_BC;
    // DEC_A;
    // goto add_n_times;
    hl += SCREEN_WIDTH * y;

// done_add_n_times:
    // POP_AF;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    hl += x;
    // PUSH_HL;
    tile_t* hl2 = hl;
    // LD_A(0x79);
    // LD_hli_A;
    *(hl2++) = 0x79;
    // LD_A_de;
    // INC_DE;
    uint8_t a = *(de++);
    // DEC_A;
    // DEC_A;
    // IF_Z goto skip_fill;
    if(a - 2 != 0) {
        // LD_C_A;
        uint8_t c = a - 2;
        // LD_A(0x7a);

        do {
        // fill_loop:
            // LD_hli_A;
            *(hl2++) = 0x7a;
            // DEC_C;
            // IF_NZ goto fill_loop;
        } while(--c != 0);
    }

// skip_fill:
    // LD_A(0x7b);
    // LD_hl_A;
    *hl2 = 0x7b;
    // POP_HL;
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    hl += SCREEN_WIDTH;
    // LD_A_de;
    // DEC_DE;
    a = *(de--);
    // DEC_A;
    // DEC_A;
    // IF_Z goto skip_section;
    if(a - 2 != 0) {
        // LD_B_A;
        uint8_t b = a - 2;

        do {
        // loop:
            // PUSH_HL;
            hl2 = hl;
            // LD_A(0x7c);
            // LD_hli_A;
            *(hl2++) = 0x7c;
            // LD_A_de;
            a = *de;
            // DEC_A;
            // DEC_A;
            // IF_Z goto skip_row;
            if(a - 2 != 0) {
                // LD_C_A;
                uint8_t c = a - 2;
                // LD_A(0x7f);

                do {
                // row_loop:
                    // LD_hli_A;
                    *(hl2++) = 0x7f;
                    // DEC_C;
                    // IF_NZ goto row_loop;
                } while(--c != 0);
            }

        // skip_row:
            // LD_A(0x7c);
            // LD_hl_A;
            *hl2 = 0x7c;
            // POP_HL;
            // PUSH_BC;
            // LD_BC(SCREEN_WIDTH);
            // ADD_HL_BC;
            hl += SCREEN_WIDTH;
            // POP_BC;
            // DEC_B;
            // IF_NZ goto loop;
        } while(--b != 0);
    }

// skip_section:
    // LD_A(0x7d);
    // LD_hli_A;
    *(hl++) = 0x7d;
    // LD_A_de;
    a = *de;
    // DEC_A;
    // DEC_A;
    // IF_Z goto skip_remainder;
    if(a - 2 != 0) {
        // LD_C_A;
        uint8_t c = a - 2;
        // LD_A(0x7a);

        do {
        // final_loop:
            // LD_hli_A;
            *(hl++) = 0x7a;
            // DEC_C;
            // IF_NZ goto final_loop;
        } while(--c != 0);
    }

// skip_remainder:
    // LD_A(0x7e);
    // LD_hl_A;
    *hl = 0x7e;
    // RET;
}

// static void Function11d035_AddNMinusOneTimes(tile_t** hl, uint8_t a) {
    // LD_A_de;
    // DEC_A;
    // LD_BC(SCREEN_WIDTH);
    // do {
    // add_n_minus_one_times:
        // ADD_HL_BC;
        // (*hl) += SCREEN_WIDTH;
        // DEC_A;
        // IF_NZ goto add_n_minus_one_times;
    // } while(--a != 0);
    // RET;
// }

// EZChat_Textbox2
void Function11d035(const uint8_t* de){
    // hlcoord(0, 0, wTilemap);
    tile_t* hl = coord(0, 0, wram->wTilemap);
    // LD_BC(SCREEN_WIDTH);
    // LD_A_de;
    // INC_DE;
    uint8_t x1 = *(de++);
    // PUSH_AF;
    // LD_A_de;
    // INC_DE;
    uint8_t y1 = *(de++);
    // AND_A_A;

// add_n_times:
    // IF_Z goto done_add_n_times;
    // ADD_HL_BC;
    // DEC_A;
    // goto add_n_times;

// done_add_n_times:
    // POP_AF;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    hl += (SCREEN_WIDTH * y1) + x1;
    // PUSH_HL;
    tile_t* hl2 = hl;
    // LD_A(0x79);
    // LD_hl_A;
    *hl2 = 0x79;
    // POP_HL;
    // PUSH_HL;
    // LD_A_de;
    // DEC_A;
    // INC_DE;
    uint8_t x2 = *(de++) - 1;
    uint8_t y2 = *de - 1;
    // LD_C_A;
    // ADD_HL_BC;
    hl2 += x2;
    // LD_A(0x7b);
    // LD_hl_A;
    *hl2 = 0x7b;
    // CALL(aFunction11d035_AddNMinusOneTimes);
    hl2 += y2 * SCREEN_WIDTH;
    // LD_A(0x7e);
    // LD_hl_A;
    *hl2 = 0x7e;
    // POP_HL;
    // PUSH_HL;
    hl2 = hl;
    // CALL(aFunction11d035_AddNMinusOneTimes);
    hl2 += y2 * SCREEN_WIDTH;
    // LD_A(0x7d);
    // LD_hl_A;
    *hl2 = 0x7d;
    // POP_HL;
    // PUSH_HL;
    hl2 = hl;
    // INC_HL;
    // PUSH_HL;
    tile_t* bc = hl2 + 1;
    // CALL(aFunction11d035_AddNMinusOneTimes);
    hl2 += y2 * SCREEN_WIDTH;
    // POP_BC;
    // DEC_DE;
    --de;
    // LD_A_de;
    uint8_t a = *de;
    // CP_A(0x2);
    // IF_Z goto skip;
    if(a != 0x2) {
        // DEC_A;
        // DEC_A;
        a -= 2;

        do {
        // loop:
            // PUSH_AF;
            // LD_A(0x7a);
            // LD_hli_A;
            *(hl2++) = 0x7a;
            // LD_bc_A;
            *(bc++) = 0x7a;
            // INC_BC;
            // POP_AF;
            // DEC_A;
            // IF_NZ goto loop;
        } while(--a != 0);
    }

// skip:
    // POP_HL;
    // LD_BC(0x14);
    // ADD_HL_BC;
    hl += SCREEN_WIDTH;
    // PUSH_HL;
    hl2 = hl;
    // LD_A_de;
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    hl2 += (*de - 1);
    // POP_BC;
    // INC_DE;
    de++;
    // LD_A_de;
    // CP_A(0x2);
    // RET_Z ;
    if(*de == 0x2)
        return;
    // PUSH_BC;
    // DEC_A;
    // DEC_A;
    // LD_C_A;
    uint8_t c = (*de - 2);
    // LD_B_A;
    uint8_t b = (*de - 2);
    // LD_DE(0x14);

    do {
    // loop2:
        // LD_A(0x7c);
        // LD_hl_A;
        *hl2 = 0x7c;
        // ADD_HL_DE;
        hl2 += SCREEN_WIDTH;
        // DEC_C;
        // IF_NZ goto loop2;
    } while(--c != 0);
    // POP_HL;
    do {
    // loop3:
        // LD_A(0x7c);
        // LD_hl_A;
        *hl = 0x7c;
        // ADD_HL_DE;
        hl += SCREEN_WIDTH;
        // DEC_B;
        // IF_NZ goto loop3;
    } while(--b != 0);
    // RET;
}

static uint8_t* PrepareEZChatCustomBox_single_row(uint8_t* hl, uint8_t b, uint8_t c, uint8_t d, uint8_t e){
    // push bc
    // ld [hl], e
    // inc hl
    *(hl++) = e;
    // ld [hl], b
    // inc hl
    *(hl++) = b;
    // ld [hl], d
    // inc hl
    // inc d
    *(hl++) = d++;
    // ld [hl], b
    // inc hl
    *(hl++) = b;
    // ld a, c
    uint8_t a = c;
    // srl c
    c >>= 1;
    // sub c
    a -= c;
    // push bc
    // ld c, a
    uint8_t c2 = a;
    // and a
    // ld a, 8
    a = 8;
    // call nz, .line_loop
    if(c2 != 0) {
        do {
            // ld [hl], e
            // inc hl
            *(hl++) = e;
            // ld [hli], a
            *(hl++) = a;
            // add a, 8
            a += 8;
            // ld [hl], d
            // inc hl
            *(hl++) = d;
            // ld [hl], b
            // inc hl
            *(hl++) = b;
            // dec c
            // jr nz, .line_loop
        } while(--c2 != 0);
    }
    // pop bc
    // sub a, 4
    a -= 4;
    // ld [hl], a
    *hl = a;
    // ld a, c
    // and a
    c2 = c;
    // ld a, [hl]
    a = *hl;
    // call nz, .line_loop
    if(c2 != 0) {
        do {
            // ld [hl], e
            // inc hl
            *(hl++) = e;
            // ld [hli], a
            *(hl++) = a;
            // add a, 8
            a += 8;
            // ld [hl], d
            // inc hl
            *(hl++) = d;
            // ld [hl], b
            // inc hl
            *(hl++) = b;
            // dec c
            // jr nz, .line_loop
        } while(--c2 != 0);
    }
    // inc d
    d++;
    // ld [hl], e
    // inc hl
    *(hl++) = e;
    // ld [hli], a
    *(hl++) = a;
    // ld [hl], d
    // inc hl
    *(hl++) = d;
    // ld [hl], b
    // inc hl
    *(hl++) = b;
    // pop bc
    // ld a, c
    // cp EZCHAT_CUSTOM_BOX_BIG_SIZE - 1
    // ret c
    if(c < EZCHAT_CUSTOM_BOX_BIG_SIZE - 1)
        return hl;
    // sub EZCHAT_CUSTOM_BOX_BIG_START - 2
    // sla a
    // sla a
    // ld d, 0
    // ld e, a
    // ld a, l
    // sub e
    // ld l, a
    // ld a, h
    // sbc d
    // ld h, a
    // ld a, c
    // sub (EZCHAT_CUSTOM_BOX_BIG_START * 2) - 2
    // sla a
    // sla a
    // push hl
    // ld e, a
    // add hl, de
    // pop de
    uint8_t* de = hl - ((c - (EZCHAT_CUSTOM_BOX_BIG_START - 2)) << 2);
    // push bc
    // ld c, EZCHAT_CUSTOM_BOX_BIG_START * 4
    c = EZCHAT_CUSTOM_BOX_BIG_START * 4;
    do {
    // .resize_loop
        // ld a, [hli]
        // ld [de], a
        *(de++) = *(hl++);
        // inc de
        // dec c
        // jr nz, .resize_loop
    } while(--c != 0);
    // pop bc
    // ld h, d
    // ld l, e
    // ret
    return de;
}

void PrepareEZChatCustomBox(void){
    // ld a, [wEZChatSelection]
    // cp EZCHAT_MAIN_RESET
    // ret nc
    if(wram->wEZChatSelection >= EZCHAT_MAIN_RESET)
        return;
    // ld hl, wMobileBoxSpriteLoadedIndex
    // cp [hl]
    // ret z
    if(wram->wEZChatSelection == wram->wMobileBoxSpriteLoadedIndex)
        return;
    // ld [hl], a
    wram->wMobileBoxSpriteLoadedIndex = wram->wEZChatSelection;
    // ld d, a
    uint8_t d = wram->wEZChatSelection;
    // call DelayFrame
    DelayFrame();
    // ld a, d
    // call EZChatMenu_GetRealChosenWordSize
    uint8_t a = EZChatMenu_GetRealChosenWordSize(d);
    // ld hl, wMobileBoxSpriteBuffer
    uint8_t* hl = wram->wMobileBoxSpriteBufferData;
    // ld c, a
    // dec c
    uint8_t c = a - 1;
    // cp EZCHAT_CUSTOM_BOX_BIG_SIZE
    // jr c, .after_big_reshape
    if(a >= EZCHAT_CUSTOM_BOX_BIG_SIZE) {
        // ld a, (EZCHAT_CUSTOM_BOX_BIG_START * 2) - 1
        a = (EZCHAT_CUSTOM_BOX_BIG_START * 2) - 1;
        // jr .done_reshape
    }
    else {
    // .after_big_reshape
        // ld a, d
        a = d;
        // and 1
        // ld a, d
        // jr z, .after_reshape
        if(a & 1) {
            // dec a
            // dec a
            a -= 2;
        }
    // .after_reshape
        // inc a
        a++;
        // call EZChatMenu_GetRealChosenWordSize
        a = EZChatMenu_GetRealChosenWordSize(a);
        // sub EZCHAT_CHARS_PER_LINE - ((EZCHAT_CHARS_PER_LINE - 1) / 2)
        bool carry = a < (EZCHAT_CHARS_PER_LINE - ((EZCHAT_CHARS_PER_LINE - 1) / 2));
        // ld c, a
        c = a - (EZCHAT_CHARS_PER_LINE - ((EZCHAT_CHARS_PER_LINE - 1) / 2));
        // ld a, ((EZCHAT_CHARS_PER_LINE - 1) / 2)
        a = ((EZCHAT_CHARS_PER_LINE - 1) / 2);
        // jr c, .prepare_for_resize
        if(!carry) {
            // dec a
            // sub c
            a = (a - 1) - c;
        }
    // .prepare_for_resize
        // ld c, a
        c = a;
        // dec c
        --c;
    }

// .done_reshape
    // inc a
    // sla a
    // ld [hli], a
    wram->wMobileBoxSpriteBufferSize = (a + 1) * 2;
    // ld de, $3000
    // ld b, 0
    // call .single_row
    hl = PrepareEZChatCustomBox_single_row(hl, 0, c, 0x30, 0x00);
    // ld de, $3308
    PrepareEZChatCustomBox_single_row(hl, 0, c, 0x33, 0x08);
}

static void AnimateEZChatCursor_UpdateObjectFlags(struct SpriteAnim* bc, uint8_t a, uint8_t e);
void AnimateEZChatCursor(struct SpriteAnim* bc){
// EZChat Message Menu
static const uint8_t Coords_Zero[] = {
#if defined(_CRYSTAL_JP)
    dbpixel4(1, 3, 5, 2),
    dbpixel4(7, 3, 5, 2),
    dbpixel4(13, 3, 5, 2),
    dbpixel4(1, 5, 5, 2),
    dbpixel4(7, 5, 5, 2),
    dbpixel4(13, 5, 5, 2),
    dbpixel4(1, 17, 5, 2),
    dbpixel4(7, 17, 5, 2),
    dbpixel4(13, 17, 5, 2),
#else
    dbpixel4( 1, 17, 5, 2), // RESET     - 04
    dbpixel4( 7, 17, 5, 2), // QUIT      - 05
    dbpixel4(13, 17, 5, 2), // OK        - 06
#endif
};

// Category Menu
static const uint8_t Coords_One[] = {
#if defined(_CRYSTAL_JP)
    dbpixel4(1, 8, 5, 2),
    dbpixel4(7, 8, 5, 2),
    dbpixel4(13, 8, 5, 2),
    dbpixel4(1, 10, 5, 2),
    dbpixel4(7, 10, 5, 2),
    dbpixel4(13, 10, 5, 2),
    dbpixel4(1, 12, 5, 2),
    dbpixel4(7, 12, 5, 2),
    dbpixel4(13, 12, 5, 2),
    dbpixel4(1, 14, 5, 2),
    dbpixel4(7, 14, 5, 2),
    dbpixel4(13, 14, 5, 2),
    dbpixel4(1, 16, 5, 2),
    dbpixel4(7, 16, 5, 2),
    dbpixel4(13, 16, 5, 2),
    dbpixel4(1, 18, 5, 2),
    dbpixel4(7, 18, 5, 2),
    dbpixel4(13, 18, 5, 2),
#else
    dbpixel4( 0,  8, 8, 8), // Category 1
    dbpixel4(10,  8, 8, 8), // Category 2
    dbpixel4( 0, 10, 8, 8), // Category 3
    dbpixel4(10, 10, 8, 8), // Category 4
    dbpixel4( 0, 12, 8, 8), // Category 5
    dbpixel4(10, 12, 8, 8), // Category 6
    dbpixel4( 0, 14, 8, 8), // Category 7
    dbpixel4(10, 14, 8, 8), // Category 8
    dbpixel4( 0, 16, 8, 8), // Category 9
    dbpixel4(10, 16, 8, 8), // Category 10
    dbpixel4( 1, 18, 5, 2), // DEL
    dbpixel4( 7, 18, 5, 2), // MODE
    dbpixel4(13, 18, 5, 2), // QUIT
#endif
};

// Sort By Letter Menu
static const uint8_t Coords_Two[] = {
#if defined(_CRYSTAL_JP)
    dbpixel2(2, 9),  // 00
    dbpixel2(3, 9),  // 01
    dbpixel2(4, 9),  // 02
    dbpixel2(5, 9),  // 03
    dbpixel2(6, 9),  // 04
    dbpixel2(2, 11),  // 05
    dbpixel2(3, 11),  // 06
    dbpixel2(4, 11),  // 07
    dbpixel2(5, 11),  // 08
    dbpixel2(6, 11),  // 09
    dbpixel2(2, 13),  // 0a
    dbpixel2(3, 13),  // 0b
    dbpixel2(4, 13),  // 0c
    dbpixel2(5, 13),  // 0d
    dbpixel2(6, 13),  // 0e
    dbpixel2(2, 15),  // 0f
    dbpixel2(3, 15),  // 10
    dbpixel2(4, 15),  // 11
    dbpixel2(5, 15),  // 12
    dbpixel2(6, 15),  // 13
    dbpixel2(8, 9),  // 14
    dbpixel2(9, 9),  // 15
    dbpixel2(10, 9),  // 16
    dbpixel2(11, 9),  // 17
    dbpixel2(12, 9),  // 18
    dbpixel2(8, 11),  // 19
    dbpixel2(9, 11),  // 1a
    dbpixel2(10, 11),  // 1b
    dbpixel2(11, 11),  // 1c
    dbpixel2(12, 11),  // 1d
    dbpixel2(8, 13),  // 1e
    dbpixel2(9, 13),  // 1f
    dbpixel2(10, 13),  // 20
    dbpixel2(11, 13),  // 21
    dbpixel2(12, 13),  // 22
    dbpixel2(14, 9),  // 23
    dbpixel2(16, 9),  // 24
    dbpixel2(18, 9),  // 25
    dbpixel2(8, 15),  // 26
    dbpixel2(9, 15),  // 27
    dbpixel2(10, 15),  // 28
    dbpixel2(11, 15),  // 29
    dbpixel2(12, 15),  // 2a
    dbpixel2(14, 11),  // 2b
    dbpixel2(14, 13),  // 2c
    dbpixel4(1, 18, 5, 2),  // 2d
    dbpixel4(7, 18, 5, 2),  // 2e
    dbpixel4(13, 18, 5, 2),  // 2f
#else
    dbpixel2( 2,  9),       // A
    dbpixel2( 4,  9),       // B
    dbpixel2( 6,  9),       // C
    dbpixel2( 8,  9),       // D
    dbpixel2(10,  9),       // E
    dbpixel2(12,  9),       // F
    dbpixel2(14,  9),       // G
    dbpixel2(16,  9),       // H
    dbpixel2(18,  9),       // I
    dbpixel2( 2, 11),       // J
    dbpixel2( 4, 11),       // K
    dbpixel2( 6, 11),       // L
    dbpixel2( 8, 11),       // M
    dbpixel2(10, 11),       // N
    dbpixel2(12, 11),       // O
    dbpixel2(14, 11),       // P
    dbpixel2(16, 11),       // Q
    dbpixel2(18, 11),       // R
    dbpixel2( 2, 13),       // S
    dbpixel2( 4, 13),       // T
    dbpixel2( 6, 13),       // U
    dbpixel2( 8, 13),       // V
    dbpixel2(10, 13),       // W
    dbpixel2(12, 13),       // X
    dbpixel2(14, 13),       // Y
    dbpixel2(16, 13),       // Z
    dbpixel2( 2, 15),       // ETC.
    dbpixel4( 1, 18, 5, 2), // ERASE
    dbpixel4( 7, 18, 5, 2), // MODE
    dbpixel4(13, 18, 5, 2), // CANCEL
#endif
};

// Words Submenu Arrow Positions
static const uint8_t Coords_Three[] = {
#if defined(_CRYSTAL_JP)
    dbpixel2(2, 10),
    dbpixel2(8, 10),
    dbpixel2(14, 10),
    dbpixel2(2, 12),
    dbpixel2(8, 12),
    dbpixel2(14, 12),
    dbpixel2(2, 14),
    dbpixel2(8, 14),
    dbpixel2(14, 14),
    dbpixel2(2, 16),
    dbpixel2(8, 16),
    dbpixel2(14, 16),
#else
    dbpixel2( 2, 10),
    dbpixel2(11, 10), // 8, 10 MENU_WIDTH
    dbpixel2( 2, 12),
    dbpixel2(11, 12), // 8, 12 MENU_WIDTH
    dbpixel2( 2, 14),
    dbpixel2(11, 14), // 8, 14 MENU_WIDTH
    dbpixel2( 2, 16),
    dbpixel2(11, 16), // 8, 16 MENU_WIDTH
#endif
};

// Yes/No Box
static const uint8_t Coords_Four[] = {
    dbpixel2(16, 10), // YES
    dbpixel2(16, 12), // NO
};

// Sort By Menu
static const uint8_t Coords_Five[] = {
    dbpixel2(4, 10), // Group Mode
    dbpixel2(4, 12), // ABC Mode
};

static const uint8_t Coords_Null[] = {
    dbpixel2(0, 20),
};

static const uint8_t FramesetsIDs_Two[] = {
#if defined(_CRYSTAL_JP)
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 00
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 01
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 02
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 03
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 04
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 05
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 06
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 07
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 08
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 09
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0a
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0b
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0c
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0d
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0e
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0f
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 10
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 11
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 12
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 13
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 14
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 15
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 16
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 17
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 18
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 19
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 1a
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 1b
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 1c
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 1d
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 1e
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 1f
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 20
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 21
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 22
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 23
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 24
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 25
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 26
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 27
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 28
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 29
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 2a
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 2b
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_4,  // 2c
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1,  // 2d
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1,  // 2e
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1,  // 2f
#else
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 00 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 01 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 02 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 03 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 04 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 05 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 06 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 07 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 08 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 09 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0a (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0b (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0c (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0d (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0e (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 0f (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 10 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 11 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 12 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 13 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 14 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 15 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 16 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 17 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 18 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,  // 19 (Letter selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_10, // 1a (Misc selection box for the sort by menu)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1,  // 1c (Bottom Menu Selection box?)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1,  // 1d (Bottom Menu Selection box?)
	SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1,  // 1e (Bottom Menu Selection box?)
#endif
};
    // LD_HL(SPRITEANIMSTRUCT_VAR1);
    // ADD_HL_BC;
    uint8_t a = 0, e = 0, d;
    const uint8_t* coords = NULL;
    switch(bc->var1) {
    //jumptable ['.Jumptable', 'hl']
    // Jumptable:
        case 0x0: //dw ['.zero'];
        // zero:
            // LD_A_addr(wcd20);
            // SLA_A;
            // LD_HL(mAnimateEZChatCursor_Coords_Zero);
            // LD_E(0x1);
            // goto load;
            // break;

        // .zero ; EZChat Message Menu
        // reinit sprite
            // ld a, [wEZChatSelection]
            // cp EZCHAT_MAIN_RESET
            // jr c, .zero_check_word
            if(wram->wEZChatSelection < EZCHAT_MAIN_RESET) {
            // .zero_check_word
                // call EZChatMenu_GetChosenWordSize
                uint8_t size = EZChatMenu_GetRealChosenWordSize(wram->wEZChatSelection);
                // and a
                // ret z
                if(size == 0)
                    return;
                // push bc
                // call PrepareEZChatCustomBox
                PrepareEZChatCustomBox();
                // pop bc
                // ld a, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_CUSTOM_BOX
                a = SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_CUSTOM_BOX;
            }
            else {
                // ld a, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1
                a = SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1;
                // jr .zero_sprite_anim_frame
            }
        // .zero_sprite_anim_frame
            // call ReinitSpriteAnimFrame
            ReinitSpriteAnimFrame_Conv(bc, a);
            // ld e, $1 ; Category Menu Index (?) (May be the priority of which the selection boxes appear (0 is highest))
            e = 0x1;
            // ld a, [wEZChatSelection]
            // cp EZCHAT_MAIN_RESET
            // jr nc, .use_base_coords
            if(wram->wEZChatSelection >= EZCHAT_MAIN_RESET) {
            // .use_base_coords
                // sub EZCHAT_MAIN_RESET
                // sla a
                a = (wram->wEZChatSelection - EZCHAT_MAIN_RESET) * 2;
                // ld hl, .Coords_Zero
                coords = Coords_Zero;
                // jr .load
            }
            else {
                // ld hl, wMobileBoxSpritePositionData
                coords = wram->wMobileBoxSpritePositionData;
                // sla a
                a = wram->wEZChatSelection * 2;
                // jr .load
            }
            break;
        case 0x1: //dw ['.one'];
        // one:
            // LD_A_addr(wcd21);
            // SLA_A;
            // LD_HL(mAnimateEZChatCursor_Coords_One);
            // LD_E(0x2);
            // goto load;
        // .one ; Category Menu
            // ld a, [wJumptableIndex]
            // ld e, $2 ; Sort by Letter Menu Index (?)
            e = 0x2;
            // cp EZCHAT_DRAW_CATEGORY_MENU
            // jr z, .continue_one
            // cp EZCHAT_MENU_CATEGORY_MENU
            // jr nz, .null_cursor_out
            if(wram->wJumptableIndex != EZCHAT_DRAW_CATEGORY_MENU 
            && wram->wJumptableIndex != EZCHAT_MENU_CATEGORY_MENU) {
            null_cursor_out:
                // ld a, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2
                // call ReinitSpriteAnimFrame
                ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
                // xor a
                a = 0;
                // ld hl, .coords_null
                coords = Coords_Null;
                // jp .load
                break;
            }
        // .continue_one
            // ld a, [wEZChatCategorySelection]
            // and $0f
            // cp EZCHAT_CATEGORY_CANC
            // push af
            // jr c, .not_menu
            if((wram->wEZChatCategorySelection & 0xf) >= EZCHAT_CATEGORY_CANC) {
                // ld a, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1
                // call ReinitSpriteAnimFrame
                ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1);
                // jr .got_sprite
            }
            else {
            // .not_menu
                // ld a, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2
                // call ReinitSpriteAnimFrame
                ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
            }
        // .got_sprite
            // pop af
            // sla a
            a = (wram->wEZChatCategorySelection & 0xf) * 2;
            // ld hl, .Coords_One
            coords = Coords_One;
            // ld e, $2 ; Sort by Letter Menu Index (?)
            e = 0x2;
            // jr .load
            break;
        case 0x2: //dw ['.two'];
        // two:
            // LD_HL(mAnimateEZChatCursor_FramesetsIDs_Two);
            // LD_A_addr(wcd22);
            // LD_E_A;
            // LD_D(0);
            // ADD_HL_DE;
            // LD_A_hl;
            // CALL(aReinitSpriteAnimFrame);

            // LD_A_addr(wcd22);
            // SLA_A;
            // LD_HL(mAnimateEZChatCursor_Coords_Two);
            // LD_E(0x4);
            // goto load;
        // .two ; Sort By Letter Menu
            // ld a, [wJumptableIndex]
            // ld e, $4 ; Yes/No Menu Index (?)
            e = 0x4;
            // cp EZCHAT_DRAW_SORT_BY_CHARACTER
            // jr z, .continue_two
            // cp EZCHAT_MENU_SORT_BY_CHARACTER
            // jr nz, .null_cursor_out
            if(wram->wJumptableIndex != EZCHAT_DRAW_CATEGORY_MENU 
            && wram->wJumptableIndex != EZCHAT_MENU_CATEGORY_MENU)
                goto null_cursor_out;
        // .continue_two
            // ld hl, .FramesetsIDs_Two
            // ld a, [wEZChatSortedSelection]
            // ld e, a
            // ld d, $0 ; Message Menu Index (?)
            // add hl, de
            // ld a, [hl]
            // call ReinitSpriteAnimFrame
            ReinitSpriteAnimFrame_Conv(bc, FramesetsIDs_Two[wram->wEZChatSortedSelection]);

            // ld a, [wEZChatSortedSelection]
            // sla a
            a = wram->wEZChatSortedSelection * 2;
            // ld hl, .Coords_Two
            coords = Coords_Two;
            // ld e, $4 ; Yes/No Menu Index (?)
            // jr .load
            break;
        case 0x3: //dw ['.three'];
        // three:
            // LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
            // CALL(aReinitSpriteAnimFrame);
            ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
            // LD_A_addr(wMobileCommsJumptableIndex);
            // SLA_A;
            a = wram->wEZChatWordSelection * 2;
            // LD_HL(mAnimateEZChatCursor_Coords_Three);
            coords = Coords_Three;
            // LD_E(0x8);
            e = 0x8;
            break;
        case 0x4: //dw ['.four'];
        // four:
            // LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
            // CALL(aReinitSpriteAnimFrame);
            ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
            // LD_A_addr(wcd2a);
            // SLA_A;
            a = wram->wcd2a * 2;
            // LD_HL(mAnimateEZChatCursor_Coords_Four);
            coords = Coords_Four;
            // LD_E(0x10);
            e = 0x10;
            // goto load;
            break;
        case 0x5: //dw ['.five'];
        // five:
            // LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
            // CALL(aReinitSpriteAnimFrame);
            ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
            // LD_A_addr(wcd2c);
            // SLA_A;
            a = wram->wcd2c * 2;
            // LD_HL(mAnimateEZChatCursor_Coords_Five);
            coords = Coords_Five;
            // LD_E(0x20);
            e = 0x20;
            // goto load;
            break;
        case 0x6: //dw ['.six'];
        // six:
            // LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_5);
            // CALL(aReinitSpriteAnimFrame);
            ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_5);
        // X = [wcd4a] * 8 + 24
            // LD_A_addr(wcd4a);
            // SLA_A;
            // SLA_A;
            // SLA_A;
            // ADD_A(0x18);
            // LD_HL(SPRITEANIMSTRUCT_XCOORD);
            // ADD_HL_BC;
            // LD_hli_A;
            bc->xCoord = (wram->wcd4a * 8) + 24;
        // Y = 48
            // LD_A(0x30);
            // LD_hl_A;
            bc->yCoord = 48;

            // LD_A(0x1);
            // LD_E_A;
            // CALL(aAnimateEZChatCursor_UpdateObjectFlags);
            AnimateEZChatCursor_UpdateObjectFlags(bc, 0x1, 0x1);
            // RET;
            return;
        case 0x7: { //dw ['.seven'];
        // seven:
            // LD_A_addr(wEZChatCursorYCoord);
            // CP_A(0x4);
            // IF_Z goto cursor0;
            // LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3);
            // goto got_frameset;

        // cursor0:
            // LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1);
            uint8_t frameset = (wram->wEZChatCursorYCoord == 0x4)
                ? SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1
                : SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3;

        // got_frameset:
            // CALL(aReinitSpriteAnimFrame);
            ReinitSpriteAnimFrame_Conv(bc, frameset);
            // LD_A_addr(wEZChatCursorYCoord);
            // CP_A(0x4);
            // IF_Z goto asm_11d1b1;
            if(wram->wEZChatCursorYCoord != 0x4) {
            // X = [wEZChatCursorXCoord] * 8 + 32
                // LD_A_addr(wEZChatCursorXCoord);
                // SLA_A;
                // SLA_A;
                // SLA_A;
                // ADD_A(0x20);
                // LD_HL(SPRITEANIMSTRUCT_XCOORD);
                // ADD_HL_BC;
                // LD_hli_A;
                bc->xCoord = wram->wEZChatCursorXCoord * 8 + 32;
            // Y = [wEZChatCursorYCoord] * 16 + 72
                // LD_A_addr(wEZChatCursorYCoord);
                // SLA_A;
                // SLA_A;
                // SLA_A;
                // SLA_A;
                // ADD_A(0x48);
                // LD_hl_A;
                bc->yCoord = wram->wEZChatCursorYCoord * 16 + 72;
                // LD_A(0x2);
                // LD_E_A;
                // CALL(aAnimateEZChatCursor_UpdateObjectFlags);
                AnimateEZChatCursor_UpdateObjectFlags(bc, 0x2, 0x2);
                // RET;
                return;
            }
            else {
            // asm_11d1b1:
            // X = [wEZChatCursorXCoord] * 40 + 24
                // LD_A_addr(wEZChatCursorXCoord);
                // SLA_A;
                // SLA_A;
                // SLA_A;
                // LD_E_A;
                // SLA_A;
                // SLA_A;
                // ADD_A_E;
                // ADD_A(0x18);uint16_t
                // LD_HL(SPRITEANIMSTRUCT_XCOORD);
                // ADD_HL_BC;
                // LD_hli_A;
                bc->xCoord = wram->wEZChatCursorXCoord * 40 + 24;
            // Y = 138
                // LD_A(0x8a);
                // LD_hl_A;
                bc->yCoord = 138;
                // LD_A(0x2);
                // LD_E_A;
                // CALL(aAnimateEZChatCursor_UpdateObjectFlags);
                AnimateEZChatCursor_UpdateObjectFlags(bc, 0x2, 0x2);
                // RET;
                return;
            }
        } break;
        case 0x8: //dw ['.eight'];
        // eight:
            // LD_D(2 * 8);
            d = 2 * 8;
            // LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_6);
            a = SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_6;
            goto eight_nine_load;
        case 0x9: //dw ['.nine'];
        // nine:
            // LD_D(-13 * 8);
            d = -13 * 8;
            // LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_7);
            a = SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_7;
            goto eight_nine_load;
        case 0xA: //dw ['.ten'];
        // ten:
            // LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1);
            // CALL(aReinitSpriteAnimFrame);
            ReinitSpriteAnimFrame_Conv(bc, SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1);
            // LD_A(0x8);
            // LD_E_A;
            // CALL(aAnimateEZChatCursor_UpdateObjectFlags);
            AnimateEZChatCursor_UpdateObjectFlags(bc, 0x8, 0x8);
            // RET;
            return;
    }

// load:
    // PUSH_DE;
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // PUSH_HL;
    // POP_DE;
    // LD_HL(SPRITEANIMSTRUCT_XCOORD);
    // ADD_HL_BC;
    // LD_A_de;
    // INC_DE;
    // LD_hli_A;
    bc->xCoord = coords[a + 0];
    // LD_A_de;
    // LD_hl_A;
    bc->yCoord = coords[a + 1];
    // POP_DE;
    // LD_A_E;
    // CALL(aAnimateEZChatCursor_UpdateObjectFlags);
    AnimateEZChatCursor_UpdateObjectFlags(bc, e, e);
    // RET;
    return;

eight_nine_load:
    // PUSH_DE;
    // CALL(aReinitSpriteAnimFrame);
    ReinitSpriteAnimFrame_Conv(bc, a);
    // LD_A_addr(wcd4a);
    // SLA_A;
    // SLA_A;
    // SLA_A;
    // LD_E_A;
    // SLA_A;
    // ADD_A_E;
    // ADD_A(8 * 8);
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_hld_A;
    bc->yCoord = (wram->wcd4a * 24) + 64;
    // POP_AF;
    // LD_hl_A;
    bc->xCoord = d;
    // LD_A(0x4);
    // LD_E_A;
    // CALL(aAnimateEZChatCursor_UpdateObjectFlags);
    AnimateEZChatCursor_UpdateObjectFlags(bc, 0x4, 0x4);
    // RET;
}

static void AnimateEZChatCursor_UpdateObjectFlags(struct SpriteAnim* bc, uint8_t a, uint8_t e){
    // LD_HL(wcd24);
    // AND_A_hl;
    // IF_NZ goto update_y_offset;
    if((wram->wEZChatSpritesMask & a) == 0) {
        // LD_A_E;
        // LD_HL(wcd23);
        // AND_A_hl;
        // IF_Z goto reset_y_offset;
        if((e & wram->wEZChatBlinkingMask) == 0)
            goto reset_y_offset;
        // LD_HL(SPRITEANIMSTRUCT_VAR3);
        // ADD_HL_BC;
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto flip_bit_0;
        if(bc->var3 != 0) {
            // DEC_hl;
            bc->var3--;
            // RET;
            return;
        }

    // flip_bit_0:
        // LD_A(0x0);
        // LD_hld_A;
        bc->var3 = 0x0;
        // LD_A(0x1);
        // XOR_A_hl;
        // LD_hl_A;
        bc->var2 ^= 0x1;
        // AND_A_A;
        // IF_NZ goto update_y_offset;
        if(bc->var2 == 0) {
        reset_y_offset:
            // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
            // ADD_HL_BC;
            // XOR_A_A;
            // LD_hl_A;
            bc->yOffset = 0x0;
            // RET;
            return;
        }
    }

// update_y_offset:
    // LD_HL(SPRITEANIMSTRUCT_YCOORD);
    // ADD_HL_BC;
    // LD_A(0xb0);
    // SUB_A_hl;
    // LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->yOffset = 0xb0 - bc->yCoord;
    // RET;
}

// EZChat_LoadPalette
void Function11d323(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x5);
    // LDH_addr_A(rSVBK);
    // LD_HL(mPalette_11d33a);
    // LD_DE(wBGPals1);
    // LD_BC(16 * PALETTE_SIZE);
    // CALL(aCopyBytes);
    CopyBytes(wram->wBGPals1, Palette_11d33a, 16 * PALETTE_SIZE);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

const uint16_t Palette_11d33a[] = {
    rgb(31, 31, 31),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(31, 16, 31),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(23, 17, 31),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(31, 31, 31),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(31, 31, 31),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(31, 31, 31),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(31, 31, 31),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(31, 31, 31),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),

    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
    rgb(00, 00, 00),
};

static bool EZChat_GetSeenPokemonByKana_CheckSeenMon(species_t a){
    // PUSH_HL;
    // PUSH_BC;
    // PUSH_DE;
    // DEC_A;
    // LD_HL(rSVBK);
    // LD_E(0x1);
    // LD_hl_E;
    // CALL(aCheckSeenMon);
    // LD_HL(rSVBK);
    // LD_E(0x5);
    // LD_hl_E;
    // POP_DE;
    // POP_BC;
    // POP_HL;
    // RET;
    return CheckSeenMon(a - 1);
}

void EZChat_GetSeenPokemonByKana(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_HL(wc648);
    // LD_A(LOW(w5_d800));
    // LD_addr_A(wcd2d);
    // LD_hli_A;
    // LD_A(HIGH(w5_d800));
    // LD_addr_A(wcd2e);
    uint8_t* wcd2d = wram->w5_d800;
    // LD_hl_A;
    gEZChatSortedWordPointers[0] = wram->w5_d800;
    uint8_t** words = gEZChatSortedWordPointers + 1;

    // LD_A(LOW(aEZChat_SortedPokemon));
    // LD_addr_A(wcd2f);
    // LD_A(HIGH(aEZChat_SortedPokemon));
    // LD_addr_A(wcd30);
    const species_t* const* wcd2f = EZChat_SortedPokemon;

    // LD_A(LOW(wc6a8));
    // LD_addr_A(wcd31);
    // LD_A(HIGH(wc6a8));
    // LD_addr_A(wcd32);
    uint8_t* wcd31 = wram->wc6a8;

    // LD_A(LOW(wc64a));
    // LD_addr_A(wcd33);
    // LD_A(HIGH(wc64a));
    // LD_addr_A(wcd34);

    // LD_HL(mEZChat_SortedWords);
    const u16_pair_s* hl = EZChat_SortedWords;
    // LD_A((EZChat_SortedWords.End - EZChat_SortedWords) / 4);
    uint8_t a = lengthof(EZChat_SortedWords);

    do {
    // MasterLoop:
        // PUSH_AF;
    //  read row
    //  offset
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        uint16_t offset = hl->a;
    //  size
        // LD_A_hli;
        // LD_C_A;
        // LD_A_hli;
        // LD_B_A;
        uint16_t size = hl->b;
    //  save the pointer to the next row
        // PUSH_HL;
        hl++;
    //  add de to w3_d000
        // LD_HL(w3_d000);
        // ADD_HL_DE;
        uint8_t* hl2 = wram->w3_d000 + (offset * 2);
    //  recover de from wcd2d (default: w5_d800)
        // LD_A_addr(wcd2d);
        // LD_E_A;
        // LD_A_addr(wcd2e);
        // LD_D_A;
        uint8_t* de = wcd2d;
    //  save bc for later
        // PUSH_BC;
        uint16_t bc = size;

        while(bc != 0) {
        // loop1:
        //  copy 2*bc bytes from 3:hl to 5:de
            // LD_A(0x3);
            // LDH_addr_A(rSVBK);
            // LD_A_hli;
            // PUSH_AF;
            // LD_A(0x5);
            // LDH_addr_A(rSVBK);
            // POP_AF;
            // LD_de_A;
            *(de++) = *(hl2++);
            // INC_DE;

            // LD_A(0x3);
            // LDH_addr_A(rSVBK);
            // LD_A_hli;
            // PUSH_AF;
            // LD_A(0x5);
            // LDH_addr_A(rSVBK);
            // POP_AF;
            // LD_de_A;
            // INC_DE;
            *(de++) = *(hl2++);

            // DEC_BC;
            --bc;
            // LD_A_C;
            // OR_A_B;
            // IF_NZ goto loop1;
        }

    //  recover the pointer from wcd2f (default: EZChat_SortedPokemon)
        // LD_A_addr(wcd2f);
        // LD_L_A;
        // LD_A_addr(wcd30);
        // LD_H_A;
    //  copy the pointer from [hl] to bc
        // LD_A_hli;
        // LD_C_A;
        // LD_A_hli;
        // LD_B_A;
        const species_t* sp = *(wcd2f++);
    //  store the pointer to the next pointer back in wcd2f
        // LD_A_L;
        // LD_addr_A(wcd2f);
        // LD_A_H;
        // LD_addr_A(wcd30);
    //  push pop that pointer to hl
        // PUSH_BC;
        // POP_HL;
        // LD_C(0x0);
        uint8_t c = 0x0;

        while(*sp != (species_t)-1) {
        // loop2:
        //  Have you seen this Pokemon?
            // LD_A_hl;
            // CP_A(0xff);
            // IF_Z goto done;
            // CALL(aEZChat_GetSeenPokemonByKana_CheckSeenMon);
            // IF_NZ goto next;
            if(EZChat_GetSeenPokemonByKana_CheckSeenMon(*sp)) {
            // next:
            //  If so, append it to the list at 5:de, and increase the count.
                // LD_A_hli;
                // LD_de_A;
                *(de++) = *sp;
                // INC_DE;
                // XOR_A_A;
                // LD_de_A;
                *de = 0;
                // INC_DE;
                de++;
                // INC_C;
                ++c;
                // goto loop2;
            }
        //  If not, skip it.
            // INC_HL;
            sp++;
            // goto loop2;
        }

    // done:
    //  Remember the original value of bc from the table?
    //  Well, the stack remembers it, and it's popping it to hl.
        // POP_HL;
    //  Add the number of seen Pokemon from the list.
        // LD_B(0x0);
        // ADD_HL_BC;
    //  Push pop to bc.
        // PUSH_HL;
        // POP_BC;
        size += c;
    //  Load the pointer from [wcd31] (default: wc6a8)
        // LD_A_addr(wcd31);
        // LD_L_A;
        // LD_A_addr(wcd32);
        // LD_H_A;
        uint8_t* hl3 = wcd31;
    //  Save the quantity from bc to [hl]
        // LD_A_C;
        // LD_hli_A;
        *(hl3++) = LOW(size);
        // LD_A_B;
        // LD_hli_A;
        *(hl3++) = HIGH(size);
    //  Save the new value of hl to [wcd31]
        // LD_A_L;
        // LD_addr_A(wcd31);
        // LD_A_H;
        // LD_addr_A(wcd32);
        wcd31 = hl3;
    //  Recover the pointer from [wcd33] (default: wc64a)
        // LD_A_addr(wcd33);
        // LD_L_A;
        // LD_A_addr(wcd34);
        // LD_H_A;
    //  Save the current value of de there
        // LD_A_E;
        // LD_addr_A(wcd2d);
        // LD_hli_A;
        // LD_A_D;
        // LD_addr_A(wcd2e);
        wcd2d = de;
        *(words++) = de; 
    //  Save the new value of hl back to [wcd33]
        // LD_hli_A;
        // LD_A_L;
        // LD_addr_A(wcd33);
        // LD_A_H;
        // LD_addr_A(wcd34);
    //  Next row
        // POP_HL;
        // POP_AF;
        // DEC_A;
        // IF_Z goto ExitMasterLoop;
        // JP(mEZChat_GetSeenPokemonByKana_MasterLoop);
    } while(--a != 0);

// ExitMasterLoop:
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;
}

void EZChat_GetCategoryWordsByKana(void){
    // LDH_A_addr(rSVBK);
    // PUSH_AF;
    // LD_A(0x3);
    // LDH_addr_A(rSVBK);

// load pointers
    // LD_HL(mMobileEZChatCategoryPointers);
    const ezchatword_s* const* hl = MobileEZChatCategoryPointers;
    // LD_BC(mMobileEZChatData_WordAndPageCounts);
    const u8_pair_s* bc = MobileEZChatData_WordAndPageCounts;

// init WRAM registers
    // XOR_A_A;
    // LD_addr_A(wcd2d);
    wram->wcd2d = 0x0;
    // INC_A;
    // LD_addr_A(wcd2e);
    wram->wcd2e = 0x1;

// enter the first loop
    // LD_A(14);
    uint8_t a1 = lengthof(MobileEZChatData_WordAndPageCounts);

    do {
    // loop1:
        // PUSH_AF;

    // load the pointer to the category
        // LD_A_hli;
        // LD_E_A;
        // LD_A_hli;
        // LD_D_A;
        const ezchatword_s* de = *(hl++);
        // PUSH_HL;

    // skip to the attributes
        // LD_HL(NAME_LENGTH_JAPANESE - 1);
        // ADD_HL_DE;

    // get the number of words in the category
        // LD_A_bc;  // number of entries to copy
        // INC_BC;
        // INC_BC;
        // PUSH_BC;
        uint8_t a2 = bc->a;
        bc++;

        do {
        // loop2:
            // PUSH_AF;
            // PUSH_HL;

        // load offset at [hl]
            // LD_A_hli;
            // LD_E_A;
            // LD_A_hl;
            // LD_D_A;

        // add to w3_d000
            // LD_HL(w3_d000);
            // ADD_HL_DE;

        // copy from wcd2d and increment [wcd2d] in place
            // LD_A_addr(wcd2d);
            // LD_hli_A;
            wram->wram3[de->start] = wram->wcd2d++;
            // INC_A;
            // LD_addr_A(wcd2d);

        // copy from wcd2e
            // LD_A_addr(wcd2e);
            // LD_hl_A;
            wram->wram3[de->start + 1] = wram->wcd2e;

        // next entry
            // POP_HL;
            // LD_DE(8);
            // ADD_HL_DE;
            de++;
            // POP_AF;
            // DEC_A;
            // IF_NZ goto loop2;
        } while(--a2 != 0);

    // reset and go to next category
        // LD_HL(wcd2d);
        // XOR_A_A;
        // LD_hli_A;
        wram->wcd2d = 0x0;
        // INC_hl;
        wram->wcd2e++;
        // POP_BC;
        // POP_HL;
        // POP_AF;
        // DEC_A;
        // IF_NZ goto loop1;
    } while(--a1 != 0);
    // POP_AF;
    // LDH_addr_A(rSVBK);
    // RET;

// INCLUDE "data/pokemon/ezchat_order.asm"
}

const char SelectStartGFX[] = "gfx/mobile/select_start.png";

const char EZChatSlowpokeLZ[] = "gfx/pokedex/slowpoke_mobile.png";

//  entries correspond to EZCHAT_* constants
const char* const MobileEZChatCategoryNames[] = {
    [EZCHAT_POKEMON]        = "POKéMON@",   //db ['"ポケモン@@"'];  // 00
    [EZCHAT_TYPES]          = "TYPES@",     //db ['"タイプ@@@"'];  // 01
    [EZCHAT_GREETINGS]      = "GREETINGS@", //db ['"あいさつ@@"'];  // 02
    [EZCHAT_PEOPLE]         = "PEOPLE@",    //db ['"ひと@@@@"'];  // 03
    [EZCHAT_BATTLE]         = "BATTLE@",    //db ['"バトル@@@"'];  // 04
    [EZCHAT_EXCLAMATIONS]   = "VOICES@",    //db ['"こえ@@@@"'];  // 05
    [EZCHAT_CONVERSATION]   = "SPEECH@",    //db ['"かいわ@@@"'];  // 06
    [EZCHAT_FEELINGS]       = "FEELINGS@",  //db ['"きもち@@@"'];  // 07
    [EZCHAT_CONDITIONS]     = "CONDITION@", //db ['"じょうたい@"'];  // 08
    [EZCHAT_LIFE]           = "LIFESTYLE@", //db ['"せいかつ@@"'];  // 09
    [EZCHAT_HOBBIES]        = "HOBBIES@",   //db ['"しゅみ@@@"'];  // 0a
    [EZCHAT_ACTIONS]        = "ACTIONS@",   //db ['"こうどう@@"'];  // 0b
    [EZCHAT_TIME]           = "TIME@@",     //db ['"じかん@@@"'];  // 0c
    [EZCHAT_FAREWELLS]      = "ENDINGS@@",  //db ['"むすび@@@"'];  // 0d
    [EZCHAT_THISANDTHAT]    = "MISC.@",     //db ['"あれこれ@@"'];  // 0e
};

#define ezchat_word(_w, _x) {.word = _w, .start = _x}

const ezchatword_s MobileEZChatCategoryPointers_Types[] = {
    ezchat_word("DARK@@@@", 0x10e), //db ['"あく@@@"', '0x26', '0x0', '0x0'];
    ezchat_word("ROCK@@@@", 0x3fc), //db ['"いわ@@@"', '0xaa', '0x0', '0x0'];
    ezchat_word("PSYCHIC@", 0x3d8), //db ['"エスパー@"', '0xda', '0x0', '0x0'];
    ezchat_word("FIGHTING", 0x1a0), //db ['"かくとう@"', '0x4e', '0x1', '0x0'];
    ezchat_word("GRASS@@@", 0x20e), //db ['"くさ@@@"', '0xba', '0x1', '0x0'];
    ezchat_word("GHOST@@@", 0x1d8), //db ['"ゴースト@"', '0xe4', '0x1', '0x0'];
    ezchat_word("ICE@@@@@", 0x294), //db ['"こおり@@"', '0xe6', '0x1', '0x0'];
    ezchat_word("GROUND@@", 0x214), //db ['"じめん@@"', '0x68', '0x2', '0x0'];
    ezchat_word("TYPE@@@@", 0x518), //db ['"タイプ@@"', '0xe8', '0x2', '0x0'];
    ezchat_word("ELECTRIC", 0x15c), //db ['"でんき@@"', '0x8e', '0x3', '0x0'];
    ezchat_word("POISON@@", 0x3c8), //db ['"どく@@@"', '0xae', '0x3', '0x0'];
    ezchat_word("DRAGON@@", 0x144), //db ['"ドラゴン@"', '0xbc', '0x3', '0x0'];
    ezchat_word("NORMAL@@", 0x370), //db ['"ノーマル@"', '0x22', '0x4', '0x0'];
    ezchat_word("STEEL@@@", 0x474), //db ['"はがね@@"', '0x36', '0x4', '0x0'];
    ezchat_word("FLYING@@", 0x1b2), //db ['"ひこう@@"', '0x5e', '0x4', '0x0'];
    ezchat_word("FIRE@@@@", 0x1a8), //db ['"ほのお@@"', '0xb2', '0x4', '0x0'];
    ezchat_word("WATER@@@", 0x558), //db ['"みず@@@"', '0xf4', '0x4', '0x0'];
    ezchat_word("BUG@@@@@", 0x0b0), //db ['"むし@@@"', '0x12', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Greetings[] = {
    ezchat_word("THANKYOU", 0x4aa), //db ['"ありがと@"', '0x58', '0x0', '0x0'];
    ezchat_word("THANKS@@", 0x4a8), //db ['"ありがとう"', '0x5a', '0x0', '0x0'];
    ezchat_word("LETS GO!", 0x2d8), //db ['"いくぜ！@"', '0x80', '0x0', '0x0'];
    ezchat_word("GO ON!@@", 0x1f2), //db ['"いくよ！@"', '0x82', '0x0', '0x0'];
    ezchat_word("DO IT!@@", 0x134), //db ['"いくわよ！"', '0x84', '0x0', '0x0'];
    ezchat_word("YEAH@@@@", 0x5be), //db ['"いやー@@"', '0xa6', '0x0', '0x0'];
    ezchat_word("HOW DO@@", 0x278), //db ['"おっす@@"', '0xa', '0x1', '0x0'];
    ezchat_word("HOWDY!@@", 0x27a), //db ['"おはつです"', '0x22', '0x1', '0x0'];
    ezchat_word("CONGRATS", 0x0ee), //db ['"おめでとう"', '0x2a', '0x1', '0x0'];
    ezchat_word("SORRY@@@", 0x468), //db ['"ごめん@@"', '0xf8', '0x1', '0x0'];
    ezchat_word("SORRY!@@", 0x46a), //db ['"ごめんよ@"', '0xfa', '0x1', '0x0'];
    ezchat_word("HI THERE", 0x250), //db ['"こらっ@@"', '0xfc', '0x1', '0x0'];
    ezchat_word("HI!@@@@@", 0x252), //db ['"こんちは！"', '0xa', '0x2', '0x0'];
    ezchat_word("HELLO@@@", 0x23e), //db ['"こんにちは"', '0x10', '0x2', '0x0'];
    ezchat_word("GOOD-BYE", 0x1fe), //db ['"さようなら"', '0x28', '0x2', '0x0'];
    ezchat_word("CHEERS@@", 0x0d2), //db ['"サンキュー"', '0x2e', '0x2', '0x0'];
    ezchat_word("I'M HERE", 0x290), //db ['"さんじょう"', '0x30', '0x2', '0x0'];
    ezchat_word("PARDON@@", 0x3aa), //db ['"しっけい@"', '0x48', '0x2', '0x0'];
    ezchat_word("EXCUSE@@", 0x17e), //db ['"しつれい@"', '0x4c', '0x2', '0x0'];
    ezchat_word("SEE YA@@", 0x416), //db ['"じゃーね@"', '0x6c', '0x2', '0x0'];
    ezchat_word("YO!@@@@@", 0x5c6), //db ['"すいません"', '0x8c', '0x2', '0x0'];
    ezchat_word("WELL…@@@", 0x56e), //db ['"それじゃ@"', '0xca', '0x2', '0x0'];
    ezchat_word("GRATEFUL", 0x210), //db ['"どうも@@"', '0xa6', '0x3', '0x0'];
    ezchat_word("WASSUP?@", 0x556), //db ['"なんじゃ@"', '0xee', '0x3', '0x0'];
    ezchat_word("HI@@@@@@", 0x24e), //db ['"ハーイ@@"', '0x2c', '0x4', '0x0'];
    ezchat_word("YEA, YEA", 0x5bc), //db ['"はいはい@"', '0x32', '0x4', '0x0'];
    ezchat_word("BYE-BYE@", 0x0b6), //db ['"バイバイ@"', '0x34', '0x4', '0x0'];
    ezchat_word("HEY@@@@@", 0x24a), //db ['"へイ@@@"', '0x8a', '0x4', '0x0'];
    ezchat_word("SMELL@@@", 0x452), //db ['"またね@@"', '0xde', '0x4', '0x0'];
    ezchat_word("TUNED IN", 0x514), //db ['"もしもし@"', '0x32', '0x5', '0x0'];
    ezchat_word("HOO-HAH@", 0x272), //db ['"やあ@@@"', '0x3e', '0x5', '0x0'];
    ezchat_word("YAHOO@@@", 0x5b8), //db ['"やっほー@"', '0x4e', '0x5', '0x0'];
    ezchat_word("YO@@@@@@", 0x5c4), //db ['"よう@@@"', '0x62', '0x5', '0x0'];
    ezchat_word("GO OVER@", 0x1f4), //db ['"ようこそ@"', '0x64', '0x5', '0x0'];
    ezchat_word("COUNT ON", 0x0fc), //db ['"よろしく@"', '0x80', '0x5', '0x0'];
    ezchat_word("WELCOME@", 0x56a), //db ['"らっしゃい"', '0x94', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_People[] = {
    ezchat_word("OPPONENT", 0x398), //db ['"あいて@@"', '0x1c', '0x0', '0x0'];
    ezchat_word("I@@@@@@@", 0x284), //db ['"あたし@@"', '0x36', '0x0', '0x0'];
    ezchat_word("YOU@@@@@", 0x5c8), //db ['"あなた@@"', '0x40', '0x0', '0x0'];
    ezchat_word("YOURS@@@", 0x5d2), //db ['"あなたが@"', '0x42', '0x0', '0x0'];
    ezchat_word("SON@@@@@", 0x462), //db ['"あなたに@"', '0x44', '0x0', '0x0'];
    ezchat_word("YOUR@@@@", 0x5d0), //db ['"あなたの@"', '0x46', '0x0', '0x0'];
    ezchat_word("YOU'RE@@", 0x5cc), //db ['"あなたは@"', '0x48', '0x0', '0x0'];
    ezchat_word("YOU'VE@@", 0x5ce), //db ['"あなたを@"', '0x4a', '0x0', '0x0'];
    ezchat_word("MOTHER@@", 0x330), //db ['"おかあさん"', '0xe8', '0x0', '0x0'];
    ezchat_word("GRANDPA@", 0x20c), //db ['"おじいさん"', '0xfc', '0x0', '0x0'];
    ezchat_word("UNCLE@@@", 0x522), //db ['"おじさん@"', '0x2', '0x1', '0x0'];
    ezchat_word("FATHER@@", 0x196), //db ['"おとうさん"', '0xe', '0x1', '0x0'];
    ezchat_word("BOY@@@@@", 0x0aa), //db ['"おとこのこ"', '0x10', '0x1', '0x0'];
    ezchat_word("ADULT@@@", 0x026), //db ['"おとな@@"', '0x14', '0x1', '0x0'];
    ezchat_word("BROTHER@", 0x0ae), //db ['"おにいさん"', '0x16', '0x1', '0x0'];
    ezchat_word("SISTER@@", 0x442), //db ['"おねえさん"', '0x18', '0x1', '0x0'];
    ezchat_word("GRANDMA@", 0x20a), //db ['"おばあさん"', '0x1c', '0x1', '0x0'];
    ezchat_word("AUNT@@@@", 0x06e), //db ['"おばさん@"', '0x20', '0x1', '0x0'];
    ezchat_word("ME@@@@@@", 0x30c), //db ['"おれさま@"', '0x34', '0x1', '0x0'];
    ezchat_word("GIRL@@@@", 0x1e0), //db ['"おんなのこ"', '0x3a', '0x1', '0x0'];
    ezchat_word("BABE@@@@", 0x07a), //db ['"ガール@@"', '0x40', '0x1', '0x0'];
    ezchat_word("FAMILY@@", 0x18e), //db ['"かぞく@@"', '0x52', '0x1', '0x0'];
    ezchat_word("HER@@@@@", 0x240), //db ['"かのじょ@"', '0x72', '0x1', '0x0'];
    ezchat_word("HIM@@@@@", 0x25a), //db ['"かれ@@@"', '0x7c', '0x1', '0x0'];
    ezchat_word("HE@@@@@@", 0x22c), //db ['"きみ@@@"', '0x9a', '0x1', '0x0'];
    ezchat_word("PLACE@@@", 0x3b8), //db ['"きみが@@"', '0x9c', '0x1', '0x0'];
    ezchat_word("DAUGHTER", 0x114), //db ['"きみに@@"', '0x9e', '0x1', '0x0'];
    ezchat_word("HIS@@@@@", 0x25c), //db ['"きみの@@"', '0xa0', '0x1', '0x0'];
    ezchat_word("HE'S@@@@", 0x22e), //db ['"きみは@@"', '0xa2', '0x1', '0x0'];
    ezchat_word("AREN'T@@", 0x060), //db ['"きみを@@"', '0xa4', '0x1', '0x0'];
    ezchat_word("GAL@@@@@", 0x1d0), //db ['"ギャル@@"', '0xae', '0x1', '0x0'];
    ezchat_word("SIBLINGS", 0x43a), //db ['"きょうだい"', '0xb2', '0x1', '0x0'];
    ezchat_word("CHILDREN", 0x0d6), //db ['"こども@@"', '0xf0', '0x1', '0x0'];
    ezchat_word("MYSELF@@", 0x344), //db ['"じぶん@@"', '0x54', '0x2', '0x0'];
    ezchat_word("I WAS@@@", 0x28a), //db ['"じぶんが@"', '0x56', '0x2', '0x0'];
    ezchat_word("TO ME@@@", 0x4e0), //db ['"じぶんに@"', '0x58', '0x2', '0x0'];
    ezchat_word("MY@@@@@@", 0x342), //db ['"じぶんの@"', '0x5a', '0x2', '0x0'];
    ezchat_word("I AM@@@@", 0x286), //db ['"じぶんは@"', '0x5c', '0x2', '0x0'];
    ezchat_word("I'VE@@@@", 0x292), //db ['"じぶんを@"', '0x5e', '0x2', '0x0'];
    ezchat_word("WHO@@@@@", 0x580), //db ['"だれ@@@"', '0x18', '0x3', '0x0'];
    ezchat_word("SOMEONE@", 0x45e), //db ['"だれか@@"', '0x1a', '0x3', '0x0'];
    ezchat_word("WHO WAS@", 0x584), //db ['"だれが@@"', '0x1c', '0x3', '0x0'];
    ezchat_word("TO WHOM@", 0x4e6), //db ['"だれに@@"', '0x1e', '0x3', '0x0'];
    ezchat_word("WHOSE@@@", 0x58a), //db ['"だれの@@"', '0x20', '0x3', '0x0'];
    ezchat_word("WHO IS@@", 0x582), //db ['"だれも@@"', '0x22', '0x3', '0x0'];
    ezchat_word("IT'S@@@@", 0x2b0), //db ['"だれを@@"', '0x24', '0x3', '0x0'];
    ezchat_word("LADY@@@@", 0x2c4), //db ['"ちゃん@@"', '0x38', '0x3', '0x0'];
    ezchat_word("FRIEND@@", 0x1c4), //db ['"ともだち@"', '0xb8', '0x3', '0x0'];
    ezchat_word("ALLY@@@@", 0x034), //db ['"なかま@@"', '0xd4', '0x3', '0x0'];
    ezchat_word("PERSON@@", 0x3b4), //db ['"ひと@@@"', '0x62', '0x4', '0x0'];
    ezchat_word("DUDE@@@@", 0x14c), //db ['"ボーイ@@"', '0x98', '0x4', '0x0'];
    ezchat_word("THEY@@@@", 0x4be), //db ['"ボク@@@"', '0xa0', '0x4', '0x0'];
    ezchat_word("THEY ARE", 0x4c0), //db ['"ボクが@@"', '0xa2', '0x4', '0x0'];
    ezchat_word("TO THEM@", 0x4e2), //db ['"ボクに@@"', '0xa4', '0x4', '0x0'];
    ezchat_word("THEIR@@@", 0x4b8), //db ['"ボクの@@"', '0xa6', '0x4', '0x0'];
    ezchat_word("THEY'RE@", 0x4c2), //db ['"ボクは@@"', '0xa8', '0x4', '0x0'];
    ezchat_word("THEY'VE@", 0x4c4), //db ['"ボクを@@"', '0xaa', '0x4', '0x0'];
    ezchat_word("WE@@@@@@", 0x55c), //db ['"みんな@@"', '0x4', '0x5', '0x0'];
    ezchat_word("BEEN@@@@", 0x08c), //db ['"みんなが@"', '0x6', '0x5', '0x0'];
    ezchat_word("TO US@@@", 0x4e4), //db ['"みんなに@"', '0x8', '0x5', '0x0'];
    ezchat_word("OUR@@@@@", 0x39e), //db ['"みんなの@"', '0xa', '0x5', '0x0'];
    ezchat_word("WE'RE@@@", 0x55e), //db ['"みんなは@"', '0xc', '0x5', '0x0'];
    ezchat_word("RIVAL@@@", 0x3fa), //db ['"ライバル@"', '0x8a', '0x5', '0x0'];
    ezchat_word("SHE@@@@@", 0x426), //db ['"わたし@@"', '0xc2', '0x5', '0x0'];
    ezchat_word("SHE WAS@", 0x42a), //db ['"わたしが@"', '0xc4', '0x5', '0x0'];
    ezchat_word("TO HER@@", 0x4de), //db ['"わたしに@"', '0xc6', '0x5', '0x0'];
    ezchat_word("HERS@@@@", 0x248), //db ['"わたしの@"', '0xc8', '0x5', '0x0'];
    ezchat_word("SHE IS@@", 0x428), //db ['"わたしは@"', '0xca', '0x5', '0x0'];
    ezchat_word("SOME@@@@", 0x45a), //db ['"わたしを@"', '0xcc', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Battle[] = {
    ezchat_word("MATCH UP", 0x308), //db ['"あいしょう"', '0x18', '0x0', '0x0'];
    ezchat_word("GO!@@@@@", 0x1f6), //db ['"いけ！@@"', '0x88', '0x0', '0x0'];
    ezchat_word("NO. 1@@@", 0x368), //db ['"いちばん@"', '0x96', '0x0', '0x0'];
    ezchat_word("DECIDE@@", 0x120), //db ['"かくご@@"', '0x4c', '0x1', '0x0'];
    ezchat_word("I WIN@@@", 0x28c), //db ['"かたせて@"', '0x54', '0x1', '0x0'];
    ezchat_word("WINS@@@@", 0x594), //db ['"かち@@@"', '0x56', '0x1', '0x0'];
    ezchat_word("WIN@@@@@", 0x592), //db ['"かつ@@@"', '0x58', '0x1', '0x0'];
    ezchat_word("WON@@@@@", 0x59e), //db ['"かった@@"', '0x60', '0x1', '0x0'];
    ezchat_word("IF I WIN", 0x29a), //db ['"かったら@"', '0x62', '0x1', '0x0'];
    ezchat_word("I'LL WIN", 0x28e), //db ['"かって@@"', '0x64', '0x1', '0x0'];
    ezchat_word("CANT WIN", 0x0be), //db ['"かてない@"', '0x66', '0x1', '0x0'];
    ezchat_word("CAN WIN@", 0x0ba), //db ['"かてる@@"', '0x68', '0x1', '0x0'];
    ezchat_word("NO MATCH", 0x364), //db ['"かなわない"', '0x70', '0x1', '0x0'];
    ezchat_word("SPIRIT@@", 0x46c), //db ['"きあい@@"', '0x84', '0x1', '0x0'];
    ezchat_word("DECIDED@", 0x122), //db ['"きめた@@"', '0xa8', '0x1', '0x0'];
    ezchat_word("ACE CARD", 0x022), //db ['"きりふだ@"', '0xb6', '0x1', '0x0'];
    ezchat_word("HI-YA!@@", 0x254), //db ['"くらえ@@"', '0xc2', '0x1', '0x0'];
    ezchat_word("COME ON@", 0x0e8), //db ['"こい！@@"', '0xda', '0x1', '0x0'];
    ezchat_word("ATTACK@@", 0x06c), //db ['"こうげき@"', '0xe0', '0x1', '0x0'];
    ezchat_word("GIVE UP@", 0x1e4), //db ['"こうさん@"', '0xe2', '0x1', '0x0'];
    ezchat_word("GUTS@@@@", 0x21a), //db ['"こんじょう"', '0x8', '0x2', '0x0'];
    ezchat_word("TALENT@@", 0x492), //db ['"さいのう@"', '0x16', '0x2', '0x0'];
    ezchat_word("STRATEGY", 0x47a), //db ['"さくせん@"', '0x1a', '0x2', '0x0'];
    ezchat_word("SMITE@@@", 0x454), //db ['"さばき@@"', '0x22', '0x2', '0x0'];
    ezchat_word("MATCH@@@", 0x306), //db ['"しょうぶ@"', '0x7e', '0x2', '0x0'];
    ezchat_word("VICTORY@", 0x53c), //db ['"しょうり@"', '0x80', '0x2', '0x0'];
    ezchat_word("OFFENSE@", 0x37e), //db ['"せめ@@@"', '0xb4', '0x2', '0x0'];
    ezchat_word("SENSE@@@", 0x420), //db ['"センス@@"', '0xb6', '0x2', '0x0'];
    ezchat_word("VERSUS@@", 0x538), //db ['"たいせん@"', '0xe6', '0x2', '0x0'];
    ezchat_word("FIGHTS@@", 0x1a2), //db ['"たたかい@"', '0xf6', '0x2', '0x0'];
    ezchat_word("POWER@@@", 0x3ce), //db ['"ちから@@"', '0x32', '0x3', '0x0'];
    ezchat_word("TASK@@@@", 0x494), //db ['"チャレンジ"', '0x36', '0x3', '0x0'];
    ezchat_word("STRONG@@", 0x47c), //db ['"つよい@@"', '0x58', '0x3', '0x0'];
    ezchat_word("TOO MUCH", 0x4f2), //db ['"つよすぎ@"', '0x5a', '0x3', '0x0'];
    ezchat_word("HARD@@@@", 0x224), //db ['"つらい@@"', '0x5c', '0x3', '0x0'];
    ezchat_word("TERRIBLE", 0x4a0), //db ['"つらかった"', '0x5e', '0x3', '0x0'];
    ezchat_word("GO EASY@", 0x1ee), //db ['"てかげん@"', '0x6c', '0x3', '0x0'];
    ezchat_word("FOE@@@@@", 0x1b4), //db ['"てき@@@"', '0x6e', '0x3', '0x0'];
    ezchat_word("GENIUS@@", 0x1d4), //db ['"てんさい@"', '0x90', '0x3', '0x0'];
    ezchat_word("LEGEND@@", 0x2d0), //db ['"でんせつ@"', '0x94', '0x3', '0x0'];
    ezchat_word("TRAINER@", 0x502), //db ['"トレーナー"', '0xc6', '0x3', '0x0'];
    ezchat_word("ESCAPE@@", 0x16e), //db ['"にげ@@@"', '0x4', '0x4', '0x0'];
    ezchat_word("LUKEWARM", 0x2fc), //db ['"ぬるい@@"', '0x10', '0x4', '0x0'];
    ezchat_word("AIM@@@@@", 0x02e), //db ['"ねらう@@"', '0x16', '0x4', '0x0'];
    ezchat_word("BATTLE@@", 0x084), //db ['"バトル@@"', '0x4a', '0x4', '0x0'];
    ezchat_word("FIGHT@@@", 0x19e), //db ['"ファイト@"', '0x72', '0x4', '0x0'];
    ezchat_word("REVIVE@@", 0x3f8), //db ['"ふっかつ@"', '0x78', '0x4', '0x0'];
    ezchat_word("POINTS@@", 0x3c6), //db ['"ポイント@"', '0x94', '0x4', '0x0'];
    ezchat_word("POKéMON@", 0x3ca), //db ['"ポケモン@"', '0xac', '0x4', '0x0'];
    ezchat_word("SERIOUS@", 0x422), //db ['"ほんき@@"', '0xbc', '0x4', '0x0'];
    ezchat_word("OH NO!@@", 0x382), //db ['"まいった！"', '0xc4', '0x4', '0x0'];
    ezchat_word("LOSS@@@@", 0x2f2), //db ['"まけ@@@"', '0xc8', '0x4', '0x0'];
    ezchat_word("YOU LOSE", 0x5ca), //db ['"まけたら@"', '0xca', '0x4', '0x0'];
    ezchat_word("LOST@@@@", 0x2f4), //db ['"まけて@@"', '0xcc', '0x4', '0x0'];
    ezchat_word("LOSE@@@@", 0x2f0), //db ['"まける@@"', '0xce', '0x4', '0x0'];
    ezchat_word("GUARD@@@", 0x218), //db ['"まもり@@"', '0xea', '0x4', '0x0'];
    ezchat_word("PARTNER@", 0x3ac), //db ['"みかた@@"', '0xf2', '0x4', '0x0'];
    ezchat_word("REJECT@@", 0x3f2), //db ['"みとめない"', '0xfe', '0x4', '0x0'];
    ezchat_word("ACCEPT@@", 0x020), //db ['"みとめる@"', '0x0', '0x5', '0x0'];
    ezchat_word("UNBEATEN", 0x520), //db ['"むてき@@"', '0x16', '0x5', '0x0'];
    ezchat_word("GOT IT!@", 0x202), //db ['"もらった！"', '0x3c', '0x5', '0x0'];
    ezchat_word("EASY@@@@", 0x150), //db ['"よゆう@@"', '0x7a', '0x5', '0x0'];
    ezchat_word("WEAK@@@@", 0x560), //db ['"よわい@@"', '0x82', '0x5', '0x0'];
    ezchat_word("TOO WEAK", 0x4f4), //db ['"よわすぎ@"', '0x84', '0x5', '0x0'];
    ezchat_word("PUSHOVER", 0x3da), //db ['"らくしょう"', '0x8e', '0x5', '0x0'];
    ezchat_word("CHIEF@@@", 0x0d4), //db ['"りーダー@"', '0x9e', '0x5', '0x0'];
    ezchat_word("RULE@@@@", 0x400), //db ['"ルール@@"', '0xa0', '0x5', '0x0'];
    ezchat_word("LEVEL@@@", 0x2da), //db ['"レべル@@"', '0xa6', '0x5', '0x0'];
    ezchat_word("MOVE@@@@", 0x332), //db ['"わざ@@@"', '0xbe', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Exclamations[] = {
    ezchat_word("!?@@@@@@", 0x004), //db ['"！@@@@"', '0x0', '0x0', '0x0'];
    ezchat_word("!@@@@@@@", 0x000), //db ['"！！@@@"', '0x2', '0x0', '0x0'];
    ezchat_word("!!@@@@@@", 0x002), //db ['"！？@@@"', '0x4', '0x0', '0x0'];
    ezchat_word("?!@@@@@@", 0x012), //db ['"？@@@@"', '0x6', '0x0', '0x0'];
    ezchat_word("?@@@@@@@", 0x010), //db ['"⋯@@@@"', '0x8', '0x0', '0x0'];
    ezchat_word("…!@@@@@@", 0x00c), //db ['"⋯！@@@"', '0xa', '0x0', '0x0'];
    ezchat_word("………@@@@@", 0x00e), //db ['"⋯⋯⋯@@"', '0xc', '0x0', '0x0'];
    ezchat_word("-@@@@@@@", 0x006), //db ['"ー@@@@"', '0xe', '0x0', '0x0'];
    ezchat_word("- - -@@@", 0x008), //db ['"ーーー@@"', '0x10', '0x0', '0x0'];
    ezchat_word("UH-OH@@@", 0x51c), //db ['"あーあ@@"', '0x14', '0x0', '0x0'];
    ezchat_word("WAAAH@@@", 0x53e), //db ['"あーん@@"', '0x16', '0x0', '0x0'];
    ezchat_word("AHAHA@@@", 0x02c), //db ['"あははー@"', '0x52', '0x0', '0x0'];
    ezchat_word("OH?@@@@@", 0x388), //db ['"あら@@@"', '0x54', '0x0', '0x0'];
    ezchat_word("NOPE@@@@", 0x36e), //db ['"いえ@@@"', '0x72', '0x0', '0x0'];
    ezchat_word("YES@@@@@", 0x5c0), //db ['"イエス@@"', '0x74', '0x0', '0x0'];
    ezchat_word("URGH@@@@", 0x52a), //db ['"うう@@@"', '0xac', '0x0', '0x0'];
    ezchat_word("HMM@@@@@", 0x264), //db ['"うーん@@"', '0xae', '0x0', '0x0'];
    ezchat_word("WHOAH@@@", 0x586), //db ['"うおー！@"', '0xb0', '0x0', '0x0'];
    ezchat_word("WROOAAR!", 0x5b2), //db ['"うおりゃー"', '0xb2', '0x0', '0x0'];
    ezchat_word("WOW@@@@@", 0x5ae), //db ['"うひょー@"', '0xbc', '0x0', '0x0'];
    ezchat_word("GIGGLE@@", 0x1dc), //db ['"うふふ@@"', '0xbe', '0x0', '0x0'];
    ezchat_word("SHOCKING", 0x430), //db ['"うわー@@"', '0xca', '0x0', '0x0'];
    ezchat_word("CRIES@@@", 0x0fe), //db ['"うわーん@"', '0xcc', '0x0', '0x0'];
    ezchat_word("AGREE@@@", 0x02a), //db ['"ええ@@@"', '0xd2', '0x0', '0x0'];
    ezchat_word("EH?@@@@@", 0x158), //db ['"えー@@@"', '0xd4', '0x0', '0x0'];
    ezchat_word("CRY@@@@@", 0x102), //db ['"えーん@@"', '0xd6', '0x0', '0x0'];
    ezchat_word("EHEHE@@@", 0x15a), //db ['"えへへ@@"', '0xdc', '0x0', '0x0'];
    ezchat_word("HOLD ON!", 0x26c), //db ['"おいおい@"', '0xe0', '0x0', '0x0'];
    ezchat_word("OH YEAH@", 0x384), //db ['"おお@@@"', '0xe2', '0x0', '0x0'];
    ezchat_word("OOPS@@@@", 0x396), //db ['"おっと@@"', '0xc', '0x1', '0x0'];
    ezchat_word("SHOCKED@", 0x42e), //db ['"がーん@@"', '0x42', '0x1', '0x0'];
    ezchat_word("EEK@@@@@", 0x156), //db ['"キャー@@"', '0xaa', '0x1', '0x0'];
    ezchat_word("GRAAAH@@", 0x208), //db ['"ギャー@@"', '0xac', '0x1', '0x0'];
    ezchat_word("HE-HE-HE", 0x230), //db ['"ぐふふふふ"', '0xbc', '0x1', '0x0'];
    ezchat_word("WAY@@@@@", 0x55a), //db ['"げっ@@@"', '0xce', '0x1', '0x0'];
    ezchat_word("SADLY@@@", 0x408), //db ['"しくしく@"', '0x3e', '0x2', '0x0'];
    ezchat_word("HMPH@@@@", 0x266), //db ['"ちえっ@@"', '0x2e', '0x3', '0x0'];
    ezchat_word("HEHE@@@@", 0x23a), //db ['"てへ@@@"', '0x86', '0x3', '0x0'];
    ezchat_word("NO@@@@@@", 0x362), //db ['"ノー@@@"', '0x20', '0x4', '0x0'];
    ezchat_word("HUH?@@@@", 0x27e), //db ['"はあー@@"', '0x2a', '0x4', '0x0'];
    ezchat_word("YUP@@@@@", 0x5d4), //db ['"はい@@@"', '0x30', '0x4', '0x0'];
    ezchat_word("HAHAHA@@", 0x21e), //db ['"はっはっは"', '0x48', '0x4', '0x0'];
    ezchat_word("AIYEEH@@", 0x030), //db ['"ひいー@@"', '0x56', '0x4', '0x0'];
    ezchat_word("HIYAH@@@", 0x260), //db ['"ひゃあ@@"', '0x6a', '0x4', '0x0'];
    ezchat_word("FUFUFU@@", 0x1c8), //db ['"ふっふっふ"', '0x7c', '0x4', '0x0'];
    ezchat_word("MUTTER@@", 0x340), //db ['"ふにゃ@@"', '0x7e', '0x4', '0x0'];
    ezchat_word("LOL@@@@@", 0x2ea), //db ['"ププ@@@"', '0x80', '0x4', '0x0'];
    ezchat_word("SNORT@@@", 0x456), //db ['"ふふん@@"', '0x82', '0x4', '0x0'];
    ezchat_word("HUMPH@@@", 0x280), //db ['"ふん@@@"', '0x88', '0x4', '0x0'];
    ezchat_word("HEHEHE@@", 0x23c), //db ['"へっへっへ"', '0x8e', '0x4', '0x0'];
    ezchat_word("BLUSH@@@", 0x0a0), //db ['"へへー@@"', '0x90', '0x4', '0x0'];
    ezchat_word("HOHOHO@@", 0x26a), //db ['"ほーほほほ"', '0x9c', '0x4', '0x0'];
    ezchat_word("UH-HUH@@", 0x51a), //db ['"ほら@@@"', '0xb6', '0x4', '0x0'];
    ezchat_word("OH, DEAR", 0x380), //db ['"まあ@@@"', '0xc0', '0x4', '0x0'];
    ezchat_word("ARRGH!@@", 0x064), //db ['"むきー！！"', '0x10', '0x5', '0x0'];
    ezchat_word("MUFU@@@@", 0x338), //db ['"むふー@@"', '0x18', '0x5', '0x0'];
    ezchat_word("MUFUFU@@", 0x33a), //db ['"むふふ@@"', '0x1a', '0x5', '0x0'];
    ezchat_word("MMM@@@@@", 0x31e), //db ['"むむ@@@"', '0x1c', '0x5', '0x0'];
    ezchat_word("OH-KAY@@", 0x386), //db ['"よーし@@"', '0x6a', '0x5', '0x0'];
    ezchat_word("OKAY@@@@", 0x38e), //db ['"よし！@@"', '0x72', '0x5', '0x0'];
    ezchat_word("LALALA@@", 0x2c6), //db ['"ラララ@@"', '0x98', '0x5', '0x0'];
    ezchat_word("YAY@@@@@", 0x5ba), //db ['"わーい@@"', '0xac', '0x5', '0x0'];
    ezchat_word("AWW!@@@@", 0x076), //db ['"わーん！！"', '0xb0', '0x5', '0x0'];
    ezchat_word("WOWEE@@@", 0x5b0), //db ['"ワオ@@@"', '0xb2', '0x5', '0x0'];
    ezchat_word("GWAH@@@@", 0x21c), //db ['"わっ！！@"', '0xce', '0x5', '0x0'];
    ezchat_word("WAHAHAHA", 0x540), //db ['"わははは！"', '0xd0', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Conversation[] = {
    ezchat_word("LISTEN@@", 0x2e4), //db ['"あのね@@"', '0x50', '0x0', '0x0'];
    ezchat_word("NOT VERY", 0x374), //db ['"あんまり@"', '0x6e', '0x0', '0x0'];
    ezchat_word("MEAN@@@@", 0x30e), //db ['"いじわる@"', '0x8e', '0x0', '0x0'];
    ezchat_word("LIE@@@@@", 0x2dc), //db ['"うそ@@@"', '0xb6', '0x0', '0x0'];
    ezchat_word("LAY@@@@@", 0x2cc), //db ['"うむ@@@"', '0xc4', '0x0', '0x0'];
    ezchat_word("OI@@@@@@", 0x38a), //db ['"おーい@@"', '0xe4', '0x0', '0x0'];
    ezchat_word("SUGGEST@", 0x480), //db ['"おすすめ@"', '0x6', '0x1', '0x0'];
    ezchat_word("NITWIT@@", 0x360), //db ['"おばかさん"', '0x1e', '0x1', '0x0'];
    ezchat_word("QUITE@@@", 0x3de), //db ['"かなり@@"', '0x6e', '0x1', '0x0'];
    ezchat_word("FROM@@@@", 0x1c6), //db ['"から@@@"', '0x7a', '0x1', '0x0'];
    ezchat_word("FEELING@", 0x19a), //db ['"きぶん@@"', '0x98', '0x1', '0x0'];
    ezchat_word("BUT@@@@@", 0x0b4), //db ['"けど@@@"', '0xd6', '0x1', '0x0'];
    ezchat_word("HOWEVER@", 0x27c), //db ['"こそ@@@"', '0xea', '0x1', '0x0'];
    ezchat_word("CASE@@@@", 0x0c8), //db ['"こと@@@"', '0xee', '0x1', '0x0'];
    ezchat_word("MISS@@@@", 0x31a), //db ['"さあ@@@"', '0x12', '0x2', '0x0'];
    ezchat_word("HOW@@@@@", 0x276), //db ['"さっぱり@"', '0x1e', '0x2', '0x0'];
    ezchat_word("HIT@@@@@", 0x25e), //db ['"さて@@@"', '0x20', '0x2', '0x0'];
    ezchat_word("ENOUGH@@", 0x168), //db ['"じゅうぶん"', '0x72', '0x2', '0x0'];
    ezchat_word("SOON@@@@", 0x466), //db ['"すぐ@@@"', '0x94', '0x2', '0x0'];
    ezchat_word("A LOT@@@", 0x01a), //db ['"すごく@@"', '0x98', '0x2', '0x0'];
    ezchat_word("A LITTLE", 0x018), //db ['"すこしは@"', '0x9a', '0x2', '0x0'];
    ezchat_word("AMAZING@", 0x042), //db ['"すっっごい"', '0xa0', '0x2', '0x0'];
    ezchat_word("ENTIRELY", 0x16a), //db ['"ぜーんぜん"', '0xb0', '0x2', '0x0'];
    ezchat_word("FULLY@@@", 0x1cc), //db ['"ぜったい@"', '0xb2', '0x2', '0x0'];
    ezchat_word("AND@@@@@", 0x048), //db ['"それで@@"', '0xce', '0x2', '0x0'];
    ezchat_word("ONLY@@@@", 0x394), //db ['"だけ@@@"', '0xf2', '0x2', '0x0'];
    ezchat_word("AROUND@@", 0x062), //db ['"だって@@"', '0xfc', '0x2', '0x0'];
    ezchat_word("PROBABLY", 0x3d4), //db ['"たぶん@@"', '0x6', '0x3', '0x0'];
    ezchat_word("IF@@@@@@", 0x298), //db ['"たら@@@"', '0x14', '0x3', '0x0'];
    ezchat_word("VERY@@@@", 0x53a), //db ['"ちょー@@"', '0x3a', '0x3', '0x0'];
    ezchat_word("A BIT@@@", 0x016), //db ['"ちょっと@"', '0x3c', '0x3', '0x0'];
    ezchat_word("WILD@@@@", 0x58e), //db ['"ったら@@"', '0x4e', '0x3', '0x0'];
    ezchat_word("THAT'S@@", 0x4b4), //db ['"って@@@"', '0x50', '0x3', '0x0'];
    ezchat_word("I MEAN@@", 0x288), //db ['"ていうか@"', '0x62', '0x3', '0x0'];
    ezchat_word("EVEN SO@", 0x170), //db ['"でも@@@"', '0x88', '0x3', '0x0'];
    ezchat_word("MUST BE@", 0x33e), //db ['"どうしても"', '0x9c', '0x3', '0x0'];
    ezchat_word("NATURALY", 0x34c), //db ['"とうぜん@"', '0xa0', '0x3', '0x0'];
    ezchat_word("GO AHEAD", 0x1ec), //db ['"どうぞ@@"', '0xa2', '0x3', '0x0'];
    ezchat_word("FOR NOW@", 0x1b8), //db ['"とりあえず"', '0xbe', '0x3', '0x0'];
    ezchat_word("HEY?@@@@", 0x24c), //db ['"なあ@@@"', '0xcc', '0x3', '0x0'];
    ezchat_word("JOKING@@", 0x2b4), //db ['"なんて@@"', '0xf4', '0x3', '0x0'];
    ezchat_word("READY@@@", 0x3e6), //db ['"なんでも@"', '0xfc', '0x3', '0x0'];
    ezchat_word("SOMEHOW@", 0x45c), //db ['"なんとか@"', '0xfe', '0x3', '0x0'];
    ezchat_word("ALTHOUGH", 0x03c), //db ['"には@@@"', '0x8', '0x4', '0x0'];
    ezchat_word("PERFECT@", 0x3b2), //db ['"バッチり@"', '0x46', '0x4', '0x0'];
    ezchat_word("FIRMLY@@", 0x1aa), //db ['"ばりばり@"', '0x52', '0x4', '0x0'];
    ezchat_word("EQUAL TO", 0x16c), //db ['"ほど@@@"', '0xb0', '0x4', '0x0'];
    ezchat_word("REALLY@@", 0x3ec), //db ['"ほんと@@"', '0xbe', '0x4', '0x0'];
    ezchat_word("TRULY@@@", 0x50c), //db ['"まさに@@"', '0xd0', '0x4', '0x0'];
    ezchat_word("SURELY@@", 0x488), //db ['"マジ@@@"', '0xd2', '0x4', '0x0'];
    ezchat_word("FOR SURE", 0x1ba), //db ['"マジで@@"', '0xd4', '0x4', '0x0'];
    ezchat_word("TOTALLY@", 0x4f6), //db ['"まったく@"', '0xe4', '0x4', '0x0'];
    ezchat_word("UNTIL@@@", 0x526), //db ['"まで@@@"', '0xe6', '0x4', '0x0'];
    ezchat_word("AS IF@@@", 0x068), //db ['"まるで@@"', '0xec', '0x4', '0x0'];
    ezchat_word("MOOD@@@@", 0x32a), //db ['"ムード@@"', '0xe', '0x5', '0x0'];
    ezchat_word("RATHER@@", 0x3e4), //db ['"むしろ@@"', '0x14', '0x5', '0x0'];
    ezchat_word("NO WAY@@", 0x366), //db ['"めちゃ@@"', '0x24', '0x5', '0x0'];
    ezchat_word("AWFULLY@", 0x074), //db ['"めっぽう@"', '0x28', '0x5', '0x0'];
    ezchat_word("ALMOST@@", 0x036), //db ['"もう@@@"', '0x2c', '0x5', '0x0'];
    ezchat_word("MODE@@@@", 0x320), //db ['"モード@@"', '0x2e', '0x5', '0x0'];
    ezchat_word("MORE@@@@", 0x32c), //db ['"もっと@@"', '0x36', '0x5', '0x0'];
    ezchat_word("TOO LATE", 0x4f0), //db ['"もはや@@"', '0x38', '0x5', '0x0'];
    ezchat_word("FINALLY@", 0x1a6), //db ['"やっと@@"', '0x4a', '0x5', '0x0'];
    ezchat_word("ANY@@@@@", 0x054), //db ['"やっぱり@"', '0x4c', '0x5', '0x0'];
    ezchat_word("INSTEAD@", 0x2a4), //db ['"より@@@"', '0x7c', '0x5', '0x0'];
    ezchat_word("TERRIFIC", 0x4a2), //db ['"れば@@@"', '0xa4', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Feelings[] = {
    ezchat_word("MEET@@@@", 0x310), //db ['"あいたい@"', '0x1a', '0x0', '0x0'];
    ezchat_word("PLAY@@@@", 0x3bc), //db ['"あそびたい"', '0x32', '0x0', '0x0'];
    ezchat_word("GOES@@@@", 0x1f8), //db ['"いきたい@"', '0x7c', '0x0', '0x0'];
    ezchat_word("GIDDY@@@", 0x1da), //db ['"うかれて@"', '0xb4', '0x0', '0x0'];
    ezchat_word("HAPPY@@@", 0x222), //db ['"うれしい@"', '0xc6', '0x0', '0x0'];
    ezchat_word("GLEE@@@@", 0x1e8), //db ['"うれしさ@"', '0xc8', '0x0', '0x0'];
    ezchat_word("EXCITE@@", 0x17a), //db ['"エキサイト"', '0xd8', '0x0', '0x0'];
    ezchat_word("CRUCIAL@", 0x100), //db ['"えらい@@"', '0xde', '0x0', '0x0'];
    ezchat_word("FUNNY@@@", 0x1ce), //db ['"おかしい@"', '0xec', '0x0', '0x0'];
    ezchat_word("GOT@@@@@", 0x200), //db ['"オッケー@"', '0x8', '0x1', '0x0'];
    ezchat_word("GO HOME@", 0x1f0), //db ['"かえりたい"', '0x48', '0x1', '0x0'];
    ezchat_word("FAILS@@@", 0x186), //db ['"がっくし@"', '0x5a', '0x1', '0x0'];
    ezchat_word("SAD@@@@@", 0x406), //db ['"かなしい@"', '0x6c', '0x1', '0x0'];
    ezchat_word("TRY@@@@@", 0x510), //db ['"がんばって"', '0x80', '0x1', '0x0'];
    ezchat_word("HEARS@@@", 0x238), //db ['"きがしない"', '0x86', '0x1', '0x0'];
    ezchat_word("THINK@@@", 0x4ca), //db ['"きがする@"', '0x88', '0x1', '0x0'];
    ezchat_word("HEAR@@@@", 0x234), //db ['"ききたい@"', '0x8a', '0x1', '0x0'];
    ezchat_word("WANTS@@@", 0x550), //db ['"きになる@"', '0x90', '0x1', '0x0'];
    ezchat_word("MISHEARD", 0x318), //db ['"きのせい@"', '0x96', '0x1', '0x0'];
    ezchat_word("DISLIKE@", 0x12e), //db ['"きらい@@"', '0xb4', '0x1', '0x0'];
    ezchat_word("ANGRY@@@", 0x04e), //db ['"くやしい@"', '0xbe', '0x1', '0x0'];
    ezchat_word("ANGER@@@", 0x04a), //db ['"くやしさ@"', '0xc0', '0x1', '0x0'];
    ezchat_word("LONESOME", 0x2ec), //db ['"さみしい@"', '0x24', '0x2', '0x0'];
    ezchat_word("FAIL@@@@", 0x184), //db ['"ざんねん@"', '0x32', '0x2', '0x0'];
    ezchat_word("JOY@@@@@", 0x2b8), //db ['"しあわせ@"', '0x36', '0x2', '0x0'];
    ezchat_word("GETS@@@@", 0x1d6), //db ['"したい@@"', '0x44', '0x2', '0x0'];
    ezchat_word("NEVER@@@", 0x354), //db ['"したくない"', '0x46', '0x2', '0x0'];
    ezchat_word("DARN@@@@", 0x110), //db ['"しまった@"', '0x64', '0x2', '0x0'];
    ezchat_word("DOWNCAST", 0x142), //db ['"しょんぼり"', '0x82', '0x2', '0x0'];
    ezchat_word("LIKES@@@", 0x2e0), //db ['"すき@@@"', '0x92', '0x2', '0x0'];
    ezchat_word("DISLIKES", 0x130), //db ['"だいきらい"', '0xda', '0x2', '0x0'];
    ezchat_word("BORING@@", 0x0a8), //db ['"たいくつ@"', '0xdc', '0x2', '0x0'];
    ezchat_word("CARE@@@@", 0x0c6), //db ['"だいじ@@"', '0xde', '0x2', '0x0'];
    ezchat_word("ADORE@@@", 0x024), //db ['"だいすき@"', '0xe4', '0x2', '0x0'];
    ezchat_word("DISASTER", 0x12c), //db ['"たいへん@"', '0xea', '0x2', '0x0'];
    ezchat_word("ENJOY@@@", 0x164), //db ['"たのしい@"', '0x0', '0x3', '0x0'];
    ezchat_word("ENJOYS@@", 0x166), //db ['"たのしすぎ"', '0x2', '0x3', '0x0'];
    ezchat_word("EAT@@@@@", 0x152), //db ['"たべたい@"', '0x8', '0x3', '0x0'];
    ezchat_word("USELESS@", 0x52e), //db ['"ダメダメ@"', '0xe', '0x3', '0x0'];
    ezchat_word("LACKING@", 0x2c0), //db ['"たりない@"', '0x16', '0x3', '0x0'];
    ezchat_word("BAD@@@@@", 0x07c), //db ['"ちくしょー"', '0x34', '0x3', '0x0'];
    ezchat_word("SHOULD@@", 0x434), //db ['"どうしよう"', '0x9e', '0x3', '0x0'];
    ezchat_word("EXCITING", 0x17c), //db ['"ドキドキ@"', '0xac', '0x3', '0x0'];
    ezchat_word("NICE@@@@", 0x35a), //db ['"ナイス@@"', '0xd0', '0x3', '0x0'];
    ezchat_word("DRINK@@@", 0x148), //db ['"のみたい@"', '0x26', '0x4', '0x0'];
    ezchat_word("SURPRISE", 0x48a), //db ['"びっくり@"', '0x60', '0x4', '0x0'];
    ezchat_word("FEAR@@@@", 0x198), //db ['"ふあん@@"', '0x74', '0x4', '0x0'];
    ezchat_word("WOBBLY@@", 0x59c), //db ['"ふらふら@"', '0x86', '0x4', '0x0'];
    ezchat_word("WANT@@@@", 0x54e), //db ['"ほしい@@"', '0xae', '0x4', '0x0'];
    ezchat_word("SHREDDED", 0x438), //db ['"ボロボロ@"', '0xb8', '0x4', '0x0'];
    ezchat_word("YET@@@@@", 0x5c2), //db ['"まだまだ@"', '0xe0', '0x4', '0x0'];
    ezchat_word("WAIT@@@@", 0x542), //db ['"まてない@"', '0xe8', '0x4', '0x0'];
    ezchat_word("CONTENT@", 0x0f0), //db ['"まんぞく@"', '0xf0', '0x4', '0x0'];
    ezchat_word("SEE@@@@@", 0x414), //db ['"みたい@@"', '0xf8', '0x4', '0x0'];
    ezchat_word("RARE@@@@", 0x3e2), //db ['"めずらしい"', '0x22', '0x5', '0x0'];
    ezchat_word("FIERY@@@", 0x19c), //db ['"メラメラ@"', '0x2a', '0x5', '0x0'];
    ezchat_word("NEGATIVE", 0x352), //db ['"やだ@@@"', '0x46', '0x5', '0x0'];
    ezchat_word("DONE@@@@", 0x13a), //db ['"やったー@"', '0x48', '0x5', '0x0'];
    ezchat_word("DANGER@@", 0x10c), //db ['"やばい@@"', '0x50', '0x5', '0x0'];
    ezchat_word("DONE FOR", 0x13c), //db ['"やばすぎる"', '0x52', '0x5', '0x0'];
    ezchat_word("DEFEATED", 0x126), //db ['"やられた@"', '0x54', '0x5', '0x0'];
    ezchat_word("BEAT@@@@", 0x088), //db ['"やられて@"', '0x56', '0x5', '0x0'];
    ezchat_word("GREAT@@@", 0x212), //db ['"よかった@"', '0x6e', '0x5', '0x0'];
    ezchat_word("DOTING@@", 0x13e), //db ['"ラブラブ@"', '0x96', '0x5', '0x0'];
    ezchat_word("ROMANTIC", 0x3fe), //db ['"ロマン@@"', '0xa8', '0x5', '0x0'];
    ezchat_word("QUESTION", 0x3dc), //db ['"ろんがい@"', '0xaa', '0x5', '0x0'];
    ezchat_word("REALIZE@", 0x3e8), //db ['"わから@@"', '0xb4', '0x5', '0x0'];
    ezchat_word("REALIZES", 0x3ea), //db ['"わかり@@"', '0xb6', '0x5', '0x0'];
    ezchat_word("SUSPENSE", 0x48c), //db ['"わくわく@"', '0xba', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Conditions[] = {
    ezchat_word("HOT@@@@@", 0x274), //db ['"あつい@@"', '0x38', '0x0', '0x0'];
    ezchat_word("EXISTS@@", 0x180), //db ['"あった@@"', '0x3a', '0x0', '0x0'];
    ezchat_word("APPROVED", 0x05c), //db ['"あり@@@"', '0x56', '0x0', '0x0'];
    ezchat_word("HAS@@@@@", 0x226), //db ['"ある@@@"', '0x5e', '0x0', '0x0'];
    ezchat_word("HURRIED@", 0x282), //db ['"あわてて@"', '0x6a', '0x0', '0x0'];
    ezchat_word("GOOD@@@@", 0x1fc), //db ['"いい@@@"', '0x70', '0x0', '0x0'];
    ezchat_word("LESS@@@@", 0x2d2), //db ['"いか@@@"', '0x76', '0x0', '0x0'];
    ezchat_word("MEGA@@@@", 0x314), //db ['"イカス@@"', '0x78', '0x0', '0x0'];
    ezchat_word("MOMENTUM", 0x322), //db ['"いきおい@"', '0x7a', '0x0', '0x0'];
    ezchat_word("GOING@@@", 0x1fa), //db ['"いける@@"', '0x8a', '0x0', '0x0'];
    ezchat_word("WEIRD@@@", 0x568), //db ['"いじょう@"', '0x8c', '0x0', '0x0'];
    ezchat_word("BUSY@@@@", 0x0b2), //db ['"いそがしい"', '0x90', '0x0', '0x0'];
    ezchat_word("TOGETHER", 0x4ea), //db ['"いっしょに"', '0x9a', '0x0', '0x0'];
    ezchat_word("FULL@@@@", 0x1ca), //db ['"いっぱい@"', '0x9c', '0x0', '0x0'];
    ezchat_word("ABSENT@@", 0x01e), //db ['"いない@@"', '0xa0', '0x0', '0x0'];
    ezchat_word("BEING@@@", 0x090), //db ['"いや@@@"', '0xa4', '0x0', '0x0'];
    ezchat_word("NEED@@@@", 0x350), //db ['"いる@@@"', '0xa8', '0x0', '0x0'];
    ezchat_word("TASTY@@@", 0x496), //db ['"うまい@@"', '0xc0', '0x0', '0x0'];
    ezchat_word("SKILLED@", 0x446), //db ['"うまく@@"', '0xc2', '0x0', '0x0'];
    ezchat_word("BIG@@@@@", 0x09c), //db ['"おおきい@"', '0xe6', '0x0', '0x0'];
    ezchat_word("LATE@@@@", 0x2c8), //db ['"おくれ@@"', '0xf2', '0x0', '0x0'];
    ezchat_word("CLOSE@@@", 0x0e0), //db ['"おしい@@"', '0xfa', '0x0', '0x0'];
    ezchat_word("AMUSING@", 0x044), //db ['"おもしろい"', '0x2c', '0x1', '0x0'];
    ezchat_word("ENGAGING", 0x162), //db ['"おもしろく"', '0x2e', '0x1', '0x0'];
    ezchat_word("COOL@@@@", 0x0f2), //db ['"かっこいい"', '0x5c', '0x1', '0x0'];
    ezchat_word("CUTE@@@@", 0x106), //db ['"かわいい@"', '0x7e', '0x1', '0x0'];
    ezchat_word("FLAWLESS", 0x1ae), //db ['"かんぺき@"', '0x82', '0x1', '0x0'];
    ezchat_word("PRETTY@@", 0x3d2), //db ['"けっこう@"', '0xd0', '0x1', '0x0'];
    ezchat_word("HEALTHY@", 0x232), //db ['"げんき@@"', '0xd8', '0x1', '0x0'];
    ezchat_word("SCARY@@@", 0x40e), //db ['"こわい@@"', '0x6', '0x2', '0x0'];
    ezchat_word("SUPERB@@", 0x486), //db ['"さいこう@"', '0x14', '0x2', '0x0'];
    ezchat_word("COLD@@@@", 0x0e2), //db ['"さむい@@"', '0x26', '0x2', '0x0'];
    ezchat_word("LIVELY@@", 0x2e6), //db ['"さわやか@"', '0x2c', '0x2', '0x0'];
    ezchat_word("FATED@@@", 0x194), //db ['"しかたない"', '0x38', '0x2', '0x0'];
    ezchat_word("MUCH@@@@", 0x336), //db ['"すごい@@"', '0x96', '0x2', '0x0'];
    ezchat_word("IMMENSE@", 0x29e), //db ['"すごすぎ@"', '0x9c', '0x2', '0x0'];
    ezchat_word("FABULOUS", 0x182), //db ['"すてき@@"', '0xa4', '0x2', '0x0'];
    ezchat_word("ELSE@@@@", 0x15e), //db ['"たいした@"', '0xe0', '0x2', '0x0'];
    ezchat_word("ALRIGHT@", 0x03a), //db ['"だいじょぶ"', '0xe2', '0x2', '0x0'];
    ezchat_word("COSTLY@@", 0x0f6), //db ['"たかい@@"', '0xec', '0x2', '0x0'];
    ezchat_word("CORRECT@", 0x0f4), //db ['"ただしい@"', '0xf8', '0x2', '0x0'];
    ezchat_word("UNLIKELY", 0x524), //db ['"だめ@@@"', '0xc', '0x3', '0x0'];
    ezchat_word("SMALL@@@", 0x450), //db ['"ちいさい@"', '0x2c', '0x3', '0x0'];
    ezchat_word("VARIED@@", 0x536), //db ['"ちがう@@"', '0x30', '0x3', '0x0'];
    ezchat_word("TIRED@@@", 0x4da), //db ['"つかれ@@"', '0x48', '0x3', '0x0'];
    ezchat_word("SKILL@@@", 0x444), //db ['"とくい@@"', '0xb0', '0x3', '0x0'];
    ezchat_word("NON-STOP", 0x36a), //db ['"とまらない"', '0xb6', '0x3', '0x0'];
    ezchat_word("NONE@@@@", 0x36c), //db ['"ない@@@"', '0xce', '0x3', '0x0'];
    ezchat_word("NOTHING@", 0x376), //db ['"なかった@"', '0xd2', '0x3', '0x0'];
    ezchat_word("NATURAL@", 0x34a), //db ['"なし@@@"', '0xd8', '0x3', '0x0'];
    ezchat_word("BECOMES@", 0x08a), //db ['"なって@@"', '0xdc', '0x3', '0x0'];
    ezchat_word("FAST@@@@", 0x192), //db ['"はやい@@"', '0x50', '0x4', '0x0'];
    ezchat_word("SHINE@@@", 0x42c), //db ['"ひかる@@"', '0x5a', '0x4', '0x0'];
    ezchat_word("LOW@@@@@", 0x2f8), //db ['"ひくい@@"', '0x5c', '0x4', '0x0'];
    ezchat_word("AWFUL@@@", 0x072), //db ['"ひどい@@"', '0x64', '0x4', '0x0'];
    ezchat_word("ALONE@@@", 0x038), //db ['"ひとりで@"', '0x66', '0x4', '0x0'];
    ezchat_word("BORED@@@", 0x0a6), //db ['"ひま@@@"', '0x68', '0x4', '0x0'];
    ezchat_word("LACKS@@@", 0x2c2), //db ['"ふそく@@"', '0x76', '0x4', '0x0'];
    ezchat_word("LOUSY@@@", 0x2f6), //db ['"へた@@@"', '0x8c', '0x4', '0x0'];
    ezchat_word("MISTAKE@", 0x31c), //db ['"まちがって"', '0xe2', '0x4', '0x0'];
    ezchat_word("KIND@@@@", 0x2ba), //db ['"やさしい@"', '0x42', '0x5', '0x0'];
    ezchat_word("WELL@@@@", 0x56c), //db ['"よく@@@"', '0x70', '0x5', '0x0'];
    ezchat_word("WEAKENED", 0x562), //db ['"よわって@"', '0x86', '0x5', '0x0'];
    ezchat_word("SIMPLE@@", 0x43c), //db ['"らく@@@"', '0x8c', '0x5', '0x0'];
    ezchat_word("SEEMS@@@", 0x41a), //db ['"らしい@@"', '0x90', '0x5', '0x0'];
    ezchat_word("BADLY@@@", 0x07e), //db ['"わるい@@"', '0xd4', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Life[] = {
    ezchat_word("CHORES@@", 0x0dc), //db ['"アルバイト"', '0x64', '0x0', '0x0'];
    ezchat_word("HOME@@@@", 0x270), //db ['"うち@@@"', '0xba', '0x0', '0x0'];
    ezchat_word("MONEY@@@", 0x326), //db ['"おかね@@"', '0xee', '0x0', '0x0'];
    ezchat_word("SAVINGS@", 0x40c), //db ['"おこづかい"', '0xf4', '0x0', '0x0'];
    ezchat_word("BATH@@@@", 0x082), //db ['"おふろ@@"', '0x24', '0x1', '0x0'];
    ezchat_word("SCHOOL@@", 0x410), //db ['"がっこう@"', '0x5e', '0x1', '0x0'];
    ezchat_word("REMEMBER", 0x3f6), //db ['"きねん@@"', '0x92', '0x1', '0x0'];
    ezchat_word("GROUP@@@", 0x216), //db ['"グループ@"', '0xc6', '0x1', '0x0'];
    ezchat_word("GOTCHA@@", 0x204), //db ['"ゲット@@"', '0xd2', '0x1', '0x0'];
    ezchat_word("TRADE@@@", 0x4fe), //db ['"こうかん@"', '0xde', '0x1', '0x0'];
    ezchat_word("WORK@@@@", 0x5a2), //db ['"しごと@@"', '0x40', '0x2', '0x0'];
    ezchat_word("TRAIN@@@", 0x500), //db ['"しゅぎょう"', '0x74', '0x2', '0x0'];
    ezchat_word("CLASS@@@", 0x0de), //db ['"じゅぎょう"', '0x76', '0x2', '0x0'];
    ezchat_word("LESSONS@", 0x2d4), //db ['"じゅく@@"', '0x78', '0x2', '0x0'];
    ezchat_word("EVOLVE@@", 0x176), //db ['"しんか@@"', '0x88', '0x2', '0x0'];
    ezchat_word("HANDBOOK", 0x220), //db ['"ずかん@@"', '0x90', '0x2', '0x0'];
    ezchat_word("LIVING@@", 0x2e8), //db ['"せいかつ@"', '0xae', '0x2', '0x0'];
    ezchat_word("TEACHER@", 0x49a), //db ['"せんせい@"', '0xb8', '0x2', '0x0'];
    ezchat_word("CENTER@@", 0x0cc), //db ['"センター@"', '0xba', '0x2', '0x0'];
    ezchat_word("TOWER@@@", 0x4f8), //db ['"タワー@@"', '0x28', '0x3', '0x0'];
    ezchat_word("LINK@@@@", 0x2e2), //db ['"つうしん@"', '0x40', '0x3', '0x0'];
    ezchat_word("TEST@@@@", 0x4a4), //db ['"テスト@@"', '0x7e', '0x3', '0x0'];
    ezchat_word("TV@@@@@@", 0x516), //db ['"テレビ@@"', '0x8c', '0x3', '0x0'];
    ezchat_word("PHONE@@@", 0x3b6), //db ['"でんわ@@"', '0x96', '0x3', '0x0'];
    ezchat_word("ITEM@@@@", 0x2b2), //db ['"どうぐ@@"', '0x9a', '0x3', '0x0'];
    ezchat_word("EXCHANGE", 0x178), //db ['"トレード@"', '0xc4', '0x3', '0x0'];
    ezchat_word("NAME@@@@", 0x346), //db ['"なまえ@@"', '0xe8', '0x3', '0x0'];
    ezchat_word("NEWS@@@@", 0x356), //db ['"ニュース@"', '0xa', '0x4', '0x0'];
    ezchat_word("POPULAR@", 0x3cc), //db ['"にんき@@"', '0xc', '0x4', '0x0'];
    ezchat_word("PARTY@@@", 0x3ae), //db ['"パーティー"', '0x2e', '0x4', '0x0'];
    ezchat_word("STUDY@@@", 0x47e), //db ['"べんきょう"', '0x92', '0x4', '0x0'];
    ezchat_word("MACHINE@", 0x2fe), //db ['"マシン@@"', '0xd6', '0x4', '0x0'];
    ezchat_word("CARD@@@@", 0x0c2), //db ['"めいし@@"', '0x1e', '0x5', '0x0'];
    ezchat_word("MESSAGE@", 0x316), //db ['"メッセージ"', '0x26', '0x5', '0x0'];
    ezchat_word("MAKEOVER", 0x302), //db ['"もようがえ"', '0x3a', '0x5', '0x0'];
    ezchat_word("DREAM@@@", 0x146), //db ['"ゆめ@@@"', '0x5a', '0x5', '0x0'];
    ezchat_word("DAY CARE", 0x118), //db ['"ようちえん"', '0x66', '0x5', '0x0'];
    ezchat_word("RADIO@@@", 0x3e0), //db ['"ラジオ@@"', '0x92', '0x5', '0x0'];
    ezchat_word("WORLD@@@", 0x5a8), //db ['"ワールド@"', '0xae', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Hobbies[] = {
    ezchat_word("IDOL@@@@", 0x296), //db ['"アイドル@"', '0x1e', '0x0', '0x0'];
    ezchat_word("ANIME@@@", 0x050), //db ['"アニメ@@"', '0x4c', '0x0', '0x0'];
    ezchat_word("SONG@@@@", 0x464), //db ['"うた@@@"', '0xb8', '0x0', '0x0'];
    ezchat_word("MOVIE@@@", 0x334), //db ['"えいが@@"', '0xd0', '0x0', '0x0'];
    ezchat_word("SWEETS@@", 0x48e), //db ['"おかし@@"', '0xea', '0x0', '0x0'];
    ezchat_word("CHAT@@@@", 0x0d0), //db ['"おしゃべり"', '0x4', '0x1', '0x0'];
    ezchat_word("TOYHOUSE", 0x4fa), //db ['"おままごと"', '0x28', '0x1', '0x0'];
    ezchat_word("TOYS@@@@", 0x4fc), //db ['"おもちゃ@"', '0x30', '0x1', '0x0'];
    ezchat_word("MUSIC@@@", 0x33c), //db ['"おんがく@"', '0x38', '0x1', '0x0'];
    ezchat_word("CARDS@@@", 0x0c4), //db ['"カード@@"', '0x3e', '0x1', '0x0'];
    ezchat_word("SHOPPING", 0x432), //db ['"かいもの@"', '0x46', '0x1', '0x0'];
    ezchat_word("GOURMET@", 0x206), //db ['"グルメ@@"', '0xc8', '0x1', '0x0'];
    ezchat_word("GAME@@@@", 0x1d2), //db ['"ゲーム@@"', '0xcc', '0x1', '0x0'];
    ezchat_word("MAGAZINE", 0x300), //db ['"ざっし@@"', '0x1c', '0x2', '0x0'];
    ezchat_word("WALK@@@@", 0x548), //db ['"さんぽ@@"', '0x34', '0x2', '0x0'];
    ezchat_word("BIKE@@@@", 0x09e), //db ['"じてんしゃ"', '0x50', '0x2', '0x0'];
    ezchat_word("HOBBY@@@", 0x268), //db ['"しゅみ@@"', '0x7a', '0x2', '0x0'];
    ezchat_word("SPORTS@@", 0x46e), //db ['"スポーツ@"', '0xa8', '0x2', '0x0'];
    ezchat_word("DIET@@@@", 0x12a), //db ['"ダイエット"', '0xd8', '0x2', '0x0'];
    ezchat_word("TREASURE", 0x50a), //db ['"たからもの"', '0xf0', '0x2', '0x0'];
    ezchat_word("TRAVEL@@", 0x508), //db ['"たび@@@"', '0x4', '0x3', '0x0'];
    ezchat_word("DANCE@@@", 0x10a), //db ['"ダンス@@"', '0x2a', '0x3', '0x0'];
    ezchat_word("FISHING@", 0x1ac), //db ['"つり@@@"', '0x60', '0x3', '0x0'];
    ezchat_word("DATE@@@@", 0x112), //db ['"デート@@"', '0x6a', '0x3', '0x0'];
    ezchat_word("TRAINING", 0x504), //db ['"でんしゃ@"', '0x92', '0x3', '0x0'];
    ezchat_word("PLUSHIE@", 0x3c4), //db ['"ぬいぐるみ"', '0xe', '0x4', '0x0'];
    ezchat_word("PC@@@@@@", 0x3b0), //db ['"パソコン@"', '0x3e', '0x4', '0x0'];
    ezchat_word("FLOWERS@", 0x1b0), //db ['"はな@@@"', '0x4c', '0x4', '0x0'];
    ezchat_word("HERO@@@@", 0x244), //db ['"ヒーロー@"', '0x58', '0x4', '0x0'];
    ezchat_word("NAP@@@@@", 0x348), //db ['"ひるね@@"', '0x6e', '0x4', '0x0'];
    ezchat_word("HEROINE@", 0x246), //db ['"ヒロイン@"', '0x70', '0x4', '0x0'];
    ezchat_word("JOURNEY@", 0x2b6), //db ['"ぼうけん@"', '0x96', '0x4', '0x0'];
    ezchat_word("BOARD@@@", 0x0a2), //db ['"ボード@@"', '0x9a', '0x4', '0x0'];
    ezchat_word("BALL@@@@", 0x080), //db ['"ボール@@"', '0x9e', '0x4', '0x0'];
    ezchat_word("BOOK@@@@", 0x0a4), //db ['"ほん@@@"', '0xba', '0x4', '0x0'];
    ezchat_word("MANGA@@@", 0x304), //db ['"マンガ@@"', '0xee', '0x4', '0x0'];
    ezchat_word("PROMISE@", 0x3d6), //db ['"やくそく@"', '0x40', '0x5', '0x0'];
    ezchat_word("HOLIDAY@", 0x26e), //db ['"やすみ@@"', '0x44', '0x5', '0x0'];
    ezchat_word("PLANS@@@", 0x3ba), //db ['"よてい@@"', '0x74', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Actions[] = {
    ezchat_word("MEETS@@@", 0x312),//db ['"あう@@@"', '0x20', '0x0', '0x0'];
    ezchat_word("CONCEDE@", 0x0ea),//db ['"あきらめ@"', '0x24', '0x0', '0x0'];
    ezchat_word("GIVE@@@@", 0x1e2),//db ['"あげる@@"', '0x28', '0x0', '0x0'];
    ezchat_word("GIVES@@@", 0x1e6),//db ['"あせる@@"', '0x2e', '0x0', '0x0'];
    ezchat_word("PLAYED@@", 0x3be),//db ['"あそび@@"', '0x30', '0x0', '0x0'];
    ezchat_word("PLAYS@@@", 0x3c0),//db ['"あそぶ@@"', '0x34', '0x0', '0x0'];
    ezchat_word("COLLECT@", 0x0e4),//db ['"あつめ@@"', '0x3e', '0x0', '0x0'];
    ezchat_word("WALKING@", 0x54a),//db ['"あるき@@"', '0x60', '0x0', '0x0'];
    ezchat_word("WALKS@@@", 0x54c),//db ['"あるく@@"', '0x62', '0x0', '0x0'];
    ezchat_word("WENT@@@@", 0x570),//db ['"いく@@@"', '0x7e', '0x0', '0x0'];
    ezchat_word("GO@@@@@@", 0x1ea),//db ['"いけ@@@"', '0x86', '0x0', '0x0'];
    ezchat_word("WAKE UP@", 0x544),//db ['"おき@@@"', '0xf0', '0x0', '0x0'];
    ezchat_word("WAKES UP", 0x546),//db ['"おこり@@"', '0xf6', '0x0', '0x0'];
    ezchat_word("ANGERS@@", 0x04c),//db ['"おこる@@"', '0xf8', '0x0', '0x0'];
    ezchat_word("TEACH@@@", 0x498),//db ['"おしえ@@"', '0xfe', '0x0', '0x0'];
    ezchat_word("TEACHES@", 0x49c),//db ['"おしえて@"', '0x0', '0x1', '0x0'];
    ezchat_word("PLEASE@@", 0x3c2),//db ['"おねがい@"', '0x1a', '0x1', '0x0'];
    ezchat_word("LEARN@@@", 0x2ce),//db ['"おぼえ@@"', '0x26', '0x1', '0x0'];
    ezchat_word("CHANGE@@", 0x0ce),//db ['"かえる@@"', '0x4a', '0x1', '0x0'];
    ezchat_word("TRUST@@@", 0x50e),//db ['"がまん@@"', '0x74', '0x1', '0x0'];
    ezchat_word("HEARING@", 0x236),//db ['"きく@@@"', '0x8c', '0x1', '0x0'];
    ezchat_word("TRAINS@@", 0x506),//db ['"きたえ@@"', '0x8e', '0x1', '0x0'];
    ezchat_word("CHOOSE@@", 0x0da),//db ['"きめ@@@"', '0xa6', '0x1', '0x0'];
    ezchat_word("COME@@@@", 0x0e6),//db ['"くる@@@"', '0xc4', '0x1', '0x0'];
    ezchat_word("SEARCH@@", 0x412),//db ['"さがし@@"', '0x18', '0x2', '0x0'];
    ezchat_word("CAUSE@@@", 0x0ca),//db ['"さわぎ@@"', '0x2a', '0x2', '0x0'];
    ezchat_word("THESE@@@", 0x4bc),//db ['"した@@@"', '0x42', '0x2', '0x0'];
    ezchat_word("KNOW@@@@", 0x2bc),//db ['"しって@@"', '0x4a', '0x2', '0x0'];
    ezchat_word("KNOWS@@@", 0x2be),//db ['"して@@@"', '0x4e', '0x2', '0x0'];
    ezchat_word("REFUSE@@", 0x3f0),//db ['"しない@@"', '0x52', '0x2', '0x0'];
    ezchat_word("STORES@@", 0x478),//db ['"しまう@@"', '0x60', '0x2', '0x0'];
    ezchat_word("BRAG@@@@", 0x0ac),//db ['"じまん@@"', '0x66', '0x2', '0x0'];
    ezchat_word("IGNORANT", 0x29c),//db ['"しらない@"', '0x84', '0x2', '0x0'];
    ezchat_word("THINKS@@", 0x4cc),//db ['"しる@@@"', '0x86', '0x2', '0x0'];
    ezchat_word("BELIEVE@", 0x092),//db ['"しんじて@"', '0x8a', '0x2', '0x0'];
    ezchat_word("SLIDE@@@", 0x44c),//db ['"する@@@"', '0xaa', '0x2', '0x0'];
    ezchat_word("EATS@@@@", 0x154),//db ['"たべる@@"', '0xa', '0x3', '0x0'];
    ezchat_word("USE@@@@@", 0x52c),//db ['"つかう@@"', '0x42', '0x3', '0x0'];
    ezchat_word("USES@@@@", 0x530),//db ['"つかえ@@"', '0x44', '0x3', '0x0'];
    ezchat_word("USING@@@", 0x532),//db ['"つかって@"', '0x46', '0x3', '0x0'];
    ezchat_word("COULDN'T", 0x0fa),//db ['"できない@"', '0x70', '0x3', '0x0'];
    ezchat_word("CAPABLE@", 0x0c0),//db ['"できる@@"', '0x72', '0x3', '0x0'];
    ezchat_word("VANISH@@", 0x534),//db ['"でない@@"', '0x84', '0x3', '0x0'];
    ezchat_word("APPEAR@@", 0x058),//db ['"でる@@@"', '0x8a', '0x3', '0x0'];
    ezchat_word("THROW@@@", 0x4d4),//db ['"なげる@@"', '0xd6', '0x3', '0x0'];
    ezchat_word("WORRY@@@", 0x5aa),//db ['"なやみ@@"', '0xea', '0x3', '0x0'];
    ezchat_word("SLEPT@@@", 0x44a),//db ['"ねられ@@"', '0x18', '0x4', '0x0'];
    ezchat_word("SLEEP@@@", 0x448),//db ['"ねる@@@"', '0x1a', '0x4', '0x0'];
    ezchat_word("RELEASE@", 0x3f4),//db ['"のがし@@"', '0x24', '0x4', '0x0'];
    ezchat_word("DRINKS@@", 0x14a),//db ['"のむ@@@"', '0x28', '0x4', '0x0'];
    ezchat_word("RUNS@@@@", 0x404),//db ['"はしり@@"', '0x3a', '0x4', '0x0'];
    ezchat_word("RUN@@@@@", 0x402),//db ['"はしる@@"', '0x3c', '0x4', '0x0'];
    ezchat_word("WORKS@@@", 0x5a6),//db ['"はたらき@"', '0x40', '0x4', '0x0'];
    ezchat_word("WORKING@", 0x5a4),//db ['"はたらく@"', '0x42', '0x4', '0x0'];
    ezchat_word("SINK@@@@", 0x440),//db ['"はまって@"', '0x4e', '0x4', '0x0'];
    ezchat_word("SMACK@@@", 0x44e),//db ['"ぶつけ@@"', '0x7a', '0x4', '0x0'];
    ezchat_word("PRAISE@@", 0x3d0),//db ['"ほめ@@@"', '0xb4', '0x4', '0x0'];
    ezchat_word("SHOW@@@@", 0x436),//db ['"みせて@@"', '0xf6', '0x4', '0x0'];
    ezchat_word("LOOKS@@@", 0x2ee),//db ['"みて@@@"', '0xfc', '0x4', '0x0'];
    ezchat_word("SEES@@@@", 0x41e),//db ['"みる@@@"', '0x2', '0x5', '0x0'];
    ezchat_word("SEEK@@@@", 0x418),//db ['"めざす@@"', '0x20', '0x5', '0x0'];
    ezchat_word("OWN@@@@@", 0x3a8),//db ['"もって@@"', '0x34', '0x5', '0x0'];
    ezchat_word("TAKE@@@@", 0x490),//db ['"ゆずる@@"', '0x58', '0x5', '0x0'];
    ezchat_word("ALLOW@@@", 0x032),//db ['"ゆるす@@"', '0x5c', '0x5', '0x0'];
    ezchat_word("FORGET@@", 0x1be),//db ['"ゆるせ@@"', '0x5e', '0x5', '0x0'];
    ezchat_word("FORGETS@", 0x1c0),//db ['"られない@"', '0x9a', '0x5', '0x0'];
    ezchat_word("APPEARS@", 0x05a),//db ['"られる@@"', '0x9c', '0x5', '0x0'];
    ezchat_word("FAINT@@@", 0x188),//db ['"わかる@@"', '0xb8', '0x5', '0x0'];
    ezchat_word("FAINTED@", 0x18a),//db ['"わすれ@@"', '0xc0', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Time[] = {
    ezchat_word("FALL@@@@", 0x18c), //db ['"あき@@@"', '0x22', '0x0', '0x0'];
    ezchat_word("MORNING@", 0x32e), //db ['"あさ@@@"', '0x2a', '0x0', '0x0'];
    ezchat_word("TOMORROW", 0x4ec), //db ['"あした@@"', '0x2c', '0x0', '0x0'];
    ezchat_word("DAY@@@@@", 0x116), //db ['"いちにち@"', '0x94', '0x0', '0x0'];
    ezchat_word("SOMETIME", 0x460), //db ['"いつか@@"', '0x98', '0x0', '0x0'];
    ezchat_word("ALWAYS@@", 0x03e), //db ['"いつも@@"', '0x9e', '0x0', '0x0'];
    ezchat_word("CURRENT@", 0x104), //db ['"いま@@@"', '0xa2', '0x0', '0x0'];
    ezchat_word("FOREVER@", 0x1bc), //db ['"えいえん@"', '0xce', '0x0', '0x0'];
    ezchat_word("DAYS@@@@", 0x11a), //db ['"おととい@"', '0x12', '0x1', '0x0'];
    ezchat_word("END@@@@@", 0x160), //db ['"おわり@@"', '0x36', '0x1', '0x0'];
    ezchat_word("TUESDAY@", 0x512), //db ['"かようび@"', '0x78', '0x1', '0x0'];
    ezchat_word("Y'DAY@@@", 0x5b4), //db ['"きのう@@"', '0x94', '0x1', '0x0'];
    ezchat_word("TODAY@@@", 0x4e8), //db ['"きょう@@"', '0xb0', '0x1', '0x0'];
    ezchat_word("FRIDAY@@", 0x1c2), //db ['"きんようび"', '0xb8', '0x1', '0x0'];
    ezchat_word("MONDAY@@", 0x324), //db ['"げつようび"', '0xd4', '0x1', '0x0'];
    ezchat_word("LATER@@@", 0x2ca), //db ['"このあと@"', '0xf4', '0x1', '0x0'];
    ezchat_word("EARLIER@", 0x14e), //db ['"このまえ@"', '0xf6', '0x1', '0x0'];
    ezchat_word("ANOTHER@", 0x052), //db ['"こんど@@"', '0xc', '0x2', '0x0'];
    ezchat_word("TIME@@@@", 0x4d8), //db ['"じかん@@"', '0x3c', '0x2', '0x0'];
    ezchat_word("DECADE@@", 0x11e), //db ['"じゅうねん"', '0x70', '0x2', '0x0'];
    ezchat_word("WEDNSDAY", 0x564), //db ['"すいようび"', '0x8e', '0x2', '0x0'];
    ezchat_word("START@@@", 0x472), //db ['"スタート@"', '0x9e', '0x2', '0x0'];
    ezchat_word("MONTH@@@", 0x328), //db ['"ずっと@@"', '0xa2', '0x2', '0x0'];
    ezchat_word("STOP@@@@", 0x476), //db ['"ストップ@"', '0xa6', '0x2', '0x0'];
    ezchat_word("NOW@@@@@", 0x378), //db ['"そのうち@"', '0xc4', '0x2', '0x0'];
    ezchat_word("FINAL@@@", 0x1a4), //db ['"ついに@@"', '0x3e', '0x3', '0x0'];
    ezchat_word("NEXT@@@@", 0x358), //db ['"つぎ@@@"', '0x4a', '0x3', '0x0'];
    ezchat_word("SATURDAY", 0x40a), //db ['"どようび@"', '0xba', '0x3', '0x0'];
    ezchat_word("SUMMER@@", 0x482), //db ['"なつ@@@"', '0xda', '0x3', '0x0'];
    ezchat_word("SUNDAY@@", 0x484), //db ['"にちようび"', '0x6', '0x4', '0x0'];
    ezchat_word("OUTSET@@", 0x3a2), //db ['"はじめ@@"', '0x38', '0x4', '0x0'];
    ezchat_word("SPRING@@", 0x470), //db ['"はる@@@"', '0x54', '0x4', '0x0'];
    ezchat_word("DAYTIME@", 0x11c), //db ['"ひる@@@"', '0x6c', '0x4', '0x0'];
    ezchat_word("WINTER@@", 0x596), //db ['"ふゆ@@@"', '0x84', '0x4', '0x0'];
    ezchat_word("DAILY@@@", 0x108), //db ['"まいにち@"', '0xc6', '0x4', '0x0'];
    ezchat_word("THURSDAY", 0x4d6), //db ['"もくようび"', '0x30', '0x5', '0x0'];
    ezchat_word("NITETIME", 0x35e), //db ['"よなか@@"', '0x76', '0x5', '0x0'];
    ezchat_word("NIGHT@@@", 0x35c), //db ['"よる@@@"', '0x7e', '0x5', '0x0'];
    ezchat_word("WEEK@@@@", 0x566), //db ['"らいしゅう"', '0x88', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_Farewells[] = {
    ezchat_word("WILL@@@@", 0x590), //db ['"いたします"', '0x92', '0x0', '0x0'];
    ezchat_word("AYE@@@@@", 0x078), //db ['"おります@"', '0x32', '0x1', '0x0'];
    ezchat_word("…@@@@@@@", 0x00a), //db ['"か！？@@"', '0x3c', '0x1', '0x0'];
    ezchat_word("HM?@@@@@", 0x262), //db ['"かい？@@"', '0x44', '0x1', '0x0'];
    ezchat_word("Y'THINK?", 0x5b6), //db ['"かしら？@"', '0x50', '0x1', '0x0'];
    ezchat_word("IS IT?@@", 0x2a8), //db ['"かな？@@"', '0x6a', '0x1', '0x0'];
    ezchat_word("BE@@@@@@", 0x086), //db ['"かも@@@"', '0x76', '0x1', '0x0'];
    ezchat_word("GIMME@@@", 0x1de), //db ['"くれ@@@"', '0xca', '0x1', '0x0'];
    ezchat_word("COULD@@@", 0x0f8), //db ['"ございます"', '0xe8', '0x1', '0x0'];
    ezchat_word("TEND TO@", 0x49e), //db ['"しがち@@"', '0x3a', '0x2', '0x0'];
    ezchat_word("WOULD@@@", 0x5ac), //db ['"します@@"', '0x62', '0x2', '0x0'];
    ezchat_word("IS@@@@@@", 0x2a6), //db ['"じゃ@@@"', '0x6a', '0x2', '0x0'];
    ezchat_word("ISNT IT?", 0x2ac), //db ['"じゃん@@"', '0x6e', '0x2', '0x0'];
    ezchat_word("LET'S@@@", 0x2d6), //db ['"しよう@@"', '0x7c', '0x2', '0x0'];
    ezchat_word("OTHER@@@", 0x39c), //db ['"ぜ！@@@"', '0xac', '0x2', '0x0'];
    ezchat_word("ARE@@@@@", 0x05e), //db ['"ぞ！@@@"', '0xbc', '0x2', '0x0'];
    ezchat_word("WAS@@@@@", 0x552), //db ['"た@@@@"', '0xd4', '0x2', '0x0'];
    ezchat_word("WERE@@@@", 0x572), //db ['"だ@@@@"', '0xd6', '0x2', '0x0'];
    ezchat_word("THOSE@@@", 0x4d2), //db ['"だからね@"', '0xee', '0x2', '0x0'];
    ezchat_word("ISN'T@@@", 0x2aa), //db ['"だぜ@@@"', '0xf4', '0x2', '0x0'];
    ezchat_word("WON'T@@@", 0x5a0), //db ['"だった@@"', '0xfa', '0x2', '0x0'];
    ezchat_word("CAN'T@@@", 0x0bc), //db ['"だね@@@"', '0xfe', '0x2', '0x0'];
    ezchat_word("CAN@@@@@", 0x0b8), //db ['"だよ@@@"', '0x10', '0x3', '0x0'];
    ezchat_word("DON'T@@@", 0x138), //db ['"だよねー！"', '0x12', '0x3', '0x0'];
    ezchat_word("DO@@@@@@", 0x132), //db ['"だわ@@@"', '0x26', '0x3', '0x0'];
    ezchat_word("DOES@@@@", 0x136), //db ['"ッス@@@"', '0x4c', '0x3', '0x0'];
    ezchat_word("WHOM@@@@", 0x588), //db ['"ってかんじ"', '0x52', '0x3', '0x0'];
    ezchat_word("WHICH@@@", 0x57c), //db ['"っぱなし@"', '0x54', '0x3', '0x0'];
    ezchat_word("WASN'T@@", 0x554), //db ['"つもり@@"', '0x56', '0x3', '0x0'];
    ezchat_word("WEREN'T@", 0x574), //db ['"ていない@"', '0x64', '0x3', '0x0'];
    ezchat_word("HAVE@@@@", 0x228), //db ['"ている@@"', '0x66', '0x3', '0x0'];
    ezchat_word("HAVEN'T@", 0x22a), //db ['"でーす！@"', '0x68', '0x3', '0x0'];
    ezchat_word("A@@@@@@@", 0x014), //db ['"でした@@"', '0x74', '0x3', '0x0'];
    ezchat_word("AN@@@@@@", 0x046), //db ['"でしょ？@"', '0x76', '0x3', '0x0'];
    ezchat_word("NOT@@@@@", 0x372), //db ['"でしょー！"', '0x78', '0x3', '0x0'];
    ezchat_word("THERE@@@", 0x4ba), //db ['"です@@@"', '0x7a', '0x3', '0x0'];
    ezchat_word("OK?@@@@@", 0x38c), //db ['"ですか？@"', '0x7c', '0x3', '0x0'];
    ezchat_word("SO@@@@@@", 0x458), //db ['"ですよ@@"', '0x80', '0x3', '0x0'];
    ezchat_word("MAYBE@@@", 0x30a), //db ['"ですわ@@"', '0x82', '0x3', '0x0'];
    ezchat_word("ABOUT@@@", 0x01c), //db ['"どうなの？"', '0xa4', '0x3', '0x0'];
    ezchat_word("OVER@@@@", 0x3a6), //db ['"どうよ？@"', '0xa8', '0x3', '0x0'];
    ezchat_word("IT@@@@@@", 0x2ae), //db ['"とかいって"', '0xaa', '0x3', '0x0'];
    ezchat_word("FOR@@@@@", 0x1b6), //db ['"なの@@@"', '0xe0', '0x3', '0x0'];
    ezchat_word("ON@@@@@@", 0x390), //db ['"なのか@@"', '0xe2', '0x3', '0x0'];
    ezchat_word("OFF@@@@@", 0x37c), //db ['"なのだ@@"', '0xe4', '0x3', '0x0'];
    ezchat_word("AS@@@@@@", 0x066), //db ['"なのよ@@"', '0xe6', '0x3', '0x0'];
    ezchat_word("TO@@@@@@", 0x4dc), //db ['"なんだね@"', '0xf2', '0x3', '0x0'];
    ezchat_word("WITH@@@@", 0x598), //db ['"なんです@"', '0xf8', '0x3', '0x0'];
    ezchat_word("BETTER@@", 0x09a), //db ['"なんてね@"', '0xfa', '0x3', '0x0'];
    ezchat_word("EVER@@@@", 0x172), //db ['"ね@@@@"', '0x12', '0x4', '0x0'];
    ezchat_word("SINCE@@@", 0x43e), //db ['"ねー@@@"', '0x14', '0x4', '0x0'];
    ezchat_word("OF@@@@@@", 0x37a), //db ['"の@@@@"', '0x1c', '0x4', '0x0'];
    ezchat_word("BELONG@@", 0x094), //db ['"の？@@@"', '0x1e', '0x4', '0x0'];
    ezchat_word("AT@@@@@@", 0x06a), //db ['"ばっかり@"', '0x44', '0x4', '0x0'];
    ezchat_word("IN@@@@@@", 0x2a0), //db ['"まーす！@"', '0xc2', '0x4', '0x0'];
    ezchat_word("OUT@@@@@", 0x3a0), //db ['"ます@@@"', '0xd8', '0x4', '0x0'];
    ezchat_word("TOO@@@@@", 0x4ee), //db ['"ますわ@@"', '0xda', '0x4', '0x0'];
    ezchat_word("LIKE@@@@", 0x2de), //db ['"ません@@"', '0xdc', '0x4', '0x0'];
    ezchat_word("DID@@@@@", 0x128), //db ['"みたいな@"', '0xfa', '0x4', '0x0'];
    ezchat_word("WITHOUT@", 0x59a), //db ['"よ！@@@"', '0x60', '0x5', '0x0'];
    ezchat_word("AFTER@@@", 0x028), //db ['"よー@@@"', '0x68', '0x5', '0x0'];
    ezchat_word("BEFORE@@", 0x08e), //db ['"よーん@@"', '0x6c', '0x5', '0x0'];
    ezchat_word("WHILE@@@", 0x57e), //db ['"よね@@@"', '0x78', '0x5', '0x0'];
    ezchat_word("THAN@@@@", 0x4a6), //db ['"るよ@@@"', '0xa2', '0x5', '0x0'];
    ezchat_word("ONCE@@@@", 0x392), //db ['"わけ@@@"', '0xbc', '0x5', '0x0'];
    ezchat_word("ANYWHERE", 0x056), //db ['"わよ！@@"', '0xd2', '0x5', '0x0'];
};

const ezchatword_s MobileEZChatCategoryPointers_ThisAndThat[] = {
    ezchat_word("HIGHS@@@", 0x258), //db ['"ああ@@@"', '0x12', '0x0', '0x0'];
    ezchat_word("LOWS@@@@", 0x2fa), //db ['"あっち@@"', '0x3c', '0x0', '0x0'];
    ezchat_word("UM@@@@@@", 0x51e), //db ['"あの@@@"', '0x4e', '0x0', '0x0'];
    ezchat_word("REAR@@@@", 0x3ee), //db ['"ありゃ@@"', '0x5c', '0x0', '0x0'];
    ezchat_word("THINGS@@", 0x4c8), //db ['"あれ@@@"', '0x66', '0x0', '0x0'];
    ezchat_word("THING@@@", 0x4c6), //db ['"あれは@@"', '0x68', '0x0', '0x0'];
    ezchat_word("BELOW@@@", 0x096), //db ['"あんな@@"', '0x6c', '0x0', '0x0'];
    ezchat_word("HIGH@@@@", 0x256), //db ['"こう@@@"', '0xdc', '0x1', '0x0'];
    ezchat_word("HERE@@@@", 0x242), //db ['"こっち@@"', '0xec', '0x1', '0x0'];
    ezchat_word("INSIDE@@", 0x2a2), //db ['"この@@@"', '0xf2', '0x1', '0x0'];
    ezchat_word("OUTSIDE@", 0x3a4), //db ['"こりゃ@@"', '0xfe', '0x1', '0x0'];
    ezchat_word("BESIDE@@", 0x098), //db ['"これ@@@"', '0x0', '0x2', '0x0'];
    ezchat_word("THIS ONE", 0x4d0), //db ['"これだ！@"', '0x2', '0x2', '0x0'];
    ezchat_word("THIS@@@@", 0x4ce), //db ['"これは@@"', '0x4', '0x2', '0x0'];
    ezchat_word("EVERY@@@", 0x174), //db ['"こんな@@"', '0xe', '0x2', '0x0'];
    ezchat_word("SEEMS SO", 0x41c), //db ['"そう@@@"', '0xbe', '0x2', '0x0'];
    ezchat_word("DOWN@@@@", 0x140), //db ['"そっち@@"', '0xc0', '0x2', '0x0'];
    ezchat_word("THAT@@@@", 0x4ac), //db ['"その@@@"', '0xc2', '0x2', '0x0'];
    ezchat_word("THAT IS@", 0x4ae), //db ['"そりゃ@@"', '0xc6', '0x2', '0x0'];
    ezchat_word("THAT ONE", 0x4b0), //db ['"それ@@@"', '0xc8', '0x2', '0x0'];
    ezchat_word("THATS IT", 0x4b6), //db ['"それだ！@"', '0xcc', '0x2', '0x0'];
    ezchat_word("AM@@@@@@", 0x040), //db ['"それは@@"', '0xd0', '0x2', '0x0'];
    ezchat_word("THAT WAS", 0x4b2), //db ['"そんな@@"', '0xd2', '0x2', '0x0'];
    ezchat_word("UP@@@@@@", 0x528), //db ['"どう@@@"', '0x98', '0x3', '0x0'];
    ezchat_word("CHOICE@@", 0x0d8), //db ['"どっち@@"', '0xb2', '0x3', '0x0'];
    ezchat_word("FAR@@@@@", 0x190), //db ['"どの@@@"', '0xb4', '0x3', '0x0'];
    ezchat_word("AWAY@@@@", 0x070), //db ['"どりゃ@@"', '0xc0', '0x3', '0x0'];
    ezchat_word("NEAR@@@@", 0x34e), //db ['"どれ@@@"', '0xc2', '0x3', '0x0'];
    ezchat_word("WHERE@@@", 0x57a), //db ['"どれを@@"', '0xc8', '0x3', '0x0'];
    ezchat_word("WHEN@@@@", 0x578), //db ['"どんな@@"', '0xca', '0x3', '0x0'];
    ezchat_word("WHAT@@@@", 0x576), //db ['"なに@@@"', '0xde', '0x3', '0x0'];
    ezchat_word("DEEP@@@@", 0x124), //db ['"なんか@@"', '0xec', '0x3', '0x0'];
    ezchat_word("SHALLOW@", 0x424), //db ['"なんだ@@"', '0xf0', '0x3', '0x0'];
    ezchat_word("WHY@@@@@", 0x58c), //db ['"なんで@@"', '0xf6', '0x3', '0x0'];
    ezchat_word("CONFUSED", 0x0ec), //db ['"なんなんだ"', '0x0', '0x4', '0x0'];
    ezchat_word("OPPOSITE", 0x39a), //db ['"なんの@@"', '0x2', '0x4', '0x0'];
};

const ezchatword_s* const MobileEZChatCategoryPointers[] = {
//  entries correspond to EZCHAT_* constants
    [EZCHAT_TYPES - 1] = MobileEZChatCategoryPointers_Types, //dw ['.Types'];  // 01
    [EZCHAT_GREETINGS - 1] = MobileEZChatCategoryPointers_Greetings, //dw ['.Greetings'];  // 02
    [EZCHAT_PEOPLE - 1] = MobileEZChatCategoryPointers_People, //dw ['.People'];  // 03
    [EZCHAT_BATTLE - 1] = MobileEZChatCategoryPointers_Battle, //dw ['.Battle'];  // 04
    [EZCHAT_EXCLAMATIONS - 1] = MobileEZChatCategoryPointers_Exclamations, //dw ['.Exclamations'];  // 05
    [EZCHAT_CONVERSATION - 1] = MobileEZChatCategoryPointers_Conversation, //dw ['.Conversation'];  // 06
    [EZCHAT_FEELINGS - 1] = MobileEZChatCategoryPointers_Feelings, //dw ['.Feelings'];  // 07
    [EZCHAT_CONDITIONS - 1] = MobileEZChatCategoryPointers_Conditions, //dw ['.Conditions'];  // 08
    [EZCHAT_LIFE - 1] = MobileEZChatCategoryPointers_Life, //dw ['.Life'];  // 09
    [EZCHAT_HOBBIES - 1] = MobileEZChatCategoryPointers_Hobbies, //dw ['.Hobbies'];  // 0a
    [EZCHAT_ACTIONS - 1] = MobileEZChatCategoryPointers_Actions, //dw ['.Actions'];  // 0b
    [EZCHAT_TIME - 1] = MobileEZChatCategoryPointers_Time, //dw ['.Time'];  // 0c
    [EZCHAT_FAREWELLS - 1] = MobileEZChatCategoryPointers_Farewells, //dw ['.Farewells'];  // 0d
    [EZCHAT_THISANDTHAT - 1] = MobileEZChatCategoryPointers_ThisAndThat, //dw ['.ThisAndThat'];  // 0e
};

// macro_11f220: MACRO
// ; parameter: number of words
//     db \1
// ; 12 words per page (0-based indexing)
//     db (\1 - 1) / 12
// ENDM
#define ezchat_wordpage_count(_w) {_w, (_w - 1) / 12}

static_assert(lengthof(MobileEZChatCategoryPointers_Types) == 18, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Greetings) == 36, "");
static_assert(lengthof(MobileEZChatCategoryPointers_People) == 69, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Battle) == 69, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Exclamations) == 66, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Conversation) == 66, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Feelings) == 69, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Conditions) == 66, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Life) == 39, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Hobbies) == 39, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Actions) == 69, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Time) == 39, "");
static_assert(lengthof(MobileEZChatCategoryPointers_Farewells) == 66, "");
static_assert(lengthof(MobileEZChatCategoryPointers_ThisAndThat) == 36, "");

const u8_pair_s MobileEZChatData_WordAndPageCounts[] = {
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Types)),  // 01: Types
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Greetings)),  // 02: Greetings
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_People)),  // 03: People
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Battle)),  // 04: Battle
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Exclamations)),  // 05: Exclamations
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Conversation)),  // 06: Conversation
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Feelings)),  // 07: Feelings
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Conditions)),  // 08: Conditions
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Life)),  // 09: Life
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Hobbies)),  // 0a: Hobbies
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Actions)),  // 0b: Actions
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Time)),  // 0c: Time
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_Farewells)),  // 0d: Farewells
    ezchat_wordpage_count(lengthof(MobileEZChatCategoryPointers_ThisAndThat)),  // 0e: ThisAndThat
};

const u16_pair_s EZChat_SortedWords[] = {
//  Addresses in WRAM bank 3 where EZChat words beginning
//  with the given kana are sorted in memory, and the pre-
//  allocated size for each.
//  These arrays are expanded dynamically to accomodate
//  any Pokemon you've seen that starts with each kana.
// macro_11f23c: MACRO
//     dw w3_d012 - w3_d000 + x, \1
// x += 2 * \1
// ENDM
// x = 0
#if defined(_CRYSTAL_JP)
    //macro_11f23c ['0x2f']  // a
    //macro_11f23c ['0x1e']  // i
    //macro_11f23c ['0x11']  // u
    //macro_11f23c ['0x09']  // e
    //macro_11f23c ['0x2e']  // o
    //macro_11f23c ['0x24']  // ka_ga
    //macro_11f23c ['0x1b']  // ki_gi
    //macro_11f23c ['0x09']  // ku_gu
    //macro_11f23c ['0x07']  // ke_ge
    //macro_11f23c ['0x1c']  // ko_go
    //macro_11f23c ['0x12']  // sa_za
    //macro_11f23c ['0x2b']  // shi_ji
    //macro_11f23c ['0x10']  // su_zu
    //macro_11f23c ['0x08']  // se_ze
    //macro_11f23c ['0x0c']  // so_zo
    //macro_11f23c ['0x2c']  // ta_da
    //macro_11f23c ['0x09']  // chi_dhi
    //macro_11f23c ['0x12']  // tsu_du
    //macro_11f23c ['0x1b']  // te_de
    //macro_11f23c ['0x1a']  // to_do
    //macro_11f23c ['0x1c']  // na
    //macro_11f23c ['0x05']  // ni
    //macro_11f23c ['0x02']  // nu
    //macro_11f23c ['0x05']  // ne
    //macro_11f23c ['0x07']  // no
    //macro_11f23c ['0x16']  // ha_ba_pa
    //macro_11f23c ['0x0e']  // hi_bi_pi
    //macro_11f23c ['0x0c']  // fu_bu_pu
    //macro_11f23c ['0x05']  // he_be_pe
    //macro_11f23c ['0x16']  // ho_bo_po
    //macro_11f23c ['0x19']  // ma
    //macro_11f23c ['0x0e']  // mi
    //macro_11f23c ['0x08']  // mu
    //macro_11f23c ['0x07']  // me
    //macro_11f23c ['0x09']  // mo
    //macro_11f23c ['0x0d']  // ya
    //macro_11f23c ['0x04']  // yu
    //macro_11f23c ['0x14']  // yo
    //macro_11f23c ['0x0b']  // ra
    //macro_11f23c ['0x01']  // ri
    //macro_11f23c ['0x02']  // ru
    //macro_11f23c ['0x02']  // re
    //macro_11f23c ['0x02']  // ro
    //macro_11f23c ['0x15']  // wa
#else
    u16_pair(  20,  51), // A
    u16_pair(  71,  31), // B
    u16_pair( 102,  40), // C
    u16_pair( 142,  35), // D
    u16_pair( 177,  26), // E
    u16_pair( 203,  39), // F
    u16_pair( 242,  39), // G
    u16_pair( 281,  51), // H
    u16_pair( 332,  24), // I
    u16_pair( 356,   3), // J
    u16_pair( 359,   3), // K
    u16_pair( 362,  31), // L
    u16_pair( 393,  36), // M
    u16_pair( 429,  26), // N
    u16_pair( 455,  24), // O
    u16_pair( 479,  25), // P
    u16_pair( 504,   2), // Q
    u16_pair( 506,  19), // R
    u16_pair( 525,  69), // S
    u16_pair( 594,  69), // T
    u16_pair( 663,  13), // U
    u16_pair( 676,   5), // V
    u16_pair( 681,  59), // W
    u16_pair( 740,   0), // X
    u16_pair( 740,  17), // Y
    u16_pair( 757,   0), // Z
    u16_pair(2048,  10), // !?
#endif
    //dw ['NULL', '0x09'];  // end

// End:

};
