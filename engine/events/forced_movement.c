#include "../../constants.h"
#include "../../util/scripting.h"
#include "forced_movement.h"

bool Script_ForcedMovement(script_s* s) {
    static const uint8_t MovementData_up[] = {
        step_dig(16),
        turn_in(DOWN),
        step_dig(16),
        turn_head(DOWN),
        movement_step_end,
    };

    static const uint8_t MovementData_down[] = {
        step_dig(16),
        turn_in(UP),
        step_dig(16),
        turn_head(UP),
        movement_step_end,
    };

    static const uint8_t MovementData_right[] = {
        step_dig(16),
        turn_in(LEFT),
        step_dig(16),
        turn_head(LEFT),
        movement_step_end,
    };

    static const uint8_t MovementData_left[] = {
        step_dig(16),
        turn_in(RIGHT),
        step_dig(16),
        turn_head(RIGHT),
        movement_step_end,
    };


    SCRIPT_BEGIN
    readvar(VAR_FACING)
    ifequal(DOWN, down)
    ifequal(UP, up)
    ifequal(LEFT, left)
    ifequal(RIGHT, right)
    s_end

up:
    applymovement(PLAYER, MovementData_up)
    s_end

down:
    applymovement(PLAYER, MovementData_down)
    s_end

right:
    applymovement(PLAYER, MovementData_right)
    s_end

left:
    applymovement(PLAYER, MovementData_left)
    s_end
    SCRIPT_END
}
