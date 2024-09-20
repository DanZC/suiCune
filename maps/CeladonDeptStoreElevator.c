#include "../constants.h"
#include "../util/scripting.h"
#include "CeladonDeptStoreElevator.h"
//// EVENTS
const Script_fn_t CeladonDeptStoreElevator_SceneScripts[] = {
    0,
};

const struct MapCallback CeladonDeptStoreElevator_MapCallbacks[] = {
    0,
};

const struct MapScripts CeladonDeptStoreElevator_MapScripts = {
    .scene_script_count = 0, // lengthof(CeladonDeptStoreElevator_SceneScripts),
    .scene_scripts = CeladonDeptStoreElevator_SceneScripts,

    .callback_count = 0, // lengthof(CeladonDeptStoreElevator_MapCallbacks),
    .callbacks = CeladonDeptStoreElevator_MapCallbacks,
};

static const struct CoordEvent CeladonDeptStoreElevator_CoordEvents[] = {
    0,
};

static const struct BGEvent CeladonDeptStoreElevator_BGEvents[] = {
    bg_event(3, 0, BGEVENT_READ, &CeladonDeptStoreElevatorScript),
};

static const struct WarpEventData CeladonDeptStoreElevator_WarpEvents[] = {
    warp_event(1, 3, CELADON_DEPT_STORE_1F, -1),
    warp_event(2, 3, CELADON_DEPT_STORE_1F, -1),
};

static const struct ObjEvent CeladonDeptStoreElevator_ObjectEvents[] = {
    0,
};

const struct MapEvents CeladonDeptStoreElevator_MapEvents = {
    .warp_event_count = lengthof(CeladonDeptStoreElevator_WarpEvents),
    .warp_events = CeladonDeptStoreElevator_WarpEvents,

    .coord_event_count = 0, // lengthof(CeladonDeptStoreElevator_CoordEvents),
    .coord_events = CeladonDeptStoreElevator_CoordEvents,

    .bg_event_count = lengthof(CeladonDeptStoreElevator_BGEvents),
    .bg_events = CeladonDeptStoreElevator_BGEvents,

    .obj_event_count = 0, // lengthof(CeladonDeptStoreElevator_ObjectEvents),
    .obj_events = CeladonDeptStoreElevator_ObjectEvents,
};

//// CODE

static const struct ElevatorData CeladonDeptStoreElevatorData = {
    .count = 6, // floors
    .floorData = (struct ElevatorFloorData[]) {
        elevfloor(FLOOR_1F, 4, CELADON_DEPT_STORE_1F),
        elevfloor(FLOOR_2F, 3, CELADON_DEPT_STORE_2F),
        elevfloor(FLOOR_3F, 3, CELADON_DEPT_STORE_3F),
        elevfloor(FLOOR_4F, 3, CELADON_DEPT_STORE_4F),
        elevfloor(FLOOR_5F, 3, CELADON_DEPT_STORE_5F),
        elevfloor(FLOOR_6F, 2, CELADON_DEPT_STORE_6F),
    },
    //db(-1) // end
    //db(0, 0) // filler
};

bool CeladonDeptStoreElevatorScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    elevator(&CeladonDeptStoreElevatorData)
    closetext
    iffalse(Done)
    pause(5)
    playsound(SFX_ELEVATOR)
    earthquake(60)
    waitsfx
Done:
    s_end
    SCRIPT_END
}
