#include "../constants.h"
#include "../util/scripting.h"
#include "TinTower6F.h"
//// EVENTS
enum {
    TINTOWER6F_POKE_BALL = 2,
};

const Script_fn_t TinTower6F_SceneScripts[] = {
    0,
};

const struct MapCallback TinTower6F_MapCallbacks[] = {
    0,
};

const struct MapScripts TinTower6F_MapScripts = {
    .scene_script_count = 0, // lengthof(TinTower6F_SceneScripts),
    .scene_scripts = TinTower6F_SceneScripts,

    .callback_count = 0, // lengthof(TinTower6F_MapCallbacks),
    .callbacks = TinTower6F_MapCallbacks,
};

static const struct CoordEvent TinTower6F_CoordEvents[] = {
    0,
};

static const struct BGEvent TinTower6F_BGEvents[] = {
    0,
};

static const struct WarpEventData TinTower6F_WarpEvents[] = {
    warp_event(3, 9, TIN_TOWER_7F, 1),
    warp_event(11, 15, TIN_TOWER_5F, 1),
};

static const struct ObjEvent TinTower6F_ObjectEvents[] = {
    object_event(8, 8, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower6FMaxPotion, EVENT_TIN_TOWER_6F_MAX_POTION),
};

const struct MapEvents TinTower6F_MapEvents = {
    .warp_event_count = lengthof(TinTower6F_WarpEvents),
    .warp_events = TinTower6F_WarpEvents,

    .coord_event_count = 0, // lengthof(TinTower6F_CoordEvents),
    .coord_events = TinTower6F_CoordEvents,

    .bg_event_count = 0, // lengthof(TinTower6F_BGEvents),
    .bg_events = TinTower6F_BGEvents,

    .obj_event_count = lengthof(TinTower6F_ObjectEvents),
    .obj_events = TinTower6F_ObjectEvents,
};

//// CODE

const struct ItemBall TinTower6FMaxPotion = {MAX_POTION, 1};
    //db(0, 0) // filler
