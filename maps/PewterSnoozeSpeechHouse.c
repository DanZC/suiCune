#include "../constants.h"
#include "../util/scripting.h"
#include "PewterSnoozeSpeechHouse.h"
//// EVENTS
enum {
    PEWTERSNOOZESPEECHHOUSE_GRAMPS = 2,
};

const Script_fn_t PewterSnoozeSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback PewterSnoozeSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts PewterSnoozeSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(PewterSnoozeSpeechHouse_SceneScripts),
    .scene_scripts = PewterSnoozeSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(PewterSnoozeSpeechHouse_MapCallbacks),
    .callbacks = PewterSnoozeSpeechHouse_MapCallbacks,
};

static const struct CoordEvent PewterSnoozeSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent PewterSnoozeSpeechHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &PewterSnoozeSpeechHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &PewterSnoozeSpeechHouseBookshelf),
};

static const struct WarpEventData PewterSnoozeSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, PEWTER_CITY, 5),
    warp_event(3, 7, PEWTER_CITY, 5),
};

static const struct ObjEvent PewterSnoozeSpeechHouse_ObjectEvents[] = {
    object_event(5, 3, SPRITE_GRAMPS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &PewterSnoozeSpeechHouseGrampsScript, -1),
};

const struct MapEvents PewterSnoozeSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(PewterSnoozeSpeechHouse_WarpEvents),
    .warp_events = PewterSnoozeSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(PewterSnoozeSpeechHouse_CoordEvents),
    .coord_events = PewterSnoozeSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(PewterSnoozeSpeechHouse_BGEvents),
    .bg_events = PewterSnoozeSpeechHouse_BGEvents,

    .obj_event_count = lengthof(PewterSnoozeSpeechHouse_ObjectEvents),
    .obj_events = PewterSnoozeSpeechHouse_ObjectEvents,
};

//// CODE

bool PewterSnoozeSpeechHouseGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(PewterSnoozeSpeechHouseGrampsText)
    SCRIPT_END
}
bool PewterSnoozeSpeechHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s PewterSnoozeSpeechHouseGrampsText[] = {
    text_start("I like snoozing"
        t_line "with the radio on…"
        t_cont "…Zzzz…"
        t_done )
    //db(0, 0) // filler
};
