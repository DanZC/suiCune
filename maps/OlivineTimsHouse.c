#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineTimsHouse.h"
//// EVENTS
enum {
    OLIVINETIMSHOUSE_TIM = 2,
};

const Script_fn_t OlivineTimsHouse_SceneScripts[] = {
    0,
};

const struct MapCallback OlivineTimsHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivineTimsHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivineTimsHouse_SceneScripts),
    .scene_scripts = OlivineTimsHouse_SceneScripts,

    .callback_count = 0, // lengthof(OlivineTimsHouse_MapCallbacks),
    .callbacks = OlivineTimsHouse_MapCallbacks,
};

static const struct CoordEvent OlivineTimsHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivineTimsHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &TimsHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &TimsHouseBookshelf),
};

static const struct WarpEventData OlivineTimsHouse_WarpEvents[] = {
    warp_event(2, 7, OLIVINE_CITY, 3),
    warp_event(3, 7, OLIVINE_CITY, 3),
};

static const struct ObjEvent OlivineTimsHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_FISHING_GURU, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Tim, -1),
};

const struct MapEvents OlivineTimsHouse_MapEvents = {
    .warp_event_count = lengthof(OlivineTimsHouse_WarpEvents),
    .warp_events = OlivineTimsHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivineTimsHouse_CoordEvents),
    .coord_events = OlivineTimsHouse_CoordEvents,

    .bg_event_count = lengthof(OlivineTimsHouse_BGEvents),
    .bg_events = OlivineTimsHouse_BGEvents,

    .obj_event_count = lengthof(OlivineTimsHouse_ObjectEvents),
    .obj_events = OlivineTimsHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivineTimsHouse.h"

bool Tim(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    trade(NPC_TRADE_TIM)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool TimsHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    //db(0, 0) // filler
    SCRIPT_END
}
