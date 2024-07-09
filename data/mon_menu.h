#pragma once

// MonMenuOptionStrings indexes
enum {
    MONMENUVALUE_STATS = 1, // 1
    MONMENUVALUE_SWITCH,    // 2
    MONMENUVALUE_ITEM,      // 3
    MONMENUVALUE_CANCEL,    // 4
    MONMENUVALUE_MOVE,      // 5
    MONMENUVALUE_MAIL,      // 6
    MONMENUVALUE_ERROR,     // 7
};
#define NUM_MONMENUVALUES MONMENUVALUE_ERROR

extern const char *MonMenuOptionStrings[];

extern const struct MonMenuOption MonMenuOptions[];
