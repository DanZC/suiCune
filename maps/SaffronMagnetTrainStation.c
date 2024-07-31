#include "../constants.h"
#include "../util/scripting.h"
#include "SaffronMagnetTrainStation.h"
//// EVENTS
enum {
    SAFFRONMAGNETTRAINSTATION_OFFICER = 2,
    SAFFRONMAGNETTRAINSTATION_GYM_GUIDE,
    SAFFRONMAGNETTRAINSTATION_TEACHER,
    SAFFRONMAGNETTRAINSTATION_LASS,
};

const Script_fn_t SaffronMagnetTrainStation_SceneScripts[] = {
    SaffronMagnetTrainStation_MapScripts_DummyScene , //  SCENE_DEFAULT,
};

const struct MapCallback SaffronMagnetTrainStation_MapCallbacks[] = {
    0,
};

const struct MapScripts SaffronMagnetTrainStation_MapScripts = {
    .scene_script_count = lengthof(SaffronMagnetTrainStation_SceneScripts),
    .scene_scripts = SaffronMagnetTrainStation_SceneScripts,

    .callback_count = 0, // lengthof(SaffronMagnetTrainStation_MapCallbacks),
    .callbacks = SaffronMagnetTrainStation_MapCallbacks,
};

static const struct CoordEvent SaffronMagnetTrainStation_CoordEvents[] = {
    coord_event(11, 6, SCENE_DEFAULT, &Script_ArriveFromGoldenrod),
};

static const struct BGEvent SaffronMagnetTrainStation_BGEvents[] = {
    0,
};

static const struct WarpEventData SaffronMagnetTrainStation_WarpEvents[] = {
    warp_event(8, 17, SAFFRON_CITY, 6),
    warp_event(9, 17, SAFFRON_CITY, 6),
    warp_event(6, 5, GOLDENROD_MAGNET_TRAIN_STATION, 4),
    warp_event(11, 5, GOLDENROD_MAGNET_TRAIN_STATION, 3),
};

static const struct ObjEvent SaffronMagnetTrainStation_ObjectEvents[] = {
    object_event(9, 9, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SaffronMagnetTrainStationOfficerScript, -1),
    object_event(10, 14, SPRITE_GYM_GUIDE, SPRITEMOVEDATA_WANDER, 1, 1, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SaffronMagnetTrainStationGymGuideScript, -1),
    object_event(6, 11, SPRITE_TEACHER, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &SaffronMagnetTrainStationTeacherScript, EVENT_SAFFRON_TRAIN_STATION_POPULATION),
    object_event(6, 10, SPRITE_LASS, SPRITEMOVEDATA_STANDING_UP, 0, 0, -1, -1, PAL_NPC_GREEN, OBJECTTYPE_SCRIPT, 0, &SaffronMagnetTrainStationLassScript, EVENT_SAFFRON_TRAIN_STATION_POPULATION),
};

const struct MapEvents SaffronMagnetTrainStation_MapEvents = {
    .warp_event_count = lengthof(SaffronMagnetTrainStation_WarpEvents),
    .warp_events = SaffronMagnetTrainStation_WarpEvents,

    .coord_event_count = lengthof(SaffronMagnetTrainStation_CoordEvents),
    .coord_events = SaffronMagnetTrainStation_CoordEvents,

    .bg_event_count = 0, // lengthof(SaffronMagnetTrainStation_BGEvents),
    .bg_events = SaffronMagnetTrainStation_BGEvents,

    .obj_event_count = lengthof(SaffronMagnetTrainStation_ObjectEvents),
    .obj_events = SaffronMagnetTrainStation_ObjectEvents,
};

//// CODE
// #define DEBUG_TRAIN_STATION 1

bool SaffronMagnetTrainStation_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool SaffronMagnetTrainStationOfficerScript(script_s* s) {
    static const uint8_t MovementBoardTheTrain[] = {
        turn_head(DOWN),
        movement_step_end
    };
    SCRIPT_BEGIN
    faceplayer
    opentext
#if !DEBUG_TRAIN_STATION
    checkevent(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(MagnetTrainToGoldenrod)
    writetext(SaffronMagnetTrainStationOfficerTrainIsntOperatingText)
    waitbutton
    closetext
    s_end
MagnetTrainToGoldenrod:
    writetext(SaffronMagnetTrainStationOfficerAreYouComingOnBoardText)
    yesorno
    iffalse(DecidedNotToRide)
    checkitem(PASS)
    iffalse(PassNotInBag)
#endif
    writetext(SaffronMagnetTrainStationOfficerRightThisWayText)
    waitbutton
    closetext
    applymovement(SAFFRONMAGNETTRAINSTATION_OFFICER, SaffronMagnetTrainStationOfficerApproachTrainDoorMovement)
    applymovement(PLAYER, SaffronMagnetTrainStationPlayerApproachAndEnterTrainMovement)
    setval(TRUE)
    special(MagnetTrain)
    warpcheck
    newloadmap(MAPSETUP_TRAIN)
    applymovement(PLAYER, MovementBoardTheTrain)
    wait(20)
    s_end
PassNotInBag:
    writetext(SaffronMagnetTrainStationOfficerYouDontHaveAPassText)
    waitbutton
    closetext
    s_end
DecidedNotToRide:
    writetext(SaffronMagnetTrainStationOfficerHopeToSeeYouAgainText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Script_ArriveFromGoldenrod(script_s* s) {
    SCRIPT_BEGIN
    applymovement(SAFFRONMAGNETTRAINSTATION_OFFICER, SaffronMagnetTrainStationOfficerApproachTrainDoorMovement)
    applymovement(PLAYER, SaffronMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement)
    applymovement(SAFFRONMAGNETTRAINSTATION_OFFICER, SaffronMagnetTrainStationOfficerReturnToBoardingGateMovement)
    opentext
    writetext(SaffronMagnetTrainStationOfficerArrivedInSaffronText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SaffronMagnetTrainStationGymGuideScript(script_s* s) {
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RETURNED_MACHINE_PART)
    iftrue(ReturnedMachinePart)
    writetext(SaffronMagnetTrainStationGymGuideText)
    waitbutton
    closetext
    s_end
ReturnedMachinePart:
    writetext(SaffronMagnetTrainStationGymGuideText_ReturnedMachinePart)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool SaffronMagnetTrainStationTeacherScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SaffronMagnetTrainStationTeacherText)
    SCRIPT_END
}
bool SaffronMagnetTrainStationLassScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(SaffronMagnetTrainStationLassText)
    SCRIPT_END
}
const uint8_t SaffronMagnetTrainStationOfficerApproachTrainDoorMovement[] = {
    step(UP),
    step(UP),
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t SaffronMagnetTrainStationOfficerReturnToBoardingGateMovement[] = {
    step(LEFT),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t SaffronMagnetTrainStationPlayerApproachAndEnterTrainMovement[] = {
    step(UP),
    step(UP),
    step(UP),
    step(LEFT),
    step(LEFT),
    step(LEFT),
    step(UP),
    step(UP),
    movement_step_end,
};
const uint8_t SaffronMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement[] = {
    step(LEFT),
    step(LEFT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    turn_head(UP),
    movement_step_end,
};
const txt_cmd_s SaffronMagnetTrainStationOfficerTrainIsntOperatingText[] = {
    text_start("I'm sorry, but the"
        t_line "MAGNET TRAIN isn't"
        t_cont "operating now."
        t_done )
};
const txt_cmd_s SaffronMagnetTrainStationOfficerAreYouComingOnBoardText[] = {
    text_start("We'll soon depart"
        t_line "for GOLDENROD."
        t_para "Are you coming on"
        t_line "board?"
        t_done )
};
const txt_cmd_s SaffronMagnetTrainStationOfficerRightThisWayText[] = {
    text_start("May I see your"
        t_line "rail PASS, please?"
        t_para "OK. Right this"
        t_line "way, please."
        t_done )
};
const txt_cmd_s SaffronMagnetTrainStationOfficerYouDontHaveAPassText[] = {
    text_start("Sorry, but you"
        t_line "don't have a PASS."
        t_done )
};
const txt_cmd_s SaffronMagnetTrainStationOfficerHopeToSeeYouAgainText[] = {
    text_start("We hope to see you"
        t_line "again."
        t_done )
};
const txt_cmd_s SaffronMagnetTrainStationOfficerArrivedInSaffronText[] = {
    text_start("We have arrived in"
        t_line "SAFFRON."
        t_para "We hope to see you"
        t_line "again."
        t_done )
};
const txt_cmd_s SaffronMagnetTrainStationGymGuideText[] = {
    text_start("The MAGNET TRAIN"
        t_line "is a super-modern"
        t_para "rail liner that"
        t_line "uses electricity"
        t_para "and magnets to"
        t_line "attain incredible"
        t_cont "speed."
        t_para "However, if there"
        t_line "isn't any elec-"
        t_cont "tricity…"
        t_done )
};
const txt_cmd_s SaffronMagnetTrainStationGymGuideText_ReturnedMachinePart[] = {
    text_start("Whew…"
        t_para "How many times"
        t_line "have I gone back"
        t_para "and forth between"
        t_line "KANTO and JOHTO?"
        t_done )
};
const txt_cmd_s SaffronMagnetTrainStationTeacherText[] = {
    text_start("Before the MAGNET"
        t_line "TRAIN STATION was"
        t_para "built, there was a"
        t_line "house there."
        t_para "A little girl"
        t_line "named COPYCAT used"
        t_cont "to live there."
        t_done )
};
const txt_cmd_s SaffronMagnetTrainStationLassText[] = {
    text_start("Hi. Do you have a"
        t_line "rail PASS? I have"
        t_para "one. All the peo-"
        t_line "ple in SAFFRON who"
        t_para "ride the MAGNET"
        t_line "TRAIN have PASSES."
        t_done )
    //db(0, 0) // filler
};
