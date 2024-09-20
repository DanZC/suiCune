#include "../constants.h"
#include "../util/scripting.h"
#include "SaffronPokecenter1F.h"
//// EVENTS
enum {
    SAFFRONPOKECENTER1F_NURSE = 2,
    SAFFRONPOKECENTER1F_TEACHER,
    SAFFRONPOKECENTER1F_FISHER,
    SAFFRONPOKECENTER1F_YOUNGSTER,
};

const Script_fn_t SaffronPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback SaffronPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts SaffronPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(SaffronPokecenter1F_SceneScripts),
    .scene_scripts = SaffronPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(SaffronPokecenter1F_MapCallbacks),
    .callbacks = SaffronPokecenter1F_MapCallbacks,
};

static const struct CoordEvent SaffronPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent SaffronPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData SaffronPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, SAFFRON_CITY, 4),
    warp_event(4, 7, SAFFRON_CITY, 4),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent SaffronPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SaffronPokecenter1FNurseScript, -1),
    object_event(7, 2, SPRITE_TEACHER, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &SaffronPokecenter1FTeacherScript, -1),
    object_event(8, 6, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &SaffronPokecenter1FFisherScript, -1),
    object_event(1, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &SaffronPokecenter1FYoungsterScript, -1),
};

const struct MapEvents SaffronPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(SaffronPokecenter1F_WarpEvents),
    .warp_events = SaffronPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(SaffronPokecenter1F_CoordEvents),
    .coord_events = SaffronPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(SaffronPokecenter1F_BGEvents),
    .bg_events = SaffronPokecenter1F_BGEvents,

    .obj_event_count = lengthof(SaffronPokecenter1F_ObjectEvents),
    .obj_events = SaffronPokecenter1F_ObjectEvents,
};

//// CODE

bool SaffronPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool SaffronPokecenter1FTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse)
    iftrue(mobile)
    jumptextfaceplayer(SaffronPokecenter1FTeacherText)
mobile:
    jumptextfaceplayer(SaffronPokecenter1FTeacherMobileText)
    SCRIPT_END
}
bool SaffronPokecenter1FFisherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(SolvedKantoPowerCrisis)
    writetext(SaffronPokecenter1FFisherText)
    waitbutton
    closetext
    s_end
SolvedKantoPowerCrisis:
    writetext(SaffronPokecenter1FFisherReturnedMachinePartText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SaffronPokecenter1FYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SaffronPokecenter1FYoungsterText)
    SCRIPT_END
}
const txt_cmd_s SaffronPokecenter1FTeacherText[] = {
    text_start("What are JOHTO's"
        t_line "#MON CENTERS"
        t_cont "like?"
        t_para "…Oh, I see. So"
        t_line "they're not much"
        t_para "different from the"
        t_line "ones in KANTO."
        t_para "I can go to JOHTO"
        t_line "without worrying,"
        t_cont "then!"
        t_done )
};
const txt_cmd_s SaffronPokecenter1FTeacherMobileText[] = {
    text_start("What are JOHTO's"
        t_line "#MON CENTERS"
        t_cont "like?"
        t_para "…Oh, I see."
        t_line "So they let you"
        t_para "link with people"
        t_line "far away?"
        t_para "Then I'll get my"
        t_line "friend in JOHTO to"
        t_para "catch a MARILL and"
        t_line "trade it to me!"
        t_done )
};
const txt_cmd_s SaffronPokecenter1FFisherText[] = {
    text_start("I just happened to"
        t_line "come through ROCK"
        t_para "TUNNEL. There was"
        t_line "some commotion at"
        t_cont "the POWER PLANT."
        t_done )
};
const txt_cmd_s SaffronPokecenter1FFisherReturnedMachinePartText[] = {
    text_start("Caves collapse"
        t_line "easily."
        t_para "Several caves have"
        t_line "disappeared in the"
        t_para "past few years,"
        t_line "like the one out-"
        t_cont "side CERULEAN."
        t_para "As a pro HIKER,"
        t_line "that's common"
        t_cont "knowledge."
        t_done )
};
const txt_cmd_s SaffronPokecenter1FYoungsterText[] = {
    text_start("SILPH CO.'s HEAD"
        t_line "OFFICE and the"
        t_para "MAGNET TRAIN STA-"
        t_line "TION--they're the"
        t_para "places to see in"
        t_line "SAFFRON."
        t_done )
    //db(0, 0) // filler
};
