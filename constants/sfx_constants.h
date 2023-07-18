#pragma once
// SFX indexes (see audio/sfx_pointers.asm)
enum {
    SFX_DEX_FANFARE_50_79,            // 00
    SFX_ITEM,                         // 01
    SFX_CAUGHT_MON,                   // 02
    SFX_POKEBALLS_PLACED_ON_TABLE,    // 03
    SFX_POTION,                       // 04
    SFX_FULL_HEAL,                    // 05
    SFX_MENU,                         // 06
    SFX_READ_TEXT,                    // 07
    SFX_READ_TEXT_2,                  // 08
    SFX_DEX_FANFARE_20_49,            // 09
    SFX_DEX_FANFARE_80_109,           // 0a
    SFX_POISON,                       // 0b
    SFX_GOT_SAFARI_BALLS,             // 0c
    SFX_BOOT_PC,                      // 0d
    SFX_SHUT_DOWN_PC,                 // 0e
    SFX_CHOOSE_PC_OPTION,             // 0f
    SFX_ESCAPE_ROPE,                  // 10
    SFX_PUSH_BUTTON,                  // 11
    SFX_SECOND_PART_OF_ITEMFINDER,    // 12
    SFX_WARP_TO,                      // 13
    SFX_WARP_FROM,                    // 14
    SFX_CHANGE_DEX_MODE,              // 15
    SFX_JUMP_OVER_LEDGE,              // 16
    SFX_GRASS_RUSTLE,                 // 17
    SFX_FLY,                          // 18
    SFX_WRONG,                        // 19
    SFX_SQUEAK,                       // 1a
    SFX_STRENGTH,                     // 1b
    SFX_BOAT,                         // 1c
    SFX_WALL_OPEN,                    // 1d
    SFX_PLACE_PUZZLE_PIECE_DOWN,      // 1e
    SFX_ENTER_DOOR,                   // 1f
    SFX_SWITCH_POKEMON,               // 20
    SFX_TALLY,                        // 21
    SFX_TRANSACTION,                  // 22
    SFX_EXIT_BUILDING,                // 23
    SFX_BUMP,                         // 24
    SFX_SAVE,                         // 25
    SFX_POKEFLUTE,                    // 26
    SFX_ELEVATOR_END,                 // 27
    SFX_THROW_BALL,                   // 28
    SFX_BALL_POOF,                    // 29
    SFX_FAINT,                        // 2a
    SFX_RUN,                          // 2b
    SFX_SLOT_MACHINE_START,           // 2c
    SFX_FANFARE,                      // 2d
    SFX_PECK,                         // 2e
    SFX_KINESIS,                      // 2f
    SFX_LICK,                         // 30
    SFX_POUND,                        // 31
    SFX_MOVE_PUZZLE_PIECE,            // 32
    SFX_COMET_PUNCH,                  // 33
    SFX_MEGA_PUNCH,                   // 34
    SFX_SCRATCH,                      // 35
    SFX_VICEGRIP,                     // 36
    SFX_RAZOR_WIND,                   // 37
    SFX_CUT,                          // 38
    SFX_WING_ATTACK,                  // 39
    SFX_WHIRLWIND,                    // 3a
    SFX_BIND,                         // 3b
    SFX_VINE_WHIP,                    // 3c
    SFX_DOUBLE_KICK,                  // 3d
    SFX_MEGA_KICK,                    // 3e
    SFX_HEADBUTT,                     // 3f
    SFX_HORN_ATTACK,                  // 40
    SFX_TACKLE,                       // 41
    SFX_POISON_STING,                 // 42
    SFX_POWDER,                       // 43
    SFX_DOUBLESLAP,                   // 44
    SFX_BITE,                         // 45
    SFX_JUMP_KICK,                    // 46
    SFX_STOMP,                        // 47
    SFX_TAIL_WHIP,                    // 48
    SFX_KARATE_CHOP,                  // 49
    SFX_SUBMISSION,                   // 4a
    SFX_WATER_GUN,                    // 4b
    SFX_SWORDS_DANCE,                 // 4c
    SFX_THUNDER,                      // 4d
    SFX_SUPERSONIC,                   // 4e
    SFX_LEER,                         // 4f
    SFX_EMBER,                        // 50
    SFX_BUBBLEBEAM,                   // 51
    SFX_HYDRO_PUMP,                   // 52
    SFX_SURF,                         // 53
    SFX_PSYBEAM,                      // 54
    SFX_CHARGE,                       // 55
    SFX_THUNDERSHOCK,                 // 56
    SFX_PSYCHIC,                      // 57
    SFX_SCREECH,                      // 58
    SFX_BONE_CLUB,                    // 59
    SFX_SHARPEN,                      // 5a
    SFX_EGG_BOMB,                     // 5b
    SFX_SING,                         // 5c
    SFX_HYPER_BEAM,                   // 5d
    SFX_SHINE,                        // 5e
    SFX_UNKNOWN_5F,                   // 5f
    SFX_UNKNOWN_60,                   // 60
    SFX_UNKNOWN_61,                   // 61
    SFX_SWITCH_POCKETS,               // 62
    SFX_UNKNOWN_63,                   // 63
    SFX_BURN,                         // 64
    SFX_TITLE_SCREEN_ENTRANCE,        // 65
    SFX_UNKNOWN_66,                   // 66
    SFX_GET_COIN_FROM_SLOTS,          // 67
    SFX_PAY_DAY,                      // 68
    SFX_METRONOME,                    // 69
    SFX_CALL,                         // 6a
    SFX_HANG_UP,                      // 6b
    SFX_NO_SIGNAL,                    // 6c
    SFX_SANDSTORM,                    // 6d
    SFX_ELEVATOR,                     // 6e
    SFX_PROTECT,                      // 6f
    SFX_SKETCH,                       // 70
    SFX_RAIN_DANCE,                   // 71
    SFX_AEROBLAST,                    // 72
    SFX_SPARK,                        // 73
    SFX_CURSE,                        // 74
    SFX_RAGE,                         // 75
    SFX_THIEF,                        // 76
    SFX_THIEF_2,                      // 77
    SFX_SPIDER_WEB,                   // 78
    SFX_MIND_READER,                  // 79
    SFX_NIGHTMARE,                    // 7a
    SFX_SNORE,                        // 7b
    SFX_SWEET_KISS,                   // 7c
    SFX_SWEET_KISS_2,                 // 7d
    SFX_BELLY_DRUM,                   // 7e
    SFX_TOXIC,                        // 7f
    SFX_SLUDGE_BOMB,                  // 80
    SFX_FORESIGHT,                    // 81
    SFX_SPITE,                        // 82
    SFX_OUTRAGE,                      // 83
    SFX_PERISH_SONG,                  // 84
    SFX_GIGA_DRAIN,                   // 85
    SFX_ATTRACT,                      // 86
    SFX_KINESIS_2,                    // 87
    SFX_ZAP_CANNON,                   // 88
    SFX_MEAN_LOOK,                    // 89
    SFX_HEAL_BELL,                    // 8a
    SFX_RETURN,                       // 8b
    SFX_EXP_BAR,                      // 8c
    SFX_MILK_DRINK,                   // 8d
    SFX_PRESENT,                      // 8e
    SFX_MORNING_SUN,                  // 8f
    SFX_LEVEL_UP,                     // 90
    SFX_KEY_ITEM,                     // 91
    SFX_FANFARE_2,                    // 92
    SFX_REGISTER_PHONE_NUMBER,        // 93
    SFX_3RD_PLACE,                    // 94
    SFX_GET_EGG_UNUSED,               // 95
    SFX_GET_EGG,                      // 96
    SFX_MOVE_DELETED,                 // 97
    SFX_2ND_PLACE,                    // 98
    SFX_1ST_PLACE,                    // 99
    SFX_CHOOSE_A_CARD,                // 9a
    SFX_GET_TM,                       // 9b
    SFX_GET_BADGE,                    // 9c
    SFX_QUIT_SLOTS,                   // 9d
    SFX_EGG_CRACK,                    // 9e
    SFX_DEX_FANFARE_LESS_THAN_20,     // 9f
    SFX_DEX_FANFARE_140_169,          // a0
    SFX_DEX_FANFARE_170_199,          // a1
    SFX_DEX_FANFARE_200_229,          // a2
    SFX_DEX_FANFARE_230_PLUS,         // a3
    SFX_EVOLVED,                      // a4
    SFX_MASTER_BALL,                  // a5
    SFX_EGG_HATCH,                    // a6
    SFX_GS_INTRO_CHARIZARD_FIREBALL,  // a7
    SFX_GS_INTRO_POKEMON_APPEARS,     // a8
    SFX_FLASH,                        // a9
    SFX_GAME_FREAK_LOGO_GS,           // aa
    SFX_NOT_VERY_EFFECTIVE,           // ab
    SFX_DAMAGE,                       // ac
    SFX_SUPER_EFFECTIVE,              // ad
    SFX_BALL_BOUNCE,                  // ae
    SFX_MOONLIGHT,                    // af
    SFX_ENCORE,                       // b0
    SFX_BEAT_UP,                      // b1
    SFX_BATON_PASS,                   // b2
    SFX_BALL_WOBBLE,                  // b3
    SFX_SWEET_SCENT,                  // b4
    SFX_SWEET_SCENT_2,                // b5
    SFX_HIT_END_OF_EXP_BAR,           // b6
    SFX_GIVE_TRADEMON,                // b7
    SFX_GET_TRADEMON,                 // b8
    SFX_TRAIN_ARRIVED,                // b9
    SFX_STOP_SLOT,                    // ba
    SFX_2_BOOPS,                      // bb
                                      // new to Crystal
    SFX_GLASS_TING,                   // bc
    SFX_GLASS_TING_2,                 // bd
    SFX_INTRO_UNOWN_1,                // be
    SFX_INTRO_UNOWN_2,                // bf
    SFX_INTRO_UNOWN_3,                // c0
    SFX_DITTO_POP_UP,                 // c1
    SFX_DITTO_TRANSFORM,              // c2
    SFX_INTRO_SUICUNE_1,              // c3
    SFX_INTRO_PICHU,                  // c4
    SFX_INTRO_SUICUNE_2,              // c5
    SFX_INTRO_SUICUNE_3,              // c6
    SFX_DITTO_BOUNCE,                 // c7
    SFX_INTRO_SUICUNE_4,              // c8
    SFX_GAME_FREAK_PRESENTS,          // c9
    SFX_TINGLE,                       // ca
    SFX_INTRO_WHOOSH,                 // cb
    SFX_TWO_PC_BEEPS,                 // cc
    SFX_4_NOTE_DITTY,                 // cd
    SFX_TWINKLE,                      // ce
    NUM_SFX,
};
