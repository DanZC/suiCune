#include "../constants.h"
#include "../util/scripting.h"
#include "Route34IlexForestGate.h"
//// EVENTS
enum {
    ROUTE34ILEXFORESTGATE_TEACHER1 = 2,
    ROUTE34ILEXFORESTGATE_BUTTERFREE,
    ROUTE34ILEXFORESTGATE_LASS,
    ROUTE34ILEXFORESTGATE_TEACHER2,
};

const Script_fn_t Route34IlexForestGate_SceneScripts[] = {
    0,
};

const struct MapCallback Route34IlexForestGate_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, Route34IlexForestGate_MapScripts_IsForestRestless),
};

const struct MapScripts Route34IlexForestGate_MapScripts = {
    .scene_script_count = 0, // lengthof(Route34IlexForestGate_SceneScripts),
    .scene_scripts = Route34IlexForestGate_SceneScripts,

    .callback_count = lengthof(Route34IlexForestGate_MapCallbacks),
    .callbacks = Route34IlexForestGate_MapCallbacks,
};

static const struct CoordEvent Route34IlexForestGate_CoordEvents[] = {
    coord_event(4, 7, SCENE_DEFAULT, &Route34IlexForestGateCelebiEvent),
};

static const struct BGEvent Route34IlexForestGate_BGEvents[] = {
    0,
};

static const struct WarpEventData Route34IlexForestGate_WarpEvents[] = {
    warp_event(4, 0, ROUTE_34, 1),
    warp_event(5, 0, ROUTE_34, 2),
    warp_event(4, 7, ILEX_FOREST, 1),
    warp_event(5, 7, ILEX_FOREST, 1),
};

static const struct ObjEvent Route34IlexForestGate_ObjectEvents[] = {
    object_event(9, 3, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route34IlexForestGateTeacherScript, EVENT_ROUTE_34_ILEX_FOREST_GATE_TEACHER_BEHIND_COUNTER),
    object_event(9, 4, SPRITE_BUTTERFREE, SPRITEMOVEDATA_POKEMON, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &Route34IlexForestGateButterfreeScript, -1),
    object_event(3, 4, SPRITE_LASS, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &Route34IlexForestGateLassScript, EVENT_ROUTE_34_ILEX_FOREST_GATE_LASS),
    object_event(5, 7, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_BLUE, OBJECTTYPE_SCRIPT, 0, &Route34IlexForestGateTeacherScript, EVENT_ROUTE_34_ILEX_FOREST_GATE_TEACHER_IN_WALKWAY),
};

const struct MapEvents Route34IlexForestGate_MapEvents = {
    .warp_event_count = lengthof(Route34IlexForestGate_WarpEvents),
    .warp_events = Route34IlexForestGate_WarpEvents,

    .coord_event_count = lengthof(Route34IlexForestGate_CoordEvents),
    .coord_events = Route34IlexForestGate_CoordEvents,

    .bg_event_count = 0, // lengthof(Route34IlexForestGate_BGEvents),
    .bg_events = Route34IlexForestGate_BGEvents,

    .obj_event_count = lengthof(Route34IlexForestGate_ObjectEvents),
    .obj_events = Route34IlexForestGate_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Route34IlexForestGate.h"

bool Route34IlexForestGate_MapScripts_IsForestRestless(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOREST_IS_RESTLESS)
    iffalse_jump(Route34IlexForestGate_MapScripts_Normal)
    disappear(ROUTE34ILEXFORESTGATE_TEACHER1)
    appear(ROUTE34ILEXFORESTGATE_TEACHER2)
    s_endcallback
    SCRIPT_END
}
bool Route34IlexForestGate_MapScripts_Normal(script_s* s) {
    SCRIPT_BEGIN
    disappear(ROUTE34ILEXFORESTGATE_TEACHER2)
    appear(ROUTE34ILEXFORESTGATE_TEACHER1)
    s_endcallback
    SCRIPT_END
}
bool Route34IlexForestGateCelebiEvent(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOREST_IS_RESTLESS)
    iffalse(skip)
    showemote(EMOTE_SHOCK, ROUTE34ILEXFORESTGATE_TEACHER2, 20)
    turnobject(ROUTE34ILEXFORESTGATE_TEACHER2, LEFT)
    turnobject(PLAYER, RIGHT)
    follow(PLAYER, ROUTE34ILEXFORESTGATE_TEACHER2)
    applymovement(PLAYER, Route34IlexForestGateTeacherBlocksPlayerMovement)
    stopfollow
    turnobject(PLAYER, DOWN)
    opentext
    writetext(Route34IlexForestGateTeacher_ForestIsRestless)
    waitbutton
    closetext
    applymovement(ROUTE34ILEXFORESTGATE_TEACHER2, Route34IlexForestGateTeacherReturnsMovement)
skip:
    s_end
    SCRIPT_END
}
bool Route34IlexForestGateTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_FOREST_IS_RESTLESS)
    iftrue(ForestIsRestless)
    checkevent(EVENT_GOT_TM12_SWEET_SCENT)
    iftrue(GotSweetScent)
    writetext(Route34IlexForestGateTeacherText)
    promptbutton
    verbosegiveitem(TM_SWEET_SCENT, 1)
    iffalse(NoRoom)
    setevent(EVENT_GOT_TM12_SWEET_SCENT)
GotSweetScent:
    writetext(Route34IlexForestGateTeacher_GotSweetScent)
    waitbutton
NoRoom:
    closetext
    s_end
ForestIsRestless:
    writetext(Route34IlexForestGateTeacher_ForestIsRestless)
    promptbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route34IlexForestGateButterfreeScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(Route34IlexForestGateButterfreeText)
    playcry(BUTTERFREE)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Route34IlexForestGateLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Route34IlexForestGateLassText)
    SCRIPT_END
}
const uint8_t Route34IlexForestGateTeacherBlocksPlayerMovement[] = {
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t Route34IlexForestGateTeacherReturnsMovement[] = {
    step(DOWN),
    step(RIGHT),
    movement_step_end,
};
const txt_cmd_s Route34IlexForestGateTeacherText[] = {
    text_start("Oh, honey. You're"
        t_line "making a #DEX?"
        t_para "It must be hard if"
        t_line "#MON won't"
        t_para "appear. Try using"
        t_line "this TM."
        t_done )
};
const txt_cmd_s Route34IlexForestGateTeacher_GotSweetScent[] = {
    text_start("It's SWEET SCENT."
        t_para "Use it wherever"
        t_line "#MON appear."
        t_para "#MON will be"
        t_line "enticed by it."
        t_done )
};
const txt_cmd_s Route34IlexForestGateTeacher_ForestIsRestless[] = {
    text_start("Something's wrong"
        t_line "in ILEX FOREST…"
        t_para "You should stay"
        t_line "away right now."
        t_done )
};
const txt_cmd_s Route34IlexForestGateButterfreeText[] = {
    text_start("BUTTERFREE: Freeh!"
        t_done )
};
const txt_cmd_s Route34IlexForestGateLassText[] = {
    text_start("Did you see the"
        t_line "shrine honoring"
        t_cont "the protector?"
        t_para "It watches over"
        t_line "the FOREST from"
        t_cont "across time."
        t_para "I think that it"
        t_line "must be a grass-"
        t_cont "type #MON."
        t_done )
    //db(0, 0) // filler
};
