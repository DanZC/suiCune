#include "../constants.h"
#include "../util/scripting.h"
#include "LavenderSpeechHouse.h"
//// EVENTS
enum {
    LAVENDERSPEECHHOUSE_POKEFAN_F = 2,
};

const Script_fn_t LavenderSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback LavenderSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts LavenderSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(LavenderSpeechHouse_SceneScripts),
    .scene_scripts = LavenderSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(LavenderSpeechHouse_MapCallbacks),
    .callbacks = LavenderSpeechHouse_MapCallbacks,
};

static const struct CoordEvent LavenderSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent LavenderSpeechHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &LavenderSpeechHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &LavenderSpeechHouseBookshelf),
};

static const struct WarpEventData LavenderSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, LAVENDER_TOWN, 3),
    warp_event(3, 7, LAVENDER_TOWN, 3),
};

static const struct ObjEvent LavenderSpeechHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_POKEFAN_F, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &LavenderSpeechHousePokefanFScript, -1),
};

const struct MapEvents LavenderSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(LavenderSpeechHouse_WarpEvents),
    .warp_events = LavenderSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(LavenderSpeechHouse_CoordEvents),
    .coord_events = LavenderSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(LavenderSpeechHouse_BGEvents),
    .bg_events = LavenderSpeechHouse_BGEvents,

    .obj_event_count = lengthof(LavenderSpeechHouse_ObjectEvents),
    .obj_events = LavenderSpeechHouse_ObjectEvents,
};

//// CODE

bool LavenderSpeechHousePokefanFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(LavenderSpeechHousePokefanFText)
    SCRIPT_END
}
bool LavenderSpeechHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s LavenderSpeechHousePokefanFText[] = {
    text_start("LAVENDER is a"
        t_line "tiny, quiet town"
        t_para "at the foot of the"
        t_line "mountains."
        t_para "It's gotten a bit"
        t_line "busier since the"
        t_para "RADIO TOWER was"
        t_line "built."
        t_done )
    //db(0, 0) // filler
};
