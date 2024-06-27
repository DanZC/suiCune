#include "../constants.h"
#include "../util/scripting.h"
#include "TinTower3F.h"
//// EVENTS
enum {
    TINTOWER3F_POKE_BALL = 2,
};

const Script_fn_t TinTower3F_SceneScripts[] = {
    0,
};

const struct MapCallback TinTower3F_MapCallbacks[] = {
    0,
};

const struct MapScripts TinTower3F_MapScripts = {
    .scene_script_count = 0, // lengthof(TinTower3F_SceneScripts),
    .scene_scripts = TinTower3F_SceneScripts,

    .callback_count = 0, // lengthof(TinTower3F_MapCallbacks),
    .callbacks = TinTower3F_MapCallbacks,
};

static const struct CoordEvent TinTower3F_CoordEvents[] = {
    0,
};

static const struct BGEvent TinTower3F_BGEvents[] = {
    0,
};

static const struct WarpEventData TinTower3F_WarpEvents[] = {
    warp_event(10, 14, TIN_TOWER_2F, 1),
    warp_event(16, 2, TIN_TOWER_4F, 2),
};

static const struct ObjEvent TinTower3F_ObjectEvents[] = {
    object_event(3, 14, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower3FFullHeal, EVENT_TIN_TOWER_3F_FULL_HEAL),
};

const struct MapEvents TinTower3F_MapEvents = {
    .warp_event_count = lengthof(TinTower3F_WarpEvents),
    .warp_events = TinTower3F_WarpEvents,

    .coord_event_count = 0, // lengthof(TinTower3F_CoordEvents),
    .coord_events = TinTower3F_CoordEvents,

    .bg_event_count = 0, // lengthof(TinTower3F_BGEvents),
    .bg_events = TinTower3F_BGEvents,

    .obj_event_count = lengthof(TinTower3F_ObjectEvents),
    .obj_events = TinTower3F_ObjectEvents,
};

//// CODE

const struct ItemBall TinTower3FFullHeal = {FULL_HEAL, 1};
    //db(0, 0) // filler
