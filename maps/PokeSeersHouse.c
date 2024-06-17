#include "../constants.h"
#include "../util/scripting.h"
#include "PokeSeersHouse.h"
//// EVENTS
enum {
    POKESEERSHOUSE_GRANNY = 2,
};

const Script_fn_t PokeSeersHouse_SceneScripts[] = {
    0,
};

const struct MapCallback PokeSeersHouse_MapCallbacks[] = {
    0,
};

const struct MapScripts PokeSeersHouse_MapScripts = {
    .scene_script_count = 0, // lengthof(PokeSeersHouse_SceneScripts),
    .scene_scripts = PokeSeersHouse_SceneScripts,

    .callback_count = 0, // lengthof(PokeSeersHouse_MapCallbacks),
    .callbacks = PokeSeersHouse_MapCallbacks,
};

static const struct CoordEvent PokeSeersHouse_CoordEvents[] = {
    0,
};

static const struct BGEvent PokeSeersHouse_BGEvents[] = {
    0,
};

static const struct WarpEventData PokeSeersHouse_WarpEvents[] = {
    warp_event(2, 7, CIANWOOD_CITY, 7),
    warp_event(3, 7, CIANWOOD_CITY, 7),
};

static const struct ObjEvent PokeSeersHouse_ObjectEvents[] = {
    object_event(2, 3, SPRITE_GRANNY, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &SeerScript, -1),
};

const struct MapEvents PokeSeersHouse_MapEvents = {
    .warp_event_count = lengthof(PokeSeersHouse_WarpEvents),
    .warp_events = PokeSeersHouse_WarpEvents,

    .coord_event_count = 0, // lengthof(PokeSeersHouse_CoordEvents),
    .coord_events = PokeSeersHouse_CoordEvents,

    .bg_event_count = 0, // lengthof(PokeSeersHouse_BGEvents),
    .bg_events = PokeSeersHouse_BGEvents,

    .obj_event_count = lengthof(PokeSeersHouse_ObjectEvents),
    .obj_events = PokeSeersHouse_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "PokeSeersHouse.h"

bool SeerScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    special(PokeSeer)
    waitbutton
    closetext
    s_end
    //db(0, 0) // filler
    SCRIPT_END
}
