#include "../constants.h"
#include "../util/scripting.h"
#include "OlivinePokecenter1F.h"
//// EVENTS
enum {
    OLIVINEPOKECENTER1F_NURSE = 2,
    OLIVINEPOKECENTER1F_FISHING_GURU,
    OLIVINEPOKECENTER1F_FISHER,
    OLIVINEPOKECENTER1F_TEACHER,
};

const Script_fn_t OlivinePokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback OlivinePokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivinePokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(OlivinePokecenter1F_SceneScripts),
    .scene_scripts = OlivinePokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(OlivinePokecenter1F_MapCallbacks),
    .callbacks = OlivinePokecenter1F_MapCallbacks,
};

static const struct CoordEvent OlivinePokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent OlivinePokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData OlivinePokecenter1F_WarpEvents[] = {
    warp_event(3, 7, OLIVINE_CITY, 1),
    warp_event(4, 7, OLIVINE_CITY, 1),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent OlivinePokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePokecenter1FNurseScript, -1),
    object_event(8, 4, SPRITE_FISHING_GURU, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePokecenter1FFishingGuruScript, -1),
    object_event(2, 3, SPRITE_FISHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &OlivinePokecenter1FFisherScript, -1),
    object_event(7, 1, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePokecenter1FTeacherScript, -1),
};

const struct MapEvents OlivinePokecenter1F_MapEvents = {
    .warp_event_count = lengthof(OlivinePokecenter1F_WarpEvents),
    .warp_events = OlivinePokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(OlivinePokecenter1F_CoordEvents),
    .coord_events = OlivinePokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(OlivinePokecenter1F_BGEvents),
    .bg_events = OlivinePokecenter1F_BGEvents,

    .obj_event_count = lengthof(OlivinePokecenter1F_ObjectEvents),
    .obj_events = OlivinePokecenter1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivinePokecenter1F.h"

bool OlivinePokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool OlivinePokecenter1FFishingGuruScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(HappinessCheckScript)
    SCRIPT_END
}
bool OlivinePokecenter1FFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivinePokecenter1FFisherText)
    SCRIPT_END
}
bool OlivinePokecenter1FTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivinePokecenter1FTeacherText)
    SCRIPT_END
}
const txt_cmd_s OlivinePokecenter1FFisherText[] = {
    text_start("The SAILOR in the"
        t_line "OLIVINE CAFE next"
        t_para "door is really"
        t_line "generous."
        t_para "He taught my"
        t_line "#MON STRENGTH."
        t_para "Now it can move"
        t_line "big boulders."
        t_done )
};
const txt_cmd_s OlivinePokecenter1FTeacherText[] = {
    text_start("There's a person"
        t_line "in CIANWOOD CITY"
        t_cont "across the sea."
        t_para "I heard him brag-"
        t_line "ging about his"
        t_cont "rare #MON."
        t_done )
    //db(0, 0) // filler
};
