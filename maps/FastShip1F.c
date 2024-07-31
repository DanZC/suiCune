#include "../constants.h"
#include "../util/scripting.h"
#include "FastShip1F.h"
//// EVENTS
enum {
    FASTSHIP1F_SAILOR1 = 2,
    FASTSHIP1F_SAILOR2,
    FASTSHIP1F_SAILOR3,
    FASTSHIP1F_GENTLEMAN,
};

const Script_fn_t FastShip1F_SceneScripts[] = {
    FastShip1F_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    FastShip1F_MapScripts_EnterFastShip , //  SCENE_FASTSHIP1F_ENTER_SHIP,
    FastShip1F_MapScripts_DummyScene2 , //  SCENE_FASTSHIP1F_MEET_GRANDPA,
};

const struct MapCallback FastShip1F_MapCallbacks[] = {
    0,
};

const struct MapScripts FastShip1F_MapScripts = {
    .scene_script_count = lengthof(FastShip1F_SceneScripts),
    .scene_scripts = FastShip1F_SceneScripts,

    .callback_count = 0, // lengthof(FastShip1F_MapCallbacks),
    .callbacks = FastShip1F_MapCallbacks,
};

static const struct CoordEvent FastShip1F_CoordEvents[] = {
    coord_event(24, 6, SCENE_FASTSHIP1F_MEET_GRANDPA, &WorriedGrandpaSceneLeft),
    coord_event(25, 6, SCENE_FASTSHIP1F_MEET_GRANDPA, &WorriedGrandpaSceneRight),
};

static const struct BGEvent FastShip1F_BGEvents[] = {
    0,
};

static const struct WarpEventData FastShip1F_WarpEvents[] = {
    warp_event(25, 1, FAST_SHIP_1F, -1),
    warp_event(27, 8, FAST_SHIP_CABINS_NNW_NNE_NE, 1),
    warp_event(23, 8, FAST_SHIP_CABINS_NNW_NNE_NE, 2),
    warp_event(19, 8, FAST_SHIP_CABINS_NNW_NNE_NE, 3),
    warp_event(15, 8, FAST_SHIP_CABINS_SW_SSW_NW, 1),
    warp_event(15, 15, FAST_SHIP_CABINS_SW_SSW_NW, 2),
    warp_event(19, 15, FAST_SHIP_CABINS_SW_SSW_NW, 4),
    warp_event(23, 15, FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 1),
    warp_event(27, 15, FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 3),
    warp_event(3, 13, FAST_SHIP_CABINS_SE_SSE_CAPTAINS_CABIN, 5),
    warp_event(6, 12, FAST_SHIP_B1F, 1),
    warp_event(30, 14, FAST_SHIP_B1F, 2),
};

static const struct ObjEvent FastShip1F_ObjectEvents[] = {
    object_event(25, 2, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &FastShip1FSailor1Script, -1),
    object_event(14, 7, SPRITE_SAILOR, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &FastShip1FSailor2Script, -1),
    object_event(22, 17, SPRITE_SAILOR, SPRITEMOVEDATA_WALK_LEFT_RIGHT, 2, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &FastShip1FSailor3Script, -1),
    object_event(19, 6, SPRITE_GENTLEMAN, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_FAST_SHIP_1F_GENTLEMAN),
};

const struct MapEvents FastShip1F_MapEvents = {
    .warp_event_count = lengthof(FastShip1F_WarpEvents),
    .warp_events = FastShip1F_WarpEvents,

    .coord_event_count = lengthof(FastShip1F_CoordEvents),
    .coord_events = FastShip1F_CoordEvents,

    .bg_event_count = 0, // lengthof(FastShip1F_BGEvents),
    .bg_events = FastShip1F_BGEvents,

    .obj_event_count = lengthof(FastShip1F_ObjectEvents),
    .obj_events = FastShip1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "FastShip1F.h"

#define INSTANT_SHIP_ARRIVAL 0

bool FastShip1F_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool FastShip1F_MapScripts_EnterFastShip(script_s* s) {
    SCRIPT_BEGIN
    sdefer(FastShip1F_MapScripts_EnterFastShipScript);
    s_end
    SCRIPT_END
}
bool FastShip1F_MapScripts_DummyScene2(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool FastShip1F_MapScripts_EnterFastShipScript(script_s* s) {
    SCRIPT_BEGIN
    applymovement(FASTSHIP1F_SAILOR1, FastShip1F_SailorStepAsideMovement)
    applymovement(PLAYER, FastShip1F_PlayerEntersShipMovement)
    applymovement(FASTSHIP1F_SAILOR1, FastShip1F_SailorBlocksDoorMovement)
    pause(30)
    playsound(SFX_BOAT)
    earthquake(30)
    blackoutmod(FAST_SHIP_CABINS_SW_SSW_NW)
    clearevent(EVENT_FAST_SHIP_HAS_ARRIVED)
    checkevent(EVENT_FAST_SHIP_FIRST_TIME)
    iftrue(SkipGrandpa)
    setscene(SCENE_FASTSHIP1F_MEET_GRANDPA)
    s_end
SkipGrandpa:
    setscene(SCENE_DEFAULT)
    s_end
    SCRIPT_END
}
bool FastShip1FSailor1Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
#if !INSTANT_SHIP_ARRIVAL
    checkevent(EVENT_FAST_SHIP_HAS_ARRIVED)
    iftrue(Arrived)
    checkevent(EVENT_FAST_SHIP_DESTINATION_OLIVINE)
    iftrue(Olivine)
    writetext(FastShip1FSailor1Text_ToVermilion)
    waitbutton
    closetext
    s_end
Olivine:
    writetext(FastShip1FSailor1Text_ToOlivine)
    waitbutton
    closetext
    s_end
#endif
Arrived:
    checkevent(EVENT_FAST_SHIP_DESTINATION_OLIVINE)
    iftrue(_Olivine)
    writetext(FastShip1FSailor1Text_InVermilion)
    waitbutton
    closetext
    scall_local(LetThePlayerOut);
    playsound(SFX_EXIT_BUILDING)
    special(FadeOutPalettes)
    waitsfx
    setevent(EVENT_VERMILION_PORT_SAILOR_AT_GANGWAY)
    setmapscene(VERMILION_PORT, SCENE_VERMILIONPORT_LEAVE_SHIP)
    warp(VERMILION_PORT, 7, 17)
    s_end
_Olivine:
    writetext(FastShip1FSailor1Text_InOlivine)
    waitbutton
    closetext
    scall_local(LetThePlayerOut);
    playsound(SFX_EXIT_BUILDING)
    special(FadeOutPalettes)
    waitsfx
    setevent(EVENT_OLIVINE_PORT_SAILOR_AT_GANGWAY)
    setmapscene(OLIVINE_PORT, SCENE_OLIVINEPORT_LEAVE_SHIP)
    warp(OLIVINE_PORT, 7, 23)
    s_end
LetThePlayerOut:
    readvar(VAR_FACING)
    ifequal(RIGHT, YouAreFacingRight)
    applymovement(FASTSHIP1F_SAILOR1, FastShip1F_SailorStepAsideMovement)
    applymovement(PLAYER, FastShip1F_PlayerLeavesShipMovement)
    s_end
YouAreFacingRight:
    applymovement(FASTSHIP1F_SAILOR1, FastShip1F_SailorStepAsideDownMovement)
    applymovement(PLAYER, FastShip1F_PlayerLeavesShipRightMovement)
    s_end
    SCRIPT_END
}
bool FastShip1FSailor2Script(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_FAST_SHIP_FIRST_TIME)
    iftrue(Vermilion)
    writetext(FastShip1FSailor2Text_FirstTime)
    waitbutton
    closetext
    s_end
Vermilion:
    writetext(FastShip1FSailor2Text)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool FastShip1FSailor3Script(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(FastShip1FSailor3Text)
    SCRIPT_END
}
bool WorriedGrandpaSceneRight(script_s* s) {
    SCRIPT_BEGIN
    moveobject(FASTSHIP1F_GENTLEMAN, 20, 6)
    SCRIPT_FALLTHROUGH(WorriedGrandpaSceneLeft)
}
bool WorriedGrandpaSceneLeft(script_s* s) {
    SCRIPT_BEGIN
    appear(FASTSHIP1F_GENTLEMAN)
    applymovement(FASTSHIP1F_GENTLEMAN, FastShip1F_GrandpaRunsInMovement)
    playsound(SFX_TACKLE)
    applymovement(PLAYER, FastShip1F_PlayerHitByGrandpaMovement)
    applymovement(FASTSHIP1F_GENTLEMAN, FastShip1F_GrandpaApproachesPlayerMovement)
    opentext
    writetext(FastShip1FGrandpaText)
    waitbutton
    closetext
    turnobject(PLAYER, RIGHT)
    applymovement(FASTSHIP1F_GENTLEMAN, FastShip1F_GrandpaRunsOutMovement)
    disappear(FASTSHIP1F_GENTLEMAN)
    setscene(SCENE_DEFAULT)
    s_end
    SCRIPT_END
}
const uint8_t FastShip1F_SailorStepAsideMovement[] = {
    slow_step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t FastShip1F_SailorBlocksDoorMovement[] = {
    slow_step(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t FastShip1F_SailorStepAsideDownMovement[] = {
    slow_step(DOWN),
    turn_head(UP),
    movement_step_end,
};
const uint8_t FastShip1F_PlayerEntersShipMovement[] = {
    step(DOWN),
    step(DOWN),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t FastShip1F_GrandpaRunsInMovement[] = {
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    movement_step_end,
};
const uint8_t FastShip1F_GrandpaApproachesPlayerMovement[] = {
    step(RIGHT),
    movement_step_end,
};
const uint8_t FastShip1F_GrandpaRunsOutMovement[] = {
    big_step(DOWN),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(RIGHT),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    big_step(DOWN),
    movement_step_end,
};
const uint8_t FastShip1F_PlayerHitByGrandpaMovement[] = {
    big_step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t FastShip1F_StepUpMovement[] = {
    step(UP),
    movement_step_end,
};
const uint8_t FastShip1F_StepDownMovement[] = {
    step(DOWN),
    movement_step_end,
};
const uint8_t FastShip1F_PlayerLeavesShipMovement[] = {
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t FastShip1F_PlayerLeavesShipRightMovement[] = {
    step(RIGHT),
    step(UP),
    movement_step_end,
};
const txt_cmd_s FastShip1FSailor1Text_ToVermilion[] = {
    text_start("FAST SHIP S.S.AQUA"
        t_line "is en route to"
        t_cont "VERMILION CITY."
        t_para "We will make an"
        t_line "announcement when"
        t_cont "we arrive."
        t_done )
};
const txt_cmd_s FastShip1FSailor1Text_ToOlivine[] = {
    text_start("FAST SHIP S.S.AQUA"
        t_line "is en route to"
        t_cont "OLIVINE CITY."
        t_para "We will make an"
        t_line "announcement when"
        t_cont "we arrive."
        t_done )
};
const txt_cmd_s FastShip1FSailor2Text_FirstTime[] = {
    text_start("Here's your cabin."
        t_para "If your #MON"
        t_line "are hurt, take a"
        t_cont "nap in the bed."
        t_para "That will heal"
        t_line "them."
        t_done )
};
const txt_cmd_s FastShip1FSailor2Text[] = {
    text_start("Here's your cabin."
        t_para "You can heal your"
        t_line "#MON by taking"
        t_cont "a nap in the bed."
        t_para "The ship will"
        t_line "arrive while"
        t_cont "you're sleeping."
        t_done )
};
const txt_cmd_s FastShip1FSailor3Text[] = {
    text_start("The passengers are"
        t_line "all trainers."
        t_para "They're all itch-"
        t_line "ing to battle in"
        t_cont "their cabins."
        t_done )
};
const txt_cmd_s FastShip1FGrandpaText[] = {
    text_start("Whoa! Excuse me."
        t_line "I was in a hurry!"
        t_para "My granddaughter"
        t_line "is missing!"
        t_para "She's just a wee"
        t_line "girl. If you see"
        t_para "her, please let me"
        t_line "know!"
        t_done )
};
const txt_cmd_s FastShip1FSailor1Text_InOlivine[] = {
    text_start("FAST SHIP S.S.AQUA"
        t_line "has arrived in"
        t_cont "OLIVINE CITY."
        t_done )
};
const txt_cmd_s FastShip1FSailor1Text_InVermilion[] = {
    text_start("FAST SHIP S.S.AQUA"
        t_line "has arrived in"
        t_cont "VERMILION CITY."
        t_done )
    //db(0, 0) // filler
};
