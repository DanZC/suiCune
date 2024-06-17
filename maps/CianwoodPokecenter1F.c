#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodPokecenter1F.h"
//// EVENTS
enum {
    CIANWOODPOKECENTER1F_NURSE = 2,
    CIANWOODPOKECENTER1F_LASS,
    CIANWOODPOKECENTER1F_GYM_GUIDE,
    CIANWOODPOKECENTER1F_SUPER_NERD,
};

const Script_fn_t CianwoodPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback CianwoodPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts CianwoodPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(CianwoodPokecenter1F_SceneScripts),
    .scene_scripts = CianwoodPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(CianwoodPokecenter1F_MapCallbacks),
    .callbacks = CianwoodPokecenter1F_MapCallbacks,
};

static const struct CoordEvent CianwoodPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent CianwoodPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData CianwoodPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, CIANWOOD_CITY, 3),
    warp_event(4, 7, CIANWOOD_CITY, 3),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent CianwoodPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodPokecenter1FNurseScript, -1),
    object_event(1, 5, SPRITE_LASS, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CianwoodPokecenter1FLassScript, -1),
    object_event(5, 3, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CianwoodGymGuideScript, -1),
    object_event(8, 6, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CianwoodPokecenter1FSuperNerdScript, -1),
};

const struct MapEvents CianwoodPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(CianwoodPokecenter1F_WarpEvents),
    .warp_events = CianwoodPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(CianwoodPokecenter1F_CoordEvents),
    .coord_events = CianwoodPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(CianwoodPokecenter1F_BGEvents),
    .bg_events = CianwoodPokecenter1F_BGEvents,

    .obj_event_count = lengthof(CianwoodPokecenter1F_ObjectEvents),
    .obj_events = CianwoodPokecenter1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodPokecenter1F.h"

bool CianwoodPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool CianwoodPokecenter1FLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CianwoodPokecenter1FLassText)
    SCRIPT_END
}
bool CianwoodGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    checkevent(EVENT_BEAT_CHUCK)
    iftrue(CianwoodGymGuideWinScript)
    opentext
    writetext(CianwoodGymGuideText)
    waitbutton
    closetext
    s_end
CianwoodGymGuideWinScript:
    opentext
    writetext(CianwoodGymGuideWinText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CianwoodPokecenter1FSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CianwoodPokecenter1FSuperNerdText)
    SCRIPT_END
}
const txt_cmd_s CianwoodPokecenter1FLassText[] = {
    text_start("Did you meet the"
        t_line "#MANIAC?"
        t_para "He's always brag-"
        t_line "ging about his"
        t_cont "rare #MON."
        t_done )
};
const txt_cmd_s CianwoodGymGuideText[] = {
    text_start("The #MON GYM"
        t_line "trainers here are"
        t_cont "macho bullies."
        t_para "If I stick around,"
        t_line "they might come"
        t_cont "after me."
        t_para "Here's some ad-"
        t_line "vice: the GYM"
        t_para "LEADER uses the"
        t_line "fighting-type."
        t_para "So you should"
        t_line "confound him with"
        t_cont "psychic #MON."
        t_para "Wipe out his #-"
        t_line "MON before they"
        t_para "can use their"
        t_line "physical strength."
        t_para "And those boulders"
        t_line "in the middle of"
        t_cont "the GYM?"
        t_para "If you don't move"
        t_line "them correctly,"
        t_para "you won't reach"
        t_line "the GYM LEADER."
        t_para "If you get stuck,"
        t_line "go outside."
        t_done )
};
const txt_cmd_s CianwoodGymGuideWinText[] = {
    text_start("<PLAYER>! You won!"
        t_line "I could tell by"
        t_cont "looking at you!"
        t_done )
};
const txt_cmd_s CianwoodPokecenter1FUnusedText1[] = {
    text_start("Don't you get the"
        t_line "urge to show off"
        t_para "your #MON to"
        t_line "friends?"
        t_para "I wish I could"
        t_line "show the #MON I"
        t_para "raised to my pal"
        t_line "in VIOLET."
        t_done )
};
const txt_cmd_s CianwoodPokecenter1FUnusedText2[] = {
    text_start("I've been battling"
        t_line "my pal in VIOLET"
        t_para "using a MOBILE"
        t_line "ADAPTER link."
        t_para "I'm down 5-7"
        t_line "against him. I've"
        t_cont "gotta crank it up!"
        t_done )
};
const txt_cmd_s CianwoodPokecenter1FSuperNerdText[] = {
    text_start("I love showing off"
        t_line "the #MON that"
        t_para "I've raised."
        t_line "Don't you?"
        t_para "I'm going to get"
        t_line "into a bunch of"
        t_para "battles, and show"
        t_line "off my #MON!"
        t_done )
    //db(0, 0) // filler
};
