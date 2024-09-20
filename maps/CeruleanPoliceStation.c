#include "../constants.h"
#include "../util/scripting.h"
#include "CeruleanPoliceStation.h"
//// EVENTS
enum {
    CERULEANPOLICESTATION_FISHING_GURU = 2,
    CERULEANPOLICESTATION_POKEFAN_F,
    CERULEANPOLICESTATION_DIGLETT,
};

const Script_fn_t CeruleanPoliceStation_SceneScripts[] = {
    0,
};

const struct MapCallback CeruleanPoliceStation_MapCallbacks[] = {
    0,
};

const struct MapScripts CeruleanPoliceStation_MapScripts = {
    .scene_script_count = 0, // lengthof(CeruleanPoliceStation_SceneScripts),
    .scene_scripts = CeruleanPoliceStation_SceneScripts,

    .callback_count = 0, // lengthof(CeruleanPoliceStation_MapCallbacks),
    .callbacks = CeruleanPoliceStation_MapCallbacks,
};

static const struct CoordEvent CeruleanPoliceStation_CoordEvents[] = {
    0,
};

static const struct BGEvent CeruleanPoliceStation_BGEvents[] = {
    0,
};

static const struct WarpEventData CeruleanPoliceStation_WarpEvents[] = {
    warp_event(2, 7, CERULEAN_CITY, 2),
    warp_event(3, 7, CERULEAN_CITY, 2),
};

static const struct ObjEvent CeruleanPoliceStation_ObjectEvents[] = {
    object_event(5, 1, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CeruleanPoliceStationFishingGuruScript, -1),
    object_event(5, 4, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CeruleanPoliceStationPokefanFScript, -1),
    object_event(3, 5, SPRITE_DIGLETT, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &CeruleanDiglett, -1),
};

const struct MapEvents CeruleanPoliceStation_MapEvents = {
    .warp_event_count = lengthof(CeruleanPoliceStation_WarpEvents),
    .warp_events = CeruleanPoliceStation_WarpEvents,

    .coord_event_count = 0, // lengthof(CeruleanPoliceStation_CoordEvents),
    .coord_events = CeruleanPoliceStation_CoordEvents,

    .bg_event_count = 0, // lengthof(CeruleanPoliceStation_BGEvents),
    .bg_events = CeruleanPoliceStation_BGEvents,

    .obj_event_count = lengthof(CeruleanPoliceStation_ObjectEvents),
    .obj_events = CeruleanPoliceStation_ObjectEvents,
};

//// CODE

bool CeruleanPoliceStationFishingGuruScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeruleanPoliceStationFishingGuruText)
    SCRIPT_END
}
bool CeruleanPoliceStationPokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeruleanPoliceStationPokefanFText)
    SCRIPT_END
}
bool CeruleanDiglett(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CeruleanDiglettText)
    playcry(DIGLETT)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s CeruleanPoliceStationFishingGuruText[] = {
    text_start("I heard that some"
        t_line "shady character is"
        t_cont "skulking about."
        t_para "I won't stand for"
        t_line "it if he turns out"
        t_cont "to be a thief."
        t_done )
};
const txt_cmd_s CeruleanPoliceStationPokefanFText[] = {
    text_start("We were held up by"
        t_line "robbers before."
        t_done )
};
const txt_cmd_s CeruleanDiglettText[] = {
    text_start("DIGLETT: Dug dug."
        t_done )
    //db(0, 0) // filler
};
