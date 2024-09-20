#include "../constants.h"
#include "../util/scripting.h"
#include "RockTunnelB1F.h"
//// EVENTS
enum {
    ROCKTUNNELB1F_POKE_BALL1 = 2,
    ROCKTUNNELB1F_POKE_BALL2,
    ROCKTUNNELB1F_POKE_BALL3,
};

const Script_fn_t RockTunnelB1F_SceneScripts[] = {
    0,
};

const struct MapCallback RockTunnelB1F_MapCallbacks[] = {
    0,
};

const struct MapScripts RockTunnelB1F_MapScripts = {
    .scene_script_count = 0, // lengthof(RockTunnelB1F_SceneScripts),
    .scene_scripts = RockTunnelB1F_SceneScripts,

    .callback_count = 0, // lengthof(RockTunnelB1F_MapCallbacks),
    .callbacks = RockTunnelB1F_MapCallbacks,
};

static const struct CoordEvent RockTunnelB1F_CoordEvents[] = {
    0,
};

static const struct BGEvent RockTunnelB1F_BGEvents[] = {
    bg_event(4, 14, BGEVENT_ITEM, &RockTunnelB1FHiddenMaxPotion),
};

static const struct WarpEventData RockTunnelB1F_WarpEvents[] = {
    warp_event(3, 3, ROCK_TUNNEL_1F, 6),
    warp_event(17, 9, ROCK_TUNNEL_1F, 4),
    warp_event(23, 3, ROCK_TUNNEL_1F, 3),
    warp_event(25, 23, ROCK_TUNNEL_1F, 5),
};

static const struct ObjEvent RockTunnelB1F_ObjectEvents[] = {
    object_event(7, 25, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RockTunnelB1FIron, EVENT_ROCK_TUNNEL_B1F_IRON),
    object_event(6, 17, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RockTunnelB1FPPUp, EVENT_ROCK_TUNNEL_B1F_PP_UP),
    object_event(15, 2, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &RockTunnelB1FRevive, EVENT_ROCK_TUNNEL_B1F_REVIVE),
};

const struct MapEvents RockTunnelB1F_MapEvents = {
    .warp_event_count = lengthof(RockTunnelB1F_WarpEvents),
    .warp_events = RockTunnelB1F_WarpEvents,

    .coord_event_count = 0, // lengthof(RockTunnelB1F_CoordEvents),
    .coord_events = RockTunnelB1F_CoordEvents,

    .bg_event_count = lengthof(RockTunnelB1F_BGEvents),
    .bg_events = RockTunnelB1F_BGEvents,

    .obj_event_count = lengthof(RockTunnelB1F_ObjectEvents),
    .obj_events = RockTunnelB1F_ObjectEvents,
};

//// CODE

const struct ItemBall RockTunnelB1FIron = {IRON, 1};
const struct ItemBall RockTunnelB1FPPUp = {PP_UP, 1};
const struct ItemBall RockTunnelB1FRevive = {REVIVE, 1};
const struct HiddenItem RockTunnelB1FHiddenMaxPotion = {MAX_POTION, EVENT_ROCK_TUNNEL_B1F_HIDDEN_MAX_POTION};
    //db(0, 0) // filler
