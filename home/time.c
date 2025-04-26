#include "../constants.h"
#include "time.h"
#include "sram.h"
#include "mobile.h"
#include "../engine/rtc/rtc.h"

//  Functions relating to the timer interrupt and the real-time-clock.

void Timer(void){
    // PUSH_AF;
    // LDH_A_addr(hMobile);
    // AND_A_A;
    // IF_Z goto not_mobile;
    if(hram->hMobile) {
        // CALL(aMobileTimer);
        MobileTimer();
    }

// not_mobile:
    // POP_AF;
    // RET;
}

//  latch clock counter data
void LatchClock(void){
    gb_write(MBC3LatchClock, 0);
    gb_write(MBC3LatchClock, 1);
}

void UpdateTime(void) {
    GetClock();
    FixDays();
    FixTime();
    GetTimeOfDay();
}

//  store clock data in hRTCDayHi-hRTCSeconds
void GetClock(void){
//  enable clock r/w
    gb_write(MBC3SRamEnable, SRAM_ENABLE);

//  clock data is 'backwards' in hram
    UpdateRTC();
    LatchClock();
    //LD_HL(MBC3SRamBank);
    //LD_DE(MBC3RTC);

    gb_write(MBC3SRamBank, RTC_S);
    // REG_A = gb_read(de);
    // maskbits(60, 0);
    hram->hRTCSeconds = gb_read(MBC3RTC) & 0x3f;

    gb_write(MBC3SRamBank, RTC_M);
    // REG_A = gb_read(de);
    // maskbits(60, 0);
    // gb_write(hRTCMinutes, REG_A);
    hram->hRTCMinutes = gb_read(MBC3RTC) & 0x3f;

    gb_write(MBC3SRamBank, RTC_H);
    // REG_A = gb_read(de);
    // maskbits(24, 0);
    // gb_write(hRTCHours, REG_A);
    hram->hRTCHours = gb_read(MBC3RTC) & 0x1f;

    gb_write(MBC3SRamBank, RTC_DL);
    // REG_A = gb_read(de);
    hram->hRTCDayLo = gb_read(MBC3RTC);

    gb_write(MBC3SRamBank, RTC_DH);
    // REG_A = gb_read(de);
    hram->hRTCDayHi = gb_read(MBC3RTC);

//  unlatch clock / disable clock r/w
    CloseSRAM();
}

//  fix day count
uint8_t FixDays(void){
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

        // uint8_t carry;
        // do {
        // modh:
            // SUB_A(140);
            // a = SubCarry8(a, 140, 0, &carry);
            // IF_NC goto modh;
        // } while(!carry);
        // do {
        // modl:
            // SUB_A(140);
            // IF_NC goto modl;
            // a = SubCarry8(a, 140, 0, &carry);
            // ADD_A(140);
        // } while(!carry);
        // a += 140;

    //  update dl
        // LDH_addr_A(hRTCDayLo);
        hram->hRTCDayLo = (a | 0x100) % 140;

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
        // mod:
            // SUB_A(140);
            // IF_NC goto mod;
        // ADD_A(140);

    //  update dl
        // LDH_addr_A(hRTCDayLo);
        hram->hRTCDayLo %= 140;

    //  flag for sRTCStatusFlags
        // LD_A(0b00100000);
        result = 0b00100000;
    }

// set:
    //  update clock with modded day value
    // PUSH_AF;
    // CALL(aSetClock);
    SetClock();
    // POP_AF;
    // SCF;
    // RET;
    return result;

// quit:
    // XOR_A_A;
    // RET;
}

//  add ingame time (set at newgame) to current time
//  store time in wCurDay, hHours, hMinutes, hSeconds
void FixTime(void){
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

void InitTimeOfDay(uint8_t hour, uint8_t min){
    // XOR_A_A;
    // LD_addr_A(wStringBuffer2);

    // LD_A(0);  // useless
    // LD_addr_A(wStringBuffer2 + 3);

    // JR(mInitTime);
    InitTime(0, hour, min, 0);
}

void InitDayOfWeek(uint8_t day){
    // CALL(aUpdateTime);
    UpdateTime();

    // LDH_A_addr(hHours);
    // LD_addr_A(wStringBuffer2 + 1);

    // LDH_A_addr(hMinutes);
    // LD_addr_A(wStringBuffer2 + 2);

    // LDH_A_addr(hSeconds);
    // LD_addr_A(wStringBuffer2 + 3);

    // JR(mInitTime);  // useless
    return InitTime(day, hram->hHours, hram->hMinutes, hram->hSeconds);
}

void InitTime(uint8_t days, uint8_t hours, uint8_t mins, uint8_t secs){
    // bank_push(BANK(av_InitTime));
    v_InitTime(days, hours, mins, secs);
    // bank_pop;
}

static void ClearClock_ClearhRTC() {
    hram->hRTCSeconds = 0;
    hram->hRTCMinutes = 0;
    hram->hRTCHours = 0;
    hram->hRTCDayLo = 0;
    hram->hRTCDayHi = 0;
}

void ClearClock(void){
    ClearClock_ClearhRTC();
    SetClock();
}

//  set clock data from hram
void SetClock(void){
//  enable clock r/w
    gb_write(MBC3SRamEnable, SRAM_ENABLE);

//  set clock data
//  stored 'backwards' in hram

    LatchClock();
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
    CloseSRAM();  // unlatch clock, disable clock r/w
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

//  append flags to sRTCStatusFlags
void RecordRTCStatus(uint8_t a){
    // LD_HL(sRTCStatusFlags);

    // PUSH_AF;
    // LD_A(BANK(sRTCStatusFlags));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asRTCStatusFlags));

    // POP_AF;
    // OR_A_hl;
    // LD_hl_A;
    gb_write(sRTCStatusFlags, gb_read(sRTCStatusFlags) | a);

    // CALL(aCloseSRAM);
    CloseSRAM();
}

//  check sRTCStatusFlags
uint8_t CheckRTCStatus(void){
    // LD_A(BANK(sRTCStatusFlags));
    // CALL(aOpenSRAM);
    OpenSRAM(MBANK(asRTCStatusFlags));

    // LD_A_addr(sRTCStatusFlags);
    uint8_t flags = gb_read(sRTCStatusFlags);
    
    // CALL(aCloseSRAM);
    CloseSRAM();

    // RET;
    return flags;
}
