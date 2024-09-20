#include "../constants.h"
#include "../util/scripting.h"
#include "SafariZoneMainOffice.h"
//// EVENTS
const Script_fn_t SafariZoneMainOffice_SceneScripts[] = {
    0,
};

const struct MapCallback SafariZoneMainOffice_MapCallbacks[] = {
    0,
};

const struct MapScripts SafariZoneMainOffice_MapScripts = {
    .scene_script_count = 0, // lengthof(SafariZoneMainOffice_SceneScripts),
    .scene_scripts = SafariZoneMainOffice_SceneScripts,

    .callback_count = 0, // lengthof(SafariZoneMainOffice_MapCallbacks),
    .callbacks = SafariZoneMainOffice_MapCallbacks,
};

static const struct CoordEvent SafariZoneMainOffice_CoordEvents[] = {
    0,
};

static const struct BGEvent SafariZoneMainOffice_BGEvents[] = {
    0,
};

static const struct WarpEventData SafariZoneMainOffice_WarpEvents[] = {
    warp_event(2, 7, FUCHSIA_CITY, 2),
    warp_event(3, 7, FUCHSIA_CITY, 2),
};

static const struct ObjEvent SafariZoneMainOffice_ObjectEvents[] = {
    0,
};

const struct MapEvents SafariZoneMainOffice_MapEvents = {
    .warp_event_count = lengthof(SafariZoneMainOffice_WarpEvents),
    .warp_events = SafariZoneMainOffice_WarpEvents,

    .coord_event_count = 0, // lengthof(SafariZoneMainOffice_CoordEvents),
    .coord_events = SafariZoneMainOffice_CoordEvents,

    .bg_event_count = 0, // lengthof(SafariZoneMainOffice_BGEvents),
    .bg_events = SafariZoneMainOffice_BGEvents,

    .obj_event_count = 0, // lengthof(SafariZoneMainOffice_ObjectEvents),
    .obj_events = SafariZoneMainOffice_ObjectEvents,
};

//// CODE

    //db(0, 0) // filler
