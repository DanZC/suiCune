#include "../../constants.h"
#include "timeset.h"
#include "print_hours_mins.h"
#include "../../home/delay.h"
#include "../../home/fade.h"
#include "../../home/text.h"
#include "../../home/clear_sprites.h"
#include "../../home/copy.h"
#include "../../home/tilemap.h"
#include "../../home/joypad.h"
#include "../../home/menu.h"
#include "../../home/print_text.h"
#include "../../home/gfx.h"
#include "../../home/time.h"
#include "../../home/map_objects.h"
#include "../../charmap.h"
#include "../../data/text/common.h"

#define TIMESET_UP_ARROW (CHAR_MALE_ICON)  //  $ef
#define TIMESET_DOWN_ARROW (CHAR_FEMALE_ICON)  //  $f5

#define TILE_TIMESET_UP     0x01
#define TILE_TIMESET_DOWN   0x02

static const char TimeSetBackgroundGFX[] = "gfx/new_game/timeset_bg.png";
static const char TimeSetUpArrowGFX[] = "gfx/new_game/up_arrow.png";
static const char TimeSetDownArrowGFX[] = "gfx/new_game/down_arrow.png";

static const char String_oclock[] = "o\'clock@";
static const char String_min[] = "min.@";

static void InitClock_ClearScreen(void) {
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(SCREEN_HEIGHT * SCREEN_WIDTH);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(coord(0, 0, wram->wTilemap), SCREEN_HEIGHT * SCREEN_WIDTH, 0);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0x1;
    // RET;
}

//  Ask the player to set the time.
void InitClock(void){
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;

    // LD_A(0x0);
    // LD_addr_A(wSpriteUpdatesEnabled);
    wram->wSpriteUpdatesEnabled = 0x0;
    // LD_A(0x10);
    // LD_addr_A(wMusicFade);
    wram->wMusicFade = 0x10;
    // LD_A(LOW(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID);
    // LD_A(HIGH(MUSIC_NONE));
    // LD_addr_A(wMusicFadeID + 1);
    wram->wMusicFadeID = MUSIC_NONE;
    // LD_C(8);
    // CALL(aDelayFrames);
    DelayFrames_Conv(8);
    // CALL(aRotateFourPalettesLeft);
    RotateFourPalettesLeft_Conv();
    // CALL(aClearTilemap);
    ClearTilemap_Conv2();
    // CALL(aClearSprites);
    ClearSprites_Conv();
    // LD_B(SCGB_DIPLOMA);
    // CALL(aGetSGBLayout);
    GetSGBLayout_Conv(SCGB_DIPLOMA);
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // LD_DE(mTimeSetBackgroundGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x00);
    // LD_BC((BANK(aTimeSetBackgroundGFX) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * 0x00, TimeSetBackgroundGFX, 0, 1);
    // LD_DE(mTimeSetUpArrowGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x01);
    // LD_BC((BANK(aTimeSetUpArrowGFX) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * TILE_TIMESET_UP, TimeSetUpArrowGFX, 0, 1);
    // LD_DE(mTimeSetDownArrowGFX);
    // LD_HL(vTiles2 + LEN_2BPP_TILE * 0x02);
    // LD_BC((BANK(aTimeSetDownArrowGFX) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles2 + LEN_2BPP_TILE * TILE_TIMESET_DOWN, TimeSetDownArrowGFX, 0, 1);
    // CALL(aInitClock_ClearScreen);
    InitClock_ClearScreen();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aRotateFourPalettesRight);
    RotateFourPalettesRight_Conv();
    // LD_HL(mOakTimeWokeUpText);
    // CALL(aPrintText);
    PrintText_Conv2(OakTimeWokeUpText);
    // LD_HL(wTimeSetBuffer);
    // LD_BC(wTimeSetBufferEnd - wTimeSetBuffer);
    // XOR_A_A;
    // CALL(aByteFill);
    ByteFill_Conv2(wram->wTimeSetBuffer, sizeof(wram->wTimeSetBuffer), 0);
    // LD_A(10);  // default hour = 10 AM
    // LD_addr_A(wInitHourBuffer);
    wram->wInitHourBuffer = hram->hRTCHours;

    while(1) {
    // loop:
        // LD_HL(mOakTimeWhatTimeIsItText);
        // CALL(aPrintText);
        PrintText_Conv2(OakTimeWhatTimeIsItText);
        // hlcoord(3, 7, wTilemap);
        // LD_B(2);
        // LD_C(15);
        // CALL(aTextbox);
        Textbox_Conv2(coord(3, 7, wram->wTilemap), 2, 15);
        // hlcoord(11, 7, wTilemap);
        // LD_hl(0x1);
        *coord(11, 7, wram->wTilemap) = TILE_TIMESET_UP;
        // hlcoord(11, 10, wTilemap);
        // LD_hl(0x2);
        *coord(11, 10, wram->wTilemap) = TILE_TIMESET_DOWN;
        // hlcoord(4, 9, wTilemap);
        // CALL(aDisplayHourOClock);
        DisplayHourOClock_Conv(coord(4, 9, wram->wTilemap));
        // LD_C(10);
        // CALL(aDelayFrames);
        DelayFrames_Conv(10);

        do {
        // SetHourLoop:
            // CALL(aJoyTextDelay);
            JoyTextDelay_Conv();
            // CALL(aSetHour);
            // IF_NC goto SetHourLoop;
        } while(!SetHour_Conv());

        // LD_A_addr(wInitHourBuffer);
        // LD_addr_A(wStringBuffer2 + 1);
        // CALL(aInitClock_ClearScreen);
        InitClock_ClearScreen();
        // LD_HL(mOakTimeWhatHoursText);
        // CALL(aPrintText);
        PrintText_Conv2(OakTimeWhatHoursText);
        // CALL(aYesNoBox);
        // IF_NC goto HourIsSet;
        if(YesNoBox_Conv())
            break;
        // CALL(aInitClock_ClearScreen);
        InitClock_ClearScreen();
        // goto loop;
    }

    wram->wInitMinuteBuffer = hram->hRTCMinutes;

    while(1) {
    // HourIsSet:
        // LD_HL(mOakTimeHowManyMinutesText);
        // CALL(aPrintText);
        PrintText_Conv2(OakTimeHowManyMinutesText);
        // hlcoord(11, 7, wTilemap);
        // LD_BC((2 << 8) | 7);
        // CALL(aTextbox);
        Textbox_Conv2(coord(11, 7, wram->wTilemap), 2, 7);
        // hlcoord(15, 7, wTilemap);
        // LD_hl(0x1);
        *coord(15, 7, wram->wTilemap) = TILE_TIMESET_UP;
        // hlcoord(15, 10, wTilemap);
        // LD_hl(0x2);
        *coord(15, 10, wram->wTilemap) = TILE_TIMESET_DOWN;
        // hlcoord(12, 9, wTilemap);
        // CALL(aDisplayMinutesWithMinString);
        DisplayMinutesWithMinString_Conv(coord(12, 9, wram->wTilemap));
        // LD_C(10);
        // CALL(aDelayFrames);
        DelayFrames_Conv(10);

        do {
        // SetMinutesLoop:
            // CALL(aJoyTextDelay);
            JoyTextDelay_Conv();
            // CALL(aSetMinutes);
            // IF_NC goto SetMinutesLoop;
        } while(!SetMinutes_Conv());

        // LD_A_addr(wInitMinuteBuffer);
        // LD_addr_A(wStringBuffer2 + 2);
        // CALL(aInitClock_ClearScreen);
        InitClock_ClearScreen();
        // LD_HL(mOakTimeWhoaMinutesText);
        // CALL(aPrintText);
        PrintText_Conv2(OakTimeWhoaMinutesText);
        // CALL(aYesNoBox);
        // IF_NC goto MinutesAreSet;
        if(YesNoBox_Conv())
            break;
        // CALL(aInitClock_ClearScreen);
        InitClock_ClearScreen();
        // goto HourIsSet;
    }


// MinutesAreSet:
    // CALL(aInitTimeOfDay);
    InitTimeOfDay_Conv(wram->wInitHourBuffer, wram->wInitMinuteBuffer);
    // LD_HL(mOakText_ResponseToSetTime);
    // CALL(aPrintText);
    PrintText_Conv2(OakText_ResponseToSetTime);
    // CALL(aWaitPressAorB_BlinkCursor);
    WaitPressAorB_BlinkCursor_Conv();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    RET;
}

void SetHour(void){
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON);
    IF_NZ goto Confirm;

    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto up;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto down;
    CALL(aDelayFrame);
    AND_A_A;
    RET;


down:
    LD_HL(wInitHourBuffer);
    LD_A_hl;
    AND_A_A;
    IF_NZ goto DecreaseThroughMidnight;
    LD_A(23 + 1);

DecreaseThroughMidnight:
    DEC_A;
    LD_hl_A;
    goto okay;


up:
    LD_HL(wInitHourBuffer);
    LD_A_hl;
    CP_A(23);
    IF_C goto AdvanceThroughMidnight;
    LD_A(-1);

AdvanceThroughMidnight:
    INC_A;
    LD_hl_A;


okay:
    hlcoord(4, 9, wTilemap);
    LD_A(0x7f);
    LD_BC(15);
    CALL(aByteFill);
    hlcoord(4, 9, wTilemap);
    CALL(aDisplayHourOClock);
    CALL(aWaitBGMap);
    AND_A_A;
    RET;


Confirm:
    SCF;
    RET;

}

bool SetHour_Conv(void){
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON);
    // IF_NZ goto Confirm;
    if(hram->hJoyPressed & A_BUTTON)
        return true;

    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto up;
    if(hram->hJoyLast & D_UP) {
    // up:
        // LD_HL(wInitHourBuffer);
        // LD_A_hl;
        // CP_A(23);
        // IF_C goto AdvanceThroughMidnight;
        if(wram->wInitHourBuffer >= 23) {
            // LD_A(-1);
            wram->wInitHourBuffer = 0;
        }
        else {
        // AdvanceThroughMidnight:
            // INC_A;
            // LD_hl_A;
            wram->wInitHourBuffer++;
        }
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto down;
    else if(hram->hJoyLast & D_DOWN) {
    // down:
        // LD_HL(wInitHourBuffer);
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto DecreaseThroughMidnight;
        if(wram->wInitHourBuffer == 0) {
            // LD_A(23 + 1);
            wram->wInitHourBuffer = 23;
        }
        else {
        // DecreaseThroughMidnight:
            // DEC_A;
            // LD_hl_A;
            // goto okay;
            wram->wInitHourBuffer--;
        }
    }
    else {
        // CALL(aDelayFrame);
        DelayFrame();
        // AND_A_A;
        // RET;
        return false;
    }


// okay:
    // hlcoord(4, 9, wTilemap);
    // LD_A(0x7f);
    // LD_BC(15);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(4, 9, wram->wTilemap), 15, 0x7f);
    // hlcoord(4, 9, wTilemap);
    // CALL(aDisplayHourOClock);
    DisplayHourOClock_Conv(coord(4, 9, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // AND_A_A;
    // RET;
    return false;

// Confirm:
    // SCF;
    // RET;
}

void DisplayHourOClock(void){
    PUSH_HL;
    LD_A_addr(wInitHourBuffer);
    LD_C_A;
    LD_E_L;
    LD_D_H;
    CALL(aPrintHour);
    INC_HL;
    LD_DE(mString_oclock);
    CALL(aPlaceString);
    POP_HL;
    RET;

}

uint8_t* DisplayHourOClock_Conv(uint8_t* hl){
    // PUSH_HL;
    // LD_A_addr(wInitHourBuffer);
    // LD_C_A;
    // LD_E_L;
    // LD_D_H;
    // CALL(aPrintHour);
    hl = PrintHour_Conv(hl, wram->wInitHourBuffer);
    // INC_HL;
    // LD_DE(mString_oclock);
    // CALL(aPlaceString);
    struct TextPrintState st = {.de = U82C(String_oclock), .hl = hl + 1};
    PlaceString_Conv(&st, st.hl);
    // POP_HL;
    // RET;
    return st.bc;
}

void DisplayHoursMinutesWithMinString(void){
//  //  unreferenced
    LD_H_D;
    LD_L_E;
    PUSH_HL;
    CALL(aDisplayHourOClock);
    POP_DE;
    INC_DE;
    INC_DE;
    LD_A(0x9c);
    LD_de_A;
    INC_DE;
    PUSH_DE;
    LD_HL(3);
    ADD_HL_DE;
    LD_A_de;
    INC_DE;
    LD_hli_A;
    LD_A_de;
    LD_hl_A;
    POP_HL;
    CALL(aDisplayMinutesWithMinString);
    INC_HL;
    INC_HL;
    INC_HL;
    RET;

}

void SetMinutes(void){
    LDH_A_addr(hJoyPressed);
    AND_A(A_BUTTON);
    IF_NZ goto a_button;
    LD_HL(hJoyLast);
    LD_A_hl;
    AND_A(D_UP);
    IF_NZ goto d_up;
    LD_A_hl;
    AND_A(D_DOWN);
    IF_NZ goto d_down;
    CALL(aDelayFrame);
    AND_A_A;
    RET;


d_down:
    LD_HL(wInitMinuteBuffer);
    LD_A_hl;
    AND_A_A;
    IF_NZ goto decrease;
    LD_A(59 + 1);

decrease:
    DEC_A;
    LD_hl_A;
    goto finish_dpad;


d_up:
    LD_HL(wInitMinuteBuffer);
    LD_A_hl;
    CP_A(59);
    IF_C goto increase;
    LD_A(-1);

increase:
    INC_A;
    LD_hl_A;

finish_dpad:
    hlcoord(12, 9, wTilemap);
    LD_A(0x7f);
    LD_BC(7);
    CALL(aByteFill);
    hlcoord(12, 9, wTilemap);
    CALL(aDisplayMinutesWithMinString);
    CALL(aWaitBGMap);
    AND_A_A;
    RET;

a_button:
    SCF;
    RET;

}

bool SetMinutes_Conv(void){
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON);
    // IF_NZ goto a_button;
    if(hram->hJoyPressed & A_BUTTON) {
        return true;
    }
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto d_up;
    if(hram->hJoyLast & D_UP) {
    // d_up:
        // LD_HL(wInitMinuteBuffer);
        // LD_A_hl;
        // CP_A(59);
        // IF_C goto increase;
        if(wram->wInitMinuteBuffer == 59)
            wram->wInitMinuteBuffer = 0;
        // LD_A(-1);
        else {
        // increase:
            // INC_A;
            // LD_hl_A;
            ++wram->wInitMinuteBuffer;
        }
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto d_down;
    else if(hram->hJoyLast & D_DOWN) {
    // d_down:
        // LD_HL(wInitMinuteBuffer);
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto decrease;
        if(wram->wInitMinuteBuffer == 0) {
            // LD_A(59 + 1);
            wram->wInitMinuteBuffer = 59;
        }
        else {
        // decrease:
            // DEC_A;
            // LD_hl_A;
            wram->wInitMinuteBuffer--;
            // goto finish_dpad;
        }
    }
    else {
        // CALL(aDelayFrame);
        DelayFrame();
        // AND_A_A;
        // RET;
        return false;
    }

// finish_dpad:
    // hlcoord(12, 9, wTilemap);
    // LD_A(0x7f);
    // LD_BC(7);
    // CALL(aByteFill);
    ByteFill_Conv2(coord(12, 9, wram->wTilemap), 7, 0x7f);
    // hlcoord(12, 9, wTilemap);
    // CALL(aDisplayMinutesWithMinString);
    DisplayMinutesWithMinString_Conv(coord(12, 9, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // AND_A_A;
    // RET;
    return false;

// a_button:
    // SCF;
    // RET;
}

void DisplayMinutesWithMinString(void){
    LD_DE(wInitMinuteBuffer);
    CALL(aPrintTwoDigitNumberLeftAlign);
    INC_HL;
    LD_DE(mString_min);
    CALL(aPlaceString);
    RET;

}

uint8_t* DisplayMinutesWithMinString_Conv(uint8_t* hl){
    // LD_DE(wInitMinuteBuffer);
    // CALL(aPrintTwoDigitNumberLeftAlign);
    hl = PrintTwoDigitNumberLeftAlign_Conv(hl, &wram->wInitMinuteBuffer);
    // INC_HL;
    // LD_DE(mString_min);
    // CALL(aPlaceString);
    struct TextPrintState st = {.hl = hl + 1, .de = U82C(String_min)};
    PlaceString_Conv(&st, st.hl);
    // RET;
    return st.bc;
}

void PrintTwoDigitNumberLeftAlign(void){
    PUSH_HL;
    LD_A(0x7f);
    LD_hli_A;
    LD_hl_A;
    POP_HL;
    LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 2);
    CALL(aPrintNum);
    RET;

}

uint8_t* PrintTwoDigitNumberLeftAlign_Conv(uint8_t* hl, uint8_t* de){
    // PUSH_HL;
    // LD_A(0x7f);
    // LD_hli_A;
    hl[0] = CHAR_SPACE;
    // LD_hl_A;
    hl[1] = CHAR_SPACE;
    // POP_HL;
    // LD_BC((PRINTNUM_LEFTALIGN | 1 << 8) | 2);
    // CALL(aPrintNum);
    // RET;
    return PrintNum_Conv2(hl, de, PRINTNUM_LEFTALIGN | 1, 2);
}

const struct TextCmd OakTimeWokeUpText[] = {
    text_far(v_OakTimeWokeUpText)
    text_end
};

const struct TextCmd OakTimeWhatTimeIsItText[] = {
    text_far(v_OakTimeWhatTimeIsItText)
    text_end
};

static void OakTimeWhatHoursText_Function(struct TextCmdState* state);
// What?@ @
const struct TextCmd OakTimeWhatHoursText[] = {
    text_far(v_OakTimeWhatHoursText)
    text_asm(OakTimeWhatHoursText_Function)
};

static const struct TextCmd OakTimeWhatHoursText_OakTimeHoursQuestionMarkText[] = {
    text_far(v_OakTimeHoursQuestionMarkText)
    text_end
};

static void OakTimeWhatHoursText_Function(struct TextCmdState* state){
    // hlcoord(1, 16, wTilemap);
    // CALL(aDisplayHourOClock);
    state->bc = DisplayHourOClock_Conv(coord(1, 16, wram->wTilemap));
    // LD_HL(mOakTimeWhatHoursText_OakTimeHoursQuestionMarkText);
    state->hl = OakTimeWhatHoursText_OakTimeHoursQuestionMarkText;
    // RET;
}

const struct TextCmd OakTimeHowManyMinutesText[] = {
    text_far(v_OakTimeHowManyMinutesText)
    text_end
};

static void OakTimeWhoaMinutesText_Function(struct TextCmdState* state);
static const struct TextCmd OakTimeWhoaMinutesText_OakTimeMinutesQuestionMarkText[];
// Whoa!@ @
const struct TextCmd OakTimeWhoaMinutesText[] = {
    text_far(v_OakTimeWhoaMinutesText)
    text_asm(OakTimeWhoaMinutesText_Function)
};
static void OakTimeWhoaMinutesText_Function(struct TextCmdState* state){
    // hlcoord(7, 14, wTilemap);
    // CALL(aDisplayMinutesWithMinString);
    state->bc = DisplayMinutesWithMinString_Conv(coord(7, 14, wram->wTilemap));
    // LD_HL(mOakTimeWhoaMinutesText_OakTimeMinutesQuestionMarkText);
    state->hl = OakTimeWhoaMinutesText_OakTimeMinutesQuestionMarkText;
    // RET;
}
static const struct TextCmd OakTimeWhoaMinutesText_OakTimeMinutesQuestionMarkText[] = {
    text_far(v_OakTimeMinutesQuestionMarkText)
    text_end
};

static void OakText_ResponseToSetTime_Function(struct TextCmdState* state);
const struct TextCmd OakText_ResponseToSetTime[] = {
    text_asm(OakText_ResponseToSetTime_Function)
};
static void OakText_ResponseToSetTime_Function(struct TextCmdState* state){
    static const struct TextCmd OakTimeOversleptText[] = {
        text_far(v_OakTimeOversleptText)
        text_end
    };

    static const struct TextCmd OakTimeYikesText[] = {
        text_far(v_OakTimeYikesText)
        text_end
    };

    static const struct TextCmd OakTimeSoDarkText[] = {
        text_far(v_OakTimeSoDarkText)
        text_end
    };
    // decoord(1, 14, wTilemap);
    // LD_A_addr(wInitHourBuffer);
    // LD_C_A;
    // CALL(aPrintHour);
    uint8_t* hl = PrintHour_Conv(coord(1, 14, wram->wTilemap), wram->wInitHourBuffer);
    // LD_hl(0x9c);
    *hl = CHAR_COLON2;
    // INC_HL;
    // LD_DE(wInitMinuteBuffer);
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // CALL(aPrintNum);
    // LD_B_H;
    // LD_C_L;
    state->bc = PrintNum_Conv2(hl + 1, &wram->wInitMinuteBuffer, PRINTNUM_LEADINGZEROS | 1, 2);
    // LD_A_addr(wInitHourBuffer);
    // CP_A(MORN_HOUR);
    // IF_C goto nite;
    if(wram->wInitHourBuffer < MORN_HOUR) {
        state->hl = OakTimeSoDarkText;
        return;
    }
    // CP_A(DAY_HOUR + 1);
    // IF_C goto morn;
    else if(wram->wInitHourBuffer < DAY_HOUR + 1) {
        state->hl = OakTimeOversleptText;
        return;
    }
    // CP_A(NITE_HOUR);
    // IF_C goto day;
    else if(wram->wInitHourBuffer < NITE_HOUR) {
        state->hl = OakTimeYikesText;
        return;
    }
    else {
        state->hl = OakTimeSoDarkText;
        return;
    }
}

// void TimeSetUpArrowGFX(void){
// INCBIN "gfx/new_game/up_arrow.1bpp"
    // return TimeSetDownArrowGFX();
// }

// void TimeSetDownArrowGFX(void){
// INCBIN "gfx/new_game/down_arrow.1bpp"

    // return SetDayOfWeek();
// }

static uint8_t* SetDayOfWeek_PlaceWeekdayString(uint8_t* hl) {
    uint8_t buf[32];
    static const char *WeekdayStrings[] = {
    //  entries correspond to wCurDay constants (see constants/wram_constants.asm)
        [SUNDAY]    = " SUNDAY@",
        [MONDAY]    = " MONDAY@",
        [TUESDAY]   = " TUESDAY@",
        [WEDNESDAY] = "WEDNESDAY@",
        [THURSDAY]  = "THURSDAY@",
        [FRIDAY]    = " FRIDAY@",
        [SATURDAY]  = "SATURDAY@",
        " SUNDAY@",
    };
    // PUSH_HL;
    // LD_A_addr(wTempDayOfWeek);
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mSetDayOfWeek_WeekdayStrings);
    // ADD_HL_DE;
    // ADD_HL_DE;
    const char* de = WeekdayStrings[wram->wTempDayOfWeek];
    // LD_A_hli;
    // LD_D_hl;
    // LD_E_A;
    // POP_HL;
    // CALL(aPlaceString);
    struct TextPrintState st = {.hl = hl, .de = U82CA(buf, de)};
    PlaceString_Conv(&st, st.hl);
    // RET;
    return st.bc;
}

static const struct TextCmd OakTimeWhatDayIsItText[] = {
    text_far(v_OakTimeWhatDayIsItText)
    text_end
};

static void ConfirmWeekdayText_Function(struct TextCmdState* state);
static const struct TextCmd ConfirmWeekdayText[] = {
    text_asm(ConfirmWeekdayText_Function)
};
static void ConfirmWeekdayText_Function(struct TextCmdState* state) {
    static const struct TextCmd OakTimeIsItText[] = {
        text_far(v_OakTimeIsItText)
        text_end
    };
    // hlcoord(1, 14, wTilemap);
    // CALL(aSetDayOfWeek_PlaceWeekdayString);
    state->bc = SetDayOfWeek_PlaceWeekdayString(coord(1, 14, wram->wTilemap));
    // LD_HL(mSetDayOfWeek_OakTimeIsItText);
    state->hl = OakTimeIsItText;
    // RET;
}

static bool SetDayOfWeek_GetJoypadAction(void) {
    // LDH_A_addr(hJoyPressed);
    // AND_A(A_BUTTON);
    // IF_Z goto not_A;
    // SCF;
    // RET;
    if(hram->hJoyPressed & A_BUTTON)
        return true;

// not_A:
    // LD_HL(hJoyLast);
    // LD_A_hl;
    // AND_A(D_UP);
    // IF_NZ goto d_up;
    if(hram->hJoyLast & D_UP) {
    // d_up:
        // LD_HL(wTempDayOfWeek);
        // LD_A_hl;
        // CP_A(6);
        // IF_C goto increase;
        if(wram->wTempDayOfWeek >= 6) {
            // LD_A(SUNDAY - 1);
            wram->wTempDayOfWeek = SUNDAY;
        }
        else {
        // increase:
            // INC_A;
            // LD_hl_A;
            wram->wTempDayOfWeek++;
        }
    }
    // LD_A_hl;
    // AND_A(D_DOWN);
    // IF_NZ goto d_down;
    else if(hram->hJoyLast & D_DOWN) {
    // d_down:
        // LD_HL(wTempDayOfWeek);
        // LD_A_hl;
        // AND_A_A;
        // IF_NZ goto decrease;
        if(wram->wTempDayOfWeek == 0) {
            // LD_A(SATURDAY + 1);
            wram->wTempDayOfWeek = SATURDAY;
        }
        else {
        // decrease:
            // DEC_A;
            // LD_hl_A;
            // goto finish_dpad;
            wram->wTempDayOfWeek--;
        }
    }
    else {
        // CALL(aDelayFrame);
        DelayFrame();
        // AND_A_A;
        // RET;
        return false;
    }


// finish_dpad:
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = 0;
    // hlcoord(10, 4, wTilemap);
    // LD_B(2);
    // LD_C(9);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(10, 4, wram->wTilemap), 9, 2);
    // hlcoord(10, 5, wTilemap);
    // CALL(aSetDayOfWeek_PlaceWeekdayString);
    SetDayOfWeek_PlaceWeekdayString(coord(10, 5, wram->wTilemap));
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // AND_A_A;
    // RET;
    return false;
}

void SetDayOfWeek(void){
    // LDH_A_addr(hInMenu);
    // PUSH_AF;
    uint8_t inMenu = hram->hInMenu;
    // LD_A(0x1);
    // LDH_addr_A(hInMenu);
    hram->hInMenu = 0x1;
    // LD_DE(mTimeSetUpArrowGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * TIMESET_UP_ARROW);
    // LD_BC((BANK(aTimeSetUpArrowGFX) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * TIMESET_UP_ARROW, TimeSetUpArrowGFX, 0, 1);
    // LD_DE(mTimeSetDownArrowGFX);
    // LD_HL(vTiles0 + LEN_2BPP_TILE * TIMESET_DOWN_ARROW);
    // LD_BC((BANK(aTimeSetDownArrowGFX) << 8) | 1);
    // CALL(aRequest1bpp);
    LoadPNG1bppAssetSectionToVRAM(vram->vTiles0 + LEN_2BPP_TILE * TIMESET_DOWN_ARROW, TimeSetDownArrowGFX, 0, 1);
    // XOR_A_A;
    // LD_addr_A(wTempDayOfWeek);
    wram->wTempDayOfWeek = RTCGetCurrentWeekday();

    do {
    // loop:
        // hlcoord(0, 12, wTilemap);
        // LD_BC((4 << 8) | 18);
        // CALL(aTextbox);
        Textbox_Conv2(coord(0, 12, wram->wTilemap), 4, 18);
        // CALL(aLoadStandardMenuHeader);
        LoadStandardMenuHeader_Conv();
        // LD_HL(mSetDayOfWeek_OakTimeWhatDayIsItText);
        // CALL(aPrintText);
        PrintText_Conv2(OakTimeWhatDayIsItText);
        // hlcoord(9, 3, wTilemap);
        // LD_B(2);
        // LD_C(9);
        // CALL(aTextbox);
        Textbox_Conv2(coord(9, 3, wram->wTilemap), 2, 9);
        // hlcoord(14, 3, wTilemap);
        // LD_hl(TIMESET_UP_ARROW);
        *coord(14, 3, wram->wTilemap) = TIMESET_UP_ARROW;
        // hlcoord(14, 6, wTilemap);
        // LD_hl(TIMESET_DOWN_ARROW);
        *coord(14, 6, wram->wTilemap) = TIMESET_DOWN_ARROW;
        // hlcoord(10, 5, wTilemap);
        // CALL(aSetDayOfWeek_PlaceWeekdayString);
        SetDayOfWeek_PlaceWeekdayString(coord(10, 5, wram->wTilemap));
        // CALL(aApplyTilemap);
        ApplyTilemap_Conv();
        // LD_C(10);
        // CALL(aDelayFrames);
        DelayFrames_Conv(10);

        do {
        // loop2:
            // CALL(aJoyTextDelay);
            JoyTextDelay_Conv();
            // CALL(aSetDayOfWeek_GetJoypadAction);
            // IF_NC goto loop2;
        } while(!SetDayOfWeek_GetJoypadAction());
        // CALL(aExitMenu);
        ExitMenu_Conv2();
        // CALL(aUpdateSprites);
        UpdateSprites_Conv();
        // LD_HL(mSetDayOfWeek_ConfirmWeekdayText);
        // CALL(aPrintText);
        PrintText_Conv2(ConfirmWeekdayText);
        // CALL(aYesNoBox);
        // IF_C goto loop;
    } while(!YesNoBox_Conv());
    // LD_A_addr(wTempDayOfWeek);
    // LD_addr_A(wStringBuffer2);
    // CALL(aInitDayOfWeek);
    InitDayOfWeek_Conv(wram->wTempDayOfWeek);
    // CALL(aLoadStandardFont);
    LoadStandardFont_Conv();
    // POP_AF;
    // LDH_addr_A(hInMenu);
    hram->hInMenu = inMenu;
    // RET;
}

static void InitialSetDSTFlag_Text(struct TextCmdState* state) {
    static const struct TextCmd DSTIsThatOKText[] = {
        text_far(v_DSTIsThatOKText)
        text_end
    };
    // CALL(aUpdateTime);
    UpdateTime_Conv();
    // LDH_A_addr(hHours);
    // LD_B_A;
    // LDH_A_addr(hMinutes);
    // LD_C_A;
    // decoord(1, 14, wTilemap);
    // FARCALL(aPrintHoursMins);
    state->bc = PrintHoursMins_Conv(coord(1, 14, wram->wTilemap), hram->hHours, hram->hMinutes);
    // LD_HL(mInitialSetDSTFlag_DSTIsThatOKText);
    state->hl = DSTIsThatOKText;
    // RET;
}

void InitialSetDSTFlag(void){
    // LD_A_addr(wDST);
    // SET_A(7);
    // LD_addr_A(wDST);
    bit_set(wram->wDST, 7);
    // hlcoord(1, 14, wTilemap);
    // LD_BC((3 << 8) | 18);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 14, wram->wTilemap), 18, 3);
    // LD_HL(mInitialSetDSTFlag_Text);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), (struct TextCmd[]){ text_asm(InitialSetDSTFlag_Text) });
    // RET;

//Text:
    //text_asm ['?']
}

static void InitialClearDSTFlag_Text(struct TextCmdState* state) {
    static const struct TextCmd TimeAskOkayText[] = {
        text_far(v_TimeAskOkayText)
        text_end
    };

    // CALL(aUpdateTime);
    UpdateTime_Conv();
    // LDH_A_addr(hHours);
    // LD_B_A;
    // LDH_A_addr(hMinutes);
    // LD_C_A;
    // decoord(1, 14, wTilemap);
    // FARCALL(aPrintHoursMins);
    state->bc = PrintHoursMins_Conv(coord(1, 14, wram->wTilemap), hram->hHours, hram->hMinutes);
    // LD_HL(mInitialClearDSTFlag_TimeAskOkayText);
    state->hl = TimeAskOkayText;
    // RET;
}

void InitialClearDSTFlag(void){
    // LD_A_addr(wDST);
    // RES_A(7);
    // LD_addr_A(wDST);
    bit_reset(wram->wDST, 7);
    // hlcoord(1, 14, wTilemap);
    // LD_BC((3 << 8) | 18);
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 14, wram->wTilemap), 18, 3);
    // LD_HL(mInitialClearDSTFlag_Text);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), (struct TextCmd[]){ text_asm(InitialClearDSTFlag_Text) });
    // RET;


//Text:
    //text_asm ['?']
}

static tile_t* MrChrono_PrintTime(tile_t* hl, uint8_t* de) {
    // LD_BC((1 << 8) | 3);
    // CALL(aPrintNum);
    hl = PrintNum_Conv2(hl, de, 1, 3);
    // LD_hl(0xe8);
    *hl = CHAR_PERIOD;
    // INC_HL;
    hl++;
    // INC_DE;
    de++;
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // CALL(aPrintNum);
    hl = PrintNum_Conv2(hl, de, PRINTNUM_LEADINGZEROS | 1, 2);
    // LD_hl(0x9c);
    *hl = CHAR_COLON2;
    // INC_HL;
    hl++;
    // INC_DE;
    de++;
    // LD_BC((PRINTNUM_LEADINGZEROS | 1 << 8) | 2);
    // CALL(aPrintNum);
    hl = PrintNum_Conv2(hl, de, PRINTNUM_LEADINGZEROS | 1, 2);
    // RET;
    return hl;
}

static void MrChrono_Text(struct TextCmdState* state) {
// Text:
    //text_asm ['?']
    // CALL(aUpdateTime);
    UpdateTime_Conv();

    // hlcoord(1, 14, wTilemap);
    // LD_hl(0x91);
    *coord(1, 14, wram->wTilemap) = 0x91;
    // INC_HL;
    // LD_hl(0x93);
    *coord(2, 14, wram->wTilemap) = 0x93;
    // INC_HL;
    // LD_hl(0x7f);
    *coord(3, 14, wram->wTilemap) = CHAR_SPACE;
    // INC_HL;

    // LD_DE(hRTCDayLo);
    // CALL(aMrChrono_PrintTime);
    MrChrono_PrintTime(coord(4, 14, wram->wTilemap), &hram->hRTCDayLo);

    // hlcoord(1, 16, wTilemap);
    // LD_hl(0x83);
    *coord(1, 16, wram->wTilemap) = CHAR_A + ('D' - 'A');
    // INC_HL;
    // LD_hl(0x85);
    *coord(2, 16, wram->wTilemap) = CHAR_A + ('F' - 'A');
    // INC_HL;
    // LD_hl(0x7f);
    *coord(3, 16, wram->wTilemap) = CHAR_SPACE;
    // INC_HL;

    // LD_DE(wStartDay);
    // CALL(aMrChrono_PrintTime);
    tile_t* hl = MrChrono_PrintTime(coord(4, 16, wram->wTilemap), &wram->wStartDay);

    // LD_hl(0x7f);
    // INC_HL;
    *(hl++) = CHAR_SPACE;

    // LD_A_addr(wDST);
    // BIT_A(7);
    // IF_Z goto off;
    if(bit_test(wram->wDST, 7)) {

        // LD_hl(0x8e);
        // INC_HL;
        *(hl++) = CHAR_A + ('O' - 'A');
        // LD_hl(0x8d);
        // INC_HL;
        *(hl++) = CHAR_A + ('N' - 'A');
        // goto done;
    }
    else {
    // off:
        // LD_hl(0x8e);
        // INC_HL;
        *(hl++) = CHAR_A + ('O' - 'A');
        // LD_hl(0x85);
        // INC_HL;
        *(hl++) = CHAR_A + ('F' - 'A');
        // LD_hl(0x85);
        // INC_HL;
        *(hl++) = CHAR_A + ('F' - 'A');
    }

    static const struct TextCmd NowOnDebug[] = {
        text_start(
            t_para "Now on DEBUG…"
            t_prompt )
    };

// done:
    // LD_HL(mMrChrono_NowOnDebug);
    state->hl = NowOnDebug;
    // RET;
}

void MrChrono(void){
//  //  unreferenced
    // hlcoord(1, 14, wTilemap);
    // LD_BC((3 << 8) | (SCREEN_WIDTH - 2));
    // CALL(aClearBox);
    ClearBox_Conv2(coord(1, 14, wram->wTilemap), (SCREEN_WIDTH - 2), 3);
    // LD_HL(mMrChrono_Text);
    // CALL(aPlaceHLTextAtBC);
    PlaceHLTextAtBC_Conv2(coord(1, 14, wram->wTilemap), (struct TextCmd[]){ text_asm(MrChrono_Text) });
    // RET;
}

void PrintHour(void){
    LD_L_E;
    LD_H_D;
    PUSH_BC;
    CALL(aGetTimeOfDayString);
    CALL(aPlaceString);
    LD_L_C;
    LD_H_B;
    INC_HL;
    POP_BC;
    CALL(aAdjustHourForAMorPM);
    LD_addr_A(wTextDecimalByte);
    LD_DE(wTextDecimalByte);
    CALL(aPrintTwoDigitNumberLeftAlign);
    RET;

}

uint8_t* PrintHour_Conv(uint8_t* de, uint8_t c){
    // LD_L_E;
    // LD_H_D;
    // PUSH_BC;
    // CALL(aGetTimeOfDayString);
    const char* s = GetTimeOfDayString_Conv(c);
    // CALL(aPlaceString);
    struct TextPrintState st = {.hl = de, .de = U82C(s)};
    PlaceString_Conv(&st, st.hl);
    // LD_L_C;
    // LD_H_B;
    // INC_HL;
    uint8_t* hl = st.bc + 1;
    // POP_BC;
    // CALL(aAdjustHourForAMorPM);
    // LD_addr_A(wTextDecimalByte);
    wram->wTextDecimalByte = AdjustHourForAMorPM_Conv(c);
    // LD_DE(wTextDecimalByte);
    // CALL(aPrintTwoDigitNumberLeftAlign);
    // RET;
    return PrintTwoDigitNumberLeftAlign_Conv(hl, &wram->wTextDecimalByte);
}

void GetTimeOfDayString(void){
    LD_A_C;
    CP_A(MORN_HOUR);
    IF_C goto nite;
    CP_A(DAY_HOUR);
    IF_C goto morn;
    CP_A(NITE_HOUR);
    IF_C goto day;

nite:
    LD_DE(mGetTimeOfDayString_nite_string);
    RET;

morn:
    LD_DE(mGetTimeOfDayString_morn_string);
    RET;

day:
    LD_DE(mGetTimeOfDayString_day_string);
    RET;


nite_string:
// db "NITE@"

morn_string:
// db "MORN@"

day_string:
//  db "DAY@"

    return AdjustHourForAMorPM();
}

const char* GetTimeOfDayString_Conv(uint8_t c){
    // LD_A_C;
    // CP_A(MORN_HOUR);
    // IF_C goto nite;
    if(c < MORN_HOUR || c >= NITE_HOUR)
        return "NITE@";
    // CP_A(DAY_HOUR);
    // IF_C goto morn;
    if(c < DAY_HOUR)
        return "MORN@";
    // CP_A(NITE_HOUR);
    // IF_C goto day;
    if(c < NITE_HOUR)
        return "DAY@";

    return NULL;
// nite:
    // LD_DE(mGetTimeOfDayString_nite_string);
    // RET;

// morn:
    // LD_DE(mGetTimeOfDayString_morn_string);
    // RET;

// day:
    // LD_DE(mGetTimeOfDayString_day_string);
    // RET;


// nite_string:
// db "NITE@"

// morn_string:
// db "MORN@"

// day_string:
//  db "DAY@"
    // return AdjustHourForAMorPM();
}

void AdjustHourForAMorPM(void){
//  Convert the hour stored in c (0-23) to a 1-12 value
    LD_A_C;
    OR_A_A;
    IF_Z goto midnight;
    CP_A(NOON_HOUR);
    RET_C ;
    RET_Z ;
    SUB_A(NOON_HOUR);
    RET;


midnight:
    LD_A(NOON_HOUR);
    RET;

}

//  Convert the hour stored in c (0-23) to a 1-12 value
uint8_t AdjustHourForAMorPM_Conv(uint8_t c){
    // LD_A_C;
    // OR_A_A;
    // IF_Z goto midnight;
    if(c == 0) {
    // midnight:
        // LD_A(NOON_HOUR);
        // RET;
        return NOON_HOUR;
    }
    // CP_A(NOON_HOUR);
    // RET_C ;
    // RET_Z ;
    if(c > NOON_HOUR) {
        // SUB_A(NOON_HOUR);
        // RET;
        return c - NOON_HOUR;
    }
    return c;
}
