#include "../../constants.h"

// decoration: MACRO
// 	; type, name, action, event flag, tile/sprite
// 	db \1, \2, \3
// 	dw \4
// 	db \5
// ENDM

const struct Decoration DecorationAttributes[] = {
// entries correspond to deco constants
    // table_width DECOATTR_STRUCT_LENGTH, DecorationAttributes
	{DECO_PLANT,   0,               0,                 EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1, 0},
	{DECO_PLANT,   PUT_IT_AWAY,     PUT_AWAY_BED,      EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1, 0},
	{DECO_BED,     FEATHERY_BED,    SET_UP_BED,        EVENT_DECO_BED_1,                   0x1b},
	{DECO_BED,     PINK_BED,        SET_UP_BED,        EVENT_DECO_BED_2,                   0x1c},
	{DECO_BED,     POLKADOT_BED,    SET_UP_BED,        EVENT_DECO_BED_3,                   0x1d},
	{DECO_BED,     PIKACHU_BED,     SET_UP_BED,        EVENT_DECO_BED_4,                   0x1e},
	{DECO_PLANT,   PUT_IT_AWAY,     PUT_AWAY_CARPET,   EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1, 0},
	{DECO_CARPET,  RED_CARPET,      SET_UP_CARPET,     EVENT_DECO_CARPET_1,                0x08},
	{DECO_CARPET,  BLUE_CARPET,     SET_UP_CARPET,     EVENT_DECO_CARPET_2,                0x0b},
	{DECO_CARPET,  YELLOW_CARPET,   SET_UP_CARPET,     EVENT_DECO_CARPET_3,                0x0e},
	{DECO_CARPET,  GREEN_CARPET,    SET_UP_CARPET,     EVENT_DECO_CARPET_4,                0x11},
	{DECO_PLANT,   PUT_IT_AWAY,     PUT_AWAY_PLANT,    EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1, 0},
	{DECO_PLANT,   MAGNAPLANT,      SET_UP_PLANT,      EVENT_DECO_PLANT_1,                 0x20},
	{DECO_PLANT,   TROPICPLANT,     SET_UP_PLANT,      EVENT_DECO_PLANT_2,                 0x21},
	{DECO_PLANT,   JUMBOPLANT,      SET_UP_PLANT,      EVENT_DECO_PLANT_3,                 0x22},
	{DECO_PLANT,   PUT_IT_AWAY,     PUT_AWAY_POSTER,   EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1, 0},
	{DECO_PLANT,   TOWN_MAP_POSTER, SET_UP_POSTER,     EVENT_DECO_POSTER_1,                0x1f},
	{DECO_POSTER,  PIKACHU,         SET_UP_POSTER,     EVENT_DECO_POSTER_2,                0x23},
	{DECO_POSTER,  CLEFAIRY,        SET_UP_POSTER,     EVENT_DECO_POSTER_3,                0x24},
	{DECO_POSTER,  JIGGLYPUFF,      SET_UP_POSTER,     EVENT_DECO_POSTER_4,                0x25},
	{DECO_PLANT,   PUT_IT_AWAY,     PUT_AWAY_CONSOLE,  EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1, 0},
	{DECO_PLANT,   FAMICOM,         SET_UP_CONSOLE,    EVENT_DECO_FAMICOM,                 SPRITE_FAMICOM},
	{DECO_PLANT,   SUPER_NES,       SET_UP_CONSOLE,    EVENT_DECO_SNES,                    SPRITE_SNES},
	{DECO_PLANT,   NINTENDO_64,     SET_UP_CONSOLE,    EVENT_DECO_N64,                     SPRITE_N64},
	{DECO_PLANT,   VIRTUAL_BOY,     SET_UP_CONSOLE,    EVENT_DECO_VIRTUAL_BOY,             SPRITE_VIRTUAL_BOY},
	{DECO_PLANT,   PUT_IT_AWAY,     PUT_AWAY_BIG_DOLL, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1, 0},
	{DECO_BIGDOLL, SNORLAX,         SET_UP_BIG_DOLL,   EVENT_DECO_BIG_SNORLAX_DOLL,        SPRITE_BIG_SNORLAX},
	{DECO_BIGDOLL, ONIX,            SET_UP_BIG_DOLL,   EVENT_DECO_BIG_ONIX_DOLL,           SPRITE_BIG_ONIX},
	{DECO_BIGDOLL, LAPRAS,          SET_UP_BIG_DOLL,   EVENT_DECO_BIG_LAPRAS_DOLL,         SPRITE_BIG_LAPRAS},
	{DECO_PLANT,   PUT_IT_AWAY,     PUT_AWAY_DOLL,     EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1, 0},
	{DECO_DOLL,    PIKACHU,         SET_UP_DOLL,       EVENT_DECO_PIKACHU_DOLL,            SPRITE_PIKACHU},
	{DECO_PLANT,   SURF_PIKA_DOLL,  SET_UP_DOLL,       EVENT_DECO_SURFING_PIKACHU_DOLL,    SPRITE_SURFING_PIKACHU},
	{DECO_DOLL,    CLEFAIRY,        SET_UP_DOLL,       EVENT_DECO_CLEFAIRY_DOLL,           SPRITE_CLEFAIRY},
	{DECO_DOLL,    JIGGLYPUFF,      SET_UP_DOLL,       EVENT_DECO_JIGGLYPUFF_DOLL,         SPRITE_JIGGLYPUFF},
	{DECO_DOLL,    BULBASAUR,       SET_UP_DOLL,       EVENT_DECO_BULBASAUR_DOLL,          SPRITE_BULBASAUR},
	{DECO_DOLL,    CHARMANDER,      SET_UP_DOLL,       EVENT_DECO_CHARMANDER_DOLL,         SPRITE_CHARMANDER},
	{DECO_DOLL,    SQUIRTLE,        SET_UP_DOLL,       EVENT_DECO_SQUIRTLE_DOLL,           SPRITE_SQUIRTLE},
	{DECO_DOLL,    POLIWAG,         SET_UP_DOLL,       EVENT_DECO_POLIWAG_DOLL,            SPRITE_POLIWAG},
	{DECO_DOLL,    DIGLETT,         SET_UP_DOLL,       EVENT_DECO_DIGLETT_DOLL,            SPRITE_DIGLETT},
	{DECO_DOLL,    STARYU,          SET_UP_DOLL,       EVENT_DECO_STARMIE_DOLL,            SPRITE_STARMIE},
	{DECO_DOLL,    MAGIKARP,        SET_UP_DOLL,       EVENT_DECO_MAGIKARP_DOLL,           SPRITE_MAGIKARP},
	{DECO_DOLL,    ODDISH,          SET_UP_DOLL,       EVENT_DECO_ODDISH_DOLL,             SPRITE_ODDISH},
	{DECO_DOLL,    GENGAR,          SET_UP_DOLL,       EVENT_DECO_GENGAR_DOLL,             SPRITE_GENGAR},
	{DECO_DOLL,    SHELLDER,        SET_UP_DOLL,       EVENT_DECO_SHELLDER_DOLL,           SPRITE_SHELLDER},
	{DECO_DOLL,    GRIMER,          SET_UP_DOLL,       EVENT_DECO_GRIMER_DOLL,             SPRITE_GRIMER},
	{DECO_DOLL,    VOLTORB,         SET_UP_DOLL,       EVENT_DECO_VOLTORB_DOLL,            SPRITE_VOLTORB},
	{DECO_DOLL,    WEEDLE,          SET_UP_DOLL,       EVENT_DECO_WEEDLE_DOLL,             SPRITE_WEEDLE},
	{DECO_DOLL,    UNOWN,           SET_UP_DOLL,       EVENT_DECO_UNOWN_DOLL,              SPRITE_UNOWN},
	{DECO_DOLL,    GEODUDE,         SET_UP_DOLL,       EVENT_DECO_GEODUDE_DOLL,            SPRITE_GEODUDE},
	{DECO_DOLL,    MACHOP,          SET_UP_DOLL,       EVENT_DECO_MACHOP_DOLL,             SPRITE_MACHOP},
	{DECO_DOLL,    TENTACOOL,       SET_UP_DOLL,       EVENT_DECO_TENTACOOL_DOLL,          SPRITE_TENTACOOL},
	{DECO_PLANT,   GOLD_TROPHY,     SET_UP_DOLL,       EVENT_DECO_GOLD_TROPHY,             SPRITE_GOLD_TROPHY},
	{DECO_PLANT,   SILVER_TROPHY,   SET_UP_DOLL,       EVENT_DECO_SILVER_TROPHY,           SPRITE_SILVER_TROPHY},
};
static_assert(lengthof(DecorationAttributes) == NUM_DECOS + NUM_DECO_CATEGORIES + 1, "");
