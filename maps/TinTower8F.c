#include "../constants.h"
#include "../util/scripting.h"
#include "TinTower8F.h"
//// EVENTS
enum {
    TINTOWER8F_POKE_BALL1 = 2,
    TINTOWER8F_POKE_BALL2,
    TINTOWER8F_POKE_BALL3,
};

const Script_fn_t TinTower8F_SceneScripts[] = {
    0,
};

const struct MapCallback TinTower8F_MapCallbacks[] = {
    0,
};

const struct MapScripts TinTower8F_MapScripts = {
    .scene_script_count = 0, // lengthof(TinTower8F_SceneScripts),
    .scene_scripts = TinTower8F_SceneScripts,

    .callback_count = 0, // lengthof(TinTower8F_MapCallbacks),
    .callbacks = TinTower8F_MapCallbacks,
};

static const struct CoordEvent TinTower8F_CoordEvents[] = {
    0,
};

static const struct BGEvent TinTower8F_BGEvents[] = {
    0,
};

static const struct WarpEventData TinTower8F_WarpEvents[] = {
    warp_event(2, 5, TIN_TOWER_7F, 2),
    warp_event(2, 11, TIN_TOWER_9F, 1),
    warp_event(16, 7, TIN_TOWER_9F, 2),
    warp_event(10, 3, TIN_TOWER_9F, 3),
    warp_event(14, 15, TIN_TOWER_9F, 6),
    warp_event(6, 9, TIN_TOWER_9F, 7),
};

static const struct ObjEvent TinTower8F_ObjectEvents[] = {
    object_event(7, 13, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower8FNugget, EVENT_TIN_TOWER_8F_NUGGET),
    object_event(11, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower8FMaxElixer, EVENT_TIN_TOWER_8F_MAX_ELIXER),
    object_event(3, 1, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower8FFullRestore, EVENT_TIN_TOWER_8F_FULL_RESTORE),
};

const struct MapEvents TinTower8F_MapEvents = {
    .warp_event_count = lengthof(TinTower8F_WarpEvents),
    .warp_events = TinTower8F_WarpEvents,

    .coord_event_count = 0, // lengthof(TinTower8F_CoordEvents),
    .coord_events = TinTower8F_CoordEvents,

    .bg_event_count = 0, // lengthof(TinTower8F_BGEvents),
    .bg_events = TinTower8F_BGEvents,

    .obj_event_count = lengthof(TinTower8F_ObjectEvents),
    .obj_events = TinTower8F_ObjectEvents,
};

//// CODE

const struct ItemBall TinTower8FNugget = {NUGGET, 1};
const struct ItemBall TinTower8FMaxElixer = {MAX_ELIXER, 1};
const struct ItemBall TinTower8FFullRestore = {FULL_RESTORE, 1};
    //db(0, 0) // filler
