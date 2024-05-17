#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore1F.h"
//// EVENTS
enum {
    GOLDENRODDEPTSTORE1F_RECEPTIONIST = 2,
    GOLDENRODDEPTSTORE1F_POKEFAN_F,
    GOLDENRODDEPTSTORE1F_BUG_CATCHER,
    GOLDENRODDEPTSTORE1F_GENTLEMAN,
};

const Script_fn_t GoldenrodDeptStore1F_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodDeptStore1F_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodDeptStore1F_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodDeptStore1F_SceneScripts),
    .scene_scripts = GoldenrodDeptStore1F_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodDeptStore1F_MapCallbacks),
    .callbacks = GoldenrodDeptStore1F_MapCallbacks,
};

static const struct CoordEvent GoldenrodDeptStore1F_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodDeptStore1F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &GoldenrodDeptStore1FDirectory),
    bg_event(3, 0, BGEVENT_READ, &GoldenrodDeptStore1FElevatorButton),
};

static const struct WarpEventData GoldenrodDeptStore1F_WarpEvents[] = {
    warp_event(7, 7, GOLDENROD_CITY, 9),
    warp_event(8, 7, GOLDENROD_CITY, 9),
    warp_event(15, 0, GOLDENROD_DEPT_STORE_2F, 2),
    warp_event(2, 0, GOLDENROD_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent GoldenrodDeptStore1F_ObjectEvents[] = {
    object_event(10, 1, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore1FReceptionistScript, -1),
    object_event(5, 4, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore1FPokefanFScript, -1),
    object_event(5, 5, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore1FBugCatcherScript, -1),
    object_event(11, 5, SPRITE_GENTLEMAN, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodDeptStore1FGentlemanScript, -1),
};

const struct MapEvents GoldenrodDeptStore1F_MapEvents = {
    .warp_event_count = lengthof(GoldenrodDeptStore1F_WarpEvents),
    .warp_events = GoldenrodDeptStore1F_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodDeptStore1F_CoordEvents),
    .coord_events = GoldenrodDeptStore1F_CoordEvents,

    .bg_event_count = lengthof(GoldenrodDeptStore1F_BGEvents),
    .bg_events = GoldenrodDeptStore1F_BGEvents,

    .obj_event_count = lengthof(GoldenrodDeptStore1F_ObjectEvents),
    .obj_events = GoldenrodDeptStore1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStore1F.h"

bool GoldenrodDeptStore1FReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore1FReceptionistText)
    SCRIPT_END
}
bool GoldenrodDeptStore1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore1FGentlemanText)
    SCRIPT_END
}
bool GoldenrodDeptStore1FPokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore1FPokefanFText)
    SCRIPT_END
}
bool GoldenrodDeptStore1FBugCatcherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodDeptStore1FBugCatcherText)
    SCRIPT_END
}
bool GoldenrodDeptStore1FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(GoldenrodDeptStore1FDirectoryText)
    SCRIPT_END
}
bool GoldenrodDeptStore1FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
const txt_cmd_s GoldenrodDeptStore1FReceptionistText[] = {
    text_start("Welcome to GOLDEN-"
        t_line "ROD DEPT.STORE."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore1FGentlemanText[] = {
    text_start("The DEPT.STORE"
        t_line "has a decent se-"
        t_cont "lection."
        t_para "But some items"
        t_line "are only available"
        t_para "as GAME CORNER"
        t_line "prizes."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore1FPokefanFText[] = {
    text_start("I'm raring to shop"
        t_line "again today!"
        t_done )
};
const txt_cmd_s GoldenrodDeptStore1FBugCatcherText[] = {
    text_start("Mom's good at"
        t_line "bargain hunting."
        t_para "She always buys"
        t_line "stuff at lower"
        t_cont "prices."
        t_done )
};
const txt_cmd_s GoldenrodDeptStore1FDirectoryText[] = {
    text_start("1F SERVICE COUNTER"
        t_para "2F TRAINER'S"
        t_line "   MARKET"
        t_para "3F BATTLE"
        t_line "   COLLECTION"
        t_para "4F MEDICINE BOX"
        t_para "5F TM CORNER"
        t_para "6F TRANQUIL SQUARE"
        t_para "ROOFTOP LOOKOUT"
        t_done )
    //db(0, 0) // filler
};
