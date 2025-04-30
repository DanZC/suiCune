void ClearSpriteAnims(void);
void PlaySpriteAnimationsAndDelayFrame(void);
void PlaySpriteAnimations(void);
void DoNextFrameForAllSprites(void);
void DoNextFrameForFirst16Sprites(void);
struct SpriteAnim* v_InitSpriteAnimStruct(uint8_t a, uint16_t de);
void DeinitializeSprite(struct SpriteAnim* bc);
void DeinitializeAllSprites(void);
bool UpdateAnimFrame(struct SpriteAnim* bc);
uint8_t AddOrSubtractY(const uint8_t* hl);
uint8_t AddOrSubtractX(const uint8_t* hl);
uint8_t GetSpriteOAMAttr(const uint8_t* hl);
void InitSpriteAnimBuffer(struct SpriteAnim* bc);
uint8_t GetSpriteAnimVTile(uint8_t a);
void v_ReinitSpriteAnimFrame(struct SpriteAnim* bc, uint8_t a);
uint8_t GetSpriteAnimFrame(struct SpriteAnim* bc);
void UnusedLoadSpriteAnimGFX(void);
void AnimateEndOfExpBar(void);
extern const char EndOfExpBarGFX[];
extern const char SGBEndOfExpBarGFX[];
void ClearSpriteAnims2(void);
//#include "data/sprite_anims/sequences.h"
#include "./sprite_anims.h"
//#include "data/sprite_anims/framesets.h"
//#include "data/sprite_anims/oam.h"
//#include "data/sprite_anims/unused_gfx.h"
//#include "gfx/battle/expbarend.2bpp"
//#include "gfx/battle/expbarend_sgb.2bpp"
