#include "../constants.h"
#include "../util/scripting.h"
#include "IlexForestAzaleaGate.h"
//// EVENTS
enum {
    ILEXFORESTAZALEAGATE_OFFICER = 2,
    ILEXFORESTAZALEAGATE_GRANNY,
};

const Script_fn_t IlexForestAzaleaGate_SceneScripts[] = {
    0,
};

const struct MapCallback IlexForestAzaleaGate_MapCallbacks[] = {
    0,
};

const struct MapScripts IlexForestAzaleaGate_MapScripts = {
    .scene_script_count = 0, // lengthof(IlexForestAzaleaGate_SceneScripts),
    .scene_scripts = IlexForestAzaleaGate_SceneScripts,

    .callback_count = 0, // lengthof(IlexForestAzaleaGate_MapCallbacks),
    .callbacks = IlexForestAzaleaGate_MapCallbacks,
};

static const struct CoordEvent IlexForestAzaleaGate_CoordEvents[] = {
    0,
};

static const struct BGEvent IlexForestAzaleaGate_BGEvents[] = {
    0,
};

static const struct WarpEventData IlexForestAzaleaGate_WarpEvents[] = {
    warp_event(0, 4, ILEX_FOREST, 2),
    warp_event(0, 5, ILEX_FOREST, 3),
    warp_event(9, 4, AZALEA_TOWN, 7),
    warp_event(9, 5, AZALEA_TOWN, 8),
};

static const struct ObjEvent IlexForestAzaleaGate_ObjectEvents[] = {
    object_event(5, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &IlexForestAzaleaGateOfficerScript, -1),
    object_event(1, 3, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &IlexForestAzaleaGateGrannyScript, -1),
};

const struct MapEvents IlexForestAzaleaGate_MapEvents = {
    .warp_event_count = lengthof(IlexForestAzaleaGate_WarpEvents),
    .warp_events = IlexForestAzaleaGate_WarpEvents,

    .coord_event_count = 0, // lengthof(IlexForestAzaleaGate_CoordEvents),
    .coord_events = IlexForestAzaleaGate_CoordEvents,

    .bg_event_count = 0, // lengthof(IlexForestAzaleaGate_BGEvents),
    .bg_events = IlexForestAzaleaGate_BGEvents,

    .obj_event_count = lengthof(IlexForestAzaleaGate_ObjectEvents),
    .obj_events = IlexForestAzaleaGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "IlexForestAzaleaGate.h"

bool IlexForestAzaleaGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(IlexForestAzaleaGateOfficerText)
    SCRIPT_END
}
bool IlexForestAzaleaGateGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(IlexForestAzaleaGateGrannyText)
    SCRIPT_END
}
const txt_cmd_s IlexForestAzaleaGateOfficerText[] = {
    text_start("ILEX FOREST is"
        t_line "big. Be careful!"
        t_cont "Don't get lost."
        t_done )
};
const txt_cmd_s IlexForestAzaleaGateGrannyText[] = {
    text_start("The FOREST is"
        t_line "watched over by"
        t_cont "its protector."
        t_para "Stay out of"
        t_line "mischief!"
        t_done )
    //db(0, 0) // filler
};
