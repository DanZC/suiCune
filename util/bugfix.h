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
    #define BUGFIX_TRANSFORM_SKETCH 1
    #define BUGFIX_DEFENSE_DOWN_DUP_EFFECTCHANCE 1
    #define BUGFIX_NOCLIP_SWIM 1
    #define BUGFIX_BETTER_DUNGEON_ROOF_PALS 1
#else
    #define BUGFIX_BETTER_DUNGEON_ROOF_PALS 1
#endif
