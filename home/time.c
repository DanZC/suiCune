#include "../constants.h"
#include "time.h"

//  Functions relating to the timer interrupt and the real-time-clock.

void Timer(void){
    //  //  unreferenced
    PUSH_AF;
    LDH_A_addr(hMobile);
    AND_A_A;
    IF_Z goto not_mobile;
    CALL(aMobileTimer);


not_mobile:
        POP_AF;
    RET;

}

void LatchClock(void){
    //  latch clock counter data
    LD_A(0);
    LD_addr_A(MBC3LatchClock);
    LD_A(1);
    LD_addr_A(MBC3LatchClock);
    RET;

}

void UpdateTime(void){
        CALL(aGetClock);
    CALL(aFixDays);
    CALL(aFixTime);
    FARCALL(aGetTimeOfDay);
    RET;

}

void GetClock(void){
    //  store clock data in hRTCDayHi-hRTCSeconds

//  enable clock r/w
    LD_A(SRAM_ENABLE);
    LD_addr_A(MBC3SRamEnable);

//  clock data is 'backwards' in hram

    CALL(aLatchClock);
    LD_HL(MBC3SRamBank);
    LD_DE(MBC3RTC);

    LD_hl(RTC_S);
    LD_A_de;
    maskbits(60, 0);
    LDH_addr_A(hRTCSeconds);

    LD_hl(RTC_M);
    LD_A_de;
    maskbits(60, 0);
    LDH_addr_A(hRTCMinutes);

    LD_hl(RTC_H);
    LD_A_de;
    maskbits(24, 0);
    LDH_addr_A(hRTCHours);

    LD_hl(RTC_DL);
    LD_A_de;
    LDH_addr_A(hRTCDayLo);

    LD_hl(RTC_DH);
    LD_A_de;
    LDH_addr_A(hRTCDayHi);

//  unlatch clock / disable clock r/w
    CALL(aCloseSRAM);
    RET;

}

void FixDays(void){
    //  fix day count
//  mod by 140

//  check if day count > 255 (bit 8 set)
    LDH_A_addr(hRTCDayHi);  // DH
    BIT_A(0);
    IF_Z goto daylo;
//  reset dh (bit 8)
    RES_A(0);
    LDH_addr_A(hRTCDayHi);

//  mod 140
//  mod twice since bit 8 (DH) was set
    LDH_A_addr(hRTCDayLo);

modh:
        SUB_A(140);
    IF_NC goto modh;

modl:
        SUB_A(140);
    IF_NC goto modl;
    ADD_A(140);

//  update dl
    LDH_addr_A(hRTCDayLo);

//  flag for sRTCStatusFlags
    LD_A(0b01000000);
    goto set;


daylo:
    //  quit if fewer than 140 days have passed
    LDH_A_addr(hRTCDayLo);
    CP_A(140);
    IF_C goto quit;

//  mod 140

mod:
        SUB_A(140);
    IF_NC goto mod;
    ADD_A(140);

//  update dl
    LDH_addr_A(hRTCDayLo);

//  flag for sRTCStatusFlags
    LD_A(0b00100000);


set:
    //  update clock with modded day value
    PUSH_AF;
    CALL(aSetClock);
    POP_AF;
    SCF;
    RET;


quit:
        XOR_A_A;
    RET;

}

void FixTime(void){
    //  add ingame time (set at newgame) to current time
//  store time in wCurDay, hHours, hMinutes, hSeconds

//  second
    LDH_A_addr(hRTCSeconds);
    LD_C_A;
    LD_A_addr(wStartSecond);
    ADD_A_C;
    SUB_A(60);
    IF_NC goto updatesec;
    ADD_A(60);

updatesec:
        LDH_addr_A(hSeconds);

//  minute
    CCF;  // carry is set, so turn it off
    LDH_A_addr(hRTCMinutes);
    LD_C_A;
    LD_A_addr(wStartMinute);
    ADC_A_C;
    SUB_A(60);
    IF_NC goto updatemin;
    ADD_A(60);

updatemin:
        LDH_addr_A(hMinutes);

//  hour
    CCF;  // carry is set, so turn it off
    LDH_A_addr(hRTCHours);
    LD_C_A;
    LD_A_addr(wStartHour);
    ADC_A_C;
    SUB_A(24);
    IF_NC goto updatehr;
    ADD_A(24);

updatehr:
        LDH_addr_A(hHours);

//  day
    CCF;  // carry is set, so turn it off
    LDH_A_addr(hRTCDayLo);
    LD_C_A;
    LD_A_addr(wStartDay);
    ADC_A_C;
    LD_addr_A(wCurDay);
    RET;

}

void InitTimeOfDay(void){
        XOR_A_A;
    LD_addr_A(wStringBuffer2);
    LD_A(0);  // useless
    LD_addr_A(wStringBuffer2 + 3);
    JR(mInitTime);

}

void InitDayOfWeek(void){
        CALL(aUpdateTime);
    LDH_A_addr(hHours);
    LD_addr_A(wStringBuffer2 + 1);
    LDH_A_addr(hMinutes);
    LD_addr_A(wStringBuffer2 + 2);
    LDH_A_addr(hSeconds);
    LD_addr_A(wStringBuffer2 + 3);
    JR(mInitTime);  // useless

}

void InitTime(void){
        FARCALL(av_InitTime);
    RET;

}

void ClearClock(void){
        CALL(aClearClock_ClearhRTC);
    CALL(aSetClock);
    RET;


ClearhRTC:
        XOR_A_A;
    LDH_addr_A(hRTCSeconds);
    LDH_addr_A(hRTCMinutes);
    LDH_addr_A(hRTCHours);
    LDH_addr_A(hRTCDayLo);
    LDH_addr_A(hRTCDayHi);
    RET;

}

void SetClock(void){
    //  set clock data from hram

//  enable clock r/w
    LD_A(SRAM_ENABLE);
    LD_addr_A(MBC3SRamEnable);

//  set clock data
//  stored 'backwards' in hram

    CALL(aLatchClock);
    LD_HL(MBC3SRamBank);
    LD_DE(MBC3RTC);

//  seems to be a halt check that got partially commented out
//  this block is totally pointless
    LD_hl(RTC_DH);
    LD_A_de;
    BIT_A(6);  // halt
    LD_de_A;

//  seconds
    LD_hl(RTC_S);
    LDH_A_addr(hRTCSeconds);
    LD_de_A;
//  minutes
    LD_hl(RTC_M);
    LDH_A_addr(hRTCMinutes);
    LD_de_A;
//  hours
    LD_hl(RTC_H);
    LDH_A_addr(hRTCHours);
    LD_de_A;
//  day lo
    LD_hl(RTC_DL);
    LDH_A_addr(hRTCDayLo);
    LD_de_A;
//  day hi
    LD_hl(RTC_DH);
    LDH_A_addr(hRTCDayHi);
    RES_A(6);  // make sure timer is active
    LD_de_A;

//  cleanup
    CALL(aCloseSRAM);  // unlatch clock, disable clock r/w
    RET;

}

void ClearRTCStatus(void){
    //  //  unreferenced
//  clear sRTCStatusFlags
    XOR_A_A;
    PUSH_AF;
    LD_A(BANK(sRTCStatusFlags));
    CALL(aOpenSRAM);
    POP_AF;
    LD_addr_A(sRTCStatusFlags);
    CALL(aCloseSRAM);
    RET;

}

void RecordRTCStatus(void){
    //  append flags to sRTCStatusFlags
    LD_HL(sRTCStatusFlags);
    PUSH_AF;
    LD_A(BANK(sRTCStatusFlags));
    CALL(aOpenSRAM);
    POP_AF;
    OR_A_hl;
    LD_hl_A;
    CALL(aCloseSRAM);
    RET;

}

void CheckRTCStatus(void){
    //  check sRTCStatusFlags
    LD_A(BANK(sRTCStatusFlags));
    CALL(aOpenSRAM);
    LD_A_addr(sRTCStatusFlags);
    CALL(aCloseSRAM);
    RET;

}
