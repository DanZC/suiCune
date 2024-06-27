#include "../constants.h"
#include "../util/scripting.h"
#include "DayOfWeekSiblingsHouse.h"
//// EVENTS
enum {
    DAYOFWEEKSIBLINGSHOUSE_POKEDEX = 2,
};

const Script_fn_t DayOfWeekSiblingsHouse_SceneScripts[] = {
    0,
};

const struct MapCallback DayOfWeekSiblingsHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts DayOfWeekSiblingsHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(DayOfWeekSiblingsHouse_SceneScripts),
    .scene_scripts = DayOfWeekSiblingsHouse_SceneScripts,

    .callback_count = 0, // lengthof(DayOfWeekSiblingsHouse_MapCallbacks),
    .callbacks = DayOfWeekSiblingsHouse_MapCallbacks,
};

static const struct CoordEvent DayOfWeekSiblingsHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent DayOfWeekSiblingsHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData DayOfWeekSiblingsHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_26, 3),
    warp_event(3, 7, ROUTE_26, 3),
};

static const struct ObjEvent DayOfWeekSiblingsHouse_ObjectEvents[] = {
    object_event(3, 3, SPRITE_POKEDEX, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DayOfWeekSiblingsHousePokedexScript, -1),
};

const struct MapEvents DayOfWeekSiblingsHouse_MapEvents = {
    .warp_event_count = lengthof(DayOfWeekSiblingsHouse_WarpEvents),
    .warp_events = DayOfWeekSiblingsHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(DayOfWeekSiblingsHouse_CoordEvents),
    .coord_events = DayOfWeekSiblingsHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(DayOfWeekSiblingsHouse_BGEvents),
    .bg_events = DayOfWeekSiblingsHouse_BGEvents,

    .obj_event_count = lengthof(DayOfWeekSiblingsHouse_ObjectEvents),
    .obj_events = DayOfWeekSiblingsHouse_ObjectEvents,
};

//// CODE

bool DayOfWeekSiblingsHousePokedexScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(DayOfWeekSiblingsHousePokedexText1)
    yesorno
    iffalse(End)
    writetext(DayOfWeekSiblingsHousePokedexText2)
    yesorno
    iffalse(End)
    writetext(DayOfWeekSiblingsHousePokedexText3)
    waitbutton
End:
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s DayOfWeekSiblingsHousePokedexText1[] = {
    text_start("There's something"
        t_line "written here."
        t_para "Read it?"
        t_done )
};
const txt_cmd_s DayOfWeekSiblingsHousePokedexText2[] = {
    text_start("To my brothers and"
        t_line "sisters:"
        t_para "We take pride in"
        t_line "serving #MON"
        t_cont "trainers."
        t_para "When trainers talk"
        t_line "to you, give them"
        t_cont "something useful."
        t_para "Love,"
        t_line "MONICA"
        t_para "Keep reading?"
        t_done )
};
const txt_cmd_s DayOfWeekSiblingsHousePokedexText3[] = {
    text_start("Monday, MONICA"
        t_line "ROUTE 40"
        t_para "Tuesday, TUSCANY"
        t_line "ROUTE 29"
        t_para "Wednesday, WESLEY"
        t_line "LAKE OF RAGE"
        t_para "Thursday, ARTHUR"
        t_line "ROUTE 36"
        t_para "Friday, FRIEDA"
        t_line "ROUTE 32"
        t_para "Saturday, SANTOS"
        t_line "BLACKTHORN CITY"
        t_para "Sunday, SUNNY"
        t_line "ROUTE 37"
        t_done )
    //db(0, 0) // filler
};
