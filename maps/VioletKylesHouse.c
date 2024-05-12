#include "../constants.h"
#include "../util/scripting.h"
#include "VioletKylesHouse.h"
//// EVENTS
enum {
    VIOLETKYLESHOUSE_POKEFAN_M = 2,
    VIOLETKYLESHOUSE_KYLE,
};

const Script_fn_t VioletKylesHouse_SceneScripts[] = {
    0,
};

const struct MapCallback VioletKylesHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts VioletKylesHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(VioletKylesHouse_SceneScripts),
    .scene_scripts = VioletKylesHouse_SceneScripts,

    .callback_count = 0, // lengthof(VioletKylesHouse_MapCallbacks),
    .callbacks = VioletKylesHouse_MapCallbacks,
};

static const struct CoordEvent VioletKylesHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent VioletKylesHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData VioletKylesHouse_WarpEvents[] = {
    warp_event(3, 7, VIOLET_CITY, 6),
    warp_event(4, 7, VIOLET_CITY, 6),
};

static const struct ObjEvent VioletKylesHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VioletKylesHousePokefanMScript, -1),
    object_event(6, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 2, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Kyle, -1),
};

const struct MapEvents VioletKylesHouse_MapEvents = {
    .warp_event_count = lengthof(VioletKylesHouse_WarpEvents),
    .warp_events = VioletKylesHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(VioletKylesHouse_CoordEvents),
    .coord_events = VioletKylesHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(VioletKylesHouse_BGEvents),
    .bg_events = VioletKylesHouse_BGEvents,

    .obj_event_count = lengthof(VioletKylesHouse_ObjectEvents),
    .obj_events = VioletKylesHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "VioletKylesHouse.h"

bool VioletKylesHousePokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VioletKylesHousePokefanMText)
    SCRIPT_END
}
bool Kyle(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    trade(NPC_TRADE_KYLE)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s VioletKylesHousePokefanMText[] = {
    text_start("A #MON you get"
        t_line "in a trade grows"
        t_cont "quickly."
        t_para "But if you don't"
        t_line "have the right GYM"
        t_para "BADGE, they may"
        t_line "disobey you."
        t_done )
    //db(0, 0) // filler
};
