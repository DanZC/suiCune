#include "../constants.h"
#include "../util/scripting.h"
#include "LavenderNameRater.h"
//// EVENTS
enum {
    LAVENDERNAMERATER_NAME_RATER = 2,
};

const Script_fn_t LavenderNameRater_SceneScripts[] = {
    LavenderNameRater_MapScripts_DummyScene,
};

const struct MapCallback LavenderNameRater_MapCallbacks[] = {
    0,
};

const struct MapScripts LavenderNameRater_MapScripts = {
    .scene_script_count = lengthof(LavenderNameRater_SceneScripts),
    .scene_scripts = LavenderNameRater_SceneScripts,

    .callback_count = 0, // lengthof(LavenderNameRater_MapCallbacks),
    .callbacks = LavenderNameRater_MapCallbacks,
};

static const struct CoordEvent LavenderNameRater_CoordEvents[] = {
    0,
};

static const struct BGEvent LavenderNameRater_BGEvents[] = {
    0,
};

static const struct WarpEventData LavenderNameRater_WarpEvents[] = {
    warp_event(2, 7, LAVENDER_TOWN, 4),
    warp_event(3, 7, LAVENDER_TOWN, 4),
};

static const struct ObjEvent LavenderNameRater_ObjectEvents[] = {
    object_event(2, 3, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &LavenderNameRater, -1),
};

const struct MapEvents LavenderNameRater_MapEvents = {
    .warp_event_count = lengthof(LavenderNameRater_WarpEvents),
    .warp_events = LavenderNameRater_WarpEvents,

    .coord_event_count = 0, // lengthof(LavenderNameRater_CoordEvents),
    .coord_events = LavenderNameRater_CoordEvents,

    .bg_event_count = 0, // lengthof(LavenderNameRater_BGEvents),
    .bg_events = LavenderNameRater_BGEvents,

    .obj_event_count = lengthof(LavenderNameRater_ObjectEvents),
    .obj_events = LavenderNameRater_ObjectEvents,
};

//// CODE

bool LavenderNameRater_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool LavenderNameRater(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    special(NameRater)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool LavenderNameRaterUnusedBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(DifficultBookshelfScript)
    //db(0, 0) // filler
    SCRIPT_END
}
