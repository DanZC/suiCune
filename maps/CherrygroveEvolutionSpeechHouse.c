#include "../constants.h"
#include "../util/scripting.h"
#include "CherrygroveEvolutionSpeechHouse.h"
//// EVENTS
enum {
    CHERRYGROVEEVOLUTIONSPEECHHOUSE_LASS = 2,
    CHERRYGROVEEVOLUTIONSPEECHHOUSE_YOUNGSTER,
};

const Script_fn_t CherrygroveEvolutionSpeechHouse_SceneScripts[] = {
    0
};

const struct MapCallback CherrygroveEvolutionSpeechHouse_MapCallbacks[] = {
    0
};

const struct MapScripts CherrygroveEvolutionSpeechHouse_MapScripts = {
    .scene_script_count = lengthof(CherrygroveEvolutionSpeechHouse_SceneScripts),
    .scene_scripts = CherrygroveEvolutionSpeechHouse_SceneScripts,

    .callback_count = lengthof(CherrygroveEvolutionSpeechHouse_MapCallbacks),
    .callbacks = CherrygroveEvolutionSpeechHouse_MapCallbacks,
};

static const struct CoordEvent CherrygroveEvolutionSpeechHouse_CoordEvents[] = {
    0
};

static const struct BGEvent CherrygroveEvolutionSpeechHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &CherrygroveEvolutionSpeechHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &CherrygroveEvolutionSpeechHouseBookshelf),
};

static const struct WarpEventData CherrygroveEvolutionSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, CHERRYGROVE_CITY, 5),
    warp_event(3, 7, CHERRYGROVE_CITY, 5),
};

static const struct ObjEvent CherrygroveEvolutionSpeechHouse_ObjectEvents[] = {
    object_event(3, 5, SPRITE_LASS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CherrygroveEvolutionSpeechHouseLassScript, -1),
    object_event(2, 5, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CherrygroveEvolutionSpeechHouseYoungsterScript, -1),
};

const struct MapEvents CherrygroveEvolutionSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(CherrygroveEvolutionSpeechHouse_WarpEvents),
    .warp_events = CherrygroveEvolutionSpeechHouse_WarpEvents,

    .coord_event_count = lengthof(CherrygroveEvolutionSpeechHouse_CoordEvents),
    .coord_events = CherrygroveEvolutionSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(CherrygroveEvolutionSpeechHouse_BGEvents),
    .bg_events = CherrygroveEvolutionSpeechHouse_BGEvents,

    .obj_event_count = lengthof(CherrygroveEvolutionSpeechHouse_ObjectEvents),
    .obj_events = CherrygroveEvolutionSpeechHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CherrygroveEvolutionSpeechHouse.h"

bool CherrygroveEvolutionSpeechHouseYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CherrygroveEvolutionSpeechHouseYoungsterText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CherrygroveEvolutionSpeechHouseLassScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(CherrygroveEvolutionSpeechHouseLassText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool CherrygroveEvolutionSpeechHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s CherrygroveEvolutionSpeechHouseYoungsterText[] = {
    text_start("#MON gain expe-"
        t_line "rience in battle"
        t_para "and change their"
        t_line "form."
        t_done )
};
const txt_cmd_s CherrygroveEvolutionSpeechHouseLassText[] = {
    text_start("#MON change?"
        t_para "I would be shocked"
        t_line "if one did that!"
        t_done )
    //db(0, 0) // filler
};
