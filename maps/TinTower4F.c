#include "../constants.h"
#include "../util/scripting.h"
#include "TinTower4F.h"
//// EVENTS
enum {
    TINTOWER4F_POKE_BALL1 = 2,
    TINTOWER4F_POKE_BALL2,
    TINTOWER4F_POKE_BALL3,
};

const Script_fn_t TinTower4F_SceneScripts[] = {
    0,
};

const struct MapCallback TinTower4F_MapCallbacks[] = {
    0,
};

const struct MapScripts TinTower4F_MapScripts = {
    .scene_script_count = 0, // lengthof(TinTower4F_SceneScripts),
    .scene_scripts = TinTower4F_SceneScripts,

    .callback_count = 0, // lengthof(TinTower4F_MapCallbacks),
    .callbacks = TinTower4F_MapCallbacks,
};

static const struct CoordEvent TinTower4F_CoordEvents[] = {
    0,
};

static const struct BGEvent TinTower4F_BGEvents[] = {
    bg_event(11, 6, BGEVENT_ITEM, &TinTower4FHiddenMaxPotion),
};

static const struct WarpEventData TinTower4F_WarpEvents[] = {
    warp_event(2, 4, TIN_TOWER_5F, 2),
    warp_event(16, 2, TIN_TOWER_3F, 2),
    warp_event(2, 14, TIN_TOWER_5F, 3),
    warp_event(17, 15, TIN_TOWER_5F, 4),
};

static const struct ObjEvent TinTower4F_ObjectEvents[] = {
    object_event(14, 10, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower4FUltraBall, EVENT_TIN_TOWER_4F_ULTRA_BALL),
    object_event(17, 14, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower4FPPUp, EVENT_TIN_TOWER_4F_PP_UP),
    object_event(2, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower4FEscapeRope, EVENT_TIN_TOWER_4F_ESCAPE_ROPE),
};

const struct MapEvents TinTower4F_MapEvents = {
    .warp_event_count = lengthof(TinTower4F_WarpEvents),
    .warp_events = TinTower4F_WarpEvents,

    .coord_event_count = 0, // lengthof(TinTower4F_CoordEvents),
    .coord_events = TinTower4F_CoordEvents,

    .bg_event_count = lengthof(TinTower4F_BGEvents),
    .bg_events = TinTower4F_BGEvents,

    .obj_event_count = lengthof(TinTower4F_ObjectEvents),
    .obj_events = TinTower4F_ObjectEvents,
};

//// CODE

const struct ItemBall TinTower4FUltraBall = {ULTRA_BALL, 1};
const struct ItemBall TinTower4FPPUp = {PP_UP, 1};
const struct ItemBall TinTower4FEscapeRope = {ESCAPE_ROPE, 1};
const struct HiddenItem TinTower4FHiddenMaxPotion = {MAX_POTION, EVENT_TIN_TOWER_4F_HIDDEN_MAX_POTION};
    //db(0, 0) // filler
