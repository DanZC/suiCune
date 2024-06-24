#include "../constants.h"
#include "../util/scripting.h"
#include "WhirlIslandB1F.h"
//// EVENTS
enum {
    WHIRLISLANDB1F_POKE_BALL1 = 2,
    WHIRLISLANDB1F_POKE_BALL2,
    WHIRLISLANDB1F_POKE_BALL3,
    WHIRLISLANDB1F_POKE_BALL4,
    WHIRLISLANDB1F_POKE_BALL5,
    WHIRLISLANDB1F_BOULDER,
};

const Script_fn_t WhirlIslandB1F_SceneScripts[] = {
    0,
};

const struct MapCallback WhirlIslandB1F_MapCallbacks[] = {
    0,
};

const struct MapScripts WhirlIslandB1F_MapScripts = {
    .scene_script_count = 0, // lengthof(WhirlIslandB1F_SceneScripts),
    .scene_scripts = WhirlIslandB1F_SceneScripts,

    .callback_count = 0, // lengthof(WhirlIslandB1F_MapCallbacks),
    .callbacks = WhirlIslandB1F_MapCallbacks,
};

static const struct CoordEvent WhirlIslandB1F_CoordEvents[] = {
    0,
};

static const struct BGEvent WhirlIslandB1F_BGEvents[] = {
    bg_event(30, 4, BGEVENT_ITEM, &WhirlIslandB1FHiddenRareCandy),
    bg_event(36, 18, BGEVENT_ITEM, &WhirlIslandB1FHiddenUltraBall),
    bg_event(2, 23, BGEVENT_ITEM, &WhirlIslandB1FHiddenFullRestore),
};

static const struct WarpEventData WhirlIslandB1F_WarpEvents[] = {
    warp_event(5, 5, WHIRL_ISLAND_NW, 2),
    warp_event(35, 3, WHIRL_ISLAND_NE, 2),
    warp_event(29, 9, WHIRL_ISLAND_NE, 3),
    warp_event(9, 31, WHIRL_ISLAND_SW, 3),
    warp_event(23, 31, WHIRL_ISLAND_SW, 2),
    warp_event(31, 29, WHIRL_ISLAND_SE, 2),
    warp_event(25, 21, WHIRL_ISLAND_B2F, 1),
    warp_event(13, 27, WHIRL_ISLAND_B2F, 2),
    warp_event(17, 21, WHIRL_ISLAND_CAVE, 1),
};

static const struct ObjEvent WhirlIslandB1F_ObjectEvents[] = {
    object_event(7, 13, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &WhirlIslandB1FFullRestore, EVENT_WHIRL_ISLAND_B1F_FULL_RESTORE),
    object_event(2, 18, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &WhirlIslandB1FCarbos, EVENT_WHIRL_ISLAND_B1F_CARBOS),
    object_event(33, 23, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &WhirlIslandB1FCalcium, EVENT_WHIRL_ISLAND_B1F_CALCIUM),
    object_event(17, 8, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &WhirlIslandB1FNugget, EVENT_WHIRL_ISLAND_B1F_NUGGET),
    object_event(19, 26, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &WhirlIslandB1FEscapeRope, EVENT_WHIRL_ISLAND_B1F_ESCAPE_ROPE),
    object_event(23, 26, SPRITE_BOULDER, SPRITEMOVEDATA_STRENGTH_BOULDER, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &WhirlIslandB1FBoulder, -1),
};

const struct MapEvents WhirlIslandB1F_MapEvents = {
    .warp_event_count = lengthof(WhirlIslandB1F_WarpEvents),
    .warp_events = WhirlIslandB1F_WarpEvents,

    .coord_event_count = 0, // lengthof(WhirlIslandB1F_CoordEvents),
    .coord_events = WhirlIslandB1F_CoordEvents,

    .bg_event_count = lengthof(WhirlIslandB1F_BGEvents),
    .bg_events = WhirlIslandB1F_BGEvents,

    .obj_event_count = lengthof(WhirlIslandB1F_ObjectEvents),
    .obj_events = WhirlIslandB1F_ObjectEvents,
};

//// CODE

const struct ItemBall WhirlIslandB1FFullRestore = {FULL_RESTORE, 1};
const struct ItemBall WhirlIslandB1FCarbos = {CARBOS, 1};
const struct ItemBall WhirlIslandB1FCalcium = {CALCIUM, 1};
const struct ItemBall WhirlIslandB1FNugget = {NUGGET, 1};
const struct ItemBall WhirlIslandB1FEscapeRope = {ESCAPE_ROPE, 1};
bool WhirlIslandB1FBoulder(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(StrengthBoulderScript)
    SCRIPT_END
}
const struct HiddenItem WhirlIslandB1FHiddenRareCandy = {RARE_CANDY, EVENT_WHIRL_ISLAND_B1F_HIDDEN_RARE_CANDY};
const struct HiddenItem WhirlIslandB1FHiddenUltraBall = {ULTRA_BALL, EVENT_WHIRL_ISLAND_B1F_HIDDEN_ULTRA_BALL};
const struct HiddenItem WhirlIslandB1FHiddenFullRestore = {FULL_RESTORE, EVENT_WHIRL_ISLAND_B1F_HIDDEN_FULL_RESTORE};
    //db(0, 0) // filler
