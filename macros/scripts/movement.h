// MovementPointers indexes (see engine/overworld/movement.asm)
// const_def 0, 4

// Directional movements

#define movement_turn_head 0x00
/*turn_head: MACRO
        db movement_turn_head | \1
ENDM*/
#define turn_head(_dir) (movement_turn_head | _dir)

#define movement_turn_step 0x04
/*turn_step: MACRO
        db movement_turn_step | \1
ENDM*/
#define turn_step(_dir) (movement_turn_step | _dir)

#define movement_slow_step 0x08
/*slow_step: MACRO
        db movement_slow_step | \1
ENDM*/
#define slow_step(_dir) (movement_slow_step | _dir)

#define movement_step 0x0c
/*step: MACRO
        db movement_step | \1
ENDM*/
#define step(_dir) (movement_step | _dir)

#define movement_big_step 0x10
/*big_step: MACRO
        db movement_big_step | \1
ENDM*/
#define big_step(_dir) (movement_big_step | _dir)

#define movement_slow_slide_step 0x14
/*slow_slide_step: MACRO
        db movement_slow_slide_step | \1
ENDM*/

#define movement_slide_step 0x18
/*slide_step: MACRO
        db movement_slide_step | \1
ENDM*/

#define movement_fast_slide_step 0x1c
/*fast_slide_step: MACRO
        db movement_fast_slide_step | \1
ENDM*/

#define movement_turn_away 0x20
/*turn_away: MACRO
        db movement_turn_away | \1
ENDM*/

#define movement_turn_in 0x24
/*turn_in: MACRO
        db movement_turn_in | \1
ENDM*/

#define movement_turn_waterfall 0x28
/*turn_waterfall: MACRO
        db movement_turn_waterfall | \1
ENDM*/

#define movement_slow_jump_step 0x2c
/*slow_jump_step: MACRO
        db movement_slow_jump_step | \1
ENDM*/

#define movement_jump_step 0x30
/*jump_step: MACRO
        db movement_jump_step | \1
ENDM*/

#define movement_fast_jump_step 0x34
/*fast_jump_step: MACRO
        db movement_fast_jump_step | \1
ENDM*/

// const_inc = 1

// Control
#define movement_remove_sliding 0x38
/*remove_sliding: MACRO
        db movement_remove_sliding
ENDM*/

#define movement_set_sliding 0x39
/*set_sliding: MACRO
        db movement_set_sliding
ENDM*/

#define movement_remove_fixed_facing 0x3a
/*remove_fixed_facing: MACRO
        db movement_remove_fixed_facing
ENDM*/

#define movement_fix_facing 0x3b
/*fix_facing: MACRO
        db movement_fix_facing
ENDM*/

#define movement_show_object 0x3c
/*show_object: MACRO
        db movement_show_object
ENDM*/

#define movement_hide_object 0x3d
/*hide_object: MACRO
        db movement_hide_object
ENDM*/

// Sleep

#define movement_step_sleep 0x3e
/*step_sleep: MACRO
if \1 <= 8
        db movement_step_sleep + \1 - 1
else
        db movement_step_sleep + 8, \1
endc
ENDM*/

// const_skip 8 // all step_sleep values

#define movement_step_end 0x47
/*step_end: MACRO
        db movement_step_end
ENDM*/

#define movement_step_48 0x48
/*step_48: MACRO
        db movement_step_48
        db \1 // ???
ENDM*/

#define movement_remove_object 0x49
/*remove_object: MACRO
        db movement_remove_object
ENDM*/

#define movement_step_loop 0x4a
/*step_loop: MACRO
        db movement_step_loop
ENDM*/

#define movement_step_4b 0x4b
/*step_4b: MACRO
        db movement_step_4b
ENDM*/

#define movement_teleport_from 0x4c
/*teleport_from: MACRO
        db movement_teleport_from
ENDM*/

#define movement_teleport_to 0x4d
/*teleport_to: MACRO
        db movement_teleport_to
ENDM*/

#define movement_skyfall 0x4e
/*skyfall: MACRO
        db movement_skyfall
ENDM*/

#define movement_step_dig 0x4f
/*step_dig: MACRO
        db movement_step_dig
        db \1 // length
ENDM*/

#define movement_step_bump 0x50
/*step_bump: MACRO
        db movement_step_bump
ENDM*/

#define movement_fish_got_bite 0x51
/*fish_got_bite: MACRO
        db movement_fish_got_bite
ENDM*/

#define movement_fish_cast_rod 0x52
/*fish_cast_rod: MACRO
        db movement_fish_cast_rod
ENDM*/

#define movement_hide_emote 0x53
/*hide_emote: MACRO
        db movement_hide_emote
ENDM*/

#define movement_show_emote 0x54
/*show_emote: MACRO
        db movement_show_emote
ENDM*/

#define movement_step_shake 0x55
/*step_shake: MACRO
        db movement_step_shake
        db \1 // displacement
ENDM*/

#define movement_tree_shake 0x56
/*tree_shake: MACRO
        db movement_tree_shake
ENDM*/

#define movement_rock_smash 0x57
/*rock_smash: MACRO
        db movement_rock_smash
        db \1 // length
ENDM*/

#define movement_return_dig 0x58
/*return_dig: MACRO
        db movement_return_dig
        db \1 // length
ENDM*/

#define movement_skyfall_top 0x59
/*skyfall_top: MACRO
        db movement_skyfall_top
ENDM*/

#define NUM_MOVEMENT_CMDS (movement_skyfall_top + 1)
