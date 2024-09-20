#include "../constants.h"
#include "../util/scripting.h"
#include "Route7SaffronGate.h"
//// EVENTS
enum {
    ROUTE7SAFFRONGATE_OFFICER = 2,
};

const Script_fn_t Route7SaffronGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route7SaffronGate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route7SaffronGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route7SaffronGate_SceneScripts),
    .scene_scripts = Route7SaffronGate_SceneScripts,

    .callback_count = 0, // lengthof(Route7SaffronGate_MapCallbacks),
    .callbacks = Route7SaffronGate_MapCallbacks,
};

static const struct CoordEvent Route7SaffronGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route7SaffronGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route7SaffronGate_WarpEvents[] = {
    warp_event(0, 4, ROUTE_7, 1),
    warp_event(0, 5, ROUTE_7, 2),
    warp_event(9, 4, SAFFRON_CITY, 10),
    warp_event(9, 5, SAFFRON_CITY, 11),
};

static const struct ObjEvent Route7SaffronGate_ObjectEvents[] = {
    object_event(5, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route7SaffronGuardScript, -1),
};

const struct MapEvents Route7SaffronGate_MapEvents = {
    .warp_event_count = lengthof(Route7SaffronGate_WarpEvents),
    .warp_events = Route7SaffronGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route7SaffronGate_CoordEvents),
    .coord_events = Route7SaffronGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route7SaffronGate_BGEvents),
    .bg_events = Route7SaffronGate_BGEvents,

    .obj_event_count = lengthof(Route7SaffronGate_ObjectEvents),
    .obj_events = Route7SaffronGate_ObjectEvents,
};

//// CODE

bool Route7SaffronGuardScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedPart)
    writetext(Route7SaffronGuardPowerPlantText)
    waitbutton
    closetext
    s_end
ReturnedPart:
    writetext(Route7SaffronGuardSeriousText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s Route7SaffronGuardPowerPlantText[] = {
    text_start("Did you hear about"
        t_line "the accident at"
        t_cont "the POWER PLANT?"
        t_para "It's located in"
        t_line "the East, close to"
        t_cont "LAVENDER TOWN."
        t_done )
};
const txt_cmd_s Route7SaffronGuardSeriousText[] = {
    text_start("I take my GUARD"
        t_line "job seriously."
        t_para "Hey! You have a"
        t_line "#DEX."
        t_para "OK. You can go"
        t_line "through."
        t_done )
    //db(0, 0) // filler
};
