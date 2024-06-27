#include "../constants.h"
#include "../util/scripting.h"
#include "HallOfFame.h"
//// EVENTS
enum {
    HALLOFFAME_LANCE = 2,
};

const Script_fn_t HallOfFame_SceneScripts[] = {
    HallOfFame_MapScripts_EnterHallOfFame , //  SCENE_DEFAULT,
    HallOfFame_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback HallOfFame_MapCallbacks[] = {
    0,
};

const struct MapScripts HallOfFame_MapScripts = {
    .scene_script_count = lengthof(HallOfFame_SceneScripts),
    .scene_scripts = HallOfFame_SceneScripts,

    .callback_count = 0, // lengthof(HallOfFame_MapCallbacks),
    .callbacks = HallOfFame_MapCallbacks,
};

static const struct CoordEvent HallOfFame_CoordEvents[] = {
    0,
};

static const struct BGEvent HallOfFame_BGEvents[] = {
    0,
};

static const struct WarpEventData HallOfFame_WarpEvents[] = {
    warp_event(4, 13, LANCES_ROOM, 3),
    warp_event(5, 13, LANCES_ROOM, 4),
};

static const struct ObjEvent HallOfFame_ObjectEvents[] = {
    object_event(4, 12, SPRITE_LANCE, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, -1),
};

const struct MapEvents HallOfFame_MapEvents = {
    .warp_event_count = lengthof(HallOfFame_WarpEvents),
    .warp_events = HallOfFame_WarpEvents,

    .coord_event_count = 0, // lengthof(HallOfFame_CoordEvents),
    .coord_events = HallOfFame_CoordEvents,

    .bg_event_count = 0, // lengthof(HallOfFame_BGEvents),
    .bg_events = HallOfFame_BGEvents,

    .obj_event_count = lengthof(HallOfFame_ObjectEvents),
    .obj_events = HallOfFame_ObjectEvents,
};

//// CODE

bool HallOfFame_MapScripts_EnterHallOfFame(script_s* s) {
    SCRIPT_BEGIN
    sdefer(HallOfFame_MapScripts_EnterHallOfFameScript);
    s_end
    SCRIPT_END
}
bool HallOfFame_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool HallOfFame_MapScripts_EnterHallOfFameScript(script_s* s) {
    SCRIPT_BEGIN
    follow(HALLOFFAME_LANCE, PLAYER)
    applymovement(HALLOFFAME_LANCE, HallOfFame_WalkUpWithLance)
    stopfollow
    turnobject(PLAYER, RIGHT)
    opentext
    writetext(HallOfFame_LanceText)
    waitbutton
    closetext
    turnobject(HALLOFFAME_LANCE, UP)
    applymovement(PLAYER, HallOfFame_SlowlyApproachMachine)
    setscene(SCENE_FINISHED)
    pause(15)
    setval(HEALMACHINE_HALL_OF_FAME)
    special(HealMachineAnim)
    setevent(EVENT_BEAT_ELITE_FOUR)
    setevent(EVENT_TELEPORT_GUY)
    setevent(EVENT_RIVAL_SPROUT_TOWER)
    clearevent(EVENT_RED_IN_MT_SILVER)
    setevent(EVENT_OLIVINE_PORT_SPRITES_BEFORE_HALL_OF_FAME)
    clearevent(EVENT_OLIVINE_PORT_SPRITES_AFTER_HALL_OF_FAME)
    setmapscene(SPROUT_TOWER_3F, SCENE_FINISHED)
    special(HealParty)
    checkevent(EVENT_GOT_SS_TICKET_FROM_ELM)
    iftrue(SkipPhoneCall)
    specialphonecall(SPECIALCALL_SSTICKET)
SkipPhoneCall:
    halloffame
    s_end
    SCRIPT_END
}
const uint8_t HallOfFame_WalkUpWithLance[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t HallOfFame_SlowlyApproachMachine[] = {
    slow_step(UP),
    movement_step_end,
};
const txt_cmd_s HallOfFame_LanceText[] = {
    text_start("LANCE: It's been a"
        t_line "long time since I"
        t_cont "last came here."
        t_para "This is where we"
        t_line "honor the LEAGUE"
        t_para "CHAMPIONS for all"
        t_line "eternity."
        t_para "Their courageous"
        t_line "#MON are also"
        t_cont "inducted."
        t_para "Here today, we"
        t_line "witnessed the rise"
        t_para "of a new LEAGUE"
        t_line "CHAMPION--a"
        t_para "trainer who feels"
        t_line "compassion for,"
        t_para "and trust toward,"
        t_line "all #MON."
        t_para "A trainer who"
        t_line "succeeded through"
        t_para "perseverance and"
        t_line "determination."
        t_para "The new LEAGUE"
        t_line "CHAMPION who has"
        t_para "all the makings"
        t_line "of greatness!"
        t_para "<PLAY_G>, allow me"
        t_line "to register you"
        t_para "and your partners"
        t_line "as CHAMPIONS!"
        t_done )
    //db(0, 0) // filler
};
