#include "../constants.h"
#include "fixed_words.h"
#include "../home/sram.h"
#include "../home/text.h"
#include "../home/copy.h"
#include "../home/names.h"
#include "../charmap.h"

uint8_t gEZChatTextStringBuffer[32];
const txt_cmd_s EZChatTextBuffer[] = {
    text_ram(gEZChatTextStringBuffer)
    text_end
};

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
        PlaceString_Conv(state, state->hl);
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

// EZChat_RenderOneWord
void Function11c075(uint8_t* de, uint8_t c){
    // PUSH_DE;
    // LD_A_C;
    // CALL(aFunction11c254);
    Function11c254(c);
    // POP_DE;
    // LD_BC(wcd36);
    // CALL(aFunction11c08f);
    Function11c08f(de, wram->wMobileTimeDataBuffer);
    // RET;
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
    uint8_t a = 6;

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
            if((wram->wJumptableIndex & 0x80) == 0x0) {
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
    ByteFill_Conv2(wram->wc608, NAME_LENGTH, CHAR_TERM);
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
        GetPokemonName_Conv2(e);
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
        ByteFill_Conv2(wram->wStringBuffer1, NAME_LENGTH, CHAR_TERM);
        hl = U82CA(wram->wStringBuffer1, word);
        bc = NAME_LENGTH - 1;
    }

// copy_string:
    // LD_DE(wc608);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(&wram->wc608, hl, bc);
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
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // RET;
}

// EZChat_EditMenu
void Function11c1b9(void){
    CALL(aFunction11c1b9_InitKanaMode);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    CALL(aEZChat_MasterLoop);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;


InitKanaMode:
    XOR_A_A;
    LD_addr_A(wJumptableIndex);
    LD_addr_A(wcf64);
    LD_addr_A(wcf65);
    LD_addr_A(wcf66);
    LD_addr_A(wcd23);
    LD_addr_A(wcd20);
    LD_addr_A(wcd21);
    LD_addr_A(wcd22);
    LD_addr_A(wcd35);
    LD_addr_A(wcd2b);
    LD_A(0xff);
    LD_addr_A(wcd24);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    CALL(aFunction11c254);
    CALL(aClearBGPalettes);
    CALL(aClearSprites);
    CALL(aClearScreen);
    CALL(aFunction11d323);
    CALL(aSetPalettes);
    CALL(aDisableLCD);
    LD_HL(mSelectStartGFX);
    LD_DE(vTiles2);
    LD_BC(0x60);
    CALL(aCopyBytes);
    LD_HL(mEZChatSlowpokeLZ);
    LD_DE(vTiles0);
    CALL(aDecompress);
    CALL(aEnableLCD);
    FARCALL(aReloadMapPart);
    FARCALL(aClearSpriteAnims);
    FARCALL(aLoadPokemonData);
    FARCALL(aPokedex_ABCMode);
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(wc6d0);
    LD_DE(wLYOverrides);
    LD_BC(0x100);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    CALL(aEZChat_GetCategoryWordsByKana);
    CALL(aEZChat_GetSeenPokemonByKana);
    RET;

}

void Function11c254(uint8_t a){
    // PUSH_AF;
    // LD_A(BANK(s4_a007));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as4_a007));
    // LD_HL(s4_a007);
    uint8_t* hl = GBToRAMAddr(s4_a007);
    // POP_AF;
    // SLA_A;
    // SLA_A;
    // LD_C_A;
    uint8_t c = a << 2;
    // SLA_A;
    // ADD_A_C;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    // LD_DE(wcd36);
    // LD_BC(12);
    // CALL(aCopyBytes);
    CopyBytes_Conv2(wram->wMobileTimeDataBuffer, hl + (a << 3) + c, 12);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void EZChat_ClearBottom12Rows(void){
    // LD_A(0x7f);
    // hlcoord(0, 6, wTilemap);
    // LD_BC((SCREEN_HEIGHT - 6) * SCREEN_WIDTH);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 6, wram->wTilemap), (SCREEN_HEIGHT - 6) * SCREEN_WIDTH, 0x7f);
    // RET;
}

void EZChat_MasterLoop(void){

loop:
    CALL(aJoyTextDelay);
    LDH_A_addr(hJoyPressed);
    LDH_addr_A(hJoypadPressed);
    LD_A_addr(wJumptableIndex);
    BIT_A(7);
    IF_NZ goto exit;
    CALL(aEZChat_MasterLoop_DoJumptableFunction);
    FARCALL(aPlaySpriteAnimations);
    FARCALL(aReloadMapPart);
    goto loop;


exit:
    FARCALL(aClearSpriteAnims);
    CALL(aClearSprites);
    RET;


DoJumptableFunction:
    //jumptable ['.Jumptable', 'wJumptableIndex']


Jumptable:
    //dw ['.SpawnObjects'];  // 00
    //dw ['.InitRAM'];  // 01
    //dw ['Function11c35f'];  // 02
    //dw ['Function11c373'];  // 03
    //dw ['Function11c3c2'];  // 04
    //dw ['Function11c3ed'];  // 05
    //dw ['Function11c52c'];  // 06
    //dw ['Function11c53d'];  // 07
    //dw ['Function11c658'];  // 08
    //dw ['Function11c675'];  // 09
    //dw ['Function11c9bd'];  // 0a
    //dw ['Function11c9c3'];  // 0b
    //dw ['Function11caad'];  // 0c
    //dw ['Function11cab3'];  // 0d
    //dw ['Function11cb52'];  // 0e
    //dw ['Function11cb66'];  // 0f
    //dw ['Function11cbf5'];  // 10
    //dw ['Function11ccef'];  // 11
    //dw ['Function11cd04'];  // 12
    //dw ['Function11cd20'];  // 13
    //dw ['Function11cd54'];  // 14
    //dw ['Function11ce0b'];  // 15
    //dw ['Function11ce2b'];  // 16


SpawnObjects:
    depixel4(3, 1, 2, 5);
    LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
    CALL(aInitSpriteAnimStruct);
    depixel4(8, 1, 2, 5);

    LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A(0x1);
    LD_hl_A;

    depixel4(9, 2, 2, 0);
    LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A(0x3);
    LD_hl_A;

    depixel2(10, 16);
    LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A(0x4);
    LD_hl_A;

    depixel2(10, 4);
    LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A(0x5);
    LD_hl_A;

    depixel2(10, 2);
    LD_A(SPRITE_ANIM_INDEX_EZCHAT_CURSOR);
    CALL(aInitSpriteAnimStruct);
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    LD_A(0x2);
    LD_hl_A;

    LD_HL(wcd23);
    SET_hl(1);
    SET_hl(2);
    JP(mFunction11cfb5);


InitRAM:
    LD_A(0x9);
    LD_addr_A(wcd2d);
    LD_A(0x2);
    LD_addr_A(wcd2e);
    LD_addr_A(wcd2f);
    LD_addr_A(wcd30);
    LD_DE(wcd2d);
    CALL(aFunction11cfce);
    JP(mFunction11cfb5);

}

void Function11c35f(void){
    LD_HL(wcd2f);
    INC_hl;
    INC_hl;
    DEC_HL;
    DEC_HL;
    DEC_hl;
    PUSH_AF;
    LD_DE(wcd2d);
    CALL(aFunction11cfce);
    POP_AF;
    RET_NZ ;
    JP(mFunction11cfb5);

}

void Function11c373(void){
    LD_HL(wcd30);
    INC_hl;
    INC_hl;
    DEC_HL;
    DEC_HL;
    DEC_hl;
    PUSH_AF;
    LD_DE(wcd2d);
    CALL(aFunction11cfce);
    POP_AF;
    RET_NZ ;
    CALL(aFunction11c38a);
    JP(mFunction11cfb5);

}

void Function11c38a(void){
    LD_HL(mUnknown_11c986);
    LD_BC(wcd36);
    LD_A(0x6);

asm_11c392:
    PUSH_AF;
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    PUSH_HL;
    PUSH_DE;
    POP_HL;
    LD_A_bc;
    INC_BC;
    LD_E_A;
    LD_A_bc;
    INC_BC;
    LD_D_A;
    PUSH_BC;
    OR_A_E;
    IF_Z goto asm_11c3af;
    LD_A_E;
    AND_A_D;
    CP_A(0xff);
    IF_Z goto asm_11c3af;
    CALL(aFunction11c05d);
    goto asm_11c3b5;

asm_11c3af:
    LD_DE(mString_11c3bc);
    CALL(aPlaceString);

asm_11c3b5:
    POP_BC;
    POP_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_11c392;
    RET;

}

void String_11c3bc(void){
    //db ['"ーーーーー@"'];

    return Function11c3c2();
}

void Function11c3c2(void){
    CALL(aEZChat_ClearBottom12Rows);
    LD_DE(mUnknown_11cfbe);
    CALL(aFunction11d035);
    hlcoord(1, 7, wTilemap);
    LD_DE(mString_11c4db);
    CALL(aPlaceString);
    hlcoord(1, 16, wTilemap);
    LD_DE(mString_11c51b);
    CALL(aPlaceString);
    CALL(aFunction11c4be);
    LD_HL(wcd23);
    SET_hl(0);
    LD_HL(wcd24);
    RES_hl(0);
    CALL(aFunction11cfb5);

    return Function11c3ed();
}

void Function11c3ed(void){
    LD_HL(wcd20);
    LD_DE(hJoypadPressed);
    LD_A_de;
    AND_A(0x8);
    IF_NZ goto asm_11c426;
    LD_A_de;
    AND_A(0x2);
    IF_NZ goto asm_11c41a;
    LD_A_de;
    AND_A(0x1);
    IF_NZ goto asm_11c42c;
    LD_DE(hJoyLast);
    LD_A_de;
    AND_A(0x40);
    IF_NZ goto asm_11c47c;
    LD_A_de;
    AND_A(0x80);
    IF_NZ goto asm_11c484;
    LD_A_de;
    AND_A(0x20);
    IF_NZ goto asm_11c48c;
    LD_A_de;
    AND_A(0x10);
    IF_NZ goto asm_11c498;
    RET;


asm_11c41a:
    CALL(aPlayClickSFX);

asm_11c41d:
    LD_HL(wcd24);
    SET_hl(0);
    LD_A(0xc);
    goto asm_11c475;

asm_11c426:
    LD_A(0x8);
    LD_addr_A(wcd20);
    RET;


asm_11c42c:
    LD_A_addr(wcd20);
    CP_A(0x6);
    IF_C goto asm_11c472;
    SUB_A(0x6);
    IF_Z goto asm_11c469;
    DEC_A;
    IF_Z goto asm_11c41d;
    LD_HL(wcd36);
    LD_C(0xc);
    XOR_A_A;

asm_11c440:
    OR_A_hl;
    INC_HL;
    DEC_C;
    IF_NZ goto asm_11c440;
    AND_A_A;
    IF_Z goto asm_11c460;
    LD_DE(mUnknown_11cfba);
    CALL(aFunction11cfce);
    decoord(1, 2, wTilemap);
    LD_BC(wcd36);
    CALL(aFunction11c08f);
    LD_HL(wcd24);
    SET_hl(0);
    LD_A(0xe);
    goto asm_11c475;

asm_11c460:
    LD_HL(wcd24);
    SET_hl(0);
    LD_A(0x11);
    goto asm_11c475;

asm_11c469:
    LD_HL(wcd24);
    SET_hl(0);
    LD_A(0xa);
    goto asm_11c475;

asm_11c472:
    CALL(aFunction11c4a5);

asm_11c475:
    LD_addr_A(wJumptableIndex);
    CALL(aPlayClickSFX);
    RET;


asm_11c47c:
    LD_A_hl;
    CP_A(0x3);
    RET_C ;
    SUB_A(0x3);
    goto asm_11c4a3;

asm_11c484:
    LD_A_hl;
    CP_A(0x6);
    RET_NC ;
    ADD_A(0x3);
    goto asm_11c4a3;

asm_11c48c:
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    CP_A(0x3);
    RET_Z ;
    CP_A(0x6);
    RET_Z ;
    DEC_A;
    goto asm_11c4a3;

asm_11c498:
    LD_A_hl;
    CP_A(0x2);
    RET_Z ;
    CP_A(0x5);
    RET_Z ;
    CP_A(0x8);
    RET_Z ;
    INC_A;

asm_11c4a3:
    LD_hl_A;
    RET;

}

void Function11c4a5(void){
    LD_HL(wcd23);
    RES_hl(0);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_11c4b7;
    XOR_A_A;
    LD_addr_A(wcd21);
    LD_A(0x6);
    RET;


asm_11c4b7:
    XOR_A_A;
    LD_addr_A(wcd22);
    LD_A(0x15);
    RET;

}

void Function11c4be(void){
    LD_A(0x1);
    hlcoord(0, 6, wAttrmap);
    LD_BC(0xa0);
    CALL(aByteFill);
    LD_A(0x7);
    hlcoord(0, 14, wAttrmap);
    LD_BC(0x28);
    CALL(aByteFill);
    FARCALL(aReloadMapPart);
    RET;

}

void String_11c4db(void){
    //db ['"６つのことば¯くみあわせます"'];
    //next ['"かえたいところ¯えらぶと\u3000でてくる"']
    //next ['"ことばのグループから\u3000いれかえたい"']
    //next ['"たんご¯えらんでください"']
    //db ['"@"'];

    return String_11c51b();
}

void String_11c51b(void){
    //db ['"ぜんぶけす\u3000やめる\u3000\u3000\u3000けってい@"'];

    return Function11c52c();
}

void Function11c52c(void){
    CALL(aEZChat_ClearBottom12Rows);
    CALL(aEZChat_PlaceCategoryNames);
    CALL(aFunction11c618);
    LD_HL(wcd24);
    RES_hl(1);
    CALL(aFunction11cfb5);

    return Function11c53d();
}

void Function11c53d(void){
    LD_HL(wcd21);
    LD_DE(hJoypadPressed);

    LD_A_de;
    AND_A(START);
    IF_NZ goto start;

    LD_A_de;
    AND_A(SELECT);
    IF_NZ goto select;

    LD_A_de;
    AND_A(B_BUTTON);
    IF_NZ goto b;

    LD_A_de;
    AND_A(A_BUTTON);
    IF_NZ goto a;

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
    LD_A_addr(wcd21);
    CP_A(15);
    IF_C goto got_category;
    SUB_A(0xf);
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
    goto go_to_function;


select:
    LD_A_addr(wcd2b);
    XOR_A(0x1);
    LD_addr_A(wcd2b);
    LD_A(0x15);
    goto go_to_function;


mode:
    LD_A(0x13);
    goto go_to_function;


got_category:
    LD_A(0x8);


go_to_function:
    LD_HL(wcd24);
    SET_hl(1);
    LD_addr_A(wJumptableIndex);
    CALL(aPlayClickSFX);
    RET;


done:
    LD_A_addr(wcd20);
    CALL(aFunction11ca6a);
    CALL(aPlayClickSFX);
    RET;


up:
    LD_A_hl;
    CP_A(0x3);
    RET_C ;
    SUB_A(0x3);
    goto finish_dpad;


down:
    LD_A_hl;
    CP_A(0xf);
    RET_NC ;
    ADD_A(0x3);
    goto finish_dpad;


left:
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    CP_A(0x3);
    RET_Z ;
    CP_A(0x6);
    RET_Z ;
    CP_A(0x9);
    RET_Z ;
    CP_A(0xc);
    RET_Z ;
    CP_A(0xf);
    RET_Z ;
    DEC_A;
    goto finish_dpad;


right:
    LD_A_hl;
    CP_A(0x2);
    RET_Z ;
    CP_A(0x5);
    RET_Z ;
    CP_A(0x8);
    RET_Z ;
    CP_A(0xb);
    RET_Z ;
    CP_A(0xe);
    RET_Z ;
    CP_A(0x11);
    RET_Z ;
    INC_A;


finish_dpad:
    LD_hl_A;
    RET;

}

void EZChat_PlaceCategoryNames(void){
    LD_DE(mMobileEZChatCategoryNames);
    LD_BC(mCoords_11c63a);
    LD_A(15);

loop:
    PUSH_AF;
    LD_A_bc;
    INC_BC;
    LD_L_A;
    LD_A_bc;
    INC_BC;
    LD_H_A;
    PUSH_BC;
    CALL(aPlaceString);
// The category names are padded with "@".
// To find the next category, the system must
// find the first character at de that is not "@".

find_next_string_loop:
    INC_DE;
    LD_A_de;
    CP_A(0x50);
    IF_Z goto find_next_string_loop;
    POP_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;
    hlcoord(1, 17, wTilemap);
    LD_DE(mEZChatString_Stop_Mode_Cancel);
    CALL(aPlaceString);
    RET;

}

void Function11c618(void){
    LD_A(0x2);
    hlcoord(0, 6, wAttrmap);
    LD_BC(0xc8);
    CALL(aByteFill);
    FARCALL(aReloadMapPart);
    RET;

}

void EZChatString_Stop_Mode_Cancel(void){
    //db ['"けす\u3000\u3000\u3000\u3000モード\u3000\u3000\u3000やめる@"'];
}

const uint16_t Coords_11c63a[] = {
    dwcoord( 1,  7),
    dwcoord( 7,  7),
    dwcoord(13,  7),
    dwcoord( 1,  9),
    dwcoord( 7,  9),
    dwcoord(13,  9),
    dwcoord( 1, 11),
    dwcoord( 7, 11),
    dwcoord(13, 11),
    dwcoord( 1, 13),
    dwcoord( 7, 13),
    dwcoord(13, 13),
    dwcoord( 1, 15),
    dwcoord( 7, 15),
    dwcoord(13, 15),
};

void Function11c658(void){
    CALL(aEZChat_ClearBottom12Rows);
    CALL(aFunction11c770);
    LD_DE(mUnknown_11cfc2);
    CALL(aFunction11d035);
    CALL(aFunction11c9ab);
    CALL(aFunction11c7bc);
    CALL(aFunction11c86e);
    LD_HL(wcd24);
    RES_hl(3);
    CALL(aFunction11cfb5);

    return Function11c675();
}

void Function11c675(void){
    LD_HL(wMobileCommsJumptableIndex);
    LD_DE(hJoypadPressed);
    LD_A_de;
    AND_A(A_BUTTON);
    IF_NZ goto a;
    LD_A_de;
    AND_A(B_BUTTON);
    IF_NZ goto b;
    LD_A_de;
    AND_A(START);
    IF_NZ goto start;
    LD_A_de;
    AND_A(SELECT);
    IF_Z goto select;

    LD_A_addr(wcd26);
    AND_A_A;
    RET_Z ;
    SUB_A(0xc);
    IF_NC goto asm_11c699;
    XOR_A_A;

asm_11c699:
    LD_addr_A(wcd26);
    goto asm_11c6c4;


start:
    LD_HL(wcd28);
    LD_A_addr(wcd26);
    ADD_A(0xc);
    CP_A_hl;
    RET_NC ;
    LD_addr_A(wcd26);
    LD_A_hl;
    LD_B_A;
    LD_HL(wMobileCommsJumptableIndex);
    LD_A_addr(wcd26);
    ADD_A_hl;
    IF_C goto asm_11c6b9;
    CP_A_B;
    IF_C goto asm_11c6c4;

asm_11c6b9:
    LD_A_addr(wcd28);
    LD_HL(wcd26);
    SUB_A_hl;
    DEC_A;
    LD_addr_A(wMobileCommsJumptableIndex);

asm_11c6c4:
    CALL(aFunction11c992);
    CALL(aFunction11c7bc);
    CALL(aFunction11c86e);
    RET;


select:
    LD_DE(hJoyLast);
    LD_A_de;
    AND_A(D_UP);
    IF_NZ goto asm_11c708;
    LD_A_de;
    AND_A(D_DOWN);
    IF_NZ goto asm_11c731;
    LD_A_de;
    AND_A(D_LEFT);
    IF_NZ goto asm_11c746;
    LD_A_de;
    AND_A(D_RIGHT);
    IF_NZ goto asm_11c755;
    RET;


a:
    CALL(aFunction11c8f6);
    LD_A(0x4);
    LD_addr_A(wcd35);
    goto asm_11c6fc;

b:
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_11c6fa;
    LD_A(0x6);
    goto asm_11c6fc;

asm_11c6fa:
    LD_A(0x15);

asm_11c6fc:
    LD_addr_A(wJumptableIndex);
    LD_HL(wcd24);
    SET_hl(3);
    CALL(aPlayClickSFX);
    RET;


asm_11c708:
    LD_A_hl;
    CP_A(0x3);
    IF_C goto asm_11c711;
    SUB_A(0x3);
    goto asm_11c76e;

asm_11c711:
    LD_A_addr(wcd26);
    SUB_A(0x3);
    RET_C ;
    LD_addr_A(wcd26);
    goto asm_11c6c4;

asm_11c71c:
    LD_HL(wcd28);
    LD_A_addr(wcd26);
    ADD_A(0xc);
    RET_C ;
    CP_A_hl;
    RET_NC ;
    LD_A_addr(wcd26);
    ADD_A(0x3);
    LD_addr_A(wcd26);
    goto asm_11c6c4;

asm_11c731:
    LD_A_addr(wcd28);
    LD_B_A;
    LD_A_addr(wcd26);
    ADD_A_hl;
    ADD_A(0x3);
    CP_A_B;
    RET_NC ;
    LD_A_hl;
    CP_A(0x9);
    IF_NC goto asm_11c71c;
    ADD_A(0x3);
    goto asm_11c76e;

asm_11c746:
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    CP_A(0x3);
    RET_Z ;
    CP_A(0x6);
    RET_Z ;
    CP_A(0x9);
    RET_Z ;
    DEC_A;
    goto asm_11c76e;

asm_11c755:
    LD_A_addr(wcd28);
    LD_B_A;
    LD_A_addr(wcd26);
    ADD_A_hl;
    INC_A;
    CP_A_B;
    RET_NC ;
    LD_A_hl;
    CP_A(0x2);
    RET_Z ;
    CP_A(0x5);
    RET_Z ;
    CP_A(0x8);
    RET_Z ;
    CP_A(0xb);
    RET_Z ;
    INC_A;

asm_11c76e:
    LD_hl_A;
    RET;

}

void Function11c770(void){
    XOR_A_A;
    LD_addr_A(wMobileCommsJumptableIndex);
    LD_addr_A(wcd26);
    LD_addr_A(wcd27);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto cd2b_is_nonzero;
    LD_A_addr(wcd21);
    AND_A_A;
    IF_Z goto cd21_is_zero;
// load from data array
    DEC_A;
    SLA_A;
    LD_HL(mMobileEZChatData_WordAndPageCounts);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_A_hli;
    LD_addr_A(wcd28);
    LD_A_hl;

load:
    LD_addr_A(wcd29);
    RET;


cd21_is_zero:
// compute from [wc7d2]
    LD_A_addr(wc7d2);
    LD_addr_A(wcd28);

div_12:
    LD_C(12);
    CALL(aSimpleDivide);
    AND_A_A;
    IF_NZ goto no_need_to_floor;
    DEC_B;

no_need_to_floor:
    LD_A_B;
    goto load;


cd2b_is_nonzero:
// compute from [wc6a8 + 2 * [wcd22]]
    LD_HL(wc6a8);
    LD_A_addr(wcd22);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hl;
    LD_addr_A(wcd28);
    goto div_12;

    return Function11c7bc();
}

void Function11c7bc(void){
    LD_BC(mUnknown_11c854);
    LD_A_addr(wcd2b);
    AND_A_A;
    IF_NZ goto asm_11c814;
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

void Unknown_11c854(void){
    //dwcoord ['2', '8'];
    //dwcoord ['8', '8'];
    //dwcoord ['14', '8'];
    //dwcoord ['2', '10'];
    //dwcoord ['8', '10'];
    //dwcoord ['14', '10'];
    //dwcoord ['2', '12'];
    //dwcoord ['8', '12'];
    //dwcoord ['14', '12'];
    //dwcoord ['2', '14'];
    //dwcoord ['8', '14'];
    //dwcoord ['14', '14'];
    //dw ['-1'];
}

void Function11c86e(void){
    // LD_A_addr(wcd26);
    // AND_A_A;
    // IF_Z goto asm_11c88a;
    if(wram->wcd26 != 0) {
        // hlcoord(2, 17, wTilemap);
        // LD_DE(mMobileString_Prev);
        // CALL(aPlaceString);
        PlaceStringSimple(U82C(MobileString_Prev), coord(2, 17, wram->wTilemap));
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

void Unknown_11c986(void){
    //dwcoord ['1', '2'];
    //dwcoord ['7', '2'];
    //dwcoord ['13', '2'];
    //dwcoord ['1', '4'];
    //dwcoord ['7', '4'];
    //dwcoord ['13', '4'];

    return Function11c992();
}

void Function11c992(void){
    LD_A(0x8);
    hlcoord(2, 7, wTilemap);

asm_11c997:
    PUSH_AF;
    LD_A(0x7f);
    PUSH_HL;
    LD_BC(0x11);
    CALL(aByteFill);
    POP_HL;
    LD_BC(0x14);
    ADD_HL_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto asm_11c997;
    RET;

}

void Function11c9ab(void){
    LD_A(0x7);
    hlcoord(0, 6, wAttrmap);
    LD_BC(0xc8);
    CALL(aByteFill);
    FARCALL(aReloadMapPart);
    RET;

}

void Function11c9bd(void){
    LD_DE(mString_11ca38);
    CALL(aFunction11ca7f);

    return Function11c9c3();
}

void Function11c9c3(void){
    LD_HL(wcd2a);
    LD_DE(hJoypadPressed);
    LD_A_de;
    AND_A(0x1);
    IF_NZ goto asm_11c9de;
    LD_A_de;
    AND_A(0x2);
    IF_NZ goto asm_11c9e9;
    LD_A_de;
    AND_A(0x40);
    IF_NZ goto asm_11c9f7;
    LD_A_de;
    AND_A(0x80);
    IF_NZ goto asm_11c9fc;
    RET;


asm_11c9de:
    LD_A_hl;
    AND_A_A;
    IF_NZ goto asm_11c9e9;
    CALL(aFunction11ca5e);
    XOR_A_A;
    LD_addr_A(wcd20);

asm_11c9e9:
    LD_HL(wcd24);
    SET_hl(4);
    LD_A(0x4);
    LD_addr_A(wJumptableIndex);
    CALL(aPlayClickSFX);
    RET;


asm_11c9f7:
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_hl;
    RET;


asm_11c9fc:
    LD_A_hl;
    AND_A_A;
    RET_NZ ;
    INC_hl;
    RET;

}

void Function11ca01(void){
    hlcoord(14, 7, wAttrmap);
    LD_DE(0x14);
    LD_A(0x5);
    LD_C_A;

asm_11ca0a:
    PUSH_HL;
    LD_A(0x6);
    LD_B_A;
    LD_A(0x7);

asm_11ca10:
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_11ca10;
    POP_HL;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto asm_11ca0a;

    return Function11ca19();
}

void Function11ca19(void){
    hlcoord(0, 12, wAttrmap);
    LD_DE(0x14);
    LD_A(0x6);
    LD_C_A;

asm_11ca22:
    PUSH_HL;
    LD_A(0x14);
    LD_B_A;
    LD_A(0x7);

asm_11ca28:
    LD_hli_A;
    DEC_B;
    IF_NZ goto asm_11ca28;
    POP_HL;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto asm_11ca22;
    FARCALL(aReloadMapPart);
    RET;

}

void String_11ca38(void){
    //db ['"とうろくちゅう<NO>あいさつ¯ぜんぶ"'];
    //next ['"けしても\u3000よろしいですか？@"']

    return String_11ca57();
}

void String_11ca57(void){
    //db ['"はい"'];
    //next ['"いいえ@"']

    return Function11ca5e();
}

void Function11ca5e(void){
    XOR_A_A;

loop:
    PUSH_AF;
    CALL(aFunction11ca6a);
    POP_AF;
    INC_A;
    CP_A(0x6);
    IF_NZ goto loop;
    RET;

}

void Function11ca6a(void){
    LD_HL(wcd36);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_hl_B;
    INC_HL;
    LD_hl_B;
    CALL(aFunction11c95d);
    LD_DE(mString_11c3bc);
    CALL(aPlaceString);
    RET;

}

void Function11ca7f(void){
    PUSH_DE;
    LD_DE(mUnknown_11cfc6);
    CALL(aFunction11cfce);
    LD_DE(mUnknown_11cfca);
    CALL(aFunction11cfce);
    hlcoord(1, 14, wTilemap);
    POP_DE;
    CALL(aPlaceString);
    hlcoord(16, 8, wTilemap);
    LD_DE(mString_11ca57);
    CALL(aPlaceString);
    CALL(aFunction11ca01);
    LD_A(0x1);
    LD_addr_A(wcd2a);
    LD_HL(wcd24);
    RES_hl(4);
    CALL(aFunction11cfb5);
    RET;

}

void Function11caad(void){
    LD_DE(mString_11cb1c);
    CALL(aFunction11ca7f);

    return Function11cab3();
}

void Function11cab3(void){
    LD_HL(wcd2a);
    LD_DE(hJoypadPressed);
    LD_A_de;
    AND_A(0x1);
    IF_NZ goto asm_11cace;
    LD_A_de;
    AND_A(0x2);
    IF_NZ goto asm_11caf9;
    LD_A_de;
    AND_A(0x40);
    IF_NZ goto asm_11cb12;
    LD_A_de;
    AND_A(0x80);
    IF_NZ goto asm_11cb17;
    RET;


asm_11cace:
    CALL(aPlayClickSFX);
    LD_A_hl;
    AND_A_A;
    IF_NZ goto asm_11cafc;
    LD_A_addr(wcd35);
    AND_A_A;
    IF_Z goto asm_11caf3;
    CP_A(0xff);
    IF_Z goto asm_11caf3;
    LD_A(0xff);
    LD_addr_A(wcd35);
    hlcoord(1, 14, wTilemap);
    LD_DE(mString_11cb31);
    CALL(aPlaceString);
    LD_A(0x1);
    LD_addr_A(wcd2a);
    RET;


asm_11caf3:
    LD_HL(wJumptableIndex);
    SET_hl(7);
    RET;


asm_11caf9:
    CALL(aPlayClickSFX);

asm_11cafc:
    LD_HL(wcd24);
    SET_hl(4);
    LD_A(0x4);
    LD_addr_A(wJumptableIndex);
    LD_A_addr(wcd35);
    CP_A(0xff);
    RET_NZ ;
    LD_A(0x1);
    LD_addr_A(wcd35);
    RET;


asm_11cb12:
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_hl;
    RET;


asm_11cb17:
    LD_A_hl;
    AND_A_A;
    RET_NZ ;
    INC_hl;
    RET;

}

void String_11cb1c(void){
    //db ['"あいさつ<NO>とうろく¯ちゅうし"'];
    //next ['"しますか？@"']

    return String_11cb31();
}

void String_11cb31(void){
    //db ['"とうろくちゅう<NO>あいさつ<WA>ほぞん"'];
    //next ['"されません<GA>よろしい\u3000ですか？@"']

    return Function11cb52();
}

void Function11cb52(void){
    LD_HL(mUnknown_11cc01);
    LD_A_addr(wMenuCursorY);

asm_11cb58:
    DEC_A;
    IF_Z goto asm_11cb5f;
    INC_HL;
    INC_HL;
    goto asm_11cb58;

asm_11cb5f:
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    CALL(aFunction11ca7f);

    return Function11cb66();
}

void Function11cb66(void){
    LD_HL(wcd2a);
    LD_DE(hJoypadPressed);
    LD_A_de;
    AND_A(0x1);
    IF_NZ goto asm_11cb81;
    LD_A_de;
    AND_A(0x2);
    IF_NZ goto asm_11cbd7;
    LD_A_de;
    AND_A(0x40);
    IF_NZ goto asm_11cbeb;
    LD_A_de;
    AND_A(0x80);
    IF_NZ goto asm_11cbf0;
    RET;


asm_11cb81:
    LD_A_hl;
    AND_A_A;
    IF_NZ goto asm_11cbd4;
    LD_A(BANK(s4_a007));
    CALL(aOpenSRAM);
    LD_HL(s4_a007);
    LD_A_addr(wMenuCursorY);
    DEC_A;
    SLA_A;
    SLA_A;
    LD_C_A;
    SLA_A;
    ADD_A_C;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    LD_DE(wcd36);
    LD_C(12);

asm_11cba2:
    LD_A_de;
    LD_hli_A;
    INC_DE;
    DEC_C;
    IF_NZ goto asm_11cba2;
    CALL(aCloseSRAM);
    CALL(aPlayClickSFX);
    LD_DE(mUnknown_11cfc6);
    CALL(aFunction11cfce);
    LD_HL(mUnknown_11cc7e);
    LD_A_addr(wMenuCursorY);

asm_11cbba:
    DEC_A;
    IF_Z goto asm_11cbc1;
    INC_HL;
    INC_HL;
    goto asm_11cbba;

asm_11cbc1:
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;
    hlcoord(1, 14, wTilemap);
    CALL(aPlaceString);
    LD_HL(wJumptableIndex);
    INC_hl;
    INC_HL;
    LD_A(0x10);
    LD_hl_A;
    RET;


asm_11cbd4:
    CALL(aPlayClickSFX);

asm_11cbd7:
    LD_DE(mUnknown_11cfba);
    CALL(aFunction11cfce);
    CALL(aFunction11c38a);
    LD_HL(wcd24);
    SET_hl(4);
    LD_A(0x4);
    LD_addr_A(wJumptableIndex);
    RET;


asm_11cbeb:
    LD_A_hl;
    AND_A_A;
    RET_Z ;
    DEC_hl;
    RET;


asm_11cbf0:
    LD_A_hl;
    AND_A_A;
    RET_NZ ;
    INC_hl;
    RET;

}

void Function11cbf5(void){
    CALL(aWaitSFX);
    LD_HL(wcf64);
    DEC_hl;
    RET_NZ ;
    DEC_HL;
    SET_hl(7);
    RET;

}

void Unknown_11cc01(void){
    //dw ['String_11cc09'];
    //dw ['String_11cc23'];
    //dw ['String_11cc42'];
    //dw ['String_11cc60'];

    return String_11cc09();
}

void String_11cc09(void){
    //db ['"じこしょうかい\u3000は"'];
    //next ['"この\u3000あいさつで\u3000いいですか？@"']

    return String_11cc23();
}

void String_11cc23(void){
    //db ['"たいせん\u3000<GA>はじまるとき\u3000は"'];
    //next ['"この\u3000あいさつで\u3000いいですか？@"']

    return String_11cc42();
}

void String_11cc42(void){
    //db ['"たいせん\u3000<NI>かったとき\u3000は"'];
    //next ['"この\u3000あいさつで\u3000いいですか？@"']

    return String_11cc60();
}

void String_11cc60(void){
    //db ['"たいせん\u3000<NI>まけたとき\u3000は"'];
    //next ['"この\u3000あいさつで\u3000いいですか？@"']

    return Unknown_11cc7e();
}

void Unknown_11cc7e(void){
    //dw ['String_11cc86'];
    //dw ['String_11cc9d'];
    //dw ['String_11ccb9'];
    //dw ['String_11ccd4'];

    return String_11cc86();
}

void String_11cc86(void){
    //db ['"じこしょうかい\u3000の"'];
    //next ['"あいさつ¯とうろくした！@"']

    return String_11cc9d();
}

void String_11cc9d(void){
    //db ['"たいせん\u3000<GA>はじまるとき\u3000の"'];
    //next ['"あいさつ¯とうろくした！@"']

    return String_11ccb9();
}

void String_11ccb9(void){
    //db ['"たいせん\u3000<NI>かったとき\u3000の"'];
    //next ['"あいさつ¯とうろくした！@"']

    return String_11ccd4();
}

void String_11ccd4(void){
    //db ['"たいせん\u3000<NI>まけたとき\u3000の"'];
    //next ['"あいさつ¯とうろくした！@"']

    return Function11ccef();
}

void Function11ccef(void){
    LD_DE(mUnknown_11cfc6);
    CALL(aFunction11cfce);
    hlcoord(1, 14, wTilemap);
    LD_DE(mString_11cd10);
    CALL(aPlaceString);
    CALL(aFunction11ca19);
    CALL(aFunction11cfb5);

    return Function11cd04();
}

void Function11cd04(void){
    LD_DE(hJoypadPressed);
    LD_A_de;
    AND_A_A;
    RET_Z ;
    LD_A(0x4);
    LD_addr_A(wJumptableIndex);
    RET;

}

void String_11cd10(void){
    //db ['"なにか\u3000ことば¯いれてください@"'];

    return Function11cd20();
}

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

void Function11cfb5(void){
    LD_HL(wJumptableIndex);
    INC_hl;
    RET;

}

void Unknown_11cfba(void){
    //db ['0', '0'];  // start coords
    //db ['20', '6'];  // end coords

    return Unknown_11cfbe();
}

void Unknown_11cfbe(void){
    //db ['0', '14'];  // start coords
    //db ['20', '4'];  // end coords

    return Unknown_11cfc2();
}

void Unknown_11cfc2(void){
    //db ['0', '6'];  // start coords
    //db ['20', '10'];  // end coords

    return Unknown_11cfc6();
}

void Unknown_11cfc6(void){
    //db ['0', '12'];  // start coords
    //db ['20', '6'];  // end coords

    return Unknown_11cfca();
}

void Unknown_11cfca(void){
    //db ['14', '7'];  // start coords
    //db ['6', '5'];  // end coords

    return Function11cfce();
}

void Function11cfce(void){
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH);
    LD_A_de;
    INC_DE;
    PUSH_AF;
    LD_A_de;
    INC_DE;
    AND_A_A;

add_n_times:
    IF_Z goto done_add_n_times;
    ADD_HL_BC;
    DEC_A;
    goto add_n_times;

done_add_n_times:
    POP_AF;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    PUSH_HL;
    LD_A(0x79);
    LD_hli_A;
    LD_A_de;
    INC_DE;
    DEC_A;
    DEC_A;
    IF_Z goto skip_fill;
    LD_C_A;
    LD_A(0x7a);

fill_loop:
    LD_hli_A;
    DEC_C;
    IF_NZ goto fill_loop;

skip_fill:
    LD_A(0x7b);
    LD_hl_A;
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    LD_A_de;
    DEC_DE;
    DEC_A;
    DEC_A;
    IF_Z goto skip_section;
    LD_B_A;

loop:
    PUSH_HL;
    LD_A(0x7c);
    LD_hli_A;
    LD_A_de;
    DEC_A;
    DEC_A;
    IF_Z goto skip_row;
    LD_C_A;
    LD_A(0x7f);

row_loop:
    LD_hli_A;
    DEC_C;
    IF_NZ goto row_loop;

skip_row:
    LD_A(0x7c);
    LD_hl_A;
    POP_HL;
    PUSH_BC;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    POP_BC;
    DEC_B;
    IF_NZ goto loop;

skip_section:
    LD_A(0x7d);
    LD_hli_A;
    LD_A_de;
    DEC_A;
    DEC_A;
    IF_Z goto skip_remainder;
    LD_C_A;
    LD_A(0x7a);

final_loop:
    LD_hli_A;
    DEC_C;
    IF_NZ goto final_loop;

skip_remainder:
    LD_A(0x7e);
    LD_hl_A;
    RET;

}

void Function11d035(void){
    hlcoord(0, 0, wTilemap);
    LD_BC(SCREEN_WIDTH);
    LD_A_de;
    INC_DE;
    PUSH_AF;
    LD_A_de;
    INC_DE;
    AND_A_A;

add_n_times:
    IF_Z goto done_add_n_times;
    ADD_HL_BC;
    DEC_A;
    goto add_n_times;

done_add_n_times:
    POP_AF;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    PUSH_HL;
    LD_A(0x79);
    LD_hl_A;
    POP_HL;
    PUSH_HL;
    LD_A_de;
    DEC_A;
    INC_DE;
    LD_C_A;
    ADD_HL_BC;
    LD_A(0x7b);
    LD_hl_A;
    CALL(aFunction11d035_AddNMinusOneTimes);
    LD_A(0x7e);
    LD_hl_A;
    POP_HL;
    PUSH_HL;
    CALL(aFunction11d035_AddNMinusOneTimes);
    LD_A(0x7d);
    LD_hl_A;
    POP_HL;
    PUSH_HL;
    INC_HL;
    PUSH_HL;
    CALL(aFunction11d035_AddNMinusOneTimes);
    POP_BC;
    DEC_DE;
    LD_A_de;
    CP_A(0x2);
    IF_Z goto skip;
    DEC_A;
    DEC_A;

loop:
    PUSH_AF;
    LD_A(0x7a);
    LD_hli_A;
    LD_bc_A;
    INC_BC;
    POP_AF;
    DEC_A;
    IF_NZ goto loop;

skip:
    POP_HL;
    LD_BC(0x14);
    ADD_HL_BC;
    PUSH_HL;
    LD_A_de;
    DEC_A;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    POP_BC;
    INC_DE;
    LD_A_de;
    CP_A(0x2);
    RET_Z ;
    PUSH_BC;
    DEC_A;
    DEC_A;
    LD_C_A;
    LD_B_A;
    LD_DE(0x14);

loop2:
    LD_A(0x7c);
    LD_hl_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop2;
    POP_HL;

loop3:
    LD_A(0x7c);
    LD_hl_A;
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto loop3;
    RET;


AddNMinusOneTimes:
    LD_A_de;
    DEC_A;
    LD_BC(SCREEN_WIDTH);

add_n_minus_one_times:
    ADD_HL_BC;
    DEC_A;
    IF_NZ goto add_n_minus_one_times;
    RET;

}

void AnimateEZChatCursor(void){
    LD_HL(SPRITEANIMSTRUCT_VAR1);
    ADD_HL_BC;
    //jumptable ['.Jumptable', 'hl']


Jumptable:
    //dw ['.zero'];
    //dw ['.one'];
    //dw ['.two'];
    //dw ['.three'];
    //dw ['.four'];
    //dw ['.five'];
    //dw ['.six'];
    //dw ['.seven'];
    //dw ['.eight'];
    //dw ['.nine'];
    //dw ['.ten'];


zero:
    LD_A_addr(wcd20);
    SLA_A;
    LD_HL(mAnimateEZChatCursor_Coords_Zero);
    LD_E(0x1);
    goto load;


one:
    LD_A_addr(wcd21);
    SLA_A;
    LD_HL(mAnimateEZChatCursor_Coords_One);
    LD_E(0x2);
    goto load;


two:
    LD_HL(mAnimateEZChatCursor_FramesetsIDs_Two);
    LD_A_addr(wcd22);
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    LD_A_hl;
    CALL(aReinitSpriteAnimFrame);

    LD_A_addr(wcd22);
    SLA_A;
    LD_HL(mAnimateEZChatCursor_Coords_Two);
    LD_E(0x4);
    goto load;


three:
    LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
    CALL(aReinitSpriteAnimFrame);
    LD_A_addr(wMobileCommsJumptableIndex);
    SLA_A;
    LD_HL(mAnimateEZChatCursor_Coords_Three);
    LD_E(0x8);

load:
    PUSH_DE;
    LD_E_A;
    LD_D(0);
    ADD_HL_DE;
    PUSH_HL;
    POP_DE;
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_A_de;
    LD_hl_A;
    POP_DE;
    LD_A_E;
    CALL(aAnimateEZChatCursor_UpdateObjectFlags);
    RET;


four:
    LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
    CALL(aReinitSpriteAnimFrame);
    LD_A_addr(wcd2a);
    SLA_A;
    LD_HL(mAnimateEZChatCursor_Coords_Four);
    LD_E(0x10);
    goto load;


five:
    LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2);
    CALL(aReinitSpriteAnimFrame);
    LD_A_addr(wcd2c);
    SLA_A;
    LD_HL(mAnimateEZChatCursor_Coords_Five);
    LD_E(0x20);
    goto load;


six:
    LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_5);
    CALL(aReinitSpriteAnimFrame);
// X = [wcd4a] * 8 + 24
    LD_A_addr(wcd4a);
    SLA_A;
    SLA_A;
    SLA_A;
    ADD_A(0x18);
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hli_A;
// Y = 48
    LD_A(0x30);
    LD_hl_A;

    LD_A(0x1);
    LD_E_A;
    CALL(aAnimateEZChatCursor_UpdateObjectFlags);
    RET;


seven:
    LD_A_addr(wEZChatCursorYCoord);
    CP_A(0x4);
    IF_Z goto cursor0;
    LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3);
    goto got_frameset;


cursor0:
    LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1);

got_frameset:
    CALL(aReinitSpriteAnimFrame);
    LD_A_addr(wEZChatCursorYCoord);
    CP_A(0x4);
    IF_Z goto asm_11d1b1;
// X = [wEZChatCursorXCoord] * 8 + 32
    LD_A_addr(wEZChatCursorXCoord);
    SLA_A;
    SLA_A;
    SLA_A;
    ADD_A(0x20);
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hli_A;
// Y = [wEZChatCursorYCoord] * 16 + 72
    LD_A_addr(wEZChatCursorYCoord);
    SLA_A;
    SLA_A;
    SLA_A;
    SLA_A;
    ADD_A(0x48);
    LD_hl_A;
    LD_A(0x2);
    LD_E_A;
    CALL(aAnimateEZChatCursor_UpdateObjectFlags);
    RET;


asm_11d1b1:
// X = [wEZChatCursorXCoord] * 40 + 24
    LD_A_addr(wEZChatCursorXCoord);
    SLA_A;
    SLA_A;
    SLA_A;
    LD_E_A;
    SLA_A;
    SLA_A;
    ADD_A_E;
    ADD_A(0x18);
    LD_HL(SPRITEANIMSTRUCT_XCOORD);
    ADD_HL_BC;
    LD_hli_A;
// Y = 138
    LD_A(0x8a);
    LD_hl_A;
    LD_A(0x2);
    LD_E_A;
    CALL(aAnimateEZChatCursor_UpdateObjectFlags);
    RET;


nine:
    LD_D(-13 * 8);
    LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_7);
    goto eight_nine_load;


eight:
    LD_D(2 * 8);
    LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_6);

eight_nine_load:
    PUSH_DE;
    CALL(aReinitSpriteAnimFrame);
    LD_A_addr(wcd4a);
    SLA_A;
    SLA_A;
    SLA_A;
    LD_E_A;
    SLA_A;
    ADD_A_E;
    ADD_A(8 * 8);
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_hld_A;
    POP_AF;
    LD_hl_A;
    LD_A(0x4);
    LD_E_A;
    CALL(aAnimateEZChatCursor_UpdateObjectFlags);
    RET;


ten:
    LD_A(SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1);
    CALL(aReinitSpriteAnimFrame);
    LD_A(0x8);
    LD_E_A;
    CALL(aAnimateEZChatCursor_UpdateObjectFlags);
    RET;


Coords_Zero:
    //dbpixel ['1', '3', '5', '2']
    //dbpixel ['7', '3', '5', '2']
    //dbpixel ['13', '3', '5', '2']
    //dbpixel ['1', '5', '5', '2']
    //dbpixel ['7', '5', '5', '2']
    //dbpixel ['13', '5', '5', '2']
    //dbpixel ['1', '17', '5', '2']
    //dbpixel ['7', '17', '5', '2']
    //dbpixel ['13', '17', '5', '2']


Coords_One:
    //dbpixel ['1', '8', '5', '2']
    //dbpixel ['7', '8', '5', '2']
    //dbpixel ['13', '8', '5', '2']
    //dbpixel ['1', '10', '5', '2']
    //dbpixel ['7', '10', '5', '2']
    //dbpixel ['13', '10', '5', '2']
    //dbpixel ['1', '12', '5', '2']
    //dbpixel ['7', '12', '5', '2']
    //dbpixel ['13', '12', '5', '2']
    //dbpixel ['1', '14', '5', '2']
    //dbpixel ['7', '14', '5', '2']
    //dbpixel ['13', '14', '5', '2']
    //dbpixel ['1', '16', '5', '2']
    //dbpixel ['7', '16', '5', '2']
    //dbpixel ['13', '16', '5', '2']
    //dbpixel ['1', '18', '5', '2']
    //dbpixel ['7', '18', '5', '2']
    //dbpixel ['13', '18', '5', '2']


Coords_Two:
    //dbpixel ['2', '9']  // 00
    //dbpixel ['3', '9']  // 01
    //dbpixel ['4', '9']  // 02
    //dbpixel ['5', '9']  // 03
    //dbpixel ['6', '9']  // 04
    //dbpixel ['2', '11']  // 05
    //dbpixel ['3', '11']  // 06
    //dbpixel ['4', '11']  // 07
    //dbpixel ['5', '11']  // 08
    //dbpixel ['6', '11']  // 09
    //dbpixel ['2', '13']  // 0a
    //dbpixel ['3', '13']  // 0b
    //dbpixel ['4', '13']  // 0c
    //dbpixel ['5', '13']  // 0d
    //dbpixel ['6', '13']  // 0e
    //dbpixel ['2', '15']  // 0f
    //dbpixel ['3', '15']  // 10
    //dbpixel ['4', '15']  // 11
    //dbpixel ['5', '15']  // 12
    //dbpixel ['6', '15']  // 13
    //dbpixel ['8', '9']  // 14
    //dbpixel ['9', '9']  // 15
    //dbpixel ['10', '9']  // 16
    //dbpixel ['11', '9']  // 17
    //dbpixel ['12', '9']  // 18
    //dbpixel ['8', '11']  // 19
    //dbpixel ['9', '11']  // 1a
    //dbpixel ['10', '11']  // 1b
    //dbpixel ['11', '11']  // 1c
    //dbpixel ['12', '11']  // 1d
    //dbpixel ['8', '13']  // 1e
    //dbpixel ['9', '13']  // 1f
    //dbpixel ['10', '13']  // 20
    //dbpixel ['11', '13']  // 21
    //dbpixel ['12', '13']  // 22
    //dbpixel ['14', '9']  // 23
    //dbpixel ['16', '9']  // 24
    //dbpixel ['18', '9']  // 25
    //dbpixel ['8', '15']  // 26
    //dbpixel ['9', '15']  // 27
    //dbpixel ['10', '15']  // 28
    //dbpixel ['11', '15']  // 29
    //dbpixel ['12', '15']  // 2a
    //dbpixel ['14', '11']  // 2b
    //dbpixel ['14', '13']  // 2c
    //dbpixel ['1', '18', '5', '2']  // 2d
    //dbpixel ['7', '18', '5', '2']  // 2e
    //dbpixel ['13', '18', '5', '2']  // 2f


Coords_Three:
    //dbpixel ['2', '10']
    //dbpixel ['8', '10']
    //dbpixel ['14', '10']
    //dbpixel ['2', '12']
    //dbpixel ['8', '12']
    //dbpixel ['14', '12']
    //dbpixel ['2', '14']
    //dbpixel ['8', '14']
    //dbpixel ['14', '14']
    //dbpixel ['2', '16']
    //dbpixel ['8', '16']
    //dbpixel ['14', '16']


Coords_Four:
    //dbpixel ['16', '10']
    //dbpixel ['16', '12']


Coords_Five:
    //dbpixel ['4', '10']
    //dbpixel ['4', '12']


FramesetsIDs_Two:
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 00
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 01
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 02
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 03
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 04
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 05
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 06
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 07
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 08
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 09
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 0a
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 0b
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 0c
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 0d
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 0e
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 0f
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 10
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 11
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 12
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 13
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 14
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 15
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 16
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 17
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 18
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 19
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 1a
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 1b
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 1c
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 1d
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 1e
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 1f
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 20
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 21
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 22
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 23
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 24
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 25
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 26
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 27
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 28
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 29
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 2a
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3'];  // 2b
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_4'];  // 2c
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1'];  // 2d
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1'];  // 2e
    //db ['SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1'];  // 2f


UpdateObjectFlags:
    LD_HL(wcd24);
    AND_A_hl;
    IF_NZ goto update_y_offset;
    LD_A_E;
    LD_HL(wcd23);
    AND_A_hl;
    IF_Z goto reset_y_offset;
    LD_HL(SPRITEANIMSTRUCT_VAR3);
    ADD_HL_BC;
    LD_A_hl;
    AND_A_A;
    IF_Z goto flip_bit_0;
    DEC_hl;
    RET;


flip_bit_0:
    LD_A(0x0);
    LD_hld_A;
    LD_A(0x1);
    XOR_A_hl;
    LD_hl_A;
    AND_A_A;
    IF_NZ goto update_y_offset;

reset_y_offset:
    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    XOR_A_A;
    LD_hl_A;
    RET;


update_y_offset:
    LD_HL(SPRITEANIMSTRUCT_YCOORD);
    ADD_HL_BC;
    LD_A(0xb0);
    SUB_A_hl;
    LD_HL(SPRITEANIMSTRUCT_YOFFSET);
    ADD_HL_BC;
    LD_hl_A;
    RET;

}

void Function11d323(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    LD_HL(mPalette_11d33a);
    LD_DE(wBGPals1);
    LD_BC(16 * PALETTE_SIZE);
    CALL(aCopyBytes);
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

}

void Palette_11d33a(void){
    //rgb ['31', '31', '31']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['31', '16', '31']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['23', '17', '31']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['31', '31', '31']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']
    //rgb ['00', '00', '00']

    return EZChat_GetSeenPokemonByKana();
}

void EZChat_GetSeenPokemonByKana(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_HL(wc648);
    LD_A(LOW(w5_d800));
    LD_addr_A(wcd2d);
    LD_hli_A;
    LD_A(HIGH(w5_d800));
    LD_addr_A(wcd2e);
    LD_hl_A;

    LD_A(LOW(aEZChat_SortedPokemon));
    LD_addr_A(wcd2f);
    LD_A(HIGH(aEZChat_SortedPokemon));
    LD_addr_A(wcd30);

    LD_A(LOW(wc6a8));
    LD_addr_A(wcd31);
    LD_A(HIGH(wc6a8));
    LD_addr_A(wcd32);

    LD_A(LOW(wc64a));
    LD_addr_A(wcd33);
    LD_A(HIGH(wc64a));
    LD_addr_A(wcd34);

    LD_HL(mEZChat_SortedWords);
    // LD_A((EZChat_SortedWords.End - EZChat_SortedWords) / 4);


MasterLoop:
    PUSH_AF;
//  read row
//  offset
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
//  size
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
//  save the pointer to the next row
    PUSH_HL;
//  add de to w3_d000
    LD_HL(w3_d000);
    ADD_HL_DE;
//  recover de from wcd2d (default: w5_d800)
    LD_A_addr(wcd2d);
    LD_E_A;
    LD_A_addr(wcd2e);
    LD_D_A;
//  save bc for later
    PUSH_BC;


loop1:
//  copy 2*bc bytes from 3:hl to 5:de
    LD_A(0x3);
    LDH_addr_A(rSVBK);
    LD_A_hli;
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    POP_AF;
    LD_de_A;
    INC_DE;

    LD_A(0x3);
    LDH_addr_A(rSVBK);
    LD_A_hli;
    PUSH_AF;
    LD_A(0x5);
    LDH_addr_A(rSVBK);
    POP_AF;
    LD_de_A;
    INC_DE;

    DEC_BC;
    LD_A_C;
    OR_A_B;
    IF_NZ goto loop1;

//  recover the pointer from wcd2f (default: EZChat_SortedPokemon)
    LD_A_addr(wcd2f);
    LD_L_A;
    LD_A_addr(wcd30);
    LD_H_A;
//  copy the pointer from [hl] to bc
    LD_A_hli;
    LD_C_A;
    LD_A_hli;
    LD_B_A;
//  store the pointer to the next pointer back in wcd2f
    LD_A_L;
    LD_addr_A(wcd2f);
    LD_A_H;
    LD_addr_A(wcd30);
//  push pop that pointer to hl
    PUSH_BC;
    POP_HL;
    LD_C(0x0);

loop2:
//  Have you seen this Pokemon?
    LD_A_hl;
    CP_A(0xff);
    IF_Z goto done;
    CALL(aEZChat_GetSeenPokemonByKana_CheckSeenMon);
    IF_NZ goto next;
//  If not, skip it.
    INC_HL;
    goto loop2;


next:
//  If so, append it to the list at 5:de, and increase the count.
    LD_A_hli;
    LD_de_A;
    INC_DE;
    XOR_A_A;
    LD_de_A;
    INC_DE;
    INC_C;
    goto loop2;


done:
//  Remember the original value of bc from the table?
//  Well, the stack remembers it, and it's popping it to hl.
    POP_HL;
//  Add the number of seen Pokemon from the list.
    LD_B(0x0);
    ADD_HL_BC;
//  Push pop to bc.
    PUSH_HL;
    POP_BC;
//  Load the pointer from [wcd31] (default: wc6a8)
    LD_A_addr(wcd31);
    LD_L_A;
    LD_A_addr(wcd32);
    LD_H_A;
//  Save the quantity from bc to [hl]
    LD_A_C;
    LD_hli_A;
    LD_A_B;
    LD_hli_A;
//  Save the new value of hl to [wcd31]
    LD_A_L;
    LD_addr_A(wcd31);
    LD_A_H;
    LD_addr_A(wcd32);
//  Recover the pointer from [wcd33] (default: wc64a)
    LD_A_addr(wcd33);
    LD_L_A;
    LD_A_addr(wcd34);
    LD_H_A;
//  Save the current value of de there
    LD_A_E;
    LD_addr_A(wcd2d);
    LD_hli_A;
    LD_A_D;
    LD_addr_A(wcd2e);
//  Save the new value of hl back to [wcd33]
    LD_hli_A;
    LD_A_L;
    LD_addr_A(wcd33);
    LD_A_H;
    LD_addr_A(wcd34);
//  Next row
    POP_HL;
    POP_AF;
    DEC_A;
    IF_Z goto ExitMasterLoop;
    JP(mEZChat_GetSeenPokemonByKana_MasterLoop);


ExitMasterLoop:
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;


CheckSeenMon:
    PUSH_HL;
    PUSH_BC;
    PUSH_DE;
    DEC_A;
    LD_HL(rSVBK);
    LD_E(0x1);
    LD_hl_E;
    CALL(aCheckSeenMon);
    LD_HL(rSVBK);
    LD_E(0x5);
    LD_hl_E;
    POP_DE;
    POP_BC;
    POP_HL;
    RET;

}

void EZChat_GetCategoryWordsByKana(void){
    LDH_A_addr(rSVBK);
    PUSH_AF;
    LD_A(0x3);
    LDH_addr_A(rSVBK);

// load pointers
    LD_HL(mMobileEZChatCategoryPointers);
    LD_BC(mMobileEZChatData_WordAndPageCounts);

// init WRAM registers
    XOR_A_A;
    LD_addr_A(wcd2d);
    INC_A;
    LD_addr_A(wcd2e);

// enter the first loop
    LD_A(14);

loop1:
    PUSH_AF;

// load the pointer to the category
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    PUSH_HL;

// skip to the attributes
    LD_HL(NAME_LENGTH_JAPANESE - 1);
    ADD_HL_DE;

// get the number of words in the category
    LD_A_bc;  // number of entries to copy
    INC_BC;
    INC_BC;
    PUSH_BC;


loop2:
    PUSH_AF;
    PUSH_HL;

// load offset at [hl]
    LD_A_hli;
    LD_E_A;
    LD_A_hl;
    LD_D_A;

// add to w3_d000
    LD_HL(w3_d000);
    ADD_HL_DE;

// copy from wcd2d and increment [wcd2d] in place
    LD_A_addr(wcd2d);
    LD_hli_A;
    INC_A;
    LD_addr_A(wcd2d);

// copy from wcd2e
    LD_A_addr(wcd2e);
    LD_hl_A;

// next entry
    POP_HL;
    LD_DE(8);
    ADD_HL_DE;
    POP_AF;
    DEC_A;
    IF_NZ goto loop2;

// reset and go to next category
    LD_HL(wcd2d);
    XOR_A_A;
    LD_hli_A;
    INC_hl;
    POP_BC;
    POP_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto loop1;
    POP_AF;
    LDH_addr_A(rSVBK);
    RET;

// INCLUDE "data/pokemon/ezchat_order.asm"

    return SelectStartGFX();
}

void SelectStartGFX(void){
// INCBIN "gfx/mobile/select_start.2bpp"
}

void EZChatSlowpokeLZ(void){
// INCBIN "gfx/pokedex/slowpoke.2bpp.lz"
}

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

void EZChat_SortedWords(void){
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
    //dw ['NULL', '0x09'];  // end

// End:

}
