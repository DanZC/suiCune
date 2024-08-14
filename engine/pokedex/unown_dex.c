#include "../../constants.h"
#include "unown_dex.h"
#include "../../home/copy.h"

void UpdateUnownDex(void){
    LD_A_addr(wUnownLetter);
    LD_C_A;
    LD_B(NUM_UNOWN);
    LD_HL(wUnownDex);

loop:
    LD_A_hli;
    AND_A_A;
    IF_Z goto done;
    CP_A_C;
    RET_Z ;
    DEC_B;
    IF_NZ goto loop;
    RET;


done:
    DEC_HL;
    LD_hl_C;
    RET;

}

void UpdateUnownDex_Conv(unown_letter_t letter){
    // LD_A_addr(wUnownLetter);
    // LD_C_A;
    // LD_B(NUM_UNOWN);
    // LD_HL(wUnownDex);
    unown_letter_t* hl = wram->wUnownDex;

    for(uint32_t i = 0; i < NUM_UNOWN; ++i) {
    // loop:
        // LD_A_hli;
        // AND_A_A;
        // IF_Z goto done;
        if(hl[i] == 0) {
        // done:
            // DEC_HL;
            // LD_hl_C;
            hl[i] = letter;
            // RET;
            return;
        }
        // CP_A_C;
        // RET_Z ;
        if(hl[i] == letter)
            return;
        // DEC_B;
        // IF_NZ goto loop;
    }
    // RET;
}

// unownword: MACRO
// for n, CHARLEN(\1)
// 	db CHARSUB(\1, n + 1) - "A" + FIRST_UNOWN_CHAR
// endr
// 	db -1
// ENDM
static const uint8_t* StringToUnownWord(uint8_t* dest, const char* str){
    uint32_t i = 0;
    for(; str[i] != 0; ++i){
        dest[i] = (str[i] - 'A') + FIRST_UNOWN_CHAR;
    }
    dest[i] = 0xff;
    return dest;
}

static const char UnownWordA[] = "ANGRY";
static const char UnownWordB[] = "BEAR";
static const char UnownWordC[] = "CHASE";
static const char UnownWordD[] = "DIRECT";
static const char UnownWordE[] = "ENGAGE";
static const char UnownWordF[] = "FIND";
static const char UnownWordG[] = "GIVE";
static const char UnownWordH[] = "HELP";
static const char UnownWordI[] = "INCREASE";
static const char UnownWordJ[] = "JOIN";
static const char UnownWordK[] = "KEEP";
static const char UnownWordL[] = "LAUGH";
static const char UnownWordM[] = "MAKE";
static const char UnownWordN[] = "NUZZLE";
static const char UnownWordO[] = "OBSERVE";
static const char UnownWordP[] = "PERFORM";
static const char UnownWordQ[] = "QUICKEN";
static const char UnownWordR[] = "REASSURE";
static const char UnownWordS[] = "SEARCH";
static const char UnownWordT[] = "TELL";
static const char UnownWordU[] = "UNDO";
static const char UnownWordV[] = "VANISH";
static const char UnownWordW[] = "WANT";
static const char UnownWordX[] = "XXXXX";
static const char UnownWordY[] = "YIELD";
static const char UnownWordZ[] = "ZOOM";

static const char *const UnownWords[] = {
// entries correspond to UNOWN_* form constants
	// table_width 2, UnownWords
    UnownWordA, // unused
    UnownWordA,
    UnownWordB,
    UnownWordC,
    UnownWordD,
    UnownWordE,
    UnownWordF,
    UnownWordG,
    UnownWordH,
    UnownWordI,
    UnownWordJ,
    UnownWordK,
    UnownWordL,
    UnownWordM,
    UnownWordN,
    UnownWordO,
    UnownWordP,
    UnownWordQ,
    UnownWordR,
    UnownWordS,
    UnownWordT,
    UnownWordU,
    UnownWordV,
    UnownWordW,
    UnownWordX,
    UnownWordY,
    UnownWordZ,
};
static_assert(lengthof(UnownWords) == NUM_UNOWN + 1, "");

void PrintUnownWord(void){
    uint8_t buf[16];
    // hlcoord(4, 15, wTilemap);
    // LD_BC(12);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(4, 15, wram->wTilemap), 12, 0x7f);
    // LD_A_addr(wDexCurUnownIndex);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(wUnownDex);
    // ADD_HL_DE;
    // LD_A_hl;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mUnownWords);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A_hli;
    // LD_E_A;
    // LD_D_hl;
    const uint8_t* de = StringToUnownWord(buf, UnownWords[wram->wUnownDex[wram->wDexCurUnownIndex]]);
    // hlcoord(4, 15, wTilemap);
    tile_t* hl = coord(4, 15, wram->wTilemap);

    while(*de != 0xff){
    // loop:
        // LD_A_de;
        // CP_A(-1);
        // RET_Z ;
        // INC_DE;
        // LD_hli_A;
        *(hl++) = *(de++);
        // goto loop;
    }
// INCLUDE "data/pokemon/unown_words.asm"

}
