void DoPlayerTurn(void);
void DoEnemyTurn(void);
void DoTurn(void);
void DoMove(void);
void CheckTurn(void);
void BattleCommand_CheckTurn(void);
void CantMove(void);
void OpponentCantMove(void);
void CheckEnemyTurn(void);
void EndTurn(void);
void MoveDisabled(void);
void HitConfusion(void);
void BattleCommand_CheckObedience(void);
void IgnoreSleepOnly(void);
bool IgnoreSleepOnly_Conv(void);
void BattleCommand_UsedMoveText(void);
void CheckUserIsCharging(void);
bool CheckUserIsCharging_Conv(void);
void BattleCommand_DoTurn(void);
void CheckMimicUsed(void);
bool CheckMimicUsed_Conv(void);
void BattleCommand_Critical(void);
void BattleCommand_Stab(void);
void BattleCheckTypeMatchup(void);
uint8_t BattleCheckTypeMatchup_Conv(void);
void CheckTypeMatchup(void);
uint8_t CheckTypeMatchup_Conv(uint8_t type, const uint8_t* types);
void BattleCommand_ResetTypeMatchup(void);
void BattleCommand_DamageVariation(void);
void BattleCommand_CheckHit(void);
void BattleCommand_EffectChance(void);
void BattleCommand_LowerSub(void);
void BattleCommand_MoveAnim(void);
void BattleCommand_MoveAnimNoSub(void);
void BattleCommand_StatUpAnim(void);
void BattleCommand_StatDownAnim(void);
void BattleCommand_StatUpDownAnim(uint8_t anim);
void BattleCommand_SwitchTurn(void);
void BattleCommand_RaiseSub(void);
void BattleCommand_FailureText(void);
void BattleCommand_ApplyDamage(void);
void GetFailureResultText(void);
void FailText_CheckOpponentProtect(void);
void FailText_CheckOpponentProtect_Conv(const struct TextCmd* hl, const struct TextCmd* de);
void BattleCommand_BideFailText(void);
void BattleCommand_CriticalText(void);
void BattleCommand_StartLoop(void);
void BattleCommand_SuperEffectiveLoopText(void);
void BattleCommand_SuperEffectiveText(void);
void BattleCommand_CheckFaint(void);
void BattleCommand_BuildOpponentRage(void);
void BattleCommand_RageDamage(void);
void EndMoveEffect(void);
void DittoMetalPowder(void);
void DittoMetalPowder_Conv(uint8_t* b, uint8_t* c);
void BattleCommand_DamageStats(void);
void PlayerAttackDamage(struct BattleCmdState* state);
void TruncateHL_BC(void);
union Register TruncateHL_BC_Conv(uint16_t hl, uint16_t bc);
void CheckDamageStatsCritical(void);
bool CheckDamageStatsCritical_Conv(void);
void ThickClubBoost(void);
uint16_t ThickClubBoost_Conv(uint16_t atk);
void LightBallBoost(void);
uint16_t LightBallBoost_Conv(uint16_t spatk);
void SpeciesItemBoost(void);
uint16_t SpeciesItemBoost_Conv(uint16_t hl, species_t b, species_t c, item_t d);
void EnemyAttackDamage(struct BattleCmdState* state);
void BattleCommand_ClearMissDamage(void);
void HitSelfInConfusion(void);
void HitSelfInConfusion_Conv(struct BattleCmdState* state);
void BattleCommand_DamageCalc(void);
uint8_t DamageCalc(uint8_t pwr, uint8_t lvl, uint8_t def, uint8_t atk);
void BattleCommand_ConstantDamage(void);
void BattleCommand_DefrostOpponent(void);
void FarPlayBattleAnimation(void);
void FarPlayBattleAnimation_Conv(uint16_t de);
void PlayFXAnimID(void);
void PlayFXAnimID_Conv(uint16_t de);
void DoEnemyDamage(void);
void DoEnemyDamage_Conv(bool ignoreSub);
void DoPlayerDamage(void);
void DoPlayerDamage_Conv(bool ignoreSub);
void DoSubstituteDamage(void);
void UpdateMoveData(void);
void BattleCommand_SleepTarget(void);
void BattleCommand_PoisonTarget(void);
void BattleCommand_Poison(void);
void CheckIfTargetIsPoisonType(void);
bool CheckIfTargetIsPoisonType_Conv(void);
void PoisonOpponent(void);
void BattleCommand_DrainTarget(void);
void BattleCommand_EatDream(void);
void SapHealth(void);
void BattleCommand_BurnTarget(void);
void Defrost(void);
void Defrost_Conv(uint8_t* stat);
void BattleCommand_FreezeTarget(void);
void BattleCommand_ParalyzeTarget(void);
void BattleCommand_AttackUp(void);
void BattleCommand_DefenseUp(void);
void BattleCommand_SpeedUp(void);
void BattleCommand_SpecialAttackUp(void);
void BattleCommand_SpecialDefenseUp(void);
void BattleCommand_AccuracyUp(void);
void BattleCommand_EvasionUp(void);
void BattleCommand_AttackUp2(void);
void BattleCommand_DefenseUp2(void);
void BattleCommand_SpeedUp2(void);
void BattleCommand_SpecialAttackUp2(void);
void BattleCommand_SpecialDefenseUp2(void);
void BattleCommand_AccuracyUp2(void);
void BattleCommand_EvasionUp2(void);
void BattleCommand_StatUp(void);
void RaiseStat(void);
void RaiseStat_Conv(uint8_t b);
void MinimizeDropSub(void);
void BattleCommand_AttackDown(void);
void BattleCommand_DefenseDown(void);
void BattleCommand_SpeedDown(void);
void BattleCommand_SpecialAttackDown(void);
void BattleCommand_SpecialDefenseDown(void);
void BattleCommand_AccuracyDown(void);
void BattleCommand_EvasionDown(void);
void BattleCommand_AttackDown2(void);
void BattleCommand_DefenseDown2(void);
void BattleCommand_SpeedDown2(void);
void BattleCommand_SpecialAttackDown2(void);
void BattleCommand_SpecialDefenseDown2(void);
void BattleCommand_AccuracyDown2(void);
void BattleCommand_EvasionDown2(void);
void BattleCommand_StatDown(void);
void CheckMist(void);
bool CheckMist_Conv(void);
void BattleCommand_StatUpMessage(void);
void BattleCommand_StatDownMessage(void);
void TryLowerStat(void);
bool TryLowerStat_Conv(uint8_t c, uint16_t* hl);
void BattleCommand_StatUpFailText(void);
void BattleCommand_StatDownFailText(void);
void GetStatName(void);
uint8_t* GetStatName_Conv(uint8_t b);
void BattleCommand_AllStatsUp(void);
void ResetMiss(void);
void LowerStat(void);
void BattleCommand_TriStatusChance(void);
void BattleCommand_Curl(void);
void BattleCommand_RaiseSubNoAnim(void);
void BattleCommand_LowerSubNoAnim(void);
void CalcPlayerStats(void);
void CalcEnemyStats(void);
void CalcBattleStats(void);
void CalcBattleStats_Conv(uint8_t* hl, uint16_t* de, uint16_t* bc, uint8_t a);
void BattleCommand_CheckRampage(void);
void BattleCommand_Rampage(void);
void SetBattleDraw(void);
void BattleCommand_ForceSwitch(void);
void CheckPlayerHasMonToSwitchTo(void);
bool CheckPlayerHasMonToSwitchTo_Conv(void);
void BattleCommand_EndLoop(void);
void BattleCommand_FakeOut(void);
void BattleCommand_FlinchTarget(void);
void FlinchTarget(void);
void CheckOpponentWentFirst(void);
bool CheckOpponentWentFirst_Conv(void);
void BattleCommand_HeldFlinch(void);
void BattleCommand_OHKO(void);
void BattleCommand_CheckCharge(void);
void BattleCommand_Charge(void);
void BattleCommand_Unused3C(void);
void BattleCommand_TrapTarget(void);
void BattleCommand_Recoil(void);
void BattleCommand_ConfuseTarget(void);
void BattleCommand_Confuse(void);
void BattleCommand_FinishConfusingTarget(void);
void BattleCommand_FinishConfusingTarget_Conv(uint8_t* hl);
void BattleCommand_Confuse_CheckSnore_Swagger_ConfuseHit(void);
void BattleCommand_Paralyze(void);
void CheckMoveTypeMatchesTarget(void);
bool CheckMoveTypeMatchesTarget_Conv(void);
void BattleCommand_RechargeNextTurn(void);
void EndRechargeOpp(void);
void BattleCommand_DoubleFlyingDamage(void);
void BattleCommand_DoubleUndergroundDamage(void);
void DoubleDamage(void);
void BattleCommand_ResetStats(void);
void BattleCommand_Heal(void);
void BattleEffect_ButItFailed(void);
void ClearLastMove(void);
void ResetActorDisable(void);
void BattleCommand_Screen(void);
void PrintDoesntAffect(void);
void PrintNothingHappened(void);
void TryPrintButItFailed(void);
void PrintButItFailed(void);
void FailMove(void);
void FailMimic(void);
void PrintDidntAffect(void);
void PrintDidntAffect2(void);
void PrintParalyze(void);
void CheckSubstituteOpp(void);
bool CheckSubstituteOpp_Conv(void);
void CheckUserMove(void);
void ResetTurn(void);
void BattleCommand_ArenaTrap(void);
void BattleCommand_Defrost(void);
void BattleCommand_Unused5D(void);
void SafeCheckSafeguard(void);
bool SafeCheckSafeguard_Conv(void);
void BattleCommand_CheckSafeguard(void);
void BattleCommand_HealMorn(void);
void BattleCommand_HealDay(void);
void BattleCommand_HealNite(void);
void BattleCommand_TimeBasedHealContinue(uint8_t b);
void BattleCommand_DoubleMinimizeDamage(void);
void BattleCommand_SkipSunCharge(void);
void CheckHiddenOpponent(void);
bool CheckHiddenOpponent_Conv(void);
void GetUserItem(void);
uint16_t GetUserItem_Conv(item_t* hl);
void GetOpponentItem(void);
uint16_t GetOpponentItem_Conv(item_t* hl);
void GetItemHeldEffect(void);
uint16_t GetItemHeldEffect_Conv(item_t b);
void AnimateCurrentMoveEitherSide(void);
void AnimateCurrentMove(void);
void PlayDamageAnim(void);
void LoadMoveAnim(void);
void LoadAnim(void);
void LoadAnim_Conv(uint8_t a);
void PlayUserBattleAnim(void);
void PlayUserBattleAnim_Conv(void);
void PlayOpponentBattleAnim(void);
void PlayOpponentBattleAnim_Conv(uint16_t de);
void CallBattleCore(void);
void AnimateFailedMove(void);
void BattleCommand_MoveDelay(void);
void BattleCommand_ClearText(void);
void SkipToBattleCommand(uint8_t b);
void GetMoveAttr(void);
void GetMoveData(void);
void GetMoveData_Conv(struct Move* de, move_t a);
void GetMoveByte(void);
void DisappearUser(void);
void AppearUserLowerSub(void);
void AppearUserRaiseSub(void);
void v_CheckBattleScene(void);
extern struct BattleCmdState gBattleCmdState;
//#include "data/moves/critical_hit_moves.h"
//#include "data/battle/critical_hit_chances.h"
//#include "engine/battle/move_effects/triple_kick.h"
#include "./ai/switch.h"
//#include "data/types/type_matchups.h"
//#include "data/battle/accuracy_multipliers.h"
//#include "engine/battle/move_effects/beat_up.h"
//#include "data/types/type_boost_items.h"
//#include "data/moves/flail_reversal_power.h"
//#include "engine/battle/move_effects/counter.h"
//#include "engine/battle/move_effects/encore.h"
//#include "engine/battle/move_effects/pain_split.h"
//#include "engine/battle/move_effects/snore.h"
//#include "engine/battle/move_effects/conversion2.h"
#include "./move_effects/lock_on.h"
//#include "engine/battle/move_effects/sketch.h"
//#include "engine/battle/move_effects/sleep_talk.h"
//#include "engine/battle/move_effects/destiny_bond.h"
//#include "engine/battle/move_effects/spite.h"
#include "./move_effects/false_swipe.h"
//#include "engine/battle/move_effects/heal_bell.h"
//#include "data/battle/stat_names.h"
//#include "data/battle/stat_multipliers.h"
//#include "engine/battle/move_effects/bide.h"
//#include "engine/battle/move_effects/teleport.h"
//#include "engine/battle/move_effects/mist.h"
#include "./move_effects/focus_energy.h"
//#include "engine/battle/move_effects/substitute.h"
//#include "engine/battle/move_effects/rage.h"
//#include "engine/battle/move_effects/mimic.h"
//#include "engine/battle/move_effects/leech_seed.h"
#include "./move_effects/splash.h"
//#include "engine/battle/move_effects/disable.h"
//#include "engine/battle/move_effects/pay_day.h"
//#include "engine/battle/move_effects/conversion.h"
//#include "engine/battle/move_effects/transform.h"
//#include "engine/battle/move_effects/selfdestruct.h"
//#include "engine/battle/move_effects/mirror_move.h"
//#include "engine/battle/move_effects/metronome.h"
//#include "engine/battle/move_effects/thief.h"
//#include "engine/battle/move_effects/nightmare.h"
//#include "engine/battle/move_effects/curse.h"
//#include "engine/battle/move_effects/protect.h"
//#include "engine/battle/move_effects/endure.h"
//#include "engine/battle/move_effects/spikes.h"
//#include "engine/battle/move_effects/foresight.h"
//#include "engine/battle/move_effects/perish_song.h"
//#include "engine/battle/move_effects/sandstorm.h"
//#include "engine/battle/move_effects/rollout.h"
#include "./move_effects/fury_cutter.h"
#include "./move_effects/attract.h"
//#include "engine/battle/move_effects/return.h"
//#include "engine/battle/move_effects/present.h"
//#include "engine/battle/move_effects/frustration.h"
#include "./move_effects/safeguard.h"
//#include "engine/battle/move_effects/magnitude.h"
//#include "engine/battle/move_effects/baton_pass.h"
//#include "engine/battle/move_effects/pursuit.h"
//#include "engine/battle/move_effects/rapid_spin.h"
#include "./move_effects/hidden_power.h"
#include "./move_effects/rain_dance.h"
#include "./move_effects/sunny_day.h"
//#include "engine/battle/move_effects/belly_drum.h"
//#include "engine/battle/move_effects/psych_up.h"
//#include "engine/battle/move_effects/mirror_coat.h"
//#include "engine/battle/move_effects/future_sight.h"
//#include "engine/battle/move_effects/thunder.h"
