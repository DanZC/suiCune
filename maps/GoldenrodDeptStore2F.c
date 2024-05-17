#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore2F.h"
//// EVENTS
enum {
    GOLDENRODDEPTSTORE2F_CLERK1 = 2,
    GOLDENRODDEPTSTORE2F_CLERK2,
    GOLDENRODDEPTSTORE2F_YOUNGSTER,
    GOLDENRODDEPTSTORE2F_COOLTRAINER_F,
    GOLDENRODDEPTSTORE2F_GENTLEMAN,
};

const Script_fn_t GoldenrodDeptStore2F_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodDeptStore2F_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodDeptStore2F_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodDeptStore2F_SceneScripts),
    .scene_scripts = GoldenrodDeptStore2F_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodDeptStore2F_MapCallbacks),
    .callbacks = GoldenrodDeptStore2F_MapCallbacks,
};

static const struct CoordEvent GoldenrodDeptStore2F_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodDeptStore2F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &GoldenrodDeptStore2FDirectory),
    bg_event(3, 0, BGEVENT_READ, &GoldenrodDeptStore2FElevatorButton),
};

static const struct WarpEventData GoldenrodDeptStore2F_WarpEvents[] = {
    warp_event(12, 0, GOLDENROD_DEPT_STORE_3F, 1),
    warp_event(15, 0, GOLDENROD_DEPT_STORE_1F, 3),
    warp_event(2, 0, GOLDENROD_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent GoldenrodDeptStore2F_ObjectEvents[] = {
    object_event(13, 5, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore2FClerk1Script, -1),
    object_event(13, 6, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore2FClerk2Script, -1),
    object_event(9, 6, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore2FYoungsterScript, -1),
    object_event(6, 2, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore2FCooltrainerFScript, -1),
    object_event(2, 6, SPRITE_GENTLEMAN, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore2FGentlemanScript, -1),
};

const struct MapEvents GoldenrodDeptStore2F_MapEvents = {
    .warp_event_count = lengthof(GoldenrodDeptStore2F_WarpEvents),
    .warp_events = GoldenrodDeptStore2F_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodDeptStore2F_CoordEvents),
    .coord_events = GoldenrodDeptStore2F_CoordEvents,

    .bg_event_count = lengthof(GoldenrodDeptStore2F_BGEvents),
    .bg_events = GoldenrodDeptStore2F_BGEvents,

    .obj_event_count = lengthof(GoldenrodDeptStore2F_ObjectEvents),
    .obj_events = GoldenrodDeptStore2F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore2F.h"

bool GoldenrodDeptStore2FClerk1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_GOLDENROD_2F_1)
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStore2FClerk2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_GOLDENROD_2F_2)
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStore2FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore2FYoungsterText)
    SCRIPT_END
}
bool GoldenrodDeptStore2FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore2FCooltrainerFText)
    SCRIPT_END
}
bool GoldenrodDeptStore2FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore2FGentlemanText)
    SCRIPT_END
}
bool GoldenrodDeptStore2FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodDeptStore2FDirectoryText)
    SCRIPT_END
}
bool GoldenrodDeptStore2FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s GoldenrodDeptStore2FUnusedText1[] = {
    text_start("We intend to sell"
        t_line "items for #MON"
        t_cont "to hold."
        t_para "This is a free"
        t_line "gift. Have a #-"
        t_cont "MON hold it."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore2FUnusedText2[] = {
    text_start("By giving #MON"
        t_line "items to hold, I"
        t_para "bet trainers will"
        t_line "develop new battle"
        t_cont "techniques."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore2FYoungsterText[] = {
    text_start("#GEAR can store"
        t_line "up to ten phone"
        t_cont "numbers."
        t_para "It's hard to de-"
        t_line "cide which numbers"
        t_cont "to keep."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore2FCooltrainerFText[] = {
    text_start("I got my ABRA at"
        t_line "the GAME CORNER."
        t_para "Now it's my best"
        t_line "partner."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore2FGentlemanText[] = {
    text_start("This DEPT.STORE"
        t_line "makes me realize"
        t_para "that GOLDENROD is"
        t_line "a big city."
        t_para "The selection here"
        t_line "is unmatched any-"
        t_cont "where else."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore2FDirectoryText[] = {
    text_start("Your Travel"
        t_line "Companion"
        t_para "2F TRAINER'S"
        t_line "   MARKET"
        t_done )
    //db(0, 0) // filler
};
