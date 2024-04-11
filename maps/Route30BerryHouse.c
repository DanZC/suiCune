#include "../constants.h"
#include "../util/scripting.h"
#include "Route30BerryHouse.h"
//// EVENTS
enum {
    ROUTE30BERRYHOUSE_POKEFAN_M = 2,
};

const Script_fn_t Route30BerryHouse_SceneScripts[] = {
};

const struct MapCallback Route30BerryHouse_MapCallbacks[] = {
};

const struct MapScripts Route30BerryHouse_MapScripts = {
    .scene_script_count = lengthof(Route30BerryHouse_SceneScripts),
    .scene_scripts = Route30BerryHouse_SceneScripts,

    .callback_count = lengthof(Route30BerryHouse_MapCallbacks),
    .callbacks = Route30BerryHouse_MapCallbacks,
};

static const struct CoordEvent Route30BerryHouse_CoordEvents[] = {
};

static const struct BGEvent Route30BerryHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &Route30BerryHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &Route30BerryHouseBookshelf),
};

static const struct WarpEventData Route30BerryHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_30, 1),
    warp_event(3, 7, ROUTE_30, 1),
};

static const struct ObjEvent Route30BerryHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &Route30BerryHousePokefanMScript, -1),
};

const struct MapEvents Route30BerryHouse_MapEvents = {
    .warp_event_count = lengthof(Route30BerryHouse_WarpEvents),
    .warp_events = Route30BerryHouse_WarpEvents,

    .coord_event_count = lengthof(Route30BerryHouse_CoordEvents),
    .coord_events = Route30BerryHouse_CoordEvents,

    .bg_event_count = lengthof(Route30BerryHouse_BGEvents),
    .bg_events = Route30BerryHouse_BGEvents,

    .obj_event_count = lengthof(Route30BerryHouse_ObjectEvents),
    .obj_events = Route30BerryHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route30BerryHouse.h"

bool Route30BerryHousePokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_BERRY_FROM_ROUTE_30_HOUSE)
    iftrue(GotBerry)
    writetext(Route30BerrySpeechHouseMonEatBerriesText)
    promptbutton
    verbosegiveitem(BERRY, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_BERRY_FROM_ROUTE_30_HOUSE)
GotBerry:
    writetext(Route30BerrySpeechHouseCheckTreesText)
    waitbutton
NoRoom:
    closetext
    s_end
    SCRIPT_END
}
bool Route30BerryHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s Route30BerrySpeechHouseMonEatBerriesText[] = {
    text_start("You know, #MON"
        t_line "eat BERRIES."
        t_para "Well, my #MON"
        t_line "got healthier by"
        t_cont "eating a BERRY."
        t_para "Here. I'll share"
        t_line "one with you!"
        t_done )
};
const txt_cmd_s Route30BerrySpeechHouseCheckTreesText[] = {
    text_start("Check trees for"
        t_line "BERRIES. They just"
        t_cont "drop right off."
        t_done )
    //db(0, 0) // filler
};
