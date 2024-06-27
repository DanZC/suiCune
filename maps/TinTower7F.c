#include "../constants.h"
#include "../util/scripting.h"
#include "TinTower7F.h"
//// EVENTS
enum {
    TINTOWER7F_POKE_BALL = 2,
};

const Script_fn_t TinTower7F_SceneScripts[] = {
    0,
};

const struct MapCallback TinTower7F_MapCallbacks[] = {
    0,
};

const struct MapScripts TinTower7F_MapScripts = {
    .scene_script_count = 0, // lengthof(TinTower7F_SceneScripts),
    .scene_scripts = TinTower7F_SceneScripts,

    .callback_count = 0, // lengthof(TinTower7F_MapCallbacks),
    .callbacks = TinTower7F_MapCallbacks,
};

static const struct CoordEvent TinTower7F_CoordEvents[] = {
    0,
};

static const struct BGEvent TinTower7F_BGEvents[] = {
    0,
};

static const struct WarpEventData TinTower7F_WarpEvents[] = {
    warp_event(3, 9, TIN_TOWER_6F, 1),
    warp_event(10, 15, TIN_TOWER_8F, 1),
    warp_event(12, 7, TIN_TOWER_7F, 4),
    warp_event(8, 3, TIN_TOWER_7F, 3),
    warp_event(6, 9, TIN_TOWER_9F, 5),
};

static const struct ObjEvent TinTower7F_ObjectEvents[] = {
    object_event(16, 1, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower7FMaxRevive, EVENT_TIN_TOWER_7F_MAX_REVIVE),
};

const struct MapEvents TinTower7F_MapEvents = {
    .warp_event_count = lengthof(TinTower7F_WarpEvents),
    .warp_events = TinTower7F_WarpEvents,

    .coord_event_count = 0, // lengthof(TinTower7F_CoordEvents),
    .coord_events = TinTower7F_CoordEvents,

    .bg_event_count = 0, // lengthof(TinTower7F_BGEvents),
    .bg_events = TinTower7F_BGEvents,

    .obj_event_count = lengthof(TinTower7F_ObjectEvents),
    .obj_events = TinTower7F_ObjectEvents,
};

//// CODE

const struct ItemBall TinTower7FMaxRevive = {MAX_REVIVE, 1};
    //db(0, 0) // filler
