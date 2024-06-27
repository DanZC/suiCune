#include "../constants.h"
#include "../util/scripting.h"
#include "Route23.h"
//// EVENTS
const Script_fn_t Route23_SceneScripts[] = {
    0,
};

const struct MapCallback Route23_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, Route23_MapScripts_FlyPoint),
};

const struct MapScripts Route23_MapScripts = {
    .scene_script_count = 0, // lengthof(Route23_SceneScripts),
    .scene_scripts = Route23_SceneScripts,

    .callback_count = lengthof(Route23_MapCallbacks),
    .callbacks = Route23_MapCallbacks,
};

static const struct CoordEvent Route23_CoordEvents[] = {
    0,
};

static const struct BGEvent Route23_BGEvents[] = {
    bg_event(11, 7, BGEVENT_READ, &IndigoPlateauSign),
};

static const struct WarpEventData Route23_WarpEvents[] = {
    warp_event(9, 5, INDIGO_PLATEAU_POKECENTER_1F, 1),
    warp_event(10, 5, INDIGO_PLATEAU_POKECENTER_1F, 2),
    warp_event(9, 13, VICTORY_ROAD, 10),
    warp_event(10, 13, VICTORY_ROAD, 10),
};

static const struct ObjEvent Route23_ObjectEvents[] = {
    0,
};

const struct MapEvents Route23_MapEvents = {
    .warp_event_count = lengthof(Route23_WarpEvents),
    .warp_events = Route23_WarpEvents,

    .coord_event_count = 0, // lengthof(Route23_CoordEvents),
    .coord_events = Route23_CoordEvents,

    .bg_event_count = lengthof(Route23_BGEvents),
    .bg_events = Route23_BGEvents,

    .obj_event_count = 0, // lengthof(Route23_ObjectEvents),
    .obj_events = Route23_ObjectEvents,
};

//// CODE

bool Route23_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_INDIGO_PLATEAU)
    s_endcallback
    SCRIPT_END
}
bool IndigoPlateauSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(IndigoPlateauSignText)
    SCRIPT_END
}
const txt_cmd_s IndigoPlateauSignText[] = {
    text_start("INDIGO PLATEAU"
        t_para "The Ultimate Goal"
        t_line "for Trainers!"
        t_para "#MON LEAGUE HQ"
        t_done )
    //db(0, 0) // filler
};
