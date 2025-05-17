#include "../../constants.h"
#include "rtc.h"
#include "../../home/time.h"
#include "../../home/sram.h"
#include "../../home/math.h"
#include "../overworld/time.h"
#include "../events/battle_tower/battle_tower.h"

void StopRTC(void){
//  //  unreferenced
    // LD_A(SRAM_ENABLE);
    // LD_addr_A(MBC3SRamEnable);
    gb_write(MBC3SRamEnable, SRAM_ENABLE);
    // CALL(aLatchClock);
    UpdateRTC();
    LatchClock();
    // LD_A(RTC_DH);
    // LD_addr_A(MBC3SRamBank);
    gb_write(MBC3SRamBank, RTC_DH);
    // LD_A_addr(MBC3RTC);
    // SET_A(6);  // halt
    // LD_addr_A(MBC3RTC);
    gb_write(MBC3RTC, gb_read(MBC3RTC) | (1 << 6));
    // CALL(aCloseSRAM);
    CloseSRAM();
    // RET;
}

void StartRTC(void){
    // LD_A(SRAM_ENABLE);
    // LD_addr_A(MBC3SRamEnable);
    gb_write(MBC3SRamEnable, SRAM_ENABLE);

    // CALL(aLatchClock);
    UpdateRTC();
    LatchClock();

    // LD_A(RTC_DH);
    // LD_addr_A(MBC3SRamBank);
    gb_write(MBC3SRamBank, RTC_DH);

    // LD_A_addr(MBC3RTC);
    // RES_A(6);  // halt
    // LD_addr_A(MBC3RTC);
    gb_write(MBC3RTC, gb_read(MBC3RTC) & ((0xFE << 6) | (0xFF >> (8 - 6))));

    // CALL(aCloseSRAM);
    CloseSRAM();
}

//  get time of day based on the current hour
void GetTimeOfDay(void){
    //  hours for the time of day
    //  0400-0959 morn | 1000-1759 day | 1800-0359 nite
    static const uint8_t TimesOfDay[][2] = {
        {MORN_HOUR, NITE_F},
        {DAY_HOUR, MORN_F},
        {NITE_HOUR, DAY_F},
        {MAX_HOUR, NITE_F},
        {0xff, MORN_F}
    };

    uint8_t hour = hram.hHours;  // hour
    // uint16_t hl = mTimesOfDay;
    uint8_t i = 0;

    do {
    //  if we're within the given time period,
    //  get the corresponding time of day
        if(hour < TimesOfDay[i][0]) break;
    //  else, get the next entry
        i++;
    //  try again
    } while(1);

//  get time of day
    // gb_write(wTimeOfDay, gb_read(++hl));
    wram->wTimeOfDay = TimesOfDay[i][1];
}

void StageRTCTimeForSave(void){
    UpdateTime();
    // LD_HL(wRTC);
    // LD_A_addr(wCurDay);
    // LD_hli_A;
    wram->wRTC[0] = wram->wCurDay;
    // LDH_A_addr(hHours);
    // LD_hli_A;
    wram->wRTC[1] = hram.hHours;
    // LDH_A_addr(hMinutes);
    // LD_hli_A;
    wram->wRTC[2] = hram.hMinutes;
    // LDH_A_addr(hSeconds);
    // LD_hli_A;
    wram->wRTC[3] = hram.hSeconds;
}

void SaveRTC(void){
    // LD_A(SRAM_ENABLE);
    // LD_addr_A(MBC3SRamEnable);
    gb_write(MBC3SRamEnable, SRAM_ENABLE);

    // CALL(aLatchClock);
    LatchClock();

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
    CloseSRAM();
}

void StartClock(void){
    // CALL(aGetClock);
    GetClock();

    // CALL(av_FixDays);
    uint8_t a = v_FixDays();

    // CALL(aFixDays);
    a |= FixDays(); 

    // IF_NC goto skip_set;
    if(a & 0xC0) {
    // bit 5: Day count exceeds 139
    // bit 6: Day count exceeds 255
        // CALL(aRecordRTCStatus);  // set flag on sRTCStatusFlags
        RecordRTCStatus(a);
    }

    // CALL(aStartRTC);
    // RET;
    StartRTC();
}

uint8_t v_FixDays(void){
    // LD_HL(hRTCDayHi);
    uint8_t hi = hram.hRTCDayHi;

    // BIT_hl(7);
    // IF_NZ goto set_bit_7;
    // BIT_hl(6);
    // IF_NZ goto set_bit_7;
    if(bit_test(hi, 7) || bit_test(hi, 6))
    {
        // Day count exceeds 16383
        // LD_A(0b10000000);
        // CALL(aRecordRTCStatus);  // set bit 7 on sRTCStatusFlags
        RecordRTCStatus(0b10000000);  // set bit 7 on sRTCStatusFlags
        return 0b10000000;
    }

    // XOR_A_A;
    // RET;
    return 0;
}

void ClockContinue(void){
    // CALL(aCheckRTCStatus);
    uint8_t stat = CheckRTCStatus();

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
        UpdateTime();

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
    OpenSRAM(MBANK(as5_aa8c));

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
    CloseSRAM();
}

void v_InitTime(uint8_t days, uint8_t hours, uint8_t mins, uint8_t secs){
    SetStartTimeToSystemTime();
    // CALL(aGetClock);
    GetClock();

    // CALL(aFixDays);
    FixDays();

    // LD_HL(hRTCSeconds);
    // LD_DE(wStartSecond);
    uint8_t carry = 0;

    // LD_A_addr(wStringBuffer2 + 3);
    // SUB_A_hl;
    // DEC_HL;
    wram->wStartSecond = SubCarry8(secs, hram.hRTCSeconds, carry, &carry);

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
    wram->wStartMinute = SubCarry8(mins, hram.hRTCMinutes, carry, &carry);

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
    wram->wStartHour = SubCarry8(hours, hram.hRTCHours, carry, &carry);

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
    wram->wStartDay = SubCarry8(days, hram.hRTCDayLo, carry, &carry);

    // IF_NC goto okay_days;
    if(carry)
    {
        // ADD_A(140);
        wram->wStartDay += 140;

        // LD_C(7);
        // CALL(aSimpleDivide);
        wram->wStartDay /= 7; // Only quotient is used. 
    }

    // LD_de_A;
}
