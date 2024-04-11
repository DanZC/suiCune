#include "../constants.h"
#include "../util/scripting.h"
#include "CherrygroveGymSpeechHouse.h"
//// EVENTS
enum {
    CHERRYGROVEGYMSPEECHHOUSE_POKEFAN_M = 2,
    CHERRYGROVEGYMSPEECHHOUSE_BUG_CATCHER,
};

const Script_fn_t CherrygroveGymSpeechHouse_SceneScripts[] = {
};

const struct MapCallback CherrygroveGymSpeechHouse_MapCallbacks[] = {
};

const struct MapScripts CherrygroveGymSpeechHouse_MapScripts = {
    .scene_script_count = lengthof(CherrygroveGymSpeechHouse_SceneScripts),
    .scene_scripts = CherrygroveGymSpeechHouse_SceneScripts,

    .callback_count = lengthof(CherrygroveGymSpeechHouse_MapCallbacks),
    .callbacks = CherrygroveGymSpeechHouse_MapCallbacks,
};

static const struct CoordEvent CherrygroveGymSpeechHouse_CoordEvents[] = {
};

static const struct BGEvent CherrygroveGymSpeechHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &CherrygroveGymSpeechHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &CherrygroveGymSpeechHouseBookshelf),
};

static const struct WarpEventData CherrygroveGymSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, CHERRYGROVE_CITY, 3),
    warp_event(3, 7, CHERRYGROVE_CITY, 3),
};

static const struct ObjEvent CherrygroveGymSpeechHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_POKEFAN_M, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CherrygroveGymSpeechHousePokefanMScript, -1),
    object_event(5, 5, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &CherrygroveGymSpeechHouseBugCatcherScript, -1),
};

const struct MapEvents CherrygroveGymSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(CherrygroveGymSpeechHouse_WarpEvents),
    .warp_events = CherrygroveGymSpeechHouse_WarpEvents,

    .coord_event_count = lengthof(CherrygroveGymSpeechHouse_CoordEvents),
    .coord_events = CherrygroveGymSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(CherrygroveGymSpeechHouse_BGEvents),
    .bg_events = CherrygroveGymSpeechHouse_BGEvents,

    .obj_event_count = lengthof(CherrygroveGymSpeechHouse_ObjectEvents),
    .obj_events = CherrygroveGymSpeechHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "CherrygroveGymSpeechHouse.h"

bool CherrygroveGymSpeechHousePokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CherrygroveGymSpeechHousePokefanMText)
    SCRIPT_END
}
bool CherrygroveGymSpeechHouseBugCatcherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(CherrygroveGymSpeechHouseBugCatcherText)
    SCRIPT_END
}
bool CherrygroveGymSpeechHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PictureBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s CherrygroveGymSpeechHousePokefanMText[] = {
    text_start("You're trying to"
        t_line "see how good you"
        t_para "are as a #MON"
        t_line "trainer?"
        t_para "You better visit"
        t_line "the #MON GYMS"
        t_para "all over JOHTO and"
        t_line "collect BADGES."
        t_done )
};
const txt_cmd_s CherrygroveGymSpeechHouseBugCatcherText[] = {
    text_start("When I get older,"
        t_line "I'm going to be a"
        t_cont "GYM LEADER!"
        t_para "I make my #MON"
        t_line "battle with my"
        t_para "friend's to make"
        t_line "them tougher!"
        t_done )
    //db(0, 0) // filler
};
