#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodMagnetTrainStation.h"
//// EVENTS
enum {
    GOLDENRODMAGNETTRAINSTATION_OFFICER = 2,
    GOLDENRODMAGNETTRAINSTATION_GENTLEMAN,
};

const Script_fn_t GoldenrodMagnetTrainStation_SceneScripts[] = {
    GoldenrodMagnetTrainStation_MapScripts_DummyScene , //  SCENE_DEFAULT,
};

const struct MapCallback GoldenrodMagnetTrainStation_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodMagnetTrainStation_MapScripts = {
    .scene_script_count = lengthof(GoldenrodMagnetTrainStation_SceneScripts),
    .scene_scripts = GoldenrodMagnetTrainStation_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodMagnetTrainStation_MapCallbacks),
    .callbacks = GoldenrodMagnetTrainStation_MapCallbacks,
};

static const struct CoordEvent GoldenrodMagnetTrainStation_CoordEvents[] = {
    coord_event(11, 6, SCENE_DEFAULT, &Script_ArriveFromSaffron),
};

static const struct BGEvent GoldenrodMagnetTrainStation_BGEvents[] = {
    0,
};

static const struct WarpEventData GoldenrodMagnetTrainStation_WarpEvents[] = {
    warp_event(8, 17, GOLDENROD_CITY, 5),
    warp_event(9, 17, GOLDENROD_CITY, 5),
    warp_event(6, 5, SAFFRON_MAGNET_TRAIN_STATION, 4),
    warp_event(11, 5, SAFFRON_MAGNET_TRAIN_STATION, 3),
};

static const struct ObjEvent GoldenrodMagnetTrainStation_ObjectEvents[] = {
    object_event(9, 9, SPRITE_OFFICER, SPRITEMOVEDATA_STANDING_DOWN, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodMagnetTrainStationOfficerScript, -1),
    object_event(11, 14, SPRITE_GENTLEMAN, SPRITEMOVEDATA_WANDER, 2, 2, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &GoldenrodMagnetTrainStationGentlemanScript, EVENT_GOLDENROD_TRAIN_STATION_GENTLEMAN),
};

const struct MapEvents GoldenrodMagnetTrainStation_MapEvents = {
    .warp_event_count = lengthof(GoldenrodMagnetTrainStation_WarpEvents),
    .warp_events = GoldenrodMagnetTrainStation_WarpEvents,

    .coord_event_count = lengthof(GoldenrodMagnetTrainStation_CoordEvents),
    .coord_events = GoldenrodMagnetTrainStation_CoordEvents,

    .bg_event_count = 0, // lengthof(GoldenrodMagnetTrainStation_BGEvents),
    .bg_events = GoldenrodMagnetTrainStation_BGEvents,

    .obj_event_count = lengthof(GoldenrodMagnetTrainStation_ObjectEvents),
    .obj_events = GoldenrodMagnetTrainStation_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodMagnetTrainStation.h"

bool GoldenrodMagnetTrainStation_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool GoldenrodMagnetTrainStationOfficerScript(script_s* s) {
    static const uint8_t MovementBoardTheTrain[] = {
        turn_head(DOWN),
        movement_step_end,
    };
    SCRIPT_BEGIN
    faceplayer
    opentext
    checkevent(EVENT_RESTORED_POWER_TO_KANTO)
    iftrue(MagnetTrainToSaffron)
    writetext(GoldenrodMagnetTrainStationOfficerTheTrainHasntComeInText)
    waitbutton
    closetext
    s_end
MagnetTrainToSaffron:
    writetext(GoldenrodMagnetTrainStationOfficerAreYouComingAboardText)
    yesorno
    iffalse(DecidedNotToRide)
    checkitem(PASS)
    iffalse(PassNotInBag)
    writetext(GoldenrodMagnetTrainStationOfficerRightThisWayText)
    waitbutton
    closetext
    applymovement(GOLDENRODMAGNETTRAINSTATION_OFFICER, GoldenrodMagnetTrainStationOfficerApproachTrainDoorMovement)
    applymovement(PLAYER, GoldenrodMagnetTrainStationPlayerApproachAndEnterTrainMovement)
    setval(FALSE)
    special(MagnetTrain)
    warpcheck
    newloadmap(MAPSETUP_TRAIN)
    applymovement(PLAYER, MovementBoardTheTrain)
    wait(20)
    s_end
PassNotInBag:
    writetext(GoldenrodMagnetTrainStationOfficerYouDontHaveARailPassText)
    waitbutton
    closetext
    s_end
DecidedNotToRide:
    writetext(GoldenrodMagnetTrainStationOfficerHopeToSeeYouAgainText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool Script_ArriveFromSaffron(script_s* s) {
    SCRIPT_BEGIN
    applymovement(GOLDENRODMAGNETTRAINSTATION_OFFICER, GoldenrodMagnetTrainStationOfficerApproachTrainDoorMovement)
    applymovement(PLAYER, GoldenrodMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement)
    applymovement(GOLDENRODMAGNETTRAINSTATION_OFFICER, GoldenrodMagnetTrainStationOfficerReturnToBoardingGateMovement)
    opentext
    writetext(GoldenrodMagnetTrainStationOfficerArrivedInGoldenrodText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
bool GoldenrodMagnetTrainStationGentlemanScript(script_s* s) {
    SCRIPT_BEGIN
    jumptextfaceplayer(GoldenrodMagnetTrainStationGentlemanText)
    SCRIPT_END
}
const uint8_t GoldenrodMagnetTrainStationOfficerApproachTrainDoorMovement[] = {
    step(UP),
    step(UP),
    step(RIGHT),
    turn_head(LEFT),
    movement_step_end,
};
const uint8_t GoldenrodMagnetTrainStationOfficerReturnToBoardingGateMovement[] = {
    step(LEFT),
    step(DOWN),
    step(DOWN),
    movement_step_end,
};
const uint8_t GoldenrodMagnetTrainStationPlayerApproachAndEnterTrainMovement[] = {
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
const uint8_t GoldenrodMagnetTrainStationPlayerLeaveTrainAndEnterStationMovement[] = {
    step(LEFT),
    step(LEFT),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    step(DOWN),
    turn_head(UP),
    movement_step_end,
};
const txt_cmd_s GoldenrodMagnetTrainStationOfficerTheTrainHasntComeInText[] = {
    text_start("The train hasn't"
        t_line "come in…"
        t_para "I know! I'll carry"
        t_line "the passengers on"
        t_cont "my back!"
        t_para "That won't work."
        t_done )
};
const txt_cmd_s GoldenrodMagnetTrainStationOfficerAreYouComingAboardText[] = {
    text_start("We'll soon depart"
        t_line "for SAFFRON."
        t_para "Are you coming"
        t_line "aboard?"
        t_done )
};
const txt_cmd_s GoldenrodMagnetTrainStationOfficerRightThisWayText[] = {
    text_start("May I see your"
        t_line "rail PASS, please?"
        t_para "OK. Right this"
        t_line "way, please."
        t_done )
};
const txt_cmd_s GoldenrodMagnetTrainStationOfficerYouDontHaveARailPassText[] = {
    text_start("Sorry. You don't"
        t_line "have a rail PASS."
        t_done )
};
const txt_cmd_s GoldenrodMagnetTrainStationOfficerHopeToSeeYouAgainText[] = {
    text_start("We hope to see you"
        t_line "again!"
        t_done )
};
const txt_cmd_s GoldenrodMagnetTrainStationOfficerArrivedInGoldenrodText[] = {
    text_start("We have arrived in"
        t_line "GOLDENROD."
        t_para "We hope to see you"
        t_line "again."
        t_done )
};
const txt_cmd_s GoldenrodMagnetTrainStationGentlemanText[] = {
    text_start("I'm the PRESIDENT."
        t_para "My dream was to"
        t_line "build a train that"
        t_para "is faster than any"
        t_line "#MON."
        t_para "It really brings"
        t_line "JOHTO much closer"
        t_cont "to KANTO."
        t_done )
    //db(0, 0) // filler
};
