#include "../constants.h"
#include "../util/scripting.h"
#include "VictoryRoadGate.h"
//// EVENTS
enum {
    VICTORYROADGATE_OFFICER = 2,
    VICTORYROADGATE_BLACK_BELT1,
    VICTORYROADGATE_BLACK_BELT2,
};

const Script_fn_t VictoryRoadGate_SceneScripts[] = {
    VictoryRoadGate_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    VictoryRoadGate_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback VictoryRoadGate_MapCallbacks[] = {
    0,
};

const struct MapScripts VictoryRoadGate_MapScripts = {
    .scene_script_count = lengthof(VictoryRoadGate_SceneScripts),
    .scene_scripts = VictoryRoadGate_SceneScripts,

    .callback_count = 0, // lengthof(VictoryRoadGate_MapCallbacks),
    .callbacks = VictoryRoadGate_MapCallbacks,
};

static const struct CoordEvent VictoryRoadGate_CoordEvents[] = {
    coord_event(10, 11, SCENE_DEFAULT, &VictoryRoadGateBadgeCheckScene),
};

static const struct BGEvent VictoryRoadGate_BGEvents[] = {
    0,
};

static const struct WarpEventData VictoryRoadGate_WarpEvents[] = {
    warp_event(17, 7, ROUTE_22, 1),
    warp_event(18, 7, ROUTE_22, 1),
    warp_event(9, 17, ROUTE_26, 1),
    warp_event(10, 17, ROUTE_26, 1),
    warp_event(9, 0, VICTORY_ROAD, 1),
    warp_event(10, 0, VICTORY_ROAD, 1),
    warp_event(1, 7, ROUTE_28, 2),
    warp_event(2, 7, ROUTE_28, 2),
};

static const struct ObjEvent VictoryRoadGate_ObjectEvents[] = {
    object_event(8, 11, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VictoryRoadGateOfficerScript, -1),
    object_event(7, 5, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VictoryRoadGateLeftBlackBeltScript, EVENT_OPENED_MT_SILVER),
    object_event(12, 5, SPRITE_BLACK_BELT, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VictoryRoadGateRightBlackBeltScript, EVENT_FOUGHT_SNORLAX),
};

const struct MapEvents VictoryRoadGate_MapEvents = {
    .warp_event_count = lengthof(VictoryRoadGate_WarpEvents),
    .warp_events = VictoryRoadGate_WarpEvents,

    .coord_event_count = lengthof(VictoryRoadGate_CoordEvents),
    .coord_events = VictoryRoadGate_CoordEvents,

    .bg_event_count = 0, // lengthof(VictoryRoadGate_BGEvents),
    .bg_events = VictoryRoadGate_BGEvents,

    .obj_event_count = lengthof(VictoryRoadGate_ObjectEvents),
    .obj_events = VictoryRoadGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "VictoryRoadGate.h"

bool VictoryRoadGate_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool VictoryRoadGate_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool VictoryRoadGateBadgeCheckScene(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, LEFT)
    sjump(VictoryRoadGateBadgeCheckScript)
    SCRIPT_END
}
bool VictoryRoadGateOfficerScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    SCRIPT_FALLTHROUGH(VictoryRoadGateBadgeCheckScript)
}
bool VictoryRoadGateBadgeCheckScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(VictoryRoadGateOfficerText)
    promptbutton
    readvar(VAR_BADGES)
    ifgreater(NUM_JOHTO_BADGES - 1, AllEightBadges)
    writetext(VictoryRoadGateNotEnoughBadgesText)
    waitbutton
    closetext
    applymovement(PLAYER, VictoryRoadGateStepDownMovement)
    s_end
AllEightBadges:
    writetext(VictoryRoadGateEightBadgesText)
    waitbutton
    closetext
    setscene(SCENE_FINISHED)
    s_end
    SCRIPT_END
}
bool VictoryRoadGateLeftBlackBeltScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VictoryRoadGateLeftBlackBeltText)
    SCRIPT_END
}
bool VictoryRoadGateRightBlackBeltScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(VictoryRoadGateRightBlackBeltText)
    SCRIPT_END
}
const uint8_t VictoryRoadGateStepDownMovement[] = {
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s VictoryRoadGateOfficerText[] = {
    text_start("Only trainers who"
        t_line "have proven them-"
        t_cont "selves may pass."
        t_done )
};
const txt_cmd_s VictoryRoadGateNotEnoughBadgesText[] = {
    text_start("You don't have all"
        t_line "the GYM BADGES of"
        t_cont "JOHTO."
        t_para "I'm sorry, but I"
        t_line "can't let you go"
        t_cont "through."
        t_done )
};
const txt_cmd_s VictoryRoadGateEightBadgesText[] = {
    text_start("Oh! The eight"
        t_line "BADGES of JOHTO!"
        t_para "Please, go right"
        t_line "on through!"
        t_done )
};
const txt_cmd_s VictoryRoadGateLeftBlackBeltText[] = {
    text_start("This way leads to"
        t_line "MT.SILVER."
        t_para "You'll see scary-"
        t_line "strong #MON out"
        t_cont "there."
        t_done )
};
const txt_cmd_s VictoryRoadGateRightBlackBeltText[] = {
    text_start("Off to the #MON"
        t_line "LEAGUE, are you?"
        t_para "The ELITE FOUR are"
        t_line "so strong it's"
        t_para "scary, and they're"
        t_line "ready for you!"
        t_done )
    //db(0, 0) // filler
};
