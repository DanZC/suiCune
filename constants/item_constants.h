// item ids
// indexes for:
// - ItemNames (see data/items/names.asm)
// - ItemDescriptions (see data/items/descriptions.asm)
// - ItemAttributes (see data/items/attributes.asm)
// - ItemEffects (see engine/items/item_effects.asm)
enum {
    NO_ITEM,
    MASTER_BALL,
    ULTRA_BALL,
    BRIGHTPOWDER,
    GREAT_BALL,
    POKE_BALL,
    TOWN_MAP,
    BICYCLE,
    MOON_STONE,
    ANTIDOTE,
    BURN_HEAL,
    ICE_HEAL,
    AWAKENING,
    PARLYZ_HEAL,
    FULL_RESTORE,
    MAX_POTION,
    HYPER_POTION,
    SUPER_POTION,
    POTION,
    ESCAPE_ROPE,
    REPEL,
    MAX_ELIXER,
    FIRE_STONE,
    THUNDERSTONE,
    WATER_STONE,
    ITEM_19,
    HP_UP,
    PROTEIN,
    IRON,
    CARBOS,
    LUCKY_PUNCH,
    CALCIUM,
    RARE_CANDY,
    X_ACCURACY,
    LEAF_STONE,
    METAL_POWDER,
    NUGGET,
    POKE_DOLL,
    FULL_HEAL,
    REVIVE,
    MAX_REVIVE,
    GUARD_SPEC,
    SUPER_REPEL,
    MAX_REPEL,
    DIRE_HIT,
    ITEM_2D,
    FRESH_WATER,
    SODA_POP,
    LEMONADE,
    X_ATTACK,
    ITEM_32,
    X_DEFEND,
    X_SPEED,
    X_SPECIAL,
    COIN_CASE,
    ITEMFINDER,
    POKE_FLUTE,
    EXP_SHARE,
    OLD_ROD,
    GOOD_ROD,
    SILVER_LEAF,
    SUPER_ROD,
    PP_UP,
    ETHER,
    MAX_ETHER,
    ELIXER,
    RED_SCALE,
    SECRETPOTION,
    S_S_TICKET,
    MYSTERY_EGG,
    CLEAR_BELL,
    SILVER_WING,
    MOOMOO_MILK,
    QUICK_CLAW,
    PSNCUREBERRY,
    GOLD_LEAF,
    SOFT_SAND,
    SHARP_BEAK,
    PRZCUREBERRY,
    BURNT_BERRY,
    ICE_BERRY,
    POISON_BARB,
    KINGS_ROCK,
    BITTER_BERRY,
    MINT_BERRY,
    RED_APRICORN,
    TINYMUSHROOM,
    BIG_MUSHROOM,
    SILVERPOWDER,
    BLU_APRICORN,
    ITEM_5A,
    AMULET_COIN,
    YLW_APRICORN,
    GRN_APRICORN,
    CLEANSE_TAG,
    MYSTIC_WATER,
    TWISTEDSPOON,
    WHT_APRICORN,
    BLACKBELT_I,
    BLK_APRICORN,
    ITEM_64,
    PNK_APRICORN,
    BLACKGLASSES,
    SLOWPOKETAIL,
    PINK_BOW,
    STICK,
    SMOKE_BALL,
    NEVERMELTICE,
    MAGNET,
    MIRACLEBERRY,
    PEARL,
    BIG_PEARL,
    EVERSTONE,
    SPELL_TAG,
    RAGECANDYBAR,
    GS_BALL,
    BLUE_CARD,
    MIRACLE_SEED,
    THICK_CLUB,
    FOCUS_BAND,
    ITEM_78,
    ENERGYPOWDER,
    ENERGY_ROOT,
    HEAL_POWDER,
    REVIVAL_HERB,
    HARD_STONE,
    LUCKY_EGG,
    CARD_KEY,
    MACHINE_PART,
    EGG_TICKET,
    LOST_ITEM,
    STARDUST,
    STAR_PIECE,
    BASEMENT_KEY,
    PASS,
    ITEM_87,
    ITEM_88,
    ITEM_89,
    CHARCOAL,
    BERRY_JUICE,
    SCOPE_LENS,
    ITEM_8D,
    ITEM_8E,
    METAL_COAT,
    DRAGON_FANG,
    ITEM_91,
    LEFTOVERS,
    ITEM_93,
    ITEM_94,
    ITEM_95,
    MYSTERYBERRY,
    DRAGON_SCALE,
    BERSERK_GENE,
    ITEM_99,
    ITEM_9A,
    ITEM_9B,
    SACRED_ASH,
    HEAVY_BALL,
    FLOWER_MAIL,
    LEVEL_BALL,
    LURE_BALL,
    FAST_BALL,
    ITEM_A2,
    LIGHT_BALL,
    FRIEND_BALL,
    MOON_BALL,
    LOVE_BALL,
    NORMAL_BOX,
    GORGEOUS_BOX,
    SUN_STONE,
    POLKADOT_BOW,
    ITEM_AB,
    UP_GRADE,
    BERRY,
    GOLD_BERRY,
    SQUIRTBOTTLE,
    ITEM_B0,
    PARK_BALL,
    RAINBOW_WING,
    ITEM_B3,
    BRICK_PIECE,
    SURF_MAIL,
    LITEBLUEMAIL,
    PORTRAITMAIL,
    LOVELY_MAIL,
    EON_MAIL,
    MORPH_MAIL,
    BLUESKY_MAIL,
    MUSIC_MAIL,
    MIRAGE_MAIL,
    ITEM_BE,
};

#define NUM_ITEMS ITEM_BE

// see data/moves/tmhm_moves.asm for moves

#define TM_ITEM_OFFSET NUM_ITEMS

#define add_tm(tmNum, tmId, tmName) enum {         \
    tmName##_TMNUM = tmId,                         \
    TM_##tmName = tmName##_TMNUM + TM_ITEM_OFFSET, \
    tmNum##_MOVE = TM_##tmName,                    \
    tmNum = tmNum##_MOVE,                          \
};

add_tm(TM01, 1, DYNAMICPUNCH);
add_tm(TM02, 2, HEADBUTT);
add_tm(TM03, 3, CURSE);
add_tm(TM04, 4, ROLLOUT);
#define ITEM_C3 0xC3
#undef TM_ITEM_OFFSET
#define TM_ITEM_OFFSET (NUM_ITEMS + 1)
add_tm(TM05, 5, ROAR);
add_tm(TM06, 6, TOXIC);
add_tm(TM07, 7, ZAP_CANNON);
add_tm(TM08, 8, ROCK_SMASH);
add_tm(TM09, 9, PSYCH_UP);
add_tm(TM10, 10, HIDDEN_POWER);
add_tm(TM11, 11, SUNNY_DAY);
add_tm(TM12, 12, SWEET_SCENT);
add_tm(TM13, 13, SNORE);
add_tm(TM14, 14, BLIZZARD);
add_tm(TM15, 15, HYPER_BEAM);
add_tm(TM16, 16, ICY_WIND);
add_tm(TM17, 17, PROTECT);
add_tm(TM18, 18, RAIN_DANCE);
add_tm(TM19, 19, GIGA_DRAIN);
add_tm(TM20, 20, ENDURE);
add_tm(TM21, 21, FRUSTRATION);
add_tm(TM22, 22, SOLARBEAM);
add_tm(TM23, 23, IRON_TAIL);
add_tm(TM24, 24, DRAGONBREATH);
add_tm(TM25, 25, THUNDER);
add_tm(TM26, 26, EARTHQUAKE);
add_tm(TM27, 27, RETURN);
add_tm(TM28, 28, DIG);
#define ITEM_DC 0xDC
#undef TM_ITEM_OFFSET
#define TM_ITEM_OFFSET (NUM_ITEMS + 2)
add_tm(TM29, 29, PSYCHIC_M);
add_tm(TM30, 30, SHADOW_BALL);
add_tm(TM31, 31, MUD_SLAP);
add_tm(TM32, 32, DOUBLE_TEAM);
add_tm(TM33, 33, ICE_PUNCH);
add_tm(TM34, 34, SWAGGER);
add_tm(TM35, 35, SLEEP_TALK);
add_tm(TM36, 36, SLUDGE_BOMB);
add_tm(TM37, 37, SANDSTORM);
add_tm(TM38, 38, FIRE_BLAST);
add_tm(TM39, 39, SWIFT);
add_tm(TM40, 40, DEFENSE_CURL);
add_tm(TM41, 41, THUNDERPUNCH);
add_tm(TM42, 42, DREAM_EATER);
add_tm(TM43, 43, DETECT);
add_tm(TM44, 44, REST);
add_tm(TM45, 45, ATTRACT);
add_tm(TM46, 46, THIEF);
add_tm(TM47, 47, STEEL_WING);
add_tm(TM48, 48, FIRE_PUNCH);
add_tm(TM49, 49, FURY_CUTTER);
add_tm(TM50, 50, NIGHTMARE);

#define TM01 TM_DYNAMICPUNCH
#define NUM_TMS NIGHTMARE_TMNUM

#define add_hm(hmNum, hmId, hmName) enum {         \
    hmName##_TMNUM = hmId,                         \
    HM_##hmName = hmName##_TMNUM + TM_ITEM_OFFSET, \
    hmNum##_MOVE = HM_##hmName,                    \
    hmNum = hmNum##_MOVE,                          \
};

add_hm(HM01, 51, CUT);
add_hm(HM02, 52, FLY);
add_hm(HM03, 53, SURF);
add_hm(HM04, 54, STRENGTH);
add_hm(HM05, 55, FLASH);
add_hm(HM06, 56, WHIRLPOOL);
add_hm(HM07, 57, WATERFALL);

#define HM01 HM_CUT
#define NUM_HMS (WATERFALL_TMNUM - NUM_TMS)

#define NUM_TM_HM (NUM_TMS + NUM_HMS)
#define NUM_TM_HM_TUTOR (NUM_TM_HM + 3)

#define ITEM_FA 0xFA

#define USE_SCRIPT_VAR 0x00
#define ITEM_FROM_MEM 0xff

// leftovers from red
#define SAFARI_BALL 0x08     // MOON_STONE
#define MOON_STONE_RED 0x0a  // BURN_HEAL
#define FULL_HEAL_RED 0x34   // X_SPEED
