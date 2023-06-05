#include "../constants.h"
#include "text.h"
#include "copy.h"
#include "tilemap.h"
#include "joypad.h"
#include "delay.h"
#include "print_text.h"
#include "pokedex_flags.h"
#include "../charmap.h"

void ClearBox(void) {
    //  Fill a c*b box at hl with blank tiles.
    LD_A(0x7f);
    // fallthrough

    return FillBoxWithByte();
}

void FillBoxWithByte(void) {
row:
    SET_PC(aFillBoxWithByte_row);
    PUSH_BC;
    PUSH_HL;

col:
    SET_PC(aFillBoxWithByte_col);
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

//  Fill a c*b box at hl with blank tiles.
void ClearBox_Conv(uint16_t hl, uint16_t bc) {
    //  Fill a c*b box at hl with blank tiles.
    return FillBoxWithByte_Conv(hl, bc, 0x7f);
}

void FillBoxWithByte_Conv(uint16_t hl, uint16_t bc, uint8_t byte) {
    uint16_t bctemp, hltemp;

    do {
        bctemp = bc;
        hltemp = hl;

        do {
            gb_write(hl++, byte);
            bc--;
        } while((bc & 0xFF) != 0);
        hl = hltemp;
        hl += SCREEN_WIDTH;
        bc = bctemp;

        bc -= 0x100;
    } while(((bc & 0xFF00) >> 8) != 0);
}

void ClearTilemap(void) {
    //  Fill wTilemap with blank tiles.

    hlcoord(0, 0, wTilemap);
    LD_A(0x7f);
    LD_BC(wTilemapEnd - wTilemap);
    CALL(aByteFill);

    // Update the BG Map.
    LDH_A_addr(rLCDC);
    BIT_A(rLCDC_ENABLE);
    RET_Z;
    JP(mWaitBGMap);
}

//  Fill wTilemap with blank tiles.
void ClearTilemap_Conv(void) {
    ByteFill_Conv(coord(0, 0, wTilemap), (wTilemapEnd - wTilemap), 0x7F);

    // Update the BG Map.
    // LDH_A_addr(rLCDC);
    // BIT_A(rLCDC_ENABLE);
    // RET_Z;
    // JP(mWaitBGMap);
}

void ClearScreen(void) {
    LD_A(PAL_BG_TEXT);
    hlcoord(0, 0, wAttrmap);
    LD_BC(SCREEN_WIDTH * SCREEN_HEIGHT);
    CALL(aByteFill);
    JR(mClearTilemap);
}

void ClearScreen_Conv(void) {
    ByteFill_Conv(coord(0, 0, wAttrmap), (SCREEN_WIDTH * SCREEN_HEIGHT), PAL_BG_TEXT);
    ClearTilemap_Conv();
}

void Textbox(void) {
    //  Draw a text box at hl with room for b lines of c characters each.
    //  Places a border around the textbox, then switches the palette to the
    //  text black-and-white scheme.
    PUSH_BC;
    PUSH_HL;
    CALL(aTextboxBorder);
    POP_HL;
    POP_BC;
    JR(mTextboxPalette);
}

//  Draw a text box at hl with room for b lines of c characters each.
//  Places a border around the textbox, then switches the palette to the
//  text black-and-white scheme.
void Textbox_Conv(uint16_t hl, uint8_t b, uint8_t c) {
    TextboxBorder_Conv(hl, b, c);
    return TextboxPalette_Conv(hl, c, b);
}

void TextboxBorder(void) {
    // Top
    PUSH_HL;
    LD_A(0x79);
    LD_hli_A;
    INC_A;  // "─"
    CALL(aTextboxBorder_PlaceChars);
    INC_A;  // "┐"
    LD_hl_A;
    POP_HL;

    // Middle
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;

row:
    PUSH_HL;
    LD_A(0x7c);
    LD_hli_A;
    LD_A(0x7f);
    CALL(aTextboxBorder_PlaceChars);
    LD_hl(0x7c);
    POP_HL;

    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    DEC_B;
    IF_NZ goto row;

    // Bottom
    LD_A(0x7d);
    LD_hli_A;
    LD_A(0x7a);
    CALL(aTextboxBorder_PlaceChars);
    LD_hl(0x7e);

    RET;

PlaceChars:
    //  Place char a c times.
    LD_D_C;

loop:
    LD_hli_A;
    DEC_D;
    IF_NZ goto loop;
    RET;
}

void TextboxBorder_Conv(uint16_t hl, uint8_t b, uint8_t c) {
    uint16_t temphl = hl;
    uint8_t id = 0x79;

//  Place char id x times.
#define TEXTBOXBORDER_PLACECHARS(x) \
    do { \
        uint8_t d = (x); \
\
        do { \
            gb_write(hl++, id); \
        } while(--d != 0); \
    } while(0)

    // Top
    gb_write(hl++, id++);
    TEXTBOXBORDER_PLACECHARS(c);
    gb_write(hl, id);

    hl = temphl + SCREEN_WIDTH;

    // Middle
    do {
        temphl = hl; 
        gb_write(hl++, 0x7c);
        id = 0x7f;
        TEXTBOXBORDER_PLACECHARS(c);
        gb_write(hl, 0x7c);
        hl = temphl + SCREEN_WIDTH;
    } while(--b != 0);

    // Bottom
    gb_write(hl++, 0x7d);
    id = 0x7a;
    TEXTBOXBORDER_PLACECHARS(c);
    gb_write(hl, 0x7e);
}

void TextboxPalette(void) {
    //  Fill text box width c height b at hl with pal 7
    LD_DE(wAttrmap - wTilemap);
    ADD_HL_DE;
    INC_B;
    INC_B;
    INC_C;
    INC_C;
    LD_A(PAL_BG_TEXT);

col:
    PUSH_BC;
    PUSH_HL;

row:
    LD_hli_A;
    DEC_C;
    IF_NZ goto row;
    POP_HL;
    LD_DE(SCREEN_WIDTH);
    ADD_HL_DE;
    POP_BC;
    DEC_B;
    IF_NZ goto col;
    RET;
}

void TextboxPalette_Conv(uint16_t hl, uint8_t c, uint8_t b) {
    //  Fill text box width c height b at hl with pal 7
    hl += (wAttrmap - wTilemap);
    b += 2;
    c += 2;

    do {
        uint8_t tempc = c;
        uint8_t tempb = b;
        uint16_t temphl = hl;

        do {
            gb_write(hl++, PAL_BG_TEXT);
        } while(--c != 0);
        hl = temphl + SCREEN_WIDTH;
        b = tempb;
        c = tempc;
    } while(--b != 0);
}

void SpeechTextbox(void) {
    //  Standard textbox.
    hlcoord(TEXTBOX_X, TEXTBOX_Y, wTilemap);
    LD_B(TEXTBOX_INNERH);
    LD_C(TEXTBOX_INNERW);
    JP(mTextbox);
}

//  Standard textbox.
void SpeechTextbox_Conv(void) {
    return Textbox_Conv(coord(TEXTBOX_X, TEXTBOX_Y, wTilemap), TEXTBOX_INNERH, TEXTBOX_INNERW);
}

void GameFreakText(void) {
    //  //  unreferenced
    // text ['"ゲームフりーク！"']  // "GAMEFREAK!"
    // done ['?']

    return RadioTerminator();
}

void RadioTerminator(void) {
    LD_HL(mRadioTerminator_stop);
    RET;

stop:
    // text_end ['?']

    return PrintText();
}

uint16_t RadioTerminator_Conv(void) {
    return mRadioTerminator_stop;
}

void PrintText(void) {
    CALL(aSetUpTextbox);
    // fallthrough

    return BuenaPrintText();
}

void PrintText_Conv(uint16_t hl) {
    // CALL(aSetUpTextbox);

    SetUpTextbox_Conv();
    // fallthrough

    return BuenaPrintText_Conv(hl);
}

void BuenaPrintText(void) {
    PUSH_HL;
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    CALL(aClearBox);
    POP_HL;
    // fallthrough

    return PrintTextboxText();
}

void BuenaPrintText_Conv(uint16_t hl) {
    // PUSH_HL;
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    // CALL(aClearBox);
    ClearBox_Conv(coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap), ((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    // POP_HL;
    // fallthrough

    return PrintTextboxText_Conv(hl);
}

void PrintTextboxText(void) {
    bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    CALL(aPlaceHLTextAtBC);
    RET;
}

void PrintTextboxText_Conv(uint16_t hl) {
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // CALL(aPlaceHLTextAtBC);
    // RET;

    PlaceHLTextAtBC_Conv(hl, coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap));
}

void SetUpTextbox(void) {
    PUSH_HL;
    CALL(aSpeechTextbox);
    CALL(aUpdateSprites);
    CALL(aApplyTilemap);
    POP_HL;
    RET;
}

void SetUpTextbox_Conv(void) {
    SpeechTextbox_Conv();
    CALL(aUpdateSprites);
    ApplyTilemap_Conv();
}

void PlaceString(void) {
    PUSH_HL;
    // fallthrough

    return PlaceNextChar();
}

void PlaceString_Conv(struct TextCmdState* state, uint16_t hl) {
    // fallthrough
    state->hltemp = state->hl;
    state->hl = hl;
    PlaceNextChar_Conv(state);
    state->hl = state->hltemp;
}

void PlaceNextChar(void) {
    LD_A_de;
    CP_A(0x50);
    JR_NZ(mCheckDict);
    LD_B_H;
    LD_C_L;
    POP_HL;
    RET;
}

void PlaceNextChar_Conv(struct TextCmdState* state) {
    while(1)
    {
        uint8_t c = gb_read(state->de);
        if(c == 0x50) 
        {
            state->bc = state->hl;
            return;
        }
        CheckDict_Conv(state, c);
    }
}

void DummyChar(void) {
    //  //  unreferenced
    POP_DE;
    // fallthrough

    return NextChar();
}

void NextChar(void) {
    INC_DE;
    JP(mPlaceNextChar);
}

void NextChar_Conv(struct TextCmdState* state) {
    // INC_DE;
    state->de++;
    // JP(mPlaceNextChar);
}

void CheckDict(void) {
    // dict: MACRO
    // assert CHARLEN(\1) == 1
    // if \1 == 0
    //     and a
    // else
    //     cp \1
    // endc
    // if ISCONST(\2)
    //     ; Replace a character with another one
    //     jr nz, .not\@
    //     ld a, \2
    // .not\@:
    // elif STRSUB("\2", 1, 1) == "."
    //     ; Locals can use a short jump
    //     jr z, \2
    // else
    //     jp z, \2
    // endc
    // ENDM

    // dict ['"<MOBILE>"', 'MobileScriptChar']
    CP_A(CHAR_MOBILE);
    JP_Z(aMobileScriptChar);
    // dict ['"<LINE>"', 'LineChar']
    CP_A(CHAR_LINE);
    JP_Z(aLineChar);
    // dict ['"<NEXT>"', 'NextLineChar']
    CP_A(CHAR_NEXT);
    JP_Z(aNextLineChar);
    // dict ['"<CR>"', 'CarriageReturnChar']
    CP_A(CHAR_CR);
    JP_Z(aCarriageReturnChar);
    // dict ['"<NULL>"', 'NullChar']
    AND_A_A; // CP_A(CHAR_NULL);
    JP_Z(aNullChar);
    // dict ['"<SCROLL>"', '_ContTextNoPause']
    CP_A(CHAR_SCROLL);
    JP_Z(av_ContTextNoPause);
    // dict ['"<_CONT>"', '_ContText']
    CP_A(CHAR__CONT);
    JP_Z(av_ContText);
    // dict ['"<PARA>"', 'Paragraph']
    CP_A(CHAR_PARA);
    JP_Z(aParagraph);
    // dict ['"<MOM>"', 'PrintMomsName']
    CP_A(CHAR_MOM);
    JP_Z(aPrintMomsName);
    // dict ['"<PLAYER>"', 'PrintPlayerName']
    CP_A(CHAR_PLAYER);
    JP_Z(aPrintPlayerName);
    // dict ['"<RIVAL>"', 'PrintRivalName']
    CP_A(CHAR_RIVAL);
    JP_Z(aPrintRivalName);
    // dict ['"<ROUTE>"', 'PlaceJPRoute']
    CP_A(CHAR_ROUTE);
    JP_Z(aPlaceJPRoute);
    // dict ['"<WATASHI>"', 'PlaceWatashi']
    CP_A(CHAR_WATASHI);
    JP_Z(aPlaceWatashi);
    // dict ['"<KOKO_WA>"', 'PlaceKokoWa']
    CP_A(CHAR_KOKO_WA);
    JP_Z(aPlaceKokoWa);
    // dict ['"<RED>"', 'PrintRedsName']
    CP_A(CHAR_RED);
    JP_Z(aPrintRedsName);
    // dict ['"<GREEN>"', 'PrintGreensName']
    CP_A(CHAR_GREEN);
    JP_Z(aPrintGreensName);
    // dict ['"#"', 'PlacePOKe']
    CP_A(CHAR_POKe);
    JP_Z(aPlacePOKe);
    // dict ['"<PC>"', 'PCChar']
    CP_A(CHAR_PC);
    JP_Z(aPCChar);
    // dict ['"<ROCKET>"', 'RocketChar']
    CP_A(CHAR_ROCKET);
    JP_Z(aRocketChar);
    // dict ['"<TM>"', 'TMChar']
    CP_A(CHAR_TM);
    JP_Z(aTMChar);
    // dict ['"<TRAINER>"', 'TrainerChar']
    CP_A(CHAR_TRAINER);
    JP_Z(aTrainerChar);
    // dict ['"<KOUGEKI>"', 'PlaceKougeki']
    CP_A(CHAR_KOUGEKI);
    JP_Z(aPlaceKougeki);
    // dict ['"<LF>"', 'LineFeedChar']
    CP_A(CHAR_LF);
    JP_Z(aLineFeedChar);
    // dict ['"<CONT>"', 'ContText']
    CP_A(CHAR_CONT);
    JP_Z(aContText);
    // dict ['"<……>"', 'SixDotsChar']
    CP_A(CHAR_SIXDOTS);
    JP_Z(aSixDotsChar);
    // dict ['"<DONE>"', 'DoneText']
    CP_A(CHAR_DONE);
    JP_Z(aDoneText);
    // dict ['"<PROMPT>"', 'PromptText']
    CP_A(CHAR_PROMPT);
    JP_Z(aPromptText);
    // dict ['"<PKMN>"', 'PlacePKMN']
    CP_A(CHAR_PKMN);
    JP_Z(aPlacePKMN);
    // dict ['"<POKE>"', 'PlacePOKE']
    CP_A(CHAR_POKE);
    JP_Z(aPlacePOKE);
    // dict ['"0b"', 'NextChar']
    CP_A(0xb); // No idea if this is correct
    JP_Z(aNextChar);
    // dict ['"¯"', '" "']
    CP_A(CHAR_SOFTLB);
    IF_NZ goto notsoftlb;
    LD_A(CHAR_SPACE);
notsoftlb:
    // dict ['"<DEXEND>"', 'PlaceDexEnd']
    CP_A(CHAR_DEXEND);
    JP_Z(aPlaceDexEnd);
    // dict ['"<TARGET>"', 'PlaceMoveTargetsName']
    CP_A(CHAR_TARGET);
    JP_Z(aPlaceMoveTargetsName);
    // dict ['"<USER>"', 'PlaceMoveUsersName']
    CP_A(CHAR_USER);
    JP_Z(aPlaceMoveUsersName);
    // dict ['"<ENEMY>"', 'PlaceEnemysName']
    CP_A(CHAR_ENEMY);
    JP_Z(aPlaceEnemysName);
    // dict ['"<PLAY_G>"', 'PlaceGenderedPlayerName']
    CP_A(CHAR_PLAY_G);
    JP_Z(aPlaceGenderedPlayerName);
    // dict ['"ﾟ"', '.place']  // should be .diacritic
    CP_A(0xe4);
    IF_Z goto place;
    // dict ['"ﾞ"', '.place']  // should be .diacritic
    CP_A(0xe5);
    IF_Z goto place;
    goto not_diacritic;

diacritic:
    //
    SET_PC(aCheckDict_diacritic);  //  unreferenced
    LD_B_A;
    CALL(aDiacritic);
    JP(mNextChar);

not_diacritic:
    CP_A(FIRST_REGULAR_TEXT_CHAR);
    IF_NC goto place;
    //  dakuten or handakuten
    CP_A(0x40);
    IF_NC goto handakuten;
    //  dakuten
    CP_A(FIRST_HIRAGANA_DAKUTEN_CHAR);
    IF_NC goto hiragana_dakuten;
    //  katakana dakuten
    ADD_A(0x85 - 0x05);
    goto place_dakuten;

hiragana_dakuten:
    ADD_A(0xb6 - 0x26);

place_dakuten:
    LD_B(0xe5);  // dakuten
    CALL(aDiacritic);
    goto place;

handakuten:
    CP_A(0x44);
    IF_NC goto hiragana_handakuten;
    //  katakana handakuten
    ADD_A(0x99 - 0x40);
    goto place_handakuten;

hiragana_handakuten:
    ADD_A(0xca - 0x44);

place_handakuten:
    LD_B(0xe4);  // handakuten
    CALL(aDiacritic);

place:
    LD_hli_A;
    CALL(aPrintLetterDelay);
    JP(mNextChar);
}

void CheckDict_Conv(struct TextCmdState* state, uint8_t a) {
    // dict: MACRO
    // assert CHARLEN(\1) == 1
    // if \1 == 0
    //     and a
    // else
    //     cp \1
    // endc
    // if ISCONST(\2)
    //     ; Replace a character with another one
    //     jr nz, .not\@
    //     ld a, \2
    // .not\@:
    // elif STRSUB("\2", 1, 1) == "."
    //     ; Locals can use a short jump
    //     jr z, \2
    // else
    //     jp z, \2
    // endc
    // ENDM

    // dict ['"<MOBILE>"', 'MobileScriptChar']
    // dict ['"<LINE>"', 'LineChar']
    // dict ['"<NEXT>"', 'NextLineChar']
    // dict ['"<CR>"', 'CarriageReturnChar']
    // dict ['"<NULL>"', 'NullChar']
    // dict ['"<SCROLL>"', '_ContTextNoPause']
    // dict ['"<_CONT>"', '_ContText']
    // dict ['"<PARA>"', 'Paragraph']
    // dict ['"<MOM>"', 'PrintMomsName']
    // dict ['"<PLAYER>"', 'PrintPlayerName']
    // dict ['"<RIVAL>"', 'PrintRivalName']
    // dict ['"<ROUTE>"', 'PlaceJPRoute']
    // dict ['"<WATASHI>"', 'PlaceWatashi']
    // dict ['"<KOKO_WA>"', 'PlaceKokoWa']
    // dict ['"<RED>"', 'PrintRedsName']
    // dict ['"<GREEN>"', 'PrintGreensName']
    // dict ['"#"', 'PlacePOKe']
    // dict ['"<PC>"', 'PCChar']
    // dict ['"<ROCKET>"', 'RocketChar']
    // dict ['"<TM>"', 'TMChar']
    // dict ['"<TRAINER>"', 'TrainerChar']
    // dict ['"<KOUGEKI>"', 'PlaceKougeki']
    // dict ['"<LF>"', 'LineFeedChar']
    // dict ['"<CONT>"', 'ContText']
    // dict ['"<……>"', 'SixDotsChar']
    // dict ['"<DONE>"', 'DoneText']
    // dict ['"<PROMPT>"', 'PromptText']
    // dict ['"<PKMN>"', 'PlacePKMN']
    // dict ['"<POKE>"', 'PlacePOKE']
    // dict ['"0b"', 'NextChar']
    // dict ['"¯"', '" "']
    // dict ['"<DEXEND>"', 'PlaceDexEnd']
    // dict ['"<TARGET>"', 'PlaceMoveTargetsName']
    // dict ['"<USER>"', 'PlaceMoveUsersName']
    // dict ['"<ENEMY>"', 'PlaceEnemysName']
    // dict ['"<PLAY_G>"', 'PlaceGenderedPlayerName']
    // dict ['"ﾟ"', '.place']  // should be .diacritic
    // dict ['"ﾞ"', '.place']  // should be .diacritic
    switch(a)
    {
    case CHAR_MOBILE: return MobileScriptChar_Conv(state);
    case CHAR_LINE:   return LineChar_Conv(state);
    case CHAR_NEXT:   return NextLineChar_Conv(state);
    case CHAR_CR:     return CarriageReturnChar_Conv(state);
    case CHAR_NULL:   return NullChar_Conv(state);
    case CHAR_SCROLL: return v_ContTextNoPause_Conv(state);
    case CHAR__CONT:  return v_ContText_Conv(state);
    case CHAR_PARA:   return Paragraph_Conv(state);
    case CHAR_MOM:    return PrintMomsName_Conv(state);
    case CHAR_PLAYER: return PrintPlayerName_Conv(state);
    case CHAR_RIVAL:  return PrintRivalName_Conv(state);
    case CHAR_ROUTE:  return PlaceJPRoute_Conv(state);
    case CHAR_WATASHI:return PlaceWatashi_Conv(state);
    case CHAR_KOKO_WA:return PlaceKokoWa_Conv(state);
    case CHAR_RED:    return PrintRedsName_Conv(state);
    case CHAR_GREEN:  return PrintGreensName_Conv(state);
    case CHAR_POKe:   return PlacePOKe_Conv(state);
    case CHAR_PC:     return PCChar_Conv(state);
    case CHAR_ROCKET: return RocketChar_Conv(state);
    case CHAR_TM:     return TMChar_Conv(state);
    case CHAR_TRAINER:return TrainerChar_Conv(state);
    case CHAR_KOUGEKI:return PlaceKougeki_Conv(state);
    case CHAR_LF:     return LineFeedChar_Conv(state);
    case CHAR_CONT:   return ContText_Conv(state);
    case CHAR_SIXDOTS:return SixDotsChar_Conv(state);
    case CHAR_DONE:   return DoneText_Conv(state);
    case CHAR_PROMPT: return PromptText_Conv(state);
    case CHAR_PKMN:   return PlacePKMN_Conv(state);
    case CHAR_POKE:   return PlacePOKE_Conv(state);
    case 0xb:         return NextChar_Conv(state);
    case CHAR_SOFTLB: a = CHAR_SPACE; break;
    case CHAR_DEXEND: return PlaceDexEnd_Conv(state);
    case CHAR_TARGET: return PlaceDexEnd_Conv(state);
    case CHAR_USER: return PlaceDexEnd_Conv(state);
    case CHAR_ENEMY: return PlaceDexEnd_Conv(state);
    case CHAR_PLAY_G: return PlaceDexEnd_Conv(state);
    case 0xe4:
    case 0xe5: goto diacritic;
    }
    goto not_diacritic;

diacritic:
    //
    // SET_PC(aCheckDict_diacritic);  //  unreferenced
    // LD_B_A;
    // CALL(aDiacritic);
    Diacritic_Conv();

    // JP(mNextChar);
    NextChar_Conv(state);
    return;

not_diacritic:
    // CP_A(FIRST_REGULAR_TEXT_CHAR);
    // IF_NC goto place;
    if(a < FIRST_REGULAR_TEXT_CHAR)
    {
    //     //  dakuten or handakuten
    //     CP_A(0x40);
    //     IF_NC goto handakuten;
    //     //  dakuten
    //     CP_A(FIRST_HIRAGANA_DAKUTEN_CHAR);
    //     IF_NC goto hiragana_dakuten;
    //     //  katakana dakuten
    //     ADD_A(0x85 - 0x05);
    //     goto place_dakuten;

    // hiragana_dakuten:
    //     ADD_A(0xb6 - 0x26);

    // place_dakuten:
    //     LD_B(0xe5);  // dakuten
    //     CALL(aDiacritic);
    //     goto place;

    // handakuten:
    //     CP_A(0x44);
    //     IF_NC goto hiragana_handakuten;
    //     //  katakana handakuten
    //     ADD_A(0x99 - 0x40);
    //     goto place_handakuten;

    // hiragana_handakuten:
    //     ADD_A(0xca - 0x44);

    // place_handakuten:
    //     LD_B(0xe4);  // handakuten
    //     CALL(aDiacritic);
    }

place:
//     LD_hli_A;
    gb_write(state->hl++, a);

    // CALL(aPrintLetterDelay);
    PrintLetterDelay_Conv();
    NextChar_Conv(state);
//     CALL(aPrintLetterDelay);
//     JP(mNextChar);
}

void MobileScriptChar(void) {
    LD_C_L;
    LD_B_H;
    FARCALL(aRunMobileScript);
    JP(mPlaceNextChar);

    // print_name: MACRO
    //     push de
    //     ld de, \1
    //     jp PlaceCommandCharacter
    // ENDM
}

void MobileScriptChar_Conv(struct TextCmdState* state) {
    // LD_C_L;
    // LD_B_H;
    REG_BC = state->hl;
    FARCALL(aRunMobileScript);
    // JP(mPlaceNextChar);
}

#define PRINT_NAME(x) \
    do {\
        PUSH_DE;\
        LD_DE(x);\
        JP(aPlaceCommandCharacter);\
    } while(0)

void PrintMomsName(void) {
    //  print_name wMomsName
    PRINT_NAME(wMomsName);
    return PrintPlayerName();
}

void PrintMomsName_Conv(struct TextCmdState* state) {
    // print_name wMomsName
    return PlaceCommandCharacter_Conv(state, wMomsName);
}

void PrintPlayerName(void) {
    // print_name wPlayerName
    PRINT_NAME(wPlayerName);
    return PrintRivalName();
}

void PrintPlayerName_Conv(struct TextCmdState* state) {
    // print_name wPlayerName
    return PlaceCommandCharacter_Conv(state, wPlayerName);
}

void PrintRivalName(void) {
    // print_name wRivalName
    PRINT_NAME(wRivalName);
    return PrintRedsName();
}

void PrintRivalName_Conv(struct TextCmdState* state) {
    // print_name wRivalName
    return PlaceCommandCharacter_Conv(state, wRivalName);
}

void PrintRedsName(void) {
    //  print_name wRedsName
    PRINT_NAME(wRedsName);
    return PrintGreensName();
}

void PrintRedsName_Conv(struct TextCmdState* state) {
    // print_name wRedsName
    return PlaceCommandCharacter_Conv(state, wRedsName);
}

void PrintGreensName(void) {
    // print_name wGreensName
    PRINT_NAME(wGreensName);
    return TrainerChar();
}

void PrintGreensName_Conv(struct TextCmdState* state) {
    // print_name wGreensName
    return PlaceCommandCharacter_Conv(state, wGreensName);
}

void TrainerChar(void) {
    // print_name TrainerCharText
    PRINT_NAME(mTrainerCharText);
    return TMChar();
}

void TrainerChar_Conv(struct TextCmdState* state) {
    //  print_name TrainerCharText
    PlaceCommandCharacter_Conv(state, mTrainerCharText);
}

void TMChar(void) {
    //      print_name TMCharText
    PRINT_NAME(mTMCharText);
    return PCChar();
}

void TMChar_Conv(struct TextCmdState* state) {
    //  print_name TMCharText
    PlaceCommandCharacter_Conv(state, mTMCharText);
}

void PCChar(void) {
    //      print_name PCCharText
    PRINT_NAME(mPCCharText);
    return RocketChar();
}

void PCChar_Conv(struct TextCmdState* state) {
    //  print_name PCCharText
    PlaceCommandCharacter_Conv(state, mPCCharText);
}

void RocketChar(void) {
    //  print_name RocketCharText
    PRINT_NAME(mRocketCharText);
    return PlacePOKe();
}

void RocketChar_Conv(struct TextCmdState* state) {
    //  print_name RocketCharText
    PlaceCommandCharacter_Conv(state, mRocketCharText);
}

void PlacePOKe(void) {
    //   print_name PlacePOKeText
    PRINT_NAME(mPlacePOKeText);
    return PlaceKougeki();
}

void PlacePOKe_Conv(struct TextCmdState* state) {
    //  print_name PlacePOKeText
    PlaceCommandCharacter_Conv(state, mPlacePOKeText);
}

void PlaceKougeki(void) {
    // print_name KougekiText
    return SixDotsChar();
}

void PlaceKougeki_Conv(struct TextCmdState* state) {
    // print_name KougekiText
    PlaceCommandCharacter_Conv(state, mKougekiText);
}

void SixDotsChar(void) {
    // print_name SixDotsCharText
    PRINT_NAME(mSixDotsCharText);
    return PlacePKMN();
}

void SixDotsChar_Conv(struct TextCmdState* state) {
    // print_name SixDotsCharText
    PlaceCommandCharacter_Conv(state, mSixDotsCharText);
}

void PlacePKMN(void) {
    //   print_name PlacePKMNText
    PRINT_NAME(mPlacePKMNText);
    return PlacePOKE();
}

void PlacePKMN_Conv(struct TextCmdState* state) {
    // print_name PlacePKMNText
    PlaceCommandCharacter_Conv(state, mPlacePKMNText);
}

void PlacePOKE(void) {
    //   print_name PlacePOKEText
    PRINT_NAME(mPlacePOKEText);
    return PlaceJPRoute();
}

void PlacePOKE_Conv(struct TextCmdState* state) {
    // print_name PlacePOKEText
    PlaceCommandCharacter_Conv(state, mPlacePOKEText);
}

void PlaceJPRoute(void) {
    // print_name PlaceJPRouteText
    PRINT_NAME(mPlaceJPRouteText);
    return PlaceWatashi();
}

void PlaceJPRoute_Conv(struct TextCmdState* state) {
    // print_name PlaceJPRouteText
    PlaceCommandCharacter_Conv(state, mPlaceJPRouteText);
}

void PlaceWatashi(void) {
    // print_name PlaceWatashiText
    PRINT_NAME(mPlaceWatashiText);
    return PlaceKokoWa();
}

void PlaceWatashi_Conv(struct TextCmdState* state) {
    // print_name PlaceWatashiText
    PlaceCommandCharacter_Conv(state, mPlaceWatashiText);
}

void PlaceKokoWa(void) {
    // print_name PlaceKokoWaText
    PRINT_NAME(mPlaceKokoWaText);
    return PlaceMoveTargetsName();
}

void PlaceKokoWa_Conv(struct TextCmdState* state) {
    // print_name PlaceKokoWaText
    PlaceCommandCharacter_Conv(state, mPlaceKokoWaText);
}

void PlaceMoveTargetsName(void) {
    LDH_A_addr(hBattleTurn);
    XOR_A(1);
    JR(mPlaceBattlersName);
}

void PlaceMoveTargetsName_Conv(struct TextCmdState* state) {
    // LDH_A_addr(hBattleTurn);
    // XOR_A(1);
    // JR(mPlaceBattlersName);
    return PlaceBattlersName_Conv(state, (gb_read(hBattleTurn) ^ 1) != 0);
}

void PlaceMoveUsersName(void) {
    LDH_A_addr(hBattleTurn);
    // fallthrough

    return PlaceBattlersName();
}

void PlaceMoveUsersName_Conv(struct TextCmdState* state) {
    // LDH_A_addr(hBattleTurn);
    // fallthrough
    return PlaceBattlersName_Conv(state, gb_read(hBattleTurn) != 0);
}

void PlaceBattlersName(void) {
    PUSH_DE;
    AND_A_A;
    IF_NZ goto enemy;

    LD_DE(wBattleMonNickname);
    JR(mPlaceCommandCharacter);

enemy:
    LD_DE(mEnemyText);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(wEnemyMonNickname);
    JR(mPlaceCommandCharacter);
}

void PlaceBattlersName_Conv(struct TextCmdState* state, bool is_enemy) {
    // PUSH_DE;
    // AND_A_A;
    // IF_NZ goto enemy;
    if(!is_enemy)
    {

        // LD_DE(wBattleMonNickname);
        // JR(mPlaceCommandCharacter);
        return PlaceCommandCharacter_Conv(state, wBattleMonNickname);
    }

// enemy:
    // LD_DE(mEnemyText);
    // CALL(aPlaceString);
    struct TextCmdState temp = {.hl = state->hl, .de = mEnemyText, .bc = state->bc};
    PlaceString_Conv(&temp, state->hl);
    // LD_H_B;
    // LD_L_C;
    state->hl = temp.bc;
    // LD_DE(wEnemyMonNickname);
    // JR(mPlaceCommandCharacter);
    return PlaceCommandCharacter_Conv(state, wEnemyMonNickname);
}

void PlaceEnemysName(void) {
    PUSH_DE;

    LD_A_addr(wLinkMode);
    AND_A_A;
    IF_NZ goto linkbattle;

    LD_A_addr(wTrainerClass);
    CP_A(RIVAL1);
    IF_Z goto rival;
    CP_A(RIVAL2);
    IF_Z goto rival;

    LD_DE(wOTClassName);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(mString_Space);
    CALL(aPlaceString);
    PUSH_BC;
    CALLFAR(aBattle_GetTrainerName);
    POP_HL;
    LD_DE(wStringBuffer1);
    JR(mPlaceCommandCharacter);

rival:
    LD_DE(wRivalName);
    JR(mPlaceCommandCharacter);

linkbattle:
    LD_DE(wOTClassName);
    JR(mPlaceCommandCharacter);
}

void PlaceGenderedPlayerName(void) {
    PUSH_DE;
    LD_DE(wPlayerName);
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_A_addr(wPlayerGender);
    BIT_A(PLAYERGENDER_FEMALE_F);
    LD_DE(mKunSuffixText);
    JR_Z(mPlaceCommandCharacter);
    LD_DE(mChanSuffixText);
    JR(mPlaceCommandCharacter);
}

void PlaceCommandCharacter(void) {
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    POP_DE;
    JP(mNextChar);
}

void PlaceCommandCharacter_Conv(struct TextCmdState* state, uint16_t de) {
    struct TextCmdState tempstate = {.hl = state->hl, .de = de, .bc = state->bc};
    // CALL(aPlaceString);
    PlaceString_Conv(&tempstate, state->hl);

    // LD_H_B;
    // LD_L_C;
    state->hl = tempstate.bc;

    // POP_DE;
    // JP(mNextChar);
    NextChar_Conv(state);
}

void TMCharText(void) {
    //     db "TM@"
    return TrainerCharText();
}

void TrainerCharText(void) {
    // db "TRAINER@"
    return PCCharText();
}

void PCCharText(void) {
    //     db "PC@"
    return RocketCharText();
}

void RocketCharText(void) {
    // db "ROCKET@"
    return PlacePOKeText();
}

void PlacePOKeText(void) {
    //  db "POKé@"
    return KougekiText();
}

void KougekiText(void) {
    //    db "こうげき@"
    return SixDotsCharText();
}

void SixDotsCharText(void) {
    // db "……@"
    return EnemyText();
}

void EnemyText(void) {
    //      db "Enemy @"
    return PlacePKMNText();
}

void PlacePKMNText(void) {
    //  db "<PK><MN>@"
    return PlacePOKEText();
}

void PlacePOKEText(void) {
    //  db "<PO><KE>@"
    return String_Space();
}

void String_Space(void) {
    //   db " @"
    //  These strings have been dummied out.
    return PlaceJPRouteText();
}

void PlaceJPRouteText(void) {
    return PlaceWatashiText();
}

void PlaceWatashiText(void) {
    return PlaceKokoWaText();
}

void PlaceKokoWaText(void) {
    // db "@"
    return KunSuffixText();
}

void KunSuffixText(void) {
    //  db "@"
    return ChanSuffixText();
}

void ChanSuffixText(void) {
    // db "@"

    return NextLineChar();
}

void NextLineChar(void) {
    POP_HL;
    LD_BC(SCREEN_WIDTH * 2);
    ADD_HL_BC;
    PUSH_HL;
    JP(mNextChar);
}

void NextLineChar_Conv(struct TextCmdState* state) {
    // POP_HL;
    // LD_BC(SCREEN_WIDTH * 2);
    // ADD_HL_BC;
    // PUSH_HL;
    state->hltemp += (SCREEN_WIDTH * 2);
    // JP(mNextChar);
    NextChar_Conv(state);
}

void LineFeedChar(void) {
    POP_HL;
    LD_BC(SCREEN_WIDTH);
    ADD_HL_BC;
    PUSH_HL;
    JP(mNextChar);
}

void LineFeedChar_Conv(struct TextCmdState* state) {
    // POP_HL;
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    // PUSH_HL;
    state->hltemp += (SCREEN_WIDTH);
    // JP(mNextChar);
    NextChar_Conv(state);
}

void CarriageReturnChar(void) {
    POP_HL;
    PUSH_DE;
    LD_BC(-wTilemap + 0x10000);
    ADD_HL_BC;
    LD_DE(-SCREEN_WIDTH);
    LD_C(1);

loop:
    LD_A_H;
    AND_A_A;
    IF_NZ goto next;
    LD_A_L;
    CP_A(SCREEN_WIDTH);
    IF_C goto done;

next:
    ADD_HL_DE;
    INC_C;
    goto loop;

done:
    hlcoord(0, 0, wTilemap);
    LD_DE(SCREEN_WIDTH);
    LD_A_C;

loop2:
    AND_A_A;
    IF_Z goto done2;
    ADD_HL_DE;
    DEC_A;
    goto loop2;

done2:
    POP_DE;
    INC_DE;
    LD_A_de;
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    PUSH_HL;
    JP(mNextChar);
}

void CarriageReturnChar_Conv(struct TextCmdState* state) {
    // POP_HL;
    uint16_t hl = state->hltemp;
    // PUSH_DE;
    // uint16_t tempde = state->de;

    // LD_BC(-wTilemap + 0x10000);
    state->bc = -wTilemap + 0x10000;

    // ADD_HL_BC;
    hl += state->bc;
    
    // LD_DE(-SCREEN_WIDTH);
    // LD_C(1);
    uint16_t de = -SCREEN_WIDTH;
    uint8_t c = 1;

    while(1)
    {
        // LD_A_H;
        // AND_A_A;
        // IF_NZ goto next;
        if((hl & 0xff00) == 0)
        {
            // LD_A_L;
            // CP_A(SCREEN_WIDTH);
            // IF_C goto done;
            if((hl & 0xff) < SCREEN_WIDTH)
                break;
        }

    // next:
    //     ADD_HL_DE;
    //     INC_C;
        hl += de;
        c++;
    //     goto loop;
    }

    // hlcoord(0, 0, wTilemap);
    // LD_DE(SCREEN_WIDTH);
    // LD_A_C;
    hl = coord(0, 0, wTilemap);
    de = SCREEN_WIDTH;

    while(c != 0)
    {
        // AND_A_A;
        // IF_Z goto done2;
        // ADD_HL_DE;
        // DEC_A;
        hl += de;
        c--;
        // goto loop2;
    }

// done2:
    // POP_DE;
    // INC_DE;
    // LD_A_de;
    // LD_C_A;
    // LD_B(0);
    state->bc = gb_read(++state->de);
    // ADD_HL_BC;
    // PUSH_HL;
    state->hltemp = hl + state->bc;
    // JP(mNextChar);

    NextChar_Conv(state);
}

void LineChar(void) {
    POP_HL;
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    PUSH_HL;
    JP(mNextChar);
}

void LineChar_Conv(struct TextCmdState* state) {
    // POP_HL;
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    // PUSH_HL;
    state->hltemp = coord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    
    // JP(mNextChar);
    NextChar_Conv(state);
}

void Paragraph(void) {
    PUSH_DE;

    LD_A_addr(wLinkMode);
    CP_A(LINK_COLOSSEUM);
    IF_Z goto linkbattle;
    CP_A(LINK_MOBILE);
    IF_Z goto linkbattle;
    CALL(aLoadBlinkingCursor);

linkbattle:
    CALL(aText_WaitBGMap);
    CALL(aPromptButton);
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    CALL(aClearBox);
    CALL(aUnloadBlinkingCursor);
    LD_C(20);
    CALL(aDelayFrames);
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    POP_DE;
    JP(mNextChar);
}

void Paragraph_Conv(struct TextCmdState* state) {
    // PUSH_DE;

    // LD_A_addr(wLinkMode);
    // CP_A(LINK_COLOSSEUM);
    // IF_Z goto linkbattle;
    // CP_A(LINK_MOBILE);
    // IF_Z goto linkbattle;
    // CALL(aLoadBlinkingCursor);
    uint8_t linkmode = gb_read(wLinkMode);
    if(linkmode != LINK_COLOSSEUM && linkmode != LINK_MOBILE)
        LoadBlinkingCursor_Conv();

// linkbattle:
    // CALL(aText_WaitBGMap);
    // CALL(aPromptButton);
    Text_WaitBGMap_Conv();
    PromptButton_Conv();
    
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    // CALL(aClearBox);
    ClearBox_Conv(coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap), ((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    
    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor_Conv();

    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames_Conv(20);
    
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    state->hl = coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    
    // POP_DE;
    // JP(mNextChar);
    NextChar_Conv(state);
}

void v_ContText(void) {
    LD_A_addr(wLinkMode);
    OR_A_A;
    IF_NZ goto communication;
    CALL(aLoadBlinkingCursor);

communication:
    CALL(aText_WaitBGMap);

    PUSH_DE;
    CALL(aPromptButton);
    POP_DE;

    LD_A_addr(wLinkMode);
    OR_A_A;
    CALL_Z(aUnloadBlinkingCursor);
    // fallthrough

    return v_ContTextNoPause();
}

void v_ContText_Conv(struct TextCmdState* state) {
    // LD_A_addr(wLinkMode);
    // OR_A_A;
    // IF_NZ goto communication;
    // CALL(aLoadBlinkingCursor);
    if(gb_read(wLinkMode) == 0)
        LoadBlinkingCursor_Conv();

// communication:
    // CALL(aText_WaitBGMap);
    Text_WaitBGMap_Conv();

    // PUSH_DE;
    // CALL(aPromptButton);
    // POP_DE;
    PromptButton_Conv();

    // LD_A_addr(wLinkMode);
    // OR_A_A;
    // CALL_Z(aUnloadBlinkingCursor);
    if(gb_read(wLinkMode) == 0)
        UnloadBlinkingCursor_Conv();
    // fallthrough

    return v_ContTextNoPause_Conv(state);
}

void v_ContTextNoPause(void) {
    PUSH_DE;
    CALL(aTextScroll);
    CALL(aTextScroll);
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    POP_DE;
    JP(mNextChar);
}

void v_ContTextNoPause_Conv(struct TextCmdState* state) {
    // PUSH_DE;
    uint16_t de = state->de;

    // CALL(aTextScroll);
    // CALL(aTextScroll);
    TextScroll_Conv(state);
    TextScroll_Conv(state);

    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->hl = coord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    // POP_DE;
    state->de = de;
    
    // JP(mNextChar);
    NextChar_Conv(state);
}

void ContText(void) {
    PUSH_DE;
    LD_DE(mContText_cont);
    LD_B_H;
    LD_C_L;
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    POP_DE;
    JP(mNextChar);

cont:
    // db "<_CONT>@"

    return PlaceDexEnd();
}

void ContText_Conv(struct TextCmdState* state) {
    // PUSH_DE;
    uint16_t de = state->de;
    // LD_DE(mContText_cont);
    state->de = mContText_cont;

    // LD_B_H;
    // LD_C_L;
    state->bc = state->hl;
    // CALL(aPlaceString);
    PlaceString_Conv(state, state->hl);
    // LD_H_B;
    // LD_L_C;
    state->hl = state->bc;
    // POP_DE;
    state->de = de;
    // JP(mNextChar);

    NextChar_Conv(state);
}

void PlaceDexEnd(void) {
    //  Ends a Pokédex entry in Gen 1.
    //  Dex entries are now regular strings.
    LD_hl(0xe8);
    POP_HL;
    RET;
}

//  Ends a Pokédex entry in Gen 1.
//  Dex entries are now regular strings.
void PlaceDexEnd_Conv(struct TextCmdState* state) {
    // LD_hl(0xe8);
    gb_write(state->hl, 0xe8);
    // POP_HL;
    // RET;
}

void PromptText(void) {
    LD_A_addr(wLinkMode);
    CP_A(LINK_COLOSSEUM);
    IF_Z goto ok;
    CP_A(LINK_MOBILE);
    IF_Z goto ok;
    CALL(aLoadBlinkingCursor);

ok:
    CALL(aText_WaitBGMap);
    CALL(aPromptButton);
    LD_A_addr(wLinkMode);
    CP_A(LINK_COLOSSEUM);
    JR_Z(mDoneText);
    CP_A(LINK_MOBILE);
    JR_Z(mDoneText);
    CALL(aUnloadBlinkingCursor);

    return DoneText();
}

void PromptText_Conv(struct TextCmdState* state) {
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_COLOSSEUM);
    // IF_Z goto ok;
    // CP_A(LINK_MOBILE);
    // IF_Z goto ok;
    // CALL(aLoadBlinkingCursor);
    uint8_t linkMode = gb_read(wLinkMode);
    if(linkMode != LINK_COLOSSEUM && linkMode != LINK_MOBILE)
        LoadBlinkingCursor_Conv();

// ok:
    // CALL(aText_WaitBGMap);
    // CALL(aPromptButton);
    Text_WaitBGMap_Conv();
    PromptButton_Conv();

    // LD_A_addr(wLinkMode);
    // CP_A(LINK_COLOSSEUM);
    // JR_Z(mDoneText);
    // CP_A(LINK_MOBILE);
    // JR_Z(mDoneText);
    // CALL(aUnloadBlinkingCursor);
    linkMode = gb_read(wLinkMode);
    if(linkMode != LINK_COLOSSEUM && linkMode != LINK_MOBILE)
        UnloadBlinkingCursor_Conv();

    return DoneText_Conv(state);
}

void DoneText(void) {
    POP_HL;
    LD_DE(mDoneText_stop);
    DEC_DE;
    RET;

stop:
    // text_end ['?']

    return NullChar();
}

void DoneText_Conv(struct TextCmdState* state) {
    // POP_HL;
    state->hl = state->hltemp;
    // LD_DE(mDoneText_stop);
    // DEC_DE;
    state->de = mDoneText_stop - 1;
    // RET;
}

void NullChar(void) {
    LD_A(0xe6);
    LD_hli_A;
    CALL(aPrintLetterDelay);
    JP(mNextChar);
}

void NullChar_Conv(struct TextCmdState* state) {
    // LD_A(0xe6);
    // LD_hli_A;
    gb_write(state->hl++, 0xe6);

    // CALL(aPrintLetterDelay);
    PrintLetterDelay_Conv();
    // JP(mNextChar);
}

void TextScroll(void) {
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    decoord(TEXTBOX_INNERX, TEXTBOX_INNERY - 1, wTilemap);
    LD_A(TEXTBOX_INNERH - 1);

col:
    PUSH_AF;
    LD_C(TEXTBOX_INNERW);

row:
    LD_A_hli;
    LD_de_A;
    INC_DE;
    DEC_C;
    IF_NZ goto row;

    INC_DE;
    INC_DE;
    INC_HL;
    INC_HL;
    POP_AF;
    DEC_A;
    IF_NZ goto col;

    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    LD_A(0x7f);
    LD_BC(TEXTBOX_INNERW);
    CALL(aByteFill);
    LD_C(5);
    CALL(aDelayFrames);
    RET;
}

void TextScroll_Conv(struct TextCmdState* state) {
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // decoord(TEXTBOX_INNERX, TEXTBOX_INNERY - 1, wTilemap);
    state->hl = coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    state->de = coord(TEXTBOX_INNERX, TEXTBOX_INNERY - 1, wTilemap);
    // LD_A(TEXTBOX_INNERH - 1);
    uint8_t y = TEXTBOX_INNERH - 1;
    do {
        // PUSH_AF;
        // LD_C(TEXTBOX_INNERW);
        uint8_t x = TEXTBOX_INNERW;
        do {
        // row:
        //     LD_A_hli;
        //     LD_de_A;
        //     INC_DE;
            gb_write(state->de++, gb_read(state->hl++));
        //     DEC_C;
        //     IF_NZ goto row;
        } while(--x != 0);

        // INC_DE;
        // INC_DE;
        state->de += 2;

        // INC_HL;
        // INC_HL;
        state->hl += 2;

        // POP_AF;
        // DEC_A;
        // IF_NZ goto col;
    } while(--y != 0);

    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    // LD_A(0x7f);
    // LD_BC(TEXTBOX_INNERW);
    // CALL(aByteFill);
    ByteFill_Conv(coord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap), TEXTBOX_INNERW, 0x7f);
    // LD_C(5);
    // CALL(aDelayFrames);
    DelayFrames_Conv(5);
    // RET;
}

void Text_WaitBGMap(void) {
    PUSH_BC;
    LDH_A_addr(hOAMUpdate);
    PUSH_AF;
    LD_A(1);
    LDH_addr_A(hOAMUpdate);

    CALL(aWaitBGMap);

    POP_AF;
    LDH_addr_A(hOAMUpdate);
    POP_BC;
    RET;
}

void Text_WaitBGMap_Conv(void) {
    // PUSH_BC;
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t temp = gb_read(hOAMUpdate);

    // LD_A(1);
    // LDH_addr_A(hOAMUpdate);
    gb_write(hOAMUpdate, 1);

    // CALL(aWaitBGMap);
    WaitBGMap_Conv();

    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    gb_write(hOAMUpdate, temp);

    // POP_BC;
    // RET;
}

void Diacritic(void) {
    RET;
}

// Lol, does nothing.
void Diacritic_Conv(void) {
    // RET;
}

void LoadBlinkingCursor(void) {
    LD_A(0xee);
    ldcoord_a(18, 17, wTilemap);
    RET;
}

void LoadBlinkingCursor_Conv(void) {
    // LD_A(0xee);
    // ldcoord_a(18, 17, wTilemap);
    gb_write(coord(18, 17, wTilemap), 0xee);

    // RET;
}

void UnloadBlinkingCursor(void) {
    lda_coord(17, 17, wTilemap);
    ldcoord_a(18, 17, wTilemap);
    RET;
}

void UnloadBlinkingCursor_Conv(void) {
    // lda_coord(17, 17, wTilemap);
    // ldcoord_a(18, 17, wTilemap);
    gb_write(coord(18, 17, wTilemap), gb_read(coord(17, 17, wTilemap)));
    
    // RET;
}

void PlaceFarString(void) {
    LD_B_A;
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A_B;
    RST(aBankswitch);
    CALL(aPlaceString);

    POP_AF;
    RST(aBankswitch);
    RET;
}

void PlaceFarString_Conv(uint8_t bank, struct TextCmdState* state, uint16_t hl) {
    // LD_B_A;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A_B;
    // RST(aBankswitch);

    bank_push(bank);


    // CALL(aPlaceString);
    PlaceString_Conv(state, hl);

    // POP_AF;
    // RST(aBankswitch);
    // RET;
    bank_pop;
}

void PokeFluteTerminator(void) {
    LD_HL(mPokeFluteTerminator_stop);
    RET;

stop:
    // text_end ['?']

    return PlaceHLTextAtBC();
}

void PlaceHLTextAtBC(void) {
    LD_A_addr(wTextboxFlags);
    PUSH_AF;
    SET_A(NO_TEXT_DELAY_F);
    LD_addr_A(wTextboxFlags);

    CALL(aDoTextUntilTerminator);

    POP_AF;
    LD_addr_A(wTextboxFlags);
    RET;
}

void PlaceHLTextAtBC_Conv(uint16_t hl, uint16_t bc) {
    uint8_t tflags = gb_read(wTextboxFlags);
    gb_write(wTextboxFlags, tflags | (1 << NO_TEXT_DELAY_F));

    struct TextCmdState state = {.hl = hl, .bc = bc, .de = 0};

    uint8_t cmd;
    while(1)
    {
        cmd = gb_read(state.hl++);
        if(cmd == TX_END)
            break;
        // CALL(aDoTextUntilTerminator_TextCommand);
        DoTextUntilTerminator_TextCommand_Conv(&state, cmd);
    }

    gb_write(wTextboxFlags, tflags);
}

void DoTextUntilTerminator(void) {
    LD_A_hli;
    CP_A(TX_END);
    RET_Z;
    CALL(aDoTextUntilTerminator_TextCommand);
    JR(mDoTextUntilTerminator);
}

void DoTextUntilTerminator_Conv(struct TextCmdState* state) {
    while(1)
    {
        // LD_A_hli;
        uint8_t cmd = gb_read(state->hl++);

        // CP_A(TX_END);
        // RET_Z;
        if(cmd == TX_END)
            return;
        
        // CALL(aDoTextUntilTerminator_TextCommand);
        DoTextUntilTerminator_TextCommand_Conv(state, cmd);

        // JR(mDoTextUntilTerminator);
    }
}

void DoTextUntilTerminator_TextCommand(void) {
    PUSH_HL;
    PUSH_BC;
    LD_C_A;
    LD_B(0);
    LD_HL(mTextCommands);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    POP_BC;
    POP_HL;
    JP(REG_DE);
}


void (*const TextCommands[])(struct TextCmdState*) = {
    [TX_START] = TextCommand_START_Conv,
    [TX_RAM] = TextCommand_RAM_Conv,
    [TX_BCD] = TextCommand_BCD_Conv,
    [TX_MOVE] = TextCommand_MOVE_Conv,
    [TX_BOX] = TextCommand_BOX_Conv,
    [TX_LOW] = TextCommand_LOW_Conv,
    [TX_PROMPT_BUTTON] = TextCommand_PROMPT_BUTTON_Conv,
    [TX_SCROLL] = TextCommand_SCROLL_Conv,
    [TX_START_ASM] = TextCommand_START_ASM_Conv,
    [TX_DECIMAL] = TextCommand_DECIMAL_Conv,
    [TX_PAUSE] = TextCommand_PAUSE_Conv,
    [TX_SOUND_DEX_FANFARE_50_79] = TextCommand_SOUND_Conv,
    [TX_DOTS] = TextCommand_DOTS_Conv,
    [TX_WAIT_BUTTON] = TextCommand_WAIT_BUTTON_Conv,
    [TX_SOUND_DEX_FANFARE_20_49] = TextCommand_SOUND_Conv,
    [TX_SOUND_ITEM] = TextCommand_SOUND_Conv,
    [TX_SOUND_CAUGHT_MON] = TextCommand_SOUND_Conv,
    [TX_SOUND_DEX_FANFARE_80_109] = TextCommand_SOUND_Conv,
    [TX_SOUND_FANFARE] = TextCommand_SOUND_Conv,
    [TX_SOUND_SLOT_MACHINE_START] = TextCommand_SOUND_Conv,
    [TX_STRINGBUFFER] = TextCommand_STRINGBUFFER_Conv,
    [TX_DAY] = TextCommand_DAY_Conv,
    [TX_FAR] = TextCommand_FAR_Conv
};

#if defined(__cplusplus) || defined(_MSC_VER)
static_assert(sizeof(TextCommands) / sizeof(void(*)(void)) == NUM_TEXT_CMDS, "");
#else
_Static_assert(sizeof(TextCommands) / sizeof(void(*)(void)) == NUM_TEXT_CMDS, "");
#endif

void DoTextUntilTerminator_TextCommand_Conv(struct TextCmdState* state, uint8_t cmd) {
    TextCommands[cmd](state);
}

// void TextCommands(void) {
    //  entries correspond to TX_* constants (see macros/scripts/text.asm)
    // table_width ['2', 'TextCommands']
    // dw ['TextCommand_START'];  // TX_START
    // dw ['TextCommand_RAM'];  // TX_RAM
    // dw ['TextCommand_BCD'];  // TX_BCD
    // dw ['TextCommand_MOVE'];  // TX_MOVE
    // dw ['TextCommand_BOX'];  // TX_BOX
    // dw ['TextCommand_LOW'];  // TX_LOW
    // dw ['TextCommand_PROMPT_BUTTON'];  // TX_PROMPT_BUTTON
    // dw ['TextCommand_SCROLL'];  // TX_SCROLL
    // dw ['TextCommand_START_ASM'];  // TX_START_ASM
    // dw ['TextCommand_DECIMAL'];  // TX_DECIMAL
    // dw ['TextCommand_PAUSE'];  // TX_PAUSE
    // dw ['TextCommand_SOUND'];  // TX_SOUND_DEX_FANFARE_50_79
    // dw ['TextCommand_DOTS'];  // TX_DOTS
    // dw ['TextCommand_WAIT_BUTTON'];  // TX_WAIT_BUTTON
    // dw ['TextCommand_SOUND'];  // TX_SOUND_DEX_FANFARE_20_49
    // dw ['TextCommand_SOUND'];  // TX_SOUND_ITEM
    // dw ['TextCommand_SOUND'];  // TX_SOUND_CAUGHT_MON
    // dw ['TextCommand_SOUND'];  // TX_SOUND_DEX_FANFARE_80_109
    // dw ['TextCommand_SOUND'];  // TX_SOUND_FANFARE
    // dw ['TextCommand_SOUND'];  // TX_SOUND_SLOT_MACHINE_START
    // dw ['TextCommand_STRINGBUFFER'];  // TX_STRINGBUFFER
    // dw ['TextCommand_DAY'];  // TX_DAY
    // dw ['TextCommand_FAR'];  // TX_FAR
    // assert_table_length ['NUM_TEXT_CMDS']

    // return TextCommand_START();
// }

void TextCommand_START(void) {
    //  write text until "@"
    LD_D_H;
    LD_E_L;
    LD_H_B;
    LD_L_C;
    CALL(aPlaceString);
    LD_H_D;
    LD_L_E;
    INC_HL;
    RET;
}

//  write text until "@"
void TextCommand_START_Conv(struct TextCmdState* state) {
    // LD_D_H;
    // LD_E_L;
    // LD_H_B;
    // LD_L_C;
    // CALL(aPlaceString);
    // struct TextCmdState tempstate = {.hl = state->bc, .de = state->hl};
    state->de = state->hl;
    state->hl = state->bc;
    PlaceString_Conv(state, state->hl);

    // LD_H_D;
    // LD_L_E;
    state->hl = state->de;
    // INC_HL;
    state->hl++;
    // RET;
}

void TextCommand_RAM(void) {
    //  write text from a ram address (little endian)
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    PUSH_HL;
    LD_H_B;
    LD_L_C;
    CALL(aPlaceString);
    POP_HL;
    RET;
}

void TextCommand_RAM_Conv(struct TextCmdState* state) {
    //  write text from a ram address (little endian)
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    state->de = gb_read(state->hl);
    state->hl += 2;

    // PUSH_HL;
    // LD_H_B;
    // LD_L_C;
    // CALL(aPlaceString);
    PlaceString_Conv(&(struct TextCmdState){.hl = state->bc, .de = state->de}, state->hl);
    // POP_HL;
    // RET;
}

void TextCommand_FAR(void) {
    //  write text from a different bank (little endian)
    LDH_A_addr(hROMBank);
    PUSH_AF;

    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;

    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);

    PUSH_HL;
    LD_H_D;
    LD_L_E;
    CALL(aDoTextUntilTerminator);
    POP_HL;

    POP_AF;
    LDH_addr_A(hROMBank);
    LD_addr_A(MBC3RomBank);
    RET;
}

//  write text from a different bank (little endian)
void TextCommand_FAR_Conv(struct TextCmdState* state) {
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    uint8_t oldBank = gb_read(hROMBank);

    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t de = gb_read16(state->hl);
    state->hl += 2;

    // LD_A_hli;
    uint8_t newBank = gb_read(state->hl++);

    // LDH_addr_A(hROMBank);
    gb_write(hROMBank, newBank);
    // LD_addr_A(MBC3RomBank);
    gb_write(MBC3RomBank, newBank);

    // PUSH_HL;
    uint16_t hltemp = state->hl;

    // LD_H_D;
    // LD_L_E;
    state->hl = de;

    // CALL(aDoTextUntilTerminator);
    DoTextUntilTerminator_Conv(state);

    // POP_HL;
    state->hl = hltemp;

    // POP_AF;
    // LDH_addr_A(hROMBank);
    // LD_addr_A(MBC3RomBank);
    gb_write(hROMBank, oldBank);
    gb_write(MBC3RomBank, oldBank);

    // RET;
}

void TextCommand_BCD(void) {
    //  write bcd from address, typically ram
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    PUSH_HL;
    LD_H_B;
    LD_L_C;
    LD_C_A;
    CALL(aPrintBCDNumber);
    LD_B_H;
    LD_C_L;
    POP_HL;
    RET;
}

//  write bcd from address, typically ram
void TextCommand_BCD_Conv(struct TextCmdState* state) {
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    state->de = gb_read16(state->hl);
    state->hl += 2;

    // LD_A_hli;
    uint8_t num = gb_read(state->hl++);

    REG_HL = state->hl;
    PUSH_HL;
    // LD_H_B;
    // LD_L_C;
    REG_HL = state->bc;
    // LD_C_A;
    REG_C = num;
    CALL(aPrintBCDNumber);
    // LD_B_H;
    // LD_C_L;
    state->bc = REG_HL;
    POP_HL;
    state->hl = REG_HL;
    // RET;
}

void TextCommand_MOVE(void) {
    //  move to a new tile
    LD_A_hli;
    LD_addr_A(wMenuScrollPosition + 2);
    LD_C_A;
    LD_A_hli;
    LD_addr_A(wMenuScrollPosition + 2 + 1);
    LD_B_A;
    RET;
}

//  move to a new tile
void TextCommand_MOVE_Conv(struct TextCmdState* state) {
    // LD_A_hli;
    // LD_addr_A(wMenuScrollPosition + 2);
    // LD_C_A;
    // LD_A_hli;
    // LD_addr_A(wMenuScrollPosition + 2 + 1);
    // LD_B_A;
    // RET;
    uint16_t newTile = gb_read16(state->hl);
    state->hl += 2;

    gb_write16(wMenuScrollPosition + 2, newTile);
    state->bc = newTile;
}

void TextCommand_BOX(void) {
    //  draw a box (height, width)
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    LD_B_A;
    LD_A_hli;
    LD_C_A;
    PUSH_HL;
    LD_H_D;
    LD_L_E;
    CALL(aTextbox);
    POP_HL;
    RET;
}

//  draw a box (height, width)
void TextCommand_BOX_Conv(struct TextCmdState* state) {
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t de = gb_read16(state->hl);
    state->hl += 2;

    // LD_A_hli;
    // LD_B_A;
    uint8_t b = gb_read(state->hl++);

    // LD_A_hli;
    // LD_C_A;
    uint8_t c = gb_read(state->hl++);

    // PUSH_HL;
    // LD_H_D;
    // LD_L_E;
    // CALL(aTextbox);
    Textbox_Conv(de, b, c);

    // POP_HL;
    // RET;
}

void TextCommand_LOW(void) {
    //  write text at (1,16)
    bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    RET;
}

//  write text at (1,16)
void TextCommand_LOW_Conv(struct TextCmdState* state) {
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->bc = coord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    // RET;
}

void TextCommand_PROMPT_BUTTON(void) {
    //  wait for button press
    LD_A_addr(wLinkMode);
    CP_A(LINK_COLOSSEUM);
    JP_Z(mTextCommand_WAIT_BUTTON);
    CP_A(LINK_MOBILE);
    JP_Z(mTextCommand_WAIT_BUTTON);

    PUSH_HL;
    CALL(aLoadBlinkingCursor);
    PUSH_BC;
    CALL(aPromptButton);
    POP_BC;
    CALL(aUnloadBlinkingCursor);
    POP_HL;
    RET;
}

//  wait for button press
void TextCommand_PROMPT_BUTTON_Conv(struct TextCmdState* state) {
    (void)state;
    // LD_A_addr(wLinkMode);
    uint8_t linkMode = gb_read(wLinkMode);

    // CP_A(LINK_COLOSSEUM);
    // JP_Z(mTextCommand_WAIT_BUTTON);
    // CP_A(LINK_MOBILE);
    // JP_Z(mTextCommand_WAIT_BUTTON);
    if(linkMode == LINK_COLOSSEUM || linkMode == LINK_MOBILE)
        return TextCommand_WAIT_BUTTON_Conv(state);

    // PUSH_HL;
    // uint16_t hltemp = state->hl;
    // CALL(aLoadBlinkingCursor);
    LoadBlinkingCursor_Conv();

    // PUSH_BC;
    // CALL(aPromptButton);
    // POP_BC;
    PromptButton_Conv();

    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor_Conv();
    // POP_HL;
    // RET;
}

void TextCommand_SCROLL(void) {
    //  pushes text up two lines and sets the BC cursor to the border tile
    //  below the first character column of the text box.
    PUSH_HL;
    CALL(aUnloadBlinkingCursor);
    CALL(aTextScroll);
    CALL(aTextScroll);
    POP_HL;
    bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    RET;
}

//  pushes text up two lines and sets the BC cursor to the border tile
//  below the first character column of the text box.
void TextCommand_SCROLL_Conv(struct TextCmdState* state) {
    // PUSH_HL;
    uint16_t hltemp = state->hl;
    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor_Conv();
    // CALL(aTextScroll);
    // CALL(aTextScroll);
    TextScroll_Conv(state);
    TextScroll_Conv(state);
    // POP_HL;
    state->hl = hltemp;
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->bc = coord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    // RET;
}

void TextCommand_START_ASM(void) {
    //  run assembly code
    BIT_H(7);
    IF_NZ goto not_rom;
    JP_hl;

not_rom:
    LD_A(TX_END);
    LD_hl_A;
    RET;
}

//  run assembly code
void TextCommand_START_ASM_Conv(struct TextCmdState* state) {
    // BIT_H(7);
    // IF_NZ goto not_rom;
    if((state->hl & 0x8000) != 0)
    {
    // not_rom:
    //     LD_A(TX_END);
    //     LD_hl_A;
    //     RET;
        gb_write(state->hl, TX_END);
        return;
    }
    REG_HL = state->hl;
    JP_hl;
}

void TextCommand_DECIMAL(void) {
    //  print a decimal number
    LD_A_hli;
    LD_E_A;
    LD_A_hli;
    LD_D_A;
    LD_A_hli;
    PUSH_HL;
    LD_H_B;
    LD_L_C;
    LD_B_A;
    AND_A(0xf);
    LD_C_A;
    LD_A_B;
    AND_A(0xf0);
    SWAP_A;
    SET_A(PRINTNUM_LEFTALIGN_F);
    LD_B_A;
    CALL(aPrintNum);
    LD_B_H;
    LD_C_L;
    POP_HL;
    RET;
}

//  print a decimal number
void TextCommand_DECIMAL_Conv(struct TextCmdState* state) {
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t de = gb_read16(state->hl);
    state->hl += 2;


    // LD_A_hli;
    // PUSH_HL;
    uint8_t a = gb_read(state->hl++);

    // LD_H_B;
    // LD_L_C;
    // LD_B_A;
    // AND_A(0xf);
    // LD_C_A;
    uint8_t c = a & 0xf;

    // LD_A_B;
    // AND_A(0xf0);
    // SWAP_A;
    // SET_A(PRINTNUM_LEFTALIGN_F);
    // LD_B_A;
    uint8_t b = ((a & 0xf0) >> 4) | (1 << PRINTNUM_LEFTALIGN_F);

    // CALL(aPrintNum);
    PrintNum_Conv(state->bc, de, b, c);

    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // RET;
}

void TextCommand_PAUSE(void) {
    //  wait for button press or 30 frames
    PUSH_HL;
    PUSH_BC;
    CALL(aGetJoypad);
    LDH_A_addr(hJoyDown);
    AND_A(A_BUTTON | B_BUTTON);
    IF_NZ goto done;
    LD_C(30);
    CALL(aDelayFrames);

done:
    POP_BC;
    POP_HL;
    RET;
}

//  wait for button press or 30 frames
void TextCommand_PAUSE_Conv(struct TextCmdState* state) {
    (void)state;
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aGetJoypad);
    GetJoypad_Conv();

    // LDH_A_addr(hJoyDown);
    // AND_A(A_BUTTON | B_BUTTON);
    // IF_NZ goto done;
    if((gb_read(hJoyDown) & (A_BUTTON | B_BUTTON)) == 0)
    {
        // LD_C(30);
        // CALL(aDelayFrames);
        DelayFrames_Conv(30);
    }

// done:
//     POP_BC;
//     POP_HL;
//     RET;
}

void TextCommand_SOUND(void) {
    //  play a sound effect from TextSFX
    PUSH_BC;
    DEC_HL;
    LD_A_hli;
    LD_B_A;
    PUSH_HL;
    LD_HL(mTextSFX);

loop:
    LD_A_hli;
    CP_A(-1);
    IF_Z goto done;
    CP_A_B;
    IF_Z goto play;
    INC_HL;
    INC_HL;
    goto loop;

play:
    PUSH_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    CALL(aPlaySFX);
    CALL(aWaitSFX);
    POP_DE;

done:
    POP_HL;
    POP_BC;
    RET;
}

// void TextSFX(void) {
//     // dbw ['TX_SOUND_DEX_FANFARE_50_79', 'SFX_DEX_FANFARE_50_79']
//     // dbw ['TX_SOUND_FANFARE', 'SFX_FANFARE']
//     // dbw ['TX_SOUND_DEX_FANFARE_20_49', 'SFX_DEX_FANFARE_20_49']
//     // dbw ['TX_SOUND_ITEM', 'SFX_ITEM']
//     // dbw ['TX_SOUND_CAUGHT_MON', 'SFX_CAUGHT_MON']
//     // dbw ['TX_SOUND_DEX_FANFARE_80_109', 'SFX_DEX_FANFARE_80_109']
//     // dbw ['TX_SOUND_SLOT_MACHINE_START', 'SFX_SLOT_MACHINE_START']
//     // db ['-1'];

//     return TextCommand_DOTS();
// }

const uint8_t TextSFX[] =
{
    TX_SOUND_DEX_FANFARE_50_79, SFX_DEX_FANFARE_50_79,
    TX_SOUND_FANFARE, SFX_FANFARE,
    TX_SOUND_DEX_FANFARE_20_49, SFX_DEX_FANFARE_20_49,
    TX_SOUND_ITEM, SFX_ITEM,
    TX_SOUND_CAUGHT_MON, SFX_CAUGHT_MON,
    TX_SOUND_DEX_FANFARE_80_109, SFX_DEX_FANFARE_80_109,
    TX_SOUND_SLOT_MACHINE_START, SFX_SLOT_MACHINE_START,
    -1
};

//  play a sound effect from TextSFX
void TextCommand_SOUND_Conv(struct TextCmdState* state) {
    // PUSH_BC;
    // DEC_HL;
    state->hl--;
    
    // LD_A_hli;
    // LD_B_A;
    uint8_t b = gb_read(state->hl++);

    // PUSH_HL;
    // LD_HL(mTextSFX);

    int i = 0;
    while(1)
    {
        // LD_A_hli;
        uint8_t a = TextSFX[i];
        // CP_A(-1);
        // IF_Z goto done;
        if(a == 0xff)
            break;
        // CP_A_B;
        // IF_Z goto play;
        if(a == b)
        {
        // play:
        //     PUSH_DE;
        //     LD_E_hl;
        //     INC_HL;
        //     LD_D_hl;
            REG_DE = TextSFX[i+1];
            CALL(aPlaySFX);
            CALL(aWaitSFX);
        //     CALL(aPlaySFX);
        //     CALL(aWaitSFX);
        //     POP_DE;
            break;
        }
        // INC_HL;
        // INC_HL;
        i += 2;
    }

// done:
//     POP_HL;
//     POP_BC;
//     RET;
}

void TextCommand_CRY(void) {
    //  //  unreferenced
    //  play a pokemon cry
    PUSH_DE;
    LD_E_hl;
    INC_HL;
    LD_D_hl;
    CALL(aPlayMonCry);
    POP_DE;
    POP_HL;
    POP_BC;
    RET;
}

void TextCommand_DOTS(void) {
    //  wait for button press or 30 frames while printing "…"s
    LD_A_hli;
    LD_D_A;
    PUSH_HL;
    LD_H_B;
    LD_L_C;

loop:
    PUSH_DE;
    LD_A(0x75);
    LD_hli_A;
    CALL(aGetJoypad);
    LDH_A_addr(hJoyDown);
    AND_A(A_BUTTON | B_BUTTON);
    IF_NZ goto next;
    LD_C(10);
    CALL(aDelayFrames);

next:
    POP_DE;
    DEC_D;
    IF_NZ goto loop;

    LD_B_H;
    LD_C_L;
    POP_HL;
    RET;
}

//  wait for button press or 30 frames while printing "…"s
void TextCommand_DOTS_Conv(struct TextCmdState* state) {
    // LD_A_hli;
    // LD_D_A;
    uint8_t d = gb_read(state->hl++);
    // PUSH_HL;
    // LD_H_B;
    // LD_L_C;
    uint16_t hl = state->bc;
    
    do {
        // PUSH_DE;
        // LD_A(0x75);
        // LD_hli_A;
        gb_write(hl++, 0x75);
        
        // CALL(aGetJoypad);
        GetJoypad_Conv();

        // LDH_A_addr(hJoyDown);
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto next;
        if(gb_read((hJoyDown) & (A_BUTTON | B_BUTTON)) == 0)
        {
            // LD_C(10);
            // CALL(aDelayFrames);
            DelayFrames_Conv(10);
        }

        // POP_DE;
        // DEC_D;
        // IF_NZ goto loop;
    } while(--d != 0);

    // LD_B_H;
    // LD_C_L;
    state->bc = hl;

    // POP_HL;
    // RET;
}

void TextCommand_WAIT_BUTTON(void) {
    //  wait for button press
    PUSH_HL;
    PUSH_BC;
    CALL(aPromptButton);
    POP_BC;
    POP_HL;
    RET;
}

//  wait for button press
void TextCommand_WAIT_BUTTON_Conv(struct TextCmdState* state) {
    (void)state;
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aPromptButton);
    // POP_BC;
    // POP_HL;
    // RET;
    PromptButton_Conv();
}

void TextCommand_STRINGBUFFER(void) {
    //  Print a string from one of the following:
    //  0: wStringBuffer3
    //  1: wStringBuffer4
    //  2: wStringBuffer5
    //  3: wStringBuffer2
    //  4: wStringBuffer1
    //  5: wEnemyMonNickname
    //  6: wBattleMonNickname
    LD_A_hli;
    PUSH_HL;
    LD_E_A;
    LD_D(0);
    LD_HL(mStringBufferPointers);
    ADD_HL_DE;
    ADD_HL_DE;
    LD_A(BANK(aStringBufferPointers));
    CALL(aGetFarWord);
    LD_D_H;
    LD_E_L;
    LD_H_B;
    LD_L_C;
    CALL(aPlaceString);
    POP_HL;
    RET;
}

//  Print a string from one of the following:
//  0: wStringBuffer3
//  1: wStringBuffer4
//  2: wStringBuffer5
//  3: wStringBuffer2
//  4: wStringBuffer1
//  5: wEnemyMonNickname
//  6: wBattleMonNickname
void TextCommand_STRINGBUFFER_Conv(struct TextCmdState* state) {
    // LD_A_hli;
    // PUSH_HL;
    uint8_t stringId = gb_read(state->hl++);

    // LD_E_A;
    // LD_D(0);
    // LD_HL(mStringBufferPointers);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A(BANK(aStringBufferPointers));
    // CALL(aGetFarWord);
    uint16_t ptr = GetFarWord_Conv(BANK(aStringBufferPointers), 
        mStringBufferPointers + (2 * stringId));

    // LD_D_H;
    // LD_E_L;
    // LD_H_B;
    // LD_L_C;
    // CALL(aPlaceString);
    PlaceString_Conv(&(struct TextCmdState){.de = ptr, .hl = state->bc}, state->bc);

    // POP_HL;
    // RET;
}

void TextCommand_DAY(void) {
    //  print the day of the week
    CALL(aGetWeekday);
    PUSH_HL;
    PUSH_BC;
    LD_C_A;
    LD_B(0);
    LD_HL(mTextCommand_DAY_Days);
    ADD_HL_BC;
    ADD_HL_BC;
    LD_A_hli;
    LD_H_hl;
    LD_L_A;
    LD_D_H;
    LD_E_L;
    POP_HL;
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    LD_DE(mTextCommand_DAY_Day);
    CALL(aPlaceString);
    POP_HL;
    RET;

/*Currently not used?
Days:
    // dw ['.Sun'];
    // dw ['.Mon'];
    // dw ['.Tues'];
    // dw ['.Wednes'];
    // dw ['.Thurs'];
    // dw ['.Fri'];
    // dw ['.Satur'];

Sun:
    //    db "SUN@"

Mon:
    //    db "MON@"

Tues:
    //   db "TUES@"

Wednes:
    // db "WEDNES@"

Thurs:
    //  db "THURS@"

Fri:
    //    db "FRI@"

Satur:
    //  db "SATUR@"

Day:
    //    db "DAY@"
*/
}

//  print the day of the week
void TextCommand_DAY_Conv(struct TextCmdState* state) {
    // CALL(aGetWeekday);
    uint8_t wd = GetWeekday_Conv();

    // PUSH_HL;
    // PUSH_BC;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mTextCommand_DAY_Days);
    // ADD_HL_BC;
    // ADD_HL_BC;
    uint16_t hl = mTextCommand_DAY_Days + (2 * wd);

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_D_H;
    // LD_E_L;
    uint16_t de = gb_read16(hl);

    // POP_HL;
    struct TextCmdState temp = {.hl = state->bc, .de = de, .bc = state->bc};
    // CALL(aPlaceString);
    PlaceString_Conv(&temp, state->bc);

    // LD_H_B;
    // LD_L_C;
    hl = temp.bc;

    // LD_DE(mTextCommand_DAY_Day);
    // CALL(aPlaceString);
    struct TextCmdState temp2 = {.hl = hl, .de = mTextCommand_DAY_Day, .bc = state->bc};
    PlaceString_Conv(&temp2, hl);
    // POP_HL;
    // RET;

/*Currently not used?
Days:
    // dw ['.Sun'];
    // dw ['.Mon'];
    // dw ['.Tues'];
    // dw ['.Wednes'];
    // dw ['.Thurs'];
    // dw ['.Fri'];
    // dw ['.Satur'];

Sun:
    //    db "SUN@"

Mon:
    //    db "MON@"

Tues:
    //   db "TUES@"

Wednes:
    // db "WEDNES@"

Thurs:
    //  db "THURS@"

Fri:
    //    db "FRI@"

Satur:
    //  db "SATUR@"

Day:
    //    db "DAY@"
*/
}
