#include "../constants.h"
#include "../util/scripting.h"
#include "TinTower2F.h"
//// EVENTS
const Script_fn_t TinTower2F_SceneScripts[] = {
    0,
};

const struct MapCallback TinTower2F_MapCallbacks[] = {
    0,
};

const struct MapScripts TinTower2F_MapScripts = {
    .scene_script_count = 0, // lengthof(TinTower2F_SceneScripts),
    .scene_scripts = TinTower2F_SceneScripts,

    .callback_count = 0, // lengthof(TinTower2F_MapCallbacks),
    .callbacks = TinTower2F_MapCallbacks,
};

static const struct CoordEvent TinTower2F_CoordEvents[] = {
    0,
};

static const struct BGEvent TinTower2F_BGEvents[] = {
    0,
};

static const struct WarpEventData TinTower2F_WarpEvents[] = {
    warp_event(10, 14, TIN_TOWER_3F, 1),
    warp_event(10, 2, TIN_TOWER_1F, 3),
};

static const struct ObjEvent TinTower2F_ObjectEvents[] = {
    0,
};

const struct MapEvents TinTower2F_MapEvents = {
    .warp_event_count = lengthof(TinTower2F_WarpEvents),
    .warp_events = TinTower2F_WarpEvents,

    .coord_event_count = 0, // lengthof(TinTower2F_CoordEvents),
    .coord_events = TinTower2F_CoordEvents,

    .bg_event_count = 0, // lengthof(TinTower2F_BGEvents),
    .bg_events = TinTower2F_BGEvents,

    .obj_event_count = 0, // lengthof(TinTower2F_ObjectEvents),
    .obj_events = TinTower2F_ObjectEvents,
};

//// CODE

    //db(0, 0) // filler
