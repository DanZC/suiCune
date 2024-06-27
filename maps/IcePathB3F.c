#include "../constants.h"
#include "../util/scripting.h"
#include "IcePathB3F.h"
//// EVENTS
enum {
    ICEPATHB3F_POKE_BALL = 2,
    ICEPATHB3F_ROCK,
};

const Script_fn_t IcePathB3F_SceneScripts[] = {
    0,
};

const struct MapCallback IcePathB3F_MapCallbacks[] = {
    0,
};

const struct MapScripts IcePathB3F_MapScripts = {
    .scene_script_count = 0, // lengthof(IcePathB3F_SceneScripts),
    .scene_scripts = IcePathB3F_SceneScripts,

    .callback_count = 0, // lengthof(IcePathB3F_MapCallbacks),
    .callbacks = IcePathB3F_MapCallbacks,
};

static const struct CoordEvent IcePathB3F_CoordEvents[] = {
    0,
};

static const struct BGEvent IcePathB3F_BGEvents[] = {
    0,
};

static const struct WarpEventData IcePathB3F_WarpEvents[] = {
    warp_event(3, 5, ICE_PATH_B2F_MAHOGANY_SIDE, 2),
    warp_event(15, 5, ICE_PATH_B2F_BLACKTHORN_SIDE, 2),
};

static const struct ObjEvent IcePathB3F_ObjectEvents[] = {
    object_event(5, 7, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &IcePathB3FNevermeltice, EVENT_ICE_PATH_B3F_NEVERMELTICE),
    object_event(6, 6, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &IcePathB3FRock, -1),
};

const struct MapEvents IcePathB3F_MapEvents = {
    .warp_event_count = lengthof(IcePathB3F_WarpEvents),
    .warp_events = IcePathB3F_WarpEvents,

    .coord_event_count = 0, // lengthof(IcePathB3F_CoordEvents),
    .coord_events = IcePathB3F_CoordEvents,

    .bg_event_count = 0, // lengthof(IcePathB3F_BGEvents),
    .bg_events = IcePathB3F_BGEvents,

    .obj_event_count = lengthof(IcePathB3F_ObjectEvents),
    .obj_events = IcePathB3F_ObjectEvents,
};

//// CODE

const struct ItemBall IcePathB3FNevermeltice = {NEVERMELTICE, 1};
bool IcePathB3FRock(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(SmashRockScript)
    //db(0, 0) // filler
    SCRIPT_END
}
