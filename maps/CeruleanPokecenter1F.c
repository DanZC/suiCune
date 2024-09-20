#include "../constants.h"
#include "../util/scripting.h"
#include "CeruleanPokecenter1F.h"
//// EVENTS
enum {
    CERULEANPOKECENTER1F_NURSE = 2,
    CERULEANPOKECENTER1F_SUPER_NERD,
    CERULEANPOKECENTER1F_GYM_GUIDE,
};

const Script_fn_t CeruleanPokecenter1F_SceneScripts[] = {
    0,
};

const struct MapCallback CeruleanPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts CeruleanPokecenter1F_MapScripts = {
    .scene_script_count = 0, // lengthof(CeruleanPokecenter1F_SceneScripts),
    .scene_scripts = CeruleanPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(CeruleanPokecenter1F_MapCallbacks),
    .callbacks = CeruleanPokecenter1F_MapCallbacks,
};

static const struct CoordEvent CeruleanPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent CeruleanPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData CeruleanPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, CERULEAN_CITY, 4),
    warp_event(4, 7, CERULEAN_CITY, 4),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent CeruleanPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeruleanPokecenter1FNurseScript, -1),
    object_event(8, 4, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeruleanPokecenter1FSuperNerdScript, -1),
    object_event(1, 5, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeruleanPokecenter1FGymGuideScript, -1),
};

const struct MapEvents CeruleanPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(CeruleanPokecenter1F_WarpEvents),
    .warp_events = CeruleanPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(CeruleanPokecenter1F_CoordEvents),
    .coord_events = CeruleanPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(CeruleanPokecenter1F_BGEvents),
    .bg_events = CeruleanPokecenter1F_BGEvents,

    .obj_event_count = lengthof(CeruleanPokecenter1F_ObjectEvents),
    .obj_events = CeruleanPokecenter1F_ObjectEvents,
};

//// CODE

bool CeruleanPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool CeruleanPokecenter1FSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse)
    iftrue(mobile)
    jumptextfaceplayer(CeruleanPokecenter1FSuperNerdText)
mobile:
    jumptextfaceplayer(CeruleanPokecenter1FSuperNerdText_Mobile)
    SCRIPT_END
}
bool CeruleanPokecenter1FGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeruleanPokecenter1FGymGuideText)
    SCRIPT_END
}
const txt_cmd_s CeruleanPokecenter1FSuperNerdText[] = {
    text_start("For battles, I'd"
        t_line "much rather use"
        t_para "#MON I've been"
        t_line "raising, even if"
        t_para "they're weaker"
        t_line "than some newly"
        t_cont "caught #MON."
        t_done )
};
const txt_cmd_s CeruleanPokecenter1FSuperNerdText_Mobile[] = {
    text_start("Do you battle by"
        t_line "mobile phone?"
        t_para "If time runs out"
        t_line "during a battle,"
        t_para "waiting to see who"
        t_line "won is really"
        t_cont "nerve wracking."
        t_done )
};
const txt_cmd_s CeruleanPokecenter1FGymGuideText[] = {
    text_start("The MAGNET TRAIN"
        t_line "travels at over"
        t_para "340 mph. It goes"
        t_line "between KANTO and"
        t_para "JOHTO in almost no"
        t_line "time at all."
        t_para "It really makes"
        t_line "JOHTO accessible."
        t_done )
    //db(0, 0) // filler
};
