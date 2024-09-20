#include "../constants.h"
#include "../util/scripting.h"
#include "LavenderPokecenter1F.h"
//// EVENTS
enum {
    LAVENDERPOKECENTER1F_NURSE = 2,
    LAVENDERPOKECENTER1F_GENTLEMAN,
    LAVENDERPOKECENTER1F_TEACHER,
    LAVENDERPOKECENTER1F_YOUNGSTER,
};

const Script_fn_t LavenderPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback LavenderPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts LavenderPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(LavenderPokecenter1F_SceneScripts),
    .scene_scripts = LavenderPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(LavenderPokecenter1F_MapCallbacks),
    .callbacks = LavenderPokecenter1F_MapCallbacks,
};

static const struct CoordEvent LavenderPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent LavenderPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData LavenderPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, LAVENDER_TOWN, 1),
    warp_event(4, 7, LAVENDER_TOWN, 1),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent LavenderPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LavenderPokecenter1FNurseScript, -1),
    object_event(7, 6, SPRITE_GENTLEMAN, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LavenderPokecenter1FGentlemanScript, -1),
    object_event(5, 3, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &LavenderPokecenter1FTeacherScript, -1),
    object_event(1, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &LavenderPokecenter1FYoungsterScript, -1),
};

const struct MapEvents LavenderPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(LavenderPokecenter1F_WarpEvents),
    .warp_events = LavenderPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(LavenderPokecenter1F_CoordEvents),
    .coord_events = LavenderPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(LavenderPokecenter1F_BGEvents),
    .bg_events = LavenderPokecenter1F_BGEvents,

    .obj_event_count = lengthof(LavenderPokecenter1F_ObjectEvents),
    .obj_events = LavenderPokecenter1F_ObjectEvents,
};

//// CODE

bool LavenderPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool LavenderPokecenter1FGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavenderPokecenter1FGentlemanText)
    SCRIPT_END
}
bool LavenderPokecenter1FTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavenderPokecenter1FTeacherText)
    SCRIPT_END
}
bool LavenderPokecenter1FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(LavenderPokecenter1FYoungsterText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(LavenderPokecenter1FYoungsterText_ReturnedMachinePart)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s LavenderPokecenter1FGentlemanText[] = {
    text_start("To the north of"
        t_line "LAVENDER is ROCK"
        t_para "TUNNEL. Go through"
        t_line "it to get to the"
        t_cont "POWER PLANT."
        t_done )
};
const txt_cmd_s LavenderPokecenter1FTeacherText[] = {
    text_start("There's a radio"
        t_line "program that plays"
        t_cont "# FLUTE music."
        t_para "Oh? Ah, your radio"
        t_line "needs an EXPN CARD"
        t_cont "to tune into it."
        t_done )
};
const txt_cmd_s LavenderPokecenter1FYoungsterText[] = {
    text_start("If the POWER PLANT"
        t_line "isn't running, the"
        t_para "MAGNET TRAIN won't"
        t_line "run either…"
        t_para "It also means the"
        t_line "RADIO STATION"
        t_cont "can't broadcast…"
        t_done )
};
const txt_cmd_s LavenderPokecenter1FYoungsterText_ReturnedMachinePart[] = {
    text_start("The DIRECTOR of"
        t_line "the RADIO STATION"
        t_cont "sure was happy."
        t_para "He said they're"
        t_line "back on the air"
        t_para "because the POWER"
        t_line "PLANT is running"
        t_cont "smoothly again."
        t_done )
    //db(0, 0) // filler
};
