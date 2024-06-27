#include "../constants.h"
#include "../util/scripting.h"
#include "BlackthornEmysHouse.h"
//// EVENTS
enum {
    BLACKTHORNEMYSHOUSE_EMY = 2,
};

const Script_fn_t BlackthornEmysHouse_SceneScripts[] = {
    0,
};

const struct MapCallback BlackthornEmysHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts BlackthornEmysHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(BlackthornEmysHouse_SceneScripts),
    .scene_scripts = BlackthornEmysHouse_SceneScripts,

    .callback_count = 0, // lengthof(BlackthornEmysHouse_MapCallbacks),
    .callbacks = BlackthornEmysHouse_MapCallbacks,
};

static const struct CoordEvent BlackthornEmysHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent BlackthornEmysHouse_BGEvents[] = {
    bg_event(0, 1, BGEVENT_READ, &EmysHouseBookshelf),
    bg_event(1, 1, BGEVENT_READ, &EmysHouseBookshelf),
};

static const struct WarpEventData BlackthornEmysHouse_WarpEvents[] = {
    warp_event(2, 7, BLACKTHORN_CITY, 3),
    warp_event(3, 7, BLACKTHORN_CITY, 3),
};

static const struct ObjEvent BlackthornEmysHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_LASS, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Emy, -1),
};

const struct MapEvents BlackthornEmysHouse_MapEvents = {
    .warp_event_count = lengthof(BlackthornEmysHouse_WarpEvents),
    .warp_events = BlackthornEmysHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(BlackthornEmysHouse_CoordEvents),
    .coord_events = BlackthornEmysHouse_CoordEvents,

    .bg_event_count = lengthof(BlackthornEmysHouse_BGEvents),
    .bg_events = BlackthornEmysHouse_BGEvents,

    .obj_event_count = lengthof(BlackthornEmysHouse_ObjectEvents),
    .obj_events = BlackthornEmysHouse_ObjectEvents,
};

//// CODE

bool Emy(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    trade(NPC_TRADE_EMY)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EmysHouseBookshelf(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(MagazineBookshelfScript)
    //db(0, 0) // filler
    SCRIPT_END
}
