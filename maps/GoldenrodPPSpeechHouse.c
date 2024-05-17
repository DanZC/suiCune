#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodPPSpeechHouse.h"
//// EVENTS
enum {
    GOLDENRODPPSPEECHHOUSE_FISHER = 2,
    GOLDENRODPPSPEECHHOUSE_LASS,
};

const Script_fn_t GoldenrodPPSpeechHouse_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodPPSpeechHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodPPSpeechHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodPPSpeechHouse_SceneScripts),
    .scene_scripts = GoldenrodPPSpeechHouse_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodPPSpeechHouse_MapCallbacks),
    .callbacks = GoldenrodPPSpeechHouse_MapCallbacks,
};

static const struct CoordEvent GoldenrodPPSpeechHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodPPSpeechHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &GoldenrodPPSpeechHouseBookshelf1),
    bg_event(1, 1, BGEVENT_READ, &GoldenrodPPSpeechHouseBookshelf2),
    bg_event(7, 1, BGEVENT_READ, &GoldenrodPPSpeechHouseRadio),
};

static const struct WarpEventData GoldenrodPPSpeechHouse_WarpEvents[] = {
    warp_event(2, 7, GOLDENROD_CITY, 7),
    warp_event(3, 7, GOLDENROD_CITY, 7),
};

static const struct ObjEvent GoldenrodPPSpeechHouse_ObjectEvents[] = {
    object_event(2, 4, SPRITE_FISHER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &GoldenrodPPSpeechHouseFisherScript, -1),
    object_event(5, 3, SPRITE_LASS, SPRITEMOVEDATA_STANDING_LEFT, 0, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodPPSpeechHouseLassScript, -1),
};

const struct MapEvents GoldenrodPPSpeechHouse_MapEvents = {
    .warp_event_count = lengthof(GoldenrodPPSpeechHouse_WarpEvents),
    .warp_events = GoldenrodPPSpeechHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodPPSpeechHouse_CoordEvents),
    .coord_events = GoldenrodPPSpeechHouse_CoordEvents,

    .bg_event_count = lengthof(GoldenrodPPSpeechHouse_BGEvents),
    .bg_events = GoldenrodPPSpeechHouse_BGEvents,

    .obj_event_count = lengthof(GoldenrodPPSpeechHouse_ObjectEvents),
    .obj_events = GoldenrodPPSpeechHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodPPSpeechHouse.h"

bool GoldenrodPPSpeechHouseFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodPPSpeechHouseFisherText)
    SCRIPT_END
}
bool GoldenrodPPSpeechHouseLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodPPSpeechHouseLassText)
    SCRIPT_END
}
bool GoldenrodPPSpeechHouseBookshelf2(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
bool GoldenrodPPSpeechHouseBookshelf1(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    SCRIPT_END
}
bool GoldenrodPPSpeechHouseRadio(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(Radio2Script)
    SCRIPT_END
}
const txt_cmd_s GoldenrodPPSpeechHouseFisherText[] = {
    text_start("Once while I was"
        t_line "battling, my"
        t_para "#MON couldn't"
        t_line "make any moves."
        t_para "The POWER POINTS,"
        t_line "or PP, of its"
        t_para "moves were all"
        t_line "gone."
        t_done )
};
const txt_cmd_s GoldenrodPPSpeechHouseLassText[] = {
    text_start("Sometimes, a"
        t_line "healthy #MON"
        t_para "may be unable to"
        t_line "use its moves."
        t_para "If that happens,"
        t_line "heal it at a #-"
        t_cont "MON CENTER or use"
        t_cont "an item."
        t_done )
    //db(0, 0) // filler
};
