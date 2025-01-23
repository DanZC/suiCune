// sprite_anim_struct members (see macros/wram.asm)
enum {
    SPRITEANIMSTRUCT_INDEX,
    SPRITEANIMSTRUCT_FRAMESET_ID,
    SPRITEANIMSTRUCT_ANIM_SEQ_ID,
    SPRITEANIMSTRUCT_TILE_ID,
    SPRITEANIMSTRUCT_XCOORD,
    SPRITEANIMSTRUCT_YCOORD,
    SPRITEANIMSTRUCT_XOFFSET,
    SPRITEANIMSTRUCT_YOFFSET,
    SPRITEANIMSTRUCT_DURATION,
    SPRITEANIMSTRUCT_DURATIONOFFSET,
    SPRITEANIMSTRUCT_FRAME,
    SPRITEANIMSTRUCT_JUMPTABLE_INDEX,
    SPRITEANIMSTRUCT_VAR1,
    SPRITEANIMSTRUCT_VAR2,
    SPRITEANIMSTRUCT_VAR3,
    SPRITEANIMSTRUCT_VAR4,
    SPRITEANIMSTRUCT_LENGTH,
};
#define NUM_SPRITE_ANIM_STRUCTS 10  // see wSpriteAnimationStructs

// wSpriteAnimDict keys (see wram.asm)
// UnusedSpriteAnimGFX indexes (see data/sprite_anims/unused_gfx.asm)
enum {
    SPRITE_ANIM_DICT_DEFAULT,          // 0
    SPRITE_ANIM_DICT_TEXT_CURSOR = 5,  // 5
    SPRITE_ANIM_DICT_GS_SPLASH,        // 6
    SPRITE_ANIM_DICT_SLOTS,            // 7
    SPRITE_ANIM_DICT_ARROW_CURSOR,     // 8
    NUM_SPRITE_ANIM_GFX,
};

// wSpriteAnimDict size (see wram.asm)
#define NUM_SPRITEANIMDICT_ENTRIES 10

// SpriteAnimSeqData indexes (see data/sprite_anims/#define s ences.asm)
enum {
    SPRITE_ANIM_INDEX_PARTY_MON,
    SPRITE_ANIM_INDEX_GS_TITLE_TRAIL,
    SPRITE_ANIM_INDEX_NAMING_SCREEN_CURSOR,
    SPRITE_ANIM_INDEX_GAMEFREAK_LOGO,
    SPRITE_ANIM_INDEX_GS_GAMEFREAK_LOGO_STAR,
    SPRITE_ANIM_INDEX_GS_GAMEFREAK_LOGO_SPARKLE,
    SPRITE_ANIM_INDEX_SLOTS_GOLEM,
    SPRITE_ANIM_INDEX_SLOTS_CHANSEY,
    SPRITE_ANIM_INDEX_SLOTS_EGG,
    SPRITE_ANIM_INDEX_COMPOSE_MAIL_CURSOR,
    SPRITE_ANIM_INDEX_RED_WALK,
    SPRITE_ANIM_INDEX_UNUSED_CURSOR,
    SPRITE_ANIM_INDEX_MEMORY_GAME_CURSOR,
    SPRITE_ANIM_INDEX_POKEGEAR_ARROW,
    SPRITE_ANIM_INDEX_TRADE_POKE_BALL,
    SPRITE_ANIM_INDEX_TRADE_POOF,
    SPRITE_ANIM_INDEX_TRADE_TUBE_BULGE,
    SPRITE_ANIM_INDEX_TRADEMON_ICON,
    SPRITE_ANIM_INDEX_TRADEMON_BUBBLE,
    SPRITE_ANIM_INDEX_EVOLUTION_BALL_OF_LIGHT,
    SPRITE_ANIM_INDEX_RADIO_TUNING_KNOB,
    SPRITE_ANIM_INDEX_MAGNET_TRAIN_RED,
    SPRITE_ANIM_INDEX_LEAF,
    SPRITE_ANIM_INDEX_CUT_TREE,
    SPRITE_ANIM_INDEX_FLY_LEAF,
    SPRITE_ANIM_INDEX_EGG_CRACK,
    SPRITE_ANIM_INDEX_GS_INTRO_HO_OH_LUGIA,
    SPRITE_ANIM_INDEX_HEADBUTT,
    SPRITE_ANIM_INDEX_EGG_HATCH,
    SPRITE_ANIM_INDEX_EZCHAT_CURSOR,
    SPRITE_ANIM_INDEX_BLUE_WALK,
    SPRITE_ANIM_INDEX_MAGNET_TRAIN_BLUE,
    SPRITE_ANIM_INDEX_MOBILE_TRADE_SENT_BALL,
    SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_BALL,
    SPRITE_ANIM_INDEX_MOBILE_TRADE_CABLE_BULGE,
    SPRITE_ANIM_INDEX_MOBILE_TRADE_SENT_PULSE,
    SPRITE_ANIM_INDEX_MOBILE_TRADE_OT_PULSE,
    SPRITE_ANIM_INDEX_MOBILE_TRADE_PING,
    SPRITE_ANIM_INDEX_INTRO_SUICUNE,
    SPRITE_ANIM_INDEX_INTRO_PICHU,
    SPRITE_ANIM_INDEX_INTRO_WOOPER,
    SPRITE_ANIM_INDEX_INTRO_UNOWN,
    SPRITE_ANIM_INDEX_INTRO_UNOWN_F,
    SPRITE_ANIM_INDEX_INTRO_SUICUNE_AWAY,
    SPRITE_ANIM_INDEX_CELEBI,
    NUM_SPRITE_ANIM_INDEXES,
};

// DoAnimFrame.Jumptable indexes (see engine/gfx/sprite_anims.asm)
enum {
    SPRITE_ANIM_SEQ_NULL,
    SPRITE_ANIM_SEQ_PARTY_MON,
    SPRITE_ANIM_SEQ_PARTY_MON_SWITCH,
    SPRITE_ANIM_SEQ_PARTY_MON_SELECTED,
    SPRITE_ANIM_SEQ_GS_TITLE_TRAIL,
    SPRITE_ANIM_SEQ_NAMING_SCREEN_CURSOR,
    SPRITE_ANIM_SEQ_GAMEFREAK_LOGO,
    SPRITE_ANIM_SEQ_GS_GAMEFREAK_LOGO_STAR,
    SPRITE_ANIM_SEQ_GS_GAMEFREAK_LOGO_SPARKLE,
    SPRITE_ANIM_SEQ_SLOTS_GOLEM,
    SPRITE_ANIM_SEQ_SLOTS_CHANSEY,
    SPRITE_ANIM_SEQ_SLOTS_EGG,
    SPRITE_ANIM_SEQ_MAIL_CURSOR,
    SPRITE_ANIM_SEQ_UNUSED_CURSOR,
    SPRITE_ANIM_SEQ_MEMORY_GAME_CURSOR,
    SPRITE_ANIM_SEQ_POKEGEAR_ARROW,
    SPRITE_ANIM_SEQ_TRADE_POKE_BALL,
    SPRITE_ANIM_SEQ_TRADE_TUBE_BULGE,
    SPRITE_ANIM_SEQ_TRADEMON_IN_TUBE,
    SPRITE_ANIM_SEQ_REVEAL_NEW_MON,
    SPRITE_ANIM_SEQ_RADIO_TUNING_KNOB,
    SPRITE_ANIM_SEQ_CUT_LEAVES,
    SPRITE_ANIM_SEQ_FLY_FROM,
    SPRITE_ANIM_SEQ_FLY_LEAF,
    SPRITE_ANIM_SEQ_FLY_TO,
    SPRITE_ANIM_SEQ_GS_INTRO_HO_OH_LUGIA,
    SPRITE_ANIM_SEQ_EZCHAT_CURSOR,
    SPRITE_ANIM_SEQ_MOBILE_TRADE_SENT_PULSE,
    SPRITE_ANIM_SEQ_MOBILE_TRADE_OT_PULSE,
    SPRITE_ANIM_SEQ_INTRO_SUICUNE,
    SPRITE_ANIM_SEQ_INTRO_PICHU_WOOPER,
    SPRITE_ANIM_SEQ_CELEBI,
    SPRITE_ANIM_SEQ_INTRO_UNOWN,
    SPRITE_ANIM_SEQ_INTRO_UNOWN_F,
    SPRITE_ANIM_SEQ_INTRO_SUICUNE_AWAY,
    NUM_SPRITE_ANIM_SEQS,
};

// SpriteAnimFrameData indexes (see data/sprite_anims/framesets.asm)
enum {
    SPRITE_ANIM_FRAMESET_00,
    SPRITE_ANIM_FRAMESET_PARTY_MON,
    SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_MAIL,
    SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_ITEM,
    SPRITE_ANIM_FRAMESET_PARTY_MON_FAST,
    SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_MAIL_FAST,
    SPRITE_ANIM_FRAMESET_PARTY_MON_WITH_ITEM_FAST,
    SPRITE_ANIM_FRAMESET_GS_TITLE_TRAIL,
    SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR,
    SPRITE_ANIM_FRAMESET_TEXT_ENTRY_CURSOR_BIG,
    SPRITE_ANIM_FRAMESET_GAMEFREAK_LOGO,
    SPRITE_ANIM_FRAMESET_GS_GAMEFREAK_LOGO_STAR,
    SPRITE_ANIM_FRAMESET_GS_GAMEFREAK_LOGO_SPARKLE,
    SPRITE_ANIM_FRAMESET_SLOTS_GOLEM,
    SPRITE_ANIM_FRAMESET_SLOTS_CHANSEY,
    SPRITE_ANIM_FRAMESET_SLOTS_CHANSEY_2,
    SPRITE_ANIM_FRAMESET_SLOTS_EGG,
    SPRITE_ANIM_FRAMESET_RED_WALK,
    SPRITE_ANIM_FRAMESET_STILL_CURSOR,
    SPRITE_ANIM_FRAMESET_TRADE_POKE_BALL,
    SPRITE_ANIM_FRAMESET_TRADE_POKE_BALL_WOBBLE,
    SPRITE_ANIM_FRAMESET_TRADE_POOF,
    SPRITE_ANIM_FRAMESET_TRADE_TUBE_BULGE,
    SPRITE_ANIM_FRAMESET_TRADEMON_ICON,
    SPRITE_ANIM_FRAMESET_TRADEMON_BUBBLE,
    SPRITE_ANIM_FRAMESET_EVOLUTION_BALL_OF_LIGHT,
    SPRITE_ANIM_FRAMESET_RADIO_TUNING_KNOB,
    SPRITE_ANIM_FRAMESET_MAGNET_TRAIN_RED,
    SPRITE_ANIM_FRAMESET_UNUSED_1C,
    SPRITE_ANIM_FRAMESET_LEAF,
    SPRITE_ANIM_FRAMESET_CUT_TREE,
    SPRITE_ANIM_FRAMESET_EGG_CRACK,
    SPRITE_ANIM_FRAMESET_EGG_HATCH_1,
    SPRITE_ANIM_FRAMESET_EGG_HATCH_2,
    SPRITE_ANIM_FRAMESET_EGG_HATCH_3,
    SPRITE_ANIM_FRAMESET_EGG_HATCH_4,
    SPRITE_ANIM_FRAMESET_GS_INTRO_HO_OH_LUGIA,
    SPRITE_ANIM_FRAMESET_HEADBUTT,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_1,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_2,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_3,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_4,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_5,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_6,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_7,
    SPRITE_ANIM_FRAMESET_BLUE_WALK,
    SPRITE_ANIM_FRAMESET_MAGNET_TRAIN_BLUE,
    SPRITE_ANIM_FRAMESET_MOBILE_TRADE_SENT_BALL,
    SPRITE_ANIM_FRAMESET_MOBILE_TRADE_OT_BALL,
    SPRITE_ANIM_FRAMESET_MOBILE_TRADE_CABLE_BULGE,
    SPRITE_ANIM_FRAMESET_MOBILE_TRADE_SENT_PULSE,
    SPRITE_ANIM_FRAMESET_MOBILE_TRADE_OT_PULSE,
    SPRITE_ANIM_FRAMESET_MOBILE_TRADE_PING,
    SPRITE_ANIM_FRAMESET_INTRO_SUICUNE,
    SPRITE_ANIM_FRAMESET_INTRO_SUICUNE_2,
    SPRITE_ANIM_FRAMESET_INTRO_PICHU,
    SPRITE_ANIM_FRAMESET_INTRO_WOOPER,
    SPRITE_ANIM_FRAMESET_INTRO_UNOWN_1,
    SPRITE_ANIM_FRAMESET_INTRO_UNOWN_2,
    SPRITE_ANIM_FRAMESET_INTRO_UNOWN_3,
    SPRITE_ANIM_FRAMESET_INTRO_UNOWN_4,
    SPRITE_ANIM_FRAMESET_INTRO_UNOWN_F_2,
    SPRITE_ANIM_FRAMESET_INTRO_SUICUNE_AWAY,
    SPRITE_ANIM_FRAMESET_INTRO_UNOWN_F,
    SPRITE_ANIM_FRAMESET_CELEBI_LEFT,
    SPRITE_ANIM_FRAMESET_CELEBI_RIGHT,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_8,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_9,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_10,
    SPRITE_ANIM_FRAMESET_EZCHAT_CURSOR_CUSTOM_BOX,
    NUM_SPRITE_ANIM_FRAMESETS,
};

// SpriteAnimOAMData indexes (see data/sprite_anims/oam.asm)
enum {
    SPRITE_ANIM_OAMSET_RED_WALK_1,
    SPRITE_ANIM_OAMSET_RED_WALK_2,
    SPRITE_ANIM_OAMSET_GS_INTRO_BUBBLE_1,
    SPRITE_ANIM_OAMSET_GS_INTRO_BUBBLE_2,
    SPRITE_ANIM_OAMSET_GS_INTRO_SHELLDER_1,
    SPRITE_ANIM_OAMSET_GS_INTRO_SHELLDER_2,
    SPRITE_ANIM_OAMSET_GS_INTRO_MAGIKARP_1,
    SPRITE_ANIM_OAMSET_GS_INTRO_MAGIKARP_2,
    SPRITE_ANIM_OAMSET_GS_INTRO_UNUSED_LAPRAS,
    SPRITE_ANIM_OAMSET_GS_INTRO_LAPRAS_1,
    SPRITE_ANIM_OAMSET_GS_INTRO_LAPRAS_2,
    SPRITE_ANIM_OAMSET_GS_INTRO_LAPRAS_3,
    SPRITE_ANIM_OAMSET_GS_INTRO_NOTE,
    SPRITE_ANIM_OAMSET_GS_INTRO_INVISIBLE_NOTE,
    SPRITE_ANIM_OAMSET_GS_INTRO_JIGGLYPUFF_1,
    SPRITE_ANIM_OAMSET_GS_INTRO_JIGGLYPUFF_2,
    SPRITE_ANIM_OAMSET_GS_INTRO_JIGGLYPUFF_3,
    SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_1,
    SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_2,
    SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_3,
    SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_4,
    SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_TAIL_1,
    SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_TAIL_2,
    SPRITE_ANIM_OAMSET_GS_INTRO_PIKACHU_TAIL_3,
    SPRITE_ANIM_OAMSET_GS_INTRO_SMALL_FIREBALL,
    SPRITE_ANIM_OAMSET_GS_INTRO_MED_FIREBALL,
    SPRITE_ANIM_OAMSET_GS_INTRO_BIG_FIREBALL,
    SPRITE_ANIM_OAMSET_GS_INTRO_CHIKORITA,
    SPRITE_ANIM_OAMSET_GS_INTRO_CYNDAQUIL,
    SPRITE_ANIM_OAMSET_GS_INTRO_TOTODILE,
    SPRITE_ANIM_OAMSET_GS_TITLE_TRAIL_1,
    SPRITE_ANIM_OAMSET_GS_TITLE_TRAIL_2,
    SPRITE_ANIM_OAMSET_TEXT_ENTRY_CURSOR,
    SPRITE_ANIM_OAMSET_TEXT_ENTRY_CURSOR_BIG,
    SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO,
    SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_STAR,
    SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_1,
    SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_2,
    SPRITE_ANIM_OAMSET_GS_GAMEFREAK_LOGO_SPARKLE_3,
    SPRITE_ANIM_OAMSET_SLOTS_GOLEM_1,
    SPRITE_ANIM_OAMSET_SLOTS_GOLEM_2,
    SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_1,
    SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_2,
    SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_3,
    SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_4,
    SPRITE_ANIM_OAMSET_SLOTS_CHANSEY_5,
    SPRITE_ANIM_OAMSET_SLOTS_EGG,
    SPRITE_ANIM_OAMSET_STILL_CURSOR,
    SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_1,
    SPRITE_ANIM_OAMSET_TRADE_POKE_BALL_2,
    SPRITE_ANIM_OAMSET_TRADE_POOF_1,
    SPRITE_ANIM_OAMSET_TRADE_POOF_2,
    SPRITE_ANIM_OAMSET_TRADE_POOF_3,
    SPRITE_ANIM_OAMSET_TRADE_TUBE_BULGE_1,
    SPRITE_ANIM_OAMSET_TRADE_TUBE_BULGE_2,
    SPRITE_ANIM_OAMSET_TRADEMON_ICON_1,
    SPRITE_ANIM_OAMSET_TRADEMON_ICON_2,
    SPRITE_ANIM_OAMSET_TRADEMON_BUBBLE,
    SPRITE_ANIM_OAMSET_EVOLUTION_BALL_OF_LIGHT_1,
    SPRITE_ANIM_OAMSET_EVOLUTION_BALL_OF_LIGHT_2,
    SPRITE_ANIM_OAMSET_RADIO_TUNING_KNOB,
    SPRITE_ANIM_OAMSET_PARTY_MON_WITH_MAIL_1,
    SPRITE_ANIM_OAMSET_PARTY_MON_WITH_MAIL_2,
    SPRITE_ANIM_OAMSET_PARTY_MON_WITH_ITEM_1,
    SPRITE_ANIM_OAMSET_PARTY_MON_WITH_ITEM_2,
    SPRITE_ANIM_OAMSET_MAGNET_TRAIN_RED_1,
    SPRITE_ANIM_OAMSET_MAGNET_TRAIN_RED_2,
    SPRITE_ANIM_OAMSET_UNUSED_43,
    SPRITE_ANIM_OAMSET_UNUSED_44,
    SPRITE_ANIM_OAMSET_UNUSED_45,
    SPRITE_ANIM_OAMSET_UNUSED_46,
    SPRITE_ANIM_OAMSET_UNUSED_47,
    SPRITE_ANIM_OAMSET_UNUSED_48,
    SPRITE_ANIM_OAMSET_UNUSED_49,
    SPRITE_ANIM_OAMSET_UNUSED_4A,
    SPRITE_ANIM_OAMSET_UNUSED_4B,
    SPRITE_ANIM_OAMSET_UNUSED_4C,
    SPRITE_ANIM_OAMSET_UNUSED_4D,
    SPRITE_ANIM_OAMSET_UNUSED_4E,
    SPRITE_ANIM_OAMSET_LEAF,
    SPRITE_ANIM_OAMSET_TREE_1,
    SPRITE_ANIM_OAMSET_CUT_TREE_2,
    SPRITE_ANIM_OAMSET_CUT_TREE_3,
    SPRITE_ANIM_OAMSET_CUT_TREE_4,
    SPRITE_ANIM_OAMSET_EGG_CRACK,
    SPRITE_ANIM_OAMSET_EGG_HATCH,
    SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_1,
    SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_2,
    SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_3,
    SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_4,
    SPRITE_ANIM_OAMSET_GS_INTRO_HO_OH_LUGIA_5,
    SPRITE_ANIM_OAMSET_HEADBUTT_TREE_2,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_1,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_2,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_3,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_4,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_5,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_6,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_7,
    SPRITE_ANIM_OAMSET_BLUE_WALK_1,
    SPRITE_ANIM_OAMSET_BLUE_WALK_2,
    SPRITE_ANIM_OAMSET_MAGNET_TRAIN_BLUE_1,
    SPRITE_ANIM_OAMSET_MAGNET_TRAIN_BLUE_2,
    SPRITE_ANIM_OAMSET_MOBILE_TRADE_CABLE_BULGE_1,
    SPRITE_ANIM_OAMSET_MOBILE_TRADE_CABLE_BULGE_2,
    SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_1,
    SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_2,
    SPRITE_ANIM_OAMSET_MOBILE_TRADE_PING_3,
    SPRITE_ANIM_OAMSET_MOBILE_TRADE_SENT_PULSE,
    SPRITE_ANIM_OAMSET_MOBILE_TRADE_OT_PULSE,
    SPRITE_ANIM_OAMSET_INTRO_SUICUNE_1,
    SPRITE_ANIM_OAMSET_INTRO_SUICUNE_2,
    SPRITE_ANIM_OAMSET_INTRO_SUICUNE_3,
    SPRITE_ANIM_OAMSET_INTRO_SUICUNE_4,
    SPRITE_ANIM_OAMSET_INTRO_PICHU_1,
    SPRITE_ANIM_OAMSET_INTRO_PICHU_2,
    SPRITE_ANIM_OAMSET_INTRO_PICHU_3,
    SPRITE_ANIM_OAMSET_INTRO_WOOPER,
    SPRITE_ANIM_OAMSET_INTRO_UNOWN_1,
    SPRITE_ANIM_OAMSET_INTRO_UNOWN_2,
    SPRITE_ANIM_OAMSET_INTRO_UNOWN_3,
    SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_1,
    SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_2,
    SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_3,
    SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_4,
    SPRITE_ANIM_OAMSET_INTRO_UNOWN_F_2_5,
    SPRITE_ANIM_OAMSET_INTRO_SUICUNE_AWAY,
    SPRITE_ANIM_OAMSET_CELEBI_1,
    SPRITE_ANIM_OAMSET_CELEBI_2,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_1,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_2,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_3,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_4,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_5,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_6,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_7,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_8,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_9,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_10,
    SPRITE_ANIM_OAMSET_GAMEFREAK_LOGO_11,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_8,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_9,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_10,
    SPRITE_ANIM_OAMSET_EZCHAT_CURSOR_CUSTOM_BOX,
    NUM_SPRITE_ANIM_OAMSETS,
};
