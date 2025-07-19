#include "../constants.h"
#include "rtc.h"
#include "serialize.h"
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

    if(sStartTimestamp == 0) {
        SetStartTimeToSystemTime();
    }

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
    for(size_t i = 0; i < 4; ++i)
        gPlayer.skip_104[i] = buffer[i];
    for(size_t i = 0; i < 4; ++i)
        gPlayer.skip_109[i] = buffer[4 + i];
    printf("start = %lld\n", (long long)*(time_t*)buffer);
}

static char tempTimeBuffer[32];

void LoadRTCStartTime(void) {
    sStartTimestamp = 0;

    uint8_t buffer[8];
    memset(buffer, 0, sizeof(buffer));
    OpenSRAM(MBANK(asPlayerData));
    struct PlayerData pd;
    Deserialize_PlayerData(&pd, (const uint8_t *)GBToRAMAddr(sPlayerData));
    for(size_t i = 0; i < 4; ++i)
        buffer[i] = pd.skip_104[i];
    for(size_t i = 0; i < 4; ++i)
        buffer[4 + i] = pd.skip_109[i];
    uint64_t value = buffer[0]
                    | ((uint64_t)(uint8_t)buffer[1] << 8ull)
                    | ((uint64_t)(uint8_t)buffer[2] << 16ull)
                    | ((uint64_t)(uint8_t)buffer[3] << 24ull)
                    | ((uint64_t)(uint8_t)buffer[4] << 32ull)
                    | ((uint64_t)(uint8_t)buffer[5] << 40ull)
                    | ((uint64_t)(uint8_t)buffer[6] << 48ull)
                    | ((uint64_t)(uint8_t)buffer[7] << 56ull);
    if(!(time_t)value || (time_t)value == -1) {
        printf("No RTC data found. Start timestamp is %lld. Loading day at 0.\n", (long long)(time_t)value);
        CloseSRAM();
        sStartTimestamp = 0;
        return;
    }
    sStartTimestamp = (time_t)value;
    strftime(tempTimeBuffer, sizeof(tempTimeBuffer), "%a %Y-%m-%d %H:%M:%S", localtime(&sStartTimestamp));
    printf("Start timestamp is %lld (%s).\n", (long long)sStartTimestamp, tempTimeBuffer);
    sLastTimestamp = time(NULL);
    if(sLastTimestamp != (time_t)-1) {
        strftime(tempTimeBuffer, sizeof(tempTimeBuffer), "%a %Y-%m-%d %H:%M:%S", localtime(&sLastTimestamp));
        printf("Current timestamp is %lld (%s).\n", (long long)sLastTimestamp, tempTimeBuffer);
    }
    CloseSRAM();
}

void RTCSyncWithSystemTime(void) {
    if(!UpdateRTC())
        return;

    struct tm* lastTime = localtime(&sLastTimestamp);
    gPlayer.curDay = lastTime->tm_wday;
    if(lastTime->tm_isdst >= 0) {
        gPlayer.DST = ((lastTime->tm_isdst == 0)? 0: (1 << 7));
    }
}

void RTCInitTimeWithSystemTime(void) {
    if(!UpdateRTC())
        return;
    
    gPlayer.startHour = 0;
    gPlayer.startMinute = 0;
    gPlayer.startSecond = 0;
    gPlayer.startDay = 6 - ((gb.cart_rtc[3] | ((gb.cart_rtc[4] & 1) << 8)) % 7);

    struct tm* lastTime = localtime(&sLastTimestamp);
    gPlayer.curDay = lastTime->tm_wday;
    if(lastTime->tm_isdst >= 0) {
        gPlayer.DST = ((lastTime->tm_isdst == 0)? 0: (1 << 7));
    }
}

uint8_t RTCGetCurrentWeekday(void) {
    struct tm* lastTime = localtime(&sLastTimestamp);
    return lastTime->tm_wday;
}
