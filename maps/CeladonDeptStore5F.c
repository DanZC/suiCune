#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonDeptStore5F.h"
//// EVENTS
enum {
    CELADONDEPTSTORE5F_CLERK1 = 2,
    CELADONDEPTSTORE5F_CLERK2,
    CELADONDEPTSTORE5F_GENTLEMAN,
    CELADONDEPTSTORE5F_SAILOR,
    CELADONDEPTSTORE5F_TEACHER,
};

const Script_fn_t CeladonDeptStore5F_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonDeptStore5F_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonDeptStore5F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonDeptStore5F_SceneScripts),
    .scene_scripts = CeladonDeptStore5F_SceneScripts,

    .callback_count = 0, // lengthof(CeladonDeptStore5F_MapCallbacks),
    .callbacks = CeladonDeptStore5F_MapCallbacks,
};

static const struct CoordEvent CeladonDeptStore5F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonDeptStore5F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &CeladonDeptStore5FDirectory),
    bg_event(3, 0, BGEVENT_READ, &CeladonDeptStore5FElevatorButton),
};

static const struct WarpEventData CeladonDeptStore5F_WarpEvents[] = {
    warp_event(12, 0, CELADON_DEPT_STORE_4F, 1),
    warp_event(15, 0, CELADON_DEPT_STORE_6F, 1),
    warp_event(2, 0, CELADON_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent CeladonDeptStore5F_ObjectEvents[] = {
    object_event(7, 5, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore5FClerk1Script, -1),
    object_event(8, 5, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore5FClerk2Script, -1),
    object_event(13, 5, SPRITE_GENTLEMAN, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore5FGentlemanScript, -1),
    object_event(3, 4, SPRITE_SAILOR, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore5FSailorScript, -1),
    object_event(1, 7, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore5FTeacherScript, -1),
};

const struct MapEvents CeladonDeptStore5F_MapEvents = {
    .warp_event_count = lengthof(CeladonDeptStore5F_WarpEvents),
    .warp_events = CeladonDeptStore5F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonDeptStore5F_CoordEvents),
    .coord_events = CeladonDeptStore5F_CoordEvents,

    .bg_event_count = lengthof(CeladonDeptStore5F_BGEvents),
    .bg_events = CeladonDeptStore5F_BGEvents,

    .obj_event_count = lengthof(CeladonDeptStore5F_ObjectEvents),
    .obj_events = CeladonDeptStore5F_ObjectEvents,
};

//// CODE

bool CeladonDeptStore5FClerk1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_CELADON_5F_1)
    closetext
    s_end
    SCRIPT_END
}
bool CeladonDeptStore5FClerk2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_CELADON_5F_2)
    closetext
    s_end
    SCRIPT_END
}
bool CeladonDeptStore5FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore5FGentlemanText)
    SCRIPT_END
}
bool CeladonDeptStore5FSailorScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore5FSailorText)
    SCRIPT_END
}
bool CeladonDeptStore5FTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore5FTeacherText)
    SCRIPT_END
}
bool CeladonDeptStore5FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonDeptStore5FDirectoryText)
    SCRIPT_END
}
bool CeladonDeptStore5FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s CeladonDeptStore5FGentlemanText[] = {
    text_start("I want to buy some"
        t_line "items that raise"
        t_para "#MON stats, but"
        t_line "I don't have"
        t_cont "enough money…"
        t_done )
};
const txt_cmd_s CeladonDeptStore5FSailorText[] = {
    text_start("I want PP UP, so I"
        t_line "can raise the PP"
        t_para "of moves. But you"
        t_line "can't buy it…"
        t_done )
};
const txt_cmd_s CeladonDeptStore5FTeacherText[] = {
    text_start("Using items on"
        t_line "them makes #-"
        t_cont "MON happy."
        t_para "They hate certain"
        t_line "items, though…"
        t_done )
};
const txt_cmd_s CeladonDeptStore5FDirectoryText[] = {
    text_start("5F: DRUG STORE"
        t_done )
    //db(0, 0) // filler
};
