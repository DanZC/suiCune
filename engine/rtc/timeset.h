void InitClock(void);
// bool SetHour(void);
// uint8_t* DisplayHourOClock(uint8_t* hl);
void DisplayHoursMinutesWithMinString(void);
// bool SetMinutes(void);
// uint8_t* DisplayMinutesWithMinString(uint8_t* hl);
// uint8_t* PrintTwoDigitNumberLeftAlign(uint8_t* hl, uint8_t* de);
extern const txt_cmd_s OakTimeWokeUpText[];
extern const txt_cmd_s OakTimeWhatTimeIsItText[];
// void String_oclock(void);
extern const txt_cmd_s OakTimeWhatHoursText[];
extern const txt_cmd_s OakTimeHowManyMinutesText[];
// void String_min(void);
extern const txt_cmd_s OakTimeWhoaMinutesText[];
extern const txt_cmd_s OakText_ResponseToSetTime[];
// void TimeSetBackgroundGFX(void);
// void TimeSetUpArrowGFX(void);
// void TimeSetDownArrowGFX(void);
void SetDayOfWeek(void);
void InitialSetDSTFlag(void);
void InitialClearDSTFlag(void);
void MrChrono(void);
uint8_t* PrintHour(uint8_t* de, uint8_t c);
// const char* GetTimeOfDayString(uint8_t c);
// uint8_t AdjustHourForAMorPM(uint8_t c);
//#include "gfx/new_game/timeset_bg.1bpp"
//#include "gfx/new_game/up_arrow.1bpp"
//#include "gfx/new_game/down_arrow.1bpp"
