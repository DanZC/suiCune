#include "../constants.h"
#include "../util/scripting.h"
#include "IcePath1F.h"
//// EVENTS
enum {
    ICEPATH1F_POKE_BALL1 = 2,
    ICEPATH1F_POKE_BALL2,
    ICEPATH1F_POKE_BALL3,
};

const Script_fn_t IcePath1F_SceneScripts[] = {
    0,
};

const struct MapCallback IcePath1F_MapCallbacks[] = {
    0,
};

const struct MapScripts IcePath1F_MapScripts = {
    .scene_script_count = 0, // lengthof(IcePath1F_SceneScripts),
    .scene_scripts = IcePath1F_SceneScripts,

    .callback_count = 0, // lengthof(IcePath1F_MapCallbacks),
    .callbacks = IcePath1F_MapCallbacks,
};

static const struct CoordEvent IcePath1F_CoordEvents[] = {
    0,
};

static const struct BGEvent IcePath1F_BGEvents[] = {
    0,
};

static const struct WarpEventData IcePath1F_WarpEvents[] = {
    warp_event(4, 19, ROUTE_44, 1),
    warp_event(36, 27, BLACKTHORN_CITY, 7),
    warp_event(37, 5, ICE_PATH_B1F, 1),
    warp_event(37, 13, ICE_PATH_B1F, 7),
};

static const struct ObjEvent IcePath1F_ObjectEvents[] = {
    object_event(31, 7, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IcePath1FHMWaterfall, EVENT_GOT_HM07_WATERFALL),
    object_event(32, 23, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IcePath1FPPUp, EVENT_ICE_PATH_1F_PP_UP),
    object_event(35, 9, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IcePath1FProtein, EVENT_ICE_PATH_1F_PROTEIN),
};

const struct MapEvents IcePath1F_MapEvents = {
    .warp_event_count = lengthof(IcePath1F_WarpEvents),
    .warp_events = IcePath1F_WarpEvents,

    .coord_event_count = 0, // lengthof(IcePath1F_CoordEvents),
    .coord_events = IcePath1F_CoordEvents,

    .bg_event_count = 0, // lengthof(IcePath1F_BGEvents),
    .bg_events = IcePath1F_BGEvents,

    .obj_event_count = lengthof(IcePath1F_ObjectEvents),
    .obj_events = IcePath1F_ObjectEvents,
};

//// CODE

const struct ItemBall IcePath1FHMWaterfall = {HM_WATERFALL, 1};
const struct ItemBall IcePath1FPPUp = {PP_UP, 1};
const struct ItemBall IcePath1FProtein = {PROTEIN, 1};
    //db(0, 0) // filler
