#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore4F.h"
//// EVENTS
enum {
    GOLDENRODDEPTSTORE4F_CLERK = 2,
    GOLDENRODDEPTSTORE4F_COOLTRAINER_M,
    GOLDENRODDEPTSTORE4F_BUG_CATCHER,
    GOLDENRODDEPTSTORE4F_GAMEBOY_KID,
};

const Script_fn_t GoldenrodDeptStore4F_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodDeptStore4F_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodDeptStore4F_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodDeptStore4F_SceneScripts),
    .scene_scripts = GoldenrodDeptStore4F_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodDeptStore4F_MapCallbacks),
    .callbacks = GoldenrodDeptStore4F_MapCallbacks,
};

static const struct CoordEvent GoldenrodDeptStore4F_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodDeptStore4F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &GoldenrodDeptStore4FDirectory),
    bg_event(3, 0, BGEVENT_READ, &GoldenrodDeptStore4FElevatorButton),
};

static const struct WarpEventData GoldenrodDeptStore4F_WarpEvents[] = {
    warp_event(12, 0, GOLDENROD_DEPT_STORE_5F, 1),
    warp_event(15, 0, GOLDENROD_DEPT_STORE_3F, 2),
    warp_event(2, 0, GOLDENROD_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent GoldenrodDeptStore4F_ObjectEvents[] = {
    object_event(13, 5, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore4FClerkScript, -1),
    object_event(11, 7, SPRITE_COOLTRAINER_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore4FCooltrainerMScript, -1),
    object_event(7, 2, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore4FBugCatcherScript, -1),
    object_event(5, 1, SPRITE_GAMEBOY_KID, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore4FGameboyKidScript, -1),
};

const struct MapEvents GoldenrodDeptStore4F_MapEvents = {
    .warp_event_count = lengthof(GoldenrodDeptStore4F_WarpEvents),
    .warp_events = GoldenrodDeptStore4F_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodDeptStore4F_CoordEvents),
    .coord_events = GoldenrodDeptStore4F_CoordEvents,

    .bg_event_count = lengthof(GoldenrodDeptStore4F_BGEvents),
    .bg_events = GoldenrodDeptStore4F_BGEvents,

    .obj_event_count = lengthof(GoldenrodDeptStore4F_ObjectEvents),
    .obj_events = GoldenrodDeptStore4F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore4F.h"

bool GoldenrodDeptStore4FClerkScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_GOLDENROD_4F)
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStore4FCooltrainerMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore4FCooltrainerMText)
    SCRIPT_END
}
bool GoldenrodDeptStore4FBugCatcherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore4FBugCatcherText)
    SCRIPT_END
}
bool GoldenrodDeptStore4FGameboyKidScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(GoldenrodDeptStore4FGameboyKidText)
    waitbutton
    closetext
    turnobject(GOLDENRODDEPTSTORE4F_GAMEBOY_KID, DOWN)
    s_end
    SCRIPT_END
}
bool GoldenrodDeptStore4FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodDeptStore4FDirectoryText)
    SCRIPT_END
}
bool GoldenrodDeptStore4FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s GoldenrodDeptStore4FCooltrainerMText[] = {
    text_start("Hey. I love strong"
        t_line "#MON."
        t_para "I feed them PRO-"
        t_line "TEIN to crank up"
        t_cont "their ATTACK."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore4FBugCatcherText[] = {
    text_start("IRON adds to your"
        t_line "#MON's DEFENSE."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore4FGameboyKidText[] = {
    text_start("Some #MON"
        t_line "evolve only by"
        t_para "being traded via a"
        t_line "Game Link cable."
        t_para "I know of four:"
        t_line "MACHOKE, KADABRA,"
        t_para "HAUNTER and, um,"
        t_line "GRAVELER."
        t_para "I heard there are"
        t_line "others too."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore4FDirectoryText[] = {
    text_start("Let Us Pump Up"
        t_line "Your #MON!"
        t_para "4F MEDICINE BOX"
        t_done )
    //db(0, 0) // filler
};
