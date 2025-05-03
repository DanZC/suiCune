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
bool IgnoreSleepOnly(void);
void BattleCommand_UsedMoveText(void);
bool CheckUserIsCharging(void);
void BattleCommand_DoTurn(void);
bool CheckMimicUsed(void);
void BattleCommand_Critical(void);
void BattleCommand_Stab(void);
uint8_t BattleCheckTypeMatchup(void);
uint8_t CheckTypeMatchup(uint8_t type, const uint8_t* types);
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
void FailText_CheckOpponentProtect(const struct TextCmd* hl, const struct TextCmd* de);
void BattleCommand_BideFailText(void);
void BattleCommand_CriticalText(void);
void BattleCommand_StartLoop(void);
void BattleCommand_SuperEffectiveLoopText(void);
void BattleCommand_SuperEffectiveText(void);
void BattleCommand_CheckFaint(void);
void BattleCommand_BuildOpponentRage(void);
void BattleCommand_RageDamage(void);
void EndMoveEffect(void);
void DittoMetalPowder(uint8_t* b, uint8_t* c);
void BattleCommand_DamageStats(void);
void PlayerAttackDamage(struct BattleCmdState* state);
uint16_t TruncateHL_BC(uint16_t hl, uint16_t bc);
bool CheckDamageStatsCritical(void);
uint16_t ThickClubBoost(uint16_t atk);
uint16_t LightBallBoost(uint16_t spatk);
uint16_t SpeciesItemBoost(uint16_t hl, species_t b, species_t c, item_t d);
void EnemyAttackDamage(struct BattleCmdState* state);
void BattleCommand_ClearMissDamage(void);
void HitSelfInConfusion(struct BattleCmdState* state);
void BattleCommand_DamageCalc(void);
uint8_t DamageCalc(uint8_t pwr, uint8_t lvl, uint8_t def, uint8_t atk);
void BattleCommand_ConstantDamage(void);
void BattleCommand_DefrostOpponent(void);
void FarPlayBattleAnimation(uint16_t de);
void PlayFXAnimID(uint16_t de);
void DoEnemyDamage(bool ignoreSub);
void DoPlayerDamage(bool ignoreSub);
void DoSubstituteDamage(void);
void UpdateMoveData(void);
void BattleCommand_SleepTarget(void);
void BattleCommand_PoisonTarget(void);
void BattleCommand_Poison(void);
bool CheckIfTargetIsPoisonType(void);
void PoisonOpponent(void);
void BattleCommand_DrainTarget(void);
void BattleCommand_EatDream(void);
void SapHealth(void);
void BattleCommand_BurnTarget(void);
void Defrost(uint8_t* stat);
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
void RaiseStat(uint8_t b);
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
bool CheckMist(void);
void BattleCommand_StatUpMessage(void);
void BattleCommand_StatDownMessage(void);
bool TryLowerStat(uint8_t c, uint16_t* hl);
void BattleCommand_StatUpFailText(void);
void BattleCommand_StatDownFailText(void);
uint8_t* GetStatName(uint8_t b);
void BattleCommand_AllStatsUp(void);
void ResetMiss(void);
void LowerStat(uint8_t a);
void BattleCommand_TriStatusChance(void);
void BattleCommand_Curl(void);
void BattleCommand_RaiseSubNoAnim(void);
void BattleCommand_LowerSubNoAnim(void);
void CalcPlayerStats(void);
void CalcEnemyStats(void);
void CalcBattleStats(uint8_t* hl, uint16_t* de, uint16_t* bc, uint8_t a);
void BattleCommand_CheckRampage(void);
void BattleCommand_Rampage(void);
void SetBattleDraw(void);
void BattleCommand_ForceSwitch(void);
bool CheckPlayerHasMonToSwitchTo(void);
void BattleCommand_EndLoop(void);
void BattleCommand_FakeOut(void);
void BattleCommand_FlinchTarget(void);
void FlinchTarget(void);
bool CheckOpponentWentFirst(void);
void BattleCommand_HeldFlinch(void);
void BattleCommand_OHKO(void);
void BattleCommand_CheckCharge(void);
void BattleCommand_Charge(void);
void BattleCommand_Unused3C(void);
void BattleCommand_TrapTarget(void);
void BattleCommand_Recoil(void);
void BattleCommand_ConfuseTarget(void);
void BattleCommand_Confuse(void);
void BattleCommand_FinishConfusingTarget(uint8_t* hl);
void BattleCommand_Confuse_CheckSnore_Swagger_ConfuseHit(void);
void BattleCommand_Paralyze(void);
bool CheckMoveTypeMatchesTarget(void);
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
bool CheckSubstituteOpp(void);
bool CheckUserMove(move_t a);
void ResetTurn(void);
void BattleCommand_ArenaTrap(void);
void BattleCommand_Defrost(void);
void BattleCommand_Unused5D(void);
bool SafeCheckSafeguard(void);
void BattleCommand_CheckSafeguard(void);
void BattleCommand_HealMorn(void);
void BattleCommand_HealDay(void);
void BattleCommand_HealNite(void);
void BattleCommand_TimeBasedHealContinue(uint8_t b);
void BattleCommand_DoubleMinimizeDamage(void);
void BattleCommand_SkipSunCharge(void);
bool CheckHiddenOpponent(void);
uint16_t GetUserItem(item_t* hl);
uint16_t GetOpponentItem(item_t* hl);
uint16_t GetItemHeldEffect(item_t b);
void AnimateCurrentMoveEitherSide(void);
void AnimateCurrentMove(void);
void PlayDamageAnim(void);
void LoadMoveAnim(void);
void LoadAnim(uint8_t a);
void PlayUserBattleAnim(void);
void PlayOpponentBattleAnim(uint16_t de);
void CallBattleCore(void);
void AnimateFailedMove(void);
void BattleCommand_MoveDelay(void);
void BattleCommand_ClearText(void);
void SkipToBattleCommand(uint8_t b);
const struct Move* GetMoveAttr(move_t a);
void GetMoveData(struct Move* de, move_t a);
void GetMoveByte(void);
void DisappearUser(void);
void AppearUserLowerSub(void);
void AppearUserRaiseSub(void);
bool v_CheckBattleScene(void);
extern struct BattleCmdState gBattleCmdState;
//#include "data/moves/critical_hit_moves.h"
//#include "data/battle/critical_hit_chances.h"
#include "./move_effects/triple_kick.h"
#include "./ai/switch.h"
//#include "data/types/type_matchups.h"
//#include "data/battle/accuracy_multipliers.h"
#include "./move_effects/beat_up.h"
//#include "data/types/type_boost_items.h"
//#include "data/moves/flail_reversal_power.h"
#include "./move_effects/counter.h"
#include "./move_effects/encore.h"
#include "./move_effects/pain_split.h"
#include "./move_effects/snore.h"
#include "./move_effects/conversion2.h"
#include "./move_effects/lock_on.h"
#include "./move_effects/sketch.h"
#include "./move_effects/sleep_talk.h"
#include "./move_effects/destiny_bond.h"
#include "./move_effects/spite.h"
#include "./move_effects/false_swipe.h"
#include "./move_effects/heal_bell.h"
//#include "data/battle/stat_names.h"
//#include "data/battle/stat_multipliers.h"
#include "./move_effects/bide.h"
#include "./move_effects/teleport.h"
#include "./move_effects/mist.h"
#include "./move_effects/focus_energy.h"
#include "./move_effects/substitute.h"
#include "./move_effects/rage.h"
#include "./move_effects/mimic.h"
#include "./move_effects/leech_seed.h"
#include "./move_effects/splash.h"
#include "./move_effects/disable.h"
#include "./move_effects/pay_day.h"
#include "./move_effects/conversion.h"
#include "./move_effects/transform.h"
#include "./move_effects/selfdestruct.h"
#include "./move_effects/mirror_move.h"
#include "./move_effects/metronome.h"
#include "./move_effects/thief.h"
#include "./move_effects/nightmare.h"
#include "./move_effects/curse.h"
#include "./move_effects/protect.h"
#include "./move_effects/endure.h"
#include "./move_effects/spikes.h"
#include "./move_effects/foresight.h"
#include "./move_effects/perish_song.h"
#include "./move_effects/sandstorm.h"
#include "./move_effects/rollout.h"
#include "./move_effects/fury_cutter.h"
#include "./move_effects/attract.h"
#include "./move_effects/return.h"
#include "./move_effects/present.h"
#include "./move_effects/frustration.h"
#include "./move_effects/safeguard.h"
#include "./move_effects/magnitude.h"
#include "./move_effects/baton_pass.h"
#include "./move_effects/pursuit.h"
#include "./move_effects/rapid_spin.h"
#include "./move_effects/hidden_power.h"
#include "./move_effects/rain_dance.h"
#include "./move_effects/sunny_day.h"
#include "./move_effects/belly_drum.h"
#include "./move_effects/psych_up.h"
#include "./move_effects/mirror_coat.h"
#include "./move_effects/future_sight.h"
#include "./move_effects/thunder.h"
