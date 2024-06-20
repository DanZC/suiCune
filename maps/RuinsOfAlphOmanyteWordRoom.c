#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphOmanyteWordRoom.h"
//// EVENTS
const Script_fn_t RuinsOfAlphOmanyteWordRoom_SceneScripts[] = {
    0,
};

const struct MapCallback RuinsOfAlphOmanyteWordRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts RuinsOfAlphOmanyteWordRoom_MapScripts = {
    .scene_script_count = 0, // lengthof(RuinsOfAlphOmanyteWordRoom_SceneScripts),
    .scene_scripts = RuinsOfAlphOmanyteWordRoom_SceneScripts,

    .callback_count = 0, // lengthof(RuinsOfAlphOmanyteWordRoom_MapCallbacks),
    .callbacks = RuinsOfAlphOmanyteWordRoom_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphOmanyteWordRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphOmanyteWordRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData RuinsOfAlphOmanyteWordRoom_WarpEvents[] = {
    warp_event(9, 7, RUINS_OF_ALPH_OMANYTE_ITEM_ROOM, 3),
    warp_event(10, 7, RUINS_OF_ALPH_OMANYTE_ITEM_ROOM, 4),
    warp_event(17, 13, RUINS_OF_ALPH_INNER_CHAMBER, 6),
};

static const struct ObjEvent RuinsOfAlphOmanyteWordRoom_ObjectEvents[] = {
    0,
};

const struct MapEvents RuinsOfAlphOmanyteWordRoom_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphOmanyteWordRoom_WarpEvents),
    .warp_events = RuinsOfAlphOmanyteWordRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphOmanyteWordRoom_CoordEvents),
    .coord_events = RuinsOfAlphOmanyteWordRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(RuinsOfAlphOmanyteWordRoom_BGEvents),
    .bg_events = RuinsOfAlphOmanyteWordRoom_BGEvents,

    .obj_event_count = 0, // lengthof(RuinsOfAlphOmanyteWordRoom_ObjectEvents),
    .obj_events = RuinsOfAlphOmanyteWordRoom_ObjectEvents,
};

//// CODE

    //db(0, 0) // filler
