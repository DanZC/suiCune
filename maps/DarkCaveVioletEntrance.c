#include "../constants.h"
#include "../util/scripting.h"
#include "DarkCaveVioletEntrance.h"
//// EVENTS
enum {
    DARKCAVEVIOLETENTRANCE_POKE_BALL1 = 2,
    DARKCAVEVIOLETENTRANCE_ROCK1,
    DARKCAVEVIOLETENTRANCE_ROCK2,
    DARKCAVEVIOLETENTRANCE_ROCK3,
    DARKCAVEVIOLETENTRANCE_ROCK4,
    DARKCAVEVIOLETENTRANCE_POKE_BALL2,
    DARKCAVEVIOLETENTRANCE_POKE_BALL3,
    DARKCAVEVIOLETENTRANCE_POKE_BALL4,
};

const Script_fn_t DarkCaveVioletEntrance_SceneScripts[] = {
    0
};

const struct MapCallback DarkCaveVioletEntrance_MapCallbacks[] = {
    0
};

const struct MapScripts DarkCaveVioletEntrance_MapScripts = {
    .scene_script_count = 0, // lengthof(DarkCaveVioletEntrance_SceneScripts),
    .scene_scripts = DarkCaveVioletEntrance_SceneScripts,

    .callback_count = 0, // lengthof(DarkCaveVioletEntrance_MapCallbacks),
    .callbacks = DarkCaveVioletEntrance_MapCallbacks,
};

static const struct CoordEvent DarkCaveVioletEntrance_CoordEvents[] = {
    0
};

static const struct BGEvent DarkCaveVioletEntrance_BGEvents[] = {
    bg_event(26, 3, BGEVENT_ITEM, &DarkCaveVioletEntranceHiddenElixer),
};

static const struct WarpEventData DarkCaveVioletEntrance_WarpEvents[] = {
    warp_event(3, 15, ROUTE_31, 3),
    warp_event(17, 1, DARK_CAVE_BLACKTHORN_ENTRANCE, 2),
    warp_event(35, 33, ROUTE_46, 3),
};

static const struct ObjEvent DarkCaveVioletEntrance_ObjectEvents[] = {
    object_event(6, 8, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &DarkCaveVioletEntrancePotion, EVENT_DARK_CAVE_VIOLET_ENTRANCE_POTION),
    object_event(16, 14, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DarkCaveVioletEntranceRock, -1),
    object_event(27, 6, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DarkCaveVioletEntranceRock, -1),
    object_event(7, 14, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DarkCaveVioletEntranceRock, -1),
    object_event(36, 31, SPRITE_ROCK, SPRITEMOVEDATA_SMASHABLE_ROCK, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &DarkCaveVioletEntranceRock, -1),
    object_event(36, 22, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &DarkCaveVioletEntranceFullHeal, EVENT_DARK_CAVE_VIOLET_ENTRANCE_FULL_HEAL),
    object_event(35, 9, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &DarkCaveVioletEntranceHyperPotion, EVENT_DARK_CAVE_VIOLET_ENTRANCE_HYPER_POTION),
    object_event(30, 28, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &DarkCaveVioletEntranceDireHit, EVENT_DARK_CAVE_VIOLET_ENTRANCE_DIRE_HIT),
};

const struct MapEvents DarkCaveVioletEntrance_MapEvents = {
    .warp_event_count = lengthof(DarkCaveVioletEntrance_WarpEvents),
    .warp_events = DarkCaveVioletEntrance_WarpEvents,

    .coord_event_count = 0, // lengthof(DarkCaveVioletEntrance_CoordEvents),
    .coord_events = DarkCaveVioletEntrance_CoordEvents,

    .bg_event_count = lengthof(DarkCaveVioletEntrance_BGEvents),
    .bg_events = DarkCaveVioletEntrance_BGEvents,

    .obj_event_count = lengthof(DarkCaveVioletEntrance_ObjectEvents),
    .obj_events = DarkCaveVioletEntrance_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "DarkCaveVioletEntrance.h"

const struct ItemBall DarkCaveVioletEntrancePotion = {POTION, 1};
const struct ItemBall DarkCaveVioletEntranceFullHeal = {FULL_HEAL, 1};
const struct ItemBall DarkCaveVioletEntranceHyperPotion = {HYPER_POTION, 1};
const struct ItemBall DarkCaveVioletEntranceDireHit = {DIRE_HIT, 1};
bool DarkCaveVioletEntranceRock(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(SmashRockScript)
    SCRIPT_END
}
const struct HiddenItem DarkCaveVioletEntranceHiddenElixer = {ELIXER, EVENT_DARK_CAVE_VIOLET_ENTRANCE_HIDDEN_ELIXER};
    //db(0, 0) // filler
