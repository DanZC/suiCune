#include "../constants.h"
#include "../util/scripting.h"
#include "TinTower9F.h"
//// EVENTS
enum {
    TINTOWER9F_POKE_BALL = 2,
};

const Script_fn_t TinTower9F_SceneScripts[] = {
    0,
};

const struct MapCallback TinTower9F_MapCallbacks[] = {
    0,
};

const struct MapScripts TinTower9F_MapScripts = {
    .scene_script_count = 0, // lengthof(TinTower9F_SceneScripts),
    .scene_scripts = TinTower9F_SceneScripts,

    .callback_count = 0, // lengthof(TinTower9F_MapCallbacks),
    .callbacks = TinTower9F_MapCallbacks,
};

static const struct CoordEvent TinTower9F_CoordEvents[] = {
    0,
};

static const struct BGEvent TinTower9F_BGEvents[] = {
    0,
};

static const struct WarpEventData TinTower9F_WarpEvents[] = {
    warp_event(12, 3, TIN_TOWER_8F, 2),
    warp_event(2, 5, TIN_TOWER_8F, 3),
    warp_event(12, 7, TIN_TOWER_8F, 4),
    warp_event(7, 9, TIN_TOWER_ROOF, 1),
    warp_event(16, 7, TIN_TOWER_7F, 5),
    warp_event(6, 13, TIN_TOWER_8F, 5),
    warp_event(8, 13, TIN_TOWER_8F, 6),
};

static const struct ObjEvent TinTower9F_ObjectEvents[] = {
    object_event(9, 1, SPRITE_POKE_BALL, SPRITEMOVEDATA_STILL, 0, 0, -1, -1, 0, OBJECTTYPE_ITEMBALL, 0, &TinTower9FHPUp, EVENT_TIN_TOWER_9F_HP_UP),
};

const struct MapEvents TinTower9F_MapEvents = {
    .warp_event_count = lengthof(TinTower9F_WarpEvents),
    .warp_events = TinTower9F_WarpEvents,

    .coord_event_count = 0, // lengthof(TinTower9F_CoordEvents),
    .coord_events = TinTower9F_CoordEvents,

    .bg_event_count = 0, // lengthof(TinTower9F_BGEvents),
    .bg_events = TinTower9F_BGEvents,

    .obj_event_count = lengthof(TinTower9F_ObjectEvents),
    .obj_events = TinTower9F_ObjectEvents,
};

//// CODE

const struct ItemBall TinTower9FHPUp = {HP_UP, 1};
const txt_cmd_s TinTower9FUnusedHoOhText[] = {
    text_start("HO-OH: Shaoooh!"
        t_done )
};
const txt_cmd_s TinTower9FUnusedLugiaText[] = {
    text_start("LUGIA: Gyaaan!"
        t_done )
    //db(0, 0) // filler
};
