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
}

const struct TextCmd* RadioTerminator(void) {
    static const txt_cmd_s stop[] = {
        text_end
    };
    return stop;
}

void PrintText_GB(uint8_t* hl) {
    // CALL(aSetUpTextbox);

    SetUpTextbox();
    // fallthrough

    return BuenaPrintText_GB(hl);
}

void PrintText(const struct TextCmd* hl) {
    // CALL(aSetUpTextbox);

    SetUpTextbox();
    // fallthrough

    return BuenaPrintText(hl);
}

void BuenaPrintText_GB(uint8_t* hl) {
    // PUSH_HL;
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    // CALL(aClearBox);
    ClearBox(wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY), TEXTBOX_INNERW, (TEXTBOX_INNERH - 1));
    // POP_HL;
    // fallthrough

    return PrintTextboxText_GB(hl);
}

void BuenaPrintText(const struct TextCmd* hl) {
    // PUSH_HL;
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    // CALL(aClearBox);
    ClearBox(wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY), TEXTBOX_INNERW, (TEXTBOX_INNERH - 1));
    // POP_HL;
    // fallthrough

    return PrintTextboxText(hl);
}

void PrintTextboxText_GB(uint8_t* hl) {
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // CALL(aPlaceHLTextAtBC);
    // RET;

    PlaceHLTextAtBC_GB(hl, wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY));
}

void PrintTextboxText(const struct TextCmd* hl) {
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // CALL(aPlaceHLTextAtBC);
    // RET;
    PlaceHLTextAtBC(coord(TEXTBOX_INNERX, TEXTBOX_INNERY, wram->wTilemap), hl);
}

void SetUpTextbox(void) {
    SpeechTextbox();
    UpdateSprites();
    ApplyTilemap();
}

bool PlaceString(struct TextPrintState* state, uint8_t* hl) {
    // fallthrough
    // PEEK("");
    state->hltemp = state->hl;
    state->hl = hl;
    bool res = PlaceNextChar(state);
    state->hl = state->hltemp;
    return res;
}

// Places string de at position hl.
void PlaceStringSimple(uint8_t* de, uint8_t* hl) {
    // fallthrough
    PlaceString(&(struct TextPrintState){.de = de, .hl = hl, .bc = 0, .hltemp = hl}, hl);
}

bool PlaceNextChar(struct TextPrintState* state) {
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
            case CHAR_MOBILE: MobileScriptChar(state); continue;
            case CHAR_LINE:   LineChar(state); continue;
            case CHAR_NEXT:   NextLineChar(state); continue;
            case CHAR_CR:     CarriageReturnChar(state); continue;
            case CHAR_NULL:   NullChar(state); continue;
            case CHAR_SCROLL: v_ContTextNoPause(state); continue;
            case CHAR__CONT:  v_ContText(state); continue;
            case CHAR_PARA:   Paragraph(state); continue;
            case CHAR_MOM:    PrintMomsName(state); continue;
            case CHAR_PLAYER: PrintPlayerName(state); continue;
            case CHAR_RIVAL:  PrintRivalName(state); continue;
            case CHAR_ROUTE:  PlaceJPRoute(state); continue;
            case CHAR_WATASHI:PlaceWatashi(state); continue;
            case CHAR_KOKO_WA:PlaceKokoWa(state); continue;
            case CHAR_RED:    PrintRedsName(state); continue;
            case CHAR_GREEN:  PrintGreensName(state); continue;
            case CHAR_POKe:   PlacePOKe(state); continue;
            case CHAR_PC:     PCChar(state); continue;
            case CHAR_ROCKET: RocketChar(state); continue;
            case CHAR_TM:     TMChar(state); continue;
            case CHAR_TRAINER:TrainerChar(state); continue;
            case CHAR_KOUGEKI:PlaceKougeki(state); continue;
            case CHAR_LF:     LineFeedChar(state); continue;
            case CHAR_CONT:   ContText(state); continue;
            case CHAR_SIXDOTS:SixDotsChar(state); continue;
            case CHAR_DONE:   return DoneText(state);
            case CHAR_PROMPT: return PromptText(state);
            case CHAR_PKMN:   PlacePKMN(state); continue;
            case CHAR_POKE:   PlacePOKE(state); continue;
            case 0xb:         NextChar(state); continue;
            case CHAR_SOFTLB: c = CHAR_SPACE; break;
            case CHAR_DEXEND: return PlaceDexEnd(state);
            case CHAR_TARGET: PlaceMoveTargetsName(state); continue;
            case CHAR_USER:   PlaceMoveUsersName(state); continue;
            case CHAR_ENEMY:  PlaceEnemysName(state); continue;
            case CHAR_PLAY_G: PlaceGenderedPlayerName(state); continue;
            case 0xe4:
            case 0xe5: {
            // diacritic:
                //
                // SET_PC(aCheckDict_diacritic);  //  unreferenced
                // LD_B_A;
                // CALL(aDiacritic);
                Diacritic();

                // JP(mNextChar);
                NextChar(state);
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
        PrintLetterDelay();
        NextChar(state);
        // CALL(aPrintLetterDelay);
        // JP(mNextChar);
    }
}

void NextChar(struct TextPrintState* state) {
    // INC_DE;
    state->de++;
    // JP(mPlaceNextChar);
}

void MobileScriptChar(struct TextPrintState* state) {
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

void PrintMomsName(struct TextPrintState* state) {
    // print_name wMomsName
    return PlaceCommandCharacter(state, wram->wMomsName);
}

void PrintPlayerName(struct TextPrintState* state) {
    // print_name wPlayerName
    return PlaceCommandCharacter(state, wram->wPlayerName);
}

void PrintRivalName(struct TextPrintState* state) {
    // print_name wRivalName
    return PlaceCommandCharacter(state, wram->wRivalName);
}

void PrintRedsName(struct TextPrintState* state) {
    // print_name wRedsName
    return PlaceCommandCharacter(state, wram->wRedsName);
}

void PrintGreensName(struct TextPrintState* state) {
    // print_name wGreensName
    return PlaceCommandCharacter(state, wram->wGreensName);
}

void TrainerChar(struct TextPrintState* state) {
    //  print_name TrainerCharText
    uint8_t buffer[8];
    PlaceCommandCharacter(state, U82CA(buffer, "TRAINER@"));
}

void TMChar(struct TextPrintState* state) {
    //  print_name TMCharText
    uint8_t buffer[8];
    PlaceCommandCharacter(state, U82CA(buffer, "TM@"));
}

void PCChar(struct TextPrintState* state) {
    //  print_name PCCharText
    uint8_t buffer[8];
    PlaceCommandCharacter(state, U82CA(buffer, "PC@"));
}

void RocketChar(struct TextPrintState* state) {
    //  print_name RocketCharText
    uint8_t buffer[16];
    PlaceCommandCharacter(state, U82CA(buffer, "ROCKET@")); // mRocketCharText
}

void PlacePOKe(struct TextPrintState* state) {
    //  print_name PlacePOKeText
    uint8_t buffer[16];
    PlaceCommandCharacter(state, U82CA(buffer, "POKé@")); // mPlacePOKeText
}

void PlaceKougeki(struct TextPrintState* state) {
    // print_name KougekiText
    PlaceCommandCharacter(state, Utf8ToCrystal("@")); // mKougekiText
}

void SixDotsChar(struct TextPrintState* state) {
    // print_name SixDotsCharText
    uint8_t buffer[8];
    PlaceCommandCharacter(state, U82CA(buffer, "……@")); // mSixDotsCharText
}

void PlacePKMN(struct TextPrintState* state) {
    // print_name PlacePKMNText
    uint8_t buffer[16];
    PlaceCommandCharacter(state, U82CA(buffer, "<PK><MN>@")); // mPlacePKMNText
}

void PlacePOKE(struct TextPrintState* state) {
    // print_name PlacePOKEText
    uint8_t buffer[16];
    PlaceCommandCharacter(state, U82CA(buffer, "<PO><KE>@")); // mPlacePOKEText
}

void PlaceJPRoute(struct TextPrintState* state) {
    // print_name PlaceJPRouteText
    PlaceCommandCharacter(state, Utf8ToCrystal("@")); // mPlaceJPRouteText
}

void PlaceWatashi(struct TextPrintState* state) {
    // print_name PlaceWatashiText
    PlaceCommandCharacter(state, Utf8ToCrystal("@")); // mPlaceWatashiText
}

void PlaceKokoWa(struct TextPrintState* state) {
    // print_name PlaceKokoWaText
    PlaceCommandCharacter(state, Utf8ToCrystal("@")); // mPlaceKokoWaText
}

void PlaceMoveTargetsName(struct TextPrintState* state) {
    // LDH_A_addr(hBattleTurn);
    // XOR_A(1);
    // JR(mPlaceBattlersName);
    return PlaceBattlersName(state, (hram.hBattleTurn ^ 1) != 0);
}

void PlaceMoveUsersName(struct TextPrintState* state) {
    // LDH_A_addr(hBattleTurn);
    // fallthrough
    return PlaceBattlersName(state, hram.hBattleTurn != TURN_PLAYER);
}

void PlaceBattlersName(struct TextPrintState* state, bool is_enemy) {
    uint8_t buffer[16];
    // PUSH_DE;
    // AND_A_A;
    // IF_NZ goto enemy;
    if(!is_enemy)
    {

        // LD_DE(wBattleMonNickname);
        // JR(mPlaceCommandCharacter);
        return PlaceCommandCharacter(state, wram->wBattleMonNickname);
    }

// enemy:
    // LD_DE(mEnemyText);
    // CALL(aPlaceString);
    struct TextPrintState temp = {.hl = state->hl, .de = U82CA(buffer, "Enemy @"), .bc = state->bc};
    PlaceString(&temp, state->hl);
    // LD_H_B;
    // LD_L_C;
    state->hl = temp.bc;
    // LD_DE(wEnemyMonNickname);
    // JR(mPlaceCommandCharacter);
    return PlaceCommandCharacter(state, wram->wEnemyMonNickname);
}

void PlaceEnemysName(struct TextPrintState* state) {
    uint8_t buffer[8];
    // PUSH_DE;

    // LD_A_addr(wLinkMode);
    // AND_A_A;
    // IF_NZ goto linkbattle;

    if(wram->wLinkMode != LINK_NULL) {
    // linkbattle:
        // LD_DE(wOTClassName);
        // JR(mPlaceCommandCharacter);
        return PlaceCommandCharacter(state, wram->wOTClassName);
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
        return PlaceCommandCharacter(state, wram->wRivalName);
    }

    // LD_DE(wOTClassName);
    // CALL(aPlaceString);
    struct TextPrintState temp = {.hl = state->hl, .de = wram->wOTClassName, .bc = state->bc};
    PlaceString(&temp, state->hl);
    // LD_H_B;
    // LD_L_C;
    state->bc = temp.bc;
    state->hl = state->bc;
    // LD_DE(mString_Space);
    // CALL(aPlaceString);
    temp.de = U82CA(buffer, " ");
    PlaceString(&temp, state->hl);
    // PUSH_BC;
    // CALLFAR(aBattle_GetTrainerName);
    uint8_t* s = Battle_GetTrainerName();
    // POP_HL;
    // LD_DE(wStringBuffer1);
    // JR(mPlaceCommandCharacter);
    state->hl = temp.bc;
    return PlaceCommandCharacter(state, s);
}

void PlaceGenderedPlayerName(struct TextPrintState* state) {
    uint8_t buffer[8];
    // PUSH_DE;
    // LD_DE(wPlayerName);
    // CALL(aPlaceString);
    struct TextPrintState temp = {.hl = state->hl, .de = wram->wPlayerName, .bc = state->bc};
    PlaceString(&temp, state->hl);
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
        return PlaceCommandCharacter(state, U82CA(buffer, "@")); // Chan suffix (empty string in English)
    }
    return PlaceCommandCharacter(state, U82CA(buffer, "@")); // Kun suffix (empty string in English)
}

void PlaceCommandCharacter(struct TextPrintState* state, uint8_t* de) {
    struct TextPrintState tempstate = {.hl = state->hl, .de = de, .bc = state->bc};
    // CALL(aPlaceString);
    PlaceString(&tempstate, state->hl);

    // LD_H_B;
    // LD_L_C;
    state->hl = tempstate.bc;
    state->bc = tempstate.bc;

    // POP_DE;
    // JP(mNextChar);
    NextChar(state);
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

void NextLineChar(struct TextPrintState* state) {
    // POP_HL;
    // LD_BC(SCREEN_WIDTH * 2);
    // ADD_HL_BC;
    // PUSH_HL;
    state->hltemp += (SCREEN_WIDTH * 2);
    state->hl = state->hltemp;
    // JP(mNextChar);
    NextChar(state);
}

void LineFeedChar(struct TextPrintState* state) {
    // POP_HL;
    // LD_BC(SCREEN_WIDTH);
    // ADD_HL_BC;
    // PUSH_HL;
    state->hltemp += (SCREEN_WIDTH);
    state->hl = state->hltemp;
    // JP(mNextChar);
    NextChar(state);
}

void CarriageReturnChar(struct TextPrintState* state) {
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

    NextChar(state);
}

void LineChar(struct TextPrintState* state) {
    // PEEK("");
    // POP_HL;
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    // PUSH_HL;
    state->hl = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
    state->hltemp = state->hl;
    
    // JP(mNextChar);
    NextChar(state);
}

void Paragraph(struct TextPrintState* state) {
    // PEEK("");
    // PUSH_DE;

    // LD_A_addr(wLinkMode);
    // CP_A(LINK_COLOSSEUM);
    // IF_Z goto linkbattle;
    // CP_A(LINK_MOBILE);
    // IF_Z goto linkbattle;
    // CALL(aLoadBlinkingCursor);
    if(wram->wLinkMode != LINK_COLOSSEUM && wram->wLinkMode != LINK_MOBILE)
        LoadBlinkingCursor();

// linkbattle:
    // CALL(aText_WaitBGMap);
    // CALL(aPromptButton);
    Text_WaitBGMap();
    PromptButton();
    
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    // LD_BC(((TEXTBOX_INNERH - 1) << 8) | TEXTBOX_INNERW);
    // CALL(aClearBox);
    ClearBox(wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY), TEXTBOX_INNERW, (TEXTBOX_INNERH - 1));
    
    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor();

    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames(20);
    
    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY, wTilemap);
    state->hl = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY);
    
    // POP_DE;
    // JP(mNextChar);
    NextChar(state);
}

void v_ContText(struct TextPrintState* state) {
    // PEEK("");
    // LD_A_addr(wLinkMode);
    // OR_A_A;
    // IF_NZ goto communication;
    // CALL(aLoadBlinkingCursor);
    if(wram->wLinkMode == LINK_NULL)
        LoadBlinkingCursor();

// communication:
    // CALL(aText_WaitBGMap);
    Text_WaitBGMap();

    // PUSH_DE;
    // CALL(aPromptButton);
    // POP_DE;
    PromptButton();

    // LD_A_addr(wLinkMode);
    // OR_A_A;
    // CALL_Z(aUnloadBlinkingCursor);
    if(wram->wLinkMode == LINK_NULL)
        UnloadBlinkingCursor();
    // fallthrough

    return v_ContTextNoPause(state);
}

void v_ContTextNoPause(struct TextPrintState* state) {
    // PEEK("");
    // PUSH_DE;
    uint8_t* de = state->de;

    // CALL(aTextScroll);
    // CALL(aTextScroll);
    TextScroll(state);
    TextScroll(state);

    // hlcoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->hl = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
    // POP_DE;
    state->de = de;
    
    // JP(mNextChar);
    NextChar(state);
}

void ContText(struct TextPrintState* state) {
    uint8_t buf[4];
    // PUSH_DE;
    uint8_t* de = state->de;
    // LD_DE(mContText_cont);
    state->de = U82CA(buf, "<_CONT>@");

    // LD_B_H;
    // LD_C_L;
    state->bc = state->hl;
    // CALL(aPlaceString);
    PlaceString(state, state->hl);
    // LD_H_B;
    // LD_L_C;
    state->hl = state->bc;
    // POP_DE;
    state->de = de;
    // JP(mNextChar);

    NextChar(state);
}

//  Ends a Pokédex entry in Gen 1.
//  Dex entries are now regular strings.
bool PlaceDexEnd(struct TextPrintState* state) {
    // LD_hl(0xe8);
    *(state->hl) = 0xe8;
    // POP_HL;
    // RET;
    return false;
}

bool PromptText(struct TextPrintState* state) {
    // LD_A_addr(wLinkMode);
    // CP_A(LINK_COLOSSEUM);
    // IF_Z goto ok;
    // CP_A(LINK_MOBILE);
    // IF_Z goto ok;
    // CALL(aLoadBlinkingCursor);
    uint8_t linkMode = gb_read(wLinkMode);
    if(linkMode != LINK_COLOSSEUM && linkMode != LINK_MOBILE)
        LoadBlinkingCursor();

// ok:
    // CALL(aText_WaitBGMap);
    // CALL(aPromptButton);
    Text_WaitBGMap();
    PromptButton();

    // LD_A_addr(wLinkMode);
    // CP_A(LINK_COLOSSEUM);
    // JR_Z(mDoneText);
    // CP_A(LINK_MOBILE);
    // JR_Z(mDoneText);
    // CALL(aUnloadBlinkingCursor);
    linkMode = gb_read(wLinkMode);
    if(linkMode != LINK_COLOSSEUM && linkMode != LINK_MOBILE)
        UnloadBlinkingCursor();

    return DoneText(state);
}

bool DoneText(struct TextPrintState* state) {
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

void NullChar(struct TextPrintState* state) {
    // LD_A(0xe6);
    // LD_hli_A;
    *(state->hl++) = CHAR_QMARK;

    // CALL(aPrintLetterDelay);
    PrintLetterDelay();
    // JP(mNextChar);
    NextChar(state);
}

void TextScroll(struct TextPrintState* state) {
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
    uint8_t temp = hram.hOAMUpdate;

    // LD_A(1);
    // LDH_addr_A(hOAMUpdate);
    hram.hOAMUpdate = 1;

    // CALL(aWaitBGMap);
    WaitBGMap();

    // POP_AF;
    // LDH_addr_A(hOAMUpdate);
    hram.hOAMUpdate = temp;

    // POP_BC;
    // RET;
}

// Lol, does nothing.
void Diacritic(void) {
    // RET;
}

void LoadBlinkingCursor(void) {
    // LD_A(0xee);
    // ldcoord_a(18, 17, wTilemap);
    // gb_write(coord(18, 17, wTilemap), CHAR_DOWN_CURSOR);
    wram->wTilemap[coordidx(18, 17)] = CHAR_DOWN_CURSOR;

    // RET;
}

void UnloadBlinkingCursor(void) {
    // PEEK("");
    // lda_coord(17, 17, wTilemap);
    // ldcoord_a(18, 17, wTilemap);
    // gb_write(coord(18, 17, wTilemap), gb_read(coord(17, 17, wTilemap)));
    wram->wTilemap[coordidx(18, 17)] = wram->wTilemap[coordidx(17, 17)];
    
    // RET;
}

void PlaceFarString(uint8_t bank, struct TextPrintState* state, uint8_t* hl) {
    // LD_B_A;
    // LDH_A_addr(hROMBank);
    // PUSH_AF;

    // LD_A_B;
    // RST(aBankswitch);

    bank_push(bank);


    // CALL(aPlaceString);
    PlaceString(state, hl);

    // POP_AF;
    // RST(aBankswitch);
    // RET;
    bank_pop;
}

// void PokeFluteTerminator(void) {
//     LD_HL(mPokeFluteTerminator_stop);
//     RET;

// stop:
//     // text_end ['?']

//     return PlaceHLTextAtBC();
// }

void PlaceHLTextAtBC_GB(uint8_t* hl, uint8_t* bc) {
    uint8_t tflags = gOptions.textboxFlags;
    gOptions.textboxFlags = tflags | (1 << NO_TEXT_DELAY_F);

    struct TextPrintState state = {.hl = hl, .bc = bc, .de = 0};

    uint8_t cmd;
    while(1)
    {
        cmd = *(state.hl++);
        if(cmd == TX_END)
            break;
        // CALL(aDoTextUntilTerminator_TextCommand);
        DoTextUntilTerminator_TextCommand_GB(&state, cmd);
    }

    gOptions.textboxFlags = tflags;
}

void PlaceHLTextAtBC(uint8_t* bc, const struct TextCmd* hl) {
    uint8_t tflags = gOptions.textboxFlags;
    gOptions.textboxFlags = tflags | (1 << NO_TEXT_DELAY_F);

    struct TextCmdState state = {.hl = hl, .bc = bc};

    const struct TextCmd* cmd;
    while(1)
    {
        cmd = state.hl++;
        if(cmd->cmd == TX_END)
            break;
        // CALL(aDoTextUntilTerminator_TextCommand);
        DoTextUntilTerminator_TextCommand(&state, cmd);
    }

    gOptions.textboxFlags = tflags;
}

void (*const TextCommands[])(struct TextPrintState*) = {
    [TX_START] = TextCommand_START_GB,
    [TX_RAM] = TextCommand_RAM_GB,
    [TX_BCD] = TextCommand_BCD_GB,
    [TX_MOVE] = TextCommand_MOVE_GB,
    [TX_BOX] = TextCommand_BOX_GB,
    [TX_LOW] = TextCommand_LOW_GB,
    [TX_PROMPT_BUTTON] = TextCommand_PROMPT_BUTTON_GB,
    [TX_SCROLL] = TextCommand_SCROLL_GB,
    [TX_START_ASM] = TextCommand_START_ASM_GB,
    [TX_DECIMAL] = TextCommand_DECIMAL_GB,
    [TX_PAUSE] = TextCommand_PAUSE_GB,
    [TX_SOUND_DEX_FANFARE_50_79] = TextCommand_SOUND_GB,
    [TX_DOTS] = TextCommand_DOTS_GB,
    [TX_WAIT_BUTTON] = TextCommand_WAIT_BUTTON_GB,
    [TX_SOUND_DEX_FANFARE_20_49] = TextCommand_SOUND_GB,
    [TX_SOUND_ITEM] = TextCommand_SOUND_GB,
    [TX_SOUND_CAUGHT_MON] = TextCommand_SOUND_GB,
    [TX_SOUND_DEX_FANFARE_80_109] = TextCommand_SOUND_GB,
    [TX_SOUND_FANFARE] = TextCommand_SOUND_GB,
    [TX_SOUND_SLOT_MACHINE_START] = TextCommand_SOUND_GB,
    [TX_STRINGBUFFER] = TextCommand_STRINGBUFFER_GB,
    [TX_DAY] = TextCommand_DAY_GB,
    [TX_FAR] = TextCommand_FAR_GB
};

void (*const TextCommands2[])(struct TextCmdState*, const struct TextCmd*) = {
    [TX_START] = TextCommand_START,
    [TX_RAM] = TextCommand_RAM,
    [TX_BCD] = TextCommand_BCD,
    [TX_MOVE] = TextCommand_MOVE,
    [TX_BOX] = TextCommand_BOX,
    [TX_LOW] = TextCommand_LOW,
    [TX_PROMPT_BUTTON] = TextCommand_PROMPT_BUTTON,
    [TX_SCROLL] = TextCommand_SCROLL,
    [TX_START_ASM] = TextCommand_START_ASM,
    [TX_DECIMAL] = TextCommand_DECIMAL,
    [TX_PAUSE] = TextCommand_PAUSE,
    [TX_SOUND_DEX_FANFARE_50_79] = TextCommand_SOUND,
    [TX_DOTS] = TextCommand_DOTS,
    [TX_WAIT_BUTTON] = TextCommand_WAIT_BUTTON,
    [TX_SOUND_DEX_FANFARE_20_49] = TextCommand_SOUND,
    [TX_SOUND_ITEM] = TextCommand_SOUND,
    [TX_SOUND_CAUGHT_MON] = TextCommand_SOUND,
    [TX_SOUND_DEX_FANFARE_80_109] = TextCommand_SOUND,
    [TX_SOUND_FANFARE] = TextCommand_SOUND,
    [TX_SOUND_SLOT_MACHINE_START] = TextCommand_SOUND,
    [TX_STRINGBUFFER] = TextCommand_STRINGBUFFER,
    [TX_DAY] = TextCommand_DAY,
    [TX_FAR] = TextCommand_FAR
};

static_assert(lengthof(TextCommands) == NUM_TEXT_CMDS, "");

void DoTextUntilTerminator_GB(struct TextPrintState* state) {
    while(1)
    {
        // LD_A_hli;
        uint8_t cmd = *(state->hl++);

        // CP_A(TX_END);
        // RET_Z;
        if(cmd == TX_END)
            return;
        
        // CALL(aDoTextUntilTerminator_TextCommand);
        // DoTextUntilTerminator_TextCommand_GB(state, cmd);
        TextCommands[cmd](state);

        // JR(mDoTextUntilTerminator);
    }
}

void DoTextUntilTerminator(struct TextCmdState* state) {
    while(1)
    {
        // LD_A_hli;
        const struct TextCmd* cmd = state->hl++;

        // CP_A(TX_END);
        // RET_Z;
        if(cmd->cmd == TX_END)
            return;
        
        // CALL(aDoTextUntilTerminator_TextCommand);
        // DoTextUntilTerminator_TextCommand_GB(state, cmd);
        TextCommands2[cmd->cmd](state, cmd);

        // JR(mDoTextUntilTerminator);
    }
}

void DoTextUntilTerminator_TextCommand_GB(struct TextPrintState* state, uint8_t cmd) {
    TextCommands[cmd](state);
}

void DoTextUntilTerminator_TextCommand(struct TextCmdState* state, const struct TextCmd* cmd) {
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

//  write text until "@"
void TextCommand_START_GB(struct TextPrintState* state) {
    // PEEK("");
    // LD_D_H;
    // LD_E_L;
    state->de = state->hl;
    // LD_H_B;
    // LD_L_C;
    state->hl = state->bc;
    // CALL(aPlaceString);
    printf("text $%04x\n", RAMAddrToGB(state->de));
    PlaceString(state, state->bc);
    // struct TextPrintState tempstate = {.hl = state->bc, .de = state->hl};

    // LD_H_D;
    // LD_L_E;
    state->hl = state->de;
    // INC_HL;
    state->hl++;
    // RET;
}

//  write text until "@"
void TextCommand_START(struct TextCmdState* state, const struct TextCmd* cmd) {
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
    if(!PlaceString(&temp, state->bc)) {
        state->hl = &cmd_end;
    }
    // struct TextPrintState tempstate = {.hl = state->bc, .de = state->hl};

    state->bc = temp.bc;
    // LD_H_D;
    // LD_L_E;
    // INC_HL;
    // RET;
}

void TextCommand_RAM_GB(struct TextPrintState* state) {
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
    PlaceString(&temp, state->bc);
    // POP_HL;
    state->de = temp.de;
    state->bc = temp.bc;
    // RET;
}

void TextCommand_RAM(struct TextCmdState* state, const struct TextCmd* cmd) {
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
    PlaceString(&temp, state->bc);
    // POP_HL;
    state->bc = temp.bc;
    // RET;
}

//  write text from a different bank (little endian)
void TextCommand_FAR_GB(struct TextPrintState* state) {
    // PEEK("");
    // LDH_A_addr(hROMBank);
    // PUSH_AF;
    uint8_t oldBank = hram.hROMBank;

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
    hram.hROMBank = newBank;
    // LD_addr_A(MBC3RomBank);
    gb_write(MBC3RomBank, newBank);

    state->de = GBToRAMAddr(de_v);

    // PUSH_HL;
    uint8_t* hltemp = state->hl;

    // LD_H_D;
    // LD_L_E;
    state->hl = state->de;

    // CALL(aDoTextUntilTerminator);
    DoTextUntilTerminator_GB(state);

    // POP_HL;
    state->hl = hltemp;

    // POP_AF;
    // LDH_addr_A(hROMBank);
    // LD_addr_A(MBC3RomBank);
    hram.hROMBank = oldBank;
    gb_write(MBC3RomBank, oldBank);

    // RET;
}

//  write text from a different text command ptr (little endian)
void TextCommand_FAR(struct TextCmdState* state, const struct TextCmd* cmd) {
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
    DoTextUntilTerminator(&temp);

    // POP_HL;
    state->bc = temp.bc;

    // POP_AF;
    // LDH_addr_A(hROMBank);
    // LD_addr_A(MBC3RomBank);

    // RET;
}

//  write bcd from address, typically ram
void TextCommand_BCD_GB(struct TextPrintState* state) {
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
    state->bc = PrintBCDNumber(state->bc, state->de, c);
    state->de += c & 0x1f;
    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // RET;
}

//  write bcd from address, typically ram
void TextCommand_BCD(struct TextCmdState* state, const struct TextCmd* cmd) {
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
    state->bc = PrintBCDNumber(state->bc, cmd->bcd_addr, cmd->bcd_flags);
    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // RET;
}

//  move to a new tile
void TextCommand_MOVE_GB(struct TextPrintState* state) {
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
void TextCommand_MOVE(struct TextCmdState* state, const struct TextCmd* cmd) {
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

//  draw a box (height, width)
void TextCommand_BOX_GB(struct TextPrintState* state) {
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
void TextCommand_BOX(struct TextCmdState* state, const struct TextCmd* cmd) {
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

//  write text at (1,16)
void TextCommand_LOW_GB(struct TextPrintState* state) {
    PEEK("");
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->bc = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
    // RET;
}

//  write text at (1,16)
void TextCommand_LOW(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)cmd;
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->bc = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
    // RET;
}

//  wait for button press
void TextCommand_PROMPT_BUTTON_GB(struct TextPrintState* state) {
    PEEK("");
    (void)state;
    // LD_A_addr(wLinkMode);
    uint8_t linkMode = gb_read(wLinkMode);

    // CP_A(LINK_COLOSSEUM);
    // JP_Z(mTextCommand_WAIT_BUTTON);
    // CP_A(LINK_MOBILE);
    // JP_Z(mTextCommand_WAIT_BUTTON);
    if(linkMode == LINK_COLOSSEUM || linkMode == LINK_MOBILE)
        return TextCommand_WAIT_BUTTON_GB(state);

    // PUSH_HL;
    // uint16_t hltemp = state->hl;
    // CALL(aLoadBlinkingCursor);
    LoadBlinkingCursor();

    // PUSH_BC;
    // CALL(aPromptButton);
    // POP_BC;
    PromptButton();

    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor();
    // POP_HL;
    // RET;
}

//  wait for button press
void TextCommand_PROMPT_BUTTON(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)state, (void)cmd;
    // LD_A_addr(wLinkMode);
    uint8_t linkMode = wram->wLinkMode;

    // CP_A(LINK_COLOSSEUM);
    // JP_Z(mTextCommand_WAIT_BUTTON);
    // CP_A(LINK_MOBILE);
    // JP_Z(mTextCommand_WAIT_BUTTON);
    if(linkMode == LINK_COLOSSEUM || linkMode == LINK_MOBILE)
        return TextCommand_WAIT_BUTTON(state, cmd);

    // PUSH_HL;
    // uint16_t hltemp = state->hl;
    // CALL(aLoadBlinkingCursor);
    LoadBlinkingCursor();

    // PUSH_BC;
    // CALL(aPromptButton);
    // POP_BC;
    PromptButton();

    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor();
    // POP_HL;
    // RET;
}

//  pushes text up two lines and sets the BC cursor to the border tile
//  below the first character column of the text box.
void TextCommand_SCROLL_GB(struct TextPrintState* state) {
    PEEK("");
    // PUSH_HL;
    uint8_t* hltemp = state->hl;
    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor();
    // CALL(aTextScroll);
    // CALL(aTextScroll);
    TextScroll(state);
    TextScroll(state);
    // POP_HL;
    state->hl = hltemp;
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->bc = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
    // RET;
}

//  pushes text up two lines and sets the BC cursor to the border tile
//  below the first character column of the text box.
void TextCommand_SCROLL(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)cmd;
    // PUSH_HL;
    // CALL(aUnloadBlinkingCursor);
    UnloadBlinkingCursor();
    // CALL(aTextScroll);
    // CALL(aTextScroll);
    struct TextPrintState temp = {.hl = state->bc, .bc = state->bc, .hltemp = state->bc};
    TextScroll(&temp);
    TextScroll(&temp);
    // POP_HL;
    // bccoord(TEXTBOX_INNERX, TEXTBOX_INNERY + 2, wTilemap);
    state->bc = wram->wTilemap + coordidx(TEXTBOX_INNERX, TEXTBOX_INNERY + 2);
    // RET;
}

//  run assembly code
void TextCommand_START_ASM_GB(struct TextPrintState* state) {
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
void TextCommand_START_ASM(struct TextCmdState* state, const struct TextCmd* cmd) {
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

//  print a decimal number
void TextCommand_DECIMAL_GB(struct TextPrintState* state) {
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
    state->bc = PrintNum(state->bc, state->de, b, c);

    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // RET;
}

//  print a decimal number
void TextCommand_DECIMAL(struct TextCmdState* state, const struct TextCmd* cmd) {
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
    state->bc = PrintNum(state->bc, de, b, c);

    // LD_B_H;
    // LD_C_L;
    // POP_HL;
    // RET;
}

//  wait for button press or 30 frames
void TextCommand_PAUSE_GB(struct TextPrintState* state) {
    PEEK("");
    (void)state;
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aGetJoypad);
    GetJoypad();

    // LDH_A_addr(hJoyDown);
    // AND_A(A_BUTTON | B_BUTTON);
    // IF_NZ goto done;
    if(((hram.hJoyDown) & (A_BUTTON | B_BUTTON)) == 0)
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
void TextCommand_PAUSE(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)state, (void)cmd;
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aGetJoypad);
    GetJoypad();

    // LDH_A_addr(hJoyDown);
    // AND_A(A_BUTTON | B_BUTTON);
    // IF_NZ goto done;
    if(((hram.hJoyDown) & (A_BUTTON | B_BUTTON)) == 0)
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
void TextCommand_SOUND_GB(struct TextPrintState* state) {
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
void TextCommand_SOUND(struct TextCmdState* state, const struct TextCmd* cmd) {
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

void TextCommand_CRY_GB(struct TextPrintState* state) {
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

void TextCommand_CRY(struct TextCmdState* state, const struct TextCmd* cmd) {
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

//  wait for button press or 30 frames while printing "…"s
void TextCommand_DOTS_GB(struct TextPrintState* state) {
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
        GetJoypad();

        // LDH_A_addr(hJoyDown);
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto next;
        if(((hram.hJoyDown) & (A_BUTTON | B_BUTTON)) == 0)
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
void TextCommand_DOTS(struct TextCmdState* state, const struct TextCmd* cmd) {
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
        GetJoypad();

        // LDH_A_addr(hJoyDown);
        // AND_A(A_BUTTON | B_BUTTON);
        // IF_NZ goto next;
        if(((hram.hJoyDown) & (A_BUTTON | B_BUTTON)) == 0)
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

//  wait for button press
void TextCommand_WAIT_BUTTON_GB(struct TextPrintState* state) {
    PEEK("");
    (void)state;
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aPromptButton);
    // POP_BC;
    // POP_HL;
    // RET;
    PromptButton();
}

//  wait for button press
void TextCommand_WAIT_BUTTON(struct TextCmdState* state, const struct TextCmd* cmd) {
    (void)state, (void)cmd;
    // PUSH_HL;
    // PUSH_BC;
    // CALL(aPromptButton);
    // POP_BC;
    // POP_HL;
    // RET;
    PromptButton();
}

//  Print a string from one of the following:
//  0: wStringBuffer3
//  1: wStringBuffer4
//  2: wStringBuffer5
//  3: wStringBuffer2
//  4: wStringBuffer1
//  5: wEnemyMonNickname
//  6: wBattleMonNickname
void TextCommand_STRINGBUFFER_GB(struct TextPrintState* state) {
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
    PlaceString(&temp, state->bc);

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
void TextCommand_STRINGBUFFER(struct TextCmdState* state, const struct TextCmd* cmd) {
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
    PlaceString(&temp, state->bc);

    state->bc = temp.bc;
    // POP_HL;
    // RET;
}

//  print the day of the week
void TextCommand_DAY_GB(struct TextPrintState* state) {
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
    PlaceString(&temp, state->bc);

    // LD_H_B;
    // LD_L_C;
    uint8_t* hl = temp.bc;

    // LD_DE(mTextCommand_DAY_Day);
    // CALL(aPlaceString);
    struct TextPrintState temp2 = {.hl = hl, .de = Utf8ToCrystal(Day), .bc = temp.bc};
    PlaceString(&temp2, hl);
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
void TextCommand_DAY(struct TextCmdState* state, const struct TextCmd* cmd) {
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
    PlaceString(&temp, state->bc);

    // LD_H_B;
    // LD_L_C;
    uint8_t* hl = temp.bc;

    // LD_DE(mTextCommand_DAY_Day);
    // CALL(aPlaceString);
    struct TextPrintState temp2 = {.hl = hl, .de = U82CA(buffer, Day), .bc = temp.bc};
    PlaceString(&temp2, hl);
    // POP_HL;
    state->bc = temp2.bc;
    // RET;
}