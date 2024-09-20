#include "../constants.h"
#include "../util/scripting.h"
#include "Route16Gate.h"
//// EVENTS
enum {
    ROUTE16GATE_OFFICER = 2,
};

const Script_fn_t Route16Gate_SceneScripts[] = {
    Route16Gate_MapScripts_DummyScene , //  SCENE_DEFAULT,
};

const struct MapCallback Route16Gate_MapCallbacks[] = {
    0,
};

const struct MapScripts Route16Gate_MapScripts = {
    .scene_script_count = lengthof(Route16Gate_SceneScripts),
    .scene_scripts = Route16Gate_SceneScripts,

    .callback_count = 0, // lengthof(Route16Gate_MapCallbacks),
    .callbacks = Route16Gate_MapCallbacks,
};

static const struct CoordEvent Route16Gate_CoordEvents[] = {
    coord_event(5, 4, SCENE_DEFAULT, &Route16GateBicycleCheck),
    coord_event(5, 5, SCENE_DEFAULT, &Route16GateBicycleCheck),
};

static const struct BGEvent Route16Gate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route16Gate_WarpEvents[] = {
    warp_event(0, 4, ROUTE_16, 4),
    warp_event(0, 5, ROUTE_16, 5),
    warp_event(9, 4, ROUTE_16, 2),
    warp_event(9, 5, ROUTE_16, 3),
};

static const struct ObjEvent Route16Gate_ObjectEvents[] = {
    object_event(5, 2, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route16GateOfficerScript, -1),
};

const struct MapEvents Route16Gate_MapEvents = {
    .warp_event_count = lengthof(Route16Gate_WarpEvents),
    .warp_events = Route16Gate_WarpEvents,

    .coord_event_count = lengthof(Route16Gate_CoordEvents),
    .coord_events = Route16Gate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route16Gate_BGEvents),
    .bg_events = Route16Gate_BGEvents,

    .obj_event_count = lengthof(Route16Gate_ObjectEvents),
    .obj_events = Route16Gate_ObjectEvents,
};

//// CODE

bool Route16Gate_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Route16GateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route16GateOfficerText)
    SCRIPT_END
}
bool Route16GateBicycleCheck(script_s* s) {
    SCRIPT_BEGIN
    checkitem(BICYCLE)
    iffalse(NoBicycle)
    s_end
NoBicycle:
    showemote(EMOTE_SHOCK, ROUTE16GATE_OFFICER, 15)
    turnobject(PLAYER, UP)
    opentext
    writetext(Route16GateCannotPassText)
    waitbutton
    closetext
    applymovement(PLAYER, Route16GateCannotPassMovement)
    s_end
    SCRIPT_END
}
const uint8_t Route16GateCannotPassMovement[] = {
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const txt_cmd_s Route16GateOfficerText[] = {
    text_start("CYCLING ROAD"
        t_line "starts here."
        t_para "It's all downhill,"
        t_line "so it's totally"
        t_cont "exhilarating."
        t_para "It's a great sort"
        t_line "of feeling that"
        t_para "you can't get from"
        t_line "a ship or train."
        t_done )
};
const txt_cmd_s Route16GateCannotPassText[] = {
    text_start("Hey! Whoa! Stop!"
        t_para "You can't go out"
        t_line "on the CYCLING"
        t_para "ROAD without a"
        t_line "BICYCLE."
        t_done )
    //db(0, 0) // filler
};
