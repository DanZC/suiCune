void InitClock(void);
void SetHour(void);
bool SetHour_Conv(void);
void DisplayHourOClock(void);
uint8_t* DisplayHourOClock_Conv(uint8_t* hl);
void DisplayHoursMinutesWithMinString(void);
void SetMinutes(void);
bool SetMinutes_Conv(void);
void DisplayMinutesWithMinString(void);
uint8_t* DisplayMinutesWithMinString_Conv(uint8_t* hl);
void PrintTwoDigitNumberLeftAlign(void);
uint8_t* PrintTwoDigitNumberLeftAlign_Conv(uint8_t* hl, uint8_t* de);
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
void PrintHour(void);
uint8_t* PrintHour_Conv(uint8_t* de, uint8_t c);
void GetTimeOfDayString(void);
const char* GetTimeOfDayString_Conv(uint8_t c);
void AdjustHourForAMorPM(void);
uint8_t AdjustHourForAMorPM_Conv(uint8_t c);
//#include "gfx/new_game/timeset_bg.1bpp"
//#include "gfx/new_game/up_arrow.1bpp"
//#include "gfx/new_game/down_arrow.1bpp"
