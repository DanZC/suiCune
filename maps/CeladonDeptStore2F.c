#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonDeptStore2F.h"
//// EVENTS
enum {
    CELADONDEPTSTORE2F_CLERK1 = 2,
    CELADONDEPTSTORE2F_CLERK2,
    CELADONDEPTSTORE2F_POKEFAN_M,
    CELADONDEPTSTORE2F_YOUNGSTER,
};

const Script_fn_t CeladonDeptStore2F_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonDeptStore2F_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonDeptStore2F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonDeptStore2F_SceneScripts),
    .scene_scripts = CeladonDeptStore2F_SceneScripts,

    .callback_count = 0, // lengthof(CeladonDeptStore2F_MapCallbacks),
    .callbacks = CeladonDeptStore2F_MapCallbacks,
};

static const struct CoordEvent CeladonDeptStore2F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonDeptStore2F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &CeladonDeptStore2FDirectory),
    bg_event(3, 0, BGEVENT_READ, &CeladonDeptStore2FElevatorButton),
};

static const struct WarpEventData CeladonDeptStore2F_WarpEvents[] = {
    warp_event(12, 0, CELADON_DEPT_STORE_3F, 1),
    warp_event(15, 0, CELADON_DEPT_STORE_1F, 3),
    warp_event(2, 0, CELADON_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent CeladonDeptStore2F_ObjectEvents[] = {
    object_event(13, 5, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore2FClerk1Script, -1),
    object_event(14, 5, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore2FClerk2Script, -1),
    object_event(5, 2, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore2FPokefanMScript, -1),
    object_event(6, 2, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore2FYoungsterScript, -1),
};

const struct MapEvents CeladonDeptStore2F_MapEvents = {
    .warp_event_count = lengthof(CeladonDeptStore2F_WarpEvents),
    .warp_events = CeladonDeptStore2F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonDeptStore2F_CoordEvents),
    .coord_events = CeladonDeptStore2F_CoordEvents,

    .bg_event_count = lengthof(CeladonDeptStore2F_BGEvents),
    .bg_events = CeladonDeptStore2F_BGEvents,

    .obj_event_count = lengthof(CeladonDeptStore2F_ObjectEvents),
    .obj_events = CeladonDeptStore2F_ObjectEvents,
};

//// CODE

bool CeladonDeptStore2FClerk1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_CELADON_2F_1)
    closetext
    s_end
    SCRIPT_END
}
bool CeladonDeptStore2FClerk2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_CELADON_2F_2)
    closetext
    s_end
    SCRIPT_END
}
bool CeladonDeptStore2FPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore2FPokefanMText)
    SCRIPT_END
}
bool CeladonDeptStore2FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore2FYoungsterText)
    SCRIPT_END
}
bool CeladonDeptStore2FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonDeptStore2FDirectoryText)
    SCRIPT_END
}
bool CeladonDeptStore2FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s CeladonDeptStore2FPokefanMText[] = {
    text_start("I just recently"
        t_line "became a trainer."
        t_para "My son encouraged"
        t_line "me to do it."
        t_para "I'm impressed by"
        t_line "the selection of"
        t_cont "convenient items."
        t_done )
};
const txt_cmd_s CeladonDeptStore2FYoungsterText[] = {
    text_start("My dad's having a"
        t_line "hard time learning"
        t_para "the names of items"
        t_line "and how they are"
        t_para "supposed to be"
        t_line "used…"
        t_done )
};
const txt_cmd_s CeladonDeptStore2FDirectoryText[] = {
    text_start("Top Grade Items"
        t_line "for Trainers!"
        t_para "2F: TRAINER'S"
        t_line "    MARKET"
        t_done )
    //db(0, 0) // filler
};
