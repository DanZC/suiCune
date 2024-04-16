#include "../constants.h"
#include "../util/scripting.h"
#include "Colosseum.h"
//// EVENTS
enum {
    COLOSSEUM_CHRIS1 = 2,
    COLOSSEUM_CHRIS2,
};

const Script_fn_t Colosseum_SceneScripts[] = {
    Colosseum_MapScripts_InitializeColosseum , //  SCENE_DEFAULT,
    Colosseum_MapScripts_DummyScene1 , //  SCENE_FINISHED,
    Colosseum_MapScripts_DummyScene2 , //  unused,
};

const struct MapCallback Colosseum_MapCallbacks[] = {
    map_callback(MAPCALLBACK_OBJECTS, Colosseum_MapScripts_SetWhichChris),
    map_callback(MAPCALLBACK_NEWMAP, Colosseum_MapScripts_PreparePokecenter2F),
};

const struct MapScripts Colosseum_MapScripts = {
    .scene_script_count = lengthof(Colosseum_SceneScripts),
    .scene_scripts = Colosseum_SceneScripts,

    .callback_count = lengthof(Colosseum_MapCallbacks),
    .callbacks = Colosseum_MapCallbacks,
};

static const struct CoordEvent Colosseum_CoordEvents[] = {
    0,
};

static const struct BGEvent Colosseum_BGEvents[] = {
    bg_event(4, 4, BGEVENT_RIGHT, &ColosseumConsoleScript),
    bg_event(5, 4, BGEVENT_LEFT, &ColosseumConsoleScript),
};

static const struct WarpEventData Colosseum_WarpEvents[] = {
    warp_event(4, 7, POKECENTER_2F, 3),
    warp_event(5, 7, POKECENTER_2F, 3),
};

static const struct ObjEvent Colosseum_ObjectEvents[] = {
    object_event(3, 4, SPRITE_CHRIS, SPRITEMOVEDATA_STANDING_RIGHT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CableClubFriendScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_1),
    object_event(6, 4, SPRITE_CHRIS, SPRITEMOVEDATA_STANDING_LEFT, 0, 0, -1, -1, 0, OBJECTTYPE_SCRIPT, 0, &CableClubFriendScript, EVENT_TEMPORARY_UNTIL_MAP_RELOAD_2),
};

const struct MapEvents Colosseum_MapEvents = {
    .warp_event_count = lengthof(Colosseum_WarpEvents),
    .warp_events = Colosseum_WarpEvents,

    .coord_event_count = 0, // lengthof(Colosseum_CoordEvents),
    .coord_events = Colosseum_CoordEvents,

    .bg_event_count = lengthof(Colosseum_BGEvents),
    .bg_events = Colosseum_BGEvents,

    .obj_event_count = lengthof(Colosseum_ObjectEvents),
    .obj_events = Colosseum_ObjectEvents,
};

//// CODE
#include "../constants.h"
#include "../util/scripting.h"
#include "Colosseum.h"

bool Colosseum_MapScripts_InitializeColosseum(script_s* s) {
    SCRIPT_BEGIN
    sdefer(Colosseum_MapScripts_InitializeAndPreparePokecenter2F);
    s_end
    SCRIPT_END
}
bool Colosseum_MapScripts_DummyScene1(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Colosseum_MapScripts_DummyScene2(script_s* s) {
    SCRIPT_BEGIN
    s_end
    SCRIPT_END
}
bool Colosseum_MapScripts_SetWhichChris(script_s* s) {
    SCRIPT_BEGIN
    special(CableClubCheckWhichChris)
    iffalse_jump(Colosseum_MapScripts_Chris2)
    disappear(COLOSSEUM_CHRIS2)
    appear(COLOSSEUM_CHRIS1)
    s_endcallback
    SCRIPT_END
}
bool Colosseum_MapScripts_Chris2(script_s* s) {
    SCRIPT_BEGIN
    disappear(COLOSSEUM_CHRIS1)
    appear(COLOSSEUM_CHRIS2)
    s_endcallback
    SCRIPT_END
}
bool Colosseum_MapScripts_PreparePokecenter2F(script_s* s) {
    SCRIPT_BEGIN
    setmapscene(POKECENTER_2F, SCENE_POKECENTER2F_LEAVE_COLOSSEUM)
    s_endcallback
    SCRIPT_END
}
bool Colosseum_MapScripts_InitializeAndPreparePokecenter2F(script_s* s) {
    SCRIPT_BEGIN
    setscene(SCENE_FINISHED)
    setmapscene(POKECENTER_2F, SCENE_POKECENTER2F_LEAVE_COLOSSEUM)
    s_end
    SCRIPT_END
}
bool ColosseumConsoleScript(script_s* s) {
    SCRIPT_BEGIN
    special(Colosseum)
    newloadmap(MAPSETUP_LINKRETURN)
    s_end
    SCRIPT_END
}
bool CableClubFriendScript(script_s* s) {
    SCRIPT_BEGIN
    opentext
    writetext(Colosseum_FriendReadyText)
    waitbutton
    closetext
    s_end
    SCRIPT_END
}
const txt_cmd_s Colosseum_FriendReadyText[] = {
    text_start("Your friend is"
        t_line "ready."
        t_done )
    //db(0, 0) // filler
};
