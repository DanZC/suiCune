#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakTinTowerEntrance.h"
//// EVENTS
enum {
    ECRUTEAKTINTOWERENTRANCE_SAGE1 = 2,
    ECRUTEAKTINTOWERENTRANCE_SAGE2,
    ECRUTEAKTINTOWERENTRANCE_SAGE3,
    ECRUTEAKTINTOWERENTRANCE_GRAMPS,
};

const Script_fn_t EcruteakTinTowerEntrance_SceneScripts[] = {
    EcruteakTinTowerEntrance_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    EcruteakTinTowerEntrance_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback EcruteakTinTowerEntrance_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, EcruteakTinTowerEntrance_MapScripts_InitializeSages),
};

const struct MapScripts EcruteakTinTowerEntrance_MapScripts = {
    .scene_script_count = lengthof(EcruteakTinTowerEntrance_SceneScripts),
    .scene_scripts = EcruteakTinTowerEntrance_SceneScripts,

    .callback_count = lengthof(EcruteakTinTowerEntrance_MapCallbacks),
    .callbacks = EcruteakTinTowerEntrance_MapCallbacks,
};

static const struct CoordEvent EcruteakTinTowerEntrance_CoordEvents[] = {
    coord_event(4, 7, SCENE_DEFAULT, &EcruteakTinTowerEntranceSageBlocksLeft),
    coord_event(5, 7, SCENE_DEFAULT, &EcruteakTinTowerEntranceSageBlocksRight),
};

static const struct BGEvent EcruteakTinTowerEntrance_BGEvents[] = {
    0,
};

static const struct WarpEventData EcruteakTinTowerEntrance_WarpEvents[] = {
    warp_event(4, 17, ECRUTEAK_CITY, 3),
    warp_event(5, 17, ECRUTEAK_CITY, 3),
    warp_event(5, 3, ECRUTEAK_TIN_TOWER_ENTRANCE, 4),
    warp_event(17, 15, ECRUTEAK_TIN_TOWER_ENTRANCE, 3),
    warp_event(17, 3, WISE_TRIOS_ROOM, 3),
};

static const struct ObjEvent EcruteakTinTowerEntrance_ObjectEvents[] = {
    object_event(4, 6, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakTinTowerEntranceSageScript, EVENT_RANG_CLEAR_BELL_1),
    object_event(5, 6, SPRITE_SAGE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakTinTowerEntranceSageScript, EVENT_RANG_CLEAR_BELL_2),
    object_event(6, 9, SPRITE_SAGE, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakTinTowerEntranceWanderingSageScript, EVENT_ECRUTEAK_TIN_TOWER_ENTRANCE_WANDERING_SAGE),
    object_event(3, 11, SPRITE_GRAMPS, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakTinTowerEntranceGrampsScript, EVENT_ECRUTEAK_TIN_TOWER_ENTRANCE_WANDERING_SAGE),
};

const struct MapEvents EcruteakTinTowerEntrance_MapEvents = {
    .warp_event_count = lengthof(EcruteakTinTowerEntrance_WarpEvents),
    .warp_events = EcruteakTinTowerEntrance_WarpEvents,

    .coord_event_count = lengthof(EcruteakTinTowerEntrance_CoordEvents),
    .coord_events = EcruteakTinTowerEntrance_CoordEvents,

    .bg_event_count = 0, // lengthof(EcruteakTinTowerEntrance_BGEvents),
    .bg_events = EcruteakTinTowerEntrance_BGEvents,

    .obj_event_count = lengthof(EcruteakTinTowerEntrance_ObjectEvents),
    .obj_events = EcruteakTinTowerEntrance_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakTinTowerEntrance.h"

bool EcruteakTinTowerEntrance_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool EcruteakTinTowerEntrance_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool EcruteakTinTowerEntrance_MapScripts_InitializeSages(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_FOUGHT_SUICUNE)
    iftrue(DontBlockTower)
    checkevent(EVENT_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER)
    iftrue(DontBlockTower)
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(BlockTower)
    s_endcallback
BlockTower:
    clearevent(EVENT_RANG_CLEAR_BELL_1)
    setevent(EVENT_RANG_CLEAR_BELL_2)
    setevent(EVENT_ECRUTEAK_TIN_TOWER_ENTRANCE_WANDERING_SAGE)
    checkitem(CLEAR_BELL)
    iftrue(NoClearBell)
    setscene(SCENE_DEFAULT)
NoClearBell:
    s_endcallback
DontBlockTower:
    clearevent(EVENT_ECRUTEAK_TIN_TOWER_ENTRANCE_WANDERING_SAGE)
    s_endcallback
    SCRIPT_END
}
bool EcruteakTinTowerEntranceSageBlocksLeft(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_RANG_CLEAR_BELL_2)
    iftrue_jump(EcruteakTinTowerEntranceAlreadyBlocked)
    applymovement(ECRUTEAKTINTOWERENTRANCE_SAGE2, EcruteakTinTowerEntranceSageBlocksLeftMovement)
    moveobject(ECRUTEAKTINTOWERENTRANCE_SAGE1, 4, 6)
    appear(ECRUTEAKTINTOWERENTRANCE_SAGE1)
    pause(5)
    disappear(ECRUTEAKTINTOWERENTRANCE_SAGE2)
    s_end
    SCRIPT_END
}
bool EcruteakTinTowerEntranceSageBlocksRight(script_s* s) {
    SCRIPT_BEGIN
    checkevent(EVENT_RANG_CLEAR_BELL_1)
    iftrue_jump(EcruteakTinTowerEntranceAlreadyBlocked)
    applymovement(ECRUTEAKTINTOWERENTRANCE_SAGE1, EcruteakTinTowerEntranceSageBlocksRightMovement)
    moveobject(ECRUTEAKTINTOWERENTRANCE_SAGE2, 5, 6)
    appear(ECRUTEAKTINTOWERENTRANCE_SAGE2)
    pause(5)
    disappear(ECRUTEAKTINTOWERENTRANCE_SAGE1)
    s_end
    SCRIPT_END
}
bool EcruteakTinTowerEntranceAlreadyBlocked(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool EcruteakTinTowerEntranceSageScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_CLEARED_RADIO_TOWER)
    iftrue(CheckForClearBell)
    checkflag(ENGINE_FOGBADGE)
    iftrue(BlockPassage_GotFogBadge)
    writetext(EcruteakTinTowerEntranceSageText)
    waitbutton
    closetext
    s_end
BlockPassage_GotFogBadge:
    writetext(EcruteakTinTowerEntranceSageText_GotFogBadge)
    waitbutton
    closetext
    s_end
CheckForClearBell:
    checkevent(EVENT_KOJI_ALLOWS_YOU_PASSAGE_TO_TIN_TOWER)
    iftrue(AllowedThrough)
    checkevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    iftrue(RangClearBell)
    checkitem(CLEAR_BELL)
    iftrue(GotClearBell)
    writetext(EcruteakTinTowerEntranceSageText_NoClearBell)
    waitbutton
    closetext
    s_end
GotClearBell:
    writetext(EcruteakTinTowerEntranceSageText_HearsClearBell)
    waitbutton
    closetext
    setscene(SCENE_FINISHED)
    setevent(EVENT_RANG_CLEAR_BELL_2)
    clearevent(EVENT_RANG_CLEAR_BELL_1)
    setevent(EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1)
    s_end
AllowedThrough:
    writetext(EcruteakTinTowerEntranceSageText_PleaseDoGoOn)
    waitbutton
    closetext
    s_end
RangClearBell:
    writetext(EcruteakTinTowerEntranceSageText_HeardClearBell)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EcruteakTinTowerEntranceWanderingSageScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_GOT_CLEAR_BELL)
    iftrue(GotClearBell)
    writetext(EcruteakTinTowerEntranceWanderingSageText)
    waitbutton
    closetext
    s_end
GotClearBell:
    writetext(EcruteakTinTowerEntranceWanderingSageText_GotClearBell)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool EcruteakTinTowerEntranceGrampsScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakTinTowerEntranceGrampsText)
    SCRIPT_END
}
const uint8_t EcruteakTinTowerEntranceSageBlocksLeftMovement[] = {
    movement_fix_facing,
    big_step(LEFT),
    movement_remove_fixed_facing,
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t EcruteakTinTowerEntranceSageBlocksRightMovement[] = {
    movement_fix_facing,
    big_step(RIGHT),
    movement_remove_fixed_facing,
    turn_head(DOWN),
    movement_step_end,
};
const txt_cmd_s EcruteakTinTowerEntranceSageText[] = {
    text_start("TIN TOWER is off"
        t_line "limits to anyone"
        t_para "without ECRUTEAK"
        t_line "GYM's BADGE."
        t_para "Sorry, but you'll"
        t_line "have to leave."
        t_done )
};
const txt_cmd_s EcruteakTinTowerEntranceSageText_GotFogBadge[] = {
    text_start("TIN TOWER is off"
        t_line "limits to anyone"
        t_para "without ECRUTEAK"
        t_line "GYM's BADGE."
        t_para "Ah!"
        t_para "ECRUTEAK's GYM"
        t_line "BADGE! Please, go"
        t_cont "right through."
        t_done )
};
const txt_cmd_s EcruteakTinTowerEntranceSageText_NoClearBell[] = {
    text_start("A momentous event"
        t_line "has occurred."
        t_para "I beg your pardon,"
        t_line "but I must ask you"
        t_cont "to leave."
        t_para "…What soothes the"
        t_line "soul…"
        t_para "The WISE TRIO say"
        t_line "things that are so"
        t_para "very difficult to"
        t_line "understand…"
        t_done )
};
const txt_cmd_s EcruteakTinTowerEntranceSageText_HearsClearBell[] = {
    text_start("A momentous event"
        t_line "has occurred."
        t_para "I beg your pardon,"
        t_line "but I must ask you"
        t_cont "to leave."
        t_para "<……><……><……>"
        t_para "Ah!"
        t_para "The sound of that"
        t_line "CLEAR BELL!"
        t_para "It… It's sublime!"
        t_para "I've never heard"
        t_line "so beautiful a"
        t_cont "sound before!"
        t_para "That bell's chime"
        t_line "is indicative of"
        t_cont "the bearer's soul."
        t_para "You…"
        t_para "You may be able to"
        t_line "make it through"
        t_cont "TIN TOWER."
        t_para "Please, do go on."
        t_done )
};
const txt_cmd_s EcruteakTinTowerEntranceSageText_PleaseDoGoOn[] = {
    text_start("Please, do go on."
        t_done )
};
const txt_cmd_s EcruteakTinTowerEntranceSageText_HeardClearBell[] = {
    text_start("That bell's chime"
        t_line "is indicative of"
        t_cont "the bearer's soul."
        t_para "You…"
        t_para "You may be able to"
        t_line "make it through"
        t_cont "TIN TOWER."
        t_para "Please, do go on."
        t_done )
};
const txt_cmd_s EcruteakTinTowerEntranceWanderingSageText[] = {
    text_start("The TIN TOWER"
        t_line "ahead is a nine-"
        t_para "tier tower of"
        t_line "divine beauty."
        t_para "It soothes the"
        t_line "soul of all who"
        t_cont "see it."
        t_done )
};
const txt_cmd_s EcruteakTinTowerEntranceWanderingSageText_GotClearBell[] = {
    text_start("The TIN TOWER"
        t_line "shook! A #MON"
        t_para "must have returned"
        t_line "to the top!"
        t_done )
};
const txt_cmd_s EcruteakTinTowerEntranceGrampsText[] = {
    text_start("Two towers…"
        t_line "Two #MON…"
        t_para "But when one"
        t_line "burned down, both"
        t_para "#MON flew away,"
        t_line "never to return."
        t_done )
    //db(0, 0) // filler
};
