#include "../constants.h"
#include "../util/scripting.h"
#include "BattleTowerElevator.h"
#include "BattleTower1F.h"
//// EVENTS
enum {
    BATTLETOWERELEVATOR_RECEPTIONIST = 2,
};

const Script_fn_t BattleTowerElevator_SceneScripts[] = {
    BattleTowerElevator_MapScripts_Scene0 , //  SCENE_DEFAULT,
    BattleTowerElevator_MapScripts_Scene1 , //  SCENE_FINISHED,
};

const struct MapCallback BattleTowerElevator_MapCallbacks[] = {
    0,
};

const struct MapScripts BattleTowerElevator_MapScripts = {
    .scene_script_count = lengthof(BattleTowerElevator_SceneScripts),
    .scene_scripts = BattleTowerElevator_SceneScripts,

    .callback_count = 0, // lengthof(BattleTowerElevator_MapCallbacks),
    .callbacks = BattleTowerElevator_MapCallbacks,
};

static const struct CoordEvent BattleTowerElevator_CoordEvents[] = {
    0,
};

static const struct BGEvent BattleTowerElevator_BGEvents[] = {
    0,
};

static const struct WarpEventData BattleTowerElevator_WarpEvents[] = {
    warp_event(1, 3, BATTLE_TOWER_HALLWAY, 1),
    warp_event(2, 3, BATTLE_TOWER_HALLWAY, 1),
};

static const struct ObjEvent BattleTowerElevator_ObjectEvents[] = {
    object_event(1, 2, SPRITE_RECEPTIONIST, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &MovementData_BattleTowerElevatorReceptionistWalksIn, -1),
};

const struct MapEvents BattleTowerElevator_MapEvents = {
    .warp_event_count = lengthof(BattleTowerElevator_WarpEvents),
    .warp_events = BattleTowerElevator_WarpEvents,

    .coord_event_count = 0, // lengthof(BattleTowerElevator_CoordEvents),
    .coord_events = BattleTowerElevator_CoordEvents,

    .bg_event_count = 0, // lengthof(BattleTowerElevator_BGEvents),
    .bg_events = BattleTowerElevator_BGEvents,

    .obj_event_count = lengthof(BattleTowerElevator_ObjectEvents),
    .obj_events = BattleTowerElevator_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "BattleTowerElevator.h"

bool BattleTowerElevator_MapScripts_Scene0(script_s* s) {
    SCRIPT_BEGIN
    sdefer(BattleTowerElevator_MapScripts_RideElevator);
    setscene(SCENE_FINISHED)
    SCRIPT_FALLTHROUGH(BattleTowerElevator_MapScripts_Scene1)
}
bool BattleTowerElevator_MapScripts_Scene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool BattleTowerElevator_MapScripts_RideElevator(script_s* s) {
    SCRIPT_BEGIN
    follow(BATTLETOWERELEVATOR_RECEPTIONIST, PLAYER)
    applymovement(BATTLETOWERELEVATOR_RECEPTIONIST, MovementData_BattleTowerElevatorReceptionistWalksIn)
    applymovement(PLAYER, MovementData_BattleTowerElevatorPlayerWalksIn)
    setval(BATTLETOWERACTION_0A)
    special(BattleTowerAction)
    playsound(SFX_ELEVATOR)
    earthquake(60)
    waitsfx
    follow(BATTLETOWERELEVATOR_RECEPTIONIST, PLAYER)
    applymovement(BATTLETOWERELEVATOR_RECEPTIONIST, MovementData_BattleTowerElevatorExitElevator)
    stopfollow
    warpsound
    disappear(BATTLETOWERELEVATOR_RECEPTIONIST)
    applymovement(PLAYER, MovementData_BattleTowerElevatorExitElevator)
    warpcheck
    s_end
    SCRIPT_END
}
const uint8_t MovementData_BattleTowerElevatorReceptionistWalksIn[] = {
    step(RIGHT),
    turn_head(DOWN),
    movement_step_end,
};
const uint8_t MovementData_BattleTowerElevatorPlayerWalksIn[] = {
    turn_head(DOWN),
    movement_step_end,
    //db(0, 0) // filler
};
