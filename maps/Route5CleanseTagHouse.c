#include "../constants.h"
#include "../util/scripting.h"
#include "Route5CleanseTagHouse.h"
//// EVENTS
enum {
    ROUTE5CLEANSETAGHOUSE_GRANNY = 2,
    ROUTE5CLEANSETAGHOUSE_TEACHER,
};

const Script_fn_t Route5CleanseTagHouse_SceneScripts[] = {
    0,
};

const struct MapCallback Route5CleanseTagHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts Route5CleanseTagHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(Route5CleanseTagHouse_SceneScripts),
    .scene_scripts = Route5CleanseTagHouse_SceneScripts,

    .callback_count = 0, // lengthof(Route5CleanseTagHouse_MapCallbacks),
    .callbacks = Route5CleanseTagHouse_MapCallbacks,
};

static const struct CoordEvent Route5CleanseTagHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent Route5CleanseTagHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &HouseForSaleBookshelf),
    bg_event(1, 1, BGEVENT_READ, &HouseForSaleBookshelf),
};

static const struct WarpEventData Route5CleanseTagHouse_WarpEvents[] = {
    warp_event(2, 7, ROUTE_5, 4),
    warp_event(3, 7, ROUTE_5, 4),
};

static const struct ObjEvent Route5CleanseTagHouse_ObjectEvents[] = {
    object_event(2, 5, SPRITE_GRANNY, SPRITEMOVEDATA_SPINCLOCKWISE, 0, 0, -1, -1, PAL_NPC_BROWN, OBJECTTYPE_SCRIPT, 0, &Route5CleanseTagHouseGrannyScript, -1),
    object_event(5, 3, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route5CleanseTagHouseTeacherScript, -1),
};

const struct MapEvents Route5CleanseTagHouse_MapEvents = {
    .warp_event_count = lengthof(Route5CleanseTagHouse_WarpEvents),
    .warp_events = Route5CleanseTagHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(Route5CleanseTagHouse_CoordEvents),
    .coord_events = Route5CleanseTagHouse_CoordEvents,

    .bg_event_count = lengthof(Route5CleanseTagHouse_BGEvents),
    .bg_events = Route5CleanseTagHouse_BGEvents,

    .obj_event_count = lengthof(Route5CleanseTagHouse_ObjectEvents),
    .obj_events = Route5CleanseTagHouse_ObjectEvents,
};

//// CODE

bool Route5CleanseTagHouseGrannyScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_CLEANSE_TAG)
    iftrue(GotCleanseTag)
    writetext(Route5CleanseTagHouseGrannyText1)
    promptbutton
    verbosegiveitem(CLEANSE_TAG, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_CLEANSE_TAG)
GotCleanseTag:
    writetext(Route5CleanseTagHouseGrannyText2)
    waitbutton
NoRoom:
    closetext
    s_end
    SCRIPT_END
}
bool Route5CleanseTagHouseTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route5CleanseTagHouseTeacherText)
    SCRIPT_END
}
bool HouseForSaleBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s Route5CleanseTagHouseGrannyText1[] = {
    text_start("Eeyaaaah!"
        t_para "I sense a sinister"
        t_line "shadow hovering"
        t_cont "over you."
        t_para "Take this to ward"
        t_line "it off!"
        t_done )
};
const txt_cmd_s Route5CleanseTagHouseGrannyText2[] = {
    text_start("You were in mortal"
        t_line "danger, but you"
        t_cont "are protected now."
        t_done )
};
const txt_cmd_s Route5CleanseTagHouseTeacherText[] = {
    text_start("My grandma is into"
        t_line "warding off what"
        t_para "she believes to be"
        t_line "evil spirits."
        t_para "I'm sorry that she"
        t_line "startled you."
        t_done )
    //db(0, 0) // filler
};
