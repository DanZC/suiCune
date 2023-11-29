#include "../constants.h"
#include "time.h"
#include "sram.h"
#include "../engine/rtc/rtc.h"

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

//  latch clock counter data
void LatchClock_Conv(void){
    gb_write(MBC3LatchClock, 0);
    gb_write(MBC3LatchClock, 1);
}

void UpdateTime(void){
        CALL(aGetClock);
    CALL(aFixDays);
    CALL(aFixTime);
    FARCALL(aGetTimeOfDay);
    RET;

}

void UpdateTime_Conv(void) {
    GetClock_Conv();
    FixDays_Conv();
    FixTime_Conv();
    GetTimeOfDay_Conv();
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

//  store clock data in hRTCDayHi-hRTCSeconds
void GetClock_Conv(void){
//  enable clock r/w
    gb_write(MBC3SRamEnable, SRAM_ENABLE);

//  clock data is 'backwards' in hram
    UpdateRTC();
    LatchClock_Conv();
    //LD_HL(MBC3SRamBank);
    //LD_DE(MBC3RTC);
    const uint16_t hl = MBC3SRamBank;
    const uint16_t de = MBC3RTC;

    gb_write(hl, RTC_S);
    REG_A = gb_read(de);
    maskbits(60, 0);
    gb_write(hRTCSeconds, REG_A);

    gb_write(hl, RTC_M);
    REG_A = gb_read(de);
    maskbits(60, 0);
    gb_write(hRTCMinutes, REG_A);

    gb_write(hl, RTC_H);
    REG_A = gb_read(de);
    maskbits(24, 0);
    gb_write(hRTCHours, REG_A);

    gb_write(hl, RTC_DL);
    REG_A = gb_read(de);
    gb_write(hRTCDayLo, REG_A);

    gb_write(hl, RTC_DH);
    REG_A = gb_read(de);
    gb_write(hRTCDayHi, REG_A);

//  unlatch clock / disable clock r/w
    CloseSRAM_Conv();
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

//  fix day count
uint8_t FixDays_Conv(void){
//  fix day count
//  mod by 140
    uint8_t result;
//  check if day count > 255 (bit 8 set)
    // LDH_A_addr(hRTCDayHi);  // DH
    // BIT_A(0);
    // IF_Z goto daylo;
    if(bit_test(hram->hRTCDayHi, 0)) {
    //  reset dh (bit 8)
        // RES_A(0);
        // LDH_addr_A(hRTCDayHi);
        bit_reset(hram->hRTCDayHi, 0);

    //  mod 140
    //  mod twice since bit 8 (DH) was set
        // LDH_A_addr(hRTCDayLo);
        uint8_t a = hram->hRTCDayLo;

        uint8_t carry;
        do {
        // modh:
            // SUB_A(140);
            a = SubCarry8(a, 140, 0, &carry);
            // IF_NC goto modh;
        } while(!carry);
        do {
        // modl:
            // SUB_A(140);
            // IF_NC goto modl;
            a = SubCarry8(a, 140, 0, &carry);
            // ADD_A(140);
        } while(!carry);
        a += 140;

    //  update dl
        // LDH_addr_A(hRTCDayLo);
        hram->hRTCDayLo = a;

    //  flag for sRTCStatusFlags
        // LD_A(0b01000000);
        // goto set;
        result = 0b01000000;
    }
    else {
    // daylo:
        //  quit if fewer than 140 days have passed
        // LDH_A_addr(hRTCDayLo);
        // CP_A(140);
        // IF_C goto quit;
        if(hram->hRTCDayLo < 140) {
            return 0;
        }

    //  mod 140
        uint8_t a = hram->hRTCDayLo;
        uint8_t carry;
        do {
        // mod:
            // SUB_A(140);
            a = SubCarry8(a, 140, 0, &carry);
            // IF_NC goto mod;
        } while(!carry);
        // ADD_A(140);
        a += 140;

    //  update dl
        // LDH_addr_A(hRTCDayLo);
        hram->hRTCDayLo = a;

    //  flag for sRTCStatusFlags
        // LD_A(0b00100000);
        result = 0b00100000;
    }

// set:
    //  update clock with modded day value
    // PUSH_AF;
    // CALL(aSetClock);
    SetClock_Conv();
    // POP_AF;
    // SCF;
    // RET;
    return result;

// quit:
    // XOR_A_A;
    // RET;
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

//  add ingame time (set at newgame) to current time
//  store time in wCurDay, hHours, hMinutes, hSeconds
void FixTime_Conv(void){
//  second
    uint8_t carry = 0;
    uint8_t curr_sec = hram->hRTCSeconds;
    uint8_t start_sec = wram->wStartSecond;
    uint8_t sec = curr_sec + start_sec;
    if(sec >= 60)
    {
        sec -= 60;
        carry = 1;
    }
    hram->hSeconds = sec;

//  minute
    // REG_F_C = 0;  // carry is set, so turn it off
    uint8_t curr_min = hram->hRTCMinutes;
    uint8_t start_min = wram->wStartMinute;
    uint8_t min = curr_min + start_min + carry;
    carry = 0;
    if(min >= 60)
    {
        min -= 60;
        carry = 1;
    }
    hram->hMinutes = min;

//  hour
    // REG_F_C = 0;  // carry is set, so turn it off
    uint8_t curr_hr = hram->hRTCHours;
    uint8_t start_hr = wram->wStartHour;
    uint8_t hr = curr_hr + start_hr + carry;
    carry = 0;
    if(hr >= 24)
    {
        hr -= 24;
        carry = 1;
    }
    hram->hHours = hr;

//  day
    // REG_F_C = 0;  // carry is set, so turn it off
    uint8_t curr_day = hram->hRTCDayLo;
    uint8_t start_day = wram->wStartDay;
    uint8_t day = curr_day + start_day + carry;
    wram->wCurDay = day;
}

void InitTimeOfDay(void){
        XOR_A_A;
    LD_addr_A(wStringBuffer2);
    LD_A(0);  // useless
    LD_addr_A(wStringBuffer2 + 3);
    JR(mInitTime);

}

void InitTimeOfDay_Conv(uint8_t hour, uint8_t min){
    // XOR_A_A;
    // LD_addr_A(wStringBuffer2);

    // LD_A(0);  // useless
    // LD_addr_A(wStringBuffer2 + 3);

    // JR(mInitTime);
    InitTime_Conv(0, hour, min, 0);
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

void InitDayOfWeek_Conv(uint8_t day){
    // CALL(aUpdateTime);
    UpdateTime_Conv();

    // LDH_A_addr(hHours);
    // LD_addr_A(wStringBuffer2 + 1);

    // LDH_A_addr(hMinutes);
    // LD_addr_A(wStringBuffer2 + 2);

    // LDH_A_addr(hSeconds);
    // LD_addr_A(wStringBuffer2 + 3);

    // JR(mInitTime);  // useless
    return InitTime_Conv(day, hram->hHours, hram->hMinutes, hram->hSeconds);
}

void InitTime(void){
        FARCALL(av_InitTime);
    RET;

}

void InitTime_Conv(uint8_t days, uint8_t hours, uint8_t mins, uint8_t secs){
    // bank_push(BANK(av_InitTime));
    v_InitTime_Conv(days, hours, mins, secs);
    // bank_pop;
}

static void ClearClock_ClearhRTC_Conv() {
    gb_write(hRTCSeconds, 0);
    gb_write(hRTCMinutes, 0);
    gb_write(hRTCHours, 0);
    gb_write(hRTCDayLo, 0);
    gb_write(hRTCDayHi, 0);
}

void ClearClock_Conv(void){
    ClearClock_ClearhRTC_Conv();
    SetClock_Conv();
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

//  set clock data from hram
void SetClock_Conv(void){
//  enable clock r/w
    gb_write(MBC3SRamEnable, SRAM_ENABLE);

//  set clock data
//  stored 'backwards' in hram

    LatchClock_Conv();
    const uint16_t hl = MBC3SRamBank;
    const uint16_t de = MBC3RTC;

//  seems to be a halt check that got partially commented out
//  this block is totally pointless
    // LD_hl(RTC_DH);
    // LD_A_de;
    // BIT_A(6);  // halt
    // LD_de_A;

//  seconds
    gb_write(hl, RTC_S);
    gb_write(de, hram->hRTCSeconds);
//  minutes
    gb_write(hl, RTC_M);
    gb_write(de, hram->hRTCMinutes);
//  hours
    gb_write(hl, RTC_H);
    gb_write(de, hram->hRTCHours);
//  day lo
    gb_write(hl, RTC_DL);
    gb_write(de, hram->hRTCDayLo);
//  day hi
    gb_write(hl, RTC_DH);
    uint8_t dayhi = hram->hRTCDayHi;
    bit_reset(dayhi, 6);  // make sure timer is active
    gb_write(de, dayhi);

//  cleanup
    CloseSRAM_Conv();  // unlatch clock, disable clock r/w
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
    LD_A(MBANK(asRTCStatusFlags));
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
    LD_A(MBANK(asRTCStatusFlags));
    CALL(aOpenSRAM);
    POP_AF;
    OR_A_hl;
    LD_hl_A;
    CALL(aCloseSRAM);
    RET;

}

//  append flags to sRTCStatusFlags
void RecordRTCStatus_Conv(uint8_t a){
    // LD_HL(sRTCStatusFlags);
    uint16_t hl = sRTCStatusFlags;

    // PUSH_AF;
    // LD_A(BANK(sRTCStatusFlags));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asRTCStatusFlags));

    // POP_AF;
    // OR_A_hl;
    // LD_hl_A;
    gb_write(hl, a | gb_read(hl));

    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
}

void CheckRTCStatus(void){
    //  check sRTCStatusFlags
    LD_A(MBANK(asRTCStatusFlags));
    CALL(aOpenSRAM);
    LD_A_addr(sRTCStatusFlags);
    CALL(aCloseSRAM);
    RET;

}

//  check sRTCStatusFlags
uint8_t CheckRTCStatus_Conv(void){
    // LD_A(BANK(sRTCStatusFlags));
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(asRTCStatusFlags));

    // LD_A_addr(sRTCStatusFlags);
    uint8_t flags = gb_read(sRTCStatusFlags);
    
    // CALL(aCloseSRAM);
    CloseSRAM_Conv();

    // RET;
    return flags;
}
