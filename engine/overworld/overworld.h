#pragma once
struct SpriteLoadData {
    const char* path;
    uint8_t length;
    uint8_t type;
    bool flag;
};
void GetEmote2bpp(void);
void v_UpdatePlayerSprite(void);
void v_RefreshSprites(void);
void v_ClearSprites(void);
void RefreshSprites(void);
// void GetPlayerSprite(void);
// void AddMapSprites(void);
// void AddIndoorSprites(void);
// void AddOutdoorSprites(void);
void LoadUsedSpritesGFX(void);
// void LoadMiscTiles(void);
// struct SpriteLoadData SafeGetSprite(uint8_t a);
// struct SpriteLoadData GetSprite(uint8_t a);
// struct SpriteLoadData GetMonSprite(uint8_t a);
bool v_DoesSpriteHaveFacings(uint8_t a);
uint8_t v_GetSpritePalette(uint8_t c);
// void LoadAndSortSprites(void);
// bool AddSpriteGFX(uint8_t a);
// void LoadSpriteGFX(void);
// void SortUsedSprites(void);
// void ArrangeUsedSprites(void);
// uint8_t GetSpriteLength(uint8_t a);
// void GetUsedSprites(void);
void GetUsedSprite(void);
void LoadEmote(uint8_t c);
//#include "data/sprites/player_sprites.h"
//#include "data/sprites/emotes.h"
//#include "data/sprites/sprite_mons.h"
//#include "data/maps/outdoor_sprites.h"
//#include "data/sprites/sprites.h"
