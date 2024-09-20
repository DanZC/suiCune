#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonDeptStore4F.h"
//// EVENTS
enum {
    CELADONDEPTSTORE4F_CLERK = 2,
    CELADONDEPTSTORE4F_SUPER_NERD,
    CELADONDEPTSTORE4F_YOUNGSTER,
};

const Script_fn_t CeladonDeptStore4F_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonDeptStore4F_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonDeptStore4F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonDeptStore4F_SceneScripts),
    .scene_scripts = CeladonDeptStore4F_SceneScripts,

    .callback_count = 0, // lengthof(CeladonDeptStore4F_MapCallbacks),
    .callbacks = CeladonDeptStore4F_MapCallbacks,
};

static const struct CoordEvent CeladonDeptStore4F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonDeptStore4F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &CeladonDeptStore4FDirectory),
    bg_event(3, 0, BGEVENT_READ, &CeladonDeptStore4FElevatorButton),
};

static const struct WarpEventData CeladonDeptStore4F_WarpEvents[] = {
    warp_event(12, 0, CELADON_DEPT_STORE_5F, 1),
    warp_event(15, 0, CELADON_DEPT_STORE_3F, 2),
    warp_event(2, 0, CELADON_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent CeladonDeptStore4F_ObjectEvents[] = {
    object_event(13, 5, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore4FClerkScript, -1),
    object_event(7, 6, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore4FSuperNerdScript, -1),
    object_event(8, 2, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore4FYoungsterScript, -1),
};

const struct MapEvents CeladonDeptStore4F_MapEvents = {
    .warp_event_count = lengthof(CeladonDeptStore4F_WarpEvents),
    .warp_events = CeladonDeptStore4F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonDeptStore4F_CoordEvents),
    .coord_events = CeladonDeptStore4F_CoordEvents,

    .bg_event_count = lengthof(CeladonDeptStore4F_BGEvents),
    .bg_events = CeladonDeptStore4F_BGEvents,

    .obj_event_count = lengthof(CeladonDeptStore4F_ObjectEvents),
    .obj_events = CeladonDeptStore4F_ObjectEvents,
};

//// CODE

bool CeladonDeptStore4FClerkScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_CELADON_4F)
    closetext
    s_end
    SCRIPT_END
}
bool CeladonDeptStore4FSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore4FSuperNerdText)
    SCRIPT_END
}
bool CeladonDeptStore4FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore4FYoungsterText)
    SCRIPT_END
}
bool CeladonDeptStore4FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonDeptStore4FDirectoryText)
    SCRIPT_END
}
bool CeladonDeptStore4FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s CeladonDeptStore4FSuperNerdText[] = {
    text_start("I'm here to buy"
        t_line "SURF MAIL to send"
        t_cont "to my girlfriend."
        t_done )
};
const txt_cmd_s CeladonDeptStore4FYoungsterText[] = {
    text_start("This is the only"
        t_line "place where you"
        t_para "can buy LOVELY"
        t_line "MAIL."
        t_done )
};
const txt_cmd_s CeladonDeptStore4FDirectoryText[] = {
    text_start("Express Yourself"
        t_line "With Gifts!"
        t_para "4F: WISEMAN GIFTS"
        t_done )
    //db(0, 0) // filler
};
