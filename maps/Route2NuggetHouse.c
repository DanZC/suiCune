#include "../constants.h"
#include "../util/scripting.h"
#include "Route2NuggetHouse.h"
//// EVENTS
enum {
    ROUTE2NUGGETHOUSE_FISHER = 2,
};

const Script_fn_t Route2NuggetHouse_SceneScripts[] = {
    0,
};

const struct MapCallback Route2NuggetHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts Route2NuggetHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(Route2NuggetHouse_SceneScripts),
    .scene_scripts = Route2NuggetHouse_SceneScripts,

    .callback_count = 0, // lengthof(Route2NuggetHouse_MapCallbacks),
    .callbacks = Route2NuggetHouse_MapCallbacks,
};

static const struct CoordEvent Route2NuggetHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent Route2NuggetHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData Route2NuggetHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_2, 1),
    warp_event(3, 7, ROUTE_2, 1),
};

static const struct ObjEvent Route2NuggetHouse_ObjectEvents[] = {
    object_event(2, 4, SPRITE_FISHER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 2, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route2NuggetHouseFisherScript, -1),
};

const struct MapEvents Route2NuggetHouse_MapEvents = {
    .warp_event_count = lengthof(Route2NuggetHouse_WarpEvents),
    .warp_events = Route2NuggetHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(Route2NuggetHouse_CoordEvents),
    .coord_events = Route2NuggetHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(Route2NuggetHouse_BGEvents),
    .bg_events = Route2NuggetHouse_BGEvents,

    .obj_event_count = lengthof(Route2NuggetHouse_ObjectEvents),
    .obj_events = Route2NuggetHouse_ObjectEvents,
};

//// CODE

bool Route2NuggetHouseFisherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_NUGGET_FROM_GUY)
    iftrue(GotNugget)
    writetext(Route2NuggetHouseFisherText)
    promptbutton
    verbosegiveitem(NUGGET, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_NUGGET_FROM_GUY)
GotNugget:
    writetext(Route2NuggetHouseFisherText_GotNugget)
    waitbutton
NoRoom:
    closetext
    s_end
    SCRIPT_END
}
bool Route2NuggetHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s Route2NuggetHouseFisherText[] = {
    text_start("Hi! Wow, I'm glad"
        t_line "to see you."
        t_para "You're the first"
        t_line "visitor I've had"
        t_cont "in a long time."
        t_para "I'm super-happy!"
        t_line "Let me give you a"
        t_cont "little present."
        t_done )
};
const txt_cmd_s Route2NuggetHouseFisherText_GotNugget[] = {
    text_start("That's a NUGGET."
        t_para "I can't give you"
        t_line "any nuggets of"
        t_para "wisdom, so that'll"
        t_line "have to do!"
        t_done )
    //db(0, 0) // filler
};
