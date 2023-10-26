void v_InitializeStartDay(void);
void ClearDailyTimers(void);
void InitCallReceiveDelay(void);
void NextCallReceiveDelay(void);
void CheckReceiveCallTimer(void);
bool CheckReceiveCallTimer_Conv(void);
void InitOneDayCountdown(void);
void InitNDaysCountdown(void);
void CheckDayDependentEventHL(void);
void RestartReceiveCallDelay(void);
void CheckReceiveCallDelay(void);
bool CheckReceiveCallDelay_Conv(void);
void RestartDailyResetTimer(void);
void CheckDailyResetTimer(void);
void SampleKenjiBreakCountdown(void);
void StartBugContestTimer(void);
void CheckBugContestTimer(void);
void InitializeStartDay(void);
void CheckPokerusTick(void);
void SetUnusedTwoDayTimer(void);
void CheckUnusedTwoDayTimer(void);
void UnusedSetSwarmFlag(void);
void UnusedCheckSwarmFlag(void);
void RestartLuckyNumberCountdown(void);
void v_CheckLuckyNumberShowFlag(void);
void DoMysteryGiftIfDayHasPassed(void);
void UpdateTimeRemaining(void);
bool UpdateTimeRemaining_Conv(uint8_t* hl, uint8_t a);
void GetSecondsSinceIfLessThan60(void);
void GetMinutesSinceIfLessThan60(void);
uint8_t GetMinutesSinceIfLessThan60_Conv(void);
void GetHoursSinceIfLessThan24(void);
void GetDaysSince(void);
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
void CopyDayToHL(void);
void CopyDayHourToHL(void);
void CopyDayHourMinToHL(void);
