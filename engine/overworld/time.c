#include "../../constants.h"
#include "time.h"
#include "../../home/random.h"
#include "../../home/time.h"
#include "../../home/pokedex_flags.h"
#include "../../home/sram.h"
#include "../link/mystery_gift.h"
#include "../events/pokerus/apply_pokerus_tick.h"

void v_InitializeStartDay(void){
    // CALL(aInitializeStartDay);
    InitializeStartDay();
    // RET;
}

void ClearDailyTimers(void){
    // XOR_A_A;
    // LD_addr_A(wLuckyNumberDayTimer);
    gPlayer.luckyNumberDayTimer = 0;
    // LD_addr_A(wUnusedTwoDayTimer);
    wram->wUnusedTwoDayTimer = 0;
    // LD_addr_A(wDailyResetTimer);
    gPlayer.dailyResetTimer = 0;
    // RET;
}

void InitCallReceiveDelay(void){
    // XOR_A_A;
    // LD_addr_A(wTimeCyclesSinceLastCall);
    wram->wTimeCyclesSinceLastCall = 0;

    return NextCallReceiveDelay();
}

void NextCallReceiveDelay(void){
    static const uint8_t ReceiveCallDelays[] = {20, 10, 5, 3};
    // LD_A_addr(wTimeCyclesSinceLastCall);
    uint8_t a = wram->wTimeCyclesSinceLastCall;
    // CP_A(3);
    // IF_C goto okay;
    // LD_A(3);
    if(a >= 3)
        a = 3;


// okay:
    // LD_E_A;
    // LD_D(0);
    // LD_HL(mNextCallReceiveDelay_ReceiveCallDelays);
    // ADD_HL_DE;
    // LD_A_hl;
    a = ReceiveCallDelays[a];
#if defined(_DEBUG) && !defined(_MSC_VER)
    // LD_H_A;
    // LD_A(BANK(sDebugTimeCyclesSinceLastCall));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asDebugTimeCyclesSinceLastCall));
    // LD_A_addr(sDebugTimeCyclesSinceLastCall);
    uint8_t a2 = gb_read(sDebugTimeCyclesSinceLastCall);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // DEC_A;
    // CP_A(2);
    // IF_NC goto debug_ok;
    if(a2 < 2) {
        // XOR_A(1);
        // LD_H_A;
        a = a2 ^ 1;
    }

// debug_ok:
    // LD_A_H;
#endif
    // JP(mRestartReceiveCallDelay);
    RestartReceiveCallDelay(a);
}

bool CheckReceiveCallTimer(void){
    // CALL(aCheckReceiveCallDelay);  // check timer
    // RET_NC ;
    if(!CheckReceiveCallDelay())
        return false;

    // LD_HL(wTimeCyclesSinceLastCall);
    // LD_A_hl;
    // CP_A(3);
    // IF_NC goto ok;
    // INC_hl;
    if(wram->wTimeCyclesSinceLastCall < 3)
        wram->wTimeCyclesSinceLastCall++;


// ok:
    // CALL(aNextCallReceiveDelay);  // restart timer
    NextCallReceiveDelay();
    // SCF;
    // RET;
    return true;
}

void InitOneDayCountdown(uint8_t* hl){
    // LD_A(1);
    return InitNDaysCountdown(hl, 1);
}

void InitNDaysCountdown(uint8_t* hl, uint8_t n){
    // LD_hl_A;
    hl[0] = n;
    // PUSH_HL;
    // CALL(aUpdateTime);
    UpdateTime();
    // POP_HL;
    // INC_HL;
    // CALL(aCopyDayToHL);
    hl[1] = gPlayer.curDay;
    // RET;
}

bool CheckDayDependentEventHL(uint8_t* hl){
    // INC_HL;
    // PUSH_HL;
    // CALL(aCalcDaysSince);
    CalcDaysSince(hl + 1);
    // CALL(aGetDaysSince);
    uint8_t days = GetDaysSince();
    // POP_HL;
    // DEC_HL;
    // CALL(aUpdateTimeRemaining);
    return UpdateTimeRemaining(hl, days);
    // RET;
}

void RestartReceiveCallDelay(uint8_t a){
    // LD_HL(wReceiveCallDelay_MinsRemaining);
    // LD_hl_A;
    wram->wReceiveCallDelay_MinsRemaining = a;
    // CALL(aUpdateTime);
    UpdateTime();
    // LD_HL(wReceiveCallDelay_StartTime);
    // CALL(aCopyDayHourMinToHL);
    CopyDayHourMinToHL(wram->wReceiveCallDelay_StartTime);
    // RET;
}

bool CheckReceiveCallDelay(void){
    // LD_HL(wReceiveCallDelay_StartTime);
    // CALL(aCalcMinsHoursDaysSince);
    CalcMinsHoursDaysSince(wram->wReceiveCallDelay_StartTime);
    // CALL(aGetMinutesSinceIfLessThan60);
    uint8_t mins = GetMinutesSinceIfLessThan60();
    // LD_HL(wReceiveCallDelay_MinsRemaining);
    // CALL(aUpdateTimeRemaining);
    return UpdateTimeRemaining(&wram->wReceiveCallDelay_MinsRemaining, mins);
    // RET;
}

void RestartDailyResetTimer(void){
    // LD_HL(wDailyResetTimer);
    // JP(mInitOneDayCountdown);
    return InitOneDayCountdown((uint8_t*)&gPlayer.dailyResetTimer);
}

void CheckDailyResetTimer(void){
    // LD_HL(wDailyResetTimer);
    // CALL(aCheckDayDependentEventHL);
    // RET_NC ;
    if(!CheckDayDependentEventHL((uint8_t*)&gPlayer.dailyResetTimer))
        return;
    
    // XOR_A_A;
    // LD_HL(wDailyFlags1);
    // LD_hli_A;  // wDailyFlags1
    gPlayer.dailyFlags1 = 0;
    // LD_hli_A;  // wDailyFlags2
    gPlayer.dailyFlags2 = 0;
    // LD_hli_A;  // wSwarmFlags
    gPlayer.swarmFlags = 0;
    // LD_hl_A;  // wSwarmFlags + 1
    wram->skip_121[0] = 0;
    // LD_HL(wDailyRematchFlags);
    // for(int rept = 0; rept < 4; rept++){
    // LD_hli_A;
    // }
    for(uint32_t i = 0; i < lengthof(gPlayer.dailyRematchFlags); ++i)
        gPlayer.dailyRematchFlags[i] = 0;
    // LD_HL(wDailyPhoneItemFlags);
    // for(int rept = 0; rept < 4; rept++){
    // LD_hli_A;
    // }
    for(uint32_t i = 0; i < lengthof(gPlayer.dailyPhoneItemFlags); ++i)
        gPlayer.dailyPhoneItemFlags[i] = 0;
    // LD_HL(wDailyPhoneTimeOfDayFlags);
    // for(int rept = 0; rept < 4; rept++){
    // LD_hli_A;
    // }
    for(uint32_t i = 0; i < lengthof(gPlayer.dailyPhoneTimeOfDayFlags); ++i)
        gPlayer.dailyPhoneTimeOfDayFlags[i] = 0;
    // LD_HL(wKenjiBreakTimer);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto RestartKenjiBreakCountdown;
    if(gPlayer.wKenjiBreakTimer[0] == 0) {
        SampleKenjiBreakCountdown();
    }
    // DEC_hl;
    // IF_NZ goto DontRestartKenjiBreakCountdown;
    else if(--gPlayer.wKenjiBreakTimer[0] == 0) {
        SampleKenjiBreakCountdown();
    }
// RestartKenjiBreakCountdown:
    // CALL(aSampleKenjiBreakCountdown);

// DontRestartKenjiBreakCountdown:
    // JR(mRestartDailyResetTimer);
    return RestartDailyResetTimer();
}

//  Generate a random number between 3 and 6
void SampleKenjiBreakCountdown(void){
    // CALL(aRandom);
    // AND_A(0b11);
    // ADD_A(3);
    // LD_addr_A(wKenjiBreakTimer);
    // RET;
    gPlayer.wKenjiBreakTimer[0] = (Random() & 0b11) + 3;
}

void StartBugContestTimer(void){
    // LD_A(BUG_CONTEST_MINUTES);
    // LD_addr_A(wBugContestMinsRemaining);
    wram->wBugContestMinsRemaining = BUG_CONTEST_MINUTES;
    // LD_A(BUG_CONTEST_SECONDS);
    // LD_addr_A(wBugContestSecsRemaining);
    wram->wBugContestSecsRemaining = BUG_CONTEST_SECONDS;
    // CALL(aUpdateTime);
    UpdateTime();
    // LD_HL(wBugContestStartTime);
    // CALL(aCopyDayHourMinSecToHL);
    CopyDayHourMinSecToHL(gPlayer.bugContestStartTime);
    // RET;
}

bool CheckBugContestTimer(void){
    // LD_HL(wBugContestStartTime);
    // CALL(aCalcSecsMinsHoursDaysSince);
    CalcSecsMinsHoursDaysSince(gPlayer.bugContestStartTime);
    // LD_A_addr(wDaysSince);
    // AND_A_A;
    // IF_NZ goto timed_out;
    // LD_A_addr(wHoursSince);
    // AND_A_A;
    // IF_NZ goto timed_out;
    if(wram->wDaysSince == 0 && wram->wHoursSince == 0) {
        // LD_A_addr(wSecondsSince);
        // LD_B_A;
        // LD_A_addr(wBugContestSecsRemaining);
        // SUB_A_B;
        uint16_t temp = wram->wBugContestSecsRemaining - wram->wSecondsSince;
        uint8_t a = (temp & 0xff);
        uint8_t carry = (temp & 0xff00)? 1: 0;
        // IF_NC goto okay;
        // ADD_A(60);
        if(carry)
            a += 60;

    // okay:
        // LD_addr_A(wBugContestSecsRemaining);
        wram->wBugContestSecsRemaining = a;
        // LD_A_addr(wMinutesSince);
        // LD_B_A;
        // LD_A_addr(wBugContestMinsRemaining);
        // SBC_A_B;
        temp = wram->wBugContestMinsRemaining - wram->wMinutesSince - carry;
        // LD_addr_A(wBugContestMinsRemaining);
        wram->wBugContestMinsRemaining = (temp & 0xff);
        carry = (temp & 0xff00)? 1: 0;
        // IF_C goto timed_out;
        if(!carry) {
            // AND_A_A;
            // RET;
            return false;
        }
    }

// timed_out:
    // XOR_A_A;
    // LD_addr_A(wBugContestMinsRemaining);
    wram->wBugContestMinsRemaining = 0;
    // LD_addr_A(wBugContestSecsRemaining);
    wram->wBugContestSecsRemaining = 0;
    // SCF;
    // RET;
    return true;
}

void InitializeStartDay(void){
    // CALL(aUpdateTime);
    UpdateTime();
    // LD_HL(wTimerEventStartDay);
    // CALL(aCopyDayToHL);
    CopyDayToHL(&gPlayer.timerEventStartDay);
    // RET;
}

void CheckPokerusTick(void){
    // LD_HL(wTimerEventStartDay);
    // CALL(aCalcDaysSince);
    CalcDaysSince(&gPlayer.timerEventStartDay);
    // CALL(aGetDaysSince);
    uint8_t days = GetDaysSince();
    // AND_A_A;
    // IF_Z goto done;  // not even a day has passed since game start
    if(days != 0) {
        // LD_B_A;
        // FARCALL(aApplyPokerusTick);
        ApplyPokerusTick(days);
    }
// done:
    // XOR_A_A;
    // RET;
}

void SetUnusedTwoDayTimer(void){
//  //  unreferenced
    LD_A(2);
    LD_HL(wUnusedTwoDayTimer);
    LD_hl_A;
    CALL(aUpdateTime);
    LD_HL(wUnusedTwoDayTimerStartDate);
    CALL(aCopyDayToHL);
    RET;

}

void CheckUnusedTwoDayTimer(void){
    LD_HL(wUnusedTwoDayTimerStartDate);
    CALL(aCalcDaysSince);
    CALL(aGetDaysSince);
    LD_HL(wUnusedTwoDayTimer);
    CALL(aUpdateTimeRemaining);
    RET;

}

void UnusedSetSwarmFlag(void){
//  //  unreferenced
    LD_HL(wDailyFlags1);
    SET_hl(DAILYFLAGS1_FISH_SWARM_F);
    RET;

}

void UnusedCheckSwarmFlag(void){
//  //  unreferenced
    AND_A_A;
    LD_HL(wDailyFlags1);
    BIT_hl(DAILYFLAGS1_FISH_SWARM_F);
    RET_NZ ;
    SCF;
    RET;

}

static uint8_t RestartLuckyNumberCountdown_GetDaysUntilNextFriday(void) {
    // CALL(aGetWeekday);
    // LD_C_A;
    uint8_t c = GetWeekday();
    // LD_A(FRIDAY);
    // SUB_A_C;
    // IF_Z goto friday_saturday;
    if(c >= FRIDAY) {
    // friday_saturday:
        // ADD_A(7);
        return 7;
    }
    // IF_NC goto earlier;  // could have done "ret nc"
    else {
    // earlier:
        // RET;
        return FRIDAY - c;
    }
}

void RestartLuckyNumberCountdown(void){
    // CALL(aRestartLuckyNumberCountdown_GetDaysUntilNextFriday);
    uint8_t n = RestartLuckyNumberCountdown_GetDaysUntilNextFriday();
    // LD_HL(wLuckyNumberDayTimer);
    // JP(mInitNDaysCountdown);
    return InitNDaysCountdown((uint8_t*)&gPlayer.luckyNumberDayTimer, n);
}

bool v_CheckLuckyNumberShowFlag(void){
    // LD_HL(wLuckyNumberDayTimer);
    // JP(mCheckDayDependentEventHL);
    return CheckDayDependentEventHL((uint8_t*)&gPlayer.luckyNumberDayTimer);
}

void DoMysteryGiftIfDayHasPassed(void){
    // LD_A(BANK(sMysteryGiftTimer));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMysteryGiftTimer));
    // LD_HL(sMysteryGiftTimer);
    // LD_A_hli;
    // LD_addr_A(wTempMysteryGiftTimer);
    // LD_A_hl;
    // LD_addr_A(wTempMysteryGiftTimer + 1);
    wram->wTempMysteryGiftTimer = gb_read16(sMysteryGiftTimer);
    // CALL(aCloseSRAM);
    CloseSRAM();

    // LD_HL(wTempMysteryGiftTimer);
    // CALL(aCheckDayDependentEventHL);
    // IF_NC goto not_timed_out;
    if(CheckDayDependentEventHL((uint8_t*)&wram->wTempMysteryGiftTimer)) {
        // LD_HL(wTempMysteryGiftTimer);
        // CALL(aInitOneDayCountdown);
        InitOneDayCountdown((uint8_t*)&wram->wTempMysteryGiftTimer);
        // CALL(aCloseSRAM);
        CloseSRAM();
        // FARCALL(aResetDailyMysteryGiftLimitIfUnlocked);
        ResetDailyMysteryGiftLimitIfUnlocked();
    }

// not_timed_out:
    // LD_A(BANK(sMysteryGiftTimer));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asMysteryGiftTimer));
    // LD_HL(wTempMysteryGiftTimer);
    // LD_A_hli;
    // LD_addr_A(sMysteryGiftTimer);
    // LD_A_hl;
    // LD_addr_A(sMysteryGiftTimer + 1);
    gb_write(sMysteryGiftTimer, wram->wTempMysteryGiftTimer);
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

//  If the amount of time elapsed exceeds the capacity of its
//  unit, skip this part.
bool UpdateTimeRemaining(uint8_t* hl, uint8_t a){
    // CP_A(-1);
    // IF_Z goto set_carry;
    if(a == 0xff) {
        *hl = 0;
        return true;
    }
    // LD_C_A;
    // LD_A_hl;  // time remaining
    // SUB_A_C;
    uint16_t temp = *hl - a;
    a = (temp & 0xff);
    uint8_t carry = (temp & 0xff00)? 1: 0;
    // IF_NC goto ok;
    // XOR_A_A;
    if(carry) {
        a = 0;
    }


// ok:
    // LD_hl_A;
    *hl = a;
    // IF_Z goto set_carry;
    if(a == 0) {
        return true;
    }
    // XOR_A_A;
    // RET;
    return false;

// set_carry:
    // XOR_A_A;
    // LD_hl_A;
    // SCF;
    // RET;
}

void GetSecondsSinceIfLessThan60(void){
//  //  unreferenced
    LD_A_addr(wDaysSince);
    AND_A_A;
    JR_NZ (mGetTimeElapsed_ExceedsUnitLimit);
    LD_A_addr(wHoursSince);
    AND_A_A;
    JR_NZ (mGetTimeElapsed_ExceedsUnitLimit);
    LD_A_addr(wMinutesSince);
    JR_NZ (mGetTimeElapsed_ExceedsUnitLimit);
    LD_A_addr(wSecondsSince);
    RET;

}

uint8_t GetMinutesSinceIfLessThan60(void){
    // LD_A_addr(wDaysSince);
    // AND_A_A;
    // JR_NZ (mGetTimeElapsed_ExceedsUnitLimit);
    // LD_A_addr(wHoursSince);
    // AND_A_A;
    // JR_NZ (mGetTimeElapsed_ExceedsUnitLimit);
    if(wram->wDaysSince != 0 || wram->wHoursSince != 0) {
        return 0xff;
    }
    // LD_A_addr(wMinutesSince);
    // RET;
    return wram->wMinutesSince;
}

void GetHoursSinceIfLessThan24(void){
//  //  unreferenced
    LD_A_addr(wDaysSince);
    AND_A_A;
    JR_NZ (mGetTimeElapsed_ExceedsUnitLimit);
    LD_A_addr(wHoursSince);
    RET;

}

uint8_t GetDaysSince(void){
    // LD_A_addr(wDaysSince);
    // RET;
    return wram->wDaysSince;
}

void GetTimeElapsed_ExceedsUnitLimit(void){
    LD_A(-1);
    RET;

}

void CalcDaysSince(uint8_t* hl){
    // XOR_A_A;
    // JR(mv_CalcDaysSince);
    return v_CalcDaysSince(hl, 0);
}

void CalcHoursDaysSince(void){
//  //  unreferenced
    INC_HL;
    XOR_A_A;
    JR(mv_CalcHoursDaysSince);

}

void CalcMinsHoursDaysSince(uint8_t* hl){
    // INC_HL;
    // INC_HL;
    // XOR_A_A;
    // JR(mv_CalcMinsHoursDaysSince);
    return v_CalcMinsHoursDaysSince(hl + 2, 0);
}

void CalcSecsMinsHoursDaysSince(uint8_t* hl){
    // INC_HL;
    // INC_HL;
    // INC_HL;
    hl += 3;
    // LDH_A_addr(hSeconds);
    // LD_C_A;
    // SUB_A_hl;
    uint16_t temp = hram.hSeconds - *hl;
    uint8_t a = (temp & 0xff);
    uint8_t carry = (temp & 0xff00)? 1: 0;
    // IF_NC goto skip;
    // ADD_A(60);
    if(carry) {
        a += 60;
    }

// skip:
    // LD_hl_C;  // current seconds
    *hl = hram.hSeconds;
    // DEC_HL;
    hl--;
    // LD_addr_A(wSecondsSince);  // seconds since
    wram->wSecondsSince = a;

    return v_CalcMinsHoursDaysSince(hl, carry);
}

void v_CalcMinsHoursDaysSince(uint8_t* hl, uint8_t carry){
    // LDH_A_addr(hMinutes);
    // LD_C_A;
    // SBC_A_hl;
    uint16_t temp = hram.hMinutes - *hl - carry;
    uint8_t a = (temp & 0xff);
    carry = (temp & 0xff00)? 1: 0;
    // IF_NC goto skip;
    // ADD_A(60);
    if(carry) {
        a += 60;
    }

// skip:
    // LD_hl_C;  // current minutes
    *hl = hram.hMinutes;
    // DEC_HL;
    --hl;
    // LD_addr_A(wMinutesSince);  // minutes since
    wram->wMinutesSince = a;

    return v_CalcHoursDaysSince(hl, carry);
}

void v_CalcHoursDaysSince(uint8_t* hl, uint8_t carry){
    // LDH_A_addr(hHours);
    // LD_C_A;
    // SBC_A_hl;
    uint16_t temp = hram.hHours - *hl - carry;
    uint8_t a = (temp & 0xff);
    carry = (temp & 0xff00)? 1: 0;
    // IF_NC goto skip;
    // ADD_A(MAX_HOUR);
    if(carry) {
        a += MAX_HOUR;
    }

// skip:
    // LD_hl_C;  // current hours
    *hl = hram.hHours;
    // DEC_HL;
    hl--;
    // LD_addr_A(wHoursSince);  // hours since
    wram->wHoursSince = a;

    return v_CalcDaysSince(hl, carry);
}

void v_CalcDaysSince(uint8_t* hl, uint8_t carry){
    // LD_A_addr(wCurDay);
    // LD_C_A;
    // SBC_A_hl;
    uint16_t temp = gPlayer.curDay - *hl - carry;
    uint8_t a = (temp & 0xff);
    carry = (temp & 0xff00)? 1: 0;
    // IF_NC goto skip;
    // ADD_A(20 * 7);
    if(carry) {
        a += (20 * 7);
    }

// skip:
    // LD_hl_C;  // current days
    *hl = gPlayer.curDay;
    // LD_addr_A(wDaysSince);  // days since
    wram->wDaysSince = a;
    // RET;
}

void CopyDayHourMinSecToHL(uint8_t* hl){
    // LD_A_addr(wCurDay);
    // LD_hli_A;
    hl[0] = gPlayer.curDay;
    // LDH_A_addr(hHours);
    // LD_hli_A;
    hl[1] = hram.hHours;
    // LDH_A_addr(hMinutes);
    // LD_hli_A;
    hl[2] = hram.hMinutes;
    // LDH_A_addr(hSeconds);
    // LD_hli_A;
    hl[3] = hram.hSeconds;
    // RET;
}

void CopyDayToHL(uint8_t* hl){
    // LD_A_addr(wCurDay);
    // LD_hl_A;
    hl[0] = gPlayer.curDay;
    // RET;
}

void CopyDayHourToHL(uint8_t* hl){
//  //  unreferenced
    // LD_A_addr(wCurDay);
    // LD_hli_A;
    hl[0] = gPlayer.curDay;
    // LDH_A_addr(hHours);
    // LD_hli_A;
    hl[1] = hram.hHours;
    // RET;
}

void CopyDayHourMinToHL(uint8_t* hl){
    // LD_A_addr(wCurDay);
    // LD_hli_A;
    hl[0] = gPlayer.curDay;
    // LDH_A_addr(hHours);
    // LD_hli_A;
    hl[1] = hram.hHours;
    // LDH_A_addr(hMinutes);
    // LD_hli_A;
    hl[2] = hram.hMinutes;
    // RET;
}
