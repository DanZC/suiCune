void OverworldLoop(void);
void DisableEvents(void);
void EnableEvents(void);
void CheckBit5_ScriptFlags2(void);
void DisableWarpsConnxns(void);
void DisableCoordEvents(void);
void DisableStepCount(void);
void DisableWildEncounters(void);
void EnableWarpsConnxns(void);
void EnableCoordEvents(void);
void EnableStepCount(void);
void EnableWildEncounters(void);
bool CheckWarpConnxnScriptFlag(void);
bool CheckCoordEventScriptFlag(void);
bool CheckStepCountScriptFlag(void);
bool CheckWildEncountersScriptFlag(void);
void StartMap(void);
void EnterMap(void);
void UnusedWait30Frames(void);
void HandleMap(void);
void MapEvents(void);
void MaxOverworldDelay(void);
void ResetOverworldDelay(void);
void NextOverworldFrame(void);
void HandleMapTimeAndJoypad(void);
void HandleMapObjects(void);
void HandleMapBackground(void);
void CheckPlayerState(void);
void CheckPlayerState_Conv(void);
void v_CheckObjectEnteringVisibleRange(void);
void PlayerEvents(void);
bool PlayerEvents_Conv(void);
void CheckTrainerBattle_GetPlayerEvent(void);
u8_flag_s CheckTrainerBattle_GetPlayerEvent_Conv(void);
void CheckTileEvent(void);
u8_flag_s CheckTileEvent_Conv(void);
void CheckWildEncounterCooldown(void);
bool CheckWildEncounterCooldown_Conv(void);
void SetUpFiveStepWildEncounterCooldown(void);
void SetMinTwoStepWildEncounterCooldown(void);
void Dummy_CheckScriptFlags2Bit5(void);
void RunSceneScript(void);
u8_flag_s RunSceneScript_Conv(void);
void CheckTimeEvents(void);
u8_flag_s CheckTimeEvents_Conv(void);
void OWPlayerInput(void);
u8_flag_s OWPlayerInput_Conv(void);
void CheckAPressOW(void);
u8_flag_s CheckAPressOW_Conv(void);
void PlayTalkObject(void);
void PlayTalkObject_Conv(void);
void TryObjectEvent(void);
u8_flag_s TryObjectEvent_Conv(void);
// void ObjectEventTypeArray(void);
void TryBGEvent(void);
u8_flag_s TryBGEvent_Conv(void);
void BGEventJumptable(void);
u8_flag_s BGEventJumptable_Conv(uint8_t a);
void CheckBGEventFlag(void);
bool CheckBGEventFlag_Conv(void);
void PlayerMovement(void);
u8_flag_s PlayerMovement_Conv(void);
// void PlayerMovementPointers(void);
void CheckMenuOW(void);
u8_flag_s CheckMenuOW_Conv(void);
bool StartMenuScript(script_s* s);
bool SelectMenuScript(script_s* s);
bool StartMenuCallback(script_s* s);
bool SelectMenuCallback(script_s* s);
void CountStep(void);
u8_flag_s CountStep_Conv(void);
void DoRepelStep(void);
bool DoRepelStep_Conv(void);
void DoPlayerEvent(void);
extern const Script_fn_t PlayerEventScriptPointers[];
bool InvalidEventScript(script_s* s);
void UnusedPlayerEventScript(void);
bool HatchEggScript(script_s* s);
bool WarpToNewMapScript(script_s* s);
bool FallIntoMapScript(script_s* s);
bool LandAfterPitfallScript(script_s* s);
bool EdgeWarpScript(script_s* s);
bool ChangeDirectionScript(script_s* s);
void WarpToSpawnPoint(void);
void RunMemScript(void);
u8_flag_s RunMemScript_Conv(void);
void LoadScriptBDE(void);
bool LoadScriptBDE_Conv(Script_fn_t de);
void TryTileCollisionEvent(void);
u8_flag_s TryTileCollisionEvent_Conv(void);
void RandomEncounter(void);
u8_flag_s RandomEncounter_Conv(void);
bool WildBattleScript(script_s* s);
void CanUseSweetScent(void);
bool CanUseSweetScent_Conv(void);
void v_TryWildEncounter_BugContest(void);
bool v_TryWildEncounter_BugContest_Conv(void);
void ChooseWildEncounter_BugContest(void);
void ChooseWildEncounter_BugContest_Conv(void);
void TryWildEncounter_BugContest(void);
bool TryWildEncounter_BugContest_Conv(void);
void DoBikeStep(void);
bool DoBikeStep_Conv(void);
//#include "constants.h"
#include "scripting.h"
//#include "data/wild/bug_contest_mons.h"
#include "cmd_queue.h"
