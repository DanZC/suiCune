#include "../constants.h"
#include "../util/scripting.h"
#include "BillsBrothersHouse.h"
//// EVENTS
enum {
    BILLSBROTHERSHOUSE_POKEFAN_F = 2,
    BILLSBROTHERSHOUSE_YOUNGSTER,
};

const Script_fn_t BillsBrothersHouse_SceneScripts[] = {
    0,
};

const struct MapCallback BillsBrothersHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts BillsBrothersHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(BillsBrothersHouse_SceneScripts),
    .scene_scripts = BillsBrothersHouse_SceneScripts,

    .callback_count = 0, // lengthof(BillsBrothersHouse_MapCallbacks),
    .callbacks = BillsBrothersHouse_MapCallbacks,
};

static const struct CoordEvent BillsBrothersHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent BillsBrothersHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData BillsBrothersHouse_WarpEvents[] = {
    warp_event(2, 7, FUCHSIA_CITY, 4),
    warp_event(3, 7, FUCHSIA_CITY, 4),
};

static const struct ObjEvent BillsBrothersHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BillsBrotherScript, -1),
    object_event(6, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BillsBrothersHouseYoungsterScript, -1),
};

const struct MapEvents BillsBrothersHouse_MapEvents = {
    .warp_event_count = lengthof(BillsBrothersHouse_WarpEvents),
    .warp_events = BillsBrothersHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(BillsBrothersHouse_CoordEvents),
    .coord_events = BillsBrothersHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(BillsBrothersHouse_BGEvents),
    .bg_events = BillsBrothersHouse_BGEvents,

    .obj_event_count = lengthof(BillsBrothersHouse_ObjectEvents),
    .obj_events = BillsBrothersHouse_ObjectEvents,
};

//// CODE

bool BillsBrotherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BillsBrotherText)
    SCRIPT_END
}
bool BillsBrothersHouseYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BillsBrothersHouseYoungsterText)
    SCRIPT_END
}
const txt_cmd_s BillsBrotherText[] = {
    text_start("My grandpa is at "
        t_line "my brother BILL's"
        t_cont "on CERULEAN CAPE."
        t_done )
};
const txt_cmd_s BillsBrothersHouseYoungsterText[] = {
    text_start("I saw these weird,"
        t_line "slow #MON on"
        t_cont "CYCLING ROAD."
        t_done )
    //db(0, 0) // filler
};
