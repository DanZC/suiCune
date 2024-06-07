#include "../constants.h"
#include "../util/scripting.h"
#include "OlivinePortPassage.h"
//// EVENTS
enum {
    OLIVINEPORTPASSAGE_POKEFAN_M = 2,
};

const Script_fn_t OlivinePortPassage_SceneScripts[] = {
    0,
};

const struct MapCallback OlivinePortPassage_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivinePortPassage_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivinePortPassage_SceneScripts),
    .scene_scripts = OlivinePortPassage_SceneScripts,

    .callback_count = 0, // lengthof(OlivinePortPassage_MapCallbacks),
    .callbacks = OlivinePortPassage_MapCallbacks,
};

static const struct CoordEvent OlivinePortPassage_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivinePortPassage_BGEvents[] = {
    0,
};

static const struct WarpEventData OlivinePortPassage_WarpEvents[] = {
    warp_event(15, 0, OLIVINE_CITY, 10),
    warp_event(16, 0, OLIVINE_CITY, 11),
    warp_event(15, 4, OLIVINE_PORT_PASSAGE, 4),
    warp_event(3, 2, OLIVINE_PORT_PASSAGE, 3),
    warp_event(3, 14, OLIVINE_PORT, 1),
};

static const struct ObjEvent OlivinePortPassage_ObjectEvents[] = {
    object_event(17, 1, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePortPassagePokefanMScript, EVENT_OLIVINE_PORT_PASSAGE_POKEFAN_M),
};

const struct MapEvents OlivinePortPassage_MapEvents = {
    .warp_event_count = lengthof(OlivinePortPassage_WarpEvents),
    .warp_events = OlivinePortPassage_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivinePortPassage_CoordEvents),
    .coord_events = OlivinePortPassage_CoordEvents,

    .bg_event_count = 0, // lengthof(OlivinePortPassage_BGEvents),
    .bg_events = OlivinePortPassage_BGEvents,

    .obj_event_count = lengthof(OlivinePortPassage_ObjectEvents),
    .obj_events = OlivinePortPassage_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivinePortPassage.h"

bool OlivinePortPassagePokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivinePortPassagePokefanMText)
    SCRIPT_END
}
const txt_cmd_s OlivinePortPassagePokefanMText[] = {
    text_start("FAST SHIP S.S.AQUA"
        t_line "sails to KANTO on"
        t_para "Mondays and Fri-"
        t_line "days."
        t_done )
    //db(0, 0) // filler
};
