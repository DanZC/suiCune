#include "../../constants.h"
#include "../../engine/events/std_scripts.h"

// std scripts associated with tile collisions

// stdcoll: MACRO
// 	db \1
// 	dw (\2StdScript - StdScripts) / 3
// ENDM
#define stdcoll(_0, _1) {.coll=_0, .script=stdscript_const(_1)}

const struct StdCollisionScript TileCollisionStdScripts[] = {
    // collision type, std script
    stdcoll(COLL_BOOKSHELF,      MagazineBookshelfScript),
    stdcoll(COLL_PC,             PCScript),
    stdcoll(COLL_RADIO,          Radio1Script),
    stdcoll(COLL_TOWN_MAP,       TownMapScript),
    stdcoll(COLL_MART_SHELF,     MerchandiseShelfScript),
    stdcoll(COLL_TV,             TVScript),
    stdcoll(COLL_WINDOW,         WindowScript),
    stdcoll(COLL_INCENSE_BURNER, IncenseBurnerScript),
    {0xff, 0} // end
};
