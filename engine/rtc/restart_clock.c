#include "../../constants.h"
#include "restart_clock.h"
#include "../../home/text.h"
#include "../../home/menu.h"
#include "../../home/time.h"
#include "../../home/joypad.h"
#include "../../home/scrolling_menu.h"
#include "../../home/pokedex_flags.h"
#include "../../charmap.h"
#include "../../data/text/common.h"
#include "print_hours_mins.h"
#include "../menus/intro_menu.h"

//  RestartClock_GetWraparoundTime.WrapAroundTimes indexes
enum {
    RESTART_CLOCK_DAY = 1,
    RESTART_CLOCK_HOUR,
    RESTART_CLOCK_MIN,
};
#define NUM_RESTART_CLOCK_DIVISIONS RESTART_CLOCK_MIN

#define wraparound_time(_0, _1, _2) {_0, _1, _2}
struct WrapAroundTime {
    uint8_t* const value;
    uint8_t max;
    uint8_t xCoord;
};

static struct WrapAroundTime RestartClock_GetWraparoundTime(uint8_t a){
    static const struct WrapAroundTime WrapAroundTimes[] = {
    //  entries correspond to RESTART_CLOCK_* constants
    // wraparound_time: MACRO
    //     dw \1 ; value pointer
    //     db \2 ; maximum value
    //     db \3 ; up/down arrow x coord (pairs with wRestartClockUpArrowYCoord)
    // ENDM
        [RESTART_CLOCK_DAY-1]   = wraparound_time(wram_ptr(wRestartClockDay), 7, 4),
        [RESTART_CLOCK_HOUR-1]  = wraparound_time(wram_ptr(wRestartClockHour), 24, 12),
        [RESTART_CLOCK_MIN-1]   = wraparound_time(wram_ptr(wRestartClockMin), 60, 15)
    };

    // PUSH_HL;
    // DEC_A;
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mRestartClock_GetWraparoundTime_WrapAroundTimes);
    // for(int rept = 0; rept < 4; rept++){
    // ADD_HL_DE;
    // }
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // INC_HL;
    // LD_B_hl;
    // INC_HL;
    // LD_C_hl;
    // POP_HL;
    // RET;
    return WrapAroundTimes[a - 1];
}

static void RestartClock_PlaceChars(uint8_t a, uint8_t d, uint8_t e) {
    // PUSH_DE;
    // CALL(aRestartClock_GetWraparoundTime);
    struct WrapAroundTime wa = RestartClock_GetWraparoundTime(a);
    // LD_A_addr(wRestartClockUpArrowYCoord);
    // DEC_A;
    // LD_B_A;
    // CALL(aCoord2Tile);
    uint8_t* hl = Coord2Tile(wa.xCoord, wram->wRestartClockUpArrowYCoord - 1);
    // POP_DE;
    // LD_hl_D;
    hl[0] = d;
    // LD_BC(2 * SCREEN_WIDTH);
    // ADD_HL_BC;
    // LD_hl_E;
    hl[2 * SCREEN_WIDTH] = e;
    // RET;
}

static void RestartClock_PrintTime(void) {
    // hlcoord(0, 5, wTilemap);
    // LD_B(5);
    // LD_C(18);
    // CALL(aTextbox);
    Textbox(coord(0, 5, wram->wTilemap), 5, 18);
    // decoord(1, 8, wTilemap);
    // LD_A_addr(wRestartClockDay);
    // LD_B_A;
    // FARCALL(aPrintDayOfWeek);
    PrintDayOfWeek_Conv(coord(1, 8, wram->wTilemap), wram->wRestartClockDay);
    // LD_A_addr(wRestartClockHour);
    // LD_B_A;
    // LD_A_addr(wRestartClockMin);
    // LD_C_A;
    // decoord(11, 8, wTilemap);
    // FARCALL(aPrintHoursMins);
    PrintHoursMins_Conv(coord(11, 8, wram->wTilemap), wram->wRestartClockHour, wram->wRestartClockMin);
    // LD_A_addr(wRestartClockPrevDivision);
    // LD_DE((CHAR_SPACE << 8) | CHAR_SPACE);
    // CALL(aRestartClock_PlaceChars);
    RestartClock_PlaceChars(wram->wRestartClockPrevDivision, CHAR_SPACE, CHAR_SPACE);
    // LD_A_addr(wRestartClockCurDivision);
    // LD_DE(("▲" << 8) | "▼");
    // LD_DE((CHAR_UP_ARROW << 8) | CHAR_DOWN_CURSOR);
    // CALL(aRestartClock_PlaceChars);
    RestartClock_PlaceChars(wram->wRestartClockCurDivision, CHAR_UP_ARROW, CHAR_DOWN_CURSOR);
    // LD_A_addr(wRestartClockCurDivision);
    // LD_addr_A(wRestartClockPrevDivision);
    wram->wRestartClockPrevDivision = wram->wRestartClockCurDivision;
    // RET;


// UnusedPlaceCharsFragment:
//   //  unreferenced
    // LD_A_addr(wRestartClockUpArrowYCoord);
    // LD_B_A;
    // CALL(aCoord2Tile);
    // RET;
}

static u8_flag_s RestartClock_joy_loop(void) {
    while(1) {
    // joy_loop:
        // CALL(aJoyTextDelay_ForcehJoyDown);
        uint8_t a = JoyTextDelay_ForcehJoyDown();
        // LD_C_A;
        // PUSH_AF;
        // CALL(aRestartClock_PrintTime);
        RestartClock_PrintTime();
        // POP_AF;
        // BIT_A(0);
        // IF_NZ goto press_A;
        if(bit_test(a, A_BUTTON_F)) {
        // press_A:
            // LD_A(FALSE);
            // SCF;
            // RET;
            return u8_flag(FALSE, true);
        }
        // BIT_A(1);
        // IF_NZ goto press_B;
        else if(bit_test(a, B_BUTTON_F)) {
        // press_B:
            // LD_A(TRUE);
            // SCF;
            // RET;
            return u8_flag(TRUE, true);
        }
        // BIT_A(6);
        // IF_NZ goto pressed_up;
        else if(bit_test(a, D_UP_F)) {
        // pressed_up:
            // LD_A_addr(wRestartClockCurDivision);
            // CALL(aRestartClock_GetWraparoundTime);
            struct WrapAroundTime wa = RestartClock_GetWraparoundTime(wram->wRestartClockCurDivision);
            // LD_A_de;
            // INC_A;
            // LD_de_A;
            uint8_t v = ++(*wa.value);
            // CP_A_B;
            // IF_C goto done_scroll;
            if(v >= wa.max) {
                // LD_A(0);
                // LD_de_A;
                (*wa.value) = 0;
            }
            // goto done_scroll;
            break;
        }
        // BIT_A(7);
        // IF_NZ goto pressed_down;
        else if(bit_test(a, D_DOWN_F)) {
        // pressed_down:
            // LD_A_addr(wRestartClockCurDivision);
            // CALL(aRestartClock_GetWraparoundTime);
            struct WrapAroundTime wa = RestartClock_GetWraparoundTime(wram->wRestartClockCurDivision);
            // LD_A_de;
            // DEC_A;
            // LD_de_A;
            uint8_t v = --(*wa.value);
            // CP_A(-1);
            // IF_NZ goto done_scroll;
            if(v == 0xff) {
                // LD_A_B;
                // DEC_A;
                // LD_de_A;
                (*wa.value) = wa.max - 1;
            }
            // goto done_scroll;
            break;
        }
        // BIT_A(5);
        // IF_NZ goto pressed_left;
        else if(bit_test(a, D_LEFT_F)) {
        // pressed_left:
            // LD_HL(wRestartClockCurDivision);
            // DEC_hl;
            // IF_NZ goto done_scroll;
            if(--wram->wRestartClockCurDivision == 0)
                wram->wRestartClockCurDivision = RESTART_CLOCK_MIN;
            // LD_hl(RESTART_CLOCK_MIN);
            // goto done_scroll;
            break;
        }
        // BIT_A(4);
        // IF_NZ goto pressed_right;
        else if(bit_test(a, D_RIGHT_F)) {
        // pressed_right:
            // LD_HL(wRestartClockCurDivision);
            // INC_hl;
            // LD_A_hl;
            // CP_A(NUM_RESTART_CLOCK_DIVISIONS + 1);
            // IF_C goto done_scroll;
            if(++wram->wRestartClockCurDivision >= NUM_RESTART_CLOCK_DIVISIONS + 1)
                wram->wRestartClockCurDivision = RESTART_CLOCK_DAY;
            // LD_hl(RESTART_CLOCK_DAY);
            break;
        }
        // goto joy_loop;
    }


// done_scroll:
    // XOR_A_A;  // FALSE
    // RET;
    return u8_flag(FALSE, false);
}

static bool RestartClock_SetClock(void) {
// SetClock:
    // LD_A(RESTART_CLOCK_DAY);
    // LD_addr_A(wRestartClockCurDivision);
    wram->wRestartClockCurDivision = RESTART_CLOCK_DAY;
    // LD_addr_A(wRestartClockPrevDivision);
    wram->wRestartClockPrevDivision = RESTART_CLOCK_DAY;
    // LD_A(8);
    // LD_addr_A(wRestartClockUpArrowYCoord);
    wram->wRestartClockUpArrowYCoord = 8;
    // CALL(aUpdateTime);
    UpdateTime();
    // CALL(aGetWeekday);
    // LD_addr_A(wRestartClockDay);
    wram->wRestartClockDay = GetWeekday();
    // LDH_A_addr(hHours);
    // LD_addr_A(wRestartClockHour);
    wram->wRestartClockHour = hram->hHours;
    // LDH_A_addr(hMinutes);
    // LD_addr_A(wRestartClockMin);
    wram->wRestartClockMin = hram->hMinutes;

    u8_flag_s res;
    do {
    // loop:
        // CALL(aRestartClock_joy_loop);
        res = RestartClock_joy_loop();
        // IF_NC goto loop;
    } while(!res.flag);
    // AND_A_A;
    // RET_NZ ;
    if(res.a != 0)
        return true;
    // CALL(aRestartClock_PrintTime);
    RestartClock_PrintTime();

    static const txt_cmd_s ClockIsThisOKText[] = {
        text_far(v_ClockIsThisOKText)
        text_end
    };
    // LD_HL(mRestartClock_ClockIsThisOKText);
    // CALL(aPrintText);
    PrintText_Conv2(ClockIsThisOKText);
    // CALL(aYesNoBox);
    // IF_C goto cancel;
    if(!YesNoBox()) {
    // cancel:
        // LD_A(TRUE);
        // RET;
        return true;
    }
    // LD_A_addr(wRestartClockDay);
    // LD_addr_A(wStringBuffer2);
    // LD_A_addr(wRestartClockHour);
    // LD_addr_A(wStringBuffer2 + 1);
    // LD_A_addr(wRestartClockMin);
    // LD_addr_A(wStringBuffer2 + 2);
    // XOR_A_A;
    // LD_addr_A(wStringBuffer2 + 3);
    // CALL(aInitTime);
    InitTime(wram->wRestartClockDay, wram->wRestartClockHour, wram->wRestartClockMin, 0);
    // CALL(aRestartClock_PrintTime);
    RestartClock_PrintTime();

    static const txt_cmd_s ClockHasResetText[] = {
        text_far(v_ClockHasResetText)
        text_end
    };
    // LD_HL(mRestartClock_ClockHasResetText);
    // CALL(aPrintText);
    PrintText_Conv2(ClockHasResetText);
    // CALL(aWaitPressAorB_BlinkCursor);
    WaitPressAorB_BlinkCursor();
    // XOR_A_A;  // FALSE
    // RET;
    return false;
}

uint8_t RestartClock(void){
    static const txt_cmd_s ClockTimeMayBeWrongText[] = {
        text_far(v_ClockTimeMayBeWrongText)
        text_end
    };

//  If we're here, we had an RTC overflow.
    // LD_HL(mRestartClock_ClockTimeMayBeWrongText);
    // CALL(aPrintText);
    PrintText_Conv2(ClockTimeMayBeWrongText);
    // LD_HL(wOptions);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t options = wram->wOptions;
    // SET_hl(NO_TEXT_SCROLL);
    bit_set(wram->wOptions, NO_TEXT_SCROLL);
    // CALL(aLoadStandardMenuHeader);
    LoadStandardMenuHeader();
    // CALL(aClearTilemap);
    ClearTilemap();

    static const txt_cmd_s ClockSetWithControlPadText[] = {
        text_far(v_ClockSetWithControlPadText)
        text_end
    };
    // LD_HL(mRestartClock_ClockSetWithControlPadText);
    // CALL(aPrintText);
    PrintText_Conv2(ClockSetWithControlPadText);
    // CALL(aRestartClock_SetClock);
    bool cancel = RestartClock_SetClock();
    // CALL(aExitMenu);
    ExitMenu();
    // POP_BC;
    // LD_HL(wOptions);
    // LD_hl_B;
    wram->wOptions = options;
    // LD_C_A;
    // REG_C = cancel? TRUE: FALSE;
    // RET;
    return cancel? TRUE: FALSE;
}

// void JPHourString(void){
//  //  unreferenced
    //db ['"じ@"'];  // HR
    // return JPMinuteString();
// }

// void JPMinuteString(void){
//  //  unreferenced
    //db ['"ふん@"'];  // MIN
// }
