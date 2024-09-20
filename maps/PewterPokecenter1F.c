#include "../constants.h"
#include "../util/scripting.h"
#include "PewterPokecenter1F.h"
//// EVENTS
enum {
    PEWTERPOKECENTER1F_NURSE = 2,
    PEWTERPOKECENTER1F_TEACHER,
    PEWTERPOKECENTER1F_JIGGLYPUFF,
    PEWTERPOKECENTER1F_BUG_CATCHER,
    PEWTERPOKECENTER1F_CHRIS,
};

const Script_fn_t PewterPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback PewterPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts PewterPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(PewterPokecenter1F_SceneScripts),
    .scene_scripts = PewterPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(PewterPokecenter1F_MapCallbacks),
    .callbacks = PewterPokecenter1F_MapCallbacks,
};

static const struct CoordEvent PewterPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent PewterPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData PewterPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, PEWTER_CITY, 4),
    warp_event(4, 7, PEWTER_CITY, 4),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent PewterPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PewterPokecenter1FNurseScript, -1),
    object_event(8, 6, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &PewterPokecenter1FTeacherScript, -1),
    object_event(1, 3, SPRITE_JIGGLYPUFF, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &PewterJigglypuff, -1),
    object_event(2, 3, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &PewterPokecenter1FBugCatcherScript, -1),
    object_event(7, 2, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Chris, -1),
};

const struct MapEvents PewterPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(PewterPokecenter1F_WarpEvents),
    .warp_events = PewterPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(PewterPokecenter1F_CoordEvents),
    .coord_events = PewterPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(PewterPokecenter1F_BGEvents),
    .bg_events = PewterPokecenter1F_BGEvents,

    .obj_event_count = lengthof(PewterPokecenter1F_ObjectEvents),
    .obj_events = PewterPokecenter1F_ObjectEvents,
};

//// CODE

bool PewterPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool PewterPokecenter1FTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PewterPokecenter1FTeacherText)
    SCRIPT_END
}
bool PewterJigglypuff(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(PewterJigglypuffText)
    playcry(JIGGLYPUFF)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool PewterPokecenter1FBugCatcherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PewterPokecenter1FBugCatcherText)
    SCRIPT_END
}
bool Chris(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    trade(NPC_TRADE_CHRIS)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s PewterPokecenter1FTeacherText[] = {
    text_start("…Yeah, and the"
        t_line "GYM in CINNABAR's"
        t_para "gone. I was really"
        t_line "amazed."
        t_para "…Yes? I'm on the"
        t_line "phone. Go away!"
        t_done )
};
const txt_cmd_s PewterJigglypuffText[] = {
    text_start("JIGGLYPUFF: Puu"
        t_line "pupuu."
        t_done )
};
const txt_cmd_s PewterPokecenter1FBugCatcherText[] = {
    text_start("Most #MON get"
        t_line "drowsy if they"
        t_para "hear a JIGGLYPUFF"
        t_line "singing."
        t_para "There are several"
        t_line "moves that can be"
        t_para "used only while a"
        t_line "#MON is asleep."
        t_done )
    //db(0, 0) // filler
};
