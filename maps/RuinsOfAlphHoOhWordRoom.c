#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphHoOhWordRoom.h"
//// EVENTS
const Script_fn_t RuinsOfAlphHoOhWordRoom_SceneScripts[] = {
    0,
};

const struct MapCallback RuinsOfAlphHoOhWordRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts RuinsOfAlphHoOhWordRoom_MapScripts = {
    .scene_script_count = 0, // lengthof(RuinsOfAlphHoOhWordRoom_SceneScripts),
    .scene_scripts = RuinsOfAlphHoOhWordRoom_SceneScripts,

    .callback_count = 0, // lengthof(RuinsOfAlphHoOhWordRoom_MapCallbacks),
    .callbacks = RuinsOfAlphHoOhWordRoom_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphHoOhWordRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphHoOhWordRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData RuinsOfAlphHoOhWordRoom_WarpEvents[] = {
    warp_event(9, 9, RUINS_OF_ALPH_HO_OH_ITEM_ROOM, 3),
    warp_event(10, 9, RUINS_OF_ALPH_HO_OH_ITEM_ROOM, 4),
    warp_event(17, 21, RUINS_OF_ALPH_INNER_CHAMBER, 2),
};

static const struct ObjEvent RuinsOfAlphHoOhWordRoom_ObjectEvents[] = {
    0,
};

const struct MapEvents RuinsOfAlphHoOhWordRoom_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphHoOhWordRoom_WarpEvents),
    .warp_events = RuinsOfAlphHoOhWordRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphHoOhWordRoom_CoordEvents),
    .coord_events = RuinsOfAlphHoOhWordRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(RuinsOfAlphHoOhWordRoom_BGEvents),
    .bg_events = RuinsOfAlphHoOhWordRoom_BGEvents,

    .obj_event_count = 0, // lengthof(RuinsOfAlphHoOhWordRoom_ObjectEvents),
    .obj_events = RuinsOfAlphHoOhWordRoom_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphHoOhWordRoom.h"

    //db(0, 0) // filler
