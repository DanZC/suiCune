#include "../constants.h"
#include "../util/scripting.h"
#include "VermilionDiglettsCaveSpeechHouse.h"
//// EVENTS
enum {
    VERMILIONDIGLETTSCAVESPEECHHOUSE_GENTLEMAN = 2,
};

const Script_fn_t VermilionDiglettsCaveSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback VermilionDiglettsCaveSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts VermilionDiglettsCaveSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(VermilionDiglettsCaveSpeechHouse_SceneScripts),
    .scene_scripts = VermilionDiglettsCaveSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(VermilionDiglettsCaveSpeechHouse_MapCallbacks),
    .callbacks = VermilionDiglettsCaveSpeechHouse_MapCallbacks,
};

static const struct CoordEvent VermilionDiglettsCaveSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent VermilionDiglettsCaveSpeechHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData VermilionDiglettsCaveSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, VERMILION_CITY, 6),
    warp_event(3, 7, VERMILION_CITY, 6),
};

static const struct ObjEvent VermilionDiglettsCaveSpeechHouse_ObjectEvents[] = {
    object_event(1, 3, SPRITE_GENTLEMAN, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &VermilionDiglettsCaveSpeechHouseGentlemanScript, -1),
};

const struct MapEvents VermilionDiglettsCaveSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(VermilionDiglettsCaveSpeechHouse_WarpEvents),
    .warp_events = VermilionDiglettsCaveSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(VermilionDiglettsCaveSpeechHouse_CoordEvents),
    .coord_events = VermilionDiglettsCaveSpeechHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(VermilionDiglettsCaveSpeechHouse_BGEvents),
    .bg_events = VermilionDiglettsCaveSpeechHouse_BGEvents,

    .obj_event_count = lengthof(VermilionDiglettsCaveSpeechHouse_ObjectEvents),
    .obj_events = VermilionDiglettsCaveSpeechHouse_ObjectEvents,
};

//// CODE

bool VermilionDiglettsCaveSpeechHouseGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionDiglettsCaveSpeechHouseGentlemanText)
    SCRIPT_END
}
const txt_cmd_s VermilionDiglettsCaveSpeechHouseGentlemanText[] = {
    text_start("Over many years,"
        t_line "DIGLETT dug a"
        t_cont "large tunnel."
        t_para "That tunnel goes"
        t_line "to a distant town."
        t_done )
    //db(0, 0) // filler
};
