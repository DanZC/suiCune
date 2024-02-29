void ClearSpriteAnims(void);
void ClearSpriteAnims_Conv(void);
void PlaySpriteAnimationsAndDelayFrame(void);
void PlaySpriteAnimationsAndDelayFrame_Conv(void);
void PlaySpriteAnimations(void);
void PlaySpriteAnimations_Conv(void);
void DoNextFrameForAllSprites(void);
void DoNextFrameForAllSprites_Conv(void);
void DoNextFrameForFirst16Sprites(void);
void v_InitSpriteAnimStruct(void);
struct SpriteAnim* v_InitSpriteAnimStruct_Conv(uint8_t a, uint16_t de);
void DeinitializeSprite(void);
void DeinitializeSprite_Conv(struct SpriteAnim* bc);
void DeinitializeAllSprites(void);
void DeinitializeAllSprites_Conv(void);
void UpdateAnimFrame(void);
bool UpdateAnimFrame_Conv(struct SpriteAnim* bc);
void AddOrSubtractY(void);
uint8_t AddOrSubtractY_Conv(uint16_t hl);
uint8_t AddOrSubtractY_Conv2(const uint8_t* hl);
void AddOrSubtractX(void);
uint8_t AddOrSubtractX_Conv(uint16_t hl);
uint8_t AddOrSubtractX_Conv2(const uint8_t* hl);
void GetSpriteOAMAttr(void);
uint8_t GetSpriteOAMAttr_Conv(uint16_t hl);
uint8_t GetSpriteOAMAttr_Conv2(const uint8_t* hl);
void InitSpriteAnimBuffer(void);
void InitSpriteAnimBuffer_Conv(struct SpriteAnim* bc);
void GetSpriteAnimVTile(void);
uint8_t GetSpriteAnimVTile_Conv(uint8_t a);
void v_ReinitSpriteAnimFrame(void);
void v_ReinitSpriteAnimFrame_Conv(struct SpriteAnim* bc, uint8_t a);
void GetSpriteAnimFrame(void);
uint8_t GetSpriteAnimFrame_Conv(struct SpriteAnim* bc);
void GetFrameOAMPointer(void);
uint16_t GetFrameOAMPointer_Conv(uint8_t a);
const struct OAMData* GetFrameOAMPointer_Conv2(uint8_t a);
void UnusedLoadSpriteAnimGFX(void);
void Sprites_Cosine(void);
uint8_t Sprites_Cosine_Conv(uint8_t a, uint8_t d);
void Sprites_Sine(void);
uint8_t Sprites_Sine_Conv(uint8_t a, uint8_t d);
void AnimateEndOfExpBar(void);
void EndOfExpBarGFX(void);
void SGBEndOfExpBarGFX(void);
void ClearSpriteAnims2(void);
void ClearSpriteAnims2_Conv(void);
//#include "data/sprite_anims/sequences.h"
#include "./sprite_anims.h"
//#include "data/sprite_anims/framesets.h"
//#include "data/sprite_anims/oam.h"
//#include "data/sprite_anims/unused_gfx.h"
//#include "gfx/battle/expbarend.2bpp"
//#include "gfx/battle/expbarend_sgb.2bpp"
