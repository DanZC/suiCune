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
    wram->wLuckyNumberDayTimer = 0;
    // LD_addr_A(wUnusedTwoDayTimer);
    wram->wUnusedTwoDayTimer = 0;
    // LD_addr_A(wDailyResetTimer);
    wram->wDailyResetTimer = 0;
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
    OpenSRAM_Conv(MBANK(asDebugTimeCyclesSinceLastCall));
    // LD_A_addr(sDebugTimeCyclesSinceLastCall);
    uint8_t a2 = gb_read(sDebugTimeCyclesSinceLastCall);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
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
    RestartReceiveCallDelay_Conv(a);
}

void CheckReceiveCallTimer(void){
    CALL(aCheckReceiveCallDelay);  // check timer
    RET_NC ;
    LD_HL(wTimeCyclesSinceLastCall);
    LD_A_hl;
    CP_A(3);
    IF_NC goto ok;
    INC_hl;


ok:
    CALL(aNextCallReceiveDelay);  // restart timer
    SCF;
    RET;

}

bool CheckReceiveCallTimer_Conv(void){
    // CALL(aCheckReceiveCallDelay);  // check timer
    // RET_NC ;
    if(!CheckReceiveCallDelay_Conv())
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

void InitOneDayCountdown(void){
    LD_A(1);

    return InitNDaysCountdown();
}

void InitOneDayCountdown_Conv(uint8_t* hl){
    // LD_A(1);
    return InitNDaysCountdown_Conv(hl, 1);
}

void InitNDaysCountdown(void){
    LD_hl_A;
    PUSH_HL;
    CALL(aUpdateTime);
    POP_HL;
    INC_HL;
    CALL(aCopyDayToHL);
    RET;

}

void InitNDaysCountdown_Conv(uint8_t* hl, uint8_t n){
    // LD_hl_A;
    hl[0] = n;
    // PUSH_HL;
    // CALL(aUpdateTime);
    UpdateTime_Conv();
    // POP_HL;
    // INC_HL;
    // CALL(aCopyDayToHL);
    hl[1] = wram->wCurDay;
    // RET;
}

void CheckDayDependentEventHL(void){
    INC_HL;
    PUSH_HL;
    CALL(aCalcDaysSince);
    CALL(aGetDaysSince);
    POP_HL;
    DEC_HL;
    CALL(aUpdateTimeRemaining);
    RET;

}

bool CheckDayDependentEventHL_Conv(uint8_t* hl){
    // INC_HL;
    // PUSH_HL;
    // CALL(aCalcDaysSince);
    CalcDaysSince_Conv(hl + 1);
    // CALL(aGetDaysSince);
    uint8_t days = GetDaysSince_Conv();
    // POP_HL;
    // DEC_HL;
    // CALL(aUpdateTimeRemaining);
    return UpdateTimeRemaining_Conv(hl, days);
    // RET;
}

void RestartReceiveCallDelay(void){
    LD_HL(wReceiveCallDelay_MinsRemaining);
    LD_hl_A;
    CALL(aUpdateTime);
    LD_HL(wReceiveCallDelay_StartTime);
    CALL(aCopyDayHourMinToHL);
    RET;

}

void RestartReceiveCallDelay_Conv(uint8_t a){
    // LD_HL(wReceiveCallDelay_MinsRemaining);
    // LD_hl_A;
    wram->wReceiveCallDelay_MinsRemaining = a;
    // CALL(aUpdateTime);
    UpdateTime_Conv();
    // LD_HL(wReceiveCallDelay_StartTime);
    // CALL(aCopyDayHourMinToHL);
    CopyDayHourMinToHL_Conv(wram->wReceiveCallDelay_StartTime);
    // RET;
}

void CheckReceiveCallDelay(void){
    LD_HL(wReceiveCallDelay_StartTime);
    CALL(aCalcMinsHoursDaysSince);
    CALL(aGetMinutesSinceIfLessThan60);
    LD_HL(wReceiveCallDelay_MinsRemaining);
    CALL(aUpdateTimeRemaining);
    RET;

}

bool CheckReceiveCallDelay_Conv(void){
    // LD_HL(wReceiveCallDelay_StartTime);
    // CALL(aCalcMinsHoursDaysSince);
    CalcMinsHoursDaysSince_Conv(wram->wReceiveCallDelay_StartTime);
    // CALL(aGetMinutesSinceIfLessThan60);
    uint8_t mins = GetMinutesSinceIfLessThan60_Conv();
    // LD_HL(wReceiveCallDelay_MinsRemaining);
    // CALL(aUpdateTimeRemaining);
    return UpdateTimeRemaining_Conv(&wram->wReceiveCallDelay_MinsRemaining, mins);
    // RET;
}

void RestartDailyResetTimer(void){
    LD_HL(wDailyResetTimer);
    JP(mInitOneDayCountdown);

}

void RestartDailyResetTimer_Conv(void){
    // LD_HL(wDailyResetTimer);
    // JP(mInitOneDayCountdown);
    return InitOneDayCountdown_Conv((uint8_t*)&wram->wDailyResetTimer);
}

void CheckDailyResetTimer(void){
    LD_HL(wDailyResetTimer);
    CALL(aCheckDayDependentEventHL);
    RET_NC ;
    XOR_A_A;
    LD_HL(wDailyFlags1);
    LD_hli_A;  // wDailyFlags1
    LD_hli_A;  // wDailyFlags2
    LD_hli_A;  // wSwarmFlags
    LD_hl_A;  // wSwarmFlags + 1
    LD_HL(wDailyRematchFlags);
    for(int rept = 0; rept < 4; rept++){
    LD_hli_A;
    }
    LD_HL(wDailyPhoneItemFlags);
    for(int rept = 0; rept < 4; rept++){
    LD_hli_A;
    }
    LD_HL(wDailyPhoneTimeOfDayFlags);
    for(int rept = 0; rept < 4; rept++){
    LD_hli_A;
    }
    LD_HL(wKenjiBreakTimer);
    LD_A_hl;
    AND_A_A;
    IF_Z goto RestartKenjiBreakCountdown;
    DEC_hl;
    IF_NZ goto DontRestartKenjiBreakCountdown;

RestartKenjiBreakCountdown:
    CALL(aSampleKenjiBreakCountdown);

DontRestartKenjiBreakCountdown:
    JR(mRestartDailyResetTimer);

}

void CheckDailyResetTimer_Conv(void){
    // LD_HL(wDailyResetTimer);
    // CALL(aCheckDayDependentEventHL);
    // RET_NC ;
    if(!CheckDayDependentEventHL_Conv((uint8_t*)&wram->wDailyResetTimer))
        return;
    
    // XOR_A_A;
    // LD_HL(wDailyFlags1);
    // LD_hli_A;  // wDailyFlags1
    wram->wDailyFlags1 = 0;
    // LD_hli_A;  // wDailyFlags2
    wram->wDailyFlags2 = 0;
    // LD_hli_A;  // wSwarmFlags
    wram->wSwarmFlags = 0;
    // LD_hl_A;  // wSwarmFlags + 1
    wram->skip_121[0] = 0;
    // LD_HL(wDailyRematchFlags);
    // for(int rept = 0; rept < 4; rept++){
    // LD_hli_A;
    // }
    for(uint32_t i = 0; i < lengthof(wram->wDailyRematchFlags); ++i)
        wram->wDailyRematchFlags[i] = 0;
    // LD_HL(wDailyPhoneItemFlags);
    // for(int rept = 0; rept < 4; rept++){
    // LD_hli_A;
    // }
    for(uint32_t i = 0; i < lengthof(wram->wDailyPhoneItemFlags); ++i)
        wram->wDailyPhoneItemFlags[i] = 0;
    // LD_HL(wDailyPhoneTimeOfDayFlags);
    // for(int rept = 0; rept < 4; rept++){
    // LD_hli_A;
    // }
    for(uint32_t i = 0; i < lengthof(wram->wDailyPhoneTimeOfDayFlags); ++i)
        wram->wDailyPhoneTimeOfDayFlags[i] = 0;
    // LD_HL(wKenjiBreakTimer);
    // LD_A_hl;
    // AND_A_A;
    // IF_Z goto RestartKenjiBreakCountdown;
    if(wram->wKenjiBreakTimer[0] == 0) {
        SampleKenjiBreakCountdown_Conv();
    }
    // DEC_hl;
    // IF_NZ goto DontRestartKenjiBreakCountdown;
    else if(--wram->wKenjiBreakTimer[0] == 0) {
        SampleKenjiBreakCountdown_Conv();
    }
// RestartKenjiBreakCountdown:
    // CALL(aSampleKenjiBreakCountdown);

// DontRestartKenjiBreakCountdown:
    // JR(mRestartDailyResetTimer);
    return RestartDailyResetTimer_Conv();
}

void SampleKenjiBreakCountdown(void){
//  Generate a random number between 3 and 6
    CALL(aRandom);
    AND_A(0b11);
    ADD_A(3);
    LD_addr_A(wKenjiBreakTimer);
    RET;

}

//  Generate a random number between 3 and 6
void SampleKenjiBreakCountdown_Conv(void){
    // CALL(aRandom);
    // AND_A(0b11);
    // ADD_A(3);
    // LD_addr_A(wKenjiBreakTimer);
    // RET;
    wram->wKenjiBreakTimer[0] = (Random() & 0b11) + 3;
}

void StartBugContestTimer(void){
    LD_A(BUG_CONTEST_MINUTES);
    LD_addr_A(wBugContestMinsRemaining);
    LD_A(BUG_CONTEST_SECONDS);
    LD_addr_A(wBugContestSecsRemaining);
    CALL(aUpdateTime);
    LD_HL(wBugContestStartTime);
    CALL(aCopyDayHourMinSecToHL);
    RET;

}

void StartBugContestTimer_Conv(void){
    // LD_A(BUG_CONTEST_MINUTES);
    // LD_addr_A(wBugContestMinsRemaining);
    wram->wBugContestMinsRemaining = BUG_CONTEST_MINUTES;
    // LD_A(BUG_CONTEST_SECONDS);
    // LD_addr_A(wBugContestSecsRemaining);
    wram->wBugContestSecsRemaining = BUG_CONTEST_SECONDS;
    // CALL(aUpdateTime);
    UpdateTime_Conv();
    // LD_HL(wBugContestStartTime);
    // CALL(aCopyDayHourMinSecToHL);
    CopyDayHourMinSecToHL_Conv(wram->wBugContestStartTime);
    // RET;
}

void CheckBugContestTimer(void){
    LD_HL(wBugContestStartTime);
    CALL(aCalcSecsMinsHoursDaysSince);
    LD_A_addr(wDaysSince);
    AND_A_A;
    IF_NZ goto timed_out;
    LD_A_addr(wHoursSince);
    AND_A_A;
    IF_NZ goto timed_out;
    LD_A_addr(wSecondsSince);
    LD_B_A;
    LD_A_addr(wBugContestSecsRemaining);
    SUB_A_B;
    IF_NC goto okay;
    ADD_A(60);


okay:
    LD_addr_A(wBugContestSecsRemaining);
    LD_A_addr(wMinutesSince);
    LD_B_A;
    LD_A_addr(wBugContestMinsRemaining);
    SBC_A_B;
    LD_addr_A(wBugContestMinsRemaining);
    IF_C goto timed_out;
    AND_A_A;
    RET;


timed_out:
    XOR_A_A;
    LD_addr_A(wBugContestMinsRemaining);
    LD_addr_A(wBugContestSecsRemaining);
    SCF;
    RET;

}

bool CheckBugContestTimer_Conv(void){
    // LD_HL(wBugContestStartTime);
    // CALL(aCalcSecsMinsHoursDaysSince);
    CalcSecsMinsHoursDaysSince_Conv(wram->wBugContestStartTime);
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
    UpdateTime_Conv();
    // LD_HL(wTimerEventStartDay);
    // CALL(aCopyDayToHL);
    CopyDayToHL_Conv(&wram->wTimerEventStartDay);
    // RET;
}

void CheckPokerusTick(void){
    LD_HL(wTimerEventStartDay);
    CALL(aCalcDaysSince);
    CALL(aGetDaysSince);
    AND_A_A;
    IF_Z goto done;  // not even a day has passed since game start
    LD_B_A;
    FARCALL(aApplyPokerusTick);

done:
    XOR_A_A;
    RET;

}

void CheckPokerusTick_Conv(void){
    // LD_HL(wTimerEventStartDay);
    // CALL(aCalcDaysSince);
    CalcDaysSince_Conv(&wram->wTimerEventStartDay);
    // CALL(aGetDaysSince);
    uint8_t days = GetDaysSince_Conv();
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
    return InitNDaysCountdown_Conv((uint8_t*)&wram->wLuckyNumberDayTimer, n);
}

void v_CheckLuckyNumberShowFlag(void){
    LD_HL(wLuckyNumberDayTimer);
    JP(mCheckDayDependentEventHL);

}

bool v_CheckLuckyNumberShowFlag_Conv(void){
    // LD_HL(wLuckyNumberDayTimer);
    // JP(mCheckDayDependentEventHL);
    return CheckDayDependentEventHL_Conv((uint8_t*)&wram->wLuckyNumberDayTimer);
}

void DoMysteryGiftIfDayHasPassed(void){
    // LD_A(BANK(sMysteryGiftTimer));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMysteryGiftTimer));
    // LD_HL(sMysteryGiftTimer);
    // LD_A_hli;
    // LD_addr_A(wTempMysteryGiftTimer);
    // LD_A_hl;
    // LD_addr_A(wTempMysteryGiftTimer + 1);
    wram->wTempMysteryGiftTimer = gb_read16(sMysteryGiftTimer);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();

    // LD_HL(wTempMysteryGiftTimer);
    // CALL(aCheckDayDependentEventHL);
    // IF_NC goto not_timed_out;
    if(CheckDayDependentEventHL_Conv((uint8_t*)&wram->wTempMysteryGiftTimer)) {
        // LD_HL(wTempMysteryGiftTimer);
        // CALL(aInitOneDayCountdown);
        InitOneDayCountdown_Conv((uint8_t*)&wram->wTempMysteryGiftTimer);
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
        // FARCALL(aResetDailyMysteryGiftLimitIfUnlocked);
        ResetDailyMysteryGiftLimitIfUnlocked();
    }

// not_timed_out:
    // LD_A(BANK(sMysteryGiftTimer));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asMysteryGiftTimer));
    // LD_HL(wTempMysteryGiftTimer);
    // LD_A_hli;
    // LD_addr_A(sMysteryGiftTimer);
    // LD_A_hl;
    // LD_addr_A(sMysteryGiftTimer + 1);
    gb_write(sMysteryGiftTimer, wram->wTempMysteryGiftTimer);
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
    // RET;
}

void UpdateTimeRemaining(void){
//  If the amount of time elapsed exceeds the capacity of its
//  unit, skip this part.
    CP_A(-1);
    IF_Z goto set_carry;
    LD_C_A;
    LD_A_hl;  // time remaining
    SUB_A_C;
    IF_NC goto ok;
    XOR_A_A;


ok:
    LD_hl_A;
    IF_Z goto set_carry;
    XOR_A_A;
    RET;


set_carry:
    XOR_A_A;
    LD_hl_A;
    SCF;
    RET;

}

//  If the amount of time elapsed exceeds the capacity of its
//  unit, skip this part.
bool UpdateTimeRemaining_Conv(uint8_t* hl, uint8_t a){
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

void GetMinutesSinceIfLessThan60(void){
    LD_A_addr(wDaysSince);
    AND_A_A;
    JR_NZ (mGetTimeElapsed_ExceedsUnitLimit);
    LD_A_addr(wHoursSince);
    AND_A_A;
    JR_NZ (mGetTimeElapsed_ExceedsUnitLimit);
    LD_A_addr(wMinutesSince);
    RET;

}

uint8_t GetMinutesSinceIfLessThan60_Conv(void){
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

void GetDaysSince(void){
    LD_A_addr(wDaysSince);
    RET;

}

uint8_t GetDaysSince_Conv(void){
    // LD_A_addr(wDaysSince);
    // RET;
    return wram->wDaysSince;
}

void GetTimeElapsed_ExceedsUnitLimit(void){
    LD_A(-1);
    RET;

}

void CalcDaysSince(void){
    XOR_A_A;
    JR(mv_CalcDaysSince);

}

void CalcDaysSince_Conv(uint8_t* hl){
    // XOR_A_A;
    // JR(mv_CalcDaysSince);
    return v_CalcDaysSince_Conv(hl, 0);
}

void CalcHoursDaysSince(void){
//  //  unreferenced
    INC_HL;
    XOR_A_A;
    JR(mv_CalcHoursDaysSince);

}

void CalcMinsHoursDaysSince(void){
    INC_HL;
    INC_HL;
    XOR_A_A;
    JR(mv_CalcMinsHoursDaysSince);

}

void CalcMinsHoursDaysSince_Conv(uint8_t* hl){
    // INC_HL;
    // INC_HL;
    // XOR_A_A;
    // JR(mv_CalcMinsHoursDaysSince);
    return v_CalcMinsHoursDaysSince_Conv(hl + 2, 0);
}

void CalcSecsMinsHoursDaysSince(void){
    INC_HL;
    INC_HL;
    INC_HL;
    LDH_A_addr(hSeconds);
    LD_C_A;
    SUB_A_hl;
    IF_NC goto skip;
    ADD_A(60);

skip:
    LD_hl_C;  // current seconds
    DEC_HL;
    LD_addr_A(wSecondsSince);  // seconds since

    return v_CalcMinsHoursDaysSince();
}

void CalcSecsMinsHoursDaysSince_Conv(uint8_t* hl){
    // INC_HL;
    // INC_HL;
    // INC_HL;
    hl += 3;
    // LDH_A_addr(hSeconds);
    // LD_C_A;
    // SUB_A_hl;
    uint16_t temp = hram->hSeconds - *hl;
    uint8_t a = (temp & 0xff);
    uint8_t carry = (temp & 0xff00)? 1: 0;
    // IF_NC goto skip;
    // ADD_A(60);
    if(carry) {
        a += 60;
    }

// skip:
    // LD_hl_C;  // current seconds
    *hl = hram->hSeconds;
    // DEC_HL;
    hl--;
    // LD_addr_A(wSecondsSince);  // seconds since
    wram->wSecondsSince = a;

    return v_CalcMinsHoursDaysSince_Conv(hl, carry);
}

void v_CalcMinsHoursDaysSince(void){
    LDH_A_addr(hMinutes);
    LD_C_A;
    SBC_A_hl;
    IF_NC goto skip;
    ADD_A(60);

skip:
    LD_hl_C;  // current minutes
    DEC_HL;
    LD_addr_A(wMinutesSince);  // minutes since

    return v_CalcHoursDaysSince();
}

void v_CalcMinsHoursDaysSince_Conv(uint8_t* hl, uint8_t carry){
    // LDH_A_addr(hMinutes);
    // LD_C_A;
    // SBC_A_hl;
    uint16_t temp = hram->hMinutes - *hl - carry;
    uint8_t a = (temp & 0xff);
    carry = (temp & 0xff00)? 1: 0;
    // IF_NC goto skip;
    // ADD_A(60);
    if(carry) {
        a += 60;
    }

// skip:
    // LD_hl_C;  // current minutes
    *hl = hram->hMinutes;
    // DEC_HL;
    --hl;
    // LD_addr_A(wMinutesSince);  // minutes since
    wram->wMinutesSince = a;

    return v_CalcHoursDaysSince_Conv(hl, carry);
}

void v_CalcHoursDaysSince(void){
    LDH_A_addr(hHours);
    LD_C_A;
    SBC_A_hl;
    IF_NC goto skip;
    ADD_A(MAX_HOUR);

skip:
    LD_hl_C;  // current hours
    DEC_HL;
    LD_addr_A(wHoursSince);  // hours since

    return v_CalcDaysSince();
}

void v_CalcHoursDaysSince_Conv(uint8_t* hl, uint8_t carry){
    // LDH_A_addr(hHours);
    // LD_C_A;
    // SBC_A_hl;
    uint16_t temp = hram->hHours - *hl - carry;
    uint8_t a = (temp & 0xff);
    carry = (temp & 0xff00)? 1: 0;
    // IF_NC goto skip;
    // ADD_A(MAX_HOUR);
    if(carry) {
        a += MAX_HOUR;
    }

// skip:
    // LD_hl_C;  // current hours
    *hl = hram->hHours;
    // DEC_HL;
    hl--;
    // LD_addr_A(wHoursSince);  // hours since
    wram->wHoursSince = a;

    return v_CalcDaysSince_Conv(hl, carry);
}

void v_CalcDaysSince(void){
    LD_A_addr(wCurDay);
    LD_C_A;
    SBC_A_hl;
    IF_NC goto skip;
    ADD_A(20 * 7);

skip:
    LD_hl_C;  // current days
    LD_addr_A(wDaysSince);  // days since
    RET;

}

void v_CalcDaysSince_Conv(uint8_t* hl, uint8_t carry){
    // LD_A_addr(wCurDay);
    // LD_C_A;
    // SBC_A_hl;
    uint16_t temp = wram->wCurDay - *hl - carry;
    uint8_t a = (temp & 0xff);
    carry = (temp & 0xff00)? 1: 0;
    // IF_NC goto skip;
    // ADD_A(20 * 7);
    if(carry) {
        a += (20 * 7);
    }

// skip:
    // LD_hl_C;  // current days
    *hl = wram->wCurDay;
    // LD_addr_A(wDaysSince);  // days since
    wram->wDaysSince = a;
    // RET;
}

void CopyDayHourMinSecToHL(void){
    LD_A_addr(wCurDay);
    LD_hli_A;
    LDH_A_addr(hHours);
    LD_hli_A;
    LDH_A_addr(hMinutes);
    LD_hli_A;
    LDH_A_addr(hSeconds);
    LD_hli_A;
    RET;

}

void CopyDayHourMinSecToHL_Conv(uint8_t* hl){
    // LD_A_addr(wCurDay);
    // LD_hli_A;
    hl[0] = wram->wCurDay;
    // LDH_A_addr(hHours);
    // LD_hli_A;
    hl[1] = hram->hHours;
    // LDH_A_addr(hMinutes);
    // LD_hli_A;
    hl[2] = hram->hMinutes;
    // LDH_A_addr(hSeconds);
    // LD_hli_A;
    hl[3] = hram->hSeconds;
    // RET;
}

void CopyDayToHL(void){
    LD_A_addr(wCurDay);
    LD_hl_A;
    RET;

}

void CopyDayToHL_Conv(uint8_t* hl){
    // LD_A_addr(wCurDay);
    // LD_hl_A;
    hl[0] = wram->wCurDay;
    // RET;
}

void CopyDayHourToHL(void){
//  //  unreferenced
    LD_A_addr(wCurDay);
    LD_hli_A;
    LDH_A_addr(hHours);
    LD_hli_A;
    RET;

}

void CopyDayHourMinToHL(void){
    LD_A_addr(wCurDay);
    LD_hli_A;
    LDH_A_addr(hHours);
    LD_hli_A;
    LDH_A_addr(hMinutes);
    LD_hli_A;
    RET;

}

void CopyDayHourMinToHL_Conv(uint8_t* hl){
    // LD_A_addr(wCurDay);
    // LD_hli_A;
    hl[0] = wram->wCurDay;
    // LDH_A_addr(hHours);
    // LD_hli_A;
    hl[1] = hram->hHours;
    // LDH_A_addr(hMinutes);
    // LD_hli_A;
    hl[2] = hram->hMinutes;
    // RET;
}
