uint8_t CheckBreedmonCompatibility(void);
bool DoEggStep(void);
void OverworldHatchEgg(void);
void HatchEggs(void);
void InitEggMoves(void);

void GetEggFrontpic(tile_t* de, species_t a);
void GetHatchlingFrontpic(tile_t* de, species_t a);
void Hatch_UpdateFrontpicBGMapCenter(tile_t* hl, uint8_t b, uint8_t c, uint8_t a);
void EggHatch_DoAnimFrame(void);
void EggHatch_AnimationSequence(void);
void Hatch_LoadFrontpicPal(uint8_t a);
void EggHatch_CrackShell(void);
void Hatch_InitShellFragments(void);
void Hatch_ShellFragmentLoop(void);
void DayCareMon1(void);
void DayCareMon2(void);
void DayCareMonCursor(void);
extern const txt_cmd_s LeftWithDayCareLadyText[];
extern const txt_cmd_s LeftWithDayCareManText[];
const txt_cmd_s* DayCareMonCompatibilityText(const uint8_t* nickname);
void DayCareMonPrintEmptyString(void);
//#include "gfx/evo/egg_hatch.2bpp"
