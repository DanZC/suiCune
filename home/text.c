#include "../constants.h"
#include "text.h"
#include "copy.h"
#include "tilemap.h"
#include "joypad.h"
#include "delay.h"
#include "print_text.h"
#include "pokedex_flags.h"
#include "audio.h"
#include "print_bcd.h"
#include "map_objects.h"
#include "../engine/battle/read_trainer_party.h"
#include "../mobile/mobile_5f.h"
#include "../charmap.h"

// If you encounter text problems, set the value below to 0.
#define USE_CONVERTED_TEXT 1

//  Fill a w*h box at hl with blank tiles.
void ClearBox(tile_t* hl, uint8_t w, uint8_t h) {
    return FillBoxWithByte(hl, w, h, CHAR_SPACE);
}

void FillBoxWithByte(tile_t* hl, uint8_t w, uint8_t h, uint8_t byte) {
    do {
        int i = 0;
        uint8_t w2 = w;
        do {
            hl[i++] = byte;
        } while(--w2 != 0);
        hl += SCREEN_WIDTH;
    } while(--h != 0);
}

//  Fill wTilemap with blank tiles.
void ClearTilemap(void) {
    ByteFill(wram->wTilemap, sizeof(wram->wTilemap), CHAR_SPACE);

    // Update the BG Map.
    // LDH_A_addr(rLCDC);
    // BIT_A(rLCDC_ENABLE);
    if(!bit_test(gb_read(rLCDC), rLCDC_ENABLE))
        return;
    // RET_Z;
    // JP(mWaitBGMap);
    return WaitBGMap();
}

void ClearScreen(void) {
    ByteFill(wram->wAttrmap, (SCREEN_WIDTH * SCREEN_HEIGHT), PAL_BG_TEXT);
    ClearTilemap();
}

//  Draw a text box at hl with room for b lines of c characters each.
//  Places a border around the textbox, then switches the palette to the
//  text black-and-white scheme.
void Textbox(tile_t* hl, uint8_t b, uint8_t c) {
    TextboxBorder(hl, b, c);
    return TextboxPalette(hl, c, b);
}

void TextboxBorder(tile_t* hl, uint8_t b, uint8_t c) {
    tile_t* temphl = hl;
    uint8_t id = CHAR_FRAME_TOP_LEFT;

//  Place char id x times.
#define TEXTBOXBORDER_PLACECHARS(x) \
    do { \
        uint8_t d = (x); \
\
        do { \
            *(hl++) = id; \
        } while(--d != 0); \
    } while(0)

    // Top
    *(hl++) = id++;
    TEXTBOXBORDER_PLACECHARS(c);
    *(hl) = CHAR_FRAME_TOP_RIGHT;

    hl = temphl + SCREEN_WIDTH;

    // Middle
    do {
        temphl = hl; 
        *(hl++) = CHAR_FRAME_SIDE;
        id = CHAR_SPACE;
        TEXTBOXBORDER_PLACECHARS(c);
        *(hl) = CHAR_FRAME_SIDE;
        hl = temphl + SCREEN_WIDTH;
    } while(--b != 0);

    // Bottom
    *(hl++) = CHAR_FRAME_BOTTOM_LEFT;
    id = CHAR_FRAME_TOP;
    TEXTBOXBORDER_PLACECHARS(c);
    *(hl) = CHAR_FRAME_BOTTOM_RIGHT;
}

//  Fill text box width c height b at hl with pal 7
void TextboxPalette(uint8_t* hl, uint8_t c, uint8_t b) {
    hl += (wAttrmap - wTilemap);
    b += 2;
    c += 2;

    for(uint8_t y = 0; y < b; ++y) {
        for(uint8_t x = 0; x < c; ++x) {
            hl[coordidx(x, y)] = PAL_BG_TEXT;
        }
    }
}

//  Standard textbox.
void SpeechTextbox(void) {
    return Textbox(coord(TEXTBOX_X, TEXTBOX_Y, wram->wTilemap), TEXTBOX_INNERH, TEXTBOX_INNERW);
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

const struct TextCmd* RadioTerminator_Conv(void) {
    static const txt_cmd_s stop[] = {
        text_end
    };
    return stop;
}

void PrintText(void) {
    CALL(aSetUpTextbox);
    // fallthrough

    return BuenaPrintText();
}

void PrintText_Conv(uint8_t* hl) {
    // CALL(aSetUpTextbox);

    SetUpTextbox_Conv();
    // fallthrough

    return BuenaPrintText_Conv(hl);
}

void PrintText_Conv2(const struct TextCmd* hl) {
    // CALL(aSetUpTextbox);

    SetUpTextbox_Conv();
    // fallthrough

    return BuenaPrintText_Conv2(hl);
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

void BuenaPrintText_Conv(uint8_t* hl) {
    // PUSH_HL;
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    // CALL(aClearBox);
    ClearBox(wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY), TEXTBOX_INNERW, (TEXTBOX_INNERH - 1));
    // POP_HL;
    // fallthrough

    return PrintTextboxText_Conv(hl);
}

void BuenaPrintText_Conv2(const struct TextCmd* hl) {
    // PUSH_HL;
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    // CALL(aClearBox);
    ClearBox(wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY), TEXTBOX_INNERW, (TEXTBOX_INNERH - 1));
    // POP_HL;
    // fallthrough

    return PrintTextboxText_Conv2(hl);
}

void PrintTextboxText(void) {
    bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    CALL(aPlaceHLTextAtBC);
    RET;
}

void PrintTextboxText_Conv(uint8_t* hl) {
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // CALL(aPlaceHLTextAtBC);
    // RET;

    PlaceHLTextAtBC_Conv(hl, wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY));
}

void PrintTextboxText_Conv2(const struct TextCmd* hl) {
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // CALL(aPlaceHLTextAtBC);
    // RET;
    PlaceHLTextAtBC_Conv2(coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wram->wTilemap), hl);
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
    SpeechTextbox();
    // CALL(aUpdateSprites);
    UpdateSprites_Conv();
    ApplyTilemap_Conv();
}

void PlaceString(void) {
    PUSH_HL;
    // fallthrough

    return PlaceNextChar();
}

bool PlaceString_Conv(struct TextPrintState* state, uint8_t* hl) {
    // fallthrough
    // PEEK("");
    state->hltemp = state->hl;
    state->hl = hl;
    bool res = PlaceNextChar_Conv(state);
    state->hl = state->hltemp;
    return res;
}

// Places string de at position hl.
void PlaceStringSimple(uint8_t* de, uint8_t* hl) {
    // fallthrough
    PlaceString_Conv(&(struct TextPrintState){.de = de, .hl = hl, .bc = 0, .hltemp = hl}, hl);
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

bool PlaceNextChar_Conv(struct TextPrintState* state) {
    while(1)
    {
        uint8_t c = *state->de;
        if(c == CHAR_TERM) 
        {
            state->bc = state->hl;
            return true;
        }
        switch(c)
        {
            case CHAR_MOBILE: MobileScriptChar_Conv(state); continue;
            case CHAR_LINE:   LineChar_Conv(state); continue;
            case CHAR_NEXT:   NextLineChar_Conv(state); continue;
            case CHAR_CR:     CarriageReturnChar_Conv(state); continue;
            case CHAR_NULL:   NullChar_Conv(state); continue;
            case CHAR_SCROLL: v_ContTextNoPause_Conv(state); continue;
            case CHAR__CONT:  v_ContText_Conv(state); continue;
            case CHAR_PARA:   Paragraph_Conv(state); continue;
            case CHAR_MOM:    PrintMomsName_Conv(state); continue;
            case CHAR_PLAYER: PrintPlayerName_Conv(state); continue;
            case CHAR_RIVAL:  PrintRivalName_Conv(state); continue;
            case CHAR_ROUTE:  PlaceJPRoute_Conv(state); continue;
            case CHAR_WATASHI:PlaceWatashi_Conv(state); continue;
            case CHAR_KOKO_WA:PlaceKokoWa_Conv(state); continue;
            case CHAR_RED:    PrintRedsName_Conv(state); continue;
            case CHAR_GREEN:  PrintGreensName_Conv(state); continue;
            case CHAR_POKe:   PlacePOKe_Conv(state); continue;
            case CHAR_PC:     PCChar_Conv(state); continue;
            case CHAR_ROCKET: RocketChar_Conv(state); continue;
            case CHAR_TM:     TMChar_Conv(state); continue;
            case CHAR_TRAINER:TrainerChar_Conv(state); continue;
            case CHAR_KOUGEKI:PlaceKougeki_Conv(state); continue;
            case CHAR_LF:     LineFeedChar_Conv(state); continue;
            case CHAR_CONT:   ContText_Conv(state); continue;
            case CHAR_SIXDOTS:SixDotsChar_Conv(state); continue;
            case CHAR_DONE:   return DoneText_Conv(state);
            case CHAR_PROMPT: return PromptText_Conv(state);
            case CHAR_PKMN:   PlacePKMN_Conv(state); continue;
            case CHAR_POKE:   PlacePOKE_Conv(state); continue;
            case 0xb:         NextChar_Conv(state); continue;
            case CHAR_SOFTLB: c = CHAR_SPACE; break;
            case CHAR_DEXEND: return PlaceDexEnd_Conv(state);
            case CHAR_TARGET: PlaceMoveTargetsName_Conv(state); continue;
            case CHAR_USER:   PlaceMoveUsersName_Conv(state); continue;
            case CHAR_ENEMY:  PlaceEnemysName_Conv(state); continue;
            case CHAR_PLAY_G: PlaceGenderedPlayerName_Conv(state); continue;
            case 0xe4:
            case 0xe5: {
            // diacritic:
                //
                // SET_PC(aCheckDict_diacritic);  //  unreferenced
                // LD_B_A;
                // CALL(aDiacritic);
                Diacritic_Conv();

                // JP(mNextChar);
                NextChar_Conv(state);
                continue;
            }
        }
        // goto not_diacritic;

    // not_diacritic:
        // CP_A(FIRST_REGULAR_TEXT_CHAR);
        // IF_NC goto place;
        if(c < FIRST_REGULAR_TEXT_CHAR)
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
        *(state->hl++) = c;

        // CALL(aPrintLetterDelay);
        PrintLetterDelay_Conv();
        NextChar_Conv(state);
        // CALL(aPrintLetterDelay);
        // JP(mNextChar);
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

void NextChar_Conv(struct TextPrintState* state) {
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

void CheckDict_Conv(struct TextPrintState* state, uint8_t a) {
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
    (void)state, (void)a;
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

void MobileScriptChar_Conv(struct TextPrintState* state) {
    (void)state;
    // LD_C_L;
    // LD_B_H;
    state->bc = state->hl;
    // FARCALL(aRunMobileScript);
    RunMobileScript(state);
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

void PrintMomsName_Conv(struct TextPrintState* state) {
    // print_name wMomsName
    return PlaceCommandCharacter_Conv(state, wram->wMomsName);
}

void PrintPlayerName(void) {
    // print_name wPlayerName
    PRINT_NAME(wPlayerName);
    return PrintRivalName();
}

void PrintPlayerName_Conv(struct TextPrintState* state) {
    // print_name wPlayerName
    return PlaceCommandCharacter_Conv(state, wram->wPlayerName);
}

void PrintRivalName(void) {
    // print_name wRivalName
    PRINT_NAME(wRivalName);
    return PrintRedsName();
}

void PrintRivalName_Conv(struct TextPrintState* state) {
    // print_name wRivalName
    return PlaceCommandCharacter_Conv(state, wram->wRivalName);
}

void PrintRedsName(void) {
    //  print_name wRedsName
    PRINT_NAME(wRedsName);
    return PrintGreensName();
}

void PrintRedsName_Conv(struct TextPrintState* state) {
    // print_name wRedsName
    return PlaceCommandCharacter_Conv(state, wram->wRedsName);
}

void PrintGreensName(void) {
    // print_name wGreensName
    PRINT_NAME(wGreensName);
    return TrainerChar();
}

void PrintGreensName_Conv(struct TextPrintState* state) {
    // print_name wGreensName
    return PlaceCommandCharacter_Conv(state, wram->wGreensName);
}

void TrainerChar(void) {
    // print_name TrainerCharText
    PRINT_NAME(mTrainerCharText);
    return TMChar();
}

void TrainerChar_Conv(struct TextPrintState* state) {
    //  print_name TrainerCharText
    uint8_t buffer[8];
    PlaceCommandCharacter_Conv(state, U82CA(buffer, "TRAINER@"));
}

void TMChar(void) {
    //      print_name TMCharText
    PRINT_NAME(mTMCharText);
    return PCChar();
}

void TMChar_Conv(struct TextPrintState* state) {
    //  print_name TMCharText
    uint8_t buffer[8];
    PlaceCommandCharacter_Conv(state, U82CA(buffer, "TM@"));
}

void PCChar(void) {
    //      print_name PCCharText
    PRINT_NAME(mPCCharText);
    return RocketChar();
}

void PCChar_Conv(struct TextPrintState* state) {
    //  print_name PCCharText
    uint8_t buffer[8];
    PlaceCommandCharacter_Conv(state, U82CA(buffer, "PC@"));
}

void RocketChar(void) {
    //  print_name RocketCharText
    PRINT_NAME(mRocketCharText);
    return PlacePOKe();
}

void RocketChar_Conv(struct TextPrintState* state) {
    //  print_name RocketCharText
    uint8_t buffer[16];
    PlaceCommandCharacter_Conv(state, U82CA(buffer, "ROCKET@")); // mRocketCharText
}

void PlacePOKe(void) {
    //   print_name PlacePOKeText
    PRINT_NAME(mPlacePOKeText);
    return PlaceKougeki();
}

void PlacePOKe_Conv(struct TextPrintState* state) {
    //  print_name PlacePOKeText
    uint8_t buffer[16];
    PlaceCommandCharacter_Conv(state, U82CA(buffer, "POKé@")); // mPlacePOKeText
}

void PlaceKougeki(void) {
    // print_name KougekiText
    return SixDotsChar();
}

void PlaceKougeki_Conv(struct TextPrintState* state) {
    // print_name KougekiText
    PlaceCommandCharacter_Conv(state, Utf8ToCrystal("@")); // mKougekiText
}

void SixDotsChar(void) {
    // print_name SixDotsCharText
    PRINT_NAME(mSixDotsCharText);
    return PlacePKMN();
}

void SixDotsChar_Conv(struct TextPrintState* state) {
    // print_name SixDotsCharText
    uint8_t buffer[8];
    PlaceCommandCharacter_Conv(state, U82CA(buffer, "……@")); // mSixDotsCharText
}

void PlacePKMN(void) {
    //   print_name PlacePKMNText
    PRINT_NAME(mPlacePKMNText);
    return PlacePOKE();
}

void PlacePKMN_Conv(struct TextPrintState* state) {
    // print_name PlacePKMNText
    uint8_t buffer[16];
    PlaceCommandCharacter_Conv(state, U82CA(buffer, "<PK><MN>@")); // mPlacePKMNText
}

void PlacePOKE(void) {
    //   print_name PlacePOKEText
    PRINT_NAME(mPlacePOKEText);
    return PlaceJPRoute();
}

void PlacePOKE_Conv(struct TextPrintState* state) {
    // print_name PlacePOKEText
    uint8_t buffer[16];
    PlaceCommandCharacter_Conv(state, U82CA(buffer, "<PO><KE>@")); // mPlacePOKEText
}

void PlaceJPRoute(void) {
    // print_name PlaceJPRouteText
    PRINT_NAME(mPlaceJPRouteText);
    return PlaceWatashi();
}

void PlaceJPRoute_Conv(struct TextPrintState* state) {
    // print_name PlaceJPRouteText
    PlaceCommandCharacter_Conv(state, Utf8ToCrystal("@")); // mPlaceJPRouteText
}

void PlaceWatashi(void) {
    // print_name PlaceWatashiText
    PRINT_NAME(mPlaceWatashiText);
    return PlaceKokoWa();
}

void PlaceWatashi_Conv(struct TextPrintState* state) {
    // print_name PlaceWatashiText
    PlaceCommandCharacter_Conv(state, Utf8ToCrystal("@")); // mPlaceWatashiText
}

void PlaceKokoWa(void) {
    // print_name PlaceKokoWaText
    PRINT_NAME(mPlaceKokoWaText);
    return PlaceMoveTargetsName();
}

void PlaceKokoWa_Conv(struct TextPrintState* state) {
    // print_name PlaceKokoWaText
    PlaceCommandCharacter_Conv(state, Utf8ToCrystal("@")); // mPlaceKokoWaText
}

void PlaceMoveTargetsName(void) {
    LDH_A_addr(hBattleTurn);
    XOR_A(1);
    JR(mPlaceBattlersName);
}

void PlaceMoveTargetsName_Conv(struct TextPrintState* state) {
    // LDH_A_addr(hBattleTurn);
    // XOR_A(1);
    // JR(mPlaceBattlersName);
    return PlaceBattlersName_Conv(state, (hram->hBattleTurn ^ 1) != 0);
}

void PlaceMoveUsersName(void) {
    LDH_A_addr(hBattleTurn);
    // fallthrough

    return PlaceBattlersName();
}

void PlaceMoveUsersName_Conv(struct TextPrintState* state) {
    // LDH_A_addr(hBattleTurn);
    // fallthrough
    return PlaceBattlersName_Conv(state, hram->hBattleTurn != TURN_PLAYER);
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

void PlaceBattlersName_Conv(struct TextPrintState* state, bool is_enemy) {
    uint8_t buffer[16];
    // PUSH_DE;
    // AND_A_A;
    // IF_NZ goto enemy;
    if(!is_enemy)
    {

        // LD_DE(wBattleMonNickname);
        // JR(mPlaceCommandCharacter);
        return PlaceCommandCharacter_Conv(state, wram->wBattleMonNickname);
    }

// enemy:
    // LD_DE(mEnemyText);
    // CALL(aPlaceString);
    struct TextPrintState temp = {.hl = state->hl, .de = U82CA(buffer, "Enemy @"), .bc = state->bc};
    PlaceString_Conv(&temp, state->hl);
    // LD_H_B;
    // LD_L_C;
    state->hl = temp.bc;
    // LD_DE(wEnemyMonNickname);
    // JR(mPlaceCommandCharacter);
    return PlaceCommandCharacter_Conv(state, wram->wEnemyMonNickname);
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

void PlaceEnemysName_Conv(struct TextPrintState* state) {
    uint8_t buffer[8];
    // PUSH_DE;

    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto linkbattle;

    if(wram->wLinkMode != LINK_NULL) {
    // linkbattle:
        // LD_DE(wOTClassName);
        // JR(mPlaceCommandCharacter);
        return PlaceCommandCharacter_Conv(state, wram->wOTClassName);
    }

    // LD_A_addr(wTrainerClass);
    // CP_A(RIVAL1);
    // IF_Z goto rival;
    // CP_A(RIVAL2);
    // IF_Z goto rival;
    if(wram->wTrainerClass == RIVAL1 || wram->wTrainerClass == RIVAL2) {
    // rival:
        // LD_DE(wRivalName);
        // JR(mPlaceCommandCharacter);
        return PlaceCommandCharacter_Conv(state, wram->wRivalName);
    }

    // LD_DE(wOTClassName);
    // CALL(aPlaceString);
    struct TextPrintState temp = {.hl = state->hl, .de = wram->wOTClassName, .bc = state->bc};
    PlaceString_Conv(&temp, state->hl);
    // LD_H_B;
    // LD_L_C;
    state->bc = temp.bc;
    state->hl = state->bc;
    // LD_DE(mString_Space);
    // CALL(aPlaceString);
    temp.de = U82CA(buffer, " ");
    PlaceString_Conv(&temp, state->hl);
    // PUSH_BC;
    // CALLFAR(aBattle_GetTrainerName);
    uint8_t* s = Battle_GetTrainerName_Conv();
    // POP_HL;
    // LD_DE(wStringBuffer1);
    // JR(mPlaceCommandCharacter);
    state->hl = temp.bc;
    return PlaceCommandCharacter_Conv(state, s);
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

void PlaceGenderedPlayerName_Conv(struct TextPrintState* state) {
    uint8_t buffer[8];
    // PUSH_DE;
    // LD_DE(wPlayerName);
    // CALL(aPlaceString);
    struct TextPrintState temp = {.hl = state->hl, .de = wram->wPlayerName, .bc = state->bc};
    PlaceString_Conv(&temp, state->hl);
    // LD_H_B;
    // LD_L_C;
    state->bc = temp.bc;
    state->hl = temp.bc;
    // LD_A_addr(wPlayerGender);
    // BIT_A(PLAYERGENDER_FEMALE_F);
    // LD_DE(mKunSuffixText);
    // JR_Z(mPlaceCommandCharacter);
    // LD_DE(mChanSuffixText);
    // JR(mPlaceCommandCharacter);
    if(bit_test(wram->wPlayerGender, PLAYERGENDER_FEMALE_F)) {
        return PlaceCommandCharacter_Conv(state, U82CA(buffer, "@")); // Chan suffix (empty string in English)
    }
    return PlaceCommandCharacter_Conv(state, U82CA(buffer, "@")); // Kun suffix (empty string in English)
}

void PlaceCommandCharacter(void) {
    CALL(aPlaceString);
    LD_H_B;
    LD_L_C;
    POP_DE;
    JP(mNextChar);
}

void PlaceCommandCharacter_Conv(struct TextPrintState* state, uint8_t* de) {
    struct TextPrintState tempstate = {.hl = state->hl, .de = de, .bc = state->bc};
    // CALL(aPlaceString);
    PlaceString_Conv(&tempstate, state->hl);

    // LD_H_B;
    // LD_L_C;
    state->hl = tempstate.bc;
    state->bc = tempstate.bc;

    // POP_DE;
    // JP(mNextChar);
    NextChar_Conv(state);
}

// void TMCharText(void) {
    //     db "TM@"
// }

// void TrainerCharText(void) {
    // db "TRAINER@"
// }

// void PCCharText(void) {
    //     db "PC@"
// }

// void RocketCharText(void) {
    // db "ROCKET@"
// }

// void PlacePOKeText(void) {
    //  db "POKé@"
// }

// void KougekiText(void) {
    //    db "こうげき@"
// }

// void SixDotsCharText(void) {
    // db "……@"
// }

// void EnemyText(void) {
    //      db "Enemy @"
// }

// void PlacePKMNText(void) {
    //  db "<PK><MN>@"
// }

// void PlacePOKEText(void) {
    //  db "<PO><KE>@"
// }

// void String_Space(void) {
    //   db " @"
    //  These strings have been dummied out.
// }

// void PlaceJPRouteText(void) {
    // return PlaceWatashiText();
// }

// void PlaceWatashiText(void) {
    // return PlaceKokoWaText();
// }

// void PlaceKokoWaText(void) {
    // db "@"
// }

// void KunSuffixText(void) {
    //  db "@"
// }

// void ChanSuffixText(void) {
    // db "@"
// }

void NextLineChar(void) {
    POP_HL;
    LD_BC(SCREEN_WIDTH * 2);
    ADD_HL_BC;
    PUSH_HL;
    JP(mNextChar);
}

void NextLineChar_Conv(struct TextPrintState* state) {
    // POP_HL;
    // LD_BC(SCREEN_WIDTH * 2);
    // ADD_HL_BC;
    // PUSH_HL;
    state->hltemp += (SCREEN_WIDTH * 2);
    state->hl = state->hltemp;
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

void LineFeedChar_Conv(struct TextPrintState* state) {
    // POP_HL;
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    // PUSH_HL;
    state->hltemp += (SCREEN_WIDTH);
    state->hl = state->hltemp;
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

void CarriageReturnChar_Conv(struct TextPrintState* state) {
    // PEEK("");
    // POP_HL;
    uint8_t* hl = state->hltemp;
    // PUSH_DE;
    state->hltemp = state->de;

    // LD_BC(-wTilemap + 0x10000);

    // ADD_HL_BC;
    
    // LD_DE(-SCREEN_WIDTH);
    // LD_C(1);

    // Find how many lines down the hl is.
    uint8_t c = ((hl - wram->wTilemap) / SCREEN_WIDTH);

    // while(1)
    // {
        // LD_A_H;
        // AND_A_A;
        // IF_NZ goto next;
        // if((hl & 0xff00) == 0)
        // {
            // LD_A_L;
            // CP_A(SCREEN_WIDTH);
            // IF_C goto done;
            // if((hl & 0xff) < SCREEN_WIDTH)
                // break;
        // }

    // next:
    //     ADD_HL_DE;
    //     INC_C;
        // hl -= SCREEN_WIDTH;
        // c++;
    //     goto loop;
    // }

    // hlcoord(0, 0, wTilemap);
    // LD_DE(SCREEN_WIDTH);
    // LD_A_C;

    // Offset hl c lines down and 0 tiles across (resetting its x position to 0).
    hl = wram->wTilemap + coordidx(0, c);

    // while(c != 0)
    // {
        // AND_A_A;
        // IF_Z goto done2;
        // ADD_HL_DE;
        // DEC_A;
        // hl += SCREEN_WIDTH;
        // c--;
        // goto loop2;
    // }

// done2:
    // POP_DE;
    // INC_DE;
    state->de = state->hltemp + 1;
    // LD_A_de;
    // LD_C_A;
    // LD_B(0);
    // ADD_HL_BC;
    state->hl = hl + *state->de;
    // PUSH_HL;
    state->hltemp = state->hl;
    // JP(mNextChar);

    NextChar_Conv(state);
}

void LineChar(void) {
    POP_HL;
    hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    PUSH_HL;
    JP(mNextChar);
}

void LineChar_Conv(struct TextPrintState* state) {
    // PEEK("");
    // POP_HL;
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    // PUSH_HL;
    state->hl = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
    state->hltemp = state->hl;
    
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

void Paragraph_Conv(struct TextPrintState* state) {
    // PEEK("");
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
    Text_WaitBGMap();
    PromptButton_Conv();
    
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    // CALL(aClearBox);
    ClearBox(wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY), TEXTBOX_INNERW, (TEXTBOX_INNERH - 1));
    
    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor_Conv();

    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames(20);
    
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    state->hl = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY);
    
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

void v_ContText_Conv(struct TextPrintState* state) {
    // PEEK("");
    // LD_A_addr(wLinkMode);
    // OR_A_A;
    // IF_NZ goto communication;
    // CALL(aLoadBlinkingCursor);
    if(wram->wLinkMode == LINK_NULL)
        LoadBlinkingCursor_Conv();

// communication:
    // CALL(aText_WaitBGMap);
    Text_WaitBGMap();

    // PUSH_DE;
    // CALL(aPromptButton);
    // POP_DE;
    PromptButton_Conv();

    // LD_A_addr(wLinkMode);
    // OR_A_A;
    // CALL_Z(aUnloadBlinkingCursor);
    if(wram->wLinkMode == LINK_NULL)
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

void v_ContTextNoPause_Conv(struct TextPrintState* state) {
    // PEEK("");
    // PUSH_DE;
    uint8_t* de = state->de;

    // CALL(aTextScroll);
    // CALL(aTextScroll);
    TextScroll_Conv(state);
    TextScroll_Conv(state);

    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->hl = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
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

void ContText_Conv(struct TextPrintState* state) {
    uint8_t buf[4];
    // PUSH_DE;
    uint8_t* de = state->de;
    // LD_DE(mContText_cont);
    state->de = U82CA(buf, "<_CONT>@");

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
bool PlaceDexEnd_Conv(struct TextPrintState* state) {
    // LD_hl(0xe8);
    *(state->hl) = 0xe8;
    // POP_HL;
    // RET;
    return false;
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

bool PromptText_Conv(struct TextPrintState* state) {
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
    Text_WaitBGMap();
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

bool DoneText_Conv(struct TextPrintState* state) {
    static const uint8_t stop[] = {
        TX_END, TX_END,
    };
    // PEEK("");
    // POP_HL;
    state->hl = state->hltemp;
    // LD_DE(mDoneText_stop);
    // DEC_DE;
    state->de = (uint8_t*)stop;
    // RET;
    return false;
}

void NullChar(void) {
    LD_A(0xe6);
    LD_hli_A;
    CALL(aPrintLetterDelay);
    JP(mNextChar);
}

void NullChar_Conv(struct TextPrintState* state) {
    // LD_A(0xe6);
    // LD_hli_A;
    *(state->hl++) = CHAR_QMARK;

    // CALL(aPrintLetterDelay);
    PrintLetterDelay_Conv();
    // JP(mNextChar);
    NextChar_Conv(state);
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

void TextScroll_Conv(struct TextPrintState* state) {
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // decoord(TEXTBOX_INNERX, TEXTBOX_INNERY - 1, wTilemap);
    state->hl = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY);
    state->de = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY - 1);
    // LD_A(TEXTBOX_INNERH - 1);
    uint8_t y = TEXTBOX_INNERH - 1;
    do {
        // PUSH_AF;
        // LD_C(TEXTBOX_INNERW);
        uint8_t x = TEXTBOX_INNERW;
        do {
        // row:
            // LD_A_hli;
            // LD_de_A;
            // INC_DE;
            *(state->de++) = *(state->hl++);
            // DEC_C;
            // IF_NZ goto row;
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
    ByteFill(wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2), TEXTBOX_INNERW, CHAR_SPACE);
    // LD_C(5);
    // CALL(aDelayFrames);
    DelayFrames(5);
    // RET;
}

void Text_WaitBGMap(void) {
    // PUSH_BC;
    // LDH_A_addr(hOAMUpdate);
    // PUSH_AF;
    uint8_t temp = hram->hOAMUpdate;

    // LD_A(1);
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = 1;

    // CALL(aWaitBGMap);
    WaitBGMap();

    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram->hOAMUpdate = temp;

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
    return LoadBlinkingCursor_Conv();
    LD_A(0xee);
    ldcoord_a(18, 17, wTilemap);
    RET;
}

void LoadBlinkingCursor_Conv(void) {
    // LD_A(0xee);
    // ldcoord_a(18, 17, wTilemap);
    // gb_write(coord(18, 17, wTilemap), CHAR_DOWN_CURSOR);
    wram->wTilemap[coordidx(18, 17)] = CHAR_DOWN_CURSOR;

    // RET;
}

void UnloadBlinkingCursor(void) {
    return UnloadBlinkingCursor_Conv();
    lda_coord(17, 17, wTilemap);
    ldcoord_a(18, 17, wTilemap);
    RET;
}

void UnloadBlinkingCursor_Conv(void) {
    // PEEK("");
    // lda_coord(17, 17, wTilemap);
    // ldcoord_a(18, 17, wTilemap);
    // gb_write(coord(18, 17, wTilemap), gb_read(coord(17, 17, wTilemap)));
    wram->wTilemap[coordidx(18, 17)] = wram->wTilemap[coordidx(17, 17)];
    
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

void PlaceFarString_Conv(uint8_t bank, struct TextPrintState* state, uint8_t* hl) {
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
#if USE_CONVERTED_TEXT
    PUSH_HL;
    PUSH_BC;
    PUSH_DE;
    PUSH_AF;
    PEEK("");
    PlaceHLTextAtBC_Conv(GBToRAMAddr(REG_HL), GBToRAMAddr(REG_BC));
    POP_AF;
    POP_DE;
    POP_BC;
    POP_HL;
    RET;
#endif
    LD_A_addr(wTextboxFlags);
    PUSH_AF;
    SET_A(NO_TEXT_DELAY_F);
    LD_addr_A(wTextboxFlags);

    CALL(aDoTextUntilTerminator);

    POP_AF;
    LD_addr_A(wTextboxFlags);
    RET;
}

void PlaceHLTextAtBC_Conv(uint8_t* hl, uint8_t* bc) {
    uint8_t tflags = wram->wTextboxFlags;
    wram->wTextboxFlags = tflags | (1 << NO_TEXT_DELAY_F);

    struct TextPrintState state = {.hl = hl, .bc = bc, .de = 0};

    uint8_t cmd;
    while(1)
    {
        cmd = *(state.hl++);
        if(cmd == TX_END)
            break;
        // CALL(aDoTextUntilTerminator_TextCommand);
        DoTextUntilTerminator_TextCommand_Conv(&state, cmd);
    }

    wram->wTextboxFlags = tflags;
}

void PlaceHLTextAtBC_Conv2(uint8_t* bc, const struct TextCmd* hl) {
    uint8_t tflags = wram->wTextboxFlags;
    wram->wTextboxFlags = tflags | (1 << NO_TEXT_DELAY_F);

    struct TextCmdState state = {.hl = hl, .bc = bc};

    const struct TextCmd* cmd;
    while(1)
    {
        cmd = state.hl++;
        if(cmd->cmd == TX_END)
            break;
        // CALL(aDoTextUntilTerminator_TextCommand);
        DoTextUntilTerminator_TextCommand_Conv2(&state, cmd);
    }

    wram->wTextboxFlags = tflags;
}

void DoTextUntilTerminator(void) {
    while(1)
    {
        SET_PC(mDoTextUntilTerminator);
        LD_A_hli;
        CP_A(TX_END);
        RET_Z;
        CALL(aDoTextUntilTerminator_TextCommand);
    }
    // JR(mDoTextUntilTerminator);
}

void (*const TextCommands[])(struct TextPrintState*) = {
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

void (*const TextCommands2[])(struct TextCmdState*, const struct TextCmd*) = {
    [TX_START] = TextCommand_START_Conv2,
    [TX_RAM] = TextCommand_RAM_Conv2,
    [TX_BCD] = TextCommand_BCD_Conv2,
    [TX_MOVE] = TextCommand_MOVE_Conv2,
    [TX_BOX] = TextCommand_BOX_Conv2,
    [TX_LOW] = TextCommand_LOW_Conv2,
    [TX_PROMPT_BUTTON] = TextCommand_PROMPT_BUTTON_Conv2,
    [TX_SCROLL] = TextCommand_SCROLL_Conv2,
    [TX_START_ASM] = TextCommand_START_ASM_Conv2,
    [TX_DECIMAL] = TextCommand_DECIMAL_Conv2,
    [TX_PAUSE] = TextCommand_PAUSE_Conv2,
    [TX_SOUND_DEX_FANFARE_50_79] = TextCommand_SOUND_Conv2,
    [TX_DOTS] = TextCommand_DOTS_Conv2,
    [TX_WAIT_BUTTON] = TextCommand_WAIT_BUTTON_Conv2,
    [TX_SOUND_DEX_FANFARE_20_49] = TextCommand_SOUND_Conv2,
    [TX_SOUND_ITEM] = TextCommand_SOUND_Conv2,
    [TX_SOUND_CAUGHT_MON] = TextCommand_SOUND_Conv2,
    [TX_SOUND_DEX_FANFARE_80_109] = TextCommand_SOUND_Conv2,
    [TX_SOUND_FANFARE] = TextCommand_SOUND_Conv2,
    [TX_SOUND_SLOT_MACHINE_START] = TextCommand_SOUND_Conv2,
    [TX_STRINGBUFFER] = TextCommand_STRINGBUFFER_Conv2,
    [TX_DAY] = TextCommand_DAY_Conv2,
    [TX_FAR] = TextCommand_FAR_Conv2
};

static_assert(lengthof(TextCommands) == NUM_TEXT_CMDS, "");

void DoTextUntilTerminator_Conv(struct TextPrintState* state) {
    while(1)
    {
        // LD_A_hli;
        uint8_t cmd = *(state->hl++);

        // CP_A(TX_END);
        // RET_Z;
        if(cmd == TX_END)
            return;
        
        // CALL(aDoTextUntilTerminator_TextCommand);
        // DoTextUntilTerminator_TextCommand_Conv(state, cmd);
        TextCommands[cmd](state);

        // JR(mDoTextUntilTerminator);
    }
}

void DoTextUntilTerminator_Conv2(struct TextCmdState* state) {
    while(1)
    {
        // LD_A_hli;
        const struct TextCmd* cmd = state->hl++;

        // CP_A(TX_END);
        // RET_Z;
        if(cmd->cmd == TX_END)
            return;
        
        // CALL(aDoTextUntilTerminator_TextCommand);
        // DoTextUntilTerminator_TextCommand_Conv(state, cmd);
        TextCommands2[cmd->cmd](state, cmd);

        // JR(mDoTextUntilTerminator);
    }
}

void DoTextUntilTerminator_TextCommand(void) {
    // PUSH_HL;
    // PUSH_BC;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mTextCommands);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // POP_BC;
    // POP_HL;
    // JP(REG_DE);
    switch(REG_A)
    {
        case TX_START: CALL(aTextCommand_START); break;
        case TX_RAM: CALL(aTextCommand_RAM); break;
        case TX_BCD: CALL(aTextCommand_BCD); break;
        case TX_MOVE: CALL(aTextCommand_MOVE); break;
        case TX_BOX: CALL(aTextCommand_BOX); break;
        case TX_LOW: CALL(aTextCommand_LOW); break;
        case TX_PROMPT_BUTTON: CALL(aTextCommand_PROMPT_BUTTON); break;
        case TX_SCROLL: CALL(aTextCommand_SCROLL); break;
        case TX_START_ASM: CALL(aTextCommand_START_ASM); break;
        case TX_DECIMAL: CALL(aTextCommand_DECIMAL); break;
        case TX_PAUSE: CALL(aTextCommand_PAUSE); break;
        case TX_SOUND_DEX_FANFARE_50_79: CALL(aTextCommand_SOUND); break;
        case TX_DOTS: CALL(aTextCommand_DOTS); break;
        case TX_WAIT_BUTTON: CALL(aTextCommand_WAIT_BUTTON); break;
        case TX_SOUND_DEX_FANFARE_20_49: CALL(aTextCommand_SOUND); break;
        case TX_SOUND_ITEM: CALL(aTextCommand_SOUND); break;
        case TX_SOUND_CAUGHT_MON: CALL(aTextCommand_SOUND); break;
        case TX_SOUND_DEX_FANFARE_80_109: CALL(aTextCommand_SOUND); break;
        case TX_SOUND_FANFARE: CALL(aTextCommand_SOUND); break;
        case TX_SOUND_SLOT_MACHINE_START: CALL(aTextCommand_SOUND); break;
        case TX_STRINGBUFFER: CALL(aTextCommand_STRINGBUFFER); break;
        case TX_DAY: CALL(aTextCommand_DAY); break;
        case TX_FAR: CALL(aTextCommand_FAR); break;
    }
    RET;
}

void DoTextUntilTerminator_TextCommand_Conv(struct TextPrintState* state, uint8_t cmd) {
    TextCommands[cmd](state);
}

void DoTextUntilTerminator_TextCommand_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    TextCommands2[cmd->cmd](state, cmd);
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
void TextCommand_START_Conv(struct TextPrintState* state) {
    // PEEK("");
    // LD_D_H;
    // LD_E_L;
    state->de = state->hl;
    // LD_H_B;
    // LD_L_C;
    state->hl = state->bc;
    // CALL(aPlaceString);
    printf("text $%04x\n", RAMAddrToGB(state->de));
    PlaceString_Conv(state, state->bc);
    // struct TextPrintState tempstate = {.hl = state->bc, .de = state->hl};

    // LD_H_D;
    // LD_L_E;
    state->hl = state->de;
    // INC_HL;
    state->hl++;
    // RET;
}

//  write text until "@"
void TextCommand_START_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    static const txt_cmd_s cmd_end = {TX_END, .end=0};
    uint8_t tempbuf[1024];
    // PEEK("");
    // LD_D_H;
    // LD_E_L;
    // LD_H_B;
    // LD_L_C;
    // CALL(aPlaceString);
    printf("Text start: %s\n", cmd->text);
    struct TextPrintState temp = {.hl = state->bc, .de = U82CA(tempbuf, cmd->text)};
    if(!PlaceString_Conv(&temp, state->bc)) {
        state->hl = &cmd_end;
    }
    // struct TextPrintState tempstate = {.hl = state->bc, .de = state->hl};

    state->bc = temp.bc;
    // LD_H_D;
    // LD_L_E;
    // INC_HL;
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

void TextCommand_RAM_Conv(struct TextPrintState* state) {
    // PEEK("");
    //  write text from a ram address (little endian)
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t addr = (uint16_t)(state->hl[0] | (state->hl[1] << 8));
    state->hl += 2;
    printf("text_ram $%04x\n", addr);

    uint8_t* de = GBToRAMAddr(addr);

    // PUSH_HL;
    // LD_H_B;
    // LD_L_C;
    // CALL(aPlaceString);
    struct TextPrintState temp = {.hl = state->bc, .de = de, .bc = state->bc};
    PlaceString_Conv(&temp, state->bc);
    // POP_HL;
    state->de = temp.de;
    state->bc = temp.bc;
    // RET;
}

void TextCommand_RAM_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    // PEEK("");
    //  write text from a ram address (little endian)
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // uint16_t addr = (uint16_t)(state->hl[0] | (state->hl[1] << 8));
    // state->hl += 2;
    // printf("text_ram $%04x\n", addr);

    // uint8_t* de = GBToRAMAddr(addr);

    // PUSH_HL;
    // LD_H_B;
    // LD_L_C;
    // CALL(aPlaceString);
    struct TextPrintState temp = {.hl = state->bc, .de = cmd->ram, .bc = state->bc};
    PlaceString_Conv(&temp, state->bc);
    // POP_HL;
    state->bc = temp.bc;
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
void TextCommand_FAR_Conv(struct TextPrintState* state) {
    // PEEK("");
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    uint8_t oldBank = hram->hROMBank;

    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t de_v = (state->hl[0] | (state->hl[1] << 8));
    state->hl += 2;

    // LD_A_hli;
    uint8_t newBank = *(state->hl++);

    printf("text_far bank %d, $%04x\n", newBank, de_v);

    // LDH_addr_A(hROMBank);
    hram->hROMBank = newBank;
    // LD_addr_A(MBC3RomBank);
    gb_write(MBC3RomBank, newBank);

    state->de = GBToRAMAddr(de_v);

    // PUSH_HL;
    uint8_t* hltemp = state->hl;

    // LD_H_D;
    // LD_L_E;
    state->hl = state->de;

    // CALL(aDoTextUntilTerminator);
    DoTextUntilTerminator_Conv(state);

    // POP_HL;
    state->hl = hltemp;

    // POP_AF;
    // LDH_addr_A(hROMBank);
    // LD_addr_A(MBC3RomBank);
    hram->hROMBank = oldBank;
    gb_write(MBC3RomBank, oldBank);

    // RET;
}

//  write text from a different text command ptr (little endian)
void TextCommand_FAR_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    // PEEK("");
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    const struct TextCmd* de = cmd->far_ptr;

    // LD_A_hli;

    // LDH_addr_A(hROMBank);
    // LD_addr_A(MBC3RomBank);

    // PUSH_HL;

    // LD_H_D;
    // LD_L_E;
    struct TextCmdState temp = {.hl = de, .bc = state->bc};

    // CALL(aDoTextUntilTerminator);
    DoTextUntilTerminator_Conv2(&temp);

    // POP_HL;
    state->bc = temp.bc;

    // POP_AF;
    // LDH_addr_A(hROMBank);
    // LD_addr_A(MBC3RomBank);

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
void TextCommand_BCD_Conv(struct TextPrintState* state) {
    PEEK("");
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    state->de = GBToRAMAddr(state->hl[0] | (state->hl[1] << 8));
    state->hl += 2;

    // LD_A_hli;
    uint8_t c = *(state->hl++);

    // PUSH_HL;
    // LD_H_B;
    // LD_L_C;
    // LD_C_A;
    // CALL(aPrintBCDNumber);
    state->bc = PrintBCDNumber_Conv(state->bc, state->de, c);
    state->de += c & 0x1f;
    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // RET;
}

//  write bcd from address, typically ram
void TextCommand_BCD_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;

    // LD_A_hli;

    // PUSH_HL;
    // LD_H_B;
    // LD_L_C;
    // LD_C_A;
    // CALL(aPrintBCDNumber);
    state->bc = PrintBCDNumber_Conv(state->bc, cmd->bcd_addr, cmd->bcd_flags);
    // LD_B_H;
    // LD_C_L;
    // POP_HL;
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
void TextCommand_MOVE_Conv(struct TextPrintState* state) {
    PEEK("");
    // LD_A_hli;
    // LD_addr_A(wMenuScrollPosition + 2);
    // LD_C_A;
    // LD_A_hli;
    // LD_addr_A(wMenuScrollPosition + 2 + 1);
    // LD_B_A;
    // RET;
    uint16_t newTile = ((uint16_t)state->hl[0] | (uint16_t)(state->hl[1] << 8));
    state->hl += 2;

    gb_write16(wMenuScrollPosition + 2, newTile);
    state->bc = wram->wTilemap + (newTile - wTilemap);
}

//  move to a new tile
void TextCommand_MOVE_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    // PEEK("");
    // LD_A_hli;
    // LD_addr_A(wMenuScrollPosition + 2);
    // LD_C_A;
    // LD_A_hli;
    // LD_addr_A(wMenuScrollPosition + 2 + 1);
    // LD_B_A;
    // RET;
    uint16_t newTile = cmd->coord;

    gb_write16(wMenuScrollPosition + 2, wTilemap + newTile);
    state->bc = wram->wTilemap + newTile;
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
void TextCommand_BOX_Conv(struct TextPrintState* state) {
    PEEK("");
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint16_t offset = state->hl[0] | (state->hl[1] << 8);
    uint8_t* de = wram->wTilemap + (offset - wTilemap);
    state->hl += 2;


    // LD_A_hli;
    // LD_B_A;
    uint8_t b = *(state->hl++);

    // LD_A_hli;
    // LD_C_A;
    uint8_t c = *(state->hl++);

    // PUSH_HL;
    // LD_H_D;
    // LD_L_E;
    // CALL(aTextbox);
    Textbox(de, b, c);

    // POP_HL;
    // RET;
}

//  draw a box (height, width)
void TextCommand_BOX_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)state;
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    uint8_t* de = wram->wTilemap + cmd->box_coord;

    // LD_A_hli;
    // LD_B_A;
    uint8_t b = cmd->box_h;

    // LD_A_hli;
    // LD_C_A;
    uint8_t c = cmd->box_w;

    // PUSH_HL;
    // LD_H_D;
    // LD_L_E;
    // CALL(aTextbox);
    Textbox(de, b, c);

    // POP_HL;
    // RET;
}

void TextCommand_LOW(void) {
    //  write text at (1,16)
    bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    RET;
}

//  write text at (1,16)
void TextCommand_LOW_Conv(struct TextPrintState* state) {
    PEEK("");
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->bc = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
    // RET;
}

//  write text at (1,16)
void TextCommand_LOW_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)cmd;
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->bc = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
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
void TextCommand_PROMPT_BUTTON_Conv(struct TextPrintState* state) {
    PEEK("");
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

//  wait for button press
void TextCommand_PROMPT_BUTTON_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)state, (void)cmd;
    // LD_A_addr(wLinkMode);
    uint8_t linkMode = wram->wLinkMode;

    // CP_A(LINK_COLOSSEUM);
    // JP_Z(mTextCommand_WAIT_BUTTON);
    // CP_A(LINK_MOBILE);
    // JP_Z(mTextCommand_WAIT_BUTTON);
    if(linkMode == LINK_COLOSSEUM || linkMode == LINK_MOBILE)
        return TextCommand_WAIT_BUTTON_Conv2(state, cmd);

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
void TextCommand_SCROLL_Conv(struct TextPrintState* state) {
    PEEK("");
    // PUSH_HL;
    uint8_t* hltemp = state->hl;
    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor_Conv();
    // CALL(aTextScroll);
    // CALL(aTextScroll);
    TextScroll_Conv(state);
    TextScroll_Conv(state);
    // POP_HL;
    state->hl = hltemp;
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->bc = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
    // RET;
}

//  pushes text up two lines and sets the BC cursor to the border tile
//  below the first character column of the text box.
void TextCommand_SCROLL_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)cmd;
    // PUSH_HL;
    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor_Conv();
    // CALL(aTextScroll);
    // CALL(aTextScroll);
    struct TextPrintState temp = {.hl = state->bc, .bc = state->bc, .hltemp = state->bc};
    TextScroll_Conv(&temp);
    TextScroll_Conv(&temp);
    // POP_HL;
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->bc = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
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
void TextCommand_START_ASM_Conv(struct TextPrintState* state) {
    // BIT_H(7);
    // IF_NZ goto not_rom;
    // if((state->hl & 0x8000) != 0)
    // {
    // not_rom:
        // LD_A(TX_END);
        // LD_hl_A;
        // RET;
        // gb_write(state->hl, TX_END);
        // return;
    // }
    // REG_HL = state->hl;
    // JP_hl;
    // PUSH_AF;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;
    // PEEK("");
    REG_HL = RAMAddrToGB(state->hl);
    REG_DE = RAMAddrToGB(state->de);
    REG_BC = RAMAddrToGB(state->bc);
    printf("text_asm $%04x (de=%04x, bc=%04x)\n", REG_HL, REG_DE, REG_BC);
    CALL((gb.selected_rom_bank << 14) | REG_HL);
    // PEEK("after");
    uint8_t* hl = GBToRAMAddr(REG_HL);
    state->hl = (hl)? hl: state->hl;
    uint8_t* bc = GBToRAMAddr(REG_BC);
    state->bc = (bc)? bc: state->bc;
    uint8_t* de = GBToRAMAddr(REG_DE);
    state->de = (de)? de: state->de;
    // POP_HL;
    // POP_DE;
    // POP_BC;
    // POP_AF;
    return;
}

//  run assembly code
void TextCommand_START_ASM_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    // BIT_H(7);
    // IF_NZ goto not_rom;
    // if((state->hl & 0x8000) != 0)
    // {
    // not_rom:
        // LD_A(TX_END);
        // LD_hl_A;
        // RET;
        // gb_write(state->hl, TX_END);
        // return;
    // }
    // REG_HL = state->hl;
    // JP_hl;
    // PUSH_AF;
    // PUSH_BC;
    // PUSH_DE;
    // PUSH_HL;
    // PEEK("");
    cmd->as(state);
    // PEEK("after");
    // POP_HL;
    // POP_DE;
    // POP_BC;
    // POP_AF;
    return;
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
void TextCommand_DECIMAL_Conv(struct TextPrintState* state) {
    PEEK("");
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // uint16_t de = gb_read16(state->hl);
    uint16_t de_v = (state->hl[0] | (state->hl[1] << 8));
    state->hl += 2;

    state->de = GBToRAMAddr(de_v);

    // LD_A_hli;
    // PUSH_HL;
    // uint8_t a = gb_read(state->hl++);
    uint8_t a = *(state->hl++);

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

    printf("text_decimal de=$%04x, bytes=%d, digits=%d", de_v, b & 0xf, c);
    if((b & 0xf) == 2) {
        printf(" (%d)\n", *(uint16_t*)state->de);
    }
    else if((b & 0xf) == 1) {
        printf(" (%d)\n", (int)*state->de);
    }
    else {
        printf(" \n");
    }

    // CALL(aPrintNum);
    state->bc = PrintNum_Conv2(state->bc, state->de, b, c);

    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // RET;
}

//  print a decimal number
void TextCommand_DECIMAL_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    // LD_A_hli;
    // LD_E_A;
    // LD_A_hli;
    // LD_D_A;
    // uint16_t de = gb_read16(state->hl);
    uint8_t* de = cmd->dec_addr;

    // LD_A_hli;
    // PUSH_HL;
    // uint8_t a = gb_read(state->hl++);
    uint8_t a = cmd->bytes;

    // LD_H_B;
    // LD_L_C;
    // LD_B_A;
    // AND_A(0xf);
    // LD_C_A;
    uint8_t c = cmd->digits;

    // LD_A_B;
    // AND_A(0xf0);
    // SWAP_A;
    // SET_A(PRINTNUM_LEFTALIGN_F);
    // LD_B_A;
    uint8_t b = (a & 0xf) | (1 << PRINTNUM_LEFTALIGN_F);

    printf("text_decimal de=$%04x, bytes=%d, digits=%d", (de[0] << 8) | de[1], b & 0xf, c);
    // CALL(aPrintNum);
    state->bc = PrintNum_Conv2(state->bc, de, b, c);

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
void TextCommand_PAUSE_Conv(struct TextPrintState* state) {
    PEEK("");
    (void)state;
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aGetJoypad);
    GetJoypad_Conv2();

    // LDH_A_addr(hJoyDown);
    // AND_A(A_BUTTON | B_BUTTON);
    // IF_NZ goto done;
    if(((hram->hJoyDown) & (A_BUTTON | B_BUTTON)) == 0)
    {
        // LD_C(30);
        // CALL(aDelayFrames);
        DelayFrames(30);
    }

// done:
    // POP_BC;
    // POP_HL;
    // RET;
}

//  wait for button press or 30 frames
void TextCommand_PAUSE_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)state, (void)cmd;
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aGetJoypad);
    GetJoypad_Conv2();

    // LDH_A_addr(hJoyDown);
    // AND_A(A_BUTTON | B_BUTTON);
    // IF_NZ goto done;
    if(((hram->hJoyDown) & (A_BUTTON | B_BUTTON)) == 0)
    {
        // LD_C(30);
        // CALL(aDelayFrames);
        DelayFrames(30);
    }

// done:
    // POP_BC;
    // POP_HL;
    // RET;
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

static const uint8_t TextSFX[] =
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
void TextCommand_SOUND_Conv(struct TextPrintState* state) {
    PEEK("");
    // PUSH_BC;
    // DEC_HL;
    state->hl--;
    
    // LD_A_hli;
    // LD_B_A;
    uint8_t b = *(state->hl++);

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
            // PUSH_DE;
            // LD_E_hl;
            // INC_HL;
            // LD_D_hl;
            PlaySFX(TextSFX[i+1]);
            WaitSFX();
            // CALL(aPlaySFX);
            // CALL(aWaitSFX);
            // POP_DE;
            break;
        }
        // INC_HL;
        // INC_HL;
        i += 2;
    }

// done:
    // POP_HL;
    // POP_BC;
    // RET;
}

//  play a sound effect from TextSFX
void TextCommand_SOUND_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)state;
    // PUSH_BC;
    // DEC_HL;
    
    // LD_A_hli;
    // LD_B_A;
    uint8_t b = cmd->cmd;
    switch(b) {
        case TX_SOUND_FANFARE:            printf("sound_fanfare\n"); break;
        case TX_SOUND_CAUGHT_MON:         printf("sound_caught_mon\n"); break;
        case TX_SOUND_SLOT_MACHINE_START: printf("sound_slot_machine_start\n"); break;
        default: printf("sound_unk\n"); break;
    }
    // PUSH_HL;
    // LD_HL(mTextSFX);

    for(int i = 0; ; i += 2)
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
            // PUSH_DE;
            // LD_E_hl;
            // INC_HL;
            // LD_D_hl;
            PlaySFX(TextSFX[i+1]);
            WaitSFX();
            // CALL(aPlaySFX);
            // CALL(aWaitSFX);
            // POP_DE;
            break;
        }
        // INC_HL;
        // INC_HL;
    }

// done:
    // POP_HL;
    // POP_BC;
    // RET;
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

void TextCommand_CRY_Conv(struct TextPrintState* state) {
    PEEK("");
    //  //  unreferenced
    //  play a pokemon cry
    (void)state;
    // PUSH_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // CALL(aPlayMonCry);
    // POP_DE;
    // POP_HL;
    // POP_BC;
    // RET;
    return;
}

void TextCommand_CRY_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    //  //  unreferenced
    //  play a pokemon cry
    (void)state, (void)cmd;
    // PUSH_DE;
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // CALL(aPlayMonCry);
    // POP_DE;
    // POP_HL;
    // POP_BC;
    // RET;
    return;
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
void TextCommand_DOTS_Conv(struct TextPrintState* state) {
    PEEK("");
    // LD_A_hli;
    // LD_D_A;
    uint8_t d = *(state->hl++);
    // PUSH_HL;
    // LD_H_B;
    // LD_L_C;
    uint8_t* hl = state->bc;
    
    do {
        // PUSH_DE;
        // LD_A(0x75);
        // LD_hli_A;
        *(hl++) = 0x75;
        
        // CALL(aGetJoypad);
        GetJoypad_Conv2();

        // LDH_A_addr(hJoyDown);
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto next;
        if(((hram->hJoyDown) & (A_BUTTON | B_BUTTON)) == 0)
        {
            // LD_C(10);
            // CALL(aDelayFrames);
            DelayFrames(10);
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

//  wait for button press or 30 frames while printing "…"s
void TextCommand_DOTS_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    // LD_A_hli;
    // LD_D_A;
    uint8_t d = cmd->n;
    // PUSH_HL;
    // LD_H_B;
    // LD_L_C;
    uint8_t* hl = state->bc;
    
    do {
        // PUSH_DE;
        // LD_A(0x75);
        // LD_hli_A;
        *(hl++) = 0x75;
        
        // CALL(aGetJoypad);
        GetJoypad_Conv2();

        // LDH_A_addr(hJoyDown);
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto next;
        if(((hram->hJoyDown) & (A_BUTTON | B_BUTTON)) == 0)
        {
            // LD_C(10);
            // CALL(aDelayFrames);
            DelayFrames(10);
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
void TextCommand_WAIT_BUTTON_Conv(struct TextPrintState* state) {
    PEEK("");
    (void)state;
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aPromptButton);
    // POP_BC;
    // POP_HL;
    // RET;
    PromptButton_Conv();
}

//  wait for button press
void TextCommand_WAIT_BUTTON_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)state, (void)cmd;
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
void TextCommand_STRINGBUFFER_Conv(struct TextPrintState* state) {
    PEEK("");
    // LD_A_hli;
    // PUSH_HL;
    uint8_t stringId = *(state->hl++);

    // LD_E_A;
    // LD_D(0);
    // LD_HL(mStringBufferPointers);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A(BANK(aStringBufferPointers));
    // CALL(aGetFarWord);
    // uint16_t ptr = GetFarWord_Conv(BANK(aStringBufferPointers), 
    //     mStringBufferPointers + (2 * stringId));
    uint8_t* de;
    switch(stringId) {
        case 0: de = wram->wStringBuffer3; break;
        case 1: de = wram->wStringBuffer4; break;
        case 2: de = wram->wStringBuffer5; break;
        case 3: de = wram->wStringBuffer2; break;
        case 4: de = wram->wStringBuffer1; break;
        case 5: de = wram->wEnemyMonNickname; break;
        case 6: de = wram->wBattleMonNickname; break;
        default: de = NULL; break;
    }

    // LD_D_H;
    // LD_E_L;
    // LD_H_B;
    // LD_L_C;
    // CALL(aPlaceString);
    struct TextPrintState temp = {.de = de, .hl = state->bc};
    PlaceString_Conv(&temp, state->bc);

    state->bc = temp.bc;
    state->de = temp.de;
    // POP_HL;
    // RET;
}

//  Print a string from one of the following:
//  0: wStringBuffer3
//  1: wStringBuffer4
//  2: wStringBuffer5
//  3: wStringBuffer2
//  4: wStringBuffer1
//  5: wEnemyMonNickname
//  6: wBattleMonNickname
void TextCommand_STRINGBUFFER_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    // LD_A_hli;
    // PUSH_HL;
    uint8_t stringId = cmd->n;

    // LD_E_A;
    // LD_D(0);
    // LD_HL(mStringBufferPointers);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A(BANK(aStringBufferPointers));
    // CALL(aGetFarWord);
    // uint16_t ptr = GetFarWord_Conv(BANK(aStringBufferPointers), 
    //     mStringBufferPointers + (2 * stringId));
    uint8_t* de;
    switch(stringId) {
        case 0: de = wram->wStringBuffer3; break;
        case 1: de = wram->wStringBuffer4; break;
        case 2: de = wram->wStringBuffer5; break;
        case 3: de = wram->wStringBuffer2; break;
        case 4: de = wram->wStringBuffer1; break;
        case 5: de = wram->wEnemyMonNickname; break;
        case 6: de = wram->wBattleMonNickname; break;
        default: de = NULL; break;
    }

    // LD_D_H;
    // LD_E_L;
    // LD_H_B;
    // LD_L_C;
    // CALL(aPlaceString);
    struct TextPrintState temp = {.de = de, .hl = state->bc};
    PlaceString_Conv(&temp, state->bc);

    state->bc = temp.bc;
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
void TextCommand_DAY_Conv(struct TextPrintState* state) {
    PEEK("");
    static const char* Days[] = {
        "SUN@",
        "MON@",
        "TUES@",
        "WEDNES@",
        "THURS@",
        "FRI@",
        "SATUR@",
    };

    static const char* Day = "DAY@";

    // CALL(aGetWeekday);
    uint8_t wd = GetWeekday();

    // PUSH_HL;
    // PUSH_BC;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mTextCommand_DAY_Days);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // uint16_t hl = mTextCommand_DAY_Days + (2 * wd);

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_D_H;
    // LD_E_L;
    // uint16_t de = gb_read16(hl);
    uint8_t* de = Utf8ToCrystal(Days[wd]);

    // POP_HL;
    struct TextPrintState temp = {.hl = state->bc, .de = de, .bc = state->bc};
    // CALL(aPlaceString);
    PlaceString_Conv(&temp, state->bc);

    // LD_H_B;
    // LD_L_C;
    uint8_t* hl = temp.bc;

    // LD_DE(mTextCommand_DAY_Day);
    // CALL(aPlaceString);
    struct TextPrintState temp2 = {.hl = hl, .de = Utf8ToCrystal(Day), .bc = temp.bc};
    PlaceString_Conv(&temp2, hl);
    // POP_HL;
    state->de = temp2.de;
    state->bc = temp2.bc;
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

//  print the day of the week
void TextCommand_DAY_Conv2(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)cmd;
    uint8_t buffer[8];
    static const char* Days[] = {
        "SUN@",
        "MON@",
        "TUES@",
        "WEDNES@",
        "THURS@",
        "FRI@",
        "SATUR@",
    };

    static const char* Day = "DAY@";

    // CALL(aGetWeekday);
    uint8_t wd = GetWeekday();

    // PUSH_HL;
    // PUSH_BC;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mTextCommand_DAY_Days);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // uint16_t hl = mTextCommand_DAY_Days + (2 * wd);

    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_D_H;
    // LD_E_L;
    // uint16_t de = gb_read16(hl);
    uint8_t* de = U82CA(buffer, Days[wd]);

    // POP_HL;
    struct TextPrintState temp = {.hl = state->bc, .de = de, .bc = state->bc};
    // CALL(aPlaceString);
    PlaceString_Conv(&temp, state->bc);

    // LD_H_B;
    // LD_L_C;
    uint8_t* hl = temp.bc;

    // LD_DE(mTextCommand_DAY_Day);
    // CALL(aPlaceString);
    struct TextPrintState temp2 = {.hl = hl, .de = U82CA(buffer, Day), .bc = temp.bc};
    PlaceString_Conv(&temp2, hl);
    // POP_HL;
    state->bc = temp2.bc;
    // RET;
}