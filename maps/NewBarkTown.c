#include "../constants.h"
#include "../util/scripting.h"
#include "NewBarkTown.h"
//// EVENTS
enum {
    NEWBARKTOWN_TEACHER,
    NEWBARKTOWN_FISHER,
    NEWBARKTOWN_SILVER,
};

const Script_fn_t NewBarkTown_SceneScripts[] = {
    NewBarkTown_MapScripts_DummyScene0 , //  SCENE_DEFAULT,
    NewBarkTown_MapScripts_DummyScene1 , //  SCENE_FINISHED,
};

const struct MapCallback NewBarkTown_MapCallbacks[] = {
    map_callback(MAPCALLBACK_NEWMAP, NewBarkTown_MapScripts_FlyPoint),
};

const struct MapScripts NewBarkTown_MapScripts = {
    .scene_script_count = lengthof(NewBarkTown_SceneScripts),
    .scene_scripts = NewBarkTown_SceneScripts,

    .callback_count = lengthof(NewBarkTown_MapCallbacks),
    .callbacks = NewBarkTown_MapCallbacks,
};

static const struct CoordEvent NewBarkTown_CoordEvents[] = {
    coord_event(1, 8, SCENE_DEFAULT, NewBarkTown_TeacherStopsYouScene1),
    coord_event(1, 9, SCENE_DEFAULT, NewBarkTown_TeacherStopsYouScene2),
};

static const struct BGEvent NewBarkTown_BGEvents[] = {
    bg_event(8, 8, BGEVENT_READ, NewBarkTownSign),
    bg_event(11, 5, BGEVENT_READ, NewBarkTownPlayersHouseSign),
    bg_event(3, 3, BGEVENT_READ, NewBarkTownElmsLabSign),
    bg_event(9, 13, BGEVENT_READ, NewBarkTownElmsHouseSign),
};

static const struct WarpEventData NewBarkTown_WarpEvents[] = {
    warp_event(6, 3, ELMS_LAB, 1),
    warp_event(13, 5, PLAYERS_HOUSE_1F, 1),
    warp_event(3, 11, PLAYERS_NEIGHBORS_HOUSE, 1),
    warp_event(11, 13, ELMS_HOUSE, 1),
};

static const struct ObjEvent NewBarkTown_ObjectEvents[] = {
    object_event(6, 8, SPRITE_TEACHER, SPRITEMOVEDATA_SPINRANDOM_SLOW, 1, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, NewBarkTownTeacherScript, -1),
    object_event(12, 9, SPRITE_FISHER, SPRITEMOVEDATA_WALK_UP_DOWN, 0, 1, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, NewBarkTownFisherScript, -1),
    object_event(3, 2, SPRITE_SILVER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, NewBarkTownSilverScript, EVENT_RIVAL_NEW_BARK_TOWN),
};

const struct MapEvents NewBarkTown_MapEvents = {
    .warp_event_count = lengthof(NewBarkTown_WarpEvents),
    .warp_events = NewBarkTown_WarpEvents,

    .coord_event_count = lengthof(NewBarkTown_CoordEvents),
    .coord_events = NewBarkTown_CoordEvents,

    .bg_event_count = lengthof(NewBarkTown_BGEvents),
    .bg_events = NewBarkTown_BGEvents,

    .obj_event_count = lengthof(NewBarkTown_ObjectEvents),
    .obj_events = NewBarkTown_ObjectEvents,
};

//// CODE


bool NewBarkTown_MapScripts_DummyScene0(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool NewBarkTown_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool NewBarkTown_MapScripts_FlyPoint(script_s* s) {
    SCRIPT_BEGIN
    setflag(ENGINE_FLYPOINT_NEW_BARK)
    clearflag(EVENT_FIRST_TIME_BANKING_WITH_MOM)
    s_endcallback
    SCRIPT_END
}
bool NewBarkTown_TeacherStopsYouScene1(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_MOM)
    turnobject(NEWBARKTOWN_TEACHER, LEFT)
    opentext
    writetext(Text_WaitPlayer)
    waitbutton
    closetext
    turnobject(PLAYER, RIGHT)
    applymovement(NEWBARKTOWN_TEACHER, NewBarkTown_TeacherRunsToYouMovement1)
    opentext
    writetext(Text_WhatDoYouThinkYoureDoing)
    waitbutton
    closetext
    follow(NEWBARKTOWN_TEACHER, PLAYER)
    applymovement(NEWBARKTOWN_TEACHER, NewBarkTown_TeacherBringsYouBackMovement1)
    stopfollow
    opentext
    writetext(Text_ItsDangerousToGoAlone)
    waitbutton
    closetext
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
bool NewBarkTown_TeacherStopsYouScene2(script_s* s) {
    SCRIPT_BEGIN
    playmusic(MUSIC_MOM)
    turnobject(NEWBARKTOWN_TEACHER, LEFT)
    opentext
    writetext(Text_WaitPlayer)
    waitbutton
    closetext
    turnobject(PLAYER, RIGHT)
    applymovement(NEWBARKTOWN_TEACHER, NewBarkTown_TeacherRunsToYouMovement2)
    turnobject(PLAYER, UP)
    opentext
    writetext(Text_WhatDoYouThinkYoureDoing)
    waitbutton
    closetext
    follow(NEWBARKTOWN_TEACHER, PLAYER)
    applymovement(NEWBARKTOWN_TEACHER, NewBarkTown_TeacherBringsYouBackMovement2)
    stopfollow
    opentext
    writetext(Text_ItsDangerousToGoAlone)
    waitbutton
    closetext
    special(RestartMapMusic)
    s_end
    SCRIPT_END
}
bool NewBarkTownTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkflag(EVENT_TALKED_TO_MOM_AFTER_MYSTERY_EGG_QUEST)
    iftrue(CallMom)
    checkflag(EVENT_GAVE_MYSTERY_EGG_TO_ELM)
    iftrue(TellMomYoureLeaving)
    checkflag(EVENT_GOT_A_POKEMON_FROM_ELM)
    iftrue(MonIsAdorable)
    writetext(Text_GearIsImpressive)
    waitbutton
    closetext
    s_end
MonIsAdorable:
    writetext(Text_YourMonIsAdorable)
    waitbutton
    closetext
    s_end
TellMomYoureLeaving:
    writetext(Text_TellMomIfLeaving)
    waitbutton
    closetext
    s_end
CallMom:
    writetext(Text_CallMomOnGear)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool NewBarkTownFisherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(Text_ElmDiscoveredNewMon)
    SCRIPT_END
}
bool NewBarkTownSilverScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(NewBarkTownRivalText1)
    waitbutton
    closetext
    turnobject(NEWBARKTOWN_SILVER, LEFT)
    opentext
    writetext(NewBarkTownRivalText2)
    waitbutton
    closetext
    follow(PLAYER, NEWBARKTOWN_SILVER)
    applymovement(PLAYER, NewBarkTown_SilverPushesYouAwayMovement)
    stopfollow
    pause(5)
    turnobject(NEWBARKTOWN_SILVER, DOWN)
    pause(5)
    playsound(SFX_TACKLE)
    applymovement(PLAYER, NewBarkTown_SilverShovesYouOutMovement)
    applymovement(NEWBARKTOWN_SILVER, NewBarkTown_SilverReturnsToTheShadowsMovement)
    s_end
    SCRIPT_END
}
bool NewBarkTownSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NewBarkTownSignText)
    SCRIPT_END
}
bool NewBarkTownPlayersHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NewBarkTownPlayersHouseSignText)
    SCRIPT_END
}
bool NewBarkTownElmsLabSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NewBarkTownElmsLabSignText)
    SCRIPT_END
}
bool NewBarkTownElmsHouseSign(script_s* s) {
    SCRIPT_BEGIN
    jumptext(NewBarkTownElmsHouseSignText)
    SCRIPT_END
}
const uint8_t NewBarkTown_TeacherRunsToYouMovement1[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    movement_step_end,
};
const uint8_t NewBarkTown_TeacherRunsToYouMovement2[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t NewBarkTown_TeacherBringsYouBackMovement1[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t NewBarkTown_TeacherBringsYouBackMovement2[] = {
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t NewBarkTown_SilverPushesYouAwayMovement[] = {
    turn_head(UP),
    step(DOWN),
    movement_step_end,
};
const uint8_t NewBarkTown_SilverShovesYouOutMovement[] = {
    turn_head(UP),
    movement_fix_facing,
    jump_step(DOWN),
    movement_remove_fixed_facing,
    movement_step_end,
};
const uint8_t NewBarkTown_SilverReturnsToTheShadowsMovement[] = {
    step(RIGHT),
    movement_step_end,
};
const txt_cmd_s Text_GearIsImpressive[] = {
    text_start("Wow, your #GEAR"
        t_line "is impressive!"
        t_para "Did your mom get"
        t_line "it for you?"
        t_done )
};
const txt_cmd_s Text_WaitPlayer[] = {
    text_start("Wait, <PLAY_G>!"
        t_done )
};
const txt_cmd_s Text_WhatDoYouThinkYoureDoing[] = {
    text_start("What do you think"
        t_line "you're doing?"
        t_done )
};
const txt_cmd_s Text_ItsDangerousToGoAlone[] = {
    text_start("It's dangerous to"
        t_line "go out without a"
        t_cont "#MON!"
        t_para "Wild #MON"
        t_line "jump out of the"
        t_para "grass on the way"
        t_line "to the next town."
        t_done )
};
const txt_cmd_s Text_YourMonIsAdorable[] = {
    text_start("Oh! Your #MON"
        t_line "is adorable!"
        t_cont "I wish I had one!"
        t_done )
};
const txt_cmd_s Text_TellMomIfLeaving[] = {
    text_start("Hi, <PLAY_G>!"
        t_line "Leaving again?"
        t_para "You should tell"
        t_line "your mom if you"
        t_cont "are leaving."
        t_done )
};
const txt_cmd_s Text_CallMomOnGear[] = {
    text_start("Call your mom on"
        t_line "your #GEAR to"
        t_para "let her know how"
        t_line "you're doing."
        t_done )
};
const txt_cmd_s Text_ElmDiscoveredNewMon[] = {
    text_start("Yo, <PLAYER>!"
        t_para "I hear PROF.ELM"
        t_line "discovered some"
        t_cont "new #MON."
        t_done )
};
const txt_cmd_s NewBarkTownRivalText1[] = {
    text_start("<……>"
        t_para "So this is the"
        t_line "famous ELM #MON"
        t_cont "LAB…"
        t_done )
};
const txt_cmd_s NewBarkTownRivalText2[] = {
    text_start("…What are you"
        t_line "staring at?"
        t_done )
};
const txt_cmd_s NewBarkTownSignText[] = {
    text_start("NEW BARK TOWN"
        t_para "The Town Where the"
        t_line "Winds of a New"
        t_cont "Beginning Blow"
        t_done )
};
const txt_cmd_s NewBarkTownPlayersHouseSignText[] = {
    text_start("<PLAYER>'s House"
        t_done )
};
const txt_cmd_s NewBarkTownElmsLabSignText[] = {
    text_start("ELM #MON LAB"
        t_done )
};
const txt_cmd_s NewBarkTownElmsHouseSignText[] = {
    text_start("ELM'S HOUSE"
        t_done )
    //db(0, 0) // filler
};
