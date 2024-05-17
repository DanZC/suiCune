#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStoreElevator.h"
//// EVENTS
const Script_fn_t GoldenrodDeptStoreElevator_SceneScripts[] = {
    0,
};

const struct MapCallback GoldenrodDeptStoreElevator_MapCallbacks[] = {
    0,
};

const struct MapScripts GoldenrodDeptStoreElevator_MapScripts = {
    .scene_script_count = 0, // lengthof(GoldenrodDeptStoreElevator_SceneScripts),
    .scene_scripts = GoldenrodDeptStoreElevator_SceneScripts,

    .callback_count = 0, // lengthof(GoldenrodDeptStoreElevator_MapCallbacks),
    .callbacks = GoldenrodDeptStoreElevator_MapCallbacks,
};

static const struct CoordEvent GoldenrodDeptStoreElevator_CoordEvents[] = {
    0,
};

static const struct BGEvent GoldenrodDeptStoreElevator_BGEvents[] = {
    bg_event(3, 0, BGEVENT_READ, &GoldenrodDeptStoreElevatorScript),
};

static const struct WarpEventData GoldenrodDeptStoreElevator_WarpEvents[] = {
    warp_event(1, 3, GOLDENROD_DEPT_STORE_1F, -1),
    warp_event(2, 3, GOLDENROD_DEPT_STORE_1F, -1),
};

static const struct ObjEvent GoldenrodDeptStoreElevator_ObjectEvents[] = {
    0,
};

const struct MapEvents GoldenrodDeptStoreElevator_MapEvents = {
    .warp_event_count = lengthof(GoldenrodDeptStoreElevator_WarpEvents),
    .warp_events = GoldenrodDeptStoreElevator_WarpEvents,

    .coord_event_count = 0, // lengthof(GoldenrodDeptStoreElevator_CoordEvents),
    .coord_events = GoldenrodDeptStoreElevator_CoordEvents,

    .bg_event_count = lengthof(GoldenrodDeptStoreElevator_BGEvents),
    .bg_events = GoldenrodDeptStoreElevator_BGEvents,

    .obj_event_count = 0, // lengthof(GoldenrodDeptStoreElevator_ObjectEvents),
    .obj_events = GoldenrodDeptStoreElevator_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "GoldenrodDeptStoreElevator.h"

static const struct ElevatorData GoldenrodDeptStoreElevatorData = {
    .count = 7, // floors
    .floorData = (struct ElevatorFloorData[]) {
        elevfloor(FLOOR_B1F, 2, GOLDENROD_DEPT_STORE_B1F),
        elevfloor(FLOOR_1F, 4, GOLDENROD_DEPT_STORE_1F),
        elevfloor(FLOOR_2F, 3, GOLDENROD_DEPT_STORE_2F),
        elevfloor(FLOOR_3F, 3, GOLDENROD_DEPT_STORE_3F),
        elevfloor(FLOOR_4F, 3, GOLDENROD_DEPT_STORE_4F),
        elevfloor(FLOOR_5F, 3, GOLDENROD_DEPT_STORE_5F),
        elevfloor(FLOOR_6F, 2, GOLDENROD_DEPT_STORE_6F),
    },
    //db(-1) // end
};

bool GoldenrodDeptStoreElevatorScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    elevator(&GoldenrodDeptStoreElevatorData)
    closetext
    iffalse(Done)
    pause(5)
    playsound(SFX_ELEVATOR)
    earthquake(60)
    waitsfx
    checkevent(EVENT_GOLDENROD_UNDERGROUND_WAREHOUSE_BLOCKED_OFF)
    iftrue(Done)
    checkevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1)
    iftrue(BoxLayout1)
    checkevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2)
    iftrue(BoxLayout2)
    checkevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3)
    iftrue(BoxLayout3)
BoxLayout3:
    setevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1)
    clearevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2)
    clearevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3)
    s_end
BoxLayout1:
    clearevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1)
    setevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2)
    clearevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3)
    s_end
BoxLayout2:
    clearevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_1)
    clearevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_2)
    setevent(EVENT_GOLDENROD_DEPT_STORE_B1F_LAYOUT_3)
    s_end
Done:
    s_end
    SCRIPT_END
}
