void CheckShininess(void);
bool CheckShininess_Conv(uint16_t bc);
void Unused_CheckShininess(void);
void SGB_ApplyCreditsPals(void);
void InitPartyMenuPalettes(void);
void InitPartyMenuPalettes_Conv(void);
void SGB_ApplyPartyMenuHPPals(void);
void Intro_LoadMagikarpPalettes(void);
void Intro_LoadAllPal0(void);
void Intro_LoadBetaIntroVenusaurPalettes(void);
void Intro_LoadPackPalettes(void);
void GSIntro_LoadMonPalette(void);
void LoadTrainerClassPaletteAsNthBGPal(void);
void LoadMonPaletteAsNthBGPal(void);
void LoadNthMiddleBGPal(void);
void LoadBetaPokerPalettes(void);
void ApplyMonOrTrainerPals(uint8_t e);
void ApplyHPBarPals(uint8_t c);
void LoadStatsScreenPals(void);
bool LoadStatsScreenPals_Conv(uint8_t c);
void LoadMailPalettes(void);
void CopyFourPalettes(void);
void CopyFourPalettes_Conv(const uint8_t* pal);
void CopyPalettes(void);
void CopyPalettes_Conv(uint16_t* de, const uint8_t* hl, uint8_t c);
void GetPredefPal(void);
const uint16_t* GetPredefPal_Conv(uint8_t a);
void LoadHLPaletteIntoDE(void);
void LoadHLPaletteIntoDE_Conv(void* de, const uint16_t* hl);
void LoadPalette_White_Col1_Col2_Black(void);
uint16_t* LoadPalette_White_Col1_Col2_Black_Conv(uint16_t* de, const uint16_t* hl);
void FillBoxCGB(void);
void FillBoxCGB_Conv(uint8_t* hl, uint8_t b, uint8_t c, uint8_t a);
void ResetBGPals(void);
void ResetBGPals_Conv(void);
void WipeAttrmap(void);
void ApplyPals(void);
void ApplyPals_Conv(void);
void ApplyAttrmap(void);
void ApplyAttrmap_Conv(void);
void CGB_ApplyPartyMenuHPPals(void);
void CGB_ApplyPartyMenuHPPals_Conv(void);
void InitPartyMenuOBPals(void);
void GetBattlemonBackpicPalettePointer(void);
uint16_t* GetBattlemonBackpicPalettePointer_Conv(uint16_t* dest);
void GetEnemyFrontpicPalettePointer(void);
uint16_t* GetEnemyFrontpicPalettePointer_Conv(uint16_t* dest);
void GetPlayerOrMonPalettePointer(void);
uint16_t* GetPlayerOrMonPalettePointer_Conv(uint16_t* dest, uint8_t a, uint16_t bc);
void GetFrontpicPalettePointer(void);
uint16_t* GetFrontpicPalettePointer_Conv(uint16_t* dest, uint8_t a, uint16_t bc);
void GetTrainerPalettePointer(void);
uint16_t* GetTrainerPalettePointer_Conv(uint16_t* dest, uint8_t a);
void GetMonPalettePointer(void);
uint16_t* GetMonPalettePointer_Conv(uint16_t* dest, uint8_t a);
void CGBCopyBattleObjectPals(void);
extern const uint16_t BattleObjectPals[];
void CGBCopyTwoPredefObjectPals(void);
void v_GetMonPalettePointer(void);
const char* v_GetMonPalettePointer_Conv(species_t a);
void GetMonNormalOrShinyPalettePointer(void);
uint16_t* GetMonNormalOrShinyPalettePointer_Conv(uint16_t* dest, species_t a, uint16_t bc);
void PushSGBPals(void);
void v_PushSGBPals(void);
void InitSGBBorder(void);
void InitCGBPals(void);
void InitCGBPals_Conv(void);
void v_InitSGBBorderPals(void);
void UpdateSGBBorder(void);
void PushSGBBorder(void);
void SGB_ClearVRAM(void);
void PushSGBBorderPalsAndWait(void);
void SGBBorder_PushBGPals(void);
void SGBBorder_MorePalPushing(void);
void SGBBorder_YetMorePalPushing(void);
void CopyData(void);
void ClearBytes(void);
void DrawDefaultTiles(void);
void SGBDelayCycles(void);
// void PredefPals(void);
extern const uint16_t PredefPals[][NUM_PAL_COLORS];
// void SGBBorderMapAndPalettes(void);
// void SGBBorderGFX(void);
// void HPBarPals(void);
// void ExpBarPalette(void);
extern const uint16_t HPBarPals[];
extern const char ExpBarPalette[];
void LoadMapPals(void);
extern const char PartyMenuBGMobilePalette[];
extern const char PartyMenuBGPalette[];
extern const uint16_t TilesetBGPalette[];
extern const uint16_t MapObjectPals[];
extern const uint16_t RoofPals[][4];
extern const char DiplomaPalettes[];
extern const char PartyMenuOBPals[];
extern const char UnusedBattleObjectPals[];
extern const char UnusedGSTitleBGPals[];
extern const char UnusedGSTitleOBPals[];
extern const char MalePokegearPals[];
extern const char FemalePokegearPals[];
extern const char BetaPokerPals[];
extern const char SlotMachinePals[];
//#include "engine/gfx/sgb_layouts.h"
//#include "gfx/intro/gs_magikarp_bg.pal"
//#include "gfx/intro/gs_magikarp_ob.pal"
//#include "gfx/mail/mail.pal"
#include "cgb_layouts.h"
//#include "gfx/battle_anims/battle_anims.pal"
//#include "gfx/sgb/blk_packets.h"
//#include "gfx/sgb/pal_packets.h"
//#include "data/sgb_ctrl_packets.h"
//#include "gfx/sgb/predef.pal"
//#include "gfx/sgb/sgb_border.sgb.tilemap"
//#include "gfx/sgb/sgb_border.pal"
//#include "gfx/sgb/sgb_border.2bpp"
//#include "gfx/battle/hp_bar.pal"
//#include "gfx/battle/exp_bar.pal"
//#include "data/pokemon/palettes.h"
//#include "data/trainers/palettes.h"
//#include "data/maps/environment_colors.h"
//#include "gfx/stats/party_menu_bg_mobile.pal"
//#include "gfx/stats/party_menu_bg.pal"
//#include "gfx/tilesets/bg_tiles.pal"
//#include "gfx/overworld/npc_sprites.pal"
//#include "gfx/tilesets/roofs.pal"
//#include "gfx/diploma/diploma.pal"
//#include "gfx/stats/party_menu_ob.pal"
//#include "gfx/battle_anims/unused_battle_anims.pal"
//#include "gfx/title/unused_gs_bg.pal"
//#include "gfx/title/unused_gs_fg.pal"
//#include "gfx/pokegear/pokegear.pal"
//#include "gfx/pokegear/pokegear_f.pal"
//#include "gfx/beta_poker/beta_poker.pal"
//#include "gfx/slots/slots.pal"
