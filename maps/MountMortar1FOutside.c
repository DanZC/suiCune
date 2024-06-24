#include "../constants.h"
#include "../util/scripting.h"
#include "MountMortar1FOutside.h"
//// EVENTS
enum {
    MOUNTMORTAR1FOUTSIDE_POKE_BALL1 = 2,
    MOUNTMORTAR1FOUTSIDE_POKE_BALL2,
};

const Script_fn_t MountMortar1FOutside_SceneScripts[] = {
    0,
};

const struct MapCallback MountMortar1FOutside_MapCallbacks[] = {
    0,
};

const struct MapScripts MountMortar1FOutside_MapScripts = {
    .scene_script_count = 0, // lengthof(MountMortar1FOutside_SceneScripts),
    .scene_scripts = MountMortar1FOutside_SceneScripts,

    .callback_count = 0, // lengthof(MountMortar1FOutside_MapCallbacks),
    .callbacks = MountMortar1FOutside_MapCallbacks,
};

static const struct CoordEvent MountMortar1FOutside_CoordEvents[] = {
    0,
};

static const struct BGEvent MountMortar1FOutside_BGEvents[] = {
    bg_event(25, 22, BGEVENT_ITEM, &MountMortar1FOutsideHiddenHyperPotion),
};

static const struct WarpEventData MountMortar1FOutside_WarpEvents[] = {
    warp_event(3, 33, ROUTE_42, 3),
    warp_event(17, 33, ROUTE_42, 4),
    warp_event(37, 33, ROUTE_42, 5),
    warp_event(17, 5, MOUNT_MORTAR_2F_INSIDE, 1),
    warp_event(11, 21, MOUNT_MORTAR_1F_INSIDE, 1),
    warp_event(29, 21, MOUNT_MORTAR_1F_INSIDE, 2),
    warp_event(17, 29, MOUNT_MORTAR_B1F, 2),
    warp_event(7, 13, MOUNT_MORTAR_1F_INSIDE, 3),
    warp_event(33, 13, MOUNT_MORTAR_1F_INSIDE, 4),
};

static const struct ObjEvent MountMortar1FOutside_ObjectEvents[] = {
    object_event(13, 15, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar1FOutsideEther, EVENT_MOUNT_MORTAR_1F_OUTSIDE_ETHER),
    object_event(31, 18, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &MountMortar1FOutsideRevive, EVENT_MOUNT_MORTAR_1F_OUTSIDE_REVIVE),
};

const struct MapEvents MountMortar1FOutside_MapEvents = {
    .warp_event_count = lengthof(MountMortar1FOutside_WarpEvents),
    .warp_events = MountMortar1FOutside_WarpEvents,

    .coord_event_count = 0, // lengthof(MountMortar1FOutside_CoordEvents),
    .coord_events = MountMortar1FOutside_CoordEvents,

    .bg_event_count = lengthof(MountMortar1FOutside_BGEvents),
    .bg_events = MountMortar1FOutside_BGEvents,

    .obj_event_count = lengthof(MountMortar1FOutside_ObjectEvents),
    .obj_events = MountMortar1FOutside_ObjectEvents,
};

//// CODE

const struct ItemBall MountMortar1FOutsideEther = {ETHER, 1};
const struct ItemBall MountMortar1FOutsideRevive = {REVIVE, 1};
const struct HiddenItem MountMortar1FOutsideHiddenHyperPotion = {HYPER_POTION, EVENT_MOUNT_MORTAR_1F_OUTSIDE_HIDDEN_HYPER_POTION};
    //db(0, 0) // filler
