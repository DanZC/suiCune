void v_InitializeStartDay(void);
void ClearDailyTimers(void);
void InitCallReceiveDelay(void);
void NextCallReceiveDelay(void);
void CheckReceiveCallTimer(void);
bool CheckReceiveCallTimer_Conv(void);
void InitOneDayCountdown(void);
void InitOneDayCountdown_Conv(uint8_t* hl);
void InitNDaysCountdown(void);
void InitNDaysCountdown_Conv(uint8_t* hl, uint8_t n);
void CheckDayDependentEventHL(void);
bool CheckDayDependentEventHL_Conv(uint8_t* hl);
void RestartReceiveCallDelay(void);
void RestartReceiveCallDelay_Conv(uint8_t a);
void CheckReceiveCallDelay(void);
bool CheckReceiveCallDelay_Conv(void);
void RestartDailyResetTimer(void);
void RestartDailyResetTimer_Conv(void);
void CheckDailyResetTimer(void);
void CheckDailyResetTimer_Conv(void);
void SampleKenjiBreakCountdown(void);
void SampleKenjiBreakCountdown_Conv(void);
void StartBugContestTimer(void);
void StartBugContestTimer_Conv(void);
void CheckBugContestTimer(void);
bool CheckBugContestTimer_Conv(void);
void InitializeStartDay(void);
void CheckPokerusTick(void);
void CheckPokerusTick_Conv(void);
void SetUnusedTwoDayTimer(void);
void CheckUnusedTwoDayTimer(void);
void UnusedSetSwarmFlag(void);
void UnusedCheckSwarmFlag(void);
void RestartLuckyNumberCountdown(void);
void v_CheckLuckyNumberShowFlag(void);
bool v_CheckLuckyNumberShowFlag_Conv(void);
void DoMysteryGiftIfDayHasPassed(void);
void UpdateTimeRemaining(void);
bool UpdateTimeRemaining_Conv(uint8_t* hl, uint8_t a);
void GetSecondsSinceIfLessThan60(void);
void GetMinutesSinceIfLessThan60(void);
uint8_t GetMinutesSinceIfLessThan60_Conv(void);
void GetHoursSinceIfLessThan24(void);
void GetDaysSince(void);
uint8_t GetDaysSince_Conv(void);
void GetTimeElapsed_ExceedsUnitLimit(void);
void CalcDaysSince(void);
void CalcDaysSince_Conv(uint8_t* hl);
void CalcHoursDaysSince(void);
void CalcMinsHoursDaysSince(void);
void CalcMinsHoursDaysSince_Conv(uint8_t* hl);
void CalcSecsMinsHoursDaysSince(void);
void CalcSecsMinsHoursDaysSince_Conv(uint8_t* hl);
void v_CalcMinsHoursDaysSince(void);
void v_CalcMinsHoursDaysSince_Conv(uint8_t* hl, uint8_t carry);
void v_CalcHoursDaysSince(void);
void v_CalcHoursDaysSince_Conv(uint8_t* hl, uint8_t carry);
void v_CalcDaysSince(void);
void v_CalcDaysSince_Conv(uint8_t* hl, uint8_t carry);
void CopyDayHourMinSecToHL(void);
void CopyDayHourMinSecToHL_Conv(uint8_t* hl);
void CopyDayToHL(void);
void CopyDayToHL_Conv(uint8_t* hl);
void CopyDayHourToHL(void);
void CopyDayHourMinToHL(void);
void CopyDayHourMinToHL_Conv(uint8_t* hl);
