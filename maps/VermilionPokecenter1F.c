#include "../constants.h"
#include "../util/scripting.h"
#include "VermilionPokecenter1F.h"
//// EVENTS
enum {
    VERMILIONPOKECENTER1F_NURSE = 2,
    VERMILIONPOKECENTER1F_FISHING_GURU,
    VERMILIONPOKECENTER1F_SAILOR,
    VERMILIONPOKECENTER1F_BUG_CATCHER,
};

const Script_fn_t VermilionPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback VermilionPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts VermilionPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(VermilionPokecenter1F_SceneScripts),
    .scene_scripts = VermilionPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(VermilionPokecenter1F_MapCallbacks),
    .callbacks = VermilionPokecenter1F_MapCallbacks,
};

static const struct CoordEvent VermilionPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent VermilionPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData VermilionPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, VERMILION_CITY, 2),
    warp_event(4, 7, VERMILION_CITY, 2),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent VermilionPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VermilionPokecenter1FNurseScript, -1),
    object_event(7, 2, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &VermilionPokecenter1FFishingGuruScript, -1),
    object_event(6, 5, SPRITE_SAILOR, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &VermilionPokecenter1FSailorScript, -1),
    object_event(1, 5, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &VermilionPokecenter1FBugCatcherScript, -1),
};

const struct MapEvents VermilionPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(VermilionPokecenter1F_WarpEvents),
    .warp_events = VermilionPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(VermilionPokecenter1F_CoordEvents),
    .coord_events = VermilionPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(VermilionPokecenter1F_BGEvents),
    .bg_events = VermilionPokecenter1F_BGEvents,

    .obj_event_count = lengthof(VermilionPokecenter1F_ObjectEvents),
    .obj_events = VermilionPokecenter1F_ObjectEvents,
};

//// CODE

bool VermilionPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool VermilionPokecenter1FFishingGuruScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_FOUGHT_SNORLAX)
    iftrue(FoughtSnorlax)
    writetext(VermilionPokecenter1FFishingGuruText)
    waitbutton
    closetext
    s_end
FoughtSnorlax:
    writetext(VermilionPokecenter1FFishingGuruText_FoughtSnorlax)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool VermilionPokecenter1FSailorScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionPokecenter1FSailorText)
    SCRIPT_END
}
bool VermilionPokecenter1FBugCatcherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionPokecenter1FBugCatcherText)
    SCRIPT_END
}
const txt_cmd_s VermilionPokecenter1FFishingGuruText[] = {
    text_start("A sleeping #MON"
        t_line "is lying in front"
        t_cont "of DIGLETT'S CAVE."
        t_para "It's a fantastic"
        t_line "opportunity to get"
        t_para "it, but how do you"
        t_line "wake it up?"
        t_done )
};
const txt_cmd_s VermilionPokecenter1FFishingGuruText_FoughtSnorlax[] = {
    text_start("There used to be a"
        t_line "sleeping #MON"
        t_para "lying in front of"
        t_line "DIGLETT'S CAVE."
        t_para "But it seems to"
        t_line "have disappeared."
        t_done )
};
const txt_cmd_s VermilionPokecenter1FSailorText[] = {
    text_start("The FAST SHIP is a"
        t_line "great place to"
        t_para "meet and battle"
        t_line "trainers."
        t_done )
};
const txt_cmd_s VermilionPokecenter1FBugCatcherText[] = {
    text_start("Oh? You have some"
        t_line "BADGES I've never"
        t_cont "seen before."
        t_para "Oh, I get it. You"
        t_line "got them in JOHTO."
        t_done )
    //db(0, 0) // filler
};
