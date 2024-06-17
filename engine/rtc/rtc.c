#include "../../constants.h"
#include "rtc.h"
#include "../../home/time.h"
#include "../../home/sram.h"
#include "../../home/math.h"
#include "../overworld/time.h"
#include "../events/battle_tower/battle_tower.h"

void StopRTC(void){
//  //  unreferenced
    LD_A(SRAM_ENABLE);
    LD_addr_A(MBC3SRamEnable);
    CALL(aLatchClock);
    LD_A(RTC_DH);
    LD_addr_A(MBC3SRamBank);
    LD_A_addr(MBC3RTC);
    SET_A(6);  // halt
    LD_addr_A(MBC3RTC);
    CALL(aCloseSRAM);
    RET;

}

void StartRTC(void){
    LD_A(SRAM_ENABLE);
    LD_addr_A(MBC3SRamEnable);
    CALL(aLatchClock);
    LD_A(RTC_DH);
    LD_addr_A(MBC3SRamBank);
    LD_A_addr(MBC3RTC);
    RES_A(6);  // halt
    LD_addr_A(MBC3RTC);
    CALL(aCloseSRAM);
    RET;

}

void StartRTC_Conv(void){
    // LD_A(SRAM_ENABLE);
    // LD_addr_A(MBC3SRamEnable);
    gb_write(MBC3SRamEnable, SRAM_ENABLE);

    // CALL(aLatchClock);
    UpdateRTC();
    LatchClock_Conv();

    // LD_A(RTC_DH);
    // LD_addr_A(MBC3SRamBank);
    gb_write(MBC3SRamBank, RTC_DH);

    // LD_A_addr(MBC3RTC);
    // RES_A(6);  // halt
    // LD_addr_A(MBC3RTC);
    gb_write(MBC3RTC, gb_read(MBC3RTC) & ((0xFE << 6) | (0xFF >> (8 - 6))));

    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
}

void GetTimeOfDay(void){
//  get time of day based on the current hour
    LDH_A_addr(hHours);  // hour
    LD_HL(mTimesOfDay);


check:
//  if we're within the given time period,
//  get the corresponding time of day
    CP_A_hl;
    IF_C goto match;
//  else, get the next entry
    INC_HL;
    INC_HL;
//  try again
    goto check;


match:
//  get time of day
    INC_HL;
    LD_A_hl;
    LD_addr_A(wTimeOfDay);
    RET;

}

//  get time of day based on the current hour
void GetTimeOfDay_Conv(void){
    //  hours for the time of day
    //  0400-0959 morn | 1000-1759 day | 1800-0359 nite
    static const uint8_t TimesOfDay[][2] = {
        {MORN_HOUR, NITE_F},
        {DAY_HOUR, MORN_F},
        {NITE_HOUR, DAY_F},
        {MAX_HOUR, NITE_F},
        {0xff, MORN_F}
    };

    uint8_t hour = hram->hHours;  // hour
    // uint16_t hl = mTimesOfDay;
    uint8_t i = 0;

    do {
    //  if we're within the given time period,
    //  get the corresponding time of day
        // if(hour < gb_read(hl)) break;
        if(hour < TimesOfDay[i][0]) break;
    //  else, get the next entry
        // hl+=2;
        i++;
    //  try again
    } while(1);

//  get time of day
    // gb_write(wTimeOfDay, gb_read(++hl));
    wram->wTimeOfDay = TimesOfDay[i][1];
}

void TimesOfDay(void){
//  hours for the time of day
//  0400-0959 morn | 1000-1759 day | 1800-0359 nite
    //db ['MORN_HOUR', 'NITE_F'];
    //db ['DAY_HOUR', 'MORN_F'];
    //db ['NITE_HOUR', 'DAY_F'];
    //db ['MAX_HOUR', 'NITE_F'];
    //db ['-1', 'MORN_F'];

    return BetaTimesOfDay();
}

void BetaTimesOfDay(void){
//  //  unreferenced
    //db ['20', 'NITE_F'];
    //db ['40', 'MORN_F'];
    //db ['60', 'DAY_F'];
    //db ['-1', 'MORN_F'];

    return StageRTCTimeForSave();
}

void StageRTCTimeForSave(void){
    CALL(aUpdateTime);
    LD_HL(wRTC);
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

void StageRTCTimeForSave_Conv(void){
    UpdateTime_Conv();
    // LD_HL(wRTC);
    // LD_A_addr(wCurDay);
    // LD_hli_A;
    wram->wRTC[0] = wram->wCurDay;
    // LDH_A_addr(hHours);
    // LD_hli_A;
    wram->wRTC[1] = hram->hHours;
    // LDH_A_addr(hMinutes);
    // LD_hli_A;
    wram->wRTC[2] = hram->hMinutes;
    // LDH_A_addr(hSeconds);
    // LD_hli_A;
    wram->wRTC[3] = hram->hSeconds;
}

void SaveRTC(void){
    LD_A(SRAM_ENABLE);
    LD_addr_A(MBC3SRamEnable);
    CALL(aLatchClock);
    LD_HL(MBC3RTC);
    LD_A(RTC_DH);
    LD_addr_A(MBC3SRamBank);
    RES_hl(7);
    LD_A(MBANK(asRTCStatusFlags));
    LD_addr_A(MBC3SRamBank);
    XOR_A_A;
    LD_addr_A(sRTCStatusFlags);
    CALL(aCloseSRAM);
    RET;

}

void SaveRTC_Conv(void){
    // LD_A(SRAM_ENABLE);
    // LD_addr_A(MBC3SRamEnable);
    gb_write(MBC3SRamEnable, SRAM_ENABLE);

    // CALL(aLatchClock);
    LatchClock_Conv();

    // LD_HL(MBC3RTC);
    // LD_A(RTC_DH);
    // LD_addr_A(MBC3SRamBank);
    // RES_hl(7);
    gb_write(MBC3SRamBank, RTC_DH);
    gb_write(MBC3RTC, gb_read(MBC3RTC) & ~(1 << 7));

    // LD_A(BANK(sRTCStatusFlags));
    // LD_addr_A(MBC3SRamBank);
    gb_write(MBC3SRamBank, MBANK(asRTCStatusFlags));

    // XOR_A_A;
    // LD_addr_A(sRTCStatusFlags);
    gb_write(sRTCStatusFlags, 0);

    // CALL(aCloseSRAM);
    CloseSRAM_Conv();
}

void StartClock(void){
    CALL(aGetClock);
    CALL(av_FixDays);
    CALL(aFixDays);
    IF_NC goto skip_set;
// bit 5: Day count exceeds 139
// bit 6: Day count exceeds 255
    CALL(aRecordRTCStatus);  // set flag on sRTCStatusFlags


skip_set:
    CALL(aStartRTC);
    RET;

}

void StartClock_Conv(void){
    // CALL(aGetClock);
    GetClock_Conv();

    // CALL(av_FixDays);
    uint8_t a = v_FixDays_Conv();

    // CALL(aFixDays);
    a |= FixDays_Conv(); 

    // IF_NC goto skip_set;
    if(a & 0xC0) {
    // bit 5: Day count exceeds 139
    // bit 6: Day count exceeds 255
        // CALL(aRecordRTCStatus);  // set flag on sRTCStatusFlags
        RecordRTCStatus_Conv(a);
    }

    // CALL(aStartRTC);
    // RET;
    StartRTC_Conv();
}

void v_FixDays(void){
    LD_HL(hRTCDayHi);
    BIT_hl(7);
    IF_NZ goto set_bit_7;
    BIT_hl(6);
    IF_NZ goto set_bit_7;
    XOR_A_A;
    RET;


set_bit_7:
// Day count exceeds 16383
    LD_A(0b10000000);
    CALL(aRecordRTCStatus);  // set bit 7 on sRTCStatusFlags
    RET;

}

uint8_t v_FixDays_Conv(void){
    // LD_HL(hRTCDayHi);
    uint8_t hi = hram->hRTCDayHi;

    // BIT_hl(7);
    // IF_NZ goto set_bit_7;
    // BIT_hl(6);
    // IF_NZ goto set_bit_7;
    if(bit_test(hi, 7) || bit_test(hi, 6))
    {
        // Day count exceeds 16383
        // LD_A(0b10000000);
        // CALL(aRecordRTCStatus);  // set bit 7 on sRTCStatusFlags
        RecordRTCStatus_Conv(0b10000000);  // set bit 7 on sRTCStatusFlags
        return 0b10000000;
    }

    // XOR_A_A;
    // RET;
    return 0;
}

void ClockContinue(void){
    CALL(aCheckRTCStatus);
    LD_C_A;
    AND_A(0b11000000);  // Day count exceeded 255 or 16383
    IF_NZ goto time_overflow;

    LD_A_C;
    AND_A(0b00100000);  // Day count exceeded 139
    IF_Z goto dont_update;

    CALL(aUpdateTime);
    LD_A_addr(wRTC + 0);
    LD_B_A;
    LD_A_addr(wCurDay);
    CP_A_B;
    IF_C goto dont_update;


time_overflow:
    FARCALL(aClearDailyTimers);
    FARCALL(aFunction170923);
    LD_A(MBANK(as5_aa8c));  // aka BANK(s5_b2fa)
    CALL(aOpenSRAM);
    LD_A_addr(s5_aa8c);
    INC_A;
    LD_addr_A(s5_aa8c);
    LD_A_addr(s5_b2fa);
    INC_A;
    LD_addr_A(s5_b2fa);
    CALL(aCloseSRAM);
    RET;


dont_update:
    XOR_A_A;
    RET;

}

void ClockContinue_Conv(void){
    // CALL(aCheckRTCStatus);
    uint8_t stat = CheckRTCStatus_Conv();

    // LD_C_A;
    // AND_A(0b11000000);  // Day count exceeded 255 or 16383
    // IF_NZ goto time_overflow;
    if((stat & 0b11000000) == 0)
    {
        // LD_A_C;
        // AND_A(0b00100000);  // Day count exceeded 139
        // IF_Z goto dont_update;
        if(stat & 0b00100000)  // Day count exceeded 139
        {
            // XOR_A_A;
            // RET;
            return;
        }

        // CALL(aUpdateTime);
        UpdateTime_Conv();

        // LD_A_addr(wRTC + 0);
        // LD_B_A;
        // LD_A_addr(wCurDay);
        // CP_A_B;
        // IF_C goto dont_update;
        if(wram->wCurDay < wram->wRTC[0])
        {
            // XOR_A_A;
            // RET;
            return;
        }
    }

    // Day count exceeded 255 or 16383
    // FARCALL(aClearDailyTimers);
    ClearDailyTimers();
    // FARCALL(aFunction170923);
    Function170923();

    // LD_A(BANK(s5_aa8c));  // aka BANK(s5_b2fa)
    // CALL(aOpenSRAM);
    OpenSRAM_Conv(MBANK(as5_aa8c));

    // LD_A_addr(s5_aa8c);
    // INC_A;
    // LD_addr_A(s5_aa8c);
    gb_write(s5_aa8c, gb_read(s5_aa8c) + 1);

    // LD_A_addr(s5_b2fa);
    // INC_A;
    // LD_addr_A(s5_b2fa);
    gb_write(s5_b2fa, gb_read(s5_b2fa) + 1);

    // CALL(aCloseSRAM);
    // RET;
    CloseSRAM_Conv();
}

void v_InitTime(void){
    CALL(aGetClock);
    CALL(aFixDays);
    LD_HL(hRTCSeconds);
    LD_DE(wStartSecond);

    LD_A_addr(wStringBuffer2 + 3);
    SUB_A_hl;
    DEC_HL;
    IF_NC goto okay_secs;
    ADD_A(60);

okay_secs:
    LD_de_A;
    DEC_DE;

    LD_A_addr(wStringBuffer2 + 2);
    SBC_A_hl;
    DEC_HL;
    IF_NC goto okay_mins;
    ADD_A(60);

okay_mins:
    LD_de_A;
    DEC_DE;

    LD_A_addr(wStringBuffer2 + 1);
    SBC_A_hl;
    DEC_HL;
    IF_NC goto okay_hrs;
    ADD_A(24);

okay_hrs:
    LD_de_A;
    DEC_DE;

    LD_A_addr(wStringBuffer2);
    SBC_A_hl;
    DEC_HL;
    IF_NC goto okay_days;
    ADD_A(140);
    LD_C(7);
    CALL(aSimpleDivide);


okay_days:
    LD_de_A;
    RET;

}

void v_InitTime_Conv(uint8_t days, uint8_t hours, uint8_t mins, uint8_t secs){
    SetStartTimeToSystemTime();
    // CALL(aGetClock);
    GetClock_Conv();

    // CALL(aFixDays);
    FixDays_Conv();

    // LD_HL(hRTCSeconds);
    // LD_DE(wStartSecond);
    uint8_t carry = 0;

    // LD_A_addr(wStringBuffer2 + 3);
    // SUB_A_hl;
    // DEC_HL;
    wram->wStartSecond = SubCarry8(secs, hram->hRTCSeconds, carry, &carry);

    // IF_NC goto okay_secs;
    if(carry)
    {
        // ADD_A(60);
        wram->wStartSecond += 60;
    }

    // LD_de_A;
    // DEC_DE;

    // LD_A_addr(wStringBuffer2 + 2);
    // SBC_A_hl;
    // DEC_HL;
    wram->wStartMinute = SubCarry8(mins, hram->hRTCMinutes, carry, &carry);

    // IF_NC goto okay_mins;
    if(carry)
    {
        // ADD_A(60);
        wram->wStartMinute += 60;
    }

    // LD_de_A;
    // DEC_DE;

    // LD_A_addr(wStringBuffer2 + 1);

    // SBC_A_hl;
    // DEC_HL;
    wram->wStartHour = SubCarry8(hours, hram->hRTCHours, carry, &carry);

    // IF_NC goto okay_hrs;
    if(carry)
    {
        // ADD_A(24);
        wram->wStartHour += 24;
    }

    // LD_de_A;
    // DEC_DE;

    // LD_A_addr(wStringBuffer2);

    // SBC_A_hl;
    // DEC_HL;
    wram->wStartDay = SubCarry8(days, hram->hRTCDayLo, carry, &carry);

    // IF_NC goto okay_days;
    if(carry)
    {
        // ADD_A(140);
        wram->wStartDay += 140;

        // LD_C(7);
        // CALL(aSimpleDivide);
        // towrite = SimpleDivide_Conv(towrite, 7).quot;
        wram->wStartDay /= 7; // Only quotient is used. 
    }

    // LD_de_A;
}
