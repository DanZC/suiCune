#include "../constants.h"
#include "../util/scripting.h"
#include "Route6SaffronGate.h"
//// EVENTS
enum {
    ROUTE6SAFFRONGATE_OFFICER = 2,
};

const Script_fn_t Route6SaffronGate_SceneScripts[] = {
    Route6SaffronGate_MapScripts_DummyScene,
};

const struct MapCallback Route6SaffronGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route6SaffronGate_MapScripts = {
    .scene_script_count = lengthof(Route6SaffronGate_SceneScripts),
    .scene_scripts = Route6SaffronGate_SceneScripts,

    .callback_count = 0, // lengthof(Route6SaffronGate_MapCallbacks),
    .callbacks = Route6SaffronGate_MapCallbacks,
};

static const struct CoordEvent Route6SaffronGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route6SaffronGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route6SaffronGate_WarpEvents[] = {
    warp_event(4, 0, SAFFRON_CITY, 12),
    warp_event(5, 0, SAFFRON_CITY, 13),
    warp_event(4, 7, ROUTE_6, 2),
    warp_event(5, 7, ROUTE_6, 2),
};

static const struct ObjEvent Route6SaffronGate_ObjectEvents[] = {
    object_event(0, 4, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route6SaffronGuardScript, -1),
};

const struct MapEvents Route6SaffronGate_MapEvents = {
    .warp_event_count = lengthof(Route6SaffronGate_WarpEvents),
    .warp_events = Route6SaffronGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route6SaffronGate_CoordEvents),
    .coord_events = Route6SaffronGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route6SaffronGate_BGEvents),
    .bg_events = Route6SaffronGate_BGEvents,

    .obj_event_count = lengthof(Route6SaffronGate_ObjectEvents),
    .obj_events = Route6SaffronGate_ObjectEvents,
};

//// CODE

bool Route6SaffronGate_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route6SaffronGuardScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedPart)
    writetext(Route6SaffronGuardWelcomeText)
    waitbutton
    closetext
    s_end
ReturnedPart:
    writetext(Route6SaffronGuardMagnetTrainText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s Route6SaffronGuardWelcomeText[] = {
    text_start("Welcome to SAFFRON"
        t_line "CITY, home of the"
        t_cont "MAGNET TRAIN!"
        t_para "…That's what I'd"
        t_line "normally say, but"
        t_para "the MAGNET TRAIN"
        t_line "isn't running now."
        t_para "It's not getting"
        t_line "any electricity"
        t_para "because there's"
        t_line "something wrong"
        t_para "with the POWER"
        t_line "PLANT."
        t_done )
};
const txt_cmd_s Route6SaffronGuardMagnetTrainText[] = {
    text_start("The MAGNET TRAIN"
        t_line "is the most famous"
        t_para "thing about SAF-"
        t_line "FRON."
        t_done )
    //db(0, 0) // filler
};
