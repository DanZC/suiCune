#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakLugiaSpeechHouse.h"
//// EVENTS
enum {
    ECRUTEAKLUGIASPEECHHOUSE_GRAMPS = 2,
    ECRUTEAKLUGIASPEECHHOUSE_YOUNGSTER,
};

const Script_fn_t EcruteakLugiaSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback EcruteakLugiaSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts EcruteakLugiaSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(EcruteakLugiaSpeechHouse_SceneScripts),
    .scene_scripts = EcruteakLugiaSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(EcruteakLugiaSpeechHouse_MapCallbacks),
    .callbacks = EcruteakLugiaSpeechHouse_MapCallbacks,
};

static const struct CoordEvent EcruteakLugiaSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent EcruteakLugiaSpeechHouse_BGEvents[] = {
    bg_event(2, 1, BGEVENT_READ, &LugiaSpeechHouseRadio),
};

static const struct WarpEventData EcruteakLugiaSpeechHouse_WarpEvents[] = {
    warp_event(3, 7, ECRUTEAK_CITY, 7),
    warp_event(4, 7, ECRUTEAK_CITY, 7),
};

static const struct ObjEvent EcruteakLugiaSpeechHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_GRAMPS, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakLugiaSpeechHouseGrampsScript, -1),
    object_event(5, 4, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakLugiaSpeechHouseYoungsterScript, -1),
};

const struct MapEvents EcruteakLugiaSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(EcruteakLugiaSpeechHouse_WarpEvents),
    .warp_events = EcruteakLugiaSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(EcruteakLugiaSpeechHouse_CoordEvents),
    .coord_events = EcruteakLugiaSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(EcruteakLugiaSpeechHouse_BGEvents),
    .bg_events = EcruteakLugiaSpeechHouse_BGEvents,

    .obj_event_count = lengthof(EcruteakLugiaSpeechHouse_ObjectEvents),
    .obj_events = EcruteakLugiaSpeechHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakLugiaSpeechHouse.h"

bool EcruteakLugiaSpeechHouseGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakLugiaSpeechHouseGrampsText)
    SCRIPT_END
}
bool EcruteakLugiaSpeechHouseYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakLugiaSpeechHouseYoungsterText)
    SCRIPT_END
}
bool LugiaSpeechHouseRadio(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(Radio2Script)
    SCRIPT_END
}
const txt_cmd_s EcruteakLugiaSpeechHouseGrampsText[] = {
    text_start("This happened when"
        t_line "I was young."
        t_para "The sky suddenly"
        t_line "turned black. A"
        t_para "giant flying #-"
        t_line "MON was blocking"
        t_cont "out the sun."
        t_para "I wonder what that"
        t_line "#MON was? "
        t_para "It was like a bird"
        t_line "and a dragon."
        t_done )
};
const txt_cmd_s EcruteakLugiaSpeechHouseYoungsterText[] = {
    text_start("Is there really a"
        t_line "#MON that big?"
        t_para "If it exists, it"
        t_line "must be powerful."
        t_done )
    //db(0, 0) // filler
};
