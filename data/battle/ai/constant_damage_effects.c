#include "../../../constants/move_effect_constants.h"
#include <stdint.h>
#include "constant_damage_effects.h"

// AIDamageCalc uses BattleCommand_ConstantDamage
// to calculate damage for these instead of
// BattleCommand_DamageCalc and BattleCommand_Stab.

const uint8_t ConstantDamageEffects[] = {
    EFFECT_SUPER_FANG,
    EFFECT_STATIC_DAMAGE,
    EFFECT_LEVEL_DAMAGE,
    EFFECT_PSYWAVE,
    (uint8_t)-1, // end
};
