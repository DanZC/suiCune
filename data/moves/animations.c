#include "../../constants.h"
#include "../../engine/battle_anims/anim_commands.h"
#include "../../util/battle_anim_macros.h"

static int BattleAnim_MirrorMove(battleanim_s* anim);
static int BattleAnim_SweetScent2(battleanim_s* anim);
static int BattleAnim_ThrowPokeBall(battleanim_s* anim);
static int BattleAnim_SendOutMon(battleanim_s* anim);
static int BattleAnim_ReturnMon(battleanim_s* anim);
static int BattleAnimSub_Return(battleanim_s* anim);
static int BattleAnim_Confused(battleanim_s* anim);
static int BattleAnim_Slp(battleanim_s* anim);
static int BattleAnim_Brn(battleanim_s* anim);
static int BattleAnim_Psn(battleanim_s* anim);
static int BattleAnim_Sap(battleanim_s* anim);
static int BattleAnim_Frz(battleanim_s* anim);
static int BattleAnim_Par(battleanim_s* anim);
static int BattleAnim_InLove(battleanim_s* anim);
static int BattleAnim_InSandstorm(battleanim_s* anim);
static int BattleAnim_InNightmare(battleanim_s* anim);
static int BattleAnim_InWhirlpool(battleanim_s* anim);
static int BattleAnim_HitConfusion(battleanim_s* anim);
static int BattleAnim_Miss(battleanim_s* anim);
static int BattleAnim_EnemyDamage(battleanim_s* anim);
static int BattleAnim_EnemyStatDown(battleanim_s* anim);
static int BattleAnim_PlayerStatDown(battleanim_s* anim);
static int BattleAnim_PlayerDamage(battleanim_s* anim);
static int BattleAnim_Wobble(battleanim_s* anim);
static int BattleAnim_MegaPunch(battleanim_s* anim);
static int BattleAnim_FocusEnergy(battleanim_s* anim);

static int BattleAnim_TargetObj_1Row(battleanim_s* anim);
static int BattleAnim_TargetObj_2Row(battleanim_s* anim);
static int BattleAnim_ShowMon_0(battleanim_s* anim);
static int BattleAnim_ShowMon_1(battleanim_s* anim);
static int BattleAnim_UserObj_1Row(battleanim_s* anim);
static int BattleAnim_UserObj_2Row(battleanim_s* anim);

static int BattleAnimSub_Drain(battleanim_s* anim);
static int BattleAnimSub_EyeBeams(battleanim_s* anim);
static int BattleAnimSub_WarpAway(battleanim_s* anim);
static int BattleAnimSub_Beam(battleanim_s* anim);
static int BattleAnimSub_Explosion1(battleanim_s* anim);
static int BattleAnimSub_Explosion2(battleanim_s* anim);
static int BattleAnimSub_Sound(battleanim_s* anim);
static int BattleAnimSub_Fire(battleanim_s* anim);
static int BattleAnimSub_Ice(battleanim_s* anim);
static int BattleAnimSub_Sludge(battleanim_s* anim);
static int BattleAnimSub_Acid(battleanim_s* anim);
static int BattleAnimSub_Metallic(battleanim_s* anim);
static int BattleAnimSub_SandOrMud(battleanim_s* anim);
static int BattleAnimSub_Glimmer(battleanim_s* anim);
static int BattleAnimSub_Glimmer2(battleanim_s* anim);

#define BattleAnim_0 BattleAnim_MirrorMove
#define BattleAnim_252 BattleAnim_MirrorMove
#define BattleAnim_253 BattleAnim_MirrorMove
#define BattleAnim_254 BattleAnim_MirrorMove
static int BattleAnim_MirrorMove(battleanim_s* anim) {
    ANIM_BEGIN
    anim_ret
    ANIM_END
}

static int BattleAnim_SweetScent2(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_FLOWER, ANIM_GFX_MISC)
    anim_obj(ANIM_OBJ_FLOWER, 64, 96, 0x2)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FLOWER, 64, 80, 0x2)
    anim_wait(64)
    anim_obj(ANIM_OBJ_COTTON, 136, 40, 0x15)
    anim_obj(ANIM_OBJ_COTTON, 136, 40, 0x2a)
    anim_obj(ANIM_OBJ_COTTON, 136, 40, 0x3f)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_ThrowPokeBall(battleanim_s* anim) {
    ANIM_BEGIN
    anim_if_param_equal(NO_ITEM, TheTrainerBlockedTheBall)
    anim_if_param_equal(MASTER_BALL, MasterBall)
    anim_if_param_equal(ULTRA_BALL, UltraBall)
    anim_if_param_equal(GREAT_BALL, GreatBall)
    // any other ball
    anim_2gfx(ANIM_GFX_POKE_BALL, ANIM_GFX_SMOKE)
    anim_sound(6, 2, SFX_THROW_BALL)
    anim_obj(ANIM_OBJ_POKE_BALL, 68, 92, 0x40)
    anim_wait(36)
    anim_obj(ANIM_OBJ_POKE_BALL, 136, 65, 0x0)
    anim_setobj(0x2, 0x7)
    anim_wait(16)
    anim_sound(0, 1, SFX_BALL_POOF)
    anim_obj(ANIM_OBJ_BALL_POOF, 136, 64, 0x10)
    anim_wait(16)
    anim_jump(Shake)

TheTrainerBlockedTheBall:
    anim_2gfx(ANIM_GFX_POKE_BALL, ANIM_GFX_HIT)
    anim_sound(6, 2, SFX_THROW_BALL)
    anim_obj(ANIM_OBJ_POKE_BALL_BLOCKED, 64, 92, 0x20)
    anim_wait(20)
    anim_obj(ANIM_OBJ_HIT_YFIX, 112, 40, 0x0)
    anim_wait(32)
    anim_ret

UltraBall:
	anim_2gfx(ANIM_GFX_POKE_BALL, ANIM_GFX_SMOKE)
    anim_sound(6, 2, SFX_THROW_BALL)
    anim_obj(ANIM_OBJ_POKE_BALL, 68, 92, 0x40)
    anim_wait(36)
    anim_obj(ANIM_OBJ_POKE_BALL, 136, 65, 0x0)
    anim_setobj(0x2, 0x7)
    anim_wait(16)
    anim_sound(0, 1, SFX_BALL_POOF)
    anim_obj(ANIM_OBJ_BALL_POOF, 136, 64, 0x10)
    anim_wait(16)
	anim_jump(Shake)

GreatBall:
    anim_2gfx(ANIM_GFX_POKE_BALL, ANIM_GFX_SMOKE)
    anim_sound(6, 2, SFX_THROW_BALL)
    anim_obj(ANIM_OBJ_POKE_BALL, 68, 92, 0x40)
    anim_wait(36)
    anim_obj(ANIM_OBJ_POKE_BALL, 136, 65, 0x0)
    anim_setobj(0x2, 0x7)
    anim_wait(16)
    anim_sound(0, 1, SFX_BALL_POOF)
    anim_obj(ANIM_OBJ_BALL_POOF, 136, 64, 0x10)
    anim_wait(16)
    anim_jump(Shake)

MasterBall:
    anim_3gfx(ANIM_GFX_POKE_BALL, ANIM_GFX_SMOKE, ANIM_GFX_SPEED)
    anim_sound(6, 2, SFX_THROW_BALL)
    anim_obj(ANIM_OBJ_POKE_BALL, 64, 92, 0x20)
    anim_wait(36)
    anim_obj(ANIM_OBJ_POKE_BALL, 136, 65, 0x0)
    anim_setobj(0x2, 0x7)
    anim_wait(16)
    anim_sound(0, 1, SFX_BALL_POOF)
    anim_obj(ANIM_OBJ_BALL_POOF, 136, 64, 0x10)
    anim_wait(24)
    anim_sound(0, 1, SFX_MASTER_BALL)
    anim_obj(ANIM_OBJ_MASTER_BALL_SPARKLE, 136, 56, 0x30)
    anim_obj(ANIM_OBJ_MASTER_BALL_SPARKLE, 136, 56, 0x31)
    anim_obj(ANIM_OBJ_MASTER_BALL_SPARKLE, 136, 56, 0x32)
    anim_obj(ANIM_OBJ_MASTER_BALL_SPARKLE, 136, 56, 0x33)
    anim_obj(ANIM_OBJ_MASTER_BALL_SPARKLE, 136, 56, 0x34)
    anim_obj(ANIM_OBJ_MASTER_BALL_SPARKLE, 136, 56, 0x35)
    anim_obj(ANIM_OBJ_MASTER_BALL_SPARKLE, 136, 56, 0x36)
    anim_obj(ANIM_OBJ_MASTER_BALL_SPARKLE, 136, 56, 0x37)
    anim_wait(64)
Shake:
    anim_bgeffect(ANIM_BG_RETURN_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(8)
    anim_incobj(2)
    anim_wait(16)
    anim_sound(0, 1, SFX_CHANGE_DEX_MODE)
    anim_incobj(1)
    anim_wait(32)
    anim_sound(0, 1, SFX_BALL_BOUNCE)
    anim_wait(32)
    anim_wait(32)
    anim_wait(32)
    anim_wait(8)
    anim_setvar(0x0)
Loop:
    anim_wait(48)
	anim_checkpokeball
    anim_if_var_equal(0x1, Click)
    anim_if_var_equal(0x2, BreakFree)
    anim_incobj(1)
    anim_sound(0, 1, SFX_BALL_WOBBLE)
    anim_jump(Loop)

Click:
    anim_keepsprites
    anim_ret

BreakFree:
    anim_setobj(0x1, 0xb)
    anim_sound(0, 1, SFX_BALL_POOF)
    anim_obj(ANIM_OBJ_BALL_POOF, 136, 64, 0x10)
    anim_wait(2)
    anim_bgeffect(ANIM_BG_ENTER_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_SendOutMon(battleanim_s* anim) {
    ANIM_BEGIN
    anim_if_param_equal(0x0, Normal)
    anim_if_param_equal(0x1, Shiny)
    anim_if_param_equal(0x2, Unknown)
    anim_1gfx(ANIM_GFX_SMOKE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_BETA_SEND_OUT_MON2, 0x0, BG_EFFECT_USER, 0x0)
    anim_sound(0, 0, SFX_BALL_POOF)
    anim_obj(ANIM_OBJ_BETA_BALL_POOF, 48, 96, 0x0)
    anim_bgeffect(ANIM_BG_ENTER_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(128)
    anim_wait(4)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret

Unknown:
    anim_1gfx(ANIM_GFX_SMOKE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_BETA_SEND_OUT_MON1, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(1)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_sound(0, 0, SFX_BALL_POOF)
    anim_obj(ANIM_OBJ_BETA_BALL_POOF, 48, 96, 0x0)
    anim_incbgeffect(ANIM_BG_BETA_SEND_OUT_MON1)
    anim_wait(96)
    anim_incbgeffect(ANIM_BG_BETA_SEND_OUT_MON1)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret

Shiny:
    anim_1gfx(ANIM_GFX_SPEED)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x3)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SHINY, 48, 96, 0x0)
    anim_wait(4)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SHINY, 48, 96, 0x8)
    anim_wait(4)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SHINY, 48, 96, 0x10)
    anim_wait(4)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SHINY, 48, 96, 0x18)
    anim_wait(4)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SHINY, 48, 96, 0x20)
    anim_wait(4)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SHINY, 48, 96, 0x28)
    anim_wait(4)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SHINY, 48, 96, 0x30)
    anim_wait(4)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SHINY, 48, 96, 0x38)
    anim_wait(32)
    anim_ret

Normal:
    anim_1gfx(ANIM_GFX_SMOKE)
    anim_sound(0, 0, SFX_BALL_POOF)
    anim_obj(ANIM_OBJ_BALL_POOF, 44, 96, 0x0)
    anim_wait(4)
    anim_bgeffect(ANIM_BG_ENTER_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
	anim_ret
    ANIM_END
}

static int BattleAnim_ReturnMon(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 0, SFX_BALL_POOF)
    ANIM_FALLTHROUGH(BattleAnimSub_Return)
}
static int BattleAnimSub_Return(battleanim_s* anim) {
    ANIM_BEGIN
    anim_bgeffect(ANIM_BG_RETURN_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Confused(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_STATUS)
    anim_sound(0, 0, SFX_KINESIS)
    anim_obj(ANIM_OBJ_CHICK, 44, 56, 0x15)
    anim_obj(ANIM_OBJ_CHICK, 44, 56, 0xaa)
    anim_obj(ANIM_OBJ_CHICK, 44, 56, 0xbf)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Slp(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_STATUS)
    anim_sound(0, 0, SFX_TAIL_WHIP)
loop:
    anim_obj(ANIM_OBJ_ASLEEP, 64, 80, 0x0)
    anim_wait(40)
    anim_loop(3, loop)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Brn(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_FIRE)
loop:
    anim_sound(0, 0, SFX_BURN)
    anim_obj(ANIM_OBJ_BURNED, 56, 88, 0x10)
    anim_wait(4)
    anim_loop(3, loop)
    anim_wait(6)
    anim_ret
    ANIM_END
}

static int BattleAnim_Psn(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_POISON)
    anim_sound(0, 0, SFX_POISON)
    anim_obj(ANIM_OBJ_SKULL, 64, 56, 0x0)
    anim_wait(8)
    anim_sound(0, 0, SFX_POISON)
    anim_obj(ANIM_OBJ_SKULL, 48, 56, 0x0)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_Sap(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CHARGE)
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_ABSORB, 128, 48, 0x2)
    anim_wait(6)
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_ABSORB, 136, 64, 0x3)
    anim_wait(6)
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_ABSORB, 136, 32, 0x4)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Frz(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ICE)
    anim_obj(ANIM_OBJ_FROZEN, 44, 110, 0x0)
    anim_sound(0, 0, SFX_SHINE)
    anim_wait(16)
    anim_sound(0, 0, SFX_SHINE)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Par(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_STATUS)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_sound(0, 0, SFX_THUNDERSHOCK)
    anim_obj(ANIM_OBJ_PARALYZED, 20, 88, 0x42)
    anim_obj(ANIM_OBJ_PARALYZED, 76, 88, 0xc2)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_InLove(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_OBJECTS)
    anim_sound(0, 0, SFX_LICK)
    anim_obj(ANIM_OBJ_HEART, 64, 76, 0x0)
    anim_wait(32)
    anim_sound(0, 0, SFX_LICK)
    anim_obj(ANIM_OBJ_HEART, 36, 72, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_InSandstorm(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_POWDER)
    anim_obj(ANIM_OBJ_SANDSTORM, 88, 0, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SANDSTORM, 72, 0, 0x1)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SANDSTORM, 56, 0, 0x2)
loop:
    anim_sound(0, 1, SFX_MENU)
    anim_wait(8)
    anim_loop(6, loop)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_InNightmare(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ANGELS)
    anim_sound(0, 0, SFX_BUBBLEBEAM)
    anim_obj(ANIM_OBJ_IN_NIGHTMARE, 68, 80, 0x0)
    anim_wait(40)
    anim_ret
    ANIM_END
}

static int BattleAnim_InWhirlpool(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WIND)
    anim_bgeffect(ANIM_BG_WHIRLPOOL, 0x0, 0x0, 0x0)
    anim_sound(0, 1, SFX_SURF)
loop:
    anim_obj(ANIM_OBJ_GUST, 132, 72, 0x0)
    anim_wait(6)
    anim_loop(6, loop)
    anim_incbgeffect(ANIM_BG_WHIRLPOOL)
    anim_wait(1)
    anim_ret
    ANIM_END
}

static int BattleAnim_HitConfusion(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 0, SFX_POUND)
    anim_obj(ANIM_OBJ_HIT, 44, 96, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Miss(battleanim_s* anim) {
    ANIM_BEGIN
    anim_ret
    ANIM_END
}

static int BattleAnim_EnemyDamage(battleanim_s* anim) {
    ANIM_BEGIN
loop:
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(5)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(5)
    anim_loop(3, loop)
    anim_ret
    ANIM_END
}

static int BattleAnim_EnemyStatDown(battleanim_s* anim) {
    ANIM_BEGIN
    anim_call(BattleAnim_UserObj_1Row)
    anim_bgeffect(ANIM_BG_VIBRATE_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(40)
    anim_call(BattleAnim_ShowMon_1)
    anim_wait(1)
    anim_ret
    ANIM_END
}

static int BattleAnim_PlayerStatDown(battleanim_s* anim) {
    ANIM_BEGIN
    anim_call(BattleAnim_UserObj_1Row)
    anim_bgeffect(ANIM_BG_WOBBLE_PLAYER, 0x0, 0x0, 0x0)
    anim_wait(40)
    anim_call(BattleAnim_ShowMon_1)
    anim_wait(1)
    anim_ret
    ANIM_END
}

static int BattleAnim_PlayerDamage(battleanim_s* anim) {
    ANIM_BEGIN
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_Y, 0x20, 0x2, 0x20)
    anim_wait(40)
    anim_ret
    ANIM_END
}

static int BattleAnim_Wobble(battleanim_s* anim) {
    ANIM_BEGIN
    anim_bgeffect(ANIM_BG_WOBBLE_SCREEN, 0x0, 0x0, 0x0)
    anim_wait(40)
    anim_ret
    ANIM_END
}

static int BattleAnim_Shake(battleanim_s* anim) {
    ANIM_BEGIN
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x20, 0x2, 0x40)
    anim_wait(40)
    anim_ret
    ANIM_END
}

static int BattleAnim_Pound(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_POUND)
    anim_obj(ANIM_OBJ_PALM, 136, 56, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_KarateChop(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_KARATE_CHOP)
    anim_obj(ANIM_OBJ_PALM, 136, 40, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 40, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_KARATE_CHOP)
    anim_obj(ANIM_OBJ_PALM, 136, 44, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 44, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_KARATE_CHOP)
    anim_obj(ANIM_OBJ_PALM, 136, 48, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 48, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Doubleslap(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_if_param_equal(0x1, alternate)
    anim_sound(0, 1, SFX_DOUBLESLAP)
    anim_obj(ANIM_OBJ_PALM, 144, 48, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 48, 0x0)
    anim_wait(8)
	anim_ret

alternate:
    anim_sound(0, 1, SFX_DOUBLESLAP)
    anim_obj(ANIM_OBJ_PALM, 120, 48, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 120, 48, 0x0)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_CometPunch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_if_param_equal(0x1, alternate)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_PUNCH, 144, 48, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 48, 0x0)
    anim_wait(8)
	anim_ret

alternate:
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_PUNCH, 120, 64, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 120, 64, 0x0)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_MegaPunch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x40, 0x2, 0x0)
    anim_wait(48)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x3)
loop:
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_PUNCH, 136, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_PUNCH, 136, 56, 0x0)
    anim_wait(6)
    anim_loop(3, loop)
    anim_ret
    ANIM_END
}

static int BattleAnim_Stomp(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_STOMP)
    anim_obj(ANIM_OBJ_KICK, 136, 40, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 40, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_STOMP)
    anim_obj(ANIM_OBJ_KICK, 136, 44, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 44, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_STOMP)
    anim_obj(ANIM_OBJ_KICK, 136, 48, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 48, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_DoubleKick(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_if_param_equal(0x1, alternate)
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_KICK, 144, 48, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 48, 0x0)
    anim_wait(8)
    anim_ret

alternate:
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_KICK, 120, 64, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 120, 64, 0x0)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_JumpKick(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_if_param_equal(0x1, alternate)
    anim_sound(0, 1, SFX_JUMP_KICK)
    anim_obj(ANIM_OBJ_KICK, 112, 72, 0x0)
    anim_obj(ANIM_OBJ_KICK, 100, 60, 0x0)
    anim_setobj(0x1, 0x2)
    anim_setobj(0x2, 0x2)
    anim_wait(24)
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_HIT, 136, 48, 0x0)
    anim_wait(16)
    anim_ret

alternate:
    anim_wait(8)
    anim_sound(0, 0, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_HIT, 44, 88, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_HiJumpKick(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x40, 0x2, 0x0)
    anim_if_param_equal(0x1, alternate)
    anim_wait(32)
    anim_sound(0, 1, SFX_JUMP_KICK)
    anim_obj(ANIM_OBJ_KICK, 112, 72, 0x0)
    anim_setobj(0x1, 0x2)
    anim_wait(16)
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_HIT, 136, 48, 0x0)
    anim_wait(16)
	anim_ret

alternate:
    anim_wait(16)
    anim_sound(0, 0, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_HIT, 44, 88, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_RollingKick(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_KICK, 112, 56, 0x0)
    anim_setobj(0x1, 0x3)
    anim_wait(12)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 48, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_MegaKick(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x40, 0x2, 0x0)
    anim_wait(67)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x3)
loop:
    anim_sound(0, 1, SFX_MEGA_KICK)
    anim_obj(ANIM_OBJ_KICK, 136, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_KICK, 136, 56, 0x0)
    anim_wait(6)
    anim_loop(3, loop)
    anim_ret
    ANIM_END
}

static int BattleAnim_HyperFang(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x20, 0x1, 0x0)
    anim_sound(0, 1, SFX_BITE)
    anim_obj(ANIM_OBJ_FANG, 136, 56, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_SuperFang(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x40, 0x2, 0x0)
    anim_wait(48)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x3)
loop:
    anim_sound(0, 1, SFX_BITE)
    anim_obj(ANIM_OBJ_FANG, 136, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_FANG, 136, 56, 0x0)
    anim_wait(6)
    anim_loop(3, loop)
    anim_ret
    ANIM_END
}

static int BattleAnim_Ember(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_FIRE)
    anim_sound(6, 2, SFX_EMBER)
    anim_obj(ANIM_OBJ_EMBER, 64, 96, 0x12)
    anim_wait(4)
    anim_sound(6, 2, SFX_EMBER)
    anim_obj(ANIM_OBJ_EMBER, 64, 100, 0x14)
    anim_wait(4)
    anim_sound(6, 2, SFX_EMBER)
    anim_obj(ANIM_OBJ_EMBER, 64, 84, 0x13)
    anim_wait(16)
    anim_incobj(1)
    anim_incobj(2)
    anim_incobj(3)
    anim_sound(0, 1, SFX_EMBER)
    anim_obj(ANIM_OBJ_EMBER, 120, 68, 0x30)
    anim_obj(ANIM_OBJ_EMBER, 132, 68, 0x30)
    anim_obj(ANIM_OBJ_EMBER, 144, 68, 0x30)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_FirePunch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HIT, ANIM_GFX_FIRE)
    anim_obj(ANIM_OBJ_PUNCH_SHAKE, 136, 56, 0x43)
    anim_call(BattleAnimSub_Fire)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_FireSpin(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_FIRE)
loop:
    anim_sound(6, 2, SFX_EMBER)
    anim_obj(ANIM_OBJ_FIRE_SPIN, 64, 88, 0x4)
    anim_wait(2)
    anim_sound(6, 2, SFX_EMBER)
    anim_obj(ANIM_OBJ_FIRE_SPIN, 64, 96, 0x3)
    anim_wait(2)
    anim_sound(6, 2, SFX_EMBER)
    anim_obj(ANIM_OBJ_FIRE_SPIN, 64, 88, 0x3)
    anim_wait(2)
    anim_sound(6, 2, SFX_EMBER)
    anim_obj(ANIM_OBJ_FIRE_SPIN, 64, 96, 0x4)
    anim_wait(2)
    anim_loop(2, loop)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_DragonRage(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_FIRE)
loop:
    anim_sound(6, 2, SFX_EMBER)
    anim_obj(ANIM_OBJ_DRAGON_RAGE, 64, 92, 0x0)
    anim_wait(3)
    anim_loop(16, loop)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Flamethrower(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_FIRE)
    anim_sound(6, 2, SFX_EMBER)
    anim_obj(ANIM_OBJ_FLAMETHROWER, 64, 92, 0x3)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FLAMETHROWER, 75, 86, 0x5)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FLAMETHROWER, 85, 81, 0x7)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FLAMETHROWER, 96, 76, 0x9)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FLAMETHROWER, 106, 71, 0xb)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FLAMETHROWER, 116, 66, 0xc)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FLAMETHROWER, 126, 61, 0xa)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FLAMETHROWER, 136, 56, 0x8)
    anim_wait(16)
loop:
    anim_sound(0, 1, SFX_EMBER)
    anim_wait(16)
    anim_loop(6, loop)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_FireBlast(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_FIRE)
loop1:
    anim_sound(6, 2, SFX_EMBER)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 64, 92, 0x7)
    anim_wait(6)
    anim_loop(10, loop1)
loop2:
    anim_sound(0, 1, SFX_EMBER)
    anim_wait(8)
    anim_loop(10, loop2)
    anim_incobj(1)
    anim_incobj(2)
    anim_incobj(3)
    anim_incobj(4)
    anim_incobj(5)
    anim_incobj(6)
    anim_incobj(7)
    anim_incobj(8)
    anim_incobj(9)
    anim_incobj(10)
    anim_wait(2)
loop3:
    anim_sound(0, 1, SFX_EMBER)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 56, 0x1)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 56, 0x2)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 56, 0x3)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 56, 0x4)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 56, 0x5)
    anim_wait(16)
    anim_loop(2, loop3)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_IcePunch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HIT, ANIM_GFX_ICE)
    anim_obj(ANIM_OBJ_PUNCH_SHAKE, 136, 56, 0x43)
    anim_call(BattleAnimSub_Ice)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_IceBeam(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ICE)
loop:
    anim_sound(6, 2, SFX_SHINE)
    anim_obj(ANIM_OBJ_ICE_BEAM, 64, 92, 0x4)
    anim_wait(4)
    anim_loop(5, loop)
    anim_obj(ANIM_OBJ_ICE_BUILDUP, 136, 74, 0x10)
loop2:
    anim_sound(6, 2, SFX_SHINE)
    anim_obj(ANIM_OBJ_ICE_BEAM, 64, 92, 0x4)
    anim_wait(4)
    anim_loop(15, loop2)
    anim_wait(48)
    anim_sound(0, 1, SFX_SHINE)
    anim_wait(8)
    anim_sound(0, 1, SFX_SHINE)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_Blizzard(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ICE)
loop:
    anim_sound(6, 2, SFX_SHINE)
    anim_obj(ANIM_OBJ_BLIZZARD, 64, 88, 0x63)
    anim_wait(2)
    anim_sound(6, 2, SFX_SHINE)
    anim_obj(ANIM_OBJ_BLIZZARD, 64, 80, 0x64)
    anim_wait(2)
    anim_sound(6, 2, SFX_SHINE)
    anim_obj(ANIM_OBJ_BLIZZARD, 64, 96, 0x63)
    anim_wait(2)
    anim_loop(3, loop)
    anim_bgeffect(ANIM_BG_WHITE_HUES, 0x0, 0x8, 0x0)
    anim_wait(32)
    anim_obj(ANIM_OBJ_ICE_BUILDUP, 136, 74, 0x10)
    anim_wait(128)
    anim_sound(0, 1, SFX_SHINE)
    anim_wait(8)
    anim_sound(0, 1, SFX_SHINE)
    anim_wait(24)
    anim_ret
    ANIM_END
}

static int BattleAnim_Bubble(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BUBBLE)
    anim_sound(32, 2, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_BUBBLE, 64, 92, 0xc1)
    anim_wait(6)
    anim_sound(32, 2, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_BUBBLE, 64, 92, 0xe1)
    anim_wait(6)
    anim_sound(32, 2, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_BUBBLE, 64, 92, 0xd1)
    anim_wait(128)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Bubblebeam(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BUBBLE)
loop:
    anim_sound(16, 2, SFX_BUBBLEBEAM)
    anim_obj(ANIM_OBJ_BUBBLE, 64, 92, 0x92)
    anim_wait(6)
    anim_sound(16, 2, SFX_BUBBLEBEAM)
    anim_obj(ANIM_OBJ_BUBBLE, 64, 92, 0xb3)
    anim_wait(6)
    anim_sound(16, 2, SFX_BUBBLEBEAM)
    anim_obj(ANIM_OBJ_BUBBLE, 64, 92, 0xf4)
    anim_wait(8)
    anim_loop(3, loop)
    anim_wait(64)
	anim_clearobjs
    anim_bgeffect(ANIM_BG_START_WATER, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(1)
    anim_call(BattleAnim_UserObj_2Row)
    anim_bgeffect(ANIM_BG_WATER, 0x1c, 0x0, 0x0)
    anim_wait(19)
    anim_call(BattleAnim_ShowMon_1)
    anim_bgeffect(ANIM_BG_END_WATER, 0x0, 0x0, 0x0)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_WaterGun(battleanim_s* anim) {
    ANIM_BEGIN
    anim_bgeffect(ANIM_BG_START_WATER, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_1gfx(ANIM_GFX_WATER)
    anim_call(BattleAnim_UserObj_2Row)
    anim_sound(16, 2, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_WATER_GUN, 64, 88, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_WATER_GUN, 64, 76, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_WATER_GUN, 64, 82, 0x0)
    anim_wait(24)
    anim_bgeffect(ANIM_BG_WATER, 0x1c, 0x0, 0x0)
    anim_wait(8)
    anim_bgeffect(ANIM_BG_WATER, 0x8, 0x0, 0x0)
    anim_wait(8)
    anim_bgeffect(ANIM_BG_WATER, 0x30, 0x0, 0x0)
    anim_wait(32)
    anim_call(BattleAnim_ShowMon_1)
    anim_bgeffect(ANIM_BG_END_WATER, 0x0, 0x0, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_HydroPump(battleanim_s* anim) {
    ANIM_BEGIN
    anim_bgeffect(ANIM_BG_START_WATER, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_1gfx(ANIM_GFX_WATER)
    anim_call(BattleAnim_UserObj_2Row)
    anim_sound(0, 1, SFX_HYDRO_PUMP)
    anim_obj(ANIM_OBJ_HYDRO_PUMP, 108, 72, 0x0)
    anim_bgeffect(ANIM_BG_WATER, 0x1c, 0x0, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_HYDRO_PUMP)
    anim_obj(ANIM_OBJ_HYDRO_PUMP, 116, 72, 0x0)
    anim_bgeffect(ANIM_BG_WATER, 0x8, 0x0, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_HYDRO_PUMP)
    anim_obj(ANIM_OBJ_HYDRO_PUMP, 124, 72, 0x0)
    anim_bgeffect(ANIM_BG_WATER, 0x30, 0x0, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_HYDRO_PUMP)
    anim_obj(ANIM_OBJ_HYDRO_PUMP, 132, 72, 0x0)
    anim_bgeffect(ANIM_BG_WATER, 0x1c, 0x0, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_HYDRO_PUMP)
    anim_obj(ANIM_OBJ_HYDRO_PUMP, 140, 72, 0x0)
    anim_bgeffect(ANIM_BG_WATER, 0x8, 0x0, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_HYDRO_PUMP)
    anim_obj(ANIM_OBJ_HYDRO_PUMP, 148, 72, 0x0)
    anim_bgeffect(ANIM_BG_WATER, 0x30, 0x0, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_HYDRO_PUMP)
    anim_obj(ANIM_OBJ_HYDRO_PUMP, 156, 72, 0x0)
    anim_bgeffect(ANIM_BG_WATER, 0x1c, 0x0, 0x0)
    anim_wait(32)
    anim_call(BattleAnim_ShowMon_1)
    anim_bgeffect(ANIM_BG_END_WATER, 0x0, 0x0, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Surf(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BUBBLE)
    anim_bgeffect(ANIM_BG_SURF, 0x0, 0x0, 0x0)
    anim_obj(ANIM_OBJ_SURF, 88, 104, 0x8)
loop:
    anim_sound(0, 1, SFX_SURF)
    anim_wait(32)
    anim_loop(4, loop)
    anim_incobj(1)
    anim_wait(56)
    anim_ret
    ANIM_END
}

static int BattleAnim_VineWhip(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WHIP)
    anim_sound(0, 1, SFX_VINE_WHIP)
    anim_obj(ANIM_OBJ_VINE_WHIP2, 116, 52, 0x80)
    anim_wait(4)
    anim_sound(0, 1, SFX_VINE_WHIP)
    anim_obj(ANIM_OBJ_VINE_WHIP1, 128, 60, 0x0)
    anim_wait(4)
    anim_incobj(1)
    anim_wait(4)
    anim_ret
    ANIM_END
}

static int BattleAnim_LeechSeed(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_PLANT)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_obj(ANIM_OBJ_LEECH_SEED, 48, 80, 0x20)
    anim_wait(8)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_obj(ANIM_OBJ_LEECH_SEED, 48, 80, 0x30)
    anim_wait(8)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_obj(ANIM_OBJ_LEECH_SEED, 48, 80, 0x28)
    anim_wait(32)
    anim_sound(0, 1, SFX_CHARGE)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_RazorLeaf(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_PLANT)
    anim_sound(0, 0, SFX_VINE_WHIP)
    anim_obj(ANIM_OBJ_RAZOR_LEAF, 48, 80, 0x28)
    anim_obj(ANIM_OBJ_RAZOR_LEAF, 48, 80, 0x5c)
    anim_obj(ANIM_OBJ_RAZOR_LEAF, 48, 80, 0x10)
    anim_obj(ANIM_OBJ_RAZOR_LEAF, 48, 80, 0xe8)
    anim_obj(ANIM_OBJ_RAZOR_LEAF, 48, 80, 0x9c)
    anim_obj(ANIM_OBJ_RAZOR_LEAF, 48, 80, 0xd0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_RAZOR_LEAF, 48, 80, 0x1c)
    anim_obj(ANIM_OBJ_RAZOR_LEAF, 48, 80, 0x50)
    anim_obj(ANIM_OBJ_RAZOR_LEAF, 48, 80, 0xdc)
    anim_obj(ANIM_OBJ_RAZOR_LEAF, 48, 80, 0x90)
    anim_wait(80)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_incobj(3)
    anim_wait(2)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_incobj(5)
    anim_wait(2)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_incobj(7)
    anim_wait(2)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_incobj(9)
    anim_wait(2)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_incobj(1)
    anim_wait(2)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_incobj(2)
    anim_wait(2)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_incobj(4)
    anim_wait(2)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_incobj(6)
    anim_wait(2)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_incobj(8)
    anim_wait(2)
    anim_sound(16, 2, SFX_VINE_WHIP)
    anim_incobj(10)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Solarbeam(battleanim_s* anim) {
    ANIM_BEGIN
    anim_if_param_equal(0x0, FireSolarBeam)
    // charge turn
    anim_1gfx(ANIM_GFX_CHARGE)
    anim_sound(0, 0, SFX_CHARGE)
    anim_obj(ANIM_OBJ_ABSORB_CENTER, 48, 84, 0x0)
    anim_obj(ANIM_OBJ_SOLAR_BEAM_CHARGE, 48, 84, 0x0)
    anim_obj(ANIM_OBJ_SOLAR_BEAM_CHARGE, 48, 84, 0x8)
    anim_obj(ANIM_OBJ_SOLAR_BEAM_CHARGE, 48, 84, 0x10)
    anim_obj(ANIM_OBJ_SOLAR_BEAM_CHARGE, 48, 84, 0x18)
    anim_obj(ANIM_OBJ_SOLAR_BEAM_CHARGE, 48, 84, 0x20)
    anim_obj(ANIM_OBJ_SOLAR_BEAM_CHARGE, 48, 84, 0x28)
    anim_obj(ANIM_OBJ_SOLAR_BEAM_CHARGE, 48, 84, 0x30)
    anim_obj(ANIM_OBJ_SOLAR_BEAM_CHARGE, 48, 84, 0x38)
    anim_wait(104)
    anim_bgeffect(ANIM_BG_FLASH_WHITE, 0x0, 0x4, 0x2)
    anim_wait(64)
    anim_ret

FireSolarBeam:
    anim_1gfx(ANIM_GFX_BEAM)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_call(BattleAnimSub_Beam)
    anim_wait(48)
	anim_ret
    ANIM_END
}

static int BattleAnim_Thunderpunch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HIT, ANIM_GFX_LIGHTNING)
    anim_obj(ANIM_OBJ_PUNCH_SHAKE, 136, 56, 0x43)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x2)
    anim_sound(0, 1, SFX_THUNDER)
    anim_obj(ANIM_OBJ_THUNDER3, 152, 68, 0x0)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Thundershock(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_LIGHTNING, ANIM_GFX_EXPLOSION)
    anim_obj(ANIM_OBJ_THUNDERSHOCK_BALL, 136, 56, 0x2)
    anim_wait(16)
    anim_sound(0, 1, SFX_THUNDERSHOCK)
    anim_obj(ANIM_OBJ_SPARKS_CIRCLE, 136, 56, 0x0)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Thunderbolt(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_LIGHTNING, ANIM_GFX_EXPLOSION)
    anim_obj(ANIM_OBJ_THUNDERBOLT_BALL, 136, 56, 0x2)
    anim_wait(16)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x2)
    anim_sound(0, 1, SFX_THUNDERSHOCK)
    anim_obj(ANIM_OBJ_SPARKS_CIRCLE_BIG, 136, 56, 0x0)
    anim_wait(64)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x2)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_ThunderWave(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_LIGHTNING)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x3)
    anim_sound(0, 1, SFX_THUNDERSHOCK)
    anim_obj(ANIM_OBJ_THUNDER_WAVE, 136, 56, 0x0)
    anim_wait(20)
    anim_bgp(0x1b)
    anim_incobj(1)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Thunder(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_LIGHTNING)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x6, 0x20)
    anim_sound(0, 1, SFX_THUNDER)
    anim_obj(ANIM_OBJ_THUNDER2, 120, 68, 0x0)
    anim_wait(16)
    anim_sound(0, 1, SFX_THUNDER)
    anim_obj(ANIM_OBJ_THUNDER3, 152, 68, 0x0)
    anim_wait(16)
    anim_sound(0, 1, SFX_THUNDER)
    anim_obj(ANIM_OBJ_THUNDER1, 136, 68, 0x0)
    anim_wait(48)
    anim_ret
    ANIM_END
}

static int BattleAnim_RazorWind(battleanim_s* anim) {
    ANIM_BEGIN
    anim_if_param_equal_(0x1, BattleAnim_FocusEnergy)
    anim_1gfx(ANIM_GFX_WHIP)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x1, 0x0)
loop:
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x2)
    anim_sound(0, 1, SFX_RAZOR_WIND)
    anim_obj(ANIM_OBJ_RAZOR_WIND2, 152, 40, 0x3)
    anim_wait(4)
    anim_sound(0, 1, SFX_RAZOR_WIND)
    anim_obj(ANIM_OBJ_RAZOR_WIND2, 136, 56, 0x3)
    anim_wait(4)
    anim_sound(0, 1, SFX_RAZOR_WIND)
    anim_obj(ANIM_OBJ_RAZOR_WIND2, 152, 64, 0x3)
    anim_wait(4)
    anim_sound(0, 1, SFX_RAZOR_WIND)
    anim_obj(ANIM_OBJ_RAZOR_WIND1, 120, 40, 0x83)
    anim_wait(4)
    anim_sound(0, 1, SFX_RAZOR_WIND)
    anim_obj(ANIM_OBJ_RAZOR_WIND1, 120, 64, 0x83)
    anim_wait(4)
    anim_loop(3, loop)
    anim_wait(24)
    anim_ret
    ANIM_END
}

// static int BattleAnim_Sonicboom_JP(battleanim_s* anim) {
//     ANIM_BEGIN // unreferenced
//     anim_2gfx(ANIM_GFX_WHIP, ANIM_GFX_HIT)
// loop:
//     anim_sound(3, 0, SFX_RAZOR_WIND)
//     anim_obj(ANIM_OBJ_SONICBOOM_JP, 64, 80, 0x3)
//     anim_wait(8)
//     anim_sound(3, 0, SFX_RAZOR_WIND)
//     anim_obj(ANIM_OBJ_SONICBOOM_JP, 64, 88, 0x2)
//     anim_wait(8)
//     anim_sound(3, 0, SFX_RAZOR_WIND)
//     anim_obj(ANIM_OBJ_SONICBOOM_JP, 64, 96, 0x4)
//     anim_wait(8)
//     anim_loop(2, loop)
//     anim_wait(32)
//     anim_incobj(1)
//     anim_incobj(2)
//     anim_incobj(3)
//     anim_incobj(4)
//     anim_incobj(5)
//     anim_incobj(6)
//     anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
//     anim_wait(16)
//     anim_ret
//     ANIM_END
// }

#define BattleAnim_Gust BattleAnim_Sonicboom
static int BattleAnim_Sonicboom(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_WIND, ANIM_GFX_HIT)
loop:
    anim_sound(0, 1, SFX_RAZOR_WIND)
    anim_obj(ANIM_OBJ_GUST, 136, 72, 0x0)
    anim_wait(6)
    anim_loop(9, loop)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 64, 0x18)
    anim_wait(8)
    anim_obj(ANIM_OBJ_HIT_YFIX, 128, 32, 0x18)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Selfdestruct(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_EXPLOSION)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x24)
    anim_if_param_equal(0x1, loop)
    anim_call(BattleAnimSub_Explosion2)
    anim_wait(16)
    anim_ret

loop:
    anim_call(BattleAnimSub_Explosion1)
    anim_wait(5)
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_loop(2, loop)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Explosion(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_EXPLOSION)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x60, 0x4, 0x10)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x24)
    anim_if_param_equal(0x1, loop)
    anim_call(BattleAnimSub_Explosion2)
    anim_wait(16)
    anim_ret

loop:
    anim_call(BattleAnimSub_Explosion1)
    anim_wait(5)
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_loop(2, loop)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Acid(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_POISON)
    anim_call(BattleAnimSub_Acid)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_RockThrow(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ROCKS)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x60, 0x1, 0x0)
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 128, 64, 0x40)
    anim_wait(2)
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_BIG_ROCK, 120, 68, 0x30)
    anim_wait(2)
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 152, 68, 0x30)
    anim_wait(2)
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_BIG_ROCK, 144, 64, 0x40)
    anim_wait(2)
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 136, 68, 0x30)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_RockSlide(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ROCKS)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0xc0, 0x1, 0x0)
loop:
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 128, 64, 0x40)
    anim_wait(4)
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_BIG_ROCK, 120, 68, 0x30)
    anim_wait(4)
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 152, 68, 0x30)
    anim_wait(4)
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_BIG_ROCK, 144, 64, 0x40)
    anim_wait(4)
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 136, 68, 0x30)
    anim_wait(16)
    anim_loop(4, loop)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Sing(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_NOISE)
    anim_sound(16, 2, SFX_SING)
loop:
    anim_obj(ANIM_OBJ_SING, 64, 92, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SING, 64, 92, 0x1)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SING, 64, 92, 0x2)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SING, 64, 92, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SING, 64, 92, 0x2)
    anim_wait(8)
    anim_loop(4, loop)
    anim_wait(64)
    anim_ret
    ANIM_END
}

#define BattleAnim_Poisonpowder BattleAnim_StunSpore
#define BattleAnim_SleepPowder BattleAnim_StunSpore
#define BattleAnim_Spore BattleAnim_StunSpore
static int BattleAnim_StunSpore(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_POWDER)
loop:
    anim_sound(0, 1, SFX_POWDER)
    anim_obj(ANIM_OBJ_POWDER, 104, 16, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_POWDER)
    anim_obj(ANIM_OBJ_POWDER, 136, 16, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_POWDER)
    anim_obj(ANIM_OBJ_POWDER, 112, 16, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_POWDER)
    anim_obj(ANIM_OBJ_POWDER, 128, 16, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_POWDER)
    anim_obj(ANIM_OBJ_POWDER, 120, 16, 0x0)
    anim_wait(4)
    anim_loop(2, loop)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_HyperBeam(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BEAM)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x30, 0x4, 0x10)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x40)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_call(BattleAnimSub_Beam)
    anim_wait(48)
    anim_ret
    ANIM_END
}

static int BattleAnim_AuroraBeam(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BEAM)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_ALTERNATE_HUES, 0x0, 0x2, 0x0)
    anim_wait(64)
    anim_call(BattleAnimSub_Beam)
    anim_wait(48)
    anim_incobj(5)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Vicegrip(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CUT)
    anim_sound(0, 1, SFX_VICEGRIP)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 152, 40, 0x0)
    anim_obj(ANIM_OBJ_CUT_UP_RIGHT, 120, 72, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Scratch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CUT)
    anim_sound(0, 1, SFX_SCRATCH)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 144, 48, 0x0)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 140, 44, 0x0)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 136, 40, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_FurySwipes(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CUT)
    anim_if_param_equal(0x1, alternate)
    anim_sound(0, 1, SFX_SCRATCH)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 144, 48, 0x0)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 140, 44, 0x0)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 136, 40, 0x0)
    anim_sound(0, 1, SFX_SCRATCH)
    anim_wait(32)
    anim_ret

alternate:
    anim_sound(0, 1, SFX_SCRATCH)
    anim_obj(ANIM_OBJ_CUT_DOWN_RIGHT, 120, 48, 0x0)
    anim_obj(ANIM_OBJ_CUT_DOWN_RIGHT, 124, 44, 0x0)
    anim_obj(ANIM_OBJ_CUT_DOWN_RIGHT, 128, 40, 0x0)
    anim_sound(0, 1, SFX_SCRATCH)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Cut(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CUT)
    anim_sound(0, 1, SFX_CUT)
    anim_obj(ANIM_OBJ_CUT_LONG_DOWN_LEFT, 152, 40, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Slash(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CUT)
    anim_sound(0, 1, SFX_CUT)
    anim_obj(ANIM_OBJ_CUT_LONG_DOWN_LEFT, 152, 40, 0x0)
    anim_obj(ANIM_OBJ_CUT_LONG_DOWN_LEFT, 148, 36, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Clamp(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_CUT, ANIM_GFX_HIT)
    anim_obj(ANIM_OBJ_CLAMP, 136, 56, 0xa0)
    anim_obj(ANIM_OBJ_CLAMP, 136, 56, 0x20)
    anim_wait(16)
    anim_sound(0, 1, SFX_BITE)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 48, 0x18)
    anim_wait(32)
    anim_sound(0, 1, SFX_BITE)
    anim_obj(ANIM_OBJ_HIT_YFIX, 128, 64, 0x18)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Bite(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_CUT, ANIM_GFX_HIT)
    anim_obj(ANIM_OBJ_BITE, 136, 56, 0x98)
    anim_obj(ANIM_OBJ_BITE, 136, 56, 0x18)
    anim_wait(8)
    anim_sound(0, 1, SFX_BITE)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 48, 0x18)
    anim_wait(16)
    anim_sound(0, 1, SFX_BITE)
    anim_obj(ANIM_OBJ_HIT_YFIX, 128, 64, 0x18)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_Teleport(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SPEED)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_TELEPORT, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(3)
    anim_incbgeffect(ANIM_BG_TELEPORT)
    anim_call(BattleAnim_ShowMon_0)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x1, 0x0)
    anim_call(BattleAnimSub_WarpAway)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Fly(battleanim_s* anim) {
    ANIM_BEGIN
    anim_if_param_equal(0x1, turn1)
    anim_if_param_equal(0x2, miss)
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_WING_ATTACK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(32)
miss:
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_ret

turn1:
    anim_1gfx(ANIM_GFX_SPEED)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x1, 0x0)
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_call(BattleAnimSub_WarpAway)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_DoubleTeam(battleanim_s* anim) {
    ANIM_BEGIN
    anim_call(BattleAnim_TargetObj_2Row)
    anim_sound(0, 0, SFX_PSYBEAM)
    anim_bgeffect(ANIM_BG_DOUBLE_TEAM, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(96)
    anim_incbgeffect(ANIM_BG_DOUBLE_TEAM)
    anim_wait(24)
    anim_incbgeffect(ANIM_BG_DOUBLE_TEAM)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Recover(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BUBBLE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_sound(0, 0, SFX_FULL_HEAL)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING, 0x0, BG_EFFECT_USER, 0x40)
    anim_obj(ANIM_OBJ_RECOVER, 44, 88, 0x30)
    anim_obj(ANIM_OBJ_RECOVER, 44, 88, 0x31)
    anim_obj(ANIM_OBJ_RECOVER, 44, 88, 0x32)
    anim_obj(ANIM_OBJ_RECOVER, 44, 88, 0x33)
    anim_obj(ANIM_OBJ_RECOVER, 44, 88, 0x34)
    anim_obj(ANIM_OBJ_RECOVER, 44, 88, 0x35)
    anim_obj(ANIM_OBJ_RECOVER, 44, 88, 0x36)
    anim_obj(ANIM_OBJ_RECOVER, 44, 88, 0x37)
    anim_wait(64)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Absorb(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CHARGE)
    anim_obj(ANIM_OBJ_ABSORB_CENTER, 44, 88, 0x0)
loop:
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_ABSORB, 128, 48, 0x2)
    anim_wait(6)
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_ABSORB, 136, 64, 0x3)
    anim_wait(6)
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_ABSORB, 136, 32, 0x4)
    anim_wait(6)
    anim_loop(5, loop)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_MegaDrain(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CHARGE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_FADE_MONS_TO_BLACK_REPEATING, 0x0, BG_EFFECT_TARGET, 0x10)
    anim_setvar(0x0)
loop:
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_ABSORB, 128, 48, 0x2)
    anim_wait(6)
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_ABSORB, 136, 64, 0x3)
    anim_wait(6)
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_obj(ANIM_OBJ_ABSORB, 136, 32, 0x4)
    anim_wait(6)
    anim_incvar
    anim_if_var_equal(0x7, done)
    anim_if_var_equal(0x2, spawn)
    anim_jump(loop)

spawn:
    anim_obj(ANIM_OBJ_ABSORB_CENTER, 44, 88, 0x0)
    anim_jump(loop)

done:
    anim_wait(32)
    anim_incbgeffect(ANIM_BG_FADE_MONS_TO_BLACK_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_EggBomb(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_EGG, ANIM_GFX_EXPLOSION)
    anim_sound(0, 0, SFX_SWITCH_POKEMON)
    anim_obj(ANIM_OBJ_EGG, 44, 104, 0x1)
    anim_wait(128)
    anim_wait(96)
    anim_incobj(1)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x3)
    anim_sound(0, 1, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION2, 128, 64, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION2, 144, 68, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION2, 136, 72, 0x0)
    anim_wait(24)
    anim_ret
    ANIM_END
}

static int BattleAnim_Softboiled(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_EGG, ANIM_GFX_BUBBLE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_sound(0, 0, SFX_SWITCH_POKEMON)
    anim_obj(ANIM_OBJ_EGG, 44, 104, 0x6)
    anim_wait(128)
    anim_incobj(2)
    anim_obj(ANIM_OBJ_EGG, 76, 104, 0xb)
    anim_wait(16)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING, 0x0, BG_EFFECT_USER, 0x40)
    anim_sound(0, 0, SFX_METRONOME)
loop:
    anim_obj(ANIM_OBJ_RECOVER, 44, 88, 0x20)
    anim_wait(8)
    anim_loop(8, loop)
    anim_wait(128)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_FocusEnergy(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SPEED)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_LIGHT, 0x0, BG_EFFECT_USER, 0x40)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
loop:
    anim_sound(0, 0, SFX_SWORDS_DANCE)
    anim_obj(ANIM_OBJ_FOCUS, 44, 108, 0x6)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 36, 108, 0x6)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 52, 108, 0x8)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 28, 108, 0x8)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 60, 108, 0x6)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 20, 108, 0x8)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 68, 108, 0x8)
    anim_wait(2)
    anim_loop(3, loop)
    anim_wait(8)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_LIGHT)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Bide(battleanim_s* anim) {
    ANIM_BEGIN
    anim_if_param_equal_(0x0, BattleAnim_MegaPunch)
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_sound(0, 0, SFX_ESCAPE_ROPE)
    anim_bgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING, 0x0, BG_EFFECT_USER, 0x20)
    anim_wait(72)
    anim_incbgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Bind(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ROPE)
    anim_sound(0, 1, SFX_BIND)
    anim_obj(ANIM_OBJ_BIND1, 132, 64, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_BIND2, 132, 56, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_BIND1, 132, 48, 0x0)
    anim_wait(64)
    anim_sound(0, 1, SFX_BIND)
    anim_incobj(1)
    anim_incobj(2)
    anim_incobj(3)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Wrap(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ROPE)
    anim_sound(0, 1, SFX_BIND)
    anim_obj(ANIM_OBJ_BIND1, 132, 64, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_BIND1, 132, 56, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_BIND1, 132, 48, 0x0)
    anim_wait(64)
    anim_sound(0, 1, SFX_BIND)
    anim_incobj(1)
    anim_incobj(2)
    anim_incobj(3)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Confusion(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_UserObj_2Row)
    anim_sound(0, 1, SFX_PSYCHIC)
    anim_bgeffect(ANIM_BG_NIGHT_SHADE, 0x0, BG_EFFECT_TARGET, 0x8)
    anim_wait(128)
    anim_incbgeffect(ANIM_BG_NIGHT_SHADE)
    anim_call(BattleAnim_ShowMon_1)
    anim_ret
    ANIM_END
}

static int BattleAnim_Constrict(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ROPE)
    anim_sound(0, 1, SFX_BIND)
    anim_obj(ANIM_OBJ_BIND2, 132, 64, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_BIND1, 132, 48, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_BIND2, 132, 40, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_BIND1, 132, 56, 0x0)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Earthquake(battleanim_s* anim) {
    ANIM_BEGIN
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x60, 0x4, 0x10)
loop:
    anim_sound(0, 1, SFX_EMBER)
    anim_wait(24)
    anim_loop(4, loop)
    anim_ret
    ANIM_END
}

static int BattleAnim_Fissure(battleanim_s* anim) {
    ANIM_BEGIN
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x40)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x60, 0x4, 0x0)
loop:
    anim_sound(0, 1, SFX_EMBER)
    anim_wait(24)
    anim_loop(4, loop)
    anim_ret
    ANIM_END
}

static int BattleAnim_Growl(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_NOISE)
    anim_battlergfx_1row // anim_battlergfx_2row
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_cry(0x0)
loop:
    anim_call(BattleAnimSub_Sound)
    anim_wait(16)
    anim_loop(3, loop)
    anim_wait(9)
    anim_bgeffect(ANIM_BG_BATTLEROBJ_1ROW, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(8)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_BLACK_REPEATING, 0x0, BG_EFFECT_TARGET, 0x40)
    anim_wait(64)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_BLACK_REPEATING)
    anim_wait(1)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(5)
    anim_incobj(10)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_Roar(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_NOISE)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_cry(0x1)
loop:
    anim_call(BattleAnimSub_Sound)
    anim_wait(16)
    anim_loop(3, loop)
    anim_wait(16)
    anim_if_param_equal(0x0, done)
    anim_bgeffect(ANIM_BG_REMOVE_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(64)
done:
    anim_ret
    ANIM_END
}

static int BattleAnim_Supersonic(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_PSYCHIC)
loop:
    anim_sound(6, 2, SFX_SUPERSONIC)
    anim_obj(ANIM_OBJ_WAVE, 64, 88, 0x2)
    anim_wait(4)
    anim_loop(10, loop)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Screech(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_PSYCHIC)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x8, 0x1, 0x20)
    anim_sound(6, 2, SFX_SCREECH)
loop:
    anim_obj(ANIM_OBJ_WAVE, 64, 88, 0x2)
    anim_wait(2)
    anim_loop(2, loop)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_ConfuseRay(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SPEED)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_CYCLE_BGPALS_INVERTED, 0x0, 0x4, 0x0)
    anim_obj(ANIM_OBJ_CONFUSE_RAY, 64, 88, 0x0)
    anim_obj(ANIM_OBJ_CONFUSE_RAY, 64, 88, 0x80)
    anim_obj(ANIM_OBJ_CONFUSE_RAY, 64, 88, 0x88)
    anim_obj(ANIM_OBJ_CONFUSE_RAY, 64, 88, 0x90)
    anim_obj(ANIM_OBJ_CONFUSE_RAY, 64, 88, 0x98)
    anim_obj(ANIM_OBJ_CONFUSE_RAY, 64, 88, 0xa0)
    anim_obj(ANIM_OBJ_CONFUSE_RAY, 64, 88, 0xa8)
    anim_obj(ANIM_OBJ_CONFUSE_RAY, 64, 88, 0xb0)
    anim_obj(ANIM_OBJ_CONFUSE_RAY, 64, 88, 0xb8)
loop:
    anim_sound(6, 2, SFX_WHIRLWIND)
    anim_wait(16)
    anim_loop(8, loop)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Leer(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BEAM)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_call(BattleAnimSub_EyeBeams)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Reflect(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_REFLECT)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x2)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SCREEN, 72, 80, 0x0)
    anim_wait(24)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x2)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SCREEN, 72, 80, 0x0)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_LightScreen(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_SPEED, ANIM_GFX_REFLECT)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_sound(0, 0, SFX_FLASH)
    anim_obj(ANIM_OBJ_SCREEN, 72, 80, 0x0)
    anim_wait(4)
    anim_obj(ANIM_OBJ_SHINY, 72, 80, 0x0)
    anim_wait(4)
    anim_obj(ANIM_OBJ_SHINY, 72, 80, 0x8)
    anim_wait(4)
    anim_obj(ANIM_OBJ_SHINY, 72, 80, 0x10)
    anim_wait(4)
    anim_obj(ANIM_OBJ_SHINY, 72, 80, 0x18)
    anim_wait(4)
    anim_obj(ANIM_OBJ_SCREEN, 72, 80, 0x0)
    anim_obj(ANIM_OBJ_SHINY, 72, 80, 0x20)
    anim_wait(4)
    anim_obj(ANIM_OBJ_SHINY, 72, 80, 0x28)
    anim_wait(4)
    anim_obj(ANIM_OBJ_SHINY, 72, 80, 0x30)
    anim_wait(4)
    anim_obj(ANIM_OBJ_SHINY, 72, 80, 0x38)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Amnesia(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_STATUS)
    anim_sound(0, 0, SFX_LICK)
    anim_obj(ANIM_OBJ_AMNESIA, 64, 80, 0x2)
    anim_wait(16)
    anim_obj(ANIM_OBJ_AMNESIA, 68, 80, 0x1)
    anim_wait(16)
    anim_obj(ANIM_OBJ_AMNESIA, 72, 80, 0x0)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_DizzyPunch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_STATUS, ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 40, 0x0)
    anim_obj(ANIM_OBJ_HIT_SMALL_YFIX, 136, 64, 0x0)
    anim_wait(16)
    anim_sound(0, 1, SFX_KINESIS)
    anim_obj(ANIM_OBJ_CHICK, 136, 24, 0x15)
    anim_obj(ANIM_OBJ_CHICK, 136, 24, 0xaa)
    anim_obj(ANIM_OBJ_CHICK, 136, 24, 0xbf)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Rest(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_STATUS)
    anim_sound(0, 0, SFX_TAIL_WHIP)
loop:
    anim_obj(ANIM_OBJ_ASLEEP, 64, 80, 0x0)
    anim_wait(40)
    anim_loop(3, loop)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_AcidArmor(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_ACID_ARMOR, 0x0, BG_EFFECT_USER, 0x8)
    anim_sound(0, 0, SFX_MEGA_PUNCH)
    anim_wait(64)
    anim_incbgeffect(ANIM_BG_ACID_ARMOR)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Splash(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 0, SFX_VICEGRIP)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_BOUNCE_DOWN, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(96)
    anim_incbgeffect(ANIM_BG_BOUNCE_DOWN)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Dig(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_SAND, ANIM_GFX_HIT)
    anim_if_param_equal(0x0, hit)
    anim_if_param_equal(0x2, fail)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_DIG, 0x0, BG_EFFECT_USER, 0x1)
    anim_obj(ANIM_OBJ_DIG_PILE, 72, 104, 0x0)
loop:
    anim_sound(0, 0, SFX_RAZOR_WIND)
    anim_obj(ANIM_OBJ_DIG_SAND, 56, 104, 0x0)
    anim_wait(16)
    anim_loop(6, loop)
    anim_wait(32)
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(8)
    anim_incbgeffect(ANIM_BG_DIG)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret

hit:
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(32)
fail:
    anim_bgeffect(ANIM_BG_ENTER_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_SandAttack(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SAND)
    anim_call(BattleAnimSub_SandOrMud)
    anim_ret
    ANIM_END
}

static int BattleAnim_StringShot(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WEB)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_sound(6, 2, SFX_MENU)
    anim_obj(ANIM_OBJ_STRING_SHOT, 64, 80, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_MENU)
    anim_obj(ANIM_OBJ_STRING_SHOT, 132, 48, 0x1)
    anim_wait(4)
    anim_sound(6, 2, SFX_MENU)
    anim_obj(ANIM_OBJ_STRING_SHOT, 64, 88, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_MENU)
    anim_obj(ANIM_OBJ_STRING_SHOT, 132, 64, 0x1)
    anim_wait(4)
    anim_sound(6, 2, SFX_MENU)
    anim_obj(ANIM_OBJ_STRING_SHOT, 64, 84, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_MENU)
    anim_obj(ANIM_OBJ_STRING_SHOT, 132, 56, 0x2)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Headbutt(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x14, 0x2, 0x0)
    anim_wait(32)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_TACKLE, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_HEADBUTT)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(8)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Tackle(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_TACKLE, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_TACKLE)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 48, 0x0)
    anim_wait(8)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_BodySlam(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_BOUNCE_DOWN, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_incbgeffect(ANIM_BG_BOUNCE_DOWN)
    anim_wait(4)
    anim_bgeffect(ANIM_BG_BODY_SLAM, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(3)
    anim_sound(0, 1, SFX_TACKLE)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 48, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_TACKLE)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 48, 0x0)
    anim_wait(3)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_TakeDown(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_TACKLE, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(3)
    anim_sound(0, 1, SFX_TACKLE)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x2)
    anim_obj(ANIM_OBJ_HIT_YFIX, 128, 56, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_TACKLE)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x2)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 48, 0x0)
    anim_wait(3)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_DoubleEdge(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x10)
    anim_bgeffect(ANIM_BG_TACKLE, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(3)
    anim_sound(0, 1, SFX_TACKLE)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 128, 48, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_TACKLE)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 144, 48, 0x0)
    anim_wait(3)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Submission(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_UserObj_1Row)
    anim_bgeffect(ANIM_BG_WOBBLE_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_sound(0, 1, SFX_SUBMISSION)
    anim_wait(32)
    anim_obj(ANIM_OBJ_HIT_YFIX, 120, 48, 0x0)
    anim_wait(32)
    anim_obj(ANIM_OBJ_HIT_YFIX, 152, 56, 0x0)
    anim_wait(32)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 52, 0x0)
    anim_wait(32)
    anim_incbgeffect(ANIM_BG_WOBBLE_MON)
    anim_call(BattleAnim_ShowMon_1)
    anim_ret
    ANIM_END
}

static int BattleAnim_Whirlwind(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WIND)
loop:
    anim_sound(0, 0, SFX_RAZOR_WIND)
    anim_obj(ANIM_OBJ_GUST, 64, 112, 0x0)
    anim_wait(6)
    anim_loop(9, loop)
    anim_incobj(1)
    anim_incobj(2)
    anim_incobj(3)
    anim_incobj(4)
    anim_incobj(5)
    anim_incobj(6)
    anim_incobj(7)
    anim_incobj(8)
    anim_incobj(9)
    anim_sound(16, 2, SFX_WHIRLWIND)
    anim_wait(128)
    anim_if_param_equal(0x0, done)
    anim_bgeffect(ANIM_BG_REMOVE_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(64)
done:
    anim_ret
    ANIM_END
}

static int BattleAnim_Hypnosis(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_PSYCHIC)
loop:
    anim_sound(6, 2, SFX_SUPERSONIC)
    anim_obj(ANIM_OBJ_WAVE, 64, 88, 0x2)
    anim_obj(ANIM_OBJ_WAVE, 56, 80, 0x2)
    anim_wait(8)
    anim_loop(3, loop)
    anim_wait(56)
    anim_ret
    ANIM_END
}

static int BattleAnim_Haze(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HAZE)
    anim_sound(0, 1, SFX_SURF)
loop:
    anim_obj(ANIM_OBJ_HAZE, 48, 56, 0x0)
    anim_obj(ANIM_OBJ_HAZE, 132, 16, 0x0)
    anim_wait(12)
    anim_loop(5, loop)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Mist(battleanim_s* anim) {
    ANIM_BEGIN
    anim_obp0(0x54)
    anim_1gfx(ANIM_GFX_HAZE)
    anim_sound(0, 0, SFX_SURF)
loop:
    anim_obj(ANIM_OBJ_MIST, 48, 56, 0x0)
    anim_wait(8)
    anim_loop(10, loop)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Smog(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HAZE)
    anim_sound(0, 1, SFX_BUBBLEBEAM)
loop:
    anim_obj(ANIM_OBJ_SMOG, 132, 16, 0x0)
    anim_wait(8)
    anim_loop(10, loop)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_PoisonGas(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HAZE)
    anim_sound(16, 2, SFX_BUBBLEBEAM)
loop:
    anim_obj(ANIM_OBJ_POISON_GAS, 44, 80, 0x2)
    anim_wait(8)
    anim_loop(10, loop)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_HornAttack(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HORN, ANIM_GFX_HIT)
    anim_obj(ANIM_OBJ_HORN, 72, 80, 0x1)
    anim_wait(16)
    anim_sound(0, 1, SFX_HORN_ATTACK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_FuryAttack(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HORN, ANIM_GFX_HIT)
    anim_obj(ANIM_OBJ_HORN, 72, 72, 0x2)
    anim_wait(8)
    anim_sound(0, 1, SFX_HORN_ATTACK)
    anim_obj(ANIM_OBJ_HIT, 128, 40, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_HORN, 80, 88, 0x2)
    anim_wait(8)
    anim_sound(0, 1, SFX_HORN_ATTACK)
    anim_obj(ANIM_OBJ_HIT, 136, 56, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_HORN, 76, 80, 0x2)
    anim_wait(8)
    anim_sound(0, 1, SFX_HORN_ATTACK)
    anim_obj(ANIM_OBJ_HIT, 132, 48, 0x0)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_HornDrill(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HORN, ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x40)
    anim_obj(ANIM_OBJ_HORN, 72, 80, 0x3)
    anim_wait(8)
loop:
    anim_sound(0, 1, SFX_HORN_ATTACK)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 132, 40, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_HORN_ATTACK)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 140, 48, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_HORN_ATTACK)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 132, 56, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_HORN_ATTACK)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 124, 48, 0x0)
    anim_wait(8)
    anim_loop(3, loop)
    anim_ret
    ANIM_END
}

static int BattleAnim_PoisonSting(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HORN, ANIM_GFX_HIT)
    anim_obj(ANIM_OBJ_NEEDLE, 64, 92, 0x14)
    anim_wait(16)
    anim_sound(0, 1, SFX_POISON_STING)
    anim_obj(ANIM_OBJ_HIT_SMALL, 136, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Twineedle(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HORN, ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_POISON_STING)
    anim_obj(ANIM_OBJ_NEEDLE, 64, 92, 0x14)
    anim_obj(ANIM_OBJ_NEEDLE, 56, 84, 0x14)
    anim_wait(16)
    anim_sound(0, 1, SFX_POISON_STING)
    anim_obj(ANIM_OBJ_HIT_SMALL, 136, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_SMALL, 128, 48, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_PinMissile(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HORN, ANIM_GFX_HIT)
loop:
    anim_obj(ANIM_OBJ_NEEDLE, 64, 92, 0x28)
    anim_wait(8)
    anim_obj(ANIM_OBJ_NEEDLE, 56, 84, 0x28)
    anim_sound(0, 1, SFX_POISON_STING)
    anim_obj(ANIM_OBJ_HIT_SMALL, 136, 56, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_NEEDLE, 52, 88, 0x28)
    anim_sound(0, 1, SFX_POISON_STING)
    anim_obj(ANIM_OBJ_HIT_SMALL, 128, 48, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_POISON_STING)
    anim_obj(ANIM_OBJ_HIT_SMALL, 132, 52, 0x0)
    anim_loop(3, loop)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_SpikeCannon(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HORN, ANIM_GFX_HIT)
loop:
    anim_obj(ANIM_OBJ_NEEDLE, 64, 92, 0x18)
    anim_wait(8)
    anim_obj(ANIM_OBJ_NEEDLE, 56, 84, 0x18)
    anim_sound(0, 1, SFX_POISON_STING)
    anim_obj(ANIM_OBJ_HIT_SMALL, 136, 56, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_NEEDLE, 52, 88, 0x18)
    anim_sound(0, 1, SFX_POISON_STING)
    anim_obj(ANIM_OBJ_HIT_SMALL, 128, 48, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_POISON_STING)
    anim_obj(ANIM_OBJ_HIT_SMALL, 132, 52, 0x0)
    anim_loop(3, loop)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Transform(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_transform
    anim_sound(0, 0, SFX_PSYBEAM)
    anim_bgeffect(ANIM_BG_WAVE_DEFORM_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(48)
    anim_updateactorpic
    anim_incbgeffect(ANIM_BG_WAVE_DEFORM_MON)
    anim_wait(48)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_PetalDance(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 0, SFX_MENU)
    anim_2gfx(ANIM_GFX_FLOWER, ANIM_GFX_HIT)
loop:
    anim_obj(ANIM_OBJ_PETAL_DANCE, 48, 56, 0x0)
    anim_wait(11)
    anim_loop(8, loop)
    anim_wait(128)
    anim_wait(64)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Barrage(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_EGG, ANIM_GFX_EXPLOSION)
    anim_sound(6, 2, SFX_THROW_BALL)
    anim_obj(ANIM_OBJ_SLUDGE_BOMB, 64, 92, 0x10)
    anim_wait(36)
    anim_sound(0, 1, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION2, 136, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_PayDay(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HIT, ANIM_GFX_STATUS)
    anim_sound(0, 1, SFX_POUND)
    anim_obj(ANIM_OBJ_HIT_YFIX, 128, 56, 0x0)
    anim_wait(16)
    anim_sound(0, 1, SFX_PAY_DAY)
    anim_obj(ANIM_OBJ_PAY_DAY, 120, 76, 0x1)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Mimic(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SPEED)
    anim_obp0(0xfc)
    anim_sound(63, 3, SFX_LICK)
    anim_obj(ANIM_OBJ_MIMIC, 132, 44, 0x0)
    anim_obj(ANIM_OBJ_MIMIC, 132, 44, 0x8)
    anim_obj(ANIM_OBJ_MIMIC, 132, 44, 0x10)
    anim_obj(ANIM_OBJ_MIMIC, 132, 44, 0x18)
    anim_obj(ANIM_OBJ_MIMIC, 132, 44, 0x20)
    anim_obj(ANIM_OBJ_MIMIC, 132, 44, 0x28)
    anim_obj(ANIM_OBJ_MIMIC, 132, 44, 0x30)
    anim_obj(ANIM_OBJ_MIMIC, 132, 44, 0x38)
    anim_wait(128)
    anim_wait(48)
    anim_ret
    ANIM_END
}

static int BattleAnim_LovelyKiss(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_OBJECTS, ANIM_GFX_ANGELS)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_obj(ANIM_OBJ_LOVELY_KISS, 152, 40, 0x0)
    anim_wait(32)
    anim_sound(0, 1, SFX_LICK)
    anim_obj(ANIM_OBJ_HEART, 128, 40, 0x0)
    anim_wait(40)
    anim_ret
    ANIM_END
}

static int BattleAnim_Bonemerang(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_MISC, ANIM_GFX_HIT)
    anim_sound(6, 2, SFX_HYDRO_PUMP)
    anim_obj(ANIM_OBJ_BONEMERANG, 88, 56, 0x1c)
    anim_wait(24)
    anim_sound(0, 1, SFX_MOVE_PUZZLE_PIECE)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(24)
    anim_ret
    ANIM_END
}

static int BattleAnim_Swift(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_OBJECTS)
    anim_sound(6, 2, SFX_METRONOME)
    anim_obj(ANIM_OBJ_SWIFT, 64, 88, 0x4)
    anim_wait(4)
    anim_obj(ANIM_OBJ_SWIFT, 64, 72, 0x4)
    anim_wait(4)
    anim_obj(ANIM_OBJ_SWIFT, 64, 76, 0x4)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Crabhammer(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x40, 0x2, 0x0)
    anim_wait(48)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x3)
loop:
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(12)
    anim_loop(3, loop)
    anim_ret
    ANIM_END
}

static int BattleAnim_SkullBash(battleanim_s* anim) {
    ANIM_BEGIN
    anim_if_param_equal_(0x1, BattleAnim_FocusEnergy)
    anim_1gfx(ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x14, 0x2, 0x0)
    anim_wait(32)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x3)
    anim_bgeffect(ANIM_BG_TACKLE, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
loop:
    anim_sound(0, 1, SFX_HEADBUTT)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(8)
    anim_loop(3, loop)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Kinesis(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_MISC, ANIM_GFX_NOISE)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_obj(ANIM_OBJ_KINESIS, 80, 76, 0x0)
    anim_wait(32)
loop:
    anim_sound(0, 0, SFX_KINESIS)
    anim_obj(ANIM_OBJ_SOUND, 64, 88, 0x0)
    anim_wait(32)
    anim_loop(3, loop)
    anim_wait(32)
    anim_sound(0, 0, SFX_KINESIS_2)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Peck(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_PECK)
    anim_obj(ANIM_OBJ_HIT_SMALL_YFIX, 128, 48, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_PECK)
    anim_obj(ANIM_OBJ_HIT_SMALL_YFIX, 136, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_DrillPeck(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
loop:
    anim_sound(0, 1, SFX_PECK)
    anim_obj(ANIM_OBJ_HIT_SMALL_YFIX, 124, 56, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_PECK)
    anim_obj(ANIM_OBJ_HIT_SMALL_YFIX, 132, 48, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_PECK)
    anim_obj(ANIM_OBJ_HIT_SMALL_YFIX, 140, 56, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_PECK)
    anim_obj(ANIM_OBJ_HIT_SMALL_YFIX, 132, 64, 0x0)
    anim_wait(4)
    anim_loop(5, loop)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Guillotine(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CUT)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x10)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x40, 0x2, 0x0)
    anim_sound(0, 1, SFX_VICEGRIP)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 156, 44, 0x0)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 152, 40, 0x0)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 148, 36, 0x0)
    anim_obj(ANIM_OBJ_CUT_UP_RIGHT, 124, 76, 0x0)
    anim_obj(ANIM_OBJ_CUT_UP_RIGHT, 120, 72, 0x0)
    anim_obj(ANIM_OBJ_CUT_UP_RIGHT, 116, 68, 0x0)
    anim_obj(ANIM_OBJ_CUT_UP_RIGHT, 120, 72, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Flash(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SPEED)
    anim_sound(0, 1, SFX_FLASH)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x6, 0x20)
    anim_wait(4)
    anim_obj(ANIM_OBJ_FLASH, 136, 56, 0x0)
    anim_wait(4)
    anim_obj(ANIM_OBJ_FLASH, 136, 56, 0x8)
    anim_wait(4)
    anim_obj(ANIM_OBJ_FLASH, 136, 56, 0x10)
    anim_wait(4)
    anim_obj(ANIM_OBJ_FLASH, 136, 56, 0x18)
    anim_wait(4)
    anim_obj(ANIM_OBJ_FLASH, 136, 56, 0x20)
    anim_wait(4)
    anim_obj(ANIM_OBJ_FLASH, 136, 56, 0x28)
    anim_wait(4)
    anim_obj(ANIM_OBJ_FLASH, 136, 56, 0x30)
    anim_wait(4)
    anim_obj(ANIM_OBJ_FLASH, 136, 56, 0x38)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Substitute(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 0, SFX_SURF)
    anim_if_param_equal(0x3, dropsub2)
    anim_if_param_equal(0x2, raisesub)
    anim_if_param_equal(0x1, dropsub)
    anim_1gfx(ANIM_GFX_SMOKE)
    anim_bgeffect(ANIM_BG_REMOVE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(48)
    anim_raisesub
    anim_obj(ANIM_OBJ_BALL_POOF, 48, 96, 0x0)
    anim_bgeffect(ANIM_BG_ENTER_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_ret

dropsub:
    anim_bgeffect(ANIM_BG_REMOVE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(48)
    anim_dropsub
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_ret

raisesub:
    anim_bgeffect(ANIM_BG_REMOVE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(48)
    anim_raisesub
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_ret

dropsub2:
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(48)
    anim_dropsub
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Minimize(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 0, SFX_SURF)
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_minimize
    anim_bgeffect(ANIM_BG_WAVE_DEFORM_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(48)
    anim_updateactorpic
    anim_incbgeffect(ANIM_BG_WAVE_DEFORM_MON)
    anim_wait(48)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_SkyAttack(battleanim_s* anim) {
    ANIM_BEGIN
    anim_if_param_equal_(0x1, BattleAnim_FocusEnergy)
    anim_1gfx(ANIM_GFX_SKY_ATTACK)
    anim_bgeffect(ANIM_BG_REMOVE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_sound(0, 0, SFX_HYPER_BEAM)
    anim_obj(ANIM_OBJ_SKY_ATTACK, 48, 88, 0x40)
    anim_wait(64)
    anim_incobj(1)
    anim_wait(21)
    anim_sound(0, 1, SFX_HYPER_BEAM)
    anim_bgeffect(ANIM_BG_ALTERNATE_HUES, 0x0, 0x2, 0x0)
    anim_wait(64)
    anim_incobj(1)
    anim_wait(32)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_NightShade(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_bgp(0x1b)
    anim_obp1(0x1b)
    anim_wait(32)
    anim_call(BattleAnim_UserObj_2Row)
    anim_bgeffect(ANIM_BG_NIGHT_SHADE, 0x0, BG_EFFECT_TARGET, 0x8)
    anim_sound(0, 1, SFX_PSYCHIC)
    anim_wait(96)
    anim_incbgeffect(ANIM_BG_NIGHT_SHADE)
    anim_call(BattleAnim_ShowMon_1)
    anim_ret
    ANIM_END
}

static int BattleAnim_Lick(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WATER)
    anim_sound(0, 1, SFX_LICK)
    anim_obj(ANIM_OBJ_LICK, 136, 56, 0x0)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_TriAttack(battleanim_s* anim) {
    ANIM_BEGIN
    anim_3gfx(ANIM_GFX_FIRE, ANIM_GFX_ICE, ANIM_GFX_LIGHTNING)
    anim_call(BattleAnimSub_Fire)
    anim_wait(16)
    anim_call(BattleAnimSub_Ice)
    anim_wait(16)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x4)
    anim_sound(0, 1, SFX_THUNDER)
    anim_obj(ANIM_OBJ_THUNDER3, 152, 68, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Withdraw(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_REFLECT)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_WITHDRAW, 0x0, BG_EFFECT_USER, 0x50)
    anim_wait(48)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_WITHDRAW, 48, 88, 0x0)
    anim_wait(64)
    anim_incobj(2)
    anim_wait(1)
    anim_incbgeffect(ANIM_BG_WITHDRAW)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Psybeam(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_PSYCHIC)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_CYCLE_BGPALS_INVERTED, 0x0, 0x4, 0x0)
loop:
    anim_sound(6, 2, SFX_PSYBEAM)
    anim_obj(ANIM_OBJ_WAVE, 64, 88, 0x4)
    anim_wait(4)
    anim_loop(10, loop)
    anim_wait(48)
    anim_ret
    ANIM_END
}

static int BattleAnim_DreamEater(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BUBBLE)
    anim_bgp(0x1b)
    anim_obp0(0x27)
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_call(BattleAnimSub_Drain)
    anim_wait(128)
    anim_wait(48)
    anim_ret
    ANIM_END
}

static int BattleAnim_LeechLife(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BUBBLE)
    anim_sound(6, 3, SFX_WATER_GUN)
    anim_call(BattleAnimSub_Drain)
    anim_wait(128)
    anim_wait(48)
    anim_ret
    ANIM_END
}

static int BattleAnim_Harden(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_REFLECT)
    anim_obp0(0x0)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_call(BattleAnimSub_Metallic)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Psywave(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_PSYCHIC)
    anim_bgeffect(ANIM_BG_PSYCHIC, 0x0, 0x0, 0x0)
loop:
    anim_sound(6, 2, SFX_PSYCHIC)
    anim_obj(ANIM_OBJ_WAVE, 64, 80, 0x2)
    anim_wait(8)
    anim_sound(6, 2, SFX_PSYCHIC)
    anim_obj(ANIM_OBJ_WAVE, 64, 88, 0x3)
    anim_wait(8)
    anim_sound(6, 2, SFX_PSYCHIC)
    anim_obj(ANIM_OBJ_WAVE, 64, 96, 0x4)
    anim_wait(8)
    anim_loop(3, loop)
    anim_wait(32)
    anim_incbgeffect(ANIM_BG_PSYCHIC)
    anim_wait(4)
    anim_ret
    ANIM_END
}

static int BattleAnim_Glare(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BEAM)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x20)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_call(BattleAnimSub_EyeBeams)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Thrash(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_POUND)
    anim_obj(ANIM_OBJ_PALM, 120, 72, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 120, 72, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_MOVE_PUZZLE_PIECE)
    anim_obj(ANIM_OBJ_PUNCH, 136, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_KICK, 152, 40, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 152, 40, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Growth(battleanim_s* anim) {
    ANIM_BEGIN
    anim_bgeffect(ANIM_BG_WHITE_HUES, 0x0, 0x8, 0x0)
    anim_1gfx(ANIM_GFX_CHARGE)
    anim_sound(0, 0, SFX_SWORDS_DANCE)
    anim_obj(ANIM_OBJ_GROWTH, 48, 108, 0x0)
    anim_obj(ANIM_OBJ_GROWTH, 48, 108, 0x8)
    anim_obj(ANIM_OBJ_GROWTH, 48, 108, 0x10)
    anim_obj(ANIM_OBJ_GROWTH, 48, 108, 0x18)
    anim_obj(ANIM_OBJ_GROWTH, 48, 108, 0x20)
    anim_obj(ANIM_OBJ_GROWTH, 48, 108, 0x28)
    anim_obj(ANIM_OBJ_GROWTH, 48, 108, 0x30)
    anim_obj(ANIM_OBJ_GROWTH, 48, 108, 0x38)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Conversion2(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_EXPLOSION)
    anim_sound(63, 3, SFX_SHARPEN)
    anim_obj(ANIM_OBJ_CONVERSION2, 132, 44, 0x0)
    anim_obj(ANIM_OBJ_CONVERSION2, 132, 44, 0x8)
    anim_obj(ANIM_OBJ_CONVERSION2, 132, 44, 0x10)
    anim_obj(ANIM_OBJ_CONVERSION2, 132, 44, 0x18)
    anim_obj(ANIM_OBJ_CONVERSION2, 132, 44, 0x20)
    anim_obj(ANIM_OBJ_CONVERSION2, 132, 44, 0x28)
    anim_obj(ANIM_OBJ_CONVERSION2, 132, 44, 0x30)
    anim_obj(ANIM_OBJ_CONVERSION2, 132, 44, 0x38)
    anim_wait(128)
    anim_wait(48)
    anim_ret
    ANIM_END
}

static int BattleAnim_Smokescreen(battleanim_s* anim) {
    ANIM_BEGIN
    anim_3gfx(ANIM_GFX_HAZE, ANIM_GFX_EGG, ANIM_GFX_SMOKE)
    anim_sound(6, 2, SFX_THROW_BALL)
    anim_obj(ANIM_OBJ_SMOKESCREEN, 64, 92, 0x6c)
    anim_wait(24)
    anim_incobj(1)
    anim_sound(0, 1, SFX_BALL_POOF)
    anim_obj(ANIM_OBJ_BALL_POOF, 108, 70, 0x10)
    anim_wait(8)
loop:
    anim_sound(0, 1, SFX_MENU)
    anim_obj(ANIM_OBJ_SMOKE, 132, 60, 0x20)
    anim_wait(8)
    anim_loop(5, loop)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_Strength(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_ROCKS, ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_Y, 0x10, 0x1, 0x20)
    anim_sound(0, 0, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_STRENGTH, 64, 104, 0x1)
    anim_wait(128)
    anim_incobj(1)
    anim_wait(20)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 132, 40, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_SwordsDance(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WHIP)
    anim_sound(0, 0, SFX_SWORDS_DANCE)
    anim_obj(ANIM_OBJ_SWORDS_DANCE, 48, 108, 0x0)
    anim_obj(ANIM_OBJ_SWORDS_DANCE, 48, 108, 0xd)
    anim_obj(ANIM_OBJ_SWORDS_DANCE, 48, 108, 0x1a)
    anim_obj(ANIM_OBJ_SWORDS_DANCE, 48, 108, 0x27)
    anim_obj(ANIM_OBJ_SWORDS_DANCE, 48, 108, 0x34)
    anim_wait(56)
    anim_ret
    ANIM_END
}

static int BattleAnim_QuickAttack(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_SPEED, ANIM_GFX_HIT)
    anim_sound(0, 0, SFX_MENU)
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_obj(ANIM_OBJ_SPEED_LINE, 24, 88, 0x2)
    anim_obj(ANIM_OBJ_SPEED_LINE, 32, 88, 0x1)
    anim_obj(ANIM_OBJ_SPEED_LINE, 40, 88, 0x0)
    anim_obj(ANIM_OBJ_SPEED_LINE, 48, 88, 0x80)
    anim_obj(ANIM_OBJ_SPEED_LINE, 56, 88, 0x81)
    anim_obj(ANIM_OBJ_SPEED_LINE, 64, 88, 0x82)
    anim_wait(12)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(8)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Meditate(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_sound(0, 0, SFX_PSYBEAM)
    anim_bgeffect(ANIM_BG_WAVE_DEFORM_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(48)
    anim_incbgeffect(ANIM_BG_WAVE_DEFORM_MON)
    anim_wait(48)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Sharpen(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SHAPES)
    anim_obp0(0xe4)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_sound(0, 0, SFX_SHARPEN)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING, 0x0, BG_EFFECT_USER, 0x40)
    anim_obj(ANIM_OBJ_SHARPEN, 48, 88, 0x0)
    anim_wait(96)
    anim_incobj(2)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_DefenseCurl(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SHAPES)
    anim_obp0(0xe4)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_sound(0, 0, SFX_SHARPEN)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING, 0x0, BG_EFFECT_USER, 0x40)
    anim_obj(ANIM_OBJ_DEFENSE_CURL, 48, 88, 0x0)
    anim_wait(96)
    anim_incobj(2)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_SeismicToss(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_GLOBE, ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_Y, 0x10, 0x1, 0x20)
    anim_sound(0, 0, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_SEISMIC_TOSS, 64, 104, 0x1)
    anim_wait(128)
    anim_incobj(1)
    anim_wait(20)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 132, 40, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Rage(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING, 0x0, BG_EFFECT_USER, 0x20)
    anim_sound(0, 0, SFX_RAGE)
    anim_wait(72)
    anim_incbgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_sound(0, 1, SFX_MOVE_PUZZLE_PIECE)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 120, 72, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 152, 40, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Agility(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WIND)
    anim_obp0(0xfc)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING, 0x0, BG_EFFECT_USER, 0x40)
    anim_obj(ANIM_OBJ_AGILITY, 8, 24, 0x10)
    anim_obj(ANIM_OBJ_AGILITY, 8, 48, 0x2)
    anim_obj(ANIM_OBJ_AGILITY, 8, 88, 0x8)
    anim_wait(4)
    anim_obj(ANIM_OBJ_AGILITY, 8, 32, 0x6)
    anim_obj(ANIM_OBJ_AGILITY, 8, 56, 0xc)
    anim_obj(ANIM_OBJ_AGILITY, 8, 80, 0x4)
    anim_obj(ANIM_OBJ_AGILITY, 8, 104, 0xe)
loop:
    anim_sound(0, 0, SFX_RAZOR_WIND)
    anim_wait(4)
    anim_loop(18, loop)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_BoneClub(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HIT, ANIM_GFX_MISC)
    anim_obj(ANIM_OBJ_BONE_CLUB, 64, 88, 0x2)
    anim_wait(32)
    anim_sound(0, 1, SFX_BONE_CLUB)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Barrier(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_REFLECT)
    anim_battlergfx_1row // anim_battlergfx_2row
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_wait(8)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SCREEN, 72, 80, 0x0)
    anim_wait(32)
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SCREEN, 72, 80, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Waterfall(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_BODY_SLAM, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(16)
    anim_call(BattleAnim_ShowMon_0)
    anim_sound(0, 1, SFX_LICK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(3)
    anim_sound(0, 1, SFX_LICK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 48, 0x0)
    anim_wait(3)
    anim_sound(0, 1, SFX_LICK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 40, 0x0)
    anim_wait(3)
    anim_sound(0, 1, SFX_LICK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 32, 0x0)
    anim_wait(3)
    anim_sound(0, 1, SFX_LICK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 24, 0x0)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_PsychicM(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_PSYCHIC)
    anim_bgeffect(ANIM_BG_ALTERNATE_HUES, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_PSYCHIC, 0x0, 0x0, 0x0)
loop:
    anim_sound(6, 2, SFX_PSYCHIC)
    anim_obj(ANIM_OBJ_WAVE, 64, 88, 0x2)
    anim_wait(8)
    anim_loop(8, loop)
    anim_wait(96)
    anim_incbgeffect(ANIM_BG_PSYCHIC)
    anim_wait(4)
    anim_ret
    ANIM_END
}

static int BattleAnim_Sludge(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_POISON)
    anim_call(BattleAnimSub_Sludge)
    anim_wait(56)
    anim_ret
    ANIM_END
}

static int BattleAnim_Toxic(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_POISON)
    anim_bgeffect(ANIM_BG_BLACK_HUES, 0x0, 0x8, 0x0)
    anim_call(BattleAnimSub_Acid)
    anim_wait(32)
    anim_call(BattleAnimSub_Sludge)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Metronome(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_MISC, ANIM_GFX_SPEED)
    anim_sound(0, 0, SFX_METRONOME)
    anim_obj(ANIM_OBJ_METRONOME_HAND, 72, 88, 0x0)
loop:
    anim_obj(ANIM_OBJ_METRONOME_SPARKLE, 72, 80, 0x0)
    anim_wait(8)
    anim_loop(5, loop)
    anim_wait(48)
    anim_ret
    ANIM_END
}

static int BattleAnim_Counter(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
loop:
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x6, 0x2)
    anim_sound(0, 1, SFX_POUND)
    anim_obj(ANIM_OBJ_PALM, 120, 72, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 120, 72, 0x0)
    anim_wait(6)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x6, 0x2)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_PUNCH, 136, 40, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 40, 0x0)
    anim_wait(6)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x6, 0x2)
    anim_sound(0, 1, SFX_MEGA_KICK)
    anim_obj(ANIM_OBJ_KICK, 152, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 152, 56, 0x0)
    anim_wait(6)
    anim_loop(3, loop)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_LowKick(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x2)
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_KICK, 124, 64, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 124, 64, 0x0)
    anim_wait(6)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x2)
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_KICK, 132, 64, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 132, 64, 0x0)
    anim_wait(6)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x2)
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_KICK, 140, 64, 0x0)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 140, 64, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_WingAttack(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_WING_ATTACK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 148, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_YFIX, 116, 56, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_WING_ATTACK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_YFIX, 120, 56, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_WING_ATTACK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 140, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_YFIX, 124, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Slam(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_WING_ATTACK)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x2)
    anim_obj(ANIM_OBJ_HIT_YFIX, 124, 40, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Disable(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_LIGHTNING, ANIM_GFX_STATUS)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_obj(ANIM_OBJ_DISABLE, 132, 56, 0x0)
    anim_wait(16)
    anim_sound(0, 1, SFX_BIND)
    anim_obj(ANIM_OBJ_PARALYZED, 104, 56, 0x42)
    anim_obj(ANIM_OBJ_PARALYZED, 160, 56, 0xc2)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_TailWhip(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_sound(0, 0, SFX_TAIL_WHIP)
    anim_bgeffect(ANIM_BG_WOBBLE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(32)
    anim_incbgeffect(ANIM_BG_WOBBLE_MON)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Struggle(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_POUND)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Sketch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_OBJECTS)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING, 0x0, BG_EFFECT_USER, 0x20)
    anim_sound(0, 0, SFX_SKETCH)
    anim_obj(ANIM_OBJ_SKETCH, 72, 80, 0x0)
    anim_wait(80)
    anim_incbgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_wait(1)
    anim_ret
    ANIM_END
}

static int BattleAnim_TripleKick(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_if_param_equal(0x1, alternate1)
    anim_if_param_equal(0x2, alternate2)
    anim_sound(0, 1, SFX_MEGA_KICK)
    anim_obj(ANIM_OBJ_KICK, 144, 48, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 48, 0x0)
    anim_wait(8)
    anim_ret

alternate1:
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_KICK, 120, 64, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 120, 64, 0x0)
    anim_wait(8)
    anim_ret

alternate2:
    anim_sound(0, 1, SFX_DOUBLE_KICK)
    anim_obj(ANIM_OBJ_KICK, 132, 32, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 132, 32, 0x0)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_Thief(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_TACKLE, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(16)
    anim_sound(0, 1, SFX_THIEF)
    anim_obj(ANIM_OBJ_HIT_YFIX, 128, 48, 0x0)
    anim_wait(16)
    anim_call(BattleAnim_ShowMon_0)
    anim_wait(1)
    anim_1gfx(ANIM_GFX_STATUS)
    anim_sound(0, 1, SFX_THIEF_2)
    anim_obj(ANIM_OBJ_THIEF, 120, 76, 0x1)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_SpiderWeb(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WEB)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_obj(ANIM_OBJ_SPIDER_WEB, 132, 48, 0x0)
    anim_sound(6, 2, SFX_SPIDER_WEB)
    anim_obj(ANIM_OBJ_STRING_SHOT, 64, 80, 0x0)
    anim_wait(4)
    anim_obj(ANIM_OBJ_STRING_SHOT, 64, 88, 0x0)
    anim_wait(4)
    anim_obj(ANIM_OBJ_STRING_SHOT, 64, 84, 0x0)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_MindReader(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_MISC)
    anim_sound(0, 1, SFX_MIND_READER)
loop:
    anim_obj(ANIM_OBJ_MIND_READER, 132, 48, 0x3)
    anim_obj(ANIM_OBJ_MIND_READER, 132, 48, 0x12)
    anim_obj(ANIM_OBJ_MIND_READER, 132, 48, 0x20)
    anim_obj(ANIM_OBJ_MIND_READER, 132, 48, 0x31)
    anim_wait(16)
    anim_loop(2, loop)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Nightmare(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ANGELS)
    anim_bgp(0x1b)
    anim_obp0(0xf)
    anim_obj(ANIM_OBJ_NIGHTMARE, 132, 40, 0x0)
    anim_obj(ANIM_OBJ_NIGHTMARE, 132, 40, 0xa0)
    anim_sound(0, 1, SFX_NIGHTMARE)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_FlameWheel(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_FIRE)
loop:
    anim_sound(0, 0, SFX_EMBER)
    anim_obj(ANIM_OBJ_FLAME_WHEEL, 48, 96, 0x0)
    anim_wait(6)
    anim_loop(8, loop)
    anim_wait(96)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_TACKLE, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x3)
    anim_sound(0, 1, SFX_EMBER)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 48, 0x1)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 48, 0x4)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 48, 0x5)
    anim_wait(8)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(4)
    anim_incobj(9)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_Snore(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_STATUS, ANIM_GFX_NOISE)
    anim_obj(ANIM_OBJ_ASLEEP, 64, 80, 0x0)
    anim_wait(32)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x60, 0x2, 0x0)
    anim_sound(0, 0, SFX_SNORE)
loop:
    anim_call(BattleAnimSub_Sound)
    anim_wait(16)
    anim_loop(2, loop)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_Curse(battleanim_s* anim) {
    ANIM_BEGIN
    anim_if_param_equal(0x1, NotGhost)
    anim_2gfx(ANIM_GFX_HIT, ANIM_GFX_OBJECTS)
    anim_obj(ANIM_OBJ_CURSE, 68, 72, 0x0)
    anim_sound(0, 0, SFX_CURSE)
    anim_wait(32)
    anim_incobj(1)
    anim_wait(12)
    anim_sound(0, 0, SFX_POISON_STING)
    anim_obj(ANIM_OBJ_HIT, 44, 96, 0x0)
    anim_wait(16)
    anim_ret

NotGhost:
    anim_1gfx(ANIM_GFX_SPEED)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_BLACK_REPEATING, 0x0, BG_EFFECT_USER, 0x40)
    anim_sound(0, 0, SFX_SHARPEN)
    anim_wait(64)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_BLACK_REPEATING)
    anim_wait(1)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_LIGHT, 0x0, BG_EFFECT_USER, 0x40)
loop:
    anim_sound(0, 0, SFX_SWORDS_DANCE)
    anim_obj(ANIM_OBJ_FOCUS, 44, 108, 0x6)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 36, 108, 0x6)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 52, 108, 0x8)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 28, 108, 0x8)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 60, 108, 0x6)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 20, 108, 0x8)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 68, 108, 0x8)
    anim_wait(2)
    anim_loop(3, loop)
    anim_wait(8)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_LIGHT)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Flail(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_sound(0, 0, SFX_SUBMISSION)
    anim_bgeffect(ANIM_BG_FLAIL, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_HIT_YFIX, 120, 48, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_HIT_YFIX, 152, 48, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 48, 0x0)
    anim_wait(8)
    anim_incbgeffect(ANIM_BG_FLAIL)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Conversion(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_EXPLOSION)
    anim_bgeffect(ANIM_BG_ALTERNATE_HUES, 0x0, 0x2, 0x0)
    anim_sound(63, 3, SFX_SHARPEN)
    anim_obj(ANIM_OBJ_CONVERSION, 48, 88, 0x0)
    anim_obj(ANIM_OBJ_CONVERSION, 48, 88, 0x8)
    anim_obj(ANIM_OBJ_CONVERSION, 48, 88, 0x10)
    anim_obj(ANIM_OBJ_CONVERSION, 48, 88, 0x18)
    anim_obj(ANIM_OBJ_CONVERSION, 48, 88, 0x20)
    anim_obj(ANIM_OBJ_CONVERSION, 48, 88, 0x28)
    anim_obj(ANIM_OBJ_CONVERSION, 48, 88, 0x30)
    anim_obj(ANIM_OBJ_CONVERSION, 48, 88, 0x38)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_Aeroblast(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_BEAM, ANIM_GFX_AEROBLAST)
    anim_bgp(0x1b)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x50, 0x4, 0x10)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_sound(0, 0, SFX_AEROBLAST)
    anim_obj(ANIM_OBJ_AEROBLAST, 72, 88, 0x0)
    anim_wait(32)
    anim_sound(0, 0, SFX_HYPER_BEAM)
    anim_obj(ANIM_OBJ_BEAM, 80, 84, 0x0)
    anim_wait(2)
    anim_sound(0, 1, SFX_HYPER_BEAM)
    anim_obj(ANIM_OBJ_BEAM, 96, 76, 0x0)
    anim_wait(2)
    anim_sound(0, 1, SFX_HYPER_BEAM)
    anim_obj(ANIM_OBJ_BEAM, 112, 68, 0x0)
    anim_obj(ANIM_OBJ_BEAM_TIP, 126, 62, 0x0)
    anim_wait(48)
    anim_ret
    ANIM_END
}

static int BattleAnim_CottonSpore(battleanim_s* anim) {
    ANIM_BEGIN
    anim_obp0(0x54)
    anim_1gfx(ANIM_GFX_MISC)
    anim_sound(0, 1, SFX_POWDER)
loop:
    anim_obj(ANIM_OBJ_COTTON_SPORE, 132, 32, 0x0)
    anim_wait(8)
    anim_loop(5, loop)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Reversal(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_SHINE, ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x0, 0x0)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT, 112, 64, 0x0)
    anim_wait(2)
    anim_sound(0, 1, SFX_SHINE)
    anim_obj(ANIM_OBJ_FORESIGHT, 120, 56, 0x0)
    anim_wait(2)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT, 128, 56, 0x0)
    anim_wait(2)
    anim_sound(0, 1, SFX_SHINE)
    anim_obj(ANIM_OBJ_FORESIGHT, 136, 48, 0x0)
    anim_wait(2)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT, 144, 48, 0x0)
    anim_wait(2)
    anim_sound(0, 1, SFX_SHINE)
    anim_obj(ANIM_OBJ_FORESIGHT, 152, 40, 0x0)
    anim_wait(24)
    anim_ret
    ANIM_END
}

static int BattleAnim_Spite(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ANGELS)
    anim_obj(ANIM_OBJ_SPITE, 132, 16, 0x0)
    anim_sound(0, 1, SFX_SPITE)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_PowderSnow(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ICE)
loop:
    anim_sound(6, 2, SFX_SHINE)
    anim_obj(ANIM_OBJ_POWDER_SNOW, 64, 88, 0x23)
    anim_wait(2)
    anim_sound(6, 2, SFX_SHINE)
    anim_obj(ANIM_OBJ_POWDER_SNOW, 64, 80, 0x24)
    anim_wait(2)
    anim_sound(6, 2, SFX_SHINE)
    anim_obj(ANIM_OBJ_POWDER_SNOW, 64, 96, 0x23)
    anim_wait(2)
    anim_loop(2, loop)
    anim_bgeffect(ANIM_BG_WHITE_HUES, 0x0, 0x8, 0x0)
    anim_wait(40)
    anim_call(BattleAnimSub_Ice)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Protect(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_OBJECTS)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_obj(ANIM_OBJ_PROTECT, 80, 80, 0x0)
    anim_obj(ANIM_OBJ_PROTECT, 80, 80, 0xd)
    anim_obj(ANIM_OBJ_PROTECT, 80, 80, 0x1a)
    anim_obj(ANIM_OBJ_PROTECT, 80, 80, 0x27)
    anim_obj(ANIM_OBJ_PROTECT, 80, 80, 0x34)
    anim_sound(0, 0, SFX_PROTECT)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_MachPunch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_SPEED, ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_sound(0, 0, SFX_MENU)
    anim_obj(ANIM_OBJ_SPEED_LINE, 24, 88, 0x2)
    anim_obj(ANIM_OBJ_SPEED_LINE, 32, 88, 0x1)
    anim_obj(ANIM_OBJ_SPEED_LINE, 40, 88, 0x0)
    anim_obj(ANIM_OBJ_SPEED_LINE, 48, 88, 0x80)
    anim_obj(ANIM_OBJ_SPEED_LINE, 56, 88, 0x81)
    anim_obj(ANIM_OBJ_SPEED_LINE, 64, 88, 0x82)
    anim_wait(12)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_PUNCH, 136, 56, 0x0)
    anim_wait(6)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(8)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_ScaryFace(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_BEAM)
    anim_bgeffect(ANIM_BG_ALTERNATE_HUES, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_call(BattleAnimSub_EyeBeams)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_FaintAttack(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 0, SFX_CURSE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_WHITE_WAIT_FADE_BACK, 0x0, BG_EFFECT_USER, 0x80)
    anim_wait(96)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT, 120, 32, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT, 152, 40, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT, 136, 48, 0x0)
    anim_wait(32)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_WHITE_WAIT_FADE_BACK)
    anim_call(BattleAnim_ShowMon_0)
    anim_wait(4)
    anim_ret
    ANIM_END
}

static int BattleAnim_SweetKiss(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_OBJECTS, ANIM_GFX_ANGELS)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_obj(ANIM_OBJ_SWEET_KISS, 96, 40, 0x0)
    anim_sound(0, 1, SFX_SWEET_KISS)
    anim_wait(32)
    anim_sound(0, 1, SFX_SWEET_KISS_2)
    anim_obj(ANIM_OBJ_HEART, 120, 40, 0x0)
    anim_wait(40)
    anim_ret
    ANIM_END
}

static int BattleAnim_BellyDrum(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HIT, ANIM_GFX_NOISE)
    anim_sound(0, 0, SFX_BELLY_DRUM)
    anim_obj(ANIM_OBJ_BELLY_DRUM_HAND, 64, 104, 0x0)
    anim_obj(ANIM_OBJ_BELLY_DRUM_NOTE, 64, 92, 0xf8)
    anim_wait(24)
    anim_sound(0, 0, SFX_BELLY_DRUM)
    anim_obj(ANIM_OBJ_BELLY_DRUM_HAND, 64, 104, 0x0)
    anim_obj(ANIM_OBJ_BELLY_DRUM_NOTE, 64, 92, 0xf8)
    anim_wait(24)
    anim_sound(0, 0, SFX_BELLY_DRUM)
    anim_obj(ANIM_OBJ_BELLY_DRUM_HAND, 64, 104, 0x0)
    anim_obj(ANIM_OBJ_BELLY_DRUM_NOTE, 64, 92, 0xf8)
    anim_wait(12)
    anim_sound(0, 0, SFX_BELLY_DRUM)
    anim_obj(ANIM_OBJ_BELLY_DRUM_HAND, 64, 104, 0x0)
    anim_obj(ANIM_OBJ_BELLY_DRUM_NOTE, 64, 92, 0xf8)
    anim_wait(12)
    anim_sound(0, 0, SFX_BELLY_DRUM)
    anim_obj(ANIM_OBJ_BELLY_DRUM_HAND, 64, 104, 0x0)
    anim_obj(ANIM_OBJ_BELLY_DRUM_NOTE, 64, 92, 0xf8)
    anim_wait(24)
    anim_sound(0, 0, SFX_BELLY_DRUM)
    anim_obj(ANIM_OBJ_BELLY_DRUM_HAND, 64, 104, 0x0)
    anim_obj(ANIM_OBJ_BELLY_DRUM_NOTE, 64, 92, 0xf8)
    anim_wait(12)
    anim_sound(0, 0, SFX_BELLY_DRUM)
    anim_obj(ANIM_OBJ_BELLY_DRUM_HAND, 64, 104, 0x0)
    anim_obj(ANIM_OBJ_BELLY_DRUM_NOTE, 64, 92, 0xf8)
    anim_wait(12)
    anim_sound(0, 0, SFX_BELLY_DRUM)
    anim_obj(ANIM_OBJ_BELLY_DRUM_HAND, 64, 104, 0x0)
    anim_obj(ANIM_OBJ_BELLY_DRUM_NOTE, 64, 92, 0xf8)
    anim_wait(12)
    anim_sound(0, 0, SFX_BELLY_DRUM)
    anim_obj(ANIM_OBJ_BELLY_DRUM_HAND, 64, 104, 0x0)
    anim_obj(ANIM_OBJ_BELLY_DRUM_NOTE, 64, 92, 0xf8)
    anim_wait(12)
    anim_ret
    ANIM_END
}

static int BattleAnim_SludgeBomb(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_EGG, ANIM_GFX_POISON)
    anim_bgeffect(ANIM_BG_BLACK_HUES, 0x0, 0x8, 0x0)
    anim_sound(6, 2, SFX_SLUDGE_BOMB)
    anim_obj(ANIM_OBJ_SLUDGE_BOMB, 64, 92, 0x10)
    anim_wait(36)
    anim_call(BattleAnimSub_Sludge)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_MudSlap(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SAND)
    anim_obp0(0xfc)
    anim_call(BattleAnimSub_SandOrMud)
    anim_ret
    ANIM_END
}

static int BattleAnim_Octazooka(battleanim_s* anim) {
    ANIM_BEGIN
    anim_3gfx(ANIM_GFX_HAZE, ANIM_GFX_EGG, ANIM_GFX_SMOKE)
    anim_sound(6, 2, SFX_SLUDGE_BOMB)
    anim_obj(ANIM_OBJ_OCTAZOOKA, 64, 92, 0x4)
    anim_wait(16)
    anim_obj(ANIM_OBJ_BALL_POOF, 132, 56, 0x10)
    anim_wait(8)
    anim_if_param_equal(0x0, done)
loop:
    anim_obj(ANIM_OBJ_SMOKE, 132, 60, 0x20)
    anim_wait(8)
    anim_loop(5, loop)
    anim_wait(128)
done:
    anim_ret
    ANIM_END
}

static int BattleAnim_Spikes(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_MISC)
    anim_sound(6, 2, SFX_MENU)
    anim_obj(ANIM_OBJ_SPIKES, 48, 88, 0x20)
    anim_wait(8)
    anim_sound(6, 2, SFX_MENU)
    anim_obj(ANIM_OBJ_SPIKES, 48, 88, 0x30)
    anim_wait(8)
    anim_sound(6, 2, SFX_MENU)
    anim_obj(ANIM_OBJ_SPIKES, 48, 88, 0x28)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_ZapCannon(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_LIGHTNING, ANIM_GFX_EXPLOSION)
    anim_bgp(0x1b)
    anim_obp0(0x30)
    anim_sound(6, 2, SFX_ZAP_CANNON)
    anim_obj(ANIM_OBJ_ZAP_CANNON, 64, 92, 0x2)
    anim_wait(40)
    anim_sound(0, 1, SFX_THUNDERSHOCK)
    anim_obj(ANIM_OBJ_THUNDERBOLT_BALL, 136, 56, 0x2)
    anim_wait(16)
    anim_obj(ANIM_OBJ_SPARKS_CIRCLE_BIG, 136, 56, 0x0)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_Foresight(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SHINE)
    anim_call(BattleAnim_UserObj_1Row)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x0, 0x0)
    anim_sound(0, 1, SFX_FORESIGHT)
    anim_obj(ANIM_OBJ_FORESIGHT, 132, 40, 0x0)
    anim_wait(24)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_BLACK_REPEATING, 0x0, BG_EFFECT_TARGET, 0x40)
    anim_wait(64)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_BLACK_REPEATING)
    anim_call(BattleAnim_ShowMon_1)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_DestinyBond(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ANGELS)
    anim_bgp(0x1b)
    anim_obp0(0x0)
    anim_if_param_equal(0x1, fainted)
    anim_sound(6, 2, SFX_WHIRLWIND)
    anim_obj(ANIM_OBJ_DESTINY_BOND, 44, 120, 0x2)
    anim_wait(128)
	anim_ret

fainted:
    anim_obj(ANIM_OBJ_DESTINY_BOND, 132, 76, 0x0)
    anim_sound(0, 1, SFX_KINESIS)
    anim_bgeffect(ANIM_BG_RETURN_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_PerishSong(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_NOISE)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_ALTERNATE_HUES, 0x0, 0x2, 0x0)
    anim_sound(0, 2, SFX_PERISH_SONG)
    anim_obj(ANIM_OBJ_PERISH_SONG, 88, 0, 0x0)
    anim_obj(ANIM_OBJ_PERISH_SONG, 88, 0, 0x8)
    anim_obj(ANIM_OBJ_PERISH_SONG, 88, 0, 0x10)
    anim_obj(ANIM_OBJ_PERISH_SONG, 88, 0, 0x18)
    anim_obj(ANIM_OBJ_PERISH_SONG, 88, 0, 0x20)
    anim_obj(ANIM_OBJ_PERISH_SONG, 88, 0, 0x28)
    anim_obj(ANIM_OBJ_PERISH_SONG, 88, 0, 0x30)
    anim_obj(ANIM_OBJ_PERISH_SONG, 88, 0, 0x38)
    anim_wait(112)
    anim_ret
    ANIM_END
}

static int BattleAnim_IcyWind(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SPEED)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_ALTERNATE_HUES, 0x0, 0x2, 0x0)
    anim_battlergfx_2row // anim_battlergfx_1row
    anim_sound(0, 0, SFX_PSYCHIC)
loop:
    anim_wait(8)
    anim_obj(ANIM_OBJ_SHOOTING_SPARKLE, 64, 88, 0x4)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SHOOTING_SPARKLE, 64, 80, 0x4)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SHOOTING_SPARKLE, 64, 96, 0x4)
    anim_wait(8)
    anim_loop(2, loop)
    anim_wait(16)
    anim_bgeffect(ANIM_BG_BATTLEROBJ_2ROW, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(6)
    anim_bgeffect(ANIM_BG_NIGHT_SHADE, 0x0, BG_EFFECT_TARGET, 0x8)
    anim_wait(64)
    anim_incbgeffect(ANIM_BG_NIGHT_SHADE)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_incobj(7)
    anim_wait(1)
    anim_ret
    ANIM_END
}

static int BattleAnim_Detect(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SHINE)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x0, 0x0)
    anim_sound(0, 0, SFX_FORESIGHT)
    anim_obj(ANIM_OBJ_FORESIGHT, 64, 88, 0x0)
    anim_wait(24)
    anim_ret
    ANIM_END
}

static int BattleAnim_BoneRush(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HIT, ANIM_GFX_MISC)
    anim_sound(0, 1, SFX_BONE_CLUB)
    anim_obj(ANIM_OBJ_BONE_RUSH, 132, 56, 0x2)
    anim_wait(16)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_YFIX, 120, 48, 0x0)
    anim_wait(16)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 64, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_LockOn(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_MISC)
    anim_sound(0, 1, SFX_MIND_READER)
loop:
    anim_obj(ANIM_OBJ_LOCK_ON, 132, 48, 0x3)
    anim_obj(ANIM_OBJ_LOCK_ON, 132, 48, 0x12)
    anim_obj(ANIM_OBJ_LOCK_ON, 132, 48, 0x20)
    anim_obj(ANIM_OBJ_LOCK_ON, 132, 48, 0x31)
    anim_wait(16)
    anim_loop(2, loop)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Outrage(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING, 0x0, BG_EFFECT_USER, 0x20)
    anim_sound(0, 0, SFX_OUTRAGE)
    anim_wait(72)
    anim_incbgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x3)
    anim_sound(0, 1, SFX_MOVE_PUZZLE_PIECE)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 120, 72, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 152, 40, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Sandstorm(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_POWDER)
    anim_obj(ANIM_OBJ_SANDSTORM, 88, 0, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SANDSTORM, 72, 0, 0x1)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SANDSTORM, 56, 0, 0x2)
loop:
    anim_sound(0, 1, SFX_MENU)
    anim_wait(8)
    anim_loop(16, loop)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_GigaDrain(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_BUBBLE, ANIM_GFX_CHARGE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_FADE_MONS_TO_BLACK_REPEATING, 0x0, BG_EFFECT_TARGET, 0x10)
    anim_sound(6, 3, SFX_GIGA_DRAIN)
    anim_call(BattleAnimSub_Drain)
    anim_wait(48)
    anim_wait(128)
    anim_incbgeffect(ANIM_BG_FADE_MONS_TO_BLACK_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_wait(1)
    anim_1gfx(ANIM_GFX_SHINE)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x0, 0x0)
loop:
    anim_sound(0, 0, SFX_METRONOME)
    anim_obj(ANIM_OBJ_GLIMMER, 24, 64, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_GLIMMER, 56, 104, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_GLIMMER, 24, 104, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_GLIMMER, 56, 64, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_GLIMMER, 40, 84, 0x0)
    anim_wait(5)
    anim_loop(2, loop)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Endure(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SPEED)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING, 0x0, BG_EFFECT_USER, 0x20)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
loop:
    anim_sound(0, 0, SFX_SWORDS_DANCE)
    anim_obj(ANIM_OBJ_FOCUS, 44, 108, 0x6)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 36, 108, 0x6)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 52, 108, 0x8)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 28, 108, 0x8)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 60, 108, 0x6)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 20, 108, 0x8)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FOCUS, 68, 108, 0x8)
    anim_wait(2)
    anim_loop(5, loop)
    anim_wait(8)
    anim_incbgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Charm(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_OBJECTS)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_WOBBLE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_sound(0, 0, SFX_ATTRACT)
    anim_obj(ANIM_OBJ_HEART, 64, 80, 0x0)
    anim_wait(32)
    anim_incbgeffect(ANIM_BG_WOBBLE_MON)
    anim_call(BattleAnim_ShowMon_0)
    anim_wait(4)
    anim_ret
    ANIM_END
}

static int BattleAnim_Rollout(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_sound(0, 0, SFX_SPARK)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_ROLLOUT, 0x60, 0x1, 0x1)
    anim_bgeffect(ANIM_BG_BODY_SLAM, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG, 136, 40, 0x0)
    anim_wait(8)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_FalseSwipe(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_SHINE, ANIM_GFX_CUT)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x0, 0x0)
    anim_sound(0, 1, SFX_CUT)
    anim_obj(ANIM_OBJ_CUT_LONG_DOWN_LEFT, 152, 40, 0x0)
    anim_wait(4)
    anim_obj(ANIM_OBJ_GLIMMER, 136, 40, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Swagger(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_MISC, ANIM_GFX_WIND)
loop:
    anim_sound(0, 0, SFX_MENU)
    anim_obj(ANIM_OBJ_SWAGGER, 72, 88, 0x44)
    anim_wait(32)
    anim_loop(2, loop)
    anim_wait(32)
    anim_sound(0, 1, SFX_KINESIS_2)
    anim_obj(ANIM_OBJ_ANGER, 104, 40, 0x0)
    anim_wait(40)
    anim_ret
    ANIM_END
}

static int BattleAnim_MilkDrink(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_MISC, ANIM_GFX_BUBBLE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_obj(ANIM_OBJ_MILK_DRINK, 74, 104, 0x0)
    anim_wait(16)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING, 0x0, BG_EFFECT_USER, 0x40)
    anim_sound(0, 0, SFX_MILK_DRINK)
loop:
    anim_obj(ANIM_OBJ_RECOVER, 44, 88, 0x20)
    anim_wait(8)
    anim_loop(8, loop)
    anim_wait(128)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Spark(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_LIGHTNING, ANIM_GFX_EXPLOSION)
    anim_sound(0, 0, SFX_ZAP_CANNON)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x4, 0x3)
    anim_obj(ANIM_OBJ_THUNDER_WAVE, 48, 92, 0x0)
    anim_wait(24)
    anim_setobj(0x1, 0x3)
    anim_wait(1)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_TACKLE, 0x0, BG_EFFECT_USER, 0x0)
    anim_sound(0, 0, SFX_SPARK)
    anim_wait(16)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(4)
    anim_incobj(2)
    anim_wait(1)
    anim_sound(0, 1, SFX_THUNDERSHOCK)
    anim_obj(ANIM_OBJ_THUNDERBOLT_BALL, 136, 56, 0x2)
    anim_obj(ANIM_OBJ_SPARKS_CIRCLE, 136, 56, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_FuryCutter(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CUT)
loop:
    anim_sound(0, 1, SFX_CUT)
    anim_if_param_and(0b00000001, obj1)
    anim_obj(ANIM_OBJ_CUT_LONG_DOWN_LEFT, 152, 40, 0x0)
    anim_jump(okay)

obj1:
    anim_obj(ANIM_OBJ_CUT_LONG_DOWN_RIGHT, 112, 40, 0x0)
okay:
    anim_wait(16)
    anim_jumpuntil(loop)
    anim_ret
    ANIM_END
}

static int BattleAnim_SteelWing(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_REFLECT)
    anim_obp0(0x0)
    anim_sound(0, 0, SFX_RAGE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_call(BattleAnimSub_Metallic)
    anim_call(BattleAnim_ShowMon_0)
    anim_1gfx(ANIM_GFX_HIT)
	anim_resetobp0
    anim_sound(0, 1, SFX_WING_ATTACK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 148, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_YFIX, 116, 56, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_WING_ATTACK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_YFIX, 120, 56, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_WING_ATTACK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 140, 56, 0x0)
    anim_obj(ANIM_OBJ_HIT_YFIX, 124, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_MeanLook(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_PSYCHIC)
    anim_obp0(0xe0)
    anim_sound(0, 1, SFX_MEAN_LOOK)
    anim_obj(ANIM_OBJ_MEAN_LOOK, 148, 32, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_MEAN_LOOK, 116, 64, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_MEAN_LOOK, 148, 64, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_MEAN_LOOK, 116, 32, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_MEAN_LOOK, 132, 48, 0x0)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_Attract(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_OBJECTS)
loop:
    anim_sound(0, 0, SFX_ATTRACT)
    anim_obj(ANIM_OBJ_ATTRACT, 44, 80, 0x2)
    anim_wait(8)
    anim_loop(5, loop)
    anim_wait(128)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_SleepTalk(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_STATUS)
loop:
    anim_sound(0, 0, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_ASLEEP, 64, 80, 0x0)
    anim_wait(40)
    anim_loop(2, loop)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_HealBell(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_MISC, ANIM_GFX_NOISE)
    anim_obj(ANIM_OBJ_HEAL_BELL, 72, 56, 0x0)
    anim_wait(32)
loop:
    anim_sound(0, 0, SFX_HEAL_BELL)
    anim_obj(ANIM_OBJ_HEAL_BELL_NOTE, 72, 52, 0x0)
    anim_wait(8)
    anim_sound(0, 0, SFX_HEAL_BELL)
    anim_obj(ANIM_OBJ_HEAL_BELL_NOTE, 72, 52, 0x1)
    anim_wait(8)
    anim_sound(0, 0, SFX_HEAL_BELL)
    anim_obj(ANIM_OBJ_HEAL_BELL_NOTE, 72, 52, 0x2)
    anim_wait(8)
    anim_sound(0, 0, SFX_HEAL_BELL)
    anim_obj(ANIM_OBJ_HEAL_BELL_NOTE, 72, 52, 0x0)
    anim_wait(8)
    anim_sound(0, 0, SFX_HEAL_BELL)
    anim_obj(ANIM_OBJ_HEAL_BELL_NOTE, 72, 52, 0x2)
    anim_wait(8)
    anim_loop(4, loop)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Return(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_BOUNCE_DOWN, 0x0, BG_EFFECT_USER, 0x0)
    anim_sound(0, 0, SFX_RETURN)
    anim_wait(64)
    anim_incbgeffect(ANIM_BG_BOUNCE_DOWN)
    anim_wait(32)
    anim_bgeffect(ANIM_BG_BODY_SLAM, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG, 136, 40, 0x0)
    anim_wait(8)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Present(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_STATUS, ANIM_GFX_BUBBLE)
    anim_sound(0, 1, SFX_PRESENT)
    anim_obj(ANIM_OBJ_PRESENT, 64, 88, 0x6c)
    anim_wait(56)
    anim_obj(ANIM_OBJ_AMNESIA, 104, 48, 0x0)
    anim_wait(48)
    anim_incobj(2)
    anim_if_param_equal(0x3, heal)
    anim_incobj(1)
    anim_wait(1)
    anim_1gfx(ANIM_GFX_EXPLOSION)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x12)
loop:
    anim_call(BattleAnimSub_Explosion2)
    anim_wait(16)
    anim_jumpuntil(loop)
    anim_ret

heal:
    anim_sound(0, 1, SFX_METRONOME)
loop2:
    anim_obj(ANIM_OBJ_RECOVER, 132, 48, 0x24)
    anim_wait(8)
    anim_loop(8, loop2)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_Frustration(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_MISC)
    anim_sound(0, 0, SFX_KINESIS_2)
    anim_obj(ANIM_OBJ_ANGER, 72, 80, 0x0)
    anim_wait(40)
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_WOBBLE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_YFIX, 120, 48, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_YFIX, 152, 48, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 48, 0x0)
    anim_wait(8)
    anim_incbgeffect(ANIM_BG_WOBBLE_MON)
    anim_wait(1)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_Safeguard(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_MISC)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_obj(ANIM_OBJ_SAFEGUARD, 80, 80, 0x0)
    anim_obj(ANIM_OBJ_SAFEGUARD, 80, 80, 0xd)
    anim_obj(ANIM_OBJ_SAFEGUARD, 80, 80, 0x1a)
    anim_obj(ANIM_OBJ_SAFEGUARD, 80, 80, 0x27)
    anim_obj(ANIM_OBJ_SAFEGUARD, 80, 80, 0x34)
    anim_sound(0, 0, SFX_PROTECT)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_PainSplit(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HIT, ANIM_GFX_OBJECTS)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_BODY_SLAM, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_TACKLE)
    anim_obj(ANIM_OBJ_HIT, 112, 48, 0x0)
    anim_obj(ANIM_OBJ_HIT, 76, 96, 0x0)
    anim_wait(8)
    anim_call(BattleAnim_ShowMon_0)
    anim_wait(1)
    anim_ret
    ANIM_END
}

static int BattleAnim_SacredFire(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_FIRE)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_ALTERNATE_HUES, 0x0, 0x2, 0x0)
loop:
    anim_sound(0, 0, SFX_EMBER)
    anim_obj(ANIM_OBJ_SACRED_FIRE, 48, 104, 0x0)
    anim_wait(8)
    anim_loop(8, loop)
    anim_wait(96)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_TACKLE, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_EMBER)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 48, 0x1)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 48, 0x4)
    anim_obj(ANIM_OBJ_FIRE_BLAST, 136, 48, 0x5)
    anim_wait(8)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(4)
    anim_incobj(9)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_Magnitude(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_ROCKS)
loop:
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0xe, 0x4, 0x0)
    anim_sound(0, 1, SFX_STRENGTH)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 128, 64, 0x40)
    anim_wait(2)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 120, 68, 0x30)
    anim_wait(2)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 152, 68, 0x30)
    anim_wait(2)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 144, 64, 0x40)
    anim_wait(2)
    anim_obj(ANIM_OBJ_SMALL_ROCK, 136, 68, 0x30)
    anim_wait(2)
    anim_jumpuntil(loop)
    anim_wait(96)
    anim_ret
    ANIM_END
}

static int BattleAnim_Dynamicpunch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HIT, ANIM_GFX_EXPLOSION)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_PUNCH_SHAKE, 136, 56, 0x43)
    anim_wait(16)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x12)
    anim_call(BattleAnimSub_Explosion2)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Megahorn(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_HORN, ANIM_GFX_HIT)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x40, 0x2, 0x0)
    anim_wait(48)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x3)
    anim_obj(ANIM_OBJ_HORN, 72, 80, 0x1)
    anim_sound(0, 1, SFX_HORN_ATTACK)
    anim_wait(16)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Dragonbreath(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_FIRE)
    anim_sound(6, 2, SFX_EMBER)
loop:
    anim_obj(ANIM_OBJ_DRAGONBREATH, 64, 92, 0x4)
    anim_wait(4)
    anim_loop(10, loop)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_BatonPass(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_MISC)
    anim_obj(ANIM_OBJ_BATON_PASS, 44, 104, 0x20)
    anim_sound(0, 0, SFX_BATON_PASS)
    anim_call(BattleAnimSub_Return)
    anim_wait(64)
    anim_ret
    ANIM_END
}

static int BattleAnim_Encore(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_OBJECTS)
    anim_obj(ANIM_OBJ_ENCORE_HAND, 64, 80, 0x90)
    anim_obj(ANIM_OBJ_ENCORE_HAND, 64, 80, 0x10)
    anim_sound(0, 0, SFX_ENCORE)
    anim_wait(16)
    anim_obj(ANIM_OBJ_ENCORE_STAR, 64, 72, 0x2c)
    anim_wait(32)
    anim_obj(ANIM_OBJ_ENCORE_STAR, 64, 72, 0x34)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Pursuit(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_if_param_equal(0x1, pursued)
    anim_sound(0, 1, SFX_COMET_PUNCH)
    anim_obj(ANIM_OBJ_HIT_YFIX, 136, 56, 0x0)
    anim_wait(16)
    anim_ret

pursued:
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(4)
    anim_call(BattleAnim_UserObj_1Row)
    anim_obj(ANIM_OBJ_BETA_PURSUIT, 132, 64, 0x0)
    anim_wait(64)
    anim_obj(ANIM_OBJ_BETA_PURSUIT, 132, 64, 0x1)
    anim_sound(0, 1, SFX_BALL_POOF)
    anim_bgeffect(ANIM_BG_ENTER_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(64)
    anim_incobj(3)
    anim_wait(16)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 120, 56, 0x0)
    anim_bgeffect(ANIM_BG_BETA_PURSUIT, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(16)
    anim_call(BattleAnim_ShowMon_1)
    anim_wait(1)
    anim_ret
    ANIM_END
}

static int BattleAnim_RapidSpin(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_WIND, ANIM_GFX_HIT)
    anim_obp0(0xe4)
loop:
    anim_sound(0, 0, SFX_MENU)
    anim_obj(ANIM_OBJ_RAPID_SPIN, 44, 112, 0x0)
    anim_wait(2)
    anim_loop(5, loop)
    anim_wait(24)
    anim_call(BattleAnim_TargetObj_2Row)
    anim_bgeffect(ANIM_BG_BODY_SLAM, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
	anim_resetobp0
    anim_sound(0, 1, SFX_MEGA_KICK)
    anim_obj(ANIM_OBJ_HIT, 136, 40, 0x0)
    anim_wait(8)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(4)
    anim_incobj(6)
    anim_wait(1)
    anim_ret
    ANIM_END
}

static int BattleAnim_SweetScent(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_FLOWER, ANIM_GFX_MISC)
    anim_sound(0, 0, SFX_SWEET_SCENT)
    anim_obj(ANIM_OBJ_FLOWER, 64, 96, 0x2)
    anim_wait(2)
    anim_obj(ANIM_OBJ_FLOWER, 64, 80, 0x2)
    anim_wait(96)
    anim_obp0(0x54)
    anim_sound(0, 1, SFX_SWEET_SCENT_2)
    anim_obj(ANIM_OBJ_COTTON, 136, 40, 0x15)
    anim_obj(ANIM_OBJ_COTTON, 136, 40, 0x2a)
    anim_obj(ANIM_OBJ_COTTON, 136, 40, 0x3f)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_IronTail(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_REFLECT)
    anim_obp0(0x0)
    anim_sound(0, 0, SFX_RAGE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_call(BattleAnimSub_Metallic)
    anim_wait(4)
    anim_1gfx(ANIM_GFX_HIT)
	anim_resetobp0
    anim_bgeffect(ANIM_BG_WOBBLE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(16)
    anim_sound(0, 1, SFX_MEGA_KICK)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 48, 0x0)
    anim_wait(16)
    anim_incbgeffect(ANIM_BG_WOBBLE_MON)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnim_MetalClaw(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_REFLECT)
    anim_obp0(0x0)
    anim_sound(0, 0, SFX_RAGE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_call(BattleAnimSub_Metallic)
    anim_call(BattleAnim_ShowMon_0)
    anim_1gfx(ANIM_GFX_CUT)
    anim_resetobp0
    anim_sound(0, 1, SFX_SCRATCH)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 144, 48, 0x0)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 140, 44, 0x0)
    anim_obj(ANIM_OBJ_CUT_DOWN_LEFT, 136, 40, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_VitalThrow(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_VITAL_THROW, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(16)
    anim_sound(0, 0, SFX_MENU)
    anim_obj(ANIM_OBJ_HIT, 64, 96, 0x0)
    anim_wait(8)
    anim_sound(0, 0, SFX_MENU)
    anim_obj(ANIM_OBJ_HIT, 56, 88, 0x0)
    anim_wait(8)
    anim_sound(0, 0, SFX_MENU)
    anim_obj(ANIM_OBJ_HIT, 68, 104, 0x0)
    anim_wait(8)
    anim_incbgeffect(ANIM_BG_VITAL_THROW)
    anim_wait(16)
    anim_call(BattleAnim_ShowMon_0)
    anim_sound(0, 1, SFX_MEGA_PUNCH)
    anim_obj(ANIM_OBJ_HIT_BIG, 132, 56, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_MorningSun(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SHINE)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x0, 0x0)
    anim_sound(0, 0, SFX_MORNING_SUN)
loop:
    anim_obj(ANIM_OBJ_MORNING_SUN, 16, 48, 0x88)
    anim_wait(6)
    anim_loop(5, loop)
    anim_wait(32)
    anim_if_param_equal(0, zero)
    anim_call(BattleAnimSub_Glimmer)
    anim_ret

zero:
    anim_call(BattleAnimSub_Glimmer2)
    anim_ret
    ANIM_END
}

static int BattleAnim_Synthesis(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SHINE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING, 0x0, BG_EFFECT_USER, 0x40)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x0, 0x0)
    anim_sound(0, 0, SFX_OUTRAGE)
    anim_wait(72)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_LIGHT_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_if_param_equal(0x1, one)
    anim_call(BattleAnimSub_Glimmer)
    anim_ret

one:
    anim_call(BattleAnimSub_Glimmer2)
    anim_ret
    ANIM_END
}

static int BattleAnim_Crunch(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_CUT, ANIM_GFX_HIT)
    anim_bgp(0x1b)
    anim_obp0(0xc0)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x20, 0x2, 0x0)
    anim_obj(ANIM_OBJ_BITE, 136, 56, 0xa8)
    anim_obj(ANIM_OBJ_BITE, 136, 56, 0x28)
    anim_wait(8)
    anim_sound(0, 1, SFX_BITE)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 144, 48, 0x18)
    anim_wait(16)
    anim_sound(0, 1, SFX_BITE)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 128, 64, 0x18)
    anim_wait(8)
    anim_ret
    ANIM_END
}

static int BattleAnim_Moonlight(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_SHINE)
    anim_bgp(0x1b)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x0, 0x0)
    anim_obj(ANIM_OBJ_MOONLIGHT, 0, 40, 0x0)
    anim_obj(ANIM_OBJ_MOONLIGHT, 16, 56, 0x0)
    anim_obj(ANIM_OBJ_MOONLIGHT, 32, 72, 0x0)
    anim_obj(ANIM_OBJ_MOONLIGHT, 48, 88, 0x0)
    anim_obj(ANIM_OBJ_MOONLIGHT, 64, 104, 0x0)
    anim_wait(1)
    anim_sound(0, 0, SFX_MOONLIGHT)
    anim_wait(63)
    anim_if_param_equal(0x3, three)
    anim_call(BattleAnimSub_Glimmer)
	anim_ret

three:
    anim_call(BattleAnimSub_Glimmer2)
    anim_ret
    ANIM_END
}

static int BattleAnim_HiddenPower(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CHARGE)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING, 0x0, BG_EFFECT_USER, 0x20)
    anim_bgeffect(ANIM_BG_CYCLE_MID_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_obj(ANIM_OBJ_HIDDEN_POWER, 44, 88, 0x0)
    anim_obj(ANIM_OBJ_HIDDEN_POWER, 44, 88, 0x8)
    anim_obj(ANIM_OBJ_HIDDEN_POWER, 44, 88, 0x10)
    anim_obj(ANIM_OBJ_HIDDEN_POWER, 44, 88, 0x18)
    anim_obj(ANIM_OBJ_HIDDEN_POWER, 44, 88, 0x20)
    anim_obj(ANIM_OBJ_HIDDEN_POWER, 44, 88, 0x28)
    anim_obj(ANIM_OBJ_HIDDEN_POWER, 44, 88, 0x30)
    anim_obj(ANIM_OBJ_HIDDEN_POWER, 44, 88, 0x38)
loop:
    anim_sound(0, 0, SFX_SWORDS_DANCE)
    anim_wait(8)
    anim_loop(12, loop)
    anim_incbgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_wait(1)
    anim_incobj(2)
    anim_incobj(3)
    anim_incobj(4)
    anim_incobj(5)
    anim_incobj(6)
    anim_incobj(7)
    anim_incobj(8)
    anim_incobj(9)
    anim_wait(16)
    anim_1gfx(ANIM_GFX_HIT)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_CrossChop(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_CUT)
    anim_sound(0, 1, SFX_CUT)
    anim_obj(ANIM_OBJ_CROSS_CHOP1, 152, 40, 0x0)
    anim_obj(ANIM_OBJ_CROSS_CHOP2, 120, 72, 0x0)
    anim_wait(8)
    anim_bgeffect(ANIM_BG_SHAKE_SCREEN_X, 0x58, 0x2, 0x0)
    anim_wait(92)
    anim_sound(0, 1, SFX_VICEGRIP)
    anim_bgeffect(ANIM_BG_FLASH_INVERTED, 0x0, 0x8, 0x10)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Twister(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_WIND, ANIM_GFX_HIT)
loop1:
    anim_sound(0, 0, SFX_RAZOR_WIND)
    anim_obj(ANIM_OBJ_GUST, 64, 112, 0x0)
    anim_wait(6)
    anim_loop(9, loop1)
loop2:
    anim_sound(0, 0, SFX_RAZOR_WIND)
    anim_wait(8)
    anim_loop(8, loop2)
    anim_incobj(1)
    anim_incobj(2)
    anim_incobj(3)
    anim_incobj(4)
    anim_incobj(5)
    anim_incobj(6)
    anim_incobj(7)
    anim_incobj(8)
    anim_incobj(9)
    anim_wait(64)
    anim_obj(ANIM_OBJ_HIT_YFIX, 144, 64, 0x18)
loop3:
    anim_sound(0, 1, SFX_RAZOR_WIND)
    anim_wait(8)
    anim_loop(4, loop3)
    anim_obj(ANIM_OBJ_HIT_YFIX, 128, 32, 0x18)
loop4:
    anim_sound(0, 1, SFX_RAZOR_WIND)
    anim_wait(8)
    anim_loop(4, loop4)
    anim_incobj(1)
    anim_incobj(2)
    anim_incobj(3)
    anim_incobj(4)
    anim_incobj(5)
    anim_incobj(6)
    anim_incobj(7)
    anim_incobj(8)
    anim_incobj(9)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_RainDance(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WATER)
    anim_bgp(0xf8)
    anim_obp0(0x7c)
    anim_sound(0, 1, SFX_RAIN_DANCE)
    anim_obj(ANIM_OBJ_RAIN, 88, 0, 0x0)
    anim_wait(8)
    anim_obj(ANIM_OBJ_RAIN, 88, 0, 0x1)
    anim_wait(8)
    anim_obj(ANIM_OBJ_RAIN, 88, 0, 0x2)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_SunnyDay(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WATER)
    anim_bgp(0x90)
    anim_sound(0, 1, SFX_MORNING_SUN)
    anim_obj(ANIM_OBJ_RAIN, 88, 0, 0x2)
    anim_wait(8)
    anim_obj(ANIM_OBJ_RAIN, 88, 0, 0x2)
    anim_wait(8)
    anim_obj(ANIM_OBJ_RAIN, 88, 0, 0x2)
    anim_wait(128)
    anim_ret
    ANIM_END
}

static int BattleAnim_MirrorCoat(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_REFLECT, ANIM_GFX_SPEED)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
loop:
    anim_sound(0, 0, SFX_SHINE)
    anim_obj(ANIM_OBJ_SCREEN, 72, 80, 0x0)
    anim_obj(ANIM_OBJ_SHOOTING_SPARKLE, 64, 72, 0x4)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SHOOTING_SPARKLE, 64, 88, 0x4)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SHOOTING_SPARKLE, 64, 80, 0x4)
    anim_wait(8)
    anim_obj(ANIM_OBJ_SHOOTING_SPARKLE, 64, 96, 0x4)
    anim_wait(8)
    anim_loop(3, loop)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_PsychUp(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_STATUS)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING, 0x0, BG_EFFECT_USER, 0x20)
    anim_sound(0, 0, SFX_PSYBEAM)
    anim_obj(ANIM_OBJ_PSYCH_UP, 44, 88, 0x0)
    anim_obj(ANIM_OBJ_PSYCH_UP, 44, 88, 0x10)
    anim_obj(ANIM_OBJ_PSYCH_UP, 44, 88, 0x20)
    anim_obj(ANIM_OBJ_PSYCH_UP, 44, 88, 0x30)
    anim_wait(64)
    anim_incbgeffect(ANIM_BG_CYCLE_MON_LIGHT_DARK_REPEATING)
    anim_call(BattleAnim_ShowMon_0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Extremespeed(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_SPEED, ANIM_GFX_CUT)
    anim_bgeffect(ANIM_BG_HIDE_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_sound(0, 0, SFX_MENU)
    anim_obj(ANIM_OBJ_SPEED_LINE, 24, 88, 0x2)
    anim_obj(ANIM_OBJ_SPEED_LINE, 32, 88, 0x1)
    anim_obj(ANIM_OBJ_SPEED_LINE, 40, 88, 0x0)
    anim_obj(ANIM_OBJ_SPEED_LINE, 48, 88, 0x80)
    anim_obj(ANIM_OBJ_SPEED_LINE, 56, 88, 0x81)
    anim_obj(ANIM_OBJ_SPEED_LINE, 64, 88, 0x82)
    anim_wait(12)
    anim_sound(0, 1, SFX_CUT)
    anim_obj(ANIM_OBJ_CUT_LONG_DOWN_LEFT, 152, 40, 0x0)
    anim_wait(32)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_Ancientpower(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_ROCKS, ANIM_GFX_HIT)
    anim_sound(0, 0, SFX_SPARK)
    anim_obj(ANIM_OBJ_ANCIENTPOWER, 64, 108, 0x20)
    anim_wait(8)
    anim_sound(0, 0, SFX_SPARK)
    anim_obj(ANIM_OBJ_ANCIENTPOWER, 75, 102, 0x20)
    anim_wait(8)
    anim_sound(0, 0, SFX_SPARK)
    anim_obj(ANIM_OBJ_ANCIENTPOWER, 85, 97, 0x20)
    anim_wait(8)
    anim_sound(0, 0, SFX_SPARK)
    anim_obj(ANIM_OBJ_ANCIENTPOWER, 96, 92, 0x20)
    anim_wait(8)
    anim_sound(0, 1, SFX_SPARK)
    anim_obj(ANIM_OBJ_ANCIENTPOWER, 106, 87, 0x20)
    anim_wait(8)
    anim_sound(0, 1, SFX_SPARK)
    anim_obj(ANIM_OBJ_ANCIENTPOWER, 116, 82, 0x20)
    anim_wait(8)
    anim_sound(0, 1, SFX_SPARK)
    anim_obj(ANIM_OBJ_ANCIENTPOWER, 126, 77, 0x20)
    anim_wait(8)
    anim_sound(0, 1, SFX_SPARK)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 56, 0x0)
    anim_wait(6)
    anim_ret
    ANIM_END
}

static int BattleAnim_ShadowBall(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_EGG, ANIM_GFX_SMOKE)
    anim_bgp(0x1b)
    anim_sound(6, 2, SFX_SLUDGE_BOMB)
    anim_obj(ANIM_OBJ_SHADOW_BALL, 64, 92, 0x2)
    anim_wait(32)
    anim_obj(ANIM_OBJ_BALL_POOF, 132, 56, 0x10)
    anim_wait(24)
    anim_ret
    ANIM_END
}

static int BattleAnim_FutureSight(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WIND)
    anim_bgeffect(ANIM_BG_CYCLE_OBPALS_GRAY_AND_YELLOW, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_ALTERNATE_HUES, 0x0, 0x2, 0x0)
    anim_bgeffect(ANIM_BG_PSYCHIC, 0x0, 0x0, 0x0)
    anim_obj(ANIM_OBJ_AGILITY, 8, 24, 0x10)
    anim_obj(ANIM_OBJ_AGILITY, 8, 48, 0x2)
    anim_obj(ANIM_OBJ_AGILITY, 8, 88, 0x8)
    anim_wait(4)
    anim_obj(ANIM_OBJ_AGILITY, 8, 32, 0x6)
    anim_obj(ANIM_OBJ_AGILITY, 8, 56, 0xc)
    anim_obj(ANIM_OBJ_AGILITY, 8, 80, 0x4)
    anim_obj(ANIM_OBJ_AGILITY, 8, 104, 0xe)
loop:
    anim_sound(0, 0, SFX_THROW_BALL)
    anim_wait(16)
    anim_loop(4, loop)
    anim_incbgeffect(ANIM_BG_PSYCHIC)
    anim_ret
    ANIM_END
}

static int BattleAnim_RockSmash(battleanim_s* anim) {
    ANIM_BEGIN
    anim_2gfx(ANIM_GFX_ROCKS, ANIM_GFX_HIT)
    anim_sound(0, 1, SFX_SPARK)
    anim_obj(ANIM_OBJ_HIT_YFIX, 128, 56, 0x0)
    anim_sound(0, 1, SFX_SPARK)
    anim_obj(ANIM_OBJ_ROCK_SMASH, 128, 64, 0x28)
    anim_obj(ANIM_OBJ_ROCK_SMASH, 128, 64, 0x5c)
    anim_sound(0, 1, SFX_SPARK)
    anim_obj(ANIM_OBJ_ROCK_SMASH, 128, 64, 0x10)
    anim_obj(ANIM_OBJ_ROCK_SMASH, 128, 64, 0xe8)
    anim_sound(0, 1, SFX_SPARK)
    anim_obj(ANIM_OBJ_ROCK_SMASH, 128, 64, 0x9c)
    anim_obj(ANIM_OBJ_ROCK_SMASH, 128, 64, 0xd0)
    anim_wait(6)
    anim_sound(0, 1, SFX_SPARK)
    anim_obj(ANIM_OBJ_ROCK_SMASH, 128, 64, 0x1c)
    anim_obj(ANIM_OBJ_ROCK_SMASH, 128, 64, 0x50)
    anim_sound(0, 1, SFX_SPARK)
    anim_obj(ANIM_OBJ_ROCK_SMASH, 128, 64, 0xdc)
    anim_obj(ANIM_OBJ_ROCK_SMASH, 128, 64, 0x90)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnim_Whirlpool(battleanim_s* anim) {
    ANIM_BEGIN
    anim_1gfx(ANIM_GFX_WIND)
    anim_bgeffect(ANIM_BG_WHIRLPOOL, 0x0, 0x0, 0x0)
    anim_sound(0, 1, SFX_SURF)
    anim_wait(16)
loop:
    anim_obj(ANIM_OBJ_GUST, 132, 72, 0x0)
    anim_wait(6)
    anim_loop(9, loop)
    anim_wait(64)
    anim_incbgeffect(ANIM_BG_WHIRLPOOL)
    anim_wait(1)
    anim_ret
    ANIM_END
}

static int BattleAnim_BeatUp(battleanim_s* anim) {
    ANIM_BEGIN
    anim_if_param_equal(0x0, current_mon)
    anim_sound(0, 0, SFX_BALL_POOF)
    anim_bgeffect(ANIM_BG_RETURN_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(16)
	anim_beatup
    anim_sound(0, 0, SFX_BALL_POOF)
    anim_bgeffect(ANIM_BG_ENTER_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(16)
current_mon:
    anim_1gfx(ANIM_GFX_HIT)
    anim_call(BattleAnim_TargetObj_1Row)
    anim_bgeffect(ANIM_BG_TACKLE, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_BEAT_UP)
    anim_obj(ANIM_OBJ_HIT_BIG_YFIX, 136, 48, 0x0)
    anim_wait(8)
    anim_call(BattleAnim_ShowMon_0)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Drain(battleanim_s* anim) {
    ANIM_BEGIN
    anim_obj(ANIM_OBJ_DRAIN, 132, 44, 0x0)
    anim_obj(ANIM_OBJ_DRAIN, 132, 44, 0x8)
    anim_obj(ANIM_OBJ_DRAIN, 132, 44, 0x10)
    anim_obj(ANIM_OBJ_DRAIN, 132, 44, 0x18)
    anim_obj(ANIM_OBJ_DRAIN, 132, 44, 0x20)
    anim_obj(ANIM_OBJ_DRAIN, 132, 44, 0x28)
    anim_obj(ANIM_OBJ_DRAIN, 132, 44, 0x30)
    anim_obj(ANIM_OBJ_DRAIN, 132, 44, 0x38)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_EyeBeams(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(6, 2, SFX_LEER)
    anim_obj(ANIM_OBJ_LEER, 72, 84, 0x0)
    anim_obj(ANIM_OBJ_LEER, 64, 80, 0x0)
    anim_obj(ANIM_OBJ_LEER, 88, 76, 0x0)
    anim_obj(ANIM_OBJ_LEER, 80, 72, 0x0)
    anim_obj(ANIM_OBJ_LEER, 104, 68, 0x0)
    anim_obj(ANIM_OBJ_LEER, 96, 64, 0x0)
    anim_obj(ANIM_OBJ_LEER, 120, 60, 0x0)
    anim_obj(ANIM_OBJ_LEER, 112, 56, 0x0)
    anim_obj(ANIM_OBJ_LEER_TIP, 130, 54, 0x0)
    anim_obj(ANIM_OBJ_LEER_TIP, 122, 50, 0x0)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_WarpAway(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 0, SFX_WARP_TO)
    anim_obj(ANIM_OBJ_WARP, 44, 108, 0x0)
    anim_obj(ANIM_OBJ_WARP, 44, 100, 0x0)
    anim_obj(ANIM_OBJ_WARP, 44, 92, 0x0)
    anim_obj(ANIM_OBJ_WARP, 44, 84, 0x0)
    anim_obj(ANIM_OBJ_WARP, 44, 76, 0x0)
    anim_obj(ANIM_OBJ_WARP, 44, 68, 0x0)
    anim_obj(ANIM_OBJ_WARP, 44, 60, 0x0)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Beam(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 0, SFX_HYPER_BEAM)
    anim_obj(ANIM_OBJ_BEAM, 64, 92, 0x0)
    anim_wait(4)
    anim_sound(0, 0, SFX_HYPER_BEAM)
    anim_obj(ANIM_OBJ_BEAM, 80, 84, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_HYPER_BEAM)
    anim_obj(ANIM_OBJ_BEAM, 96, 76, 0x0)
    anim_wait(4)
    anim_sound(0, 1, SFX_HYPER_BEAM)
    anim_obj(ANIM_OBJ_BEAM, 112, 68, 0x0)
    anim_obj(ANIM_OBJ_BEAM_TIP, 126, 62, 0x0)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Explosion1(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 0, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION1, 24, 64, 0x0)
    anim_wait(5)
    anim_sound(0, 0, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION1, 56, 104, 0x0)
    anim_wait(5)
    anim_sound(0, 0, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION1, 24, 104, 0x0)
    anim_wait(5)
    anim_sound(0, 0, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION1, 56, 64, 0x0)
    anim_wait(5)
    anim_sound(0, 0, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION1, 40, 84, 0x0)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Explosion2(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 1, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION1, 148, 32, 0x0)
    anim_wait(5)
    anim_sound(0, 1, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION1, 116, 72, 0x0)
    anim_wait(5)
    anim_sound(0, 1, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION1, 148, 72, 0x0)
    anim_wait(5)
    anim_sound(0, 1, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION1, 116, 32, 0x0)
    anim_wait(5)
    anim_sound(0, 1, SFX_EGG_BOMB)
    anim_obj(ANIM_OBJ_EXPLOSION1, 132, 52, 0x0)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Sound(battleanim_s* anim) {
    ANIM_BEGIN
    anim_obj(ANIM_OBJ_SOUND, 64, 76, 0x0)
    anim_obj(ANIM_OBJ_SOUND, 64, 88, 0x1)
    anim_obj(ANIM_OBJ_SOUND, 64, 100, 0x2)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Fire(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 1, SFX_EMBER)
loop:
    anim_obj(ANIM_OBJ_BURNED, 136, 56, 0x10)
    anim_obj(ANIM_OBJ_BURNED, 136, 56, 0x90)
    anim_wait(4)
    anim_loop(4, loop)
	anim_ret
    ANIM_END
}

static int BattleAnimSub_Ice(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 1, SFX_SHINE)
    anim_obj(ANIM_OBJ_ICE, 128, 42, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_SHINE)
    anim_obj(ANIM_OBJ_ICE, 144, 70, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_SHINE)
    anim_obj(ANIM_OBJ_ICE, 120, 56, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_SHINE)
    anim_obj(ANIM_OBJ_ICE, 152, 56, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_SHINE)
    anim_obj(ANIM_OBJ_ICE, 144, 42, 0x0)
    anim_wait(6)
    anim_sound(0, 1, SFX_SHINE)
    anim_obj(ANIM_OBJ_ICE, 128, 70, 0x0)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Sludge(battleanim_s* anim) {
    ANIM_BEGIN
loop:
    anim_sound(0, 1, SFX_TOXIC)
    anim_obj(ANIM_OBJ_SLUDGE, 132, 72, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_TOXIC)
    anim_obj(ANIM_OBJ_SLUDGE, 116, 72, 0x0)
    anim_wait(8)
    anim_sound(0, 1, SFX_TOXIC)
    anim_obj(ANIM_OBJ_SLUDGE, 148, 72, 0x0)
    anim_wait(8)
    anim_loop(5, loop)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Acid(battleanim_s* anim) {
    ANIM_BEGIN
loop:
    anim_sound(6, 2, SFX_BUBBLEBEAM)
    anim_obj(ANIM_OBJ_ACID, 64, 92, 0x10)
    anim_wait(5)
    anim_loop(8, loop)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Metallic(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 0, SFX_SHINE)
    anim_bgeffect(ANIM_BG_FADE_MON_TO_BLACK, 0x0, BG_EFFECT_USER, 0x40)
    anim_wait(8)
    anim_obj(ANIM_OBJ_HARDEN, 48, 84, 0x0)
    anim_wait(32)
    anim_obj(ANIM_OBJ_HARDEN, 48, 84, 0x0)
    anim_wait(64)
    anim_incbgeffect(ANIM_BG_FADE_MON_TO_BLACK)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_SandOrMud(battleanim_s* anim) {
    ANIM_BEGIN
loop:
    anim_sound(6, 2, SFX_MENU)
    anim_obj(ANIM_OBJ_SAND, 64, 92, 0x4)
    anim_wait(4)
    anim_loop(8, loop)
    anim_wait(32)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Glimmer(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 0, SFX_METRONOME)
    anim_obj(ANIM_OBJ_GLIMMER, 44, 64, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_GLIMMER, 24, 96, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_GLIMMER, 56, 104, 0x0)
    anim_wait(21)
    anim_ret
    ANIM_END
}

static int BattleAnimSub_Glimmer2(battleanim_s* anim) {
    ANIM_BEGIN
    anim_sound(0, 0, SFX_METRONOME)
loop:
    anim_obj(ANIM_OBJ_GLIMMER, 24, 64, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_GLIMMER, 56, 104, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_GLIMMER, 24, 104, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_GLIMMER, 56, 64, 0x0)
    anim_wait(5)
    anim_obj(ANIM_OBJ_GLIMMER, 40, 84, 0x0)
    anim_wait(5)
    anim_loop(2, loop)
    anim_wait(16)
    anim_ret
    ANIM_END
}

static int BattleAnim_TargetObj_1Row(battleanim_s* anim) {
    ANIM_BEGIN
    anim_battlergfx_1row // anim_battlergfx_2row
    anim_bgeffect(ANIM_BG_BATTLEROBJ_1ROW, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(6)
    anim_ret
    ANIM_END
}

static int BattleAnim_TargetObj_2Row(battleanim_s* anim) {
    ANIM_BEGIN
    anim_battlergfx_2row // anim_battlergfx_1row
    anim_bgeffect(ANIM_BG_BATTLEROBJ_2ROW, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(6)
    anim_ret
    ANIM_END
}

static int BattleAnim_ShowMon_0(battleanim_s* anim) {
    ANIM_BEGIN
    anim_wait(1)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_TARGET, 0x0)
    anim_wait(5)
    anim_incobj(1)
    anim_wait(1)
    anim_ret
    ANIM_END
}

static int BattleAnim_UserObj_1Row(battleanim_s* anim) {
    ANIM_BEGIN
    anim_battlergfx_1row // anim_battlergfx_2row
    anim_bgeffect(ANIM_BG_BATTLEROBJ_1ROW, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(6)
    anim_ret
    ANIM_END
}

static int BattleAnim_UserObj_2Row(battleanim_s* anim) {
    ANIM_BEGIN
    anim_battlergfx_2row // anim_battlergfx_1row
    anim_bgeffect(ANIM_BG_BATTLEROBJ_2ROW, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_ret
    ANIM_END
}

static int BattleAnim_ShowMon_1(battleanim_s* anim) {
    ANIM_BEGIN
    anim_wait(1)
    anim_bgeffect(ANIM_BG_SHOW_MON, 0x0, BG_EFFECT_USER, 0x0)
    anim_wait(4)
    anim_incobj(1)
    anim_wait(1)
    anim_ret
    ANIM_END
}

const battleanim_func BattleAnimations[] = {
// entries correspond to constants/move_constants.asm
// table_width 2, BattleAnimations
    [0x00]          = BattleAnim_0,
    [POUND]         = BattleAnim_Pound,
    [KARATE_CHOP]   = BattleAnim_KarateChop,
    [DOUBLESLAP]    = BattleAnim_Doubleslap,
    [COMET_PUNCH]   = BattleAnim_CometPunch,
    [MEGA_PUNCH]    = BattleAnim_MegaPunch,
    [PAY_DAY]       = BattleAnim_PayDay,
    [FIRE_PUNCH]    = BattleAnim_FirePunch,
    [ICE_PUNCH]     = BattleAnim_IcePunch,
    [THUNDERPUNCH]  = BattleAnim_Thunderpunch,
    [SCRATCH]       = BattleAnim_Scratch,
    [VICEGRIP]      = BattleAnim_Vicegrip,
    [GUILLOTINE]    = BattleAnim_Guillotine,
    [RAZOR_WIND]    = BattleAnim_RazorWind,
    [SWORDS_DANCE]  = BattleAnim_SwordsDance,
    [CUT]           = BattleAnim_Cut,
    [GUST]          = BattleAnim_Gust,
    [WING_ATTACK]   = BattleAnim_WingAttack,
    [WHIRLWIND]     = BattleAnim_Whirlwind,
    [FLY]           = BattleAnim_Fly,
    [BIND]          = BattleAnim_Bind,
    [SLAM]          = BattleAnim_Slam,
    [VINE_WHIP]     = BattleAnim_VineWhip,
    [STOMP]         = BattleAnim_Stomp,
    [DOUBLE_KICK]   = BattleAnim_DoubleKick,
    [MEGA_KICK]     = BattleAnim_MegaKick,
    [JUMP_KICK]     = BattleAnim_JumpKick,
    [ROLLING_KICK]  = BattleAnim_RollingKick,
    [SAND_ATTACK]   = BattleAnim_SandAttack,
    [HEADBUTT]      = BattleAnim_Headbutt,
    [HORN_ATTACK]   = BattleAnim_HornAttack,
    [FURY_ATTACK]   = BattleAnim_FuryAttack,
    [HORN_DRILL]    = BattleAnim_HornDrill,
    [TACKLE]        = BattleAnim_Tackle,
    [BODY_SLAM]     = BattleAnim_BodySlam,
    [WRAP]          = BattleAnim_Wrap,
    [TAKE_DOWN]     = BattleAnim_TakeDown,
    [THRASH]        = BattleAnim_Thrash,
    [DOUBLE_EDGE]   = BattleAnim_DoubleEdge,
    [TAIL_WHIP]     = BattleAnim_TailWhip,
    [POISON_STING]  = BattleAnim_PoisonSting,
    [TWINEEDLE]     = BattleAnim_Twineedle,
    [PIN_MISSILE]   = BattleAnim_PinMissile,
    [LEER]          = BattleAnim_Leer,
    [BITE]          = BattleAnim_Bite,
    [GROWL]         = BattleAnim_Growl,
    [ROAR]          = BattleAnim_Roar,
    [SING]          = BattleAnim_Sing,
    [SUPERSONIC]    = BattleAnim_Supersonic,
    [SONICBOOM]     = BattleAnim_Sonicboom,
    [DISABLE]       = BattleAnim_Disable,
    [ACID]          = BattleAnim_Acid,
    [EMBER]         = BattleAnim_Ember,
    [FLAMETHROWER]  = BattleAnim_Flamethrower,
    [MIST]          = BattleAnim_Mist,
    [WATER_GUN]     = BattleAnim_WaterGun,
    [HYDRO_PUMP]    = BattleAnim_HydroPump,
    [SURF]          = BattleAnim_Surf,
    [ICE_BEAM]      = BattleAnim_IceBeam,
    [BLIZZARD]      = BattleAnim_Blizzard,
    [PSYBEAM]       = BattleAnim_Psybeam,
    [BUBBLEBEAM]    = BattleAnim_Bubblebeam,
    [AURORA_BEAM]   = BattleAnim_AuroraBeam,
    [HYPER_BEAM]    = BattleAnim_HyperBeam,
    [PECK]          = BattleAnim_Peck,
    [DRILL_PECK]    = BattleAnim_DrillPeck,
    [SUBMISSION]    = BattleAnim_Submission,
    [LOW_KICK]      = BattleAnim_LowKick,
    [COUNTER]       = BattleAnim_Counter,
    [SEISMIC_TOSS]  = BattleAnim_SeismicToss,
    [STRENGTH]      = BattleAnim_Strength,
    [ABSORB]        = BattleAnim_Absorb,
    [MEGA_DRAIN]    = BattleAnim_MegaDrain,
    [LEECH_SEED]    = BattleAnim_LeechSeed,
    [GROWTH]        = BattleAnim_Growth,
    [RAZOR_LEAF]    = BattleAnim_RazorLeaf,
    [SOLARBEAM]     = BattleAnim_Solarbeam,
    [POISONPOWDER]  = BattleAnim_Poisonpowder,
    [STUN_SPORE]    = BattleAnim_StunSpore,
    [SLEEP_POWDER]  = BattleAnim_SleepPowder,
    [PETAL_DANCE]   = BattleAnim_PetalDance,
    [STRING_SHOT]   = BattleAnim_StringShot,
    [DRAGON_RAGE]   = BattleAnim_DragonRage,
    [FIRE_SPIN]     = BattleAnim_FireSpin,
    [THUNDERSHOCK]  = BattleAnim_Thundershock,
    [THUNDERBOLT]   = BattleAnim_Thunderbolt,
    [THUNDER_WAVE]  = BattleAnim_ThunderWave,
    [THUNDER]       = BattleAnim_Thunder,
    [ROCK_THROW]    = BattleAnim_RockThrow,
    [EARTHQUAKE]    = BattleAnim_Earthquake,
    [FISSURE]       = BattleAnim_Fissure,
    [DIG]           = BattleAnim_Dig,
    [TOXIC]         = BattleAnim_Toxic,
    [CONFUSION]     = BattleAnim_Confusion,
    [PSYCHIC_M]     = BattleAnim_PsychicM,
    [HYPNOSIS]      = BattleAnim_Hypnosis,
    [MEDITATE]      = BattleAnim_Meditate,
    [AGILITY]       = BattleAnim_Agility,
    [QUICK_ATTACK]  = BattleAnim_QuickAttack,
    [RAGE]          = BattleAnim_Rage,
    [TELEPORT]      = BattleAnim_Teleport,
    [NIGHT_SHADE]   = BattleAnim_NightShade,
    [MIMIC]         = BattleAnim_Mimic,
    [SCREECH]       = BattleAnim_Screech,
    [DOUBLE_TEAM]   = BattleAnim_DoubleTeam,
    [RECOVER]       = BattleAnim_Recover,
    [HARDEN]        = BattleAnim_Harden,
    [MINIMIZE]      = BattleAnim_Minimize,
    [SMOKESCREEN]   = BattleAnim_Smokescreen,
    [CONFUSE_RAY]   = BattleAnim_ConfuseRay,
    [WITHDRAW]      = BattleAnim_Withdraw,
    [DEFENSE_CURL]  = BattleAnim_DefenseCurl,
    [BARRIER]       = BattleAnim_Barrier,
    [LIGHT_SCREEN]  = BattleAnim_LightScreen,
    [HAZE]          = BattleAnim_Haze,
    [REFLECT]       = BattleAnim_Reflect,
    [FOCUS_ENERGY]  = BattleAnim_FocusEnergy,
    [BIDE]          = BattleAnim_Bide,
    [METRONOME]     = BattleAnim_Metronome,
    [MIRROR_MOVE]   = BattleAnim_MirrorMove,
    [SELFDESTRUCT]  = BattleAnim_Selfdestruct,
    [EGG_BOMB]      = BattleAnim_EggBomb,
    [LICK]          = BattleAnim_Lick,
    [SMOG]          = BattleAnim_Smog,
    [SLUDGE]        = BattleAnim_Sludge,
    [BONE_CLUB]     = BattleAnim_BoneClub,
    [FIRE_BLAST]    = BattleAnim_FireBlast,
    [WATERFALL]     = BattleAnim_Waterfall,
    [CLAMP]         = BattleAnim_Clamp,
    [SWIFT]         = BattleAnim_Swift,
    [SKULL_BASH]    = BattleAnim_SkullBash,
    [SPIKE_CANNON]  = BattleAnim_SpikeCannon,
    [CONSTRICT]     = BattleAnim_Constrict,
    [AMNESIA]       = BattleAnim_Amnesia,
    [KINESIS]       = BattleAnim_Kinesis,
    [SOFTBOILED]    = BattleAnim_Softboiled,
    [HI_JUMP_KICK]  = BattleAnim_HiJumpKick,
    [GLARE]         = BattleAnim_Glare,
    [DREAM_EATER]   = BattleAnim_DreamEater,
    [POISON_GAS]    = BattleAnim_PoisonGas,
    [BARRAGE]       = BattleAnim_Barrage,
    [LEECH_LIFE]    = BattleAnim_LeechLife,
    [LOVELY_KISS]   = BattleAnim_LovelyKiss,
    [SKY_ATTACK]    = BattleAnim_SkyAttack,
    [TRANSFORM]     = BattleAnim_Transform,
    [BUBBLE]        = BattleAnim_Bubble,
    [DIZZY_PUNCH]   = BattleAnim_DizzyPunch,
    [SPORE]         = BattleAnim_Spore,
    [FLASH]         = BattleAnim_Flash,
    [PSYWAVE]       = BattleAnim_Psywave,
    [SPLASH]        = BattleAnim_Splash,
    [ACID_ARMOR]    = BattleAnim_AcidArmor,
    [CRABHAMMER]    = BattleAnim_Crabhammer,
    [EXPLOSION]     = BattleAnim_Explosion,
    [FURY_SWIPES]   = BattleAnim_FurySwipes,
    [BONEMERANG]    = BattleAnim_Bonemerang,
    [REST]          = BattleAnim_Rest,
    [ROCK_SLIDE]    = BattleAnim_RockSlide,
    [HYPER_FANG]    = BattleAnim_HyperFang,
    [SHARPEN]       = BattleAnim_Sharpen,
    [CONVERSION]    = BattleAnim_Conversion,
    [TRI_ATTACK]    = BattleAnim_TriAttack,
    [SUPER_FANG]    = BattleAnim_SuperFang,
    [SLASH]         = BattleAnim_Slash,
    [SUBSTITUTE]    = BattleAnim_Substitute,
    [STRUGGLE]      = BattleAnim_Struggle,
    [SKETCH]        = BattleAnim_Sketch,
    [TRIPLE_KICK]   = BattleAnim_TripleKick,
    [THIEF]         = BattleAnim_Thief,
    [SPIDER_WEB]    = BattleAnim_SpiderWeb,
    [MIND_READER]   = BattleAnim_MindReader,
    [NIGHTMARE]     = BattleAnim_Nightmare,
    [FLAME_WHEEL]   = BattleAnim_FlameWheel,
    [SNORE]         = BattleAnim_Snore,
    [CURSE]         = BattleAnim_Curse,
    [FLAIL]         = BattleAnim_Flail,
    [CONVERSION2]   = BattleAnim_Conversion2,
    [AEROBLAST]     = BattleAnim_Aeroblast,
    [COTTON_SPORE]  = BattleAnim_CottonSpore,
    [REVERSAL]      = BattleAnim_Reversal,
    [SPITE]         = BattleAnim_Spite,
    [POWDER_SNOW]   = BattleAnim_PowderSnow,
    [PROTECT]       = BattleAnim_Protect,
    [MACH_PUNCH]    = BattleAnim_MachPunch,
    [SCARY_FACE]    = BattleAnim_ScaryFace,
    [FAINT_ATTACK]  = BattleAnim_FaintAttack,
    [SWEET_KISS]    = BattleAnim_SweetKiss,
    [BELLY_DRUM]    = BattleAnim_BellyDrum,
    [SLUDGE_BOMB]   = BattleAnim_SludgeBomb,
    [MUD_SLAP]      = BattleAnim_MudSlap,
    [OCTAZOOKA]     = BattleAnim_Octazooka,
    [SPIKES]        = BattleAnim_Spikes,
    [ZAP_CANNON]    = BattleAnim_ZapCannon,
    [FORESIGHT]     = BattleAnim_Foresight,
    [DESTINY_BOND]  = BattleAnim_DestinyBond,
    [PERISH_SONG]   = BattleAnim_PerishSong,
    [ICY_WIND]      = BattleAnim_IcyWind,
    [DETECT]        = BattleAnim_Detect,
    [BONE_RUSH]     = BattleAnim_BoneRush,
    [LOCK_ON]       = BattleAnim_LockOn,
    [OUTRAGE]       = BattleAnim_Outrage,
    [SANDSTORM]     = BattleAnim_Sandstorm,
    [GIGA_DRAIN]    = BattleAnim_GigaDrain,
    [ENDURE]        = BattleAnim_Endure,
    [CHARM]         = BattleAnim_Charm,
    [ROLLOUT]       = BattleAnim_Rollout,
    [FALSE_SWIPE]   = BattleAnim_FalseSwipe,
    [SWAGGER]       = BattleAnim_Swagger,
    [MILK_DRINK]    = BattleAnim_MilkDrink,
    [SPARK]         = BattleAnim_Spark,
    [FURY_CUTTER]   = BattleAnim_FuryCutter,
    [STEEL_WING]    = BattleAnim_SteelWing,
    [MEAN_LOOK]     = BattleAnim_MeanLook,
    [ATTRACT]       = BattleAnim_Attract,
    [SLEEP_TALK]    = BattleAnim_SleepTalk,
    [HEAL_BELL]     = BattleAnim_HealBell,
    [RETURN]        = BattleAnim_Return,
    [PRESENT]       = BattleAnim_Present,
    [FRUSTRATION]   = BattleAnim_Frustration,
    [SAFEGUARD]     = BattleAnim_Safeguard,
    [PAIN_SPLIT]    = BattleAnim_PainSplit,
    [SACRED_FIRE]   = BattleAnim_SacredFire,
    [MAGNITUDE]     = BattleAnim_Magnitude,
    [DYNAMICPUNCH]  = BattleAnim_Dynamicpunch,
    [MEGAHORN]      = BattleAnim_Megahorn,
    [DRAGONBREATH]  = BattleAnim_Dragonbreath,
    [BATON_PASS]    = BattleAnim_BatonPass,
    [ENCORE]        = BattleAnim_Encore,
    [PURSUIT]       = BattleAnim_Pursuit,
    [RAPID_SPIN]    = BattleAnim_RapidSpin,
    [SWEET_SCENT]   = BattleAnim_SweetScent,
    [IRON_TAIL]     = BattleAnim_IronTail,
    [METAL_CLAW]    = BattleAnim_MetalClaw,
    [VITAL_THROW]   = BattleAnim_VitalThrow,
    [MORNING_SUN]   = BattleAnim_MorningSun,
    [SYNTHESIS]     = BattleAnim_Synthesis,
    [MOONLIGHT]     = BattleAnim_Moonlight,
    [HIDDEN_POWER]  = BattleAnim_HiddenPower,
    [CROSS_CHOP]    = BattleAnim_CrossChop,
    [TWISTER]       = BattleAnim_Twister,
    [RAIN_DANCE]    = BattleAnim_RainDance,
    [SUNNY_DAY]     = BattleAnim_SunnyDay,
    [CRUNCH]        = BattleAnim_Crunch,
    [MIRROR_COAT]   = BattleAnim_MirrorCoat,
    [PSYCH_UP]      = BattleAnim_PsychUp,
    [EXTREMESPEED]  = BattleAnim_Extremespeed,
    [ANCIENTPOWER]  = BattleAnim_Ancientpower,
    [SHADOW_BALL]   = BattleAnim_ShadowBall,
    [FUTURE_SIGHT]  = BattleAnim_FutureSight,
    [ROCK_SMASH]    = BattleAnim_RockSmash,
    [WHIRLPOOL]     = BattleAnim_Whirlpool,
    [BEAT_UP]       = BattleAnim_BeatUp,
    // assert_table_length NUM_ATTACKS + 1
    [0xfc]                  = BattleAnim_252,
    [0xfd]                  = BattleAnim_253,
    [0xfe]                  = BattleAnim_254,
    [ANIM_SWEET_SCENT_2]    = BattleAnim_SweetScent2,
    // assert_table_length 0x100
// 0x100
    [ANIM_THROW_POKE_BALL]  = BattleAnim_ThrowPokeBall,
    [ANIM_SEND_OUT_MON]     = BattleAnim_SendOutMon,
    [ANIM_RETURN_MON]       = BattleAnim_ReturnMon,
    [ANIM_CONFUSED]         = BattleAnim_Confused,
    [ANIM_SLP]              = BattleAnim_Slp,
    [ANIM_BRN]              = BattleAnim_Brn,
    [ANIM_PSN]              = BattleAnim_Psn,
    [ANIM_SAP]              = BattleAnim_Sap,
    [ANIM_FRZ]              = BattleAnim_Frz,
    [ANIM_PAR]              = BattleAnim_Par,
    [ANIM_IN_LOVE]          = BattleAnim_InLove,
    [ANIM_IN_SANDSTORM]     = BattleAnim_InSandstorm,
    [ANIM_IN_NIGHTMARE]     = BattleAnim_InNightmare,
    [ANIM_IN_WHIRLPOOL]     = BattleAnim_InWhirlpool,
    [ANIM_MISS]             = BattleAnim_Miss,
    [ANIM_ENEMY_DAMAGE]     = BattleAnim_EnemyDamage,
    [ANIM_ENEMY_STAT_DOWN]  = BattleAnim_EnemyStatDown,
    [ANIM_PLAYER_STAT_DOWN] = BattleAnim_PlayerStatDown,
    [ANIM_PLAYER_DAMAGE]    = BattleAnim_PlayerDamage,
    [ANIM_WOBBLE]           = BattleAnim_Wobble,
    [ANIM_SHAKE]            = BattleAnim_Shake,
    [ANIM_HIT_CONFUSION]    = BattleAnim_HitConfusion,
};
static_assert(lengthof(BattleAnimations) == NUM_BATTLE_ANIMS + 1, "");
