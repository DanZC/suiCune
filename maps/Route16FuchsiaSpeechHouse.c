#include "../constants.h"
#include "../util/scripting.h"
#include "Route16FuchsiaSpeechHouse.h"
//// EVENTS
enum {
    ROUTE16FUCHSIASPEECHHOUSE_SUPER_NERD = 2,
};

const Script_fn_t Route16FuchsiaSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback Route16FuchsiaSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts Route16FuchsiaSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(Route16FuchsiaSpeechHouse_SceneScripts),
    .scene_scripts = Route16FuchsiaSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(Route16FuchsiaSpeechHouse_MapCallbacks),
    .callbacks = Route16FuchsiaSpeechHouse_MapCallbacks,
};

static const struct CoordEvent Route16FuchsiaSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent Route16FuchsiaSpeechHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &Route16FuchsiaSpeechHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &Route16FuchsiaSpeechHouseBookshelf),
};

static const struct WarpEventData Route16FuchsiaSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_16, 1),
    warp_event(3, 7, ROUTE_16, 1),
};

static const struct ObjEvent Route16FuchsiaSpeechHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_SUPER_NERD, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route16FuchsiaSpeechHouseSuperNerdScript, -1),
};

const struct MapEvents Route16FuchsiaSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(Route16FuchsiaSpeechHouse_WarpEvents),
    .warp_events = Route16FuchsiaSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(Route16FuchsiaSpeechHouse_CoordEvents),
    .coord_events = Route16FuchsiaSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(Route16FuchsiaSpeechHouse_BGEvents),
    .bg_events = Route16FuchsiaSpeechHouse_BGEvents,

    .obj_event_count = lengthof(Route16FuchsiaSpeechHouse_ObjectEvents),
    .obj_events = Route16FuchsiaSpeechHouse_ObjectEvents,
};

//// CODE

bool Route16FuchsiaSpeechHouseSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route16FuchsiaSpeechHouseSuperNerdText)
    SCRIPT_END
}
bool Route16FuchsiaSpeechHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s Route16FuchsiaSpeechHouseSuperNerdText[] = {
    text_start("If you cruise down"
        t_line "CYCLING ROAD, you"
        t_para "will end up in"
        t_line "FUCHSIA CITY."
        t_done )
    //db(0, 0) // filler
};
