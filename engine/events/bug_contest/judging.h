uint8_t v_BugContestJudging(void);
extern const txt_cmd_s ContestJudging_FirstPlaceText[];
extern const txt_cmd_s ContestJudging_FirstPlaceScoreText[];
extern const txt_cmd_s ContestJudging_SecondPlaceText[];
extern const txt_cmd_s ContestJudging_SecondPlaceScoreText[];
extern const txt_cmd_s ContestJudging_ThirdPlaceText[];
extern const txt_cmd_s ContestJudging_ThirdPlaceScoreText[];
void LoadContestantName(uint8_t a);
uint8_t BugContest_GetPlayersResult(void);
void BugContest_JudgeContestants(uint16_t playerScore);
void ClearContestResults(void);
void DetermineContestWinners(void);
void CopyTempContestant(struct BugContestWinner* hl);
void ComputeAIContestantScores(void);
uint16_t ContestScore(void);
//#include "data/events/bug_contest_winners.h"
