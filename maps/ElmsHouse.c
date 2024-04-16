#include "../constants.h"
#include "../util/scripting.h"
#include "ElmsHouse.h"
//// EVENTS
enum {
    ELMSHOUSE_ELMS_WIFE = 2,
    ELMSHOUSE_ELMS_SON,
};

const Script_fn_t ElmsHouse_SceneScripts[] = {
    0,
};

const struct MapCallback ElmsHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts ElmsHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(ElmsHouse_SceneScripts),
    .scene_scripts = ElmsHouse_SceneScripts,

    .callback_count = 0, // lengthof(ElmsHouse_MapCallbacks),
    .callbacks = ElmsHouse_MapCallbacks,
};

static const struct CoordEvent ElmsHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent ElmsHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &ElmsHousePC),
    bg_event(6, 1, BGEVENT_READ, &ElmsHouseBookshelf),
    bg_event(7, 1, BGEVENT_READ, &ElmsHouseBookshelf),
};

static const struct WarpEventData ElmsHouse_WarpEvents[] = {
    warp_event(2, 7, NEW_BARK_TOWN, 4),
    warp_event(3, 7, NEW_BARK_TOWN, 4),
};

static const struct ObjEvent ElmsHouse_ObjectEvents[] = {
    object_event(1, 5, SPRITE_TEACHER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &ElmsWife, -1),
    object_event(5, 4, SPRITE_BUG_CATCHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ElmsSon, -1),
};

const struct MapEvents ElmsHouse_MapEvents = {
    .warp_event_count = lengthof(ElmsHouse_WarpEvents),
    .warp_events = ElmsHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(ElmsHouse_CoordEvents),
    .coord_events = ElmsHouse_CoordEvents,

    .bg_event_count = lengthof(ElmsHouse_BGEvents),
    .bg_events = ElmsHouse_BGEvents,

    .obj_event_count = lengthof(ElmsHouse_ObjectEvents),
    .obj_events = ElmsHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "ElmsHouse.h"

bool ElmsWife(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(ElmsWifeText)
    SCRIPT_END
}
bool ElmsSon(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(ElmsSonText)
    SCRIPT_END
}
bool ElmsHousePC(script_s* s) {
    SCRIPT_BEGIN
    jumptext(ElmsHousePCText)
    SCRIPT_END
}
bool ElmsHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
const txt_cmd_s ElmsWifeText[] = {
    text_start("Hi, <PLAY_G>! My"
        t_line "husband's always"
        t_para "so busy--I hope"
        t_line "he's OK."
        t_para "When he's caught"
        t_line "up in his #MON"
        t_para "research, he even"
        t_line "forgets to eat."
        t_done )
};
const txt_cmd_s ElmsSonText[] = {
    text_start("When I grow up,"
        t_line "I'm going to help"
        t_cont "my dad!"
        t_para "I'm going to be a"
        t_line "great #MON"
        t_cont "professor!"
        t_done )
};
const txt_cmd_s ElmsHouseLabFoodText[] = {
    text_start("There's some food"
        t_line "here. It must be"
        t_cont "for the LAB."
        t_done )
};
const txt_cmd_s ElmsHousePokemonFoodText[] = {
    text_start("There's some food"
        t_line "here. This must be"
        t_cont "for #MON."
        t_done )
};
const txt_cmd_s ElmsHousePCText[] = {
    text_start("#MON. Where do"
        t_line "they come from? "
        t_para "Where are they"
        t_line "going?"
        t_para "Why has no one"
        t_line "ever witnessed a"
        t_cont "#MON's birth?"
        t_para "I want to know! I"
        t_line "will dedicate my"
        t_para "life to the study"
        t_line "of #MON!"
        t_para "…"
        t_para "It's a part of"
        t_line "PROF.ELM's re-"
        t_cont "search papers."
        t_done )
    //db(0, 0) // filler
};
