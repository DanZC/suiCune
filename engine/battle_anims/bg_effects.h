void ExecuteBGEffects(void);
void ExecuteBGEffects_Conv(void);
void QueueBGEffect(void);
bool QueueBGEffect_Conv(void);
void EndBattleBGEffect(void);
void EndBattleBGEffect_Conv(struct BattleBGEffect* bc);
void DoBattleBGEffectFunction(void);
void DoBattleBGEffectFunction_Conv(struct BattleBGEffect* bc);
// void BattleBGEffects(void);
extern void(*const BattleBGEffects[54])(void);
void BattleBGEffect_End(void);
void BattleBGEffect_End_Conv(struct BattleBGEffect* bc);
void BatttleBGEffects_GetNamedJumptablePointer(void);
void BattleBGEffects_AnonJumptable(void);
void BattleBGEffects_IncAnonJumptableIndex(void);
void BattleBGEffect_FlashInverted(void);
void BattleBGEffect_FlashWhite(void);
void BattleBGEffect_FlashContinue(void);
void BattleBGEffect_WhiteHues(void);
void BattleBGEffect_BlackHues(void);
void BattleBGEffect_AlternateHues(void);
void BattleBGEffect_CycleOBPalsGrayAndYellow(void);
void BattleBGEffect_CycleMidOBPalsGrayAndYellow(void);
void BattleBGEffect_CycleBGPals_Inverted(void);
void BattleBGEffect_HideMon(void);
void BattleBGEffect_ShowMon(void);
void BattleBGEffect_BattlerObj_1Row(void);
void BattleBGEffect_BattlerObj_2Row(void);
void v_QueueBattleAnimation(void);
void BattleBGEffect_RemoveMon(void);
void BattleBGEffect_EnterMon(void);
void BattleBGEffect_ReturnMon(void);
void BattleBGEffect_RunPicResizeScript(void);
void BattleBGEffect_Surf(void);
void BattleBGEffect_Whirlpool(void);
void BattleBGEffect_StartWater(void);
void BattleBGEffect_Water(void);
void BattleBGEffect_EndWater(void);
void BattleBGEffect_Psychic(void);
void BattleBGEffect_Teleport(void);
void BattleBGEffect_NightShade(void);
void BattleBGEffect_DoubleTeam(void);
void BattleBGEffect_AcidArmor(void);
void BattleBGEffect_Withdraw(void);
void BattleBGEffect_Dig(void);
void BattleBGEffect_Tackle(void);
void BattleBGEffect_BodySlam(void);
void Tackle_MoveForward(void);
void Tackle_ReturnMove(void);
void Rollout_FillLYOverridesBackup(void);
void BattleBGEffect_BetaPursuit(void);
void VitalThrow_MoveBackwards(void);
void BattleBGEffect_VitalThrow(void);
void BattleBGEffect_WobbleMon(void);
void BattleBGEffect_Flail(void);
void BattleBGEffect_WaveDeformMon(void);
void BattleBGEffect_BounceDown(void);
void BattleBGEffect_BetaSendOutMon1(void);
void BattleBGEffect_BetaSendOutMon2(void);
void BattleBGEffect_FadeMonsToBlackRepeating(void);
void BattleBGEffect_RapidFlash(void);
void BattleBGEffect_FadeMonToLight(void);
void BattleBGEffect_FadeMonToBlack(void);
void BattleBGEffect_FadeMonToLightRepeating(void);
void BattleBGEffect_FadeMonToBlackRepeating(void);
void BattleBGEffect_CycleMonLightDarkRepeating(void);
void BattleBGEffect_FlashMonRepeating(void);
void BattleBGEffect_FadeMonToWhiteWaitFadeBack(void);
void BattleBGEffect_FadeMonFromWhite(void);
void BattleBGEffect_VibrateMon(void);
void BattleBGEffect_WobblePlayer(void);
void BattleBGEffect_Rollout(void);
void BattleBGEffect_ShakeScreenX(void);
void BattleBGEffect_ShakeScreenY(void);
void BattleBGEffects_GetShakeAmount(void);
void BattleBGEffect_WobbleScreen(void);
void BattleBGEffect_GetNthDMGPal(void);
void BGEffect_RapidCyclePals(void);
void BGEffects_LoadBGPal0_OBPal1(void);
void BGEffects_LoadBGPal1_OBPal0(void);
void BattleBGEffect_GetFirstDMGPal(void);
void BattleBGEffect_GetNextDMGPal(void);
void BattleBGEffects_ClearLYOverrides(void);
void BattleBGEffects_SetLYOverrides(void);
void BattleBGEffect_SetLCDStatCustoms1(void);
void BattleBGEffect_SetLCDStatCustoms2(void);
void BattleAnim_ResetLCDStatCustom(void);
void BattleBGEffects_ResetVideoHRAM(void);
void DeformScreen(void);
void InitSurfWaves(void);
void DeformWater(void);
void BattleBGEffect_WavyScreenFX(void);
void BGEffect_FillLYOverridesBackup(void);
void BGEffect_DisplaceLYOverridesBackup(void);
void BGEffect_CheckBattleTurn(void);
void BGEffect_CheckFlyDigStatus(void);
void BattleBGEffects_CheckSGB(void);
void BattleBGEffects_Sine(void);
void BattleBGEffects_Cosine(void);
