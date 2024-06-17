#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodLugiaSpeechHouse.h"
//// EVENTS
enum {
    CIANWOODLUGIASPEECHHOUSE_TEACHER = 2,
    CIANWOODLUGIASPEECHHOUSE_LASS,
    CIANWOODLUGIASPEECHHOUSE_TWIN,
};

const Script_fn_t CianwoodLugiaSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback CianwoodLugiaSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts CianwoodLugiaSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(CianwoodLugiaSpeechHouse_SceneScripts),
    .scene_scripts = CianwoodLugiaSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(CianwoodLugiaSpeechHouse_MapCallbacks),
    .callbacks = CianwoodLugiaSpeechHouse_MapCallbacks,
};

static const struct CoordEvent CianwoodLugiaSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent CianwoodLugiaSpeechHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &CianwoodLugiaSpeechHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &CianwoodLugiaSpeechHouseBookshelf),
};

static const struct WarpEventData CianwoodLugiaSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, CIANWOOD_CITY, 6),
    warp_event(3, 7, CIANWOOD_CITY, 6),
};

static const struct ObjEvent CianwoodLugiaSpeechHouse_ObjectEvents[] = {
    object_event(2, 4, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CianwoodLugiaSpeechHouseTeacherScript, -1),
    object_event(6, 5, SPRITE_LASS, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &CianwoodLugiaSpeechHouseLassScript, -1),
    object_event(0, 2, SPRITE_TWIN, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &CianwoodLugiaSpeechHouseTwinScript, -1),
};

const struct MapEvents CianwoodLugiaSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(CianwoodLugiaSpeechHouse_WarpEvents),
    .warp_events = CianwoodLugiaSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(CianwoodLugiaSpeechHouse_CoordEvents),
    .coord_events = CianwoodLugiaSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(CianwoodLugiaSpeechHouse_BGEvents),
    .bg_events = CianwoodLugiaSpeechHouse_BGEvents,

    .obj_event_count = lengthof(CianwoodLugiaSpeechHouse_ObjectEvents),
    .obj_events = CianwoodLugiaSpeechHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CianwoodLugiaSpeechHouse.h"

bool CianwoodLugiaSpeechHouseTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CianwoodLugiaSpeechHouseTeacherText)
    SCRIPT_END
}
bool CianwoodLugiaSpeechHouseLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CianwoodLugiaSpeechHouseLassText)
    SCRIPT_END
}
bool CianwoodLugiaSpeechHouseTwinScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CianwoodLugiaSpeechHouseTwinText)
    SCRIPT_END
}
bool CianwoodLugiaSpeechHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s CianwoodLugiaSpeechHouseTeacherText[] = {
    text_start("You came from"
        t_line "OLIVINE?"
        t_para "Do you remember"
        t_line "the four islands"
        t_cont "along the way?"
        t_para "I heard that a "
        t_line "mythical sea crea-"
        t_cont "ture is hiding in"
        t_cont "them."
        t_done )
};
const txt_cmd_s CianwoodLugiaSpeechHouseLassText[] = {
    text_start("I heard that you"
        t_line "can only see it if"
        t_para "you have a SILVER"
        t_line "WING."
        t_para "It must have the"
        t_line "same scent as the"
        t_cont "creature."
        t_done )
};
const txt_cmd_s CianwoodLugiaSpeechHouseTwinText[] = {
    text_start("I've heard that"
        t_line "the whirlpools"
        t_para "around the islands"
        t_line "are caused by the"
        t_cont "sea creature."
        t_para "You might need a"
        t_line "special move to"
        t_cont "get past them."
        t_done )
    //db(0, 0) // filler
};
