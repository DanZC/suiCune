#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodNameRater.h"
//// EVENTS
enum {
    GOLDENRODNAMERATER_NAME_RATER = 2,
};

const Script_fn_t GoldenrodNameRater_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodNameRater_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodNameRater_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodNameRater_SceneScripts),
    .scene_scripts = GoldenrodNameRater_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodNameRater_MapCallbacks),
    .callbacks = GoldenrodNameRater_MapCallbacks,
};

static const struct CoordEvent GoldenrodNameRater_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodNameRater_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &GoldenrodNameRaterBookshelf),
    bg_event(1, 1, BGEVENT_READ, &GoldenrodNameRaterBookshelf),
    bg_event(7, 1, BGEVENT_READ, &GoldenrodNameRaterRadio),
};

static const struct WarpEventData GoldenrodNameRater_WarpEvents[] = {
    warp_event(2, 7, GOLDENROD_CITY, 8),
    warp_event(3, 7, GOLDENROD_CITY, 8),
};

static const struct ObjEvent GoldenrodNameRater_ObjectEvents[] = {
    object_event(2, 4, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_DOWN, 2, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodNameRater, -1),
};

const struct MapEvents GoldenrodNameRater_MapEvents = {
    .warp_event_count = lengthof(GoldenrodNameRater_WarpEvents),
    .warp_events = GoldenrodNameRater_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodNameRater_CoordEvents),
    .coord_events = GoldenrodNameRater_CoordEvents,

    .bg_event_count = lengthof(GoldenrodNameRater_BGEvents),
    .bg_events = GoldenrodNameRater_BGEvents,

    .obj_event_count = lengthof(GoldenrodNameRater_ObjectEvents),
    .obj_events = GoldenrodNameRater_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodNameRater.h"

bool GoldenrodNameRater(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    special(NameRater)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodNameRaterBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    SCRIPT_END
}
bool GoldenrodNameRaterRadio(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(Radio2Script)
//INCLUDE "data/text/unused_sweet_honey.asm"
    //db(0, 0) // filler
    SCRIPT_END
}
