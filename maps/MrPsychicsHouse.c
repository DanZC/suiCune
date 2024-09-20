#include "../constants.h"
#include "../util/scripting.h"
#include "MrPsychicsHouse.h"
//// EVENTS
enum {
    MRPSYCHICSHOUSE_FISHING_GURU = 2,
};

const Script_fn_t MrPsychicsHouse_SceneScripts[] = {
    0,
};

const struct MapCallback MrPsychicsHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts MrPsychicsHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(MrPsychicsHouse_SceneScripts),
    .scene_scripts = MrPsychicsHouse_SceneScripts,

    .callback_count = 0, // lengthof(MrPsychicsHouse_MapCallbacks),
    .callbacks = MrPsychicsHouse_MapCallbacks,
};

static const struct CoordEvent MrPsychicsHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent MrPsychicsHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &MrPsychicsHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &MrPsychicsHouseBookshelf),
};

static const struct WarpEventData MrPsychicsHouse_WarpEvents[] = {
    warp_event(2, 7, SAFFRON_CITY, 5),
    warp_event(3, 7, SAFFRON_CITY, 5),
};

static const struct ObjEvent MrPsychicsHouse_ObjectEvents[] = {
    object_event(5, 3, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &MrPsychic, -1),
};

const struct MapEvents MrPsychicsHouse_MapEvents = {
    .warp_event_count = lengthof(MrPsychicsHouse_WarpEvents),
    .warp_events = MrPsychicsHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(MrPsychicsHouse_CoordEvents),
    .coord_events = MrPsychicsHouse_CoordEvents,

    .bg_event_count = lengthof(MrPsychicsHouse_BGEvents),
    .bg_events = MrPsychicsHouse_BGEvents,

    .obj_event_count = lengthof(MrPsychicsHouse_ObjectEvents),
    .obj_events = MrPsychicsHouse_ObjectEvents,
};

//// CODE

bool MrPsychic(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_TM29_PSYCHIC)
    iftrue(AlreadyGotItem)
    writetext(MrPsychicText1)
    promptbutton
    verbosegiveitem(TM_PSYCHIC_M, 1)
    iffalse(Done)
    setevent(EVENT_GOT_TM29_PSYCHIC)
AlreadyGotItem:
    writetext(MrPsychicText2)
    waitbutton
Done:
    closetext
    s_end
    SCRIPT_END
}
bool MrPsychicsHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s MrPsychicText1[] = {
    text_start("…"
        t_para "…"
        t_para "…"
        t_para "…I got it!"
        t_para "You wanted this!"
        t_done )
};
const txt_cmd_s MrPsychicText2[] = {
    text_start("TM29 is PSYCHIC."
        t_para "It may lower the"
        t_line "target's SPCL.DEF."
        t_done )
    //db(0, 0) // filler
};
