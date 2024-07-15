#include "../constants.h"
#include "../util/scripting.h"
#include "TrainerHouseB1F.h"
//// EVENTS
enum {
    TRAINERHOUSEB1F_RECEPTIONIST = 2,
    TRAINERHOUSEB1F_CHRIS,
};

const Script_fn_t TrainerHouseB1F_SceneScripts[] = {
    TrainerHouseB1F_MapScripts_DummyScene , //  SCENE_DEFAULT,
};

const struct MapCallback TrainerHouseB1F_MapCallbacks[] = {
    0,
};

const struct MapScripts TrainerHouseB1F_MapScripts = {
    .scene_script_count = lengthof(TrainerHouseB1F_SceneScripts),
    .scene_scripts = TrainerHouseB1F_SceneScripts,

    .callback_count = 0, // lengthof(TrainerHouseB1F_MapCallbacks),
    .callbacks = TrainerHouseB1F_MapCallbacks,
};

static const struct CoordEvent TrainerHouseB1F_CoordEvents[] = {
    coord_event(7, 3, SCENE_DEFAULT, &TrainerHouseReceptionistScript),
};

static const struct BGEvent TrainerHouseB1F_BGEvents[] = {
    0,
};

static const struct WarpEventData TrainerHouseB1F_WarpEvents[] = {
    warp_event(9, 4, TRAINER_HOUSE_1F, 3),
};

static const struct ObjEvent TrainerHouseB1F_ObjectEvents[] = {
    object_event(7, 1, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, -1),
    object_event(6, 11, SPRITE_CHRIS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, PAL_NPC_RED, OBJECTTYPE_SCRIPT, 0, &ObjectEvent, -1),
};

const struct MapEvents TrainerHouseB1F_MapEvents = {
    .warp_event_count = lengthof(TrainerHouseB1F_WarpEvents),
    .warp_events = TrainerHouseB1F_WarpEvents,

    .coord_event_count = lengthof(TrainerHouseB1F_CoordEvents),
    .coord_events = TrainerHouseB1F_CoordEvents,

    .bg_event_count = 0, // lengthof(TrainerHouseB1F_BGEvents),
    .bg_events = TrainerHouseB1F_BGEvents,

    .obj_event_count = lengthof(TrainerHouseB1F_ObjectEvents),
    .obj_events = TrainerHouseB1F_ObjectEvents,
};

//// CODE

bool TrainerHouseB1F_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TrainerHouseReceptionistScript(script_s* s) {
    SCRIPT_BEGIN
    turnobject(PLAYER, UP)
    opentext
    checkflag(ENGINE_FOUGHT_IN_TRAINER_HALL_TODAY)
    iftrue(FoughtTooManyTimes)
    writetext(TrainerHouseB1FIntroText)
    promptbutton
    special(TrainerHouse)
    iffalse(GetCal3Name)
    gettrainername(STRING_BUFFER_3, CAL, CAL2)
    goto GotName;
GetCal3Name:
    gettrainername(STRING_BUFFER_3, CAL, CAL3)
GotName:
    writetext(TrainerHouseB1FYourOpponentIsText)
    promptbutton
    writetext(TrainerHouseB1FAskWantToBattleText)
    yesorno
    iffalse(Declined)
    setflag(ENGINE_FOUGHT_IN_TRAINER_HALL_TODAY)
    writetext(TrainerHouseB1FGoRightInText)
    waitbutton
    closetext
    applymovement(PLAYER, Movement_EnterTrainerHouseBattleRoom)
    opentext
    writetext(TrainerHouseB1FCalBeforeText)
    waitbutton
    closetext
    special(TrainerHouse)
    iffalse(NoSpecialBattle)
    winlosstext(TrainerHouseB1FCalBeatenText, 0)
    setlasttalked(TRAINERHOUSEB1F_CHRIS)
    loadtrainer(CAL, CAL2)
    startbattle
    reloadmapafterbattle
    iffalse(End)
NoSpecialBattle:
    winlosstext(TrainerHouseB1FCalBeatenText, 0)
    setlasttalked(TRAINERHOUSEB1F_CHRIS)
    loadtrainer(CAL, CAL3)
    startbattle
    reloadmapafterbattle
End:
    applymovement(PLAYER, Movement_ExitTrainerHouseBattleRoom)
    s_end
Declined:
    writetext(TrainerHouseB1FPleaseComeAgainText)
    waitbutton
    closetext
    applymovement(PLAYER, Movement_TrainerHouseTurnBack)
    s_end
FoughtTooManyTimes:
    writetext(TrainerHouseB1FSecondChallengeDeniedText)
    waitbutton
    closetext
    applymovement(PLAYER, Movement_TrainerHouseTurnBack)
    s_end
    SCRIPT_END
}
const uint8_t Movement_EnterTrainerHouseBattleRoom[] = {
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(LEFT),
    turn_head(RIGHT),
    movement_step_end,
};
const uint8_t Movement_ExitTrainerHouseBattleRoom[] = {
    step(UP),
    step(UP),
    step(UP),
    step(RIGHT),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(UP),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    step(RIGHT),
    movement_step_end,
};
const uint8_t Movement_TrainerHouseTurnBack[] = {
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const txt_cmd_s TrainerHouseB1FIntroText[] = {
    text_start("Hi. Welcome to our"
        t_line "TRAINING HALL."
        t_para "You may battle a"
        t_line "trainer once per"
        t_cont "day."
        t_done )
};
const txt_cmd_s TrainerHouseB1FYourOpponentIsText[] = {
    text_ram(wram_ptr(wStringBuffer3))
    text_start(" is your"
        t_line "opponent today."
        t_done )
};
const txt_cmd_s TrainerHouseB1FAskWantToBattleText[] = {
    text_start("Would you like to"
        t_line "battle?"
        t_done )
};
const txt_cmd_s TrainerHouseB1FGoRightInText[] = {
    text_start("Please go right"
        t_line "through."
        t_para "You may begin"
        t_line "right away."
        t_done )
};
const txt_cmd_s TrainerHouseB1FPleaseComeAgainText[] = {
    text_start("Sorry. Only those"
        t_line "trainers who will"
        t_para "be battling are"
        t_line "allowed to go in."
        t_done )
};
const txt_cmd_s TrainerHouseB1FSecondChallengeDeniedText[] = {
    text_start("I'm sorry."
        t_line "This would be your"
        t_para "second time today."
        t_line "You're permitted"
        t_para "to enter just once"
        t_line "a day."
        t_done )
};
const txt_cmd_s TrainerHouseB1FCalBeatenText[] = {
    text_start("I lost…"
        t_line "Darn…"
        t_done )
};
const txt_cmd_s TrainerHouseB1FCalBeforeText[] = {
    text_start("I traveled out"
        t_line "here just so I"
        t_cont "could battle you."
        t_done )
    //db(0, 0) // filler
};
