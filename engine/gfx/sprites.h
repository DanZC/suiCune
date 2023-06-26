void ClearSpriteAnims(void);
void ClearSpriteAnims_Conv(void);
void PlaySpriteAnimationsAndDelayFrame(void);
void PlaySpriteAnimations(void);
void DoNextFrameForAllSprites(void);
void DoNextFrameForFirst16Sprites(void);
void v_InitSpriteAnimStruct(void);
struct SpriteAnim* v_InitSpriteAnimStruct_Conv(uint8_t a, uint16_t de);
void DeinitializeSprite(void);
void DeinitializeAllSprites(void);
void UpdateAnimFrame(void);
void AddOrSubtractY(void);
void AddOrSubtractX(void);
void GetSpriteOAMAttr(void);
void InitSpriteAnimBuffer(void);
void GetSpriteAnimVTile(void);
uint8_t GetSpriteAnimVTile_Conv(uint8_t a);
void v_ReinitSpriteAnimFrame(void);
void v_ReinitSpriteAnimFrame_Conv(struct SpriteAnim* bc, uint8_t a);
void GetSpriteAnimFrame(void);
void GetFrameOAMPointer(void);
void UnusedLoadSpriteAnimGFX(void);
void Sprites_Cosine(void);
void Sprites_Sine(void);
void AnimateEndOfExpBar(void);
void EndOfExpBarGFX(void);
void SGBEndOfExpBarGFX(void);
void ClearSpriteAnims2(void);
//#include "data/sprite_anims/sequences.h"
#include "./sprite_anims.h"
//#include "data/sprite_anims/framesets.h"
//#include "data/sprite_anims/oam.h"
//#include "data/sprite_anims/unused_gfx.h"
//#include "gfx/battle/expbarend.2bpp"
//#include "gfx/battle/expbarend_sgb.2bpp"
