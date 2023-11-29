#include "../constants.h"
#include "rtc.h"
#include <time.h>
#include <memory.h>
#include "../home/sram.h"

/*
    A better RTC system for suiCune.
    The game will pull from the system's RTC to gather time values.
    The start timestamp is used to keep track of the number of days that
    have passed since the adventure was started. This is because Pokemon
    Crystal does not keep track of dates, only the number of days
    that have passed since the RTC was last initialized.
    If the system does not have a RTC, the system will fallback to a 
    pseudo time-keeping system, which may involve the player setting the time
    at the beginning of each play session.
*/

time_t sLastTimestamp = 0;
time_t sStartTimestamp = 0;

static bool IsLeapYear(int year) {
    year += 1900;
    return (year % 400 == 0) || ((year % 100 != 0) && (year % 4 == 0));
}

static uint16_t CountDays(const struct tm* const begin, const struct tm* const end) {
    if(begin->tm_year == end->tm_year) {
        return end->tm_yday - begin->tm_yday;
    }
    else {
        int days = (IsLeapYear(begin->tm_year)? 366: 365) - begin->tm_yday;
        for(int i = begin->tm_year + 1; i < end->tm_year; ++i) {
            days += IsLeapYear(i)? 366: 365;
        }
        days += end->tm_yday;
        return (uint16_t)days;
    }
}


// On systems that do not have RTC support, time(NULL) will
// return -1.
// However, most systems with libc and SDL2 support have RTC support.
int CheckRTCSupport(void) {
    if(time(NULL) == (time_t)-1)
        return FALSE;
    return TRUE;
}

// Update the RTC if there is RTC support.
// Returns 0 if RTC is not supported.
// otherwise, updates the RTC timestamp.
int UpdateRTC(void) {
    time_t t = time(NULL);
    if(t == (time_t)-1)
        return FALSE;
    sLastTimestamp = t;

    struct tm lastTime = *localtime(&sLastTimestamp);
    gb.cart_rtc[2] = lastTime.tm_hour;
    gb.cart_rtc[1] = lastTime.tm_min;
    gb.cart_rtc[0] = lastTime.tm_sec;

    struct tm startTime = *localtime(&sStartTimestamp);
    uint16_t dayCount = CountDays(&startTime, &lastTime);
    gb.cart_rtc[4] &= 0xFE;
    gb.cart_rtc[4] |= (dayCount >> 8) & 1;
    gb.cart_rtc[3] = (dayCount & 0xff);
    return TRUE;
}

// The game will write the system timestamp to SRAM.
// This will be used on subsequent program runs to determine
// the start date for the current save file.
void SetStartTimeToSystemTime(void) {
    sStartTimestamp = time(NULL);

    uint64_t value = (uint64_t)sStartTimestamp;
    char buffer[8];
    buffer[0] = (value         & 0xff);
    buffer[1] = ((value >> 8ll)  & 0xff);
    buffer[2] = ((value >> 16ll) & 0xff);
    buffer[3] = ((value >> 24ll) & 0xff);
    buffer[4] = ((value >> 32ll) & 0xff);
    buffer[5] = ((value >> 40ll) & 0xff);
    buffer[6] = ((value >> 48ll) & 0xff);
    buffer[7] = ((value >> 56ll) & 0xff);
    gb_write(sPlayerData + (wRTC - wPlayerData) + 4, buffer[0]);
    gb_write(sPlayerData + (wRTC - wPlayerData) + 5, buffer[1]);
    gb_write(sPlayerData + (wRTC - wPlayerData) + 6, buffer[2]);
    gb_write(sPlayerData + (wRTC - wPlayerData) + 7, buffer[3]);
    memcpy(wram->skip_109, buffer + 4, 4);
    printf("start = %lld\n", *(time_t*)buffer);
}

void LoadRTCStartTime(void) {
    sStartTimestamp = 0;

    uint8_t buffer[8];
    memset(buffer, 0, sizeof(buffer));
    OpenSRAM_Conv(MBANK(asPlayerData));
    buffer[0] = gb_read(sPlayerData + (wRTC - wPlayerData) + 4);
    buffer[1] = gb_read(sPlayerData + (wRTC - wPlayerData) + 5);
    buffer[2] = gb_read(sPlayerData + (wRTC - wPlayerData) + 6);
    buffer[3] = gb_read(sPlayerData + (wRTC - wPlayerData) + 7);
    buffer[4] = gb_read(sPlayerData + (wTimeOfDayPal - wPlayerData) + 1);
    buffer[5] = gb_read(sPlayerData + (wTimeOfDayPal - wPlayerData) + 2);
    buffer[6] = gb_read(sPlayerData + (wTimeOfDayPal - wPlayerData) + 3);
    buffer[7] = gb_read(sPlayerData + (wTimeOfDayPal - wPlayerData) + 4);
    uint64_t value = buffer[0]
                    | ((uint64_t)(uint8_t)buffer[1] << 8ull)
                    | ((uint64_t)(uint8_t)buffer[2] << 16ull)
                    | ((uint64_t)(uint8_t)buffer[3] << 24ull)
                    | ((uint64_t)(uint8_t)buffer[4] << 32ull)
                    | ((uint64_t)(uint8_t)buffer[5] << 40ull)
                    | ((uint64_t)(uint8_t)buffer[6] << 48ull)
                    | ((uint64_t)(uint8_t)buffer[7] << 56ull);
    if(!(time_t)value) {
        SetStartTimeToSystemTime();
        printf("No RTC data found. Loading day at 0.\n");
        CloseSRAM_Conv();
        return;
    }
    sStartTimestamp = (time_t)value;
    printf("%lld\n", sStartTimestamp);
    CloseSRAM_Conv();
}

void RTCSyncWithSystemTime(void) {
    if(!UpdateRTC())
        return;

    struct tm* lastTime = localtime(&sLastTimestamp);
    wram->wCurDay = lastTime->tm_wday;
    if(lastTime->tm_isdst >= 0) {
        wram->wDST = ((lastTime->tm_isdst == 0)? 0: (1 << 7));
    }
}

void RTCInitTimeWithSystemTime(void) {
    if(!UpdateRTC())
        return;
    
    wram->wStartHour = 0;
    wram->wStartMinute = 0;
    wram->wStartSecond = 0;
    wram->wStartDay = 6 - ((gb.cart_rtc[3] | ((gb.cart_rtc[4] & 1) << 8)) % 7);

    struct tm* lastTime = localtime(&sLastTimestamp);
    wram->wCurDay = lastTime->tm_wday;
    if(lastTime->tm_isdst >= 0) {
        wram->wDST = ((lastTime->tm_isdst == 0)? 0: (1 << 7));
    }
}

uint8_t RTCGetCurrentWeekday(void) {
    struct tm* lastTime = localtime(&sLastTimestamp);
    return lastTime->tm_wday;
}
