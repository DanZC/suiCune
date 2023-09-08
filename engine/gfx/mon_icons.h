void LoadOverworldMonIcon(void);
void LoadMenuMonIcon(void);
void Unused_GetPartyMenuMonIcon(void);
void Mobile_InitAnimatedMonIcon(void);
struct SpriteAnim* Mobile_InitAnimatedMonIcon_Conv(void);
void Mobile_InitPartyMenuBGPal71(void);
void Mobile_InitPartyMenuBGPal71_Conv(void);
void PartyMenu_InitAnimatedMonIcon(void);
struct SpriteAnim* PartyMenu_InitAnimatedMonIcon_Conv(void);
void InitPartyMenuIcon(void);
struct SpriteAnim* InitPartyMenuIcon_Conv(void);
void SetPartyMonIconAnimSpeed(void);
void SetPartyMonIconAnimSpeed_Conv(struct SpriteAnim* bc);
void NamingScreen_InitAnimatedMonIcon(void);
void NamingScreen_InitAnimatedMonIcon_Conv(void);
void MoveList_InitAnimatedMonIcon(void);
void MoveList_InitAnimatedMonIcon_Conv(void);
void Trade_LoadMonIconGFX(void);
void Trade_LoadMonIconGFX_Conv(void);
void GetSpeciesIcon(void);
void GetSpeciesIcon_Conv(uint16_t de);
void FlyFunction_GetMonIcon(void);
uint8_t* FlyFunction_GetMonIcon_Conv(uint16_t de);
void GetMonIconDE(void);
void GetMemIconGFX(void);
void GetMemIconGFX_Conv(void);
void GetIconGFX(void);
void GetIconGFX_Conv(uint8_t a);
// void HeldItemIcons(void);
void GetIcon_de(void);
uint8_t* GetIcon_de_Conv(uint16_t de);
void GetIcon_a(void);
uint8_t* GetIcon_a_Conv(uint8_t a);
void GetIcon(void);
uint8_t* GetIcon_Conv(uint16_t hl);
void GetGFXUnlessMobile(void);
void GetGFXUnlessMobile_Conv(uint8_t* hl, const char* de, uint8_t c);
void FreezeMonIcons(void);
void FreezeMonIcons_Conv(void);
void UnfreezeMonIcons(void);
void UnfreezeMonIcons_Conv(void);
void HoldSwitchmonIcon(void);
void HoldSwitchmonIcon_Conv(void);
void ReadMonMenuIcon(void);
uint8_t ReadMonMenuIcon_Conv(species_t a);
//#include "gfx/icons/mail.2bpp"
//#include "gfx/icons/item.2bpp"
//#include "data/pokemon/menu_icons.h"
//#include "data/icon_pointers.h"
//#include "gfx/icons.h"
