#include "../constants.h"
#include "../util/scripting.h"
#include "VermilionMagnetTrainSpeechHouse.h"
//// EVENTS
enum {
    VERMILIONMAGNETTRAINSPEECHHOUSE_POKEFAN_F = 2,
    VERMILIONMAGNETTRAINSPEECHHOUSE_YOUNGSTER,
};

const Script_fn_t VermilionMagnetTrainSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback VermilionMagnetTrainSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts VermilionMagnetTrainSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(VermilionMagnetTrainSpeechHouse_SceneScripts),
    .scene_scripts = VermilionMagnetTrainSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(VermilionMagnetTrainSpeechHouse_MapCallbacks),
    .callbacks = VermilionMagnetTrainSpeechHouse_MapCallbacks,
};

static const struct CoordEvent VermilionMagnetTrainSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent VermilionMagnetTrainSpeechHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &VermilionMagnetTrainSpeechHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &VermilionMagnetTrainSpeechHouseBookshelf),
};

static const struct WarpEventData VermilionMagnetTrainSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, VERMILION_CITY, 4),
    warp_event(3, 7, VERMILION_CITY, 4),
};

static const struct ObjEvent VermilionMagnetTrainSpeechHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VermilionMagnetTrainSpeechHousePokefanFScript, -1),
    object_event(0, 3, SPRITE_YOUNGSTER, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &VermilionMagnetTrainSpeechHouseYoungsterScript, -1),
};

const struct MapEvents VermilionMagnetTrainSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(VermilionMagnetTrainSpeechHouse_WarpEvents),
    .warp_events = VermilionMagnetTrainSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(VermilionMagnetTrainSpeechHouse_CoordEvents),
    .coord_events = VermilionMagnetTrainSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(VermilionMagnetTrainSpeechHouse_BGEvents),
    .bg_events = VermilionMagnetTrainSpeechHouse_BGEvents,

    .obj_event_count = lengthof(VermilionMagnetTrainSpeechHouse_ObjectEvents),
    .obj_events = VermilionMagnetTrainSpeechHouse_ObjectEvents,
};

//// CODE

bool VermilionMagnetTrainSpeechHousePokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionMagnetTrainSpeechHousePokefanFText)
    SCRIPT_END
}
bool VermilionMagnetTrainSpeechHouseYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VermilionMagnetTrainSpeechHouseYoungsterText)
    SCRIPT_END
}
bool VermilionMagnetTrainSpeechHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s VermilionMagnetTrainSpeechHousePokefanFText[] = {
    text_start("Do you know about"
        t_line "the MAGNET TRAIN?"
        t_para "It's a railway"
        t_line "that goes to GOL-"
        t_cont "DENROD in JOHTO."
        t_done )
};
const txt_cmd_s VermilionMagnetTrainSpeechHouseYoungsterText[] = {
    text_start("I want to go to"
        t_line "SAFFRON to see"
        t_cont "the MAGNET TRAIN."
        t_done )
    //db(0, 0) // filler
};
