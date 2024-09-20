#include "../constants.h"
#include "../util/scripting.h"
#include "CeruleanGymBadgeSpeechHouse.h"
//// EVENTS
enum {
    CERULEANGYMBADGESPEECHHOUSE_POKEFAN_M = 2,
};

const Script_fn_t CeruleanGymBadgeSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback CeruleanGymBadgeSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts CeruleanGymBadgeSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(CeruleanGymBadgeSpeechHouse_SceneScripts),
    .scene_scripts = CeruleanGymBadgeSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(CeruleanGymBadgeSpeechHouse_MapCallbacks),
    .callbacks = CeruleanGymBadgeSpeechHouse_MapCallbacks,
};

static const struct CoordEvent CeruleanGymBadgeSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent CeruleanGymBadgeSpeechHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData CeruleanGymBadgeSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, CERULEAN_CITY, 1),
    warp_event(3, 7, CERULEAN_CITY, 1),
};

static const struct ObjEvent CeruleanGymBadgeSpeechHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CeruleanGymBadgeSpeechHousePokefanMScript, -1),
};

const struct MapEvents CeruleanGymBadgeSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(CeruleanGymBadgeSpeechHouse_WarpEvents),
    .warp_events = CeruleanGymBadgeSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(CeruleanGymBadgeSpeechHouse_CoordEvents),
    .coord_events = CeruleanGymBadgeSpeechHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(CeruleanGymBadgeSpeechHouse_BGEvents),
    .bg_events = CeruleanGymBadgeSpeechHouse_BGEvents,

    .obj_event_count = lengthof(CeruleanGymBadgeSpeechHouse_ObjectEvents),
    .obj_events = CeruleanGymBadgeSpeechHouse_ObjectEvents,
};

//// CODE

bool CeruleanGymBadgeSpeechHousePokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CeruleanGymBadgeSpeechHousePokefanMText)
    SCRIPT_END
}
const txt_cmd_s CeruleanGymBadgeSpeechHousePokefanMText[] = {
    text_start("Are you collecting"
        t_line "KANTO GYM BADGES?"
        t_done )
    //db(0, 0) // filler
};
