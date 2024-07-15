#include "../constants.h"
#include "../util/scripting.h"
#include "ViridianPokecenter1F.h"
//// EVENTS
enum {
    VIRIDIANPOKECENTER1F_NURSE = 2,
    VIRIDIANPOKECENTER1F_COOLTRAINER_M,
    VIRIDIANPOKECENTER1F_COOLTRAINER_F,
    VIRIDIANPOKECENTER1F_BUG_CATCHER,
};

const Script_fn_t ViridianPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback ViridianPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts ViridianPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(ViridianPokecenter1F_SceneScripts),
    .scene_scripts = ViridianPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(ViridianPokecenter1F_MapCallbacks),
    .callbacks = ViridianPokecenter1F_MapCallbacks,
};

static const struct CoordEvent ViridianPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent ViridianPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData ViridianPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, VIRIDIAN_CITY, 5),
    warp_event(4, 7, VIRIDIAN_CITY, 5),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent ViridianPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ViridianPokecenter1FNurseScript, -1),
    object_event(8, 4, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &ViridianPokecenter1FCooltrainerMScript, -1),
    object_event(5, 3, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &ViridianPokecenter1FCooltrainerFScript, -1),
    object_event(1, 6, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &ViridianPokecenter1FBugCatcherScript, -1),
};

const struct MapEvents ViridianPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(ViridianPokecenter1F_WarpEvents),
    .warp_events = ViridianPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(ViridianPokecenter1F_CoordEvents),
    .coord_events = ViridianPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(ViridianPokecenter1F_BGEvents),
    .bg_events = ViridianPokecenter1F_BGEvents,

    .obj_event_count = lengthof(ViridianPokecenter1F_ObjectEvents),
    .obj_events = ViridianPokecenter1F_ObjectEvents,
};

//// CODE

bool ViridianPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool ViridianPokecenter1FCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_BLUE_IN_CINNABAR)
    iftrue(BlueReturned)
    writetext(ViridianPokecenter1FCooltrainerMText)
    waitbutton
    closetext
    s_end
BlueReturned:
    writetext(ViridianPokecenter1FCooltrainerMText_BlueReturned)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool ViridianPokecenter1FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(ViridianPokecenter1FCooltrainerFText)
    SCRIPT_END
}
bool ViridianPokecenter1FBugCatcherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(ViridianPokecenter1FBugCatcherText)
    SCRIPT_END
}
const txt_cmd_s ViridianPokecenter1FCooltrainerMText[] = {
    text_start("Where in the world"
        t_line "is VIRIDIAN's GYM"
        t_para "LEADER? I wanted"
        t_line "to challenge him."
        t_done )
};
const txt_cmd_s ViridianPokecenter1FCooltrainerMText_BlueReturned[] = {
    text_start("There are no GYM"
        t_line "TRAINERS at the"
        t_cont "VIRIDIAN GYM."
        t_para "The LEADER claims"
        t_line "his policy is to"
        t_para "win without having"
        t_line "any underlings."
        t_done )
};
const txt_cmd_s ViridianPokecenter1FCooltrainerFText[] = {
    text_start("I heard that the"
        t_line "GYM in CINNABAR is"
        t_cont "gone."
        t_para "I wonder what be-"
        t_line "came of BLAINE,"
        t_cont "the GYM LEADER."
        t_done )
};
const txt_cmd_s ViridianPokecenter1FBugCatcherText[] = {
    text_start("My dream is to be-"
        t_line "come a GYM LEADER."
        t_done )
    //db(0, 0) // filler
};
