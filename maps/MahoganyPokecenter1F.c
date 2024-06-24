#include "../constants.h"
#include "../util/scripting.h"
#include "MahoganyPokecenter1F.h"
//// EVENTS
enum {
    MAHOGANYPOKECENTER1F_NURSE = 2,
    MAHOGANYPOKECENTER1F_POKEFAN_M,
    MAHOGANYPOKECENTER1F_YOUNGSTER,
    MAHOGANYPOKECENTER1F_COOLTRAINER_F,
};

const Script_fn_t MahoganyPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback MahoganyPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts MahoganyPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(MahoganyPokecenter1F_SceneScripts),
    .scene_scripts = MahoganyPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(MahoganyPokecenter1F_MapCallbacks),
    .callbacks = MahoganyPokecenter1F_MapCallbacks,
};

static const struct CoordEvent MahoganyPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent MahoganyPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData MahoganyPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, MAHOGANY_TOWN, 4),
    warp_event(4, 7, MAHOGANY_TOWN, 4),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent MahoganyPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MahoganyPokecenter1FNurseScript, -1),
    object_event(7, 2, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &MahoganyPokecenter1FPokefanMScript, -1),
    object_event(1, 3, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &MahoganyPokecenter1FYoungsterScript, -1),
    object_event(2, 3, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MahoganyPokecenter1FCooltrainerFScript, -1),
};

const struct MapEvents MahoganyPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(MahoganyPokecenter1F_WarpEvents),
    .warp_events = MahoganyPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(MahoganyPokecenter1F_CoordEvents),
    .coord_events = MahoganyPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(MahoganyPokecenter1F_BGEvents),
    .bg_events = MahoganyPokecenter1F_BGEvents,

    .obj_event_count = lengthof(MahoganyPokecenter1F_ObjectEvents),
    .obj_events = MahoganyPokecenter1F_ObjectEvents,
};

//// CODE

bool MahoganyPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool MahoganyPokecenter1FPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(MahoganyPokecenter1FPokefanMText)
    SCRIPT_END
}
bool MahoganyPokecenter1FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(MahoganyPokecenter1FYoungsterText)
    SCRIPT_END
}
bool MahoganyPokecenter1FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(MahoganyPokecenter1FCooltrainerFText)
    SCRIPT_END
}
const txt_cmd_s MahoganyPokecenter1FPokefanMText[] = {
    text_start("What's this? TEAM"
        t_line "ROCKET has come"
        t_cont "back?"
        t_para "I saw some men in"
        t_line "black at LAKE OF"
        t_cont "RAGE…"
        t_done )
};
const txt_cmd_s MahoganyPokecenter1FYoungsterText[] = {
    text_start("I stop my #MON"
        t_line "from evolving too"
        t_cont "early."
        t_para "I make them learn"
        t_line "certain moves be-"
        t_cont "fore I let them"
        t_cont "evolve."
        t_done )
};
const txt_cmd_s MahoganyPokecenter1FCooltrainerFText[] = {
    text_start("#MON do become"
        t_line "stronger when they"
        t_para "evolve, but they"
        t_line "also learn moves"
        t_cont "more slowly."
        t_done )
    //db(0, 0) // filler
};
