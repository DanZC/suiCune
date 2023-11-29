#pragma once

int CheckRTCSupport(void);
int UpdateRTC(void);
void SetStartTimeToSystemTime(void);
void LoadRTCStartTime(void);
void RTCSyncWithSystemTime(void);
void RTCInitTimeWithSystemTime(void);
uint8_t RTCGetCurrentWeekday(void);
