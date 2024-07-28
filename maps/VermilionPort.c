#include "../constants.h"
#include "../util/scripting.h"
#include "VermilionPort.h"
//// EVENTS
enum {
    VERMILIONPORT_SAILOR1 = 2,
    VERMILIONPORT_SAILOR2,
    VERMILIONPORT_SUPER_NERD,
};

const Script_fn_t VermilionPort_SceneScripts[] = {
    VermilionPort_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    VermilionPort_MapScripts_LeaveFastShip , //  SCENE_VERMILIONPORT_LEAVE_SHIP,
};

const struct MapCallback VermilionPort_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, VermilionPort_MapScripts_FlyPoint),
};

const struct MapScripts VermilionPort_MapScripts = {
    .scene_script_count = lengthof(VermilionPort_SceneScripts),
    .scene_scripts = VermilionPort_SceneScripts,

    .callback_count = lengthof(VermilionPort_MapCallbacks),
    .callbacks = VermilionPort_MapCallbacks,
};

static const struct CoordEvent VermilionPort_CoordEvents[] = {
    coord_event(7, 11, SCENE_DEFAULT, &VermilionPortWalkUpToShipScript),
};

static const struct BGEvent VermilionPort_BGEvents[] = {
    bg_event(16, 13, BGEVENT_ITEM, &VermilionPortHiddenIron),
};

static const struct WarpEventData VermilionPort_WarpEvents[] = {
    warp_event(9, 5, VERMILION_PORT_PASSAGE, 5),
    warp_event(7, 17, FAST_SHIP_1F, 1),
};

static const struct ObjEvent VermilionPort_ObjectEvents[] = {
    object_event(7, 17, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VermilionPortSailorAtGangwayScript, EVENT_VERMILION_PORT_SAILOR_AT_GANGWAY),
    object_event(6, 11, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VermilionPortSailorScript, -1),
    object_event(11, 11, SPRITE_SUPER_NERD, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &VermilionPortSuperNerdScript, -1),
};

const struct MapEvents VermilionPort_MapEvents = {
    .warp_event_count = lengthof(VermilionPort_WarpEvents),
    .warp_events = VermilionPort_WarpEvents,

    .coord_event_count = lengthof(VermilionPort_CoordEvents),
    .coord_events = VermilionPort_CoordEvents,

    .bg_event_count = lengthof(VermilionPort_BGEvents),
    .bg_events = VermilionPort_BGEvents,

    .obj_event_count = lengthof(VermilionPort_ObjectEvents),
    .obj_events = VermilionPort_ObjectEvents,
};

//// CODE

bool VermilionPort_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool VermilionPort_MapScripts_LeaveFastShip(script_s* s) {
    SCRIPT_BEGIN
    sdefer(VermilionPort_MapScripts_LeaveFastShipScript);
    s_end
    SCRIPT_END
}
bool VermilionPort_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_VERMILION)
    s_endcallback
    SCRIPT_END
}
bool VermilionPort_MapScripts_LeaveFastShipScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, VermilionPortLeaveFastShipMovement)
    appear(VERMILIONPORT_SAILOR1)
    setscene(SCENE_DEFAULT)
    setevent(EVENT_FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN_TWIN_1)
    setevent(EVENT_FAST_SHIP_CABINS_SE_SSE_GENTLEMAN)
    setevent(EVENT_FAST_SHIP_PASSENGERS_FIRST_TRIP)
    clearevent(EVENT_OLIVINE_PORT_PASSAGE_POKEFAN_M)
    setevent(EVENT_FAST_SHIP_FIRST_TIME)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    blackoutmod(VERMILION_CITY)
    s_end
    SCRIPT_END
}
bool VermilionPortSailorAtGangwayScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue_jump(VermilionPortAlreadyRodeScript)
    writetext(VermilionPortDepartingText)
    waitbutton
    closetext
    turnobject(VERMILIONPORT_SAILOR1, DOWN)
    pause(10)
    playsound(SFX_EXIT_BUILDING)
    disappear(VERMILIONPORT_SAILOR1)
    waitsfx
    applymovement(PLAYER, VermilionPortEnterFastShipMovement)
    playsound(SFX_EXIT_BUILDING)
    special(FadeOutPalettes)
    waitsfx
    setevent(EVENT_FAST_SHIP_PASSENGERS_EASTBOUND)
    clearevent(EVENT_FAST_SHIP_PASSENGERS_WESTBOUND)
    clearevent(EVENT_BEAT_POKEMANIAC_ETHAN)
    clearevent(EVENT_BEAT_BURGLAR_COREY)
    clearevent(EVENT_BEAT_BUG_CATCHER_KEN)
    clearevent(EVENT_BEAT_GUITARIST_CLYDE)
    clearevent(EVENT_BEAT_POKEFANM_JEREMY)
    clearevent(EVENT_BEAT_POKEFANF_GEORGIA)
    clearevent(EVENT_BEAT_SAILOR_KENNETH)
    clearevent(EVENT_BEAT_TEACHER_SHIRLEY)
    clearevent(EVENT_BEAT_SCHOOLBOY_NATE)
    clearevent(EVENT_BEAT_SCHOOLBOY_RICKY)
    setevent(EVENT_FAST_SHIP_DESTINATION_OLIVINE)
    appear(VERMILIONPORT_SAILOR1)
    setmapscene(FAST_SHIP_1F, SCENE_FASTSHIP1F_ENTER_SHIP)
    warp(FAST_SHIP_1F, 25, 1)
    s_end
    SCRIPT_END
}
bool VermilionPortAlreadyRodeScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(VermilionPortCantBoardText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool VermilionPortWalkUpToShipScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(VERMILIONPORT_SAILOR2, RIGHT)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue(skip)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iftrue(skip)
    turnobject(PLAYER, LEFT)
    opentext
    readvar(VAR_WEEKDAY)
    ifequal(MONDAY, NextShipWednesday)
    ifequal(TUESDAY, NextShipWednesday)
    ifequal(THURSDAY, NextShipSunday)
    ifequal(FRIDAY, NextShipSunday)
    ifequal(SATURDAY, NextShipSunday)
    writetext(VermilionPortAskBoardingText)
    yesorno
    iffalse_jump(VermilionPortNotRidingMoveAwayScript)
    writetext(VermilionPortAskTicketText)
    promptbutton
    checkitem(S_S_TICKET)
    iffalse(NoTicket)
    writetext(VermilionPortSSTicketText)
    waitbutton
    closetext
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    applymovement(PLAYER, VermilionPortApproachFastShipMovement)
    sjump(VermilionPortSailorAtGangwayScript)
NoTicket:
    writetext(VermilionPortNoTicketText)
    waitbutton
    closetext
    applymovement(PLAYER, VermilionPortCannotEnterFastShipMovement)
    s_end
NextShipWednesday:
    writetext(VermilionPortSailMondayText)
    waitbutton
    closetext
    applymovement(PLAYER, VermilionPortCannotEnterFastShipMovement)
    s_end
NextShipSunday:
    writetext(VermilionPortSailSundayText)
    waitbutton
    closetext
    applymovement(PLAYER, VermilionPortCannotEnterFastShipMovement)
    s_end
skip:
    s_end
    SCRIPT_END
}
bool VermilionPortNotRidingScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(VermilionPortComeAgainText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool VermilionPortNotRidingMoveAwayScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(VermilionPortComeAgainText)
    waitbutton
    closetext
    applymovement(PLAYER, VermilionPortCannotEnterFastShipMovement)
    s_end
    SCRIPT_END
}
bool VermilionPortSailorScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue_jump(VermilionPortAlreadyRodeScript)
    readvar(VAR_WEEKDAY)
    ifequal(MONDAY, NextShipWednesday)
    ifequal(TUESDAY, NextShipWednesday)
    ifequal(THURSDAY, NextShipSunday)
    ifequal(FRIDAY, NextShipSunday)
    ifequal(SATURDAY, NextShipSunday)
    writetext(VermilionPortAskBoardingText)
    yesorno
    iffalse_jump(VermilionPortNotRidingScript)
    writetext(VermilionPortAskTicketText)
    promptbutton
    checkitem(S_S_TICKET)
    iffalse(NoTicket)
    writetext(VermilionPortSSTicketText)
    waitbutton
    closetext
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    applymovement(PLAYER, VermilionPortApproachFastShipRightMovement)
    sjump(VermilionPortSailorAtGangwayScript)
NoTicket:
    writetext(VermilionPortNoTicketText)
    waitbutton
    closetext
    s_end
NextShipWednesday:
    writetext(VermilionPortSailMondayText)
    waitbutton
    closetext
    s_end
NextShipSunday:
    writetext(VermilionPortSailSundayText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool VermilionPortSuperNerdScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(VermilionPortSuperNerdText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const struct HiddenItem VermilionPortHiddenIron = {IRON, EVENT_VERMILION_PORT_HIDDEN_IRON};
const uint8_t VermilionPortEnterFastShipMovement[] = {
    step(DOWN),
    movement_step_end,
};
const uint8_t VermilionPortLeaveFastShipMovement[] = {
    step(UP),
    movement_step_end,
};
const uint8_t VermilionPortCannotEnterFastShipMovement[] = {
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t VermilionPortApproachFastShipMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t VermilionPortApproachFastShipRightMovement[] = {
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s VermilionPortDepartingText[] = {
    text_start("We're departing"
        t_line "soon. Please get"
        t_cont "on board."
        t_done )
};
const txt_cmd_s VermilionPortCantBoardText[] = {
    text_start("Sorry. You can't"
        t_line "board now."
        t_done )
};
const txt_cmd_s VermilionPortAskBoardingText[] = {
    text_start("Welcome to FAST"
        t_line "SHIP S.S.AQUA."
        t_para "Will you be board-"
        t_line "ing today?"
        t_done )
};
const txt_cmd_s VermilionPortAskTicketText[] = {
    text_start("May I see your"
        t_line "S.S.TICKET?"
        t_done )
};
const txt_cmd_s VermilionPortComeAgainText[] = {
    text_start("We hope to see you"
        t_line "again!"
        t_done )
};
const txt_cmd_s VermilionPortSSTicketText[] = {
    text_start("<PLAYER> flashed"
        t_line "the S.S.TICKET."
        t_para "That's it."
        t_line "Thank you!"
        t_done )
};
const txt_cmd_s VermilionPortNoTicketText[] = {
    text_start("<PLAYER> tried to"
        t_line "show the S.S."
        t_cont "TICKET…"
        t_para "…But no TICKET!"
        t_para "Sorry!"
        t_line "You may board only"
        t_para "if you have an"
        t_line "S.S.TICKET."
        t_done )
};
const txt_cmd_s VermilionPortSailMondayText[] = {
    text_start("The FAST SHIP will"
        t_line "sail on Wednesday."
        t_done )
};
const txt_cmd_s VermilionPortSailSundayText[] = {
    text_start("The FAST SHIP will"
        t_line "sail next Sunday."
        t_done )
};
const txt_cmd_s VermilionPortSuperNerdText[] = {
    text_start("You came from"
        t_line "JOHTO?"
        t_para "I hear many rare"
        t_line "#MON live over"
        t_cont "there."
        t_done )
    //db(0, 0) // filler
};
