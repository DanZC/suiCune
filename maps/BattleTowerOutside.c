#include "../constants.h"
#include "../util/scripting.h"
#include "BattleTowerOutside.h"
//// EVENTS
enum {
    BATTLETOWEROUTSIDE_STANDING_YOUNGSTER = 2,
    BATTLETOWEROUTSIDE_BEAUTY,
    BATTLETOWEROUTSIDE_SAILOR,
    BATTLETOWEROUTSIDE_LASS,
};

const Script_fn_t BattleTowerOutside_SceneScripts[] = {
    0,
};

const struct MapCallback BattleTowerOutside_MapCallbacks[] = {
    map_callback(MAPCALLBACK_TILES, BattleTowerOutside_MapScripts_Callback1),
    map_callback(MAPCALLBACK_OBJECTS, BattleTowerOutside_MapScripts_Callback2),
};

const struct MapScripts BattleTowerOutside_MapScripts = {
    .scene_script_count = 0, // lengthof(BattleTowerOutside_SceneScripts),
    .scene_scripts = BattleTowerOutside_SceneScripts,

    .callback_count = lengthof(BattleTowerOutside_MapCallbacks),
    .callbacks = BattleTowerOutside_MapCallbacks,
};

static const struct CoordEvent BattleTowerOutside_CoordEvents[] = {
    0,
};

static const struct BGEvent BattleTowerOutside_BGEvents[] = {
    bg_event(10, 10, BGEVENT_READ, &BattleTowerOutsideSign),
};

static const struct WarpEventData BattleTowerOutside_WarpEvents[] = {
    warp_event(8, 21, ROUTE_40_BATTLE_TOWER_GATE, 3),
    warp_event(9, 21, ROUTE_40_BATTLE_TOWER_GATE, 4),
    warp_event(8, 9, BATTLE_TOWER_1F, 1),
    warp_event(9, 9, BATTLE_TOWER_1F, 2),
};

static const struct ObjEvent BattleTowerOutside_ObjectEvents[] = {
    object_event(6, 12, SPRITE_STANDING_YOUNGSTER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &BattleTowerOutsideYoungsterScript, -1),
    object_event(13, 11, SPRITE_BEAUTY, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &BattleTowerOutsideBeautyScript, -1),
    object_event(12, 18, SPRITE_SAILOR, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &BattleTowerOutsideSailorScript, EVENT_BATTLE_TOWER_OUTSIDE_SAILOR),
    object_event(12, 24, SPRITE_LASS, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, -1),
};

const struct MapEvents BattleTowerOutside_MapEvents = {
    .warp_event_count = lengthof(BattleTowerOutside_WarpEvents),
    .warp_events = BattleTowerOutside_WarpEvents,

    .coord_event_count = 0, // lengthof(BattleTowerOutside_CoordEvents),
    .coord_events = BattleTowerOutside_CoordEvents,

    .bg_event_count = lengthof(BattleTowerOutside_BGEvents),
    .bg_events = BattleTowerOutside_BGEvents,

    .obj_event_count = lengthof(BattleTowerOutside_ObjectEvents),
    .obj_events = BattleTowerOutside_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BattleTowerOutside.h"

bool BattleTowerOutside_MapScripts_Callback1(script_s* s) {
    SCRIPT_BEGIN
    s_endcallback
    SCRIPT_END
}
bool BattleTowerOutside_MapScripts_Callback2(script_s* s) {
    SCRIPT_BEGIN
    clearevent(EVENT_BATTLE_TOWER_OUTSIDE_SAILOR)
    s_endcallback
    SCRIPT_END
}
bool BattleTowerOutsideYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BattleTowerOutsideYoungsterText)
    SCRIPT_END
}
bool BattleTowerOutsideBeautyScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BattleTowerOutsideBeautyText)
    SCRIPT_END
}
bool BattleTowerOutsideSailorScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(BattleTowerOutsideSailorText)
    SCRIPT_END
}
bool BattleTowerOutsideSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(BattleTowerOutsideSignText)
    SCRIPT_END
}
const txt_cmd_s BattleTowerOutsideYoungsterText_NotYetOpen[] = {
    text_start("Wow, the BATTLE"
        t_line "TOWER is huge! My"
        t_para "neck is tired from"
        t_line "looking up at it."
        t_done )
};
const txt_cmd_s BattleTowerOutsideYoungsterText_Mobile[] = {
    text_start("Wow, the BATTLE"
        t_line "TOWER is huge!"
        t_para "Since there are a"
        t_line "whole bunch of"
        t_para "trainers inside,"
        t_line "there must also be"
        t_para "a wide variety of"
        t_line "#MON."
        t_done )
};
const txt_cmd_s BattleTowerOutsideYoungsterText[] = {
    text_start("Wow, the BATTLE"
        t_line "TOWER is huge!"
        t_para "There must be many"
        t_line "kinds of #MON"
        t_cont "in there!"
        t_done )
};
const txt_cmd_s BattleTowerOutsideBeautyText_NotYetOpen[] = {
    text_start("What on earth do"
        t_line "they do here?"
        t_para "If the name says"
        t_line "anything, I guess"
        t_para "it must be for"
        t_line "#MON battles."
        t_done )
};
const txt_cmd_s BattleTowerOutsideBeautyText[] = {
    text_start("You can use only"
        t_line "three #MON."
        t_para "It's so hard to"
        t_line "decide which three"
        t_para "should go into"
        t_line "battle…"
        t_done )
};
const txt_cmd_s BattleTowerOutsideSailorText_Mobile[] = {
    text_start("Ehehehe…"
        t_line "I sneaked out of"
        t_cont "work to come here."
        t_para "I'm never giving"
        t_line "up until I become"
        t_cont "a LEADER!"
        t_done )
};
const txt_cmd_s BattleTowerOutsideSailorText[] = {
    text_start("Hehehe, I snuck"
        t_line "out from work."
        t_para "I can't bail out"
        t_line "until I've won!"
        t_para "I have to win it"
        t_line "all. That I must!"
        t_done )
};
const txt_cmd_s BattleTowerOutsideSignText_NotYetOpen[] = {
// originally shown when the Battle Tower was closed
    text_start("BATTLE TOWER"
        t_done )
};
const txt_cmd_s BattleTowerOutsideSignText[] = {
    text_start("BATTLE TOWER"
        t_para "Take the Ultimate"
        t_line "Trainer Challenge!"
        t_done )
};
const txt_cmd_s BattleTowerOutsideText_DoorsClosed[] = {
// originally shown when the Battle Tower was closed
    text_start("The BATTLE TOWER's"
        t_line "doors are closed…"
        t_done )
};
const txt_cmd_s BattleTowerOutsideText_DoorsOpen[] = {
// originally shown after the Battle Tower opened
    text_start("It's open!"
        t_done )
    //db(0, 0) // filler
};
