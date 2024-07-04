#include "../constants.h"
#include "../util/scripting.h"
#include "SilverCaveItemRooms.h"
//// EVENTS
enum {
    SILVERCAVEITEMROOMS_POKE_BALL1 = 2,
    SILVERCAVEITEMROOMS_POKE_BALL2,
};

const Script_fn_t SilverCaveItemRooms_SceneScripts[] = {
    0,
};

const struct MapCallback SilverCaveItemRooms_MapCallbacks[] = {
    0,
};

const struct MapScripts SilverCaveItemRooms_MapScripts = {
    .scene_script_count = 0, // lengthof(SilverCaveItemRooms_SceneScripts),
    .scene_scripts = SilverCaveItemRooms_SceneScripts,

    .callback_count = 0, // lengthof(SilverCaveItemRooms_MapCallbacks),
    .callbacks = SilverCaveItemRooms_MapCallbacks,
};

static const struct CoordEvent SilverCaveItemRooms_CoordEvents[] = {
    0,
};

static const struct BGEvent SilverCaveItemRooms_BGEvents[] = {
    0,
};

static const struct WarpEventData SilverCaveItemRooms_WarpEvents[] = {
    warp_event(13, 3, SILVER_CAVE_ROOM_2, 3),
    warp_event(7, 15, SILVER_CAVE_ROOM_2, 4),
};

static const struct ObjEvent SilverCaveItemRooms_ObjectEvents[] = {
    object_event(6, 3, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SilverCaveItemRoomsMaxRevive, EVENT_SILVER_CAVE_ITEM_ROOMS_MAX_REVIVE),
    object_event(15, 11, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &SilverCaveItemRoomsFullRestore, EVENT_SILVER_CAVE_ITEM_ROOMS_FULL_RESTORE),
};

const struct MapEvents SilverCaveItemRooms_MapEvents = {
    .warp_event_count = lengthof(SilverCaveItemRooms_WarpEvents),
    .warp_events = SilverCaveItemRooms_WarpEvents,

    .coord_event_count = 0, // lengthof(SilverCaveItemRooms_CoordEvents),
    .coord_events = SilverCaveItemRooms_CoordEvents,

    .bg_event_count = 0, // lengthof(SilverCaveItemRooms_BGEvents),
    .bg_events = SilverCaveItemRooms_BGEvents,

    .obj_event_count = lengthof(SilverCaveItemRooms_ObjectEvents),
    .obj_events = SilverCaveItemRooms_ObjectEvents,
};

//// CODE

const struct ItemBall SilverCaveItemRoomsMaxRevive = {MAX_REVIVE, 1};
const struct ItemBall SilverCaveItemRoomsFullRestore = {FULL_RESTORE, 1};
    //db(0, 0) // filler
