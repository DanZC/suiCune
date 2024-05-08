#include "../../constants.h"
#include "../../gfx/battle_anims.h"

// anim_obj_gfx: MACRO
// ; # tiles, gfx pointer
// 	db \1
// 	dba \2
// ENDM

#define anim_obj_gfx(_tiles, _path) {_tiles, _path}

const struct BattleAnimGFX AnimObjGFX[] = {
// entries correspond to ANIM_GFX_* constants
//table_width 4, AnimObjGFX
    [0x00]                  = anim_obj_gfx( 0, AnimObj00GFX),
    [ANIM_GFX_HIT]          = anim_obj_gfx(21, AnimObjHitGFX),
    [ANIM_GFX_CUT]          = anim_obj_gfx( 6, AnimObjCutGFX),
    [ANIM_GFX_FIRE]         = anim_obj_gfx( 6, AnimObjFireGFX),
    [ANIM_GFX_WATER]        = anim_obj_gfx(20, AnimObjWaterGFX),
    [ANIM_GFX_LIGHTNING]    = anim_obj_gfx(26, AnimObjLightningGFX),
    [ANIM_GFX_PLANT]        = anim_obj_gfx(18, AnimObjPlantGFX),
    [ANIM_GFX_SMOKE]        = anim_obj_gfx(12, AnimObjSmokeGFX),
    [ANIM_GFX_EXPLOSION]    = anim_obj_gfx( 9, AnimObjExplosionGFX),
    [ANIM_GFX_ROCKS]        = anim_obj_gfx(17, AnimObjRocksGFX),
    [ANIM_GFX_ICE]          = anim_obj_gfx( 6, AnimObjIceGFX),
    [ANIM_GFX_POKE_BALL]    = anim_obj_gfx(10, AnimObjPokeBallGFX),
    [ANIM_GFX_POISON]       = anim_obj_gfx( 9, AnimObjPoisonGFX),
    [ANIM_GFX_BUBBLE]       = anim_obj_gfx(13, AnimObjBubbleGFX),
    [ANIM_GFX_NOISE]        = anim_obj_gfx(16, AnimObjNoiseGFX),
    [ANIM_GFX_POWDER]       = anim_obj_gfx( 2, AnimObjPowderGFX),
    [ANIM_GFX_BEAM]         = anim_obj_gfx(11, AnimObjBeamGFX),
    [ANIM_GFX_SPEED]        = anim_obj_gfx( 9, AnimObjSpeedGFX),
    [ANIM_GFX_CHARGE]       = anim_obj_gfx( 9, AnimObjChargeGFX),
    [ANIM_GFX_WIND]         = anim_obj_gfx(19, AnimObjWindGFX),
    [ANIM_GFX_WHIP]         = anim_obj_gfx(10, AnimObjWhipGFX),
    [ANIM_GFX_EGG]          = anim_obj_gfx(12, AnimObjEggGFX),
    [ANIM_GFX_ROPE]         = anim_obj_gfx(18, AnimObjRopeGFX),
    [ANIM_GFX_PSYCHIC]      = anim_obj_gfx(13, AnimObjPsychicGFX),
    [ANIM_GFX_REFLECT]      = anim_obj_gfx(10, AnimObjReflectGFX),
    [ANIM_GFX_STATUS]       = anim_obj_gfx(27, AnimObjStatusGFX),
    [ANIM_GFX_SAND]         = anim_obj_gfx(12, AnimObjSandGFX),
    [ANIM_GFX_WEB]          = anim_obj_gfx(14, AnimObjWebGFX),
    [ANIM_GFX_HAZE]         = anim_obj_gfx(16, AnimObjHazeGFX),
    [ANIM_GFX_HORN]         = anim_obj_gfx( 7, AnimObjHornGFX),
    [ANIM_GFX_FLOWER]       = anim_obj_gfx( 8, AnimObjFlowerGFX),
    [ANIM_GFX_MISC]         = anim_obj_gfx(40, AnimObjMiscGFX),
    [ANIM_GFX_SKY_ATTACK]   = anim_obj_gfx(36, AnimObjSkyAttackGFX),
    [ANIM_GFX_GLOBE]        = anim_obj_gfx(16, AnimObjGlobeGFX),
    [ANIM_GFX_SHAPES]       = anim_obj_gfx(48, AnimObjShapesGFX),
    [ANIM_GFX_OBJECTS]      = anim_obj_gfx(18, AnimObjObjectsGFX),
    [ANIM_GFX_SHINE]        = anim_obj_gfx(38, AnimObjShineGFX),
    [ANIM_GFX_ANGELS]       = anim_obj_gfx(35, AnimObjAngelsGFX),
    [ANIM_GFX_WAVE]         = anim_obj_gfx(18, AnimObjWaveGFX),
    [ANIM_GFX_AEROBLAST]    = anim_obj_gfx(24, AnimObjAeroblastGFX),
    [ANIM_GFX_PLAYERHEAD]   = anim_obj_gfx( 1, NULL),
    [ANIM_GFX_ENEMYFEET]    = anim_obj_gfx( 1, NULL),
};
static_assert(lengthof(AnimObjGFX) == NUM_ANIM_GFX + 1, "");
