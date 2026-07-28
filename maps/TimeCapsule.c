#include "../constants.h"
#include "../util/scripting.h"
#include "TimeCapsule.h"
//// EVENTS
enum {
    TIMECAPSULE_CHRIS1 = 2,
    TIMECAPSULE_CHRIS2,
};

const Script_fn_t TimeCapsule_SceneScripts[] = {
    TimeCapsule_MapScripts_InitializeTimeCapsule , //  SCENE_DEFAULT,
    TimeCapsule_MapScripts_DummyScene , //  SCENE_FINISHED,
};

const struct MapCallback TimeCapsule_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, TimeCapsule_MapScripts_SetWhichChris),
};

const struct MapScripts TimeCapsule_MapScripts = {
    .scene_script_count = lengthof(TimeCapsule_SceneScripts),
    .scene_scripts = TimeCapsule_SceneScripts,

    .callback_count = lengthof(TimeCapsule_MapCallbacks),
    .callbacks = TimeCapsule_MapCallbacks,
};

static const struct CoordEvent TimeCapsule_CoordEvents[] = {
    0,
};

static const struct BGEvent TimeCapsule_BGEvents[] = {
    bg_event(4, 4, BGEVENT_RIGHT, &TimeCapsuleConsoleScript),
    bg_event(5, 4, BGEVENT_LEFT, &TimeCapsuleConsoleScript),
};

static const struct WarpEventData TimeCapsule_WarpEvents[] = {
    warp_event(4, 7, POKECENTER_2F, 4),
    warp_event(5, 7, POKECENTER_2F, 4),
};

static const struct ObjEvent TimeCapsule_ObjectEvents[] = {
    object_event(3, 4, SPRITE_CHRIS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TimeCapsuleFriendScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1),
    object_event(6, 4, SPRITE_CHRIS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &TimeCapsuleFriendScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2),
};

const struct MapEvents TimeCapsule_MapEvents = {
    .warp_event_count = lengthof(TimeCapsule_WarpEvents),
    .warp_events = TimeCapsule_WarpEvents,

    .coord_event_count = 0, // lengthof(TimeCapsule_CoordEvents),
    .coord_events = TimeCapsule_CoordEvents,

    .bg_event_count = lengthof(TimeCapsule_BGEvents),
    .bg_events = TimeCapsule_BGEvents,

    .obj_event_count = lengthof(TimeCapsule_ObjectEvents),
    .obj_events = TimeCapsule_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "TimeCapsule.h"
#include "Pokecenter2F.h"

bool TimeCapsule_MapScripts_InitializeTimeCapsule(script_s* s) {
    SCRIPT_BEGIN
    sdefer(TimeCapsule_MapScripts_InitializeAndPreparePokecenter2F);
    s_end
    SCRIPT_END
}
bool TimeCapsule_MapScripts_DummyScene(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool TimeCapsule_MapScripts_SetWhichChris(script_s* s) {
    SCRIPT_BEGIN
    special(CableClubCheckWhichChris)
    iffalse(Chris2)
    disappear(TIMECAPSULE_CHRIS2)
    appear(TIMECAPSULE_CHRIS1)
    s_endcallback
Chris2:
    disappear(TIMECAPSULE_CHRIS1)
    appear(TIMECAPSULE_CHRIS2)
    s_endcallback
    SCRIPT_END
}
bool TimeCapsule_MapScripts_InitializeAndPreparePokecenter2F(script_s* s) {
    SCRIPT_BEGIN
    setscene(SCENE_FINISHED)
    setmapscene(POKECENTER_2F, SCENE_POKECENTER2F_LEAVE_TIME_CAPSULE)
    s_end
    SCRIPT_END
}
bool TimeCapsuleConsoleScript(script_s* s) {
    SCRIPT_BEGIN
    special(TimeCapsule)
    newloadmap(MAPSETUP_LINKRETURN)
    s_end
    SCRIPT_END
}
bool TimeCapsuleFriendScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(TimeCapsuleFriendScript_FriendReadyText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s TimeCapsuleFriendScript_FriendReadyText[] = {
    text_start("Your friend is"
        t_line "ready."
        t_done )
    //db(0, 0) // filler
};
