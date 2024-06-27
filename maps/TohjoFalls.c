#include "../constants.h"
#include "../util/scripting.h"
#include "TohjoFalls.h"
//// EVENTS
enum {
    TOHJOFALLS_POKE_BALL = 2,
};

const Script_fn_t TohjoFalls_SceneScripts[] = {
    0,
};

const struct MapCallback TohjoFalls_MapCallbacks[] = {
    0,
};

const struct MapScripts TohjoFalls_MapScripts = {
    .scene_script_count = 0, // lengthof(TohjoFalls_SceneScripts),
    .scene_scripts = TohjoFalls_SceneScripts,

    .callback_count = 0, // lengthof(TohjoFalls_MapCallbacks),
    .callbacks = TohjoFalls_MapCallbacks,
};

static const struct CoordEvent TohjoFalls_CoordEvents[] = {
    0,
};

static const struct BGEvent TohjoFalls_BGEvents[] = {
    0,
};

static const struct WarpEventData TohjoFalls_WarpEvents[] = {
    warp_event(13, 15, ROUTE_27, 2),
    warp_event(25, 15, ROUTE_27, 3),
};

static const struct ObjEvent TohjoFalls_ObjectEvents[] = {
    object_event(2, 6, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TohjoFallsMoonStone, EVENT_TOHJO_FALLS_MOON_STONE),
};

const struct MapEvents TohjoFalls_MapEvents = {
    .warp_event_count = lengthof(TohjoFalls_WarpEvents),
    .warp_events = TohjoFalls_WarpEvents,

    .coord_event_count = 0, // lengthof(TohjoFalls_CoordEvents),
    .coord_events = TohjoFalls_CoordEvents,

    .bg_event_count = 0, // lengthof(TohjoFalls_BGEvents),
    .bg_events = TohjoFalls_BGEvents,

    .obj_event_count = lengthof(TohjoFalls_ObjectEvents),
    .obj_events = TohjoFalls_ObjectEvents,
};

//// CODE

const struct ItemBall TohjoFallsMoonStone = {MOON_STONE, 1};
    //db(0, 0) // filler
