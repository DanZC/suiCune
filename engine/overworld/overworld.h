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
void GetPlayerSprite(void);
void GetPlayerSprite_Conv(void);
void AddMapSprites(void);
void AddIndoorSprites(void);
void AddOutdoorSprites(void);
void LoadUsedSpritesGFX(void);
void LoadMiscTiles(void);
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
void AddSpriteGFX(void);
void LoadSpriteGFX(void);
void SortUsedSprites(void);
void ArrangeUsedSprites(void);
void GetSpriteLength(void);
void GetUsedSprites(void);
void GetUsedSprite(void);
void GetUsedSprite_Conv(void);
void LoadEmote(void);
void LoadEmote_Conv(uint8_t c);
//#include "data/sprites/player_sprites.h"
//#include "data/sprites/emotes.h"
//#include "data/sprites/sprite_mons.h"
//#include "data/maps/outdoor_sprites.h"
//#include "data/sprites/sprites.h"
