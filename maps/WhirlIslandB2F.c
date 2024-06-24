#include "../constants.h"
#include "../util/scripting.h"
#include "WhirlIslandB2F.h"
//// EVENTS
enum {
    WHIRLISLANDB2F_POKE_BALL1 = 2,
    WHIRLISLANDB2F_POKE_BALL2,
    WHIRLISLANDB2F_POKE_BALL3,
};

const Script_fn_t WhirlIslandB2F_SceneScripts[] = {
    0,
};

const struct MapCallback WhirlIslandB2F_MapCallbacks[] = {
    0,
};

const struct MapScripts WhirlIslandB2F_MapScripts = {
    .scene_script_count = 0, // lengthof(WhirlIslandB2F_SceneScripts),
    .scene_scripts = WhirlIslandB2F_SceneScripts,

    .callback_count = 0, // lengthof(WhirlIslandB2F_MapCallbacks),
    .callbacks = WhirlIslandB2F_MapCallbacks,
};

static const struct CoordEvent WhirlIslandB2F_CoordEvents[] = {
    0,
};

static const struct BGEvent WhirlIslandB2F_BGEvents[] = {
    0,
};

static const struct WarpEventData WhirlIslandB2F_WarpEvents[] = {
    warp_event(11, 5, WHIRL_ISLAND_B1F, 7),
    warp_event(7, 11, WHIRL_ISLAND_B1F, 8),
    warp_event(7, 25, WHIRL_ISLAND_LUGIA_CHAMBER, 1),
    warp_event(13, 31, WHIRL_ISLAND_SW, 5),
};

static const struct ObjEvent WhirlIslandB2F_ObjectEvents[] = {
    object_event(10, 11, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &WhirlIslandB2FFullRestore, EVENT_WHIRL_ISLAND_B2F_FULL_RESTORE),
    object_event(6, 4, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &WhirlIslandB2FMaxRevive, EVENT_WHIRL_ISLAND_B2F_MAX_REVIVE),
    object_event(5, 12, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &WhirlIslandB2FMaxElixer, EVENT_WHIRL_ISLAND_B2F_MAX_ELIXER),
};

const struct MapEvents WhirlIslandB2F_MapEvents = {
    .warp_event_count = lengthof(WhirlIslandB2F_WarpEvents),
    .warp_events = WhirlIslandB2F_WarpEvents,

    .coord_event_count = 0, // lengthof(WhirlIslandB2F_CoordEvents),
    .coord_events = WhirlIslandB2F_CoordEvents,

    .bg_event_count = 0, // lengthof(WhirlIslandB2F_BGEvents),
    .bg_events = WhirlIslandB2F_BGEvents,

    .obj_event_count = lengthof(WhirlIslandB2F_ObjectEvents),
    .obj_events = WhirlIslandB2F_ObjectEvents,
};

//// CODE

const struct ItemBall WhirlIslandB2FFullRestore = {FULL_RESTORE, 1};
const struct ItemBall WhirlIslandB2FMaxRevive = {MAX_REVIVE, 1};
const struct ItemBall WhirlIslandB2FMaxElixer = {MAX_ELIXER, 1};
    //db(0, 0) // filler
