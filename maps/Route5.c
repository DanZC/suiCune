#include "../constants.h"
#include "../util/scripting.h"
#include "Route5.h"
//// EVENTS
enum {
    ROUTE5_POKEFAN_M = 2,
};

const Script_fn_t Route5_SceneScripts[] = {
    0,
};

const struct MapCallback Route5_MapCallbacks[] = {
    0,
};

const struct MapScripts Route5_MapScripts = {
    .scene_script_count = 0, // lengthof(Route5_SceneScripts),
    .scene_scripts = Route5_SceneScripts,

    .callback_count = 0, // lengthof(Route5_MapCallbacks),
    .callbacks = Route5_MapCallbacks,
};

static const struct CoordEvent Route5_CoordEvents[] = {
    0,
};

static const struct BGEvent Route5_BGEvents[] = {
    bg_event(17, 17, BGEVENT_READ, &Route5UndergroundPathSign),
    bg_event(10, 11, BGEVENT_READ, &HouseForSaleSign),
};

static const struct WarpEventData Route5_WarpEvents[] = {
    warp_event(17, 15, ROUTE_5_UNDERGROUND_PATH_ENTRANCE, 1),
    warp_event(8, 17, ROUTE_5_SAFFRON_GATE, 1),
    warp_event(9, 17, ROUTE_5_SAFFRON_GATE, 2),
    warp_event(10, 11, ROUTE_5_CLEANSE_TAG_HOUSE, 1),
};

static const struct ObjEvent Route5_ObjectEvents[] = {
    object_event(17, 16, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route5PokefanMScript, EVENT_ROUTE_5_6_POKEFAN_M_BLOCKS_UNDERGROUND_PATH),
};

const struct MapEvents Route5_MapEvents = {
    .warp_event_count = lengthof(Route5_WarpEvents),
    .warp_events = Route5_WarpEvents,

    .coord_event_count = 0, // lengthof(Route5_CoordEvents),
    .coord_events = Route5_CoordEvents,

    .bg_event_count = lengthof(Route5_BGEvents),
    .bg_events = Route5_BGEvents,

    .obj_event_count = lengthof(Route5_ObjectEvents),
    .obj_events = Route5_ObjectEvents,
};

//// CODE

bool Route5PokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route5PokefanMText)
    SCRIPT_END
}
bool Route5UndergroundPathSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(Route5UndergroundPathSignText)
    SCRIPT_END
}
bool HouseForSaleSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(HouseForSaleSignText)
    SCRIPT_END
}
const txt_cmd_s Route5PokefanMText[] = {
    text_start("The road is closed"
        t_line "until the problem"
        t_para "at the POWER PLANT"
        t_line "is solved."
        t_done )
};
const txt_cmd_s Route5UndergroundPathSignText[] = {
    text_start("UNDERGROUND PATH"
        t_para "CERULEAN CITY -"
        t_line "VERMILION CITY"
        t_done )
};
const txt_cmd_s HouseForSaleSignText[] = {
    text_start("What's this?"
        t_para "House for Sale…"
        t_line "Nobody lives here."
        t_done )
    //db(0, 0) // filler
};
