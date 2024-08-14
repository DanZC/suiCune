#pragma once
struct SpriteLoadData {
    const char* path;
    uint8_t length;
    uint8_t type;
    bool flag;
};
void GetEmote2bpp(void);
void v_UpdatePlayerSprite(void);
void v_UpdatePlayerSprite_Conv(void);
void v_RefreshSprites(void);
void v_ClearSprites(void);
void RefreshSprites(void);
void RefreshSprites_Conv(void);
void GetPlayerSprite(void);
void GetPlayerSprite_Conv(void);
void AddMapSprites(void);
void AddMapSprites_Conv(void);
void AddIndoorSprites(void);
void AddIndoorSprites_Conv(void);
void AddOutdoorSprites(void);
void AddOutdoorSprites_Conv(void);
void LoadUsedSpritesGFX(void);
void LoadUsedSpritesGFX_Conv(void);
void LoadMiscTiles(void);
void LoadMiscTiles_Conv(void);
void SafeGetSprite(void);
struct SpriteLoadData SafeGetSprite_Conv(uint8_t a);
void GetSprite(void);
struct SpriteLoadData GetSprite_Conv(uint8_t a);
void GetMonSprite(void);
struct SpriteLoadData GetMonSprite_Conv(uint8_t a);
void v_DoesSpriteHaveFacings(void);
bool v_DoesSpriteHaveFacings_Conv(uint8_t a);
void v_GetSpritePalette(void);
uint8_t v_GetSpritePalette_Conv(uint8_t c);
void LoadAndSortSprites(void);
void LoadAndSortSprites_Conv(void);
void AddSpriteGFX(void);
bool AddSpriteGFX_Conv(uint8_t a);
void LoadSpriteGFX(void);
void LoadSpriteGFX_Conv(void);
void SortUsedSprites(void);
void SortUsedSprites_Conv(void);
void ArrangeUsedSprites(void);
void ArrangeUsedSprites_Conv(void);
void GetSpriteLength(void);
uint8_t GetSpriteLength_Conv(uint8_t a);
void GetUsedSprites(void);
void GetUsedSprites_Conv(void);
void GetUsedSprite(void);
void GetUsedSprite_Conv(void);
void LoadEmote(void);
void LoadEmote_Conv(uint8_t c);
//#include "data/sprites/player_sprites.h"
//#include "data/sprites/emotes.h"
//#include "data/sprites/sprite_mons.h"
//#include "data/maps/outdoor_sprites.h"
//#include "data/sprites/sprites.h"
