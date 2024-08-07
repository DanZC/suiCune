#include "../../constants.h"
#include "../../engine/battle/effect_commands.h"

const struct EffectFunc HeldStatUpItems[] = {
    {HELD_ATTACK_UP,     BattleCommand_AttackUp},
    {HELD_DEFENSE_UP,    BattleCommand_DefenseUp},
    {HELD_SPEED_UP,      BattleCommand_SpeedUp},
    {HELD_SP_ATTACK_UP,  BattleCommand_SpecialAttackUp},
    {HELD_SP_DEFENSE_UP, BattleCommand_SpecialDefenseUp},
    {HELD_ACCURACY_UP,   BattleCommand_AccuracyUp},
    {HELD_EVASION_UP,    BattleCommand_EvasionUp},
    {(uint8_t)-1,        NULL}, // end
};
