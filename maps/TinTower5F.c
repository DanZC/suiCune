#include "../constants.h"
#include "../util/scripting.h"
#include "TinTower5F.h"
//// EVENTS
enum {
    TINTOWER5F_POKE_BALL = 2,
};

const Script_fn_t TinTower5F_SceneScripts[] = {
    0,
};

const struct MapCallback TinTower5F_MapCallbacks[] = {
    0,
};

const struct MapScripts TinTower5F_MapScripts = {
    .scene_script_count = 0, // lengthof(TinTower5F_SceneScripts),
    .scene_scripts = TinTower5F_SceneScripts,

    .callback_count = 0, // lengthof(TinTower5F_MapCallbacks),
    .callbacks = TinTower5F_MapCallbacks,
};

static const struct CoordEvent TinTower5F_CoordEvents[] = {
    0,
};

static const struct BGEvent TinTower5F_BGEvents[] = {
    bg_event(16, 14, BGEVENT_ITEM, &TinTower5FHiddenFullRestore),
    bg_event(3, 15, BGEVENT_ITEM, &TinTower5FHiddenCarbos),
};

static const struct WarpEventData TinTower5F_WarpEvents[] = {
    warp_event(11, 15, TIN_TOWER_6F, 2),
    warp_event(2, 4, TIN_TOWER_4F, 1),
    warp_event(2, 14, TIN_TOWER_4F, 3),
    warp_event(17, 15, TIN_TOWER_4F, 4),
};

static const struct ObjEvent TinTower5F_ObjectEvents[] = {
    object_event(9, 9, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower5FRareCandy, EVENT_TIN_TOWER_5F_RARE_CANDY),
};

const struct MapEvents TinTower5F_MapEvents = {
    .warp_event_count = lengthof(TinTower5F_WarpEvents),
    .warp_events = TinTower5F_WarpEvents,

    .coord_event_count = 0, // lengthof(TinTower5F_CoordEvents),
    .coord_events = TinTower5F_CoordEvents,

    .bg_event_count = lengthof(TinTower5F_BGEvents),
    .bg_events = TinTower5F_BGEvents,

    .obj_event_count = lengthof(TinTower5F_ObjectEvents),
    .obj_events = TinTower5F_ObjectEvents,
};

//// CODE

const struct ItemBall TinTower5FRareCandy = {RARE_CANDY, 1};
const struct HiddenItem TinTower5FHiddenFullRestore = {FULL_RESTORE, EVENT_TIN_TOWER_5F_HIDDEN_FULL_RESTORE};
const struct HiddenItem TinTower5FHiddenCarbos = {CARBOS, EVENT_TIN_TOWER_5F_HIDDEN_CARBOS};
    //db(0, 0) // filler
