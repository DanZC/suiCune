#include "../constants.h"
#include "../util/scripting.h"
#include "CherrygrovePokecenter1F.h"
//// EVENTS
enum {
    CHERRYGROVEPOKECENTER1F_NURSE,
    CHERRYGROVEPOKECENTER1F_FISHER,
    CHERRYGROVEPOKECENTER1F_GENTLEMAN,
    CHERRYGROVEPOKECENTER1F_TEACHER,
};

const Script_fn_t CherrygrovePokecenter1F_SceneScripts[] = {
};

const struct MapCallback CherrygrovePokecenter1F_MapCallbacks[] = {
};

const struct MapScripts CherrygrovePokecenter1F_MapScripts = {
    .scene_script_count = lengthof(CherrygrovePokecenter1F_SceneScripts),
    .scene_scripts = CherrygrovePokecenter1F_SceneScripts,

    .callback_count = lengthof(CherrygrovePokecenter1F_MapCallbacks),
    .callbacks = CherrygrovePokecenter1F_MapCallbacks,
};

static const struct CoordEvent CherrygrovePokecenter1F_CoordEvents[] = {
};

static const struct BGEvent CherrygrovePokecenter1F_BGEvents[] = {
};

static const struct WarpEventData CherrygrovePokecenter1F_WarpEvents[] = {
    warp_event(3, 7, CHERRYGROVE_CITY, 2),
    warp_event(4, 7, CHERRYGROVE_CITY, 2),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent CherrygrovePokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CherrygrovePokecenter1FNurseScript, -1),
    object_event(2, 3, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CherrygrovePokecenter1FFisherScript, -1),
    object_event(8, 6, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CherrygrovePokecenter1FGentlemanScript, -1),
    object_event(1, 6, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CherrygrovePokecenter1FTeacherScript, -1),
};

const struct MapEvents CherrygrovePokecenter1F_MapEvents = {
    .warp_event_count = lengthof(CherrygrovePokecenter1F_WarpEvents),
    .warp_events = CherrygrovePokecenter1F_WarpEvents,

    .coord_event_count = lengthof(CherrygrovePokecenter1F_CoordEvents),
    .coord_events = CherrygrovePokecenter1F_CoordEvents,

    .bg_event_count = lengthof(CherrygrovePokecenter1F_BGEvents),
    .bg_events = CherrygrovePokecenter1F_BGEvents,

    .obj_event_count = lengthof(CherrygrovePokecenter1F_ObjectEvents),
    .obj_events = CherrygrovePokecenter1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CherrygrovePokecenter1F.h"

// bool CherrygrovePokecenter1F_MapScripts(script_s* s) {
//     SCRIPT_BEGIN
//     SCRIPT_FALLTHROUGH(CherrygrovePokecenter1FNurseScript)
// }
bool CherrygrovePokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool CherrygrovePokecenter1FFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CherrygrovePokecenter1FFisherText)
    SCRIPT_END
}
bool CherrygrovePokecenter1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CherrygrovePokecenter1FGentlemanText)
    SCRIPT_END
}
bool CherrygrovePokecenter1FTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue(CommCenterOpen)
    writetext(CherrygrovePokecenter1FTeacherText)
    waitbutton
    closetext
    s_end
CommCenterOpen:
    writetext(CherrygrovePokecenter1FTeacherText_CommCenterOpen)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct TextCmd CherrygrovePokecenter1FFisherText[] = {
    text_start("It's great. I can"
        t_line "store any number"
        t_para "of #MON, and"
        t_line "it's all free."
        t_done )
};
const struct TextCmd CherrygrovePokecenter1FGentlemanText[] = {
    text_start("That PC is free"
        t_line "for any trainer"
        t_cont "to use."
        t_done )
};
const struct TextCmd CherrygrovePokecenter1FTeacherText[] = {
    text_start("The COMMUNICATION"
        t_line "CENTER upstairs"
        t_cont "was just built."
        t_para "But they're still"
        t_line "finishing it up."
        t_done )
};
const struct TextCmd CherrygrovePokecenter1FTeacherText_CommCenterOpen[] = {
    text_start("The COMMUNICATION"
        t_line "CENTER upstairs"
        t_cont "was just built."
        t_para "I traded #MON"
        t_line "there already!"
        t_done )
};
// bool CherrygrovePokecenter1F_MapEvents(script_s* s) {
//     SCRIPT_BEGIN
//     //db(0, 0) // filler
//     SCRIPT_END
// }
