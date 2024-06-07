#include "../constants.h"
#include "../util/scripting.h"
#include "Route40BattleTowerGate.h"
//// EVENTS
enum {
    ROUTE40BATTLETOWERGATE_ROCKER = 2,
    ROUTE40BATTLETOWERGATE_TWIN,
};

const Script_fn_t Route40BattleTowerGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route40BattleTowerGate_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, Route40BattleTowerGate_MapScripts_ShowSailor),
};

const struct MapScripts Route40BattleTowerGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route40BattleTowerGate_SceneScripts),
    .scene_scripts = Route40BattleTowerGate_SceneScripts,

    .callback_count = lengthof(Route40BattleTowerGate_MapCallbacks),
    .callbacks = Route40BattleTowerGate_MapCallbacks,
};

static const struct CoordEvent Route40BattleTowerGate_CoordEvents[] = {
    0,
};

static const struct BGEvent Route40BattleTowerGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route40BattleTowerGate_WarpEvents[] = {
    warp_event(4, 7, ROUTE_40, 1),
    warp_event(5, 7, ROUTE_40, 1),
    warp_event(4, 0, BATTLE_TOWER_OUTSIDE, 1),
    warp_event(5, 0, BATTLE_TOWER_OUTSIDE, 2),
};

static const struct ObjEvent Route40BattleTowerGate_ObjectEvents[] = {
    object_event(3, 3, SPRITE_ROCKER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route40BattleTowerGateRockerScript, EVENT_BATTLE_TOWER_OUTSIDE_SAILOR),
    object_event(7, 5, SPRITE_TWIN, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route40BattleTowerGateTwinScript, -1),
};

const struct MapEvents Route40BattleTowerGate_MapEvents = {
    .warp_event_count = lengthof(Route40BattleTowerGate_WarpEvents),
    .warp_events = Route40BattleTowerGate_WarpEvents,

    .coord_event_count = 0, // lengthof(Route40BattleTowerGate_CoordEvents),
    .coord_events = Route40BattleTowerGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route40BattleTowerGate_BGEvents),
    .bg_events = Route40BattleTowerGate_BGEvents,

    .obj_event_count = lengthof(Route40BattleTowerGate_ObjectEvents),
    .obj_events = Route40BattleTowerGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route40BattleTowerGate.h"

bool Route40BattleTowerGate_MapScripts_ShowSailor(script_s* s) {
    SCRIPT_BEGIN
    clearevent(EVENT_BATTLE_TOWER_OUTSIDE_SAILOR)
    s_endcallback
    SCRIPT_END
}
bool Route40BattleTowerGateRockerScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route40BattleTowerGateRockerText)
    SCRIPT_END
}
bool Route40BattleTowerGateTwinScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route40BattleTowerGateTwinText)
    SCRIPT_END
}
const txt_cmd_s Route40BattleTowerGateUnusedText1[] = {
    text_start("Did you come to"
        t_line "see the BATTLE"
        t_cont "TOWER too?"
        t_para "But I guess you"
        t_line "can't go in yet."
        t_done )
};
const txt_cmd_s Route40BattleTowerGateUnusedText2[] = {
    text_start("BATTLE TOWER has"
        t_line "opened."
        t_para "I want to go, but"
        t_line "I haven't thought"
        t_para "up a cool line for"
        t_line "when I win."
        t_done )
};
const txt_cmd_s Route40BattleTowerGateRockerText[] = {
    text_start("Are you going to"
        t_line "the BATTLE TOWER?"
        t_para "This is a secret,"
        t_line "but if you win a"
        t_para "whole lot, you can"
        t_line "win special gifts."
        t_done )
};
const txt_cmd_s Route40BattleTowerGateUnusedText3[] = {
    text_start("I'm going to train"
        t_line "my #MON so I'll"
        t_para "be all ready for"
        t_line "the BATTLE TOWER."
        t_done )
};
const txt_cmd_s Route40BattleTowerGateTwinText[] = {
    text_start("The levels of the"
        t_line "#MON I want to"
        t_para "use are all"
        t_line "different."
        t_para "I have to go train"
        t_line "them now!"
        t_done )
    //db(0, 0) // filler
};
