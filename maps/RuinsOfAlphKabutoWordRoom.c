#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphKabutoWordRoom.h"
//// EVENTS
const Script_fn_t RuinsOfAlphKabutoWordRoom_SceneScripts[] = {
    0,
};

const struct MapCallback RuinsOfAlphKabutoWordRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts RuinsOfAlphKabutoWordRoom_MapScripts = {
    .scene_script_count = 0, // lengthof(RuinsOfAlphKabutoWordRoom_SceneScripts),
    .scene_scripts = RuinsOfAlphKabutoWordRoom_SceneScripts,

    .callback_count = 0, // lengthof(RuinsOfAlphKabutoWordRoom_MapCallbacks),
    .callbacks = RuinsOfAlphKabutoWordRoom_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphKabutoWordRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphKabutoWordRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData RuinsOfAlphKabutoWordRoom_WarpEvents[] = {
    warp_event(9, 5, RUINS_OF_ALPH_KABUTO_ITEM_ROOM, 3),
    warp_event(10, 5, RUINS_OF_ALPH_KABUTO_ITEM_ROOM, 4),
    warp_event(17, 11, RUINS_OF_ALPH_INNER_CHAMBER, 4),
};

static const struct ObjEvent RuinsOfAlphKabutoWordRoom_ObjectEvents[] = {
    0,
};

const struct MapEvents RuinsOfAlphKabutoWordRoom_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphKabutoWordRoom_WarpEvents),
    .warp_events = RuinsOfAlphKabutoWordRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphKabutoWordRoom_CoordEvents),
    .coord_events = RuinsOfAlphKabutoWordRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(RuinsOfAlphKabutoWordRoom_BGEvents),
    .bg_events = RuinsOfAlphKabutoWordRoom_BGEvents,

    .obj_event_count = 0, // lengthof(RuinsOfAlphKabutoWordRoom_ObjectEvents),
    .obj_events = RuinsOfAlphKabutoWordRoom_ObjectEvents,
};

//// CODE

    //db(0, 0) // filler
