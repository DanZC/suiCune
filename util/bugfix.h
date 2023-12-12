#pragma once

// Optional compiler switch for fixing bugs in Pokemon Crystal.
// By default, all logic bugs from the original game have been carried over.
// You can pass -DBUGFIX=1 to add bug fixes to the game.

#if BUGFIX
    #define BUGFIX_CONVERSION2 1
    #define BUGFIX_MEANLOOK 1
    #define BUGFIX_YESNO_OVERFLOW 1
#endif
