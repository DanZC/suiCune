bool CheckShininess(uint16_t bc);
void Unused_CheckShininess(void);
void SGB_ApplyCreditsPals(void);
void InitPartyMenuPalettes(void);
void SGB_ApplyPartyMenuHPPals(void);
void Intro_LoadMagikarpPalettes(void);
void Intro_LoadAllPal0(void);
void Intro_LoadBetaIntroVenusaurPalettes(void);
void Intro_LoadPackPalettes(void);
void GSIntro_LoadMonPalette(void);
void LoadTrainerClassPaletteAsNthBGPal(uint8_t e);
void LoadMonPaletteAsNthBGPal(uint8_t e);
void LoadNthMiddleBGPal(uint16_t* hl, uint8_t a);
void LoadBetaPokerPalettes(void);
void ApplyMonOrTrainerPals(uint8_t e);
void ApplyHPBarPals(uint8_t c);
bool LoadStatsScreenPals(uint8_t c);
void LoadMailPalettes(uint8_t e);
void CopyFourPalettes(const uint8_t* pal);
void CopyPalettes(uint16_t* de, const uint8_t* hl, uint8_t c);
const uint16_t* GetPredefPal(uint8_t a);
void LoadHLPaletteIntoDE(void* de, const uint16_t* hl);
uint16_t* LoadPalette_White_Col1_Col2_Black(uint16_t* de, const uint16_t* hl);
tile_t* FillBoxCGB(tile_t* hl, uint8_t b, uint8_t c, uint8_t a);
void ResetBGPals(void);
void WipeAttrmap(void);
void ApplyPals(void);
void ApplyAttrmap(void);
void CGB_ApplyPartyMenuHPPals(void);
void CGB_ApplyPartyMenuHPPals(void);
void InitPartyMenuOBPals(void);
uint16_t* GetBattlemonBackpicPalettePointer(uint16_t* dest);
uint16_t* GetEnemyFrontpicPalettePointer(uint16_t* dest);
uint16_t* GetPlayerOrMonPalettePointer(uint16_t* dest, uint8_t a, uint16_t bc);
uint16_t* GetFrontpicPalettePointer(uint16_t* dest, uint8_t a, uint16_t bc);
uint16_t* GetTrainerPalettePointer(uint16_t* dest, uint8_t a);
// uint16_t* GetMonPalettePointer(uint16_t* dest, uint8_t a);
void CGBCopyBattleObjectPals(void);
extern const uint16_t BattleObjectPals[];
void CGBCopyTwoPredefObjectPals(void);
const char* v_GetMonPalettePointer(species_t a);
uint16_t* GetMonNormalOrShinyPalettePointer(uint16_t* dest, species_t a, uint16_t bc);
void PushSGBPals(void);
void v_PushSGBPals(void);
void InitSGBBorder(void);
void InitCGBPals(void);
void v_InitSGBBorderPals(void);
void UpdateSGBBorder(void);
void PushSGBBorder(void);
void SGB_ClearVRAM(void);
void PushSGBBorderPalsAndWait(void);
void SGBBorder_PushBGPals(void);
void SGBBorder_MorePalPushing(void);
void SGBBorder_YetMorePalPushing(void);
void CopyData(void);
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
