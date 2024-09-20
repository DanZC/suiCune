#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonMansionRoof.h"
//// EVENTS
enum {
    CELADONMANSIONROOF_FISHER = 2,
};

const Script_fn_t CeladonMansionRoof_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonMansionRoof_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonMansionRoof_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonMansionRoof_SceneScripts),
    .scene_scripts = CeladonMansionRoof_SceneScripts,

    .callback_count = 0, // lengthof(CeladonMansionRoof_MapCallbacks),
    .callbacks = CeladonMansionRoof_MapCallbacks,
};

static const struct CoordEvent CeladonMansionRoof_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonMansionRoof_BGEvents[] = {
    bg_event(6, 1, BGEVENT_LEFT, &CeladonMansionRoofGraffiti),
};

static const struct WarpEventData CeladonMansionRoof_WarpEvents[] = {
    warp_event(1, 1, CELADON_MANSION_3F, 1),
    warp_event(6, 1, CELADON_MANSION_3F, 4),
    warp_event(2, 5, CELADON_MANSION_ROOF_HOUSE, 1),
};

static const struct ObjEvent CeladonMansionRoof_ObjectEvents[] = {
    object_event(7, 5, SPRITE_FISHER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonMansionRoofFisherScript, -1),
};

const struct MapEvents CeladonMansionRoof_MapEvents = {
    .warp_event_count = lengthof(CeladonMansionRoof_WarpEvents),
    .warp_events = CeladonMansionRoof_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonMansionRoof_CoordEvents),
    .coord_events = CeladonMansionRoof_CoordEvents,

    .bg_event_count = lengthof(CeladonMansionRoof_BGEvents),
    .bg_events = CeladonMansionRoof_BGEvents,

    .obj_event_count = lengthof(CeladonMansionRoof_ObjectEvents),
    .obj_events = CeladonMansionRoof_ObjectEvents,
};

//// CODE

bool CeladonMansionRoofFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonMansionRoofFisherText)
    SCRIPT_END
}
bool CeladonMansionRoofGraffiti(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonMansionRoofGraffitiText)
    SCRIPT_END
}
const txt_cmd_s CeladonMansionRoofFisherText[] = {
    text_start("High places--I do"
        t_line "love them so!"
        t_para "I'd say the only"
        t_line "thing that loves"
        t_para "heights as much as"
        t_line "me is smoke!"
        t_done )
};
const txt_cmd_s CeladonMansionRoofGraffitiText[] = {
    text_start("There's graffiti"
        t_line "on the wall…"
        t_para "<PLAYER> added a"
        t_line "moustache!"
        t_done )
    //db(0, 0) // filler
};
