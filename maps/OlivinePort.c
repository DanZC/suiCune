#include "../constants.h"
#include "../util/scripting.h"
#include "OlivinePort.h"
//// EVENTS
enum {
    OLIVINEPORT_SAILOR1 = 2,
    OLIVINEPORT_SAILOR2,
    OLIVINEPORT_SAILOR3,
    OLIVINEPORT_FISHING_GURU1,
    OLIVINEPORT_FISHING_GURU2,
    OLIVINEPORT_YOUNGSTER,
    OLIVINEPORT_COOLTRAINER_F,
};

const Script_fn_t OlivinePort_SceneScripts[] = {
    OlivinePort_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    OlivinePort_MapScripts_LeaveFastShip , //  SCENE_OLIVINEPORT_LEAVE_SHIP,
};

const struct MapCallback OlivinePort_MapCallbacks[] = {
    0,
};

const struct MapScripts OlivinePort_MapScripts = {
    .scene_script_count = lengthof(OlivinePort_SceneScripts),
    .scene_scripts = OlivinePort_SceneScripts,

    .callback_count = 0, // lengthof(OlivinePort_MapCallbacks),
    .callbacks = OlivinePort_MapCallbacks,
};

static const struct CoordEvent OlivinePort_CoordEvents[] = {
    coord_event(7, 15, SCENE_DEFAULT, &OlivinePortWalkUpToShipScript),
};

static const struct BGEvent OlivinePort_BGEvents[] = {
    bg_event(1, 22, BGEVENT_ITEM, &OlivinePortHiddenProtein),
};

static const struct WarpEventData OlivinePort_WarpEvents[] = {
    warp_event(11, 7, OLIVINE_PORT_PASSAGE, 5),
    warp_event(7, 23, FAST_SHIP_1F, 1),
};

static const struct ObjEvent OlivinePort_ObjectEvents[] = {
    object_event(7, 23, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePortSailorAtGangwayScript, EVENT_OLIVINE_PORT_SAILOR_AT_GANGWAY),
    object_event(7, 15, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePortSailorBeforeHOFScript, EVENT_OLIVINE_PORT_SPRITES_BEFORE_HALL_OF_FAME),
    object_event(6, 15, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePortSailorAfterHOFScript, EVENT_OLIVINE_PORT_SPRITES_AFTER_HALL_OF_FAME),
    object_event(4, 14, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePortFishingGuru1Script, EVENT_OLIVINE_PORT_SPRITES_BEFORE_HALL_OF_FAME),
    object_event(13, 14, SPRITE_FISHING_GURU, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePortFishingGuru2Script, EVENT_OLIVINE_PORT_SPRITES_BEFORE_HALL_OF_FAME),
    object_event(4, 15, SPRITE_YOUNGSTER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePortYoungsterScript, EVENT_OLIVINE_PORT_SPRITES_AFTER_HALL_OF_FAME),
    object_event(11, 15, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &OlivinePortCooltrainerFScript, EVENT_OLIVINE_PORT_SPRITES_AFTER_HALL_OF_FAME),
};

const struct MapEvents OlivinePort_MapEvents = {
    .warp_event_count = lengthof(OlivinePort_WarpEvents),
    .warp_events = OlivinePort_WarpEvents,

    .coord_event_count = lengthof(OlivinePort_CoordEvents),
    .coord_events = OlivinePort_CoordEvents,

    .bg_event_count = lengthof(OlivinePort_BGEvents),
    .bg_events = OlivinePort_BGEvents,

    .obj_event_count = lengthof(OlivinePort_ObjectEvents),
    .obj_events = OlivinePort_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "OlivinePort.h"

bool OlivinePort_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool OlivinePort_MapScripts_LeaveFastShip(script_s* s) {
    SCRIPT_BEGIN
    sdefer(OlivinePort_MapScripts_LeaveFastShipScript);
    s_end
    SCRIPT_END
}
bool OlivinePort_MapScripts_LeaveFastShipScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(PLAYER, OlivinePortLeaveFastShipMovement)
    appear(OLIVINEPORT_SAILOR1)
    setscene(SCENE_DEFAULT)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    blackoutmod(OLIVINE_CITY)
    s_end
    SCRIPT_END
}
bool OlivinePortSailorAtGangwayScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue_jump(OlivinePortAlreadyRodeScript)
    writetext(OlivinePortSailorGetOnBoardText)
    waitbutton
    closetext
    turnobject(OLIVINEPORT_SAILOR1, DOWN)
    pause(10)
    playsound(SFX_EXIT_BUILDING)
    disappear(OLIVINEPORT_SAILOR1)
    waitsfx
    applymovement(PLAYER, OlivinePortEnterFastShipMovement)
    playsound(SFX_EXIT_BUILDING)
    special(FadeOutPalettes)
    waitsfx
    checkevent(EVENT_FAST_SHIP_FIRST_TIME)
    iffalse(FirstTime)
    clearevent(EVENT_FAST_SHIP_PASSENGERS_EASTBOUND)
    setevent(EVENT_FAST_SHIP_PASSENGERS_WESTBOUND)
    clearevent(EVENT_BEAT_COOLTRAINERM_SEAN)
    clearevent(EVENT_BEAT_COOLTRAINERF_CAROL)
    clearevent(EVENT_BEAT_GENTLEMAN_EDWARD)
    clearevent(EVENT_BEAT_BEAUTY_CASSIE)
    clearevent(EVENT_BEAT_PSYCHIC_RODNEY)
    clearevent(EVENT_BEAT_SUPER_NERD_SHAWN)
    clearevent(EVENT_BEAT_SAILOR_GARRETT)
    clearevent(EVENT_BEAT_FISHER_JONAH)
    clearevent(EVENT_BEAT_BLACKBELT_WAI)
FirstTime:
    clearevent(EVENT_FAST_SHIP_DESTINATION_OLIVINE)
    appear(OLIVINEPORT_SAILOR1)
    setmapscene(FAST_SHIP_1F, SCENE_FASTSHIP1F_ENTER_SHIP)
    warp(FAST_SHIP_1F, 25, 1)
    s_end
    SCRIPT_END
}
bool OlivinePortAlreadyRodeScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(OlivinePortCantBoardText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool OlivinePortWalkUpToShipScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(OLIVINEPORT_SAILOR3, RIGHT)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue(skip)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    iftrue(skip)
    turnobject(PLAYER, LEFT)
    opentext
    checkevent(EVENT_FAST_SHIP_FIRST_TIME)
    iffalse(FirstTime)
    readvar(VAR_WEEKDAY)
    ifequal(SUNDAY, NextShipMonday)
    ifequal(SATURDAY, NextShipMonday)
    ifequal(TUESDAY, NextShipFriday)
    ifequal(WEDNESDAY, NextShipFriday)
    ifequal(THURSDAY, NextShipFriday)
FirstTime:
    writetext(OlivinePortAskBoardText)
    yesorno
    iffalse_jump(OlivinePortNotRidingMoveAwayScript)
    writetext(OlivinePortAskTicketText)
    promptbutton
    checkitem(S_S_TICKET)
    iffalse(NoTicket)
    writetext(OlivinePortFlashTicketText)
    waitbutton
    closetext
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    applymovement(PLAYER, OlivinePortApproachFastShipFirstTimeMovement)
    sjump(OlivinePortSailorAtGangwayScript)
NoTicket:
    writetext(OlivinePortNoTicketText)
    waitbutton
    closetext
    applymovement(PLAYER, OlivinePortCannotEnterFastShipMovement)
    s_end
NextShipMonday:
    writetext(OlivinePortMondayShipText)
    waitbutton
    closetext
    applymovement(PLAYER, OlivinePortCannotEnterFastShipMovement)
    s_end
NextShipFriday:
    writetext(OlivinePortFridayShipText)
    waitbutton
    closetext
    applymovement(PLAYER, OlivinePortCannotEnterFastShipMovement)
    s_end
skip:
    s_end
    SCRIPT_END
}
bool OlivinePortNotRidingScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(OlivinePortComeAgainText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool OlivinePortNotRidingMoveAwayScript(script_s* s) {
    SCRIPT_BEGIN
    writetext(OlivinePortComeAgainText)
    waitbutton
    closetext
    applymovement(PLAYER, OlivinePortCannotEnterFastShipMovement)
    s_end
    SCRIPT_END
}
bool OlivinePortSailorAfterHOFScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue_jump(OlivinePortAlreadyRodeScript)
    checkevent(EVENT_FAST_SHIP_FIRST_TIME)
    iffalse(FirstTime)
    readvar(VAR_WEEKDAY)
    ifequal(SUNDAY, NextShipMonday)
    ifequal(SATURDAY, NextShipMonday)
    ifequal(TUESDAY, NextShipFriday)
    ifequal(WEDNESDAY, NextShipFriday)
    ifequal(THURSDAY, NextShipFriday)
FirstTime:
    writetext(OlivinePortAskBoardText)
    yesorno
    iffalse_jump(OlivinePortNotRidingScript)
    writetext(OlivinePortAskTicketText)
    promptbutton
    checkitem(S_S_TICKET)
    iffalse(NoTicket)
    writetext(OlivinePortFlashTicketText)
    waitbutton
    closetext
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2)
    readvar(VAR_FACING)
    ifequal(RIGHT, Right)
    applymovement(PLAYER, OlivinePortApproachFastShipAfterHOFMovement)
    sjump(OlivinePortSailorAtGangwayScript)
Right:
    applymovement(PLAYER, OlivinePortApproachFastShipAfterHOFRightMovement)
    sjump(OlivinePortSailorAtGangwayScript)
NoTicket:
    writetext(OlivinePortNoTicketText)
    waitbutton
    closetext
    s_end
NextShipMonday:
    writetext(OlivinePortMondayShipText)
    waitbutton
    closetext
    s_end
NextShipFriday:
    writetext(OlivinePortFridayShipText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool OlivinePortSailorBeforeHOFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(OlivinePortSailorBeforeHOFText)
    SCRIPT_END
}
bool OlivinePortFishingGuru1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(OlivinePortFishingGuru1Text)
    waitbutton
    closetext
    turnobject(OLIVINEPORT_FISHING_GURU1, UP)
    s_end
    SCRIPT_END
}
bool OlivinePortFishingGuru2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(OlivinePortFishingGuru2Text)
    waitbutton
    closetext
    turnobject(OLIVINEPORT_FISHING_GURU2, UP)
    s_end
    SCRIPT_END
}
bool OlivinePortYoungsterScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(OlivinePortYoungsterText)
    waitbutton
    closetext
    turnobject(OLIVINEPORT_YOUNGSTER, DOWN)
    s_end
    SCRIPT_END
}
bool OlivinePortCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    writetext(OlivinePortCooltrainerFText)
    waitbutton
    closetext
    turnobject(OLIVINEPORT_COOLTRAINER_F, DOWN)
    s_end
    SCRIPT_END
}
const struct HiddenItem OlivinePortHiddenProtein = {PROTEIN, EVENT_OLIVINE_PORT_HIDDEN_PROTEIN};
const uint8_t OlivinePortEnterFastShipMovement[] = {
    step(DOWN),
    movement_step_end,
};
const uint8_t OlivinePortLeaveFastShipMovement[] = {
    step(UP),
    movement_step_end,
};
const uint8_t OlivinePortCannotEnterFastShipMovement[] = {
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t OlivinePortApproachFastShipFirstTimeMovement[] = {
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t OlivinePortApproachFastShipAfterHOFMovement[] = {
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t OlivinePortApproachFastShipAfterHOFRightMovement[] = {
    step(UP),
    step(RIGHT),
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const txt_cmd_s OlivinePortSailorGetOnBoardText[] = {
    text_start("We're departing"
        t_line "soon. Please get"
        t_cont "on board."
        t_done )
};
const txt_cmd_s OlivinePortCantBoardText[] = {
    text_start("Sorry. You can't"
        t_line "board now."
        t_done )
};
const txt_cmd_s OlivinePortAskBoardText[] = {
    text_start("Welcome to FAST"
        t_line "SHIP S.S.AQUA."
        t_para "Will you be board-"
        t_line "ing today?"
        t_done )
};
const txt_cmd_s OlivinePortAskTicketText[] = {
    text_start("May I see your"
        t_line "S.S.TICKET?"
        t_done )
};
const txt_cmd_s OlivinePortComeAgainText[] = {
    text_start("We hope to see you"
        t_line "again!"
        t_done )
};
const txt_cmd_s OlivinePortFlashTicketText[] = {
    text_start("<PLAYER> flashed"
        t_line "the S.S.TICKET."
        t_para "That's it."
        t_line "Thank you!"
        t_done )
};
const txt_cmd_s OlivinePortNoTicketText[] = {
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
const txt_cmd_s OlivinePortMondayShipText[] = {
    text_start("The FAST SHIP will"
        t_line "sail next Monday."
        t_done )
};
const txt_cmd_s OlivinePortFridayShipText[] = {
    text_start("The FAST SHIP will"
        t_line "sail next Friday."
        t_done )
};
const txt_cmd_s OlivinePortFishingGuru1Text[] = {
    text_start("SHELLDER are easy"
        t_line "to catch here."
        t_para "They're kind of"
        t_line "rare elsewhere."
        t_done )
};
const txt_cmd_s OlivinePortFishingGuru2Text[] = {
    text_start("How many RODS do"
        t_line "you have?"
        t_para "Different RODS"
        t_line "catch different"
        t_cont "#MON."
        t_done )
};
const txt_cmd_s OlivinePortYoungsterText[] = {
    text_start("S.S.AQUA uses jets"
        t_line "to skim over the"
        t_cont "waves!"
        t_done )
};
const txt_cmd_s OlivinePortCooltrainerFText[] = {
    text_start("There are lots of"
        t_line "#MON in KANTO."
        t_para "I wish I could go…"
        t_done )
};
const txt_cmd_s OlivinePortSailorBeforeHOFText[] = {
    text_start("We don't want you"
        t_line "to fall into the"
        t_para "sea, so you're not"
        t_line "allowed in."
        t_done )
    //db(0, 0) // filler
};
