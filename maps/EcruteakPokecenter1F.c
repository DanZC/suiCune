#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakPokecenter1F.h"
//// EVENTS
enum {
    ECRUTEAKPOKECENTER1F_NURSE = 2,
    ECRUTEAKPOKECENTER1F_POKEFAN_M,
    ECRUTEAKPOKECENTER1F_COOLTRAINER_F,
    ECRUTEAKPOKECENTER1F_GYM_GUIDE,
    ECRUTEAKPOKECENTER1F_BILL,
};

const Script_fn_t EcruteakPokecenter1F_SceneScripts[] = {
    EcruteakPokecenter1F_MapScripts_MeetBill , //  SCENE_DEFAULT,
    EcruteakPokecenter1F_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback EcruteakPokecenter1F_MapCallbacks[] = {
    0,
};

const struct MapScripts EcruteakPokecenter1F_MapScripts = {
    .scene_script_count = lengthof(EcruteakPokecenter1F_SceneScripts),
    .scene_scripts = EcruteakPokecenter1F_SceneScripts,

    .callback_count = 0, // lengthof(EcruteakPokecenter1F_MapCallbacks),
    .callbacks = EcruteakPokecenter1F_MapCallbacks,
};

static const struct CoordEvent EcruteakPokecenter1F_CoordEvents[] = {
    0,
};

static const struct BGEvent EcruteakPokecenter1F_BGEvents[] = {
    0,
};

static const struct WarpEventData EcruteakPokecenter1F_WarpEvents[] = {
    warp_event(3, 7, ECRUTEAK_CITY, 6),
    warp_event(4, 7, ECRUTEAK_CITY, 6),
    warp_event(0, 7, POKECENTER_2F, 1),
};

static const struct ObjEvent EcruteakPokecenter1F_ObjectEvents[] = {
    object_event(3, 1, SPRITE_NURSE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakPokecenter1FNurseScript, -1),
    object_event(7, 6, SPRITE_POKEFAN_M, SPRITEMOVEDATA_SPINRANDOM_FAST, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakPokecenter1FPokefanMScript, -1),
    object_event(1, 4, SPRITE_COOLTRAINER_F, SPRITEMOVEDATA_SPINRANDOM_SLOW, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &EcruteakPokecenter1FCooltrainerFScript, -1),
    object_event(7, 1, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &EcruteakPokecenter1FGymGuideScript, -1),
    object_event(0, 7, SPRITE_BILL, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, EVENT_ECRUTEAK_POKE_CENTER_BILL),
};

const struct MapEvents EcruteakPokecenter1F_MapEvents = {
    .warp_event_count = lengthof(EcruteakPokecenter1F_WarpEvents),
    .warp_events = EcruteakPokecenter1F_WarpEvents,

    .coord_event_count = 0, // lengthof(EcruteakPokecenter1F_CoordEvents),
    .coord_events = EcruteakPokecenter1F_CoordEvents,

    .bg_event_count = 0, // lengthof(EcruteakPokecenter1F_BGEvents),
    .bg_events = EcruteakPokecenter1F_BGEvents,

    .obj_event_count = lengthof(EcruteakPokecenter1F_ObjectEvents),
    .obj_events = EcruteakPokecenter1F_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "EcruteakPokecenter1F.h"

bool EcruteakPokecenter1F_MapScripts_MeetBill(script_s* s) {
    SCRIPT_BEGIN
    sdefer(EcruteakPokecenter1F_MapScripts_BillActivatesTimeCapsule);
    s_end
    SCRIPT_END
}
bool EcruteakPokecenter1F_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool EcruteakPokecenter1F_MapScripts_BillActivatesTimeCapsule(script_s* s) {
    SCRIPT_BEGIN
    pause(30)
    playsound(SFX_EXIT_BUILDING)
    appear(ECRUTEAKPOKECENTER1F_BILL)
    waitsfx
    applymovement(ECRUTEAKPOKECENTER1F_BILL, EcruteakPokecenter1FBillMovement1)
    applymovement(PLAYER, EcruteakPokecenter1FPlayerMovement1)
    turnobject(ECRUTEAKPOKECENTER1F_NURSE, UP)
    pause(10)
    turnobject(ECRUTEAKPOKECENTER1F_NURSE, DOWN)
    pause(30)
    turnobject(ECRUTEAKPOKECENTER1F_NURSE, UP)
    pause(10)
    turnobject(ECRUTEAKPOKECENTER1F_NURSE, DOWN)
    pause(20)
    turnobject(ECRUTEAKPOKECENTER1F_BILL, DOWN)
    pause(10)
    opentext
    writetext(EcruteakPokecenter1F_BillText1)
    promptbutton
    writetext(EcruteakPokecenter1F_BillText2)
    waitbutton
    closetext
    turnobject(PLAYER, DOWN)
    applymovement(ECRUTEAKPOKECENTER1F_BILL, EcruteakPokecenter1FBillMovement2)
    playsound(SFX_EXIT_BUILDING)
    disappear(ECRUTEAKPOKECENTER1F_BILL)
    clearevent(EVENT_MET_BILL)
    setflag(ENGINE_TIME_CAPSULE)
    setscene(SCENE_FINISHED)
    waitsfx
    s_end
    SCRIPT_END
}
bool EcruteakPokecenter1FNurseScript(script_s* s) {
    SCRIPT_BEGIN
    jumpstd(PokecenterNurseScript)
    SCRIPT_END
}
bool EcruteakPokecenter1FPokefanMScript(script_s* s) {
    SCRIPT_BEGIN
    special(Mobile_DummyReturnFalse)
    iftrue(mobile)
    jumptextfaceplayer(EcruteakPokecenter1FPokefanMText)
mobile:
    jumptextfaceplayer(EcruteakPokecenter1FPokefanMTextMobile)
    SCRIPT_END
}
bool EcruteakPokecenter1FCooltrainerFScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakPokecenter1FCooltrainerFText)
    SCRIPT_END
}
bool EcruteakPokecenter1FGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(EcruteakPokecenter1FGymGuideText)
    SCRIPT_END
}
const uint8_t EcruteakPokecenter1FBillMovement1[] = {
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    turn_head(UP),
    movement_step_end,
};
const uint8_t EcruteakPokecenter1FBillMovement2[] = {
    step(RIGHT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t EcruteakPokecenter1FPlayerMovement1[] = {
    step(UP),
    step(UP),
    step(UP),
    movement_step_end,
};
const txt_cmd_s EcruteakPokecenter1F_BillText1[] = {
    text_start("Hi, I'm BILL. And"
        t_line "who are you?"
        t_para "Hmm, <PLAYER>, huh?"
        t_line "You've come at the"
        t_cont "right time."
        t_done )
};
const txt_cmd_s EcruteakPokecenter1F_BillText2[] = {
    text_start("I just finished"
        t_line "adjustments on my"
        t_cont "TIME CAPSULE."
        t_para "You know that"
        t_line "#MON can be"
        t_cont "traded, right?"
        t_para "My TIME CAPSULE"
        t_line "was developed to"
        t_para "enable trades with"
        t_line "the past."
        t_para "But you can't send"
        t_line "anything that"
        t_para "didn't exist in"
        t_line "the past."
        t_para "If you did, the PC"
        t_line "in the past would"
        t_cont "have a breakdown."
        t_para "So you have to"
        t_line "remove anything"
        t_para "that wasn't around"
        t_line "in the past."
        t_para "Put simply, no"
        t_line "sending new moves"
        t_para "or new #MON in"
        t_line "the TIME CAPSULE."
        t_para "Don't you worry."
        t_line "I'm done with the"
        t_cont "adjustments."
        t_para "Tomorrow, TIME"
        t_line "CAPSULES will be"
        t_para "running at all"
        t_line "#MON CENTERS."
        t_para "I have to hurry on"
        t_line "back to GOLDENROD"
        t_cont "and see my folks."
        t_para "Buh-bye!"
        t_done )
};
const txt_cmd_s EcruteakPokecenter1FPokefanMText[] = {
    text_start("The way the KIMONO"
        t_line "GIRLS dance is"
        t_para "marvelous. Just"
        t_line "like the way they"
        t_cont "use their #MON."
        t_done )
};
const txt_cmd_s EcruteakPokecenter1FPokefanMTextMobile[] = {
    text_start("You must be hoping"
        t_line "to battle more"
        t_para "people, right?"
        t_line "There's apparently"
        t_para "some place where"
        t_line "trainers gather."
        t_para "Where, you ask?"
        t_para "It's a little past"
        t_line "OLIVINE CITY."
        t_done )
};
const txt_cmd_s EcruteakPokecenter1FCooltrainerFText[] = {
    text_start("MORTY, the GYM"
        t_line "LEADER, is soooo"
        t_cont "cool."
        t_para "His #MON are"
        t_line "really tough too."
        t_done )
};
const txt_cmd_s EcruteakPokecenter1FGymGuideText[] = {
    text_start("LAKE OF RAGE…"
        t_para "The appearance of"
        t_line "a GYARADOS swarm…"
        t_para "I smell a conspir-"
        t_line "acy. I know it!"
        t_done )
    //db(0, 0) // filler
};
