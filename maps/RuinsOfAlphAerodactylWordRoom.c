#include "../constants.h"
#include "../util/scripting.h"
#include "RuinsOfAlphAerodactylWordRoom.h"
//// EVENTS
const Script_fn_t RuinsOfAlphAerodactylWordRoom_SceneScripts[] = {
    0,
};

const struct MapCallback RuinsOfAlphAerodactylWordRoom_MapCallbacks[] = {
    0,
};

const struct MapScripts RuinsOfAlphAerodactylWordRoom_MapScripts = {
    .scene_script_count = 0, // lengthof(RuinsOfAlphAerodactylWordRoom_SceneScripts),
    .scene_scripts = RuinsOfAlphAerodactylWordRoom_SceneScripts,

    .callback_count = 0, // lengthof(RuinsOfAlphAerodactylWordRoom_MapCallbacks),
    .callbacks = RuinsOfAlphAerodactylWordRoom_MapCallbacks,
};

static const struct CoordEvent RuinsOfAlphAerodactylWordRoom_CoordEvents[] = {
    0,
};

static const struct BGEvent RuinsOfAlphAerodactylWordRoom_BGEvents[] = {
    0,
};

static const struct WarpEventData RuinsOfAlphAerodactylWordRoom_WarpEvents[] = {
    warp_event(9, 5, RUINS_OF_ALPH_AERODACTYL_ITEM_ROOM, 3),
    warp_event(10, 5, RUINS_OF_ALPH_AERODACTYL_ITEM_ROOM, 4),
    warp_event(17, 11, RUINS_OF_ALPH_INNER_CHAMBER, 8),
};

static const struct ObjEvent RuinsOfAlphAerodactylWordRoom_ObjectEvents[] = {
    0,
};

const struct MapEvents RuinsOfAlphAerodactylWordRoom_MapEvents = {
    .warp_event_count = lengthof(RuinsOfAlphAerodactylWordRoom_WarpEvents),
    .warp_events = RuinsOfAlphAerodactylWordRoom_WarpEvents,

    .coord_event_count = 0, // lengthof(RuinsOfAlphAerodactylWordRoom_CoordEvents),
    .coord_events = RuinsOfAlphAerodactylWordRoom_CoordEvents,

    .bg_event_count = 0, // lengthof(RuinsOfAlphAerodactylWordRoom_BGEvents),
    .bg_events = RuinsOfAlphAerodactylWordRoom_BGEvents,

    .obj_event_count = 0, // lengthof(RuinsOfAlphAerodactylWordRoom_ObjectEvents),
    .obj_events = RuinsOfAlphAerodactylWordRoom_ObjectEvents,
};

//// CODE

    //db(0, 0) // filler
