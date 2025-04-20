#include "../../constants.h"
#include "item_effects.h"
#include "../../home/item.h"
#include "../../home/text.h"
#include "../../home/audio.h"
#include "../../home/joypad.h"
#include "../../home/battle.h"
#include "../../home/delay.h"
#include "../../home/copy.h"
#include "../../home/copy_name.h"
#include "../../home/menu.h"
#include "../../home/tilemap.h"
#include "../../home/pokemon.h"
#include "../../home/random.h"
#include "../../home/clear_sprites.h"
#include "../../home/flag.h"
#include "../../home/names.h"
#include "../../home/pokedex_flags.h"
#include "../../home/fade.h"
#include "../../home/gfx.h"
#include "../../home/string.h"
#include "../../home/sram.h"
#include "../battle_anims/anim_commands.h"
#include "../battle/returntobattle_useball.h"
#include "../battle/effect_commands.h"
#include "../battle/core.h"
#include "../events/overworld.h"
#include "../events/itemfinder.h"
#include "../events/squirtbottle.h"
#include "../events/card_key.h"
#include "../events/basement_key.h"
#include "../events/happiness_egg.h"
#include "../events/sacred_ash.h"
#include "../events/bug_contest/caught_mon.h"
#include "../menus/naming_screen.h"
#include "../pokemon/party_menu.h"
#include "../pokemon/health.h"
#include "../pokemon/experience.h"
#include "../pokemon/move_mon.h"
#include "../pokemon/level_up_happiness.h"
#include "../pokemon/tempmon.h"
#include "../pokemon/mon_stats.h"
#include "../pokemon/evolve.h"
#include "../pokemon/caught_data.h"
#include "../pokedex/new_pokedex_entry.h"
#include "../smallflag.h"
#include "../../mobile/mobile_41.h"
#include "../../data/moves/moves.h"
#include "../../data/text/common.h"
#include "../../data/text/battle.h"
#include "../../data/items/x_stats.h"
#include "../../data/items/heal_status.h"
#include "../../data/items/heal_hp.h"
#include "../../data/pokemon/evos_attacks_pointers.h"
#include "../../data/pokemon/dex_entries.h"
#include "../../data/wild/flee_mons.h"
#if !defined(_MSC_VER)
#include <stddef.h>
#endif

void v_DoItemEffect(void){
    LD_A_addr(wCurItem);
    LD_addr_A(wNamedObjectIndex);
    CALL(aGetItemName);
    CALL(aCopyName1);
    LD_A(1);
    LD_addr_A(wItemEffectSucceeded);
    LD_A_addr(wCurItem);
    DEC_A;
    LD_HL(mItemEffects);
    RST(aJumpTable);
    RET;

}

void v_DoItemEffect_Conv(item_t item){
    // LD_A_addr(wCurItem);
    wram->wCurItem = item;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetItemName);
    // CALL(aCopyName1);
    CopyName1(GetItemName(item));
    // LD_A(1);
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = TRUE;
    // LD_A_addr(wCurItem);
    // DEC_A;
    // LD_HL(mItemEffects);
    switch(item) {
    default:
    case NO_ITEM:       return NoEffect();
    case MASTER_BALL:   return PokeBallEffect();  // MASTER_BALL
    case ULTRA_BALL:    return PokeBallEffect();  // ULTRA_BALL
    case BRIGHTPOWDER:  return NoEffect();  // BRIGHTPOWDER
    case GREAT_BALL:    return PokeBallEffect();  // GREAT_BALL
    case POKE_BALL:     return PokeBallEffect();  // POKE_BALL
    //dw ['TownMapEffect'];  // TOWN_MAP
    case BICYCLE:       return BicycleEffect();  // BICYCLE
    case MOON_STONE:    return EvoStoneEffect();  // MOON_STONE
    case ANTIDOTE:      return StatusHealingEffect();  // ANTIDOTE
    case BURN_HEAL:     return StatusHealingEffect();  // BURN_HEAL
    case ICE_HEAL:      return StatusHealingEffect();  // ICE_HEAL
    case AWAKENING:     return StatusHealingEffect();  // AWAKENING
    case PARLYZ_HEAL:   return StatusHealingEffect();  // PARLYZ_HEAL
    case FULL_RESTORE:  return FullRestoreEffect();  // FULL_RESTORE
    case MAX_POTION:    return RestoreHPEffect();  // MAX_POTION
    case HYPER_POTION:  return RestoreHPEffect();  // HYPER_POTION
    case SUPER_POTION:  return RestoreHPEffect();  // SUPER_POTION
    case POTION:        return RestoreHPEffect();  // POTION
    case ESCAPE_ROPE:   return EscapeRopeEffect();  // ESCAPE_ROPE
    case REPEL:         return RepelEffect();  // REPEL
    case MAX_ELIXER:    return RestorePPEffect();  // MAX_ELIXER
    case FIRE_STONE:    return EvoStoneEffect();  // FIRE_STONE
    case THUNDERSTONE:  return EvoStoneEffect();  // THUNDERSTONE
    case WATER_STONE:   return EvoStoneEffect();  // WATER_STONE
    case ITEM_19:       return NoEffect();  // ITEM_19
    case HP_UP:         return VitaminEffect();  // HP_UP
    case PROTEIN:       return VitaminEffect();  // PROTEIN
    case IRON:          return VitaminEffect();  // IRON
    case CARBOS:        return VitaminEffect();  // CARBOS
    case LUCKY_PUNCH:   return NoEffect();  // LUCKY_PUNCH
    case CALCIUM:       return VitaminEffect();  // CALCIUM
    case RARE_CANDY:    return RareCandyEffect();  // RARE_CANDY
    case X_ACCURACY:    return XAccuracyEffect();  // X_ACCURACY
    case LEAF_STONE:    return EvoStoneEffect();  // LEAF_STONE
    case METAL_POWDER:  return NoEffect();  // METAL_POWDER
    case NUGGET:        return NoEffect();  // NUGGET
    case POKE_DOLL:     return PokeDollEffect();  // POKE_DOLL
    case FULL_HEAL:     return StatusHealingEffect();  // FULL_HEAL
    case REVIVE:        return ReviveEffect();  // REVIVE
    case MAX_REVIVE:    return ReviveEffect();  // MAX_REVIVE
    case GUARD_SPEC:    return GuardSpecEffect();  // GUARD_SPEC
    case SUPER_REPEL:   return SuperRepelEffect();  // SUPER_REPEL
    case MAX_REPEL:     return MaxRepelEffect();  // MAX_REPEL
    case DIRE_HIT:      return DireHitEffect();  // DIRE_HIT
    case ITEM_2D:       return NoEffect();  // ITEM_2D
    case FRESH_WATER:   return RestoreHPEffect();  // FRESH_WATER
    case SODA_POP:      return RestoreHPEffect();  // SODA_POP
    case LEMONADE:      return RestoreHPEffect();  // LEMONADE
    case X_ATTACK:      return XItemEffect();  // X_ATTACK
    case ITEM_32:       return NoEffect();  // ITEM_32
    case X_DEFEND:      return XItemEffect();  // X_DEFEND
    case X_SPEED:       return XItemEffect();  // X_SPEED
    case X_SPECIAL:     return XItemEffect();  // X_SPECIAL
    case COIN_CASE:     return CoinCaseEffect();  // COIN_CASE
    case ITEMFINDER:    return ItemfinderEffect();  // ITEMFINDER
    //dw ['PokeFluteEffect'];  // POKE_FLUTE
    case EXP_SHARE:     return NoEffect();  // EXP_SHARE
    case OLD_ROD:       return OldRodEffect();  // OLD_ROD
    case GOOD_ROD:      return GoodRodEffect();  // GOOD_ROD
    case SILVER_LEAF:   return NoEffect();  // SILVER_LEAF
    case SUPER_ROD:     return SuperRodEffect();  // SUPER_ROD
    case PP_UP:         return RestorePPEffect();  // PP_UP
    case ETHER:         return RestorePPEffect();  // ETHER
    case MAX_ETHER:     return RestorePPEffect();  // MAX_ETHER
    case ELIXER:        return RestorePPEffect();  // ELIXER
    case RED_SCALE:     return NoEffect();  // RED_SCALE
    case SECRETPOTION:  return NoEffect();  // SECRETPOTION
    case S_S_TICKET:    return NoEffect();  // S_S_TICKET
    case MYSTERY_EGG:   return NoEffect();  // MYSTERY_EGG
    case CLEAR_BELL:    return NoEffect();  // CLEAR_BELL
    case SILVER_WING:   return NoEffect();  // SILVER_WING
    case MOOMOO_MILK:   return RestoreHPEffect();  // MOOMOO_MILK
    case QUICK_CLAW:    return NoEffect();  // QUICK_CLAW
    case PSNCUREBERRY:  return StatusHealingEffect();  // PSNCUREBERRY
    case GOLD_LEAF:     return NoEffect();  // GOLD_LEAF
    case SOFT_SAND:     return NoEffect();  // SOFT_SAND
    case SHARP_BEAK:    return NoEffect();  // SHARP_BEAK
    case PRZCUREBERRY:  return StatusHealingEffect();  // PRZCUREBERRY
    case BURNT_BERRY:   return StatusHealingEffect();  // BURNT_BERRY
    case ICE_BERRY:     return StatusHealingEffect();  // ICE_BERRY
    case POISON_BARB:   return NoEffect();  // POISON_BARB
    case KINGS_ROCK:    return NoEffect();  // KINGS_ROCK
    case BITTER_BERRY:  return BitterBerryEffect();  // BITTER_BERRY
    case MINT_BERRY:    return StatusHealingEffect();  // MINT_BERRY
    case RED_APRICORN:  return NoEffect();  // RED_APRICORN
    case TINYMUSHROOM:  return NoEffect();  // TINYMUSHROOM
    case BIG_MUSHROOM:  return NoEffect();  // BIG_MUSHROOM
    case SILVERPOWDER:  return NoEffect();  // SILVERPOWDER
    case BLU_APRICORN:  return NoEffect();  // BLU_APRICORN
    case ITEM_5A:       return NoEffect();  // ITEM_5A
    case AMULET_COIN:   return NoEffect();  // AMULET_COIN
    case YLW_APRICORN:  return NoEffect();  // YLW_APRICORN
    case GRN_APRICORN:  return NoEffect();  // GRN_APRICORN
    case CLEANSE_TAG:   return NoEffect();  // CLEANSE_TAG
    case MYSTIC_WATER:  return NoEffect();  // MYSTIC_WATER
    case TWISTEDSPOON:  return NoEffect();  // TWISTEDSPOON
    case WHT_APRICORN:  return NoEffect();  // WHT_APRICORN
    case BLACKBELT_I:   return NoEffect();  // BLACKBELT_I
    case BLK_APRICORN:  return NoEffect();  // BLK_APRICORN
    case ITEM_64:       return NoEffect();  // ITEM_64
    case PNK_APRICORN:  return NoEffect();  // PNK_APRICORN
    case BLACKGLASSES:  return NoEffect();  // BLACKGLASSES
    case SLOWPOKETAIL:  return NoEffect();  // SLOWPOKETAIL
    case PINK_BOW:      return NoEffect();  // PINK_BOW
    case STICK:         return NoEffect();  // STICK
    case SMOKE_BALL:    return NoEffect();  // SMOKE_BALL
    case NEVERMELTICE:  return NoEffect();  // NEVERMELTICE
    case MAGNET:        return NoEffect();  // MAGNET
    case MIRACLEBERRY:  return StatusHealingEffect();  // MIRACLEBERRY
    case PEARL:         return NoEffect();  // PEARL
    case BIG_PEARL:     return NoEffect();  // BIG_PEARL
    case EVERSTONE:     return NoEffect();  // EVERSTONE
    case SPELL_TAG:     return NoEffect();  // SPELL_TAG
    case RAGECANDYBAR:  return RestoreHPEffect();  // RAGECANDYBAR
    case GS_BALL:       return NoEffect();  // GS_BALL
    case BLUE_CARD:     return BlueCardEffect();  // BLUE_CARD
    case MIRACLE_SEED:  return NoEffect();  // MIRACLE_SEED
    case THICK_CLUB:    return NoEffect();  // THICK_CLUB
    case FOCUS_BAND:    return NoEffect();  // FOCUS_BAND
    case ITEM_78:       return NoEffect();  // ITEM_78
    case ENERGYPOWDER:  return EnergypowderEffect();  // ENERGYPOWDER
    case ENERGY_ROOT:   return EnergyRootEffect();  // ENERGY_ROOT
    case HEAL_POWDER:   return HealPowderEffect();  // HEAL_POWDER
    case REVIVAL_HERB:  return RevivalHerbEffect();  // REVIVAL_HERB
    case HARD_STONE:    return NoEffect();  // HARD_STONE
    case LUCKY_EGG:     return NoEffect();  // LUCKY_EGG
    case CARD_KEY:      return CardKeyEffect();  // CARD_KEY
    case MACHINE_PART:  return NoEffect();  // MACHINE_PART
    case EGG_TICKET:    return NoEffect();  // EGG_TICKET
    case LOST_ITEM:     return NoEffect();  // LOST_ITEM
    case STARDUST:      return NoEffect();  // STARDUST
    case STAR_PIECE:    return NoEffect();  // STAR_PIECE
    case BASEMENT_KEY:  return BasementKeyEffect();  // BASEMENT_KEY
    case PASS:          return NoEffect();  // PASS
    case ITEM_87:       return NoEffect();  // ITEM_87
    case ITEM_88:       return NoEffect();  // ITEM_88
    case ITEM_89:       return NoEffect();  // ITEM_89
    case CHARCOAL:      return NoEffect();  // CHARCOAL
    case BERRY_JUICE:   return RestoreHPEffect();  // BERRY_JUICE
    case SCOPE_LENS:    return NoEffect();  // SCOPE_LENS
    case ITEM_8D:       return NoEffect();  // ITEM_8D
    case ITEM_8E:       return NoEffect();  // ITEM_8E
    case METAL_COAT:    return NoEffect();  // METAL_COAT
    case DRAGON_FANG:   return NoEffect();  // DRAGON_FANG
    case ITEM_91:       return NoEffect();  // ITEM_91
    case LEFTOVERS:     return NoEffect();  // LEFTOVERS
    case ITEM_93:       return NoEffect();  // ITEM_93
    case ITEM_94:       return NoEffect();  // ITEM_94
    case ITEM_95:       return NoEffect();  // ITEM_95
    case MYSTERYBERRY:  return RestorePPEffect();  // MYSTERYBERRY
    case DRAGON_SCALE:  return NoEffect();  // DRAGON_SCALE
    case BERSERK_GENE:  return NoEffect();  // BERSERK_GENE
    case ITEM_99:       return NoEffect();  // ITEM_99
    case ITEM_9A:       return NoEffect();  // ITEM_9A
    case ITEM_9B:       return NoEffect();  // ITEM_9B
    case SACRED_ASH:    return SacredAshEffect();  // SACRED_ASH
    case HEAVY_BALL:    return PokeBallEffect();  // HEAVY_BALL
    case FLOWER_MAIL:   return NoEffect();  // FLOWER_MAIL
    case LEVEL_BALL:    return PokeBallEffect();  // LEVEL_BALL
    case LURE_BALL:     return PokeBallEffect();  // LURE_BALL
    case FAST_BALL:     return PokeBallEffect();  // FAST_BALL
    case ITEM_A2:       return NoEffect();  // ITEM_A2
    case LIGHT_BALL:    return NoEffect();  // LIGHT_BALL
    case FRIEND_BALL:   return PokeBallEffect();  // FRIEND_BALL
    case MOON_BALL:     return PokeBallEffect();  // MOON_BALL
    case LOVE_BALL:     return PokeBallEffect();  // LOVE_BALL
    //dw ['NormalBoxEffect'];  // NORMAL_BOX
    //dw ['GorgeousBoxEffect'];  // GORGEOUS_BOX
    case SUN_STONE:     return EvoStoneEffect();  // SUN_STONE
    case POLKADOT_BOW:  return NoEffect();  // POLKADOT_BOW
    case ITEM_AB:       return NoEffect();  // ITEM_AB
    case UP_GRADE:      return NoEffect();  // UP_GRADE
    case BERRY:         return RestoreHPEffect();  // BERRY
    case GOLD_BERRY:    return RestoreHPEffect();  // GOLD_BERRY
    case SQUIRTBOTTLE:  return SquirtbottleEffect();  // SQUIRTBOTTLE
    case ITEM_B0:       return NoEffect();  // ITEM_B0
    case PARK_BALL:     return PokeBallEffect();  // PARK_BALL
    case RAINBOW_WING:  return NoEffect();  // RAINBOW_WING
    case ITEM_B3:       return NoEffect();  // ITEM_B3
    }
    // RST(aJumpTable);
    // RET;
}

void ItemEffects(void){
//  entries correspond to item ids (see constants/item_constants.asm)
    //table_width ['2', 'ItemEffects']
    //dw ['PokeBallEffect'];  // MASTER_BALL
    //dw ['PokeBallEffect'];  // ULTRA_BALL
    //dw ['NoEffect'];  // BRIGHTPOWDER
    //dw ['PokeBallEffect'];  // GREAT_BALL
    //dw ['PokeBallEffect'];  // POKE_BALL
    //dw ['TownMapEffect'];  // TOWN_MAP
    //dw ['BicycleEffect'];  // BICYCLE
    //dw ['EvoStoneEffect'];  // MOON_STONE
    //dw ['StatusHealingEffect'];  // ANTIDOTE
    //dw ['StatusHealingEffect'];  // BURN_HEAL
    //dw ['StatusHealingEffect'];  // ICE_HEAL
    //dw ['StatusHealingEffect'];  // AWAKENING
    //dw ['StatusHealingEffect'];  // PARLYZ_HEAL
    //dw ['FullRestoreEffect'];  // FULL_RESTORE
    //dw ['RestoreHPEffect'];  // MAX_POTION
    //dw ['RestoreHPEffect'];  // HYPER_POTION
    //dw ['RestoreHPEffect'];  // SUPER_POTION
    //dw ['RestoreHPEffect'];  // POTION
    //dw ['EscapeRopeEffect'];  // ESCAPE_ROPE
    //dw ['RepelEffect'];  // REPEL
    //dw ['RestorePPEffect'];  // MAX_ELIXER
    //dw ['EvoStoneEffect'];  // FIRE_STONE
    //dw ['EvoStoneEffect'];  // THUNDERSTONE
    //dw ['EvoStoneEffect'];  // WATER_STONE
    //dw ['NoEffect'];  // ITEM_19
    //dw ['VitaminEffect'];  // HP_UP
    //dw ['VitaminEffect'];  // PROTEIN
    //dw ['VitaminEffect'];  // IRON
    //dw ['VitaminEffect'];  // CARBOS
    //dw ['NoEffect'];  // LUCKY_PUNCH
    //dw ['VitaminEffect'];  // CALCIUM
    //dw ['RareCandyEffect'];  // RARE_CANDY
    //dw ['XAccuracyEffect'];  // X_ACCURACY
    //dw ['EvoStoneEffect'];  // LEAF_STONE
    //dw ['NoEffect'];  // METAL_POWDER
    //dw ['NoEffect'];  // NUGGET
    //dw ['PokeDollEffect'];  // POKE_DOLL
    //dw ['StatusHealingEffect'];  // FULL_HEAL
    //dw ['ReviveEffect'];  // REVIVE
    //dw ['ReviveEffect'];  // MAX_REVIVE
    //dw ['GuardSpecEffect'];  // GUARD_SPEC
    //dw ['SuperRepelEffect'];  // SUPER_REPEL
    //dw ['MaxRepelEffect'];  // MAX_REPEL
    //dw ['DireHitEffect'];  // DIRE_HIT
    //dw ['NoEffect'];  // ITEM_2D
    //dw ['RestoreHPEffect'];  // FRESH_WATER
    //dw ['RestoreHPEffect'];  // SODA_POP
    //dw ['RestoreHPEffect'];  // LEMONADE
    //dw ['XItemEffect'];  // X_ATTACK
    //dw ['NoEffect'];  // ITEM_32
    //dw ['XItemEffect'];  // X_DEFEND
    //dw ['XItemEffect'];  // X_SPEED
    //dw ['XItemEffect'];  // X_SPECIAL
    //dw ['CoinCaseEffect'];  // COIN_CASE
    //dw ['ItemfinderEffect'];  // ITEMFINDER
    //dw ['PokeFluteEffect'];  // POKE_FLUTE
    //dw ['NoEffect'];  // EXP_SHARE
    //dw ['OldRodEffect'];  // OLD_ROD
    //dw ['GoodRodEffect'];  // GOOD_ROD
    //dw ['NoEffect'];  // SILVER_LEAF
    //dw ['SuperRodEffect'];  // SUPER_ROD
    //dw ['RestorePPEffect'];  // PP_UP
    //dw ['RestorePPEffect'];  // ETHER
    //dw ['RestorePPEffect'];  // MAX_ETHER
    //dw ['RestorePPEffect'];  // ELIXER
    //dw ['NoEffect'];  // RED_SCALE
    //dw ['NoEffect'];  // SECRETPOTION
    //dw ['NoEffect'];  // S_S_TICKET
    //dw ['NoEffect'];  // MYSTERY_EGG
    //dw ['NoEffect'];  // CLEAR_BELL
    //dw ['NoEffect'];  // SILVER_WING
    //dw ['RestoreHPEffect'];  // MOOMOO_MILK
    //dw ['NoEffect'];  // QUICK_CLAW
    //dw ['StatusHealingEffect'];  // PSNCUREBERRY
    //dw ['NoEffect'];  // GOLD_LEAF
    //dw ['NoEffect'];  // SOFT_SAND
    //dw ['NoEffect'];  // SHARP_BEAK
    //dw ['StatusHealingEffect'];  // PRZCUREBERRY
    //dw ['StatusHealingEffect'];  // BURNT_BERRY
    //dw ['StatusHealingEffect'];  // ICE_BERRY
    //dw ['NoEffect'];  // POISON_BARB
    //dw ['NoEffect'];  // KINGS_ROCK
    //dw ['BitterBerryEffect'];  // BITTER_BERRY
    //dw ['StatusHealingEffect'];  // MINT_BERRY
    //dw ['NoEffect'];  // RED_APRICORN
    //dw ['NoEffect'];  // TINYMUSHROOM
    //dw ['NoEffect'];  // BIG_MUSHROOM
    //dw ['NoEffect'];  // SILVERPOWDER
    //dw ['NoEffect'];  // BLU_APRICORN
    //dw ['NoEffect'];  // ITEM_5A
    //dw ['NoEffect'];  // AMULET_COIN
    //dw ['NoEffect'];  // YLW_APRICORN
    //dw ['NoEffect'];  // GRN_APRICORN
    //dw ['NoEffect'];  // CLEANSE_TAG
    //dw ['NoEffect'];  // MYSTIC_WATER
    //dw ['NoEffect'];  // TWISTEDSPOON
    //dw ['NoEffect'];  // WHT_APRICORN
    //dw ['NoEffect'];  // BLACKBELT_I
    //dw ['NoEffect'];  // BLK_APRICORN
    //dw ['NoEffect'];  // ITEM_64
    //dw ['NoEffect'];  // PNK_APRICORN
    //dw ['NoEffect'];  // BLACKGLASSES
    //dw ['NoEffect'];  // SLOWPOKETAIL
    //dw ['NoEffect'];  // PINK_BOW
    //dw ['NoEffect'];  // STICK
    //dw ['NoEffect'];  // SMOKE_BALL
    //dw ['NoEffect'];  // NEVERMELTICE
    //dw ['NoEffect'];  // MAGNET
    //dw ['StatusHealingEffect'];  // MIRACLEBERRY
    //dw ['NoEffect'];  // PEARL
    //dw ['NoEffect'];  // BIG_PEARL
    //dw ['NoEffect'];  // EVERSTONE
    //dw ['NoEffect'];  // SPELL_TAG
    //dw ['RestoreHPEffect'];  // RAGECANDYBAR
    //dw ['NoEffect'];  // GS_BALL
    //dw ['BlueCardEffect'];  // BLUE_CARD
    //dw ['NoEffect'];  // MIRACLE_SEED
    //dw ['NoEffect'];  // THICK_CLUB
    //dw ['NoEffect'];  // FOCUS_BAND
    //dw ['NoEffect'];  // ITEM_78
    //dw ['EnergypowderEffect'];  // ENERGYPOWDER
    //dw ['EnergyRootEffect'];  // ENERGY_ROOT
    //dw ['HealPowderEffect'];  // HEAL_POWDER
    //dw ['RevivalHerbEffect'];  // REVIVAL_HERB
    //dw ['NoEffect'];  // HARD_STONE
    //dw ['NoEffect'];  // LUCKY_EGG
    //dw ['CardKeyEffect'];  // CARD_KEY
    //dw ['NoEffect'];  // MACHINE_PART
    //dw ['NoEffect'];  // EGG_TICKET
    //dw ['NoEffect'];  // LOST_ITEM
    //dw ['NoEffect'];  // STARDUST
    //dw ['NoEffect'];  // STAR_PIECE
    //dw ['BasementKeyEffect'];  // BASEMENT_KEY
    //dw ['NoEffect'];  // PASS
    //dw ['NoEffect'];  // ITEM_87
    //dw ['NoEffect'];  // ITEM_88
    //dw ['NoEffect'];  // ITEM_89
    //dw ['NoEffect'];  // CHARCOAL
    //dw ['RestoreHPEffect'];  // BERRY_JUICE
    //dw ['NoEffect'];  // SCOPE_LENS
    //dw ['NoEffect'];  // ITEM_8D
    //dw ['NoEffect'];  // ITEM_8E
    //dw ['NoEffect'];  // METAL_COAT
    //dw ['NoEffect'];  // DRAGON_FANG
    //dw ['NoEffect'];  // ITEM_91
    //dw ['NoEffect'];  // LEFTOVERS
    //dw ['NoEffect'];  // ITEM_93
    //dw ['NoEffect'];  // ITEM_94
    //dw ['NoEffect'];  // ITEM_95
    //dw ['RestorePPEffect'];  // MYSTERYBERRY
    //dw ['NoEffect'];  // DRAGON_SCALE
    //dw ['NoEffect'];  // BERSERK_GENE
    //dw ['NoEffect'];  // ITEM_99
    //dw ['NoEffect'];  // ITEM_9A
    //dw ['NoEffect'];  // ITEM_9B
    //dw ['SacredAshEffect'];  // SACRED_ASH
    //dw ['PokeBallEffect'];  // HEAVY_BALL
    //dw ['NoEffect'];  // FLOWER_MAIL
    //dw ['PokeBallEffect'];  // LEVEL_BALL
    //dw ['PokeBallEffect'];  // LURE_BALL
    //dw ['PokeBallEffect'];  // FAST_BALL
    //dw ['NoEffect'];  // ITEM_A2
    //dw ['NoEffect'];  // LIGHT_BALL
    //dw ['PokeBallEffect'];  // FRIEND_BALL
    //dw ['PokeBallEffect'];  // MOON_BALL
    //dw ['PokeBallEffect'];  // LOVE_BALL
    //dw ['NormalBoxEffect'];  // NORMAL_BOX
    //dw ['GorgeousBoxEffect'];  // GORGEOUS_BOX
    //dw ['EvoStoneEffect'];  // SUN_STONE
    //dw ['NoEffect'];  // POLKADOT_BOW
    //dw ['NoEffect'];  // ITEM_AB
    //dw ['NoEffect'];  // UP_GRADE
    //dw ['RestoreHPEffect'];  // BERRY
    //dw ['RestoreHPEffect'];  // GOLD_BERRY
    //dw ['SquirtbottleEffect'];  // SQUIRTBOTTLE
    //dw ['NoEffect'];  // ITEM_B0
    //dw ['PokeBallEffect'];  // PARK_BALL
    //dw ['NoEffect'];  // RAINBOW_WING
    //dw ['NoEffect'];  // ITEM_B3
    //assert_table_length ['ITEM_B3']
//  The items past ITEM_B3 do not have effect entries:
//     BRICK_PIECE
//     SURF_MAIL
//     LITEBLUEMAIL
//     PORTRAITMAIL
//     LOVELY_MAIL
//     EON_MAIL
//     MORPH_MAIL
//     BLUESKY_MAIL
//     MUSIC_MAIL
//     MIRAGE_MAIL
//     ITEM_BE
//  They all have the ITEMMENU_NOUSE attribute so they can't be used anyway.
//  NoEffect would be appropriate, with the table then being NUM_ITEMS long.
}

//  table of routines that increase or decrease the catch rate based on
//  which ball is used in a certain situation.
static const struct MultiplierFunc {
    item_t item;
    uint8_t (*func)(uint8_t);
} BallMultiplierFunctionTable[] = {
    {ULTRA_BALL,    UltraBallMultiplier},
    {GREAT_BALL,    GreatBallMultiplier},
    {SAFARI_BALL,   SafariBallMultiplier},  // Safari Ball, leftover from RBY
    {HEAVY_BALL,    HeavyBallMultiplier},
    {LEVEL_BALL,    LevelBallMultiplier},
    {LURE_BALL,     LureBallMultiplier},
    {FAST_BALL,     FastBallMultiplier},
    {MOON_BALL,     MoonBallMultiplier},
    {LOVE_BALL,     LoveBallMultiplier},
    {PARK_BALL,     ParkBallMultiplier},
    {(item_t)-1,    NULL},  // end
};

void PokeBallEffect(void){
    // LD_A_addr(wBattleMode);
    // DEC_A;
    // JP_NZ (mUseBallInTrainerBattle);
    if(wram->wBattleMode != WILD_BATTLE)
        return UseBallInTrainerBattle();

    // LD_A_addr(wPartyCount);
    // CP_A(PARTY_LENGTH);
    // IF_NZ goto room_in_party;
    if(wram->wPartyCount == PARTY_LENGTH) {
        // LD_A(BANK(sBoxCount));
        // CALL(aOpenSRAM);
        OpenSRAM_Conv(MBANK(asBoxCount));
        // LD_A_addr(sBoxCount);
        // CP_A(MONS_PER_BOX);
        uint8_t boxCount = gb_read(sBoxCount);
        // CALL(aCloseSRAM);
        CloseSRAM_Conv();
        // JP_Z (mBall_BoxIsFullMessage);
        if(boxCount >= MONS_PER_BOX)
            return Ball_BoxIsFullMessage();
    }

// room_in_party:
    // XOR_A_A;
    // LD_addr_A(wWildMon);
    wram->wWildMon = 0x0;
    // LD_A_addr(wCurItem);
    // CP_A(PARK_BALL);
    // CALL_NZ (aReturnToBattle_UseBall);
    if(wram->wCurItem != PARK_BALL) // We use the Park Ball from the battle screen.
        ReturnToBattle_UseBall();

    // LD_HL(wOptions);
    // RES_hl(NO_TEXT_SCROLL);
    bit_reset(wram->wOptions, NO_TEXT_SCROLL);
    // LD_HL(mItemUsedText);
    // CALL(aPrintText);
    PrintText_Conv2(ItemUsedText);

    // LD_A_addr(wEnemyMonCatchRate);
    // LD_B_A;
    uint8_t b = wram->wEnemyMonCatchRate;
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_TUTORIAL);
    // JP_Z (mPokeBallEffect_catch_without_fail);
    // LD_A_addr(wCurItem);
    // CP_A(MASTER_BALL);
    // JP_Z (mPokeBallEffect_catch_without_fail);
    if(wram->wBattleType != BATTLETYPE_TUTORIAL && wram->wCurItem != MASTER_BALL) {
        // LD_A_addr(wCurItem);
        // LD_C_A;
        // LD_HL(mBallMultiplierFunctionTable);
        const struct MultiplierFunc* ball_mul = BallMultiplierFunctionTable;

        while(ball_mul->item != (item_t)-1) {
        // get_multiplier_loop:
            // LD_A_hli;
            // CP_A(0xff);
            // IF_Z goto skip_or_return_from_ball_fn;
            // CP_A_C;
            // IF_Z goto call_ball_function;
            if(wram->wCurItem == ball_mul->item) {
            // call_ball_function:
                // LD_A_hli;
                // LD_H_hl;
                // LD_L_A;
                // LD_DE(mPokeBallEffect_skip_or_return_from_ball_fn);
                // PUSH_DE;
                // JP_hl;
                b = ball_mul->func(b);
                break;
            }
            // INC_HL;
            // INC_HL;
            // goto get_multiplier_loop;
            ball_mul++;
        }

    // skip_or_return_from_ball_fn:
        // LD_A_addr(wCurItem);
        // CP_A(LEVEL_BALL);
        // LD_A_B;
        // JP_Z (mPokeBallEffect_skip_hp_calc);

        if(wram->wCurItem != LEVEL_BALL) {
            // LD_A_B;
            // LDH_addr_A(hMultiplicand + 2);
            uint8_t base = b;

            // LD_HL(wEnemyMonHP);
            // LD_B_hl;
            // INC_HL;
            // LD_C_hl;
            uint16_t hp = BigEndianToNative16(wram->wEnemyMon.hp);
            // INC_HL;
            // LD_D_hl;
            // INC_HL;
            // LD_E_hl;
            uint16_t maxhp = BigEndianToNative16(wram->wEnemyMon.maxHP);
            // SLA_C;
            // RL_B;
            hp <<= 1;

            // LD_H_D;
            // LD_L_E;
            // ADD_HL_DE;
            // ADD_HL_DE;
            // LD_D_H;
            // LD_E_L;
            maxhp *= 3;
            // LD_A_D;
            // AND_A_A;
            // IF_Z goto okay_1;

            if(maxhp > 0xff) {
                // SRL_D;
                // RR_E;
                // SRL_D;
                // RR_E;
                maxhp >>= 2;
                // SRL_B;
                // RR_C;
                // SRL_B;
                // RR_C;
                hp >>= 2;

                // LD_A_C;
                // AND_A_A;
                // IF_NZ goto okay_1;
                // LD_C(0x1);
                if(hp == 0) {
                    hp = 0x1;
                }
            }

        // okay_1:
            // LD_B_E;

            // PUSH_BC;
            // LD_A_B;
            // SUB_A_C;
            uint16_t mul = maxhp - hp;
            // LDH_addr_A(hMultiplier);
            // XOR_A_A;
            // LDH_addr_A(hDividend + 0);
            // LDH_addr_A(hMultiplicand + 0);
            // LDH_addr_A(hMultiplicand + 1);
            // CALL(aMultiply);
            // POP_BC;

            // LD_A_B;
            // LDH_addr_A(hDivisor);
            // LD_B(4);
            // CALL(aDivide);
            uint8_t num = (uint8_t)((base * mul) / maxhp);

            // LDH_A_addr(hQuotient + 3);
            // AND_A_A;
            // IF_NZ goto statuscheck;
            // LD_A(1);
            if(num == 0)
                num = 1;

        // statuscheck:
        //  This routine is buggy. It was intended that SLP and FRZ provide a higher
        //  catch rate than BRN/PSN/PAR, which in turn provide a higher catch rate than
        //  no status effect at all. But instead, it makes BRN/PSN/PAR provide no
        //  benefit.
        //  Uncomment the line below to fix this.
            // LD_B_A;
            b = num;
            uint8_t status_add;
            // LD_A_addr(wEnemyMonStatus);
            // AND_A(1 << FRZ | SLP);
            // LD_C(10);
            // IF_NZ goto addstatus;
            if(wram->wEnemyMon.status[0] & (1 << FRZ | SLP))
                status_add = 10;
#if BUGFIX_BRN_PSN_PAR_CATCH_RATE
            else if(wram->wEnemyMon.status[0])
#else
        // ld a, [wEnemyMonStatus]
            else if(wram->wEnemyMon.status[0] & (1 << FRZ | SLP))
            // AND_A_A;
#endif
                status_add = 5;
            // LD_C(5);
            // IF_NZ goto addstatus;
            // LD_C(0);
            else
                status_add = 0;

        // addstatus:
            // LD_A_B;
            // ADD_A_C;
            // IF_NC goto max_1;
            // LD_A(0xff);
            if(b + status_add > 0xff)
                status_add = 0xff;
            else
                status_add += b;

        // max_1:
        // BUG: farcall overwrites a, and GetItemHeldEffect takes b anyway.
        // This is probably the reason the HELD_CATCH_CHANCE effect is never used.
        // Uncomment the line below to fix.
            // LD_D_A;
            // PUSH_DE;
            // LD_A_addr(wBattleMonItem);
#if BUGFIX_HELD_ITEM_CATCH_CHANCE
        // ld b, a
            // FARCALL(aGetItemHeldEffect);
            uint16_t held_effect = GetItemHeldEffect_Conv(wram->wBattleMon.item);
#else
            // FARCALL(aGetItemHeldEffect);
            uint16_t held_effect = GetItemHeldEffect_Conv(b);
#endif
            // LD_A_B;
            // CP_A(HELD_CATCH_CHANCE);
            // POP_DE;
            // LD_A_D;
            b = status_add;
            // IF_NZ goto max_2;
            if(HIGH(held_effect) == HELD_CATCH_CHANCE) {
                // ADD_A_C;
                // IF_NC goto max_2;
                if(b + LOW(held_effect) > 0xff)
                    b = 0xff;
                else
                    b += LOW(held_effect);
                // LD_A(0xff);
            // max_2:;
            }
        }

    // skip_hp_calc:
        // LD_B_A;
        // LD_addr_A(wFinalCatchRate);
        wram->wFinalCatchRate = b;
        // CALL(aRandom);
        uint8_t r = Random();

        // CP_A_B;
        // LD_A(0);
        // IF_Z goto catch_without_fail;
        // IF_NC goto fail_to_catch;
        if(r > b)
            wram->wWildMon = 0;
        else
            wram->wWildMon = wram->wEnemyMon.species;
    }
    else {
    // catch_without_fail:
        // LD_A_addr(wEnemyMonSpecies);
        wram->wWildMon = wram->wEnemyMon.species;
    }

// fail_to_catch:
    // LD_addr_A(wWildMon);
    // LD_C(20);
    // CALL(aDelayFrames);
    DelayFrames(20);

    // LD_A_addr(wCurItem);
    // CP_A(POKE_BALL + 1);  // Assumes Master/Ultra/Great come before
    // IF_C goto not_kurt_ball;
    // LD_A(POKE_BALL);

// not_kurt_ball:
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = (wram->wCurItem < POKE_BALL + 1)? wram->wCurItem: POKE_BALL;

    // LD_DE(ANIM_THROW_POKE_BALL);
    // LD_A_E;
    // LD_addr_A(wFXAnimID);
    // LD_A_D;
    // LD_addr_A(wFXAnimID + 1);
    wram->wFXAnimID = ANIM_THROW_POKE_BALL;
    // XOR_A_A;
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = TURN_PLAYER;
    // LD_addr_A(wThrownBallWobbleCount);
    wram->wThrownBallWobbleCount = 0;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // PREDEF(pPlayBattleAnim);
    PlayBattleAnim();

    // LD_A_addr(wWildMon);
    // AND_A_A;
    // IF_NZ goto caught;
    if(wram->wWildMon == 0) {
        // LD_A_addr(wThrownBallWobbleCount);
        // CP_A(1);
        // LD_HL(mBallBrokeFreeText);
        // JP_Z (mPokeBallEffect_shake_and_break_free);
        if(wram->wThrownBallWobbleCount == 1) {
            PrintText_Conv2(BallBrokeFreeText);
            ClearSprites();
            goto return_from_capture;
        }
        // CP_A(2);
        // LD_HL(mBallAppearedCaughtText);
        // JP_Z (mPokeBallEffect_shake_and_break_free);
        else if(wram->wThrownBallWobbleCount == 2) {
            PrintText_Conv2(BallAppearedCaughtText);
            ClearSprites();
            goto return_from_capture;
        }
        // CP_A(3);
        // LD_HL(mBallAlmostHadItText);
        // JP_Z (mPokeBallEffect_shake_and_break_free);
        else if(wram->wThrownBallWobbleCount == 3) {
            PrintText_Conv2(BallAlmostHadItText);
            ClearSprites();
            goto return_from_capture;
        }
        // CP_A(4);
        // LD_HL(mBallSoCloseText);
        // JP_Z (mPokeBallEffect_shake_and_break_free);
        else if(wram->wThrownBallWobbleCount == 4) {
            PrintText_Conv2(BallSoCloseText);
            ClearSprites();
            goto return_from_capture;
        }
    }

// caught:
    // LD_HL(wEnemyMonStatus);
    // LD_A_hli;
    // PUSH_AF;
    uint8_t enemyStatus = wram->wEnemyMon.status[0];
    // INC_HL;
    // LD_A_hli;
    // PUSH_AF;
    uint16_t enemyHP = wram->wEnemyMon.hp;
    // LD_A_hl;
    // PUSH_AF;
    // PUSH_HL;
    // LD_HL(wEnemyMonItem);
    // LD_A_hl;
    // PUSH_AF;
    item_t enemyItem = wram->wEnemyMon.item;
    // PUSH_HL;
    // LD_HL(wEnemySubStatus5);
    // LD_A_hl;
    // PUSH_AF;
    uint8_t enemySS5 = wram->wEnemySubStatus5;
    // SET_hl(SUBSTATUS_TRANSFORMED);
    bit_set(wram->wEnemySubStatus5, SUBSTATUS_TRANSFORMED);

//  This code is buggy. Any wild Pokémon that has Transformed will be
//  caught as a Ditto, even if it was something else like Mew.
//  To fix, do not set [wTempEnemyMonSpecies] to DITTO.
    // BIT_A(SUBSTATUS_TRANSFORMED);
    // IF_NZ goto ditto;
    // goto not_ditto;
    if(bit_test(enemySS5, SUBSTATUS_TRANSFORMED)) {
    // ditto:
#if !BUGFIX_CAUGHT_TRANSFORMED_MON_BECOMES_DITTO
        // LD_A(DITTO);
        // LD_addr_A(wTempEnemyMonSpecies);
        wram->wTempEnemyMonSpecies = DITTO;
#endif
        // goto load_data;
    }
    else {
    // not_ditto:
        // SET_hl(SUBSTATUS_TRANSFORMED);
        bit_set(wram->wEnemySubStatus5, SUBSTATUS_TRANSFORMED); // Why are we setting this variable twice?
        // LD_HL(wEnemyBackupDVs);
        // LD_A_addr(wEnemyMonDVs);
        // LD_hli_A;
        // LD_A_addr(wEnemyMonDVs + 1);
        // LD_hl_A;
        wram->wEnemyBackupDVs = wram->wEnemyMon.dvs;
    }

// load_data:
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wTempEnemyMonSpecies;
    // LD_A_addr(wEnemyMonLevel);
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = wram->wEnemyMon.level;
    // FARCALL(aLoadEnemyMon);
    LoadEnemyMon();

    // POP_AF;
    // LD_addr_A(wEnemySubStatus5);
    wram->wEnemySubStatus5 = enemySS5;

    // POP_HL;
    // POP_AF;
    // LD_hl_A;
    wram->wEnemyMon.item = enemyItem;
    // POP_HL;
    // POP_AF;
    // LD_hld_A;
    // POP_AF;
    // LD_hld_A;
    wram->wEnemyMon.hp = enemyHP;
    // DEC_HL;
    // POP_AF;
    // LD_hl_A;
    wram->wEnemyMon.status[0] = enemyStatus;

    // LD_HL(wEnemySubStatus5);
    // BIT_hl(SUBSTATUS_TRANSFORMED);
    // IF_NZ goto Transformed;
    if(!bit_test(wram->wEnemySubStatus5, SUBSTATUS_TRANSFORMED)) {
        // LD_HL(wWildMonMoves);
        // LD_DE(wEnemyMonMoves);
        // LD_BC(NUM_MOVES);
        // CALL(aCopyBytes);
        CopyBytes(wram->wEnemyMon.moves, wram->wWildMonMoves, sizeof(wram->wEnemyMon.moves));

        // LD_HL(wWildMonPP);
        // LD_DE(wEnemyMonPP);
        // LD_BC(NUM_MOVES);
        // CALL(aCopyBytes);
        CopyBytes(wram->wEnemyMon.pp, wram->wWildMonPP, sizeof(wram->wEnemyMon.pp));
    }

// Transformed:
    // LD_A_addr(wEnemyMonSpecies);
    // LD_addr_A(wWildMon);
    // LD_addr_A(wCurPartySpecies);
    // LD_addr_A(wTempSpecies);
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_TUTORIAL);
    // JP_Z (mPokeBallEffect_FinishTutorial);
    if(wram->wBattleType == BATTLETYPE_TUTORIAL) {
    // FinishTutorial:
        // LD_HL(mText_GotchaMonWasCaught);

    // shake_and_break_free:
        // CALL(aPrintText);
        PrintText_Conv2(Text_GotchaMonWasCaught);
        // CALL(aClearSprites);
        ClearSprites();
    }
    else {
        // FARCALL(aStubbedTrainerRankings_WildMonsCaught);
        StubbedTrainerRankings_WildMonsCaught();

        // LD_HL(mText_GotchaMonWasCaught);
        // CALL(aPrintText);
        PrintText_Conv2(Text_GotchaMonWasCaught);

        // CALL(aClearSprites);
        ClearSprites();

        // LD_A_addr(wTempSpecies);
        // DEC_A;
        // CALL(aCheckCaughtMon);
        bool caught = CheckCaughtMon_Conv(wram->wEnemyMon.species - 1);

        // LD_A_C;
        // PUSH_AF;
        // LD_A_addr(wTempSpecies);
        // DEC_A;
        // CALL(aSetSeenAndCaughtMon);
        SetSeenAndCaughtMon_Conv(wram->wEnemyMon.species - 1);
        // POP_AF;
        // AND_A_A;
        // IF_NZ goto skip_pokedex;

        // CALL(aCheckReceivedDex);
        // IF_Z goto skip_pokedex;

        if(!caught && CheckReceivedDex()) {
            // LD_HL(mNewDexDataText);
            // CALL(aPrintText);
            PrintText_Conv2(NewDexDataText);

            // CALL(aClearSprites);
            ClearSprites();

            // LD_A_addr(wEnemyMonSpecies);
            // LD_addr_A(wTempSpecies);
            wram->wTempSpecies = wram->wEnemyMon.species;
            // PREDEF(pNewPokedexEntry);
            NewPokedexEntry();
        }

    // skip_pokedex:
        // LD_A_addr(wBattleType);
        // CP_A(BATTLETYPE_CONTEST);
        // JP_Z (mPokeBallEffect_catch_bug_contest_mon);
        if(wram->wBattleType == BATTLETYPE_CONTEST) {
        // catch_bug_contest_mon:
            // FARCALL(aBugContest_SetCaughtContestMon);
            BugContest_SetCaughtContestMon();
            // goto return_from_capture;
        }
        else {
            // CP_A(BATTLETYPE_CELEBI);
            // IF_NZ goto not_celebi;
            if(wram->wBattleType == BATTLETYPE_CELEBI) {
                // LD_HL(wBattleResult);
                // SET_hl(BATTLERESULT_CAUGHT_CELEBI);
                bit_set(wram->wBattleResult, BATTLERESULT_CAUGHT_CELEBI);
            }

        // not_celebi:
            // LD_A_addr(wPartyCount);
            // CP_A(PARTY_LENGTH);
            // IF_Z goto SendToPC;
            if(wram->wPartyCount != PARTY_LENGTH) {
                // XOR_A_A;  // PARTYMON
                // LD_addr_A(wMonType);
                wram->wMonType = PARTYMON;
                // CALL(aClearSprites);
                ClearSprites();

                // PREDEF(pTryAddMonToParty);
                TryAddMonToParty_Conv(wram->wCurPartySpecies, wram->wCurPartyLevel);

                // FARCALL(aSetCaughtData);
                SetCaughtData_Conv(wram->wCurPartyLevel);

                // LD_A_addr(wCurItem);
                // CP_A(FRIEND_BALL);
                // IF_NZ goto SkipPartyMonFriendBall;
                if(wram->wCurItem == FRIEND_BALL) {
                    // LD_A_addr(wPartyCount);
                    // DEC_A;
                    // LD_HL(wPartyMon1Happiness);
                    // LD_BC(PARTYMON_STRUCT_LENGTH);
                    // CALL(aAddNTimes);

                    // LD_A(FRIEND_BALL_HAPPINESS);
                    // LD_hl_A;
                    wram->wPartyMon[wram->wPartyCount - 1].mon.happiness = FRIEND_BALL_HAPPINESS;
                }

            // SkipPartyMonFriendBall:
                // LD_HL(mAskGiveNicknameText);
                // CALL(aPrintText);
                PrintText_Conv2(AskGiveNicknameText);

                // LD_A_addr(wCurPartySpecies);
                // LD_addr_A(wNamedObjectIndex);
                // CALL(aGetPokemonName);
                GetPokemonName(wram->wCurPartySpecies);

                // CALL(aYesNoBox);
                // JP_C (mPokeBallEffect_return_from_capture);
                if(YesNoBox_Conv()) {
                    // LD_A_addr(wPartyCount);
                    // DEC_A;
                    // LD_addr_A(wCurPartyMon);
                    wram->wCurPartyMon = wram->wPartyCount - 1;
                    // LD_HL(wPartyMonNicknames);
                    // LD_BC(MON_NAME_LENGTH);
                    // CALL(aAddNTimes);
                    uint8_t* nick = wram->wPartyMonNickname[wram->wCurPartyMon];

                    // LD_D_H;
                    // LD_E_L;
                    // PUSH_DE;
                    // XOR_A_A;  // PARTYMON
                    // LD_addr_A(wMonType);
                    wram->wMonType = PARTYMON;
                    // LD_B(NAME_MON);
                    // FARCALL(aNamingScreen);
                    NamingScreen_Conv(nick, NAME_MON);

                    // CALL(aRotateThreePalettesRight);
                    RotateThreePalettesRight_Conv();

                    // CALL(aLoadStandardFont);
                    LoadStandardFont_Conv();

                    // POP_HL;
                    // LD_DE(wStringBuffer1);
                    // CALL(aInitName);
                    InitName_Conv2(nick, wram->wStringBuffer1);
                }
                // JP(mPokeBallEffect_return_from_capture);
            }
            else {
            // SendToPC:
                // CALL(aClearSprites);
                ClearSprites();

                // PREDEF(pSendMonIntoBox);
                SendMonIntoBox_Conv();

                // FARCALL(aSetBoxMonCaughtData);
                SetBoxMonCaughtData(wram->wCurPartyLevel);

                // LD_A(BANK(sBoxCount));
                // CALL(aOpenSRAM);
                OpenSRAM_Conv(MBANK(asBoxCount));

                // LD_A_addr(sBoxCount);
                // CP_A(MONS_PER_BOX);
                // IF_NZ goto BoxNotFullYet;
                if(gb_read(sBoxCount) == MONS_PER_BOX) {
                    // LD_HL(wBattleResult);
                    // SET_hl(BATTLERESULT_BOX_FULL);
                    bit_set(wram->wBattleResult, BATTLERESULT_BOX_FULL);
                }

            // BoxNotFullYet:
                // LD_A_addr(wCurItem);
                // CP_A(FRIEND_BALL);
                // IF_NZ goto SkipBoxMonFriendBall;
                if(wram->wCurItem == FRIEND_BALL) {
                // The captured mon is now first in the box
                    // LD_A(FRIEND_BALL_HAPPINESS);
                    // LD_addr_A(sBoxMon1Happiness);
                    gb_write(sBoxMon1Happiness, FRIEND_BALL_HAPPINESS);
                }

            // SkipBoxMonFriendBall:
                // CALL(aCloseSRAM);
                CloseSRAM_Conv();

                // LD_HL(mAskGiveNicknameText);
                // CALL(aPrintText);
                PrintText_Conv2(AskGiveNicknameText);

                // LD_A_addr(wCurPartySpecies);
                // LD_addr_A(wNamedObjectIndex);
                // CALL(aGetPokemonName);
                GetPokemonName(wram->wCurPartySpecies);

                // CALL(aYesNoBox);
                // IF_C goto SkipBoxMonNickname;
                if(YesNoBox_Conv()) {
                    // XOR_A_A;
                    // LD_addr_A(wCurPartyMon);
                    wram->wCurPartyMon = 0x0;
                    // LD_A(BOXMON);
                    // LD_addr_A(wMonType);
                    wram->wMonType = BOXMON;
                    // LD_DE(wMonOrItemNameBuffer);
                    // LD_B(NAME_MON);
                    // FARCALL(aNamingScreen);
                    NamingScreen_Conv(wram->wMonOrItemNameBuffer, NAME_MON);

                    // LD_A(BANK(sBoxMonNicknames));
                    // CALL(aOpenSRAM);
                    OpenSRAM_Conv(MBANK(asBoxMonNicknames));

                    // LD_HL(wMonOrItemNameBuffer);
                    // LD_DE(sBoxMonNicknames);
                    // LD_BC(MON_NAME_LENGTH);
                    // CALL(aCopyBytes);
                    CopyBytes(GBToRAMAddr(sBoxMonNicknames), wram->wMonOrItemNameBuffer, MON_NAME_LENGTH);

                    // LD_HL(sBoxMonNicknames);
                    // LD_DE(wStringBuffer1);
                    // CALL(aInitName);
                    InitName_Conv2(GBToRAMAddr(sBoxMonNicknames), wram->wStringBuffer1);

                    // CALL(aCloseSRAM);
                    CloseSRAM_Conv();
                }
                
            // SkipBoxMonNickname:
                // LD_A(BANK(sBoxMonNicknames));
                // CALL(aOpenSRAM);
                OpenSRAM_Conv(MBANK(asBoxMonNicknames));

                // LD_HL(sBoxMonNicknames);
                // LD_DE(wMonOrItemNameBuffer);
                // LD_BC(MON_NAME_LENGTH);
                // CALL(aCopyBytes);
                CopyBytes(wram->wMonOrItemNameBuffer, GBToRAMAddr(sBoxMonNicknames), MON_NAME_LENGTH);

                // CALL(aCloseSRAM);
                CloseSRAM_Conv();

                // LD_HL(mBallSentToPCText);
                // CALL(aPrintText);
                PrintText_Conv2(BallSentToPCText);

                // CALL(aRotateThreePalettesRight);
                RotateThreePalettesRight_Conv();
                // CALL(aLoadStandardFont);
                LoadStandardFont_Conv();
                // goto return_from_capture;
            }
        }
    }

// FinishTutorial:
    // LD_HL(mText_GotchaMonWasCaught);

// shake_and_break_free:
    // CALL(aPrintText);
    // CALL(aClearSprites);

return_from_capture:
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_TUTORIAL);
    // RET_Z ;
    // CP_A(BATTLETYPE_DEBUG);
    // RET_Z ;
    if(wram->wBattleType == BATTLETYPE_TUTORIAL || wram->wBattleType == BATTLETYPE_DEBUG)
        return;
    // CP_A(BATTLETYPE_CONTEST);
    // IF_Z goto used_park_ball;
    if(wram->wBattleType == BATTLETYPE_CONTEST) {
    // used_park_ball:
        // LD_HL(wParkBallsRemaining);
        // DEC_hl;
        wram->wParkBallsRemaining--;
        // RET;
    }

    // LD_A_addr(wWildMon);
    // AND_A_A;
    // IF_Z goto toss;
    if(wram->wWildMon != 0) {
        // CALL(aClearBGPalettes);
        ClearBGPalettes_Conv();
        // CALL(aClearTilemap);
        ClearTilemap_Conv2();
    }

// toss:
    // LD_HL(wNumItems);
    // INC_A;
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = 1;
    // JP(mTossItem);
    TossItem_Conv((item_pocket_s*)&wram->wNumItems, wram->wCurItem);
}

//  multiply catch rate by 2
uint8_t UltraBallMultiplier(uint8_t b){
    // SLA_B;
    // RET_NC ;
    if((b * 2) <= 0xff)
        return b * 2;
    // LD_B(0xff);
    // RET;
    return 0xff;
}

uint8_t SafariBallMultiplier(uint8_t b){
    return GreatBallMultiplier(b);
}

uint8_t GreatBallMultiplier(uint8_t b){
    return ParkBallMultiplier(b);
}

//  multiply catch rate by 1.5
uint8_t ParkBallMultiplier(uint8_t b){
    // LD_A_B;
    // SRL_A;
    // ADD_A_B;
    // LD_B_A;
    // RET_NC ;
    if((b + (b >> 1)) <= 0xff)
        return b + (b >> 1);
    // LD_B(0xff);
    // RET;
    return 0xff;
}

void GetPokedexEntryBank(void){
//  This function is buggy.
//  It gets the wrong bank for Kadabra (64), Tauros (128), and Sunflora (192).
//  Uncomment the line below to fix this.
    PUSH_HL;
    PUSH_DE;
    LD_A_addr(wEnemyMonSpecies);
// dec a
    RLCA;
    RLCA;
    maskbits(NUM_DEX_ENTRY_BANKS, 0);
    LD_HL(mGetPokedexEntryBank_PokedexEntryBanks);
    LD_D(0);
    LD_E_A;
    ADD_HL_DE;
    LD_A_hl;
    POP_DE;
    POP_HL;
    RET;


// PokedexEntryBanks:
    //db ['BANK("Pokedex Entries 001-064")'];
    //db ['BANK("Pokedex Entries 065-128")'];
    //db ['BANK("Pokedex Entries 129-192")'];
    //db ['BANK("Pokedex Entries 193-251")'];
}

//  subtract 20 from catch rate if weight < 102.4 kg
//  else add 0 to catch rate if weight < 204.8 kg
//  else add 20 to catch rate if weight < 307.2 kg
//  else add 30 to catch rate if weight < 409.6 kg
//  else add 40 to catch rate (never happens)
uint8_t HeavyBallMultiplier(uint8_t b){
    static const uint8_t WeightsTable[] = {
    //  weight factor, boost
        HIGH(2048), 0,
        HIGH(3072), 20,
        HIGH(4096), 30,
        HIGH(65280), 40,
    };
    // LD_A_addr(wEnemyMonSpecies);
    // LD_HL(mPokedexDataPointerTable);
    // DEC_A;
    // LD_E_A;
    // LD_D(0);
    // ADD_HL_DE;
    // ADD_HL_DE;
    // LD_A(BANK(aPokedexDataPointerTable));
    // CALL(aGetFarWord);
    const struct DexEntry* entry = PokedexDataPointerTable[wram->wEnemyMon.species - 1];

// SkipText:
    // CALL(aGetPokedexEntryBank);
    // CALL(aGetFarByte);
    // INC_HL;
    // CP_A(0x50);
    // IF_NZ goto SkipText;

    // CALL(aGetPokedexEntryBank);
    // PUSH_BC;
    // INC_HL;
    // INC_HL;
    // CALL(aGetFarWord);
    uint16_t weight = entry->weight;

    // SRL_H;
    // RR_L;
    // LD_B_H;
    // LD_C_L;

    // for(int rept = 0; rept < 4; rept++){
    // SRL_B;
    // RR_C;
    // }
    // CALL(aHeavyBallMultiplier_subbc);

    // SRL_B;
    // RR_C;
    // CALL(aHeavyBallMultiplier_subbc);

    // LD_A_H;
    // POP_BC;
    // goto compare;
    uint8_t h = weight >> 8;


// subbc:
// subtract bc from hl
    // PUSH_BC;
    // LD_A_B;
    // CPL;
    // LD_B_A;
    // LD_A_C;
    // CPL;
    // LD_C_A;
    // INC_BC;
    // ADD_HL_BC;
    // POP_BC;
    // RET;

// compare:
    // LD_C_A;
    // CP_A(HIGH(1024));  // 102.4 kg
    // IF_C goto lightmon;
    if(h < HIGH(1024)) {
    // lightmon:
        // LD_A_B;
        // SUB_A(20);
        // LD_B_A;
        // RET_NC ;
        if(b > 20)
            return b - 20;
        // LD_B(0x1);
        // RET;
        return 1;
    }

    // LD_HL(mHeavyBallMultiplier_WeightsTable);
    const uint8_t* hl = WeightsTable;

    while(*hl >= h) {
    // lookup:
        // LD_A_C;
        // CP_A_hl;
        // IF_C goto heavymon;
        // INC_HL;
        // INC_HL;
        // goto lookup;
        hl += 2;
    }

// heavymon:
    // INC_HL;
    hl++;
    // LD_A_B;
    // ADD_A_hl;
    // LD_B_A;
    // RET_NC ;
    if(h + *hl <= 0xff)
        return h + *hl;
    // LD_B(0xff);
    // RET;
    return 0xff;
}

//  multiply catch rate by 3 if this is a fishing rod battle
uint8_t LureBallMultiplier(uint8_t b){
    // LD_A_addr(wBattleType);
    // CP_A(BATTLETYPE_FISH);
    // RET_NZ ;
    if(wram->wBattleType != BATTLETYPE_FISH)
        return b;

    // LD_A_B;
    // ADD_A_A;
    // IF_C goto max;

    // ADD_A_B;
    // IF_NC goto done;
    if(b * 3 <= 0xff)
        return b * 3;

// max:
    // LD_A(0xff);

// done:
    // LD_B_A;
    // RET;
    return 0xff;
}

//  This function is buggy.
//  Intent:  multiply catch rate by 4 if mon evolves with moon stone
//  Reality: no boost
uint8_t MoonBallMultiplier(uint8_t b){
    // PUSH_BC;
    // LD_A_addr(wTempEnemyMonSpecies);
    // DEC_A;
    // LD_C_A;
    // LD_B(0);
    // LD_HL(mEvosAttacksPointers);
    // ADD_HL_BC;
    // ADD_HL_BC;
    // LD_A(BANK(aEvosAttacksPointers));
    // CALL(aGetFarWord);
    // POP_BC;
    const struct EvoData* evos = EvosAttacksPointers[wram->wTempMon.mon.species - 1]->evolutions;

    // Go through each evolution to see if any of them evolve through this method.
    while(evos->type != 0) {
        // PUSH_BC;
        // LD_A(BANK("Evolutions and Attacks"));
        // CALL(aGetFarByte);
        // CP_A(EVOLVE_ITEM);
        // POP_BC;
        // RET_NZ ;
        if(evos->type != EVOLVE_ITEM) {
            evos++;
            continue;
        }

        // INC_HL;
        // INC_HL;
        // INC_HL;

    //  Moon Stone's constant from Pokémon Red is used.
    //  No Pokémon evolve with Burn Heal,
    //  so Moon Balls always have a catch rate of 1×.
        // PUSH_BC;
        // LD_A(BANK("Evolutions and Attacks"));
        // CALL(aGetFarByte);
        // CP_A(MOON_STONE_RED);  // BURN_HEAL
        // POP_BC;
        // RET_NZ ;
#if BUGFIX_MOON_BALL_WRONG_ITEM
        if(evos->item.useItem != MOON_STONE)
#else
        if(evos->item.useItem != MOON_STONE_RED) // aka BURN_HEAL
#endif
        {
            evos++;
            continue;
        }
        // SLA_B;
        // IF_C goto max;
        // SLA_B;
        // IF_NC goto done;
        if(b * 4 <= 0xff)
            return b * 4;

    // max:
        // LD_B(0xff);

    // done:
        // RET;
        return 0xff;
    }
    return b;
}

//  This function is buggy.
//  Intent:  multiply catch rate by 8 if mons are of same species, different sex
//  Reality: multiply catch rate by 8 if mons are of same species, same sex
uint8_t LoveBallMultiplier(uint8_t b){
// does species match?
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_C_A;
    // LD_A_addr(wTempBattleMonSpecies);
    // CP_A_C;
    // RET_NZ ;
    if(wram->wTempEnemyMonSpecies != wram->wTempBattleMonSpecies)
        return b;

// check player mon species
    // PUSH_BC;
    // LD_A_addr(wTempBattleMonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wTempBattleMonSpecies;
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMonType);
    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wCurBattleMon;
    // FARCALL(aGetGender);
    u8_flag_s bgender = GetGender_Conv(PARTYMON);
    // IF_C goto done1;  // no effect on genderless
    if(bgender.flag)
        return b;

    // LD_D(0);  // male
    // IF_NZ goto playermale;
    // INC_D;  // female
    uint8_t d = (bgender.a == 0)? 1: 0;

// playermale:
// check wild mon species
    // PUSH_DE;
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = wram->wTempEnemyMonSpecies;
    // LD_A(WILDMON);
    // LD_addr_A(wMonType);
    // FARCALL(aGetGender);
    u8_flag_s wgender = GetGender_Conv(WILDMON);
    // IF_C goto done2;  // no effect on genderless
    if(wgender.flag)
        return b;

    // LD_D(0);  // male
    // IF_NZ goto wildmale;
    // INC_D;  // female
    uint8_t d2 = (wgender.a == 0)? 1: 0;

// wildmale:
    // LD_A_D;
    // POP_DE;
    // CP_A_D;
    // POP_BC;
    // RET_NZ ;  // for the intended effect, this should be "ret z"
#if BUGFIX_LOVE_BALL_SAME_GENDER
    if(d == d2)
#else
    if(d != d2)
#endif
        return b;

    // SLA_B;
    // IF_C goto max;
    // SLA_B;
    // IF_C goto max;
    // SLA_B;
    // RET_NC ;
    if(b * 8 <= 0xff)
        return b * 8;

// max:
    // LD_B(0xff);
    // RET;
    return 0xff;

// done2:
    // POP_DE;

// done1:
    // POP_BC;
    // RET;
}

//  This function is buggy.
//  Intent:  multiply catch rate by 4 if enemy mon is in one of the three
//           FleeMons tables.
//  Reality: multiply catch rate by 4 if enemy mon is one of the first three in
//           the first FleeMons table.
uint8_t FastBallMultiplier(uint8_t b){
    // LD_A_addr(wTempEnemyMonSpecies);
    // LD_C_A;
    species_t c = wram->wTempEnemyMonSpecies;
    // LD_HL(mFleeMons);
    const species_t** mons = FleeMons;
    const species_t* hl = *mons;
    // LD_D(3);
    uint8_t d = 3;

#if BUGFIX_FAST_BALL_INCOMPLETE_CHECK
    do {
        // LD_A(BANK(aFleeMons));
        // CALL(aGetFarByte);

        // INC_HL;
        // CP_A(-1);
        // IF_Z goto next;
        while(*hl != (species_t)-1) {
            // CP_A_C;
            // IF_NZ goto next;  // for the intended effect, this should be "jr nz, .loop"
            if(*hl != c) {
                hl++;
                continue;
            }
            // SLA_B;
            // IF_C goto max;
            if(b * 4 < 0xff)
                return b * 4;

            // SLA_B;
            // RET_NC ;

        // max:
            // LD_B(0xff);
            // RET;
            return 0xff;
        }

        mons++;
        hl = *mons;
    // next:
        // DEC_D;
        // IF_NZ goto loop;
    } while(--d != 0);
    // RET;
    return b;
#else
    do {
        // LD_A(BANK(aFleeMons));
        // CALL(aGetFarByte);

        // INC_HL;
        // CP_A(-1);
        // IF_Z goto next;
        if(*hl == (species_t)-1) {
            mons++;
            hl = *mons;
            continue;
        }

        // CP_A_C;
        // IF_NZ goto next;  // for the intended effect, this should be "jr nz, .loop"
        if(*hl != c) {
            hl++;
            continue;
        }
        // SLA_B;
        // IF_C goto max;
        if(b * 4 < 0xff)
            return b * 4;

        // SLA_B;
        // RET_NC ;

    // max:
        // LD_B(0xff);
        // RET;
        return 0xff;

    // next:
        // DEC_D;
        // IF_NZ goto loop;
    } while(--d != 0);
    // RET;
    return b;
#endif
}

//  multiply catch rate by 8 if player mon level / 4 > enemy mon level
//  multiply catch rate by 4 if player mon level / 2 > enemy mon level
//  multiply catch rate by 2 if player mon level > enemy mon level
uint8_t LevelBallMultiplier(uint8_t b){
    // LD_A_addr(wBattleMonLevel);
    // LD_C_A;
    uint8_t c = wram->wBattleMon.level;
    uint8_t e = wram->wEnemyMon.level;
    // LD_A_addr(wEnemyMonLevel);
    // CP_A_C;
    // RET_NC ;  // if player is lower level, we're done here
    if(c <= e)
        return b;
    uint16_t b2 = b << 1;
    // SLA_B;
    // IF_C goto max;
    if(b2 > 0xff)
        return 0xff;

    // SRL_C;
    // CP_A_C;
    // RET_NC ;  // if player/2 is lower level, we're done here
    if(c / 2 <= e)
        return (uint8_t)b2;
    // SLA_B;
    b2 <<= 1;
    // IF_C goto max;
    if(b2 > 0xff)
        return 0xff;

    // SRL_C;
    // CP_A_C;
    // RET_NC ;  // if player/4 is lower level, we're done here
    if(c / 4 <= e)
        return (uint8_t)b2;
    // SLA_B;
    b2 <<= 1;
    // RET_NC ;
    if(b2 <= 0xff)
        return (uint8_t)b2;

// max:
    // LD_B(0xff);
    // RET;
    return 0xff;
}

//  BallDodgedText and BallMissedText were used in Gen 1.
void BallDodgedText(void){
//  //  unreferenced
    //text_far ['_BallDodgedText']
    //text_end ['?']

    return BallMissedText();
}

void BallMissedText(void){
//  //  unreferenced
    //text_far ['_BallMissedText']
    //text_end ['?']
}

const txt_cmd_s BallBrokeFreeText[] = {
    text_far(v_BallBrokeFreeText)
    text_end
};

const txt_cmd_s BallAppearedCaughtText[] = {
    text_far(v_BallAppearedCaughtText)
    text_end
};

const txt_cmd_s BallAlmostHadItText[] = {
    text_far(v_BallAlmostHadItText)
    text_end
};

const txt_cmd_s BallSoCloseText[] = {
    text_far(v_BallSoCloseText)
    text_end
};

static void Text_GotchaMonWasCaught_Function(struct TextCmdState* state){
    // CALL(aWaitSFX);
    WaitSFX();
    // PUSH_BC;
    // LD_DE(MUSIC_NONE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_NONE);
    // CALL(aDelayFrame);
    DelayFrame();
    // LD_DE(MUSIC_CAPTURE);
    // CALL(aPlayMusic);
    PlayMusic(MUSIC_CAPTURE);
    // POP_BC;
    // LD_HL(mWaitButtonText);
    state->hl = WaitButtonText;
    // RET;
}

const txt_cmd_s Text_GotchaMonWasCaught[] = {
// Gotcha! @ was caught!@ @
    text_far(v_Text_BallCaught)
    text_asm(Text_GotchaMonWasCaught_Function)
};

const txt_cmd_s WaitButtonText[] = {
    text_far(v_WaitButtonText)
    text_end
};

const txt_cmd_s BallSentToPCText[] = {
    text_far(v_BallSentToPCText)
    text_end
};

const txt_cmd_s NewDexDataText[] = {
    text_far(v_NewDexDataText)
    text_end
};

const txt_cmd_s AskGiveNicknameText[] = {
    text_far(v_AskGiveNicknameText)
    text_end
};

void ReturnToBattle_UseBall(void){
    // FARCALL(av_ReturnToBattle_UseBall);
    // RET;
    return v_ReturnToBattle_UseBall();
}

void TownMapEffect(void){
    FARCALL(aPokegearMap);
    RET;

}

void BicycleEffect(void){
    // FARCALL(aBikeFunction);
    // RET;
    return BikeFunction();
}

void EvoStoneEffect(void){
    // LD_B(PARTYMENUACTION_EVO_STONE);
    // CALL(aUseItem_SelectMon);
    bool cancel = UseItem_SelectMon(PARTYMENUACTION_EVO_STONE);

    // JP_C (mEvoStoneEffect_DecidedNotToUse);
    if(cancel) {
    // DecidedNotToUse:
        // XOR_A_A;
        // LD_addr_A(wItemEffectSucceeded);
        wram->wItemEffectSucceeded = FALSE;
        // RET;
        return;
    }

    // LD_A(MON_ITEM);
    // CALL(aGetPartyParamLocation);
    struct PartyMon* mon = wram->wPartyMon + wram->wCurPartyMon;

    // LD_A_hl;
    // CP_A(EVERSTONE);
    // IF_Z goto NoEffect;
    if(mon->mon.item != EVERSTONE) {
        // LD_A(TRUE);
        // LD_addr_A(wForceEvolution);
        wram->wForceEvolution = TRUE;
        // FARCALL(aEvolvePokemon);
        EvolvePokemon();

        // LD_A_addr(wMonTriedToEvolve);
        // AND_A_A;
        // IF_Z goto NoEffect;
        if(wram->wMonTriedToEvolve) {
            // JP(mUseDisposableItem);
            return UseDisposableItem();
        }
    }

// NoEffect:
    // CALL(aWontHaveAnyEffectMessage);
    WontHaveAnyEffectMessage();

// DecidedNotToUse:
    // XOR_A_A;
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = FALSE;
    // RET;
}

void VitaminEffect(void){
    // LD_B(PARTYMENUACTION_HEALING_ITEM);
    // CALL(aUseItem_SelectMon);
    bool cancel = UseItem_SelectMon(PARTYMENUACTION_HEALING_ITEM);

    // JP_C (mRareCandy_StatBooster_ExitMenu);
    if(cancel)
        return RareCandy_StatBooster_ExitMenu();

    // CALL(aRareCandy_StatBooster_GetParameters);
    RareCandy_StatBooster_GetParameters();

    // CALL(aGetStatExpRelativePointer);
    uint8_t stat = GetStatExpRelativePointer();

    // LD_A(MON_STAT_EXP);
    // CALL(aGetPartyParamLocation);
    struct PartyMon* mon = wram->wPartyMon + wram->wCurPartyMon;

    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(100);
    // JR_NC (mNoEffectMessage);
    if(mon->mon.statExp[stat] >= 100)
        return NoEffectMessage();

    // ADD_A(10);
    // LD_hl_A;
    mon->mon.statExp[stat] += 10;
    // CALL(aUpdateStatsAfterItem);
    UpdateStatsAfterItem(mon);

    // CALL(aGetStatExpRelativePointer);

    // LD_HL(mStatStrings);
    // ADD_HL_BC;
    // LD_A_hli;
    // LD_H_hl;
    // LD_L_A;
    // LD_DE(wStringBuffer2);
    // LD_BC(ITEM_NAME_LENGTH);
    // CALL(aCopyBytes);
    U82CB(wram->wStringBuffer2, ITEM_NAME_LENGTH, StatStrings[stat]);

    // CALL(aPlay_SFX_FULL_HEAL);
    Play_SFX_FULL_HEAL();

    // LD_HL(mItemStatRoseText);
    // CALL(aPrintText);
    PrintText_Conv2(ItemStatRoseText);

    // LD_C(HAPPINESS_USEDITEM);
    // FARCALL(aChangeHappiness);
    ChangeHappiness_Conv(HAPPINESS_USEDITEM);

    // JP(mUseDisposableItem);
    UseDisposableItem();
}

void NoEffectMessage(void){
    // LD_HL(mItemWontHaveEffectText);
    // CALL(aPrintText);
    PrintText_Conv2(ItemWontHaveEffectText);
    // JP(mClearPalettes);
    ClearPalettes_Conv();
}

void UpdateStatsAfterItem(struct PartyMon* hl){
    // LD_A(MON_MAXHP);
    // CALL(aGetPartyParamLocation);
    // LD_D_H;
    // LD_E_L;
    // LD_A(MON_STAT_EXP - 1);
    // CALL(aGetPartyParamLocation);
    // LD_B(TRUE);
    // PREDEF_JUMP(pCalcMonStats);
    CalcMonStats_PartyMon(hl, TRUE);
}

void RareCandy_StatBooster_ExitMenu(void){
    // XOR_A_A;
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = FALSE;
    // JP(mClearPalettes);
    return ClearPalettes_Conv();
}

const txt_cmd_s ItemStatRoseText[] = {
    text_far(v_ItemStatRoseText)
    text_end
};

const char* StatStrings[] = {
    //dw ['.health'];
// health:
    "HEALTH@",
    //dw ['.attack'];
// attack:
    "ATTACK@",
    //dw ['.defense'];
// defense:
    "DEFENSE@",
    //dw ['.speed'];
// speed:
    "SPEED@",
    //dw ['.special'];
// special:
    "SPECIAL@",
};

uint8_t GetStatExpRelativePointer(void){
    static const struct ItemStat {
        item_t item;
        uint8_t stat;
    } StatExpItemPointerOffsets[] = {
        {HP_UP,     (MON_HP_EXP  - MON_STAT_EXP) / 2},
        {PROTEIN,   (MON_ATK_EXP - MON_STAT_EXP) / 2},
        {IRON,      (MON_DEF_EXP - MON_STAT_EXP) / 2},
        {CARBOS,    (MON_SPD_EXP - MON_STAT_EXP) / 2},
        {CALCIUM,   (MON_SPC_EXP - MON_STAT_EXP) / 2},
    };
    // LD_A_addr(wCurItem);
    item_t item = wram->wCurItem;
    // LD_HL(mStatExpItemPointerOffsets);
    const struct ItemStat* istat = StatExpItemPointerOffsets;

    while(istat->item != item) {
    // next:
        // CP_A_hl;
        // INC_HL;
        // IF_Z goto got_it;
        // INC_HL;
        // goto next;
        istat++;
    }


// got_it:
    // LD_A_hl;
    // LD_C_A;
    // LD_B(0);
    // RET;
    return istat->stat;
}

void RareCandy_StatBooster_GetParameters(void){
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wCurSpecies);
    // LD_addr_A(wTempSpecies);
    wram->wCurSpecies = wram->wCurPartySpecies;
    // LD_A(MON_LEVEL);
    // CALL(aGetPartyParamLocation);
    struct PartyMon* hl = wram->wPartyMon + wram->wCurPartyMon;
    // LD_A_hl;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = hl->mon.level;
    // CALL(aGetBaseData);
    GetBaseData_Conv2(wram->wCurPartySpecies);
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMonNicknames);
    // CALL(aGetNickname);
    GetCurNickname_Conv();
    // RET;
}

void RareCandyEffect(void){
    // LD_B(PARTYMENUACTION_HEALING_ITEM);
    // CALL(aUseItem_SelectMon);
    bool cancel = UseItem_SelectMon(PARTYMENUACTION_HEALING_ITEM);

    // JP_C (mRareCandy_StatBooster_ExitMenu);
    if(cancel)
        return RareCandy_StatBooster_ExitMenu();

    // CALL(aRareCandy_StatBooster_GetParameters);
    RareCandy_StatBooster_GetParameters();

    // LD_A(MON_LEVEL);
    // CALL(aGetPartyParamLocation);
    struct PartyMon* hl = wram->wPartyMon + wram->wCurPartyMon;

    // LD_A_hl;
    // CP_A(MAX_LEVEL);
    // JP_NC (mNoEffectMessage);
    if(hl->mon.level >= MAX_LEVEL)
        return NoEffectMessage();

    // INC_A;
    // LD_hl_A;
    // LD_addr_A(wCurPartyLevel);
    wram->wCurPartyLevel = ++hl->mon.level;
    // PUSH_DE;
    // LD_D_A;
    // FARCALL(aCalcExpAtLevel);
    uint32_t exp = CalcExpAtLevel_Conv(wram->wCurPartyLevel);

    // POP_DE;
    // LD_A(MON_EXP);
    // CALL(aGetPartyParamLocation);

    // LDH_A_addr(hMultiplicand + 0);
    // LD_hli_A;
    hl->mon.exp[0] = HIGH(exp >> 8);
    // LDH_A_addr(hMultiplicand + 1);
    // LD_hli_A;
    hl->mon.exp[1] = HIGH(exp);
    // LDH_A_addr(hMultiplicand + 2);
    // LD_hl_A;
    hl->mon.exp[2] = LOW(exp);

    // LD_A(MON_MAXHP);
    // CALL(aGetPartyParamLocation);
    // LD_A_hli;
    // LD_B_A;
    // LD_C_hl;
    uint16_t maxHP = BigEndianToNative16(hl->maxHP);
    // PUSH_BC;
    // CALL(aUpdateStatsAfterItem);
    UpdateStatsAfterItem(hl);

    // LD_A(MON_MAXHP + 1);
    // CALL(aGetPartyParamLocation);

    // POP_BC;
    // LD_A_hld;
    // SUB_A_C;
    // LD_C_A;
    // LD_A_hl;
    // SBC_A_B;
    // LD_B_A;
    uint16_t bc = BigEndianToNative16(hl->maxHP) - maxHP;
    // DEC_HL;
    // LD_A_hl;
    // ADD_A_C;
    // LD_hld_A;
    uint16_t new_hp = BigEndianToNative16(hl->HP) + bc;
    // LD_A_hl;
    // ADC_A_B;
    // LD_hl_A;
    hl->HP = NativeToBigEndian16(new_hp);
    // FARCALL(aLevelUpHappinessMod);
    LevelUpHappinessMod();

    // LD_A(PARTYMENUTEXT_LEVEL_UP);
    // CALL(aItemActionText);
    ItemActionText(PARTYMENUTEXT_LEVEL_UP);

    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // PREDEF(pCopyMonToTempMon);
    CopyMonToTempMon_Conv();

    // hlcoord(9, 0, wTilemap);
    // LD_B(10);
    // LD_C(9);
    // CALL(aTextbox);
    Textbox_Conv2(coord(9, 0, wram->wTilemap), 10, 9);

    // hlcoord(11, 1, wTilemap);
    // LD_BC(4);
    // PREDEF(pPrintTempMonStats);
    PrintTempMonStats_Conv(coord(11, 1, wram->wTilemap), 4);

    // CALL(aWaitPressAorB_BlinkCursor);
    WaitPressAorB_BlinkCursor_Conv();

    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMonType);
    wram->wMonType = PARTYMON;
    // LD_A_addr(wCurPartySpecies);
    // LD_addr_A(wTempSpecies);
    // PREDEF(pLearnLevelMoves);
    LearnLevelMoves_Conv(hl, wram->wCurPartyLevel, wram->wCurPartySpecies);

    // XOR_A_A;
    // LD_addr_A(wForceEvolution);
    wram->wForceEvolution = FALSE;
    // FARCALL(aEvolvePokemon);
    EvolvePokemon();

    // JP(mUseDisposableItem);
    return UseDisposableItem();
}

void HealPowderEffect(void){
    // LD_B(PARTYMENUACTION_HEALING_ITEM);
    // CALL(aUseItem_SelectMon);
    bool cancel = UseItem_SelectMon(PARTYMENUACTION_HEALING_ITEM);

    // JP_C (mStatusHealer_ExitMenu);
    if(cancel)
        return StatusHealer_ExitMenu();

    // CALL(aUseStatusHealer);
    uint8_t res = UseStatusHealer();
    // CP_A(FALSE);
    // IF_NZ goto not_used;
    if(res == FALSE) {
        // LD_C(HAPPINESS_BITTERPOWDER);
        // FARCALL(aChangeHappiness);
        ChangeHappiness_Conv(HAPPINESS_BITTERPOWDER);
        // CALL(aLooksBitterMessage);
        LooksBitterMessage();

        // LD_A(0x0); // FALSE is already 0
    }

// not_used:
    // JP(mStatusHealer_Jumptable);
    return StatusHealer_Jumptable(res);
}

void StatusHealingEffect(void){
    // LD_B(PARTYMENUACTION_HEALING_ITEM);
    // CALL(aUseItem_SelectMon);
    bool cancel = UseItem_SelectMon(PARTYMENUACTION_HEALING_ITEM);
    // JP_C (mStatusHealer_ExitMenu);
    if(cancel)
        return StatusHealer_ExitMenu();

    return FullyHealStatus();
}

void FullyHealStatus(void){
    // CALL(aUseStatusHealer);
    // JP(mStatusHealer_Jumptable);
    return StatusHealer_Jumptable(UseStatusHealer());
}

uint8_t UseStatusHealer(void){
    struct PartyMon* curMon = wram->wPartyMon + wram->wCurPartyMon;
    // CALL(aIsMonFainted);
    // LD_A(TRUE);
    // RET_Z ;
    if(IsMonFainted(curMon))
        return TRUE;
    // CALL(aGetItemHealingAction);
    uint16_t action = GetItemHealingAction(wram->wCurItem);
    uint8_t text = HIGH(action);
    uint8_t c = LOW(action);
    // LD_A(MON_STATUS);
    // CALL(aGetPartyParamLocation);
    // LD_A_hl;
    // AND_A_C;
    // IF_NZ goto good;
    if((curMon->status & c) == 0) {
        // CALL(aIsItemUsedOnConfusedMon);
        // LD_A(TRUE);
        // RET_NC ;
        if(!IsItemUsedOnConfusedMon(c))
            return TRUE;
        // LD_B(PARTYMENUTEXT_HEAL_CONFUSION);
        text = PARTYMENUTEXT_HEAL_CONFUSION;
    }

// good:
    // XOR_A_A;
    // LD_hl_A;
    curMon->status = 0x0;
    // LD_A_B;
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = text;
    // CALL(aHealStatus);
    HealStatus(c);
    // CALL(aPlay_SFX_FULL_HEAL);
    Play_SFX_FULL_HEAL();
    // CALL(aItemActionTextWaitButton);
    ItemActionTextWaitButton();
    // CALL(aUseDisposableItem);
    UseDisposableItem();
    // LD_A(FALSE);
    // RET;
    return FALSE;
}

bool IsItemUsedOnConfusedMon(uint8_t c){
    // CALL(aIsItemUsedOnBattleMon);
    // IF_NC goto nope;
    if(!IsItemUsedOnBattleMon())
        return false;
    // LD_A_addr(wPlayerSubStatus3);
    // BIT_A(SUBSTATUS_CONFUSED);
    // IF_Z goto nope;
    if(!bit_test(wram->wPlayerSubStatus3, SUBSTATUS_CONFUSED))
        return false;
    // LD_A_C;
    // CP_A(0xff);
    // IF_NZ goto nope;
    // SCF;
    // RET;
    return c == 0xff;

// nope:
    // AND_A_A;
    // RET;
}

void BattlemonRestoreHealth(uint16_t hp){
    // CALL(aIsItemUsedOnBattleMon);
    // RET_NC ;
    if(!IsItemUsedOnBattleMon())
        return;
    // LD_A(MON_HP);
    // CALL(aGetPartyParamLocation);
    // LD_A_hli;
    // LD_addr_A(wBattleMonHP);
    // LD_A_hld;
    // LD_addr_A(wBattleMonHP + 1);
    wram->wBattleMon.hp = NativeToBigEndian16(hp);
    // RET;
}

void HealStatus(uint8_t c){
    // CALL(aIsItemUsedOnBattleMon);
    // RET_NC ;
    if(!IsItemUsedOnBattleMon())
        return;
    // XOR_A_A;
    // LD_addr_A(wBattleMonStatus);
    wram->wBattleMon.status[0] = 0;
    // LD_HL(wPlayerSubStatus5);
    // RES_hl(SUBSTATUS_TOXIC);
    bit_reset(wram->wPlayerSubStatus5, SUBSTATUS_TOXIC);
    // LD_HL(wPlayerSubStatus1);
    // RES_hl(SUBSTATUS_NIGHTMARE);
    bit_reset(wram->wPlayerSubStatus1, SUBSTATUS_NIGHTMARE);
    // CALL(aGetItemHealingAction);
    // LD_A_C;
    // CP_A(0b11111111);
    // IF_NZ goto not_full_heal;
    if(c == 0b11111111) {
        // LD_HL(wPlayerSubStatus3);
        // RES_hl(SUBSTATUS_CONFUSED);
        bit_reset(wram->wPlayerSubStatus3, SUBSTATUS_CONFUSED);
    }

// not_full_heal:
    // PUSH_BC;
    // FARCALL(aCalcPlayerStats);
    CalcPlayerStats();
    // POP_BC;
    // RET;
}

uint16_t GetItemHealingAction(item_t item){
    // PUSH_HL;
    // LD_A_addr(wCurItem);
    // LD_HL(mStatusHealingActions);
    const struct HealingAction* hl = StatusHealingActions;
    // LD_BC(3);

    while(hl->item != item) {
    // next:
        // CP_A_hl;
        // IF_Z goto found_it;
        // ADD_HL_BC;
        hl++;
        // goto next;
    }

// found_it:
    // INC_HL;
    // LD_B_hl;
    // INC_HL;
    // LD_A_hl;
    // LD_C_A;
    // CP_A(0b11111111);
    // POP_HL;
    // RET;

// INCLUDE "data/items/heal_status.asm"
    return (hl->action_text << 8) | hl->status;
}

void StatusHealer_Jumptable(uint8_t a){
    // LD_HL(mStatusHealer_Jumptable_dw);
    // RST(aJumpTable);
    // RET;


// dw:
    switch(a) {
        case 0: return StatusHealer_ClearPalettes();
        case 1: return StatusHealer_NoEffect();
        case 2: return StatusHealer_ExitMenu();
    }
}

void RevivalHerbEffect(void){
    // LD_B(PARTYMENUACTION_HEALING_ITEM);
    // CALL(aUseItem_SelectMon);
    bool cancel = UseItem_SelectMon(PARTYMENUACTION_HEALING_ITEM);
    // JP_C (mStatusHealer_ExitMenu);
    if(cancel)
        return StatusHealer_ExitMenu();

    // CALL(aRevivePokemon);
    uint8_t res = RevivePokemon();
    // CP_A(FALSE);
    // IF_NZ goto not_used;
    if(res == FALSE) {
        // LD_C(HAPPINESS_REVIVALHERB);
        // FARCALL(aChangeHappiness);
        ChangeHappiness_Conv(HAPPINESS_REVIVALHERB);
        // CALL(aLooksBitterMessage);
        LooksBitterMessage();

        // LD_A(0x0); // FALSE is already 0
    }

// not_used:
    // JP(mStatusHealer_Jumptable);
    return StatusHealer_Jumptable(res);
}

void ReviveEffect(void){
    // LD_B(PARTYMENUACTION_HEALING_ITEM);
    // CALL(aUseItem_SelectMon);
    bool cancel = UseItem_SelectMon(PARTYMENUACTION_HEALING_ITEM);
    // JP_C (mStatusHealer_ExitMenu);
    if(cancel)
        return StatusHealer_ExitMenu();

    // CALL(aRevivePokemon);
    // JP(mStatusHealer_Jumptable);
    return StatusHealer_Jumptable(RevivePokemon());
}

uint8_t RevivePokemon(void){
    struct PartyMon* curMon = wram->wPartyMon + wram->wCurPartyMon;
    // CALL(aIsMonFainted);
    // LD_A(TRUE);
    // RET_NZ ;
    if(!IsMonFainted(curMon))
        return TRUE;
    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // IF_Z goto skip_to_revive;

    if(wram->wBattleMode != 0) {
        // LD_A_addr(wCurPartyMon);
        // LD_C_A;
        // LD_D(0);
        // LD_HL(wBattleParticipantsIncludingFainted);
        // LD_B(CHECK_FLAG);
        // PREDEF(pSmallFarFlagAction);
        // LD_A_C;
        // AND_A_A;
        // IF_Z goto skip_to_revive;

        if(SmallFarFlagAction_Conv(&wram->wBattleParticipantsIncludingFainted, wram->wCurPartyMon, CHECK_FLAG)) {
            // LD_A_addr(wCurPartyMon);
            // LD_C_A;
            // LD_HL(wBattleParticipantsNotFainted);
            // LD_B(SET_FLAG);
            // PREDEF(pSmallFarFlagAction);
            SmallFarFlagAction_Conv(&wram->wBattleParticipantsNotFainted, wram->wCurPartyMon, SET_FLAG);
        }
    }

// skip_to_revive:
    // XOR_A_A;
    // LD_addr_A(wLowHealthAlarm);
    wram->wLowHealthAlarm = 0x0;
    // LD_A_addr(wCurItem);
    // CP_A(REVIVE);
    // IF_Z goto revive_half_hp;
    if(wram->wCurItem == REVIVE) {
    // revive_half_hp:
        // CALL(aReviveHalfHP);
        ReviveHalfHP(curMon);
    }
    else {
        // CALL(aReviveFullHP);
        // goto finish_revive;
        ReviveFullHP(curMon);
    }

// finish_revive:
    // CALL(aHealHP_SFX_GFX);
    HealHP_SFX_GFX();
    // LD_A(PARTYMENUTEXT_REVIVE);
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = PARTYMENUTEXT_REVIVE;
    // CALL(aItemActionTextWaitButton);
    ItemActionTextWaitButton();
    // CALL(aUseDisposableItem);
    UseDisposableItem();
    // LD_A(FALSE);
    // RET;
    return FALSE;
}

static uint8_t FullRestoreEffect_FullRestore(void){
    struct PartyMon* curMon = wram->wPartyMon + wram->wCurPartyMon;
    // XOR_A_A;
    // LD_addr_A(wLowHealthAlarm);
    wram->wLowHealthAlarm = 0x0;
    // CALL(aReviveFullHP);
    uint16_t hp = ReviveFullHP(curMon);
    // LD_A(MON_STATUS);
    // CALL(aGetPartyParamLocation);
    // XOR_A_A;
    // LD_hli_A;
    // LD_hl_A;
    curMon->status = 0;
    curMon->unused = 0;
    // CALL(aHealStatus);
    HealStatus(0b11111111);
    // CALL(aBattlemonRestoreHealth);
    BattlemonRestoreHealth(hp);
    // CALL(aHealHP_SFX_GFX);
    HealHP_SFX_GFX();
    // LD_A(PARTYMENUTEXT_HEAL_HP);
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = PARTYMENUTEXT_HEAL_HP;
    // CALL(aItemActionTextWaitButton);
    ItemActionTextWaitButton();
    // CALL(aUseDisposableItem);
    UseDisposableItem();
    // LD_A(0);
    // RET;
    return 0;
}

void FullRestoreEffect(void){
    // LD_B(PARTYMENUACTION_HEALING_ITEM);
    // CALL(aUseItem_SelectMon);
    bool cancel = UseItem_SelectMon(PARTYMENUACTION_HEALING_ITEM);
    // JP_C (mStatusHealer_ExitMenu);
    if(cancel)
        return StatusHealer_ExitMenu();

    struct PartyMon* curMon = wram->wPartyMon + wram->wCurPartyMon;
    // CALL(aIsMonFainted);
    // JP_Z (mStatusHealer_NoEffect);
    if(IsMonFainted(curMon))
        return StatusHealer_NoEffect();

    // CALL(aIsMonAtFullHealth);
    // IF_C goto NotAtFullHealth;
    if(IsMonAtFullHealth(curMon)) {
        // JP(mFullyHealStatus);
        return FullyHealStatus();
    }

// NotAtFullHealth:
    // CALL(aFullRestoreEffect_FullRestore);
    // JP(mStatusHealer_Jumptable);
    return StatusHealer_Jumptable(FullRestoreEffect_FullRestore());
}

void BitterBerryEffect(void){
    // LD_HL(wPlayerSubStatus3);
    // BIT_hl(SUBSTATUS_CONFUSED);
    // LD_A(1);
    // IF_Z goto done;
    if(!bit_test(wram->wPlayerSubStatus3, SUBSTATUS_CONFUSED))
        return StatusHealer_Jumptable(1);

    // RES_hl(SUBSTATUS_CONFUSED);
    // XOR_A_A;
    // LDH_addr_A(hBattleTurn);
    // CALL(aUseItemText);
    UseItemText();

    // LD_HL(mConfusedNoMoreText);
    // CALL(aStdBattleTextbox);
    StdBattleTextbox(ConfusedNoMoreText);

    // LD_A(0);

// done:
    // JP(mStatusHealer_Jumptable);
    return StatusHealer_Jumptable(0);
}

void RestoreHPEffect(void){
    // CALL(aItemRestoreHP);
    // JP(mStatusHealer_Jumptable);
    return StatusHealer_Jumptable(ItemRestoreHP());
}

void EnergypowderEffect(void){
    // LD_C(HAPPINESS_BITTERPOWDER);
    // JR(mEnergypowderEnergyRootCommon);
    return EnergypowderEnergyRootCommon(HAPPINESS_BITTERPOWDER);
}

void EnergyRootEffect(void){
    // LD_C(HAPPINESS_ENERGYROOT);
    return EnergypowderEnergyRootCommon(HAPPINESS_ENERGYROOT);
}

void EnergypowderEnergyRootCommon(uint8_t c){
    // PUSH_BC;
    // CALL(aItemRestoreHP);
    uint8_t res = ItemRestoreHP();
    // POP_BC;
    // CP_A(0);
    // IF_NZ goto skip_happiness;
    if(res == 0) {
        // FARCALL(aChangeHappiness);
        ChangeHappiness_Conv(c);
        // CALL(aLooksBitterMessage);
        LooksBitterMessage();
        // LD_A(0);
    }

// skip_happiness:
    // JP(mStatusHealer_Jumptable);
    return StatusHealer_Jumptable(res);
}

uint8_t ItemRestoreHP(void){
    // LD_B(PARTYMENUACTION_HEALING_ITEM);
    // CALL(aUseItem_SelectMon);
    bool cancel = UseItem_SelectMon(PARTYMENUACTION_HEALING_ITEM);
    // LD_A(2);
    // RET_C ;
    if(cancel)
        return 2;

    struct PartyMon* curMon = wram->wPartyMon + wram->wCurPartyMon;
    // CALL(aIsMonFainted);
    // LD_A(1);
    // RET_Z ;

    // CALL(aIsMonAtFullHealth);
    // LD_A(1);
    // RET_NC ;
    if(IsMonFainted(curMon) || IsMonAtFullHealth(curMon))
        return 1;

    // XOR_A_A;
    // LD_addr_A(wLowHealthAlarm);
    wram->wLowHealthAlarm = 0x0;
    // CALL(aGetHealingItemAmount);
    uint16_t amount = GetHealingItemAmount(wram->wCurItem);
    // CALL(aRestoreHealth);
    amount = RestoreHealth_Conv(curMon, amount);
    // CALL(aBattlemonRestoreHealth);
    BattlemonRestoreHealth(amount);
    // CALL(aHealHP_SFX_GFX);
    HealHP_SFX_GFX();
    // LD_A(PARTYMENUTEXT_HEAL_HP);
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = PARTYMENUTEXT_HEAL_HP;
    // CALL(aItemActionTextWaitButton);
    ItemActionTextWaitButton();
    // CALL(aUseDisposableItem);
    UseDisposableItem();
    // LD_A(0);
    // RET;
    return 0;
}

void HealHP_SFX_GFX(void){
    // PUSH_DE;
    // LD_DE(SFX_POTION);
    // CALL(aWaitPlaySFX);
    WaitPlaySFX(SFX_POTION);
    // POP_DE;
    // LD_A_addr(wCurPartyMon);
    // hlcoord(11, 0, wTilemap);
    // LD_BC(SCREEN_WIDTH * 2);
    // CALL(aAddNTimes);
    // LD_A(0x2);
    // LD_addr_A(wWhichHPBar);
    // PREDEF_JUMP(pAnimateHPBar);
    AnimateHPBar_Conv(coord(11, 0, wram->wTilemap) + wram->wCurPartyMon * SCREEN_WIDTH * 2, 0x2);
}

static u8_flag_s UseItem_SelectMon_SelectMon(uint8_t b) {
    // LD_A_B;
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = b;
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // CALL(aClearBGPalettes);
    ClearBGPalettes_Conv();
    // CALL(aChooseMonToUseItemOn);
    return ChooseMonToUseItemOn();
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // RET;
}

bool UseItem_SelectMon(uint8_t b){
    // CALL(aUseItem_SelectMon_SelectMon);
    u8_flag_s res = UseItem_SelectMon_SelectMon(b);
    // RET_C ;
    if(res.flag)
        return true;

    // LD_A_addr(wCurPartySpecies);
    // CP_A(EGG);
    // IF_NZ goto not_egg;
    if(wram->wCurPartySpecies == EGG) {
        // CALL(aCantUseOnEggMessage);
        CantUseOnEggMessage();
        // SCF;
        // RET;
        return true;
    }

// not_egg:
    // AND_A_A;
    // RET;
    return false;
}

u8_flag_s ChooseMonToUseItemOn(void){
    // FARCALL(aLoadPartyMenuGFX);
    LoadPartyMenuGFX();
    // FARCALL(aInitPartyMenuWithCancel);
    InitPartyMenuWithCancel();
    // FARCALL(aInitPartyMenuGFX);
    InitPartyMenuGFX();
    // FARCALL(aWritePartyMenuTilemap);
    WritePartyMenuTilemap();
    // FARCALL(aPrintPartyMenuText);
    PrintPartyMenuText();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // FARCALL(aPartyMenuSelect);
    // RET;
    return PartyMenuSelect();
}

void ItemActionText(uint8_t text){
    // LD_addr_A(wPartyMenuActionText);
    wram->wPartyMenuActionText = text;
    // LD_A_addr(wCurPartySpecies);
    // PUSH_AF;
    species_t curPartySpecies = wram->wCurPartySpecies;
    // LD_A_addr(wCurPartyMon);
    // PUSH_AF;
    uint8_t curPartyMon = wram->wCurPartyMon;
    // PUSH_HL;
    // PUSH_DE;
    // PUSH_BC;
    // FARCALL(aWritePartyMenuTilemap);
    WritePartyMenuTilemap();
    // FARCALL(aPrintPartyMenuActionText);
    PrintPartyMenuActionText();
    // CALL(aWaitBGMap);
    WaitBGMap_Conv();
    // CALL(aSetPalettes);
    SetPalettes_Conv();
    // CALL(aDelayFrame);
    DelayFrame();
    // POP_BC;
    // POP_DE;
    // POP_HL;
    // POP_AF;
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = curPartyMon;
    // POP_AF;
    // LD_addr_A(wCurPartySpecies);
    wram->wCurPartySpecies = curPartySpecies;
    // RET;
}

void ItemActionTextWaitButton(void){
    // XOR_A_A;
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_NONE;
    // hlcoord(0, 0, wTilemap);
    // LD_BC(wTilemapEnd - wTilemap);
    // LD_A(0x7f);
    // CALL(aByteFill);
    ByteFill(coord(0, 0, wram->wTilemap), sizeof(wram->wTilemap), 0x7f);
    // LD_A_addr(wPartyMenuActionText);
    // CALL(aItemActionText);
    ItemActionText(wram->wPartyMenuActionText);
    // LD_A(0x1);
    // LDH_addr_A(hBGMapMode);
    hram->hBGMapMode = BGMAPMODE_UPDATE_TILES;
    // LD_C(50);
    // CALL(aDelayFrames);
    DelayFrames(50);
    // JP(mWaitPressAorB_BlinkCursor);
    return WaitPressAorB_BlinkCursor_Conv();
}

void StatusHealer_NoEffect(void){
    // CALL(aWontHaveAnyEffectMessage);
    WontHaveAnyEffectMessage();
    // JR(mStatusHealer_ClearPalettes);
    return StatusHealer_ClearPalettes();
}

void StatusHealer_ExitMenu(void){
    // XOR_A_A;
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = FALSE;
    return StatusHealer_ClearPalettes();
}

void StatusHealer_ClearPalettes(void){
    // CALL(aClearPalettes);
    ClearPalettes_Conv();
    // RET;
}

bool IsItemUsedOnBattleMon(void){
    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // RET_Z ;
    if(wram->wBattleMode == 0)
        return false;
    // LD_A_addr(wCurPartyMon);
    // PUSH_HL;
    // LD_HL(wCurBattleMon);
    // CP_A_hl;
    // POP_HL;
    // IF_NZ goto nope;
    // SCF;
    // RET;

// nope:
    // XOR_A_A;
    // RET;
    return wram->wCurPartyMon == wram->wCurBattleMon;
}

uint16_t ReviveHalfHP(struct PartyMon* bc){
    // CALL(aLoadHPFromBuffer1);
    // SRL_D;
    // RR_E;
    // JR(mContinueRevive);
    return ContinueRevive(bc, BigEndianToNative16(bc->maxHP) / 2);
}

uint16_t ReviveFullHP(struct PartyMon* bc){
    // CALL(aLoadHPFromBuffer1);
    return ContinueRevive(bc, BigEndianToNative16(bc->maxHP));
}

uint16_t ContinueRevive(struct PartyMon* bc, uint16_t hp){
    // LD_A(MON_HP);
    // CALL(aGetPartyParamLocation);
    // LD_hl_D;
    // INC_HL;
    // LD_hl_E;
    // JP(mLoadCurHPIntoBuffer3);
    bc->HP = NativeToBigEndian16(hp);
    wram->wHPBuffer3 = hp;
    return hp;
}

void RestoreHealth(void){
    LD_A(MON_HP + 1);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    ADD_A_E;
    LD_hld_A;
    LD_A_hl;
    ADC_A_D;
    LD_hl_A;
    IF_C goto full_hp;
    CALL(aLoadCurHPIntoBuffer3);
    LD_A(MON_HP + 1);
    CALL(aGetPartyParamLocation);
    LD_D_H;
    LD_E_L;
    LD_A(MON_MAXHP + 1);
    CALL(aGetPartyParamLocation);
    LD_A_de;
    SUB_A_hl;
    DEC_DE;
    DEC_HL;
    LD_A_de;
    SBC_A_hl;
    IF_C goto finish;

full_hp:
    CALL(aReviveFullHP);

finish:
    RET;

}

uint16_t RestoreHealth_Conv(struct PartyMon* bc, uint16_t amount){
    // LD_A(MON_HP + 1);
    // CALL(aGetPartyParamLocation);
    uint16_t hp = BigEndianToNative16(bc->HP);
    // LD_A_hl;
    // ADD_A_E;
    // LD_hld_A;
    // LD_A_hl;
    // ADC_A_D;
    // LD_hl_A;
    // IF_C goto full_hp;
    if(hp + amount > 0xffff) {
        return ReviveFullHP(bc);
    }
    hp += amount;
    // CALL(aLoadCurHPIntoBuffer3);
    wram->wHPBuffer3 = hp;
    // LD_A(MON_HP + 1);
    // CALL(aGetPartyParamLocation);
    // LD_D_H;
    // LD_E_L;
    // LD_A(MON_MAXHP + 1);
    uint16_t maxHP = BigEndianToNative16(bc->maxHP);
    // CALL(aGetPartyParamLocation);
    // LD_A_de;
    // SUB_A_hl;
    // DEC_DE;
    // DEC_HL;
    // LD_A_de;
    // SBC_A_hl;
    // IF_C goto finish;
    if(hp >= maxHP) {
        return ReviveFullHP(bc);
    }

// full_hp:
    // CALL(aReviveFullHP);

    bc->HP = NativeToBigEndian16(hp);
// finish:
    // RET;
    return hp;
}

void RemoveHP(void){
    LD_A(MON_HP + 1);
    CALL(aGetPartyParamLocation);
    LD_A_hl;
    SUB_A_E;
    LD_hld_A;
    LD_A_hl;
    SBC_A_D;
    LD_hl_A;
    IF_NC goto okay;
    XOR_A_A;
    LD_hld_A;
    LD_hl_A;

okay:
    CALL(aLoadCurHPIntoBuffer3);
    RET;

}

void RemoveHP_Conv(struct PartyMon* bc, uint16_t amount){
    // LD_A(MON_HP + 1);
    // CALL(aGetPartyParamLocation);
    uint16_t hp = BigEndianToNative16(bc->HP);
    // LD_A_hl;
    // SUB_A_E;
    // LD_hld_A;
    // LD_A_hl;
    // SBC_A_D;
    // LD_hl_A;
    // IF_NC goto okay;
    if(hp < amount) {
        // XOR_A_A;
        // LD_hld_A;
        // LD_hl_A;
        wram->wHPBuffer3 = 0;
        bc->HP = 0;
    }
    else {
        wram->wHPBuffer3 = hp - amount;
        bc->HP = NativeToBigEndian16(hp - amount);
    }

// okay:
    // CALL(aLoadCurHPIntoBuffer3);
    // RET;
}

bool IsMonFainted(struct PartyMon* bc){
    // PUSH_DE;
    // CALL(aLoadMaxHPIntoBuffer1);
    wram->wHPBuffer1 = BigEndianToNative16(bc->maxHP);
    // CALL(aLoadCurHPIntoBuffer2);
    wram->wHPBuffer2 = BigEndianToNative16(bc->HP);
    // CALL(aLoadHPFromBuffer2);
    // LD_A_D;
    // OR_A_E;
    // POP_DE;
    // RET;
    return bc->HP == 0;
}

bool IsMonAtFullHealth(struct PartyMon* bc){
    // CALL(aLoadHPFromBuffer2);
    uint16_t maxHP = BigEndianToNative16(bc->maxHP);
    uint16_t HP = BigEndianToNative16(bc->HP);
    // LD_H_D;
    // LD_L_E;
    // CALL(aLoadHPFromBuffer1);
    // LD_A_L;
    // SUB_A_E;
    // LD_A_H;
    // SBC_A_D;
    // RET;
    return maxHP == HP;
}

void LoadCurHPIntoBuffer3(void){
    LD_A(MON_HP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LD_addr_A(wHPBuffer3 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer3);
    RET;

}

void LoadHPIntoBuffer3(void){
//  //  unreferenced
    LD_A_D;
    LD_addr_A(wHPBuffer3 + 1);
    LD_A_E;
    LD_addr_A(wHPBuffer3);
    RET;

}

void LoadHPFromBuffer3(void){
//  //  unreferenced
    LD_A_addr(wHPBuffer3 + 1);
    LD_D_A;
    LD_A_addr(wHPBuffer3);
    LD_E_A;
    RET;

}

void LoadCurHPIntoBuffer2(void){
    LD_A(MON_HP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LD_addr_A(wHPBuffer2 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer2);
    RET;

}

void LoadHPFromBuffer2(void){
    LD_A_addr(wHPBuffer2 + 1);
    LD_D_A;
    LD_A_addr(wHPBuffer2);
    LD_E_A;
    RET;

}

void LoadMaxHPIntoBuffer1(void){
    PUSH_HL;
    LD_A(MON_MAXHP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LD_addr_A(wHPBuffer1 + 1);
    LD_A_hl;
    LD_addr_A(wHPBuffer1);
    POP_HL;
    RET;

}

void LoadHPFromBuffer1(void){
    LD_A_addr(wHPBuffer1 + 1);
    LD_D_A;
    LD_A_addr(wHPBuffer1);
    LD_E_A;
    RET;

}

void GetOneFifthMaxHP(void){
    PUSH_BC;
    LD_A(MON_MAXHP);
    CALL(aGetPartyParamLocation);
    LD_A_hli;
    LDH_addr_A(hDividend + 0);
    LD_A_hl;
    LDH_addr_A(hDividend + 1);
    LD_A(5);
    LDH_addr_A(hDivisor);
    LD_B(2);
    CALL(aDivide);
    LDH_A_addr(hQuotient + 2);
    LD_D_A;
    LDH_A_addr(hQuotient + 3);
    LD_E_A;
    POP_BC;
    RET;

}

uint16_t GetOneFifthMaxHP_Conv(struct PartyMon* bc){
    // PUSH_BC;
    // LD_A(MON_MAXHP);
    // CALL(aGetPartyParamLocation);
    // LD_A_hli;
    // LDH_addr_A(hDividend + 0);
    // LD_A_hl;
    // LDH_addr_A(hDividend + 1);
    // LD_A(5);
    // LDH_addr_A(hDivisor);
    // LD_B(2);
    // CALL(aDivide);
    // LDH_A_addr(hQuotient + 2);
    // LD_D_A;
    // LDH_A_addr(hQuotient + 3);
    // LD_E_A;
    // POP_BC;
    // RET;
    return BigEndianToNative16(bc->maxHP) / 5;
}

uint16_t GetHealingItemAmount(item_t item){
    // PUSH_HL;
    // LD_A_addr(wCurItem);
    // LD_HL(mHealingHPAmounts);
    const struct HealingHPEntry* hl = HealingHPAmounts;
    // LD_D_A;

    while(hl->item != (item_t)-1) {
    // next:
        // LD_A_hli;
        // CP_A(-1);
        // IF_Z goto NotFound;
        // CP_A_D;
        // IF_Z goto done;
        if(hl->item == item) {
            printf("Healing item: %d, amount %d\n", hl->item, hl->amount);
            return hl->amount;
        }
        // INC_HL;
        // INC_HL;
        hl++;
        // goto next;
    }

// NotFound:
    // SCF;

// done:
    // LD_E_hl;
    // INC_HL;
    // LD_D_hl;
    // POP_HL;
    // RET;

// INCLUDE "data/items/heal_hp.asm"
    printf("Healing item: %d, amount %d\n", item, 0);
    return 0;
}

static u8_flag_s Softboiled_MilkDrinkFunction_SelectMilkDrinkRecipient(uint8_t b){
    static const txt_cmd_s ItemCantUseOnMonText[] = {
        text_far(v_ItemCantUseOnMonText)
        text_end
    };
    while(1){
    // loop:
        // PUSH_BC;
        // LD_A(PARTYMENUACTION_HEALING_ITEM);
        // LD_addr_A(wPartyMenuActionText);
        wram->wPartyMenuActionText = PARTYMENUACTION_HEALING_ITEM;
        // CALL(aChooseMonToUseItemOn);
        u8_flag_s res = ChooseMonToUseItemOn();
        // POP_BC;
        // IF_C goto set_carry;
        if(res.flag)
            return u8_flag(b, true);
        // LD_A_addr(wPartyMenuCursor);
        // DEC_A;
        // LD_C_A;
        uint8_t c = res.a - 1;
        // LD_A_B;
        // CP_A_C;
        // IF_Z goto cant_use;  // chose the same mon as user
        // LD_A_C;
        // LD_addr_A(wCurPartyMon);
        // CALL(aIsMonFainted);
        // IF_Z goto cant_use;
        // CALL(aIsMonAtFullHealth);
        // IF_NC goto cant_use;
        if(c != b && !IsMonFainted(wram->wPartyMon + c) && !IsMonAtFullHealth(wram->wPartyMon + c)) {
            // XOR_A_A;
            // RET;
            return u8_flag(c, false);
        }

    // set_carry:
        // SCF;
        // RET;

    // cant_use:
        // PUSH_BC;
        // LD_HL(mSoftboiled_MilkDrinkFunction_ItemCantUseOnMonText);
        // CALL(aMenuTextboxBackup);
        MenuTextboxBackup_Conv(ItemCantUseOnMonText);
        // POP_BC;
        // goto loop;
    }
}

void Softboiled_MilkDrinkFunction(void){
//  Softboiled/Milk Drink in the field
    // LD_A_addr(wPartyMenuCursor);
    // DEC_A;
    // LD_B_A;
    uint8_t b = wram->wPartyMenuCursor - 1;
    // CALL(aSoftboiled_MilkDrinkFunction_SelectMilkDrinkRecipient);  // select pokemon
    u8_flag_s res = Softboiled_MilkDrinkFunction_SelectMilkDrinkRecipient(b);
    // IF_C goto skip;
    if(!res.flag){
        // LD_A_B;
        // LD_addr_A(wCurPartyMon);
        struct PartyMon* user = wram->wPartyMon + b;
        // CALL(aIsMonFainted);
        IsMonFainted(user);
        // CALL(aGetOneFifthMaxHP);
        uint16_t amt = GetOneFifthMaxHP_Conv(user);
        // CALL(aRemoveHP);
        RemoveHP_Conv(user, amt);
        // PUSH_BC;
        // CALL(aHealHP_SFX_GFX);
        HealHP_SFX_GFX();
        // POP_BC;
        // CALL(aGetOneFifthMaxHP);
        amt = GetOneFifthMaxHP_Conv(user);
        // LD_A_C;
        // LD_addr_A(wCurPartyMon);
        struct PartyMon* recipient = wram->wPartyMon + res.a;
        // CALL(aIsMonFainted);
        IsMonFainted(recipient);
        // CALL(aRestoreHealth);
        RestoreHealth_Conv(recipient, amt);
        // CALL(aHealHP_SFX_GFX);
        HealHP_SFX_GFX();
        // LD_A(PARTYMENUTEXT_HEAL_HP);
        // CALL(aItemActionText);
        ItemActionText(PARTYMENUTEXT_HEAL_HP);
        // CALL(aJoyWaitAorB);
        JoyWaitAorB_Conv();
    }

// skip:
    // LD_A_B;
    // INC_A;
    // LD_addr_A(wPartyMenuCursor);
    wram->wPartyMenuCursor = b + 1;
    // RET;
}

void EscapeRopeEffect(void){
    // XOR_A_A;
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = FALSE;
    // FARCALL(aEscapeRopeFunction);
    EscapeRopeFunction();

    // LD_A_addr(wItemEffectSucceeded);
    // CP_A(1);
    // CALL_Z (aUseDisposableItem);
    if(wram->wItemEffectSucceeded)
        UseDisposableItem();
    // RET;
}

void SuperRepelEffect(void){
    // LD_B(200);
    // JR(mUseRepel);
    return UseRepel(200);
}

void MaxRepelEffect(void){
    // LD_B(250);
    // JR(mUseRepel);
    return UseRepel(250);
}

void RepelEffect(void){
    // LD_B(100);
    return UseRepel(100);
}

void UseRepel(uint8_t b){
    // LD_A_addr(wRepelEffect);
    // AND_A_A;
    // LD_HL(mRepelUsedEarlierIsStillInEffectText);
    // JP_NZ (mPrintText);
    if(wram->wRepelEffect)
        return PrintText_Conv2(RepelUsedEarlierIsStillInEffectText);

    // LD_A_B;
    // LD_addr_A(wRepelEffect);
    wram->wRepelEffect = b;
    // JP(mUseItemText);
    return UseItemText();
}

const txt_cmd_s RepelUsedEarlierIsStillInEffectText[] = {
    text_far(v_RepelUsedEarlierIsStillInEffectText)
    text_end
};

void XAccuracyEffect(void){
    // LD_HL(wPlayerSubStatus4);
    // BIT_hl(SUBSTATUS_X_ACCURACY);
    // JP_NZ (mWontHaveAnyEffect_NotUsedMessage);
    if(bit_test(wram->wPlayerSubStatus4, SUBSTATUS_X_ACCURACY))
        return WontHaveAnyEffect_NotUsedMessage();
    // SET_hl(SUBSTATUS_X_ACCURACY);
    bit_set(wram->wPlayerSubStatus4, SUBSTATUS_X_ACCURACY);
    // JP(mUseItemText);
    return UseItemText();
}

void PokeDollEffect(void){
    // LD_A_addr(wBattleMode);
    // DEC_A;  // WILD_BATTLE?
    // IF_NZ goto not_wild;
    if(wram->wBattleMode != WILD_BATTLE) {
    // not_wild:
        // XOR_A_A;
        // LD_addr_A(wItemEffectSucceeded);
        wram->wItemEffectSucceeded = FALSE;
        // RET;
        return;
    }
    // INC_A;  // TRUE
    // LD_addr_A(wForcedSwitch);
    wram->wForcedSwitch = TRUE;
    // LD_A_addr(wBattleResult);
    // AND_A(BATTLERESULT_BITMASK);
    // OR_A(DRAW);
    // LD_addr_A(wBattleResult);
    wram->wBattleResult = (wram->wBattleResult & BATTLERESULT_BITMASK) | DRAW;
    // JP(mUseItemText);
    return UseItemText();
}

void GuardSpecEffect(void){
    // LD_HL(wPlayerSubStatus4);
    // BIT_hl(SUBSTATUS_MIST);
    // JP_NZ (mWontHaveAnyEffect_NotUsedMessage);
    if(bit_test(wram->wPlayerSubStatus4, SUBSTATUS_MIST))
        return WontHaveAnyEffect_NotUsedMessage();
    // SET_hl(SUBSTATUS_MIST);
    bit_set(wram->wPlayerSubStatus4, SUBSTATUS_MIST);
    // JP(mUseItemText);
    return UseItemText();
}

void DireHitEffect(void){
    // LD_HL(wPlayerSubStatus4);
    // BIT_hl(SUBSTATUS_FOCUS_ENERGY);
    // JP_NZ (mWontHaveAnyEffect_NotUsedMessage);
    if(bit_test(wram->wPlayerSubStatus4, SUBSTATUS_FOCUS_ENERGY))
        return WontHaveAnyEffect_NotUsedMessage();
    // SET_hl(SUBSTATUS_FOCUS_ENERGY);
    bit_set(wram->wPlayerSubStatus4, SUBSTATUS_FOCUS_ENERGY);
    // JP(mUseItemText);
    return UseItemText();
}

void XItemEffect(void){
    // CALL(aUseItemText);
    UseItemText();

    // LD_A_addr(wCurItem);
    item_t target = wram->wCurItem;
    // LD_HL(mXItemStats);
    const struct ItemStat* hl = XItemStats;

    while(hl->item != target) {
    // loop:
        // CP_A_hl;
        // IF_Z goto got_it;
        // INC_HL;
        // INC_HL;
        // goto loop;
        hl++;
    }

// got_it:
    // INC_HL;
    // LD_B_hl;
    // XOR_A_A;
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = TURN_PLAYER;
    // LD_addr_A(wAttackMissed);
    wram->wAttackMissed = FALSE;
    // LD_addr_A(wEffectFailed);
    wram->wEffectFailed = FALSE;
    // FARCALL(aRaiseStat);
    RaiseStat_Conv(hl->stat);
    // CALL(aWaitSFX);
    WaitSFX();

    // FARCALL(aBattleCommand_StatUpMessage);
    BattleCommand_StatUpMessage();
    // FARCALL(aBattleCommand_StatUpFailText);
    BattleCommand_StatUpFailText();

    // LD_A_addr(wCurBattleMon);
    // LD_addr_A(wCurPartyMon);
    wram->wCurPartyMon = wram->wCurBattleMon;
    // LD_C(HAPPINESS_USEDXITEM);
    // FARCALL(aChangeHappiness);
    ChangeHappiness_Conv(HAPPINESS_USEDXITEM);
    // RET;

// INCLUDE "data/items/x_stats.asm"
}

void PokeFluteEffect(void){
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_NZ goto in_battle;
// overworld flute code was dummied out here


in_battle:
    XOR_A_A;
    LD_addr_A(wPokeFluteCuredSleep);

    LD_B(~SLP);

    LD_HL(wPartyMon1Status);
    CALL(aPokeFluteEffect_CureSleep);

    LD_A_addr(wBattleMode);
    CP_A(WILD_BATTLE);
    IF_Z goto skip_otrainer;
    LD_HL(wOTPartyMon1Status);
    CALL(aPokeFluteEffect_CureSleep);

skip_otrainer:

    LD_HL(wBattleMonStatus);
    LD_A_hl;
    AND_A_B;
    LD_hl_A;
    LD_HL(wEnemyMonStatus);
    LD_A_hl;
    AND_A_B;
    LD_hl_A;

    LD_A_addr(wPokeFluteCuredSleep);
    AND_A_A;
    LD_HL(mPokeFluteEffect_PlayedFluteText);
    JP_Z (mPrintText);
    LD_HL(mPokeFluteEffect_PlayedTheFlute);
    CALL(aPrintText);

    LD_A_addr(wLowHealthAlarm);
    AND_A(1 << DANGER_ON_F);
    IF_NZ goto dummy;
// more code was dummied out here

dummy:
    LD_HL(mPokeFluteEffect_FluteWakeUpText);
    JP(mPrintText);


CureSleep:
    LD_DE(PARTYMON_STRUCT_LENGTH);
    LD_C(PARTY_LENGTH);

loop:
    LD_A_hl;
    PUSH_AF;
    AND_A(SLP);
    IF_Z goto not_asleep;
    LD_A(TRUE);
    LD_addr_A(wPokeFluteCuredSleep);

not_asleep:
    POP_AF;
    AND_A_B;
    LD_hl_A;
    ADD_HL_DE;
    DEC_C;
    IF_NZ goto loop;
    RET;


PlayedFluteText:
    //text_far ['_PlayedFluteText']
    //text_end ['?']


FluteWakeUpText:
    //text_far ['_FluteWakeUpText']
    //text_end ['?']


PlayedTheFlute:
// played the # FLUTE.@ @
    //text_far ['Text_PlayedPokeFlute']
    //text_asm ['?']
    LD_A_addr(wBattleMode);
    AND_A_A;
    IF_NZ goto battle;

    PUSH_DE;
    LD_DE(SFX_POKEFLUTE);
    CALL(aWaitPlaySFX);
    CALL(aWaitSFX);
    POP_DE;


battle:
    JP(mPokeFluteTerminator);

}

void BlueCardEffect(void){
    static const txt_cmd_s BlueCardBalanceText[] = {
        text_far(v_BlueCardBalanceText)
        text_end
    };
    // LD_HL(mBlueCardEffect_BlueCardBalanceText);
    // JP(mMenuTextboxWaitButton);
    return MenuTextboxWaitButton(BlueCardBalanceText);
}

void CoinCaseEffect(void){
    static const txt_cmd_s CoinCaseCountText[] = {
        text_far(v_CoinCaseCountText)
        text_end
    };
    // LD_HL(mCoinCaseEffect_CoinCaseCountText);
    // JP(mMenuTextboxWaitButton);
    return MenuTextboxWaitButton(CoinCaseCountText);
}

void OldRodEffect(void){
    // LD_E(0x0);
    // JR(mUseRod);
    return UseRod(0x0);
}

void GoodRodEffect(void){
    // LD_E(0x1);
    // JR(mUseRod);
    return UseRod(0x1);
}

void SuperRodEffect(void){
    // LD_E(0x2);
    // JR(mUseRod);
    return UseRod(0x2);
}

void UseRod(uint8_t rod){
    // FARCALL(aFishFunction);
    // RET;
    return FishFunction_Conv(rod);
}

void ItemfinderEffect(void){
    // FARCALL(aItemFinder);
    // RET;
    return ItemFinder();
}

void RestorePPEffect(void){
    // LD_A_addr(wCurItem);
    // LD_addr_A(wTempRestorePPItem);
    wram->wTempRestorePPItem = wram->wCurItem;
    bool cancel;

loop:
// Party Screen opens to choose on which mon to use the Item
    // LD_B(PARTYMENUACTION_HEALING_ITEM);
    // CALL(aUseItem_SelectMon);
    cancel = UseItem_SelectMon(PARTYMENUACTION_HEALING_ITEM);
    // JP_C (mPPRestoreItem_Cancel);
    if(cancel)
        return PPRestoreItem_Cancel();

loop2:
    // LD_A_addr(wTempRestorePPItem);
    // CP_A(MAX_ELIXER);
    // JP_Z (mElixer_RestorePPofAllMoves);
    // CP_A(ELIXER);
    // JP_Z (mElixer_RestorePPofAllMoves);
    if(wram->wTempRestorePPItem == MAX_ELIXER || wram->wTempRestorePPItem == ELIXER)
        return Elixer_RestorePPofAllMoves();

    // LD_HL(mRaiseThePPOfWhichMoveText);
    // LD_A_addr(wTempRestorePPItem);
    // CP_A(PP_UP);
    // IF_Z goto ppup;
    // LD_HL(mRestoreThePPOfWhichMoveText);
    const txt_cmd_s* text = (wram->wTempRestorePPItem == PP_UP)? RaiseThePPOfWhichMoveText: RestoreThePPOfWhichMoveText;

// ppup:
    // CALL(aPrintText);
    PrintText_Conv2(text);

    // LD_A_addr(wCurMoveNum);
    uint8_t curMoveNum = wram->wCurMoveNum;
    // PUSH_AF;
    // XOR_A_A;
    // LD_addr_A(wCurMoveNum);
    wram->wCurMoveNum = 0x0;
    // LD_A(0x2);
    // LD_addr_A(wMoveSelectionMenuType);
    wram->wMoveSelectionMenuType = 0x2;
    // FARCALL(aMoveSelectionScreen);
    cancel = MoveSelectionScreen();
    // POP_BC;

    // LD_A_B;
    // LD_addr_A(wCurMoveNum);
    wram->wCurMoveNum = curMoveNum;
    // IF_NZ goto loop;
    if(cancel)
        goto loop;
    struct PartyMon* mon = wram->wPartyMon + wram->wCurPartyMon;
    // LD_HL(wPartyMon1Moves);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aGetMthMoveOfNthPartymon);
    move_t move = mon->mon.moves[wram->wMenuCursorY];
    uint8_t* pp = mon->mon.PP + wram->wMenuCursorY;
    // PUSH_HL;
    // LD_A_hl;
    // LD_addr_A(wNamedObjectIndex);
    // CALL(aGetMoveName);
    // CALL(aCopyName1);
    CopyName1(GetMoveName(move));
    // POP_HL;

    // LD_A_addr(wTempRestorePPItem);
    // CP_A(PP_UP);
    // JP_NZ (mNot_PP_Up);
    if(wram->wTempRestorePPItem != PP_UP)
        return Not_PP_Up(mon, wram->wMenuCursorY, wram->wTempRestorePPItem);

    // LD_A_hl;
    // CP_A(SKETCH);
    // IF_Z goto CantUsePPUpOnSketch;

    // LD_BC(MON_PP - MON_MOVES);
    // ADD_HL_BC;
    // LD_A_hl;
    // CP_A(PP_UP_MASK);
    // IF_C goto do_ppup;
    if(move == SKETCH || (*pp >= PP_UP_MASK)) {
    // CantUsePPUpOnSketch:
        // LD_HL(mPPIsMaxedOutText);
        // CALL(aPrintText);
        PrintText_Conv2(PPIsMaxedOutText);
        goto loop2;
    }

// do_ppup:
    // LD_A_hl;
    // ADD_A(PP_UP_ONE);
    // LD_hl_A;
    *pp += PP_UP_ONE;
    // LD_A(TRUE);
    // LD_addr_A(wUsePPUp);
    wram->wUsePPUp = TRUE;
    // CALL(aApplyPPUp);
    // CALL(aPlay_SFX_FULL_HEAL);
    Play_SFX_FULL_HEAL();

    // LD_HL(mPPsIncreasedText);
    // CALL(aPrintText);
    PrintText_Conv2(PPsIncreasedText);

    return FinishPPRestore();
}

void FinishPPRestore(void){
    // CALL(aClearPalettes);
    ClearPalettes_Conv();
    // JP(mUseDisposableItem);
    UseDisposableItem();
}

static void BattleRestorePP_UpdateBattleMonPP(void) {
    // LD_A_addr(wCurPartyMon);
    // LD_HL(wPartyMon1Moves);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    struct PartyMon* mon = wram->wPartyMon + wram->wCurPartyMon;
    // CALL(aAddNTimes);
    // LD_DE(wBattleMonMoves);
    // LD_B(NUM_MOVES);

    for(uint32_t b = 0; b < NUM_MOVES; ++b) {
    // loop:
        // LD_A_de;
        // AND_A_A;
        // IF_Z goto done;
        if(wram->wBattleMon.moves[b] == NO_MOVE) 
            break;
        // CP_A_hl;
        // IF_NZ goto next;
        if(wram->wBattleMon.moves[b] != mon->mon.moves[b])
            continue;
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // for(int rept = 0; rept < NUM_MOVES + 2; rept++){  //  wBattleMonPP - wBattleMonMoves
        // INC_DE;
        // }
        // LD_BC(MON_PP - MON_MOVES);
        // ADD_HL_BC;
        // LD_A_hl;
        // LD_de_A;
        wram->wBattleMon.pp[b] = mon->mon.PP[b];
        // POP_BC;
        // POP_DE;
        // POP_HL;

    // next:
        // INC_HL;
        // INC_DE;
        // DEC_B;
        // IF_NZ goto loop;
    }

// done:
    // RET;
}

void BattleRestorePP(void){
    // LD_A_addr(wBattleMode);
    // AND_A_A;
    // IF_Z goto not_in_battle;
    // LD_A_addr(wCurPartyMon);
    // LD_B_A;
    // LD_A_addr(wCurBattleMon);
    // CP_A_B;
    // IF_NZ goto not_in_battle;
    // LD_A_addr(wPlayerSubStatus5);
    // BIT_A(SUBSTATUS_TRANSFORMED);
    // IF_NZ goto not_in_battle;
    if(wram->wBattleMode != 0 
    && wram->wCurPartyMon == wram->wCurBattleMon
    && !bit_test(wram->wPlayerSubStatus5, SUBSTATUS_TRANSFORMED)) {
        // CALL(aBattleRestorePP_UpdateBattleMonPP);
        BattleRestorePP_UpdateBattleMonPP();
    }

// not_in_battle:
    // CALL(aPlay_SFX_FULL_HEAL);
    Play_SFX_FULL_HEAL();
    // LD_HL(mPPRestoredText);
    // CALL(aPrintText);
    PrintText_Conv2(PPRestoredText);
    // JR(mFinishPPRestore);
    return FinishPPRestore();
}

void Not_PP_Up(struct PartyMon* mon, uint8_t n, item_t item){
    // CALL(aRestorePP);
    // JR_NZ (mBattleRestorePP);
    if(RestorePP_Conv(mon, n, item))
        return BattleRestorePP();
    // JP(mPPRestoreItem_NoEffect);
    return PPRestoreItem_NoEffect();
}

void Elixer_RestorePPofAllMoves(void){
    // XOR_A_A;
    // LD_HL(wMenuCursorY);
    // LD_hli_A;
    wram->wMenuCursorY = 0;
    // LD_hl_A;
    wram->wMenuCursorX = 0;
    // LD_B(NUM_MOVES);
    uint8_t b = NUM_MOVES;

    do {
    // moveLoop:
        // PUSH_BC;
        struct PartyMon* curMon = wram->wPartyMon + wram->wCurPartyMon;
        // LD_HL(wPartyMon1Moves);
        // LD_BC(PARTYMON_STRUCT_LENGTH);
        // CALL(aGetMthMoveOfNthPartymon);
        // LD_A_hl;
        // AND_A_A;
        // IF_Z goto next;
        if(curMon->mon.moves[wram->wMenuCursorY] == NO_MOVE)
            continue;

        // CALL(aRestorePP);
        // IF_Z goto next;
        if(RestorePP_Conv(curMon, wram->wMenuCursorY, wram->wTempRestorePPItem)) {
            // LD_HL(wMenuCursorX);
            // INC_hl;
            wram->wMenuCursorX++;
        }

    // next:
        // LD_HL(wMenuCursorY);
        // INC_hl;
        // POP_BC;
        // DEC_B;
        // IF_NZ goto moveLoop;
    } while(wram->wMenuCursorY++, --b != 0);
    // LD_A_addr(wMenuCursorX);
    // AND_A_A;
    // JP_NZ (mBattleRestorePP);
    if(wram->wMenuCursorX != 0)
        return BattleRestorePP();

    return PPRestoreItem_NoEffect();
}

void PPRestoreItem_NoEffect(void){
    // CALL(aWontHaveAnyEffectMessage);
    WontHaveAnyEffectMessage();

    return PPRestoreItem_Cancel();
}

void PPRestoreItem_Cancel(void){
    // CALL(aClearPalettes);
    ClearPalettes_Conv();
    // XOR_A_A;
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = FALSE;
    // RET;
}

void RestorePP(void){
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMonType);
    CALL(aGetMaxPPOfMove);
    LD_HL(wPartyMon1PP);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    CALL(aGetMthMoveOfNthPartymon);
    LD_A_addr(wTempPP);
    LD_B_A;
    LD_A_hl;
    AND_A(PP_MASK);
    CP_A_B;
    IF_NC goto dont_restore;

    LD_A_addr(wTempRestorePPItem);
    CP_A(MAX_ELIXER);
    IF_Z goto restore_all;
    CP_A(MAX_ETHER);
    IF_Z goto restore_all;

    LD_C(5);
    CP_A(MYSTERYBERRY);
    IF_Z goto restore_some;

    LD_C(10);


restore_some:
    LD_A_hl;
    AND_A(PP_MASK);
    ADD_A_C;
    CP_A_B;
    IF_NC goto restore_all;
    LD_B_A;


restore_all:
    LD_A_hl;
    AND_A(PP_UP_MASK);
    OR_A_B;
    LD_hl_A;
    RET;


dont_restore:
    XOR_A_A;
    RET;

}

bool RestorePP_Conv(struct PartyMon* mon, uint8_t n, item_t item){
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMonType);
    // CALL(aGetMaxPPOfMove);
    uint8_t maxpp = GetMaxPPOfMove_Conv(mon, PARTYMON, n);
    // LD_HL(wPartyMon1PP);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // CALL(aGetMthMoveOfNthPartymon);
    // LD_A_addr(wTempPP);
    // LD_B_A;
    uint8_t b = maxpp;
    // LD_A_hl;
    // AND_A(PP_MASK);
    // CP_A_B;
    // IF_NC goto dont_restore;
    if((mon->mon.PP[n] & PP_MASK) < maxpp) {
        // LD_A_addr(wTempRestorePPItem);
        // CP_A(MAX_ELIXER);
        // IF_Z goto restore_all;
        // CP_A(MAX_ETHER);
        // IF_Z goto restore_all;
        if(item != MAX_ELIXER && item != MAX_ETHER) {
            // LD_C(5);
            // CP_A(MYSTERYBERRY);
            // IF_Z goto restore_some;

            // LD_C(10);
            const uint8_t c = (item == MYSTERYBERRY)? 5: 10;

        // restore_some:
            // LD_A_hl;
            // AND_A(PP_MASK);
            // ADD_A_C;
            const uint8_t pp = mon->mon.PP[n] & PP_MASK;
            // CP_A_B;
            // IF_NC goto restore_all;
            // LD_B_A;
            if(pp + c < maxpp)
                b = pp + c;
        }

    // restore_all:
        // LD_A_hl;
        // AND_A(PP_UP_MASK);
        // OR_A_B;
        // LD_hl_A;
        mon->mon.PP[n] = (mon->mon.PP[n] & PP_UP_MASK) | b;
        // RET;
        return true;
    }

// dont_restore:
    // XOR_A_A;
    // RET;
    return false;
}

const txt_cmd_s RaiseThePPOfWhichMoveText[] = {
    text_far(v_RaiseThePPOfWhichMoveText)
    text_end
};

const txt_cmd_s RestoreThePPOfWhichMoveText[] = {
    text_far(v_RestoreThePPOfWhichMoveText)
    text_end
};

const txt_cmd_s PPIsMaxedOutText[] = {
    text_far(v_PPIsMaxedOutText)
    text_end
};

const txt_cmd_s PPsIncreasedText[] = {
    text_far(v_PPsIncreasedText)
    text_end
};

const txt_cmd_s PPRestoredText[] = {
    text_far(v_PPRestoredText)
    text_end
};

void SquirtbottleEffect(void){
    // FARCALL(av_Squirtbottle);
    // RET;
    return v_Squirtbottle();
}

void CardKeyEffect(void){
    // FARCALL(av_CardKey);
    // RET;
    return v_CardKey();
}

void BasementKeyEffect(void){
    // FARCALL(av_BasementKey);
    // RET;
    return v_BasementKey();
}

void SacredAshEffect(void){
    // FARCALL(av_SacredAsh);
    v_SacredAsh();
    // LD_A_addr(wItemEffectSucceeded);
    // CP_A(0x1);
    // RET_NZ ;
    if(wram->wItemEffectSucceeded != TRUE)
        return;
    // CALL(aUseDisposableItem);
    UseDisposableItem();
    // RET;
}

void NormalBoxEffect(void){
    LD_C(DECOFLAG_SILVER_TROPHY_DOLL);
    JR(mOpenBox);

}

void GorgeousBoxEffect(void){
    LD_C(DECOFLAG_GOLD_TROPHY_DOLL);
    return OpenBox();
}

void OpenBox(void){
    FARCALL(aSetSpecificDecorationFlag);

    LD_HL(mOpenBox_SentTrophyHomeText);
    CALL(aPrintText);

    JP(mUseDisposableItem);


SentTrophyHomeText:
    //text_far ['_SentTrophyHomeText']
    //text_end ['?']

    return NoEffect();
}

void NoEffect(void){
    // JP(mIsntTheTimeMessage);
    return IsntTheTimeMessage();
}

void Play_SFX_FULL_HEAL(void){
    // PUSH_DE;
    // LD_DE(SFX_FULL_HEAL);
    // CALL(aWaitPlaySFX);
    WaitPlaySFX(SFX_FULL_HEAL);
    // POP_DE;
    // RET;
}

void UseItemText(void){
    // LD_HL(mItemUsedText);
    // CALL(aPrintText);
    PrintText_Conv2(ItemUsedText);
    // CALL(aPlay_SFX_FULL_HEAL);
    Play_SFX_FULL_HEAL();
    // CALL(aWaitPressAorB_BlinkCursor);
    WaitPressAorB_BlinkCursor_Conv();
    return UseDisposableItem();
}

void UseDisposableItem(void){
    // LD_HL(wNumItems);
    // LD_A(1);
    // LD_addr_A(wItemQuantityChange);
    wram->wItemQuantityChange = 1;
    // JP(mTossItem);
    TossItem_Conv((item_pocket_s*)&wram->wNumItems, wram->wCurItem);
}

void UseBallInTrainerBattle(void){
    // CALL(aReturnToBattle_UseBall);
    ReturnToBattle_UseBall();
    // LD_DE(ANIM_THROW_POKE_BALL);
    // LD_A_E;
    // LD_addr_A(wFXAnimID);
    // LD_A_D;
    // LD_addr_A(wFXAnimID + 1);
    wram->wFXAnimID = ANIM_THROW_POKE_BALL;
    // XOR_A_A;
    // LD_addr_A(wBattleAnimParam);
    wram->wBattleAnimParam = 0;
    // LDH_addr_A(hBattleTurn);
    hram->hBattleTurn = TURN_PLAYER;
    // LD_addr_A(wNumHits);
    wram->wNumHits = 0;
    // PREDEF(pPlayBattleAnim);
    PlayBattleAnim();
    // LD_HL(mBallBlockedText);
    // CALL(aPrintText);
    PrintText_Conv2(BallBlockedText);
    // LD_HL(mBallDontBeAThiefText);
    // CALL(aPrintText);
    PrintText_Conv2(BallDontBeAThiefText);
    // JR(mUseDisposableItem);
    return UseDisposableItem();
}

void WontHaveAnyEffect_NotUsedMessage(void){
    // LD_HL(mItemWontHaveEffectText);
    // CALL(aPrintText);
    PrintText_Conv2(ItemWontHaveEffectText);

// Item wasn't used.
    // LD_A(0x2);
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = 0x2;
    // RET;
}

void LooksBitterMessage(void){
    // LD_HL(mItemLooksBitterText);
    // JP(mPrintText);
    PrintText_Conv2(ItemLooksBitterText);
}

void Ball_BoxIsFullMessage(void){
    // LD_HL(mBallBoxFullText);
    // CALL(aPrintText);
    PrintText_Conv2(BallBoxFullText);

// Item wasn't used.
    // LD_A(0x2);
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = 0x2;
    // RET;
}

void CantUseOnEggMessage(void){
    // LD_HL(mItemCantUseOnEggText);
    // JR(mCantUseItemMessage);
    return CantUseItemMessage(ItemCantUseOnEggText);
}

void IsntTheTimeMessage(void){
    // LD_HL(mItemOakWarningText);
    // JR(mCantUseItemMessage);
    return CantUseItemMessage(ItemOakWarningText);
}

void WontHaveAnyEffectMessage(void){
    // LD_HL(mItemWontHaveEffectText);
    // JR(mCantUseItemMessage);
    return CantUseItemMessage(ItemWontHaveEffectText);
}

void BelongsToSomeoneElseMessage(void){
//  //  unreferenced
    // LD_HL(mItemBelongsToSomeoneElseText);
    // JR(mCantUseItemMessage);
    return CantUseItemMessage(ItemBelongsToSomeoneElseText);
}

void CyclingIsntAllowedMessage(void){
//  //  unreferenced
    // LD_HL(mNoCyclingText);
    // JR(mCantUseItemMessage);
    return CantUseItemMessage(NoCyclingText);
}

void CantGetOnYourBikeMessage(void){
//  //  unreferenced
    // LD_HL(mItemCantGetOnText);
// fallthrough

    return CantUseItemMessage(ItemCantGetOnText);
}

void CantUseItemMessage(const txt_cmd_s* hl){
//  Item couldn't be used.
    // XOR_A_A;
    // LD_addr_A(wItemEffectSucceeded);
    wram->wItemEffectSucceeded = 0x0;
    // JP(mPrintText);
    return PrintText_Conv2(hl);
}

const txt_cmd_s ItemLooksBitterText[] = {
    text_far(v_ItemLooksBitterText)
    text_end
};

const txt_cmd_s ItemCantUseOnEggText[] = {
    text_far(v_ItemCantUseOnEggText)
    text_end
};

const txt_cmd_s ItemOakWarningText[] = {
    text_far(v_ItemOakWarningText)
    text_end
};

const txt_cmd_s ItemBelongsToSomeoneElseText[] = {
    text_far(v_ItemBelongsToSomeoneElseText)
    text_end
};

const txt_cmd_s ItemWontHaveEffectText[] = {
    text_far(v_ItemWontHaveEffectText)
    text_end
};

const txt_cmd_s BallBlockedText[] = {
    text_far(v_BallBlockedText)
    text_end
};

const txt_cmd_s BallDontBeAThiefText[] = {
    text_far(v_BallDontBeAThiefText)
    text_end
};

const txt_cmd_s NoCyclingText[] = {
    text_far(v_NoCyclingText)
    text_end
};

const txt_cmd_s ItemCantGetOnText[] = {
    text_far(v_ItemCantGetOnText)
    text_end
};

const txt_cmd_s BallBoxFullText[] = {
    text_far(v_BallBoxFullText)
    text_end
};

const txt_cmd_s ItemUsedText[] = {
    text_far(v_ItemUsedText)
    text_end
};

void ItemGotOnText(void){
//  //  unreferenced
    //text_far ['_ItemGotOnText']
    //text_end ['?']

    return ItemGotOffText();
}

void ItemGotOffText(void){
//  //  unreferenced
    //text_far ['_ItemGotOffText']
    //text_end ['?']

    return ApplyPPUp();
}

void ApplyPPUp(void){
    LD_A(MON_MOVES);
    CALL(aGetPartyParamLocation);
    PUSH_HL;
    LD_DE(wPPUpPPBuffer);
    PREDEF(pFillPP);
    POP_HL;
    LD_BC(MON_PP - MON_MOVES);
    ADD_HL_BC;
    LD_DE(wPPUpPPBuffer);
    LD_B(0);

loop:
    INC_B;
    LD_A_B;
    CP_A(NUM_MOVES + 1);
    RET_Z ;
    LD_A_addr(wUsePPUp);
    DEC_A;  // FALSE?
    IF_NZ goto use;
    LD_A_addr(wMenuCursorY);
    INC_A;
    CP_A_B;
    IF_NZ goto skip;


use:
    LD_A_hl;
    AND_A(PP_UP_MASK);
    LD_A_de;  // wasted cycle
    CALL_NZ (aComputeMaxPP);


skip:
    INC_HL;
    INC_DE;
    goto loop;

    return ComputeMaxPP();
}

void ComputeMaxPP(void){
    PUSH_BC;
// Divide the base PP by 5.
    LD_A_de;
    LDH_addr_A(hDividend + 3);
    XOR_A_A;
    LDH_addr_A(hDividend);
    LDH_addr_A(hDividend + 1);
    LDH_addr_A(hDividend + 2);
    LD_A(5);
    LDH_addr_A(hDivisor);
    LD_B(4);
    CALL(aDivide);
// Get the number of PP, which are bits 6 and 7 of the PP value stored in RAM.
    LD_A_hl;
    LD_B_A;
    SWAP_A;
    AND_A(0xf);
    SRL_A;
    SRL_A;
    LD_C_A;
// If this value is 0, we are done
    AND_A_A;
    IF_Z goto NoPPUp;


loop:
// Normally, a move with 40 PP would have 64 PP with three PP Ups.
// Since this would overflow into bit 6, we prevent that from happening
// by decreasing the extra amount of PP each PP Up provides, resulting
// in a maximum of 61.
    LDH_A_addr(hQuotient + 3);
    CP_A(0x8);
    IF_C goto okay;
    LD_A(0x7);


okay:
    ADD_A_B;
    LD_B_A;
    LD_A_addr(wTempPP);
    DEC_A;
    IF_Z goto NoPPUp;
    DEC_C;
    IF_NZ goto loop;


NoPPUp:
    LD_hl_B;
    POP_BC;
    RET;

}

uint8_t ComputeMaxPP_Conv(uint8_t pp, uint8_t base){
    // PUSH_BC;
// Divide the base PP by 5.
    // LD_A_de;
    // LDH_addr_A(hDividend + 3);
    // XOR_A_A;
    // LDH_addr_A(hDividend);
    // LDH_addr_A(hDividend + 1);
    // LDH_addr_A(hDividend + 2);
    // LD_A(5);
    // LDH_addr_A(hDivisor);
    // LD_B(4);
    // CALL(aDivide);
    base /= 5;
// Get the number of PP, which are bits 6 and 7 of the PP value stored in RAM.
    // LD_A_hl;
    // LD_B_A;
    // SWAP_A;
    // AND_A(0xf);
    // SRL_A;
    // SRL_A;
    // LD_C_A;
    uint8_t ppup_count = (pp & PP_UP_MASK) >> 6;
// If this value is 0, we are done
    // AND_A_A;
    // IF_Z goto NoPPUp;
    if(ppup_count == 0) {
    // NoPPUp:
        // LD_hl_B;
        // POP_BC;
        // RET;
        return pp;
    }

    uint8_t b = pp;
    uint8_t c = ppup_count;
    do {
    // loop:
    // Normally, a move with 40 PP would have 64 PP with three PP Ups.
    // Since this would overflow into bit 6, we prevent that from happening
    // by decreasing the extra amount of PP each PP Up provides, resulting
    // in a maximum of 61.
        // LDH_A_addr(hQuotient + 3);
        uint8_t a = base;
        // CP_A(0x8);
        // IF_C goto okay;
        if(a >= 0x8) 
        // LD_A(0x7);
            a = 0x7;

    // okay:
        // ADD_A_B;
        // LD_B_A;
        b += a;
        // LD_A_addr(wTempPP);
        // DEC_A;
        // IF_Z goto NoPPUp;
        // DEC_C;
        // IF_NZ goto loop;
    } while(--c != 0);


// NoPPUp:
    // LD_hl_B;
    // POP_BC;
    // RET;
    return b;
}

void RestoreAllPP(void){
    LD_A(MON_PP);
    CALL(aGetPartyParamLocation);
    PUSH_HL;
    LD_A(MON_MOVES);
    CALL(aGetPartyParamLocation);
    POP_DE;
    XOR_A_A;  // PARTYMON
    LD_addr_A(wMenuCursorY);
    LD_addr_A(wMonType);
    LD_C(NUM_MOVES);

loop:
    LD_A_hli;
    AND_A_A;
    RET_Z ;
    PUSH_HL;
    PUSH_DE;
    PUSH_BC;
    CALL(aGetMaxPPOfMove);
    POP_BC;
    POP_DE;
    LD_A_de;
    AND_A(PP_UP_MASK);
    LD_B_A;
    LD_A_addr(wTempPP);
    ADD_A_B;
    LD_de_A;
    INC_DE;
    LD_HL(wMenuCursorY);
    INC_hl;
    POP_HL;
    DEC_C;
    IF_NZ goto loop;
    RET;

}

void RestoreAllPP_Conv(struct PartyMon* pmon){
    // LD_A(MON_PP);
    // CALL(aGetPartyParamLocation);
    // PUSH_HL;
    // LD_A(MON_MOVES);
    // CALL(aGetPartyParamLocation);
    // POP_DE;
    // XOR_A_A;  // PARTYMON
    // LD_addr_A(wMenuCursorY);
    // LD_addr_A(wMonType);
    // LD_C(NUM_MOVES);
    move_t* hl = pmon->mon.moves;
    uint8_t* de = pmon->mon.PP;

    for(size_t i = 0; i < NUM_MOVES; ++i) {
    // loop:
        // LD_A_hli;
        move_t a = hl[i];
        // AND_A_A;
        // RET_Z ;
        if(a == NO_MOVE)
            return;
        // PUSH_HL;
        // PUSH_DE;
        // PUSH_BC;
        // CALL(aGetMaxPPOfMove);
        uint8_t maxpp = GetMaxPPOfMove_Conv(pmon, PARTYMON, i);
        // POP_BC;
        // POP_DE;
        // LD_A_de;
        // AND_A(PP_UP_MASK);
        // LD_B_A;
        // LD_A_addr(wTempPP);
        // ADD_A_B;
        // LD_de_A;
        de[i] = (de[i] & PP_UP_MASK) + maxpp;
        // INC_DE;
        // LD_HL(wMenuCursorY);
        // INC_hl;
        // POP_HL;
        // DEC_C;
        // IF_NZ goto loop;
    }
    // RET;
}

void GetMaxPPOfMove(void){
    LD_A_addr(wStringBuffer1 + 0);
    PUSH_AF;
    LD_A_addr(wStringBuffer1 + 1);
    PUSH_AF;

    LD_A_addr(wMonType);
    AND_A_A;

    LD_HL(wPartyMon1Moves);
    LD_BC(PARTYMON_STRUCT_LENGTH);
    IF_Z goto got_partymon;  // PARTYMON

    LD_HL(wOTPartyMon1Moves);
    DEC_A;
    IF_Z goto got_partymon;  // OTPARTYMON

    LD_HL(wTempMonMoves);
    DEC_A;
    IF_Z goto got_nonpartymon;  // BOXMON

    LD_HL(wTempMonMoves);  // Wasted cycles
    DEC_A;
    IF_Z goto got_nonpartymon;  // TEMPMON

    LD_HL(wBattleMonMoves);  // WILDMON


got_nonpartymon:
//   //  BOXMON, TEMPMON, WILDMON
    CALL(aGetMthMoveOfCurrentMon);
    goto gotdatmove;


got_partymon:
//   //  PARTYMON, OTPARTYMON
    CALL(aGetMthMoveOfNthPartymon);


gotdatmove:
    LD_A_hl;
    DEC_A;

    PUSH_HL;
    LD_HL(mMoves + MOVE_PP);
    LD_BC(MOVE_LENGTH);
    CALL(aAddNTimes);
    LD_A(BANK(aMoves));
    CALL(aGetFarByte);
    LD_B_A;
    LD_DE(wStringBuffer1);
    LD_de_A;
    POP_HL;

    PUSH_BC;
    LD_BC(MON_PP - MON_MOVES);
    LD_A_addr(wMonType);
    CP_A(WILDMON);
    IF_NZ goto notwild;
    LD_BC(wEnemyMonPP - wEnemyMonMoves);

notwild:
    ADD_HL_BC;
    LD_A_hl;
    AND_A(PP_UP_MASK);
    POP_BC;

    OR_A_B;
    LD_HL(wStringBuffer1 + 1);
    LD_hl_A;
    XOR_A_A;
    LD_addr_A(wTempPP);
    LD_A_B;  // this gets lost anyway
    CALL(aComputeMaxPP);
    LD_A_hl;
    AND_A(PP_MASK);
    LD_addr_A(wTempPP);

    POP_AF;
    LD_addr_A(wStringBuffer1 + 1);
    POP_AF;
    LD_addr_A(wStringBuffer1 + 0);
    RET;

}

uint8_t GetMaxPPOfMove_Conv(void* mon, uint8_t montype, uint8_t n){
    // LD_A_addr(wStringBuffer1 + 0);
    // PUSH_AF;
    // LD_A_addr(wStringBuffer1 + 1);
    // PUSH_AF;
    move_t* move;
    uint8_t* mpp;

    // LD_A_addr(wMonType);
    // AND_A_A;

    // LD_HL(wPartyMon1Moves);
    // LD_BC(PARTYMON_STRUCT_LENGTH);
    // IF_Z goto got_partymon;  // PARTYMON
    switch(montype) {
    case PARTYMON:
    case OTPARTYMON:
    // got_partymon:
    //   //  PARTYMON, OTPARTYMON
        // CALL(aGetMthMoveOfNthPartymon);
        move = ((struct PartyMon*)mon)->mon.moves + n;
        mpp = ((struct PartyMon*)mon)->mon.PP + n;
        break;
    // LD_HL(wOTPartyMon1Moves);
    // DEC_A;
    // IF_Z goto got_partymon;  // OTPARTYMON

    // LD_HL(wTempMonMoves);
    // DEC_A;
    // IF_Z goto got_nonpartymon;  // BOXMON
    case BOXMON:
    case TEMPMON:
    // got_nonpartymon:
    //   //  BOXMON, TEMPMON, WILDMON
        // CALL(aGetMthMoveOfCurrentMon);
        move = ((struct BoxMon*)mon)->moves + n;
        mpp = ((struct BoxMon*)mon)->PP + n;
        break;
        // goto gotdatmove;

    // LD_HL(wTempMonMoves);  // Wasted cycles
    // DEC_A;
    // IF_Z goto got_nonpartymon;  // TEMPMON

    default:
    case WILDMON:
        // LD_HL(wBattleMonMoves);  // WILDMON
        move = wram->wBattleMon.moves + n;
        mpp = wram->wBattleMon.pp + n;
        break;
    }

// gotdatmove:
    // LD_A_hl;
    // DEC_A;

    // PUSH_HL;
    // LD_HL(mMoves + MOVE_PP);
    // LD_BC(MOVE_LENGTH);
    // CALL(aAddNTimes);
    // LD_A(BANK(aMoves));
    // CALL(aGetFarByte);
    // LD_B_A;
    uint8_t pp = Moves[*move].pp;
    // LD_DE(wStringBuffer1);
    // LD_de_A;
    // POP_HL;

    // PUSH_BC;
    // LD_BC(MON_PP - MON_MOVES);
    // LD_A_addr(wMonType);
    // CP_A(WILDMON);
    // IF_NZ goto notwild;
    // LD_BC(wEnemyMonPP - wEnemyMonMoves);

// notwild:
    // ADD_HL_BC;
    // LD_A_hl;
    // AND_A(PP_UP_MASK);
    // POP_BC;

    // OR_A_B;
    uint8_t pp2 = pp | (*mpp & PP_UP_MASK);
    // LD_HL(wStringBuffer1 + 1);
    // LD_hl_A;
    // XOR_A_A;
    // LD_addr_A(wTempPP);
    // LD_A_B;  // this gets lost anyway
    // CALL(aComputeMaxPP);
    // LD_A_hl;
    // AND_A(PP_MASK);
    // LD_addr_A(wTempPP);
    return ComputeMaxPP_Conv(pp2, pp) & PP_MASK;

    // POP_AF;
    // LD_addr_A(wStringBuffer1 + 1);
    // POP_AF;
    // LD_addr_A(wStringBuffer1 + 0);
    // RET;

}

void GetMthMoveOfNthPartymon(void){
    LD_A_addr(wCurPartyMon);
    CALL(aAddNTimes);

    return GetMthMoveOfCurrentMon();
}

void GetMthMoveOfCurrentMon(void){
    LD_A_addr(wMenuCursorY);
    LD_C_A;
    LD_B(0);
    ADD_HL_BC;
    RET;

}
