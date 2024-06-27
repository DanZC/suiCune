#include "../constants.h"
#include "../util/scripting.h"
#include "MoveDeletersHouse.h"
//// EVENTS
enum {
    MOVEDELETERSHOUSE_SUPER_NERD = 2,
};

const Script_fn_t MoveDeletersHouse_SceneScripts[] = {
    0,
};

const struct MapCallback MoveDeletersHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts MoveDeletersHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(MoveDeletersHouse_SceneScripts),
    .scene_scripts = MoveDeletersHouse_SceneScripts,

    .callback_count = 0, // lengthof(MoveDeletersHouse_MapCallbacks),
    .callbacks = MoveDeletersHouse_MapCallbacks,
};

static const struct CoordEvent MoveDeletersHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent MoveDeletersHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &MoveDeletersHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &MoveDeletersHouseBookshelf),
};

static const struct WarpEventData MoveDeletersHouse_WarpEvents[] = {
    warp_event(2, 7, BLACKTHORN_CITY, 6),
    warp_event(3, 7, BLACKTHORN_CITY, 6),
};

static const struct ObjEvent MoveDeletersHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MoveDeleter, -1),
};

const struct MapEvents MoveDeletersHouse_MapEvents = {
    .warp_event_count = lengthof(MoveDeletersHouse_WarpEvents),
    .warp_events = MoveDeletersHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(MoveDeletersHouse_CoordEvents),
    .coord_events = MoveDeletersHouse_CoordEvents,

    .bg_event_count = lengthof(MoveDeletersHouse_BGEvents),
    .bg_events = MoveDeletersHouse_BGEvents,

    .obj_event_count = lengthof(MoveDeletersHouse_ObjectEvents),
    .obj_events = MoveDeletersHouse_ObjectEvents,
};

//// CODE

bool MoveDeleter(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    special(MoveDeletion)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool MoveDeletersHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    //db(0, 0) // filler
    SCRIPT_END
}
