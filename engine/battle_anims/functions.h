void DoBattleAnimFrame(struct BattleAnim* bc);
void BattleAnimFunction_Null(struct BattleAnim* bc);
void BattleAnimFunction_ThrowFromUserToTargetAndDisappear(struct BattleAnim* bc);
bool BattleAnimFunction_ThrowFromUserToTarget(struct BattleAnim* bc);
void BattleAnimFunction_MoveWaveToTarget(struct BattleAnim* bc);
void BattleAnimFunction_MoveInCircle(struct BattleAnim* bc);
void BattleAnimFunction_MoveFromUserToTarget(struct BattleAnim* bc);
void BattleAnimFunction_MoveFromUserToTargetAndDisappear(struct BattleAnim* bc);
void BattleAnimFunction_PokeBall(struct BattleAnim* bc);
void BattleAnimFunction_PokeBallBlocked(struct BattleAnim* bc);
void GetBallAnimPal(struct BattleAnim* bc, item_t item);
void BattleAnimFunction_Ember(struct BattleAnim* bc);
void BattleAnimFunction_Drop(struct BattleAnim* bc);
void BattleAnimFunction_MoveFromUserToTargetSpinAround(struct BattleAnim* bc);
void BattleAnimFunction_Shake(struct BattleAnim* bc);
void BattleAnimFunction_FireBlast(struct BattleAnim* bc);
void BattleAnimFunction_RazorLeaf(struct BattleAnim* bc);
int16_t BattleAnim_ScatterHorizontal(struct BattleAnim* bc);
void BattleAnimFunction_RockSmash(struct BattleAnim* bc);
void BattleAnimFunction_Bubble(struct BattleAnim* bc);
void BattleAnimFunction_Surf(struct BattleAnim* bc);
void BattleAnimFunction_Sing(struct BattleAnim* bc);
void BattleAnimFunction_WaterGun(struct BattleAnim* bc);
void BattleAnimFunction_Powder(struct BattleAnim* bc);
void BattleAnimFunction_Recover(struct BattleAnim* bc);
void BattleAnimFunction_ThunderWave(struct BattleAnim* bc);
void BattleAnimFunction_Clamp_Encore(struct BattleAnim* bc);
void BattleAnimFunction_Bite(struct BattleAnim* bc);
void BattleAnimFunction_SolarBeam(struct BattleAnim* bc);
void BattleAnimFunction_Gust(struct BattleAnim* bc);
void BattleAnimFunction_Absorb(struct BattleAnim* bc);
void BattleAnimFunction_Wrap(struct BattleAnim* bc);
void BattleAnimFunction_LeechSeed(struct BattleAnim* bc);
void BattleAnim_StepThrownToTarget(struct BattleAnim* bc, uint8_t* hl, uint8_t a);
void BattleAnimFunction_Spikes(struct BattleAnim* bc);
void BattleAnimFunction_RazorWind(struct BattleAnim* bc);
void BattleAnimFunction_Kick(struct BattleAnim* bc);
void BattleAnimFunction_Egg(struct BattleAnim* bc);
void BattleAnimFunction_MoveUp(struct BattleAnim* bc);
void BattleAnimFunction_Sound(struct BattleAnim* bc);
void BattleAnimFunction_ConfuseRay(struct BattleAnim* bc);
void BattleAnimFunction_Dizzy(struct BattleAnim* bc);
void BattleAnimFunction_Amnesia(struct BattleAnim* bc);
void BattleAnimFunction_FloatUp(struct BattleAnim* bc);
void BattleAnimFunction_Dig(struct BattleAnim* bc);
void BattleAnimFunction_String(struct BattleAnim* bc);
void BattleAnimFunction_Paralyzed(struct BattleAnim* bc);
void BattleAnimFunction_SpiralDescent(struct BattleAnim* bc);
void BattleAnimFunction_PetalDance(struct BattleAnim* bc);
void BattleAnimFunction_PoisonGas(struct BattleAnim* bc);
void BattleAnimFunction_SmokeFlameWheel(struct BattleAnim* bc);
void BattleAnimFunction_SacredFire(struct BattleAnim* bc);
void BattleAnimFunction_PresentSmokescreen(struct BattleAnim* bc);
void BattleAnimFunction_Horn(struct BattleAnim* bc);
void BattleAnimFunction_Needle(struct BattleAnim* bc);
void BattleAnimFunction_ThiefPayday(struct BattleAnim* bc);
void BattleAnimFunction_AbsorbCircle(struct BattleAnim* bc);
void BattleAnimFunction_Conversion(struct BattleAnim* bc);
void BattleAnimFunction_Bonemerang(struct BattleAnim* bc);
void BattleAnimFunction_Shiny(struct BattleAnim* bc);
void BattleAnimFunction_SkyAttack(struct BattleAnim* bc);
void BattleAnimFunction_GrowthSwordsDance(struct BattleAnim* bc);
void BattleAnimFunction_StrengthSeismicToss(struct BattleAnim* bc);
void BattleAnimFunction_SpeedLine(struct BattleAnim* bc);
void BattleAnimFunction_Sludge(struct BattleAnim* bc);
void BattleAnimFunction_MetronomeHand(struct BattleAnim* bc);
void BattleAnimFunction_MetronomeSparkleSketch(struct BattleAnim* bc);
void BattleAnimFunction_Agility(struct BattleAnim* bc);
void BattleAnimFunction_SafeguardProtect(struct BattleAnim* bc);
void BattleAnimFunction_LockOnMindReader(struct BattleAnim* bc);
void BattleAnimFunction_HealBellNotes(struct BattleAnim* bc);
void BattleAnimFunction_BatonPass(struct BattleAnim* bc);
void BattleAnimFunction_EncoreBellyDrum(struct BattleAnim* bc);
void BattleAnimFunction_SwaggerMorningSun(struct BattleAnim* bc);
void BattleAnimFunction_HiddenPower(struct BattleAnim* bc);
void BattleAnimFunction_Curse(struct BattleAnim* bc);
void BattleAnimFunction_PerishSong(struct BattleAnim* bc);
void BattleAnimFunction_RapidSpin(struct BattleAnim* bc);
void BattleAnimFunction_BetaPursuit(struct BattleAnim* bc);
void BattleAnimFunction_RainSandstorm(struct BattleAnim* bc);
void BattleAnimFunction_AnimObjB0(void);
void BattleAnimFunction_PsychUp(struct BattleAnim* bc);
void BattleAnimFunction_Cotton(struct BattleAnim* bc);
void BattleAnimFunction_AncientPower(struct BattleAnim* bc);
void BattleAnim_StepCircle(struct BattleAnim* bc, uint8_t a, uint8_t d);
void BattleAnim_StepToTarget(struct BattleAnim* bc, uint8_t a);
void BattleAnim_AnonJumptable(void);
void BattleAnim_IncAnonJumptableIndex(void);
void BattleAnim_AbsSinePrecise(void);
void BattleAnim_AbsCosinePrecise(void);
void BattleAnimSineWave(void);
//#include "data/battle_anims/ball_colors.h"
