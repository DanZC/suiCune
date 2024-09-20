#include "../constants.h"
#include "../util/scripting.h"
#include "Route17Route18Gate.h"
//// EVENTS
enum {
    ROUTE17ROUTE18GATE_OFFICER = 2,
};

const Script_fn_t Route17Route18Gate_SceneScripts[] = {
    Route17Route18Gate_MapScripts_DummyScene , //  SCENE_DEFAULT,
};

const struct MapCallback Route17Route18Gate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route17Route18Gate_MapScripts = {
    .scene_script_count = lengthof(Route17Route18Gate_SceneScripts),
    .scene_scripts = Route17Route18Gate_SceneScripts,

    .callback_count = 0, // lengthof(Route17Route18Gate_MapCallbacks),
    .callbacks = Route17Route18Gate_MapCallbacks,
};

static const struct CoordEvent Route17Route18Gate_CoordEvents[] = {
    coord_event(5, 4, SCENE_DEFAULT, &Route17Route18GateBicycleCheck),
    coord_event(5, 5, SCENE_DEFAULT, &Route17Route18GateBicycleCheck),
};

static const struct BGEvent Route17Route18Gate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route17Route18Gate_WarpEvents[] = {
    warp_event(0, 4, ROUTE_17, 1),
    warp_event(0, 5, ROUTE_17, 2),
    warp_event(9, 4, ROUTE_18, 1),
    warp_event(9, 5, ROUTE_18, 2),
};

static const struct ObjEvent Route17Route18Gate_ObjectEvents[] = {
    object_event(5, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route17Route18GateOfficerScript, -1),
};

const struct MapEvents Route17Route18Gate_MapEvents = {
    .warp_event_count = lengthof(Route17Route18Gate_WarpEvents),
    .warp_events = Route17Route18Gate_WarpEvents,

    .coord_event_count = lengthof(Route17Route18Gate_CoordEvents),
    .coord_events = Route17Route18Gate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route17Route18Gate_BGEvents),
    .bg_events = Route17Route18Gate_BGEvents,

    .obj_event_count = lengthof(Route17Route18Gate_ObjectEvents),
    .obj_events = Route17Route18Gate_ObjectEvents,
};

//// CODE

bool Route17Route18Gate_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route17Route18GateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route17Route18GateOfficerText)
    SCRIPT_END
}
bool Route17Route18GateBicycleCheck(script_s* s) {
    SCRIPT_BEGIN
    checkitem(BICYCLE)
    iffalse(NoBicycle)
    s_end
NoBicycle:
    showemote(EMOTE_SHOCK, ROUTE17ROUTE18GATE_OFFICER, 15)
    turnobject(PLAYER, UP)
    opentext
    writetext(Route17Route18GateCannotPassText)
    waitbutton
    closetext
    applymovement(PLAYER, Route17Route18GateCannotPassMovement)
    s_end
    SCRIPT_END
}
const uint8_t Route17Route18GateCannotPassMovement[] = {
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const txt_cmd_s Route17Route18GateOfficerText[] = {
    text_start("CYCLING ROAD"
        t_line "Uphill Starts Here"
        t_done )
};
const txt_cmd_s Route17Route18GateCannotPassText[] = {
    text_start("Hang on! Don't you"
        t_line "have a BICYCLE?"
        t_para "The CYCLING ROAD"
        t_line "is beyond here."
        t_para "You have to have a"
        t_line "BICYCLE to go on."
        t_done )
    //db(0, 0) // filler
};
