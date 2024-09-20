#include "../constants.h"
#include "../util/scripting.h"
#include "RockTunnel1F.h"
//// EVENTS
enum {
    ROCKTUNNEL1F_POKE_BALL1 = 2,
    ROCKTUNNEL1F_POKE_BALL2,
};

const Script_fn_t RockTunnel1F_SceneScripts[] = {
    0,
};

const struct MapCallback RockTunnel1F_MapCallbacks[] = {
    0,
};

const struct MapScripts RockTunnel1F_MapScripts = {
    .scene_script_count = 0, // lengthof(RockTunnel1F_SceneScripts),
    .scene_scripts = RockTunnel1F_SceneScripts,

    .callback_count = 0, // lengthof(RockTunnel1F_MapCallbacks),
    .callbacks = RockTunnel1F_MapCallbacks,
};

static const struct CoordEvent RockTunnel1F_CoordEvents[] = {
    0,
};

static const struct BGEvent RockTunnel1F_BGEvents[] = {
    bg_event(24, 4, BGEVENT_ITEM, &RockTunnel1FHiddenXAccuracy),
    bg_event(21, 15, BGEVENT_ITEM, &RockTunnel1FHiddenXDefend),
};

static const struct WarpEventData RockTunnel1F_WarpEvents[] = {
    warp_event(15, 3, ROUTE_9, 1),
    warp_event(11, 25, ROUTE_10_SOUTH, 1),
    warp_event(5, 3, ROCK_TUNNEL_B1F, 3),
    warp_event(15, 9, ROCK_TUNNEL_B1F, 2),
    warp_event(27, 3, ROCK_TUNNEL_B1F, 4),
    warp_event(27, 13, ROCK_TUNNEL_B1F, 1),
};

static const struct ObjEvent RockTunnel1F_ObjectEvents[] = {
    object_event(4, 18, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RockTunnel1FElixer, EVENT_ROCK_TUNNEL_1F_ELIXER),
    object_event(10, 15, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RockTunnel1FTMSteelWing, EVENT_ROCK_TUNNEL_1F_TM_STEEL_WING),
};

const struct MapEvents RockTunnel1F_MapEvents = {
    .warp_event_count = lengthof(RockTunnel1F_WarpEvents),
    .warp_events = RockTunnel1F_WarpEvents,

    .coord_event_count = 0, // lengthof(RockTunnel1F_CoordEvents),
    .coord_events = RockTunnel1F_CoordEvents,

    .bg_event_count = lengthof(RockTunnel1F_BGEvents),
    .bg_events = RockTunnel1F_BGEvents,

    .obj_event_count = lengthof(RockTunnel1F_ObjectEvents),
    .obj_events = RockTunnel1F_ObjectEvents,
};

//// CODE

const struct ItemBall RockTunnel1FElixer = {ELIXER, 1};
const struct ItemBall RockTunnel1FTMSteelWing = {TM_STEEL_WING, 1};
const struct HiddenItem RockTunnel1FHiddenXAccuracy = {X_ACCURACY, EVENT_ROCK_TUNNEL_1F_HIDDEN_X_ACCURACY};
const struct HiddenItem RockTunnel1FHiddenXDefend = {X_DEFEND, EVENT_ROCK_TUNNEL_1F_HIDDEN_X_DEFEND};
    //db(0, 0) // filler
