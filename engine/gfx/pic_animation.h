void Unused_AnimateMon_Slow_Normal(void);
void AnimateMon_Menu(void);
void AnimateMon_Menu_Conv(uint8_t* hl);
void AnimateMon_Trade(void);
void AnimateMon_Trade_Conv(uint8_t* hl);
void AnimateMon_Evolve(void);
void AnimateMon_Evolve_Conv(uint8_t* hl);
void AnimateMon_Hatch(void);
void AnimateMon_Hatch_Conv(uint8_t* hl);
void AnimateMon_HOF(void);
// void PokeAnims(void);
void AnimateFrontpic(void);
void AnimateFrontpic_Conv(uint8_t* hl, uint8_t d, uint8_t e);
void LoadMonAnimation(void);
void LoadMonAnimation_Conv(uint8_t* hl, uint8_t d, uint8_t e);
void SetUpPokeAnim(void);
bool SetUpPokeAnim_Conv(void);
// void PokeAnim_SetupCommands(void);
void PokeAnim_SetWait(void);
void PokeAnim_Wait(void);
void PokeAnim_Setup(void);
void PokeAnim_Setup2(void);
void PokeAnim_Idle(void);
void PokeAnim_Play(void);
void PokeAnim_Play2(void);
void PokeAnim_BasePic(void);
void PokeAnim_Finish(void);
void PokeAnim_Cry(void);
void PokeAnim_CryNoWait(void);
void PokeAnim_StereoCry(void);
void PokeAnim_DeinitFrames(void);
void AnimateMon_CheckIfPokemon(void);
bool AnimateMon_CheckIfPokemon_Conv(void);
void PokeAnim_InitPicAttributes(void);
void PokeAnim_InitPicAttributes_Conv(const uint8_t* bc, uint8_t* hl, uint8_t d);
void PokeAnim_InitAnim(void);
void PokeAnim_InitAnim_Conv(uint8_t b, uint8_t c);
void PokeAnim_DoAnimScript(void);
void PokeAnim_DoAnimScript_Conv(void);
void PokeAnim_End(void);
void PokeAnim_GetDuration(void);
uint8_t PokeAnim_GetDuration_Conv(uint8_t a);
void PokeAnim_GetFrame(void);
void PokeAnim_StartWaitAnim(void);
void PokeAnim_StopWaitAnim(void);
void PokeAnim_IsUnown(void);
bool PokeAnim_IsUnown_Conv(species_t a);
void PokeAnim_IsEgg(void);
bool PokeAnim_IsEgg_Conv(void);
void PokeAnim_GetPointer(void);
void PokeAnim_GetPointer_Conv(void);
void PokeAnim_GetBitmaskIndex(void);
uint16_t PokeAnim_GetBitmaskIndex_Conv(void);
void PokeAnim_CopyBitmaskToBuffer(void);
void PokeAnim_ConvertAndApplyBitmask(void);
void PokeAnim_PlaceGraphic(void);
void PokeAnim_PlaceGraphic_Conv(void);
void PokeAnim_SetVBank1(void);
void PokeAnim_SetVBank1_Conv(void);
void PokeAnim_SetVBank0(void);
void PokeAnim_SetVBank0_Conv(void);
void PokeAnim_GetAttrmapCoord(void);
uint8_t* PokeAnim_GetAttrmapCoord_Conv(void);
void GetMonAnimPointer(void);
void GetMonAnimPointer_Conv(void);
void PokeAnim_GetFrontpicDims(void);
uint8_t PokeAnim_GetFrontpicDims_Conv(void);
void GetMonFramesPointer(void);
void GetMonBitmaskPointer(void);
void PokeAnim_GetSpeciesOrUnown(void);
uint8_t PokeAnim_GetSpeciesOrUnown_Conv(species_t a);
void Unused_HOF_AnimateAlignedFrontpic(void);
void HOF_AnimateFrontpic(void);
void HOF_AnimateFrontpic_Conv(uint8_t* de, uint8_t c);
