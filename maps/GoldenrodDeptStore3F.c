#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore3F.h"
//// EVENTS
enum {
    GOLDENRODDEPTSTORE3F_CLERK = 2,
    GOLDENRODDEPTSTORE3F_SUPER_NERD,
    GOLDENRODDEPTSTORE3F_ROCKER,
};

const Script_fn_t GoldenrodDeptStore3F_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodDeptStore3F_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodDeptStore3F_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodDeptStore3F_SceneScripts),
    .scene_scripts = GoldenrodDeptStore3F_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodDeptStore3F_MapCallbacks),
    .callbacks = GoldenrodDeptStore3F_MapCallbacks,
};

static const struct CoordEvent GoldenrodDeptStore3F_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodDeptStore3F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &GoldenrodDeptStore3FDirectory),
    bg_event(3, 0, BGEVENT_READ, &GoldenrodDeptStore3FElevatorButton),
};

static const struct WarpEventData GoldenrodDeptStore3F_WarpEvents[] = {
    warp_event(12, 0, GOLDENROD_DEPT_STORE_2F, 1),
    warp_event(15, 0, GOLDENROD_DEPT_STORE_4F, 2),
    warp_event(2, 0, GOLDENROD_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent GoldenrodDeptStore3F_ObjectEvents[] = {
    object_event(6, 1, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore3FClerkScript, -1),
    object_event(12, 5, SPRITE_SUPER_NERD, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore3FSuperNerdScript, -1),
    object_event(2, 5, SPRITE_ROCKER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore3FRockerScript, -1),
};

const struct MapEvents GoldenrodDeptStore3F_MapEvents = {
    .warp_event_count = lengthof(GoldenrodDeptStore3F_WarpEvents),
    .warp_events = GoldenrodDeptStore3F_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodDeptStore3F_CoordEvents),
    .coord_events = GoldenrodDeptStore3F_CoordEvents,

    .bg_event_count = lengthof(GoldenrodDeptStore3F_BGEvents),
    .bg_events = GoldenrodDeptStore3F_BGEvents,

    .obj_event_count = lengthof(GoldenrodDeptStore3F_ObjectEvents),
    .obj_events = GoldenrodDeptStore3F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore3F.h"

bool GoldenrodDeptStore3FClerkScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_GOLDENROD_3F)
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStore3FSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore3FSuperNerdText)
    SCRIPT_END
}
bool GoldenrodDeptStore3FRockerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore3FRockerText)
    SCRIPT_END
}
bool GoldenrodDeptStore3FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodDeptStore3FDirectoryText)
    SCRIPT_END
}
bool GoldenrodDeptStore3FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s GoldenrodDeptStore3FSuperNerdText[] = {
    text_start("I, I, I'm really"
        t_line "impatient!"
        t_para "I use X SPEED in"
        t_line "battle to speed up"
        t_cont "my #MON."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore3FRockerText[] = {
    text_start("Hey! When you bat-"
        t_line "tle, do you use X"
        t_cont "SPECIAL?"
        t_para "It's awesome. It"
        t_line "really jacks up"
        t_cont "SPECIAL ATTACK!"
        t_done )
};
const txt_cmd_s GoldenrodDeptStore3FDirectoryText[] = {
    text_start("For Victory"
        t_line "Seekers"
        t_para "3F BATTLE"
        t_line "   COLLECTION"
        t_done )
    //db(0, 0) // filler
};
