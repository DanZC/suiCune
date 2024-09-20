#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonDeptStore1F.h"
//// EVENTS
enum {
    CELADONDEPTSTORE1F_RECEPTIONIST = 2,
    CELADONDEPTSTORE1F_GENTLEMAN,
    CELADONDEPTSTORE1F_TEACHER,
};

const Script_fn_t CeladonDeptStore1F_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonDeptStore1F_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonDeptStore1F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonDeptStore1F_SceneScripts),
    .scene_scripts = CeladonDeptStore1F_SceneScripts,

    .callback_count = 0, // lengthof(CeladonDeptStore1F_MapCallbacks),
    .callbacks = CeladonDeptStore1F_MapCallbacks,
};

static const struct CoordEvent CeladonDeptStore1F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonDeptStore1F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &CeladonDeptStore1FDirectory),
    bg_event(3, 0, BGEVENT_READ, &CeladonDeptStore1FElevatorButton),
};

static const struct WarpEventData CeladonDeptStore1F_WarpEvents[] = {
    warp_event(7, 7, CELADON_CITY, 1),
    warp_event(8, 7, CELADON_CITY, 1),
    warp_event(15, 0, CELADON_DEPT_STORE_2F, 2),
    warp_event(2, 0, CELADON_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent CeladonDeptStore1F_ObjectEvents[] = {
    object_event(10, 1, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore1FReceptionistScript, -1),
    object_event(11, 4, SPRITE_GENTLEMAN, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore1FGentlemanScript, -1),
    object_event(5, 3, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore1FTeacherScript, -1),
};

const struct MapEvents CeladonDeptStore1F_MapEvents = {
    .warp_event_count = lengthof(CeladonDeptStore1F_WarpEvents),
    .warp_events = CeladonDeptStore1F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonDeptStore1F_CoordEvents),
    .coord_events = CeladonDeptStore1F_CoordEvents,

    .bg_event_count = lengthof(CeladonDeptStore1F_BGEvents),
    .bg_events = CeladonDeptStore1F_BGEvents,

    .obj_event_count = lengthof(CeladonDeptStore1F_ObjectEvents),
    .obj_events = CeladonDeptStore1F_ObjectEvents,
};

//// CODE

bool CeladonDeptStore1FReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore1FReceptionistText)
    SCRIPT_END
}
bool CeladonDeptStore1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore1FGentlemanText)
    SCRIPT_END
}
bool CeladonDeptStore1FTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore1FTeacherText)
    SCRIPT_END
}
bool CeladonDeptStore1FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonDeptStore1FDirectoryText)
    SCRIPT_END
}
bool CeladonDeptStore1FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s CeladonDeptStore1FReceptionistText[] = {
    text_start("Hello! Welcome to"
        t_line "CELADON DEPT."
        t_cont "STORE!"
        t_para "The directory is"
        t_line "on the wall."
        t_done )
};
const txt_cmd_s CeladonDeptStore1FGentlemanText[] = {
    text_start("This DEPT.STORE is"
        t_line "part of the same"
        t_para "chain as the one"
        t_line "in GOLDENROD CITY."
        t_para "They were both"
        t_line "renovated at the"
        t_cont "same time."
        t_done )
};
const txt_cmd_s CeladonDeptStore1FTeacherText[] = {
    text_start("This is my first"
        t_line "time here."
        t_para "It's so big…"
        t_para "I'm afraid I'll"
        t_line "get lost."
        t_done )
};
const txt_cmd_s CeladonDeptStore1FDirectoryText[] = {
    text_start("1F: SERVICE"
        t_line "    COUNTER"
        t_para "2F: TRAINER'S"
        t_line "    MARKET"
        t_para "3F: TM SHOP"
        t_para "4F: WISEMAN GIFTS"
        t_para "5F: DRUG STORE"
        t_para "6F: ROOFTOP"
        t_line "    SQUARE"
        t_done )
    //db(0, 0) // filler
};
