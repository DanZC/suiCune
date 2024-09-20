#include "../constants.h"
#include "../util/scripting.h"
#include "CinnabarPokecenter1F.h"
//// EVENTS
enum {
    CINNABARPOKECENTER1F_NURSE = 2,
    CINNABARPOKECENTER1F_COOLTRAINER_F,
    CINNABARPOKECENTER1F_FISHER,
};

const Script_fn_t CinnabarPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback CinnabarPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts CinnabarPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(CinnabarPokecenter1F_SceneScripts),
    .scene_scripts = CinnabarPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(CinnabarPokecenter1F_MapCallbacks),
    .callbacks = CinnabarPokecenter1F_MapCallbacks,
};

static const struct CoordEvent CinnabarPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent CinnabarPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData CinnabarPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, CINNABAR_ISLAND, 1),
    warp_event(4, 7, CINNABAR_ISLAND, 1),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent CinnabarPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CinnabarPokecenter1FNurseScript, -1),
    object_event(7, 6, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CinnabarPokecenter1FCooltrainerFScript, -1),
    object_event(2, 4, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CinnabarPokecenter1FFisherScript, -1),
};

const struct MapEvents CinnabarPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(CinnabarPokecenter1F_WarpEvents),
    .warp_events = CinnabarPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(CinnabarPokecenter1F_CoordEvents),
    .coord_events = CinnabarPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(CinnabarPokecenter1F_BGEvents),
    .bg_events = CinnabarPokecenter1F_BGEvents,

    .obj_event_count = lengthof(CinnabarPokecenter1F_ObjectEvents),
    .obj_events = CinnabarPokecenter1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CinnabarPokecenter1F.h"

bool CinnabarPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool CinnabarPokecenter1FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CinnabarPokecenter1FCooltrainerFText)
    SCRIPT_END
}
bool CinnabarPokecenter1FFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CinnabarPokecenter1FFisherText)
    SCRIPT_END
}
const txt_cmd_s CinnabarPokecenter1FCooltrainerFText[] = {
    text_start("CINNABAR GYM's"
        t_line "BLAINE apparently"
        t_para "lives alone in the"
        t_line "SEAFOAM ISLANDS"
        t_cont "cave…"
        t_done )
};
const txt_cmd_s CinnabarPokecenter1FFisherText[] = {
    text_start("It's been a year"
        t_line "since the volcano"
        t_cont "erupted."
        t_done )
    //db(0, 0) // filler
};
