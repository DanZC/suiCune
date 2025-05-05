#pragma once
struct IconData {
    const char* path;
    uint8_t c;
};
struct IconData LoadOverworldMonIcon(species_t e);
void LoadMenuMonIcon(uint8_t e);
void Unused_GetPartyMenuMonIcon(void);
// struct SpriteAnim* Mobile_InitAnimatedMonIcon(void);
// void Mobile_InitPartyMenuBGPal71(void);
// struct SpriteAnim* PartyMenu_InitAnimatedMonIcon(void);
// struct SpriteAnim* InitPartyMenuIcon(void);
// void SetPartyMonIconAnimSpeed(struct SpriteAnim* bc);
// void NamingScreen_InitAnimatedMonIcon(void);
// void MoveList_InitAnimatedMonIcon(void);
// void Trade_LoadMonIconGFX(void);
void GetSpeciesIcon(uint16_t de);
uint8_t* FlyFunction_GetMonIcon(uint16_t de);
void GetMonIconDE(void);
// void GetMemIconGFX(void);
// void GetIconGFX(uint8_t a);
// void HeldItemIcons(void);
// uint8_t* GetIcon_de(uint16_t de);
// uint8_t* GetIcon_a(uint8_t a);
// uint8_t* GetIcon(uint16_t hl);
void GetGFXUnlessMobile(uint8_t* hl, const char* de, uint8_t c);
void FreezeMonIcons(void);
void UnfreezeMonIcons(void);
void HoldSwitchmonIcon(void);
// uint8_t ReadMonMenuIcon(species_t a);
//#include "gfx/icons/mail.2bpp"
//#include "gfx/icons/item.2bpp"
//#include "data/pokemon/menu_icons.h"
//#include "data/icon_pointers.h"
//#include "gfx/icons.h"
