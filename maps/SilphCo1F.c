#include "../constants.h"
#include "../util/scripting.h"
#include "SilphCo1F.h"
//// EVENTS
enum {
    SILPHCO1F_RECEPTIONIST = 2,
    SILPHCO1F_OFFICER,
};

const Script_fn_t SilphCo1F_SceneScripts[] = {
    0,
};

const struct MapCallback SilphCo1F_MapCallbacks[] = {
    0,
};

const struct MapScripts SilphCo1F_MapScripts = {
    .scene_script_count = 0, // lengthof(SilphCo1F_SceneScripts),
    .scene_scripts = SilphCo1F_SceneScripts,

    .callback_count = 0, // lengthof(SilphCo1F_MapCallbacks),
    .callbacks = SilphCo1F_MapCallbacks,
};

static const struct CoordEvent SilphCo1F_CoordEvents[] = {
    0,
};

static const struct BGEvent SilphCo1F_BGEvents[] = {
    0,
};

static const struct WarpEventData SilphCo1F_WarpEvents[] = {
    warp_event(2, 7, SAFFRON_CITY, 7),
    warp_event(3, 7, SAFFRON_CITY, 7),
};

static const struct ObjEvent SilphCo1F_ObjectEvents[] = {
    object_event(4, 2, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SilphCoReceptionistScript, -1),
    object_event(13, 1, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SilphCoOfficerScript, -1),
};

const struct MapEvents SilphCo1F_MapEvents = {
    .warp_event_count = lengthof(SilphCo1F_WarpEvents),
    .warp_events = SilphCo1F_WarpEvents,

    .coord_event_count = 0, // lengthof(SilphCo1F_CoordEvents),
    .coord_events = SilphCo1F_CoordEvents,

    .bg_event_count = 0, // lengthof(SilphCo1F_BGEvents),
    .bg_events = SilphCo1F_BGEvents,

    .obj_event_count = lengthof(SilphCo1F_ObjectEvents),
    .obj_events = SilphCo1F_ObjectEvents,
};

//// CODE

bool SilphCoReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SilphCoReceptionistText)
    SCRIPT_END
}
bool SilphCoOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_UP_GRADE)
    iftrue(GotUpGrade)
    writetext(SilphCoOfficerText)
    promptbutton
    verbosegiveitem(UP_GRADE, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_UP_GRADE)
GotUpGrade:
    writetext(SilphCoOfficerText_GotUpGrade)
    waitbutton
NoRoom:
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s SilphCoReceptionistText[] = {
    text_start("Welcome. This is"
        t_line "SILPH CO.'s HEAD"
        t_cont "OFFICE BUILDING."
        t_done )
};
const txt_cmd_s SilphCoOfficerText[] = {
    text_start("Only employees are"
        t_line "permitted to go"
        t_cont "upstairs."
        t_para "But since you came"
        t_line "such a long way,"
        t_para "have this neat"
        t_line "little souvenir."
        t_done )
};
const txt_cmd_s SilphCoOfficerText_GotUpGrade[] = {
    text_start("It's SILPH CO.'s"
        t_line "latest product."
        t_para "It's not for sale"
        t_line "anywhere yet."
        t_done )
    //db(0, 0) // filler
};
