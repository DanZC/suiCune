#include "../constants.h"
#include "../util/scripting.h"
#include "VermilionFishingSpeechHouse.h"
//// EVENTS
enum {
    VERMILIONFISHINGSPEECHHOUSE_FISHING_GURU = 2,
};

const Script_fn_t VermilionFishingSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback VermilionFishingSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts VermilionFishingSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(VermilionFishingSpeechHouse_SceneScripts),
    .scene_scripts = VermilionFishingSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(VermilionFishingSpeechHouse_MapCallbacks),
    .callbacks = VermilionFishingSpeechHouse_MapCallbacks,
};

static const struct CoordEvent VermilionFishingSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent VermilionFishingSpeechHouse_BGEvents[] = {
    bg_event(3, 0, BGEVENT_READ, &FishingDudesHousePhoto),
};

static const struct WarpEventData VermilionFishingSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, VERMILION_CITY, 1),
    warp_event(3, 7, VERMILION_CITY, 1),
};

static const struct ObjEvent VermilionFishingSpeechHouse_ObjectEvents[] = {
    object_event(2, 4, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &FishingDude, -1),
};

const struct MapEvents VermilionFishingSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(VermilionFishingSpeechHouse_WarpEvents),
    .warp_events = VermilionFishingSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(VermilionFishingSpeechHouse_CoordEvents),
    .coord_events = VermilionFishingSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(VermilionFishingSpeechHouse_BGEvents),
    .bg_events = VermilionFishingSpeechHouse_BGEvents,

    .obj_event_count = lengthof(VermilionFishingSpeechHouse_ObjectEvents),
    .obj_events = VermilionFishingSpeechHouse_ObjectEvents,
};

//// CODE

bool FishingDude(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(FishingDudeText)
    SCRIPT_END
}
bool FishingDudesHousePhoto(script_s* s) {
    SCRIPT_BEGIN
    jumptext(FishingDudesHousePhotoText)
    SCRIPT_END
}
bool FishingDudesHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s FishingDudeText[] = {
    text_start("I am the FISHING"
        t_line "DUDE, the elder of"
        t_cont "the FISHING BROS."
        t_para "Have you met the"
        t_line "FISHING GURU at"
        t_cont "LAKE OF RAGE?"
        t_para "He dreams about"
        t_line "seeing the world's"
        t_cont "greatest MAGIKARP."
        t_para "If you don't mind,"
        t_line "could you show him"
        t_para "any MAGIKARP you"
        t_line "catch?"
        t_para "Who knows, you may"
        t_line "catch the MAGIKARP"
        t_cont "of his dreams."
        t_done )
};
const txt_cmd_s FishingDudesHousePhotoText[] = {
    text_start("It's a photo of"
        t_line "people fishing…"
        t_para "They're having a"
        t_line "great time…"
        t_done )
    //db(0, 0) // filler
};
