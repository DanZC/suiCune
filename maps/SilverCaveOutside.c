#include "../constants.h"
#include "../util/scripting.h"
#include "SilverCaveOutside.h"
//// EVENTS
const Script_fn_t SilverCaveOutside_SceneScripts[] = {
    0,
};

const struct MapCallback SilverCaveOutside_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, SilverCaveOutside_MapScripts_FlyPoint),
};

const struct MapScripts SilverCaveOutside_MapScripts = {
    .scene_script_count = 0, // lengthof(SilverCaveOutside_SceneScripts),
    .scene_scripts = SilverCaveOutside_SceneScripts,

    .callback_count = lengthof(SilverCaveOutside_MapCallbacks),
    .callbacks = SilverCaveOutside_MapCallbacks,
};

static const struct CoordEvent SilverCaveOutside_CoordEvents[] = {
    0,
};

static const struct BGEvent SilverCaveOutside_BGEvents[] = {
    bg_event(24, 19, BGEVENT_READ, &MtSilverPokecenterSign),
    bg_event(17, 13, BGEVENT_READ, &MtSilverSign),
    bg_event(9, 25, BGEVENT_ITEM, &SilverCaveOutsideHiddenFullRestore),
};

static const struct WarpEventData SilverCaveOutside_WarpEvents[] = {
    warp_event(23, 19, SILVER_CAVE_POKECENTER_1F, 1),
    warp_event(18, 11, SILVER_CAVE_ROOM_1, 1),
};

static const struct ObjEvent SilverCaveOutside_ObjectEvents[] = {
    0,
};

const struct MapEvents SilverCaveOutside_MapEvents = {
    .warp_event_count = lengthof(SilverCaveOutside_WarpEvents),
    .warp_events = SilverCaveOutside_WarpEvents,

    .coord_event_count = 0, // lengthof(SilverCaveOutside_CoordEvents),
    .coord_events = SilverCaveOutside_CoordEvents,

    .bg_event_count = lengthof(SilverCaveOutside_BGEvents),
    .bg_events = SilverCaveOutside_BGEvents,

    .obj_event_count = 0, // lengthof(SilverCaveOutside_ObjectEvents),
    .obj_events = SilverCaveOutside_ObjectEvents,
};

//// CODE

bool SilverCaveOutside_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_SILVER_CAVE)
    s_endcallback
    SCRIPT_END
}
bool MtSilverPokecenterSign(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool MtSilverSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(MtSilverSignText)
    SCRIPT_END
}
const struct HiddenItem SilverCaveOutsideHiddenFullRestore = {FULL_RESTORE, EVENT_SILVER_CAVE_OUTSIDE_HIDDEN_FULL_RESTORE};
const txt_cmd_s MtSilverSignText[] = {
    text_start("MT.SILVER"
        t_done )
    //db(0, 0) // filler
};
