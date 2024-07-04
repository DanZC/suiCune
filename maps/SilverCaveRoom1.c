#include "../constants.h"
#include "../util/scripting.h"
#include "SilverCaveRoom1.h"
//// EVENTS
enum {
    SILVERCAVEROOM1_POKE_BALL1 = 2,
    SILVERCAVEROOM1_POKE_BALL2,
    SILVERCAVEROOM1_POKE_BALL3,
    SILVERCAVEROOM1_POKE_BALL4,
};

const Script_fn_t SilverCaveRoom1_SceneScripts[] = {
    0,
};

const struct MapCallback SilverCaveRoom1_MapCallbacks[] = {
    0,
};

const struct MapScripts SilverCaveRoom1_MapScripts = {
    .scene_script_count = 0, // lengthof(SilverCaveRoom1_SceneScripts),
    .scene_scripts = SilverCaveRoom1_SceneScripts,

    .callback_count = 0, // lengthof(SilverCaveRoom1_MapCallbacks),
    .callbacks = SilverCaveRoom1_MapCallbacks,
};

static const struct CoordEvent SilverCaveRoom1_CoordEvents[] = {
    0,
};

static const struct BGEvent SilverCaveRoom1_BGEvents[] = {
    bg_event(16, 23, BGEVENT_ITEM, &SilverCaveRoom1HiddenDireHit),
    bg_event(17, 12, BGEVENT_ITEM, &SilverCaveRoom1HiddenUltraBall),
};

static const struct WarpEventData SilverCaveRoom1_WarpEvents[] = {
    warp_event(9, 33, SILVER_CAVE_OUTSIDE, 2),
    warp_event(15, 1, SILVER_CAVE_ROOM_2, 1),
};

static const struct ObjEvent SilverCaveRoom1_ObjectEvents[] = {
    object_event(4, 9, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SilverCaveRoom1MaxElixer, EVENT_SILVER_CAVE_ROOM_1_MAX_ELIXER),
    object_event(15, 29, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SilverCaveRoom1Protein, EVENT_SILVER_CAVE_ROOM_1_PROTEIN),
    object_event(5, 30, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SilverCaveRoom1EscapeRope, EVENT_SILVER_CAVE_ROOM_1_ESCAPE_ROPE),
    object_event(7, 18, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SilverCaveRoom1UltraBall, EVENT_SILVER_CAVE_ROOM_1_ULTRA_BALL),
};

const struct MapEvents SilverCaveRoom1_MapEvents = {
    .warp_event_count = lengthof(SilverCaveRoom1_WarpEvents),
    .warp_events = SilverCaveRoom1_WarpEvents,

    .coord_event_count = 0, // lengthof(SilverCaveRoom1_CoordEvents),
    .coord_events = SilverCaveRoom1_CoordEvents,

    .bg_event_count = lengthof(SilverCaveRoom1_BGEvents),
    .bg_events = SilverCaveRoom1_BGEvents,

    .obj_event_count = lengthof(SilverCaveRoom1_ObjectEvents),
    .obj_events = SilverCaveRoom1_ObjectEvents,
};

//// CODE

const struct ItemBall SilverCaveRoom1MaxElixer = {MAX_ELIXER, 1};
const struct ItemBall SilverCaveRoom1Protein = {PROTEIN, 1};
const struct ItemBall SilverCaveRoom1EscapeRope = {ESCAPE_ROPE, 1};
const struct ItemBall SilverCaveRoom1UltraBall = {ULTRA_BALL, 1};
const struct HiddenItem SilverCaveRoom1HiddenDireHit = {DIRE_HIT, EVENT_SILVER_CAVE_ROOM_1_HIDDEN_DIRE_HIT};
const struct HiddenItem SilverCaveRoom1HiddenUltraBall = {ULTRA_BALL, EVENT_SILVER_CAVE_ROOM_1_HIDDEN_ULTRA_BALL};
    //db(0, 0) // filler
