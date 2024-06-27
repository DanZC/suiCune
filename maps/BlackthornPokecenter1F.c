#include "../constants.h"
#include "../util/scripting.h"
#include "BlackthornPokecenter1F.h"
//// EVENTS
enum {
    BLACKTHORNPOKECENTER1F_NURSE = 2,
    BLACKTHORNPOKECENTER1F_GENTLEMAN,
    BLACKTHORNPOKECENTER1F_TWIN,
    BLACKTHORNPOKECENTER1F_COOLTRAINER_M,
};

const Script_fn_t BlackthornPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback BlackthornPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts BlackthornPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(BlackthornPokecenter1F_SceneScripts),
    .scene_scripts = BlackthornPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(BlackthornPokecenter1F_MapCallbacks),
    .callbacks = BlackthornPokecenter1F_MapCallbacks,
};

static const struct CoordEvent BlackthornPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent BlackthornPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData BlackthornPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, BLACKTHORN_CITY, 5),
    warp_event(4, 7, BLACKTHORN_CITY, 5),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent BlackthornPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornPokecenter1FNurseScript, -1),
    object_event(5, 3, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BlackthornPokecenter1FGentlemanScript, -1),
    object_event(1, 4, SPRITE_TWIN, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BlackthornPokecenter1FTwinScript, -1),
    object_event(7, 6, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BlackthornPokecenter1FCooltrainerMScript, -1),
};

const struct MapEvents BlackthornPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(BlackthornPokecenter1F_WarpEvents),
    .warp_events = BlackthornPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(BlackthornPokecenter1F_CoordEvents),
    .coord_events = BlackthornPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(BlackthornPokecenter1F_BGEvents),
    .bg_events = BlackthornPokecenter1F_BGEvents,

    .obj_event_count = lengthof(BlackthornPokecenter1F_ObjectEvents),
    .obj_events = BlackthornPokecenter1F_ObjectEvents,
};

//// CODE

bool BlackthornPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool BlackthornPokecenter1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BlackthornPokecenter1FGentlemanText)
    SCRIPT_END
}
bool BlackthornPokecenter1FTwinScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BlackthornPokecenter1FTwinText)
    SCRIPT_END
}
bool BlackthornPokecenter1FCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(HappinessCheckScript)
    SCRIPT_END
}
const txt_cmd_s BlackthornPokecenter1FGentlemanText[] = {
    text_start("Deep inside far-"
        t_line "off INDIGO PLATEAU"
        t_para "is the #MON"
        t_line "LEAGUE."
        t_para "I hear the best"
        t_line "trainers gather"
        t_para "there from around"
        t_line "the country."
        t_done )
};
const txt_cmd_s BlackthornPokecenter1FTwinText[] = {
    text_start("There was this"
        t_line "move I just had"
        t_para "to teach my #-"
        t_line "MON."
        t_para "So I got the MOVE"
        t_line "DELETER to make it"
        t_cont "forget an HM move."
        t_done )
    //db(0, 0) // filler
};
