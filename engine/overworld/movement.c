#include "../../constants.h"
#include "movement.h"
#include "../../home/map_objects.h"
#include "map_objects.h"

// void MovementPointers(void){
//  entries correspond to movement_* constants (see macros/scripts/movement.asm)
    //table_width ['2', 'MovementPointers']
    //dw ['Movement_turn_head_down'];  // 00
    //dw ['Movement_turn_head_up'];  // 01
    //dw ['Movement_turn_head_left'];  // 02
    //dw ['Movement_turn_head_right'];  // 03
    //dw ['Movement_turn_step_down'];  // 04
    //dw ['Movement_turn_step_up'];  // 05
    //dw ['Movement_turn_step_left'];  // 06
    //dw ['Movement_turn_step_right'];  // 07
    //dw ['Movement_slow_step_down'];  // 08
    //dw ['Movement_slow_step_up'];  // 09
    //dw ['Movement_slow_step_left'];  // 0a
    //dw ['Movement_slow_step_right'];  // 0b
    //dw ['Movement_step_down'];  // 0c
    //dw ['Movement_step_up'];  // 0d
    //dw ['Movement_step_left'];  // 0e
    //dw ['Movement_step_right'];  // 0f
    //dw ['Movement_big_step_down'];  // 10
    //dw ['Movement_big_step_up'];  // 11
    //dw ['Movement_big_step_left'];  // 12
    //dw ['Movement_big_step_right'];  // 13
    //dw ['Movement_slow_slide_step_down'];  // 14
    //dw ['Movement_slow_slide_step_up'];  // 15
    //dw ['Movement_slow_slide_step_left'];  // 16
    //dw ['Movement_slow_slide_step_right'];  // 17
    //dw ['Movement_slide_step_down'];  // 18
    //dw ['Movement_slide_step_up'];  // 19
    //dw ['Movement_slide_step_left'];  // 1a
    //dw ['Movement_slide_step_right'];  // 1b
    //dw ['Movement_fast_slide_step_down'];  // 1c
    //dw ['Movement_fast_slide_step_up'];  // 1d
    //dw ['Movement_fast_slide_step_left'];  // 1e
    //dw ['Movement_fast_slide_step_right'];  // 1f
    //dw ['Movement_turn_away_down'];  // 20
    //dw ['Movement_turn_away_up'];  // 21
    //dw ['Movement_turn_away_left'];  // 22
    //dw ['Movement_turn_away_right'];  // 23
    //dw ['Movement_turn_in_down'];  // 24
    //dw ['Movement_turn_in_up'];  // 25
    //dw ['Movement_turn_in_left'];  // 26
    //dw ['Movement_turn_in_right'];  // 27
    //dw ['Movement_turn_waterfall_down'];  // 28
    //dw ['Movement_turn_waterfall_up'];  // 29
    //dw ['Movement_turn_waterfall_left'];  // 2a
    //dw ['Movement_turn_waterfall_right'];  // 2b
    //dw ['Movement_slow_jump_step_down'];  // 2c
    //dw ['Movement_slow_jump_step_up'];  // 2d
    //dw ['Movement_slow_jump_step_left'];  // 2e
    //dw ['Movement_slow_jump_step_right'];  // 2f
    //dw ['Movement_jump_step_down'];  // 30
    //dw ['Movement_jump_step_up'];  // 31
    //dw ['Movement_jump_step_left'];  // 32
    //dw ['Movement_jump_step_right'];  // 33
    //dw ['Movement_fast_jump_step_down'];  // 34
    //dw ['Movement_fast_jump_step_up'];  // 35
    //dw ['Movement_fast_jump_step_left'];  // 36
    //dw ['Movement_fast_jump_step_right'];  // 37
    //dw ['Movement_remove_sliding'];  // 38
    //dw ['Movement_set_sliding'];  // 39
    //dw ['Movement_remove_fixed_facing'];  // 3a
    //dw ['Movement_fix_facing'];  // 3b
    //dw ['Movement_show_object'];  // 3c
    //dw ['Movement_hide_object'];  // 3d
    //dw ['Movement_step_sleep_1'];  // 3e
    //dw ['Movement_step_sleep_2'];  // 3f
    //dw ['Movement_step_sleep_3'];  // 40
    //dw ['Movement_step_sleep_4'];  // 41
    //dw ['Movement_step_sleep_5'];  // 42
    //dw ['Movement_step_sleep_6'];  // 43
    //dw ['Movement_step_sleep_7'];  // 44
    //dw ['Movement_step_sleep_8'];  // 45
    //dw ['Movement_step_sleep'];  // 46
    //dw ['Movement_step_end'];  // 47
    //dw ['Movement_48'];  // 48
    //dw ['Movement_remove_object'];  // 49
    //dw ['Movement_step_loop'];  // 4a
    //dw ['Movement_4b'];  // 4b
    //dw ['Movement_teleport_from'];  // 4c
    //dw ['Movement_teleport_to'];  // 4d
    //dw ['Movement_skyfall'];  // 4e
    //dw ['Movement_step_dig'];  // 4f
    //dw ['Movement_step_bump'];  // 50
    //dw ['Movement_fish_got_bite'];  // 51
    //dw ['Movement_fish_cast_rod'];  // 52
    //dw ['Movement_hide_emote'];  // 53
    //dw ['Movement_show_emote'];  // 54
    //dw ['Movement_step_shake'];  // 55
    //dw ['Movement_tree_shake'];  // 56
    //dw ['Movement_rock_smash'];  // 57
    //dw ['Movement_return_dig'];  // 58
    //dw ['Movement_skyfall_top'];  // 59
    //assert_table_length ['NUM_MOVEMENT_CMDS']
// }

void (*const MovementPointers[])(struct Object* bc) = {
    [turn_head(DOWN)]               = Movement_turn_head_down,
    [turn_head(UP)]                 = Movement_turn_head_up,
    [turn_head(LEFT)]               = Movement_turn_head_left,
    [turn_head(RIGHT)]              = Movement_turn_head_right,
    [turn_step(DOWN)]               = Movement_turn_step_down,
    [turn_step(UP)]                 = Movement_turn_step_up,
    [turn_step(LEFT)]               = Movement_turn_step_left,
    [turn_step(RIGHT)]              = Movement_turn_step_right,
    [slow_step(DOWN)]               = Movement_slow_step_down,
    [slow_step(UP)]                 = Movement_slow_step_up,
    [slow_step(LEFT)]               = Movement_slow_step_left,
    [slow_step(RIGHT)]              = Movement_slow_step_right,
    [step(DOWN)]                    = Movement_step_down,
    [step(UP)]                      = Movement_step_up,
    [step(LEFT)]                    = Movement_step_left,
    [step(RIGHT)]                   = Movement_step_right,
    [big_step(DOWN)]                = Movement_big_step_down,
    [big_step(UP)]                  = Movement_big_step_up,
    [big_step(LEFT)]                = Movement_big_step_left,
    [big_step(RIGHT)]               = Movement_big_step_right,
    [slow_slide_step(DOWN)]         = Movement_slow_slide_step_down,
    [slow_slide_step(UP)]           = Movement_slow_slide_step_up,
    [slow_slide_step(LEFT)]         = Movement_slow_slide_step_left,
    [slow_slide_step(RIGHT)]        = Movement_slow_slide_step_right,
    [slide_step(DOWN)]              = Movement_slide_step_down,
    [slide_step(UP)]                = Movement_slide_step_up,
    [slide_step(LEFT)]              = Movement_slide_step_left,
    [slide_step(RIGHT)]             = Movement_slide_step_right,
    [fast_slide_step(DOWN)]         = Movement_fast_slide_step_down,
    [fast_slide_step(UP)]           = Movement_fast_slide_step_up,
    [fast_slide_step(LEFT)]         = Movement_fast_slide_step_left,
    [fast_slide_step(RIGHT)]        = Movement_fast_slide_step_right,
    [turn_away(DOWN)]               = Movement_turn_away_down,
    [turn_away(UP)]                 = Movement_turn_away_up,
    [turn_away(LEFT)]               = Movement_turn_away_left,
    [turn_away(RIGHT)]              = Movement_turn_away_right,
    [turn_in(DOWN)]                 = Movement_turn_in_down,
    [turn_in(UP)]                   = Movement_turn_in_up,
    [turn_in(LEFT)]                 = Movement_turn_in_left,
    [turn_in(RIGHT)]                = Movement_turn_in_right,
    [turn_waterfall(DOWN)]          = Movement_turn_waterfall_down,
    [turn_waterfall(UP)]            = Movement_turn_waterfall_up,
    [turn_waterfall(LEFT)]          = Movement_turn_waterfall_left,
    [turn_waterfall(RIGHT)]         = Movement_turn_waterfall_right,
    [slow_jump_step(DOWN)]          = Movement_slow_jump_step_down,
    [slow_jump_step(UP)]            = Movement_slow_jump_step_up,
    [slow_jump_step(LEFT)]          = Movement_slow_jump_step_left,
    [slow_jump_step(RIGHT)]         = Movement_slow_jump_step_right,
    [jump_step(DOWN)]               = Movement_jump_step_down,
    [jump_step(UP)]                 = Movement_jump_step_up,
    [jump_step(LEFT)]               = Movement_jump_step_left,
    [jump_step(RIGHT)]              = Movement_jump_step_right,
    [fast_jump_step(DOWN)]          = Movement_fast_jump_step_down,
    [fast_jump_step(UP)]            = Movement_fast_jump_step_up,
    [fast_jump_step(LEFT)]          = Movement_fast_jump_step_left,
    [fast_jump_step(RIGHT)]         = Movement_fast_jump_step_right,
    [movement_remove_sliding]       = Movement_remove_sliding,
    [movement_set_sliding]          = Movement_set_sliding,
    [movement_remove_fixed_facing]  = Movement_remove_fixed_facing,
    [movement_fix_facing]           = Movement_fix_facing,
    [movement_show_object]          = Movement_show_object,
    [movement_hide_object]          = Movement_hide_object,
    [step_sleep(1)]                 = Movement_step_sleep_1,
    [step_sleep(2)]                 = Movement_step_sleep_2,
    [step_sleep(3)]                 = Movement_step_sleep_3,
    [step_sleep(4)]                 = Movement_step_sleep_4,
    [step_sleep(5)]                 = Movement_step_sleep_5,
    [step_sleep(6)]                 = Movement_step_sleep_6,
    [step_sleep(7)]                 = Movement_step_sleep_7,
    [step_sleep(8)]                 = Movement_step_sleep_8,
    [movement_step_sleep + 8]       = Movement_step_sleep,
    [movement_step_end]             = Movement_step_end,
    [movement_step_48]              = Movement_48,
    [movement_remove_object]        = Movement_remove_object,
    [movement_step_loop]            = Movement_step_loop,
    [movement_step_4b]              = Movement_4b,
    [movement_teleport_from]        = Movement_teleport_from,
    [movement_teleport_to]          = Movement_teleport_to,
    [movement_skyfall]              = Movement_skyfall,
    [movement_step_dig]             = Movement_step_dig,
    [movement_step_bump]            = Movement_step_bump,
    [movement_fish_got_bite]        = Movement_fish_got_bite,
    [movement_fish_cast_rod]        = Movement_fish_cast_rod,
    [movement_hide_emote]           = Movement_hide_emote,
    [movement_show_emote]           = Movement_show_emote,
    [movement_step_shake]           = Movement_step_shake,
    [movement_tree_shake]           = Movement_tree_shake,
    [movement_rock_smash]           = Movement_rock_smash,
    [movement_return_dig]           = Movement_return_dig,
    [movement_skyfall_top]          = Movement_skyfall_top,
};

static_assert(lengthof(MovementPointers) == NUM_MOVEMENT_CMDS, "");

void Movement_teleport_from(struct Object* bc){
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_TELEPORT_FROM);
    // RET;
    bc->stepType = STEP_TYPE_TELEPORT_FROM;
}

void Movement_teleport_to(struct Object* bc){
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_TELEPORT_TO);
    // RET;
    bc->stepType = STEP_TYPE_TELEPORT_TO;
}

void Movement_skyfall(struct Object* bc){
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_SKYFALL);
    // RET;
    bc->stepType = STEP_TYPE_SKYFALL;
}

void Movement_skyfall_top(struct Object* bc){
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_SKYFALL_TOP);
    // RET;
    bc->stepType = STEP_TYPE_SKYFALL_TOP;
}

void Movement_step_dig(struct Object* bc){
    // CALL(aGetSpriteDirection);
    uint8_t a = GetSpriteDirection_Conv(bc);
    // RLCA;
    a = (a << 1) | (a >> 7);
    // RLCA;
    a = (a << 1) | (a >> 7);
    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepFrame = a;
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_SPIN);
    bc->action = OBJECT_ACTION_SPIN;
    // CALL(aJumpMovementPointer);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = JumpMovementPointer_Conv();
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_SLEEP);
    bc->stepType = STEP_TYPE_SLEEP;
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // RET;
}

void Movement_return_dig(struct Object* bc){
    // CALL(aGetSpriteDirection);
    uint8_t a = GetSpriteDirection_Conv(bc);
    // RLCA;
    a = (a << 1) | (a >> 7);
    // RLCA;
    a = (a << 1) | (a >> 7);
    // LD_HL(OBJECT_STEP_FRAME);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepFrame = a;
    // CALL(aJumpMovementPointer);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = JumpMovementPointer_Conv();
    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_RETURN_DIG);
    bc->stepType = STEP_TYPE_RETURN_DIG;
    // RET;
}

void Movement_fish_got_bite(struct Object* bc){
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_FISHING);
    bc->action = OBJECT_ACTION_FISHING;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_GOT_BITE);
    bc->stepType = STEP_TYPE_GOT_BITE;
    // RET;
}

void Movement_rock_smash(struct Object* bc){
    // CALL(aJumpMovementPointer);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = JumpMovementPointer_Conv();
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STAND);
    bc->action = OBJECT_ACTION_STAND;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_ROCK_SMASH);
    bc->stepType = STEP_TYPE_ROCK_SMASH;
    // RET;
}

void Movement_fish_cast_rod(struct Object* bc){
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_FISHING);
    bc->action = OBJECT_ACTION_FISHING;
    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_FROM_MOVEMENT);
    bc->stepType = STEP_TYPE_FROM_MOVEMENT;
    // RET;
}

void Movement_step_loop(struct Object* bc){
    // LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    // ADD_HL_BC;
    // LD_hl(0x0);
    bc->movementByteIndex = 0x0;
    // JP(mContinueReadingMovement);
    return ContinueReadingMovement();
}

void Movement_step_end(struct Object* bc){
    // CALL(aRestoreDefaultMovement);
    // LD_HL(OBJECT_MOVEMENTTYPE);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->movementType = RestoreDefaultMovement_Conv(bc);

    // LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    // ADD_HL_BC;
    // LD_hl(0x0);
    bc->movementByteIndex = 0x0;

    // LD_HL(wVramState);
    // RES_hl(7);
    bit_reset(wram->wVramState, 7);

    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_FROM_MOVEMENT);
    bc->stepType = STEP_TYPE_FROM_MOVEMENT;
    // RET;
}

void Movement_48(struct Object* bc){
    // CALL(aRestoreDefaultMovement);
    // LD_HL(OBJECT_MOVEMENTTYPE);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->movementType = RestoreDefaultMovement_Conv(bc);

    // LD_HL(OBJECT_MOVEMENT_BYTE_INDEX);
    // ADD_HL_BC;
    // LD_hl(0x0);
    bc->movementByteIndex = 0x0;

    // CALL(aJumpMovementPointer);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = JumpMovementPointer_Conv();

    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_SLEEP);
    bc->stepType = STEP_TYPE_SLEEP;

    // LD_HL(wVramState);
    // RES_hl(7);
    bit_reset(wram->wVramState, 7);
    // RET;
}

void Movement_remove_object(struct Object* bc){
    // CALL(aDeleteMapObject);
    DeleteMapObject_Conv(bc);
    // LD_HL(wObjectFollow_Leader);
    // LDH_A_addr(hMapObjectIndex);
    // CP_A_hl;
    // IF_NZ goto not_leading;
    if(hram->hMapObjectIndex != wram->wObjectFollow_Leader) {
        // LD_hl(-1);
        wram->wObjectFollow_Leader = 0xff;
    }
// not_leading:
    // LD_HL(wVramState);
    // RES_hl(7);
    bit_reset(wram->wVramState, 7);
    // RET;
}

void Movement_4b(struct Object* bc){
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STAND);
    bc->action = OBJECT_ACTION_STAND;

    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_STANDING);
    bc->stepType = STEP_TYPE_STANDING;

    // LD_HL(wVramState);
    // RES_hl(7);
    bit_reset(wram->wVramState, 7);
    // RET;
}

void Movement_step_sleep_1(struct Object* bc){
    // LD_A(1);
    // JR(mMovement_step_sleep_common);
    return Movement_step_sleep_common(bc, 1);
}

void Movement_step_sleep_2(struct Object* bc){
    // LD_A(2);
    // JR(mMovement_step_sleep_common);
    return Movement_step_sleep_common(bc, 2);
}

void Movement_step_sleep_3(struct Object* bc){
    // LD_A(3);
    // JR(mMovement_step_sleep_common);
    return Movement_step_sleep_common(bc, 3);
}

void Movement_step_sleep_4(struct Object* bc){
    // LD_A(4);
    // JR(mMovement_step_sleep_common);
    return Movement_step_sleep_common(bc, 4);
}

void Movement_step_sleep_5(struct Object* bc){
    // LD_A(5);
    // JR(mMovement_step_sleep_common);
    return Movement_step_sleep_common(bc, 5);
}

void Movement_step_sleep_6(struct Object* bc){
    // LD_A(6);
    // JR(mMovement_step_sleep_common);
    return Movement_step_sleep_common(bc, 6);
}

void Movement_step_sleep_7(struct Object* bc){
    // LD_A(7);
    // JR(mMovement_step_sleep_common);
    return Movement_step_sleep_common(bc, 7);
}

void Movement_step_sleep_8(struct Object* bc){
    // LD_A(8);
    // JR(mMovement_step_sleep_common);
    return Movement_step_sleep_common(bc, 8);
}

void Movement_step_sleep(struct Object* bc){
//  parameters:
//     duration (DecimalParam)

    CALL(aJumpMovementPointer);
    // JR(mMovement_step_sleep_common);
    return Movement_step_sleep_common(bc, 0);
}

void Movement_step_sleep_common(struct Object* bc, uint8_t a){
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = a;

    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_SLEEP);
    bc->stepType = STEP_TYPE_SLEEP;

    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STAND);
    bc->action = OBJECT_ACTION_STAND;

    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // RET;
}

void Movement_step_bump(struct Object* bc){
    // LD_A(1);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = 1;

    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_BUMP);
    bc->stepType = STEP_TYPE_BUMP;

    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_BUMP);
    bc->action = OBJECT_ACTION_BUMP;

    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // RET;
}

void Movement_tree_shake(struct Object* bc){
    // LD_A(24);
    // LD_HL(OBJECT_STEP_DURATION);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->stepDuration = 24;

    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_SLEEP);
    bc->stepType = OBJECT_STEP_TYPE;

    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_WEIRD_TREE);
    bc->action = OBJECT_ACTION_WEIRD_TREE;

    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    // RET;
    bc->dirWalking = STANDING;
}

void Movement_remove_sliding(struct Object* bc){
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // RES_hl(SLIDING_F);
    bit_reset(bc->flags1, SLIDING_F);
    // JP(mContinueReadingMovement);
    return ContinueReadingMovement();
}

void Movement_set_sliding(struct Object* bc){
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // SET_hl(SLIDING_F);
    bit_set(bc->flags1, SLIDING_F);
    // JP(mContinueReadingMovement);
    return ContinueReadingMovement();
}

void Movement_remove_fixed_facing(struct Object* bc){
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // RES_hl(FIXED_FACING_F);
    bit_reset(bc->flags1, FIXED_FACING_F);
    // JP(mContinueReadingMovement);
    return ContinueReadingMovement();
}

void Movement_fix_facing(struct Object* bc){
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // SET_hl(FIXED_FACING_F);
    bit_set(bc->flags1, FIXED_FACING_F);
    // JP(mContinueReadingMovement);
    return ContinueReadingMovement();
}

void Movement_show_object(struct Object* bc){
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // RES_hl(INVISIBLE_F);
    bit_reset(bc->flags1, INVISIBLE_F);
    // JP(mContinueReadingMovement);
    return ContinueReadingMovement();
}

void Movement_hide_object(struct Object* bc){
    // LD_HL(OBJECT_FLAGS1);
    // ADD_HL_BC;
    // SET_hl(INVISIBLE_F);
    bit_set(bc->flags1, INVISIBLE_F);
    // JP(mContinueReadingMovement);
    return ContinueReadingMovement();
}

void Movement_hide_emote(struct Object* bc){
    // CALL(aDespawnEmote);
    DespawnEmote_Conv(bc);
    // JP(mContinueReadingMovement);
    return ContinueReadingMovement();
}

void Movement_show_emote(struct Object* bc){
    // CALL(aSpawnEmote);
    SpawnEmote_Conv(bc);
    // JP(mContinueReadingMovement);
    return ContinueReadingMovement();
}

void Movement_step_shake(struct Object* bc){
//  parameters:
//     displacement (DecimalParam)
    // CALL(aJumpMovementPointer);
    // CALL(aShakeScreen);
    ShakeScreen_Conv(bc, JumpMovementPointer_Conv());
    // JP(mContinueReadingMovement);
    return ContinueReadingMovement();
}

void Movement_turn_head_down(struct Object* bc){
    // LD_A(OW_DOWN);
    // JR(mTurnHead);
    return TurnHead(bc, OW_DOWN);
}

void Movement_turn_head_up(struct Object* bc){
    // LD_A(OW_UP);
    // JR(mTurnHead);
    return TurnHead(bc, OW_UP);
}

void Movement_turn_head_left(struct Object* bc){
    // LD_A(OW_LEFT);
    // JR(mTurnHead);
    return TurnHead(bc, OW_LEFT);
}

void Movement_turn_head_right(struct Object* bc){
    // LD_A(OW_RIGHT);
    // JR(mTurnHead);
    return TurnHead(bc, OW_RIGHT);
}

void TurnHead(struct Object* bc, uint8_t a){
    // LD_HL(OBJECT_FACING);
    // ADD_HL_BC;
    // LD_hl_A;
    bc->facing = a;

    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STAND);
    bc->action = OBJECT_ACTION_STAND;

    // LD_HL(OBJECT_DIRECTION_WALKING);
    // ADD_HL_BC;
    // LD_hl(STANDING);
    bc->dirWalking = STANDING;
    // RET;
}

void Movement_slow_step_down(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | DOWN);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_SLOW << 2 | DOWN);
}

void Movement_slow_step_up(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | UP);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_SLOW << 2 | UP);
}

void Movement_slow_step_left(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | LEFT);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_SLOW << 2 | LEFT);
}

void Movement_slow_step_right(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | RIGHT);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_SLOW << 2 | RIGHT);
}

void Movement_step_down(struct Object* bc){
    // LD_A(STEP_WALK << 2 | DOWN);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_WALK << 2 | DOWN);
}

void Movement_step_up(struct Object* bc){
    // LD_A(STEP_WALK << 2 | UP);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_WALK << 2 | UP);
}

void Movement_step_left(struct Object* bc){
    // LD_A(STEP_WALK << 2 | LEFT);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_WALK << 2 | LEFT);
}

void Movement_step_right(struct Object* bc){
    // LD_A(STEP_WALK << 2 | RIGHT);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_WALK << 2 | RIGHT);
}

void Movement_big_step_down(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | DOWN);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_BIKE << 2 | DOWN);
}

void Movement_big_step_up(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | UP);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_BIKE << 2 | UP);
}

void Movement_big_step_left(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | LEFT);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_BIKE << 2 | LEFT);
}

void Movement_big_step_right(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | RIGHT);
    // JP(mNormalStep);
    return NormalStep(bc, STEP_BIKE << 2 | RIGHT);
}

void Movement_turn_away_down(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | DOWN);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_SLOW << 2 | DOWN);
}

void Movement_turn_away_up(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | UP);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_SLOW << 2 | UP);
}

void Movement_turn_away_left(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | LEFT);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_SLOW << 2 | LEFT);
}

void Movement_turn_away_right(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | RIGHT);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_SLOW << 2 | RIGHT);
}

void Movement_turn_in_down(struct Object* bc){
    // LD_A(STEP_WALK << 2 | DOWN);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_WALK << 2 | DOWN);
}

void Movement_turn_in_up(struct Object* bc){
    // LD_A(STEP_WALK << 2 | UP);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_WALK << 2 | UP);
}

void Movement_turn_in_left(struct Object* bc){
    // LD_A(STEP_WALK << 2 | LEFT);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_WALK << 2 | LEFT);
}

void Movement_turn_in_right(struct Object* bc){
    // LD_A(STEP_WALK << 2 | RIGHT);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_WALK << 2 | RIGHT);
}

void Movement_turn_waterfall_down(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | DOWN);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_BIKE << 2 | DOWN);
}

void Movement_turn_waterfall_up(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | UP);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_BIKE << 2 | UP);
}

void Movement_turn_waterfall_left(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | LEFT);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_BIKE << 2 | LEFT);
}

void Movement_turn_waterfall_right(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | RIGHT);
    // JP(mTurningStep);
    return TurningStep(bc, STEP_BIKE << 2 | RIGHT);
}

void Movement_slow_slide_step_down(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | DOWN);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_SLOW << 2 | DOWN);
}

void Movement_slow_slide_step_up(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | UP);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_SLOW << 2 | UP);
}

void Movement_slow_slide_step_left(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | LEFT);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_SLOW << 2 | LEFT);
}

void Movement_slow_slide_step_right(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | RIGHT);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_SLOW << 2 | RIGHT);
}

void Movement_slide_step_down(struct Object* bc){
    // LD_A(STEP_WALK << 2 | DOWN);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_WALK << 2 | DOWN);
}

void Movement_slide_step_up(struct Object* bc){
    // LD_A(STEP_WALK << 2 | UP);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_WALK << 2 | UP);
}

void Movement_slide_step_left(struct Object* bc){
    // LD_A(STEP_WALK << 2 | LEFT);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_WALK << 2 | LEFT);
}

void Movement_slide_step_right(struct Object* bc){
    // LD_A(STEP_WALK << 2 | RIGHT);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_WALK << 2 | RIGHT);
}

void Movement_fast_slide_step_down(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | DOWN);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_BIKE << 2 | DOWN);
}

void Movement_fast_slide_step_up(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | UP);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_BIKE << 2 | UP);
}

void Movement_fast_slide_step_left(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | LEFT);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_BIKE << 2 | LEFT);
}

void Movement_fast_slide_step_right(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | RIGHT);
    // JP(mSlideStep);
    return SlideStep(bc, STEP_BIKE << 2 | RIGHT);
}

void Movement_slow_jump_step_down(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | DOWN);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_SLOW << 2 | DOWN);
}

void Movement_slow_jump_step_up(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | UP);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_SLOW << 2 | UP);
}

void Movement_slow_jump_step_left(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | LEFT);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_SLOW << 2 | LEFT);
}

void Movement_slow_jump_step_right(struct Object* bc){
    // LD_A(STEP_SLOW << 2 | RIGHT);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_SLOW << 2 | RIGHT);
}

void Movement_jump_step_down(struct Object* bc){
    // LD_A(STEP_WALK << 2 | DOWN);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_WALK << 2 | DOWN);
}

void Movement_jump_step_up(struct Object* bc){
    // LD_A(STEP_WALK << 2 | UP);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_WALK << 2 | UP);
}

void Movement_jump_step_left(struct Object* bc){
    // LD_A(STEP_WALK << 2 | LEFT);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_WALK << 2 | LEFT);
}

void Movement_jump_step_right(struct Object* bc){
    // LD_A(STEP_WALK << 2 | RIGHT);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_WALK << 2 | RIGHT);
}

void Movement_fast_jump_step_down(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | DOWN);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_BIKE << 2 | DOWN);
}

void Movement_fast_jump_step_up(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | UP);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_BIKE << 2 | UP);
}

void Movement_fast_jump_step_left(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | LEFT);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_BIKE << 2 | LEFT);
}

void Movement_fast_jump_step_right(struct Object* bc){
    // LD_A(STEP_BIKE << 2 | RIGHT);
    // JP(mJumpStep);
    return JumpStep(bc, STEP_BIKE << 2 | RIGHT);
}

void Movement_turn_step_down(struct Object* bc){
    // LD_A(OW_DOWN);
    // JR(mTurnStep);
    return TurnStep(bc, OW_DOWN);
}

void Movement_turn_step_up(struct Object* bc){
    // LD_A(OW_UP);
    // JR(mTurnStep);
    return TurnStep(bc, OW_UP);
}

void Movement_turn_step_left(struct Object* bc){
    // LD_A(OW_LEFT);
    // JR(mTurnStep);
    return TurnStep(bc, OW_LEFT);
}

void Movement_turn_step_right(struct Object* bc){
    // LD_A(OW_RIGHT);
    // JR(mTurnStep);
    return TurnStep(bc, OW_RIGHT);
}

void TurnStep(struct Object* bc, uint8_t a){
    // LD_HL(OBJECT_1D);  // new facing
    // ADD_HL_BC;
    // LD_hl_A;
    bc->field_1D = a;

    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STEP);
    bc->action = OBJECT_ACTION_STEP;

    // LD_HL(OBJECT_STEP_TYPE);
    // ADD_HL_BC;
    // LD_hl(STEP_TYPE_TURN);
    bc->stepType = STEP_TYPE_TURN;
    // RET;
}

void NormalStep(struct Object* bc, uint8_t a){
    // CALL(aInitStep);
    InitStep_Conv(bc, a);
    // CALL(aUpdateTallGrassFlags);
    UpdateTallGrassFlags_Conv(bc);
    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STEP);
    bc->action = OBJECT_ACTION_STEP;

    // LD_HL(OBJECT_NEXT_TILE);
    // ADD_HL_BC;
    // LD_A_hl;
    // CALL(aCheckSuperTallGrassTile);
    // IF_Z goto shake_grass;

    // CALL(aCheckGrassTile);
    // IF_C goto skip_grass;
    if(CheckSuperTallGrassTile_Conv(bc->nextTile) || CheckGrassTile_Conv(bc->nextTile)) {
    // shake_grass:
        // CALL(aShakeGrass);
        ShakeGrass_Conv(bc);
    }

// skip_grass:
    // LD_HL(wCenteredObject);
    // LDH_A_addr(hMapObjectIndex);
    // CP_A_hl;
    // IF_Z goto player;
    if(wram->wCenteredObject != hram->hMapObjectIndex) {
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_NPC_WALK);
        bc->stepType = STEP_TYPE_NPC_WALK;
        // RET;
        return;
    }
    else {
    // player:
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_PLAYER_WALK);
        bc->stepType = STEP_TYPE_PLAYER_WALK;
        // RET;
        return;
    }
}

void TurningStep(struct Object* bc, uint8_t a){
    // CALL(aInitStep);
    InitStep_Conv(bc, a);
    // CALL(aUpdateTallGrassFlags);
    UpdateTallGrassFlags_Conv(bc);

    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_SPIN);
    bc->action = OBJECT_ACTION_SPIN;

    // LD_HL(wCenteredObject);
    // LDH_A_addr(hMapObjectIndex);
    // CP_A_hl;
    // IF_Z goto player;
    if(wram->wCenteredObject != hram->hMapObjectIndex) {
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_NPC_WALK);
        bc->stepType = STEP_TYPE_NPC_WALK;
        // RET;
        return;
    } else {
    // player:
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_PLAYER_WALK);
        bc->stepType = STEP_TYPE_PLAYER_WALK;
        // RET;
        return;
    }
}

void SlideStep(struct Object* bc, uint8_t a){
    // CALL(aInitStep);
    InitStep_Conv(bc, a);
    // CALL(aUpdateTallGrassFlags);
    UpdateTallGrassFlags_Conv(bc);

    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STAND);
    bc->action = OBJECT_ACTION_STAND;

    // LD_HL(wCenteredObject);
    // LDH_A_addr(hMapObjectIndex);
    // CP_A_hl;
    // IF_Z goto player;
    if(wram->wCenteredObject != hram->hMapObjectIndex) {
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_NPC_WALK);
        bc->stepType = STEP_TYPE_NPC_WALK;
        // RET;
        return;
    }
    else {
    // player:
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_PLAYER_WALK);
        bc->stepType = STEP_TYPE_PLAYER_WALK;
        // RET;
        return;
    }
}

void JumpStep(struct Object* bc, uint8_t a){
    // CALL(aInitStep);
    InitStep_Conv(bc, a);
    // LD_HL(OBJECT_1F);
    // ADD_HL_BC;
    // LD_hl(0x0);
    bc->field_1F = 0x0;

    // LD_HL(OBJECT_FLAGS2);
    // ADD_HL_BC;
    // RES_hl(OVERHEAD_F);
    bit_reset(bc->flags2, OVERHEAD_F);

    // LD_HL(OBJECT_ACTION);
    // ADD_HL_BC;
    // LD_hl(OBJECT_ACTION_STEP);
    bc->action = OBJECT_ACTION_STEP;

    // CALL(aSpawnShadow);
    SpawnShadow_Conv(bc);

    // LD_HL(wCenteredObject);
    // LDH_A_addr(hMapObjectIndex);
    // CP_A_hl;
    // IF_Z goto player;
    if(wram->wCenteredObject != hram->hMapObjectIndex) {
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_NPC_JUMP);
        bc->stepType = STEP_TYPE_NPC_JUMP;
        // RET;
    }
    else {
    // player:
        // LD_HL(OBJECT_STEP_TYPE);
        // ADD_HL_BC;
        // LD_hl(STEP_TYPE_PLAYER_JUMP);
        bc->stepType = STEP_TYPE_PLAYER_JUMP;
        // RET;
    }
}
