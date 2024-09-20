#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonDeptStore3F.h"
//// EVENTS
enum {
    CELADONDEPTSTORE3F_CLERK = 2,
    CELADONDEPTSTORE3F_YOUNGSTER,
    CELADONDEPTSTORE3F_GAMEBOY_KID1,
    CELADONDEPTSTORE3F_GAMEBOY_KID2,
    CELADONDEPTSTORE3F_SUPER_NERD,
};

const Script_fn_t CeladonDeptStore3F_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonDeptStore3F_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonDeptStore3F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonDeptStore3F_SceneScripts),
    .scene_scripts = CeladonDeptStore3F_SceneScripts,

    .callback_count = 0, // lengthof(CeladonDeptStore3F_MapCallbacks),
    .callbacks = CeladonDeptStore3F_MapCallbacks,
};

static const struct CoordEvent CeladonDeptStore3F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonDeptStore3F_BGEvents[] = {
    bg_event(14, 0, BGEVENT_READ, &CeladonDeptStore3FDirectory),
    bg_event(3, 0, BGEVENT_READ, &CeladonDeptStore3FElevatorButton),
};

static const struct WarpEventData CeladonDeptStore3F_WarpEvents[] = {
    warp_event(12, 0, CELADON_DEPT_STORE_2F, 1),
    warp_event(15, 0, CELADON_DEPT_STORE_4F, 2),
    warp_event(2, 0, CELADON_DEPT_STORE_ELEVATOR, 1),
};

static const struct ObjEvent CeladonDeptStore3F_ObjectEvents[] = {
    object_event(7, 1, SPRITE_CLERK, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore3FClerkScript, -1),
    object_event(6, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore3FYoungsterScript, -1),
    object_event(9, 1, SPRITE_GAMEBOY_KID, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore3FGameboyKid1Script, -1),
    object_event(10, 1, SPRITE_GAMEBOY_KID, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore3FGameboyKid2Script, -1),
    object_event(13, 4, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CeladonDeptStore3FSuperNerdScript, -1),
};

const struct MapEvents CeladonDeptStore3F_MapEvents = {
    .warp_event_count = lengthof(CeladonDeptStore3F_WarpEvents),
    .warp_events = CeladonDeptStore3F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonDeptStore3F_CoordEvents),
    .coord_events = CeladonDeptStore3F_CoordEvents,

    .bg_event_count = lengthof(CeladonDeptStore3F_BGEvents),
    .bg_events = CeladonDeptStore3F_BGEvents,

    .obj_event_count = lengthof(CeladonDeptStore3F_ObjectEvents),
    .obj_events = CeladonDeptStore3F_ObjectEvents,
};

//// CODE

bool CeladonDeptStore3FClerkScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    pokemart(MARTTYPE_STANDARD, MART_CELADON_3F)
    closetext
    s_end
    SCRIPT_END
}
bool CeladonDeptStore3FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore3FYoungsterText)
    SCRIPT_END
}
bool CeladonDeptStore3FGameboyKid1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeladonDeptStore3FGameboyKid1Text)
    waitbutton
    closetext
    turnobject(CELADONDEPTSTORE3F_GAMEBOY_KID1, DOWN)
    s_end
    SCRIPT_END
}
bool CeladonDeptStore3FGameboyKid2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(CeladonDeptStore3FGameboyKid2Text)
    waitbutton
    closetext
    turnobject(CELADONDEPTSTORE3F_GAMEBOY_KID2, DOWN)
    s_end
    SCRIPT_END
}
bool CeladonDeptStore3FSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeladonDeptStore3FSuperNerdText)
    SCRIPT_END
}
bool CeladonDeptStore3FElevatorButton(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(ElevatorButtonScript)
    SCRIPT_END
}
bool CeladonDeptStore3FDirectory(script_s* s) {
    SCRIPT_BEGIN
    jumptext(CeladonDeptStore3FDirectoryText)
    SCRIPT_END
}
const txt_cmd_s CeladonDeptStore3FYoungsterText[] = {
    text_start("I can't decide"
        t_line "which #MON I"
        t_para "should use this TM"
        t_line "on…"
        t_done )
};
const txt_cmd_s CeladonDeptStore3FGameboyKid1Text[] = {
    text_start("Uh-oh! I traded my"
        t_line "#MON without"
        t_para "removing the UP-"
        t_line "GRADE from it."
        t_done )
};
const txt_cmd_s CeladonDeptStore3FGameboyKid2Text[] = {
    text_start("Yeah! I'm finally"
        t_line "getting a PORYGON!"
        t_para "I'm no good at the"
        t_line "slots, so I could"
        t_para "never get enough"
        t_line "coins…"
        t_para "…Huh?"
        t_para "The traded PORYGON"
        t_line "turned into a dif-"
        t_cont "ferent #MON!"
        t_done )
};
const txt_cmd_s CeladonDeptStore3FSuperNerdText[] = {
    text_start("The TM SHOP sells"
        t_line "some rare moves."
        t_done )
};
const txt_cmd_s CeladonDeptStore3FDirectoryText[] = {
    text_start("3F: TM SHOP"
        t_para "Make Your #MON"
        t_line "Stronger!"
        t_done )
    //db(0, 0) // filler
};
