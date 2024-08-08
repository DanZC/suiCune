#include "../constants.h"
#include "../util/scripting.h"
#include "LavenderTown.h"
//// EVENTS
enum {
    LAVENDERTOWN_POKEFAN_M = 2,
    LAVENDERTOWN_TEACHER,
    LAVENDERTOWN_GRAMPS,
    LAVENDERTOWN_YOUNGSTER,
};

const Script_fn_t LavenderTown_SceneScripts[] = {
    0,
};

const struct MapCallback LavenderTown_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, LavenderTown_MapScripts_FlyPoint),
};

const struct MapScripts LavenderTown_MapScripts = {
    .scene_script_count = 0, // lengthof(LavenderTown_SceneScripts),
    .scene_scripts = LavenderTown_SceneScripts,

    .callback_count = lengthof(LavenderTown_MapCallbacks),
    .callbacks = LavenderTown_MapCallbacks,
};

static const struct CoordEvent LavenderTown_CoordEvents[] = {
    0,
};

static const struct BGEvent LavenderTown_BGEvents[] = {
    bg_event(11, 3, BGEVENT_READ, &LavenderTownSign),
    bg_event(15, 7, BGEVENT_READ, &KantoRadioStationSign),
    bg_event(3, 9, BGEVENT_READ, &VolunteerPokemonHouseSign),
    bg_event(15, 13, BGEVENT_READ, &SoulHouseSign),
    bg_event(6, 5, BGEVENT_READ, &LavenderPokecenterSignText),
    bg_event(2, 5, BGEVENT_READ, &LavenderMartSignText),
};

static const struct WarpEventData LavenderTown_WarpEvents[] = {
    warp_event(5, 5, LAVENDER_POKECENTER_1F, 1),
    warp_event(5, 9, MR_FUJIS_HOUSE, 1),
    warp_event(3, 13, LAVENDER_SPEECH_HOUSE, 1),
    warp_event(7, 13, LAVENDER_NAME_RATER, 1),
    warp_event(1, 5, LAVENDER_MART, 2),
    warp_event(13, 11, SOUL_HOUSE, 1),
    warp_event(14, 5, LAV_RADIO_TOWER_1F, 1),
};

static const struct ObjEvent LavenderTown_ObjectEvents[] = {
    object_event(12, 7, SPRITE_POKEFAN_M, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &LavenderTownPokefanMScript, -1),
    object_event(2, 15, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &LavenderTownTeacherScript, -1),
    object_event(14, 12, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &LavenderTownGrampsScript, -1),
    object_event(6, 11, SPRITE_YOUNGSTER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 1, &LavenderTownYoungsterScript, -1),
};

const struct MapEvents LavenderTown_MapEvents = {
    .warp_event_count = lengthof(LavenderTown_WarpEvents),
    .warp_events = LavenderTown_WarpEvents,

    .coord_event_count = 0, // lengthof(LavenderTown_CoordEvents),
    .coord_events = LavenderTown_CoordEvents,

    .bg_event_count = lengthof(LavenderTown_BGEvents),
    .bg_events = LavenderTown_BGEvents,

    .obj_event_count = lengthof(LavenderTown_ObjectEvents),
    .obj_events = LavenderTown_ObjectEvents,
};

//// CODE

bool LavenderTown_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_LAVENDER)
    s_endcallback
    SCRIPT_END
}
bool LavenderTownPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavenderTownPokefanMText)
    SCRIPT_END
}
bool LavenderTownTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavenderTownTeacherText)
    SCRIPT_END
}
bool LavenderTownGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavenderTownGrampsText)
    SCRIPT_END
}
bool LavenderTownYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavenderTownYoungsterText)
    SCRIPT_END
}
bool LavenderTownSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(LavenderTownSignText)
    SCRIPT_END
}
bool KantoRadioStationSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(KantoRadioStationSignText)
    SCRIPT_END
}
bool VolunteerPokemonHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(VolunteerPokemonHouseSignText)
    SCRIPT_END
}
bool SoulHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(SoulHouseSignText)
    SCRIPT_END
}
bool LavenderPokecenterSignText(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterSignScript)
    SCRIPT_END
}
bool LavenderMartSignText(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MartSignScript)
    SCRIPT_END
}
const txt_cmd_s LavenderTownPokefanMText[] = {
    text_start("That's quite some"
        t_line "building, eh?"
        t_para "It's KANTO's RADIO"
        t_line "TOWER."
        t_done )
};
const txt_cmd_s LavenderTownTeacherText[] = {
    text_start("KANTO has many"
        t_line "good radio shows."
        t_done )
};
const txt_cmd_s LavenderTownGrampsText[] = {
    text_start("People come from"
        t_line "all over to pay"
        t_para "their respects to"
        t_line "the departed souls"
        t_cont "of #MON."
        t_done )
};
const txt_cmd_s LavenderTownYoungsterText[] = {
    text_start("You need a #"
        t_line "FLUTE to wake"
        t_cont "sleeping #MON."
        t_para "Every trainer has"
        t_line "to know that!"
        t_done )
};
const txt_cmd_s LavenderTownSignText[] = {
    text_start("LAVENDER TOWN"
        t_para "The Noble Purple"
        t_line "Town"
        t_done )
};
const txt_cmd_s KantoRadioStationSignText[] = {
    text_start("KANTO RADIO"
        t_line "STATION"
        t_para "Your Favorite"
        t_line "Programs On-Air"
        t_cont "Around the Clock!"
        t_done )
};
const txt_cmd_s VolunteerPokemonHouseSignText[] = {
    text_start("LAVENDER VOLUNTEER"
        t_line "#MON HOUSE"
        t_done )
};
const txt_cmd_s SoulHouseSignText[] = {
    text_start("SOUL HOUSE"
        t_para "May the Souls of"
        t_line "#MON Rest Easy"
        t_done )
    //db(0, 0) // filler
};
