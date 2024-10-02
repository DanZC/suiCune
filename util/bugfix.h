#pragma once

// Optional compiler switch for fixing bugs in Pokemon Crystal.
// By default, all logic bugs from the original game have been carried over.
// You can pass -DBUGFIX=1 to add bug fixes to the game.

#if BUGFIX
    #define BUGFIX_CONVERSION2 1
    #define BUGFIX_MEANLOOK 1
    #define BUGFIX_YESNO_OVERFLOW 1
    #define BUGFIX_ANIMCMDCLEAROBJ 1
    #define BUGFIX_BELLYDRUM 1
    #define BUGFIX_BEATUP_DESYNC 1
    #define BUGFIX_BEAT_UP_FAIL_TEXT 1
    #define BUGFIX_TRANSFORM_SKETCH 1
    #define BUGFIX_DEFENSE_DOWN_DUP_EFFECTCHANCE 1
    #define BUGFIX_EFFECTCHANCE 1
    #define BUGFIX_CHECKHIDDENOPPONENT 1
    #define BUGFIX_NOCLIP_SWIM 1
    #define BUGFIX_HAIRCUT_PCT_FAIL 1
    #define BUGFIX_CREDITS_HINMENU_NOT_PRESERVED 1
    #define BUGFIX_OWN_MON_OT_CHECK_NAME_LENGTH 1
    #define BUGFIX_HOFPC_DISPLAY_WIN_COUNT 1
    #define BUGFIX_HALLOFFAME_RANKING_HEALINGS 1
    #define BUGFIX_BRN_PSN_PAR_CATCH_RATE 1
    #define BUGFIX_HELD_ITEM_CATCH_CHANCE 1
    #define BUGFIX_CAUGHT_TRANSFORMED_MON_BECOMES_DITTO 1
    #define BUGFIX_MOON_BALL_WRONG_ITEM 1
    #define BUGFIX_LOVE_BALL_SAME_GENDER 1
    #define BUGFIX_FAST_BALL_INCOMPLETE_CHECK 1
    #define BUGFIX_BETTER_DUNGEON_ROOF_PALS 1
    #define BUGFIX_OPTIONS_MENU_JOYPAD 1
#else
    #define BUGFIX_BETTER_DUNGEON_ROOF_PALS 1
    #define BUGFIX_OPTIONS_MENU_JOYPAD 1
#endif
